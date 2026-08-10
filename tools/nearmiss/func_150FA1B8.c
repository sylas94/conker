#include <ultra64.h>
#include "functions.h"
#include "variables.h"


extern s32 D_800BE628;
extern s32 D_80082FA4;
void func_15110360(s32 arg0, f32 arg1[4][4], f32 arg2, f32 arg3, f32 arg4);
Gfx *func_15110544(Gfx *gfx, s32 a, s32 b, s32 c, s32 d, u8 r, u8 g, u8 bl);
void func_150FB4C0(Gfx *gfx, f32 mtx[4][4]);

typedef struct {
    u8  pad0[0x24];
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    f32 unk30;
} Struct150F9AB0;

void func_150F9AB0(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6) {
    f32 sp38[4][4];
    Struct150F9AB0 *temp;
    Gfx *gfx;

    func_15110360(D_80082FA4, sp38, arg4, arg5, arg6);
    temp = (Struct150F9AB0 *)((struct259 *)D_800BE628 + D_80082FA4);
    gfx = func_15110544(arg0, (s32)temp->unk2C, (s32)temp->unk24,
                        (s32)(temp->unk30 - 1.0f), (s32)temp->unk28, 0, 0, 0);
    gfx->words.w0 = 0xE7000000;
    gfx->words.w1 = 0;
    gfx++;
    gDPSetOtherMode(gfx++, 0x2C0F, 0x0F0A4004);
    gDPSetCombine(gfx++, 0x357E6A, 0xFFFFFFFF);
    func_150FB4C0(gfx, sp38);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_126F60/func_150F9BB0.s")

extern s32 D_800A1CCC;
extern s32 D_800A1CD8;
extern s32 D_800A1CE4;
extern s32 D_800A1CF0;
extern f32 D_800A1D94;
extern s32 func_15145EA4(s32 *arg0, s32 *arg1, s32 arg2, s32 arg3);

/* sub-object living at +0x110 inside Struct150FA1B8Body */
typedef struct {
    u8  pad0[0x48];
    f32 unk48;
    f32 unk4C;
    u8  pad50[0x8];
    u8  unk58;
} Struct150FA1B8Head;

typedef struct {
    u8       pad0[0x34];
    struct17 unk34;
    struct17 unk40;
} Struct150FA1B8Body;

/* sub-object living at +0x170 inside Struct150FA1B8Cloth */
typedef struct {
    f32 unk0;
    f32 unk4;
} Struct150FA1B8Tail;

typedef struct {
    u8       pad0[0x34];
    struct17 unk34;
    struct17 unk40;
    u8       pad4C[0xC];
    /* 0x58 */ s32 unk58;
} Struct150FA1B8Cloth;

typedef struct {
    /* 0x00 */ struct127 *unk0;
    /* 0x04 */ u8  unk4;
    u8  pad5[3];
    /* 0x08 */ Struct150FA1B8Body  *unk8[2];
    /* 0x10 */ Struct150FA1B8Cloth *unk10[2];
} Struct150FA1B8Sub;

typedef struct {
    u8  pad0[0xE];
    /* 0x0E */ s16 unkE;
    u8  pad10[0x18];
    /* 0x28 */ Struct150FA1B8Sub unk28;
} Struct150FA1B8;

void func_150FA1B8(Struct150FA1B8 *arg0) {
    Struct150FA1B8Body *body;
    Struct150FA1B8Cloth *cloth;
    struct17 sp88[2];
    struct17 sp70[2];
    u8 i;
    s32 sp5C[4];
    s32 sp4C[4];
    Struct150FA1B8Body *p;
    Struct150FA1B8Head *ph;
    Struct150FA1B8Head *head;
    Struct150FA1B8Tail *tail;
    struct127 *owner;
    f32 amount;
    u8 j;
    Struct150FA1B8Sub *sub;

    sub = &arg0->unk28;
    owner = sub->unk0;
    if ((owner->interaction_state == 0) || (owner->unique_id != sub->unk4)) {
        arg0->unkE = -1;
        return;
    }

    if (owner->unk1D4 != 0) {
        sp5C[0] = (s32)&D_800A1CCC;
        sp5C[1] = (s32)&D_800A1CD8;
        sp5C[2] = (s32)&D_800A1CE4;
        sp5C[3] = (s32)&D_800A1CF0;
        sp4C[0] = (s32)&sp88[0];
        sp4C[1] = (s32)&sp88[1];
        sp4C[2] = (s32)&sp70[0];
        sp4C[3] = (s32)&sp70[1];
        func_15145EA4(sp5C, sp4C, (s32)owner->unk1D4 + 0x40, 4);

        i = 0;
        do {
            body = sub->unk8[i];
            if (body != NULL) {
                head = (Struct150FA1B8Head *)((u8 *)body + 0x110);
                head->unk58 |= 1;
                body->unk34 = sp88[i];
                body->unk40 = sp70[i];
            }
            cloth = sub->unk10[i];
            if (cloth != NULL) {
                cloth->unk58 |= 2;
                cloth->unk58 &= ~4;
                cloth->unk34 = sp88[i];
                cloth->unk40 = sp70[i];
            }
            i++;
        } while (i < 2);
    } else {
        j = 0;
        do {
            p = sub->unk8[j];
            ph = (Struct150FA1B8Head *)((u8 *)p + 0x110);
            if (p != NULL) {
                ph->unk58 &= ~1;
            }
            cloth = sub->unk10[j];
            if (cloth != NULL) {
                cloth->unk58 &= ~2;
            }
            j++;
        } while (j < 2);
    }

    amount = D_800A1D94;
    i = 0;
    do {
        if (sub->unk8[i] != NULL) {
            head = (Struct150FA1B8Head *)((u8 *)sub->unk8[i] + 0x110);
            if (arg0->unkE < 10) {
                head->unk48 = 0.0f;
                head->unk4C = 0.0f;
            } else {
                head->unk48 = 6.0f;
                head->unk4C = 15.0f;
            }
        }
        if (sub->unk10[i] != NULL) {
            tail = (Struct150FA1B8Tail *)((u8 *)sub->unk10[i] + 0x170);
            if (arg0->unkE < 10) {
                tail->unk4 = 0.0f;
            } else {
                tail->unk4 = amount;
            }
        }
        i++;
    } while (i < 2);
}

void func_150FA468(struct102 *arg0, s32 arg1, u8 arg2) {
    if (arg2 == 0x4C) {
        *(s8 *)((s32)arg0 + 0x11) = -1;
        func_1515D4D4(0, 0, 0, 0xFF);
    } else if (arg2 == 0x4D) {
        *(u8 *)((s32)arg0 + 0x11) = 0x1E;
    } else if (arg2 == 0x4E) {
        *(s8 *)((s32)arg0 + 0x11) = -1;
    } else if (arg2 == 0x4F) {
        *(s8 *)((s32)arg0 + 0x11) = -1;
        func_1515D4D4(0xFF, 0xFF, 0xFF, 0xFF);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_126F60/func_150FA520.s")

void func_150FAA40(u8 arg0, s32 arg1) {
    struct {
        s32 unk0;
        s32 unk4;
        f32 unk8;
    } sp3C;
    struct260 *temp_v0;

    if (D_80088B60 == 0) {
        sp3C.unk0 = *(s32 *)&D_800D3098 + 0x71C;
        sp3C.unk4 = *(s32 *)&D_800D3098 + 0x6E8;
        sp3C.unk8 = 0.0f;

        temp_v0 = func_15149130(0x12C, -1, 0x57, -1, 0, 0x46, (struct37 *)0xC, arg0, arg1);
        if (temp_v0 != NULL) {
            D_80088B60 = 1;
        }
        if (temp_v0 != NULL) {
            memcpy((void *)((s32)temp_v0 + 0x28), &sp3C, 0xC);
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_126F60/func_150FAAEC.s")

void func_150FACE4(struct102 *arg0, s32 arg1, u8 arg2) {
    switch (arg2) {
        case 0x4E:
        case 0x4F:
            func_1516972C(arg0);
            break;
    }
}

extern void func_1515F170(s32 arg0, u8 arg1);

void func_150FAD28(void) {
    func_1515F170(8, 0);
    func_1515F170(0xB, 1);
    func_151494E0(*(s32 *)&D_800D3098 + 0x514, 0x30);
    func_151494E0(0, 0x4D);
}

void func_150FAD78(void) {
    func_1515F170(8, 1);
    func_1515F170(7, 0);
    func_151494E0(*(s32 *)&D_800D3098 + 0x514, 0x31);
    func_151494E0(0, 0x4C);
}

void func_150FADC8(s32 *arg0, s32 arg1, u8 arg2) {
    if (arg2 == 0x53) {
        arg0[0x16] |= 2;
    } else if (arg2 == 0x54) {
        arg0[0x16] &= ~2;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_126F60/func_150FAE18.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_126F60/func_150FB188.s")

extern s32 func_151D710C(s32, s32, s32, s32, s32);
extern void func_15157F80(s32, s32, s32, s32, s32);

void func_150FB1E8(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    func_15157F80(func_151D710C(arg0, arg1, arg2, arg3, arg4), arg1, arg2, arg3, arg4);
}

void func_150FB240(u8 *arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4) {
    if ((arg2 - arg3) < arg1) {
        *arg0 = (arg2 - arg1) * arg4;
    } else {
        *arg0 = 0xFF;
    }
}

s32 func_150FB29C(void *arg0) {
    func_150FB240((u8 *)arg0 + 0x43, *(s16 *)((u8 *)arg0 + 0x16), *(s16 *)((u8 *)arg0 + 0x120), *(s16 *)((u8 *)arg0 + 0x64), *(s16 *)((u8 *)arg0 + 0x66));
    return 1;
}

extern void func_150FB240(u8 *arg0, s16 arg1, s16 arg2, s16 arg3, s16 arg4);

s32 func_150FB2E0(void *arg0) {
    func_150FB240((u8 *)arg0 + 0x2E, *(s16 *)((u8 *)arg0 + 0x22), *(s16 *)((u8 *)arg0 + 0x70), *(s16 *)((u8 *)arg0 + 0x26), *(s16 *)((u8 *)arg0 + 0x28));
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_126F60/func_150FB324.s")
