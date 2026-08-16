/* func_150F64DC  (game_1228D0.c, 884 B, COLD decompile this wave)
 * BOUNDED SCORE (--max-lines 221 == 884/4, the symbol's own instruction count):
 *      140 on the FIRST build, then 120 with -R and 120 without -R.
 * (The default window is noise here -- ALWAYS pass --max-lines 221.)
 * NOT SHIPPED: the #pragma in conker/src/game_1228D0.c is RESTORED and that file
 * is pristine (`git status --short -- conker/src/game_1228D0.c` prints nothing).
 *
 * ============================ WHAT IS LEFT ============================
 * 120 == EXACTLY TWO REORDERING PENALTIES (asm-differ penalty_reordering = 60).
 * The frame is EXACT (0xC8, every local at golden's offset, stack-offset multiset
 * IDENTICAL to golden -- verified by permuter_tu.sh frame: "base.c MATCHES golden
 * (77 displacements)").  Every register pick is identical.  Every instruction is
 * present.  The whole residual is that two instructions are scheduled 2-3 slots
 * early in one basic block:
 *
 *   golden                              mine
 *   11d0 andi  s3,v0,0x1                11d0 andi  s3,v0,0x1
 *   11d4 addiu s3,s3,2                  11d4 lw    t7,0xc0(sp)        <- hoisted
 *   11d8 sll   t5,s3,0x18               11d8 addiu s3,s3,2
 *   11dc sra   s3,t5,0x18               11dc sll   t5,s3,0x18
 *   11e0 lw    t7,0xc0(sp)              11e0 lui   a0,%hi(D_800A1B30) <- hoisted
 *   11e4 lui   a0,%hi(D_800A1B30)       11e4 sra   s3,t5,0x18
 *   11e8 addiu a0,a0,%lo(D_800A1B30)    11e8 addiu a0,a0,%lo(D_800A1B30)
 *
 * Golden emits the `count` sign-extension chain and the func_15143134 argument
 * setup as two UNINTERLEAVED runs (i.e. plain source order); my build fills the
 * two latency slots of the chain with the first two instructions of the call
 * setup.  Same multiset, same registers, same relative order -- only the two
 * hoists differ.  RESIDUAL CLASS: SCHEDULING (as1), 2 moves.
 *
 * ---------------- HOW THE SHAPE WAS OBTAINED (STEP ZERO PAID AGAIN) ----------
 * func_150DFEFC in conker/src/game_10CD70.c is a MATCHED sibling with the same
 * emitter-object shape, the same first early-out, the same
 * `src->timerN -= D_800BE9E4; if (< 0)` idiom, the same Header/Header2 pair fed
 * to func_151602C0 with the SAME 11-argument pattern, and the same
 * `s8 count; do {...} while (count > 0);` particle loop with a u8 colour[4].
 * Its declaration list
 *      SmokeSource *src; struct127 *obj; Header header; Header2 header2; s8 count;
 * plus a block-scoped `u8 colour[4]` was reused directly, and the frame came out
 * EXACT on build #1 (score 140).  Reuse the SmokeSource/SmokeEmitter field map
 * verbatim -- +0x0 obj, +0x4 id, +0x6/8/A timers, emitter +0x1, +0xC, +0xE, +0x28.
 *
 * ---------------- FRAME DECODE (quote) ----------------
 * framesize 0xC8.  Saved regs [0x40,0x80): f20@0x40 f22@0x48 f24@0x50,
 * s0..s7 @0x58..0x74, fp@0x78, ra@0x7C.  Arg-build [0x00,0x38) -- func_15107C1C
 * takes 14 args so the highest arg slot is sp+0x34.  Temps [0x80,0x98) (src
 * spills to 0x84).  LOCALS = [0x98,0xC8) = 0x30, TOP-DOWN in declaration order:
 *      src     [0xC4,0xC8)   4
 *      obj     [0xC0,0xC4)   4   <- obj spills to its OWN home: `sw v0,0xC0(sp)`
 *      count   [0xBC,0xC0)   4   (an s8 local still gets a 4-byte slot)
 *      pos     [0xB0,0xBC)  0xC  (func_15143134 writes 3 floats here)
 *      header  [0xA8,0xB0)  6+2  (Header is size 6, padded to pos's 4-alignment)
 *      header2 [0x9C,0xA8)  0xC
 *      colour  [0x98,0x9C)   4   (block-scoped u8[4], declared last)
 * sum = 4+4+4+12+8+12+4 = 0x30 EXACT.
 * CROSS-CHECK against the matched sibling func_150DFEFC: framesize 0xB0, same
 * law -- src[0xAC] obj[0xA8] header[0xA0] header2[0x94] count[0x90] colour[0x8C]
 * = 0x24 -- and there too `obj` spills to its OWN home (0xA8) while `src` spills
 * to a TEMP (0x78), exactly as here (obj -> 0xC0 home, src -> 0x84 temp).
 * NEW LAW WORTH BANKING: a pointer local that is live across many calls spills to
 * its declaration home; a pointer local that is merely an address CSE (`&arg->f`)
 * gets a temp slot instead.  Both siblings show it.
 *
 * ---------------- CALLEE PROTOTYPES, ALL SIX VERIFIED ----------------
 *  func_150ADA20  -- functions.h says u8; golden feeds v0 straight into `divu`
 *                    with NO andi 0xff, so it is a word.  FILE-LOCAL SHADOW ADDED
 *                    (game_1228D0.c had none).  No other function in the TU
 *                    references it, and every previously-matched function in the
 *                    TU was re-verified byte-identical afterwards (see below).
 *  func_150ADA68  -- functions.h `f32 (void)`, correct as-is.
 *  func_10010F88  -- functions.h (s32,u16,s16,u8,s32,s16,s16,s16,s16,s16) works
 *                    UNCHANGED, no shadow needed.
 *  func_15143134  -- (void*, void*, s32); same as game_11C2B0.c / game_14FF90.c.
 *  func_151602C0  -- (Header*,Header2*,s32,s32,s32,s32,u8,u8,s32,u8,s32), copied
 *                    verbatim from the matched caller in game_10CD70.c:287.
 *  func_15107C1C  -- (struct127*,u8,void*,s16,s16,s16,s32,f32,f32,s16,s16,u8*,u8,
 *                    s32), from its own matched DEFINITION in game_133190.c:402.
 *                    Return value discarded, so declared `void *` here.
 * NEW LAW MEASURED HERE: an `(s16)` cast on a STACK-passed argument costs ZERO
 * instructions, while the same cast on a REGISTER-passed argument costs
 * `sll 16 / sra 16`.  Golden shows exactly that asymmetry (a3 gets sll/sra,
 * sp+0x10 and sp+0x14 do not) because the callee re-reads a stack-passed short
 * with `lh` at offset+2.  The matched func_15107700 call inside func_150DFEFC
 * shows the register-arg half of the law three times over.  So a golden stack
 * argument with no visible truncation does NOT disprove an s16 prototype.
 *
 * ---------------- LOOP-INVARIANT HOISTING (reproduced with no reordering) -----
 * s5=0x65, s6=0x2B, s7=0x12 and f20=27.0f, f22=16.0f, f24=20.0f are hoisted out
 * of the do-while, ranked by SOURCE POSITION OF FIRST USE, and came out right
 * first time: 0x65 (colour[3]) < 0x2B (arg4) < 0x12 (arg5); 27.0f (arg7) <
 * 16.0f (arg8's multiply) < 20.0f (arg8's add).
 *
 * ======================= MEASURED VARIANT LOG =======================
 * Base for everything below is the live-C build.  All bounded, --max-lines 221.
 * WIN (140 -> 120), found by the permuter and kept:
 *   `(obj->unique_id != src->id)` instead of `(src->id != obj->unique_id)` in the
 *   first early-out.  Worth 20 (four regalloc penalties).  It is also the operand
 *   order the matched sibling func_150DFEFC uses -- STEP ZERO would have given it
 *   for free; I typed the operands the other way round and paid 20 points for it.
 *
 * NEGATIVES, all measured against the 140 base (i.e. before the win above), all
 * with framesize 0xC8 and golden's stack-offset multiset:
 *   -- 22 mutually-distinct spellings ALL scored EXACTLY 140.  This is the
 *      N-NO-OPS SIGNATURE: the binary evidences "the scheduler made one different
 *      choice here", not any construct.  Do not spend more builds on spelling.
 *      count spelling:    `2 + (rand & 1)`; `(s8)((rand & 1) + 2)`
 *      call spelling:     `(s32)obj->unk1D4`; `&pos.x`; `&D_800A1B30[0]`
 *      globals:           `extern f32 D_800A1B30[]`; `extern f32 D_800A1B30;`+`&`;
 *                         `extern Vec D_800A1B30;`+`&`
 *      prototypes:        func_15143134 3rd arg as `struct255 *`; func_15143134
 *                         returning s32; func_15107C1C returning void
 *      locals:            `f32 pos[3]` instead of a 3-float struct; colour[4] at
 *                         function scope instead of block scope; declaration order
 *                         count,obj,src instead of src,obj,count
 *      structure:         the two early-outs combined into one `||`; the two
 *                         early-outs nested; the timer `if` inverted to an early
 *                         return with the body at top level; `src = &arg0->src`
 *                         assigned before `obj = arg0->src.obj`
 *      -g3 LINE PLACEMENT (the "adjacent-pair line JOIN" reading): joining the
 *                         count statement to the func_15143134 call onto one line,
 *                         joining it to the preceding func_10010F88 line, and
 *                         joining the call to the following header.unk0 line --
 *                         ALL THREE BYTE-IDENTICAL.  The line-join lever DID NOT
 *                         REPRODUCE HERE EITHER.  Treat it as dead.
 *   WORSE:
 *      620   `count = func_150ADA20() & 1; count += 2;`   (splitting the statement)
 *      700   `func_15143134(..., src->obj->unk1D4)` instead of `obj->unk1D4`
 *      222   declaring header2 BEFORE header (confirms header is declared first)
 *
 * ================= WAVE N+1 (this session): 5 MORE MEASURED NEGATIVES =======
 * Base re-verified at 120 after re-applying the parked source to game_1228D0.c
 * (bounded --max-lines 221).  Sweep harness carried a CONTROL that fired, so the
 * uniform readings below are real, not the CRLF/no-op harness trap:
 *      base       120     count = (func_150ADA20() & 1) + 2;
 *      mod2U      120     count = (func_150ADA20() % 2U) + 2;
 *      u32mod2    120     count = ((u32)func_150ADA20() % 2U) + 2;
 *      mod2Uadd   120     count = 2 + (func_150ADA20() % 2U);
 *      mod2       585     count = (func_150ADA20() % 2) + 2;     <- CONTROL fired
 *      CTRLand3   125     count = (func_150ADA20() & 3) + 2;     <- CONTROL fired
 * WHY `% 2U` WAS WORTH TESTING AND WHY IT IS NOW DEAD: every other RNG use in
 * this function and in the matched sibling func_150DFEFC is spelled `% NU`
 * (`% 9U`, `% 0x3DU`, `% 0x65U`, `% 0x2BU`, `% 0x12U`, `% 0x5BU`), so `& 1` was
 * the odd one out and `% 2U` strength-reduces to the same `andi`.  It is a
 * DIFFERENT ucode operation reduced at a different point in the pipeline, which
 * is exactly the class of change that moved func_1515589C by 1000 points this
 * wave -- and here it is byte-identical.  The count expression is now exhausted.
 *
 * ALSO SETTLED THIS WAVE:
 *  -- The interleave is NOT introducible/removable by the count spelling, so it
 *     is not an operand-readiness effect on the chain's INPUT.
 *  -- `cc -S` CANNOT be used to separate ugen from as1 here: the recompiled IDO
 *     segfaults ("Fatal error in: /usr/lib/ugen  Signal 11 - core dumped") on
 *     -S with `-32 -O2 -g3 -mips2 -o32` over the asm-processor output.  Do not
 *     re-attempt; find another way to see the pre-as1 stream if that matters.
 *  -- conker/Makefile:146-149 documents that **IDO ITSELF SCHEDULES at -g3**
 *     (it hoists `addiu sp,sp,N` into the `jr ra` delay slot, which -g0 does
 *     not).  So this residual is most likely ugen's scheduler, not as1's, and
 *     the lever is therefore a ucode-shape change, not an as1 hazard.
 *  -- Read the matched sibling func_150DFEFC in full (game_10CD70.c:265-310).
 *     It does NOT contain the adjacency in question -- its `count = ...;` is
 *     immediately followed by `do {`, never by a call whose first argument is a
 *     %hi/%lo global -- so it is NOT ground truth for this ordering after all.
 *     Its declaration order is also different (src, obj, header, header2, count;
 *     count LAST), whereas this function's frame pins src, obj, count, pos,
 *     header, header2.  Do not expect the sibling to settle the ordering.
 *
 * NEXT THINGS TO TRY, in order:
 *   1. the TU-aware permuter is set up and selftested at $HOME/perm/func_150F64DC
 *      (permuter_tu.sh, base chained to the 120 source).  Selftest: (a) PASS,
 *      (b) PASS harness object == Makefile object, (b2) PASS pycparser round trip
 *      codegen-neutral, (c) base score 140 == asm-differ, (d) PASS negative
 *      control 140 -> 510, (e) isolation DIFFERS from the in-TU build, so the
 *      TU-aware harness is LOAD-BEARING here -- a stock single-function permuter
 *      would optimise the wrong bytes.  Run it with
 *        PERMUTER_TU_REQUIRE_FRAME=200 PERMUTER_TU_REQUIRE_OFFSETS=1 \
 *          ./permuter_tu.sh run $HOME/perm/func_150F64DC -j 12 --best-only --stop-on-zero
 *      (both gates are safe: the base already matches golden's frame AND its
 *      full stack-offset multiset, so the search cannot buy register wins by
 *      moving the frame.)  ~11k iterations from the 140 base produced exactly one
 *      improvement, the operand swap above.
 *   2. the two hoisted instructions are the ONLY thing between this and zero.  If
 *      a lever exists it is something that changes as1's ready-list priority
 *      without changing the instruction multiset -- look for a matched function
 *      elsewhere in the corpus that has an s8 counter initialised from an RNG
 *      call IMMEDIATELY followed by a call whose first argument is a %hi/%lo
 *      global, and copy its spelling exactly.  (func_150DFEFC is NOT such a
 *      function -- checked this wave, see above.  Widen the search to any
 *      matched caller of func_15143134: game_11C2B0.c and game_14FF90.c both
 *      call it, and whichever one has a live value spilled to a local home
 *      immediately before the call will show whether golden's uninterleaved
 *      form is normal or exceptional.)
 *   3. THE UNTESTED CLASS.  Everything measured so far changes the count
 *      statement or the call's spelling -- i.e. the two statements that are
 *      being interleaved.  What has NEVER been varied is the code BEFORE the
 *      block: the `func_10010F88` 10-argument call whose stack stores
 *      (`sw t2,0x1c(sp)`, `sw t3,0x20(sp)`, `sw t4,0x24(sp)`) and the two
 *      spills `sw v1,0x84(sp)` / `sw v0,0xc0(sp)` sit immediately above it.
 *      `lw t7,0xc0(sp)` is a LOAD FROM THE SLOT ONE OF THOSE STORES WROTE, so a
 *      store/load alias edge is the one mechanism that could pin it in place --
 *      and that edge exists only if ugen's scheduler treats the region as one
 *      scheduling unit rather than stopping at the `jal func_150ADA20`.  Vary
 *      the func_10010F88 argument expressions (which of them are stack-passed,
 *      and their evaluation order) and watch whether `lw t7,0xc0(sp)` moves.
 */

