#include <ultra64.h>
#include "functions.h"
#include "variables.h"

typedef struct {
    u8 pad0[0x94];
    s32 unk94;
    u8 pad98[0x13C];
    s32 unk1D4;
} struct_150EEE00_arg0;

extern u8 D_800A1638[];
extern u8 D_800A163C[];
extern f32 D_800A15F0[][3];
extern s32 (*D_8008FD00)(s32, u8);
extern f32 D_800A1830;
extern f32 D_800A1834;
extern f32 D_800A1870;
extern f32 D_800A1874;
extern u8 D_800A1674;
extern u8 D_800A1680;
extern f32 sinf(f32);

typedef struct {
    u8 pad0[0x14];
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    u8 pad20[0x1B];
    u8 unk3B;
} Struct150F0E48Src;

typedef struct {
    Struct150F0E48Src *unk0;
    u8 unk4;
    u8 pad5[3];
    f32 unk8;
    f32 unkC;
    f32 unk10;
} Struct150F0E48Sub;

typedef struct {
    u8 pad0[0x2B];
    u8 unk2B;
    u8 pad2C[0xC];
    f32 unk38;
    f32 unk3C;
    f32 unk40;
    f32 unk44;
    f32 unk48;
    u8 pad4C[0x5C];
    Struct150F0E48Src *unkA8;
    u8 unkAC;
} Struct150F0E48Obj;

typedef struct {
    u8 pad_0[0x68];
    u8 field_0x68;
    u8 field_0x69;
    u8 pad_1[0x1A];
    u16 field_0x84;
    u8 pad_2[0x25E];
    s32 field_0x2E4;
} ActorStateFields;

