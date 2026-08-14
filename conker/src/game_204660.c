#include <ultra64.h>
#include "functions.h"
#include "variables.h"


struct260 *func_151D71B0(s16 arg0, u8 arg1, u8 arg2, f32 arg3, void *arg4, u8 arg5, s32 arg6) {
    struct260 *temp_v0;
    struct {
        s32 unk0;
        u8 unk4;
        u8 unk5;
        u8 pad6;
        u8 pad7;
        f32 unk8;
        f32 unkC;
        f32 unk10;
        f32 unk14;
    } sp34;

    sp34.unk0 = 0;
    sp34.unk4 = arg2;
    sp34.unk5 = 0;
    sp34.unk8 = 0.0f;
    sp34.unkC = 0.0f;
    sp34.unk10 = 0.0f;
    sp34.unk14 = arg3;

    temp_v0 = func_15149130(arg0, -1, 0x42, -1, arg1, 0x36, (struct37 *)((s32)arg4 + 0x18), arg5, arg6);
    if (temp_v0 != NULL) {
        memcpy((void *)((s32)temp_v0 + 0x28), &sp34, 0x18);
    }
    return temp_v0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_204660/func_151D7264.s")

extern void (*D_8008FCA4[])(s32 *, s32, u8);

void func_151D73A8(s32 *arg0, s32 arg1, u8 arg2) {
    if (D_8008FCA4[*(u8 *)((s32)arg0 + 0x2C)] != 0) {
        D_8008FCA4[*(volatile u8 *)((s32)arg0 + 0x2C)](arg0, arg1, arg2);
    }
}

void func_151D77C8();

void func_151D7404() {
    func_151D77C8();
}

void func_151D7424(struct260 *arg0) {
    func_151D7404(arg0);
    func_1514933C(arg0);
}

void func_151D7450(struct260 *arg0) {
    func_151D7404(arg0);
    func_15149368(arg0);
}

void func_151D747C(struct struct127 *arg0) {
    struct {
        s32 unk0;
        u8 unk4;
    } sp18;

    sp18.unk0 = (s32)arg0;
    sp18.unk4 = arg0->unique_id;
    func_151494E0((s32)&sp18, 0x3D);
}

void func_151D74B0(struct struct127 *arg0, u8 arg1, s8 arg2, u8 arg3, void *arg4) {
    struct {
        s32 unk0;
        u8 unk4;
        u8 unk5;
        u8 unk6;
    } sp30;
    struct260 *temp_v0;

    sp30.unk0 = (s32)arg0;
    sp30.unk4 = arg0->unique_id;
    sp30.unk5 = arg1;
    sp30.unk6 = arg2;

    temp_v0 = func_151D71B0(0x12C, 0, 0, 12.0f, (void *)8, arg3, (s32)arg4);
    if (temp_v0 != NULL) {
        memcpy((void *)((s32)temp_v0 + 0x40), &sp30, 8);
    }
}

void func_151D7538(s32 arg0, s32 arg1, u8 arg2) {
    s32 *p = &arg0;
    s32 q;
    if (arg2 == 0x3D) {
        q = *p + 0x40;
        if ((*(s32 *)q == *(s32 *)arg1) || (*(u8 *)(q + 4) == *(u8 *)(*(s32 *)&arg1 + 4))) {
            func_1516972C((struct102 *)*p);
        }
    } else {
        q = *p + 0x40;
        func_15149514(arg1, arg2, q, q + 4, *p);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_204660/func_151D75C4.s")

s32 func_151D7724(s32 *arg0) {
    s32 *v0 = (s32 *)arg0[0x40 / 4];
    u8 *p = (u8 *)arg0 + 0x28;
    u16 type;

    if (!(v0[0x94 / 4] & 2)) {
        type = *(u16 *)((u8 *)v0 + 0x84);
        if (type != 4 && type != 0xA && type != 0xC) {
            goto done;
        }
    }
    p[5] &= ~1;
done:
    return 1;
}

s32 func_151D7770(s32 *arg0) {
    u8 *p = (u8 *)arg0 + 0x28;
    s32 *v = (s32 *)arg0[0x40 / 4];
    if (*(u16 *)((u8 *)v + 0x84) == 0) {
        p[5] &= ~1;
    }
    return 1;
}

s32 func_151D779C(s32 *arg0) {
    u8 *p = (u8 *)arg0 + 0x28;
    s32 *v = (s32 *)arg0[0x40 / 4];

    if (*(u8 *)((u8 *)v + 0xAD) != 0) {
        p[5] &= ~1;
    }
    return 1;
}

void func_151D77C8(s32 *arg0) {
    s32 **p = (s32 **)((u8 *)arg0 + 0x28);

    if (*p != 0) {
        s32 *v1 = (s32 *)(*p)[0x98 / 4];
        *(u8 *)((u8 *)*p + 0x30) = 0;
        *(u16 *)((u8 *)*p + 0x1E) &= ~2;
        *(u16 *)((u8 *)*p + 0x1E) |= 8;
        *(u16 *)((u8 *)*p + 0x1E) |= 1;
        *(u16 *)((u8 *)*p + 0x1C) = 0x14;
        *v1 = 0;
        *p = 0;
    }
}

struct blk12_D7830 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
};

extern s32 func_15147A80(void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);

void func_151D7830(s32 *arg0) {
    s32 *temp_v0;
    struct {
        s32 unk0;
        struct blk12_D7830 unk4;
        f32 unk10;
        f32 unk14;
        f32 unk18;
    } sp68;
    struct {
        struct blk12_D7830 unk0;
        s16 unkC;
        s16 unkE;
        s32 unk10;
        u8 unk14;
        u8 unk15;
        u8 pad16[2];
        s32 unk18;
    } sp4C;
    /* NOT a struct-size artefact -- deliberately LEFT IN PLACE.  Both aggregates
     * above are proven to be exactly 0x1C: the header sp4C by func_15147A80's own
     * memcpy((u8 *)temp_v0 + 0x10, arg0, 0x1C) (game_174BF0.c:169) and by its
     * member offsets, and sp68 by its members plus memcpy(..., &sp68, 0x1C).
     * Golden pins BOTH bases with `addiu a0,sp,0x4C` and `addiu a1,sp,0x68`, so
     * neither can carry leading padding, and nothing is declared below sp4C for
     * trailing padding to belong to.  The gap is compiler-TEMP space at
     * sp+[0x44,0x4C) and is dead in our object.  Measured: deleting it gives
     * frame 0x80 (breaks the match); a 4-byte `s32 pad_dummy;` gives frame 0x88
     * with .text byte-identical, so the true shortfall is 4 bytes, not 8. */
    s32 pad_dummy[2];

    sp68.unk0 = (s32)arg0;
    sp68.unk4 = *(struct blk12_D7830 *)((u8 *)arg0 + 0x30);
    sp68.unk10 = 0.0f;
    sp68.unk14 = 0.0f;
    sp68.unk18 = 0.0f;
    sp4C.unk15 = 0x19;

    sp4C.unk0 = *(struct blk12_D7830 *)((u8 *)arg0 + 0x30);
    sp4C.unkC = 0x12C;
    sp4C.unkE = 0x76;
    sp4C.unk10 = 0x12;
    sp4C.unk14 = 4;
    sp4C.unk18 = 0;

    temp_v0 = (s32 *)func_15147A80(&sp4C, 0x20, 0x1C, 0xD, 0x10, 0x10, 0, 0, 0,
                                   *((u8 *)arg0 + 0xC), *((u8 *)arg0 + 0x1));
    if (temp_v0 != NULL) {
        memcpy((void *)temp_v0[0x98 / 4], &sp68, 0x1C);
        arg0[0x28 / 4] = (s32)temp_v0;
    }
}

extern f32 D_800BE9A4;
struct func_151D792C_vec
{
  s32 unk0;
  s32 unk4;
  s32 unk8;
};
struct func_151D792C_entry
{
  struct func_151D792C_vec unk0;
  f32 unkC;
  f32 unk10;
  f32 unk14;
  s32 unk18;
};
struct func_151D792C_obj
{
  u8 pad0[0x1E];
  u16 unk1E;
  u8 pad20[5];
  u8 unk25;
  u8 pad26[6];
  s8 unk2C;
  s8 unk2D;
  s8 unk2E;
  u8 pad2F[0x25];
  f32 unk54;
  f32 unk58;
  f32 unk5C;
  u8 pad60[0x34];
  struct func_151D792C_entry *unk94;
};
void func_151D8718(f32 *arg0, f32 *arg1, f32 arg2);
s32 func_151D792C(struct func_151D792C_obj *arg0)
{
  struct func_151D792C_entry *base;
  struct func_151D792C_entry *entry;
  s32 i;
  s32 stride;
  base = arg0->unk94;
  if ((arg0->unk2C < 2) && (arg0->unk1E & 8))
  {
    return 0;
  }
  i = arg0->unk2E;
  if (i != arg0->unk2D)
  {
    do
    {
      i -= 1;
      if (i < 0)
      {
        i = arg0->unk25 - 1;
      }
      entry = &base[i];
      func_151D8718((f32 *) entry, &entry->unkC, D_800BE9A4);
    }
    while (i != arg0->unk2D);
  }
  stride = sizeof(struct func_151D792C_entry);
  stride_set:
  if (arg0->unk2C <= 0)
  {
    goto zero;
  }

  ;
  *((struct func_151D792C_vec *) (&arg0->unk54)) = ((struct func_151D792C_entry *) (((u8 *) base) + (arg0->unk2D * stride)))->unk0;
  goto done;
  zero:
  arg0->unk54 = 0.0f;

  arg0->unk58 = 0.0f;
  arg0->unk5C = 0.0f;
  done:
  return 1;

}

void func_151D8718(f32 *arg0, f32 *arg1, f32 arg2);


#pragma GLOBAL_ASM("asm/nonmatchings/game_204660/func_151D7A38.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_204660/func_151D7CD0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_204660/func_151D80C4.s")

extern f32 D_800AB2EC;
extern f32 D_800AB2F0;

void func_151D8718(f32 *arg0, f32 *arg1, f32 arg2) {
    f32 v = arg1[0];
    arg1[0] += D_800AB2EC * arg2;
    arg0[1] += v * arg2 + D_800AB2F0 * (arg2 * arg2);
}

void func_151D8764(s32 *arg0) {
    s32 *temp = (s32 *)arg0[0x98 / 4];
    s32 *temp2 = (s32 *)temp[0];
    if (temp2 != 0) {
        temp2[0x28 / 4] = 0;
    }
}

extern void func_151478F4(s32 *arg0);

void func_151D8780(s32 *arg0) {
    func_151D8764(arg0);
    func_151478F4(arg0);
}

extern void func_15147928(s32 *arg0);

void func_151D87AC(s32 *arg0) {
    func_151D8764(arg0);
    func_15147928(arg0);
}
