/* ===========================================================================
 * func_150FF474  --  game_12C1E0.c  --  576 bytes / 144 instructions
 * PARKED at 4660 honest (with AND without -R, window bounded to 144 words).
 *
 * VERDICT: RODATA-BLOCKED, exactly the same mechanism as func_150FFD84 -- but
 * on a DIFFERENT block (0x246B10, not 0x246BF0).
 *
 * golden hoists the VALUES of three constants out of the spawn loop into
 * callee-saved FP registers before the loop:
 *      758: lui at,%hi(D_800A2124) ; 75c: lwc1 $f26,%lo(D_800A2124)(at)
 *      760: lui at,%hi(D_800A2128) ; 764: lwc1 $f24,%lo(D_800A2128)(at)
 *      568: lui at,0x40a0          ; 570: mtc1 at,$f22          (5.0f)
 *      578: lui at,%hi(D_800A212C) ; 588: lwc1 $f20,%lo(D_800A212C)(at)
 * and therefore saves FOUR doubles: sdc1 $f26,0x50 / $f24,0x48 / $f22,0x40 /
 * $f20,0x38.  A loop-invariant LOAD can only be hoisted out of a loop that
 * contains calls (func_150ADA68, func_150ADA20, func_1513D2F0 are all in this
 * loop) if the compiler knows the memory is a compile-time constant.  Spelled
 * `extern f32` they are ordinary globals, IDO re-loads them every iteration,
 * only the 5.0f literal survives in $f20, three `sdc1` disappear and the frame
 * SHRINKS from 0xE0 to 0xD0.  None of the three is lui-able:
 *      D_800A2124 = 0x401EE979 =  2.48300004   (low16 0xE979)
 *      D_800A2128 = 0x3F7FBE78 =  0.9990000725 (low16 0xBE78)
 *      D_800A212C = 0x4131999A = 11.10000038   (low16 0x999A)
 *
 * CORRECTED-PROBE EVIDENCE (read the SHAPE, not the score):
 *   honest `extern f32`                       -> frame 0xD0, 1 sdc1, size 580
 *   lui-able stand-ins (11.0f/1.0f/2.5f)      -> frame 0xE0 EXACTLY, 3 sdc1
 *   true non-lui-able literals (the real bit  -> frame 0xE0, size 576 == GOLDEN
 *     patterns, i.e. what a migration gives)     EXACTLY, score 901
 * So with the block migrated this function reaches golden's exact instruction
 * COUNT and the residual collapses to 4660 -> 901 (71/144 words, register
 * numbering only).  It cannot close without the migration.
 *
 * ---------------------------------------------------------------------------
 * WHY THE MIGRATION IS NOT AVAILABLE (see func_150FFD84.c for the full write-up)
 * ---------------------------------------------------------------------------
 * These three words live at ROM 0x246BE4..0x246BF0, at the END of block
 * 0x246B10.  func_150FFD84's blockers live at 0x246C54..0x246C5C, inside block
 * 0x246BF0.  Between them, at 0x246BF0..0x246C30, sit five NAMED objects
 * (D_800A2130/213C/2148/2154 Vec3s and the D_800A2160 s32[4]), two of which
 * (D_800A2148, D_800A2154) are referenced from game_981E0.c and one
 * (D_800A2130) from the data table at ROM 0x23474C (D_8008FC8C).  One object
 * file has ONE .rodata section placed at ONE address, so game_12C1E0 cannot own
 * both float runs.  A yaml `- [0x246BF0, .rodata, game_12C1E0]` does not help
 * this function at all.
 *
 * ---------------------------------------------------------------------------
 * STEP-ZERO WIN: the record type came free from MATCHED code
 * ---------------------------------------------------------------------------
 * The 0x58-byte record built at sp+0x84 is field-for-field `Struct15102B38`
 * from game_12FDD0.c (MATCHED func_15102B38, which hands the same record to
 * func_1513D2F0): unk0=0x5F, unk1=5, unk2=0x2203, unk4=arg5, unk8/unkC=0,
 * unk10..13=0xFF, unk14 Vec2, unk1C/unk28 Vec3, unk34/38/3C=0.0f,
 * unk40=0x40CC0009, unk44=arg6, unk45=0xFF, unk46=0, unk47=7, unk48, unk4C.
 * The only correction is that unk14/unk18 are f32 here (12FDD0 only ever
 * block-copies them out of a Vec2 of s32, so its s32 spelling proves nothing).
 * The call is func_1513D2F0(&rec, &D_800A4AA0, 0,0,0, 0x1B, flag+1, 0,0,0,
 * arg2, arg3) -- the same 12-argument shape as game_12FDD0.c's.
 *
 * FRAME DECODE: framesize 0xE0.  arg-build [0x00,0x30) (12 args), sdc1 f20..f26
 * at 0x38..0x58, s0..s7/fp/ra at 0x58..0x80, homes [0x80,0xE0):
 *   [0xDF,0xE0) decl#1 u8  i     (`andi ...,0xff` on the increment)
 *   [0x84,0xDC) decl#2 rec (0x58)
 *   [0x80,0x84) decl#3 s32 flag
 * `sw $a2,0xE8($sp)` homes arg2 (0xE0+8), and `andi $s7,$a2,0xff` is the u8
 * conversion for func_1513D2F0's argA hoisted out of the loop.
 *
 * MEASURED (bounded window, 144 words)
 *   4660  honest `extern f32` spelling.  CURRENT.  frame 0xD0, size 580.
 *   2944  lui-able stand-in probe (semantically WRONG, shape evidence only).
 *    901  true-literal probe = what the migration would produce.  size 576.
 *
 * RESIDUAL CLASS: ALLOCATION forced by the rodata spelling.
 * =========================================================================== */

