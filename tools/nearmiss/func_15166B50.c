/* tools/nearmiss/func_15166B50.c  --  game_193E50
 *
 * KIND: COMPLETE, COMPILABLE TU (not a snippet -- an earlier header said otherwise).
 * Score it DIRECTLY, in one command:
 *     python3 tools/fastscore.py game_193E50 func_15166B50 tools/nearmiss/func_15166B50.c
 * It still carries the ObjType0DData pad split (field_0x1 / field_0xC named inside
 * the old pad_0[0x10]); that split must go into conker/src/game_193E50.c with it.
 *
 * STATUS: PARKED.  mism = 19, n=134/134, frame=-256 (0x100).  (Was 34; see the
 *         WAVE ADDENDUM directly below this comment block -- cluster (b) is CLOSED.)
 *         2026-08-21: still 19.  See WAVE ADDENDUM 2 at the very end of this comment
 *         block: the residual is a GENUINE RANKING TIE, now confirmed by a full
 *         permuter run (the permuter is USABLE on this TU now -- selftest PASSES).
 * THE LENGTH GAP IS ZERO, so 34 is ENTIRELY REAL -- there is no phantom component
 * and no pad correction to apply.  (Do NOT pad-correct by counting trailing `nop`s
 * in the golden .s: that overcounts by one whenever the epilogue's delay slot is a
 * nop, because splat prints a delay-slot instruction with one extra leading space.
 * The only number to trust is fastscore's own n=ours/golden gap, which is what it
 * actually bills at 10 points apiece.)
 * Every sp-relative offset is EXACT: sp70 at 0x70, mf[4][4] at 0xC0, x/y/z at
 * 0xBC/0xB8/0xB4, the saves s0..s7/fp/ra at 0x40..0x64.
 * Progress: 60 -> 57 (u8 prim colours) -> 34 (frame law: three word-locals).
 *
 * ==========================  THE FRAME LAW (generalisable)  =================
 * IDO reserves a stack slot for EVERY declared local, including ones that end up
 * living purely in registers.  Locals are laid out TOP-DOWN in DECLARATION order
 * (first-declared is highest / flush with the frame top) and
 *      frame = roundup8(0x6C + sum_of_all_declared_local_sizes)
 * where 0x6C = argarea_block(0x28) + savearea(0x40) + 4.  Verified on 8 variants
 * of this function and against the already-matched func_151669A0 in the same TU.
 * CONSEQUENCE: a 0xC "hole" in the golden frame between two used locals is not a
 * hole -- it is three register-allocated word locals you have not declared yet.
 * Do NOT chase such holes with padding arrays; declare the variables.
 *
 * ==========================  WHAT IS LEFT: 34 rows, ONE root cause  =========
 * The rows split 18 / 16 (an earlier header said 22/12 -- that was miscounted):
 *   register permutation : idx 1,2,9,10,11,15,21,50,52,55,71,73,75,79,103,107,112,118
 *   4000.0f displacement : idx 22..37
 * and the second cluster is a CONSEQUENCE of the first (proved below).
 *
 * The whole residue is ONE saved-register permutation:
 *      golden   s0=arg0  s1=i  s2=mtx  s3=&mf  s4=&x s5=&y s6=&z s7=&sp70 fp=0xC0
 *      ours     s0=mtx   s1=i  s2=&mf  s3=arg0 s4=&x s5=&y s6=&z s7=&sp70 s8=0xC0
 * s4..s7 and fp/s8 already match; the loop body, the branch structure, the epilogue
 * and every stack offset are byte-identical.  idx21 (`sb $t7,0xD0($sX)`) and idx103/
 * 107/118 differ ONLY in the base register, i.e. they are the same permutation.
 *
 * ==========================  THE SAVED-REGISTER LAW (new, measured)  ========
 * IDO fills the saved registers from BOTH ENDS:
 *   - address-taken locals are materialised in REVERSE use order and take s7
 *     DOWNWARD: &sp70=s7, &z=s6, &y=s5, &x=s4, then &mf next;
 *   - scalars take s0 UPWARD in CREATION (first-definition) order, NOT declaration
 *     order.
 * PROVED: swapping the source order of `mtx = arg0->field_0x10;` and `i = 0;`
 * swaps their registers (s0<->s1) and nothing else.  That is a real, working lever.
 * Golden's order is [arg0, i, mtx] -> s0,s1,s2 with the five addresses contiguous
 * at s3..s7.  Ours is [mtx, i] -> s0,s1, then &mf -> s2, then arg0 -> s3, then
 * x,y,z,sp70 -> s4..s7.  In other words OUR ordering is golden's ROTATED LEFT BY
 * ONE:  golden [arg0,i,mtx,&mf]  vs  ours [mtx,i,&mf,arg0].
 *
 * THE ONE UNEXPLAINED FACT, and the whole of the remaining 34:
 * the incoming PARAMETER's saved copy is allocated LAST in our compile (s3) and
 * FIRST in golden's (s0) -- even though BOTH emit `or $sX,$a0,$zero` as instruction
 * idx2 and BOTH use that register for the pre-loop `lbu $t6,0xD0($sX)`.  Nothing
 * reachable from C source moved it (see below).  Fix that one placement and all 34
 * rows go together.
 *
 * ==========================  DO NOT REPEAT  =================================
 * Earlier waves:
 *  - Declaring the ParticleInit local FIRST: it then sits flush at the frame top
 *    (0xC0) instead of 0x70.  mf[4][4] must be the first declared local.
 *  - Padding arrays (s32 fill[n]) to reach frame 0x100: reaches the size but leaves
 *    the base at 0x74/0x78, and is a fake.  The honest fix is three word locals.
 *  - Permuting the three word locals among themselves: FLAT at 34 (all 6 orders).
 *    DECLARATION ORDER IS EXHAUSTED -- do not sweep it again.
 *  - Padding ParticleInit to 0x3C and dropping `rnd`: FLAT at 34.
 *  - `s8 primR/primG/primB`: IDO folds 0xFF to -1 (`addiu t6,zero,-1`); golden has
 *    `addiu t6,zero,0xFF`.  Those three fields are u8 HERE.  Do not revert.  (Do not
 *    "fix" the shared struct in game_1B9F30.c -- that one never assigns a constant.)
 *  - Moving `sp70.width/height` to the TOP of the block: the two
 *    `field_0xD8 * 4000.0f` expressions CSE into ONE (122 instrs, mism 228).  The
 *    intervening struct stores are what defeat IDO's alias analysis.  Keep them.
 *  - Moving `sp70.animPtr = D_8008CA4C;` last: 61.  After sizeGrowth: flat 34.
 *  - Replacing `mtx` with `(Mtx *)((u8 *)arg0->field_0x10 + i)`: 36.
 *  - `mf[0]` / `f32 mf[16]` instead of `&mf[0][0]`: FLAT at 34.
 *  - Declaring i/mtx BEFORE mf: base drops to 0x6C, frame -248.
 * This wave (all frame-preserving at -256 and n=134/134 unless noted; all REFUTED):
 *  - `i` created BEFORE `mtx`, in every spelling -- comma init
 *    `for (i = 0, mtx = ...; ...)`, two separate statements with `for (; ...)`,
 *    a `while` form, a `do/while` form: ALL 36.  This genuinely swaps s0/s1, but
 *    arg0 stays at s3, so it costs 2 rows.  mtx-BEFORE-i is correct; keep it.
 *  - `for (mtx = ..., i = 0; ...)` and an explicit `mtx = ...; i = 0;` pair: flat 34
 *    (identical rows) -- comma-init carries no information, only relative order does.
 *  - An explicit parameter-copy local `obj = arg0;` (replacing `rnd` so the frame
 *    holds), used throughout: fully COALESCED, byte-identical 34.
 *  - THE BEHAVIOUR-TABLE SIGNATURE THEORY IS REFUTED BY MEASUREMENT.  Retyping the
 *    parameter `struct102 *arg0` or `void *arg0` and casting once into an
 *    `ObjType0DData *obj` local (which is what the D_8008CA20 dispatch table and the
 *    existing `func_1516972C((struct102 *)arg0)` cast suggest): ALSO fully coalesced,
 *    byte-identical 34, in both i/mtx orders.  The cast is a no-op and does not
 *    create a distinct value, so it cannot move arg0 off s3.
 *  - Creating i/mtx at the TOP of the if-block (before the struct stores): flat 34
 *    (mtx-first) / 36 (i-first).
 *  - Creating i/mtx BEFORE the `if`: 129, and 135 instructions -- hoisting past the
 *    branch is wrong.
 *  - Loop FORM carries no information: for / while / do-while all reduce to the
 *    same code once the i-vs-mtx creation order is fixed.
 *  - Dropping `rnd` and inlining `(func_150ADA20() & 0x7F) + 0x55`: flat 34, rows
 *    byte-identical.  So `rnd` is interchangeable with struct padding and the third
 *    word local remains UNIDENTIFIED (see honesty flag).
 *  - CLUSTER (b) IS NOT INDEPENDENT.  `4000.0f * field_0xD8` vs
 *    `field_0xD8 * 4000.0f`, applied to width, to height, and to both; `(s16)` casts
 *    on the products; extra parentheses; moving `animPtr` after `sizeGrowth` -- ALL
 *    EIGHT produce a BYTE-IDENTICAL row set.  IDO normalises the mul.s operand order
 *    when one operand is a memory load, so the "memory operand first" lever carries
 *    no information here.  The 16 rows at idx22..37 are purely the displacement of
 *    the `lui $at,0x457A / mtc1 $at,$f0` pair, which golden emits adjacently right
 *    after the branch and we split (lui at idx25, mtc1 deferred to idx36); that is a
 *    scheduling consequence of the register permutation, not a separate defect.
 *    Do not attack it on its own.
 *  - `4000.0` without the `f` suffix: 137 instructions, 149.  The suffix is required.
 *  - PERMUTER UNUSABLE, AS PREDICTED.  `permuter_tu.sh selftest` on this TU: (a)
 *    PASSES; (b) FAILS; (b2) FAILS -- the pycparser round trip changes codegen, so
 *    every score it printed would be measured on a different source than the one
 *    shown; (c) and (d) fail as a consequence; (e) reports that isolation differs
 *    from the in-TU build.  This TU contains gSPMatrix/gSPVertex/gSPModifyVertex in
 *    func_15166D68, which is the known round-trip trap.  Do not run it here.
 *
 * ==========================  HONESTY FLAG  ==================================
 * The THIRD word local is not identified.  The frame pins the COUNT (three) and the
 * SIZE (4 bytes each) of the word locals between `z` and the ParticleInit, and two
 * of them are identifiable from the code (`i` and `mtx`).  The third is spelled
 * `rnd` here, but dropping it entirely and inlining the func_150ADA20() call
 * measures BYTE-IDENTICALLY, and so does padding the ParticleInit by 4 instead --
 * a genuine ranking tie.  An unused or immediately-consumed local has no live range,
 * so it is allocated no register and appears nowhere in the instruction stream;
 * nothing in this function's bytes can discriminate the candidates.  Naming it needs
 * evidence from OUTSIDE this function.  Do not call this file a match on the
 * strength of the name `rnd`.
 *
 * Calibration sibling used: func_1518CA80 in conker/src/game_1B9F30.c (matched),
 * which documents the same 0x38-byte ParticleInit handed to func_15167D84.
 */

