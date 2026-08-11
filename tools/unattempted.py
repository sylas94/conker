#!/usr/bin/env python3
"""Every seam tried today was a BIASED SAMPLE. What does the unbiased pool look like?

  wave 3/4  -- big never-attempted functions. Hard BY SIZE (>=1200 B was the filter).
  wave 5    -- the rescued near-miss backlog. Hard BY SELECTION: these are precisely the
               functions people GAVE UP on, which is why they sit at register ties.

Neither sampled small-to-medium NEVER-ATTEMPTED functions. Prior notes say the historical
pipeline was size-first and swept the small end, so that seam may be exhausted -- but that is
an assumption nobody has re-measured, and it decides where the next wave goes.

Reports the size distribution of what is left, split by whether it was ever attempted.
"""
import os, re, csv, sys, subprocess, collections

REPO = "/mnt/c/Users/ssyla/OneDrive/Desktop/conker/conker decomp"
CK = os.path.join(REPO, "conker")
SRC = os.path.join(CK, "src")
MAP = os.path.join(CK, "build/conker.us.map")

rows = []
for sec in (".init", ".game", ".debugger"):
    out = subprocess.run([sys.executable, "../tools/progress.py", ".", MAP, sec,
                          "--version", "us"], cwd=CK, capture_output=True, text=True).stdout
    rows += [r for r in csv.DictReader(out.splitlines()) if r.get("version") == "us"]
size = {r["function"]: int(r["length"]) for r in rows}

PR = re.compile(r'GLOBAL_ASM\("asm/nonmatchings/[^"]+/(func_[0-9A-Fa-f]+)\.s"\)')
stubs = set()
for root, _, files in os.walk(SRC):
    for fn in files:
        if fn.endswith(".c"):
            stubs |= set(PR.findall(open(os.path.join(root, fn), errors="replace").read()))

tried = set()
ap = os.path.join(REPO, "tools/attempts.tsv")
if os.path.exists(ap):
    for line in open(ap, errors="replace"):
        p = line.split("\t")
        if p and p[0].startswith("func_"):
            tried.add(p[0].strip())
# the rescued backlog counts as attempted too
nm = os.path.join(REPO, "tools/nearmiss")
if os.path.isdir(nm):
    tried |= {f[:-2] for f in os.listdir(nm) if f.startswith("func_") and f.endswith(".c")}

BANDS = [(0, 200), (200, 400), (400, 800), (800, 1200), (1200, 2000), (2000, 4096), (4096, 10**9)]
print(f"{'size band':<16}{'stubs':>7}{'bytes':>10}   {'NEVER attempted':>16}{'bytes':>10}")
tot_n = tot_nb = 0
for lo, hi in BANDS:
    inb = [f for f in stubs if f in size and lo <= size[f] < hi]
    nev = [f for f in inb if f not in tried]
    b = sum(size[f] for f in inb); nb = sum(size[f] for f in nev)
    tot_n += len(nev); tot_nb += nb
    label = f"{lo}-{hi if hi < 10**9 else '+'}"
    print(f"{label:<16}{len(inb):>7}{b:>10,}   {len(nev):>16}{nb:>10,}")

allb = sum(size[f] for f in stubs if f in size)
print(f"\ntotal stubs {len(stubs):,} / {allb:,} B")
print(f"NEVER attempted: {tot_n:,} stubs / {tot_nb:,} B "
      f"({100*tot_nb/allb:.1f}% of remaining bytes)")
print(f"previously attempted and still open: {len(stubs)-tot_n:,} stubs / {allb-tot_nb:,} B")
print("\nThe attempted-and-still-open set is the one with a known hard floor (register ties).")
print("The never-attempted set has UNKNOWN difficulty -- and is where an unbiased sample lives.")
