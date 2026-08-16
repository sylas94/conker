#include <ultra64.h>
/* include/functions.h declares func_150ADA20 as returning u8.  The golden code for
 * func_150B54A8 saves its result across further calls without zero-extending it and
 * feeds it straight into `divu`, which a u8-returning declaration cannot produce, so the
 * real return type is a word.  Per project policy the shared header is left alone and the
 * correct prototype is made file-local. */
#define func_150ADA20 func_150ADA20_u8_decl_in_functions_h
#include "functions.h"
#undef func_150ADA20
s32 func_150ADA20(void);
#include "variables.h"

extern void func_151D2AB0(s32);

struct260 *func_150B53D0(void *arg0, s16 arg1, u8 arg2, s32 arg3) {
    struct260 *temp_v0;
    struct {
        void *unk0;
        u8 unk4;
        f32 unk8;
        f32 unkC;
    } sp3C;

    if (arg0 == NULL) {
        return NULL;
    }

    sp3C.unk0 = arg0;
    sp3C.unk4 = *((u8 *)arg0 + 0x3B);
    sp3C.unk8 = 0.0f;
    sp3C.unkC = 0.0f;

    temp_v0 = func_15149130((arg1 == -1) ? 0x12C : arg1, -1, 0x24, -1, (arg1 == -1) ? 0 : 1, 0x23, (struct37 *)0x10, arg2, arg3);
    if (temp_v0 != NULL) {
        memcpy((void *)((s32)temp_v0 + 0x28), &sp3C, 0x10);
        func_151D2AB0(6);
    }
    return temp_v0;
}

extern f32 D_8009FC20;
extern f32 D_8009FC24;
extern f32 D_8009FC28;
extern f32 D_8009FC2C;
extern f32 D_800BE9A4;

extern void func_1502EA98(struct127 *, u8, u8, u8, u8, s32, u8);
extern void func_15107700(struct127 *, s16, s16, s16, s32, f32, f32, s16, s16, u8 *, u8, s32);
extern void func_15107B78(struct127 *, s32, s32, s32, s32);

typedef struct {
    /* 0x00 */ struct127 *obj;
    /* 0x04 */ u8  id;
    /* 0x05 */ u8  pad5[3];
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
} Src150B54A8; /* size 0x10 */

typedef struct {
    /* 0x00 */ u8  pad0;
    /* 0x01 */ u8  unk1;
    /* 0x02 */ u8  pad2[0xA];
    /* 0x0C */ u8  unkC;
    /* 0x0D */ u8  padD;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ u8  pad10[0x18];
    /* 0x28 */ Src150B54A8 src;
} Emitter150B54A8;

void func_150B54A8(Emitter150B54A8 *arg0) {
    Src150B54A8 *src;
    struct127 *obj;

    obj = arg0->src.obj;
    src = &arg0->src;
    if ((obj->interaction_state == 0) || (obj->unique_id != src->id) || (obj->id == 0xFF)) {
        arg0->unkE = -1;
        return;
    }
    func_1502EA98(obj, 0xFF, 0xFF, 0xFF, 0x1E, 0, 0xA);
    src->unk8 += (D_8009FC20 + (func_150ADA68() * D_8009FC24)) * D_800BE9A4;
    while (1.0f < src->unk8) {
        u8 colour[4];

        colour[0] = 0xBA;
        colour[1] = 0xD2;
        colour[2] = 0xFF;
        colour[3] = (func_150ADA20() % 0x7EU) + 0x82;
        func_15107700(obj, (s16)(func_150ADA20() & 0xFF), (s16)((func_150ADA20() % 0x65U) - 0x3F),
                      (s16)((func_150ADA20() & 0xF) + 0xF), 4, 129.0f,
                      (func_150ADA68() * 75.0f) + 35.0f, 0, 1, colour, arg0->unkC, arg0->unk1);
        src->unk8 -= 1.0f;
    }
    src->unkC += (D_8009FC28 + (func_150ADA68() * D_8009FC2C)) * D_800BE9A4;
    while (1.0f < src->unkC) {
        func_15107B78(obj, (s16)(func_150ADA20() & 0xFF), (s16)((func_150ADA20() % 0x65U) - 0x3F),
                      arg0->unkC, arg0->unk1);
        src->unkC -= 1.0f;
    }
}

extern void func_151D2B4C(s32);

void func_150B57C4(s32 arg0) {
    func_151D2B4C(6);
}

void func_150B57E8(struct260 *arg0) {
    func_150B57C4((s32)arg0);
    func_1514933C(arg0);
}

void func_150B5814(struct260 *arg0) {
    func_150B57C4((s32)arg0);
    func_15149368(arg0);
}

typedef struct {
    s32 unk0;
    u8  unk4;
} SubA;

typedef struct {
    s32 unk0;
    union {
        s32 w4;
        u8  b4;
    } u4;
    u8  unk8;
    u8  unk9;
} ArgB;

void func_150B5840(struct260 *arg0, s32 arg1, u8 arg2) {
    SubA *temp_v0 = (SubA *)((u8 *)arg0 + 0x28);
    ArgB *b = (ArgB *)arg1;
    s32 b0;

    if (arg2 == 0) {
        b0 = b->unk0;
        if ((b0 == temp_v0->unk0) || (b->u4.b4 == temp_v0->unk4)) {
            func_1516972C((struct102 *)arg0);
        }
    } else if (arg2 == 0x2D) {
        if (temp_v0->unk0 == b->unk0) {
            temp_v0->unk0 = b->u4.w4;
            temp_v0->unk4 = b->unk9;
        } else if (temp_v0->unk0 == b->u4.w4) {
            temp_v0->unk0 = b->unk0;
            temp_v0->unk4 = b->unk8;
        }
    }
}
