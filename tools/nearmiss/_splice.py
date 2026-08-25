#!/usr/bin/env python3
"""Turn a near-miss PARK file into a full TU source, ready for fastscore/structdiff/_dump.

WHY THIS EXISTS
    Every scoring tool in this repo takes a COMPLETE translation unit, because a function's
    bytes depend on the TU it is compiled in (declaration order, what else is live, which
    OPT_FLAGS the Makefile pins). But the park files under tools/nearmiss/ hold only a
    comment header plus the candidate body -- they are a splice, not a TU. Feeding a park
    straight to a scorer produces "Syntax Error" on the first line of the header, which reads
    like a broken candidate rather than a wrong input.

    That mistake has now cost time twice, so the splice lives here instead of being
    re-derived inside each session's throwaway script.

WHAT IT DOES
    Replaces `#pragma GLOBAL_ASM("asm/nonmatchings/<tu>/<func>.s")` in conker/src/<tu>.c with
    the park's contents.  A park that already carries its own #include is assumed to BE a
    full TU and is passed through untouched.

USAGE
    python3 tools/nearmiss/_splice.py <tu> <func> [park.c] [-o out.c]
        park.c defaults to tools/nearmiss/<func>.c; output defaults to stdout.
"""
import io
import os
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.dirname(os.path.dirname(HERE))


def splice(tu, func, park_path):
    park = io.open(park_path, encoding="utf-8", errors="replace").read()
    # SPLICE BY DEFAULT. Guessing the park's kind from its text does not work: parks mention
    # "#include" and "GLOBAL_ASM" inside their own comment headers, so both of those tests
    # misclassified real body splices as whole TUs and compiled them without the rest of their
    # file -- which fails on the first global they do not declare, and looks like a broken
    # candidate rather than a wrong input. Only an explicit STANDALONE TU marker (a handful of
    # parks that really are complete files) suppresses the splice.
    if "STANDALONE TU" in park[:4000]:
        return park
    tu_path = None
    for root, _d, files in os.walk(os.path.join(REPO, "conker", "src")):
        if tu + ".c" in files:
            tu_path = os.path.join(root, tu + ".c")
            break
    if tu_path is None:
        raise SystemExit("no such TU: %s" % tu)
    src = io.open(tu_path, encoding="utf-8", errors="replace").read()
    pragma = '#pragma GLOBAL_ASM("asm/nonmatchings/%s/%s.s")' % (tu, func)
    if pragma not in src:
        raise SystemExit("pragma for %s not found in %s -- already decompiled?" % (func, tu))
    return src.replace(pragma, park)


def main(argv):
    if len(argv) < 2:
        print(__doc__.strip().split("USAGE")[-1].strip())
        return 2
    tu, func = argv[0], argv[1]
    rest = list(argv[2:])
    out = None
    if "-o" in rest:
        k = rest.index("-o")
        out = rest[k + 1]
        del rest[k:k + 2]
    park = rest[0] if rest else os.path.join(HERE, func + ".c")
    text = splice(tu, func, park)
    if out:
        io.open(out, "w", encoding="utf-8", newline="\n").write(text)
        print(out)
    else:
        sys.stdout.write(text)
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
