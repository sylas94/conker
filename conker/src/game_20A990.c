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

extern OSPifRam D_800E0A30;
extern u8 __osContLastCmd;

s32 __osSiRawStartDma(s32 dir, void *dramAddr);

/* func_151DD65C = __osPackEepWriteData.  Byte-perfect at the tree default.
 *
 * The other three are parked near-misses, all with golden's instruction sequence already:
 *   func_151DD4E0 (osEepromWrite)  mism=85,  n=94/95   -- same missing trailing `b` as
 *       osEepromRead in game_20A5F0; see the note there.
 *   func_151DD710 (__osEepStatus)  mism=89,  n=109/108 -- one instruction too MANY.
 *   func_151DD8C0 (demo playback)  mism=35,  n=44/44   -- every instruction is golden's;
 *       the residue is register allocation (golden keeps &D_800BE748 in $a1 and the frame
 *       pointer in $a0 and starts short-lived temps at $t8; we use $a0/$v0/$t7).  Six
 *       spellings of the frame-pointer expression all land within 45-50.
 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_20A990/func_151DD4E0.s")

void func_151DD65C(u8 address, u8 *buffer) {
    u8 *ptr;
    __OSContEepromFormat eepromformat;
    s32 i;

    ptr = (u8 *) &D_800E0A30;
    D_800E0A30.pifstatus = 1;
    eepromformat.txsize = 10;
    eepromformat.rxsize = 1;
    eepromformat.cmd = 5;
    eepromformat.address = address;
    for (i = 0; i < 8; i++) {
        eepromformat.data[i] = *buffer++;
    }
    for (i = 0; i < 4; i++) {
        *ptr++ = 0;
    }
    *(__OSContEepromFormat *) ptr = eepromformat;
    ptr += sizeof(__OSContEepromFormat);
    *ptr = 0xFE;
}

s32 func_151DD710(OSMesgQueue *mq, OSContStatus *data) {
    s32 ret = 0;
    s32 i;
    u8 *ptr;
    __OSContRequesFormat requestformat;

    for (i = 0; i < 16; i++) {
        D_800E0A30.ramarray[i] = 0;
    }
    D_800E0A30.pifstatus = 1;
    ptr = (u8 *) &D_800E0A30;
    for (i = 0; i < 4; i++) {
        *ptr++ = 0;
    }
    requestformat.dummy = 0xFF;
    requestformat.txsize = 1;
    requestformat.rxsize = 3;
    requestformat.cmd = 0;
    requestformat.typeh = 0xFF;
    requestformat.typel = 0xFF;
    requestformat.status = 0xFF;
    requestformat.dummy1 = 0xFF;
    *(__OSContRequesFormat *) ptr = requestformat;
    ptr += sizeof(__OSContRequesFormat);
    *ptr = 0xFE;

    ret = __osSiRawStartDma(1, &D_800E0A30);
    osRecvMesg(mq, NULL, OS_MESG_BLOCK);
    __osContLastCmd = 0xFE;
    if (ret != 0) {
        return ret;
    }
    ret = __osSiRawStartDma(0, &D_800E0A30);
    osRecvMesg(mq, NULL, OS_MESG_BLOCK);
    if (ret != 0) {
        return ret;
    }
    ptr = (u8 *) &D_800E0A30;
    for (i = 0; i < 4; i++) {
        *ptr++ = 0;
    }
    requestformat = *(__OSContRequesFormat *) ptr;
    data->errno = (requestformat.rxsize & 0xC0) >> 4;
    data->type = (requestformat.typel << 8) | (requestformat.typeh);
    data->status = requestformat.status;
    return data->errno;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_20A990/func_151DD8C0.s")
