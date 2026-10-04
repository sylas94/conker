#include <ultra64.h>
#include "functions.h"
#include "variables.h"

/* The eeprom PIF ram block at 0x800E0A30 and the two request layouts it carries.  These are
 * file-local because src/libultra/io/controller.h describes a DIFFERENT (already-matched)
 * copy of this code -- see the note there -- and its __OSContRequesFormat orders typeh/typel
 * the other way round from what these functions want. */
typedef struct {
    /* 0x00 */ u32 ramarray[15];
    /* 0x3C */ u32 pifstatus;
} OSPifRam;

typedef struct {
    /* 0x0 */ u8 txsize;
    /* 0x1 */ u8 rxsize;
    /* 0x2 */ u8 cmd;
    /* 0x3 */ u8 address;
    /* 0x4 */ u8 data[8];
} __OSContEepromFormat;

extern OSPifRam D_800E0A30;

/* func_151DD304 = __osPackEepReadData.  Byte-perfect at the tree default -- no OPT_FLAGS
 * override needed here, unlike the game's other private libultra copies.
 *
 * func_151DD140 = osEepromRead.  PARKED at mism=101, n=112/113, and the frame is already
 * golden's (sdata 0x3C, eepromformat 0x30, ret 0x4C -- four word automatics above the two
 * aggregates, sdata declared before eepromformat).  The ONE missing instruction is a
 * redundant `b .L151DD1D0` that golden emits at the end of the LAST switch case, with
 * `addiu $a0,$zero,-0x1` in its delay slot; IDO folds ours into a bare `addiu` because that
 * block is physically last.  Refuted as a source question: default-first / default-middle /
 * default-last, if-else-if, early `break` inside each case, `>` vs `>=`, switching on a u16
 * local, hoisting the early-out above the switch, and -O2 / -O1 all leave it at 100-141.
 * Next lever is the permuter, not another spelling.
 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_20A5F0/func_151DD140.s")

void func_151DD304(u8 address) {
    u8 *ptr;
    __OSContEepromFormat eepromformat;
    s32 i;

    ptr = (u8 *) &D_800E0A30;
    D_800E0A30.pifstatus = 1;
    eepromformat.txsize = 2;
    eepromformat.rxsize = 8;
    eepromformat.cmd = 4;
    eepromformat.address = address;
    for (i = 0; i < 4; i++) {
        *ptr++ = 0;
    }
    *(__OSContEepromFormat *) ptr = eepromformat;
    ptr += sizeof(__OSContEepromFormat);
    *ptr = 0xFE;
}
