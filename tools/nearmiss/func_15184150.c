/* func_15184150 near-miss, score 70 (whole-object isolated diff, -o -s).
 * Everything matches byte-for-byte through instruction 108/134 (offset 0x1B0).
 * Residual: 10 lines, ALL pure FP-register naming, in the two tail multiplies.
 *   target: lwc1 $f8,0x14c ; mtc1 $f6 ; cvt.s.w $f0,$f6 ; mul.s $f2,$f8,$f0
 *   ours:   lwc1 $f10,0x14c; mtc1 $f6 ; cvt.s.w $f8,$f6 ; mul.s $f0,$f8,$f10
 * i.e. the target materializes each int->float conversion into the $f0 scratch
 * and makes the memory-loaded scale the mul's `fs`; IDO from any source form
 * tried materializes the conversion into a stacked temp instead.
 * decomp-permuter candidate.
 *
 * Needs at top of game_1B1600.c:
 *   extern u8 D_800C3E90;
 *   extern s32 func_1502DB20(s32);
 */

s32 func_15184150(s32 arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    s32 id;
    s32 count;
    s32 i;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 (*bones)[4][4];

    id = D_800CC2D0[arg0].id;
    *arg3 = 0.0f;
    *arg2 = 0.0f;
    *arg1 = 0.0f;

    if ((D_800CC2D0[arg0].unk1D4 == 0) || (D_800C3E90 != 0)) {
        return 0;
    }

    count = func_1502DB20(id);
    for (i = 0; i < count; i++) {
        bones = (f32 (*)[4][4])D_800CC2D0[arg0].unk1D4;
        dx = bones[i][3][0];
        dy = bones[i][3][1];
        dz = bones[i][3][2];
        dx -= D_800CC2D0[arg0].x_position;
        dy -= D_800CC2D0[arg0].y_position;
        dz -= D_800CC2D0[arg0].z_position;
        if (dx < 0.0f) {
            dx = -dx;
        }
        if (*arg1 < dx) {
            *arg1 = dx;
        }
        if (dy < 0.0f) {
            dy = -dy;
        }
        if (*arg2 < dy) {
            *arg2 = dy;
        }
        if (dz < 0.0f) {
            dz = -dz;
        }
        if (*arg3 < dz) {
            *arg3 = dz;
        }
    }

    if ((*arg1 == 0.0f) || (*arg2 == 0.0f) || (*arg3 == 0.0f)) {
        *arg1 = *arg3 = D_800CC2D0[arg0].xz_scale * D_800D1C90[D_800CC2D0[arg0].id]->unk1A;
        *arg2 = D_800CC2D0[arg0].y_scale *
                (D_800D1C90[D_800CC2D0[arg0].id]->unk1C + D_800D1C90[D_800CC2D0[arg0].id]->unk1E);
    }
}
