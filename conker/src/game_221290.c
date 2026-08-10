#include <ultra64.h>

#include "functions.h"
#include "variables.h"



#pragma GLOBAL_ASM("asm/nonmatchings/game_221290/func_151F3DE0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_221290/func_151F42E8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_221290/func_151F4F38.s")

/* Rare's compressed-audio bitstream decoder context. Not in structs.h. */
typedef struct {
    /* 0x00 */ s32 unk00[23];
    /* 0x5C */ s32 unk5C[13];
    /* 0x90 */ s32 unk90[13];
    /* 0xC4 */ s32 unkC4[13];
} AudRow; /* size 0xF8 */

typedef struct {
    /* 0x0000 */ u8 unk0000[0x1C];
    /* 0x001C */ u8 unk001C[0x2004];
    /* 0x2020 */ s32 unk2020;
    /* 0x2024 */ u8 unk2024[0x3BC4 - 0x2024];
    /* 0x3BC4 */ s32 unk3BC4;
    /* 0x3BC8 */ u8 unk3BC8[0x3C90 - 0x3BC8];
    /* 0x3C90 */ s32 unk3C90[2];
    /* 0x3C98 */ s32 unk3C98[2];
    /* 0x3CA0 */ s32 unk3CA0[2];
    /* 0x3CA8 */ s32 unk3CA8[2];
    /* 0x3CB0 */ u8 unk3CB0[0x3CF0 - 0x3CB0];
    /* 0x3CF0 */ s32 unk3CF0[2];
    /* 0x3CF8 */ u8 unk3CF8[0x3D08 - 0x3CF8];
    /* 0x3D08 */ AudRow unk3D08[2];
    /* 0x3EF8 */ s32 unk3EF8;
    /* 0x3EFC */ s32 unk3EFC[6];
    /* 0x3F14 */ s32 unk3F14[16];
} AudCtx;

typedef struct {
    /* 0x000 */ s32 unk000[2][3][3][4];
} AudCounts; /* size 0x120 */

extern AudCounts D_800B0B0C;

s32 func_151F8960(void *, s32 *, s32);

