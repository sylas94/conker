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
  Remaining: one instruction. Callers pass `*((u8*)&arg0 + 3)`, `0x12`, `0x11`, consistent with
  a u8 parameter; the caller is already matched, so gate any install on the full ROM sha1.
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
