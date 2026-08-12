/* PARKED near-miss: func_1508114C  (game_AE1D0.c, 1064 bytes, frame 0xE0)
 *
 * BEST SCORE 60  (was 960 at the end of wave 23).
 *   cd conker && python3 ../tools/asm-differ/diff.py -o func_1508114C -R --max-lines 4096
 *   identical without -R.  Bounded: readelf -sW expected/build/src/game_AE1D0.c.o -> 1064.
 *   Built size is now EXACTLY 1064 (wave 23 was 1068, one nop long).
 *   .rodata / .data IDENTICAL.
 *
 * THE ENTIRE RESIDUAL IS ONE DISPLACED INSTRUCTION:
 *     golden   5ac: li   s4,-1
 *              5b0: blez t5,740          <- loop guard
 *              5b4:  move s1,zero        <- delay slot, i = 0
 *              5b8: lw   s0,0xd8(sp)     <- p = spheres, in the LOOP PREHEADER
 *              5bc: addiu s8,sp,0x84
 *     mine     5ac: li   s4,-1
 *              5b0: lw   s0,0xd8(sp)     <- p = spheres, BEFORE the guard
 *              5b4: blez t5,740
 *              5b8:  move s1,zero
 *              5bc: addiu s8,sp,0x84
 *   Every other byte of the 1064 is identical.  Golden puts the reload of `spheres` into
 *   the compiler-generated preheader (the block after the count guard, alongside the
 *   hoisted `addiu fp,sp,0x84` and the rotated first `lbu t6,0(s0)`); mine emits it as a
 *   plain statement before the guard.  Classification: this is neither a register tie nor
 *   a scheduling tie inside a block -- it is IDO's choice of BASIC BLOCK for a spilled
 *   variable's reload, and the only source-level control over it found so far is the loop
 *   shape (see NEGATIVES).
 *
 * WHAT IT IS.  Ray vs. per-bone hit-sphere test for one actor.  Broad-phase: build the whole-
 * object bounding sphere from D_800D1C90[obj->id] (height at +0x10 * y_scale + y_position;
 * radius at +0xE * y_scale) and ray-test it with func_151452C4 (ray/sphere, prototype taken
 * from the LIVE C in game_16EE20.c/game_200930.c).  If that hits, walk the model's hit-sphere
 * table -- D_80086C60[type] / count D_8009CBCC[type], type = D_8009BD32[idx*4] where
 * idx = func_1508108C(obj) -- skipping bones masked off in obj->unk9C, transforming each
 * sphere's local offset by its bone matrix (func_15143134) and keeping the nearest /
 * highest-priority hit.  Returns -1 (no skeleton / unknown model), 0 (miss) or 1 (hit) and
 * fills eleven output parameters.
 *
 * ORIGINAL-GAME BUG, reproduced deliberately: after the loop the code does
 *     if (*outDist == -1.0f) return 0;
 *     *outDist = tNear;
 * which overwrites the tracked best distance with the LAST call's near-t.  The golden asm
 * (0x15081460..0x15081484) does exactly this; do not "fix" it.
 *
 * FRAME DECODE (frame 0xE0, confirmed to the byte).
 *   arg build 0x00..0x27, saved regs 0x28..0x57 (f20 + s0-s7,fp,ra), compiler TEMP 0x58..0x5C
 *   (4 bytes), home area 0x5C..0xE0 = 0x84 = 132 = 12 scalars (48) + 7 struct17 (84):
 *     0xDC idx   0xD8 spheres  0xD4 count  0xD0 type  0xCC bestIndex  0xC8 tNear  0xC4 tFar
 *     0xC0 i  |  0xB4 centre  0xA8 bestCentre  0x9C near  0x90 far  0x84 local  0x78 bestNear
 *     0x6C bestFar  |  0x68 bestPart  0x64 p  0x60 mtx  0x5C radius
 *   Confirmed against golden: sw t9,0xd8 / sw t1,0xd4 / sw s1,0xcc / addiu t3,sp,0xc8 /
 *   addiu t4,sp,0xc4 / swc1 f4,0xb4 / addiu t8,sp,0xa8 / addiu s5,sp,0x9c / addiu s6,sp,0x90 /
 *   addiu fp,sp,0x84 / addiu t2,sp,0x78 / addiu t5,sp,0x6c.
 *   The four scalars BELOW the structs never touch their homes, so their ORDER is free but
 *   their COUNT is not: 12 scalars is what the frame demands.
 *
 * THE TWO LEVERS THAT TOOK 960 -> 60 (wave 24), both load-bearing, each re-measured alone:
 *  (1) `mtx` -- read obj->unk1D4 into a local BEFORE the three `local.unkN` stores.
 *      WHY: `local`'s address is taken (passed to func_15143134), so the stores to it are
 *      potential aliases and IDO's scheduler CANNOT hoist a load above them.  Golden's
 *      `lw v0,0x1d4(s2)` sits at the TOP of the loop body, 20 instructions before its use,
 *      which is only reachable if the read is generated before the stores -- i.e. it is a
 *      separate statement in the source.  With the read left inline in the call argument the
 *      load stays pinned next to the jal, the mtc1->cvt.s.w delay cannot be filled, and IDO
 *      emits a nop (that nop was the whole 1068-vs-1064 size difference).
 *      `mtx` replaces `hit`: the broad-phase result is tested inline, keeping 12 scalars.
 *  (2) `(s32)mtx` -- the CAST at the point of use, with `mtx` declared `u8 *`.
 *      WHY: golden is `addu a2,v0,t7` (base first).  For `<variable> + <temp>` IDO
 *      canonicalises the TEMP to the first operand regardless of how the source is written
 *      (`mtx + (p->bone << 6)` and `(p->bone << 6) + mtx` both give `addu a2,t7,v0`).  For
 *      `<temp> + <temp>` it keeps source order.  A cast node makes the variable a temp, so
 *      `(s32)mtx + (p->bone << 6)` restores golden's operand order.  Worth 10 points and,
 *      more importantly, it is the only spelling that is actually golden-shaped.
 *
 * MEASURED NEGATIVES (every one re-scored through make + buildlock + the real asm-differ,
 * with the pragma removed and the object asserted to exist):
 *   wave 24, from the 960 base:
 *   - `for (i = 0, p = spheres; ...)` instead of `p = spheres;` before the for ..... 960 (no change;
 *       it only swaps WHICH of the two inits lands in the blez delay slot -- `move s1` moves
 *       to 5b0 and `lw s0` becomes the delay slot.  Same cost, different displaced row.)
 *   - `for (p = spheres, i = 0; ...)` ............................................. 70 (same as base+mtx)
 *   - `p = spheres;` placed BEFORE `bestPart = -1;` ............................... 75 (worse: the lw
 *       moves up another slot, above `li s4,-1`)
 *   - mtx as `s32` with `mtx + (p->bone << 6)` ................................... 70
 *   - mtx as `s32` with `(p->bone << 6) + mtx` ................................... 70 (IDO ignores
 *       the source operand order here -- see lever (2))
 *   - mtx as `u8 *` with `mtx + (p->bone << 6)` (pointer arithmetic, no cast) ..... 70
 *   - mtx as `s32` with `mtx += p->bone << 6;` then passing mtx .................. 70
 *   - mtx as `s32` with `(s32)(mtx + (p->bone << 6))` ............................ 70
 *   - `mtx = (s32)obj->unk1D4 + (p->bone << 6);` (WHOLE address in the local),
 *       statement placed BEFORE the local.unkN stores ............................ 1320, 1060 bytes
 *       (this is wave 23's "mtx variable" negative.  It loses TWO instructions: with the
 *        bone read pulled up next to the mask test's bone read, and no aliasing store
 *        between them, IDO CSEs the two `lbu 0(s0)` into one.  Golden has two.)
 *   - the same statement placed AFTER the stores ................................. 960
 *   - `if (count > 0) { p = spheres; do { ... } while (i != count); }` with `i = 0`
 *       before the if ............................................................ 105
 *       *** this shape DOES fix the lw s0 placement -- it is the only one found that does ***
 *       but it re-ranks the saved registers: golden has s7=outDist, s5=&near, s6=&far and
 *       this shape gives s5=outDist, s6=&near, s7=&far, a 3-cycle rotation costing 20 rows.
 *   - the same with `while (i < count)` .......................................... 105
 *   - the same with `i = 0;` and `bestPart = -1;` swapped ........................ 215
 *   - the same with `i = 0;` moved inside the if ................................. 160
 *   - the same with `p = spheres; i = 0;` inside the if .......................... 220
 *   - do-while shape with the read left INLINE (no mtx) .......................... 995
 *   - index cursor `spheres[i]` everywhere, 12 scalars ........................... 386, frame 0xE8
 *       (the index form ALSO puts the reload in the preheader -- IDO strength-reduces it into
 *        an induction pointer initialised there -- but it needs 12 bytes of compiler temp
 *        instead of 4, so the frame grows by 8.)
 *   - index cursor with the declaration list cut to 10 scalars to pay for the temp
 *       (`hit` and `radius` both inlined) so the frame is 0xE0 again ............. 485
 *       (frame and every stack offset correct, but inlining `radius` rotates the whole
 *        floating-point register assignment: f0/f4/f6/f8/f10/f16/f18 all shift.  This is
 *        positive evidence that `radius` is a REAL local, not frame filler.)
 *   wave 23, from scratch (kept for the record):
 *   - 8 scalars + 7 struct17 (frame 0xD8) ....................................... 2585
 *   - 10 scalars, index cursor, `best = &spheres[bestIndex]` .................... 1715
 *   - 10 scalars, pointer cursor + inline tail (frame 0xD8) ..................... 2207
 *   - 11 scalars (cursor + `best` variable) ..................................... 1750
 *   - 12 scalars, `p = &spheres[i]` at top of body instead of a cursor ........... 1276
 *   - swapping the declaration order of `hit` and `radius` ...................... 960 (no change)
 *   - using `hit` for the in-loop func_151452C4 call as well .................... 960 (no change)
 *
 * THE PERMUTER HAS BEEN RUN ON THIS.  conker/permuter_tu.sh setup + selftest PASS (base
 * score 60, harness object byte-identical to the Makefile object, pycparser round trip
 * codegen-neutral, negative control 65).  ~500 iterations at -j 4 with
 * PERMUTER_TU_REQUIRE_FRAME=224 PERMUTER_TU_REQUIRE_OFFSETS=1 produced NO output-* at all,
 * i.e. it never beat 60.  Note the harness directory must live on the Linux filesystem
 * ($HOME/permtu_1508114C) -- inside the repo on /mnt/c the IDO `cc` cannot write its object
 * and every selftest stage fails with a bogus "No such file or directory".
 *
 * WHAT TO TRY NEXT.  The question is now completely isolated: get `lw s0,0xd8(sp)` into the
 * loop preheader WITHOUT the saved-register rotation the do-while shape causes.  Either
 *   (a) find out what re-ranks {outDist, near, far} between the for shape and the
 *       if+do-while shape (they have identical reference counts, so it is the extra basic
 *       block); if that can be neutralised, the do-while shape closes the function; or
 *   (b) find a for-loop spelling in which `p = spheres` is sunk past the guard.
 *
 * TU state: the #pragma GLOBAL_ASM for func_1508114C is LIVE in game_AE1D0.c and the tree is
 * clean; this file is the working C only.  The typedefs/externs below go with the function.
 */

