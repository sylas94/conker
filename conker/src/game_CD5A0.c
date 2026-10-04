#include <ultra64.h>
#include "functions.h"
#include "variables.h"


/* 12-byte slot record. The first word is a bitfield: golden reads it whole (`lw` + `srl 31`)
   for the guard and updates the top byte in place (`lbu`/`sb`) for each field write, which is
   exactly what these bitfield assignments produce. */
typedef struct Rec150A0264 {
    u32 unk0_b0 : 1;
    u32 unk0_b1 : 1;
    u32 unk0_b2 : 4;
    u32 unk0_b6 : 2;
    u32 unk0_rest : 24;
    u32 unk4;
    u32 unk8;
} Rec150A0264;

typedef struct Src150A0264 {
    char pad0[4];
    s32 unk4;
    s32 unk8;
} Src150A0264;

extern Rec150A0264 D_800D3010[];

/* NEAR MISS, mism=65 n=46/43 (THREE OVER). The shape is certainly
       for (i = 0; i < 10; i++) { D_800D3010[i].unk0_b0 = 0; .unk4 = 0; .unk8 = 0; }
   -- golden PEELS records 0 and 1 and then runs a 4-records-per-iteration unrolled loop
   from &D_800D3010[2] to &D_800D3010[10], which is what IDO does to this loop; we get the
   same shape but three instructions long. Try a pointer walk instead of the index, and
   check whether the peel wants the two records written out explicitly.
#pragma GLOBAL_ASM removed only when it reaches 0. */
#pragma GLOBAL_ASM("asm/nonmatchings/game_CD5A0/func_150A00F0.s")

extern u16 D_80088510[];
extern u16 D_8008851C[];

void func_150A019C(void) {
    s32 i;

    for (i = 0; i < 10; i++) {
        if ((D_800D3010[i].unk0_b0 != 0) && (D_800D3010[i].unk0_b1 == 1)) {
            D_800D3010[i].unk8 = D_800D3010[i].unk8 + D_800BE9E4;
            if (D_800D3010[i].unk8 >= D_80088510[D_800D3010[i].unk0_b2]) {
                D_800D3010[i].unk8 = D_800D3010[i].unk8 - D_80088510[D_800D3010[i].unk0_b2];
                D_800D3010[i].unk4 = D_800D3010[i].unk4 + 1;
                if (D_8008851C[D_800D3010[i].unk0_b2] != 0) {
                    D_800D3010[i].unk4 = D_800D3010[i].unk4 % D_8008851C[D_800D3010[i].unk0_b2];
                }
            }
        }
    }
}


s32 func_150A0264(s32 arg0, Src150A0264 *arg1) {
    Rec150A0264 *r = &D_800D3010[arg0];

    if (r->unk0_b0 != 0) {
        return 0;
    }
    r->unk0_b0 = 1;
    r->unk0_b1 = 0;
    r->unk0_b2 = arg1->unk4;
    r->unk4 = 0;
    return 1;
}

s32 func_150A02D0(s32 arg0, s32 arg1, Src150A0264 *arg2) {
    switch (arg1) {
    case 0:
        D_800D3010[arg0].unk0_b1 = 1;
        return 1;
    case 1:
        D_800D3010[arg0].unk0_b1 = 0;
        return 1;
    case 2:
        D_800D3010[arg0].unk4 = arg2->unk8;
        return 1;
    }
    return 0;
}

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} D3014Struct;

extern D3014Struct D_800D3014[];

s32 func_150A0374(s32 arg0, s32 arg1, s32 arg2) {
    if (arg1 == 3) {
        return D_800D3014[arg0].unk0;
    }
    return 0;
}
