/* PARK 2026-10-08 (wave 10C): mism 130, BLOCKED rodata too: needs literals 4.04/0.4/-0.9/0.1/0.9 (golden hoists the loads out of a loop with calls) but block 244CD0 is shared with asm game_EF410 func_150C1F60; a yaml split at 0x244CF0 might free it. Residue: golden does or s0,v0; andi t7,s0,0xFF; or s0,t7 for angle = rand(); ours fuses into one andi. Refuted: u8/s32/u32 angle, &0xFF, %256, s32 return shadow, block-local init. */
#include <ultra64.h>
#define func_150ADA20 func_150ADA20_hdr
#include "functions.h"
#undef func_150ADA20
#include "variables.h"


s32 func_15142314(s32, s32, s32);
extern u32 func_150ADA20(void);

typedef struct {
    char pad_0[0x1D4];
    s32 field_0x1D4;
} ActorFields;

s32 func_150C19C0(s32 arg0, ActorFields *arg1, u8 arg2) {
    s32 sp1C;

    switch (arg2) {
    case 1:
        sp1C = 0x18;
        break;
    case 2:
        sp1C = 0x15;
        break;
    }

    func_15142314(arg1->field_0x1D4, sp1C, arg0);
    return 1;
}

s32 func_150C1A2C(s32 arg0, s32 arg1) {
    return 0x7;
}

typedef struct {
    /* 0x00 */ f32 unk00;
    /* 0x04 */ f32 unk04;
    /* 0x08 */ f32 unk08;
    /* 0x0C */ f32 unk0C;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ f32 unk40;
    /* 0x44 */ f32 unk44;
    /* 0x48 */ f32 unk48;
    /* 0x4C */ f32 unk4C;
    /* 0x50 */ s32 unk50;
    /* 0x54 */ s16 unk54;
    /* 0x56 */ s16 unk56;
    /* 0x58 */ u8 unk58;
    /* 0x59 */ u8 pad59[3];
    /* 0x5C */ s32 unk5C;
    /* 0x60 */ u8 unk60;
    /* 0x61 */ u8 unk61;
    /* 0x62 */ u8 unk62;
    /* 0x63 */ u8 unk63;
    /* 0x64 */ u8 unk64;
    /* 0x65 */ u8 unk65;
    /* 0x66 */ u8 unk66;
    /* 0x67 */ u8 unk67;
    /* 0x68 */ u8 unk68;
    /* 0x69 */ u8 pad69;
    /* 0x6A */ u8 unk6A;
    /* 0x6B */ u8 pad6B;
    /* 0x6C */ s32 unk6C;
    /* 0x70 */ u8 unk70;
    /* 0x71 */ u8 pad71;
    /* 0x72 */ s16 unk72;
    /* 0x74 */ s16 unk74;
    /* 0x76 */ u8 pad76[6];
} Struct150C1A40Particle;

typedef struct {
    u8 pad0[0x3B];
    u8 unk3B;
    u8 pad3C[0x3A];
    u16 unk76;
    u8 pad78[0xD4];
    f32 unk14C;
    f32 unk150;
    u8 pad154[0x2C];
    f32 unk180;
    u8 pad184[0x50];
    s32 unk1D4;
} Struct150C1A40;

extern void func_1514C2F0(f32 arg0, f32 arg1, f32 arg2, f32 arg3,
                          u8 arg4, s8 arg5, s16 arg6, u8 arg7,
                          s32 arg8, f32 arg9, s32 arg10, u8 arg11);
extern void func_15165F80(s32, s32, s32, s32, s32, s32, s32, s32, s32);
extern void *func_15132A4C(void *, s32, s32, s32, u8, s32);

