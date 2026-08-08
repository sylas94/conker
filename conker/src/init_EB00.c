#include <ultra64.h>
#define func_1000F85C func_1000F85C_hdr
#include "functions.h"
#undef func_1000F85C
#include "variables.h"

s32 func_10010E78(s32 arg0, s32 arg1, u16 arg2, s16 arg3, u8 arg4,
                   s32 arg5, s16 arg6, s16 arg7, s16 arg8, s16 arg9,
                   s16 argA);
void func_10011624(struct15 *arg0, s32 *arg1, s32 arg2, s32 arg3);
s32 func_1510F8CC(s32 arg0);
s32 func_1000F568(s32 arg0, s32 arg1);

typedef struct {
    u16 unk0;
    u16 unk2;
} struct_init_EB00_10011EB8_pair;

typedef struct {
    struct_init_EB00_10011EB8_pair unk0[5];
} struct_init_EB00_10011EB8_row;

typedef struct {
    u16 unk0;
    u8 pad2[6];
    u16 unk8;
    s16 unkA;
    s32 unkC;
    u8 pad10[8];
    union {
        s32 w;
        u16 h[2];
    } unk18;
    struct127 *unk1C;
} struct_init_EB00_1000ECCC;

s32 func_1000ECCC(struct_init_EB00_1000ECCC *arg0, s32 arg1, s32 arg2, s32 arg3,
                  s32 arg4, s32 arg5, u16 *arg6);

s32 func_1000EB00(struct04 *arg0, s32 arg1, s32 *arg2, s32 *arg3, s32 arg6, s32 arg7, u16 *arg8) {
    if (arg0->unk24 != 0) {
        arg0->unk24 = 0;
    }
    *arg3 = 64;
    if (D_800CC37D || (*arg2 == 0)) {
        *arg2 = 0;
        *arg8 = 0;
        return 0;
    }
    arg0->unk18 -= D_800BE9E4;
    if (arg0->unk18 > 0) {
        *arg2 = 0;
        *arg8 = 0;
    } else {
        arg0->unk18 = (func_150ADA20() & 0x7F) + 0x80;
        arg0->unk0 = (func_150ADA20() % 3U) + 0x6C;
    }
    return 0;
}

s32 func_1000EBC4(struct00 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 temp_v0 = arg0->unkC;
    s32 temp_v1 = arg0->unk18;
    temp_v1 -= D_800BE9E4;

    if (temp_v1 <= 0) {
        temp_v0 = temp_v0 - D_800BE9E4 * 1000;
        if (temp_v0 < 0) {
            return 1;
        }
        arg0->unkC = temp_v0;
    }
    arg0->unk18 = temp_v1;
    return 0;
}

s32 func_1000EC24(struct251 *arg0, s32 arg1, s32 *arg2, struct11 *arg3, struct04 *arg4, s32 *arg5, u16 *arg6) {
    s16 temp_v1 = arg0->unk18.h[1];

    if (*arg6 != 0) {
        arg0->unk1C = *arg6;
        arg0->unk0 = 0;
        *arg6 = 0;
    }

    temp_v1 -= D_800BE9E4;

    if (temp_v1 <= 0) {
        if (*arg2 != 0) {
            func_10010F30(arg0->unk1C, *arg2, arg3->unk3, arg4->unk2, *arg5);
        }
        return 1;
    }
    arg0->unk18.w = temp_v1;
    return 0;
}

