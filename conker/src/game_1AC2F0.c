#include <ultra64.h>
#define func_15048A40 func_15048A40_hdr
#include "functions.h"
#undef func_15048A40
#include "variables.h"

extern f32 func_15048A40(u8 arg0);


extern u8 D_800DDDA0[];
extern u8 D_800DDDC0;

typedef struct {
    char pad_0x00[0xE];
    s16 field_0x0E;
    char pad_0x10[0x1B];
    u8 field_0x2B;
    char pad_0x2C[0x2];
    s16 field_0x2E;
} ColorBlendTask;

void func_1517EE40(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s8 arg4, s32 arg5) {
    u8 *p;

    if ((s8)arg4 == ((s8 *)&D_800DDDAC)[arg5]) {
        if ((&D_800DDDB0)[arg5] >= (&D_800DDE28)[arg5]) {
            if (((u8 *)&D_800DDDC0)[arg5] == 0) {
                return;
            }
        }
    }

    p = &D_800DDDA0[arg5 * 3];
    p[1] = arg1;
    p[2] = arg2;
    p[0] = arg0;
    (&D_800DDE28)[arg5] = arg3;
    (&D_800DDDB0)[arg5] = 0;
    ((s8 *)&D_800DDDAC)[arg5] = (s8)arg4;
    ((u8 *)&D_800DDDC0)[arg5] = 0;
}

extern u8 D_800DDDAC;
extern s32 D_800DDDB0;
extern s32 D_800DDE28;
extern u8 D_800DDDC0;
s32 func_1517EF00(s32 arg0)
{
  s32 v1;
  s32 a1;
  v1 = ((&D_800DDDB0)[arg0] * 255) / a1;
  if ((&D_800DDDC0)[arg0] != 0)
  {
    v1 = (&D_800DDDC0)[arg0];
  }
  else
  {
    a1 = (&D_800DDE28)[arg0];
    if (a1 != 0)
    {
      v1 = ((&D_800DDDB0)[arg0] * 255) / a1;
      if (v1 >= 0x100)
      {
        v1 = 0xFF;
      }
    }
    else
    {
      v1 = 0xFF;
    }
    if (((s8 *) (&D_800DDDAC))[arg0] == 0)
    {
      v1 = 255 - v1;
    }
  }
  return v1;
}

extern s32 func_1517EF00(s32);


extern s32 func_1517EF00(s32);

s32 func_1517EFAC(s32 arg0) {
    if (func_1517EF00(arg0) == 0xFF) {
        return 1;
    }
    return 0;
}

s32 func_1517EFDC(void) {
    s32 s1 = -1;
    s32 s0;
    s32 v0;
    for (s0 = 0; s0 <= D_80082FA0; s0++) {
        if ((func_1517EF00(s0) > 0) || (0.0f < (&D_800DDDC8)[s0])) {
            s1++;
        }
    }
    v0 = D_80082FA0;
    if (s1 == v0) {
        return 1;
    }
    return 0;
}

#define WGFX1517F08C(pkt, a, b)     \
{                                   \
    Gfx *_g = (Gfx *)(pkt);         \
    _g->words.w0 = (u32)(a);        \
    _g->words.w1 = (u32)(b);        \
}

Gfx *func_1517F08C(Gfx *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    typedef struct {
        char pad0[0x24];
        f32 unk24;
        f32 unk28;
        f32 unk2C;
        f32 unk30;
        char pad34[0x14C];
    } Struct1517F08C;
    WGFX1517F08C(arg0++, 0xE7000000, 0);
    WGFX1517F08C(arg0++, 0xFCFFFFFF, 0xFFFDF6FB);
    gDPSetPrimColor(arg0++, 0, 0, arg2, arg3, arg4, arg1);
    WGFX1517F08C(arg0++, 0xEF002CFF, 0x504344);

    gDPFillRectangle(arg0++,
        ((Struct1517F08C *)D_800BE628)[arg5].unk2C,
        ((Struct1517F08C *)D_800BE628)[arg5].unk24,
        ((Struct1517F08C *)D_800BE628)[arg5].unk30,
        ((Struct1517F08C *)D_800BE628)[arg5].unk28);

    return arg0;
}