void func_150C1A40(Struct150C1A40 *arg0, s32 arg1, s32 arg2) {
    struct17 pos;
    f32 half;
    Struct150C1A40Particle p;
    f32 radius;
    u8 dir;
    s32 n;
    u8 angle;
    f32 speed;
    f32 c;
    f32 s;

    if (arg0->unk1D4 != 0) {
        half = (arg0->unk14C + arg0->unk150) * 0.5f;
        func_150C19C0((s32)&pos, (ActorFields *)arg0, arg1);
        dir = (arg0->unk76 >> 8) + 0x40;
        radius = half * 70.0f;
        func_1514C2F0(pos.unk0, arg0->unk180, pos.unk8, radius, dir, (arg1 == 1) ? 0x10 : -0x10, 8, 0, 0, radius * 4.04f, 0, 0xFF);
        func_15165F80(-1, pos.unk0, (s32)arg0->unk180 + 2.0f, pos.unk8, 8, 0x15, 0, 0xFF, 0);
        p.unk56 = 5;
        p.unk50 = 0x29E9;
        p.unk58 = 0;
        p.unk5C = 0;
        p.unk60 = 0xFF;
        p.unk61 = 1;
        p.unk62 = 0;
        p.unk63 = 0;
        p.unk64 = 0;
        p.unk65 = 0;
        p.unk66 = 0;
        p.unk67 = 0;
        p.unk68 = 0;
        p.unk6A = 1;
        p.unk6C = (s32)arg0;
        p.unk1C = 1.0f;
        p.unk20 = 1.0f;
        p.unk24 = 1.0f;
        p.unk04 = 0.4f;
        p.unk48 = 0.0f;
        p.unk4C = -0.9f;
        p.unk70 = arg0->unk3B;
        p.unk72 = 0x10;
        p.unk74 = 0xF;
        n = (func_150ADA20() & 7) + 5;
        while (n--) {
            angle = func_150ADA20();
            speed = (func_150ADA68() * 0.9f + 0.1f) * 9.0f * half;
            c = func_151423D8(angle - 0x40);
            s = func_151423D8(angle);
            p.unk54 = (func_150ADA20() & 0xF) + 0x1E;
            p.unk28 = radius * c + pos.unk0;
            p.unk2C = arg0->unk180 + 2.0f;
            p.unk30 = radius * s + pos.unk8;
            p.unk34 = speed * c;
            p.unk38 = speed + speed;
            p.unk3C = speed * s;
            p.unk00 = p.unk0C = p.unk08 = (func_150ADA68() * 0.9f + 0.1f) * half * 1.5f;
            p.unk10 = func_150ADA68() * 360.0f;
            p.unk14 = func_150ADA68() * 360.0f;
            p.unk18 = func_150ADA68() * 360.0f;
            p.unk40 = 25.0f - func_150ADA68() * 50.0f;
            p.unk44 = 25.0f - func_150ADA68() * 50.0f;
            {
                void *ret = func_15132A4C(&p, 3, 0xFF, 4, 0xFF, 0);

                if (ret != NULL) {
                    *(f32 *)((u8 *)ret + 0x170) = arg0->unk180;
                }
            }
        }
    }
}

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    char padC[0xA];
    s16 unk16;
    s16 unk18;
    s16 unk1A;
    s16 unk1C;
    s16 unk1E;
    s16 unk20;
    s16 unk22;
    s16 unk24;
    s16 unk26;
    u8 unk28;
    u8 unk29;
    u8 unk2A;
    u8 unk2B;
    u8 unk2C;
    u8 unk2D;
    u8 unk2E;
    u8 unk2F;
    u8 unk30;
    u8 unk31;
} Struct150C1E34Stack;

extern f64 D_800A0228;
extern void func_151429E0(u8, u8 *, u8 *, u8 *);
extern void func_1518CA80(void *, u8);

s32 func_150C1E34(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7,
                  s32 arg8, s32 arg9, s32 argA, s32 argB, f32 argC) {
    Struct150C1E34Stack sp1C;

    sp1C.unk0 = arg2;
    sp1C.unk4 = arg3;
    sp1C.unk8 = arg4;
    sp1C.unk1E = (arg2 - arg5) * 10.0f;
    sp1C.unk20 = (arg4 - arg7) * 10.0f;
    sp1C.unk16 = sp1C.unk18 = argC;
    sp1C.unk1C = sp1C.unk1A = argC * D_800A0228;
    sp1C.unk22 = 150;
    sp1C.unk24 = 20;
    sp1C.unk26 = 600;
    func_151429E0(0, &sp1C.unk28, &sp1C.unk29, &sp1C.unk2A);
    func_151429E0(0, &sp1C.unk2B, &sp1C.unk2C, &sp1C.unk2D);
    sp1C.unk2E = 0xFF;
    sp1C.unk2F = 0xFF;
    sp1C.unk30 = (func_150ADA20() % 16U) + 12;
    sp1C.unk31 = 1;
    func_1518CA80(&sp1C, 1);
    return 1;
}
