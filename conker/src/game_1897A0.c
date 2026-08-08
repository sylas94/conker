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

typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
} Struct1515D130Src;

typedef struct {
    Struct1515D130Src *unk0;
    f32 unk4;
} Struct1515D130Emitter;

typedef struct {
    u8 pad0[0x1];
    u8 unk1;
    u8 pad2[0xA];
    u8 unkC;
    u8 padD[0x1B];
    Struct1515D130Emitter unk28;
    u8 unk30;
} Struct1515D130Arg0;

typedef struct {
    f32 unk0;
    f32 unk4;
    s32 unk8;
    s32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    s32 unk28;
    s32 unk2C;
    s16 unk30;
    s16 unk32;
    s16 unk34;
    s16 unk36;
    s16 unk38;
    u8 pad3A[2];
    f32 unk3C;
} Struct1515D130Preset;

typedef struct {
    s32 unk0;
    s32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
    s16 unk2C;
    s16 unk2E;
    s16 unk30;
    s16 unk32;
    s32 unk34;
    s32 unk38;
    s16 unk3C;
    s16 unk3E;
    u16 unk40;
    u8 unk42;
    u8 unk43;
    u8 unk44;
    u8 unk45;
    u8 unk46;
    u8 unk47;
    u8 unk48;
    u8 unk49;
    u8 unk4A;
    u8 unk4B;
    u8 unk4C;
    u8 unk4D;
    u8 unk4E;
    u8 unk4F;
    u8 unk50;
    u8 unk51;
    u8 unk52;
    u8 unk53;
    u8 unk54;
    u8 unk55;
    u8 unk56;
    u8 unk57;
    u8 unk58;
    u8 pad59[3];
    s32 unk5C;
    s32 unk60;
    s16 unk64;
    s16 unk66;
    s16 unk68;
    u8 unk6A;
    u8 pad6B[1];
    f32 unk6C;
    s8 unk70;
    s8 unk71;
} Struct1515D130Spawn;

extern Struct1515D130Preset D_800A64A0[];
extern void func_15143794(s32, s32, f32, f32 *);
extern void func_15152B38(Struct1515D130Spawn *, u8, s32);

void func_1515D130(Struct1515D130Arg0 *arg0) {
    Struct1515D130Preset *preset;
    Struct1515D130Emitter *emitter;
    Struct1515D130Spawn spawn;
    s32 rand0;
    s32 rand1;

    preset = &D_800A64A0[arg0->unk30];
    emitter = &arg0->unk28;
    emitter->unk4 += preset->unk0 + (func_150ADA68() * preset->unk4);

    while (emitter->unk4 > 1.0f) {
        spawn.unk0 = preset->unk8;
        spawn.unk4 = preset->unkC;
        spawn.unk14 = preset->unk10;
        spawn.unk18 = preset->unk14;
        spawn.unk1C = preset->unk18;
        spawn.unk20 = preset->unk1C;
        spawn.unk24 = preset->unk20;
        spawn.unk28 = preset->unk24;
        spawn.unk2C = 0;
        spawn.unk2E = 0xFF;
        spawn.unk30 = -0x3F;
        spawn.unk32 = 0x50;
        spawn.unk34 = preset->unk28;
        spawn.unk38 = preset->unk2C;
        spawn.unk3C = preset->unk30;
        spawn.unk3E = preset->unk32;
        spawn.unk40 = 1;
        spawn.unk42 = 0xC;
        spawn.unk43 = 2;
        spawn.unk44 = 3;
        spawn.unk45 = 0xB4;
        spawn.unk46 = 0;
        spawn.unk47 = 0;
        spawn.unk48 = 0x9B;
        spawn.unk49 = 0x32;
        spawn.unk4A = 0x64;
        spawn.unk4B = 0;
        spawn.unk4C = 0x64;
        spawn.unk4D = 0xFF;
        spawn.unk4E = 0xFF;
        spawn.unk4F = 0xFF;
        spawn.unk50 = 0xFF;
        spawn.unk51 = 0;
        spawn.unk52 = 0;
        spawn.unk53 = 0;
        spawn.unk54 = 0;
        spawn.unk55 = 0xFF;
        spawn.unk56 = 0;
        spawn.unk57 = 1;
        spawn.unk58 = 0x24;
        spawn.unk5C = 0x200005;
        spawn.unk60 = 0x60600;
        spawn.unk64 = preset->unk34;
        spawn.unk66 = preset->unk36;
        spawn.unk68 = preset->unk38;
        spawn.unk6A = 0;
        spawn.unk6C = preset->unk3C;
        spawn.unk70 = -1;
        spawn.unk71 = 0;
        rand0 = func_150ADA20();
        rand1 = func_150ADA20();
        func_15143794((s16) (rand0 & 0xFF), (s16) (0x40 - (rand1 & 0x7F)), emitter->unk0->unk6, &spawn.unk8);
        spawn.unk8 += emitter->unk0->unk0;
        spawn.unkC += emitter->unk0->unk2;
        spawn.unk10 += emitter->unk0->unk4;
        func_15152B38(&spawn, arg0->unkC, arg0->unk1);
        emitter->unk4 -= 1.0f;
    }
}
