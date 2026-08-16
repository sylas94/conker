#!/usr/bin/env python3
"""Pick targets from the untested middle: 800-1200 B, never attempted, no jtbl.

Rationale (measured 2026-08-10): 73.1% of remaining bytes have never been attempted, and the
800-1200 band is 82% untouched because the historical pipeline was size-first and stopped
around 800 B while this session's big-game filter started at 1200 B. Nobody has sampled it.

Unlike the rescued near-miss backlog, this pool is NOT selected for hardness -- those seeds
sit at register ties precisely because people abandoned them.

Ranks by tractability, not by bytes: fewer distinct callees (each is a prototype that must be
exactly right), fewer float ops, fewer branch regions, smaller frame. Bytes are nearly constant
across the band, so tractability is the only thing worth optimising.
"""
import os, re, csv, sys, subprocess, json

REPO = "/mnt/c/Users/ssyla/OneDrive/Desktop/conker/conker decomp"
CK = os.path.join(REPO, "conker")
SRC, NM = os.path.join(CK, "src"), os.path.join(CK, "asm/nonmatchings")
MAP = os.path.join(CK, "build/conker.us.map")
LO, HI = 800, 1200

rows = []
for sec in (".init", ".game", ".debugger"):
    out = subprocess.run([sys.executable, "../tools/progress.py", ".", MAP, sec,
                          "--version", "us"], cwd=CK, capture_output=True, text=True).stdout
    rows += [r for r in csv.DictReader(out.splitlines()) if r.get("version") == "us"]
size = {r["function"]: int(r["length"]) for r in rows}

PRAG = re.compile(r'GLOBAL_ASM\("asm/nonmatchings/([^"]+)/(func_[0-9A-Fa-f]+)\.s"\)')
sub, cfile = {}, {}
for root, _, files in os.walk(SRC):
    for fn in sorted(files):
        if fn.endswith(".c"):
            rel = os.path.relpath(os.path.join(root, fn), SRC)
            for m in PRAG.finditer(open(os.path.join(root, fn), errors="replace").read()):
                sub[m.group(2)] = m.group(1); cfile[m.group(2)] = rel

tried = set()
ap = os.path.join(REPO, "tools/attempts.tsv")
if os.path.exists(ap):
    for line in open(ap, errors="replace"):
        p = line.split("\t")
        if p and p[0].startswith("func_"):
            tried.add(p[0].strip())
nm = os.path.join(REPO, "tools/nearmiss")
if os.path.isdir(nm):
    tried |= {f[:-2] for f in os.listdir(nm) if f.startswith("func_") and f.endswith(".c")}

# spimdisasm INDENTS branch labels ("  .L15015AFC:"), so an anchored ^\.L never matches and
# every function reads as a single region. Verified against game_42DC0/func_15015A38, which
# has 7 labels and 9 branches but scored "1 region" under the anchored pattern.
LBL   = re.compile(r'^\s*\.L[0-9A-Fa-f]{8}:', re.M)
JAL   = re.compile(r'\bjal\s+(\w+)')
FRAME = re.compile(r'addiu\s+\$sp,\s*\$sp,\s*-(0x[0-9A-Fa-f]+|\d+)')
FLT   = re.compile(r'^\s*/\*.*?\*/\s+\w+\.[sd]\b', re.M)
LWC   = re.compile(r'\b(lwc1|ldc1)\s+\$f\d+,\s*%lo\((\w+)\)')
# Instructions IDO cannot emit at -mips2 -o32. Their presence proves the function is
# hand-written assembly regardless of whether spimdisasm labelled it.
MIPS3 = re.compile(r'\*/\s+(dmtc1|dmfc1|dadd|daddu|daddi|daddiu|dsub|dsubu|dsll|dsll32|'
                   r'dsrl|dsrl32|dsra|dsra32|dmult|dmultu|ddiv|ddivu|ld|sd|ldl|ldr|sdl|sdr|'
                   r'lld|scd)\b')

