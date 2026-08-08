#include <ultra64.h>

#include "functions.h"
#include "variables.h"

#include "macros.h"

typedef struct func_15002560_node {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    s16 unkC;
} func_15002560_node;

typedef struct Point16 {
    s16 x;
    s16 y;
    s16 z;
} Point16;

typedef struct Face16 {
    Point16 *pts[3];
} Face16;

typedef struct Point32 {
    f32 x;
    f32 y;
    f32 z;
} Point32;

typedef struct Face32 {
    Point32 pts[3];
} Face32;

typedef struct YRange {
    s16 min;
    s16 max;
} YRange;

extern s32 D_800DBE44;

void func_15002560(u16 *arg0, u16 *arg1);
void func_15002008(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u16 *arg4);
s32 func_15049260(Face32 arg0);

void func_15000AC0(void) {
    D_800D9E64 = (u8)0;
}

// jump table
#pragma GLOBAL_ASM("asm/nonmatchings/game_2DF70/func_15000AD0.s")
// loops!
#pragma GLOBAL_ASM("asm/nonmatchings/game_2DF70/func_15001460.s")

void func_15001970(void) {
    s32 pad;
    s32 tmp;

    D_800B0DE4 = 0;
    D_800DBE63 = 0;
    *D_800DBE18 = 0;
    *D_800DBE1C = 0;
    D_800DBE20 = 0;
    tmp = D_80091C04[D_800BE9F0];
    D_800DBE24 = 0;
    D_800B0DC0 = allocate_memory(tmp, 1, 0, 0);
    D_800B0DC8 = tmp + D_800B0DC0;
    D_800B0DC4 = D_800B0DC0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_2DF70/func_15001A08.s")
// NON-MATCHING: JUSTREG
// void func_15001A08(void) {
//     s32 sp24;
//     s32 tmp;
//     s32 sp1C;
//
//     tmp = D_800BE9F0;
//     sp24 = D_80091AF0[tmp];
//
//     __osPiGetAccess();
//
//     while ((IO_READ(PI_STATUS_REG) & 3)) {};
//
//     tmp = D_80000308 | 0xB0000D24 | 0xA0000000;
//     sp1C = *(s32*)tmp;
//
//     __osPiRelAccess();
//
//     if (sp1C != 0x98CCE31A) {
//         sp24 <<= 1;
//     }
//
//     D_800B0DDC = allocate_memory(sp24, 1, 0, 0);
//     D_800B0DE0 = D_800B0DDC;
//     D_800B0DCC = 0;
//     D_800B0DD0 = 0;
//     D_800DBE30 = 0;
//     D_800DBE32 = 0;
//     D_800DBE34 = 0;
//     D_800DBE36 = 0;
// }

u16* func_15001B10(void) {
    u16 *temp_v0;

    D_800B0DE0 = ALIGN4(D_800B0DE0);
    D_800B0DCC += 1;

    temp_v0 = (u16*)D_800B0DE0;
    temp_v0[6] = 0;
    temp_v0[2] = 0;

    D_800B0DE0 += 14;
    return temp_v0;
}

void func_15001B5C(u8 arg0) {
    *D_800B0DE0++ = arg0;
}

void func_15001B8C(u16 arg0) {
   D_800B0DE0[0] = (arg0 >> 8);
   D_800B0DE0[1] = arg0 & 0xFF;
   D_800B0DE0 += 2;
}

void func_15001BC8(s32 arg0, s16 *arg1, s16 *arg2) {
    u16 *tmp;
    s16 *sp20;
    s32 i;

    func_1510F800(arg0);
    D_800B0DD8 = 10;
    D_800B0DD4 = 512;
    sp20 = allocate_memory((D_800DBE4C + 1) << 1, 1, 0, 0);

    *sp20 = D_800DBE4C;
    for (i = 0; i < D_800DBE4C; i++) {
        sp20[i + 1] = i;
    }

    tmp = func_15001DE0(0, 0, 32768, 32768, 0, sp20);
    D_800DBE08[arg0] = tmp;
    func_15002560(tmp, 0);
    func_10004074(sp20);

    // regalloc fix:
    if (1) { }

    if (arg1 != 0) {
        *arg1 = D_800B0DCC;
    }
    if (arg2 != 0) {
        *arg2 = D_800B0DD0;
    }
}

void func_15001CEC(s32 arg0) {
    u16 *temp_v0;
    s16 *sp20;
    s32 i;

    func_1510F800(arg0);
    temp_v0 = func_15001B10();

    D_800DBE08[arg0] = temp_v0;

    *((s16*)temp_v0 + 0) = 32768;
    temp_v0[1] = 32767;
    temp_v0[2] = 0;
    temp_v0[3] = -32768;
    temp_v0[4] = 0;
    temp_v0[5] = 0;
    temp_v0[6] = 0;

    sp20 = allocate_memory((D_800DBE4C + 1) << 1, 1, 0, 0);

    *sp20 = D_800DBE4C;
    for (i = 0; i < D_800DBE4C; i++) {
        sp20[i + 1] = i;
    }

    func_15002008(-0x8000, 0x8000, -0x8000, 0x8000, sp20);
    func_10004074(sp20);
}

u16 *func_15001DE0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    u16 *temp_v0;
    u16 *temp_v0_2;
    u16 *temp_v0_3;
    u16 *temp_v0_4;

    s32 sp7C;
    s32 sp78;

    s32 tmp0;
    s32 tmp1;

    s32 sp44;
    s32 sp48;
    s32 sp4C;
    s32 sp50;
    s32 sp54;
    s32 sp58;

    tmp0 = D_800B0DD8;
    tmp1 = D_800B0DD4;

    sp54 = arg0 - arg2;
    sp50 = arg0 + arg2;
    sp4C = arg1 - arg3;
    sp48 = arg1 + arg3;

    if ((func_15002248(sp54, sp50, sp4C, sp48, &sp7C, &sp78, arg5, &sp58) < tmp0) || (arg2 < tmp1)) {
        temp_v0 = func_15001B10();
        D_800B0DD0 = (D_800B0DD0 + 1);
        temp_v0[0] = sp7C;
        temp_v0[1] = sp78;
        temp_v0[3] = arg2;
        temp_v0[4] = arg0;
        temp_v0[5] = arg1;
        temp_v0[2] = 0;
        temp_v0[6] = 0;
        func_15002008(sp54, sp50, sp4C, sp48, sp58);
    } else {
        temp_v0 = func_15001B10();
        temp_v0[0] = sp7C;
        temp_v0[1] = sp78;
        temp_v0[3] = arg2;
        temp_v0[4] = arg0;
        temp_v0[5] = arg1;
        temp_v0[2] = 0;

        temp_v0_2 = func_15001DE0(arg0 - (arg2 >> 1), arg1 - (arg3 >> 1), arg2 >> 1, arg3 >> 1, 0, sp58);
        temp_v0[6] = (s32)temp_v0_2 - (s32)temp_v0;
        temp_v0_3 = func_15001DE0(arg0 - (arg2 >> 1), (arg3 >> 1) + arg1, arg2 >> 1, arg3 >> 1, 0, sp58);
        temp_v0_2[2] = (s32)temp_v0_3 - (s32)temp_v0_2;
        temp_v0_4 = func_15001DE0((arg2 >> 1) + arg0, arg1 - (arg3 >> 1), arg2 >> 1, arg3 >> 1, 0, sp58);
        temp_v0_3[2] = (s32)temp_v0_4 - (s32)temp_v0_3;
        temp_v0_4[2] = (s32)func_15001DE0((arg2 >> 1) + arg0, (arg3 >> 1) + arg1, arg2 >> 1, arg3 >> 1, 0, sp58) - (s32)temp_v0_4;
    }
    func_10004074(sp58);
    return temp_v0;
}

