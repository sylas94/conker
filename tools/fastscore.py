#!/usr/bin/env python3
"""fastscore.py -- 0.7 s exact per-function scoring, ~85x faster than the make+asm-differ loop.

WHY THIS EXISTS
    The normal match loop is `make build/src/<tu>.c.o` + asm-differ, which costs ~60 s per
    variant because make re-scans dependencies and asm-processor post-processes the object.
    That budget is what stops an agent from sweeping a search space (e.g. all 720 declaration
    orderings of a 9-local function).  This script does the same compile by hand -- asm_processor
    then IDO cc, straight into a PRIVATE directory -- and compares the emitted instruction WORDS
    against the golden .s, masking relocated fields.  Measured on game_AEB40/func_15084044 it
    reproduces asm-differ's row count EXACTLY (13 rows -> mism 13) at 0.7 s per build.

    It NEVER touches conker/build/, so it needs no buildlock and cannot collide with another
    agent's build or read a stale object (trap 4).

WHAT THE NUMBER MEANS
    mism = number of instruction words that differ from golden, after masking every field that
    carries a relocation (R_MIPS_26 -> low 26 bits, HI16/LO16/GPREL16 -> low 16 bits), plus
    10 per instruction of length difference.  It is a SEARCH METRIC, not a verdict:
      * mism == 0 means the instruction stream matches, but the masked-out relocation SYMBOLS
        were not compared.  You must still confirm with the real loop
        (`make` + `python3 ../tools/asm-differ/diff.py -o <func> -R --max-lines 4096`)
        before declaring a match.  See the relocation-naming floor in the wave brief.
      * mism > 0 is trustworthy as an ordering: lower really is closer.

USAGE
    python3 tools/fastscore.py <tu> <func> [source.c ...]
        <tu>      e.g. game_AEB40         (golden read from asm/nonmatchings/<tu>/<func>.s)
        <func>    e.g. func_15084044
        source.c  candidate TU sources; defaults to conker/src/<tu>.c
    Run from anywhere; paths are resolved against the repo root below.

    As a library:
        import fastscore
        sc = fastscore.Scorer("game_AEB40", "func_15084044")
        mism, info, rows = sc.score(open("cand.c").read())
"""

import io
import os
import re
import subprocess
import sys

REPO = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
CONKER = os.path.join(REPO, "conker")
CC = os.path.join(REPO, "ido", "ido5.3_recomp", "cc")
OBJDUMP = "mips-linux-gnu-objdump"

# Must stay in sync with conker/Makefile (CFLAGS + INCLUDE_CFLAGS + OPT_FLAGS + MIPSBIT).
CFLAGS = (
    "-G 0 -Xfullwarn -Xcpluscomm -signed -nostdinc -non_shared -Wab,-r4300_mul "
    "-D_LANGUAGE_C -D_FINALROM -DF3DEX_GBI_2 -D_MIPS_SZLONG=32 -woff 649,838 "
    "-I . -I include -I include/2.0L -I include/2.0L/PR -I include/libc "
    "-I src/libultra/os -I src/libultra/audio -I src/libultra/io"
).split()
OPT_DEFAULT = ["-O2", "-g3"]          # conker/Makefile: OPT_FLAGS := -O2 -g3
MIPSBIT = ["-mips2", "-o32"]          # conker/Makefile: MIPSBIT := -mips2 -o32

# Per-object OPT_FLAGS overrides, e.g.
#   $(BUILD_DIR)/$(SRC_DIR)/game_21CAF0.c.o: OPT_FLAGS := -O1
#   $(BUILD_DIR)/$(SRC_DIR)/libultra/audio/%.o: OPT_FLAGS := -g
_OVERRIDE = re.compile(
    r"^\$\(BUILD_DIR\)/\$\(SRC_DIR\)/(\S+)\.o:\s*OPT_FLAGS\s*:?=\s*(.+?)\s*$", re.M)


def _tu_relpath(tu):
    """TU name -> path relative to conker/src, e.g. game_21CAF0 -> game_21CAF0.c."""
    root_src = os.path.join(CONKER, "src")
    for root, _dirs, files in os.walk(root_src):
        if tu + ".c" in files:
            full = os.path.join(root, tu + ".c")
            return os.path.relpath(full, root_src).replace(os.sep, "/")
    return None


def opt_flags_for(tu):
    """-> (flags, origin).  Reads conker/Makefile so a -g / -O1 TU is scored correctly.

    A TU whose object carries an OPT_FLAGS override is NOT built at the tree default,
    and compiling it at -O2 -g3 yields a wrong score with no outward sign.
    """
    mk = os.path.join(CONKER, "Makefile")
    rel = _tu_relpath(tu)
    if rel is None or not os.path.exists(mk):
        return OPT_DEFAULT, "default"
    target = rel   # the regex capture excludes the trailing ".o"
    exact = wild = None
    for pat, flags in _OVERRIDE.findall(io.open(mk, encoding="utf-8").read()):
        if pat == target:
            exact = flags.split()
        elif pat.endswith("%") and target.startswith(pat[:-1]):
            wild = flags.split()
    if exact:
        return exact, "Makefile"
    if wild:
        return wild, "Makefile(wildcard)"
    return OPT_DEFAULT, "default"

GOLD_WORD = re.compile(r"/\* \w+ \w+ ([0-9A-F]{8}) \*/")


