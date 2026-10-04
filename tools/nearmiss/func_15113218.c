/* ############################################################################
 * RULING 2026-08-21 -- DO NOT SHIP THIS. DO NOT RE-LITIGATE IT.
 *
 * This function reaches SCORE 0 with a byte-identical instruction stream, and a
 * 16-byte `s32 pad[4]` would close it.  It was put to the project owner as an
 * explicit policy question, with the precedent laid out (three ALREADY-SHIPPED
 * functions carry exactly this construct: game_19A8B0/func_1516F024 with a
 * documented rationale comment, game_10B7D0/func_150DE458, and
 * game_57FA0/func_1502B9B4 as pad[3]+pad0).
 *
 * THE RULING WAS: leave it parked until the bytes can be NAMED.
 *
 * So the bar for this function is evidence that names the reservation -- not
 * precedent, not a load-bearing test, not corpus base rates.  A future wave that
 * rediscovers the pad[4] spelling has NOT found something new; it has found the
 * thing that was already declined.
 *
 * WHAT WOULD ACTUALLY CLOSE IT: a match on any of func_15112A80, func_151135C4,
 * func_15188F84, func_150F2A60, func_150F34F4 or func_150BDB70 -- the only other
 * code written against these tables, and the only realistic source of a naming
 * for the reserved block.
 * ##########################################################################*/

