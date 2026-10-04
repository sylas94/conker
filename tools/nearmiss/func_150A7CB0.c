/* tools/nearmiss/func_150A7CB0.c -- game_D5160, 20 instructions, leaf
 * STATUS: mism=2 AT PLAIN -O2, n=20/20.  Cold decompile 2026-08-25.
 * >>> THIS TU NEEDS `$(BUILD_DIR)/$(SRC_DIR)/game_D5160.c.o: OPT_FLAGS := -O2` <<<
 * game_D5160 is ONE pragma and ZERO matched functions, so the override is free to add.
 * Golden fills the `jr $ra` delay slot with a store, which -g3 forbids: at -O2 -g3 the best
 * is 3 with a wasted delay slot; at -O2 it is 2 and the slot is filled.
 *
 * Builds a 4x4 scale matrix: [0]=arg1, [5]=arg2, [10]=arg3, [15]=1.0f, everything else 0.
 * The three scale slots and all the zeros are stored with INTEGER `sw` (arg1..arg3 arrive in
 * $a1..$a3 as raw words), so the struct must be s32 for those fields and f32 only for
 * unk3C -- declaring them f32 makes IDO insert `mtc1` moves and costs 8 words (100 -> 60 -> 3).
 * LEFT: 2 rows -- golden puts `sw zero,0x38(a0)` in the delay slot and `swc1 f4,0x3C(a0)`
 * before it; we choose the opposite instruction for the slot.  Swapping the two source
 * statements does not change it.
 */

typedef struct M150A7CB0 {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ s32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ s32 unk24;
    /* 0x28 */ s32 unk28;
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ s32 unk30;
    /* 0x34 */ s32 unk34;
    /* 0x38 */ s32 unk38;
    /* 0x3C */ f32 unk3C;
} M150A7CB0;

void func_150A7CB0(M150A7CB0 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    arg0->unk0 = arg1;
    arg0->unk4 = 0;
    arg0->unk8 = 0;
    arg0->unkC = 0;
    arg0->unk10 = 0;
    arg0->unk14 = arg2;
    arg0->unk18 = 0;
    arg0->unk1C = 0;
    arg0->unk20 = 0;
    arg0->unk24 = 0;
    arg0->unk28 = arg3;
    arg0->unk2C = 0;
    arg0->unk30 = 0;
    arg0->unk34 = 0;
    arg0->unk38 = 0;
    arg0->unk3C = 1.0f;
}
