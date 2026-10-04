#include <ultra64.h>
#define func_150ADA20 func_150ADA20_u8_decl_in_functions_h
#define func_10010F88 func_10010F88_void_decl_in_functions_h
#include "functions.h"
#undef func_150ADA20
#undef func_10010F88
u32 func_150ADA20(void);
s32 func_10010F88(s32 arg0, u16 arg1, s16 arg2, u8 arg3, s32 arg4, s16 arg5, s16 arg6, s16 arg7, s16 arg8, s16 arg9);
#include "variables.h"

struct sub150F4 {
    f32 unk0;
    struct17 unk4;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    u8 unk24;
    u8 pad25[3];
};

typedef struct {
    u8 pad0[0x20];
    f32 unk20;
    f32 unk24;
    f32 unk28;
    u8 pad2C[0xC];
    struct17 unk38;
    f32 unk44;
    f32 unk48;
    f32 unk4C;
    f32 unk50;
    f32 unk54;
    f32 unk58;
    u8 pad5C[0x14];
    u8 unk70;
    u8 unk71;
    u8 pad72[0x16];
    u32 unk88;
    u8 pad8C[0xE4];
    struct sub150F4 unk170;
} Actor150F4;

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
    f32 unk24;
    struct17 unk28;
    struct17 unk34;
    struct17 unk40;
    f32 unk4C;
    s32 unk50;
    s16 unk54;
    s16 unk56;
    u8 unk58;
    u8 pad59[3];
    s32 unk5C;
    u8 unk60;
    u8 unk61;
    u8 unk62;
    u8 unk63;
    u8 unk64;
    u8 unk65;
    u8 unk66;
    u8 unk67;
    u8 unk68;
    s8 unk69;
    u8 unk6A;
    u8 pad6B;
    s32 unk6C;
    u8 unk70;
    u8 pad71;
    s16 unk72;
    s16 unk74;
    u8 pad76[2];
    s32 unk78;
} Spawn150F4;

const s16 D_800A19F0[] = { 9, 10, 11 };
const f32 D_800A19F8[] = { 1.0f, 1.0f, 1.0f };
const s16 D_800A1A04[] = { 6, 7, 8, 0x23, 0x24, 0x25, 0x2D, 0x2E, 0x52, 0xA8, 0xA9, 0xAA, 0xAB, 0xBE, 0xBF, 0x95 };
const f32 D_800A1A24[] = { 0.2f, 0.1f, 0.1f, 0.025f, 0.025f, 0.08f, 0.2f, 0.2f, 0.1f, 0.25f, 0.25f, 0.25f, 0.25f, 0.25f, 0.35f, 0.2f };

extern s32 func_15145128(struct17 *, struct17 *, f32 *, f32 *);
extern s32 func_1513264C(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, u8 arg5, s32 arg6);
extern void func_1514373C(f32 arg0, f32 arg1, f32 *arg2, f32 *arg3);
extern struct17 *func_15144B34(s32);
extern f32 func_15143E64(struct17 *);

