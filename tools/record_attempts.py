#!/usr/bin/env python3
"""Record wave-6 attempts in tools/attempts.tsv.

Without this, the selector re-picks functions that were just tried and bailed -- attempts.tsv
is the only durable memory of "someone looked at this". The wave-6 failures matter especially:
one is hand-written assembly and can NEVER be decompiled, so it must never surface again.
"""
import json, os, sys

TASK = ("/mnt/c/Users/ssyla/AppData/Local/Temp/claude/"
        "c--Users-ssyla-OneDrive-Desktop-conker-conker-decomp/"
        "3a55963f-d160-4a7e-8579-73e12a66c8bc/tasks/wwailuqxk.output")
REPO = "/mnt/c/Users/ssyla/OneDrive/Desktop/conker/conker decomp"
AP = os.path.join(REPO, "tools/attempts.tsv")

d = json.load(open(TASK, encoding="utf-8", errors="replace"))
rows = d["result"]["results"]

attempted, closed = [], []
for r in rows:
    for a in r.get("attempted", []):
        attempted.append(a)
    for c in r.get("closed", []):
        closed.append(c)

print("=== CLOSED (now live, will drop out of the stub list automatically) ===")
for c in closed:
    print(f"  {c['func']:<17}{c['bytes']:>6} B  {c['tu']}")

print("\n=== ATTEMPTED AND NOT CLOSED (must be recorded) ===")
for a in attempted:
    res = (a.get("residual") or "").replace("\n", " ")
    print(f"  {a['func']:<17}best {str(a.get('best_score')):<8}{res[:120]}")

existing = set()
if os.path.exists(AP):
    for line in open(AP, errors="replace"):
        p = line.split("\t")
        if p and p[0].startswith("func_"):
            existing.add(p[0].strip())

# Only record a REAL attempt. best_score -1 is a sentinel meaning "never built, never scored"
# -- two of these ran out of budget with no C written. Recording those would permanently hide
# two never-touched targets from the selector, which is the opposite of what attempts.tsv is
# for. The hand-written bail IS worth recording (it is permanently undecompilable), and it is
# identifiable by its residual rather than by a score.
def real_attempt(a):
    if isinstance(a.get("best_score"), (int, float)) and a["best_score"] >= 0:
        return True
    return "andwritten" in (a.get("residual") or "")

skipped = [a["func"] for a in attempted if not real_attempt(a)]
if skipped:
    print(f"\nNOT recording (never built, still virgin targets): {', '.join(skipped)}")
new = [a for a in attempted if real_attempt(a) and a["func"] not in existing]
if "--write" in sys.argv:
    with open(AP, "a") as fh:
        for a in new:
            sc = a.get("best_score")
            sc = "NA" if sc in (None, -1) else sc
            fh.write(f"{a['func']}\tmidband_w6\t{sc}\tNA\n")
    print(f"\nappended {len(new)} rows to tools/attempts.tsv")
else:
    print(f"\nwould append {len(new)} rows (pass --write)")
