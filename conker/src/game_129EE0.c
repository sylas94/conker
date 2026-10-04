#include <ultra64.h>
#define func_1513EDE4 func_1513EDE4_orig
#define func_150ADA20 func_150ADA20_u8_decl_in_functions_h
#define func_10010F88 func_10010F88_void_decl_in_functions_h
#include "functions.h"
#undef func_1513EDE4
#undef func_150ADA20
#undef func_10010F88
void func_10010F88(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
u32 func_150ADA20(void);
#include "variables.h"

typedef struct {
    char pad_0x00[0x124];
    f32 field_0x124;
    f32 field_0x128;
} ScaleUpdateState;

typedef struct {
    char pad_0x00[0x8];
    s16 field_0x08;
    char pad_0x0A[0xE];
    s16 field_0x18;
    char pad_0x1A[0xE];
    s16 field_0x28;
    char pad_0x2A[0xE];
    s16 field_0x38;
} ScaleUpdateNode;

extern ScaleUpdateNode *func_1513EDE4(ScaleUpdateState *arg0, s16 arg1);
extern void func_150FCBC0(u8 arg0);
extern s32 func_1000EC24();
extern void func_15164F0C(s32 arg0, u8 arg1, s32 arg2, s32 arg3, s32 arg4);
extern void func_151D8868(void *arg0, s32 arg1, s32 arg2, s32 arg3);

struct sp44_150FCA30 {
    u8 unk0;
    u8 unk1;
    s16 unk2;
    u8 unk4;
    u8 unk5;
    s8 unk6;
    u8 unk7;
};

void func_150FCA30(void) {
    s32 i;
    struct sp44_150FCA30 sp44;

    func_150FCBC0(0);
    func_150FCBC0(1);
    func_150FCBC0(2);

    func_1000FA64(0x2B8, -0x7F6, 0x618, -0xA47, 0x6D60, 0x2328, 0x1B58, (s32)func_1000EC24, (void *)0x2D, 0, 0, 0);
    func_1000FA64(0x2B7, -0x13F, -0x111, -0xD5B, 0x6D60, 0x2328, 0x1B58, (s32)func_1000EC24, 0, 0, 0, 0);
    func_1000FA64(0x2B6, 0x5EF, 0x3B3, -0xA49, 0x6D60, 0x2328, 0x1B58, (s32)func_1000EC24, (void *)0x5A, 0, 0, 0);

    for (i = 0; i < D_80082FA0 + 1; i++) {
        func_15164F0C(4, i, 0, 0xFF, 1);
    }

    sp44.unk0 = 1;
    sp44.unk2 = 0x64;
    sp44.unk5 = 0xF;
    sp44.unk4 = 8;
    sp44.unk6 = -1;
    func_151D8868(&sp44, 0, 0xFF, 0);
}

typedef struct {
    /* 0x00 */ s16 unk00;
    /* 0x02 */ s16 unk02;
    /* 0x04 */ s16 unk04;
    /* 0x06 */ s16 unk06;
    /* 0x08 */ s32 unk08;
    /* 0x0C */ s32 unk0C;
    /* 0x10 */ struct17 unk10;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ s32 unk34;
    /* 0x38 */ s32 unk38;
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ f32 unk40;
    /* 0x44 */ f32 unk44;
    /* 0x48 */ f32 unk48;
    /* 0x4C */ s16 unk4C;
    /* 0x4E */ s16 unk4E;
    /* 0x50 */ s16 unk50;
    /* 0x52 */ s16 unk52;
    /* 0x54 */ s16 unk54;
    /* 0x56 */ s16 unk56;
    /* 0x58 */ s8 unk58;
} Struct150FCBC0;

const s16 D_800A1EE0[3][2] = { { -40, 80 }, { -13, 63 }, { -50, 63 } };

void *func_151541B8(struct17 *, f32, s32, f32, f32, u8, s32);
extern void func_15143874(s32, f32, f32 *, f32 *);
extern void func_1514FCE8(Struct150FCBC0 *, u8, s32);

void func_150FCBC0(u8 arg0) {
    struct134 *obj;
    struct17 pos;
    const s16 *range;
    Struct150FCBC0 desc;
    s16 count;
    u8 angle;
    u32 r;
    f32 rnd;

    if (arg0 >= 3) {
        return;
    }
    obj = D_800D9AA0[arg0];
    if (obj == NULL) {
        return;
    }
    pos.unk0 = obj->unk0;
    pos.unk4 = (s16)obj->unk2 + (s16)obj->unk8 * 0.5f;
    pos.unk8 = obj->unk4;
    rnd = func_150ADA68();
    func_151541B8(&pos, rnd * 4.0f + 12.0f, 0x40D637C9, (f32)((func_150ADA20() % 0x38U) + 0xC8), 2.6090002f, 0xFF, 1);
    count = (func_150ADA20() & 1) + 3;
    if (count > 0) {
        range = D_800A1EE0[arg0];
        desc.unk02 = 0x50;
        desc.unk04 = -0x20;
        desc.unk06 = 0x2B;
        desc.unk08 = 1;
        desc.unk0C = 8;
        desc.unk1C = 249.0f;
        desc.unk20 = 451.0f;
        desc.unk24 = 506.0f;
        desc.unk28 = 100.0f;
        desc.unk2C = 1505.0f;
        desc.unk30 = 1511.0f;
        desc.unk34 = 3;
        desc.unk38 = 2;
        desc.unk3C = 90.0f;
        desc.unk40 = 0.813f;
        desc.unk44 = -2.0f;
        desc.unk48 = 1.085f;
        desc.unk4C = 12;
        desc.unk4E = 50;
        desc.unk50 = 100;
        desc.unk52 = 100;
        desc.unk54 = 12;
        desc.unk56 = 12;
        desc.unk58 = -1;
        do {
            r = func_150ADA20();
            angle = range[0] + (r % (range[1] + 1));
            desc.unk00 = angle - 40;
            func_15143874((s16)angle, (s16)obj->unk6, &desc.unk10.unk0, &desc.unk10.unk8);
            desc.unk10.unk0 += obj->unk0;
            desc.unk10.unk8 += obj->unk4;
            desc.unk10.unk4 = func_150ADA68() * (s16)obj->unk8 + (s16)obj->unk2;
            func_1514FCE8(&desc, 0xFF, 1);
            count--;
        } while (count > 0);
    }
}

extern void func_15165BB0(s32 *arg0, s32 *arg1, s32 arg2, s32 arg3, f32 arg4);

f32 func_150FCF1C(s32 *arg0) {
    struct134 *temp;
    f32 sp20[3];

    temp = D_800D9AA0[0];
    if (temp == NULL) {
        return 1.0f;
    }
    sp20[0] = (f32)temp->unk0;
    sp20[1] = (f32)(s16)temp->unk2;
    sp20[2] = (f32)temp->unk4;
    func_15165BB0(arg0, (s32 *)sp20, 0x44FAE000, 0x460CB400, 0.00011104942f);
}

void func_150FCFB0(s32 arg0) {
    func_15103828();
}

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
} Floor150FCFD4; /* 0x24 */