# --- which symbols are actually COMPILER LITERAL POOLS? ---------------------------------
# `lwc1 $fN, %lo(SYM)` is how IDO loads BOTH its own constant pool AND an ordinary float
# global, so the instruction alone cannot tell them apart -- func_151EDBDC was flagged [POOL]
# on that basis and needed no migration at all, because D_8008FE1C/D_8008FE20 are real globals
# sitting in a 42-glabel hand-authored block. The discriminator is the DATA: a compiler pool is
# a block holding exactly one glabel whose payload is .float/.double.
DATA = os.path.join(CK, "asm/data")
GL = re.compile(r'^glabel\s+(\S+)', re.M)
FLT_DATA = re.compile(r'^\s*/\*.*?\*/\s*\.(float|double)\b', re.M)
OTHER_DATA = re.compile(r'^\s*/\*.*?\*/\s*\.(word|byte|short|asciz|ascii|incbin)\b', re.M)
pool_syms = set()
if os.path.isdir(DATA):
    for fn in os.listdir(DATA):
        if not fn.endswith(".rodata.s"):
            continue
        txt = open(os.path.join(DATA, fn), errors="replace").read()
        syms = GL.findall(txt)
        if len(syms) == 1 and FLT_DATA.search(txt) and not OTHER_DATA.search(txt):
            pool_syms.add(syms[0])

cand = []
for f, s in sub.items():
    if f not in size or not (LO <= size[f] < HI) or f in tried:
        continue
    try:
        t = open(os.path.join(NM, s, f + ".s"), errors="replace").read()
    except OSError:
        continue
    if "jtbl_" in t:
        continue
    # HAND-WRITTEN ASSEMBLY IS NOT DECOMPILABLE and it ranks FIRST under any tractability
    # metric -- it has no jal (0 callees), often no stack frame, and few branches, which is
    # exactly what "tractable" was measuring. func_150A3FC4 topped the first list this way and
    # cost an agent a slot before it read the header. spimdisasm marks these explicitly.
    if "Handwritten function" in t or "handwritten instruction" in t:
        continue
    # ...but that comment is NOT always present. func_150A5378 carries no marker at all and is
    # still undecompilable: it contains 11 `dmtc1`, a 64-bit MIPS III move that IDO simply
    # cannot emit at -mips2 -o32. Detecting the ISA level is a far more reliable test than a
    # comment, so reject anything using an instruction outside the project's target ISA.
    # (ldc1/sdc1 are MIPS II and legitimate -- do not add them.)
    if MIPS3.search(t):
        continue
    callees = JAL.findall(t)
    fr = FRAME.search(t)
    cand.append({
        "func": f, "file": cfile[f], "bytes": size[f],
        "regions": len(LBL.findall(t)) + 1,
        "callees": len(set(callees)), "calls": len(callees),
        "frame": int(fr.group(1), 0) if fr else 0,
        "flt": len(FLT.findall(t)),
        # only a single-glabel float block counts; a real global needs no migration
        "pool": any(m.group(2) in pool_syms for m in LWC.finditer(t)),
    })

# tractability: penalise prototypes to get right, float density, branchiness, frame size
for c in cand:
    c["cost"] = (c["callees"] * 3.0 + c["flt"] * 0.35 + c["regions"] * 0.6
                 + c["frame"] / 64.0)
cand.sort(key=lambda c: c["cost"])

print(f"UNTESTED MIDDLE: {len(cand)} functions, {sum(c['bytes'] for c in cand):,} B "
      f"({LO}-{HI} B, never attempted, no jtbl)\n")
print(f"{'function':<17}{'file':<20}{'bytes':>6}{'cost':>7}{'callees':>8}{'flt':>5}"
      f"{'regions':>8}{'frame':>7}  pool")
for c in cand[:30]:
    print(f"{c['func']:<17}{c['file']:<20}{c['bytes']:>6}{c['cost']:>7.1f}{c['callees']:>8}"
          f"{c['flt']:>5}{c['regions']:>8}{c['frame']:>#7x}  {'YES' if c['pool'] else ''}")

seen, picks = set(), []
for c in cand:
    if c["file"] in seen:
        continue
    seen.add(c["file"]); picks.append(c)
    if len(picks) == 10:
        break
print(f"\n=== WAVE PICKS (distinct TUs) — {sum(p['bytes'] for p in picks):,} B ===")
for p in picks:
    print(f"  {p['func']:<17}{p['file']:<20}{p['bytes']:>5} B  cost {p['cost']:>5.1f}  "
          f"{p['callees']} callees, {p['flt']} fp, {p['regions']} regions"
          f"{'  [needs rodata migration]' if p['pool'] else ''}")
json.dump(picks, open("/tmp/midband.json", "w"), indent=1)
