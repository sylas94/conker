/* Near-miss park for func_15036570 (game_63A20.c), best score 7140 (asm-differ -R --max-lines 4096).
 *
 * STATUS: whole-TU file. Drop this over conker/src/game_63A20.c to reproduce the 7140 base.
 *
 * WHAT IS ALREADY SOLVED (do not re-derive):
 *   - Frame size 0x60 and EVERY stack slot match exactly:
 *       x=0x5C y=0x58 z=0x54 nx=0x50 ny=0x4C nz=0x48 obj=0x44 (spill) t=0x30,
 *       incoming args at 0x60/0x64/0x68, ra at 0x24, outgoing args 0x10/0x14/0x18.
 *     This is pinned by the LOCAL DECLARATION LIST: exactly 12 locals, in this order,
 *     with `t` LAST. IDO assigns local slots descending from the frame top in
 *     declaration order; 15 locals gave frame 0x70, 12 give 0x60. DO NOT add or
 *     remove a local without re-checking every sp offset.
 *   - All control flow, all branch targets, all float constants, both call sites,
 *     both struct layouts and every memory operand match.
 *
 * WHAT IS LEFT (this is the permuter's job):
 *   1. Temp-register rotation is off by one position from the very first expression:
 *        golden  &D_800CC2D0 -> $t9, index math -> $t8, rec->unk2D0 -> $t1, idx*4 -> $t7
 *        ours    &D_800CC2D0 -> $t8, index math -> $t7, rec->unk2D0 -> $t9, idx*4 -> $t1
 *      i.e. ours is the same cyclic sequence {t7,t8,t9,t1} started one step earlier.
 *   2. One INSERTED instruction at 0x64: `move $a3,$v1`. Golden keeps `m` in $v1 for the
 *      whole compare chain and puts the multi-use constant 0x138 in $a0; ours puts 0x138
 *      in $v1 and copies `m` out to $a3.
 *   3. Ours is 5 instructions SHORT (0x340 vs golden 0x354). Ours performs a
 *      partial-redundancy elimination golden does not: the `(s16)x` truncation computed
 *      in each branch is kept live in $v1 across the join and reused for `obj->unk0 = x`,
 *      where golden re-loads `lwc1 $f8,0x5c(sp)` and re-truncs in the tail block.
 *      The same effect makes our then-branch hoist all three `lwc1` loads to the top of
 *      the block, where golden interleaves load/trunc/store per component.
 *
 * SPELLINGS RULED OUT BY MEASUREMENT (do not repeat):
 *   - Permuting the four register-only locals (rec/v/m/h) across declaration indices
 *     7..10: score UNCHANGED at exactly 7140. Declaration order among non-memory
 *     locals has no effect here.
 *   - Explicit f32 temporaries a/b/c holding v->x,v->y,v->z before the lerp
 *     (15 locals): frame grows to 0x70, score 8367. Strictly worse.
 *   - Duplicating the three `obj->unkN = ...` tail stores into BOTH branches, hoping
 *     IDO would tail-merge them: it does NOT merge. Score 6741 but the function grows
 *     to 0x36C (longer than golden) and the tail is emitted twice. Structurally worse
 *     than the shared tail below even though the number is lower.
 *
 * POOL: the 0.7f literal is IDO's own .rodata pool; golden calls it D_80097D80.
 * Block asm/data/23C840.rodata.s, ONE glabel, remaining 12 bytes are zero padding,
 * and func_15036570 is its ONLY referencing function -> clean to migrate.
 * Do NOT replace 0.7f with `extern f32 D_80097D80;`.
 */

#include <ultra64.h>
#include "functions.h"
#include "variables.h"

typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ u8  pad6[0x1A];
    /* 0x20 */ s16 unk20;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ s16 unk24;
    /* 0x26 */ u8  pad26[0xA];
    /* 0x30 */ s16 unk30;
    /* 0x32 */ s16 unk32;
    /* 0x34 */ s16 unk34;
} Struct63A20;

typedef struct {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
    /* 0x04 */ s16 z;
} Vec3s63A20;

extern void func_150A7960(f32 *, f32, f32, f32, f32 *, f32 *, f32 *);

void func_15036570(s32 idx, f32 *mtxA, f32 *mtxB) {
    f32 x;
    f32 y;
    f32 z;
    f32 nx;
    f32 ny;
    f32 nz;
    Struct63A20 *obj;
    struct127 *rec;
    Vec3s63A20 *v;
    u16 m;
    f32 h;
    f32 t;

    rec = &D_800CC2D0[idx];
    m = rec->unk84.uh;
    h = rec->unk2D0->unk8;
    obj = (Struct63A20 *)(&D_800C3FC0)[idx];

    if ((m == 0x3E) || (m == 0x41) || ((m == 0x138) && (36.0f <= h)) ||
        (((m == 0x3D) || (m == 0xD9)) && (21.0f < h))) {
        func_150A7960(mtxA, -7.0f, -17.0f, -7.0f, &x, &y, &z);
        v = &((Vec3s63A20 *)&D_800C3FC4)[idx];
        v->x = x;
        v->y = y;
        v->z = z;
    } else {
        if ((((m == 0x3D) || (m == 0xD9)) && (7.0f < h)) || (m == 0x138) || (m == 0x139)) {
            t = 1.0f;
        } else {
            t = 0.7f;
        }
        x = (obj->unk30 + obj->unk20) * 0.5f;
        y = (obj->unk32 + obj->unk22) * 0.5f;
        z = (obj->unk34 + obj->unk24) * 0.5f;
        func_150A7960(mtxB, x, y, z, &nx, &ny, &nz);
        v = &((Vec3s63A20 *)&D_800C3FC4)[idx];
        v->x = v->x + ((nx - v->x) * t);
        v->y = v->y + ((ny - v->y) * t);
        v->z = v->z + ((nz - v->z) * t);
        x = v->x;
        y = v->y;
        z = v->z;
    }

    obj->unk0 = x;
    obj->unk2 = y;
    obj->unk4 = z;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_63A20/func_150368C4.s")
