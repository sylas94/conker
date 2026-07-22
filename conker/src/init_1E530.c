#include <ultra64.h>

#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/init_1E530/func_1001E530.s")
#pragma GLOBAL_ASM("asm/nonmatchings/init_1E530/func_1001ED6C.s")
// _n_loadOutputBuffer ?
A8 *func_1001F28C(A20 *arg0, A_arg1 *arg1, s32 arg2, s32 arg3, A8 *arg4) {
    A8 *local54;
    s32 local50;
    s32 local4C;
    s32 local48;
    s32 local44;
    f32 local40;
    f32 local3C;
    f32 local38;
    s32 local34;
    s32 local30;
    s32 local2C;
    s16 local2A;
    A8 *local24;

    local54 = arg4;
    local48 = 0x2E0;
    local34 = 0;
    local2C = 0xB8;
    if (arg1->unk24 != 0) {
        local30 = arg1->unk4 - arg1->unk0;
        local38 = func_1001FA78((f32 (*)[4]) arg1, local2C);
        local38 = local38 / (f32) local30;
        local38 = (f32) (s32) (local38 * 32768.0f);
        local38 = local38 / 32768.0f;
        local3C = 1.0f - local38;
        local40 = arg1->unk24->unk24 + (local3C * (f32) local2C);
        local4C = (s32) local40;
        arg1->unk24->unk24 = local40 - (f32) local4C;
        local44 = arg0->unk28[arg2] + (-(arg1->unk4 - arg1->unk18)) * 2;
        local34 = (local44 & 7) >> 1;
        local54 = func_1001F5A4(arg0, arg2, local44 - (local34 * 2), local48, local4C + local34, local54);
        local50 = (s32) (local3C * 32768.0f);
        local2A = arg3 >> 8;
        local24 = local54++;
        local24->unk0 = (osVirtualToPhysical(arg1->unk24->unk14[arg2]) & 0xFFFFFF) | 0x5000000;
        local24->unk4 = ((arg1->unk24->unk28 & 3) << 30) | ((local50 & 0xFFFF) << 0xE) | (((local48 + (local34 * 2)) & 0xFFF) << 2) | (local2A & 3);
        arg1->unk24->unk28 = 0;
        arg1->unk18 = arg1->unk18 + (local4C - local2C);
    } else {
        local44 = arg0->unk28[arg2] + (-arg1->unk4) * 2;
        local54 = func_1001F5A4(arg0, arg2, local44, arg3, 0xB8, local54);
    }
    return local54;
}
// _n_loadBuffer ?
A8 *func_1001F5A4(A20 *arg0, s32 arg1, u32 arg2, s32 arg3, s32 arg4, A8 *arg5) {
    A8 *sp34;
    s32 sp30;
    s32 sp2C;
    u32 sp28;
    u32 sp24;
    A8 *sp20;
    A8 *sp1C;
    A8 *sp18;

    sp34 = arg5;
    sp24 = arg0->unk20[arg1] + (arg0->unk0 * 2);
    if (arg2 < (u32) arg0->unk20[arg1]) {
        arg2 += arg0->unk0 * 2;
    }
    sp28 = (arg4 * 2) + arg2;
    if (sp28 > sp24) {
        sp30 = (s32) (sp28 - sp24) >> 1;
        sp2C = (s32) (sp24 - arg2) >> 1;
        sp20 = sp34++;
        sp20->unk0 = (((sp2C * 2) & 0xFFF) << 0xC) | 0x4000000 | (arg3 & 0xFFF);
        sp20->unk4 = osVirtualToPhysical((void *) arg2);
        sp1C = sp34++;
        sp1C->unk0 = (((sp30 * 2) & 0xFFF) << 0xC) | 0x4000000 | ((arg3 + (sp2C * 2)) & 0xFFF);
        sp1C->unk4 = osVirtualToPhysical((void *) arg0->unk20[arg1]);
        arg0 = arg0;
    } else {
        sp18 = sp34++;
        sp18->unk0 = (((arg4 * 2) & 0xFFF) << 0xC) | 0x4000000 | (arg3 & 0xFFF);
        sp18->unk4 = osVirtualToPhysical((void *) arg2);
    }
    return sp34;
}
// void *func_1001F5A4(void *arg0, s32 arg1, u32 arg2, s32 arg3, s32 arg4, void *arg5) {
//     void *sp34;
//     s32 sp30;
//     s32 sp2C;
//     u32 sp28;
//     u32 sp24;
//     void *sp20;
//     void *sp1C;
//     void *sp18;
//     void *temp_t3;
//     void *temp_t3_2;
//     void *temp_t7;
//
//     sp34 = arg5;
//     sp24 = (arg0 + (arg1 * 4))->unk20 + (*arg0 * 2);
//     if (arg2 < (u32) (arg0 + (arg1 * 4))->unk20) {
//         arg2 = arg2 + (*arg0 * 2);
//     }
//     sp28 = (arg4 * 2) + arg2;
//     if (sp24 < sp28) {
//         sp30 = (s32) (sp28 - sp24) >> 1;
//         sp2C = (s32) (sp24 - arg2) >> 1;
//         temp_t7 = sp34;
//         sp34 = temp_t7 + 8;
//         sp20 = temp_t7;
//         *temp_t7 = (s32) ((((sp2C * 2) & 0xFFF) << 0xC) | 0x4000000 | (arg3 & 0xFFF));
//         sp20->unk4 = osVirtualToPhysical(arg2);
//         temp_t3 = sp34;
//         sp34 = temp_t3 + 8;
//         sp1C = temp_t3;
//         sp1C->unk0 = (s32) ((((sp30 * 2) & 0xFFF) << 0xC) | 0x4000000 | ((arg3 + (sp2C * 2)) & 0xFFF));
//         sp1C->unk4 = osVirtualToPhysical((arg0 + (arg1 * 4))->unk20);
//     } else {
//         temp_t3_2 = sp34;
//         sp34 = temp_t3_2 + 8;
//         sp18 = temp_t3_2;
//         *temp_t3_2 = (s32) ((((arg4 * 2) & 0xFFF) << 0xC) | 0x4000000 | (arg3 & 0xFFF));
//         sp18->unk4 = osVirtualToPhysical(arg2);
//     }
//     return sp34;
// }