typedef struct {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 unk1;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ u8 unk10;
    /* 0x11 */ u8 unk11;
    /* 0x12 */ u8 unk12;
    /* 0x13 */ u8 unk13;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ struct17 unk1C;
    /* 0x28 */ struct17 unk28;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ s32 unk40;
    /* 0x44 */ u8 unk44;
    /* 0x45 */ u8 unk45;
    /* 0x46 */ u8 unk46;
    /* 0x47 */ u8 unk47;
    /* 0x48 */ s32 unk48;
    /* 0x4C */ u8 unk4C;
    /* 0x50 */ s32 unk50;
    /* 0x54 */ s16 unk54;
    /* 0x56 */ s16 unk56;
} Spawn150FCFD4; /* 0x58 */

typedef struct Actor150FD514 Actor150FD514;

typedef struct {
    /* 0x00 */ struct127 *unk0;
    /* 0x04 */ u8 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ s32 unk24;
    /* 0x28 */ Actor150FD514 *unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ Floor150FCFD4 unk30;
    /* 0x54 */ u16 unk54;
    /* 0x56 */ u16 unk56;
    /* 0x58 */ u8 unk58;
    /* 0x59 */ u8 unk59;
} Ext150FCFD4; /* 0x5C */

struct Actor150FD514 {
    /* 0x000 */ u8 unk0;
    /* 0x001 */ u8 unk1;
    /* 0x002 */ u8 pad2[0xA];
    /* 0x00C */ u8 unkC;
    /* 0x00D */ u8 padD[0x1F];
    /* 0x02C */ f32 unk2C;
    /* 0x030 */ f32 unk30;
    /* 0x034 */ f32 unk34;
    /* 0x038 */ f32 unk38;
    /* 0x03C */ f32 unk3C;
    /* 0x040 */ u8 pad40[0x1C];
    /* 0x05C */ u8 unk5C;
    /* 0x05D */ u8 pad5D[0xB3];
    /* 0x110 */ Ext150FCFD4 ext;
};

