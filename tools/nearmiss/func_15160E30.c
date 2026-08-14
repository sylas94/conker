/* ===========================================================================
 * func_15160E30  --  game_18D770.c  (1032 B, -O2 -g3, no OPT_FLAGS override)
 *
 * BEST SCORE 430 (with -R and without -R, identical).  Cold start was 804.
 * FRAME IS EXACT (0x100) AND EVERY REGISTER MATCHES -- the asm-differ output
 * has ZERO 'r' (register) rows and ZERO 's'/'i' (stack-offset/immediate) rows.
 * The entire residual is TEN instruction-SCHEDULING rows in three clusters,
 * listed at the bottom.  This is the closest a cold start has come here.
 *
 * ---------------------------------------------------------------------------
 * WHAT THE FUNCTION IS
 * ---------------------------------------------------------------------------
 * The per-frame update for the actor type func_15160CDC creates (struct225
 * with the 0x28-byte payload memcpy'd to +0x18): a laser/beam sight.  It takes
 * two bone-space points out of the payload, transforms both by the owner's
 * bone matrix (func_15145EA4 with count 2 and matrix (s32)obj->unk1D4 +
 * (payload->unk5 << 6) -- the exact idiom already matched in game_12B250.c),
 * makes a direction from point B - point A, normalises it (func_15145128),
 * ray-casts along it (func_15081690), and writes the result into the actor's
 * struct226 render record: unkE/unk10/unk12 = the hit point (or the owner's
 * position when there is no hit), unk2F = an alpha byte = payload->unk20 *
 * trace.distance clamped to [0,255], unk9 = 1 for "no hit" / 0 for "hit".
 * If the hit object is type 0x9E it also pokes its +0x2E4 word to 1.
 *
 * Sibling: func_15160B74 (still a #pragma) is the same function for the
 * 0x18-byte payload of func_15160A58; its first eight instructions are
 * identical in shape and were used as the template for the entry sequence.
 *
 * ---------------------------------------------------------------------------
 * THE FRAME DECODE -- THIS IS WHAT CLOSED THE GAP (878 -> 430)
 * ---------------------------------------------------------------------------
 * Golden framesize 0x100.  Home area is contiguous and ends at framesize:
 *   0xFC p(4)  0xF8 obj(4)  0xF4 alpha(4)
 *   0xE8 spE8(12)  0xDC spDC(12)  0x78 trace(0x64)
 *   0x70 sp70(8)   0x68 sp68(8)   0x64 sp64(4)  0x60 sp60(4)
 *   0x5C hitFlag(4)  0x58 hit(4)
 *   -> 0x58..0x100 = 0xA8 = sum(sizeof(local)).  Contiguity is exact:
 *      0x78 + 0x64 == 0xDC and 0xDC + 12 == 0xE8, which is what pins the
 *      trace record at 0x64 bytes (= Ray151C196C in game_1ED0F0.c) and leaves
 *      exactly 12 bytes above spE8 and exactly 8 bytes below sp60.
 * Below that: temps 0x50..0x58 (one live spill, `sw v1,0x54(sp)`, the payload
 * pointer across both calls), saved s0/s1/ra at 0x44/0x48/0x4C, arg build
 * 0x00..0x3C (func_15081690 takes 15 args).
 *
 * The five scalars are all register-resident -- their homes are NEVER read or
 * written by golden.  They are -g3 debug slots.  They are not invented frame
 * padding: their COUNT and their POSITION (three before the aggregates, two
 * after) are forced by the arithmetic above, and their IDENTITY is read off
 * the body:
 *   p, obj, alpha        the three obvious variables (v1, s0, f0)
 *   hitFlag              golden does `lbu v0,0xd1(sp)` ONCE and tests the same
 *                        register twice (`bnez v0` for ==0, `slti at,v0,2`
 *                        for >=2).  Written as two reads of trace.unk59 IDO
 *                        produces the identical code but the frame is 8 bytes
 *                        short, so it is a declared auto.
 *   hit                  golden does `lw t0,0x78(sp)` ONCE and uses it for
 *                        both `lbu 4(t0)` and `sw 0x2e4(t0)`.  Same argument.
 * MEASURED: with only p/obj/alpha declared (all three first) the frame is
 * 0xF8 and the score 878; adding hitFlag and hit LAST gives 0x100 and 430.
 * Declaring p/obj/alpha LAST instead gives 0x108 (their homes land under the
 * aggregates) and 894.
 *
 * ---------------------------------------------------------------------------
 * OTHER LEVERS THAT PAID
 * ---------------------------------------------------------------------------
 *  804 -> (fixed) `if (obj->unique_id != p->unk4)` rather than
 *        `if (p->unk4 != obj->unique_id)`.  IDO reverses comparison operands,
 *        so the FIRST-loaded value is the RIGHT operand: golden loads
 *        `lbu t7,4(v1)` (p->unk4) then `lbu t8,0x3b(s0)` (unique_id).
 *  Entry sequence: `obj = (struct127 *)arg0->unk18;` BEFORE
 *  `p = (Payload *)&arg0->unk18;` gives golden's `lw s0,0x18(s1)` /
 *  `addiu v1,s1,0x18` order.  The reverse (`p` first, then `obj = p->unk0`)
 *  emits the addiu first.
 *
 * RULED OUT (each a single-variable build, all 430 or worse):
 *   `alpha = trace.unk4 * p->unk20`  (operand swap)              430 identical
 *   `struct17 *sp70[2]/sp68[2]` instead of s32[2] + casts        430 identical
 *   swap the declaration order of hit and hitFlag                430 identical
 *   `alpha = p->unk20; alpha = alpha * trace.unk4;` (split form) 535 -- this
 *       DOES fix the load-order cluster (2) below, but it makes `alpha` an
 *       in-place web so the multiply becomes `mul.s $f0,$f0,$f6` instead of
 *       golden's `mul.s $f0,$f6,$f8` and renames eight FP registers.  Golden
 *       is the combined form; the load order is scheduling, not statement form.
 *   a 12-byte unreferenced `struct17` as the first local (the earlier, wrong
 *       reading of the 0xF4..0x100 gap)                          894
 *
 * ---------------------------------------------------------------------------
 * RESIDUAL AT 430 -- ALL THREE CLUSTERS ARE SCHEDULING
 * ---------------------------------------------------------------------------
 * (1) 3 rows.  Golden materialises `addiu a0,sp,0xdc` (&spDC) in the very
 *     first slot after `jal func_15145EA4` returns, i.e. BEFORE the three
 *     `spDC.x -= spE8.x` subtractions, and then `move a1,a0` at c50.  This
 *     file computes a0 after the second subtraction and the move after the
 *     third.  Same instructions, same registers, two positions apart.  Note
 *     golden rematerialises the address here even though it already built it
 *     at bf0 for `sp68[1] = (s32)&spDC`.
 * (2) 2 rows.  Golden loads `lwc1 $f6,0x20(v1)` (p->unk20) then
 *     `lwc1 $f8,0x7c(sp)` (trace.unk4); this file emits the two loads in the
 *     opposite order.  The `mul.s $f0,$f6,$f8` that consumes them is
 *     byte-identical.  See the split-form note above: the only known way to
 *     reorder the loads costs the FP register map.
 * (3) 5 rows.  `li v0,1` (the `return 1`) in the LAST TWO blocks.  Golden puts
 *     it last -- in the `b` delay slot at f00 for the unk9=0 block, and as the
 *     final instruction at f60 for the shared fallback -- and consequently
 *     keeps a `nop` at ef0 that belongs to the inlined float->unsigned
 *     conversion template (`ctc1 $31; nop`).  This file hoists `li v0,1` into
 *     that nop slot and into the trunc.w.s->mfc1 gap, so it fills the template
 *     nop and the `b` delay slot takes `sb zero,9(t5)` instead.  Instruction
 *     COUNTS are equal in both blocks; only the placement differs.  Note the
 *     first two `return 1` blocks (identical source) DO hoist `li v0,1` early
 *     in golden and match here exactly -- so this is a scheduler tie-break in
 *     the two tail blocks, not a source-level difference.
 *
 * NEXT MOVES: this is a permuter-ready base -- hand-reduced, exact frame, exact
 * registers, three isolated scheduling clusters.  Seed conker/permuter_tu.sh
 * with this file.  Do NOT accept a permuter output on its own number; re-score
 * on ../tools/asm-differ/diff.py -o func_15160E30 -R --max-lines 4096.
 * =========================================================================== */

