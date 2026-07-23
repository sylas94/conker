#include <ultra64.h>

#include "functions.h"
#include "variables.h"

struct struct1501A764Sub {
    u8 pad0[4];
    s16 unk4;
    u8 pad6[6];
    s16 unkC;
    u8 padE[2];
};

struct struct1501A764 {
    u8 pad0[0xC];
    f32 unkC;
    f32 unk10;
    u8 pad14[0x20];
    f32 unk34;
    f32 unk38;
    u8 pad3C[0x144];
};

struct struct1501A764c {
    u8 pad0[0x40];
    struct struct1501A764Sub unk40[1];
    u8 pad50[0x130];
};


void func_1501A220(s32 arg0, s32 arg1) {
    s32 phi_s0;
    s32 i;
    s32 var_s1;
    f32 temp_f0;
    f32 temp_f2;
    s32 temp_f16;

    D_80082FA0 = arg0;
    var_s1 = D_80082FA0;

    if (var_s1 == 0) {
        phi_s0 = 1;
    } else {
        phi_s0 = var_s1 + 2;
    }

    D_800BE628 = allocate_memory(phi_s0 * 0x180, 1, 1, 0);
    D_800BE62C = allocate_memory(phi_s0 * 16, 1, 1, 0);

    if (D_80082FA0 == 1) {
        temp_f0 = (f32)D_800BE63C[0] - 2.0f;
        temp_f2 = temp_f0;
        temp_f2 *= *(f32 *)&D_800968E0;
        temp_f16 = temp_f2;
        D_800BE6B8 = (f32)(temp_f16 - (temp_f16 % 4)) / temp_f0;
    }

    func_150006E0(D_800BE9F0);

    var_s1 = D_80082FA0;
    i = 0;
    if (var_s1 >= 0) {
        do {
            func_1501A8C0(i, var_s1, 1023, 0);
            var_s1 = D_80082FA0;
            i++;
        } while (i <= var_s1);
    }

    if (var_s1 != 0) {
        func_1501A8C0(i, 0, 1023, 0);
    }

    D_800BE617 = 1;
    D_800BE614 = 1;
    D_800BE635 = 0;
    func_1510B070(arg1);
}
// NON-MATCHING: 80% there
// void func_1501A220(s32 arg0, s32 arg1) {
//     s32 phi_s0;
//     s32 i;
//
//     f32 temp_f0;
//     s32 temp_f16;
//
//     D_80082FA0 = arg0;
//
//     if (arg0 == 0) {
//         phi_s0 = 1;
//     } else {
//         phi_s0 = arg0 + 2;
//     }
//     D_800BE628 = allocate_memory((phi_s0 * 3) << 7, 1, 1, 0);
//     D_800BE62C = allocate_memory(phi_s0 * 16, 1, 1, 0);
//     if (D_80082FA0 == 1) {
//         temp_f0 = D_800BE63C - 2.0f;
//         temp_f16 = temp_f0 * D_800968E0;
//         phi_s0 = temp_f16 & 3;
//         if ((temp_f16 < 0) && ((temp_f16 & 3) != 0)) {
//             phi_s0 -= 4;
//         }
//         D_800BE6B8 = (temp_f16 - phi_s0) / temp_f0;
//     }
//
//     func_150006E0(D_800BE9F0);
//
//     for(i = 0; i <= D_80082FA0; i++) {
//         func_1501A8C0(i, D_80082FA0, 1023, 0);
//     }
//     if (D_80082FA0 != 0) {
//         func_1501A8C0(i, 0, 1023, 0);
//     }
//
//     D_800BE617 = 1;
//     D_800BE614 = 1;
//     D_800BE635 = 0;
//     func_1510B070(arg1);
// }