void func_15002008(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u16 *arg4) {
    Face16 *face;
    s32 count;
    s32 idx;
    s32 last;
    s32 diff;
    s32 i;
    s32 j;
    Face32 sp78;

    last = -1;
    count = arg4[0];

    func_150492CC((f32)(arg1 - arg0), 32000.0f, (f32)(arg3 - arg2));

    for (i = 1; i <= count; i++) {
        idx = arg4[i];
        face = &((Face16 *)D_800DBE3C)[idx];

        for (j = 0; j < 3; j++) {
            if ((u32)face->pts[j] > 0x80000000) {
                sp78.pts[j].x = (f32)(face->pts[j]->x - (arg0 + arg1) / 2);
                sp78.pts[j].y = (f32)face->pts[j]->y;
                sp78.pts[j].z = (f32)(face->pts[j]->z - (arg2 + arg3) / 2);
            } else {
                sp78.pts[j].x = 0.0f;
                sp78.pts[j].y = 0.0f;
                sp78.pts[j].z = 0.0f;
            }
        }

        if (func_15049260(sp78) == 0) {
            diff = idx - last;
            if (last == -1) {
                func_15001B8C(idx | 0x8000);
            } else if (diff < 0x80) {
                func_15001B5C(diff);
            } else {
                func_15001B8C(idx | 0x8000);
            }
            last = idx;
        }
    }

    func_15001B5C(0);
}

