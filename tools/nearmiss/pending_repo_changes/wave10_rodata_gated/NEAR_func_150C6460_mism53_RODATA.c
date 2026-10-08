#include <ultra64.h>
#define func_1513C73C func_1513C73C_hdr
#include "functions.h"
#undef func_1513C73C
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
    char pad_0x0[0x14];
    f32 field_0x14;
    f32 field_0x18;
    f32 field_0x1C;
    char pad_0x20[0x1B4];
    s32 field_0x1D4;
} GameF3270Actor;

typedef struct {
    char pad_0x0[0x1];
    u8 field_0x1;
    char pad_0x2[0xA];
    u8 field_0xC;
    char pad_0xD[0xB];
    GameF3270Actor *field_0x18;
    char pad_0x1C[0x18];
    f32 field_0x34;
    f32 field_0x38;
    char pad_0x3C[0x1C];
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
        pos[1] = arg0->field_0x18 + D_800A0410;
        pos[2] = arg0->field_0x1C;
        if (func_15045800(pos, 0, arg0->field_0x18 - 100.0f, &arg1->field_0x34) != 0) {
            link.unk8 = arg1->field_0x34;
        } else {
            link.unk8 = arg0->field_0x18 + D_800A0414;
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
    desc.unk24 = D_800A0418;
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

#pragma GLOBAL_ASM("asm/nonmatchings/game_F3270/func_150C60D8.s")

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

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ u8 unk6;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ u8 unk10;
    /* 0x11 */ u8 unk11;
    /* 0x12 */ u8 unk12;
    /* 0x13 */ u8 unk13;
    /* 0x14 */ u8 unk14;
    /* 0x15 */ u8 unk15;
    /* 0x16 */ u8 unk16;
    /* 0x17 */ u8 unk17;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ u8 pad1C[0xC];
} GameF3270EmitDesc;

typedef struct {
    /* 0x00 */ GameF3270ObjectOwner58 *owner;
    /* 0x04 */ u8 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ s16 unk18;
    /* 0x1C */ f32 unk1C;
} GameF3270EmitLink;

extern struct17 D_800887D0;
extern u8 D_800AB414[][3];
extern f32 D_800A043C;
extern f32 D_800A0440;
extern void func_15143134(void *, void *, s32);
extern u8 func_151D8E20(void);
struct210 *func_1513C73C(s32 arg0, u8 arg1, u8 arg2, s32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, u8 arg9, s32 argA, s32 argB, u8 argC, s32 argD);

GameF3270Object *func_150C6460(GameF3270ObjectOwner58 *arg0) {
    GameF3270Object *ret;
    struct17 pos;
    GameF3270Actor *actor;

    ret = NULL;
    actor = arg0->field_0x18;
    if (actor->field_0x1D4 != 0) {
        struct17 offset;

        offset = D_800887D0;
        func_15143134(&offset, &pos, actor->field_0x1D4);
    } else {
        pos.unk0 = actor->field_0x14;
        pos.unk4 = actor->field_0x18;
        pos.unk8 = actor->field_0x1C;
    }
    {
    struct17 probe;
    GameF3270EmitDesc desc;
    GameF3270EmitLink link;
    f32 scale;
    u8 color;
    u32 r3;
    u32 r2;
    u32 r1;

    probe.unk0 = pos.unk0;
    probe.unk4 = pos.unk4 + 200.0f;
    probe.unk8 = pos.unk8;
    if (func_15045800(&probe.unk0, 0, pos.unk4 - 200.0f, &arg0->field_0x34) != 0) {
        color = func_151D8E20();
        probe.unk4 = arg0->field_0x34;
        scale = func_150ADA68() * 50.0f + 100.0f;
        link.owner = arg0;
        link.unk4 = 1;
        link.unk8 = 26214.4f;
        link.unkC = 32768.0f;
        link.unk10 = 0.0f;
        link.unk14 = 0;
        link.unk16 = 10;
        link.unk18 = 10;
        link.unk1C = 0.231f;
        desc.unk0 = 0x20300;
        desc.unk4 = 300;
        desc.unk6 = 0x38;
        desc.unk8 = 0;
        desc.unkC = link.unkC * 0.5f + link.unk8;
        desc.unk10 = 0x96;
        desc.unk11 = 0xFF;
        desc.unk12 = D_800AB414[color][0];
        desc.unk13 = D_800AB414[color][1];
        desc.unk14 = D_800AB414[color][2];
        desc.unk15 = 0xFF;
        desc.unk16 = 0;
        desc.unk17 = 6;
        desc.unk18 = 0x440001;
        r1 = func_150ADA20();
        r2 = func_150ADA20();
        r3 = func_150ADA20();
        ret = (GameF3270Object *)func_1513C73C((s32)&desc, 8, 2, (s32)&arg0->field_0x38, probe.unk0, probe.unk4, probe.unk8,
                                               scale, scale, r1 & 0xFF, ((r3 & 1) << 1) + (r2 & 1), 0x20, arg0->field_0xC, arg0->field_0x1);
        if (ret != NULL) {
            memcpy(&ret->field_0xB0, &link, sizeof(link));
        }
    }
    }
    return ret;
}