void func_150F4570(struct17 *arg0, struct17 *arg1, u8 arg2, f32 arg3, f32 arg4, f32 arg5, u8 arg6, s32 arg7, u8 arg8, s32 arg9) {
    Spawn150F4 spawn;
    struct17 dir;
    struct17 diff;
    f32 len;
    f32 inv;
    struct sub150F4 extra;
    s32 ret;

    diff.unk0 = arg1->unk0 - arg0->unk0;
    diff.unk4 = arg1->unk4 - arg0->unk4;
    diff.unk8 = arg1->unk8 - arg0->unk8;
    if (func_15145128(&diff, &dir, &len, &inv) != 0) {
        extra.unk24 = (arg6 ? 1 : 0) | (arg7 ? 2 : 0);
        extra.unk0 = len * arg4;
        extra.unk4 = *arg0;
        extra.unk10 = func_150ADA68() * 6.2831855f;
        extra.unk14 = func_150ADA68() * 0.2f + 0.08000000566f;
        if (func_150ADA20() & 1) {
            extra.unk14 = -extra.unk14;
        }
        extra.unk20 = func_150ADA68() * 21.0f + 13.0f;
        {
            f32 angle = func_150ADA68() * 6.2831855f;
            extra.unk18 = cosf(angle);
            extra.unk1C = sinf(angle);
        }
        spawn.unk00 = 1.0f;
        spawn.unk04 = 1.0f;
        spawn.unk08 = spawn.unk0C = arg5;
        spawn.unk10 = func_150ADA68() * 360.0f;
        spawn.unk14 = func_150ADA68() * 360.0f;
        spawn.unk18 = func_150ADA68() * 360.0f;
        spawn.unk1C = 1.0f;
        spawn.unk20 = 1.0f;
        spawn.unk24 = 1.0f;
        spawn.unk28 = *arg0;
        spawn.unk34.unk0 = dir.unk0 * arg3;
        spawn.unk34.unk4 = dir.unk4 * arg3;
        spawn.unk34.unk8 = dir.unk8 * arg3;
        spawn.unk40.unk0 = func_150ADA68() * 21.90300179f + -10.95150089f;
        spawn.unk40.unk4 = 0.0f;
        spawn.unk40.unk8 = func_150ADA68() * 21.90300179f + -10.95150089f;
        spawn.unk4C = 0.0f;
        spawn.unk50 = 0x14900;
        spawn.unk54 = 0x12C;
        spawn.unk56 = arg2;
        spawn.unk58 = 8;
        spawn.unk5C = 0;
        spawn.unk60 = 0xFF;
        spawn.unk61 = 0x16;
        spawn.unk62 = 7;
        spawn.unk63 = 0;
        spawn.unk64 = 0;
        spawn.unk65 = 0;
        spawn.unk66 = 0;
        spawn.unk67 = 0;
        spawn.unk68 = 2;
        spawn.unk69 = -1;
        spawn.unk6A = 2;
        spawn.unk6C = 0;
        spawn.unk70 = 0;
        spawn.unk72 = 1;
        spawn.unk74 = 0xFF;
        spawn.unk78 = arg7;
        ret = func_1513264C(&spawn, 3, 0xFF, 0, 0x28, arg8, arg9);
        if (ret != 0) {
            memcpy((void *)(ret + 0x170), &extra, sizeof(extra));
        }
    }
}

s32 func_150F48D0(Actor150F4 *arg0) {
    struct sub150F4 *p;

    p = &arg0->unk170;
    p->unk0 -= D_800BE9A4;
    if (p->unk0 <= 0.0f) {
        return 0;
    }
    {
    f32 h;
    f32 r;
    func_1514373C(p->unk10, p->unk20, &r, &h);
    p->unk10 += p->unk14 * D_800BE9A4;
    p->unk4.unk0 += arg0->unk44 * D_800BE9A4;
    p->unk4.unk4 += arg0->unk48 * D_800BE9A4;
    p->unk4.unk8 += arg0->unk4C * D_800BE9A4;
    arg0->unk38.unk0 = p->unk4.unk0 + r * p->unk18;
    arg0->unk38.unk4 = p->unk4.unk4 + h;
    arg0->unk38.unk8 = p->unk4.unk8 - r * p->unk1C;
    }
    arg0->unk20 += arg0->unk50 * D_800BE9A4;
    arg0->unk24 += arg0->unk54 * D_800BE9A4;
    arg0->unk28 += arg0->unk58 * D_800BE9A4;
}

s32 func_150F4A38(Actor150F4 *arg0) {
    struct sub150F4 *p;
    f32 dist;

    p = &arg0->unk170;
    if ((p->unk24 & 1) || (p->unk24 & 2)) {
        struct17 *pos;
        struct17 diff;

        pos = func_15144B34(0);
        diff.unk0 = arg0->unk38.unk0 - pos->unk0;
        diff.unk4 = arg0->unk38.unk4 - pos->unk4;
        diff.unk8 = arg0->unk38.unk8 - pos->unk8;
        dist = func_15143E64(&diff);
    }
    if (p->unk24 & 1) {
        if (dist < 500.0f) {
            arg0->unk70 = 0;
        } else if (dist < 1200.0f) {
            arg0->unk70 = (dist - 500.0f) * 0.00142857142857142857 * 255.0;
        } else {
            arg0->unk70 = 0xFF;
        }
    }
    if ((p->unk24 & 2) && !(p->unk24 & 4)) {
        if (arg0->unk88 >> 16) {
            func_1000F9D4(arg0->unk88 >> 16, arg0->unk38.unk0, arg0->unk38.unk4, arg0->unk38.unk8);
        } else if (dist < 200.0f) {
            arg0->unk88 |= func_10010F88(arg0->unk88 & 0xFFFF, (func_150ADA20() & 0x3FFF) + 0x4000, 0, 0, -1,
                                         arg0->unk38.unk0, arg0->unk38.unk4, arg0->unk38.unk8, 10000, 20000) << 16;
        }
    }
    return 1;
}