int func_15002248(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 *arg4, s32 *arg5, u16 *arg6, u16 **arg7) {
    s32 i;
    s32 j;
    s32 count;
    s32 total;
    s32 idx;
    u16 *out;
    Face16 *face;
    s32 temp;
    s32 flag;
    s32 res;
    s32 pad;
    s32 mask;
    Face32 sp74;

    pad = (1 << (D_80082FA0 + 1)) - 1;
    mask = -(1 << (D_80082FA0 + 1));

    func_150492CC((f32)(arg1 - arg0), 32000.0f, (f32)(arg3 - arg2));

    total = arg6[0] + 1;
    count = 0;
    out = allocate_memory(total << 1, 1, 0, 0);
    *arg7 = out;
    *arg4 = 0;
    *arg5 = 0;
    flag = 0;

    for (i = 1; i < total; i++) {
        idx = arg6[i];
        face = &((Face16 *)D_800DBE3C)[idx];

        for (j = 0; j < 3; j++) {
            if ((u32)face->pts[j] > 0x80000000) {
                sp74.pts[j].x = (f32)(face->pts[j]->x - ((arg0 + arg1) >> 1));
                sp74.pts[j].y = (f32)face->pts[j]->y;
                sp74.pts[j].z = (f32)(face->pts[j]->z - ((arg2 + arg3) >> 1));
            } else {
                sp74.pts[j].x = 0.0f;
                sp74.pts[j].y = 0.0f;
                sp74.pts[j].z = 0.0f;
            }
        }

        res = func_15049260(sp74);
        if (res == 0) {
            count++;
            out[count] = idx;

            if (flag) {
                temp = (((YRange *)D_800DBE44)[idx].min - pad) & mask;
                if (temp < *arg4) {
                    *arg4 = temp;
                }
                temp = ((((YRange *)D_800DBE44)[idx].max + pad) & mask) + pad;
                if (*arg5 < temp) {
                    *arg5 = temp;
                }
            } else {
                flag = 1;
                *arg4 = (((YRange *)D_800DBE44)[idx].min - pad) & mask;
                *arg5 = ((((YRange *)D_800DBE44)[idx].max + pad) & mask) + pad;
            }
        }
    }

    out[0] = count;
    return count;
}

void func_15002560(u16 *arg0, u16 *arg1) {
    s32 temp_v0;
    func_15002560_node *temp_s0;
    func_15002560_node *var_s1;

loop:
    if (arg0 != 0) {
        if (((func_15002560_node *)arg0)->unk4 == 0) {
            if (arg1 != 0) {
                temp_v0 = (s32)arg1 - (s32)arg0;
            } else {
                temp_v0 = 0;
            }
            ((func_15002560_node *)arg0)->unk4 = temp_v0;
        }
        temp_v0 = ((func_15002560_node *)arg0)->unkC;
        if (temp_v0 == 0) {
            return;
        }
        var_s1 = (func_15002560_node *)((u8 *)arg0 + temp_v0);
        if (var_s1->unk4 != 0) {
            do {
                temp_s0 = (func_15002560_node *)((u8 *)var_s1 + var_s1->unk4);
                func_15002560((u16 *)var_s1, (u16 *)temp_s0);
                var_s1 = temp_s0;
            } while (temp_s0->unk4 != 0);
        }
        arg0 = (u16 *)var_s1;
        goto loop;
    }
}

void func_150025FC(void) {
    s32 tmp0;
    s32 tmp1;
    s32 tmp2;
    s32 tmp3;

    tmp0 = D_800DBE2A;
    tmp1 = D_800DBE2C;

    D_800DBE28 = (((tmp0 + 7) / 8) + 0xF) & 0xFFF0;
    tmp2 = func_1502B5C8(0, 2, 5, D_800BE9F0 << 1);
    tmp3 = func_1502B5C8(0, 2, 5, (D_800BE9F0 << 1) + 1);
    if (tmp2 == 0) {
        D_800BE5D0 = 0;
    } else {
        func_150183D0(D_800DBE28, tmp1, tmp2, tmp3);
        func_10004074(tmp3);
    }
}

