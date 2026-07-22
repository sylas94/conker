/* SDK osCreatePiManager. The file-statics (piThread, piThreadStack, piEventQueue,
 * piEventBuf, __osPiDevMgr) live at fixed addresses; reference them by their extracted
 * symbol names. __osDevMgrMain is func_10002E50. The thread stack top
 * &piThreadStack[OS_PIM_STACKSIZE] resolves to &piEventQueue (adjacent in .bss). */
#include <ultra64.h>

extern OSDevMgr D_8002AB50;      /* __osPiDevMgr */
extern OSThread D_80035910;      /* piThread */
extern OSMesgQueue piEventQueue;
extern OSMesg D_80036B58;        /* piEventBuf */
extern OSMesgQueue __osPiAccessQueue;
extern u32 __osPiAccessQueueEnabled;
extern void func_10002E50(void *);   /* __osDevMgrMain */
extern void __osPiCreateAccessQueue(void);
extern s32 osPiRawStartDma(s32, u32, void *, u32);
extern s32 osEPiRawStartDma(OSPiHandle *, s32, u32, void *, u32);

void osCreatePiManager(OSPri pri, OSMesgQueue *cmdQ, OSMesg *cmdBuf, s32 cmdMsgCnt)
{
    u32 savedMask;
    OSPri oldPri;
    OSPri myPri;

    if (!D_8002AB50.active)
    {
        osCreateMesgQueue(cmdQ, cmdBuf, cmdMsgCnt);
        osCreateMesgQueue(&piEventQueue, (OSMesg *) &D_80036B58, 1);
        if (!__osPiAccessQueueEnabled)
            __osPiCreateAccessQueue();
        osSetEventMesg(OS_EVENT_PI, &piEventQueue, (OSMesg) 0x22222222);
        oldPri = -1;
        myPri = osGetThreadPri(NULL);
        if (myPri < pri)
        {
            oldPri = myPri;
            osSetThreadPri(NULL, pri);
        }
        savedMask = __osDisableInt();
        D_8002AB50.active = 1;
        D_8002AB50.thread = &D_80035910;
        D_8002AB50.cmdQueue = cmdQ;
        D_8002AB50.evtQueue = &piEventQueue;
        D_8002AB50.acsQueue = &__osPiAccessQueue;
        D_8002AB50.dma = osPiRawStartDma;
        D_8002AB50.edma = osEPiRawStartDma;
        /* stack top == &piThreadStack[OS_PIM_STACKSIZE], which is &piEventQueue */
        osCreateThread(&D_80035910, 0, func_10002E50, &D_8002AB50, &piEventQueue, pri);
        osStartThread(&D_80035910);
        __osRestoreInt(savedMask);
        if (oldPri != -1)
        {
            osSetThreadPri(NULL, oldPri);
        }
    }
}
