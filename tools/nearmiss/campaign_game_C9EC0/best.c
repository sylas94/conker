#include <ultra64.h>
#include "functions.h"
#include "variables.h"


typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
} GameC9EC0Struct;

extern GameC9EC0Struct D_80087430[];
extern GameC9EC0Struct D_80088420[];
s32 func_1509CA10(s32 arg0) {
    return D_80087430[arg0].unk0;
}

typedef struct {
    u16 unk0;
    u16 unk2;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
} GameC9EC0StructB;

extern GameC9EC0StructB D_80087438[];

s32 func_1509CA30(s32 arg0) {
    return D_80087438[arg0].unk0;
}

extern GameC9EC0StructB D_8008743A[];

s32 func_1509CA50(s32 arg0) {
    return D_8008743A[arg0].unk0 & 0xFFF;
}

extern GameC9EC0Struct D_80087434[];

s32 func_1509CA78(s32 arg0) {
    return D_80087434[arg0].unk0;
}

s32 func_1509CA98(s32 arg0) {
    s32 i;

    i = 0;
loop:
    if (D_80087430[i].unk0 && arg0 == ((D_80087430[i].unk4 & 0x1FFFFFFF) + 1)) {
        return i;
    }
    if (D_80087430[i + 1].unk0 && arg0 == ((D_80087430[i + 1].unk4 & 0x1FFFFFFF) + 1)) {
        return i + 1;
    }
    if (D_80087430[i + 2].unk0 && arg0 == ((D_80087430[i + 2].unk4 & 0x1FFFFFFF) + 1)) {
        return i + 2;
    }
    if (D_80087430[i + 3].unk0 && arg0 == ((D_80087430[i + 3].unk4 & 0x1FFFFFFF) + 1)) {
        return i + 3;
    }
    i += 4;
    if (i != 0xCC) {
        goto loop;
    }

    return 0xCC;
}