extern u8 D_800DDDA0[];
Gfx *func_1517F08C(Gfx *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);

s32 func_1517F3A0(s32 arg0, s32 arg1) {
    s32 v0 = func_1517EF00(arg1);
    u8 *p;
    if (v0 == 0) {
        return arg0;
    }
    p = &D_800DDDA0[arg1 * 3];
    return func_1517F08C(arg0, v0, p[0], p[1], p[2], arg1);
}

s32 func_1517F40C(s32 arg0) {
    if ((&D_800DDDB0)[arg0] >= (&D_800DDE28)[arg0]) {
        return 1;
    }
    return 0;
}

void func_1517F448(s32 arg0) {
    if ((&D_800DDDB0)[arg0] != (&D_800DDE28)[arg0]) {
        (&D_800DDDB0)[arg0] += D_800BE9E4;
    }
}

extern u8 D_800DDD90[];
extern u8 D_800DDD9C[];
extern s16 D_800DDE10[];

void func_1517F488(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    u8 *p = &D_800DDD90[arg5 * 3];
    p[0] = arg0;
    p[1] = arg1;
    p[2] = arg2;
    D_800DDD9C[arg5] = arg3;
    D_800DDE10[arg5] = arg4;
}

s32 func_1517F4D8(s32 arg0, s32 arg1) {
    u8 *p;

    if (((u16 *)D_800DDE10)[arg1] == 0) {
        return arg0;
    }

    if (D_800DDD9C[arg1] == 0) {
        return arg0;
    }

    p = &D_800DDD90[arg1 * 3];
    return func_1517F08C(arg0, D_800DDD9C[arg1], p[0], p[1], p[2], arg1);
}

extern u8 D_8008D010[];
extern u8 D_800DDD88;
extern u8 D_800DDD89;
extern u8 D_800DDD8A;
extern u8 D_800DDD8B;
extern u8 D_800DDD8C;

s32 func_1517F564(s32 arg0) {
    f32 temp_f2[4];
    f32 sp20;
    f32 fade;
    u8 *p;
    s32 v0;
    s32 a1;
    s32 red;
    s32 green;
    s32 blue;

    if (D_800DDE08 == 0) {
        return arg0;
    }

    v0 = D_800DDD8B;
    if (v0 == 0) {
        return arg0;
    }

    if (D_800DDD8C != 0) {
        fade = (func_15048A40(D_800DDD89) + 1.0f) * 0.5f;
        a1 = (s32)((f32)D_800DDD8B * fade);
        sp20 = 0.0f;
    } else {
        a1 = v0;
        sp20 = temp_f2[0];
    }

    p = &D_8008D010[D_800DDD8A * 6];
    red = (s32)((f32)p[0] + ((f32)(p[3] - p[0]) * sp20));
    green = (s32)((f32)p[1] + ((f32)(p[4] - p[1]) * sp20));
    blue = (s32)((f32)p[2] + ((f32)(p[5] - p[2]) * sp20));
    return func_1517F08C(arg0, a1, red, green, blue, 0);
}

void func_1517F720(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    D_800DDE08 = arg1;
    D_800DDD88 = arg2;
    D_800DDD89 = 0;
    D_800DDD8A = arg0;
    D_800DDD8B = arg3;
    D_800DDD8C = arg4;
}

extern s32 D_800BE9E4;

void func_1517F75C(void) {
    s32 i;

    for (i = 0; i <= D_80082FA0; i++) {
        if (D_800BE9E4 < ((u16 *)D_800DDE10)[i]) {
            ((u16 *)D_800DDE10)[i] -= D_800BE9E4;
        } else {
            ((u16 *)D_800DDE10)[i] = 0;
        }
    }
}


extern s32 D_800BE9E4;
extern u16 D_800DDE08;
extern u8 D_800DDD88;
extern u8 D_800DDD89;
void func_1517F7B4(void)
{
  if (D_800DDE08)
  {
    if (D_800BE9E4 < D_800DDE08)
    {
      D_800DDE08 -= D_800BE9E4;
    }
    else
    {
      D_800DDE08 = 0;
    }
    D_800DDD89 += D_800DDD88 * D_800BE9E4;
  }
}


