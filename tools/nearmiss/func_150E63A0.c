/* PARK 2026-10-08 (wave 10C): mism 258, frame 0xA0 right. Golden keeps scale in f0 (loaded once), stores prev to stack and reloads, keeps d/m in named FP pool. Refuted: struct17 vs f32[3] prev, a scale local (frame grows to 0xA8). Next: map the 15 -g3 local slots between prev (0x88) and vtx (0x48). */
#include <ultra64.h>
#define func_1513D524 func_1513D524_void_proto
#include "functions.h"
#undef func_1513D524
#include "variables.h"

extern s32 func_150AC9C0(f32, f32, f32, f32, f32, f32, void *, void *, f32 *, f32 *, f32 *, s32, s32 *, s32, f32);
extern f32 func_15144A74(struct17 *, struct17 *);
extern s32 func_15145C90(s32);
extern s32 func_1513D524(s32, u8, u8, u8, u8, u8, s32, u8, s32);

typedef struct {
    u8 unk0;
    u8 pad1;
    s16 unk2;
    s16 unk4;
    u8 pad6[2];
    s32 unk8;
    s32 unkC;
    u8 unk10;
    u8 unk11;
    u8 unk12;
    u8 unk13;
    f32 unk14;
    f32 unk18;
    struct17 unk1C;
    struct17 unk28;
    f32 unk34;
    f32 unk38;
    f32 unk3C;
    s32 unk40;
    u8 unk44;
    u8 unk45;
    u8 pad46[0x12];
} Struct150E5FD0Local;

typedef struct {
    u8 field_0x00;
    u8 pad_0x01[3];
    struct17 field_0x04;
    s32 field_0x10;
    s32 field_0x14[5];
    f32 field_0x28;
    s8 field_0x2C;
    u8 pad_0x2D[3];
} Struct150E5FD0Extra;

typedef struct {
    u8 pad_0x00[0x1];
    u8 field_0x01;
    u8 pad_0x02[0xA];
    u8 field_0x0C;
    u8 pad_0x0D[0x103];
    Struct150E5FD0Extra field_0x110;
} Struct150EEffectObject;

s32 func_150E5FD0(struct17 *arg0, struct17 *arg1, f32 arg2, f32 arg3, f32 arg4, u8 arg5, s32 arg6, u8 arg7, u8 arg8, s16 arg9, s8 argA) {
    s32 ret;
    Struct150E5FD0Local sp94;
    Struct150E5FD0Extra sp64;
    s32 sp60;
    struct17 sp54;
    s32 temp_v0;
    s32 temp_v1;

    sp94.unk0 = 0x41;
    sp94.unk2 = 0x2301;
    sp94.unk8 = 0;
    sp94.unkC = 0;
    sp94.unk10 = 0;
    sp94.unk11 = 0;
    sp94.unk12 = 0;
    sp94.unk4 = arg9;
    sp94.unk13 = 0xFF;
    sp94.unk44 = arg8;
    sp94.unk45 = 0xFF;
    sp94.unk14 = arg3;
    sp94.unk18 = arg4;
    sp94.unk1C = *arg0;
    sp94.unk28 = *arg1;
    sp94.unk34 = 0.0f;
    sp94.unk38 = arg2;
    sp94.unk3C = 0.0f;
    sp94.unk40 = 1;
    sp64.field_0x00 = 0;
    sp64.field_0x2C = argA;
    if ((arg7 != 0) && (func_150AC9C0(arg0->unk0, arg0->unk4, arg0->unk8, arg1->unk0, arg1->unk4, arg1->unk8, &sp64.field_0x10, &sp64.field_0x14, &sp64.field_0x04.unk0, &sp64.field_0x04.unk4, &sp64.field_0x04.unk8, 0, &sp60, 0, 0.0f) != 0) && (func_15145C90(sp60) != 0)) {
        sp64.field_0x00 |= 1;
        sp54.unk0 = sp64.field_0x04.unk0 - sp94.unk1C.unk0;
        sp54.unk4 = sp64.field_0x04.unk4 - sp94.unk1C.unk4;
        sp54.unk8 = sp64.field_0x04.unk8 - sp94.unk1C.unk8;
        if (func_15144A74(&sp54, &sp64.field_0x04) < 0.0f) {
            sp64.field_0x28 = -1.0f;
        } else {
            sp64.field_0x28 = 1.0f;
        }
    }
    if (func_150ADA20() & 1) {
        temp_v1 = 2;
    } else {
        temp_v1 = 0;
    }
    if (func_150ADA20() & 1) {
        temp_v0 = 1;
    } else {
        temp_v0 = 0;
    }
    ret = func_1513D524((s32)&sp94, 0xF, 0x15, 0, 0xF, (u8)(temp_v0 | temp_v1), 0x30, arg5, arg6);
    if (ret != 0) {
        memcpy((u8 *)ret + 0x110, &sp64, sizeof(sp64));
    }
    return ret;
}

