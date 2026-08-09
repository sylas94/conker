#! /usr/bin/env python3
"""
split_conker.py - the repo's supported entry point to n64splat.

Always invoke splat through this wrapper (``make -C conker extract`` does).
Calling ``tools/n64splat/split.py`` directly re-opens two traps:


TRAP 1 - spimdisasm marker labels break tools/asm-processor
---------------------------------------------------------
spimdisasm emits two purely informational labels that splat never configures,
so they keep spimdisasm's own defaults:

    ASM_NM_LABEL        -> "nonmatching <sym>, <size>" emitted *before* a glabel
    ASM_DATA_END_LABEL  -> "enddlabel <sym>"           emitted *after*  a data symbol

``conker/include/macro.inc`` no-ops both, but that only helps the *assembler*.
tools/asm-processor does not use macro.inc: it re-parses each ``.s`` file with
its own GLOBAL_ASM parser and assembles it against
``tools/asm-processor/prelude.inc``. That parser requires a .text block to open
with ``glabel``, so a leading ``nonmatching`` line kills every pragma'd TU with

    Error: .text block without an initial glabel

and a trailing ``enddlabel`` corrupts its .text size accounting (first seen on
``asm/nonmatchings/game_D7980/func_150AA814.s``).

Fix: force both labels to "" before splat runs. Empty string is spimdisasm's
documented "off" value - every emitter is guarded by ``if <LABEL>:``. splat
assigns ASM_TEXT_LABEL/ASM_JTBL_LABEL/... in
``disassembler/spimdisasm_disassembler.py::configure`` but never touches these
two, so we also re-apply the override *after* configure() via a monkeypatch,
which keeps working if a future splat starts setting them.

The fix must live here, in the parent repo: tools/n64splat and
tools/asm-processor are git submodules, and any edit inside them is reverted by
``git submodule update``.


TRAP 2 - "--modes ld" silently truncates undefined_*_auto.txt
-------------------------------------------------------------
``scripts/split.py::main`` calls ``write_undefined_funcs_auto()`` and
``write_undefined_syms_auto()`` unconditionally - outside the ``is_mode_active("ld")``
guard - and both write only symbols whose ``referenced`` flag is set. That flag
is populated during the *code* split phase. A run that skips code mode
therefore rewrites both files with zero entries.

``conker/Makefile`` feeds both to the linker with ``-T``, and ``.gitignore``
ignores ``*_auto.txt``, so the truncation is (a) fatal to the very next link -
hundreds of unrelated undefined references - and (b) NOT recoverable with git.
The only way back is a full re-split.

Policy implemented here:

  * A split that does not include ``code`` mode is REFUSED when the config
    would (re)generate the auto-symbol files.
  * ``--keep-auto-syms`` opts into such a run: the wrapper snapshots both files
    in memory beforehand and restores them afterwards, loudly.
  * After every run, if the config enables the auto-symbol files, they must
    exist and be non-empty, or the wrapper restores what it can and exits 1.

See the module-level constants below to tune this.
"""

from __future__ import annotations

import argparse
import os
import re
import sys
from pathlib import Path
from typing import Dict, List, Optional, Tuple

TOOLS_DIR = Path(__file__).resolve().parent
REPO_ROOT = TOOLS_DIR.parent

# Marker labels that must be silenced. Empty string == "do not emit".
MARKER_ATTRS = ("ASM_NM_LABEL", "ASM_DATA_END_LABEL")

# Bare marker directives that must never reach asm-processor. Used for the
# belt-and-braces post-split scan, so this keeps working even if spimdisasm
# renames the GlobalConfig attributes above out from under us.
BAD_ASM_LINE_RE = re.compile(rb"^[ \t]*(nonmatching|endlabel|enddlabel)\b")


def die(*lines: str) -> "None":
    print("", file=sys.stderr)
    print("split_conker.py: FATAL", file=sys.stderr)
    for line in lines:
        print(f"  {line}", file=sys.stderr)
    print("", file=sys.stderr)
    sys.exit(1)


def note(*lines: str) -> None:
    for line in lines:
        print(f"split_conker.py: {line}", file=sys.stderr)


# --------------------------------------------------------------------------
# Locate the n64splat submodule and import it
# --------------------------------------------------------------------------


