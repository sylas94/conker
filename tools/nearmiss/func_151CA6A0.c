#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern f32 D_800AAED4;
extern f32 D_800AAED8;
extern f32 D_800AAEA8;
extern f32 D_800AAEAC;
extern f32 D_800AAEB0;
extern f32 D_800AAEB4;
extern f32 D_800AAEB8;
extern f32 func_151CC1D4(void *);
extern f32 sinf(f32);
extern void func_1514373C(f32, f32, f32 *, f32 *);
extern void func_15145974(struct17 *, f32 *, f32 *);
extern void func_1000FD38(void *, void *, s32);
extern s32 func_151C87E0(s32, s32);
extern void func_151C899C(s32, s32);
extern void *func_1515548C(void *, u8, s32, s32, s32, u8, s32);
extern void func_15160274(s32, s32, s32);
extern void func_1515572C(s32, s32);
extern void func_151A561C(s32, s32);
extern void (*D_8008FC10[])(struct102 *, void **, u8);
typedef struct {
    u8 pad0[0x14];
    f32 unk14;
    u8 pad18[0x4];
    f32 unk1C;
    u8 pad20[0x160];
    f32 unk180;
} struct_func_151C9AC0_arg0;
typedef struct {
    u8 unk0[0x24];
} struct_func_151C9AC0_sp20;
typedef struct {
    u8 pad_0x00[0x28];
    s32 field_0x28;
    struct102 *field_0x2C;
    u8 pad_0x30[0x4];
    s32 field_0x34;
    s32 field_0x38;
    s32 field_0x3C;
    s32 field_0x40;
    s32 field_0x44;
    s32 field_0x48;
    s32 field_0x4C;
    s32 field_0x50;
    u8 pad_0x54[0x32];
    u8 field_0x86;
} Game1F4650LinkBlock;
typedef struct {
    u8 pad_0x00[0x13C];
    s32 field_0x13C;
    u8 pad_0x140[0x4];
    s32 field_0x144;
} Game1F4650LinkedObject;
typedef struct {
    u8 pad_0x00[0x170];
    s32 field_0x170;
} Game1F4650LinkOwner;
typedef struct {
    s32 field_0x0;
    s32 field_0x4;
} Game1F4650LinkMatchEvent;
typedef struct {
    s32 field_0x0;
    u8 field_0x4;
} Game1F4650LinkStateEvent;
typedef struct {
    s32 field_0x0;
    u8 pad_0x4[0x8];
    u8 field_0xC;
    u8 field_0xD;
    u8 field_0xE;
    u8 pad_0xF[0x1];
    f32 field_0x10;
    f32 field_0x14;
    f32 field_0x18;
    u8 pad_0x1C[0x4];
    f32 field_0x20;
} Game1F4650EffectState;
typedef struct {
    u8 pad_0x00[0x14];
    f32 field_0x14;
    u8 pad_0x18[0x58];
    Game1F4650EffectState field_0x70;
} Game1F4650EffectObject;
typedef struct {
    u8 field_0x0;
    u8 pad_0x1[0x3];
    s32 field_0x4;
} Game1F4650EffectTriggerEvent;
typedef struct {
    u8 pad_0x0[0x9];
    u8 field_0x9;
} Game1F4650ByteFlagTarget;
typedef struct {
    u8 pad_0x0[0x6F];
    u8 field_0x6F;
} Game1F4650StatusFlagBlock;
typedef struct {
    u8 pad_0x00[0x14];
    Game1F4650ByteFlagTarget *field_0x14;
    Game1F4650StatusFlagBlock *field_0x18;
} Game1F4650StatusFlagOwner;
typedef struct {
    u8 pad_0x00[0x58];
    s32 field_0x58;
    u8 pad_0x5C[0x12C];
    Game1F4650StatusFlagBlock *field_0x188;
} Game1F4650StatusFlagObject;
extern void func_1504715C(struct_func_151C9AC0_sp20 *, struct_func_151C9AC0_arg0 *);
extern s32 func_151ABE40(f32 *, struct_func_151C9AC0_sp20 *, s32, u8, s32);

