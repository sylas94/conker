/* func_150611E8 (game_83300.c, 1012 B) -- best measured score 4538.
 *
 * WHAT IT DOES (settled, read straight off the asm -- the logic below is believed exact):
 *   Path/waypoint follower.  (*(u8 **)&D_800D2108)[arg1] is the node COUNT of path arg1;
 *   D_800D2104[arg1] is the node array, 8-byte records {s16 x; s16 y; s16 z; u16 radius}
 *   (field roles confirmed against the already-matched func_15056150 / func_1505693C in the
 *   same TU: x at +0, y at +2, z at +4, radius at +6).  It truncates the actor's world
 *   x/z to s16, finds the nearest node in the XZ plane, nudges the index back one node when
 *   the winning distance^2 exceeds 28000 and the previous node is nearer than the next,
 *   then steers the actor towards the segment with func_150593C4(actor, atan2ish, radius,
 *   lerp) and, for wide segments (radius > 20), stashes `angle | 1` in
 *   ((struct126 *)actor->unk31C)->unk68.
 *
 *   NOT a bug to "fix": bestIdx is genuinely read uninitialised when the loop does not run
 *   (golden does `lw t4,0x30(sp)` before any store to it).  count >= 3 makes that
 *   unreachable in practice; reproduce it, do not initialise it.
 *
 * WHAT IS ALREADY BYTE-EXACT with this C:
 *   - entry / count fetch / `count < 3` early-out (incl. the branch-likely `lw ra` delay slot)
 *   - the s16 truncation of x_position/z_position (trunc.w.s + sll/sra)
 *   - `best = 0x7FFFFFFF` (lui/ori), the x4 loop unroll with the `count & 3` remainder loop,
 *     and the recomputation of (dx*dx + dz*dz) inside the then-branch
 *   - the whole `best > 28000` refinement block (offsets +8/+C and -8/-4 off one base)
 *   - the u32->f32 conversion of radius (bgez / 0x4F800000 path), the D_8009968C multiply,
 *     the clamp to 1.0f, the func_1505A630 call and its hoisted `a2 = 0`
 *   - the 20.0f test and the `sh angle|1, 0x68(ptr)` store
 *
 * RESIDUAL -- two coupled artefacts, neither reachable from any spelling tried:
 *
 *  (1) FRAME SIZE: golden 0x38, this 0x48.  Local area is [frame_top - S, frame_top);
 *      golden S = 32 (0x18..0x37), this S = 48 (0x18..0x47).  Only three slots are ever
 *      referenced in either build (two f32 spills at 0x18/0x1C around the func_1505A630
 *      call, and bestIdx), so the extra 16 bytes are homes for compiler-managed temps that
 *      ended up in registers.  bestIdx sits at 0x30 in golden (2nd home from the top) and
 *      0x34 here (5th), i.e. this C creates three extra temps BEFORE bestIdx and one after.
 *      MEASURED NEGATIVE RESULTS -- the frame did NOT move for any of these:
 *        - deleting the `node` local and writing nodes[bestIdx] / nodes[bestIdx+1] inline
 *        - deleting toNext/toPrev and reusing `best` as the scratch
 *        - moving toNext/toPrev between block scope and the top-level declaration list
 *      It DID move (0x48 -> 0x50) when a third pointer local was added, so homes are handed
 *      out per value, but they are not in 1:1 correspondence with declared locals.  Every
 *      sp-relative row in the function differs because of this one number.
 *
 *  (2) LOOP INDUCTION VARIABLE: golden strength-reduces to a single pointer IV
 *      (`addiu a2,a2,0x20`, accesses at 0(a2)/8(a2)/0x10(a2)/0x18(a2)); this keeps base +
 *      byte-offset and emits an extra `addu v0,t3,a2` per unrolled iteration plus `move
 *      t3,t5`, and reloads `lh 0(v0)`/`lh 4(v0)` in the then-branch instead of keeping dx/dz
 *      live.  Cause: the pointer variable's web spans past the loop.
 *      This one IS steerable, but only by trading it against the tail:
 *        - loop base as a variable assigned in the loop, tail reading node[1].x/.z inline
 *          at the call  ->  LOOP IS PERFECT (zero rows), tail worse, total 6173
 *        - same, plus `dx = node[1].x; dz = node[1].z;` before the radius test (which is what
 *          golden's early `lh v1,8(a0)` / `lh a1,0xc(a0)` demand)  ->  loop takes the IV
 *          damage, tail improves, total 5048 -> 4538 with the loop pointer named `node`
 *      i.e. the early next-node loads and the clean IV are mutually exclusive under every
 *      spelling tried.  4538 (this file) is the better of the two.
 *
 * SPELLINGS RULED OUT (each one built and scored):
 *   - `((Waypoint *)D_800D2104[arg1])[i].x` twice in the loop body: unrolls x2 not x4
 *     (`andi v0,t5,0x1`), which is a whole-loop structural miss -- 9037.
 *   - `node = &((Waypoint *)D_800D2104[arg1])[i];` inside the loop -- 10559.
 *   - hoisting `nodes = ...` above the loop: gets the x4 unroll but keeps arg1 in a
 *     callee-saved s0 and loads the base once, where golden re-derives it in BOTH loop
 *     preambles and again in the tail -- 6211.
 *   - separate dedicated loop pointer (4 pointer locals): frame grows to 0x50 -- 4714.
 *   - separate `s32 nx, nz;` instead of reusing dx/dz for the early next-node loads -- 5058.
 *   - nested `if (unk31C) { if (dist > 20.0f) }` vs `&&`: `&&` is very slightly better and
 *     is what is used here.
 *
 * NOTE FOR ANY PERMUTER ATTEMPT: game_83300.c is a KNOWN-BAD TU for the permuter -- its
 * pycparser round trip produces an EMPTY disassembly (the function vanishes).  Do not expect
 * a permuter run to rescue this; it needs either a hand insight into the temp-home count or
 * a permuter fix for this TU.
 *
 * No banned constructs: no dummy labels, no volatile, no self-assignment, no dead locals,
 * no no-op masks.  The uninitialised bestIdx is original-game behaviour, not a forcer.
 *
 * Needs, at the top of game_83300.c:  void func_150611E8(struct127 *arg0, s32 arg1);
 * (line 677 calls it before the definition, so without the prototype cfe rejects the
 * definition as a redeclaration returning int).
 */

