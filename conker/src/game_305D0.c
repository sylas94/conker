#include <ultra64.h>

#include "functions.h"
#include "variables.h"


// what is this loop doing?
extern s32 D_800B0E30[];
extern u8 D_800B0E34[];
typedef struct 
{
  s32 unk0;
  s32 unk4;
  s32 unk8;
} Struct15003120;
void func_15003120(s32 arg0, s32 arg1, s32 arg2)
{
  s32 i;
  s32 count;
  s32 head;
  ((s32 *) D_800B0E30[0])[arg0] = arg2;
  ((u8 *) ((s32 *) D_800B0E34)[0])[arg0] = 0;
  if (arg2 == 0)
  {
    return;
  }
  ((s32 *) D_800B0E30[0])[arg0] += arg1;
  count = 0;
  i = 0;
  head = ((s32 *) D_800B0E30[0])[arg0];
  if (((Struct15003120 *) head)->unk0 != 0)
  {
    do
    {
      ((Struct15003120 *) ((s32 *) D_800B0E30[0])[arg0])[i].unk0 += arg1;
      ((Struct15003120 *) ((s32 *) D_800B0E30[0])[arg0])[i].unk4 += arg1;
      count++;
      i++;
    }
    while (((Struct15003120 *) ((s32 *) D_800B0E30[0])[arg0])[i].unk0 != 0);
  }
  ((u8 *) ((s32 *) D_800B0E34)[0])[arg0] = count;
}


typedef struct
{
  s32 unk0;
  s32 unk4;
  s32 unk8;
  s32 unkC;
  s32 unk10;
  s32 unk14;
  s32 unk18;
  s32 unk1C;
  s32 unk20;
} AssetHeader;

typedef struct
{
  AssetHeader *unk0;
  s32 unk4;
} AssetEntry;

extern s32 D_800B0E10[];
extern s32 D_800B0E20[];
extern u8  D_800B0E38;
extern s32 D_800B0E40[];
extern AssetEntry *D_800B0E50;

