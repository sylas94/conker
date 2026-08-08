#!/usr/bin/env python3
"""Deterministic integration gate for the orchestrator. Replaces the unreliable
LLM integration agent. Match agents leave matching C in their files (failures
self-revert); this script force-cleanly rebuilds, ROM-gates, and commits ONLY
what truly matches — bisecting out any broken function so the ROM can never
regress.

Usage: integrate.py <file1> <func1> <file2> <func2> ...
  (the claimed (file, func) matches from one round)

Robustness vs the prior agent:
- FORCE-clean rebuild (rm the bins) so a failed compile can't leave a stale
  matching bin that passes the sha1 check (the bug that broke 2 commits).
- Check the make exit code AND both sha1s.
- On mismatch, bisect: revert files one at a time until the ROM matches, so a
  single bad function never blocks the good ones.
"""
import os, subprocess, sys, json, time

REPO = os.environ.get("CONKER_REPO", os.path.expanduser("~/conker"))
INNER_SHA = "842e3d348e3c8ae0039e2ab367ad492f9b5266d8"
OUTER_SHA = "4cbadd3c4e0729dec46af64ad018050eada4f47a"

def write_rom_status(ok, commit=""):
    try:
        json.dump({"ok": ok, "sha1": OUTER_SHA, "at": int(time.time()), "commit": commit},
                  open("/tmp/rom_status.json", "w"))
    except Exception:
        pass

def cycle_tag():
    try:
        return " [cycle %s]" % open(os.path.join(REPO, ".cycle")).read().strip()
    except Exception:
        return ""

def sh(cmd):
    return subprocess.run(cmd, shell=True, cwd=REPO, capture_output=True, text=True)

def rom_matches():
    """FORCE-clean build; True only if make succeeds AND both sha1s match."""
    sh("rm -f conker/build/conker.us.bin build/conker.us.z64")
    if sh(". .venv/bin/activate && make -C conker").returncode != 0:
        return False
    inner = sh("sha1sum conker/build/conker.us.bin").stdout.split()
    if not inner or inner[0] != INNER_SHA:
        return False
    if sh(". .venv/bin/activate && make -C conker replace && make -j").returncode != 0:
        return False
    outer = sh("sha1sum build/conker.us.z64").stdout.split()
    return bool(outer) and outer[0] == OUTER_SHA

def is_destubbed(file, func):
    p = f"{REPO}/conker/src/{file}.c"
    pragma = f'#pragma GLOBAL_ASM("asm/nonmatchings/{file}/{func}.s")'
    try:
        return pragma not in open(p).read()
    except OSError:
        return False

def main():
    args = sys.argv[1:]
    pairs = [(args[i], args[i + 1]) for i in range(0, len(args) - 1, 2)]
    # keep only the ones the agents actually de-stubbed (real attempts)
    claimed = [(f, fn) for f, fn in pairs if is_destubbed(f, fn)]
    if not claimed:
        print("INTEGRATE: nothing de-stubbed; nothing to commit"); return

    if rom_matches():
        good = claimed
    else:
        # ADD-BACK bisect: save each claim's matching source, revert to the clean committed base,
        # then add claims back ONE AT A TIME, keeping only those that still build the matching ROM.
        # This drops ONLY genuinely-broken claims. The old linear "revert in order until it matches"
        # dropped good claims that merely preceded a broken one (the "+1 committed when several
        # matched" bug). Claims are distinct files, so each is an independent test.
        saved = {(f, fn): open(os.path.join(REPO, f"conker/src/{f}.c")).read() for f, fn in claimed}
        sh("git checkout conker/src/")
        good = []
        for f, fn in claimed:
            open(os.path.join(REPO, f"conker/src/{f}.c"), "w").write(saved[(f, fn)])
            if rom_matches():
                good.append((f, fn))
            else:
                sh(f"git checkout conker/src/{f}.c")
        if not rom_matches():
            print("INTEGRATE: ROM broken at clean committed base — ABORT, no commit")
            sh("git checkout conker/src/"); write_rom_status(False); return
        bad = [fn for f, fn in claimed if (f, fn) not in good]
        if bad:
            print(f"INTEGRATE: reverted broken/unverifiable: {', '.join(bad)}")
            # Tally ROM-reverts: a func that object-matches (iter_match SCORE:0) but fails the ROM gate looks
            # "matched" (score 0) to the attempts-shelf, so it's re-picked every cycle and reverts forever
            # (e.g. func_151EEFF0/func_150C851C across cycles 30-31). similar_chunk blocklists repeat (>=2)
            # offenders from re-selection (re-probe cycles still give them a fresh shot).
            try:
                with open(os.path.join(REPO, "tools", "rom_reverts.txt"), "a") as fh:
                    for fn in bad:
                        fh.write(fn + "\n")
            except OSError:
                pass

    if not good:
        print("INTEGRATE: no verified matches to commit"); return
    files = " ".join(f"conker/src/{f}.c" for f, _ in good)
    funcs = ", ".join(fn for _, fn in good)
    sh(f"git add {files} tools/ido_cookbook.md")
    if sh("git diff --cached --quiet").returncode == 0:
        print("INTEGRATE: nothing staged (already committed?); no commit"); return
    if os.environ.get("CONKER_TYPING"):                         # Phase-1 typing pass (type_pass.sh)
        head = f"game: type {len(good)} functions (offset-casts -> struct access){cycle_tag()}"
        body = "byte-identical; force-clean full-ROM sha1 verifies. Offset-cast access -> local typed struct."
    else:
        head = f"game: match {len(good)} functions via orchestrator{cycle_tag()}"
        body = "asm-differ score 0; force-clean full-ROM sha1 verifies."
    msg = (f"{head}\\n\\n{funcs}\\n\\n{body}\\n\\n"
           "Co-Authored-By: Claude Opus 5 (1M context) <noreply@anthropic.com>")
    r = sh(f'git commit -q -m "$(printf \'{msg}\')"')
    # A failed commit must NOT report success: git exits non-zero on a missing
    # user.name/user.email or a rejecting hook, which silently left verified
    # matches staged-but-uncommitted (and rom_status claiming a commit landed).
    if r.returncode != 0:
        print(f"INTEGRATE: ROM verified but COMMIT FAILED (git exit {r.returncode}) — "
              f"{len(good)} matches left STAGED, fix git and re-commit")
        print((r.stderr or r.stdout).strip()[:500])
        return
    write_rom_status(True, sh("git rev-parse --short HEAD").stdout.strip())
    print(f"INTEGRATE: committed {len(good)} — {funcs}")

if __name__ == "__main__":
    main()
