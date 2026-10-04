/* tools/nearmiss/func_150F6DE4.c  --  game_124260 (the TU's ONLY remaining pragma)
 *
 * KIND: SNIPPET / PARTIAL TU.  This file is game_124260.c's HEAD (func_150F6DB0 and
 *       the type block) plus the target.  It scores directly with fastscore:
 *           python3 tools/fastscore.py game_124260 func_150F6DE4 tools/nearmiss/func_150F6DE4.c
 *       but to BUILD it you must splice the func_150F6DE4 body + the two typedefs
 *       (EmitDesc / BeamInit / SpawnedObj) into the real TU, replacing the pragma,
 *       and keep everything from `typedef struct { ... } BeamEnd;` onwards.
 *
 * SCORE: raw 78  /  pad-corrected 68.  (Our object emits one trailing alignment
 *        nop that golden's 162-word listing does not have: 10 points of phantom.)
 *        Instruction count and FRAME (0x130) are both correct.
 *
 * WHAT IT IS: spawn a "beam" object.  A 0x78-byte BeamInit is built on the stack
 *   (owner ptr, owner->unique_id at +4, two zeroed slots via a 2-iteration loop,
 *   +0x74 = 0), func_15149130 allocates, memcpy copies it to obj+0x28.  Then a
 *   0x70-byte particle-emitter descriptor is filled and passed to func_15130280
 *   TWICE (identical except the RGBA at +0x18..0x1B: 00 00 FF FF, then FF 00 00 FF),
 *   the two results stored at obj+0x30 / obj+0x34.
 *
 * CALIBRATION: the descriptor is `Struct15131EE4Local` from the MATCHED sibling
 *   game_15D730.c:100 (func_15131EE4 at line ~380 builds the same block and calls
 *   func_15130280).  Copy that struct verbatim and replace its `u8 pad67[9]` with
 *   pad67 / s16 unk68 / pad6A[2] / f32 unk6C -- total size stays 0x70.
 *
 * TWO DISCOVERIES (do not undo):
 *  1. LOCAL LAYOUT.  Locals are allocated top-down in declaration order and the
 *     first-declared sits flush with the frame top.  Golden:
 *        BeamInit spB8 @0xB8 (0x78) | 3 scalars @0xAC..0xB7 | EmitDesc sp3C @0x3C
 *        (0x70) | one 4-byte compiler temp @0x38 (the obj+0x28 spill)
 *     so the declaration order MUST be  spB8, obj, i, dst, sp3C.  Declaring the
 *     EmitDesc first puts spB8 at 0x50 and misses every offset.
 *  2. THE DOUBLE FLOAT STORE COSTS TWO TEMP WORDS IF SPELLED AS TWO READS.
 *        sp3C.unk2C = D_800A1BB0;  sp3C.unk28 = D_800A1BB0;      -> frame 0x138 (114)
 *        sp3C.unk28 = sp3C.unk2C = D_800A1BB0;                   -> frame 0x130 (78)
 *     Two separate reads of the same global CSE to one lwc1 but make IDO reserve
 *     8 extra bytes of temp area, which shifts EVERY sp offset by 8.  The chained
 *     form (and the read-back form `unk28 = sp3C.unk2C;`) both give the right frame.
 *
 * RESIDUAL (68 rows), all in the descriptor-fill window (idx 39..134):
 *   The chained assignment pays for the frame with an extra `swc1 0x68 / lwc1 0x68`
 *   read-back where golden keeps the value in $f0 and stores it twice; that shifts
 *   the whole fill block by one and golden also hoists `addiu $s0,$sp,0x3C` to the
 *   top of the block.  We have NOT found a spelling that gets one load + two
 *   register stores AND a 4-byte temp area.  Everything from idx 135 to the epilogue
 *   already matches byte-for-byte.
 *
 * DO NOT REPEAT (all measured, all flat or worse):
 *   - all 120 declaration permutations x {two-read, chained}: best stays 78; the
 *     second plateau is 82 (any order that does not put spB8 first).
 *   - moving the unk28/unk2C pair to each of the 33 positions in the fill sequence:
 *     best 102.
 *   - `f32 v = D_800A1BB0;` as a named temp (114), `register f32` (114),
 *     reverse store order (114), inlining `dst` (154, loses the spill), unrolling
 *     the 2-iteration loop (242), `u8 i` (116).
 */
#include <ultra64.h>
#include "functions.h"
#include "variables.h"

typedef struct {
    char pad_0[0x3B];
    u8 field_0x3B;
} ActorUniqueIdFields;

void func_150F6DB0(ActorUniqueIdFields *arg0) {
    struct {
        s32 unk0;
        u8 unk4;
    } sp18;

    sp18.unk0 = (s32)arg0;
    sp18.unk4 = arg0->field_0x3B;
    func_151494E0((s32)&sp18, 0x3E);
}

