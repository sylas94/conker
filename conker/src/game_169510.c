#include <ultra64.h>

#include "functions.h"
#include "variables.h"

typedef struct {
    s32 unk0;
    u8  unk4;
    u8  unk5;
    u16 unk6;
    u16 unk8;
    u16 unkA;
} struct1513FFF4_80090B60;

typedef struct {
    u8 pad0[0x8];
    s16 unk8;
    s16 unkA;
    u8 padC[0x4];
} struct1513FFF4;

typedef struct {
    u8  pad0[6];
    u16 unk6;
    u8  pad8[4];
    s8  unkC;
    s8  unkD;
    s8  unkE;
    s8  unkF;
} Dst151400D0;

typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    u16 unk8;
} Src151400D0;

typedef struct {
    char pad_0x00[0x2C];
    f32 field_0x2C;
    f32 field_0x30;
    char pad_0x34[0xF4];
    f32 field_0x128;
} ScaleUpdateState;

extern struct1513FFF4_80090B60 D_80090B60[];
extern f32 D_800A5184;
void func_1513FFF4(struct1513FFF4 *arg0, u8 arg1, u8 arg2);
void func_151400D0(Dst151400D0 *dst, Src151400D0 *src);


typedef struct {
    u8  pad0[0x10];
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s16 unk1C;
    u8  unk1E;
    u8  pad1F[0x1];
    s32 unk20;
    s32 unk24;
    u8  unk28;
    u8  pad29[0x4];
    u8  unk2D;
    u8  pad2E[0xC];
    s16 unk3A;
    s16 unk3C;
    u8  pad3E[0x42];
    u8  unk80;
    u8  unk81;
} Anim1513C060;

extern s32 (*D_80089C70[])(Anim1513C060 *);
extern s32 (*D_80089CA8[])(Anim1513C060 *);

void func_1513C060(Anim1513C060 *arg0) {
    s32 rate;
    s8 finished;
    s32 numFrames;
    s32 limit;
    s32 temp;

    if (!(arg0->unk10 & 1)) {
        return;
    }

    finished = 0;
    if (arg0->unk18 & 1) {
        arg0->unk1C -= D_800BE9E4;
        if (arg0->unk1C < 0) {
            finished = 1;
        }
    }
    if (arg0->unk80 != 0) {
        if (D_80089C70[arg0->unk80](arg0) == 0) {
            finished = 1;
        }
    }

    if ((arg0->unk18 & 0x8000) && !finished) {
        if (arg0->unk1C < arg0->unk3A) {
            temp = arg0->unk1C * arg0->unk3C;
            if (temp < arg0->unk28) {
                arg0->unk28 = temp;
            }
        }
    }
    if (arg0->unk18 & 0x10000) {
        if (!finished) {
            if (arg0->unk1C < arg0->unk3A) {
                temp = arg0->unk1C * arg0->unk3C;
                if (temp < arg0->unk28) {
                    arg0->unk2D = temp;
                }
            }
        }
    }

    if (!finished) {
        rate = arg0->unk24;
        if (rate != 0) {
            numFrames = D_80090B60[arg0->unk1E].unk4;
            limit = (numFrames << 16) - 1;
            arg0->unk20 += rate * D_800BE9E4;
            if (limit < arg0->unk20) {
                if (arg0->unk18 & 2) {
                    finished = 1;
                } else if (arg0->unk18 & 0x40) {
                    arg0->unk24 = 0;
                    arg0->unk20 = limit;
                } else if (arg0->unk18 & 4) {
                    arg0->unk20 = limit - (arg0->unk20 % limit);
                    arg0->unk24 = -rate;
                } else {
                    do {
                        arg0->unk20 -= limit;
                    } while (limit < arg0->unk20);
                }
            } else if (arg0->unk20 < 0) {
                if (arg0->unk18 & 8) {
                    finished = 1;
                } else if (arg0->unk18 & 0x80) {
                    arg0->unk24 = 0;
                    arg0->unk20 = 0;
                } else if (arg0->unk18 & 4) {
                    arg0->unk20 = (-arg0->unk20) % limit;
                    arg0->unk24 = -rate;
                } else {
                    do {
                        arg0->unk20 += limit;
                    } while (arg0->unk20 < 0);
                }
            }
        }
    }

    if (finished) {
        if (arg0->unk81 != 0) {
            if (D_80089CA8[arg0->unk81](arg0) != 0) {
                func_1516972C(arg0);
            }
        } else {
            func_1516972C(arg0);
        }
    }
}

