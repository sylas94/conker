#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern s16 D_800CC2B2;
extern f32 D_800CC2B4;
s16 func_15063390(struct127 *arg0);
void func_15143134(void *, f32 *, s32);
void func_1506AC8C(struct127 *, s32, void *);

struct func_15063B64_sp28 {
    struct127 *unk0;
    f32 unk4[3];
    s32 unk10;
    volatile s32 unk14;
};

s16 func_15063390(struct127 *arg0) {
    struct127 *temp;

    temp = &D_800CC2D0[arg0->unk222];
    return func_1505A630(temp->x_position - arg0->x_position, arg0->z_position - temp->z_position, 0);
}

void func_15063404(struct127 *arg0) {
    struct127 *temp = &D_800CC2D0[arg0 - D_800CC2D0];
    temp->unk31C->unk78 = 0x9;
    func_15083568(arg0, 0x1D, 1.0f, 0);
    func_15083568(arg0, 0x1E, 1.0f, 0);
    arg0->disable_jump = 0x14;
    arg0->disable_run = 0;
    arg0->unk83 = 0;
    *(s16 *)((u8 *)temp->unk31C + 0x24) = 0x3C;
    temp->unk31C->unk11A = 2;
    func_1505E650(arg0, 0x7F, 1.0f, 0.0f, 0.0f, 0.0f, 0);
}

void func_150836CC(struct127 *arg0, s32 arg1);

void func_150634E4(struct127 *arg0) {
    D_800CC2D0[arg0 - D_800CC2D0].unk31C->unk78 = 0;
    D_800CC2D0[arg0 - D_800CC2D0].unk31C->unk11A = 0;
    func_150836CC(arg0, 0x1D);
    func_150836CC(arg0, 0x1E);
    arg0->disable_jump = 0;
    arg0->disable_run = 0;
    arg0->unk83 = 0;
}

void func_15063570(struct127 *arg0) {
    D_800CC2D0[arg0 - D_800CC2D0].unk31C->unk78 = 0x3B;
    D_800CC2D0[arg0 - D_800CC2D0].unk31C->unk11A = 2;
    func_15083568(arg0, 0x89, 1.0f, 0);
    arg0->disable_jump = 0x14;
    arg0->disable_run = 0;
    arg0->unk83 = 0;
    func_1505E650(arg0, 0x221, 1.0f, 0.0f, 0.0f, 0.0f, 0);
}

struct s15063628 {
    u8  pad0[0xB0];
    s32 unkB0;
    u8  padB4[0x130 - 0xB4];
    f32 unk130;
    f32 unk134;
    f32 unk138;
    f32 unk13C;
    f32 unk140;
    s32 unk144;
};

void func_15081690(s32, f32, f32, s32, f32, f32, f32, s32, f32, s32, s32, s32, s32, s32, s32);
void func_150636A4(struct127 *arg0);

void func_15063628(struct127 *arg0, f32 arg1) {
    struct s15063628 *p = (struct s15063628 *)arg0->unk31C;

    func_15081690(arg0, p->unk13C, p->unk140, p->unk144,
                  p->unk130, p->unk134, p->unk138, (s32)&p->unkB0,
                  arg1, 0, 0, 0, -1, 0, 0);
    func_150636A4(arg0);
}

extern struct127 D_800CC2D0[26];
void func_150636A4(struct127 *arg0);
struct tgt150636A4
{
  u8 pad0[0x195];
  u8 unk195;
  u8 unk196;
};
struct mid150636A4
{
  u8 pad0[0x31C];
  struct tgt150636A4 *unk31C;
};
struct sub150636A4
{
  u8 pad0[0xB0];
  struct mid150636A4 *unkB0;
};
void func_150636A4(struct127 *arg0)
{
  struct tgt150636A4 *new_var;
  struct mid150636A4 *temp_v0;
  temp_v0 = ((struct sub150636A4 *) arg0->unk31C)->unkB0;
  if (temp_v0 != 0)
  {
    new_var = temp_v0->unk31C;
    if (new_var != 0)
    {
      temp_v0->unk31C->unk195 = 0x1E;
      temp_v0->unk31C->unk196 = arg0 - D_800CC2D0;
    }
  }
}


#pragma GLOBAL_ASM("asm/nonmatchings/game_90840/func_150636F0.s")

