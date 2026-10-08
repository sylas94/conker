#include <ultra64.h>
/* functions.h types func_150ADA20 as returning u8; golden spills/uses the full u32 return
 * (same shadow-prototype idiom as game_121A20.c). */
#define func_150ADA20 func_150ADA20_u8_decl_in_functions_h
#include "functions.h"
#undef func_150ADA20
u32 func_150ADA20(void);
#include "variables.h"

void func_150A7960(f32 *, f32, f32, f32, f32 *, f32 *, f32 *);

void func_150D82B0(s32 arg0) {
}

typedef struct Pos150D82BC {
    f32 unk0;
    f32 unk4;
    f32 unk8;
} Pos150D82BC;

typedef struct Actor150D82BC {
    u8 pad0[0x84];
    u16 unk84;
    u8 pad86[0x24A];
    Pos150D82BC *unk2D0;
} Actor150D82BC;

typedef struct Draw150D82BC {
    u8 pad0[0x18];
    s16 unk18;
    u8 pad1A[0xA];
    Gfx **unk24;
} Draw150D82BC;

extern s32 D_80090298[];
extern f32 D_800A0B10; /* 1/17; stays in asm/data/2455D0.rodata.s (shared with func_150D83D8/func_150D85AC) */

s32 func_150D82BC(Draw150D82BC *arg0, Actor150D82BC *arg1) {
    Pos150D82BC *pos = arg1->unk2D0;
    Gfx *list;
    s32 i;
    s32 uls;
    s32 w;
    f32 t;

    if (pos == NULL) {
        return 0;
    }
    arg0->unk18 = D_80090298[6];
    if (arg1->unk84 == 0xD) {
        if (23.0f <= pos->unk8 && pos->unk8 <= 40.0f) {
            arg0->unk18 = D_80090298[7];
            t = pos->unk8 - 23.0f;
            t *= D_800A0B10;
            list = *arg0->unk24;
            i = 0;
            while (((s8 *)&list[i])[0] != (s8)G_SETTILESIZE) {
                i++;
            }
            w = list[i].words.w0;
            uls = 70.0f * t + 2.0f;
            if (uls < 0) {
                uls += (w >> 12) & 0xFFF;
            }
            list[i].words.w0 = _SHIFTL(G_SETTILESIZE, 24, 8) | _SHIFTL(uls, 12, 12) | _SHIFTL(2, 0, 12);
        }
    }
    return 0;
}

typedef struct Draw150D83D8 {
    u8 pad0[0x18];
    s16 unk18;
    u8 pad1A[0xA];
    Gfx **unk24;
    u8 pad28[0x10];
    s32 unk38;
    s32 unk3C;
} Draw150D83D8;

extern f32 D_800A0B14; /* 0.01f; asm/data/2455D0.rodata.s */

s32 func_150D83D8(Draw150D83D8 *arg0, Actor150D82BC *arg1) {
    Gfx *list;
    s32 i;
    f32 t;

    switch (arg0->unk38) {
        case 0:
            arg0->unk3C = 50;
            arg0->unk18 = D_80090298[27];
            if (arg1->unk84 == 0x18D && 46.0f <= arg1->unk2D0->unk8) {
                arg0->unk38 = 1;
                arg0->unk18 = D_80090298[28];
            }
            break;
        case 1:
            arg0->unk3C += D_800BE9E4;
            if (arg0->unk3C >= 100) {
                arg0->unk3C = 100;
                arg0->unk38 = 2;
            }
            break;
        case 2:
            if (arg1->unk84 == 0x18E && 34.0f <= arg1->unk2D0->unk8) {
                arg0->unk38 = 3;
            }
            break;
        case 3:
            arg0->unk3C -= D_800BE9E4 * 4;
            if (arg0->unk3C <= 0) {
                arg0->unk3C = 0;
                arg0->unk38 = 4;
            }
            break;
    }
    t = arg0->unk3C * D_800A0B14;
    list = *arg0->unk24;
    i = 0;
    while (((s8 *)&list[i])[0] != (s8)G_SETTILESIZE) {
        i++;
    }
    list[i].words.w0 = _SHIFTL(G_SETTILESIZE, 24, 8) | _SHIFTL(2, 12, 12) | _SHIFTL((s32)(120.0f * t + 2.0f), 0, 12);
    return 0;
}

