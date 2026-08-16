#include <ultra64.h>
#define func_15048A40 func_15048A40_void_unused
#include "functions.h"
#undef func_15048A40
#include "variables.h"

extern void func_1516F864(s32);
extern void func_1516F94C(s32, s32);

struct Table1516F024 {
    u8 unk0[0xB];
};

extern struct Table1516F024 D_8008CBC4;
extern struct Table1516F024 D_8008CBD0;
extern struct Table1516F024 D_8008CBDC;
extern struct Table1516F024 D_8008CBE8;

struct Obj1516D4E8 {
    char pad0[0xE];
    s16 unkE;
    s16 unk10;
    s16 unk12;
    s16 unk14;
    s16 unk16;
    s16 unk18;
    u8 unk1A;
    u8 unk1B;
    u8 unk1C;
    u8 unk1D;
    u8 unk1E;
    u8 unk1F;
    u8 unk20;
    u8 unk21;
    u8 unk22;
    u8 unk23;
    u8 unk24;
    u8 unk25;
    u8 unk26;
    u8 unk27;
    u8 unk28;
    u8 unk29;
    u8 unk2A;
    u8 unk2B;
    u8 unk2C;
    u8 unk2D;
    u8 unk2E;
    u8 unk2F;
    s32 unk30;
};

struct Obj1516D99C {
    char pad0[0xE];
    s16 unkE;
    s16 unk10;
    s16 unk12;
    s16 unk14;
    s16 unk16;
    s16 unk18;
    s16 unk1A;
    s16 unk1C;
    u16 unk1E;
    u16 unk20;
    u16 unk22;
    u8 unk24;
    u8 unk25;
    u8 unk26;
    u8 unk27;
    u8 unk28;
    u8 unk29;
    u8 unk2A;
    u8 unk2B;
    u8 unk2C;
    u8 unk2D;
    u8 unk2E;
    u8 unk2F;
    u8 unk30;
    u8 unk31;
    u8 unk32;
    u8 unk33;
    u8 unk34;
    u8 unk35;
    u8 unk36;
    u8 unk37;
    u8 unk38;
    u8 unk39;
    u8 unk3A;
    u8 unk3B;
    u8 unk3C;
    u8 unk3D;
    u8 unk3E;
    u8 unk3F;
    u8 unk40;
    u8 unk41;
    u8 unk42;
    u8 unk43;
    u8 unk44;
    u8 unk45;
    u8 unk46;
    u8 unk47;
    u8 unk48;
};

typedef struct {
    char pad_0[0x18];
    s16 field_0x18;
} Obj1516F984;

typedef struct {
    char pad_0[0x14];
    s16 field_0x14;
    s16 field_0x16;
    s16 field_0x18;
    char pad_0x1A[0x5];
    u8 field_0x1F;
    char pad_0x20[0x4];
    u8 field_0x24;
    char pad_0x25[0x1];
    u8 field_0x26;
    char pad_0x27[0x5];
    u8 field_0x2C;
    u8 field_0x2D;
} Obj1516FadeState;

typedef struct {
    char pad_0[0x14];
    s16 field_0x14;
    s16 field_0x16;
    s16 field_0x18;
    char pad_0x1A[0x5];
    u8 field_0x1F;
    char pad_0x20[0x4];
    u8 field_0x24;
    char pad_0x25[0x7];
    s8 field_0x2C;
} Obj1516FadeStepState;

extern struct Obj1516D99C *func_15167A68(s32, s32, s32, s32, s32, s32);
extern s32 func_150448D0(s32, s32, s32, s32, s32, s32, s32, s32, s32);

#define LOW_S16(arg) (*(s16 *)((u8 *)&(arg) + 2))
#define LOW_U16(arg) (*(u16 *)((u8 *)&(arg) + 2))
#define LOW_U8(arg) (*(u8 *)((u8 *)&(arg) + 3))


