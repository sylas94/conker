#!/usr/bin/env python3
"""Split the 66 single-symbol rodata blocks into REAL blockers and false positives.

The naive count treats every single-symbol block as a migration candidate. That is wrong, and
the distinction is the whole point:

  * A COMPILER CONSTANT POOL (what func_1510C8A8 hit) has no name in the original source. The
    C writes a float literal, IDO emits a private .rodata, conker.ld discards it, and the
    object will not link no matter how perfect the code is. These NEED the yaml migration.
    Signature: .float/.double payload, loaded with lwc1/ldc1 via a %hi/%lo pair.

  * A REAL NAMED GLOBAL (a lookup table, a string, a struct) was declared in the original
    source. Decompiled C just says `extern ...;` and references it -- the block stays owned by
    asm and nothing is blocked. These are FALSE POSITIVES for this class.

Only the first group is an unlock.
"""
import os, re, csv, sys, subprocess, collections

REPO = "/mnt/c/Users/ssyla/OneDrive/Desktop/conker/conker decomp"
CK = os.path.join(REPO, "conker")
SRC, NM, DATA = (os.path.join(CK, "src"), os.path.join(CK, "asm/nonmatchings"),
                 os.path.join(CK, "asm/data"))
MAP = os.path.join(CK, "build/conker.us.map")

rows = []
for sec in (".init", ".game", ".debugger"):
    out = subprocess.run([sys.executable, "../tools/progress.py", ".", MAP, sec,
                          "--version", "us"], cwd=CK, capture_output=True, text=True).stdout
    rows += [r for r in csv.DictReader(out.splitlines()) if r.get("version") == "us"]
size = {r["function"]: int(r["length"]) for r in rows}

PRAG = re.compile(r'GLOBAL_ASM\("asm/nonmatchings/([^"]+)/(func_[0-9A-Fa-f]+)\.s"\)')
stub, tu_of = {}, {}
for fn in sorted(os.listdir(SRC)):
    if fn.endswith(".c"):
        for m in PRAG.finditer(open(os.path.join(SRC, fn), errors="replace").read()):
            stub[m.group(2)] = m.group(1); tu_of[m.group(2)] = fn

GL = re.compile(r'^glabel\s+(\S+)', re.M)
single = {}
for f in sorted(os.listdir(DATA)):
    if f.endswith(".rodata.s"):
        txt = open(os.path.join(DATA, f), errors="replace").read()
        s = GL.findall(txt)
        if len(s) == 1:
            single[f] = (s[0], txt)

sym_re = {v[0]: re.compile(r'\b%s\b' % re.escape(v[0])) for v in single.values()}
refs = collections.defaultdict(set)
asm_of = {}
for func, sub in stub.items():
    try:
        t = open(os.path.join(NM, sub, func + ".s"), errors="replace").read()
    except OSError:
        continue
    asm_of[func] = t
    for sym, rx in sym_re.items():
        if rx.search(t):
            refs[sym].add(func)

FLOATDATA = re.compile(r'^\s*/\*.*?\*/\s*\.(float|double)\b', re.M)
OTHERDATA = re.compile(r'^\s*/\*.*?\*/\s*\.(word|byte|short|asciz|ascii|incbin)\b', re.M)

pools, globals_ = [], []
for fname, (sym, txt) in single.items():
    users = refs.get(sym, set())
    if not users:
        continue
    tus = {tu_of[f] for f in users}
    if len(tus) != 1:
        continue
    nflt, noth = len(FLOATDATA.findall(txt)), len(OTHERDATA.findall(txt))
    # how is it loaded in the referencing asm?
    # NB: build this with concatenation, not %-formatting -- the pattern contains "%lo(",
    # which Python's % operator parses as a format spec and dies with a TypeError.
    fp_rx = re.compile(r'(lwc1|ldc1)\s+\$f\d+,\s*%lo\(' + re.escape(sym) + r'\)')
    fpload = any(fp_rx.search(asm_of[f]) for f in users)
    rec = {"addr": fname.split(".")[0], "sym": sym, "tu": tus.pop(),
           "bytes": sum(size.get(f, 0) for f in users), "funcs": sorted(users),
           "flt": nflt, "oth": noth, "fpload": fpload}
    (pools if (fpload and nflt and not noth) else globals_).append(rec)

pools.sort(key=lambda c: -c["bytes"])
tp = sum(c["bytes"] for c in pools)
tg = sum(c["bytes"] for c in globals_)
print(f"=== REAL BLOCKERS: compiler constant pools ===")
print(f"  {len(pools)} blocks, {tp:,} stub bytes behind them")
print(f"  (float/double payload AND loaded via lwc1/ldc1 %lo -- no name in the original source,")
print(f"   so live-C emits a private .rodata that conker.ld discards and the object will NOT link)\n")
print(f"{'yaml addr':<12}{'symbol':<18}{'tu':<20}{'bytes':>7}  funcs")
for c in pools:
    print(f"0x{c['addr']:<10}{c['sym']:<18}{c['tu']:<20}{c['bytes']:>7}  "
          f"{','.join(c['funcs'][:3])}{'...' if len(c['funcs'])>3 else ''}")

print(f"\n=== FALSE POSITIVES: real named globals ===")
print(f"  {len(globals_)} blocks, {tg:,} bytes -- decompiled C declares these `extern` and")
print(f"  references them; the block stays owned by asm and nothing is blocked.")
print(f"  (sample: {', '.join(c['sym'] for c in globals_[:6])})")
