#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern f32 cosf(f32);
extern f32 sinf(f32);
extern s32 D_800BE9E4;
extern void func_1510E82C(s32 *, s32, f32 *, s32, s32 *, s32, f32, f32, f32, f32, s32, s32);

struct Obj15171CA0 {
    char pad0[0x16];
    s16 unk16;
    char pad18[0x26 - 0x18];
    s16 unk26;
    char pad28[0x36 - 0x28];
    s16 unk36;
    char pad38[0x46 - 0x38];
    s16 unk46;
    char pad48[0x50 - 0x48];
    s16 unk50;
    s16 unk52;
    s16 unk54;
    u16 unk56;
    u8  unk58;
    u8  unk59;
};

extern struct Obj15171CA0 *func_15167A68(s32, s32, s32, s32, s32, s32);

struct Obj15171CA0 *func_15171CA0(s16 arg0, u16 arg1, u8 arg2, s32 arg3, s32 arg4, s32 arg5, u8 arg6, s32 arg7) {
    struct Obj15171CA0 *ret = func_15167A68(arg5 == 0 ? 0xF : 0x43, arg7, 0x60, 1, arg6, 1);
    if (ret == 0) {
        return NULL;
    }
    ret->unk50 = arg0;
    ret->unk52 = 0;
    ret->unk54 = arg4;
    ret->unk56 = arg1;
    ret->unk58 = arg2;
    ret->unk59 = arg3;
    ret->unk16 = 0;
    ret->unk26 = 0;
    ret->unk36 = 0;
    ret->unk46 = 0;
    return ret;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_19F150/func_15171D4C.s")

struct Some15171F04 {
    u32 unk0;
    u8 unk4;
    u8 pad5;
    u16 unk6;
    u16 unk8;
    u8 unkA;
};
extern struct Some15171F04 *D_8008CA4C[];
s32 func_151725FC(Vtx *arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s32 arg6, u8 arg7);

void func_15171F04(f32 arg0, f32 arg1, f32 arg2, s32 arg3, s16 arg4, u16 arg5, u8 arg6, s32 arg7, s32 arg8, s32 arg9, s32 arg10, u8 arg11, s32 arg12) {
    struct Obj15171CA0 *temp;

    temp = func_15171CA0(arg4, arg5, arg6, arg8, arg9, arg10, arg11, arg12);
    if (temp != NULL) {
        if (func_151725FC((Vtx *)((u8 *)temp + 0x10), arg3, arg0, arg1, arg2, 0.0f, arg7, D_8008CA4C[temp->unk58]->unk6) == 0) {
            func_1516972C((struct102 *)temp);
        }
    }
}

void func_15171FC0(struct Obj15171CA0 *arg0) {
    s32 temp_v0;

    temp_v0 = arg0->unk50;
    if (temp_v0 < -1) {
        arg0->unk50 = temp_v0 + 1;
        if (arg0->unk50 == -1) {
            func_1516972C((struct102 *)arg0);
        }
        return;
    }

    if (temp_v0 == 0) {
        arg0->unk50 = -3;
        return;
    }

    if (temp_v0 == -1) {
        return;
    }

    if ((arg0->unk59 & 4) == 0) {
        if (D_800BE9E4 < temp_v0) {
            arg0->unk50 = temp_v0 - D_800BE9E4;
        } else {
            arg0->unk50 = 0;
        }
    }

    arg0->unk52 += arg0->unk54;
    temp_v0 = D_8008CA4C[arg0->unk58]->unk4;
    if ((arg0->unk52 / 256) < temp_v0) {
        return;
    }

    if (arg0->unk59 & 4) {
        arg0->unk50 = -3;
    } else {
        arg0->unk52 = (temp_v0 << 8) - 0x100;
    }
}

extern s32 D_800DD1B4;
extern s32 D_800DD1B8;
extern s16 D_800DD1BC;
extern s16 D_800DD1C0;
extern s16 D_800DD1C2;
extern s16 D_800DD1C4;
extern s16 D_800DD1C6;
extern s32 D_800D2C9C;
struct Arg15094F70 {
    s32 unk0[6];
};
extern Gfx *func_15094F70(Gfx *, struct Some15171F04 *, s32, struct Arg15094F70 *, s32, s32, s32, s32, s32);
extern Gfx *func_15142FBC(Gfx *gfx, s32 arg1, s32 arg2, s32 *arg3);

Gfx *func_151720C4(Gfx *gfx, struct Obj15171CA0 *arg1, s32 arg2) {
    s32 r;
    s32 g;
    s32 b;
    s32 a;
    s32 newComb;
    s32 cyc;
    s32 comb;
    s32 newCyc;
    struct Arg15094F70 sp98;
    u32 tex;
    s32 frame;
    s32 flag;
    struct Some15171F04 *desc;
    s32 mode[2];

    flag = 1;
    if (arg1->unk50 >= 2) {
        desc = D_8008CA4C[arg1->unk58];
        frame = arg1->unk52 >> 8;
        tex = desc->unk0;
        if (desc->unk0 >= 0x10000000U) {
            tex = ((u32 *)desc->unk0)[frame];
            frame = 0;
        }
        if (tex != D_800DD1B4 || frame != D_800DD1B8) {
            gfx = func_15094F70(gfx, desc, arg1->unk52, &sp98, 0, 0, 0, 2, 3);
            D_800DD1B4 = tex;
            D_800DD1B8 = frame;
        }
        cyc = D_800DD1BC & 0xF;
        comb = D_800DD1BC & 0xF0;
        newCyc = !(arg1->unk59 & 1) ? 1 : 2;
        if (desc->unkA == 5) {
            newCyc += 2;
        }
        if (cyc != newCyc) {
            cyc = newCyc;
            if (flag) {
                gDPPipeSync(gfx++);
            }
            flag = 0;
            switch (newCyc) {
                case 1:
                    mode[1] = 0;
                    mode[0] = 0x504DD8;
                    break;
                case 2:
                    mode[1] = 0;
                    mode[0] = 0x504B50;
                    break;
                case 3:
                    mode[1] = 0x100000;
                    mode[0] = 0xC184DD8;
                    break;
                case 4:
                    mode[1] = 0x100000;
                    mode[0] = 0xC184B50;
                    break;
            }
            gDPSetAlphaCompare(gfx++, G_AC_NONE);
            gSPClearGeometryMode(gfx++, G_FOG | G_LOD);
        }
        gfx = func_15142FBC(gfx, mode[1] | G_TP_PERSP | D_800D2C9C | G_TF_BILERP | G_TC_FILT | G_CD_NOISE | G_AD_DISABLE, mode[0], &flag);
        if (!(arg1->unk59 & 8)) {
            if (desc->unkA == 0) {
                if (arg1->unk56 != 0) {
                    newComb = 0x10;
                } else {
                    newComb = 0x20;
                }
            } else if (desc->unkA == 5) {
                if (arg1->unk56 != 0) {
                    newComb = 0x60;
                } else {
                    newComb = 0x50;
                }
            } else {
                newComb = 0x30;
            }
        } else {
            newComb = 0x40;
        }
        if (comb != newComb) {
            comb = newComb;
            if (flag) {
                gDPPipeSync(gfx++);
            }
            switch (newComb) {
                case 0x10:
                    gDPSetCombineLERP(gfx++, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0);
                    break;
                case 0x20:
                    gDPSetCombineLERP(gfx++, 0, 0, 0, TEXEL0, PRIMITIVE, 0, TEXEL0, 0, 0, 0, 0, TEXEL0, PRIMITIVE, 0, TEXEL0, 0);
                    break;
                case 0x30:
                    gDPSetCombineLERP(gfx++, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0, 0, 0, 0, PRIMITIVE, TEXEL0, 0, PRIMITIVE, 0);
                    break;
                case 0x40:
                    gDPSetCombineLERP(gfx++, 0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0, 0, 0, 0, TEXEL0);
                    break;
                case 0x50:
                    gDPSetCombineLERP(gfx++, 0, 0, 0, TEXEL0, PRIMITIVE, 0, TEXEL1, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED);
                    break;
                case 0x60:
                    gDPSetCombineLERP(gfx++, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, TEXEL1, 0, 0, 0, 0, COMBINED, 0, 0, 0, COMBINED);
                    break;
            }
        }
        D_800DD1BC = cyc | comb;
        r = (arg1->unk56 >> 8) & 0xF8;
        g = (arg1->unk56 >> 3) & 0xF8;
        b = (arg1->unk56 << 2) & 0xF8;
        if (arg1->unk50 >= 0x1A) {
            a = 0xFF;
        } else {
            a = arg1->unk50 * 10;
        }
        if (r != D_800DD1C0 || g != D_800DD1C2 || b != D_800DD1C4 || a != D_800DD1C6) {
            D_800DD1C0 = r;
            D_800DD1C2 = g;
            D_800DD1C4 = b;
            D_800DD1C6 = a;
            if (flag) {
                gDPPipeSync(gfx++);
            }
            gDPSetPrimColor(gfx++, 1, 0, r, g, b, a);
        }
        gSPVertex(gfx++, (u8 *)arg1 + 0x10, 4, 0);
        gSP1Triangle(gfx++, 0, 1, 2, 0);
        gSP1Triangle(gfx++, 0, 2, 3, 0);
    }
    return gfx;
}

extern s32 func_1510E388(void *, void *, f32 *, f32 *);

static const s16 D_800A6FD0[8] = { 0x800, 0, 0, 0, 0, 0x800, 0x800, 0x800 };
static const s16 D_800A6FE0[8] = { 0x400, 0, 0, 0, 0, 0x400, 0x400, 0x400 };
static const s16 D_800A6FF0[8] = { 0x200, 0, 0, 0, 0, 0x200, 0x200, 0x200 };

s32 func_151725FC(Vtx *arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s32 arg6, u8 arg7) {
    s32 i;
    const s16 *tbl;
    f32 cx;
    f32 cy;
    f32 s;
    f32 len1;
    f32 len2;
    f32 v[2][3];
    f32 lenSq;
    f32 lenSq2;
    f32 b;
    f32 a;
    f32 minSq;
    f32 d;
    f32 c;
    f32 x;
    f32 z;
    f32 y;
    s32 n;
    f32 size;
    f32 ang;

    n = arg6 / 16;
    if (n == 0) {
        n = 1;
    }
    if (func_1510E388((void *)arg1, NULL, &a, &b) == 0) {
        return 0;
    }
    x = -n;
    v[0][2] = x;
    v[0][0] = 0.0f;
    v[0][1] = a * v[0][0] + b * v[0][2];
    d = (b + b) * (-v[0][1] - v[0][1]) + ((-v[0][2] - v[0][2]) + (-v[0][2] - v[0][2]));
    if (d == 0.0f) {
        d = 0.001f;
    }
    v[1][0] = -n;
    v[1][1] = ((a * v[1][0] + a * v[1][0]) * (-v[0][2] - v[0][2])) / d;
    if (b == 0.0f) {
        z = 0.0f;
    } else {
        z = (v[1][1] - a * v[1][0]) / b;
    }
    lenSq = v[0][0] * v[0][0] + v[0][1] * v[0][1] + v[0][2] * v[0][2];
    if (lenSq > 100000000.0f) {
        lenSq = 100000000.0f;
    }
    minSq = n * n;
    if (lenSq < minSq) {
        lenSq = minSq;
    }
    len1 = sqrtf(lenSq);
    v[1][2] = z;
    lenSq2 = v[1][0] * v[1][0] + v[1][1] * v[1][1] + z * z;
    if (lenSq2 > 100000000.0f) {
        lenSq2 = 100000000.0f;
    }
    if (lenSq2 < minSq) {
        lenSq2 = minSq;
    }
    len2 = sqrtf(lenSq2);
    size = arg6;
    for (i = 0; i < 3; i++) {
        v[0][i] = v[0][i] * size / len1;
        v[1][i] = v[1][i] * size / len2;
        arg0[0].v.ob[i] = v[0][i];
        arg0[1].v.ob[i] = v[1][i];
        arg0[2].v.ob[i] = -v[0][i];
        arg0[3].v.ob[i] = -v[1][i];
    }
    ang = (arg5 - 225.0f) * 0.01745329238f;
    c = cosf(ang);
    s = sinf(ang);
    if (arg7 == 0x10) {
        cx = cy = 256.0f;
        tbl = D_800A6FF0;
    } else if (arg7 == 0x20) {
        cx = cy = 512.0f;
        tbl = D_800A6FE0;
    } else {
        cx = cy = 1024.0f;
        tbl = D_800A6FD0;
    }
    for (i = 0; i < 4; i++) {
        arg0[i].v.tc[0] = ((tbl[i * 2] - cx) * c - (tbl[i * 2 + 1] - cy) * s) + cx + 8192.0f;
        arg0[i].v.tc[1] = ((tbl[i * 2 + 1] - cy) * c + (tbl[i * 2] - cx) * s) + cy + 8192.0f;
    }
    for (i = 0; i < 4; i++) {
        arg0[i].v.ob[0] = arg0[i].v.ob[0] + arg2;
        arg0[i].v.ob[1] = arg0[i].v.ob[1] + arg3;
        arg0[i].v.ob[2] = arg0[i].v.ob[2] + arg4;
    }
    return 1;
}

s32 func_15172B20(void *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5, s32 arg6, u8 arg7) {
    struct sp15172B20 {
        s32 unk0;
        f32 unk4;
        s32 unk8;
        s32 unkC;
    };
    f32 temp_f0;
    f32 temp_f6;
    struct sp15172B20 sp40;
    f32 temp_f12;

    temp_f12 = (arg4 - 90.0f) * 0.01745329238f;
    temp_f6 = cosf(temp_f12);
    temp_f0 = sinf(temp_f12);
    arg1 += (f32) arg5 * temp_f0;
    arg3 += (f32) arg5 * temp_f6;
    func_1510E82C(&sp40.unk0, 0, &sp40.unk4, 0, &sp40.unk8, 0, arg1, arg2, arg3, arg2, 0, 0);
    if (sp40.unk0 == 0) {
        return 0;
    }
    if (sp40.unk4 == -10000.0f) {
        return 0;
    }
    return func_151725FC(arg0, sp40.unk0, arg1, sp40.unk4, arg3, arg4, arg6, arg7);
}
