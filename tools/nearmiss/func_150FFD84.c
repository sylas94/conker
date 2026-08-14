/* ===========================================================================
 * func_150FFD84  --  game_12C1E0.c  --  1020 bytes  --  cold decompile
 * PARKED at 6378 (with AND without -R).  Draft1 was 6887.
 *
 * VERDICT: RODATA-BLOCKED, same mechanism as func_150EFB80 in game_11C2B0.
 * PROVEN by substitution: with the two in-loop float constants spelled as
 * ordinary lui-able literals instead of `extern f32`, the score drops to 4487,
 * the FRAME BECOMES EXACTLY 0x118, the `sdc1 $f26/$f28` saves appear, and the
 * ENTIRE LOOP BODY becomes structurally identical to golden (zero structural
 * rows from 0x1278 to the epilogue).  See MEASURED NEGATIVES.
 *
 * ---------------------------------------------------------------------------
 * FRAME DECODE (SETTLED -- reproduces the exact 0x118 frame once unblocked)
 * ---------------------------------------------------------------------------
 * framesize 0x118.  arg-build [0x00,0x20).  saved regs [0x20,0x70):
 *   f20 20 f22 28 f24 30 f26 38 f28 40 | s0 48 s1 4C s2 50 s3 54 s4 58
 *   s5 5C s6 60 s7 64 fp 68 ra 6C
 * Params: framesize 0x118 puts the caller arg slots at 0x118(a0) 0x11C(a1)
 *   0x120(a2) 0x124(a3); golden homes a2/a3 there at entry and reads
 *   `lbu 0x123(sp)` = ((u8 *)&arg2)[3] and `lw 0x124(sp)` = arg3.  Caller
 *   (asm/90840.s:422) passes func_150FFD84(s2, s3, 0xFF, 1).
 * Home area, TOP-DOWN in declaration order, ENDING at framesize:
 *   [0xA8,0x118) decl#1  0x70  spawn   (0xA8+0x70 == 0x118 exactly -> 1st)
 *   [0xA4,0xA8)  decl#2   4    count   (s2)
 *   [0xA0,0xA4)  decl#3   4    baseX   (s5)
 *   [0x9C,0xA0)  decl#4   4    baseY   (s6)
 *   [0x98,0x9C)  decl#5   4    yaw     (a1 of func_15145974 = sp+0x98)
 *   [0x94,0x98)  decl#6   4    pitch   (a2 of func_15145974 = sp+0x94)
 *   [0x84,0x94)  decl#7  0x10  tbl     (s3 = sp+0x84, copied from D_800A2160)
 *   [0x80,0x84)  decl#8   4    rand0   (s1; home never referenced)
 *   [0x7C,0x80)  decl#9   4    rand1   (s0; home never referenced)
 * sum = 0x70+4+4+4+4+4+0x10+4+4 = 0x9C; temps [0x70,0x7C) = 12 bytes;
 * 0x20(arg) + 0x50(saved) + 0xC(temp) + 0x9C(homes) = 0x118. CONFIRMED by
 * build: the unblocked variant emits `addiu sp,sp,-0x118` exactly.
 *
 * The spawn struct is the SAME type as `struct Local15153634Spawn` in the
 * matched func_15153634 (game_17CAF0.c) -- every one of the 30+ field offsets
 * written here lines up with it, and its size is 0x70, which is what makes
 * decl#1 end exactly at framesize.
 *
 * ---------------------------------------------------------------------------
 * THE BLOCKER
 * ---------------------------------------------------------------------------
 * Golden hoists D_800A2194 and D_800A2198 OUT of the loop into $f28/$f26:
 *      11f4: lui at,%hi(D_800A2194) ; 11f8: lwc1 $f28,%lo(D_800A2194)(at)
 *      1200: lui at,%hi(D_800A2198) ; 1204: lwc1 $f26,%lo(D_800A2198)(at)
 * A loop-invariant LOAD can only be hoisted out of a loop that contains calls
 * if the compiler knows the memory cannot be written -- i.e. only if it is a
 * COMPILE-TIME CONSTANT.  In the original these are float literals that IDO
 * emitted into this TU's own .rodata.  Spelled as `extern f32` they are
 * ordinary globals, every call in the loop may clobber them, and IDO correctly
 * re-loads them each iteration -- which also costs the two `sdc1` saves and
 * shrinks the frame by 0x10 to 0x108.  Neither is lui-able:
 *      D_800A2194 = 0xBF283127 = -0.6570000052  (low16 0x3127 != 0)
 *      D_800A2198 = 0x3F1EF9DC =  0.6210000515  (low16 0xF9DC != 0)
 * Block: conker/asm/data/246BF0.rodata.s.  The same block holds D_800A218C,
 * D_800A2190 and the D_800A2160 int table this function also reads, plus
 * constants consumed by the four functions still stubbed in this TU
 * (func_150FF2D4, func_150FF474, func_150FF6E0, func_150FF840), so the block
 * cannot be migrated for this function alone.
 *
 * ---------------------------------------------------------------------------
 * ONE OPEN QUESTION (3 instructions), separate from the blocker
 * ---------------------------------------------------------------------------
 * Golden computes baseY as a real multiply by zero and does NOT fold it:
 *      11e0: lui at,%hi(D_800A2190) ; 11ec: lwc1 $f6,%lo(D_800A2190)(at)
 *      11f0: mtc1 zero,$f4          ; 11fc: mul.s $f8,$f4,$f6
 * i.e. it constant-propagates `pitch` to 0.0 into the multiply's operand yet
 * still emits the load and the mul.  Every spelling tried folds
 * `0.0f * D_800A2190` away entirely, costing exactly those 3 instructions and
 * cascading a 3-instruction address shift (and its register renumbering)
 * through the rest of the function -- which is most of the residual score.
 * Tried and REFUTED: `pitch * D_800A2190` and the literal `0.0f * D_800A2190`
 * produce byte-identical output (proving `pitch` is already propagated), and
 * `extern const f32` changes nothing.  A consistent story requires golden's
 * right operand to be something an `extern f32` read cannot be, which points
 * at the same rodata migration.  DO NOT "fix" this with a construct that
 * merely hides the constant -- that would be a fake match.
 *
 * ---------------------------------------------------------------------------
 * MEASURED NEGATIVES / POSITIVES  (base noted for each -- the probe base and
 * the true base are DIFFERENT bases; do not compare across them)
 * ---------------------------------------------------------------------------
 * TRUE BASE (honest `extern f32` spelling):
 *   6887  draft1.
 *   6887  `extern const f32` on D_800A2194/D_800A2198.  ZERO effect.
 *   6887  literal `0.0f * D_800A2190` instead of `pitch * D_800A2190`.
 *         ZERO effect -> pitch is already constant-propagated.
 *   6378  CURRENT: draft1 + the three real fixes found on the probe base
 *         (store order, OR association, unk24 placement).
 * PROBE BASE (D_800A2194/2198 replaced by lui-able literals 0.5f/-0.5f;
 * semantically WRONG, evidence only -- this is the blocker-neutralised build):
 *   4745  probe alone.  Frame becomes EXACTLY 0x118, `sdc1 $f26/$f28` appear.
 *   4727  + `spawn.unk28 = spawn.unk2C = e;`  (draft1 had the double
 *         assignment the other way round, which stored 0xd4 before 0xd0;
 *         golden stores 0xd0 first, so unk28 must be the INNER assignment).
 *   4727->4487 + `spawn.unk58 = spawn.unk58 | (rand1 | rand0);` written with
 *         explicit parens (draft1's `|=` re-associated to
 *         `(unk58|rand1)|rand0`; golden groups the two flags first:
 *         `or t0,s0,s1` then `or t1,t3,t0`), AND moving
 *         `spawn.unk24 = 1.0f;` to the END of the init block (golden
 *         materialises 1.0f late and puts the `swc1 $f4,0xcc(sp)` in the
 *         func_15145974 delay slot; draft1 emitted it early).
 *   All three fixes are kept in the parked source below.
 *
 * RESIDUAL CLASS: the blocker is ALLOCATION/SCHEDULING forced by the rodata
 * spelling; the 3-instruction fold is a CODEGEN (algebraic simplification)
 * difference with the same suspected root cause.  With the block migrated this
 * function is expected to close: on the probe base the entire loop body and
 * the whole prologue are already byte-exact.
 * =========================================================================== */