class Scorer(object):
    def __init__(self, tu, func, workdir=None):
        self.tu = tu
        self.func = func
        gs = os.path.join(CONKER, "asm", "nonmatchings", tu, func + ".s")
        if not os.path.exists(gs):
            raise SystemExit("no golden asm at %s" % gs)
        self.gold = [int(x, 16) for x in GOLD_WORD.findall(open(gs).read())]
        if not self.gold:
            raise SystemExit("parsed 0 words from %s -- is it a handwritten stub?" % gs)
        self.opt, self.opt_origin = opt_flags_for(tu)
        self.work = workdir or os.path.join(
            os.path.expanduser("~"), ".conker_fastscore", "%s.%s" % (tu, func))
        if not os.path.isdir(self.work):
            os.makedirs(self.work)

    def _compile(self, src, tag):
        cf = os.path.join(self.work, tag + ".c")
        pc = os.path.join(self.work, tag + ".p.c")
        ob = os.path.join(self.work, tag + ".o")
        with open(cf, "w") as fo:
            fo.write(src)
        cwd = os.getcwd()
        os.chdir(CONKER)  # asm_processor and the -I paths are relative to conker/
        try:
            with open(pc, "w") as fo:
                rc = subprocess.call(
                    [sys.executable, "../tools/asm-processor/asm_processor.py"]
                    + self.opt + [cf],
                    stdout=fo, stderr=subprocess.PIPE)
            if rc != 0:
                return None, "APFAIL (asm-processor rejected the source)"
            if os.path.exists(ob):
                os.remove(ob)
            # Capture stderr rather than discarding it: a bare "CCFAIL" with no
            # diagnostic has repeatedly cost people a hand re-run of the cc line to
            # find a one-line cause (usually a local prototype clashing with
            # functions.h). Surface the compiler's first real error instead.
            cc = subprocess.run([CC, "-c", "-32"] + CFLAGS + self.opt + MIPSBIT
                                + ["-o", ob, pc],
                                stdout=subprocess.DEVNULL,
                                stderr=subprocess.PIPE)
            if not os.path.exists(ob):
                err = cc.stderr.decode(errors="replace").strip().splitlines()
                err = [l for l in err if "Error" in l or "error" in l] or err
                msg = err[0][:160] if err else "no diagnostic"
                return None, "CCFAIL: " + msg
            return ob, None
        finally:
            os.chdir(cwd)

    def score(self, src, tag="t"):
        """-> (mism, info, rows).  rows = [(index, addr, ours, golden), ...]"""
        ob, err = self._compile(src, tag)
        if err:
            return (10 ** 6, err, [])
        # The trailing sentinel is load-bearing: the body regex is terminated by a
        # blank line, and the LAST function in .text has none.  Without it, a
        # perfectly good object reports NOFN -- a false "your source did not
        # -z is REQUIRED: plain `objdump -d` collapses runs of zero words into "...", which
        # silently DROPS instructions (a `mflo; nop; nop` loses 2), invents a phantom length
        # gap, and mis-aligns every index after the first collapse. One function reported ~100
        # phantom rows and a pad that did not exist; a genuine score-0 match re-scored as 20.
        # compile" that silently kills a whole search.  Cost this project a wave.
        dis = subprocess.check_output([OBJDUMP, "-dz", ob]).decode() + "\n\n"
        m = re.search(r"^([0-9a-f]+) <%s>:\n(.*?)\n\n" % re.escape(self.func),
                      dis, re.S | re.M)
        if not m:
            return (10 ** 6, "NOFN (still a #pragma GLOBAL_ASM?)", [])
        body = m.group(2)
        addrs, words = [], []
        for a, w in re.findall(r"^\s*([0-9a-f]+):\t([0-9a-f]{8})", body, re.M):
            addrs.append(int(a, 16))
            words.append(int(w, 16))
        rel = subprocess.check_output([OBJDUMP, "-r", ob]).decode()
        masks = {}
        for off, typ in re.findall(r"^([0-9a-f]{8}) (R_MIPS_\w+)", rel, re.M):
            masks[int(off, 16)] = 0x03FFFFFF if typ == "R_MIPS_26" else 0xFFFF
        rows = []
        n = min(len(words), len(self.gold))
        for i in range(n):
            mk = masks.get(addrs[i], 0)
            if (words[i] & ~mk) != (self.gold[i] & ~mk):
                rows.append((i, addrs[i], words[i], self.gold[i]))
        mism = len(rows) + abs(len(words) - len(self.gold)) * 10
        fr = re.search(r"addiu\s+sp,sp,(-\d+)", body)
        info = "frame=%s n=%d/%d" % (fr.group(1) if fr else "leaf",
                                     len(words), len(self.gold))
        return (mism, info, rows)


def main(argv):
    if len(argv) < 3:
        raise SystemExit(__doc__)
    tu, func = argv[1], argv[2]
    srcs = argv[3:] or [os.path.join(CONKER, "src", tu + ".c")]
    sc = Scorer(tu, func)
    # Print the flags: a TU built at -g or -O1 scored as -O2 -g3 produces a confident
    # wrong number, and that is invisible unless it is stated.
    print("# %s: OPT_FLAGS %s (%s)" % (tu, " ".join(sc.opt), sc.opt_origin))
    for path in srcs:
        mism, info, rows = sc.score(open(path).read())
        print("%-44s mism=%-6d %s" % (os.path.basename(path), mism, info))
        for i, a, w, g in rows[:24]:
            print("    idx%-5d %04x  ours=%08x  gold=%08x" % (i, a, w, g))
        if len(rows) > 24:
            print("    ... %d more" % (len(rows) - 24))


if __name__ == "__main__":
    main(sys.argv)
