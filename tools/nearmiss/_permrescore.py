#!/usr/bin/env python3
"""Re-score EVERY decomp-permuter output inside the real TU, and screen each for forcers.

TWO TRAPS THIS ENCODES, BOTH PAID FOR IN THIS REPO
    1. THE PERMUTER'S OWN output-<n> RANKING IS INVERTED IN-FILE. Confirmed on three separate
       functions now. On func_15040A78 its best-named output re-scored mid-table and its sixth
       was the real best; the same happened on func_1518BD60. The permuter scores the region it
       compiles; what matters is the score inside the actual translation unit. So never trust
       the numbering -- score all of them.
    2. THE BEST-SCORING CANDIDATE IS OFTEN THE ONLY DISHONEST ONE. On func_15040A78 a regex
       screen over 13 outputs flagged exactly one for forcer shapes, and it was the top scorer
       (141): it reused the opcode variable as a zero holder before it held an opcode, and
       laundered a pointer through `&(*p)`. On this kind of residue the permuter buys points
       mainly by laundering registers, so a score with no honesty check attached is worthless.

    A permuter score of 0 is a CANDIDATE, never a match. Confirm with asm-differ -R and gate on
    the ROM sha1.

USAGE
    python3 tools/nearmiss/_permrescore.py <tu> <func> <permuter-dir>
"""
import glob
import io
import os
import re
import subprocess
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.dirname(os.path.dirname(HERE))
sys.path.insert(0, os.path.join(REPO, "tools"))
import fastscore  # noqa: E402

# Shapes that buy bytes without meaning anything. Every one of these has been seen adopted by
# a permuter run on this project and rejected by hand.
FORCERS = [
    (r"&\s*\(\s*\*", "pointer laundering &(*x)"),
    (r"<<\s*\d+\s*\)\s*<<", "split shift (x<<a)<<b"),
    (r"\bvolatile\b", "volatile"),
    (r"\|\s*0x0\b", "|= 0x0 no-op"),
    (r"\+\s*0\b(?!\.)", "+ 0 no-op"),
    (r"\*\s*1\b(?!\.)", "* 1 no-op"),
]


MARKER = "PERMUTER_SPLICE_MARKER"


def extract_region(text):
    """Everything AFTER the splice marker -- exactly what the harness's compile.sh uses.

    An output's source.c is a whole pycparser-expanded file: the base prelude (typedefs and
    declarations) followed by the marker, then the region. Splicing the WHOLE file onto
    tu_head.c duplicates the prelude and nothing compiles -- which reads as "every candidate
    is broken". It also makes the forcer screen fire on every output, because the prelude
    declares vu8/vu16/vu32 and the screen sees `volatile`. Both symptoms came from this one
    mistake, and a screen that flags 100% of candidates is reporting a harness bug.
    """
    for line in text.split("\n"):
        if MARKER in line:
            return text.split(line, 1)[1]
    return text


def main(argv):
    if len(argv) < 3:
        print(__doc__.strip().split("USAGE")[-1].strip())
        return 2
    tu, func, pdir = argv[0], argv[1], argv[2]
    head = io.open(os.path.join(pdir, "tu_head.c"), encoding="utf-8", errors="replace").read()
    tail = io.open(os.path.join(pdir, "tu_tail.c"), encoding="utf-8", errors="replace").read()
    sc = fastscore.Scorer(tu, func,
                          workdir=os.path.expanduser("~/.conker_perm/%s.%s" % (tu, func)))

    base_region = io.open(os.path.join(pdir, "region.c"), encoding="utf-8",
                          errors="replace").read()
    base, binfo, _ = sc.score(head + base_region + tail)
    print("BASE (region.c) in-file: mism=%s  %s" % (base, binfo))
    print()

    rows = []
    for d in sorted(glob.glob(os.path.join(pdir, "output-*"))):
        name = os.path.basename(d)
        src = os.path.join(d, "source.c")
        if not os.path.exists(src):
            continue
        region = extract_region(io.open(src, encoding="utf-8", errors="replace").read())
        text = head + region + tail
        mism, info, _ = sc.score(text)
        flat = re.sub(r"\s+", " ", region)
        hits = [lbl for pat, lbl in FORCERS if re.search(pat, flat)]
        own = ""
        st = os.path.join(d, "score.txt")
        if os.path.exists(st):
            own = io.open(st, encoding="utf-8", errors="replace").read().strip()[:8]
        rows.append((mism if mism is not None else 10 ** 9, name, own, str(info), hits))

    rows.sort()
    print("%-14s %-8s %-8s %-26s %s" % ("output", "in-file", "its own", "info", "FORCERS"))
    for mism, name, own, info, hits in rows:
        mark = ("FORCER: " + ", ".join(hits)) if hits else ""
        better = "  <-- BETTER THAN BASE" if base is not None and mism < base else ""
        print("%-14s %-8s %-8s %-26s %s%s" % (name, mism, own, info[:26], mark, better))

    clean = [r for r in rows if not r[4] and base is not None and r[0] < base]
    print()
    if clean:
        print("CLEAN improvements over base (%s):" % base)
        for mism, name, _o, info, _h in clean:
            print("    %-14s mism=%-6s %s" % (name, mism, info))
        print("Re-derive the IDEA by hand before adopting: a permuter score is a claim about a")
        print("CANDIDATE, never about the idea inside it.")
    else:
        print("NO clean candidate beats the base. Nothing to adopt.")
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