const s32 D_800A1EEC[10] = {
    0x00FF00FF, 0x00FF00FF, 0x000000FF, 0x00FF00FF, 0x00000000,
    0x00FF00FF, 0x00FF0000, 0x000000FF, 0x00FF00FF, 0x00FF0000,
};

extern void func_1504715C(Floor150FCFD4 *, struct127 *);
extern s32 func_15046C80(struct17 *, s32, f32, Floor150FCFD4 *);
extern void func_1505D024(struct127 *, s32, u16, s32);
extern s32 func_1516284C(Header *, s32 *, s32, s32, s32, u8, u8, s32, u8, u8, s32);

void func_150FCFD4(struct127 *arg0, u8 arg1, s32 arg2) {
    Floor150FCFD4 floor;
    struct17 pos;
    u8 hit;
    struct17 probe;
    Spawn150FCFD4 spawn;
    Ext150FCFD4 ext;
    void *ret;
    Ext150FCFD4 *dst;
    Header sfx;
    s32 ipos[3];
    Spawn150FCFD4 shadow;
    s32 flag;

    if (arg0->unk7 < 0xFF) {
        return;
    }
    pos.unk0 = arg0->x_position;
    probe.unk0 = pos.unk0;
    probe.unk4 = arg0->y_position + 100.0f;
    pos.unk8 = arg0->z_position;
    probe.unk8 = pos.unk8;
    func_1504715C(&floor, arg0);
    if (func_15046C80(&probe, 0, -10000.0f, &floor)) {
        pos.unk4 = floor.unk00;
        hit = 1;
    } else {
        pos.unk4 = arg0->y_position;
        hit = 0;
    }
    func_1505D024(arg0, 0x39, arg0->unk7A, -1);
    ext.unk0 = arg0;
    ext.unk4 = arg0->unique_id;
    ext.unk8 = 60.0f;
    ext.unkC = 50.0f;
    ext.unk10 = func_150ADA68() * 6.2831855f;
    ext.unk58 = 0;
    ext.unk14 = -2048.0f;
    ext.unk18 = -2048.0f;
    ext.unk1C = func_150ADA68() * 6.2831855f;
    ext.unk20 = func_150ADA68() * 6.2831855f;
    ext.unk24 = 0;
    ext.unk28 = 0;
    ext.unk2C = 0.0f;
    ext.unk30 = floor;
    ext.unk54 = func_1000FA64(0x69E, pos.unk0, pos.unk4, pos.unk8, 0x7D00, 0xBB8, 0x1F4, 0, 0, 0, 0, 0);
    flag = hit ? 1 : 0;
    ext.unk59 = flag;
    spawn.unk0 = 0x59;
    spawn.unk1 = 0xB;
    spawn.unk2 = 0x5B1A;
    spawn.unk4 = 300;
    spawn.unk8 = 0;
    spawn.unkC = 0;
    spawn.unk10 = 0xFF;
    spawn.unk11 = 0;
    spawn.unk12 = 0;
    spawn.unk13 = 0xFF;
    spawn.unk44 = 0xFF;
    spawn.unk14 = 0.0f;
    spawn.unk18 = 1500.0f;
    spawn.unk1C = pos;
    spawn.unk28 = *(struct17 *)&D_800A5480;
    spawn.unk34 = 1.0f;
    spawn.unk38 = 0.0f;
    spawn.unk3C = 1.0f;
    spawn.unk40 = 0x24EC0008;
    spawn.unk45 = 0xFF;
    spawn.unk46 = 0;
    spawn.unk47 = 6;
    spawn.unk48 = 0;
    spawn.unk4C = 0xFF;
    spawn.unk50 = 0;
    spawn.unk54 = 1;
    spawn.unk56 = 0xFF;
    ret = func_1513D2F0(&spawn, (s32)D_800A1EEC, 0, 0x2B, 0, 0x24, 0, 0, 0, 0x5C, arg1, arg2);
    if (ret != NULL) {
        dst = (Ext150FCFD4 *)((u8 *)ret + 0x110);
        memcpy(dst, &ext, sizeof(ext));
        sfx.unk0 = 2;
        sfx.unk1 = 2;
        sfx.unk2 = 300;
        sfx.unk4 = 6;
        ipos[0] = pos.unk0;
        ipos[1] = pos.unk4;
        ipos[2] = pos.unk8;
        dst->unk24 = func_1516284C(&sfx, ipos, 0xFF, 0, 0, 0xFF, 0, 0, 0x17, arg1, arg2);
        {
            extern s32 D_800A4AA0;

            if (hit) {
                extern f32 D_800A5480;

                shadow.unk0 = 3;
                shadow.unk1 = 0;
                shadow.unk2 = 0x3103;
                shadow.unk4 = 300;
                shadow.unk8 = 0;
                shadow.unkC = 0;
                shadow.unk10 = 0xFF;
                shadow.unk11 = 0;
                shadow.unk12 = 0;
                shadow.unk13 = 0xFF;
                shadow.unk44 = 0xFF;
                shadow.unk14 = 1.0f;
                shadow.unk18 = 1.0f;
                shadow.unk1C.unk0 = pos.unk0;
                shadow.unk1C.unk4 = pos.unk4 + 5.0f;
                shadow.unk1C.unk8 = pos.unk8;
                shadow.unk28 = *(struct17 *)&D_800A5480;
                shadow.unk34 = 1.0f;
                shadow.unk38 = 1.0f;
                shadow.unk3C = 1.0f;
                shadow.unk40 = 0x04EC0008;
                shadow.unk45 = 0xFF;
                shadow.unk46 = 0;
                shadow.unk47 = 6;
                shadow.unk48 = 0;
                shadow.unk4C = 0xFF;
                shadow.unk50 = 0;
                shadow.unk54 = 1;
                shadow.unk56 = 0xFF;
                dst->unk28 = (Actor150FD514 *)func_1513D594((s32)&shadow, (s32)&D_800A4AA0, 0, 0, 0, 0, 0, 50.0f, 50.0f, 0, (s32)&floor.unk04, 0, 0, 0, 0, arg1, arg2);
            }
        }
    }
}

