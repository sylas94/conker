/* ============================================================================
 * NEAR-MISS PARK: game_40490 / func_15013778   (125 insns / 500 bytes)
 * BEST MEASURED RESIDUAL: 17 mismatching instructions out of 125.
 *   symbol size mine == gold (0x1F4), instruction MULTISET is IDENTICAL,
 *   frame is identical (0xC8), every stack offset is identical, every
 *   register is identical.  The ONLY difference is the SCHEDULE of a
 *   17-instruction window at 0x20..0x60 (the block entered when unk8 != 0).
 *
 * MEASUREMENT: symbol-bounded objdump compare (readelf value+size ->
 * objdump --start-address/--stop-address) of conker/build/src/game_40490.c.o
 * against conker/expected/build/src/game_40490.c.o.  asm-differ `-o` was NOT
 * used for the number: with this TU it reads a 16 KB window straight through
 * the following functions and reported 2433 for a source whose own 500 bytes
 * were 101 off.  Scoring script: scratchpad/w40490_bounded.py.
 *
 * THE RESIDUAL, PRECISELY NAMED
 * -----------------------------
 * golden materialises the shared 0.0f constant (`mtc1 zero,$f12`) as the
 * FIRST instruction of the block, then cvt/add.s, and only THEN the 1.0f
 * (`lui at,0x3f80 / mtc1 at,$f8`) that feeds the reciprocal divide:
 *      mtc1 v0,$f4 | mtc1 zero,$f12 | cvt.s.w $f0,$f4 | add.s $f6,$f0,$f0
 *    | lui at,0x3f80 | mtc1 at,$f8 | lui at,%hi(D_80096640) | swc1 $f6,0xA8
 *    | lh t6,6(s0) | lwc1 $f10,0xA8 | mfc1 a3,$f12 | mtc1 t6,$f16 | div.s ...
 * mine emits the 1.0f first and uses it as the mtc1->cvt hazard filler:
 *      mtc1 v0,$f4 | lui at,0x3f80 | mtc1 at,$f8 | cvt.s.w $f0,$f4
 *    | lui at,%hi | mtc1 zero,$f12 | addiu a0,sp,80 | mfc1 a3,$f12 | add.s ...
 * i.e. FLOAT-CONSTANT MATERIALISATION ORDER.  Proven law (below): IDO orders
 * hoisted float constants by FIRST USE IN SOURCE.  To beat this I need the
 * 0.0f to be *referenced* before the 1.0f while its STORE to tmp.unk28 stays
 * in 6th place -- and the only 0.0f references in the function are that store
 * and the two call arguments, which are downstream.  I could not construct a
 * source with that property without a banned construct.  BOUNDED for me.
 *
 * EVERYTHING I RULED OUT, WITH ITS SCORE
 * --------------------------------------
 * EXHAUSTIVE 2-D GRID over the position of `scale = 1.0f/tmp.unk18` x the
 * position of `tmp.unk28 = 0.0f` inside the 11-statement body (90 builds):
 *   floor is 17, reached only at (unk28 @5,6,7 x scale @2).  Full surface:
 *     scale@2 unk28@5/6/7 -> 17   scale@2 unk28@2 -> 19   scale@2 unk28@4 -> 20
 *     scale@3 unk28@2 -> 19       scale@3 unk28@5/6/7 -> 19
 *     scale@4 unk28@2 -> 19       scale@4 unk28@5/6/7 -> 20
 *     scale@5 -> 20..22           scale@6,@7 -> 119/117 with sizedelta +4
 *     scale@8 -> 30   scale@9 -> 33   scale@10 -> 38   scale@11 -> 122 (+4 B)
 *   -> statement order CANNOT reach the golden schedule.
 * `tmp.unk28 = 0;` (int zero) instead of 0.0f ................. 37
 * `func_150A8050(..., 0)` (int zero) instead of 0.0f .......... 37
 * `func_150A7960(mtx[0], 0, tmp.unk18, 0, ...)` int zeros ..... 20
 * ALL four zero sites spelled as int `0` ...................... 17 (== baseline)
 *   -> IDO keeps SEPARATE constant-table entries for `0` and `0.0f`; mixing
 *      the spellings reorders the pool.  This is a real, reusable law.
 * `tmp.unkC *= scale;` compound assign instead of `= a * b` ... 17 (no change)
 * early-return form `if (x == 0) return 1;` + bare body ....... 121, sizedelta +8
 * declaring temp_v0 last instead of first ..................... 38 (frame layout)
 * declaring mtx before tmp .................................... 101 (both locals +4)
 * caching `s32 height = (s16)arg0->unk8` in a local ............ 101 (steals $s1;
 *   golden re-loads `lh v0,8(s0)` after the memcpy, so there is NO cached local)
 * moving the new `extern f32` decls to the top of the TU ...... 17 (free)
 * `func_1501474C`/`func_15014B60` live vs pragma'd ............ 17 (no TU coupling)
 *
 * NOT tried: decomp-permuter.  The residual is a pure scheduling coin-flip
 * with no structural handle (identical multiset, identical registers,
 * identical frame), which is exactly the class conker-permuter-setup.md
 * records as un-crackable; and game_40490.c has 25 functions, the size at
 * which permuter zeros stop transferring.
 * ========================================================================= */

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    f32 unk30;
} Struct15013778;

