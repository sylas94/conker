#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern f32 D_800A0068;

void func_150BDE90(void *arg0, u8 arg1, s32 arg2) {
    struct {
        void *unk0;
        u16 unk4;
        u16 unk6;
    } sp38;
    struct260 *temp_v0;

    sp38.unk0 = arg0;
    sp38.unk4 = 0;

    temp_v0 = func_15149130(0x12C, -1, 0x4F, -1, 0, 0x3C, (struct37 *)0x8, arg1, arg2);
    if (temp_v0 != NULL) {
        memcpy((void *)((s32)temp_v0 + 0x28), &sp38, 8);
    }
}

extern f32 D_800A0000;
extern f32 D_800A0004;

/* The 8-byte payload func_150BDE90 memcpys to +0x28 of the object it creates:
 * unk0 = the owner object, unk4 = the respawn countdown this function ticks. */
typedef struct {
    /* 0x00 */ void *unk0;
    /* 0x04 */ s16  unk4;
    /* 0x06 */ s16  unk6;
} EB340Spawn;

typedef struct {
    /* 0x00 */ u8  pad0[0xC];
    /* 0x0C */ u8  unkC;
    /* 0x0D */ u8  pad0D[0x1B];
    /* 0x28 */ EB340Spawn unk28;
} EB340Obj;

/* Same 0x58-byte particle-emitter descriptor as struct_150CF680 in game_FC5F0.c
 * and struct_151CAB78_sp90 in game_1F4650.c; func_1515548C memcpys 0x58 of it. */
typedef struct {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ u8  unk10;
    /* 0x11 */ u8  pad11;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ s16 unk18;
    /* 0x1A */ u8  unk1A;
    /* 0x1B */ u8  unk1B;
    /* 0x1C */ u8  unk1C;
    /* 0x1D */ u8  unk1D;
    /* 0x1E */ u8  unk1E;
    /* 0x1F */ u8  unk1F;
    /* 0x20 */ u8  unk20;
    /* 0x21 */ u8  unk21;
    /* 0x22 */ u8  unk22;
    /* 0x23 */ u8  unk23;
    /* 0x24 */ s32 unk24;
    /* 0x28 */ s32 unk28;
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ s32 unk30;
    /* 0x34 */ s32 unk34;
    /* 0x38 */ s32 unk38;
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ u8  unk40;
    /* 0x41 */ u8  unk41;
    /* 0x42 */ u8  pad42[2];
    /* 0x44 */ u8  unk44;
    /* 0x45 */ u8  pad45[3];
    /* 0x48 */ f32 unk48;
    /* 0x4C */ f32 unk4C;
    /* 0x50 */ f32 unk50;
    /* 0x54 */ f32 unk54;
} EB340Emitter;

/* Copied to +0x70 of the emitter object func_1515548C returns. */
typedef struct {
    /* 0x00 */ void *unk0;
    /* 0x04 */ u8   pad4[0x8];
    /* 0x0C */ u8   unkC;
    /* 0x0D */ u8   unkD;
    /* 0x0E */ u8   padE[0x2];
    /* 0x10 */ f32  unk10;
    /* 0x14 */ u8   pad14[0x44];
} EB340Payload;

extern void *func_1515548C(EB340Emitter *, s32, s32, s32, s32, u8, s32);

void func_150BDF0C(EB340Obj *arg0) {
    EB340Spawn *p;
    EB340Emitter sp94;
    void *temp;
    EB340Payload sp38;

    arg0->unk28.unk4 -= D_800BE9E4;
    p = &arg0->unk28;
    if (arg0->unk28.unk4 < 0) {
        sp94.unk0 = (func_150ADA68() * 270.0f) + -135.0f;
        sp94.unk4 = -120.0f;
        sp94.unk8 = (func_150ADA68() * 10.0f) + 3.0f;
        sp94.unkC = (func_150ADA68() * 17.0f) + 9.0f;
        sp94.unk10 = 0xAB;
        sp94.unk12 = 0x3E8;
        sp94.unk14 = 0x31;
        sp94.unk16 = 1;
        sp94.unk18 = 0xFF;
        sp94.unk1A = 7;
        sp94.unk1B = 0xFF;
        sp94.unk1C = 0xFF;
        sp94.unk1D = 0xFF;
        sp94.unk1E = (func_150ADA20() % 0x9CU) + 0x64;
        sp94.unk1F = 0xFF;
        sp94.unk20 = 0xFF;
        sp94.unk21 = 0xFF;
        sp94.unk22 = 0xFF;
        sp94.unk23 = 0xFF;
        sp94.unk24 = 0;
        sp94.unk28 = 0x200004;
        sp94.unk2C = 0x1F0601;
        sp94.unk30 = 3;
        sp94.unk34 = 0x22;
        sp94.unk38 = 0x80;
        sp94.unk3C = 0x20;
        sp94.unk40 = 0;
        sp94.unk41 = 7;
        sp94.unk44 = *((u8 *)p->unk0 + 0x23D);
        sp94.unk48 = 1.0f;
        sp94.unk4C = 1.0f;
        sp94.unk50 = 0.0f;
        sp94.unk54 = 0.0f;
        sp38.unk0 = p->unk0;
        sp38.unkD = 0;
        sp38.unkC = 0;
        sp38.unk10 = (func_150ADA68() * D_800A0000) + D_800A0004;
        temp = func_1515548C(&sp94, 0xA, 0, 0, 0x58, arg0->unkC, 0);
        if (temp != NULL) {
            memcpy((u8 *)temp + 0x70, &sp38, 0x58);
        }
        p->unk4 = (func_150ADA20() % 0x97U) + 0x19;
    }
}