extern void *allocate_memory(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
extern AssetEntry *func_1502B6BC(s32 *arg0, s32 arg1, s32 *arg2, s32 arg3, s32 arg4, s32 arg5);
extern s32 func_150049A4(s32 arg0, s32 arg1, s32 arg2);
extern s32 func_1510CE60(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 *arg4);
extern s32 func_1510D0EC(s32 arg0, s32 *arg1, s32 arg2, s32 arg3);

void func_150031EC(s32 arg0)
{
  AssetEntry *table;
  AssetHeader *asset;
  s32 count;
  s32 loaded;
  u32 i;
  s32 j;
  s32 k;
  s32 sp50;
  s32 tex;

  if (arg0 >= 0x45)
  {
    arg0 = 0;
  }
  table = func_1502B6BC(&loaded, 0, &count, 2, 4, arg0);
  D_800B0E50 = table;
  for (k = 1; k < 4; k++)
  {
    D_800B0E00[k] = 0;
    D_800B0E10[k] = 0;
    D_800B0E40[k] = 0;
  }
  func_150034B4();
  if (loaded != 0)
  {
    D_800B0E30[0] = (s32) allocate_memory(count * 4, 1, 0, 0);
    ((s32 *) D_800B0E34)[0] = (s32) allocate_memory(count, 1, 0, 0);
    bzero((void *) ((s32 *) D_800B0E34)[0], count);
    bzero((void *) D_800B0E30[0], count);
    D_800B0E38 = count;
    for (i = 0; i < count; i++)
    {
      asset = table[i].unk0;
      if ((asset != 0) && (table[i].unk4 != 0))
      {
        if (asset->unk0 != 0)
        {
          asset->unk0 += (s32) asset;
        }
        if (asset->unk8 != 0)
        {
          asset->unk8 += (s32) asset;
        }
        if (asset->unk10 != 0)
        {
          asset->unk10 += (s32) asset;
        }
        func_15003120(i, (s32) asset, asset->unk20);
        if (i < 4)
        {
          D_800B0E00[i] = asset->unk0;
          D_800B0E10[i] = (s32) asset + 0x28;
          D_800B0E40[i] = (u32) (D_800B0E00[i] - D_800B0E10[i]) >> 4;
          D_800B0E20[i] = asset->unk8;
          if (i == 0)
          {
            func_150039BC(asset->unk10);
          }
          func_150049A4(D_800B0E00[i], D_800B0E10[i] + 0xFF000000, (s32) asset);
          func_1510CE60(D_800B0E00[i], 0, 1, 0x3F, 0);
        }
        else
        {
          func_150049A4(asset->unk0, 0, (s32) asset);
        }
      }
    }
  }
  if (((u8 *) D_800B0DF0)[0x4B] != 0)
  {
    j = 0;
    while ((tex = ((s32 **) &D_80082B20)[((u8 *) D_800B0DF0)[0x4B]][j++]) != 0)
    {
      func_1510D0EC(tex, &sp50, 0x3E, 0);
    }
  }
}

s32 func_150034B4(void) {
      s32 i;

      for (i = 0; i < 7762; i++) {
          D_800B0E58[i] = -1;
          D_800BC448[i] = 0;
      }

      D_800D9F58 = 0xFFFF; // -1 s16?
      D_800D9F5C = -1;

      if ((D_800BE9F0 != 1) && (D_800BE9F0 != 50)) {
          D_800D9F60 = 0;
      } else {
          D_800D9F60 = 1;
      }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_305D0/func_15003570.s")
// NON-MATCHING: something along these lines
// void func_15003570(void) {
//     s32 temp_s4;
//     s32 phi_s0;
//     s32 phi_s1;
//
//     s32 i;
//     u8 *temp_v0;
//     s16 *phi_s2;
//     s16 *phi_s3;
//
//     temp_s4 = allocate_memory(16, 1, 2, 0);
//
//     phi_s0 = 0x1A37E0; // 1718240
//     phi_s2 = D_80091D20;
//     phi_s3 = D_800B87A0;
//
//     for (i = 0; i < 7762; i++) {
//         if ((phi_s0 & 1) != 0) {
//             phi_s0 = phi_s0 - 1;
//             phi_s1 = 1;
//         } else {
//             phi_s1 = 0;
//         }
//         func_10004514(phi_s0, temp_s4, 16, 1);
//         temp_v0 = temp_s4 + phi_s1;
//         phi_s2[i] = (*temp_v0 << 24) + (*(temp_v0 + 1) << 16) + (*(temp_v0 + 2) << 8) + *(temp_v0 + 3);
//         phi_s0 = phi_s3[i];
//     }
//
//     func_10004074(temp_s4);
// }

#pragma GLOBAL_ASM("asm/nonmatchings/game_305D0/func_15003668.s")
// NON-MATCHING: score 125, instruction-for-instruction identical; the only
// residual is a 3-way rotation of the callee-saved registers holding the loop
// counter (target s1 / IDO s2), the hoisted &D_800DBEF4 base (target s2 / IDO
// s3) and `start` (target s3 / IDO s1). Declaration order, block scoping,
// merging `start` with `size`, chained assignment, `register` and using the
// (unused) parameter as the scratch all leave the rotation unchanged --
// permuter candidate.
//
// typedef struct {
//     s32 unk0;
//     s32 unk4;
// } SegmentEntry;
//
// typedef struct {
//     u8  pad0[0x1C];
//     s32 unk1C;
//     u8  pad20[0x2F];
//     u8  unk4F;
//     u8  pad50[0x6];
//     s16 unk56;
//     s16 unk58;
//     u8  pad5A[0x46];
// } SceneObject; /* size 0xA0 */
//
// extern void func_15001460(s32 arg0);
// extern void func_15002754(void);
// extern s32 func_15002878(void);
// extern void func_1510F800(s32 arg0);
//
// void func_15003668(s32 arg0) {
//     s32 start;
//     s32 size;
//     s32 i;
//
//     arg0 = arg0;
//     D_800DBE62 = (u8)0;
//     func_15001970();
//     D_800D2C68 = (u8)0;
//
//     func_150026C4(0);
//     func_15002724(D_800B0E00[0]);
//     func_15002754();
//     func_15001460(D_800B0E00[0]);
//     func_150026E8(0);
//
//     func_150026C4(1);
//     func_15002724(D_800B0E00[3]);
//     func_15002754();
//     func_15001460(D_800B0E00[3]);
//     func_150026E8(1);
//
//     func_150026C4(2);
//     for (i = 0; i < D_800DBEF0; i++) {
//         if ((((SceneObject *)D_800DBEF4)[i].unk4F & 0x60) != 0x20) {
//             func_15002724(((SceneObject *)D_800DBEF4)[i].unk1C);
//         }
//     }
//     func_15002754();
//
//     D_800D2C68 = (u8)1;
//     D_800D2C2C = 0;
//     for (i = 0; i < D_800DBEF0; i++) {
//         if ((((SceneObject *)D_800DBEF4)[i].unk4F & 0x60) != 0x20) {
//             start = D_800DBE38;
//             ((SceneObject *)D_800DBEF4)[i].unk58 = start;
//             func_15001460(((SceneObject *)D_800DBEF4)[i].unk1C);
//             ((SceneObject *)D_800DBEF4)[i].unk56 = D_800DBE38 - start;
//         } else {
//             ((SceneObject *)D_800DBEF4)[i].unk58 = 0;
//             ((SceneObject *)D_800DBEF4)[i].unk56 = 0;
//         }
//     }
//     func_150026E8(2);
//
//     D_800D2C68 = (u8)0;
//     ((SegmentEntry *)&D_800D3300)->unk0 = 0;
//     ((SegmentEntry *)&D_800D3300)->unk4 = D_800DBE3C << 8;
//     func_1510F800(0);
//
//     size = (func_15002878() + 7) & ~7;
//     D_800D3668 = D_8003809C;
//     D_800D366C = D_800D3668 + size;
//     func_1510F800(2);
// }

void func_150038A0(void) {
    func_15001A08();
    func_15001BC8(0, &D_800DBE2A, &D_800DBE2C);
    func_15001BC8(1, 0, 0);
    func_15001CEC(2);
    func_1510F800(0);
    func_150025FC();
    D_800DBE62 = (u8)1;
}

s32 func_1500390C(s32 arg0) {
    s32 i;

    for (i = 0; i < 7762; i++) {
        if (arg0 == D_800B0E58[i]) {
            return i;
        }
    }
    return -1;
}

void func_150039B0(s32 arg0) {
}

void func_150039BC(s32 arg0) {
    D_800DBE5C = arg0;
    if (D_800DBE5C) {
        D_800DBE5C += 8;
    }
}