typedef struct {
    u8 pad_0x00[0x34];
    f32 field_0x34;
    f32 field_0x38;
    f32 field_0x3C;
    f32 field_0x40;
    f32 field_0x44;
    f32 field_0x48;
    u8 pad_0x4C[4];
    f32 field_0x50;
    u8 pad_0x54[0xBC];
    Struct150E5FD0Extra field_0x110;
} Struct150E6230Object;

extern s32 (*D_80088A10[])(Struct150E6230Object *);

s8 func_150E6230(Struct150E6230Object *arg0) {
    s8 ret = 1;

    {
        Struct150E5FD0Extra *e = &arg0->field_0x110;
        f32 sign;
        struct17 sp30;

        if (e->field_0x00 & 1) {
            sp30.unk0 = e->field_0x04.unk0 - arg0->field_0x34;
            sp30.unk4 = e->field_0x04.unk4 - arg0->field_0x38;
            sp30.unk8 = e->field_0x04.unk8 - arg0->field_0x3C;
            if (func_15144A74(&sp30, &e->field_0x04) < 0.0f) {
                sign = -1.0f;
            } else {
                sign = 1.0f;
            }
            if (sign != e->field_0x28) {
                ret = (e->field_0x2C != -1) ? D_80088A10[e->field_0x2C](arg0) : 0;
            }
        }
    }
    {
        f32 vx = arg0->field_0x40 * arg0->field_0x50;
        f32 vy = arg0->field_0x44 * arg0->field_0x50;
        f32 vz = arg0->field_0x48 * arg0->field_0x50;

        arg0->field_0x34 += vx * D_800BE9A4;
        arg0->field_0x38 += vy * D_800BE9A4;
        arg0->field_0x3C += vz * D_800BE9A4;
    }
    return ret;
}

extern void func_151D5D60();

typedef struct {
    s16 x;
    s16 y;
    s16 z;
    s16 unk6;
    u8 pad8[7];
    u8 unkF;
} Vtx150E63A0;

typedef struct {
    u8 pad0[0x2C];
    f32 unk2C;
    f32 unk30;
    struct17 unk34;
    struct17 unk40;
    u8 pad4C[0x10];
    u8 unk5C;
    u8 pad5D[0x63];
    u8 unkC0[0x40];
    Vtx150E63A0 *unk100[1];
} Struct150E63A0;

