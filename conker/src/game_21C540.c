#include <ultra64.h>
#include "functions.h"
#include "variables.h"

/* game_21C540 -- the game's private copy of osContInit / __osContGetInitData /
 * __osPackRequestData.  Built at -O1, like the rest of the libultra code in this ROM
 * (see the OPT_FLAGS override in the Makefile); at the -O2 -g3 tree default these score
 * 198/132/134, at -O1 all three are byte-perfect.
 *
 * The three functions do NOT call each other: func_151EF090's `jal`s resolve to the
 * BOOT-segment copies at 0x10025608 / 0x10025538 (checked against the raw encodings
 * 0x0C009582 / 0x0C00954E), so the external names below are deliberate.
 *
 * The two details that differ from the published SDK source -- the zero loop running to 16
 * rather than ARRLEN(ramarray)==15, and the type word being assembled as
 * `(typel << 8) | typeh` against this field order -- are taken from the already-matched
 * __osPfsRequestData2 / __osPfsGetInitData2 in src/libultra/io/pfsisplug2.c, which is the
 * same libultra code operating on a different PIF ram block.
 *
 * Local declaration order in func_151EF090 is load-bearing: IDO gives each automatic a stack
 * home in REVERSE declaration order (first declared lands highest), and golden's frame is
 * dummy 0x7C, ret 0x78, time 0x70, t 0x50, timerMesgQueue 0x38.
 */

typedef struct {
    /* 0x0 */ u8 dummy;
    /* 0x1 */ u8 txsize;
    /* 0x2 */ u8 rxsize;
    /* 0x3 */ u8 cmd;
    /* 0x4 */ u8 typeh;
    /* 0x5 */ u8 typel;
    /* 0x6 */ u8 status;
    /* 0x7 */ u8 dummy1;
} __OSContRequesFormat;

extern s32 __osContInitialized;
extern u8 __osMaxControllers;
extern u8 __osContLastCmd;
extern u32 __osContPifRam[16];
extern u32 D_80042A4C;
extern OSMesgQueue __osEepromTimerQ;
extern OSMesg D_80042A90;

void __osPackRequestData(u8 cmd);
void __osContGetInitData(u8 *pattern, OSContStatus *data);
s32 __osSiRawStartDma(s32 dir, void *dramAddr);
void __osSiCreateAccessQueue(void);

/* This ROM predates the OS_CPU_COUNTER form in include/2.0L/PR/os_convert.h: golden loads the
 * 64-bit osClockRate global at 0x8002BD10 and divides by 1000000. */
#define GAME_USEC_TO_CYCLES(n) (((u64)(n) * (u64)D_8002BD10) / 1000000)

s32 func_151EF090(OSMesgQueue *mq, u8 *bitpattern, OSContStatus *data) {
    OSMesg dummy;
    s32 ret = 0;
    u64 time;
    OSTimer t;
    OSMesgQueue timerMesgQueue;

    if (__osContInitialized) {
        return 0;
    }
    __osContInitialized = 1;

    time = osGetTime();
    if (time < GAME_USEC_TO_CYCLES(500000)) {
        osCreateMesgQueue(&timerMesgQueue, &dummy, 1);
        osSetTimer(&t, GAME_USEC_TO_CYCLES(500000) - time, 0, &timerMesgQueue, &dummy);
        osRecvMesg(&timerMesgQueue, &dummy, OS_MESG_BLOCK);
    }

    __osMaxControllers = 4;

    __osPackRequestData(0);
    ret = __osSiRawStartDma(OS_WRITE, __osContPifRam);
    osRecvMesg(mq, &dummy, OS_MESG_BLOCK);

    ret = __osSiRawStartDma(OS_READ, __osContPifRam);
    osRecvMesg(mq, &dummy, OS_MESG_BLOCK);

    __osContGetInitData(bitpattern, data);

    __osContLastCmd = 0;
    __osSiCreateAccessQueue();
    osCreateMesgQueue(&__osEepromTimerQ, &D_80042A90, 1);

    return ret;
}

void func_151EF288(u8 *pattern, OSContStatus *data) {
    u8 *ptr;
    __OSContRequesFormat requestformat;
    s32 i;
    u8 bits;

    bits = 0;
    ptr = (u8 *) __osContPifRam;
    for (i = 0; i < __osMaxControllers; i++, ptr += sizeof(__OSContRequesFormat)) {
        requestformat = *(__OSContRequesFormat *) ptr;
        data->errno = (requestformat.rxsize & 0xC0) >> 4;
        if (data->errno == 0) {
            data->type = (requestformat.typel << 8) | (requestformat.typeh);
            data->status = requestformat.status;
            bits |= 1 << i;
        }
        data++;
    }
    *pattern = bits;
}

void func_151EF358(u8 cmd) {
    u8 *ptr;
    __OSContRequesFormat requestformat;
    s32 i;

    for (i = 0; i < 16; i++) {
        __osContPifRam[i] = 0;
    }
    D_80042A4C = 1;
    ptr = (u8 *) __osContPifRam;
    requestformat.dummy = 0xFF;
    requestformat.txsize = 1;
    requestformat.rxsize = 3;
    requestformat.cmd = cmd;
    requestformat.typeh = 0xFF;
    requestformat.typel = 0xFF;
    requestformat.status = 0xFF;
    requestformat.dummy1 = 0xFF;
    for (i = 0; i < __osMaxControllers; i++) {
        *(__OSContRequesFormat *) ptr = requestformat;
        ptr += sizeof(__OSContRequesFormat);
    }
    *ptr = 0xFE;
}
