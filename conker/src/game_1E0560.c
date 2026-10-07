#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern s32 (*D_8008FAF0[])(void *, void *, s32);
extern s32 (*D_8008FAF8[])(void *);
extern void (*D_8008FB70[])(void *);
extern void *func_15167A68(s32, s32, s32, s32, u8, s32);
extern void func_151D5E30(void *);
extern f32 D_800AA390;
extern f32 D_800AA3AC;

typedef struct {
    u8 pad0[0x10];
    u8 unk10;
    u8 pad11;
    s16 unk12;
    u8 unk14[0xC];
    u8 unk20[0xC];
    s8 unk2C;
    s8 unk2D;
    u8 pad2E[0x6];
    s8 unk34;
} Struct151B3184;

typedef struct {
    s32 unk0;
    u8 pad4[0x10];
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    u8 pad20[0x1B];
    u8 unk3B;
} Struct151B3F28Inner;

typedef struct {
    u8 pad0[0x10];
    u8 unk10;
    u8 pad11[0x13F];
    Struct151B3F28Inner *unk150;
} Struct151B3F28;

typedef struct {
    u8 pad0[0x10];
    u8 unk10;
    u8 pad11[0x27];
    f32 unk38;
    u8 pad3C[0xFC];
    f32 unk138;
    s32 unk13C;
    u8 unk140[0x10];
} Struct151B30B0;

void *func_151B30B0(s32 arg0, f32 arg1, s32 arg2, u8 arg3, s32 arg4) {
    Struct151B30B0 *temp_v0;
    Struct151B30B0 *sp24;
    f32 temp_f0;
    f32 temp_f2;

    temp_v0 = func_15167A68(0x33, arg4, arg2 + 0x150, 1, arg3, 1);
    if (temp_v0 == 0) {
        return NULL;
    }

    sp24 = temp_v0;
    memcpy(&temp_v0->unk10, (void *)arg0, 0x38);
    temp_f0 = temp_v0->unk38;
    temp_v0->unk10 |= 0xE;
    temp_f2 = (temp_f0 * temp_f0) / D_800AA390;
    temp_v0->unk138 = temp_f2 + temp_f2;
    temp_v0->unk13C = (s32)(temp_f0 * arg1 * 4096.0f);
    bzero(temp_v0->unk140, 0x10);
    return sp24;
}

