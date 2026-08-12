/*
 * PARKED near-miss -- func_150428D4  (game_6E770.c, 876 B)
 *
 * BEST MEASURED SCORE:     2953
 * BEST MEASURED STRUCTURE: 3003  <-- THE BODY BELOW.  Read the next paragraph before
 *                                   "fixing" the 50-point regression; it is not one.
 *   cd conker && python3 ../tools/asm-differ/diff.py -o func_150428D4 -R --max-lines 4096
 *   Identical with and without -R for every variant measured.  Frame 0x80 correct AND every
 *   stack offset matches golden (sp54/sp58/sp5C/sp60/sp64 out-params, and `flag`'s home at
 *   0x68, land where golden puts them).
 *
 * ------------------------------------------------- WHY THE PARKED BODY SCORES 3003, NOT 2953
 * The only difference between the 2953 source and the 3003 source is ONE token:
 *     s32 glyph;  glyph = func_15042C40(c) & 0xFF;      -> 2953   ins=8 del=8 chg=5 reg=93
 *     u8  glyph;  glyph = func_15042C40(c);             -> 3003   ins=8 del=8 chg=6 reg=92
 * The u8 form EMITS GOLDEN'S SECOND `andi s3,v0,0xff`, which the s32 form cannot:
 *     golden        jal ; nop / andi v1,v0,0xff / li at,0x60 / andi s3,v0,0xff / bne / [move t0,zero]
 *     s32 glyph     jal ; move s4,zero / andi v1,v0,0xff / li at,0x60 / bne / [move s3,v1]
 *     u8  glyph     jal ; move s4,zero / andi v1,v0,0xff / li at,0x60 / bne / [andi s3,v0,0xff]
 * i.e. with `u8 glyph` the instruction is PRESENT and merely sits in the bne delay slot
 * instead of before the branch; with `s32 glyph` it does not exist at all and a `move` stands
 * in its place.  asm-differ charges the u8 form 50 points for the displacement while giving
 * the s32 form a free pass on a missing instruction -- the misranking the cookbook warns about.
 * Ship whichever you like, but do NOT conclude that `s32 glyph` is closer.
 *
 * CORPUS EVIDENCE for `u8 glyph` (this is how it was found, not by guessing):
 * 629,660 lines of disassembly from 841 built objects contain 66 sites with two
 * `andi rX,rY,0xff` off one source register; only TWO send the second to a callee-saved
 * register, and one of them -- game_131F30.c `func_151050B0` @0x940 -- is golden's shape
 * exactly (`andi v1,v0,0xff` ... `andi s1,v0,0xff`, gap 4).  Its C assigns an int expression
 * to a **u8 variable** that is then live across a `jal`: the mask for the long-lived variable
 * is REMATERIALISED rather than copied.  That is the whole mechanism.  `s32 x = f() & 0xFF`
 * makes one masked value and copies it; `u8 x = f()` makes the mask the assignment itself.
 *
 * ---------------------------------------------- THE GLYPH TABLE'S REAL TYPE (recovered, free)
 * `D_80085994` was declared here as `extern u8 (*D_80085994)[4];`.  Its real type is already
 * written down in an ALREADY-MATCHED TU -- src/game_42DC0.c:47-57:
 *     typedef struct { u8 width; u8 height; u8 unk2; u8 unk3; } Glyph15015A38;
 *     extern Glyph15015A38 *D_80085994[];        <- ARRAY OF POINTERS, one per font
 * so this function's accesses are `D_80085994[0][glyph].width` etc.  The named fields tell you
 * what the arithmetic means: the advance is `width + unk2 - 1` and the line height is
 * `height + unk3`.  Adopting it is score-neutral (2953 -> 2953 on the s32 base, 3003 -> 3003 on
 * the u8 base, byte-identical objects), so it is pure documentation profit and it is what the
 * body below uses.  ALWAYS grep the tree for a symbol before inventing a type for it.
 *
 * ------------------------------------------------------------------------------- RESIDUAL
 * NINE callee-saved registers where golden uses SEVEN, and that single fact produces ~92 of
 * the ~114 differing rows (every later register name shifts).  The two extras:
 *   flag        -> s4    golden keeps it in t0 and stores/reloads its own -g3 home 0x68(sp)
 *                        around func_150415E0.  (0x68 IS flag's debug home in this declaration
 *                        order -- homes run DESCENDING from 0x7C, so c=0x7C i=0x78 glyph=0x74
 *                        lineH=0x70 maxW=0x6C flag=0x68 sp64=0x64 ... sp54=0x54 temp=0x50.
 *                        The declaration order below is therefore already correct; do not
 *                        permute it, it will move the out-param offsets.)
 *   &D_80085994 -> s6/s7 IDO LICM-hoists `lui %hi ; addiu %lo` into the loop preheader and
 *                        loads `0(sN)` twice; golden rematerialises `lui %hi ; lw %lo(sym)`
 *                        at each of the two uses.
 * Because `flag` sits in a callee-saved register, the scheduler is free to sink `flag = 0`
 * into the func_15042C40 JAL delay slot (golden's is a `nop` there and `move t0,zero` takes
 * the bne delay slot).  Get flag into t0 and that whole block falls into place by itself --
 * the delay-slot placement is a SYMPTOM of the register class, not a cause of it, so do not
 * try to steer the delay slot directly.
 * Smaller rows: two extra prologue `sw` + two extra epilogue `lw` (the 9-vs-7 saves), an extra
 * `beqz a0` (the while's entry test, which golden does not emit), `addu s2,s3,v1` scheduled
 * after the guard branch instead of before it, one `b`/`nop` pair at the `*arg3 = sp5C` store,
 * and one `bnez`-vs-`bnezl` at the lineH update.
 *
 * ============================== MEASURED NEGATIVES ==============================
 * Every line was built HARD (object AND asm-processor intermediate removed, make hard-failed
 * on error, object existence checked) and scored with AND without -R -- equal for every one.
 * Structural counts are inserts/deletes/changed/register-only rows from the same diff.
 *
 * --- carried over from the previous wave (pointer-cursor era; do not re-explore) ---
 *   3857  parked baseline (u8 *p cursor)
 *   3857  p = str + glyph;
 *   4051  separate never-reassigned `s32 idx` used only for the cursor
 *   4091  glyph declared u8, no explicit & 0xFF        <-- ON THE POINTER-CURSOR BASE.  On the
 *         index base this is the 3003 STRUCTURAL WIN above.  The old number is why it was
 *         dismissed; it was measured on a base whose loop shape was wrong.
 *   3907  u8 index copy + s32 compare copy (chasing the double andi) on the pointer base
 *   3197  the same split on top of the 2953 index base
 *   3885  `p = &str[glyph];` hoisted above the `*arg2 += 0xC` block
 *   3747  caching str[0] in the (dead at that point) sp60 slot -- permuter find, and WRONG
 *   4122  for (;;) { c = str[i]; if (c == 0) break; ... }
 *   3278  index rewrite, `c = str[i]; do { ... } while (c != 0);`
 *   3278  index rewrite, `} while ((c = str[i]) != 0);`
 *   3147  index rewrite + a row pointer reloaded once per statement
 *   2845  index rewrite + `u8 (*metrics)[4]` local caching D_80085994   <-- REJECTED: better
 *         score, but the extra local consumes a stack home and shifts every func_150415E0
 *         out-param slot DOWN BY 4 while the frame stays 0x80.  Unreachable position.
 *         ANY new local in this function does this.  That is why the D_80085994 hoist cannot
 *         be attacked by caching it, and it is the reason `row`/`metrics` locals are banned.
 *
 * --- NEW this wave, all on the 2953 index base unless stated ---
 *   2953  regenerated parked baseline (generator sanity check)   ins=8 del=8 chg=5 reg=93
 *   3003  `u8 glyph` (no explicit mask)                          ins=8 del=8 chg=6 reg=92  *WIN*
 *   3511  `u8 glyph` PLUS a redundant `& 0xFF`                   ins=8 del=8 chg=8 reg=99
 *
 *   LOOP SHAPE.  Golden emits ONE guard (`lbu t9,0(s3)` / `beql t9,zero,exit` with
 *   `lw t2,0(s1)` in the delay slot), then `addu s2,s3,v1`, then an UNTESTED
 *   `lbu a0,0(s2)` / `move v0,a0`, then the body.  Three shapes were tried to reproduce it:
 *   4312  `while (str[i] != 0) { c = str[i]; ... }` (no outer if)  ins=5 del=8 chg=12 reg=94
 *         -- DOES remove the extra entry test and DOES put `addu s2` before the guard, but the
 *         condition is read FIRST so the CSE temp is int-typed and `c = str[i]` becomes
 *         `andi a0,v0,0xff` where golden has `move v0,a0`.
 *   4157  `if (str[0] != 0) { do { c = str[i]; ... } while (str[i] != 0); }`   ins=5 del=8 chg=11
 *   4157  ... same with a bare-truthiness loop condition
 *   4157  ... same with a bare-truthiness outer guard
 *         -- all three lose the `beqzl`+`lw` guard (plain `beqz`, delay slot taken by `addu s2`)
 *            and still emit the `andi` instead of the `move`.
 *   4207  `u8 glyph` + the do-while shape                        ins=5 del=8 chg=12 reg=96
 *   The loop-shape family trades the extra `beqz` for a worse guard; nothing found that gets
 *   both.  It is NOT the 9-vs-7 register problem, so it is second priority.
 *
 *   D_80085994 ADDRESS HOIST -- SIX independent spellings, ALL byte-identical output
 *   (`lui sN,%hi ; addiu sN,sN,%lo` still hoisted into the preheader every time):
 *   2953  `extern u8 (*D_80085994)[4];`     `D_80085994[glyph][0]`            (the old base)
 *   2953  `((u8 *)D_80085994)[glyph * 4 + k]`                                 flat cast
 *   2953  `((Metrics *)D_80085994)[glyph].unkK`                               struct cast
 *   2953/3003  `extern Glyph15015A38 *D_80085994[];`  `D_80085994[0][glyph].width`  real type
 *   3003  `(*D_80085994)[glyph].width`
 *   3003  `(D_80085994[0] + glyph)->width`
 *   The address materialisation is NOT reachable from the access spelling.  Corpus context:
 *   879 sites across the corpus rematerialise a global pointer (`lui %hi` + `lw %lo`) and 180
 *   sites hoist its address into a callee-saved register -- BOTH behaviours are common in
 *   matched C, so this is a cost-model/ranking decision, not a spelling.
 *   3414  metrics statements SWAPPED (temp first, `*arg1 +=` second)  ins=5 del=11 chg=7 reg=87
 *         -- removes the intervening store, so IDO collapses the two pointer loads into one.
 *            Golden loads it twice.  Wrong direction despite the lower register-row count.
 *   3013  `temp = unk3 + height;` instead of `height + unk3` (golden's addu is [3]+[1], but
 *         the source order that produces it is [1]+[3]; do not "fix" it)
 *
 *   FLAG -> t0 attempts, all on the u8-glyph (3003) base:
 *   3187  `flag` declared in the inner block scope instead of the top-level list
 *   3003  `if (flag)` instead of `if (flag != 0)`            (exactly inert)
 *   3153  `flag = 0;` moved BEFORE the call                  (reg=94: strictly worse -- flag is
 *         then genuinely live across func_15042C40 as well)
 *   Nothing moved flag out of a callee-saved register.
 *
 * -------------------------------------------------------------------- WHAT TO TRY NEXT
 * The residual is one question and it is a register-CLASS question, not a spelling question:
 * why does IDO promote `flag` and `&D_80085994` to callee-saved registers here when golden's
 * compile left `flag` in its 0x68 home and rematerialised the address?  Both compiles have all
 * nine of s0-s8 free, so this is IDO's promotion COST MODEL ranking two low-benefit candidates
 * differently, driven by estimated block frequency.  That points at the CFG -- i.e. at the loop
 * shape above -- rather than at any expression.  A profitable next move is to find, in the
 * corpus, a matched function with a loop containing a call plus a boolean flag set on some
 * paths, and compare its C's loop shape with ours; the `func_151050B0` andi hit shows this
 * corpus route works.  Do NOT spend another run on access spellings for D_80085994, and do NOT
 * add a local of any kind -- the 0x54..0x68 stack offsets are correct now and any new local
 * moves them.
 *
 * HARNESS: `./permuter_tu.sh selftest` PASSES for game_6E770 (a, b, b2, c, d all PASS; (e)
 * reports isolation differs from the in-TU build, so the TU-aware harness is load-bearing).
 * ~1700 iterations from the 2953 base with PERMUTER_TU_REQUIRE_FRAME=128 produced nothing that
 * keeps the stack layout.  Gate any future run on the OUT-PARAM OFFSETS, not just the frame.
 */
