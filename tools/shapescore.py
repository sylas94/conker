#!/usr/bin/env python3
"""shapescore.py -- the STRUCTURAL companion to tools/fastscore.py.

WHY THIS EXISTS
    fastscore's `mism` counts instruction words that differ from golden AT THE SAME
    INDEX.  That is the right final target (mism 0 == the stream matches), but while a
    function's temp-register allocation is out of phase with golden's, most rows differ
    only in register NAME, and `mism` is then dominated by which rows happen to line up.

    Measured on game_40490/func_150130B4 (2026-08-15): a greedy legal-statement-reorder
    search improved mism 227 -> 212 while DESTROYING 7 rows of golden's instruction
    shape (384/406 -> 377/406).  Two independent searches converged on the same
    plateau, so this is not noise: the two metrics genuinely move in opposite
    directions.  Optimising mism alone can therefore walk you away from golden's code
    while the number goes down.  ALWAYS read both.

WHAT THIS MEASURES
    Both sides are decoded from RAW WORDS through the SAME objdump invocation (never
    from the golden .s text, whose formatting differs and silently mis-parses), then
    normalised: every GPR -> R, every FPR -> F, every immediate and branch target -> #.
    What survives is the instruction SHAPE.  The two shape sequences are then aligned
    with difflib, so a row that golden has and we have too -- merely somewhere else --
    counts as MOVED, not as wrong.

    shape_miss = rows of golden whose shape is not matched anywhere in the alignment.
                 0 means we emit golden's instruction sequence up to register naming
                 and immediates; the remaining work is then purely allocation.
    Also reported: the true insert/delete residue, i.e. shapes present on one side only
    after cancelling moved rows.  THAT is the honest "what does my source actually get
    wrong" number -- e.g. `golden-only {nop x1} / ours-only {move R,R x1}` says you have
    substituted a spurious move for a scheduler nop and your matching instruction COUNT
    is a coincidence.

USAGE
    python3 tools/shapescore.py <tu> <func> [source.c ...]      # full TU sources
    python3 tools/shapescore.py --blocks <tu> <func> [source.c] # + the diff blocks

    As a library:
        import shapescore
        sc = shapescore.ShapeScorer("game_40490", "func_150130B4")
        miss, mism, info, blocks = sc.score(open("cand.c").read())

NOT A VERDICT.  Like fastscore, this masks things (all immediates!), so shape_miss == 0
does NOT mean matched.  Confirm with the real loop and the ROM gate.

NEGATIVE-CONTROLLED (game_40490/func_150130B4, 2026-08-15) -- and the FIRST attempt at the
control was itself inconclusive, which is the lesson:
  * source still carrying `#pragma GLOBAL_ASM`      -> NOFN, refuses to print a number
    (no-evidence, never a plausible-looking score).
  * function absent from the object                 -> NOFN likewise.
  * FAILED FIRST ATTEMPT: perturbing `desc.unk58 = 0x11` -> `0x12` and `spawn.unk47 = 6` -> `9`
    moved NEITHER metric, because both rows were ALREADY counted as mismatches.  A damage probe
    only proves anything if it lands on a row that currently MATCHES golden.  (Same trap that
    produced a false FAIL in permuter_tu.sh's selftest -- see the cookbook.)
  * word probe on a MATCHING row (`0x70` -> `0x71`, i.e. `li a1,112`): mism 227 -> 228,
    shape_miss correctly UNCHANGED at 22 (immediates are masked by design).
  * shape probe, one statement deleted (`spawn.unk46 = 0;`): shape_miss 22 -> 23, n 406 -> 405,
    and the residue names exactly the missing instruction (`golden-only { sb zero,#(sp) }`).
So the two metrics are independently live and measure different things, as intended.
"""

import difflib
import os
import re
import struct
import subprocess
import sys

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import fastscore  # noqa: E402  (same directory)

REGS = ("at v0 v1 a0 a1 a2 a3 t0 t1 t2 t3 t4 t5 t6 t7 s0 s1 s2 s3 s4 s5 s6 s7 "
        "t8 t9 k0 k1 gp s8 ra").split()
GPR = re.compile(r"\b(" + "|".join(REGS) + r")\b")
FPR = re.compile(r"\$f\d+")
NUM = re.compile(r"-?\b(?:0x)?[0-9a-f]+\b")
RELOC = re.compile(r"^([0-9a-f]{8}) (R_MIPS_\w+)", re.M)


