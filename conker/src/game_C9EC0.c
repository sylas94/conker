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

extern GameC9EC0Struct D_8008743C[];

s32 func_1509CBD4(s32 arg0) {
    u16 *p;
    s32 ret;
    s32 i;

    p = (u16 *)D_8008743C[arg0].unk0;
    for (i = 0; p[i] != 0xFFFF; i++) {
        ret = func_1509CBD4(p[i]);
        if (!(((u8 *)D_800D2E4C)[p[i] >> 3] & (1 << (p[i] & 7))) || ret == 0) {
            return 0;
        }
    }
    return 1;
}


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


void func_1509CDDC(s32 arg0) {
    s32 i;
    s32 total;

    func_1509CCF4(arg0);
    do {
        total = 0;
        for (i = 0; i != 0xCC; i++) {
            if ((*(u8 (*)[0xF0])&D_800D2E70)[i] == 3) {
                total += func_1509CCF4(i);
            }
        }
    } while (total != 0);
}

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

#pragma GLOBAL_ASM("asm/nonmatchings/game_C9EC0/func_1509D180.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_C9EC0/func_1509D780.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_C9EC0/func_1509D8FC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_C9EC0/func_1509DBBC.s")
