#!/usr/bin/env bash
# Re-score every abandoned reconstruction in backlog.json.
#
# backlog.py finds 72 still-unmatched functions that already have a live reconstruction on
# disk. Its "hint" column is parsed from filenames and is NOT evidence: the snapshots were
# written across many sessions, headers have drifted since, and some hints are TU addresses
# that survived the filter. This turns that speculative list into measured scores.
#
# Output: rescore.tsv  (func, bytes, tu, snapshot, hint, measured, status)
# Sorted by measured score, it is the work queue -- lowest scores are the cheapest bytes
# left in the project.
#
# SAFETY. This splices into the REAL tree and runs the REAL make, because that is the only
# thing that reproduces IDO's TU-context-dependent codegen. Therefore:
#   * it REFUSES to run while an agent wave is live (they share build/ and would corrupt
#     each other -- the same hazard the agents are warned about);
#   * it snapshots the target .c and restores it after every candidate, pass or fail;
#   * it verifies `git status --short` is clean for that file before moving on, and ABORTS
#     the whole run if a restore ever fails, rather than leaving the tree dirty.
set -u

R="/mnt/c/Users/ssyla/OneDrive/Desktop/conker/conker decomp"
S="/mnt/c/Users/ssyla/AppData/Local/Temp/claude/c--Users-ssyla-OneDrive-Desktop-conker-conker-decomp/3a55963f-d160-4a7e-8579-73e12a66c8bc/scratchpad"
W="/mnt/c/Users/ssyla/.claude/projects/c--Users-ssyla-OneDrive-Desktop-conker-conker-decomp/3a55963f-d160-4a7e-8579-73e12a66c8bc/subagents/workflows"
OUT="$S/rescore.tsv"
LIMIT="${1:-999}"

# ---- refuse to race a live wave ----
now=$(date +%s)
for d in "$W"/wf_*; do
  j="$d/journal.jsonl"; [ -f "$j" ] || continue
  # grep -c PRINTS 0 and EXITS 1 on no match, so `|| echo 0` yields the string "0\n0"
  # and every later [ -eq ] blows up. Take the output, ignore the status.
  st=$(grep -c '"type":"started"' "$j" 2>/dev/null); st=${st:-0}
  rs=$(grep -c '"type":"result"' "$j" 2>/dev/null); rs=${rs:-0}
  [ "$st" -eq "$rs" ] && continue
  last=$(ls -t "$d"/agent-*.jsonl 2>/dev/null | head -1); [ -n "$last" ] || continue
  if [ $(( now - $(stat -c %Y "$last") )) -lt 600 ]; then
    echo "REFUSING TO RUN: wave $(basename "$d") is live (agent transcript touched"
    echo "$(( now - $(stat -c %Y "$last") ))s ago). It shares conker/build/ with this script."
    exit 3
  fi
done

cd "$R/conker" || exit 1
if [ -n "$(git status --short -- src/ 2>/dev/null)" ]; then
  echo "REFUSING TO RUN: conker/src is already dirty. Commit or restore it first:"
  git status --short -- src/
  exit 3
fi

printf 'func\tbytes\ttu\tsnapshot\thint\tmeasured\tstatus\n' > "$OUT"

python3 - "$LIMIT" <<'PY' | while IFS=$'\t' read -r func bytes tu snap hint; do
import json, sys, os
S = "/mnt/c/Users/ssyla/AppData/Local/Temp/claude/c--Users-ssyla-OneDrive-Desktop-conker-conker-decomp/3a55963f-d160-4a7e-8579-73e12a66c8bc/scratchpad"
rows = json.load(open(os.path.join(S, "backlog.json")))
# cheapest-looking first: a known low hint is the best bet, unknowns after, by size
rows.sort(key=lambda r: (r["score_hint"] is None, r["score_hint"] or 0, -r["bytes"]))
for r in rows[:int(sys.argv[1])]:
    print("\t".join([r["func"], str(r["bytes"]), r["tu"], r["file"], str(r["score_hint"] or "-")]))
PY

  src="src/$tu"
  [ -f "$src" ] || { printf '%s\t%s\t%s\t%s\t%s\t-\tNO_TU\n' "$func" "$bytes" "$tu" "$snap" "$hint" >> "$OUT"; continue; }
  cp "$src" "/tmp/rescore_orig.c"

  # Splice. Two snapshot shapes exist: a FULL TU (carries other functions' pragmas) and a
  # BODY fragment. A full TU is used as-is; a fragment replaces the target's pragma line.
  if grep -q 'GLOBAL_ASM' "$S/$snap" && [ "$(grep -c 'GLOBAL_ASM' "$S/$snap")" -gt 1 ]; then
    cp "$S/$snap" "$src"
  else
    python3 - "$src" "$S/$snap" "$func" <<'PY'
import re, sys
src, snap, func = sys.argv[1], sys.argv[2], sys.argv[3]
tu = open(src, errors="replace").read()
body = open(snap, errors="replace").read()
pat = re.compile(r'^[^\n]*GLOBAL_ASM\("[^"]*/%s\.s"\)[^\n]*\n' % re.escape(func), re.M)
if not pat.search(tu):
    sys.exit(9)
open(src, "w").write(pat.sub(lambda m: body + "\n", tu, count=1))
PY
    if [ $? -eq 9 ]; then
      cp /tmp/rescore_orig.c "$src"
      printf '%s\t%s\t%s\t%s\t%s\t-\tNO_PRAGMA\n' "$func" "$bytes" "$tu" "$snap" "$hint" >> "$OUT"; continue
    fi
  fi

  # build + score; a compile failure is a real answer (the snapshot has bit-rotted)
  if ! make -s "build/src/$tu.o" VERSION=us >/tmp/rescore_build.log 2>&1; then
    status=BUILD_FAIL; measured="-"
  else
    measured=$(python3 ../tools/asm-differ/diff.py -o "$func" -R 2>/tmp/rescore_diff.log \
               | grep -oE '(CURRENT|SCORE:?) *\(?[0-9]+\)?' | grep -oE '[0-9]+' | tail -1)
    if [ -z "$measured" ]; then status=NO_SCORE; measured="-"; else status=OK; fi
  fi

  cp /tmp/rescore_orig.c "$src"
  make -s "build/src/$tu.o" VERSION=us >/dev/null 2>&1
  if [ -n "$(git status --short -- "$src")" ]; then
    echo "ABORT: failed to restore $src -- tree is dirty, stopping before it spreads."
    git status --short -- "$src"; exit 4
  fi

  printf '%s\t%s\t%s\t%s\t%s\t%s\t%s\n' "$func" "$bytes" "$tu" "$snap" "$hint" "$measured" "$status" >> "$OUT"
  printf '  %-17s %6s B  hint %-6s measured %-8s %s\n' "$func" "$bytes" "$hint" "$measured" "$status"
done

echo
echo "=== wrote $OUT ==="
sort -t$'\t' -k6 -n "$OUT" | head -30
echo
echo "final tree check:"; git status --short -- src/ || true
