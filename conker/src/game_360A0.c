#include <ultra64.h>

#include "functions.h"
#include "variables.h"

/* structs.h's struct110 types offsets 0/2/4 as u8 and 0xC/0x10 as u8 as well; the
   golden code reads them with lh / lwc1.  File-local typedef per the usual policy. */
typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    u8  pad8[0x4];
    f32 unkC;
    f32 unk10;
    u8  pad14[0x2];
    u8  unk16;
    u8  pad17[0x4];
    u8  unk1B;
} Struct15008BF0Obj;

/* The 0x50-byte emitter descriptor handed to func_15189900 (struct145 in structs.h,
   but that copy types unk0/unk2/unk6 as u16 and unk28 as s32). */
typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    f32 unk30;
    f32 unk34;
    s16 unk38;
    s16 unk3A;
    f32 unk3C;
    f32 unk40;
    s16 unk44;
    s16 unk46;
    s32 unk48;
    s32 unk4C;
} Struct15008BF0Emit;

extern void func_15143874(s32, f32, f32 *, f32 *);
extern void func_15189900(Struct15008BF0Emit *, s32);

s32 func_15008BF0(Struct15008BF0Obj *arg0) {
    Struct15008BF0Emit sp28;
    f32 sp24;
    f32 sp20;

    arg0->unk16 |= 4;
    sp28.unk28 = arg0->unk6 * 0.19600000977516174f * 0.002188183832913637f;
    sp28.unk2C = 0.0f;
    sp28.unk48 = 4;
    sp28.unk4C = 2;
    sp28.unk38 = 100;
    sp28.unk3A = 100;
    sp28.unk44 = 40;
    sp28.unk46 = 20;
    sp28.unk30 = 7.0f;
    sp28.unk34 = 6.0f;
    sp28.unk20 = 20.100000381469727f;
    sp28.unk24 = 7.5f;
    sp28.unk3C = 0.4000000059604645f;
    sp28.unk40 = 0.6070000529289246f;
    sp28.unk0 = arg0->unk10 * 0.7111111283302307f;
    sp28.unk2 = 20;
    sp28.unk4 = (arg0->unkC * 0.7111111283302307f) - 64.0f;
    sp28.unk6 = 8;
    func_15143874((s16)(sp28.unk0 - 64), arg0->unk6, &sp20, &sp24);
    sp28.unk8 = arg0->unk0 - sp20;
    sp28.unkC = arg0->unk2;
    sp28.unk10 = arg0->unk4 - sp24;
    sp28.unk14 = sp20 + sp20;
    sp28.unk18 = 0.0f;
    sp28.unk1C = sp24 + sp24;
    func_15189900(&sp28, arg0->unk1B);
    return 1;
}
