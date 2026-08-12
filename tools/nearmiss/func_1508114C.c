/* PARKED near-miss: func_1508114C  (game_AE1D0.c, 1064 bytes, frame 0xE0)
 *
 * BEST SCORE 960 (asm-differ -o func_1508114C -R --max-lines 4096; identical without -R).
 * Bounded: mips-linux-gnu-readelf -sW expected/build/src/game_AE1D0.c.o -> size=1064, so the
 * score is trustworthy.  Built size 1068 = exactly ONE extra instruction (a nop, see below).
 * .rodata / .data already IDENTICAL; only .text differs.
 *
 * WHAT IT IS.  Ray vs. per-bone hit-sphere test for one actor.  Broad-phase: build the whole-
 * object bounding sphere from D_800D1C90[obj->id] (height at +0x10 * y_scale + y_position;
 * radius at +0xE * y_scale) and ray-test it with func_151452C4 (ray/sphere, prototype taken
 * from the LIVE C in game_16EE20.c/game_200930.c).  If that hits, walk the model's hit-sphere
 * table -- D_80086C60[type] / count D_8009CBCC[type], type = D_8009BD32[idx*4] where
 * idx = func_1508108C(obj) -- skipping bones masked off in obj->unk9C, transforming each
 * sphere's local offset by its bone matrix (func_15143134(src,dst,(s32)obj->unk1D4+(bone<<6)))
 * and keeping the nearest/highest-priority hit.  Returns -1 (no skeleton / unknown model),
 * 0 (miss) or 1 (hit) and fills eleven output parameters.
 *
 * ORIGINAL-GAME BUG, reproduced deliberately: after the loop the code does
 *     if (*outDist == -1.0f) return 0;
 *     *outDist = tNear;
 * which overwrites the tracked best distance with the LAST call's near-t.  The golden asm
 * (0x15081460..0x15081484) does exactly this; do not "fix" it.
 *
 * FRAME DECODE (this is what got the frame exactly right -- frame 0xE0 matches).
 *   saved regs 0x28..0x57 (f20 + s0-s7,fp,ra), arg build 0x00..0x1F, temps 0x58..0x5C.
 *   Home area 0x5C..0xE0 = 0x84 = 132 bytes = 12 scalars (48) + 7 struct17 (84):
 *     0xDC ---  0xD8 spheres  0xD4 count  0xD0 ---  0xCC bestIndex  0xC8 tNear  0xC4 tFar
 *     0xC0 ---  then the seven struct17 at 0xB4 0xA8 0x9C 0x90 0x84 0x78 0x6C, then four more
 *     scalars below the structs at 0x68 0x64 0x60 0x5C.
 *   Only five of the twelve scalars ever touch their home (spheres, count, bestIndex, tNear,
 *   tFar) -- the other seven live in registers, which is why the count, not the naming, is
 *   what the frame pins down.  Going 10 -> 12 scalars is what moved 2207 -> 960.
 *
 * MEASURED NEGATIVES (all re-scored through make + buildlock + real asm-differ):
 *   - 8 scalars + 7 struct17 (frame 0xD8, 8 bytes short) ................. score 2585
 *   - 10 scalars, index cursor spheres[i], `best = &spheres[bestIndex]` ... score 1715 (frame 0xE0
 *       by luck: that shape needs 12 bytes of temp; but both addu operand orders are wrong)
 *   - 10 scalars, pointer cursor + inline tail (frame 0xD8) .............. score 2207
 *   - 11 scalars (cursor + `best` variable) ............................. score 1750
 *   - 12 scalars, `p = &spheres[i]` at top of body instead of a cursor ... score 1276
 *   - 12 scalars, `mtx` variable for the matrix arg instead of `hit` ..... score 1320 (1060 bytes)
 *   - swapping the declaration order of `hit` and `radius` .............. score 960 (no change)
 *   - using `hit` for the in-loop func_151452C4 call as well ............ score 960 (no change)
 *
 * TWO LEVERS THAT PAID, both found with an isolated IDO micro-benchmark (t2.c):
 *   (a) `addu` operand order.  `(s32)o->m + (p->bone << 6)` with p an explicit POINTER CURSOR
 *       emits `addu a2,<base>,<offset>` (golden); with an INDEX `p[i].bone` it emits
 *       `addu a2,<offset>,<base>`.  Golden is base-first => the loop uses a cursor.
 *   (b) the same test on the tail: `q = &p[k]; q->part` gives offset-first, `p[k].part` inline
 *       gives base-first.  Golden is base-first => the tail is NOT cached in a pointer local.
 *   Also verified: IDO uses UNSIGNED-PRESERVING promotion, so a plain `u16` field feeding a
 *   float gives the `bgez`/`+2^32` sequence with no `(u32)` cast needed.
 *
 * RESIDUAL (everything below 0x5c0 is byte-identical; ~all of the 960 is one region):
 *   1. `lw s0,0xd8(sp)` (p = spheres) sits BEFORE the `blez` count guard in mine and in the
 *      loop preheader AFTER it in golden -- one displaced instruction.
 *   2. golden hoists `lw v0,0x1d4(s2)` nine instructions early (into v0) and fills the
 *      mtc1->cvt.s.w delay with `move a1,s3`; mine keeps it adjacent to the jal and emits a
 *      nop at 0x5ec.  That nop is the whole +4-byte size difference.
 *   3. downstream of (2), the t-register rotation in the loop and the tail runs one slot
 *      behind golden (t4 where golden has t3, etc.).  Pure cascade, no extra instructions.
 *   Next thing to try: the permuter, seeded with this file (this is the "hand-reduced base"
 *   case it is good at).  Do NOT ship a version with a dead local added to force the hoist.
 *
 * TU state: the #pragma GLOBAL_ASM for func_1508114C is LIVE in game_AE1D0.c; this file is the
 * working C only.  The typedefs/externs below must be added to the TU alongside the function.
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
    s32 hit;
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
    hit = func_151452C4(rayOrigin, rayDir, &centre, radius, &near, &far, &tNear, &tFar);
    if (hit == 0) {
        return 0;
    }
    bestPart = -1;
    p = spheres;
    for (i = 0; i < count; i++, p++) {
        if (((1 << p->bone) & obj->unk9C) != 0) {
            continue;
        }
        local.unk0 = p->x;
        local.unk4 = p->y;
        local.unk8 = p->z;
        func_15143134(&local, &centre, (s32)obj->unk1D4 + (p->bone << 6));
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

#pragma GLOBAL_ASM("asm/nonmatchings/game_AE1D0/func_15081574.s")
