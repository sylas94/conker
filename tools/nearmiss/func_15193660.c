/* =====================================================================================
 * game_1C0B10 / func_15193660   (404 B, 101 instructions)   PARKED 2026-08-16
 *
 * BEST SHIPPABLE SCORE:  12   (extern-f32 spelling, frame 0x98 exact, n = 101/101)
 * BEST SCORE AT ALL:      0   (identical C, float LITERALS instead of `extern f32`)
 *
 * THE VERDICT IN ONE LINE
 *   The C below is PROVEN BYTE-EXACT.  Spelled with inline float literals it scores 0 with
 *   the exact instruction count, and IDOs own literal pool comes out byte-for-byte equal to
 *   goldens rodata block (D_800A81C0..D_800A81E0, same nine values, same order).  It cannot
 *   ship only because live-C .rodata is discarded by this build: NO object in the tree has a
 *   .rodata section (checked all 464 in conker/expected/build/src).  This is the documented
 *   systemic rodata blocker, and this function is a clean, fully-solved instance of it.
 *
 * WHAT THE RESIDUAL 12 ACTUALLY IS  (extern-f32 spelling)
 *   Every one of the 12 rows is a pure FP-REGISTER-NAME difference.  Offsets, opcodes, order
 *   and instruction count are all exact:
 *       idx16  lwc1 f0  <- D_800A81C0        golden: lwc1 f2
 *       idx18  lwc1 f2  <- D_800A81C4        golden: lwc1 f14
 *       idx33  mtc1 zero,f12                 golden: mtc1 zero,f0
 *       idx34  mtc1 zero,f14                 golden: mtc1 zero,f12
 *       idx82..85, 91..94  the eight swc1 of those four registers
 *   Goldens leftover-FP pool (f0,f2,f12,f14) is dealt out in the order  z1, C0, z2, C4.
 *   The extern spelling can only produce  C0, C4, z1, z2  -- because with an `extern f32` the
 *   register is allocated where the LOAD is emitted, and the load must sit at the statements
 *   source position.  With a literal pool IDO decouples the two: the pool loads are hoisted to
 *   the top of the function in pool order while the register assignment still follows value
 *   CREATION order.  No source order can reproduce that decoupling.
 *   MEASURED DEAD FLAT: 24 extern variants (4 block orders x 3 hoist positions x 2 zero
 *   spellings) all scored exactly 12; 6 more scored 38.  This is not a spelling we have not
 *   found -- it is a mechanism the spelling cannot reach.
 *
 * THE UNLOCK, precisely
 *   conker/conker.us.yaml line 1444:   - [0x24CC80, rodata]
 *   becomes                            - [0x24CC80, .rodata, game_1C0B10]
 *   (0x24CC80 is 16-aligned and the block is 0x50 bytes = a multiple of 16, so Law 1 is
 *   satisfied; there is already a precedent two lines above: [0x24CC20, .rodata, game_1BFCB0].)
 *   COST: the block is 20 words, D_800A81C0..D_800A820C, and it is shared with the TUs three
 *   OTHER, already-matched functions -- func_151937F4 (D_800A81E4), func_151938E4 (D_800A81E8)
 *   and func_151938FC (D_800A81EC..D_800A8208).  All of them must be converted from
 *   `extern f32` to literals in the same edit so IDO mints the whole 20-word pool in exactly
 *   that order, and all four must then re-verify.  That is a TU-level campaign, not a
 *   one-function edit -- which is exactly what the "rodata-blocked functions unlock in TU-LEVEL
 *   CLUSTERS" law predicts.  Whoever does it should start from this file: the hard half (the C)
 *   is finished.
 *
 * HOW THE SOURCE ORDER WAS DETERMINED  (all four constraints independently confirmed)
 *   1. The struct is `struct Local15152520Arg` from game_17CAF0.c -- the MATCHED definition of
 *      the callee func_15152520.  Field offsets/types are ground truth, not guessed.  (Renamed
 *      here to Local15193660Arg because it must be file-local.)
 *   2. `0.f` vs `0.0f` splits IDOs zero pool.  With all four zeros spelled `0.0f` IDO emits
 *      ONE `mtc1 zero` and the function is one instruction short (n=100/101).  Spelling the
 *      unk54/unk60 pair `0.f` splits the pool and gives goldens two.  Worth 90 -> 15.
 *   3. `unk70 = 0x21` must be assigned immediately after the unk50..unk64 block and BEFORE the
 *      eight 0xFF bytes: golden materialises 0x21 as the 9th li-constant (t6) and the first
 *      0xFF as the 10th (t7).  Assigning it in offset order makes it the 15th and shifts the
 *      whole 0xFF temp rotation by one slot.  Worth 13 rows.
 *   4. The unk50..unk64 order was settled by an EXHAUSTIVE 720-permutation sweep (all orders of
 *      the six fields, literal spelling).  Exactly one order scores 0: 58, 50, 54, 60, 64, 5C.
 *      The runner-up plateau is 2 (12 orders), residual = the intra-pair swc1 store order.
 *
 * TO SHIP AFTER THE RODATA MIGRATION: replace the nine D_800A81xx reads below with, in order,
 *      D_800A81C0 -> -12.85999966f     D_800A81C4 ->  25.37999916f
 *      D_800A81C8 ->  12.40300083f     D_800A81CC ->   5.039000034f
 *      D_800A81D0 ->   0.908870995f    D_800A81D4 ->  -0.7070000172f
 *      D_800A81D8 ->   0.2610000074f   D_800A81DC ->   1.960000038f
 *      D_800A81E0 ->   0.3070000112f
 * and delete the nine extern declarations.  Nothing else changes; that edit alone is 12 -> 0.
 * ===================================================================================== */

