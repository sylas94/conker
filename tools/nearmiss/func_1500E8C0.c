/* ============================== PARKED -- NEAR MISS ==============================
 * func_1500E8C0   (game_3BA70.c, 480 bytes / 120 instructions, frame 0x90)
 * Wave 2026-08-21.
 *
 * FILE KIND: **BODY-TO-SPLICE**, not a standalone TU.
 *   Everything below the end of this comment block replaces EXACTLY the single line
 *       #pragma GLOBAL_ASM("asm/nonmatchings/game_3BA70/func_1500E8C0.s")
 *   in conker/src/game_3BA70.c.  Nothing else changes: no header edit, no Makefile
 *   edit, no yaml edit, no sibling touched.  game_3BA70 is built at the tree default
 *   -O2 -g3 (confirmed: fastscore prints "OPT_FLAGS -O2 -g3 (default)").
 *   Every extern / typedef the body needs beyond the TU's existing
 *   <ultra64.h> + functions.h + variables.h is declared below as LIVE C.
 *
 * MEASURED END TO END FROM THIS FILE (mechanical splice into the committed TU):
 *       mism = 48        n = 120/120  (EXACT)        frame = -144 = 0x90  (EXACT)
 *   Everything except twelve floating-point constant materialisations and the stores
 *   that consume them is byte-identical to golden.  Rows 0..26 (prologue + both
 *   func_15195AA8 calls) and rows 88..119 (the D_800BE9F0 test and the 12-argument
 *   func_1000FA64 call) match exactly.  The 48 differing words all lie in 0x374..0x45C.
 *
 * ---------------------------------------------------------------------------
 * WHAT IS SETTLED (do not re-derive)
 * ---------------------------------------------------------------------------
 * 1. The 0x50-byte descriptor handed to func_15189900 is the SAME struct as the one in
 *    the already-matched func_15008BF0 (conker/src/game_360A0.c, Struct15008BF0Emit).
 *    structs.h's struct145 mistypes unk0/unk2/unk6 as u16 and unk28 as s32; golden
 *    writes unk28 with swc1, so it is f32.  File-local typedef, exactly as
 *    game_360A0.c already does.  Every field offset is pinned by a golden store; there
 *    is no ambiguity left in the struct.
 *
 * 2. tmp.unk1C = 900.0f - tmp.unk10;  is CORRECT and is what produces golden's
 *    sub.s $f16,$f10,$f2.  Writing the arithmetic on two literals (900.0f - 400.0f) or
 *    the folded result (500.0f) makes IDO constant-fold it: one instruction
 *    disappears, n drops to 119/120 and mism jumps to ~98.  Reading the just-assigned
 *    struct member back is what keeps the subtract alive AND makes golden's operand
 *    $f2 the same register that is stored to unk10.
 *
 * 3. D_80096210 / D_80096214 / D_80096218 / D_8009621C are REAL external f32 objects
 *    (conker/asm/data/23AA60.rodata.s emits them with .float), NOT this function's own
 *    literal pool:  0.2142857164, 0.6000000238, 0.3999999762, -3000.
 *    variables.h already declares 14/18/1C as "extern f32"; it mistypes
 *    **D_80096210 as "extern s32"** (variables.h line 534).  The body below works
 *    around that with *(f32 *)&D_80096210 so that the splice needs NO header edit.
 *    Retyping it to extern f32 and writing tmp.unk28 = D_80096210; was measured:
 *    IDENTICAL codegen, mism=48.  So the header bug is real and worth fixing one day,
 *    but it is NOT the blocker, and fixing it forces a whole-tree rebuild for no gain.
 *    NO RODATA MIGRATION IS NEEDED OR WANTED HERE.  The block at 0x23AA60 is shared:
 *    it holds func_1500E738's jump table (this TU's other #pragma) as well as these
 *    four floats, so [0x23AA60, .rodata, game_3BA70] must wait for func_1500E738.
 *
 * 4. All twelve fp constants are lui-materialisable (low16 == 0) or external loads;
 *    none needs a private pool.  The function emits no .rodata.
 *
 * 5. SEMANTICS, from the already-decompiled callee (func_15189900, game_1B6DB0.c).  It
 *    memcpys the 0x50 bytes into a particle-emitter object and then reads
 *        unk8 + unk14 * 0.5f      and      unk10 + unk1C * 0.5f
 *    i.e. unk8/unkC/unk10 are an ORIGIN and unk14/unk18/unk1C are the matching
 *    EXTENTS of a spawn box.  Our values are origin (800, -3000, 400) and extent
 *    (0, 0, 500).  That is independent confirmation of point 2: unk1C is a Z extent
 *    written as far-minus-near, 900.0f - unk10, with unk10 = 400.0f the near plane.
 *    It also says unk14 = 0.0f and unk18 = 0.0f are genuinely zero extents, not
 *    stand-ins for something with a longer live range.
 *
 * ---------------------------------------------------------------------------
 * THE ENTIRE RESIDUAL, IN ONE LINE
 * ---------------------------------------------------------------------------
 * IDO materialises the twelve fp constants in a fixed order and assigns them registers
 * by a round-robin.  Ours and golden's round-robins differ:
 *
 *   golden  f2=400.0  f0=0.0  f4=[6210]  f6=5.0  f8=6.0  f10=8.0  f16=7.0
 *           f18=[6214]  f4=[6218]  f6=800.0  f8=[621C]  f10=900.0
 *   ours    f2=400.0  f4=[6210]  f6=5.0  f8=6.0  f10=8.0  f16=7.0  f18=900.0
 *           f6=[6214]  f8=[6218]  f0=0.0   f10=800.0  f16=[621C]
 *
 * Read that as two edits: golden pulls **0.0 forward to slot 2** and pushes **900.0
 * back to slot 12**.  The relative order of the other ten is ALREADY IDENTICAL.
 * Golden's sequence is a clean 8-wide rotation f2,f0,f4,f6,f8,f10,f16,f18 and then a
 * wrap onto f4,f6,f8,f10 (f2 and f0 are still live: 400.0 feeds the subtract at the
 * end, 0.0 feeds unk18's store at the end).  Ours never puts f0 into the rotation at
 * all -- it turns up out of turn in slot 10.  Every one of the 48 differing words is a
 * consequence of those two displacements; there is no second defect.
 *
 * ---------------------------------------------------------------------------
 * DO-NOT-REPEAT.  Every spelling measured this wave, with its score.
 * (All n=120/120 unless noted, so mism is directly comparable.)
 * ---------------------------------------------------------------------------
 *   STATEMENT ORDER -- **PROVABLY INERT**.  Do not spend another minute here.
 *     A 900-second hill climb over all single-element moves of the 24 assignments got
 *     only 48 -> 42, and it got there by scattering the *integer* stores (u46 to the
 *     very end, u10..u1C between u2 and u4) -- i.e. by chasing noise, not by touching
 *     the fp order.  Then the decisive control: two radically different orderings
 *     (u2C first vs u2C last) were dumped row by row and produced **byte-identical
 *     diff row sets** -- the same 48 addresses.  IDO canonicalises a straight-line
 *     block of constant stores into one local aggregate, so source order of those
 *     statements cannot reach this.  Measured, all 48:
 *       base (golden's store order)                        48
 *       u1C moved to the end                               48
 *       u10/u14/u18 hoisted above the int block            48
 *       int block first                                    48
 *       u2C last                                           48
 *       tail floats before u1C                             48
 *       hill-climb "best" (scattered ints)                 42   <- noise, not signal
 *   SPELLING OF THE SUBTRACT
 *       tmp.unk1C = 900.0f - tmp.unk10;                    48   <- correct, keeps sub.s
 *       tmp.unk1C = 900.0f; tmp.unk1C -= tmp.unk10;        48   (identical codegen)
 *       f32 fv = 900.0f; tmp.unk1C = fv - tmp.unk10;       48   (identical codegen)
 *       tmp.unk1C = -(tmp.unk10 - 900.0f);                 91   n=121/120, adds neg.s
 *       tmp.unk1C = 900.0f - 400.0f;                       98   n=119/120, FOLDS
 *       tmp.unk1C = 500.0f;                                98   n=119/120, FOLDS
 *   SPELLING OF THE ZEROS
 *       three separate  = 0.0f                             48
 *       tmp.unk14 = tmp.unk18 = 0.0f;                      48
 *       tmp.unk2C = tmp.unk14 = tmp.unk18 = 0.0f;          48
 *       = 0  (int literal) instead of 0.0f                 48
 *       f32 fv = 0.0f; used for all three                  48
 *       tmp.unk14 = tmp.unk2C;  (read-back)                48
 *   D_80096210 ACCESS FORM
 *       *(f32 *)&D_80096210   (with variables.h's s32)     48
 *       extern f32 D_80096210; direct                      48   (header patched, then
 *                                                                reverted -- no gain)
 *   DECLARATION PLACEMENT
 *       typedef+extern immediately above the function      48
 *       typedef+extern at the top of the TU                48
 *   LOCALS
 *       Emit tmp; s32 phi_v0;                              48
 *       + one extra named f32, before or after phi_v0      48   (frame stays 0x90: the
 *                                                                locals area has 4
 *                                                                spare bytes, so one
 *                                                                more named 4-byte
 *                                                                local is FREE here)
 *   OPT_FLAGS  (diagnostic only -- this is NOT a proposal)
 *       -O2 -g3  (tree default; the TU's other four
 *                 functions already match at it)           48   <- best
 *       -O2                                                53
 *       -O1                                       178, n=127/120
 *       -O3 -g3  /  -O2 -g          asm-processor rejects the source
 *     => OPT_FLAGS IS NOT THE LEVER HERE.  -O2 -g3 is both the best score and the only
 *        setting consistent with func_1500E5C0 / func_1500E70C / func_1500E890 /
 *        func_1500EAA0 already being byte-perfect in this TU.  Do not propose an
 *        override.
 *   AGGREGATE SHAPE
 *       flat struct (as below)                             48
 *       unk10..unk1C wrapped in a nested sub-struct        48   (rotation IDENTICAL)
 *       two separate locals, hi 0x70..0x8F + lo 0x40..0x6F,
 *         only &lo passed                          307, n=96/120  <- INVALID: `hi` is
 *                                                                    never read, so
 *                                                                    IDO dead-store-
 *                                                                    eliminates all
 *                                                                    ten of its stores
 *   CALLEE PROTOTYPES  (the "entry phase" theory -- REFUTED, all rotations IDENTICAL)
 *       functions.h as-is: void *func_15195AA8(8x s32)     48
 *       shadow: void func_15195AA8(...)                    48
 *       shadow: s32  func_15195AA8(...)                    48
 *       shadow: f32  func_15195AA8(...)                    48
 *       shadow: last parameter s8 instead of s32           48
 *       shadow: parameters (s32,s32,s32,u8,u8,u8,u8,s16)   50
 *       shadow: first parameter void * instead of s32      48
 *       shadow: func_15189900(void *, s32)                 48
 *     => the discarded return value and the argument widths of the two preceding calls
 *        do NOT set the fp rotation phase.  Do not re-run this sweep.
 *   DECOMP-PERMUTER
 *       imported (conker/nonmatchings/func_1500E8C0 -- gitignored, left in place so a
 *       future wave can resume) and run 15 min, -j 6, --stop-on-zero --best-only,
 *       compiler_type = ido.  NO ZERO.  Its best find (output-715-1) is just
 *       "tmp.unk1C moved to the end", which fastscore already measures as 48 -- i.e.
 *       the permuter's own score scale moved but the object did not.  Consistent with
 *       the setup note's rule: a rotation-phase coin flip with no structural handle is
 *       what the permuter is worst at.  Do not simply re-run it longer.
 *
 * ---------------------------------------------------------------------------
 * BEST THEORY OF THE BLOCKER
 * ---------------------------------------------------------------------------
 * This is an fp temp-register ROTATION-COUNTER problem -- the floating-point twin of
 * the integer temp rotation documented in tools/ido_cookbook.md.  IDO walks an 8-wide
 * fp pool {f0,f2,f4,f6,f8,f10,f16,f18}.  Golden enters the constant block with the
 * counter positioned so the first two constants take f2 then f0; ours enters one step
 * out of phase and skips f0, which forces 900.0 into f18 (the last fresh register)
 * instead of letting it wrap onto f10 at the end.  Two independent probes say the pool
 * position is decided BEFORE the block and is untouchable from inside it:
 *   (a) replacing 0.0f with 1.0f (so it needs a real lui+mtc1 rather than mtc1 zero)
 *       moves that constant to slot 1 and shifts 400.0 to slot 2 -- the pool responds
 *       to the KIND of materialisation, not to source position;
 *   (b) removing the subtract entirely stops 400.0 being hoisted at all (it falls to
 *       slot 6), so the hoist is a live-range effect, not a statement-order effect.
 *
 * THAT THEORY'S OBVIOUS LEVER IS ALREADY REFUTED.  "The two func_15195AA8 calls set
 * the counter's entry phase" was the leading candidate and it is WRONG: eight shadow
 * prototypes (void / s32 / f32 return, narrowed parameters, pointer first parameter,
 * and func_15189900's second parameter) all leave the rotation bit-for-bit unchanged
 * (table above).  Nested aggregates leave it unchanged too.  Combined with statement
 * order being provably inert, the position is:
 *
 *   FOR A FIXED MULTISET OF TWELVE CONSTANTS, IDO PRODUCES ONE FIXED ROTATION, AND
 *   NOTHING REACHABLE FROM THIS FUNCTION'S SOURCE CHANGES IT.
 *
 * Yet golden's rotation, from the same twelve values, differs.  Something in the real
 * source therefore changes the MULTISET or the LIVE RANGES, not the ordering.  The two
 * probes that DID move the rotation are the only known handles, and both are
 * multiset/live-range changes:
 *     * 0.0f -> 1.0f      (a real lui+mtc1 instead of `mtc1 zero`) -- moves that
 *                          constant to slot 1 and pushes 400.0 to slot 2
 *     * drop the subtract  -- 400.0 stops being hoisted and falls to slot 6
 *
 * WHERE THE NEXT WAVE SHOULD LOOK, in priority order:
 *   1. A THIRTEENTH fp value that IDO deletes.  A store IDO dead-store-eliminates
 *      (a field written twice, the first write dead) would advance the rotation
 *      by one WITHOUT changing n=120 -- which is exactly the shape of the residual
 *      (0.0 one slot too late, 900.0 one wrap too early).  This is the single most
 *      plausible remaining explanation.  BUT: inventing such a store with no evidence
 *      is a forcer and is BANNED.  Look for evidence first -- the sibling emitters
 *      (func_15008BF0 in game_360A0.c, and whatever else calls func_15189900) may show
 *      a house pattern where one field is initialised to a default and then
 *      overwritten.  Only ship it if the pattern is attested elsewhere.
 *   2. Whether unk14/unk18/unk2C really are 0.0f, or are copies of a field that is
 *      itself 0.0f from somewhere with a longer live range.
 *   3. func_15189900 itself is already decompiled (game_1B6DB0.c, func_15189900 with a
 *      "Struct15189900Arg *"): read what it does with unk14/unk18/unk2C/unk1C.  If a
 *      field this function leaves alone is in fact required, that is the missing store.
 * Note both call sites' emitted argument setup ALREADY matches golden exactly, so any
 * change must be checked to keep rows 0..26 at zero -- read the rotation, not mism.
 *
 * REPRODUCING THE PROBE.  The fastest read on a candidate is not mism, it is the
 * rotation itself.  Compile, then dump with
 *     mips-linux-gnu-objdump -dz <obj>
 * and pull out the (destination register, constant) sequence of the lui/mtc1, mtc1
 * zero and lwc1 pairs; compare against golden's line above.  When the two sequences
 * agree the score is 0 -- nothing else in this function is wrong.
 *
 * NOT ATTEMPTED, DELIBERATELY: nothing on the banned list was used or is needed.  No
 * pointer-to-a-parameter, no static shadowing a real global, no volatile, no dead
 * code-motion barrier, no split store, no dead local.  The frame and the instruction
 * count are both already exact, so this is NOT the "declare N unreferenced bytes"
 * failure mode; there is nothing here for the owner ruling to stop.
 * ============================================================================= */