#pragma GLOBAL_ASM("asm/nonmatchings/game_19A8B0/func_1516D400.s")

void func_1516D4E8(
    s32 arg0, s32 arg1, s32 arg2, s32 arg3,
    s32 arg4, s32 arg5, s32 arg6, s32 arg7,
    s32 arg8, s32 arg9, s32 arg10, s32 arg11,
    s32 arg12, s32 arg13, s32 arg14, s32 arg15,
    s32 arg16, s32 arg17, s32 arg18, s32 arg19,
    s32 arg20, s32 arg21, s32 arg22, s32 arg23,
    s32 arg24, s32 arg25, s32 arg26, s32 arg27,
    volatile s32 arg28, s32 arg29, s32 arg30) {
    struct Obj1516D4E8 *ret;
    s32 temp_a2;

    ret = (struct Obj1516D4E8 *)func_15167A68(arg27 != 0 ? 0x67 : 0x12, arg30, 0x34, 0, LOW_U8(arg29), 1);
    if (ret != NULL) {
        ret->unkE = LOW_S16(arg0);
        ret->unk10 = LOW_S16(arg1);
        ret->unk12 = LOW_S16(arg2);
        ret->unk1A = LOW_U8(arg3);
        ret->unk1B = LOW_U8(arg4);
        ret->unk1C = LOW_U8(arg5);
        ret->unk1D = LOW_U8(arg6);
        ret->unk1E = LOW_U8(arg7);
        ret->unk1F = LOW_U8(arg8);
        ret->unk20 = LOW_U8(arg9);
        ret->unk21 = LOW_U8(arg10);
        ret->unk22 = LOW_U8(arg11);
        ret->unk23 = LOW_U8(arg12);
        ret->unk14 = LOW_S16(arg23);
        ret->unk16 = LOW_S16(arg24);
        ret->unk24 = LOW_U8(arg25);
        ret->unk18 = LOW_S16(arg26);
        ret->unk25 = 0;
        ret->unk26 = LOW_U8(arg13);
        ret->unk27 = LOW_U8(arg14);
        ret->unk28 = LOW_U8(arg15);
        temp_a2 = arg28;
        ret->unk29 = LOW_U8(arg16);
        ret->unk2A = LOW_U8(arg17);
        ret->unk2B = LOW_U8(arg18);
        ret->unk2C = LOW_U8(arg19);
        ret->unk2D = LOW_U8(arg20);
        ret->unk2E = LOW_U8(arg21);
        ret->unk2F = LOW_U8(arg22);
        if (temp_a2 != 0) {
            ret->unk30 = func_150448D0(-1, 0, temp_a2, 0x14, 0x14, 0x14, 0, (s32) &ret->unkE, (s32) &ret->unk14);
        } else {
            ret->unk30 = 0;
        }
    }
}

void func_1516972C(struct102 *arg0);
extern s32 D_800BE9E4;
extern s32 (*D_8008CBA0[])(struct Obj1516D4E8 *);
void func_1516D678(struct Obj1516D4E8 *arg0)
{
  s32 temp;
  s32 ptr;
  temp = arg0->unk24;
  if (temp != 0)
  {
    temp -= D_800BE9E4;
    if (temp < 0)
    {
      temp = 0;
    }
    arg0->unk24 = temp;
  }
  if (D_8008CBA0[arg0->unk23](arg0) == 1)
  {
    ptr = arg0->unk30;
    if (ptr != 0)
    {
      *((s16 *) (ptr + 4)) = 0;
    }
    func_1516972C((struct102 *) arg0);
  }
  else
  {
    temp = arg0->unk10;
    temp = (temp << 8) + arg0->unk25;
    temp += ((u32) arg0->unk18) * ((u32) D_800BE9E4);
    arg0->unk10 = temp >> 8;
    arg0->unk25 = temp & 0xFFFFu;
  }
}


#pragma GLOBAL_ASM("asm/nonmatchings/game_19A8B0/func_1516D738.s")