/* ============================  WAVE ADDENDUM -- 34 -> 19  =====================
 * Everything above this line is the previous wave's record and is preserved
 * verbatim except for the STATUS line.  This wave moved the score 34 -> 19 by
 * closing CLUSTER (b) outright, and it OVERTURNS one claim above.
 *
 * ---- CLUSTER (b) IS CLOSED, AND IT IS INDEPENDENT OF CLUSTER (a) ------------
 * All of the 4000.0f rows (idx22..idx37) now match.  Golden's
 *      lui at,0x457A / mtc1 at,f0 / li t9,4 / lw t8,%lo(D_8008CA4C) / li t0,5
 * is reproduced exactly.  THE FIX IS TO DECLARE SOMETHING IN THE if-BLOCK'S OWN
 * SCOPE -- i.e. the golden source has a local declared inside
 *      if (arg0->field_0xD0 == 5) { ... }
 * that we were not modelling.  Adding one takes 34 -> 19.
 *
 * The earlier conclusion that (b) was "not independent" was drawn from sweeping
 * SPELLINGS OF THE MULTIPLY (operand order, (s16) casts, parentheses, animPtr
 * position).  That sweep is right as far as it goes -- I reproduced it: all those
 * spellings are byte-identical, and `4000.0` without the f suffix is far worse.
 * But the multiply was never the lever.  The lever is the BLOCK SCOPE, and pulling
 * it left the saved-register signature bit-for-bit unchanged
 * (arg0/i/mtx/&mf = s3/s1/s0/s2 before and after).  The two clusters are therefore
 * separable, and (b) is now done: all 19 remaining rows are cluster (a).
 *
 * HONESTY CAVEAT -- measured, and stated plainly rather than papered over.
 * The mechanism is the DECLARATION, not the use and not the storage:
 *      f32 k = 4000.0f;  used in both width/height expressions   -> 19
 *      f32 k;            declared, never used                    -> 19
 *      s32 dd; / s16 h; / u8 b; / Mtx *m; / ObjType0DData *o;    -> 19 (all unused)
 *      the SAME declaration at function scope after sp70          -> 34 (inert)
 *      the SAME declaration in the else branch                    -> 34 (inert)
 *      f64 (8 bytes) in the if-block                              -> frame -264
 * So the placement is established and the spelling is a guess.  `f32 k = 4000.0f`
 * is kept because it is at least used and is the only value in the block a
 * programmer would naturally name.  It passes the load-bearing test (delete it and
 * the object changes, 19 -> 34) but a future wave should try to identify the real
 * local rather than treat this spelling as settled.
 *
 * FRAME NOTE that makes the above safe: locals sum to 0x90, and 0x6C + 0x90 = 0xFC
 * rounds up to 0x100, so there is a 4-BYTE PAD at 0x6C..0x70.  Up to 4 bytes of
 * extra nested-scope locals fit in it with sp70 still at 0x70 and mf still at 0xC0.
 * A 5th byte (or an f64) pushes the frame to -264.
 *
 * ---- CLUSTER (a): HOW IDO ACTUALLY RANKS THESE REGISTERS --------------------
 * Measured, and it is NOT "first-use order":
 *  - ONLY references inside the LOOP count.  Out-of-loop references count ZERO.
 *    Proven two ways: deleting the tail func_1516972C(arg0) reference does not move
 *    arg0, and rewriting the ENTIRE pre-loop body to use globals instead of arg0 --
 *    so that arg0's only surviving uses are the mtx init and the two loop loads --
 *    STILL leaves arg0 on s3.  Live-range length is not the lever either.
 *  - CSE'd references count ZERO (two source refs collapsing to one lbu rank as one).
 *  - Strength-reduced references count ZERO: for(i=0;i<3;i++) with
 *    &arg0->field_0x10[i] compiles BYTE-IDENTICALLY to the hand-written pointer IV,
 *    and the arg0 reference in it buys nothing.
 *  - The ONE lever that promotes arg0 to s0 is a THIRD genuine emitted in-loop
 *    reference.  Verified twice: add `sp70.unk1A = arg0->field_0xD2;` to the loop
 *    body and the signature becomes exactly golden's s0/s1/s2/s3 shape.  But it
 *    costs 2 instructions (n=136), and golden's loop demonstrably touches s0 only
 *    twice: lbu 0xC(s0) at idx103 and lbu 0x1(s0) at idx107.
 *    ==> Either there is a zero-cost third reference nobody has found, or arg0's
 *    displacement has a cause other than reference count.  That is the whole of the
 *    remaining 19 rows, and it is the ONLY question left on this function.
 *  - Positional shape: s4..s8 are handed out in ASCENDING source order of first use
 *    (&x, &y, &z, &sp70, const 0xC0) and arg0 lands immediately BELOW that run.
 *    Replace x/y/z with globals and arg0 moves to s6 -- it always sits just under
 *    the block of address temps, never above it.
 *
 * ---- ADDITIONAL REFUTATIONS FROM THIS WAVE (do not re-walk) -----------------
 *  - A 120-cell sweep of (loop-init form) x (guMtxL2F mf spelling: mf / &mf[0][0] /
 *    mf[0] / cast) x (func_150A7960 mf spelling) x (rnd named vs inlined): every
 *    cell scored 19 or worse and NOT ONE moved a saved register.
 *  - sp70.animPtr swept through all 20 positions in the block: 34,34, then 35 x8,
 *    then 60/61 x10.  Position 0 or 1 only.
 *  - sp70.width swept through positions 0..10: 61,63,63,63,63,63,62,61,57,53,34.
 *    It must stay exactly where it is (the intervening stores are what defeat the CSE).
 *  - arg0->field_0xD0 = arg0->field_0xD0 - 1;  /  -= 1;  /  if (--arg0->field_0xD0
 *    == 5): all byte-identical to arg0->field_0xD0--.  Out-of-loop refs are inert.
 *  - Changing the parameter to void * or s32 and casting it into an
 *    ObjType0DData *obj local: 19, still s3.  Fully coalesced, as the copy-local
 *    theory already predicted.
 *  - guMtxL2F(mf, mtx++) with the separate mtx++ deleted: 84 (n=135).
 *    mtx++ moved into the for-increment (either order): 19, no change.
 *    else { if (...) } instead of else if (...): 19, no change.
 *  - Hoisting the two arg0 loop loads into an inner-scope block just before the call
 *    (u8 c = arg0->field_0xC; u8 d = arg0->field_0x1;): 50, n=134, arg0 STILL s3.
 *    Moving arg0's first in-loop use earlier does not promote it.
 *  - A second nested-scope local in the if-block, or an f64 one: frame -264.
 *
 * ---- MEASUREMENT NOTE -------------------------------------------------------
 * Do NOT pad-correct by counting trailing nops in the golden .s.  That overcounts
 * by one whenever the epilogue delay slot is a nop, because splat prints a
 * delay-slot instruction with one extra leading space.  Trust only fastscore's own
 * n=ours/golden gap; here it is zero, so 19 is entirely real.
 *
 * ---- PERMUTER ---------------------------------------------------------------
 * Confirmed unusable, matching the prediction: selftest (b2) FAILS ("round trip
 * changes codegen"), and (b), (c), (d) fail too -- 4/4 live perturbations changed
 * the object without changing the score, i.e. the harness is not scoring
 * func_15166B50 at all.  One correction for a future wave: stripping the two
 * GBI-macro functions (func_15166D68, func_15166FD8) out of the TU leaves this
 * function's object BIT-IDENTICAL, so TU context is genuinely inert here despite
 * what selftest (e) reports.
 * ========================================================================== */