s32 func_151F578C(AudCtx *arg0, s32 arg1, s32 arg2) {
    AudCounts sp70 = D_800B0B0C;
    s32 sp60[4];
    s32 sp5C = arg0->unk3C90[arg2];
    s32 *sp58 = &arg0->unk3CF0[arg2];
    s32 sp54 = arg0->unk3CA8[arg2];
    s32 sp50 = arg0->unk3CA0[arg2];
    s32 sp4C = arg0->unk3C98[arg2];
    s32 sp48;
    s32 sp44;
    s32 sp40;
    s32 sp3C;
    s32 sp38;
    s32 sp28[4];
    s32 sp24;
    s32 sp20;
    s32 sp1C;

    if (((arg0->unk3BC4 != 1) && (arg0->unk3BC4 != 3)) || (arg2 != 1)) {
        sp48 = 0;
        if (sp5C < 0x190) {
            sp60[0] = (sp5C >> 4) / 5;
            sp60[1] = (sp5C >> 4) % 5;
            sp60[2] = (sp5C % 16) >> 2;
            sp60[3] = sp5C % 4;
            *sp58 = 0;
            sp44 = 0;
        } else if ((sp5C >= 0x190) && (sp5C < 0x1F4)) {
            sp60[0] = ((sp5C - 0x190) >> 2) / 5;
            sp60[1] = ((sp5C - 0x190) >> 2) % 5;
            sp60[2] = (sp5C - 0x190) % 4;
            sp60[3] = 0;
            *sp58 = 0;
            sp44 = 1;
        } else if ((sp5C >= 0x1F4) && (sp5C < 0x200)) {
            sp60[0] = (sp5C - 0x1F4) / 3;
            sp60[1] = (sp5C - 0x1F4) % 3;
            sp60[2] = 0;
            sp60[3] = 0;
            *sp58 = 1;
            sp44 = 2;
        }
    }
    if (((arg0->unk3BC4 == 1) || (arg0->unk3BC4 == 3)) && (arg2 == 1)) {
        arg0->unk3EF8 = sp5C % 2;
        sp38 = sp5C >> 1;
        sp48 = 1;
        if (sp38 < 0xB4) {
            sp60[0] = sp38 / 0x24;
            sp60[1] = (sp38 % 0x24) / 6;
            sp60[2] = (sp38 % 0x24) % 6;
            sp60[3] = 0;
            *sp58 = 0;
            sp44 = 0;
        } else if ((sp38 >= 0xB4) && (sp38 < 0xF4)) {
            sp60[0] = ((sp38 - 0xB4) % 0x40) >> 4;
            sp60[1] = ((sp38 - 0xB4) % 0x10) >> 2;
            sp60[2] = (sp38 - 0xB4) % 4;
            sp60[3] = 0;
            *sp58 = 0;
            sp44 = 1;
        } else if ((sp38 >= 0xF4) && (sp38 < 0xFF)) {
            sp60[0] = (sp38 - 0xF4) / 3;
            sp60[1] = (sp38 - 0xF4) % 3;
            sp60[2] = 0;
            sp60[3] = 0;
            *sp58 = 0;
            sp44 = 2;
        }
    }
    if ((sp4C != 0) && (sp50 == 2)) {
        bcopy(&sp70.unk000[sp48][sp44][sp54 + 1][0], sp28, 0x10);
    } else {
        bcopy(&sp70.unk000[sp48][sp44][0][0], sp28, 0x10);
    }
    sp24 = 0;
    if ((sp4C == 0) || ((sp4C != 0) && (sp50 != 2))) {
        for (sp40 = 0; sp40 < 4; sp40++) {
            sp20 = sp60[sp40];
            sp1C = (1 << sp20) - 1;
            for (sp3C = 0; sp3C < sp28[sp40]; sp3C++) {
                arg0->unk3D08[arg2].unk00[sp24] =
                    (sp20 != 0) ? func_151F8960(arg0->unk001C, &arg0->unk2020, sp20) : 0;
                if (arg2 != 0) {
                    arg0->unk3EFC[sp24] = sp1C;
                }
                sp24++;
            }
        }
    } else {
        if (sp50 == 2) {
            if (sp54 == 0) {
                for (sp40 = 0; sp40 < 4; sp40++) {
                    sp20 = sp60[sp40];
                    sp1C = (1 << sp20) - 1;
                    for (sp3C = 0; sp3C < sp28[sp40]; sp3C += 3) {
                        arg0->unk3D08[arg2].unk5C[sp24] =
                            (sp20 != 0) ? func_151F8960(arg0->unk001C, &arg0->unk2020, sp20) : 0;
                        arg0->unk3D08[arg2].unk90[sp24] =
                            (sp20 != 0) ? func_151F8960(arg0->unk001C, &arg0->unk2020, sp20) : 0;
                        arg0->unk3D08[arg2].unkC4[sp24] =
                            (sp20 != 0) ? func_151F8960(arg0->unk001C, &arg0->unk2020, sp20) : 0;
                        if (arg2 != 0) {
                            arg0->unk3F14[sp24] = sp1C;
                        }
                        sp24++;
                    }
                }
            } else {
                sp20 = sp60[0];
                sp1C = (1 << sp20) - 1;
                for (sp3C = 0; sp3C < 6; sp3C++) {
                    arg0->unk3D08[arg2].unk00[sp24] =
                        (sp20 != 0) ? func_151F8960(arg0->unk001C, &arg0->unk2020, sp20) : 0;
                    if (arg2 != 0) {
                        arg0->unk3EFC[sp24] = sp1C;
                    }
                    sp24++;
                }
                sp28[0] -= 6;
                sp24 = 3;
                for (sp40 = 0; sp40 < 4; sp40++) {
                    sp20 = sp60[sp40];
                    sp1C = (1 << sp20) - 1;
                    for (sp3C = 0; sp3C < sp28[sp40]; sp3C += 3) {
                        arg0->unk3D08[arg2].unk5C[sp24] =
                            (sp20 != 0) ? func_151F8960(arg0->unk001C, &arg0->unk2020, sp20) : 0;
                        arg0->unk3D08[arg2].unk90[sp24] =
                            (sp20 != 0) ? func_151F8960(arg0->unk001C, &arg0->unk2020, sp20) : 0;
                        arg0->unk3D08[arg2].unkC4[sp24] =
                            (sp20 != 0) ? func_151F8960(arg0->unk001C, &arg0->unk2020, sp20) : 0;
                        if (arg2 != 0) {
                            arg0->unk3F14[sp24] = sp1C;
                        }
                        sp24++;
                    }
                }
            }
        }
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_221290/func_151F63C4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_221290/func_151F6970.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_221290/func_151F6B28.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_221290/func_151F6FD0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_221290/func_151F78B4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_221290/func_151F7F60.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_221290/func_151F8088.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_221290/func_151F85C4.s")
// void *func_151F85C4(s32 arg0, s32 arg1, s32 arg2) {
//     void *sp1C;
//
//     sp1C = (void *)0x800E1880;
//     if (sp1C == 0) {
//         return NULL;
//     }
//     sp1C->unkC = -1;
//     sp1C->unk10 = -1;
//     sp1C->unk14 = -1;
//     sp1C->unk0 = arg0;
//     sp1C->unk4 = arg1;
//     sp1C->unk8 = arg2;
//     sp1C->unk201C = 0;
//     sp1C->unk2020 = 0;
//     sp1C->unk3BA0 = 0;
//     if (func_151F8088(sp1C, 0) == 0) {
//         return NULL;
//     }
//     sp1C->unk8474 = 0;
//     bzero(sp1C + 0x6A64, 0x900);
//     return sp1C;
// }

#pragma GLOBAL_ASM("asm/nonmatchings/game_221290/func_151F86B0.s")
