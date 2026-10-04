#include <ultra64.h>
#include "functions.h"
#include "variables.h"

typedef struct {
    /* 0x0 */ f32 x;
    /* 0x4 */ f32 y;
    /* 0x8 */ f32 z;
} Vec3F150C04C0;

typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ Vec3F150C04C0 unk08;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ s16 unk24;
    /* 0x26 */ s16 unk26;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ void *unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ f32 unk40;
    /* 0x44 */ f32 unk44;
    /* 0x48 */ void *unk48;
    /* 0x4C */ void *unk4C;
    /* 0x50 */ s32 unk50;
    /* 0x54 */ f32 unk54;
    /* 0x58 */ u8 unk58;
    /* 0x59 */ u8 unk59;
    /* 0x5A */ u8 pad5A[2];
    /* 0x5C */ s32 unk5C;
    /* 0x60 */ void *unk60;
} Struct150C04C0;

typedef struct {
    /* 0x0 */ s16 unk0;
    /* 0x2 */ s16 unk2;
    /* 0x4 */ s16 unk4;
    /* 0x6 */ s16 unk6;
} Struct150C04C0Color;

extern void func_15150400(Struct150C04C0 *, Struct150C04C0Color *, u8, s32);

typedef struct {
    char pad_0[0x14];
    s16 field_0x14;
    s16 field_0x16;
    char pad_0x18[0x7];
    u8 field_0x1F;
    char pad_0x20[0x4];
    u8 field_0x24;
    char pad_0x25[0x1];
    u8 field_0x26;
    u8 field_0x27;
    char pad_0x28[0x4];
    u8 field_0x2C;
    s8 field_0x2D;
    s8 field_0x2E;
    u8 field_0x2F;
} Struct150BF0F4;

typedef struct {
    s16 unk0;
    s16 unk2;
    u8 unk4;
    u8 pad5;
    u16 unk6;
    s32 unk8;
    s32 unkC;
    s16 unk10;
    s16 unk12;
    s32 unk14;
    s32 unk18;
    u8 unk1C;
    u8 unk1D;
    u8 unk1E;
    u8 unk1F;
    u8 unk20;
    u8 unk21;
    u8 unk22;
    u8 unk23;
    u8 unk24;
    u8 unk25;
    s16 unk26;
    s16 unk28;
    s16 unk2A;
    f32 unk2C;
    f32 unk30;
    f32 unk34;
    struct17 unk38;
    s16 unk44;
    s16 unk46;
    s16 unk48;
    s16 unk4A;
    f32 unk4C;
    f32 unk50;
    f32 unk54;
    f32 unk58;
    s32 unk5C;
    s8 unk60;
    s8 unk61;
    u8 unk62;
    u8 unk63;
    u8 unk64;
    u8 pad65[3];
    f32 unk68;
} Arg15153634;

extern void func_15153634(Arg15153634 *, s32, u8, s32);
extern void func_15136C3C(struct127 *, s32, s32, s32, s32, s32, s32, s32);

typedef struct {
    s32 unk00;
    s32 unk04;
    struct17 unk08;
    s16 unk14;
    s16 unk16;
    s16 unk18;
    s16 unk1A;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
    s16 unk2C;
    s16 unk2E;
    f32 unk30;
    f32 unk34;
    f32 unk38;
} Arg15152190;

typedef struct {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 unk1;
    /* 0x02 */ u8 pad2[0xA];
    /* 0x0C */ u8 unkC;
    /* 0x0D */ u8 padD[0x2B];
    /* 0x38 */ f32 unk38;
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ f32 unk40;
} Struct150C01DC;

extern void func_15152190(Arg15152190 *, const s32 *, const f32 *, s32, f32, s32, u8, s32);

typedef struct {
    /* 0x000 */ u8 pad0[0x73];
    /* 0x073 */ u8 unk73;
    /* 0x074 */ u8 pad74[0x34];
    /* 0x0A8 */ f32 unkA8;
    /* 0x0AC */ u8 padAC[0x78];
    /* 0x124 */ s32 unk124;
} Struct150BF760;

typedef struct {
    /* 0x00 */ u8 pad0[0x2];
    /* 0x02 */ u8 unk2;
    /* 0x03 */ u8 pad3[0x2D];
} SpawnSlot150BF760;

extern u8 D_800C35E8;
extern void func_1511B51C(Struct150BF760 *);
extern s32 func_15195FB0(Struct150BF760 *, s32, s32, s32, s32, s32, s32);
extern s32 func_150825C0(s32, s32);
extern f32 sinf(f32);

