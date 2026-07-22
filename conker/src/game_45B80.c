#include <ultra64.h>

#include "functions.h"
#include "variables.h"


void* func_151674F8(void *arg0, s32 arg1, s16 arg2, s32 arg3);
Gfx *func_15174AA4(Gfx *arg0, s32 arg1, s32 arg2);
Gfx *func_1510B7B4(Gfx *arg0, s32 arg1);
Gfx *func_151135C4(Gfx *arg0, s32 arg1, s16 arg2);
Gfx *func_15186794(Gfx *arg0, s32 arg1);
Gfx *func_15188D00(Gfx *arg0, s32 arg1, s16 arg2);
Gfx *func_151D6778(Gfx *arg0);
Gfx *func_1502BAD0(Gfx *arg0, s32 arg1, s16 arg2);
Gfx *func_15035FE8(Gfx *arg0, s32 arg1);
extern u8 D_80089470;


void func_150186D0(void) {
    func_10001444();
    func_1501A39C();
    func_151E6BFC();

    D_800BE5E0 = 1;
    D_800D18A0 = 0;
    D_800D18A2 = 0;
    D_800D18A4 = 0;
    D_800D23A9 = 0;

    while (func_1501878C() != 0) {};

    D_8002AC60 = 1;
    D_8002AC64 = 3500;
    *D_800BE728 = func_1501BBB8();

    while (func_151DCFD8(1) != 0) {};
}

// something big and interesting
#pragma GLOBAL_ASM("asm/nonmatchings/game_45B80/func_1501878C.s")

void func_15018DFC(void) {
    func_150A09D0(D_800BE9E4);
    func_150619A8();
    func_1501C870();
    if (D_800BEAC0 == 0) {
        if (D_800C35EA == 1) {
            func_1502378C();
        } else {
            func_1504A730();
        }
        func_15085ABC(D_800D2340);
    }
    func_1507C370();
    func_1507C8FC();
}

Gfx *func_15018E88(void *arg0, s16 arg1) {
    if (D_800BE616 == 0) {
        func_1517D7B0(&arg0, 1);
    }
    arg0 = func_151674F8(arg0, 0, arg1, 0);
    arg0 = func_151674F8(arg0, 0, arg1, 1);
    return func_15174AA4(arg0, D_800BE9F0, arg1);
}

void *func_15018F08(void *arg0, s16 arg1) {
    arg0 = func_15174B48(arg0, D_800BE9F0, arg1);
    arg0 = func_151674F8(arg0, 1, arg1, 0);
    arg0 = func_151674F8(arg0, 1, arg1, 1);

    func_1517D7B0(&arg0, 2);

    return arg0;
}

void func_15018F80(s16 arg0) {
    struct108 *sp24 = &D_800DBFF0[arg0];
    D_8003C8E0 = 0xA000000;
    if ((func_1517F40C(arg0) == 0) && (D_800BEAC0 == 0)) {
        func_1517F448(arg0);
    }
    func_1501B640(arg0);
    D_800D3674 = (sp24->unk388 < 0.0f) ? -1000 : 5000;
    func_15172D80(arg0);
    D_8003C8E0 = 0;
}

void func_1501905C(void) {
    D_800BE9D0 = D_800BE9D8[D_800BE9C0];
    *D_800BE728 = func_1501BBB8();
    func_15019F20();
    if ((D_800BEAC1 != 0) && (D_800BEAC0 == 0)) {
        func_15169040(0, 0x47);
    }
    func_1501C1B0();
    func_1501BB20();
    func_1502C380();
    if (0) {};
    func_1000D758(D_800DBFF0->unk2A4, D_800DBFF0->unk2A8, D_800DBFF0->unk2AC);
    func_10011BB8();
    if (D_800E0B94 == 2) {
        func_150ADACC(0x81280783); // 2166884227
    }
    func_10012020();
}

// few loops
#pragma GLOBAL_ASM("asm/nonmatchings/game_45B80/func_15019130.s")

void func_15019414(void) {
    if (D_800BEAC0 == 0) {
        func_15167010();
    }
    func_1517ABB0();
    if (D_800BE616 == 0) {
        func_1508F0A4();
    }
}

