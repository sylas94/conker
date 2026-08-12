/* func_150D4D58 -- game_100810.c -- 972 bytes / 243 insns / frame 0x108
 * STATUS: best 1205 (1345 at the start of this wave, 3498 the wave before, 7399 first draft).
 * NOT a match.  Live C is parked here; the repo file has the #pragma restored.
 *
 * ===================== WAVE 2026-08-12: 1345 -> 1205 ================================
 * ONE edit, and it is a TYPE lever, not an order lever:
 *     params.unkA = func_150ADA20() % 18U + 27;            <- 1345
 *     params.unkA = (s16) (func_150ADA20() % 18U) + 27;    <- 1205
 * Semantically identical (the modulus is 0..17, unkA is s16, so the narrowing cannot
 * change a bit) and it is instruction-count-neutral: 243 insns both ways, and the
 * params-area byte-store sequence is still golden's EXACTLY.  What it buys is the whole
 * three-instruction group, registers included:
 *     GOLD  mfhi t8 / addiu t7,t8,0x1b / sh t7,0xa2(sp)
 *     MINE  mfhi t8 / addiu t7,t8,0x1b / sh t7,0xa2(sp)    (was mfhi t5 / addiu t7,t5)
 * The narrowing creates the extra temp web golden spends there.  The cast type is
 * load-bearing and UNIQUE -- this is not "any cast will do":
 *     (s16) 1205   (u16) 1340   (s32) 1345 (inert)   (s8) 1410   (u8) 1440
 *     (s16) applied OUTSIDE the +27 instead: 1345 (inert)
 * Discovered by the permuter (which proposed the cruder statement split
 * `unkA = ...%18U; unkA = unkA + 27;`, 1215) and then reduced to the cast, 10 better.
 * The same cast on the OTHER two loop expressions is worth nothing or negative:
 *     unk1B: (u8) 1320  (u16) 1320  (s16) 1325  (s32) 1205 (inert)
 *     unk1D: (u8)/(s32) 1205 (inert);  splitting unk1B into two statements: 1345
 * REFUSED this wave: moving params.unk1E after params.unk61 scores 1315 but emits
 * `1c 20 61 1e` where golden has `1c 1e 20 61` -- same class as the 1312 refused last
 * wave.  Moving params.unk66 between the two angleBase statements (the permuter's
 * top-ranked candidate on ITS scale) scores 2336 on asm-differ AND breaks the store
 * order to `1e 61 20`.  NOTE: the permuter's internal score is NOT comparable to
 * asm-differ here -- its "1280" is asm-differ 2336.  Re-score every candidate.
 * ====================================================================================
 *
 * WHAT IT IS: a particle burst emitter.  It fills a 0x70-byte spawn-parameter struct and
 * calls func_15130280 (the particle spawner) rand%11+10 times, each time re-randomising
 * colour (D_800A09C0[rand&3]), lifetime, size, launch direction (func_15143794 turns an
 * s16 yaw/pitch pair + speed into a velocity vector) and two random render flags.
 *
 * ================= FRAME DECODE (golden .s, framesize 0x108 = 264) ==================
 *   0x00..0x17  arg build, 6 words (func_15130280 takes 6 args; slots 0x10/0x14 used)
 *   0x18..0x1F  pad to 8 for the sdc1 block
 *   0x20..0x4F  sdc1 $f20,$f22,$f24,$f26,$f28,$f30
 *   0x50..0x77  sw  $s0..$s7,$fp,$ra                      -> saved area ends at 0x78
 *   0x78..0x97  32 bytes: compiler TEMP area + declared-auto homes
 *   0x98..0x107 `params`, 0x70 bytes, ENDING EXACTLY AT FRAMESIZE
 *               => params is the FIRST-DECLARED local (first declared = highest address)
 *   0x114       $a3 home (caller's arg slot); read back as `lbu 0x117(sp)` => arg3 is u8
 *   0x118       5th parameter (arg4)
 *
 * *** THE FRAME IS NOW GOLDEN'S.  SOLVED THIS WAVE. ***
 * 0x78..0x97 is NEVER REFERENCED in either object -- no sp displacement in golden or in
 * my build falls between 0x78 and 0x97.  So every one of those 32 bytes is a declared-auto
 * HOME that never spills, and the reading is arithmetic, not a search:
 *     framesize = roundup8(base + temp + sum(sizeof(local))),  base = 0x78 = 120
 *     mine with 7 scalars: roundup8(120 + T + 112 + 28) = 0x110  =>  T in [5,12]
 *     +1 dummy 0x110, +2 0x118, +3 0x118, +4 0x120 (measured)    =>  T in [5,8]
 *     golden 0x108 at the same T  =>  Ng in {5,6}
 * i.e. GOLDEN DECLARES SIX SCALARS AND I DECLARED SEVEN.  The one to drop is `speed`:
 * golden puts arg2 in $f20 (`mtc1 a2,$f20`) for the angleBase multiply and then REUSES
 * $f20 for the per-iteration speed (`add.s $f20,$f16,$f24`), which is exactly what
 * assigning to the parameter looks like.
 *
 * *** CORRECTION TO THE PREVIOUS WAVE'S LOG ***  It recorded "reassigning the parameter
 * arg2 instead of declaring speed: byte-identical output and identical frame -- a
 * WRITTEN-TO parameter gets a home in the local area too".  That is WRONG, measured twice
 * this wave: `arg2 = ...` in place of `speed = ...` sheds exactly 4 bytes of frame
 * (0x110 -> 0x108, every sp displacement then equal to golden's) and 326 points
 * (3498 -> 3172).  A written-to REGISTER parameter is homed in the CALLER's argument slot
 * (that is what golden's `sw a3,276(sp)` is), not in the callee's locals area, so it costs
 * no home.  Do not re-derive the old claim.
 * ====================================================================================
 */

