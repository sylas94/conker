#include <ultra64.h>
#define func_1513EDE4 func_1513EDE4_orig
#include "functions.h"
#undef func_1513EDE4
#include "variables.h"

typedef struct {
    char pad_0x00[0x124];
    f32 field_0x124;
    f32 field_0x128;
} ScaleUpdateState;

typedef struct {
    char pad_0x00[0x8];
    s16 field_0x08;
    char pad_0x0A[0xE];
    s16 field_0x18;
    char pad_0x1A[0xE];
    s16 field_0x28;
    char pad_0x2A[0xE];
    s16 field_0x38;
} ScaleUpdateNode;

extern ScaleUpdateNode *func_1513EDE4(ScaleUpdateState *arg0, s16 arg1);
extern void func_150FCBC0(s32 arg0);
extern s32 func_1000EC24();
extern void func_15164F0C(s32 arg0, u8 arg1, s32 arg2, s32 arg3, s32 arg4);
extern void func_151D8868(void *arg0, s32 arg1, s32 arg2, s32 arg3);

struct sp44_150FCA30 {
    u8 unk0;
    u8 unk1;
    s16 unk2;
    u8 unk4;
    u8 unk5;
    s8 unk6;
    u8 unk7;
};

void func_150FCA30(void) {
    s32 i;
    struct sp44_150FCA30 sp44;

    func_150FCBC0(0);
    func_150FCBC0(1);
    func_150FCBC0(2);

    func_1000FA64(0x2B8, -0x7F6, 0x618, -0xA47, 0x6D60, 0x2328, 0x1B58, (s32)func_1000EC24, (void *)0x2D, 0, 0, 0);
    func_1000FA64(0x2B7, -0x13F, -0x111, -0xD5B, 0x6D60, 0x2328, 0x1B58, (s32)func_1000EC24, 0, 0, 0, 0);
    func_1000FA64(0x2B6, 0x5EF, 0x3B3, -0xA49, 0x6D60, 0x2328, 0x1B58, (s32)func_1000EC24, (void *)0x5A, 0, 0, 0);

    for (i = 0; i < D_80082FA0 + 1; i++) {
        func_15164F0C(4, i, 0, 0xFF, 1);
    }

    sp44.unk0 = 1;
    sp44.unk2 = 0x64;
    sp44.unk5 = 0xF;
    sp44.unk4 = 8;
    sp44.unk6 = -1;
    func_151D8868(&sp44, 0, 0xFF, 0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_129EE0/func_150FCBC0.s")

extern f32 D_800A1F2C;
extern void func_15165BB0(s32 *arg0, s32 *arg1, s32 arg2, s32 arg3, f32 arg4);

f32 func_150FCF1C(s32 *arg0) {
    struct134 *temp;
    f32 sp20[3];

    temp = D_800D9AA0[0];
    if (temp == NULL) {
        return 1.0f;
    }
    sp20[0] = (f32)temp->unk0;
    sp20[1] = (f32)(s16)temp->unk2;
    sp20[2] = (f32)temp->unk4;
    func_15165BB0(arg0, (s32 *)sp20, 0x44FAE000, 0x460CB400, D_800A1F2C);
}

void func_150FCFB0(s32 arg0) {
    func_15103828();
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_129EE0/func_150FCFD4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_129EE0/func_150FD514.s")

void func_150FDB0C(void *arg0, s32 arg1, u8 arg2)
{
  u8 *state;
  s32 *v0;
  s32 a2;
  s32 v1;
  s32 *msg;
 v0 = (s32 *) (((u8 *) arg0) + 0x110); if (arg2 == 0x2D) { v1 = *((s32 *) arg1); ; if (v1 == (*v0)) {
      state = (u8 *) v0;
      *v0 = *((s32 *) (arg1 + 4));
      *((u8 *) (state + 4)) = *((u8 *) (arg1 + 9));
    }
    else
    {
      if ((*((s32 *) (arg1 + 4))) == (*v0))
      {
        *v0 = v1;
        *((u8 *) (((u8 *) v0) + 4)) = *((u8 *) (arg1 + 8));
      }
      dummy_label_150FDB0C:
      ;

      ;
      ;
    }
  }
  else
  {
    msg = (s32 *) arg1;
    v1 = arg2 == 0;
    if (v1)
    {
      v1 = *msg;
      if (v1 != (*v0))
      {
        if ((*((u8 *) (((u8 *) v0) + 4))) != (*((u8 *) (arg1 + 4))))
        {
          return;
        }
      }
      *v0 = 0;
    }
  }
}


ScaleUpdateNode *func_150FDBA0(ScaleUpdateState *arg0, s16 arg1) {
    ScaleUpdateNode *node;

    node = func_1513EDE4(arg0, arg1);
    if (node != NULL) {
        node->field_0x08 = arg0->field_0x124;
        node->field_0x18 = arg0->field_0x128;
        node->field_0x28 = arg0->field_0x128;
        node->field_0x38 = arg0->field_0x124;
    }
    return node;
}

void func_150FDC2C(struct210 *arg0) {
    struct102 **p;

    p = (struct102 **)((u8 *)arg0 + 0x110);
    if (p[9] != 0) {
        func_1516972C(p[9]);
    }
    if (p[10] != 0) {
        func_1516972C(p[10]);
    }
    if (*(u16 *)((u8 *)p + 0x54) != 0) {
        func_100111C8(*(u16 *)((u8 *)p + 0x54));
    }
    if (*(u16 *)((u8 *)p + 0x56) != 0) {
        func_100111C8(*(u16 *)((u8 *)p + 0x56));
    }
}

extern void func_150FDC2C(struct210 *);

void func_150FDCAC(struct210 *arg0) {
    func_150FDC2C(arg0);
    func_1513CA6C(arg0);
}

void func_150FDCD8(struct210 *arg0) {
    func_150FDC2C(arg0);
    func_1513CAA0(arg0);
}
