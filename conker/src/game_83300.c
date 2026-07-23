#include <ultra64.h>

#include "functions.h"
#include "variables.h"


void func_15058F24(struct127 *arg0, f32, f32);
u8   func_150599C8(struct127 *arg0, u8 arg1, u16 arg2);
void func_1505A250(f32 arg0, f32 arg1, f32 arg2, f32 *arg3, f32 *arg4);
f32  func_1505A3A8(f32 arg0, void *arg1, f32 arg2, f32 arg3, u8 arg4);

u8  func_1505B9C4(void *arg0, struct127 *arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5, u8 arg6);
s32 func_1505C1E4(void *arg0, struct127 *arg1, void *arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6);
extern struct255 *D_800CC4A4;
void func_1505F188(struct127 *arg0);
extern f32 D_8009962C;
extern f32 D_80099630;
extern f32 D_800994C0;
extern f32 D_800994C4;
extern f32 D_800994C8;
extern f32 D_800994CC;
extern f32 D_800994D0;

typedef struct {
    char pad_0[0x4];
    u16 field_0x4;
    s16 field_0x6;
    f32 field_0x8;
    f32 field_0xC;
    f32 field_0x10;
    f32 field_0x14;
    f32 field_0x18;
    f32 field_0x1C;
    f32 field_0x20;
    f32 field_0x24;
    s32 field_0x28;
    s32 field_0x2C;
    s32 field_0x30;
    s32 field_0x34;
    s8 field_0x38;
    s8 field_0x39;
    char pad_0x3A[0x6];
    u8 field_0x40[1];
    u8 field_0x41;
    char pad_0x42[0x1CE];
    u8 field_0x210[1];
    u8 field_0x211;
    char pad_0x212[0x1CE];
} AnimPlaybackState;

typedef struct {
    char pad_0[0x4];
    u8 field_0x4;
    char pad_0x5[0x7F];
    u16 field_0x84;
    char pad_0x86[0x24A];
    AnimPlaybackState *field_0x2D0;
} AnimPlaybackOwner;

#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15055E50.s")

void func_15056150(struct127 *arg0) {
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f14;
    f32 temp_f16;
    f32 temp_f18;
    f32 temp_f20;
    f32 temp_f22;
    f32 temp_f2;
    s16 *temp_v1;

    if (arg0->unk2E8 != 0) {
        temp_v1 = D_800D2104[arg0->unk13F];
        temp_f2 = temp_v1[4];
        temp_f12 = temp_v1[6];
        temp_f14 = temp_v1[5];
        temp_f16 = arg0->unk2E8;
        temp_f16 = temp_f16 * 8.0f;
        temp_f18 = arg0->x_position - temp_f2;
        temp_f20 = arg0->z_position - temp_f12;
        temp_f22 = arg0->y_position - temp_f14;
        temp_f0 = sqrtf((temp_f18 * temp_f18) + (temp_f20 * temp_f20) + (temp_f22 * temp_f22) + D_80099440);
        temp_f18 *= 1.0f / temp_f0;
        temp_f20 *= 1.0f / temp_f0;
        temp_f22 *= 1.0f / temp_f0;
        if (temp_f16 < temp_f0) {
            arg0->x_position = temp_f18 * temp_f16 + temp_f2;
            arg0->z_position = temp_f20 * temp_f16 + temp_f12;
            arg0->y_position = temp_f22 * temp_f16 + temp_f14;
        }
    }
}

