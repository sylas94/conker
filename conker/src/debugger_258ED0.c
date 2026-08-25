#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* NOT DECOMPILABLE -- this is a HAND-WRITTEN assembly routine, not compiler output.
 * The extracted .s is even labelled `/* Handwritten function *(/` by spimdisasm. It walks
 * all 32 TLB entries with `mtc0 $t0,$0` / `tlbr` / `mfc0` of CP0 registers $2 (EntryLo0),
 * $3 (EntryLo1), $10 (EntryHi) and $5 (PageMask), fanning them into four adjacent u32[32]
 * arrays at D_160038AC/D_1600392C/D_160039AC/D_16003A2C, and uses `addi` rather than the
 * `addiu` IDO emits for pointer arithmetic. It is the only function in the whole
 * nonmatchings corpus containing a CP0 instruction.
 *
 * 2026-08-21: the "IDO cannot emit this" claim is now MEASURED against
 * ../ido/ido5.3_recomp/cc, not assumed. All three escape hatches are shut:
 *   - `asm("tlbr");` compiles, but IDO 5.3 has no inline-asm construct: it emits an ordinary
 *     `jal asm` (R_MIPS_26 to an undefined symbol `asm`) plus a .rodata string argument.
 *     "It compiled" here means a link error, not a match. `__asm__(...)` is identical.
 *   - `#pragma asm` / `#pragma endasm` (the IRIX MIPSpro spelling) is not recognised by this
 *     front-end; the body is parsed as C -> "Unknown character $ ignored" + Syntax Error,
 *     at file scope and inside a function body alike. No object produced.
 * Best measurable C floor (loop scaffolding with the four mfc0 reads faked as extern loads)
 * is mism=160 n=52/40 at -O1; 238 at the tree default. No gradient exists.
 * This pragma is permanent; it is not a near-miss and should not be counted as one.
 * Full ledger: tools/nearmiss/func_16003650.c
 */
#pragma GLOBAL_ASM("asm/nonmatchings/debugger_258ED0/func_16003650.s")