#pragma GLOBAL_ASM("asm/nonmatchings/game_476D0/func_1501A39C.s")
// PERMUTER CANDIDATE: reconstruction below scores 30 — byte-identical EXCEPT two adjacent,
// independent increments (`addiu v1,v1,4` D_800BE9C8-walk vs `addiu v0,v0,8` g) are emitted in
// the opposite order. A for-loop `i<2` schedules them correctly but derives the loop terminal as
// `D_800BE9D8+0x8` (wrong reloc; target references symbol D_800BE9E0). Only a do-while with an
// explicit `!= &D_800BE9E0` bound yields the D_800BE9E0 reloc with no guard, but that form
// schedules the D_800BE9C8 induction increment last. The two constraints conflict from C source.
// permuter NO ZERO, best 30
// extern Gfx *D_800BE9C8[];
// extern Gfx D_8002C930[];
// void func_1501A39C(void) {
//     Gfx *g;
//     s32 i = 0;
//     do {
//         g = D_800BE9C8[i];
//         gSPSegment(g++, 0, 0);
//         gSPSegment(g++, 0, 0);
//         gSPDisplayList(g++, D_8002C930);
//         gDPSetDepthImage(g++, D_800BE9C4);
//         gSPViewport(g++, (Vp *)((u8 *)D_800BE628 + i * 0x10 + 0x40));
//         i++;
//         D_800BE9D8[i - 1] = (s32)g;
//     } while (&D_800BE9E0 != &D_800BE9D8[i]);
// }

#pragma GLOBAL_ASM("asm/nonmatchings/game_476D0/func_1501A490.s")
// PERMUTER CANDIDATE: reconstruction below is semantically correct (build OK, most instrs match,
// a1/a2/a3 homing reproduced) but scores 1734 — IDO keeps the Gfx pointer in a temp + stack spill
// across the func_1501AF44 call, whereas the target dedicates saved register s0 to it (gdl crosses
// the call on only the else-path, so IDO picks spill over a callee-saved reg; not forceable from C).
// void func_1501AF44(f32 *arg0, f32 *arg1, f32 *arg2, f32 *arg3);
// s32 func_1501A490(s32 arg0, s16 idx, s32 a2, s32 a3, s32 arg4, s32 arg5) {
//     Gfx *gdl = (Gfx *)arg0;
//     struct259 *s;
//     f32 ulx, lrx, uly, lry;
//     gDPPipeSync(gdl++);
//     if (idx == 0xFF) {
//         gDPSetScissor(gdl++, arg5, 2, 0, D_800BE620 - 2, D_800BE624);
//     } else {
//         s = &((struct259 *)D_800BE628)[idx];
//         ulx = *(f32 *)((u8 *)s + 0x2C);
//         lrx = *(f32 *)((u8 *)s + 0x30);
//         uly = *(f32 *)((u8 *)s + 0x24);
//         if (arg4 != 0) {
//             if ((f32)arg4 < *(f32 *)((u8 *)s + 0x28)) { lry = (f32)arg4; }
//             else { lry = *(f32 *)((u8 *)s + 0x28); }
//         } else { lry = *(f32 *)((u8 *)s + 0x28); }
//         func_1501AF44(&ulx, &uly, &lrx, &lry);
//         gDPSetScissor(gdl++, arg5, ulx, uly, lrx, lry);
//     }
//     return (s32)gdl;
// }

Gfx *func_1501A680(Gfx *arg0) {
    gDPSetColorImage(arg0++, G_IM_FMT_RGBA, G_IM_SIZ_16b, D_800BE620, D_8002AAE8[D_800BE9C0]);
    return arg0;
}

Gfx *func_1501A6CC(Gfx *arg0, s32 a, s32 b, s32 c, s32 d) {
    if (a < 3) {
        a = 2;
    }
    if (b <= 0) {
        b = 0;
    }
    if (c >= (D_800BE620 - 2)) {
        c = D_800BE620 - 2;
    }
    if (d >= D_800BE624) {
        d = D_800BE624;
    }

    gDPFillRectangle(arg0++, a, b, c, d);
    return arg0;
}

