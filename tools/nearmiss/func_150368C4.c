// NEAR-MISS, best score 2505 (asm-differ -R --max-lines 4096, IDO 5.3 -O2 -g3 -mips2).
// PERMUTER CANDIDATE. Whole-TU file: drop this in as conker/src/game_63A20.c to reproduce.
//
// Everything matches structurally end to end -- frame 0x80, every stack slot (0x38 temp,
// 0x3c t0 spill, 0x78 sub, 0x84/0x88 arg homes), all four early returns, the four-arm
// geometry-mode chain, both func_15036570/func_1515E544/func_15094F70 call sequences and
// the entire six-command display list are instruction-for-instruction identical.
//
// The ONLY residual is inside the 15 vertex-colour stores, and it is one IDO uopt decision
// I could not reach from source. Golden emits, mid-block:
//     li    a0, 1
//     sll   v0, a0, 0x4          # v0 = 16 = &vtx[1] - &vtx[0]
//     addiu v1, v1, 0x300        # rebase the colour-source pointer
// and then addresses vertices 1..4 as `addu tX, <vtx>, v0` + displacement 0xc/0x1c/0x2c/0x3c
// and the colour bytes as 0xc/0xd/0xe(v1).  My build folds both: `sb tX, 0x1c(<vtx>)` and
// `lbu tX, 0x30c(v1)`.  Net: golden has 8 instructions I do not (1 li, 1 sll, 5 addu,
// 1 addiu), and that shifts the temp-register rotation for the whole rest of the function,
// which is what the remaining ~45 'r' rows are -- they are a cascade, not independent misses.
//
// Spellings tried, ALL producing byte-identical output (score stayed exactly 2505/3408):
//   * literal indices  ((Vtx *)(&D_800C3FC0)[idx])[1..4]        (this file)
//   * local `s32 n = 1;` assigned immediately before the block, indices [n], [n+1]...
//   * same local assigned in the ENTRY basic block (before all four early returns)
//   * explicit pointer form ((Vtx *)(&D_800C3FC0)[idx] + 1)[0..3]
// IDO's constant propagation folds `1 * sizeof(Vtx)` in every case, so the `li 1; sll 4`
// pair cannot be produced by a constant index; the golden index must survive const-prop for
// a reason with no source handle at -O2 -g3.  The 0x300 rebase is the same uopt pass and
// almost certainly the same decision (both live in that one basic block).
//
// Notes on types (structs.h is wrong here, so the shapes are respelled file-locally):
//   * struct127 0x66 is `pad66`, and 0x301..0x317 is one `u8 unk301[0x17]` blob; the real
//     shape is u8 0x301, u8 0x302, s32 0x304[4], ptr 0x314 (8-byte elements), ptr 0x31C.
//   * struct126 0x28 is a single `s32`; it is really a 2-entry array indexed by D_800BE9C0.
//   * D_800C3FC0 is declared `struct222 *` but is used as an array of pointers, so it is
//     spelled `(&D_800C3FC0)[idx]` exactly as game_32200.c already does.
//   * func_15094F70 is `void` in game_C1D70.c but its tail call leaves the new Gfx* in $v0
//     and this caller consumes it, so it is declared returning Gfx * here.
// No .rodata migration is needed: this function has no float constants at all.
#include <ultra64.h>
#include "functions.h"
#include "variables.h"

/* structs.h describes 0x66 and the 0x300 block of struct127 as padding, and struct126's
   0x28 slot as a single word; both are wrong for this file, so the shapes are respelled
   locally. */
typedef struct {
    u8  pad0[0x66];
    u8  unk66;
    u8  pad67[0x16D];
    u8  *unk1D4;
    u8  pad1D8[0x129];
    u8  unk301;
    u8  unk302;
    u8  pad303;
    s32 unk304[4];
    struct222 *unk314;
    u8  pad318[4];
    struct126 *unk31C;
    u8  pad320[0xC];
} Obj63A20;

typedef struct {
    u8  pad0[4];
    u8  unk4;
    u8  pad5[0x23];
    u8  *unk28[2];
} Sub63A20;

extern Gfx D_80084350[];
extern u8 D_800903BC;
extern Mtx D_80089470;

