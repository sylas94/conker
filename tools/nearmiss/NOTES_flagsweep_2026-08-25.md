# The OPT_FLAGS seam on length-delta parks is EXHAUSTED (measured 2026-08-25)

## Why this sweep was run

Today `func_150A7DA0` (guTranslateF) turned out to be **16** at `-O2` against a parked "best
635", and `func_150A7CB0` (guScaleF) **2** against a parked "eight over" — purely because
nobody had measured them at a scheduling-enabled flag. See
`NOTES_small_tier_2026-08-25.md` and the `conker-g3-delayslot` memory. That raised the obvious
question: **how many other parks are sitting on a stale score for the same reason?**

Per `conker-g3-delayslot`, the signature worth acting on is **the instruction COUNT becoming
exact** at different flags; a 1–3 point gain at unchanged length is noise. So the candidate set
is exactly the parks whose length is currently WRONG.

## What was swept

All **35** parks in `ranked.tsv` with a non-zero `len_delta`, each spliced into its real TU and
scored at the tree default (`-O2 -g3`) plus `-O2`, `-O1`, `-g`.
(`-O3` and `-O1 -g3` are not buildable in this tree — asm-processor rejects both.)

Script: `scratchpad/lensweep.py` (targeted; `_flagsweep.py` sweeps all 207 parks and takes
~14 min, which is why the length-delta filter is worth applying first).

## Result: ONE signature in 35

```
func_150E7C9C   game_113D60   225 -> 202  @ -O1    <-- LENGTH BECOMES EXACT
func_150FFD84   game_12C1E0   322 -> 272  @ -g         (length still wrong)
func_1515E888   game_18A8F0   206 -> 202  @ -O2        (noise band)
func_150499A0   game_76E50    206 -> 203  @ -O2        (noise band)
func_150FF474   game_12C1E0   154 -> 153  @ -O2        (noise band)
func_1510D404   game_139FC0   124 -> 121  @ -O2        (noise band)
```
The other 29 are flat at the tree default.

**Conclusion: the gu pair was the exception, not the tip of a seam.** Do not re-run a flag
sweep over the parked backlog expecting more guTranslateF-sized corrections — this is the
measurement, and it says they are not there. The remaining low-score parks
(`func_150585F0` @2, `func_151D8868` @2, `func_15184FA4` @3, `func_10008CE8` @5,
`func_15121C80` @5) all already have EXACT length, so flags cannot be their answer either.

## The one live lead

`func_150E7C9C` (game_113D60) at `-O1` is length-exact but still 202 rows out, so it is a
cold-decompile-grade job, not a near-miss to close. Worth noting only because its parked score
was measured at flags that could never match. **Before acting on it, check the TU's pragma
count** — an `OPT_FLAGS` override changes every function in the TU, so it is only free if the
TU holds one function or its siblings are all still pragmas (a `#pragma GLOBAL_ASM` function is
spliced from golden asm and is unaffected by OPT_FLAGS).
