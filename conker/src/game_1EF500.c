#include <ultra64.h>
#define func_150ADA20 func_150ADA20_u8_proto
#include "functions.h"
#undef func_150ADA20
#include "variables.h"

typedef void (*GameFunc151C455CDispatch)(s32);
typedef void (*GameFunc151C455CCallback)(struct17 *, s32);

extern GameFunc151C455CDispatch D_8008FBD0[];
extern s32 func_150ADA20(void);
extern s32 func_1000B060(f32, f32, u32);
extern void func_1000E7A0(u32, s32);
extern s32 func_1510F8CC(s32);
extern f32 D_800AAA30;
extern f32 D_800AAA34;
extern f32 D_800AAA7C;
extern f32 D_800AAA80;
extern f32 D_800AAA84;

typedef struct {
    u8 pad0[0x2C];
    s16 unk2C;
} GameStruct151C2050State;

void func_151C2050(struct127 *arg0, f32 *arg1, f32 *arg2, s32 arg3, f32 arg4) {
    s32 sp4C;
    s32 sp48;
    struct108 *camera;
    s32 sp40;
    s16 temp_v0;
    f32 sp34;
    f32 temp_f0;

    if (arg0 != 0) {
        if ((D_800BE616 != 0) || ((camera = arg0->camera) == 0)) {
            temp_v0 = ((GameStruct151C2050State *)D_800B0DF0)->unk2C;
            if ((temp_v0 == 0x24) || (temp_v0 == 0x13) || (temp_v0 == 0x4D) || (temp_v0 == 0x85) || (temp_v0 == 0x93)) {
                func_100114D0((s32)arg1[0], (s32)arg1[1], (s32)arg1[2], 0x7FFF, 0x3E8, 0x64, &sp4C, &sp48, 0);
                if ((u32)sp48 >= 0x1001U) {
                    sp48 = (u32)sp48 >> 7;
                    func_1000E7A0(8, (func_1510F8CC(arg3) + 1) | (sp48 << 8) | (sp4C << 16));
                }
            }
        } else {
            temp_v0 = ((GameStruct151C2050State *)D_800B0DF0)->unk2C;
            if ((temp_v0 == 0x24) || (temp_v0 == 0x13)) {
                temp_f0 = 255.0f - (arg4 * D_800AAA30);
                if (temp_f0 > 16.0f) {
                    sp34 = temp_f0;
                    sp40 = func_1000B060(arg2[0], arg2[2], (u32)(camera->unk3A0 * D_800AAA34));
                    func_1000E7A0(8, (func_1510F8CC(arg3) + 1) | ((s32)sp34 << 8) | (sp40 << 16));
                }
            }
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1EF500/func_151C229C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1EF500/func_151C2734.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1EF500/func_151C2AD0.s")

typedef struct {
    s32 unk0;
    u8 unk4;
} GameStruct151C2E4C;

s32 func_151C2E4C(GameStruct151C2E4C *a0, GameStruct151C2E4C *a1) {
    if (a0 == a1) {
        return 0;
    }
    if (a0->unk0 == 0) {
        return 0;
    }
    if (a0->unk4 == 0xFF) {
        return 0;
    }
    return 1;
}

typedef struct {
    s32 unk0;
    u8 unk4;
    u8 pad[0x122];
    u8 unk127;
} GameStruct151C2E94;

s32 func_151C2E94(GameStruct151C2E94 *a0, GameStruct151C2E94 *a1) {
    if (a0 == a1) {
        return 0;
    }
    if (a0->unk0 == 0) {
        return 0;
    }
    if (a0->unk4 == 0xFF) {
        return 0;
    }
    if (a0->unk127 == 0xFF) {
        return 0;
    }
    return 1;
}

s32 func_151D4DAC(s32, s32, s32, s32, s32, s32, void *, s32, s32);

s32 func_151C2EF0(s32 a0, s32 a1, struct108 *a2, s32 a3, s32 arg4, s32 arg5) {
    return func_151D4DAC(a0, a1, a3, arg4, arg5, *(s32 *)((u8 *)a2 + 0x1B4),
                         (u8 *)a2 + 0x170, *((u8 *)a2 + 0xC), *((u8 *)a2 + 0x1));
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1EF500/func_151C2F48.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1EF500/func_151C329C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1EF500/func_151C36D8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1EF500/func_151C3B0C.s")

void func_151C436C(s32 a0, f32 *a1, s32 a2) {
    f32 x;
    f32 tx;
    f32 y;
    f32 ty;
    f32 z;
    f32 tz;
    f32 factor;

    if (a2 > 0) {
        x = a1[4];
        tx = a1[7];
        y = a1[5];
        ty = a1[8];
        z = a1[6];
        tz = a1[9];
        factor = D_800AAA7C;
        do {
            a1[4] += (tx - a1[4]) * factor;
            a1[5] += (ty - a1[5]) * factor;
            a1[6] += (tz - a1[6]) * factor;
            a2--;
        } while (a2 > 0);
    }
}

typedef struct {
    s32 unk00;
    f32 unk04;
    struct17 unk08;
    struct17 unk14;
    struct17 unk20;
    struct17 unk2C;
    struct17 unk38;
    u8 unk44[0x12];
    s16 unk56;
    u8 unk58;
    u8 unk59;
    u8 unk5A;
    u8 pad5B;
    s32 unk5C;
    s32 unk60;
    u8 pad64[0xC];
} Ray151C43E0;

typedef struct {
    u8 unk0;
    u8 pad1[0x5F];
    f32 unk60;
    f32 unk64;
    f32 unk68;
    u8 pad6C[0x20];
    f32 unk8C;
    s32 unk90;
    u8 pad94[4];
    f32 unk98;
    u8 pad9C[0xC];
    s8 unkA8;
    u8 padA9[3];
    s32 unkAC;
} Mover151C43E0;

typedef struct {
    u8 pad0[0x34];
    struct17 pos;
} Pos151C43E0;

void func_15081690(s32, f32, f32, f32, f32, f32, f32, Ray151C43E0 *, f32, s32, s32, s32, s32, s32, s32);

u8 func_151C43E0(struct108 *arg0, Mover151C43E0 *arg1, f32 arg2) {
    u8 result;
    s32 obj;
    f32 scale;
    Ray151C43E0 ray;
    s32 solid;

    obj = arg1->unk90;
    result = 1;
    if (arg1->unk0 & 4) {
        if (arg1->unk8C < arg2) {
            scale = arg1->unk98 * arg1->unk8C;
        } else {
            scale = arg1->unk98 * arg2;
        }
        if (scale != 0.0f) {
            struct17 *from = &((Pos151C43E0 *)arg0)->pos;

            solid = !(arg1->unk0 & 8);
            func_15081690(obj, from->unk0, from->unk4, from->unk8, arg1->unk60, arg1->unk64, arg1->unk68, &ray, scale, 1, 0,
                          solid, arg1->unkA8, 0, arg1->unkAC);
            if (ray.unk59 >= 2) {
                func_151C2EF0(ray.unk00, obj, arg0, (s32)&ray.unk08, (s32)&ray.unk20, (s32)&ray);
                result = 0;
            }
        }
    }
    return result;
}

typedef struct {
    u8 pad0[0x34];
    f32 unk34;
    f32 unk38;
    f32 unk3C;
} GameStruct151C4510a;

typedef struct {
    u8 pad0[0x4];
    f32 unk4;
    f32 unk8;
    f32 unkC;
} GameStruct151C4510b;

void func_151C4510(GameStruct151C4510a *a0, GameStruct151C4510b *a1, f32 a2) {
    a0->unk34 += a1->unk4 * a2;
    a0->unk38 += a1->unk8 * a2;
    a0->unk3C += a1->unkC * a2;
}

typedef struct {
    u8 unk0;
    u8 pad1[0x83];
    struct131 *unk84;
    u8 pad88[0x4];
    f32 unk8C;
    u8 pad90[0xC];
    s8 unk9C;
} GameStruct151C455C;

s32 func_151C455C(s32 arg0, GameStruct151C455C *arg1, f32 arg2) {
    s32 ret;
    GameFunc151C455CCallback callback;
    struct131 *temp_v1;
    s8 index;

    arg1->unk8C -= arg2;
    ret = 1;
    if (arg1->unk8C <= 0.0f) {
        callback = (GameFunc151C455CCallback)D_800E0940;
        if ((callback != 0) && (arg1->unk0 & 1)) {
            temp_v1 = arg1->unk84;
            if (temp_v1 != 0) {
                callback((struct17 *)((u8 *)arg1 + 0x30), temp_v1 - D_800DBEF4);
            }
        }
        if (arg1->unk0 & 2) {
            index = arg1->unk9C;
            if (index != -1) {
                D_8008FBD0[index](arg0);
            }
        }
        ret = 0;
    }
    return ret;
}

typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
} GameStruct151C4644Vec;

typedef struct {
    GameStruct151C4644Vec *unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s16 unk10;
    s16 unk12;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    f32 unk30;
    f32 unk34;
} GameStruct151C4644Sub;

typedef struct {
    u8 pad0[1];
    u8 unk1;
    u8 pad2[0xA];
    u8 unkC;
    u8 padD[0x1B];
    GameStruct151C4644Sub unk28;
} GameStruct151C4644;

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
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
    f32 unk40;
} GameStruct151C4644Payload;

void func_151C4644(GameStruct151C4644 *arg0) {
    GameStruct151C4644Sub *sub;
    GameStruct151C4644Payload sp48;
    struct260 *temp_v0;

    sub = &arg0->unk28;
    sub->unk4 -= D_800BE9E4;
    if (sub->unk4 < 0) {
        sp48.unk0 = sub->unk1C;
        sp48.unk4 = sub->unk20;
        sp48.unk8 = func_150ADA68() * sub->unk24;
        sp48.unkC = func_150ADA68() * sub->unk24;
        sp48.unk10 = func_150ADA68() * D_800AAA80;
        sp48.unk14 = func_150ADA68() * D_800AAA84;
        sp48.unk18 = sub->unk28;
        sp48.unk1C = sub->unk28;
        sp48.unk20 = 0.0f;
        sp48.unk24 = (func_150ADA68() * sub->unk18) + sub->unk14;
        sp48.unk28 = 0.0f;
        sp48.unk2C = sub->unk0->unk0;
        sp48.unk30 = sub->unk0->unk2;
        sp48.unk34 = sub->unk0->unk4;
        sp48.unk38 = sub->unk2C;
        sp48.unk3C = sub->unk30;
        sp48.unk40 = sub->unk34;

        temp_v0 = func_15149130((s16)((func_150ADA20() % (u32)(sub->unk12 + 1)) + sub->unk10),
                                -1, 0x2B, -1, 1, 0, (struct37 *)0x44, arg0->unkC, arg0->unk1);
        if (temp_v0 != NULL) {
            memcpy((u8 *)temp_v0 + 0x28, &sp48, 0x44);
        }

        sub->unk4 = (func_150ADA20() % (u32)(sub->unkC + 1)) + sub->unk8;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1EF500/func_151C4820.s")

typedef struct {
    s32 unk0;
    s32 unk4;
    u8 unk8;
    u8 unk9;
} GameStruct151C4AB0a;

typedef struct {
    u8 pad0[0x90];
    s32 unk90;
    u8 unk94;
} GameStruct151C4AB0b;

void func_151C4AB0(void *a0, GameStruct151C4AB0a *a1, u8 a2) {
    GameStruct151C4AB0b *v0 = (GameStruct151C4AB0b *)((u8 *)a0 + 0x110);
    if (a2 == 0x2D) {
        if (v0->unk90 == a1->unk0) {
            v0->unk90 = a1->unk4;
            v0->unk94 = a1->unk9;
        } else if (v0->unk90 == a1->unk4) {
            v0->unk90 = a1->unk0;
            v0->unk94 = a1->unk8;
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1EF500/func_151C4B0C.s")
