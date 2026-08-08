#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_100810/func_150D3360.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_100810/func_150D3A68.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_100810/func_150D3FD4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_100810/func_150D4300.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_100810/func_150D49C0.s")

extern s32 func_1514654C(struct127 *, struct126 *, s32, void *, void *, s32);
extern f32 D_800A09D0;
extern f32 D_800A09DC;

s32 func_150D4AE0(struct17 *arg0, struct17 *arg1, struct127 *arg2, struct126 *arg3) {
    void *sp30[2];
    void *sp28[2];

    if (arg2->unk1D4 != 0) {
        sp30[0] = &D_800A09D0;
        sp30[1] = &D_800A09DC;
        sp28[0] = arg0;
        sp28[1] = (void *)arg1;
        if (func_1514654C(arg2, arg3, 0, sp30, sp28, 2) != 0) {
            return 1;
        }
        return 0;
    }

    arg0->unk0 = arg2->x_position;
    arg0->unk4 = arg2->y_position + 100.0f;
    arg0->unk8 = arg2->z_position;
    arg1->unk0 = arg2->x_position;
    arg1->unk4 = arg2->y_position + 100.0f + 500.0f;
    arg1->unk8 = arg2->z_position;
    return 2;
}

extern void func_150D4C2C(void *);
extern void func_151478F4(void *);
extern void func_15147928(void *);

void func_150D4BD4(void *arg0) {
    func_150D4C2C(arg0);
    func_151478F4(arg0);
}

void func_150D4C00(void *arg0) {
    func_150D4C2C(arg0);
    func_15147928(arg0);
}

extern void func_1000FD38(void *, void *, s32);
extern void func_150D5124(void);
extern s8 D_8008FD8C;

void func_150D4C2C(void *arg0) {
    struct102 **s0;

    s0 = *(struct102 ***)((u8 *)arg0 + 0x98);
    if (D_8008FD8C < 5) {
        func_1000FD38(func_150D5124, s0, 0x5B3);
    }
    func_1000FD38(func_150D5124, s0, 0x5B4);
    func_1000FD38(func_150D5124, s0, 0x5BC);
    if (s0[3] != 0) {
        func_1516972C(s0[3]);
    }
    if (s0[4] != 0) {
        func_1516972C(s0[4]);
    }
}

struct Bar150D4CC4 {
    char pad48[0x48];
    f32 unk48;
};

struct Obj150D4CC4 {
    char pad18[0x18];
    u8 unk18;
    char pad19[0x170 - 0x19];
    s16 unk170;
    char pad172[0x2];
    f32 unk174;
};

extern s32 D_800A09C0[];
extern f32 D_800A0A14;

s32 func_150D4CC4(struct Obj150D4CC4 *arg0) {
    struct Bar150D4CC4 *v1 = (struct Bar150D4CC4 *)((char *)arg0 + 0x110);

    arg0->unk170 -= D_800BE9E4;
    if (arg0->unk170 < 0) {
        arg0->unk18 = D_800A09C0[func_150ADA20() & 3];
        arg0->unk170 = (func_150ADA20() & 7) + 3;
    }

    v1->unk48 = v1->unk48 + (arg0->unk174 - v1->unk48) * D_800A0A14;
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_100810/func_150D4D58.s")

// PERMUTER CANDIDATE / JUSTREG (best 105). Instruction stream is byte-identical --
// every opcode, immediate, branch polarity and delay slot matches; the ONLY residual is
// a t6<->t7 transposition on 20 lines (target: else-branch `lui %hi(D_800BE9E4)` = t6 and
// then-branch `sll` = t7; IDO gives the reverse, then keeps the swap for the rest of the
// function). IDO's temp rotation numbers the two ramp branches depth-first
// (then-lui, then-sll, else-lui, else-sll = t5,t6,t7,t8) where the target numbers the two
// %hi materializations first (t5,t6) and the two shifts after (t7,t8) -- no source form
// reorders that. Tried: `<<` vs `*`, compound vs plain RMW (110), `a<b` vs `b>a` operand
// order, `!=` guard vs three-way `else if` (1055), split vs chained `*arg4 = unk20 = pitch`.
// s32 func_150D5124(Snd150D5124 *arg0, s32 arg1, u32 *arg2, s32 arg3, s32 *arg4,
//                   s32 arg5, u16 *arg6) {
//     // Src150D5124 { struct127 *unk0; u8 pad4; u8 unk5; }
//     // Snd150D5124 { s16 unk0,unk2,unk4,unk6; u8 pad8[4]; s32 unkC; u8 pad10[8];
//     //               Src150D5124 *unk18; s32 unk1C; s16 unk20; u8 pad22[2]; u16 unk24; }
//     Src150D5124 *src; s32 soundId; s32 volume; s32 pitch;
//     s32 targetVolume; s32 targetPitch;
//     targetVolume = 0; targetPitch = 0;
//     soundId = arg0->unk1C; src = arg0->unk18; volume = arg0->unkC; pitch = *arg4;
//     if (soundId == 0x5B3) {
//         if (src->unk0 != 0) {
//             targetVolume = src->unk0->unk28 * 25.0f;
//             if (targetVolume > 5000) { targetVolume = 5000; }
//             else if (targetVolume < 500) { targetVolume = 0; }
//             targetPitch += src->unk0->unk28 * 5.0f;
//             if (targetPitch > 1000) { targetPitch = 1000; }
//         }
//         if (src->unk5 == 2) { targetVolume += 7000; }
//         else if (src->unk5 == 1) { targetPitch = 400; targetVolume += 7000; }
//         else { targetPitch = 400; if (targetVolume != 0) { volume = targetVolume; } }
//     } else if (soundId == 0x5BC) {
//         targetVolume = 24000;
//         if (src->unk5 == 0) { volume = targetVolume; } else { targetVolume = 400; }
//     } else if (soundId == 0x5B4) {
//         if (src->unk5 == 0) { targetVolume = 16000; targetPitch = 400; volume = targetVolume; }
//         else if ((src->unk5 == 1) || (D_8008FD8C >= 5)) { targetVolume = 12000; }
//         else { targetPitch = 400; }
//     }
//     if (volume != targetVolume) {
//         if (volume < targetVolume) {
//             volume += D_800BE9E4 * 256;
//             if (volume > targetVolume) { volume = targetVolume; }
//         } else {
//             volume -= D_800BE9E4 * 256;
//             if (volume < targetVolume) { volume = targetVolume; }
//         }
//     }
//     if (pitch != targetPitch) {
//         if (pitch < targetPitch) {
//             pitch += D_800BE9E4 * 256;
//             if (pitch > targetPitch) { pitch = targetPitch; }
//         } else {
//             pitch -= D_800BE9E4 * 8;
//             if (pitch < targetPitch) { pitch = targetPitch; }
//         }
//     }
//     if (volume < 500) { volume = 0; }
//     else if (*arg6 == 0) { arg0->unk0 = soundId; *arg6 = soundId; }
//     arg0->unk2 = src->unk0->x_position;
//     arg0->unk4 = src->unk0->y_position;
//     arg0->unk6 = src->unk0->z_position;
//     if (D_800C35EA == 1) { arg0->unkC = volume >> 1; *arg2 = *arg2 >> 1; }
//     else { arg0->unkC = volume; }
//     *arg4 = arg0->unk20 = pitch;
//     if (*arg2 == 0) {
//         if (arg0->unk24 != 0) { func_100111C8(arg0->unk24); arg0->unk24 = 0; }
//         *arg6 = 0;
//     }
//     return 0;
// }
#pragma GLOBAL_ASM("asm/nonmatchings/game_100810/func_150D5124.s")
