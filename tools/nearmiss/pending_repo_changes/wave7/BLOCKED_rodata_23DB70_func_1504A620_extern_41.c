extern f32 D_800990B0;
extern f32 D_800990B4;

f32 func_1504A620(f32 arg0) {
    f32 sum;
    f32 z;
    f32 zsq;
    f32 term;
    f32 old;
    s32 n;

    if (arg0 < 0) {
        return 0.0f;
    }
    if (arg0 == 0.0f) {
        return 0.0f;
    }
    sum = 0;
    while (2.0f <= arg0) {
        arg0 = arg0 * 0.5f;
        sum += D_800990B0;
    }
    while (arg0 < 1.0f) {
        arg0 = arg0 + arg0;
        sum -= D_800990B4;
    }
    z = (arg0 - 1.0f) / (arg0 + 1.0f);
    zsq = z * z;
    term = z + z;
    n = 1;
    do {
        old = sum;
        sum += term / (f32)n;
        term *= zsq;
        n += 2;
    } while (sum != old);
    return sum;
}
