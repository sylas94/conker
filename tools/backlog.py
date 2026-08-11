#!/usr/bin/env python3
"""Inventory the abandoned near-miss snapshots.

The scratchpad holds ~60 `best*.c` files -- each one is structural reconstruction work
somebody already paid for and then dropped when the score plateaued. They are only an asset
if we know, per file: which function it reconstructs, whether that function is STILL an
unmatched stub, and how many bytes it is worth. Filenames are unreliable (some encode the
function, some encode only a score, some neither), so identify by parsing the C.

Pairs with the TU-aware permuter harness: a validated harness plus a ranked pile of
already-structural seeds is a much cheaper byte source than scouting new functions cold.
"""
import os, re, csv, sys, subprocess, collections

REPO = "/mnt/c/Users/ssyla/OneDrive/Desktop/conker/conker decomp"
CK = os.path.join(REPO, "conker")
SRC = os.path.join(CK, "src")
MAP = os.path.join(CK, "build/conker.us.map")
SCRATCH = os.path.dirname(os.path.abspath(__file__))

# ---- what is still a stub, and how big ----
rows = []
for sec in (".init", ".game", ".debugger"):
    out = subprocess.run([sys.executable, "../tools/progress.py", ".", MAP, sec,
                          "--version", "us"], cwd=CK, capture_output=True, text=True).stdout
    rows += [r for r in csv.DictReader(out.splitlines()) if r.get("version") == "us"]
size = {r["function"]: int(r["length"]) for r in rows}

PRAG = re.compile(r'GLOBAL_ASM\("asm/nonmatchings/([^"]+)/(func_[0-9A-Fa-f]+)\.s"\)')
stub, cfile = {}, {}
for fn in sorted(os.listdir(SRC)):
    if fn.endswith(".c"):
        for m in PRAG.finditer(open(os.path.join(SRC, fn), errors="replace").read()):
            stub[m.group(2)] = fn

# ---- which functions does each snapshot define? ----
# A definition is `func_XXXXXXXX(` at the start of a line-ish position followed eventually by
# a brace; a mere call is `\bfunc_(` mid-expression. Requiring a preceding type token and a
# following `{` before the next `;` separates them reliably enough for ranking.
DEF = re.compile(r'^[A-Za-z_][\w \t\*]*?\b(func_[0-9A-Fa-f]{8})\s*\([^;]*?\)\s*\{', re.M | re.S)
# NB for anyone writing an asm scanner alongside this: spimdisasm INDENTS branch labels
# ("  .L15015AFC:"). An anchored ^\.L matches nothing, so every function reads as branch-free
# and any "regions" metric built on it silently becomes the constant 1. Use ^\s*\.L.
# Verified against game_42DC0/func_15015A38: 7 labels, 9 branches, scored as 1 region.
ANY = re.compile(r'\b(func_[0-9A-Fa-f]{8})\b')

# A "score" in a filename is only believable next to a score-ish word. Bare digits are usually
# the TU's load address (g40490_best207.c, g157840_best1536.c) -- reading those as scores is
# how an inventory oversells itself.
SCORE_TAG = re.compile(r'(?:best|score|nearmiss|near_miss|v|q)_?(\d{1,5})(?![0-9A-Fa-f])', re.I)
# Files that are copies of the ORIGINAL tree file, not reconstructions. They contain the
# pragma, so a body-reference fallback would happily "identify" a function in them.
BACKUP = re.compile(r'pristine|original|\bhead\b|\.bak|_orig|^base\.c$', re.I)

cands, junk = [], []
for fn in sorted(os.listdir(SCRATCH)):
    if not fn.endswith(".c"):
        continue
    p = os.path.join(SCRATCH, fn)
    try:
        txt = open(p, errors="replace").read()
    except OSError:
        continue
    defs = [f for f in dict.fromkeys(DEF.findall(txt)) if f in stub]
    if BACKUP.search(fn) or not defs:
        # still a stub AND still carries its own pragma => it is a backup, not a rebuild
        junk.append(fn)
        continue
    f = max(defs, key=lambda x: size.get(x, 0))
    # if the file still contains this function's own pragma, the definition is dead code
    if re.search(r'GLOBAL_ASM\("[^"]*/%s\.s"\)' % f, txt):
        junk.append(fn)
        continue
    hint = SCORE_TAG.findall(re.sub(r'func_[0-9A-Fa-f]{8}', '', fn))
    cands.append({
        "file": fn, "func": f, "bytes": size.get(f, 0), "tu": stub.get(f, "?"),
        "score_hint": min((int(h) for h in hint), default=None),
        "lines": txt.count("\n"),
    })

# one row per function, keeping the snapshot with the best score hint
best = {}
for c in cands:
    k = c["func"]
    if k not in best or (c["score_hint"] or 10**9) < (best[k]["score_hint"] or 10**9):
        best[k] = c

rank = sorted(best.values(), key=lambda c: -c["bytes"])
tot = sum(c["bytes"] for c in rank)
print(f"ABANDONED RECONSTRUCTIONS (live definition, function still a stub):")
print(f"  {len(cands)} snapshots -> {len(rank)} distinct functions, {tot:,} bytes")
print(f"  rejected {len(junk)} files (backups / pragma-still-present / no live definition)\n")
print(f"{'function':<17}{'bytes':>7}{'hint':>7}{'lines':>7}  {'tu':<20}{'snapshot'}")
for c in rank:
    print(f"{c['func']:<17}{c['bytes']:>7}{str(c['score_hint'] or '-'):>7}{c['lines']:>7}  "
          f"{c['tu']:<20}{c['file']}")

print(f"\ntop 10 = {sum(c['bytes'] for c in rank[:10]):,} B   "
      f"top 25 = {sum(c['bytes'] for c in rank[:25]):,} B")
print("hint = score parsed from a best/score/nearmiss tag in the filename; '-' = unknown.")
print("ALL hints are UNVERIFIED. The re-score pass is what makes this list real.")

import json
json.dump(rank, open(os.path.join(SCRATCH, "backlog.json"), "w"), indent=1)
print(f"\nwrote {os.path.join(SCRATCH, 'backlog.json')}")
