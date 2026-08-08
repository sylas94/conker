#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern f32 D_800A8DB0;

extern void func_151A6F00(void *, s32, u8, s32);
extern void func_151D5334(void *, f32, f32, f32, s32, u8, s32);
extern void func_151D3FF4(void *, u8, s32);
extern void func_151D5514(void *, u8, s32);
extern void func_151541B8(void *, f32, s32, f32, f32, u8, s32);

#pragma GLOBAL_ASM("asm/nonmatchings/game_1D2B10/func_151A5660.s")

void func_151A5D2C(u16 arg0);

void func_151A5CAC(struct260 *arg0) {
    if (*(u16 volatile *)((u8*)arg0 + 0x6C) != 0) {
        func_151A5D2C(*(u16*)((u8*)arg0 + 0x6C));
    }
    func_1514933C(arg0);
}

void func_151A5CEC(struct260 *arg0) {
    if (*(u16 volatile *)((u8*)arg0 + 0x6C) != 0) {
        func_151A5D2C(*(u16*)((u8*)arg0 + 0x6C));
    }
    func_15149368(arg0);
}

void func_151A5D2C(u16 arg0) {
    func_100111C8(arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1D2B10/func_151A5D58.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1D2B10/func_151A5F70.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1D2B10/func_151A6068.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1D2B10/func_151A6350.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1D2B10/func_151A6600.s")

extern void func_1000FD38(void *, void *, s32);
extern s32 func_1000EF40();

void func_151A6AB8(struct210 *arg0) {
    struct102 *temp;
    *(u8 *)(*(s32 *)((u8 *)arg0 + 0x110) + 0x14) = 1;
    func_1000FD38(func_1000EF40, *(void **)((u8 *)arg0 + 0x110), 0);
    temp = *(struct102 **)((u8 *)arg0 + 0x120);
    if (temp != 0) {
        func_1516972C(temp);
    }
}

extern void func_151A6AB8(struct210 *);

void func_151A6B10(struct210 *arg0) {
    func_151A6AB8(arg0);
    func_1513CA6C(arg0);
}

void func_151A6B3C(struct210 *arg0) {
    func_151A6AB8(arg0);
    func_1513CAA0(arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1D2B10/func_151A6B68.s")

extern s32 D_800A5770;
extern s32 D_800DCE50[][0x68];
typedef struct Func151A6BD8Obj
{
  u8 pad0[8];
  struct Func151A6BD8Obj *next;
  u8 padC[7];
  u8 type;
  u8 pad14[0x14];
  s32 owner;
} Func151A6BD8Obj;
Func151A6BD8Obj *func_151A6BD8(s32 arg0)
{
  u8 i;
  u8 j;
  Func151A6BD8Obj *obj;
 i = 0; do {
    j = 0;
    do
    {
      obj = (Func151A6BD8Obj *) D_800DCE50[j][(&D_800A5770)[i]];
      if (obj != 0)
      {
        do
        {
          if ((obj->type == 0x2C) && (arg0 == obj->owner))
          {
            return obj;
          }
          obj = obj->next;
        }
        while (obj != 0);
      }
      next_j:
      j++;

    }
    while (j < 2);
    i++;

  }
  while (i < 2);
  return 0;
}


void func_151A6C90(void *arg0, u8 arg1, s32 arg2) {
    struct17 sp9C;
    struct {
        s16 unk00;
        u8 pad02[2];
        struct17 unk04;
        s16 unk10;
        u8 pad12[2];
        f32 unk14;
        s16 unk18;
        s16 unk1A;
        s16 unk1C;
        s16 unk1E;
        f32 unk20;
        f32 unk24;
        f32 unk28;
        f32 unk2C;
        f32 unk30;
        f32 unk34;
        f32 unk38;
        f32 unk3C;
        f32 unk40;
        f32 unk44;
        f32 unk48;
        f32 unk4C;
        f32 unk50;
        u8 unk54;
        u8 unk55;
        s16 unk56;
        s16 unk58;
    } sp40;

    sp9C.unk0 = *(f32 *)((u8 *)arg0 + 0x14);
    sp9C.unk4 = *(f32 *)((u8 *)arg0 + 0x18);
    sp9C.unk8 = *(f32 *)((u8 *)arg0 + 0x1C);

    if (arg0 != 0) {
        sp40.unk00 = (func_150ADA20() & 3) + 6;
        sp40.unk04 = sp9C;
        sp40.unk14 = 60.0f;
        sp40.unk20 = (f32)(s16)0;
        sp40.unk30 = 0.0f;
        sp40.unk10 = 0x50;
        sp40.unk18 = 0;
        sp40.unk1A = 0xFF;
        sp40.unk1C = -0x3F;
        sp40.unk24 = 35.0f;
        sp40.unk28 = 10.0f;
        sp40.unk2C = 40.0f;
        sp40.unk3C = D_800A8DB0;
        sp40.unk40 = 0.5f;
        sp40.unk4C = -2.0f;
        sp40.unk50 = 4.0f;
        sp40.unk1E = 0x50;
        sp40.unk54 = 0;
        sp40.unk55 = 0;
        sp40.unk56 = 0x32;
        sp40.unk58 = 0x19;
        sp40.unk44 = -1.0f;
        sp40.unk48 = -1.0f;
        sp40.unk34 = 0.0f;
        sp40.unk38 = 0.0f;

        func_151A6F00(&sp40, 0, arg1, arg2);
        func_151D5334(&sp9C, 506.0f, 1013.0f, 0.00098716688808053732f, 5, arg1, arg2);
        func_151D3FF4(&sp9C, arg1, arg2);
        func_151D5514(&sp9C, arg1, arg2);

        *(f32 *)((u8 *)&sp40 - 8) = func_150ADA68();
        func_151541B8(&sp9C, (*(f32 *)((u8 *)&sp40 - 8) * 4.0f) + 12.0f, 0x3FD20C49,
                      (func_150ADA20() % 0x38U) + 0xC8, 0.0f, arg1, arg2);
        func_151D5404(&sp9C, 1502.0f, 3000.0f, 0.00033333332976326346f, 0xC, 0xF, 0xFF, 0);
    }
}
