#include <ultra64.h>
#include "functions.h"
#include "variables.h"

void func_15047390(f32 mf[4][4], f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9);
s32 func_1505D1C4(f32, f32, f32, s32, s32, u16, s32, s32);

s32 func_150E1570(struct127 *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, s32 arg7, s32 arg8) {
    f32 mf[4][4];
    f32 dx;
    f32 dy;
    f32 dz;
    f32 dist;
    s32 hit;
    s32 result;
    s32 i;
    s32 best;
    s32 bestHit;
    s32 owner;
    struct127 *obj;

    bestHit = 0;
    result = 0;
    func_15047390(mf, arg1, arg2, arg3, arg4, arg5, arg6, 0.0f, 1.0f, 0.0f);

    dx = arg1 - arg4;
    dy = arg2 - arg5;
    dz = arg3 - arg6;
    dist = sqrtf((dx * dx) + (dy * dy) + (dz * dz));

    if (arg0 != NULL) {
        owner = arg0->unk124 - 1;
    } else {
        owner = -1;
    }

    best = -1;
    obj = D_800CC2D0;
    for (i = 0; i != 25; i++, obj = (struct127 *)((u8 *)obj + 0x32C)) {
        if ((obj->interaction_state != 0) && (i != arg7) && (obj->health != 0) && (obj->immune == 0) && (i != owner)) {
            hit = func_15049440(mf, obj->x_position, obj->y_position + (f32)obj->unkD6, obj->z_position,
                                (f32)obj->unkD2, (f32)obj->unkD4, 0.0f, dist, 10.0f, 10.0f);
            if (hit != 0) {
                if ((best == -1) || (hit < bestHit)) {
                    best = i;
                    bestHit = hit;
                }
            }
        }
    }

    if (best != -1) {
        obj = &D_800CC2D0[best];
        result = func_1505D1C4(obj->x_position, (f32)obj->unkD6 + obj->y_position, obj->z_position, arg8, D_800C3E78, 0,
                               0, 0);
        obj->unk76 = arg0->unk76;
    }
    return result;
}