/* ============================================================================
 * func_15113218   (game_13D350.c, 247 instructions)
 *
 * STATUS: SCORE 0 (byte-identical instruction stream, -R, --max-lines 247)
 *         BUT NOT SHIPPED. Blocked on ONE open question: the frame is 0xD8 and
 *         requires 120 BYTES OF DECLARED LOCALS; only 100 bytes are justified
 *         by the emitted code. The remaining 20 bytes (5 words) are locals the
 *         ORIGINAL source declared and never used. I could not name them from
 *         evidence, and "dead locals that exist only to move the frame" are
 *         banned, so this is parked as an OPEN QUESTION, not a match.
 *
 * Everything else is settled and reproducible: register allocation is
 * identical (s0=actor, s1=obj, s2=pos, s3=byte-offset IV, s4=&mtx,
 * s5=&D_80089240[i], s6=&D_80089250, s7=&D_800BE9C0, s8=&D_800DBEE8[i],
 * f20=0.0f loop-invariant), and every branch/schedule matches.
 *
 * SCORE LADDER (measured, `diff.py -o func_15113218 -R --max-lines 247`)
 *   6593  draft 1: `if (D_800DBEE8[i] > 0) { for (k=0;...) }`      (doubled test)
 *   6008  dropped the redundant `if` -- the for-loop's own entry guard is
 *         golden's single `blez v1`. Same law as the outer loop (see below).
 *   4883  x/y/z as an ARRAY `f32 v[3]` (forces memory; three f32 SCALARS get
 *         promoted to $f20/$f22 and golden has NO $f22 save), AND the actor
 *         address written as a repeated expression rather than a local.
 *   2000  actor address respelled -- see THE ACTOR-ADDRESS LAW below. This
 *         alone was worth 2883 and fixed s0/s1 allocation at the same time.
 *    383  dropped `if (D_80082FA0 < 0) return;` -- see THE DOUBLED-GUARD LAW.
 *      0  frame padded to 0xD8 with 5 probe locals (probe1 between k and v,
 *         probe2..5 after v).
 *
 * ---------------------------------------------------------------------------
 * THE ACTOR-ADDRESS LAW (new, worth 2883 here)
 * ---------------------------------------------------------------------------
 * golden:  ladder(type)*812 ; at = 0xFFFEC2D0 (= -100*812)
 *          addu t7, t6, at          <- (ladder + const)
 *          addu s0, t7, t9          <- ... + &D_800CC2D0
 *
 *   `&D_800CC2D0[type - 100]`  does NOT produce that. IDO treats the -81200 as
 *   an ADDRESS DISPLACEMENT, keeps `&D_800CC2D0[type]` in the saved register,
 *   and then either
 *     (a) re-materialises `lui 0xffff / addu / lw -0x3b5c` at every deref, or
 *     (b) (once the expression is repeated rather than held in a local) picks a
 *         ROUNDED bias `lui 0xfffe / ori 0x8000` = -0x18000 and uses fat
 *         displacements 0x42e4 / 0x4360 / 0x44a4.
 *   A ROUNDED bias constant (multiple of 0x8000) in your output where golden
 *   has an EXACT one is the fingerprint of this: the constant went down IDO's
 *   address-displacement path instead of staying an integer add.
 *
 *   The fix is to make the offset part of an INTEGER expression so the symbol
 *   is added last.  This TU already contains the matched idiom at
 *   game_13D350.c:242 -- `(Struct15113E54 *)(((entry & 0xFFF) * 0xA0) + (s32)D_800DBEF4)`:
 *
 *       actor = (Actor *)((type * 0x32C - 0x13D30) + (s32)D_800CC2D0);
 *
 *   Reproduced golden's `(ladder + const) + symbol` grouping on build #1.
 *   NOTE this is the LADDER form of the three-way actor-indexing law: zero
 *   `multu`, zero `div`, index came from a local. Confirmed against binary.
 *
 * ---------------------------------------------------------------------------
 * THE DOUBLED-GUARD LAW (fired TWICE here, 585 + 1617)
 * ---------------------------------------------------------------------------
 * If you write an explicit early-out AND a loop whose entry test is the same
 * predicate, IDO emits the test twice, and as1 turns the first into a
 * branch-LIKELY plus a duplicated first-instruction-of-target:
 *
 *      bltzl v1,36fc          <- yours, spurious
 *      lw    ra,0x44(sp)      <- duplicate of the target's first insn
 *      bltz  v1,36f8          <- the real one; golden has ONLY this
 *
 * Golden's single `bltz t6, <epilogue>` IS the for-loop's own rotated entry
 * guard. So `for (i = 0; i <= D_80082FA0; i++)` alone -- NO preceding
 * `if (D_80082FA0 < 0) return;`. Same for the inner loop: `for (k = 0;
 * k < D_800DBEE8[i]; k++)` alone, no `if (D_800DBEE8[i] > 0)` wrapper.
 * A spurious `Xl` + duplicate pair immediately before the real branch is the
 * signature; look for a second source-level test of the same predicate.
 *
 * ---------------------------------------------------------------------------
 * THE MEMORY-RESIDENT VECTOR (worth ~1100)
 * ---------------------------------------------------------------------------
 * golden stores the three floats to 0x78/0x70/0x74 and reloads them with `lw`
 * to pass them in a1/a2/a3.  Three f32 SCALARS get promoted to callee-saved
 * $f registers instead (you get an extra `sdc1 $f22` that golden lacks, and
 * `mfc1 a1,$f22` where golden has `lw a1,0x70(sp)`).  An ARRAY is never
 * register-allocated, so `f32 v[3]` forces golden's shape.  Note also
 * `v[2] = 0.0f; v[0] = v[2];` -- the store-then-RELOAD of 0x78 into 0x70 is
 * literally what golden does; `v[0] = 0.0f; v[2] = 0.0f;` would emit two
 * `swc1 $f20` and lose the `lwc1`.
 *
 * ---------------------------------------------------------------------------
 * INDEX EXPRESSION IS REPEATED, NOT CACHED
 * ---------------------------------------------------------------------------
 * `(*D_80089240[i])[k].unk0` appears FOUR times. It is NOT a local: golden
 * keeps it in a2 where no call intervenes and RELOADS it from memory after
 * every call. A declared local would have been spilled to a home slot; golden
 * has no such slot. The 4-byte element struct (Entry15113218) is what makes
 * IDO's induction variable the BYTE OFFSET s3 (+=4) while the loop test is
 * `slt s3, count*4` -- classic linear-function-test-replacement off
 * `for (k = 0; k < count; k++)`.
 *
 * ---------------------------------------------------------------------------
 * THE OPEN QUESTION: the 20 unexplained bytes
 * ---------------------------------------------------------------------------
 * Measured frame map (framesize 0xD8 = 216):
 *      0x00-0x17  arg build (16) + 8 pad for the 8-aligned sdc1
 *      0x18-0x1F  $f20
 *      0x20-0x43  s0..s8
 *      0x44       ra
 *      0x48-0x5F  compiler temp area (24 bytes, measured: it absorbs the
 *                 8-byte rounding, 20 at framesize 0xC0, 24 at 0xC8/0xD8)
 *      0x60-0xD7  DECLARED LOCALS, 120 bytes, TOP-DOWN in declaration order
 *
 * Slot map that produces score 0 (top-down = first declared is highest):
 *      0xD4  type          <- justified
 *      0xD0  obj           <- justified
 *      0xCC  pos           <- justified
 *      0x8C  mtx[4][4]     <- justified (s4 = sp+0x8C, mtx[3][0] = 0xBC)
 *      0x88  actor         <- justified
 *      0x84  i             <- justified, SPILLED (sw zero,0x84 / lw v0,0x84)
 *      0x80  k             <- justified
 *      0x7C  ????          <- UNEXPLAINED (1 word)
 *      0x70  v[3]          <- justified, SPILLED (0x70/0x74/0x78)
 *      0x60  ???? ???? ???? ????   <- UNEXPLAINED (4 words / 16 bytes)
 *
 * Only `i` and `v` are ever touched; everything else is a declared-but-unspilled
 * home, which is exactly the FRAME LAW AMENDMENT (the home AREA is sized by the
 * DECLARED count even though only spilled locals occupy slots).
 *
 * Candidates considered and NOT adopted, because none is provable:
 *   - `idx` and `count` as declared-but-dead locals (2 words). Making them LIVE
 *     breaks the match: golden reloads both from memory every iteration, so a
 *     live local would have to be spilled and golden has no slot for it.
 *   - `f32 v[4]` instead of `f32 v[3]` (absorbs the 0x7C word: a homogeneous
 *     coord vector with [3] unused is a natural N64 idiom) plus a second dead
 *     `f32 w[4]` at 0x60. This DOES fit the slot map exactly and is the single
 *     most plausible story, but "second dead vec4" is still invention.
 *   - a 12-byte second vector `f32 ox,oy,oz` at 0x64-0x6F mirroring the matched
 *     sibling func_15114348 (which really does declare dx,dy,dz + ox,oy,oz),
 *     plus 2 words. Fits, also unprovable.
 * Sibling functions func_151135C4 (frame 0x50) and func_151137D4 (frame 0x30)
 * were checked for a shared declaration template -- they do NOT share one.
 *
 * TO CLOSE: find any evidence for those 5 words (a sibling in another TU with
 * the same loop shape and MORE of them live, or a matching function elsewhere
 * that spills one of them). Then swap the probes for the real names. Nothing
 * else about this function is in doubt.
 *
 * ---------------------------------------------------------------------------
 * THIRD PASS 2026-08-23 -- TWO HYPOTHESES KILLED, AND THE QUESTION IS SHARPER
 * ---------------------------------------------------------------------------
 * 1. IT IS NOT A BUILD-FLAG PROBLEM. -g3 was shown today to change codegen enough to block
 *    three other functions entirely (game_21C4F0 and game_21D420 shipped byte-perfect once
 *    their TUs were pinned to plain -O2), so it was worth asking whether the 20 bytes are
 *    compensating for the wrong flags. They are not. Scored with and without the probes at
 *    every usable flag set:
 *        with probes     -O2 -g3 = 0    -O2 = 20    -O1 = 783   -g = 965
 *        without probes  -O2 -g3 = 26   -O2 = 45    -O1 = 783   -g = 965
 *    No flag set matches the honest source. -O2 -g3 is correct for this TU.
 *
 * 2. THE SHAPE OF THE MISSING LOCALS IS UNDETERMINED, AND CANNOT BE MEASURED.
 *    It is tempting to read the probe slots (0x7C, then 0x6C/0x68/0x64/0x60) as "one 16-byte
 *    object plus one word", since the last four are contiguous. THAT REASONING IS CIRCULAR:
 *    those addresses are where IDO put THIS FILE'S probes, not evidence about golden. Measured
 *    directly, every one of these scores 0 at the same frame -0xD8:
 *        5 scalars | 1 word + f32[4] | 1 word + s32[4] | 1 word + f32[2][2] | 1 word + f32[5]
 *    and both of these score 26 at -0xD0:
 *        f32[4] alone | 1 word + f32[3]
 *    So the ONLY thing that matters is that the declared locals total enough bytes to reach
 *    frame -0xD8. Any filler of the right size works, which is precisely why filler is banned
 *    and why the score of 0 proves nothing about the source.
 *
 * WHAT WOULD ACTUALLY SETTLE IT: not another measurement. The residue is 20-24 bytes of
 * declared locals whose identity the emitted code cannot reveal, because they are never read
 * or written. Only understanding what this function was written to compute -- from its
 * callers, its siblings, or the data it touches -- can name them. Until then the pragma stays.
 *
 * ========================================================================== */

