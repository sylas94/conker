#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern f32 D_800A73C0;
extern f32 D_800A73C4;
extern f32 D_800A73C8;

typedef struct {
    char pad_0[0x68];
    u8 field_0x68;
    char pad_0x69;
    u8 field_0x6A;
    char pad_0x6B[0x4];
    u8 field_0x6F;
} GameObjectStateBytes;

typedef struct {
    char pad_0[0x18];
    f32 field_0x18;
    f32 field_0x1C;
} GameObjectFloatPair;

typedef struct {
    char pad_0[0x28];
    u8 field_0x28;
    u8 field_0x29;
    u8 field_0x2A;
    char pad_0x2B[0x2D];
    s32 field_0x58;
    char pad_0x5C[0xB4];
    GameObjectFloatPair field_0x110;
    char pad_0x130[0x58];
    GameObjectStateBytes *field_0x188;
} GameObjectWithStateBytes;

void *func_151407D0(void *, s32, void *, u8, u8, u8, u8, s32, s32, s32);

void *func_15189FF0(void *arg0, void *arg1, void *arg2, u8 arg3, u8 arg4, u8 arg5, u8 arg6) {
    void *obj;

    *((u8 *)arg1 + 0x58) = 0xB;
    obj = func_151407D0(arg1, 0x80, arg0, arg3, arg4, arg5, arg6, -1, 0xFF, 1);
    if (obj != NULL) {
        /* arg2 is the 0x20-byte attach block func_1518A094 reads at obj+0x170 */
        u8 *attach = (u8 *)obj + 0x170;

        memcpy(attach, arg2, 0x20);
    } else {
        return NULL;
    }
    return obj;
}

typedef struct {
    s32 unk0;
    u8 pad4[0x37];
    u8 unk3B;
    u8 pad3C[0x198];
    u8 *unk1D4;
} Target1518A094;

typedef struct {
    f32 x;
    f32 y;
    f32 z;
    f32 x2;
    f32 y2;
    f32 z2;
    Target1518A094 *target;
    u8 bone;
    u8 targetId;
    s8 handler; /* index into D_8008D5A0, -1 = none */
} Attach1518A094;

typedef struct {
    u8 pad0[0x34];
    f32 unk34;
    f32 unk38;
    f32 unk3C;
    f32 unk40;
    f32 unk44;
    f32 unk48;
    u8 pad4C[0xC];
    s32 flags;
    u8 pad5C[0x114];
    Attach1518A094 attach; /* 0x170 */
} Obj1518A094;

extern s32 (*D_8008D5A0[])(void *, u8 *);
void func_150A7960(f32 *, f32, f32, f32, f32 *, f32 *, f32 *);

s32 func_1518A094(Obj1518A094 *arg0) {
    Attach1518A094 *at;

    at = &arg0->attach;
    if (at->target == NULL) {
        at->target = (Target1518A094 *)func_15083E90(at->targetId);
        if (at->target == NULL) {
            return 0;
        }
    }
    if ((at->target->unk0 != 0) && (at->target->unk3B == at->targetId)) {
        if (at->handler != -1) {
            u8 ok;

            if (D_8008D5A0[at->handler](arg0, &ok)) {
                if (!ok) {
                    return 1;
                }
            } else {
                return 0;
            }
        }
        if (at->target->unk1D4 != NULL) {
            f32 *mtx;
            f32 *out;

            mtx = (f32 *)(at->target->unk1D4 + (at->bone << 6));
            out = &arg0->unk34;
            func_150A7960(mtx, at->x, at->y, at->z, &out[0], &out[1], &out[2]);
            out = &arg0->unk40;
            func_150A7960(mtx, at->x2, at->y2, at->z2, &out[0], &out[1], &out[2]);
            arg0->flags |= 2;
            arg0->flags &= ~4;
        } else {
            arg0->flags &= ~2;
        }
    } else {
        return 0;
    }
    return 1;
}

s32 func_1518A214(void *arg0, u8 *arg1) {
    s32 temp_v0;
    GameObjectFloatPair *temp_v0_2;
    f32 temp_f0;

    temp_v0 = ((GameObjectWithStateBytes *)arg0)->field_0x188->field_0x68 - 0xF;
    temp_v0_2 = (GameObjectFloatPair *)((u8 *)arg0 + 0x110);
    switch (temp_v0) {
    default:
        temp_f0 = D_800A73C0;
        temp_v0_2->field_0x18 = temp_f0;
        temp_v0_2->field_0x1C = temp_f0;
        ((GameObjectWithStateBytes *)arg0)->field_0x2A = 0;
        ((GameObjectWithStateBytes *)arg0)->field_0x29 = 0;
        ((GameObjectWithStateBytes *)arg0)->field_0x28 = 0xFF;
        *arg1 = 1;
        break;
    case 0:
        ((GameObjectWithStateBytes *)arg0)->field_0x58 &= ~2;
        *arg1 = 0;
        break;
    case 1:
        temp_f0 = D_800A73C4;
        temp_v0_2->field_0x18 = temp_f0;
        temp_v0_2->field_0x1C = temp_f0;
        ((GameObjectWithStateBytes *)arg0)->field_0x28 = 0x80;
        ((GameObjectWithStateBytes *)arg0)->field_0x29 = 0;
        ((GameObjectWithStateBytes *)arg0)->field_0x2A = 0;
        *arg1 = 1;
        break;
    case 2:
        temp_f0 = D_800A73C8;
        temp_v0_2->field_0x18 = temp_f0;
        temp_v0_2->field_0x1C = temp_f0;
        ((GameObjectWithStateBytes *)arg0)->field_0x28 = 0xFF;
        ((GameObjectWithStateBytes *)arg0)->field_0x29 = 0;
        ((GameObjectWithStateBytes *)arg0)->field_0x2A = 0;
        *arg1 = 1;
        break;
    }
    return 1;
}

s32 func_1518A2E8(GameObjectWithStateBytes *arg0, u8 *arg1) {
    if (arg0->field_0x188->field_0x6A != 0) {
        arg0->field_0x58 &= ~2;
        *arg1 = 0;
    } else {
        *arg1 = 1;
    }
    return 1;
}

s32 func_1518A324(GameObjectWithStateBytes *arg0, u8 *arg1) {
    if (arg0->field_0x188->field_0x6F == 0) {
        arg0->field_0x58 &= ~2;
        *arg1 = 0;
    } else {
        *arg1 = 1;
    }
    return 1;
}

typedef struct {
    s32 unk0;
    s32 unk4;
    u8 unk8;
    u8 unk9;
} GameStruct1518A360a;

typedef struct {
    u8 unk0[0x18];
    s32 unk18;
    u8 unk1C;
    u8 unk1D;
} GameStruct1518A360b;

void func_1518A360(void *arg0, GameStruct1518A360a *arg1, u8 arg2) {
    GameStruct1518A360b *v0 = (GameStruct1518A360b *)((u8 *)arg0 + 0x170);
    if (arg2 == 0x2D) {
        if (v0->unk18 == arg1->unk0) {
            v0->unk18 = arg1->unk4;
            v0->unk1D = arg1->unk9;
        } else if (v0->unk18 == arg1->unk4) {
            v0->unk18 = arg1->unk0;
            v0->unk1D = arg1->unk8;
        }
    }
}
