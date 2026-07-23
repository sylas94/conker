#include <ultra64.h>
#include "functions.h"
#include "variables.h"


// FILE-FLAGS-SUSPECT: game_21CAC0 looks like -O1 (Makefile override missing).
// At -O1 the addressing matches EXACTLY (compact `lui/lw %lo` load + separate `lui at`
// store, `lui at` scheduled early) — best 370 (register-only near-miss). At -O2 -g3
// every C form GCSE-shares the base (addiu pointer reused for load+store) — best 525.
// Reconstruction (needs `extern u32 D_80091970;` + -O1):
// PERMUTER CANDIDATE best 370 at -O1 (needs a game_21CAC0 -O1 Makefile override, NOT applied
// while this stays pragma). Structure byte-identical;
// residual = register cascade (target a0/a1/v0 for load/product/result; IDO uses temps + a
// move v0). Every explicit-local phrasing regresses to 670. Reconstruction (needs -O1 + the
// extern below): u32 func_151EF610(void){ return D_80091970 = (D_80091970*4+2)*(D_80091970*4+3)>>2; }
// extern u32 D_80091970;
#pragma GLOBAL_ASM("asm/nonmatchings/game_21CAC0/func_151EF610.s")
