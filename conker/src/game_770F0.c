#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void func_15049C40(f32 *arg0, f32 *arg1) {
    f32 d;

    d = (arg0[0] * arg1[0]) + (arg0[1] * arg1[1]) + (arg0[2] * arg1[2]) + (arg0[3] * arg1[3]);
    if (d < 0.0f) {
        arg1[0] = -arg1[0];
        arg1[1] = -arg1[1];
        arg1[2] = -arg1[2];
        arg1[3] = -arg1[3];
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_770F0/func_15049CB8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_770F0/func_15049EDC.s")

void func_1504A140(f32 *q, f32 *m) {
    f32 s;
    f32 a, b, c;
    f32 wx, wy, wz;
    f32 xx, xy, xz;
    f32 yy, yz, zz;

    s = 2.0f / (q[0] * q[0] + q[1] * q[1] + q[2] * q[2] + q[3] * q[3]);

    a = q[1] * s;
    b = q[2] * s;
    c = q[3] * s;

    wx = q[0] * a;
    wy = q[0] * b;
    wz = q[0] * c;
    xx = q[1] * a;
    xy = q[1] * b;
    xz = q[1] * c;
    yy = q[2] * b;
    yz = q[2] * c;
    zz = q[3] * c;

    m[0] = 1.0f - (yy + zz);
    m[1] = xy + wz;
    m[2] = xz - wy;
    m[4] = xy - wz;
    m[5] = 1.0f - (xx + zz);
    m[6] = yz + wx;
    m[8] = xz + wy;
    m[9] = yz - wx;
    m[10] = 1.0f - (xx + yy);
    m[3] = 0.0f;
    m[7] = 0.0f;
    m[11] = 0.0f;
    m[15] = 1.0f;
}