extern void func_1502EA98(struct127 *, u8, u8, u8, u8, s32, u8);
extern void func_15107B78(struct127 *, s32, s32, s32, s32);
extern void func_151D5334(struct17 *, f32, f32, f32, s32, u8, s32);
extern void func_150E7FEC(f32, s32, void *, void *, s32, s32, s32, s32, s32, s32, s32, s32);
extern void func_150E83AC(struct17 *, s16, u8, s32);
extern f32 sinf(f32);

s32 func_150FD514(Actor150FD514 *arg0) {
    struct127 *owner;
    Ext150FCFD4 *ext;
    f32 z;
    f32 x;
    struct17 pos;

    ext = &arg0->ext;
    owner = ext->unk0;
    if (owner != NULL) {
        if (owner->interaction_state == 0 || owner->unique_id != ext->unk4) {
            ext->unk0 = NULL;
            owner = NULL;
        }
        /* BUG (original game): owner may have just been set to NULL above, and is dereferenced anyway */
        x = owner->x_position;
        z = owner->z_position;
    } else {
        x = arg0->unk34;
        z = arg0->unk3C;
    }
    if (owner != NULL) {
        func_1502EA98(owner, 0xFF, 0, 0, 0xFF, 0, 4);
        ext->unk2C += (0.091000006f + func_150ADA68() * 0.07f) * D_800BE9A4;
        while (ext->unk2C > 1.0f) {
            func_15107B78(owner, (s16)(func_150ADA20() & 0xFF), (s16)((func_150ADA20() % 101) - 63), arg0->unkC, arg0->unk1);
            ext->unk2C -= 1.0f;
        }
    }
    if (ext->unkC > 20.0f) {
        arg0->unk2C = (50.0f - ext->unkC) * 0.033333335f * ext->unk8;
    } else if (ext->unkC > 10.0f) {
        arg0->unk2C = ext->unk8;
    } else {
        arg0->unk2C = ext->unkC * 0.1f * ext->unk8;
        if (ext->unk58 == 0) {
            if (owner != NULL) {
                func_1505D024(owner, 0x16, owner->unk7A, -1);
                func_10010F88(0x69D, 0x7D00, 0, 0, 0, arg0->unk34, arg0->unk38, arg0->unk3C, 0x1F4, 0xBB8);
            }
            ext->unk58 = 1;
            func_151D5404((struct17 *)&arg0->unk34, 506.0f, 1013.0f, 0.0009871669f, 0xF, 0x14, arg0->unkC, arg0->unk1);
            func_151D5334((struct17 *)&arg0->unk34, 506.0f, 1013.0f, 0.0009871669f, 5, arg0->unkC, arg0->unk1);
            if (ext->unk59 & 1) {
                pos.unk0 = arg0->unk34;
                pos.unk4 = ext->unk30.unk00;
                pos.unk8 = arg0->unk3C;
                func_150E7FEC(func_150ADA68() * 78.0f + 125.0f, (u8)((func_150ADA20() % 76) + 180), &ext->unk30.unk04, &pos,
                              (func_150ADA20() % 207) + 302, 0, 1, 0, 0, 0, arg0->unkC, 0);
                func_150E83AC(&pos, (func_150ADA20() % 80) + 243, arg0->unkC, arg0->unk1);
            }
        }
    }
    arg0->unk5C = sinf(ext->unk10) * 57.0f + 198.0f;
    ext->unk10 += 0.28500003f * D_800BE9A4;
    ext->unk10 = func_15144B68(ext->unk10);
    ext->unk1C += 0.10700001f * D_800BE9A4;
    ext->unk20 += -0.086f * D_800BE9A4;
    ext->unk1C = func_15144B68(ext->unk1C);
    ext->unk20 = func_15144B68(ext->unk20);
    ext->unk14 = func_150AD78C(ext->unk1C) * 1666.0f + -4633.0f;
    ext->unk18 = func_150AD78C(ext->unk20) * 1192.0f + 1242.0f;
    if (ext->unk28 != NULL) {
        ext->unk28->unk2C = ext->unk28->unk30 = arg0->unk2C * 0.02f;
        ext->unk28->unk5C = arg0->unk5C;
        ext->unk28->unk34 = x;
        ext->unk28->unk3C = z;
    }
    arg0->unk34 = x;
    arg0->unk3C = z;
    ext->unkC -= D_800BE9A4;
    if (ext->unkC < 0.0f) {
        return 0;
    }
    return 1;
}

