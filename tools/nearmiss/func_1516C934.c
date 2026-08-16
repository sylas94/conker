#include <ultra64.h>
#include "functions.h"
#include "variables.h"

typedef struct {
    u8 *unk0;
    s32 unk4;
} struct_game_197C20_0;

typedef struct {
    s32 unk0;
    s32 unk4;
} struct_game_197C20_1;

typedef struct {
    s32 field_0x0;
    char pad_0[0x4];
    u8 field_0x8;
} struct_game_197C20_2;

typedef struct {
    u8 field_0x0;
    char pad_0[0xF];
    struct_game_197C20_2 *field_0x10;
    char pad_1[0x1];
    u8 field_0x15;
    char pad_2[0xA];
    u8 field_0x20;
} struct_game_197C20_3;

extern struct_game_197C20_0 *D_800DD254;
extern struct_game_197C20_0 *D_800DD258;


s32 func_1516A770(u8 *arg0) {
    s32 count = 1;

    while (*arg0 != 0) {
        if (*arg0 == 0xBD) {
            *arg0 = 0;
            count++;
        }
        arg0++;
    }
    return count;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_197C20/func_1516A7B0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_197C20/func_1516AA70.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_197C20/func_1516B6BC.s")

u8 *func_1516C878(struct_game_197C20_1 *arg0, s32 arg1, s16 arg2) {
    u8 *temp_v1;
    u8 *sp0;
    s32 temp_v0;
    s32 temp_a0;

    switch (arg2) {
    case 0:
        temp_v1 = D_800DD254[arg0->unk4].unk0;
        break;
    case 1:
        temp_v1 = D_800DD258[arg0->unk4].unk0;
        break;
    case 2:
        temp_v1 = (u8 *)arg0->unk4;
        break;
    default:
        temp_v1 = sp0;
        break;
    }

    temp_v0 = 0;
    if (arg1 > 0) {
        temp_a0 = temp_v1[0];
        do {
            temp_v0++;
            if (temp_a0 != 0) {
                do {
                    temp_a0 = temp_v1[1];
                    temp_v1++;
                } while (temp_a0 != 0);
            }
            if (temp_a0 == 0) {
                do {
                    temp_a0 = temp_v1[1];
                    temp_v1++;
                } while (temp_a0 == 0);
            }
        } while (temp_v0 != arg1);
    }

    return temp_v1;
}


extern s32 D_800BE9C8[];
extern s32 D_800BEBA4;
extern u8 D_800859A0[];

typedef struct {
    u8 pad_0x00[0x10];
    s32 *field_0x10;
    u8 pad_0x14[0x10];
    u8 *field_0x24;
    u8 pad_0x28[0x8];
    f32 field_0x30;
    f32 field_0x34;
    u8 pad_0x38[0x18];
    f32 field_0x50;
    f32 field_0x54;
} Struct1516C934;

extern void func_150428D4(u8 *, s32 *, s32 *, s32 *);
extern Gfx *func_150417AC(Gfx *, f32, f32, u8 *, u8, u8, u8, u8, f32, f32, s32);

Gfx *func_1516C934(Gfx *gfx, Struct1516C934 *arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5) {
    Gfx *orig;
    u8 buf[0x54];
    Struct1516C934 *p;
    s32 cond;
    s32 i;
    s32 len;
    s32 first;
    f32 dx;
    f32 y;
    f32 xoff;
    s32 w;
    s32 h;
    s32 d;

    i = 0;
    len = 0;
    p = arg1;
    orig = gfx;
    dx = arg1->field_0x50 - arg1->field_0x30;
    y = arg1->field_0x54 - arg1->field_0x34;
    gSPDisplayList(gfx++, D_800859A0);
    first = 1;

    while (p->field_0x24[i] == 0xA) {
        i++;
    }

    do {
        if ((((s32)gfx - D_800BE9C8[D_800BE9C0]) >> 3) > D_800BEBA4) {
            cond = 1;
        } else {
            cond = 0;
        }
        if (cond) {
            return orig;
        }

        buf[len] = p->field_0x24[i];
        if (buf[len] == 0xA) {
            buf[len] = 0;
        }
        if (buf[len] == 0) {
            func_150428D4(buf, &w, &h, &d);
            if (first == 0) {
                y += (f32)h;
            } else {
                first = 0;
            }
            if (*arg1->field_0x10 & 0x20000) {
                xoff = (arg1->field_0x30 - (f32)(w >> 1)) - 1.0f;
            } else {
                xoff = 0.0f;
            }
            if (*arg1->field_0x10 & 0x40000) {
                gfx = func_150417AC(gfx, (dx + xoff) + 1.0f, y, buf, 0xFF, 0xFF, 0xFF, arg5, 4096.0f, 4096.0f, len);
                len = 0;
            } else if ((*arg1->field_0x10 & 4) == 0) {
                gfx = func_150417AC(gfx, (dx + xoff) + 1.0f, y, buf, 0, 0, 0, arg5, 4096.0f, 4096.0f, len);
                len = 0;
            } else {
                gfx = func_150417AC(gfx, dx + xoff, y, buf, arg2, arg3, arg4, arg5, 4096.0f, 4096.0f, len);
                len = 0;
            }
            y += (f32)d;
        } else {
            len++;
        }
    } while (p->field_0x24[i++] != 0);

    return gfx;
}


#pragma GLOBAL_ASM("asm/nonmatchings/game_197C20/func_1516CC58.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_197C20/func_1516D0CC.s")

void func_1516D2E0(struct_game_197C20_3 *arg0) {
    if ((arg0 != 0) && (arg0->field_0x0 == 0x51)) {
        arg0->field_0x10->field_0x8 = 0;
        func_1516972C((struct102 *)arg0);
        arg0->field_0x15 = 0;
    }
}

void func_1516D328(struct_game_197C20_3 *arg0) {
    if ((arg0 != 0) && (arg0->field_0x0 == 0x51)) {
        arg0->field_0x10->field_0x0 |= 0x100;
        arg0->field_0x10->field_0x0 &= ~0x400;
        arg0->field_0x20 = arg0->field_0x10->field_0x8;
    }
}

u8 *func_1516D378(struct_game_197C20_3 *arg0) {
    if ((arg0 != 0) && (arg0->field_0x0 == 0x51)) {
        arg0->field_0x10->field_0x0 |= 0x100;
        arg0->field_0x10->field_0x0 &= ~0x400;
        return (u8 *)arg0;
    }
    return 0;
}

s32 func_1516D3C4(u8 *arg0) {
    s32 *temp;

    if ((arg0 != 0) && (*arg0 == 0x51)) {
        temp = *(s32 **)(arg0 + 0x10);
        *temp |= 0x500;
        return (s32)arg0;
    }
    return 0;
}
