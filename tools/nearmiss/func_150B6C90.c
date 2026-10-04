/* tools/nearmiss/func_150B6C90.c -- game_E4070, 41 instructions, frame -0x28
 *
 * STATUS: mism=26, n=42/41 (ONE OVER).  Was 220/n=61 -- fixed by LAW A + LAW E.
 *
 * The zero block is ONE loop, not two scalars plus a record loop:
 *      for (i = 0; i < 10; i++) D_800D9898[i] = 0;
 * 10 % 4 == 2, so IDO peels 2 (absolute, sharing $at) and unrolls 4 across 2 iterations.
 * Reading it as "two scalar stores + a struct loop" cost 20 words and forced a base register;
 * the unroller path produces the `$at` + addend form for free.  <-- this also RESOLVES the
 * "$at + addend" blocker that this file used to share with func_151E81EC: the form comes
 * from the unroller, not from any aggregate spelling.
 *
 * LAW E (new, see NOTES_ido_loop_laws.md): a loop bound written as a DIFFERENT SYMBOL makes
 * IDO compute the trip count at runtime (subu/divu) and unroll with a remainder.  Written as
 * `&base[N]` off the SAME symbol it emits a plain loop.  Worth 20 words here.
 *
 * ------------------------------------------------------------------ WHAT IS LEFT: 1 word
 * Golden emits the two peeled stores ADJACENT (`sw zero,%lo(D_800D9898)(at)` /
 * `sw zero,%lo(D_800D989C)(at)`) so they share one `lui $at`.  Ours separates them and pays
 * a second `lui $at` -- the same adjacency rule as func_151DD970.  Moving `D_800D9890 = 3;`
 * after the loop (29) or before the call (42) both make it worse; s5 order is best.
 */

extern struct Obj151A4FD0 *func_151A4FD0(s32, s32, s32, s32, s32, s32, u8, s32);
extern s32  *D_800D9894;
extern s32  *D_800D9898[];

void func_150B6C90(void) {
    s32 i;

    if (D_800D9894 != 0) {
        func_1516972C((struct102 *)D_800D9894);
    }
    D_800D9894 = (s32 *)func_151A4FD0(0, 0, 0xFF, 0, 0, D_800BE9E8, 0, 0);
    D_800D9890 = 3;
    for (i = 0; i < 10; i++) {
        D_800D9898[i] = 0;
    }
}
