/* tools/nearmiss/func_1515F0AC.c -- game_18A8F0, 24 instructions, leaf
 * STATUS: mism=32, n=25/24 (ONE OVER).  Cold decompile 2026-08-25.
 * Clamps a float to [-32768.0f (0xC7000000), D_800A6524] and stores it as an s32 into
 * D_800DCD10[arg1].
 * LEFT: one extra `nop` and the order of `c.le.s` vs `lui at,0xc700`.  Golden emits the
 * compare FIRST and fills the branch-likely delay slot with the `mtc1`; ours emits the lui
 * first and pays a nop.  An inverted if/else nesting scores the same (31 vs 32) so the
 * clamp's shape is not the lever -- it is delay-slot fill on the branch-likely pair.
 */

extern f32 D_800A6524;
extern s32 D_800DCD10[];

void func_1515F0AC(f32 arg0, s32 arg1) {
    if (D_800A6524 <= arg0) {
        arg0 = D_800A6524;
    } else if (arg0 < -32768.0f) {
        arg0 = -32768.0f;
    }
    D_800DCD10[arg1] = arg0;
}
