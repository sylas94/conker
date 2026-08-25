#!/usr/bin/env python3
"""Why does each non-splicing park fail? Group by the REAL compiler message.

Nearly half the parked near-misses cannot be built at all. That is worth fixing in bulk
rather than one at a time, but only if the failures share causes -- so this collects the
actual first error for each and groups them by shape, with the offending identifier kept
separately so the groups collapse properly.
"""
import io
import os
import re
import sys
import collections

HERE = os.path.dirname(os.path.abspath(__file__))
REPO = os.path.dirname(os.path.dirname(HERE))
sys.path.insert(0, os.path.join(REPO, "tools"))
import fastscore  # noqa: E402
sys.path.insert(0, HERE)
import _splice  # noqa: E402

idx = {}
for root, _d, files in os.walk(os.path.join(REPO, "conker", "src")):
    for f in files:
        if f.endswith(".c"):
            path = os.path.join(root, f)
            txt = io.open(path, encoding="utf-8", errors="replace").read()
            for m in re.finditer(r'GLOBAL_ASM\("asm/nonmatchings/([^/]+)/(\w+)\.s"\)', txt):
                idx[m.group(2)] = (m.group(1), path)

kinds = collections.Counter()
members = collections.defaultdict(list)
for pf in sorted(f for f in os.listdir(HERE) if re.match(r"^func_[0-9A-Fa-f]+\.c$", f)):
    func = pf[:-2]
    if func not in idx:
        continue
    tu, _p = idx[func]
    try:
        src = _splice.splice(tu, func, os.path.join(HERE, pf))
    except SystemExit as e:
        kinds["splice refused: %s" % str(e)[:40]] += 1
        members["splice refused: %s" % str(e)[:40]].append((tu, func))
        continue
    sc = fastscore.Scorer(tu, func, workdir=os.path.expanduser("~/.conker_why/%s.%s" % (tu, func)))
    mism, info, _ = sc.score(src)
    if mism is not None and mism < 10 ** 6:
        continue
    txt = str(info)
    m = re.search(r"line \d+: (.+?)(?:;|$)", txt)
    detail = m.group(1) if m else txt[:70]
    kind = re.sub(r"'[^']*'", "'X'", detail).strip()[:58]
    kinds[kind] += 1
    members[kind].append((tu, func, re.search(r"'([^']*)'", detail).group(1) if "'" in detail else ""))

print("NON-SPLICING PARKS BY REAL CAUSE\n")
for k, n in kinds.most_common():
    print("%3d  %s" % (n, k))
    for row in members[k][:4]:
        print("       %s" % (" ".join(str(x) for x in row)))
    if len(members[k]) > 4:
        print("       ... %d more" % (len(members[k]) - 4))
    print()
