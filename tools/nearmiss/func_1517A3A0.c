#include <ultra64.h>
#include "functions.h"
#include "variables.h"


struct func_1517A84C_obj {
    u8 unk0;
    u8 pad1[0x8F];
    s16 unk90;
    s16 unk92;
    s16 unk94;
    s16 unk96;
    s16 unk98;
    s16 unk9A;
    s8 unk9C;
    s8 unk9D;
    s8 unk9E;
    u8 unk9F;
    s16 unkA0;
    s16 unkA2;
    s16 unkA4;
    u16 unkA6;
    f32 unkA8;
    u16 unkAC;
    u16 unkAE;
    s16 unkB0;
    u8 unkB2;
    u8 unkB3;
};

extern f32 D_800A7220;
extern struct func_1517A84C_obj *func_15167A68(s32, s32, s32, s32, s32, s32);
extern u8 func_150ADA20(void);

#pragma GLOBAL_ASM("asm/nonmatchings/game_1A7260/func_15179DB0.s")

void func_15179FE0(u8 arg0, s16 arg1, s16 arg2, s16 arg3, s8 arg4, u16 arg5, u16 arg6, u8 arg7, u8 arg8, u8 arg9, s32 arg10) {
    struct func_1517A84C_obj *obj;
    s32 rnd;

    obj = func_15167A68(arg10, 0, 0xB8, 1, 0xFF, 1);
    if (obj != NULL) {
        obj->unk90 = arg1;
        obj->unk92 = arg2;
        obj->unk94 = arg3;
        obj->unkA2 = arg4;
        obj->unkA0 = ((u32)func_150ADA20() % arg7) - (arg7 >> 1);
        obj->unkA4 = ((u32)func_150ADA20() % arg7) - (arg7 >> 1);
        if (arg6 == 5) {
            obj->unk90 += obj->unkA0 * 4;
            obj->unk92 -= obj->unkA2 * 4;
            obj->unk94 += obj->unkA4 * 4;
        }
        obj->unk96 = 0;
        obj->unk98 = 0;
        obj->unk9A = 0;
        obj->unk9C = ((u32)func_150ADA20() % arg8) - (arg8 >> 1);
        obj->unk9D = ((u32)func_150ADA20() % arg8) - (arg8 >> 1);
        obj->unk9E = ((u32)func_150ADA20() % arg8) - (arg8 >> 1);
        rnd = func_150ADA20() & 0x7F;
        obj->unkA8 = (rnd + 0x8C) * D_800A7220;
        obj->unkA6 = arg5;
        obj->unk9F = arg0;
        obj->unkAC = arg6;
        obj->unkAE = arg9;
        obj->unkB2 = 0;
        obj->unkB3 = 0xFF;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1A7260/func_1517A1EC.s")

s32 func_1517A394(arg0)
s32 arg0;
{
    return arg0;
}

extern f32 D_800D9C10[][4][4];
extern f32 D_800D35E0;
extern s32 D_800D2C9C;
extern Gfx D_8008CDF0[];
extern s16 D_800DD450;

extern s32 func_1510AEE0(f32 (*)[4], f32, f32, f32, f32, f32, f32, f32, f32 *, f32 *);
extern s32 func_1517A9A8(s32, s32);
extern Gfx *func_15142FBC(Gfx *, s32, s32, u8 *);

Gfx *func_1517A3A0(Gfx *gfx, struct func_1517A84C_obj *obj, s16 arg2) {
    f32 q1;
    f32 q2;
    f32 q3;
    f32 q4;
    f32 q5;
    u8 update;

    if ((obj->unk0 != 0xC) && (obj->unk0 != 0x59)) {
        if (func_1510AEE0(D_800D9C10[arg2], obj->unk90, obj->unk92, obj->unk94, D_800D9B20,
                          D_800D9B1C, D_800D35E0, (&D_800D35E0)[1], NULL, NULL) != 0) {
            if (obj->unk0 == 8) {
                if (obj->unkB2 & (1 << arg2)) {
                    obj->unkB2 |= 0x10 << arg2;
                }
            }
            return gfx;
        }
    }

    if (obj->unk0 != 9) {
        obj->unkB2 |= 1 << arg2;
    }

    gfx = (Gfx *)func_1517A9A8((s32)gfx, obj->unk9F);
    func_15043D90((Mtx *)((u8 *)obj + (D_800BE9C0 << 6) + 0x10), obj->unk96, obj->unk98, obj->unk9A,
                  obj->unkA8, obj->unkA8, obj->unkA8, obj->unk90, obj->unk92, obj->unk94);
    gSPMatrix(gfx++, (u8 *)obj + (D_800BE9C0 << 6) + 0x10,
              G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);

    if (obj->unkB3 != D_800DD450) {
        gDPPipeSync(gfx++);
        gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, obj->unkB3);
        D_800DD450 = obj->unkB3;
    }

    update = 0;
    gfx = func_15142FBC(gfx, D_800D2C9C | 0x82CA0,
                        ((obj->unk0 == 8) || (obj->unk0 == 9)) ? 0x5049D8 : 0x504240, &update);
    gSPDisplayList(gfx++, D_8008CDF0);
    return gfx;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1A7260/func_1517A644.s")

void func_1517A84C(struct func_1517A84C_obj *arg0) {
    s32 temp_v0;
    s32 temp_v1;

    temp_v0 = arg0->unkA6;
    if (temp_v0 == 0) {
        arg0->unk90 += arg0->unkA0;
        temp_v0 = arg0->unkA2;
        arg0->unk92 += temp_v0;
        arg0->unk94 += arg0->unkA4;
        if (temp_v0 > 0) {
            arg0->unkA2 = temp_v0 - 1;
            if (arg0->unkA2 <= 0) {
                arg0->unkA2 = -3;
            }
        }
        temp_v1 = arg0->unkB0;
        temp_v0 = arg0->unk92 - temp_v1;
        if (temp_v0 <= 0) {
            arg0->unk96 = 0x5A;
            arg0->unk9A = 0;
            arg0->unkA6 = 0x3C;
            arg0->unk92 = temp_v1;
        } else {
            arg0->unk96 += arg0->unk9C;
            arg0->unk98 += arg0->unk9D;
            arg0->unk9A += arg0->unk9E;
        }
    } else {
        temp_v0 -= D_800BE9E4;
        if (temp_v0 > 0) {
            arg0->unkA6 = temp_v0;
            arg0->unkB3 = (temp_v0 << 8) / 0x3C;
        } else {
            func_1516972C((struct102 *)arg0);
        }
    }
}

extern s16 D_800DD450;
extern s32 func_1517A394();

s32 func_1517A958(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    arg2 = arg2;
    arg3 = arg3;
    D_800DD450 = -1;
    if ((arg1 == 0xC) || (arg1 == 0x59)) {
        arg0 = func_1517A394();
    }
    return arg0;
}

extern s32 D_800DD1B0;
extern s32 D_80090614;
struct sp34_t { s32 unk0[5]; };
extern s32 func_15094F70(s32, s32, s32, struct sp34_t*, s32, s32, s32, s32, s32);

s32 func_1517A9A8(s32 arg0, s32 arg1) {
    struct sp34_t sp34;

    if (arg1 != D_800DD1B0) {
        arg0 = func_15094F70(arg0, (s32)&D_80090614, (s32)((u32)arg1 << 8), &sp34, 0, 0, 0, 2, 3);
        D_800DD1B0 = arg1;
    }
    return arg0;
}

u8 func_150ADA20(void);
extern void func_1517A644(f32, u8, s16, s16, s32);
void func_1517AA20(f32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4)
{
  s32 randX;
  s32 randZ;
  s32 arg2s;
  s32 i;
  s32 limit;
  s32 randBit;
  u32 offset;
  f32 pos;
  if (arg0 < 12.0f)
  {
  }
  else
  {
    limit = (s32) (arg0 * 8.0f);
    arg0 *= 0.5f;
 arg2s = (s16) arg2; i = 0; if (arg4 > 0) { do {
        randX = func_150ADA20() & 0x3F;
        randZ = func_150ADA20() & 0x3F;
        randX -= 0x20;
        randZ -= 0x20;
        offset = (((u32) func_150ADA20()) % ((u32) limit)) >> 4;
        pos = ((f32) offset) + arg0;
        randBit = func_150ADA20();
        randBit &= 1;
        func_1517A644(pos, randBit, (s16) (arg1 + randX), (s16) arg2s, arg3 + randZ);
        i += 1;
      }
      while (i != arg4);
    }
  }
}


extern void func_1510B7B4(s32, s32);

void func_1517AB7C(s32 arg0, s32 arg1, s16 arg2) {
    func_1510B7B4(arg0, arg2);
}
