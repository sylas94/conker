#include <PR/ultratypes.h>

// NOTE: <ultra64.h> is deliberately not included here. It pulls in <PR/gu.h>,
// which contains "#pragma intrinsic(sqrtf)"; that makes IDO expand sqrtf inline
// as sqrt.s instead of emitting the "jal sqrtf" the original code uses.
extern f32 sqrtf(f32);

// NOTE: built with OPT_FLAGS := -O2 (no -g), see the Makefile override. The
// original libultra was compiled without debug info; at -g3 IDO schedules the
// stack-pointer restore into the "jr ra" delay slot, which the shipped code
// does not do. -g0 reproduces the original epilogue from plain source.
void guNormalize(f32 *x, f32 *y, f32 *z) {
    f32 l;

    l = 1.0f / sqrtf((*x) * (*x) + (*y) * (*y) + (*z) * (*z));
    *x *= l;
    *y *= l;
    *z *= l;
}