class ShapeScorer(object):
    def __init__(self, tu, func, workdir=None):
        self.fs = fastscore.Scorer(tu, func, workdir)
        self.func = func
        self.gold = self.fs.gold
        self.gshape, self.graw = self._shape(self.gold, "gold")

    def _shape(self, words, tag):
        """Decode raw words through objdump so both sides share one text format."""
        p = os.path.join(self.fs.work, "shape_%s.bin" % tag)
        with open(p, "wb") as fo:
            for w in words:
                fo.write(struct.pack(">I", w))
        out = subprocess.check_output(
            [fastscore.OBJDUMP, "-D", "-b", "binary", "-m", "mips:4300", "-EB", p]
        ).decode()
        raw, shape = [], []
        for _a, _w, rest in re.findall(
                r"^\s*([0-9a-f]+):\t([0-9a-f]{8})\s*(.*)$", out, re.M):
            rest = re.sub(r"<[^>]*>", "", rest).strip()
            rest = re.sub(r"\s+", " ", rest) or "nop"
            raw.append(rest)
            shape.append(NUM.sub("#", FPR.sub("F", GPR.sub("R", rest))))
        if len(shape) != len(words):
            raise SystemExit("shapescore: objdump decoded %d of %d words -- refusing "
                             "to report a number" % (len(shape), len(words)))
        return shape, raw

    def score(self, src, tag="s"):
        """-> (shape_miss, mism, info, blocks).  blocks = [(tag,i1,i2,j1,j2), ...]"""
        ob, err = self.fs._compile(src, tag)
        if err:
            return (10 ** 6, 10 ** 6, err, [])
        dis = subprocess.check_output([fastscore.OBJDUMP, "-d", ob]).decode() + "\n\n"
        m = re.search(r"^([0-9a-f]+) <%s>:\n(.*?)\n\n" % re.escape(self.func),
                      dis, re.S | re.M)
        if not m:
            return (10 ** 6, 10 ** 6, "NOFN (still a #pragma GLOBAL_ASM?)", [])
        body = m.group(2)
        pairs = re.findall(r"^\s*([0-9a-f]+):\t([0-9a-f]{8})", body, re.M)
        addrs = [int(a, 16) for a, _ in pairs]
        words = [int(w, 16) for _, w in pairs]
        rel = subprocess.check_output([fastscore.OBJDUMP, "-r", ob]).decode()
        masks = {int(o, 16): (0x03FFFFFF if t == "R_MIPS_26" else 0xFFFF)
                 for o, t in RELOC.findall(rel)}
        n = min(len(words), len(self.gold))
        mism = sum(1 for i in range(n)
                   if (words[i] & ~masks.get(addrs[i], 0)) !=
                      (self.gold[i] & ~masks.get(addrs[i], 0)))
        mism += abs(len(words) - len(self.gold)) * 10
        oshape, oraw = self._shape(words, tag)
        sm = difflib.SequenceMatcher(None, self.gshape, oshape, autojunk=False)
        eq = sum(b.size for b in sm.get_matching_blocks())
        blocks = [op for op in sm.get_opcodes() if op[0] != "equal"]
        fr = re.search(r"addiu\s+sp,sp,(-\d+)", body)
        info = "frame=%s n=%d/%d" % (fr.group(1) if fr else "leaf",
                                     len(words), len(self.gold))
        self._last = (oshape, oraw)
        return (len(self.gshape) - eq, mism, info, blocks)

    def residue(self, blocks):
        """Shapes present on only ONE side after cancelling moved rows."""
        from collections import Counter
        oshape = self._last[0]
        cg, co = Counter(), Counter()
        for _t, i1, i2, j1, j2 in blocks:
            for i in range(i1, i2):
                cg[self.gshape[i]] += 1
            for j in range(j1, j2):
                co[oshape[j]] += 1
        return cg - co, co - cg


def main(argv):
    show_blocks = "--blocks" in argv
    argv = [a for a in argv if a != "--blocks"]
    if len(argv) < 3:
        raise SystemExit(__doc__)
    tu, func = argv[1], argv[2]
    srcs = argv[3:] or [os.path.join(fastscore.CONKER, "src", tu + ".c")]
    sc = ShapeScorer(tu, func)
    for path in srcs:
        miss, mism, info, blocks = sc.score(open(path).read())
        print("%-40s shape_miss=%-5d mism=%-6d %s"
              % (os.path.basename(path), miss, mism, info))
        if miss >= 10 ** 6:
            continue
        gonly, oonly = sc.residue(blocks)
        print("    TRUE golden-only shapes: %s"
              % (dict(gonly) if gonly else "(none)"))
        print("    TRUE ours-only shapes:   %s"
              % (dict(oonly) if oonly else "(none)"))
        if show_blocks:
            oraw = sc._last[1]
            for t, i1, i2, j1, j2 in blocks:
                print("    %-8s G[%3d:%3d] O[%3d:%3d]  G:%s | O:%s"
                      % (t, i1, i2, j1, j2,
                         " ; ".join(sc.graw[i1:i2])[:60],
                         " ; ".join(oraw[j1:j2])[:60]))


if __name__ == "__main__":
    main(sys.argv)
