#include <ultra64.h>
#include "functions.h"
#include "variables.h"

// func_150AD780: HAND-WRITTEN. Only 3 instrs and NO `jr $ra`: it adds D_8009F710 (pi/2)
// to $f12 and FALLS THROUGH into func_150AD78C (i.e. cos(x) = sin(x + pi/2)). A C tail-call
// would emit a `j`/`jal` (a 4th instruction), never a fall-through. Not IDO-reproducible.
#pragma GLOBAL_ASM("asm/nonmatchings/game_DAC30/func_150AD780.s")

// func_150AD78C: HAND-WRITTEN custom sinf. Two instructions no C idiom can produce with the
// -O2/-g3/-mips2 flags here:
//   (1) `mfc1 $t0,$f12` — a register bitcast of the float arg's bits. Every C idiom
//       (*(s32*)&x, or a union) spills x to the stack (swc1+lw) and the union even adds a frame.
//   (2) `cvt.w.s` (round-to-nearest) for n=round(x/pi); C's `(s32)f` emits `trunc.w.s` here.
// The reconstruction below is algorithmically exact and structurally very close (poly/branches/
// range-reduction all line up); it stalls only on those two hand-asm-only instructions, so the
// function cannot reach score 0 from C. Coeffs live in asm/data/2441D0.rodata.s.
//
// extern f32 D_8009F714,D_8009F718,D_8009F71C,D_8009F720,D_8009F724,D_8009F728,D_8009F72C;
// extern f32 D_8009F730,D_8009F734,D_8009F738,D_8009F73C;
// f32 func_150AD78C(f32 x) {
//     s32 t = (*(s32*)&x >> 22) & 0x1FF;
//     f32 xsq;
//     if (t < 0xFF) {
//         if (t < 0xE6) return x;
//         xsq = x * x;
//         return (D_8009F720 + (D_8009F71C + (D_8009F718 + D_8009F714 * xsq) * xsq) * xsq)
//                * (xsq * x) + x;
//     } else {
//         s32 n; f32 fn, r;
//         if (t >= 0x136) return 0.0f;
//         n  = /*round*/(s32)(D_8009F724 * x);   /* target rounds via cvt.w.s */
//         fn = (f32)n;
//         x  = x - D_8009F728 * fn;
//         x  = x - D_8009F72C * fn;
//         xsq = x * x;
//         r = (D_8009F73C + (D_8009F738 + (D_8009F734 + D_8009F730 * xsq) * xsq) * xsq)
//             * xsq * x + x;
//         if (n & 1) r = -r;
//         return r;
//     }
// }
#pragma GLOBAL_ASM("asm/nonmatchings/game_DAC30/func_150AD78C.s")
