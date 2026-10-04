/* tools/nearmiss/func_1518BD60.c -- game_1B8F40, jtbl block 24BED0 (near-miss, 163)
 *
 * STATUS: PARKED at mism=162, n=214/214 (EXACT LENGTH), frame EXACT (-0x120).
 * The decode below is complete and was measured; the candidate C is at the bottom of this
 * file. Splice it over the pragma in conker/src/game_1B8F40.c to reproduce.
 *
 * *** THE PARKED SCORE WENT 128 -> 162 ON PURPOSE. READ "REVISED 2026-08-25" NEAR THE ***
 * *** BOTTOM OF THIS HEADER BEFORE REACTING TO THAT NUMBER. The 128 was a structurally ***
 * *** IMPOSSIBLE local minimum; 162 is the honest baseline that can still reach 0.     ***
 *
 * WHY IT MATTERS: it jointly owns rodata block 24BED0 with func_1518BA90 (which is at
 * score 0, see tools/nearmiss/func_1518BA90.c). The jtbl migration
 *      - [0x24BED0, rodata]  ->  - [0x24BED0, .rodata, game_1B8F40]
 * needs the TU to re-emit the WHOLE block, and THIS function owns D_800A7440 (0.654f).
 * So nothing in game_1B8F40 can ship until this one matches. 214 words, 856 bytes.
 *
 * *** READ THE FAMILY FIRST -- THREE SIBLINGS ARE ALREADY MATCHED ***
 * This is a particle-emitter tick, the same shape as:
 *      game_17CAF0.c  func_15151A38, func_15152F70   <- MATCHED, carry the struct models
 *      game_175250.c  func_15148F1C                  <- MATCHED
 *      game_1B6DB0.c  (parked at 2010)               <- READ ITS NOTE BEFORE STARTING
 * The game_1B6DB0 note is the important one: that sibling is structurally exact and still
 * scores 2010, stuck on a uniform +1 integer temp-register rotation plus three delay slots.
 * Budget for that failure mode. Ours is much smaller (214 words vs its 0x148 frame), so the
 * rotation may not bite, but do not assume the family is easy. IT DID BITE -- see THE
 * RESIDUAL below; same class, one extra hoisted invariant instead of a rotation.
 *
 * The callee prototype is already known and correct -- game_17CAF0.c:336:
 *   extern s32 func_15147DA0(void *, void *, s32, s32, s32, s32, s32, s32, s32, s32, s32,
 *                            s32 *, s32, u8, s32);
 * and the RNG/trig helpers are in functions.h:
 *   u8  func_150ADA20(void);      // integer RNG
 *   f32 func_150ADA68(void);      // float RNG, 0..1
 *   f32 func_151423D8(u8);        // sin/cos of a byte angle
 *
 * ---------------------------------------------------------------- DECODE
 * PROLOGUE CONSTANTS (all loop-invariant, hoisted before the loop):
 *      s0 = arg0            s7 = 0x160600          s5 = &D_800BE9E4 (the global dt)
 *      f26 = 0.0f           f28 = D_800A7440 = 0.654f
 *      fp = 0x15 (21)       s6 = 0x17 (23)         s3 = 0 (loop counter)
 * D_800BE9E4 is the per-frame delta; it is 2 at runtime.
 *
 * LOOP: `s3` counts 0..1 -- the tail is `s3 = (s3 + 1) & 0xFF; while (s3 < 2)`, i.e. the
 * counter is a u8. Two emitters per object.
 *      s2     = (u8 *)arg0 + s3 * 4          // per-emitter slice
 *      timer  = *(s32 *)(s2 + 0x2C) - dt     // stored straight back to s2->unk2C
 *
 * FOUR GUARDS, each a `beql`/`bnel` straight to the loop tail (so: `continue`):
 *      arg0->unk24 == NULL                 -> continue
 *      *(void **)arg0->unk24 == NULL       -> continue   (word at offset 0)
 *      arg0->unk24->unk1D4 == 0            -> continue
 *      arg0->unk28 != arg0->unk24->unk3B   -> continue   (both lbu)
 * then `bgezl timer` skips the spawn block and lands at the position update (L1518C024).
 * So the spawn body is guarded by `if (timer < 0)`.
 *
 * SPAWN BODY (only when timer went negative):
 *      s4 = s3                                        // set in the first jal's delay slot
 *      s1 = func_150ADA20() % (arg0->unk22 + 1)       // lh, +1, divu/mfhi, `break 7` guard
 *      f22 = func_151423D8(s1 & 0xFF)
 *      f24 = func_151423D8((s1 - 0x40) & 0xFF)        // 0x40 = 90 degrees -> sin/cos pair
 *      f20 = func_150ADA68() * arg0->unk14 + arg0->unk10
 *      s2->unk2C = func_150ADA20() % 23 + 5           // re-arm the timer (s6 = 23)
 *
 * THE THREE STACK OBJECTS (offsets are exact; the siblings name these style/spawn/pos):
 *   style @ sp+0xB8, seven words then two bytes:
 *      +0x00 = 0      +0x04 = 1       +0x08 = 0x160600 (s7)   +0x0C = 3
 *      +0x10 = 0x10   +0x14 = 0x80    +0x18 = 0x20
 *      +0x1C (0xD4) = 0               +0x1D (0xD5) = 9
 *   spawn @ sp+0xDC:
 *      +0x00 = func_150ADA68() * arg0->unk1C + arg0->unk18
 *      +0x04 = f20 * f24              +0x08 = 0.0f (f26)
 *      +0x0C = f20 * f22              +0x10 = 0.654f (f28)
 *      +0x18 (0xF4) = arg0->unk2A | 8
 *      +0x19 (0xF5) = arg0->unk29
 *      +0x1A (0xF6) = 0xFF - ((arg0->unk24->unk184 >> 5) << 6)
 *      +0x1B (0xF7) = 0xFF
 *   pos @ sp+0xFC:
 *      +0x0C (0x108) = func_150ADA20() % 21 + 0x50     (s16; fp = 21)
 *      +0x0E (0x10A) = 1                               (s16)
 *      +0x10 (0x10C) = 1                               (s32)
 *      +0x15 (0x111) = func_150ADA20() % (arg0->unk20 + 1) + 3   (u8)
 *
 * THE CALL -- argument slots verified one by one against the matched sibling's call at
 * game_17CAF0.c:1297, which uses the identical prototype:
 *      func_15147DA0(&pos, &spawn, pos.unk15 * 12 + 8, 5,
 *                    1, 0, 2, 1, 0, 0, 0, (s32 *)&style, 0, arg0->unkC, arg0->unk1)
 * NOTE the third argument: golden computes `((a2 << 2) - a2) << 2` then `+ 8`, i.e.
 * a2 * 12 + 8, where a2 is the byte just written to pos.unk15 and RELOADED (`lbu 0x111(sp)`).
 * The reload is in golden -- do not "optimise" it by reusing the value.
 *
 * ON SUCCESS (return value non-zero):
 *      p = (u8 *)ret->unk98 + 0x48;
 *      *(void **)p = arg0;       *(u8 *)(p + 4) = s4;      // s4 is the emitter index
 *
 * POSITION UPDATE (runs on BOTH paths -- this is where `bgezl` lands):
 *      off = s3 * 6;                                    // sll/subu/sll: (i*4 - i) * 2
 *      s2->unk34 = (f32)*(s16 *)((u8 *)arg0->unk24 + 0x1AC + off);
 *      s2->unk3C = (f32)*(s16 *)((u8 *)arg0->unk24 + 0x1B0 + off);
 * arg0->unk24 is RELOADED between those two stores in golden (`lw $t4, 0x24($s0)`), so the
 * source reads it twice -- there is no TBAA across the intervening f32 store.
 *
 * ---------------------------------------------------------------- ORDER OF WORK
 * 1. The pos/spawn/style models are game_17CAF0.c's Local15152F70Pos / ...Spawn / ...Style
 *    (NOT the Local151539B4 family). spawn and style matched this function's offsets
 *    byte-for-byte on the first read; only Pos needed the size change discussed below.
 * 2. Frame first: golden is 0x120 with s0-s7+fp+ra and f20-f28 saved, f20..f28 at
 *    0x48..0x68, s0..s7 at 0x70..0x8C, fp 0x90, ra 0x94. Locals: style 0xB8, spawn 0xDC,
 *    pos 0xFC. Get those three offsets right before chasing any instruction.
 * 3. Then the guards, then the spawn body front-to-back. Never chase a late diff while an
 *    early one is open -- the first divergence cascades.
 * 4. Expect the family's known residuals last: temp-register rotation and IDO-filled delay
 *    slots. Read the game_1B6DB0.c note before spending time on those.

 * ---------------------------------------------------------------- MEASURED 2026-08-22
 * The decode above compiled FIRST TRY at n=214/214 -- EXACT INSTRUCTION COUNT. The whole
 * structure (loop, four guards, spawn block, 15-arg call, position update) is therefore
 * correct; what is left is frame and register allocation only.
 *
 *      d_v1      (Pos = 0x1C, the sibling's size)   mism=165  frame=-0x118  n=214/214
 *      d_posbig  (Pos = 0x24)                       mism=163  frame=-0x120  n=214/214  <-- parked
 *      d_toplocal(dead f64 declared above pos)      mism=163  frame=-0x120  n=214/214
 *
 * THE FRAME NEEDS 8 MORE BYTES THAN THE SIBLING'S STRUCT MODEL GIVES. Two routes reach
 * golden's 0x120 and they score IDENTICALLY, so the score cannot distinguish them:
 *   (a) this TU's Pos is 0x24, not the 0x1C used by game_17CAF0.c's Local15152F70Pos;
 *   (b) an 8-byte local sits ABOVE pos (declared first -- IDO lays locals out top-down in
 *       declaration order).
 * ROUTE (b) IS A DEAD LOCAL AND IS BANNED under the owner's unnamed-frame-bytes ruling --
 * it is recorded here only to show the ambiguity is real, not to be used. Route (a) is
 * parked because a struct whose declared size exceeds the fields THIS function writes is
 * ordinary (the caller may use the tail), but note it is still an INFERENCE: pos is the
 * topmost local, so sizeof(Pos) and "8 bytes above pos" are indistinguishable from the
 * frame alone. Resolve it by finding another user of this Pos type, not by scoring.
 *
 * NEXT: 163 rows with exact length and exact frame is register allocation and scheduling.
 * Work it front-to-back. Read the game_1B6DB0.c note first -- its sibling died at 2010 on a
 * uniform temp-register rotation, and that is the most likely wall here too.
 */