/* =====================  WAVE ADDENDUM 2  --  2026-08-21  ======================
 * Still 19, n=134/134, frame=-256.  Nothing moved.  Three things below OVERTURN
 * earlier claims in this header, and one of them is a tool-availability change that
 * matters more than the score.
 *
 * ---- A. THE PERMUTER IS NOW USABLE ON THIS TU.  IT FOUND NOTHING. -----------
 * `./permuter_tu.sh setup game_193E50 func_15166B50 <this file>` then `selftest`:
 *      (a) PASS  reassembly identity
 *      (b) PASS  harness object == repo-Makefile object, identical codegen
 *      (b2) PASS pycparser round trip is CODEGEN-NEUTRAL   <-- was FAIL, now PASS
 *      (d) PASS  negative control
 *      SELFTEST: PASS
 * The previous header's "PERMUTER UNUSABLE, AS PREDICTED" is OUT OF DATE for this TU.
 * (It is still FAIL on the sibling target game_196DB0/func_15169A48, where (b2) still
 * fails.)  A real run was then made:
 *      PERMUTER_TU_REQUIRE_FRAME=256 PERMUTER_TU_REQUIRE_OFFSETS=1  (env prefix)
 *        ./permuter_tu.sh run <dir> -j 10 --best-only --stop-on-zero
 *      base asm-differ score 244; ~1800 iterations; MINIMUM SEEN = 244 = the base.
 *      Not one candidate beat the base, and no output/ directory was produced.
 * Combined with the manual sweeps below this is strong evidence that the remaining 19
 * is a RANKING TIE, not an unfound spelling.  A future wave may run it longer, but it
 * should expect nothing from the randomiser and look for a STRUCTURAL fact instead.
 *
 * ---- B. THE TEMP-ROTATION COUNTER DOES NOT REACH SAVED REGISTERS ------------
 * The counter law that decomposed the sibling function (a redundant `& 0xFF` on a u8
 * field is a FREE value that still consumes a temp number, so N of them rotate every
 * later $t register by N mod 9) was applied here in 40 cells: masks x1..x8 on
 * arg0->field_0xC, on arg0->field_0x1, on both, on field_0xD0 in the `== 5` test and
 * in the `== 0` test.  RESULT: the ROW SET is IDENTICAL in all 40 (mism 19/20/21, the
 * 1-2 point wobble being the masked field's own load).  IDO's $s0..$s7 allocation is a
 * SEPARATE mechanism from the $t rotation and is immune to free values.
 * Do not bring the mask lever to a saved-register residual again.
 *
 * ---- C. THE PERMUTATION IS NOT A ROTATION.  IT IS TWO INDEPENDENT EDITS. ----
 * Re-derived from the object rather than from the earlier prose:
 *      ours   s0=mtx   s1=i  s2=&mf  s3=arg0  s4=&x s5=&y s6=&z s7=&sp70  fp=0xC0
 *      golden s0=arg0  s1=i  s2=mtx  s3=&mf   s4=&x s5=&y s6=&z s7=&sp70  fp=0xC0
 * As ordered lists s0..s7 that is NOT "ours rotated left by one" (the old header's
 * claim): it is TWO orthogonal edits -- arg0 moves from slot 3 to slot 0, AND i/mtx
 * swap.  Proof that they are orthogonal: creating `i` before `mtx` really does swap
 * s0/s1 and nothing else, giving [i, mtx, &mf, arg0, ...], which IS golden rotated
 * left by one -- and it scores 21, i.e. WORSE, because two of ours' four slots
 * currently coincide with golden's by accident.  So `mtx`-before-`i` is only
 * ACCIDENTALLY the better of the two; if a future wave ever promotes arg0 to s0 it
 * must re-test both creation orders, because the correct one may flip.
 * All five prologue rows (idx1, 2, 9, 10, 11) are ONE consequence, not five defects:
 * golden's prologue is `sw $s0,0x40 / or $s0,$a0,$zero / sw $ra / sw $fp / sw $s7 ...
 * sw $s1` -- the register that will hold the parameter copy is saved FIRST and ALONE,
 * then the copy is made, then the rest descend.  Ours does exactly that with $s3.
 * Fix which register arg0 lands in and idx1/2/9/10/11/15/21/37/55/71/73/75/79/103/
 * 107/112/118 all go together.
 *
 * ---- D. THE BLOCK-SCOPE LAW IS SPENT ON THIS FUNCTION -----------------------
 * It already paid once (cluster (b), 34 -> 19).  Every further application is worse,
 * and the 4-byte pad at 0x6C..0x70 admits exactly ONE nested local:
 *      second decl in the if-block (before or after k)      52, frame -264
 *      decl in the `else if (field_0xD0 == 0)` arm           52, frame -264
 *      decl in the LOOP BODY, any type (s32/f32/s16/u8/
 *        Mtx ptr / ObjType0DData ptr)                       84, frame -264, n=135
 * IMPORTANT: DISJOINT SCOPES DO NOT SHARE THE PAD.  A local in the else-if arm cannot
 * overlap `k` in the if arm even though their lifetimes are disjoint -- it still costs
 * 4 more bytes and blows the frame to -264.  Do not try that trick again.
 * `k` also cannot be moved into the loop body: it is read by sp70.width/height, which
 * are set before the loop.
 * Note the epilogue ALREADY exhibits the law's forward direction and matches golden:
 * `b .L15166D30 / lw $ra,0x64($sp)` and `bnel $v0,$zero,.L15166D30 / lw $ra,...` --
 * the `lw ra` duplicated into the branch target rather than the slot filled from
 * above.  There is nothing left for the law to buy here.
 *
 * ---- E. NEW REFUTATIONS THIS WAVE (all byte-identical at 19, do not re-walk) --
 *   - x/y/z replaced by an `f32 xyz[3]` array, passed &xyz[2],&xyz[1],&xyz[0] and read
 *     back into sp70.x/y/z: BYTE-IDENTICAL.  The address pool does not care.
 *   - guMtxL2F(&mf[0][0], mtx) instead of guMtxL2F(mf, mtx): byte-identical.
 *   - func_150A7960(mf[0], ...) instead of &mf[0][0]: byte-identical.
 *   - mtx = &arg0->field_0x10[0] instead of arg0->field_0x10: byte-identical.
 *   - `i < 0xC0` instead of `i != 0xC0`: byte-identical.
 *   - `mtx = arg0->field_0x10;` hoisted to the TOP of the if-block (above all the
 *     sp70 stores): byte-identical.  (Contrast sp70.width, which is position-critical.)
 *   - `f32 k;` unused with 4000.0f written literally in BOTH width/height expressions:
 *     byte-identical to `f32 k = 4000.0f;` used in both.  This re-confirms that the
 *     mechanism is the DECLARATION, not the use -- and it means the `= 4000.0f`
 *     initialiser in the shipped file is still a guess, exactly as flagged.
 *   - `k * arg0->field_0xD8` (constant first) in both: byte-identical.
 *   - CORRECTION to an earlier claim: retyping the parameter `void *arg0v` and casting
 *     into an `ObjType0DData *arg0` local does NOT coalesce for free -- it scores 52 at
 *     frame -264.  It coalesced earlier only because that test REPLACED `rnd`, holding
 *     the local count.  The coalescing conclusion stands; the frame bookkeeping does not.
 *
 * ---- F. WHAT IS ACTUALLY LEFT ----------------------------------------------
 * One question, unchanged and now much better fenced: what ranks the incoming
 * parameter FIRST among the saved registers in golden and LAST-but-one in ours, when
 * both loops touch it exactly twice, both copy it at idx2, and every spelling of every
 * other local is byte-identical?  Reference count is refuted (golden's loop touches s0
 * twice, so the "third in-loop reference" lever that does promote arg0 cannot be what
 * golden did -- it costs 2 instructions golden does not have).  The next thing to try
 * is NOT another spelling of this function: it is the `static`-scope law (a global
 * pulled into a function-scope static changes saved-register pressure) applied to
 * D_8008CA4C, and a look at a MATCHED sibling that also copies its pointer parameter
 * into s0 to see what its loop does differently.
 *
 * HONESTY FLAGS ALL STILL STAND: `rnd` is unidentified (dropping it is byte-identical),
 * and `f32 k = 4000.0f` is a guessed spelling of a declaration whose PLACEMENT is
 * proven but whose name, type and initialiser are not.  This file is not a match.
 * ========================================================================== */

