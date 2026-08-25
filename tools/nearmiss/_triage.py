#!/usr/bin/env python3
"""Score EVERY parked near-miss and rank them, cheapest residue first.

WHY THIS EXISTS
    The backlog was ranked by SIZE (backlog.tsv is sorted by byte count), which is a ranking
    of how much work a function was to write, not of how close it now is to matching. Nothing
    in the tree recorded current scores, so the parks that are nearly finished were invisible.
    Scoring the whole set found one sitting at mism=2 -- 168 of its 170 instructions already
    identical -- that had gone untouched while effort went to functions scoring in the
    hundreds.

    A park is also silently WORTHLESS if it no longer splices: several carry file-local
    typedef or prototype shadows that now clash with declarations their TU has since gained.
    Those show up here as compile failures rather than as good scores, which is the point --
    a park that cannot be built is not a near-miss, and should not be counted as one.

OUTPUT
    A TSV on stdout: score, length delta, frame, tu, func, note. Sorted by score, so the top
    of the list is the work most likely to close.

USAGE
    python3 tools/nearmiss/_triage.py [--out ranked.tsv]
"""
import io
import os
import re
import sys

HERE = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.dirname(os.path.dirname(HERE))
sys.path.insert(0, os.path.join(REPO, "tools"))
import fastscore  # noqa: E402

_index = None


def pragma_index():
    global _index
    if _index is None:
        _index = {}
        for root, _d, files in os.walk(os.path.join(REPO, "conker", "src")):
            for f in files:
                if not f.endswith(".c"):
                    continue
                path = os.path.join(root, f)
                try:
                    txt = io.open(path, encoding="utf-8", errors="replace").read()
                except OSError:
                    continue
                for m in re.finditer(r'GLOBAL_ASM\("asm/nonmatchings/([^/]+)/(\w+)\.s"\)', txt):
                    _index[m.group(2)] = (m.group(1), path)
    return _index


def main(argv):
    out = None
    if "--out" in argv:
        out = argv[argv.index("--out") + 1]
    idx = pragma_index()
    rows = []
    parks = sorted(f for f in os.listdir(HERE) if re.match(r"^func_[0-9A-Fa-f]+\.c$", f))
    for pf in parks:
        func = pf[:-2]
        hit = idx.get(func)
        if hit is None:
            rows.append((10 ** 8, "-", "-", "-", func, "already decompiled (no pragma)"))
            continue
        tu, tupath = hit
        park = io.open(os.path.join(HERE, pf), encoding="utf-8", errors="replace").read()
        src = io.open(tupath, encoding="utf-8", errors="replace").read()
        pragma = '#pragma GLOBAL_ASM("asm/nonmatchings/%s/%s.s")' % (tu, func)
        try:
            sc = fastscore.Scorer(tu, func,
                                  workdir=os.path.expanduser("~/.conker_triage/%s.%s" % (tu, func)))
            mism, info, _ = sc.score(src.replace(pragma, park))
        except Exception as e:
            rows.append((10 ** 7, "-", "-", tu, func, "scorer error: %s" % str(e)[:50]))
            continue
        if mism is None or mism >= 10 ** 6:
            rows.append((10 ** 7, "-", "-", tu, func, "DOES NOT SPLICE: %s" % str(info)[:60]))
            continue
        m = re.search(r"frame=(-?\d+)\s+n=(\d+)/(\d+)", str(info))
        frame, delta = "-", "-"
        if m:
            frame = m.group(1)
            delta = str(int(m.group(2)) - int(m.group(3)))
        rows.append((mism, delta, frame, tu, func, ""))
        print("%-8s %-6s %-8s %-14s %s %s" % (mism, delta, frame, tu, func, ""))
        sys.stdout.flush()

    rows.sort(key=lambda r: r[0])
    text = "score\tlen_delta\tframe\ttu\tfunc\tnote\n"
    for r in rows:
        text += "%s\t%s\t%s\t%s\t%s\t%s\n" % (r[0] if r[0] < 10 ** 7 else "", r[1], r[2],
                                              r[3], r[4], r[5])
    if out:
        io.open(out, "w", encoding="utf-8", newline="\n").write(text)
    print("\n=== RANKED (top 30) ===")
    for r in rows[:30]:
        print("%-8s %-6s %-8s %-14s %s %s" % (r[0] if r[0] < 10 ** 7 else "FAIL",
                                              r[1], r[2], r[3], r[4], r[5]))
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
