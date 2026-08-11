#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern s8 D_800D239A;
extern s8 D_800D2398;
extern s8 D_800D2399;
extern s8 *D_800D23B0;
s32 func_1508802C();

typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    s16 unkE;
} B3020Struct;

extern s16 D_80087290;
extern s16 D_80087294;
extern B3020Struct *D_800D2350;
s16 *func_1502B5C8(s32 *, s32, s32, s32);
void func_15085BE8(void);

void func_15085B70(s32 arg0) {
    s16 *temp_v0;

    temp_v0 = func_1502B5C8(0, 2, 0x19, arg0);
    if (temp_v0 == 0) {
        D_80087290 = 0;
        D_80087294 = 0;
        D_800D2350 = 0;
    } else {
        D_80087290 = temp_v0[0];
        D_80087294 = temp_v0[1];
        D_800D2350 = (B3020Struct *)(temp_v0 + 2);
    }
    func_15085BE8();
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_B3020/func_15085BE8.s")

extern f32 D_800D2360[];
extern u8 D_800D237C[];
extern f32 D_8009D9CC;
extern u8 D_8008729C;
extern s32 D_800D2354;
extern f32 sqrtf(f32);
f32 func_15086D94(f32, f32, f32, f32, f32);

u8 func_15085DA8(f32 arg0) {
    s32 i = 0;

    while (D_800D2360[i] <= arg0) {
        i++;
    }
    return D_800D237C[i];
}

s32 func_15085DF8(f32 arg0, f32 arg1, f32 arg2, s8 arg3, s8 arg4) {
    f32 sp70;
    f32 sp6C;
    f32 sp68;
    f32 temp_f2;
    f32 temp_f16;
    f32 temp_f18;
    f32 temp_f20;
    f32 bestDist;
    s32 i;
    s32 useGate;
    s32 bestIdx;
    B3020Struct *entry;

    useGate = 0;
    bestDist = D_8009D9CC;
    if (arg3 == 0) {
        useGate = 1;
    }

    if (D_8008729C != 0xFF) {
        entry = &D_800D2350[D_8008729C];
        temp_f2 = (f32) entry->unk0 - arg0;
        temp_f16 = (f32) entry->unk2 - arg1;
        temp_f18 = (f32) entry->unk4 - arg2;
        if ((useGate == 0) || ((useGate != 0) && (sp70 = temp_f2, sp6C = temp_f16, sp68 = temp_f18, func_15086D94(arg0, arg1, arg2, temp_f2, temp_f18) < 0.0f))) {
            bestDist = (temp_f2 * temp_f2) + (temp_f16 * temp_f16) + (temp_f18 * temp_f18) + 10.0f;
        }
        D_8008729C = 0xFF;
    }

    bestIdx = 0xFF;
    i = 0;
    if (D_80087290 > 0) {
        do {
            entry = &D_800D2350[i];
            if (((arg4 == ((u8 *)entry)[6]) || (arg4 == -1)) && ((arg3 == ((u8 *)entry)[0xE]) || (arg3 == -1))) {
                temp_f2 = (f32) entry->unk0 - arg0;
                temp_f16 = (f32) entry->unk2 - arg1;
                temp_f18 = (f32) entry->unk4 - arg2;
                temp_f20 = (temp_f2 * temp_f2) + (temp_f16 * temp_f16) + (temp_f18 * temp_f18);
                if ((temp_f20 < bestDist) && ((useGate == 0) || ((useGate != 0) && (func_15086D94(arg0, arg1, arg2, temp_f2, temp_f18) < 0.0f)))) {
                    bestDist = temp_f20;
                    bestIdx = i;
                }
            }
            i++;
        } while (i < D_80087290);
    }

    D_800D2354 = (s32) sqrtf(bestDist);
    return bestIdx;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_B3020/func_15086098.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_B3020/func_15086364.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_B3020/func_15086BD0.s")

extern void func_150A3194(s32, s32, s32, s32, s32);

extern B3020Struct *D_800D2350;

void func_15086C70(s32 arg0) {
    s16 temp = D_800D2350[arg0].unk4;
    func_150A3194(3, 0xB, D_800D2350[arg0].unk0, D_800D2350[arg0].unk2, temp);
}

extern s16 D_80087290;

s32 func_15086CBC(s32 arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    if (arg0 < 0) {
        goto fail;
    }

    if (arg0 >= D_80087290) {
fail:
        return 0;
    }

    *arg1 = D_800D2350[arg0].unk0;
    *arg2 = D_800D2350[arg0].unk2;
    *arg3 = D_800D2350[arg0].unk4;
    return 1;
}

s32 func_15086D48(s32 arg0) {
    s32 i;

    for (i = 0; i < D_80087290; i++) {
        if (arg0 == ((u8 *)D_800D2350)[i * 16 + 7]) {
            return i;
        }
    }
    return 0xFF;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_B3020/func_15086D94.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_B3020/func_150870D0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_B3020/func_15087350.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_B3020/func_15087CC0.s")

extern u8 *D_800872A0;
u8 func_150888A8(u8, u8, s32);

struct Struct15087DCC {
    char pad0[0x2B];
    u8 unk2B;
    u8 unk2C;
    u8 unk2D;
    u8 unk2E;
    s8 unk2F;
    char pad30[0x84 - 0x30];
};

void func_15087DCC(s32 arg0, s32 arg1) {
    struct Struct15087DCC *p;
    if (D_800872A0 == 0) {
        return;
    }
    p = (struct Struct15087DCC *)(arg0 * sizeof(struct Struct15087DCC) + (s32)D_800872A0);
    if (arg1 == p->unk2F) {
        return;
    }
    if (arg1 != 0) {
        p->unk2D = func_150888A8(p->unk2B, p->unk2C, 1);
        p->unk2E = func_150888A8(p->unk2C, p->unk2D, 1);
    }
    p->unk2F = arg1;
}

struct Struct15087E54 {
    char pad0[0xC];
    f32 unkC;
    f32 unk10;
    char pad14[0x84 - 0x14];
};

struct Struct15087E54arg1 {
    char pad0[0x76];
    u16 unk76;
};

void func_15087E54(s32 arg0, struct Struct15087E54arg1 *arg1) {
    struct Struct15087E54 *p;
    u16 d;
    u16 r;
    if (D_800872A0 == 0) {
        return;
    }
    p = (struct Struct15087E54 *)(arg0 * sizeof(struct Struct15087E54) + (s32)D_800872A0);
    r = func_1505A630(p->unk10, p->unkC, 0) + 0x4000;
    d = (u16)(r - arg1->unk76);
    if (d & 0x8000) {
        if (d < 0xDBFF) {
            arg1->unk76 = r + 0x2400;
        }
    } else {
        if (d >= 0x2401) {
            arg1->unk76 = r - 0x2400;
        }
    }
}

extern s8 D_800D23A8;
extern u8 *D_800872A0;

struct Struct15087EF0 {
    f32 unk0;
    char pad4[0xC - 4];
    f32 unkC;
    f32 unk10;
    char pad14[0x84 - 0x14];
};

struct Struct15087EF0arg1 {
    char pad0[0x76];
    s16 unk76;
};

void func_15087EF0(s32 arg0, struct Struct15087EF0arg1 *arg1) {
    struct Struct15087EF0 *p;
    u16 r;
    if (D_800872A0 == 0) {
        return;
    }
    p = (struct Struct15087EF0 *)(arg0 * sizeof(struct Struct15087EF0) + (s32)D_800872A0);
    r = func_1505A630(p->unk10, p->unkC, 0);
    if (D_800D23A8 == 0) {
        if (p->unk0 < 0.5f) {
            r = (u16)(r + 0x4A00);
        } else {
            r = (u16)(r + 0x3600);
        }
    } else {
        if (0.5f <= p->unk0) {
            r = (u16)(r + 0x4A00);
        } else {
            r = (u16)(r + 0x3600);
        }
    }
    arg1->unk76 = r;
}

struct Struct15087FC4 {
    char pad0[0x31];
    u8 unk31;
    char pad32[0x84 - 0x32];
};

void func_15087FC4(s32 arg0, s32 arg1) {
    struct Struct15087FC4 *p;
    if (D_800872A0 == 0) {
        return;
    }
    p = (struct Struct15087FC4 *)(arg0 * sizeof(struct Struct15087FC4) + (s32)D_800872A0);
    p->unk31 = arg1;
}

extern u8 *D_800872A0;

struct Struct15087FEC {
    char pad0[4];
    f32 unk4;
    char pad8[0x84 - 8];
};

void func_15087FEC(s32 arg0, s32 arg1) {
    struct Struct15087FEC *p;
    if (D_800872A0 == 0) {
        return;
    }
    p = (struct Struct15087FEC *)(arg0 * sizeof(struct Struct15087FEC) + (s32)D_800872A0);
    p->unk4 = (f32)arg1 * (1.0f / 256.0f);
}

s32 func_1508802C(s8 *arg0, struct127 *arg1, s32 arg2) {
    struct126 *temp_v0;

    temp_v0 = arg1->unk31C;
    if (temp_v0->unk120 != 0) {
        return 1;
    }

    if ((D_800D18A0 & (1 << (arg1 - D_800CC2D0))) != 0) {
        return 1;
    }

    temp_v0->unk84 = 1;
    arg1->interaction_state = 0xC;
    arg1->unk232 = arg2;
    D_800D154C = arg1;
    D_800C3E78 = arg0[0x31];
    arg1->unk218 = func_1507BB28(0, arg2);
    arg1->unk21C = 0;
    arg1->immune = 0xFF;
    arg0[0x30] = 2;
    return 0;
}

s32 func_150880F8(s32 arg0, s32 arg1) {
    s8 *p;
    struct127 *obj;
    s32 ret;

    ret = 0;
    if (D_800872A0 == 0) {
        return 0;
    }

    p = (s8 *)(arg0 * 0x84 + (s32)D_800872A0);
    obj = &D_800CC2D0[p[0x31]];
    if (p[0x30] == 0) {
        ret = func_1508802C(p, obj, arg1);
    } else if (p[0x30] == 1) {
        p[0x30] = 2;
        obj->immune = 0xFF;
    }

    p[0x2A] = D_800D239A;
    D_800D239A++;
    return ret;
}

struct Struct150881CC {
    f32 unk0;
    char pad4[0x84 - 4];
};

s32 func_150881CC(s32 arg0) {
    struct Struct150881CC *p;
    if (D_800872A0 == 0) {
        return 0;
    }
    p = (struct Struct150881CC *)(arg0 * sizeof(struct Struct150881CC) + (s32)D_800872A0);
    return (s32)(p->unk0 * 256.0f);
}

struct Struct15088218 {
    char pad0[8];
    f32 unk8;
    char padC[0x24 - 0xC];
    s16 unk24;
    char pad26[0x84 - 0x26];
};

s32 func_15088218(s32 arg0) {
    struct Struct15088218 *p;
    s32 v;
    if (D_800872A0 == 0) {
        return 0;
    }
    p = (struct Struct15088218 *)(arg0 * sizeof(struct Struct15088218) + (s32)D_800872A0);
    v = p->unk24;
    return (v << 4) + (s32)(p->unk8 * 16.0f);
}

struct Struct15088270 {
    char pad0[0x14];
    f32 unk14;
    char pad18[0x84 - 0x18];
};

s32 func_15088270(s32 arg0) {
    struct Struct15088270 *p;
    if (D_800872A0 == 0) {
        return 0;
    }
    p = (struct Struct15088270 *)(arg0 * sizeof(struct Struct15088270) + (s32)D_800872A0);
    return (s32)p->unk14;
}

struct Struct150882B0 {
    char pad0[0x27];
    s8 unk27;
    char pad28[0x84 - 0x28];
};

s32 func_150882B0(s32 arg0) {
    struct Struct150882B0 *p;
    if (D_800872A0 == 0) {
        return 0;
    }
    p = (struct Struct150882B0 *)(arg0 * sizeof(struct Struct150882B0) + (s32)D_800872A0);
    return p->unk27;
}

struct Struct150882E4 {
    char pad0[8];
    f32 unk8;
    char padC[0x24 - 0xC];
    s16 unk24;
    char pad26[3];
    s8 unk29;
    char pad2A[0x84 - 0x2A];
};

s32 func_150882E4(s32 arg0, s32 arg1) {
    struct Struct150882E4 *p;
    struct Struct150882E4 *iter;
    s32 i;
    s32 wanted;

    if (D_800872A0 == 0) {
        return 0x10;
    }

    p = (struct Struct150882E4 *)(arg0 * sizeof(struct Struct150882E4) + (s32)D_800872A0);
    wanted = p->unk29 + arg1;
    i = 0;
    if (D_800D2398 > 0) {
        iter = (struct Struct150882E4 *)D_800872A0;
        do {
            if (wanted == iter->unk29) {
                if (i != arg0) {
                    arg0 = (p->unk24 << 4) + (s32)(p->unk8 * 16.0f);
                    arg0 = arg0 - (iter->unk24 << 4) - (s32)(iter->unk8 * 16.0f);
                    if (arg0 < 0) {
                        arg0 = -arg0;
                    }
                    return (arg0 << 8) | i;
                }
            }
            i++;
            iter++;
        } while (i < D_800D2398);
    }

    return 0x10;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_B3020/func_150883B0.s")

struct Struct1508855C {
    char pad0[0x31];
    s8 unk31;
    char pad32[0x84 - 0x32];
};

s32 func_1508855C(struct127 *arg0) {
    u8 *base;
    s32 index;
    s32 i;
    s32 limit;
    struct Struct1508855C *p;

    index = ((s32)arg0 - (s32)D_800CC2D0) / (s32)sizeof(struct127);
    base = D_800872A0;
    if (base == 0) {
        return -1;
    }

    if (index == 0) {
        return 0;
    }

    i = 1;
    limit = D_800D2398 + D_800D2399;
    p = (struct Struct1508855C *)(base + sizeof(struct Struct1508855C));
    if (limit < 2) {
        goto fail;
    }

    do {
        if (index == p->unk31) {
            return i;
        }
        i++;
        p++;
    } while (i < limit);

fail:
    return -1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_B3020/func_150885EC.s")

extern s32 D_800D2394;
extern s8 D_800D2398;
extern s8 D_800D2399;
typedef struct Struct15088824 Struct15088824;
void func_15088824();

s32 func_1508868C(s32 arg0) {
    s32 i;
    s32 offset;
    s32 base;

    base = (s32)D_800872A0;
    if (base == 0) {
        return -1;
    }

    offset = 1;
    i = 0;
    if (D_800D2399 > 0) {
        do {
            if ((D_800D2394 & offset) == 0) {
                D_800D2394 |= offset;
                i += D_800D2398;
                offset = i * 0x84;
                func_15088824(offset + base);
                D_800872A0[offset + 0x30] = 1;
                D_800872A0[offset + 0x31] = (arg0 - (s32)D_800CC2D0) / (s32)sizeof(struct127);
                return i;
            }
            i++;
            offset <<= 1;
        } while (i < D_800D2399);
    }
    return -1;
}

void func_15088780(void) {
    s32 func_1508855C();
    s32 temp_v0;

    if (D_800872A0 != 0) {
        temp_v0 = func_1508855C();
        D_800872A0[temp_v0 * 0x84 + 0x31] = 0;
        D_800D2394 &= ~(1 << (temp_v0 - D_800D2398));
    }
}

extern u8 *D_800872A0;

s32 func_150887F8(void) {
    u8 *p = D_800872A0;
    if (p == 0) {
        return 0;
    }
    return p[0x46] == 0xFF;
}

struct Struct15088824 {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ s16 unk24;
    /* 0x26 */ u8 unk26;
    /* 0x27 */ u8 unk27;
    /* 0x28 */ u8 unk28;
    /* 0x29 */ u8 unk29;
    /* 0x2A */ u8 unk2A;
    /* 0x2B */ u8 unk2B;
    /* 0x2C */ u8 unk2C;
    /* 0x2D */ u8 unk2D;
    /* 0x2E */ u8 unk2E;
    /* 0x2F */ u8 unk2F;
    /* 0x30 */ u8 unk30;
    /* 0x31 */ u8 unk31;
    /* 0x32 */ u8 unk32;
    /* 0x33 */ u8 unk33;
    /* 0x34 */ u8 pad34[0x15];
    /* 0x49 */ u8 unk49;
};

void func_15088824(Struct15088824 *arg0) {
    arg0->unk2B = 0;
    arg0->unk2C = 0;
    arg0->unk2D = 0;
    arg0->unk2E = 0;
    arg0->unk28 = 0;
    arg0->unk1C = 0;
    arg0->unk18 = 0;
    arg0->unk20 = -1;
    arg0->unk2F = 0;
    arg0->unk8 = 0.0f;
    arg0->unk0 = 0.5f;
    arg0->unk4 = 0.5f;
    arg0->unk24 = 0;
    arg0->unk26 = 0;
    arg0->unk27 = 0;
    arg0->unk31 = 0;
    arg0->unkC = 0.0f;
    arg0->unk14 = 0.0f;
    arg0->unk33 = 2;
    arg0->unk30 = 0;
    arg0->unk2A = 0x7F;
    arg0->unk49 = 0;
    arg0->unk10 = 1.0f;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_B3020/func_150888A8.s")

struct Struct15088A08 {
    char pad0[0x8];
    f32 unk8;
    char padC[0xC];
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    s16 unk24;
    s8 unk26;
    s8 unk27;
    s8 unk28;
    char pad29[2];
    u8 unk2B;
    u8 unk2C;
    u8 unk2D;
    u8 unk2E;
    s8 unk2F;
    s8 unk30;
    s8 unk31;
};

extern u8 D_800D2390;
extern s8 D_800E0BE7;
extern u8 D_800BE616;
extern s8 D_8008FD90;
extern s16 D_800E0C10[];
extern s32 D_800E0C18[];

s32 func_15088A08(struct Struct15088A08 *arg0, f32 arg1) {
    s32 dir;
    s32 idx;
    s32 lim;
    s32 t;
    s32 v;

    dir = 0;
    arg0->unk8 += arg1;
    if (arg0->unk8 < 0.0f) {
        arg0->unk8 += 1.0f;
        arg0->unk2E = arg0->unk2D;
        arg0->unk2D = arg0->unk2C;
        arg0->unk2C = arg0->unk2B;
        arg0->unk2B = func_150888A8(arg0->unk2D, arg0->unk2C, arg0->unk2F);
        dir = -1;
    } else if (arg0->unk8 >= 1.0f) {
        arg0->unk8 -= 1.0f;
        arg0->unk2B = arg0->unk2C;
        arg0->unk2C = arg0->unk2D;
        arg0->unk2D = arg0->unk2E;
        arg0->unk2E = func_150888A8(arg0->unk2C, arg0->unk2D, arg0->unk2F);
        dir = 1;
        if (D_800D23A8 == 0) {
            if (((u8 *)D_800D2350)[arg0->unk2C * 16 + 0xF] == 5) {
                D_800D2390 = 1;
            }
            if (((u8 *)D_800D2350)[arg0->unk2C * 16 + 0xF] == 6) {
                D_800D2390 = 2;
            }
        } else {
            if (((u8 *)D_800D2350)[arg0->unk2C * 16 + 0xF] == 7) {
                D_800D2390 = 1;
            }
            if (((u8 *)D_800D2350)[arg0->unk2C * 16 + 0xF] == 8) {
                D_800D2390 = 2;
            }
            if (((u8 *)D_800D2350)[arg0->unk2C * 16 + 0xF] == 9) {
                D_800D2390 = 3;
            }
        }
    }

    if (dir != 0) {
        lim = D_800E0BE7;
        idx = arg0->unk31;
        arg0->unk24 += dir;
        arg0->unk27 = arg0->unk24 / arg0->unk26;
        if (D_800BE616 != 0) {
            if (lim < arg0->unk27) {
                arg0->unk27 = lim + 1;
            }
        }
        if (arg0->unk28 < arg0->unk27) {
            arg0->unk28 = arg0->unk27;
            if ((idx < D_8008FD90) && (arg0->unk30 == 0) && (arg0->unk1C > 0)) {
                if (lim >= arg0->unk28) {
                    t = arg0->unk1C - arg0->unk18;
                    if (t > 0x7D00) {
                        t = 0x7D00;
                    }
                    if ((D_800E0C10[idx] <= 0) || (t < D_800E0C10[idx])) {
                        D_800E0C10[idx] = t;
                    }
                    arg0->unk20 = t;
                }
                if (lim == arg0->unk28) {
                    v = arg0->unk1C;
                    if (v > 0x57E40) {
                        v = 0x57E40;
                    }
                    D_800E0C18[idx] = v;
                }
            }
            if (lim == arg0->unk28) {
                arg0->unk18 = -arg0->unk1C;
            } else if (arg0->unk28 < lim) {
                arg0->unk18 = arg0->unk1C;
            }
        }
    }

    return dir;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_B3020/func_15088D58.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_B3020/func_15088F30.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_B3020/func_1508907C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_B3020/func_150891E8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_B3020/func_150896EC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_B3020/func_15089BB0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_B3020/func_15089BC0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_B3020/func_15089F9C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_B3020/func_1508A1BC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_B3020/func_1508A6FC.s")

extern s8 D_8008FD90;
extern s16 *D_8008FDD4;

s32 func_1508B194(s32 arg0) {
    if (arg0 >= D_8008FD90) {
        return 0;
    }

    return *(s16 *)((u8 *)D_8008FDD4 + arg0 * 12 + 0x70);
}

void func_1508B1D4(s32 arg0) {
    if (arg0 < D_8008FD90) {
        *(s16 *)((u8 *)D_8008FDD4 + arg0 * 12 + 0x70) = 0;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_B3020/func_1508B20C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_B3020/func_1508B2A8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_B3020/func_1508B3F8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_B3020/func_1508B9BC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_B3020/func_1508BC20.s")

s32 func_1508BF14(void) {
    s32 numSlots;
    s32 owner;
    s32 pass;
    s32 myIdx;
    s32 i;
    s32 j;
    s32 end;
    s32 cost;
    s32 bestCost;
    s8 counts[16];
    s32 *owners;
    s32 *links;
    s32 *costs;
    s32 *statuses;
    s32 *weights;
    s32 *bestCosts;
    s32 *bestSlots;
    s32 bestSlot;
    s32 n;

    myIdx = ((s32 *)D_800D23B0)[1];
    numSlots = ((s32 *)D_800D23B0)[4];
    statuses = (s32 *)(D_800D23B0 + 0x15C);
    weights = (s32 *)(D_800D23B0 + 0x39C);
    owners = (s32 *)(D_800D23B0 + 0xE64);
    bestCosts = (s32 *)(D_800D23B0 + 0x45C);
    bestSlots = (s32 *)(D_800D23B0 + 0x49C);
    links = (s32 *)(D_800D23B0 + 0x5DC);
    costs = (s32 *)(D_800D23B0 + 0x9DC);
    owner = owners[myIdx];

    for (i = 0; i < numSlots; i++) counts[i] = 0;

    for (pass = 0; pass != 2; pass++) {
        for (i = 0; i < numSlots; i++) {
            n = 0;
            if ((statuses[i] == 2) || (statuses[i] == 3)) {
                n = 1;
            }
            if ((n && (pass == 0)) || (!n && (pass != 0))) {
                if (owners[i] == owner) {
                    bestSlot = -1;
                    bestCost = 10000000;
                    for (j = 0; j < numSlots; j++) {
                        if (weights[j] > 0) {
                            if (owners[j] != owner) {
                                cost = -1;
                                n = j * 16;
                                end = n + 16;
                                while ((n < end) && (links[n] != -1)) {
                                    if (links[n] == i) {
                                        cost = costs[n];
                                        n = end;
                                    } else {
                                        n++;
                                    }
                                }
                                if (cost != -1) {
                                    cost <<= counts[j];
                                    if (cost < bestCost) {
                                        bestCost = cost;
                                        bestSlot = j;
                                    }
                                }
                            }
                        }
                    }
                    counts[bestSlot]++;
                    bestCosts[i] = bestCost;
                    bestSlots[i] = bestSlot;
                }
            }
        }
    }
    return 0;
}

s32 func_1508C194(s32 arg0) {
    return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_B3020/func_1508C1A4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_B3020/func_1508C5B8.s")

s32 func_1508C9CC(void) {
    s32 count;
    s32 ret;
    s8 cur;
    struct127 *obj;
    struct126 *unk31C;

    count = 0;
    ret = -1;
    cur = D_800D23B0[0x1702];
    do {
        cur = (s8)(cur + 1);
        if (cur >= D_8008FD8C) {
            cur = 0;
        }

        obj = &D_800CC2D0[cur];
        if (obj->interaction_state != 0) {
            unk31C = obj->unk31C;
            if ((unk31C != 0) && (unk31C->unk84 != 0) && ((D_800D18A0 & (1 << cur)) == 0)) {
                count = D_8008FD8C;
                ret = cur;
            }
        }
        count++;
    } while (count < D_8008FD8C);

    D_800D23B0[0x1702] = cur;
    return ret;
}

s32 func_1508CA88(void) {
    s8 **p2;
    s8 temp;

    p2 = &D_800D23B0;
    D_800D23B0[0x1703]++;
    temp = D_800D23B0[0x1703];
    if (temp >= D_8008FD90) {
        D_800D23B0[0x1703] = 0;
        temp = (*p2)[0x1703];
    }
    return temp;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_B3020/func_1508CAD8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_B3020/func_1508D850.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_B3020/func_1508DA1C.s")

extern struct127 D_800CC2D0[26];
extern s8 *D_800D23B0;
s32 func_1508DAEC(s32 arg0, s32 arg1)
{
  s8 *base;
  s32 value;
  s32 *entry;
  s8 *slot;
  s32 slotOffset;
  int mode;
  struct127 *obj;
  base = D_800D23B0;
  value = arg0 * 4;
  entry = (s32 *) (((s32) base) + value);
  if (base == 0)
  {
    return 0;
  }
  value = entry[0x3AC];
  if (value >= 0)
  {
    if (arg1 < 0)
    {
      return 1;
    }
    entry[0x3AC] = -1;
    slotOffset = value * 4;
    obj = &D_800CC2D0[arg0];
    slot = D_800D23B0 + slotOffset;
    if (((*((s32 *) (slot + 0x11F4))) & 2) == 0)
    {
      *((s32 *) (slot + 0xF70)) = -1;
      *((s32 *) ((D_800D23B0 + slotOffset) + 0x10F0)) = -1;
      mode = *((s32 *) (D_800D23B0 + 0xEAC));
      if (arg1 == 1)
      {
        *((s32 *) ((D_800D23B0 + slotOffset) + 0x12F4)) = 0x12C;
        obj = &D_800CC2D0[arg0];
        mode = 4;
        *((s32 *) ((D_800D23B0 + slotOffset) + 0x1374)) = (s32) obj->x_position;
        *((s32 *) ((D_800D23B0 + slotOffset) + 0x13F4)) = (s32) (obj->y_position + 50.0f);
        *((s32 *) ((D_800D23B0 + slotOffset) + 0x1474)) = (s32) obj->z_position;
      }
      *((s32 *) ((D_800D23B0 + slotOffset) + 0x1070)) = mode;
    }
  }
  return 0;
}


#pragma GLOBAL_ASM("asm/nonmatchings/game_B3020/func_1508DC24.s")

void func_1508E6C8(void) {
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_B3020/func_1508E6D0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_B3020/func_1508E780.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_B3020/func_1508E89C.s")

extern struct127 D_800CC40F[];

void func_1508EB90(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp = *(u8*)&D_800CC40F[arg0];
    func_1509BFB0(1, temp | 0x2000, arg1, arg2);
}

void func_1508EBF8(s32 arg0, s32 arg1) {
    s32 temp = *(u8*)&D_800CC40F[arg0];
    func_1509BFB0(1, temp | 0x2000, 0x14, arg1);
}

void func_1508EC5C(s32 arg0, s32 arg1) {
    s32 temp = *(u8*)&D_800CC40F[arg0];
    func_1509BFB0(1, temp | 0x2000, 0x61, arg1);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_B3020/func_1508ECC0.s")

typedef struct {
    s16 unk0;
    s16 unk2;
    s32 unk4;
    s32 unk8[4];
} Struct1508EDBC;

void func_1508EDBC(s32 arg0) {
    if (arg0 < D_80087380) {
        ((Struct1508EDBC *)D_800D23C0)[arg0].unk2 = 0;
        ((Struct1508EDBC *)D_800D23C0)[arg0].unk4 = 0;
        ((Struct1508EDBC *)D_800D23C0)[arg0].unk0 = 0;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_B3020/func_1508EE0C.s")
