#include <ultra64.h>

#include "functions.h"
#include "variables.h"

// PARKED at score 506 (from 11737 at the default -O2 -g3). This one is CLOSE and the
// remaining gap is small and well characterised -- it is the best hand-off of this wave.
//
// BUILD IT WITH -O1. Add to the Makefile next to the existing libultra/os override:
//     $(BUILD_DIR)/$(SRC_DIR)/libultra/os/initialize.c.o: OPT_FLAGS := -O1
// (deliberately NOT left in the Makefile while this file is still a #pragma). -O1 is what
// collapsed the score: 9170 -> 2097. At -O2 IDO hoists both loop-invariant call arguments
// (the 0x1FC007FC PIF address and `&pifdata`) into s0/s1 and turns the back-edges into
// branch-likelies; the ROM re-materialises `lui/ori` and `addiu a1,sp,0x3c` inside each loop
// and leaves the delay slots as nops. libultra/os/getthreadpri.c already needs -O1 here, so
// the whole os group looks like it was shipped at a lower optimisation level.
//
// THREE FINDINGS THAT GOT IT TO 506, all confirmed by measurement:
//   1. `register u32 sr;` -- the ROM keeps __osGetSR()'s result in s0 (`move s0,v0` then
//      `or a0,s0,at`). At -O1 a plain local is spilled to the stack instead (4 instructions
//      instead of 2, and the extra temp rotated every later t-register by one). Adding
//      `register` fixed the frame size (-0x40), the `sw s0,0x18(sp)` save, and the rotation
//      in one go: 2097 -> 550. `register` is the established libultra idiom in this tree
//      (see libultra/io/ai.c and aisetfreq.c).
//   2. LOCAL DECLARATION ORDER decides stack offsets: IDO -O1 assigns the LAST-declared local
//      the LOWEST address. The ROM wants stat=0x30, leostat=0x34, clock=0x38, pifdata=0x3C,
//      so they must be declared pifdata, clock, leostat, stat. 550 -> 506.
//   3. `bcopy(src, dst, 0x10)` is NOT inlined by this IDO (it emits `jal bcopy`); the ROM has
//      four inline lw/sw pairs alternating $at with one other temp. A 16-byte STRUCTURE
//      ASSIGNMENT reproduces that exactly, and all four vector copies then match byte for byte.
//
// WHAT IS LEFT (506):
//   a. The whole named-local block sits 4 bytes LOW (ours stat=0x2C..pifdata=0x38, ROM
//      stat=0x30..pifdata=0x3C). The frame is the right size, so the ROM reserves 16 bytes of
//      compiler temps at 0x20-0x2F where we reserve 12 (0x20-0x2B). Introducing a named
//      `u64 t` for the clock scaling is NOT the answer -- tried, it takes a HIGH slot (0x30)
//      and pushes the u32s further down (506 -> 678). The ROM's 0x20/0x24 pair is an
//      anonymous temp, so the extra 8 bytes at 0x28 is a second anonymous 64-bit temp.
//   b. `D_8002BD10 = <64-bit>` emits TWO `lui at` (one per half) where the ROM materialises
//      the base once and does two `sw` off it. Two extra instructions, at both assignment
//      sites. The ROM also builds the register pair FIRST (`move t3,t9; li t2,0`) before
//      storing, where we interleave -- i.e. the ROM's RHS is a genuine 64-bit value in a
//      register pair, ours is short-circuited from the u32 `clock`.
//   Everything else in the diff is the benign RELOCATION-NAMING FLOOR: `%hi(D_80000000)` vs
//   our `0x8000`, `%hi(D_A4600010)` vs `0xa460`, and `%lo(D_8002BD14)` vs our
//   `%lo(D_8002BD10+0x4)` -- identical linked bytes in every case.
//
// HEADER INACCURACY worth fixing properly one day: include/variables.h:130 declares
// `extern s64 D_8002BD10;` plus a separate `extern s32 D_8002BD14;` for its low half. This is
// osClockRate and libultra types it UNSIGNED -- the ROM calls __ll_mul for the multiply but
// __ull_div for the divide, and IDO picks __ll_div vs __ull_div purely by signedness, so an
// s64 declaration cannot match. The reconstruction declares it file-locally as u64 instead.
//
// #include <os_internal.h>
// #include <R4300.h>
// #include <rcp.h>
// #include "../io/piint.h"
//
// extern u64 D_8002BD10;      // osClockRate
// extern s32 D_800428E0;      // __osFinalrom
// extern s32 D_8000030C;      // osResetType
// extern s32 D_8000031C[16];  // osAppNMIBuffer, 0x40 bytes
// extern s32 D_8002BD20;      // 64DD present
// extern s32 func_10026700(void *, u32 *);  // __osSiRawReadIo
// extern s32 func_10026750(void *, u32);    // __osSiRawWriteIo
// extern void func_100071D0(void);          // __osExceptionPreamble
// extern s32 osPiRawReadIo(u32, u32 *);
// extern void __osLeoInterrupt(void);
//
// #define PIF_ADDR_S8 (PIF_RAM_START + 0x3C)
//
// typedef struct { u32 w0, w1, w2, w3; } __OSExcVec;
//
// void __osInitialize_common(void) {
//     register u32 sr;
//     u32 pifdata;
//     u32 clock = 0;
//     u32 leostat;
//     u32 stat;
//
//     D_800428E0 = 1;
//
//     sr = __osGetSR();
//     __osSetSR(sr | SR_CU1);
//     __osSetFpcCsr(FPCSR_FS | FPCSR_EV);
//
//     while (func_10026700((void *)PIF_ADDR_S8, &pifdata)) { ; }
//     while (func_10026750((void *)PIF_ADDR_S8, pifdata | 8)) { ; }
//
//     *(__OSExcVec *)UT_VEC  = *(__OSExcVec *)func_100071D0;
//     *(__OSExcVec *)XUT_VEC = *(__OSExcVec *)func_100071D0;
//     *(__OSExcVec *)ECC_VEC = *(__OSExcVec *)func_100071D0;
//     *(__OSExcVec *)E_VEC   = *(__OSExcVec *)func_100071D0;
//
//     osWritebackDCache((void *)UT_VEC, E_VEC - UT_VEC + 0x10);
//     osInvalICache((void *)UT_VEC, E_VEC - UT_VEC + 0x10);
//     osMapTLBRdb();
//
//     osPiRawReadIo(4, &clock);
//     clock &= ~0xF;
//     if (clock != 0) {
//         D_8002BD10 = clock;
//     }
//     D_8002BD10 = D_8002BD10 * 3 / 4;
//
//     if (D_8000030C == 0) {
//         bzero(D_8000031C, 0x40);
//     }
//
//     WAIT_ON_IOBUSY(stat)
//
//     leostat = IO_READ(LEO_STATUS);
//     if ((leostat & LEO_STATUS_PRESENCE_MASK) == 0) {
//         D_8002BD20 = 1;
//         __osSetHWIntrRoutine(1, __osLeoInterrupt);
//     } else {
//         D_8002BD20 = 0;
//     }
// }
#pragma GLOBAL_ASM("asm/nonmatchings/libultra/os/initialize/__osInitialize_common.s")