#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern f32 D_800A81C0;
extern f32 D_800A81C4;
extern f32 D_800A81C8;
extern f32 D_800A81CC;
extern f32 D_800A81D0;
extern f32 D_800A81D4;
extern f32 D_800A81D8;
extern f32 D_800A81DC;
extern f32 D_800A81E0;

struct Local15193660Header {
    s32 unk0;
    s32 unk4;
    s32 unk8;
};

struct Local15193660Bytes {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
};

/* Byte-for-byte `struct Local15152520Arg` from the MATCHED game_17CAF0.c (its consumer). */
struct Local15193660Arg {
    s32 unk0;
    s32 unk4;
    struct Local15193660Header unk8;
    s16 unk14;
    s16 unk16;
    s16 unk18;
    s16 unk1A;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    s16 unk30;
    s16 unk32;
    s32 unk34;
    s32 unk38;
    s32 unk3C;
    f32 unk40;
    f32 unk44;
    f32 unk48;
    f32 unk4C;
    f32 unk50;
    f32 unk54;
    f32 unk58;
    f32 unk5C;
    f32 unk60;
    f32 unk64;
    struct Local15193660Bytes unk68;
    struct Local15193660Bytes unk6C;
    u8 unk70;
    u8 unk71;
    s16 unk72;
    s16 unk74;
};

extern void func_15142314(s32, s32, f32 *);
extern void func_15152520(struct Local15193660Arg *, u8, s32);

