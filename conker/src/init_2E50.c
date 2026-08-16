#include <ultra64.h>

#include "functions.h"

/* variables.h is deliberately not included: it declares D_80035910 as an
 * OSThread *, but the PI thread's ADDRESS is what gets passed to osStopThread
 * here. src/libultra/io/pimgr.c carries the same file-local override. */
extern OSThread D_80035910; /* piThread */
extern u8 D_8003A572;
extern u8 D_8003A573;
extern u8 D_8003A575;

/* __osDevMgrMain, with Rare's PI-thread interlock added to the DMAREAD case. */
void func_10002E50(void *arg) {
    OSIoMesg *mb;
    OSMesg em;
    OSMesg dummy;
    OSDevMgr *dm;
    s32 ret;

    mb = NULL;
    dm = (OSDevMgr *)arg;

    while (1) {
        osRecvMesg(dm->cmdQueue, (OSMesg *)&mb, OS_MESG_BLOCK);
        switch (mb->hdr.type) {
            case OS_MESG_TYPE_DMAREAD:
                if (D_8003A572 != 0) {
                    D_8003A575 = 1;
                    osStopThread(&D_80035910);
                    D_8003A575 = 0;
                }
                D_8003A573 = 1;
                osRecvMesg(dm->acsQueue, &dummy, OS_MESG_BLOCK);
                ret = dm->dma(OS_READ, mb->devAddr, mb->dramAddr, mb->size);
                break;
            case OS_MESG_TYPE_DMAWRITE:
                osRecvMesg(dm->acsQueue, &dummy, OS_MESG_BLOCK);
                ret = dm->dma(OS_WRITE, mb->devAddr, mb->dramAddr, mb->size);
                break;
            case OS_MESG_TYPE_EDMAREAD:
                osRecvMesg(dm->acsQueue, &dummy, OS_MESG_BLOCK);
                ret = dm->edma(mb->piHandle, OS_READ, mb->devAddr, mb->dramAddr, mb->size);
                break;
            case OS_MESG_TYPE_EDMAWRITE:
                osRecvMesg(dm->acsQueue, &dummy, OS_MESG_BLOCK);
                ret = dm->edma(mb->piHandle, OS_WRITE, mb->devAddr, mb->dramAddr, mb->size);
                break;
            case OS_MESG_TYPE_LOOPBACK:
                osSendMesg(mb->hdr.retQueue, mb, OS_MESG_NOBLOCK);
                ret = -1;
                break;
            default:
                ret = -1;
                break;
        }
        if (ret == 0) {
            osRecvMesg(dm->evtQueue, &em, OS_MESG_BLOCK);
            osSendMesg(mb->hdr.retQueue, mb, OS_MESG_NOBLOCK);
            osSendMesg(dm->acsQueue, NULL, OS_MESG_NOBLOCK);
            if (mb->hdr.type == OS_MESG_TYPE_DMAREAD) {
                D_8003A573 = 0;
            }
        }
    }
}
