#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_F2820/func_150C5370.s")

void func_150C5430(struct102 *arg0) {
    func_15169804(arg0);
}

void func_150C5450(struct102 *arg0) {
    func_15169824(arg0);
}

extern void (*D_800887B8[])(void);

void func_150C5470(struct102 *arg0) {
    s32 temp = *(u8 *)((u8 *)arg0 + 0x38);

    if (temp < 0) {
        temp = 0;
    } else if (temp >= 2) {
        temp = 0;
    }
    D_800887B8[temp]();
}

extern void (*D_800887C0[])(void);

void func_150C54C0(struct102 *arg0) {
    s32 temp = *(u8 *)((u8 *)arg0 + 0x38);

    if (temp < 0) {
        temp = 0;
    } else if (temp >= 2) {
        temp = 0;
    }
    D_800887C0[temp]();
}

extern void func_1514EDF0(struct102 *arg0, s32 arg1);

void func_150C5510(struct102 *arg0) {
    func_1514EDF0(arg0, *(s32 *)((u8 *)arg0 + 0xC8));
    func_150C5430(arg0);
}

void func_150C553C(struct102 *arg0) {
    func_1514EDF0(arg0, *(s32 *)((u8 *)arg0 + 0xC8));
    func_150C5450(arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_F2820/func_150C5568.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_F2820/func_150C56A4.s")

typedef struct {
    s32 unk0;
    u8 pad4[0x10];
    f32 unk14;
    f32 unk18;
    f32 unk1C;
} Sub150C5B88;

s32 func_150C5B88(struct102 *arg0) {
    Sub150C5B88 **temp_v1;

    temp_v1 = (Sub150C5B88 **)((u8 *)arg0 + 0xC8);
    if ((*temp_v1)->unk0 == 0) {
        return 0;
    }
    *(f32 *)((u8 *)arg0 + 0x24) = (*temp_v1)->unk14;
    *(f32 *)((u8 *)arg0 + 0x28) = (*temp_v1)->unk18;
    *(f32 *)((u8 *)arg0 + 0x2C) = (*temp_v1)->unk1C;
    return 1;
}

extern void func_15143134(void *, s32, s32);
s32 func_150C5BD4(struct102 *arg0)
{
  u8 *p = ((u8 *) arg0) + 0xC8;
  u32 offset;
  s32 t0;
  if ((*((s32 *) (*((s32 *) p)))) == 0)
  {
    return 0;
  }
  if (p[4] != (*(((u8 *) (*((s32 *) p))) + 0x3B)))
  {
    return 0;
  }
  t0 = *((s32 *) (((u8 *) (*((s32 *) p))) + 0x1D4));
  if (t0 == 0)
  {
    *((f32 *) (((u8 *) arg0) + 0x24)) = *((f32 *) (((u8 *) (*((s32 *) p))) + 0x14));
    *((f32 *) (((u8 *) arg0) + 0x28)) = *((f32 *) (((u8 *) (*((s32 *) p))) + 0x18));
    *((f32 *) (((u8 *) arg0) + 0x2C)) = *((f32 *) (((u8 *) (*((s32 *) p))) + 0x1C));
  }
  else
  {
    offset = (p[5] << 4) << 2;
    func_15143134(p + 0x8, (s32) (((u8 *) arg0) + 0x24), t0 + offset);
  }
  return 1;
}


void func_150C5C74(s32 arg0) {
    func_1514D3B0(arg0, 0x15, 1, 0);
}

void func_150C5C9C(s32 arg0) {
    func_1514D3B0(arg0, 0x15, 2, 0);
}

extern void (*D_800887C8[])(struct102 *, s32, u8);

void func_150C5CC4(struct102 *arg0, s32 arg1, u8 arg2) {
    void (*temp)(struct102 *, s32, u8) = D_800887C8[*(u8 *)((u8 *)arg0 + 0x38)];

    if (temp != NULL) {
        temp(arg0, arg1, arg2);
    }
}

typedef struct {
    s32 unk0;
    u8 unk4;
} SubA150C5D0C;

typedef struct {
    s32 unk0;
    union {
        s32 w4;
        u8 b4;
    } u4;
    u8 unk8;
    u8 unk9;
} ArgB150C5D0C;

void func_150C5D0C(struct102 *arg0, s32 arg1, u8 arg2) {
    SubA150C5D0C *temp_v0 = (SubA150C5D0C *)((u8 *)arg0 + 0xC8);
    ArgB150C5D0C *b = (ArgB150C5D0C *)arg1;

    if (arg2 == 0) {
        if ((b->unk0 == temp_v0->unk0) || (b->u4.b4 == temp_v0->unk4)) {
            func_1516972C(arg0);
        }
    } else if (arg2 == 0x2D) {
        if (temp_v0->unk0 == b->unk0) {
            temp_v0->unk0 = b->u4.w4;
            temp_v0->unk4 = b->unk9;
        } else if (temp_v0->unk0 == b->u4.w4) {
            temp_v0->unk0 = b->unk0;
            temp_v0->unk4 = b->unk8;
        }
    }
}