/* ---- declarations added to game_100810.c ------------------------------------- */

typedef struct {                 /* == Struct15131EE4Local, src/game_15D730.c (matched) */
    s32 unk0;  s32 unk4;  s16 unk8;  s16 unkA;  s32 unkC; s32 unk10;
    u8 unk14; u8 unk15; u8 unk16; u8 unk17; u8 unk18; u8 unk19; u8 unk1A;
    u8 unk1B; u8 unk1C; u8 unk1D;
    s16 unk1E; s16 unk20; s16 unk22;
    f32 unk24; f32 unk28; f32 unk2C;
    struct17 unk30; struct17 unk3C; struct17 unk48;
    f32 unk54; s32 unk58; s32 unk5C;
    u8 unk60; u8 unk61; s8 unk62; s8 unk63; s8 unk64; u8 unk65; u8 unk66;
    u8 pad67[9];
} Struct150D4D58;
/* unk62 is s8, NOT the u8 the in-tree Struct15131EE4Local declares.  Golden materialises
 * the stored constant as `li t3,-1`; a u8 field turns `= -1` into `li 255`, which is what
 * I emitted before the fix.  The in-tree type is not evidence here: its only live writer
 * (func_15131EE4, src/game_15D730.c) does `sp40.unk62 = 0x27`, a positive constant that
 * compiles identically for u8 and s8, so it never constrained the signedness.  Corrected
 * file-locally rather than in the shared header, per the usual header-inaccuracy pattern.
 * Worth 0 points on its own (the row is still register-mismatched) but it makes the
 * OPCODE match, so it will matter once the $t rotation lands. */

extern f32 D_800A5480;
extern f32 D_800A0A18;
extern f32 D_800A0A1C;
extern f32 D_800A0A20;
extern f32 D_800A0A24;
extern f32 D_800A0A28;
extern void func_15143794(s32, s32, f32, f32 *);
extern void *func_15130280(void *, u8, s32, s32, u8, s32);

/* ---- body (score 1205, frame 0x108 = golden, 243 insns = golden) -------------- */