void func_1516972C(struct102 *arg0);

void func_150BE150(struct102 *arg0, s32 **arg1, u8 arg2) {
    if (arg2 == 0x21) {
        if (*(s32 *)((u8 *)arg0 + 0x28) == (s32)arg1[0]) {
            func_1516972C(arg0);
        }
    } else if (arg2 == 0) {
        s32 *temp = arg1[0];
        if (*(s32 *)((u8 *)arg0 + 0x28) == temp[0xC6]) {
            func_1516972C(arg0);
        }
    }
}

extern f32 D_800BE9A4;

s32 func_150BE1C4(f32 *arg0) {
    arg0[5] += arg0[32] * D_800BE9A4;
    if (arg0[5] > 120.0f) {
        return 0;
    }
    return 1;
}

extern void func_1511650C(struct131 *arg0, s32, s32, f32);

void func_150BE210(struct131 *arg0) {
    if ((((u8 *)arg0)[0x73] & 3) == 3) {
        return;
    }
    func_1511650C(arg0, 1, 0x62C, 500.0f);
    if (((u8 *)arg0)[0x4F] & 4) {
        *(f32 *)((u8 *)arg0 + 0x84) += *(f32 *)((u8 *)arg0 + 0x64);
    } else if (270.0f < *(f32 *)((u8 *)arg0 + 0x84)) {
        *(f32 *)((u8 *)arg0 + 0x84) = 270.0f;
    }
    if (360.0f < *(f32 *)((u8 *)arg0 + 0x84)) {
        u16 a0 = *(u16 *)((u8 *)arg0 + 0x74);
        ((u8 *)arg0)[0x73] &= 0xFFFC;
        ((u8 *)arg0)[0x73] |= 3;
        *(f32 *)((u8 *)arg0 + 0x64) = 0.0f;
        func_100111C8(a0);
        *(u16 *)((u8 *)arg0 + 0x74) = 0;
    }
}

void func_150BE2E8(s16 *arg0) {
    f32 temp_f12;
    f32 temp_f2;
    f32 temp_f0;
    f32 temp_f14;
    f32 temp_f16;
    f32 temp_f18;
    f32 temp_f20;
    f32 temp_f22;

    temp_f0 = arg0[0x3E];
    temp_f2 = arg0[0x3F];
    temp_f12 = arg0[0x40];
    temp_f14 = arg0[0x41];
    temp_f16 = arg0[0x42];
    temp_f18 = arg0[0x43];
    temp_f20 = arg0[0x1E] * 0.00006103515625f;
    temp_f22 = arg0[0x1F] * 0.00006103515625f;
    temp_f20 -= temp_f20 * D_800A0068;
    temp_f22 += temp_f20 * D_800BE9E4;

    arg0[0x8] = (s32)((temp_f14 - temp_f0) * temp_f22 + temp_f0);
    arg0[0x9] = (s32)((temp_f16 - temp_f2) * temp_f22 + temp_f2);
    arg0[0xA] = (s32)((temp_f18 - temp_f12) * temp_f22 + temp_f12);
    if (1.0f < temp_f22) {
        temp_f22 = 1;
    }

    arg0[0x1E] = (s32)(temp_f20 * 16384.0f);
    arg0[0x1F] = (s32)(temp_f22 * 16384.0f);
}

s16 *func_150BE438(s16 *arg0, s32 arg1) {
    arg0[0] = 0x68;
    arg0[1] = D_800CC2D0[arg1].unk2E8;
    arg0[2] = 0xE;
    arg0[3] = D_800CC2D0[arg1].unk2E4;
    return arg0 + 4;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_EB340/func_150BE494.s")