s16 *func_150D8590(s16 *arg0, s32 arg1) {
    arg0[0] = 0x42;
    arg0[1] = 0;
    return arg0 + 2;
}

typedef struct {
    s16 unk0;
    s16 unk2;
    u8 unk4;
    u8 pad5;
    u16 unk6;
    s32 unk8;
    s32 unkC;
    s16 unk10;
    s16 unk12;
    s32 unk14;
    s32 unk18;
    u8 unk1C;
    u8 unk1D;
    u8 unk1E;
    u8 unk1F;
    u8 unk20;
    u8 unk21;
    u8 unk22;
    u8 unk23;
    u8 unk24;
    u8 unk25;
    s16 unk26;
    s16 unk28;
    s16 unk2A;
    f32 unk2C;
    f32 unk30;
    f32 unk34;
    struct17 unk38;
    s16 unk44;
    s16 unk46;
    s16 unk48;
    s16 unk4A;
    f32 unk4C;
    f32 unk50;
    f32 unk54;
    f32 unk58;
    s32 unk5C;
    s8 unk60;
    s8 unk61;
    u8 unk62;
    u8 unk63;
    u8 unk64;
    u8 pad65[3];
    f32 unk68;
} Arg15153634;

typedef struct {
    /* 0x00 */ f32 unk00;
    /* 0x04 */ f32 unk04;
    /* 0x08 */ f32 unk08;
    /* 0x0C */ f32 unk0C;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ u8 unk1C;
    /* 0x1D */ u8 pad1D[0x7];
} Struct1504715C; /* 0x24 */

void func_1504715C(Struct1504715C *, s32);
s32 func_15046C80(struct17 *, s32, f32, void *);
void func_150E7FEC(f32, s32, void *, void *, s32, s32, s32, s32, s32, s32, s32, s32);
void func_150E83AC(struct17 *, s16, u8, s32);
void func_15153634(Arg15153634 *, s32, u8, s32);
extern f32 D_800A0B18; /* asm/data/2455D0.rodata.s */
extern f32 D_800A0B1C;
extern f32 D_800A0B20;
extern f32 D_800A0B24;

void func_150D85AC(struct127 *arg0) {
    struct17 pos;
    struct17 top;
    Struct1504715C hit;

    pos.unk0 = arg0->x_position;
    pos.unk4 = arg0->unk180;
    pos.unk8 = arg0->z_position;
    {
        extern void func_1504715C(Struct1504715C *, s32);

        top.unk0 = pos.unk0;
        top.unk4 = pos.unk4 + 100.0f;
        top.unk8 = pos.unk8;
        func_1504715C(&hit, (s32)arg0);
    }
    if (func_15046C80(&top, 0, pos.unk4 - 200.0f, &hit) != 0) {
        if (hit.unk1C & 1) {
            pos.unk0 = top.unk0;
            pos.unk4 = hit.unk00;
            pos.unk8 = top.unk8;
            func_150E7FEC(func_150ADA68() * 109.0f + 140.0f, (u8)(func_150ADA20() % 86 + 170), &hit.unk04, &pos,
                          func_150ADA20() % 251 + 500, 0, 1, 0, 0, 0, 0xFF, 0);
        }
    }
    func_150E83AC(&pos, func_150ADA20() % 62 + 120, 0xFF, 1);
    {
        Arg15153634 a;

        a.unk0 = 0x1A;
        a.unk2 = 7;
        a.unk4 = 0x6C;
        a.unk6 = 0x5103;
        a.unk8 = 0x200005;
        a.unkC = 0;
        a.unk10 = 0x1E;
        a.unk12 = 0xA;
        a.unk14 = 0;
        a.unk18 = 0;
        a.unk1F = 0xFF;
        a.unk1C = 0xB9;
        a.unk1D = 0xC7;
        a.unk1E = 0xC4;
        a.unk20 = 0x95;
        a.unk21 = 0x91;
        a.unk22 = 0x7E;
        a.unk23 = 0x64;
        a.unk24 = 0x9B;
        a.unk25 = 0xFF;
        a.unk26 = 0x1E;
        a.unk28 = 8;
        a.unk2A = 0x1E;
        a.unk2C = D_800A0B18;
        a.unk30 = 150.0f;
        a.unk34 = 298.0f;
        a.unk38.unk0 = pos.unk0;
        a.unk38.unk4 = pos.unk4 + 35.0f;
        a.unk38.unk8 = pos.unk8;
        a.unk44 = 0;
        a.unk46 = -0x10;
        a.unk48 = 0xFF;
        a.unk4A = 0x14;
        a.unk4C = 18.0f;
        a.unk50 = 18.0f;
        a.unk54 = D_800A0B1C;
        a.unk58 = D_800A0B20;
        a.unk5C = 0x840E07;
        a.unk60 = 0x10;
        a.unk61 = -1;
        a.unk62 = 8;
        a.unk63 = 6;
        a.unk64 = 1;
        a.unk68 = D_800A0B24;
        func_15153634(&a, 0xFF, 0xFF, 1);
    }
}

