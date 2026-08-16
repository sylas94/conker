#include <ultra64.h>
#include "functions.h"
#include "variables.h"

struct Vec3F1518A3C0 {
    f32 x;
    f32 y;
    f32 z;
};

extern s32 D_8008D5B0[];
extern s32 D_8008D5B8[];
extern void *func_151580B0(void *, s32, s32, u8, s32, u8, s32);

void *func_1518A3C0(struct Vec3F1518A3C0 *arg0, struct Vec3F1518A3C0 *arg1, f32 arg2, struct Vec3F1518A3C0 *arg3, struct Vec3F1518A3C0 *arg4, f32 arg5, f32 arg6, u8 arg7, s16 arg8, u8 arg9, s32 argA, u8 argB, s32 argC) {
    void *ret;
    struct {
        u8 unk00[1];
        u8 unk01[1];
        u8 unk02[1];
        u8 unk03[1];
        s16 unk04;
        u8 unk06;
        u8 pad07;
        s32 unk08;
        s32 unk0C;
        s32 unk10;
        s32 unk14;
        s32 unk18;
        s32 unk1C;
        s32 unk20;
        u8 unk24;
        u8 unk25;
        u8 pad26[2];
        u8 unk28;
        u8 unk29;
        u8 unk2A;
        u8 unk2B;
        u8 unk2C;
        u8 unk2D;
        u8 unk2E;
        u8 unk2F;
        s32 unk30;
        u8 unk34;
        u8 unk35;
        u8 pad36[2];
        struct Vec3F1518A3C0 unk38;
    } sp68;
    struct {
        struct Vec3F1518A3C0 unk00;
        f32 unk0C;
        struct Vec3F1518A3C0 unk10;
        struct Vec3F1518A3C0 unk1C;
        f32 unk28;
        f32 unk2C;
    } sp38;
    struct {
        s16 unk00;
        u8 pad02[2];
        s32 unk04;
    } sp30;

    sp38.unk00 = *arg1;
    sp38.unk10 = *arg3;
    sp38.unk1C = *arg4;
    sp38.unk0C = arg2;
    sp38.unk28 = arg5;
    sp38.unk2C = arg6;
    sp68.unk00[0] = arg7;
    sp68.unk02[0] = 1;
    sp68.unk03[0] = 1;
    sp68.unk04 = arg8;

    if (arg9) {
        sp68.unk06 = D_8008D5B8[func_150ADA20() & 1];
    } else {
        sp68.unk06 = D_8008D5B0[func_150ADA20() & 1];
    }

    sp68.unk0C = 0x220205;
    sp68.unk10 = 0x40600;
    sp68.unk25 = 7;
    sp68.unk14 = 1;
    sp68.unk18 = 0x4A;
    sp68.unk1C = 0x80;
    sp68.unk20 = 0x20;
    sp68.unk08 = 0;
    sp68.unk24 = 0;
    sp68.unk01[0] = 1;
    sp68.unk28 = 0xFF;
    sp68.unk29 = 0xFF;
    sp68.unk2A = 0xFF;
    sp68.unk2B = 0xFF;
    sp68.unk2C = 0xFF;
    sp68.unk2D = 0xFF;
    sp68.unk2E = 0xFF;
    sp68.unk2F = 0xFF;
    sp68.unk30 = 0;
    sp68.unk34 = 0;
    sp68.unk35 = 2;
    sp68.unk38 = *arg0;

    sp30.unk00 = 0xC;
    sp30.unk04 = 0x15;

    ret = func_151580B0(&sp68, 3, 0xFF, 1, argA + 0x38, argB, argC);
    if (ret == 0) {
        return 0;
    }
    memcpy((u8 *)ret + 0xF8, &sp30, 8);
    memcpy((u8 *)ret + 0x100, &sp38, 0x30);
    return ret;
}

