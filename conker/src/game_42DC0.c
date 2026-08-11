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

typedef u8 Cell15015A38[224];

typedef struct {
    u8 width;
    u8 height;
    u8 unk2;
    u8 unk3;
} Glyph15015A38;

extern Glyph15015A38 *D_80085994[];
extern Cell15015A38 *D_80085990[];

void func_15015A38(u8 *arg0, s32 arg1, s32 arg2) {
    s32 i;
    s32 n;
    s32 row;
    s32 pos;
    s32 stride;
    s32 flip;
    s32 len;
    s32 val;

    D_80085994[arg2][arg1].width = arg0[0] + 1;
    D_80085994[arg2][arg1].height = arg0[1] + 1;
    D_80085994[arg2][arg1].unk2 = arg0[2];
    D_80085994[arg2][arg1].unk3 = arg0[3];

    stride = (D_80085994[arg2][arg1].width + 7) & 0xFFF8;
    pos = 8;

    for (i = 0; i < D_80085994[arg2][arg1].width; i++) {
        D_80085990[arg2][arg1][i] = 0;
    }

    for (row = 1; row < D_80085994[arg2][arg1].height + 1; row++) {
        if ((row & 1) == 0) {
            flip = 0;
        } else {
            flip = 4;
        }
        for (i = 0; i < D_80085994[arg2][arg1].width; i++) {
            if (i == 0) {
                D_80085990[arg2][arg1][(i ^ flip) + row * stride] = 0;
            } else {
                len = (arg0[pos] & 0xF) + 1;
                val = arg0[pos] & 0xF0;
                pos++;
                for (n = 0; n < len; n++) {
                    D_80085990[arg2][arg1][((i + n) ^ flip) + row * stride] = val;
                }
                i += len - 1;
            }
        }
        for (; i < stride; i++) {
            D_80085990[arg2][arg1][(i ^ flip) + row * stride] = 0;
        }
    }

    for (i = 0; i < stride; i++) {
        D_80085990[arg2][arg1][i + row * stride] = 0;
    }
}
