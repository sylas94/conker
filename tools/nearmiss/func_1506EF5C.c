/* tools/nearmiss/func_1506EF5C.c -- game_981E0, 22 instructions, leaf
 * STATUS: mism=20, n=22/22 (EXACT LENGTH).  Cold decompile 2026-08-25.
 * Unpacks the D_800D1580 command word and writes four fields through the D_800D154C pointer.
 * The pointer is RELOADED before every store in golden -- IDO cannot prove the stores do not
 * clobber it -- so spelling each access as `D_800D154C->...` is correct, not wasteful.
 * D_800D154C is `struct127 *` in variables.h; the local Obj view is reached by a cast macro
 * (the header-inaccuracy idiom) to avoid a redeclaration.
 * LEFT: register allocation only.  Ours starts the temp run at $a0, golden at $a2, and ours
 * keeps the packed word in $v0 where golden keeps `packed >> 16` there.  Adding an explicit
 * `hi = packed >> 16;` local (LAW C) does not move it -- still exactly 20.
 */

typedef struct Obj1506EF5C {
    char pad0[0x276];
    /* 0x276 */ u8 unk276;
    char pad277[0x282 - 0x277];
    /* 0x282 */ u16 unk282;
    /* 0x284 */ u8 unk284[8][2];
} Obj1506EF5C;

#define P1506EF5C ((Obj1506EF5C *)D_800D154C)

void func_1506EF5C(void) {
    s32 packed;
    s32 idx;

    packed = D_800D1580;
    idx = (packed >> 16) & 0xFF;
    P1506EF5C->unk282 = 0xFFFF;
    P1506EF5C->unk276 = 5;
    P1506EF5C->unk284[idx][0] = packed >> 8;
    P1506EF5C->unk284[idx][1] = packed;
}
