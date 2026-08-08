#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern s32 D_800DDD58;
extern s32 func_1517D074(s32, s16, s16, s16, f32, s32, s32, s32, s32, s32);

extern s32 func_151EF610(void);
extern u8 D_80095CE1[];

s32 func_1517B500(s16 *arg0, s16 *arg1, s32 *arg2, s32 arg3)
{
    s32 diff;
    s32 limit;
    s32 rnd;

    *arg2 = (*arg2 * 3) / 2;
    limit = D_80095CE1[((u8 *) arg0)[8] * 10] << 8;
    if (*arg2 >= limit)
    {
        *arg2 = *arg2 - limit;
    }

    arg1[0] = arg0[0];
    arg1[1] = arg0[1];
    arg1[2] = arg0[2];

    diff = 0x29 - ((s8 *) arg0)[0xD];
    if (diff == 0)
    {
        ((s8 *) arg0)[0xD] = (((s8 *) arg0)[0xD] - (func_151EF610() % 8)) + 4;
    }
    else if (diff < 0)
    {
        rnd = func_151EF610();
        ((s8 *) arg0)[0xD] = ((((s8 *) arg0)[0xD] - ((func_151EF610() % -diff) >> 1)) - (rnd % 8)) + 4;
    }
    else
    {
        rnd = func_151EF610();
        ((s8 *) arg0)[0xD] = ((((func_151EF610() % diff) >> 1) + ((s8 *) arg0)[0xD]) + (rnd % 8)) - 4;
    }

    arg1[0] = arg0[0];
    arg1[1] = arg0[1];
    arg1[2] = arg0[2];
    return 0;
}

s32 func_1517B6E8(s16 *arg0, s16 *arg1, s32 *arg2, s32 arg3)
{
  s32 v0;
  v0 = *arg2;
  if (v0 >= 0x600)
  {
    arg1[1] = ((v0 >> 6) + arg0[1]) - ((0, 0x18));
    arg1[0] = (arg0[0] + ((*arg2) >> 8)) - 6;
    {
      s32 temp;
      s32 v2;
      v2 = ((*((u8 *) arg3)) << 7) / (((*arg2) >> 6) - 0x17);
      temp = *((u8 *) arg3);
      v2 >>= 4;
      if (v2 < temp)
      {
        *((u8 *) arg3) = v2;
      }
    }
    *arg2 = 0x600;
  }
  else
  {
    arg1[0] = arg0[0];
    arg1[1] = arg0[1];
  }
  arg1[2] = arg0[2];
  return 0;
}


s32 func_1517B7A8(s16 *a0, s16 *a1, s32 *a2, s32 a3) {
    s32 v0 = *a2;

    if (v0 >= 0x300) {
        if (v0 >= 0x501) {
            *a2 = v0 - 0x200;
        } else {
            *a2 = 0x300;
        }
    }

    a1[0] = a0[0];
    a1[1] = a0[1];
    a1[2] = a0[2];
    return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1A89B0/func_1517B7F8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1A89B0/func_1517B89C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1A89B0/func_1517BBAC.s")

extern void func_10006240(s32, s32, s32);
extern void func_10004074(s32);

struct s1517CFC4_a { s32 unk0; s32 unk4; s32 unk8; s32 unkC; };

void func_1517CFC4(void) {
    s32 i;
    s32 *q;
    struct s1517CFC4_a *p;

    for (q = (s32 *)&D_800DD478, p = (struct s1517CFC4_a *)&D_800DDA90, i = 0; i != 15; i++, p++) {
        if (p->unk8 != 0) {
            if (q[i * 26] != 0) {
                func_10006240(p->unk8, q[i * 26], D_8003809C);
                func_10004074(p->unk8);
            }
            p->unk8 = 0;
        }
    }
}


#pragma GLOBAL_ASM("asm/nonmatchings/game_1A89B0/func_1517D074.s")

struct Entry1517D578 {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    u8  unk6;
    s16 unk8;
    s16 unkA;
    f32 unkC;
};
extern struct Entry1517D578 D_800DDD28[];

void func_1517D578(s16 arg0, s16 arg1, s16 arg2, f32 arg3, s32 arg4, s32 arg5, u8 arg6)
{
    struct Entry1517D578 *e;
    u8 idx = D_8008CEB0;
    if (D_8008CEB0 < 3)
    {
        e = &D_800DDD28[idx];
        e->unk0 = arg0;
        e->unk2 = arg1;
        e->unk4 = arg2;
        e->unkC = arg3;
        e->unk8 = arg4;
        e->unkA = arg5;
        e->unk6 = arg6;
        D_8008CEB0 = idx + 1;
    }
}

void func_1517D5FC(s16 arg0, s16 arg1, s16 arg2, s32 arg3, s32 arg4, s32 arg5)
{
    func_1517D578(arg0, arg1, arg2, D_800DBFF0[arg3].unk380, arg4, arg5, D_800DDD1C >> 3);
}

s32 func_1517D690(s32 arg0, s32 arg1) {
    s32 saved;

    saved = D_800DDD58;
    if ((D_800DDD1C = D_800DDD1C + 5) >= 0xC8) {
        D_800DDD1C -= 0xC8;
    }

    if (D_8008CEB0 != 0) {
        do {
            D_8008CEB0 = D_8008CEB0 - 1;
            if (arg1 != 0) {
                arg0 = func_1517D074(arg0,
                                      D_800DDD28[D_8008CEB0].unk0,
                                      D_800DDD28[D_8008CEB0].unk2,
                                      D_800DDD28[D_8008CEB0].unk4,
                                      D_800DDD28[D_8008CEB0].unkC,
                                      (s32)(u16)D_800DDD28[D_8008CEB0].unk8,
                                      (s32)(u16)D_800DDD28[D_8008CEB0].unkA,
                                      0x10, 0x20,
                                      ((D_800DDD28[D_8008CEB0].unk6 * 0x280) << 1) + arg1);
            }
        } while (D_8008CEB0 != 0);
    }

    D_800DDD58 = saved;
    return arg0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1A89B0/func_1517D7B0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1A89B0/func_1517DE5C.s")

extern struct { s16 unk0; s16 unk2; s16 unk4; } D_800DD470;

void func_1517E05C(s32 arg0, s32 arg1, s32 arg2) {
    D_800DD470.unk0 = arg0;
    D_800DD470.unk2 = arg1;
    D_800DD470.unk4 = arg2;
}
