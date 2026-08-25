/* NEAR-MISS PARK -- func_15122440  (TU game_14F8F0, 336 words)
 * ============================================================================
 * STATUS     : PARKED.  fastscore mism = 181, n = 336/336, frame = 0x78 (EXACT).
 *              First differing row: idx 139 (0x22C).  Rows 0..138 match EXACTLY,
 *              including every register and every sp displacement.
 * FILE KIND  : SELF-CONTAINED BODY TO SPLICE.  Replace the single line
 *              [the GLOBAL-ASM pragma line naming
 *               asm/nonmatchings/game_14F8F0/func_15122440.s -- deliberately not
 *               spelled out here, so this comment can never be picked up
 *               as a live pragma by asm-processor after the splice]
 *              in conker/src/game_14F8F0.c with EVERYTHING in this file below
 *              this header comment -- the declaration block AND the function.
 *              Nothing has to be added anywhere else, and nothing may be left
 *              out: none of D_800894C0, D_800894C8 or D_800A3480..D_800A3498
 *              exists in variables.h, functions.h or structs.h, so splicing the
 *              function alone is a hard CCFAIL ("D_800894C8 undefined").
 *              The TU also holds the MATCHED func_15122980 -- do NOT overwrite
 *              it; the pragma line is the only thing replaced.
 * VERIFIED    : that exact splice into a clean copy of the TU, scored with
 *                python3 tools/fastscore.py game_14F8F0 func_15122440 <copy>
 *              reproduces  mism=181  frame=-120  n=336/336, first diff idx 139.
 *
 * WHAT IS SOLVED (all confirmed by measurement, do not re-derive)
 * ----------------------------------------------------------------------------
 *  * Stack layout is EXACT.  frame 0x78; locals 0x38..0x77; 12 declarations in
 *    this order (first-declared = highest address; that rule was re-confirmed
 *    against the matched sibling func_15122980, which declares struct17 sp44
 *    before struct17 sp38):
 *        struct17 v   @0x6C   f32 t   @0x68   f32 ang @0x64   f32 rot @0x60
 *        f32 s        @0x5C   f32 c   @0x58*  f32 z   @0x54   f32 y   @0x50
 *        f32 x        @0x4C*  f32 a   @0x48   f32 b   @0x44   struct17 dir @0x38
 *    (* = never spills; the two register-only locals.  0x58 and 0x4C are the only
 *    unreferenced slots in golden and they are interchangeable -- swapping c and
 *    x scores the same 181.)  Every referenced spill offset (0x44 0x48 0x50 0x54
 *    0x5C 0x60 0x64 0x68, plus both struct17s) matches golden exactly, so the
 *    declaration ORDER above is forced by measurement, not guessed.
 *  * "pitch" and "rot" are ONE variable (@0x60).  Giving pitch its own local
 *    makes the frame 0x80; merging pitch into c/x/t/y/z instead costs 46..67 rows.
 *  * Both clamps are NESTED TERNARIES, not if/else-if.  if/else spellings cost
 *    33..172 rows.  The tell is the asymmetry
 *        mov.s $f12,$f0                       (outer true arm -> result register)
 *        ... mov.s $f2,$f12 / mov.s $f2,$f0 ; mov.s $f12,$f2   (inner, via a temp)
 *    which is exactly a nested conditional expression.
 *  * D_800894C8 is a struct17 GLOBAL assigned wholesale into the local
 *    (v = D_800894C8) and then fully overwritten -- IDO keeps the dead 3-word copy.
 *  * D_800A3490 and D_800A3494 are two DISTINCT extern f32 objects, both 2.2f.
 *    They cannot be float literals: IDO folds `2.2f + 2.2f` into ONE 4.4f pool
 *    entry (probe: `f32 p7(void){return 2.2f+2.2f;}` -> a single .rodata word).
 *  * The unk86C test is  if (D_800A3488 != arg0->unk86C) { rot = arg0->unk86C; }
 *    else { health chain }.  The other polarity emits bc1fl where golden has bc1tl.
 *
 * REMAINING DIFF (181 rows, all from idx 139 to the end)
 * ----------------------------------------------------------------------------
 * The instruction MULTISET is right nearly everywhere; what differs is the FP
 * register choice and the intra-block schedule.  Two concrete symptoms:
 *
 *  (1) From idx 139 on we are exactly TWO steps behind golden in IDO's FP temp
 *      rotation (f4,f6,f8,f10,f14,f16,f18,...).  At idx 139 golden takes $f14 and
 *      we take $f8; at idx 179..190 golden starts the rotation at $f8 and we start
 *      at $f4.  Rows 0..138 are byte-identical, so nothing BEFORE idx 139 explains
 *      it: the divergence is driven by a global allocation constraint coming from
 *      the second half of the function.
 *
 *  (2) The x/y/z copies.  Golden computes the three
 *          v.unk0 += arg0->unk2BC;  v.unk4 += arg0->unk2C0;  v.unk8 += arg0->unk2C4;
 *      sums into rotation temps $f4/$f10/$f6, stores them to 0x6C/0x70/0x74, and
 *      THEN emits
 *          mov.s $f12,$f4 ; mov.s $f14,$f10 ; mov.s $f16,$f6
 *      (the last one in the delay slot of `beqz $t3, .L15122770`).  We COALESCE:
 *      our three add.s write straight into $f12/$f16/$f14, the three mov.s vanish,
 *      the delay slot has to be filled by the a-constant materialisation instead,
 *      the branch becomes a beqzl, and the whole a/b block is dragged out of shape.
 *      Golden's register order is f12/f14/f16 (definition order); ours f12/f16/f14.
 *
 * BEST THEORY OF THE BLOCKER
 * ----------------------------------------------------------------------------
 * The one lever left is: make IDO NOT coalesce x/y/z with the `+=` results.
 * Golden's three mov.s are a live-range split at the if/else join -- the three
 * values are defined in one block and consumed in BOTH successors.  Every source
 * spelling found that keeps x/y/z as named locals lets IDO forward the store and
 * coalesce; every spelling that REMOVES them makes IDO reload from the struct
 * (0x6C/0x70/0x74) instead of emitting mov.s, which is 2 instructions short and
 * scores worse (204).  If that one thing flips, (1) very plausibly follows: the FP
 * allocator is global and this is the only structural difference left.
 *
 * The a-constant is a second, smaller open question.  Golden emits
 *      lui $at,0x3F800000 ; mtc1 $at,$f18 ; add.s $f0,$f18,$f18       (a = 2.0f)
 * i.e. ONE materialisation of 1.0f used twice inside one add.  Probes show IDO
 * DOES strength-reduce `x * 2.0f` into `x + x` (p1 -> add.s $f0,$f12,$f12) and
 * does NOT fold `a = 1.0f; a + a` in a small function (q1/q3 -> one mtc1 + one
 * add.s $f0,$f2,$f2).  Yet inside THIS function every `a = 1.0f; a = a + a;` /
 * `a *= 2.0f` spelling rematerialises 1.0f TWICE (2 extra instructions, n=338).
 * The current `a = 1.0f + 1.0f` folds to 2.0f, giving the RIGHT instruction count
 * but the wrong shape (mov.s $f2,$f18 where golden has add.s $f0,$f18,$f18).
 * I believe this is downstream of the same knock-on as (2): once the mov.s exist,
 * the beqzl becomes a beqz, the constant is no longer hoisted into the delay slot,
 * and `a = 1.0f; a = a + a;` should collapse to golden's two instructions.
 * FIX (2) FIRST, then re-test the a-spellings.
 *
 * DO-NOT-REPEAT  (every spelling measured, with its fastscore)
 * ----------------------------------------------------------------------------
 *   a = 1.0f + 1.0f;                            181  <- current (IDO folds to 2.0f)
 *   a = 2.0f;                                   181  (byte-identical output)
 *   a = 1.0f * 2.0f;                            181  (folds)
 *   a = 1.0f; a = a + a;                        208  n=338, two mtc1 of 0x3F800000
 *   a = 1.0f; a = a * 2.0f;                     208  same
 *   a = 1.0f; a *= 2.0f;                        208  same
 *   a = 1.0f; a = a + 1.0f;                     208  same
 *   a = 1.0f; a = 1.0f + a;                     208  same
 *   5 statement orderings of the a/b block      206..208
 *   drop x/y/z, use v.unk0/4/8 in both arms     204  n=334, IDO RELOADS, no mov.s
 *   deltas as inline expressions (no x/y/z)     181  byte-identical to current
 *   x = v.unk0 + arg0->unk2BC; v.unk0 = x; ...  181  byte-identical
 *   v.unkN += ...; x = v.unkN;  interleaved     181  byte-identical
 *   all 6 orderings of the x=/y=/z= copies      181  byte-identical (all six)
 *   x/y/z assigned in BOTH if/else arms         226  n=339
 *   swap the two register-only slots (c <-> x)  181  byte-identical
 *   pitch as its own 13th local                 frame 0x80, +8 on every offset
 *   pitch merged into c / x / t / y / z         227 / 248 / 248 / 248 / 248
 *   88-clamp as if/else-if                      274
 *   200-clamp as if/else-if                     214
 *   the 10.0f/0.0f ternary as if/else           297
 *   all 8 combinations of those three           181..353; only all-ternary = 181
 *   arg0->unk3DC = ang moved earlier/later      198..221 (4 placements tried)
 *   struct17 v = D_800894C8;  (initialiser)     181  byte-identical
 *   decomp-permuter, 570+ iterations, harness
 *     selftest PASS, PERMUTER_TU_REQUIRE_FRAME=120
 *                                               best permuter-metric 2765 ->
 *                                               fastscore 195 (WORSE than 181), and
 *                                               its "win" is a split double-store to
 *                                               arg0->unk2F8, i.e. a fake construct.
 *                                               REJECTED.
 *
 * NOT TRIED / NEXT MOVES
 * ----------------------------------------------------------------------------
 *   - Any honest spelling that makes the three x/y/z values arrive at the if/else
 *     join as a live-range split rather than a forwarded store.  None found.
 *   - Re-run the permuter from THIS base with reordering weight raised and
 *     insertion disabled, now gated with PERMUTER_TU_REQUIRE_OFFSETS=1 (the base
 *     now satisfies the offset multiset, so that gate is finally usable).
 *
 * DECLARATIONS
 * ----------------------------------------------------------------------------
 * They are already in this file, immediately below this comment -- splice them
 * with the function.  game_14F8F0.c independently declares D_800A34A0,
 * func_150495B0, func_15123A54, func_1512E140 and func_1512A390 above its
 * pragma, so those are deliberately not repeated here.
 * ============================================================================
 */

