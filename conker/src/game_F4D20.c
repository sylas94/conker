#include <ultra64.h>
/* functions.h declares func_150ADA20 as returning u8 and func_15048A40 as returning void; the
 * code below needs the full word of func_150ADA20's result and func_15048A40's f32 result. */
#define func_150ADA20 func_150ADA20_hdr
#define func_15048A40 func_15048A40_hdr
#include "functions.h"
#undef func_150ADA20
#undef func_15048A40
u32 func_150ADA20(void);
f32 func_15048A40(u8 arg0);
#include "variables.h"


extern void func_1511650C(struct131 *arg0, s32, s32, f32);
extern struct131 *func_151149AC(u8);

void func_150C7870(struct131 *arg0) {
    if (!(((u8 *)D_800D2E4C)[0xA] & 8)) {
        if (!(((u8 *)D_800DBEF4)[0x73] & 4)) {
            func_1511650C(arg0, 1, 0x353, 1000.0f);
        } else {
            func_1511650C(arg0, 1, 0x43, 400.0f);
        }
    }
}

typedef struct {
    u8  pad00[0x3C];
    s32 unk3C;
    u8  pad40[0x33];
    u8  unk73;
    u8  pad74[0x16C];
    s32 unk1E0;
    u8  pad1E4[0x38];
    s32 unk21C;
} GameObj150C78E0;

typedef struct {
    u8  pad00[0x3C];
    s32 unk3C;
} SubObj150C78E0;

extern void func_151150BC(GameObj150C78E0 *);

void func_150C78E0(GameObj150C78E0 *arg0) {
    SubObj150C78E0 *temp;

    if (!(arg0->unk73 & 4)) {
        temp = (SubObj150C78E0 *)((u8 *)D_800DBEF4 + 0x1E0);
        arg0->unk3C = -(temp->unk3C & 0xFFFF0000) & 0xFFFF0000;
        func_151150BC(arg0);
    }
}

void func_150C7930(GameObj150C78E0 *arg0) {
    SubObj150C78E0 *temp;

    temp = (SubObj150C78E0 *)((u8 *)D_800DBEF4 + 0x1E0);
    arg0->unk3C = temp->unk3C & 0xFFFF0000;
    func_151150BC(arg0);
}

extern s32 func_15116110(GameObj150C78E0 *);

typedef struct {
    u8  pad00[0x13];
    s8  unk13;
} Obj7C;

typedef struct {
    u8  pad00[0x3C];
    s16 unk3C;
} SubObj7968;

typedef struct {
    u8  pad00[0x73];
    u8  unk73;
    u8  pad74[0x8];
    Obj7C *unk7C;
} GameObj150C7968;

void func_150C7968(GameObj150C7968 *arg0) {
    SubObj7968 *temp;
    Obj7C *obj;
    s32 t;

    func_15116110((GameObj150C78E0 *)arg0);
    if (!(arg0->unk73 & 4)) {
        temp = (SubObj7968 *)((u8 *)D_800DBEF4 + 0x1E0);
        obj = arg0->unk7C;
        t = temp->unk3C >> 4;
        if (obj != 0) {
            obj->unk13 = t;
        }
    }
}

extern void func_1000D96C(s32, s32, s32);
extern void func_1000DE1C(s32, s32);
extern f32 func_150489B0(u8);
extern void func_15179FE0(u8, s16, s16, s16, s8, u16, u16, u8, u8, u8, s32);
extern f32 D_800A04D0;
extern f32 D_800A04D4;
extern s32 D_800887F4;

void func_150C79BC(s32 arg0) {
    s32 x;
    s32 y;
    s32 z;
    s32 r;
    s32 t;
    u8 ang;

    x = (s32)D_800DBFF0[arg0].unk2F8 + 2418;
    y = (s32)D_800DBFF0[arg0].unk2FC - 2500;
    z = (s32)D_800DBFF0[arg0].unk300 - 1775;
    if ((y >= -199) && (((x * x) + (z * z)) < 1440000)) {
        if (D_800887F4 == 0) {
            func_1000D96C(0x5F, 0xF, 6);
            func_1000DE1C(0x10, 4);
            D_800887F4 = 1;
        }
    } else {
        if (D_800887F4 != 0) {
            func_1000D96C(0xF, 0x5F, 4);
            func_1000D96C(0x10, 0, 3);
            D_800887F4 = 0;
        }
    }
    y = (s32)D_800DBFF0[arg0].unk2FC - 1583;
    if ((y < 0) && (((x * x) + (z * z)) < 810000) &&
        ((func_150ADA20() & 0xFFFF) < 0x2000)) {
        r = func_150ADA20() % 900;
        ang = func_150ADA20();
        x = (s32)((func_150489B0(ang) * (f32)r) + D_800A04D0);
        z = (s32)((func_15048A40(ang) * (f32)r) + D_800A04D4);
        t = (s32)((f32)((func_150ADA20() & 0xFFFF) * 2) * 0.0000152587890625f);
        func_15179FE0(t, (s16)x, 1583, (s16)z, 7, 1200, 37, 10, 30, 3, 8);
    }
}

typedef struct {
    s32 unk0;
    s32 unk4;
} Entry150C7C90;

typedef struct {
    u8 pad00[0x1C];
    Entry150C7C90 *unk1C;
    u8 pad20[0x1C];
    s32 unk3C;
    u8 pad40[0x3C];
    s32 unk7C;
} GameObj150C7C90;

void func_150C7C90(GameObj150C7C90 *arg0) {
    Entry150C7C90 *entry;
    Entry150C7C90 *selected;
    s32 idx;
    s32 count;
    s32 angle;
    s32 word;
    s32 newWord;

    idx = arg0->unk7C;
    if (idx == 0) {
        selected = arg0->unk1C;
        count = 0;
        if (*(s8 *)&selected->unk0 != -0xE) {
            do {
                count++;
            } while (*(s8 *)&selected[count].unk0 != -0xE);
        }
        arg0->unk7C = count;
        idx = count;
    }
    selected = &arg0->unk1C[idx];
    angle = -0x29D - func_151149AC(arg0->unk3C & 0xFF)->unk12;
    if (arg0->unk3C & 0x8000) {
        angle = 0x344 - angle;
    }
    while (angle < 0) {
        angle += 0x400;
    }
    while (angle >= 0x400) {
        angle -= 0x400;
    }
    selected->unk0 &= ~0xFFF;
    selected->unk0 |= angle;
}

typedef struct {
    u8 pad00[0x10];
    s16 unk10;
    s16 unk12;
    s16 unk14;
} GameObj150C7D7C;

void func_150C7D7C(GameObj150C7D7C *arg0) {
    struct127 *temp_v0;

    temp_v0 = func_15083E90(0xC);
    arg0->unk10 = (s16)(s32)(temp_v0->x_position - 30.0f);
    arg0->unk12 = (s16)(s32)(temp_v0->y_position + 50.0f);
    arg0->unk14 = (s16)(s32)(temp_v0->z_position + 30.0f);
}
