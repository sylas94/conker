#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void func_1514C678(f32, f32, s32, f32, s32, s32, s32, s32, s32, f32, s32, s32);
void func_151D3FF4(struct17 *, u8, s32);
extern void func_151429E0(u8, u8 *, u8 *, u8 *);
extern void func_15156190(void *, u8, s32, u8, s32);
extern f32 D_8009F900;
extern f32 D_8009F904;
extern f32 D_8009F908;
extern f32 D_8009F90C;
extern f32 D_8009F910;
extern f32 D_8009F914;

s32 func_150B2480(s32 arg0, s32 arg1) {
    return 0xA;
}

void func_150B2494(struct127 *arg0, s32 arg1, s32 arg2) {
    struct17 sp3C;

    sp3C.unk0 = arg0->x_position;
    sp3C.unk4 = *(f32 *)((u8 *)arg0 + 0x180);
    sp3C.unk8 = arg0->z_position;
    func_1514C678(sp3C.unk0, sp3C.unk4, *(s32 *)&sp3C.unk8, 135.0f, 0, 0xFF,
                  (func_150ADA20() % 15U) + 0x1B, 7, 0, 0.0f, 0, 0xFF);
    func_151D5404(&sp3C, 1502.0f, 3000.0f, 0.00033333332976326346f, 0xC, 0xF, 0xFF, 0);
    func_151D3FF4(&sp3C, 0xFF, 0);
}

s32 func_150B2570(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5,
                  s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 arg10, s32 arg11,
                  s32 arg12, s32 arg13, u8 arg14) {
    s32 pad;
    u8 sp38[0x3C];
    s16 angle;
    f32 sp30;
    f32 sp2C;
    f32 sp28;
    f32 temp_f2;

    arg0 = arg8 - 0x40;
    sp30 = func_151423D8(arg0);
    sp2C = func_151423D8((u8)arg8);
    angle = (func_150ADA20() % 21U) - 0x1E;
    arg0 = angle - 0x40;
    sp28 = func_151423D8(arg0);
    temp_f2 = func_151423D8((u8)angle);
    temp_f2 = 10.0f * temp_f2;
    *(f32 *)&sp38[0x00] = arg2;
    *(f32 *)&sp38[0x04] = arg3;
    *(f32 *)&sp38[0x08] = arg4;
    *(f32 *)&sp38[0x0C] = temp_f2 * sp30;
    *(f32 *)&sp38[0x10] = -10.0f * sp28;
    *(f32 *)&sp38[0x14] = temp_f2 * sp2C;

    *(f32 *)&sp38[0x18] = (func_150ADA68() * D_8009F900) + D_8009F904;
    *(f32 *)&sp38[0x1C] = (func_150ADA68() * D_8009F908) + D_8009F90C;
    func_151429E0(8, &sp38[0x20], &sp38[0x21], &sp38[0x22]);
    func_151429E0(8, &sp38[0x24], &sp38[0x25], &sp38[0x26]);
    sp38[0x23] = 0xFF;
    sp38[0x27] = 0xFF;
    sp38[0x28] = 9;
    *(s16 *)&sp38[0x2A] = (func_150ADA20() % 7U) + 0x12;

    *(f32 *)&sp38[0x30] = (func_150ADA68() * D_8009F910) + D_8009F914;
    *(s16 *)&sp38[0x2C] = 0x1601;
    sp38[0x34] = 0xFF;
    *(s16 *)&sp38[0x36] = 8;
    *(s16 *)&sp38[0x38] = 0x1F;
    func_15156190(sp38, 1, 0, arg14, 1);
    return 1;
}