/* ============================================================================
 * SECOND PASS ON THE OPEN QUESTION  --  VERDICT: STILL NOT IDENTIFIED
 * (nothing above is retracted; everything below is new measurement.)
 *
 * I could NOT name the unexplained words from evidence, so the pragma stays.
 * But three things about the question are now settled that were not before,
 * and the budget is SMALLER than the header above states.
 *
 * ---------------------------------------------------------------------------
 * 1. THE FRAME LAW, MEASURED -- the overhead is 92 and is NOT negotiable
 * ---------------------------------------------------------------------------
 * Under -O2 -g3 IDO gives EVERY declared automatic a stack home whether or not
 * it is ever spilled, so framesize reads out the declared-local total directly:
 *
 *     framesize = roundup8( OVERHEAD + declared_local_bytes )
 *
 * with the locals packed TOP-DOWN from framesize (first declared = highest).
 * Measured by sweeping trailing `s32 pad;` declarations (0..9) on this body:
 *
 *     declared L :  100  104  108  112  116  120  124  128  132  136
 *     framesize  : 0xC0 0xC8 0xC8 0xD0 0xD0 0xD8 0xD8 0xE0 0xE0 0xE8
 *
 * => OVERHEAD = 92 exactly, and framesize 0xD8 pins L to {120, 124}.
 *    (NOTE: the frame CANNOT distinguish 120 from 124 -- an 8-byte rounding
 *    slack is real. Both score 0. So the tail is "16 or 20 bytes", not "20".)
 *
 * OVERHEAD 92 decomposes as, measured against standalone IDO probes:
 *      0x00-0x0F  argument build      16   (= roundup8(max(16, nargs*4)))
 *      0x10-0x17  FP-save-area pad     8   (appears IFF any $f2x is saved;
 *                                          probes with no FP save have GPRs
 *                                          starting at 0x10 and no hole)
 *      0x18-0x1F  $f20                 8
 *      0x20-0x47  s0..s8, ra          40   (ra at the TOP of the GPR block)
 *      0x48-0x5B  compiler temp/spill 20   (allocated, NEVER referenced)
 *
 * The 20-byte temp area at 0x48 is NOT a lever. It is invariant across six
 * separate body mutations -- deleting the func_150442C0 call, the three
 * trunc.w.s/sh writebacks, the second func_150A7CB0, the three mtx[3][*]
 * stores, the func_1511490C call, and the whole `type < 3` arm -- overhead
 * stayed 92 in all six. It only moves when the emitted CODE changes (gutting
 * the body to a bare double loop drops it to 80). Since a score-0 candidate by
 * definition emits golden's code, its overhead is 92. There is no honest
 * spelling that buys frame bytes back from the temp area.
 *
 * ---------------------------------------------------------------------------
 * 2. THE SLOT MAP IS FULLY PINNED -- and the budget is 16 bytes, not 20
 * ---------------------------------------------------------------------------
 * Verified by scoring layout variants in-file (all reported as fastscore mism):
 *
 *   [3 words] [mtx 64B @0x8C] [1 word @0x88] [i @0x84] [1 word @0x80]
 *   [v @0x70] [TAIL 16 or 20 bytes @0x60..0x6F/0x5C..0x6F]
 *
 *   - `i` MUST land at sp+0x84 (it is the only spilled scalar). Promoting i/k
 *     above mtx and demoting obj/pos scores 6, not 0.
 *   - the ORDER of the three words above mtx is free: type/obj/pos and
 *     obj/pos/type both score 0. The binary does not determine it.
 *   - THE IMPROVEMENT: spelling the offset vector `f32 v[4]` instead of
 *     `f32 v[3]` scores 0 (verified) and ABSORBS the stray 0x7C word. That
 *     leaves all SIX named scalars (type/obj/pos/actor/i/k) sitting on their
 *     original homes with no dead scalar wedged among them, and reduces the
 *     unnamed part to ONE CONTIGUOUS TRAILING BLOCK of 16 bytes at 0x60-0x6F:
 *
 *         s32 type; Obj *obj; Pos *pos; f32 mtx[4][4];
 *         Actor *actor; s32 i; s32 k; f32 v[4];   <- w unused, 4-wide vector
 *         s32 pad[4];                             <- 16 B, sp+0x60..0x6F
 *
 *     Measured score-0 spellings: v4+pad[4], v4+pad[5], v4+f32 w[4],
 *     v4+f32 w[3]+s32, v3+word+pad[4], v3+word+pad[5]. All 0. The instruction
 *     stream cannot tell them apart; only the total 120/124 is observable.
 *
 * ---------------------------------------------------------------------------
 * 3. CORPUS BASE RATE FOR THIS EXACT SITUATION (full scan, this pass)
 * ---------------------------------------------------------------------------
 * Scanned every leading declaration block in conker/src (1616 matched
 * functions with a parseable block; parser handles `T (*name)[4]` forms):
 *      53 matched functions carry >=1 declared-but-never-referenced local
 *      294 dead bytes in total
 *      LARGEST DEAD BLOCK ANYWHERE = 16 BYTES, and it occurs three times:
 *        game_19A8B0/func_1516F024   s32 pad[4];   (declared FIRST)
 *        game_10B7D0/func_150DE458   s32 pad[4];   (declared FIRST)
 *        game_57FA0 /func_1502B9B4   s32 pad[3]; + s32 pad0;
 *      next: game_1FA770/func_151CD3CC  s32 unused[3];  (12 B)
 * Two of them ship a standard rationale comment, verbatim from game_19A8B0:
 *      "Reserves the 16 bytes at the top of the -g3 stack frame (sp+0x58..0x67)
 *       that the shipped build allocated but never referenced.  Declared first
 *       so the remaining locals land on their original stack homes."
 * So the project ALREADY ships 16-byte unnamed reservations, with precedent and
 * a comment convention -- the header above understated the precedent (it knew
 * only func_150FDDA0's single `s32 unused;`). A 16-byte tail here would TIE the
 * corpus record; a 20-byte tail would EXCEED it. That is the honest weight:
 * precedent exists at exactly this size, but no evidence NAMES these bytes, and
 * "16 vs 20" is not even decidable from the binary. Ranking-tie territory.
 *
 * ---------------------------------------------------------------------------
 * 4. RULED OUT THIS PASS, WITH REASONS
 * ---------------------------------------------------------------------------
 *  - No ROM duplicate to difference against. Only four functions in the whole
 *    corpus touch D_800DBEE8 (func_15112A80, this one, func_151135C4,
 *    game_1B5CC0/func_15188F84) and only this one also calls guMtxF2L. The
 *    three other users of the -100*0x32C actor bias 0xFFFEC2D0
 *    (game_11FF10/func_150F2A60, /func_150F34F4, game_EB020/func_150BDB70)
 *    are all still pragmas, so none can be read for a declaration template.
 *  - Nearest MATCHED relatives declare no such block, so no twin calibrates it:
 *      game_138520/func_1510B690 -- same `for (i = 0; i <= D_80082FA0; i++)`
 *        chunk loop + guMtxF2L; declares only `s32 i; f32 sp4C[4][4];
 *        f32 (*d9d10)[4][4];`  no pad.
 *      game_185560/func_1515858C, /func_15158920 -- matrix build + guMtxF2L;
 *        func_15158920 does carry ONE dead word, `f32 (*unused)[4];`, wedged
 *        between two live locals. Closest shape found; one word, not four.
 *      in-TU: func_15114348 (dx,dy,dz,ox,oy,oz,mtx,tmp,axes[3][3]),
 *        func_1511490C / func_151148A8 (one f32[4][4] each) -- all fully used.
 *  - Structural rewrites that would DISSOLVE the tail all break the pinned map:
 *      bigger mtx ([5][4] or [4][5]) moves mtx[3][0] off 0xBC;
 *      putting the pad above mtx moves mtx off 0x8C;
 *      `f32 v[8]`/`f32 v[2][4]` at 0x60 would fit the arithmetic exactly (used
 *        elements land on 0x70/0x74/0x78) but requires the code to index
 *        v[4..6] / v[1][0..2] for no reason -- rejected as invention, not
 *        evidence;
 *      `f32 v[2][3]` or three s16 write-back locals mis-align v off 0x70.
 *  - The three floats are NOT compiler arg-homing temps: the temp area lives at
 *    0x48-0x5B, below the declared locals, and 0x70/0x74/0x78 sit inside the
 *    declared-local region. The MEMORY-RESIDENT VECTOR law above stands.
 *
 * ---------------------------------------------------------------------------
 * 5. WHAT WOULD ACTUALLY CLOSE IT
 * ---------------------------------------------------------------------------
 *  (a) Any of func_15112A80 / func_151135C4 / func_15188F84 / func_150F2A60 /
 *      func_150F34F4 / func_150BDB70 reaching a match: they are the only code
 *      in the ROM written against the same tables, and a declaration template
 *      with a live 16-byte local in that family would name this block.
 *  (b) A lead ruling that a documented 16-byte `s32 pad[4]` reservation is in
 *      policy here as it already is in three shipped functions. That is a
 *      POLICY call, not a decompilation finding, so I did not take it.
 * Everything else about this function remains settled; only the tail is open.
 * ========================================================================== */

