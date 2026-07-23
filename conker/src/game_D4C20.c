#include <ultra64.h>

#include "functions.h"
#include "variables.h"


// handwritten memset? UNMATCHABLE from C: the loop uses signed `addi` (trap-on-overflow)
// for the counter/pointer arithmetic (opcodes 20C6FFFF / 20840001). IDO's C compiler only
// ever emits `addiu` for pointer/counter math, so no C source can reproduce these bytes.
#pragma GLOBAL_ASM("asm/nonmatchings/game_D4C20/func_150A7770.s")
