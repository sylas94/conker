/* func_151B7328  (game_1E37D0.c, 848 B, cold decompile)
 * BEST SCORE: 676 with -R and without -R (base: pragma-removed live C in
 * conker/src/game_1E37D0.c).  Progression: 1329 -> 684 -> 676.
 * NOT SHIPPED: the pragma in conker/src/game_1E37D0.c is RESTORED and that file
 * is pristine (`git status --short -- conker/src/game_1E37D0.c` prints nothing).
 *
 * STATUS: every instruction matches golden 1:1.  The ONLY residual is that the
 * whole local block sits 8 bytes higher than golden:
 *      golden framesize 0x100, mine 0x108
 *      golden header@0xE4 data@0xD4 dst@0xD0 emit@0x60 tbl@0x50 spill@0x48
 *      mine   header@0xEC data@0xDC dst@0xD8 emit@0x68 tbl@0x58 spill@0x50
 * Everything is a uniform +8, so the aggregate SIZES are all right; there are
 * 8 extra bytes of compiler-temp pool below the locals.  Residual class:
 * FRAME (temp-pool size), which then drags two register picks with it
 * (golden `or t2,v0,v1` / `lw a3,0xD0(sp)` vs mine `or t8,..` / `lw v1,..`).
 *
 * ---------------- WHAT IS ESTABLISHED (do not re-derive) ----------------
 * Frame decode, cross-checked against two MATCHED siblings:
 *   func_151B6320 (same TU): framesize 0x90, saved [0x38,0x40), locals
 *      [0x40,0x90) = 0x50 = header 0x1C + payload 0x30 + temp 4.
 *      => the committed source's `top_dummy`/`pad_dummy` autos are just a
 *         0x18-wide Header151B6320; the TRUE header width is 0x1C.
 *   func_15131EE4 (game_15D730.c): framesize 0xB0, locals [0x20,0xB0) = 0x90
 *      = Struct15131EE4Local 0x70 + Struct15131EE4Extra 0x14 + 3 scalars.
 * HEADER WIDTH 0x1C IS PROVEN, not guessed: func_15147A80 (game_174BF0.c,
 * matched) does `memcpy((u8*)temp_v0 + 0x10, arg0, 0x1C)` on this very struct.
 *
 * Emitter151B7328 == Struct15131EE4Local (0x70) from game_15D730.c; the whole
 * field map at sp+0x60..0xD0 lines up 1:1, including pad67[9].
 *
 * MEASURED NEGATIVES (each vs the base it is listed against):
 *  - `emit.unk58 = (temp_v0|temp_v1) | 0x4C000;`  -> IDO builds 0x4C000 whole
 *    (lui 0x4 + ori 0xC000 into `at`, ONE `or`).  Golden splits: `or t2,v0,v1;
 *    ori t3,t2,0xC000; lui at,0x4; or t1,t3,at`.  Source must therefore be
 *    `(temp_v0 | temp_v1) | 0xC000 | 0x40000`.  Worth ~300 pts. (vs 1329 base)
 *    Cross-check: the matched func_15131EE4 writes `temp_v0 | 0x4C000 | temp_v1`
 *    and DOES get the built-whole form -- so the two spellings are separable.
 *  - `u8 unk62` gives `li 0xff`; golden has `li -1` at unk62/63/64 and `li 0xff`
 *    only at unk66 => unk62 must be s8. (vs 1329 base)
 *  - dropping `s32 ret` (folding the call into `dst->unk0 = ...`): NO code
 *    change, frame unchanged 0x108.  (vs 684 base)
 *  - dropping `s32 temp_v0` in favour of `((func_150ADA20()&1) ? 0x80 : 0)`:
 *    BYTE-IDENTICAL output, frame unchanged 0x108. (vs 684 base)
 *    => register-allocated scalars are NOT costing frame bytes here; the 8
 *       surplus bytes are a compiler TEMP-POOL difference, not a local count.
 *       DO NOT keep adding/removing scalars, it has been measured three times.
 *
 * ---------------- THE FRAME BISECT (this is the whole remaining problem) -----
 * MODEL, established by six probe builds:  the region below the aggregates is a
 * SINGLE POOL shared by register-allocated scalar locals AND compiler temps.
 * Declaring a scalar vs letting IDO invent a temp is NET ZERO -- the pool size
 * is fixed by the EXPRESSION STRUCTURE, not by the declaration list.
 *    framesize = argbuild(0x30) + gap+saved(0x10) + aggregates + pool
 *    golden: aggregates 0xB0, pool 0x10  -> 0x100
 *    mine  : aggregates 0xB0, pool 0x18  -> 0x108      (2 surplus 4-byte webs)
 * Proof that aggregates are right: shrinking Emitter pad67[9]->pad67[1] (a
 * deliberately WRONG 0x68 emitter) gave framesize 0x100 and header@0xE4 exactly,
 * score 467 -- i.e. only emit/tbl were then misplaced.  So 0xB0 of aggregate is
 * correct and the surplus is pool.
 *
 * PROBE LADDER (framesize measured each time, full flags block unless noted):
 *   full function, 4 scalars (obj,temp_v1,temp_v0,ret)          -> 0x108
 *   full function, 3 scalars (ret dropped)                      -> 0x108
 *   full function, 2 scalars (temp_v0 -> ternary)               -> 0x108 (byte-identical)
 *   obj typed / all casts removed                               -> 0x108 (no effect)
 *   flags block gutted (`temp_v1=0;` only)                      -> 0x100  <== pool 0x10
 *   flags block: only the FIRST rand if/else                    -> 0x100  <== still 0x10
 *   flags block full, but `dst->unk4=..; memcpy2; callback` cut -> 0x0F8  <== pool 0x08
 *   ... plus `dst->unk4 = ..; memcpy(.., arg0, arg2);` restored -> 0x108  <== pool 0x18
 *   ... plus the callback if-block restored                     -> 0x108  <== callback is FREE
 *   `dst->unk4 = dst + 1; memcpy(dst + 1, ...)`                 -> 0x108 (no effect)
 * CONCLUSION: the two statements
 *       dst->unk4 = (u8 *)dst + 0x10;
 *       memcpy(dst->unk4, arg0, arg2);
 * cost FOUR pool webs in my spelling and only TWO in golden's.  Everything else
 * in the function is already web-for-web identical.  That pair is the ONLY thing
 * left to re-spell.  Later probes against the 684 base:
 *   - `u8 *payload; payload = (u8*)dst + 0x10; dst->unk4 = payload;
 *      memcpy(payload, arg0, arg2);`  -> 684 -> 676, frame STILL 0x108.
 *      (kept: it is the current best, and `payload` has two real uses)
 *   - splitting `emit.unk28 = emit.unk2C = X;` into two statements -> 676,
 *      BYTE-IDENTICAL, frame still 0x108.  Both spellings are equivalent here;
 *      the chained one is kept because golden's two `swc1` with no reload is
 *      exactly what it produces.
 * NOT the cause (measured): casts, `dst + 1` vs `(u8*)dst + 0x10`, the callback
 * block, the declaration list, the ternary-vs-if/else spelling, the chained
 * float assignment.
 * STILL UNTRIED: typing Data151B7328.unk4 as `Data151B7328 *`/`s32`; giving the
 * Data struct a trailing array member so the address is an address-of-member
 * (one addiu, no cast+add pair) rather than a cast plus pointer add.
 *
 * Rodata pre-filter: CLEAR.  D_800AA460 {0x60,0x61,0x62,0x63} and
 * D_800AA480 (1700.0f, low16 = 0x8000 so it can NOT inline) both live in the
 * EXTERNAL asm blob conker/asm/data/24EF20.rodata.s, so `extern` references
 * reproduce golden's relocs exactly.  D_800A5480 likewise (249F40.rodata.s).
 * This function is NOT rodata-blocked.
 */

/* ---- BEST MEASURED VERSION (676).  Paste over the pragma in game_1E37D0.c ---- */

/* func_15147A80 (game_174BF0.c) does memcpy(obj + 0x10, arg0, 0x1C) out of this
 * header, so the real header type is 0x1C wide.  (Header151B6320 above models it
 * as 0x18 + two hand-placed dummy autos; same frame, different spelling.) */
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
        emit.unk58 = ((func_150ADA20() & 1) ? 0x80 : 0) | temp_v1 | 0xC000 | 0x40000;
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
