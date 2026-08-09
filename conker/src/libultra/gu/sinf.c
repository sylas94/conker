#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern f32 D_80085EB0; /* 1 / (pi/2) */
extern f32 D_80085EB4; /* pi/2, high part */
extern f32 D_80085EB8; /* pi/2, low part */
extern f32 D_80085EBC;
extern f32 D_80098D90[]; /* [1]..[4]: odd-power polynomial coefficients */

/* sinf: SDK-style range reduction to +/-pi/4 followed by a degree-9 odd
   polynomial. `m` is the biased exponent field of |x| (bits 22..30), used to
   pick the path: tiny (return x), small enough for the bare polynomial, in
   range for reduction, or too large / NaN. */
f32 sinf(f32 x)
{
    f32 xsq;
    f32 y;
    f32 ysq;
    f32 result;
    f32 fn;
    f32 *c;
    s32 bits;
    s32 n;
    s32 m;

    bits = *((s32 *) &x);
    m = (bits >> 22) & 0x1FF;

    if (m < 0xFF) {
        if (m >= 0xE6) {
            y = x;
            xsq = y * y;
            c = D_80098D90;
            result = (((((c[4] * xsq) + c[3]) * xsq) + c[2]) * xsq) + c[1];
            return ((y * xsq) * result) + y;
        }
        return x;
    }
    if (m < 0x136) {
        y = x;
        fn = y * D_80085EB0;
        if (0.0f <= fn) {
            n = (s32) (fn + 0.5f);
        } else {
            n = (s32) (fn - 0.5f);
        }
        fn = (f32) n;
        y = y - (fn * D_80085EB4);
        y = y - (fn * D_80085EB8);
        ysq = y * y;
        c = D_80098D90;
        result = (((((c[4] * ysq) + c[3]) * ysq) + c[2]) * ysq) + c[1];
        if ((n & 1) == 0) {
            return ((y * ysq) * result) + y;
        }
        return -(((y * ysq) * result) + y);
    }
    if (x != x) {
        return D_8002C920;
    }
    return D_80085EBC;
}
