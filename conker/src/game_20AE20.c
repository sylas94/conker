#include <ultra64.h>
#include "functions.h"
#include "variables.h"

struct Struct151E5034 {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    u16 unk20;
    char pad22[8];
    s8 unk2A;
    s8 unk2B;
    s8 unk2C;
    char pad2D[0x11];
    s8 unk3E;
    s8 unk3F;
    char pad40;
    s8 unk41;
    char pad42;
    s8 unk43;
    s8 unk44;
};

struct Struct151E4314 {
    s16 unk0;
    s8 unk2;
    s8 unk3;
};

extern s8 D_800AB692[];
extern struct Struct151E4314 D_800AB7A4[];
extern s8 D_800E0C00[];
extern s8 D_800E0BEB;
extern s16 D_800E0A80;
extern s16 D_8008FDCC;
extern u8 **D_800E0BD8;
extern void func_1501D348(s32, s32, s32, s32, s32);
void func_151E2834(void);
s32 func_1517EFDC(void);
extern s32 D_800E0A90;
extern u8 D_8008FE28;
extern s8 D_800E0B96;
extern u8 D_800D2E40;
extern u8 D_800E0B94;
extern u8 D_8008FDA4;
extern s16 D_800E0B9A;
extern u8 D_800E0B95;
extern u8 D_800E0BDC;
extern u16 D_800BE930;
extern s8 D_800AB690[];
extern s32 D_800AB754[];
extern char D_800AB850[];
extern void (*D_800E0A88)(void);
extern u8 D_800E0A95;
extern s8 D_800E0A96;
extern s8 D_8008FDE0;
extern void (*D_8008FDEC[])(void);
void func_1000E934(void);
void func_1000F1A8(void);
void func_1501C730(s32, s32, s32, s32, s32);
void func_15042D94(s32, s32, s32, char *, s32);
void func_151E2404(void);
void func_151E3344(s32, s32, s32, s32, s32);
void func_151E6964(s32);
void func_151E530C(void);
void func_151E55A8(void);
void func_151E557C(void);
void func_151E7EF8(void);
s32 func_151F2CDC(void);
void func_151F2D6C(s32, s32);
s32 func_1509CA30(s32);
s32 func_1509CA50(s32);
void func_1509CC94(s32);
void func_1509CDDC(s32);
void func_1509CF28(s32, s32 *);
void func_1509D054(void);
void func_1509D08C(s32, s32, s32 *, s32 *);
extern s8 D_8008FD70;
extern s16 D_8008FDAC;
extern u8 D_8008FDB4;
extern s8 D_8008FF00;
extern u8 D_8008FF04;
extern s32 D_800BE3E4;
extern s8 D_800D23A8;
extern s8 D_800E0B99;
extern s8 D_800E0BB1;
extern u8 D_800E0BD1;

#pragma GLOBAL_ASM("asm/nonmatchings/game_20AE20/func_151DD970.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_20AE20/func_151DD9E4.s")

s32 func_151DDB94(s32 arg0) {
    return ~arg0;
}

