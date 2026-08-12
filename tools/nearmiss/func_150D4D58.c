/* func_150D4D58 -- game_100810.c -- 972 bytes / 243 insns / frame 0x108
 * STATUS: best 3498 (from 7399 on the first honest draft).  NOT a match.  Live C is parked
 * here; the repo file has the #pragma restored.
 *
 * WHAT IT IS: a particle burst emitter.  It fills a 0x70-byte spawn-parameter struct and
 * calls func_15130280 (the particle spawner) rand%11+10 times, each time re-randomising
 * colour (D_800A09C0[rand&3]), lifetime, size, launch direction (func_15143794 turns an
 * s16 yaw/pitch pair + speed into a velocity vector) and two random render flags.
 *
 * ================= FRAME DECODE (golden .s, framesize 0x108 = 264) ==================
 *   0x00..0x17  arg build, 6 words (func_15130280 takes 6 args; slots 0x10/0x14 used)
 *   0x18..0x1F  pad to 8 for the sdc1 block
 *   0x20..0x4F  sdc1 $f20,$f22,$f24,$f26,$f28,$f30
 *   0x50..0x74  sw  $s0..$s7,$fp,$ra                      -> saved area ends at 0x78
 *   0x78..0x97  32 bytes: compiler TEMP area + declared-auto homes
 *   0x98..0x107 `params`, 0x70 bytes, ENDING EXACTLY AT FRAMESIZE
 *               => params is the FIRST-DECLARED local (first declared = highest address)
 *   0x114       $a3 home (caller's arg slot); read back as `lbu 0x117(sp)` => arg3 is u8
 *   0x118       5th parameter (arg4)
 *
 * The 0x70 size is a FACT, not padding: func_15130280 is LIVE MATCHED C in
 * src/game_15D730.c and does `memcpy((s32)temp_v0 + 0x10, arg0, 0x70)`.
 * The struct TYPE is also byte-verified: `Struct15131EE4Local` in src/game_15D730.c is
 * used by func_15131EE4, which I re-scored at 0 with .text/.rodata/.data of the whole TU
 * IDENTICAL to expected/.  Every field offset I decode here lands on one of its members.
 *
 * OPEN: golden's 32 bytes at 0x78..0x97 split as (temp area) + 4*N declared scalars.
 * My best build has 7 declared scalars (28 bytes) and IDO reserves 12 bytes of temp,
 * rounding to 40 -> framesize 0x110, 8 too big.  Golden's total is 32, so golden is
 * (0 temp, 8 scalars) or (4 temp, 7 scalars) or (8 temp, 6 scalars).  Measured: the
 * reserved temp area is UNUSED (no sp displacement in 0x78..0x97 in either object) and
 * does not respond to removing either struct assignment (probes P1/P2/P3 below).
 * ====================================================================================
 */

/* ---- declarations added to game_100810.c ------------------------------------- */

typedef struct {                 /* == Struct15131EE4Local, src/game_15D730.c (matched) */
    s32 unk0;  s32 unk4;  s16 unk8;  s16 unkA;  s32 unkC; s32 unk10;
    u8 unk14; u8 unk15; u8 unk16; u8 unk17; u8 unk18; u8 unk19; u8 unk1A;
    u8 unk1B; u8 unk1C; u8 unk1D;
    s16 unk1E; s16 unk20; s16 unk22;
    f32 unk24; f32 unk28; f32 unk2C;
    struct17 unk30; struct17 unk3C; struct17 unk48;
    f32 unk54; s32 unk58; s32 unk5C;
    u8 unk60; u8 unk61; u8 unk62; s8 unk63; s8 unk64; u8 unk65; u8 unk66;
    u8 pad67[9];
} Struct150D4D58;

extern f32 D_800A5480;
extern f32 D_800A0A18;
extern f32 D_800A0A1C;
extern f32 D_800A0A20;
extern f32 D_800A0A24;
extern f32 D_800A0A28;
extern void func_15143794(s32, s32, f32, f32 *);
extern void *func_15130280(void *, u8, s32, s32, u8, s32);

/* ---- body (score 3498) ------------------------------------------------------- */

void func_150D4D58(struct17 *arg0, struct17 *arg1, f32 arg2, u8 arg3, s32 arg4) {
    Struct150D4D58 params;
    s32 count;
    s32 angleBase;
    f32 speed;
    f32 spread;
    f32 base;
    s32 r1;
    s32 r2;

    count = func_150ADA20() % 11U + 10;
    params.unk8 = 0x2203;
    params.unk0 = 0x200005;
    params.unk4 = 0;
    params.unkC = 0;
    params.unk10 = 0;
    params.unk14 = 0xFF;
    params.unk15 = 0xFF;
    params.unk16 = 0xFF;
    params.unk17 = 0xFF;
    params.unk18 = 0xFF;
    params.unk19 = 0xFF;
    params.unk1A = 0xFF;
    params.unk1C = 0xFF;
    params.unk30 = *arg0;
    params.unk3C = *(struct17 *)&D_800A5480;
    angleBase = (s16) (arg2 * D_800A0A18);
    angleBase = (s16) ((angleBase >> 8) + 0x40);
    params.unk1E = 10;
    params.unk20 = 25;
    params.unk61 = 7;
    params.unk62 = -1;
    params.unk22 = 1;
    params.unk24 = 1.0f;
    params.unk58 = 0x4C207;
    params.unk60 = 0;
    params.unk63 = -1;
    params.unk64 = -1;
    params.unk65 = 0;
    params.unk5C = 0;
    params.unk66 = 0xFF;
    spread = D_800A0A20;
    base = D_800A0A1C;

    do {
        speed = func_150ADA68() * spread + base;
        params.unk1D = D_800A09C0[func_150ADA20() & 3];
        params.unkA = func_150ADA20() % 18U + 27;
        params.unk1B = func_150ADA20() % 156U + 100;
        params.unk2C = params.unk28 = func_150ADA68() * 233.0f + 199.0f;
        r1 = func_150ADA20();
        r2 = func_150ADA20();
        func_15143794((s16) (r1 % 130U + angleBase), (s16) (r2 % 81U - 64),
                      func_150ADA68() * 10.0f + 5.0f, &params.unk48.unk0);
        params.unk48.unk0 = params.unk48.unk0 - arg1->unk0 * speed;
        params.unk48.unk8 = params.unk48.unk8 - arg1->unk8 * speed;
        params.unk54 = func_150ADA68() * D_800A0A24 + D_800A0A28;
        params.unk58 &= ~0xC0;
        if (func_150ADA20() & 1) {
            r1 = 0x80;
        } else {
            r1 = 0;
        }
        if (func_150ADA20() & 1) {
            r2 = 0x40;
        } else {
            r2 = 0;
        }
        params.unk58 = params.unk58 | (r2 | r1);
        func_15130280(&params, 1, 0, 0, arg3, arg4);
        count -= 1;
    } while (count > 0);
}

