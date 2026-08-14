#!/usr/bin/env bash
# Cold-target picker applying EVERY screen this session has established.
#
# BUG FIXED 2026-08-14: the previous version walked asm/nonmatchings/ and assumed a .s file
# meant the function was still stubbed. IT DOES NOT -- .s files are RETAINED after a function
# is decompiled. That fed a whole wave four already-closed functions. The authoritative test
# for "still stubbed" is a live `#pragma GLOBAL_ASM` line in conker/src/<tu>.c, so that is now
# the FIRST screen and it is built from src/, not from the asm directory.
#
# Screens: still stubbed (from src/) | never attempted (no parked file) | mid band |
#          no jump table | no splat interior-symbol run >=3 (trap #6 score floor) |
#          no pooled float constant (rodata blocker)
# Ranked by tractability: few distinct callees, few fp ops, few branch labels.
set -uo pipefail
cd "/mnt/c/Users/ssyla/OneDrive/Desktop/conker/conker decomp/conker" || exit 1

python3 - <<'PY'
import re, os, glob

# ---- SCREEN 0: what is ACTUALLY still stubbed, read from src/ ----
stubbed = {}          # func -> tu
for c in glob.glob("src/**/*.c", recursive=True):
    tu = os.path.basename(c)[:-2]
    try: txt = open(c, errors="ignore").read()
    except OSError: continue
    for m in re.finditer(r'#pragma\s+GLOBAL_ASM\("([^"]+)"\)', txt):
        f = os.path.basename(m.group(1))
        if f.endswith(".s"): stubbed[f[:-2]] = tu
print(f"still-stubbed functions (from src/ pragmas): {len(stubbed)}")

syms = {}
for ln in open("undefined_syms_auto.txt"):
    m = re.match(r'\s*(D_[0-9A-Fa-f]+)\s*=\s*0x([0-9A-Fa-f]+)', ln)
    if m: syms[m.group(1)] = int(m.group(2), 16)

def longest_run(vals):
    s, best = set(vals), 0
    for v in vals:
        if v - 4 in s: continue
        n, x = 1, v
        while x + 4 in s: n, x = n + 1, x + 4
        best = max(best, n)
    return best

parked = {f[:-2] for f in os.listdir("../tools/nearmiss") if f.endswith(".c")}

rows = []
for func, tu in stubbed.items():
    if func in parked: continue
    cands = glob.glob(f"asm/nonmatchings/**/{func}.s", recursive=True)
    if not cands: continue
    try: txt = open(cands[0], errors="ignore").read()
    except OSError: continue
    lines = txt.count("\n")
    if not (200 <= lines <= 330): continue
    if re.search(r'\bjr\s+\$?(v[01]|t[0-9]|a[0-3])\b', txt): continue        # jump table
    used = {syms[u] for u in set(re.findall(r'\bD_[0-9A-Fa-f]{8}\b', txt)) if u in syms}
    if len(used) >= 3 and longest_run(sorted(used)) >= 3: continue           # trap #6 floor
    fp   = len(re.findall(r'\b(lwc1|swc1|ldc1|sdc1|mul\.s|add\.s|sub\.s|div\.s|cvt\.|trunc\.)', txt))
    jals = len(set(re.findall(r'jal\s+([A-Za-z_][A-Za-z0-9_]*)', txt)))
    regs = len(re.findall(r'^\.L[0-9A-F]{8}:', txt, re.M))
    pooled = len(re.findall(r'%lo\(D_[0-9A-Fa-f]+\)\(\$?at\)', txt))
    actor  = "ACTOR" if "D_800CC2D0" in txt else ""
    rows.append((jals*2.0 + fp*0.35 + regs*0.6, func, tu, lines, jals, fp, regs, pooled, actor))

rows.sort()
print(f"candidates surviving ALL screens: {len(rows)}\n")
print(f"{'FUNC':<16} {'TU':<14} {'LINES':>5} {'JAL':>4} {'FP':>4} {'REG':>4} {'POOL':>5}  {'COST':>6}  NOTE")
seen = set()
for cost, func, tu, lines, jals, fp, regs, pooled, actor in rows:
    if tu in seen: continue
    seen.add(tu)
    print(f"{func:<16} {tu:<14} {lines:>5} {jals:>4} {fp:>4} {regs:>4} {pooled:>5}  {cost:>6.1f}  {actor}")
    if len(seen) >= 14: break
PY
