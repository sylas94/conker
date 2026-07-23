#include <ultra64.h>

#define func_150ADA20 func_150ADA20_u8_proto
#include "functions.h"
#undef func_150ADA20
#include "variables.h"

void func_15131D4C(s32 arg0, s32 arg1);
s32 func_1000F568(s32 arg0, s32 arg1);
extern s32 func_151EF610(void);
extern s32 D_800D187C;
extern void *func_150335C8(struct127 *arg0, struct127 *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
extern void func_15166118(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9);
extern void func_151942E8();
extern f32 D_8009A104;

struct func_1506F1A8_stack {
    s32 unk00;
    struct127 *unk04;
    u8 unk08;
    s8 unk09;
    u8 pad0A[2];
    f32 unk0C;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    f32 unk30;
    f32 unk34;
    s8 unk38;
    s8 unk39;
    s8 unk3A;
    s8 unk3B;
    s8 unk3C;
    s8 unk3D;
    u8 unk3E;
    u8 pad3F[1];
    f32 unk40;
    f32 unk44;
    f32 unk48;
    s8 unk4C;
    u8 pad4D[3];
    u8 unk50;
    u8 unk51;
    u8 unk52;
    u8 unk53;
    s8 unk54;
    u8 pad55[3];
    f32 unk58;
    f32 unk5C;
    s16 unk60;
    s16 unk62;
    f32 unk64;
    f32 unk68;
    f32 unk6C;
    f32 unk70;
    f32 unk74;
    f32 unk78;
    f32 unk7C;
    f32 unk80;
    f32 unk84;
    f32 unk88;
    s16 unk8C;
    s16 unk8E;
    f32 unk90;
    u8 unk94;
    u8 unk95;
    u8 pad96[2];
    f32 unk98;
    f32 unk9C;
    f32 unkA0;
    f32 unkA4;
    f32 unkA8;
    f32 unkAC;
    s32 unkB0;
    s32 unkB4;
    s16 unkB8;
    s16 unkBA;
    f32 unkBC;
    f32 unkC0;
    f32 unkC4;
    f32 unkC8;
    f32 unkCC;
    f32 unkD0;
    f32 unkD4;
    s16 unkD8;
    s16 unkDA;
    s16 unkDC;
    s16 unkDE;
    f32 unkE0;
    f32 unkE4;
    f32 unkE8;
    f32 unkEC;
    f32 unkF0;
    s16 unkF4;
    s16 unkF6;
    s16 unkF8;
    s16 unkFA;
    f32 unkFC;
    f32 unk100;
    f32 unk104;
    f32 unk108;
    f32 unk10C;
    f32 unk110;
    f32 unk114;
    s16 unk118;
    s16 unk11A;
};

void func_151994B8(s32 arg0, struct func_1506F1A8_stack *arg1, s32 arg2, s32 arg3);
extern f32 D_80099DAC;
extern f32 D_80099DB0;
extern f32 D_80099DB4;
extern f32 D_80099DB8;
extern f32 D_80099DBC;
extern f32 D_80099DC0;
extern f32 D_80099DC4;
extern f32 D_80099DC8;
extern f32 D_80099DCC;
extern f32 D_80099DD0;
extern f32 D_80099DD4;
extern f32 D_80099DD8;
extern f32 D_80099DDC;
extern f32 D_80099DE0;
extern f32 D_80099DE4;
extern f32 D_80099DE8;
extern f32 D_80099DEC;
extern f32 D_80099DF0;
extern f32 D_80099DF4;
extern f32 D_80099DF8;
extern f32 D_80099DFC;
extern f32 D_80099E00;
extern f32 D_80099E04;
extern f32 D_80099E08;
extern f32 D_80099E0C;
extern f32 D_80099E10;
extern f32 D_80099E14;
extern f32 D_80099E18;
extern f32 D_80099E1C;
extern f32 D_80099E20;

struct func_1506C32C_stack {
    s32 sp24;
    s32 sp28;
    s32 sp2C;
    s32 sp30;
};

typedef struct Vec3w_15070D24 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} Vec3w_15070D24;

typedef struct Stack_15070D24 {
    Header2 header2;
    Header header;
    u8 pad16[2];
    f32 sp64[3];
    f32 sp70[2];
    Vec3w_15070D24 sp78;
    Vec3w_15070D24 sp84;
} Stack_15070D24;

extern Vec3w_15070D24 D_80099B88;
extern Vec3w_15070D24 D_80099B94;
extern Vec3w_15070D24 D_80099BBC;
extern f32 D_8009A094;
extern f32 D_80099F2C;
extern s32 func_150ADA20(void);
extern void func_15143134(void *, void *, s32);
extern void func_151DC484(f32 *, struct199 *, s32, u8, s32);
extern void func_15102B38(s32, u8, s32, s32, f32 *, s32, s32, f32, s32, s32, s32, s32, u8, s32);
extern void func_150E1570(struct127 *, f32, f32, f32, f32, f32, f32, s32, s32);


#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506AD30.s")

void func_1506AF74(void) {
    if ((D_800D154C->unk100 & 8) != 0) {
        D_800D154C->unk100 |= 4;
    }
    D_800D154C->unk100 &= 0xF7;
    func_1505E650(D_800D154C, 0x38, 1.0f, 5.0f, 0.0f, 0.0f, 0);
}

void func_1506AFE0(void) {
    func_1505E650(D_800D154C, 0x48, 1.0f, 5.0f, 0.0f, 0.0f, 0);
}

void func_1506B020(void) {
    D_800D154C->unk1CB = (u8)1;
    func_1505E650(D_800D154C, 0x39, 1.0f, 5.0f, 0.0f, 0.0f, 0);
}

void func_1506B070(void) {
}

void func_1506B078(void) {
    f32 tmp = (D_800D154C->y_position - (D_800D154C->unk118 - 150.0f)) * D_80099C34;

    if (tmp < 0.0f) {
        tmp = 1.0f;
    } else {
        tmp +=  1.0f;
    }
    func_1506B100(0xD1, tmp, 4.0f);
}

// triggered when entering water?
void func_1506B100(s32 arg0, f32 arg1, f32 arg2) {
    func_1505E650(D_800D154C, arg0, arg1, arg2, 0.0f, 0.0f, 0);
}

void func_1506B14C(void) {
    func_1505E650(D_800D154C, D_800D154C->unk84.uh + 1, D_800D154C->animation_speed, 3.0f, 0.0f, 0.0f, 0);
}

void func_1506B198(void) {
    func_1505E650(D_800D154C, D_800D154C->unk84.uh + 1, D_800D154C->animation_speed, 3.0f, 0.0f, 0.0f, 1);
}

void func_1506B1E8(void) {
    func_1505E650(D_800D154C, 0x3C, 1.0f, 3.0f, 0.0f, 0.0f, 0);
}

void func_1506B228(void) {
    func_1505E650(D_800D154C, 0x54, 1.0f, 3.0f, 0.0f, 0.0f, 0);
}

void func_1506B268(void) {
    D_800D154C->unk83 = 0;
    D_800D154C->disable_run = 0;
    func_1505E650(D_800D154C, 0xF, 1.0f, 6.0f, 0.0f, 0.0f, 0);
}

void func_1506B2BC(void) {
    struct127 *temp_v0 = func_150721E8(D_800D154C);
    if ((temp_v0 != 0) && (((((s32)temp_v0 - (s32)&D_800CC2D0) / 0x32C) + 1) == D_800CC2D0[0].unk274)) {
        D_800D154C->unk218 = 0;
        D_800D154C->unk232 = (u8)4;
    }
}

void func_1506B328(void) {
    func_1505E650(D_800D154C, 0x3E, 1.0f, 5.0f, 0.0f, 0.0f, 0);
}

void func_1506B368(void) {
}

void func_1506B370(void) {
    // return index of D_800D154C in structs array
    func_1507D4F8(((s32)D_800D154C - (s32)D_800CC2D0) / (s32)sizeof(struct127));
}

void func_1506B3B0(void) {
}

// PERMUTER CANDIDATE (best 1479): logic byte-correct (all diffs are register-rename/schedule/frame,
// no wrong ops). Residual: obj(D_800D154C) wants a1 (IDO gives a3, cascades all temps); target keeps
// a redundant `v0 = mag` copy for the 2nd/3rd threshold compares; %hi(D_80099A3C) base is hoisted
// early to before the call; frame 0x20 vs my 0x28 (one extra spill); +3/+4 tail wants bgezl (IDO
// emits plain bgez). Header note: D_80099A3C is really a u8[] (header says s16[]); D_80099A3E is u8
// (header s16). Reconstruction (byte-correct logic):
// void func_1506B3B8(void) {
//     s16 sdiff; s32 mag; u8 sel = 0;
//     sdiff = (D_800D154C->unk7A + (D_800D154C->unk1FD << 8)) -
//             func_1505A630(D_800CC2D0[0].x_position - D_800D154C->x_position,
//                           D_800D154C->z_position - D_800CC2D0[0].z_position, 0);
//     mag = (sdiff >> 8) & 0xFF;
//     if ((mag & 0x80) != 0) mag = (-mag) & 0xFF;
//     if (mag < ((u8 *)D_80099A3C)[0]) {
//         sel = 1;
//     } else {
//         if (D_80099A43 < mag) sel = 5;
//         else if (*(u8 *)&D_80099A3E < mag) sel = 2;
//         if (sdiff >= 0) sel = (sel + 3) & 0xFF; else sel = (sel + 4) & 0xFF;
//     }
//     D_800D154C->unk138 = 0;
//     D_800D154C->unk244 = ((u8 *)D_80099A3C)[sel];
//     D_800D154C->unk21C = 0x4E20;
// }
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506B3B8.s")
// NON-MATCHING: 5% there...
// void func_1506B3B8(void) {
//     u8 sp19;
//     s16 temp_t0;
//     s32 temp_a3;
//     s32 temp_v0;
//     s32 temp_v1;
//     struct127 *temp_a1;
//     struct127 *temp_a1_2;
//     s32 phi_a2;
//     s32 phi_a0;
//     u8 phi_a0_2;
//
//     temp_a1 = D_800D154C;
//     sp19 = 0;
//     temp_a1_2 = D_800D154C;
//     temp_t0 = (temp_a1_2->unk7A + (temp_a1_2->unk1FD << 8)) - func_1505A630(D_800CC2D0[0].x_position - temp_a1->x_position, temp_a1->z_position - D_800CC2D0[0].z_position, temp_a1, 0);
//     temp_v1 = (s32) temp_t0 >> 8;
//     temp_a3 = temp_v1 & 0xFF;
//     phi_a2 = temp_v1 & 0xFF;
//     if ((temp_a3 & 0x80) != 0) {
//         phi_a2 = -temp_a3 & 0xFF;
//     }
//     temp_v0 = phi_a2;
//     if (phi_a2 < (s32) D_80099A3C) {
//         phi_a0 = 1;
//     } else {
//         if ((s32) D_80099A43 < temp_v0) {
//             phi_a0_2 = (u8)5U;
//         } else {
//             phi_a0_2 = sp19;
//             if ((s32) D_80099A3E < temp_v0) {
//                 phi_a0_2 = (u8)2U;
//             }
//         }
//         if ((s32) temp_t0 < 0) {
//             phi_a0 = (phi_a0_2 + 4) & 0xFF;
//         } else {
//             phi_a0 = (phi_a0_2 + 3) & 0xFF;
//         }
//     }
//     temp_a1_2->unk138 = (u8)0;
//     D_800D154C->unk244 = (s16) D_80099A3C[phi_a0]; // + 0x800A0000)->unk-65C4;
//     D_800D154C->unk21C = (u16)0x4E20;
// }

void func_1506B4EC(void) {
    func_1506B3B8();
}

void func_1506B50C(void) {
    D_800D154C->unk21C = 0;
}

