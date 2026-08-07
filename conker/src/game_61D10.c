#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_61D10/func_15034860.s")

extern s16 D_800C3EF0;
extern f32 D_80097D60;

struct Entry15034EB4 {
    u8 pad[0x34];
    f32 unk34;
    u8 pad2[0x8];
};

struct Obj15034EB4 {
    u8 pad[0x14C];
    f32 unk14C;
    u8 pad2[0x84];
    struct Entry15034EB4 *unk1D4;
};

void func_15034EB4(struct Obj15034EB4 *obj, s32 idx, s32 idx2) {
    f32 amt;
    struct Entry15034EB4 *e;
    struct Entry15034EB4 *e2;
    struct Entry15034EB4 *base;

    if (D_800C3EF0 != 0) {
        base = obj->unk1D4;
        amt = ((f32)D_800C3EF0 * D_80097D60) * obj->unk14C;
        e = &base[idx];
        e->unk34 -= amt;
        if (idx2 != -1) {
            e2 = &base[idx2];
            e2->unk34 -= amt;
        }
    }
}

extern u8 D_800C3F00;

void func_15034F20(void) {
    D_800C3F00 = 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_61D10/func_15034F30.s")

extern u8 D_800C3F00;
struct Foo
{
  u8 unk0[12];
};
extern struct Foo D_800C3F08[];
struct Foo *func_150356C8(void)
{
  int new_var;
  u8 temp = D_800C3F00;
  if (1)
  {
    if (temp == 15)
    {
      return 0;
    }
    temp = temp + 1;
    new_var = temp;
    D_800C3F00 = new_var;
  }
  return (struct Foo *) ((((u8 *) D_800C3F08) + (((u8) new_var) * 12)) - 12);
}


#pragma GLOBAL_ASM("asm/nonmatchings/game_61D10/func_15035714.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_61D10/func_15035808.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_61D10/func_15035D6C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_61D10/func_15035FE8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_61D10/func_15036148.s")