/* ---- BEST MEASURED VERSION (120).  Paste over the pragma in game_1228D0.c ----
 * and add the func_150ADA20 shadow at the top of the TU:
 *     #include <ultra64.h>
 *     #define func_150ADA20 func_150ADA20_u8_decl_in_functions_h
 *     #include "functions.h"
 *     #undef func_150ADA20
 *     s32 func_150ADA20(void);
 *     #include "variables.h"
 */

typedef struct {
    /* 0x00 */ struct127 *obj;
    /* 0x04 */ u8  id;
    /* 0x05 */ u8  pad5;
    /* 0x06 */ s16 timer0;
    /* 0x08 */ s16 timer1;
    /* 0x0A */ s16 timer2;
} Src150F64DC; /* size 0xC */

typedef struct {
    /* 0x00 */ u8  pad0;
    /* 0x01 */ u8  unk1;
    /* 0x02 */ u8  pad2[0xA];
    /* 0x0C */ u8  unkC;
    /* 0x0D */ u8  padD;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ u8  pad10[0x18];
    /* 0x28 */ Src150F64DC src;
} Emitter150F64DC;

typedef struct { f32 x; f32 y; f32 z; } Vec150F64DC;

extern f32 D_800A1B30[3];
extern void func_15143134(void *, void *, s32);
extern struct225 *func_151602C0(Header *, Header2 *, s32, s32, s32, s32, u8, u8, s32, u8, s32);
extern void *func_15107C1C(struct127 *, u8, void *, s16, s16, s16, s32, f32, f32, s16, s16, u8 *, u8, s32);