/* ---- struct patch required in game_193E50.c ---------------------------------
 * Replace
 *     char pad_0[0x10];
 * at the top of ObjType0DData with
 *     char pad_0[0x1];
 *     u8   field_0x1;
 *     char pad_2[0xA];
 *     u8   field_0xC;
 *     char pad_D[0x3];
 * (layout-neutral; func_151669A0 / func_15166D68 / func_15166F6C do not touch
 * those bytes, so they are unaffected -- but re-score them after editing.)
 * -------------------------------------------------------------------------- */

#include <ultra64.h>
#include "functions.h"
#include "variables.h"

typedef struct {
    char pad_0[0x1];
    u8 field_0x1;
    char pad_2[0xA];
    u8 field_0xC;
    char pad_D[0x3];
    Mtx field_0x10[3];
    u8 field_0xD0;
    char pad_0xD1[0x1];
    s16 field_0xD2;
    s16 field_0xD4;
    s16 field_0xD6;
    f32 field_0xD8;
} ObjType0DData;

extern void *func_15167A68(s32, s32, s32, s32, s32, s32);
extern void func_1517E05C(s32, s32, s32);
extern s32 D_8009054C;
extern s32 D_800DD220;
extern s32 D_800DD224;
extern s32 D_800DD228[];
extern s32 D_800DD230;