def find_splat_dir() -> Path:
    candidates: List[Path] = []
    env = os.environ.get("CONKER_N64SPLAT")
    if env:
        candidates.append(Path(env))
    candidates.append(TOOLS_DIR / "n64splat")
    for parent in [TOOLS_DIR, *TOOLS_DIR.parents]:
        candidates.append(parent / "tools" / "n64splat")

    for cand in candidates:
        if (cand / "src" / "splat" / "__init__.py").is_file():
            return cand.resolve()

    die(
        "could not find the n64splat submodule.",
        f"Looked (in order) at: {', '.join(str(c) for c in candidates)}",
        "The submodule is probably not checked out. Run:",
        "    git submodule update --init --recursive",
        "Or point CONKER_N64SPLAT at a working n64splat checkout.",
    )
    raise SystemExit(1)  # unreachable; keeps type checkers happy


SPLAT_DIR = find_splat_dir()
# Must precede site-packages: a pip-installed `splat64` may also be present, and
# this repo is only known to build byte-perfect against the vendored submodule.
sys.path.insert(0, str(SPLAT_DIR))

try:
    import spimdisasm  # type: ignore
except ImportError as exc:  # pragma: no cover
    die(
        f"cannot import spimdisasm ({exc}).",
        "Install the pinned toolchain into the active Python environment:",
        f"    pip install -r {REPO_ROOT / 'requirements.txt'} -r {SPLAT_DIR / 'requirements.txt'}",
        f"Interpreter in use: {sys.executable}",
    )

try:
    import yaml  # type: ignore
except ImportError as exc:  # pragma: no cover
    die(
        f"cannot import PyYAML ({exc}).",
        f"    pip install -r {REPO_ROOT / 'requirements.txt'}",
    )


def silence_markers(strict: bool = True) -> None:
    """Turn off spimdisasm's `nonmatching` / `enddlabel` marker labels."""
    gc = spimdisasm.common.GlobalConfig
    for attr in MARKER_ATTRS:
        if not hasattr(gc, attr):
            if strict:
                note(
                    f"WARNING: spimdisasm {spimdisasm.__version__} has no "
                    f"GlobalConfig.{attr}; skipping that override.",
                    "If extraction produces marker lines, the post-split scan will catch it.",
                )
            continue
        setattr(gc, attr, "")


silence_markers()

try:
    import src.splat as splat  # type: ignore # noqa: E402
except ImportError as exc:  # pragma: no cover
    die(
        f"cannot import splat from {SPLAT_DIR} ({exc}).",
        "The submodule may be checked out but its dependencies missing. Run:",
        f"    pip install -r {SPLAT_DIR / 'requirements.txt'}",
        f"Interpreter in use: {sys.executable}",
    )

# splat configures spimdisasm inside SpimdisasmDisassembler.configure(). It does
# not currently touch our two markers, but re-assert after configure() so that a
# future splat/spimdisasm cannot quietly turn them back on.
try:
    from src.splat.disassembler import spimdisasm_disassembler as _spim_dis  # type: ignore

    _orig_configure = _spim_dis.SpimdisasmDisassembler.configure

    def _configure_with_markers_off(self, *a, **kw):  # type: ignore[no-untyped-def]
        result = _orig_configure(self, *a, **kw)
        silence_markers(strict=False)
        return result

    _spim_dis.SpimdisasmDisassembler.configure = _configure_with_markers_off  # type: ignore[assignment]
except Exception as exc:  # pragma: no cover
    note(
        f"WARNING: could not hook SpimdisasmDisassembler.configure ({exc}).",
        "Marker suppression still applied at import time.",
    )


# --------------------------------------------------------------------------
# Config peek (pre-flight): where do the auto-symbol files live, and are they on?
# --------------------------------------------------------------------------


