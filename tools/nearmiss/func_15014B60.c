/* ============================================================================
 * NEAR-MISS PARK: game_40490 / func_15014B60   (259 insns / 1036 bytes)
 * BEST MEASURED RESIDUAL: 49 mismatching instructions out of 259, but only
 *   TWO independent causes:
 *     (a) FRAME IS 8 BYTES TOO BIG (0xE0 vs golden 0xD8).  That alone shifts
 *         every local by +8 and accounts for ~44 of the 49 rows -- they are
 *         all `swc1 $fX,N+8(sp)` vs `swc1 $fX,N(sp)`, identical opcodes and
 *         identical registers.
 *     (b) a 4-instruction BLOCK MOVE: golden loads D_800966A0/D_800966A4 into
 *         $f0/$f2 before the third random's `mflo`, mine loads them ~9 insns
 *         later after the third `mul.s`.  Same multiset.
 *   symbol size mine == gold (0x40C).  The whole 6-iteration spawn loop, all
 *   three ternaries, both do-while loops and the entire epilogue are
 *   byte-identical INCLUDING register names.
 *
 * MEASUREMENT: symbol-bounded objdump compare (scratchpad/w40490_bounded.py),
 * object force-rebuilt before every measurement, all under tools/buildlock.sh.
 *
 * THE RESIDUAL, PRECISELY NAMED
 * -----------------------------
 * The declaration list is PROVEN CORRECT: golden's locals sit at
 *   header@0x74  header2@0x7C  i@0x88  temp_v0@0x8C  payload@0x90
 * and mine sit at exactly the same RELATIVE offsets
 *   header@0x7C  header2@0x84  i@0x90  temp_v0@0x94  payload@0x98
 * -- the local BLOCK is 100 bytes in both.  What differs is the compiler
 * TEMP-RESERVATION area that sits between the saved-register block (0x38..0x5F,
 * identical in both) and the first local: golden reserves 20 bytes (0x60..0x73),
 * mine reserves 28 (0x60..0x7B).  Nothing is ever stored into that region in
 * either build; it is a pure reservation, so the +8 is IDO deciding my float
 * expression region needs two more spill slots than golden's.
 *
 * The reservation is a THRESHOLD, not a per-statement cost.  Measured by
 * ablation (frame size of the resulting object):
 *   full (3 randoms + 4 packed-field lines) ............ 224
 *   drop the 3rd random ................................ 216   <- golden's size
 *   drop the 2nd random ................................ 216
 *   drop all 3 randoms ................................. 216
 *   drop payload.unk18 only ............................ 224
 *   drop payload.unk1C only ............................ 224
 *   drop payload.unk20 only ............................ 224
 *   drop payload.unk3C only ............................ 224
 *   drop payload.unk1C AND unk20 (1 use of A0/A4 left) . 216
 *   drop the whole packed-field block .................. 216
 * i.e. it needs (>=3 osGetCount()/RNG randoms) AND (>=3 uses of the CSE'd
 * D_800966A0 * D_800966A4 constant pair) to trip.  Golden has 3 and 3 and
 * does NOT trip, so golden's C expresses one of the two in a form that costs
 * one fewer live float temp.  I could not find that form.  OPEN -- this is
 * the one of my three residuals that still has levers (see below).
 *
 * EVERYTHING I RULED OUT, WITH ITS SCORE / FRAME  (baseline 49 / -224)
 * -------------------------------------------------------------------
 * `(f32)((osGetCount()*RNG()) & 0xFFFFU) * D * 360.0f` explicit left parens . 49/224
 * `* 360.0f * D` (swap the two multiplies) ................................. 57/224
 * `(u32)func_150ADA20()` cast .............................................. 49/224
 * `(0xFFFFU & (osGetCount()*RNG()))` (mask on the left) .................... 49/224
 * `(f32)(u32)((osGetCount()*RNG()) & 0xFFFF)` .............................. 49/224
 * `& 0xFFFF` (signed mask) instead of `& 0xFFFFU` .......................... 49/224
 * `360.f` instead of `360.0f` .............................................. 49/224
 * `(f32)((u32)arg0->unk18 & 0xFFFFU)` extra cast ........................... 49/224
 * `D_800966A0 * (f32)x * D_800966A4` (reassociated) ........................ 49/224
 * `* (D_800966A0 * D_800966A4)` (constants folded first) ................... 168/216
 *     -> reaches the golden FRAME but emits 2 fewer instructions (sizedelta
 *        -8): golden really does do value*A0 then *A4, so this is not it.
 * `func_150ADA20() * osGetCount()` (operand swap) .......................... 257/216
 *     -> also reaches the golden frame, but IDO then masks the u8 return with
 *        `andi s3,v0,0xff` and drops a saved register.  Golden has NO andi
 *        and saves s0..s7+fp+ra, so osGetCount() is definitively the LEFT
 *        operand.  (Useful negative: it proves IDO evaluates `a()*b()`
 *        left-to-right here.)
 * `payload.unk40 = arg0;` before `payload.unk44 = 1;` ...................... 49/224
 * `while` loop instead of `for` ............................................ 51/224
 * `s32 i;` declared before `temp_v0` ....................................... 49/224
 * `Header header;` block-scoped inside the for loop ........................ 45/224
 * `Header header;` declared before `Header2 header2;` ...................... 45/224
 *     (both 45s still carry the +8 frame; they are noise, not progress)
 * removing the else-branch cleanup loop .................................... 85/224
 *     -> the else branch is NOT the source of the extra temps
 * moving the new `extern` decls to the top of the TU ....................... 49/224
 * other two target functions live vs pragma'd .............................. 49/224
 *
 * LEVERS THAT REMAIN (why this is OPEN, not BOUNDED)
 * -------------------------------------------------
 *  * a file-local struct134 shadow typedef with u32 unk18/unk1C, which would
 *    remove the `(u32)` casts from the shift expressions and may change how
 *    many float temps IDO reserves.  I did not try it because struct134 is
 *    used by ~15 already-matching functions in this TU and a shadow risks
 *    them; it needs a whole-TU re-score to be safe.
 *  * a file-local prototype for func_150ADA20 (functions.h says it returns u8;
 *    a different return type changes multu/mult and the temp accounting).
 *    Same whole-TU risk -- func_15013DE8 and func_15014F6C also call it.
 *  * the decomp-permuter: unlike my other two parks this residual HAS a
 *    structural handle (an expression-form change that moves the frame), which
 *    conker-permuter-setup.md records as the case the permuter cracks.  The
 *    caveat is that game_40490.c has 25 functions and permuter zeros stop
 *    transferring at that size.
 * ========================================================================= */

