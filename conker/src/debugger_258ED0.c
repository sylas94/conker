#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* NOT DECOMPILABLE -- this is a HAND-WRITTEN assembly routine, not compiler output.
 * The extracted .s is even labelled `/* Handwritten function *(/` by spimdisasm. It walks
 * all 32 TLB entries with `mtc0 $t0,$0` / `tlbr` / `mfc0` of CP0 registers $2 (EntryLo0),
 * $3 (EntryLo1), $10 (EntryHi) and $5 (PageMask), and uses `addi` rather than the `addiu`
 * IDO emits for pointer arithmetic. IDO has no inline-asm facility and no intrinsic that
 * emits `tlbr` or a raw `mtc0`/`mfc0`, so no C source can produce these 40 instructions.
 * This pragma is permanent; it is not a near-miss and should not be counted as one.
 */
#pragma GLOBAL_ASM("asm/nonmatchings/debugger_258ED0/func_16003650.s")