void func_151669A0(s32 arg0, s32 arg1, s32 arg2, f32 arg3, s32 arg4, s32 arg5) {
    ObjType0DData *temp_v0;
    Mtx *mtx;
    s32 temp_s0;
    s32 i;
    f32 temp_f24;
    f32 temp_f26;
    f32 temp_f28;

    temp_v0 = func_15167A68(0xD, arg5, 0xE0, 1, (u8)arg4, 1);
    if (temp_v0 != 0) {
        temp_v0->field_0xD0 = 0xA;
        temp_v0->field_0xD2 = arg0;
        temp_v0->field_0xD4 = arg1;
        temp_v0->field_0xD6 = arg2;
        temp_v0->field_0xD8 = arg3;

        temp_s0 = func_150ADA20() & 0x7F;
        temp_f24 = arg0;
        temp_f26 = arg1;
        temp_f28 = arg2;
        mtx = temp_v0->field_0x10;
        for (i = 0; i != 0xC0; i += 0x40) {
            if (arg3 != 1.0f) {
                func_15043D90(mtx, 0.0f, temp_s0, 0.0f, arg3, arg3, arg3, temp_f24, temp_f26, temp_f28);
            } else {
                func_15043E68(mtx, 0.0f, temp_s0, 0.0f, temp_f24, temp_f26, temp_f28);
            }
            temp_s0 += func_150ADA20() & 0x3F;
            mtx++;
            temp_s0 += 0x5A;
        }
        func_1517E05C(arg0, arg1, arg2);
    }
}