s32 func_1501A490(s32 arg0, s16 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5);
void func_1510B958(s32 arg0);
s32 func_1510B9D0(s32 arg0, s16 arg1);
s32 func_1515D6D0(s32 arg0, s32 arg1);
s32 func_1517EFAC(s32 arg0);
extern s16 D_80084480;
extern s32 D_800BE9F0;
extern s32 D_800BE628;
extern u8 D_800BE9C0;
extern u8 D_800BEAC0;
extern u16 D_800D18A0;
s32 func_1510FEA0(s32 arg0, s32 arg1);
s32 func_15019464(Gfx *arg0, s16 arg1)
{
 func_1510B958(arg1); { Gfx *_g = (Gfx *) (arg0++); _g->words.w0 = ((((unsigned int) ((((unsigned int) 0xdc) & ((0x01 << 8) - 1)) << 24)) | ((unsigned int) ((((unsigned int) (((sizeof(Vp)) - 1) / 8)) & ((0x01 << 5) - 1)) << 19))) | ((unsigned int) ((((unsigned int) (0 / 8)) & ((0x01 << 8) - 1)) << 8))) | ((unsigned int) ((((unsigned int) 8) & ((0x01 << 8) - 1)) << 0)); _g->words.w1 = (unsigned int) ((((D_800BE628 ^ 0) + (arg1 * 0x180)) + (D_800BE9C0 * 0x10)) + 0x40); } ;
  arg0 = (Gfx *) func_1501A490((s32) arg0, arg1, 0, 0, 0, 0);
  if (D_800BEAC0 != 0)
  {
    return (s32) arg0;
  }
  if (D_80084480 != 0)
  {
    return (s32) arg0;
  }
  arg0 = (Gfx *) func_1510FEA0((s32) arg0, D_800BE9F0);
  if ((func_1517EFAC(arg1) != 0) || ((D_800D18A0 & (1 << arg1)) != 0))
  {
    return (s32) arg0;
  }
  arg0 = (Gfx *) func_1515D6D0((s32) arg0, arg1);
  return func_1510B9D0((s32) arg0, arg1);
}

// NON-MATCHING: 70% of the way there... maybe.
// s32 func_15019464(Gfx *arg0, s16 arg1) {
//     s32 temp_s0;
//     s32 ret;
//
//     func_1510B958(arg1);
//     gSPViewport(arg0++, (D_800BE628 + (arg1 * 0x180) + (D_800BE9C0 * 0x10) + 0x40));
//     // arg0->unk0 = 0xDC080008;
//     // arg0->unk4 = (s32) (D_800BE628 + (temp_t6 * 0x180) + (D_800BE9C0 * 0x10) + 0x40);
//     temp_s0 = func_1501A490(arg0, arg1, 0, 0, 0, 0);
//     if ((D_800BEAC0 != 0) || (D_80084480 != 0)) {
//         return temp_s0;
//     }
//
//     temp_s0 = func_1510FEA0(temp_s0, D_800BE9F0);
//     if ((func_1517EFAC(arg1) != 0) || ((D_800D18A0 & (1 << arg1)) != 0)){
//         return temp_s0;
//     }
//
//     temp_s0 = func_1515D6D0(temp_s0, arg1);
//     temp_s0 = func_1510B9D0(temp_s0, arg1);
//     return temp_s0;
//
// }

