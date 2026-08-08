#include <ultra64.h>

#include "functions.h"
#include "variables.h"

void func_151D9014(void *a0, void *a1, s32 a2, f32 a3, s32 sp10, s32 sp14,
                   f32 sp18, s32 sp1C, f32 sp20, f32 sp24, s32 sp28, s32 sp2C,
                   s32 sp30, s32 sp34, s32 sp38, s32 sp3C);
void func_151B9BF0(s32 arg0, s32 arg1, s16 arg2, s16 arg3, s32 arg4, s32 arg5,
                   s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 arg10, s32 arg11,
                   s32 arg12, s32 arg13, s32 arg14, s32 arg15);
void func_151EF040(s32 arg0, s32 *arg1);
void func_15171200(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5,
                   f32 arg6, f32 arg7, f32 arg8, s32 arg9, s32 arg10, f32 arg11,
                   s32 arg12, s32 arg13);
void func_151709B4(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4, s32 arg5,
                   s32 arg6);
void func_1516D99C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5,
                   s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 arg10, s32 arg11,
                   s32 arg12, s32 arg13, s32 arg14, s32 arg15, s32 arg16,
                   s32 arg17, s32 arg18, s32 arg19, s32 arg20, s32 arg21,
                   s32 arg22, s32 arg23, s32 arg24, s32 arg25, s32 arg26,
                   s32 arg27, s32 arg28, s32 arg29, s32 arg30, s32 arg31,
                   s32 arg32, s32 arg33, s32 arg34, s32 arg35, s32 arg36,
                   s32 arg37, s32 arg38, s32 arg39, s32 arg40, s32 arg41,
                   s32 arg42, s32 arg43, s32 arg44, s32 arg45, s32 arg46,
                   s32 arg47, s32 arg48);
struct225 *func_151602C0(Header *header, Header2 *header2, s32 arg2, s32 arg3,
                         s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 offset,
                         s32 arg9, s32 argA);
extern f32 D_800A0338;
extern s32 func_10004074[];

typedef struct {
    u8 pad0[0x14];
    f32 unk14;
    f32 unk18;
    f32 unk1C;
} Struct150C3D5CArg;

typedef struct {
    Header2 header2;
    Header header;
    u8 pad12[0xA];
    s32 check;
} Struct150C3D5CLocals;

#pragma GLOBAL_ASM("asm/nonmatchings/game_EF410/func_150C1F60.s")
extern f32 D_800A0258;
extern f32 D_800A025C;
extern f32 D_800A0260;
extern f32 D_800A0264;
void func_15151A38(void *arg0, u8 arg1, s32 arg2);

typedef struct {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ s16 unk24;
    /* 0x26 */ s16 unk26;
    /* 0x28 */ s16 unk28;
    /* 0x2A */ s16 unk2A;
    /* 0x2C */ s16 unk2C;
    /* 0x2E */ s16 unk2E;
    /* 0x30 */ s16 unk30;
    /* 0x32 */ s16 unk32;
    /* 0x34 */ s16 unk34;
    /* 0x36 */ s16 unk36;
    /* 0x38 */ u8 unk38;
    /* 0x39 */ u8 unk39;
    /* 0x3A */ u8 unk3A;
    /* 0x3B */ u8 pad3B;
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ s32 unk40;
    /* 0x44 */ s32 unk44;
    /* 0x48 */ s32 unk48;
    /* 0x4C */ s32 unk4C;
    /* 0x50 */ s32 unk50;
    /* 0x54 */ u8 unk54;
    /* 0x55 */ u8 unk55;
    /* 0x56 */ u8 unk56;
    /* 0x57 */ u8 pad57;
    /* 0x58 */ s32 unk58;
    /* 0x5C */ s32 unk5C;
    /* 0x60 */ s32 unk60;
    /* 0x64 */ s32 unk64;
    /* 0x68 */ s32 unk68;
    /* 0x6C */ s32 unk6C;
    /* 0x70 */ s32 unk70;
    /* 0x74 */ s32 unk74;
    /* 0x78 */ s32 unk78;
    /* 0x7C */ u8 unk7C;
    /* 0x7D */ u8 unk7D;
    /* 0x7E */ u8 pad7E[2];
    /* 0x80 */ s16 unk80;
    /* 0x82 */ s16 unk82;
    /* 0x84 */ s32 unk84;
} Struct150C2290Arg;

