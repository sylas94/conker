#include <ultra64.h>
#include "functions.h"
#include "variables.h"

typedef struct {
    u8 pad0[0x8];
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    u8 pad20[0x30];
} Struct15189900Arg;

typedef struct {
    u8 pad0[0x10];
    Struct15189900Arg unk10;
    s16 unk60;
    u8 pad62[0x2];
    f32 unk64;
    f32 unk68;
    s32 unk6C;
    u8 unk70;
} Struct15189900Obj;

extern Struct15189900Obj *func_15167A68(s32, s32, s32, s32, s32, s32);
extern void func_1510F800(s32);


void func_15189900(Struct15189900Arg *arg0, s32 arg1) {
    Struct15189900Obj *temp_v0;
    s32 var_v0;

    temp_v0 = func_15167A68(0x1A, 1, 0x78, 1, 0xFF, 1);
    if (temp_v0 != 0) {
        memcpy(&temp_v0->unk10, arg0, 0x50);
        func_1510F800(0);
        temp_v0->unk6C = func_1510FD20((s32)(temp_v0->unk10.unk8 + (temp_v0->unk10.unk14 * 0.5f)), (s32)(temp_v0->unk10.unk10 + (temp_v0->unk10.unk1C * 0.5f)));
        if ((u8)arg1 != 0) {
            var_v0 = 1;
        } else {
            var_v0 = 0;
        }
        temp_v0->unk70 = var_v0;
        temp_v0->unk60 = 0;
        temp_v0->unk64 = 0.0f;
        if (temp_v0->unk10.unk18 < 0.0f) {
            temp_v0->unk68 = temp_v0->unk10.unkC + temp_v0->unk10.unk18;
        } else {
            temp_v0->unk68 = temp_v0->unk10.unkC;
        }
    }
}