typedef struct {
    /* 0x000 */ u8 unk0;
    /* 0x001 */ u8 unk1;
    /* 0x002 */ u8 pad2[0xA];
    /* 0x00C */ u8 unkC;
    /* 0x00D */ u8 padD[0xB];
    /* 0x018 */ f32 unk18;
    /* 0x01C */ u8 pad1C[0x1C];
    /* 0x038 */ f32 unk38;
    /* 0x03C */ f32 unk3C;
    /* 0x040 */ f32 unk40;
    /* 0x044 */ u8 pad44[0x1C];
    /* 0x060 */ s32 unk60;
    /* 0x064 */ u8 pad64[0x2];
    /* 0x066 */ u16 unk66;
    /* 0x068 */ u8 pad68[0xA8];
    /* 0x110 */ u8 unk110[0x60];
    /* 0x170 */ f32 unk170;
} Struct150C0648;

extern f32 func_150ADA68(void);
extern s32 func_15133B98(Struct150C0648 *, s32, s32, s32, f32, s32);

typedef struct {
    /* 0x000 */ f32 x;
    /* 0x004 */ f32 y;
    /* 0x008 */ f32 z;
    /* 0x00C */ u8 padC[0x4];
    /* 0x010 */ s16 rx;
    /* 0x012 */ s16 ry;
    /* 0x014 */ s16 rz;
    /* 0x016 */ u16 count;
    /* 0x018 */ u8 pad18[0x8];
    /* 0x020 */ s16 *dst[2];
    /* 0x028 */ s16 *src;
    /* 0x02C */ f32 sx;
    /* 0x030 */ f32 sy;
    /* 0x034 */ f32 sz;
    /* 0x038 */ u8 pad38[0x4];
    /* 0x03C */ s32 unk3C;
    /* 0x040 */ u8 pad40[0x33];
    /* 0x073 */ u8 unk73;
    /* 0x074 */ u16 unk74;
    /* 0x076 */ u8 pad76[0x6];
    /* 0x07C */ f32 unk7C;
    /* 0x080 */ f32 unk80;
    /* 0x084 */ f32 unk84;
    /* 0x088 */ u8 pad88[0x54];
    /* 0x0DC */ s32 unkDC;
    /* 0x0E0 */ u8 padE0[0x44];
    /* 0x124 */ f32 unk124;
} Struct150BF21C;

extern f32 cosf(f32);
extern void func_15114D24(Struct150BF21C *, s32, s32, s16, s16, s32);
extern void func_15114F04(Struct150BF21C *, s32, s32);
extern void func_150A7DA0(f32 [4][4], f32, f32, f32);
extern void func_15043F6C(f32 [4][4], f32, f32, f32, f32, f32, f32, f32, f32, f32);
extern void func_150A7A48(f32 [4][4], f32 [4][4], f32 [4][4]);
extern void func_150A7960(f32 [4][4], f32, f32, f32, f32 *, f32 *, f32 *);


void func_150BEF70(s32 arg0) {
}

extern void func_1516D99C();

void func_150BEF7C(s32 arg0) {
    s32 i;
    s32 pos;
    s32 v;
    v = arg0 & 0xFFFF;
    pos = 0x17C;
    for (i = 0; i != 2; i++) {
        func_1516D99C(0x1FDB, 0x25, (s16)pos, 0xD,
            0, 0x50, 0x8F, 0, 0, 0, 0, 0,
            8, 0xC8, 0xA, 0, 0, 0, 0, 0,
            0x28, 0x28, 4, 0, 0, 0, 0, 0x555,
            0x555, 0x555, 0x555, v, 0x32, 0, 0xFF, 0x14,
            0xFA0, 0x7D0, 1, 6, 0, 1, 0, 0,
            0, 0, 3, 0xFF, 0);
        pos = -pos;
    }
}

