/*
 * NEAR MISS: func_151B65D4  (game_1E37D0.c)  -- asm-differ 754  (was 1398, was 1533)
 * WAVE 2026-08-12.
 *
 * mine 212 instructions / 848 B  vs  golden 213 / 852 B.  Frame 184 = golden's, and every
 * stack offset golden uses is reproduced except one: golden's second compiler temp is at 80,
 * mine is at 84.
 *
 * ############################################################################
 * # THIS FILE MUST NOT BE COMMITTED AS A MATCH.  It declares `unknown0` and  #
 * # `unknown1`, two 4-byte locals that the frame PROVES exist and that are   #
 * # still unidentified.  An unnamed frame-shaping local is an open question, #
 * # not a match.  See "THE OPEN QUESTION" below.                             #
 * ############################################################################
 *
 * ============================================================================
 * RESULT 1 OF THIS WAVE: 1398 -> 754, from ONE statement move.
 * ============================================================================
 *   `age = payload->unk18 + D_800BE9A4;`  moved ABOVE  `pos = payload->unk8;`
 * That is it.  644 points.  The previous revision claimed a 136-build sweep of "all
 * dependency-respecting permutations of the 12 head statements" found nothing better than
 * 1398; that claim was wrong for this pair.  Re-swept properly this wave:
 *   - every statement to every position + all pairwise swaps, dependency-filtered: 119
 *     variants, 32 tie at 754, nothing lower;
 *   - 400 random dependency-respecting permutations (seed 20260812): best 772.
 *   754 is the floor of the statement-order axis.  Do not sweep it again.
 *
 * The move also fixed the load order: golden's `lwc1 24(a2) / lwc1 0(v0) / add.s $f18 /
 * lwc1 160(sp) / lwc1 164(sp) / lwc1 28(a2) / lwc1 168(sp)` is now reproduced exactly.
 *
 * ============================================================================
 * RESULT 2: THE FRAME LAW, SHARPENED -- and it makes the two unknowns UNAVOIDABLE.
 * ============================================================================
 * Measured on this function with a private whole-TU scorer (offsets read off objdump):
 *
 *     framesize = roundup8( base + sum(sizeof(local)) ),  base = 88 for this function
 *     base = 72 (16 outgoing-arg bytes + f20..f30 at 0x10..0x3F + ra at 0x44)
 *          + 16 (the compiler-temp area)
 *     temp_base = framesize - sum(sizeof(local)) - 16
 *     the declared-local home area ENDS at framesize and locals are laid out TOP-DOWN in
 *     DECLARATION ORDER (first-declared = highest address).
 *
 *   Calibration table (all measured, INSNS 212 throughout):
 *       L=88  -> frame 176, temps 72 & 84       L=92  -> frame 184, temps 76 & 88
 *       L=96  -> frame 184, temps 72 & 84       L=100 -> frame 192, temps 76 & 88
 *       L=104 -> frame 192
 *   The temp area is a FIXED 16 bytes.  It does not shrink when only ONE float needs memory
 *   (m1_nocount96: count made a non-local, 1 temp, frame still 184, temp still at 72) and it
 *   does not grow when extra loop-invariant floats are forced live across the loop
 *   (x1/x2: frame still 184).  Unreferenced locals are NOT dropped -- they occupy their home
 *   like any other (independently re-confirmed on func_151CA6A0: +1 scalar is absorbed by the
 *   round-up, +2 grows the frame, +4/+8/+16 all match roundup8(base+L) exactly).
 *
 *   GOLDEN USES SLOT 72.  72 = temp_base only when L = 184 - 16 - 96 = 96.
 *     - L = 88 (the exact sum of the NAMED locals) puts temp_base at 80: frame would be 176.
 *     - L = 92 gives frame 184 AND golden's pos@132 / delta@160 / trail@176 / payload@180
 *       (measured: h_* variants, 762) -- but temp_base is 76, so slot 72 lies in the 4-byte
 *       alignment pad and can never be written.  REFUTED by golden's own `swc1 $f8,0x48(sp)`.
 *   So L = 96 = 24 words, of which 22 are named (88 bytes).  Two words are real.
 *
 * ============================================================================
 * THE OPEN QUESTION -- `unknown0` / `unknown1`.  STILL OPEN.  Do not ship.
 * ============================================================================
 * Golden's declaration list, read off the frame (top-down, first-declared highest):
 *
 *     180 payload | 176 trail | 172 [1 word] | 160 delta (12)
 *     144..156 [4 words] | 132 pos (12) | 88..128 [11 words]
 *
 * Named: payload, trail, e, delta, obj, dist, pos, scale, age, angle, radius, count,
 * stepAge, stepX, stepY, stepZ, stepRadius, stepAngle = 22 words = 88 bytes.  Two words
 * short.  Everything tried to dissolve them, and why each failed:
 *   - widening `delta` to 16 bytes: its only consumer is func_15143E64, LIVE MATCHED C in
 *     game_16EE20, which reads exactly 12 (`sqrtf(x*x+y*y+z*z)`).  No support for a 4th
 *     component -- the INVERSE case in the follow-the-pointer rule: the missing bytes belong
 *     to some other local.
 *   - widening `pos`: golden copies exactly 3 words out of it, twice.
 *   - `Trail151B65D4 tmp;` (0x1C) spanning 132..159: fits the byte budget, but then `obj`
 *     and `dist` have no slot, and inlining `obj` costs 2 instructions (m3_noobj96: 214
 *     instructions, 1798) when golden has only 1 more than we do.
 *   - `e` cannot be inlined: `arg0->unk2E` is incremented inside the loop, so
 *     `&trail[arg0->unk2E]` is not the same address before and after.  `e` is proven.
 *   - `register` on any local is completely inert (k1/k2/k3 byte-identical to the base).
 *   - L=104 (u1..u6: 1673..1809) and L=92 (above) are both refuted by the frame.
 *
 * ============================================================================
 * WHAT THE REMAINING ROWS ARE (754)
 * ============================================================================
 * (a) golden `count`@88 / `stepAngle`@80 / `stepRadius`@72;
 *     mine   `stepAngle`@88 / `count`@84 / `stepRadius`@72.
 *     88 is the LAST declared local's home; 72 and 84 are the two compiler temps.
 *     MEASURED, 8 declaration orders this wave and last: `stepAngle` ALWAYS takes its own
 *     home wherever that home is (a96 moves it to 128 and the slot follows), and `count` and
 *     `stepRadius` ALWAYS take temps.  In golden the roles are swapped, so golden's `count`
 *     is the last declared local and `stepAngle` is a temp.  Declaring `count` last does NOT
 *     do it (c96/k4/k5: 1406) -- IDO's choice is role-based, not order-based.
 * (b) golden issues `addiu a0,sp,0x84` BEFORE the bc1f, and materialises the 16384.0f /
 *     32768.0f constants AFTER the mul chain, leaving a third `nop` in it -- that nop IS the
 *     missing 213th instruction.  Mine fills those latency slots with the two `mtc1`s.
 *
 * NEXT MOVE: (b) is a scheduling difference in a block whose statement order is now proven
 * flat, so it needs a structural change, not a permutation -- the same shape of problem as
 * func_151CA6A0's block 5.  But NAMING THE TWO WORDS COMES FIRST: without them there is
 * nothing to ship even at score 0.
 *
 * NOT A BLOCKER: no rodata migration needed.  D_800AA474/478 live in
 * asm/data/24EF20.rodata.s and D_800BE9A4 is in variables.h.  .rodata and .data are already
 * IDENTICAL to expected/; only .text differs.
 */
