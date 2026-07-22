#include <ultra64.h>

#include "functions.h"
#include "variables.h"


// Local copies of libultra controller definitions (src/libultra/io/controller.h
// is not on the include path for this file, and shared headers may not be edited).
#define CHNL_ERR(format) ((format.rxsize & CHNL_ERR_MASK) >> 4)

typedef struct {
    /* 0x00 */ u32 ramarray[15];
    /* 0x3C */ u32 pifstatus;
} OSPifRam;

typedef struct {
    /* 0x0 */ u8 dummy;
    /* 0x1 */ u8 txsize;
    /* 0x2 */ u8 rxsize;
    /* 0x3 */ u8 cmd;
    /* 0x4 */ u16 button;
    /* 0x6 */ s8 stick_x;
    /* 0x7 */ s8 stick_y;
} __OSContReadFormat;

extern OSPifRam __osContPifRam;
extern u8 __osContLastCmd;
extern u8 __osMaxControllers;

#pragma GLOBAL_ASM("asm/nonmatchings/debugger_256F80/func_16001700.s")
// NON-MATCHING: score 140, but the LOGIC is byte-exact - every instruction matches in
// opcode/immediate/offset (an osContInit-style routine: skip if __osContLastCmd==1 else
// __osPackRequestData + SI DMA + a osGetCount spin-wait calling the identity func_160016F4;
// then a 0xFF do-while fill of [__osContPifRam, __osContLastCmd), D_80042A4C(=pifstatus)=0, a
// second SI DMA whose return is the function's result, __osContLastCmd=1, and a second spin).
// KEY FIX that took it 1407->140: giving the fill-loop limit its own local `end =
// (u32*)&__osContLastCmd` stops IDO from promoting &__osContLastCmd to a saved reg (s2) across
// the calls (which had added an 8-byte frame + reload cascade); the do-while (not for) drops the
// loop guard. Remaining 140 is TWO pure IDO-scheduler nuances, insensitive to any source reorder
// tried: (1) the fill-setup interleaves the two address luis as lui-p,lui-end,addiu-end,addiu-p
// which neither `p;end` nor `end;p` source order reproduces exactly; (2) the second osGetCount's
// delay slot gets `s0=0` in the target but IDO fills it with the `__osContLastCmd=1` store in
// mine (hoisting s0=0) - because the store sits between the func_160019A8 call and s0=0, unlike
// the first spin-loop where a call precedes s0=0 so only s0=0 is delay-slot-eligible. D_80042A4C
// declared file-locally. PERMUTER CANDIDATE (scheduling-only).
//
// extern u32 D_80042A4C;
// void func_160018BC(void);
// s32 func_160019A8(s32 direction, void *dramAddr);
// s32 func_16001700(void) {
//     s32 ret, s0, s1;
//     u32 *p, *end;
//     if (__osContLastCmd != 1) {
//         func_160018BC();
//         func_160019A8(1, &__osContPifRam);
//         s0 = 0;
//         s1 = osGetCount() + 0x30D40;
//         while (osGetCount() < s1) { s0 = func_160016F4(s0); }
//         func_160016F4(s0);
//     }
//     end = (u32 *)&__osContLastCmd;
//     p = (u32 *)&__osContPifRam;
//     do { *p++ = 0xFF; } while (p < end);
//     D_80042A4C = 0;
//     ret = func_160019A8(0, &__osContPifRam);
//     __osContLastCmd = 1;
//     s0 = 0;
//     s1 = osGetCount() + 0xC3500;
//     while (osGetCount() < s1) { s0 = func_160016F4(s0); }
//     func_160016F4(s0);
//     return ret;
// }

void func_16001830(OSContPad *data) {
    u8 *ptr;
    __OSContReadFormat readformat;
    int i;

    ptr = (u8 *)__osContPifRam.ramarray;
    for (i = 0; i < __osMaxControllers; i++) {
        readformat = *(__OSContReadFormat *)ptr;
        data->errno = CHNL_ERR(readformat);
        if (data->errno == 0) {
            data->button = readformat.button;
            data->stick_x = readformat.stick_x;
            data->stick_y = readformat.stick_y;
        }
        ptr += sizeof(__OSContReadFormat);
        data++;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/debugger_256F80/func_160018BC.s")

// Best attempt for func_160018BC (__osPackReadData): score 10 of 16000. Every
// instruction, register and encoding matches; the only difference is which
// symbol the zero-loop limit relocates against - IDO derives the limit from the
// loop base, emitting %hi/%lo(__osContPifRam+0x40), while the reference .s names
// %hi/%lo(__osContLastCmd). Both are 0x80042A50, so the linked ROM bytes are
// identical. The count-based for-loop (below) gives the two independent base
// computations (a1 for ptr, a0 for the clear-loop dst) that the target has, but
// its limit folds to __osContPifRam+0x40. A pointer do-while `do { *dst++ = 0; }
// while (dst < (u32*)&__osContLastCmd);` names __osContLastCmd correctly but IDO
// CSEs ptr's and dst's identical base into one lui/addiu + moves (one instruction
// short of the target's two computations); no source form tried defeats that CSE.
// PERMUTER CANDIDATE (reloc-symbol/instruction-count near-miss).
//
// void func_160018BC(void) {
//     u8 *ptr;
//     __OSContReadFormat readformat;
//     int i;
//
//     ptr = (u8 *)__osContPifRam.ramarray;
//     for (i = 0; i < 16; i++) {
//         ((u32 *)&__osContPifRam)[i] = 0;
//     }
//     __osContPifRam.pifstatus = 1;
//     readformat.dummy = 0xFF;
//     readformat.txsize = 1;
//     readformat.rxsize = 4;
//     readformat.cmd = 1;
//     readformat.button = 0xFFFF;
//     readformat.stick_x = -1;
//     readformat.stick_y = -1;
//
//     for (i = 0; i < __osMaxControllers; i++) {
//         *(__OSContReadFormat *)ptr = readformat;
//         ptr += sizeof(__OSContReadFormat);
//     }
//     *ptr = 0xFE;
// }

// another __osSiDeviceBusy function
s32 func_16001984()
{
    register u32 stat = IO_READ(SI_STATUS_REG);
    if (stat & (SI_STATUS_DMA_BUSY | SI_STATUS_RD_BUSY))
        return 1;
    return 0;
}

// very similar to __osSiRawStartDma
s32 func_160019A8(s32 direction, void *dramAddr) {
    if ((s32)dramAddr & 3) { // what is this checking?
        return -1;
    }
    if (func_16001984()) {
        return -1;
    }

    if (direction == OS_WRITE) {
        osWritebackDCache(dramAddr, 64);
    }

    IO_WRITE(SI_DRAM_ADDR_REG, osVirtualToPhysical(dramAddr));

    if (direction == OS_READ) {
        IO_WRITE(SI_PIF_ADDR_RD64B_REG, 0x1FC007C0);
    } else {
        IO_WRITE(SI_PIF_ADDR_WR64B_REG, 0x1FC007C0);
    }
    if (direction == OS_READ) {
        osInvalDCache(dramAddr, 64);
    }

    return 0;
}

void func_16001A64(void) {
}

s32 func_16001A6C(f32 arg0) {
    s32 tmp = *(s32*) &arg0;

    if ((tmp * 2) == 0) {
        return 0;
    }
    tmp = (tmp & 0x7F800000) >> 0x17;
    if ((tmp <= 0) || (tmp >= 255)) {
        return 1;
    }
    return 0;
}
