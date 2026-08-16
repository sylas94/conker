#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern f32 D_800A9D84;
extern f32 D_800A9D88;
extern f32 D_800A9D80;
extern void func_151D5D60();
void *func_1513418C(void *, s32, s32, s32);
void func_1516962C(s32, struct102 *, s32);
void func_151AE984(f32 *, f32, f32, f32, s32, u8);
void func_151AEAB4(f32 *, s32, u8);
void func_15143134(f32 *, f32 *, s32);
void func_15135DD0(f32 *, f32 *, f32, u8, s32);
void func_151AF388(f32 *, f32, f32, f32, s32);

typedef struct {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 pad1[3];
    /* 0x04 */ f32 unk4[3];
    /* 0x10 */ f32 unk10[3];
} struct_AF4D0;

typedef struct {
    char pad_0[0x74];
    u8 field_0x74;
    char pad_0x75[0x15F];
    s32 field_0x1D4;
} GameObjectTransformOwner;

typedef struct {
    char pad_0[0x44];
    s32 field_0x44;
    char pad_0x48[0x4];
    f32 field_0x4C;
    s8 field_0x50;
    s8 field_0x51;
    s16 field_0x52;
} ObjectFxPayload;

typedef struct {
    char pad_0[0x98];
    s8 field_0x98;
    char pad_0x99[0x3];
    ObjectFxPayload *field_0x9C;
    char pad_0xA0[0xE];
    u8 field_0xAE;
} ObjectFxControl;

typedef struct {
    char pad_0[0x3C];
    f32 field_0x3C;
    char pad_0x40[0x36];
    u16 field_0x76;
    char pad_0x78[0x2A4];
    ObjectFxControl *field_0x31C;
} GameObjectFxOwner;

typedef struct {
    char pad_0[0x10];
    s32 field_0x10;
    s32 field_0x14;
    u8 field_0x18;
    char pad_0x19[0x3];
    s32 field_0x1C;
    u8 field_0x20;
    char pad_0x21[0x3];
    s32 field_0x24;
    f32 field_0x28;
} ObjectLinkPayload;

typedef struct {
    char pad_0[0x4];
    s16 field_0x04;
    u16 field_0x06;
    f32 field_0x08;
    f32 field_0x0C;
    s16 field_0x10;
    u16 field_0x12;
    u8 field_0x14;
    u8 field_0x15;
    char pad_0x16[0x2];
    f32 field_0x18;
    f32 field_0x1C;
    f32 field_0x20;
    f32 field_0x24;
    f32 field_0x28;
} ObjectSpawnParams;

typedef struct {
    s32 field_0x00;
    s32 field_0x04;
    u8 field_0x08;
} ObjectSpawnPayload;

extern struct_AF4D0 D_800A9DF0[];
extern f32 D_800AA0E4;
extern s8 D_800A9023[];
extern ObjectSpawnParams D_800A9180[];

void func_15143794(s32, s32, f32, f32 *);
void func_151D9014(f32 *, f32 *, s32, f32, s32, s32, f32, s32, f32, f32, s32, s32, s32, s32, u8, s32);

#pragma GLOBAL_ASM("asm/nonmatchings/game_1D92F0/func_151ABE40.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1D92F0/func_151AC078.s")

