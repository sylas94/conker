#include <ultra64.h>
#include "functions.h"
#include "variables.h"

void func_1513470C(struct102 *arg0);

typedef struct {
    /* 0x00 */ s32 field_0x00;
    /* 0x04 */ u8 field_0x04;
    /* 0x05 */ u8 pad_0x05[0x3];
    /* 0x08 */ f32 field_0x08;
    /* 0x0C */ f32 field_0x0C;
    /* 0x10 */ f32 field_0x10;
    /* 0x14 */ s16 field_0x14;
    /* 0x16 */ s16 field_0x16;
    /* 0x18 */ s16 field_0x18;
    /* 0x1A */ s16 field_0x1A;
    /* 0x1C */ f32 field_0x1C;
} RandomLerpState;

typedef struct {
    /* 0x00 */ char pad_0x00[0x24];
    /* 0x24 */ s32 field_0x24;
    /* 0x28 */ char pad_0x28[0x88];
    /* 0xB0 */ RandomLerpState field_0xB0;
} RandomLerpObject;

typedef struct {
    /* 0x00 */ char pad_0x00[0x6C];
    /* 0x6C */ RandomLerpObject *field_0x6C;
} RandomLerpOwner;

RandomLerpObject *func_150C6D90(RandomLerpOwner *arg0);

void func_150C66F0(RandomLerpOwner *arg0) {
    RandomLerpState *temp;

    if (*(s32 *)&arg0->field_0x6C != 0) {
        temp = &arg0->field_0x6C->field_0xB0;
        temp->field_0x04 = 1;
        done:
            ;
    } else {
        arg0->field_0x6C = func_150C6D90(arg0);
    }
}

s32 func_150C673C(RandomLerpObject *arg0) {
    s8 ret;
    RandomLerpState *sub;

    ret = 1;
    sub = &arg0->field_0xB0;
    if (sub->field_0x04 == 0) {
        ret = 0;
    }
    sub->field_0x04 = 0;
    sub->field_0x14 -= D_800BE9E4;
    if (sub->field_0x14 < 0) {
        sub->field_0x14 = (func_150ADA20() % (u32)(sub->field_0x18 + 1)) + sub->field_0x16;
        sub->field_0x10 = func_150ADA68() * sub->field_0x0C + sub->field_0x08;
    }
    arg0->field_0x24 += (s32)((sub->field_0x10 - (f32)arg0->field_0x24) * sub->field_0x1C);
    return ret;
}

extern s32 func_1513F6C0(void *arg0, s32 arg1, s32 arg2);

s32 func_150C682C(u8 *arg0) {
    s32 *temp = (s32 *)((*(u8 **)((u8 *)arg0 + 0xB0)) + 0x58);
    temp[5] = 0;
    *(s32 *)((u8 *)arg0 + 0x18) |= 2;
    *(u8 **)((u8 *)arg0 + 0xB0) = 0;
    func_1513F6C0(arg0, 0, 0);
    return 0;
}

s32 func_150C68C4(s32 arg0, u8 *arg1);

void func_150C6870(u8 *arg0) {
    s32 temp = *(s32 *)((u8 *)arg0 + 0x18);
    if (*(s32 *)((u8 *)arg0 + 0x70) != 0) {
        u8 *p = *(u8 **)((u8 *)arg0 + 0x70) + 0x58;
        p[4] = 1;
    } else {
        *(s32 *)((u8 *)arg0 + 0x70) = func_150C68C4(temp, arg0);
    }
}

typedef struct {
    u8 pad0[0x14];
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    u8 pad20[0x1B];
    u8 unk3B;
} Actor150C68C4;

typedef struct {
    u8 *unk0;
    u8 unk4;
    f32 unk8;
} Link150C68C4;

typedef struct {
    s32 unk0;
    s32 unk4;
    u8 unk8;
    void *unkC;
    u8 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    s16 unk28;
    u8 unk2A;
    u8 unk2B;
    u8 unk2C;
    u8 unk2D;
} Spawn150C68C4;

extern s32 func_15045800(f32 *, s32, f32, f32 *);
extern void *func_1513418C(void *, s32, u8, s32);

s32 func_150C68C4(s32 arg0, u8 *arg1) {
    Spawn150C68C4 spawn;
    Link150C68C4 link;
    void *ret;

    link.unk0 = arg1;
    link.unk4 = 1;
    {
        f32 pos[3];

        pos[0] = ((Actor150C68C4 *)arg0)->unk14;
        pos[1] = ((Actor150C68C4 *)arg0)->unk18 + 5000.0f;
        pos[2] = ((Actor150C68C4 *)arg0)->unk1C;
        if (func_15045800(pos, 0, ((Actor150C68C4 *)arg0)->unk18 - 100.0f, (f32 *)(arg1 + 0x34)) != 0) {
            link.unk8 = *(f32 *)(arg1 + 0x34);
        } else {
            link.unk8 = ((Actor150C68C4 *)arg0)->unk18 + 5000.0f;
        }
    }
    spawn.unk0 = 0;
    spawn.unk4 = 0;
    spawn.unk8 = ((Actor150C68C4 *)arg0)->unk3B;
    spawn.unkC = (void *)arg0;
    spawn.unk10 = 0;
    spawn.unk14 = 0.0f;
    spawn.unk18 = 0.0f;
    spawn.unk1C = 0.0f;
    spawn.unk20 = 80.0f;
    spawn.unk24 = 0.60497f;
    spawn.unk28 = 0x12C;
    spawn.unk2A = 10;
    spawn.unk2B = 5;
    spawn.unk2C = 2;
    spawn.unk2D = 3;
    ret = func_1513418C(&spawn, 0xC, 0xFF, 0);
    if (ret != NULL) {
        memcpy((u8 *)ret + 0x58, &link, 0xC);
    }
    return (s32)ret;
}

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ u8 unk14;
    /* 0x15 */ u8 unk15;
    /* 0x16 */ u8 unk16;
    /* 0x17 */ u8 unk17;
    /* 0x18 */ u8 unk18;
    /* 0x19 */ u8 unk19;
    /* 0x1A */ u8 unk1A;
    /* 0x1B */ u8 unk1B;
    /* 0x1C */ u8 unk1C;
    /* 0x1D */ u8 unk1D;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ s16 unk22;
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
    /* 0x50 */ f32 unk50;
    /* 0x54 */ f32 unk54;
    /* 0x58 */ s32 unk58;
    /* 0x5C */ u8 pad5C[4];
    /* 0x60 */ u8 unk60;
    /* 0x61 */ u8 unk61;
    /* 0x62 */ u8 unk62;
    /* 0x63 */ s8 unk63;
    /* 0x64 */ u8 pad64[0x8];
} GameF3BA0SplashDesc;

