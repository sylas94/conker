#include <ultra64.h>

/* The SDK source uses a file-static `OSTask tp;` at 0x80036B60. Referencing each
 * converted field as its own absolute symbol (rather than tp.t.field off a single base)
 * stops IDO from CSE-ing the base into a saved register, matching the per-field %hi/%lo
 * the static generates. Avoids needing a .bss placement for the static. */
extern OSTask D_80036B60;
extern u64 *D_80036B70;
extern u64 *D_80036B78;
extern u64 *D_80036B80;
extern u64 *D_80036B88;
extern u64 *D_80036B8C;
extern u64 *D_80036B90;
extern u64 *D_80036B98;

OSTask *_VirtualToPhysicalTask(OSTask *intp)
{
    bcopy(intp, &D_80036B60, sizeof(OSTask));
    if (D_80036B70 != NULL)
        D_80036B70 = (u64 *) osVirtualToPhysical(D_80036B70);
    if (D_80036B78 != NULL)
        D_80036B78 = (u64 *) osVirtualToPhysical(D_80036B78);
    if (D_80036B80 != NULL)
        D_80036B80 = (u64 *) osVirtualToPhysical(D_80036B80);
    if (D_80036B88 != NULL)
        D_80036B88 = (u64 *) osVirtualToPhysical(D_80036B88);
    if (D_80036B8C != NULL)
        D_80036B8C = (u64 *) osVirtualToPhysical(D_80036B8C);
    if (D_80036B90 != NULL)
        D_80036B90 = (u64 *) osVirtualToPhysical(D_80036B90);
    if (D_80036B98 != NULL)
        D_80036B98 = (u64 *) osVirtualToPhysical(D_80036B98);
    return &D_80036B60;
}

void osSpTaskLoad(OSTask *intp)
{

    OSTask *tp;
    tp = _VirtualToPhysicalTask(intp);
    if (tp->t.flags & OS_TASK_YIELDED)
    {
        tp->t.ucode_data = tp->t.yield_data_ptr;
        tp->t.ucode_data_size = tp->t.yield_data_size;
        intp->t.flags &= ~OS_TASK_YIELDED;
        if (tp->t.flags & OS_TASK_LOADABLE)
          tp->t.ucode = (u64 *)IO_READ((u32)intp->t.yield_data_ptr + OS_YIELD_DATA_SIZE - 4);
    }
    osWritebackDCache(tp, sizeof(OSTask));
    __osSpSetStatus(SP_CLR_YIELD | SP_CLR_YIELDED | SP_CLR_TASKDONE | SP_SET_INTR_BREAK);
    while (__osSpSetPc(SP_IMEM_START) == -1)
        ;

    while (__osSpRawStartDma(1, (SP_IMEM_START - sizeof(*tp)), tp,
                 sizeof(OSTask)) == -1)
        ;

    while (__osSpDeviceBusy())
        ;

    while (__osSpRawStartDma(1, SP_IMEM_START, tp->t.ucode_boot,
                 tp->t.ucode_boot_size) == -1)
        ;
}

void osSpTaskStartGo(OSTask *tp) {
    while(__osSpDeviceBusy())
        ;
    __osSpSetStatus(SP_SET_INTR_BREAK | SP_CLR_SSTEP | SP_CLR_BROKE | SP_CLR_HALT);
}
