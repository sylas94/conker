/* tools/nearmiss/func_1515F040.c -- game_18A8F0, 27 instructions, leaf
 * STATUS: mism=35, n=28/27 (ONE OVER).  Cold decompile 2026-08-25.
 * >>> TWIN of tools/nearmiss/func_1515F0AC.c (same TU): identical clamp, except this one
 * >>> reads D_800A6520 and scales by 65536.0f (0x47800000) before the truncate.
 * >>> SOLVE ONE, SHIP BOTH.
 * LEFT (both): one extra `nop` and the order of `c.le.s` vs `lui at,0xc700` -- golden emits
 * the compare first and fills the branch-likely delay slot with the `mtc1`; ours emits the
 * lui first and pays a nop.
 */

extern f32 D_800A6520;
extern s32 D_800DCD10[];

void func_1515F040(f32 arg0, s32 arg1) {
    if (D_800A6520 <= arg0) {
        arg0 = D_800A6520;
    } else if (arg0 < -32768.0f) {
        arg0 = -32768.0f;
    }
    D_800DCD10[arg1] = arg0 * 65536.0f;
}
