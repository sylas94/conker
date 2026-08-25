#include <ultra64.h>

#include "functions.h"
#include "variables.h"

extern u8 D_800A1C00[][8];
extern s32 func_151149AC(u8);

typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ u8  unk14;
    /* 0x15 */ u8  unk15;
    /* 0x16 */ u8  unk16;
    /* 0x17 */ u8  unk17;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ u8  unk24[0x1C];
} ObjRec; /* size 0x40 */

typedef struct {
    /* 0x00 */ void *unk0;
    /* 0x04 */ u8  unk4;
    /* 0x05 */ u8  unk5;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ u8  unk8;
    /* 0x09 */ u8  pad9[3];
    /* 0x0C */ s32 unkC[8];
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ s16 unk3C;
    /* 0x3E */ s16 pad3E;
    /* 0x40 */ f32 unk40;
    /* 0x44 */ f32 unk44;
    /* 0x48 */ f32 unk48;
} Struct11D60; /* size 0x4C */

typedef struct {
    /* 0x00 */ u8  pad0[0x1C];
    /* 0x1C */ s32 unk1C;
} Arg11D60;

extern ObjRec *func_151438D8(s32, s32, u16, ObjRec *);

void func_15011D40(void) {
    func_15103800();
}

s32 func_15011D60(Arg11D60 *arg0) {
    Struct11D60 tmp;
    ObjRec obj;
    ObjRec *found;
    u8 flag;


    bzero(&tmp, 0x4C);
    tmp.unk8 = 0;
    tmp.unk6 = (func_150ADA20() % 0x79U) + 0x12C;
    tmp.unk0 = arg0;

    tmp.unk4 = arg0->unk1C;
    if (tmp.unk4 >= 4) {
        flag = 1;
    } else {
        flag = 0;
    }
    tmp.unk5 = flag;
    {
        u8 i;
        for (i = 0; i < 8; i++) {
            tmp.unkC[i] = func_151149AC(D_800A1C00[i][tmp.unk4]);
        }
        tmp.unk3C = 0;
        tmp.unk2C = 0.0f;
        tmp.unk30 = 0.0f;
        tmp.unk34 = 0.0f;
        tmp.unk38 = 0.0f;
    }
    obj.unk15 = 3;
    obj.unk17 = 0x15;
    obj.unk18 = tmp.unk4;
    found = func_151438D8(0, D_800D3094, 0x11A0, &obj);
    if (found != NULL) {
        tmp.unk40 = found->unk0;
        tmp.unk44 = found->unk4;
        tmp.unk48 = found->unk6;
    } else {
        tmp.unk48 = 10.0f;
    }
    found = (ObjRec *)func_15149130(0x12C, -1, -1, -1, 0, 0x38, (struct37 *)0x4C, 0xFF, 1);
    if (found != NULL) {
        memcpy((u8 *)found + 0x28, &tmp, 0x4C);
    }
    return 1;
}
