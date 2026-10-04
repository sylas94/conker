#include <ultra64.h>
#include "functions.h"
#include "variables.h"


extern f32 D_800A6C70;

void func_15165C80(f32 *arg0, Vtx *arg1, f32 arg2, f32 *arg3, f32 arg4, f32 arg5, u8 *arg6, u8 arg7) {
    f32 deg;
    f32 sn;
    f32 sx;
    f32 cs;
    f32 cx;
    f32 vel;
    s32 i;
    s16 y;
    s16 x;
    f32 rad;

    deg = *arg0;
    vel = *arg3;
    rad = deg * D_800A6C70;
    sn = func_150AD78C(rad);
    sx = sn * arg2;
    cs = func_150AD780(rad);
    cx = cs * arg2;
    arg7 = arg7 >> 1;
    y = (s16)sx;
    x = (s16)cx;
    for (i = 0; i < arg7; i++) {
        arg1[arg6[i]].v.ob[0] = -x;
        arg1[arg6[i]].v.ob[1] = y;
        arg1[arg6[i + arg7]].v.ob[0] = x;
        arg1[arg6[i + arg7]].v.ob[1] = y;
    }
    *arg0 += vel * (f32)D_800BE9E4;
    if (arg4 <= *arg0) {
        *arg3 = -vel;
        *arg0 = arg4;
    } else if (*arg0 <= arg5) {
        *arg3 = -vel;
        *arg0 = arg5;
    }
}
