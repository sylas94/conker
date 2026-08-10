#include <ultra64.h>
#include "functions.h"
#include "variables.h"

typedef struct {
    s32 field_0x0;
    s32 field_0x4;
    u8 field_0x8;
    u8 field_0x9;
    u8 pad_0xA[0xD0];
    u8 field_0xDA;
    u8 pad_0xDB;
    s32 field_0xDC[1];
} CollisionPairRecord;

struct Some15171F04 {
    u8 pad0[4];
    u8 unk4;
    u8 pad5;
    u16 unk6;
    u16 unk8;
};

typedef struct {
    char pad_0x0[0x90];
    s16 field_0x90;
    char pad_0x92[0x2];
    f32 field_0x94;
    f32 field_0x98;
    f32 field_0x9C;
    f32 field_0xA0;
    f32 field_0xA4;
    f32 field_0xA8;
    f32 field_0xAC;
    f32 field_0xB0;
    f32 field_0xB4;
    f32 field_0xB8;
    f32 field_0xBC;
    f32 field_0xC0;
    f32 field_0xC4;
    f32 field_0xC8;
    f32 field_0xCC;
    s8 field_0xD0;
    char pad_0xD1[0x1];
    s16 field_0xD2;
    s16 field_0xD4;
    s16 field_0xD6;
    s16 field_0xD8;
    u8 field_0xDA;
    u8 field_0xDB;
    s32 field_0xDC;
    s16 field_0xE0;
    u8 field_0xE2;
    u8 field_0xE3;
    f32 field_0xE4;
    f32 field_0xE8;
    f32 field_0xEC;
    f32 field_0xF0;
    f32 field_0xF4;
    f32 field_0xF8;
    u8 field_0xFC;
    u8 field_0xFD;
    u8 field_0xFE;
} TrailSprite;

extern f32 sqrtf(f32);
extern struct Some15171F04 *D_8008CA4C[];
extern TrailSprite *func_15167A68(s32, s32, s32, s32, s32, s32);

