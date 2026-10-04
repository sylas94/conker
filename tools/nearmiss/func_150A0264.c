/* tools/nearmiss/func_150A0264.c -- game_CD5A0, 27 instructions, LEAF (no frame)
 *
 * STATUS: mism=9, n=27/27 (EXACT LENGTH), leaf. NINE register names, nothing else.
 * Another prime decomp-permuter candidate (exact length + exact frame + pure register tie).
 * Cold decompile, opened 2026-08-25 from the never-attempted list.
 *
 * WHAT IT IS: "claim slot arg0" over a 12-byte-stride table at D_800D3010. Bails if the
 * record's top bit is already set, otherwise sets it, clears bit 6, zeroes the second word,
 * and packs a 4-bit field (mask 0x3C) out of arg1->unk4.
 *
 * ---------------------------------------------------------------- SCORE LADDER (measured)
 *   12  `r->unk4 = 0;` written BEFORE the final byte assignment
 *   12  ...with arg1->unk4 hoisted into a named local first (identical)
 *   12  ...with the final `or` operands written in the other order (identical)
 *    9  `r->unk4 = 0;` written AFTER the final byte assignment   <-- PARKED
 * Golden emits that `sw $zero, 0x4($v1)` LATE -- after `lw $t6,0x4($a1)` and after the
 * `andi ...,0xC3` -- and only writing it last in the source reproduces that placement.
 *
 * BYTE-NEUTRAL (do not bother): the operand order of the final `or`. Golden reads
 * `or $t1, $t8, $t0` (shifted term first) but BOTH spellings compile identically -- IDO
 * normalises it. Measured on top of both store placements.
 *
 * ---------------------------------------------------------------- WHAT IS LEFT
 * Pure temp rotation, one register behind at the start and then divergent:
 *      ours:   t0 -> t2 -> t4 -> t5 -> t9
 *      golden: t1 -> t3 -> t9 -> t0 -> t1     (it WRAPS; we run sequentially)
 * Same family as func_1516F864 and func_15034420 in this wave. See [[ido-matching-tricks]].
 *
 * ---------------------------------------------------------------- STILL TO PIN
 * The record is almost certainly BITFIELDS, not the byte punning below -- the read/modify/
 * write chain (`ori 0x80` / `andi 0xBF` / `andi 0xC3` + `andi 0x3C`) is exactly what three
 * bitfield assignments produce, and the guard reads the SAME storage as a 32-bit word
 * (`lw` + `srl 31`) while the updates use `lbu`/`sb`. A big-endian layout of
 *      u32 f0:1;  u32 f1:1;  u32 f2:4;  u32 f3:2;  ...
 * puts f0 at 0x80, f1 at 0x40, f2 at 0x3C -- i.e. the guard is `if (r->f0) return 0;`,
 * then `r->f0 = 1; r->f1 = 0; r->unk4 = 0; r->f2 = arg1->unk4;`. That is worth trying
 * before the permuter, since a bitfield spelling may also fix the temp rotation.
 */

typedef struct Rec150A0264 {
    u32 unk0;
    s32 unk4;
    s32 unk8;
} Rec150A0264;

typedef struct Src150A0264 {
    char pad0[4];
    s32 unk4;
} Src150A0264;

extern Rec150A0264 D_800D3010[];

s32 func_150A0264(s32 arg0, Src150A0264 *arg1) {
    Rec150A0264 *r = &D_800D3010[arg0];
    u8 *b;

    if ((r->unk0 >> 31) != 0) {
        return 0;
    }
    b = (u8 *)r;
    *b = *b | 0x80;
    *b = *b & 0xBF;
    *b = (*b & 0xC3) | ((arg1->unk4 << 2) & 0x3C);
    r->unk4 = 0;
    return 1;
}
