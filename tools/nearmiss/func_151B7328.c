/* func_151B7328  (game_1E37D0.c, 848 B)
 * BOUNDED SCORE (--max-lines 212 == 848/4): 668 -> 279, with -R and without -R.
 * NOT SHIPPED: the #pragma in conker/src/game_1E37D0.c is RESTORED and that file
 * is pristine.
 *
 * ############ THE WIN THIS WAVE: 668 -> 279, DECLARATION ORDER ############
 * Declaring the two POINTER scalars FIRST
 *      Obj151B7328 *obj;  u8 *payload;  Header151B7328 header;  Data151B7328 data;
 *      Data151B7328 *dst; Emitter151B7328 emit; Tbl151B7328 tbl;
 *      s32 temp_v0; s32 temp_v1;
 * puts EVERY AGGREGATE AT GOLDEN'S EXACT OFFSET and puts temp_v1's spill at
 * golden's 0x48:
 *      header 0xE4, data 0xD4, dst 0xD0, emit 0x60, tbl 0x50, temp_v1 spill 0x48
 * After that change the ONLY stack differences left in the whole function are
 * the frame instruction itself and the INCOMING-ARGUMENT area:
 *      addiu sp,sp,-0x100  vs  -0x108        (and the matching epilogue)
 *      a0..a3 saved at 0x100/0x104/0x108/0x10C  vs  0x108/0x10C/0x110/0x114
 *      lbu 0x107 / lbu 0x10F / lw 0x110      vs  0x10F / 0x117 / 0x118
 * plus a one-step temp-register rotation (t2<-t8, t9<-t1, t4<-t9, t5<-t4,
 * t0<-t5, t7<-t0, t6<-t7 and a3 <-> v1) which is the usual symptom of exactly
 * one surplus web.  NOTHING ELSE DIFFERS: 233 instructions each, mnemonic-only
 * diff EMPTY, every non-argument stack offset identical.
 * Declaration-order sweep that found it (frame / header offset / score):
 *      h,da,ds,e,t,o,p,v0,v1   0x108  hdr 0xEC  668   <- previous parked order
 *      h,da,ds,e,t,o,p,v1,v0   0x108  hdr 0xEC  676
 *      h,da,ds,e,t,p,v1,v0,o   0x108  hdr 0xEC  684
 *      o,h,da,ds,e,t,v1,v0,p   0x108  hdr 0xE8  512
 *      o,h,da,ds,e,t,p,v1,v0   0x108  hdr 0xE8  504
 *      o,h,da,ds,e,t,p,v0,v1   0x108  hdr 0xE8  496  <- what the permuter found
 *      p,h,da,ds,e,t,o,v0,v1   0x108  hdr 0xE8  496
 *      o,p,h,da,ds,e,t,v0,v1   0x108  hdr 0xE4  279  <- KEEP
 * CAVEAT, AND IT MATTERS: this is a COMPENSATING order, not proven ground truth.
 * The two pointer scalars sitting ABOVE `header` occupy exactly the 8 bytes that
 * the surplus temp reserve steals below, so the aggregates land right for the
 * wrong reason.  Golden is equally consistent with
 *      (A) 9 locals (0xC0) + 0 temp, header declared FIRST, or
 *      (B) 7 locals (0xB8) + 8 temp, order header,data,dst,emit,tbl,obj,temp_v1
 *          (this one also lands header@0xE4 and temp_v1@0x48 exactly)
 * and in BOTH readings my build has 8 surplus bytes.  Do not treat the 279 order
 * as settled; treat the 8 bytes as the blocker.
 *
 * ======================================================================
 * ==  READ THIS FIRST: TWO EARLIER BISECTS OF THIS FUNCTION WERE WRONG. ==
 * ======================================================================
 * Wave N-2 blamed the pair `dst->unk4 = (u8 *)dst + 0x10; memcpy(dst->unk4,...)`.
 * Wave N-1 re-ran that bisect, could not reproduce ANY step of it, and instead
 * concluded the surplus was an unexplained whole-function "reserve".
 * THIS wave ran a clean cumulative-prefix probe that appeared to localise the
 * surplus to the `tbl` pair, and then DISPROVED that too with a control.
 * The controls are recorded below so nobody localises it a fourth time.
 *
 * ---------------- WHAT THE RESIDUAL ACTUALLY IS (proven) ----------------
 * The .text mnemonic sequence is IDENTICAL to golden -- 233 instructions each,
 * `diff` of the mnemonic-only streams is EMPTY.  Confirmed by
 *   mips-linux-gnu-objdump -drz -m mips:4300 <obj> | awk '<func only>'
 * on both objects.  The ONLY differences are:
 *   (1) framesize 0x108 vs golden 0x100, and EVERY local offset is exactly +8;
 *   (2) three register picks that the shift drags with it:
 *         golden `lbu t6,0x107(sp)` / `li t7,0x14`   vs mine `lbu t7` / `li t6`
 *         golden `lw a3,0xD0(sp)`, `addiu a0,a3,0x10`, `sw a0,4(a3)`
 *                                                   vs mine the same on v1
 *         golden's `li t6,14` sits one slot later than mine.
 * CRUCIALLY, the SAVED-REGISTER SLOTS AND THE ARG-BUILD AREA ARE NOT SHIFTED:
 * ra@0x3C and s0@0x38 and the arg slots 0x10..0x28 are at the SAME offsets in
 * both objects.  So the 8 surplus bytes are a block of UNUSED stack sitting at
 * sp+[0x40,0x48), between the saved registers and the bottom of the locals.
 * Mine never references [0x40,0x48) at all.  It is an unused COMPILER-TEMP
 * RESERVE, 8 bytes, and golden's reserve is ZERO.
 *
 *   golden layout: argbuild [0x00,0x2C) | pad [0x2C,0x38) | s0,ra [0x38,0x40)
 *                  | temp (none)        | locals [0x40,0x100) = 0xC0
 *   mine  layout:  argbuild [0x00,0x2C) | pad [0x2C,0x38) | s0,ra [0x38,0x40)
 *                  | TEMP [0x40,0x48)   | locals [0x48,0x108) = 0xC0
 *
 * The declared locals sum to 0xC0 in BOTH -- the aggregate sizes are right:
 *   header 0x1C + data 0x10 + dst 4 + emit 0x70 + tbl 0x10 + 4 scalars 0x10.
 * golden: header@0xE4 data@0xD4 dst@0xD0 emit@0x60 tbl@0x50 scalars[0x40,0x50)
 * mine:   header@0xEC data@0xDC dst@0xD8 emit@0x68 tbl@0x58 scalars[0x48,0x58)
 * golden spills temp_v1 to 0x48 = the 2ND of its four scalars (top-down
 * 0x4C,0x48,0x44,0x40), so golden's scalar declaration order has temp_v1 second.
 * Mine spills temp_v1 to 0x48 too, but for mine that is the FOURTH scalar.
 *
 * ---------------- THE CONTROLS THAT KILLED THE `tbl` READING ----------------
 * Cumulative-prefix probe (all 9 locals declared in every build, statements added
 * in source order; `frame` read off the prologue):
 *      P00 header setup + func_15147A80 only        frame 0xF8  hdr@0xDC
 *      P01 + dst/memcpy1                            frame 0xF8  hdr@0xDC
 *      P02 + payload/dst->unk4/memcpy2              frame 0xF8  hdr@0xDC
 *      P03 + the callback if-block                  frame 0x100 hdr@0xE4  <- GOLDEN
 *      P04 + `tbl = ...; emit.unk1D = tbl.unk0[..]` frame 0x108 hdr@0xEC
 *      P05..P11 (everything else, cumulative)       frame 0x108 hdr@0xEC
 * That looks like a clean localisation onto the tbl pair.  IT IS NOT:
 *      X1  FULL function MINUS the tbl pair, tbl still declared  frame 0x108
 *      X2  FULL function MINUS the tbl pair, tbl decl removed    frame 0xF8
 * X1 is the decisive one: with everything else present, deleting the tbl pair
 * does NOT get the frame back to 0x100.  (X1 vs X2 also proves IDO KEEPS the
 * home of a declared-but-never-referenced local -- exactly 0x10 of difference --
 * so the prefix probe's early rows are confounded by nothing else, but the
 * prefix result still does not transfer to the full function.)
 *
 * EVERY SINGLE-STATEMENT-GROUP REMOVAL FROM THE FULL FUNCTION KEEPS 0x108:
 *      minus dst/memcpy1                       0x108   (wave N-1)
 *      minus payload/dst->unk4/memcpy2         0x108   (wave N-1)
 *      minus the callback if-block             0x108   (wave N-1)
 *      minus the tbl pair                      0x108   (X1, this wave)
 *      minus the emit scalar block             0x108  score 3514
 *      minus the float chain                   0x108  score 3002
 *      minus the three Vec copies              0x108  score 3940
 *      minus emit.unk1E/20/22/54/24            0x108  score  386
 *      minus emit.unk60..66 / unk5C            0x108  score  457
 *      minus the flags if/else block           0x108   (wave N-1)
 *      minus `dst->unk0 = func_15130280(...)`  0x108  score  437
 * => THE 8 BYTES ARE A WHOLE-FUNCTION PROPERTY, NOT A STATEMENT'S.  Stop
 * bisecting statements.  (Note the three scores BELOW 668 in that list: removing
 * code can IMPROVE the number because the +8 shift's reordering cascade shrinks.
 * Partial-removal scores are NOT comparable to the base -- read the FRAME, not
 * the score, when probing this residual.)
 *
 * ---------------- SPELLINGS OF THE tbl PAIR, ALL 0x108 / 668 ----------------
 *      `extern Tbl151B7328 D_800AA460;` + `tbl = D_800AA460;`
 *      `s32 tbl[4];` + `*(Tbl151B7328 *)tbl = *(Tbl151B7328 *)D_800AA460;`
 *      Tbl as four named s32 fields + `(&tbl.unk0)[i]`
 *      `tbl.unk0[(s32)(func_150ADA20() & 3)]`
 *      `(u8)tbl.unk0[func_150ADA20() & 3]`
 * and `extern void *func_15147A80(...)` instead of `extern s32 func_15147A80(...)`
 * (return type pointer vs integer): 0x108 / 668, and func_151B6320 stays at 0.
 *
 * ============ CALIBRATION: THE MATCHED SIBLING IN THIS VERY FILE ============
 * func_151B6320 (top of conker/src/game_1E37D0.c, LIVE C, scores 0) has the same
 * `func_15147A80(<11 args>)` + `memcpy(obj->unk98, &payload, N)` shape and gets
 * TEMP == 0:  framesize 0x90 = argbuild 0x2C + pad 0xC + saved 8 + locals 0x50.
 * Its declaration list is currently written as
 *      s32 top_dummy; Header151B6320 header; s32 pad_dummy;
 *      Payload151B6320 payload; s32 *temp_v0;
 * The two "dummy" locals are almost certainly NOT dummies: 4 + 0x18 + 4 + 0x2C
 * is numerically identical to header 0x1C + payload 0x30, i.e. Header151B6320 is
 * really 0x1C bytes (6 bytes of trailing pad, not 2) and Payload151B6320 is
 * really 0x30.  That is the SAME "the struct is 4-8 bytes bigger than you think"
 * trap that Header151B7328's `u8 pad16[6]` already encodes in this function.
 * Worth fixing there (it removes two unnamed frame-shaping locals from shipped
 * code, which the project's own rules call an open question), and worth
 * remembering as a general law: TRAILING STRUCT PADDING, NOT A DUMMY LOCAL.
 *
 * The other calibration siblings (all pool == 0):
 *   func_15131EE4 (game_15D730.c:370) -- SAME emitter struct (Struct15131EE4Local,
 *      0x70) and the SAME two-if/else flags block; framesize 0xB0, locals 0x90 =
 *      Local 0x70 + Extra 0x14 + three scalars 0xC, temp 0.  It declares
 *      `s32 ret;` capturing func_15130280's return; capturing it HERE grows the
 *      frame to 0x110, so golden's func_151B7328 does NOT capture it.
 *      It also writes `*(struct17 *)&D_800A5480` exactly as this function does,
 *      so that cast is NOT the source of a temp.
 *   func_15151A38 / func_15152F70 (game_17CAF0.c) -- 0xF8 / 0x108, temp 0.
 *
 * ---------------- SCALAR-COUNT SWEEP (wave N-1, still valid) ----------------
 *      2 scalars (obj,temp_v1)                 -> 0x108, 684
 *      3 scalars (obj,payload,temp_v1)         -> 0x108, 676
 *      4 scalars (obj,payload,temp_v0,temp_v1) -> 0x108, 668   <- current
 *      5 scalars (+ s32 ret)                   -> 0x110, 1132
 * Declaration-order permutations of the four (vs the 668 base): 668 for
 * obj,payload,temp_v0,temp_v1; 684 for obj,temp_v1,temp_v0,payload,
 * temp_v0,temp_v1,obj,payload and payload,temp_v1,temp_v0,obj.  NOTE these were
 * all measured with the frame 8 bytes wrong, so per the project's own rule they
 * are STALE the moment the frame is fixed -- golden's temp_v1 is its 2ND scalar,
 * so a reordering that looks bad today may be right once the reserve is gone.
 *
 * ---------------- OTHER MEASURED NEGATIVES (retained) ----------------
 *  - `emit.unk58 = (temp_v0|temp_v1) | 0x4C000;` -> IDO builds 0x4C000 whole
 *    (lui 0x4 + ori 0xC000, ONE `or`).  Golden splits it, so the source must be
 *    `... | 0xC000 | 0x40000`.  Worth ~300.  (Cross-check: the matched
 *    func_15131EE4 writes `temp_v0 | 0x4C000 | temp_v1` and DOES get the
 *    built-whole form, so the two spellings are genuinely separable.)
 *  - `u8 unk62` gives `li 0xff`; golden has `li -1` at unk62/63/64 and `li 0xff`
 *    only at unk66 => unk62..64 must be s8.
 *  - splitting `emit.unk28 = emit.unk2C = X;` into two statements: BYTE-IDENTICAL.
 *  - every cast shape, `dst + 1` vs `(u8 *)dst + 0x10`, ternary vs if/else,
 *    declaring vs not declaring obj/temp_v0/temp_v1/ret: BYTE-IDENTICAL.
 *  - four distinct spellings of the memcpy pair: all 684 (N-no-ops signature).
 *
 * ---------------- TOOLING TRAP THAT COST A WHOLE BATCH ----------------
 * conker/src/game_1E37D0.c has CRLF line endings.  A python variant harness that
 * does `src.replace("        tbl = ...\n...", new)` with '\n' patterns MATCHES
 * NOTHING, str.replace silently returns the original, and EVERY variant reports
 * the BASE score.  I got eight consecutive "668" readings that way, including
 * two that were supposed to delete whole statements.  ALWAYS normalise
 * (`.replace('\r\n','\n')`) AND assert the pattern is present before building --
 * and treat "every variant scored identically" as a harness bug until a control
 * variant that MUST change the score actually does.
 *
 * Rodata pre-filter: CLEAR.  D_800AA460 {0x60,0x61,0x62,0x63} and D_800AA480
 * (1700.0f, low16 = 0x8000 so it can NOT inline) both live in the EXTERNAL asm
 * blob conker/asm/data/24EF20.rodata.s; D_800A5480 in 249F40.rodata.s.  This
 * function is NOT rodata-blocked; its TU .rodata is 0 bytes both sides.
 *
 * NOTE: game_1E37D0.c also contains func_151B65D4, which is BLOCKED. Do not
 * touch it.
 *
 * ---------------- NEXT ----------------
 *   1. The TU-aware permuter is set up at $HOME/perm/func_151B7328, re-seeded
 *      from the 279 source (./permuter_tu.sh setup game_1E37D0 func_151B7328
 *      <live-C copy of the TU>).  Selftest: (b) PASS harness object == Makefile
 *      object, (b2) PASS pycparser round trip codegen-neutral, (c) base score
 *      matches asm-differ, (d) PASS negative control, (e) isolation DIFFERS so
 *      the TU-aware harness is load-bearing.  Check (a) "reassembly identity"
 *      FAILS for this TU and it is a FALSE ALARM: game_1E37D0.c is CRLF and the
 *      harness's splitter rejoins with LF, so all 360 lines "differ" by \r.  (b)
 *      proves the codegen is identical anyway.  Do not chase (a) here.
 *      Because the base frame is still wrong you can only use
 *      PERMUTER_TU_MAX_FRAME=264 (stops the search trading the frame away);
 *      REQUIRE_FRAME/REQUIRE_OFFSETS would reject the base itself.
 *      ~1700 iterations from the 668 base produced the declaration-order move
 *      (496) that led to the 279 above; it is worth a much longer run from 279.
 *   2. The open question is now precise and narrow: WHAT MAKES IDO RESERVE ONE
 *      8-BYTE COMPILER TEMP SLOT THAT IT NEVER USES?  It is not any single
 *      statement and it is not the declaration list.  Excluded this wave (all
 *      frame 0x108, and func_151B6320 stayed byte-identical throughout):
 *        - the indirect call, five ways: `(*D_8008FB90[arg1])(...)`; a typedef'd
 *          function-pointer array; an explicitly-sized array; `if (!call)`
 *          instead of `if (call == 0)`; callee params typed as the real pointers.
 *        - a single exit instead of two `return`s (678, i.e. WORSE).
 *        - returning s32 instead of void * (668).
 *        - func_15147A80 declared to return void * instead of s32 (668).
 *      Still untried, in order of promise:
 *        (a) the 11-argument func_15147A80 call -- argbuild 0x2C plus a 0xC pad
 *            to 0x38 is the ONLY structural feature this function shares with the
 *            matched func_151B6320 (which gets temp 0) and nothing else does.
 *            Vary the DECLARED ARITY / parameter types of func_15147A80 -- but
 *            note func_151B6320 shares that prototype, so re-verify it stays 0.
 *        (b) the arg-save area: golden saves a0..a3 to 0x100..0x10C, i.e. the
 *            frame boundary is exactly where the incoming args begin.  Try
 *            param-list shapes (e.g. arg1/arg3 as s32 rather than u8) and watch
 *            the FLOOR, not the score.
 *        (c) a long permuter run from the 279 seed.
 */

