#include <ultra64.h>

#include "functions.h"
#include "variables.h"

extern f32 D_800A4A84;
extern f32 D_800A4A88;
extern f32 D_800A4A8C;
extern f32 D_800A4A90;
extern f32 D_800A4A94;
extern f32 sinf(f32);
struct102 *func_1513B5E0(void *, s32, s32, s32, s32);

typedef struct ObjRenderState {
    u8 pad_0[0x10];
    u8 field_0x10;
    u8 pad_0x11;
    s8 field_0x12;
    u8 pad_0x13[0x36];
    u8 field_0x49;
    u8 pad_0x4A[0xA];
    u32 field_0x54;
    u32 field_0x58[2][4];
    Mtx field_0x78[2];
} ObjRenderState;

struct Obj1513BAE8 {
    u8 pad0[0x50];
    s32 unk50;
};


#pragma GLOBAL_ASM("asm/nonmatchings/game_168A90/func_1513B5E0.s")
extern s32 (*D_80089C18[])(struct102 *);
extern s32 (*D_80089C28[])(struct102 *, s16);

#define WGFX168A90(pkt, a, b)       \
{                                   \
    Gfx *_g = (Gfx *)(pkt);         \
    _g->words.w0 = (u32)(a);        \
    _g->words.w1 = (u32)(b);        \
}

void func_1513B798(struct102 *arg0) {
    s32 idx;
    u8 done = 0;

    if (*((u8 *)arg0 + 0x10) & 1) {
        *(s16 *)((u8 *)arg0 + 0x14) -= D_800BE9E4;
        if (*(s16 *)((u8 *)arg0 + 0x14) < 0) {
            done = 1;
        }
    }
    if (!done) {
        idx = *(s8 *)((u8 *)arg0 + 0x11);
        if (idx != -1) {
            if (D_80089C18[idx](arg0) == 0) {
                done = 1;
            }
        }
    }
    if (done) {
        func_1516972C(arg0);
    }
}
Gfx *func_1513B83C(Gfx *arg0, ObjRenderState *arg1, s16 arg2) {
    s32 idx;

    if ((arg1->field_0x10 & 2) && !(arg1->field_0x49 & (1 << arg2))) {
        return arg0;
    }

    idx = arg1->field_0x12;
    if (idx != -1) {
        if (D_80089C28[idx]((struct102 *)arg1, arg2) == 0) {
            return arg0;
        }
    }

    WGFX168A90(arg0++, 0xDA380003, (s32)&arg1->field_0x78[D_800BE9C0]);
    WGFX168A90(arg0++, 0xDB060004, arg1->field_0x58[D_800BE9C0][arg2]);
    WGFX168A90(arg0++, 0xDE000000, arg1->field_0x54);

    return arg0;
}

s32 func_1513B968(s32 arg0, s16 arg1) {
    // FIXME: &arg0->unk_120[D_800BE9C0]
    func_150A7B80(arg0 + 120 + (D_800BE9C0 << 6));
    return 1;
}

void func_1513B9A8(struct132 *arg0) {
    func_100043B4(arg0->unk4C, 4);
    func_15169804(arg0);
}

void func_1513B9DC(struct132 *arg0) {
    func_100043B4(arg0->unk4C, 4);
    func_15169824(arg0);
}

void func_1513BA10(struct132 *arg0) {
    D_80089C44[arg0->unk48]();
}

void func_1513BA44(struct132 *arg0) {
    D_80089C54[arg0->unk48]();
}

void func_15109064(struct132 *, s32, u8);
void func_151BA468(struct132 *, s32, u8);

void func_1513BA78(struct132 *arg0, s32 arg1, u8 arg2) {
    switch (arg0->unk48) {
    case 1:
        func_15109064(arg0, arg1, arg2);
        break;
    case 2:
        func_151BA468(arg0, arg1, arg2);
        break;
    }
}

s32 func_1513BAD4(s32 arg0, s32 arg1) {
    return 0;
}

struct102 *func_1513BAE8(void) {
    struct102 *temp_v0;
    u8 sp38[0x3C];
    f32 sp24[5];

    sp38[1] = 2;
    sp38[2] = 5;
    *(s16 *)&sp38[4] = 0x12C;
    *(s32 *)&sp38[0x30] = 9;
    sp24[0] = 0.0f;
    sp24[1] = 0.0f;
    sp24[3] = 0.0f;
    sp24[4] = 0.0f;
    sp24[2] = 0.0f;
    sp38[0] = 0;
    *(s32 *)&sp38[0x34] = 0x1AE;
    *(s32 *)&sp38[8] = 1;
    *(s32 *)&sp38[0xC] = 0x220205;
    *(s32 *)&sp38[0x10] = 0x40600;
    sp38[0x24] = 0;
    sp38[0x25] = 0;
    *(s32 *)&sp38[0x14] = 1;
    *(s32 *)&sp38[0x18] = 0x36;
    *(s32 *)&sp38[0x1C] = 0x80;
    *(s32 *)&sp38[0x20] = 0x20;
    sp38[0x38] = 3;

    temp_v0 = func_1513B5E0(sp38, 1, 0x14, 0xFF, 1);
    if (temp_v0 != NULL) {
        if (*(s32 *)((u8 *)temp_v0 + 0x50) != 0x1180) {
            func_1516972C(temp_v0);
        } else {
            memcpy((u8 *)temp_v0 + ((struct Obj1513BAE8 *)temp_v0)->unk50 + 0xF8, sp24, 0x14);
        }
    }
    return temp_v0;
}

