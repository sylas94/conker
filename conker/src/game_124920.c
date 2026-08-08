#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern f32 D_800A1BD8;
extern f32 sinf(f32);

struct Func150F7E20Sub {
    u8 pad0[0x18];
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
};

struct Func150F7E20Obj {
    u8 pad0[0x2C];
    f32 unk2C;
    f32 unk30;
    u8 pad34[0x28];
    u8 unk5C;
};

#pragma GLOBAL_ASM("asm/nonmatchings/game_124920/func_150F7470.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_124920/func_150F78B4.s")

s32 func_150F7E20(struct Func150F7E20Obj *arg0) {
    f32 temp;
    struct Func150F7E20Sub *sub;

    sub = (struct Func150F7E20Sub *)((u8 *)arg0 + 0x110);
    arg0->unk5C = sub->unk18 * D_800A1BD8;
    temp = (sinf(sub->unk1C) * sub->unk28) + sub->unk24;
    arg0->unk30 = temp;
    arg0->unk2C = temp;
    sub->unk1C = func_15144B68(sub->unk1C + (sub->unk20 * D_800BE9A4));
    sub->unk18 -= D_800BE9A4;
    if (sub->unk18 < 0.0f) {
        return 0;
    }
    return 1;
}

void func_150F7F58(struct210 *arg0, s16 arg1) {
    func_15140410(arg0, &arg0->unk110, &arg0->unk11C, arg1);
}

extern f32 func_150ADA68(void);
void func_151541B8(void *, f32, u32, f32, f32, u8, s32);
void func_151D3F14(void *, u8, s32);
struct126 *func_150FF288(struct127 *);
s32 func_150FF6E0(struct17 *, struct17 *, struct17 *, struct17 *, struct17 *, struct127 *, struct126 *);
void func_150FF474(struct17 *, struct17 *, s32, s32);
void func_151D4408(struct17 *, struct17 *, void *, struct127 *, f32, s32, s32);

typedef u8 Func150F9950Entry[0x40];

void func_150F7F8C(void *arg0, u8 arg1, s32 arg2) {
    f32 temp1;
    f32 temp0;

    temp0 = func_150ADA68();
    temp1 = func_150ADA68();
    func_151541B8(arg0, temp0 * 3.0f + 9.0f, 0x3F030C35, temp1 * 70.0f + 70.0f, 0.0f, arg1, arg2);
    func_151D3F14(arg0, arg1, arg2);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_124920/func_150F802C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_124920/func_150F81BC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_124920/func_150F85A0.s")

void func_150F884C(s32 arg0, s32 arg1) {
    s32 sp18[2];
    sp18[0] = arg1;
    func_151494E0((s32)&sp18, 0x3F);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_124920/func_150F887C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_124920/func_150F892C.s")

extern u8 D_800A1C40[];

void func_150F9720(u8 arg0) {
    struct { s32 unk0; u8 unk4; } sp18;
    sp18.unk0 = 0;
    sp18.unk4 = D_800A1C40[arg0 * 2];
    func_151494E0((s32)&sp18, 0x42);
    sp18.unk4 = D_800A1C40[arg0 * 2 + 1];
    func_151494E0((s32)&sp18, 0x42);
}

void func_150F9788(struct260 *arg0) {
}

void func_150F9788(struct260 *);

void func_150F9794(struct260 *arg0) {
    func_150F9788(arg0);
    func_1514933C(arg0);
}

void func_150F97C0(struct260 *arg0) {
    func_150F9788(arg0);
    func_15149368(arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_124920/func_150F97EC.s")

void func_150F9950(struct127 *arg0, s32 arg1, s32 arg2) {
    struct17 sp60[6];
    struct17 sp54;
    struct17 sp48;
    struct17 sp3C;
    struct17 sp30;
    struct126 *temp;

    temp = func_150FF288(arg0);
    if (temp != 0) {
        if (func_150FF6E0(sp60, &sp54, &sp48, &sp3C, &sp30, arg0, temp) != 0) {
            func_151D3F14(&sp54, ((u8 *)&arg1)[3], arg2);
            func_151D4408(&sp48, &sp3C, (*(Func150F9950Entry **)&arg0->unk1D4)[*((u8 *)temp + 2)], arg0, 1.0f, ((u8 *)&arg1)[3], arg2);
            func_150FF474(&sp54, sp60, ((u8 *)&arg1)[3], arg2);
        }
    }
}
