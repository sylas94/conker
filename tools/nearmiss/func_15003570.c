/* tools/nearmiss/func_15003570.c -- the LAST pragma in game_305D0.c (closing it zeroes the TU)
 *
 * STATUS 2026-08-24: mism=20, frame=-48 EXACT, n=62/62 EXACT. Went from unattempted to this in
 * one pass. Prologue (all 7 saves), epilogue, the allocate_memory call, the whole alignment
 * if/else including both branch delay slots, and the two tail calls are ALL byte-identical.
 * Everything left is inside the loop body.
 *
 * *** WHAT IT DOES -- fully solved, read straight off golden. ***
 * It streams a table out of ROM into a RAM array, handling UNALIGNED ROM addresses:
 *
 *      buf = allocate_memory(0x10, 1, 2, 0);          // 16-byte scratch
 *      addr = (s32)D_1A37E0;                          // a ROM offset, taken as an ADDRESS
 *      dst  = (u16 *)D_800B87A0;                      // destination table
 *      src  = (u16 *)D_80091D20;                      // parallel table of per-entry strides
 *      do {
 *          if (addr & 1) { addr -= 1; adj = 1; } else { adj = 0; }   // DMA needs even alignment
 *          func_10004514(addr, buf, 0x10, 1);         // read 16 bytes of ROM
 *          *dst++ = (buf[adj] << 24) + buf[adj+3] + (buf[adj+1] << 16) + (buf[adj+2] << 8);
 *          addr += *src++ + adj;                      // adj added back: undoes the align-down
 *      } while (dst != (u16 *)&D_800BC444);
 *      func_10004074(buf);                            // free
 *
 * The align-down is why `adj` is added back into `addr` at the end: the stride in D_80091D20 is
 * relative to the ORIGINAL (possibly odd) address. Note the u32 is assembled with `+`, not `|`
 * (golden emits addu), and then stored through a u16 -- the top bytes are discarded on purpose.
 * D_800BC444 is the end-marker symbol one past the D_800B87A0 table (0x3CA4 bytes = 7762 u16).
 *
 * TYPES: variables.h declares D_80091D20 and D_800B87A0 as `s32[]`, but golden uses lhu/sh --
 * they are u16 tables. This is the known header-inaccuracy situation, so CAST AT USE rather
 * than redeclare (a redeclaration is a hard CCFAIL). allocate_memory has no prototype in
 * functions.h; use the file-local `extern void *allocate_memory(s32, s32, s32, s32);` exactly
 * as game_138520.c already does. func_10004074 is commented out in functions.h -- also local.
 *
 * *** WHAT MOVED, AND WHAT DIDN'T. ***
 * A 16-cell sweep over {declaration order} x {assignment order} x {*dst++ vs *dst then dst++} x
 * {*src++ + adj vs (*src + adj) then src++} gave a single clean result:
 *   - ASSIGNMENT order is the lever: `dst = ...; src = ...;` beats the reverse, 23 -> 20.
 *   - DECLARATION order is a NO-OP here (both orders appear in the tied top 8).
 *   - The ++ placement, in both the store and the advance, is a NO-OP (all four combinations tie).
 * So do not re-sweep those three; only assignment order matters and it is already set.
 *
 * *** THE TWO REMAINING DIFFERENCES, both inside the loop. ***
 * 1. s2/s3 ARE STILL SWAPPED. Golden binds src->$s2 and dst->$s3; we bind dst->$s2, src->$s3.
 *    Assignment order did NOT fix this (it improved the score for a different reason). What
 *    distinguishes them in golden is USE order inside the loop: golden reads src early
 *    (`lhu $t6,0x0($s2)` at instruction 38, interleaved with the byte loads) and stores dst
 *    late (instruction 48), whereas ours stores dst first and reads src after. A source that
 *    reads the stride into a temp BEFORE the store would reproduce that order -- but beware,
 *    the frame is EXACTLY right now and has NO stack-homed locals (0x30 = 16 outgoing + 7
 *    saved regs), so any added local risks the frame. That is the trade to explore next.
 * 2. THE BYTE-ASSEMBLY SCHEDULE. Golden loads offsets 0,3,1,2 and folds as ((b0<<24)+b3)
 *    +(b1<<16)+(b2<<8). We load 2,0,3,1 and fold as ((b2<<8)+(b0<<24))+b3+(b1<<16). Writing the
 *    source in golden's exact term order does NOT reproduce it -- natural order and golden order
 *    both score the same, so IDO is rescheduling regardless. Likely follows from (1).
 *
 * NEXT: fix the src/dst register binding via use order, and expect (2) to fall out with it.
 * Do not force it with dummy reads.
 */
#include <ultra64.h>

#include "functions.h"
#include "variables.h"

extern void *allocate_memory(s32, s32, s32, s32);
extern void func_10004074(void *);
extern u8 D_1A37E0[];
extern s32 D_800BC444;

void func_15003570(void) {
    u8 *buf;
    s32 addr;
    s32 adj;
    u16 *src;
    u16 *dst;

    buf = allocate_memory(0x10, 1, 2, 0);
    addr = (s32)D_1A37E0;
    dst = (u16 *)D_800B87A0;
    src = (u16 *)D_80091D20;
    do {
        if (addr & 1) {
            addr -= 1;
            adj = 1;
        } else {
            adj = 0;
        }
        func_10004514(addr, buf, 0x10, 1);
        *dst++ = (buf[adj] << 24) + buf[adj + 3] + (buf[adj + 1] << 16) + (buf[adj + 2] << 8);
        addr += *src++ + adj;
    } while (dst != (u16 *)&D_800BC444);
    func_10004074(buf);
}