void func_151B3184(Struct151B3184 *arg0) {
    s32 temp;
    u8 failed;

    failed = 0;
    if (arg0->unk10 & 1) {
        arg0->unk12 -= D_800BE9E4;
        if (arg0->unk12 < 0) {
            failed = 1;
        }
    }
    if (failed == 0) {
        temp = arg0->unk2C;
        if (temp != -1) {
            if (D_8008FAF0[temp](arg0, arg0->unk14, 1) == 0) {
                failed = 1;
            }
        }
        temp = arg0->unk2D;
        if (temp != -1) {
            if (D_8008FAF0[temp](arg0, arg0->unk20, 0) == 0) {
                failed = 1;
            }
        }
        if ((arg0->unk10 & 4) || (arg0->unk10 & 8)) {
            arg0->unk10 |= 2;
        } else {
            temp = arg0->unk34;
            if (temp != -1) {
                if (D_8008FAF8[temp](arg0) == 0) {
                    failed = 1;
                }
            }
        }
    }
    if (failed) {
        func_1516972C((struct102 *) arg0);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1E0560/func_151B32C8.s")

extern void (*D_8008FB68[])(void *, s32, u8);

void func_151B3A34(struct102 *arg0, s32 arg1, u8 arg2) {
    void (*fn)(void *, s32, u8) = D_8008FB68[*(u8 *)((u8 *)arg0 + 0x44)];
    if (fn != NULL) {
        fn(arg0, arg1, arg2);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1E0560/func_151B3A7C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1E0560/func_151B3CF0.s")

s32 func_151B3F28(Struct151B3F28 *arg0, f32 *arg1, u8 arg2) {
    Struct151B3F28Inner **temp_v0;
    s32 ret;

    ret = 1;
    if (arg2 == 0) {
        goto no_arg;
    }

    temp_v0 = &arg0->unk150;
    if ((*temp_v0)->unk0 == 0) {
        goto failed;
    }
    if (*(u8 *)((u8 *) temp_v0 + 4) != (*temp_v0)->unk3B) {
        goto failed;
    }
    arg1[0] = (*temp_v0)->unk14;
    arg1[1] = (*temp_v0)->unk18;
    arg1[2] = (*temp_v0)->unk1C;
    arg0->unk10 &= ~4;
    goto done;

failed:
    ret = 0;
    arg0->unk10 |= 0xC;
failed_after_store:
    goto final_return;

no_arg:
    arg1[0] = 0.0f;
    arg1[1] = D_800AA3AC;
    arg1[2] = 0.0f;
    arg0->unk10 &= ~8;

done:
final_return:
    return ret;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1E0560/func_151B3FDC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1E0560/func_151B42A4.s")

typedef struct {
    s32 unk0;
    u8 pad4[0x37];
    u8 unk3B;
    u8 pad3C[0x198];
    s32 unk1D4;
} Struct151B47D8Actor;

typedef struct {
    Struct151B47D8Actor *unk0;
    u8 unk4;
    u8 unk5;
    u8 pad6[2];
    f32 unk8[3];
} Struct151B47D8Part;

typedef struct {
    u8 pad0[0x10];
    u8 unk10;
} Struct151B47D8;

typedef struct {
    Struct151B47D8Part p0;
    Struct151B47D8Part p1;
} Struct151B47D8Pair;

void func_15143134(void *, s32, s32);

s32 func_151B47D8(Struct151B47D8 *arg0, Struct151B47D8Pair *arg1, s32 arg2, u8 arg3) {
    Struct151B47D8Actor *a = arg1->p0.unk0;
    Struct151B47D8Actor *b = arg1->p1.unk0;

    if (a->unk1D4 == 0 || b->unk1D4 == 0) {
        arg0->unk10 |= 0xC;
        return 1;
    }
    if (a->unk0 == 0 || a->unk3B != arg1->p0.unk4 || b->unk0 == 0 || b->unk3B != arg1->p1.unk4) {
        return 0;
    }
    arg0->unk10 &= ~(arg3 ? 4 : 8);
    func_15143134(arg3 ? arg1->p0.unk8 : arg1->p1.unk8, arg2,
                  arg3 ? a->unk1D4 + (arg1->p0.unk5 << 6) : b->unk1D4 + (arg1->p1.unk5 << 6));
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1E0560/func_151B48DC.s")

s32 func_151B498C(s32 arg0, s32 *arg1, s32 *arg2, s32 *arg3, s32 *arg4, s32 *arg5,
                   s32 *arg6, s32 *arg7, s32 *arg8, s32 *arg9, s32 *arg10, s32 *arg11,
                   u8 *arg12, u8 *arg13) {
    *arg1 = 0x220005;
    *arg2 = 0x40600;
    *arg3 = 0xFF;
    *arg4 = 0xFF;
    *arg5 = 0xFF;
    *arg6 = 0xFF;
    *arg7 = 0xFF;
    *arg8 = 0xFF;
    *arg9 = 0xFF;
    *arg10 = 0xFF;
    *arg11 = 0;
    *arg12 = 5;
    *arg13 = 0x2B;
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1E0560/func_151B4A14.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1E0560/func_151B4B78.s")

void func_151B4C1C(u8 *arg0) {
    void (*fn)(void *);

    func_151D5E30(arg0 + 0x140);
    fn = D_8008FB70[arg0[0x44]];
    if (fn != NULL) {
        fn(arg0);
    }
}

void func_151B4C1C(u8 *);

void func_151B4C6C(struct102 *arg0) {
    func_151B4C1C((u8 *)arg0);
    func_15169824(arg0);
}

void func_151B4C98(struct102 *arg0) {
    func_151B4C1C((u8 *)arg0);
    func_15169824(arg0);
}