struct210 *func_1513C350(struct210 *arg0, s32 arg1, u8 arg2, u8 arg3, u8 arg4, s32 arg5, s32 arg6, struct167 *arg7, s32 arg8, u8 arg9, s32 argA) {
    struct210 *temp_v0;
    u8 id;
    s32 i;

    if (arg1 == 0) {
        arg1 = &D_800A4AA0;
    }
    if (arg0->unk0 & 0x40000) {
        id = 0x4A;
    } else {
        id = 0x1B;
    }
    temp_v0 = func_15167A68(id, argA, arg8 + 0xB0, 1, arg9, 1);
    if (temp_v0 == 0) {
        return NULL;
    }
    memcpy(&temp_v0->unk18.i.unk0, arg0, 0x28);
    func_1513FFF4(&temp_v0->unk40, temp_v0->unk1E, arg4);
    func_151400D0(&temp_v0->unk40, arg1);
    temp_v0->unk80 = arg2;
    temp_v0->unk81 = arg3;
    temp_v0->unk84 = arg5;
    temp_v0->unk10 = 1;
    temp_v0->unk14 = 0;
    temp_v0->unkA0 = arg6;
    for (i = 0; i < 4; i++) {
        temp_v0->unk8C[i] = 0;
    }

    temp_v0->unk9C = 0;
    if (arg5) {
        for (i = 0; i <= D_80082FA0; i++) {
            temp_v0->unk8C[i] = func_1515D480(arg5);
        }
        temp_v0->unk9C = func_1515D440();
    }
    if (arg7) {
        *(struct167 *)temp_v0->unkA4 = *arg7;
    }
    return temp_v0;
}

struct210 *func_1513C4EC(s32 arg0, s32 arg1, u8 arg2, u8 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, u8 arg9, u8 argA, s32 argB, s32 argC, s32 argD, u8 argE, s32 argF) {
    s32 temp_v0;
    struct17 tmp;

    tmp.unk0 = arg4;
    tmp.unk4 = arg5;
    tmp.unk8 = arg6;
    temp_v0 = func_1513C350(arg0, arg1, arg2, arg3, argA, argB, argC, &tmp, argD, argE, argF);
    if (temp_v0 == 0) {
        return 0;
    }
    func_1513E13C(temp_v0, arg4, arg5, arg6, arg7, arg8, arg9);
    return temp_v0;
}

struct210 *func_1513C5B0(s32 arg0, s32 arg1, u8 arg2, u8 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, u8 arg9, u8 argA, s32 argB, u8 argC, s32 argD) {
    s32 tmp = func_1513C350(arg0, arg1, arg2, arg3, argA, 0, 0, 0, argB, argC, argD);
    if (tmp == 0) {
        return 0;
    }
    func_1513E13C(tmp, arg4, arg5, arg6, arg7, arg8, arg9);
    return tmp;
}

struct210 *func_1513C650(s32 arg0, u8 arg1, u8 arg2, s32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, u8 arg9, u8 argA, s32 argB, s32 argC, s32 argD, u8 argE, s32 argF) {
    s32 temp_v0;
    struct17 tmp;

    tmp.unk0 = arg4;
    tmp.unk4 = arg5;
    tmp.unk8 = arg6;

    temp_v0 = func_1513C350(arg0, 0, arg1, arg2, argA, argB, argC, &tmp, argD, argE, argF);
    if (temp_v0 == 0) {
        return 0;
    }

    if (func_1513E2AC(temp_v0, 0, arg3, arg4, arg5, arg6, arg7, arg8, arg9) == 0) {
        func_1516972C(temp_v0);
        return 0;
    }
    return temp_v0;
}

struct210 *func_1513C73C(s32 arg0, u8 arg1, u8 arg2, s32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, u8 arg9, u8 argA, s32 argB, u8 argC, s32 argD) {
    s32 tmp = func_1513C350(arg0, 0, arg1, arg2, argA, 0, 0, 0, argB, argC, argD);
    if (tmp == 0) {
        return 0;
    }

    if (func_1513E2AC(tmp, 0, arg3, arg4, arg5, arg6, arg7, arg8, arg9) == 0) {
        func_1516972C(tmp);
        return 0;
    }
    return tmp;
}

struct210 *func_1513C804(s32 arg0, s32 arg1, u8 arg2, u8 arg3, s32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, u8 argA, u8 argB, s32 argC, u8 argD, s32 argE) {
    s32 tmp = func_1513C350(arg0, 0, arg2, arg3, argB, 0, 0, 0, argC, argD, argE);
    if (tmp == 0) {
        return 0;
    }
    if (func_1513E2AC(tmp, 0, arg4, arg5, arg6, arg7, arg8, arg9, argA) == 0) {
        func_1516972C(tmp);
        return 0;
    }
    return tmp;
}