A8 *func_1001F79C(A20 *arg0, s32 arg1, u32 arg2, s32 arg3, A8 *arg4) {
    A8 *sp34;
    s32 sp30;
    s32 sp2C;
    u32 sp28;
    u32 sp24;
    A8 *sp20;
    A8 *sp1C;
    A8 *sp18;

    sp34 = arg4;
    sp24 = arg0->unk20[arg1] + (arg0->unk0 * 2);
    if (arg2 < (u32) arg0->unk20[arg1]) {
        arg2 += arg0->unk0 * 2;
    }
    sp28 = arg2 + 0x170;
    if (sp28 > sp24) {
        sp30 = (s32) (sp28 - sp24) >> 1;
        sp2C = (s32) (sp24 - arg2) >> 1;
        sp20 = sp34++;
        sp20->unk0 = (((sp2C * 2) & 0xFFF) << 0xC) | 0x6000000 | (arg3 & 0xFFF);
        sp20->unk4 = osVirtualToPhysical((void *) arg2);
        sp1C = sp34++;
        sp1C->unk0 = (((sp30 * 2) & 0xFFF) << 0xC) | 0x6000000 | ((arg3 + (sp2C * 2)) & 0xFFF);
        sp1C->unk4 = osVirtualToPhysical((void *) arg0->unk20[arg1]);
        arg0 = arg0;
    } else {
        sp18 = sp34++;
        sp18->unk0 = (arg3 & 0xFFF) | 0x6170000;
        sp18->unk4 = osVirtualToPhysical((void *) arg2);
    }
    return sp34;
}
// void *func_1001F79C(void *arg0, s32 arg1, u32 arg2, s32 arg3, void *arg4) {
//     void *sp34;
//     s32 sp30;
//     s32 sp2C;
//     u32 sp28;
//     u32 sp24;
//     void *sp20;
//     void *sp1C;
//     void *sp18;
//     void *temp_t0;
//     void *temp_t7;
//     void *temp_t7_2;
//
//     sp34 = arg4;
//     sp24 = (arg0 + (arg1 * 4))->unk20 + (*arg0 * 2);
//     if (arg2 < (u32) (arg0 + (arg1 * 4))->unk20) {
//         arg2 = arg2 + (*arg0 * 2);
//     }
//     sp28 = arg2 + 0x170;
//     if (sp24 < sp28) {
//         sp30 = (s32) (sp28 - sp24) >> 1;
//         sp2C = (s32) (sp24 - arg2) >> 1;
//         temp_t0 = sp34;
//         sp34 = temp_t0 + 8;
//         sp20 = temp_t0;
//         *temp_t0 = (s32) ((((sp2C * 2) & 0xFFF) << 0xC) | 0x6000000 | (arg3 & 0xFFF));
//         sp20->unk4 = osVirtualToPhysical(arg2);
//         temp_t7 = sp34;
//         sp34 = temp_t7 + 8;
//         sp1C = temp_t7;
//         sp1C->unk0 = (s32) ((((sp30 * 2) & 0xFFF) << 0xC) | 0x6000000 | ((arg3 + (sp2C * 2)) & 0xFFF));
//         sp1C->unk4 = osVirtualToPhysical((arg0 + (arg1 * 4))->unk20);
//     } else {
//         temp_t7_2 = sp34;
//         sp34 = temp_t7_2 + 8;
//         sp18 = temp_t7_2;
//         sp18->unk0 = (s32) ((arg3 & 0xFFF) | 0x6170000);
//         sp18->unk4 = osVirtualToPhysical(arg2);
//     }
//     return sp34;
// }