#include <ultra64.h>
#include "functions.h"
#include "variables.h"

/* The 0x28-byte payload func_15160CDC memcpy's into struct225 + 0x18. */
struct S15160E30Payload {
    /* 0x00 */ struct127 *unk0;
    /* 0x04 */ u8 unk4;
    /* 0x05 */ u8 unk5;
    /* 0x06 */ u8 pad6[0x2];
    /* 0x08 */ struct17 unk8;
    /* 0x14 */ struct17 unk14;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ u8 unk24;
    /* 0x25 */ u8 unk25;
    /* 0x26 */ u8 pad26[0x2];
};

struct S15160E30Hit {
    /* 0x000 */ u8 pad0[0x4];
    /* 0x004 */ u8 unk4;
    /* 0x005 */ u8 pad5[0x2DF];
    /* 0x2E4 */ s32 unk2E4;
};

/* The ray/trace record func_15081690 fills in (Ray151C196C in game_1ED0F0.c). */
struct S15160E30Trace {
    /* 0x00 */ struct S15160E30Hit *unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ struct17 unk8;
    /* 0x14 */ u8 pad14[0x59 - 0x14];
    /* 0x59 */ u8 unk59;
    /* 0x5A */ u8 pad5A[0x64 - 0x5A];
};

extern s32 func_15145EA4(s32 *arg0, s32 *arg1, s32 arg2, s32 arg3);
extern s32 func_15145128(struct17 *, struct17 *, f32 *, f32 *);
extern void func_15081690(struct127 *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5,
                          f32 arg6, void *arg7, f32 arg8, s32 arg9, s32 argA, s32 argB, s32 argC,
                          s32 argD, s32 argE);

