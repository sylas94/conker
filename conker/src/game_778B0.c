#include <ultra64.h>
#include "functions.h"
#include "variables.h"

f32 func_1504A2B0(f32 arg0);
f32 func_1504A620(f32 arg0);

f32 func_1504A400(f32 arg0, f32 arg1) {
    f32 base;

    if ((arg0 != 0.0f) && (arg1 == 0.0f)) {
        return 1.0f;
    }
    if (arg0 == 0.0f) {
        return 0.0f;
    }
    if (((arg0 == 0.0f) && (arg1 == 0.0f)) ||
        ((arg0 < 0.0f) && (arg1 != (f32) (s32) arg1))) {
        return 0.0f;
    }

    if (arg1 != (f32) (s32) arg1) {
        arg0 = func_1504A2B0(func_1504A620(arg0) * arg1);
    } else if (0.0f < arg1) {
        base = arg0;
        arg1--;
        while (arg1--) {
            arg0 *= base;
        }
    } else {
        base = 1.0f;
        while (arg1++) {
            base /= arg0;
        }
        arg0 = base;
    }
    return arg0;
}
