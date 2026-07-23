#include <ultra64.h>

#include "functions.h"
#include "variables.h"

typedef struct {
    u8 pad0[0x10];
    s32 unk10;
} Struct1515C2F0Arg0;

typedef struct {
    u8 pad0[0x98];
    void *unk98;
} Struct1515C2F0Ret;

extern Struct1515C2F0Ret *func_15147A80(void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);

void *func_1515C2F0(Struct1515C2F0Arg0 *arg0, s32 arg1, void *arg2, s32 arg3, u8 arg4, s32 arg5) {
    Struct1515C2F0Ret *temp_v0;
    Struct1515C2F0Ret *sp3C;

    arg0->unk10 = 0xA;
    temp_v0 = func_15147A80(arg0, arg1 + 0x40, 0x10, 8, 8, 8, 0, 0, arg3, arg4, arg5);
    if (temp_v0 == 0) {
        return NULL;
    }
    sp3C = temp_v0;
    memcpy(temp_v0->unk98, arg2, 0x3C);
    return sp3C;
}
// void *func_1515C2F0(void *arg0, void *arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5) {
//     void *sp3C;
//     void *temp_v0;
//
//     arg0->unk10 = 0xA;
//     temp_v0 = func_15147A80(&arg1->unk40, 0x10, 8, 8, 8, 0, 0, arg3, (?32) arg4, arg5);
//     if (temp_v0 == 0) {
//         return NULL;
//     }
//     sp3C = temp_v0;
//     memcpy(temp_v0->unk98, arg2, 0x3C); // memcpy
//     return sp3C;
// }

#pragma GLOBAL_ASM("asm/nonmatchings/game_1897A0/func_1515C388.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1897A0/func_1515C534.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1897A0/func_1515C6F4.s")
// PERMUTER CANDIDATE (best 215): logic byte-identical (element base + unk94 cached), only
// register renames remain (unk94 vs element-base register swap, -1 temp).
#pragma GLOBAL_ASM("asm/nonmatchings/game_1897A0/func_1515CF9C.s")

typedef struct {
    char pad0[0x25];
    u8 unk25;
    char pad26[0x6];
    s8 unk2C;
    char pad2D[0x1];
    s8 unk2E;
} Struct1515D030;

s32 func_1515D030(Struct1515D030 *arg0, s32 arg1) {
    s8 temp_v0;
    s32 phi_v1;

    temp_v0 = arg0->unk2C;
    phi_v1 = 1;
    if ((s32) temp_v0 >= 3) {
        arg0->unk2C = (s8) (temp_v0 - 1);
        arg0->unk2E = (s8) (arg0->unk2E - 1);
        if ((s32) arg0->unk2E < 0) {
            arg0->unk2E = (s8) (arg0->unk25 - 1);
            phi_v1 = 1;
        }
    } else {
        phi_v1 = 0;
    }
    return phi_v1;
}

// s32 func_1515D030(void *arg0, ? arg1) {
//     s8 temp_v0;
//     s32 phi_v1;
//
//     temp_v0 = arg0->unk2C;
//     if ((s32) temp_v0 >= 3) {
//         arg0->unk2C = (s8) (temp_v0 - 1);
//         arg0->unk2E = (s8) (arg0->unk2E - 1);
//         phi_v1 = 1;
//         if ((s32) arg0->unk2E < 0) {
//             arg0->unk2E = (s8) (arg0->unk25 - 1);
//             phi_v1 = 1;
//         }
//     } else {
//         phi_v1 = 0;
//     }
//     return phi_v1;
// }

struct260 *func_151491F4(s16 arg0, s8 arg1, s8 arg2, u8 arg3, u8 arg4, s32 arg5, u8 arg6, s32 arg7);
typedef struct 
{
  u8 pad0[0x18];
  s32 unk18;
} Struct1515D088Arg0;
s32 func_1515D088(Struct1515D088Arg0 *arg0)
{
  s32 temp_v0_2;
  struct 
  {
    void *unk0;
    f32 unk4;
    s8 unk8;
  } sp30;
  temp_v0_2 = arg0->unk18;
  sp30.unk8 = (s8) (temp_v0_2 & 0xFFFF);
  if (((temp_v0_2 & 0xFF) < 0) || ((temp_v0_2 & 0xFF) >= 2))
  {
    return 0;
  }
  sp30.unk0 = arg0;
  sp30.unk4 = 0.0f;
  temp_v0_2 = (s32) func_151491F4(0x12C, -1, 0x11, 0, 0xD, 0xC, 0xFF, 1);
  if (temp_v0_2 != 0)
  {
    memcpy((void *) (temp_v0_2 + 0x28), &sp30, 0xC);
  }
  return temp_v0_2;
}

// s32 func_1515D088(void *arg0) {
//     s32 sp3C;
//     s8 sp38;
//     f32 sp34;
//     void *sp30;
//     s32 temp_t7;
//     s32 temp_v0;
//     void * temp_v0_2;
//     s32 phi_v1;
//
//     temp_t7 = arg0->unk18;
//     temp_v0 = temp_t7 & 0xFF;
//     sp38 = (s8) temp_t7;
//     if ((temp_v0 < 0) || (temp_v0 >= 2)) {
//         return 0;
//     }
//     sp30 = arg0;
//     sp34 = 0.0f;
//     temp_v0_2 = func_151491F4(0x12C, -1, 0x11, 0, 0xD, 0xC, 0xFF, 1);
//     phi_v1 = &temp_v0_2;
//     if (temp_v0_2 != 0) {
//         sp3C = temp_v0_2;
//         memcpy(temp_v0_2->unk28, &sp30, 0xC); // memcpy
//         phi_v1 = sp3C;
//     }
//     return phi_v1;
// }

// fat struct
#pragma GLOBAL_ASM("asm/nonmatchings/game_1897A0/func_1515D130.s")