extern f32 D_80096640;
extern f32 D_80096644;

/* Behaviour: a "column"/beam spawner.  If the object's half-height
 * (arg0->unk8) is non-zero it builds a 0x34-byte particle-emitter payload
 * describing a vertical shaft: the payload records the object's world
 * position, the full height (2*half-height), the radius (unk6), the two
 * Euler angles from unkC/unk10, two tuning constants, and a unit direction
 * vector obtained by rotating (0, fullHeight, 0) through the object's
 * orientation matrix and normalising it by 1/fullHeight.  The payload is
 * memcpy'd into a freshly-allocated type-0x19 effect record, and finally a
 * looping sound (id 0x67C) is started at the shaft's mid-point with radius
 * fullHeight and falloff halfHeight, using func_1000EF40 as its update hook.
 * Always returns 1. */
s32 func_15013778(struct134 *arg0) {
    struct260 *temp_v0;
    Struct15013778 tmp;
    f32 mtx[4][4];
    f32 scale;

    if ((s16)arg0->unk8 != 0) {
        tmp.unk18 = (f32)(s16)arg0->unk8 + (f32)(s16)arg0->unk8;
        scale = 1.0f / tmp.unk18;
        tmp.unk1C = (f32)(s16)arg0->unk6;
        tmp.unk20 = *(f32 *)&arg0->unkC;
        tmp.unk24 = *(f32 *)&arg0->unk10;
        tmp.unk28 = 0.0f;
        tmp.unk2C = D_80096640;
        tmp.unk30 = D_80096644;
        tmp.unk0 = (f32)arg0->unk0;
        tmp.unk4 = (f32)(s16)arg0->unk2;
        tmp.unk8 = (f32)arg0->unk4;

        func_150A8050(mtx, *(f32 *)&arg0->unkC, *(f32 *)&arg0->unk10, 0.0f);
        func_150A7960(mtx[0], 0.0f, tmp.unk18, 0.0f, &tmp.unkC, &tmp.unk10, &tmp.unk14);

        tmp.unkC = tmp.unkC * scale;
        tmp.unk10 = tmp.unk10 * scale;
        tmp.unk14 = tmp.unk14 * scale;

        temp_v0 = func_15149130(0x12C, -1, 0x19, -1, 0, 0x17, (struct37 *)0x34, 0xFF, 0);
        if (temp_v0 != NULL) {
            memcpy((u8 *)temp_v0 + 0x28, &tmp, 0x34);
        }

        func_1000FA64(0x67C, arg0->unk0, (s16)arg0->unk2 + (s16)arg0->unk8, arg0->unk4, 0x2EE0,
                      (s16)arg0->unk8 * 2, (s16)arg0->unk8 / 2, (s32)func_1000EF40, NULL, 0, 8, 0);
    }
    return 1;
}
