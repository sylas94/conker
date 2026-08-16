/* func_150C1260  (game_EE710, 1024 bytes)  --  PARKED at 710 / 24600.
 *
 * WHAT IS DONE.  Frame (0x138), every stack-local address, the whole struct layout, both
 * loop-invariant float hoists ($f30 = 0.1f, $f28 = 0.9f, $f26 = 360.0f), the switch, all
 * three outgoing calls' argument blocks and the entire float schedule reproduce exactly.
 * ~230 of ~244 instructions are byte-identical.  Score history, all measured:
 *     3995 -> 3203 (declare the struct LAST + a named local for arg0->unk1D4)
 *          -> 2798 (unk56 before unk50; named `scale` local; unk08/unk0C/unk00 order)
 *          -> 1545 (declare the struct after `mag`, not last; `u8 ang`)
 *          ->  710 (read arg0->unk1D4 twice instead of via a local; two-step narrowing;
 *                   `while (i--)` -- NOT `while (i-- != 0)`, which emits sltu)
 *
 * THE RODATA IS *NOT* THE BLOCKER, BUT IT IS STILL REQUIRED TO SHIP.
 * This TU is a clean WHOLE-BLOCK migration and the loop-rodata law holds exactly as written:
 *     conker.us.yaml:1259    - [0x244C90, rodata]
 *                         -> - [0x244C90, .rodata, game_EE710]
 * Block 0x244C90..0x244CB0 = D_800A01D0 (0.4f), D_800A01D4 (-0.9f), D_800A01D8 (0.1f),
 * D_800A01DC (0.9f), D_800A01E0 (2.23f) + 3 zero words.  PROOF OF SOLE OWNERSHIP: grepping
 * conker/asm and conker/src for all five symbols returns only asm/EE710.s and
 * asm/nonmatchings/game_EE710/func_150C1260.s.  Written as LITERALS (as below) IDO hoists
 * 0.1f/0.9f into $f30/$f28 exactly as golden does -- confirming the law -- so the literals
 * are correct and the migration is the only thing standing between this C and the linker.
 * DO NOT APPLY THE YAML LINE UNTIL THE C REACHES 0: a migrated line with a live #pragma
 * breaks the link.
 *
 * THE RESIDUAL -- three clusters, every one of them "IDO folded a two-step sequence that
 * golden kept".  Nothing is missing, mis-ordered or mis-typed; these are copy-propagation
 * decisions.
 *
 *  1. golden  lw $v1,0x1D4($s2) / beqz $v1 / move $a0,$v1
 *     ours    lw $a0,0x1D4($s2) / beqzl $a0 / <epilogue in delay slot>
 *     Golden keeps the pointer in the CSE register $v1 and copies it to $a0; we coalesce
 *     straight into $a0, so there is no useful delay-slot filler and IDO switches to beqzl.
 *     Tried: named local read twice; named local read once; global read twice (current);
 *     positive nesting.  All identical.
 *
 *  2. golden  addiu $v1,$v1,5 / beqz $v1 / addiu $s1,$v1,-1     (in-place, then derive)
 *     ours    addiu $t8,$v1,5 / beqz $t8 / addiu $s1,$v1,4      (derive from the pre-add)
 *     We fold (x&7)+5-1 to (x&7)+4; golden does not.  Tried: one statement; `i = x & 7;`
 *     plus `i += 5;`; `while (i--)`; `while (i-- != 0)` (worse: sltu); `while (i) { i--; }`
 *     (worse, 1465).
 *
 *  3. golden  move $s0,$v0 / andi $t8,$s0,0xFF / move $s0,$t8   (3 instructions)
 *     ours    andi $s0,$v0,0xFF                                  (1)
 *     This is the ONLY length difference -- it is why every branch offset after it is 8
 *     bytes low.  Tried, all 710 or worse: `u8 ang = func_150ADA20();`;
 *     `s32 ang = (u8)func_150ADA20();`; `s32 rnd; u8 ang; rnd = f(); ang = rnd;` (current);
 *     `s32 ang = rnd & 0xFF;`; reusing `rnd` for the later `& 0x1F` random; moving the
 *     `ang = rnd` assignment after the `speed` statement (much worse, 1781); with and
 *     without the file-local `func_150ADA20 -> s32` prototype shadow (identical -- the
 *     shadow is NOT needed here, the 0xFF comes from the u8 local, so it was removed).
 *     MODEL REFUTED, and this is the useful part: the obvious explanation for golden's
 *     surviving `move $s0,$v0` is "the raw value is live across the func_150ADA68 call, so
 *     it must be parked in a callee-saved register first".  Writing exactly that (rnd = f();
 *     speed = <uses f68>; ang = rnd;) DOES stop the fold -- and simultaneously forces IDO to
 *     take a FIFTH callee-saved register: our build then uses $s0-$s4 and `addiu $s4,$sp,0xb0`
 *     where golden uses only $s0-$s3 and `addiu $s3,$sp,0xa8`.  Golden therefore does NOT
 *     hold the raw value across that call; its `move` survives inside a single basic block
 *     with the source's live range ending immediately.  That makes this a pure IDO
 *     copy-propagation tie, not a missing statement, a missing declaration or a wrong type.
 *
 * BAIL SIGNATURE: ~14 genuinely different honest spellings across the three clusters, score
 * pinned at exactly 710 for eight of them.  The permuter's only lever here would be a no-op
 * retyping cast, which is banned.
 *
 * ------------------------------------------------------------------------------------
 * WAVE 63: NINE MORE SPELLINGS MEASURED, CLUSTER 3 IS NOW A CLOSED QUESTION.  PARK IT.
 *
 * The cluster-3 cell table was completed.  functions.h declares `u8 func_150ADA20(void)` and
 * `f32 func_151423D8(u8)`; the two call-site `andi ...,0xFF` come free from that u8 PARAM, so
 * the only open question was ever the assignment.  All nine were built and scored with the
 * object deleted first; the shadow is the file-local `s32 func_150ADA20(void)` re-declaration:
 *     shadow  + `s32 ang; ang=f(); ang=(u8)ang;`                  1162
 *     shadow  + `u8  ang; ang=f();`                               1162
 *     shadow  + `s32 rnd,ang; rnd=f(); ang=(u8)rnd;`               710
 *     NO shdw + `s32 ang; ang=f();`                               1097
 *     NO shdw + `u8  ang; ang=f();`                               1162
 *     NO shdw + `s32 ang,rnd; rnd=f(); ang=(u8)rnd;`               710
 *     NO shdw + `s32 ang,rnd; ang=f(); ang=(u8)ang;`               710
 *     NO shdw + `u8  ang; s32 rnd; rnd=f(); ang=(u8)rnd;`          710
 *     NO shdw + `s32 ang,rnd; ang=f(); ang=ang & 0xFF;`            710
 *
 * NEW MEASURED FACT (the useful one): WITHOUT the shadow, `s32 ang = func_150ADA20();` emits
 * a BARE `move $s0,$v0` and NO mask at all -- IDO trusts the u8 return.  That is golden's
 * FIRST instruction, reproduced exactly.  But the moment any narrowing is added back, in any
 * spelling, IDO folds the pair into the single `andi $s0,$v0,0xFF` and the `move` disappears
 * again.  Every one of the five 710 spellings produces character-for-character the same
 * three-row residual:
 *     golden  move $s0,$v0 / andi $t8,$s0,0xFF / jal / move $s0,$t8
 *     ours                   andi $s0,$v0,0xFF / jal
 * So golden's shape is a `move` that IDO declined to copy-propagate into the following andi.
 * There is no C that both (a) narrows and (b) leaves that copy standing: narrowing is exactly
 * what triggers the propagation.  Combined with the earlier refutation of the "raw is live
 * across func_150ADA68" model (it does stop the fold, but costs a FIFTH callee-saved register
 * -- golden uses only $s0-$s3), cluster 3 is an IDO copy-propagation tie, not a spelling.
 *
 * TOTAL: 23 honest spellings, score never once below 710.  That is the documented bail
 * signature.  PARKED.  The pragma is restored and conker.us.yaml:1260 was never touched --
 * the [0x244C90, .rodata, game_EE710] migration remains correct and pre-scoped, but it must
 * NOT be applied while this function is still a #pragma.
 * ------------------------------------------------------------------------------------
 *
 * REPRODUCE: paste the body below over the #pragma in conker/src/game_EE710.c, then
 *   cd conker && ../tools/buildlock.sh bash -c 'make -s VERSION=us NON_MATCHING=1  *       PERMUTER=1 build/src/game_EE710.c.o && python3 ../tools/asm-differ/diff.py -o -R  *       func_150C1260 --max-lines 4096'
 */

