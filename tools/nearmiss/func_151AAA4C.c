/* tools/nearmiss/func_151AAA4C.c -- game_1D6E80, 28 instructions, frame -0x18
 * STATUS: mism=43, n=26/28 (TWO SHORT).  Cold decompile 2026-08-25.
 * Advances a packed timer and returns t*unk94 + unk90 where t = func_151423D8(u8 index).
 * unk88 must be u32 -- golden uses `srl`, and s32 gives `sra` (worth 1 row).
 * func_151423D8 is declared `f32 func_151423D8(u8)` in functions.h; passing an explicit u8
 * local is worth 10 (53 -> 43).
 * LEFT: golden keeps arg0 ONLY on the stack -- `sw a0,0x18(sp)` at entry and then a fresh
 * `lw` from that home slot before EVERY use, including one immediately after the store.  We
 * keep it in $a1.  Find what denies the pointer a register (address-taken? a wider parameter
 * list?) and the two missing words are those reloads.
 */

typedef struct Obj151AAA4C {
    char pad0[0x88];
    /* 0x88 */ u32 unk88;
    /* 0x8C */ s32 unk8C;
    /* 0x90 */ f32 unk90;
    /* 0x94 */ f32 unk94;
} Obj151AAA4C;

extern s32 D_800BE9E4;

f32 func_151AAA4C(Obj151AAA4C *arg0) {
    f32 t;
    u8 idx;

    idx = (arg0->unk88 >> 16) - 0x40;
    t = func_151423D8(idx);
    arg0->unk88 = arg0->unk88 + (arg0->unk8C * D_800BE9E4);
    return (t * arg0->unk94) + arg0->unk90;
}