void func_150D4D58(struct17 *arg0, struct17 *arg1, f32 arg2, u8 arg3, s32 arg4) {
    Struct150D4D58 params;
    s32 count;
    s32 angleBase;
    f32 spread;
    f32 base;
    s32 r1;
    s32 r2;

    count = func_150ADA20() % 11U + 10;
    params.unk8 = 0x2203;
    params.unk0 = 0x200005;
    params.unk4 = 0;
    params.unkC = 0;
    params.unk10 = 0;
    params.unk14 = 0xFF;
    params.unk15 = 0xFF;
    params.unk16 = 0xFF;
    params.unk17 = 0xFF;
    params.unk18 = 0xFF;
    params.unk19 = 0xFF;
    params.unk1A = 0xFF;
    params.unk1C = 0xFF;
    params.unk30 = *arg0;
    params.unk3C = *(struct17 *)&D_800A5480;
    params.unk1E = 10;
    params.unk20 = 25;
    params.unk61 = 7;
    params.unk62 = -1;
    params.unk22 = 1;
    params.unk24 = 1.0f;
    params.unk58 = 0x4C207;
    params.unk60 = 0;
    params.unk63 = -1;
    params.unk64 = -1;
    params.unk65 = 0;
    params.unk5C = 0;
    params.unk66 = 0xFF;
    angleBase = (s16) (arg2 * D_800A0A18);
    angleBase = (s16) ((angleBase >> 8) + 0x40);
    spread = D_800A0A20;
    base = D_800A0A1C;

    do {
        arg2 = func_150ADA68() * spread + base;
        params.unk1D = D_800A09C0[func_150ADA20() & 3];
        params.unkA = (s16) (func_150ADA20() % 18U) + 27;
        params.unk1B = func_150ADA20() % 156U + 100;
        params.unk28 = params.unk2C = func_150ADA68() * 233.0f + 199.0f;
        r1 = func_150ADA20();
        r2 = func_150ADA20();
        func_15143794((s16) (r1 % 130U + angleBase), (s16) (r2 % 81U - 64),
                      func_150ADA68() * 10.0f + 5.0f, &params.unk48.unk0);
        params.unk48.unk0 = params.unk48.unk0 - arg1->unk0 * arg2;
        params.unk48.unk8 = params.unk48.unk8 - arg1->unk8 * arg2;
        params.unk54 = func_150ADA68() * D_800A0A24 + D_800A0A28;
        params.unk58 &= ~0xC0;
        if (func_150ADA20() & 1) {
            r1 = 0x80;
        } else {
            r1 = 0;
        }
        if (func_150ADA20() & 1) {
            r2 = 0x40;
        } else {
            r2 = 0;
        }
        params.unk58 = params.unk58 | (r2 | r1);
        func_15130280(&params, 1, 0, 0, arg3, arg4);
        count -= 1;
    } while (count > 0);
}

