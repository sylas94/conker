f32 func_1504A620(f32 arg0) {
    f32 sum;
    f32 term;
    f32 zsq;
    f32 old;
    s32 n;

    if (arg0 < 0) {
        return 0.0f;
    }
    if (arg0 == 0) {
        return 0.0f;
    }
    sum = 0;
    while (2.0f <= arg0) {
        arg0 = arg0 * 0.5f;
        sum += 0.6931471825f;
    }
    while (arg0 < 1.0f) {
        arg0 = arg0 + arg0;
        sum -= 0.6931471825f;
    }
    arg0 = (arg0 - 1.0f) / (arg0 + 1.0f);
    term = arg0 + arg0;
    zsq = arg0 * arg0;
    n = 1;
    do {
        old = sum;
        sum += term / (f32)n;
        term *= zsq;
        n += 2;
    } while (sum != old);
    return sum;
}
