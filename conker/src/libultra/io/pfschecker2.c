#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#include "controller.h"


// TODO (large, 435 instrs, -O1): SDK osPfsChecker. Calls corrupted_init/corrupted (the
// non-2 symbols), __osCheckId/__osGetId, __osContRamRead/Write, __osPfsRWInode,
// __osPfsSelectBank. Frame 0x488: dir entry (__OSDir) @0x25C, inode buf @0x27C, page
// arrays @0x23C and @0x37C, bank cursor @0x33, repairedFlag @0x34, i @0x484.
// Phases: (1) __osCheckId; if ret==2 __osGetId; if ret return ret; corrupted_init(pfs,&cache@0x38).
// (2) for(i=0;i<pfs->dir_size@0x50;i++) __osContRamRead dir entry; if game_code@0x25C && company@0x260
//     nonzero, walk the start_page@0x262 inode chain checking corrupted(); on corruption or
//     start_page==1, blank the entry + __osContRamWrite it back (repairedFlag++).
// (3) for each bank: __osPfsRWInode read, rebuild the used inode table @0x37C from @0x23C marks,
//     __osPfsRWInode write back. (4) if repairedFlag: pfs->status@0x0 |= 2; else &= ~2. return 0.
// Use the reverse-declaration stack rule + marking-inside-if register trick from [[ido-matching-tricks]].
#pragma GLOBAL_ASM("asm/nonmatchings/libultra/io/pfschecker2/osPfsChecker2.s")

s32 corrupted_init2(OSPfs *pfs, __OSInodeCache *usedTbl)
{
    s32 i;
    s32 offset;
    s32 startPage;
    u8 bank;
    __OSInodeUnit inodePage;
    __OSInode inode;
    s32 ret;

    for (i = 0; i < 256; i++) {
        usedTbl->map[i] = 0;
    }
    usedTbl->bank = 0xFF;
    for (bank = 0; bank < pfs->banks; bank++) {
        if (bank > 0) {
            startPage = 1;
        } else {
            startPage = pfs->inode_start_page;
        }
        ret = __osPfsRWInode(pfs, &inode, 0, bank);
        if ((ret != 0) && (ret != 3)) {
            return ret;
        }
        for (i = startPage; i < 128; i++) {
            inodePage = inode.inode_page[i];
            if (inodePage.ipage < pfs->inode_start_page) {
                continue;
            }
            if (inodePage.inode_t.bank != bank) {
                offset = inodePage.inode_t.page / 4 + (inodePage.inode_t.bank % 8) * 32;
                usedTbl->map[offset] |= 1 << (bank % 8);
            }
        }
    }
    return 0;
}

s32 corrupted2(OSPfs *pfs, __OSInodeUnit startpage, __OSInodeCache *usedTbl)
{
    s32 j;
    s32 offset;
    s32 count;
    u8 bank;
    s32 startPage;
    s32 ret;

    count = 0;
    ret = 0;
    offset = startpage.inode_t.page / 4 + (startpage.inode_t.bank % 8) * 32;
    for (bank = 0; bank < pfs->banks; bank++) {
        startPage = (bank > 0) ? 1 : pfs->inode_start_page;
        if (bank != startpage.inode_t.bank) {
            if ((usedTbl->map[offset] & (1 << (bank % 8))) == 0) {
                continue;
            }
        }
        if (bank != usedTbl->bank) {
            ret = __osPfsRWInode(pfs, &usedTbl->inode, 0, bank);
            if ((ret != 0) && (ret != 3)) {
                return ret;
            }
            usedTbl->bank = bank;
        }
        for (j = startPage; (count < 2) && (j < 128); j++) {
            if (usedTbl->inode.inode_page[j].ipage == startpage.ipage) {
                count++;
            }
        }
        if (count >= 2) {
            return 2;
        }
    }
    return count;
}
