#!/usr/bin/env python3
"""How big is the single-symbol rodata migration class?

Both functions that closed today closed on a SYSTEMIC fix, not a source-grind:
  func_1510C8A8 -- a one-line conker.us.yaml rodata migration
  func_15121490 -- a CSE/statement-order law
while 15 of 16 hand-grinds died on compiler-internal register ties (see the cookbook's
"loop-invariant ranking tie" bail rule). So the leverage is in systemic unlocks.

func_1510C8A8's unlock was mechanical: its float pool lived in an asm/data/*.rodata.s file
holding exactly ONE symbol, so pointing that block at the TU let compiled C own it. This asks
how many more blocks are like that, and how many stub bytes sit behind them.

A block is a candidate when:
  * its asm/data/*.rodata.s file declares exactly ONE glabel  (nothing else to reproduce)
  * that symbol is referenced from exactly ONE translation unit (no cross-TU ownership)
  * at least one referencing function is still a stub          (there is something to gain)
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
        txt = open(os.path.join(SRC, fn), errors="replace").read()
        for m in PRAG.finditer(txt):
            stub[m.group(2)] = m.group(1)
            tu_of[m.group(2)] = fn

GL = re.compile(r'^glabel\s+(\S+)', re.M)
blocks = {}
for f in sorted(os.listdir(DATA)):
    if not f.endswith(".rodata.s"):
        continue
    blocks[f] = GL.findall(open(os.path.join(DATA, f), errors="replace").read())

single = {f: s for f, s in blocks.items() if len(s) == 1}
print(f"rodata blocks: {len(blocks)} total, {len(single)} hold exactly ONE symbol "
      f"({100*len(single)/max(1,len(blocks)):.0f}%)\n")

refs = collections.defaultdict(set)
sym_re = {s[0]: re.compile(r'\b%s\b' % re.escape(s[0])) for s in single.values()}
for func, sub in stub.items():
    try:
        t = open(os.path.join(NM, sub, func + ".s"), errors="replace").read()
    except OSError:
        continue
    for sym, rx in sym_re.items():
        if rx.search(t):
            refs[sym].add(func)

cand = []
for fname, syms in single.items():
    sym = syms[0]
    users = refs.get(sym, set())
    if not users:
        continue
    tus = {tu_of[f] for f in users}
    if len(tus) != 1:
        continue
    cand.append({
        "block": fname, "addr": fname.split(".")[0], "sym": sym, "tu": tus.pop(),
        "funcs": sorted(users), "bytes": sum(size.get(f, 0) for f in users),
    })

cand.sort(key=lambda c: -c["bytes"])
tot = sum(c["bytes"] for c in cand)
print(f"=== CLEAN MIGRATION CANDIDATES: {len(cand)} blocks, {tot:,} stub bytes behind them ===")
print("(single-symbol block, referenced from exactly one TU, at least one referencing stub)\n")
print(f"{'yaml addr':<12}{'symbol':<18}{'tu':<20}{'bytes':>7}  funcs")
for c in cand[:40]:
    print(f"0x{c['addr']:<10}{c['sym']:<18}{c['tu']:<20}{c['bytes']:>7}  "
          f"{','.join(c['funcs'][:3])}{'...' if len(c['funcs'])>3 else ''}")

print(f"\nthe yaml edit per block:  - [0x<addr>, .rodata, <tu without .c>]")
print("verify per block: the live-C object's .rodata must byte-match the asm file, and the")
print("linker map must show the block coming from build/src/<tu>.c.o")