/* ---------------------------------------------------------------------------
 * DECLARATIONS REQUIRED BY THE BODY BELOW.
 * They are NOT in variables.h / functions.h / structs.h -- splicing the function
 * without them is a hard CCFAIL ("D_800894C8 undefined").  They are part of this
 * file: splice EVERYTHING below this banner, not just the function.
 * game_14F8F0.c already declares D_800A34A0, func_150495B0, func_15123A54,
 * func_1512E140 and func_1512A390 above its pragma, so those are not repeated.
 * ------------------------------------------------------------------------- */
void func_15123070(struct108 *arg0);

extern f32 D_800894C0;
extern struct17 D_800894C8;
extern f32 D_800A3480;
extern f32 D_800A3484;
extern f32 D_800A3488;
extern f32 D_800A348C;
extern f32 D_800A3490;
extern f32 D_800A3494;
extern f32 D_800A3498;

void func_15122440(struct108 *arg0) {
    struct17 v;
    f32 t;
    f32 ang;
    f32 rot;
    f32 s;
    f32 c;
    f32 z;
    f32 y;
    f32 x;
    f32 a;
    f32 b;
    struct17 dir;

    v = D_800894C8;
    ang = (arg0->unk3D0->unk40 + 90.0f) * D_800A3480;
    func_1512A390(arg0);
    if (((arg0->unk5F0 & 1) == 0) && (arg0->unk3D0->unk102 == 0)) {
        ang = arg0->unk39C - D_800A3484;
    }
    if (D_800A3488 != arg0->unk86C) {
        rot = arg0->unk86C;
    } else if (arg0->unk3D0->health == 0) {
        rot = 0.0f;
    } else {
        rot = ((arg0->unk3D0->unk102 != 0) ? 10.0f : 0.0f) + arg0->unk3D0->unkB8;
    }
    if (arg0->unk3D0->unk102 != 0) {
        rot = rot * 0.5f;
    }
    rot = (rot < -88.0f) ? -88.0f : ((rot > 88.0f) ? 88.0f : rot);
    if (fabsf(D_800894C0 - rot) < 10.0f) {
        rot = D_800894C0;
    } else {
        D_800894C0 = rot;
    }
    rot = rot * D_800A348C;
    func_15123070(arg0);
    if ((*arg0->unk36C & 0x10) != 0) {
        v.unk0 = 150.0f;
    } else {
        v.unk0 = arg0->unk374;
    }
    if ((arg0->unk3D0->unk102 != 0) && (arg0->unk3E8 == 0) && (*(f32 *)((u8 *)arg0 + 0x370) < arg0->unk374)) {
        v.unk0 = *(f32 *)((u8 *)arg0 + 0x370);
    }
    t = cosf(rot) * v.unk0;
    v.unk4 = sinf(rot) * v.unk0;
    v.unk0 = t;
    s = sinf(ang);
    c = cosf(ang);
    *(f32 *)((u8 *)arg0 + 0x3DC) = ang;
    v.unk8 = -v.unk0 * s;
    v.unk0 = v.unk0 * c;
    v.unk4 = (v.unk4 < -200.0f) ? -200.0f : ((v.unk4 > 200.0f) ? 200.0f : v.unk4);
    v.unk0 += arg0->unk2BC;
    v.unk4 += arg0->unk2C0;
    v.unk8 += arg0->unk2C4;
    x = v.unk0;
    y = v.unk4;
    z = v.unk8;
    if (arg0->unk23C != 0) {
        arg0->unk2F8 = x;
        arg0->unk2FC = y;
        arg0->unk300 = z;
        *(f32 *)((u8 *)arg0 + 0x3C0) = 0.0f;
        *(f32 *)((u8 *)arg0 + 0x3C4) = 0.0f;
        *(f32 *)((u8 *)arg0 + 0x3C8) = 0.0f;
    } else {
        a = 1.0f + 1.0f;
        b = D_800A3490 + D_800A3494;
        if (arg0->unk3D0->unk102 != 0) {
            a += a;
            b += b;
        }
        func_150495B0(&arg0->unk2F8, x, (f32 *)((u8 *)arg0 + 0x3C0), a, b, arg0->unk7B4);
        func_150495B0(&arg0->unk2FC, y, (f32 *)((u8 *)arg0 + 0x3C4), a, b, arg0->unk7B4);
        func_150495B0(&arg0->unk300, z, (f32 *)((u8 *)arg0 + 0x3C8), a, b, arg0->unk7B4);
    }
    if ((arg0->unk3D0->unk102 == 0) && ((arg0->unk36A & 0x10) == 0)) {
        x = arg0->unk2F8 - arg0->unk2BC;
        y = arg0->unk2FC - arg0->unk2C0;
        z = arg0->unk300 - arg0->unk2C4;
        if (sqrtf((x * x) + (y * y) + (z * z)) < 120.0f) {
            func_150491EC((struct17 *)&arg0->unk2BC, (struct17 *)&arg0->unk2F8, &dir);
            arg0->unk2F8 = arg0->unk2BC + (120.0f * dir.unk0);
            arg0->unk2FC = arg0->unk2C0 + (120.0f * dir.unk4);
            arg0->unk300 = arg0->unk2C4 + (120.0f * dir.unk8);
        }
    }
    if (arg0->unk2FC < (arg0->unk35C + 30.0f)) {
        arg0->unk2FC = arg0->unk35C + 30.0f;
    }
    arg0->unk5E8 = arg0->unk5E8 + ((*(f32 *)((u8 *)arg0 + 0x5EC) - arg0->unk5E8) * D_800A3498);
    arg0->unk348 = *(f32 *)((u8 *)arg0 + 0x344) = arg0->unk2FC - arg0->unk354;
    x = arg0->unk2F8 - arg0->unk2BC;
    z = arg0->unk300 - arg0->unk2C4;
    *(f32 *)((u8 *)arg0 + 0x370) = sqrtf((x * x) + (z * z));
}