s32 func_1000ECCC(struct_init_EB00_1000ECCC *arg0, s32 arg1, s32 arg2, s32 arg3,
                  s32 arg4, s32 arg5, u16 *arg6) {
    s16 temp_a1;
    s16 temp_t4;
    s32 temp_v1;

    temp_v1 = arg0->unk18.w;
    temp_a1 = temp_v1;
    if (*arg6 != 0) {
        arg0->unk18.w = (*arg6 << 16) | (temp_v1 & 0xFFFF);
        arg0->unk0 = 0;
        *arg6 = 0;
        temp_v1 = arg0->unk18.w;
    }

    temp_a1 -= D_800BE9E4;
    temp_t4 = temp_v1 >> 16;
    if (temp_a1 <= 0) {
        *arg6 = temp_t4;
        arg0->unk0 = temp_t4;
        if (func_10010894(arg0->unk1C) == 0) {
            func_10010344(*arg6, arg0->unk1C, arg0->unkC, arg0->unkA, arg0->unk8);
        }
        return 1;
    }

    arg0->unk18.w = (temp_v1 & 0xFFFF0000) | temp_a1;
    return 0;
}
// ? func_1000ECCC(void *arg0, ? arg1, ? arg2, ? arg3, void *arg6) {
//     s16 temp_a1;
//     s32 temp_t4;
//     s32 temp_v1;
//     u16 temp_v0;
//
//     temp_v1 = arg0->unk18;
//     temp_v0 = *arg6;
//     if (temp_v0 != 0) {
//         arg0->unk18 = (s32) ((temp_v0 << 0x10) | (temp_v1 & 0xFFFF));
//         arg0->unk0 = (u16)0;
//         *arg6 = (u16)0U;
//     }
//     temp_a1 = (s16) temp_v1 - *(void *)0x800BE9E4;
//     if ((s32) temp_a1 <= 0) {
//         temp_t4 = arg0->unk18 >> 0x10;
//         *arg6 = (u16) temp_t4;
//         arg0->unk0 = (s16) temp_t4;
//         if (func_10010894(arg0->unk1C, temp_a1, arg6) == 0) {
//             func_10010344(*arg6, arg0->unk1C, arg0->unkC, arg0->unkA, (?32) arg0->unk8);
//         }
//         return 1;
//     }
//     arg0->unk18 = (s32) ((arg0->unk18 & 0xFFFF0000) | temp_a1);
//     return 0;
// }

// PERMUTER CANDIDATE / JUSTREG (best 65). Byte-perfect instruction stream; the
// hoisted `and (temp_v1 & 0xFFFF0000)` at 0x304 colors to t0 (mine) vs t9 (target),
// shifting every downstream temp by one. Sibling of matched func_1000ECCC; differs
// only by the unguarded func_10010630 call, which perturbs the global coloring.
// Tried OR/AND operand swaps (65/70). Needs permuter to shift the temp rotation.
// s32 func_1000EDA0(struct_init_EB00_1000ECCC *arg0, s32 arg1, s32 arg2, s32 arg3,
//                   s32 arg4, s32 arg5, u16 *arg6) {
//     s16 temp_a1; s16 temp_t4; s32 temp_v1;
//     temp_v1 = arg0->unk18.w;
//     temp_a1 = temp_v1;
//     if (*arg6 != 0) {
//         arg0->unk18.w = (*arg6 << 16) | (temp_v1 & 0xFFFF);
//         arg0->unk0 = 0; *arg6 = 0; temp_v1 = arg0->unk18.w;
//     }
//     temp_a1 -= D_800BE9E4;
//     temp_t4 = temp_v1 >> 16;
//     if (temp_a1 <= 0) {
//         *arg6 = temp_t4; arg0->unk0 = temp_t4;
//         func_10010630(*arg6, arg0->unk1C, arg0->unkC, arg0->unkA, arg0->unk8);
//         return 1;
//     }
//     arg0->unk18.w = (temp_v1 & 0xFFFF0000) | temp_a1;
//     return 0;
// }
#pragma GLOBAL_ASM("asm/nonmatchings/init_EB00/func_1000EDA0.s")

// PERMUTER CANDIDATE (best 1650). Body is byte-correct (float trunc block, all casts
// match: unk1C & 0xFF -> lw+andi, (u32)unk184 -> srl). Blocked by the return-placement /
// branch-likely heuristic (same class as func_1000CDA0, memory: "unfixable from C"):
// target emits `beqzl obj, EPILOGUE; li v0,1` guards (return value in v0 delay slot),
// but IDO gives `bnezl obj, continue` with the next load hoisted into the delay, forcing
// the return value into v1 + a trailing `move v0,v1` that cascades a v0/v1 swap on every
// obj access. Tried early-return / || / single-return-var / inverted-guard: 1650-1990.
// typedef struct { u8 pad0[2]; s16 unk2; s16 unk4; s16 unk6; u8 pad8[0x10];
//     struct127 *unk18; s32 unk1C; u8 pad20[4]; u16 unk24; } struct_init_EB00_EE70;
// s32 func_1000EE70(struct_init_EB00_EE70 *arg0, s32 arg1, s32 *arg2, s32 arg3,
//                   s32 arg4, s32 *arg5) {
//     struct127 *obj = arg0->unk18;
//     if (obj == 0) { return 1; }
//     if (*arg2 == 0) { return 1; }
//     if ((obj->interaction_state != 0) && (obj->unique_id == (arg0->unk1C & 0xFF))) {
//         *arg5 = (((u32) obj->unk184 >> 3) & 0x30) << 1;
//         arg0->unk2 = (s16) obj->x_position;
//         arg0->unk4 = (s16) obj->y_position;
//         arg0->unk6 = (s16) obj->z_position;
//         return 0;
//     }
//     if (func_1000F44C(arg0->unk24) != 0) { return 1; }
//     return 0;
// }
#pragma GLOBAL_ASM("asm/nonmatchings/init_EB00/func_1000EE70.s")

