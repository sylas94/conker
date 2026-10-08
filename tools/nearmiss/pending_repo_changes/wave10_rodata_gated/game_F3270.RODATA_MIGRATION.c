#include <ultra64.h>
#include "functions.h"
#include "variables.h"

typedef struct {
    char pad_0x0[0x4];
    u8 field_0x4;
} GameF3270Child58State;

typedef struct {
    char pad_0x0[0x58];
    GameF3270Child58State field_0x58;
} GameF3270SpawnedObject;

typedef struct {
    char pad_0x0[0x18];
    s32 field_0x18;
    char pad_0x1C[0x18];
    f32 field_0x34;
    char pad_0x38[0x24];
    GameF3270SpawnedObject *field_0x5C;
} GameF3270SpawnOwner;

typedef struct {
    char pad_0x0[0x4];
    u8 field_0x4;
    char pad_0x5[0x3];
    f32 field_0x8;
    f32 field_0xC;
    f32 field_0x10;
    s16 field_0x14;
    s16 field_0x16;
    s16 field_0x18;
    char pad_0x1A[0x2];
    f32 field_0x1C;
} GameF3270B0State;

typedef struct {
    char pad_0x0[0x24];
    s32 field_0x24;
    char pad_0x28[0x88];
    GameF3270B0State field_0xB0;
} GameF3270Object;

typedef struct {
    char pad_0x0[0x58];
    GameF3270Object *field_0x58;
} GameF3270ObjectOwner58;

GameF3270Object *func_150C6460(GameF3270ObjectOwner58 *arg0);
typedef struct {
    char pad_0x0[0x14];
    f32 field_0x14;
    f32 field_0x18;
    f32 field_0x1C;
    char pad_0x20[0x1B];
    u8 field_0x3B;
} GameF3270SpawnSource;

GameF3270SpawnedObject *func_150C5F94(GameF3270SpawnSource *arg0, GameF3270SpawnOwner *arg1);

void func_150C5DC0(GameF3270ObjectOwner58 *arg0) {
    GameF3270B0State *temp;

    if (*(s32 *)&arg0->field_0x58 != 0) {
        temp = &arg0->field_0x58->field_0xB0;
        temp->field_0x4 = 1;
        done:
            ;
    } else {
        arg0->field_0x58 = func_150C6460(arg0);
    }
}

s32 func_150C5E0C(GameF3270Object *arg0) {
    s8 ret;
    GameF3270B0State *sub;

    ret = 1;
    sub = &arg0->field_0xB0;
    if (sub->field_0x4 == 0) {
        ret = 0;
    }
    sub->field_0x4 = 0;
    sub->field_0x14 -= D_800BE9E4;
    if (sub->field_0x14 < 0) {
        sub->field_0x14 = (func_150ADA20() % (u32)(sub->field_0x18 + 1)) + sub->field_0x16;
        sub->field_0x10 = func_150ADA68() * sub->field_0xC + sub->field_0x8;
    }
    arg0->field_0x24 += (s32)((sub->field_0x10 - (f32)arg0->field_0x24) * sub->field_0x1C);
    return ret;
}

extern s32 func_1513F6C0(void *arg0, s32 arg1, s32 arg2);

s32 func_150C5EFC(u8 *arg0) {
    s32 *temp = (s32 *)((*(u8 **)((u8 *)arg0 + 0xB0)) + 0x58);
    temp[0] = 0;
    *(s32 *)((u8 *)arg0 + 0x18) |= 2;
    *(u8 **)((u8 *)arg0 + 0xB0) = 0;
    func_1513F6C0(arg0, 0, 0);
    return 0;
}