void func_1513C8D4(struct210 *arg0) {
    func_1513C92C(arg0);
    func_15169804(arg0);
}

void func_1513C900(struct210 *arg0) {
    func_1513C92C(arg0);
    func_15169824(arg0);
}

void func_1513C92C(struct210 *arg0) {
    s32 i;

    for (i = 0; i <= D_80082FA0; i++) {
        if (arg0->unk8C[i]) {
            func_100043B4(arg0->unk8C[i], 4);
        }
    }
    if (arg0->unk9C != 0) {
        func_100043B4(arg0->unk9C, 4);
    }
}

void func_1513C9B0(struct210 *arg0) {
    s32 idx;
    if ((arg0->unk18.i.unk0 & 0x1000) != 0) {
        idx = arg0->unk1F;
    } else {
        idx = 0;
    }
    D_80089EE8[idx]();
}

void func_1513C9FC(struct210 *arg0) {
    s32 idx;
    if ((arg0->unk18.i.unk0 & 0x1000) != 0) {
        idx = arg0->unk1F;
    } else {
        idx = 0;
    }
    D_80089EF0[idx]();
}

void func_1513CA48(struct210 *arg0) {
    func_151D5E30(&arg0->unk100);
}

void func_1513CA6C(struct210 *arg0) {
    func_1513CA48(arg0);
    func_1513CAD4(arg0);
    func_15169804(arg0);
}

void func_1513CAA0(struct210 *arg0) {
    func_1513CA48(arg0);
    func_1513CAD4(arg0);
    func_15169824(arg0);
}

void func_1513CAD4(struct210 *arg0) {
    s32 i;

    for (i = 0; i <= D_80082FA0; i++) {
        if (arg0->unkA4[i]) {
            func_100043B4(arg0->unkA4[i], 4);
        }
    }
    if (arg0->unkB4 != 0) {
        func_100043B4(arg0->unkB4, 4);
    }
}

// is this really struct210?
void func_1513CB58(struct210 *arg0) {
    s32 idx;
    if ((arg0->unk58 & 0x400000) != 0) {
        idx = arg0->unk18.b.unk1; //unk19;
    } else {
        idx = 0;
    }
    D_80089EF8[idx]();
}