#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern void func_150A7960(f32 *, f32, f32, f32, f32 *, f32 *, f32 *);
extern s32 func_15147A80(void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
} Vec151B6320;

typedef struct {
    Vec151B6320 unk0;
    s16 unkC;
    s16 unkE;
    s32 unk10;
    u8 unk14;
    u8 unk15;
    u8 pad16[2];
} Header151B6320;

typedef struct {
    f32 *unk0;
    u8 unk4;
    u8 pad5[3];
    Vec151B6320 unk8;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    s32 unk28;
} Payload151B6320;

typedef struct {
    s32 unk0;
    u8 pad4[0x14 - 0x4];
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
    u8 pad2C[0x38 - 0x2C];
    f32 unk38;
    f32 unk3C;
    f32 unk40;
} struct151B76CCObj;

typedef struct {
    u8 pad0[4];
    struct151B76CCObj **unk4;
} struct151B76CCList;

typedef struct {
    u8 pad0[0x98];
    struct151B76CCList *unk98;
} struct151B76CCArg0;

void func_151B6320(f32 *arg0, u8 arg1, s32 arg2) {
    s32 top_dummy;
    Header151B6320 header;
    s32 pad_dummy;
    Payload151B6320 payload;
    s32 *temp_v0;

    header.unk15 = 0xA;
    header.unk0.unk0 = arg0[5];
    header.unk0.unk4 = arg0[6];
    header.unk0.unk8 = arg0[7];
    header.unkC = 0x12C;
    header.unkE = 6;
    payload.unk0 = arg0;
    payload.unk4 = *(u8 *)((u8 *)arg0 + 0x3B);
    payload.unk8 = header.unk0;
    payload.unk14 = 0.0f;
    payload.unk18 = 0.0f;
    payload.unk20 = -16384.0f;
    payload.unk1C = -16384.0f;
    payload.unk24 = 0.0f;
    header.unk10 = 0xD;

    temp_v0 = (s32 *)func_15147A80(&header, 0x30, 0x1C, 0xB, 0xB, 0xB, 0, 0, 0, arg1, arg2);
    if (temp_v0 != NULL) {
        memcpy((void *)temp_v0[0x98 / 4], &payload, 0x2C);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1E37D0/func_151B6420.s")

typedef struct {
    s32 unk0;
    u8 pad4[0x14 - 0x4];
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    u8 pad20[0x3B - 0x20];
    u8 unk3B;
    f32 unk3C;
} Obj151B65D4;

typedef struct {
    Obj151B65D4 *unk0;
    u8 unk4;
    u8 pad5[3];
    Vec151B6320 unk8;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    s32 unk28;
} Payload151B65D4;

typedef struct {
    Vec151B6320 unk0;
    f32 unkC;
    u8 unk10;
    u8 pad11[3];
    f32 unk14;
    f32 unk18;
} Trail151B65D4;

typedef struct {
    u8 pad0[0x10];
    f32 unk10;
    f32 unk14;
    f32 unk18;
    u8 pad1C[0x1E - 0x1C];
    u16 unk1E;
    u8 pad20[0x25 - 0x20];
    u8 unk25;
    u8 pad26[0x2C - 0x26];
    s8 unk2C;
    s8 unk2D;
    s8 unk2E;
    u8 pad2F;
    u8 unk30;
    u8 pad31[0x94 - 0x31];
    Trail151B65D4 *unk94;
    Payload151B65D4 *unk98;
} Actor151B65D4;

extern f32 func_15143E64(Vec151B6320 *);
extern f32 D_800AA474;
extern f32 D_800AA478;
extern f32 D_800BE9A4;

s32 func_151B65D4(Actor151B65D4 *arg0) {
    Payload151B65D4 *payload;
    Trail151B65D4 *trail;
    Trail151B65D4 *e;
    Vec151B6320 delta;
    Obj151B65D4 *obj;
    f32 dist;
    f32 unknown0;
    f32 unknown1;
    Vec151B6320 pos;
    f32 scale;
    f32 age;
    f32 angle;
    f32 radius;
    f32 count;
    f32 stepAge;
    f32 stepX;
    f32 stepY;
    f32 stepZ;
    f32 stepRadius;
    f32 stepAngle;

    payload = arg0->unk98;
    trail = arg0->unk94;
    obj = payload->unk0;
    if ((obj->unk0 == 0) || (obj->unk3B != payload->unk4) || (obj->unk3C < 15.0f)) {
        arg0->unk30 = 0;
        arg0->unk1E |= 8;
        return 1;
    }

    arg0->unk10 = obj->unk14;
    arg0->unk14 = obj->unk18;
    arg0->unk18 = obj->unk1C;
    delta.unk0 = arg0->unk10 - payload->unk8.unk0;
    delta.unk4 = arg0->unk14 - payload->unk8.unk4;
    delta.unk8 = arg0->unk18 - payload->unk8.unk8;
    dist = func_15143E64(&delta);
    payload->unk14 += (dist * D_800AA474) * D_800BE9A4;
    payload->unk1C += dist * D_800AA478;
    if (1.0f < payload->unk14) {
        count = payload->unk14;
        scale = 1.0f / count;
        age = payload->unk18 + D_800BE9A4;
        pos = payload->unk8;
        angle = payload->unk20;
        radius = payload->unk24;
        stepAge = -(age * scale);
        stepX = delta.unk0 * scale;
        stepY = delta.unk4 * scale;
        stepZ = delta.unk8 * scale;
        stepAngle = (payload->unk1C - payload->unk20) * scale;
        stepRadius = dist * scale;
        do {
            e = &trail[arg0->unk2E];
            e->unk0 = pos;
            e->unk10 = 0x9B;
            e->unk14 = angle;
            e->unkC = 13.0f - age;
            age += stepAge;
            while (16384.0f < e->unk14) {
                e->unk14 -= 32768.0f;
            }
            e->unk18 = radius;
            arg0->unk2E++;
            if (arg0->unk2E == arg0->unk25) {
                arg0->unk2E = 0;
            }
            arg0->unk2C++;
            if (arg0->unk2E == arg0->unk2D) {
                arg0->unk2D++;
                if (arg0->unk2D == arg0->unk25) {
                    arg0->unk2D = 0;
                }
                arg0->unk2C--;
            }
            pos.unk0 += stepX;
            pos.unk4 += stepY;
            pos.unk8 += stepZ;
            angle += stepAngle;
            radius += stepRadius;
            payload->unk14 -= 1.0f;
        } while (1.0f < payload->unk14);
        payload->unk8 = pos;
        payload->unk20 = angle;
        payload->unk24 = radius;
        payload->unk18 = age;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1E37D0/func_151B6928.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1E37D0/func_151B70B4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1E37D0/func_151B7144.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1E37D0/func_151B7328.s")

s32 func_151B7678(struct151B76CCArg0 *arg0, f32 *arg1) {
    struct151B76CCList *list;
    struct151B76CCObj **entry;
    struct151B76CCObj *obj;

    list = arg0->unk98;
    entry = list->unk4;
    obj = *entry;
    if ((obj->unk0 == 0) || (*((u8 *) entry + 4) != *((u8 *) obj + 0x3B))) {
        return 0;
    }

    arg1[0] = obj->unk14;
    arg1[1] = obj->unk18;
    arg1[2] = obj->unk1C;
    return 1;
}

s32 func_151B76CC(struct151B76CCArg0 *arg0, f32 *arg1) {
    struct151B76CCList *list;
    struct151B76CCObj **objPtr;
    struct151B76CCObj *obj;
    f32 mtx[4][4];

    list = arg0->unk98;
    objPtr = list->unk4;
    obj = *objPtr;
    func_150A8050(mtx, obj->unk20, obj->unk24, obj->unk28);
    mtx[3][0] = obj->unk38;
    mtx[3][1] = obj->unk3C;
    mtx[3][2] = obj->unk40;
    mtx[0][0] *= obj->unk18;
    mtx[0][1] *= obj->unk18;
    mtx[0][2] *= obj->unk18;
    mtx[1][0] *= obj->unk1C;
    mtx[1][1] *= obj->unk1C;
    mtx[1][2] *= obj->unk1C;
    mtx[2][0] *= obj->unk18;
    mtx[2][1] *= obj->unk18;
    mtx[2][2] *= obj->unk18;
    func_150A7960(mtx[0], 0.0f, 0.0f, -250.0f, arg1, arg1 + 1, arg1 + 2);
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1E37D0/func_151B77F4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1E37D0/func_151B7998.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1E37D0/func_151B7C38.s")

extern void (*D_8008FB98[])(void *, s32, u8);

void func_151B82CC(void *arg0, s32 arg1, u8 arg2) {
    void *v0 = *(void **)((u8 *)arg0 + 0x98);
    void (*f)(void *, s32, u8) = D_8008FB98[*(u8 *)((u8 *)v0 + 0x8)];
    if (f != 0) {
        f(arg0, arg1, arg2);
    }
}

struct S151B8318 {
    s32 unk0;
    u8 unk4;
};

struct T151B8318 {
    s32 unk0;
    struct S151B8318 *unk4;
};

void func_151B8318(struct102 *arg0, struct S151B8318 *arg1, u8 arg2) {
    int id;
    struct T151B8318 *v0 = *(struct T151B8318 **)((u8 *)arg0 + 0x98);
    struct S151B8318 *v1 = v0->unk4;

    if (arg2 == 0) {
        if ((v1->unk0 == (id = arg1->unk0)) || (arg1->unk4 == v1->unk4)) {
            func_1516972C(arg0);
        }
    }
}

void func_151B8370(void *arg0) {
    s32 v0 = *(s32 *)((u8 *)arg0 + 0x98);
    struct102 *v = *(struct102 **)v0;
    if (v != 0) {
        func_1516972C(v);
    }
}

extern void func_151B8370(void *);
extern void func_151478F4(void *);

void func_151B83A0(void *arg0) {
    func_151B8370(arg0);
    func_151478F4(arg0);
}

extern void func_15147928(void *);

void func_151B83CC(void *arg0) {
    func_151B8370(arg0);
    func_15147928(arg0);
}
