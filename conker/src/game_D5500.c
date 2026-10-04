#include <ultra64.h>
#include "functions.h"
#include "variables.h"

// is this handwritten?? YES — confirmed hand-written asm: prologue stores swc1 f24,-0x14(sp)
// BEFORE addiu sp,-0x30, and a mid-body addiu sp,+0x10 split from the epilogue addiu sp,+0x20;
// keeps all 6 sin/cos results in callee-saved FP regs with zero spills. Not IDO-reproducible.
// Natural-C reconstruction scored 9757 (all stack layout). Kept as GLOBAL_ASM.
//
// RE-CONFIRMED (wave 2026-08-21) with corpus-level proof, so nobody re-opens this.
// The semantics ARE fully recovered: this is a Z*Y*X Euler->4x4 matrix builder,
//   f32 c[3],s[3]; for each of arg1,arg2,arg3: r = arg * (PI/180);
//   c = func_150AD780(r) /*cos*/, s = func_150AD78C(r) /*sin*/;
//   m[0][*] = { cy*cz,  cy*sz, -sy, 0 }
//   m[1][*] = { sx*sy*cz - cx*sz,  sx*sy*sz + cx*cz,  sx*cy, 0 }
//   m[2][*] = { cx*sy*cz + sx*sz,  cx*sy*sz - sx*cz,  cx*cy, 0 }
//   m[3][*] = { 0, 0, 0, 1.0f }
// and D_8009F6C0 (0.017453292f) is this function's OWN anonymous float literal --
// it is referenced by exactly ONE .s in the whole tree (this one) and lives in a
// rodata blob, i.e. the literal-pool fingerprint, not a shared global.
// That reconstruction still scores 119 at -O2/-O2 -g3 (79 of 84 rows differ, 88 vs
// 84 instructions); -O1 and -g are far worse (642, n=140). Writing the constant as an
// inline literal instead of the global does not move the score at all (119 either way).
//
// Four IDO-mechanism markers, each measured against the 464 matched objects in expected/:
//  1. First instruction is `swc1 $f24,-0x14($sp)` -- a store 20 bytes BELOW $sp before any
//     allocation. The TU is exactly this function (0xD5500..0xD5650 == 84 words + pad), so
//     the instruction cannot belong to a preceding function.
//  2. The frame teardown is SPLIT: `addiu $sp,$sp,0x10` mid-body, `addiu $sp,$sp,0x20`
//     before `jr`. IDO always emits one restore, in or adjacent to the delay slot.
//     Corpus scan: exactly 7 functions tree-wide have >1 positive `addiu sp,sp,N`, and
//     every one of them is a raw GLOBAL_ASM blob in this same 0x150A cluster
//     (game_D3040 x3, game_D52A0, game_D5650, game_DAFA0, and this). ZERO compiled C.
//  3. Corpus scan for any store to a NEGATIVE $sp offset: exactly 3 tree-wide, all
//     GLOBAL_ASM blobs in this cluster (game_D4450/func_150A70C0,
//     game_D4E10/func_150A7A48, and this). ZERO compiled C.
//  4. `sw $a0,0x8($sp)` spills the matrix pointer into the reserved 16-byte outgoing-arg
//     area. IDO reserves 0x0..0xF for outgoing args and never spills there; for a pointer
//     live across 6 calls it uses $s0 (our build does exactly that: `sw $s0`/`or $s0`).
//     Golden uses no $s-register at all, and holds the deg2rad constant in callee-saved
//     $f30 across four `jal`s -- IDO reloads it after every call (measured).
// Conclusion: hand-written. BAILED, do not re-attempt without a new mechanism.
#pragma GLOBAL_ASM("asm/nonmatchings/game_D5500/func_150A8050.s")
