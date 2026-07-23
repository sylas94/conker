#include <ultra64.h>

#define func_15083E90 func_15083E90_s32_proto
#include "functions.h"
#undef func_15083E90
#include "variables.h"

extern f32 D_800A5698;
extern f32 D_800A5694;
extern f32 D_800A569C;
extern s16 D_800DD1C0;
extern s16 D_800DD1C2;
extern s16 D_800DD1C4;
extern s16 D_800DD1C6;
extern s16 D_800DD1C8;
extern s16 D_800DD1CA;
extern s16 D_800DD1CC;
extern s16 D_800DD1CE;
extern s32 D_800DD1FC;
extern s32 D_800DD200;
extern s32 D_800DD1B0;
extern s16 D_800DD204;
extern s16 D_800DD206;
extern s32 D_800DD208;
extern s32 D_800DD20C;
extern s32 D_800DD210;
extern s32 D_800DD214;
extern s32 D_800DD218;
extern s32 D_800DD21C;
extern u8 D_800C3E90;
extern u8 D_8008A160[];
extern s32 D_800DCA00;
extern Mtx *D_800DCA04;
extern f32 D_800DCA08;
extern f32 D_800DCA0C;
extern f32 D_800DCA10;

struct127 *func_15083E90();
void func_150A7960(f32 *, f32, f32, f32, f32 *, f32 *, f32 *);
void func_15142314(Mtx *, s32, f32 *);
Gfx *func_15094FE8(Gfx *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
s32 func_1514306C(s32, s32, s32, u8);

struct unk151420F8 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
};

extern struct unk151420F8 D_800A5200;
s32 func_150A2AEC(s32, s32, struct unk151420F8 *, s32);


void func_15141970(struct37 *arg0) {
    func_1514EDF0(arg0, arg0->unk2C);
}

void func_15141990(void *arg0) {
    func_15141970(arg0);
}

void func_151419B0(void *arg0) {
    func_15141970(arg0);
}

struct A1_151419D0 {
    s32 unk0;
    s32 unk4;
    u8 unk8;
    u8 unk9;
};

struct B_151419D0 {
    s32 unk0;
    s32 unk4;
    u8 unk8;
};

void func_1516972C(struct102 *arg0);

void func_151419D0(struct102 *arg0, struct A1_151419D0 *arg1, u8 arg2) {
    struct B_151419D0 *p = (struct B_151419D0 *)((u8 *)arg0 + 0x28);
    s32 v;
    if (arg2 == 0) {
        v = arg1->unk0;
        if ((v == p->unk4) ||
            (p->unk8 == *(u8*)&arg1->unk4)) {
            func_1516972C(arg0);
        }
    } else if (arg2 == 0x2D) {
        if (p->unk4 == arg1->unk0) {
            p->unk4 = arg1->unk4;
            p->unk8 = arg1->unk9;
        } else if (p->unk4 == arg1->unk4) {
            p->unk4 = arg1->unk0;
            p->unk8 = arg1->unk8;
        }
    }
}
// PERMUTER/HARD: reconstruction is logically correct (best 2673) but has structural mismatches the C
// can't easily force: target reloads D_8008A0B4[idx].unk0 for the indirect call (mine CSEs the != 0
// test value), keeps the list node in a temp (mine promotes to a saved reg -> one extra saved reg),
// and wants beqz+nop where IDO hoists the unk2F4 load into a beqzl delay slot. Calls func_15141C0C /
// func_1510F8CC / func_15141CC0 (indexed fn ptrs D_8008A084[]), func_15141E38, and the func_1514ECE0
// linked-list iterator (node->unk10 = elem, elem->unk28 = idx, elem->unkE = s16, node->unk14 = next).
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15141A7C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15141C0C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15141CC0.s")