void func_150C5F40(GameF3270SpawnOwner *arg0) {
    s32 temp_a2;
    GameF3270Child58State *temp;

    temp_a2 = arg0->field_0x18;
    if (*(s32 *)&arg0->field_0x5C != 0) {
        temp = &arg0->field_0x5C->field_0x58;
        temp->field_0x4 = 1;
        done:
            ;
    } else {
        arg0->field_0x5C = func_150C5F94((GameF3270SpawnSource *)temp_a2, arg0);
    }
}

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ u8 unk8;
    /* 0x09 */ u8 pad9[0x3];
    /* 0x0C */ GameF3270SpawnSource *unkC;
    /* 0x10 */ u8 unk10;
    /* 0x11 */ u8 pad11[0x3];
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ s16 unk28;
    /* 0x2A */ u8 unk2A;
    /* 0x2B */ u8 unk2B;
    /* 0x2C */ s8 unk2C;
    /* 0x2D */ u8 unk2D;
} GameF3270SpawnDesc;

typedef struct {
    /* 0x00 */ GameF3270SpawnOwner *owner;
    /* 0x04 */ u8 unk4;
    /* 0x08 */ f32 unk8;
} GameF3270SpawnLink;

extern f32 D_800A0410;
extern f32 D_800A0414;
extern f32 D_800A0418;
extern s32 func_15045800(f32 *, s32, f32, f32 *);
extern GameF3270SpawnedObject *func_1513418C(GameF3270SpawnDesc *, s32, u8, s32);

GameF3270SpawnedObject *func_150C5F94(GameF3270SpawnSource *arg0, GameF3270SpawnOwner *arg1) {
    GameF3270SpawnDesc desc;
    GameF3270SpawnLink link;
    GameF3270SpawnedObject *result;

    link.owner = arg1;
    link.unk4 = 1;
    {
        f32 pos[3];

        pos[0] = arg0->field_0x14;
        pos[1] = arg0->field_0x18 + 5000.0f;
        pos[2] = arg0->field_0x1C;
        if (func_15045800(pos, 0, arg0->field_0x18 - 100.0f, &arg1->field_0x34) != 0) {
            link.unk8 = arg1->field_0x34;
        } else {
            link.unk8 = arg0->field_0x18 + 5000.0f;
        }
    }
    desc.unk0 = 0;
    desc.unk4 = 0;
    desc.unk8 = arg0->field_0x3B;
    desc.unkC = arg0;
    desc.unk10 = 0;
    desc.unk14 = 0.0f;
    desc.unk18 = 0.0f;
    desc.unk1C = 0.0f;
    desc.unk20 = 25.0f;
    desc.unk24 = 0.132485002f;
    desc.unk28 = 300;
    desc.unk2A = 10;
    desc.unk2B = 4;
    desc.unk2C = 1;
    desc.unk2D = 2;
    result = func_1513418C(&desc, 0xC, 0xFF, 0);
    if (result != NULL) {
        memcpy(&result->field_0x58, &link, sizeof(link));
    }
    return result;
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
} GameF3270SplashDesc;

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
} GameF3270SplashState;

typedef struct {
    char pad_0x0[0x60];
    f32 field_0x60;
} GameF3270SplashOwner;

extern f32 D_800A041C;
extern f32 D_800A0420;
extern f32 D_800A0424;
extern f32 D_800A0428;
extern f32 D_800A042C;
extern f32 D_800A0430;
extern f32 D_800A0434;
extern f32 D_800A0438;
extern void *func_151303BC(GameF3270SplashDesc *, s32, s32);

void func_150C60D8(f32 arg0, f32 arg1, f32 arg2, f32 arg3, s32 arg4, f32 arg5, GameF3270SplashOwner *arg6) {
    void *ret;
    GameF3270SplashDesc desc;
    f32 size;
    GameF3270SplashState state;

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

s32 func_150C63EC(u8 *arg0) {
    s32 ret = 1;

    if (arg0[0x5C] == 0) {
        ret = 0;
    }
    arg0[0x5C] = 0;
    return ret;
}

void func_150C6410(struct102 *arg0) {
    s32 *temp = (s32 *)((*(u8 **)((u8 *)arg0 + 0x58)) + 0x58);
    temp[1] = 0;
    func_151346EC(arg0);
}

void func_150C6438(struct102 *arg0) {
    s32 *temp = (s32 *)((*(u8 **)((u8 *)arg0 + 0x58)) + 0x58);
    temp[1] = 0;
    func_1513470C(arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_F3270/func_150C6460.s")