typedef struct {
    u8 pad0[0x50];
    s32 unk50;
    u8 pad54[4];
    Vtx *unk58[2][4];
} Obj1513BBFC;

typedef struct {
    s32 start;
    s32 count;
} Range1513BBFC;

extern struct17 D_800A49C0[];
extern Range1513BBFC D_800A4A2C[];
extern f32 D_800A4A74;
extern f32 D_800A4A78;
extern f32 D_800A4A7C;
extern f32 D_800A4A80;
extern struct17 *func_15144B34(s32);

s32 func_1513BBFC(Obj1513BBFC *arg0, s16 arg1) {
    f32 *v;
    f32 scaleX;
    f32 scaleY;
    f32 offX;
    f32 offY;
    s32 k;
    struct17 *center;
    f32 dirX;
    f32 dirZ;
    s32 j;

    func_1513B968((s32)arg0, arg1);
    v = (f32 *)((u8 *)arg0 + arg0->unk50 + 0xF8);
    scaleX = sinf(v[3]) * D_800A4A74 + D_800A4A78;
    scaleY = sinf(v[4]) * D_800A4A7C + D_800A4A80;
    center = func_15144B34(arg1);
    offX = v[0] - (s32)(v[0] * (1.0f / 1024.0f)) * 1024.0f;
    offY = v[1] - (s32)(v[1] * (1.0f / 1024.0f)) * 1024.0f;
    for (k = 0; k < 9; k++) {
        f32 dx;
        f32 dz;

        dx = D_800A49C0[k].unk0 - center->unk0;
        dz = D_800A49C0[k].unk8 - center->unk8;
        if (dx != 0.0f || dz != 0.0f) {
            f32 len;

            len = 1.0f / sqrtf(dx * dx + dz * dz);
            dirX = dz * len;
            dirZ = -dx * len;
        } else {
            dirX = 1.0f;
            dirZ = 0.0f;
        }
        for (j = D_800A4A2C[k].start; j < D_800A4A2C[k].start + D_800A4A2C[k].count; j++) {
            Vtx *vtx;
            f32 x;
            f32 y;
            f32 z;
            f32 ex;
            f32 ey;
            f32 ez;

            vtx = &arg0->unk58[D_800BE9C0][arg1][j];
            x = vtx->v.ob[0];
            y = vtx->v.ob[1];
            z = vtx->v.ob[2];
            ex = x - D_800A49C0[k].unk0;
            ey = y - D_800A49C0[k].unk4;
            ez = z - D_800A49C0[k].unk8;
            vtx->v.tc[0] = (ex * dirX + ez * dirZ) * scaleX - offX;
            vtx->v.tc[1] = ey * scaleY - offY;
        }
    }
    return 1;
}

struct Obj1513BEB0 {
    u8 pad0[0x50];
    s32 unk50;
};

s32 func_1513BEB0(struct Obj1513BEB0 *arg0) {
    f32 *v0;

    v0 = (f32 *)((u8 *)arg0 + arg0->unk50 + 0xF8);
    v0[2] = v0[2] + D_800A4A84 * D_800BE9A4;
    v0[2] = func_15144B68(v0[2]);
    v0[0] = v0[0] + D_800A4A88 * D_800BE9A4;
    v0[1] = sinf(v0[2]) * D_800A4A8C;
    v0[3] = v0[3] + D_800A4A90 * D_800BE9A4;
    v0[4] = v0[4] + D_800A4A94 * D_800BE9A4;
    v0[3] = func_15144B68(v0[3]);
    v0[4] = func_15144B68(v0[4]);

    if (4096.0f < v0[0]) {
        do {
            v0[0] = v0[0] - 4096.0f;
        } while (4096.0f < v0[0]);
    }
    if (v0[0] < 0.0f) {
        do {
            v0[0] = v0[0] + 4096.0f;
        } while (v0[0] < 0.0f);
    }
    if (4096.0f < v0[1]) {
        do {
            v0[1] = v0[1] - 4096.0f;
        } while (4096.0f < v0[1]);
    }
    if (v0[1] < 0.0f) {
        do {
            v0[1] = v0[1] + 4096.0f;
        } while (v0[1] < 0.0f);
    }
    return 1;
}
