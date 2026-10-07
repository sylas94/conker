/* game_AE1D0 / func_15080D20 -- NEAR-MISS 155 (fastscore, n=219/219 exact length), first attempt 2026-10-06.
 * Last pragma in game_AE1D0. Melee hit test (attacker point vs target bone hit spheres).
 * TO SCORE: this body must sit AFTER HitSphere/ModelBounds in the TU (move those typedefs above the
 * pragma when shipping -- function order is fixed); change the TU prototype to
 * (struct127 *, struct127 *, s32, f32, f32, s32) and cast the caller's arg0 to (struct127 *).
 *
 * SOLVED: `type` is s32 (golden never andi's it); the projected point must be an ARRAY `f32 pos[3]` --
 * a struct17 local gets scalarised into f20-f30 and the whole function diverges (332 -> 155).
 * SLOT LAYOUT (relative to frame top, -g3): 9 scalar locals above pos (pos at frame-0x30), 4 scalars,
 * then the two struct17 out-vectors (local frame-0x4C, out frame-0x58). This version already has that
 * relative layout; golden's frame is 8 bytes bigger only because it spills one more temp (0x60..0x77).
 *
 * OPEN: golden rotates FROM THE OLD COORDINATES (loads pos[2] into f4 and pos[0] into f6 once, then
 * new pos[0] = z*s + x*c and new pos[2] = z*c + (-x)*s, with the z*s product emitted first). This body
 * uses the NEW pos[0] in the pos[2] line -- semantically different from golden. Adding `f32 x, z`
 * temporaries fixes that but gives 11 scalars above pos (frame right, offsets 8 low): two of the
 * current nine (bounds/s/c/angle/bound/height/dx/dy/dz) are not named locals in the original. */

extern f32 D_8009CBD8;
extern f32 D_8009CBDC;
void func_1505D1C4(f32, f32, f32, s32, s32, s32, s32, s32);

/* Melee test: project a point `reach` ahead of `attacker` along its pitch (unkB8) and yaw (unk40),
 * reject against `target`'s whole-model bounding sphere, then test each bone hit sphere of table
 * `type` with the attack radius.  On a hit (and unless the target is immune) reports it through
 * func_1505D1C4 and returns the bone index + 1; 0 for a miss. */
s32 func_15080D20(struct127 *attacker, struct127 *target, s32 type, f32 reach, f32 radius, s32 arg5) {
    ModelBounds *bounds;
    f32 s;
    f32 c;
    f32 angle;
    f32 bound;
    f32 height;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 pos[3];
    HitSphere *p;
    s32 count;
    s32 i;
    u8 *mtx;
    struct17 local;
    struct17 centre;

    reach *= attacker->xz_scale;
    radius *= attacker->xz_scale;
    angle = attacker->unkB8 * D_8009CBD8;
    s = sinf(angle);
    c = cosf(angle);
    pos[0] = 0.0f;
    pos[1] = -reach * s;
    pos[2] = reach * c;
    angle = attacker->unk40 * D_8009CBDC;
    s = sinf(angle);
    c = cosf(angle);
    pos[0] = pos[2] * s + pos[0] * c;
    pos[2] = pos[2] * c + -pos[0] * s;
    pos[0] += attacker->x_position;
    pos[1] += attacker->y_position;
    pos[2] += attacker->z_position;

    bounds = (ModelBounds *)D_800D1C90[target->id];
    bound = bounds->body_radius * target->xz_scale;
    height = bounds->body_height * target->y_scale;
    dx = pos[0] - target->x_position;
    dy = pos[1] - (target->y_position + height);
    dz = pos[2] - target->z_position;
    if (bound * bound < dx * dx + dy * dy + dz * dz) {
        return 0;
    }

    count = D_8009CBCC[type];
    p = D_80086C60[type];
    mtx = (u8 *)target->unk1D4;
    for (i = 0; i < count; i++, p++) {
        local.unk0 = p->x;
        local.unk4 = p->y;
        local.unk8 = p->z;
        func_15143134(&local, &centre, (s32)mtx + (p->bone << 6));
        dx = pos[0] - centre.unk0;
        dy = pos[1] - centre.unk4;
        dz = pos[2] - centre.unk8;
        bound = p->radius * target->xz_scale + radius;
        if (!(bound * bound < dx * dx + dy * dy + dz * dz)) {
            if (target->immune == 0) {
                func_1505D1C4(target->x_position, target->y_position, target->z_position, arg5,
                              attacker - D_800CC2D0, 0, 0, 0);
            }
            return p->bone + 1;
        }
    }
    return 0;
}