/* ================================ MEASURED LOG ================================
 * Every number below is `python3 ../tools/asm-differ/diff.py -o func_150D4D58 -R
 * --max-lines 4096` after a clean `make build/src/game_100810.c.o VERSION=us`
 * (both -R and no-R agreed on every measurement).  frame is `addiu sp,sp,-N`.
 *
 *  1. first honest draft, 8 scalars (count,angleBase,speed,size,r1,r2,flagA,flagB)
 *                                                             7399   frame 0x110
 *  2. merge r1/flagA and r2/flagB -> 6 scalars                 7037   frame 0x108  <-- all
 *     stack offsets became golden's (0x98 struct base, 0xA0/0xA2/.../0xFE, 0x114, 0x117,
 *     0x118) but the instruction stream was still 8 insns short.
 *  3. HOIST: `spread = D_800A0A20; base = D_800A0A1C;` before the loop              4434
 *     This is the big structural lever.  Golden pre-loads BOTH globals into callee-saved
 *     $f22/$f24; a source that reads them inside the loop cannot, because the loop is
 *     full of calls -- IDO then hoists only the ADDRESSES into $s6/$s7 and reloads each
 *     iteration.  Freeing $s7/$fp is what lets golden hoist the divisors 18 and 156 into
 *     registers, which is what produces its two `bnez $s7 / break 7` divide guards
 *     (mine had `li at,0x12` and no guard, hence the 8-instruction shortfall).
 *     It also explains why golden hoists 233.0f/199.0f/10.0f but NOT 5.0f: with the two
 *     globals taking f22/f24 there are only three callee-saved FP registers left.
 *  4. + integer-store source order (unk1E,unk20,unk61,unk62,unk22,unk58,unk60,unk63,
 *     unk64,unk65,unk5C,unk66) -- read straight off golden's store order, since IDO's
 *     scheduler preserves the relative order of integer stores (it freely floats the
 *     FLOAT store of unk24 to the end, which is why unk24's position carries no info)
 *                                                                                  3928
 *  5. + `r1 = func_150ADA20(); r2 = func_150ADA20();` as statements instead of inline
 *     calls in the func_15143794 argument list                                     3548
 *  6. + reuse r1/r2 for the two render flags, restore `speed` as a local            3498
 *
 * NEGATIVES (all measured, frame in brackets):
 *   `params.unk2C = params.unk28 = X;` vs a `size` local:  4122 vs 4434 [0x110/0x118]
 *   reassigning the parameter `arg2` instead of declaring `speed`: byte-identical output
 *     and identical frame -- a WRITTEN-TO parameter gets a home in the local area too,
 *     so that lever cannot shed 4 bytes.
 *   one extra dummy scalar: frame UNCHANGED (0x110) -- the locals area is rounded up to
 *     8, so the declared-scalar count is only observable two at a time.  Two extra
 *     dummies: frame 0x118.
 *   ablation probes for the 12-byte reserved temp area (these are deliberately WRONG
 *     code, run only to read the frame):
 *     delete `params.unk3C = *(struct17*)&D_800A5480;`   4877 [0x110]  (no frame change)
 *     delete `params.unk30 = *arg0;`                     6418 [0x110]  (no frame change)
 *     delete both                                       10163 [0x110]  (no frame change)
 *     delete the func_15143794 call                      8156 [0x100]  <- worth 16 bytes
 *     delete the func_15130280 call                      5758 [0x108]  <- argbuild 24->16
 *   `(f32 *)&params.unk48` instead of `&params.unk48.unk0`: 3928, byte-identical.
 *
 * RESIDUAL at 3498: the instruction stream now aligns row-for-row with golden.  What is
 * left is (a) every sp displacement shifted by 8 because the frame is 0x110 not 0x108,
 * (b) $t*-rotation renumbering through the setup block, (c) $s0/$s1 swapped for r1/r2
 * (golden r1->$s1, r2->$s0; mine the reverse), (d) two scheduling spots: golden splits
 * the second `(s16)` sign-extension of angleBase across 12 instructions and materialises
 * the small `li` constants earlier.
 * NEXT: the frame.  Find what reserves 12 bytes of unused temp; it is not the struct
 * assignments (probes above) and it is not the declared-scalar count.
 * ============================================================================== */
