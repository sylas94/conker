#include <os_internal.h>
#include <rcp.h>
#include "../os/osint.h"

// PARKED at score 555 (default -O2 -g3). 34 of the 37 instructions are byte-exact; the whole
// residual is ONE codegen decision.
//
// THE PREVIOUS NOTE HERE WAS WRONG and is corrected: it claimed the blocker was
// "hardware-register symbolization" of the two AI stores, on the grounds that IO_WRITE with a
// constant emits no relocation while the golden has %hi/%lo relocs to D_A4500000/D_A4500004.
// That is the documented RELOCATION-NAMING FLOOR, not a defect. We emit
//     lui t1,0xa450 / sw v0,0(t1)        = 3C09A450 / AD220000
// and the ROM encodes exactly those words (asm/nonmatchings/.../osAiSetNextBuffer.s), while the
// golden's reloc resolves D_A4500000 = 0xA4500000 (undefined_syms_auto.txt:7989) to the same
// bytes. tools/relcheck.py compares our PLAIN words against the ROM and passes them. IO_WRITE
// is correct and matches; aisetfreq.c already ships IO_WRITE(AI_DACRATE_REG, ...) this way.
//
// THE REAL BLOCKER is the address of hdwrBugFlag. The ROM emits a fresh direct symbol
// reference at each of the three uses, which the assembler expands with $at as the store base:
//     lui t6,%hi(hdwrBugFlag) / lbu t6,%lo(hdwrBugFlag)(t6)
//     lui at,%hi(hdwrBugFlag) / sb  t0,%lo(hdwrBugFlag)(at)      (x2, one per if/else arm)
// IDO at -O2 instead materialises the address ONCE into v0 (`lui v0,%hi / addiu v0,v0,%lo`
// hoisted above the prologue stores) and uses `0(v0)` at all three sites -- 2 instructions
// added at the top, 3 saved at the uses, and every subsequent register rotated.
//
// Measured, so nothing here is a guess:
//   -O2 -g3  555   (this file)        -O2  1495        -O1  1929        -g  2763
//   `static u8 hdwrBugFlag = 0;` instead of the extern: IDENTICAL 555, identical hoist.
//     So storage class is not the lever -- and `static` is wrong anyway, see below.
//   -O1 DOES produce the ROM's direct-symbol shape, but pays for it everywhere else: bptr and
//     bufPtr go to the stack, and the jal delay slots come back as nops. So -O1 is not it
//     either; the ROM is -O2-quality register allocation with -O1-style addressing.
//
// A repo-wide survey of MATCHED functions (352 asm files) says when IDO picks each shape:
// it materialises &SYM into a register only when two or more references to SYM are connected
// by a dominator path containing NO call. 274 hoisted cases vs 162 direct cases, and 60% of
// the direct ones have a call between every consecutive pair (a 5x enrichment). Here the load
// and both stores sit in one call-free region -- __osAiDeviceBusy() is called AFTER all three
// -- so this IDO must hoist. There is no honest source rewrite that inserts a call the ROM
// does not have. This is the same "shipped libultra was built by a less aggressively hoisting
// compiler" pattern seen in libultra/os/initialize.c (where -O1 fixed the analogous
// loop-invariant hoist and dropped 9170 -> 506).
//
// NOTE for whoever picks this up: hdwrBugFlag must stay `extern`. It is the SDK's
// function-local `static u8 hdwrBugFlag = 0;`, but it still lives in splat-owned data
// (asm/data/290D0.data.s, 0x8002AB40 per symbol_addrs.us.txt). Defining the static here
// allocates a SECOND copy in this TU's .bss and binds every reference to that copy, so the
// linked bytes would stop matching the ROM even if the codegen did.
//
// extern u8 hdwrBugFlag;
//
// s32 osAiSetNextBuffer(void *bufPtr, u32 size) {
//     char *bptr;
//
//     bptr = bufPtr;
//     if (hdwrBugFlag != 0) {
//         bptr = (char *)((u32)bufPtr - 0x2000);
//     }
//
//     if ((((s32)bufPtr + size) & 0x3FFF) == 0x2000) {
//         hdwrBugFlag = 1;
//     } else {
//         hdwrBugFlag = 0;
//     }
//
//     if (__osAiDeviceBusy()) {
//         return -1;
//     }
//
//     IO_WRITE(AI_DRAM_ADDR_REG, osVirtualToPhysical(bptr));
//     IO_WRITE(AI_LEN_REG, size);
//
//     return 0;
// }
#pragma GLOBAL_ASM("asm/nonmatchings/libultra/io/aisetnextbuf/osAiSetNextBuffer.s")
