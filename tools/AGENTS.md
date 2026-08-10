# Conker Decomp — Orchestrator Runbook

Match every `game` function to byte-identical IDO 5.3 `-O2 -g3` asm. Branch `decomp/game-matches`.
Two engines run in PARALLEL: the **orchestrator** (LLM agents match `GLOBAL_ASM` stubs) and the
**permuter daemon** (cracks JUSTREG residue on spare CPU). You coordinate them BETWEEN runs.

## LATEST STATE & PENDING (read FIRST after compaction)
- **Active run (CYCLE ~34, 2026-06-26):** `CONKER_SEGMENTS=init,debugger bash tools/orchestrator_codex.sh 12 400 8`,
  tracked → notifies. **~65.7% funcs / ~34% bytes, ~2030 stubs left.** Steady trickle 1–5 matches/cycle (frontier,
  NOT a bug; every 5th cycle is a RE-PROBE, now bounded to a 16-func slice). GAP ROUTINE below is the standing cadence.
- **STRATEGY PIVOT (2026-06-26, user-approved) — see memory [[conker-strategy-pivot]]. Byte-match hit a structural
  WALL: both engines cap ~250 insns (LLM max-ever 252, permuter 180) but ~40% of remaining BYTES are in funcs bigger
  than either has matched (up to 4837). So the goal is now BYTES, not func-%. TWO TRACKS:**
  (1) CLOSE-SEED HARVEST — `similar_chunk._harvest_key` re-orders re-attempts to BYTE-MOVERS (within a score band,
  larger IN-REACH ≤260-insn seeds first; >260 to the back). 269 in-reach close seeds incl 13 big. (2) NAME-ONLY
  TYPING — `tools/name_struct.py [src/FILE.c]` picks the matched file with the most `->unkNN`, an agent names the
  LOCAL struct fields from usage, the force-clean dual-SHA gate AUTO-ENFORCES name-only (a rename is codegen-identical
  → commits; any layout/size/type change → ROM differs → reverted). PROVEN: 13 fields named in game_117490.c,
  ROM-identical (commit 2ae13ca). Excludes libultra. Tracks done files in `tools/typed_files.txt`. **CADENCE: run it
  every ~3rd gap (NOT concurrent with matching — both build+commit, would race; time-slice instead).** ~10K `->unkNN`
  accesses remain. Permuter stays a free daemon (NOT leaned into — capped at 180). Measure BYTE-% per cycle, not func-%.
- **SESSION 2026-06-24→26 — mechanisms built (all committed, all gate-safe). Five seed sources now feed ONE byte-
  exact gate:** (1) PERMUTER closest-first scheduling — DATA-DRIVEN (n=39 cracks: max-ever-crack score=80 → cap
  `PERM_MAX_SCORE=80`; latest crack ~234K iters → `KICK_ITERS=300K` kills stuck workers via `_kick_overground`;
  priority = least-iters-first, score weak within-band). (2) PERMUTER conflict RESOLVER in `apply_wins` — on a
  compile-fail noport, parse cfe `redeclaration/conflicting` syms, strip those agent-local decls, retry (lifted
  port rate ~50%→66%). (3) NOPORT FEEDBACK — a close noport (project score ≤80) → saved as `.nearmiss` seed
  (`src:permuter-noport`) + re-opened in attempted-log → matching loop finishes it. (4) MANUAL-COMMENT HARVEST —
  `queue_comment_seeds.py` turned 117 dev decomp-attempt comments into `.nearmiss` seeds (`src:manual-comment`,
  scored 35/50/80 by author notes); converting ~3/cycle (steerable subset; regalloc-stuck ones feed the permuter).
  (5) ACCURATE CRACK LEDGER `.permuter_cracks.tsv` (sweep+apply_wins write; dashboard reconciles vs HEAD →
  ported/pending/noport/superseded, conservation holds). DASHBOARD progress now from committed HEAD (not working
  tree). `similar_chunk` gives permuter-noport + manual-comment seeds targeted prompt hints.