/* structs.h's struct145 types unk0/unk2/unk6 as u16 and unk28 as s32; the golden code
   writes unk28 with swc1, so it is f32.  Same file-local typedef that the already
   matched func_15008BF0 uses in conker/src/game_360A0.c. */
typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    f32 unk30;
    f32 unk34;
    s16 unk38;
    s16 unk3A;
    f32 unk3C;
    f32 unk40;
    s16 unk44;
    s16 unk46;
    s32 unk48;
    s32 unk4C;
} Struct1500E8C0Emit; /* 0x50 */

extern void func_15189900(Struct1500E8C0Emit *, s32);

void func_1500E8C0(void) {
    Struct1500E8C0Emit tmp;
    s32 phi_v0;

    func_15195AA8(D_800B0E00[0], D_800902E8, 0, -1, 0, 0, 0, -6);
    func_15195AA8(D_800B0E00[1], D_800902E8, 0, -1, 0, 1, 0, -6);
    /* variables.h types D_80096210 as s32; asm/data/23AA60.rodata.s emits it as
       ".float 0.2142857164".  Cast so the splice needs no header edit. */
    tmp.unk28 = *(f32 *)&D_80096210;
    tmp.unk30 = 5.0f;
    tmp.unk34 = 6.0f;
    tmp.unk20 = 8.0f;
    tmp.unk24 = 7.0f;
    tmp.unk2C = 0.0f;
    tmp.unk48 = 3;
    tmp.unk4C = 2;
    tmp.unk0 = 0x34;
    tmp.unk2 = 0x12;
    tmp.unk4 = -0x28;
    tmp.unk6 = 0xF;
    tmp.unk38 = 0x9B;
    tmp.unk3A = 0x64;
    tmp.unk44 = 0x29;
    tmp.unk46 = 0x29;
    tmp.unk10 = 400.0f;
    tmp.unk14 = 0.0f;
    tmp.unk18 = 0.0f;
    tmp.unk1C = 900.0f - tmp.unk10;
    tmp.unk3C = D_80096214;
    tmp.unk40 = D_80096218;
    tmp.unk8 = 800.0f;
    tmp.unkC = D_8009621C;
    func_15189900(&tmp, 1);
    if (D_800BE9F0 == 6) {
        phi_v0 = 52;
    } else {
        phi_v0 = 7;
    }
    func_1000FA64(1567, (s16)phi_v0, 0, 0, 12000, 1000, 400, (s32)func_1000EF40, 0, 0, 72, 0);
}