s32 func_1509CB68(void) {
    s32 count;
    s32 i;

    count = 0;
    i = 0;
    do {
        if (D_80087430[i].unk0 != 0) {
            count++;
        }
        if (D_80087430[i + 1].unk0 != 0) {
            count++;
        }
        if (D_80087430[i + 2].unk0 != 0) {
            count++;
        }
        if (D_80087430[i + 3].unk0 != 0) {
            count++;
        }
        i += 4;
    } while (D_80088420 != &D_80087430[i]);
    return count;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_C9EC0/func_1509CBD4.s")

extern void func_1509CE64(void *, void *);
extern GameC9EC0Struct D_8008743C[];
void func_1509CCB4();

void func_1509CC94(void) {
    func_1509CCB4();
}

void func_1509CCB4(s32 arg0) {
    func_1509CE64((void *)D_8008743C[arg0].unk0, func_1509CCB4);
}

extern s32 D_800D2E70;
extern struct102 *D_800D2E4C;
extern GameC9EC0Struct D_80087440[];
void func_1509CCB4();
void func_1509CCB4(s32 arg0);
s32 func_1509CCF4(s32 arg0)
{
  u16 *p;
  s32 count;
  count = 0;
  p = (u16 *) D_80087440[arg0].unk0;
  while ((*p) != 0xFFFF)
  {
    ((u8 *) D_800D2E4C)[(*p) >> 3] |= 1 << ((*p) & 7);
    if ((((u8 *) (&D_800D2E70))[*p] != 3) != ((0, 0U)))
    {
      ((u8 *) (&D_800D2E70))[*p] = 3;
      func_1509CCB4(*p);
      count++;
    }
    p++;
  }

  return count;
}


#pragma GLOBAL_ASM("asm/nonmatchings/game_C9EC0/func_1509CDDC.s")

void func_1509CE64(void *arg0, void *arg1) {
    u16 *p;
    void (*cb)(s32);

    p = (u16 *)arg0;
    cb = (void (*)(s32))arg1;
    while (*p != 0xFFFF) {
        cb(*p);
        ((u8 *)&D_800D2E70)[*p] = 3;
        ((u8 *)D_800D2E4C)[*p >> 3] |= (1 << (*p & 7));
        p++;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_C9EC0/func_1509CF28.s")

extern s32 D_800D2FB0;
extern s32 func_10004074(s32);

void func_1509D054(void) {
    s32 temp;
    if (D_800D2FB0) {
        temp = D_800D2FB0;
        func_10004074(temp);
        D_800D2FB0 = 0;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_C9EC0/func_1509D08C.s")

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
} GameC9EC0Cmd;

extern void *func_1505EEF4(s32);
extern void func_151616D0(u8, u8, s32);
extern void func_150EB8C4(void);
extern void func_150F9720(u8);
extern void func_150F6DB0(void *);
extern void func_151CD394(s32);
extern void func_150E35DC(s32);
extern void func_150B3DD0(void);
extern void func_150C5C9C(void *);
extern void func_150C522C(void);
extern void func_151D2718(s16);

typedef struct {
    u8 pad0[0x14];
    s32 unk14;
    u8 unk18;
    u8 unk19;
    u8 pad1A[2];
    s32 unk1C;
    } GameC9EC0Ray;

extern void func_150BD070(u8, s32);
extern void func_150FAD28(void);
extern void func_150FAA40(u8, s32);
extern void func_15108120(void *, u8, s32);
extern void func_150ECC00(void *, u8, s32);
extern void func_150FAD78(void);
extern void func_150FCFD4(void *, u8, s32);
extern void func_150E0300(void);
extern void func_151557FC(s32, s32, f32);
extern s32 func_150F6DE4(void *);
extern s32 func_1514EC1C(s32, s32, s16);
extern s32 func_15046C80(f32 *, s32, f32, void *);
extern void func_151BFE84(void *, f32 *, f32 *, s32, u8, s32);
extern void func_15136C3C(void *, s32, s32, s32, s32, s32, s32, s32);
extern void func_151C0098(f32 *, void *, s32, s32, s32);
extern void func_150FCA30(void);
extern s32 func_1518F51C(void *, u8, s32, s32, s8, s8, u8, s32, u8, s32);
extern void func_150E1060(u8, u8, s32);
extern void func_151CD35C(s32);
extern void func_1000E7A0(u32, s32);
extern void *func_150B53D0(void *, s16, u8, s32);
extern void func_150BEF7C(s32);
extern void func_15178EFC(s32);
extern s32 func_150E3208(s32, s32, s32, s32, s32, s32, s32, s32);
extern s32 func_150E32D0(s32, s32, s32, s32, s32, f32);
extern s32 func_150E3414(s32, s32, s32, s32, s32, s32, s32, s32, f32);
extern void func_150DECC0(f32 *, u8, s32);
extern void func_150E81A8(u8, s32, s32);
extern void func_150E8930(void);
extern void func_151D26C0(s16);
extern void func_15163A60(u8, u8, s32);
extern void func_150D5A6C(void *, u8, s32);

#pragma GLOBAL_ASM("asm/nonmatchings/game_C9EC0/func_1509D180.s")

s32 func_1509D780(s32 arg0, GameC9EC0Cmd *arg1) {
    void *obj;

    switch (arg0) {
    case 41:
        func_150EB8C4();
        break;
    case 39:
        func_150F9720(((u8 *)arg1)[7]);
        break;
    case 38:
        func_151616D0(0x29, 0x18, 0);
        break;
    case 36:
        obj = func_1505EEF4(arg1->unk4 & 0xFFF);
        if (obj != NULL) {
            func_150F6DB0(obj);
        }
        break;
    case 26:
        func_151616D0(0x26, 0x18, 0);
        break;
    case 18:
        func_151CD394(arg1->unk4);
        break;
    case 2:
        D_800D9920 = 0;
        break;
    case 4:
    case 5:
    case 6:
        func_150E35DC(arg0 >> 6);
        break;
    case 8:
        func_150B3DD0();
        break;
    case 9:
        obj = func_1505EEF4(arg1->unk4 & 0xFFF);
        if (obj == NULL) {
            return 0;
        }
        func_150C5C9C(obj);
        break;
    case 10:
        func_150C522C();
        break;
    case 19:
        func_151D2718(((s16 *)arg1)[3]);
        break;
    case 21:
        func_151616D0(0x20, 0x18, 0);
        break;
    case 22:
        func_151616D0(0x23, 0x28, 0);
        func_151616D0(0x24, 0x28, 0);
        break;
    }
}

extern void func_15197A7C(void *);
extern void func_151645C4(u8);
extern void func_1515F170(s32, u8);
extern void func_150DEC28(u8, u8);

typedef struct {
    f32 unk0;
    u8 unk4;
    u8 unk5;
    u8 unk6;
    u8 unk7;
} GameC9EC0Msg;

extern u8 D_800A0960[][16];

s32 func_1509D8FC(s32 arg0, s32 arg1, GameC9EC0Cmd *arg2) {
    s32 idx;

    switch (arg0) {
    case 52:
        if (arg1 == 3) {
            func_15197A7C(func_1505EEF4(arg2->unk4 & 0xFFF));
        }
        break;
    case 50:
        if (arg1 == 2) {
            func_151403A8(0, 0x53);
        } else if (arg1 == 3) {
            func_151403A8(0, 0x54);
        }
        break;
    case 45:
        func_151645C4(arg1 == 6);
        break;
    case 40:
        if (arg1 == 2) {
            func_1515F170(4, 1);
            func_1515F170(5, 0);
        } else if (arg1 == 3) {
            func_1515F170(4, 0);
            func_1515F170(5, 1);
        }
        break;
    case 31:
        if (arg1 == 5) {
            u8 sp38[4];

            sp38[0] = arg2->unk8;
            func_151403A8((s32)sp38, 0x36);
        }
    case 30:
        if (arg1 == 2) {
            u8 sp34[4];

            sp34[0] = arg2->unk8;
            func_151494E0((s32)sp34, 0x34);
        }
        break;
    case 29:
        if (arg1 == 5) {
            GameC9EC0Msg msg;

            msg.unk0 = arg2->unkC;
            msg.unk4 = arg2->unk8;
            msg.unk5 = arg2->unk10;
            msg.unk6 = arg2->unk14;
            msg.unk7 = arg2->unk18;
            func_1516944C(0x35, (s32)&msg, 0x33);
        }
        break;
    case 28:
        if (arg1 == 5) {
            s32 i;

            i = arg2->unk8;
            if (i < 0 || i >= 3) {
                return 1;
            }
            func_151494E0((s32)D_800A0960[i], 0x32);
        }
        break;
    case 11:
    case 12:
    case 13:
    case 14:
        {
            u8 a;
            u8 b;

            idx = arg0 & 0x3F;
            if (idx == 11) {
                a = 1;
            } else if (idx == 12) {
                a = 2;
            } else if (idx == 13) {
                a = 3;
            } else if (idx == 14) {
                a = 4;
            } else {
                a = 0;
            }
            if (arg1 == 2) {
                b = 0x17;
            } else if (arg1 == 3) {
                b = 0x18;
            } else {
                b = 0x17;
            }
            func_151616D0(a, b, 0);
        }
        break;
    case 17:
        func_150DEC28(((u8 *)arg2)[0xB], arg1 == 3);
        break;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_C9EC0/func_1509DBBC.s")