void func_151DDBA0(void) {
    D_800D2E40 = 0;
    func_1501C730(6, 0x1D, 0, 0, 1);
    D_800E0B94 = 3;
    D_8008FDA4 = 0;
    D_800BEAC1 = 0;
    func_151E557C();
    func_1000F1A8();
    func_1000E934();
    D_8008FD8C = 1;
    D_8008FD90 = 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_20AE20/func_151DDC20.s")

void func_151DE6D4(void) {
    s32 timer;

    func_151E530C();
    D_800CC2D0[0].unk25C |= 0x200;
    D_800CC2D0[0].y_position = 1000.0f;

    if (D_80000300 == 0) {
        D_800E0A90 = 0;
    }

    timer = D_800E0A90;
    if (timer >= 0x14B) {
        if (D_800E0B9A & 0x8000) {
            if (timer >= 0x1E0) {
            } else {
                timer = D_800E0A90 = 0x1E0;
            }
            if (timer < 0x259) {
            } else {
                if (timer >= 0x2D0) {
                } else {
                    timer = D_800E0A90 = 0x2D0;
                }
            }
        }
    }

    if (timer >= 0x349) {
        D_8008FE28 = 2;
        D_800E0B94 = 1;
        D_800D2E40 = 0;
        func_1501C730(6, 0x21, 0, 0, 1);
        *(u8 *)&D_800E0B96 = 0xFF;
    }
}

extern s32 D_800E0A90;
extern u8 D_800E0B97;
extern u8 D_800E0B98;
extern u8 D_800E0A8C;
extern u8 D_8008FE28;
void func_151DE85C(void);

void func_151DE7D4(void) {
    D_800E0A90 = 0;
    D_800E0B97 = 0;
    D_800E0B98 = 0;
    D_800E0A8C = 0;
    D_8008FE28 = 2;
    func_151DE85C();
}

extern s8 D_8008FE30;
extern s8 D_8008FD74;
extern s8 D_800E0B96;

void func_151DE81C(void) {
    D_8008FD74 = 4;
    D_800E0B96 = 0;
    if (D_8008FE30 == 0) {
        func_1500764C();
    }
}

extern u8 D_800D2E40;
extern u8 D_800E0B94;
extern u8 D_8008FD80;
extern u8 D_8008FDA4;
extern struct Struct151E5034 *D_8008FDD4;
void func_1501C730(s32, s32, s32, s32, s32);

void func_151DE85C(void) {
    D_800D2E40 = 0;
    func_1501C730(6, 0x1D, 0, 0, 1);
    D_800E0B94 = 3;
    D_8008FD80 = 1;
    D_8008FE28 = 2;
    D_8008FDA4 = 0;
    D_8008FDD4->unk3E = 0;
    D_8008FDD4->unk2B = 5;
    D_8008FDD4->unk2C = D_8008FDD4->unk2B;
}

void func_151DE8E8(void) {
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_20AE20/func_151DE8F0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_20AE20/func_151DF1BC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_20AE20/func_151DF574.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_20AE20/func_151DFF38.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_20AE20/func_151E0424.s")

void func_151E09DC(void) {
    s32 arg0;
    s32 temp;

    func_1504332C(0xFF, 0xFF, 0xFF, 0xFF);
    func_15042D94(0x94, 0x7E, 1, D_800AB850, 0x1A);
    func_15042D78(0x81);

    arg0 = D_800AB754[D_800AB690[D_8008FDD4->pad42 * 10]];
    if (D_800E0A96 == 0) {
        D_8008FDD4->unk20 &= ~0x20;
        temp = D_800E0A95 - (D_800BE9E4 << 5);
        if (temp <= 0) {
            D_8008FDD4->unk3F = 0;
            if (D_8008FDE0 != 0) {
                func_151E2404();
            }
            D_8008FDE0 = 0;
            D_800E0A96 = -1;
            return;
        }
        D_800E0A95 = temp;
    } else {
        temp = D_800E0A95 + (D_800BE9E4 << 5);
        if (temp >= 0x100) {
            temp = 0xFF;
        }
    }

    D_800E0A95 = temp;
    if (temp != 0xFF) {
        D_8008FDD4->unk20 = 0;
    }
    func_151E3344(arg0, 1, 0, temp & 0xFF, 0);

    if (D_8008FDD4->unk20 & 0x20) {
        D_800E0A96 = 0;
    }
    D_8008FDD4->unk20 &= ~0x20;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_20AE20/func_151E0B70.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_20AE20/func_151E1214.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_20AE20/func_151E1744.s")

extern u8 D_8008FD80;
void func_151E530C(void);
void func_151E43DC(void);

void func_151E2284(void) {
    D_8008FD80 = 3;
    func_151E530C();
    func_151E43DC();
    D_8008FD80 = 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_20AE20/func_151E22BC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_20AE20/func_151E2404.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_20AE20/func_151E24F0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_20AE20/func_151E2834.s")

void func_151E30C4(void) {
    s32 sp2C;
    s32 sp28;
    s32 sp24;

    sp24 = 0;
    if (D_8008FDB4 != 0) {
        sp28 = D_8008FDAC;
    } else {
        func_1509CF28(D_8008FF00, &sp2C);
        func_1509D08C(D_8008FF00, D_8008FF04, &sp28, &sp24);
        func_1509D054();
    }

    func_15017790();
    func_1509CC94(sp28);
    func_1509CDDC(sp28);
    D_800BE9F4 = (u16 *)func_1509CA30(sp28);
    func_15085710(0, 9, sp24);
    D_800BE3E4 = sp24;

    D_800DD2C0 = func_1509CA50(sp28);
    if (D_8008FDB4 == 2) {
        D_800DD2C0 = D_800E0BD1;
    }

    D_8008FD70 = 0;
    D_800D23A8 = 0;
    D_8008FDBC = 0;
    D_8008FDA8 = -1;
    D_800E0B94 = 0;
    *(u8 *)&D_800E0B99 = 1;
    D_8008FD8C = 1;
    D_8008FD90 = 1;
    *(s8 *)&D_8008FD94 = 1;

    D_800BE618 = 1;
    D_80087260 = 3;
    if (D_800E9D00 & 0x200) {
        D_80087260 = 0x33;
    }

    D_80087270[0] = 0;
    D_800D18A8 = 0;
    D_800E0BB1 = 1;
    func_151E7EF8();
    D_800D2E40 = 1;
    func_1501C730(6, (s32)D_800BE9F4, func_1509CA50(sp28), 0, 1);
}

void func_151E327C(void) {
    D_80087260 = 3;
    if (D_800E9D00 & 0x200) {
        D_80087260 = 0x33;
    }

    D_80087270[0] = 0;
    D_8008FD8C = 1;
    D_8008FD90 = 1;
    *(s8 *)&D_8008FD94 = 1;
    D_8008FDBC = 0;
    D_800BE618 = 1;
    D_800D23A8 = 0;
    D_800E0B94 = 0;
    D_800D2E40 = 0;
    func_1501C730(6, *(s8 *)&D_800BE3DF, D_800BE3E0, 0, 1);
    *(u8 *)&D_800E0B99 = 1;
    D_800E0BB1 = 1;
    func_151E7EF8();
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_20AE20/func_151E3344.s")

void func_151E4264(void) {
    if (D_8008FD80 != 0) {
        D_8008FD80 = 0;
        return;
    }

    func_151E530C();
    if ((D_800E0B9A != 0) || (D_800C35EA != 1)) {
        if ((D_800C35EA == 1) && (func_151F2CDC() == 1)) {
            func_151F2D6C(0, 0x2DE0);
        }
        D_800E0B94 = 7;
        D_800E0A88 = func_151E2834;
        D_8008FD74 = 8;
    }
}

void func_151E4314(void) {
    struct Struct151E4314 *entry;
    s32 idx;
    s32 arg1;

    idx = D_800AB692[D_8008FDD4->pad42 * 10];
    if (idx >= 0) {
        entry = &D_800AB7A4[idx];
        if (D_800E0C00[0]) {
            arg1 = entry->unk3;
        } else {
            arg1 = entry->unk2;
        }
        func_1501D348(entry->unk0, arg1, 0, 0, 0);
        D_8008FD80 = 1;
        D_800E0B94 = 5;
        D_8008FD8C = 1;
        D_8008FD90 = 1;
    } else {
        func_151E2834();
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_20AE20/func_151E43DC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_20AE20/func_151E4BD8.s")

extern u8 D_800E0B94;

void func_151E4DC4(void) {
    D_800E0B94 = 0xA;
}

extern s16 D_800E0B9A;

void func_151E4DD8(void) {
    if (D_800E0B9A & 0x8020) {
        D_800E0B94 = 4;
    }
}

void func_151E4E00(void) {
    D_8008FDCC = 0;
    func_151E557C();
    D_800E0B94 = 3;
    D_8008FDA4 = 0;
    D_8008FD80 = 0;
    D_800D2E40 = 0;
    func_1501C730(6, 0x1D, 0, 0, 1);
}

void func_151E4E64(void) {
    func_151E530C();
    func_151E55A8();
    if (D_800E0A90 >= 0x4B1) {
        D_800E0B9A |= 0x8000;
    }
    if (D_800E0B9A != 0) {
        D_800E0B94 = 7;
        D_800E0A88 = func_151E4E00;
        D_8008FD74 = 8;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_20AE20/func_151E4EE8.s")

extern struct Struct151E5034 *D_8008FDD4;

void func_151E5034(void) {
    D_8008FDD4->unk0 = 0.0f;
    D_8008FDD4->unk4 = 0.0f;
    D_8008FDD4->unk2B = 0;
    D_8008FDD4->unk20 = 0;
    D_8008FDD4->unk3E = 0;
    D_8008FDD4->unk3F = 0;
    D_8008FDD4->unk41 = 0;
    D_8008FDD4->unk43 = 0;
    D_8008FDD4->unk44 = 0;
    D_8008FDD4->unk10 = 0.0f;
    D_8008FDD4->unk2A = 0;
    D_8008FDD4->unk14 = 0.0f;
    D_8008FDD4->unk18 = 0.0f;
    D_8008FDD4->unk1C = 0.0f;
    D_8008FDD4->unkC = 0.0f;
    D_8008FDD4->unk8 = 0.0f;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_20AE20/func_151E50C8.s")

void func_151E51EC(void) {
    u8 state;
    s32 timer;

    state = D_800E0B94;
    D_8003C8E0 = 0x08000000;
    D_800E0BDC = 0xFF;
    func_15042D78(0x81);

    D_800E0B9A = D_800BE930;
    timer = *(s8 *)&D_8008FE28;
    if (timer != 0) {
        D_8008FE28 = timer - 1;
        D_800E0B9A = 0;
    }

    if (D_800E0B94 == 0) {
        func_151E6964(2);
    } else if (D_800E0B94 == 8) {
        func_151E6964(4);
    } else {
        func_151E6964(1);
    }

    D_8008FDEC[D_800E0B94]();

    if (D_800E0B94 != 7) {
        D_800E0A90 += D_800BE9E4;
        if (D_800E0B94 == state) {
        } else {
            D_800E0B95 = state;
            D_800E0A90 = 0;
        }
    }
    D_8003C8E0 = 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_20AE20/func_151E530C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_20AE20/func_151E53E8.s")

extern u8 D_80084060[];

void func_151E557C(void) {
    D_80084060[0] = 0;
    D_80084060[1] = 1;
    D_80084060[2] = 2;
    D_80084060[3] = 3;
}

void func_151E55A8(void) {
    s32 temp;
    s32 step;
    s32 direction;

    direction = D_800E0B98;
    if (direction == 0) {
        step = D_800BE9E4 * 8;
    } else {
        step = -D_800BE9E4 * 8;
    }
    temp = D_800E0B97;
    temp += step;
    if (temp >= 0x100) {
        temp = 0x1FE - temp;
        D_800E0B98 = direction ^ 1;
    } else if (temp < 0) {
        temp = -temp;
        D_800E0B98 = direction ^ 1;
    }
    D_800E0B97 = temp;
}

extern u8 D_800E0A8C;

void func_151E562C(void) {
    if (D_800E0A8C != 0) {
        D_800E0A8C = 0;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_20AE20/func_151E564C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_20AE20/func_151E565C.s")

extern u8 D_800BE616;
extern u8 D_800E0B94;
extern s8 D_800E0C00[];

s32 func_151E5F64(s32 arg0) {
    s32 ret;

    if ((D_800BE616 != 0) || (D_800E0B94 != 0)) {
        ret = D_800E0C00[arg0];
        if (ret < 0) {
            ret = 0;
        }
        return ret;
    }
    return arg0;
}

s8 func_151E5FAC(void) {
    if (D_800E0BEB != 0) {
        if (D_8008FD8C >= 5) {
            return D_8008FD90;
        }
        return D_8008FD8C;
    }
    return D_8008FD90;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_20AE20/func_151E5FF4.s")

extern s8 D_800E0BEA;
extern s8 D_800E0BD3;
extern s32 D_800E0BD4;
extern s32 D_8008FDD8;
extern u8 **D_800E0B88;
extern void func_10004074(void *);
extern void *allocate_memory(s32, s32, s32, s32);
s32 func_1502B5C8();

void func_151E6964(s32 arg0) {
    u8 *p;
    u8 *end;
    s32 i;
    s32 size;

    if (D_800E0BEA != D_800BEAAB) {
        D_800BEAAB = D_800E0BEA;
        D_800E0BD3 = 0;
    }
    if (arg0 == D_800E0BD3) {
        return;
    }
    if (D_800E0BD4 != 0) {
        func_10004074((void *)D_800E0BD4);
        D_800E0BD4 = 0;
        if (D_8008FDD8 != 0) {
            func_10004074((void *)D_8008FDD8);
            func_10004074(D_800E0B88);
            func_10004074(D_800E0BD8);
            D_8008FDD8 = 0;
        }
    }
    D_800E0BD3 = arg0;
    if (D_800E0BD3 == 0) {
        return;
    }

    D_800E0BD4 = func_1502B5C8(&size, 3, 0x1C, D_800BEAAB, arg0 - 1);
    p = (u8 *)D_800E0BD4;
    end = p + size;
    i = 0;
    do {
        while (*p != 0) {
            p++;
        }
        while (*p == 0) {
            p++;
        }
        i++;
    } while (p < end);

    D_800E0BD8 = allocate_memory((i + 1) << 2, 1, 0, 0);
    p = (u8 *)D_800E0BD4;
    end = p + size;
    i = 0;
    do {
        D_800E0BD8[i] = p;
        i++;
        while (*p != 0) {
            p++;
        }
        while (*p == 0) {
            p++;
        }
    } while (p < end);

    if (arg0 - 1 != 0) {
        return;
    }

    D_8008FDD8 = func_1502B5C8(&size, 3, 0x1C, D_800BEAAB, 2);
    D_800E0B88 = allocate_memory(0x140, 1, 0, 0);
    p = (u8 *)D_8008FDD8;
    i = 0;
    do {
        D_800E0B88[i] = p;
        i++;
        while (*p != 0) {
            p++;
        }
        while (*p == 0) {
            p++;
        }
    } while (i != 80);
}

void func_151E6BFC(void) {
    D_800E0BD3 = 0;
    D_800E0BD4 = 0;
    D_8008FDD8 = 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_20AE20/func_151E6C1C.s")

struct Struct151149AC {
    char pad0[0x80];
    s32 unk80;
};
extern struct Struct151E5034 *D_8008FDD4;
extern u8 D_8008FFB0[2][6];
extern f32 D_800ABA8C;
struct Struct151149AC *func_151149AC(s32);

void func_151E7DC0(void) {
    struct Struct151E5034 *sp;
    struct Struct151149AC *r;
    s32 i;
    s32 a;

    sp = D_8008FDD4;
    if (sp->unk8 < D_800ABA8C && sp->unk3E == 0) {
        return;
    }
    for (i = 0; i != 2; i++) {
        sp = D_8008FDD4;
        if (sp->unk3E == 0) {
            a = D_8008FFB0[i][sp->unk2C];
        } else {
            a = D_8008FFB0[i][0];
        }
        r = func_151149AC(a);
        if (r != 0) {
            r->unk80 = 2;
        }
    }
}

extern s8 D_800E0BE9;

void func_151E7E9C(void) {
    if (D_800E0BE9 == 2) {
        func_10017870(1);
    } else if (D_800E0BE9 == 0) {
        func_10017870(2);
    } else {
        func_10017870(4);
    }
}

extern void func_151DDC20(void);

void func_151E7EF8(void) {
    s32 *p;
    s32 *end;
    s32 sum;

    func_151E7E9C();
    sum = 0;
    p = (s32 *)func_151DDC20;
    end = (s32 *)func_151DE7D4;
    for (; p < end; p++) {
        sum += *p;
    }
    if (sum != (s32)0xBFC924E3) {
        *(s32 *)osSpTaskLoad = 0;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_20AE20/func_151E7F60.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_20AE20/func_151E81EC.s")

void func_151E8214(void) {
    if (D_800E0B94 != 8) {
        if (func_1517EFDC() == 0) {
            D_800E0A90 = 0;
        }
        if (D_800E0A90 >= 0xA1) {
            D_8008FDCC = 0;
            D_800E0B94 = 8;
            D_8008FD8C = 1;
            D_8008FD90 = 1;
            D_8008FDA4 = 0;
            D_800E0A80 = -2;
            D_800E0A90 = 0;
            D_800D2E43 = 1;
        }
    }
}

void func_151E82B8(void) {
    func_151E530C();
    if (D_800E0A80 == -1) {
        if (D_800E0A90 >= 0x79) {
            D_800E0B94 = 9;
            D_800E0A90 = 0;
            D_8008FDCC = 0xFF;
            D_800E0A80 = 0;
            func_1501C730(6, 0x1D, 0, 0, 1);
            return;
        }
    }
    if (D_800E0A80 == -2) {
        D_800E0A80 = 0;
    }

    if (D_800E0A90 >= 0x1BE) {
        if (D_800E0A80 >= 0) {
            while (D_800E0BD8[D_800E0A80][0] != 0x2A) {
                D_800E0A80++;
            }
            D_800E0A80++;
            if (D_800E0BD8[D_800E0A80][0] == 0x3D) {
                D_800E0A80 = -1;
            }
            D_800E0A90 = 0;
        }
    }
}

void func_151E83E8(void) {
    if (D_800E0A80 == 0) {
        D_800E0A80 = -1;
        func_1501D348(0x1D, 6, 0, 0, 0);
    }
    func_151E530C();
    if (func_1517EFDC() == 0) {
        D_800E0A90 = 0;
    }
    if (D_800E0A90 >= 0x65) {
        func_151E5034();
        D_8008FDA4 = 0;
        D_800E0B94 = 1;
        D_800E0A90 = 0;
        D_800D2E40 = 0;
        func_1501C730(6, 0x21, 0, 0, 1);
    }
}
