#include <ultra64.h>
#include "functions.h"
#include "variables.h"


extern void func_15132A4C(void *, s32, s32, s32, u8, s32);
extern void func_1518CA80(void *, u8);
extern void func_151429E0(u8, u8 *, u8 *, u8 *);

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
    u8 pad59[3];
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
    u8 pad69;
    /* 0x6A */ u8 unk6A;
    u8 pad6B;
    /* 0x6C */ s32 unk6C;
    /* 0x70 */ u8 unk70;
    u8 pad71;
    /* 0x72 */ s16 unk72;
    /* 0x74 */ s16 unk74;
    u8 pad76[2];
} Struct1518B6B0;

typedef struct {
    /* 0x00 */ f32 unk00;
    /* 0x04 */ f32 unk04;
    /* 0x08 */ f32 unk08;
    u8 pad0C[0xA];
    /* 0x16 */ s16 unk16;
    /* 0x18 */ s16 unk18;
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ s16 unk24;
    /* 0x26 */ s16 unk26;
    /* 0x28 */ u8 unk28;
    /* 0x29 */ u8 unk29;
    /* 0x2A */ u8 unk2A;
    /* 0x2B */ u8 unk2B;
    /* 0x2C */ u8 unk2C;
    /* 0x2D */ u8 unk2D;
    /* 0x2E */ u8 unk2E;
    /* 0x2F */ u8 unk2F;
    /* 0x30 */ u8 unk30;
    /* 0x31 */ u8 unk31;
    u8 pad32[6];
} Struct1518B6B0b;

void func_1518B6B0(f32 arg0, f32 arg1, f32 arg2, u8 arg3, s32 arg4) {
    s32 i;
    Struct1518B6B0 sp;
    Struct1518B6B0b sp2;
    f32 scale;
    f32 speed;
    f32 sinYaw;
    f32 cosYaw;
    f32 sinPitch;
    f32 cosPitch;
    f32 spread;
    u8 yaw;
    u8 pitch;

    sp.unk04 = 0.4f;
    sp.unk56 = 4;
    sp.unk1C = 1.0f;
    sp.unk20 = 1.0f;
    sp.unk24 = 1.0f;
    sp.unk48 = 0.0f;
    sp.unk4C = -1.3f;
    sp.unk50 = 0x29E8;
    sp.unk58 = 0;
    sp.unk5C = 0;
    sp.unk60 = 0xFF;
    sp.unk61 = 1;
    sp.unk62 = 0;
    sp.unk63 = 0;
    sp.unk64 = 0;
    sp.unk65 = 0;
    sp.unk66 = 0;
    sp.unk67 = 0;
    sp.unk68 = 0;
    sp.unk6A = 2;
    sp.unk6C = 0;
    sp.unk70 = 0;
    sp.unk72 = 0x4000;
    sp.unk74 = 0;

    for (i = (func_150ADA20() % 8U) + 3; i > 0; i--) {
        scale = (func_150ADA68() * 0.7f) + 0.3f;
        yaw = func_150ADA20() & 0xFF;
        pitch = -0x10 - (func_150ADA20() % 32U);
        speed = (func_150ADA68() * 10.0f) + 5.0f;
        sinYaw = func_151423D8((u8)(yaw - 0x40));
        cosYaw = func_151423D8(yaw);
        sinPitch = func_151423D8((u8)(pitch - 0x40));
        cosPitch = func_151423D8(pitch);
        spread = func_150ADA68() * 20.0f;
        sp.unk28 = (spread * sinYaw) + arg0;
        sp.unk2C = arg1;
        sp.unk30 = (spread * cosYaw) + arg2;
        sp.unk34 = speed * cosPitch * sinYaw;
        sp.unk38 = -speed * sinPitch;
        sp.unk3C = speed * cosPitch * cosYaw;
        sp.unk54 = (func_150ADA20() % 32U) + 0x14;
        sp.unk00 = scale;
        sp.unk08 = scale;
        sp.unk0C = scale;
        sp.unk10 = func_150ADA68() * 360.0f;
        sp.unk14 = func_150ADA68() * 360.0f;
        sp.unk18 = func_150ADA68() * 360.0f;
        sp.unk40 = 25.0f - (func_150ADA68() * 50.0f);
        sp.unk44 = 25.0f - (func_150ADA68() * 50.0f);
        func_15132A4C(&sp, 3, 0xFF, 0, arg3, arg4);
    }

    sp2.unk00 = arg0;
    sp2.unk04 = arg1;
    sp2.unk08 = arg2;
    sp2.unk16 = 0x1F4;
    sp2.unk18 = 0x1F4;
    sp2.unk1A = (func_150ADA20() % 16U) + 0x32;
    sp2.unk1C = (func_150ADA20() % 16U) + 0x32;
    sp2.unk1E = 0;
    sp2.unk20 = 0;
    sp2.unk22 = (func_150ADA20() % 201U) + 0x12C;
    sp2.unk24 = 0;
    sp2.unk26 = 0x258;
    func_151429E0(1, &sp2.unk28, &sp2.unk29, &sp2.unk2A);
    func_151429E0(1, &sp2.unk2B, &sp2.unk2C, &sp2.unk2D);
    sp2.unk2E = 0xFF;
    sp2.unk2F = 0xFF;
    sp2.unk30 = 0xA;
    sp2.unk31 = 0;
    func_1518CA80(&sp2, 1);
}