A8 *func_1001F978(A55 *arg0, s32 arg1, s32 arg2, A8 *arg3) {
    A8 *sp24;
    s16 sp22;
    A8 *sp1C;
    A8 *sp18;

    sp24 = arg3;
    sp22 = arg2 >> 8;

    sp1C = sp24++;
    sp1C->unk0 = 0xB000020;
    sp1C->unk4 = osVirtualToPhysical(&arg0->unk8);

    sp18 = sp24++;
    sp18->unk0 = ((arg0->unk28 & 0xFF) << 0x10) | 0xE000000 | (arg0->unk2 & 0xFFFF);
    sp18->unk4 = (osVirtualToPhysical(arg0->unk2C[arg1]) & 0xFFFFFF) | ((sp22 & 0xFF) << 0x18);
    arg0->unk28 = 0;
    return sp24;
}
// NON-MATCHING: lots of work still to do
// struct56 *func_1001F978(struct55 *arg0, s32 arg1, s32 arg2, struct56 *arg3) {
//     struct56 *sp24;
//     s16 sp22;
//     struct56 *temp_t9;
//
//     sp24 = arg3;
//     sp22 = arg2 >> 8;
//     temp_t9 = sp24;
//     sp24 = temp_t9->unk8;
//     temp_t9->unk0 = 0xB000020;
//     temp_t9->unk4 = osVirtualToPhysical(&arg0->unk8);
//     temp_t9 = sp24;
//     sp24 = temp_t9->unk8;
//     temp_t9->unk0 = (s32) (((arg0->unk28 & 0xFF) << 0x10) | 0xE000000 | (arg0->unk2 & 0xFFFF));
//     temp_t9->unk4 = (s32) ((osVirtualToPhysical(arg0->unk2C[arg1]) & 0xFFFFFF) | ((sp22 & 0xFF) << 0x18));
//     arg0->unk28 = 0;
//     return sp24;
// }

f32 func_1001FA78(f32 arg0[4][4], s32 arg1) {
    f32 tmp;

    arg0[1][1] += arg0[1][0] * arg1;
    if (arg0[1][1] > 2.0f) {
        arg0[1][1] -= 4.0f;
    }
    else {
        arg0[1][1] = arg0[1][1]; // ???
    }

    tmp = arg0[1][1];
    tmp = tmp < 0.0f ? -tmp : tmp;
    tmp = tmp - 1.0f;

    return tmp * arg0[1][3];
}
