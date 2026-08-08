#include <ultra64.h>
#include "functions.h"
#include "variables.h"

typedef struct {
    char pad_0[0x10];
    Mtx field_0x10[3];
    u8 field_0xD0;
    char pad_0xD1[0x1];
    s16 field_0xD2;
    s16 field_0xD4;
    s16 field_0xD6;
    f32 field_0xD8;
} ObjType0DData;

extern void *func_15167A68(s32, s32, s32, s32, s32, s32);
extern void func_1517E05C(s32, s32, s32);
extern s32 D_8009054C;
extern s32 D_800DD220;
extern s32 D_800DD224;
extern s32 D_800DD228[];
extern s32 D_800DD230;

void func_151669A0(s32 arg0, s32 arg1, s32 arg2, f32 arg3, s32 arg4, s32 arg5) {
    ObjType0DData *temp_v0;
    Mtx *mtx;
    s32 temp_s0;
    s32 i;
    f32 temp_f24;
    f32 temp_f26;
    f32 temp_f28;

    temp_v0 = func_15167A68(0xD, arg5, 0xE0, 1, (u8)arg4, 1);
    if (temp_v0 != 0) {
        temp_v0->field_0xD0 = 0xA;
        temp_v0->field_0xD2 = arg0;
        temp_v0->field_0xD4 = arg1;
        temp_v0->field_0xD6 = arg2;
        temp_v0->field_0xD8 = arg3;

        temp_s0 = func_150ADA20() & 0x7F;
        temp_f24 = arg0;
        temp_f26 = arg1;
        temp_f28 = arg2;
        mtx = temp_v0->field_0x10;
        for (i = 0; i != 0xC0; i += 0x40) {
            if (arg3 != 1.0f) {
                func_15043D90(mtx, 0.0f, temp_s0, 0.0f, arg3, arg3, arg3, temp_f24, temp_f26, temp_f28);
            } else {
                func_15043E68(mtx, 0.0f, temp_s0, 0.0f, temp_f24, temp_f26, temp_f28);
            }
            temp_s0 += func_150ADA20() & 0x3F;
            mtx++;
            temp_s0 += 0x5A;
        }
        func_1517E05C(arg0, arg1, arg2);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_193E50/func_15166B50.s")

extern Vtx D_8008B3E0[];

Gfx *func_15166D68(Gfx *pkt, ObjType0DData *obj, s32 arg2) {
    Mtx *mtx;
    s32 s;
    s32 i;

    for (i = 0, mtx = obj->field_0x10; i != 0xC0; i += 0x40) {
        gSPMatrix(pkt++, mtx, G_MTX_LOAD);
        gSPVertex(pkt++, D_8008B3E0, 6, 0);
        s = 0x2800 - ((obj->field_0xD0 << 12) / 10);
        gSPModifyVertex(pkt++, 0, G_MWO_POINT_ST, (s << 16) + 0x2000);
        gSPModifyVertex(pkt++, 1, G_MWO_POINT_ST, (s << 16) + 0x2000);
        gSPModifyVertex(pkt++, 2, G_MWO_POINT_ST, (s << 16) + 0x2400);
        gSPModifyVertex(pkt++, 3, G_MWO_POINT_ST, ((s + 0x800) << 16) + 0x2000);
        gSPModifyVertex(pkt++, 4, G_MWO_POINT_ST, ((s + 0x800) << 16) + 0x2000);
        gSPModifyVertex(pkt++, 5, G_MWO_POINT_ST, ((s + 0x800) << 16) + 0x2400);
        gSP1Triangle(pkt++, 5, 3, 0, 0);
        gSP1Triangle(pkt++, 2, 5, 0, 0);
        gSP1Triangle(pkt++, 1, 4, 5, 0);
        gSP1Triangle(pkt++, 1, 5, 2, 0);
        mtx++;
    }
    return pkt;
}

void func_15166F6C(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    D_800DD228[0] = (s32)&D_8009054C;
    func_15094F70(arg0, D_800DD228[0], D_800DD220, (s32)&D_800DD230, 0, 0, 0, D_800DD224, 3);
}

extern Mtx D_80089470;

Gfx *func_15166FD8(Gfx *pkt, s32 arg1, s32 arg2) {
    gSPMatrix(pkt++, &D_80089470, G_MTX_LOAD);
    return pkt;
}
