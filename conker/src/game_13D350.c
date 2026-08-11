#include <ultra64.h>
#define func_1502B7F0 func_1502B7F0__proto
#include "functions.h"
#undef func_1502B7F0
#include "variables.h"

extern u8 D_800DBEA8[];
Gfx *func_15110544(Gfx *gfx, s32 a, s32 b, s32 c, s32 d, u8 r, u8 g, u8 bl);
Gfx *func_1501A6CC(Gfx *arg0, s32 a, s32 b, s32 c, s32 d);

typedef struct {
    u8  pad0[0x24];
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    f32 unk30;
} Struct151103C8;

#pragma GLOBAL_ASM("asm/nonmatchings/game_13D350/func_1510FEA0.s")

extern s32 D_800BE628;
void func_150A7A48(f32 a[4][4], f32 b[4][4], f32 c[4][4]);
void func_151102CC(f32 a0[4][4], f32 a1, f32 a2, f32 a3);

void func_151102CC(f32 arg0[4][4], f32 arg1, f32 arg2, f32 arg3) {
    f32 sp28[4][4];

    func_150A8050(arg0, 0.0f, arg2, 0.0f);
    func_150A8050(sp28, arg1, 0.0f, 0.0f);
    func_150A7A48(arg0, sp28, arg0);
    func_150A8050(sp28, 0.0f, 0.0f, arg3);
    func_150A7A48(arg0, sp28, arg0);
}

void func_15110360(s32 arg0, f32 arg1[4][4], f32 arg2, f32 arg3, f32 arg4) {
    func_151102CC(arg1, arg2, arg3, arg4);
    func_150A7A48(arg1, (f32 (*)[4])((u8 *)((struct259 *)D_800BE628 + arg0) + 0xBC), arg1);
}

Gfx *func_151103C8(Gfx *gfx, s32 arg1, s32 arg2, s32 arg3) {
    Struct151103C8 *temp;

    temp = (Struct151103C8 *)((struct259 *)D_800BE628 + D_80082FA4);
    gfx = func_15110544(gfx, (s32)temp->unk2C, (s32)temp->unk24,
                        (s32)(temp->unk30 - 1.0f), (s32)temp->unk28,
                        D_800DBEA8[0], D_800DBEA8[1], D_800DBEA8[2]);
    if (D_80082FA0 != 0) {
        if (D_80082FA4 == 0) {
            gDPPipeSync(gfx++);
            gfx = (Gfx *)func_1501A490((s32)gfx, 0xFF, 0, 0, 0, 0);
            gDPSetFillColor(gfx++, 0x10001);
            gfx = func_1501A6CC(gfx, 0, (D_800BE624 >> 1) - 6, D_800BE620,
                                (D_800BE624 >> 1) + 6);
            if (D_80082FA0 != 1) {
                gfx = func_1501A6CC(gfx, (D_800BE620 >> 1) - 1, 0,
                                    (D_800BE620 >> 1) + 1, D_800BE624);
            }
        }
    }
    return gfx;
}

Gfx *func_1501A680(Gfx *arg0);
Gfx *func_1501A6CC(Gfx *arg0, s32 a, s32 b, s32 c, s32 d);

Gfx *func_15110544(Gfx *gfx, s32 a, s32 b, s32 c, s32 d, u8 r, u8 g, u8 bl) {
    s32 color;

    gDPPipeSync(gfx++);
    gDPSetOtherMode(gfx++, 0x302C0F, 4);
    gfx = func_1501A680(gfx);
    color = GPACK_RGBA5551(r, g, bl, 1);
    gDPSetFillColor(gfx++, (color << 16) | color);
    gfx = func_1501A6CC(gfx, a, b, c, d);
}