#pragma GLOBAL_ASM("asm/nonmatchings/game_1F4650/func_151C71A0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1F4650/func_151C756C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1F4650/func_151C7E98.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1F4650/func_151C82D0.s")

void func_151C8674(s32 arg0, s32 arg1) {
    struct {
        s32 unk0;
        s32 unk4;
    } sp18;
    if (arg0 != 0) {
        sp18.unk0 = arg0;
        sp18.unk4 = arg1;
        func_151403A8((s32)&sp18, 0x20);
    }
}

void func_151C86AC(s32 arg0, s32 arg1, u8 arg2) {
    s32 *arg0p;
    Game1F4650LinkBlock *temp_v0;
    s32 temp_v1;

    arg0p = &arg0;
    switch (arg2) {
    case 0x20:
        temp_v0 = (Game1F4650LinkBlock *)(*arg0p + 0x110);
        if ((temp_v0->field_0x86 & 0x10) && (((Game1F4650LinkMatchEvent *)arg1)->field_0x4 == temp_v0->field_0x28)) {
            if (func_151C87E0(((Game1F4650LinkMatchEvent *)arg1)->field_0x0, *arg0p) != 0) {
                func_151C899C(((Game1F4650LinkMatchEvent *)arg1)->field_0x0, *arg0p);
            }
        }
        break;
    case 0x3A:
        temp_v0 = (Game1F4650LinkBlock *)*arg0p;
        temp_v0 = (Game1F4650LinkBlock *)((s32)temp_v0 + 0x110);
        if (((Game1F4650LinkStateEvent *)arg1)->field_0x0 == temp_v0->field_0x28) {
            temp_v1 = ((Game1F4650LinkStateEvent *)arg1)->field_0x4;
            switch (temp_v1) {
            case 0:
                temp_v0->field_0x86 |= 2;
                break;
            case 1:
                temp_v0->field_0x86 &= ~2;
                break;
            case 2:
                func_151C899C(0, *arg0p);
                break;
            }
        }
        break;
    }
}

