# func_151CA6A0 — 1068 B, game_1F4650.c — parked at **asm-differ 517** (was 4333), 2026-08-12

`tools/nearmiss/func_151CA6A0.c` is the WHOLE TU with this function live (pragma removed).
Drop it over `conker/src/game_1F4650.c` to resume. The repo copy of the TU is UNTOUCHED
(pragma still in place) — verified with `git status --short -- conker/`.

**517 is a real, bounded score**, cross-checked in the real repo build:
`tools/buildlock.sh` + `make -s build/src/game_1F4650.c.o VERSION=us` +
`diff.py -o func_151CA6A0 -R --max-lines 4096` prints `CURRENT (517)`, and the same without
`-R`. `readelf -sW` gives size=1068 so asm-differ bounds the symbol. Instruction count is
**267 = golden's 267**. Frame 248 = golden; stack-offset multiset matches golden (100
displacements). 43 differing rows remain, 39 of them register-only.

## Correction to the previous revision of this file

It claimed the function was "parked at 2917". **It was not.** The file on disk was the 4333
baseline; 2917 was a measured table row (`s32 arg1` + `u8 kind = arg1;`) that was never
written into the parked file and was in any case structurally wrong. This revision parks the
C that actually produces the score in the heading.

## 4333 → 517 in four steps, all honest C

| step | edit | score | insns (gold 267) |
|---|---|---|---|
| baseline | as parked last wave | 4333 | 269 |
| **1** | `if (arg1 != 0)` → **`if (arg1)`** (×4) | **2596** | 267 |
| **2** | move `spA0.unk44 = *(u8*)(arg0+0x23D);` **above** the two `spA0.unk14` mask statements | **652** | 267 |
| **3** | split `spA0.unk14 = (spA0.unk14 & ~0x6) \| 0x4;` into `&= ~0x6;` + `\|= 0x4;` | **582** | 267 |
| **4** | lift the loop-counter init out of the `for`: `i = 0;` **before** `sp44.unk24 = 0.0f;`, loop becomes `for (; i != 12; i++)` | **517** | 267 |
| (rejected) | hoist `sp44.unk24 = 0.0f;` above `spA0.unk30 = 8;` instead | 577 | 267 — see "refused" |
| (rejected) | permuter's `if ((short) arg1)` | 562 | **269** — see "camouflage" |

### Step 4 — the loop-counter init, and why it is progress and not a nudge

Golden's object says, unambiguously, which of the two comes first:

```
GOLD  38b0: move s0,zero          MINE @582  38b0: swc1 $f2,0x68(sp)
      38b4: swc1 $f2,0x68(sp)                38b4: move s0,zero
```

With `for (i = 0; i != 12; i++)` IDO puts the last `sp44` store first. Writing the
initialisation as its own statement *ahead of that store* — `i = 0;` … `sp44.unk24 = 0.0f;`
… `for (; i != 12; i++)` — makes IDO emit `move s0,zero` first, **exactly matching golden**,
and removes both of the displaced rows around the loop entry (the `b`/`swc1` pair). 65 points,
no instruction added, and the source now agrees with the evidence in the object rather than
being tuned against it. Placing `i = 0;` further up (two blocks earlier, or at the top of the
function) is inert or much worse (1956), so it is specifically *ahead of the final store*.

### Step 1 — THE u8-PARAMETER LAW, SOLVED, AND IT IS A SPELLING AFTER ALL

