#include <ultra64.h>
#include "functions.h"
#include "variables.h"

typedef struct {
    u8  pad0[0xC];
    s16 unkC;
    s16 unkE;
    s16 unk10;
    s16 unk12;
    s16 unk14;
    s8  unk16;
    u8  unk17;
} Struct8008D050; /* size 0x18 */

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
} Struct800DDE60;

typedef struct {
    u8  pad0[0x14];
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    u8  pad20[0x8];
    f32 unk28;
} Struct15182FDC;

extern u8 D_800DDE54[];
extern u8 D_8008D058[];
extern Struct8008D050 D_8008D050[];
extern Struct800DDE60 *D_800DDE60[];

void func_150A7960(f32 *mtx, f32 x, f32 y, f32 z, f32 *outX, f32 *outY, f32 *outZ);

#pragma GLOBAL_ASM("asm/nonmatchings/game_1AFC80/func_151827D0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1AFC80/func_15182C5C.s")

f32 func_15182F58(s32 arg0, s32 arg1) {
    f32 var_f0;
    f32 var_f2;

    var_f0 = 0.0f;
    var_f2 = *(f32 *) &D_8008D058[D_800DDE54[arg1] * 0x18] * (f32) (arg0 * 0x28);
    if (var_f2 < var_f0) {
        var_f2 = var_f0;
    } else {
        var_f0 = 39.0f;
        if (var_f0 < var_f2) {
            var_f2 = var_f0;
        }
    }
    return var_f2;
}

s32 func_15182FDC(Struct15182FDC *arg0, s32 arg1, s32 arg2) {
    f32 dx;
    f32 dy;
    f32 dz;
    f32 x;
    f32 y;
    f32 z;
    f32 nx;
    f32 ny;
    f32 nz;
    f32 mtx[4][4];
    s32 idx;
    s32 row;
    s8 val;

    if (3.0f < arg0->unk28) {
        return 0;
    }

    idx = D_8008D050[D_800DDE54[arg2]].unk12;
    nx = (f32) D_800DBEF4[idx].unk10;
    ny = (f32) D_800DBEF4[idx].unk12;
    nz = (f32) D_800DBEF4[idx].unk14;
    if ((arg0->unk18 < ((D_800DDE60[arg2][arg1].unk8 * 0.0625f) + ny) - 300.0f) ||
        (((D_800DDE60[arg2][arg1].unk8 * 0.0625f) + ny) + 300.0f < arg0->unk18)) {
        return 0;
    }

    dx = arg0->unk14 - nx;
    dy = 0.0f;
    dz = arg0->unk1C - nz;
    func_150A8050(mtx, 0.0f, (f32) D_8008D050[D_800DDE54[arg2]].unk10, 0.0f);
    func_150A7960(&mtx[0][0], dx, dy, dz, &x, &y, &z);

    if ((0.0f < z) || (z < (f32) D_8008D050[D_800DDE54[arg2]].unkC) || (x < 0.0f) ||
        ((f32) D_8008D050[D_800DDE54[arg2]].unkE < x)) {
        return 0;
    }

    row = (s32) func_15182F58((s32) z, arg2);
    val = D_8008D050[D_800DDE54[arg2]].unk16;
    idx = row + 1;
    if (arg1 == row) {
        return val;
    }
    if ((arg1 == idx) || (arg1 + 1 == row)) {
        return (val * 4) / 7;
    }
    return 0;
}
