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