typedef struct {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ u8 unk4;
    /* 0x05 */ u8 unk5;
    /* 0x06 */ u8 unk6;
    /* 0x07 */ u8 unk7;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ u8 unk18;
    /* 0x19 */ u8 unk19;
    /* 0x1A */ u8 unk1A;
    /* 0x1B */ u8 unk1B;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
} GameF3BA0SplashState;

typedef struct {
    char pad_0x0[0x60];
    f32 field_0x60;
} GameF3BA0SplashOwner;

extern void *func_151303BC(GameF3BA0SplashDesc *, s32, s32);

void func_150C6A08(f32 arg0, f32 arg1, f32 arg2, f32 arg3, s32 arg4, f32 arg5, GameF3BA0SplashOwner *arg6) {
    void *ret;
    GameF3BA0SplashDesc desc;
    f32 size;
    GameF3BA0SplashState state;

    desc.unk1D = 0x2F;
    desc.unk8 = 0xC01;
    desc.unk0 = 0x200005;
    desc.unk4 = 0;
    desc.unkC = desc.unk10 = desc.unk14 = desc.unk15 = desc.unk16 = desc.unk17 = desc.unk18 = desc.unk19 = desc.unk1A = 0;
    desc.unk1C = 0xFF;
    desc.unk22 = 0;
    desc.unk24 = 0.0f;
    desc.unk58 = 0x3207;
    desc.unk60 = 5;
    desc.unk61 = 5;
    desc.unk62 = 4;
    desc.unk63 = -1;
    desc.unk30 = arg0;
    desc.unk34 = arg1;
    desc.unk3C = 0.0f;
    desc.unk40 = 0.0f;
    desc.unk44 = 0.0f;
    desc.unk1E = 0x1E;
    desc.unk20 = 8;
    desc.unk38 = arg2;
    state.unk24 = arg6->field_0x60;
    state.unk10 = 4.0f;
    state.unk14 = 0.25f;
    state.unk4 = 0;
    state.unk5 = 0;
    state.unk18 = 0;
    state.unk19 = 0;
    desc.unk48 = -arg3 * 0.2f;
    desc.unk4C = 0.0f;
    desc.unk50 = -arg5 * 0.2f;
    if (func_150ADA20() & 1) {
        desc.unk58 |= 0x40;
    }
    if (func_150ADA20() & 1) {
        desc.unk58 |= 0x80;
    }
    desc.unkA = func_150ADA20() % 51U + 0x6A;
    desc.unk1B = func_150ADA20() % 101U + 100;
    size = func_150ADA68() * 62.0f + 41.0f;
    desc.unk28 = size;
    state.unk0 = size;
    desc.unk2C = size;
    state.unk6 = func_150ADA20() % 5U + 4;
    state.unk7 = func_150ADA20() % 5U + 4;
    state.unk8 = (func_150ADA68() * 0.25f + 0.15f) * state.unk0;
    state.unkC = (func_150ADA68() * 0.25f + 0.15f) * state.unk0;
    state.unk1A = func_150ADA20() % 5U + 4;
    state.unk1B = func_150ADA20() % 5U + 4;
    state.unk1C = (func_150ADA68() * 0.1f + 0.08f) * state.unk0;
    state.unk20 = (func_150ADA68() * 0.1f + 0.08f) * state.unk0;
    desc.unk54 = (func_150ADA68() * 60.0f + 21.0f) * 0.001f;
    ret = func_151303BC(&desc, 2, 0x28);
    if (ret != NULL) {
        memcpy((u8 *)ret + 0xA8, &state, sizeof(state));
    }
}

typedef struct {
    char pad[0x5C];
    u8 unk5C;
} Func150C6D1CArg;

s32 func_150C6D1C(Func150C6D1CArg* arg) {
    s32 ret = 1;
    if (arg->unk5C == 0) {
        ret = 0;
    }
    arg->unk5C = 0;
    return ret;
}

typedef struct {
    char pad[0x18];
    s32 unk18;
} Func150C6D40Inner;

typedef struct {
    char pad[0x58];
    Func150C6D40Inner inner58;
} Func150C6D40Sub;

typedef struct {
    char pad[0x58];
    Func150C6D40Sub* unk58;
} Func150C6D40Arg;

void func_150C6D40(Func150C6D40Arg* arg0) {
    Func150C6D40Inner* inner = &arg0->unk58->inner58;
    inner->unk18 = 0;
    func_151346EC((struct102*)arg0);
}

void func_150C6D68(Func150C6D40Arg* arg0) {
    Func150C6D40Inner* inner = &arg0->unk58->inner58;
    inner->unk18 = 0;
    func_1513470C((struct102*)arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_F3BA0/func_150C6D90.s")
