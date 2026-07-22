#include <ultra64.h>
#include "functions.h"
#include "variables.h"


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
