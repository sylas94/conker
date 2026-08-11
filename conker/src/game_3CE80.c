#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern struct180 D_80096320;
extern struct180 D_80096338;
extern struct180 D_80096350;
extern struct180 D_80096368;
extern struct180 D_80096380;

extern f32 D_800DCDA4;
extern f32 D_800DCDA8;
extern f32 D_800DCDAC;
extern f32 D_800DCDB0;
extern f32 D_800DCDB4;
extern f32 D_800DCDB8;
extern f32 D_800DCDBC;
extern f32 D_800DCDC0;

typedef struct {
    u8  pad0[0x28];
    s16 unk28;
    s16 unk2A;
    s16 unk2C;
    s16 unk2E;
    s8  unk30;
} Struct1500F9D0;

s32 func_1500F9D0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    Struct1500F9D0 *temp;

    temp = (Struct1500F9D0 *)func_151491F4((s16)((func_150ADA20() & 0x7F) + 0xA), 1, -1, 1, 0, 0xA, 0xFF, 0);
    if (temp != 0) {
        temp->unk28 = arg0;
        temp->unk2A = arg1;
        temp->unk2C = arg2;
        temp->unk2E = arg3;
        temp->unk30 = arg4;
    }
}

void func_1500FA64(void) {
    struct179 tmp;

    tmp.unk20 = 0;

    tmp.unk4 = *(struct180 *)&D_80096320;
    tmp.unk0 = 1;
    tmp.unk1C = fabsf(tmp.unk4.unk4 - tmp.unk4.unk10);
    func_151ACBD4(&tmp, 0);

    tmp.unk4 = *(struct180 *)&D_80096338;
    tmp.unk0 = 2;
    tmp.unk1C = fabsf(tmp.unk4.unk4 - tmp.unk4.unk10);
    func_151ACBD4(&tmp, 0);

    tmp.unk4 = *(struct180 *)&D_80096350;
    tmp.unk0 = 3;
    tmp.unk1C = fabsf(tmp.unk4.unk4 - tmp.unk4.unk10);
    func_151ACBD4(&tmp, 0);

    tmp.unk4 = *(struct180 *)&D_80096368;
    tmp.unk0 = 4;
    tmp.unk1C = fabsf(tmp.unk4.unk4 - tmp.unk4.unk10);
    tmp.unk4 = *(struct180 *)&D_80096380;
    tmp.unk0 = 5;
    tmp.unk1C = fabsf(tmp.unk4.unk4 - tmp.unk4.unk10);
    func_151ACBD4(&tmp, 0);

    func_1500F9D0(-0x6E7, -0x46A, 0x421, -0x648, 1);
    func_1500F9D0(-0xA71, 0x71B, 0x82B, -0x602, 2);
    func_1500F9D0(-0x870, 0x36E, 0x4E1, -0x602, 2);
    func_1500F9D0(-0xBD5, 0x3F1, 0x659, -0x602, 2);
    func_1500F9D0(-0xE6B, -0x263, -0x427, -0x647, 1);

    D_800DCDA4 = (f32)(u32)((u8 *)&D_800DCD20)[0];
    D_800DCDA8 = (f32)(u32)((u8 *)&D_800DCD20)[1];
    D_800DCDAC = (f32)(u32)((u8 *)&D_800DCD20)[2];
    D_800DCDB0 = (f32)(u32)D_800DCD28[0];
    D_800DCDB4 = (f32)(u32)D_800DCD28[1];
    D_800DCDB8 = (f32)(u32)D_800DCD28[2];
    D_800DCDBC = (f32)(u32)D_800DCD3C;
    D_800DCDC0 = (f32)(u32)D_800DCD3D;
}