void func_150A7A00(s32 arg0, f32 arg1, f32 arg2, f32 arg3, f32* arg4, f32* arg5, f32* arg6, f32* arg7);
void func_1501A764(s16 arg0, f32 arg1, f32 arg2, f32 arg3, f32 *arg4, f32 *arg5, f32 *arg6) {
    f32 sp34;
    f32 sp30;
    f32 sp2C;
    f32 sp28;

    func_150A7A00((s32)((u8 *)&D_800D9D10 + (arg0 << 6)), arg1, arg2, arg3, &sp34, &sp30, &sp2C, &sp28);
    sp28 = 1.0f / sp28;
    *arg4 = (((struct struct1501A764 *)D_800BE628)[arg0].unk34 + (((struct struct1501A764 *)D_800BE628)[arg0].unkC + 5.0f) * sp34 * sp28);
    *arg5 = (((struct struct1501A764 *)D_800BE628)[arg0].unk38 - ((((struct struct1501A764 *)D_800BE628)[arg0].unk10 + 5.0f) * sp30 * sp28));
    *arg6 = (((sp2C * sp28) * (f32)((struct struct1501A764c *)D_800BE628)[arg0].unk40[D_800BE9C0].unk4) + (f32)((struct struct1501A764c *)D_800BE628)[arg0].unk40[D_800BE9C0].unkC) * 32.0f;
}
// void func_1501A764(s16 arg0, f32 arg1, f32 arg2, f32 arg3, f32 *arg4, f32 *arg5, f32 *arg6) {
//     f32 sp34;
//     f32 sp30;
//     f32 sp2C;
//     f32 sp28;
//     struct140 *temp_v0_2;
//
//     func_150A7A00(arg1, arg2, &D_800D9D10 + (arg0 << 6), arg1, arg2, arg3, &sp34, &sp30, &sp2C, &sp28);
//     sp28 = 1.0f / sp28;
//     // temp_v1 = arg0 * 0x180;
//     temp_v0_2 = &D_800BE628[arg0];
//     // sp28 = temp_f8;
//     *arg4 = (((temp_v0_2->unkC + 5.0f) * sp34 * sp28) + temp_v0_2->unk34);
//     temp_v0_2 = &D_800BE628 [arg0];
//     *arg5 = (temp_v0_2->unk38 - ((temp_v0_2->unk10 + 5.0f) * sp30 * sp28));
//     temp_v0_2 = &D_800BE628[arg0].unk50[D_800BE9C0];  // (D_800BE9C0 * 0x10);
//     *arg6 = (((f32) temp_v0_2->unk4C + (sp2C * sp28 * (f32) temp_v0_2->unk44)) * 32.0f);
// }

#pragma GLOBAL_ASM("asm/nonmatchings/game_476D0/func_1501A8C0.s")

s32 func_1501AE94(s32 arg0) {
    f32 a = (f32)D_800BE620 - 2.0f;
    f32 b = (f32)D_800BE624;
    struct259 *p = &((struct259 *)D_800BE628)[arg0];
    if (*(f32 *)((u8 *)p + 0x2C) < 2.0f) {
        goto block1;
    }
    if (a < *(f32 *)((u8 *)p + 0x30)) {
    block1:
        return 0;
    }
    if (*(f32 *)((u8 *)p + 0x24) < 0.0f) {
        goto block2;
    }
    if (b < *(f32 *)((u8 *)p + 0x28)) {
    block2:
        return 0;
    }
    return 1;
}

void func_1501AF44(f32 *arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    f32 t;

    if (*arg0 < 2.0f) {
        *arg0 = 2.0f;
    } else {
        if (((f32)D_800BE620 - 2.0f) < *arg0) {
            t = (f32)D_800BE620 - 2.0f;
        } else {
            t = *arg0;
        }
        *arg0 = t;
    }

    if (*arg2 < 2.0f) {
        *arg2 = 2.0f;
    } else {
        if (((f32)D_800BE620 - 2.0f) < *arg2) {
            t = (f32)D_800BE620 - 2.0f;
        } else {
            t = *arg2;
        }
        *arg2 = t;
    }

    if (*arg1 < 0.0f) {
        *arg1 = 0.0f;
    } else {
        if ((f32)D_800BE624 < *arg1) {
            t = (f32)D_800BE624;
        } else {
            t = *arg1;
        }
        *arg1 = t;
    }

    if (*arg3 < 0.0f) {
        *arg3 = 0.0f;
    } else {
        if ((f32)D_800BE624 < *arg3) {
            t = (f32)D_800BE624;
        } else {
            t = *arg3;
        }
        *arg3 = t;
    }
}

