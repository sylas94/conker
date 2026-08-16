/* ============================================================================
 * PARKED  func_15080828  (game_AD9B0.c) -- the LAST pragma in that TU, so
 * closing it makes game_AD9B0.c a fully decompiled TU.  960 B golden.
 * WAVE 5 (2026-08-13), cold start.
 *
 * ===================== FRAME DECODE, READ OFF GOLDEN =======================
 * Prologue/epilogue:  addiu sp,sp,-0x48 / sw ra,0x24(sp) / sw a0,0x48(sp)
 *                     ... lw ra,0x24(sp) / addiu sp,sp,0x48 / jr ra
 * framesize 0x48 = 72.  NO callee-saved register is saved at all -- `ra' is
 * the only thing in the save area.  Every stack slot the function touches:
 *
 *   0x10 0x14 0x18   arg build.  func_1502B6BC is called with a0..a3 plus
 *                    slots 0x10/0x14/0x18, i.e. SEVEN arguments, so the arg
 *                    build is 0x00..0x1B rounded up to 0x00..0x1F.
 *   0x24             $ra
 *   0x2C 0x30 0x38 0x3C 0x40      locals
 *   0x48             $a0 -- the PARAMETER, homed in the CALLER's arg slot
 *                    (written once at entry, then re-read with `lw t9,0x48(sp)'
 *                    three separate times late in the function).  Per the
 *                    parameter-home rule this costs the frame nothing.
 *
 * Home area ENDS at framesize (0x48) and runs TOP-DOWN in declaration order.
 * The used slots are 0x40 0x3C 0x38 0x30 0x2C with DEAD HOLES at 0x44 and
 * 0x34.  Reading the holes as register-only declared autos gives a seven-word
 * home area 0x2C..0x47, sum(sizeof(local)) = 0x1C = 28:
 *
 *      declared #1 -> 0x44   (dead hole: register-only)
 *      declared #2 -> 0x40   flag        (3 stores, 2 loads; a real variable)
 *      declared #3 -> 0x3C   lenA        strlen(D_800D1948->unk0) + 1
 *      declared #4 -> 0x38   lenB        strlen(D_800D1944->unk0) + 1
 *      declared #5 -> 0x34   (dead hole: register-only)
 *      declared #6 -> 0x30   total       D_800D1995 + half
 *      declared #7 -> 0x2C   half        D_800D1948->unkC >> 1
 *
 * The competing reading is that the home area is only 0x38..0x47 (four words)
 * and that 0x2C/0x30 are compiler TEMPS -- they are written just before a call
 * and reloaded just after it, which is the spill signature.  The two readings
 * are distinguished by the brief's move test: reorder the declarations and see
 * which slots move.  MEASURE BEFORE BELIEVING EITHER.
 *
 * ================== VALIDATION AGAINST THE SPILL/RELOAD PAIRS ==============
 * Every value live across a call is bracketed, and the widths pin the types:
 *   0x40  sw t9 / sw zero / sw zero  ... lw t1 (twice, after two calls)  -> s32
 *   0x3C  sw t6 (strlen+1) ... lw a2 (bcopy size), lw v0 (pointer bump)  -> s32
 *   0x38  sw t8 (strlen+1) ... lw a2 (bcopy size)                        -> s32
 *   0x30  sw v1 ... lw t7  across allocate_memory                        -> s32
 *   0x2C  sw t6 ... lw a2, lw t6  across allocate_memory and bcopy       -> s32
 * All five are word-width; there is no byte or half local and no f32 local
 * (the three float constants are materialised with lui/mtc1 straight into
 * $f4/$f6/$f8 and stored to globals, never homed).
 *
 * ===================== SEMANTICS, READ OFF GOLDEN ===========================
 * flag  = (arg0 == 0 && !(D_800D2E68 & 0x10));   three separate stores
 * D_800D1944 = func_1502B6BC(0,0,0,3, 0x1A, D_800BEAAB, D_800D1940);
 * if (D_800D1944 == 0) return;
 * D_800D1994 = 0; D_800D1998 = res->unk8; D_800D1995 = res->unkC >> 1;
 * if (flag) { second func_1502B6BC with arg6 = 0x43; build the concatenated
 *             string in D_800D194C with a 0xBD separator byte; rebuild the
 *             u16 table in D_800D1998 }
 * else     { D_800D1948 = 0; }
 *
 * *** ORIGINAL-GAME QUIRK, MUST BE REPRODUCED, NOT "FIXED" ***
 * After the SECOND func_1502B6BC (whose result is stored to D_800D1948) the
 * early-out re-tests **D_800D1944**, not D_800D1948:
 *      1508090C  lui $t9, %hi(D_800D1944)
 *      15080918  lw  $t9, %lo(D_800D1944)($t9)
 *      1508091C  beql $t9, $zero, .L15080BDC
 * D_800D1944 was already proven non-zero eight instructions earlier and
 * nothing writes it in between, so the test is dead in practice -- but it is
 * golden and the compiler could not remove it (D_800D1944 is a global and
 * func_1502B6BC may write it).  Writing `if (D_800D1948 == 0)' would be a
 * different function.
 *
 * The two flag tests near the end:
 *   if (flag != 0 || arg0 != 0 || !(D_800D2E60[D_800D1940 >> 3] &
 *                                   (1 << (D_800D1940 & 7)))) {
 *       if (D_800D2E40 == 0) { cfg->unk0 |= 0x60; }
 *   }
 *   if (arg0 != 0 || D_800D1940 == 0x42) { cfg->unk0 |= 0x80; }
 * The bit test is the same idiom func_15080500 already uses in this TU
 * (`idx = arg3 >> 3; mask = 1 << (arg3 & 7)'), with `sra' because the u8 is
 * promoted to signed int.
 *
 * D_800D1958 is `extern s32 D_800D1958[12]' in variables.h (48 bytes, marked
 * "struct?").  It is used here purely as a struct, so this TU casts it with a
 * FILE-LOCAL typedef -- the shared header is not touched.
 * D_800D2E40 is declared nowhere in include/; game_20AE20.c line 48 has
 * `extern u8 D_800D2E40;' so this TU uses the same file-local extern.
 *
 * ============================ MEASUREMENTS =================================
 * All through tools/buildlock.sh with the stale-object guard (rm the .o AND
 * the asm-processor intermediate, make, assert the object exists).
 *   first draft (semantics as decoded above) ......... 6305, ours 1028 B
 *   + flag if/else ARMS SWAPPED (see below) .......... 6095, ours 1028 B
 *   + the three float stores moved to just before the
 *     func_1516A7B0 call .............................. 6760  -- REVERTED,
 *       it is worse; leave them where the shipped source has them.
 * golden is 960 B, so the shipped draft is 68 B (17 instructions) too big.
 * Frame is EXACT at 0x48 from the first draft, and every stack offset the
 * function uses (0x10 0x14 0x18 0x24 0x2C 0x30 0x38 0x3C 0x40 0x48) is
 * already correct, so the frame decode above is CONFIRMED, not conjectural.
 *
 * THE FLAG BLOCK IS NOW BYTE-IDENTICAL TO GOLDEN (rows 328..370, 17 rows,
 * every register included).  The lever was the ARM ORDER, read off the branch
 * sense: golden emits `bnez t8,368' with the FALL-THROUGH arm setting flag=1,
 * so the source must test the ZERO case first:
 *       if ((D_800D2E68 & 0x10) == 0) { flag = 1; } else { flag = 0; }
 * and NOT the equivalent `if (D_800D2E68 & 0x10) { flag = 0; } else ...',
 * which emits `beqz' and costs 210.
 *
 * ================= THE ONE BLOCKER LEFT, AND IT IS SYSTEMIC ================
 * Golden materialises the address of D_800D1958 into a register ONCE and does
 * every field access off it:
 *       5a4  lui   v0, %hi(D_800D1958)
 *       5ac  addiu v0, v0, %lo(D_800D1958)
 *       ...  sw t3,4(v0) / sh t7,0x26(v0) / sb t4,8(v0) / sh zero,0x24(v0)
 *            / sb zero,0x2b(v0) / sw t0,0x18(v0) / sw t1,0x1c(v0)
 *            / sw t2,0x20(v0) / sb v1,0x28(v0) / sb v1,0x29(v0)
 *            / sb v1,0x2a(v0) / lw t6,0(v0) / sw t7,0(v0)
 * Ours re-materialises `lui at,%hi(D_800D1958)' for EVERY non-zero offset --
 * eleven extra instructions, i.e. 44 of the 68 excess bytes.  It also forces
 * the constant 0xFF to be rebuilt three times (golden has ONE `li v1,0xff',
 * hoisted into a branch delay slot at 620).
 *
 * THIS IS NOT A SPELLING PROBLEM.  Measured in the standalone IDO probe
 * harness (scratchpad w5-m3p8vq/probe.sh, p3.c, p4.c), IDO constant-folds a
 * local pointer whose value is a link-time constant address, in EVERY form
 * tried, and then reaches each field through an `at' macro:
 *     p = (S *)G;            /* array cast, what the TU does */   folded
 *     p = &GS;               /* struct via a file-local shadow */ folded
 *                            -- p3.c v1 and v2 are BYTE-IDENTICAL objects,
 *                               so the "declare it as a struct" idea is dead
 *                               and does not need a TU build to refute
 *     two reaching defs of p, both the same constant (p4.c w2)     folded
 *     p assigned at the top and live across a call (p4.c w4)       folded
 *     p a PARAMETER (p4.c w3)                                      REGISTER
 * Only a genuinely non-constant base keeps the register.  So golden's source
 * does something here that `p = &global' does not express, and finding it is
 * the whole remaining job on this function.
 *
 * NOTE FOR A LATER WAVE -- this may be worth more than this one function.  A
 * scan for the pattern across the tree is parked at w5-m3p8vq/findbase.py; it
 * currently reports 0 hits because it only recognises an ADJACENT lui/addiu
 * pair and golden's are two instructions apart (5a4 / 5ac).  Fix that and
 * count how many golden functions hold a global base in a register versus how
 * many live-C ones do.  If the live-C count really is ~0 while golden's is
 * large, this is a systemic blocker of the same shape as the jtbl one, not a
 * quirk of func_15080828.
 *
 * REMAINING SMALLER RESIDUALS, all read off the diff and none yet addressed:
 *   * ours spills `half * 2' to 0x28(sp) across the first bcopy and reloads
 *     it (`sw a3,0x28(sp)' / `lw a3,0x28(sp)', +8 B).  Golden does NOT keep
 *     it: it reloads `half' from its home at 0x2c and recomputes `sll' both
 *     times.  Our compile CSE'd the two `half * 2' subexpressions; golden's
 *     did not.
 *   * from row 374 onward every temp is off by exactly ONE step of the IDO
 *     rotation (ours t5/t6/t4 where golden has t6/t7/t5), i.e. golden created
 *     one more temp web than we did before that point even though the emitted
 *     flag block is now identical.  Per the rotation law in the cookbook that
 *     is a single missing folded temp, not eleven separate register bugs --
 *     fix the D_800D1958 base first and re-read, because that is exactly the
 *     kind of change that shifts the whole rotation.
 *   * golden `bnel t5,at,648' vs ours `bne t5,at,650' at the D_800D1940==0x42
 *     test -- almost certainly downstream of the size difference, not its own
 *     problem.
 *
 * STATE: the #pragma is RESTORED and this TU is untouched in git.  The source
 * below is the 6095 draft, ready to paste back over the pragma.
 * ============================================================================ */

#include <ultra64.h>
#include "functions.h"
#include "variables.h"

typedef struct {
    char *unk0;
    s32 unk4;
    void *unk8;
    u32 unkC;
} Res15080828;

typedef struct {
    s32 unk0;
    s32 unk4;
    u8 unk8;
    u8 pad9[0xF];
    void *unk18;
    void *unk1C;
    void *unk20;
    s16 unk24;
    s16 unk26;
    u8 unk28;
    u8 unk29;
    u8 unk2A;
    u8 unk2B;
} Cfg15080828;

extern u8 D_800D2E40;
extern void *func_1502B6BC(s32, s32, s32, s32, s32, s32, s32);
extern void *allocate_memory(s32, s32, s32, s32);
extern s32 strlen(const char *);
/* NB: do NOT declare bcopy here -- include/2.0L/PR/os_libc.h line 84 already
 * has `extern void bcopy(const void *, void *, int);' and re-declaring it with
 * s32 is a hard cfe error ("Incompatible type for the function parameter"). */
extern void *func_1516A7B0(s32, s32, s32, void *, void *, s32);

void func_15080828(s32 arg0) {
    Cfg15080828 *cfg;
    s32 flag;
    s32 lenA;
    s32 lenB;
    char *name;
    s32 total;
    s32 half;

    if (arg0 == 0) {
        if ((D_800D2E68 & 0x10) == 0) {
            flag = 1;
        } else {
            flag = 0;
        }
    } else {
        flag = 0;
    }

    D_800D1944 = (s32)func_1502B6BC(0, 0, 0, 3, 0x1A, D_800BEAAB, D_800D1940);
    if (D_800D1944 == 0) {
        return;
    }
    D_800D1994 = 0;
    D_800D1998 = (s32)((Res15080828 *)D_800D1944)->unk8;
    D_800D1995 = ((Res15080828 *)D_800D1944)->unkC >> 1;

    if (flag != 0) {
        D_800D1948 = (s32)func_1502B6BC(0, 0, 0, 3, 0x1A, D_800BEAAB, 0x43);
        if (D_800D1944 == 0) {
            return;
        }
        lenA = strlen(((Res15080828 *)D_800D1948)->unk0) + 1;
        lenB = strlen(((Res15080828 *)D_800D1944)->unk0) + 1;
        D_800D194C = (s32)allocate_memory(lenA + lenB + 1, 1, 0, 0);
        bcopy(((Res15080828 *)D_800D1948)->unk0, (void *)D_800D194C, lenA);
        ((u8 *)D_800D194C)[lenA - 1] = 0xBD;
        bcopy(((Res15080828 *)D_800D1944)->unk0, (void *)(D_800D194C + lenA), lenB);
        half = ((Res15080828 *)D_800D1948)->unkC >> 1;
        total = D_800D1995 + half;
        D_800D1998 = (s32)allocate_memory(total * 2, 1, 0, 0);
        bcopy(((Res15080828 *)D_800D1948)->unk8, (void *)D_800D1998, half * 2);
        bcopy(((Res15080828 *)D_800D1944)->unk8,
              (void *)(D_800D1998 + half * 2), D_800D1995 * 2);
        D_800D1995 = total;
    } else {
        D_800D1948 = 0;
    }

    D_800D1941 = 1;
    if (flag != 0) {
        name = (char *)D_800D194C;
    } else {
        name = ((Res15080828 *)D_800D1944)->unk0;
    }

    cfg = (Cfg15080828 *)D_800D1958;
    cfg->unk0 = 0x38013;
    if ((flag != 0) || (arg0 != 0) ||
        !(D_800D2E60[D_800D1940 >> 3] & (1 << (D_800D1940 & 7)))) {
        if (D_800D2E40 == 0) {
            cfg->unk0 |= 0x60;
        }
    }
    if ((arg0 != 0) || (D_800D1940 == 0x42)) {
        cfg->unk0 |= 0x80;
    }

    D_800D1988 = 78.0f;
    D_800D198C = 48.0f;
    D_800D1990 = 9.0f;
    cfg->unk4 = (s32)name;
    cfg->unk26 = 100;
    cfg->unk8 = 1;
    cfg->unk24 = 0;
    cfg->unk2B = 0;
    cfg->unk18 = &D_800D1988;
    cfg->unk1C = &D_800D198C;
    cfg->unk20 = &D_800D1990;
    cfg->unk28 = 0xFF;
    cfg->unk29 = 0xFF;
    cfg->unk2A = 0xFF;
    D_800D1950 = (s32)func_1516A7B0(0, 0, 0, (void *)func_150807F4, cfg, 0);
    ((u8 *)D_800D1950)[0x14] = 0;
}
