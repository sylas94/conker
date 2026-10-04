/* tools/nearmiss/func_1515B994.c -- game_188440, 31 instructions, leaf
 * STATUS: mism=21, n=31/31 (EXACT LENGTH).  Cold decompile 2026-08-25.
 * A velocity/position integrator: unk14 += (unk78 + 0.5*unk74)*dt, unk78 += unk74*dt, then
 * unk1C = unk7C + unk80*(new unk78 + old unk78)*0.5.
 * D_800BE9A4 is loaded TWICE through a base register in golden -- the store to unk14 sits
 * between the two reads and IDO will not CSE across it -- so DO NOT hoist it into a local.
 * LEFT: FP register allocation is one slot out (ours starts loads at $f0 and puts 0.5f in
 * $f14; golden starts at $f2 and uses $f16).  LAW C says add a local; one extra local for
 * `0.5f * unk74` does not move it (still 21).  Needs the right one.
 */

typedef struct Obj1515B994 {
    char pad0[0x14];
    /* 0x14 */ f32 unk14;
    char pad18[4];
    /* 0x1C */ f32 unk1C;
    char pad20[0x74 - 0x20];
    /* 0x74 */ f32 unk74;
    /* 0x78 */ f32 unk78;
    /* 0x7C */ f32 unk7C;
    /* 0x80 */ f32 unk80;
} Obj1515B994;

extern f32 D_800BE9A4;

s32 func_1515B994(Obj1515B994 *arg0) {
    f32 old;
    f32 acc;

    old = arg0->unk78;
    acc = 0.5f * arg0->unk74;
    arg0->unk14 = arg0->unk14 + ((old * D_800BE9A4) + (acc * D_800BE9A4));
    arg0->unk78 = old + (arg0->unk74 * D_800BE9A4);
    arg0->unk1C = arg0->unk7C + ((arg0->unk80 * (arg0->unk78 + old)) * 0.5f);
    return 1;
}