/*
 * ---------------------------------------------------------------- THE RESIDUAL, DIAGNOSED
 * 163 -> 162 and then a wall. THE CAUSE IS ONE EXTRA HOISTED LOOP-INVARIANT.
 *
 * Golden spends FOUR saved registers on loop invariants; we spend FIVE:
 *      golden:  $s5=&D_800BE9E4  $s6=23  $s7=0x160600  $fp=21     ($s3 = the counter)
 *      ours:    $s4=&D_800BE9E4  $s5=23  $s6=0x160600  $s7=21  $fp=255
 * We hoist the constant 255 into $fp; golden does NOT hoist it, it rematerialises it TWICE
 * inside the spawn block (`addiu $t2,$zero,0xFF` for the subtraction and `addiu $t4,$zero,0xFF`
 * for the store). That single extra invariant shifts every other saved register by one and
 * the shift cascades through all 214 instructions -- which is essentially the whole score.
 *
 * SIX SPELLINGS REFUTED (all n=214/214, frame exact; do not repeat):
 *      spawn.unk1A before spawn.unk1B .................. 162   <- parked, the best
 *      (u8) cast on the subtraction .................... 163
 *      subtrahend hoisted into a local ................. 163
 *      one side spelled 255, the other 0xFF ............ 163
 *      spawn.unk1B written first, before unk18 ......... 163
 *      -(shade + 1) instead of 0xFF - shade ............ 204  (n=215/214, WORSE)
 *
 * This is the cookbook's loop-invariant ranking tie: IDO ranks hoist candidates by
 * depth-weighted reference count, and 255 has two references in any honest spelling. There
 * is no source-level handle that removes one reference without changing the semantics --
 * and the obvious cheat (deriving one 0xFF from the other, e.g.
 * `spawn.unk1B = spawn.unk1A + shade;`) is a FORCER and is banned. Do not ship that.
 *
 * PERMUTER RUN, 2026-08-22 -- 43,573 iterations, frame-gated to 288. Result: 162 -> 128.
 *
 * *** THE PERMUTER'S OWN RANKING IS INVERTED IN-FILE. DO NOT TRUST output-<n> ORDER. ***
 * Re-scored with fastscore inside the real TU, its six outputs came out:
 *      permuter 1637 (its BEST)  ->  in-file 203, n=215/214   (WORSE than base, and long)
 *      permuter 2312            ->  in-file 120, n=214/214   (its 4th-ranked, actually best)
 *      permuter 3100            ->  in-file 199, n=216/214
 *      permuter 3188            ->  in-file 214, n=216/214
 *      permuter 3223            ->  in-file 161
 *      permuter 3226            ->  in-file 162
 * Its top-ranked candidate is one of the WORST in-file. Always re-score every output, not
 * just the best-named one -- taking the permuter's winner here would have been a regression.
 *
 * ITS 120 CONTAINS A FORCER, AND THE FORCER WAS REJECTED. The 2312 candidate makes exactly
 * two changes to the parked source, and they decompose cleanly:
 *      (1) HONEST -- hoist `(arg0->unk22 + 1)` into a named u32 local at the top of the loop
 *          body instead of computing it inside the `if (temp < 0)` guard.   162 -> 128
 *      (2) FORCER -- spell `x << 6` as `(x << 2) << 4`.                     162 -> 155
 *          Both together: 123. (The permuter's own 120 also reorders statements.)
 * (2) is semantically identical to what was already written and exists only to perturb
 * codegen -- the banned class. TAKEN: (1) only, parked below at 128. The 5 points that (2)
 * would add are not worth a fake match, and a future pass must not quietly reintroduce it.
 *
 * STILL OPEN at 128: the extra hoisted 255 described above. The permuter did not break it in
 * 43k iterations, which is evidence the saved-register assignment is not reachable by
 * source perturbation at all. If it resists again, this function may need the frame/offset
 * gates tightened (PERMUTER_TU_REQUIRE_OFFSETS=1) rather than more iterations.
 */