void func_15056258(struct127 *arg0) {
    f32 temp_f2;
    f32 temp_f4;
    f32 phi_f12;

    temp_f4 = arg0->unk11C;
    temp_f2 = arg0->unk118 - arg0->unk11C;
    arg0->unk11C = arg0->unk118;
    phi_f12 = 2.0f * (arg0->y_position - ((arg0->unk118 - 60.0f) - 170.0f));
    if (!(phi_f12 < 0.0f)) {
        if (!(fabsf(temp_f2) > 30.0f)) {
            if (phi_f12 > 300.0f) {
                phi_f12 = 300.0f;
            }
            arg0->y_position += (phi_f12 * temp_f2 * D_80099444);
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_150562FC.s")
// NON-MATCHING: 10% of the way there...
// void func_150562FC(struct127 *arg0) {
//     f32 sp70;
//     f32 sp6C;
//     f32 sp68;
//     u8 sp63;
//     s32 sp54;
//     f32 sp4C;
//     f32 temp_f0;
//     f32 temp_f12;
//     f32 temp_f14;
//
//     s32 *temp_a3;
//     // s32 temp_t1;
//     s32 temp_t1_2;
//     s32 temp_t2;
//     s32 temp_t9;
//     s32 temp_v0_6;
//     struct255 *temp_v1_2;
//     u16 temp_v0_2;
//     u16 temp_v0_3;
//     u16 temp_v0_4;
//     u16 temp_v0_5;
//     u16 temp_v0_7;
//     u16 temp_v0_8;
//     u16 temp_v1;
//     u8 temp_v0;
//     struct127 *temp_t0;
//     struct127 *temp_t0_2;
//     u8 *temp_v0_11;
//     s32 phi_a2;
//     s32 phi_t1;
//     s32 phi_t1_2;
//     s32 phi_t1_3;
//     s32 phi_a2_2;
//     f32 phi_f18;
//     s32 phi_t1_4;
//     f32 phi_f0;
//     s32 phi_t1_5;
//     s32 phi_t2;
//
//     sp63 = arg0->unk13D - 0x64;
//     sp54 = 0;
//     sp4C = 5.0f;
//     arg0->immune = (u8)0x1E;
//     temp_t0 = &D_800CC2D0[sp63];
//     arg0->unk180 = (f32) temp_t0->unk180;
//     arg0->unk1CC = (f32) arg0->y_position;
//     arg0->gravity = 4.5f;
//     arg0->y_velocity = 0.0f;
//     if ((s32) arg0->unk21C < 0x1E) {
//         arg0->unk21C += D_800BE9A0;
//     }
//     temp_v0 = arg0->id;
//     if (temp_v0 == 0x57) {
//         arg0->unk5C = 9;
//         if ((s32) arg0->unk21C >= 0xA) {
//             temp_v0_2 = temp_t0->unk84.uh;
//             sp54 = 1;
//             phi_a2 = 0xD;
//             if (temp_v0_2 == 0x114) {
//                 phi_a2 = 0x24;
//             }
//             phi_t1 = 0;
//             if (temp_v0_2 == 0x116) {
//                 phi_t1 = 1;
//             }
//             if (temp_v0_2 == 0x117) {
//                 phi_t1 = 2;
//             }
//             func_150649A0(sp63, D_800C3E78, phi_a2);
//             phi_t1_3 = phi_t1;
//             phi_a2_2 = phi_a2;
//         } else if (temp_v0 == 0x8C) {
//             arg0->unk5C = 4;
//             if ((s32) arg0->unk21C >= 0xA) {
//                 temp_v0_2 = temp_t0->unk84.uh;
//                 sp54 = 1;
//                 phi_t1_2 = 0;
//                 if (temp_v0_2 == 0x1A6) {
//                     phi_t1_2 = 1;
//                 }
//                 if (temp_v0_2 == 0x1A7) {
//                     phi_t1_2 = 2;
//                 }
//                 func_150649A0(sp63, D_800C3E78, 0xD);
//                 phi_t1_3 = phi_t1_2;
//                 phi_a2_2 = 0xD;
//             }
//         } else {
//             if ((temp_v0 == 0xA8) || (temp_v0 == 0xA9)) {
//                 arg0->unk5C = 9;
//                 temp_v0_2 = temp_t0->unk84.uh;
//                 sp54 = 1;
//                 phi_t1_3 = 0;
//                 if (temp_v0_2 == 0x1B0) {
//                     phi_t1_3 = 1;
//                 }
//                 phi_a2_2 = 0xD;
//                 if (temp_v0_2 == 0x1B1) {
//                     phi_t1_3 = 2;
//                     phi_a2_2 = 0xD;
//                 }
//             } else {
//                 phi_t1_3 = 0;
//                 phi_a2_2 = 0xD;
//                 if (temp_v0 == 0x5E) {
//                     arg0->unk5C = 9;
//                     temp_v0_2 = temp_t0->unk84.uh;
//                     sp54 = 1;
//                     sp4C = 16.0f;
//                     phi_t1_3 = 0;
//                     if (temp_v0_2 == 0x286) {
//                         phi_t1_3 = 2;
//                     }
//                     phi_a2_2 = 0xD;
//                     if (temp_v0_2 == 0x27E) {
//                         phi_t1_3 = 1;
//                         phi_a2_2 = 0xD;
//                     }
//                 }
//             }
//         }
//         temp_v0_6 = func_1505E7CC(phi_a2_2, arg0); //, phi_a2_2);
//         temp_t0_2 = &D_800CC2D0[sp63];
//         phi_t1_4 = phi_t1_3;
//         temp_t2 = temp_v0_6;
//         temp_a3 = D_800D1588[arg0->id] - 8;
//         if (temp_t0_2->interaction_state == 1) {
//             if (temp_t0_2->in_water != 0) {
//                 temp_t9 = temp_v0_6 * 3;
//                 arg0->unk5C = 4;
//                 sp54 = 1;
//                 if (((temp_a3 + (temp_t9 * 8)) + 14) != 0) { // unkE
//                     phi_t1_4 = 1;
//                 }
//             }
//         }
//         if ((s32) arg0->unk21C < 0x14) {
//             phi_f18 = (f32) (u32) arg0->unk21C / 50.0f;
//             if (D_800BE9B4 != 0) {
//                 phi_f18 = 1.0f;
//             }
//         } else {
//             phi_f18 = D_80099448;
//         }
//
//         sp70 = (f32) arg0->unk10F;
//
//         func_150599C8(arg0, 0x10, (temp_t0_2->unk7A + (arg0->unk13E << 8)) & 0xFFFF); //, temp_a3);
//         temp_t1_2 = phi_t1_4;
//         temp_v1_2 = temp_t0_2->unk1D4;
//         if (temp_v1_2 != 0) {
//             temp_f0 = (f32) ((s32) arg0->unk10C / 0x64);
//             if (temp_t0_2->interaction_state != 0x15) {
//                 temp_v0_8 = arg0->unk21C;
//                 if ((s32) temp_v0_8 >= 7) {
//                     arg0->y_position = (f32) temp_v1_2->unk240->unk1A;
//                     if ((s32) temp_v0_8 < 0xE) {
//                         // temp_f6 = (f32) temp_v0_8;
//                         temp_f0 = (temp_v0_8 / 14.0f) * temp_f0;
//                     }
//                     arg0->y_position = (f32) (arg0->y_position + temp_f0);
//                 }
//                 if (arg0->id == 0xE) {
//                     arg0->unkC4 = 0.0f;
//                 } else if (arg0->id == 0x13) {
//                     sp70 = 204.0f;
//                     arg0->unkC4 = 0.0f;
//                 }
//             }
//         }
//         phi_t1_5 = phi_t1_4;
//         phi_t2 = temp_t2;
//         if (temp_t0_2->interaction_state == 0x15) {
//             phi_t2 = func_1505E7CC(0x39, arg0);
//             arg0->unk7A = (u16) temp_t0_2->unk7A;
//             arg0->y_position = (f32) (temp_t0_2->y_position - 10.0f);
//             if ((arg0->unk28 > 100.0f) && ((s32) arg0->unk21C >= 0x15)) {
//                 phi_t1_5 = 1;
//             } else {
//                 sp4C = 0.0f;
//                 phi_t1_5 = phi_t1_4;
//             }
//             sp70 = 0.0f;
//             temp_f0 = arg0->unkC4;
//             arg0->xz_velocity = 0.0f;
//             arg0->unkC4 = (f32) (temp_f0 + ((temp_t0_2->unkC4 - temp_f0) * D_8009944C));
//         }
//         func_1505A184(D_800CC2D0[sp63].unk7A,  sp70, 0, &sp70, &sp6C, &sp68);
//         temp_t0_2 = &D_800CC2D0[sp63];
//         temp_f12 = temp_t0_2->x_position + sp70;
//
//         temp_f14 = temp_t0_2->z_position + sp6C;
//         arg0->x_position = (f32) (arg0->x_position + ((temp_f12 - arg0->x_position) * phi_f18));
//         arg0->z_position = (f32) (arg0->z_position + ((temp_f14 - arg0->z_position) * phi_f18));
//         temp_v0_11 = temp_a3 + (phi_t2 * 0x18) + (phi_t1_5 * 4);
//         func_1505E650(arg0, temp_v0_11[0xA],  temp_v0_11[0xC] / 100.0f, sp4C, 0.0f, 0.0f, 0);
//         if (sp54 != 0) {
//             arg0->unk65 = (s8) (sp63 + 1);
//             arg0->unk101 = (u8) (arg0->unk101 | 4);
//         } else {
//             arg0->unk65 = (u8)0;
//         }
//     }
// }

s32 func_1505693C(struct127 *arg0, s32 arg1) {
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f2;

    u16 *temp_v0 = (u16*)D_800D2104[(u16)arg0->unk13F];

    if (temp_v0[3] == 0) {
        return 1;
    }

    temp_f0 = temp_v0[3] * 8;
    temp_f0 = temp_f0 * temp_f0;
    temp_f2 = (s16)temp_v0[0] - D_800CC2D0[arg1].x_position;
    temp_f12 = (s16)temp_v0[2] - D_800CC2D0[arg1].z_position;

    if ((temp_f2 * temp_f2) + (temp_f12 * temp_f12) < temp_f0) {
        return 1;
    }
    return 0;
}

// PERMUTER CANDIDATE best 3463 (structural match; IDO swaps v0<->v1 for result vs row-pointer and
// keeps the row element pointer live across w rather than recomputing -> arg0 spills to s0/frame).
// typedef struct { u8 b[0xA]; } Row56A00;
// u8 func_15056A00(struct127 *arg0, u8 arg1, u8 arg2) {
//     u8 v0; u16 w;
//     v0 = 0;
//     if (((Row56A00 *) D_80099A3C)[arg2].b[7] < arg1) v0 = 5;
//     else if (((Row56A00 *) D_80099A3C)[arg2].b[2] < arg1) v0 = 2;
//     w = arg0->unk76;
//     if (((arg0->unk78 - w) & 0x8000) != 0) v0 += 3; else v0 += 4;
//     if (((Row56A00 *) D_80099A3C)[arg2].b[v0] == 0xFF) return v0;
//     arg0->unk218 = (struct216 *) ((s32) arg0->unk218 - 5);
//     arg0->unk21C = 0x4E20; arg0->unk223 = 0xD; arg0->unk44 = 0.0f;
//     arg0->unkF4 &= ~0xE; arg0->unkF4 |= 4;
//     arg0->unk78 = w; arg0->unk7A = w; arg0->unk138 = 0;
//     arg0->unk244 = ((Row56A00 *) D_80099A3C)[arg2].b[v0];
//     return v0;
// }
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15056A00.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15056B08.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505841C.s")
// NON-MATCHING: JUSTREG
// void func_1505841C(struct127 *arg0, f32 arg1) {
//     struct197 *temp_v0_2;
//     f32 temp_f0;
//     f32 temp_f1;
//     s32 idx;
//
//     temp_f0 = (((arg0->unk246 & 0x1F) << 8) + arg0->unk249) * D_80099468;
//     if ((arg0->unk246 & 0x80) == 0) {
//         if ((arg0->xz_velocity <= 1.0f) || (((arg0->unk22C & 0x10) != 0) && (arg0->unk28 == 0.0f))) {
//             temp_f0 = arg1;
//         } else {
//             // regalloc off here
//             temp_f1 = (arg0->xz_velocity * (0.5f / arg0->xz_scale));
//             temp_f0 = temp_f1 / (temp_f0 * 10.0f);
//             temp_f0 += D_8009946C;
//
//             if ((arg0->unk246 & 0x20) == 0) {
//                 temp_f0 += D_80099470;
//             }
//         }
//     }
//     if (arg0->unk223 == 0xD) {
//         temp_f0 = (arg0->unk250 & 0x7F) * D_80099474;
//     }
//     if (arg0->unk246 == 0xFF) {
//         temp_f0 = 0.0f;
//     }
//     func_1505E650(arg0, arg0->unk244, temp_f0, arg0->unk1D0, 0.0f, 0.0f, 0);
//
//     if (arg0->unk246 == 0xFF) {
//         // regalloc off here
//         idx = D_800419A0 << 4;
//         temp_f0 = D_800418B0[idx];
//         if (temp_f0 >= 0.0f) {
//             temp_v0_2 = arg0->unk2D0;
//             temp_v0_2->unk8 = (f32) ((temp_v0_2->unk18 * (32768.0f - temp_f0)) / 32768.0f);
//         }
//     }
// }

#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_150585F0.s")
// NON-MATCHING: 80% there
// void func_150585F0(struct127 *arg0) {
//     f32 temp_f0;
//     u16 phi_a2;
//
//     func_1505A3A8(arg0->unk109 * D_80099478, arg0, 1.0f, arg0->unk109 * D_80099478, 0);
//     if (arg0->unk1CC < D_8009947C) {
//         arg0->unk1CC = arg0->y_position;
//     }
//     if ((arg0->in_water != 0) && ((s32) arg0->in_water < 0xA)) {
//         arg0->gravity = 0.0f;
//         if (arg0->y_velocity < 60.0f) {
//             arg0->y_velocity *= D_80099480;
//         }
//         if (((arg0->unk118 - 60.0f) + 40.0f) < arg0->y_position) {
//             arg0->unk81 = (u8)0;
//             arg0->unk83 = (u8)0;
//             arg0->in_water = (u8)0U;
//             arg0->unkB8 = 0.0f;
//             arg0->gravity = 4.0f;
//         }
//     }
//     if ((D_800BE616 == 0) || (arg0->interaction_state != 1)) {
//         arg0->unk21C = (u16)0;
//     }
//     if (arg0->stunned != 0xFF) {
//         if (arg0->stunned != 0xFE) {
//             if ((arg0->health != 0) || (1 != arg0->interaction_state)) {
//                 arg0->stunned -= 1;
//             }
//         }
//         arg0->unk10C -= D_800CC264;
//         if ((arg0->unk28 < D_80099484) && ((arg0->unkF4 & 0x100) != 0)) {
//             arg0->unk10C = (u16)0;
//         }
//         if ((s32) arg0->unk10C <= 0) {
//             if (arg0->unk31C != 0) {
//                 arg0->unk31C->matrix_physics = (u8)0;
//             }
//             arg0->unk10C = (u16)0;
//             func_1505E874(0.0f, D_800C3E78);
//         }
//         if (arg0->stunned == 0) {
//             arg0->xz_velocity = 0.0f;
//             arg0->unk81 = (u8)0;
//             arg0->unk76 = arg0->unk78 = arg0->unk7A;
//             if (arg0->in_water != 0) {
//                 arg0->y_velocity = 0.0f;
//                 if (arg0->interaction_state == 1) {
//                     func_1506B078();
//                 }
//             } else if (arg0->interaction_state == 1) {
//                 arg0->unkF8 &= 0xFFFF7FFF;
//                 arg0->gravity = 4.0f;
//             }
//             if (arg0->unk238 != 0) {
//                 arg0->unk23A = arg0->unk238;
//             }
//         } else {
//             if ((arg0->unk10B & 2) == 0) {
//                 phi_a2 = arg0->unk76;
//                 if ((arg0->unk10B & 4) != 0) {
//                     phi_a2 ^= 0x8000;
//                 }
//                 arg0->unk80 = (u8)0xA;
//                 func_150599C8(arg0, 12, phi_a2);
//             }
//         }
//     }
// }

#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15058898.s")

void func_15058EA4(struct127 *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6) {
    if (arg1 < arg0->y_position) {
        arg0->gravity = arg2;
    } else if (arg0->y_position < arg3) {
        arg0->gravity = arg4;
    }
    if (arg5 < arg0->y_velocity) {
        arg0->y_velocity = arg5;
    } else if (arg0->y_velocity < arg6) {
        arg0->y_velocity = arg6;
    }
}

// NON-MATCHING: best 400 (PERMUTER CANDIDATE: one extra `sw a2,0x18(sp)` spill of unused arg2 +
// missing `mov.s f12,f20` arg1-copy + a handful of at/t7/v0 and f10/f4 regalloc renames.)
// void func_15058F24(struct127 *arg0, f32 arg1, f32 arg2) {
//     f32 temp_f12;
//     f32 temp_f14;
//     f32 tmp;
//     f32 temp_f16;
//
//     temp_f16 = 0.5f - arg1;
//     if (arg1 >= 0.5f) {
//         arg1 -= 0.5f;
//     }
//     temp_f14 = arg0->unk118 + 9.0f;
//     if ((arg0->y_position < temp_f14) || ((arg0->in_water < 0x64) == 0)) {
//
//         if (0) {};
//
//         if (arg0->in_water == 0) {
//             arg0->y_position = temp_f14;
//             arg0->in_water = (u8)0x64U;
//             arg0->gravity = temp_f16 * -6.0f;
//             arg0->y_velocity *= arg1;
//         } else {
//             if ((temp_f14 + 100.0f) < arg0->y_position) {
//                 arg0->in_water = (u8)0U;
//             }
//             if (temp_f16 < 0.0f) {
//                 arg0->gravity = temp_f16 * -6.0f;
//             } else {
//                 temp_f12 = arg0->y_position - ((temp_f14 + 10.0f) - (120.0f * arg1));
//                 if ((fabsf(temp_f12) < 2.0f) && (fabsf(arg0->y_velocity) < 2.0f)) {
//                     tmp = temp_f12 * D_800994A4;
//                     arg0->gravity = 1.0f;
//                     arg0->y_velocity = 0.0f;
//                     arg0->y_position -= tmp;
//                 } else {
//                     if (temp_f12 > 0.0f) {
//                         if (arg0->y_velocity > 0.0f) {
//                             arg0->gravity = temp_f16 * 6.0f;
//                             arg0->y_velocity *= 0.5f;
//                         }
//                     } else {
//                         temp_f12 = temp_f16 * 80.0f;
//                         if (arg0->y_velocity > temp_f12) {
//                             arg0->y_velocity = temp_f12;
//                         }
//                         arg0->gravity = temp_f16 * -6.0f;
//                     }
//                 }
//             }
//         }
//         temp_f12 = -100.0f * arg1;
//         if (arg0->y_velocity < temp_f12) {
//             arg0->y_velocity = temp_f12;
//         }
//     }
// }
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15058F24.s")

void func_15059140(struct127 *arg0) {
    f32 sp2C;

    sp2C = 0.5f;
    D_800CC268 = 0;
    if ((arg0->unk13D == 0) || ((s32) arg0->unk21C < 0x10)) {
        if (arg0->unk223 != 8) {
            func_15059C84(arg0);
            func_1505A770(arg0);
        }
    }
    func_1505D6F0(arg0, D_800C3E78);
    func_15055E50(arg0, arg0->unk1E4);
    if (arg0->id == 8) {
        func_15056150(arg0);
    }
    if (arg0->unk13D < 0x64) {
        func_15058898(arg0, arg0->old_y_position);
    }
    if (arg0->unkF4 & 0x40000) {
        if (((arg0->unkF4 & 0x12000) != 0) || (D_800CC268 != 0)) {
            arg0->unk21C = 0U;
        }
    }
    if (arg0->unkB0 != 0) {
        func_15058F24(arg0, arg0->unkB0 * D_800994A8, 1.0f);
    }
    if (arg0->unkF8 & 0x20000) {
        func_15056258(arg0);
    }
    if (arg0->in_water != 0) {
        func_15059444(arg0);
    }
    if (arg0->id == 0xA) {
        arg0->unk180 = D_800994AC;
    }
    if ((arg0->unkF8 & 0x180000) != 0) {
        func_150511E8(arg0);
    }
    func_1505B5F8(arg0, arg0->unk180);
    if (((arg0->unkF4 & 0x1000) != 0) && (arg0->unk28 < D_800994B0)) {
        func_15056B08(arg0);
    }
    if (arg0->unkF8 & 0x80000) {
        sp2C = D_800994B4;
    }
    func_1505A250(0, 0, sp2C, &arg0->unk164, &arg0->unk168);
    if (arg0->unkD0 != 0) {
        func_1505C7D8(arg0, D_800C3E78);
    }
    if (arg0->unk13D == 0) {
        if (D_800BE9A0 >= arg0->unk10F) {
            arg0->unk10F = 0U;
        } else {
            arg0->unk10F -= D_800BE9A0;
        }
    }
    if (arg0->unk107 != 0) {
        arg0->unk107 -= 1;
    }
    if (arg0->immune != 0xFF) {
        if (D_800BE9A0 >= arg0->immune) {
            arg0->immune = 0U;
        } else {
            arg0->immune -= D_800BE9A0;
        }
    }
}

void func_150593C4(struct127 *arg0, u16 arg1, f32 arg2, f32 arg3) {
    f32 sp2C;
    f32 sp28;
    f32 sp24;

    func_1505A184(arg1, arg2, 0, &sp2C, &sp28, &sp24);
    arg0->unk16C += (sp2C - arg0->unk16C) * arg3;
    arg0->unk170 += (sp28 - arg0->unk170) * arg3;
}

void func_15059444(struct127 *arg0) {
    s32 sp1C;
    s32 phi_v0;
    s32 tmp;

    sp1C = -1;

    switch (D_800BE9F0) {
        case 4:
            func_150593C4(arg0, 0x4000, 50.0f, 0.05999999865889549f);
            break;
        case 6:
            sp1C = func_15083E0C(28);
            break;
        case 41:
            if (func_150A29C8(D_800C3E78, 0x4028) == 0) {
                phi_v0 = 12;
            } else if (func_150A29C8(D_800C3E78, 0x400E) == 0) {
                phi_v0 = 10;
            } else if (func_150A29C8(D_800C3E78, 0x400D) == 0) {
                phi_v0 = 9;
            } else {
                phi_v0 = 6;
            }
            sp1C = func_15083E0C(phi_v0);
            // FIXME: fakematch to force regalloc
            dummy_label_858530:;
            break;
        case 43:
            sp1C = func_15083E0C(18);
            break;
        case 65:
            if (func_150A29C8(D_800C3E78, 0x401F) == 0) {
                phi_v0 = 27;
            } else {
                phi_v0 = 26;
            }
            sp1C = func_15083E0C(phi_v0);
            break;
    }

    if (sp1C != -1) {
        func_150611E8(arg0, sp1C);
    }
}

void func_1505959C(struct127 *arg0, s32 arg1) {
    struct252 *temp_v0;
    s32 *temp_v1;
    s32 phi_v1;

    arg0->unkF8 &= 0xFF7FFFFF;
    arg0->unk13D = arg1 + 100;
    arg0->unk21C = 0;
    arg0->gravity = 4.0f;
    arg0->unk25C &= ~8;

    D_800CC2D0[arg1].unk83 = 0xFF;
    D_800CC2D0[arg1].disable_run = 0xFF;
    phi_v1 = 0;
    if (arg0->id == 0x57) {
        phi_v1 = 1;
    }
    if (D_800CC2D0[arg1].id == 0x9B) {
        phi_v1 = 2;
    }
    if (arg0->id == 0x5E) {
        phi_v1 = 3;
    }
    if (arg0->id == 0x3C) {
        phi_v1 = 4;
        D_800CC2D0[arg1].unk13C = (u8)0;
        D_800CC2D0[arg1].unk76 = func_1505A630(arg0->x_position - D_800CC2D0[arg1].x_position, D_800CC2D0[arg1].z_position - arg0->z_position, 0);
    }
    if (arg0->id == 0x89) {
        phi_v1 = 5;
    }
    func_1505E650(&D_800CC2D0[arg1], D_800860C0[phi_v1], D_800860CC[phi_v1], 0.0f, 0.0f, 0.0f, 0);
    arg0->stunned = 0xFE;
    arg0->unk105 = 0;
    arg0->unk106 = func_1505E7CC(D_800860E4[phi_v1], arg0);
    arg0->unk84.uh = 0xFFFF;
    func_1505E874(D_800C3E78, arg0);
    temp_v1 = (s32*)D_800D1588[arg0->id];
    if (temp_v1 != 0) {
        temp_v0 = (struct252 *)*(temp_v1 - 2);
        if ((temp_v0 != 0) && ((temp_v0[arg0->unk106].unk15 & 2) != 0)) {
            arg0->unk7A = D_800CC2D0[arg1].unk7A;
        }
        if ((temp_v0 == 0) || ((temp_v0[arg0->unk106].unk15 & 1) == 0)) {
            arg0->unk13E = (arg0->unk7A - D_800CC2D0[arg1].unk7A) >> 8;
        } else {
            arg0->unk13E = 0;
        }
    } else {
        arg0->unk13E = (arg0->unk7A - D_800CC2D0[arg1].unk7A) >> 8;
    }
}

void func_150597FC(struct127 *arg0) {
    s32 var_a1;
    s32 mask;
    struct126 *temp_a2;
    struct127 *temp_v0;
    s32 temp_v1;

    mask = D_800CC268;
    for (var_a1 = 0; var_a1 < D_8008FD8C; var_a1++) {
        if (((1 << var_a1) & mask) && (temp_v0 = &D_800CC2D0[var_a1], (temp_v0->unk13C == 0)) && (temp_v0->disable_run == 0) && (temp_v0->interaction_state == 1) && (temp_v0->stunned == 0) && (temp_v0->unk127 != 0xFF)) {
            break;
        }
    }
    if (var_a1 != D_8008FD8C) {
        temp_v0 = &D_800CC2D0[var_a1];
        if (temp_v0->unk13C == 0) {
            temp_a2 = temp_v0->unk31C;
            if ((temp_a2->unk27 == 0) && (temp_v0->health != 0) && (arg0->unk13D == 0) && ((arg0->stunned != 0) || (arg0->unk25C & 0x1000) || (arg0->id == 0x57)) && (arg0->unk28 == 0.0f) && (temp_v0->unk28 == 0.0f) && (arg0->unk25C & 8) && (temp_a2->unk19B == 0) && ((temp_v1 = arg0->id, (temp_v1 != 0xA9)) || (*(u8 *)((u8 *)temp_v0 + 0x128) == 0)) && ((temp_v1 != 0xA8) || (*(u8 *)((u8 *)temp_v0 + 0x128) != 0))) {
                temp_v0->unk13C = D_800C3E78 + 0x64;
                temp_v0->xz_velocity = 0.0f;
                *(s16 *)((u8 *)temp_a2 + 0x18) = 0;
                func_1505959C(arg0, var_a1);
            }
        }
    }
}

u8 func_150599C8(struct127 *arg0, u8 arg1, u16 arg2) {
    s16 temp_a3;
    s16 temp_t6;
    s16 temp_t8;
    s32 temp_v0;
    s32 temp_lo;
    s16 phi_v1;

    temp_v0 = (s32) (((arg1 << 8) + arg0->unk1E8) * D_800CC264) / 0x64;
    temp_a3 = arg2 - arg0->unk7A;
    if (arg0->unk1EA != 0) {
        temp_lo = (s32) (arg0->unk1EA * D_800CC264) / 0x64;
        temp_t6 = arg0->unk1EC + temp_lo;
        temp_t8 = arg0->unk1EC - temp_lo;
        if (temp_t6 < temp_a3) {
            temp_a3 = temp_t6;
        }
        if (temp_a3 < temp_t8) {
            temp_a3 = temp_t8;
        }
    }

    phi_v1 = temp_a3;
    if (temp_a3 < 0) {
        temp_a3 = temp_a3 ^ 0xFFFF;
    }
    if (temp_a3 < temp_v0) {
        temp_v0 = temp_a3;
    }
    if ((arg0->unkF4 & 1) == 0) {
        if (arg0->unk80 != 0) {
            if (phi_v1 < 0) {
                arg0->unk7A -= temp_v0;
            } else {
                arg0->unk7A += temp_v0;
            }
        }
    }
    return temp_a3 >> 8;
}

u8 func_15059B54(struct127 *arg0, u16 arg1) {
    s16 temp_t8;
    s16 temp_t8_2;
    s16 temp_t2;
    s32 temp_lo;
    s16 phi_a2;
    s16 phi_a1;

    temp_t8 = arg0->unk78 - arg0->unk76;
    phi_a2 = temp_t8;
    if (phi_a2 < 0) {
        phi_a2 = phi_a2 ^ 0xFFFF;
    }
    if (arg0->unk1EA != 0) {
        temp_lo = (s32) (arg0->unk1EA * D_800CC264) / 0x64;
        temp_t8_2 = arg0->unk1EC + temp_lo;
        temp_t2 = arg0->unk1EC - temp_lo;
        if (temp_t8_2 < temp_t8) {
            temp_t8 = temp_t8_2;
        }
        if (temp_t8 < temp_t2) {
            temp_t8 = temp_t2;
        }
    }

    phi_a1 = temp_t8;
    if (temp_t8 < 0) {
        temp_t8 = temp_t8 ^ 0xFFFF;
    }
    if (temp_t8 < arg1) {
        arg1 = temp_t8;
    }
    if ((arg0->unkF4 & 1) == 0) {
        if (phi_a1 < 0) {
            arg0->unk76 -= arg1;
            arg0->unk1EC = -arg1;
        } else {
            arg0->unk76 += arg1;
            arg0->unk1EC = arg1;
        }
    }
    return phi_a2 >> 8;
}
// NON-MATCHING: 90% there, missing an s16 cast
// u8 func_15059B54(struct127 *arg0, u16 arg1) {
//     s16 temp_t8;
//     s16 temp_t8_2;
//     s16 temp_t2;
//     s32 temp_lo;
//     s16 phi_a2;
//
//     temp_t8 = arg0->unk78 - arg0->unk76;
//     phi_a2 = temp_t8;
//     if (phi_a2 < 0) {
//         phi_a2 = phi_a2 ^ 0xFFFF;
//     }
//     if (arg0->unk1EA != 0) {
//         temp_lo = (s32) (arg0->unk1EA * D_800CC264) / 0x64;
//         temp_t8_2 = arg0->unk1EC + temp_lo;
//         temp_t2 = arg0->unk1EC - temp_lo;
//         if (temp_t8_2 < temp_t8) {
//             temp_t8 = temp_t8_2;
//         }
//         if (temp_t8 < temp_t2) {
//             temp_t8 = temp_t2;
//         }
//     }
//
//     if (temp_t8 < 0) {
//         temp_t8 ^= 0xFFFF;
//     }
//     if (temp_t8 < arg1) {
//         arg1 = temp_t8;
//     }
//     if ((arg0->unkF4 & 1) == 0) {
//         if (temp_t8 < 0) {
//             arg0->unk76 -= arg1;
//             arg0->unk1EC = -arg1;
//         } else {
//             arg0->unk76 += arg1;
//             arg0->unk1EC = arg1;
//         }
//     }
//     return phi_a2 >> 8;
// }

#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15059C84.s")
void func_1505A184(u16 arg0, f32 arg1, f32 arg2, f32 *arg3, f32 *arg4, f32 *arg5) {
    f32 s2;
    union { f32 f; f64 d; } ang2;
    f32 c2;

    arg1 = arg1 * 0.5f;
    arg2 = arg2 * D_800994B8;
    *arg5 = func_150AD78C(arg2) * -arg1;
    arg1 = func_150AD780(arg2) * arg1;
    ang2.f = (f32)arg0 * D_800994BC;
    s2 = func_150AD780(ang2.f);
    c2 = func_150AD78C(ang2.f);
    *arg3 = s2 * arg1;
    *arg4 = -c2 * arg1;
}
void func_1505A250(f32 arg0, f32 arg1, f32 arg2, f32 *arg3, f32 *arg4) {
    f32 dx = arg0 - *arg3, dy = arg1 - *arg4, mag, sx, sy;
    if (dx == 0.0f) { if (dy == 0.0f) return; }
    mag = sqrtf((dx * dx) + (dy * dy));
    arg2 *= D_800D1550[0];
    sx = fabsf((dx / mag) * arg2);
    sy = fabsf((dy / mag) * arg2);
    if (0.0f <= dx) { *arg3 = *arg3 + sx; if (arg0 < *arg3) *arg3 = arg0; }
    else            { *arg3 = *arg3 - sx; if (*arg3 < arg0) *arg3 = arg0; }
    if (0.0f <= dy) { *arg4 = *arg4 + sy; if (arg1 < *arg4) *arg4 = arg1; }
    else            { *arg4 = *arg4 - sy; if (*arg4 < arg1) *arg4 = arg1; }
}


// PERMUTER CANDIDATE best 3576 (control flow BYTE-PERFECT; entire diff is a systematic FP-register
// rename: target promotes aa->callee-saved $f20 (+ frame to save it) & bb->$f14 via mtc1 up front,
// but IDO keeps this leaf's aa/bb in temps $f2/$f0 with an arg-home spill. Copy-param-to-local and
// scale-hoist tricks did not force the f20 promotion. Reconstruction below is logically exact.)
// f32 func_1505A3A8(f32 arg0, void *arg1, f32 arg2, f32 arg3, u8 arg4) {
//     struct127 *obj = (struct127 *)arg1;
//     f32 aa = arg2 * D_800D1550[0];
//     f32 bb = arg3 * D_800D1550[0];
//     f32 vel;
//     if (D_800CC27C != 0) {
//         if (obj->unk28 < 5.0f) {
//             if (obj->interaction_state != 0x1E) aa = 0.0f;
//         }
//     }
//     if (obj->interaction_state == 1) {
//         if (obj->in_water != 0) { aa = 2.0f; bb = bb * D_800994C0; }
//         if (obj->unkA8 != 0) bb = bb * 0.25f;
//         if (obj->unk81 != 0) {
//             if (obj->unk81 & 0x40) {
//                 if (obj->unk81 & 0x20) bb = 0.0f; else bb = D_800994C4;
//             } else {
//                 bb = bb * D_800994C8;
//                 if (arg4 >= 0x2E) aa = aa * 0.5f;
//                 if (arg4 >= 0x5B) arg0 = arg0 * 0.5f;
//             }
//         }
//         if (obj->unkAE != 0) bb = bb * D_800994CC;
//     }
//     if (arg0 < 0.0f) {
//         vel = obj->xz_velocity;
//         if (0.0f < vel) bb = bb + aa; else bb = aa;
//     } else {
//         vel = obj->xz_velocity;
//         if (vel < 0.0f) aa = aa + bb;
//     }
//     if (arg0 < vel) {
//         obj->xz_velocity = vel - bb;
//         if (obj->xz_velocity < arg0) obj->xz_velocity = arg0;
//     } else {
//         if ((arg0 - 1.0f) < vel) aa = aa * D_800994D0;
//         obj->xz_velocity = vel + aa;
//         if (arg0 < obj->xz_velocity) obj->xz_velocity = arg0;
//     }
// }
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505A3A8.s")

f32 func_1505A5CC(struct49 *arg0) {
    f32 x, y;
    f32 ret;

    // regalloc nonsense
    ret = arg0->unk2;
    x = ret;
    y = arg0->unk3;

    x = sqrtf(x*x + y*y) * D_800994D4;
    ret = x;

    if (ret > 35.0f) {
        ret = 35.0f;
    }

    return ret;
}

u16 func_1505A630(f32 arg0, f32 arg1, s32 arg2) {
    return ((u16) (u32) (func_150484A0(-arg0, arg1) * D_800994D8)) + 16384;
}

f32 func_1505A6F8(struct127 *arg0, struct127 *arg1) {
    f32 x, z;

    x = arg0->x_position - arg1->x_position;
    x *= x;
    z = arg0->z_position - arg1->z_position;
    z *= z;
    return sqrtf(x + z);
}

// distance between two objects?
f32 func_1505A72C(struct127 *arg0, struct127 *arg1) {
    f32 x, y, z;

    x = arg0->x_position - arg1->x_position;
    x *= x;
    z = arg0->z_position - arg1->z_position;
    z *= z;
    y = arg0->y_position - arg1->y_position;
    y *= y;
    return sqrtf(x + z + y);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505A770.s")
// a big one, but could be ok
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505A9AC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505B5F8.s")
// void func_1505B5F8(struct127 *arg0, f32 arg1) {
//     f32 tmp;
//     u8 temp_v0_2;
//
//     if ((arg0->unkF8 & 0x8000) == 0) {
//         if (arg0->unk252 != 0) {
//             if ((arg0->unk253 * 8) < (arg0->unk1CC - arg0->y_position)) {
//                 if (arg0->stunned == 0) {
//                     arg0->stunned = (u8)0xFEU;
//                     arg0->unk105 = (u8)0;
//                     arg0->unk106 = func_1505E7CC(arg0->unk252, arg0);
//                     arg0->unk84.uh = (u16)0xFF;
//                     func_1505E874(D_800C3E78, arg0);
//                     arg0->y_position = (f32) arg0->old_y_position;
//                 }
//             }
//         }
//         arg0->unk28 = arg0->y_position - arg1;
//         if (arg0->y_position <= arg1) {
//             arg0->unkF4 |= 0x8000;
//             temp_v0_2 = D_800B0DF0->unk13;
//             if (temp_v0_2 != 0) {
//                 if (arg0->unk28 != 0.0f) {
//                     func_15174690(D_800C3E78, 0, 0x1000 / (s32) temp_v0_2, 0, 0x199, 4, 0xAA, 0xFF, 0); // 0.0f, arg1,
//                 }
//             }
//             arg0->y_position = arg1;
//             tmp = arg0->unk28;
//             arg0->unk28 = 0.0f;
//             if ((arg0->stunned != 0) || ((arg0->unkF8 << 0xF) >= 0)) {
//                 if (arg0->interaction_state == 1) {
//                     if (arg0->y_velocity < -6.0f) {
//                         arg0->y_velocity = -6.0f;
//                     }
//                 } else {
//                     if ((arg0->unk1CC - arg0->y_position) > 450.0f) {
//                         if (arg0->health > 0) {
//                             if ((arg0->unk144 != 0) && ((arg0->unk144->unkE & 0x80) == 0)) {
//                                 arg0->health = (u8) (arg0->health - 1);
//                             }
//                         }
//                     }
//                     arg0->unk1CC = arg1;
//                     if ((arg0->stunned == 0) && (arg0->gravity > 0.5f)) {
//                         if (((arg0->unkF8 & 0x800) != 0) && (tmp != 0.0f) && ((arg0->y_velocity < (-4.0f * arg0->gravity * D_800D1550[0])))) {
//                             arg0->y_velocity = ((0.0f - arg0->y_velocity) * ((f32) arg0->unk2CB * D_8009950C));
//                             if ((arg0->unk2CC != 0) && (arg0->y_velocity > 5.0f)) {
//                                 D_800D1580 = arg0->unk2CC;
//                                 func_1506E5FC();
//                             }
//                         } else if (arg0->interaction_state != 7) {
//                             arg0->y_velocity = -4.0f * D_800D1550[0];
//                         }
//                     } else {
//                         if ((arg0->unkF4 & 0x80) != 0) {
//                             arg0->y_velocity = -4.0f;
//                         } else if ((tmp == 0.0f) || (((-1.5f * arg0->gravity * D_800D1550[0]) < arg0->y_velocity))) {
//                             arg0->y_velocity = 0.0f;
//                         } else {
//                             arg0->y_velocity = (0.0f - arg0->y_velocity) * ((f32) arg0->unk2CB * D_80099510);
//                         }
//                         arg0->xz_velocity *= D_80099514;
//                     }
//                 }
//             }
//         }
//     }
// }

#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505B9C4.s")

s16 func_1505C140(struct127 *arg0, struct127 *arg1) {
    s16 ret = func_1505A630(arg0->x_position - arg1->x_position, arg1->z_position - arg0->z_position, 0);
    ret -= arg1->unk7A;

    if (ret < 0) {
        ret = -ret;
    }
    return ret;
}

struct252 *func_1505C1A4(struct127 *arg0) {
    s32 *temp_v1;
    struct252 *ret;

    if ((arg0->id != 0xFF) && (D_800D1588[arg0->id] != 0)) {
        temp_v1 = (s32*)D_800D1588[arg0->id] - 3;
        ret = *temp_v1;
    } else {
        ret = &D_8009A9F8;
    }
    return ret;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505C1E4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505C7D8.s")

s32 func_1505D024(struct127 *arg0, s32 arg1, u16 arg2, s32 arg3) {
    s32 pad;
    s32 ret;
    s32 temp_lo;
    struct252 *sp30;

    sp30 = &D_8009A9F8;
    if (D_800C35EA == 1) {
        return 0;
    }
    if ((arg1 & 0x20000) && (arg0->immune != 0)) {
        return 0;
    }
    if ((arg1 & 0x40000) && (arg0->stunned != 0)) {
        return 0;
    }
    if (((arg1 << 0xB) >= 0) && (arg0->health == 0)) {
        return 0;
    }
    if (arg3 == -1) {
        D_800D1340 = (u8)0;
    } else {
        D_800D1340 = arg3 + 1;
    }
    D_800D1292 = arg2;
    D_800D1296 = arg2;
    if (arg1 & 0x10000) {
        sp30 = func_1505C1A4(D_800D154C);
    }

    temp_lo = arg0 - D_800CC2D0;
    ret = 1 << temp_lo;
    if (arg1 & 0x80000) {
        ret = func_1505C1E4(&D_800D121C, arg0, sp30, arg1 & 0xFF, temp_lo + 1, 0, 7);
    } else {
        func_1505B9C4(&D_800D121C, arg0, (s32)sp30, (s32)sp30, arg1 & 0xFF, temp_lo + 1, 7);
    }
    return ret;
}

void func_1505D1C4(f32 arg0, f32 arg1, f32 arg2, s32 arg3, s32 arg4, u16 arg5, s32 arg6, s32 arg7) {
    s32 pad;
    s32 tmp;

    tmp = D_800C3E78;
    func_1505F188(&D_800D121C);
    D_800D1230 = arg0;
    D_800D1234 = arg1;
    D_800D1238 = arg2;
    D_800D1340 = arg4 + 1;
    D_800D1359 = arg6;
    D_800D1292 = arg5;
    D_800C3E78 = 25;
    D_800D1510 = arg7;
    D_800D1330 = 100.0f;
    D_800D12EC = (arg3 & 0xFFFF) + 1;
    D_800D1368 = 0.5f;
    D_800D136C = 0.5f;
    func_1505C7D8(&D_800D121C, 25);
    D_800C3E78 = tmp;
}

void func_1505D2B8(struct127 *arg0, u8 arg1) {
    struct253 *temp_v0;

    temp_v0 = &D_8009A6D8[arg1];
    arg0->y_velocity = temp_v0->unk18;
    arg0->xz_velocity = temp_v0->unk14;
    arg0->gravity = temp_v0->unk1C;
    arg0->stunned = 0xFE;
    arg0->unk105 = 0;
    arg0->unk106 = func_1505E7CC(arg0->unk10E & 0x7F, arg0);
    arg0->unk10E = 0xFF;
    func_1505E874(D_800C3E78, arg0);
}

f32 func_1505D34C(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 *arg4) {
    f32 sp24;
    s32 pad;
    f32 temp_f0;
    f32 temp_f12;

    if (arg3 != 1.0f) {
        arg1 = arg1 * arg3;
        arg2 = arg2 * arg3;
    }
    temp_f12 = (arg0 - 90.0f) * D_80099520; // 0.01745329238474369f;
    sp24 = func_150AD780(temp_f12);
    temp_f0 = func_150AD78C(temp_f12);
    *arg4 = (-arg1 * temp_f0) + (arg2 * sp24);
    return (arg1 * sp24) + arg2 * temp_f0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505D408.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505D5D0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505D6F0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505DADC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505DDA8.s")
f32 func_1505DF10(struct127 *arg0, u8 arg1, s16 *arg2, f32 *arg3, f32 *arg4) {
    struct127 *ptr;
    f32 temp_f12;
    f32 temp_f2;
    f32 temp_f14;

    ptr = &D_800CC2D0[arg1];
    temp_f12 = ptr->x_position - arg0->x_position;
    temp_f2 = arg0->y_position - ptr->y_position;
    temp_f14 = arg0->z_position - ptr->z_position;
    *arg4 = temp_f2;
    *arg2 = func_1505A630(temp_f12, temp_f14, 0);
    temp_f12 = temp_f12 * temp_f12;
    temp_f2 = temp_f2 * temp_f2;
    temp_f14 = temp_f14 * temp_f14;
    *arg3 = temp_f12 + temp_f14;
    return (temp_f12 + temp_f2) + temp_f14;
}
extern u16 D_800C4ED0[];

void func_1505DFDC(AnimPlaybackOwner *arg0) {
    s32 sp1C;
    AnimPlaybackState *temp;
    u16 *p;

    arg0->field_0x84 = 0xFFFF;
    temp = arg0->field_0x2D0;
    if (temp != NULL) {
        sp1C = arg0->field_0x4;
        temp->field_0x28 = 0;
        bzero(temp->field_0x40, 0x3A0);
        p = &D_800C4ED0[sp1C];
        temp->field_0x41 = *p + 1;
        temp->field_0x211 = *p + 1;
        temp->field_0x30 = 0;
        temp->field_0x34 = 0;
    }
}

void func_1505E060(AnimPlaybackState *arg0) {
    arg0->field_0x6 = arg0->field_0x4;
    arg0->field_0xC = arg0->field_0x8;
    arg0->field_0x14 = arg0->field_0x10;
    arg0->field_0x24 = arg0->field_0x20;
    arg0->field_0x1C = arg0->field_0x18;
    arg0->field_0x39 = arg0->field_0x38;
    arg0->field_0x2C = arg0->field_0x28;
    bcopy(arg0->field_0x40, arg0->field_0x210, 0x1D0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505E0C4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505E650.s")
u32 func_1505E7CC(s32 arg0, struct127 *arg1) {
    s32 idx;
    s32 *ptr;
    u32 count;
    u8 *base;
    u8 *entry;
    u32 i;

    idx = arg1->id;
    if (idx == 0xFF) {
        return 0;
    }
    ptr = (s32 *)D_800D1588[idx];
    if (ptr == NULL) {
        return 0;
    }
    count = ptr[-1];
    if (count == 0) {
        return 0;
    }
    count = count / 0x18;
    base = (u8 *)ptr[-2];
    if (base == NULL) {
        return 0;
    }
    if (count != 0) {
        i = 0;
        entry = base;
        do {
            if (arg0 == entry[0]) {
                return i;
            }
            i++;
            entry += 0x18;
        } while (i < count);
    }
    return 0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505E874.s")
struct127 *func_1505ED34(void) {
    s32 i;
    struct127 *ptr;

    for (i = 0, ptr = D_800CC2D0; (i < 25) && (ptr->interaction_state != 0); i++, ptr++) {
    }

    if (i == 25) {
        ptr = D_800CC2D0;
        i = 0;
        if ((0x27 != ptr->interaction_state) || (D_800CC4A4 != NULL)) {
            do {
                i++;
                ptr++;
            } while ((i < 25) && ((0x27 != ptr->interaction_state) || (ptr->unk1D4 != NULL)));
        }

        if (i != 25) {
            if (ptr->interaction_state != 0) {
                func_15060F28(ptr, 0);
            }
        }
    }

    if (i == 25) {
        for (ptr = D_800CC2D0, i = 0; (i < 25) && (0x27 != ptr->interaction_state); i++, ptr++) {
        }

        if (i != 25) {
            if (ptr->interaction_state != 0) {
                func_15060F28(ptr, 0);
            }
        }
    }

    if (i == 25) {
        if (ptr->interaction_state != 0) {
            func_15060F28(ptr, 0);
        }
    }

    func_1505F188(ptr);
    return ptr;
}

struct127 *func_1505EEB0(s32 state, s32 *arg1) {
    struct127 *ptr;
    s32 i;

    for (ptr = D_800CC2D0, i = 0; (i < 25) && (state != ptr->interaction_state); i++, ptr++) {
    }

    *arg1 = i;
    return ptr;
}
// I HATE LOOPS.
// struct127 *func_1505EEB0(s32 state, s32 *arg1) {
//     struct127 *tmp = D_800CC2D0;
//     s32 i = 0;
//
//     if (state != tmp->interaction_state) {
//         for (i = 0; i < 25; i++) {
//             tmp = &D_800CC2D0[i];
//             if (state == tmp->interaction_state)
//                 break;
//         }
//     }
//
//     *arg1 = i;
//     return tmp;
// }

// PERMUTER/HARD CANDIDATE best 745 (natural loop) — needs split symbols D_800CC40F (elem0 unk13F)
// and D_800CC5FC (loop base = elem1) which only a hand-peel emits, but hand-peel (best 1205) breaks
// IDO's counter-merge/folded-read peel structure. EFD0 (unk127/D_800CC3F7) & F0AC (id/D_800CC2D4) identical shape.
// struct127 *func_1505EEF4(s32 arg0) {
//     struct127 *ptr; s32 i;
//     for (ptr = D_800CC2D0, i = 0; i < 25; i++, ptr++) {
//         if ((ptr->interaction_state != 0) && (ptr->unk13F == arg0)) return ptr;
//     }
//     return NULL;
// }
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505EEF4.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505EFD0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505F0AC.s")
// PERMUTER CANDIDATE best 835 (body byte-identical; blocker is the D_8009962C load position
// vs the struct-clear loop, coupled to an f0<->f2 swap for 1.0f vs D_8009962C. decl-init keeps
// correct f0/f2 regs but hoists the load above the loop + reorders the li/D_80099630 block.)
// void func_1505F188(struct127 *arg0) {
//     s32 *p; f32 v = D_8009962C;
//     for (p = (s32 *)arg0; p < (s32 *)((u8 *)arg0 + 0x32C); p++) *p = 0;
//     ((u8 *)arg0)[0x2FD] = 2;
//     *(s16 *)&arg0->unk38 = -0x2710;
//     arg0->xz_scale = 1.0f; arg0->y_scale = 1.0f;
//     arg0->unk118 = v; arg0->unk180 = v;
//     ((u8 *)arg0)[0x1DC] = 0xFF; arg0->unk127 = 0xFF; arg0->unk84.uh = 0xFFFF; arg0->unk13F = 0xFF;
//     *(u8 **)((u8 *)arg0 + 0x2C4) = &arg0->id;
//     ((u8 *)arg0)[0x2C8] = 1; arg0->unk2C9 = 1; arg0->id = 0xFF; arg0->unk2CB = 0x32;
//     arg0->unk48 = 1.0f; arg0->gravity = D_80099630;
//     arg0->unk6E = ((u32) func_150ADA20() % 0x32) + 0x32;
//     func_150615DC(arg0);
//     ((u8 *)arg0)[0x1DD] = 0xFF; ((u8 *)arg0)[0x1DE] = 0xFF; ((u8 *)arg0)[0x1DF] = 0xFF;
//     *(s16 *)((u8 *)arg0 + 0x18C) = 0; *(s16 *)((u8 *)arg0 + 0x18E) = 0;
//     *(s16 *)((u8 *)arg0 + 0x190) = 0; *(s16 *)((u8 *)arg0 + 0x192) = 0;
//     *(s16 *)((u8 *)arg0 + 0x194) = 0; *(s16 *)((u8 *)arg0 + 0x196) = 0xA;
//     *(s16 *)((u8 *)arg0 + 0x198) = 0xA; *(s16 *)((u8 *)arg0 + 0x19A) = 0;
//     *(s16 *)((u8 *)arg0 + 0x19C) = 0;
// }
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505F188.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1505F298.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1506045C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15060778.s")
void func_15060A30(s32 arg0, struct127 *arg1) {
    if (arg1->camera == NULL) {
        func_10010344(arg0, arg1, 0x6D60, 0x1F4, 0x9C4);
    } else {
        func_15060778(arg0, arg1, 0x5DC0, 0, 0x1F4, 0x9C4, 1);
    }
}
void func_15060A9C(s32 arg0, struct127 *arg1) {
    if (arg1->camera == NULL) {
        func_10010630(arg0, arg1, 0x5DC0, 0x1F4, 0x9C4);
    } else {
        func_15060778(arg0, arg1, 0x5DC0, 0, 0x1F4, 0x9C4, 0);
    }
}

void func_15060B04(s32 arg0, struct127 *arg1, s32 arg2) {
    if (arg1->camera == NULL) {
        func_10010630(arg0, arg1, arg2, 500, 2500);
    } else {
        func_15060778(arg0, arg1, arg2, 0, 500, 2500, 0);
    }
}

void func_15060B70(s32 arg0, void *arg1) {
    func_10010154(arg0, arg1, 0x6D60, 0x1F4, 0x9C4);
}

s32 func_15060BA4(struct127 *arg0, s32 arg1) {
    if (arg0->health == 6) {
        return 0;
    }
    arg0->health += arg1;
    if (arg0->health >= 7) {
        arg0->health = 6;
    }
    return 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15060BE0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15060D54.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15060F28.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_150611E8.s")

// TODO: is this really struct127?
void func_150615DC(struct127 *arg0) {
    arg0->unk7 = 0xFF;
    arg0->unk8 = 0xFF;
    arg0->unk9 = 0;
    arg0->unkA = 0;
    arg0->unkE.ub[1] = 0;
    arg0->unkB = arg0->unkC = arg0->unkD = arg0->unkE.ub[0] = 0xFF;
}

// PERMUTER CANDIDATE best 105 (structure BYTE-IDENTICAL; two keys already applied: `s32 b=arg4`
// pins arg4->v0 [1705->130], and reusing dead `arg2` as the store value pins sv->a2 [130->105]).
// Remaining diff is ONE coupled register swap in the 8/9 handler + L690: (1<<b) lands in a1 & the
// unkE reload in v1, but the target uses v1 & a1 respectively; PLUS one IDO scheduler-slot fill (the
// <8-tail `lui %hi(D_800DBFF4)` is hoisted into the lbu-0xA load-delay slot). Both are IDO free-list/
// scheduler internals -- resisted operand-order, statement-split, explicit-mask-local, and every
// arg1-reuse-for-unkE variant (each regressed to 500-1440 by conflicting with (1<<b)'s a1). Exact:
// void func_1506160C(struct127 *arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4) {
//     if (arg1 >= 8) {
//         s32 b = arg4;
//         if (arg1 != 0xA) {
//             if (arg1 == 8) { arg0->unkE.ub[1] |= (1 << b); arg2 = 0; }
//             else { arg0->unkE.ub[1] &= ~(1 << b); arg2 = 0xFF; }
//             if (arg0->unkE.ub[1] & ((1 << b) << 4)) ((u8 *)arg0)[0xB + b] = arg2;
//             arg0->unkE.ub[1] &= ~((1 << b) << 4);
//         } else { arg0->unkE.ub[1] |= ((1 << b) << 4); arg2 = 0; }
//         if ((((u8 *)arg0)[0x2FD] != 0) || (D_800DBFF4[b] != 0)) ((u8 *)arg0)[0xB + b] = arg2;
//         return;
//     }
//     if (arg1 < arg0->unkA) return;
//     if (arg1 == 4)      { arg0->unkA = arg1; arg0->unk7 = 0; arg0->unk8 = 0xFF; arg0->unk9 = 0x20; }
//     else if (arg1 == 5) { arg0->unkA = arg1; arg0->unk8 = 0; arg0->unk9 = 0x20; }
//     else if (arg1 == 6) { arg0->unkA = arg1; arg0->unk8 = 0; arg0->unk9 = 8; }
//     else if (arg1 == 2) { arg0->unkA = arg1; arg0->unk8 = arg2; arg0->unk9 = arg3; }
//     else if (arg1 == 1) { arg0->unkA = 0; arg0->unk7 = arg2; arg0->unk8 = arg2; }
//     if (*(s32 *)D_800DBFF4 != 0) arg0->unk7 = arg0->unk8;
// }
// permuter NO ZERO (best 105, structure byte-identical; residual = coupled 2-reg swap
// [a1/v1 for (1<<b) vs unkE reload] + 1 scheduler slot). Header fix (arg1/arg4->u8) took it
// from 11818->105. Reconstruction preserved in the comment block above.
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_1506160C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_150617BC.s")
// ???
s32 func_1506196C(u8 *arg0, s32 arg1) {
    s32 temp_v1 = arg0[7] * (arg0 + arg1)[0xB];
    if (temp_v1 == 0xFE01) {
        temp_v1 = 0xFF;
    } else {
        temp_v1 = temp_v1 >> 8;
    }
    return temp_v1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_150619A8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15061B4C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_150623F4.s")
// PERMUTER CANDIDATE best 1662 (JUSTREG: instructions match, saved-register numbering off;
// target allocates arg0->s1,arg1->s2,base->s3 but IDO gives base->s1)
// void func_150626EC(struct127 *arg0, s32 arg1) {
//     struct127 *ptr;
//     for (ptr = D_800CC2D0; ptr != (struct127 *) &D_800D121C; ptr++) {
//         if ((ptr->interaction_state != 0) &&
//             (((arg0 - D_800CC2D0) + 1) == ptr->unk65) &&
//             (ptr->unk127 == 0xFF)) {
//             func_15060F28(ptr, arg1);
//         }
//     }
// }
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_150626EC.s")

void func_150627D4(struct127 *arg0) {
    arg0->unk2FB = 0;
    func_1503B840(arg0);
    func_15039CC8(arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15062800.s")

void func_15062AC4(struct127 *arg0) {
    if (arg0->unkE6 && arg0->unkE4) {
        f32 tmp = arg0->unkE4;
        arg0->unkEC = tmp / arg0->unkE6;
        arg0->unkF0 = arg0->unkE6 / tmp;
    } else {
        arg0->unkF0 = arg0->unkEC = 0.0f;
    }
}

void func_15062B1C(struct127 *arg0, f32 arg1) {
    arg0->unkE4 = arg0->xz_scale * arg1;
    func_15062AC4(arg0);
}

void func_15062B50(struct127 *arg0, f32 arg1) {
    arg0->unkE6 = arg0->y_scale * arg1;
    func_15062AC4(arg0);
}

void func_15062B84(struct127 *arg0) {
    if (arg0->unkD4 && arg0->unkD2) {
        f32 tmp = arg0->unkD2;
        arg0->unkDC = tmp / arg0->unkD4;
        arg0->unkE0 = arg0->unkD4 / tmp;
    } else {
        arg0->unkDC = 0.0f;
        arg0->unkE0 = 0.0f;
    }
}

void func_15062BDC(struct127 *arg0, f32 arg1, f32 arg2) {
    struct124 *temp_v0;

    arg0->xz_scale = arg1;
    arg0->y_scale = arg2;
    if (arg0->id != 255) {
        temp_v0 = D_800D1C90[arg0->id];
        arg0->unkD2 = (s32) (temp_v0->unk20 * arg0->xz_scale);
        arg0->unkD4 = (s32) (temp_v0->unk22 * arg0->y_scale);
        arg0->unkD6 = (s32) (temp_v0->unk24 * arg0->y_scale);
        arg0->unkE4 = (s32) (temp_v0->unk1A * arg0->xz_scale);
        arg0->unkE6 = (s32) (temp_v0->unk1C * arg0->y_scale);
        arg0->unkE8 = (s32) (temp_v0->unk1E * arg0->y_scale);
        func_15062AC4(arg0);
        func_15062B84(arg0);
    }
}

// PERMUTER CANDIDATE best 180 (EVERY instruction matches; remaining diff is a coherent 5-register
// cycle a0->a1->a3->v1->t0 rooted in the base pointer landing in a0 vs the target's a1 — an IDO
// free-list coin-flip. Hand-fixes: *(s32*)&arg1 homes arg1 at prologue; explicit `base` local; the
// nested default-then-adjust wrap shape; flag=arg5. Progression 3331->900->395->360->180.)
// typedef struct { s32 unk0; s32 unk4; } Entry62D10;
// extern Entry62D10 **D_800C4488[];
// void func_15062D10(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
//     Entry62D10 *base, *entry; s32 packed, modX, modY, newX, newY, tmp, flag;
//     if ((&D_800D19A0)[arg0] == 0) return;
//     flag = arg5;
//     base = D_800C4488[arg0][arg4];
//     entry = &base[*(s32 *)&arg1];
//     packed = entry->unk4;
//     modX = ((packed >> 12) & 0xFFF) + 2;
//     modY = (packed & 0xFFF) + 2;
//     packed = entry->unk0;
//     if (flag != 0) newX = arg2 & 0xFFF;
//     else { tmp = ((packed >> 12) & 0xFFF) + arg2; newX = tmp;
//            if (modX < tmp) newX = tmp - modX; else if (tmp < 0) newX = tmp + modX; }
//     if (flag != 0) newY = arg3 & 0xFFF;
//     else { tmp = (packed & 0xFFF) + arg3; newY = tmp;
//            if (modY < tmp) newY = tmp - modY; else if (tmp < 0) newY = tmp + modY; }
//     entry->unk0 = (packed & 0xFF000000) | (newY & 0xFFF) | ((newX & 0xFFF) << 12);
// }
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15062D10.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15062E24.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15062FC0.s")
void func_15194FF4(struct127 *, struct127 *, s32);

void func_15063168(struct127 *arg0) {
    s32 i;
    s32 self;
    struct127 *obj;

    self = ((s32)arg0 - (s32)D_800CC2D0) / (s32)sizeof(struct127);
    for (i = 0; i < D_8008FD8C; i++) {
        if (i == self) {
            continue;
        }
        if (((1 << i) & D_800CC268) == 0) {
            continue;
        }
        obj = (struct127 *)D_800CC2D0[i].unk31C;
        if (obj == 0) {
            continue;
        }
        if (((u8 *)obj)[0x1AC] != 0) {
            continue;
        }
        func_15194FF4(arg0, &D_800CC2D0[i], 1);
    }
}

// PERMUTER CANDIDATE best 1960 (structural match: all field save/restore + 2 calls correct;
// target 8-aligns idx/cam spill slots leaving frame gaps at 0x28/0x4c and schedules a1=0 late).
// void func_15082A44(struct129 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
// void func_15063254(struct127 *arg0, s32 arg1, s32 arg2, f32 arg3) {
//     struct129 *obj; s32 idx; struct108 *cam;
//     f32 x, y, z, b8, u40, uC4; s32 rot;
//     idx = arg0->unk13F;
//     obj = arg0->unk144;
//     obj->unk4 = arg1; obj->unk3 = arg2; obj->unk20 = arg3; obj->unk24 = arg3; obj->unk2 = 0;
//     cam = arg0->camera;
//     z = arg0->z_position; x = arg0->x_position; y = arg0->y_position;
//     b8 = arg0->unkB8; u40 = arg0->unk40; uC4 = arg0->unkC4; rot = arg0->unk76;
//     func_15060F28(arg0, 0);
//     func_15082A44(obj, idx, 0, 0, (arg0 - D_800CC2D0) + 1);
//     arg0->x_position = x; arg0->y_position = y; arg0->camera = cam; arg0->z_position = z;
//     arg0->unkB8 = b8; arg0->unk40 = u40; arg0->unk76 = rot; arg0->unk7A = rot;
//     arg0->old_x_position = x; arg0->old_y_position = y;
//     arg0->unk1CC = arg0->y_position; arg0->old_z_position = arg0->z_position;
//     arg0->unkC4 = uC4; cam->unk3D4 = (struct127 *) arg0->unk31C;
// }
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_15063254.s")
