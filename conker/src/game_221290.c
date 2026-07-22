#include <ultra64.h>

#include "functions.h"
#include "variables.h"



#pragma GLOBAL_ASM("asm/nonmatchings/game_221290/func_151F3DE0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_221290/func_151F42E8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_221290/func_151F4F38.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_221290/func_151F578C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_221290/func_151F63C4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_221290/func_151F6970.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_221290/func_151F6B28.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_221290/func_151F6FD0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_221290/func_151F78B4.s")
s32 func_151F7F60(Struct221290 *arg0) {
    s32 n = 0x1000;
    s32 result;

    if ((arg0->unk201C + arg0->unk3F88) >= 0x1FFC) {
        bcopy(&arg0->unk1C[n], &arg0->unk1C[0], n);
        arg0->unk201C -= n;
        arg0->unk2020 -= n << 3;
    }
    result = arg0->unk4(arg0->unk0, &arg0->unk1C[arg0->unk201C], arg0->unk3F88, -1);
    if (result < arg0->unk3F88) {
        bzero(&arg0->unk1C[result], arg0->unk3F88 - result);
    }
    arg0->unk18 += arg0->unk3F88;
    arg0->unk201C += arg0->unk3F88;
    return arg0->unk201C - arg0->unk3F88;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_221290/func_151F8088.s")
Struct221290 *func_151F85C4(s32 arg0, Callback221290 arg1, s32 arg2) {
    Struct221290 *temp = &D_800E1880;

    if (temp == NULL) {
        return NULL;
    }
    temp->unkC = -1;
    temp->unk10 = -1;
    temp->unk14 = -1;
    temp->unk0 = arg0;
    temp->unk4 = arg1;
    temp->unk8 = arg2;
    temp->unk201C = 0;
    temp->unk2020 = 0;
    temp->unk3BA0 = 0;
    if (func_151F8088(temp, 0) == 0) {
        return NULL;
    }
    temp->unk8474 = 0;
    bzero(temp->unk6A64, 0x900);
    return temp;
}
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

s32 func_151F86B0(void *arg0, void **arg1, s32 *arg2) {
    Struct221290 *temp;
    s32 result2;
    u8 buf[0x100];
    s32 j;

    temp = arg0;
    temp->unk3BA0++;
    if (temp->unk3BA0 >= 6) {
        temp->unk3BA0 = 0;
    }
    if (func_151F8088(temp, temp->unk8474) == 0) {
        D_800E0E04 = 3;
        return 0;
    }
    temp->unk8474 = -1;
    result2 = temp->unk8478(temp);
    if (result2 == 0) {
        goto end;
    }
    *arg1 = (u8 *)temp + temp->unk3BA0 * 1160 + 0x2070;
    *arg2 = *(s32 *)((u8 *)temp + 0x3F8C);
    if (*(s32 *)((u8 *)temp + 0x3BC8) != 0) {
        j = 0;
        do {
            if (temp->unk4(temp->unk0, &buf[j], 1, -1) == 0) {
                break;
            }
        } while (buf[j++]);
        if (D_800E0E00 != NULL) {
            D_800E0E00(0, buf, strlen(buf) + 1);
        }
    }
end:
    return result2;
}