void func_1506B520(void) {
    s32 tmp;

    if (D_800D154C->health != 0) {
        if ((D_800D154C->unk31C != 0) && (D_800D154C->unk31C->unk78 == 0x25)) {
            tmp = 427;
        } else {
            tmp = 240;
        }
        func_1505E650(D_800D154C, tmp, 1.5f, 3.0f, 0.0f, 0.0f, 0);
    } else {
        func_1507CD64(D_800D154C, 1);
    }
}

void func_1506B5A4(void) {
}

void func_1506B5AC(void) {
}

void func_1506B5B4(void) {
    D_800D154C->unk1CB = (u8)1;
}

void func_1506B5CC(void) {
    D_800D154C->unk1CB = (u8)1;
}

void func_1506B5E4(void) {
    func_1506160C(D_800D154C, 2, 7, 8, 0);
    D_800D154C->animation_speed = 0.0f;
    D_800D154C->unk2D0->unk10 = 0.0f;
}

void func_1506B634(s32 arg0) {
    u32 temp_v0;
    u32 temp_v1;
    u8 temp_a0;
    struct126 *temp_a1;
    struct127 *volatile *temp_a2;

    temp_v0 = func_150ADA20();
    temp_a2 = (struct127 *volatile *)&D_800D154C;
    temp_v1 = temp_v0 % (u32)(u8)arg0;
    temp_a0 = temp_v1;
    temp_a1 = (*temp_a2)->unk31C;
    if (temp_a1->unk16 != 0) {
        if (D_800BE9F0 == 0x29) {
            if ((u8)temp_v1 == 7) {
                temp_a0 = 0;
            }
        }
        temp_a1->unkE = ((u8 *)D_80099ABC)[temp_a0];
    } else {
        temp_a1->unkE = ((u8 *)D_80099AB4)[(u8)temp_v1];
    }

    if ((*temp_a2)->unk31C->unkE == 0xA7) {
        D_800D1580 = 0xFF020144;
        D_800D154C->unk31C->unkC = (func_150ADA20() % 3U) + 2;
        func_1506E8D8();
        D_800D154C->xz_velocity = D_800D154C->xz_velocity * D_80099C38;
    }
}

void func_1506B740(void) {
    u8 res = func_150ADA20() & 0xFF;

    if ((D_80099C3C != D_800D154C->unk118) && (D_800D154C->y_position < D_800D154C->unk118)) {
        D_800D154C->unk31C->unkE = 0x2D0;
    } else {
        if (D_800D154C->unk84.uh == 0xA7) {
            if (D_800D154C->unk31C->unkC == 0) {
                res = 0;
            } else {
                D_800D154C->unk31C->unkC--;
                res = 0xFF;
            }
        }
        if (res < 0x80) {
            func_1506B634(8);
        }
    }
}

void func_1506B7F4(void) {
    D_800D154C->disable_run = 0;
    D_800D154C->unk83 = 0;
    func_1506B634(2);
}

void func_1506B82C(void) {
    D_800D154C->disable_run = 0;
    D_800D154C->unk83 = 0;
    func_1507F640();
}

void func_1506B860(void) {
    func_1506B100(181, 0.6299999952316284f, 5.0f);
}

void func_1506B88C(void) {
    func_1506B100(182, 1.0f, 4.0f);
}

void func_1506B8B4(void) {
    D_800D154C->unk31C->unk78 = (u8)0;
    D_800D154C->disable_run = (u8)0;
    D_800D154C->unk83 = (u8)0;
    func_1507F640();
}

void func_1506B8F4(void) {
    func_1506B100(222, 0.75f, 4.0f);
}

void func_1506B91C(void) {
    func_1506B100(191, 1.0f, 4.0f);
}

void func_1506B944(void) {
    D_800D154C->disable_run = (u8)0;
    D_800D154C->unk83 = (u8)0;
    func_1506B100(0xC5, 1.0f, 4.0f);
}

void func_1506B984(void) {
    func_1506B100(0xAF, 1.0f, 4.0f);
}

void func_1506B9AC(void) {
    D_800D154C->unk244 = (u16)0;
}

void func_1506B9C0(void) {
    struct126 *temp_a0;

    D_800BE720[D_800C3E78] |= 0x4000;
    temp_a0 = D_800D154C->unk31C;
    if (temp_a0 != 0) {
        temp_a0->unk78 = 0;
        D_800D2E60[D_800D1940 >> 3] |=  (1 << (D_800D1940 & 7));
    }
    func_1507F640(temp_a0);
}

void func_1506BA4C(s32 arg0, s32 arg1) {
    if (D_800D1580 == 0) {
        func_100109D0(D_800D154C);
    } else {
        if (D_800D154C->camera == 0) {
            func_10010154(D_800D1580, D_800D154C, 28000, arg0, arg1);
        } else {
            func_10010154(D_800D1580, D_800D154C, 24000, 500, 2500);
        }
    }
}

void func_1506BAD8(s32 arg0, s32 arg1) {
    if (D_800D1580 == 0) {
        func_10010A3C(D_800D154C);
    } else {
        if (D_800D154C->camera == 0) {
            func_10010344(D_800D1580, D_800D154C, 28000, arg0, arg1);
        } else {
            func_10010344(D_800D1580, D_800D154C, 24000, 500, 2500);
        }
    }
}

void func_1506BB64(s32 arg0, s32 arg1) {
    func_10012718(D_800D1582, D_800D154C, 28000, arg0, arg1);
}

void func_1506BBA8(s32 arg0, s32 arg1) {
    if (D_800D154C->camera == 0) {
        func_10010154(D_800D1582, D_800D154C, 14000, arg0, arg1);
    } else {
        func_10010154(D_800D1582, D_800D154C, 12000, 500, 2500);
    }
}

void func_1506BC24(s32 arg0, s32 arg1) {
    if (D_800D154C->camera == 0) {
        func_10010344(D_800D1582, D_800D154C, 0x36B0, arg0, arg1);
    } else {
        func_10010344(D_800D1582, D_800D154C, 0x2EE0, 0x1F4, 0x9C4);
    }
}

void func_1506BCA0(void) {
    D_800D154C->y_velocity = D_800D1580;
}

// ???
void func_1506BCC8(void) {
    struct127 *temp_v1;
    f32 temp_f0;

    temp_v1 = D_800D154C;
    if (temp_v1->interaction_state == 0x16) {
        if (temp_v1->y_position == temp_v1->unk180) {
            D_800D154C->y_velocity = (func_151EF610() % 8) + D_800D1580;
            temp_v1 = D_800D154C;
            if (temp_v1->xz_velocity != 0.0f) {
                temp_v1->y_velocity = temp_v1->y_velocity * (temp_v1->xz_velocity / 40.0f);
            } else {
                temp_v1->y_velocity = 0.0f;
            }
        }
    } else {
        temp_f0 = temp_v1->y_position - temp_v1->unk180;
        if ((-5.0f < temp_f0) && (temp_f0 < 5.0f)) {
            temp_v1->y_velocity = (f32) D_800D1580;
        }
    }
}

void func_1506BDE8(void) {
    if (D_800D154C->y_position < D_80099C40) {
        D_800D154C->y_velocity = (f32) D_800D1580;
    }
}

void func_1506BE2C(void) {
    D_800D154C->gravity = D_800D1580;
}

void func_1506BE54(void) {
    D_800D154C->gravity = D_800D1580 * D_80099C44;
}

void func_1506BE84(void) {
    D_800D154C->disable_run = 0;
}

void func_1506BE98(void) {
    D_800D154C->target_speed = D_800D1580;
}

void func_1506BEC0(void) {
    D_800D154C->disable_run = D_800D1580;
}

void func_1506BEDC(void) {
    D_800D154C->unkD0 = D_800D1580;
    D_800D154C->unk114 = (f32) ((s32) D_800D1580 >> 8);
}

