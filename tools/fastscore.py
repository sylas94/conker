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
OPT = ["-O2", "-g3", "-mips2", "-o32"]

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
                    [sys.executable, "../tools/asm-processor/asm_processor.py",
                     "-O2", "-g3", cf],
                    stdout=fo, stderr=subprocess.DEVNULL)
            if rc != 0:
                return None, "APFAIL"
            if os.path.exists(ob):
                os.remove(ob)
            subprocess.call([CC, "-c", "-32"] + CFLAGS + OPT + ["-o", ob, pc],
                            stdout=subprocess.DEVNULL, stderr=subprocess.DEVNULL)
            if not os.path.exists(ob):
                return None, "CCFAIL"
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
        # compile" that silently kills a whole search.  Cost this project a wave.
        dis = subprocess.check_output([OBJDUMP, "-d", ob]).decode() + "\n\n"
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
    for path in srcs:
        mism, info, rows = sc.score(open(path).read())
        print("%-44s mism=%-6d %s" % (os.path.basename(path), mism, info))
        for i, a, w, g in rows[:24]:
            print("    idx%-5d %04x  ours=%08x  gold=%08x" % (i, a, w, g))
        if len(rows) > 24:
            print("    ... %d more" % (len(rows) - 24))


if __name__ == "__main__":
    main(sys.argv)
