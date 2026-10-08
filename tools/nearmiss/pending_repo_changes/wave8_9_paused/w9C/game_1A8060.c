#include <ultra64.h>
#include "functions.h"
#include "variables.h"


typedef struct Entry1517ABB0 {
    s32 unk0;
    u8 unk4;
    u8 pad5[3];
} Entry1517ABB0;

typedef struct Rec1517ABB0 {
    u8 unk0;
    u8 unk1;
    u8 pad2[6];
} Rec1517ABB0;

/* D_800DD460[i] holds a table of row pointers into Entry1517ABB0 arrays. */
#define ENTRY_1517ABB0(i, j, k) (((Entry1517ABB0 **)D_800DD460[i])[j][k])

extern Rec1517ABB0 D_800A7230[];
extern u16 D_800C4310[];
extern void func_10004074(s32);

void func_1517ABB0(void) {
    s32 i;
    s32 j;
    s32 k;

    for (i = 0; i < 2; i++) {
        if (D_800DD460[i] != 0) {
            for (j = 0; j < D_800C4310[D_800A7230[i].unk0]; j++) {
                for (k = 0; k < D_800A7230[i].unk1; k++) {
                    if (ENTRY_1517ABB0(i, j, k).unk0 != 0) {
                        if (ENTRY_1517ABB0(i, j, k).unk4 != 0) {
                            ENTRY_1517ABB0(i, j, k).unk4--;
                        } else {
                            func_10004074(ENTRY_1517ABB0(i, j, k).unk0);
                            ENTRY_1517ABB0(i, j, k).unk0 = 0;
                        }
                    }
                }
            }
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1A8060/func_1517AD00.s")