void func_1506BF1C(void) {
    if (D_800D154C->unk118 <= D_800D154C->y_position) {
        func_1506BF5C();
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506BF5C.s")

void func_1506C32C(void) {
    s32 cmd;
    struct func_1506C32C_stack values;
    s32 index;
    s32 temp;

    if (D_800D187C != 0) {
        D_800D187C--;
        cmd = D_800D1580;
        values.sp24 = D_800D187C & 0x7FF;
        values.sp28 = cmd & 0x7FF;
        values.sp2C = (cmd >> 11) & 0x7FF;
        values.sp30 = (cmd >> 22) & 0x7FF;

        if (values.sp30 != 0) {
            index = 4;
        } else if (values.sp2C != 0) {
            index = 3;
        } else if (values.sp28 != 0) {
            index = 2;
        } else {
            index = 0;
        }

        if (index != 0) {
            index = func_1000F568(values.sp24, index) - values.sp24;
        }

        temp = *(&values.sp24 + index);
        if (temp != 0) {
            D_800D187C &= 0xFFFEF800;
            D_800D1580 = temp | D_800D187C;
            func_1506BF5C();
        }
    }
}

void func_1506C418(void) {
    func_10010A3C(D_800D154C);
}

void func_1506C43C(void) {
    func_100109D0(D_800D154C);
}

// requires jump table
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506C460.s")
// requires jump table
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506CE6C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506D2E8.s")

void func_1506D4F4(void) {
    func_1505E650(D_800D154C, D_800D154C->unk84.uh, 0.009999999776482582f, 0.0f, 0.0f, 0.0f, 0);
}

void func_1506D538(void) {
    if (D_800C35EA != 1) {
        func_1507D4F8(D_800C3E78);
    }
}

void func_1506D570(void) {
    D_800D154C->unk6E = 0;
}

// HARD (best 4385): needs IDO's SOFT float->int truncation (fcsr save + ctc1 RZ + cvt.w.s + 2^31
// overflow retry) for `(s32)((f32)(u16 val)/divisor)`, but the same cast here emits a single
// trunc.w.s. Both forms occur per-construct in this file; the source construct that routes this
// division-result cast through the soft library sequence wasn't found. Input (u32->f32) conversion
// already matches. Reconstruction:
// extern f32 D_80099D48;
// extern void func_1507E7E4(struct127 *, s32, s32, s32, s32);
// void func_1506D584(void) {
//     struct127 *obj = D_800D154C;
//     s32 cmd; f32 divisor; u32 val;
//     if (((u8 *)obj)[0x70] != 0x2A) {
//         cmd = D_800D1580;
//         divisor = obj->unk2D0->unk10;
//         val = cmd & 0xFFFF;
//         if (divisor == 0.0f) divisor = D_80099D48;
//         if (val != 0xFFFF) val = (s32)((f32)val / divisor) & 0xFFFF;
//         func_1507E7E4(obj, (cmd >> 24) & 0xFF, (cmd >> 16) & 0xFF, val, 0);
//     }
// }
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506D584.s")
// ???
void func_1506D6B4(void) {
    struct127 *p = D_800D154C;
    s32 sel;
    if (D_80099D4C == p->unk118) { return; }
    if (p->unk118 < (f32) p->unk1A6) { return; }
    if (p->health >= 2) { sel = 0x2C; } else { sel = 0x29; }
    D_800D1580 = (D_800D1580 & 0xFFFF) | (sel = (sel << 10) << 14);
    func_1506D584();
}
void func_1506D74C(void) {
    f32 sp34;
    f32 sp30;
    f32 sp2C;

    if (D_800D154C->in_water == 0) {
        D_800D154C->gravity = 5.0f;
        D_800D154C->y_velocity = 0.0f;
    }
    D_800D154C->y_position += 70.0f;
    ((u8 *)D_800D154C)[0x137] = 0;
    D_800D154C->disable_run = 0;
    func_1505A184(D_800D154C->unk76, (f32)D_800D1580, 0, &sp34, &sp30, &sp2C);
    func_1505E650(D_800D154C, 0xF, 1.0f, 0.0f, 0.0f, 0.0f, 0);
    D_800D154C->x_position += sp34;
    D_800D154C->z_position += sp30;
    D_800D154C->unk100 |= 2;
    D_800D154C->unk28 = 0.0f;
    D_800D154C->unk83 = 0x14;
    D_800D154C->unk31C->unk44 = 0xC;
    D_800D154C->unk31C->unk54 = 0xA;
}

void func_1506D898(void) {
    D_800D154C->y_position -= 80.0f;
    func_1505E650(D_800D154C, 663, 1.0f, 0.0f, 0.0f, 0.0f, 0);
    D_800D154C->unk100 &= 0xFFDF;
    D_800D154C->unk83 = 0;
    D_800D154C->disable_run = 0;
    D_800D154C->unk31C->unk97 = 0;
    D_800D154C->unk31C->unk44 = 12;
}

void func_1506D934(void) {
    D_800D154C->unk103 = D_800D1580;
}

void func_1506D950(void) {
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506D958.s")

void func_1506DA78(void) {
    D_800D154C->immune = D_800D1580;
}

void func_1506DA94(void) {
    if (D_800D1580 != 0) {
        if ((D_800D154C->unk44 > 20.0f) && (D_800D154C->xz_velocity > 20.0f)) {
            D_800D154C->unk83 = (u8)0;
        }
    }
    func_15174690(D_800C3E78, 0, 24, 0, 409, 4, 170, 0xFF, 0);
}

void func_1506DB30(void) {
    D_800D1890 = (s8) D_800D1580;
    func_15076760();
}

void func_1506DB5C(void) {
    D_800D154C->xz_velocity = (f32) D_800D1580;
}

void func_1506DB84(void) {
    D_800D154C->unk239 = (s8) D_800D1580;
}

void func_1506DBA0(void) {
    D_800D154C->unk1E5 = D_800D1580 & 0xff;
    D_800D154C->unk1E6 = (D_800D1580 >> 8) & 0xff;
}

void func_1506DBD4(void) {
    struct127 *temp_v0 = func_15072208(D_800D154C, 0);
    if (temp_v0 != NULL) {
        func_15054A5C(temp_v0, D_800D154C);
    }
}

extern f32 D_80099D50;

void func_1506DC10(void) {
    s32 a0;
    s32 v1;
    if (((D_800D154C->unk118 - 60.0f) < D_800D154C->y_position) || (D_80099D50 == D_800D154C->unk118)) {
        v1 = func_150ADA20() & 3;
        if (v1 >= 2) {
            a0 = v1 + 0x612;
        } else {
            a0 = v1 + 0x8F;
        }
    } else {
        a0 = 9;
    }
    func_15060A9C(a0, D_800D154C);
}

void func_1506DCA4(void) {
    D_800D154C->unk2E8 = D_800D1580;
}

void func_1506DCC0(void) {
    D_800D154C->unk2EC = (s32) D_800D1580;
}

void func_1506DCDC(void) {
    D_800D154C->health = (s8) D_800D1580;
}

void func_1506DCF8(void) {
}

void func_1506DD00(void) {
    struct127 *temp_v1;

    if (D_800D1580 == 0) {
        temp_v1 = D_800D154C;
        temp_v1->unkF8 = (s32) temp_v1->unk144->unk18;
    } else {
        temp_v1 = D_800D154C;
        temp_v1->unkF8 |= D_800D1580;
    }
}

void func_1506DD44(void) {
    D_800D154C->unkF8 &= ~D_800D1580;
}

void func_1506DD6C(void) {
    if (D_800D154C->unk31C != 0) {
        D_800D154C->unk31C->matrix_physics = D_800D1580 & 0x7F;
    }
    if (D_800D1580 == 0) {
        D_800D154C->unk76 = D_800D154C->unk7A;
    }
}

void func_1506DDB8(void) {
}

void func_1506DDC0(void) {
    if (func_15178E50(D_800BE9F0) != 0) {
        func_1516EED4(D_800C3E78, D_800D1580, 0xFF, 0);
    }
}

void func_1506DE04(void) {
    s32 i;
    for(i = 0; i < 2; i++) {
        func_15174690(D_800C3E78, 10, 18, 12, 0x199, 4, 0xAA, 0xFF, 0);
    }
}

// jump table
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506DE84.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506E0EC.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506E2CC.s")
// PERMUTER/REGALLOC CANDIDATE (best 4009): logic byte-close but cmd wants register a3 (IDO gives v1)
// which cascades all temp regs; v1=cmd&0x7FFF wants early compute + spill to 0x18 (IDO computes it
// late); first test wants plain bgez (IDO emits bgezl). Reconstruction:
// extern s32 func_151F2CDC(struct127 *);
// extern s32 *D_800BE5A8[];
// s32 func_1506E46C(struct127 *arg0, s32 *arg1, s32 arg2) {
//     s32 cmd = *arg1;
//     s32 v1 = cmd & 0x7FFF;
//     if ((cmd << 10) < 0) {
//         if (arg2 == 0)      { if (func_100107F8(arg0) != 0) return 0; }
//         else if (arg2 == 1) { if (func_10010894(arg0) != 0) return 0; }
//         else if (arg2 == 2) { if (func_151F2CDC(arg0) == 1) return 0; }
//     }
//     if (v1 >= 0x7D0) {
//         s32 v0 = D_800BE5A8[((u8 *)arg0)[0x288]][v1 - 0x7D0];
//         if (v0 == 0) return 0;
//         if ((cmd & 0xFF200000) != 0) cmd = (cmd & 0xFF200000) | (v0 & 0xFFFFFF);
//         else cmd = cmd | v0;
//     }
//     v1 = (u32)cmd >> 16;
//     if (v1 != 0) {
//         if (((u32)cmd >> 24) < (u32)(func_150ADA20() & 0xFF)) return 0;
//         if ((v1 & 0x1F) != 0) cmd = func_1000F568(cmd & 0x7FFF, v1 & 0x1F);
//         else cmd = cmd & 0x7FFF;
//     }
//     *arg1 = cmd;
//     return 1;
// }
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506E46C.s")

void func_1506E5FC(void) {
    if (func_1506E46C(D_800D154C, &D_800D1580, 0) != 0) {
        func_1506BA4C(300, 1800);
    }
}

void func_1506E63C(void) {
    if (func_1506E46C(D_800D154C, &D_800D1580, 0) != 0) {
        func_1506BA4C(100, 800);
    }
}

void func_1506E67C(void) {
    if (func_1506E46C(D_800D154C, &D_800D1580, 0) != 0) {
        func_1506BA4C(190, 1300);
    }
}

void func_1506E6BC(void) {
    if (func_1506E46C(D_800D154C, &D_800D1580, 0) != 0) {
        func_1506BA4C(300, 3000);
    }
}

void func_1506E6FC(void) {
    if (func_1506E46C(D_800D154C, &D_800D1580, 0) != 0) {
        func_1506BA4C(700, 4000);
    }
}

void func_1506E73C(void) {
    if (func_1506E46C(D_800D154C, &D_800D1580, 0) != 0) {
        func_1506BA4C(3000, 8000);
    }
}

void func_1506E77C(void) {
    if (func_1506E46C(D_800D154C, &D_800D1580, 0) != 0) {
        func_1506BBA8(300, 1800);
    }
}

void func_1506E7BC(void) {
    if (func_1506E46C(D_800D154C, &D_800D1580, 0) != 0) {
        func_1506BBA8(300, 3000);
    }
}

void func_1506E7FC(void) {
    if (D_800D154C->unk28 == 0.0f) {
        if (D_800D154C->unk107 == 0) {
            func_1506E5FC();
        }
    }
}

void func_1506E848(void) {
    if ((func_1506E46C(D_800D154C, &D_800D1580, 0) != 0) && (func_1000F4D8((u16)D_800D1582) == 0)) {
        func_1506BA4C(0x50, 800);
    }
}

void func_1506E898(void) {
    if (func_1506E46C(D_800D154C, &D_800D1580, 2) != 0) {
        func_1506BB64(300, 1800);
    }
}

void func_1506E8D8(void) {
    if (func_1506E46C(D_800D154C, &D_800D1580, 1) != 0) {
        func_1506BAD8(300, 1800);
    }
}

void func_1506E918(void) {
    if (func_1506E46C(D_800D154C, &D_800D1580, 1) != 0) {
        func_1506BAD8(100, 800);
    }
}

void func_1506E958(void) {
    if (func_1506E46C(D_800D154C, &D_800D1580, 1) != 0) {
        func_1506BAD8(190, 1300);
    }
}

void func_1506E998(void) {
    if (func_1506E46C(D_800D154C, &D_800D1580, 1) != 0) {
        func_1506BAD8(300, 3000);
    }
}

void func_1506E9D8(void) {
    if (func_1506E46C(D_800D154C, &D_800D1580, 1) != 0) {
        func_1506BAD8(700, 4000);
    }
}

void func_1506EA18(void) {
    if (func_1506E46C(D_800D154C, &D_800D1580, 1) != 0) {
        func_1506BAD8(3000, 8000);
    }
}

void func_1506EA58(void) {
    if (func_1506E46C(D_800D154C, &D_800D1580, 1) != 0) {
        func_1506BC24(300, 3000);
    }
}

void func_1506EA98(void) {
    u8 temp_t6;
    struct127 *temp_a1;

    temp_t6 = (D_800D154C->unk13C - 100);
    if (D_800D154C->unk13C != 0) {
        temp_a1 = &D_800CC2D0[temp_t6];
        if (D_800CC2D0[temp_t6].unk13D >= 100) {
            D_800CC2D0[temp_t6].unk13D = (u8)0U;
            D_800CC2D0[temp_t6].xz_velocity = 18.0f;
            D_800CC2D0[temp_t6].y_velocity = 40.0f;
            D_800CC2D0[temp_t6].gravity = 6.0f;
            D_800CC2D0[temp_t6].unk76 = (u16) D_800D154C->unk7A;
            D_800CC2D0[temp_t6].unk65 = (u8)0;
            if (D_800CC2D0[temp_t6].id  == 0x20) {
                D_800CC2D0[temp_t6].unkF8 |= 0x200;
                D_800CC2D0[temp_t6].y_velocity = 0.0f;
                D_800CC2D0[temp_t6].gravity = 0.0f;
                D_800CC2D0[temp_t6].xz_velocity = 0.0f;
            }
            D_800CC2D0[temp_t6].stunned = (u8)0xFE;
            D_800CC2D0[temp_t6].unk105 = (u8)0;
            D_800CC2D0[temp_t6].unk106 = func_1505E7CC(0xC, temp_a1); //, temp_t6);
            D_800CC2D0[temp_t6].unk84.uh = (u16)0xFFFF;
            D_800CC2D0[temp_t6].unk1CC = (f32) D_80099DA0;
            func_1505E874(temp_t6, temp_a1);
            D_800CC2D0[temp_t6].unk25C |= 0x40;
        }
        D_800D154C->unk13C = (u8)0;
    }
}

void func_1506EBC0(void) {
    u8 temp_v0 = (u8)(D_800D154C->unk13C - 100);

    if (D_800D154C->unk13C) {
        if ((s32) D_800CC2D0[temp_v0].unk13D >= 0x64) {
            D_800CC2D0[temp_v0].unk65 = 0;
            D_800CC2D0[temp_v0].unk13D = (u8)0U;
            D_800CC2D0[temp_v0].xz_velocity = 0.0f;
            D_800CC2D0[temp_v0].y_velocity = 0.0f;
            D_800CC2D0[temp_v0].gravity = 6.0f;
            D_800CC2D0[temp_v0].unk1CC = D_80099DA4; // 1000000.0
        }
        D_800D154C->unk13C = 0U;
    }
}

void func_1506EC50(void) {
    if (D_80099DA8 < D_800D154C->unk28) {
        if (((D_800D1580 & 0x8000) == 0) || (D_800CC2E8[0] < D_800D154C->y_position)) {
            D_800D1878 = D_800D1580 & 0xFF;
            D_800D1880 = 0;
            D_800D154C->unk138 -= 1;
        }
    }
}

void func_1506ECD0(void) {
    D_800D154C->unk2D0->unk4 |= 0x8000;
}

void func_1506ECF0(void) {
    D_800D154C->unk3A = (s8) D_800D1580;
}

void func_1506ED0C(void) {
    D_800D154C->unk83 = (s8) D_800D1580;
    D_800D154C->unk100 |= 0x10;
    D_800D154C->unk31C->unk31 = (u8)1;
}

void func_1506ED4C(void) {
    D_800D154C->unk100 = (s8) D_800D1580;
}

void func_1506ED68(void) {
    D_800D154C->unkA9 = (u8)5;
    D_800D154C->unk31C->unk31 = (u8)0;
}

void func_1506ED90(void) {
    D_800D154C->unk21C = (s16) D_800D1580;
}

void func_1506EDAC(void) {
    D_800D154C->unkF4 = (s32) D_800D1580;
}

void func_1506EDC8(void) {
    D_800D154C->unkF4 &= ~D_800D1580;
}

void func_1506EDF0(void) {
    D_800D154C->unkF4 |= D_800D1580;
}

void func_1506EE14(void) {
    D_800D154C->unk25C |= D_800D1580;
}

void func_1506EE38(void) {
    D_800D154C->unk25C &= ~D_800D1580;
}

void func_1506EE60(void) {
    s32 temp_v0 = D_800D1580;
    s32 temp_a1 = D_800D1580 & 0xFFFF;

    if (temp_v0 != 0) {
        func_15188810(D_800D154C, temp_a1, D_800D1580 >> 0x10);
        return;
    }
    func_15188A9C(D_800D154C, temp_a1);
}
// NON-MATCHING: same issue as earlier
// void func_1506EE60(void) {
//     s32 temp_a1;
//     s32 temp_v0;
//
//     temp_v0 = D_800D1580;
//     temp_a1 = temp_v0 & 0xFFFF;
//     if (temp_v0 != 0) {
//         func_15188810(D_800D154C.unk0, temp_a1, temp_v0 >> 0x10);
//         return;
//     }
//     func_15188A9C(D_800D154C.unk154C, temp_a1);
// }

void func_1506EEAC(void) {
    func_151898C0(D_800D154C, D_800D1580);
}

void func_1506EED8(void) {
    D_800D154C->unk24E = (s8) D_800D1580;
}

void func_1506EEF4(void) {
    D_800D154C->unk276 = (D_800D1580 >> 16) & 0xFFFF;
    D_800D154C->unk278 = (D_800D1580 >> 24) & 0xFF;
    D_800D154C->unk282 = D_800D1580 & 0xFFFF;
    D_800D154C->unk284 = 0;
    D_800D154C->unk285 = 0;
    D_800D154C->unk286 = 0;
    D_800D154C->unk287 = 0;
}

// TBD whats goins on here
// PERMUTER CANDIDATE (best 190, void): all instructions byte-identical, pure register
// rename (target keeps &D_800D154C in a2; IDO picks a0). No C form flips it.
// permuter NO ZERO, best 150 (2x600s, no zero)
// void func_1506EF5C(void) {
//     s32 temp = D_800D1580;
//     *(u16 *)&D_800D154C->unk282 = 0xFFFF;
//     D_800D154C->unk276 = 5;
//     *(u8 *)((u8 *)D_800D154C + ((temp >> 16) & 0xFF) * 2 + 0x284) = temp >> 8;
//     *(u8 *)((u8 *)D_800D154C + ((temp >> 16) & 0xFF) * 2 + 0x285) = temp;
// }
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506EF5C.s")

void func_1506EFB4(void) {
    D_800D154C->unk282 = (u16)0;
}

void func_1506EFC8(s32 arg0) {
    if (D_800D154C->id != 0x8C) {
        func_150BB760(D_800D154C);
    }
}

void func_1506F004(s32 arg0) {
    func_150BCBBC(D_800D154C);
}

void func_1506F02C(s32 arg0) {
    func_150BA4C0(D_800D154C, 0xFF, 0);
}

void func_1506F05C(s32 arg0) {
    func_151925C4(D_800D154C, 0x32, 0xFF, 1);
}

void func_1506F090(s32 arg0) {
    func_151925C4(D_800D154C, -1, 0xFF, 1);
}

void func_1506F0C4(s32 arg0) {
    func_150C1260(D_800D154C, 0);
}

void func_1506F0F0(s32 arg0) {
    func_150C1260(D_800D154C, 1);
}

void func_1506F11C(s32 arg0) {
    func_150BABE0(D_800D154C, 0, 0xFF);
}

void func_1506F14C(s32 arg0) {
    func_150BABE0(D_800D154C, 1, 0xFF);
}

void func_1506F17C(s32 arg0) {
    func_150AEEB0(D_800D154C, 0xFF);
}

void func_1506F1A8(s32 arg0) {
    struct func_1506F1A8_stack sp1C;
    struct127 *obj;

    obj = D_800D154C;
    sp1C.unk04 = obj;
    sp1C.unk08 = obj->unique_id;
    sp1C.unk14 = 80.0f;
    sp1C.unk20 = 102.0f;
    sp1C.unk24 = D_80099DAC;
    sp1C.unk28 = D_80099DB0;
    sp1C.unk2C = 1200.0f;
    sp1C.unk40 = D_80099DB4;
    sp1C.unk30 = 26.0f;
    sp1C.unk34 = D_80099DB8;
    sp1C.unk44 = -187.0f;
    sp1C.unk48 = D_80099DBC;
    sp1C.unk58 = D_80099DC0;
    sp1C.unk5C = D_80099DC4;
    sp1C.unk64 = D_80099DC8;
    sp1C.unk6C = D_80099DCC;
    sp1C.unk68 = D_80099DD0;
    sp1C.unk70 = D_80099DD4;
    sp1C.unk74 = D_80099DD8;
    sp1C.unk78 = D_80099DDC;
    sp1C.unk7C = D_80099DE0;
    sp1C.unk80 = D_80099DE4;
    sp1C.unk84 = D_80099DE8;
    sp1C.unk88 = D_80099DEC;
    sp1C.unk90 = D_80099DF0;
    sp1C.unk98 = D_80099DF4;
    sp1C.unkA8 = D_80099DF8;
    sp1C.unkAC = D_80099DFC;
    sp1C.unkBC = 14.0f;
    sp1C.unkC0 = 9.0f;
    sp1C.unkCC = 25.0f;
    sp1C.unkD0 = D_80099E00;
    sp1C.unkD4 = D_80099E04;
    sp1C.unkEC = D_80099E08;
    sp1C.unk09 = 0xC;
    sp1C.unk3E = 0xC8;
    sp1C.unkF0 = D_80099E0C;
    sp1C.unk38 = -1;
    sp1C.unk39 = 2;
    sp1C.unk3A = -1;
    sp1C.unk4C = -1;
    sp1C.unk00 = 0xF;
    sp1C.unk54 = 1;
    sp1C.unk50 = 0x3C;
    sp1C.unk51 = 0xFF;
    sp1C.unk52 = 0xEB;
    sp1C.unk53 = 0x52;
    sp1C.unkFC = 402.0f;
    sp1C.unk60 = 0x1E;
    sp1C.unk62 = 0xF;
    sp1C.unk8C = 0xC;
    sp1C.unk8E = 0x15;
    sp1C.unk94 = 0x50;
    sp1C.unk95 = 0x78;
    sp1C.unkB0 = 4;
    sp1C.unkB4 = 2;
    sp1C.unkB8 = 0x1E;
    sp1C.unkBA = 0x11;
    sp1C.unk0C = 0.0f;
    sp1C.unk10 = 0.0f;
    sp1C.unk18 = 0.0f;
    sp1C.unk1C = 0.0f;
    sp1C.unk3B = 0;
    sp1C.unk3C = 0;
    sp1C.unk3D = 0;
    sp1C.unk9C = 0.0f;
    sp1C.unkA0 = 5.0f;
    sp1C.unkA4 = 100.0f;
    sp1C.unkC4 = 0.5f;
    sp1C.unkC8 = 0.5f;
    sp1C.unkD8 = 0x50;
    sp1C.unkDA = 0x78;
    sp1C.unkDC = 0x10;
    sp1C.unkDE = 0xF;
    sp1C.unkE0 = 0.0f;
    sp1C.unkE4 = 5.0f;
    sp1C.unkE8 = 100.0f;
    sp1C.unkF4 = 0x28;
    sp1C.unkF6 = 0xF;
    sp1C.unkF8 = 0x50;
    sp1C.unkFA = 0x50;
    sp1C.unk118 = 0x14;
    sp1C.unk11A = 0xC;
    sp1C.unk100 = D_80099E10;
    sp1C.unk104 = D_80099E14;
    sp1C.unk108 = D_80099E18;
    sp1C.unk10C = 45.0f;
    sp1C.unk110 = D_80099E1C;
    sp1C.unk114 = D_80099E20;
    func_151994B8(0, &sp1C, 0xFF, 0);
}

void func_1506F524(s32 arg0) {
    func_15197A7C(D_800D154C);
}

// NEAR-MISS (best 4124, store-order without the f22/fE24/fE28 locals). Giant stack-struct
// initializer using the SAME struct (func_1506F1A8_stack) and the SAME call
// func_151994B8(0, &sp, 0xFF, 0) as the already-matched func_1506F1A8. All 89 field values are
// verified correct (extracted mechanically via scratchpad/parse_init.py). Residual: IDO spills 2
// float temps so the frame is 0x140 vs the target's 0x138 => every stack offset shifts +8 (~90
// 's' marks) plus a float-load schedule diff. No hand-found assignment order avoids the spill
// (store-order 4124, func_1506F1A8-order 4779, both +CSE-locals worse). Permuter/ordering candidate.
/* Reconstruction (values correct; scheduling near-miss):
extern f32 D_80099E24, D_80099E28, D_80099E2C, D_80099E30, D_80099E34, D_80099E38, D_80099E3C;
extern f32 D_80099E40, D_80099E44, D_80099E48, D_80099E4C, D_80099E50, D_80099E54, D_80099E58;
extern f32 D_80099E5C, D_80099E60, D_80099E64, D_80099E68, D_80099E6C, D_80099E70, D_80099E74;
extern f32 D_80099E78, D_80099E7C, D_80099E80, D_80099E84, D_80099E88, D_80099E8C, D_80099E90, D_80099E94;

void func_1506F54C(s32 arg0) {
    struct func_1506F1A8_stack sp1C;
    struct127 *obj;
    f32 f22 = 22.0f;
    f32 fE24 = D_80099E24;
    f32 fE28 = D_80099E28;

    obj = D_800D154C;
    sp1C.unk04 = obj;
    sp1C.unk14 = 165.0f;
    sp1C.unk20 = 193.0f;
    sp1C.unk24 = D_80099E2C;
    sp1C.unk28 = D_80099E30;
    sp1C.unk2C = 370.0f;
    sp1C.unk40 = D_80099E34;
    sp1C.unk30 = D_80099E38;
    sp1C.unk34 = D_80099E3C;
    sp1C.unk44 = -191.0f;
    sp1C.unk48 = D_80099E40;
    sp1C.unk58 = D_80099E44;
    sp1C.unk5C = D_80099E48;
    sp1C.unk6C = D_80099E50;
    sp1C.unk68 = D_80099E54;
    sp1C.unk70 = D_80099E58;
    sp1C.unk64 = D_80099E4C;
    sp1C.unk74 = D_80099E5C;
    sp1C.unk78 = D_80099E60;
    sp1C.unk7C = 0.0f;
    sp1C.unk80 = D_80099E64;
    sp1C.unk84 = D_80099E68;
    sp1C.unk88 = D_80099E6C;
    sp1C.unk90 = D_80099E70;
    sp1C.unk98 = D_80099E74;
    sp1C.unkA0 = 58.0f;
    sp1C.unkA4 = 212.0f;
    sp1C.unkAC = D_80099E78;
    sp1C.unkBC = 6.0f;
    sp1C.unkC0 = 10.0f;
    sp1C.unkC4 = D_80099E7C;
    sp1C.unkCC = 37.0f;
    sp1C.unkD0 = D_80099E80;
    sp1C.unkD4 = D_80099E84;
    sp1C.unkE4 = 130.0f;
    sp1C.unk08 = obj->unique_id;
    sp1C.unkE8 = 306.0f;
    sp1C.unk09 = 0xD;
    sp1C.unk3E = 0x9F;
    sp1C.unk00 = 0xF;
    sp1C.unk54 = 1;
    sp1C.unk50 = 0x3C;
    sp1C.unk51 = 0xFF;
    sp1C.unk52 = 0xEB;
    sp1C.unk53 = 0x52;
    sp1C.unkEC = D_80099E88;
    sp1C.unk39 = -1;
    sp1C.unk4C = -1;
    sp1C.unk60 = 0x23;
    sp1C.unk62 = 0xA;
    sp1C.unk94 = 0x50;
    sp1C.unk95 = 0x50;
    sp1C.unkB0 = 3;
    sp1C.unkB4 = 2;
    sp1C.unkB8 = 0x19;
    sp1C.unkBA = 0xA;
    sp1C.unk0C = f22;
    sp1C.unk10 = f22;
    sp1C.unk18 = f22;
    sp1C.unk1C = f22;
    sp1C.unk38 = 0;
    sp1C.unk3A = 0;
    sp1C.unk3B = 0;
    sp1C.unk3C = 0;
    sp1C.unk3D = 0;
    sp1C.unk8C = 0xF;
    sp1C.unk8E = 0x11;
    sp1C.unk9C = f22;
    sp1C.unkA8 = fE24;
    sp1C.unkC8 = fE24;
    sp1C.unkD8 = 0x50;
    sp1C.unkDA = 0x50;
    sp1C.unkDC = 0xF;
    sp1C.unkDE = 0x11;
    sp1C.unkE0 = f22;
    sp1C.unkF4 = 0x23;
    sp1C.unkF6 = 0xF;
    sp1C.unkF8 = 0x50;
    sp1C.unkFA = 0x64;
    sp1C.unk104 = fE28;
    sp1C.unk108 = fE28;
    sp1C.unk118 = 0xF;
    sp1C.unk11A = 0x11;
    sp1C.unkF0 = D_80099E8C;
    sp1C.unkFC = 198.0f;
    sp1C.unk100 = 102.0f;
    sp1C.unk10C = 89.0f;
    sp1C.unk110 = D_80099E90;
    sp1C.unk114 = D_80099E94;
    func_151994B8(0, &sp1C, 0xFF, 0);
}
*/
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1506F54C.s")

void func_1506F8C0(s32 arg0) {
    func_1519EF70(D_800D154C, 0, 0);
}

void func_1506F8F0(s32 arg0) {
    struct127* a0;
    func_150E2EA4(a0 = D_800D154C, a0->unique_id, 0x14, -1, 482.0f, -127.0f, -45.0f, D_80099E98, -211.0f, -114.0f, 3, 3, 5, 20.0f, (func_150ADA68() * 10.0f) + 40.0f, 0, 0.0f);
}

void func_1506F9C0(s32 arg0) {
    struct127* a0;
    func_150E2EA4(a0 = D_800D154C, a0->unique_id, 0x14, -1, 241.0f, -127.0f, -45.0f, 418.0f, -211.0f, -114.0f, 3, 3, 5, 20.0f, (func_150ADA68() * 10.0f) + 40.0f, 0, 0.0f);
}

void func_1506FA90(s32 arg0) {
    struct127* a0;
    func_150E2EA4(a0 = D_800D154C, a0->unique_id, 0x1A, -1, -181.0f, -218.0f, -1.0f, D_80099E9C, -584.0f, -2.0f, 3, 3, 5, 20.0f, (func_150ADA68() * 10.0f) + 40.0f, 0, 0.0f);
}

void func_1506FB60(s32 arg0) {
    if (func_151044F4() != 0) {
        func_151C6A28(D_800D154C, (arg0 - 0x13) & 0xFF, 0xFF, 0);
    } else {
        func_151C62D0(D_800D154C, (arg0 - 0x13) & 0xFF, 0, 0, -1, 0xFF, 0);
    }
}

void func_1506FBE8(s32 arg0) {
    func_151A0A10(D_800D154C, 0x46, 0xFF, 0);
}

void func_1506FC1C(s32 arg0) {
    func_151A0A10(D_800D154C, 0x28, 0xFF, 0);
}

void func_1506FC50(s32 arg0) {
    func_1519E688();
}

void func_1506FC74(s32 arg0) {
    func_1519E6BC(D_800D154C);
}

void func_1506FC9C(s32 arg0) {
    func_150B3AB0(D_800D154C, 0xFF);
}

void func_1506FCC8(s32 arg0) {
    func_15196438(D_800D154C, 6, 0xFF, 0);
}

void func_1506FCFC(s32 arg0) {
    func_15196438(D_800D154C, 5, 0xFF, 0);
}

extern f32 D_80099EA0;

void func_1506FD30(s32 arg0) {
    struct127* a0;
    func_150E2EA4(a0 = D_800D154C, a0->unique_id, 1, -1, 0.0f, 0, D_80099EA0, 0.0f, 0, 414.0f, 3, 3, 5, 20.0f, (func_150ADA68() * 10.0f) + 40.0f, 1, 50.0f);
}

void func_1506FDF0(s32 arg0) {
    func_151AABC4(D_800D154C, 0);
}

void func_1506FE1C(s32 arg0) {
    func_151AABC4(D_800D154C, 1);
}

void func_1506FE48(s32 arg0) {
    func_151AABC4(D_800D154C, 0);
}

void func_1506FE74(s32 arg0) {
    func_151AABC4(D_800D154C, 1);
}

void func_1506FEA0(s32 arg0) {
    func_151AABC4(D_800D154C, 2);
}

void func_1506FECC(s32 arg0) {
    func_151AABC4(D_800D154C, 3);
}

void func_1506FEF8(s32 arg0) {
    func_151AB920(D_800D154C, 0);
}

void func_1506FF24(s32 arg0) {
    func_151AB920(D_800D154C, 1);
}

void func_1506FF50(s32 arg0) {
    func_151AB930(D_800D154C);
}

void func_1506FF78(s32 arg0) {
    func_150CBF80(D_800D154C, 0, 1, 0xFF);
}

void func_1506FFAC(s32 arg0) {
    func_150CBF80(D_800D154C, 1, 1, 0xFF);
}

void func_1506FFE0(s32 arg0) {
    func_150CBF80(D_800D154C, 2, 1, 0xFF);
}

void func_15070014(s32 arg0) {
    func_150CA150(D_800D154C);
}

void func_1507003C(s32 arg0) {
    func_151B01B8(D_800D154C, 0);
    func_151B09BC(D_800D154C, 0, 0x3E8, 0xFF, 0);
}

void func_15070084(s32 arg0) {
    func_151AECA0(D_800D154C, 0xFF, 1);
}

void func_150700B4(s32 arg0) {
    func_151B03B8(D_800D154C, 0xFF, 1);
}

void func_150700E4(s32 arg0) {
    func_15193660(D_800D154C, 0xFF, 1);
}

void func_15070114(s32 arg0) {
    func_151937F4(D_800D154C, 0xFF, 1);
}

void func_15070144(s32 arg0) {
    struct198 tmp;
    s32 tmp0;

    tmp.unk0 = 1;
    tmp.unk8 = 0;
    tmp.unkC = 0;
    tmp.unk4 = D_800D154C;

    if (D_800BE9F0 == 0x2B) {
        tmp0 = 3;
    } else {
        tmp0 = 0;
    }
    func_151C0698(D_800D154C, 0, &tmp, tmp0 & 0xFF, 0xFF, 1);
    func_151C1FB8(D_800D154C);
}

void func_150701C4(s32 arg0) {
    func_151C5280(D_800D154C, 0xFF, 1);
}

void func_150701F4(s32 arg0) {
    func_151C9740(D_800D154C, 0xFF, 1);
}

void func_15070224(s32 arg0) {
    Header header;
    Header2 header2;

    header.unk0 = 3;
    header.unk1 = -1;
    header.unk2 = (func_150ADA20() % 5U) + 4;
    header.unk4 = 0;

    header2.unk0 = (s32) D_800D154C->x_position;
    header2.unk4 = (s32) D_800D154C->y_position;
    header2.unk8 = (s32) D_800D154C->z_position;

    func_151602C0(&header, &header2, (func_150ADA20() % 3U) + 4, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0, 0xFF, 1);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15070300.s")

void func_15070690(s32 arg0) {
    func_150EEE00(D_800D154C, (arg0 - 0x3E) & 0xFF, arg0);
}

void func_150706C4(s32 arg0) {
    func_150EEF40(D_800D154C, (arg0 - 0x3E) & 0xFF, arg0);
}

void func_150706F8(s32 arg0) {
    if ((D_800D154C->unk94 & 0x10) == 0) {
        func_150F03F8(D_800D154C, 0, 0xFF, 1);
    }
    if ((D_800D154C->unk94 & 8) == 0) {
        func_150F03F8(D_800D154C, 1, 0xFF, 1);
    }
}

void func_15070760(s32 arg0) {
    func_150EBEC0(D_800D154C, 0, 0xFF, 1);
}

void func_15070794(s32 arg0) {
    func_150EBEC0(D_800D154C, 1, 0xFF, 1);
}

void func_150707C8(s32 arg0) {
    func_150FDDA0(D_800D154C, 0xFF, 1);
}

void func_150707F8(s32 arg0) {
    func_150FDF38(D_800D154C, 0xFF, 1, 0, 0);
}

void func_15070830(s32 arg0) {
    func_150FE320(D_800D154C, 0xFF, 1);
}

void func_15070860(s32 arg0) {
    func_150FE49C(D_800D154C, 0xFF, 1, 0, 0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15070898.s")

void func_15070C18(s32 arg0) {
    func_15199834(D_800D154C);
}

void func_15103E40(struct127 *, struct127 *, struct17 *, u8, u8, u8, u8);
void func_15070C40(u8 arg0) {
    struct17 tmp;
    struct127 *temp_a1;
    struct127 *phi_a0;

    temp_a1 = D_800D154C;
    tmp.unk0 = temp_a1->x_position;
    tmp.unk4 = temp_a1->y_position;
    tmp.unk8 = temp_a1->z_position;

    phi_a0 = temp_a1->unk124 ? &D_800CC2D0[temp_a1->unk124 - 1] : temp_a1;
    func_15103E40(phi_a0, temp_a1, &tmp, arg0, 0, 0xFF, 0);
}

void func_15070CDC(s32 arg0) {
    func_15070C40(1);
}

void func_15070D00(s32 arg0) {
    func_15070C40(0);
}

void func_15070D24(s32 arg0) {
    Stack_15070D24 sp4C;

    sp4C.sp84 = D_80099B88;
    sp4C.sp78 = D_80099B94;

    if (D_800D154C->unk1D4 == 0) {
        return;
    }

    if ((D_800D154C->unk74 & 0xF) == 0xF) {
        return;
    }

    sp4C.sp70[0] = (func_150ADA68() * 101.0f) + 151.0f;
    sp4C.sp70[1] = (func_150ADA68() * 4.0f) + 4.0f;

    func_15143134(&sp4C.sp84, sp4C.sp64, (s32)D_800D154C->unk1D4 + 0x40);

    func_15102B38((s32)D_800D154C, 1, (s32)&sp4C.sp84, (s32)&sp4C.sp78, sp4C.sp70,
                  ((func_150ADA20() + 0U) % 6U) + 5, ((func_150ADA20() + 0U) % 0x9CU) + 0x64,
                  (func_150ADA68() * 2496.0f) + D_80099F2C,
                  (s32)sp4C.sp64, 0xFF, 0, -1, 0xFF, 0);

    sp4C.header.unk0 = 3;
    sp4C.header.unk1 = -1;
    sp4C.header.unk2 = (func_150ADA20() % 6U) + 0xA;
    sp4C.header.unk4 = 0;

    sp4C.header2.unk0 = (s32)sp4C.sp64[0];
    sp4C.header2.unk4 = (s32)sp4C.sp64[1];
    sp4C.header2.unk8 = (s32)sp4C.sp64[2];

    func_151602C0(&sp4C.header, &sp4C.header2, (func_150ADA20() % 0xC9U) + 0x37, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0, 0xFF, 0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15070F60.s")
void func_15071230(s32 arg0) {
    func_15070F60(0);
}

void func_15071254(s32 arg0) {
    func_15070F60(1);
}

void func_15071278(s32 arg0) {
    func_150FC438(D_800D154C, 0, 1, D_800D154C->unk84.ub[1]);
}

extern void func_150FE860(struct127 *arg0, s32 arg1, s32 arg2);
extern void func_151D8868(void *arg0, s32 arg1, s32 arg2, s32 arg3);

struct sp18_150712AC {
    /* 0x0 */ u8 unk0;
    /* 0x1 */ u8 unk1;
    /* 0x2 */ s16 unk2;
    /* 0x4 */ u8 unk4;
    /* 0x5 */ u8 unk5;
    /* 0x6 */ s8 unk6;
    /* 0x7 */ u8 unk7;
};

void func_150712AC(s32 arg0) {
    struct sp18_150712AC sp18;

    func_150FE860(D_800D154C, 0xFF, 1);
    if (D_800D154C->camera != 0) {
        sp18.unk0 = 1;
        sp18.unk2 = (func_150ADA20() % 7U) + 0xA;
        sp18.unk5 = 1 << D_800D154C->camera->unk23D;
        sp18.unk4 = (func_150ADA20() % 7U) + 2;
        sp18.unk6 = -1;
        func_151D8868(&sp18, 0, 0xFF, 1);
    }
}

extern void func_150FF084(struct127 *arg0, s32 arg1, s32 arg2);
extern void func_150FED30(struct127 *arg0, s32 arg1, s32 arg2);

void func_15071360(s32 arg0) {
    struct sp18_150712AC sp18;

    if (func_151044F4() != 0) {
        func_150FF084(D_800D154C, 0xFF, 1);
    } else {
        func_150FED30(D_800D154C, 0xFF, 1);
    }
    if (D_800D154C->camera != 0) {
        sp18.unk0 = 1;
        sp18.unk2 = (func_150ADA20() % 5U) + 0xF;
        sp18.unk5 = 1 << D_800D154C->camera->unk23D;
        sp18.unk4 = (func_150ADA20() % 4U) + 3;
        sp18.unk6 = -1;
        func_151D8868(&sp18, 0, 0xFF, 1);
    }
}

void func_15071434(s32 arg0) {
    func_150FF840(D_800D154C, 1, 0, 0xFF, 1);
}

void func_15071470(s32 arg0) {
    func_150FF840(D_800D154C, 0, 0, 0xFF, 1);
}

void func_150714AC(s32 arg0) {
    func_150FF840(D_800D154C, 0, 1, 0xFF, 1);
}

void func_150714E8(s32 arg0) {
    func_151D5714(D_800D154C, &D_800A2148, &D_800A2154, D_80088BB0, 1.0f, 0xFF, 1);
}

void func_15071544(s32 arg0) {
    func_151D4668(D_800D154C);
    func_151D469C(D_800D154C, 4, 0x78, 0xFF, 1);
}

void func_1507158C(s32 arg0) {
    func_151D4668(D_800D154C);
    func_151D469C(D_800D154C, 2, 0x78, 0xFF, 1);
}

void func_150715D4(s32 arg0) {
    func_151D4668(D_800D154C);
    func_151D469C(D_800D154C, 3, 0x78, 0xFF, 1);
}

void func_1507161C(s32 arg0) {

}

void func_15071628(s32 arg0) {
    func_151D0058(D_800D154C, (arg0 - 0x55) & 0xFF, 0xFF, 1);
}

void func_15071668(s32 arg0) {
    func_151D0024(D_800D154C);
}

void func_15071690(s32 arg0) {
    struct127 *temp_a0;
    s32 pad0;
    s32 sp1C;

    temp_a0 = D_800D154C;
    if ((temp_a0->unk1D4 != 0) && ((temp_a0->unk74 & 0xF) != 0xF)) {
        func_150B60E0(temp_a0, &sp1C);
        func_150B5C38(&sp1C, 0xFF, 1);
    }
}

void func_150716EC(s32 arg0) {
    struct17 tmp;
    struct127 *temp_v0;

    temp_v0 = D_800D154C;
    tmp.unk0 = temp_v0->x_position;
    tmp.unk4 = temp_v0->y_position;
    tmp.unk8 = temp_v0->z_position;
    func_151D5404(&tmp, 1502.0f, 3000.0f, 0.00033333332976326346f, 0xC, 0xF, 0xFF, 0);
}

void func_15071764(s32 arg0) {
    struct127 *sp34 = func_15083E90(18);
    if (sp34 != NULL) {
        func_150F0BEC(sp34);
        func_150F10D4(sp34);
        func_15161E24(sp34, 1, 2, 300, 70, 255, 130, 0, 255, 1);
    }
}

void func_150717E0(s32 arg0) {
    struct {
        struct127 *unk0;
        u8 unk4;
    } sp20;
    struct127 *temp_v0;

    temp_v0 = func_15083E90(0x12);
    if (temp_v0 != 0) {
        sp20.unk0 = temp_v0;
        sp20.unk4 = temp_v0->unique_id;
        func_15131D4C((s32)&sp20, 0x43);
        func_151494E0((s32)&sp20, 0x43);
    }
}

void func_15071830(s32 arg0) {
    func_150F9BB0(D_800D154C, 0xFF, 1);
}

void func_15071860(s32 arg0) {
    func_1519072C(D_800D154C);
}

void func_15071888(s32 arg0) {
    func_151D5714(D_800D154C, &D_800A1FB0, &D_800A1FBC, D_80088B90, D_80099F30, 0xFF, 1);
}

extern u32 D_80099BB8;
void func_15143134(void *, void *, s32);
void func_151C329C(s32 arg0, s32 arg1, s32 arg2);

void func_150718E4(s32 arg0) {
    f32 *p;
    f32 sp24[2];
    u32 sp20;

    sp20 = D_80099BB8;
    if ((D_800D154C->unk1D4 != 0) || ((D_800D154C->unk74 & 0xF) == 0xF)) {
        p = sp24;
        func_15143134(&D_800A5480, p,
                      (((s32)((u8 *)&sp20)[func_150ADA20() & 3]) << 6) + (s32)D_800D154C->unk1D4);
        sp24[1] = D_800D154C->unk180 + 20.0f;
        func_151C329C((s32)p, 0xFF, 1);
    }
}

void func_15071998(s32 arg0) {
    func_150FA520(D_800D154C, 0, 0xFF, 1);
}

void func_150719CC(s32 arg0) {
    func_150FA520(D_800D154C, 1, 0xFF, 1);
}

void func_15071A00(s32 arg0) {
    func_150FA520(D_800D154C, 2, 0xFF, 1);
}

void func_15071A34(s32 arg0) {
    func_151D09A8(D_800D154C, 0xFF, 1);
}

void func_15071A64(s32 arg0) {
    struct199 tmp;

    if (!(func_150ADA20() & 1) && (D_800D154C->unk1D4 != 0) && ((D_800D154C->unk74 & 0xF) != 0xF) &&
        (D_800CC2D0->stunned != 0) && ((s32)D_800CC2D0->health > 0)) {
        func_1504715C(&tmp, D_800D154C);
        func_15143134(&D_80099BBC, &tmp.unk24, (s32)D_800D154C->unk1D4 + 0x3C0);
        func_151DC484(&tmp.unk24, &tmp, 0, 0xFF, 1);
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15071B18.s")

void func_15071D08(s32 arg0) {
    func_150F2230(D_800D154C, 0xFF, 1);
}

void func_15071D38(void) {
    void (*func)(s32);

    func = D_80086150[D_800D1580];
    if (func != 0) {
        func(D_800D1580);
    }
}

void func_15071D78(void) {
    struct127 *tmp;
    struct127 *orig;

    tmp = func_150721E8(D_800D154C);
    if (tmp != NULL) {
        orig = D_800D154C;
        D_800D154C = tmp;
        func_15071D38();
        D_800D154C = orig;
    }
}

void func_15071DC8(void) {
    func_15141A7C(D_800D154C, D_800D1580);
}

void func_15071DF4(void) {
    func_15192800(D_800D154C, D_800D1580);
}

void func_15071E20(void) {
    D_800D154C->unk247 = (s8) D_800D1580;
}

void func_15071E3C(void) {
    D_800D154C->unk248 = (s8) D_800D1580;
}

void func_15071E58(void) {
    D_800D1878 = D_800D1580 & 0xFF;
    D_800D154C->unk244 = (D_800D1580 >> 8) & 0xFF;
    func_1505E650(D_800D154C, D_800D154C->unk244, 1.2000000476837158f, 3.0f, D_800D1878, 0.0f, 0);
}

void func_15071ED4(void) {
    func_1505E650(D_800D154C, 0x59, 1.0f, 3.0f, 0.0f, 0.0f, 0);
}

void func_15071F14(void) {
    func_1505E650(D_800D154C, 0x24, 1.0f, 3.0f, 0.0f, 0.0f, 0);
}

void func_15071F54(void) {
    func_1507C8E0(D_800D154C, D_800D1580);
}

void func_15071F80(void) {
    if (D_800C35EA == 1) {
        D_800D154C->unk138++;
    }
}

void func_15071FB0(void) {
    if (D_800D154C->unk28 == 0.0f) {
        D_800D154C->unk10C = (u16)0;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15071FDC.s")
void func_1506160C(struct127 *, s32, u8, u8, s32);
extern s32 D_800D1580;
extern struct127 *D_800D154C;
void func_150721A4(void)
{
  u8 new_var;
  u16 temp_a2 = D_800D1580;
  unsigned short temp_t6 = D_800D1580 >> 8;
  u8 temp_t7 = D_800D1580 >> 16;
  new_var = temp_t7;
  func_1506160C(D_800D154C, new_var & 0xFFu, temp_a2, temp_t6, 0);
}


struct127 *func_150721E8(struct127 *arg0) {
    return func_15072208(arg0, 0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15072208.s")

void func_150722F0(void) {
    struct127 *temp_v0 = func_150721E8(D_800D154C);
    if (temp_v0 != 0) {
        s32 tmp0 = D_800D1580 >> 8;
        u16 tmp1 = D_800D1580;
        func_1506160C(temp_v0, 2, tmp0, tmp1, 0);
    }
}

void func_1507233C(void) {
    D_800D154C->unk94 = (s32) ~(D_800D1580 | 1);
}

void func_15072360(void) {
    D_800D154C->unk94 &= ~D_800D1580;
}

void func_15072388(void) {
    D_800D154C->unk94 |= D_800D1580;
}

void func_150723AC(void) {
    struct127 *temp_v0 = func_15083E90(D_800D1583);
    if (temp_v0 != NULL) {
        func_15060F28(temp_v0, 0);
    }
}

void func_150723E0(void) {
    struct127 *temp_v0 = func_15083E90(D_800D1583);
    if ((temp_v0 != 0) && (temp_v0->unk65 != 0)) {
        func_15060F28(temp_v0, 0);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15072420.s")
extern u8 D_800BE616;
extern u8 D_800C3E78;
extern struct127 D_800CC2D0[26];
extern s32 D_800D1580;
extern struct127 *D_800D154C;
void func_1507266C(void)
{
  s32 temp_v1;
  s32 temp_a2;
  struct127 *temp_a1;
  unsigned short new_var;
  if (D_800BE616 == 0)
  {
    if (D_800D154C->unk222 == 0)
    {
      return;
    }
  }
  new_var = D_800D1580;
  temp_a2 = D_800D1580 >> 16;
  temp_v1 = new_var;
  temp_a1 = &D_800CC2D0[D_800D154C->unk222];
  temp_a1->unk65 = D_800C3E78 + 1;
  temp_a1->unk5C = temp_a2;
  temp_a1->unk101 = 4;
  temp_a1->stunned = 0;
  temp_a1->immune = 0xFF;
  temp_a1->unk218 = 0;
  temp_a1->unkE4 = 0;
  temp_a1->unkE6 = 0;
  temp_a1->unk232 = temp_v1;
  temp_a1->unkEC = 1.0f;
  temp_a1->unkF0 = 1.0f;
  temp_a1->unkDC = 1.0f;
  temp_a1->unkE0 = 1.0f;
  func_151B5BA0(&D_800CC2D0[D_800C3E78], temp_a1, temp_a2);
}


void func_15072740(void) {
    s32 temp_v0;
    struct127 *temp_v1;

    temp_v0 = D_800D1580 >> 16;
    temp_v1 = &D_800CC2D0[D_800D154C->unk222];
    temp_v1->unk65 = D_800C3E78 + 1;
    temp_v1->unk5C = temp_v0;
    temp_v1->unk101 = 4;
}

void func_150727AC(void) {
    D_800D154C->animation_speed = D_800D1580 * D_80099F4C;
    D_800D154C->unk2D0->unk10 = D_800D154C->animation_speed;
}

// HARD/SPLIT-SYMBOL blocked (best 50 natural / 85 struct-byte-identical). Same family as
// game_83300 func_1505EEF4/func_150626EC: IDO unrolls this small-bodied loop x4, which needs a
// static trip count => same-base loop bounds (D_800CC2D0+addend). But the target's loop bounds are
// DISTINCT symbols D_800CC5FC (=&elem1, start) and D_800D121C (=&elem25, end). Naming those symbols
// (pointer loop) makes IDO emit a remainder-handling prologue (score ~3700). Naming only the start
// (D_800CC5FC[] array, i<24) + separate entry-0 via D_800CC335/D_800CC4E8/D_800CC502 gets the START
// symbol + clean unroll but leaves the END as D_800CC5FC+0x4c20 (target D_800D121C) => best 85. Not
// permuter-fixable (reloc symbol, not registers). Natural reconstruction (best 50):
// void func_150727F0(void) {
//     s32 i;
//     for (i = 0; i < 25; i++) {
//         if (D_800CC2D0[i].interaction_state != 0 && (D_800C3E78 + 1) == D_800CC2D0[i].unk65) {
//             D_800CC2D0[i].unk218 = 0;
//             D_800CC2D0[i].unk232 = D_800D1580;
//         }
//     }
// }
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_150727F0.s")

void func_15072918(void) {
    func_15060F28(D_800D154C, 0);
}

void func_15072940(void) {
    func_15060F28(D_800D154C, 1);
}

void func_15072968(void) {
    func_1505E650(D_800D154C, 44, 1.5f, 12.0f, 0.0f, 0.0f, 0);
    D_800D154C->disable_run = 25;
}

void func_150729B4(void) {
    D_800D154C->unk2E4 = D_800D1580;
}

void func_150729D0(void) {
    D_800D154C->unk31C->unk8 = (u16)1;
    func_1507EB4C(D_800D154C, 21);
    func_1506B82C();
}

void func_15072A14(void) {
    D_800D154C->unk31C->unk66 = (u16)0;
    func_1507F640();
}

void func_15072A40(void) {
    D_800D154C->unk31C->unk19B = (u8)0;
    D_800D154C->unk31C->unk78 = (u8)0;
    func_1507F640();
}

void func_15072A7C(void) {
    if (D_800D154C->unk31C != 0) {
        D_800D154C->unk31C->unk1A9++;
        if ((func_150ADA20() & 7) < (u32) D_800D154C->unk31C->unk1A9) {
            func_1505E650(D_800D154C, 394, 1.0f, 4.0f, 0.0f, 0.0f, 0);
        }
    }
}

void func_15072AF8(void) {
    func_1505E650(D_800D154C, D_800D154C->unk84.uh + 1, 1.0f, 6.0f, 0.0f, 0.0f, 0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15072B44.s")
void func_15072DA0(void) {
    D_800D154C->unk2F8 &= 0xFFF8;
    D_800D154C->unk2F8 |= D_800D1580;
}

void func_15072DD8(void) {
    func_15083568(D_800D154C, D_800D1580, 1.0f, 0);

    if ((D_800D154C->unk31C != 0) && (D_800D154C->unk31C->unk11A == 1)) {
        D_800D154C->unk31C->unk11A = (u8)2U;
    }
}

void func_15072E38(void) {
    func_150836CC(D_800D154C, D_800D1580);

    if (D_800D154C->unk31C != 0) {
        D_800D154C->unk31C->unk11A = (u8)0;
    }
}

void func_15072E7C(void) {
    D_800D154C->unk10C = (s16) D_800D1580;
}

void func_15072E98(void) {
    D_800D154C->unk2D0->unk10 *= D_800D1874;
}

void func_15072EC0(void) {
    struct197 *tmp;

    tmp = D_800D154C->unk2D0;
    if (tmp->unk10 < D_800D1874) {
        D_800D154C->unk10C = 0;
    }
}

void func_15072EF4(void) {
    D_800D154C->stunned = (s8) D_800D1580;
}

void func_15072F10(void) {
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    s16 temp;

    temp = (s16)(D_800D154C->unk1D1 * 200);
    *(s16 *)((u8 *)D_800D154C->unk31C + 0x24) -= 1;
    func_1505A184((u16)(D_800D154C->unk7A - D_800D154C->unk31C->unk12), 2000.0f, (f32)temp * 0.0054931640625f, &sp4C, &sp48, &sp44);
    sp4C = sp4C * D_8009A094 + D_800D154C->x_position;
    sp48 = sp48 * D_8009A094 + D_800D154C->z_position;
    sp44 = sp44 * D_8009A094 + D_800D154C->y_position;
    func_150E1570(D_800D154C, D_800D154C->x_position, D_800D154C->y_position + (f32)D_800D154C->unkD6, D_800D154C->z_position, sp4C, sp44, sp48, D_800C3E78, 0x12);
}

void func_1507304C(void) {
}

void func_15073054(void) {
    D_800D154C->unk22E = (s16) D_800D1580;
}

void func_15073070(void) {

}

void func_15073078(void) {
    func_1512D748(0, D_800D1580, 1);
}

void func_150730A4(void) {
    D_800D154C->unk1FF = (u8)3;
    D_800D154C->unk200 = (s8) D_800D1580;
}

void func_150730D0(void) {
    struct127 *temp_v0;

    if (D_800D1580 == 1) {
        temp_v0 = D_800D154C;
        temp_v0->unk2F8 |= 0x100;
    } else {
        temp_v0 = D_800D154C;
        temp_v0->unk2F8 &= 0xFEFF;
      }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15073118.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1507342C.s")

void func_150738E8(void) {
    u8 temp_v0 = (u8)(D_800D154C->unk13C - 100);

    if (D_800D154C->unk13C != 0) {
        D_800D154C->unk13C = 0U;
        D_800CC2D0[temp_v0].unkF8 = 0x8200;
        D_800CC2D0[temp_v0].unk13D = 0;
        D_800CC2D0[temp_v0].unk76 = D_800D154C->unk7A;
        D_800CC2D0[temp_v0].unk65 = 0;
        D_800CC2D0[temp_v0].unk232 = 6;
        D_800CC2D0[temp_v0].unk218 = 0;
        D_800CC2D0[temp_v0].stunned = 0;
        D_800CC2D0[temp_v0].unk7A = 0xE000;
        func_1505E650(D_800D154C, 0x97, 1.0f, 5.0f, 0.0f, 0.0f, 0);
    }
}

void func_150739A4(void) {
    D_800D154C->unk64 = (s8) D_800D1580;
}

void func_150739C0(void) {
    D_800D154C->unk64 -= D_800BE9A0;

    if (D_800D154C->unk64 >= 0) {
        D_800D1880 = 0;
        D_800D154C->unk138--;
        D_800D1878 = D_800D1580;
    }
}

void func_15073A28(void) {
    D_800D154C->unk44 = (f32) D_800D1580;
}

// PERMUTER CANDIDATE (best 664): byte-identical ops, register renames (target loads obj into
// v1 and reuses v0 for unk124-index then val=D_800D1580; IDO gives obj=v0, index=t6, val=v1)
// plus two scheduler slots (immune=0 store fills the lw a1 load-delay; D_800D154C reload hoisted
// above the immune=0x14 store). No C form flips the v0/v1 root allocation.
// extern void func_1505D024(struct127 *, s32, s32, s32);
// extern f32 D_8009A0D8;
// void func_15073A50(void) {
//     struct127 *obj = D_800D154C;
//     struct127 *e = &D_800CC2D0[obj->unk124];
//     s32 val;
//     if (e->unk65 != 0) {
//         val = D_800D1580;
//         obj->unk13C = 0;
//         e->immune = 0;
//         func_1505D024(e, D_800D1580 & 0xFF00FF, 0, D_800C3E78);
//         e->unk1CC = D_8009A0D8;
//         if ((val << 1) < 0) {
//             e->unk1CC = D_800D154C->y_position;
//         }
//         e->immune = 0x14;
//         e->unk76 = D_800D154C->unk7A + val;
//     }
// }
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15073A50.s")

void func_15073B38(void) {
    struct func_15073B38_inner {
        u8 padA8[0xA8];
        f32 unkA8;
        u8 unkAC;
        s8 unkAD;
    };
    s32 *temp_v0;
    struct127 **temp_v1;
    f32 temp_f0;
    f32 temp_f2;

    temp_v0 = &D_800D1580;
    temp_v1 = &D_800D154C;
    temp_f0 = (f32)(*temp_v0 & 0xFFFF);
    ((struct func_15073B38_inner *)(*temp_v1)->unk31C)->unkA8 = temp_f0;
    temp_f2 = (f32)((*temp_v0 >> 16) & 0xFF);
    ((struct func_15073B38_inner *)(*temp_v1)->unk31C)->unkAC = (u32)temp_f2;
    ((struct func_15073B38_inner *)(*temp_v1)->unk31C)->unkAD = (*temp_v0 >> 24) & 0xFF;
}

void func_15073C28(void) {
    func_1507F640();
}

void func_15073C48(void) {

}

void func_15073C50(void) {
    D_800D154C->unk224 = (s32)(*(f32 *)((u8 *)D_800CC2E8 + (D_800D154C->unk222 * 0x32C)) + (f32)D_800D1580);
}

void func_15073CB8(void) {
    struct127 *tmp = func_1505F0AC(0x53);
    if ((tmp != 0) && ((u16)tmp->unk244 == 0x1F)) {
        tmp->unk21C = (u16)0;
    }
}

void func_15073CF4(void) {
    func_15062B1C(D_800D154C, (f32) D_800D1580);
}


void func_15073D34(void) {
    func_15062B50(D_800D154C, (f32) D_800D1580);
}

void func_15073D74(void) {
    struct127 *temp_v0;

    temp_v0 = func_15083E90(D_800D1583);
    if (temp_v0 != 0) {
        temp_v0->unk65 = (u8)0;
    }
}

void func_15073DA4(void) {
    s32 tmp;

    if (D_800D1580 != 0) {
        tmp = 18;
    } else {
        tmp = 2;
    }
    func_1506C460(D_800D154C->unk40, 150.0f, 0, 0, 100, tmp, 60.0f, 0.5f, 0, 0, 1);
}

void func_15073E2C(void) {
    func_1506C460(D_800D154C->unk40, 80.0f, 0, 0, 100, 11, 40.0f, 0.5f, 0, 14, 1);
}

void func_15073EA4(void) {
    func_1506C460(D_800D154C->unk40, 60.0f, 0, 0, 100, 12, 40.0f, 0.5f, 0, 14, 1);
}

void func_15073F1C(void) {
    struct126 *temp_v0 = func_1503195C(D_800D154C, 0x3C, 0);
    if (temp_v0 != NULL) {
        temp_v0->unk38 = 0x960;
    }
}

void func_15073F54(void) {
}

void func_15073F5C(void) {
    D_800D154C->unk2CB = (s8) D_800D1580;
}

void func_15073F78(void) {
    D_800D154C->unk10B &= ~D_800D1580;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15073FA0.s")

void func_15074644(void) {
    D_800D154C->unk31C->unk11A = (s8) D_800D1580;
}

void func_15074664(void) {
    if (D_800D154C->unk31C != NULL) {
        if (D_800D1580 == 1) {
            func_10011FDC(5);
        } else if ((u8) D_800D154C->unk31C->unk94 == 1) {
            func_10011FDC(0);
        }
        D_800D154C->unk31C->unk94 = D_800D1580;
    }
}
void func_150746F0(void) {
    struct127 *volatile *temp_a1;
    struct127 *temp_a0;
    s32 temp_v0;
    struct126 *temp_a1_2;
    struct108 *temp_v0_2;

    temp_a1 = &D_800D154C;
    temp_a0 = NULL;
    if (D_800BE616 != 0) {
        temp_a1 = &D_800D154C;
        temp_a0 = *temp_a1;
    } else if ((*temp_a1)->unk13C != 0) {
        temp_a0 = D_800CC2D0;
    }
    if (temp_a0 != NULL) {
        temp_v0 = D_800D1580;
        if (temp_v0 >= temp_a0->health) {
            temp_a0->health = 0;
            (*temp_a1)->health = 0;
            if (temp_a0->interaction_state == 1) {
                temp_a0->immune = 0xFF;
                func_1507CD64(temp_a0, 6);
            }
        } else {
            temp_a1_2 = temp_a0->unk31C;
            temp_a0->health = temp_a0->health - temp_v0;
            if (temp_a1_2 != NULL) {
                temp_v0_2 = temp_a0->camera;
                if (temp_v0_2 != NULL) {
                    if (((u8 *)temp_a1_2)[0x197] != 0) {
                        func_1517F488(0xFF, 0, 0, 0xB4, 0x14, ((u8 *)temp_v0_2)[0x23D]);
                    }
                }
            }
        }
    }
}
// ?
void func_150747E4(void) {
    s32 i;
    s32 t;

    t = D_800D154C->unk65;
    i = t;
    if (i != 0) {
        i = i - 1;
        D_800CC2D0[i].unk232 = D_800D1580;
        D_800CC2D0[i].unk218 = 0;
    }
}

void func_15074840(void) {
    if (D_800D154C->unk31C != 0) {
        D_800D154C->unk31C->unk1AA += D_800D1580;
    }
}

void func_15074870(void) {
    D_800D154C->unk24F = (s8) D_800D1580;
}

// PERMUTER CANDIDATE (best 395): ops byte-identical, register renames (target v1/a2 for
// D_800D1580/D_800D154C; IDO gives v0/v1) + one extra move on the flag/result path.
// void func_1507488C(void) {
//     s32 temp = D_800D1580;
//     struct127 *p = D_800D154C;
//     s32 mask = (temp >> 8) & 0xFF;
//     s32 flag = temp & 1;
//     s32 result = flag;
//     if (((&p->unk2E4)[(temp >> 16) & 0xFF] & mask) != 0) {
//         result = (flag ^ 1) & 0xFF;
//     }
//     if (result != 0) {
//         p->unk138 = p->unk138 + (temp >> 24);
//     }
// }
#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1507488C.s")

void func_150748F4(void) {
    D_800CC3D7 = (s8) D_800D1580;
}

void func_1507490C(void) {
    struct127 *tmp;
    u8 temp_v0 = (u8)(D_800D154C->unk13C - 100);

    if (D_800D154C->unk13C != 0) {
        tmp = &D_800CC2D0[temp_v0 & 0xFF];
        if (D_800CC2D0[temp_v0].unk13D >= 0x64) {
            D_800CC2D0[temp_v0].unk232 = D_800D1580;
            D_800CC2D0[temp_v0].unk218 = 0;
            D_800CC2D0[temp_v0].stunned = 0;
        }
    }
}

void func_15074980(void) {
    s32 i;
    struct126 *temp;
    f32 dist = (f32)(D_800D1580 * 8);

    for (i = 0; i < D_8008FD8C; i++) {
        if (func_1505A72C(D_800D154C, &D_800CC2D0[i]) < dist) {
            temp = D_800CC2D0[i].unk31C;
            if (temp != 0) {
                temp->chasing = 0x14;
            }
        }
    }
}

void func_15074A44(void) {
    if (D_800D154C->unk31C != 0) {
        D_800D154C->unk31C->unk26 = (s8) D_800D1580;
    }
}

void func_15074A6C(void) {
    if (D_800D154C->unk13C == 0) {
        D_800D154C->unk138++;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_15074A94.s")
// NON-MATCHING: JUSTREG
// void func_15074A94(void) {
//     f32 phi_f2;
//     f32 temp_f0;
//
//     temp_f0 = func_1505A72C(&D_800CC2D0, D_800D154C);
//
//     if (D_800D154C->unk148 < D_8009A0E8) {
//         D_800D154C->unk148 = D_800D154C->unk154;
//     }
//
//     if (temp_f0 < 200.0f) {
//         phi_f2 = D_8009A0EC;
//     } else {
//         if (D_8009A0F0 < temp_f0) {
//             phi_f2 = D_800D154C->unk148;
//         } else {
//             f32 tmp = D_8009A0F4;
//             phi_f2 = D_800D154C->unk148;
//             phi_f2 = phi_f2 - tmp;
//             phi_f2 = phi_f2 * ((temp_f0 - 200.0f) / D_8009A0F8);
//             phi_f2 = phi_f2 + tmp;
//         }
//     }
//     D_800D154C->unk154 = D_800D154C->unk158 = phi_f2;
//     D_800D154C->unk15C = D_8009A0FC;
// }

void func_15074B7C(void) {
    D_800D1880 = 0;
    D_800D1878 = D_800D1580;

    if (D_800D1580 == 0) {
        D_800D1878 = D_8009A100;
        D_800D154C->unk1FC |= 4;
        D_800D154C->unk138 = 0;
    }
}

void func_15074BD8(s32 arg0, s32 arg1, s32 arg2) {
}

void func_15074BEC(s32 arg0, s32 arg1, s32 arg2) {
}

void func_15074C00(s32 arg0, struct127 *arg1, s32 arg2) {
    struct199 tmp; // is this actually 2 structs?

    if (((u8)arg1->unk239 & 0x7F) == 5) {
        func_1504715C(&tmp);
        tmp.unk24 = D_800CC2C0;
        tmp.unk28 = D_800CC2C4;
        tmp.unk2C = D_800CC2C8;
        func_150C04C0(&tmp.unk24, &tmp, 0x16, 1, 0xFF, 0);
    }
}

void func_15074C80(struct127 *arg0, struct127 *arg1) {
    s32 temp_a2;

    if ((u16)arg0->unk278 == 0x11) {
        func_151942E8(arg0, arg1);
    }

    if (((u16)arg0->unk278 == 2) || ((u16)arg0->unk278 == 0x12) || ((u16)arg0->unk278 == 3) || ((u16)arg0->unk278 == 6)) {
        if (arg1->health == 0) {
            if ((u16)arg0->unk278 == 2) {
                temp_a2 = 0x2A;
            } else if ((u16)arg0->unk278 == 0x12) {
                temp_a2 = 0x2F;
            } else {
                if ((u16)arg0->unk278 == 3) {
                    temp_a2 = 0x39;
                } else {
                    temp_a2 = 0x51;
                }
            }
            func_150335C8(arg0, arg1, temp_a2, 0xC, 1, 0);
        }
        arg0->health = 0;
    }

    if (arg1->interaction_state == 0x19) {
        func_15166118((s32)(256.0f - (func_150484A0(arg0->y_velocity, arg0->xz_velocity) * D_8009A104)),
                      0xC0 - ((s32)arg0->unk76 >> 8),
                      (s32)arg0->x_position,
                      (s32)arg0->y_position,
                      (s32)arg0->z_position,
                      0x10,
                      0x14,
                      0,
                      0xFF,
                      0);
    }
}

void func_15074DEC(struct127 *arg0, s32 arg1, s32 arg2) {
    arg0->unk2E8 = 1;
}

void func_15074E04(s32 arg0, s32 arg1, s32 arg2) {
    func_1516FE1C((s32) (arg1 - (s32)&D_800CC2D0) / (s32) sizeof(struct127), 0xB4, 0xFF, 0);
    func_1518D1C0(arg1, 0xB, 0, 1, 0xFF, 0, &D_80099C1C);
}

void func_15074E80(struct127 *arg0, struct127 *arg1, s32 arg2) {
    s8 sp1F = 0;
    func_15194794(arg0, arg1, &sp1F);
    if (arg1->interaction_state == 1) {
        arg0->immune = (u8)0xFF;
        arg1->immune = (u8)0xC8;
        D_800D1580 = 0x60000; // 393216
        func_15072740();
    }
}

void func_15074EE8(struct127 *arg0, struct127 *arg1, s32 arg2) {
    if (arg1->interaction_state == 1) {
        arg0->immune = (u8)0xFF;
        arg1->immune = (u8)0xC8;
        D_800D1580 = 0x70000;
        func_15072740();
    }
}

void func_15074F30(struct127 *arg0, struct127 *arg1, s32 arg2) {
    arg0->unk232 = arg1->unk109;
    arg0->unk218 = 0;
}

extern f32 D_8009A108;
extern f32 D_8009A10C;
extern f32 D_8009A110;
void func_15194408(struct127 *arg0, struct127 *arg1);

void func_15074F48(struct127 *arg0, struct127 *arg1, s32 arg2) {
    f32 dx = D_8009A108 - arg0->x_position;
    f32 dz = arg0->z_position - D_8009A10C;

    arg1->unk76 = func_1505A630(dx, dz, 0);
    arg1->xz_velocity = sqrtf(dx * dx + dz * dz) * D_8009A110;
    func_15194408(arg0, arg1);
}

void func_15074FD4(struct127 *arg0, struct127 *arg1, s32 arg2) {
    if (arg1->interaction_state == 1) {
        arg0->immune = (u8)0xFF;
        arg1->immune = (u8)0xC8;
        D_800D1580 = 0x60000;
        if (arg0->id == 0x8E) {
            D_800D1580 = 0x140000;
        }
        func_15072740();
    }
    func_151942B0(arg0, arg1, arg2);
}

void func_15075050(struct127 *arg0, s32 arg1, s32 arg2) {
    arg0->unkB8 = 5.0f;
    if (arg0->xz_velocity > 0.0f) {
        arg0->unkB8 = -5.0f;
    }
    arg0->gravity = 5.0f;
    arg0->y_velocity = 12.0f;
}

void func_150750A4(struct127 *arg0, s32 arg1, s32 arg2) {
    arg0->gravity = 5.0f;
}

void func_150750C4(struct127 *arg0, struct127 *arg1, u8 *arg2) {

    if ((arg1->id  == 0x88) && ((s32) arg0->unk107 < 0x37)) {
        arg0->unk138 += 3;
    }
    func_15194794(arg0, arg1, arg2);
    if (arg1->id != 0x53) {
        func_15145A50(arg1);
        arg1->health = (u8)0;
        func_1507CD64(arg1, 8);
        *arg2 = (u8)39;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_981E0/func_1507515C.s")