// NEAR-MISS 990 (wave 60). Instruction MULTISET is identical to golden -- same count, same
// opcodes, same registers, same frame (0x48), same stack slots; the residual is pure
// list-scheduler tie-breaking in three spots: (a) the `lui/addiu a3,%hi/%lo(D_800BE9A4)` pair
// is emitted before `lw a1,0x48(sp)` in golden and interleaved after it here; (b) the 0.5f
// `lui at,0x3f00` is the first instruction of the post-loop block in golden (and is what the
// `beqzl` delay slot duplicates) while we schedule `lwc1 f8,0x10(v1)` there; (c) `li v0,1`
// (the `return 1`) lands late in golden and early here. BAIL SIGNATURE: unsteerable
// scheduling residual. Candidate kept in tools/nearmiss/func_1518A5F4.c.
//
// WHAT IS PROVEN -- do not re-derive:
//  * this is the same physics step as the MATCHED func_15157AA8 in game_183640.c; reuse its
//    MotionState/MotionVec model and its exact spelling
//    `posX += (oldVel.x + 0.5f * accelX * D_800BE9A4) * D_800BE9A4;`. The object layout here
//    is pos at +0x48/0x4C/0x50 and the MotionState at +0x100 (not +0x54/+0x120).
//  * `p = &arg0->motion;` MUST be written BEFORE the `func_15158AFC(arg0)` call. Written
//    after, IDO copy-propagates the +0x100 into every member offset (`lw at,0x110(a1)`) and
//    only materialises `v1` at the loop; written before, it rematerialises
//    `addiu v1,a1,0x100` from the reloaded parameter exactly where golden has it. 1405 -> 990.
//  * the damping loop is `for (i = D_800BE9E4; i != 0; i--)`, unrolled x4 by IDO with the
//    `-(n&3)` remainder prologue -- reproduced byte-for-byte with no Makefile flag change
//    (LOOP_UNROLL is empty; -O2 -g3 unrolls this on its own).
//  * declaration list `MotionState *p; MotionVec oldVel; f32 accelX, accelY, accelZ; s32 i;`
//    gives golden's frame and slots exactly; moving `i` earlier is free (990 either way).
//  * spellings that are WORSE: `accelX * 0.5f * dt` (1020); interleaving each accel with its
//    own position update (4464). `(0.5f*accelX)*dt` and `x = x + ...` are neutral (990).
//  * permuter: selftest PASS at base 990, ~30 min at -j 4, never beat 990.
//
// WAVE 61 -- the residual was re-read and NAMED. Both remaining spots are the same IDO
// behaviour, not two independent ties: golden materialises a CONSTANT AT THE HEAD OF ITS
// BASIC BLOCK and we interleave it.
//   (a) golden emits `lui a3,%hi(D_800BE9A4) / addiu a3,a3,%lo(...)` as an ADJACENT PAIR
//       immediately after the func_15158AFC call and before `lw a1,0x48(sp)`; we split the
//       pair and thread `lw a1` / `addiu t6,sp,0x38` / `addiu v1,a1,0x100` through it.
//   (b) golden's post-loop block begins with `lui at,0x3f000000>>16` (the 0.5f, into $f18),
//       which is why TWO branch-likely delay slots (`beql` at 0x6cc and `beqzl` at 0x30c)
//       both duplicate it; ours begins with `lwc1 $f8,0x10(v1)` so the delay slots differ.
// This is the SAME signature that was cracked on game_20A290/func_151DCDE0 in this wave --
// there golden hoisted a constant load into the prologue and the cause turned out to be
// real (the value was a FLOAT LITERAL in an owned .rodata pool, not the `extern f32` it had
// been modelled as; IDO schedules a literal as a constant and hoists it, and the pool's own
// ordering proved it). Checked here and NOT the same cause: D_800BE9A4 is loaded seven
// times through `lwc1 $f0,0x0($a3)` in golden, so it is a genuine global re-read and not a
// named local, and the 0.5f is already a literal (lui+mtc1, low16 == 0, no pool entry). So
// (a)/(b) remain a scheduler ranking difference with no source lever found. Still parked.
#pragma GLOBAL_ASM("asm/nonmatchings/game_1B7870/func_1518A5F4.s")


struct Sub1518A914 {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
};

struct Foo1518A914 {
    char pad0[0x48];
    /* 0x48 */ f32 unk48;
    /* 0x4C */ f32 unk4C;
    /* 0x50 */ f32 unk50;
    char pad54[0x100 - 0x54];
    /* 0x100 */ struct Sub1518A914 unk100;
};

s32 func_1518A914(Mtx *arg0, struct Foo1518A914 *arg1) {
    struct Sub1518A914 *p = &arg1->unk100;
    f32 sp24[4][4];

    func_150A8050(sp24, p->unk0, p->unk4, p->unk8);
    sp24[3][0] = arg1->unk48;
    sp24[3][1] = arg1->unk4C;
    sp24[3][2] = arg1->unk50;
    sp24[0][0] *= p->unkC;
    sp24[0][1] *= p->unkC;
    sp24[0][2] *= p->unkC;
    sp24[1][0] *= p->unkC;
    sp24[1][1] *= p->unkC;
    sp24[1][2] *= p->unkC;
    sp24[2][0] *= p->unkC;
    sp24[2][1] *= p->unkC;
    sp24[2][2] *= p->unkC;
    guMtxF2L(sp24, arg0);
    return 1;
}