s32 func_15160E30(struct225 *arg0) {
    struct S15160E30Payload *p;
    struct127 *obj;
    f32 alpha;
    struct17 spE8;
    struct17 spDC;
    struct S15160E30Trace trace;
    s32 sp70[2];
    s32 sp68[2];
    f32 sp64;
    f32 sp60;
    s32 hitFlag;
    struct S15160E30Hit *hit;

    obj = (struct127 *)arg0->unk18;
    p = (struct S15160E30Payload *)&arg0->unk18;

    if (obj->interaction_state == 0) {
        return 0;
    }
    if (obj->unique_id != p->unk4) {
        return 0;
    }
    if ((obj->unk1D4 != 0) && ((p->unk24 & 1) != 0)) {
        if ((obj->unk74 & 0xF) != 0xF) {
            sp70[0] = (s32)&p->unk8;
            sp70[1] = (s32)&p->unk14;
            sp68[0] = (s32)&spE8;
            sp68[1] = (s32)&spDC;
            func_15145EA4(sp70, sp68, (s32)obj->unk1D4 + (p->unk5 << 6), 2);

            spDC.unk0 -= spE8.unk0;
            spDC.unk4 -= spE8.unk4;
            spDC.unk8 -= spE8.unk8;

            if (func_15145128(&spDC, &spDC, &sp64, &sp60) == 0) {
                arg0->unk14->unkE = obj->x_position;
                arg0->unk14->unk10 = obj->y_position;
                arg0->unk14->unk12 = obj->z_position;
                arg0->unk14->unk2F = 0;
                arg0->unk14->unk9 = 1;
                return 1;
            }

            func_15081690(obj, spE8.unk0, spE8.unk4, spE8.unk8, spDC.unk0, spDC.unk4, spDC.unk8,
                          &trace, 0.0f, 0, 0, 1, -1, 0, 0);

            hitFlag = trace.unk59;
            if (hitFlag == 0) {
                arg0->unk14->unkE = obj->x_position;
                arg0->unk14->unk10 = obj->y_position;
                arg0->unk14->unk12 = obj->z_position;
                arg0->unk14->unk2F = 0;
                arg0->unk14->unk9 = 1;
                return 1;
            }

            if ((p->unk24 & 2) != 0) {
                if (hitFlag >= 2) {
                    hit = trace.unk0;
                    if (hit->unk4 == 0x9E) {
                        hit->unk2E4 = 1;
                    }
                }
            }

            arg0->unk14->unkE = trace.unk8.unk0;
            arg0->unk14->unk10 = trace.unk8.unk4;
            arg0->unk14->unk12 = trace.unk8.unk8;
            alpha = p->unk20 * trace.unk4;
            if (alpha > 255.0f) {
                alpha = 255.0f;
            }
            if (alpha < 0.0f) {
                alpha = 0.0f;
            }
            arg0->unk14->unk2F = alpha;
            arg0->unk14->unk9 = 0;
            return 1;
        }
    }
    arg0->unk14->unkE = obj->x_position;
    arg0->unk14->unk10 = obj->y_position;
    arg0->unk14->unk12 = obj->z_position;
    arg0->unk14->unk2F = 0;
    arg0->unk14->unk9 = 1;
    return 1;
}