// NON-MATCHING, best score 2010 (from ~2595 on the first honest spelling). This is a
// particle-emitter tick, a near-clone of the matched func_15151A38/func_15152F70 pair in
// game_17CAF0.c and of func_15148F1C in game_175250.c -- those three carry the struct
// models for the func_15147DA0 call (pos 0x18 / spawn 0x20 / style 0x20).
//
// WHAT IS ALREADY EXACT: frame size 0x148, every stack offset (style 0xC8, lowY 0xE8,
// spawn 0xEC, pos 0x10C), every FP register, every field offset, both `break 7` guards,
// the four func_151423D8 sin/cos calls, the whole func_15147DA0 argument block and the
// memcpy tail. The residual is (a) three delay slots that IDO fills for us and leaves as
// `nop` in golden, and (b) a uniform +1 integer temp-register rotation that starts in the
// camera-proximity search loop.
//
// THE ROTATION: golden spends exactly THREE t-registers in the search loop (t0=0x9A0,
// t1=&D_800BE630, t2=mflo) because it coalesces three pairs of live ranges --
// v0 = D_80082FA0 then &struct108, v1 = the obj->unk60 reload then the walk pointer, and
// a0 = the loop index `i` then the D_800BE630[] byte. We only coalesce two, so the byte
// lands in t2 and mflo in t3: four t-registers, and every later temp is +1 mod 9 (t1..t9)
// for the rest of the function. Nothing about the loop's SPELLING has moved this yet.
//
// THE DELAY SLOTS: golden leaves `nop` after the jal that follows `pos.unk8 = ...`,
// `spawn.unk0 = ...` and `spawn.unkC = ...`, but DOES fill the one after
// `spawn.unk10 = ...` with `swc1 f8,0xFC(sp)` -- and those last two statements are
// structurally identical (`(func_150ADA68() * obj->unkX) + obj->unkY` into the same
// struct). So it is a scheduler preference, not a spelling, unless it is downstream of
// the rotation. Those three nops are the whole 16-byte .text shortfall.
//
// SOLVED ALONG THE WAY (keep these, they were each worth several rows):
//  * `ang1` needs `+ -obj->unk12`, NOT `- obj->unk12`: IDO rewrites `a - (b - c)` into
//    `(a-b) + c` (addu) but rewrites `a - (b + (-c))` into `(a-b) - (-c)`, which is
//    golden's negu/subu/subu triple. Measured, not guessed.
//  * the dead `addiu v0,v0,0x2F8` is the -g3 materialisation of the named `cam` pointer;
//    it appears only when `cam` is the ONLY pointer local. Adding a second pointer local
//    (`ent = &D_800DBFF0[idx]`) makes IDO drop it (-1 instruction).
//  * locals total exactly 0xC8 bytes at 0x80..0x148 with ~0x28 of compiler temps below
//    them; 36 bytes must sit above `pos` and 32 below `style`, which is what pins the
//    interleaved declaration order below (same trick the 17CAF0 siblings use).
//
// EXACTLY WHAT IS PARKED BELOW: the last spelling edited in, which is the measured-2010
// model with `struct108 *ent` swapped for a `u8 idx` local (byte-neutral for the frame:
// idx@0x12B, ang1@0x128, ang2@0x126 still lands pos at 0x10C). That swap was queued but
// the build never landed before the tree had to be made safe again, so treat the parked
// spelling as UNMEASURED. The measured-2010 spelling is identical except:
//     struct108 *ent;                              -- in place of `u8 idx`
//     ent = &D_800DBFF0[D_800BE630[i]];
//     cam = (struct17 *)&ent->unk2F8;
// and the measured-2045 spelling had `s32 handle` first (with `handle = obj->unk6C;`
// hoisted out of the guard) and no `ent`/`idx` at all.
//
// Detailed measurements in tools/nearmiss/func_15189A00.c.
//
// typedef struct {
//     u8  pad0[0x1];
//     u8  unk1;
//     u8  pad2[0xA];
//     u8  unkC;
//     u8  padD[0x3];
//     s16 unk10;
//     s16 unk12;
//     s16 unk14;
//     s16 unk16;
//     f32 unk18;
//     f32 unk1C;
//     f32 unk20;
//     f32 unk24;
//     f32 unk28;
//     f32 unk2C;
//     f32 unk30;
//     f32 unk34;
//     f32 unk38;
//     f32 unk3C;
//     f32 unk40;
//     f32 unk44;
//     s16 unk48;
//     s16 unk4A;
//     f32 unk4C;
//     f32 unk50;
//     s16 unk54;
//     s16 unk56;
//     s32 unk58;
//     s32 unk5C;
//     s16 unk60;
//     u8  pad62[0x2];
//     f32 unk64;
//     f32 unk68;
//     s32 unk6C;
//     u8  unk70;
// } Struct15189A00Obj;
//
// typedef struct {
//     f32 unk0;
//     f32 unk4;
//     f32 unk8;
//     s16 unkC;
//     s16 unkE;
//     s32 unk10;
//     u8  pad14;
//     u8  unk15;
// } Struct15189A00Pos;
//
// typedef struct {
//     f32 unk0;
//     f32 unk4;
//     f32 unk8;
//     f32 unkC;
//     f32 unk10;
//     f32 unk14;
//     u8  unk18;
//     u8  unk19;
//     u8  unk1A;
//     u8  unk1B;
//     s16 unk1C;
//     s16 unk1E;
// } Struct15189A00Spawn;
//
// typedef struct {
//     s32 unk0;
//     s32 unk4;
//     s32 unk8;
//     s32 unkC;
//     s32 unk10;
//     s32 unk14;
//     s32 unk18;
//     u8  unk1C;
//     u8  unk1D;
// } Struct15189A00Style;
//
// typedef struct {
//     u8  pad0[0x98];
//     u8  *unk98;
// } Struct15189A00Part;
//
// extern u8 D_800BE630[];
// extern f32 D_800A73A0;
// extern f32 D_800A73A4;
// extern s32 func_151464B8(s32);
// extern Struct15189A00Part *func_15147DA0(void *, void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, void *, s32, u8, s32);
//
// void func_15189A00(Struct15189A00Obj *obj) {
//     s32 i;
//     s32 found;
//     struct17 *cam;
//     f32 dx;
//     f32 dy;
//     f32 dz;
//     f32 distSq;
//     u8  idx;
//     s16 ang1;
//     s16 ang2;
//     Struct15189A00Pos pos;
//     Struct15189A00Spawn spawn;
//     f32 lowY;
//     Struct15189A00Style style;
//     f32 rnd;
//     f32 speed;
//     f32 sin1;
//     f32 cos1;
//     f32 sin2;
//     f32 cos2;
//     f32 horiz;
//     Struct15189A00Part *part;
//
//     if ((obj->unk6C != 0) && (func_151464B8(obj->unk6C) != 0)) {
//         return;
//     }
//     obj->unk60 -= D_800BE9E4;
//     if (obj->unk60 < 0) {
//         obj->unk60 += 0x32;
//         found = 0;
//         for (i = 0; (i <= D_80082FA0) && (found == 0); i++) {
//             idx = D_800BE630[i];
//             cam = (struct17 *)&D_800DBFF0[idx].unk2F8;
//             dx = cam->unk0 - obj->unk18;
//             dy = cam->unk4 - obj->unk1C;
//             dz = cam->unk8 - obj->unk20;
//             distSq = ((dx * dx) + (dy * dy)) + (dz * dz);
//             if (distSq < D_800A73A0) {
//                 found = 1;
//             }
//         }
//         if (found == 0) {
//             return;
//         }
//     }
//     obj->unk64 += (obj->unk38 + (func_150ADA68() * obj->unk3C)) * D_800BE9A4;
//     if (obj->unk64 > 1.0f) {
//         pos.unk10 = 1;
//         pos.unkE = 5;
//         spawn.unk1C = 0x10;
//         spawn.unk1E = 0xF;
//         spawn.unk18 = 0x48;
//         spawn.unk19 = 3;
//         spawn.unk1A = 0xFF;
//         style.unk0 = 0;
//         style.unk4 = 1;
//         style.unk8 = 0x160600;
//         style.unkC = 3;
//         style.unk10 = 0x22;
//         style.unk14 = 0x80;
//         style.unk18 = 0x20;
//         style.unk1C = 0;
//         style.unk1D = 7;
//         lowY = obj->unk68;
//         spawn.unk14 = D_800A73A4;
//         do {
//             pos.unk15 = (func_150ADA20() % (u32)(obj->unk5C + 1)) + obj->unk58;
//             rnd = func_150ADA68();
//             pos.unk0 = obj->unk18 + (rnd * obj->unk24);
//             pos.unk4 = obj->unk1C + (rnd * obj->unk28);
//             pos.unk8 = obj->unk20 + (rnd * obj->unk2C);
//             spawn.unk0 = (func_150ADA68() * obj->unk44) + obj->unk40;
//             ang1 = obj->unk10 - ((func_150ADA20() % (u32)((obj->unk12 * 2) + 1)) + -obj->unk12);
//             ang2 = (func_150ADA20() % (u32)(obj->unk16 + 1)) + obj->unk14;
//             speed = (func_150ADA68() * obj->unk34) + obj->unk30;
//             sin1 = func_151423D8((u8)ang1);
//             cos1 = func_151423D8((u8)(ang1 - 0x40));
//             sin2 = func_151423D8((u8)ang2);
//             cos2 = func_151423D8((u8)(ang2 - 0x40));
//             horiz = speed * sin2;
//             spawn.unk4 = horiz * cos1;
//             spawn.unk8 = -speed * cos2;
//             spawn.unkC = horiz * sin1;
//             spawn.unk10 = (func_150ADA68() * obj->unk50) + obj->unk4C;
//             spawn.unk1B = (func_150ADA20() % (u32)(obj->unk4A + 1)) + obj->unk48;
//             pos.unkC = (func_150ADA20() % (u32)(obj->unk56 + 1)) + obj->unk54;
//             part = func_15147DA0(&pos, &spawn, 8, 1, (obj->unk70 & 1) ? 0xA : 0, 0, 0, 0, 0, 0, 0,
//                                  &style, 0, obj->unkC, obj->unk1);
//             if (part != 0) {
//                 memcpy(part->unk98 + 0x48, &lowY, 4);
//             }
//             obj->unk64 -= 1.0f;
//         } while (obj->unk64 > 1.0f);
//     }
// }