#include <ultra64.h>
#include "functions.h"
#include "variables.h"

void func_15142314(s32, s32, f32 *);
extern void func_1514C2F0(f32 arg0, f32 arg1, f32 arg2, f32 arg3,
                          u8 arg4, s8 arg5, s16 arg6, u8 arg7,
                          s32 arg8, f32 arg9, s32 arg10, u8 arg11);
void func_15165F80(s32, s32, s32, s32, s32, s32, s32, s32, s32);
extern void *func_15132A4C(void *, s32, s32, s32, u8, s32);

typedef struct {
    char pad00[0x3B];
    u8 unk3B;
    char pad3C[0x14C - 0x3C];
    f32 unk14C;
    f32 unk150;
    char pad154[0x180 - 0x154];
    f32 unk180;
    char pad184[0x1D4 - 0x184];
    s32 unk1D4;
} Struct150C1260;

void func_150C1260(Struct150C1260 *arg0, u8 arg1) {
    f32 sp12C[3];
    s32 sp128;
    f32 mid;
    f32 mag;
    struct {
        f32 unk00;
        f32 unk04;
        f32 unk08;
        f32 unk0C;
        f32 unk10;
        f32 unk14;
        f32 unk18;
        f32 unk1C;
        f32 unk20;
        f32 unk24;
        f32 unk28;
        f32 unk2C;
        f32 unk30;
        f32 unk34;
        f32 unk38;
        f32 unk3C;
        f32 unk40;
        f32 unk44;
        f32 unk48;
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
        u8 pad69;
        u8 unk6A;
        u8 pad6B;
        void *unk6C;
        u8 unk70;
        u8 pad71;
        s16 unk72;
        s16 unk74;
        u8 pad76[2];
    } spA8;
    s32 i;
    void *ret;
    u8 ang;
    s32 rnd;
    f32 sn;
    f32 cs;
    f32 speed;
    f32 scale;

    mid = (arg0->unk14C + arg0->unk150) * 0.5f;
    if (arg0 == NULL) {
        return;
    }
    if (arg0->unk1D4 == 0) {
        return;
    }
    switch (arg1) {
    case 0:
        sp128 = 0xD;
        break;
    case 1:
        sp128 = 0x11;
        break;
    }
    func_15142314(arg0->unk1D4, sp128, sp12C);

    mag = mid * 80.0f;
    func_1514C2F0(sp12C[0], arg0->unk180, sp12C[2], mag, 0, 0x10, 0x10, 0, 0, mag * 4.0f, 0, 0xFF);
    func_15165F80(-1, (s32)sp12C[0], (s32)((s32)arg0->unk180 + 2.0f), (s32)sp12C[2], 0xB, 0x13, 0, 0xFF, 0);

    spA8.unk1C = 1.0f;
    spA8.unk20 = 1.0f;
    spA8.unk24 = 1.0f;
    spA8.unk04 = 0.4f;
    spA8.unk48 = 0.0f;
    spA8.unk4C = -0.9f;
    spA8.unk56 = 5;
    spA8.unk50 = 0x29E8;
    spA8.unk58 = 0;
    spA8.unk5C = 0;
    spA8.unk60 = 0xFF;
    spA8.unk61 = 1;
    spA8.unk62 = 0;
    spA8.unk63 = 0;
    spA8.unk64 = 0;
    spA8.unk65 = 0;
    spA8.unk66 = 0;
    spA8.unk67 = 0;
    spA8.unk68 = 0;
    spA8.unk6A = 1;
    spA8.unk6C = arg0;
    spA8.unk70 = arg0->unk3B;
    spA8.unk72 = 0x10;
    spA8.unk74 = 0xF;

    i = (func_150ADA20() & 7) + 5;
    while (i--) {
        rnd = func_150ADA20();
        ang = rnd;
        speed = (((func_150ADA68() * 0.9f) + 0.1f) * 18.0f) * mid;
        sn = func_151423D8(ang - 0x40);
        cs = func_151423D8(ang);
        spA8.unk54 = (func_150ADA20() & 0x1F) + 0xF;
        spA8.unk28 = (mag * sn) + sp12C[0];
        spA8.unk2C = arg0->unk180 + 2.0f;
        spA8.unk30 = (mag * cs) + sp12C[2];
        spA8.unk34 = speed * sn;
        spA8.unk38 = speed;
        spA8.unk3C = speed * cs;
        scale = (((func_150ADA68() * 0.9f) + 0.1f) * mid) * 2.23f;
        spA8.unk08 = scale;
        spA8.unk0C = scale;
        spA8.unk00 = scale;
        spA8.unk10 = func_150ADA68() * 360.0f;
        spA8.unk14 = func_150ADA68() * 360.0f;
        spA8.unk18 = func_150ADA68() * 360.0f;
        spA8.unk40 = 25.0f - (func_150ADA68() * 50.0f);
        spA8.unk44 = 25.0f - (func_150ADA68() * 50.0f);
        ret = func_15132A4C(&spA8, 3, 0xFF, 4, 0xFF, 0);
        if (ret != NULL) {
            *(f32 *)((u8 *)ret + 0x170) = arg0->unk180;
        }
    }
}
