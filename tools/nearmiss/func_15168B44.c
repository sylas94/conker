/* tools/nearmiss/func_15168B44.c -- game_1944C0, 26 instructions, leaf
 * STATUS: mism=34, n=25/26 (ONE SHORT).  Cold decompile 2026-08-25.
 * unk14 is a PACKED PAIR OF u16 accessed with explicit masks, NOT a bitfield: spelling it as
 * `u32 hi:16; u32 lo:16` makes IDO use `lhu 0x16(a0)` / `sh` halfword accesses (89, n=19),
 * while golden does `lw 0x14` + andi/and/or.  That is the counter-example to the bitfield law
 * -- a half-word mask on a 32-bit load is NOT automatically a bitfield.
 * Golden stores unk14 TWICE (the cleared value, then the recombined value), so the source
 * really does two assignments; a single combined assignment loses a word.  Hoisting the
 * cleared value into a local gets both stores but still n=25.
 * LEFT: 1 word + register naming.
 */

typedef struct Obj15168B44 {
    char pad0[0x14];
    /* 0x14 */ u32 unk14;
    char pad18[0x38 - 0x18];
    /* 0x38 */ s16 unk38;
    char pad3A[0x3F - 0x3A];
    /* 0x3F */ u8 unk3F;
} Obj15168B44;

void func_15168B44(Obj15168B44 *arg0) {
    u32 v;
    u32 hi;
    u32 lo;

    v = arg0->unk14;
    lo = v & 0xFFFF;
    if (lo != 0) {
        hi = v & 0xFFFF0000;
        arg0->unk14 = hi;
        arg0->unk38 = 0x1E;
        arg0->unk14 = hi | ((lo - 1) & 0xFFFF);
    } else if ((s32)((v >> 16) & 0xFFFF) < arg0->unk3F) {
        arg0->unk3F = arg0->unk3F - ((v >> 16) & 0xFFFF);
        arg0->unk38 = 0x1E;
    } else {
        arg0->unk38 = 0;
    }
}
