#!/usr/bin/env bash
# iter_match.sh <file> <func>
# Single-function build + object-level diff for the conker decomp matching loop.
# Builds ONLY src/<file>.c.o (no full ROM build) and object-diffs <func> against
# the reference in expected/. Prints "SCORE: N" (0 == byte-perfect match).
#
# Run from anywhere. Safe to run concurrently with OTHER files (never edit a
# .c file another agent owns, and never run a full `make`).
set -uo pipefail
cd "${CONKER_REPO:-$HOME/conker}/conker"
# shellcheck disable=SC1091
source ../.venv/bin/activate 2>/dev/null

file="$1"; func="$2"
obj="build/src/${file}.c.o"

# FORCE a fresh build every time: removing the object defeats make's mtime check,
# which can otherwise treat a same-second .c edit as "up to date" and diff a STALE
# matching .o → a false SCORE: 0 that integrate.py later rejects (wasted bisect).
rm -f "$obj"
berr=$(make "$obj" 2>&1)
if [ $? -ne 0 ] || [ ! -f "$obj" ]; then
  echo "BUILD-FAIL"
  echo "$berr" | grep -iE "error|undefined|syntax" | head -6
  echo "SCORE: 999999"
  exit 0
fi

# --max-lines is NOT cosmetic. It defaults to 1024, which also caps the diff at
# max_lines*4 = 4096 BYTES; anything past that is replaced by a "..." row. score_diff_lines()
# then sees lines_were_truncated, walks back to the end of the last 50-instruction matching
# streak, and STOPS SCORING THERE. So for any function larger than 4096 bytes the default
# command silently reports a small fraction of the real residue. Measured on
# game_1A89B0/func_1517BBAC (5144 bytes): default 791, untruncated 40536 -- an apparent
# "plateau at 791" that was really a function nowhere near matching. Functions <= 4096 bytes
# are unaffected (verified: identical scores, still 0 for the ones that match).
diff=$(python3 ../tools/asm-differ/diff.py -o "$func" --max-lines 4096 2>&1)
score=$(echo "$diff" | grep -oE "CURRENT \(([0-9]+)\)" | grep -oE "[0-9]+" | head -1)
echo "$diff"
echo "SCORE: ${score:-unknown}"
# Track the running-best deterministically: report it to the agent + snapshot the best-C (harvest
# source) and the score-0 source (integrate restore source). Defeats codex over-running past its
# best or mis-reporting it. Per-attempt state is cleared by the orchestrator at round start.
if [ -n "${score:-}" ] && [ "$score" != "unknown" ]; then
  bf="/tmp/best_${func}.score"
  best=$(cat "$bf" 2>/dev/null || echo 999999)
  if [ "$score" -lt "$best" ] 2>/dev/null; then
    echo "$score" > "$bf"; best="$score"
    cp "src/${file}.c" "/tmp/bestc_${func}.c" 2>/dev/null     # best-C so far (for .nearmiss harvest)
  fi
  echo "BEST: $best  (your lowest score so far -- do NOT edit away from it)"
  [ "$score" = "0" ] && cp "src/${file}.c" "/tmp/match_${func}.c" 2>/dev/null   # score-0 = integrate restore
fi
