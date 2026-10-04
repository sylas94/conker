/* tools/nearmiss/func_1502EE8C.c -- game_58F80, 26 instructions, leaf
 * STATUS: mism=8, n=26/26 (EXACT LENGTH).  Cold decompile 2026-08-25.
 * The nine-instruction shift/add chain at the top is a multiply by 812 == 0x32C, the actor
 * record stride, so the load is D_800CC2D0[arg0].unk6A[arg1] (D_800CC33A == D_800CC2D0+0x6A).
 * LADDER: 20 (n=25) with three `return` statements -> 8 (n=26) with a single result variable
 * and one exit.  This is LAW F run backwards: golden assigns a shared `$v1` in each branch
 * delay slot and falls into one `or $v0,$v1,zero`, so the source has ONE return, not three.
 * LEFT: 8 rows of branch POLARITY.  Golden branches TO the `r = v - 2` block and falls
 * through to `r = 2`; ours does the opposite.  Explicit nesting is identical (8), seeding
 * `r = 2` first is worse (10), a ternary chain is worse and one word long (20, n=27).
 */

typedef struct Act1502EE8C {
    char pad0[0x6A];
    /* 0x6A */ u8 unk6A[2];
    char pad6C[0x32C - 0x6C];
} Act1502EE8C;

s32 func_1502EE8C(s32 arg0, s32 arg1) {
    u8 v;
    s32 r;

    v = ((Act1502EE8C *)D_800CC2D0)[arg0].unk6A[arg1];
    if (v < 2) {
        r = v;
    } else if (v < 4) {
        r = v - 2;
    } else {
        r = 2;
    }
    return r;
}