s32 func_151AC3CC(s16 *arg0) {
    u8 *ptr = *(u8 **)((u8 *)arg0 + 0x98);
    s32 val = arg0[0x1C / 2] << 3;
    if (val >= 0x100) {
        val = 0xFF;
    }
    if (val < ptr[0x1B]) {
        ptr[0x1B] = val;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1D92F0/func_151AC408.s")

u8 func_151D8E20(void);

typedef struct {
    f32 field_0x00;
    f32 field_0x04;
    f32 field_0x08;
    f32 field_0x0C;
    f32 field_0x10;
} ObjectEffectSample;

typedef struct {
    f32 field_0x00;
    char pad_0x04[0x17];
    u8 field_0x1B;
    char pad_0x1C[0x4];
    u8 field_0x20;
} ObjectEffectPayloadData;

typedef struct {
    char pad_0[0x1];
    u8 field_0x01;
    char pad_0x02[0xA];
    u8 field_0x0C;
    char pad_0x0D[0x20];
    s8 field_0x2D;
    char pad_0x2E[0x66];
    ObjectEffectSample *field_0x94;
    ObjectEffectPayloadData *field_0x98;
} ObjectEffectState;

s32 func_151AC550(ObjectEffectState *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4, s32 arg5) {
    ObjectEffectPayloadData *ptr = arg0->field_0x98;
    ObjectEffectSample *arr = arg0->field_0x94;
    f32 sp34[3];

    sp34[0] = arr[arg0->field_0x2D].field_0x00;
    sp34[1] = arg4;
    sp34[2] = arr[arg0->field_0x2D].field_0x08;
    func_151DBCBC(func_151D8E20(), ptr->field_0x00 * 7.0f, ptr->field_0x1B, arg5, sp34, arg0->field_0x0C, arg0->field_0x01);
    ptr->field_0x20 = 4;
    return 1;
}

s32 func_151AC61C(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5, s32 arg6, s32 arg7, s16 arg8, s32 arg9, s32 argA, s32 argB, s32 argC, ObjectSpawnPayload *argD, u8 argE) {
    ObjectSpawnParams *params;
    f32 sp78[4];
    f32 sp64[5];
    s32 temp1[2];
    f32 tempf1;
    s32 temp0;
    f32 tempf0;
    f32 tempf2;

    params = &D_800A9180[D_800A9023[argB * 5]];
    sp78[-1] = arg2;
    sp78[0] = arg3;
    sp78[1] = arg4;

    temp1[0] = func_150ADA20();
    tempf0 = func_150ADA68();
    func_15143794(arg8,
                  (s16)((temp1[0] % (u32)(params->field_0x06 + 1)) + params->field_0x04),
                  ((tempf0 = tempf0) * params->field_0x0C) + params->field_0x08,
                  &sp64[1]);

    tempf0 = func_150ADA68();
    temp0 = func_150ADA20();
    temp1[0] = func_150ADA20();
    tempf1 = func_150ADA68();
    tempf2 = func_150ADA68();

    func_151D9014(&sp78[-1],
                  &sp64[1],
                  argD->field_0x08,
                  ((tempf0 = tempf0) * params->field_0x24) + params->field_0x20,
                  (temp0 % (u32)(params->field_0x12 + 1)) + params->field_0x10,
                  (temp1[0] % (u32)(params->field_0x15 + 1)) + params->field_0x14,
                  ((tempf1 = tempf1) * params->field_0x1C) + params->field_0x18,
                  tempf2 < params->field_0x28,
                  1.0f,
                  1.0f,
                  1,
                  argD->field_0x00,
                  1,
                  0,
                  argE,
                  argD->field_0x04);
    return 1;
}

typedef struct {
    char pad_0[0x2C];
    f32 field_0x2C;
    f32 field_0x30;
    f32 field_0x34;
    f32 field_0x38;
    f32 field_0x3C;
    char pad_0x40[0xC];
    f32 field_0x4C;
    f32 field_0x50;
    char pad_0x54[0x6C];
    char field_0xC0[0x40];
    s16 *field_0x100[1];
} ObjectGeometryState;

s16 *func_151AC810(ObjectGeometryState *arg0, s16 arg1) {
    s16 *var_v0;
    s16 *ret;
    f32 temp_f0;
    f32 temp_f14;
    f32 temp_f2;
    f32 temp_f12;
    u8 sp37;

    func_151D5D60(arg0->field_0x100, arg1, 0x40, &var_v0, &sp37);
    ret = var_v0;
    if (var_v0) {
        if (sp37) {
            memcpy(arg0->field_0x100[arg1], arg0->field_0xC0, 0x40);
            memcpy(arg0->field_0x100[arg1] + 0x20, arg0->field_0xC0, 0x40);
        }
    } else {
        return 0;
    }

    temp_f0 = arg0->field_0x2C * arg0->field_0x4C;
    temp_f14 = arg0->field_0x30 * arg0->field_0x50;
    temp_f2 = D_800DD1D8[arg1] * temp_f0;
    temp_f12 = D_800DD1E8[arg1] * temp_f0;

    var_v0[3] = 0;
    var_v0[0xB] = 0;
    var_v0[0x13] = 0;
    var_v0[0x1B] = 0;
    var_v0[0] = var_v0[0x18] = arg0->field_0x34 + temp_f12;
    var_v0[1] = var_v0[9] = arg0->field_0x38;
    var_v0[2] = var_v0[0x1A] = arg0->field_0x3C - temp_f2;
    var_v0[8] = var_v0[0x10] = arg0->field_0x34 - temp_f12;
    var_v0[0x11] = var_v0[0x19] = arg0->field_0x38 + temp_f14;
    var_v0[0xA] = var_v0[0x12] = arg0->field_0x3C + temp_f2;

    return ret;
}

extern f32 D_800BE9A4;

s32 func_151AC9EC(ObjectGeometryState *arg0) {
    f32 temp = arg0->field_0x4C * D_800BE9A4;
    arg0->field_0x2C += temp;
    arg0->field_0x30 += temp;
    return 1;
}

s32 func_151ACA20(s16 *arg0) {
    s32 val = 0xFF;
    if (arg0[0x1C / 2] < 0x10) {
        val = (s16)(arg0[0x1C / 2] << 4);
    }
    if (val < ((u8 *)arg0)[0x5C]) {
        ((u8 *)arg0)[0x5C] = val;
    }
    return 1;
}

extern u8 *func_15167A68(s32, s32, s32, s32, s32, s32);
s32 func_151ACB38(u8 *arg0, u8 *arg1);

s32 func_151ACA60(struct127 *arg0, f32 arg1, s32 arg2) {
    ObjectLinkPayload *temp;

    if (arg0 == 0) {
        return 0;
    }
    temp = (ObjectLinkPayload *)func_15167A68(0x30, 0, arg2 + 0x30, 1, 0xFF, 1);
    if (temp == 0) {
        return 0;
    }
    if (func_151ACB38((u8 *)arg0, &temp->field_0x18) == 0) {
        func_1516979C((struct102 *)temp);
        return 0;
    }
    temp->field_0x1C = (s32)arg0;
    temp->field_0x20 = arg0->unique_id;
    temp->field_0x24 = arg0 - D_800CC2D0;
    temp->field_0x28 = arg1;
    temp->field_0x10 = 1;
    temp->field_0x14 = 0;
    return (s32)temp;
}

s32 func_151ACB38(u8 *arg0, u8 *arg1) {
    s32 ret = 0;
    if (arg0[0x3B] == 1) {
        arg1[0] = 1;
        ret = 1;
    }
    return ret;
}

s32 func_151AE3A8(u8 *arg0);
s32 func_151ACB60(u8 *arg0)
{
  s32 result;
  s32 v0 = *((s32 *) ((*((s32 *) ((*((s32 *) (arg0 + 0x1C))) + 0x31C))) + 0x9C));
  if (v0 != 0)
  {
    result = func_151AE3A8(arg0);
    if (arg0)
    {
    }
    return result;
  }
}


void func_151ACB94(s32 arg0, s32 arg1, u8 arg2) {
    func_15169850(arg1, arg2, arg0 + 0x1C, arg0 + 0x20, arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1D92F0/func_151ACBD4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1D92F0/func_151AD174.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1D92F0/func_151AD92C.s")

void func_151AE0E4(u8 *arg0, u8 arg1);
void func_151AE264(GameObjectFxOwner *arg0);

void func_151AE06C(struct127 *arg0, struct133 *arg1) {
    u8 sp1F;
    u8 temp_a1;
    u8 sp1E;

    if (func_151ACB38((u8 *)arg0, &sp1F) != 0) {
        temp_a1 = arg1->unk1B;
        if (*((u8 *)arg0->unk31C + 0x98) == 0) {
            func_151AE0E4((u8 *)arg0, temp_a1);
        } else if (temp_a1 == *((u8 *)arg0->unk31C + 0x98)) {
        } else {
            sp1E = temp_a1;
            func_151AE264((GameObjectFxOwner *)arg0);
            func_151AE0E4((u8 *)arg0, sp1E);
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1D92F0/func_151AE0E4.s")

extern f32 D_800A9294;

void func_151AE264(GameObjectFxOwner *arg0) {
    f32 temp = arg0->field_0x3C * D_800A9294;
    ObjectFxPayload *v0 = arg0->field_0x31C->field_0x9C;
    v0->field_0x4C = temp;
    v0->field_0x50 = arg0->field_0x76 >> 8;
    v0->field_0x51 = arg0->field_0x31C->field_0xAE;
    v0->field_0x52 = 0x14;
    v0->field_0x44 = 0;
    arg0->field_0x31C->field_0x98 = 0;
    arg0->field_0x31C->field_0x9C = 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1D92F0/func_151AE2BC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1D92F0/func_151AE3A8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1D92F0/func_151AE590.s")

void func_151AE640(s32 *arg0, s32 *arg1, u8 arg2)
{
  s32 *ptr = arg0;
  s32 temp;
  if (arg2 == ((unsigned short) 0))
  {
    temp = arg1[0];
    if (temp == ptr[0x11])
    {
      ptr[0x11] = 0;
    }
 dummy_label_988571: ;
  }
  else
    if (arg2 == 0x2D)
  {
    temp = arg1[0];
    if (temp == ptr[0x11])
    {
      ptr[0x11] = arg1[1];
    }
    else
      if (arg1[1] == ptr[0x11])
    {
      ptr[0x11] = temp;
    }
  }
}


extern f32 D_800A9D70;
s32 func_15045800(f32 *arg0, s32 arg1, f32 arg2, s32 arg3);
s32 func_151ABE40(f32 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
s32 func_10010FFC(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
void func_151AE6B0(u8 *arg0)
{
  u8 *v1 = *((u8 **) (arg0 + 0x18));
  f32 sp30[3];
  s32 temp;
 goto dummy_label_19982; dummy_label_19982: ;
  sp30[0] = *((f32 *) (v1 + 0x14));
  if (D_800A9D70 < (*((f32 *) (v1 + 0x118))))
  {
    sp30[1] = (*((f32 *) (v1 + 0x118))) + 100.0f;
  }
  else
  {
    sp30[1] = (*((f32 *) (v1 + 0x18))) + 150.0f;
  }
  sp30[2] = *((f32 *) (v1 + 0x1C));
  temp = (s32) (arg0 + 0x34);
  if (func_15045800(sp30, 0, sp30[1] - 300.0f, temp) != 0)
  {
    sp30[1] = *((f32 *) (arg0 + 0x34));
    func_151ABE40(sp30, temp, 5, arg0[0xC], arg0[0x1]);
    func_10010FFC(0, 0x11, 0x5208, 0, 0, (s32) v1);
  }
}


void *func_151AE7B0(struct102 *arg0, f32 arg1, s16 arg2, u8 arg3, s32 arg4) {
    void *result;
    struct {
        s32 unk0;
        s32 unk4;
        u8 unk8;
        u8 pad9[3];
        struct102 *unkC;
        u8 unk10;
        u8 pad11[3];
        f32 unk14;
        f32 unk18;
        f32 unk1C;
        f32 unk20;
        f32 unk24;
        s16 unk28;
        u8 unk2A;
        u8 unk2B;
        s8 unk2C;
        u8 unk2D;
    } sp1C;

    if (arg0 == 0) {
        return 0;
    }

    func_1516962C(0x28, arg0, 0x11);
    sp1C.unk0 = 0;
    sp1C.unk4 = 0;
    sp1C.unk8 = *((u8 *)arg0 + 0x3B);
    sp1C.unkC = arg0;
    sp1C.unk10 = 1;
    sp1C.unk14 = 0.0f;
    sp1C.unk18 = 0.0f;
    sp1C.unk1C = 0.0f;
    sp1C.unk20 = D_800A9D80;
    sp1C.unk24 = arg1;
    sp1C.unk2A = 2;
    if (arg2 != 0) {
        sp1C.unk28 = arg2;
        sp1C.unk2A = 6;
    } else {
        sp1C.unk28 = 0x12C;
    }
    sp1C.unk2B = 6;
    sp1C.unk2C = -1;
    sp1C.unk2D = 5;
    result = func_1513418C(&sp1C, 0, arg3, arg4);
    return result;
}

void func_151AE890(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, u8 *arg6) {
    f32 sp2C[3];
    register f32 temp_f0;

    sp2C[0] = arg0;
    sp2C[1] = arg1;
    sp2C[2] = arg2;
    temp_f0 = func_150ADA68();
    if (temp_f0 < D_800A9D84) {
        return;
    }
    if (temp_f0 < 0.25f) {
        register s32 temp_a1;

        temp_f0 = func_150ADA68();
        temp_a1 = (0.0f < temp_f0) ? 1 : 0;
        func_151AEAB4(sp2C, temp_a1, arg6[0xC]);
    } else {
        register s32 temp_v0;

        temp_f0 = func_150ADA68();
        temp_v0 = (D_800A9D88 < temp_f0) ? 1 : 0;
        func_151AE984(sp2C, arg3, arg4, arg5, temp_v0, arg6[0xC]);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1D92F0/func_151AE984.s")

u8 func_150ADA20(void);
f32 func_150ADA68(void);
f32 func_151423D8(u8);
extern f32 D_800A9D98;
extern f32 D_800A9D9C;
extern f32 D_800A9DA0;
extern f32 D_800A9DA4;
void func_151AEAB4(f32 *, s32, u8);
void func_151DA6F8(f32 *, f32 *, f32, s16, s32, f32, s32, s32, f32, f32, s32, u8, s32, s16, s16, s32, u8, s32);
void func_151AEAB4(f32 *arg0, s32 arg1, u8 arg2)
{
  s32 pad94;
  struct 
  {
    u32 sp60;
    u32 sp64;
    f32 sp68;
    u8 pad6C[4];
    f32 sp70;
    f32 sp74;
    f32 sp78;
    f32 sp7C;
    u8 pad80[6];
    u8 sp86;
    u8 sp87;
    f32 sp88[3];
  } sp;
  f32 temp_f12;
  f32 temp_f2;
  sp.sp87 = func_150ADA20();
  sp.sp86 = (u8) (func_150ADA20() & 0x7F) - 0x3F;
  sp.sp7C = func_151423D8(sp.sp87);
  sp.sp78 = func_151423D8((u8) (sp.sp87 - 0x40));
  sp.sp74 = func_151423D8(sp.sp86);
  sp.sp70 = func_151423D8((u8) (sp.sp86 - 0x40));
  temp_f2 = ((func_150ADA68() * 80.0f) + 20.0f) * D_800A9D98;
  temp_f12 = temp_f2 * sp.sp74;
  sp.sp88[0] = temp_f12 * sp.sp78;
  sp.sp88[1] = (-temp_f2) * sp.sp70;
  sp.sp88[2] = temp_f12 * sp.sp7C;
  goto next;
  next:
  *((f32 *) (((u8 *) (&sp)) - 4)) = func_150ADA68();

  sp.sp60 = func_150ADA20();
  sp.sp64 = func_150ADA20();
  sp.sp68 = func_150ADA68();
  func_151DA6F8(arg0, sp.sp88, ((*((f32 *) (((u8 *) (&sp)) - 4))) * D_800A9D9C) + D_800A9DA0, (s16) ((sp.sp60 % 41U) + 0x3C), (sp.sp64 % 101U) + 0x9B, (sp.sp68 * 4.0f) + D_800A9DA4, (func_150ADA20() % 5U) + 3, ((u8 *) (&arg1))[3], 1.0f, 1.0f, 0, 0, 0, 0x10, 0xF, 0, arg2, 1);
}


#pragma GLOBAL_ASM("asm/nonmatchings/game_1D92F0/func_151AECA0.s")

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ u8  unk8;
    /* 0x09 */ u8  pad9[0x3];
    /* 0x0C */ struct102 *unkC;
    /* 0x10 */ u8  unk10;
    /* 0x11 */ u8  pad11[0x3];
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ s16 unk28;
    /* 0x2A */ u8  unk2A;
    /* 0x2B */ u8  unk2B;
    /* 0x2C */ s8  unk2C;
    /* 0x2D */ u8  unk2D;
} struct_AF270;

extern f32 D_800A9DCC;
extern f32 D_800A9DD0;
void func_1516962C(s32, struct102 *, s32);
void *func_1513418C(void *, s32, s32, s32);

void *func_151AF270(struct102 *arg0, s32 arg1, s32 arg2) {
    void *result;
    struct_AF270 sp1C;

    if (arg0 == 0) {
        return 0;
    }
    func_1516962C(0x28, arg0, 0x16);
    sp1C.unk0 = 0;
    sp1C.unk4 = 0;
    sp1C.unk8 = *((u8 *)arg0 + 0x3B);
    sp1C.unkC = arg0;
    sp1C.unk10 = 1;
    sp1C.unk14 = 0.0f;
    sp1C.unk18 = 0.0f;
    sp1C.unk1C = 0.0f;
    sp1C.unk20 = D_800A9DCC;
    sp1C.unk24 = D_800A9DD0;
    sp1C.unk2A = 6;
    sp1C.unk28 = 0x140;
    sp1C.unk2B = 0xA;
    sp1C.unk2C = -1;
    sp1C.unk2D = 9;
    result = func_1513418C(&sp1C, 0, (u8)arg1, arg2);
    return result;
}

void func_151AF338(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, void *arg6) {
    f32 sp24[3];

    sp24[0] = arg0;
    sp24[1] = arg1;
    sp24[2] = arg2;
    func_151AF388(sp24, arg3, arg4, arg5, *(u8 *)((s32)arg6 + 0xC));
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1D92F0/func_151AF388.s")

void func_151AF4D0(GameObjectTransformOwner *arg0, s32 arg1, s32 arg2, s32 arg3) {
    f32 sp44[3];
    f32 sp38[3];
    s32 temp_a2;
    struct_AF4D0 *temp_v0;
    s32 temp_v1;

    if (arg0 != 0) {
        temp_v1 = arg0->field_0x1D4;
        if (temp_v1 != 0) {
            if ((arg0->field_0x74 & 0xF) != 0xF) {
                temp_v0 = &D_800A9DF0[(u8)arg1];
                temp_a2 = temp_v1;
                temp_a2 += temp_v0->unk0 << 6;
                func_15143134(temp_v0->unk4, sp44, temp_a2);
                func_15143134(temp_v0->unk10, sp38, temp_a2);
                func_15135DD0(sp44, sp38, ((func_150ADA68() * 170.0f) + 71.0f) * D_800AA0E4, (u8)arg2, arg3);
            }
        }
    }
}