extern void func_15036570(s32, void *, void *);
extern Gfx *func_1515E544(Gfx *, s32, u8, u8, void *);
extern Gfx *func_15094F70(Gfx *, void *, s32, void *, s32, s32, s32, s32, s32);

#pragma GLOBAL_ASM("asm/nonmatchings/game_63A20/func_15036570.s")

Gfx *func_150368C4(Gfx *gfx, s32 idx, s32 arg2) {
    Obj63A20 *obj;
    Sub63A20 *sub;
    u8 *col;
    u8 *p;

    obj = &((Obj63A20 *)D_800CC2D0)[idx];
    if ((obj->unk31C->unk75 != 2) && (obj->unk31C->unk75 != 0x13)) {
        return gfx;
    }
    sub = (Sub63A20 *)func_1503195C((struct127 *)obj, 8, 0);
    if (sub == NULL) {
        return gfx;
    }
    if (idx > 0) {
        return gfx;
    }

    col = sub->unk28[D_800BE9C0];
    ((Vtx *)(&D_800C3FC0)[idx])[0].v.cn[0] = col[0x30C];
    ((Vtx *)(&D_800C3FC0)[idx])[0].v.cn[1] = col[0x30D];
    ((Vtx *)(&D_800C3FC0)[idx])[0].v.cn[2] = col[0x30E];
    ((Vtx *)(&D_800C3FC0)[idx])[1].v.cn[0] = col[0x30C];
    ((Vtx *)(&D_800C3FC0)[idx])[1].v.cn[1] = col[0x30D];
    ((Vtx *)(&D_800C3FC0)[idx])[1].v.cn[2] = col[0x30E];
    ((Vtx *)(&D_800C3FC0)[idx])[2].v.cn[0] = col[0x30C];
    ((Vtx *)(&D_800C3FC0)[idx])[2].v.cn[1] = col[0x30D];
    ((Vtx *)(&D_800C3FC0)[idx])[2].v.cn[2] = col[0x30E];
    ((Vtx *)(&D_800C3FC0)[idx])[3].v.cn[0] = col[0x30C];
    ((Vtx *)(&D_800C3FC0)[idx])[3].v.cn[1] = col[0x30D];
    ((Vtx *)(&D_800C3FC0)[idx])[3].v.cn[2] = col[0x30E];
    ((Vtx *)(&D_800C3FC0)[idx])[4].v.cn[0] = col[0x30C];
    ((Vtx *)(&D_800C3FC0)[idx])[4].v.cn[1] = col[0x30D];
    ((Vtx *)(&D_800C3FC0)[idx])[4].v.cn[2] = col[0x30E];

    p = obj->unk1D4;
    if (p == NULL) {
        return gfx;
    }
    func_15036570(idx, p + 0x240, p + 0x100);

    gSPDisplayList(gfx++, D_80084350);
    gfx = func_1515E544(gfx, obj->unk304[arg2], obj->unk301, obj->unk302,
                        obj->unk314 + D_800BE9C0);

    if ((obj->unk66 & 0xC) == 0xC) {
        gSPClearGeometryMode(gfx++, G_LIGHTING);
    } else if (((obj->unk66 & 0xC) != 8) && ((sub->unk4 & 1) == 0)) {
        gSPClearGeometryMode(gfx++, G_LIGHTING);
    } else if (D_800DCD7C != 0) {
        gSPSetGeometryMode(gfx++, G_LIGHTING);
    } else {
        gSPClearGeometryMode(gfx++, G_LIGHTING);
    }

    gfx = func_15094F70(gfx, &D_800903BC, 0, NULL, 0, 0, 0, 2, 3);
    gSPMatrix(gfx++, &D_80089470, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPVertex(gfx++, (Vtx *)(&D_800C3FC0)[idx], 1, 0);
    gSPMatrix(gfx++, (Mtx *)(p + 0x100), G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPVertex(gfx++, &((Vtx *)(&D_800C3FC0)[idx])[1], 4, 1);
    gSP1Triangle(gfx++, 0, 1, 2, 0);
    gSP1Triangle(gfx++, 0, 3, 4, 0);
    return gfx;
}
