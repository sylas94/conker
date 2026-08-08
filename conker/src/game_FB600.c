#include <ultra64.h>
#include "functions.h"
#include "variables.h"


extern void *func_1515FF74(void *, s32, u8, s32);
extern f32 D_800A07FC;
struct Sub150CE150
{
  s8 unk0;
  s8 unk1;
  s8 unk2;
  s8 pad3;
  s16 unk4;
  s8 unk6;
  s8 pad7;
};
struct Buf150CE150
{
  void *unk0;
  u8 unk4;
  s8 pad5;
  s8 pad6;
  s8 pad7;
  f32 unk8;
  f32 unkC;
  s32 unk10;
  s8 unk14;
  char pad15[0x8F0 - 0x15];
};
void *func_150CE150(void *arg0, s16 arg1, u8 arg2, s32 arg3)
{
  struct Sub150CE150 sp910;
  struct Buf150CE150 sp20;
  void *temp_v0;
  if (arg0 == 0)
  {
    return 0;
    return temp_v0;
  }
  sp20.unk8 = D_800A07FC;
  sp910.unk0 = 1;
  sp910.unk1 = 1;
  sp910.unk2 = 0;
  sp910.unk4 = arg1;
  sp910.unk6 = 2;
  sp20.unk10 = 0x2710;
  sp20.unk14 = 0;
  sp20.unkC = D_800A07FC;
  sp20.unk0 = arg0;
  sp20.unk4 = *((u8 *) (((s32) arg0) + 0x3B));
  temp_v0 = func_1515FF74(&sp910, 0x8F0, arg2, arg3);
  if (temp_v0 != 0)
  {
    temp_v0 = memcpy((void *) (((s32) temp_v0) + 0x18), &sp20, 0x8F0);
  }
}


#pragma GLOBAL_ASM("asm/nonmatchings/game_FB600/func_150CE200.s")

typedef struct {
    /* 0x000 */ void *unk0;
    /* 0x004 */ u8 unk4;
    /* 0x008 */ f32 unk8;
    /* 0x00C */ f32 unkC;
    /* 0x010 */ s32 step;
    /* 0x014 */ u8 flags;
    /* 0x018 */ s32 x0;
    /* 0x01C */ s32 y0;
    /* 0x020 */ s32 x1;
    /* 0x024 */ s32 y1;
    /* 0x028 */ f32 unk28;
    /* 0x02C */ f32 unk2C;
    /* 0x030 */ s16 xmap[640];
    /* 0x530 */ s16 ymap[480];
} Zoom150CE450;

void func_150CE450(void *arg0, u16 *fb) {
    Zoom150CE450 *p = (Zoom150CE450 *)((u8 *)arg0 + 0x18);
    s16 *xm;
    s16 *ym;
    u32 acc;
    u32 i;
    s32 lo;
    s32 src;
    s32 y;
    s32 x;

    if ((p->flags & 1) == 0) {
        return;
    }

    xm = p->xmap;
    ym = p->ymap;

    acc = 0;
    lo = p->x0;
    src = lo;
    for (i = lo; i <= p->x1; i++) {
        xm[i] = src;
        acc += p->step;
        if (acc >= 0x10000) {
            src = i;
            acc -= 0x10000;
        }
    }

    acc = 0;
    lo = p->y0;
    src = lo;
    for (i = lo; i <= p->y1; i++) {
        ym[i] = src;
        acc += p->step;
        if (acc >= 0x10000) {
            src = i;
            acc -= 0x10000;
        }
    }

    for (y = p->y1; y >= p->y0; y--) {
        if ((y != p->y1) && (ym[y + 1] == ym[y])) {
            memcpy((u8 *)fb + (((y * D_800BE620) + p->x0) * 2),
                   (u8 *)fb + ((((y + 1) * D_800BE620) + p->x0) * 2),
                   ((p->x1 - p->x0) * 2) + 2);
        } else {
            for (x = p->x1; x >= p->x0; x--) {
                fb[(y * D_800BE620) + x] = fb[(ym[y] * D_800BE620) + xm[x]];
            }
        }
    }
}

typedef struct {
    s32 unk0;
    u8 unk4;
} SubA_150CE694;

typedef struct {
    s32 unk0;
    union {
        s32 w4;
        u8 b4;
    } u4;
    u8 unk8;
    u8 unk9;
} ArgB_150CE694;

void func_150CE694(struct260 *arg0, s32 arg1, u8 arg2) {
    SubA_150CE694 *temp_v0 = (SubA_150CE694 *)((u8 *)arg0 + 0x18);
    ArgB_150CE694 *b = (ArgB_150CE694 *)arg1;
    s32 b0;

    if (arg2 == 0x2D) {
        if (temp_v0->unk0 == b->unk0) {
            temp_v0->unk0 = b->u4.w4;
            temp_v0->unk4 = b->unk9;
        } else {
            if (temp_v0->unk0 == b->u4.w4) {
                temp_v0->unk0 = b->unk0;
                temp_v0->unk4 = b->unk8;
            }
trailing_150CE694:
            ;
        }
    } else if (arg2 == 0) {
        b0 = b->unk0;
        if ((b0 == temp_v0->unk0) || (b->u4.b4 == temp_v0->unk4)) {
            func_1516972C((struct102 *)arg0);
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_FB600/func_150CE740.s")
