#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern u8 D_800DBEA8[];
extern u8 D_800DD2E4[];
void func_151733E4(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

extern struct104 *D_800B0DF0;
void func_151733E4(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);
extern s8 D_800DD2E0;
typedef struct 
{
  u16 unk0;
  u16 unk2;
  u8 pad4[0x36];
  s16 unk3A;
  s16 unk3C;
  s16 unk3E;
  s16 unk40;
  u8 unk42;
  u8 unk43;
  u8 unk44;
  u8 unk45;
  s8 unk46;
} struct151732E0_arg;
typedef struct 
{
  u8 unk0;
  u8 unk1;
  u8 unk2;
  u8 unk3;
  s16 unk4;
  s16 unk6;
  s16 unk8;
  s16 unkA;
  u16 unkC;
  u16 unkE;
} struct151732E0_state;
extern struct151732E0_state D_8008CC70;
void func_151732E0(s32 arg0)
{
  s16 value;
  s8 idx;
  ;
  if ((((struct151732E0_arg *) D_800B0DF0)->unk3C == ((struct151732E0_arg *) D_800B0DF0)->unk40) && (((struct151732E0_arg *) D_800B0DF0)->unk3C == 0))
  {
    ((struct151732E0_arg *) D_800B0DF0)->unk40 = 0x64;
  }
  D_8008CC70.unk0 = ((struct151732E0_arg *) D_800B0DF0)->unk42;
  D_8008CC70.unk1 = ((struct151732E0_arg *) D_800B0DF0)->unk43;
  D_8008CC70.unk2 = ((struct151732E0_arg *) D_800B0DF0)->unk44;
  D_8008CC70.unk3 = ((struct151732E0_arg *) D_800B0DF0)->unk45;
  D_8008CC70.unk4 = ((struct151732E0_arg *) D_800B0DF0)->unk3A;
  D_8008CC70.unk6 = ((struct151732E0_arg *) D_800B0DF0)->unk3C;
  D_8008CC70.unk8 = ((struct151732E0_arg *) D_800B0DF0)->unk3E;
  D_8008CC70.unkA = ((struct151732E0_arg *) D_800B0DF0)->unk40;
  D_8008CC70.unkC = ((struct151732E0_arg *) D_800B0DF0)->unk2;
  D_8008CC70.unkE = ((struct151732E0_arg *) D_800B0DF0)->unk0;
  if (((struct151732E0_arg *) D_800B0DF0)->unk46 != (-1))
  {
    D_800DD2E0 = 1;
    idx = ((struct151732E0_arg *) D_800B0DF0)->unk46;
    func_151733E4(idx, idx, arg0, 0, -1);
  }
  else
  {
    D_800DD2E0 = 0;
    func_151733E4(0, 0, arg0, 0, -1);
  }
}


Gfx *func_151733D8(Gfx *arg0, s32 arg1) {
    while (1) {
        return arg0;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1A0790/func_151733E4.s")

void func_151738C4(s32 arg0) {
    if (*((s8 *)D_800B0DF0 + 0x46) == -1) {
        if (D_800DBFF0->unk5F0 & 1) {
            func_151733E4(6, 6, arg0, 0, -1);
            D_800DBEA8[0] = D_800DD2E4[0];
            D_800DBEA8[1] = D_800DD2E4[1];
            D_800DBEA8[2] = D_800DD2E4[2];
        } else {
            func_151733E4(0, 0, arg0, 0, -1);
            D_800DBEA8[0] = D_800B0DF0->unk5;
            D_800DBEA8[1] = D_800B0DF0->unk6;
            D_800DBEA8[2] = D_800B0DF0->unk7;
        }
    }
}

s8 func_15173994(s32 arg0) {
    return *((s8*)D_800B0DF0 + 0x46);
}
