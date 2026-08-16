#include <ultra64.h>
#include "functions.h"
#include "variables.h"


// PARKED (wave 60). The semantics are certain -- this is the game's LCG-ish RNG:
//     extern u32 D_80091970;
//     s32 func_151EF610(void) {
//         return D_80091970 = (D_80091970 * 4 + 2) * (D_80091970 * 4 + 3) >> 2;
//     }
// (`multu`/`srl` fix the type as u32; the CSE'd `sll t6,x,2` is the compiler's, not the
// source's -- an explicit `u32 x = D_80091970 * 4;` scores the same 235.)
//
// BLOCKER is purely how the compiler ADDRESSES the global, and it is a FLAG contradiction,
// not a spelling one. Golden uses the un-CSE'd assembler-macro form for BOTH accesses:
//     lui a0,%hi(g); lw a0,%lo(g)(a0)   ...   lui at,%hi(g); sw v0,%lo(g)(at)
// Measured directly out of ../ido/ido5.3_recomp/cc (probe TU, objdump -d -r):
//   * -O2: IDO ALWAYS CSEs a same-symbol read+write into `lui r; addiu r,r,%lo` + `lw/sw 0(r)`.
//     Confirmed non-negotiable across 15 spellings: single-expression, split statements,
//     named locals, `register`, volatile on either side, union member aliasing, u32-vs-s32
//     symbols, and read-g/write-g2. Only the *void* + two-distinct-symbols shape (r5) emits
//     golden's `at` macro store -- adding `return` flips it back to the register form.
//   * -O1: reproduces golden's addressing EXACTLY, but allocates the -O1 temp rotation
//     (t6,t7,t8,t9,t0,t1) instead of golden's a0/t6/t7/t8/a1/v0, and adds a trailing
//     `move v0,t1` because -O1 does not target the return register.
// Golden therefore wants -O1's addressing with -O2's register allocation. Flag sweep, same
// source: -O2 = 235 (best), -O1 = 370, -O1 -g3 = 470, -O2 -g3 = 525 (current tree default),
// -O2/-g/-g1/-g2 = 770, -O3 = 235. A literal-address macro (`*(u32*)0x80091970`) would defeat
// the CSE but emits `lui/ori` with no relocation -- it does NOT reproduce the golden bytes.
// BAIL SIGNATURE: score does not move across genuinely different honest spellings.
#pragma GLOBAL_ASM("asm/nonmatchings/game_21CAC0/func_151EF610.s")