void func_150E1AB0(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8,
                   f32 arg9, f32 arg10, s16 arg11, u16 arg12, s8 arg13, s16 arg14, s16 arg15, s32 arg16,
                   u8 arg17, u8 arg18, s32 arg19, u8 arg20, u8 arg21, f32 arg22, f32 arg23, f32 arg24,
                   f32 arg25, f32 arg26, f32 arg27) {
    TrailSprite *obj;
    u8 *vtx;
    s16 tw;
    s16 th;
    s32 i;

    obj = func_15167A68(0xB, 0, 0x100, 1, 0xFF, 1);
    if (obj == NULL) {
        return;
    }
    obj->field_0x90 = arg11;
    obj->field_0x94 = arg1;
    obj->field_0x98 = arg2;
    obj->field_0x9C = arg3;
    obj->field_0xA4 = func_150484A0(-(arg4 - arg1), -(arg6 - arg3));
    obj->field_0xA0 = func_150484A0(arg5 - arg2,
                                    sqrtf(((arg4 - arg1) * (arg4 - arg1)) + ((arg6 - arg3) * (arg6 - arg3))));
    obj->field_0xC4 = 0.0f;
    obj->field_0xC8 = 0.0f;
    obj->field_0xCC = 0.0f;
    obj->field_0xB0 = arg4;
    obj->field_0xB4 = arg5;
    obj->field_0xB8 = arg6;
    obj->field_0xAC = arg8;
    obj->field_0xA8 = arg7;
    obj->field_0xBC = arg9;
    obj->field_0xC0 = arg10;
    obj->field_0xE3 = 0;
    obj->field_0xFD = 0;
    obj->field_0xDC = arg16;
    obj->field_0xFC = arg20;
    obj->field_0xFE = arg21;
    obj->field_0xD8 = arg12;
    obj->field_0xD0 = arg13;
    if (obj->field_0xD0 != 0) {
        if (arg16 == 0) {
            func_1516979C((struct102 *)obj);
            return;
        }
        obj->field_0xD2 = arg14;
        obj->field_0xD4 = arg15;
        obj->field_0xD6 = -arg15;
        obj->field_0xDA = arg17;
        obj->field_0xE2 = arg18;
        obj->field_0xE0 = arg19;
        obj->field_0xE4 = arg22;
        obj->field_0xE8 = arg23;
        obj->field_0xEC = arg24;
        obj->field_0xF0 = arg25;
        obj->field_0xF4 = arg26;
        obj->field_0xF8 = arg27;
    } else {
        obj->field_0xD6 = 1;
        obj->field_0xE0 = -1;
    }
    vtx = (u8 *)obj;
    i = 0;
    do {
        i++;
        vtx += 0x40;
        tw = ((D_8008CA4C[obj->field_0xD8]->unk6 - 1) << 5) + 0x2000;
        th = ((D_8008CA4C[obj->field_0xD8]->unk8 - 1) << 5) + 0x2000;
        *(s16 *)(vtx - 0x8) = 0x2000;
        *(s16 *)(vtx - 0x6) = 0x2000;
        *(s16 *)(vtx - 0xA) = 0;
        *(s16 *)(vtx - 0x28) = tw;
        *(s16 *)(vtx - 0x26) = 0x2000;
        *(s16 *)(vtx - 0x2A) = 0;
        *(s16 *)(vtx + 0x8) = 0x2000;
        *(s16 *)(vtx + 0xA) = th;
        *(s16 *)(vtx + 0x6) = 0;
        *(s16 *)(vtx - 0x18) = tw;
        *(s16 *)(vtx - 0x16) = th;
        *(s16 *)(vtx - 0x1A) = 0;
    } while (i != 2);
    obj->field_0xDB = 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_10EF60/func_150E1D14.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_10EF60/func_150E28DC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_10EF60/func_150E2DA4.s")

void func_150E1AB0(s32, f32, f32, f32, f32, f32, f32, f32, f32, f32, f32, s16, u16, s8, s16, s16, s32, u8, u8, s32, u8, u8, f32, f32, f32, f32, f32, f32);

void func_150E2DB4(s32 a0, u8 a1, s16 a2, s32 a3, f32 a4, f32 a5, f32 a6, f32 a7, f32 a8, f32 a9, s16 a10, s16 a11, u16 a12, u8 a13) {
    func_150E1AB0(0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 40.0f, 400.0f, a12, 39, 1, a10, a11, a0, a1, a2, a3, 0, a13, a4, a5, a6, a7, a8, a9);
}

void func_150E2EA4(struct127 *a0, s32 a1, s32 a2, s32 a3, f32 a4, f32 a5, f32 a6, f32 a7, f32 a8, f32 a9, s32 a10, s32 a11, s32 a12, f32 a13, f32 a14, s32 a15, f32 a16) {
    func_150E1AB0(0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, a16, 0.0f, a13, a14, *(u16 *)((u8 *)&a12 + 2), 39, 1, *(s16 *)((u8 *)&a10 + 2), *(s16 *)((u8 *)&a11 + 2), (s32)a0, *((u8 *)&a1 + 3), *(s16 *)((u8 *)&a2 + 2), a3, 0, *((u8 *)&a15 + 3), a4, a5, a6, a7, a8, a9);
}

s32 func_150E2DA4(s32, s32);

s32 func_150E2F90(s32 a0, s32 a1, s16 a2) {
    return func_150E2DA4(a0, a2);
}

void func_150E2FC0(CollisionPairRecord *a0, CollisionPairRecord *a1, u8 a2) {
    s32 temp_v0;

    if (a2 == 0x2D) {
        if ((temp_v0 = a1->field_0x0) != a0->field_0xDC[0]) {
            goto check_second;
        }
        a0->field_0xDC[0] = a1->field_0x4;
        a0->field_0xDA = a1->field_0x9;
        return;
check_second:
        if ((u32)a1->field_0x4 != (u32)a0->field_0xDC[0]) {
            return;
        }
        a0->field_0xDC[0] = temp_v0;
        a0->field_0xDA = a1->field_0x8;
    }
}
