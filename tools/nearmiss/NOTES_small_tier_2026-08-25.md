# Small-function tier: what matched, what didn't (2026-08-25)

Ten byte-perfect matches shipped this session. This note records the tier BELOW them so the
next pass does not re-derive it. All scores are at the tree default unless stated.

## The reusable win: pointer-chase setter form

Four functions sat at `mism=2` with correct length until the spelling was swapped:

    *(s32 *)(*(u32 *)((u8 *)arg0 + 0x28) + 0x134) = 0;      /* 2 */
    s32 *t = *(s32 **)((u8 *)arg0 + 0x28); t[0x4D] = 0;     /* 0 */

Identical semantics; the temp form leaves the loaded pointer in `$v0` as golden does.
Try it FIRST on any small pointer-chase function.

## Still open, with diagnosis

- **func_151A8584 / func_151A85D4** (game_1D4E00, 20 words each) -- a TWIN PAIR, identical
  shape, and they score identically (28, frame=-24 EXACT, n=21/20) so whatever fixes one fixes
  both. Structure is certain:
        f = D_8008F94C[arg0->unk5C];        /* D_8008F958 for the twin */
        if (f != NULL) f(arg0);
        func_151A8560(arg0);
        func_15169804(arg0);                /* func_15169824 for the twin */
  ONE instruction too many. Golden puts `sw $a0,0x18($sp)` in BOTH the `jalr` delay slot and
  the following `jal` delay slot -- arg0 re-homed each time -- while we spill once and reload.
  *** SPELLING IS REFUTED AS A LEVER. BAIL. *** Six honest spellings all tie at EXACTLY 28:
  table declared `void (*[])(void *)` vs `void *[]` + cast; NO local at all (table entry
  re-evaluated inside the `if`); local initialised at its declaration; local assigned as a
  separate statement; the index hoisted into a `u8` local; and `if (f)` vs `if (f != NULL)`.
  A score that does not move across genuinely different honest spellings is this repo's bail
  signature. The residue is not source-level -- do not re-sweep spelling. The next honest
  levers are the permuter or a flag question, and note the frame is ALREADY EXACT, so any
  candidate that adds a local is wrong by construction.
- **func_1507EEB8** (game_AC030, 15) -- now **21 at n=14/15**, ONE short. A 5-byte shift
  register: p[4]=p[3]; p[3]=p[2]; p[2]=p[1]; p[1]=p[0]; p[0]=arg0.
  *** THE FIX WAS THE PARAMETER TYPE, AND IT IS A REUSABLE TELL. ***
  The prologue `sw $a0,0x0($sp)` + `andi $t6,$a0,0xFF` + `or $a0,$t6,$zero` is the signature of
  a **`u8` PARAMETER**: -g3 homes the incoming word, then IDO narrows it to 8 bits and keeps it
  in `$a0`. It is NOT `(u8)arg0` or `arg0 & 0xFF` inside the body -- those produce neither the
  home nor the `or`, and six such spellings all tied at 51 / n=11 (the bail signature).
  Declaring the parameter `u8 arg0` -- AND changing the TU's own forward declaration to match,
  or it is a redeclaration CCFAIL -- took it 51 -> 21 and 11 -> 14 words in one step.
  Pointer-base spelling is a NO-OP: `p[4]=p[3]...` off `arg1` and `q[0]=q[-1]...` off `arg1+4`
  score identically both before and after the type fix. Do not sweep that again.
  Remaining: ONE instruction, and it is now pinned exactly. Instructions 0-2 (`sw $a0,0x0($sp)`
  / `andi $t6,$a0,0xFF` / `or $a0,$t6,$zero`) are byte-identical. The whole residue is that
  golden MATERIALISES a base pointer at arg1+4 and addresses everything with NEGATIVE offsets:
      addiu $v0,$a1,0x4 ; lbu $t8,-0x2($v0) ... sb $t7,0x0($v0) ; sb $a0,0x0($a1)
  keeping BOTH `$v0` and `$a1` live, and storing `arg0` to `0($a1)` LAST. We fold `arg1 + 4`
  back into `$a1`-relative positive offsets (`lbu $t7,3(a1)` ... `sb $t0,1(a1)`) and store
  `arg0` FIRST, which is semantically identical (all four loads still precede all stores) but
  one instruction shorter. Writing `u8 *q = (u8 *)arg1 + 4;` and indexing `q[0]`/`q[-1]`/... does
  NOT stop the fold -- measured, same 21/n=14 as the plain `p[]` form.
  NEXT IDEA (untried): the +4 base may not be pointer arithmetic in the source at all. If arg1
  is a struct whose member is a 5-byte array, `&s->hist[4]` or a second named pointer may force
  the materialisation. Do NOT reach for `volatile` -- that is a forcer.
  Callers pass `*((u8*)&arg0 + 3)`, `0x12`, `0x11`, consistent with a u8 parameter; the caller
  is already matched, so gate any install on the full ROM sha1, not on this function's score.
