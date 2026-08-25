#include <ultra64.h>
#include "functions.h"
#include "variables.h"

typedef struct Entity {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ u8  unk8[0x34];
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ u8  unk40[0x33];
    /* 0x73 */ u8  unk73;
} Entity;

typedef struct EntitySlot {
    /* 0x00 */ Entity *unk0;
    /* 0x04 */ s32 unk4;
} EntitySlot;

typedef struct Owner {
    /* 0x000 */ u8 pad0[0x11B];
    /* 0x11B */ u8 unk11B;
} Owner;

extern s32 D_800DBFC0;
extern EntitySlot D_800DBFC8[];
extern Owner *D_800CC5EC;

void func_1511F980(void) {
    D_800DBFC0 = 0;
}

void func_1511F990(Entity *arg0, s32 arg1) {
    s32 i;
    s32 j;
    s32 added;
    s32 state;
    s32 flag;
    s32 val;

    /* The & 0xFF is redundant for the value (the (s8) cast already keeps bits 16..23)
     * but it is NOT redundant for codegen: it costs one IDO integer web in block 0,
     * which sets the t6..t9 temp-rotation phase for the whole function.  Removing it,
     * or spelling it (s8)(u8), rotates every temp by one and costs ~60 rows.  Keep it. */
    val = (s8)((arg0->unk3C >> 16) & 0xFF);
    added = 0;
    state = arg0->unk73 & 3;
    flag = arg0->unk73 & 4;
    for (i = 0; i < D_800DBFC0; i++) {
        if (D_800DBFC8[i].unk0 == arg0) {
            break;
        }
    }
    if (i == D_800DBFC0) {
        if (i >= 4) {
            return;
        }
        D_800DBFC8[i].unk0 = arg0;
        D_800DBFC8[i].unk4 = val;
        D_800DBFC0++;
        added = 1;
    }
    if (val >= 0) {
        if (added != 0) {
            if (val == D_800CC5EC->unk11B) {
                if (arg1 == 0) {
                    if (state != 0 && state != 1) {
                        state = 1;
                    }
                    arg0->unk4 = (f32) ((arg0->unk3C << 22) >> 22);
                } else if (arg1 == 1) {
                    state = 3;
                } else if (arg1 == 2) {
                    state = 2;
                } else if (arg1 == 3) {
                    if (state != 0 && state != 1) {
                        if (flag != 0) {
                            state = 1;
                        }
                    } else {
                        if (flag == 0) {
                            state = 3;
                        }
                    }
                    arg0->unk4 = (f32) ((arg0->unk3C << 22) >> 22);
                }
            } else {
                if (arg1 == 0 || arg1 == 2 || arg1 == 3) {
                    if (arg1 != 3 || flag != 0) {
                        state = 0;
                    } else {
                        state = 3;
                    }
                }
            }
        } else {
            if (state == 1 || state == 2) {
                for (j = 0; j < D_800DBFC0; j++) {
                    if (j == i) {
                        continue;
                    }
                    if (val != D_800DBFC8[j].unk4) {
                        continue;
                    }
                    if (flag == 0 && (D_800DBFC8[j].unk0->unk73 & 4)) {
                        continue;
                    }
                    if ((D_800DBFC8[j].unk0->unk73 & 3) == 3 && state == 2) {
                        continue;
                    }
                    if ((D_800DBFC8[j].unk0->unk73 & 3) == 0 && state == 1) {
                        continue;
                    }
                    D_800DBFC8[j].unk0->unk73 &= ~3;
                    D_800DBFC8[j].unk0->unk73 |= state;
                }
            }
        }
    }
    arg0->unk73 &= ~3;
    arg0->unk73 |= state;
}
