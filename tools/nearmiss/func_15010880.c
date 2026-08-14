/*
 * PARKED NEAR-MISS -- func_15010880  (game_3DC30.c, 336 B, 84 instructions, frame 0x60)
 *
 * BEST MEASURED SCORE: 210   (with -R and without -R; ALWAYS equal, every variant)
 * Measured with:  cd conker && python3 ../tools/asm-differ/diff.py -o func_15010880 \
 *                     -R --max-lines 4096
 * The file previously parked here carried NO score at all, only the note
 * "NON-MATCHING: ops in wrong order".  That note is correct and this file now says
 * exactly WHICH ops, why, and everything that has been ruled out.
 *
 * NOTE ON SCORING THIS TU: `-o func_15010780` reports 210 as well.  That is the
 * cookbook's window-overshoot trap (trap #1) -- func_15010780 is 0x100 bytes and the
 * 16,384-byte window swallows func_15010880.  func_15010780 and func_150109D0 both
 * MATCH; the authoritative check is the whole-.text compare against expected/, which
 * differs by exactly 23 bytes -- all of them inside func_15010880.
 *
 * ------------------------------------------------------------------ THE RESIDUAL
 * The instruction MULTISET is IDENTICAL (verified by objdump, not by the differ):
 * same 84 instructions, same registers, same immediates, same relocations.  Only
 * TWELVE instructions in one straight-line window are ORDERED differently, and the
 * whole diff is 3 rows + 1 delete + 1 insert.
 *
 *   golden 0x184..0x1b0                     mine 0x184..0x1b0
 *     lui   t6,%hi(func_150DE32C)             lui   v0,%hi(D_800D3098)
 *     addiu t6,t6,%lo(func_150DE32C)          lw    v0,%lo(D_800D3098)(v0)
 *     lui   at,%hi(D_800E0934)                lui   t6,%hi(func_150DE32C)
 *     sw    t6,%lo(D_800E0934)(at)            addiu t6,t6,%lo(func_150DE32C)
 *     lui   v0,%hi(D_800D3098)                lui   at,%hi(D_800E0934)
 *     lw    v0,%lo(D_800D3098)(v0)            li    t9,0xc
 *     li    t9,0xc                            li    t0,0xff
 *     li    t0,0xff                           li    t1,1
 *     li    t1,1                              addiu t7,v0,0xea0
 *     addiu t7,v0,0xea0                       addiu t8,v0,0xed4
 *     addiu t8,v0,0xed4                       sw    t6,%lo(D_800E0934)(at)
 *     sh    zero,0x54(sp)                     sh    zero,0x54(sp)
 *
 * In one sentence: MY BUILD HOISTS THE D_800D3098 LOAD ABOVE THE D_800E0934 STORE
 * AND SINKS THE STORE TO THE BOTTOM OF THE WINDOW; GOLDEN RUNS THE STORE CHAIN TO
 * COMPLETION FIRST.  Both are legal schedules of the same DAG and both cover the
 * lw->addiu load-use interlock (golden with 3 fillers, mine with 6).
 *
 * ============================ WHAT THIS WAVE WAS SENT TO TEST ======================
 * THE WAVE HYPOTHESIS IS A CLEAN NEGATIVE HERE.  BEFORE 210, AFTER 210.
 *
 * variables.h says `extern struct178 D_800D3098[73]`; the symbol really holds a
 * POINTER, and golden proves it (`lui v0,%hi; lw v0,%lo(v0)` -- it loads the WORD AT
 * the symbol).  Replacing the cast-through-address idiom with the sanctioned shadow
 *
 *     #define D_800D3098 D_800D3098_array_decl_in_variables_h
 *     #include "variables.h"
 *     #undef D_800D3098
 *     extern struct178 *D_800D3098;
 *
 * changes the score by EXACTLY NOTHING: 210 -> 210 (variant B).  So does every
 * combination of it with every other lever below.
 *
 * WHY IT IS INERT HERE, AND THIS SHARPENS THE LAW RATHER THAN DENYING IT.  The wave
 * brief's mechanism is that `((T *) *(s32 *) &SYM)` forces base-then-offset while a
 * plain `extern T *SYM` gives offset-then-base *wherever the address is produced as a
 * VALUE* (`p = &TBL[i]`).  This function DOES have two value sites -- and I found them:
 *
 *     0xEA0 = 72 * 0x34   and   0xED4 = 73 * 0x34,  sizeof(struct178) == 0x34
 *
 * so `addiu t7,v0,0xea0` / `addiu t8,v0,0xed4` are literally `&D_800D3098[72]` and
 * `&D_800D3098[73]` (index 73 is one PAST the declared [73] -- more evidence the
 * array declaration is wrong).  Writing them that way is a real semantic improvement
 * and is what the body below now does.  But the indices are COMPILE-TIME CONSTANTS,
 * so both orderings fold to the same single `addiu rD,base,K` and the two spellings
 * are bit-identical.  THE LAW NEEDS A RUNTIME INDEX TO BITE.  Recorded so the next
 * agent does not re-derive it: constant-index value sites are NOT diagnostic.
 *
 * The other global was retyped too, for completeness: `extern s32 D_800E0934` really
 * holds a function pointer (golden stores &func_150DE32C into it).  Shadowing it as
 * `void (*D_800E0934)(void)` -- variant Y -- is also 210.
 *
 * ------------------------------------------------------------- MEASURED NEGATIVES
 * ~55 builds, every one hard-built (object AND asm-processor intermediate removed
 * first) and scored with AND without -R; the two ALWAYS agreed.  Do not re-explore.
 *
 * GLOBAL SPELLING / TYPE  (all 210 -- this whole axis is dead)
 *    210  cast-through-address + `s32 base` local            <- the old parked form
 *    210  D_800D3098 shadow as `struct178 *`, `base = (s32) D_800D3098`
 *    210  shadow + `&D_800D3098[72]` / `[73]` value sites    <- THE BODY BELOW
 *    210  cast idiom + the same indexed value sites
 *    210  shadow + `struct178 *base` local then `&base[72]`
 *    210  `u8 *base` / `struct178 *base` with byte arithmetic
 *    210  no base local at all (D_800D3098 read twice, CSE merges it)
 *    210  D_800E0934 shadowed as `void (*)(void)`  /  as `void *`
 *    210  BOTH globals shadowed at once
 *    210  `*(s32 *) &D_800E0934 = ...`   (alias-analysis probe, see below)
 *    210  `extern s32 D_800E0934[]` + `D_800E0934[0] = ...`     (alias probe)
 *    210  `extern void (*D_800E0934[])(void)` + `[0] = ...`     (alias probe)
 *    210  file-local struct177 shadow with `struct178 *unk4, *unk8` (pointer fields)
 *
 * ALIAS ANALYSIS IS NOT THE MECHANISM.  The obvious theory was that golden could not
 * hoist the load above the store because the two memory references were not provably
 * distinct.  Three independent ways of making the store opaque (indirect through
 * `&SYM`, unsized extern array, extern array of function pointers) all leave the
 * schedule bit-identical.  IDO resolves symbol identity through every one of them.
 *
 * STATEMENT ORDER -- EXHAUSTIVE.  All 12 orderings of the four statements
 * (S = the D_800E0934 store, Z = `tmp.unk0 = 0`, 4 = unk4, 8 = unk8) with 4 before 8;
 * the 8-before-4 half was spot-checked at 228 and is uniformly worse:
 *    210  S Z 4 8   <- optimal          210  Z S 4 8   <- equal-optimal
 *    270  S 4 Z 8       270  S 4 8 Z        505  Z 4 S 8       514  Z 4 8 S
 *    565  4 S Z 8       565  4 S 8 Z        505  4 Z S 8       514  4 Z 8 S
 *    574  4 8 S Z       574  4 8 Z S
 *    228  ...any ordering with unk8 assigned before unk4
 *    503  the store moved ABOVE the func_15177410 call
 *    573  the store AND `tmp.unk0 = 0` moved above the call
 *    821  the two addresses staged through named `struct178 *` locals (frame grows)
 * LAW: the D_800E0934 store must precede the address computations, and unk4 must
 * precede unk8.  That is already what the body does.  The axis is exhausted.
 *
 * DECLARATION ORDER (frame stays 0x60 throughout; `tmp` must be declared FIRST,
 * exactly as the FRAME LAW predicts -- it owns the top of the home area at 0x54):
 *    210  tmp, temp_v0, base      210  tmp, base, temp_v0      210  tmp, temp_v0
 *    227  temp_v0, tmp, base      227  base, temp_v0, tmp      227  temp_v0, tmp
 *    239  temp_v0, base, tmp      239  base, tmp, temp_v0
 *
 * THE -g3 SOURCE-LINE LEVER IS *NOT* DEAD ON THIS FUNCTION -- BUT IT ONLY HURTS.
 * The cookbook lists it under "DEAD, do not re-derive".  That is wrong here and the
 * counter-example is worth keeping: JOINING statements onto one source line MOVES THE
 * SCORE on func_15010880, i.e. IDO's scheduler really is line-aware at -g3.  Every
 * join measured is strictly worse, so the lever is live and useless:
 *    425  all four statements on one line
 *    425  store + unk4 joined
 *    365  unk0 alone, then store + unk4 + unk8 joined
 *    288  unk0 + unk4 + unk8 joined
 *    228  unk4 + unk8 joined
 *    210  call + store joined / store + unk0 joined / call + store + unk0 joined
 *    210  blank lines added or removed anywhere (1, 2 and 5 blank lines)
 *    210  a single statement SPLIT across two physical lines (store, or both loads)
 * So: only a join that puts the store on the same line as an address computation does
 * anything, and it does the wrong thing.  Blank lines and splits are inert because
 * .loc follows the statement, not the physical layout.
 *
 * OPT_FLAGS -- the TU's -O2 -g3 is confirmed optimal, so this is not a Makefile
 * override case like guNormalize.  (Whole-.text byte deltas vs expected/ in brackets.)
 *    210  -O2 -g3   [23 bytes]   <- shipped setting
 *    330  -O2       [79]
 *   3899  -O2 -g / -g1 / -g2  (all three identical)  [355]
 *   1204  -O1 -g3   [203]
 *   6864  -O3 -g3   [535]
 *
 * THE $v0 WRITE-AFTER-WRITE THEORY -- TESTED AND REFUTED.  Golden delays the write to
 * $v0 by exactly four slots after `jal func_15177410`, which is what a scheduler does
 * when it believes the call DEFINES $v0.  func_15177410 is declared `void`; if the
 * original TU had seen a non-void prototype (very plausible in C89) the compiler would
 * have had an output dependence and delayed `lui v0`.  Measured with a file-local
 * prototype shadow:
 *    360  `s32 func_15177410(...)`      360  `void *func_15177410(...)`
 *    210  `f32 func_15177410(...)`      (f32 returns in $f0, so no $v0 def -- inert)
 * Non-void makes it WORSE, so the WAW model is wrong.  Independently: func_15177410's
 * golden epilogue (asm/1A48C0.s) never touches $v0, so it IS void and a non-void
 * prototype would have been a lie about the ROM regardless.  Do not revisit.
 *
 * STRUCTURAL CHECKS THAT CAME BACK CLEAN (so do not chase them):
 *   - `lui $at,%hi(S)` separated from its `%lo(S)($at)` partner is NORMAL for this
 *     compiler, not a tell.  Scanned all 2387 golden .s files: gap=0 occurs 3470
 *     times but gap=6 (mine) occurs 84 times and gaps run past 170.  My build's
 *     6-instruction separation proves nothing.
 *   - frame 0x60, ra at 0x44, tmp at 0x54..0x5f -- all identical to golden, and
 *     consistent with exactly three declared autos (12 + 4 + 4 = 0x14 home area).
 *   - struct177 is right: `sh zero,0x54(sp)` proves unk0 is 16-bit.
 *
 * ------------------------------------------------------------------ PERMUTER STATUS
 * permuter_tu.sh setup + selftest on game_3DC30 / func_15010880: ALL FIVE CHECKS PASS
 * (including (b) byte-identical codegen vs the Makefile object, and (e) which reports
 * that isolation DIFFERS from the in-TU build, so the TU harness is load-bearing).
 * Run: 3906 iterations, -j 4, --stack-diffs, from the 210 base (permuter metric 330).
 * BEST FOUND = 330 = the base.  Not one improvement.  The only distinct scores it
 * reached were 335 / 340 / 347 / 348 and worse.
 *
 * ------------------------------------------------------------------------- VERDICT
 * Residual is 100% INSTRUCTION SCHEDULING: identical multiset, identical registers,
 * identical relocations, twelve instructions permuted in one window.  Three axes are
 * now swept EXHAUSTIVELY (statement order 12/12, declaration order 8/8, OPT_FLAGS 7/7)
 * and two more broadly (global spelling/type 13 spellings, source-line joins 12).
 * Everything lands on 210 or worse; nothing has ever gone below.
 *
 * This is a different wall from the register-colouring wall in func_15162B28: there
 * the allocator disagrees, here the SCHEDULER does.  Re-open only with a model of what
 * makes IDO's scheduler run a global-store chain to completion before starting a
 * global-load chain.  The decisive datum for whoever tries: golden fills the
 * lw->addiu interlock with 3 instructions and mine with 6, so mine is the "hoist the
 * load as early as possible" schedule and golden is the "leave it in place" one --
 * find what disables the hoist and this function closes.
 */