/* ---------------- THE FLOOR IS THE FUNCTION'S, NOT THE TU'S ----------------
 * Measured directly: compiled with the repo's exact IDO flags, func_151B7328's
 * prologue is `addiu sp,sp,-264` BOTH in the whole game_1E37D0.c (all
 * #pragma GLOBAL_ASM lines stripped) AND with every other function in the file
 * reduced to a bare declaration.  So the 8 surplus bytes are a property of THIS
 * FUNCTION'S OWN SOURCE, not of TU context.  An isolated compile is therefore a
 * valid instrument for the FRAME here (it is not for the score -- the TU-aware
 * harness's check (e) reports isolation changes other bytes).
 *
 * ---------------- A PERMUTER RESULT THAT WAS REFUSED ----------------
 * From the 279 seed the permuter reaches 169 with exactly one change:
 *      if ((unsigned char)(func_150ADA20() & 1)) { temp_v0 = 0x80; } ...
 * on the SECOND of the two if/else blocks only.  REFUSED, and it must stay
 * refused: golden's two blocks are SYMMETRIC (`andi t7,v0,1` then `andi t6,v0,1`,
 * the same shape byte for byte), so nothing in the binary evidences a cast on one
 * and not the other.  It is a no-op cast whose only effect is to rotate a temp
 * register -- the banned category -- and it buys that rotation on top of a frame
 * that is still 8 bytes wrong, i.e. exactly the plateau permuter_tu.sh's own docs
 * warn about.  Any future 169 sighting is this, not progress.
 * A second permuter output, 276, chains `emit.unk64 = (emit.unk63 = -1);`.
 * ALSO REFUSED: golden materialises -1 THREE separate times (`li t5,-1`,
 * `li t0,-1`, `li t7,-1`, then three sb) for unk62/63/64, which is three
 * independent statements; the chained form would store one register twice.
 * Three points is not worth making the output less like golden.
 *
 * ---------------- THE FRAME FLOOR (new, and it is the whole problem) --------
 * The frame is PINNED at 0x108 across 7, 8 and 9 declared locals -- the temp
 * pool absorbs whatever the declaration list gives up:
 *      7 locals 0xB8 -> temp 0x10      8 locals 0xBC -> temp 0xC
 *      9 locals 0xC0 -> temp 0x8      10 locals 0xC4 -> frame 0x110, temp 0xC
 * Golden's floor is 0x100.  So the residual is EXACTLY ONE 8-BYTE COMPILER-TEMP
 * SLOT that IDO reserves in my build and does not reserve in golden's, and which
 * my build never writes to (sp+[0x40,0x48) is dead in my object).  Nothing in the
 * declaration list can spend it: every scalar you delete comes straight back as a
 * temp.  Attack the floor, not the locals.
 *
 * ---- BEST MEASURED VERSION (279).  Paste over the pragma in game_1E37D0.c ---- */