s32 func_150BF0F4(Struct150BF0F4 *arg0) {
    s32 temp_v0;
    s32 temp_v1;
    s32 temp_a1;

    temp_v0 = arg0->field_0x1F;
    temp_v1 = arg0->field_0x26;
    temp_a1 = arg0->field_0x24;
    if (temp_a1 != 0) {
        if (temp_v0 != temp_v1) {
            temp_v0 += D_800BE9E4 * arg0->field_0x27;
            if (temp_v1 < temp_v0) {
                temp_v0 = temp_v1;
            }
            arg0->field_0x1F = temp_v0;
            temp_a1 = ((volatile Struct150BF0F4 *)arg0)->field_0x24;
        }
    } else {
        if (temp_v0 != 0) {
            temp_v0 -= D_800BE9E4 * arg0->field_0x2F;
            if (temp_v0 < 0) {
                temp_v0 = 0;
            }
            arg0->field_0x1F = temp_v0;
            temp_a1 = ((volatile Struct150BF0F4 *)arg0)->field_0x24;
        }
    }

    if ((temp_a1 == 0) && (temp_v0 == 0)) {
        return 1;
    }

    temp_v0 = arg0->field_0x2D;
    temp_v0 *= D_800BE9E4;
    arg0->field_0x14 = arg0->field_0x14 + temp_v0;
    temp_v1 = arg0->field_0x14;
    temp_v0 = arg0->field_0x2E;
    temp_v0 *= D_800BE9E4;
    arg0->field_0x16 = arg0->field_0x16 + temp_v0;
    if ((temp_v1 <= 0) || (temp_v1 <= 0)) {
        arg0->field_0x16 = 0;
        arg0->field_0x14 = arg0->field_0x16;
        return 1;
    }

    temp_v1 = arg0->field_0x2C;
    temp_v1 += D_800BE9E4;
    if (temp_v1 >= 0x80) {
        temp_v1 = 0x7F;
    }
    arg0->field_0x2C = temp_v1;
    return 0;
}

void func_150BF21C(Struct150BF21C *arg0) {
    s16 *dst;
    s16 *src;
    f32 diff;
    f32 x;
    f32 y;
    f32 z;
    f32 spd;
    s32 paused;
    f32 amp;
    f32 mtx[4][4];
    f32 mtx2[4][4];
    f32 factor;
    s32 i;
    f32 amp3;

    y = arg0->unk7C;
    amp = 0.0f;
    factor = 0.05f;
    if (D_800C35EA == 0) {
        paused = 0;
    } else if (D_800C35E8 == 1) {
        paused = 0;
    } else {
        paused = 1;
    }
    if (D_800BE9B4 != 0) {
        y = arg0->unk3C;
        arg0->unk7C = y;
    }
    if (!paused) {
        diff = arg0->unk3C - y;
        if (diff == 0.0f) {
            arg0->unk84 = 0.0f;
            arg0->unk80 += 0.05f;
            amp = ((y / 1500.0f) + 1.0f) * D_800BE9A4;
            if (amp < 0.0f) {
                amp = 0.0f;
            }
            func_15114D24(arg0, -1, 0x7D00, 0x1F4, 0x7D0, 0);
        } else {
            factor = 0.2f;
            arg0->unk80 = 0.0f;
            spd = arg0->unk84;
            if (diff < 0.0f) {
                if (-60.0f < spd) {
                    spd -= 5.0f;
                }
            } else {
                if (spd < 6.0f) {
                    spd += 0.5f;
                }
                func_15114D24(arg0, 0xB9, 0x7D00, 0x1F4, 0x7D0, 1);
            }
            arg0->unk84 = spd;
            if (fabsf(spd) < fabsf(diff)) {
                y += spd * D_800BE9A4;
                if (spd < -25.0f) {
                    arg0->unk124 = -10.0f;
                } else {
                    arg0->unk124 = spd * 0.4000000060f;
                }
                arg0->unkDC = 0x7D00;
                arg0->unk73 &= ~3;
                arg0->unk73 |= 2;
                if (arg0->unk74 == 0) {
                    func_15114D24(arg0, 0xB9, 0x3E80, 0x3E8, 0xFA0, 0);
                }
                func_15114F04(arg0, 0x3E80, spd * 500.0f);
            } else {
                y = arg0->unk3C;
                if (spd < 0.0f) {
                    arg0->unkDC = 0x80;
                }
                arg0->unk73 &= ~3;
                arg0->unk73 |= 3;
                arg0->unk124 = 0.0f;
                func_15114D24(arg0, -1, 0, 0, 0, 0);
            }
            arg0->unk7C = y;
            arg0->unk84 = spd;
        }
        amp3 = amp * 3.0f;
        arg0->x += ((amp3 * sinf(arg0->unk80)) - arg0->x) * factor;
        arg0->y += (((amp * 4.0f) * sinf(arg0->unk80 * 1.100000024f)) - arg0->y) * factor;
        arg0->z += ((amp3 * cosf(arg0->unk80)) - arg0->z) * factor;
    } else {
        y = 0.0f;
    }
    func_150A7DA0(mtx, 0.0f, y, 0.0f);
    func_15043F6C(mtx2, arg0->x, arg0->y, arg0->z, arg0->sx, arg0->sy, arg0->sz, arg0->rx, arg0->ry, arg0->rz);
    func_150A7A48(mtx, mtx2, mtx);
    dst = arg0->dst[D_800BE9C0];
    src = arg0->src;
    for (i = 0; i < arg0->count; i++) {
        func_150A7960(mtx, src[0], src[1], src[2], &x, &y, &z);
        dst[0] = x;
        dst[1] = y;
        dst[2] = z;
        src += 8;
        dst += 8;
    }
}

