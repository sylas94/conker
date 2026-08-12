/*
 * NEAR MISS: func_151B65D4  (game_1E37D0.c)  -- score 1533, 848/852 bytes
 *
 * asm-differ in this repo diffs the WHOLE object in -o mode, so 1533 is a
 * whole-TU number inflated by downstream displacement. The bounded per-symbol
 * instruction diff is the honest picture:
 *
 *     mine 212 instructions / 848 B   vs   golden 213 / 852 B
 *
 * Everything from `.L151B67B8` (the do-while body) to the epilogue is already
 * BYTE-IDENTICAL: the trail-element write, the 16384/32768 angle-wrap while
 * loop, the whole ring-buffer counter block (unk2C/2D/2E/25) and the
 * accumulator tail. So is the entire prologue and the three-way early-out.
 *
 * RESIDUAL: stack-slot layout in the setup block only.
 *
 *   golden sp offsets: 72 80 88 | 132 136 140 | 160 164 168 | 176 180 184 (frame 184)
 *   mine   sp offsets: 72 84 92 | 132 136 140 | 144 148 152 | 168 172 176 (frame 176)
 *
 *   golden: stepRadius@72 stepAngle@80 count@88 ; pos@132 ; DEAD 144..159 ; delta@160
 *   mine:   stepRadius@72 count@84   stepAngle@92 ; pos@132 ; delta@144
 *
 * Golden's declared-local area is 8 bytes TALLER than mine and carries a
 * 16-byte hole at 144..159 that the golden .s never touches. Everything else
 * lines up. The one missing instruction pair is a spill store+reload that I
 * DID reproduce (see `count` below); the last single instruction is a
 * scheduling `nop` that follows from the offsets.
 *
 * WHAT WAS TRIED, WITH SCORES (all whole-TU asm-differ, -R and non-R agree):
 *
 *   2749  first cold write (count = payload->unk14 before the `if`;
 *         `payload->unk4 != obj->unk3B`; `unk25 == unk2E` comparison order)
 *   2699  + flipped all four integer comparisons. IDO emits `bne(RHS, LHS)`,
 *         so golden's `bne(unk25, unk2E)` needs source `unk2E == unk25`, and
 *         golden's `bne(payload->unk4, obj->unk3B)` needs source
 *         `obj->unk3B != payload->unk4`. Four flips, all confirmed.
 *   2693  `count` removed entirely, `payload->unk14` read twice. IDO did NOT
 *         make a CSE temp -- it just re-loaded from (a2). WRONG DIRECTION.
 *   2137  `count = payload->unk14;` moved INSIDE the `if`, so the local has
 *         exactly ONE def and ONE use and `payload->unk14` is CSEd with the
 *         comparison. This is what produces golden's redundant
 *         `swc1 $f2,0x58(sp)` / `lwc1 $f8,0x58(sp)` pair. KEY FINDING.
 *   1681  aggregate locals (`delta`, `pos`) declared FIRST in the block.
 *   1533  aggregates declared after `dist` (current). BEST.
 *   2161  `pos` declared before `delta` (they swap slots; strictly worse).
 *
 * DECLARATION-POSITION SWEEP (13 builds, aggregates walked through the scalar
 * list): score is monotone in position -- 1681,1533,1713,1753,1793,1833,1873,
 * 1913,1953,1993,2033,2121,2161. Each preceding scalar slides the aggregate
 * block DOWN by 4 bytes; the local-area top is pinned at 160 in every variant
 * and the frame never leaves 176. Declaration order alone cannot buy the
 * missing 8 bytes.
 *
 * REORDERING SWEEP (count first/last/before-steps, steps first, vecs last):
 * 1533 / 1541 / 1689 / 1713 / 2009 / 2129. The three FP spill slots stay at
 * 72/84/92 no matter how the scalars are ordered -- they are assigned by the
 * allocator, not by declaration order. Golden's 72/80/88 is not reachable this
 * way.
 *
 * LAYOUT PROBE (diagnostic only, NOT parked -- it needs a dead local): adding
 * one more 12-byte aggregate between `delta` and `pos` reproduces golden's
 * aggregate SHAPE exactly -- pos block, 16-byte hole, delta block at 160 --
 * but overshoots the frame to 192 (golden 184) and moves the spill slots to
 * 76/88/96. So golden is +8 bytes of locals over mine, not +12/+16.
 *
 * NEXT LEVER FOR WHOEVER PICKS THIS UP: find the honest source shape worth
 * exactly 8 more bytes of declared locals that also tightens the three FP
 * spill slots from 12/8 spacing to 8/8. A 12-byte aggregate is too big and a
 * scalar reorder is too small; suspect either an 8-byte local or one more
 * live value in the setup block that I folded into a register. decomp-permuter
 * is NOT installed in this WSL instance (tools/permuter_pass.py expects
 * ~/conker/tools/decomp-permuter, which does not exist here) -- installing it
 * is probably the cheapest way to finish this one.
 *
 * NOT A BLOCKER: no rodata migration needed. D_800AA474/478 live in
 * asm/data/24EF20.rodata.s (7 glabels) and D_800BE9A4 is already in
 * variables.h -- all real globals, correctly spelled `extern f32`.
 * func_15143E64 is a 3-component vector length (sqrt of sum of squares),
 * `f32 func_15143E64(struct17 *)` in the already-matched game_16EE20.
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
    Obj151B65D4 *obj;
    f32 dist;
    Vec151B6320 delta;
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
    f32 stepAngle;
    f32 stepRadius;

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
        pos = payload->unk8;
        scale = 1.0f / count;
        age = payload->unk18 + D_800BE9A4;
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