/* ================================ MEASURED LOG ================================
 * Every number is the REAL asm-differ (`-o func_150D4D58 -R --max-lines 4096`) on an
 * object built with the repo's exact pipeline; -R and no-R agreed on every single
 * measurement in this file.  The function is BOUNDED (readelf size 972 == byte count).
 *
 * ---- earlier waves (unchanged, still true) ----
 *  1. first honest draft, 8 scalars                            7399   frame 0x110
 *  2. merge r1/flagA and r2/flagB -> 6 scalars                 7037   frame 0x108
 *  3. HOIST `spread`/`base` out of the loop                    4434
 *     The big structural lever.  Golden pre-loads BOTH globals into callee-saved
 *     $f22/$f24; a source that reads them inside the loop cannot, because the loop is
 *     full of calls -- IDO then hoists only the ADDRESSES into $s6/$s7 and reloads each
 *     iteration.  Freeing $s7/$fp is what lets golden hoist the divisors 18 and 156 into
 *     registers, producing its two `bnez $s7 / break 7` divide guards.
 *     It also explains why golden hoists 233.0f/199.0f/10.0f but NOT 5.0f: with the two
 *     globals in f22/f24 only three callee-saved FP registers are left.
 *  4. + integer-store source order read off golden's store order                   3928
 *  5. + `r1 = func_150ADA20(); r2 = func_150ADA20();` as statements                3548
 *  6. + reuse r1/r2 for the two render flags                                       3498
 *
 * ---- THIS WAVE: 3498 -> 1345, and the frame is now golden's ----
 *  7. `speed` deleted; the loop assigns the PARAMETER `arg2` instead      3172  [0x108]
 *     -> 6 declared scalars.  Every sp displacement is now golden's.  See the frame
 *        decode above and the correction it contains.
 *     Declaration ORDER of the six survivors is completely unobservable here: all six
 *     permutations tried scored 3172 byte-for-byte.  That follows from the frame reading
 *     -- no home is ever referenced, so where each home sits cannot show up in the code.
 *  8. `params.unk62` u8 -> s8                                            3172  (0 points,
 *     but it converts my `li 255` into golden's `li -1`; see the typedef comment)
 *  9. the angleBase pair moved to the END of the setup block, immediately
 *     before `spread`/`base`                                             1353  [0x108]
 *     Found by an every-unit-to-every-position sweep of the 25-unit setup block.
 *     This is the INDEPENDENT-STATEMENT-ORDER lever and it paid 1819 points.
 * 10. `params.unk2C = params.unk28 = X;` -> `params.unk28 = params.unk2C = X;`
 *                                                                        1345  [0x108]
 *     Golden stores unk28 (0x28) then unk2C (0x2C); I had them the other way round.
 *     Semantically identical (both fields end up holding X, both f32).
 *
 * ---- REFUSED this wave ----
 *   moving `params.unk61 = 7;` above `params.unk20 = 25;` scores 1312 (33 points better
 *   than 1345) -- and it is REFUSED, because it BREAKS the one thing this block states
 *   unambiguously.  Golden's byte-store sequence is
 *       ... 1c 1e 20 61 62 22 58 60 63 64 65 5c 66 ...
 *   and the 1312 variant emits
 *       ... 1c 1e 61 20 62 22 58 60 63 64 65 5c 66 ...
 *   The 33 points are $t-rotation noise bought by making the code demonstrably LESS like
 *   golden.  The parked 1345 reproduces golden's store sequence exactly, byte for byte.
 *   (Verified by extracting every sb/sh/sw to the params area from both objects.)
 *   The same applies to its neighbours 1320/1323/1327, which move the same stores.
 *
 * ---- NEGATIVES (measured; frame in brackets) ----
 *   EXHAUSTIVE single-unit-move sweep of the setup block, every one of the 25 units to
 *     every one of the 25 positions (625 builds): nothing beat 1353 except the refused
 *     store-order-breaking moves.
 *   splitting the two `angleBase` statements so each moves independently (48 builds):
 *     flat at 1353; they want to be adjacent and last.
 *   `params.unk24 = 1.0f;` to every position (23 builds): flat at 1353 except one spot at
 *     3038 -- unk24's float store floats freely, so its position carries no information.
 *   `spread`/`base` order swapped, and the pair moved to every earlier position:
 *     nothing better than 1353; moving the pair to the very top costs an instruction.
 *   `params.unk28 = X; params.unk2C = params.unk28;` (two statements)   1353, no gain.
 *   dummy-scalar frame calibration: +1 -> 0x110, +2 -> 0x118, +3 -> 0x118, +4 -> 0x120,
 *     i.e. exactly roundup8(base + T + sum) with a step of 8 per two scalars.
 *   older ablation probes for the reserved temp area (deliberately WRONG code, run only
 *   to read the frame) -- these still stand and are why T is 5..8 and not 0:
 *     delete `params.unk3C = ...`   4877 [0x110]   delete `params.unk30 = *arg0;` 6418 [0x110]
 *     delete both                  10163 [0x110]   delete the func_15143794 call  8156 [0x100]
 *     delete the func_15130280 call 5758 [0x108]  (argbuild 24->16)
 *   `(f32 *)&params.unk48` instead of `&params.unk48.unk0`: byte-identical.
 *
 * ---- CALLEE SIGNATURES, re-verified against golden's argument registers ----
 *   func_150ADA20()  -> s32 in $v0, no args.  Used 9x; every use is `divu`/`andi` on $v0.
 *   func_150ADA68()  -> f32 in $f0, no args.  Used 4x; every use is `mul.s` on $f0.
 *   func_15143794(s32 a0, s32 a1, f32 a2, f32 *a3)
 *       golden sets a0/a1 by `sll/sra 0x10` pairs (both s16-narrowed s32), a2 in $f14
 *       (3rd arg, FP), a3 = `addiu a3,sp,224` = &params.unk48 (0x98+0x48=0xE0=224).  OK.
 *   func_15130280(void *a0, u8 a1, s32 a2, s32 a3, u8 stack0x10, s32 stack0x14)
 *       golden: a0 = `addiu a0,sp,152` (&params), `li a1,1`, a2/a3 = zero,
 *       `lbu t0,279(sp)` -> `sw t0,16(sp)` (arg3, u8, from its caller-slot home 0x117),
 *       and s5 = `lw s5,280(sp)` -> `sw s5,20(sp)` (arg4, s32, from 0x118).  OK -- and
 *       this one is cross-checked against the LIVE MATCHED definition in src/game_15D730.c.
 *   All four signatures are confirmed; none is a remaining risk.
 *
 * ---- NEGATIVES measured 2026-08-12 at the 1205 base (~1700 builds this wave) ----
 *   EXHAUSTIVE single-unit-move sweep RE-RUN at the new base, all 32 units to all 32
 *     positions (992 builds).  Only FOUR beat 1205 and all four break golden's byte-store
 *     sequence, i.e. they are the same refused class as last wave's 1312:
 *       unk20 <-> unk61 swap            1172   emits ... 1c 1e 61 20 62 ...  (golden 1e 20 61 62)
 *       unk1E moved after unk61         1175   emits ... 1c 20 61 1e 62 ...
 *       unk62 moved before unk61        1179   emits ... 1c 1e 62 20 61 ...
 *     Everything else is >= 1205; 14 further orderings are exactly 1205 (inert).
 *   EXHAUSTIVE split-angleBase placement: the two angleBase statements placed INDEPENDENTLY
 *     at every (p,q) with p<=q over the 31-unit backbone (528 builds).  Best is the base
 *     itself (adjacent, last, 1205); the next family is 1482.  The pair genuinely wants to
 *     be adjacent and last.  This closes the axis the permuter kept proposing.
 *   CAST SWEEP over every other expression site x {s16,u16,s32} / {f32,f64} (26 builds):
 *     count, unk1B, unk54, unk28/2C, both angleBase halves, unk48.unk0/unk8, arg2, the
 *     r2|r1 or -- ALL exactly 1205 (inert) or worse.  The unkA site is the ONLY one.
 *   DECLARATION-TYPE sweep: all 15 s32/s16 assignments over {count,angleBase,r1,r2} that
 *     keep the frame at 0x108 (an f32 local costs 8 home bytes, an s32 4, and 0x108 only
 *     pins sum(homes)=32) -- every one is WORSE, 1505..2320.  angleBase as u16/u8: 3318.
 *     All four locals are confirmed s32 by measurement, not just by the frame arithmetic.
 *
 * ---- THE PREHEADER ORDERING (a) IS NOT REACHABLE FROM STATEMENT PLACEMENT ----
 * Proven this wave, and worth not re-deriving.  Every `lui at,X` in the preheader writes
 * the SAME register $at, so the scheduler cannot reorder them: the $at chain is a direct
 * readout of IDO's PRE-SCHEDULING order.  Measured:
 *     GOLDEN  1.0f, D_800A0A18, 10.0f, 199.0f, 233.0f, D_800A0A1C, D_800A0A20
 *     MINE    1.0f, D_800A0A18, D_800A0A20, D_800A0A1C, 10.0f, 199.0f, 233.0f
 * and the chain follows SOURCE ORDER exactly (verified by moving the pair to the top:
 * chain moves with it, 3237; by swapping the two: chain swaps, 1635; by moving the 1.0f
 * store to the end: chain follows, 2497).  The LICM-hoisted group is ALWAYS appended after
 * every source statement of the preheader, in DESCENDING allocated-register order
 * (f30,f28,f26 = reverse of first use in the loop), then the integer hoists (s6,s5,s8,s7).
 * Golden's group is the same but with f24 and f22 INSIDE it -- so in golden those two loads
 * are LICM hoists, not preheader source statements.  IDO will not hoist a global LOAD out
 * of a call-containing loop; it hoists only the ADDRESS into $s6/$s7 and reloads per
 * iteration.  Measured three ways, all 4989-6000 and all with `lwc1 $f16,0(s6)` in the loop:
 *     globals inlined in the loop expression                     6000  [frame 0xf8]
 *     same + `extern const f32` on both globals                  6000  BYTE-IDENTICAL to
 *         the non-const build -- IDO ignores `const` for aliasing entirely
 *     globals as separate assignment statements at the loop top  4989  [frame 0x108]
 * So (a) needs a mechanism that puts a preheader source statement AFTER the LICM group, and
 * no source-level handle for that exists.  Do not spend another wave on statement order
 * here; the remaining $t transpositions (7<->1 and -1<->0x4C207, plus the D_800A09C0 index
 * chain) are downstream of it.
 *
 * ---- RESIDUAL at 1345 (superseded, kept for the row map): 174 of 243 rows identical ----
 *   (a) rows ~74-114, the setup block: golden materialises the three FP LITERALS
 *       (10.0f -> f30, 199.0f -> f28, 233.0f -> f26) BEFORE loading the two globals
 *       (D_800A0A1C -> f24, then D_800A0A20 -> f22), and interleaves all five with the
 *       integer stores.  Mine loads the two globals first and then the literals.  The
 *       literals come from inside the loop and the globals from the two statements just
 *       above it, so plain statement order cannot reach it -- 625 single moves say so.
 *   (b) everything from row 118 down is a pure $t-rotation renaming (same opcodes, same
 *       stack offsets, same order) that should collapse the moment (a) lands.
 *   (c) rows 169-173: the two `sll/sra 0x10` sign-extension pairs for the func_15143794
 *       arguments are emitted in the opposite interleave.
 * NEXT: (a).  What makes IDO emit a loop-invariant CONSTANT before a loop-invariant
 * GLOBAL LOAD?  Ideas not yet tried: a different spelling of the two global reads that
 * delays their address materialisation, and the permuter seeded here -- the base is now
 * strong (correct frame, correct instruction count, correct store order) which is exactly
 * the condition under which the permuter has paid before.
 * ============================================================================== */