#pragma GLOBAL_ASM("asm/nonmatchings/game_1AC2F0/func_1517F814.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1AC2F0/func_1517F9F4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1AC2F0/func_1517FB9C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1AC2F0/func_15180580.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1AC2F0/func_151814FC.s")

extern f32 D_800DDDC8;

s32 func_15181CC8(s32 arg0) {
    if ((&D_800DDDC8)[arg0] == 0.0f) {
        return 1;
    }
    return 0;
}

extern f32 D_800A72AC;
extern f32 D_800DDDE8[][2];

void func_15181D00(s32 arg0, s32 arg1) {
    if (arg1 == 0) {
        (&D_800DDDC8)[arg0] = 0.0f;
    } else {
        (&D_800DDDD8)[arg0] = 0.0f;
        (&D_800DDDC8)[arg0] = D_800A72AC;
        D_800DDDE8[arg0][0] = 0.0f;
        D_800DDDE8[arg0][1] = 0.0f;
    }
    (&D_800DDE1C)[arg0] = arg1;
}

extern f32 D_800A72B0;
extern f32 D_800A72B4;

void func_15181D70(s32 arg0) {
    (&D_800DDDD8)[arg0] = D_800A72B0;
    (&D_800DDDC8)[arg0] = 0.0f;
    D_800DDDE8[arg0][0] = 0.0f;
    D_800DDDE8[arg0][1] = 0.0f;
    (&D_800DDE20)[arg0] = 1;
}

void func_15181DC8(s32 arg0) {
    (&D_800DDDD8)[arg0] = 0;
    (&D_800DDDC8)[arg0] = 0.0f;
    D_800DDDE8[arg0][0] = 0.0f;
    D_800DDDE8[arg0][1] = 0.0f;
    (&D_800DDE20)[arg0] = 0;
}

void func_15181E18(s32 arg0) {
    u8 *p;

    if (D_800BE616 != 0) {
        p = &D_800DDDA0[arg0 * 3];
        p[0] = 0;
        p[1] = 0;
        p[2] = 0;
        (&D_800DDE28)[arg0] = 0x19;
        (&D_800DDDB0)[arg0] = 0;
        ((u8 *)&D_800DDDAC)[arg0] = 0;
        ((u8 *)&D_800DDDC0)[arg0] = 0;
    } else {
        ((u8 *)&D_800DDE3C)[arg0] = 1;
        (&D_800DDDC8)[arg0] = 1.0f;
        D_800DDDE8[arg0][0] = 0.0f;
        D_800DDDE8[arg0][1] = 0.0f;
        (&D_800DDDD8)[arg0] = D_800A72B4;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1AC2F0/func_15181EE0.s")

void func_15182670(s32 arg0, s32 arg1, s32 arg2, s32 arg3, volatile s16 arg4, u8 arg5, u8 arg6, s32 arg7) {
    struct {
        u8 unk0;
        u8 unk1;
        u8 unk2;
        u8 unk3;
        u8 unk4;
        u8 pad5;
        s16 unk6;
        s32 pad8;
    } sp34;
    struct260 *temp_v0;

    if (arg4 > 0) {
        sp34.unk0 = ((u8 *)&arg0)[3];
        sp34.unk1 = ((u8 *)&arg1)[3];
        sp34.unk2 = ((u8 *)&arg2)[3];
        sp34.unk3 = ((u8 *)&arg3)[3];
        sp34.unk4 = arg5;
        sp34.unk6 = ((u8 *)&arg3)[3] / arg4;

        temp_v0 = func_15149130(arg4, -1, 0x39, 3, 1, 0, (struct37 *)0x8, arg6, arg7);
        if (temp_v0 != NULL) {
            memcpy((void *)((s32)temp_v0 + 0x28), &sp34, 8);
        }
    }
}

void func_15182748(ColorBlendTask *arg0) {
    arg0->field_0x2B = arg0->field_0x2E * arg0->field_0x0E;
}

s32 func_15182768(s32 arg0, s32 arg1, s16 arg2) {
    u8 *p = (u8 *)(*(s32 *)&arg1 + 0x28);
    if (arg2 == *(u8 *)(*(s32 *)&arg1 + 0x2C)) {
        arg0 = func_1517F08C(arg0, p[3], p[0], p[1], p[2], p[4]);
    }
    return arg0;
}