void *func_150EEF80(struct_150EEE00_arg0 *, u8, u8, s32);
void func_15143134(void *, void *, s32);
void func_15143874(s32, f32, f32 *, f32 *);
void func_151C329C(void *, s32, s32);
void *func_151407D0(void *, s32, void *, s32, s32, s32, s32, s32, s32, s32);
struct225 *func_151602C0(Header *, Header2 *, s32, s32, s32, s32, s32, s32, s32, u8, s32);
s32 func_15160A58(s32, s32, void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
void func_150F0A24(f32 *);

void func_150EEE00(struct_150EEE00_arg0 *arg0, u8 arg1) {
    f32 sp54[3];
    Header sp4C;
    Header2 sp40;
    s32 temp_v1;

    if (D_800A163C[arg1] & arg0->unk94) {
        return;
    }

    func_150EEF80(arg0, arg1, 0xFF, 1);
    temp_v1 = arg0->unk1D4;
    if (temp_v1 != 0) {
        func_15143134(D_800A15F0[arg1], sp54, temp_v1 + (D_800A1638[arg1] << 6));
        sp4C.unk0 = 3;
        sp4C.unk1 = -1;
        sp4C.unk2 = (func_150ADA20() % 3U) + 4;
        sp4C.unk4 = 0;
        sp40.unk0 = (s32) sp54[0];
        sp40.unk4 = (s32) sp54[1];
        sp40.unk8 = (s32) sp54[2];
        func_151602C0(&sp4C, &sp40, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0, 0xFF, 1);
        func_150F0A24(sp54);
    }
}

void func_150EEF40(struct210 *arg0, u8 arg1) {
    s8 sp18[6];

    *(struct210 **)&sp18[0] = arg0;
    sp18[4] = *(u8 *)((s32)arg0 + 0x3B);
    sp18[5] = arg1;
    func_151403A8(&sp18, 0x43);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_11C2B0/func_150EEF80.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_11C2B0/func_150EF38C.s")

s32 func_150EF784(u8 *arg0, s32 arg1, s32 arg2) {
    if (arg0[4] == 0x28) {
        return 1;
    }
    return 0;
}

void func_150EF7B0(u8 *arg0) {
    s32 i;
    s32 v;
    s32 *p = (s32 *)(arg0 + 0x110);

    for (i = 0; i != 8; i += 4) {
        v = *(s32 *)((u8 *)p + i + 0x1C);
        if (v != 0) {
            func_1516972C((struct102 *)v);
        }
    }
    v = p[9];
    if (v != 0) {
        func_1516972C((struct102 *)v);
    }
    v = p[10];
    if (v != 0) {
        func_1516972C((struct102 *)v);
    }
    v = p[11];
    if (v != 0) {
        func_1516972C((struct102 *)v);
    }
    func_1513CA6C(arg0);
}

void func_150EF860(u8 *arg0) {
    s32 i;
    s32 v;
    s32 *p = (s32 *)(arg0 + 0x110);

    for (i = 0; i != 8; i += 4) {
        v = *(s32 *)((u8 *)p + i + 0x1C);
        if (v != 0) {
            func_1516979C((struct102 *)v);
        }
    }
    v = p[9];
    if (v != 0) {
        func_1516979C((struct102 *)v);
    }
    v = p[10];
    if (v != 0) {
        func_1516979C((struct102 *)v);
    }
    v = p[11];
    if (v != 0) {
        func_1516979C((struct102 *)v);
    }
    func_1513CAA0((struct210 *)arg0);
}

typedef struct {
    s32 unk0;
    union {
        s32 w4;
        struct {
            u8 b4;
            u8 b5;
            u8 b6;
            u8 b7;
        } b;
    } u4;
    u8 unk8;
    u8 unk9;
} ArgB_150EF910;

typedef struct {
    s32 unk0;
    u8 unk4;
    u8 pad5[3];
    s32 unk8;
    u8 unkC;
    u8 unkD;
} SubA_150EF910;

void func_150EF910(void *arg0, s32 arg1, u8 arg2) {
    ArgB_150EF910 *b = (ArgB_150EF910 *)arg1;
    SubA_150EF910 *a = (SubA_150EF910 *)((u8 *)arg0 + 0x110);
    s32 bu0;
    s32 bu0b;
    s32 au0;
    u8 au4;
    u8 bu4;

    if (arg2 == 0) {
        au0 = a->unk0;
        bu0 = b->unk0;
        au4 = a->unk4;
        bu4 = b->u4.b.b4;
        if ((au0 == bu0) || (au4 == bu4)) {
            func_1516972C((struct102 *)arg0);
        }
    } else if (arg2 == 0x2D) {
        if (a->unk0 == b->unk0) {
            a->unk0 = b->u4.w4;
            a->unk4 = b->unk9;
        } else if (a->unk0 == b->u4.w4) {
            a->unk0 = b->unk0;
            a->unk4 = b->unk8;
        }
        if (a->unk8 == b->unk0) {
            a->unk8 = b->u4.w4;
            a->unkC = b->unk9;
        } else {
            if (a->unk8 == b->u4.w4) {
                a->unk8 = b->unk0;
                a->unkC = b->unk8;
            }
        block2_end: ;
        }
    } else if (arg2 == 0x43) {
        if ((a->unk0 == b->unk0) || (a->unk4 == b->u4.b.b4)) {
            if (a->unkD == b->u4.b.b5) {
                func_1516972C((struct102 *)arg0);
            }
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_11C2B0/func_150EFA4C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_11C2B0/func_150EFB80.s")

typedef struct {
    s32 unk00;
    u8 unk04;
    u8 unk05;
    u8 pad06[2];
    s32 unk08;
} Payload_150EFEC8;

typedef struct {
    u8 pad_0[0x3B];
    u8 field_0x3B;
} ActorIdByteFields;

typedef struct {
    f32 unk00;
    f32 unk04;
    f32 unk08;
    f32 unk0C;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    s32 unk24;
    s32 unk28;
    s32 unk2C;
    s32 unk30;
    s32 unk34;
    s32 unk38;
    s32 unk3C;
    s32 unk40;
    s32 unk44;
    f32 unk48;
    s16 unk4C;
    s16 unk4E;
    s16 unk50;
    s16 unk52;
    u8 unk54;
    u8 unk55;
    u8 unk56;
    u8 unk57;
    u8 unk58;
    s8 unk59;
    u8 pad5A[2];
} Struct98_150EFEC8;

typedef struct {
    u8 unk00;
    u8 unk01;
    s16 unk02;
    s16 unk04;
    u8 pad06[2];
    s32 unk08;
    s32 unk0C;
    u8 unk10;
    u8 unk11;
    u8 unk12;
    u8 unk13;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    f32 unk30;
    f32 unk34;
    f32 unk38;
    f32 unk3C;
    s32 unk40;
    u8 unk44;
    u8 unk45;
    u8 unk46;
    u8 unk47;
    s32 unk48;
    u8 pad4C[0xC];
} Struct40_150EFEC8;

typedef struct {
    u8 pad_0[0x170];
    Payload_150EFEC8 field_0x170;
} CreatedObjectPayloadFields;

s32 func_150EFEC8(ActorIdByteFields *arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4, s32 arg5, u8 arg6, s32 arg7) {
    CreatedObjectPayloadFields *temp_v0;
    Struct98_150EFEC8 sp98;
    Struct40_150EFEC8 sp40;
    Payload_150EFEC8 sp34;

    sp34.unk00 = (s32)arg0;
    sp34.unk04 = arg0->field_0x3B;
    sp34.unk05 = arg1;
    sp34.unk08 = arg5;

    sp40.unk00 = D_8008FD00((s32)arg0, arg1);
    sp40.unk01 = 3;
    sp40.unk02 = 0x2203;
    sp40.unk04 = 0x12C;
    sp40.unk08 = 0;
    sp40.unk0C = 0;
    sp40.unk10 = arg2;
    sp40.unk11 = arg3;
    sp40.unk12 = arg4;
    sp40.unk13 = 0xFF;
    sp40.unk18 = 100.0f;
    sp40.unk14 = 100.0f;
    sp40.unk1C = 0.0f;
    sp40.unk20 = 0.0f;
    sp40.unk24 = 0.0f;
    sp40.unk28 = 0.0f;
    sp40.unk2C = 0.0f;
    sp40.unk30 = 0.0f;
    sp40.unk34 = 1.0f;
    sp40.unk38 = 1.0f;
    sp40.unk3C = 1.0f;
    sp40.unk40 = 0xCD2002;
    sp40.unk44 = 0xFF;
    sp40.unk45 = 0xFF;
    sp40.unk46 = 0;
    sp40.unk47 = 6;
    sp40.unk48 = 0;

    sp98.unk04 = 160.0f;
    sp98.unk00 = 160.0f;
    sp98.unk0C = 80.0f;
    sp98.unk08 = 80.0f;
    sp98.unk10 = 0.5f;
    sp98.unk14 = 0.5f;
    sp98.unk18 = 1.0f;
    sp98.unk1C = D_800A1830;
    sp98.unk20 = D_800A1834;
    sp98.unk24 = -1;
    sp98.unk34 = -1;
    sp98.unk28 = -1;
    sp98.unk38 = -1;
    sp98.unk2C = -1;
    sp98.unk3C = -1;
    sp98.unk30 = -1;
    sp98.unk40 = -1;
    sp98.unk44 = 0;
    sp98.unk48 = 1.0f;
    sp98.unk4C = 0;
    sp98.unk4E = 0;
    sp98.unk50 = 0;
    sp98.unk52 = 0;
    sp98.unk54 = 0xFF;
    sp98.unk55 = 0xFF;
    sp98.unk56 = 0xFF;
    sp98.unk57 = 0xFF;
    sp98.unk58 = 0xA;
    sp98.unk59 = -1;

    temp_v0 = func_151407D0(&sp98, 0x6C, &sp40, 0x1E, 0, 0, 0, -1, arg6, arg7);
    if (temp_v0 != 0) {
        memcpy(&temp_v0->field_0x170, &sp34, 0xC);
    }
    return (s32)temp_v0;
}

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} Vec3w_150F00EC;

typedef struct {
    u8 pad0[0x18];
    u8 unk18;
    u8 pad19[0x17];
    f32 unk30;
    f32 unk34;
    f32 unk38;
} Sub110_150F00EC;

typedef struct {
    u8 pad0[0x34];
    Vec3w_150F00EC unk34;
    u8 pad40[0xD0];
} Sub178_150F00EC;

typedef struct {
    u8 pad0[0x34];
    Vec3w_150F00EC unk34;
    f32 unk40;
    f32 unk44;
    f32 unk48;
    u8 pad4C[0xC];
    s32 unk58;
    u8 pad5C[0x11C];
    Sub178_150F00EC *unk178;
} Arg150F00EC;

s32 func_150F00EC(Arg150F00EC *arg0) {
    Sub178_150F00EC *temp_v0;
    Sub110_150F00EC *temp_v1;

    temp_v0 = arg0->unk178;
    temp_v1 = (Sub110_150F00EC *)(temp_v0 + 1);
    if (*(u8 *)((u8 *)temp_v0 + 0x128) & 1) {
        arg0->unk34 = temp_v0->unk34;
        arg0->unk40 = *(f32 *)&temp_v0->unk34.unk0 + (temp_v1->unk30 * 500.0f);
        arg0->unk44 = *(f32 *)&temp_v0->unk34.unk4 + (temp_v1->unk34 * 500.0f);
        arg0->unk48 = *(f32 *)&temp_v0->unk34.unk8 + (temp_v1->unk38 * 500.0f);
        arg0->unk58 |= 6;
    } else {
        arg0->unk58 &= ~4;
        arg0->unk58 &= ~2;
    }
    return 1;
}

struct225 *func_150F0198(u8 arg0, u8 arg1, u8 arg2, u8 arg3, s32 arg4, u8 arg5, s32 arg6) {
    struct225 *temp_v0;
    Header header;
    Header2 header2;
    s32 payload;

    payload = arg4;
    header.unk0 = 2;
    header.unk1 = -1;
    header.unk2 = 0x12C;
    header.unk4 = 0x21;
    header2.unk0 = 0;
    header2.unk4 = 0;
    header2.unk8 = 0;

    temp_v0 = func_151602C0(&header, &header2, arg0, arg1, arg2, arg3, 0xFF, 0, 4, arg5, arg6);
    if (temp_v0 != NULL) {
        memcpy(&temp_v0->unk18, &payload, 4);
    }
    return temp_v0;
}

typedef struct {
    u8 pad_0[0x12C];
    s32 field_0x12C[1];
} SlotTableFields;

typedef struct {
    u8 pad_0[0x8];
    SlotTableFields *field_0x8;
    u8 field_0xC;
} SlotTableLinkFields;

typedef struct {
    u8 pad_0[0x60];
    SlotTableLinkFields *field_0x60;
} SlotTableOwnerFields;

void func_150F02A0(SlotTableOwnerFields *arg0);

void func_150F0260(SlotTableOwnerFields *arg0) {
    func_150F02A0(arg0);
}

void func_150F0280(SlotTableOwnerFields *arg0) {
    func_150F02A0(arg0);
}

void func_150F02A0(SlotTableOwnerFields *arg0) {
    SlotTableLinkFields *temp = arg0->field_0x60;
    SlotTableFields *base = temp->field_0x8;
    base->field_0x12C[temp->field_0xC] = 0;
}

void func_150F0318(struct260 *arg0);

void func_150F02C0(struct260 *arg0) {
    func_150F0318(arg0);
    func_1514933C(arg0);
}

void func_150F02EC(struct260 *arg0) {
    func_150F0318(arg0);
    func_15149368(arg0);
}

void func_150F0318(struct260 *arg0) {
    s32 *t = *(s32 **)((u8 *)arg0 + 0x28);

    t[0x4D] = 0;
}

void func_150F0380(struct210 *arg0);

void func_150F0328(struct210 *arg0) {
    func_150F0380(arg0);
    func_151411A4(arg0);
}

void func_151411C4(struct210 *arg0);

void func_150F0354(struct210 *arg0) {
    func_150F0380(arg0);
    func_151411C4(arg0);
}

void func_150F0380(struct210 *arg0) {
    s32 *t = *(s32 **)((u8 *)arg0 + 0x178);

    t[0x4E] = 0;
}

void func_150F03E8(struct210 *arg0);
void func_151617C4(struct210 *arg0);

void func_150F0390(struct210 *arg0) {
    func_150F03E8(arg0);
    func_151617C4(arg0);
}

void func_151617E4(struct210 *arg0);

void func_150F03BC(struct210 *arg0) {
    func_150F03E8(arg0);
    func_151617E4(arg0);
}

void func_150F03E8(struct210 *arg0) {
    s32 *t = *(s32 **)((u8 *)arg0 + 0x18);

    t[0x4F] = 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_11C2B0/func_150F03F8.s")

typedef struct {
    s32 unk0;
    u8  unk4;
} SubA_F07E4;

typedef struct {
    s32 unk0;
    union {
        s32 w4;
        u8  b4;
    } u4;
    u8  unk8;
    u8  unk9;
} ArgB_F07E4;

void func_150F07E4(struct260 *arg0, s32 arg1, u8 arg2) {
    SubA_F07E4 *temp_v0 = *(SubA_F07E4 **)((u8 *)arg0 + 0x60);
    ArgB_F07E4 *b = (ArgB_F07E4 *)arg1;
    s32 b0;

    if (arg2 == 0) {
        b0 = b->unk0;
        if ((b0 == temp_v0->unk0) || (b->u4.b4 == temp_v0->unk4)) {
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

typedef struct {
    s32 unk0;
    u8  unk4;
} SubA_F088C;

typedef struct {
    s32 unk0;
    union {
        s32 w4;
        u8  b4;
    } u4;
    u8  unk8;
    u8  unk9;
} ArgB_F088C;

void func_150F088C(struct260 *arg0, s32 arg1, u8 arg2) {
    SubA_F088C *temp_v0 = (SubA_F088C *)((u8 *)arg0 + 0x170);
    ArgB_F088C *b = (ArgB_F088C *)arg1;
    s32 b0;

    if (arg2 == 0) {
        b0 = b->unk0;
        if ((b0 == temp_v0->unk0) || (b->u4.b4 == temp_v0->unk4)) {
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

void func_150F0938(s32 arg0) {
    func_15160A58(arg0, 0x25, &D_800A1674, 2, 0x12C, 4, 0, 0xFF, 0, 0xFF, 0, -1, 0, 0, 0xFF, 1);
    func_15160A58(arg0, 2, &D_800A1680, 2, 0x12C, 0xD, 0xFF, 0xFF, 0xFF, 0xFF, 0, -1, 0, 0, 0xFF, 1);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_11C2B0/func_150F0A24.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_11C2B0/func_150F0BEC.s")

s32 func_150F0E48(Struct150F0E48Obj *arg0, s32 arg1) {
    Struct150F0E48Sub *sub;
    Struct150F0E48Src *src;

    sub = (Struct150F0E48Sub *)((u8 *)arg0 + 0xA8);
    src = sub->unk0;
    if (src->unk3B != sub->unk4) {
        return 0;
    }

    arg0->unk40 = src->unk14;
    arg0->unk44 = src->unk18;
    arg0->unk48 = src->unk1C;
    sub->unk8 += D_800A1870 * D_800BE9A4;
    sub->unkC += D_800A1874 * D_800BE9A4;
    sub->unk10 += 0.25f * D_800BE9A4;
    sub->unk8 = func_15144B68(sub->unk8);
    sub->unkC = func_15144B68(sub->unkC);
    sub->unk10 = func_15144B68(sub->unk10);
    arg0->unk38 = (sinf(sub->unk8) * 243.0f) + 780.0f;
    arg0->unk3C = (sinf(sub->unkC) * 243.0f) + 780.0f;
    arg0->unk2B = (sinf(sub->unk10) * 50.0f) + 200.0f;
    return 1;
}

typedef struct {
    s32 unk0;
    u8  unk4;
} SubA150F1020;

typedef struct {
    s32 unk0;
    union {
        s32 w4;
        u8  b4;
    } u4;
    u8  unk8;
    u8  unk9;
} ArgB150F1020;

void func_150F1020(struct260 *arg0, s32 arg1, u8 arg2) {
    SubA150F1020 *temp_v0 = (SubA150F1020 *)((u8 *)arg0 + 0xA8);
    ArgB150F1020 *b = (ArgB150F1020 *)arg1;
    s32 b0;

    if (arg2 == 0x2D) {
        if (temp_v0->unk0 == b->unk0) {
            temp_v0->unk0 = b->u4.w4;
            temp_v0->unk4 = b->unk9;
        } else {
            if (temp_v0->unk0 == b->u4.w4) {
                temp_v0->unk0 = b->unk0;
                temp_v0->unk4 = b->unk8;
            }
        block_150F1020: ;
        }
    } else if (arg2 == 0 || arg2 == 0x43) {
        b0 = b->unk0;
        if ((b0 == temp_v0->unk0) || (b->u4.b4 == temp_v0->unk4)) {
            func_1516972C((struct102 *)arg0);
        }
    }
}

void func_150F10D4(struct210 *arg0) {
    s8 sp40[0x18];
    struct260 *temp_v0;

    *(struct210 **)&sp40[0] = arg0;
    sp40[4] = *(u8 *)((s32)arg0 + 0x3B);
    *(f32 *)&sp40[8] = 0.0f;
    *(f32 *)&sp40[0xC] = *(f32 *)((s32)arg0 + 0x14);
    *(f32 *)&sp40[0x10] = *(f32 *)((s32)arg0 + 0x18);
    *(f32 *)&sp40[0x14] = *(f32 *)((s32)arg0 + 0x1C);

    temp_v0 = func_15149130(0x12C, -1, 0x4C, -1, 0, 0x3A, (struct37 *)0x18, 0xFF, 1);
    if (temp_v0 != NULL) {
        memcpy((void *)((s32)temp_v0 + 0x28), &sp40, 0x18);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_11C2B0/func_150F1170.s")

void func_150F15F8(s32 arg0, s32 arg1, u8 arg2) {
    s32 *p = &arg0;
    s32 q;
    s32 b0;

    if (arg2 == 0x43) {
        b0 = *(s32 *)arg1;
        q = *p + 0x28;
        if ((b0 == *(s32 *)q) || (*(u8 *)(q + 4) == *(u8 *)(*(s32 *)&arg1 + 4))) {
            func_1516972C((struct102 *)*p);
        }
    } else {
        q = *p + 0x28;
        func_15149514(arg1, arg2, q, q + 4, *p);
    }
}

struct func150F1684_sub {
    s32 unk0;
    u8 unk4;
};

void func_150F1684(struct func150F1684_sub *arg0, struct func150F1684_sub *arg1, u8 arg2) {
    struct func150F1684_sub *temp = (struct func150F1684_sub *)((s32)arg0 + 0x18);
    s32 word;

    if (arg2 == 0x43) {
        word = arg1->unk0;
        if ((temp->unk0 == word) || (arg1->unk4 == temp->unk4)) {
            func_1516972C((struct102 *)arg0);
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_11C2B0/func_150F16DC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_11C2B0/func_150F1A00.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_11C2B0/func_150F1B48.s")

void func_150F1CB0(ActorStateFields *arg0) {
    if (arg0->field_0x84 == 0x14) {
        arg0->field_0x68 = 0x1B;
    } else {
        arg0->field_0x68 = 0xC;
    }
    arg0->field_0x69 = 0x13;
    if ((arg0->field_0x2E4 & 0x3) == 0x3) {
        arg0->field_0x69 = 0x14;
    }
    if ((arg0->field_0x2E4 & 0xC) == 0xC) {
        arg0->field_0x69 = 0x17;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_11C2B0/func_150F1D10.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_11C2B0/func_150F20F0.s")

void func_150F2230(struct127 *arg0, s32 arg1, s32 arg2) {
    struct { f32 x; f32 y; f32 z; } sp2C;
    struct { f32 x; f32 y; f32 z; } sp20;

    if ((arg0->unk1D4 != NULL) && ((arg0->unk74 & 0xF) != 0xF)) {
        sp2C.x = 0.0f;
        sp2C.y = 0.0f;
        sp2C.z = 0.0f;
        func_15143874((s16)(func_150ADA20() & 0xFF), 100.0f, &sp2C.x, &sp2C.z);
        func_15143134(&sp2C.x, &sp20.x, (s32)arg0->unk1D4 + 0x4C0);
        func_151C329C(&sp20.x, (u8)arg1, arg2);
    }
}