s32 func_1000EF40(struct57 *arg0, struct57 *arg1, s32 *arg2, s32 arg3, s32 arg4, s32 arg5, u16 *arg6) {
    if (arg0->unk10 & 0x80) {
        arg0->unk10 = (s32) (arg0->unk10 & -0x81);
    }
    if (*arg2 == 0) {
        if (arg0->unk24 != 0) {
            func_100111C8(arg0->unk24);
            arg0->unk24 = 0;
        }
        *arg6 = 0;
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/init_EB00/func_1000EFB4.s")
void func_1000F1A8(void) {
    s32 i;

    D_80042760 = 0;
    D_80041FD9 = 1;
    D_80041FD8 = 0;
    bzero(D_800425E0, 0x180);

    for (i = 0; i < 0x10; i++) {
        D_800425E0[i].unk2 = i + 0x10;
    }

    D_80041F50 = 0;
    func_100176EC();
    D_80041F60 = D_80041F61 = 0;
}

void func_10017780(u8 arg0, u16 arg1);
s32* allocate_memory(s32, s32, s32, s32);
void func_1000F248(s32 arg0) {
    u16 tmp;

    func_1000F1A8();
    if (arg0 == 4) {
        D_80041F54 = 0;
        D_80041F58 = D_8002C3F8; // 0.009999999776482582
    } else {
        D_80041F54 = 23000;
        D_80041F58 = D_8002C3FC; // 0.10000000149011612
    }

    if (arg0 == 0x35) {
        D_80041FD9 = 0;
    } else if (arg0 == 0x36) {
        D_80041FD9 = 0;
    } else if (arg0 == 0x3C) {
        D_80041FD9 = 0;
        D_80041FD8 = 0x3C;
    } else if (arg0 == 0x27) {
        D_80041FD9 = 0;
        D_80041FD8 = 0x28;
    } else if ((arg0 == 0x3A) || (arg0 == 0x40)) {
        D_80041FD9 = 0;
        D_80041FD8 = 0x3C;
    }

    D_80041F5C = allocate_memory(1762, 1, 0, 0);

    bzero(D_80041F5C, 1762);

    if (arg0 == 0x31) {
        D_80041FDC = 14000;
    } else {
        D_80041FDC = 23000;
    }
    func_10011E88(arg0);
    D_80041F60 = D_80041F61 = 0;
    func_10017780(0, D_80041F56);
    func_10017780(1, D_80041F56);
    func_10017780(2, 23000);
    // fakematch
    if (arg0) {}
}

s32 func_1000F3D0(u16 arg0) {
    struct120 *temp_v1;

    temp_v1 = &D_800425E0[arg0 & 0xF];
    if (temp_v1->unk8 != 0) {
        if ((temp_v1->unk0 == arg0) || (arg0 == (arg0 & 0xF))) {
            if (func_100173C4(&temp_v1->unk8) != 0) {
                return 1;
            }
        }
    }
    return 0;
}

s32 func_1000F44C(u16 arg0) {
    u32 mask;
    struct120 *temp_a1;
    struct31 *temp_a2;

    mask = __osDisableInt();
    temp_a1 = &D_800425E0[arg0 & 0xF];
    temp_a2 = temp_a1->unk8;
    if ((temp_a2 != 0) && (temp_a1->unk0 == arg0) && ((temp_a2->unk53 & 2) != 0)) {
        __osRestoreInt(mask);
        return 1;
    }
    __osRestoreInt(mask);
    return 0;
}

s32 func_100173C4(struct31 **arg0);
extern struct120 D_800425E0[];
extern struct120 D_800426A0[];
s32 func_1000F4D8(u16 arg0)
{
  struct120 *temp_s0;
  arg0 &= 0x7FFF;
 temp_s0 = D_800425E0; do { if (temp_s0->unk8 != 0) { if ((temp_s0->unk4 & 0x7FFF) == arg0) {
        if (func_100173C4(&temp_s0->unk8) != 0)
        {
          return 1;
        }
      }
    }
    temp_s0++;
  }
  while (temp_s0 != D_800426A0);
  return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/init_EB00/func_1000F568.s")
#pragma GLOBAL_ASM("asm/nonmatchings/init_EB00/func_1000F6B8.s")
typedef struct {
    struct31 *unk0;
    u8 pad4[8];
} struct_init_EB00_425E8;
extern struct_init_EB00_425E8 D_800425E8[];

void func_1000F85C(u16 arg0, s16 arg1, s32 arg2) {
    if (arg0 < 0x10) {
        return;
    }
    if (func_1000F3D0(arg0) != 0) {
        if (arg1 == 0x10) {
            f32 sp1C = alCents2Ratio(arg2);
            arg2 = *(s32 *)&sp1C;
        } else if (arg1 == 0x11) {
            arg1 = 0x10;
        }
        func_10017714((s32) D_800425E8[arg0 & 0xF].unk0, arg1, arg2);
    }
}

void func_1000F91C(u16 arg0, u16 arg1, s16 arg2, u8 arg3, s32 arg4,
                   s16 arg5, s16 arg6, s16 arg7, s16 arg8, s16 arg9) {
    s32 sp2C;
    s32 tmp = func_1000F6B8(arg4, arg5, arg6, arg7, &sp2C, (s32) arg8, (s32) arg9);

    func_1000F85C(arg0, 8, (u32) (tmp * arg1) >> 0xF);
    func_1000F85C(arg0, 4, sp2C & 0x7F);
    func_1000F85C(arg0, 256, (sp2C & 0x80) | arg3);
    func_1000F85C(arg0, 16, arg2);
}

void func_1000F9D4(u16 arg0, s16 arg1, s16 arg2, s16 arg3) {
    u32 tmp;

    func_1000F6B8(-1, arg1, arg2, arg3, &tmp, 32760, 32765);
    func_1000F85C(arg0, 4, tmp & 0x7F);
    func_1000F85C(arg0, 256, tmp & 0x80);
}

u16 func_1000FA64(u16 arg0, s16 arg1, s16 arg2, s16 arg3, s32 arg4,
                  u16 arg5, s16 arg6, s32 arg7, void *arg8, s32 arg9,
                  s32 argA, s32 argB) {
    s32 sp24;
    register s32 temp_a2;

    if (D_80042760 < 0x20) {
        temp_a2 = D_80042760;
        D_80042760++;
    } else {
        return 0;
    }

    if (arg7 != 0) {
        D_80041FE0[temp_a2].unk10 = argA | 0x12;
    } else {
        D_80041FE0[temp_a2].unk10 = (argA & 0x108) | 2;
    }

    if (argA & 0x40) {
        arg2 = func_15083E0C((u8)arg1);
        if (arg2 == -1) {
            return 0;
        }
    }

    D_80041FE0[temp_a2].unk24 = 0;
    *((u8 *)&D_80041FE0[temp_a2] + 0x23) = 0;
    *((u8 *)&D_80041FE0[temp_a2] + 0x22) = 0;
    *((u16 *)&D_80041FE0[temp_a2] + 0) = arg0;
    *((s16 *)&D_80041FE0[temp_a2] + 1) = arg1;
    *((s16 *)&D_80041FE0[temp_a2] + 2) = arg2;
    *((s16 *)&D_80041FE0[temp_a2] + 3) = arg3;
    *((u16 *)&D_80041FE0[temp_a2] + 4) = arg5;
    *((s16 *)&D_80041FE0[temp_a2] + 5) = arg6;
    D_80041FE0[temp_a2].unkC = arg4;
    D_80041FE0[temp_a2].unk14 = arg7;
    D_80041FE0[temp_a2].unk18 = (s32)arg8;
    D_80041FE0[temp_a2].unk1C = arg9;
    *(f32 *)&D_80041FE0[temp_a2].unk2C = alCents2Ratio(argB);
    D_80041FE0[temp_a2].unk26 = 0;
    *(u16 *)&D_80041FE0[temp_a2].unk28 = 0;
    *(s16 *)&D_80041FE0[temp_a2].unk20 = argB;
    sp24 = D_80042760;
    func_10011624(D_80041FE0, &D_80042760, temp_a2, temp_a2 + 1);
    if (sp24 == D_80042760) {
        D_80041FE0[temp_a2].unk10 |= 0x1000;
        return D_80041FE0[temp_a2].unk24;
    }
    return 0;
}
// PERMUTER CANDIDATE (best 280). Everything matches (arg promotion s2-s6, all 5 bnel
// field compares incl. operand order, the func_100111C8 guard, unk10|=0x80) EXCEPT the
// D_80042760 count reload placement after the call: target sinks it call-path-only (merge
// at the ori), IDO puts it at the merge so the beqzl skip-path reloads count too. Pointer
// vs base[i] indexing: 520 vs 280; for/do-while/operand-order all tried. Reload-sink heuristic.
// typedef struct { u16 unk0; s16 unk2; s16 unk4; s16 unk6; u16 unk8; u8 padA[6];
//     s32 unk10; u8 pad14[0x10]; u16 unk24; u8 pad26[0xA]; } struct_init_EB00_FC18;
// void func_1000FC18(u16 arg0, s16 arg1, s16 arg2, s16 arg3, u16 arg4) {
//     struct_init_EB00_FC18 *base = (struct_init_EB00_FC18 *) D_80041FE0;
//     s32 i;
//     for (i = 0; i < D_80042760; i++) {
//         if ((base[i].unk0 == arg0) && (arg1 == base[i].unk2) && (arg2 == base[i].unk4) &&
//             (arg3 == base[i].unk6) && ((base[i].unk8 & 0x7FFF) == arg4)) {
//             if (base[i].unk24 != 0) { func_100111C8(base[i].unk24); }
//             base[i].unk10 |= 0x80;
//         }
//     }
// }
#pragma GLOBAL_ASM("asm/nonmatchings/init_EB00/func_1000FC18.s")
void func_1000FD38(s32 arg0, s32 arg1, s32 arg2) {
    s32 i;

    for (i = 0; i < D_80042760; i++) {
        if ((arg0 == D_80041FE0[i].unk14) && (arg1 == D_80041FE0[i].unk18) &&
            (arg2 == D_80041FE0[i].unk1C)) {
            if (D_80041FE0[i].unk24 != 0) {
                func_100111C8(D_80041FE0[i].unk24);
            }
            D_80041FE0[i].unk10 |= 0x80;
        }
    }
}
// PERMUTER CANDIDATE / JUSTREG (best 40). The index form below is byte-perfect in
// structure, ordering, and every other register EXCEPT the loop count D_80042760:
// target keeps it in v0 (blez/slt/reload), IDO gives mine v1. Pure caller-saved
// coloring; resisted for/while/reversed-compare/explicit-guard/do-while forms (all 40)
// and a fn-ptr-cast (682, adds addr load). Needs the permuter to flip v0<->v1.
void func_1000FDF4(u16 arg0) {
    s32 i;
    struct15 *temp;
    for (i = 0; i < D_80042760; i++) {
        if (D_80041FE0[i].unk24 == arg0) {
            if ((temp = D_80041FE0)[i].unk24) {
                func_100111C8(D_80041FE0[i].unk24);
            }
            D_80041FE0[i].unk10 |= 0x80;
        }
    }
}
s32 func_1000FE88(struct15 *arg0, s32 arg1, s32 *arg2) {
    if (arg1 < *arg2) {
        if (((struct15 *)((u8 *)arg0 + (arg1 * 0x30)))->unk24 != 0) {
            func_100111C8(((struct15 *)((u8 *)arg0 + (arg1 * 0x30)))->unk24);
        }
        ((struct15 *)((u8 *)arg0 + (arg1 * 0x30)))->unk10 |= 0x80;
        return 0;
    }
    return 1;
}
// ? func_1000FE88(s32 arg0, s32 arg1, void *arg2) {
//     void *sp1C;
//     s32 temp_t7;
//     u16 temp_a0;
//     void *temp_v1;
//     ? phi_return;
//
//     phi_return = 1;
//     if (arg1 < *arg2) {
//         temp_t7 = arg1 * 0x30;
//         temp_v1 = arg0 + temp_t7;
//         temp_a0 = temp_v1->unk24;
//         if (temp_a0 != 0) {
//             sp1C = temp_v1;
//             func_100111C8(temp_a0, arg0);
//         }
//         (arg0 + temp_t7)->unk10 = (s32) ((arg0 + temp_t7)->unk10 | 0x80);
//         phi_return = 0;
//     }
//     return phi_return;
// }

s32 func_1000FEF0(u16 arg0, void *arg1, s32 arg2) {
    u16 id;
    s32 i;

    if (!arg0) {
        return -1;
    }
    for (i = 0; i < D_80042760; i++) {
        if ((arg0 == (*(&D_80041FE0[i])).unk24) && ((s32) arg1 == D_80041FE0[i].unk18) &&
            (arg2 == D_80041FE0[i].unk1C) && ((D_80041FE0[i].unk10 & 0x80) == 0)) {
            return i;
        }
    }
    return -1;
}

s32 func_1000FF90(s32 arg0, s32 arg1, s32 arg2) {
    s32 i;

    for (i = 0; i < D_80042760; i++) {
        if ((arg0 == D_80041FE0[i].unk14) &&
            ((arg1 == D_80041FE0[i].unk18) || (arg1 == -1)) &&
            ((arg2 == D_80041FE0[i].unk1C) || ((u32) arg2 == 0xFFFFFFFFU)) &&
            ((D_80041FE0[i].unk10 & 0x80) == 0)) {
            return i;
        }
    }
    return -1;
}
void func_1001001C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 i;
    struct15 *tmp;

    tmp = D_80041FE0;
    i = 0;
    if (D_80042760 > 0) {
        do {
            if ((arg0 == tmp->unk14) && (arg1 == tmp->unk18) && (arg2 == tmp->unk1C)) {
                *(f32 *)&tmp->unk2C = alCents2Ratio(arg4);
                tmp->unkC = arg3;
            }
            i++;
            tmp++;
        } while (i < D_80042760);
    }
}
void func_100100E0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    s32 count;
    struct15 *p;

    p = D_80041FE0;
    count = D_80042760;
    if (count > 0) {
        p = D_80041FE0;
        do {
            if ((arg0 == p->unk14) && (arg1 == p->unk18) && (arg2 == p->unk1C)) {
                p->unk14 = arg3;
                p->unk18 = arg4;
                p->unk1C = arg5;
            }
            p++;
        } while (p < &D_80041FE0[count]);
    }
}
#pragma GLOBAL_ASM("asm/nonmatchings/init_EB00/func_10010154.s")
#pragma GLOBAL_ASM("asm/nonmatchings/init_EB00/func_10010344.s")

void func_10010558(u16 arg0, struct127 *arg1, s32 arg2, s16 arg3, u16 arg4, s32 arg5) {
    if (arg5 <= 0) {
        func_10010344(arg0, arg1, arg2, arg3, arg4);
    } else {
        func_1000FA64(arg0, arg1->x_position, arg1->y_position, arg1->z_position, arg2, arg4, arg3, func_1000ECCC, arg5, arg1, 0, 0);
    }
}

// PERMUTER CANDIDATE (best 2084). Arg mapping / all casts byte-correct. Blocked by a
// register-allocation divergence: target promotes arg2 to saved reg s1 (2 saved regs)
// and schedules the func_1000EE70 %hi/%lo address late (inside the else); IDO keeps arg2
// on the stack (1 saved reg, reloads it) and hoists the address into the camera branch,
// cascading every temp + float register. Local-copy of arg2 didn't force promotion.
// void func_10010630(u16 arg0, struct127 *arg1, s32 arg2, s16 arg3, u16 arg4) {
//     if (arg1->interaction_state != 0) {
//         if (arg1->camera != 0) {
//             func_10010F30(arg0, arg2 & 0xFFFF, 64, 0, (((u32) arg1->unk184 >> 3) & 0x30) * 2);
//         } else {
//             func_1000FA64(arg0, arg1->x_position, arg1->y_position, arg1->z_position, arg2,
//                           arg4, arg3, (void *) func_1000EE70, arg1, arg1->unique_id, 0, 0);
//         }
//     }
// }
#pragma GLOBAL_ASM("asm/nonmatchings/init_EB00/func_10010630.s")

void func_10010720(u16 arg0, struct127 *arg1, s32 arg2, s16 arg3, u16 arg4, s32 arg5) {
    if (arg5 <= 0) {
        func_10010630(arg0, arg1, arg2, arg3, arg4);
    } else {
        func_1000FA64(arg0, arg1->x_position, arg1->y_position, arg1->z_position, arg2, arg4, arg3, func_1000EDA0, arg5, arg1, 0, 0);
    }
}

s32 func_100107F8(struct127 *arg0) {
    if (arg0->interaction_state == 0) {
        return 0;
    } else {
        if (arg0->camera != 0) {
            if (arg0->unk8E != 0) {
                if (func_1000F3D0(arg0->unk8E) != 0) {
                    return 1;
                }
            }
        } else {
            if (func_1000FF90(func_1000EE70, arg0, arg0->unique_id | 0x10000) != -1) {
                return 1;
            }
        }
        arg0->unk8E = 0;
    }
    return 0;
}

s32 func_10010894(struct127 *arg0) {
    if (arg0->camera != 0) {
        if (arg0->unk8C != 0) {
            if (func_1000F3D0(arg0->unk8C) != 0) {
                return 1;
            }
        }
    } else {
        if (func_1000FF90(func_1000EE70, arg0, arg0->unique_id | 0x20000) != -1) {
            return 1;
        }
    }
    arg0->unk8C = 0;
    return 0;
}

void func_1001091C(struct127 *arg0, struct15 *arg1) {
    s32 temp_v0;

    if ((arg1 != 0) && (arg0->interaction_state != 0)) {
        if (arg0->camera != 0) {
            if (arg0->unk8E != 0) {
                func_1000F85C(arg0->unk8E, 8, *(s32 *) &arg1);
            }
        } else {
            temp_v0 = func_1000FF90((s32) func_1000EE70, (s32) arg0, arg0->unique_id | 0x10000);
            if (temp_v0 != -1) {
                D_80041FEC[temp_v0][0] = (s32) arg1;
            } else {
                arg0->unk8E = 0;
            }
        }
    }
}
// NON-MATCHING: something isnt right...
// void func_1001091C(struct127 *arg0, struct15 *arg1) {
//     s32 temp_v0;
//
//     if ((arg1 != NULL) && (arg0->unk0 != 0)) {
//         if (arg0->camera != 0) {
//             if (arg0->unk8E != 0) {
//                 func_1000F85C(arg0->unk8E, 8, arg1->unk1C); // help
//             }
//         } else {
//             temp_v0 = func_1000FF90(func_1000EE70, arg0, arg0->unique_id | 0x10000);
//             if (temp_v0 != -1) {
//                 D_80041FEC[temp_v0][0] = arg1;
//             } else {
//                 arg0->unk8E = 0;
//             }
//         }
//     }
// }

void func_100109D0(struct127 *arg0) {
    if (arg0->camera) {
        if (arg0->unk8E) {
            func_100111C8(arg0->unk8E);
        }
    } else {
        func_1000FD38(func_1000EE70, arg0, arg0->unique_id | 0x10000);
    }
    arg0->unk8E = 0;
}

void func_10010A3C(struct127 *arg0) {
    if (arg0->camera) {
        if (arg0->unk8C) {
            func_100111C8(arg0->unk8C);
        }
    } else {
        func_1000FD38(func_1000EE70, arg0, arg0->unique_id | 0x20000);
    }
    arg0->unk8C = 0;
}

void func_10010AA8(struct127 *arg0) {
    s32 sp24;
    struct15 *tmp;

    if (arg0->camera != 0) {
        if (arg0->unk8C && func_1000F44C(arg0->unk8C)) {
            func_100111C8(arg0->unk8C);
        }
        if (arg0->unk8E && func_1000F44C(arg0->unk8E)) {
            func_100111C8(arg0->unk8E);
        }
    } else {
        sp24 = func_1000FEF0(arg0->unk8C, arg0, arg0->unique_id);
        if (sp24 != -1) {
            if (func_1000F44C(arg0->unk8C)) {
                func_100111C8(arg0->unk8C);
            }
            tmp = &D_80041FE0[sp24];
            tmp->unk10 |= 0x80;
        }
        sp24 = func_1000FEF0(arg0->unk8E, arg0, arg0->unique_id);
        if (sp24 != -1) {
            if (func_1000F44C(arg0->unk8E)) {
                func_100111C8(arg0->unk8E);
            }
            tmp = &D_80041FE0[sp24];
            tmp->unk10 |= 0x80;
        }
    }
    arg0->unk8C = 0;
    arg0->unk8E = 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/init_EB00/func_10010BE8.s")

s32 func_10010E78(s32 arg0, s32 arg1, u16 arg2, s16 arg3, u8 arg4,
                  s32 arg5, s16 arg6, s16 arg7, s16 arg8, s16 arg9,
                  s16 argA) {
    s32 sp2C;
    u32 temp_t1;

    temp_t1 = func_1000F6B8(arg5, arg6, arg7, arg8, &sp2C, (s32) arg9, (s32) argA);
    temp_t1 = (u32) (arg2 * temp_t1) >> 0xF;
    if (temp_t1 != 0) {
        return func_10010BE8((u16) arg0, arg1, temp_t1, sp2C & 0x7F, arg3, (sp2C & 0x80) | arg4, D_80041FD9);
    }
    return 0;
}

void func_10010F30(s32 arg0, u16 arg1, u8 arg2, s16 arg3, u8 arg4) {
    func_10010BE8(0, arg0, arg1, arg2, arg3, arg4, D_80041FD9);
}

void func_10010F88(s32 arg0, u16 arg1, s16 arg2, u8 arg3, s32 arg4,
                   s16 arg5, s16 arg6, s16 arg7, s16 arg8, s16 arg9) {
    func_10010E78(0, arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9);
}
#pragma GLOBAL_ASM("asm/nonmatchings/init_EB00/func_10010FFC.s")

void func_100111C8(u16 arg0) {
    struct120 *tmp = &D_800425E0[arg0 & 0xF];

    if ((tmp->unk8 != 0) && (tmp->unk0 == arg0)) {
        tmp->unk0 = 0;
        tmp->unk4 = 0;
        func_10017594(tmp->unk8);
        tmp->unk8 = 0;
    }
}

void func_1001123C(u16 arg0) {
    struct120 *tmp = &D_800425E0[arg0 & 0xF];

    if ((tmp->unk8 != 0) && (tmp->unk0 == arg0)) {
        if (func_100112BC(arg0, 1) == 0) {
            func_10017594(tmp->unk8);
            tmp->unk8 = 0;
        }
    }
}

s32 func_100112BC(s32 arg0, s32 arg1) {
    struct49 *temp_a0;
    s32 temp_v1 = D_80041F50;

    if (temp_v1 < 16) {
        temp_a0 = &D_80041F10[temp_v1];
        temp_a0->unk0 = arg0;
        temp_a0->unk2 = arg1;
        temp_a0->unk3 = arg0 & 0xF;
        D_80041F50 = temp_v1 + 1;
        return 1;
    } else {
        return 0;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/init_EB00/func_10011310.s")

s32 func_1001147C(u16 arg0) {
    struct120 *tmp;

    if (arg0 != 0) {
        tmp = &D_800425E0[arg0 & 0xF];
        if (tmp->unk0 == arg0) {
            return tmp->unk4 & 0x7FFF;
        }
    }
    return -1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/init_EB00/func_100114D0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/init_EB00/func_10011624.s")
#pragma GLOBAL_ASM("asm/nonmatchings/init_EB00/func_10011BB8.s")

void func_10011E88(s32 arg0) {
}

void func_10011E94(s32 arg0) {
    if (arg0) {
        D_80041F61 = 1;
    } else {
        D_80041F61 = 0;
    }
}

u16 func_10011EB8(s32 arg0, s16 *arg1, s32 arg2) {
    register s32 temp_a3;
    struct_init_EB00_10011EB8_pair *entry;
    s32 temp_a0;

    temp_a3 = arg0;
    temp_a3 = func_1510F8CC(temp_a3 | 0);

    if (arg1 != NULL) {
        if (D_80082FA0 != 0) {
            *arg1 = 0x7FFF / (D_80082FA0 + 1);
        } else {
            *arg1 = 0x7FFF;
        }
    }

    entry = &((struct_init_EB00_10011EB8_row *) D_8002C240)[temp_a3].unk0[arg2];
    temp_a0 = entry->unk0;
    if (entry->unk2 >= 2) {
        temp_a0 = func_1000F568(temp_a0, ((struct_init_EB00_10011EB8_row *) D_8002C240)[temp_a3].unk0[arg2].unk2);
    }
    return temp_a0;
}