typedef struct {
    /* 0x00 */ s32 animPtr;
    /* 0x04 */ s32 sizeGrowth;
    /* 0x08 */ s32 unk08;
    /* 0x0C */ s16 animFrame;
    /* 0x0E */ s16 animSpeed;
    /* 0x10 */ s16 x;
    /* 0x12 */ s16 y;
    /* 0x14 */ s16 z;
    /* 0x16 */ s16 velX;
    /* 0x18 */ s16 velZ;
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ u8 xFrac;
    /* 0x1D */ u8 zFrac;
    /* 0x1E */ u8 yFrac;
    /* 0x1F */ s8 updateFuncIdx;
    /* 0x20 */ s16 velY;
    /* 0x22 */ s16 accelY;
    /* 0x24 */ s16 width;
    /* 0x26 */ s16 height;
    /* 0x28 */ s16 lifetime;
    /* 0x2A */ s8 alphaFade;
    /* 0x2B */ u8 expireFuncIdx;
    /* 0x2C */ u8 primR;
    /* 0x2D */ u8 primG;
    /* 0x2E */ u8 primB;
    /* 0x2F */ u8 alpha;
    /* 0x30 */ s8 envR;
    /* 0x31 */ s8 envG;
    /* 0x32 */ s8 envB;
    /* 0x34 */ s16 flags;
} ParticleInit;

