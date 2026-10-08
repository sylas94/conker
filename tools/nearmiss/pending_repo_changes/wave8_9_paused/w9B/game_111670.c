#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern f32 D_800A1140;
extern f32 D_800A1144;
extern f32 D_800A1148;
extern f32 D_800A114C;
extern f32 D_800A1150;
extern f32 D_800A1154;
extern f32 D_800A1158;
extern f32 D_800A115C;
extern s32 func_15132A4C(void *, s32, s32, s32, u8, s32);
extern s32 func_151EF610(f32);

typedef struct Struct150E5558 {
    /* 0x00 */ f32 unk00;
    /* 0x04 */ f32 unk04;
    /* 0x08 */ f32 unk08;
    /* 0x0C */ f32 unk0C;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ f32 unk40;
    /* 0x44 */ f32 unk44;
    /* 0x48 */ f32 unk48;
    /* 0x4C */ f32 unk4C;
    /* 0x50 */ s32 unk50;
    /* 0x54 */ s16 unk54;
    /* 0x56 */ s16 unk56;
    /* 0x58 */ u8 unk58;
    /* 0x59 */ u8 pad59[3];
    /* 0x5C */ s32 unk5C;
    /* 0x60 */ u8 unk60;
    /* 0x61 */ u8 unk61;
    /* 0x62 */ u8 unk62;
    /* 0x63 */ u8 unk63;
    /* 0x64 */ u8 unk64;
    /* 0x65 */ u8 unk65;
    /* 0x66 */ u8 unk66;
    /* 0x67 */ u8 unk67;
    /* 0x68 */ u8 unk68;
    /* 0x69 */ u8 pad69;
    /* 0x6A */ u8 unk6A;
    /* 0x6B */ u8 pad6B;
    /* 0x6C */ s32 unk6C;
    /* 0x70 */ u8 unk70;
    /* 0x71 */ u8 pad71;
    /* 0x72 */ s16 unk72;
    /* 0x74 */ s16 unk74;
    /* 0x76 */ u8 pad76[6];
} Struct150E5558;


typedef struct Struct150E42F8D99F0
{
  s16 unk0;
  s16 unk2;
  s16 unk4;
} Struct150E42F8D99F0;
extern Struct150E42F8D99F0 D_800D99F0;

void func_150E41C0(void) {
    s32 x;
    s32 y;
    s32 z;
    f32 angle;
    f32 dy;
    f32 dz;
    f32 s;
    f32 c;
    f32 dx;

    x = D_800DBFF0->unk2F8;
    y = D_800DBFF0->unk2FC;
    z = D_800DBFF0->unk300;
    angle = D_800DBFF0->unk398;
    s = sinf(angle);
    c = cosf(angle);
    dx = 0.0f;
    dy = 500.0f * s;
    dz = -500.0f * c;
    angle = D_800DBFF0->unk3A0;
    s = sinf(angle);
    c = cosf(angle);
    x += dx * c + dz * s;
    z += dz * c - dx * s;
    y += dy;
    D_800D99F0.unk0 = x;
    D_800D99F0.unk2 = y;
    D_800D99F0.unk4 = z;
}

u8 func_150ADA20(void);
extern s32 D_800DBE3C;
extern s32 D_800DBE4C;
extern s32 D_800DBE5C;
extern f32 D_800A1060;
extern s32 func_1510F8CC(s32);
extern s32 func_1510F8D8(s32, s32, s32, s32 *);
extern void func_150E4550(f32, f32, f32, s32, s32, s32, s32);
void func_150E42F8(s32 arg0)
{
  s32 temp_s0;
  s32 temp_s1;
  s32 temp_s2;
  s32 sp70;
  s32 temp_v0;
  s32 sp68;
  s32 idx;
  s32 i;
  f32 temp_f20;
  s32 sp58;
  sp58 = 0;
  i = 0;
  sp70 = D_800D99F0.unk0;
  sp68 = D_800D99F0.unk4;
  if (arg0 > 0)
  {
 temp_f20 = D_800A1060; do {
      temp_s0 = (func_150ADA20() % 0x1F4) + sp70;
      temp_s1 = (func_150ADA20() % 0x1F4) + sp68;
      temp_s2 = temp_s1;
      temp_s1 = func_1510F8D8(temp_s0, 0x2710, temp_s2, &sp58);
      if ((temp_f20 != ((f32) temp_s1)) && (sp58 != 0))
      {
        idx = (sp58 - D_800DBE3C) / 12;
        if ((idx >= 0) && (idx < D_800DBE4C))
        {
          temp_v0 = func_1510F8CC(((s32 *) D_800DBE5C)[idx]);
          if (temp_v0 != 0)
          {
            func_150E4550((f32) temp_s0, (f32) temp_s1, (f32) temp_s2, 0, temp_v0, sp58, 0xFF);
          }
        }
      }
      i++;
    }
    while (i != arg0);
  }
}