/* ---- header block: paste above the pragma in src/game_13D350.c ---- */

extern u16 D_800DBEE8[];
extern f32 D_800DBF08[][4][4];

typedef struct {
    /* 0x00 */ u16 unk0;
    /* 0x02 */ u16 unk2;
} Entry15113218; /* size 0x4 */

extern Entry15113218 **D_80089240[];
extern Mtx **D_80089250[];

typedef struct {
    u8  pad0[0x30];
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
} Struct15113218Pos;

/* struct127 (the 0x32C actor record) with the fields this function needs;
   the shared header types 0x90 as u16 but golden loads it signed (`lh`). */
typedef struct {
    u8  pad0[0x14];
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    u8  pad20[0x70];
    /* 0x90 */ s16 unk90;
    u8  pad92[0x142];
    /* 0x1D4 */ Struct15113218Pos *unk1D4;
    u8  pad1D8[0x154];
} Struct15113218Actor; /* size 0x32C */

/* struct131 (the 0xA0 object record) with the fields this function needs. */
typedef struct {
    u8  pad0[0x10];
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14;
    u8  pad16[0x16];
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ s32 unk30;
    /* 0x34 */ s32 unk34;
    u8  pad38[0x16];
    /* 0x4E */ u8  unk4E;
    u8  pad4F[0x21];
    /* 0x70 */ u8  unk70;
    u8  pad71[0x2F];
} Struct15113218Obj; /* size 0xA0 */

