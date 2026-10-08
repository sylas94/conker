#include <ultra64.h>
#include "functions.h"
#include "variables.h"

typedef struct {
    char pad_0[0x88];
    s32 field_0x88;
} Game1E30A0Data;


#pragma GLOBAL_ASM("asm/nonmatchings/game_1E30A0/func_151B5BF0.s")

typedef struct Sub151B5E94 {
    f32 unk0;
    f32 unk4;
} Sub151B5E94;

typedef struct Obj151B5E94 {
    u8 pad0[0x18];
    f32 unk18;
    f32 unk1C;
    u8 pad20[0x18];
    f32 unk38;
    f32 unk3C;
    f32 unk40;
    u8 pad44[0x12C];
    Sub151B5E94 unk170;
} Obj151B5E94;

extern f32 D_800AA434;
extern f32 D_800AA438;
extern f32 D_800AA43C;
extern f32 D_800AA440;
extern f32 sinf(f32);
extern void func_15133894(Obj151B5E94 *);

void func_151B5E94(Obj151B5E94 *arg0) {
    f32 temp;
    Sub151B5E94 *p;

    p = &arg0->unk170;
    p->unk0 += D_800AA434 * D_800BE9A4;
    if (p->unk0 > D_800AA438) {
        p->unk0 = 0.0f;
        func_10010F88(0x502, 0x5DC0, 0, 0, -1, arg0->unk38, arg0->unk3C, arg0->unk40, 100, 500);
    }
    if (p->unk0 < D_800AA43C) {
        f32 s = sinf(p->unk0);

        temp = p->unk4 + s * (D_800AA440 * p->unk4);
        arg0->unk1C = temp;
        arg0->unk18 = temp;
    } else {
        temp = p->unk4;
        arg0->unk1C = temp;
        arg0->unk18 = temp;
    }
    func_15133894(arg0);
}

void func_151B5FCC(Game1E30A0Data *arg0) {
    if (arg0->field_0x88 != 0) {
        func_100111C8(arg0->field_0x88);
        arg0->field_0x88 = 0;
    }
}
