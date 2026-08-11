// NEAR-MISS, best score 6300 (asm-differ -R --max-lines 4096, IDO 5.3 -O2 -g3 -mips2).
// PERMUTER CANDIDATE.  TU: conker/src/game_B3020.c -- paste this in place of
//   #pragma GLOBAL_ASM("asm/nonmatchings/game_B3020/func_1508C5B8.s")
// (needs `extern f32 D_8009DA68;` and `extern void func_1508C1A4(s32, s32);` alongside it;
// D_800D23B0 / D_800CC2D0 / D_8008FD8C / D_8008FD90 / D_800D18A0 are already in scope there).
//
// WHAT MATCHES: frame 0xc0; every saved-register slot; the whole declared-local layout
// (owners at 0x7c, dist[4] at 0x80-0x8f, who[4] at 0x90-0x93 -- this pins the declaration
// order: 10 word scalars + 3 byte scalars = 44 bytes ABOVE who[], then who, then dist,
// then owners, since IDO lays locals out top-down from sp+0xc0); both halves' control flow;
// the strength-reduced init loop, the insertion-sort loop, the who[] scan loop, the whole
// second-half wrap/mask/retry loop and the epilogue.  Golden is only 3 instructions longer.
//
// ORIGINAL-GAME BUG, reproduced deliberately -- do NOT "fix" it:
// golden does `mov.s $f14,$f12` + `mov.s $f16,$f12` right after `lwc1 $f12,0x14($fp)`, so all
// three of x/y/z are D_800CC2D0[i].x_position.  dx therefore evaluates to 0.0 and dz to
// (x - z) of the SAME object -- there is no load from object j anywhere in the inner loop.
// The "3 nearest" search degenerates into "first 3 candidates that pass the filters".  Three
// separate f32 locals initialised from one expression is the only thing that produces one
// lwc1 + two mov.s.
//
// RESIDUAL (all of it; nothing else diverges structurally):
//  1. IV-init folding, ~6 instructions.  Golden sets up the insertion loop as
//        li    a1,2 / sll t6,a1,0x2 / addiu t7,sp,0x80 / addiu t8,sp,0x90
//        addu  v0,a1,t8      (= &who[2])
//        addu  v1,t6,t7      (= &dist[2])
//     i.e. it keeps the initial index 2 in a REGISTER and scales it, while my build folds
//     both to `addiu v0,sp,0x88` / `addiu s0,sp,0x92`.  Tried: `k = 2;` inside the guard
//     (this file), `k = 2;` hoisted above `if (d < dist[2])` (score 6375, worse), a
//     `for`-shaped loop, and `dist[k]`-vs-`dist[2]` in the guard.  IDO folds every time.
//     NOTE: func_150368C4 in game_63A20 shows the IDENTICAL artefact (`li a0,1; sll v0,a0,4`
//     for &vtx[1]); whatever source-level lever produces a non-folded small constant index
//     would close BOTH functions.
//  2. Which derived pointer carries the loop test.  Golden tests the who[] pointer
//     (`s1 = sp+0x90`, `addiu v0,v0,-1`, `sltu at,v0,s1`); mine tests the dist[] pointer
//     (`s1 = sp+0x80`, `addiu v0,v0,-4`).  Statement order inside the loop body flips the
//     INIT loop's choice (that is why `who[k] = -1;` precedes `dist[k] = ...` here -- worth
//     300 points) but not the insertion loop's.
//  3. D_8009DA68 (= 900000000.0f, a real shared global in asm/data/2424E0.rodata.s with many
//     glabels, NOT a compiler literal pool -- no rodata migration needed).  Golden hoists the
//     load into callee-saved $f22 outside the whole outer loop; my build reloads it per outer
//     iteration into $f0 and spends $f22 on `x` instead.  2 instructions.
//  4. Two extra `mov.s` in mine ($f14 for dx, $f12 for d); golden keeps both in $f2.
//  5. `move a0,v1` placement for `j = D_8008FD90` (sunk into the guarded block in golden).
//  6. i2/i3 land in the opposite saved registers (golden i3->s3, i2->s2; mine i3->s2).
//     Tried both declaration orders and both assignment orders; score stays exactly 6300,
//     so this is a pure allocation tie with no source handle.
// Everything after the first divergence is a temp-register rotation cascade off items 1-3.
#pragma GLOBAL_ASM("asm/nonmatchings/game_B3020/func_1508C1A4.s")

