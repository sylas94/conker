#include <ultra64.h>
#include "functions.h"
#include "variables.h"

// is this handwritten?? YES — confirmed hand-written asm: prologue stores swc1 f24,-0x14(sp)
// BEFORE addiu sp,-0x30, and a mid-body addiu sp,+0x10 split from the epilogue addiu sp,+0x20;
// keeps all 6 sin/cos results in callee-saved FP regs with zero spills. Not IDO-reproducible.
// Natural-C reconstruction scored 9757 (all stack layout). Kept as GLOBAL_ASM.
#pragma GLOBAL_ASM("asm/nonmatchings/game_D5500/func_150A8050.s")
