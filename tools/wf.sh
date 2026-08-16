#!/usr/bin/env bash
# Live workflow tracker.
#
# A workflow whose journal has fewer results than starts is NOT necessarily running --
# agents killed by a session limit leave exactly that signature forever. The only
# reliable liveness signal is whether an agent transcript was written to RECENTLY, so
# that is what this uses (default: touched in the last 5 minutes).
#
#   wf.sh            one snapshot
#   wf.sh -w         refresh every 20s until nothing is live
#   wf.sh -a         include stale/dead runs

W="/mnt/c/Users/ssyla/.claude/projects/c--Users-ssyla-OneDrive-Desktop-conker-conker-decomp/3a55963f-d160-4a7e-8579-73e12a66c8bc/subagents/workflows"
S="/mnt/c/Users/ssyla/AppData/Local/Temp/claude/c--Users-ssyla-OneDrive-Desktop-conker-conker-decomp/3a55963f-d160-4a7e-8579-73e12a66c8bc/scratchpad"
FRESH=300
SHOW_ALL=0; WATCH=0
for a in "$@"; do [ "$a" = "-a" ] && SHOW_ALL=1; [ "$a" = "-w" ] && WATCH=1; done

snap() {
  now=$(date +%s); live=0
  printf '%s\n' "──────── $(date '+%H:%M:%S') ────────"
  for d in "$W"/wf_*; do
    j="$d/journal.jsonl"; [ -f "$j" ] || continue
    st=$(grep -c '"type":"started"' "$j"); rs=$(grep -c '"type":"result"' "$j")
    last=$(ls -t "$d"/agent-*.jsonl 2>/dev/null | head -1); [ -n "$last" ] || continue
    age=$(( now - $(stat -c %Y "$last") ))
    if [ "$st" -eq "$rs" ]; then state="done"
    elif [ "$age" -lt "$FRESH" ]; then state="LIVE"; live=$((live+1))
    else state="stale"; fi
    [ "$SHOW_ALL" = 0 ] && [ "$state" != "LIVE" ] && continue
    # name the workflow from its saved script, and show which agents are still out
    sp=$(ls -t /mnt/c/Users/ssyla/.claude/projects/*/*/workflows/scripts/*.js 2>/dev/null | head -50)
    printf "  %-5s %-20s agents %2s/%-2s  idle %3ss\n" "$state" "$(basename "$d")" "$rs" "$st" "$age"
    if [ "$state" = "LIVE" ]; then
      for a in "$d"/agent-*.jsonl; do
        aage=$(( now - $(stat -c %Y "$a") ))
        # an agent with a result line in the journal has finished
        id=$(basename "$a" .jsonl); id=${id#agent-}
        if grep -q "$id" "$j" && [ "$(grep -c "\"agentId\":\"$id\"" "$j")" -gt 1 ]; then continue; fi
        tool=$(tail -c 40000 "$a" | grep -o '"name":"[A-Za-z]*"' | tail -1 | cut -d'"' -f4)
        printf "         └─ %s  %5sKB  idle %3ss  last tool: %s\n" \
               "$id" "$(( $(stat -c %s "$a") / 1024 ))" "$aage" "${tool:-?}"
      done
    fi
  done
  [ "$live" -eq 0 ] && echo "  (nothing live)"
  return $live
}

if [ "$WATCH" = 1 ]; then
  while true; do snap; n=$?; [ "$n" -eq 0 ] && { echo "all workflows finished."; break; }; sleep 20; done
else
  snap || true          # snap returns the live count; that is not a failure
fi
exit 0
