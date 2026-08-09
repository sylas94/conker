#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_E4070/func_150B6BC0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_E4070/func_150B6C90.s")

extern s32 *D_800D9898[];
extern s32 *D_800D98A4[];

void func_150B6D34(void) {
    s32 i;
    s32 *e;

    i = 0;
    do {
        e = D_800D9898[i + 5];
        if (e != 0) {
            e[8] = 1;
        }
        i++;
    } while (&D_800D98A4[0] != &D_800D9898[i]);
    D_800D9890 = 3;
}

extern s32 *D_800D9894;
extern s32 *D_800D98C0[];

void func_150B6D78(void) {
    s32 i;

    if (D_800D9894 != 0) {
        func_1516972C((struct102 *)D_800D9894);
        D_800D9894 = 0;
    }
    i = 0;
    do {
        if (D_800D9898[i] != 0) {
            func_1516972C((struct102 *)D_800D9898[i]);
            D_800D9898[i] = 0;
        }
        i++;
    } while (&D_800D98C0[0] != &D_800D9898[i]);
    D_800D9890 = 3;
}

void func_150B6DFC(void *arg0) {
    *(s16 *)((u8 *)arg0 + 0x34) += D_800BE9E4 * 0x30;
    if (*(s16 *)((u8 *)arg0 + 0x34) >= 0x801) {
        *(s16 *)((u8 *)arg0 + 0x34) = -0xC00;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_E4070/func_150B6E3C.s")

typedef struct {
    u8 pad0[0x18];
    s32 unk18;
    u8 pad1C[0x10];
    f32 unk2C;
    f32 unk30;
    u8 pad34[0x11];
    u8 unk45;
} Struct150B709C;

void func_150B709C(Struct150B709C *arg0) {
    s32 div;
    s32 var_v0;
    s32 var_v1;

    div = 0x1E;
    var_v0 = arg0->unk18;
    if (var_v0 == div) {
        var_v1 = arg0->unk45;
        var_v1 += D_800BE9E4 * 8;
        if (var_v1 >= 0x100) {
            var_v1 = 0;
        }
        arg0->unk45 = var_v1;
    }
    var_v0 += D_800BE9E4 * 2;
    if (var_v0 >= 0x1F) {
        var_v0 = div;
    }
    arg0->unk18 = var_v0;
    arg0->unk2C = (f32)(((var_v0 * -0x54) / div) + 0xE6);
    arg0->unk30 = (f32)(((var_v0 * -0x32) / div) + 0xAA);
}

extern s32 D_800BE9E4;
void func_150B71A8(void *arg0)
{
  u8 *base;
  s16 temp_v0;
  unsigned int temp_v1;
  temp_v1 = 0x1000;
  temp_v0 = *((s16 *) (((u8 *) arg0) + 0x38));
  if (temp_v1 == temp_v0)
  {
  }
  else
  {
    *((s16 *) (((u8 *) arg0) + 0x38)) = temp_v0 + (D_800BE9E4 * 0x100);
    if ((*((s16 *) (((u8 *) arg0) - -0x38))) >= 0x1001)
    {
      *((s16 *) (((u8 *) arg0) + 0x38)) = temp_v1;
    }
    return;
  }
  temp_v0 = *((s16 *) (((u8 *) arg0) + 0x3A));
  if (temp_v1 != temp_v0)
  {
    *((s16 *) (((u8 *) arg0) + 0x3A)) = temp_v0 + (D_800BE9E4 * 0x100);
    if ((*((s16 *) (((u8 *) arg0) + 0x3A))) >= 0x1001)
    {
      base = (u8 *) arg0;
      *((s16 *) (base + 0x3A)) = temp_v1;
    }
  }
}


#pragma GLOBAL_ASM("asm/nonmatchings/game_E4070/func_150B7220.s")

typedef struct {
    char pad18[0x18];
    s16 unk18;
    s16 unk1A;
    s32 unk1C;
    s16 unk20;
    s16 unk22;
    s16 unk24;
    char pad26[6];
    f32 unk2C;
    f32 unk30;
} Struct73F0;

void func_150B73F0(Struct73F0 *a0) {
    s32 a = a0->unk18;
    s32 b = a0->unk1A;
    s32 c = a0->unk20;
    s32 e = a0->unk22;
    s32 d = a0->unk1C;
    s32 n = a0->unk24;
    s32 t1 = (n << 16) / d;
    a0->unk2C = (f32)((((c - a) * t1) >> 16) + a);
    a0->unk30 = (f32)((((e - b) * t1) >> 16) + b);
}

typedef struct {
    /* 0x00 */ void *unk0;
    /* 0x04 */ void *unk4;
    /* 0x08 */ u8  pad8[0xC];
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ s16 unk18;
    /* 0x1A */ u8  pad1A[0x2];
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ s16 unk24;
    /* 0x26 */ s16 unk26;
    /* 0x28 */ s16 unk28;
    /* 0x2A */ s16 unk2A;
    /* 0x2C */ s16 unk2C;
    /* 0x2E */ s16 unk2E;
    /* 0x30 */ u8  unk30;
    /* 0x31 */ u8  unk31;
    /* 0x32 */ u8  unk32;
    /* 0x33 */ u8  unk33;
    /* 0x34 */ u8  unk34;
    /* 0x35 */ u8  unk35;
    /* 0x36 */ u8  unk36;
    /* 0x37 */ u8  unk37;
    /* 0x38 */ u8  unk38;
    /* 0x39 */ u8  unk39;
} struct_7484;

extern u8 D_800918DC;
extern u8 D_800918E8;
extern u8 D_800918F4;
extern u8 D_80091900;
struct102 *func_15169968(struct_7484 *);

void func_150B7484(void) {
    struct_7484 sp1C;

    sp1C.unk31 = 1;
    sp1C.unk2C = 0x58;
    sp1C.unk1C = 60.0f;
    sp1C.unk20 = 60.0f;
    sp1C.unk14 = 0;
    sp1C.unk16 = 0;
    sp1C.unk18 = 0;
    sp1C.unk2E = 0x58;
    sp1C.unk30 = 6;
    sp1C.unk0 = &D_800918DC;
    sp1C.unk32 = 0xFF;
    sp1C.unk33 = 0;
    sp1C.unk34 = 0;
    sp1C.unk35 = 0xFF;
    sp1C.unk24 = 0;
    sp1C.unk26 = 0;
    sp1C.unk39 = 0;
    sp1C.unk36 = 7;
    sp1C.unk37 = 0x15;
    sp1C.unk38 = 1;
    sp1C.unk28 = 0x51;
    sp1C.unk2A = 0x51;
    if (D_800D9898[0] != 0) {
        func_1516972C((struct102 *)D_800D9898[0]);
    }
    D_800D9898[0] = (s32 *)func_15169968(&sp1C);
    D_800D9890 = 3;
}

void func_150B7560(void) {
    struct_7484 sp1C;

    if (D_800D9898[0] != 0) {
        func_1516972C((struct102 *)D_800D9898[0]);
        D_800D9898[0] = 0;
    }
    sp1C.unk18 = 0x4D;
    sp1C.unk31 = 0xF;
    sp1C.unk14 = 0;
    sp1C.unk16 = 0;
    sp1C.unk2C = 0x58;
    sp1C.unk2E = 0x58;
    sp1C.unk30 = 0;
    sp1C.unk0 = &D_800918DC;
    sp1C.unk24 = 0;
    sp1C.unk26 = 0;
    sp1C.unk32 = 0xFF;
    sp1C.unk33 = 0;
    sp1C.unk34 = 0;
    sp1C.unk35 = 0xFF;
    sp1C.unk36 = 7;
    sp1C.unk37 = 0x11;
    sp1C.unk38 = 1;
    sp1C.unk39 = 0;
    sp1C.unk28 = 0x1000;
    sp1C.unk2A = 0x1000;
    sp1C.unk1C = 60.0f;
    sp1C.unk20 = 60.0f;
    if (D_800D98A4[0] != 0) {
        func_1516972C((struct102 *)D_800D98A4[0]);
    }
    D_800D98A4[0] = (s32 *)func_15169968(&sp1C);
    D_800D9890 = 3;
}

void func_150B76BC(s32, s32);

void func_150B765C(void) {
    func_150B76BC(0x3C, 1);
    D_800D9890 = 3;
}

void func_150B768C(void) {
    func_150B76BC(0xE6, 2);
    D_800D9890 = 3;
}

void func_150B76BC(s32 arg0, s32 arg1) {
    struct_7484 sp24;

    sp24.unk1C = (f32)arg0;
    sp24.unk20 = 170.0f;
    sp24.unk31 = 1;
    sp24.unk2C = 0x58;
    sp24.unk2E = 0x40;
    sp24.unk30 = 6;
    sp24.unk14 = 0;
    sp24.unk16 = 0;
    sp24.unk18 = 0;
    sp24.unk0 = &D_800918E8;
    sp24.unk32 = 0xFF;
    sp24.unk33 = 0;
    sp24.unk34 = 0;
    sp24.unk35 = 0xFF;
    sp24.unk24 = 0;
    sp24.unk26 = 0;
    sp24.unk39 = 0;
    sp24.unk36 = 7;
    sp24.unk37 = 0x15;
    sp24.unk38 = 1;
    sp24.unk28 = 0x51;
    sp24.unk2A = 0x51;
    if (D_800D9898[arg1] != 0) {
        func_1516972C((struct102 *)D_800D9898[arg1]);
    }
    D_800D9898[arg1] = (s32 *)func_15169968(&sp24);
}

void func_150B77A8(void) {
    struct_7484 sp24;

    if (D_800D9898[1] != 0) {
        func_1516972C((struct102 *)D_800D9898[1]);
        D_800D9898[1] = 0;
    }

    sp24.unk1C = 60.0f;
    sp24.unk20 = 170.0f;
    sp24.unk2C = 0x40;
    sp24.unk2E = 0x40;
    sp24.unk30 = 4;
    sp24.unk0 = &D_800918F4;
    sp24.unk4 = &D_80091900;
    sp24.unk14 = 0;
    sp24.unk16 = 0;
    sp24.unk18 = 0;
    sp24.unk31 = 0;
    sp24.unk24 = -0x800;
    sp24.unk26 = 9;
    sp24.unk32 = 0xFF;
    sp24.unk33 = 0;
    sp24.unk34 = 0;
    sp24.unk35 = 0xFF;
    sp24.unk36 = 0xD;
    sp24.unk37 = 0x12;
    sp24.unk38 = 2;
    sp24.unk39 = 3;
    sp24.unk28 = 0x1000;
    sp24.unk2A = 0x1000;
    if (D_800D9898[4] != 0) {
        func_1516972C((struct102 *)D_800D9898[4]);
    }
    D_800D9898[4] = (s32 *)func_15169968(&sp24);

    sp24.unk24 = 0;
    sp24.unk26 = 0;
    sp24.unk2C = 0x58;
    sp24.unk2E = 0x40;
    sp24.unk30 = 0;
    sp24.unk36 = 7;
    sp24.unk37 = 0x11;
    sp24.unk0 = &D_800918E8;
    sp24.unk38 = 1;
    if (D_800D9898[8] != 0) {
        func_1516972C((struct102 *)D_800D9898[8]);
    }
    D_800D9898[8] = (s32 *)func_15169968(&sp24);
    D_800D9890 = 3;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_E4070/func_150B791C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_E4070/func_150B7B40.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_E4070/func_150B82D0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_E4070/func_150B85C0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_E4070/func_150B879C.s")
