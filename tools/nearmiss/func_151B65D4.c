/*
 * NEAR MISS: func_151B65D4  (game_1E37D0.c)  -- asm-differ 1398 (was 1533)
 *
 * mine 212 instructions / 848 B   vs   golden 213 / 852 B.
 * The whole-TU 1398 is inflated by downstream displacement; the bounded
 * per-symbol picture is 32 differing rows out of 1933 in the -o dump
 * (`<`=5 `>`=4 `r`=10 `|`=9 `s`=3 `i`=1), ALL of them inside a single
 * ~14-instruction window of the setup block between `lw at,8(t2)` and
 * `swc1 ...,0x48(sp)`.  Prologue, early-out, the whole do-while body, the
 * angle-wrap loop, the ring-buffer counters and the epilogue are identical.
 *
 * ============================================================
 * THE BIG RESULT THIS WAVE: IDO's frame layout is now SOLVED.
 * ============================================================
 * The previous revision's premise ("golden's declared-local area is 8 bytes
 * taller, with a dead 16-byte hole") was right about the symptom and wrong
 * about the mechanism -- it treated the aggregate block, the 'pad' and the
 * a2/t1 stores as three separate regions.  They are one region.  Calibrated
 * on the ALREADY-MATCHED sibling func_151B6320 in this same TU:
 *
 *   RULE.  EVERY declared auto gets a stack home, whether or not it ends up
 *   in a register.  The home area is exactly sum(sizeof(local)) bytes, it
 *   ENDS at framesize, and locals are laid out TOP-DOWN in DECLARATION
 *   ORDER.  Register-allocated locals simply never touch their home, which
 *   is what produces the "dead holes" in golden .s files.  Below the home
 *   area sits the compiler-temp area; below that the saved registers.
 *
 *       framesize = 72 + temp_area + sum(sizeof(local))     [this function]
 *       (72 = 16 outgoing-arg bytes + 0x10..0x3F fp saves + 0x40..0x47 ra)
 *
 *   Verified on func_151B6320 (frame 144, locals 64..143): top_dummy@140,
 *   header@116..139, pad_dummy@112, payload@68..111, temp_v0@64 -- exactly
 *   80 bytes, exactly the declaration order, no slack anywhere.  That is
 *   also the explanation for that function's `top_dummy`/`pad_dummy`.
 *
 *   Verified on this function 13 more times: every probe's frame size,
 *   aggregate offsets and a2/t1 store offsets are predicted exactly.
 *   `sw t1,X(sp)` / `sw a2,X+4(sp)` are NOT spill slots -- they are the
 *   HOMES of the first two declared locals (payload, trail).
 *
 * DECODING GOLDEN WITH THAT RULE.  Frame 184; a2/t1 stored at 180/176;
 * delta at 160 (`addiu a0,sp,0xa0` feeds func_15143E64); pos at 132
 * (`addiu a0,sp,0x84`).  So golden's declaration list is, top-down:
 *
 *     180 payload | 176 trail | 172 [1 word] | 160 delta (12)
 *     144 [4 words] | 132 pos (12) | 88..131 [11 words]
 *
 *   = 96 bytes of declared locals, temp area 16 bytes at 72..87.
 *   ONE word above delta, FOUR words between delta and pos, ELEVEN below.
 *   My previous list put THREE words above delta and NONE between.
 *
 * That reordering alone (e above delta; obj, dist below it) plus two more
 * words in the middle group reproduces golden's frame size and EVERY
 * aggregate offset:  1533 -> 1406 -> 1398.
 *
 * THE ONE OPEN QUESTION: `unknown0` / `unknown1` below.
 * Golden's frame PROVES 96 bytes of declared locals.  Every value this
 * function computes, named, comes to 88 (22 words).  Two words are
 * therefore declared in the original and never make it into the emitted
 * code.  They are NOT a frame-moving forcer of my invention -- the binary
 * demands them -- but they are also not identified, so THIS FILE MUST NOT
 * BE COMMITTED AS A MATCH until they are named or the score reaches 0.
 * Everything below was tried to dissolve them and FAILED:
 *   - widening `delta` and/or `pos` to 16 bytes: the only consumer of
 *     `&delta` is func_15143E64, which is LIVE MATCHED C in game_16EE20 and
 *     reads exactly 12 bytes (`sqrtf(x*x+y*y+z*z)`, `struct17` = 0x C bytes).
 *     There is no support for a 4th component.  Inverse case: the missing
 *     bytes belong to some OTHER local.
 *   - `Trail151B65D4 tmp;` (0x1C) spanning 132..159 exactly, with
 *     stepAngle/stepRadius written as in-loop loop-invariant expressions
 *     (semantically identical -- neither unk1C nor unk20 is written in the
 *     loop).  Fits the byte budget EXACTLY (24 words) but IDO then keeps one
 *     of them in a register: 210 instructions, 844 B, score 2987.
 *   - the same with only stepAngle inlined (W1 3246 / W3 3238), only
 *     stepRadius inlined (W2 1777), both inlined + padding (W4 3246,
 *     W5 2991).  Every inlining LOSES instructions; golden has one MORE
 *     than we do, so this whole basin is the wrong direction.
 *   - "88 declared + 24-byte temp area" (v_d88, 1777): the temp area is
 *     16 bytes in every single build ever measured here; it never grows.
 *   - 104 declared bytes (u1/u2/u3 1673, u4 1681, u5 1809, u6 1689): frame
 *     goes to 192.  92 declared (pgap4 1615, pdelta16 1631): frame 184 but
 *     pos lands at 136 and delta at 152.
 *
 * WHAT THE 32 REMAINING ROWS ARE.  Two things, both in the setup block:
 *  (a) a 4-byte shift of two spill slots.  golden stepRadius@72(temp)
 *      stepAngle@80(temp) count@88 ; mine stepRadius@72 count@84(temp)
 *      stepAngle@88.  MEASURED LAW (8 orderings, t0..t9): the third slot is
 *      always exactly stepAngle's declared HOME, and count and stepRadius
 *      always take the two compiler temps at 72 and 84.  In golden the roles
 *      are swapped -- the count value owns the home and stepAngle is a temp.
 *      Making stepAngle stop being a declared local is the only lever that
 *      does that, and it costs instructions (see above).  This is worth ~5
 *      rows.
 *  (b) a scheduling permutation of ~14 instructions: golden issues
 *      `addiu a0,sp,0x84` BEFORE the bc1f, loads payload->unk18 and
 *      D_800BE9A4 immediately after the div.s and computes
 *      `add.s $f18` (age) before the delta loads, and computes
 *      `sub.s $f14` (unk1C-unk20) before the mul block, leaving a third
 *      `nop` in it (golden 3 nops, mine 2 -- that IS the missing 213th
 *      instruction).
 *
 * STATEMENT-ORDER SWEEP (the cookbook's top lever) -- 136 builds, all
 * dependency-respecting permutations of the 12 head statements of the
 * `if (1.0f < payload->unk14)` block (16 hand-picked + 120 random, seed
 * 20260812).  NOTHING beats the order below.  Best random was 1456 (r035);
 * ties at 1398 came from o05/o06/o07/o09/o13/o14 (moving `count`/`pos`/
 * `scale` and the sAng/sRad tail around).  Twelve orders reached the
 * CORRECT 852-byte size (o15 2674, r003 2293, r027 1900, r042 2155,
 * r044 2065, r048 3791, r060 3195, r068 1651, r095 2733, r107 3899,
 * r108 3448, r110 3255, r116 2070) -- none of them near the optimum, so
 * the 213th instruction and the good schedule are not simultaneously
 * reachable on this axis.
 *
 * STILL TRUE FROM THE PREVIOUS REVISION (do not re-explore):
 *   2749 first cold write; 2699 + flipped comparisons; 2693 count removed
 *   (IDO re-loads instead of CSEing -- wrong direction); 2137 `count`
 *   moved inside the if so it has one def and one use (this is what makes
 *   golden's redundant swc1/lwc1 pair and is still in the code below);
 *   1681/1533/1713/.../2161 declaration-position sweep.
 *   IDO emits bne(RHS,LHS), so golden's `bne(unk25,unk2E)` needs source
 *   `unk2E == unk25` and `bne(unk4,unk3B)` needs `obj->unk3B != payload->unk4`.
 *
 * NEXT LEVER: make the count value own a declared home and stepAngle a
 * compiler temp WITHOUT losing an instruction, then re-run the statement
 * sweep.  The permuter has never been run on this function; the 1398 base
 * with its frame now exactly golden's is a genuinely good seed (gate with
 * PERMUTER_TU_REQUIRE_FRAME, base frame = 184 = golden).
 *
 * NOT A BLOCKER: no rodata migration needed.  D_800AA474/478 live in
 * asm/data/24EF20.rodata.s and D_800BE9A4 is in variables.h.
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
