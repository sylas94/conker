#include <ultra64.h>
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
} Struct1504715C; /* 0x24 */

u32 func_150ADA20(void);
f32 func_150ADA68(void);
void func_1504715C(Struct1504715C *, s32);
s32 func_15046C80(struct17 *, s32, f32, void *);
void func_151D3FF4(struct17 *, u8, s32);
void func_150E7FEC(f32, s32, void *, void *, s32, s32, s32, s32, s32, s32, s32, s32);
void func_150E83AC(struct17 *, s16, u8, s32);
void func_151D5404(struct17 *, f32, f32, f32, s32, s32, u8, s32);
void func_151D5334(struct17 *, f32, f32, f32, s32, u8, s32);
void func_151D5514(struct17 *, u8, s32);
void func_151D40D4(struct17 *, s32, s32, s32, s32, s32, s32, s32);
void func_15055A2C(s32, f32, f32, f32, s32);
void func_151541B8(struct17 *, f32, f32, f32, f32, u8, s32);

void func_15103E40(s32 arg0, s32 arg1, struct17 *arg2, u8 arg3, s32 arg4, u8 arg5, s32 arg6) {
    struct17 sp8C;
    u8 onGround;
    struct17 sp7C;
    Struct1504715C sp58;
    s32 soundA;
    s32 soundB;

    if (arg0 == 0) {
        return;
    }

    onGround = 0;
    func_151D3FF4(arg2, arg5, arg6);

    sp7C.unk0 = arg2->unk0;
    sp7C.unk4 = arg2->unk4 + 100.0f;
    sp7C.unk8 = arg2->unk8;
    func_1504715C(&sp58, arg1);

    if (func_15046C80(&sp7C, 0, arg2->unk4 - 100.0f, &sp58) != 0) {
        if (sp58.unk1C & 1) {
            sp8C.unk0 = sp7C.unk0;
            onGround = 1;
            sp8C.unk4 = sp58.unk00;
            sp8C.unk8 = sp7C.unk8;
            func_150E7FEC(func_150ADA68() * 125.0f + 204.0f,
                          (u8)((u32)func_150ADA20() % 0x65U + 0x9B), &sp58.unk04, &sp8C,
                          (u32)func_150ADA20() % 0x12EU + 0x1F4, 0, 1, 0, 0, 0, arg5, 0);
        }
    }

    func_150E83AC(onGround ? &sp8C : arg2, (s16)(func_150ADA20() % 0x3EU + 0x78), arg5, arg6);
    func_151D5404(arg2, 506.0f, 1013.0f, 0.0009871669f, 0xF, 0x14, arg5, arg6);
    func_151D5334(arg2, 506.0f, 1013.0f, 0.0009871669f, 5, arg5, arg6);
    func_151D5514(arg2, arg5, arg6);

    if (arg3 != 0) {
        if (arg3 == 2) {
            soundA = 0x42;
            soundB = 0x41;
        } else {
            soundA = 0x2B;
            soundB = 0x2A;
        }
        func_151D40D4(arg2, 0, arg0, arg1, 0, soundA, soundB, arg4);
    }

    func_15055A2C(0, arg2->unk0, arg2->unk4, arg2->unk8, 1);
    func_151541B8(arg2, func_150ADA68() * 4.0f + 12.0f, 1.6409999f,
                  (f32)(u32)(func_150ADA20() % 0x38U + 0xC8), 0.0f, arg5, arg6);
}