#pragma GLOBAL_ASM("asm/nonmatchings/game_EF410/func_150C2290.s")
/* Best 590. Only diff: target homes a0 + does `andi a1,a0,0xff` early;
   IDO keeps arg0 in a3 and masks late (register-alloc heuristic).
   PERMUTER CANDIDATE. permuter NO ZERO: `void func_150C2290(u8 arg0)` (u8, not s32)
   drops the score to 60 — remaining diff is a single-instruction const-hoist of the
   1.0f (unk18) load that IDO schedules one slot later; not C-controllable. Reconstruction:
void func_150C2290(u8 arg0) {
    Struct150C2290Arg sp18;

    sp18.unk0 = D_800A0258;
    sp18.unk4 = 40.0f;
    sp18.unk8 = D_800A025C;
    sp18.unk1C = 100.0f;
    sp18.unk20 = 57.5f;
    sp18.unkC = D_800A0260;
    sp18.unk10 = 39.0f;
    sp18.unk24 = 2;
    sp18.unk26 = 3;
    sp18.unk28 = -0x29;
    sp18.unk2C = -0x16;
    sp18.unk2A = 0x15;
    sp18.unk2E = 0x16;
    sp18.unk30 = 7;
    sp18.unk32 = 0;
    sp18.unk34 = 0x30;
    sp18.unk36 = 0x15;
    sp18.unk38 = 0xB;
    sp18.unk39 = 1;
    sp18.unk3A = 0x28;
    sp18.unk3C = 1;
    sp18.unk40 = 4;
    sp18.unk44 = 0;
    sp18.unk48 = 0;
    sp18.unk4C = 0;
    sp18.unk50 = 0;
    sp18.unk54 = 0xFF;
    sp18.unk55 = 0xFF;
    sp18.unk56 = 0;
    sp18.unk58 = 3;
    sp18.unk5C = 0xFF;
    sp18.unk60 = 0;
    sp18.unk64 = 0x220005;
    sp18.unk68 = 0x1D0600;
    sp18.unk6C = 1;
    sp18.unk70 = 0x3B;
    sp18.unk74 = 0x80;
    sp18.unk78 = 0x20;
    sp18.unk7C = 0;
    sp18.unk7D = 7;
    sp18.unk80 = 0xC;
    sp18.unk82 = 0x15;
    sp18.unk14 = D_800A0264;
    sp18.unk18 = 1.0f;
    func_15151A38(&sp18, (u8)arg0, 1);
}
*/

void func_1514C470(f32 arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5,
                   f32 arg6, u8 arg7, s32 arg8, f32 arg9, s32 arg10, u8 arg11);

#pragma GLOBAL_ASM("asm/nonmatchings/game_EF410/func_150C2424.s")
/* Blocked by the C-rodata linker gap, not by the C.  D_800A0268 / D_800A026C
   are not real globals: they are IDO-generated .rodata float literals
   (asm/data/244CD0.rodata.s -> 8500.0f and 8843.0f).  Written the way the
   original author wrote them, this matches byte-for-byte (verified SCORE 0):

void func_150C2424(u8 arg0) {
    func_1514C470(8500.0f, -490.0f, -328.0f, 8500.0f, -490.0f, 328.0f,
                  (func_150ADA68() * 8.0f) + 8.0f, 1, 0, 0.0f, 0, arg0);
    func_1514C470(8843.0f, -560.0f, -580.0f, 8117.0f, -560.0f, -580.0f,
                  (func_150ADA68() * 3.0f) + 4.0f, 3, 0, 0.0f, 0, arg0);
}

   ...but that makes IDO emit a .rodata section for this TU, and conker.ld has
   no `build/src/game_EF410.c.o(.rodata);` entry (only .text at line 507), so
   the section lands in /DISCARD/ and the %hi/%lo relocs resolve to 0 -- a
   silently wrong ROM.  Unlock = add that one line to conker.ld beside
   build/asm/data/244CD0.rodata.s.o(.rodata) and drop the two externs.

   Referencing the literals as `extern f32 D_800A0268` instead (the usual
   workaround) costs one scheduler tie and stalls at 130: IDO orders the
   lui/mtc1 of -490.0f before the lui/lwc1 of the global, where the target has
   them the other way round.  Tried and still 130: hoisting the rng call and/or
   the loaded value into named locals, `extern const f32`, `extern f32 x[]` +
   `x[0]`, int and double spellings of the coordinate literals. */