void func_150FDB0C(void *arg0, s32 arg1, u8 arg2)
{
  u8 *state;
  s32 *v0;
  s32 a2;
  s32 v1;
  s32 *msg;
 v0 = (s32 *) (((u8 *) arg0) + 0x110); if (arg2 == 0x2D) { v1 = *((s32 *) arg1); ; if (v1 == (*v0)) {
      state = (u8 *) v0;
      *v0 = *((s32 *) (arg1 + 4));
      *((u8 *) (state + 4)) = *((u8 *) (arg1 + 9));
    }
    else
    {
      if ((*((s32 *) (arg1 + 4))) == (*v0))
      {
        *v0 = v1;
        *((u8 *) (((u8 *) v0) + 4)) = *((u8 *) (arg1 + 8));
      }
      dummy_label_150FDB0C:
      ;

      ;
      ;
    }
  }
  else
  {
    msg = (s32 *) arg1;
    v1 = arg2 == 0;
    if (v1)
    {
      v1 = *msg;
      if (v1 != (*v0))
      {
        if ((*((u8 *) (((u8 *) v0) + 4))) != (*((u8 *) (arg1 + 4))))
        {
          return;
        }
      }
      *v0 = 0;
    }
  }
}


ScaleUpdateNode *func_150FDBA0(ScaleUpdateState *arg0, s16 arg1) {
    ScaleUpdateNode *node;

    node = func_1513EDE4(arg0, arg1);
    if (node != NULL) {
        node->field_0x08 = arg0->field_0x124;
        node->field_0x18 = arg0->field_0x128;
        node->field_0x28 = arg0->field_0x128;
        node->field_0x38 = arg0->field_0x124;
    }
    return node;
}

void func_150FDC2C(struct210 *arg0) {
    struct102 **p;

    p = (struct102 **)((u8 *)arg0 + 0x110);
    if (p[9] != 0) {
        func_1516972C(p[9]);
    }
    if (p[10] != 0) {
        func_1516972C(p[10]);
    }
    if (*(u16 *)((u8 *)p + 0x54) != 0) {
        func_100111C8(*(u16 *)((u8 *)p + 0x54));
    }
    if (*(u16 *)((u8 *)p + 0x56) != 0) {
        func_100111C8(*(u16 *)((u8 *)p + 0x56));
    }
}

extern void func_150FDC2C(struct210 *);

void func_150FDCAC(struct210 *arg0) {
    func_150FDC2C(arg0);
    func_1513CA6C(arg0);
}

void func_150FDCD8(struct210 *arg0) {
    func_150FDC2C(arg0);
    func_1513CAA0(arg0);
}
