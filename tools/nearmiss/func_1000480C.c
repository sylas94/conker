/* NEAR-MISS PARK -- init_4470 / func_1000480C  (468 B)   fastscore mism=139
 *
 * 30 of the 139 is a phantom length penalty (golden .s carries 2 trailing pad
 * `nop`s: 117 words vs 115 real; we emit 114, so we are 1 instruction short --
 * the epilogue wastes a nop because only ONE saved register is restored).
 *
 * THE WHOLE RESIDUAL IS ONE MISSING REGISTER PROMOTION.  Instruction-for-
 * instruction the streams are isomorphic (verified side by side end to end);
 * golden puts `size`->$s0 AND `devAddr`->$s1, we get `size`->$s0 and
 * `devAddr`->$a3, and that one difference renames ~109 of 114 rows.
 *
 * ESTABLISHED:
 *  - D_8003A573 MUST be volatile (file-local shadow via the #define trick below):
 *    without it IDO hoists the load and the busy-wait becomes an infinite loop
 *    with the wrong shape.  Worth 189 -> 160.
 *  - Reusing the `size` PARAMETER in place (`size = (size+1) & ~1; ... size -= 2;`)
 *    plus a `u32 count` assigned BEFORE the if is what promotes size to $s0
 *    (160 -> 139).  Dropping `count`, or moving `count = size - 2` inside both
 *    branches, loses the promotion (153).
 *  - A SEPARATE `len` local instead of reusing `size` swaps which variable is
 *    promoted: devAddr->$s0, len->$t0, frame becomes the correct 0x40, but
 *    scores worse (151).  So exactly ONE promotion happens whatever we do.
 *  - Tried and INERT / worse: extra `rem = size & 2` local (139), `u8 *dst`
 *    local (144), len+rem (158), len+dst (178).
 *  - `((u16 *)&tmp)[1]` / `[0]` for the halfword picks, `tmp >> 16` for the high
 *    half and a plain `tmp` for the low half (which reloads from the stack because
 *    the intervening `sh` through a pointer aliases the address-taken local) all
 *    reproduce golden exactly.
 *  - 0xA0000000 is NOT a symbol: `lui $a3,0xA000` + `lw 0($t)` is how splat renders
 *    the inline constant, and IDO rematerialises it per block just like golden.
 *
 * NEXT: find the second promotion.  Golden uses EVERY local register
 * (v0,v1,a0-a3,t0-t9) plus s0,s1 -- i.e. its register demand is strictly higher
 * than ours, so the lead is "what extra simultaneously-live value does golden
 * have", not "which spelling promotes devAddr".
 */
#include <ultra64.h>

#include "functions.h"
#define D_8003A573 D_8003A573_hdr_nonvolatile
#include "variables.h"
#undef D_8003A573
extern volatile u8 D_8003A573;


void func_10004470(void) {
    int i;
    osCreatePiManager(150, &D_800388B0, &D_800380E0, 0xC8);

    for (i = 0; i < 3; i++)
    {
        osCreateMesgQueue(&gMessageQueue[i], &gMessages[i], 1);
    }

    osCreateMesgQueue(&gMessageQueue0, &gMessage0, 300);
    D_8003A570 = 0;
    D_8003A571 = 0;
}

s32 func_10004514(s32 devAddr, void *dramAddr, u32 size, s32 arg3) {
    OSMesgQueue *msgQueue;
    OSIoMesg tmpIoMsg;
    OSIoMesg *ioMsg;
    s32 sp3c;

    sp3c = __osRunningThread->id - 3;
    if ((size < 0xC8U) && (sp3c == 0)) {
        func_1000480C(devAddr, dramAddr, size);
        return;
    }
    if ((sp3c >= 4) || ( sp3c < 0)) {
        sp3c = 0;
    }
    if (arg3 == 0) {
        if (D_8003A571 != 300) { // messages waiting?
            ioMsg = &D_80038950[D_8003A570];
            msgQueue = &gMessageQueue0;
            if (D_8003A570 == 299) { // number of message queues used?
                D_8003A570 = 0;
            } else {
                D_8003A570 += 1U;
            }
            D_8003A571 += 1U;
        } else {
            return;
        }
    } else {
        ioMsg = &tmpIoMsg;
        msgQueue = &gMessageQueue[sp3c];
    }
    osInvalDCache(dramAddr, size);
    osPiStartDma(ioMsg, 0, 0, devAddr, dramAddr, size, msgQueue);

    if (arg3 != 0) {
        osRecvMesg(msgQueue, 0, OS_MESG_BLOCK);
    }
}

