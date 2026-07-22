#include <os_internal.h>
#include "controller.h"
#include "siint.h"


extern u32 D_800429D0[];   /* __osPfsPifRam ramarray words */
extern u32 D_80042A0C;     /* __osPfsPifRam.pifstatus */

extern void __osPfsRequestData(u8);
extern void __osPfsGetInitData(u8 *, OSContStatus *);

s32 osPfsIsPlug2(OSMesgQueue *queue, u8 *pattern)
{
    s32 ret;
    OSMesg dummy;
    u8 bitpattern;
    OSContStatus data[MAXCONTROLLERS];
    s32 channel;
    u8 bits;
    s32 crc_error_cnt;

    ret = 0;
    bits = 0;
    crc_error_cnt = 3;
    __osSiGetAccess();
    while (TRUE)
    {
        __osPfsRequestData(CONT_CMD_REQUEST_STATUS);
        ret = __osSiRawStartDma(OS_WRITE, D_800429D0);
        osRecvMesg(queue, &dummy, OS_MESG_BLOCK);
        ret = __osSiRawStartDma(OS_READ, D_800429D0);
        osRecvMesg(queue, &dummy, OS_MESG_BLOCK);
        __osPfsGetInitData(&bitpattern, data);
        for (channel = 0; channel < __osMaxControllers; channel++)
        {
            if ((data[channel].status & CONT_ADDR_CRC_ER) == 0)
            {
                crc_error_cnt--;
                break;
            }
        }
        if (__osMaxControllers == channel)
            crc_error_cnt = 0;
        if (crc_error_cnt < 1)
        {
            for (channel = 0; channel < __osMaxControllers; channel++)
            {
                if (data[channel].errno == 0 && (data[channel].status & CONT_CARD_ON) != 0)
                    bits |= 1 << channel;
            }
            __osSiRelAccess();
            *pattern = bits;
            return ret;
        }
    }
}

void __osPfsRequestData2(u8 cmd)
{
    u8 *ptr;
    __OSContRequesFormat requestformat;
    s32 i;

    __osContLastCmd = cmd;
    for (i = 0; i < 16; i++) {
        D_800429D0[i] = 0;
    }
    D_80042A0C = 1;
    ptr = (u8 *) D_800429D0;
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


void __osPfsGetInitData2(u8 *pattern, OSContStatus *data)
{
    u8 *ptr;
    __OSContRequesFormat requestformat;
    s32 i;
    u8 bits;

    bits = 0;
    ptr = (u8 *) D_800429D0;
    for (i = 0; i < __osMaxControllers; i++, ptr += sizeof(__OSContRequesFormat))
    {
        requestformat = *(__OSContRequesFormat *) ptr;
        data->errno = CHNL_ERR(requestformat);
        if (data->errno == 0)
        {
            data->type = (requestformat.typel << 8) | (requestformat.typeh);
            data->status = requestformat.status;
            bits |= 1 << i;
        }
        data++;
    }
    *pattern = bits;
}