class AutoSyms:
    """Resolved location/enablement of the two undefined_*_auto.txt files."""

    def __init__(self, config_paths: List[Path]) -> None:
        merged: Dict = {}
        for path in config_paths:
            if not path.is_file():
                die(f"config file does not exist: {path}")
            with path.open() as f:
                doc = yaml.safe_load(f) or {}
            opts = doc.get("options") or {}
            if not isinstance(opts, dict):
                die(f"{path}: 'options' is not a mapping")
            merged.update(opts)

        # Mirrors splat: base_path is relative to the FIRST config file.
        base = Path(
            os.path.normpath(config_paths[0].parent / merged.get("base_path", "."))
        )
        self.base_path = base
        self.create_syms = bool(merged.get("create_undefined_syms_auto", True))
        self.create_funcs = bool(merged.get("create_undefined_funcs_auto", True))
        self.syms_path = Path(
            os.path.normpath(
                base / merged.get("undefined_syms_auto_path", "undefined_syms_auto.txt")
            )
        )
        self.funcs_path = Path(
            os.path.normpath(
                base
                / merged.get("undefined_funcs_auto_path", "undefined_funcs_auto.txt")
            )
        )
        self.asm_path = Path(
            os.path.normpath(base / merged.get("asm_path", "asm"))
        )

    @property
    def any_enabled(self) -> bool:
        return self.create_syms or self.create_funcs

    def tracked(self) -> List[Tuple[str, Path]]:
        out: List[Tuple[str, Path]] = []
        if self.create_syms:
            out.append(("undefined_syms_auto", self.syms_path))
        if self.create_funcs:
            out.append(("undefined_funcs_auto", self.funcs_path))
        return out


def snapshot(paths: List[Tuple[str, Path]]) -> Dict[Path, Optional[bytes]]:
    snap: Dict[Path, Optional[bytes]] = {}
    for _, path in paths:
        snap[path] = path.read_bytes() if path.is_file() else None
    return snap


def restore(snap: Dict[Path, Optional[bytes]]) -> List[Path]:
    restored: List[Path] = []
    for path, data in snap.items():
        if data is None:
            continue
        current = path.read_bytes() if path.is_file() else b""
        if current == data:
            continue
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_bytes(data)
        restored.append(path)
    return restored


# --------------------------------------------------------------------------
# Post-split scan for marker lines that would break asm-processor
# --------------------------------------------------------------------------


def scan_asm_for_markers(asm_path: Path, limit: int = 10) -> List[str]:
    hits: List[str] = []
    if not asm_path.is_dir():
        return hits
    for path in sorted(asm_path.rglob("*.s")):
        try:
            with path.open("rb") as f:
                for lineno, line in enumerate(f, 1):
                    if BAD_ASM_LINE_RE.match(line):
                        hits.append(
                            f"{path}:{lineno}: {line.decode('utf-8', 'replace').rstrip()}"
                        )
                        break
        except OSError:
            continue
        if len(hits) >= limit:
            break
    return hits


# --------------------------------------------------------------------------
# main
# --------------------------------------------------------------------------


def build_parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(
        prog="split_conker.py",
        description=(
            "Conker wrapper around n64splat: suppresses spimdisasm marker labels "
            "that break asm-processor, and refuses splits that would truncate "
            "undefined_syms_auto.txt / undefined_funcs_auto.txt."
        ),
    )
    splat.scripts.split.add_arguments_to_parser(parser)
    group = parser.add_argument_group("conker wrapper options")
    group.add_argument(
        "--keep-auto-syms",
        action="store_true",
        help=(
            "Permit a split that omits 'code' mode (e.g. --modes ld). The wrapper "
            "snapshots undefined_syms_auto.txt / undefined_funcs_auto.txt before the "
            "run and restores them afterwards, because a non-code split always "
            "rewrites them empty."
        ),
    )
    group.add_argument(
        "--allow-empty-auto-syms",
        action="store_true",
        help=(
            "Skip the post-split non-empty assertion on the auto-symbol files. Only "
            "for configs that legitimately define no undefined symbols."
        ),
    )
    group.add_argument(
        "--skip-marker-scan",
        action="store_true",
        help="Skip the post-split scan for stray 'nonmatching'/'enddlabel' lines.",
    )
    return parser


def normalize_modes(modes) -> List[str]:
    if modes is None:
        return ["all"]
    if isinstance(modes, str):
        return [modes]
    return list(modes)