- **func_10001420** (init_1420, 9) -- 19 at n=10/9, one over. Zero-fills 0xFE0 bytes at
  `&D_80043B40` (note variables.h declares it `s32 *`, and its `// 4064` comment == 0xFE0).
  Golden: `a0 = base + 0xFE0; do { a1 += 4; *(a1-1) = 0; } while (a1 < a0);`. Deriving `end`
  from `p` (`p + 0xFE0/4`) did not remove the extra instruction.
- **func_151E81EC** (game_20AE20, 10) -- 26 at n=12/10. Zeroes D_800E0BA4, D_800E0BA0,
  D_800E0BA8, D_800E0BAC (in THAT order) then a byte at D_8008FD84. Golden reuses one `$at`
  across the BA4/BA0 pair and another across BA8/BAC; we emit an extra `lui` per store. Likely
  wants an array/struct rather than four separate externs.

## Not worth attempting

`game_D3040 / DAC30 / D4E10 / D4C20 / DAE50 / D5650 / DADB0 / D5030` and `game_225D20` --
the handwritten-math cluster. Several disassemble with explicit
`/* handwritten instruction */` markers (`sub`, `neg`, `add` without overflow-checking forms),
and `game_D5030`'s guMtxIdent is proven `-mips3`-blocked: the codegen needs a 64-bit type AND
`-mips3`, but a `-mips3` object cannot link ("failed to merge target specific data").

## Counting trap

Ranking `asm/nonmatchings/*.s` reports ~2108 functions left; ~467 are ORPHANS whose C is
already decompiled, and every splice against them fails with "pragma not found". Rank by
`#pragma GLOBAL_ASM` lines actually present in `conker/src/*.c`: 1641 real, 1449 unattempted
and unparked, only ~35 under 20 instructions -- and this session consumed most of those.

## Second wave (13-30 word tier) -- diagnosed, none matched

- **func_15167010** (game_1944C0, 23) -- **24 at n=22/23**, ONE short. Walks `D_8008B4A8` in
  0x34-byte strides to `base+0x1484`, calling `entry->unk18` when non-NULL. Golden saves
  `s0,s1,s2` but NEVER USES s1 -- that dead save is very likely the missing instruction, so the
  source has a third variable that our version optimises away. `struct115 *` stride arithmetic
  and a raw `u8 *` walk score the same. variables.h has `extern struct115 D_8008B4A8[]`; do not
  redeclare it.
- **func_1519ED24** (game_1CBE20, 24) -- 43 at n=26/24, two over. Copies 8 floats out of
  `arg0->unk170` into arg0, scaling the first two by `D_800A8CD8`, returns 1. Dropping the
  destination local (writing through `arg0` directly) did NOT help -- same 43 either way.
