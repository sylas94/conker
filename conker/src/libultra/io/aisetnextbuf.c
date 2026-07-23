#include <os_internal.h>
#include <rcp.h>
#include "../os/osint.h"

#pragma GLOBAL_ASM("asm/nonmatchings/libultra/io/aisetnextbuf/osAiSetNextBuffer.s")
// NON-MATCHING: hardware-register symbolization blocker (best 20 via IO_WRITE).
// The exact SDK source (below) is byte-perfect EXCEPT the two AI-register stores.
// The expected .o has splat-synthesized %hi/%lo relocs to D_A4500000/D_A4500004,
// but those addresses come from a CONSTANT in the real source (IO_WRITE), so:
//   - IO_WRITE(constant 0xA4500000): correct codegen (real regs t1/t3, folded
//     store), but NO relocation -> score 20 (asm-differ penalizes reloc absence).
//   - D_A4500000 = x (symbol, non-volatile): reloc matches + %lo folds into store,
//     but IDO uses $at (not t1/t3) + hoists the size reload -> score 225.
//   - *(vu32*)&D_A4500000 (symbol, volatile): real regs + reloc, but full address
//     materialization adds an addiu per store -> score 210.
// Real-reg + folded-store is only producible from a constant (known-zero %lo), which
// cannot carry a reloc. Needs a build mechanism to symbolize the AI reg constants.
// s32 osAiSetNextBuffer(void *bufPtr, u32 size) {
//     static u8 hdwrBugFlag = 0;
//     char *bptr = bufPtr;
//     if (hdwrBugFlag != 0) bptr = (char *)((u32)bufPtr - 0x2000);
//     if ((((s32)bufPtr + size) & 0x3fff) == 0x2000) hdwrBugFlag = 1;
//     else hdwrBugFlag = 0;
//     if (__osAiDeviceBusy()) return -1;
//     IO_WRITE(AI_DRAM_ADDR_REG, osVirtualToPhysical(bptr));
//     IO_WRITE(AI_LEN_REG, size);
//     return 0;
// }
