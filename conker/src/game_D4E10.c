#include <ultra64.h>
#include "functions.h"
#include "variables.h"


// func_150A7960: PERMUTER CANDIDATE, best 2585 (likely HAND-WRITTEN). Point x 4x4-matrix transform
// writing 3 components through outX/outY/outZ (stack args at 0x10/0x14/0x18(sp)). The add-tree and
// all operand orders match, but the target does a prologue `mtc1 a1,$f0; mtc1 a2,$f2; mtc1 a3,$f4`
// keeping all three int-passed float args resident with ZERO stack homing. No C phrasing reproduces
// this: every one of 9+ variants (all groupings/operand orders, arg-local copies, split-statement)
// homes exactly one arg to its arg-home slot and uses $f12/$f14 -- identical to the GENUINELY MATCHED
// sibling of the same shape func_150442C0 (game_71770.c, a leaf taking ptr+3 floats) which also homes
// one arg. Best hand form (scored 2585):
//   *outX = (m[1][0]*y + m[0][0]*x) + (m[3][0] + m[2][0]*z);   (rows 1,2 analogous for cols 1,2)
#pragma GLOBAL_ASM("asm/nonmatchings/game_D4E10/func_150A7960.s")

// func_150A7A00: HAND-WRITTEN trampoline. Saves $ra into $t9, sets $ra = &func_150A7A14, then
// `j func_150A7960` (not jal). No C construct sets ra to another function before a jump. Unmatchable.
#pragma GLOBAL_ASM("asm/nonmatchings/game_D4E10/func_150A7A00.s")

// func_150A7A14: HAND-WRITTEN continuation of the trampoline above. Consumes $f0/$f2/$f4 set up by
// func_150A7960, reads a caller stack arg at 0x1C(sp), and returns via `jr $t9` (the ra saved by
// func_150A7A00). Not a standalone function; not C-reproducible. Unmatchable.
#pragma GLOBAL_ASM("asm/nonmatchings/game_D4E10/func_150A7A14.s")

// func_150A7A48: genuine C 4x4 matrix multiply (out = a * b, 4 rows). NOT verified to score 0 only
// because expected/build/src/game_D4E10.c.o is MISSING. The target hoists all 16 b-matrix elements
// into $f0-$f15 for the whole loop (leaf fn, 0x20 frame saving $f20-$f27 for temps) via LICM; a
// naive loop instead reloads b each iteration. Forcing the hoist needs a scored iteration
// (16 named b-locals would blow the 0x20 frame under -g3, so it must come from array-access LICM).
// void func_150A7A48(f32 *a, f32 *b, f32 *out) {
//     s32 i;
//     for (i = 0; i < 4; i++) {
//         out[0] = ((a[0]*b[0] + a[1]*b[4]) + a[2]*b[8])  + a[3]*b[12];
//         out[1] = ((a[0]*b[1] + a[1]*b[5]) + a[2]*b[9])  + a[3]*b[13];
//         out[2] = ((a[0]*b[2] + a[1]*b[6]) + a[2]*b[10]) + a[3]*b[14];
//         out[3] = ((a[0]*b[3] + a[1]*b[7]) + a[2]*b[11]) + a[3]*b[15];
//         a += 4; out += 4;
//     }
// }
// func_150A7A48: PERMUTER CANDIDATE, best 8545 (likely HAND-WRITTEN). 4x4 matrix multiply
// out = a * b, 4 rows, out[j] = a[0]*b[j] + a[1]*b[4+j] + a[2]*b[8+j] + a[3]*b[12+j].
// The target hoists ALL 16 b-elements into $f0-$f15 for the whole loop (0x20 frame saving
// $f20-$f27 for temps) via LICM. Natural C never hoists them: IDO cannot prove `out` and `b`
// don't alias, so it reloads b every iteration; `restrict` is rejected (IDO 5.3 is C89) and
// 16 named b-locals blow the 0x20 frame under -g3. Best hand form (do-while, scored 8545):
//   s32 i = 4;
//   do { out[0]=a[0]*b[0]+a[1]*b[4]+a[2]*b[8]+a[3]*b[12]; ...cols 1..3...; a+=4; out+=4; } while(--i);
#pragma GLOBAL_ASM("asm/nonmatchings/game_D4E10/func_150A7A48.s")
