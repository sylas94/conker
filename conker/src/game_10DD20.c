#include <ultra64.h>
#define func_150ADA20 func_150ADA20_hdr
#include "functions.h"
#undef func_150ADA20
#include "variables.h"


typedef struct {
    /* 0x00 */ f32 unk00;
    /* 0x04 */ f32 unk04;
    /* 0x08 */ f32 unk08;
    /* 0x0C */ f32 unk0C;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ u8  unk1C;
    /* 0x1D */ u8  pad1D[0x7];
} Struct150E0870Floor; /* 0x24 */

extern u32 func_150ADA20(void);
void func_1504715C(Struct150E0870Floor *, struct127 *);
s32 func_15046C80(struct17 *, s32, f32, Struct150E0870Floor *);
void func_151D3FF4(struct17 *, u8, s32);
void func_150E7FEC(f32, u8, void *, void *, s32, s32, s32, s32, s32, s32, u8, s32);
void func_150E83AC(struct17 *, s16, u8, s32);
void func_151D5334(struct17 *, f32, f32, f32, s32, u8, s32);
void func_151D5514(struct17 *, u8, s32);
void func_151D40D4(struct17 *, s32, struct127 *, struct127 *, s32, s32, s32, s32);
void func_151541B8(struct17 *, f32, f32, f32, f32, u8, s32);
void func_15136C3C(struct127 *, s32, s32, s32, s32, s32, u8, s32);

void func_150E0870(struct127 *arg0, u8 arg1, s32 arg2) {
    struct17 sp8C;
    struct17 sp80;
    u8 onGround;

    if (arg0 == NULL) {
        return;
    }
    if (D_800C35EA != 1) {
        func_10010630(0x2BB, arg0, 0x7FFF, 1000, 2000);
        func_10010630(0x2BA, arg0, 0x7FFF, 1000, 2000);
    }
    sp8C.unk0 = arg0->x_position;
    sp8C.unk4 = arg0->y_position + 20.0f;
    sp8C.unk8 = arg0->z_position;
    onGround = 0;
    {
        struct17 sp70;
        Struct150E0870Floor sp4C;

        sp70.unk0 = sp8C.unk0;
        sp70.unk4 = sp8C.unk4 + 100.0f;
        sp70.unk8 = sp8C.unk8;
        func_1504715C(&sp4C, arg0);
        if (func_15046C80(&sp70, 0, sp8C.unk4 - 200.0f, &sp4C) != 0) {
            if (sp4C.unk1C & 1) {
                sp80.unk0 = sp70.unk0;
                onGround = 1;
                sp80.unk4 = sp4C.unk00;
                sp80.unk8 = sp70.unk8;
                func_150E7FEC(func_150ADA68() * 125.0f + 204.0f,
                              func_150ADA20() % 0x65U + 0x9B, &sp4C.unk04, &sp80,
                              func_150ADA20() % 0x12EU + 0x1F4, 0, 1, 0, 0, 0, arg1, 0);
            }
        }
    }
    func_151D5404(&sp8C, 506.0f, 1013.0f, 0.0009871669f, 0xF, 0x14, arg1, arg2);
    func_151D5334(&sp8C, 506.0f, 1013.0f, 0.0009871669f, 5, arg1, arg2);
    func_151D5514(&sp8C, arg1, arg2);
    func_151D3FF4(&sp8C, arg1, arg2);
    func_150E83AC(onGround ? &sp80 : &sp8C, (s16)(func_150ADA20() % 0x3EU + 0x78), arg1, arg2);
    func_151541B8(&sp8C, func_150ADA68() * 4.0f + 12.0f, 1.6409999f,
                  (f32)(func_150ADA20() % 0x38U + 0xC8), 0.0f, arg1, arg2);
    func_15136C3C(arg0, 1, 1, 1, 1, 0, arg1, arg2);
    func_151D40D4(&sp8C, 0, arg0, arg0, 0, 0x16, 0x15, 0);
}

u8 func_150599C8(struct127 *arg0, u8 arg1, u16 arg2);
void func_15056B08(struct127 *arg0);
void func_150585F0(struct127 *arg0, f32 arg1);
s32 func_150535F4(struct127 *arg0);
void func_1502178C(struct127 *arg0, s32 arg1, s32 arg2);
extern u16 D_800CC346;

void func_150E0BE0(struct127 *arg0) {
    arg0->unkB0 = 0xF;
    arg0->unk80 = 0xA;
    if (arg0->unk87 != 0) {
        if (arg0->unk83 < 100) {
            arg0->unk83 += D_800BE9A0;
        }
        if (arg0->unk83 >= 5) {
            if (arg0->unk251 != 3) {
                arg0->unk78 = D_800CC346;
                arg0->unk218 = NULL;
                arg0->unk232 = 4;
                if (arg0->unk251 == 2) {
                    arg0->unk232 = 2;
                }
            }
        }
    } else {
        if (arg0->unk83 >= 0x3D) {
            D_800D1580 = 0xFF020133;
            D_800D154C = D_800CC2D0;
            func_1506E8D8();
            D_800D154C = arg0;
        }
        arg0->unk83 = 0;
    }
    if (arg0->unk232 == 4) {
        if (arg0->unk83 == 0) {
            arg0->unk78 = arg0->unk76;
        }
        func_150599C8(arg0, 3, arg0->unk78);
    }
    arg0->unk87 = 0;
    if (arg0->stunned == 0) {
        func_15056B08(arg0);
    } else {
        func_150585F0(arg0, 0.05f);
    }
    arg0->unk40 = ((s16)(arg0->unk7A + 0x4000)) * 0.005493164f;
    func_15059140(arg0);
    *(f32 *)&arg0->padBC = arg0->x_position - arg0->old_x_position;
    arg0->unk148 = arg0->z_position - arg0->old_z_position;
    if (func_150535F4(arg0) == 0) {
        func_1502178C(arg0, 0, -1);
    }
}
