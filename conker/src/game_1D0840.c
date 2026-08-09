#include <ultra64.h>
#define func_15169260 func_15169260_s32
#include "functions.h"
#undef func_15169260
#include "variables.h"


extern f32 D_800A8D50;
extern f32 D_800A8D54;
extern f32 D_800A8D5C;
extern f32 D_800A8D60;

struct Data151A561C {
    s32 unk0;
};

extern struct Data151A561C D_800A8D70;
void func_15169260(struct Data151A561C *, s32, s32, u8);

struct vec151A3504 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
};

struct frame151A3504 {
    void *unk0;
    u8 unk4;
    u8 unk5;
    u8 pad6[0x2];
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    s16 unk18;
    s16 unk1A;
    s16 unk1C;
    u8 pad1E[0x2];
    f32 unk20;
    f32 unk24;
    u8 unk28;
    u8 unk29;
    u8 unk2A;
    u8 unk2B;
    u8 unk2C;
    u8 unk2D;
    u8 unk2E;
    u8 pad2F;
    u8 unk30;
    u8 pad31[0x3];
    struct vec151A3504 unk34;
    f32 unk40;
    u8 unk44;
    u8 pad45[0x3];
    f32 unk48;
    u8 unk4C;
    u8 pad4D[0x3];
};

struct header151A3504 {
    struct vec151A3504 unk0;
    s16 unkC;
    u16 unkE;
    s32 unk10;
    u8 unk14;
    u8 unk15;
    u8 pad16[0x2];
};

