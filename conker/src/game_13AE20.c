#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern void *func_15167A68(s32, s32, s32, s32, s32, s32);

void *func_1510D970(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 size[2];
    union { s32 w; f64 d; } flag;
    s32 i;

    size[0] = 0x128;
    flag.w = arg3 & 1;
    if (flag.w != 0) {
        size[0] = 0x13A;
    }

    arg3 = (s32)func_15167A68(0x4B, 0, size[0], 1, 0xFF, 1);
    if (arg3 != 0) {
        for (i = 0; i < 2; i++) {
            *(s16 *)((u8 *)arg3 + (i * 0x40) + 0x96) = 0;
            *(s16 *)((u8 *)arg3 + (i * 0x40) + 0x98) = 0x800;
            *(s16 *)((u8 *)arg3 + (i * 0x40) + 0x9A) = 0;
            *(s16 *)((u8 *)arg3 + (i * 0x40) + 0xA6) = 0;
            *(s16 *)((u8 *)arg3 + (i * 0x40) + 0xA8) = 0;
            *(s16 *)((u8 *)arg3 + (i * 0x40) + 0xAA) = 0;
            *(s16 *)((u8 *)arg3 + (i * 0x40) + 0xB6) = 0;
            *(s16 *)((u8 *)arg3 + (i * 0x40) + 0xB8) = 0;
            *(s16 *)((u8 *)arg3 + (i * 0x40) + 0xBA) = 0x800;
            *(s16 *)((u8 *)arg3 + (i * 0x40) + 0xC6) = 0;
            *(s16 *)((u8 *)arg3 + (i * 0x40) + 0xC8) = 0x800;
            *(s16 *)((u8 *)arg3 + (i * 0x40) + 0xCA) = 0x800;
        }

        *((u8 *)arg3 + 0x120) = arg0;
        *(s32 *)((u8 *)arg3 + 0x110) = arg1;
        *((u8 *)arg3 + 0x121) = arg2;
        *((u8 *)arg3 + 0x124) = arg4;

        if (flag.w != 0) {
            for (i = 0; i < 9; i++) {
                *(s16 *)((u8 *)arg3 + 0x128 + (i * 2)) = 0x7FFF;
            }
        }
    }

    return (void *)arg3;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_13AE20/func_1510DA84.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_13AE20/func_1510E120.s")

typedef struct {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
    /* 0x04 */ s16 z;
} Point3s; /* size = 0x6 */

s32 func_1510E388(Point3s **pts, Point3s *verts, f32 *outA, f32 *outB) {
    f32 ax;
    f32 ay;
    f32 az;
    f32 bx;
    f32 by;
    f32 bz;
    f32 tmp;
    f32 d0;
    f32 d1;
    f32 t;
    s32 i;
    s32 i0;
    s32 i1;
    s32 i2;
    s32 sel;

    i = 0;
    if ((pts == NULL) && (verts == NULL)) {
        *outB = 0.0f;
        *outA = 0.0f;
        return 0;
    }

    do {
        sel = 1;
        if (i >= 3) {
            i0 = i - 3;
        } else {
            i0 = i;
        }
        if (i0 != 2) {
            i1 = i0 + 1;
        } else {
            i1 = 0;
        }
        if (i1 != 2) {
            i2 = i1 + 1;
        } else {
            i2 = 0;
        }

        if (verts != NULL) {
            ax = verts[i1].x - verts[i0].x;
            ay = verts[i1].y - verts[i0].y;
            az = verts[i1].z - verts[i0].z;
            bx = verts[i2].x - verts[i0].x;
            by = verts[i2].y - verts[i0].y;
            bz = verts[i2].z - verts[i0].z;
        } else {
            ax = pts[i1]->x - pts[i0]->x;
            ay = pts[i1]->y - pts[i0]->y;
            az = pts[i1]->z - pts[i0]->z;
            bx = pts[i2]->x - pts[i0]->x;
            by = pts[i2]->y - pts[i0]->y;
            bz = pts[i2]->z - pts[i0]->z;
        }

        if (i >= 3) {
            tmp = ax;
            ax = bx;
            bx = tmp;
            tmp = ay;
            ay = by;
            by = tmp;
            tmp = az;
            az = bz;
            bz = tmp;
        }
        d0 = bx * az;
        d1 = ax * bz;
        if (d0 == d1) {
            sel = 0;
        }
        if (bx == 0.0f) {
            sel = 0;
        }
        i++;
        if (i == 6) {
            sel = 2;
        }
    } while (sel == 0);

    if (sel == 2) {
        *outA = 0.0f;
        *outB = 0.0f;
        return 0;
    }

    t = ((bx * ay) - (ax * by)) / (d0 - d1);
    *outB = t;
    *outA = (by - (t * bz)) / bx;
    return 1;
}

extern Mtx D_80089470;

Gfx *func_1510E634(Gfx *pkt, s32 arg1, s32 arg2) {
    gSPMatrix(pkt++, &D_80089470, G_MTX_LOAD);
    return pkt;
}