def main() -> int:
    parser = build_parser()
    args = parser.parse_args()

    config_paths = [Path(p) for p in args.config]
    modes = normalize_modes(args.modes)
    splits_code = "all" in modes or "code" in modes

    auto = AutoSyms(config_paths)

    # ---- Pre-flight: refuse a non-code split that would clobber the auto files
    if auto.any_enabled and not splits_code and not args.keep_auto_syms:
        die(
            f"refusing to run splat with --modes {' '.join(modes)}.",
            "",
            "splat writes undefined_funcs_auto.txt and undefined_syms_auto.txt on EVERY",
            "run, but only lists symbols flagged 'referenced' - a flag set during the",
            "code-split phase. A split without 'code' mode therefore rewrites both files",
            "EMPTY, and conker/Makefile feeds both to ld with -T, so the next link dies",
            "with hundreds of undefined references. They are gitignored (*_auto.txt), so",
            "there is no git checkout back.",
            "",
            "Affected files:",
            *[f"    {p}" for _, p in auto.tracked()],
            "",
            "Choose one:",
            "  * Full split (regenerates everything, always correct):",
            f"        {Path(__file__).name} {' '.join(str(p) for p in config_paths)}",
            "  * Keep the existing auto-symbol files across a partial split",
            "    (correct when the yaml edit cannot change the undefined-symbol set,",
            "     e.g. migrating a rodata blob into a TU):",
            f"        {Path(__file__).name} {' '.join(str(p) for p in config_paths)}"
            f" --modes {' '.join(modes)} --keep-auto-syms",
        )

    snap: Dict[Path, Optional[bytes]] = {}
    if auto.any_enabled and not splits_code:
        snap = snapshot(auto.tracked())
        present = [str(p) for p, d in snap.items() if d]
        note(
            f"--keep-auto-syms: partial split (--modes {' '.join(modes)}); snapshotted "
            f"{len(present)} auto-symbol file(s) for restore after the run.",
        )

    # ---- Run splat
    splat.scripts.split.main(
        args.config,
        args.modes,
        args.verbose,
        args.use_cache,
        args.skip_version_check,
        args.stdout_only,
        args.disassemble_all,
        args.make_full_disasm_for_code,
    )

    # ---- Restore anything a partial split flattened
    if snap:
        restored = restore(snap)
        for path in restored:
            note(f"--keep-auto-syms: restored {path} (splat had rewritten it empty).")
        if not restored:
            note("--keep-auto-syms: auto-symbol files unchanged; nothing to restore.")

    # ---- Post-flight: the auto files must not be empty
    if auto.any_enabled and not args.allow_empty_auto_syms:
        bad: List[str] = []
        for name, path in auto.tracked():
            if not path.is_file():
                bad.append(f"{path} (missing)")
            elif path.stat().st_size == 0:
                bad.append(f"{path} (0 bytes)")
        if bad:
            die(
                "the split finished but left the auto-symbol file(s) unusable:",
                *[f"    {b}" for b in bad],
                "",
                "conker/Makefile passes both to ld via -T; linking now would fail with",
                "hundreds of undefined references.",
                "",
                "Every pre-split snapshot that existed has already been restored, so the",
                "file(s) above had no usable content before this run either.",
                "",
                "Re-run a FULL split to regenerate them:",
                f"    {Path(__file__).name} {' '.join(str(p) for p in config_paths)}",
                "",
                "If this config genuinely has no undefined symbols, either set",
                "'create_undefined_syms_auto: no' / 'create_undefined_funcs_auto: no' in",
                "the yaml, or pass --allow-empty-auto-syms.",
            )

    # ---- Post-flight: no marker line may survive into the asm tree
    if splits_code and not args.skip_marker_scan:
        hits = scan_asm_for_markers(auto.asm_path)
        if hits:
            die(
                "spimdisasm marker labels leaked into the extracted asm tree:",
                *[f"    {h}" for h in hits],
                "",
                "tools/asm-processor cannot parse these: a .text block must open with",
                "'glabel', and a trailing 'enddlabel' breaks its .text size accounting.",
                "",
                f"Installed spimdisasm: {spimdisasm.__version__}. This wrapper clears",
                f"GlobalConfig.{', GlobalConfig.'.join(MARKER_ATTRS)} - if that no longer",
                "suffices, spimdisasm has renamed or added a marker and this wrapper",
                "needs updating. Pin the known-good version in requirements.txt:",
                "    spimdisasm==1.40.1",
            )

    return 0


if __name__ == "__main__":
    sys.exit(main())