extern f32 D_80096698;
extern f32 D_8009669C;
extern f32 D_800966A0;
extern f32 D_800966A4;
extern f32 D_800966A8;
extern f32 D_800966AC;
extern f32 D_800966B0;
extern u8 D_800A0938[];
struct225 *func_151602C0(Header *header, Header2 *header2, s32 arg2, s32 arg3, s32 arg4, s32 arg5, u8 arg6, u8 arg7, s32 offset, u8 arg9, s32 argA);

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
    struct225 *unk24[6];
    f32 unk3C;
    struct134 *unk40;
    u8 unk44;
    u8 pad45[3];
} Struct15014B60;

/* Behaviour: spawns a six-part particle/sprite cluster (a fire, smoke plume or
 * similar) anchored on the object.  It seeds three pseudo-random angles in
 * 0..360 from osGetCount() * func_150ADA20() masked to 16 bits, unpacks four
 * 16-bit fields out of arg0->unk18/unk1C into scaled floats (three sharing one
 * constant pair, the fourth with its own), then loops six times calling
 * func_151602C0 with a common 6-byte header (type 2, -1, lifetime 0x12C, 0) and
 * the object's integer XYZ, tinting each part either solid red (0xFF,0,0) when
 * the current level D_800BE9F0 == 0x40 or with the level-independent palette
 * D_800A0938[i*3 + 0..2] otherwise, and stores the six handles in the payload.
 * The 0x48-byte payload is memcpy'd into a freshly-allocated type-0x2E effect
 * record; if that allocation fails, the six parts are released again with
 * func_1516972C so nothing leaks.  Always returns 1. */
s32 func_15014B60(struct134 *arg0) {
    Struct15014B60 payload;
    struct260 *temp_v0;
    s32 i;
    Header2 header2;
    Header header;

    arg0->unk16 |= 4;
    payload.unk44 = 1;
    payload.unk40 = arg0;
    payload.unk0 = (f32)arg0->unk0;
    payload.unk4 = (f32)(s16)arg0->unk2;
    payload.unk8 = (f32)arg0->unk4;
    payload.unkC = (f32)((osGetCount() * func_150ADA20()) & 0xFFFFU) * D_80096698 * 360.0f;
    payload.unk10 = (f32)((osGetCount() * func_150ADA20()) & 0xFFFFU) * D_8009669C * 360.0f;
    payload.unk14 = (f32)((osGetCount() * func_150ADA20()) & 0xFFFFU) * D_800966A8 * 360.0f;
    payload.unk18 = (f32)(arg0->unk18 & 0xFFFFU) * D_800966A0 * D_800966A4;
    payload.unk1C = (f32)(((u32)arg0->unk18 >> 16) & 0xFFFFU) * D_800966A0 * D_800966A4;
    payload.unk20 = (f32)(arg0->unk1C & 0xFFFFU) * D_800966A0 * D_800966A4;
    payload.unk3C = (f32)(((u32)arg0->unk1C >> 16) & 0xFFFFU) * D_800966AC * D_800966B0;

    header2.unk0 = arg0->unk0;
    header2.unk4 = (s16)arg0->unk2;
    header2.unk8 = arg0->unk4;

    for (i = 0; i < 6; i++) {
        header.unk0 = 2;
        header.unk1 = -1;
        header.unk2 = 0x12C;
        header.unk4 = 0;
        payload.unk24[i] = func_151602C0(&header, &header2, 5,
                                         (D_800BE9F0 == 0x40) ? 0xFF : D_800A0938[i * 3],
                                         (D_800BE9F0 == 0x40) ? 0 : D_800A0938[(i * 3) + 1],
                                         (D_800BE9F0 == 0x40) ? 0 : D_800A0938[(i * 3) + 2],
                                         0xFF, 0, 0, 0xFF, 0);
    }

    temp_v0 = func_15149130(0x12C, -1, 0x2E, -1, 0, 0x29, (struct37 *)0x48, 0xFF, 0);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &payload, 0x48);
    } else {
        for (i = 0; i < 6; i++) {
            if (payload.unk24[i] != NULL) {
                func_1516972C((struct102 *)payload.unk24[i]);
            }
        }
    }
    return 1;
}