s32 func_151C87AC(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s16 *arg6) {
    void *temp = *(void **)((s32)arg0 + 0x18);
    if (!(*(u8 *)((s32)temp + 0x86) & 0x2)) {
        *arg6 = 0;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1F4650/func_151C87E0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1F4650/func_151C899C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1F4650/func_151C8FCC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1F4650/func_151C9198.s")

void func_151C94D4(Game1F4650LinkedObject *arg0) {
    register Game1F4650LinkBlock *temp_s0;
    s32 temp_a0;

    temp_s0 = (Game1F4650LinkBlock *)((s32)arg0 + 0x110);
    if (arg0->field_0x13C != 0) {
        func_1516972C(temp_s0->field_0x2C);
        func_1000FD38(func_151C87AC, (void *)temp_s0, 0);
    }

    temp_s0 = (Game1F4650LinkBlock *)*(s32 *)&arg0;
    temp_a0 = ((Game1F4650LinkedObject *)temp_s0)->field_0x144;
    temp_s0 = (Game1F4650LinkBlock *)((s32)temp_s0 + 0x110);
    if (temp_a0 != 0) {
        func_1516972C((struct102 *)temp_a0);
    }

    temp_a0 = temp_s0->field_0x38;
    if (temp_a0 != 0) {
        func_1516972C((struct102 *)temp_a0);
    }

    temp_a0 = temp_s0->field_0x3C;
    if (temp_a0 != 0) {
        func_1516972C((struct102 *)temp_a0);
    }

    temp_a0 = temp_s0->field_0x40;
    if (temp_a0 != 0) {
        func_1516972C((struct102 *)temp_a0);
    }

    temp_a0 = temp_s0->field_0x44;
    if (temp_a0 != 0) {
        func_1516972C((struct102 *)temp_a0);
    }

    temp_a0 = temp_s0->field_0x48;
    if (temp_a0 != 0) {
        func_1516972C((struct102 *)temp_a0);
    }

    temp_a0 = temp_s0->field_0x4C;
    if (temp_a0 != 0) {
        func_1516972C((struct102 *)temp_a0);
    }

    temp_a0 = temp_s0->field_0x50;
    if (temp_a0 != 0) {
        func_1516972C((struct102 *)temp_a0);
    }

    func_1513CA6C(arg0);
}

void func_151C95D8(Game1F4650LinkedObject *arg0) {
    register Game1F4650LinkBlock *temp_s0;
    s32 temp_a0;

    temp_s0 = (Game1F4650LinkBlock *)((s32)arg0 + 0x110);
    if (arg0->field_0x13C != 0) {
        func_1516972C(temp_s0->field_0x2C);
        func_1000FD38(func_151C87AC, (void *)temp_s0, 0);
    }

    temp_s0 = (Game1F4650LinkBlock *)*(s32 *)&arg0;
    temp_a0 = ((Game1F4650LinkedObject *)temp_s0)->field_0x144;
    temp_s0 = (Game1F4650LinkBlock *)((s32)temp_s0 + 0x110);
    if (temp_a0 != 0) {
        func_1516972C((struct102 *)temp_a0);
    }

    temp_a0 = temp_s0->field_0x38;
    if (temp_a0 != 0) {
        func_1516972C((struct102 *)temp_a0);
    }

    temp_a0 = temp_s0->field_0x3C;
    if (temp_a0 != 0) {
        func_1516972C((struct102 *)temp_a0);
    }

    temp_a0 = temp_s0->field_0x40;
    if (temp_a0 != 0) {
        func_1516972C((struct102 *)temp_a0);
    }

    temp_a0 = temp_s0->field_0x44;
    if (temp_a0 != 0) {
        func_1516972C((struct102 *)temp_a0);
    }

    temp_a0 = temp_s0->field_0x48;
    if (temp_a0 != 0) {
        func_1516972C((struct102 *)temp_a0);
    }

    temp_a0 = temp_s0->field_0x4C;
    if (temp_a0 != 0) {
        func_1516972C((struct102 *)temp_a0);
    }

    temp_a0 = temp_s0->field_0x50;
    if (temp_a0 != 0) {
        func_1516972C((struct102 *)temp_a0);
    }

    func_1513CAA0(arg0);
}

s32 func_151C96DC(Game1F4650LinkOwner *arg0, s32 arg1) {
    Game1F4650LinkBlock *temp;

    temp = (Game1F4650LinkBlock *)(arg0->field_0x170 + 0x110);
    if (temp->field_0x86 & 0x2) {
        return 1;
    }
    return 0;
}

void func_151C970C(s32 arg0, s32 arg1) {
    struct {
        s32 unk0;
        u8 unk4;
    } sp18;
    sp18.unk0 = arg1;
    sp18.unk4 = arg0;
    func_151403A8((s32)&sp18, 0x3A);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1F4650/func_151C9740.s")

void func_151C9AC0(struct_func_151C9AC0_arg0 *arg0, u8 arg1, s32 arg2) {
    f32 sp44[3];
    struct_func_151C9AC0_sp20 sp20;

    sp44[0] = arg0->unk14;
    sp44[1] = arg0->unk180 + 2.0f;
    sp44[2] = arg0->unk1C;
    func_1504715C(&sp20, arg0);
    func_151ABE40(sp44, &sp20, 2, arg1, arg2);
}

s32 func_151C9B30(Game1F4650StatusFlagOwner *arg0) {
    Game1F4650StatusFlagBlock *temp = arg0->field_0x18;
    if (temp->field_0x6F == 0) {
        arg0->field_0x14->field_0x9 = 0;
    } else {
        arg0->field_0x14->field_0x9 = 1;
    }
    return 1;
}

s32 func_151C9B64(Game1F4650StatusFlagObject *arg0, u8 *arg1) {
    Game1F4650StatusFlagBlock *temp = arg0->field_0x188;
    if (temp->field_0x6F == 0) {
        *arg1 = 1;
    } else {
        arg0->field_0x58 &= ~0x2;
        *arg1 = 0;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1F4650/func_151C9BA0.s")

void func_150BDE90(void *, u8, s32);
void func_151C9F38(void *, s32, u8, s8, u8);
void func_151CC524(void *, s32, s32, s32, u8, u8);
void func_151CC840(void *, s32, s32, s32, u8, u8);
void func_151CCF08(void *, u8, s8, u8);
void func_151CB5FC(void *, s32, u8, s8, u8);

void func_151C9DE8(void *arg0, u8 arg1, s8 arg2, u8 arg3, s32 arg4) {
    func_151C9F38(arg0, 4, arg1, arg2, arg3);
    func_151CC524(arg0, 0, 0x32, 0xFF, arg1, arg3);
    func_151CC840(arg0, 0, 0x32, 0xFF, arg1, arg3);
    func_151CCF08(arg0, arg1, arg2, arg3);
    func_150BDE90(arg0, arg3, arg4);
    func_151CB5FC(arg0, 2, arg1, arg2, arg3);
    if (D_800BE9F0 == 0x27) {
        D_8008CD00 = 1;
    }
}

void func_151C9ED4(s32 arg0) {
    s32 sp24;

    sp24 = arg0;
    func_15160274((s32)&sp24, 0x21, arg0);
    func_1515572C((s32)&sp24, 0x21);
    func_151A561C((s32)&sp24, 0x21);
    func_151494E0((s32)&sp24, 0x21);
    D_8008CD00 = 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1F4650/func_151C9F38.s")

extern f32 D_800AAE8C;
extern f32 D_800AAE90;
extern f32 D_800AAE94;
extern f32 D_800AAE98;

void func_151CA6A0(void *arg0, u8 arg1) {
    typedef struct {
        f32 unk0;
        f32 unk4;
        f32 unk8;
        f32 unkC;
        u8  unk10;
        u8  pad11;
        s16 unk12;
        u16 unk14;
        s16 unk16;
        s16 unk18;
        u8  unk1A;
        u8  unk1B;
        u8  unk1C;
        u8  unk1D;
        u8  unk1E;
        u8  unk1F;
        u8  unk20;
        u8  unk21;
        u8  unk22;
        u8  unk23;
        s32 unk24;
        s32 unk28;
        s32 unk2C;
        s32 unk30;
        s32 unk34;
        s32 unk38;
        s32 unk3C;
        u8  unk40;
        u8  unk41;
        u8  pad42[2];
        u8  unk44;
        u8  pad45[3];
        f32 unk48;
        f32 unk4C;
        f32 unk50;
        f32 unk54;
    } struct_151CA6A0_spA0;
    typedef struct {
        void *unk0;
        f32 unk4;
        f32 unk8;
        u8  unkC;
        u8  unkD;
        u8  padE[0xA];
        f32 unk18;
        f32 unk1C;
        f32 unk20;
        f32 unk24;
        f32 unk28;
        u8  pad2C[0x30];
    } struct_151CA6A0_sp44;
    struct_151CA6A0_spA0 spA0;
    struct_151CA6A0_sp44 sp44;
    void *temp_v0;
    s32 temp_type;
    s32 i;

    sp44.unkD = 0;
    sp44.unkC = 0;
    spA0.unkC = 25.0f;
    spA0.unk8 = 25.0f;
    sp44.unk0 = arg0;
    sp44.unk4 = 0.0f;
    sp44.unk8 = 130.0f;

    if (D_80082FA0 > 0) {
        spA0.unk10 = 0x73;
    } else {
        spA0.unk10 = 0x5D;
    }

    spA0.unk12 = 0x12C;
    spA0.unk14 = (1 << (*(u8 *)((s32)arg0 + 0x23D) + 0xB)) | 0x50;
    spA0.unk16 = 1;
    spA0.unk18 = 0xFF;
    spA0.unk1A = 7;
    spA0.unk1B = 0;
    spA0.unk1C = 0xFF;
    spA0.unk1D = 0;
    spA0.unk1E = 0x82;
    spA0.unk1F = 0xFF;
    spA0.unk20 = 0xFF;
    spA0.unk21 = 0xFF;
    spA0.unk22 = 0xFF;
    spA0.unk23 = 0xFF;
    spA0.unk24 = 0;
    spA0.unk28 = 0x200004;
    spA0.unk2C = 0x1F0601;
    spA0.unk30 = 8;
    spA0.unk34 = 0x44;
    spA0.unk38 = 0x80;
    spA0.unk3C = 0x20;
    spA0.unk40 = 0;
    spA0.unk41 = 0xA;
    spA0.unk44 = *(u8 *)((s32)arg0 + 0x23D);
    spA0.unk14 &= ~0x6;
    spA0.unk14 |= 0x6;
    spA0.unk0 = 25.0f;
    spA0.unk4 = 25.0f;

    if (arg1) {
        temp_type = 4;
    } else {
        temp_type = 0;
    }
    temp_v0 = func_1515548C(&spA0, temp_type, 0, 0, 0x58, 0xFF, 1);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x70, &sp44, 0x58);
    }

    spA0.unk14 &= ~0x6;
    spA0.unk14 |= 0x4;
    spA0.unk0 = -25.0f;
    spA0.unk4 = 25.0f;
    if (arg1) {
        temp_type = 4;
    } else {
        temp_type = 0;
    }
    temp_v0 = func_1515548C(&spA0, temp_type, 0, 0, 0x58, 0xFF, 1);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x70, &sp44, 0x58);
    }

    spA0.unk14 &= ~0x6;
    spA0.unk0 = -25.0f;
    spA0.unk4 = -25.0f;
    if (arg1) {
        temp_type = 4;
    } else {
        temp_type = 0;
    }
    temp_v0 = func_1515548C(&spA0, temp_type, 0, 0, 0x58, 0xFF, 1);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x70, &sp44, 0x58);
    }

    spA0.unk14 &= ~0x6;
    spA0.unk14 |= 0x2;
    spA0.unk0 = 25.0f;
    spA0.unk4 = -25.0f;
    if (arg1) {
        temp_type = 4;
    } else {
        temp_type = 0;
    }
    temp_v0 = func_1515548C(&spA0, temp_type, 0, 0, 0x58, 0xFF, 1);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x70, &sp44, 0x58);
    }

    spA0.unk0 = 0.0f;
    spA0.unk4 = 0.0f;
    spA0.unkC = 3.0f;
    spA0.unk8 = 3.0f;
    spA0.unk10 = 0x99;
    spA0.unk14 = (1 << (*(u8 *)((s32)arg0 + 0x23D) + 0xB)) | 0x50;
    spA0.unk30 = 8;
    spA0.unk34 = 0x44;
    sp44.unk28 = D_800AAE8C;
    if (D_80082FA0 == 1) {
        sp44.unk18 = -62.0f;
    } else {
        sp44.unk18 = -50.0f;
    }
    sp44.unk1C = 0.0f;
    if (D_80082FA0 == 1) {
        sp44.unk20 = D_800AAE90;
    } else {
        sp44.unk20 = D_800AAE94;
    }
    i = 0;
    sp44.unk24 = 0.0f;

    for (; i != 12; i++) {
        temp_v0 = func_1515548C(&spA0, 7, 0, 0, 0x58, 0xFF, 1);
        if (temp_v0 != NULL) {
            memcpy((u8 *)temp_v0 + 0x70, &sp44, 0x58);
        }
        sp44.unk24 += D_800AAE98;
    }
}