The previous note concluded the discriminator was *quantitative* ("number of uses / blocks
the range spans"), i.e. not reachable from source. That was half right — it IS a count, but a
count of a **spelling**, and it is therefore completely reachable from source:

> **an implicit truth test binds a `u8` parameter to a callee-saved register in the prologue;
> two or more explicit `!= 0` comparisons do not.**
> (The exact threshold is established by the 2^4 sweep below.)

```c
if (arg1)        -> prologue: andi s0,a1,0xff        (golden)
if (arg1 != 0)   -> prologue: andi t6,a1,0xff ; move a1,t6  ... later: move s0,a1
if (arg1 == 0)   -> 5858, worse still
```

With `if (arg1)` the **prologue is byte-identical to golden**, including the callee-save
order golden uses (`sw s0` first, then `ra`, then `s1`, because `s0` is defined at
instruction 5):

```
3500: addiu sp,sp,-0xf8      3510: andi  s0,a1,0xff
3504: lui   at,0x41c8        3514: sw    ra,0x2c(sp)
3508: sw    s0,0x24(sp)      3518: sw    s1,0x28(sp)
350c: mtc1  at,$f0           351c: sw    a0,0xf8(sp)   3520: sw a1,0xfc(sp)
```

Worth **1737 points on its own, and it also corrected the instruction count** (269 → 267):
the in-place form costs `andi tN` + `move aM,tN` + `move s0,a1` = 3 instructions where
golden spends 1.

**Why it is worth so much more than 2 instructions.** The extra `andi t6,…` consumes one
IDO temp register, which **rotated every t-register in the whole body by +1**
(`lui t7,%hi(D_80082FA0)` → `lui t8`, `lw t6,0xf8(sp)` → `lw t7`, `li t9,0x5d` → `li t0`, …).
132 of the 4333's rows were that rotation. This is the "forcers are temp-register rotation
counters" law seen from the other side: an *unwanted* extra mask rotates the pool just as a
deleted one does.

Ruled out around it, all measured: `register u8`, `unsigned char`, K&R old-style definition
(`func(arg0, arg1) void *arg0; u8 arg1; {`), K&R + `register`, ternary into `temp_type`,
ternary inlined at the call sites, `temp_type` declared first/last, `register s32 temp_type`.
All byte-identical to their base.

#### The law, sharpened by an exhaustive 2^4 sweep

The four tests were then swept over **all 16 combinations** of `if (arg1)` vs
`if (arg1 != 0)` (`t` = truth test, `N` = `!= 0`, positions 1..4):

| combination | score | insns (gold 267) |
|---|---|---|
| `tttt` `Nttt` `tNtt` `ttNt` `tttN` | **582** | **267** |
| `NNtt` | 910 | 269 |
| `NtNt` | 930 | 269 |
| `NttN` | 947 | 270 |
| `NNtN` / `NtNN` / `NNNt` | 1090 / 1110 / 1120 | 268 |
| `NNNN` | 1794 | 269 |
| `tNNt` / `tNtN` / `ttNN` / `tNNN` | 3974 / 3984 / 3984 / 4024 | 269 / 269 / 269 / 268 |

**The threshold is at TWO.** All five variants with at most one `!= 0` are byte-identical
to each other; every variant with two or more costs the in-place normalisation. So the rule
is not positional and not "where the first use is":

> IDO keeps a `u8` parameter in its incoming argument register — normalising in place with
> `andi tN,aM,0xff` + `move aM,tN`, plus a later `move sN,aM` — as soon as **two or more** of
> its uses are explicit `x != 0` comparisons. Zero or one such comparison and the parameter
> is bound straight into a callee-saved register in the prologue (`andi sN,aM,0xff`).

That single extra `andi` is a temp-register-pool consumer, so the penalty is never 2
instructions — it is 2 instructions *plus* a rotation of every t-register in the function.

### Step 2 — statement order (AXIS 1), found by exhaustive sweep

Golden's schedule loads `spA0.unk44`'s source **before** the `unk14` read-modify-write pair:

```
lbu t8,0x23d(t1)   <- unk44's load
andi t2,t6,0xfff9  /  sh  /  ori t4,t2,0x6  /  sh      <- the two unk14 masks
swc1 $f0,0xa0(sp)  /  swc1 $f0,0xa4(sp)
beqz s0,L          /  sb t8,0xe4(sp)                   <- unk44's store in the delay slot
```

so `spA0.unk44 = …;` belongs **before** `spA0.unk14 &= ~0x6;`, not after the two float
stores. Worth **1944 points** (2596 → 652).

### Step 3 — split the combined mask, and it costs nothing

`spA0.unk14 = (spA0.unk14 & ~0x6) | 0x4;` → `spA0.unk14 &= ~0x6; spA0.unk14 |= 0x4;`
(the spelling the neighbouring pair in the same function already uses). **No instruction is
added** — IDO forwards the stored value — and it is what makes golden's
`lhu v0,0xb4(sp)` reload register appear: before the split mine reloaded into a t-register at
all three later call sites, after it all three read `v0` exactly like golden. 70 points.

## REFUSED: the 577, and why refusing it was right

Hoisting `sp44.unk24 = 0.0f;` above `spA0.unk30 = 8;` scored 577 — five better than the 582 it
was compared against — and was **refused**, because golden's own schedule shows that store
sitting immediately *after* the loop-counter init, and the 577 moved it 20 instructions
earlier. Step 4 then reached **517** by attacking the same transposition from the correct
side: leave the store where golden has it and move the *counter init* ahead of it. The
refused plateau and the real fix were the same row; taking the 5 points would have hidden it.

## CAMOUFLAGE, REJECTED: the permuter's 562

See the Permuter section: `if ((short) arg1)` scores lower while emitting **269** instructions
against golden's 267. A score that improves while the instruction count moves away from
golden's is not progress. Gate on the count first.

## Residual at 517 — 43 differing rows, and what they are

Marker census from asm-differ's own dump: **39 `r` (register-only), 2 `<`, 2 `>`**.

* **The 39 `r` rows are one t-register divergence that begins at `0x3728`** (`andi t7,v0,0xfff9`
  golden vs `andi t5,v0,…` mine) — **everything before that address is byte-identical**. The
  offset is not a uniform rotation (gold `t1,t8,t6` vs mine `t7,t1,t8`) and it widens at each
  of the 3rd/4th call blocks, so it is a *global allocation* difference flipped by something
  downstream, not a positional counter.
* **The 2+2 rows are exactly two displaced instructions in the second descriptor block**:
  golden hoists `li v1,1` (the `1` of `if (D_80082FA0 == 1)`) to just after `mtc1 zero,$f2`,
  where mine emits it at its use; and golden defers `sb tN,0xb0(sp)` (`spA0.unk10 = 0x99`)
  until after the four `swc1`s, where mine emits it straight after its `li`.
* Also register-coloured but really an order difference: golden emits the four block-2 float
  stores in source order (`0xa0,0xa4,0xac,0xa8`); mine emits the `3.0f` pair first. Reordering
  them in the source does **not** change the emitted order (measured, exhaustively).
* `.rodata`/`.data` need no attention: only `.text` differs.

## Sweeps performed this wave — report the flat ones too

All with a private whole-TU scorer that compiles the candidate with the repo's exact pipeline
into a private temp dir and runs the REAL asm-differ against `expected/` through a private
`build/` + `expected/` pair (so it needs no buildlock and is parallel-safe). Calibrated: it
reproduces `0` for both TUs with the pragma in, `165` for the parked func_1512B730, and
`582` here — the last cross-checked against `make` + asm-differ in the real tree.

| sweep | size | result |
|---|---|---|
| parameter binding / declaration spellings | 15 | **`if (arg1)` wins**; 8 of the rest byte-identical to base |
| **block 1 (28 stmts): EVERY statement moved to EVERY position + every adjacent line join** | 750 | 652 is the floor; **30 variants tie at 652 byte-identical** |
| block 1 re-swept from 582 | 750 | **flat — 582 is the floor** |
| **block 2 (13 units): every unit to every position + joins** (brace-aware, the two `if/else`s are single units) | 141 | **flat — 582 is the floor.** Reordering the four float stores in the source does NOT change their emitted order |
| call / NULL-test / mask / loop spellings | 15 | only the mask split helps; `if (temp_v0)`, `if (temp_v0 != 0)`, embedded assignment, `memcpy` cast, `& 0xFFF9`, `i < 12` all byte-identical |
| loop head (`while`, `do`, split init, join with previous line), `spA0.unk10` moved outside the block, float literal `0.f`/`3.f` respellings, local declaration order ×3 | 17 | **flat at 582**; every float respelling *costs* an instruction (the 0.0f CSE is currently correct) |
| **block 0 (the opening `sp44` block, 8 units): every unit to every position + joins** | 63 | **flat — 582 is the floor** |
| **loop body (3 units): every unit to every position + joins** | 6 | **flat — 582 is the floor**; every move costs 1–4 instructions |
| **all four `if (arg1)` tests: all 2^4 truth-vs-`!=0` combinations** | 16 | see the law above |

| loop-counter placement + `temp_v0` typing (`s32`, `u8 *`) | 7 | **`i = 0;` ahead of the last store wins (517)**; `s32`/`u8 *` for `temp_v0` byte-identical |
| **block 1, block 2 and the spelling set ALL RE-SWEPT from the 517 base** | 906 | **flat — 517 is the floor of every one of them** |

**Every straight-line region of this function has been swept exhaustively for statement order
and adjacent line joins — block 0 (63), block 1 (750), block 2 (141), the loop body (6) — and
all four are flat, both at 582 and again at 517.** AXIS 1 and AXIS 2 are spent here; report
that as evidence, not as a gap.

## Permuter

`./permuter_tu.sh setup game_1F4650 func_151CA6A0 <this file> <dir>` → **SELFTEST PASS**
(all five checks; (e) reports isolation DIFFERS, so the TU-aware harness is load-bearing).
`frame` reports golden 248 = base 248 and the stack-offset multiset already matches golden,
so both gates are usable:

```
PERMUTER_TU_REQUIRE_FRAME=248 PERMUTER_TU_REQUIRE_OFFSETS=1 ./permuter_tu.sh run <dir> -j4
```

Permuter metric reads **577** for this base (asm-differ 582); the +5 offset between the two
scorers is constant and was seen on func_1512B730 too (350/355, 160/165). Do not read a
permuter number as an asm-differ number.

**Run result: ~1,860 iterations at -j4 → seven `output-577-*` TIES and three "wins".
ALL THREE WINS ARE REJECTED.** Every one of them is a single inserted CAST — the randomizer's
`add_cast` pass — and nothing else. (Method: strip *all* parentheses and whitespace before
diffing the output against `base.c`, otherwise pycparser's re-parenthesisation buries the one
real token.)

| output | permuter score | insns (gold **267**) | the entire change | why rejected |
|---|---|---|---|---|
| `output-557-1` | 557 | **269** | `if ((short) arg1)` on test 1 | emits a redundant `sll`/`sra` sign-extension pair and tests `beqz t5` instead of golden's `beqz s0` |
| `output-477-1` | 477 | **269** | `if ((unsigned short) temp_v0 != 0)` | **semantically wrong** — truncates a *pointer* to 16 bits before the NULL test |
| `output-527-1` | 527 | 267 | `1 << (long long)(…)` on a `spA0.unk14` shift count | correct length, but see below |

The `(long long)` one deserves the detail because its length is right, which is exactly when
a bad candidate is dangerous. Applied to the **second** `spA0.unk14 = (1 << (…+0xB)) | 0x50;`
by hand it scores **467** (applied to the first: 832; to both: 842). Marker census against the
parked 517:

```
517  (parked)        r 39   '<' 2   '>' 2
467  ((long long))   r 32   '<' 2   '>' 2
```

**It fixes nothing.** The two displaced instructions — golden's hoisted `li v1,1` and deferred
`sb tN,0xb0(sp)` — are byte-for-byte the same defect in both; the 50 points are entirely
register-name noise. A gratuitous `(long long)` on a shift count is not something anyone wrote
in 1999, and it is camouflage over the blocker rather than progress toward it. **REFUSED**,
on the same grounds as the 577.

**Lesson for this function: gate every permuter output on the instruction count (267) AND on
the non-register row census before reading its score.** On this function the permuter's metric
rewards adding instructions, and its `add_cast` pass will hand you three different casts that
all "win".

## Next move for whoever picks this up

The cheap statement-order gradient is spent — all four straight-line regions swept
exhaustively, twice, all flat. What is left is:

1. **Two displaced instructions in the second descriptor block** (`li v1,1` hoisted by golden,
   `sb …,0xb0(sp)` deferred by golden). These are worth far more than the register rows and
   they are the only structural evidence left. Step 4 shows the productive method: read
   golden's object for an ORDER it insists on, then find the source form that makes IDO agree,
   rather than searching for a lower number.
2. **The 39-row register divergence** that begins where the objects are still byte-identical.
   Fix (1) first — on this function every structural fix so far has collapsed a block of
   register rows with it (the mask split alone moved all three later reloads onto golden's
   `v0`).

Axes NOT yet tried, in the order I would try them: the *shape* of block 2 (whether
`spA0.unk10`/`unk14`/`unk30`/`unk34` are re-assigned there at all versus a second descriptor
being built, or whether `sp44`'s per-instance fields come from a helper); and whether the
four call sites are a loop or a macro in the original rather than four written-out copies.

## Reusable facts about game_1F4650.c (for func_151CB110 / func_151CAD28 / func_151C82D0)

* `func_1515548C(descriptor*, u8 kind, 0, 0, size, u8, s32)` returns a node or NULL; the
  caller then `memcpy((u8*)ret + 0x70, &payload, size)`. `+0x70` is the payload slot for
  every user of this API in the tree (`game_FC5F0`, `game_113D60`, `game_1F4650`).
  The 2nd argument is `u8`: the call site ends `andi a1,v0,0xff`, so keep `temp_type` `s32`.
* The 0x58-byte descriptor is `struct_150CF680` in `src/game_FC5F0.c`. Field `unk14` is
  **u16**, not the `s16` those files declare (golden reloads it with `lhu`).
  `unk14 = (1 << (obj->[0x23D] + 0xB)) | 0x50` is the layer/priority mask; bits 1..2 are a
  2-value alignment field poked with `x &= ~6; x |= k;` — **write it as two statements**, not
  as `x = (x & ~6) | k`.
* Payload local is 0x5C bytes and sits immediately below the descriptor. func_151CA6A0-only
  fields: `+0x18` f32 radius (-62 / -50), `+0x1C` f32, `+0x20` f32 (1/62 = D_800AAE90 or
  1/50 = D_800AAE94), `+0x24` f32 angle (stepped by D_800AAE98 = pi/6, 12 times = a full
  circle), `+0x28` f32 = D_800AAE8C (99999).
* `D_800AAE88..D_800AAE98` are REAL GLOBALS (`asm/data/24F740.rodata.s`) — `extern f32`,
  no rodata migration needed.
* IDO local layout: locals are allocated **descending in declaration order** (first declared
  gets the highest address). A scalar added at the END of the declaration list does not
  disturb the struct locals; added at the FRONT it shifts everything by 4.
* **The sibling `func_151CAB78` contains a byte-identical `if (arg1 != 0) { temp_type = 4; }`
  block.** A whole-file regex over that text rewrites two functions. Anchor every edit
  between `void func_151CA6A0(` and `void func_151CAACC(` — this trap was hit once this wave
  and caught by an assertion.