#include <ultra64.h>

#include "functions.h"
#define D_800D3098 D_800D3098_array_decl_in_variables_h
#include "variables.h"
#undef D_800D3098

/* variables.h declares this `struct178 D_800D3098[73]`.  Golden loads the WORD AT the
 * symbol (`lui v0,%hi; lw v0,%lo(v0)`), so it is really a POINTER to the table.  Note
 * that this function reaches element 73, one past the declared bound.  Twelve live TUs
 * work around the bad declaration with `*(s32 *) &D_800D3098`; this is the sanctioned
 * file-local shadow instead.  (Scored identically -- see the notes above.) */
extern struct178 *D_800D3098;

void func_15010780(void) {
    func_15177410(1, 255,    0, 108, 0, 0.0f, 15000, 80.0f, 77, 15, 127, 127, 127, 127, 127, 127);
    func_15177410(0, 255, 6628, 108, 0, 0.0f, 15000, 80.0f, 77, 15, 127, 127, 127, 127, 127, 127);
}

void func_15010880(void) {
    struct177 tmp;
    struct260 *temp_v0;

    func_15177410(0x10, 0xE9, -0x1B5, 0x463, -0xCBF, 90.0f, 0x3A98, 36.0f, 0x4D, 0xF, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F);
    D_800E0934 = (s32) func_150DE32C;
    tmp.unk0 = 0;

    tmp.unk4 = (s32) &D_800D3098[72];
    tmp.unk8 = (s32) &D_800D3098[73];

    temp_v0 = func_15149130(0x12C, -1, 0x5E, -1, 0, 0, (struct37 *) 0xC, 0xFF, 1);
    if (temp_v0 != NULL) {
        memcpy((u8 *) temp_v0 + 0x28, &tmp, 0xC);
    }
    if (D_800D2E4C->unk12 & 0x40) {
        func_15149130(5, 9, -1, -1, 1, 0, NULL, 0xFF, 1);
    }
}

void func_150109D0(void) {
    struct179 tmp;

    tmp.unk20 = 0;
    //D_80096430 listed as (struct180*), but used as (struct180) here;
    tmp.unk4 = *((struct180*) &D_80096430);

    tmp.unk0 = 1;
    tmp.unk1C = fabsf(tmp.unk4.unk4 - tmp.unk4.unk10);
    func_151ACBD4(&tmp, 0);
    func_150E8854();
}
