#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_1F3780/func_151C62D0.s")

void func_151C69CC(void *a0, s32 a1, u8 a2);

void func_151C6974(void *a0, s32 a1, s32 a2) {
    func_151C69CC(a0, a2, 0);
}

void func_151C69A0(void *a0, s32 a1, s32 a2) {
    func_151C69CC(a0, a2, 1);
}

typedef struct 
{
  s32 unk0;
  s32 unk4;
  s32 unk8;
} D_800AAB08Entry;
extern s32 D_800AAB00[];
extern D_800AAB08Entry D_800AAB08[];
void func_151C69CC(void *a0, s32 a1, u8 a2);
void func_151C69CC(void *a0, s32 a1, u8 a2)
{
  D_800AAB08Entry *temp_a0;
  s32 temp_a2;
  temp_a2 = ((s32 *) a0)[0x1D4 / 4] + D_800AAB00[a2];
  temp_a0 = &D_800AAB08[a2];
  func_15143134(temp_a0, a1, temp_a2);
}


#pragma GLOBAL_ASM("asm/nonmatchings/game_1F3780/func_151C6A28.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1F3780/func_151C6D70.s")

struct blk12_C6EA0 { s32 a; s32 b; s32 c; };

typedef struct {
    u8 pad_0[0x3B];
    u8 field_0x3B;
} ActorIdByteFields;

typedef struct {
    u8 pad_0[0x170];
    u8 field_0x170;
} CreatedObjectFlagFields;

s32 func_1513264C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, u8 arg5, s32 arg6);

void func_151C6EA0(ActorIdByteFields *arg0, u8 arg1, s32 arg2) {
    struct {
        f32 unk00;
        f32 unk04;
        f32 unk08;
        f32 unk0C;
        struct blk12_C6EA0 unk10;
        f32 unk1C;
        f32 unk20;
        f32 unk24;
        struct blk12_C6EA0 unk28;
        struct blk12_C6EA0 unk34;
        struct blk12_C6EA0 unk40;
        f32 unk4C;
        s32 unk50;
        s16 unk54;
        s16 unk56;
        u8 unk58;
        u8 pad59[3];
        s32 unk5C;
        u8 unk60;
        u8 unk61;
        u8 unk62;
        u8 unk63;
        u8 unk64;
        u8 unk65;
        u8 unk66;
        u8 unk67;
        u8 unk68;
        s8 unk69;
        u8 unk6A;
        u8 pad6B;
        s32 unk6C;
        u8 unk70;
        u8 pad71;
        s16 unk72;
        s16 unk74;
        u8 pad76[2];
        s32 unk78;
    } sp34;
    struct { u8 b; u8 pad[3]; } sp30;
    struct blk12_C6EA0 *src = (struct blk12_C6EA0 *)&D_800A5480;
    CreatedObjectFlagFields *temp_v0;

    sp30.b = 0;
    sp34.unk00 = 1.0f;
    sp34.unk04 = 1.0f;
    sp34.unk0C = 1.0f;
    sp34.unk08 = 1.0f;
    sp34.unk10 = *src;
    sp34.unk1C = 1.0f;
    sp34.unk20 = 1.0f;
    sp34.unk24 = 1.0f;
    sp34.unk28 = *src;
    sp34.unk34 = *src;
    sp34.unk40 = *src;
    sp34.unk50 = 0x11900;
    sp34.unk54 = 0x12C;
    sp34.unk56 = 0xF;
    sp34.unk58 = 0;
    sp34.unk5C = 0;
    sp34.unk60 = 0x64;
    sp34.unk61 = 0x17;
    sp34.unk62 = 0;
    sp34.unk63 = 0;
    sp34.unk64 = 0;
    sp34.unk65 = 0;
    sp34.unk66 = 0;
    sp34.unk67 = 0;
    sp34.unk68 = 0x5;
    sp34.unk69 = -1;
    sp34.unk6A = 1;
    sp34.unk4C = 0.0f;
    sp34.unk6C = (s32)arg0;
    sp34.unk70 = arg0->field_0x3B;
    sp34.unk72 = 1;
    sp34.unk74 = 0xFF;
    sp34.unk78 = 0;

    temp_v0 = (CreatedObjectFlagFields *)func_1513264C((s32)&sp34, 3, 0xFF, 0, 1, arg1, arg2);
    if (temp_v0 != 0) {
        memcpy(&temp_v0->field_0x170, &sp30.b, 1);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1F3780/func_151C7038.s")
