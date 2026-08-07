#include <ultra64.h>
#include "functions.h"
#include "variables.h"

typedef struct {
    s32 romStart;
    s32 romEnd;
} RomRange15015920;

typedef struct {
    u8 pad[4];
    u8 b4;
    u8 b5;
    u8 b6;
    u8 b7;
} Record15015920;

extern RomRange15015920 D_80082F80[];
extern void func_10004074(void *);
extern void func_15015A38(u8 *, s32, s32);

extern u8 D_800CBD4C;

void func_15015910(void) {
    D_800CBD4C = 0;
}

void func_15015920(s16 arg0) {
    u8 *data;
    u8 *pos;
    s32 idx;

    data = (u8 *)func_10003C6C(0x2800, 1, 2, 1, 0);
    func_10004514(D_80082F80[arg0].romStart, data, D_80082F80[arg0].romEnd - D_80082F80[arg0].romStart, 1);
    pos = data;
    idx = 0;
    if ((u32)(pos + 0xF) < (u32)(data + D_80082F80[arg0].romEnd - D_80082F80[arg0].romStart)) {
        do {
            func_15015A38(pos, idx, arg0);
            pos = (u8 *)((s32)pos + (((Record15015920 *)pos)->b4 << 0x18) + (((Record15015920 *)pos)->b5 << 0x10) + (((Record15015920 *)pos)->b6 << 8) + ((Record15015920 *)pos)->b7);
            idx += 1;
        } while ((u32)(pos + 0xF) < (u32)(data + D_80082F80[arg0].romEnd - D_80082F80[arg0].romStart));
    }
    func_10004074(data);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_42DC0/func_15015A38.s")