s32 func_150C251C(void *arg0) {
    void *temp_v0 = *(void **)((s32)arg0 + 0x98);
    s32 temp_v1 = *(s16 *)((s32)arg0 + 0x1C) << 3;
    s32 temp_t7;

    if (temp_v1 >= 0x100) {
        temp_v1 = 0xFF;
    }
    temp_t7 = temp_v1 & 0xFF;
    *(u8 *)((s32)temp_v0 + 0x1B) = temp_v1;
    if (temp_t7 < 0) {
        return 0;
    }
    return 1;
}
extern f32 D_800A0270;

#pragma GLOBAL_ASM("asm/nonmatchings/game_EF410/func_150C2558.s")
/* Best 1307. FP block matches; blocker is IDO constant-CSE/reg-alloc for the
   value-1 fields (unk24/unk39/unk6C share one register allocated late) plus
   the integer field ordering. PERMUTER CANDIDATE. Reconstruction:
s32 func_150C2558(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5,
                  s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 arg10, s32 arg11,
                  s32 arg12, s32 arg13, u8 arg14) {
    Struct150C2290Arg sp18;

    sp18.unk0 = arg2;
    sp18.unk4 = arg3;
    sp18.unk8 = (arg4 + 15.0f) - func_150ADA68() * 30.0f;
    sp18.unk28 = (s32)(sp18.unk8 * D_800A0270) - 0x40;
    sp18.unk1C = 200.0f;
    sp18.unk20 = 150.0f;
    sp18.unkC = 22.0f;
    sp18.unk10 = 44.0f;
    sp18.unk14 = 0.0f;
    sp18.unk18 = 0.0f;
    sp18.unk24 = 1;
    sp18.unk26 = 0;
    sp18.unk2A = 9;
    sp18.unk2C = 0;
    sp18.unk2E = 0;
    sp18.unk30 = 3;
    sp18.unk32 = 3;
    sp18.unk34 = 0x28;
    sp18.unk36 = 0x15;
    sp18.unk38 = 0xB;
    sp18.unk39 = 1;
    sp18.unk3A = 0x28;
    sp18.unk3C = 1;
    sp18.unk40 = 4;
    sp18.unk44 = 0;
    sp18.unk48 = 0;
    sp18.unk4C = 0;
    sp18.unk50 = 0;
    sp18.unk54 = 0xFF;
    sp18.unk55 = 0xFF;
    sp18.unk56 = 0;
    sp18.unk58 = 3;
    sp18.unk5C = 0xFF;
    sp18.unk60 = 0;
    sp18.unk64 = 0x220005;
    sp18.unk68 = 0x1D0600;
    sp18.unk6C = 1;
    sp18.unk70 = 0x3B;
    sp18.unk74 = 0x80;
    sp18.unk78 = 0x20;
    sp18.unk7C = 0;
    sp18.unk7D = 7;
    sp18.unk80 = 0xC;
    sp18.unk82 = 0x15;
    func_15151A38(&sp18, arg14, 1);
    return 1;
}
*/
extern f32 D_800A0274;
extern f32 D_800A0278;
extern f32 D_800A027C;

typedef struct {
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ s16 unk16;
    /* 0x18 */ f32 unk18[3];
    /* 0x24 */ s16 unk24;
    /* 0x26 */ s16 unk26;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ s16 unk30;
    /* 0x32 */ s16 unk32;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ u8 unk3C;
    /* 0x3D */ s8 unk3D;
    /* 0x3E */ u8 unk3E[2];
    /* 0x40 */ f32 unk40;
    /* 0x44 */ f32 unk44;
    /* 0x48 */ s8 unk48;
    /* 0x49 */ u8 unk49;
    /* 0x4A */ u8 unk4A[2];
    /* 0x4C */ f32 unk4C;
    /* 0x50 */ s8 unk50;
    /* 0x51 */ u8 pad51[3];
    /* 0x54 */ f32 unk54;
} Struct150C2700;