void func_150026C4(s32 arg0) {
    D_800DBE38 = 0;
    func_1510F800(arg0);
}

void func_150026E8(s32 arg0) {
    D_800DBE18[arg0] = D_800DBE38;
    D_800DBE4C = D_800DBE38;
    D_800B0DE4 += D_800DBE38;
}

void func_15002724(s32 arg0) {
    D_800DBE38 += func_150027F8(arg0);
}

void func_15002754(void) {
    s32 count;
    s32 idx;

    D_800DBDD8[D_800DBE50] = D_800B0DC0 = ALIGN4(D_800B0DC0);
    count = D_800DBE38;
    idx = D_800DBE50;
    D_800B0DC0 += count * 12;
    D_800DBDE8[idx] = D_800B0DC0;
    D_800B0DC0 += count * 8;
    D_800DBDF8[idx] = D_800B0DC0;
    D_800B0DC0 += count * 4;
    func_1510F800(idx);
    D_800DBE38 = 0;
}


int func_150027F8(s32 arg0) {
    s32 var_v0;
    s32 var_v1;
    s32 temp_a1;
    if (arg0 != 0) {
        goto non_null;
    }
    return 0;
non_null:
    var_v0 = 0;
    var_v1 = 0;
    temp_a1 = *(s8 *)arg0;
    if (temp_a1 != -0x21) {
        do {
            var_v0++;
            if ((temp_a1 >> 4) == 1) {
                var_v1 += 4;
            } else if (temp_a1 == 6) {
                var_v1 += 2;
            } else if (temp_a1 == 5) {
                var_v1 += 1;
            }
            temp_a1 = *(s8 *)(arg0 + (var_v0 << 3));
        } while (temp_a1 != -0x21);
    }
    return var_v1;
}

s32 func_15002878(void) {
    s32 i;
    s32 tmp;
    s32 highest;

    highest = *D_800DBE18;

    for (i = 0; i < 3; i++) {
        tmp = D_800DBE1C[i];
        if (highest < tmp) {
            highest = tmp;
        }
    }

    return highest;
}

// 12 loops!
#pragma GLOBAL_ASM("asm/nonmatchings/game_2DF70/func_150028BC.s")

void func_15002F40(s32 arg0) {
    if (arg0 == 50 || arg0 == 51) {
        D_800DBE64 = 150.0f;
        return;
    }
    if (D_800BE616) {
        D_800DBE64 = 85.0f;
        return;
    }
    D_800DBE64 = 50.0f;
}

s32 func_15002FA0(s32 arg0) {
    return arg0 ^ 0xF0F0F0F0;
}

void func_15002FB4(s32 arg0) {
    struct00 *sp3C; // TBD
    s32 sp38;
    s32 sp34;
    struct104 *temp_v0;
    s32 sp2C;

    sp3C = func_1502B6BC(&sp34, 0, &sp38, 2, 21, arg0);
    if ((sp38 != 0) && ((sp3C->unk4 << 8) != 0)) {
        D_800B0DF0 = sp3C->unk0;
        if (sp34 == 0) {
            D_8003C8E0 = 0xC000037;
            func_150AD770();
        }
        if (D_800B0DF0 == 0) {
            D_8003C8E0 = 0xC000037;
            func_150AD770();
        }
    }
    func_151EF040(func_15002FA0(0x40F0FAAC), &sp2C);
    sp2C = func_15002FA0(sp2C);
    if (sp2C != 0xE7B00F09) {
        temp_v0 = D_800B0DF0;
        temp_v0->unk12 >>= 1;
    }

    temp_v0 = D_800B0DF0;
    if (temp_v0->unk12 != 0) {
        D_800D2F3C = temp_v0->unk12;
        D_800D2F40 = sp3C->unk8;
    } else {
        D_800D2F3C = 0U;
        D_800D2F40 = 0;
    }

    if ((D_8008FD90 >= 2) && (temp_v0->unk8 == 4)) {
        temp_v0->unk8 = 2U;
    }
}

void func_1500310C(void) {
}
