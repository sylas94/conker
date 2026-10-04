# Usage: python3 tools/nearmiss/_dump.py <tu> <func> <candidate.c>
# Prints golden vs ours side by side, X-marking every differing word.
import sys, os, subprocess, re
sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..'))
import fastscore
tu, fn, path = sys.argv[1], sys.argv[2], sys.argv[3]
sc = fastscore.Scorer(tu, fn)
mism, info, rows = sc.score(open(path).read())
print("mism", mism, info)
ob = os.path.join(sc.work, "t.o")
dis = subprocess.check_output([fastscore.OBJDUMP, "-d", ob]).decode() + "\n\n"
m = re.search(r"^([0-9a-f]+) <%s>:\n(.*?)\n\n" % re.escape(fn), dis, re.S | re.M)
ours = []
for line in m.group(2).splitlines():
    mm = re.match(r"^\s*([0-9a-f]+):\t([0-9a-f]{8})\s+(.*)$", line)
    if mm: ours.append(mm.group(3).strip())
gs = os.path.join(fastscore.CONKER, "asm", "nonmatchings", tu, fn + ".s")
gold = []
for line in open(gs).read().splitlines():
    mm = re.search(r"\*/\s+(.*)$", line)
    if mm: gold.append(mm.group(1).strip())
bad = set(r[0] for r in rows)
for i in range(max(len(ours), len(gold))):
    o = ours[i] if i < len(ours) else "---"
    g = gold[i] if i < len(gold) else "---"
    print("%s %3d  %-34s | %s" % ("X" if i in bad or o=="---" or g=="---" else " ", i, o, g))