void func_15150178(Struct150C2700 *arg0, f32 *arg1, s32 arg2, u8 arg3, s32 arg4);

s32 func_150C2700(s32 a0, s32 a1, f32 a2, f32 a3, f32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 argA, s32 argB, s32 argC, s32 argD, u8 argE) {
    Struct150C2700 sp20;

    sp20.unk18[0] = a2;
    sp20.unk18[1] = a3;
    sp20.unk24 = 6;
    sp20.unk26 = 5;
    sp20.unk10 = 0x6B;
    sp20.unk12 = 0x46;
    sp20.unk14 = -0x1F;
    sp20.unk16 = 0x2E;
    sp20.unk30 = 0x64;
    sp20.unk32 = 0;
    sp20.unk3C = 0x9B;
    sp20.unk3D = 0x64;
    sp20.unk44 = 0.0f;
    sp20.unk48 = 1;
    sp20.unk49 = 6;
    sp20.unk4C = 0.0f;
    sp20.unk50 = 1;
    sp20.unk54 = 0.0f;
    sp20.unk18[2] = arg4;
    sp20.unk28 = 30.0f;
    sp20.unk2C = 35.0f;
    sp20.unk34 = D_800A0274;
    sp20.unk38 = D_800A0278;
    sp20.unk40 = D_800A027C;
    func_15150178(&sp20, sp20.unk18, 0, argE, 1);
    return 1;
}

extern f32 D_800A0280;
extern f32 D_800A0284;
extern void func_15134908(void *, s32, u8, s32);

typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ s32 unk08;
    /* 0x0C */ f32 unk0C;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ u8 unk16;
    /* 0x17 */ u8 unk17;
    /* 0x18 */ u8 unk18;
    /* 0x19 */ s8 unk19;
} Struct150C2804;