extern f32 D_800A1BB0;
extern void *func_15130280(void *, u8, s32, s32, u8, s32);

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ u8 unk14;
    /* 0x15 */ u8 unk15;
    /* 0x16 */ u8 unk16;
    /* 0x17 */ u8 unk17;
    /* 0x18 */ u8 unk18;
    /* 0x19 */ u8 unk19;
    /* 0x1A */ u8 unk1A;
    /* 0x1B */ u8 unk1B;
    /* 0x1C */ u8 unk1C;
    /* 0x1D */ u8 unk1D;
    /* 0x1E */ s16 unk1E;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ struct17 unk30;
    /* 0x3C */ struct17 unk3C;
    /* 0x48 */ struct17 unk48;
    /* 0x54 */ f32 unk54;
    /* 0x58 */ s32 unk58;
    /* 0x5C */ s32 unk5C;
    /* 0x60 */ u8 unk60;
    /* 0x61 */ u8 unk61;
    /* 0x62 */ s8 unk62;
    /* 0x63 */ s8 unk63;
    /* 0x64 */ s8 unk64;
    /* 0x65 */ u8 unk65;
    /* 0x66 */ u8 unk66;
    /* 0x67 */ u8 pad67;
    /* 0x68 */ s16 unk68;
    /* 0x6A */ u8 pad6A[2];
    /* 0x6C */ f32 unk6C;
} EmitDesc;

typedef struct {
    /* 0x00 */ struct127 *unk0;
    /* 0x04 */ u8 unk4;
    /* 0x05 */ u8 pad5[3];
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ u8 pad10[0x74 - 0x10];
    /* 0x74 */ u8 unk74;
    /* 0x75 */ u8 pad75[3];
} BeamInit;

typedef struct {
    /* 0x00 */ u8 pad0;
    /* 0x01 */ u8 unk1;
    /* 0x02 */ u8 pad2[0xA];
    /* 0x0C */ u8 unkC;
} SpawnedObj;

struct260 *func_150F6DE4(struct127 *arg0) {
    BeamInit spB8;
    struct260 *obj;
    s32 i;
    BeamInit *dst;
    EmitDesc sp3C;

    spB8.unk0 = arg0;
    spB8.unk4 = ((ActorUniqueIdFields *)arg0)->field_0x3B;
    for (i = 0; i < 2; i = (u8)(i + 1)) {
        ((s32 *)&spB8)[i + 2] = 0;
    }
    spB8.unk74 = 0;
    obj = func_15149130(0x12C, -1, 0x43, -1, 0, 0x37, (struct37 *)0x78, 0xFF, 1);
    if (obj != NULL) {
        dst = (BeamInit *)((u8 *)obj + 0x28);
        memcpy(dst, &spB8, 0x78);
        sp3C.unk8 = 0x4417;
        sp3C.unk0 = 0x200004;
        sp3C.unk4 = 0;
        sp3C.unkA = 0x12C;
        sp3C.unkC = 0;
        sp3C.unk10 = 0;
        sp3C.unk14 = 0xFF;
        sp3C.unk15 = 0xFF;
        sp3C.unk16 = 0xFF;
        sp3C.unk17 = 0xFF;
        sp3C.unk1C = 0xFF;
        sp3C.unk28 = sp3C.unk2C = D_800A1BB0;
        sp3C.unk30 = *(struct17 *)&D_800A5480;
        sp3C.unk3C = *(struct17 *)&D_800A5480;
        sp3C.unk48 = *(struct17 *)&D_800A5480;
        sp3C.unk1E = 1;
        sp3C.unk20 = 0xFF;
        sp3C.unk22 = 1;
        sp3C.unk58 = 0x64C000;
        sp3C.unk60 = 8;
        sp3C.unk61 = 6;
        sp3C.unk62 = -1;
        sp3C.unk63 = -1;
        sp3C.unk64 = 3;
        sp3C.unk65 = 0;
        sp3C.unk5C = 0;
        sp3C.unk66 = 0xFF;
        sp3C.unk68 = 0xA;
        sp3C.unk1D = 0x64;
        sp3C.unk18 = 0;
        sp3C.unk19 = 0;
        sp3C.unk1A = 0xFF;
        sp3C.unk1B = 0xFF;
        sp3C.unk54 = 0.0f;
        sp3C.unk24 = 1.0f;
        sp3C.unk6C = 20.0f;
        dst->unk8 = (s32)func_15130280(&sp3C, 1, 0, 0, ((SpawnedObj *)obj)->unkC, ((SpawnedObj *)obj)->unk1);
        sp3C.unk18 = 0xFF;
        sp3C.unk19 = 0;
        sp3C.unk1A = 0;
        sp3C.unk1B = 0xFF;
        dst->unkC = (s32)func_15130280(&sp3C, 1, 0, 0, ((SpawnedObj *)obj)->unkC, ((SpawnedObj *)obj)->unk1);
    }
    return obj;
}
