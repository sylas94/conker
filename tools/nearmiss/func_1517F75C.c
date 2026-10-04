/* tools/nearmiss/func_1517F75C.c -- game_1AC2F0, 22 instructions, leaf
 * STATUS: mism=32, n=23/22 (ONE OVER).  Cold decompile 2026-08-25.
 * Counts down every s16 in D_800DDE10[0 .. D_80082FA0] by the frame delta D_800BE9E4,
 * clamping at 0.  Note the loop runs while `p <= end` (`sltu at,a1,a0` + `beql`), so the
 * bound is INCLUSIVE -- D_80082FA0 is the last index, not the count.
 * LEFT: we materialise &D_800DDE10 into $a2 and then COPY it to $v0 for the walking pointer;
 * golden keeps one register ($a0) and walks it directly.  That copy is the extra word.
 * Deriving `end` from `p` instead of from the array symbol (LAW E) does not remove it, and
 * neither does s16 vs u16 on the pointer -- both still 32.
 */

extern s32 D_80082FA0;
extern s32 D_800BE9E4;

void func_1517F75C(void) {
    s16 *p;
    s16 *end;
    s32 dt;
    s32 v;

    p = D_800DDE10;
    if (D_80082FA0 >= 0) {
        end = &p[D_80082FA0];
        dt = D_800BE9E4;
        do {
            v = *p;
            if (dt < v) {
                *p = v - dt;
            } else {
                *p = 0;
            }
            p++;
        } while (p <= end);
    }
}
