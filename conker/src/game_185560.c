#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern s32 (*D_8008AE00[])(void *);

typedef struct {
    f32 m[4][4];
} MtxF15158920;

extern MtxF15158920 D_8008AE18;
extern f32 D_800A6070;

typedef struct {
    struct WORD words[10];
} Struct1515A974PayloadWords;

typedef struct {
    struct UBYTES4 first;
    Struct1515A974PayloadWords rest;
} Struct1515A974Payload;

typedef struct {
    f32 unk0;
    f32 unk4;
    Struct1515A974Payload payload;
} Struct1515A974Row;

extern Struct1515A974Row D_800A636C[];

typedef struct {
    Struct1515A974Payload payload;
    s32 pad2C[2];
    struct183 tmp;
} Struct1515A974Locals;

typedef struct {
    u8 pad0[0xD8];
    s32 unkD8;
    u8 unkDC;
    u8 padDD[3];
    s32 unkE0[4];
    s32 unkF0;
    s32 unkF4;
} Struct151580B0;

extern Struct151580B0 *func_15167A68(s32, s32, s32, s32, s32, s32);
extern s32 func_1515D480(s32);
extern s32 func_1515D440(void);
s32 func_15159370();

s32 func_151580B0(void *arg0, s32 arg1, s32 arg2, u8 arg3, s32 arg4, u8 arg5, s32 arg6) {
    Struct151580B0 *temp_v0;
    s32 i;

    temp_v0 = func_15167A68(arg3 ? 0x55 : 0x37, arg6, arg4 + 0xF8, 1, arg5, 1);
    if (temp_v0 == 0) {
        return 0;
    }
    memcpy(&temp_v0->pad0[0x10], arg0, 0x44);
    temp_v0->unkD8 = arg1;
    temp_v0->unkF4 = arg2;
    temp_v0->unkDC = 0;
    for (i = 0; i < 4; i++) {
        temp_v0->unkE0[i] = 0;
    }

    temp_v0->unkF0 = 0;
    if (arg1) {
        for (i = 0; i <= D_80082FA0; i++) {
            temp_v0->unkE0[i] = func_1515D480(arg1);
        }
        temp_v0->unkF0 = func_1515D440();
    }
    return (s32) temp_v0;
}

s32 func_151580B0(void *arg0, s32 arg1, s32 arg2, u8 arg3, s32 arg4, u8 arg5, s32 arg6);

s32 func_151581D8(void *arg0, u8 arg1, s32 arg2, u8 arg3, s32 arg4) {
    return func_151580B0(arg0, 0, 0, arg1, arg2, arg3, arg4);
}

typedef struct {
    u8 pad0[0x10];
    u8 unk10;
    u8 pad11;
    s8 unk12;
    u8 pad13;
    s16 unk14;
} Struct15158224;