typedef struct {
    Vec151B6320 unk0;
    s16 unkC;
    s16 unkE;
    s32 unk10;
    u8 unk14;
    u8 unk15;
    u8 pad16[6];
} Header151B7328;

/* The block func_15147A80 hands back in obj->unk98: a 0x10 byte descriptor with
 * the caller's payload copied in immediately behind it (unk4 points at +0x10). */
typedef struct {
    s32 unk0;
    void *unk4;
    u8 unk8;
    u8 pad9[7];
} Data151B7328;

typedef struct {
    u8 pad0[0x98];
    Data151B7328 *unk98;
} Obj151B7328;

typedef struct {
    s32 unk0[4];
} Tbl151B7328;

/* == Struct15131EE4Local in game_15D730.c (0x70), the func_15130280 argument. */
typedef struct {
    s32 unk0;
    s32 unk4;
    s16 unk8;
    s16 unkA;
    s32 unkC;
    s32 unk10;
    u8 unk14;
    u8 unk15;
    u8 unk16;
    u8 unk17;
    u8 unk18;
    u8 unk19;
    u8 unk1A;
    u8 unk1B;
    u8 unk1C;
    u8 unk1D;
    s16 unk1E;
    s16 unk20;
    s16 unk22;
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    Vec151B6320 unk30;
    Vec151B6320 unk3C;
    Vec151B6320 unk48;
    f32 unk54;
    s32 unk58;
    s32 unk5C;
    u8 unk60;
    u8 unk61;
    s8 unk62;
    s8 unk63;
    s8 unk64;
    u8 unk65;
    u8 unk66;
    u8 pad67[9];
} Emitter151B7328;