void func_10004674(void) {
    int i;
    for (i = 0; i < D_8003A571; i++)
    {
        osRecvMesg(&gMessageQueue0, 0, OS_MESG_BLOCK);
    }

    D_8003A571 = 0;
}

void func_100046E4(s32 devAddr, void *dramAddr, u32 size) {
    s32 ioMsg[4];
    OSMesg recvMsg;
    OSMesgQueue *msgQueue;
    s32 threadId;
    u32 sent;
    u32 transferSize;

    sent = 0;
    threadId = __osRunningThread->id - 3;
    if ((threadId >= 4) || (threadId < 0)) {
        threadId = 0;
    }

    osInvalDCache(dramAddr, size);
    if (size != 0) {
        msgQueue = &gMessageQueue[threadId];
        do {
            transferSize = ((size - sent) < 0x14000U) ? (size - sent) : 0x14000;
            osPiStartDma((OSIoMesg *)((u8 *)ioMsg - 8), 0, 0, devAddr, dramAddr, transferSize, msgQueue);
            osRecvMesg(msgQueue, (OSMesg *)((u8 *)&recvMsg - 8), OS_MESG_BLOCK);
            sent += transferSize;
            devAddr += transferSize;
            dramAddr = (void *)((u8 *)dramAddr + transferSize);
        } while (sent < size);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/init_4470/func_1000480C.s")
// void func_1000480C(s32 devAddr, void *dramAddr, u32 size) {
//     s32 sp38;


void func_1000480C(s32 devAddr, void *dramAddr, u32 size) {
    s32 tmp;
    u32 i;
    u32 count;

    D_8003A572 = 1;
    size = (size + 1) & ~1;
    while (D_8003A573 != 0) {
    }
    while ((IO_READ(PI_STATUS_REG) & (PI_STATUS_DMA_BUSY | PI_STATUS_IO_BUSY)) != 0) {
    }
    devAddr |= D_80000308;
    count = size - 2;
    if ((devAddr & 2) != 0) {
        tmp = *(vs32 *)((devAddr - 2) | 0xA0000000);
        size -= 2;
        *(u16 *)dramAddr = ((u16 *)&tmp)[1];
        count = size - 2;
        for (i = 0; i < count; i += 4) {
            tmp = *(vs32 *)((devAddr + i + 2) | 0xA0000000);
            *(s16 *)((u8 *)dramAddr + i + 2) = tmp >> 16;
            *(s16 *)((u8 *)dramAddr + i + 4) = tmp;
        }
        if ((size & 2) != 0) {
            tmp = *(vs32 *)((devAddr + i + 2) | 0xA0000000);
            *(u16 *)((u8 *)dramAddr + i + 2) = ((u16 *)&tmp)[0];
        }
    } else {
        for (i = 0; i < count; i += 4) {
            *(s32 *)((u8 *)dramAddr + i) = *(vs32 *)((devAddr + i) | 0xA0000000);
        }
        if ((size & 2) != 0) {
            tmp = *(vs32 *)((devAddr + i) | 0xA0000000);
            *(u16 *)((u8 *)dramAddr + i) = ((u16 *)&tmp)[0];
        }
    }
    D_8003A572 = 0;
    if (D_8003A575 != 0) {
        osStartThread((OSThread *)&D_80035910);
    }
}
