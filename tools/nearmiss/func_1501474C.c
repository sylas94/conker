/* ============================================================================
 * NEAR-MISS PARK: game_40490 / func_1501474C   (261 insns / 1044 bytes)
 * BEST MEASURED RESIDUAL: 21 mismatching instructions out of 261.
 *   symbol size mine == gold (0x414), frame identical (0xB0), EVERY stack
 *   offset identical, EVERY local at the golden address, the entire 235-
 *   instruction body byte-identical.  The residual is one 21-instruction
 *   window at 0x384..0x3D8 whose instruction MULTISET is identical to
 *   golden's -- only the placement of two `li` constants differs.
 *
 * MEASUREMENT: symbol-bounded objdump compare (scratchpad/w40490_bounded.py)
 * of build/src/game_40490.c.o vs expected/build/src/game_40490.c.o, object
 * rebuilt from scratch (`rm -f` the .o AND the asm-processor intermediate)
 * before every single measurement, all under tools/buildlock.sh.
 *
 * THE RESIDUAL, PRECISELY NAMED
 * -----------------------------
 * The two STACK arguments of the trailing func_15149130 call -- arg6 = 0x40
 * and arg7 = 0xFF -- are materialised at the wrong point.
 *   golden:  li a0,300 | li a1,-1 | li a2,44 | li a3,-1 | mul.s | swc1 168
 *          | lw t1,24(s0) | sb t1,172 | lw t9,24(s0) | li t1,64 | srl t3,t9,8
 *          | sb t3,173 | lw t7,24(s0) | li t9,255 | srl t4,t7,16 | sb t4,174
 *          | lw t5,24(s0) | sw t9,28(sp) | srl t2,t5,24 | sb t2,175
 *          | sw t1,24(sp)
 *   mine:    li t4,64 | li t5,255 | li a0,300 | li a1,-1 | li a2,44 | li a3,-1
 *          | mul.s | swc1 168 | lw t2 | sb t2,172 | lw t1 | srl t9 | sb t9,173
 *          | lw t0 | srl t3 | sb t3,174 | lw t7 | sw t5,28 | srl t6 | sb t6,175
 *          | sw t4,24
 * golden's register allocator assigns the two constants to t1/t9 -- registers
 * that have just DIED in the byte-extraction block -- which forces them to be
 * emitted late, where the scheduler drops them into the lw load-delay slots.
 * Mine allocates fresh t4/t5, so they are free to float to the top of the
 * block.  Register allocation runs on the pre-scheduled IR, so this says the
 * golden IR emits the call's stack-arg setup AFTER the four byte stores while
 * mine emits it BEFORE.  Both sources put the call after the stores, so this
 * is an IDO IR-ordering artifact I could not reach from C.
 * Note the temp-rotation state entering the window is PROVABLY IDENTICAL --
 * every register up to 0x380 matches golden -- so this is NOT the classic
 * "rotation is off by N" case that a mask-count change would fix.
 *
 * EVERYTHING I RULED OUT, WITH ITS SCORE  (baseline 21)
 * ----------------------------------------------------
 * memcpy size `sizeof(payload)` instead of 0x40 ............... 21
 * arg6 `(struct37 *)sizeof(payload)` .......................... 21
 * both of the above ........................................... 21
 * `(u8)` casts on the three shifted byte assignments ........... 21
 * `arg0->unk18 >> 8` (signed) instead of `(u32)... >> 8` ....... 21
 * arg7 spelled `255` instead of `0xFF` ......................... 21
 * `if ((temp_v0 = func_15149130(...)) != NULL)` ................ 21
 * `if (temp_v0)` instead of `!= NULL` .......................... 21
 * `memcpy((void *)((s32)temp_v0 + 0x28), ...)` ................. 21
 * `if (temp_v0 == NULL) return 1;` then straight-line memcpy ... 35, sizedelta +12
 * `payload.unk30 = 0.0f` moved after unk34 ..................... 45
 * byte block moved AFTER the func_15149130 call ................ 28
 * byte block moved after payload.unk30 ......................... 47
 * byte block moved after payload.unk24 ......................... 227, sizedelta -8
 * byte block moved after payload.unk1C ......................... 234, sizedelta -8
 * byte block moved before the pts copies ....................... 235, sizedelta -8
 *   (the -8 cases prove the byte block is LAST in the golden source: moved
 *    earlier, IDO CSEs the four `lw 0x18(s0)` into fewer loads; golden has
 *    four separate loads.)
 * moving the new `extern f32` decls to the top of the TU ....... 21 (free)
 * other two target functions live vs pragma'd .................. 21 (no coupling)
 *
 * TWO LAWS THIS FUNCTION ESTABLISHED (they are why the other 235 insns match)
 * --------------------------------------------------------------------------
 * 1. LOCAL STACK LAYOUT IS A TRANSCRIPT OF THE DECLARATION LIST.  IDO -g3
 *    lays locals out BOTTOM-UP in REVERSE declaration order, and it reserves
 *    a home for EVERY declared local, including ones that are register-
 *    allocated and ones the optimiser deletes entirely.  Reading the holes in
 *    golden's frame therefore recovers the original declaration list exactly.
 *    Here golden's frame is  x@0x38 ?@0x3C z@0x40 ?@0x44 sn@0x48 pts@0x4C
 *    ?@0x6C payload@0x70, which decodes uniquely to
 *        payload; temp_v0; pts[4]; sn; cs; z; y; x;
 *    Applying it took the function from 38 mismatches to 21 in one edit.
 * 2. A local that the optimiser DELETES still costs its frame slot.  `y` is
 *    assigned `(f32)(s16)arg0->unk2` and never read; IDO dead-code-eliminates
 *    the store AND the load (verified: symbol size unchanged, no swc1 to
 *    0x3C) but keeps the 4-byte home.  So `y` is not a pad I invented -- the
 *    4-byte hole at 0x3C is positive evidence that the original C declared
 *    it, and the sibling func_15015354 in this very file declares exactly
 *    `f32 z; f32 y; f32 x;` in that order.  FLAGGING IT ANYWAY: if the wave
 *    owner considers a DCE'd assignment a banned dead assignment, drop the
 *    `y = ...` line and keep the bare declaration -- byte-identical output,
 *    and then no code at all is emitted for it.
 * ========================================================================= */