void func_1513CBA4(struct210 *arg0) {
    s32 idx;
    if ((arg0->unk58 & 0x400000) != 0) {
        idx = arg0->unk18.b.unk1; //unk19;
    } else {
        idx = 0;
    }
    D_80089F2C[idx]();
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_1513CBF0.s")

void func_1513CF9C(s32 arg0, s32 arg1, u8 arg2) {
    D_80089F60[0](arg0, arg1, arg2);
}

void func_1513CFD0(s32 arg0, s32 arg1, s32 arg2) {
}

typedef struct {
    u8  pad0[0x10];
    s32 unk10;
    u8  pad14[0x4];
    u8  unk18;
    u8  pad19[0x3];
    s16 unk1C;
    u8  pad1E[0x2];
    s32 unk20;
    s32 unk24;
    u8  pad28[0x3];
    u8  unk2B;
    u8  pad2C[0x2C];
    s32 unk58;
    u8  unk5C;
    u8  pad5D[0xF];
    s16 unk6C;
    s16 unk6E;
    u8  unk70;
    u8  unk71;
    u8  unk72;
} Anim1513CFE4;

extern s32 (*D_80089CB8[])(Anim1513CFE4 *);
extern s32 (*D_80089D60[])(Anim1513CFE4 *);
extern s32 (*D_80089E10[])(Anim1513CFE4 *);

void func_1513CFE4(Anim1513CFE4 *arg0) {
    s32 rate;
    s8 finished;
    s32 numFrames;
    s32 limit;
    s32 temp;

    if (!(arg0->unk10 & 1)) {
        return;
    }

    finished = 0;
    if (arg0->unk58 & 1) {
        arg0->unk1C -= D_800BE9E4;
        if (arg0->unk1C < 0) {
            finished = 1;
        }
    }
    if (arg0->unk70 != 0) {
        if (D_80089CB8[arg0->unk70](arg0) == 0) {
            finished = 1;
        }
    }
    if (arg0->unk71 != 0) {
        if (D_80089D60[arg0->unk71](arg0) == 0) {
            finished = 1;
        }
    }

    if ((arg0->unk58 & 0x8000000) && !finished) {
        if (arg0->unk1C < arg0->unk6C) {
            temp = arg0->unk1C * arg0->unk6E;
            if (temp < arg0->unk5C) {
                arg0->unk5C = temp;
            }
        }
    }
    if (arg0->unk58 & 0x10000000) {
        if (!finished) {
            if (arg0->unk1C < arg0->unk6C) {
                temp = arg0->unk1C * arg0->unk6E;
                if (temp < arg0->unk5C) {
                    arg0->unk2B = temp;
                }
            }
        }
    }

    if (!finished) {
        rate = arg0->unk24;
        if (rate != 0) {
            numFrames = D_80090B60[arg0->unk18].unk4;
            limit = (numFrames << 16) - 1;
            arg0->unk20 += rate * D_800BE9E4;
            if (limit < arg0->unk20) {
                if (arg0->unk58 & 0x800) {
                    finished = 1;
                } else if (arg0->unk58 & 0x400) {
                    arg0->unk20 = limit - (arg0->unk20 % limit);
                    arg0->unk24 = -rate;
                } else {
                    do {
                        arg0->unk20 -= limit;
                    } while (limit < arg0->unk20);
                }
            } else if (arg0->unk20 < 0) {
                if (arg0->unk58 & 0x1000) {
                    finished = 1;
                } else if (arg0->unk58 & 0x400) {
                    arg0->unk20 = (-arg0->unk20) % limit;
                    arg0->unk24 = -rate;
                } else {
                    do {
                        arg0->unk20 += limit;
                    } while (arg0->unk20 < 0);
                }
            }
        }
    }

    if (finished) {
        if (arg0->unk72 != 0) {
            if (D_80089E10[arg0->unk72](arg0) != 0) {
                finished = 0;
            }
        }
    }
    if (finished) {
        func_1516972C(arg0);
    }
}

void *func_1513D2F0(void *arg0, s32 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, u8 arg6, s32 arg7, s32 arg8, s32 arg9, u8 argA, s32 argB) {
    struct210 *temp_v0;
    s32 flags;
    s32 id;
    s32 i;

    flags = *(s32 *)((u8 *)arg0 + 0x40);
    if (flags & 0x800000) {
        id = 0x56;
    } else if (flags & 0x2000000) {
        id = 0x49;
    } else {
        id = 0x1C;
    }
    temp_v0 = func_15167A68(id, argB, arg9 + 0x110, 1, argA, (flags & 0x80000000U) ? 2 : 1);
    if (temp_v0 == NULL) {
        return NULL;
    }
    memcpy(&temp_v0->unk18.i.unk0, arg0, 0x58);
    *(u8 *)((u8 *)temp_v0 + 0x70) = arg2;
    *(u8 *)((u8 *)temp_v0 + 0x71) = arg3;
    *(u8 *)((u8 *)temp_v0 + 0x72) = arg4;
    *(u8 *)((u8 *)temp_v0 + 0x73) = arg5;
    *(u8 *)((u8 *)temp_v0 + 0x74) = 0;
    bzero(&temp_v0->unk100, 0x10);
    func_1513FFF4((struct1513FFF4 *)((u8 *)temp_v0 + 0xC0), *(u8 *)((u8 *)temp_v0 + 0x18), arg6);
    func_151400D0((Dst151400D0 *)((u8 *)temp_v0 + 0xC0), (Src151400D0 *)arg1);
    temp_v0->unk10 = 1;
    temp_v0->unk14 = 0;
    *(f32 *)((u8 *)temp_v0 + 0x78) = D_800A5184;
    *(s32 *)((u8 *)temp_v0 + 0x98) = 0;
    *(u8 *)((u8 *)temp_v0 + 0x95) = 0;
    *(u8 *)((u8 *)temp_v0 + 0x94) = 0;
    *(s32 *)((u8 *)temp_v0 + 0x90) = 0;
    *(s32 *)((u8 *)temp_v0 + 0x9C) = arg7;
    *(s32 *)((u8 *)temp_v0 + 0xB8) = arg8;
    *(u8 *)((u8 *)temp_v0 + 0xA0) = 0;
    for (i = 0; i < 4; i++) {
        temp_v0->unkA4[i] = 0;
    }

    temp_v0->unkB4 = 0;
    if (arg7) {
        for (i = 0; i <= D_80082FA0; i++) {
            temp_v0->unkA4[i] = func_1515D480(arg7);
        }
        temp_v0->unkB4 = func_1515D440();
    }
    return temp_v0;
}

void func_1513D4B8(s32 arg0, s32 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, u8 arg6, s32 arg7, u8 arg8, s32 arg9) {
    func_1513D2F0(arg0, arg1, arg2, arg3, arg4, arg5, arg6, 0, 0, arg7, arg8, arg9);
}

void func_1513D524(s32 arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, s32 arg6, u8 arg7, s32 arg8) {
    func_1513D2F0(arg0, &D_800A4AA0, arg1, arg2, arg3, arg4, arg5, 0, 0, arg6, arg7, arg8);
}

s32 func_1513D594(s32 arg0, s32 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, s16 arg6, f32 arg7, f32 arg8, s32 arg9, s32 argA, s32 argB, s32 argC, u8 argD, s32 argE, u8 argF, s32 arg10) {
    struct210 *temp_v0;

    if (arg1 == 0) {
        arg1 = &D_800A4AA0;
    }
    temp_v0 = func_1513D2F0(arg0, arg1, arg2, arg3, arg4, 0xC, arg5, argB, argC, argE + 0x18, argF, arg10);
    if ((temp_v0 != 0) && (func_1513D6FC(&temp_v0->unk110, arg6, arg7, arg8, arg9, argA, argD) == 0)) {
        func_1516972C(temp_v0);
        return 0;
    }
    return temp_v0;
}

void func_1513D668(s32 arg0, s32 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, s16 arg6, f32 arg7, f32 arg8, s32 arg9, s32 argA, u8 argB, s32 argC, u8 argD, s32 argE) {
    func_1513D594(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, argA, 0, 0, argB, argC, argD, argE);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_1513D6FC.s")
// s32 func_1513D6FC(struct211 *arg0, s16 arg1, f32 arg2, f32 arg3, s32 arg4, s32 arg5, u8 arg6) {
//     f32 spBC;
//     f32 spB8;
//     f32 spB4;
//     s32 spB0;
//     f32 spAC;
//     s32 spA8;
//     f32 spA4;
//     s32 spA0;
//     s32 sp9C;
//     s32 sp98;
//     s32 sp94;
//     s32 sp90;
//     f32 sp8C;
//     f32 sp88;
//     f32 sp84;
//     s32 sp80;
//     f32 sp7C;
//     f32 sp78;
//     f32 sp74;
//     f32 sp70;
//     f32 sp6C;
//     f32 sp68;
//     f32 sp64;
//     f32 sp60;
//     s32 sp5C;
//     s32 sp58;
//     s32 sp54; // ?
//     s32 sp50; // ?
//     s32 sp4C; // ?
//     s32 sp48; // ?
//     s32 sp44; // ?
//     s32 sp40; // ?
//     s32 sp3C; // ?
//     s32 sp38; // ?
//     s32 sp34; // ?
//     s32 sp30; // ?
//     f32 sp2C;
//     f32 sp28;
//     f32 sp24;
//
//     f32 temp_f0;
//     f32 temp_f16;
//     f32 temp_f18;
//     f32 phi_f12;
//     f32 phi_f14;
//     f32 phi_f12_2;
//
//     if (arg6 != 0) {
//         spB4 = func_151423D8(arg1 - 64);
//         temp_f0 = func_151423D8(arg1);
//         spAC = arg2 * temp_f0;
//         spA4 = arg3 * temp_f0;
//         if (func_1510E388(arg4, arg5, &spBC, &spB8) == 0) {
//             return 0;
//         }
//         temp_f18 = spA4 * spB8;
//         sp2C = fabsf(spA4);
//         temp_f16 = arg3 * spB4;
//         sp28 = sqrtf((spA4 * spA4) + (temp_f18 * temp_f18));
//         if (temp_f16 != 0.0f) {
//             sp8C = temp_f16 * spBC;
//             sp88 = fabsf(temp_f16) / sqrtf((temp_f16 * temp_f16) + (sp8C * sp8C));
//         } else {
//             sp8C = 0.0f;
//             sp88 = 0.0f;
//         }
//         if (spA4 != 0.0f) {
//             sp84 = temp_f18;
//             phi_f12 = sp2C / sp28;
//         } else {
//             sp84 = 0.0f;
//             phi_f12 = 0.0f;
//         }
//         arg0->unk0 = sp88 * temp_f16;
//         arg0->unk8 = phi_f12 * spA4;
//         arg0->unk4 = (sp88 * sp8C) + (phi_f12 * sp84) + 0.5f;
//         temp_f18 = -(arg2 * spB4);
//         temp_f16 = temp_f18 * spB8;
//         sp28 = fabsf(temp_f18);
//         sp2C = temp_f16;
//         sp24 = sqrtf((temp_f18 * temp_f18) + (temp_f16 * temp_f16));
//         if (spAC != 0.0f) {
//             temp_f0 = spAC * spBC;
//             sp8C = temp_f0;
//             phi_f14 = fabsf(spAC) / sqrtf((spAC * spAC) + (temp_f0 * temp_f0));
//         } else {
//             sp8C = 0.0f;
//             sp88 = 0.0f;
//             phi_f14 = 0.0f;
//         }
//         if (temp_f18 != 0.0f) {
//             sp84 = sp2C;
//             phi_f12_2 = sp28 / sp24;
//         } else {
//             sp84 = 0.0f;
//             phi_f12_2 = 0.0f;
//         }
//         arg0->unkC = phi_f14 * spAC;
//         arg0->unk14 = phi_f12_2 * temp_f18;
//         arg0->unk10 = (phi_f14 * sp8C) + (phi_f12_2 * sp84) + 0.5f;
//     } else {
//         sp7C = func_151423D8(arg1 - 64);
//         sp78 = func_151423D8(arg1);
//         if (func_15144E80(arg5, &sp6C, &sp60, &sp54) == 0) {
//             return 0;
//         }
//         if (func_15145128(&sp6C, &sp6C, &sp50, &sp4C) == 0) {
//             return 0;
//         }
//         if (func_15145128(&sp60, &sp60, &sp50, &sp4C) == 0) {
//             return 0;
//         }
//         temp_f0 = arg2 * sp78;
//         temp_f18 = arg2 * sp7C;
//         arg0->unk0 = (temp_f0 * sp6C) + (temp_f18 * sp60);
//         arg0->unk4 = (temp_f0 * sp70) + (temp_f18 * sp64);
//         arg0->unk8 = (temp_f0 * sp74) + (temp_f18 * sp68);
//         temp_f0 = -arg3 * sp7C;
//         temp_f18 = arg3 * sp78;
//         arg0->unkC = (temp_f0 * sp6C) + (temp_f18 * sp60);
//         arg0->unk10 = (temp_f0 * sp70) + (temp_f18 * sp64);
//         arg0->unk14 = (temp_f0 * sp74) + (temp_f18 * sp68);
//     }
//     return 1;
// }

#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_1513DB00.s")

// jump table
#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_1513DF9C.s")

void func_1513E070(s32 arg0, s32 arg1, s32 arg2) {
}

void func_1513E084(struct210 *arg0, struct212 *arg1, u8 arg2) {
    struct212 *temp_v0 = &arg0->unk110;
    if (arg2 == 0x1A) {
        if ((temp_v0->unk0 == arg1->unk0) || (temp_v0->unk4.b.unk0 == arg1->unk4.b.unk0)) {
            func_1516972C(arg0);
        }
    } else {
        temp_v0 = &arg0->unk110;
        if (arg2 == 0x2D) {
            if (temp_v0->unk0 == arg1->unk0) {
                temp_v0->unk0 = arg1->unk4.i.unk0;
                temp_v0->unk4.b.unk0 = arg1->unk9;
            } else if (temp_v0->unk0 == arg1->unk4.i.unk0) {
                temp_v0->unk0 = arg1->unk0;
                temp_v0->unk4.b.unk0 = arg1->unk8;
            }
        }
    }
}

void func_1513E134(void) {
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_1513E13C.s")
// PERMUTER CANDIDATE best 3348 — reconstruction below is semantically close (first 12 instrs match)
// but FP store scheduling + a +4 stack-slot shift on sp48/sp1C/sp30 differ.
// void func_1513E13C(struct210 *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, u8 arg6) {
//     f32 sp48; f32 sp30; f32 sp1C;
//     f32 temp_f0, temp_f12, temp_f14, temp_f16, temp_f18, temp_f2; s32 temp_f10;
//     sp48 = func_151423D8((arg6 - 0x40));
//     temp_f0 = func_151423D8(arg6);
//     temp_f12 = arg5 * sp48;
//     temp_f14 = arg4 * temp_f0;
//     temp_f18 = arg1 + temp_f14;
//     arg0->unk40 = temp_f18 - temp_f12;
//     temp_f10 = arg2;
//     arg0->unk42 = temp_f10;
//     temp_f16 = arg5 * temp_f0;
//     temp_f2 = arg4 * sp48;
//     sp1C = arg3 + temp_f16;
//     sp30 = arg1 - temp_f14;
//     arg0->unk44 = sp1C + temp_f2;
//     arg0->unk52 = temp_f10;
//     arg0->unk50 = sp30 - temp_f12;
//     arg0->unk54 = sp1C - temp_f2;
//     arg0->unk62 = temp_f10;
//     arg0->unk60 = sp30 + temp_f12;
//     arg0->unk72 = temp_f10;
//     arg0->unk70 = temp_f18 + temp_f12;
//     sp30 = arg3 - temp_f16;
//     arg0->unk64 = sp30 - temp_f2;
//     arg0->unk74 = sp30 + temp_f2;
// }

void func_1513E2A4(void) {
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_1513E2AC.s")

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
} struct_func_1513E6E8_110;

typedef struct {
    u8 pad0[0x34];
    f32 unk34;
    f32 unk38;
    f32 unk3C;
    f32 unk40;
    f32 unk44;
    f32 unk48;
    f32 unk4C;
    f32 unk50;
    f32 unk54;
    s32 unk58;
    u8 pad5C;
    u8 unk5D;
    u8 pad5E[0xB2];
    struct_func_1513E6E8_110 unk110;
} struct_func_1513E6E8;

s32 func_1513E6E8(struct_func_1513E6E8 *arg0) {
    struct_func_1513E6E8_110 *vel;

    vel = &arg0->unk110;
    if (arg0->unk58 & 0x20) {
        vel->unkC = vel->unkC + (vel->unk2C * D_800BE9A4);
    }
    if (arg0->unk58 & 0x40) {
        arg0->unk34 = arg0->unk34 + (vel->unk8 * D_800BE9A4);
        arg0->unk38 = arg0->unk38 + (vel->unkC * D_800BE9A4);
        arg0->unk3C = arg0->unk3C + (vel->unk10 * D_800BE9A4);
    }
    if (arg0->unk58 & 0x80) {
        arg0->unk40 = arg0->unk40 + (vel->unk14 * D_800BE9A4);
        arg0->unk44 = arg0->unk44 + (vel->unk18 * D_800BE9A4);
        arg0->unk48 = arg0->unk48 + (vel->unk1C * D_800BE9A4);
    }
    if (arg0->unk58 & 0x100) {
        arg0->unk4C = arg0->unk4C + (vel->unk20 * D_800BE9A4);
        arg0->unk50 = arg0->unk50 + (vel->unk24 * D_800BE9A4);
        arg0->unk54 = arg0->unk54 + (vel->unk28 * D_800BE9A4);
    }
    arg0->unk5D = 0xFF;
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_1513E83C.s")

// ???
#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_1513EAD8.s")

void func_1513EDB4(s32 arg0, s16 arg1) {
    func_1513EAD8(arg0, 0, arg1);
}

void func_1513EDE4(s32 arg0, s16 arg1) {
    func_1513EAD8(arg0, 1, arg1);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_1513EE14.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_1513F114.s")

void func_1513F4B0(struct210 *arg0, s16 arg1) {
    func_15140410(arg0, &arg0->unk110, &arg0->unk11C, arg1);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_1513F4E4.s")
// PERMUTER NO ZERO (best 730). word0 (first ~52 instrs) BYTE-PERFECT; word1's ops are
// byte-identical to target but IDO's delay-slot scheduling gives a different temp-register
// rotation from the first pair on (all `r`/reorder marks, no wrong ops). Reconstruction:
// typedef struct { u8 unk0..unkF; } CombineEntry;  // 16-byte combiner mux table entry
// extern CombineEntry D_800A4BA8[]; extern s16 D_800DD1BE; extern s16 func_15143044(u8, s32);
// Gfx *func_1513F4E4(Gfx *gfx, u8 arg1, u8 *arg2) {
//     s16 temp_v0 = func_15143044(arg1, 0);
//     if (temp_v0 != D_800DD1BE) {
//         CombineEntry *e; Gfx *g2;
//         if (arg2[0] == 1) { gDPPipeSync(gfx++); arg2[0] = 0; }
//         e = &D_800A4BA8[arg1];
//         g2 = gfx++;
//         g2->words.w0 = (((e->unkA & 0x1F) | ((e->unk8 & 0xF) << 5) | ((e->unk0 & 0xF) << 20)
//              | ((e->unk2 & 0x1F) << 15) | ((e->unk4 & 7) << 12) | ((e->unk6 & 7) << 9)) & 0xFFFFFF) | 0xFC000000;
//         g2->words.w1 = (e->unkF & 7) | ((e->unk9 & 0xF) << 24) | ((e->unkC & 7) << 21) | ((e->unkE & 7) << 18)
//              | ((e->unkB & 7) << 6) | ((e->unkD & 7) << 3) | (e->unk1 << 28) | ((e->unk3 & 7) << 15)
//              | ((e->unk5 & 7) << 12) | ((e->unk7 & 7) << 9);
//         D_800DD1BE = temp_v0;
//     }
//     return gfx;
// }

void func_1513F680(struct171 *arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4) {
    arg0->unk70 = arg1;
    arg0->unk71 = arg2;
    arg0->unk72 = arg3;
    arg0->unk73 = arg4;
}

void func_1513F6C0(struct171 *arg0, u8 arg1, u8 arg2) {
    *(u8 *)((u8 *)arg0 + 0x80) = arg1;
    *(u8 *)((u8 *)arg0 + 0x81) = arg2;
}

s32 func_1513F6E8(ScaleUpdateState *arg0) {
    f32 temp = arg0->field_0x128;
    arg0->field_0x2C = arg0->field_0x2C + (temp * D_800BE9A4);
    arg0->field_0x30 = arg0->field_0x30 + (temp * D_800BE9A4);
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_1513F728.s")

void func_1513FA2C(void *arg0, s16 arg1) {
    f32 stack_vals[2];
    stack_vals[0] = 1.0f;
    stack_vals[1] = 1.0f;
    func_1513FAB4(arg0, 0, stack_vals, arg1);
}

void func_1513FA70(s32 arg0, s16 arg1) {
    f32 sp18[2];

    sp18[0] = 1.0f;
    sp18[1] = 1.0f;
    func_1513FAB4(arg0, 1, sp18, arg1);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_1513FAB4.s")

void func_1513FFF4(struct1513FFF4 *arg0, u8 arg1, u8 arg2) {
    struct1513FFF4_80090B60 *temp_v0;
    u16 temp_v1;
    u16 temp_a0;
    s32 temp;

    if (arg1 != 0xFF) {
        temp_v0 = &D_80090B60[arg1];
        temp_v1 = temp_v0->unk6 - 1;
        temp_a0 = temp_v0->unk8 - 1;

        if (arg2 & 1) {
            temp = temp_v1 << 6;
        } else {
            temp = 0;
        }
        arg0[3].unk8 = temp;
        arg0[0].unk8 = temp;

        if (arg2 & 1) {
            temp = 0;
        } else {
            temp = temp_v1 << 6;
        }
        arg0[2].unk8 = temp;
        arg0[1].unk8 = temp;

        if (arg2 & 2) {
            temp = temp_a0 << 6;
        } else {
            temp = 0;
        }
        arg0[1].unkA = temp;
        arg0[0].unkA = temp;

        if (arg2 & 2) {
            temp = 0;
        } else {
            temp = temp_a0 << 6;
        }
        arg0[3].unkA = temp;
        arg0[2].unkA = temp;
    }
}

void func_151400D0(Dst151400D0 *dst, Src151400D0 *src) {
    dst[0].unk6 = src[0].unk8;
    dst += 3;
    src += 3;
    dst[-3].unkC = src[-3].unk0;
    dst[-3].unkD = src[-3].unk2;
    dst[-3].unkE = src[-3].unk4;
    dst[-3].unkF = src[-3].unk6;
    dst[-3].unk6 = 0;

    dst[-2].unk6 = src[-2].unk8;
    dst[-2].unkC = src[-2].unk0;
    dst[-2].unkD = src[-2].unk2;
    dst[-2].unkE = src[-2].unk4;
    dst[-2].unkF = src[-2].unk6;
    dst[-2].unk6 = 0;

    dst[-1].unk6 = src[-1].unk8;
    dst[-1].unkC = src[-1].unk0;
    dst[-1].unkD = src[-1].unk2;
    dst[-1].unkE = src[-1].unk4;
    dst[-1].unkF = src[-1].unk6;
    dst[-1].unk6 = 0;

    dst[0].unk6 = src[0].unk8;
    dst[0].unkC = src[0].unk0;
    dst[0].unkD = src[0].unk2;
    dst[0].unkE = src[0].unk4;
    dst[0].unkF = src[0].unk6;
    dst[0].unk6 = 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_15140190.s")

void func_151403A8(s32 arg0, u8 arg1) {
    func_15169260(&D_800A5168, 4, arg0, arg1);
}

void func_151403DC(s32 arg0, u8 arg1) {
    func_15169260(&D_800A5178, 3, arg0, arg1);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_15140410.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_169510/func_151406AC.s")