/*
 * ================================================================ REVISED 2026-08-25
 * TWO CORRECTIONS TO EVERYTHING ABOVE. The 128 was real but it is a DEAD END, and the
 * residual it is attributed to is not the residual any more.
 *
 * (1) "STILL OPEN at 128: the extra hoisted 255" IS STALE. At 128 the 255 hoist is ALREADY
 *     GONE. Measured on the full row list: rows idx21-idx26 put $s5=&D_800BE9E4,
 *     $s6=23, $s7=0x160600, $fp=21 -- ALL FOUR INVARIANTS EXACTLY WHERE GOLDEN PUTS THEM,
 *     with idx25/idx26 byte-identical to golden. The `lim` hoist killed the 255 as a side
 *     effect (it occupies the saved register the 255 was taking). Do not go hunting the
 *     255 from the 128 baseline; it is not there.
 *
 * (2) THE 128 CANNOT EVER REACH 0 -- IT IS STRUCTURALLY WRONG, NOT JUST MIS-COLOURED.
 *     Hoisting `lim = arg0->unk22 + 1` to the top of the loop body puts `lh $s4, 0x22($s0)`
 *     at row idx31. GOLDEN COMPUTES IT INSIDE THE SPAWN GUARD, at idx50 (`lh $t5, 0x22($s0)`
 *     / `addiu $t6, $t5, 1`, immediately after the first `jal func_150ADA20`). An
 *     instruction in the wrong position is not reachable by register colouring, so 128 is a
 *     LOCAL MINIMUM BELOW THE STRUCTURALLY CORRECT ONE. The permuter found it precisely
 *     because it optimises the score, and the score cannot see structure.
 *
 * THE PARKED C BELOW HAS THEREFORE BEEN REVERTED to computing the modulus inside the guard
 * (golden's structure), which measures 162. 162 IS THE HONEST BASELINE; work from it.
 *
 * ---------------------------------------------------------------- THE REAL RESIDUAL AT 162
 * Golden carries a TENTH saved value that we do not:
 *      1518BE20:  jal   func_150ADA20
 *      1518BE24:   or   $s4, $s3, $zero      <- delay slot: a COPY of the loop counter
 * and $s4 is then used exactly once, at `sb $s4, 0x4($v1)` (the emitter index written into
 * the spawned particle). $s3 is callee-saved and still live there, so the copy is redundant
 * -- yet golden keeps both. That tenth value is what leaves golden with room for only FOUR
 * hoisted invariants; we have nine values, spare capacity, and so IDO hoists the 255 too.
 * Our first `jal` gets a bare `nop` delay slot where golden schedules that move.
 *
 * *** THE COPY IS NOT REACHABLE FROM SOURCE. SIX MORE SPELLINGS REFUTED 2026-08-25, ***
 * *** all n=214/214, frame exact, ALL scoring exactly 162 -- IDO coalesces every one: ***
 *      u8  which = i;  at top of spawn block ................... 162
 *      s32 which = i;  at top of spawn block ................... 162
 *      u32 which = i;  at top of spawn block ................... 162
 *      s16 which = i;  at top of spawn block ................... 162
 *      s32 which = i;  at top of LOOP body ..................... 162
 *      counter retyped s32 with explicit `i = (i + 1) & 0xFF` ... 162
 * Widening, narrowing and same-width copies all coalesce identically. A redundant
 * register-to-register move CANNOT be conjured from C here, so "add a tenth value to crowd
 * out the hoist" is a closed line of attack -- do not re-run it.
 *
 * WHAT IS LEFT is a saved-register assignment tie, the class [[conker-permuter-setup]]
 * records as unreachable by source perturbation (43,573 frame-gated iterations from this
 * same baseline moved nothing but the `lim` hoist). Before spending another pass here, note
 * the cost/benefit: this function is the SOLE blocker on rodata block 24BED0, whose partner
 * func_1518BA90 already scores 0, so cracking it ships TWO functions and the block migration
 * `- [0x24BED0, rodata]` -> `- [0x24BED0, .rodata, game_1B8F40]`. Ownership is verified
 * clean: func_1518BA90 owns jtbl_800A7410 + D_800A7434/38/3C, func_1518BD60 owns D_800A7440,
 * nothing else references any of them, and the TU currently emits no .rodata at all.
 * ================================================================
 */

