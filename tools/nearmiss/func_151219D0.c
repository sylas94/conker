#include <ultra64.h>
#include "functions.h"
#include "variables.h"


extern f32 D_800A3420;
extern f32 D_800A3424;
extern f32 D_800A3430;

void func_151219D0(struct108 *arg0) {
    f32 minX;
    f32 maxX;
    f32 minZ;
    f32 maxZ;
    f32 sumY;
    f32 centreZ;
    f32 dist;
    f32 dx;
    f32 dz;
    s32 i;

    minX = D_800A3420;
    maxX = D_800A3424;
    minZ = D_800A3420;
    maxZ = D_800A3424;
    sumY = 0.0f;
    for (i = 0; i < D_8008FD8C; i++) {
        if (D_800CC2D0[i].x_position < minX) {
            minX = D_800CC2D0[i].x_position;
        }
        if (maxX < D_800CC2D0[i].x_position) {
            maxX = D_800CC2D0[i].x_position;
        }
        sumY += D_800CC2D0[i].y_position;
        if (D_800CC2D0[i].z_position < minZ) {
            minZ = D_800CC2D0[i].z_position;
        }
        if (maxZ < D_800CC2D0[i].z_position) {
            maxZ = D_800CC2D0[i].z_position;
        }
    }
    sumY = (sumY / D_8008FD8C) + 150.0f;
    centreZ = (minZ + maxZ) * 0.5f;
    arg0->unk2BC = maxX;
    arg0->unk2C0 = sumY;
    arg0->unk2C4 = centreZ;

    dist = 0.0f;
    for (i = 0; i < D_8008FD8C; i++) {
        dx = (D_800CC2D0[i].x_position - maxX) * 0.5f;
        if (dx < 0.0f) {
            dx = 0.0f;
        }
        dz = D_800CC2D0[i].z_position - centreZ;
        if (dz < 0.0f) {
            dz = -dz;
        }
        if (dz < dx) {
            dz = dx;
        }
        if (dist < dz) {
            dist = dz;
        }
    }
    if (dist < 300.0f) {
        dist = 300.0f;
    }
    dist += 100.0f;
    arg0->unk2F8 = arg0->unk2BC + (dist + dist);
    arg0->unk2FC = arg0->unk2C0 + (dist * 0.5f);
    arg0->unk300 = arg0->unk2C4;
}

void func_15121C00(struct108 *arg0, f32 arg1, s32 arg2, f32 arg3, f32 arg4) {
    func_15049688(&arg0->unk37C, arg1, (f32 *)&arg0->pad8C0, arg3, arg4, arg0->unk7B4);
    arg0->unk39C = arg0->unk37C * D_800A3430;
}

void func_15121C64(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 *p = &arg0;
}
