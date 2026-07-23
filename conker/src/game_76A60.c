#include <ultra64.h>
#include "functions.h"
#include "variables.h"


// PERMUTER CANDIDATE: func_150495B0 best 1260. The reconstruction below is STRUCTURALLY
// byte-identical to the target (every op + all three branch polarities bc1fl/bc1f/bc1fl match).
// Residual is pure FP register allocation: target keeps arg3 in $f14 via `mtc1 a3,$f14` and 0.0
// in $f6, but IDO puts 0.0 in $f14 and spills arg3 to its arg-home (sw a3; lwc1 $f6) — the
// local-copy trick (f32 v3=arg3) made it WORSE (1439). Also target spills `temp` to 4(sp) and
// reloads; mine keeps it in a reg. Classic float-permuter case (cf. cosf/sinf in memory notes).
// Reconstruction:
//   void func_150495B0(f32 *arg0, f32 arg1, f32 *arg2, f32 arg3, f32 arg4, f32 arg5) {
//     f32 sign, dir, d, temp, b;
//     d = arg1 - *arg0;
//     if (d < 0.0f) sign = -1.0f; else sign = 1.0f;
//     d = d * arg3;
//     b = *arg2;
//     *arg2 = b + (d - b) * arg4 * arg5;
//     temp = (*arg2 * arg5) + *arg0;
//     if (arg1 < temp) dir = -1.0f; else dir = 1.0f;
//     if (dir == sign) *arg0 = temp; else { *arg0 = arg1; *arg2 = 0.0f; }
//   }
#pragma GLOBAL_ASM("asm/nonmatchings/game_76A60/func_150495B0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_76A60/func_15049688.s")