void func_151CAACC(struct102 *arg0, void **arg1, u8 arg2) {
    void (*fn)(struct102 *, void **, u8);
    void *temp;

    if (arg2 == 0x21) {
        if (*(s32 *)((s32)arg0 + 0x70) == *(s32 *)arg1) {
            func_1516972C(arg0);
        label_151CAACC:
            ;
        }
    } else if (arg2 == 0) {
        temp = *arg1;
        if (*(s32 *)((s32)arg0 + 0x70) == *(s32 *)((s32)temp + 0x318)) {
            func_1516972C(arg0);
        }
    }
    fn = D_8008FC10[*(u8 *)((s32)arg0 + 0x7D)];
    if (fn != NULL) {
        fn(arg0, arg1, arg2);
    }
}

void func_151CAB78(void *arg0, u8 arg1) {
    typedef struct {
        f32 unk0;
        f32 unk4;
        f32 unk8;
        f32 unkC;
        u8  unk10;
        u8  pad11;
        s16 unk12;
        s16 unk14;
        s16 unk16;
        s16 unk18;
        u8  unk1A;
        u8  unk1B;
        u8  unk1C;
        u8  unk1D;
        u8  unk1E;
        u8  unk1F;
        u8  unk20;
        u8  unk21;
        u8  unk22;
        u8  unk23;
        s32 unk24;
        s32 unk28;
        s32 unk2C;
        s32 unk30;
        s32 unk34;
        s32 unk38;
        s32 unk3C;
        u8  unk40;
        u8  unk41;
        u8  pad42[2];
        u8  unk44;
        u8  pad45[3];
        f32 unk48;
        f32 unk4C;
        f32 unk50;
        f32 unk54;
    } struct_151CAB78_sp90;
    typedef struct {
        void *unk0;
        f32 unk4;
        f32 unk8;
        u8 unkC;
        u8 unkD;
        u8 padE[0x4E];
    } struct_151CAB78_sp34;
    struct_151CAB78_sp90 sp90;
    struct_151CAB78_sp34 sp34;
    void *temp_v0;
    s32 temp_type;
    f32 temp_f0;

    sp34.unk0 = arg0;
    sp34.unk4 = 0.0f;
    sp34.unkD = 0;
    sp34.unkC = 0;
    sp34.unk8 = 130.0f;

    if (D_80082FA0 > 0) {
        temp_f0 = 2.0f;
    } else {
        temp_f0 = 1.0f;
    }

    sp90.unk10 = 0x64;
    sp90.unk12 = 0x12C;
    sp90.unkC = temp_f0 * 12.0f;
    sp90.unk8 = sp90.unkC;
    sp90.unk14 = (1 << (*(u8 *)((s32)arg0 + 0x23D) + 0xB)) | 0x50;
    sp90.unk16 = 1;
    sp90.unk18 = 0xFF;
    sp90.unk1A = 7;
    sp90.unk1B = 0xFF;
    sp90.unk1C = 0xC8;
    sp90.unk1D = 0;
    sp90.unk1E = 0x82;
    sp90.unk1F = 0xFF;
    sp90.unk20 = 0xFF;
    sp90.unk21 = 0xFF;
    sp90.unk22 = 0xFF;
    sp90.unk23 = 0xFF;
    sp90.unk24 = 0;
    sp90.unk28 = 0x200004;
    sp90.unk2C = 0x1F0601;
    sp90.unk30 = 8;
    sp90.unk34 = 0x44;
    sp90.unk38 = 0x80;
    sp90.unk3C = 0x20;
    sp90.unk40 = 0;
    sp90.unk41 = 0xA;
    sp90.unk0 = 0.0f;
    sp90.unk4 = 0.0f;
    sp90.unk44 = *(u8 *)((s32)arg0 + 0x23D);

    if (arg1 != 0) {
        temp_type = 4;
    } else {
        temp_type = 0;
    }

    temp_v0 = func_1515548C(&sp90, temp_type, 0, 0, 0x58, 0xFF, 1);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x70, &sp34, 0x58);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1F4650/func_151CAD28.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1F4650/func_151CB110.s")

