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

extern f32 sqrtf(f32);

#pragma function sqrtf

void func_15049CB8(f32 m[4][4], f32 *q) {
    f32 tr;
    f32 s;
    s32 i;
    s32 j;
    s32 k;

    tr = m[0][0] + m[1][1] + m[2][2] + 1.0f;
    if (tr > 0.01f) {
        extern f32 sqrtf(f32);

        s = sqrtf(tr);
        q[0] = s * 0.5f;
        s = 0.5f / s;
        q[1] = (m[1][2] - m[2][1]) * s;
        q[2] = (m[2][0] - m[0][2]) * s;
        q[3] = (m[0][1] - m[1][0]) * s;
    } else {
        s32 nxt[3] = {1, 2, 0};
        f32 t;

        i = 0;
        if (m[0][0] < m[1][1]) {
            i = 1;
        }
        if (m[i][i] < m[2][2]) {
            i = 2;
        }
        j = nxt[i];
        k = nxt[j];
        s = sqrtf(m[i][i] - m[j][j] - m[k][k] + 1.0f);
        q[i + 1] = s * 0.5f;
        t = 0.5f / s;
        q[0] = (m[j][k] - m[k][j]) * t;
        q[j + 1] = (m[i][j] + m[j][i]) * t;
        q[k + 1] = (m[i][k] + m[k][i]) * t;
    }
}

void func_15049EDC(f32 *a, f32 *b, f32 t, f32 *out) {
    f32 cosom;
    f32 omega;
    f32 ang0;
    f32 ang1;
    f32 sinom;
    f32 scale0;
    f32 scale1;

    cosom = (a[0] * b[0]) + (a[1] * b[1]) + (a[2] * b[2]) + (a[3] * b[3]);
    if (cosom < -0.99999f) {
        scale0 = 1.0f - t;
        out[0] = scale0 * a[0] - b[0] * t;
        out[1] = scale0 * a[1] - b[1] * t;
        out[2] = scale0 * a[2] - b[2] * t;
        out[3] = scale0 * a[3] - b[3] * t;
    } else if (cosom <= 0.99999f) {
        extern f32 func_15048360(f32);

        omega = func_15048360(cosom);
        ang0 = (1.0f - t) * omega;
        ang1 = t * omega;
        sinom = sinf(omega);
        scale0 = sinf(ang0) / sinom;
        scale1 = sinf(ang1) / sinom;
        out[0] = scale0 * a[0] + b[0] * scale1;
        out[1] = scale0 * a[1] + b[1] * scale1;
        out[2] = scale0 * a[2] + b[2] * scale1;
        out[3] = scale0 * a[3] + b[3] * scale1;
    } else {
        scale0 = 1.0f - t;
        out[0] = scale0 * a[0] + b[0] * t;
        out[1] = scale0 * a[1] + b[1] * t;
        out[2] = scale0 * a[2] + b[2] * t;
        out[3] = scale0 * a[3] + b[3] * t;
    }
}

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