Gfx *func_150195A0(Gfx *arg0, s16 arg1)
{
    struct108 *sp2C;
    Gfx *temp_v0;

    sp2C = &D_800DBFF0[arg1];
    if (D_800BEAC0 != 0) {
        return arg0;
    }
    if (D_80084480 != 0) {
        return arg0;
    }
    if ((func_1517EFAC(arg1) != 0) || ((D_800D18A0 & (1 << arg1)) != 0)) {
        return arg0;
    }
    if (D_80082FA0 > 0) {
        arg0 = func_1515D6D0((s32)func_1510B7B4(arg0, arg1), arg1);
        func_1510B958(arg1);
        gSPViewport(arg0++, (((D_800BE628 ^ 0) + (arg1 * 0x180)) + (D_800BE9C0 * 0x10)) + 0x40);
        arg0 = (Gfx *) func_1501A490((s32) arg0, arg1, 0, 0, 0, 0);
    }
    arg0 = func_151135C4(arg0, 1, arg1);
    if (D_800BE575 == 2) {
        arg0 = func_151D6778(arg0);
    }
    arg0 = func_151674F8(arg0, 6, arg1, 0);
    arg0 = func_151674F8(arg0, 6, arg1, 1);
    arg0 = func_15186794(arg0, arg1);
    arg0 = (Gfx *) func_1501A490((s32) arg0, arg1, 0, 0, 0, 0);
    arg0 = func_1502BAD0(arg0, 1, arg1);
    temp_v0 = func_15035FE8(arg0, arg1);
    arg0 = temp_v0;
    gSPMatrix(arg0++, &D_80089470, G_MTX_LOAD);
    if (sp2C->unk5F0 & 1) {
        arg0 = func_15018E88(arg0, arg1);
        arg0 = func_151135C4(arg0, 0, arg1);
        arg0 = func_15018F08(arg0, arg1);
    } else {
        arg0 = func_15018F08(arg0, arg1);
        arg0 = func_151135C4(arg0, 0, arg1);
        arg0 = func_15018E88(arg0, arg1);
    }
    arg0 = func_15188D00(arg0, 0, arg1);
    arg0 = func_15188D00(arg0, 1, arg1);
    arg0 = func_1502BAD0(arg0, 2, arg1);
    arg0 = func_151674F8(arg0, 2, arg1, 0);
    return func_151674F8(arg0, 2, arg1, 1);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_45B80/func_150198FC.s")

void func_15019BB8(Gfx *arg0, s32 arg1) {
    gSPViewport(arg0++, (s32)((u8 *)D_800BE628 + arg1 * 0x180) + D_800BE9C0 * 0x10 + 64);
    arg0 = (Gfx *)func_1501A490((s32)arg0, arg1, 0, 0, 0, 0);
    arg0 = (Gfx *)func_1517F4D8((s32)arg0, arg1);
    arg0 = (Gfx *)func_1517F3A0((s32)arg0, arg1);
    arg0 = (Gfx *)func_15180580((s32)arg0, arg1);
    if ((D_800D18A0 & (1 << arg1)) || (D_800D18A2 & (1 << arg1))) {
        arg0 = (Gfx *)func_1507DB6C((s32)arg0, arg1);
    }
    arg0 = (Gfx *)func_151674F8(arg0, 4, arg1, 0);
    arg0 = (Gfx *)func_151674F8(arg0, 4, arg1, 1);
}
// NON-MATCHING: need to figure out what is going on
// void func_15019BB8(struct14 *arg0, s32 arg1) {
//     s32 temp_v0;
//     s32 sp2A;
//     s16 sp28;
//
//     arg0->unk0 = 0xDC080008;
//     arg0->unk4 = &D_800BE628[arg1].unk40[D_800BE9C0];
//     sp28 = arg1;
//
//     temp_v0 = func_1501A490(&arg0->unk8, &sp28, 0, 0, 0, 0);
//     temp_v0 = func_1517F4D8(temp_v0, arg1);
//     temp_v0 = func_1517F3A0(temp_v0, arg1);
//     temp_v0 = func_15180580(temp_v0, arg1);
//     // temp_v1 = 1 << arg1;
//     if (((D_800D18A0 & (1 << arg1)) != 0) || ( ((D_800D18A2 & (1 << arg1)) != 0))) {
//         temp_v0 = func_1507DB6C(temp_v0, arg1);
//     }
//     temp_v0 = func_151674F8(temp_v0, 4, sp2A, 0);
//     func_151674F8(temp_v0, 4, sp2A, 1);
// }

#pragma GLOBAL_ASM("asm/nonmatchings/game_45B80/func_15019CC8.s")

void func_15019E60(Gfx *arg0) {
    if (D_80082FA0 != 0) {
        D_80082FA4 = D_80082FA0 + 1;
        gSPViewport(arg0++, (D_80082FA4 * 0x180) + D_800BE628 + 64);
    } else {
        gSPViewport(arg0++, D_800BE628 + 64);
    }
    func_15043384(func_151E8620(func_1501A490(arg0, 0xFF, 0, 0, 0, 0)));
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_45B80/func_15019F20.s")