/* ---- parked source: this is the 6378 build, verbatim ---- */

extern void func_15143794(s32, s32, f32, f32 *);
extern void *func_15130280(void *, u8, s32, s32, u8, s32);
void func_15145974(struct17 *arg0, f32 *arg1, f32 *arg2);
extern f32 D_800A218C;
extern f32 D_800A2190;
extern f32 D_800A2194;
extern f32 D_800A2198;
/* variables.h types D_800A5480 as a single `f32`, but the golden code copies
 * 12 bytes out of it (lw 0/4/8) and asm/data/249F40.rodata.s shows three
 * consecutive zero words there.  Cast at the use site rather than retype the
 * shared header, which 100+ TUs include. */

struct Local150FFD84Tbl {
    s32 unk0[4];
};

extern struct Local150FFD84Tbl D_800A2160;   /* {0x60,0x61,0x62,0x63} */

struct Local150FFD84Spawn {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ u16 unk08;
    /* 0x0A */ s16 unk0A;
    /* 0x0C */ s32 unk0C;
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
    /* 0x48 */ f32 unk48;
    /* 0x4C */ f32 unk4C;
    /* 0x50 */ f32 unk50;
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
    /* 0x67 */ u8 pad67[9];
};

void func_150FFD84(struct17 *arg0, struct17 *arg1, s32 arg2, s32 arg3) {
    struct Local150FFD84Spawn spawn;
    s32 count;
    s32 baseX;
    s32 baseY;
    f32 yaw;
    f32 pitch;
    struct Local150FFD84Tbl tbl;
    s32 rand0;
    s32 rand1;

    count = (func_150ADA20() % 9U) + 0xA;
    spawn.unk08 = 0x2203;
    spawn.unk00 = 0x200005;
    spawn.unk04 = 0;
    spawn.unk0C = 0;
    spawn.unk10 = 0;
    spawn.unk14 = 0xFF;
    spawn.unk15 = 0xFF;
    spawn.unk16 = 0xFF;
    spawn.unk17 = 0xFF;
    spawn.unk18 = 0xFF;
    spawn.unk19 = 0xFF;
    spawn.unk1A = 0xFF;
    spawn.unk1C = 0xFF;
    spawn.unk1E = 7;
    spawn.unk20 = 0x24;
    spawn.unk22 = 1;
    spawn.unk30 = *arg0;
    spawn.unk3C = *(struct17 *)&D_800A5480;
    spawn.unk58 = 0x4C207;
    spawn.unk5C = 0;
    spawn.unk60 = 0;
    spawn.unk61 = 7;
    spawn.unk62 = -1;
    spawn.unk63 = -1;
    spawn.unk64 = -1;
    spawn.unk65 = 0;
    spawn.unk66 = 0xFF;
    spawn.unk24 = 1.0f;
    func_15145974(arg1, &yaw, &pitch);
    pitch = 0.0f;
    baseX = (s16)((((s16)(s32)(yaw * D_800A218C)) >> 8) - 0x8A);
    baseY = (s16)((((s16)(s32)(pitch * D_800A2190)) >> 8) - 0x8A);
    do {
        tbl = D_800A2160;
        spawn.unk1D = tbl.unk0[func_150ADA20() % 4U];
        spawn.unk0A = (func_150ADA20() % 0xDU) + 0xA;
        spawn.unk1B = (func_150ADA20() % 0x65U) + 0x9B;
        spawn.unk28 = spawn.unk2C = (func_150ADA68() * 155.0f) + 75.0f;
        rand0 = func_150ADA20();
        rand1 = func_150ADA20();
        func_15143794((s16)((rand0 % 0x15U) + baseX), (s16)((rand1 % 0x15U) + baseY),
                      (func_150ADA68() * 20.0f) + 20.0f, &spawn.unk48);
        spawn.unk54 = (func_150ADA68() * D_800A2198) + D_800A2194;
        spawn.unk58 &= ~0xC0;
        if ((func_150ADA20() & 1) != 0) {
            rand0 = 0x80;
        } else {
            rand0 = 0;
        }
        if ((func_150ADA20() & 1) != 0) {
            rand1 = 0x40;
        } else {
            rand1 = 0;
        }
        spawn.unk58 = spawn.unk58 | (rand1 | rand0);
        func_15130280(&spawn, 1, 0, 0, ((u8 *)&arg2)[3], arg3);
        count--;
    } while (count > 0);
}