void func_1516D99C(
    s32 arg0, s32 arg1, s32 arg2, s32 arg3,
    s32 arg4, s32 arg5, s32 arg6, s32 arg7,
    s32 arg8, s32 arg9, s32 arg10, s32 arg11,
    s32 arg12, s32 arg13, s32 arg14, s32 arg15,
    s32 arg16, s32 arg17, s32 arg18, s32 arg19,
    s32 arg20, s32 arg21, s32 arg22, s32 arg23,
    s32 arg24, s32 arg25, s32 arg26, s32 arg27,
    s32 arg28, s32 arg29, s32 arg30, s32 arg31,
    s32 arg32, s32 arg33, s32 arg34, s32 arg35,
    s32 arg36, s32 arg37, s32 arg38, s32 arg39,
    s32 arg40, s32 arg41, s32 arg42, s32 arg43,
    s32 arg44, s32 arg45, s32 arg46, s32 arg47,
    s32 arg48) {
    struct Obj1516D99C *ret;
    s32 temp_v1;

    ret = func_15167A68(arg44 != 0 ? 0x66 : 0x11, arg48, 0x4C, 0, LOW_U8(arg47), 1);
    if (ret != NULL) {
        ret->unkE = LOW_S16(arg0);
        ret->unk10 = LOW_S16(arg1);
        ret->unk12 = LOW_S16(arg2);
        ret->unk14 = LOW_S16(arg27);
        ret->unk16 = LOW_S16(arg28);
        ret->unk18 = LOW_S16(arg29);
        ret->unk1A = LOW_S16(arg30);
        ret->unk24 = LOW_U8(arg3);
        ret->unk25 = LOW_U8(arg4);
        ret->unk26 = LOW_U8(arg5);
        ret->unk27 = LOW_U8(arg6);
        ret->unk28 = LOW_U8(arg7);
        ret->unk2A = LOW_U8(arg9);
        ret->unk2B = LOW_U8(arg10);
        ret->unk2C = LOW_U8(arg11);
        ret->unk29 = LOW_U8(arg8);
        ret->unk2D = LOW_U8(arg12);
        ret->unk2E = LOW_U8(arg13);
        ret->unk2F = LOW_U8(arg14);
        ret->unk30 = LOW_U8(arg15);
        ret->unk31 = LOW_U8(arg16);
        ret->unk32 = LOW_U8(arg17);
        ret->unk33 = LOW_U8(arg18);
        ret->unk34 = LOW_U8(arg19);
        ret->unk35 = LOW_U8(arg20);
        ret->unk36 = LOW_U8(arg21);
        ret->unk37 = LOW_U8(arg22);
        ret->unk38 = LOW_U8(arg23);
        ret->unk39 = LOW_U8(arg24);
        ret->unk3A = LOW_U8(arg25);
        temp_v1 = LOW_U16(arg31);
        ret->unk3B = LOW_U8(arg26);
        ret->unk20 = temp_v1;
        ret->unk3C = temp_v1;
        ret->unk3D = LOW_U8(arg32);
        ret->unk3E = LOW_U8(arg33);
        ret->unk3F = LOW_U8(arg34);
        ret->unk40 = LOW_U8(arg35);
        ret->unk1C = LOW_S16(arg36);
        ret->unk1E = LOW_U16(arg37);
        ret->unk22 = LOW_U16(arg38);
        ret->unk41 = LOW_U8(arg39);
        ret->unk42 = 0;
        ret->unk43 = LOW_U8(arg40);
        if (arg44 != 0) {
            if (LOW_U8(arg41) >= 4) {
                LOW_U8(arg41) = 3;
            }
        }
        ret->unk44 = LOW_U8(arg41);
        ret->unk45 = LOW_U8(arg42);
        ret->unk46 = LOW_U8(arg43);
        ret->unk47 = LOW_U8(arg45);
        ret->unk48 = LOW_U8(arg46);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_19A8B0/func_1516DB90.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_19A8B0/func_1516E778.s")

extern u8 D_800A6E00[];
extern u8 D_800A6E0C[][3];

s32 func_1516E8CC(struct Obj1516D4E8 *arg0) {
    struct Obj1516D4E8 *vp;
    s32 temp_v1;
    s32 idx;
    s32 temp;
    s32 i;
    f32 frac;
    f32 inv;

    vp = arg0;
    temp_v1 = arg0->unk1F;
    if (arg0->unk24 != 0) {
        if (temp_v1 != 0xFF) {
            temp_v1 += D_800BE9E4 << 5;
            if (temp_v1 >= 0x100) {
                temp_v1 = 0xFF;
            }
            vp->unk1F = temp_v1;
        }
    } else {
        if (temp_v1 != 0) {
            temp_v1 -= D_800BE9E4 << 4;
            if (temp_v1 < 0) {
                temp_v1 = 0;
            }
            vp->unk1F = temp_v1;
        }
    }

    if ((arg0->unk24 == 0) && (temp_v1 == 0)) {
        return 1;
    }

    temp = arg0->unk14;
    idx = arg0->unk24;
    temp += D_800BE9E4 * 10;
    arg0->unk16 = temp;
    arg0->unk14 = temp;

    if (arg0->unk24 == 0) {
        idx += arg0->unk1F >> 5;
    } else {
        idx = idx + 8;
    }

    for (i = vp->unk26; i < vp->unk26 + 8; i++) {
        if (idx >= D_800A6E00[i]) {
            frac = (f32)(idx - D_800A6E00[i]) / (f32)(D_800A6E00[i - 1] - D_800A6E00[i]);
            inv = 1.0f - frac;
            arg0->unk1C = D_800A6E0C[i][0] * inv + D_800A6E0C[i - 1][0] * frac;
            arg0->unk1D = D_800A6E0C[i][1] * inv + D_800A6E0C[i - 1][1] * frac;
            arg0->unk1E = D_800A6E0C[i][2] * inv + D_800A6E0C[i - 1][2] * frac;
            break;
        }
    }
    return 0;
}

/* The ROM has 8 bytes of `jr ra; nop` between func_1516E8CC and func_1516ECAC.
 * splat has no symbol for them so they fold into func_1516E8CC's size; they are an
 * empty leaf function, the same shape game_981E0.c func_1507304C and
 * game_1A5440.c func_15178750_pad already reconstruct. */
static void func_1516ECA4_pad(void) {
}

s32 func_1516ECAC(Obj1516FadeState *arg0) {
    s32 temp_v0;
    s32 temp_v1;
    s32 temp_a1;
    s32 temp;

    temp_v0 = arg0->field_0x24;
    temp_v1 = arg0->field_0x1F;
    if (temp_v0 != 0) {
        if (temp_v1 != 0xFF) {
            temp_v1 += D_800BE9E4 << 7;
            if (temp_v1 >= 0x100) {
                temp_v1 = 0xFF;
            }
            arg0->field_0x1F = temp_v1;
            temp_v0 = ((volatile Obj1516FadeState *)arg0)->field_0x24;
        }
    } else {
        if (temp_v1 != 0) {
            temp_v1 -= D_800BE9E4 * arg0->field_0x26;
            if (temp_v1 < 0) {
                temp_v1 = 0;
            }
            arg0->field_0x1F = temp_v1;
            temp_v0 = ((volatile Obj1516FadeState *)arg0)->field_0x24;
        }
    }

    if ((temp_v0 == 0) && (temp_v1 == 0)) {
        return 1;
    }

    temp_a1 = (arg0->field_0x2C << 8) | arg0->field_0x2D;
    temp = (temp_a1 * temp_v1) >> 7;
    arg0->field_0x16 = temp;
    arg0->field_0x14 = temp;
    return 0;
}

extern void func_1516D99C();

void func_1516ED68(s32 a0, s32 a1, u8 a2, s32 a3) {
    u8 v;
    v = D_800CC2D4[a0 * 812];
    if (v != 0x3A) {
        return;
    }
    func_1516D99C(5, 0, 0, 4,
        0, 0xFF, 0xFF, 0xFF, 0, 0, 0, 0,
        2, 0, 0, 0, 0, 0, 0, 8,
        0, 0, 0, 0, 0, 0, 0, 0x124,
        0x124, 0, 0, a1, 0, 0, a0, 0xC,
        0, 0, 0x81, 2, 0, 1, 0, 0,
        0, 5, 0, a2, a3);
}

void func_1516EED4(s32 a0, s32 a1, u8 a2, s32 a3) {
    if (a0 < 4 && (*(u8 (*)[4])&D_800DD2A0)[a0] >= a1) {
        (*(u8 (*)[4])&D_800DD2A0)[a0] = 0;
        func_1516D99C(0, 0, 0, 4,
            0, 0xFF, 0xFF, 0xFF, 0, 0, 0, 0,
            2, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0, 0, 0x200,
            0x200, 0, 0, 0x1E, 0, 0, a0, 0x14,
            0, 0, 0x81, 8, 0, 1, 0, 0,
            0, 0xC, 0, a2, a3);
    }
}

s32 func_1516F024(Obj1516FadeState *arg0) {
    /* Reserves the 16 bytes at the top of the -g3 stack frame (sp+0x58..0x67)
     * that the shipped build allocated but never referenced.  Declared first so
     * the remaining locals land on their original stack homes. */
    s32 pad[4];
    s32 temp_a2;
    struct Table1516F024 sp48;
    struct Table1516F024 sp3C;
    struct Table1516F024 sp30;
    struct Table1516F024 sp24;
    s32 temp_v0;
    s32 temp_v1;
    s32 temp_a1;

    sp48 = D_8008CBC4;
    sp3C = D_8008CBD0;
    sp30 = D_8008CBDC;
    sp24 = D_8008CBE8;

    temp_a1 = arg0->field_0x24;
    temp_a2 = arg0->field_0x2C;
    temp_v0 = arg0->field_0x1F;
    if (temp_a1 != 0) {
        temp_v1 = sp30.unk0[temp_a2];
        if (temp_v0 != temp_v1) {
            temp_v0 += D_800BE9E4 << 4;
            if (temp_v1 < temp_v0) {
                temp_v0 = temp_v1;
            }
            arg0->field_0x1F = temp_v0;
            temp_a1 = ((volatile Obj1516FadeState *)arg0)->field_0x24;
        }
    } else {
        if (temp_v0 != 0) {
            temp_v0 -= D_800BE9E4 * sp24.unk0[temp_a2];
            if (temp_v0 < 0) {
                temp_v0 = 0;
            }
            arg0->field_0x1F = temp_v0;
            temp_a1 = ((volatile Obj1516FadeState *)arg0)->field_0x24;
        }
    }

    if ((temp_a1 == 0) && (temp_v0 == 0)) {
        return 1;
    }

    func_1516F864((s32)arg0);
    temp_v0 = arg0->field_0x14;
    temp_v0 += D_800BE9E4 * sp3C.unk0[temp_a2];
    arg0->field_0x16 = temp_v0;
    arg0->field_0x14 = temp_v0;
    if (temp_a2 == 3) {
        arg0->field_0x18 = 0x64;
    }
    func_1516F94C((s32)arg0, sp48.unk0[temp_a2]);
    return 0;
}

extern void func_1516D99C();

void func_1516F1C0(s32 a0, s32 a1, u8 a2, s32 a3) {
    func_1516D99C(2, 0, 0, 0x2D,
        0, 0xFF, 0xFF, 0xFF, 0, 0, 0, 0,
        2, 0, 0, 0, 0, 0, 0, 1,
        0, 0, 0, 0, 0, 0, 0, 0x50,
        0x50, 0, 0, a1, 0xA, 0xA, a0, 0x3C,
        0, 0, 0x81, 4, 0, 1, 0, 0,
        0, 4, 2, a2, a3);
}

void func_1516F2F8(u8 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5) {
    func_1516D99C(3, 0, 0, 0x2B,
        0, 0xFF, 0xFF, 0xFF, 0, 0, 0, 0,
        2, 0, 0, 0, 0, 0, 0, 2,
        0, 0, 0, 0, 0, 0, 0, 0x50,
        0x50, 0, 0, a1, 4, 4, a0, 0x10,
        0, 0, 0x81, 4, 0, 1, 0, 0,
        0, 1, 0, LOW_U8(a4), a5);
    func_1516D99C(3, 0, 0, 0x2B,
        0, 0xFF, 0xFF, 0xFF, 0, 0, 0, 0,
        2, 0, 0, 0, 0, 0, 0, 3,
        0, 0, 0, 0, 0, 0, 0, 0x50,
        0x50, 0, 0, 7, 4, 4, a0, a2,
        0, 0, 0x81, 5, 0, 1, 0, 0,
        0, 1, a3, LOW_U8(a4), a5);
}

/* Spawns two type-0xD particle emitters at (arg0, arg1, arg2) -- identical apart
 * from their spawn table entry (arg10 vs arg11) and the second one's extra mode
 * byte 6 -- then plays 3-D sound 7 at the same spot with arg3 as its user data.
 * The position is latched into posX/posY/posZ while the first emitter is being
 * built so both later calls reuse it. */
void func_1516F548(
    s32 arg0, s32 arg1, s32 arg2, s32 arg3,
    s32 arg4, s32 arg5, s32 arg6, s32 arg7,
    s32 arg8, s32 arg9, s32 arg10, s32 arg11,
    s32 arg12, s32 arg13, s32 arg14, s32 arg15,
    s32 arg16) {
    s32 posX;
    s32 posY;
    s32 posZ;

    func_1516D99C(posX = (s16)arg0, posY = (s16)arg1, posZ = (s16)arg2, 0xD,
        0, 0x67, 0x17, 0xD, 0, 0, 0x12, 0,
        2, (u8)arg4, 0, (u8)arg6, 0, 0, 0, arg10,
        0, 0, 0, 0, 0, 0, 0, (s16)((arg7 << 12) / 4096),
        (s16)((arg7 << 12) / 4096), (s16)((arg8 << 12) / 4096), (s16)((arg8 << 12) / 4096), (u16)arg3, (u8)arg9, 0x14, 0xFF, 0x10,
        (s16)arg5, 0xC8, 1, 0, 0, 1, 0, 0,
        0, 0, 0, LOW_U8(arg15), arg16);
    func_1516D99C(LOW_S16(posX), LOW_S16(posY), LOW_S16(posZ), 0xD,
        0, 0x67, 0x17, 0xD, 0, 0, 0x12, 0,
        2, (u8)arg4, 0, (u8)arg6, 0, 0, 0, arg11,
        0, 0, 0, 0, 0, 0, 0, (s16)((arg7 << 12) / 4096),
        (s16)((arg7 << 12) / 4096), (s16)((arg8 << 12) / 4096), (s16)((arg8 << 12) / 4096), (u16)arg3, (u8)arg9, 0x14, 0xFF, 0x10,
        (s16)arg5, 0xC8, 1, 6, 0, 1, 0, 0,
        0, 0, 0, LOW_U8(arg15), arg16);
    func_1000FA64(7, LOW_S16(posX), LOW_S16(posY), LOW_S16(posZ), 0x36B0, 0x3E8, 0x64,
        (s32)func_1000EBC4, (void *)arg3, 0, 0, 0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_19A8B0/func_1516F864.s")

void func_1516F8EC(s32 arg0, s32 arg1)
{
  u8 *ptr;
  s32 val;
  ptr = (u8 *) arg0;
  val = (*((s8 *) (ptr + 0x26))) << 8;
  val += ptr[0x27];
  val = (val * arg1) >> 8;
  ptr[0x26] = val >> 8;
  ptr[0x27] = val & 0xFFFFu;
}

extern void func_1516F8EC(s32, s32);


void func_1516F91C(s32 arg0, s32 arg1)
{
  s32 v0;
  v0 = (*((s8 *) (arg0 + 0x28))) << 8;
  v0 += *((u8 *) (arg0 + 0x29));
  v0 = (v0 * arg1) >> 8;
  *((u8 *) (arg0 + 0x28)) = v0 >> 8;
  *((u8 *) (arg0 + 0x29)) = v0 & 0xFF;
}

extern void func_1516F91C(s32, s32);


extern void func_1516F8EC(s32, s32);
extern void func_1516F91C(s32, s32);

void func_1516F94C(s32 arg0, s32 arg1) {
    func_1516F8EC(arg0, arg1);
    func_1516F91C(arg0, arg1);
}

void func_1516F984(Obj1516F984 *arg0, s32 arg1) {
    s32 temp;
    func_1516F94C((s32)arg0, arg1);
    temp = arg0->field_0x18;
    temp = temp * arg1;
    arg0->field_0x18 = temp >> 8;
}

s32 func_1516F9C4(Obj1516FadeStepState *arg0) {
    s32 temp_a1;
    s32 temp_v0;
    s32 temp;

    temp_a1 = arg0->field_0x24;
    temp_v0 = arg0->field_0x1F;
    if (temp_a1 != 0) {
        if (temp_v0 != 0xFF) {
            temp_v0 += D_800BE9E4 << 4;
            if (temp_v0 >= 0x100) {
                temp_v0 = 0xFF;
            }
            arg0->field_0x1F = temp_v0;
            temp_a1 = ((volatile Obj1516FadeStepState *)arg0)->field_0x24;
        }
    } else {
        if (temp_v0 != 0) {
            temp_v0 -= D_800BE9E4 << 3;
            if (temp_v0 < 0) {
                temp_v0 = 0;
            }
            arg0->field_0x1F = temp_v0;
        }
        temp = (temp_v0 << 9) >> 8;
        arg0->field_0x16 = temp;
        arg0->field_0x14 = temp;
        temp_a1 = ((volatile Obj1516FadeStepState *)arg0)->field_0x24;
    }

    if ((temp_a1 == 0) && (temp_v0 == 0)) {
        return 1;
    }

    func_1516F864((s32)arg0);
    func_1516F984((Obj1516F984 *)arg0, 0xF0);
    return 0;
}

void func_1516FA88(s16 arg0, s16 arg1, s16 arg2, s32 arg3, u8 arg4, s32 arg5) {
    func_1516D99C(arg0, arg1, arg2, 0x1B,
        0, 0xFF, 0xFF, 0xFF, 0, 0xFF, 0xFF, 0xFF,
        3, 0, 0, 0, 0, 0, 0, 0,
        0, 0, 0, 0, 0, 0, 0, 0x400,
        0x400, 0, 0, 2, 0, 0, 0xFF, 0xF,
        0, 0, 9, 0, 0xFF, 0xA, 0x5A, 5,
        arg3, 0, 0, arg4, arg5);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_19A8B0/func_1516FBCC.s")

s32 func_1516FD50(Obj1516FadeStepState *arg0) {
    s32 temp_a1;
    s32 temp_v0;
    s32 temp;

    temp_a1 = arg0->field_0x24;
    temp_v0 = arg0->field_0x1F;
    if (temp_a1 != 0) {
        if (temp_v0 != 0xFF) {
            temp_v0 += D_800BE9E4 << 4;
            if (temp_v0 >= 0x100) {
                temp_v0 = 0xFF;
            }
            arg0->field_0x1F = temp_v0;
            temp_a1 = ((volatile Obj1516FadeStepState *)arg0)->field_0x24;
        }
    } else {
        if (temp_v0 != 0) {
            temp_v0 -= D_800BE9E4 << 3;
            if (temp_v0 < 0) {
                temp_v0 = 0;
            }
            arg0->field_0x1F = temp_v0;
        }
        temp = (temp_v0 << 9) >> 8;
        arg0->field_0x16 = temp;
        arg0->field_0x14 = temp;
        temp_a1 = ((volatile Obj1516FadeStepState *)arg0)->field_0x24;
    }

    if ((temp_a1 == 0) && (temp_v0 == 0)) {
        return 1;
    }

    func_1516F864((s32)arg0);
    arg0->field_0x18 = arg0->field_0x18 + arg0->field_0x2C;
    return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_19A8B0/func_1516FE1C.s")

extern u8 func_150ADA20(void);
extern f32 func_150489B0(u8);
extern f32 func_15048A40(u8);

void func_15170034(s32 arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    s32 mask;
    f32 r;
    f32 sp24;
    f32 sp20;
    s32 v;

    mask = (arg0 & 0x40) ? 0x3F : 0x7F;
    v = func_150ADA20() & mask;
    *arg2 = func_150489B0((u8)v);
    sp20 = func_15048A40((u8)v);
    v = func_150ADA20() & 0xFF;
    sp24 = func_150489B0((u8)v);
    r = func_15048A40((u8)v);
    *arg1 = sp20 * r;
    *arg3 = sp20 * sp24;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_19A8B0/func_151700D8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_19A8B0/func_15170500.s")

typedef struct {
    char pad_0[0x18];
    s16 field_0x18;
    char pad_0x1A[0x5];
    u8 field_0x1F;
    char pad_0x20[0x4];
    u8 field_0x24;
    char pad_0x25[0x1];
    s8 field_0x26;
    u8 field_0x27;
    char pad_0x28[0x7];
    u8 field_0x2F;
} Obj151707E0;

extern s32 func_151EF610(void);

s32 func_151707E0(Obj151707E0 *arg0) {
    s32 active;
    s32 temp;
    s32 velX;

    active = arg0->field_0x24;
    temp = arg0->field_0x1F;
    if (active != 0) {
        if (temp == 0) {
            arg0->field_0x24 = (func_150ADA20() % 0x19U) + 0xC8;
        }
        if (temp != 0xFE) {
            temp += D_800BE9E4 << 6;
            if (temp >= 0xFF) {
                temp = 0xFE;
            }
            arg0->field_0x1F = temp;
        }
    } else {
        if (temp != 0) {
            temp -= D_800BE9E4 << 4;
            if (temp < 0) {
                temp = 0;
            }
            arg0->field_0x1F = temp;
        }
    }

    if ((arg0->field_0x24 == 0) && (temp == 0)) {
        return 1;
    }

    func_1516F864((s32) arg0);
    if (arg0->field_0x2F != 0) {
        func_1516F8EC((s32) arg0, (func_151EF610() % 0x20) + 0xE6);
        func_1516F91C((s32) arg0, (func_151EF610() % 0x20) + 0xE6);
        arg0->field_0x18 = 0;
    } else {
        velX = (arg0->field_0x26 << 8) + arg0->field_0x27;
        temp = arg0->field_0x26 * 0x100;
        temp += arg0->field_0x27;
        if (((velX * velX) + (temp * temp)) >= 0x7D1) {
            func_1516F8EC((s32) arg0, (func_151EF610() % 0x20) + 0xDC);
            func_1516F91C((s32) arg0, (func_151EF610() % 0x20) + 0xDC);
        }
        arg0->field_0x18 = 0;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_19A8B0/func_151709B4.s")