void func_151CB49C(struct102 *arg0, void **arg1, u8 arg2) {
    void *temp_v0;
    s32 temp_a2;

    temp_a2 = arg2;
    if (temp_a2 == 0x21) {
        if (*(s32 *)((s32)arg0 + 0x18) == *(s32 *)arg1) {
            func_1516972C(arg0);
        }
    } else if (temp_a2 == 0) {
        temp_v0 = *arg1;
        if (*(s32 *)((s32)arg0 + 0x18) == *(s32 *)((s32)temp_v0 + 0x318)) {
            func_1516972C(arg0);
        }
    }
}

void func_151CB510(void *arg0) {
    void *temp_v0;
    s32 base;
    f32 target;

    temp_v0 = *(void **)((s32)arg0 + 0x70);
    if ((*(u16 *)*(s32 *)((s32)temp_v0 + 0x36C) & 0x2000) && (base = (s32)arg0 + 0x70, *(u16 *)(*(s32 *)((s32)temp_v0 + 0x3D4) + 0x19E) == 0)) {
        target = *(f32 *)(base + 8);
    } else {
        target = 0.0f;
        base = (s32)arg0 + 0x70;
    }
    *(f32 *)(base + 4) += (target - *(f32 *)(base + 4)) * D_800AAEA8;
    *(u8 *)((s32)arg0 + 0x2E) = (u32)*(f32 *)(base + 4);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1F4650/func_151CB5FC.s")

void func_151CB918(Game1F4650EffectObject *arg0, Game1F4650EffectTriggerEvent *arg1, u8 arg2) {
    Game1F4650EffectState *base = &arg0->field_0x70;

    if (arg2 == 0x37) {
        if (base->field_0xE == arg1->field_0x0) {
            if (base->field_0x0 == arg1->field_0x4) {
                base->field_0x10 = 0.0f;
                base->field_0xC |= 0x1;
                base->field_0x14 = 0.0f;
            }
        }
    }
}

s32 func_151CB970(void *arg0) {
    typedef struct {
        u8 pad0[0xC];
        u8 unkC;
        u8 unkD;
        u8 padE[2];
        f32 unk10;
        f32 unk14;
        f32 unk18;
        u8 pad1C[4];
        f32 unk20;
    } Struct151CB970;
    register Struct151CB970 *base;
    f32 temp_f0;
    f32 pad0;
    f32 temp_f2;
    f32 temp_f12;
    u8 temp_v0;

    base = (Struct151CB970 *)((s32)arg0 + 0x70);
    temp_f0 = func_151CC1D4(arg0);
    temp_f2 = (1.0f - ((temp_f0 - base->unk18) * base->unk20)) * 75.0f;

    if (base->unkC & 1) {
        temp_f0 = sinf(base->unk10);
        temp_f12 = 91.0f + temp_f2;
        pad0 = (112.0f + temp_f2) - temp_f12;
        *(f32 *)((s32)arg0 + 0x14) = (temp_f0 * pad0) + temp_f12;
        base->unk10 += D_800AAEAC * D_800BE9A4;
        if (D_800AAEB0 <= base->unk10) {
            *(f32 *)((s32)arg0 + 0x14) = temp_f12;
            base->unkC &= ~1;
        }
    } else {
        *(f32 *)((s32)arg0 + 0x14) = 91.0f + temp_f2;
    }

    if (base->unkD == 2) {
        *(f32 *)((s32)arg0 + 0x14) -= 20.0f;
    }

    temp_v0 = (u32)base->unk14;
    if (*(u8 *)((s32)arg0 + 0x20) == 0x7C) {
        *(u8 *)((s32)arg0 + 0x2E) = 0xFF - temp_v0;
    } else {
        *(u8 *)((s32)arg0 + 0x2E) = temp_v0;
    }

    base->unk14 += (255.0f - base->unk14) * D_800AAEB4;
    return 1;
}

void func_151CBB6C(struct102 *arg0, void **arg1, u8 arg2) {
    void *temp_v0;
    s32 temp_a2;

    temp_a2 = arg2;
    if (temp_a2 == 0x21) {
        if (*(s32 *)((s32)arg0 + 0x20) == *(s32 *)arg1) {
            func_1516972C(arg0);
        }
    } else if (temp_a2 == 0) {
        temp_v0 = *arg1;
        if (*(s32 *)((s32)arg0 + 0x20) == *(s32 *)((s32)temp_v0 + 0x318)) {
            func_1516972C(arg0);
        }
    }
}

s32 func_151CBBE0(void *arg0) {
    typedef struct {
        u8 pad0[0x18];
        f32 unk18;
        u8 pad1C[4];
        f32 unk20;
        f32 unk24;
        f32 unk28;
    } Struct151CBBE0;
    register Struct151CBBE0 *base;
    f32 scaled;
    f32 temp_f0;

    base = (Struct151CBBE0 *)((s32)arg0 + 0x70);
    temp_f0 = func_151CC1D4(arg0);
    if (temp_f0 != base->unk28) {
        base->unk28 = temp_f0;
        scaled = ((temp_f0 - base->unk18) * base->unk20) * D_800AAEB8;
        func_1514373C(base->unk24 + scaled,
            55.0f, (f32 *)((s32)arg0 + 0x10), (f32 *)((s32)arg0 + 0x14));
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1F4650/func_151CBC60.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1F4650/func_151CC1D4.s")

extern void func_1515572C(s32, s32);

void func_151CC290(s32 arg0) {
    s32 sp1C;

    sp1C = arg0;
    func_1515572C((s32)&sp1C, 0x46);
}

void func_151CC2BC(void *arg0, s32 *arg1, u8 arg2) {
    typedef struct {
        s32 field_0x0;
        u8 pad_0x4[0x8];
        u8 field_0xC;
        u8 pad_0xD[0x1F];
        f32 field_0x2C;
        f32 field_0x30;
        f32 field_0x34;
        f32 field_0x38;
        u8 pad_0x3C[0x14];
        f32 field_0x50;
    } State;
    State *base;

    base = (State *)((s32)arg0 + 0x70);
    if ((arg2 == 0x46) && (*arg1 == *(s32 *)((u8 *)base + 0))) {
        base->field_0xC |= 2;
        base->field_0x50 = 35.0f;
        *(u8 *)((s32)arg0 + 0x2B) = (u32)base->field_0x2C;
        *(u8 *)((s32)arg0 + 0x2C) = (u32)base->field_0x30;
        *(u8 *)((s32)arg0 + 0x2D) = (u32)base->field_0x34;
        *(u8 *)((s32)arg0 + 0x2E) = (u32)base->field_0x38;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1F4650/func_151CC524.s")

s32 func_151CC77C(void *arg0) {
    register f32 *temp_a1;
    register f32 *temp_a2;
    struct {
        f32 sp20;
        f32 sp24;
        s32 pad28;
        s32 pad2C;
    } sp20;
    void *temp_v0;
    void *temp_v1;

    temp_v0 = *(void **)((s32)arg0 + 0x70);
    temp_v1 = *(void **)((s32)temp_v0 + 0x3D0);
    if (temp_v1 == NULL) {
        return 0;
    }
    temp_v0 = *(void **)((s32)temp_v1 + 0x31C);
    temp_a1 = &sp20.sp24;
    temp_a2 = &sp20.sp20;
    if (temp_v0 == NULL) {
        return 0;
    }
    func_15145974((struct17 *)((s32)temp_v0 + 0x130), temp_a1, temp_a2);
    if (*(u8 *)((s32)arg0 + 0x20) == 0x9A) {
        *(f32 *)((s32)arg0 + 0x60) = -((sp20.sp24 * D_800AAED4) * 2560.0f) * 2.0f;
    } else {
        *(f32 *)((s32)arg0 + 0x64) = ((sp20.sp20 * D_800AAED8) * 2560.0f) * 2.0f;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1F4650/func_151CC840.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1F4650/func_151CCD1C.s")

void func_151CCE94(void *arg0) {
    void *temp_v0;
    void *sp28;

    if (D_800BE616 != 0) {
        sp28 = arg0;
        temp_v0 = func_151A4FD0(0, 0, 0, 0xFF, 0, *(u8 *)((s32)arg0 + 0x23D), 1, 4);
        if (temp_v0 != NULL) {
            memcpy((void *)((s32)temp_v0 + 0x20), &sp28, 4);
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1F4650/func_151CCF08.s")

extern f32 func_151CC1D4(void *);

void func_151CD224(Game1F4650EffectObject *arg0) {
    Game1F4650EffectState *base = &arg0->field_0x70;
    f32 ret = func_151CC1D4(arg0);
    f32 temp = (1.0f - (ret - base->field_0x18) * base->field_0x20) * 75.0f;
    if (base->field_0xD == 5) {
        arg0->field_0x14 = 92.0f + temp;
    } else if (base->field_0xD == 4) {
        arg0->field_0x14 = -92.0f - temp;
    }
}
