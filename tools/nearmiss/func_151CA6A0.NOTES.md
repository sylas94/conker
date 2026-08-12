# func_151CA6A0 (game_1F4650.c, 1068 B) — still open. Re-measured 2026-08-11.

`tools/nearmiss/func_151CA6A0.c` is the WHOLE TU with the function live (pragma removed).
Drop it over `conker/src/game_1F4650.c` to reproduce. The repo copy of the TU is
UNTOUCHED (pragma still in place) — verified with `git status --short`.

## Corrections to the previous revision of this file

1. **The 4333 is a real bounded score.** `mips-linux-gnu-readelf -sW
   expected/build/src/game_1F4650.c.o | awk '$8=="func_151CA6A0"{print $3}'` prints
   `1068`, equal to the byte count, so asm-differ bounds the symbol. The old claim that
   asm-differ "cannot bound a GLOBAL_ASM-sourced golden symbol" is wrong for this function.
2. **The residual is NOT just two instructions.** With temp registers canonicalised and
   branch targets stripped (`05_norm.py` in the scratchpad), gold-vs-baseline is
   **47 differing rows**, and they do not all collapse when the instruction count is
   corrected — a candidate with the exact 267-instruction count still shows 46.
   Beyond the parameter prologue there are two further families:
   * the whole `spA0` initialiser block is scheduled differently (golden defers
     `sh t6,0xB4(sp)` / the `andi 0xfff9` + `ori 0x6` pair to just before the first
     `beqz`, and hoists `sw tX,0x8(sp)`-class stores; mine emits them early);
   * golden reloads `spA0.unk14` into **`$v0`** after each of calls 2/3/4
     (`lhu v0,0xB4(sp)` / `andi tX,v0,0xfff9`); mine uses a t-register — 6 rows;
   * `li v1,1` and the `swc1 $f0,0xAC/0xA8(sp)` + `sb tX,0xB0(sp)` group sit in a
     different order in the second half.
   These are probably all downstream of the parameter binding (they are what the
   scheduler does with the different register pressure), but that is unproven.

## The root residual

Golden binds the `u8` parameter to a callee-saved register **in the prologue**:

```
GOLD                       MINE (baseline)
addiu sp,sp,-0xF8          addiu sp,sp,-0xF8
lui   at,0x41C8            lui   at,0x41C8
sw    s0,0x24(sp)          sw    a1,0xFC(sp)
mtc1  at,$f0               andi  t6,a1,0xff     <-- EXTRA
andi  s0,a1,0xff           mtc1  at,$f0
sw    ra,0x2C(sp)          move  a1,t6
sw    s1,0x28(sp)          ...
sw    a0,0xF8(sp)          move  s0,a1          <-- EXTRA (before the 1st beqz)
sw    a1,0xFC(sp)
```

IDO normalises in place into `$a1`, keeps it there for the first `if (arg1 != 0)` (which
precedes any call), and splits the live range into `$s0` for the three later tests.
`$s0` is then reused for the loop counter in both builds.

**The `andi` must be the PARAMETER's own normalisation** — that is the only thing IDO
emits in the (unschedulable) prologue. Any `andi` produced by a source-level statement is
schedulable and drifts down to its first use: measured directly, `s32 arg1` + `u8 kind =
arg1;` does emit `andi s0,a1,0xff` — at instruction 82, immediately before the first
`beqz`, not at instruction 5. So no local-copy spelling can reach golden; the parameter
itself has to be bound to `$s0`.

## Spellings ruled out (all measured, whole-TU build, asm-differ `-o … -R --max-lines 4096`)

| spelling | insns (gold 267) | score (base 4333) | note |
|---|---|---|---|
| `u8 arg1`, four `if (arg1 != 0) {t=4;} else {t=0;}` | 269 | 4333 | baseline; the shape matched sibling `func_151CAB78` uses |
| `s32 arg1`, four `if ((arg1 & 0xFF) != 0)` | 266 | — | loses golden's `sw a1,0xFC(sp)` home store → the param really is u8 |
| `register u8 arg1` | 269 | 4333 | byte-identical to baseline |
| `temp_type = (arg1 != 0) ? 4 : 0;` ×4 | 269 | 4333 | byte-identical to baseline |
| ternary inlined into the 4 call arg lists, no `temp_type` | 269 | 4333 | byte-identical to baseline — "first use inside a call" does NOT fire, the ternary is still evaluated into `v0` first |
| `u8 temp_type` | 265 | 4773 | collapses the call-site `andi a1,v0,0xff` — wrong |
| `u8 kind;` declared last, `kind = arg1;` first statement, 4 tests on `kind` | **267** | **3014** | right length, but the value is materialised as `lbu s0,0xFF(sp)` from arg1's home slot, mid-body, and the prologue `andi`/`sw s0` vanish |
| same, copy placed just before the first test | 267 | 3014 | identical to the above |
| same, `kind` declared FIRST | 267 | 4059 | `kind` takes a stack slot and shifts every local by 4 (`sb zero,77(sp)`) — declare last |
| `register u8 kind;` | 267 | 3014 | identical to plain `u8 kind` |
| `s32 kind = arg1;` (u8 param) | 269 | 4333 | copy elided, back to baseline |
| `s32 arg1` param + `u8 kind = arg1;` | 266 | 2917 | best score, but structurally wrong: `andi s0,a1,0xff` lands mid-body and the home store is gone |

