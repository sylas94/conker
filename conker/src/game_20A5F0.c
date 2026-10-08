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
 * func_151DD140 = osEepromRead, verbatim SDK shape.  The redundant `b` at the end of the
 * 16K case (the old mism=101 park) is the SDK's `default:` having NO `break`: the default
 * body is physically last, so the 16K case's break jumps over it, and as1 later moves the
 * default's `li` into the compare chain's delay slot and deletes the body.
 */
extern u8 __osContLastCmd;
s32 __osSiRawStartDma(s32 dir, void *dramAddr);
s32 func_151DD710(OSMesgQueue *mq, OSContStatus *data);
void func_151DD304(u8 address);

s32 func_151DD140(OSMesgQueue *mq, u8 address, u8 *buffer) {
    s32 ret = 0;
    s32 i = 0;
    u16 type;
    u8 *ptr;
    OSContStatus sdata;
    __OSContEepromFormat eepromformat;

    ptr = (u8 *) &D_800E0A30;
    __osSiGetAccess();
    ret = func_151DD710(mq, &sdata);
    if (ret == 0) {
        type = sdata.type & (CONT_EEPROM | CONT_EEP16K);
        switch (type) {
            case CONT_EEPROM:
                if (address >= 64) {
                    ret = -1;
                }
                break;
            case CONT_EEPROM | CONT_EEP16K:
                if (address >= 256) {
                    ret = -1;
                }
                break;
            default:
                ret = CONT_NO_RESPONSE_ERROR;
        }
    }
    if (ret != 0) {
        __osSiRelAccess();
        return ret;
    }
    while (sdata.status & CONT_EEPROM_BUSY) {
        func_151DD710(mq, &sdata);
    }
    func_151DD304(address);
    __osSiRawStartDma(OS_WRITE, &D_800E0A30);
    osRecvMesg(mq, NULL, OS_MESG_BLOCK);
    __osSiRawStartDma(OS_READ, &D_800E0A30);
    __osContLastCmd = 4;
    osRecvMesg(mq, NULL, OS_MESG_BLOCK);
    for (i = 0; i < 4; i++) {
        ptr++;
    }
    eepromformat = *(__OSContEepromFormat *) ptr;
    ret = (eepromformat.rxsize & 0xC0) >> 4;
    if (ret == 0) {
        for (i = 0; i < 8; i++) {
            *buffer++ = eepromformat.data[i];
        }
    }
    __osSiRelAccess();
    return ret;
}

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