extern f32 D_80096690;
extern f32 D_80096694;

typedef struct {
    f32 x;
    f32 z;
} Vec2_1501474C;

typedef struct {
    Vec2_1501474C unk0;
    Vec2_1501474C unk8;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    f32 unk30;
    f32 unk34;
    f32 unk38;
    u8 unk3C;
    u8 unk3D;
    u8 unk3E;
    u8 unk3F;
} Struct1501474C;

/* Behaviour: builds a rotated rectangular "curtain"/wall effect.  The object
 * carries a half-width (unk6), a half-depth (unkA) and a yaw stored in unk10.
 * sinf/cosf of that yaw (each scaled by its own constant) rotate the four
 * corners (+w,+d) (+w,-d) (-w,-d) (-w,+d) about the object's XZ position, and
 * the payload gets corner 1 and corner 2 as its two anchor points plus the two
 * edge vectors (c0-c1) and (c3-c2) that span the quad.  Then it records the
 * top and bottom Y (unk2+unk8, unk2) and unpacks arg0->unk1C as four bytes
 * into two pairs of scaled floats (bytes 0/1 -> x/512, bytes 2/3 -> x*250/256)
 * and arg0->unk18 as four raw bytes.  The 0x40-byte payload is memcpy'd into a
 * freshly-allocated type-0x2C effect record.  Always returns 1. */
s32 func_1501474C(struct134 *arg0) {
    Struct1501474C payload;
    struct260 *temp_v0;
    Vec2_1501474C pts[4];
    f32 sn;
    f32 cs;
    f32 z;
    f32 y;
    f32 x;

    arg0->unk16 |= 4;
    x = (f32)arg0->unk0;
    y = (f32)(s16)arg0->unk2;
    z = (f32)arg0->unk4;
    sn = sinf(*(f32 *)&arg0->unk10 * D_80096690);
    cs = cosf(*(f32 *)&arg0->unk10 * D_80096694);

    pts[0].x = ((f32)(s16)arg0->unk6 * cs) + x + ((f32)(s16)arg0->unkA * sn);
    pts[0].z = ((f32)(s16)arg0->unkA * cs) + z - ((f32)(s16)arg0->unk6 * sn);
    pts[1].x = ((f32)(s16)arg0->unk6 * cs) + x + ((f32)-(s16)arg0->unkA * sn);
    pts[1].z = ((f32)-(s16)arg0->unkA * cs) + z - ((f32)(s16)arg0->unk6 * sn);
    pts[2].x = ((f32)-(s16)arg0->unk6 * cs) + x + ((f32)-(s16)arg0->unkA * sn);
    pts[2].z = ((f32)-(s16)arg0->unkA * cs) + z - ((f32)-(s16)arg0->unk6 * sn);
    pts[3].x = ((f32)-(s16)arg0->unk6 * cs) + x + ((f32)(s16)arg0->unkA * sn);
    pts[3].z = ((f32)(s16)arg0->unkA * cs) + z - ((f32)-(s16)arg0->unk6 * sn);

    payload.unk0 = pts[1];
    payload.unk8 = pts[2];
    payload.unk10 = pts[0].x - pts[1].x;
    payload.unk14 = pts[0].z - pts[1].z;
    payload.unk18 = pts[3].x - pts[2].x;
    payload.unk1C = pts[3].z - pts[2].z;
    payload.unk20 = (f32)((s16)arg0->unk2 + (s16)arg0->unk8);
    payload.unk24 = (f32)(s16)arg0->unk2;
    payload.unk28 = (f32)(arg0->unk1C & 0xFFU) * 0.00390625f * 0.5f;
    payload.unk2C = (f32)(((u32)arg0->unk1C >> 8) & 0xFFU) * 0.00390625f * 0.5f;
    payload.unk30 = 0.0f;
    payload.unk34 = (f32)(((u32)arg0->unk1C >> 16) & 0xFFU) * 0.00390625f * 250.0f;
    payload.unk38 = (f32)(((u32)arg0->unk1C >> 24) & 0xFFU) * 0.00390625f * 250.0f;
    payload.unk3C = arg0->unk18;
    payload.unk3D = (u32)arg0->unk18 >> 8;
    payload.unk3E = (u32)arg0->unk18 >> 16;
    payload.unk3F = (u32)arg0->unk18 >> 24;

    temp_v0 = func_15149130(0x12C, -1, 0x2C, -1, 0, 0, (struct37 *)0x40, 0xFF, 0);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &payload, 0x40);
    }
    return 1;
}
