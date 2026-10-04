/* near-miss 8: frame/slots/all FP exact except golden reuses p[i+1] (f16) for the final add after the *deriv store;
   ours reloads lwc1 4(v0) (store may alias). A d local fixes the reload but adds a mov.s (22) or moves slots. */
f32 func_150498A4(f32 *p, s32 i, f32 t, f32 *deriv) {
    /* Catmull-Rom segment through p[i..i+3] at parameter t, plus its derivative */
    f32 b;
    f32 c;
    f32 r;
    f32 a;

    a = -0.5f * p[i] + 1.5f * p[i + 1] + -1.5f * p[i + 2] + 0.5f * p[i + 3];
    b = p[i] + -2.5f * p[i + 1] + (p[i + 2] + p[i + 2]) + -0.5f * p[i + 3];
    c = -0.5f * p[i] + 0.5f * p[i + 2];
    *deriv = (a * 3.0f * t + (b + b)) * t + c;
    r = ((a * t + b) * t + c) * t;
    r += p[i + 1];
    return r;
}