extern f32 D_8009DA68;
extern void func_1508C1A4(s32, s32);

s32 func_1508C5B8(s32 arg0, s32 arg1) {
    s32 i;
    s32 j;
    s32 k;
    s32 n;
    u8 i2;
    u8 i3;
    u8 kind;
    f32 x;
    f32 y;
    f32 z;
    f32 dx;
    f32 dz;
    f32 d;
    s8 who[4];
    f32 dist[4];
    s32 *owners;

    i3 = ((u8 *)D_800D23B0)[0x1700];
    i2 = ((u8 *)D_800D23B0)[0x1701];
    owners = (s32 *)(D_800D23B0 + 0xE64);

    if (arg1 != 0) {
        for (i = 0; i < D_8008FD90; i++) {
            x = D_800CC2D0[i].x_position;
            y = D_800CC2D0[i].x_position;
            z = D_800CC2D0[i].x_position;
            for (k = 0; k < 3; k++) {
                who[k] = -1;
                dist[k] = D_8009DA68;
            }
            for (j = D_8008FD90; j < D_8008FD8C; j++) {
                if (owners[i] == owners[j]) {
                    continue;
                }
                if ((((s32 *)(D_800D23B0 + 0x16C0))[i] & (0x10001 << j)) != 0) {
                    continue;
                }
                dx = y - x;
                dz = z - D_800CC2D0[i].z_position;
                if (i == ((s32 *)(D_800D23B0 + 0x11C))[j]) {
                    dx = dx * 0.5f;
                    dz = dz * 0.5f;
                }
                d = (dx * dx) + (dz * dz);
                if (d < dist[2]) {
                    k = 2;
                    do {
                        who[k + 1] = who[k];
                        dist[k + 1] = dist[k];
                        who[k] = j;
                        dist[k] = d;
                        k--;
                    } while ((k >= 0) && (d < dist[k]));
                }
            }
            for (k = 0; k < 3; k++) {
                if (who[k] != -1) {
                    ((s32 *)(D_800D23B0 + 0x16C0))[i] &= ~(0x10001 << who[k]);
                    ((s32 *)(D_800D23B0 + 0x16C0))[who[k]] &= ~(0x10001 << i);
                    func_1508C1A4(i, who[k]);
                }
            }
        }
    }

    while (arg1 != 0) {
        kind = *(u8 *)&D_800CC2D0[i3].pad128;
        n = 0;
        do {
            i2++;
            if (i2 >= D_8008FD8C) {
                i3++;
                if (i3 >= D_8008FD8C - 1) {
                    i3 = 0;
                }
                i2 = i3 + 1;
                kind = *(u8 *)&D_800CC2D0[i3].pad128;
            }
            ((s32 *)(D_800D23B0 + 0x16C0))[i3] &= ~(0x10001 << i2);
            ((s32 *)(D_800D23B0 + 0x16C0))[i2] &= ~(0x10001 << i3);
            n++;
        } while ((n < 0x40) &&
                 ((D_800D18A0 & ((1 << i3) | (1 << i2))) != 0 ||
                  (kind == *(u8 *)&D_800CC2D0[i2].pad128)));
        func_1508C1A4(i3, i2);
        arg1--;
    }

    ((u8 *)D_800D23B0)[0x1700] = i3;
    ((u8 *)D_800D23B0)[0x1701] = i2;
    return ((s32 *)(D_800D23B0 + 0x16C0))[arg0];
}