Vtx150E63A0 *func_150E63A0(Struct150E63A0 *arg0, s16 arg1) {
    struct17 cur;
    f32 prev[3];
    f32 dx;
    f32 dy;
    f32 dz;
    f32 mx;
    f32 my;
    f32 mz;
    f32 cx;
    f32 cy;
    f32 cz;
    f32 nx;
    f32 ny;
    f32 nz;
    f32 lenSq;
    f32 len;
    f32 k;
    Vtx150E63A0 *vtx;
    Vtx150E63A0 *ret;
    u8 fresh;
    struct17 *cam;

    func_151D5D60(arg0->unk100, arg1, 0x40, &vtx, &fresh);
    ret = vtx;
    if (vtx) {
        if (fresh) {
            memcpy(arg0->unk100[arg1], arg0->unkC0, 0x40);
            memcpy((u8 *)arg0->unk100[arg1] + 0x40, arg0->unkC0, 0x40);
        }
    } else {
        return NULL;
    }
    cur = arg0->unk34;
    cam = (struct17 *)&D_800DBFF0[arg1].unk2F8;
    prev[0] = arg0->unk34.unk0 - arg0->unk40.unk0 * arg0->unk30;
    prev[1] = arg0->unk34.unk4 - arg0->unk40.unk4 * arg0->unk30;
    prev[2] = arg0->unk34.unk8 - arg0->unk40.unk8 * arg0->unk30;
    dx = prev[0] - cur.unk0;
    mx = (dx * 0.5f + cur.unk0) - cam->unk0;
    dy = prev[1] - cur.unk4;
    my = (dy * 0.5f + cur.unk4) - cam->unk4;
    dz = prev[2] - cur.unk8;
    mz = (dz * 0.5f + cur.unk8) - cam->unk8;
    cx = dy * mz - my * dz;
    cy = dz * mx - mz * dx;
    cz = dx * my - mx * dy;
    lenSq = cx * cx + cy * cy + cz * cz;
    if (lenSq == 0.0f) {
        nx = ny = nz = 0.0f;
    } else {
        len = sqrtf(lenSq);
        k = arg0->unk2C / len;
        nx = cx * k;
        ny = cy * k;
        nz = cz * k;
    }
    vtx->x = cur.unk0 - nx;
    vtx->y = cur.unk4 - ny;
    vtx->z = cur.unk8 - nz;
    vtx->unkF = arg0->unk5C;
    vtx->unk6 = 0;
    vtx++;
    vtx->x = prev[0] - nx;
    vtx->y = prev[1] - ny;
    vtx->z = prev[2] - nz;
    vtx->unkF = 0;
    vtx->unk6 = 0;
    vtx++;
    vtx->x = prev[0] + nx;
    vtx->y = prev[1] + ny;
    vtx->z = prev[2] + nz;
    vtx->unkF = 0;
    vtx->unk6 = 0;
    vtx++;
    vtx->x = cur.unk0 + nx;
    vtx->y = cur.unk4 + ny;
    vtx->z = cur.unk8 + nz;
    vtx->unkF = arg0->unk5C;
    vtx->unk6 = 0;
    return ret;
}

s32 func_150E679C(void *arg0) {
    s32 v0 = *(s16 *)((u8 *)arg0 + 0x1C);
    s32 v1;
    if (v0 < 8) {
        v1 = v0 << 5;
        if (v1 < *(u8 *)((u8 *)arg0 + 0x5C)) {
            *(u8 *)((u8 *)arg0 + 0x5C) = v1;
        }
    }
    return 1;
}

struct LocalDef150E67D0 {
    s32 unk0;
    s16 unk4;
    s8  unk6;
    s8  unk7;
    s32 unk8;
    s32 unkC;
    u8  unk10;
    u8  unk11;
    u8  unk12;
    u8  unk13;
    u8  unk14;
    u8  unk15;
    s8  unk16;
    s8  unk17;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    s32 unk24;
    s32 unk28;
    s32 unk2C;
};

s32 func_150E67D0(Struct150EEffectObject *arg0) {
    struct LocalDef150E67D0 tmp;
    Struct150E5FD0Extra *temp;

    tmp.unk6 = 0x3A;
    tmp.unk0 = 1;
    tmp.unk4 = 0x64;
    tmp.unk8 = 0;
    tmp.unkC = 0;
    tmp.unk10 = 0xFF;
    tmp.unk11 = 0xFF;
    tmp.unk12 = 0;
    tmp.unk13 = 0;
    tmp.unk14 = 0;
    tmp.unk15 = 0xFF;
    tmp.unk18 = 0x130001;

    temp = &arg0->field_0x110;
    func_1513C73C((s32)&tmp, 0, 0, (s32)&temp->field_0x14, temp->field_0x04.unk0, temp->field_0x04.unk4, temp->field_0x04.unk8, 50.0f, 50.0f, func_150ADA20() & 0xFF, 0, 0, arg0->field_0x0C, arg0->field_0x01);
    return 0;
}
