void func_150495B0(f32 *arg0, f32 arg1, f32 *arg2, f32 arg3, f32 arg4, f32 arg5) {
    f32 sign;
    f32 dir;
    f32 d;
    f32 temp;

    d = arg1 - *arg0;
    if (d < 0.0f) {
        sign = -1.0f;
    } else {
        sign = 1.0f;
    }
    d *= arg3;
    *arg2 += (d - *arg2) * arg4 * arg5;
    temp = *arg2 * arg5 + *arg0;
    if (arg1 < temp) {
        dir = -1.0f;
    } else {
        dir = 1.0f;
    }
    if (dir == sign) {
        *arg0 = temp;
    } else {
        *arg0 = arg1;
        *arg2 = 0.0f;
    }
}