/* One hit sphere bound to a bone of a model. */
typedef struct {
    /* 0x0 */ u8  bone;
    /* 0x1 */ u8  part;
    /* 0x2 */ u16 radius;
    /* 0x4 */ s16 x;
    /* 0x6 */ s16 y;
    /* 0x8 */ s16 z;
} HitSphere; /* size 0xA */

/* struct124 (include/structs.h) has the wrong types at 0xE/0x10: the game reads
 * a u16 at 0xE and an s16 at 0x10, not an s16 and an s32. */
typedef struct {
    /* 0x00 */ u8  pad0[0xE];
    /* 0x0E */ u16 body_radius;
    /* 0x10 */ s16 body_height;
} ModelBounds;

/* D_8009BD30 is an array of 4-byte records; the byte at +2 of record N selects
 * which hit-sphere table the model uses. */
extern u8 D_8009BD32[];
extern HitSphere *D_80086C60[];
extern u8 D_8009CBCC[];

s32 func_151452C4(struct17 *arg0, struct17 *arg1, struct17 *arg2, f32 arg3, struct17 *arg4, struct17 *arg5, f32 *arg6, f32 *arg7);

s32 func_1508114C(struct127 *obj, struct17 *rayOrigin, struct17 *rayDir, struct17 *outNear, struct17 *outFar, struct17 *outCentre, f32 *outDist, s32 *outIndex, s32 *outBone, s32 *outPart, s16 *outOffset) {
    s32 idx;
    HitSphere *spheres;
    s32 count;
    s32 type;
    s32 bestIndex;
    f32 tNear;
    f32 tFar;
    s32 i;
    struct17 centre;
    struct17 bestCentre;
    struct17 near;
    struct17 far;
    struct17 local;
    struct17 bestNear;
    struct17 bestFar;
    s32 bestPart;
    HitSphere *p;
    u8 *mtx;
    f32 radius;

    if (obj->unk1D4 == NULL) {
        return -1;
    }
    idx = func_1508108C((Struct1508108C *)obj);
    if (idx == -1) {
        return -1;
    }
    type = D_8009BD32[idx * 4];
    spheres = D_80086C60[type];
    count = D_8009CBCC[type];
    *outDist = -1.0f;
    centre.unk0 = obj->x_position;
    centre.unk4 = (((ModelBounds *)D_800D1C90[obj->id])->body_height * obj->y_scale) + obj->y_position;
    centre.unk8 = obj->z_position;
    radius = ((ModelBounds *)D_800D1C90[obj->id])->body_radius * obj->y_scale;
    if (func_151452C4(rayOrigin, rayDir, &centre, radius, &near, &far, &tNear, &tFar) == 0) {
        return 0;
    }
    bestPart = -1;
    p = spheres;
    for (i = 0; i < count; i++, p++) {
        if (((1 << p->bone) & obj->unk9C) != 0) {
            continue;
        }
        mtx = (u8 *)obj->unk1D4;
        local.unk0 = p->x;
        local.unk4 = p->y;
        local.unk8 = p->z;
        func_15143134(&local, &centre, (s32)mtx + (p->bone << 6));
        if (func_151452C4(rayOrigin, rayDir, &centre, p->radius * obj->xz_scale, &near, &far, &tNear, &tFar) != 0) {
            if ((*outDist == -1.0f) || ((tNear < *outDist) && (p->part >= bestPart))) {
                *outDist = tNear;
                bestNear = near;
                bestFar = far;
                bestCentre = centre;
                bestIndex = i;
                bestPart = p->part;
            }
        }
    }
    if (*outDist == -1.0f) {
        return 0;
    }
    *outDist = tNear;
    *outIndex = bestIndex;
    *outPart = spheres[bestIndex].part;
    *outBone = spheres[bestIndex].bone;
    outOffset[0] = spheres[bestIndex].x;
    outOffset[1] = spheres[bestIndex].y;
    outOffset[2] = spheres[bestIndex].z;
    *outNear = bestNear;
    *outFar = bestFar;
    if (outCentre != NULL) {
        *outCentre = bestCentre;
    }
    return 1;
}
