#include <os_internal.h>
#include <rcp.h>
#include "../os/osint.h"

// SDK source verbatim. hdwrBugFlag MUST be the function-scope static: that storage class is
// what makes IDO emit a fresh `lui` per access (an extern hoists &hdwrBugFlag into a register).
// Its 0x10-byte .data (0x8002AB40, ROM 0x2AB40) has to be owned by this TU:
//     - [0x2AB40, .data, libultra/io/aisetnextbuf]   (split out of the init_data `data` blob)
s32 osAiSetNextBuffer(void *bufPtr, u32 size) {
    static u8 hdwrBugFlag = 0;
    char *bptr = bufPtr;

    if (hdwrBugFlag != 0) {
        bptr -= 0x2000;
    }

    if ((((u32)bufPtr + size) & 0x3FFF) == 0x2000) {
        hdwrBugFlag = 1;
    } else {
        hdwrBugFlag = 0;
    }

    if (__osAiDeviceBusy()) {
        return -1;
    }

    IO_WRITE(AI_DRAM_ADDR_REG, osVirtualToPhysical(bptr));
    IO_WRITE(AI_LEN_REG, size);

    return 0;
}
