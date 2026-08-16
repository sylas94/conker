#include <ultra64.h>

#include "functions.h"
#include "variables.h"

extern f32 D_8009DC80; /* 0.01745329238f -- degrees to radians, asm/data/242740.rodata.s */

void func_1508EF80(struct17 *arg0, struct17 *arg1, f32 arg2, struct17 *arg3) {
    f32 dx;
    f32 dz;
    f32 ang;
    struct17 out;

    dx = arg0->unk0 - arg1->unk0;
    dz = arg0->unk8 - arg1->unk8;
    ang = arg2 * D_8009DC80;
    out.unk0 = ((cosf(ang) * dx) + (sinf(ang) * dz)) + arg1->unk0;
    out.unk8 = ((-sinf(ang) * dx) + (cosf(ang) * dz)) + arg1->unk8;
    arg3->unk0 = out.unk0;
    arg3->unk8 = out.unk8;
}
