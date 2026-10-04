/* tools/nearmiss/func_1514672C.c -- game_16EE20, 30 instructions, leaf
 * STATUS: mism=3, n=30/30.  Cold decompile 2026-08-25.  Axis-aligned bounds test.
 * LADDER: 84 (n=36) with four separate `return 0;` statements -- each one grows its own
 * epilogue.  Golden branches all four failures to ONE shared `return 0`, which is what a
 * single `if (a || b || c || d) return 0;` produces: 84 -> 3, and the length becomes exact.
 * Worth remembering: repeated early returns in a guard chain are almost always ONE `||`.
 * LEFT: 3 rows -- golden loads D_800A56C4 before arg0[0], we load arg0[0] first.  Reversing
 * every comparison (`fabsf(x) > lim`) is identical at 3; hoisting arg0[1] into a local is
 * much worse (38).
 */

extern f32 D_800A56C4;
extern f32 D_800A56C8;

s32 func_1514672C(f32 *arg0) {
    f32 lim;

    lim = D_800A56C4;
    if ((lim < fabsf(arg0[0])) || (lim < fabsf(arg0[2])) || (lim < arg0[1]) ||
        (arg0[1] < D_800A56C8)) {
        return 0;
    }
    return 1;
}