void func_15141DA4(void *arg0, s32 arg1, s32 arg2) {
    if ((arg1 < 12) && (arg1 >= 0) &&
        (arg2 < 20) && (arg2 >= 0) &&
        (D_800BE616 == 0) &&
        (D_8008A084[arg1] != 0) && (arg2 != -1)) {
        if ((D_8008A0B4[arg2].unk0 != 0) && (D_8008A0B4[arg2].unk4 > 0)) {
            func_15141E38(arg0, arg2);
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15141E38.s")
void func_15141F78(u8 arg0, struct157 *arg1, f32 arg2, u8 arg3, struct157 *arg4, u8 arg5) {
    struct157 tmp;
    f32 temp_f2;
    s32 phi_v0;

    tmp.unk6 = arg0;
    tmp.unk7 = 0;
    tmp.unk0 = 0x6F701;
    tmp.unk4 = (func_150ADA20() % 61U) + 100;
    tmp.unk8 = 0;
    tmp.unkC = 0;
    tmp.unk10 = (func_150ADA20() & 0x7F) + 128;
    *(u8 *)&tmp.unk11 = 0xFF;
    *(u8 *)&tmp.unk12 = 0xFF;
    *(u8 *)&tmp.unk13 = 0xFF;
    *(u8 *)&tmp.unk14 = 0xFF;
    *(u8 *)&tmp.unk15 = 0xFF;
    tmp.unk18 = 0x3B0002;
    tmp.unk16 = 0;
    tmp.unk17 = 7;
    *(u8 *)&tmp.unk20 = 0xFF;
    tmp.unk1C = arg1->unk18;
    tmp.unk22 = 0x28;
    tmp.unk24 = 6;

    temp_f2 = ((func_150ADA68() * 5.0f) + 10.0f) * arg2;
    if (arg5 == 2) {
        phi_v0 = 1;
    } else {
        phi_v0 = 0;
    }

    func_1513C650((s32)&tmp, 0, 0, (s32)&arg1->unk4, *(f32 *)&arg4->unk0, *(f32 *)&arg1->unk0, *(f32 *)&arg4->unk8, temp_f2, temp_f2, arg3, phi_v0, 3, 1, 0, 0xFF, 1);
}
// NON-MATCHING: need to determine arguments
// void func_1513C650(s32, s32, s32, u16, s32, s32, s32, f32, f32, s32, s32, s32, s32, s32, u8, s32);
// s32 func_1513C650(s32 arg0, u8 arg1, u8 arg2, s32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, u8 arg9, u8 argA, s32 argB, s32 argC, s32 argD, u8 argE, s32 argF);
// void func_15141F78(u8 arg0, struct157 *arg1, f32 arg2, s32 arg3, struct157 *arg4, u8 arg5) {
//     struct157 tmp;
//     f32 temp_f2;
//     s32 phi_v0;
//
//     tmp.unk6 = arg0;
//     tmp.unk7 = 0;
//     tmp.unk0 = 0x6F701;
//     tmp.unk4 = (func_150ADA20() % 61U) + 100;
//     tmp.unk8 = 0;
//     tmp.unkC = 0;
//     tmp.unk10 = (func_150ADA20() & 0x7F) + 128;
//     tmp.unk11 = 0xFF;
//     tmp.unk12 = 0xFF;
//     tmp.unk13 = 0xFF;
//     tmp.unk14 = 0xFF;
//     tmp.unk15 = 0xFF;
//     tmp.unk18 = 0x3B0002;
//     tmp.unk16 = 0;
//     tmp.unk17 = 7;
//     tmp.unk20 = 0xFF;
//     tmp.unk1C = arg1->unk18;
//     tmp.unk22 = 0x28;
//     tmp.unk24 = 6;
//     temp_f2 = ((func_150ADA68() * 5.0f) + 10.0f) * arg2;
//     // --- matching to here ---
//     if (arg5 == 2) {
//         phi_v0 = 1;
//     } else {
//         phi_v0 = 0;
//     }
//     func_1513C650(&tmp, 0, 0, arg1->unk4, arg4->unk0, arg1->unk0, arg4->unk8, temp_f2, temp_f2, arg3, phi_v0, 3, 1, 0, 0xFF, 1);
// }

s32 func_151420F8(s32 arg0) {
    struct unk151420F8 sp18;

    sp18 = D_800A5200;
    if (func_150A2AEC((arg0 - (s32)D_800CC2D0) / (s32)sizeof(struct127), 6, &sp18, arg0) == -1) {
        return 0;
    }
    return 1;
}
struct vec15142180 {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ s32 unk08;
};

struct conker15142180 {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06;
    /* 0x08 */ struct vec15142180 unk08;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ s16 unk2C;
    /* 0x2E */ s16 unk2E;
    /* 0x30 */ s16 unk30;
    /* 0x32 */ s16 unk32;
    /* 0x34 */ s16 unk34;
    /* 0x36 */ s16 unk36;
    /* 0x38 */ s16 unk38;
    /* 0x3A */ s16 unk3A;
    /* 0x3C */ s8 unk3C;
    /* 0x40 */ f32 unk40;
    /* 0x44 */ s16 unk44;
    /* 0x46 */ s16 unk46;
    /* 0x48 */ s32 unk48;
};

extern f32 D_800A5470;
extern f32 D_800A5474;

void func_15153F18(struct conker15142180 *a0, struct vec15142180 *a1, s32 a2, s32 a3, s32 a4);

void func_15142180(u8 arg0, struct vec15142180 *arg1, s32 arg2, f32 arg3, f32 arg4) {
    struct conker15142180 sp24;

    sp24.unk08 = *arg1;
    sp24.unk2C = 3;
    sp24.unk2E = 3;
    sp24.unk02 = 0xFF;
    sp24.unk04 = -0x19;
    sp24.unk06 = 0xA;
    sp24.unk14 = 2.5f * arg3;
    sp24.unk18 = (1.0f + 1.0f) * arg3;
    sp24.unk1C = D_800A5470;
    sp24.unk20 = D_800A5474;
    sp24.unk24 = 3.0f * arg4;
    sp24.unk28 = 3.5f * arg4;
    sp24.unk00 = 0;
    sp24.unk30 = 3;
    sp24.unk32 = 1;
    sp24.unk34 = 9;
    sp24.unk36 = 0xF;
    sp24.unk38 = 0xB4;
    sp24.unk3A = 0x4B;
    sp24.unk40 = 0.0f;
    sp24.unk44 = 0xC;
    sp24.unk46 = 0x15;
    sp24.unk48 = arg2;
    sp24.unk3C = arg0;
    func_15153F18(&sp24, &sp24.unk08, 0, 0xFF, 1);
}

s32 func_151422C0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    return (arg3 + arg2) >> 1;
}

s32 func_151422DC(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    return arg4;
}

s32 func_151422F8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    return arg4;
}

void func_15142314(Mtx *arg0, s32 arg1, f32 *arg2) {
    if (D_800C3E90 != 0) {
        s16 *ip = (s16 *)((s32)arg0 + arg1 * 0x40);
        arg2[0] = ((f32)(ip[0xC] << 16) + (f32)ip[0x1C]) * (1.0f / 65536.0f);
        arg2[1] = ((f32)(ip[0xD] << 16) + (f32)ip[0x1D]) * (1.0f / 65536.0f);
        arg2[2] = ((f32)(ip[0xE] << 16) + (f32)ip[0x1E]) * (1.0f / 65536.0f);
    } else {
        f32 *fp = (f32 *)((s32)arg0 + arg1 * 0x40);
        arg2[0] = fp[0xC];
        arg2[1] = fp[0xD];
        arg2[2] = fp[0xE];
    }
}
f32 func_151423D8(u8 arg0) {
    s32 temp_v1;
    s32 temp_v0 = arg0;
    u16 temp_t0;
    if (temp_v0 & 0x40) {
        temp_v1 = 0x40 - (temp_v0 & 0x3F);
    } else {
        temp_v1 = temp_v0 & 0x3F;
    }
    temp_t0 = temp_v0 & 0xC0;
    if ((temp_t0 == 0) || (temp_t0 == 0xC0)) {
        return D_8009A220[temp_v1];
    }
    return -D_8009A220[temp_v1];
}
struct127 *func_15142444(u8 arg0, struct127 *arg1) {
    s32 temp_v0;
    struct127 *ret;

    temp_v0 = arg0;
    if (temp_v0 == 0xFF) {
        if (arg1->unk1D4 != NULL) {
            return arg1;
        }
        return NULL;
    }

    if ((arg1 != NULL) && (arg1->interaction_state != 0) && (temp_v0 == arg1->unique_id)) {
        if (arg1->unk1D4 != NULL) {
            return arg1;
        }
        return NULL;
    }

    ret = func_15083E90();
    if ((ret != NULL) && (ret->unk1D4 != NULL)) {
        return ret;
    }
    return NULL;
}
void func_150A8050(f32 (*)[4], f32, f32, f32);

void func_151424F4(Mtx *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, f32 arg10, f32 arg11) {
    f32 sp28[4][4];

    func_150A8050(&sp28, arg3, arg4, arg5);
    sp28[3][0] = arg9;
    sp28[3][1] = arg10;
    sp28[3][2] = arg11;
    sp28[0][0] *= arg6 * arg1;
    sp28[0][1] *= arg7 * arg1;
    sp28[0][2] *= arg8 * arg1;
    sp28[1][0] *= arg6 * arg2;
    sp28[1][1] *= arg7 * arg2;
    sp28[1][2] *= arg8 * arg2;
    sp28[2][0] *= arg6 * arg1;
    sp28[2][1] *= arg7 * arg1;
    sp28[2][2] *= arg8 * arg1;
    guMtxF2L(&sp28, arg0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15142600.s")
void func_15142838(Mtx *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8) {
    f32 mtx[4][4];

    func_150A8050(mtx, arg3, arg4, arg5);
    mtx[3][0] = arg6;
    mtx[3][1] = arg7;
    mtx[3][2] = arg8;
    mtx[0][0] *= arg1;
    mtx[0][1] *= arg1;
    mtx[0][2] *= arg1;
    mtx[1][0] *= arg2;
    mtx[1][1] *= arg2;
    mtx[1][2] *= arg2;
    mtx[2][0] *= arg1;
    mtx[2][1] *= arg1;
    mtx[2][2] *= arg1;
    guMtxF2L(mtx, arg0);
}
void func_15142914(f32 mtx[4][4], f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8) {
    func_150A8050(mtx, arg3, arg4, arg5);
    mtx[3][0] = arg6;
    mtx[3][1] = arg7;
    mtx[3][2] = arg8;
    mtx[0][0] *= arg1;
    mtx[0][1] *= arg1;
    mtx[0][2] *= arg1;
    mtx[1][0] *= arg2;
    mtx[1][1] *= arg2;
    mtx[1][2] *= arg2;
    mtx[2][0] *= arg1;
    mtx[2][1] *= arg1;
    mtx[2][2] *= arg1;
}
void func_151429E0(u8 arg0, u8 *arg1, u8 *arg2, u8 *arg3) {
    u8 *temp_v1;

    temp_v1 = &D_8008A160[((func_150ADA20() & 3) * 3) + (arg0 * 0xC)];
    *arg1 = temp_v1[0];
    *arg2 = temp_v1[1];
    *arg3 = temp_v1[2];
}
s32 func_15142A5C(struct127 *arg0) {
    void *temp_v0 = arg0->unk2D0;
    s32 ret = 0;

    if (*(s16 *)((s32)temp_v0 + 0x3C) > 0) {
        return 1;
    }
    return ret;
}
f32 func_15142A80(f32 arg0) {
    return ((1.0f - arg0) * (arg0 - 2.0f) * arg0) * D_800A5624;
}
f32 func_15142AC0(f32 arg0) {
    return ((arg0 + 1.0f) * (arg0 - 1.0f) * (arg0 - 2.0f)) * 0.5f;
}
f32 func_15142B04(f32 arg0) {
    return ((2.0f - arg0) * (arg0 + 1.0f) * arg0) * 0.5f;
}
f32 func_15142B44(f32 arg0) {
    return ((arg0 + 1.0f) * (arg0 - 1.0f) * arg0) * D_800A5628;
}
Gfx *func_15142B7C(Gfx *gfx, s32 arg1, s32 arg2) {
    if (~D_800DD200 & arg2) {
        gSPClearGeometryMode(gfx++, arg2);
        D_800DD200 |= arg2;
    }

    if (~D_800DD1FC & arg1) {
        gSPSetGeometryMode(gfx++, arg1);
        D_800DD1FC |= arg1;
    }

    return gfx;
}
Gfx *func_15142C10(Gfx *gfx, s32 arg1, s32 arg2, s32 arg3, s32 arg4, u8 *arg5) {
    if ((arg1 != (&D_800DD1C8)[0]) || (arg2 != D_800DD1CA) || (arg3 != D_800DD1CC) ||
        (arg4 != D_800DD1CE)) {
        if (*arg5 == 1) {
            gDPPipeSync(gfx++);
            *arg5 = 0;
        }

        gDPSetEnvColor(gfx++, arg1, arg2, arg3, arg4);

        (&D_800DD1C8)[0] = arg1;
        D_800DD1CA = arg2;
        D_800DD1CC = arg3;
        D_800DD1CE = arg4;
    }

    return gfx;
}
Gfx *func_15142CF0(Gfx *gfx, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, u8 *arg7) {
    if ((arg1 != (&D_800DD204)[0]) || (arg2 != D_800DD206) || (arg3 != D_800DD1C0) ||
        (arg4 != D_800DD1C2) || (arg5 != D_800DD1C4) || (arg6 != D_800DD1C6)) {
        if (*arg7 == 1) {
            gDPPipeSync(gfx++);
            *arg7 = 0;
        }

        gDPSetPrimColor(gfx++, arg1, arg2, arg3, arg4, arg5, arg6);

        (&D_800DD204)[0] = arg1;
        D_800DD206 = arg2;
        D_800DD1C0 = arg3;
        D_800DD1C2 = arg4;
        D_800DD1C4 = arg5;
        D_800DD1C6 = arg6;
    }

    return gfx;
}
Gfx *func_15142E24(Gfx *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, u8 arg7, s32 arg8, u8 *arg9, s32 argA) {
    s32 temp_v0;

    temp_v0 = func_1514306C(arg1, arg6, arg2 >> 16, arg7);
    if ((temp_v0 != D_800DD1B0) || (arg3 != D_800DD208) || (arg4 != D_800DD20C) || (arg5 != D_800DD210) || (arg8 != D_800DD214)) {
        if (*arg9 == 1) {
            *arg9 = 0;
        }
        if ((D_800BE9F0 == 0x18) || (D_800BE9F0 == 0x13) || (D_800BE9F0 == 6) || (D_800BE9F0 == 0x3B) || (D_800BE9F0 == 2) || (D_800BE616 != 0)) {
            argA = 3;
        }
        arg0 = func_15094FE8(arg0, arg1, arg2 >> 8, arg8, 0, 0, 0, arg3, arg4, arg5, argA);
        D_800DD1B0 = temp_v0;
        D_800DD208 = arg3;
        D_800DD20C = arg4;
        D_800DD210 = arg5;
        D_800DD214 = D_800DD214;
    }
    return arg0;
}
Gfx *func_15142FBC(Gfx *gfx, s32 arg1, s32 arg2, u8 *arg3) {
    if ((arg1 != D_800DD218) || (arg2 != D_800DD21C)) {
        if (*arg3 == 1) {
            gDPPipeSync(gfx++);
            *arg3 = 0;
        }

        gDPSetOtherMode(gfx++, arg1 | 0xF, arg2);

        D_800DD218 = arg1;
        D_800DD21C = arg2;
    }

    return gfx;
}
s16 func_15143044(u8 arg0, s32 arg1) {
    return 0x7FFF - arg0;
}
// BLOCKED: jump table. Logic matches (got 1160->920 with case-6 polarity fixed) but the IDO-generated
// jump table is an anonymous .rodata local vs the target's named jtbl_800A562C, which asm-differ counts
// as a large diff. Reconstruction (switch arg3 1..6): 1:D_800915B0 2:D_80091514 3:0 4:D_80091564[arg1]
// 5:arg1 6:{x=*(s32*)arg0; (u32)x>=0x10000000 ? ((s32*)x)[arg2] : x} default:D_80090B60[arg1].unk0[arg2]
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_1514306C.s")
void func_15143134(struct17 *arg0, f32 *arg1, Mtx *arg2) {
    f32 sp38[4][4];

    D_800DCA00 = 1;
    if ((arg0 != NULL) && ((arg0->unk0 != 0.0f) || (arg0->unk4 != 0.0f) || (arg0->unk8 != 0.0f))) {
        D_800DCA00 = 2;
        D_800DCA08 = arg0->unk0;
        D_800DCA0C = arg0->unk4;
        D_800DCA10 = arg0->unk8;
        if (D_800C3E90) {
            D_800DCA00 = 3;
            D_800DCA04 = arg2;
            guMtxL2F(sp38, arg2);
            func_150A7960(sp38[0], arg0->unk0, arg0->unk4, arg0->unk8, arg1, arg1 + 1, arg1 + 2);
            D_800DCA00 = 4;
        state4_done:
            ;
        } else {
            D_800DCA00 = 5;
            D_800DCA04 = arg2;
            func_150A7960((f32 *)arg2, arg0->unk0, arg0->unk4, arg0->unk8, arg1, arg1 + 1, arg1 + 2);
            D_800DCA00 = 6;
        }
    } else {
        D_800DCA00 = 7;
        func_15142314(arg2, 0, arg1);
        D_800DCA00 = 8;
    }
    D_800DCA00 = 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_151432BC.s")

// void func_151432BC(struct208 *arg0, f32 *arg1, f32 *arg2, f32 *arg3, f32 *arg4) {
//     struct209 tmp;
//     f32 temp_f2;
//     f32 temp_f6;
//     f32 temp_ret;
//     s32 temp_t6;
//     u8 temp_a0;
//
//     temp_t6 = (arg0->unk15) & 3;
//     if (temp_t6 == 0) {
//         tmp.unk1B = func_150ADA20();
//         tmp.unk14 = func_151423D8((tmp.unk1B - 64) & 0xFF);
//         tmp.unk10 = func_151423D8(tmp.unk1B);
//         temp_ret = func_150ADA68();
//         temp_f2 = temp_ret * arg0->unk6;
//         *arg1 = (arg0->unk0 + (temp_f2 * tmp.unk10));
//         *arg2 = (arg0->unk4 - (temp_f2 * tmp.unk14));
//         *arg3 = (arg0->unk2 + arg0->unk8);
//         *arg4 = arg0->unk2;
//     } else if (temp_t6 != 1) {
//         if (temp_t6 == 2) {
//             tmp.unk2F = (u32) (arg0->unk10 * D_800A5644); // 0.7111111283302307
//             tmp.unk28 = func_151423D8((tmp.unk2F - 64));
//             tmp.unk24 = func_151423D8(tmp.unk2F);
//             tmp.unk20 = (func_150ADA68() * (2.0f * (f32) arg0->unk6)) + (f32) -(s32) arg0->unk6;
//             temp_f2 = (func_150ADA68() * (2.0f * (f32) arg0->unkA)) + (f32) -(s32) arg0->unkA;
//             temp_f6 = temp_f2 * tmp.unk24;
//             *arg1 = (arg0->unk0 + ((tmp.unk20 * tmp.unk24) + (temp_f2 * tmp.unk28)));
//             *arg2 = (arg0->unk4 + (temp_f6 - (tmp.unk20 * tmp.unk28)));
//             *arg3 = (arg0->unk2 + arg0->unk8);
//             *arg4 = arg0->unk2;
//         } else {
//             *arg1 = arg0->unk0;
//             *arg2 = arg0->unk4;
//             *arg3 = (arg0->unk2 + arg0->unk8);
//             *arg4 = (arg0->unk2 - arg0->unk8);
//         }
//     } else {
//         tmp.unkB = func_150ADA20();
//         tmp.unk4 = func_151423D8((tmp.unkB - 64));
//         tmp.unk0 = func_151423D8(tmp.unkB);
//         temp_ret = func_150ADA68();
//         temp_f2 = temp_ret * (f32) arg0->unk6;
//         *arg1 = (arg0->unk0 + (temp_f2 * tmp.unk0));
//         *arg2 = (arg0->unk4 - (temp_f2 * tmp.unk4));
//         *arg3 = (arg0->unk2 + arg0->unk8);
//         *arg4 = (arg0->unk2 - arg0->unk8);
//     }
// }


void func_151436B4(f32 arg0, f32 arg1, f32 arg2, f32 *arg3) {
    f32 cos0;
    f32 sin0;
    f32 cos1;
    f32 sin1;
    f32 temp;

    cos0 = cosf(arg0);
    sin0 = sinf(arg0);
    cos1 = cosf(arg1);
    sin1 = sinf(arg1);
    temp = arg2 * cos1;
    arg3[0] = temp * sin0;
    arg3[1] = -arg2 * sin1;
    arg3[2] = temp * cos0;
}
void func_1514373C(f32 arg0, f32 arg1, f32 *arg2, f32 *arg3) {
    f32 c;
    f32 s;

    c = cosf(arg0);
    s = sinf(arg0);
    *arg2 = arg1 * s;
    *arg3 = arg1 * c;
}
void func_15143794(s32 arg0, s32 arg1, f32 arg2, f32 *arg3) {
    f32 cos0;
    f32 sin0;
    f32 cos1;
    f32 sin1;
    u8 idx0;
    u8 idx1;
    f32 temp;

    cos0 = func_151423D8((u8) arg0);
    idx0 = (s16) arg0 - 0x40;
    sin0 = func_151423D8(idx0);
    cos1 = func_151423D8((u8) arg1);
    idx1 = (s16) arg1 - 0x40;
    sin1 = func_151423D8(idx1);
    temp = arg2 * cos1;
    arg3[0] = temp * sin0;
    arg3[1] = -arg2 * sin1;
    arg3[2] = temp * cos0;
}
void func_15143834(s16 arg0, s16 arg1, f32 arg2, f32 *arg3) {
    func_15143794(arg0, arg1, arg2, arg3);
}
void func_15143874(s32 arg0, f32 arg1, f32 *arg2, f32 *arg3) {
    f32 temp;
    f32 temp2;
    u8 idx;

    temp = func_151423D8((u8) arg0);
    idx = (s16) arg0 - 0x40;
    temp2 = func_151423D8(idx);
    *arg2 = arg1 * temp2;
    *arg3 = arg1 * temp;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_151438D8.s")
// PERMUTER CANDIDATE, best 100 (JUSTREG: byte-identical ops; target uses v1/a1 where IDO picks v0/v1)
// permuter NO ZERO, best 100
// void func_15143D18(s32 *arg0, s32 *arg1, s32 arg2, s32 arg3) {
//     if (arg3 < arg2) { s32 t = arg2 ^ arg3; s32 t2 = arg3 ^ t; arg3 = t2; arg2 = t ^ t2; }
//     if (*arg1 < *arg0) { *arg0 = *arg0 ^ *arg1; *arg1 = *arg1 ^ *arg0; *arg0 = *arg0 ^ *arg1; }
//     if (*arg0 < arg2) { *arg0 = arg2; }
//     if (arg3 < *arg1) { *arg1 = arg3; }
// }
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15143D18.s")
s32 func_15143DA8(s32 *arg0, s32 arg1, s32 arg2) {
    s32 **pp = &arg0;
    s32 t;
    s32 t2;
    if (arg2 < arg1) {
        t = arg1 ^ arg2;
        t2 = arg2 ^ t;
        arg2 = t2;
        arg1 = t ^ t2;
    }
    if (**pp < arg1) {
        **pp = arg1;
        return 1;
    }
    if (arg2 < **pp) {
        **pp = arg2;
        return 2;
    }
    return 0;
}

s32 func_15143E08(struct127 *arg0) {
    return (((s32) arg0->unk7A >> 8) + 64) & 0xFF;
}

s32 func_15143E24(struct127 *arg0) {
    struct126 *temp_v1 = arg0->unk31C;
    if (temp_v1 != NULL) {
        return (s16)((arg0->unk7A - temp_v1->unk12) >> 8);
    }
    return (s16)(arg0->unk7A >> 8);
}
f32 func_15143E64(struct17 *arg0) {
    f32 x = arg0->unk0;
    f32 y = arg0->unk4;
    f32 z = arg0->unk8;

    return sqrtf(x * x + y * y + z * z);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15143E94.s")
extern u8 D_80090B64[];

// PERMUTER CANDIDATE, best 120 (JUSTREG: byte-perfect ops, 23 register renames, no structural diffs).
// Full reconstruction below (loop temp lands in $a0, target uses $t5; return-val/max reg pairing).
// permuter NO ZERO, best 45 (2x600s, improved from 120/55, no zero)
// s32 func_1514401C(u8 arg0, s32 *arg1, s32 *arg2, u8 arg3) {
//     s32 v1 = 0;
//     s32 b = D_80090B64[arg0 * 12];
//     s32 max = (b << 16) - 1;
//     s32 t5;
//     s32 t1 = (*arg2 += *arg1 * D_800BE9E4);
//     if (max < t1) {
//         if (arg3 & 1) { v1 = 1; }
//         else if (arg3 & 2) { *arg1 = 0; *arg2 = max; }
//         else if (arg3 & 4) { *arg2 = max - (t1 % max); *arg1 = -*arg1; }
//         else { do { t5 = t1 - max; *arg2 = t5; t1 = t5; } while (max < t5); }
//     } else if ((t1 < 0) && ((arg3 & 8) == 0)) {
//         if (arg3 & 0x10) { *arg1 = 0; *arg2 = 0; }
//         else if (arg3 & 4) { *arg2 = (-t1) % max; *arg1 = -*arg1; }
//         else { do { t5 = t1 + max; *arg2 = t5; t1 = t5; } while (t5 < 0); }
//     }
//     return v1;
// }
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_1514401C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_151441A4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_151442FC.s")
s32 func_151444DC(s32 arg0, s32 arg1, s32 arg2) {
    s32 range;
    if (arg1 < arg0) {
        range = arg1 - arg2 + 1;
        do {
            arg0 -= range;
        } while (arg1 < arg0);
    }
    if (arg0 < arg2) {
        range = arg1 - arg2 + 1;
        do {
            arg0 += range;
        } while (arg0 < arg2);
    }
    return arg0;
}
f32 func_15144528(f32 arg0, f32 arg1, f32 arg2) {
    f32 temp;

    if (arg1 < arg0) {
        temp = arg1 - arg2;
        do {
            arg0 -= temp;
        } while (arg1 < arg0);
    }
    if (arg0 < arg2) {
        temp = arg1 - arg2;
        do {
            arg0 += temp;
        } while (arg0 < arg2);
    }
    return arg0;
}
f32 func_15144598(struct134 *arg0) {
    f32 temp_f2;
    s16 temp_v0;
    s32 temp_t6;

    temp_t6 = *((u8 *)arg0 + 0x15) & 3;
    switch (temp_t6) {
    default:
        temp_f2 = 1.0f;
        break;
    case 2:
        temp_f2 = (f32)((s16)arg0->unk6 * (s16)arg0->unkA) * 4.0f;
        break;
    case 0:
    case 1:
        temp_v0 = (s16)arg0->unk6;
        temp_f2 = (f32)(temp_v0 * temp_v0) * D_800A5694;
        break;
    }
    return temp_f2;
}
f32 func_1514462C(s32 arg0) {
    struct169 *temp_a0;
    s32 temp_t6;
    f32 temp_f2;
    f32 temp_f0;

    temp_a0 = (struct169 *)arg0;
    temp_t6 = temp_a0->unk15 & 3;
    switch (temp_t6) {
    default:
        temp_f2 = 1.0f;
        break;
    case 2:
        temp_f2 = (f32)(temp_a0->unk6 * temp_a0->unk8 * temp_a0->unkA);
        break;
    case 0:
        temp_f2 = (f32)(temp_a0->unk6 * temp_a0->unk6) * D_800A5698 * (f32)temp_a0->unk8;
        break;
    case 1:
        temp_f0 = (f32)temp_a0->unk6;
        temp_f2 = ((temp_f0 * D_800A569C) * temp_f0) * temp_f0;
        break;
    }
    return temp_f2;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_1514470C.s")
f32 func_15144A74(struct17 *arg0, struct17 *arg1) {
    return arg0->unk0 * arg1->unk0 + arg0->unk4 * arg1->unk4 + arg0->unk8 * arg1->unk8;
}
f32 func_15144AA8(s32 arg0) {
    f32 v = D_800DBFF0[arg0].unk380;
    if (360.0f < v) {
        do {
            v -= 360.0f;
        } while (360.0f < v);
    }
    if (v < 0.0f) {
        do {
            v += 360.0f;
        } while (v < 0.0f);
    }
    return v;
}
struct17 *func_15144B34(s32 arg0) {
    return (struct17 *)&D_800DBFF0[arg0].unk2F8;
}
f32 func_15144B68(f32 arg0);
extern f32 D_800A56A4;
f32 func_15144B68(f32 arg0)
{
  f32 new_var;
  new_var = D_800A56A4;
  if (1)
  {
    f32 v = arg0;
    if (new_var < v)
    {
      do
      {
        v -= new_var;
      }
      while (new_var < v);
    }
    if (v < 0.0f)
    {
      do
      {
        v += new_var;
      }
      while (v < 0.0f);
    }
    return v;
  }
}

f32 func_15144BC8(f32 arg0) {
    f32 v = arg0;
    if (360.0f < v) {
        do {
            v -= 360.0f;
        } while (360.0f < v);
    }
    if (v < 0.0f) {
        do {
            v += 360.0f;
        } while (v < 0.0f);
    }
    return v;
}

s32 func_15144C2C(s16 arg0) {
    s16 tmp1 = arg0;

    while (tmp1 >= 256)
    {
        tmp1 -= 255;
    }
    while (tmp1 < 0)
    {
        tmp1 += 255;
    }

    return tmp1;
}

f32 func_15144C8C(f32 arg0, f32 arg1) {
    f32 tmp;

    arg0 = func_15144B68(arg0);
    tmp = fabsf(arg0 - func_15144B68(arg1));
    if (D_800A56A8 < tmp) {
        tmp = D_800A56AC - tmp;
    }
    return tmp;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15144CEC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15144E80.s")

void func_151450B4(struct17 *arg0, struct17 *arg1, struct17 *arg2) {
    arg2->unk0 = arg0->unk4 * arg1->unk8 - arg0->unk8 * arg1->unk4;
    arg2->unk4 = arg0->unk8 * arg1->unk0 - arg0->unk0 * arg1->unk8;
    arg2->unk8 = arg0->unk0 * arg1->unk4 - arg0->unk4 * arg1->unk0;
}

s32 func_15145128(struct17 *arg0, struct17 *arg1, f32 *arg2, f32 *arg3) {
    f32 sq;
    f32 sp0;

    if (arg3 != 0) {
    } else {
        arg3 = &sp0;
    }
    sq = arg0->unk0 * arg0->unk0 + arg0->unk4 * arg0->unk4 + arg0->unk8 * arg0->unk8;
    if (sq == 0.0f) {
        return 0;
    }
    if (arg2 != 0) {
        *arg2 = sqrtf(sq);
        *arg3 = 1.0f / sqrtf(sq);
    } else {
        *arg3 = 1.0f / sqrtf(sq);
    }
    arg1->unk0 = *arg3 * arg0->unk0;
    arg1->unk4 = *arg3 * arg0->unk4;
    arg1->unk8 = *arg3 * arg0->unk8;
    return 1;
}
s32 func_151452C4(struct17 *arg0, struct17 *arg1, struct17 *arg2, f32 arg3, struct17 *arg4, struct17 *arg5, f32 *arg6, f32 *arg7);

s32 func_151451F0(struct17 *arg0, struct17 *arg1, struct17 *arg2, f32 arg3, f32 arg4, struct17 *arg5, struct17 *arg6, f32 *arg7, f32 *arg8) {
    f32 temp_f0;

    if (func_151452C4(arg0, arg1, arg2, arg3, arg5, arg6, arg7, arg8) != 0) {
        temp_f0 = *arg7;
        if (temp_f0 < 0.0f) {
            if (*arg8 < 0.0f) {
                return 0;
            }
        }
        if (0.0f <= temp_f0) {
            if (*arg8 < 0.0f) {
                return 1;
            }
        }
        if (temp_f0 < arg4) {
            return 1;
        }
        return 0;
    }
    return 0;
}
// PERMUTER CANDIDATE, best 1637 (structure byte-perfect: every instruction corresponds in order,
// whole first ~30-instr block 3968-39c0 byte-identical, and the entire tail matches instruction-for-
// instruction). Remaining diffs are purely IDO float-register coloring (target dy=f12,dz=f14,B=f2;
// IDO gives dy=f2,dz=f12,B=f14 -- a coloring-priority swap that cascades) PLUS the target spills
// `disc` to 0x1c and reloads it before the bc1f (frame 0x70 vs 0x68, shifting all stack offsets by 4).
// Neither forceable from C (tried arg3^2-early local, *(f32*)&disc address-of spill, decl reorder,
// D-as-separate-var -- all no help). Ray-sphere intersection; args from func_151451F0's call site.
// s32 func_151452C4(struct17 *arg0, struct17 *arg1, struct17 *arg2, f32 arg3, struct17 *arg4,
//                   struct17 *arg5, f32 *arg6, f32 *arg7) {
//     struct17 sp58, sp4C, sp28; f32 dx,dy,dz,b,disc,t,f12,p0,p1;
//     dx = arg2->unk0 - arg0->unk0; dy = arg2->unk4 - arg0->unk4; dz = arg2->unk8 - arg0->unk8;
//     sp58 = *arg1; sp4C = *arg0;
//     b = dx*sp58.unk0 + dy*sp58.unk4 + dz*sp58.unk8;
//     disc = (dx*dx + dy*dy + dz*dz) - b*b;
//     if ((arg3*arg3) < disc) return 0;
//     t = sqrtf((arg3*arg3) - disc);
//     f12 = t; if (b < t) f12 = -t;
//     p0 = b - f12; p1 = b + f12;
//     arg4->unk0 = p0*sp58.unk0 + sp4C.unk0; arg4->unk4 = p0*sp58.unk4 + sp4C.unk4;
//     arg4->unk8 = p0*sp58.unk8 + sp4C.unk8; *arg6 = p0;
//     arg5->unk0 = p1*sp58.unk0 + sp4C.unk0; arg5->unk4 = p1*sp58.unk4 + sp4C.unk4;
//     arg5->unk8 = p1*sp58.unk8 + sp4C.unk8; *arg7 = p1;
//     sp28.unk0 = arg4->unk0 - arg0->unk0; sp28.unk4 = arg4->unk4 - arg0->unk4;
//     sp28.unk8 = arg4->unk8 - arg0->unk8;
//     if (func_15144A74(&sp28, arg1) < 0.0f) return 0;
//     return 1;
// }
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_151452C4.s")

s32 func_151454BC(u8 arg0, f32 arg1, struct17 *arg2) {
    f32 tmp1;
    f32 tmp2;
    f32 tmp3;
    struct17 *temp_v0;

    temp_v0 = func_15144B34(arg0);
    tmp1 = arg2->unk0 - temp_v0->unk0;
    tmp2 = arg2->unk4 - temp_v0->unk4;
    tmp3 = arg2->unk8 - temp_v0->unk8;

    if ((arg1 * arg1) < ((tmp1 * tmp1) + (tmp2 * tmp2) + (tmp3 * tmp3))) {
        return 0;
    }
    return 1;
}

s32 func_1514563C(struct17 *arg0, struct17 *arg1, struct17 *arg2, struct17 *arg3, f32 *arg4);

void func_15145548(struct17 *arg0, struct17 *arg1, struct17 *arg2, struct17 *arg3, f32 *arg4) {
    f32 sp0;

    if (arg4 != 0) {
    } else {
        arg4 = &sp0;
    }
    if (func_1514563C(arg0, arg1, arg2, arg3, arg4) != 0) {
        if (*arg4 < 0.0f) {
            *arg3 = *arg0;
        } else if (1.0f < *arg4) {
            arg3->unk0 = arg0->unk0 + arg1->unk0;
            arg3->unk4 = arg0->unk4 + arg1->unk4;
            arg3->unk8 = arg0->unk8 + arg1->unk8;
        }
    } else {
        *arg3 = *arg0;
    }
}
s32 func_1514563C(struct17 *arg0, struct17 *arg1, struct17 *arg2, struct17 *arg3, f32 *arg4) {
    f32 sp1C[1];
    f32 denom;
    f32 dot0;
    f32 dot1;

    if (arg4 == NULL) {
        arg4 = &sp1C[-3];
    }
    denom = (arg1->unk0 * arg1->unk0) + (arg1->unk4 * arg1->unk4) + (arg1->unk8 * arg1->unk8);
    if (denom == 0.0f) {
        return 0;
    }
    dot0 = (arg1->unk0 * arg0->unk0) + (arg1->unk4 * arg0->unk4) + (arg1->unk8 * arg0->unk8);
    dot1 = (arg1->unk0 * arg2->unk0) + (arg1->unk4 * arg2->unk4) + (arg1->unk8 * arg2->unk8);
    *arg4 = (dot1 - dot0) / denom;
    arg3->unk0 = arg0->unk0 + (*arg4 * arg1->unk0);
    arg3->unk4 = arg0->unk4 + (*arg4 * arg1->unk4);
    arg3->unk8 = arg0->unk8 + (*arg4 * arg1->unk8);
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15145740.s")
// NON-MATCHING: 90% there
// void func_15145740(struct127 *arg0, struct17 *arg1, struct17 *arg2, struct17 *arg3, f32 arg4) {
//     struct194 tmp;
//     f32 temp_f6;
//     s16 phi_v1;
//     s16 phi_t0;
//
//     if ((arg0->unk4 == 0x96) && ((arg0->unk31C->unk7D != 0))) {
//         phi_t0 = arg0->unk7A + arg0->unk31C->unk80;
//     } else {
//         if (arg0->unk31C != 0) {
//             phi_t0 = arg0->unk7A - arg0->unk31C->unk12;
//         } else {
//             phi_t0 = arg0->unk7A;
//         }
//     }
//     if ((arg0->unk4 == 0x96) && (arg0->unk31C->unk7D != 0)) {
//         phi_v1 = arg0->unk31C->unk82 + 1024;
//     } else {
//         phi_v1 = arg0->unk1D1 * 200;
//     }
//     tmp.unk14 = phi_t0;
//     tmp.unk10 = phi_v1 * 0.005493164f;
//     tmp.unk0 = tmp.unk10 * D_800A56B4;
//     func_1505A184(phi_t0, 2000.0f, tmp.unk10, &arg1->unk0, &arg1->unk8, &arg1->unk4);
//     if (arg2 != 0) {
//         arg2->unk4 = cosf(tmp.unk0) * 1000.0f;
//         temp_f6 = sinf(tmp.unk0) * 1000.0f;
//         tmp.unk8 = temp_f6;
//         tmp.unk4 = phi_t0 * D_800A56B8;
//         arg2->unk0 = cosf(tmp.unk4) * tmp.unk8;
//         arg2->unk8 = sinf(tmp.unk4) * -temp_f6;
//         if (arg3 != 0) {
//             tmp.unkC = tmp.unk0 + arg4;
//             arg3->unk4 = cosf(tmp.unkC) * 1000.0f;
//             tmp.unk8 = sinf(tmp.unkC) * 1000.0f;
//             arg3->unk0 = cosf(tmp.unk4) * tmp.unk8;
//             arg3->unk8 = sinf(tmp.unk4) * -tmp.unk8;
//         }
//     }
// }

void func_15145974(struct17 *arg0, f32 *arg1, f32 *arg2) {
    *arg1 = func_150484A0(arg0->unk0, arg0->unk8) * D_800A56BC;
    if (arg2 != NULL) {
        *arg2 = (func_150484A0(sqrtf(arg0->unk0 * arg0->unk0 + arg0->unk8 * arg0->unk8), arg0->unk4) * D_800A56C0) - 90.0f;
    }
}

f32 func_15145A0C(f32 arg0, f32 arg1, f32 arg2) {
    return D_800A548C[(s32)(arg0 * arg2 * 100.0f)] * arg1;
}


void func_15145A50(struct127 *arg0) {
    arg0->unk5 = 3;
    if (D_800BE9F0 != 51) {
        if ((D_800BE616 != 0) || (arg0->interaction_state == 5) || (arg0->interaction_state == 1) || (arg0->interaction_state == 21)) {
            arg0->interaction_state = 5;
            if (arg0->unk31C != NULL) {
                arg0->unk31C->unk78 = 0;
            }
        } else {
            func_15053694(arg0);
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15145AD8.s")

u8 func_15145C90(s32 arg0) {
    if (arg0 < 0) {
        return 1;
    } else {
        return (D_800DBEF4[arg0].unk6F & 0x80) == 0x80;
    }
}

// PERMUTER CANDIDATE, best 1982 (loop body byte-identical; target coalesces arg0/arg1 into one saved
// reg by spilling arg1 to its home, IDO keeps both -> one extra saved reg cascade). Reconstruction:
// struct s15145CD0 { f32 unk0,unk4,unk8; s16 padC,padE,unk10,unk12,unk14; };
// void func_15145CD0(struct s15145CD0 *a0, struct17 **a1, struct17 **a2, s32 a3) {
//     f32 m[4][4]; struct17 *v0,*v1; s32 i;
//     func_150A8050(m,a0->unk0,a0->unk4,a0->unk8);
//     m[3][0]=(f32)a0->unk10; m[3][1]=(f32)a0->unk12; m[3][2]=(f32)a0->unk14;
//     for(i=a3;i>0;i--){ v0=*a1; v1=*a2; func_150A7960(m[0],v0->unk0,v0->unk4,v0->unk8,&v1->unk0,&v1->unk4,&v1->unk8); a1++; a2++; }
// }
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15145CD0.s")
// PERMUTER CANDIDATE, best 962 (same one-extra-saved-reg cascade as func_15145CD0; loop body identical).
// Same as CD0 but flat struct17 arrays: src++ by one struct17, three dest pointers p0/p1/p2 += 3 floats.
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15145DB4.s")
// PERMUTER CANDIDATE, best 1876 (body byte-perfect, all registers match: s0=dest, s1=counter,
// s2=src, s3=matrix; loop back-edge bgtz matches). ONLY diff: target spills the pointer args a0/a1
// to their home slots (0xa0/0xa4) and reloads s2/s0 from home at each branch's loop guard, which
// fills the guard delay slot -> blez; IDO here moves a0->s2, a1->s0 directly (nothing for the guard
// delay -> blezl) + frame 0x98 vs 0xa0. Pure spill-strategy micro-decision (permuter reload-through-
// memory mutation). Reconstruction (arg0=struct17** src, arg1=struct17** dst, arg2=Mtx, arg3=count):
// void func_15145EA4(struct17 **arg0, struct17 **arg1, Mtx *arg2, s32 arg3) {
//     f32 sp5C[4][4]; struct17 *v, *dst;
//     if (D_800C3E90 != 0) {
//         guMtxL2F(sp5C, arg2);
//         while (arg3 > 0) { v = *arg0;
//             if (v && (v->unk0!=0.0f || v->unk4!=0.0f || v->unk8!=0.0f)) { dst=*arg1;
//                 func_150A7960(sp5C[0], v->unk0,v->unk4,v->unk8, &dst->unk0,&dst->unk4,&dst->unk8); }
//             else { func_15142314(arg2, 0, (f32*)*arg1); }
//             arg3--; arg0++; arg1++; }
//     } else {
//         while (arg3 > 0) { v = *arg0;
//             if (v && (v->unk0!=0.0f || v->unk4!=0.0f || v->unk8!=0.0f)) { dst=*arg1;
//                 func_150A7960((f32*)arg2, v->unk0,v->unk4,v->unk8, &dst->unk0,&dst->unk4,&dst->unk8); }
//             else { func_15142314(arg2, 0, (f32*)*arg1); }
//             arg3--; arg0++; arg1++; }
//     }
// }
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15145EA4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_15146078.s")
extern u8 D_800BE9C0;
extern u8 D_800D9BD0[][2][8];
extern s32 D_800D9E10[];
extern u8 D_800D9E20;
extern u8 D_800D9E21;
void *func_1515D914(void *, s16, s32, s32, s32, s32, s32, s32, s32, void *, s32, s32, s32, s32);
void *func_1515E544(void *, s32, u8, u8, void *);
void *func_151462C8(void *arg0, s32 *arg1, u8 arg2, void *arg3, u8 arg4, s16 arg5, struct17 *arg6, u8 arg7, s32 arg8)
{
  s32 temp_t1;
  s32 temp_t2;
  s32 temp_v1;
  s16 temp_a1;
  s32 var_t0;
  s32 var_v1;
  temp_v1 = arg5 * 4;
  temp_t1 = *((s32 *) ((((u8 *) arg1) + temp_v1) + 8));
  if (temp_t1 != 0)
  {
    temp_t2 = arg1[6];
    if (temp_t2 != 0)
    {
 do { if (arg2 == 1) { if (arg3 != 0) { if (((((*((s32 *) (((u8 *) arg3) + 0))) == 0) || (arg4 != (*(((u8 *) arg3) + 0x3B)))) || ((*(((u8 *) arg3) + 4)) == 0xFF)) || ((*(((u8 *) arg3) + 0x302)) == 0)) { arg2 = 2; } } else { arg2 = 0; } } switch (arg2) { case 1: arg0 = func_1515E544(arg0, *((s32 *) ((((u8 *) arg3) + temp_v1) + 0x304)), *(((u8 *) arg3) + 0x301), *(((u8 *) arg3) + 0x302), *((void **) (((u8 *) arg3) + 0x314))); break; case 2: arg0 = func_1515E544(arg0, D_800D9E10[arg5], D_800D9E20, D_800D9E21, D_800D9BD0[arg5][D_800BE9C0]); break; do { } while (0); case 0: default: temp_a1 = arg5; var_t0 = (arg7 & 1) ? (2) : (0); if (arg7 & 2) { var_v1 = 0x10; } else { var_v1 = 0; } arg0 = func_1515D914(arg0, temp_a1, (s32) arg6->unk0, (s32) arg6->unk4, (s32) arg6->unk8, arg8, temp_t1, arg1[0], temp_t2, arg1 + 1, arg1[7], 0, (var_v1 | 8) | var_t0, 0); break; } } while (0);
    }
  }
  return arg0;
}

extern s32 D_80082FA0;

u8 func_151464B8(s16 *arg0) {
    s32 i;
    s16 mask;
    s16 field;
    s32 ret;

    i = 0;
    mask = 0;
    for (; i <= D_80082FA0; i++) {
        mask |= 1 << i;
    }
    ret = (arg0[1] & mask) == 0;
    field = arg0[1];
    return ret;
}

void func_15146508(struct127 *arg0, struct127 *arg1) {
    struct193 tmp;

    tmp.unk0 = arg0;
    tmp.unk4 = arg1;
    tmp.unk8 = arg0->unique_id;
    tmp.unk9 = arg1->unique_id;
    func_15169040(&tmp, 45, arg0, arg1);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_16EE20/func_1514654C.s")

s32 func_1514672C(struct17 *arg0) {
    f32 temp_f2;
    f32 temp_f0;

    temp_f2 = D_800A56C4;
block_1514672C:
    if ((temp_f2 < fabsf(arg0->unk0)) || (temp_f2 < fabsf(arg0->unk8)) || (temp_f0 = arg0->unk4, (temp_f2 < temp_f0)) || (temp_f0 < D_800A56C8)) {
        return 0;
    }
    return 1;
}
// NON-MATCHING: JUSTREG: first 3 statements are out of order
// s32 func_1514672C(struct17 *arg0) {
//     if ((D_800A56C4 < fabsf(arg0->unk0)) || (D_800A56C4 < fabsf(arg0->unk8)) || (D_800A56C4 < arg0->unk4) || (arg0->unk4 < D_800A56C8)) {
//         return 0;
//     } else {
//         return 1;
//     }
// }

void func_151467A4(f32 *arg0, f32 arg1, f32 *arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 *arg7) {
    *arg0 = *arg0 - D_800BE9A4;
    if (*arg0 < 0.0f) {
        *arg0 = func_150ADA68() * arg1;
        if ((func_150ADA20() & 3) != 0) {
            *arg2 = (func_150ADA68() * (arg4 - arg3)) + arg3;
        } else {
            *arg2 = (func_150ADA68() * (arg5 - arg4)) + arg4;
        }
    }
    *arg7 = ((*arg2 - *arg7) * arg6) + *arg7;
}
