/* ============================== CLOSED -- MATCHED ==============================
 * func_1508114C  (game_AE1D0.c, 1064 bytes, frame 0xE0)
 *
 * SCORE 0, with -R and without.  Bounded: readelf -sW on BOTH objects -> 1064.
 * Whole-object section compare (build/src/game_AE1D0.c.o vs expected/):
 *     .text IDENTICAL (2416 bytes)   .rodata IDENTICAL (0)   .data IDENTICAL (0)
 * -- i.e. every function in the TU, not just this one, is byte-for-byte golden.
 * The live definition is in conker/src/game_AE1D0.c and the #pragma GLOBAL_ASM is GONE.
 * This file is now a record of HOW it closed; the authoritative copy is the TU.
 *
 * ------------------------- WHAT CLOSED IT (wave 2026-08-12) -------------------------
 * The whole residual at 60 was ONE displaced instruction: golden puts the reload
 * `lw s0,0xd8(sp)` (p = spheres) in the compiler-generated LOOP PREHEADER, after the
 * zero-trip guard, while the `for` shape emits it before the guard:
 *     golden  5b0: blez t5,740 / 5b4: move s1,zero (delay) / 5b8: lw s0,0xd8(sp)
 *     for     5b0: lw s0,0xd8(sp) / 5b4: blez t5,740 / 5b8: move s1,zero (delay)
 * The previous wave had established that the guarded-do-while shape fixes the placement
 * but "costs a 3-cycle rotation of the saved registers s5/s6/s7, 105".  THAT TRADE IS NOT
 * REAL.  It was an artefact of how that wave spelled the loop-continuation, not of the
 * loop shape.  The winning shape is:
 *
 *     bestPart = -1;
 *     i = 0;                       <-- OUTSIDE the guard  (lands in the blez delay slot)
 *     if (count > 0) {
 *         p = spheres;             <-- INSIDE the guard   (this is the preheader block)
 *         do {
 *             if (((1 << p->bone) & obj->unk9C) != 0) {
 *                 goto next;       <-- `continue` is WRONG in a do-while: it would skip
 *             }                        the increments and hang.  The goto is the honest
 *             ... body ...             spelling of the for-loop's `continue`.
 *         next:
 *             i++;
 *             p++;
 *         } while (i != count);
 *     }
 *
 * TWO THINGS ARE LOAD-BEARING, each isolated by measurement:
 *
 *  (1) THE ASYMMETRIC INIT PLACEMENT.  `i = 0` before the guard, `p = spheres` after it.
 *      This is the entire point: the guard's delay slot is filled from the block BEFORE
 *      it (so `i = 0` must be there) and the preheader is the block AFTER it (so
 *      `p = spheres` must be there).  All three alternatives were built and scored:
 *          i and p BOTH inside the if   ... 65
 *          i and p BOTH before the if   ... 60   (identical to the old `for` shape)
 *          p before the if, i inside     ... 60
 *          i before, p inside            ....  0  <-- unique
 *      So the asymmetry is not a stylistic choice; it is what the binary states.
 *
 *  (2) THE `goto next` SKIP EDGE.  Restructuring the skip as a positive nest
 *      (`if ((mask & obj->unk9C) == 0) { ...body... } i++; p++;`) -- semantically
 *      identical, no goto -- scores 95.  Golden's `bnel $t1,$zero,.L15081450` is a branch
 *      straight to the increment block, i.e. a real continuation edge, and the nested
 *      form does not produce it.
 *
 * WHY THE PREVIOUS WAVE MEASURED 105 FOR "the same shape": it cannot have had this
 * continuation edge (a literal `continue` inside a do-while does not increment, so that
 * wave must have spelled the skip some other way).  The saved-register rotation it
 * recorded -- golden s7=outDist/s5=&near/s6=&far becoming s5/s6/s7 -- does NOT happen
 * with the goto form.  Placement and register ranking never actually traded against each
 * other; the reference counts of {outDist, &near, &far} are unchanged by the loop shape,
 * exactly as the web-refcount law predicts, and the ranking follows loop-weighted counts
 * (&near and &far take 4 in-loop refs each -- one argument pass plus the three loads of
 * the `bestNear = near` / `bestFar = far` struct copies -- against outDist's 3, so
 * s5=&near, s6=&far, s7=outDist).
 *
 * ------------------------- THE TWO EARLIER LEVERS (still load-bearing) ---------------
 *  (a) `mtx` -- read obj->unk1D4 into a local BEFORE the three `local.unkN` stores.
 *      `local`'s address is taken (passed to func_15143134), so those stores are alias
 *      barriers the scheduler will not hoist a load across.  Golden's `lw v0,0x1d4(s2)`
 *      sits at the TOP of the loop body, 20 instructions before its use, which is only
 *      reachable if the read is a separate statement generated before the stores.  Left
 *      inline in the call argument, the load pins next to the jal, the mtc1->cvt.s.w
 *      delay cannot be filled, and IDO emits a nop (that nop was the old 1068-vs-1064).
 *  (b) `(s32)mtx` -- the cast AT THE POINT OF USE, with `mtx` declared `u8 *`.  Golden is
 *      `addu a2,v0,t7` (base first).  For `<variable> + <temp>` IDO canonicalises the TEMP
 *      first however the source is written; for `<temp> + <temp>` it keeps source order.
 *      A cast node makes the variable a temp, restoring golden's operand order.
 *
 * ------------------------- FRAME DECODE (confirmed to the byte) ----------------------
 *   frame 0xE0.  arg build 0x00..0x27, saved regs 0x28..0x57 (f20 + s0-s7,fp,ra),
 *   compiler TEMP 0x58..0x5C (4 bytes), home area 0x5C..0xE0 = 0x84 = 132 bytes
 *   = 12 scalars (48) + 7 struct17 (84), top-down in declaration order:
 *     0xDC idx   0xD8 spheres  0xD4 count  0xD0 type  0xCC bestIndex  0xC8 tNear  0xC4 tFar
 *     0xC0 i  |  0xB4 centre  0xA8 bestCentre  0x9C near  0x90 far  0x84 local  0x78 bestNear
 *     0x6C bestFar  |  0x68 bestPart  0x64 p  0x60 mtx  0x5C radius
 *   The four scalars BELOW the structs never touch their homes, so their ORDER is free but
 *   their COUNT is not.  Positive evidence that `radius` is a real local and not filler:
 *   inlining it (10 scalars + index cursor, frame back to 0xE0) rotates the entire FP
 *   register assignment -- f0/f4/f6/f8/f10/f16/f18 all shift -- and scores 485.
 *
 * ------------------------- ORIGINAL-GAME BUG, reproduced --------------------------
 * After the loop the code does
 *     if (*outDist == -1.0f) return 0;
 *     *outDist = tNear;
 * which overwrites the tracked best distance with the LAST call's near-t rather than the
 * best one.  Golden (0x15081460..0x15081484) does exactly this.  Do not "fix" it.
 *
 * ------------------------- MEASURED NEGATIVES (kept for the record) ----------------
 * Every number is the real asm-differ, pragma removed, object asserted to exist.
 *   THIS WAVE, around the winning shape:
 *   - goto-free positive nest of the bone-mask test ............................. 95
 *   - `i = 0; p = spheres;` both inside the guard ............................... 65
 *   - `i = 0; p = spheres;` both before the guard ............................... 60
 *   - `p = spheres;` before the guard, `i = 0;` inside .......................... 60
 *   PREVIOUS WAVES, from the `for`-shape base (all still true of that shape):
 *   - `for (i = 0, p = spheres; ...)` ........................................... 960/60-class
 *       (only swaps WHICH init lands in the blez delay slot -- same cost, other row)
 *   - `p = spheres;` placed BEFORE `bestPart = -1;` ............................. 75
 *   - mtx as `s32` with `mtx + (p->bone << 6)` .................................. 70
 *   - mtx as `s32` with `(p->bone << 6) + mtx` .................................. 70
 *   - mtx as `u8 *` with `mtx + (p->bone << 6)` (no cast) ....................... 70
 *   - mtx as `s32` with `mtx += p->bone << 6;` then passing mtx ................. 70
 *   - mtx as `s32` with `(s32)(mtx + (p->bone << 6))` ........................... 70
 *   - `mtx = (s32)obj->unk1D4 + (p->bone << 6);` before the stores ... 1320, 1060 bytes
 *       (loses two instructions: with the bone read pulled up next to the mask test's
 *        bone read and no aliasing store between them, IDO CSEs the two `lbu 0(s0)` into
 *        one.  Golden has two.)   The same statement after the stores ........... 960
 *   - index cursor `spheres[i]`, 12 scalars ........................ 386, frame 0xE8
 *       (the index form ALSO reaches the preheader -- IDO strength-reduces it into an
 *        induction pointer initialised there -- but it needs 12 bytes of compiler temp
 *        instead of 4, so the frame grows by 8.  Golden's 4-byte temp area proves golden
 *        does NOT strength-reduce, i.e. `p` is a real declared pointer cursor.)
 *   - index cursor cut to 10 scalars to pay for the temp (frame 0xE0 again) ..... 485
 *   - 8 scalars + 7 struct17 (frame 0xD8) ...................................... 2585
 *   - 10 scalars, index cursor, `best = &spheres[bestIndex]` ................... 1715
 *   - 10 scalars, pointer cursor + inline tail (frame 0xD8) .................... 2207
 *   - 11 scalars (cursor + `best` variable) .................................... 1750
 *   - 12 scalars, `p = &spheres[i]` at top of body instead of a cursor ......... 1276
 *   - swapping the declaration order of `hit` and `radius` ...................... 960 (inert)
 *   - using `hit` for the in-loop func_151452C4 call as well .................... 960 (inert)
 *   - do-while shape with the obj->unk1D4 read left INLINE (no mtx) ............. 995
 *
 * THE PERMUTER produced nothing here (setup + selftest PASS, base 60, ~500 iterations at
 * -j4 gated on PERMUTER_TU_REQUIRE_FRAME=224 / PERMUTER_TU_REQUIRE_OFFSETS=1, no output-*
 * at all).  The close came from source-level reasoning about which BASIC BLOCK each
 * initialisation belongs to, which is not in the permuter's search space.
 *
 * NOTE FOR FUTURE WAVES: "shape X fixes the placement but costs a register rotation" was
 * a false trade caused by an incidental spelling difference inside shape X.  When a shape
 * both fixes a residual and introduces a new one, re-derive the new residual from scratch
 * under the BEST spelling of that shape before recording it as a trade.
 * ============================================================================== */