extern s32 D_8008CA4C;
s32 func_15167D84(void *, s32, s32, s32, s32, s32);
void func_150A7960(f32 *, f32, f32, f32, f32 *, f32 *, f32 *);

void func_15166B50(ObjType0DData *arg0) {
    f32 mf[4][4];
    f32 x;
    f32 y;
    f32 z;
    s32 i;
    Mtx *mtx;
    s32 rnd;
    ParticleInit sp70;

    arg0->field_0xD0--;
    if (arg0->field_0xD0 == 5) {
        f32 k = 4000.0f;
        sp70.animPtr = D_8008CA4C;
        sp70.sizeGrowth = 0;
        sp70.unk08 = 4;
        sp70.animFrame = 0;
        sp70.velX = 0;
        sp70.velZ = 0;
        sp70.unk1A = 0;
        sp70.updateFuncIdx = 5;
        sp70.velY = 0;
        sp70.accelY = 0;
        sp70.width = arg0->field_0xD8 * k;
        sp70.height = arg0->field_0xD8 * k;
        sp70.lifetime = 0x200;
        sp70.alphaFade = 0;
        sp70.expireFuncIdx = 0;
        sp70.primR = 0xFF;
        sp70.primG = 0xFF;
        sp70.primB = 0xFF;
        sp70.alpha = 0xFF;
        sp70.flags = 0;
        mtx = arg0->field_0x10;
        for (i = 0; i != 0xC0; i += 0x40) {
            guMtxL2F(mf, mtx);
            func_150A7960(&mf[0][0], -400.0f, 10.0f, 0.0f, &x, &y, &z);
            rnd = func_150ADA20();
            sp70.animSpeed = (rnd & 0x7F) + 0x55;
            sp70.x = x;
            sp70.y = y;
            sp70.z = z;
            func_15167D84(&sp70, 0, 0, -1, arg0->field_0xC, arg0->field_0x1);
            mtx++;
        }
    } else if (arg0->field_0xD0 == 0) {
        func_1516972C((struct102 *)arg0);
    }
}

