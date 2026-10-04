# Usage: python3 tools/nearmiss/_sweep.py <tu> <func> <list.json>   list.json = [[label, full_tu_source], ...]
import sys, os, json
sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
import fastscore
tu, fn, listfile = sys.argv[1], sys.argv[2], sys.argv[3]
sc = fastscore.Scorer(tu, fn, workdir=os.path.expanduser("~/.conker_sweep/%s.%s" % (tu, fn)))
items = json.load(open(listfile))   # [[label, source], ...]
res = []
for label, src in items:
    mism, info, rows = sc.score(src)
    res.append((mism, label, info))
    print("%-8d %-60s %s" % (mism, label, info)); sys.stdout.flush()
res.sort()
print("=== BEST ===")
for m, l, i in res[:12]:
    print("%-8d %-60s %s" % (m, l, i))