void func_150BF760(Struct150BF760 *arg0) {
    struct127 *obj;
    s32 mode;
    s32 id;
    struct197 *anim;
    f32 ratio;

    ratio = 0.0f;
    if ((D_800C35EA == 1) && (D_800C35E8 != 1)) {
        return;
    }
    func_1511B51C(arg0);
    if (arg0->unk124 == 0) {
        arg0->unk124 = func_15195FB0(arg0, D_800902B8, 1, -1, 0, 0, -8);
    }
    obj = func_15083E90(0x14);
    mode = arg0->unk73 & 3;
    if (obj != NULL) {
        anim = obj->unk2D0;
        ratio = anim->unk8 / (anim->unk18 - 2.0f);
    }
    arg0->unkA8 = 0.0f;
    if (mode == 2) {
        if (ratio <= 0.75f) {
            arg0->unkA8 = -sinf(ratio * 3.141592741f * 1.333333254f) * 10.0f;
        }
        if (obj == NULL) {
            id = func_15083E0C(0x14);
            ((SpawnSlot150BF760 *)D_800D20FC)[id].unk2 = 0;
            func_150825C0(id, 0);
            obj = func_15083E90(0x14);
        }
        if (obj->unk232 != 2) {
            obj->unk232 = 2;
            obj->unk218 = 0;
        }
    } else if (mode == 3) {
        if ((obj != NULL) && (1.0f <= ratio)) {
            func_15060F28(obj, 0);
        }
    } else if (mode == 0) {
        if (0.25f <= ratio) {
            arg0->unkA8 = sinf(ratio * 4.188789368f - 4.188789368f) * 10.0f;
        }
        if ((obj != NULL) && (1.0f <= ratio)) {
            func_15060F28(obj, 0);
        }
    } else if (mode == 1) {
        if (0.25f <= ratio) {
            arg0->unkA8 = sinf(ratio * 4.188789368f - 4.188789368f) * 10.0f;
        }
        if (obj == NULL) {
            id = func_15083E0C(0x14);
            ((SpawnSlot150BF760 *)D_800D20FC)[id].unk2 = 0;
            func_150825C0(id, 0);
            obj = func_15083E90(0x14);
        }
        /* BUG (original game): reads obj->unk232 only when obj IS NULL (golden: bnel a0,zero) */
        if (obj == NULL) {
            if (obj->unk232 != 3) {
                obj->unk232 = 3;
                obj->unk218 = 0;
            }
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_EC420/func_150BFA7C.s")

void func_150BFFE0(struct127 *arg0) {
    struct17 pos;
    Arg15153634 a;

    pos.unk0 = arg0->x_position;
    pos.unk4 = arg0->unk180 + 70.0f;
    pos.unk8 = arg0->z_position;
    func_15136C3C(arg0, 0, 0, 1, 0, 0, 0xFF, 1);
    a.unk0 = 0x11;
    a.unk2 = 7;
    a.unk4 = 0x6C;
    a.unk6 = 0x5103;
    a.unk8 = 0x200005;
    a.unkC = 0;
    a.unk10 = 0x28;
    a.unk12 = 0x14;
    a.unk14 = 0;
    a.unk18 = 0;
    a.unk1F = 0xFF;
    a.unk1C = 0x4E;
    a.unk1D = 0x54;
    a.unk1E = 0x7B;
    a.unk20 = 0xA4;
    a.unk21 = 0xA1;
    a.unk22 = 0xC8;
    a.unk23 = 0x9B;
    a.unk24 = 0x64;
    a.unk25 = 0xFF;
    a.unk26 = 0x1E;
    a.unk28 = 8;
    a.unk2A = 0x1E;
    a.unk2C = 1.019999981f;
    a.unk30 = 451.0f;
    a.unk34 = 501.0f;
    a.unk38.unk0 = pos.unk0;
    a.unk38.unk4 = pos.unk4 + 35.0f;
    a.unk38.unk8 = pos.unk8;
    a.unk44 = 0;
    a.unk46 = -0x14;
    a.unk48 = 0xFF;
    a.unk4A = 0x1E;
    a.unk4C = 15.0f;
    a.unk50 = 39.0f;
    a.unk54 = 0.3540000021f;
    a.unk58 = 0.6260000467f;
    a.unk5C = 0x40040E07;
    a.unk60 = 0x10;
    a.unk61 = -1;
    a.unk62 = 8;
    a.unk63 = 6;
    a.unk64 = 1;
    a.unk68 = 0.8775510192f;
    func_15153634(&a, 0xFF, 0xFF, 1);
}

s32 func_150C01DC(Struct150C01DC *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4) {
    struct17 pos;
    Arg15152190 b;

    pos.unk0 = arg0->unk38;
    pos.unk4 = arg4 + 20.0f;
    pos.unk8 = arg0->unk40;
    {
    const s32 ints[1] = { 5 };
    const f32 floats[1] = { 1.0f };

    b.unk00 = 5;
    b.unk04 = 4;
    b.unk08 = pos;
    b.unk14 = 0;
    b.unk16 = 0xFF;
    b.unk18 = -0x40;
    b.unk1A = 0x22;
    b.unk1C = 12.0f;
    b.unk20 = 8.0f;
    b.unk24 = -1.697000027f;
    b.unk28 = 0.4990000129f;
    b.unk2C = 0x1E;
    b.unk2E = 0xF;
    b.unk30 = 0.8000000119f;
    b.unk34 = 1.200000048f;
    b.unk38 = 15.29900074f;
    func_15152190(&b, ints, floats, 1, 0.0f, 1, arg0->unkC, arg0->unk1);
    }
    {
    Arg15153634 a;

    a.unk0 = 5;
    a.unk2 = 8;
    a.unk4 = 0x6C;
    a.unk6 = 0x5103;
    a.unk8 = 0x200005;
    a.unkC = 0;
    a.unk10 = 0x1E;
    a.unk12 = 0xF;
    a.unk14 = 0;
    a.unk18 = 0;
    a.unk1F = 0xFF;
    a.unk1C = 0x4E;
    a.unk1D = 0x54;
    a.unk1E = 0x7B;
    a.unk20 = 0xA4;
    a.unk21 = 0xA1;
    a.unk22 = 0xC8;
    a.unk23 = 0x64;
    a.unk24 = 0x9B;
    a.unk25 = 0xFF;
    a.unk26 = 0xE;
    a.unk28 = 0x12;
    a.unk2A = 0xE;
    a.unk2C = 1.046154022f;
    a.unk30 = 218.0f;
    a.unk34 = 305.0f;
    a.unk38 = pos;
    a.unk44 = 0;
    a.unk46 = -0x28;
    a.unk48 = 0xFF;
    a.unk4A = 0x28;
    a.unk4C = 19.0f;
    a.unk50 = 8.0f;
    a.unk54 = 0.2620000243f;
    a.unk58 = 0.2620000243f;
    a.unk5C = 0x840E07;
    a.unk60 = 0x10;
    a.unk61 = -1;
    a.unk62 = 8;
    a.unk63 = 6;
    a.unk64 = 1;
    a.unk68 = 0.8977670074f;
    func_15153634(&a, 0xFF, arg0->unkC, arg0->unk1);
    }
    return 0;
}

void func_150C04C0(Vec3F150C04C0 *arg0, void *arg1, s32 arg2, u8 arg3, u8 arg4, s32 arg5) {
    Struct150C04C0 sp34;
    Struct150C04C0Color sp2C;
    s32 ints[1];
    const f32 floats[1] = { 1.0f };
    f32 sp20;
    u8 temp_v0;

    ints[0] = arg2;
    sp34.unk00 = 9;
    sp34.unk04 = 4;
    sp20 = 0.6500000358f;
    sp34.unk08 = *arg0;
    sp34.unk14 = 4.0f;
    sp34.unk18 = 7.0f;
    sp34.unk1C = -1.280000091f;
    sp34.unk20 = 0.3360000253f;
    sp34.unk28 = 0.6000000238f;
    sp34.unk2C = 0.4500000179f;
    sp34.unk24 = 0x50;
    sp34.unk26 = 0x3C;
    sp34.unk34 = arg1;
    sp34.unk48 = ints;
    sp34.unk4C = (void *)floats;
    sp34.unk50 = 1;
    sp34.unk30 = 17.07700157f;
    sp34.unk38 = 0.7520000339f;
    sp34.unk3C = 0.2040000111f;
    sp34.unk40 = 0.1640000045f;
    sp34.unk44 = 10.0f;
    sp34.unk54 = 78.0f;
    if (arg3 != 0) {
        temp_v0 = 1;
    } else {
        temp_v0 = 0;
    }
    sp34.unk58 = temp_v0;
    sp34.unk59 = 0xE;
    sp34.unk5C = 4;
    sp34.unk60 = &sp20;
    sp2C.unk0 = 0;
    sp2C.unk2 = 0xFF;
    sp2C.unk4 = -0x32;
    sp2C.unk6 = 0x23;
    func_15150400(&sp34, &sp2C, arg4, arg5);
}

s32 func_150C0648(Struct150C0648 *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4, s32 arg5) {
    u8 flag;

    if (func_150ADA68() < arg0->unk170) {
        {
            Struct150C04C0 desc;
            Struct150C04C0Color color;
            s32 ints[1];
            const f32 floats[1] = { 1.0f };

            ints[0] = arg0->unk66;
            desc.unk00 = 2;
            desc.unk04 = 0;
            desc.unk08.x = arg0->unk38;
            desc.unk08.y = arg4 + 20.0f;
            desc.unk08.z = arg0->unk40;
            desc.unk14 = 5.0f;
            desc.unk18 = 4.0f;
            desc.unk1C = -1.210000038f;
            desc.unk20 = 0.4720000327f;
            desc.unk24 = 0x28;
            desc.unk26 = 0x1E;
            desc.unk28 = arg0->unk18 * 0.3600000143f;
            desc.unk2C = arg0->unk18 * 0.4130000174f;
            desc.unk30 = 31.52700233f;
            desc.unk34 = arg0->unk110;
            desc.unk38 = 1.0f;
            desc.unk3C = 0;
            desc.unk40 = 0;
            desc.unk44 = 10.0f;
            desc.unk48 = ints;
            desc.unk4C = (void *)floats;
            desc.unk50 = 1;
            desc.unk54 = 0;
            if (arg0->unk60 & 0x800) {
                flag = 1;
            } else {
                flag = 0;
            }
            desc.unk58 = flag;
            desc.unk59 = 0xA;
            desc.unk5C = 0;
            desc.unk60 = NULL;
            color.unk0 = 0;
            color.unk2 = 0xFF;
            color.unk4 = -0x2A;
            color.unk6 = 0x19;
            func_15150400(&desc, &color, arg0->unkC, arg0->unk1);
            {
            Arg15153634 a;
            f32 y;

            y = arg4 + 20.0f;
            a.unk0 = 1;
            a.unk2 = 2;
            a.unk4 = 0x6C;
            a.unk6 = 0x5103;
            a.unk8 = 0x200005;
            a.unkC = 0;
            a.unk10 = 0x1E;
            a.unk12 = 0x10;
            a.unk14 = 0;
            a.unk18 = 0;
            a.unk1F = 0xFF;
            a.unk1C = 0x4E;
            a.unk1D = 0x54;
            a.unk1E = 0x7B;
            a.unk20 = 0xA4;
            a.unk21 = 0xA1;
            a.unk22 = 0xC8;
            a.unk23 = 0xC8;
            a.unk24 = 0x37;
            a.unk25 = 0xFF;
            a.unk26 = 0x14;
            a.unk28 = 0xC;
            a.unk2A = 0x14;
            a.unk2C = 1.024461985f;
            a.unk30 = 178.0f;
            a.unk34 = 91.0f;
            a.unk38.unk0 = arg0->unk38;
            a.unk38.unk4 = y;
            a.unk38.unk8 = arg0->unk40;
            a.unk44 = 0;
            a.unk46 = -0x12;
            a.unk48 = 0xFF;
            a.unk4A = 0xB;
            a.unk4C = 4.0f;
            a.unk50 = 6.0f;
            a.unk54 = 0.006000000052f;
            a.unk58 = 0.0f;
            a.unk5C = 0x40040E07;
            a.unk60 = 0x10;
            a.unk61 = -1;
            a.unk62 = 8;
            a.unk63 = 6;
            a.unk64 = 1;
            a.unk68 = 0.9535999894f;
            func_15153634(&a, 0xFF, arg0->unkC, arg0->unk1);
            }
        }
        return 0;
    }
    return func_15133B98(arg0, arg1, arg2, arg3, arg4, arg5);
}