void func_150F4CFC(struct102 *arg0, s32 arg1, u8 arg2) {
    struct sub150F4 *p;
    p = (struct sub150F4 *)((u8 *)arg0 + 0x170);
    if (arg2 == 0x4E) {
        ((u8 *)arg0)[0x71] = 0;
        p->unk24 |= 0x5;
    } else if (arg2 == 0x4F) {
        func_1516972C(arg0);
    }
}

void func_150F4D5C(void *arg0, s8 arg1, u8 arg2, u8 arg3, s32 arg4) {
    struct {
        void *unk0;
        f32 unk4;
        u8 unk8;
        u8 unk9;
        u8 padA;
        u8 padB;
    } sp34;
    struct260 *temp_v0;

    sp34.unk0 = arg0;
    sp34.unk4 = 0.0f;
    sp34.unk8 = arg1;
    sp34.unk9 = arg2;

    temp_v0 = func_15149130(0x12C, -1, 0x56, -1, 0, 0, (struct37 *)0xC, arg3, arg4);
    if (temp_v0 != NULL) {
        memcpy((void *)((s32)temp_v0 + 0x28), &sp34, 0xC);
    }
}

typedef struct {
    u8 count;
    s16 *ids;
    f32 *scales;
} Rec150F4;

typedef struct {
    u8 pad0[0x23D];
    u8 unk23D;
    u8 pad23E[0x142];
    f32 unk380;
} Obj150F4;

typedef struct {
    Obj150F4 *unk0;
    f32 unk4;
    s8 unk8;
    u8 unk9;
} Emit150F4;

typedef struct {
    u8 pad0;
    u8 unk1;
    u8 pad2[0xA];
    u8 unkC;
    u8 padD[0x1B];
    Emit150F4 unk28;
} Emitter150F4;

extern Rec150F4 D_80088B20[];
extern s32 (*D_80088B38[])();
extern void func_15143874(s16, f32, f32 *, f32 *);

void func_150F4DEC(Emitter150F4 *arg0) {
    Emit150F4 *e;
    struct17 *pos;
    s32 angle;
    struct17 a;
    struct17 b;
    Rec150F4 *rec;
    u8 i;
    f32 speed;

    e = &arg0->unk28;
    if (e->unk8 != -1) {
        if (!D_80088B38[e->unk8]()) {
            return;
        }
    }
    e->unk4 += (0.05100000277f + func_150ADA68() * 0.153000012f) * D_800BE9A4;
    if (1.0f < e->unk4) {
        pos = func_15144B34(e->unk0->unk23D);
        angle = (e->unk0->unk380 + 180.0f) * 0.7111111283f;
        do {
            func_15143874(angle + 0x15, func_150ADA68() * 381.0f + 254.0f, &a.unk0, &a.unk8);
            a.unk4 = func_150ADA68() * 212.0f + -133.0f;
            a.unk0 += pos->unk0;
            a.unk4 += pos->unk4;
            a.unk8 += pos->unk8;
            func_15143874(angle - 0x15, func_150ADA68() * 381.0f + 254.0f, &b.unk0, &b.unk8);
            b.unk4 = func_150ADA68() * 212.0f + -133.0f;
            b.unk0 += pos->unk0;
            b.unk4 += pos->unk4;
            b.unk8 += pos->unk8;
            if (func_150ADA20() & 1) {
                struct17 tmp;

                tmp = a;
                a = b;
                b = tmp;
            }
            rec = &D_80088B20[e->unk9];
            i = func_150ADA20() % rec->count;
            speed = func_150ADA68() * 10.0f + 5.0f;
            func_150F4570(&a, &b, rec->ids[i], speed, 1.0f / speed,
                          rec->scales[i] * (func_150ADA68() * 0.07500000298f + 0.07500000298f), 0, 0, arg0->unkC,
                          arg0->unk1);
            e->unk4 -= 1.0f;
        } while (1.0f < e->unk4);
    }
}
