#include <ultra64.h>
#include "functions.h"
#include "variables.h"


f32 func_150497E0(f32 *p, s32 i, f32 t) {
    /* Catmull-Rom segment through p[i..i+3] at parameter t */
    f32 a;
    f32 c;
    f32 b;
    f32 r;

    a = -0.5f * p[i] + 1.5f * p[i + 1] + -1.5f * p[i + 2] + 0.5f * p[i + 3];
    b = p[i] + -2.5f * p[i + 1] + (p[i + 2] + p[i + 2]) + -0.5f * p[i + 3];
    c = -0.5f * p[i] + 0.5f * p[i + 2];
    r = ((a * t + b) * t + c) * t;
    r += p[i + 1];
    return r;
}


#pragma GLOBAL_ASM("asm/nonmatchings/game_76C90/func_150498A4.s")
