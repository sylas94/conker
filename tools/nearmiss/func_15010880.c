#include <ultra64.h>

#include "functions.h"
#include "variables.h"


void func_15010780(void) {
    func_15177410(1, 255,    0, 108, 0, 0.0f, 15000, 80.0f, 77, 15, 127, 127, 127, 127, 127, 127);
    func_15177410(0, 255, 6628, 108, 0, 0.0f, 15000, 80.0f, 77, 15, 127, 127, 127, 127, 127, 127);
}

void func_15010880(void) {
    struct177 tmp;
    struct260 *temp_v0;
    s32 base;

    func_15177410(0x10, 0xE9, -0x1B5, 0x463, -0xCBF, 90.0f, 0x3A98, 36.0f, 0x4D, 0xF, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F, 0x7F);
    D_800E0934 = (s32) func_150DE32C;
    tmp.unk0 = 0;

    base = *(s32 *) &D_800D3098;
    tmp.unk4 = base + 0xEA0;
    tmp.unk8 = base + 0xED4;

    temp_v0 = func_15149130(0x12C, -1, 0x5E, -1, 0, 0, (struct37 *) 0xC, 0xFF, 1);
    if (temp_v0 != NULL) {
        memcpy((u8 *) temp_v0 + 0x28, &tmp, 0xC);
    }
    if (D_800D2E4C->unk12 & 0x40) {
        func_15149130(5, 9, -1, -1, 1, 0, NULL, 0xFF, 1);
    }
}
// NON-MATCHING: ops in wrong order
// void func_15010880(void) {
//     struct177 tmp;
//     struct37 *temp_v0;

//     func_15177410(0x10, 0xE9, -437, 0x463, -0xCBF, 90.0f, 15000, 36.0f, 0x4D, 15, 127, 127, 127, 127, 127, 127);
//     D_800E0934 = func_150DE32C;
    
//     tmp.unk0 = 0;
//     tmp.unk4 = *((s32*) &D_800D3098) + 0xEA0;
//     tmp.unk8 = *((s32*) &D_800D3098) + 0xED4;

//     temp_v0 = func_15149130(300, -1, 94, -1, 0, 0, 12, 255, 1);
//     if (temp_v0 != NULL) {
//         memcpy(&temp_v0->unk28, &tmp, 12); // memcpy
//     }
//     if ((D_800D2E4C->unk12 & 0x40) != 0) {
//         func_15149130(5, 9, -1, -1, 1, 0, 0, 255, 1);
//     }
// }

void func_150109D0(void) {
    struct179 tmp;

    tmp.unk20 = 0;  
    //D_80096430 listed as (struct180*), but used as (struct180) here;
    tmp.unk4 = *((struct180*) &D_80096430); 

    tmp.unk0 = 1;
    tmp.unk1C = fabsf(tmp.unk4.unk4 - tmp.unk4.unk10); 
    func_151ACBD4(&tmp, 0);
    func_150E8854();
}