- **func_150A7CB0 / func_150A7DA0** (game_D5160 / game_D5250, 20 each) -- these are **guScaleF**
  and **guTranslateF**: a 4x4 float matrix with the diagonal at 0x0/0x14/0x28/0x3C, taking the
  three values in `$a1..$a3`. The SDK-shaped source is structurally right but scores 100/99 at
  n=28/20 -- EIGHT over, because our f32 parameters route through FP registers (`mtc1`/`swc1`)
  where golden stores them straight from the GPRs (`sw $a1,0x0($a0)`) and writes the twelve
  zeros as `sw $zero` rather than float stores. This is the SAME parameter-staging problem as
  guMtxXFMF (see tools/nearmiss/guMtxXFMF.c) -- treat all three as one blocker, not three
  functions, and do not re-sweep matrix spelling until that is understood.

  **SUPERSEDED 2026-08-25 -- the "eight over" and the parameter-staging framing are both wrong
  for func_150A7CB0. It is TWO over, and the blocker is a delay-slot scheduler tie.**

  * **The parameter staging is not a mystery and not a blocker: it is a TYPE fact.** golden's
    twelve `sw $zero` are NOT what IDO emits for `0.0f` -- measured, a `0.0f` store compiles to
    `mtc1 $zero,$f0` + `swc1 $f0` (that is the whole of the "eight over": score 60, n=24/20).
    `sw $zero` and `sw $a1` only come from INTEGER-typed stores, so the original source stored
    integer words, and the punned reconstruction already parked in the TU is closer to the
    original than the SDK float form is. It is not a forcer.
  * **`-g3` is the second half.** The TU's own comment already said so. Scores for the parked
    punned form: `-O2 -g3` = 3 (jr delay slot left as a nop), **`-O2` = 2**, `-O1` = 2,
    `-g` = 59. Both TUs hold EXACTLY ONE function, so a per-TU `OPT_FLAGS := -O2` override
    cannot break a sibling -- this is the ideal case for one. See [[conker-g3-delayslot]].
  * **What is actually left is 2 words, and it is a scheduler tie, not a spelling.** golden ends
    `swc1 $f4,0x3C` / `jr` / `sw $zero,0x38`(slot); we end `sw $zero,0x38` / `jr` /
    `swc1 $f4,0x3C`(slot). IDO sorts our last two stores into ADDRESS order and then drops the
    last one into the slot; golden's kept source order. **ELEVEN spellings measured, ALL exactly
    2 at -O2, byte-identical output:** five statement orderings of the last row (incl. 1.0f
    first / mid / top / plain address order), s32-typed matrix with the 1.0f as the cast access
    and both orders of the final pair, 1.0f via a named `f32` local, an `f32 *` alias local, and
    writing [3][2] through a separate `s32 *`. Statement order and which side carries the cast
    are BOTH irrelevant here. Do not re-sweep matrix spelling -- that space is now measured out.
  * The only known lever left is a code-motion barrier (`dummy_label:;`), which the TU's second
    commented block already tried and labelled "fakematch to help". That is the banned class.
  * **func_150A7DA0 measured too: `-O2 -g3` = 59, `-O2` = 16 (n=20/20, EXACT LENGTH),
    `-O1` = 54.** Its parked note's "best 635" is stale by a wide margin -- the flag was the
    whole story there as well, and it is now the closer of the two by structure.
    Its residual is the SAME reordering law, in a bigger dose: golden interleaves the four
    `swc1 $f4` diagonal stores among the `sw $zero`s in strict ADDRESS order
    (0x4, 0x0, 0x8, 0xC, 0x10, 0x14, ...), whereas we emit every int store first and group all
    four float stores at the end. We also CSE the 1.0f into `$f0`; golden uses `$f4`.
    Note golden's `sw $zero,0x4` sits BETWEEN the `mtc1` and the first `swc1 $f4,0x0` -- that
    is a scheduler hazard fill, which is why address order is broken at exactly that one spot.

  **THE UNIFYING LAW, and the one thing left worth testing.** In both functions our IDO
  REORDERS int stores ahead of float stores (guScaleF: the final pair; guTranslateF: wholesale
  grouping), while golden preserves address order. That is an aliasing decision: our stores mix
  `*(s32 *)&m[i][j]` with `m[i][j]`, two different types, so IDO is free to sink the float ones.
  Golden's compiler was NOT free to, which suggested the original source reaches both through
  ONE type rather than the cast-punning both reconstructions use.

  **THAT UNION HYPOTHESIS IS REFUTED -- tested and byte-identical.** A
  `typedef union { f32 f; s32 i; } MtxE;` matrix, every element written through one union type
  (`.i` for the words, `.f` for the 1.0f), scores EXACTLY the same as the cast form on both
  functions: guScaleF 2 / 3 / 2 and guTranslateF 16 / 59 / 54 at -O2 / -O2 -g3 / -O1. So the
  reordering is NOT a type-based aliasing decision, and unifying the access type is not the
  lever. Thirteen spellings are now measured out across the two functions. Whatever fixes this
  is not reachable by how the stores are TYPED or ORDERED in C -- treat that as settled and do
  not spend a fourth pass on matrix spelling.
