#!/usr/bin/env bash
# Refined: the trap needs a RUN of >=3 CONSECUTIVE 4-byte-spaced symbols referenced by ONE
# function (an unrolled array front-peel), not merely two adjacent scalars.
set -uo pipefail
cd "/mnt/c/Users/ssyla/OneDrive/Desktop/conker/conker decomp/conker" || exit 1

python3 - <<'PY'
import re, os
syms = {}
for ln in open("undefined_syms_auto.txt"):
    m = re.match(r'\s*(D_[0-9A-Fa-f]+)\s*=\s*0x([0-9A-Fa-f]+)', ln)
    if m: syms[m.group(1)] = int(m.group(2), 16)

def longest_run(vals):
    """longest chain of values each exactly 4 after the previous"""
    s, best = set(vals), 0
    for v in vals:
        if v - 4 in s: continue          # not a run start
        n, x = 1, v
        while x + 4 in s: n, x = n + 1, x + 4
        best = max(best, n)
    return best

hits = []
for dirpath, _, files in os.walk("asm/nonmatchings"):
    for fn in files:
        if not fn.endswith(".s"): continue
        p = os.path.join(dirpath, fn)
        try: txt = open(p, errors="ignore").read()
        except OSError: continue
        used = {syms[u] for u in set(re.findall(r'\bD_[0-9A-Fa-f]{8}\b', txt)) if u in syms}
        if len(used) < 3: continue
        r = longest_run(sorted(used))
        if r >= 3:
            hits.append((r, fn[:-2], os.path.basename(dirpath), len(txt.splitlines())))

hits.sort(reverse=True)
print(f"stubbed functions referencing a RUN of >=3 consecutive 4-byte-spaced symbols: {len(hits)}")
print(f"(this is the unrolled-array-peel signature; the confirmed case had a run of 4)\n")
print(f"{'RUN':>4}  {'FUNC':<18} {'TU':<16} LINES")
for r, f, tu, lines in hits[:20]:
    print(f"{r:>4}  {f:<18} {tu:<16} {lines}")
import collections
print("\nrun-length distribution:", dict(sorted(collections.Counter(h[0] for h in hits).items())))
PY
