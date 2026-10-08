# Waves 8 + 9 -- PAUSED 2026-10-06 (agents stopped mid-batch by the owner)

**UPDATE 2026-10-06: all 37 manifest functions (33 TUs) were reviewed, accepted and SPLICED into
conker/src, UNCOMMITTED by the owner's request. Force-clean ROM check: code bin 842e3d34... and full
ROM 4cbadd3c... both exact; all 33 objects rebuilt fresh. Pragmas 1447 -> 1410.** Steps 1-2 below are
DONE; only step 3 (the 53 in requeue.txt) remains. The other TU copies in w8A/w9A/w9C that are not in
the manifest are unchanged or prototype-only (game_16EE20) and were deliberately not spliced.

## What is saved
- `w8A..w9C/<TU>.c` -- each agent's whole-TU copy (based on the e077627 tree). Every function the
  copy de-pragmas scored **mism 0** in fastscore when paused: see `wave89_manifest.tsv`
  (37 functions in 33 TUs; columns wave, TU, func, mism). NOT YET REVIEWED against the fake-match
  policy and NOT ROM-gated -- treat them as candidates.
- `requeue.txt` -- the 53 wave 8/9 functions that were not finished (unattempted or in progress).
- `wave8_*.txt`, `wave9_*.txt` -- the original batch lists; `SMALL_BRIEF.md` (agent brief incl. the
  2026-10-06 laws); `cut.py`, `small.py`, `lint.py`, `splice.sh`, `rom.sh`, `tried.txt`.

## To resume
1. For each TU copy: run `python lint.py conker/src/<TU>.c w8X/<TU>.c` and READ the diff (pads inside
   typedefs are fine; reject dead locals/reads, block-scoped parameter aliases, parameter reuse,
   `if (0)`, volatile, comma-index tricks -- see SMALL_BRIEF.md). If a TU changed since e077627,
   splice per function instead of copying the file.
2. Copy accepted TUs into conker/src, delete their build/src/<TU>.c.o, run rom.sh (both sha1s).
   If the ROM differs, bisect by reverting single TUs.
3. Re-queue: remove the `requeue.txt` names from tried.txt, regenerate the list with `small.py`
   (writes small_list.json next to it), cut new waves with `cut.py <wave> 3 15 [busy wave files]`.
   Waves can overlap when their TU sets are disjoint (cut.py's extra args exclude busy TUs).