void func_15158224(Struct15158224 *arg0) {
    s32 temp;
    u8 failed;

    failed = 0;
    if (arg0->unk10 & 1) {
        arg0->unk14 -= D_800BE9E4;
        if (arg0->unk14 < 0) {
            failed = 1;
        }
    }
    if (failed == 0) {
        temp = arg0->unk12;
        if (temp != -1) {
            if (D_8008AE00[temp](arg0) == 0) {
                failed = 1;
            }
        }
    }
    if (failed) {
        func_1516972C((struct102 *) arg0);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_185560/func_151582C8.s")

extern void guMtxF2L(f32 mf[4][4], Mtx *m);

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
} SubF8;

typedef struct {
    u8 pad0[0x48];
    f32 unk48;
    f32 unk4C;
    f32 unk50;
    u8 pad54[0xF8 - 0x54];
    SubF8 subF8;
} Obj1515;

s32 func_1515858C(Mtx *arg0, Obj1515 *arg1) {
    SubF8 *p = &arg1->subF8;
    f32 sp24[4][4];

    func_150A8050(&sp24, p->unk0, p->unk4, p->unk8);
    sp24[3][0] = arg1->unk48;
    sp24[3][1] = arg1->unk4C;
    sp24[3][2] = arg1->unk50;
    sp24[0][0] *= p->unkC;
    sp24[0][1] *= p->unkC;
    sp24[0][2] *= p->unkC;
    sp24[1][0] *= p->unkC;
    sp24[1][1] *= p->unkC;
    sp24[1][2] *= p->unkC;
    sp24[2][0] *= p->unkC;
    sp24[2][1] *= p->unkC;
    sp24[2][2] *= p->unkC;
    guMtxF2L(&sp24, arg0);
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_185560/func_15158684.s")

s32 func_15158920(Mtx *arg0, Obj1515 *arg1) {
    f32 scale;
    f32 (*unused)[4];
    f32 sp18[4][4];

    *(MtxF15158920 *)sp18 = D_8008AE18;
    scale = arg1->subF8.unk0 * D_800A6070;
    sp18[3][0] = arg1->unk48;
    sp18[3][1] = arg1->unk4C;
    sp18[3][2] = arg1->unk50;
    sp18[0][0] *= scale;
    sp18[0][1] *= scale;
    sp18[0][2] *= scale;
    sp18[1][0] *= scale;
    sp18[1][1] *= scale;
    sp18[1][2] *= scale;
    sp18[2][0] *= scale;
    sp18[2][1] *= scale;
    sp18[2][2] *= scale;
    guMtxF2L(sp18, arg0);
    return 1;
}

void func_15158A20(struct102 *arg0) {
    s32 i;
    u8 *p;
    s32 *temp;

    i = 0;
    if (D_80082FA0 >= 0) {
        p = (u8 *)arg0;
        do {
            if (*(s32 **)(p + 0xE0)) {
                temp = *(s32 **)(p + 0xE0);
                func_100043B4(temp, 4);
            }
            i++;
            p += 4;
        } while (i <= D_80082FA0);
    }
    if (*(s32 **)((u8 *)arg0 + 0xF0)) {
        temp = *(s32 **)((u8 *)arg0 + 0xF0);
        func_100043B4(temp, 4);
    }
}

void func_15158A20(struct102 *);

void func_15158AA4(struct102 *arg0) {
    func_15158A20(arg0);
    func_15169804(arg0);
}

void func_15169824(struct102 *);

void func_15158AD0(struct102 *arg0) {
    func_15158A20(arg0);
    func_15169824(arg0);
}

typedef struct {
    u8 pad0[0x14];
    s16 unk14;
    u8 pad16[0x25];
    u8 unk3B;
    u8 pad3C[0xBC];
    s16 unkF8;
    u8 padFA[0x2];
    s32 unkFC;
} Struct15158AFC;

s32 func_15158AFC(Struct15158AFC *arg0) {
    s32 temp;

    if (arg0->unk14 < arg0->unkF8) {
        temp = arg0->unk14 * arg0->unkFC;
        if (temp < arg0->unk3B) {
            arg0->unk3B = temp;
        }
    }
    return 1;
}

typedef struct 
{
  s32 unk0;
  s32 unk4;
  u8 unk8;
  u8 unk9;
} Struct15158B3Ca;
typedef struct 
{
  u8 pad0[0x40];
  s32 unk40;
  u8 unk44;
} Struct15158B3Cb;
void func_15158B3C(Struct15158B3Cb *a0, Struct15158B3Ca *a1, u8 a2)
{
  s32 v0;
  if (a2 == 0x2D)
  {
    v0 = a1->unk0;
    if (a0->unk40 == v0)
    {
      a0->unk40 = a1->unk4;
      a0->unk44 = a1->unk9;
    }
    else
    {
      if (a0->unk40 == a1->unk4)
      {
        a0->unk40 = v0;
        a0->unk44 = a1->unk8;
      }
 dummy_label_356969: ;
    }
  }
  else
    if (a2 == 0)
  {
    v0 = a1->unk0;
    if (a0->unk40 != v0)
    {
      if (a0->unk44 != (*(((u8 *) a1) + 4)))
      {
        return;
      }
    }
    a0->unk40 = 0;
    a0->unk44 = 0;
  }
}


typedef struct {
    u8 pad0[0x14];
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    u8 pad20[0x3B - 0x20];
    u8 unk3B;
} Struct15158BD0_src;

typedef struct {
    u8 pad0[0x10];
    s32 unk10;
    s32 unk14;
    Struct15158BD0_src *unk18;
    u8 unk1C;
    u8 pad1D[0x20 - 0x1D];
    f32 unk20;
    f32 unk24;
    f32 unk28;
    u8 unk2C;
    u8 unk2D;
    u8 unk2E;
    u8 unk2F;
    u8 unk30;
    u8 unk31;
    u8 pad32[0x50 - 0x32];
    u8 unk50;
} Struct15158BD0_ret;

s32 func_15158BD0(Struct15158BD0_src *arg0, u8 arg1, s32 arg2) {
    Struct15158BD0_ret *temp_v0;
    Struct15158BD0_ret *sp2C;

    if (arg0 == 0) {
        return 0;
    }
    temp_v0 = (Struct15158BD0_ret *)func_15167A68(0x2E, 0, arg2 + 0x58, 1, 0xFF, 1);
    if (temp_v0 == 0) {
        return 0;
    }
    sp2C = temp_v0;
    temp_v0->unk18 = arg0;
    temp_v0->unk1C = arg0->unk3B;
    temp_v0->unk2C = 2;
    temp_v0->unk2D = 2;
    temp_v0->unk2E = 2;
    temp_v0->unk2F = 3;
    temp_v0->unk30 = 0;
    temp_v0->unk20 = arg0->unk14;
    temp_v0->unk24 = arg0->unk18;
    temp_v0->unk28 = arg0->unk1C;
    temp_v0->unk31 = 0;
    if (arg1 != 0) {
        temp_v0->unk31 |= 1;
    }
    sp2C->unk10 = 1;
    sp2C->unk14 = 0;
    if (func_15159370(arg0, (u8 *)sp2C + 0x1D, sp2C) == 0) {
        func_1516979C((struct102 *)sp2C);
        return 0;
    }
    sp2C->unk50 = 0;
    return sp2C;
}

void func_1514EDF0(struct102 *, s32);

void func_15158CD4(struct102 *arg0) {
    func_1514EDF0(arg0, *(s32 *)((u8 *)arg0 + 0x18));
    func_15169804(arg0);
}

void func_15158D00(struct102 *arg0) {
    func_1514EDF0(arg0, *(s32 *)((u8 *)arg0 + 0x18));
    func_15169824(arg0);
}

typedef struct {
    u8 pad0[0x18];
    f32 unk18;
    u8 pad1C[0xFC];
    f32 unk118;
    u8 pad11C[0x1B];
    u8 unk137;
    u8 pad138[0x4C];
    s32 unk184;
} Struct15159084;

typedef struct {
    u8 pad0[0x118];
    f32 unk118;
    u8 pad11C[0x64];
    f32 unk180;
} Struct15159120;

typedef struct {
    u8 pad0[0x18];
    f32 unk18;
    u8 pad1C[0xFC];
    f32 unk118;
} Struct15159184;

s32 func_15159084(Struct15159084 *, u8);
s32 func_15159120(Struct15159120 *, u8);
s32 func_15159184(Struct15159184 *, u8);
s32 func_15159230(Struct15158BD0_src *, f32 *, u8);
s32 func_151592B8(Struct15158BD0_src *, u8);

typedef struct {
    u8 pad0[0x18];
    Struct15158BD0_src *unk18;
    u8 pad1C;
    u8 unk1D;
    u8 pad1E[0x20 - 0x1E];
    f32 unk20;
    f32 unk24;
    f32 unk28;
    u8 unk2C;
    u8 unk2D;
    u8 unk2E;
    u8 unk2F;
    u8 unk30;
    u8 unk31;
} Struct15158D2C;

typedef struct {
    s32 from;
    s32 to;
} Struct15158D2C_Rule;

/* Packs the five state fields into one bitfield, three bits per field. */
#define STATE_BITS(a, b, c, d, e)                                              \
    ((1 << (a)) | (1 << ((b) + 3)) | (1 << ((c) + 6)) | (1 << ((d) + 9)) |     \
     (1 << ((e) + 13)))

extern void (*D_8008AFD0[])(Struct15158D2C *);
extern s8 *D_8008B02C[];
extern Struct15158D2C_Rule D_800A6200[];

void func_15158D2C(Struct15158D2C *arg0) {
    s32 oldBits;
    s8 action;
    u8 old2C;
    u8 old2D;
    u8 old2E;
    u8 old2F;
    u8 old30;
    s32 newBits;
    s32 i;

    old2C = arg0->unk2C;
    old2D = arg0->unk2D;
    old2E = arg0->unk2E;
    old2F = arg0->unk2F;
    old30 = arg0->unk30;

    arg0->unk2C = func_15159084((Struct15159084 *)arg0->unk18, arg0->unk1D);
    if (arg0->unk2C == 0) {
        arg0->unk2D = func_15159120((Struct15159120 *)arg0->unk18, arg0->unk1D);
    } else {
        arg0->unk2D = 2;
    }

    if (arg0->unk2C == 0) {
        if (arg0->unk2D == 0) {
            arg0->unk2E = 1;
        } else {
            arg0->unk2E = func_15159184((Struct15159184 *)arg0->unk18, arg0->unk1D);
        }
    } else {
        arg0->unk2E = 0;
    }

    arg0->unk2F = func_15159230(arg0->unk18, &arg0->unk20, arg0->unk2F);
    arg0->unk20 = arg0->unk18->unk14;
    arg0->unk24 = arg0->unk18->unk18;
    arg0->unk28 = arg0->unk18->unk1C;
    arg0->unk30 = func_151592B8(arg0->unk18, arg0->unk1D);

    if (arg0->unk31 & 1) {
        newBits = STATE_BITS(arg0->unk2C, arg0->unk2D, arg0->unk2E, arg0->unk2F, arg0->unk30);
        for (i = 0; i < 28; i++) {
            action = D_8008B02C[arg0->unk1D][i];
            if (action != -1) {
                oldBits = STATE_BITS(old2C, old2D, old2E, old2F, old30);
                if ((D_800A6200[i].from | oldBits) == D_800A6200[i].from) {
                    if ((D_800A6200[i].to | newBits) == D_800A6200[i].to) {
                        D_8008AFD0[action](arg0);
                    }
                }
            }
        }
    }
}

void func_1519F400(void *);

typedef struct {
    u8  pad0[0x18];
    s32 unk18;
    u8  unk1C;
} SubA_15158FA4;

typedef struct {
    s32 unk0;
    union {
        s32 w4;
        u8  b4;
    } u4;
    u8  unk8;
    u8  unk9;
} ArgB_15158FA4;

void func_15158FA4(void *arg0, s32 arg1, u8 arg2) {
    SubA_15158FA4 *a = (SubA_15158FA4 *)arg0;
    ArgB_15158FA4 *b = (ArgB_15158FA4 *)arg1;
    s32 t;

    if (arg2 == 0) {
        if ((b->unk0 == a->unk18) || (b->u4.b4 == a->unk1C)) {
            func_1516972C((struct102 *)arg0);
        }
    } else if (arg2 == 0x2D) {
        t = b->unk0;
        if (a->unk18 == t) {
            a->unk18 = b->u4.w4;
            a->unk1C = b->unk9;
        } else {
            if (a->unk18 == b->u4.w4) {
                a->unk18 = t;
                a->unk1C = b->unk8;
            }
        dummy_label_15158FA4: ;
        }
    } else if (arg2 == 0x4) {
        if ((b->unk0 == a->unk18) || (b->u4.b4 == a->unk1C)) {
            func_1519F400(arg0);
        }
    }
}

extern f32 D_800A63A0;

s32 func_15159084(Struct15159084 *arg0, u8 arg1) {
    s32 ret;
    s32 flags;

    flags = arg0->unk184 & 0x1F;
    if ((arg1 == 2) || (arg1 == 3)) {
        ret = 0;
    } else {
        if ((D_800A63A0 == arg0->unk118) && ((flags & 0xA) == 0)) {
            ret = 1;
        } else if ((arg0->unk118 < arg0->unk18) || (arg0->unk137 != 0)) {
            ret = 1;
        } else {
            ret = 0;
        }
    }
    return ret;
}

s32 func_15159120(Struct15159120 *arg0, u8 arg1) {
    s32 ret;

    if ((arg1 == 2) || (arg1 == 3)) {
        ret = 1;
    } else if (arg0->unk180 < (arg0->unk118 - 35.0f)) {
        ret = 1;
    } else {
        ret = 0;
    }
    return ret;
}

s32 func_15159184(Struct15159184 *arg0, u8 arg1) {
    s32 ret;

    if ((arg1 == 2) || (arg1 == 3)) {
        if (D_800C35EA != 1) {
            ret = 0;
        } else if ((arg0->unk118 - 75.0f) < arg0->unk18) {
            ret = 1;
        } else {
            ret = 0;
        }
    } else if ((arg0->unk118 - 75.0f) < arg0->unk18) {
        ret = 1;
    } else {
        ret = 0;
    }
    return ret;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_185560/func_15159230.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_185560/func_151592B8.s")

s32 func_15159370(struct127 *arg0, u8 *arg1) {
    s32 ret;

    ret = 0;
    if (D_800BE616 != 0) {
        *arg1 = 0;
        ret = 1;
    }
    if (arg0->unique_id == 1) {
        *arg1 = 0;
        ret = 1;
    }
    if ((arg0->unk5 == 5) || (arg0->unk5 == 2)) {
        *arg1 = 1;
        ret = 1;
    }
    switch (arg0->id) {
    case 8:
        *arg1 = 2;
        ret = 1;
        break;
    case 10:
        *arg1 = 3;
        ret = 1;
        break;
    case 0x29:
    case 0x2A:
        *arg1 = 4;
        ret = 1;
        break;
    }
    return ret;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_185560/func_1515942C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_185560/func_15159594.s")

typedef struct {
    f32 unk0;
    u8 unk4;
    u8 unk5;
    s8 unk6;
    s8 unk7;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    u8 unk18;
    u8 unk19;
    u8 unk1A;
    u8 unk1B;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
} Sub151596BC;

typedef struct {
    u8 pad0[0x38];
    f32 unk38;
    f32 unk3C;
    u8 pad40[0x4];
    f32 unk44;
    u8 pad48[0x4];
    f32 unk4C;
    f32 unk50;
    f32 unk54;
    u8 pad58[0x4];
    f32 unk5C;
    u8 pad60[0x8];
    u32 unk68;
    u8 pad6C[0x3C];
    Sub151596BC sub;
} Struct151596BC;

s32 func_151596BC(Struct151596BC *arg0, s32 arg1) {
    Sub151596BC *sub;
    f32 temp0;
    f32 temp1;
    u8 ret;
    f32 temp2;

    sub = &arg0->sub;
    ret = 1;
    arg0->sub.unk4 += arg0->sub.unk6 * D_800BE9E4;
    arg0->sub.unk5 += arg0->sub.unk7 * D_800BE9E4;
    temp0 = func_151423D8(arg0->sub.unk4 - 0x40);
    temp1 = func_151423D8(sub->unk5 - 0x40);
    arg0->unk38 = sub->unk0 + (sub->unk8 * temp0);
    arg0->unk3C = sub->unk0 + (sub->unkC * temp1);

    if (0.0f < arg0->unk5C) {
        if (sub->unk10 < arg0->unk5C) {
            arg0->unk5C = sub->unk10;
        }
        temp2 = arg0->unk5C * sub->unk14;
        sub->unk18 += sub->unk1A * D_800BE9E4;
        sub->unk19 += sub->unk1B * D_800BE9E4;
        temp0 = func_151423D8(sub->unk18 - 0x40);
        temp1 = func_151423D8(sub->unk19 - 0x40);
        arg0->unk4C = (sub->unk1C * temp0) * temp2;
        arg0->unk54 = (sub->unk20 * temp1) * temp2;
    }

    if (arg0->unk68 & 0x2000) {
        if (sub->unk24 < (arg0->unk50 + arg0->unk44)) {
            ret = 0;
        }
    }
    return ret;
}

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
} Vec15159890;

typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ s16 unk08;
    /* 0x0A */ s16 unk0A;
    /* 0x0C */ s32 unk0C;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ u8 unk14;
    /* 0x15 */ u8 unk15;
    /* 0x16 */ u8 unk16;
    /* 0x17 */ u8 unk17;
    /* 0x18 */ u8 unk18;
    /* 0x19 */ u8 unk19;
    /* 0x1A */ u8 unk1A;
    /* 0x1B */ u8 unk1B;
    /* 0x1C */ u8 unk1C;
    /* 0x1D */ u8 unk1D;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ Vec15159890 unk30;
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ f32 unk40;
    /* 0x44 */ f32 unk44;
    /* 0x48 */ Vec15159890 unk48;
    /* 0x54 */ f32 unk54;
    /* 0x58 */ s32 unk58;
    /* 0x5C */ u8 pad5C[0x4];
    /* 0x60 */ u8 unk60;
    /* 0x61 */ u8 unk61;
    /* 0x62 */ u8 unk62;
    /* 0x63 */ s8 unk63;
    /* 0x64 */ u8 pad64[0x8];
} Params15159890;

extern f32 D_800A63A8;
extern f32 D_800A63AC;
extern f32 D_800A63B0;
extern f32 D_800A63B4;
extern f32 D_800A63B8;
extern f32 D_800A63BC;
extern f32 D_800A63C0;

void *func_151303BC(Params15159890 *, s32, s32);

void *func_15159890(f32 *arg0, f32 *arg1, s32 arg2, s32 arg3) {
    f32 temp_f2;
    Params15159890 params;
    void *temp_v0;
    Sub151596BC extra;

    params.unk1D = 0x2F;
    params.unk08 = 0xC01;
    params.unk00 = 0x200005;
    params.unk04 = 0;
    params.unk1A = 0;
    params.unk19 = 0;
    params.unk18 = 0;
    params.unk17 = 0;
    params.unk16 = 0;
    params.unk15 = 0;
    params.unk14 = 0;
    params.unk10 = 0;
    params.unk0C = 0;
    params.unk1C = 0xFF;
    params.unk22 = 0;
    params.unk24 = 0.0f;
    params.unk58 = 0x3207;
    params.unk60 = 5;
    params.unk61 = 5;
    params.unk62 = 4;
    params.unk63 = -1;
    params.unk30 = *(Vec15159890 *)arg0;
    params.unk3C = 0.0f;
    params.unk40 = 0.0f;
    params.unk44 = 0.0f;
    extra.unk4 = 0;
    extra.unk5 = 0;
    extra.unk18 = 0;
    extra.unk19 = 0;
    extra.unk24 = 1000.0f;
    extra.unk10 = 4.0f;
    extra.unk14 = 0.25f;
    params.unk48 = *(Vec15159890 *)arg1;

    if (func_150ADA20() & 1) {
        params.unk58 |= 0x40;
    }
    if (func_150ADA20() & 1) {
        params.unk58 |= 0x80;
    }

    params.unk0A = (func_150ADA20() % 25U) + 0x1E;
    params.unk1E = 0x1E;
    params.unk20 = 8;
    params.unk1B = (func_150ADA20() % 101U) + 0x64;
    temp_f2 = (func_150ADA68() * 20.0f) + 49.0f;
    params.unk28 = temp_f2;
    extra.unk0 = temp_f2;
    params.unk2C = temp_f2;
    extra.unk6 = (func_150ADA20() % 5U) + 4;
    extra.unk7 = (func_150ADA20() % 5U) + 4;
    extra.unk8 = ((func_150ADA68() * 0.25f) + D_800A63A8) * extra.unk0;
    extra.unkC = ((func_150ADA68() * 0.25f) + D_800A63AC) * extra.unk0;
    extra.unk1A = (func_150ADA20() % 5U) + 4;
    extra.unk1B = (func_150ADA20() % 5U) + 4;
    extra.unk1C = ((func_150ADA68() * D_800A63B0) + D_800A63B4) * extra.unk0;
    extra.unk20 = ((func_150ADA68() * D_800A63B8) + D_800A63BC) * extra.unk0;
    params.unk54 = ((func_150ADA68() * 254.0f) + 108.0f) * D_800A63C0;

    temp_v0 = func_151303BC(&params, 2, 0x28);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0xA8, &extra, 0x28);
    }
    return temp_v0;
}

