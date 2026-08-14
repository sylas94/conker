#!/usr/bin/env bash
# Cold-target picker applying EVERY screen this session has established.
#
# BUG FIXED 2026-08-14: the previous version walked asm/nonmatchings/ and assumed a .s file
# meant the function was still stubbed. IT DOES NOT -- .s files are RETAINED after a function
# is decompiled. That fed a whole wave four already-closed functions. The authoritative test
# for "still stubbed" is a live `#pragma GLOBAL_ASM` line in conker/src/<tu>.c.
# PERF FIX: index asm/nonmatchings ONCE instead of globbing per function.
#
# Screens: still stubbed (from src/) | never attempted | mid band | no jump table |
#          no splat interior-symbol run >=3 (trap #6 relocation-naming floor) |
#          no pooled float constant (rodata blocker)
set -uo pipefail
cd "/mnt/c/Users/ssyla/OneDrive/Desktop/conker/conker decomp/conker" || exit 1

python3 - <<'PY'
import re, os, glob

# ---- SCREEN 0: what is ACTUALLY still stubbed, read from src/ pragmas ----
stubbed = {}
for c in glob.glob("src/**/*.c", recursive=True):
    tu = os.path.basename(c)[:-2]
    try: txt = open(c, errors="ignore").read()
    except OSError: continue
    for m in re.finditer(r'#pragma\s+GLOBAL_ASM\("([^"]+)"\)', txt):
        f = os.path.basename(m.group(1))
        if f.endswith(".s"): stubbed[f[:-2]] = tu
print(f"still-stubbed functions (from src/ pragmas): {len(stubbed)}")
print("cross-check with: grep -rc GLOBAL_ASM src/ --include=*.c | awk -F: '{s+=$2} END{print s}'")

# ---- index the asm tree ONCE ----
asmpath = {}
for dirpath, _, files in os.walk("asm/nonmatchings"):
    for fn in files:
        if fn.endswith(".s"): asmpath.setdefault(fn[:-2], os.path.join(dirpath, fn))

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

rows, skipped = [], {"parked":0,"noasm":0,"handwritten":0,"size":0,"jtbl":0,"floor":0,"in_tu_note":0}
# NOTE, deliberately NOT a screen: a prior reconstruction is sometimes parked as a COMMENT BLOCK
# inside the TU rather than in tools/nearmiss/ (func_15167E0C had an 885 note that way, and half a
# wave went into re-deriving it). The obvious test -- "name occurs in src/<tu>.c more than once" --
# was TRIED AND REJECTED: it discards 424 of ~550 candidates, because the second occurrence is
# almost always a forward declaration or a same-file caller. Catching a handful of notes is not
# worth losing three quarters of the pool, so the agent brief tells agents to grep their own TU
# for an existing note instead. Keep it that way unless someone writes a precise test.
for func, tu in stubbed.items():
    if func in parked: skipped["parked"] += 1; continue
    p = asmpath.get(func)
    if not p: skipped["noasm"] += 1; continue
    try: txt = open(p, errors="ignore").read()
    except OSError: continue
    # SCREEN: splat tags hand-written assembly on line 1. Such a function is not compiler
    # output at all -- no prologue, int regs saved into FPU regs, branches into the previous
    # function, interior glabels, trapping `sub`, 64-bit ldl/ldr in a -mips2 build. 29 of these
    # still carry live pragmas, clustered in the 0x150A-0x150D hand-written math region.
    # A whole wave-half was spent discovering this the hard way; screen it here.
    if "Handwritten function" in txt or "handwritten instruction" in txt:
        skipped["handwritten"] += 1; continue
    lines = txt.count("\n")
    if not (200 <= lines <= 330): skipped["size"] += 1; continue
    if re.search(r'\bjr\s+\$?(v[01]|t[0-9]|a[0-3])\b', txt): skipped["jtbl"] += 1; continue
    used = {syms[u] for u in set(re.findall(r'\bD_[0-9A-Fa-f]{8}\b', txt)) if u in syms}
    if len(used) >= 3 and longest_run(sorted(used)) >= 3: skipped["floor"] += 1; continue
    fp   = len(re.findall(r'\b(lwc1|swc1|ldc1|sdc1|mul\.s|add\.s|sub\.s|div\.s|cvt\.|trunc\.)', txt))
    jals = len(set(re.findall(r'jal\s+([A-Za-z_][A-Za-z0-9_]*)', txt)))
    regs = len(re.findall(r'^\.L[0-9A-F]{8}:', txt, re.M))
    pooled = len(re.findall(r'%lo\(D_[0-9A-Fa-f]+\)\(\$?at\)', txt))
    actor  = "ACTOR" if "D_800CC2D0" in txt else ""
    rows.append((jals*2.0 + fp*0.35 + regs*0.6, func, tu, lines, jals, fp, regs, pooled, actor))

rows.sort()
print(f"\nscreened out: {skipped}")
print(f"candidates surviving ALL screens: {len(rows)}\n")
print(f"{'FUNC':<16} {'TU':<14} {'LINES':>5} {'JAL':>4} {'FP':>4} {'REG':>4} {'POOL':>5}  {'COST':>6}  NOTE")
seen = set()
for cost, func, tu, lines, jals, fp, regs, pooled, actor in rows:
    if tu in seen: continue
    seen.add(tu)
    print(f"{func:<16} {tu:<14} {lines:>5} {jals:>4} {fp:>4} {regs:>4} {pooled:>5}  {cost:>6.1f}  {actor}")
    if len(seen) >= 14: break
PY