void func_150A7B80(Mtx *arg0);
struct Struct1511490C;
void func_1511490C(f32 arg0[4][4], struct Struct1511490C *arg1);

/* ---- the function: SCORE 0 exactly as written ---- */

/* ALTERNATIVE SPELLING found on the second pass -- ALSO SCORE 0, and strictly
 * better evidence-wise: every named local sits on its original home, no dead
 * scalar is wedged between live ones, and the unnamed part collapses to ONE
 * contiguous 16-byte trailing block (sp+0x60..0x6F) -- the same size and shape
 * the project already ships in game_19A8B0/func_1516F024 and
 * game_10B7D0/func_150DE458. Left COMMENTED because naming those 16 bytes is
 * still unproven; swap it in only on a lead ruling.
 *
 *     s32 type;
 *     Struct15113218Obj *obj;
 *     Struct15113218Pos *pos;
 *     f32 mtx[4][4];
 *     Struct15113218Actor *actor;
 *     s32 i;
 *     s32 k;
 *     f32 v[4];      -- 0x70..0x7F, w component unused
 *     s32 pad[4];    -- 0x60..0x6F, allocated by the shipped build, never referenced
 *
 * (function body identical to the one below, unchanged.)
 */

void func_15113218(void) {
    s32 type;
    Struct15113218Obj *obj;
    Struct15113218Pos *pos;
    f32 mtx[4][4];
    Struct15113218Actor *actor;
    s32 i;
    s32 k;
    s32 probe1;            /* OPEN QUESTION -- 0x7C */
    f32 v[3];
    s32 probe2;            /* OPEN QUESTION -- 0x6C */
    s32 probe3;            /* OPEN QUESTION -- 0x68 */
    s32 probe4;            /* OPEN QUESTION -- 0x64 */
    s32 probe5;            /* OPEN QUESTION -- 0x60 */

    for (i = 0; i <= D_80082FA0; i++) {
        if (func_150859AC(i, 0) == 0) {
            continue;
        }
        for (k = 0; k < D_800DBEE8[i]; k++) {
            obj = (Struct15113218Obj *)&D_800DBEF4[(*D_80089240[i])[k].unk0];
            if ((obj->unk70 & 1) == 1) {
                func_150A7B80(&(*D_80089250[D_800BE9C0])[(*D_80089240[i])[k].unk0]);
                continue;
            }
            type = obj->unk4E;
            if (type == 3) {
                continue;
            }
            if (type < 3) {
                func_1511490C(mtx, (struct Struct1511490C *)obj);
                guMtxF2L(mtx, &(*D_80089250[D_800BE9C0])[(*D_80089240[i])[k].unk0]);
            } else if ((type > 100) && (type < 125)) {
                actor = (Struct15113218Actor *)((type * 0x32C - 0x13D30) + (s32)D_800CC2D0);
                if (actor->unk1D4 == NULL) {
                    func_150A7CB0(mtx, obj->unk2C, obj->unk30, obj->unk34);
                    mtx[3][0] = actor->unk14;
                    mtx[3][1] = actor->unk18;
                    mtx[3][2] = actor->unk1C;
                    guMtxF2L(mtx, &(*D_80089250[D_800BE9C0])[(*D_80089240[i])[k].unk0]);
                } else {
                    v[2] = 0.0f;
                    v[0] = v[2];
                    v[1] = actor->unk90;
                    pos = actor->unk1D4;
                    func_150A7CB0(mtx, obj->unk2C, obj->unk30, obj->unk34);
                    mtx[3][0] = pos->unk30;
                    mtx[3][1] = pos->unk34;
                    mtx[3][2] = pos->unk38;
                    func_150442C0(mtx, v[0], v[1], v[2]);
                    obj->unk10 = mtx[3][0];
                    obj->unk12 = mtx[3][1];
                    obj->unk14 = mtx[3][2];
                    guMtxF2L(mtx, &(*D_80089250[D_800BE9C0])[(*D_80089240[i])[k].unk0]);
                }
            } else {
                guMtxF2L(D_800DBF08[D_800BE9C0], &(*D_80089250[D_800BE9C0])[(*D_80089240[i])[k].unk0]);
            }
        }
    }
}