- **INIT/DEBUGGER reserved slice (option B, 2026-06-24):** the game RANK never selects init_*.c / debugger* (131
  init + 22 debugger were stuck at 0 progress). `similar_chunk.segment_stubs()` + a reserved slice now feed them
  through the SAME pipeline (one integrate, no concurrency risk). **ACTIVATE by relaunching the orchestrator with
  `CONKER_SEGMENTS=init,debugger`** (default `CONKER_SEG_SLOTS=3` of each 12-chunk → ~24/cycle, drains the ~146 in
  ~6 cycles, then falls through to game). Chose B over a parallel pipeline because integrate.py is unguarded +
  tree-global (force-clean ROM `make` + commit, no flock) — a 2nd same-tree pipeline races make/ROM/git; a
  worktree-isolated pipeline (option C) was overkill for 146 funcs. If relaunched WITHOUT the env, segments idle.
- **PERMUTER LIVE & PRODUCING MATCHES (2026-06-24) — runs CONCURRENTLY with matching.** MEASURED yield so far:
  cycle-7 gap 1/2 ported, cycle-8 gap **6/12 ported (50% port rate)** → 7 permuter byte-exact matches the LLM
  loop never got. Pipeline proven end-to-end: harvest→`import_new`→supervisor permutes→`collect`→`apply_wins`→
  ROM-gated commit. Reservoir 123 `.full.c`, 98 imported dirs.
  **GAP ROUTINE (every gap, BETWEEN orchestrator runs, after the matching cycle ends):** (1) PAUSE supervisor —
  DO NOT use `pkill -9 -f permuter...`: your shell cmd contains that string so pkill -9 KILLS YOUR OWN SHELL
  mid-routine. Use the comm-checked PID kill: `for p in $(pgrep -f permuter); do [ "$p" = "$$" ] && continue; c=$(ps
  -o comm= -p $p); case "$c" in python3|timeout|nice) kill -9 $p;; esac; done; rm -f /tmp/permuter_supervisor.pid`
  (avoids dir-race with import_new); (2) `python3 tools/permuter_daemon.py collect`; (3) `python3
  tools/apply_wins.py` (extract func → iter_match SCORE 0 → integrate ROM gate → commit; non-porters get
  `.noport`); (4) `python3 tools/permuter_daemon.py import_new` (ingest new near-misses + re-import improved/stale
  seeds, which rmtree's the dir and CLEARS stale `.noport` for a fresh crack); (5) RELAUNCH ONE supervisor
  `setsid python3 tools/permuter_daemon.py supervise 180 3600 >/tmp/permuter_supervise.log 2>&1 </dev/null &`;
  (6) relaunch matching. **OPS GOTCHA:** `pgrep -fc '...supervise'` SELF-MATCHES your own shell cmd (the string
  is in it, brackets don't help the non-pgrep parts) — verify the REAL count with `ps -eo args | grep -c
  '^python3 .*permuter_daemon.py supervise'` (want exactly 1). Two supervisors = double-launched workers.
  **NON-PORTS:** permuter score-0 is relative to its ISOLATED import; STALE imports (base.c older than current
  src) crack against old context and score ~30-80 in-project (won't port) — they refresh on re-import. `apply_
  wins` extract is now redefinition-aware (`_project_types()`): strips only project-header typedefs (Gfx/Mtx/
  s32, 461 names), KEEPS agent-local typed `struct_<hex>` (the type-sweep's) — else typed funcs fail to compile.
- **TU-AWARE PERMUTER — `conker/permuter_tu.sh` (2026-08-10).** Fixes the "NON-PORTS" bullet above at the root.
  Stock decomp-permuter compiles an ISOLATED single-function source: `src/ast_util.py:extract_fn()` demotes every
  other function definition in base.c to a bare prototype, and IDO -O2 -g3 codegen is TU-dependent. `permuter_tu.sh`
  keeps base.c single-function (so the randomizer is unchanged) but its generated `compile.sh` splices the candidate
  back into the real TU and compiles the WHOLE file with the repo's exact flags + asm-processor, in a private
  per-worker temp dir (never the shared `build/`). MEASURED on game_1A89B0/func_1517BBAC: 1.2 s per whole-TU compile
  on 16 cores, and its object's target-function disassembly is byte-identical to `make build/src/<tu>.c.o` —
  whereas the isolated compile of the same source is NOT (different sha1). `setup` / `selftest` / `run` / `extract` /
  `chain`; **always run `selftest` first** (5 controls incl. a pycparser round-trip check and a negative control),
  and `run` forces `--stack-diffs` because without it the scorer rewrites every sp offset to `addr(sp)` and reports
  0 for sources asm-differ scores in the hundreds. A permuter 0 is still only a CANDIDATE — re-score with asm-differ.
  **Two traps it now handles for you.** (1) *Fake constructs*: setup zeroes the ten randomization passes that can
  only emit banned code (`perm_refer_to_var` → `if (var) {}`, `perm_ins_block` → `if (1) {...}`, `perm_empty_stmt`,
  `perm_add_self_assignment`, `perm_dummy_comma_expr`, `perm_add_mask`, `perm_xor_zero`, `perm_mult_zero`,
  `perm_duplicate_assignment`, `perm_pad_var_decl`), so a win is shippable instead of having to be un-faked.
  `PERMUTER_TU_ALLOW_FAKE=1` restores them for diagnosis only. (2) *Frame trade-away*: the scorer weighs a stack
  byte at 1 but a reordering at 60 and an insertion at 100, so on a function whose last blocker is frame size it
  BUYS register wins by GROWING the frame — measured on func_1517BBAC, every "improved" output came back at frame
  232 vs the seed's 224 vs golden's 216, i.e. further from a match than it started. `./permuter_tu.sh frame <dir>`
  reports both frames and prints the gate to use; `PERMUTER_TU_MAX_FRAME=<n>` fails any candidate whose frame grew,
  `PERMUTER_TU_REQUIRE_FRAME=<n>` demands an exact frame (only usable once the base already has it).
- **CYCLE-5 GAP WORK — ALL DONE & COMMITTED (2026-06-23):**
  1. ✅ Cookbook tweaks (score-magnitude-tracks-size reframe; reloc-spelling + stack-aggregate-off-by-word BAIL
     bullets; register/volatile-last + STALL rule) — committed `0df39e8`.
  2. ✅ Committed tool fixes (dashboard truthfulness, permuter seed `.full.c`, map_select/build_actor) — `0df39e8`.
  3. ✅ `match→type` sweep wired into `orchestrator_codex.sh` after the rounds (type_pass commits via integrate,
     so distill's checkout can't lose it; 20-batch cap; self-skips when cast-free) — committed `22ded99`.
  5. ✅ EFFORT TRIAGE — committed `22ded99`: `difficult_functions.py` derives a plateau SHELF from the
     attempts.tsv history (≥2 attempts, FLAT, not a near-miss; or repeatedly uncompilable — NEVER on raw score
     height); `similar_chunk.py` SELECT skips it (bypassed on `CONKER_REPROBE=1`); orchestrator derives the shelf
     each cycle + RE-PROBES the whole shelf every 5th cycle (thaw); match prompt got the STALL bail (revert after
     ~3 no-progress iters post first-mismatch diagnosis). NOTE: 5a "instrument" was already done — the orchestrator
     ALREADY appends `(func,file,best,size)` to `attempts.tsv` every round. Shelf was 18 funcs at relaunch.
  6. ✅ Relaunched (cleared the attempted-log first — see PERMUTER below).
- **PERMUTER — still PAUSED; feeding it ORGANICALLY now (NOT a separate backfill script).** Diagnosis stays: 323
  `.nearmiss` json but only 4 had `.full.c` (rest are stale old-harvester seeds the fixed importer skips) and
  those 4 had all MATCHED → empty pantry → killed the spin-looping supervisor. KEY: `supervise` does NOT auto-run
  `import_new` (must run it manually); and NOTHING was clearing `/tmp/orchestrator_attempted_all.txt` (936 funcs)
  so the near-miss RE-ATTEMPT priority in similar_chunk never fired. FIX CHOSEN at this gap: **cleared the
  attempted-log before relaunch**, so cycle 6 re-attempts all ~215 still-stub near-misses FIRST (lowest-score
  first, each seeded with its prior best at `/tmp/prev_<func>.c`) — this organically regenerates their `.full.c`
  via the committed harvest fix AND matches some outright. **NEXT GAP (after cycle 6): run `python3
  tools/permuter_daemon.py import_new`, VERIFY one worker compiles+permutes, THEN relaunch the supervisor**
  (`setsid python3 tools/permuter_daemon.py supervise 180 3600 >/tmp/permuter_supervise.log 2>&1 </dev/null &`).
  Do NOT relaunch the supervisor until `.full.c` exist for still-stubs (`ls .nearmiss/*.full.c`) — else empty spin.
- **PERMUTER-FEED AUDIT (workflow `wco6ydl5u`, 29 agents, 2026-06-23): 16 confirmed bugs.** FIXED & COMMITTED
  this gap: [1] harvest backfilled a `.full.c` body that disagreed with the kept json when scores differed →
  now backfills only when `js == score` (`ba1c745`); [6/7] `permuter_daemon._stub_set` single-segment regex +
  flat `src/*.c` glob missed 102/323 NESTED-path seeds → `_eligible` would `rmtree` ~1/3 of valid imports →
  recurse + `[^"]+` (`49ef333`); [5] `import_new` `git checkout -- src/` backstop for a SIGKILL-leaked seed body;
  [8] `import_new` re-imports an improved seed instead of pinning a stale `base.c`; [15] `similar_chunk` drops the
  22 score-0 (object-match-but-ROM-fail) seeds from re-attempt priority (`49ef333`). **QUEUED FOR THIS GAP (need
  orchestrator edits — unsafe while it runs):** [2/9/10] in `orchestrator_codex.sh:79` (+ `type_pass.sh:61`)
  broaden the round-start clear `rm -f /tmp/{match,best,bestc}_func_*` → `_*` (38 non-`func_` stubs leak stale
  /tmp → stale `/tmp/match_<f>.c` can be `cp`'d into live src = corruption); [4] orchestrator harvest block: skip
  `best==0` so no new score-0 `.nearmiss` seeds are written; [13] decide re-attempt CADENCE — near-misses only get
  re-attempted+backfilled when the attempted-log is cleared; the one-time clear handled cycle-7's 215, but future
  near-misses need a per-cycle (or periodic) `/tmp/orchestrator_attempted_*.txt` clear to keep feeding. SKIPPED
  (low/none): [3] non-`func_` permuter globs (0 such seeds today), [14] shelf blocks backfill 4/5 cycles (only 18
  plateaus), [16] placeholder near-miss burns one slot. Full report: the `wco6ydl5u` task output.
- **PERMUTER SEED FIX (harvest side validated):** permuter seeds died on undefined-symbol COMPILE errors — the
  `.nearmiss` body lacked the func's supporting externs/struct decls. FIX: `harvest_nearmiss.py` also saves the
  whole compilable best-C file as `.nearmiss/<func>.full.c`; `import_new` imports from it (skips seeds w/o it).
  Live for cycle-5 harvests. **NO worktree needed** — the supervisor IS already an async daemon; the "build-race"
  was a red herring (real cause = broken seeds). Crack count undercounts (prune deletes matched funcs' output-0).
- **PHASE 1 TYPING: DONE** — 170 funcs typed, 0 reverts, **0 offset-casts left** (~10.5k `->`, port-ready). via
  `type_orchestrator.sh` (offset-casts → local typed structs, iter_match-verified). PHASE 2 (consolidate local →
  shared semantic structs) DEFERRED: the "99-copy Actor" was a CLUSTERING OVER-MERGE (1-2-field fragments chained
  via common offsets); needs K≥3 subset-aware clustering + per-function judgment. No cheap win (include/ structs
  are ~160 `struct<N>` placeholders, only ~9 semantic).
- **FAILURE ANALYSIS (subagent, 1674 transcripts):** ~80-85% of failures are INTRINSIC + already correctly BAILed
  (coupled regalloc 16.6%, reloc/jtbl 11.7%, scheduling 6%, -g3 spill 5.2%, FP/64-bit ~7%). Cookbook comprehensive.
  Fixable upside ~5-10% (near/mid). Score magnitude tracks FUNC SIZE not wrongness (big-func address cascade).
- **UPSTREAM (subagent-verified):** CLEAN LINEAR DESCENDANT of mkst/origin (still at fork `3adf229`); NO re-split
  divergence — same config/naming, append-only. Upstreaming = normal PR. The "re-split" was toolchain modernization
  (spimdisasm 1.42 marker fix, `libglib2.0-0`, `pycparser<3` — fixes mkst's own broken build). **PR drafts ready in
  `~/conker-pr-draft/`** (PR_DESCRIPTION, TOOLCHAIN_FIXES, INDEX). User handles the PR/comms later.
- **STRATEGIC:** matching near its practical ceiling. Keep it ($0), but upstream PR / data-rodata sections / struct
  consolidation are higher leverage when the user shifts focus.
- **DASHBOARD:** `tools/dashboard.py` :8077. Restart: kill `tools/dashboard.py` procs + `setsid python3
  tools/dashboard.py 8077 >/tmp/dashboard.log 2>&1 </dev/null &`. Read-only. Background refresher serves pre-built
  snapshot (client count doesn't drive git/pgrep load). History graph = our de-stub timeline (not the README).
- **DETERMINISTIC HARVEST:** `iter_match.sh` prints `BEST: M`, snapshots best-C → `/tmp/bestc_<func>.c`; orchestrator
  harvests `.nearmiss` (keep-best). Read the TRACKED `/tmp/best_<func>.score`, NOT the codex log (agent echoes the
  prompt's literal "SCORE: 0"). `.cycle` counter (gitignored); `integrate.py` tags commits `[cycle N]`.

## CURRENT MODE — Codex engine (rationing Claude tokens)
The matching now runs on **Codex** (zero Claude tokens), via a shell mirror of the orchestrator:
- **Run:** `bash tools/orchestrator_codex.sh 12 400 8` (chunk maxi rounds) as a tracked background task →
  one completion notification. Uses `codex exec --full-auto` for matching; similar_chunk + integrate.py
  are the deterministic glue.
- **MAXI regime (size cap, RAISE as bands deplete):** raise when a band's match RATE decays OR round-1
  candidates drop below ~8 — opening a fresh band refreshes the high-similarity supply. History: ≤90 (runs 1-9)
  → 150 (runs 10-16, 91-150 band ~80% drained) → now `maxi 250`. Unattempted runway as of run 16:
  151-250≈487, 251-400≈280, 400+≈210. Next bumps: 400, then uncapped. Bigger funcs = lower count, more bytes each.
- **Cadence each gap (lean — minimal Claude tokens):** force-clean ROM gate → `apply_wins.py` →
  `permuter_daemon.py import_new` → relaunch `orchestrator_codex.sh` → `git push sholdee decomp/game-matches`.
- **BIG-FUNC LANE (`CONKER_BIGLANE=1`, opt-in):** targets the byte wall — funcs ≥200 insn the normal flow
  shelves after 2 plateaus and the permuter can't touch. Adds a re-admitting selection lane (resumes from
  a carried-forward `/tmp/prev_<func>.c` each cycle), a region-anchored prompt, heavy 5400s timeout for
  ≥250, and always-harvest carry-forward. Bounded to the first 2 rounds/cycle. Activate:
  `CONKER_BIGLANE=1 CONKER_SEGMENTS=init,debugger bash tools/orchestrator_codex.sh 12 400 8`. Knobs +
  design in `tools/PLANS_match_rate.md` (Plan A). Measure in BYTES + `attempts.tsv` col-4 best-score trend.
- **Cookbook is TIERED:** `ido_cookbook.md` = 182-line CORE (always read); `ido_reference.md` = full
  270-bullet set (grep on-demand). Codex/Claude prompts read core + grep reference.
- **DISTILL (back on):** `orchestrator_codex.sh` ends each run with a codex distill step — skims the run's
  `/tmp/codexm_*.log`, APPENDS only genuinely-novel idioms to `ido_reference.md` under `## Post-cutover distilled`.
  Append-only guard (new file must start with old + ≤2KB growth, else revert) + reverts stray edits; self-commits.
- **MATCH CAPTURE (defeats codex over-run — was losing ~55% of found matches):** codex `--full-auto` keeps
  editing PAST `SCORE: 0` and destroys the match. `iter_match.sh` now snapshots `src/<file>.c` to
  `/tmp/match_<func>.c` the instant it prints SCORE 0; the orchestrator clears stale snapshots before MATCH and
  RESTORES each file from its snapshot after MATCH (before integrate). Deterministic — immune to whatever codex
  does after. (Prompt also hard-stops at 0; secondary.) NOTE: can't kill codex on capture to stop the over-run —
  its work runs in a DETACHED broker, so killing the `codex exec` client orphans the broker (it keeps editing →
  chaos). Over-run waste (codex tokens + wall-clock) is tolerated; the snapshot still captures the match. TODO
  parity: restore in orchestrator.js.
- **SEEDS (`similar_chunk.py` writes them; both orchestrators read them):** per picked func it writes the top-3
  similar matched functions' C → `/tmp/ref_`, `/tmp/ref2_`, `/tmp/ref3_<func>.c`, AND an m2c structural draft →
  `/tmp/m2c_<func>.c` (best-effort `--context`, falls back to raw). Prompts use refs for style + m2c for structure,
  with guardrails (never copy verbatim; m2c types are guesses). Both engines benefit since both call similar_chunk.
- **RETENTION (deterministic, via iter_match's tracked best):** `iter_match.sh` tracks the per-func running-best,
  prints `BEST: M` to the agent (so it sees regression), and snapshots the best-C to `/tmp/bestc_<func>.c`. The
  orchestrator harvests `.nearmiss` from that snapshot via `harvest_nearmiss.py` (keep-best) when `score ≤ 80 OR
  ≤ ½ instr count` — NOT from codex self-report (which drifted to over-run versions) or the log (prompt-polluted).
  `attempts.tsv` best-score also reads `/tmp/best_<func>.score`. `.nearmiss/*.json` tracked + backed up; permuter
  `import_new` keeps its ≤80 filter.
- **RE-ATTEMPT (ACTIVE — m2c validated +18% on run 18):** `rm /tmp/orchestrator_attempted_*.txt` re-opens every
  still-stubbed function (safe — only stubs re-open). `similar_chunk.py` then prioritizes **near-miss funcs first,
  lowest prior score first** (closest), and seeds each with its OWN best-C at `/tmp/prev_<func>.c` (#1) on top of
  m2c + top-3 refs. Prompts: step 0e starts the agent FROM /tmp/prev_<func>.c. Run at high maxi (400) so most
  near-misses are eligible. Closest near-misses (score 2-8) crack first; stop/raise when yield decays.
- **Fork port (DONE — 42/70 committed):** sibling-fork matches were ported via `port_fork.py` (per-func
  iter_match filter) → integrate.py. Re-running yields ~0 (the other 28 fail in our tree on header/struct
  drift); skip unless ~/conker-llm-fork advances materially.
- **Backup remote:** `sholdee` → https://github.com/sholdee/conker (branch decomp/game-matches). `git push sholdee` each gap.
- The Claude Workflow `orchestrator.js` still exists (agent-agnostic) if switching back from Codex.

## INVARIANTS — learned the hard way; violating these corrupts commits
1. **Act ONLY on a workflow's completion NOTIFICATION.** `ps`/output-size checks LIE (a workflow shows
   no process between agent spawns). Acting early ⇒ your build races the running one ⇒ stale-bin ⇒ bad commit.
2. **Never build / edit src / git while ANY workflow or build runs.** One actor on the tree at a time.
3. **FORCE-clean before every ROM check:** `rm -f conker/build/conker.us.bin build/conker.us.z64` FIRST.
   A failed compile leaves a STALE matching bin → a false "ROM OK". This caused both integrity incidents.
4. **The gate is the full ROM sha1** (inner `842e3d34…`, outer `4cbadd3c…`). `integrate.py` enforces it
   deterministically — trust it; never hand-commit a match without a force-clean ROM verify. A pre-commit hook
   (`tools/git-hooks/`, active via `core.hooksPath`) blocks edits to these SHA constants — the "fake a match"
   vector (override a genuine gate change with `ALLOW_GATE_EDIT=1 git commit`).

## THE CYCLE  (run only when NOTHING else is running)
```
0. INSPECT (force-clean):
   . .venv/bin/activate
   rm -f conker/build/conker.us.bin build/conker.us.z64
   make -C conker && make -C conker replace && make -j
   sha1sum build/conker.us.z64   # MUST be 4cbadd3c4e0729dec46af64ad018050eada4f47a
   git status --short | grep conker/src   # any stray .c = failed-agent cruft → git checkout it
1. APPLY PERMUTER WINS:   python3 tools/apply_wins.py        # collect→port→verify→commit; non-porters auto-.noport
2. INGEST HARVEST:        python3 tools/permuter_daemon.py import_new
3. REFILL (if pool low):  python3 tools/stub_expand.py expand 30   (ROM-gated) ; then REGEN RANKING (below) ; force-clean ROM verify
4. PERMUTERS: a SUPERVISOR keeps MAX_PARALLEL alive automatically (auto-replaces dead/cracked/timed-out
   with the newest seeds). Just ensure it's running (safe any time — only permutes what's imported):
   kill -0 $(cat /tmp/permuter_supervisor.pid 2>/dev/null) 2>/dev/null || \
     setsid python3 tools/permuter_daemon.py supervise 180 3600 >/tmp/permuter_supervise.log 2>&1 </dev/null &
5. ORCHESTRATOR:  Workflow { scriptPath: "tools/orchestrator.js", args: {rounds:8, chunk:8, maxi:55} }
6. WAIT for the completion notification. Repeat.
```
REGEN RANKING (after any expand):
```
cd conker; for d in asm/nonmatchings/game_*; do for f in "$d"/*.s; do [ -f "$f" ]||continue; \
  echo "$(grep -cE '^\s+/\*' "$f") ${f#asm/nonmatchings/}"; done; done | sort -n > /tmp/game_ranked2.txt
```

## TOOLS
- `orchestrator.js` — self-driving loop: select→match→distill→**rescue(Codex)**→integrate ×N rounds (Workflow).
  Claude agents read the cookbook + a similar matched reference, harvest near-misses (score ≤80) to
  `~/conker/.nearmiss/<func>.json`; Codex (`agentType: codex:codex-rescue`) takes a 2nd pass at misses ≤150.
  Integration = `integrate.py` (gates BOTH engines — only true de-stubbed score-0 matches commit).
- `select_chunk.py N M` — next N DISTINCT-file stubs (6..M instr), not in `/tmp/orchestrator_attempted.txt` (smallest-first; legacy).
- `find_similar.py FUNC [--top N]` — rank MATCHED functions by asm similarity to FUNC (cached corpus, register-normalized; drops low-quality refs).
- `similar_chunk.py N M` — like select_chunk but prioritizes stubs with a STRONG matched reference (similarity scheduling);
  writes each reference C to `/tmp/ref_<func>.c` for the match/rescue agents. This is what the orchestrator's Select stage runs.
- `iter_match.sh FILE FUNC` — build ONE object + object-diff vs `expected/`. `SCORE: 0` = match.
  ⚠ a STUB also scores 0 — only trust it for an already-de-stubbed function.
- `integrate.py FILE FUNC …` — DETERMINISTIC gate: force-clean build, dual-sha1, bisect out broken funcs, commit good.
- `stub_expand.py expand N` — flip N pure-asm game segments `asm`→`c` in the yaml + extract → new stubs.
  ROM-gated; auto-bisects rodata/jtbl segments that fail; refreshes `expected/`.
- `permuter_daemon.py {import_new | run SECS | collect | supervise [interval] [timeout]}` — spare-CPU decomp-permuter
  over `.nearmiss/` seeds (nice 19, detached, newest-first). `supervise` = long-running self-restarting pool (pidfile-guarded);
  `run` one-shot tops up free slots. `import_new` touches the build tree → run only BETWEEN runs.
- `apply_wins.py` — port + project-re-verify + commit permuter winners (their score-0 is isolated; re-verify!).
- `ido_cookbook.md` — IDO matching idioms agents read; the orchestrator's distiller MERGES novel ones (no new sections).
- `setup.sh` — fresh-host bring-up (re-applies n64splat marker-label patch, pins `pycparser<3`, venv).

## PROGRESS / STATE
```
git log --oneline | grep -c "game: match"                          # match commits
grep -rho GLOBAL_ASM conker/src/game_*.c | wc -l                   # stubs remaining
grep -cE '^\s+- \[0x[0-9A-Fa-f]+, asm\]' conker/conker.us.yaml     # un-stubbed segments left
```

## KNOWN LIMITS
- A few un-stubbed segments fail the expand sha1-gate (rodata/jump-table) — need manual yaml rodata subsegments.
- Some permuter wins don't port (isolated import context ≠ project) — `apply_wins` auto-`.noport`s them.
- jtbl-externalized & native-64-bit functions are unmatchable as stubbed C (BAIL — see cookbook).
- After `stub_expand`, run `permuter_daemon import_new` only between runs; the `expected/` refresh is automatic.

## BIG-FUNC CONVERSION (open R&D — the hard tail)
Big funcs (>=200 insn, ~40% of remaining BYTES) reach near-miss (score 10-34) but DON'T convert. Root
cause (proven, 2026-06-29): the LLM's best-C is byte-perfect compiled in ISOLATION (the decomp-permuter's
world, score 0) but N>0 in the full-file PROJECT build — a full-TU stack-frame/local-LAYOUT residue. So
**the permuter can NEVER crack them** (it's 0 in isolation, nothing to permute), and the LLM oscillates.
DEAD ENDS (all tried, all failed): frame-targeted prompt clause (live in big-lane, 0 conversions);
header fixes (callee sigs + sqrtf both red herrings — sqrtf already intrinsic via `2.0L/PR/gu.h`);
hand-rolled layout search `tools/inproject_search.py` (decl+struct mutations can't reach statement-driven
spill/regalloc).
- **`tools/inproject_permute.py` (v3) — built, run, DECISIVE NEGATIVE:** decomp-permuter's STATEMENT-level
  randomizer (library) + IN-PROJECT scorer (`iter_match`). On func_150CF140 (baseline 10): 400 iters, 390
  built, ZERO improvements — best never dipped below 10. So even the full statement-level randomizer,
  searching in-project, cannot reduce the residue.
- **ANSWER: the residue is CONTEXT-FORCED, not function-structure-reachable.** No permuter (isolated or
  in-project) can crack these — the frame inflation is imposed by the full-file COMPILATION CONTEXT (a global
  type/symbol), independent of the function body. ALL permuter/search paths are RULED OUT. The only remaining
  path: isolate WHAT global context forces the +16 frame and fix it (diff codegen under varied global type
  defs). Don't re-run inproject_search/inproject_permute expecting a crack. See memory
  `conker-bigfunc-residue-analysis.md`. **Big funcs are a hard tail — keep the normal trickle as the driver.**

## TROUBLESHOOTING
- **ENOSPC but `df -h` shows free space → it's INODES, not bytes.** `/tmp` is a tmpfs with a fixed
  inode cap (~1M). The permuter leaks `/tmp/permuterXXXX.{c,o}` on every `timeout`-SIGTERM kill; over days
  these exhaust the inode table at ~1% byte use. **Diagnose with `df -i /tmp`** (not `df -h`). Deadlock
  symptom: Bash/Write/the `!` prefix all fail (each needs to spool to `/tmp`); only Read works → fix from a
  REAL external terminal. Clean: `find /tmp -maxdepth 1 -name 'permuter*' -delete` (`rm /tmp/permuter*` dies
  on arg-list-too-long at that scale). MITIGATED: `permuter_daemon.py` `_reap_tmp()` prunes `permuter*`
  >30min old each supervise loop (180s) — but it only runs while a supervisor is alive. See memory
  `conker-tmpfs-inode-leak.md`.
- **A cycle can crash AFTER committing its match** (e.g. in a later round). `.cycle` == last `[cycle N]`
  commit does NOT prove the cycle finished cleanly — read `/tmp/orchestrator_run.log`, don't trust the
  counter alone. (`.cycle` AHEAD of the last commit still reliably means it died mid-cycle.)
- **ROM badge red but sha1 looks correct** = stale `/tmp/rom_status.json` with `"ok": false` from a failed
  verify (e.g. a crashed build). Only `integrate.py` writes it, and only `true` on a successful commit, so it
  stays red until the next match lands. If HEAD is verified-good (`make -C conker verify` → `OK`), it's safe
  to refresh the file's `ok`/`at`/`commit` by hand to clear the badge immediately.

## FRESH HOST
`tools/setup.sh`, then place `baserom.us.z64` (sha1 `4cbadd3c…`) in repo root, then run THE CYCLE.