extern s32 D_800BE9E4;
extern s32 func_15147DA0(void *, void *, s32, s32, s32, s32, s32, s32, s32, s32, s32,
                         s32 *, s32, u8, s32);

struct H1518BD60 { s32 unk0; s32 unk4; s32 unk8; };

struct Pos1518BD60 {
    struct H1518BD60 unk0;
    s16 unkC;
    s16 unkE;
    s32 unk10;
    u8 pad14;
    u8 unk15;
    u8 pad16[2];
    s32 unk18;
    s32 unk1C;
    s32 unk20;
};

struct Spawn1518BD60 {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    u8 pad14[4];
    u8 unk18;
    u8 unk19;
    u8 unk1A;
    u8 unk1B;
};

struct Style1518BD60 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    u8 unk1C;
    u8 unk1D;
};

struct Rec1518BD60 { s16 unk0; s16 unk2; s16 unk4; };

struct Tgt1518BD60 {
    void *unk0;
    u8 pad4[0x37];
    u8 unk3B;
    u8 pad3C[0x148];
    s32 unk184;
    u8 pad188[0x24];
    struct Rec1518BD60 unk1AC[2];
    u8 pad1B8[0x1C];
    s32 unk1D4;
};

struct Emit1518BD60 {
    u8 pad0;
    u8 unk1;
    u8 pad2[0xA];
    u8 unkC;
    u8 padD[3];
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    s16 unk20;
    s16 unk22;
    struct Tgt1518BD60 *unk24;
    u8 unk28;
    u8 unk29;
    u8 unk2A;
    u8 pad2B;
    s32 unk2C[2];
    f32 unk34[2];
    f32 unk3C[2];
};

