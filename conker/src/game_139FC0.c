#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern u8 D_1A37E0[];
extern u8 D_800D9F68[];

#define WGFX1510CDB8(pkt, a, b)     \
{                                   \
    Gfx *_g = (Gfx *)(pkt);         \
    _g->words.w0 = (u32)(a);        \
    _g->words.w1 = (u32)(b);        \
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_139FC0/func_1510CB10.s")

Gfx *func_1510CDB8(Gfx *arg0, s32 arg1, s32 arg2, s32 arg3) {
    gDPSetPrimColor(arg0++, 0xF2, 0, D_800D9B68[arg3][0], D_800D9B68[arg3][1], D_800D9B68[arg3][2], arg1);

    gDPSetEnvColor(arg0++, D_800D9B78[arg3][0], D_800D9B78[arg3][1], D_800D9B78[arg3][2], arg2);

    return arg0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_139FC0/func_1510CE60.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_139FC0/func_1510D0EC.s")

s32 func_1510D374(s32 arg0) {
    s32 sum;
    s32 i;

    sum = (s32)D_1A37E0;
    for (i = 0; i < arg0; i++) {
        sum += ((u16 *)D_80091D20)[i];
    }

    return sum;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_139FC0/func_1510D404.s")

void func_1510D608(s32 arg0, s32 arg1) {
    s8 *p = (s8 *)&D_800BC448[arg0];
    s8 temp = *p;
    if (temp != 0) {
        *p = (temp & 0x40) | arg1;
    }
}

void func_1510D694(s32);
extern s32 func_10004074(s16 *);

void func_1510D630(s16 *arg0) {
    s16 *p;
    s16 *end;
    s16 count = arg0[0];

    p = arg0 + 1;
    if (count > 0) {
        end = arg0 + count + 1;
        do {
            func_1510D694(*p);
            p++;
        } while (end != p);
    }
    func_10004074(arg0);
}

void func_1510D694(s32 arg0) {
    if ((s8)D_800BC448[arg0] != 0) {
        if (D_800D9F68[arg0] != 0) {
            if (--D_800D9F68[arg0] == 0) {
                if (arg0 < D_800D9F58) {
                    D_800D9F58 = arg0;
                }
                if (D_800D9F5C < arg0) {
                    D_800D9F5C = arg0;
                }
                func_1510D608(arg0, 3);
            }
        }
    }
}

void func_1510D720(s32 arg0) {
    if ((s8)D_800BC448[arg0] != 0) {
        if (D_800D9F68[arg0] != 0) {
            if (--D_800D9F68[arg0] == 0) {
                if (arg0 < D_800D9F58) {
                    D_800D9F58 = arg0;
                }
                if (D_800D9F5C < arg0) {
                    D_800D9F5C = arg0;
                }
                func_1510D608(arg0, 2);
            }
        }
    }
}

void func_1510D7AC(s32 arg0) {
    register s8 *flag;

    flag = (s8 *)&D_800BC448[arg0];
    if (*flag != 0) {
        if (D_800D9F68[arg0] != 0) {
            if (--D_800D9F68[arg0] == 0) {
                if (*flag & 0x40) {
                    func_10004074(*(s16 **)D_800B0E58[arg0]);
                }
                func_10004074((s16 *)D_800B0E58[arg0]);
                D_800B0E58[arg0] = -1;
                *flag = 0;
            }
        }
    }
}

extern u8 D_800D9ED0;

void func_1510D864(void) {
    D_800D9ED0 = 0;
}

extern u8 D_800D9ED0;
struct Entry1510D874
{
  s32 unk0;
  s32 unk4;
  s32 unk8;
  s8 unkC;
  s8 unkD;
};
extern struct Entry1510D874 D_800D9ED8[];
void func_1510D874(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
{
  struct Entry1510D874 *new_var;
  u8 idx = D_800D9ED0;
  if (D_800D9ED0 < 8)
  {
    struct Entry1510D874 *e = &D_800D9ED8[idx];
    e->unk0 = arg0;
    e->unk4 = arg1;
    e->unk8 = arg2;
    new_var = e;
    new_var->unkC = arg3;
    e->unkD = arg4;
    D_800D9ED0 = idx + 1;
  }
}


#pragma GLOBAL_ASM("asm/nonmatchings/game_139FC0/func_1510D8C0.s")