void func_15193660(struct127 *arg0, u8 arg1, s32 arg2) {
    struct Local15193660Arg sp20;

    if (arg0 != 0) {
        if (arg0->interaction_state != 0) {
            if (arg0->unk1D4 != 0) {
                func_15142314((s32) arg0->unk1D4, 0xA, (f32 *) &sp20.unk8);
                sp20.unk0 = 8;
                sp20.unk4 = 7;
                sp20.unk58 = D_800A81C0;
                sp20.unk50 = D_800A81C0;
                sp20.unk54 = 0.f;
                sp20.unk60 = 0.f;
                sp20.unk64 = D_800A81C4;
                sp20.unk5C = D_800A81C4;
                sp20.unk14 = 0;
                sp20.unk16 = 0xFF;
                sp20.unk18 = -0x21;
                sp20.unk1A = 0x18;
                sp20.unk1C = D_800A81C8;
                sp20.unk20 = D_800A81CC;
                sp20.unk24 = D_800A81D0;
                sp20.unk28 = D_800A81D4;
                sp20.unk2C = D_800A81D8;
                sp20.unk30 = 0x28;
                sp20.unk32 = 0x23;
                sp20.unk34 = 0xA0;
                sp20.unk38 = 0x13;
                sp20.unk3C = 0;
                sp20.unk40 = 0.0f;
                sp20.unk44 = D_800A81DC;
                sp20.unk48 = D_800A81E0;
                sp20.unk4C = 0.0f;
                sp20.unk70 = 0x21;
                sp20.unk68.unk0 = 0xFF;
                sp20.unk68.unk1 = 0xFF;
                sp20.unk68.unk2 = 0xFF;
                sp20.unk68.unk3 = 0xFF;
                sp20.unk6C.unk0 = 0xFF;
                sp20.unk6C.unk1 = 0xFF;
                sp20.unk6C.unk2 = 0xFF;
                sp20.unk6C.unk3 = 0xFF;
                sp20.unk71 = 0xF;
                sp20.unk72 = 0x19;
                sp20.unk74 = 0xA;
                func_15152520(&sp20, arg1, arg2);
            }
        }
    }
}

/* =====================================================================================
 * RE-MEASURED 2026-08-20 -- THE "SCORES 0 WITH LITERALS" CLAIM ABOVE DOES NOT REPRODUCE.
 *
 * Three spellings were built and scored with tools/fastscore.py. All three give EXACTLY 12,
 * frame -152, n=101/101 -- the same residual the extern spelling has:
 *
 *   1. this file as saved (extern f32)                                      12
 *   2. this file with all 25 extern refs replaced by inline literals        12
 *   3. the whole TU, func_15193660 converted to literals, others extern     12
 *   4. the whole TU, ALL FOUR functions converted to literals               12
 *
 * So the 12 is NOT caused by the extern spelling, and moving to a literal pool does not
 * decouple load position from register assignment the way the header above predicts.
 * Do not re-run the extern-vs-literal experiment; it is measured and flat.
 *
 * WHAT THE WHOLE-TU CONVERSION *DID* ESTABLISH (this part is solid and worth keeping):
 *   The migration itself is viable. Converting all four functions emits a .rodata section of
 *   exactly 0x50 bytes, 16-aligned, and 19 of golden's 20 words are byte-identical in the
 *   right order:
 *       ours    ... 4101999a 3eae147b 3c23d70a 3c23d70a 3a83126f ...
 *       golden  ... 4101999A 3A83126F 3C23D70A 3C23D70A 3A83126F ...
 *                            ^^^^^^^^
 *   * IDO does NOT dedupe float literals: 0.001f appears in three separate slots and 0.01f in
 *     two, exactly as golden has them. (Probed standalone as well: six uses -> five slots, the
 *     one merge being CSE of an identical expression, not pool dedup.)
 *   * 19 floats = 76 bytes pad to 80 under .rodata's 2**4 alignment, which is precisely
 *     golden's trailing `.float 0` at 24CCCC. That word is PADDING, not a value.
 *   * No symbol in block 0x24CC80 is referenced from any other TU, and the ten externs the
 *     matched functions use appear in source order matching their address order.
 *
 * THE ONE BAD WORD, and it is a real source question, not a tooling problem:
 *   offset 0x30 wants 0.001f (3A83126F) but we emit 0.34f (3EAE147B), because the live line
 *       sp54.unk0C = 340.0f * D_800A81F0;
 *   becomes `340.0f * 0.001f` once the extern is substituted, and IDO CONSTANT-FOLDS it.
 *   The original source cannot have written that product as two literals. Whatever it wrote
 *   keeps 0.001f as its own pool entry -- so the real question is how that value reaches the
 *   expression unfolded. Answer that and the block is reproducible.
 * ===================================================================================== */
