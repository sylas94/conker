#include <ultra64.h>
/* functions.h declares func_1515D4D4 with u8 colour parameters, which makes the
 * caller mask each argument with `andi 0xFF`.  The golden call site here passes a
 * full word straight out of trunc.w.s with no mask, and the callee masks its own
 * 4th argument -- so the declaration visible to this translation unit took plain
 * words.  Shadow the header declaration rather than edit the shared header. */
#define func_1515D4D4 func_1515D4D4_prototype
#include "functions.h"
#undef func_1515D4D4
#include "variables.h"

void func_1515D4D4(s32, s32, s32, s32);

extern f32 D_800A08E0;

typedef struct {
    u8 pad0[0x28];
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
} Obj150D1B40;

void func_150D1B40(Obj150D1B40 *arg0) {
    f32 *p = &arg0->unk28;

    func_151467A4(&arg0->unk30, 10.0f, &arg0->unk2C, 86.0f, 170.0f, 255.0f, D_800A08E0, p);
    func_1515D4D4((s32)*p, ((u8 *)&D_800DCD20)[1], ((u8 *)&D_800DCD20)[2], 0);
}

s32 func_1509BE40(s32, s32, s32, s32);

void func_150D1BD0(s32 *arg0) {
    if (func_1509BE40(1, 0x402C, 6, 0x2000) != 0) {
        arg0[0x21] |= 0x10;
    } else {
        arg0[0x21] &= ~0x10;
    }
}
