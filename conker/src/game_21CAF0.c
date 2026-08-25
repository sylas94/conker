#include <ultra64.h>
#include "functions.h"
#include "variables.h"

/* Rare linked a private copy of the libultra VI code into the game binary; this TU is
 * osViSetSpecialFeatures().  Like the rest of that embedded copy (see game_21CAC0) it was
 * built at -O1, not the tree default -O2 -g3 -- hence the Makefile OPT_FLAGS override.
 *
 * D_8002BDE4 is __osViNext.  __OSViContext is not in include/, so the layout is declared
 * file-locally per the project convention (structs.h is not to be edited for one TU).
 */
typedef struct {
    /* 0x00 */ u16 state;
    /* 0x02 */ u16 retraceCount;
    /* 0x04 */ void *framep;
    /* 0x08 */ OSViMode *modep;
    /* 0x0C */ u32 control;
    /* 0x10 */ OSMesgQueue *msgq;
    /* 0x14 */ OSMesg msg;
} ViContext;

extern ViContext *D_8002BDE4;

void func_151EF640(u32 func) {
    register u32 prevInt = __osDisableInt();

    if (func & OS_VI_GAMMA_ON) {
        D_8002BDE4->control |= 0x8; /* VI_CTRL_GAMMA_ON */
    }
    if (func & OS_VI_GAMMA_OFF) {
        D_8002BDE4->control &= ~0x8;
    }
    if (func & OS_VI_GAMMA_DITHER_ON) {
        D_8002BDE4->control |= 0x4; /* VI_CTRL_GAMMA_DITHER_ON */
    }
    if (func & OS_VI_GAMMA_DITHER_OFF) {
        D_8002BDE4->control &= ~0x4;
    }
    if (func & OS_VI_DIVOT_ON) {
        D_8002BDE4->control |= 0x10; /* VI_CTRL_DIVOT_ON */
    }
    if (func & OS_VI_DIVOT_OFF) {
        D_8002BDE4->control &= ~0x10;
    }
    if (func & OS_VI_DITHER_FILTER_ON) {
        D_8002BDE4->control |= 0x10000; /* VI_CTRL_DITHER_FILTER_ON */
        D_8002BDE4->control &= ~0x300;  /* VI_CTRL_ANTIALIAS_MASK */
    }
    if (func & OS_VI_DITHER_FILTER_OFF) {
        D_8002BDE4->control &= ~0x10000;
        D_8002BDE4->control |= D_8002BDE4->modep->comRegs.ctrl & 0x300;
    }
    D_8002BDE4->state |= 8; /* VI_STATE_MODE_SPECIAL_UPDATED */
    __osRestoreInt(prevInt);
}
