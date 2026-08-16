#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern void func_1514C2F0(f32 arg0, f32 arg1, f32 arg2, f32 arg3,
                          u8 arg4, s8 arg5, s16 arg6, u8 arg7,
                          s32 arg8, f32 arg9, s32 arg10, u8 arg11);

s32 func_15147DA0(void *arg0, void *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5,
                  s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 arg10, s32 *arg11,
                  s32 arg12, u8 arg13, s32 arg14);

void func_150C1660(f32 arg0, f32 arg1, f32 arg2, u8 arg3) {
    func_1514C2F0(arg0, arg1, arg2, 80.0f, 0, 3, 0x19, 2, 0, 0.0f, 0, arg3);
}

s32 func_150C16C0(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5,
                  s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 arg10, s32 arg11,
                  s32 arg12, s32 arg13, u8 arg14) {
    struct { f32 x; f32 y; f32 z; s16 unk0C; s16 unk0E; s32 unk10; u8 pad14; u8 unk15; s32 pad18; s32 pad1C; } sp108;
    struct { f32 unk00; f32 unk04; f32 unk08; f32 unk0C; f32 unk10; u8 pad14[4]; u8 unk18; u8 unk19; u8 unk1A; u8 unk1B; s32 pad1C; } spE8;
    struct { s32 unk00; s32 unk04; s32 unk08; s32 unk0C; s32 unk10; s32 unk14; s32 unk18; u8 unk1C; u8 unk1D; } spC8;
    s32 i;
    s16 ang;
    f32 mag;
    f32 spA;
    f32 spB;
    f32 spC;
    f32 spD;

    i = 1;
    spC8.unk00 = 0;
    spC8.unk04 = 1;
    spC8.unk08 = 0x160600;
    spC8.unk0C = 3;
    spC8.unk10 = 0x10;
    spC8.unk14 = 0x80;
    spC8.unk18 = 0x20;
    spC8.unk1C = 0;
    spC8.unk1D = 9;
    sp108.unk10 = 1;
    sp108.unk0E = 1;
    spE8.unk19 = 0xA;
    spE8.unk1A = 0xFF;
    spE8.unk18 = 0x28;
    spE8.unk1B = 0xFF;
    sp108.x = arg2;
    sp108.y = arg3;
    sp108.z = arg4;

    do {
        ang = (func_150ADA20() % 13U) - 0x3F;
        spA = func_151423D8((u8)ang);
        spB = func_151423D8((u8)(ang - 0x40));
        spC = func_151423D8((u8)arg8);
        spD = func_151423D8((u8)(arg8 - 0x40));
        mag = (func_150ADA68() * 17.4f) + 25.5f;
        sp108.unk15 = (func_150ADA20() % 9U) + 5;
        sp108.unk0C = (func_150ADA20() & 0x3F) + 0x5A;
        spE8.unk00 = (func_150ADA68() * 20.2f) + 24.7f;
        spE8.unk10 = (func_150ADA68() * 0.2f) + 0.4f;
        spE8.unk04 = (mag * spA) * spD;
        spE8.unk08 = -mag * spB;
        spE8.unk0C = (mag * spA) * spC;
        func_15147DA0(&sp108, &spE8, 0, 1, 5, 0, 0, 0, 0, 0, 0, (s32 *)&spC8, 0, arg14, 0);
        i--;
    } while (i != 0);
    return 1;
}

typedef struct {
    char pad[0x1B];
    u8 unk1B;
} SubStruct_150C1978;

typedef struct {
    char pad[0x1C];
    s16 unk1C;
    char pad2[0x98 - 0x1E];
    SubStruct_150C1978 *unk98;
} Struct_150C1978;

s32 func_150C1978(Struct_150C1978 *a0) {
    SubStruct_150C1978 *p = a0->unk98;
    s32 v1 = a0->unk1C << 3;
    if (v1 >= 0x100) {
        v1 = 0xFF;
    }
    p->unk1B = v1;
    if ((v1 & 0xFF) < 0) {
        return 0;
    }
    return 1;
}
