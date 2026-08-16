#include <ultra64.h>
#include "functions.h"
#include "variables.h"

// PARKED -- HAND-WRITTEN ASSEMBLY, not compiler output. Two independent lines of evidence.
//
// (1) BARE `cvt.w.s` IS A HAND-ASM FINGERPRINT IN THIS ROM. The shipped code converts each
//     fixed-point element with a bare, in-place `cvt.w.s $f2,$f2` (round-to-nearest). IDO
//     cannot emit that for a C float->int conversion:
//       (s32)f  at -mips2  ->  trunc.w.s  (what we get; 2271 occurrences ROM-wide)
//       (s32)f  at -mips1  ->  cfc1 / ctc1 / cvt.w.s / ctc1  rounding-mode save-set-restore
//                              (measured: a -mips1 build of this file emits 16 cvt.w.s but
//                               also 16 cfc1 + 32 ctc1 -- strictly further from the ROM)
//       (u32)f  either     ->  cfc1 / ctc1 / cvt.w.s / cfc1 / andi 0x78 unsigned fixup
//     Of the 448 `cvt.w.s` in the ROM, 431 carry that cfc1/ctc1 fixup. The 17 BARE ones occur
//     in exactly 17 functions, and every one of them is hand-written assembly: 16 live in the
//     0x150A math cluster and the 17th (func_150FB4C0) is 64-bit hand asm (`sd`, `dsll32`,
//     `.set gp=64`). Not one is compiler output. See tools/findcvt.sh, which reproduces this.
//
// (2) ROM ADDRESS. conker.us.yaml interleaves this TU with the hand-asm math cluster:
//       0xD4450 game_D4450   6 pragmas, 0 live C
//       0xD4C40 libultra/gu/guMtxF2L      <- here
//       0xD4E10 game_D4E10   4 pragmas, 0 live C
//       0xD5070 libultra/gu/guMtxIdentF   <- also parked, same reason
//       0xD5500 game_D5500   2 pragmas, 0 live C
//       0xD5650 game_D5650   7 pragmas, 0 live C
//     The gu routines that ARE compiled C sit in completely different regions and are all
//     matched already (cosf/sinf/guPerspectiveF/guRotateF at 0x750B0-0x75640, guNormalize and
//     mtxcatl at 0x21D4A0-0x21D530). So this ROM links gu from two sources, and 0xD4450-0xD5650
//     is the assembly one. memory/conker-handwritten-math-cluster.md already flagged the region.
//
// The reconstruction below is otherwise algorithmically exact -- straight-line (the SDK's
// nested loop does NOT unroll under IDO: -O2/-O3 leave the loop and score 11905), correct
// pair interleaving, correct Mtx layout (int halves at +0x00, frac halves at +0x20) and
// correct offsets. It scores 12225 at -O2, and essentially the entire residual is the
// trunc.w.s-vs-cvt.w.s substitution plus the register pressure it causes: trunc.w.s needs a
// separate destination FPR, while the ROM's cvt.w.s is in-place.
//
// void guMtxF2L(float mf[4][4], Mtx *m) {
//     s32 e1, e2;
//     u16 *ai = (u16 *)&m->m[0][0];
//     u16 *af = (u16 *)&m->m[2][0];
//
//     e1 = FTOFIX32(mf[0][0]);  e2 = FTOFIX32(mf[0][1]);
//     af[0] = e1;  ai[0] = (u32)e1 >> 16;  af[1] = e2;  ai[1] = (u32)e2 >> 16;
//     ... (eight such pairs, mf[0][0] through mf[3][3]) ...
// }
#pragma GLOBAL_ASM("asm/nonmatchings/libultra/gu/guMtxF2L/guMtxF2L.s")