#include <ultra64.h>
#include "functions.h"
#include "variables.h"


extern u8 D_80084930;
extern u8 D_800848D0[];
extern u8 D_80085930;
extern u8 D_80085931;
extern u8 D_80085932;
extern u8 D_80085933[];

#define WGFX(pkt, a, b)             \
{                                   \
    Gfx *_g = (Gfx *)(pkt);         \
    _g->words.w0 = (u32)(a);        \
    _g->words.w1 = (u32)(b);        \
}

Gfx *func_150412C0(Gfx *gfx) {
    WGFX(gfx++, 0xD7000002, 0xFFFFFFFF);
    WGFX(gfx++, 0xE7000000, 0x00000000);
    WGFX(gfx++, 0xFCFFFFFF, 0xFFFCF279);
    WGFX(gfx++, 0xEF002C0F, 0x0055204C);
    WGFX(gfx++, 0xFD90003F, &D_80084930);
    WGFX(gfx++, 0xFD900000, &D_80084930);
    WGFX(gfx++, 0xF5900000, 0x07000000);
    WGFX(gfx++, 0xE6000000, 0x00000000);
    WGFX(gfx++, 0xF3000000, 0x077FF200);
    WGFX(gfx++, 0xE7000000, 0x00000000);
    WGFX(gfx++, 0xF5800800, 0x00000000);
    WGFX(gfx++, 0xF2000000, 0x000FC1FC);
    return gfx;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_6E770/func_150413FC.s")

s32 func_15041480(u8 arg0) {
    s32 i;

    for (i = 0; ; ) {
        if (arg0 == D_800848D0[i]) {
            return i;
        }
        if (arg0 == D_800848D0[i + 1]) {
            return i + 1;
        }
        if (arg0 == D_800848D0[i + 2]) {
            return i + 2;
        }
        if (arg0 == D_800848D0[i + 3]) {
            return i + 3;
        }
        i += 4;
        if (i != 0x50) {
            continue;
        }
        break;
    }

    return i;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_6E770/func_150415E0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_6E770/func_150417AC.s")

/* Real type, copied from the already-matched src/game_42DC0.c (func_15015A38 writes this
 * table). D_80085994 is an ARRAY OF POINTERS, one glyph table per font; this function uses
 * font 0, which is why golden's `lw` carries a bare %lo(D_80085994) with no offset. */
typedef struct {
    u8 width;
    u8 height;
    u8 unk2;
    u8 unk3;
} Glyph15015A38;

extern Glyph15015A38 *D_80085994[];
extern f32 D_800380A4;

s32 func_15042C40(u8);
void func_150415E0(s32, s32 *, s32 *, f32 *, s32 *, f32 *);

void func_150428D4(u8 *str, s32 *arg1, s32 *arg2, s32 *arg3) {
    u8 c;
    s32 i;
    u8 glyph;
    s32 lineH;
    s32 maxW;
    s32 flag;
    s32 sp64;
    s32 sp60;
    f32 sp5C;
    s32 sp58;
    f32 sp54;
    s32 temp;

    if (str == NULL) {
        return;
    }

    *arg1 = 0;
    *arg2 = 0;
    *arg3 = 0;
    maxW = 0;
    lineH = 0;
    i = 0;
    if (str[0] == 0) {
        *arg2 += 0xC;
    }
    if (str[0] != 0) {
        while ((c = str[i]) != 0) {
            if (c == 0xBC) {
                i += 2;
            } else {
                glyph = func_15042C40(c);
                flag = 0;
                if (glyph == 0x60) {
                    *arg1 += 4;
                    if (lineH < 0xC) {
                        lineH = 0xC;
                    }
                } else if ((glyph >= 0xA1) && (glyph < 0xA8)) {
                    /* control codes 0xA1..0xA7 occupy no space */
                } else if ((glyph >= 0xA8) && (glyph < 0x100)) {
                    func_150415E0(glyph, &sp64, &sp60, &sp5C, &sp58, &sp54);
                    *arg1 = (s32)(*arg1 + sp64 * sp54);
                    temp = (s32)((s32)(sp60 * sp54) - sp5C) + 1;
                    if (lineH < temp) {
                        lineH = temp;
                    }
                    if (*arg3 < sp5C) {
                        *arg3 = (s32)sp5C;
                    }
                } else if (glyph < 0xA1) {
                    if (str[i] == 0xA) {
                        if (maxW < *arg1) {
                            maxW = *arg1;
                        }
                        *arg1 = 0;
                        if (lineH < 0xC) {
                            lineH = 0xC;
                        }
                        *arg2 += lineH;
                        lineH = 0;
                    } else {
                        flag = 1;
                    }
                }
                i++;
                if (flag != 0) {
                    *arg1 += D_80085994[0][glyph].width + D_80085994[0][glyph].unk2 - 1;
                    temp = D_80085994[0][glyph].height + D_80085994[0][glyph].unk3;
                    if (lineH <= temp) {
                        lineH = temp;
                    }
                }
            }
        }
    }

    if (*arg1 < maxW) {
        *arg1 = maxW;
    }
    *arg2 += lineH;
    *arg1 = (s32)(*arg1 * D_800380A0);
    *arg2 = (s32)(*arg2 * D_800380A4);
    *arg3 = (s32)(*arg3 * D_800380A0);
}

s32 func_15042C40(u8 arg0) {
    s32 i;
    u8 c;
    u8 *ptr;
    s32 original;

    original = arg0;
    if ((original >= 0x61) && (original < 0x7B)) {
        c = original - 0x20;
    } else {
        c = original;
    }

    if (original == 0x20) {
        return 0x60;
    }

    i = 3;
    if (D_80085930 == c) {
        return 0;
    }
    if (D_80085931 == c) {
        return 1;
    }
    if (D_80085932 == c) {
        return 2;
    }

    ptr = D_80085933;
    for (i = 3; ; ) {
        if (c == ptr[0]) {
            return i;
        }
        if (c == ptr[1]) {
            return i + 1;
        }
        if (c == ptr[2]) {
            return i + 2;
        }
        if (c == ptr[3]) {
            return i + 3;
        }
        i += 4;
        ptr += 4;
        if (i != 0x5F) {
            continue;
        }
        break;
    }

    return original;
}