s32 func_150639BC(struct127 *arg0) {
    D_800CC2B2 = arg0->unk7A - arg0->unk31C->unk12 - func_15063390(arg0);
    if (D_800CC2B2 > 0x3E80) {
        D_800CC2B2 = 0x3E80;
    }
    if (D_800CC2B2 < -0x3E80) {
        D_800CC2B2 = -0x3E80;
    }
    return D_800CC2B2;
}

s32 func_15063A38(struct127 *arg0, s32 arg1, s32 arg2) {
    if (arg1 & arg2) {
        D_800CC2B2 = ((s8 *)D_800CC284)[2] * 200;
        if (arg0->unk31C->unk84 != 0) {
            D_800CC2B2 = func_150639BC(arg0);
        }

        D_800CC2B4 = 12.0f;
        D_800CC2B2 = arg0->unk31C->unk12 + ((D_800CC2B2 * D_800CC264) / 0x7D0);

        if (D_800CC2B2 < -0x2328) {
            arg0->unk76 = arg0->unk7A = (arg0->unk7A - D_800CC2B2) - 0x2328;
            D_800CC2B2 = -0x2328;
        }

        if (D_800CC2B2 >= 0x2329) {
            arg0->unk76 = arg0->unk7A = (arg0->unk7A - D_800CC2B2) + 0x2328;
            D_800CC2B2 = 0x2328;
        }

        arg0->unk31C->unk12 = D_800CC2B2;
        return 1;
    }
    return 0;
}

void func_15063B64(struct127 *arg0) {
    struct func_15063B64_sp28 sp28;

    if ((arg0->id == 0x75) || (arg0->id == 0xB1)) {
        sp28.unk14 = 0x64;
    } else {
        sp28.unk14 = 0x2C;
    }

    if (func_1503195C(arg0, sp28.unk14, 0) != 0) {
        if (arg0->unk1D4 != 0) {
            func_15143134(0, sp28.unk4, (s32)arg0->unk1D4 + 0x100);
        } else {
            sp28.unk4[0] = arg0->x_position;
            sp28.unk4[1] = arg0->y_position;
            sp28.unk4[2] = arg0->z_position;
        }

        sp28.unk10 = ((s32)arg0 - (s32)D_800CC2D0) / (s32)sizeof(struct127) + 1;
        sp28.unk0 = arg0;
        func_1506AC8C(arg0, 0xB, &sp28);
        func_150836CC(arg0, sp28.unk14);

        if (arg0->unk31C->grenade_count != 0) {
            arg0->unk31C->grenade_count--;
        }
        arg0->unk31C->unk11A = 0;
    }
}

/* Object-level asm-differ reports score 40 here, but the difference is NOT codegen: all
 * 137 instructions, registers, branch targets, delay slots and IDO's peel-1-then-unroll-by-4
 * are identical. The only differing words are four relocation ADDENDS, where the extracted
 * .s names interior symbols of D_800CC2D0[26] (D_800CC5FC = +0x32C, D_800CC2D4 = +0x4,
 * D_800CC335 = +0x65, D_800D121C = +0x4F4C) and C naturally spells them as base+offset.
 * Both resolve to the same linked addresses, so the ROM bytes are identical -- which the
 * force-clean full-ROM sha1 gate confirms. */
struct127 *func_15063C60(struct127 *arg0, s32 arg1) {
    s32 i;

    for (i = 0; i < 25; i++) {
        if ((D_800CC2D0[i].interaction_state != 0) && (arg1 == D_800CC2D0[i].id) &&
            (((arg0 - D_800CC2D0) + 1) == D_800CC2D0[i].unk65)) {
            return &D_800CC2D0[i];
        }
    }
    return NULL;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_90840/func_15063E84.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_90840/func_15063FA0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_90840/func_150641D8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_90840/func_150642AC.s")

void func_150649A0(s32 arg0, s32 arg1) {
    struct127 *objects;
    struct197 *dst;
    struct197 *src;

    objects = D_800CC2D0;
    dst = objects[arg1].unk2D0;
    src = objects[arg0].unk2D0;

    if (dst != 0) {
        if (src != 0) {
            dst->unk8 = src->unk8;
            if (dst->unk18 <= dst->unk8) {
                dst->unk8 = dst->unk18 - 1.0f;
            }
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_90840/func_15064A14.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_90840/func_15064B94.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_90840/func_15065A5C.s")
