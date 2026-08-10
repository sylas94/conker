#!/usr/bin/env bash
# Live DECOMP progress tracker.
#
# wf.sh answers "is an agent alive". This answers the question that actually matters:
# what score has each function reached, and is it still falling? asm-differ prints
# "CURRENT (N)" / "SCORE: N" into the agent transcript on every probe, so the transcript
# is a running log of the match attempt. Lower is better; 0 is byte-identical.
#
#   track.sh        one snapshot
#   track.sh -w     refresh every 30s until the wave finishes
#
# The workflow directory is per-SESSION, so hardcoding one session id makes this tool die the
# next time the session rolls. Search every session under the project and keep whichever has
# the most recently written agent transcript.
P="/mnt/c/Users/ssyla/.claude/projects/c--Users-ssyla-OneDrive-Desktop-conker-conker-decomp"
W="${TRACK_WF_DIR:-}"
if [ -z "$W" ]; then
  W=$(ls -td "$P"/*/subagents/workflows 2>/dev/null \
      | while read -r d; do
          n=$(ls -t "$d"/wf_*/agent-*.jsonl 2>/dev/null | head -1)
          [ -n "$n" ] && echo "$(stat -c %Y "$n") $d"
        done | sort -rn | head -1 | cut -d' ' -f2-)
fi
[ -n "$W" ] && [ -d "$W" ] || { echo "no workflow dir found under $P"; exit 0; }
FRESH=600
WATCH=0; for a in "$@"; do [ "$a" = "-w" ] && WATCH=1; done

snap() {
  now=$(date +%s); live=0
  echo "════════ $(date '+%H:%M:%S')  decomp progress ════════"
  for d in "$W"/wf_*; do
    j="$d/journal.jsonl"; [ -f "$j" ] || continue
    st=$(grep -c '"type":"started"' "$j"); rs=$(grep -c '"type":"result"' "$j")
    [ "$st" -eq "$rs" ] && continue
    last=$(ls -t "$d"/agent-*.jsonl 2>/dev/null | head -1); [ -n "$last" ] || continue
    [ $(( now - $(stat -c %Y "$last") )) -lt "$FRESH" ] || continue
    live=$((live+1))
    echo "  ${d##*/}   agents done ${rs}/${st}"
    for a in "$d"/agent-*.jsonl; do
      id=$(basename "$a" .jsonl); id=${id#agent-}
      [ "$(grep -c "\"agentId\":\"$id\"" "$j")" -gt 1 ] && continue   # finished
      age=$(( now - $(stat -c %Y "$a") ))
      # Which function is this agent on? Two wrong ways: the FIRST func_ in the
      # transcript is an example cited in the shared prompt, and the MOST FREQUENT is
      # usually a callee the scout is reading about. The prompt's own task line is the
      # only unambiguous marker.
      # -i because prompts vary between "TASK: MATCH" and "TASK: match"
      fn=$(grep -iom1 'TASK: \(SCOUT\|MATCH\) \**func_[0-9A-Fa-f]\{8\}' "$a" \
           | grep -o 'func_[0-9A-Fa-f]\{8\}')
      # Fallback for agents whose task line uses different wording (an analysis or
      # mining pass). The scoring command always names the target, so use that.
      [ -z "$fn" ] && fn=$(grep -om1 'diff\.py -o func_[0-9A-Fa-f]\{8\}' "$a" \
                           | grep -o 'func_[0-9A-Fa-f]\{8\}')
      # every score this agent has printed, in order
      scores=$(grep -o 'CURRENT ([0-9]\+)\|SCORE: [0-9]\+' "$a" 2>/dev/null \
               | grep -o '[0-9]\+' | tail -40)
      n=$(echo "$scores" | grep -c . )
      cur=$(echo "$scores" | tail -1)
      # 'best' must IGNORE zeros. Agents open with a baseline probe while the pragma is still
      # in place, which diffs the golden asm against itself and prints 0; letting that into
      # the minimum makes every later real improvement read as "plateau?".
      best=$(echo "$scores" | grep -v '^0$' | sort -n | head -1)
      [ -z "$best" ] && best="$cur"
      first=$(echo "$scores" | grep -v '^0$' | head -1)
      [ -z "$first" ] && first=$(echo "$scores" | head -1)
      # 'idle' is seconds since the transcript was last written. It inflates during any
      # long tool call -- a build writes nothing until it returns -- so only flag the
      # genuinely suspicious case rather than every pause.
      note=""; [ "$age" -gt 900 ] && note="  <-- STALLED?"
      if [ "$n" -ge 2 ]; then
        # a trend needs TWO probes; with one, best==now is trivially true and "improving"
        # would be a lie
        [ "$cur" -le "$best" ] && trend="improving" || trend="plateau?"
        # NEVER call it matched off a historical 0. Agents open with a baseline probe while
        # the #pragma GLOBAL_ASM is still in place -- that assembles the GOLDEN asm and diffs
        # it against itself, printing 0. Only the CURRENT score can mean anything, and even a
        # current 0 has to be confirmed against the pragma state before anyone believes it.
        [ "$cur" = "0" ] && trend="ZERO - verify pragma is gone"
        printf "    %-14s %-3s probes  first %-7s best %-7s now %-7s  %s  (idle %ss)%s\n" \
               "${fn:-?}" "$n" "$first" "$best" "$cur" "$trend" "$age" "$note"
      elif [ "$n" -eq 1 ]; then
        printf "    %-14s 1   probe   baseline %-9s (no trend yet)      (idle %ss)%s\n" \
               "${fn:-?}" "$first" "$age" "$note"
      else
        printf "    %-14s scouting/reading, no probe yet            (idle %ss)\n" "${fn:-?}" "$age"
      fi
    done
  done
  [ "$live" -eq 0 ] && echo "  (no wave running)"
  return $live
}

if [ "$WATCH" = 1 ]; then
  while true; do snap; [ $? -eq 0 ] && { echo "wave finished."; break; }; sleep 30; done
else
  snap || true
fi
exit 0