extern void func_150E42F8(s32);


extern void func_150E41C0(void);
extern void func_150E42F8(s32);

void func_150E4514(s32 arg0) {
    func_150E41C0();
    func_150E42F8(arg0 / 0x1E);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_111670/func_150E4550.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_111670/func_150E4928.s")

void func_150E4CBC(struct42 *arg0) {
    s32 temp_v0;
    s32 temp_t0;
    s32 temp_a1;

    temp_v0 = arg0->unk90;
    if (temp_v0 < 9) {
        arg0->unkA4 = (s32)((f32)(((temp_v0 * 0x5A) / 9) * arg0->unk96) * 0.00390625f);
    } else {
        arg0->unkA4 = (s32)((f32)((0x5A - (((temp_v0 * 0x5A) - 0x32A) / 0x258)) * arg0->unk96) * 0.00390625f);
        temp_t0 = D_800BE9E4 * 17;
        temp_a1 = *(u8 *)((u8 *)arg0 + 0xB4);
        if (temp_t0 < temp_a1) {
            *(u8 *)((u8 *)arg0 + 0xB4) = temp_a1 - temp_t0;
            temp_v0 = arg0->unk90;
        } else {
            *(s16 *)((u8 *)arg0 + 0x98) = -1;
            temp_v0 = arg0->unk90;
        }
    }
    arg0->unkA2 = (s32)((f32)arg0->unk94 * 14.0f) >> 8;
    if (temp_v0 >= 0x261) {
        *(s16 *)((u8 *)arg0 + 0x98) = -1;
        temp_v0 = arg0->unk90;
    }
    arg0->unk90 = temp_v0 + D_800BE9E4;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_111670/func_150E4E04.s")

void func_150E5558(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s32 arg6) {
    Struct150E5558 sp34;
    f32 var_f16;
    f32 var_f2;
    f32 temp_f2;
    f32 temp_f6;

    bzero(&sp34, sizeof(sp34));

    if (arg4 != 0.0f) {
        var_f16 = func_150484A0(arg3, arg4) * D_800A1140;
    } else {
        var_f16 = 90.0f;
    }

    if (arg5 != 0.0f) {
        var_f2 = func_150484A0(arg3, arg5) * D_800A1144;
    } else {
        var_f2 = 90.0f;
    }

    sp34.unk14 = var_f2;
    sp34.unk18 = var_f16;
    sp34.unk1C = 1.0f;
    sp34.unk20 = 1.0f;
    sp34.unk24 = 1.0f;
    sp34.unk00 = 1.0f;
    sp34.unk08 = D_800A1148;
    sp34.unk0C = D_800A1148;
    sp34.unk28 = arg0;
    sp34.unk2C = arg1;
    sp34.unk30 = arg2;
    sp34.unk10 = 0.0f;

    if (arg6 == 4) {
        sp34.unk56 = 6;
        sp34.unk04 = D_800A114C;
    } else if (arg6 == 9) {
        sp34.unk56 = 8;
        sp34.unk04 = D_800A1150;
    } else {
        sp34.unk56 = 7;
        sp34.unk04 = D_800A1154;
    }

    sp34.unk54 = (func_151EF610(D_800A1148) % 60) + 0x3C;
    sp34.unk50 = 0x29E9;

    temp_f6 = func_150ADA68();
    sp34.unk4C = D_800A1158;
    temp_f2 = (temp_f6 * D_800A115C) + 1.5f;
    sp34.unk34 = temp_f2 * arg3;
    sp34.unk38 = -temp_f2 * arg4;
    sp34.unk3C = temp_f2 * arg5;

    sp34.unk40 = (func_150ADA68() * 6.0f) + -3.0f;
    sp34.unk48 = (func_150ADA68() * 6.0f) + -3.0f;
    temp_f6 = (func_150ADA68() * 6.0f) + -3.0f;
    sp34.unk58 = 0;
    sp34.unk5C = 0;
    sp34.unk44 = temp_f6;
    sp34.unk60 = 0xFF;
    sp34.unk61 = 1;
    sp34.unk62 = 0;
    sp34.unk63 = 3;
    sp34.unk64 = 0;
    sp34.unk65 = 0;
    sp34.unk66 = 0;
    sp34.unk67 = 0;
    sp34.unk68 = 0;
    sp34.unk6A = 2;
    sp34.unk6C = 0;
    sp34.unk70 = 0;
    sp34.unk72 = 0x20;
    sp34.unk74 = 7;

    func_15132A4C(&sp34, 3, 0xFF, 0, 0xFF, 0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_111670/func_150E5810.s")