void func_150C2804(s32 arg0, s32 arg1, s32 arg2, s16 arg3, s32 arg4, s32 arg5) {
    Struct150C2804 sp1C;

    sp1C.unk0C = D_800A0280;
    sp1C.unk00 = arg0;
    sp1C.unk04 = arg1;
    sp1C.unk08 = arg2;
    sp1C.unk10 = D_800A0284;
    sp1C.unk14 = arg3;
    sp1C.unk16 = 5;
    sp1C.unk17 = 6;
    sp1C.unk18 = 3;
    sp1C.unk19 = -1;
    func_15134908(&sp1C, 0, arg4, arg5);
}
void func_150C2898(f32 a0, f32 a1, f32 a2, f32 a3, f32 a4, f32 a5, u8 *a6) {
    f32 sp6C[3];
    f32 sp60[3];
    f32 r;
    struct { f32 c; s32 a; u32 b; s32 pad; } sp4C;

    sp6C[0] = a0;
    sp6C[1] = a1;
    sp6C[2] = a2;
    r = (func_150ADA68() * 112.0f + 247.0f) * D_800A0288;
    sp60[0] = -a3 * r;
    sp60[1] = -a4 * r;
    sp60[2] = -a5 * r;
    sp4C.c = func_150ADA68();
    sp4C.a = func_150ADA20();
    sp4C.b = func_150ADA20();
    func_151D9014(sp6C, sp60, 6, sp4C.c * D_800A028C + D_800A0290,
                    (sp4C.a & 0xF) + 25, (sp4C.b % 101) + 155,
                    func_150ADA68() * 119.0f + 129.0f, 0, 1.0f, 1.0f, 1, 0, 1, 0,
                    a6[0xC], a6[1]);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_EF410/func_150C29F0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_EF410/func_150C2C00.s")
s32 func_150C2FCC(f32 *arg0) {
    arg0[11] -= arg0[11] * arg0[84];
    arg0[12] -= arg0[12] * arg0[84];
    arg0[14] += (arg0[20] * D_800BE9A4) + (((0.5f * arg0[19]) * D_800BE9A4) * D_800BE9A4);
    arg0[20] += arg0[19] * D_800BE9A4;
    if ((arg0[11] < 10.0f) || (arg0[12] < 10.0f)) {
        return 0;
    }
    return 1;
}
extern struct17 *func_15144B34(s32);

s32 func_150C308C(void *arg0) {
    u8 ret;
    struct17 *temp_v0;
    f32 sum;

    ret = 0;
    if (*(s16 *)((s32)arg0 + 0x1C) >= 6) {
        temp_v0 = func_15144B34(D_80082FA4);
        sum = (temp_v0->unk0 * temp_v0->unk0) + (temp_v0->unk8 * temp_v0->unk8);
        if (sum < D_800A0310) {
            ret = 1;
        } else if (D_800A0314 < func_15144C8C(func_150484A0(temp_v0->unk0, temp_v0->unk8), *(f32 *)((s32)arg0 + 0x160))) {
            ret = 1;
        }
    }
    if (ret != 0) {
        *(s16 *)((s32)arg0 + 0x1C) = 5;
    }
    return 1;
}

Gfx *func_150C3160(Gfx *arg0, void *arg1) {
    s32 temp_v0;
    s32 temp_v1;
    s32 temp_a0;
    f32 temp_f0;

    temp_v0 = *(s32 *)((s32)arg1 + 0x2E8);
    temp_f0 = (temp_v0 != 0) ? ((f32)*(s32 *)((s32)arg1 + 0x2E4) / (f32)temp_v0) : 1.0f;
    temp_f0 = 1.0f - temp_f0;
    temp_v1 = (s32)((500.0f * temp_f0) + 2.0f);
    temp_a0 = 2 - *(s32 *)((s32)arg1 + 0x2EC);
    *(s32 *)((s32)arg1 + 0x2EC) = temp_v1 / 3;
    while (temp_a0 < 0) {
        temp_a0 += 0x40;
    }
    gDPSetTileSize(arg0++, 4, temp_v1, temp_a0, 0x1FE, 0x03E);
    return arg0;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_EF410/func_150C3230.s")
/* Best 250 of 209 instructions. Structure, frame (0x60), stack-slot layout,
   branch shape and every instruction ADDRESS line up end-to-end; only 11 words
   differ. Two of them are the reloc-spelling artifact (the extracted .s names the
   interior symbol D_800CC028 == D_800CC2D0 - 0x2A8, i.e. &D_800CC2D0[i-1].unk84,
   which natural C spells as base+offset -- same linked bytes). The rest are a
   3-word delay-slot/register schedule split in the 0x1F9/0x1FB selector plus a
   uniform +1 t-register rotation (t3/t4/t5 -> t4/t5/t6) in the tail health block
   -- the allocator skips one mid-pool register and no source lever responds
   (tried: if-chain, nested ternary, switch, if+ternary hybrid, default-then-
   override, a named local for the lhu value, statement reordering, declaration
   reordering, bare truthiness). PERMUTER CANDIDATE. Reconstruction:

typedef struct {
    struct127 *unk0;
    f32 unk4[3];
    s32 unk10;
    s32 unk14;
} Struct150C3230;

void func_15059C84(struct127 *arg0);
void func_1505A770(struct127 *arg0);
void func_1507C324(struct127 *arg0, struct127 *arg1);
void func_1506AC8C(struct127 *arg0, s32 arg1, void *arg2);

void func_150C3230(struct127 *arg0) {
    s32 index;
    s32 type;
    struct127 *target;
    Struct150C3230 sp3C;

    arg0->unkF8 |= 0x4000000;
    if ((arg0->unk222 != 0) && (arg0->unk65 == 0)) {
        arg0->old_x_position = D_800CC2D0[arg0->unk124 - 1].x_position;
        arg0->old_y_position = D_800CC2D0[arg0->unk124 - 1].y_position;
        arg0->old_z_position = D_800CC2D0[arg0->unk124 - 1].z_position;
        arg0->unk222 = 0;
    }

    func_15059C84(arg0);
    func_1505A770(arg0);
    func_15058898(arg0, arg0->old_y_position);
    func_1505B5F8(arg0, arg0->unk180);

    if (arg0->unk28 == 0.0f) {
        arg0->xz_velocity *= 0.5f;
    }

    index = arg0->unk65;
    if (index != 0) {
        arg0->unk222 = index;
        type = (D_800CC2D0[index - 1].unk84.uh == 0x1F9)
                   ? 2
                   : ((D_800CC2D0[index - 1].unk84.uh == 0x1FB) ? 3 : 1);
    } else {
        type = 0;
    }

    func_1505E650(arg0, type, 0.0f, 0.0f, 0.0f, 0.0f, 0);

    if (arg0->unk65 != 0) {
        func_1507C324(arg0, &D_800CC2D0[arg0->unk65 - 1]);
    }

    if (arg0->unk2E4 != 0) {
        if (arg0->unk65 != 0) {
            target = &D_800CC2D0[arg0->unk65 - 1];
            if (target->interaction_state == 5) {
                arg0->unk65 = 0;
                arg0->unk2E4 = 0;
            }
        } else {
            target = NULL;
        }

        if ((D_800BE616 == 0) && (D_800C35EA == 0) && (arg0->unk65 == 0)) {
            arg0->unk2E4 = 0;
        }

        if (D_800BE9E4 < arg0->unk2E4) {
            arg0->unk2E4 -= D_800BE9E4;
            if (D_800BE616 != 0) {
                func_1508B20C(arg0->x_position, arg0->y_position, arg0->z_position, 900.0f);
            }
        } else {
            sp3C.unk4[0] = arg0->x_position;
            sp3C.unk4[1] = arg0->y_position;
            sp3C.unk4[2] = arg0->z_position;
            sp3C.unk0 = &D_800CC2D0[arg0->unk124 - 1];
            sp3C.unk10 = arg0->unk65;
            if (target != NULL) {
                target->stunned = 0;
                target->immune = 0;
                if (target->health != 0) {
                    target->health = 1;
                }
            }
            func_1506AC8C(arg0, (D_800BE616 != 0) ? 0xB : 0xE, &sp3C);
            func_15060F28(arg0, 1);
        }
    }
}
*/
#pragma GLOBAL_ASM("asm/nonmatchings/game_EF410/func_150C3574.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_EF410/func_150C3994.s")

s32 func_150C3D48(s32 arg0) {
    return arg0 + 0xEDCBA988;
}

void func_150C3D5C(Struct150C3D5CArg *arg0) {
    Struct150C3D5CLocals local;

    func_151B9BF0(0x2F, 1, (s16)(s32)arg0->unk14, (s16)(s32)arg0->unk18,
                  (s32)arg0->unk1C, 0x578, 0x500, 0x320, 0x4B0, 0x200, 0x200,
                  0x1E, 1, 0, 0xFF, 0);

    ((void (*)(s32, s32 *))func_151EF040)(func_150C3D48(local.check = 0xC23459B8), &local.check);
    if (local.check != 0x0330C820) {
        func_10004074[0] = 0x03E00008;
        func_10004074[1] = 0;
    }

    func_15171200(3, 0xCB, arg0->unk14, arg0->unk18, arg0->unk1C, 10.0f, 1.0f,
                  2.0f, 60.0f, 3, 0x3C, D_800A0338, 0xFF, 0);
    func_151709B4((s32)arg0->unk14, (s32)(arg0->unk18 + 20.0f),
                  (s32)arg0->unk1C, 0xA, 2000.0f, 0xFF, 0);
    func_1516D99C((s16)(s32)arg0->unk14, (s16)(s32)arg0->unk18,
                  (s16)(s32)arg0->unk1C, 0xD, 0, 0, 0, 0, 0, 0, 0, 0, 4, 0, 0,
                  0, 0xFF, 0, 0, 0, 0x14, 0x14, 2, 0, 0, 0, 0, 0x51, 0x51,
                  0x51, 0x51, 0xA, 1, 0, 0xFF, 0xA, 0x578, 0x190, 1, 1, 0, 1,
                  0, 0, 0, 0, 0, 0xFF, 0);

    local.header.unk0 = 3;
    local.header.unk1 = -1;
    local.header.unk2 = (func_150ADA20() % 11U) + 0xA;
    local.header.unk4 = 0;
    local.header2.unk0 = (s32)arg0->unk14;
    local.header2.unk4 = (s32)arg0->unk18;
    local.header2.unk8 = (s32)arg0->unk1C;
    func_151602C0(&local.header, &local.header2, (func_150ADA20() % 52U) + 0x28,
                  0xFF, 0xFF, 0x5A, 0xFF, 0, 0, 0xFF, 1);
}