struct260 *func_151A3504(struct frame151A3504 *, u8);
void func_151A4590(s32, u8);
void func_151A499C(void *, u8);
void *func_1513418C(void *, s32, u8, s32);
struct260 *func_15130374(void *, u8, s32, u8, s32);
u16 func_10010154(u16, void *, u16, s16, u16);
s32 func_15160A58(void *, s32, void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
extern s32 func_15147A80(void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
struct struct151A4E34;
s32 func_151A4E34(struct struct151A4E34 **arg0, s32 arg1);

struct frame151A3390 {
    s32 unk0;
    u8 unk4;
    u8 unk5;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    s16 unk18;
    s16 unk1A;
    s16 unk1C;
    f32 unk20;
    f32 unk24;
    u8 unk28;
    u8 unk29;
    u8 unk2A;
    u8 unk2B;
    u8 unk2C;
    u8 unk2D;
    u8 unk2E;
};

void func_151A3390(void *arg0, u8 arg1) {
    struct frame151A3390 sp68;
    f32 sp5C[3];

    sp68.unk0 = (s32)arg0;
    sp68.unk4 = *((u8 *)arg0 + 0x3B);
    sp68.unk5 = 1;
    sp68.unk8 = 0.0f;
    sp68.unkC = 0.0f;
    sp68.unk10 = 0.0f;
    sp68.unk2B = 1;
    sp68.unk2C = 0xFF;
    sp68.unk2D = 8;
    sp68.unk2E = 0x1F;
    sp68.unk18 = 0xAA;
    sp68.unk1A = 0x28;
    sp68.unk1C = 7;
    sp68.unk28 = 2;
    sp68.unk29 = 4;
    sp68.unk2A = 1;
    sp68.unk14 = D_800A8D50;
    sp68.unk20 = 30.0f;
    sp68.unk24 = D_800A8D54;
    func_151A3504(&sp68, arg1);
    func_151A4590(arg0, arg1);
    func_151A499C(arg0, arg1);
    func_10010154(0x1AA, arg0, 0x55F0, 0x3E8, 0xFA0);
    sp5C[0] = 0.0f;
    sp5C[1] = 0.0f;
    sp5C[2] = 0.0f;
    func_15160A58(arg0, 1, sp5C, 2, 0x12C, 0x50, 0xFF, 0xFF, 0x75, 0xFF, 0, -1, 0, 0, arg1, 1);
}

struct260 *func_151A3504(struct frame151A3504 *arg0, u8 arg1) {
    s32 pad_dummy;
    struct header151A3504 sp8C;
    struct frame151A3504 sp3C;
    struct260 *temp_v0;

    if (arg0->unk0 == NULL) {
        return NULL;
    }

    memcpy(&sp3C, arg0, 0x30);
    sp3C.unk44 = 0;
    sp8C.unk15 = 0x32;
    sp8C.unkE = 2;
    sp8C.unkC = 0x3E8;
    sp3C.unk30 = 6;
    sp3C.unk4C = 0;
    sp3C.unk40 = 0.0f;
    sp3C.unk48 = 0.0f;

    if (func_151A4E34((struct struct151A4E34 **)&sp3C, (s32)&sp8C) != 0) {
        sp3C.unk34 = sp8C.unk0;
        sp8C.unkE |= 4;
    }

    sp8C.unk10 = 8;
    temp_v0 = (struct260 *)func_15147A80(&sp8C, 0x50, 0x18, 6, 6, 6, 0, 0, 0, arg1, 0);
    if (temp_v0 != NULL) {
        memcpy((void *)*(s32 *)((u8 *)temp_v0 + 0x98), &sp3C, 0x50);
    }
    return temp_v0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1D0840/func_151A361C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1D0840/func_151A37C0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1D0840/func_151A3BE4.s")

struct frame151A4590 {
    s32 unk0;
    s32 unk4;
    u8 unk8;
    u8 pad9[3];
    void *unkC;
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
};

void func_151A4590(s32 arg0, u8 arg1) {
    struct frame151A4590 sp18;

    if (arg0 != 0) {
        sp18.unk0 = 0;
        sp18.unk4 = 0;
        sp18.unk8 = *((u8 *)arg0 + 0x3B);
        sp18.unk10 = 1;
        sp18.unk14 = 0.0f;
        sp18.unk18 = 0.0f;
        sp18.unk1C = 0.0f;
        sp18.unk20 = D_800A8D5C;
        sp18.unk24 = 3.0f;
        sp18.unk28 = 0x64;
        sp18.unk2A = 0xA;
        sp18.unk2B = 1;
        sp18.unk2C = -1;
        sp18.unk2D = 0;
        sp18.unkC = (void *)arg0;
        func_1513418C(&sp18, 0, arg1, 0);
    }
}

void func_151A4638(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, void *arg6) {
    struct260 *ret;
    struct {
        s16 sp28[6];
        u8 pad34[4];
        struct {
            s32 unk00;
            s32 unk04;
            s16 unk08;
            s16 unk0A;
            s32 unk0C;
            s32 unk10;
            u8 unk14;
            u8 unk15;
            u8 unk16;
            u8 unk17;
            u8 unk18;
            u8 unk19;
            u8 unk1A;
            u8 unk1B;
            u8 unk1C;
            u8 unk1D;
            s16 unk1E;
            s16 unk20;
            s16 unk22;
            f32 unk24;
            f32 unk28;
            f32 unk2C;
            f32 unk30;
            f32 unk34;
            f32 unk38;
            u8 pad3C[0xC];
            f32 unk48;
            f32 unk4C;
            f32 unk50;
            f32 unk54;
            s32 unk58;
            u8 pad5C[4];
            u8 unk60;
            u8 unk61;
            u8 unk62;
            s8 unk63;
        } sp38;
        u8 pad9C[8];
    } stack;

    stack.sp38.unk1D = 0x27;
    stack.sp38.unk08 = 0x1401;
    stack.sp38.unk00 = 0x200005;
    stack.sp38.unk04 = 0;
    stack.sp38.unk0A = (func_150ADA20() % 5U) + 0xF;
    stack.sp38.unk0C = 0;
    stack.sp38.unk10 = 0;
    stack.sp38.unk14 = 0x8A;
    stack.sp38.unk15 = 0;
    stack.sp38.unk16 = 0;
    stack.sp38.unk17 = 0xFF;
    stack.sp38.unk18 = 0;
    stack.sp38.unk19 = 0;
    stack.sp38.unk1A = 0;
    stack.sp38.unk1E = 1;
    stack.sp38.unk20 = 0xFF;
    stack.sp38.unk22 = 1;
    stack.sp38.unk24 = 1.0f;

    stack.sp38.unk28 = stack.sp38.unk2C = (func_150ADA68() * 50.0f) + 500.0f;
    stack.sp38.unk30 = arg0;
    stack.sp38.unk34 = arg1;
    stack.sp38.unk38 = arg2;
    stack.sp38.unk48 = -arg3 * (D_800A8D60 * D_800BE9A8);
    stack.sp38.unk4C = -arg4 * (D_800A8D60 * D_800BE9A8);
    stack.sp38.unk50 = -arg5 * (D_800A8D60 * D_800BE9A8);
    stack.sp38.unk58 = 0xD;
    stack.sp38.unk60 = 1;
    stack.sp38.unk61 = 1;
    stack.sp38.unk54 = 0.0f;

    if (func_150ADA20() & 1) {
        stack.sp38.unk58 |= 0x40;
    }

    if (func_150ADA20() & 1) {
        stack.sp38.unk58 |= 0x80;
    }

    stack.sp38.unk1B = 0xFF;
    stack.sp38.unk1C = 0xFF;
    stack.sp38.unk62 = 0;
    stack.sp38.unk63 = -1;
    stack.sp28[0] = 0x10;
    stack.sp28[1] = 0xF;
    stack.sp28[2] = 0xD;
    stack.sp28[3] = 0x13;
    stack.sp28[4] = 0x11;
    stack.sp28[5] = -0x18;

    ret = func_15130374(&stack.sp38, 0, 0xC, *((u8 *)arg6 + 0xC), 1);
    if (ret != 0) {
        memcpy((u8 *)ret + 0xA8, stack.sp28, 0xC);
    }
}

struct Sub151A483C {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
};

struct Obj151A483C {
    u8 pad0[0x18];
    s16 unk18;
    s16 unk1A;
    u8 pad1C[0x2B - 0x1C];
    u8 unk2B;
    u8 unk2C;
    u8 pad2D[0x38 - 0x2D];
    f32 unk38;
    f32 unk3C;
    u8 pad40[0x70 - 0x40];
    u8 unk70;
    u8 unk71;
    u8 unk72;
    u8 pad73[0xA8 - 0x73];
    struct Sub151A483C unkA8;
};

s32 func_151A483C(struct Obj151A483C *arg0, u8 arg1) {
    s16 temp_v1;
    struct Sub151A483C *temp_v0;
    f32 temp_f0;

    temp_v0 = &arg0->unkA8;
    temp_v1 = arg0->unk1A;
    if (temp_v1 < temp_v0->unk4) {
        arg0->unk2B = (u32)temp_v1 * (u32)temp_v0->unk6;
    }
    if (temp_v1 < temp_v0->unk8) {
        temp_f0 = (f32)(temp_v0->unkA * D_800BE9E4);
        *(volatile f32 *)&arg0->unk38 = arg0->unk38 + temp_f0;
        *(volatile f32 *)&arg0->unk3C = arg0->unk3C + temp_f0;
        temp_v1 = *(volatile s16 *)&arg0->unk1A;
    }
    if (temp_v1 < temp_v0->unk0) {
        arg0->unk72 = 1;
        arg0->unk70 = 2;
        arg0->unk71 = 2;
        arg0->unk2C = (u32)temp_v1 * (u32)temp_v0->unk2;
        arg0->unk18 = 0x5203;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1D0840/func_151A4900.s")

extern f32 D_800A8D64;

struct frame151A499C {
    void *unk0;
    u8 unk4;
    f32 unk8;
    f32 unkC;
    u8 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
};

void func_151A499C(void *arg0, u8 arg1) {
    struct260 *ret;
    struct frame151A499C sp2C;

    sp2C.unk0 = arg0;
    sp2C.unk4 = *((u8 *)arg0 + 0x3B);
    sp2C.unkC = 0.0f;
    sp2C.unk10 = 1;
    sp2C.unk14 = 0.0f;
    sp2C.unk18 = 0.0f;
    sp2C.unk1C = 0.0f;
    sp2C.unk8 = D_800A8D64;
    ret = func_151491F4(0x12C, -1, 5, 0, 1, 0x20, arg1, 0);
    if (ret != 0) {
        memcpy((u8 *)ret + 0x28, &sp2C, 0x20);
    }
}

struct Obj151A4A38 {
    s32 unk0;
    u8 pad4[0x37];
    u8 unk3B;
    u8 pad3C[0x38];
    u8 unk74;
    u8 pad75[1];
    u16 unk76;
    u8 pad78[0x15C];
    s32 unk1D4;
};

struct Sub151A4A38 {
    struct Obj151A4A38 *unk0;
    u8 unk4;
    u8 pad5[3];
    f32 unk8;
    f32 unkC;
    u8 unk10;
    u8 pad11[3];
    f32 unk14;
    f32 unk18;
    f32 unk1C;
};

struct Ent151A4A38 {
    u8 pad0[1];
    u8 unk1;
    u8 pad2[0xA];
    u8 unkC;
    u8 unkD;
    s16 unkE;
    u8 pad10[0x18];
    struct Sub151A4A38 unk28;
};

struct Block151A4A38 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
};

struct Arg151A4A38 {
    s16 unk0;
    s16 unk2;
    u8 unk4;
    u8 pad5;
    u16 unk6;
    s32 unk8;
    s32 unkC;
    s16 unk10;
    s16 unk12;
    s32 unk14;
    s32 unk18;
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
    s16 unk26;
    s16 unk28;
    s16 unk2A;
    f32 unk2C;
    f32 unk30;
    f32 unk34;
    struct Block151A4A38 unk38;
    s16 unk44;
    s16 unk46;
    s16 unk48;
    s16 unk4A;
    f32 unk4C;
    f32 unk50;
    f32 unk54;
    f32 unk58;
    s32 unk5C;
    s8 unk60;
    s8 unk61;
    u8 unk62;
    u8 unk63;
    u8 unk64;
    u8 pad65[3];
    f32 unk68;
};

void func_15143134(void *, s32, s32);
void func_15153634(void *, s32, s32, s32);

void func_151A4A38(struct Ent151A4A38 *arg0) {
    struct Sub151A4A38 *sub;
    struct Block151A4A38 sp98;
    struct Arg151A4A38 sp2C;
    s16 sp2A;

    sub = &arg0->unk28;
    if ((arg0->unk28.unk0->unk0 == 0) || (sub->unk0->unk0 == 8) || (sub->unk0->unk3B != sub->unk4)) {
        arg0->unkE = -1;
        arg0->unkD |= 1;
        return;
    }

    if (sub->unk0->unk1D4 == 0) {
        return;
    }
    if ((sub->unk0->unk74 & 0xF) == 0xF) {
        return;
    }

    sub->unkC += sub->unk8 * D_800BE9A4;
    if (sub->unkC > 1.0f) {
        sp2A = (sub->unk0->unk76 >> 8) - 0x40;
        func_15143134(&sub->unk14, (s32)&sp98, sub->unk0->unk1D4 + (sub->unk10 << 6));

        sp2C.unk0 = (s16)sub->unkC;
        sp2C.unk2 = 0;
        sub->unkC -= (f32)sp2C.unk0;
        sp2C.unk4 = 0x28;
        sp2C.unk6 = 0xC01;
        sp2C.unk8 = 0x200005;
        sp2C.unkC = 0;
        sp2C.unk10 = 0x17;
        sp2C.unk12 = 0xD;
        sp2C.unk14 = 0;
        sp2C.unk18 = 0;
        sp2C.unk1C = 0;
        sp2C.unk1D = 0;
        sp2C.unk1E = 0;
        sp2C.unk1F = 0xFF;
        sp2C.unk20 = 0;
        sp2C.unk21 = 0;
        sp2C.unk22 = 0;
        sp2C.unk30 = 300.0f;
        sp2C.unk34 = 400.0f;
        sp2C.unk38 = sp98;
        sp2C.unk26 = 1;
        sp2C.unk28 = 0;
        sp2C.unk2A = 1;
        sp2C.unk2C = 1.0f;
        sp2C.unk64 = 0;
        sp2C.unk44 = sp2A - 0x19;
        sp2C.unk46 = -0x2C;
        sp2C.unk48 = 0x32;
        sp2C.unk4A = 0x32;
        sp2C.unk4C = 0.0f;
        sp2C.unk50 = 15.0f;
        sp2C.unk54 = -0.5f;
        sp2C.unk58 = -0.5f;
        sp2C.unk5C = 7;
        sp2C.unk62 = 1;
        sp2C.unk63 = 0;

        if (func_150ADA20() & 1) {
            sp2C.unk5C |= 0x40;
        }
        if (func_150ADA20() & 1) {
            sp2C.unk5C |= 0x80;
        }

        sp2C.unk23 = 0xFF;
        sp2C.unk24 = 0;
        sp2C.unk25 = 0xFF;
        sp2C.unk60 = -1;
        sp2C.unk61 = -1;
        func_15153634(&sp2C, 0xFF, arg0->unkC, arg0->unk1);
    }
}

typedef struct {
    s32 unk0;
    u8 unk4;
} SubA_151A4CE0;

typedef struct {
    s32 unk0;
    union {
        u8 b4;
        s32 w4;
    } u4;
    u8 unk8;
    u8 unk9;
} ArgB_151A4CE0;

void func_151A4E9C(void *arg0);

void func_151A4CE0(struct260 *arg0, s32 arg1, u8 arg2) {
    SubA_151A4CE0 *temp_v0 = *(SubA_151A4CE0 **)((u8 *)arg0 + 0x98);
    ArgB_151A4CE0 *b = (ArgB_151A4CE0 *)arg1;

    if (arg2 == 0) {
        if ((b->unk0 == temp_v0->unk0) || (b->u4.b4 == temp_v0->unk4)) {
            func_151A4E9C(arg0);
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

void func_1516972C(struct102 *arg0);

typedef struct {
    s32 unk0;
    u8 unk4;
} SubA_151A4D88;

typedef struct {
    s32 unk0;
    union {
        u8 b4;
        s32 w4;
    } u4;
    u8 unk8;
    u8 unk9;
} ArgB_151A4D88;

void func_151A4D88(struct260 *arg0, s32 arg1, u8 arg2) {
    SubA_151A4D88 *temp_v0 = (SubA_151A4D88 *)((u8 *)arg0 + 0x28);
    ArgB_151A4D88 *b = (ArgB_151A4D88 *)arg1;

    if (arg2 == 0) {
        if ((b->unk0 == temp_v0->unk0) || (b->u4.b4 == temp_v0->unk4)) {
            func_1516972C((struct102 *)arg0);
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

void func_15143134(void *, s32, s32);
struct struct151A4E34
{
  u8 pad0[0x74];
  u8 unk74;
  u8 pad75[0x1D4 - 0x75];
  struct elem151A4E34 *unk1D4;
};
s32 func_151A4E34(struct struct151A4E34 **arg0, s32 arg1)
{
  struct struct151A4E34 *v0 = arg0[0];
  u32 offset;
  s32 v1 = (s32) v0->unk1D4;
  if (v1 == 0)
  {
    return 0;
  }
  if ((v0->unk74 & 0xF) == 0xF)
  {
    return 0;
  }
  offset = ((*(((u8 *) arg0) + 5)) << 4) << 2;
  func_15143134(((u8 *) arg0) + 8, arg1, v1 + offset);
  return 1;
}


void func_151A4E9C(void *arg0)
{
  u8 *p;
  u8 v;
  int mask;
  *((u8 *) (((u8 *) arg0) + 0x30)) = 0;
  *((u16 *) (((u8 *) arg0) + 0x1E)) &= 0xFFFD;
 mask = 0xFFu; do { p = *((u8 **) (((u8 *) arg0) + 0x98)); v = (p[0x30] & mask) | 1; *(p + 0x30) = v; *((volatile u8 *) (p + 0x30)) = v | 4; } while (0);
}


#pragma GLOBAL_ASM("asm/nonmatchings/game_1D0840/func_151A4ECC.s")

void func_1516972C(struct102 *arg0);

struct struct151A4F7C {
    s32 unk0;
    u8 unk4;
};

void func_151A4F7C(struct102 *arg0, struct102 *arg1, u8 arg2)
{
    struct struct151A4F7C *p = (struct struct151A4F7C *)((u8 *)arg0 + 0x28);
    struct struct151A4F7C *q = (struct struct151A4F7C *)arg1;
    if (!arg2) {
        if (q->unk0 == p->unk0 || q->unk4 == p->unk4) {
            func_1516972C(arg0);
        }
    }
}

struct Obj151A4FD0 {
    char pad0[0x10];
    s32 unk10;
    u8  unk14;
    u8  unk15;
    u8  unk16;
    u8  unk17;
    u8  unk18;
    u8  unk19;
    u8  unk1A;
};

extern struct Obj151A4FD0 *func_15167A68(s32, s32, s32, s32, s32, s32);

struct Obj151A4FD0 *func_151A4FD0(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4, s32 a5, u8 a6, s32 a7) {
    struct Obj151A4FD0 *ret = func_15167A68(0x5A, 0, a7 + 0x20, 0, 0xFF, 1);
    if (ret == 0) {
        return NULL;
    }
    ret->unk14 = a0;
    ret->unk10 = a1;
    ret->unk15 = a2;
    ret->unk16 = a3;
    ret->unk17 = a4;
    ret->unk19 = a6;
    ret->unk18 = 0;
    ret->unk1A = a5;
    return ret;
}

void func_151A5070(struct Obj151A4FD0 *arg0) {
    struct Obj151A4FD0 *temp_a1;
    s32 temp_v0;
    s32 temp_t8;
    s32 var_v0;

    temp_a1 = arg0;
    temp_v0 = temp_a1->unk10;
    if (temp_v0 != 0) {
        temp_v0 -= D_800BE9E4;
        if (temp_v0 <= 0) {
            func_1516972C((struct102 *)temp_a1);
            return;
        }
        temp_a1->unk10 = temp_v0;
    }

    if (temp_a1->unk19 == 0) {
        func_10011FA0((s32 *)2);
    }

    var_v0 = temp_a1->unk15;
    temp_t8 = D_800BE9E4 * 2;
    if (temp_a1->unk18 == 0) {
        var_v0 -= temp_t8;
        if (var_v0 < 0x90) {
            var_v0 = 0x90;
            temp_a1->unk18 = 1;
        }
    } else {
        var_v0 += temp_t8;
        if (var_v0 >= 0x100) {
            var_v0 = 0xFF;
            temp_a1->unk18 = 0;
        }
    }
    temp_a1->unk15 = var_v0;
}

extern void (*D_8008F900[])(void *, void *, s16);

void func_151A5130(void *arg0, void *arg1, s16 arg2)
{
  D_8008F900[*((u8 *) (((u8 *) arg1) + 0x14))](arg0, arg1, arg2);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1D0840/func_151A5170.s")

extern void (*D_8008F904[])(void *, void *, u8);

void func_151A55D4(void *arg0, void *arg1, u8 arg2)
{
  void (*f)(void *, void *, u8);
  f = D_8008F904[*((u8 *) (((u8 *) arg0) + 0x19))];
  if (f != NULL) {
    f(arg0, arg1, arg2);
  }
}

void func_151A561C(s32 arg0, u8 arg1) {
    struct Data151A561C sp1C;

    sp1C = D_800A8D70;
    func_15169260(&sp1C, 1, arg0, arg1);
}
