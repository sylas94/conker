#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern f32 D_80085EA0; /* 1 / (pi/2) */
extern f32 D_80085EA4; /* pi/2, high part */
extern f32 D_80085EA8; /* pi/2, low part */
extern f32 D_80085EAC;
extern f32 D_80098D70[]; /* [1]..[4]: odd-power polynomial coefficients */

/* cosf: cos(x) = sin(|x| + pi/2), so the range reduction rounds to the nearest
   HALF integer (the +0.5f / -0.5f pair around the rounding step) and the same
   odd polynomial is then evaluated on the reduced argument.
   The test uses the biased exponent field of x (bits 22..30); >= 0x136 means
   |x| is too large to reduce meaningfully. */
f32 cosf(f32 x)
{
    f32 xa;
    f32 t;
    f32 y;
    f32 ysq;
    f32 result;
    f32 *c;
    s32 n;

    n = *((s32 *) &x);
    if (((n >> 22) & 0x1FF) < 0x136) {
        if (0.0f < x) {
            xa = x;
        } else {
            xa = -x;
        }
        y = xa;
        t = (xa * D_80085EA0) + 0.5f;
        /* NOTE: this zero is spelled `0.f` while the one above is `0.0f`.
           IDO pools identical float literals within a function into a single
           value, which would keep one register tied up across the whole block
           and shift the allocation; two distinct spellings keep them separate,
           as the shipped code has them. Do not normalise the spelling. */
        if (0.f <= t) {
            n = (s32) (t + 0.5f);
        } else {
            n = (s32) (t - 0.5f);
        }
        t = ((f32) n) - 0.5f;
        y = y - (t * D_80085EA4);
        y = y - (t * D_80085EA8);
        ysq = y * y;
        c = D_80098D70;
        result = (((((c[4] * ysq) + c[3]) * ysq) + c[2]) * ysq) + c[1];
        if ((n & 1) == 0) {
            return ((y * ysq) * result) + y;
        }
        return -(((y * ysq) * result) + y);
    }
    if (x != x) {
        return D_8002C920;
    }
    return D_80085EAC;
}