struct S150D88AC {
    u8 pad0[0x14];
    u8 *unk14;
    u8 *unk18;
};

s32 func_150D88AC(struct S150D88AC *arg0) {
    if (arg0->unk18[0x6F] != 0) {
        arg0->unk14[0x9] = 0;
    } else {
        arg0->unk14[0x9] = 1;
    }
    return 1;
}

s32 func_150D88E0(void *arg0, struct127 *arg1, u8 arg2) {
    struct {
        f32 z;
        f32 y;
        f32 x;
        s32 temp_a1;
    } sp30;

    switch (arg2) {
    case 3:
        sp30.temp_a1 = 0x12;
        sp30.x = -7.0f;
        sp30.z = 30.0f;
        break;
    case 4:
        sp30.temp_a1 = 0x15;
        sp30.x = -4.0f;
        sp30.z = 35.0f;
        break;
    case 5:
        sp30.temp_a1 = 0xF;
        sp30.x = 5.0f;
        sp30.z = 20.0f;
        break;
    case 6:
        sp30.temp_a1 = 0x18;
        sp30.x = 5.0f;
        sp30.z = 31.0f;
        break;
    }

    sp30.y = 0.0f;
    func_150A7960((f32 *)((u8 *)arg1->unk1D4 + (sp30.temp_a1 << 6)), sp30.x, sp30.y, sp30.z, &sp30.x, &sp30.y, &sp30.z);
    ((f32 *)arg0)[0] = sp30.x;
    ((f32 *)arg0)[1] = sp30.y;
    ((f32 *)arg0)[2] = sp30.z;
    return 1;
}

s32 func_150D8A20(s32 arg0, s32 arg1) {
    return 0x8;
}

extern f32 D_800A0B30;
extern f32 D_800A0B34;
s32 func_150D88E0(void *, struct127 *, u8);
void func_151875E0(f32, f32, f32, s32, s32, s32, f32, f32);
void func_15165F80(s32, s32, s32, s32, s32, s32, s32, s32, s32);

void func_150D8A34(struct127 *arg0, s32 arg1, s32 arg2) {
    struct { f32 x; f32 y; f32 z; } sp34;

    if (arg0->unk1D4 != NULL) {
        func_150D88E0(&sp34, arg0, (u8)arg1);
        func_151875E0(sp34.x, sp34.y, sp34.z, 0x1E, 0xF, 0x7, D_800A0B30, D_800A0B34);
        func_15165F80(-1, (s32)sp34.x, (s32)(arg0->unk180 + 4.0f), (s32)sp34.z, 4, 0x32, 0, 0xFF, 0);
    }
}