/* ---- parked source: this is the honest 4660 build, verbatim ---- */

typedef struct {
    /* 0x00 */ u8 unk0;
    /* 0x01 */ u8 unk1;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ u8 pad6[2];
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ u8 unk10;
    /* 0x11 */ u8 unk11;
    /* 0x12 */ u8 unk12;
    /* 0x13 */ u8 unk13;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ struct17 unk1C;
    /* 0x28 */ struct17 unk28;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ s32 unk40;
    /* 0x44 */ u8 unk44;
    /* 0x45 */ u8 unk45;
    /* 0x46 */ u8 unk46;
    /* 0x47 */ u8 unk47;
    /* 0x48 */ s32 unk48;
    /* 0x4C */ u8 unk4C;
    /* 0x4D */ u8 pad4D[3];
    /* 0x50 */ s32 unk50;
    /* 0x54 */ s16 unk54;
    /* 0x56 */ s16 unk56;
} Struct150FF474;

extern f32 D_800A2124;
extern f32 D_800A2128;
extern f32 D_800A212C;

void func_150FF474(struct17 *arg0, struct17 *arg1, s32 arg2, s32 arg3) {
    u8 i;
    Struct150FF474 rec;
    s32 flag;

    rec.unk0 = 0x5F;
    rec.unk1 = 5;
    rec.unk2 = 0x2203;
    rec.unk8 = 0;
    rec.unkC = 0;
    rec.unk10 = 0xFF;
    rec.unk11 = 0xFF;
    rec.unk12 = 0xFF;
    rec.unk13 = 0xFF;
    rec.unk1C = *arg0;
    rec.unk34 = 0.0f;
    rec.unk38 = 0.0f;
    rec.unk3C = 0.0f;
    rec.unk40 = 0x40CC0009;
    rec.unk45 = 0xFF;
    rec.unk46 = 0;
    rec.unk47 = 7;
    rec.unk4C = 0xFF;
    rec.unk48 = 0;
    rec.unk4 = (func_150ADA20() & 3) + 3;
    for (i = 0; i < 6; i++) {
        rec.unk14 = (func_150ADA68() * D_800A212C) + 5.0f;
        rec.unk18 = (func_150ADA68() * D_800A2128) + D_800A2124;
        rec.unk28 = arg1[i];
        rec.unk44 = (func_150ADA20() % 0x9CU) + 0x64;
        if ((func_150ADA20() & 1) != 0) {
            flag = 2;
        } else {
            flag = 0;
        }
        func_1513D2F0(&rec, (s32)&D_800A4AA0, 0, 0, 0, 0x1B, flag + 1, 0, 0, 0, arg2, arg3);
    }
}

/* the migration-equivalent spelling that reaches size 576 / score 901 is
 * identical except:
 *      rec.unk14 = (func_150ADA68() * 11.10000038f) + 5.0f;
 *      rec.unk18 = (func_150ADA68() * 0.9990000725f) + 2.48300004f;
 * -- those three decimal spellings assemble to 0x4131999A / 0x3F7FBE78 /
 * 0x401EE979, i.e. the exact ROM words, and IDO emits them into .rodata in the
 * ROM's order (2124, 2128, 212C).  It cannot be shipped: live-C .rodata is
 * /DISCARD/ed and block 0x246B10 cannot be migrated (see above). */