void func_150F64DC(Emitter150F64DC *arg0) {
    Src150F64DC *src;
    struct127 *obj;
    s8 count;
    Vec150F64DC pos;
    Header header;
    Header2 header2;

    obj = arg0->src.obj;
    src = &arg0->src;
    if ((obj->interaction_state == 0) || (obj->unique_id != src->id)) {
        arg0->unkE = -1;
        return;
    }
    if (obj->unk1D4 == 0) {
        return;
    }
    if (obj->unk94 & 2) {
        return;
    }
    src->timer0 -= D_800BE9E4;
    if (src->timer0 < 0) {
        u8 colour[4];

        func_10010F88(0x679, 0x18CE, 0, 0, 0, (s32)obj->x_position, (s32)obj->y_position, (s32)obj->z_position, 0x7918, 0x7D00);
        count = (func_150ADA20() & 1) + 2;
        func_15143134(D_800A1B30, &pos, obj->unk1D4);
        header.unk0 = 3;
        header.unk1 = -1;
        header.unk2 = (func_150ADA20() % 9U) + 0xA;
        header.unk4 = 0;
        header2.unk0 = (s32)pos.x;
        header2.unk4 = (s32)pos.y;
        header2.unk8 = (s32)pos.z;
        func_151602C0(&header, &header2, (func_150ADA20() % 0x3DU) + 0x3C, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0, arg0->unkC, arg0->unk1);
        do {
            colour[0] = 0xA0;
            colour[1] = 0xA0;
            colour[2] = 0xFF;
            colour[3] = (func_150ADA20() % 0x65U) + 0x9B;
            func_15107C1C(obj, 0, D_800A1B30, (s16)(func_150ADA20() & 0xFF), (s16)((func_150ADA20() % 0x2BU) - 0x32), (s16)((func_150ADA20() % 0x12U) + 5), 4, 27.0f, (func_150ADA68() * 16.0f) + 20.0f, 0, 2, colour, arg0->unkC, arg0->unk1);
            count--;
        } while (count > 0);
        src->timer0 = (func_150ADA20() % 0x5BU) + 0x5A;
    }
}