#pragma GLOBAL_ASM("asm/nonmatchings/game_1B6DB0/func_15189A00.s")

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
} Struct15189EBC_elem;

typedef struct {
    u8 unk0[0x1];
    u8 unk1;
    u8 pad2[0xA];
    u8 unkC;
    u8 padD[0x20];
    s8 unk2D;
    u8 pad2E[0x66];
    Struct15189EBC_elem *unk94;
    u8 *unk98;
} Struct15189EBC;

typedef struct {
    f32 unk0;
    u8 pad4[0x4];
    u8 unk8;
} Struct15189EBC_sub;

typedef struct {
    f32 unk0;
    u8 pad4[0x17];
    u8 unk1B;
    u8 pad1C[0x4];
    u8 unk20;
    u8 pad21[0x27];
    Struct15189EBC_sub unk48;
} Struct15189EBC_v1;

extern f64 D_800A73A8;
extern f32 D_800A73B0;
extern s32 func_151D8E20(void);
void func_151DBCBC(u8 arg0, f32 arg1, s16 arg2, s32 arg3, void *arg4, u8 arg5, s32 arg6);
f32 func_150ADA68(void);

s32 func_15189EBC(Struct15189EBC *arg0) {
    f64 tmp;
    Struct15189EBC_v1 *v1 = (Struct15189EBC_v1 *)arg0->unk98;
    Struct15189EBC_elem *base = arg0->unk94;
    struct17 sp34;

    if (base[arg0->unk2D].unk4 < v1->unk48.unk0) {
        tmp = func_150ADA68();
        if (tmp < D_800A73A8) {
            sp34.unk0 = base[arg0->unk2D].unk0;
            sp34.unk4 = v1->unk48.unk0;
            sp34.unk8 = base[arg0->unk2D].unk8;
            func_151DBCBC((u8)func_151D8E20(), v1->unk0 * 6.0f, v1->unk1B, 0, &sp34, arg0->unkC, arg0->unk1);
        }
        v1->unk20 = 4;
        v1->unk48.unk0 = D_800A73B0;
    }
    return 1;
}

s32 func_15189FD0(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 *p = &arg0;
    return 1;
}