## Corpus law, refined

`06_u8param.py` (scratchpad) classifies every live-C matched function in `expected/`:
**18** normalise a `u8` parameter straight into a callee-saved register
(`andi sN,aM,0xff` inside the first 10 instructions); **232** use the in-place form
(`andi tN,aM,0xff` + `move aM,tN`). Of the 18, exactly one — `game_E2DA0 func_150B648C` —
*tests* the parameter before its first `jal`, i.e. shares func_151CA6A0's shape:

```c
void func_150B648C(u8 arg0) {
    ...
    if (arg0 == 0) { ... } else if (arg0 == 1) { ... } else { ... }
    ...  /* then ~8 more uses: D_8009FC60[arg0], D_8009FC6C[arg0], … */
}
```

Its parameter is used ~10 times in ~6 blocks. The in-place sibling `func_151CAB78` uses
its parameter twice. func_151CA6A0 uses it four times. So the discriminator looks
**quantitative** (number of uses / blocks the range spans), not a spelling — which is
consistent with every spelling above failing to move it. If that is right, the lever, if
one exists, is a reconstruction error elsewhere in the body that changes register
pressure, not the parameter's declaration.

## Permuter

`./permuter_tu.sh setup game_1F4650 func_151CA6A0 <this file>` → **selftest PASS**
(reassembly identity, harness-vs-Makefile codegen identical, pycparser round-trip neutral,
positive + negative controls, and TU-context is load-bearing: the isolated build differs).
`frame` reports golden frame 248 = base frame 248 and the **stack-offset multiset already
matches golden (100 displacements)**, so both gates are usable:

```
PERMUTER_TU_REQUIRE_FRAME=248 PERMUTER_TU_REQUIRE_OFFSETS=1 ./permuter_tu.sh run <dir> -j8
```

2835 iterations at -j8, base 4063 (permuter scorer) → best 3748. **The 3748 output is
semantically wrong and must not be used**: its only change is moving
`spA0.unk18 = 0xFF;` out of the first initialiser block down past the four
`func_1515548C(&spA0, …)` calls, so the callee would read an uninitialised field on calls
1–4. Golden stores it once, at `sh $t8,0xB8($sp)`, line 68 of the golden `.s` — before the
first call. Another instance of "a better score is not evidence of equivalence".

## Reusable facts about game_1F4650.c (for func_151CB110 / func_151CAD28 / func_151C82D0)

* `func_1515548C(descriptor*, u8 kind, 0, 0, size, u8, s32)` returns a node or NULL; the
  caller then `memcpy((u8*)ret + 0x70, &payload, size)`. `+0x70` is the payload slot for
  every user of this API in the tree (`game_FC5F0`, `game_113D60`, `game_1F4650`).
* The 0x58-byte descriptor is `struct_150CF680` in `src/game_FC5F0.c`. Field `unk14` is
  **u16**, not the `s16` those files declare (golden reloads it with `lhu`).
  `unk14 = (1 << (obj->[0x23D] + 0xB)) | 0x50` is the layer/priority mask; bits 1..2 are a
  2-value alignment field poked with `x = (x & ~6) | k`.
* Payload local is **0x5C** bytes and sits immediately below the descriptor.
  func_151CA6A0-only fields: `+0x18` f32 radius (-62 / -50), `+0x1C` f32, `+0x20` f32
  (1/62 = D_800AAE90 or 1/50 = D_800AAE94), `+0x24` f32 angle (stepped by
  D_800AAE98 = pi/6, 12 times = a full circle), `+0x28` f32 = D_800AAE8C (99999).
* `D_800AAE88..D_800AAE98` are REAL GLOBALS (`asm/data/24F740.rodata.s`) — `extern f32`,
  no rodata migration needed.
* IDO local layout confirmed: locals are allocated **descending in declaration order**
  (first declared gets the highest address). A scalar added at the END of the declaration
  list does not disturb the struct locals; added at the FRONT it shifts everything by 4.
