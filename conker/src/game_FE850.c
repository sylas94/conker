#include <ultra64.h>
/* See game_FEFF0.c: functions.h's u8 colour parameters for func_1515D4D4 make the
 * caller emit `andi 0xFF` masks that the golden does not have.  Shadow the header
 * declaration locally rather than edit the shared header. */
#define func_1515D4D4 func_1515D4D4_prototype
#include "functions.h"
#undef func_1515D4D4
#include "variables.h"

void func_1515D4D4(s32, s32, s32, s32);


extern f32 D_800A08B0;
extern f32 D_800A08B4;
extern f32 D_800A08B8;
extern void func_15059C84(s32);

struct Obj150D13A0 {
    u8 pad0[0x3C];
    f32 unk3C;
    u8 pad40[0xB8 - 0x40];
    f32 unkB8;
    f32 unkBC;
    f32 unkC0;
    f32 unkC4;
    u8 padC8[0x148 - 0xC8];
    f32 unk148;
};

void func_150D13A0(s32 arg0) {
    struct Obj150D13A0 *temp = (struct Obj150D13A0 *)arg0;

    temp->unkB8 = temp->unkB8 + temp->unkBC;
    temp->unkBC = temp->unkBC * D_800A08B0;
    temp->unk3C = temp->unk3C * D_800A08B4;
    temp->unkC4 = temp->unkC4 + temp->unk148;
    temp->unk148 = temp->unk148 * D_800A08B8;
    func_15059C84(arg0);
}

extern s32 func_151149AC(u32);

struct Obj150D1410 {
    u8 pad0[0x6E];
    u8 unk6E;
};

void func_150D1410(s32 arg0) {
    struct Obj150D1410 *temp;

    temp = (struct Obj150D1410 *)func_151149AC(0xF9);
    if (temp != 0) {
        if (((arg0 - (s32)&D_800CC2D0[0]) / 0x32C) == 0) {
            temp->unk6E = 1;
        } else {
            temp->unk6E = 0;
        }
    }
}

struct Obj150D146C {
    u8 pad0[0x6E];
    u8 unk6E;
};

void func_150D146C(s32 arg0) {
    struct Obj150D146C *temp;

    temp = (struct Obj150D146C *)func_151149AC(0xF9);
    if (temp != 0) {
        temp->unk6E = 1;
    }
}

extern f32 D_800A08C0;

typedef struct {
    u8 pad0[0x28];
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
} Obj150D149C;

void func_150D149C(Obj150D149C *arg0) {
    f32 *p = &arg0->unk28;

    func_151467A4(&arg0->unk30, 10.0f, &arg0->unk2C, 50.0f, 100.0f, 123.0f, D_800A08C0, p);
    func_1515D4D4((s32)*p, ((u8 *)&D_800DCD20)[1], ((u8 *)&D_800DCD20)[2], 0);
}