void *func_15159890(f32 *, f32 *, s32, s32);

void func_15159BB0(f32 arg0, f32 arg1, f32 arg2, s32 arg3, s32 arg4, s32 arg5, u8 *arg6) {
    f32 sp24[3];
    f32 sp18[3];

    sp24[0] = arg0;
    sp24[1] = arg1;
    sp18[0] = 0.0f;
    sp18[1] = 0.0f;
    sp18[2] = 0.0f;
    sp24[2] = arg2;
    func_15159890(sp24, sp18, arg6[0xC], arg6[0x1]);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_185560/func_15159C08.s")

extern float sinf(float angle);
f32 func_151423D8(u8);
f32 func_15144B68(f32 arg0);
extern f32 D_800BE9A4;
extern s32 D_800BE9E4;
typedef struct 
{
  f32 unkA8;
  u8 unkAC;
  u8 unkAD;
  s8 unkAE;
  s8 unkAF;
  f32 unkB0;
  f32 unkB4;
  f32 unkB8;
  f32 unkBC;
  f32 unkC0;
  f32 unkC4;
  f32 unkC8;
} Sub1515A11C;
typedef struct 
{
  u8 pad0[0x38];
  f32 unk38;
  f32 unk3C;
  u8 pad40[0xC];
  f32 unk4C;
  f32 unk50;
  f32 unk54;
  u8 pad58[0x50];
  Sub1515A11C sub;
} Struct1515A11C;
extern f32 sinf(f32);
s32 func_1515A11C(Struct1515A11C *arg0, s32 arg1)
{
  Sub1515A11C *s0;
  f32 temp0;
  f32 temp1;
  s0 = &arg0->sub;
  arg0->sub.unkAC = arg0->sub.unkAC + (arg0->sub.unkAE * D_800BE9E4);
  arg0->sub.unkAD = arg0->sub.unkAD + (arg0->sub.unkAF * D_800BE9E4);
  temp0 = func_151423D8(arg0->sub.unkAC - 0x40);
  temp1 = func_151423D8(s0->unkAD - 0x40);
  arg0->unk38 = s0->unkA8 + (s0->unkB0 * temp0);
  arg0->unk3C = s0->unkA8 + (s0->unkB4 * temp1);
  if ((s0 && s0) && s0)
  {
  }
  s0->unkC4 = s0->unkC4 + (s0->unkC8 * D_800BE9A4);
  s0->unkC4 = func_15144B68(s0->unkC4);
  temp0 = sinf(s0->unkC4);
  arg0->unk4C = s0->unkB8 * temp0;
  arg0->unk50 = s0->unkBC * temp0;
  arg0->unk54 = s0->unkC0 * temp0;
  return 1;
}


#pragma GLOBAL_ASM("asm/nonmatchings/game_185560/func_1515A238.s")

typedef struct {
    f32 unk0;
    u8 unk4;
    u8 unk5;
    s8 unk6;
    s8 unk7;
    f32 unk8;
    f32 unkC;
    u8 unk10;
    u8 unk11;
    u8 unk12;
    u8 unk13;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
} Sub1515A60C;

typedef struct {
    u8 pad0[0x38];
    f32 unk38;
    f32 unk3C;
    u8 pad40[0xC];
    f32 unk4C;
    u8 pad50[0x4];
    f32 unk54;
    f32 unk58;
    f32 unk5C;
    f32 unk60;
    u8 pad64[0x44];
    Sub1515A60C sub;
} Struct1515A60C;

s32 func_1515A60C(Struct1515A60C *arg0, s32 arg1) {
    Sub1515A60C *sub;
    s32 i;

    sub = &arg0->sub;
    arg0->unk38 = (func_151423D8(arg0->sub.unk4 - 0x40) * sub->unk8) + sub->unk0;
    arg0->unk3C = (func_151423D8(sub->unk5 - 0x40) * sub->unkC) + sub->unk0;
    arg0->unk4C = func_151423D8(sub->unk10 - 0x40) * sub->unk14;
    arg0->unk54 = func_151423D8(sub->unk11 - 0x40) * sub->unk18;

    sub->unk4 += sub->unk6 * D_800BE9E4;
    sub->unk5 += sub->unk7 * D_800BE9E4;
    sub->unk10 += sub->unk12 * D_800BE9E4;
    sub->unk11 += sub->unk13 * D_800BE9E4;

    for (i = D_800BE9E4; i > 0; i--) {
        arg0->unk58 *= sub->unk1C;
        arg0->unk5C *= sub->unk1C;
        arg0->unk60 *= sub->unk1C;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_185560/func_1515A78C.s")

s32 func_1514ECE0(void *, s16, void *);

s32 func_1515A920(struct102 *arg0, s32 *arg1) {
    s32 *temp;
    s32 v;

    if (func_1514ECE0(*(void **)((u8 *)arg0 + 0x2F4), 0x13, &temp) == 0) {
        return 0;
    }
    v = *(s32 *)((u8 *)temp + 0x10);
    *arg1 = v + 0x34;
    return 1;
}

void func_1515A974(struct102 *volatile arg0, s32 arg1) {
    Struct1515A974Locals local;
    void *ret;
    s32 idx;

    idx = ((u8 *)arg0)[0x1F];
    if (idx <= 0) {
        local.tmp.unk0 = 0xF;
        local.tmp.unk4 = (s32)arg0;
        local.tmp.unk8 = D_800A636C[idx].unk0;
        local.tmp.unkC = D_800A636C[idx].unk4;
        local.tmp.unk10 = 0.0f;
        local.tmp.unk14 = 0.0f;
        local.tmp.unk18 = 0.0f;
        local.tmp.unk1C = 0.0f;
        local.tmp.unk20 = 0.0f;
        local.tmp.unk24 = 0;
        local.tmp.unk25 = -1;
        local.tmp.unk26 = 2;
        local.payload.first = D_800A636C[idx].payload.first;
        local.payload.rest = D_800A636C[idx].payload.rest;
        ret = func_151A8B20(&local.tmp, -1, 0x2C, 0xFF, 0);
        if (ret != NULL) {
            memcpy((u8 *)ret + 0x80, &local.payload, 0x2C);
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_185560/func_1515AA84.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_185560/func_1515AB88.s")