void func_1518BD60(struct Emit1518BD60 *arg0) {
    struct Pos1518BD60 pos;
    struct Spawn1518BD60 spawn;
    struct Style1518BD60 style;
    f32 temp_f20;
    f32 temp_f22;
    f32 temp_f24;
    s32 temp;
    s32 rnd;
    u8 i;

    i = 0;
    do {
        temp = arg0->unk2C[i] - D_800BE9E4;
        arg0->unk2C[i] = temp;
        if ((arg0->unk24 != NULL) && (arg0->unk24->unk0 != NULL) &&
            (arg0->unk24->unk1D4 != 0) && (arg0->unk28 == arg0->unk24->unk3B)) {
            if (temp < 0) {
                rnd = func_150ADA20() % (u32)(arg0->unk22 + 1);
                temp_f22 = func_151423D8(rnd & 0xFF);
                temp_f24 = func_151423D8((rnd - 0x40) & 0xFF);
                temp_f20 = (func_150ADA68() * arg0->unk14) + arg0->unk10;
                arg0->unk2C[i] = (func_150ADA20() % 23U) + 5;
                style.unk0 = 0;
                style.unk4 = 1;
                style.unk8 = 0x160600;
                style.unkC = 3;
                style.unk10 = 0x10;
                style.unk14 = 0x80;
                style.unk18 = 0x20;
                style.unk1C = 0;
                style.unk1D = 9;
                pos.unk15 = (func_150ADA20() % (u32)(arg0->unk20 + 1)) + 3;
                pos.unk10 = 1;
                pos.unkE = 1;
                pos.unkC = (func_150ADA20() % 21U) + 0x50;
                spawn.unk19 = arg0->unk29;
                spawn.unk0 = (func_150ADA68() * arg0->unk1C) + arg0->unk18;
                spawn.unk8 = 0.0f;
                spawn.unk10 = 0.654f;
                spawn.unk4 = temp_f20 * temp_f24;
                spawn.unkC = temp_f20 * temp_f22;
                spawn.unk18 = arg0->unk2A | 8;
                spawn.unk1A = 0xFF - ((arg0->unk24->unk184 >> 5) << 6);
                spawn.unk1B = 0xFF;
                temp = func_15147DA0(&pos, &spawn, (pos.unk15 * 12) + 8, 5, 1, 0, 2, 1, 0,
                                     0, 0, (s32 *)&style, 0, arg0->unkC, arg0->unk1);
                if (temp != 0) {
                    u8 *p = (u8 *)*(s32 *)(temp + 0x98) + 0x48;
                    *(struct Emit1518BD60 **)p = arg0;
                    *(u8 *)(p + 4) = i;
                }
            }
            arg0->unk34[i] = (f32)arg0->unk24->unk1AC[i].unk0;
            arg0->unk3C[i] = (f32)arg0->unk24->unk1AC[i].unk4;
        }
        i++;
    } while (i < 2);
}
