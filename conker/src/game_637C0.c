#include <ultra64.h>
#include "functions.h"
#include "variables.h"

void func_150440A0(f32 arg0[4][4], f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9);

void func_15036310(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    f32 (*mtx)[4];
    f32 sp68[3];
    f32 sp5C[3];
    f32 sp50[3];
    f32 sp44[3];

    struct127 *obj;
    f32 temp;

    obj = &D_800CC2D0[arg1];
    if (obj->unk1D4 != NULL) {
        mtx = (f32 (*)[4])((u8 *)obj->unk1D4 + (arg2 << 6));
        sp5C[0] = mtx[3][0];
        sp5C[1] = mtx[3][1];
        sp5C[2] = mtx[3][2];
        sp50[0] = D_800DBFF0->unk2F8 - sp5C[0];
        sp50[1] = D_800DBFF0->unk2FC - sp5C[1];
        sp50[2] = D_800DBFF0->unk300 - sp5C[2];
        if (arg3 != 0) {
            temp = sp50[0];
            sp50[0] = sp50[2];
            sp50[2] = -temp;
        }
        sp68[0] = 0.0f;
        sp68[1] = 1.0f;
        sp68[2] = 0.0f;
        temp = sp50[1];
        sp44[0] = (temp * sp68[2]) - (sp50[2] * sp68[1]);
        sp44[1] = (sp50[2] * sp68[0]) - (sp50[0] * sp68[2]);
        sp44[2] = (sp50[0] * sp68[1]) - (sp68[0] * temp);
        sp68[0] = (temp * sp44[2]) - (sp50[2] * sp44[1]);
        sp68[1] = (sp50[2] * sp44[0]) - (sp50[0] * sp44[2]);
        sp68[2] = (sp50[0] * sp44[1]) - (sp44[0] * temp);

        func_150440A0(mtx, sp5C[0], sp5C[1], sp5C[2],
                      sp5C[0] - sp50[0], sp5C[1] - temp, sp5C[2] - sp50[2],
                      sp68[0], sp68[1], sp68[2]);
        if (obj->xz_scale != 1.0f) {
            mtx[0][0] *= obj->xz_scale;
            mtx[1][0] *= obj->xz_scale;
            mtx[2][0] *= obj->xz_scale;
            mtx[0][2] *= obj->xz_scale;
            mtx[1][2] *= obj->xz_scale;
            mtx[2][2] *= obj->xz_scale;
        }
        if (obj->y_scale != 1.0f) {
            mtx[0][1] *= obj->y_scale;
            mtx[1][1] *= obj->y_scale;
            mtx[2][1] *= obj->y_scale;
        }
    }
}
