#include <ultra64.h>

#include "functions.h"
#include "variables.h"


extern u32 osGetCount(void);
s32 func_160016F4(s32 arg0);
s32 func_160019A8(s32 direction, void *dramAddr);
typedef struct 
{
  u32 ramarray[15];
  u32 pifstatus;
} OSPifRam;
typedef struct
{
  u8 dummy;
  u8 txsize;
  u8 rxsize;
  u8 cmd;
  u16 button;
  s8 stick_x;
  s8 stick_y;
} __OSContReadFormat;
extern u8 __osContLastCmd;
extern u8 __osMaxControllers;
extern OSPifRam __osContPifRam;
extern s32 D_80042A4C;
void func_160018BC(void);
s32 func_16001700(void)
{
  s32 ret;
  s32 count;
  s32 count2;
  u32 end;
  s32 *ptr;
  s32 *ptrEnd;
  if (__osContLastCmd != 1)
  {
    func_160018BC();
    func_160019A8(1, &__osContPifRam);
    count = 0;
    end = osGetCount() + 0x30D40;
    if (osGetCount() < end)
    {
 do { count = func_160016F4(count); } while (osGetCount() < end); } func_160016F4(count); } ptrEnd = (s32 *) (&__osContLastCmd); ptr = (s32 *) (&__osContPifRam); do { ptrEnd = (s32 *) (&__osContLastCmd);
    *(ptr++) = 0xFF;
  }
  while (((u32) ptr) < ((u32) ptrEnd));
  D_80042A4C = 0;
  ret = func_160019A8(0, &__osContPifRam);
  __osContLastCmd = 1;
  count2 = 0;
  end = osGetCount() + 0xC3500;
  if (osGetCount() < end)
  {
    do
    {
      count2 = func_160016F4(count2);
    }
    while (osGetCount() < end);
  }
  func_160016F4(count2);
  return ret;
}

s32 func_160019A8(s32 direction, void *dramAddr);

void func_16001830(OSContPad *data)
{
  u8 *ptr;
  __OSContReadFormat readformat;
  s32 i;

  ptr = (u8 *)&__osContPifRam;
  i = 0;
  if ((s32)__osMaxControllers > 0)
  {
    do
    {
      readformat = *(__OSContReadFormat *)ptr;
      data->errno = (readformat.rxsize & CHNL_ERR_MASK) >> 4;
      if (data->errno == 0)
      {
        data->button = readformat.button;
        data->stick_x = readformat.stick_x;
        data->stick_y = readformat.stick_y;
      }
      i++;
      ptr += sizeof(__OSContReadFormat);
      data++;
    }
    while (i < (s32)__osMaxControllers);
  }
}
// __osPackReadData
void func_160018BC(void)
{
  u8 *ptr;
  __OSContReadFormat readformat;
  s32 i;

  /* NOTE: this loop zeroes all 16 words of __osContPifRam (ramarray[15] + pifstatus),
   * not just ramarray -- golden's bound is __osContPifRam + 0x40. IDO strength-reduces
   * the index into a pointer walk whose limit it spells %hi/%lo(__osContPifRam+0x40),
   * while the splat-extracted golden spells the same address %hi/%lo(__osContLastCmd)
   * (undefined_syms_auto.txt pins __osContPifRam = 0x80042A10 and
   * __osContLastCmd = 0x80042A50, so the two are the same word). That is the whole
   * residual against golden: asm-differ scores 10, tools/relcheck.py PASSES, and the
   * two sibling functions in this file already sit on the same floor. Spelling the
   * loop as a pointer walk bounded by &__osContLastCmd names the symbol correctly but
   * costs the separate base materialisation IDO gives the strength-reduced form
   * (score 340), so the index form below is the closer of the two. */
  ptr = (u8 *)&__osContPifRam;
  for (i = 0; i < 16; i++)
  {
    ((u32 *)&__osContPifRam)[i] = 0;
  }
  __osContPifRam.pifstatus = 1;

  readformat.dummy = 0xFF;
  readformat.txsize = 1;
  readformat.rxsize = 4;
  readformat.cmd = 1;
  readformat.button = 0xFFFF;
  readformat.stick_x = -1;
  readformat.stick_y = -1;

  for (i = 0; i < (s32)__osMaxControllers; i++)
  {
    *(__OSContReadFormat *)ptr = readformat;
    ptr += sizeof(__OSContReadFormat);
  }
  *ptr = 0xFE;
}

// another __osSiDeviceBusy function
s32 func_16001984()
{
    register u32 stat = IO_READ(SI_STATUS_REG);
    if (stat & (SI_STATUS_DMA_BUSY | SI_STATUS_RD_BUSY))
        return 1;
    return 0;
}

// very similar to __osSiRawStartDma
s32 func_160019A8(s32 direction, void *dramAddr) {
    if ((s32)dramAddr & 3) { // what is this checking?
        return -1;
    }
    if (func_16001984()) {
        return -1;
    }

    if (direction == OS_WRITE) {
        osWritebackDCache(dramAddr, 64);
    }

    IO_WRITE(SI_DRAM_ADDR_REG, osVirtualToPhysical(dramAddr));

    if (direction == OS_READ) {
        IO_WRITE(SI_PIF_ADDR_RD64B_REG, 0x1FC007C0);
    } else {
        IO_WRITE(SI_PIF_ADDR_WR64B_REG, 0x1FC007C0);
    }
    if (direction == OS_READ) {
        osInvalDCache(dramAddr, 64);
    }

    return 0;
}

void func_16001A64(void) {
}

s32 func_16001A6C(f32 arg0) {
    s32 tmp = *(s32*) &arg0;

    if ((tmp * 2) == 0) {
        return 0;
    }
    tmp = (tmp & 0x7F800000) >> 0x17;
    if ((tmp <= 0) || (tmp >= 255)) {
        return 1;
    }
    return 0;
}