extern s32 D_800AA460[4];
extern f32 D_800AA480;
extern s32 (*D_8008FB90[])(void *, void *);
extern void *func_15130280(void *, u8, s32, s32, u8, s32);

void *func_151B7328(void *arg0, u8 arg1, s32 arg2, u8 arg3, s32 arg4) {
    Obj151B7328 *obj;
    u8 *payload;
    Header151B7328 header;
    Data151B7328 data;
    Data151B7328 *dst;
    Emitter151B7328 emit;
    Tbl151B7328 tbl;
    s32 temp_v0;
    s32 temp_v1;

    data.unk0 = 0;
    data.unk4 = NULL;
    header.unk15 = 0x14;
    data.unk8 = arg1;
    header.unk0 = *(Vec151B6320 *)&D_800A5480;
    header.unkC = 0x12C;
    header.unkE = 0x14;
    header.unk10 = 0x10;
    header.unk14 = 2;

    obj = (Obj151B7328 *)func_15147A80(&header, arg2 + 0x10, 0x14, 0, 0xE, 0xE, 0, 0, 0, arg3, arg4);
    if (obj != NULL) {
        dst = obj->unk98;
        memcpy(dst, &data, 0xC);
        payload = (u8 *)dst + 0x10;
        dst->unk4 = payload;
        memcpy(payload, arg0, arg2);
        if (D_8008FB90[arg1](obj, (u8 *)obj + 0x10) == 0) {
            func_1516972C((struct102 *)obj);
            return NULL;
        }

        tbl = *(Tbl151B7328 *)D_800AA460;
        emit.unk1D = tbl.unk0[func_150ADA20() & 3];
        emit.unk8 = 0x1303;
        emit.unk0 = 0x200005;
        emit.unk4 = 0;
        emit.unkA = 0x12C;
        emit.unkC = 0;
        emit.unk10 = 0;
        emit.unk14 = 0xFF;
        emit.unk15 = 0xFF;
        emit.unk16 = 0xFF;
        emit.unk17 = 0xFF;
        emit.unk18 = 0xFF;
        emit.unk19 = 0xFF;
        emit.unk1A = 0xFF;
        emit.unk1B = 0xFF;
        emit.unk1C = 0xFF;
        emit.unk28 = emit.unk2C = (func_150ADA68() * 800.0f) + D_800AA480;
        emit.unk30 = header.unk0;
        emit.unk3C = *(Vec151B6320 *)&D_800A5480;
        emit.unk48 = *(Vec151B6320 *)&D_800A5480;
        emit.unk1E = 1;
        emit.unk20 = 0xFF;
        emit.unk22 = 1;
        emit.unk54 = 0.0f;
        emit.unk24 = 1.0f;

        if (func_150ADA20() & 1) {
            temp_v1 = 0x40;
        } else {
            temp_v1 = 0;
        }
        if (func_150ADA20() & 1) {
            temp_v0 = 0x80;
        } else {
            temp_v0 = 0;
        }
        emit.unk58 = temp_v0 | temp_v1 | 0xC000 | 0x40000;
        emit.unk60 = 6;
        emit.unk61 = 5;
        emit.unk62 = -1;
        emit.unk63 = -1;
        emit.unk64 = -1;
        emit.unk65 = 0;
        emit.unk5C = 0;
        emit.unk66 = 0xFF;

        dst->unk0 = (s32)func_15130280(&emit, 1, 0, 0, arg3, arg4);
    }
    return obj;
}
