#include <ultra64.h>
#include <os_internal.h>
#include <R4300.h>
#include <rcp.h>

/* __osInitialize_common, verbatim 2.0-era SDK shape.  Builds at -O1:
 *     $(BUILD_DIR)/$(SRC_DIR)/libultra/os/initialize.c.o: OPT_FLAGS := -O1
 *
 * The SDK DEFINES osClockRate & co. in this file, and that is load-bearing: IDO emits an
 * `sd` macro (one `lui $at`, two `sw`) for a 64-bit store only when the u64 is defined in the
 * same TU -- through an extern it materialises the address once per half.  So this TU owns
 * the 0x20-byte .data block at 0x2BD10 (needs `[0x2BD10, .data, libultra/os/initialize]` +
 * `[0x2BD30, data]` in conker.us.yaml, and `D_8002BD14 = 0x8002BD14;` for the asm files that
 * still address osClockRate's low word by that alias).  Nothing here is variables.h: it
 * declares D_8002BD10 as s64, but osClockRate is u64 (the ROM divides with __ull_div). */
u64 D_8002BD10 = 62500000; /* osClockRate (OS_CLOCK_RATE) */
u32 D_8002BD18 = 0;        /* __osShutdown */
u32 D_8002BD1C = 0x003FFF01; /* __OSGlobalIntMask (OS_IM_ALL) */
s32 D_8002BD20 = 0;        /* 64DD present */

extern s32 D_800428E0;      /* __osFinalrom */
extern s32 D_8000030C;      /* osResetType */
extern s32 D_8000031C[16];  /* osAppNMIBuffer, 0x40 bytes */
extern s32 func_10026700(u32, u32 *); /* __osSiRawReadIo */
extern s32 func_10026750(u32, u32);   /* __osSiRawWriteIo */
extern void func_100071D0(void);      /* __osExceptionPreamble */
extern s32 osPiRawReadIo(u32, u32 *);
extern void __osLeoInterrupt(void);

#define LEO_STATUS (0x05000500 + 0x08)
#define LEO_STATUS_PRESENCE_MASK 0xFFFF

typedef struct {
    u32 inst1, inst2, inst3, inst4;
} __osExceptionVector;

void __osInitialize_common(void) {
    u32 pifdata;
    u32 clock = 0;
    u32 leostat;
    u32 stat;

    D_800428E0 = 1;
    __osSetSR(__osGetSR() | SR_CU1);
    __osSetFpcCsr(FPCSR_FS | FPCSR_EV);
    while (func_10026700(PIF_RAM_END - 3, &pifdata)) {
        ;
    }
    while (func_10026750(PIF_RAM_END - 3, pifdata | 8)) {
        ;
    }
    *(__osExceptionVector *) UT_VEC = *(__osExceptionVector *) func_100071D0;
    *(__osExceptionVector *) XUT_VEC = *(__osExceptionVector *) func_100071D0;
    *(__osExceptionVector *) ECC_VEC = *(__osExceptionVector *) func_100071D0;
    *(__osExceptionVector *) E_VEC = *(__osExceptionVector *) func_100071D0;
    osWritebackDCache((void *) UT_VEC, E_VEC - UT_VEC + sizeof(__osExceptionVector));
    osInvalICache((void *) UT_VEC, E_VEC - UT_VEC + sizeof(__osExceptionVector));
    osMapTLBRdb();
    osPiRawReadIo(4, &clock);
    clock &= ~0xF;
    if (clock != 0) {
        D_8002BD10 = clock;
    }
    D_8002BD10 = D_8002BD10 * 3 / 4;
    if (D_8000030C == 0) {
        bzero(D_8000031C, 0x40);
    }
    stat = IO_READ(PI_STATUS_REG);
    while (stat & (PI_STATUS_IO_BUSY | PI_STATUS_DMA_BUSY)) {
        stat = IO_READ(PI_STATUS_REG);
    }
    if (!((leostat = IO_READ(LEO_STATUS)) & LEO_STATUS_PRESENCE_MASK)) {
        D_8002BD20 = 1;
        __osSetHWIntrRoutine(1, __osLeoInterrupt);
    } else {
        D_8002BD20 = 0;
    }
}