Gfx *func_15110600(Gfx *gfx, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_v0;

    temp_v0 = D_800BE9F0;
    if ((temp_v0 == 0x1B) || (temp_v0 == 0x1E) ||
        ((temp_v0 == 0x31) && (*(u8 *)&D_800DBFF0->unk3D4->unk78 == 3))) {
        gfx = func_15110544(gfx, 2, 0, D_800BE620 - 2, D_800BE624,
                            D_800DBEA8[0], D_800DBEA8[1], D_800DBEA8[2]);
    }
    return gfx;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_13D350/func_151106A8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_13D350/func_151108C4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_13D350/func_15110CFC.s")

extern s32 *D_800DBE80;
extern s32 *D_800891BC[];
s32 func_1502B7F0();
void func_10004074();
void func_1510D694(s32);
void func_15111858(void);

void func_1511172C(s32 arg0) {
    s32 i;
    struct104 *var_v0;
    struct104 * volatile *var_s3;
    s32 **var_s0;

    var_s3 = (struct104 * *)&D_800B0DF0;
    if (arg0 == 1) {
        var_s3 = (struct104 * *)&D_800B0DF0;
        (*var_s3)->unk8 = 1;
        var_s0 = &D_800DBE80;
        if (D_800DBE80 != 0) {
            s32 *temp_v0;

            temp_v0 = D_800DBE80;
            func_10004074(temp_v0);
        }
        func_15111858();
        return;
    }

    var_v0 = *var_s3;
    if (arg0 != var_v0->unk9) {
        if (var_v0->unk8 == 4) {
            if (D_80038080 != 0) {
                for (i = 0; i != 0x168; i++) {
                    func_1510D694(D_800891BC[(*var_s3)->unk9][0] + i);
                }
            }
            var_s0 = &D_800DBE80;
            func_10004074(*var_s0);
            (*var_s3)->unk9 = arg0;
            func_1502B7F0(var_s0, 2, 0xD, (*var_s3)->unk9);
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_13D350/func_15111858.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_13D350/func_15111AF4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_13D350/func_15112520.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_13D350/func_15112A80.s")

void func_15113180(void) {
    s32 i;
    s32 offset;
    struct131 *temp_a0;

    i = 0;
    offset = 0;
    if (D_800DBEF0 > 0) {
        do {
            temp_a0 = (struct131 *)((u8 *)D_800DBEF4 + offset);
            temp_a0->unk6F &= ~0x40;
            temp_a0 = (struct131 *)((u8 *)D_800DBEF4 + offset);
            if (((temp_a0->unk6F & 0xF) != 0) || ((((u8 *)temp_a0)[0x70] & 4) == 4)) {
                if (*(s32 *)((u8 *)temp_a0 + 0x38) != 0) {
                    temp_a0->unk6F |= 0x40;
                }
            }
            i++;
            offset += 0xA0;
        } while (i < D_800DBEF0);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_13D350/func_15113218.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_13D350/func_151135C4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_13D350/func_151137D4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_13D350/func_15113C88.s")

extern s32 D_800DBF98;

/* struct131 with the fields this file needs spelled out (the shared header
   stops at unk6F). */
typedef struct Struct15113E54 {
    u8  pad0[0x38];
    /* 0x38 */ void (*unk38)(struct Struct15113E54 *);
    u8  pad3C[0x1E];
    /* 0x5A */ s16 unk5A;
    /* 0x5C */ s16 unk5C;
    /* 0x5E */ s16 unk5E;
    u8  pad60[0xE];
    /* 0x6E */ u8  unk6E;
    /* 0x6F */ u8  unk6F;
    u8  pad70[0x10];
    /* 0x80 */ s32 unk80;
    u8  pad84[0x1C];
} Struct15113E54; /* size 0xA0 */

typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ u16 unk2;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ u16 unk8[8];
} Struct150174C0; /* size 0x18 */

#define RECORDS (*(Struct150174C0 **)&D_800D23C0)

void func_15113E54(s32 arg0) {
    s16 x;
    s16 y;
    s16 z;
    s32 flags;
    s32 i;
    s32 j;
    s32 count;
    s32 offset;
    s32 entry;
    Struct15113E54 *obj;

    arg0 = arg0;
    x = 0;
    y = 0;
    z = 0;
    flags = 0;
    i = 0;
    count = D_800DBEF0 - D_800DBF98;
    if (count > 0) {
        offset = 0;
        do {
            obj = (Struct15113E54 *)((u8 *)offset + (s32)D_800DBEF4);
            if (((obj->unk6F & 0x40) == 0x40) && (obj->unk6E == 0)) {
                obj->unk38(obj);
            }
            i++;
            offset += 0xA0;
        } while (i != count);
    }

    for (i = 0; i < (s32)D_80087380; i++) {
        if ((RECORDS[i].unk8[0] >> 12) == 2) {
            for (j = 0; j < RECORDS[i].unk2; j++) {
                entry = RECORDS[i].unk8[j];
                if ((entry >> 12) == 2) {
                    obj = (Struct15113E54 *)(((entry & 0xFFF) * 0xA0) + (s32)D_800DBEF4);
                    if (((obj->unk6F & 0x40) == 0x40) && (obj->unk6E == 0)) {
                        if (j != 0) {
                            obj->unk5A = x;
                            obj->unk5C = y;
                            obj->unk5E = z;
                            obj->unk80 = flags;
                        }
                        obj->unk38(obj);
                    }
                    if (j == 0) {
                        x = obj->unk5A;
                        y = obj->unk5C;
                        z = obj->unk5E;
                        flags = obj->unk80;
                    }
                }
            }
        }
    }
}

extern s32 *D_800DBF94;

s32 func_15114050(struct131 *arg0, s32 arg1) {
    if (((u8 *)arg0)[0x4F] & 0x80) {
        if (arg1 == -1) {
            return 1;
        }
        if (D_800DBF94[arg0 - D_800DBEF4] & (1 << arg1)) {
            return 1;
        }
    }
    return 0;
}

s32 func_151140C4(struct131 *arg0) {
    s32 i;

    i = 0;
    if (((u8 *)arg0)[0x4F] & 0x80) {
        for (; i != 32; i++) {
            if (D_800DBF94[arg0 - D_800DBEF4] & (1 << i)) {
                return i;
            }
        }
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_13D350/func_15114188.s")

/* struct131 again, with the rotation/offset fields func_15114348 needs. */
typedef struct {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    u8  padC[0x4];
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14;
    u8  pad16[0x44];
    /* 0x5A */ s16 unk5A;
    /* 0x5C */ s16 unk5C;
    /* 0x5E */ s16 unk5E;
    /* 0x60 */ f32 unk60;
    /* 0x64 */ f32 unk64;
    /* 0x68 */ f32 unk68;
    u8  pad6C[0x34];
} Struct15114348; /* size 0xA0 */

void func_150A7960(f32 *m, f32 x, f32 y, f32 z, f32 *ox, f32 *oy, f32 *oz);

#define OBJ15114348 ((Struct15114348 *)((u8 *)D_800DBEF4 + arg0 * 0xA0))

void func_15114348(s32 arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    f32 dx;
    f32 dy;
    f32 dz;
    f32 ox;
    f32 oy;
    f32 oz;
    f32 mtx[4][4];
    f32 tmp[4][4];
    f32 axes[3][3];

    axes[0][0] = 1.0f;
    axes[0][1] = 0.0f;
    axes[0][2] = 0.0f;
    axes[1][0] = 0.0f;
    axes[1][1] = 1.0f;
    axes[1][2] = 0.0f;
    axes[2][0] = 0.0f;
    axes[2][1] = 0.0f;
    axes[2][2] = 1.0f;

    dx = *arg1 - OBJ15114348->unk10;
    dy = *arg2 - OBJ15114348->unk12;
    dz = *arg3 - OBJ15114348->unk14;

    if (OBJ15114348->unk0 != 0.0f) {
        /* Spelled 1.f/0.f, not 1.0f/0.0f: IDO pools float literals by spelling, and the
           original source keeps these axis constants out of the identity-matrix pool
           above (sharing them costs 345 in diff). */
        guRotateF(mtx, OBJ15114348->unk0, 1.f, 0.f, 0.f);
        func_150A7960(&mtx[0][0], axes[1][0], axes[1][1], axes[1][2], &axes[1][0], &axes[1][1], &axes[1][2]);
        func_150A7960(&mtx[0][0], axes[2][0], axes[2][1], axes[2][2], &axes[2][0], &axes[2][1], &axes[2][2]);
    }
    if (OBJ15114348->unk8 != 0.0f) {
        guRotateF(mtx, OBJ15114348->unk8, axes[2][0], axes[2][1], axes[2][2]);
        func_150A7960(&mtx[0][0], axes[1][0], axes[1][1], axes[1][2], &axes[1][0], &axes[1][1], &axes[1][2]);
        func_150A7960(&mtx[0][0], axes[0][0], axes[0][1], axes[0][2], &axes[0][0], &axes[0][1], &axes[0][2]);
    }
    if (OBJ15114348->unk4 != 0.0f) {
        guRotateF(mtx, OBJ15114348->unk4, axes[1][0], axes[1][1], axes[1][2]);
        func_150A7960(&mtx[0][0], axes[0][0], axes[0][1], axes[0][2], &axes[0][0], &axes[0][1], &axes[0][2]);
        func_150A7960(&mtx[0][0], axes[2][0], axes[2][1], axes[2][2], &axes[2][0], &axes[2][1], &axes[2][2]);
    }

    guRotateF(mtx, OBJ15114348->unk60, axes[0][0], axes[0][1], axes[0][2]);
    guRotateF(tmp, OBJ15114348->unk68, axes[2][0], axes[2][1], axes[2][2]);
    func_150A7A48(mtx, tmp, mtx);
    guRotateF(tmp, OBJ15114348->unk64, axes[1][0], axes[1][1], axes[1][2]);
    func_150A7A48(mtx, tmp, mtx);

    func_150A7960(&mtx[0][0], dx, dy, dz, &ox, &oy, &oz);

    ox = OBJ15114348->unk5A + (ox - dx);
    oy = OBJ15114348->unk5C + (oy - dy);
    oz = OBJ15114348->unk5E + (oz - dz);

    *arg1 += ox;
    *arg2 += oy;
    *arg3 += oz;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_13D350/func_1511473C.s")

void func_150A7A48(f32 a[4][4], f32 b[4][4], f32 c[4][4]);

struct Struct151148A8 {
    f32 unk0;
    f32 unk4;
    f32 unk8;
};

void func_151148A8(f32 arg0[4][4], struct Struct151148A8 *arg1) {
    f32 sp18[4][4];

    func_150A8050(arg0, 0.0f, arg1->unk4, 0.0f);
    func_150A8050(sp18, arg1->unk0, 0.0f, arg1->unk8);
    func_150A7A48(sp18, arg0, arg0);
}

struct Struct1511490C {
    char pad0[0x10];
    s16 unk10;
    s16 unk12;
    s16 unk14;
    char pad16[2];
    f32 unk18;
    char pad1C[0x10];
    s32 unk2C;
    s32 unk30;
    s32 unk34;
};

void func_150A7CB0(f32 mtx[4][4], s32 x, s32 y, s32 z);

void func_1511490C(f32 arg0[4][4], struct Struct1511490C *arg1) {
    f32 sp20[4][4];

    func_151148A8(arg0, arg1);
    arg0[3][0] = arg1->unk10;
    arg0[3][1] = arg1->unk12 + arg1->unk18;
    arg0[3][2] = arg1->unk14;
    func_150A7CB0(sp20, arg1->unk2C, arg1->unk30, arg1->unk34);
    func_150A7A48(sp20, arg0, arg0);
}

struct131 *func_151149AC(u8 id) {
    s32 i;
    s32 offset;
    struct131 *base;
    struct131 *ptr;

    if (id == 0) {
        return NULL;
    }

    i = 0;
    if (D_800DBEF0 > 0) {
        base = D_800DBEF4;
        offset = 0;
        ptr = base;
        do {
            i++;
            if (((u8 *)ptr)[0x72] == id) {
                return (struct131 *)((u8 *)offset + (s32)base);
            }
            offset += sizeof(struct131);
            ptr++;
        } while (i < D_800DBEF0);
    }
    return NULL;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_13D350/func_15114A1C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_13D350/func_15114B94.s")

s32 func_15114CC4(void *a0, s32 a1, s32 *a2, s32 a3) {
    s16 *v1 = *(s16 **)((u8 *)a0 + 0x18);

    if (v1 != 0 && (*a2 != 0 || *(s32 *)((u8 *)a0 + 0x1C) == 0)) {
        *(s32 *)((u8 *)a0 + 0x1C) = 1;
        *(s16 *)((u8 *)a0 + 0x2) = v1[8];
        *(s16 *)((u8 *)a0 + 0x4) = v1[9];
        *(s16 *)((u8 *)a0 + 0x6) = v1[10];
        return 0;
    }
    return 1;
}

typedef struct {
    char pad0[0x10];
    s16 unk10;
    s16 unk12;
    s16 unk14;
    char pad16[0x5E];
    u16 unk74;
} Struct15114D24;

s32 func_10010E78(u16 arg0, s32 arg1, u16 arg2, s16 arg3, u8 arg4, s32 arg5,
                  s16 arg6, s16 arg7, s16 arg8, s16 arg9, s16 argA);

void func_15114D24(Struct15114D24 *arg0, s32 arg1, s32 arg2, s16 arg3, s16 arg4, s32 arg5) {
    u16 sfx;

    if (arg5 & 1) {
        if (arg0->unk74 != 0) {
            if (func_1001147C(arg0->unk74) == arg1) {
                return;
            }
        }
    }

    if (arg1 == -1) {
        if (arg0->unk74 != 0) {
            func_100111C8(arg0->unk74);
            arg0->unk74 = 0;
        }
        return;
    }

    if (arg5 & 8) {
        sfx = 0;
    } else {
        sfx = arg0->unk74;
    }

    if (arg5 & 4) {
        func_10010E78(sfx, arg1, arg2, 0, 0, -1, arg0->unk10, arg0->unk12,
                      arg0->unk14, arg3, arg4);
        if ((arg5 & 8) == 0) {
            arg0->unk74 = 0;
        }
    } else if (arg5 & 2) {
        if (sfx != 0) {
            func_1001123C(sfx);
            sfx = 0;
        }
        arg0->unk74 = func_10010E78(sfx, arg1, arg2, 0, 0, -1, arg0->unk10,
                                    arg0->unk12, arg0->unk14, arg3, arg4);
    } else {
        if (sfx != 0) {
            func_1001123C(sfx);
        }
        arg0->unk74 = func_1000FA64(arg1, arg0->unk10, arg0->unk12, arg0->unk14,
                                    arg2, arg4, arg3, (s32)func_15114CC4, arg0,
                                    0, 0, 0);
    }
}

void func_15114F04(s32 arg0, s32 arg1, s32 arg2) {
    func_1001001C(func_15114CC4, arg0, 0, arg1, arg2);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_13D350/func_15114F44.s")
