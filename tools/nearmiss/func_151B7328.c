/* func_151B7328  (game_1E37D0.c, 848 B, cold decompile)
 * BEST SCORE: 668 with -R and without -R (base: pragma-removed live C in
 * conker/src/game_1E37D0.c).  Progression: 1329 -> 684 -> 676 -> 668.
 * NOT SHIPPED: the pragma in conker/src/game_1E37D0.c is RESTORED and that file
 * is pristine (`git status --short -- conker/src/game_1E37D0.c` prints nothing).
 *
 * STATUS: every instruction matches golden 1:1.  The ONLY residual is that the
 * whole local block sits 8 bytes higher than golden:
 *      golden framesize 0x100, mine 0x108
 *      golden header@0xE4 data@0xD4 dst@0xD0 emit@0x60 tbl@0x50
 *      mine   header@0xEC data@0xDC dst@0xD8 emit@0x68 tbl@0x58
 * plus exactly two register picks that the shift drags with it:
 *      golden `lbu t6,0x107(sp)` / `li t7,0x14`  vs mine `lbu t7` / `li t6`
 *      golden `lw a3,0xD0(sp)`                   vs mine `lw v1,0xD8(sp)`
 * Residual class: FRAME (surplus compiler-temp reserve, 8 bytes).
 *
 * =====================================================================
 * ==  CORRECTION: THE PREVIOUS PARKED BISECT DOES NOT REPRODUCE.     ==
 * =====================================================================
 * The earlier note claimed the pair
 *      dst->unk4 = (u8 *)dst + 0x10;
 *      memcpy(dst->unk4, arg0, arg2);
 * "cost FOUR pool webs vs golden's TWO", localised by a 9-build bisect.
 * I re-ran that bisect and EVERY STEP OF IT FAILED TO REPRODUCE.  Measured
 * this wave (all against the live-C base, framesize read off the prologue):
 *   - drop ONLY `dst->unk4 = payload;`            -> 0x108 (score 1158)
 *   - drop ONLY `memcpy(payload, arg0, arg2);`    -> 0x108 (score 1510)
 *   - drop ONLY the FIRST memcpy(dst,&data,0xC)   -> 0x108 (score 2171)
 *   - drop ONLY the callback if-block             -> 0x108 (score 3089)
 *   - gut the flags block to `emit.unk58=0xC000;` -> 0x108 (score 7004)
 * i.e. NO single statement removal moves the frame off 0x108.  The old
 * "flags gutted -> 0x100" and "unk4/memcpy2 cut -> 0x0F8" readings are wrong.
 *
 * Four mutually-distinct spellings of the memcpy pair were then measured and
 * ALL FOUR scored EXACTLY 684 with framesize 0x108 -- the N-NO-OPS signature:
 *   a) memcpy(dst->unk4 = (u8 *)dst + 0x10, arg0, arg2);   (unk4 as void *)
 *   b) same with unk4 typed `u8 *`
 *   c) separate heap-block type with a trailing `u8 unk10[1]`, so the address
 *      is an address-of-member: `dst->unk4 = dst->unk10; memcpy(dst->unk10,..)`
 *   d) the plain two-statement form
 * => THE MEMCPY SPELLING IS NOT THE LEVER.  Do not spend more builds there.
 *
 * ---------------- WHAT THE FRAME ACTUALLY DECODES TO ----------------
 * Calibrated against THREE matched siblings, all of which have pool == 0:
 *   func_15131EE4 (game_15D730.c) framesize 0xB0: argbuild 0x18 + gap 4 +
 *      ra 4 + locals 0x90; locals = Local 0x70 + Extra 0x14 + 3 scalars 0xC.
 *      EXACT, no pool.  <-- same emitter struct AND the same two-if/else flags
 *      block as this function, so it is the closest calibration available.
 *   func_15151A38 (game_17CAF0.c) framesize 0xF8: locals [0x98,0xF8) = 0x60 =
 *      Pos 0x1C + Spawn 0x20 + NINE scalars 0x24.  EXACT, no pool.
 *   func_15152F70 (game_17CAF0.c) framesize 0x108: locals [0x90,0x108) = 0x78 =
 *      Pos 0x1C + Spawn 0x1C + Style 0x20 + EIGHT scalars 0x20.  EXACT, no pool.
 *      (that one I closed this wave -- score 0, .text identical.)
 * Note s16 locals occupy a 4-byte slot each, not 2.
 *
 * Applying that law here, GOLDEN's locals region is [0x40,0x100) = 0xC0 =
 *      header 0x1C + data 0x10 + dst 4 + emit 0x70 + tbl 0x10  (= 0xB0)
 *    + FOUR 4-byte scalars                                      (= 0x10)
 * so golden declares FOUR trailing scalars, and golden's temp_v1 spills to
 * 0x48, i.e. it is the 2ND of those four (block [0x40,0x50), top-down).
 *
 * THE SCALAR-COUNT SWEEP (this is new, and it is what bought the 8 points):
 *      2 scalars (obj,temp_v1)                    -> 0x108, score 684
 *      3 scalars (obj,payload,temp_v1)            -> 0x108, score 676  <- old best
 *      4 scalars (obj,payload,temp_v0,temp_v1)    -> 0x108, score 668  <- NEW BEST
 *      5 scalars (+ s32 ret)                      -> 0x110, score 1132
 * So the frame is NOT flat in the local count (the old note said it was); it
 * steps at 5.  Four scalars reproduces golden's locals size 0xC0 EXACTLY, and
 * it is also the declaration list the matched sibling func_15131EE4 uses
 * (ret/temp_v0/temp_v1 + the two if/else blocks).  `ret` is NOT golden's 4th
 * scalar -- capturing the func_15130280 return grows the frame to 0x110.
 *
 * Declaration-order permutations of the four scalars (all vs the 668 base):
 *      obj,payload,temp_v0,temp_v1   -> 668   <- keep
 *      obj,temp_v1,temp_v0,payload   -> 684
 *      temp_v0,temp_v1,obj,payload   -> 684
 *      payload,temp_v1,temp_v0,obj   -> 684
 * Statement order: moving `emit.unk8 = 0x1303;` above the tbl copy -> 1640.
 *
 * ---------------- WHAT IS LEFT ----------------
 * Under the calibrated law the naive region sum for golden is
 *      argbuild 0x2C + saved 0x8 + locals 0xC0 = 0xF4 -> 0xF8 rounded,
 * but golden's framesize is 0x100 and mine is 0x108, so BOTH carry a reserve
 * above the naive sum (golden 8, mine 16).  Every matched sibling I measured
 * carries ZERO.  So the open question is no longer "which statement costs a
 * web" -- it is WHY THIS FUNCTION HAS A RESERVE AT ALL, and why mine is one
 * 8-byte unit larger.  Next things to try, in order:
 *   1. the permuter (tools/decomp-permuter, ido configured) -- this is now a
 *      pure register/frame-shape residual, which is what it is for.
 *   2. the 11-argument func_15147A80 call: argbuild 0x2C is the only structural
 *      difference from every sibling I calibrated against (they max out at 6
 *      and 15 args with no reserve).  Try varying the DECLARED arity/param
 *      types of func_15147A80 (file-local shadow only -- NEVER edit
 *      functions.h) and watch the reserve, not the score.
 *   3. `Obj151B7328` is only used for `obj->unk98` and `(u8 *)obj + 0x10`;
 *      try typing obj as the callee's real return type instead of casting.
 *
 * MEASURED NEGATIVES retained from the previous wave (still valid):
 *  - `emit.unk58 = (temp_v0|temp_v1) | 0x4C000;` -> IDO builds 0x4C000 whole
 *    (lui 0x4 + ori 0xC000 into `at`, ONE `or`).  Golden splits: `or t2,v0,v1;
 *    ori t3,t2,0xC000; lui at,0x4; or t1,t3,at`.  Source must therefore be
 *    `... | 0xC000 | 0x40000`.  Worth ~300 pts.  (Cross-check: matched
 *    func_15131EE4 writes `temp_v0 | 0x4C000 | temp_v1` and DOES get the
 *    built-whole form, so the two spellings are genuinely separable.)
 *  - `u8 unk62` gives `li 0xff`; golden has `li -1` at unk62/63/64 and `li 0xff`
 *    only at unk66 => unk62 must be s8.
 *  - splitting `emit.unk28 = emit.unk2C = X;` into two statements: BYTE-
 *    IDENTICAL.  Keep the chained form (golden's two swc1 with no reload).
 *  - casts, `dst + 1` vs `(u8 *)dst + 0x10`: byte-identical, not the lever.
 *
 * HEADER WIDTH 0x1C IS PROVEN, not guessed: func_15147A80 (game_174BF0.c,
 * matched) does `memcpy((u8*)temp_v0 + 0x10, arg0, 0x1C)` on this very struct.
 * Emitter151B7328 == Struct15131EE4Local (0x70) from game_15D730.c; the whole
 * field map at sp+0x60..0xD0 lines up 1:1, including pad67[9].
 *
 * Rodata pre-filter: CLEAR.  D_800AA460 {0x60,0x61,0x62,0x63} and
 * D_800AA480 (1700.0f, low16 = 0x8000 so it can NOT inline) both live in the
 * EXTERNAL asm blob conker/asm/data/24EF20.rodata.s, so `extern` references
 * reproduce golden's relocs exactly.  D_800A5480 likewise (249F40.rodata.s).
 * This function is NOT rodata-blocked.  Its TU .rodata is 0 bytes both sides.
 *
 * NOTE: game_1E37D0.c also contains func_151B65D4, which is BLOCKED. Do not
 * touch it.
 */

/* ---- BEST MEASURED VERSION (668).  Paste over the pragma in game_1E37D0.c ---- */

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
    Header151B7328 header;
    Data151B7328 data;
    Data151B7328 *dst;
    Emitter151B7328 emit;
    Tbl151B7328 tbl;
    Obj151B7328 *obj;
    u8 *payload;
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
