#include <ultra64.h>
#include "functions.h"
#include "variables.h"


/* Particle descriptor passed to func_15130280 (0x70 bytes). */
typedef struct {
    s32 unk0;
    s32 unk4;
    s16 unk8;
    s16 unkA;
    s32 unkC;
    s32 unk10;
    u8 unk14;
    u8 unk15;
    u8 unk16;
    u8 unk17;
    u8 unk18;
    u8 unk19;
    u8 unk1A;
    u8 unk1B;
    u8 unk1C;
    u8 unk1D;
    s16 unk1E;
    s16 unk20;
    s16 unk22;
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    struct17 pos;
    struct17 unk3C;
    struct17 vel;
    f32 unk54;
    u32 unk58;
    s32 unk5C;
    u8 unk60;
    u8 unk61;
    s8 unk62;
    s8 unk63;
    s8 unk64;
    u8 unk65;
    u8 unk66;
    u8 pad67;
    s16 unk68;
    u8 pad6A[2];
    f32 unk6C;
} Struct151082D0Particle; /* 0x70 */

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
} Struct151082D0Sub;

typedef struct {
    f32 accum;
    s16 *unk4;
    u8 unk8;
} Struct151082D0Data;

typedef struct {
    u8 pad0;
    u8 unk1;
    u8 pad2[0xA];
    u8 unkC;
    u8 padD[0x1B];
    Struct151082D0Data data;
} Struct151082D0;

extern void *func_15130280(void *, u8, s32, s32, u8, s32);
extern void func_1514373C(f32 arg0, f32 arg1, f32 *arg2, f32 *arg3);

void func_151082D0(Struct151082D0 *arg0) {
    Struct151082D0Data *data;

    data = &arg0->data;
    data->accum += (0.030000001f + func_150ADA68() * 0.010000001f) * D_800BE9A4;
    if (data->accum > 1.0f) {
        if (data->unk8 & 1) {
            Struct151082D0Particle spawn;
            Struct151082D0Sub sub;
            void *ret;

            spawn.unk1D = 0x74;
            spawn.unk8 = 0x5310;
            spawn.unk0 = 0x200005;
            spawn.unk4 = 0x9F0600;
            spawn.unk14 = 0xFF;
            spawn.unk15 = 0xFF;
            spawn.unk16 = 0xFF;
            spawn.unk17 = 0xFF;
            spawn.unkC = 0;
            spawn.unk10 = 0;
            spawn.unk1C = 0xFF;
            spawn.unk1E = 1;
            spawn.unk3C.unk0 = 0.0f;
            spawn.unk3C.unk4 = 0.0f;
            spawn.unk3C.unk8 = 0.0f;
            spawn.vel.unk0 = 0.0f;
            spawn.vel.unk4 = 0.0f;
            spawn.vel.unk8 = 0.0f;
            spawn.unk54 = 0.0f;
            spawn.unk20 = 0xFF;
            spawn.unk22 = 1;
            spawn.unk24 = 1.0f;
            spawn.unk60 = 6;
            spawn.unk61 = 6;
            spawn.unk62 = 0x18;
            spawn.unk63 = -1;
            spawn.unk64 = -1;
            spawn.unk65 = 0;
            spawn.unk5C = 0;
            spawn.unkA = 300;
            spawn.unk18 = 0xFF;
            spawn.unk19 = 0xFF;
            spawn.unk1A = 0xFF;
            sub.unk10 = 0.0f;
            do {
                sub.unk0 = sub.unk4 = func_150ADA68() * 20.0f + 30.0f;
                sub.unk8 = sub.unk0 * 0.15f;
                sub.unkC = sub.unk8 * 0.5f;
                spawn.unk28 = func_150ADA68() * 500.0f + 600.0f;
                spawn.unk2C = spawn.unk28 * 0.5f;
                func_1514373C(func_150ADA68() * 3.1415927f * 2.0f, data->unk4[3], &spawn.pos.unk0, &spawn.pos.unk8);
                spawn.pos.unk0 += data->unk4[0];
                spawn.pos.unk8 += data->unk4[2];
                spawn.pos.unk4 = data->unk4[1] + data->unk4[4] * func_150ADA68();
                spawn.unk58 = ((func_150ADA20() & 1) ? 0x40 : 0) | 0x8000 | 0x4000;
                spawn.unk1B = (func_150ADA20() & 0x7F) + 0x80;
                ret = func_15130280(&spawn, 2, 0, 0x14, arg0->unkC, arg0->unk1);
                if (ret != NULL) {
                    memcpy((u8 *)ret + 0xA8, &sub, sizeof(sub));
                }
                data->accum -= 1.0f;
            } while (data->accum > 1.0f);
        } else {
            do {
                data->accum -= 1.0f;
            } while (data->accum > 1.0f);
        }
    }
}

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
} Struct15108658Sub;

typedef struct {
    u8 pad0[0x1C];
    s32 unk1C;
    u8 pad20[0x54];
    s8 unk74;
    u8 pad75[0x33];
    Struct15108658Sub unkA8;
} Struct15108658;
s32 func_15108658(Struct15108658 *arg0, s32 arg1) {
    Struct15108658Sub *s = &arg0->unkA8;
    f32 diff = s->unk4 - s->unk0;

    if (s->unk0 < s->unkC || diff < s->unkC) {
        arg0->unk1C = 0;
    } else if (s->unk0 < s->unk8 || diff < s->unk8) {
        arg0->unk1C = 0x10000;
    } else {
        arg0->unk1C = 0x20000;
    }
    if (s->unk10) {
        f32 rem = 11.0f - s->unk10;

        if (s->unk10 < 1.5730001f || rem < 1.5730001f) {
            arg0->unk1C = 0;
            arg0->unk74 = -1;
        } else {
            arg0->unk74 = 3;
        }
        s->unk10 -= D_800BE9A4;
        if (s->unk10 < 0.0f) {
            s->unk10 = 0.0f;
            arg0->unk74 = -1;
        }
    } else {
        s->unk0 -= D_800BE9A4;
        if (s->unk0 < 0.0f) {
            return 0;
        }
        if (arg0->unk1C == 0x20000 && func_150ADA68() < 0.051000003f) {
            s->unk10 = 11.0f;
        }
    }
    return 1;
}

struct SubFC {
    u8 pad[8];
    u8 flag;
};

struct ObjFC {
    u8 pad[0x28];
    struct SubFC sub;
};

void func_151087FC(struct ObjFC *arg0, s32 arg1, u8 arg2) {
    struct SubFC *p = &arg0->sub;
    if (arg2 == 0x2B) {
        p->flag |= 0x1;
    } else if (arg2 == 0x2C) {
        p->flag &= 0xFFFE;
    }
}
