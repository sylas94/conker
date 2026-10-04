/* tools/nearmiss/func_150FB188.c -- game_126F60, 24 instructions, frame -0x30
 * STATUS: mism=11, n=24/24 (EXACT LENGTH).  Cold decompile 2026-08-25.
 * Zeroes three object fields (-95.0f / -80.0f are 0xC2BE0000 / 0xC2A00000), builds a 5-float
 * stack vector, and tail-calls func_15157DEC(arg0, sp1C).
 * LADDER: 17 with D_800A1DC0 referenced twice -> 11 hoisting it into a local `v`.
 * LEFT: golden materialises the D_800A1DC0 load FIRST and puts 0.0f in $f0 with the global in
 * $f2; ours creates 0.0f first and takes $f2 for it.  FP LAW C again -- one more local, or a
 * different declaration order, should rotate it.
 */

typedef struct Obj150FB188 {
    char pad0[0x54];
    /* 0x54 */ f32 unk54;
    /* 0x58 */ f32 unk58;
    /* 0x5C */ f32 unk5C;
} Obj150FB188;

extern f32 D_800A1DC0;
extern void func_15157DEC(Obj150FB188 *, f32 *);

s32 func_150FB188(Obj150FB188 *arg0) {
    f32 sp1C[5];
    f32 v;

    v = D_800A1DC0;
    arg0->unk5C = 0.0f;
    arg0->unk54 = -95.0f;
    arg0->unk58 = -80.0f;
    sp1C[0] = 0.0f;
    sp1C[1] = 0.0f;
    sp1C[2] = 0.0f;
    sp1C[3] = v;
    sp1C[4] = v;
    func_15157DEC(arg0, sp1C);
    return 1;
}