extern Vtx D_8008B3E0[];

Gfx *func_15166D68(Gfx *pkt, ObjType0DData *obj, s32 arg2) {
    Mtx *mtx;
    s32 s;
    s32 i;

    for (i = 0, mtx = obj->field_0x10; i != 0xC0; i += 0x40) {
        gSPMatrix(pkt++, mtx, G_MTX_LOAD);
        gSPVertex(pkt++, D_8008B3E0, 6, 0);
        s = 0x2800 - ((obj->field_0xD0 << 12) / 10);
        gSPModifyVertex(pkt++, 0, G_MWO_POINT_ST, (s << 16) + 0x2000);
        gSPModifyVertex(pkt++, 1, G_MWO_POINT_ST, (s << 16) + 0x2000);
        gSPModifyVertex(pkt++, 2, G_MWO_POINT_ST, (s << 16) + 0x2400);
        gSPModifyVertex(pkt++, 3, G_MWO_POINT_ST, ((s + 0x800) << 16) + 0x2000);
        gSPModifyVertex(pkt++, 4, G_MWO_POINT_ST, ((s + 0x800) << 16) + 0x2000);
        gSPModifyVertex(pkt++, 5, G_MWO_POINT_ST, ((s + 0x800) << 16) + 0x2400);
        gSP1Triangle(pkt++, 5, 3, 0, 0);
        gSP1Triangle(pkt++, 2, 5, 0, 0);
        gSP1Triangle(pkt++, 1, 4, 5, 0);
        gSP1Triangle(pkt++, 1, 5, 2, 0);
        mtx++;
    }
    return pkt;
}

void func_15166F6C(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    D_800DD228[0] = (s32)&D_8009054C;
    func_15094F70(arg0, D_800DD228[0], D_800DD220, (s32)&D_800DD230, 0, 0, 0, D_800DD224, 3);
}

extern Mtx D_80089470;

Gfx *func_15166FD8(Gfx *pkt, s32 arg1, s32 arg2) {
    gSPMatrix(pkt++, &D_80089470, G_MTX_LOAD);
    return pkt;
}