/* One node of the per-level path/waypoint list. D_800D2104[path] is the node array,
   (*(u8 **)&D_800D2108)[path] its node count. */
typedef struct {
    /* 0x0 */ s16 x;
    /* 0x2 */ s16 y;
    /* 0x4 */ s16 z;
    /* 0x6 */ u16 radius;
} Waypoint150611E8; /* size 0x8 */

/* struct126 spelled far enough out to reach the field this function writes. */
typedef struct {
    u8  pad0[0x68];
    /* 0x68 */ s16 unk68;
} Struct150611E8;

extern u8 D_800D2108[];
extern f32 D_8009968C;

void func_150611E8(struct127 *arg0, s32 arg1) {
    Waypoint150611E8 *nodes;
    Waypoint150611E8 *node;
    s32 count;
    s32 best;
    s32 bestIdx;
    s32 i;
    s32 dx;
    s32 dz;
    s16 px;
    s16 pz;
    u32 radius;
    f32 dist;
    f32 lerp;
    s32 angle;

    count = (*(u8 **)&D_800D2108)[arg1];
    if (count < 3) {
        return;
    }

    px = arg0->x_position;
    pz = arg0->z_position;
    best = 0x7FFFFFFF;

    for (i = 0; i < count; i++) {
        node = (Waypoint150611E8 *)D_800D2104[arg1];
        dx = px - node[i].x;
        dz = pz - node[i].z;
        if (((dx * dx) + (dz * dz)) < best) {
            best = (dx * dx) + (dz * dz);
            bestIdx = i;
        }
    }

    if ((bestIdx != 0) && (count != bestIdx + 1)) {
        nodes = (Waypoint150611E8 *)D_800D2104[arg1];
        if (best > 28000) {
            s32 toNext;
            s32 toPrev;

            dx = px - nodes[bestIdx + 1].x;
            dz = pz - nodes[bestIdx + 1].z;
            toNext = (dx * dx) + (dz * dz);
            dx = px - nodes[bestIdx - 1].x;
            dz = pz - nodes[bestIdx - 1].z;
            toPrev = (dx * dx) + (dz * dz);
            if (toPrev < toNext) {
                bestIdx--;
            }
        }

        node = &nodes[bestIdx];
        radius = node[1].radius;
        dx = node[1].x;
        dz = node[1].z;
        if (radius == 0) {
            dist = 8.0f;
        } else {
            dist = radius;
        }
        lerp = dist * D_8009968C;
        if (lerp > 1.0f) {
            lerp = 1.0f;
        }
        angle = func_1505A630(dx - node->x, node->z - dz, 0);
        if ((arg0->unk31C != NULL) && (dist > 20.0f)) {
            ((Struct150611E8 *)arg0->unk31C)->unk68 = angle | 1;
        }
        func_150593C4(arg0, angle, dist, lerp);
    }
}
