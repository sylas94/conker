/* tools/nearmiss/func_150EA490.c -- game_117490, 28 instructions, frame -0x18
 * STATUS: mism=43, n=26/28 (TWO SHORT).
 * >>> EXACT TWIN of tools/nearmiss/func_151AAA4C.c (game_1D6E80): same code with the record
 * >>> at +0x80 instead of +0x88.  Same score, same residue.  SOLVE ONE, SHIP BOTH.
 * unk80 must be u32 (golden uses `srl`), and func_151423D8 takes a u8 -- passing an explicit
 * u8 local is worth 10.
 * LEFT (both twins): golden keeps the object pointer ONLY in its incoming home slot --
 * `sw a0,0x18(sp)` at entry, then a fresh `lw` from that slot before every use, including one
 * immediately after the store.  We keep it in $a1.  A `void *` parameter with casts at every
 * use scores identically (43), so the parameter TYPE is not the lever.
 */

typedef struct Obj150EA490 {
    char pad0[0x80];
    /* 0x80 */ u32 unk80;
    /* 0x84 */ s32 unk84;
    /* 0x88 */ f32 unk88;
    /* 0x8C */ f32 unk8C;
} Obj150EA490;

extern s32 D_800BE9E4;

f32 func_150EA490(Obj150EA490 *arg0) {
    f32 t;
    u8 idx;

    idx = (arg0->unk80 >> 16) - 0x40;
    t = func_151423D8(idx);
    arg0->unk80 = arg0->unk80 + (arg0->unk84 * D_800BE9E4);
    return (t * arg0->unk8C) + arg0->unk88;
}
