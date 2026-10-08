extern f32 D_8002C214;
extern f64 D_8002C218;

s32 func_1000B060(f32 arg0, f32 arg1, s32 arg2) {
    s16 tmp;
    s16 sp1C;
    f32 sp18;

    sp18 = sqrtf(arg0 * arg0 + arg1 * arg1);
    if (D_8002C214 < sp18) {
        sp18 = arg0 / sp18;
    }
    sp1C = 128;
    tmp = func_150487E0(sp18) * D_8002C218;
    if (0.0f < arg1) {
        if (tmp < 0) {
            tmp = -128 - tmp;
        } else {
            tmp = 128 - tmp;
        }
    }
    tmp = (s8)(tmp + arg2);
    if (tmp >= 96 || tmp < -96) {
        tmp = 0;
    } else if (tmp >= 32) {
        tmp = 95 - tmp;
    } else if (tmp < -32) {
        tmp = -95 - tmp;
    } else {
        tmp = tmp + tmp;
        sp1C = 0;
    }
    return (tmp + 64) | sp1C;
}