// PERMUTER CANDIDATE: reconstruction below is semantically correct (build OK) and scores 275 with
// matching stack slots — the ONLY diff is a 2-instruction scheduler reorder: the target hoists the
// shared D_800968F4 load to the top of the function; IDO here loads it at the first multiply.
// (Hoisting it via a named local fixes the order but adds a -g3 debug slot that shifts every other
// slot by 4, netting 200 — worse. Not resolvable from C source; scheduler decision.)
// permuter NO ZERO, best 275 (re-run 600s, no improvement; -g3 debug-slot blocks C hoist)
#pragma GLOBAL_ASM("asm/nonmatchings/game_476D0/func_1501B0A0.s")
// extern f32 D_800968F4, D_800968F8, D_800968FC;
// extern void func_1510B128(s32, f32, f32, f32, f32);
// void func_1501B0A0(s32 arg0, s32 arg1) {
//     f32 ang1 = *(f32 *)((u8 *)&((struct259 *)D_800BE628)[arg0] + 0x6C) * D_800968F4;
//     f32 ang2 = *(f32 *)((u8 *)&((struct259 *)D_800BE628)[arg0] + 0x70) * D_800968F4;
//     f32 tan1 = sinf(ang1) / cosf(ang1);
//     f32 tan2 = sinf(ang2) / cosf(ang2);
//     f32 v14 = (f32)(&D_800BE638)[arg1] / (tan1 + tan1);
//     f32 v38 = (f32)(&D_800BE650)[arg1] / (tan2 + tan2);
//     f32 r1 = func_150484A0(*(f32 *)((u8 *)&((struct259 *)D_800BE628)[arg0] + 0xC),  v14) * D_800968F8 - *(f32 *)((u8 *)&((struct259 *)D_800BE628)[arg1] + 0x6C);
//     f32 r2 = func_150484A0(*(f32 *)((u8 *)&((struct259 *)D_800BE628)[arg0] + 0x10), v38) * D_800968FC - *(f32 *)((u8 *)&((struct259 *)D_800BE628)[arg1] + 0x70);
//     func_1510B128(arg0, r1, r2, 1.0f, 0.0f);
// }

#pragma GLOBAL_ASM("asm/nonmatchings/game_476D0/func_1501B22C.s")
// PERMUTER CANDIDATE: reconstruction below is semantically exact (build OK) but scores 954 —
// pure register-allocation near-miss. Block2's zero-constant lands in f12 not f14 and cos reloads
// to a different slot (0x20 vs target 0x34, which the target reuses from block1), cascading into
// store reordering; also a t6/t7 swap on the base-pointer add. Codegen is identical regardless of
// C form (merged/separate locals, inline/assigned negations).
// void func_1501B22C(s32 arg0) {
//     struct259 *temp = &((struct259 *)D_800BE628)[arg0];
//     f32 half74 = temp->unk74 * 0.5f;
//     f32 half78 = temp->unk78 * 0.5f;
//     f32 ang, cv, sv;
//     ang = -half74 * D_80096900;
//     cv = cosf(ang);  sv = sinf(ang);
//     temp->unk9C = sv;  temp->unk90 = sv;
//     cv = -cv;  temp->unk94 = cv;  temp->unk88 = -cv;
//     temp->unk98 = 0.0f;  temp->unk8C = 0.0f;
//     ang = half78 * D_80096904;
//     cv = cosf(ang);  sv = sinf(ang);
//     temp->unkA0 = 0.0f;  temp->unkA8 = -sv;  temp->unkB4 = -sv;
//     temp->unkAC = 0.0f;  temp->unkA4 = -cv;  temp->unkB0 = cv;
// }
// JUSTREG: I think?
// void func_1501B22C(s32 arg0) {
//     f32 tmp0;
//     f32 tmp1;
//     f32 tmp2;
//     f32 tmp3;
//     f32 tmp4;
//     f32 tmp5;
//     f32 tmp6;
//     f32 tmp7;
//
//     struct259 *temp_s0;
//
//     temp_s0 = D_800BE628 + (arg0 * 0x180);
//     tmp0 = temp_s0->unk74 * 0.5f;
//     tmp7 = -tmp0;
//     tmp5 = temp_s0->unk78 * 0.5f;
//     tmp7 *= D_80096900;
//     tmp3 = cosf(tmp7);
//     tmp7 = sinf(tmp7);
//     temp_s0->unk9C = tmp7;
//     temp_s0->unk90 = tmp7;
//     tmp3 = -tmp3;
//     temp_s0->unk88 = -tmp3;
//     temp_s0->unk94 = tmp3;
//     temp_s0->unk98 = 0.0f;
//     temp_s0->unk8C = 0.0f;
//     tmp6 = tmp5 * D_80096904;
//     tmp2 = cosf(tmp6);
//     tmp0 = sinf(tmp6);
//     tmp4 = -tmp2;
//     tmp0 = -tmp0;
//     temp_s0->unkA0 = 0.0f;
//     temp_s0->unkB0 = -tmp4;
//     temp_s0->unkA8 = tmp0;
//     temp_s0->unkB4 = tmp0;
//     temp_s0->unkAC = 0.0f;
//     temp_s0->unkA4 = tmp4;
// }
