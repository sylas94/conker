/* tools/nearmiss/func_1507488C.c -- game_981E0, 26 instructions, leaf
 * STATUS: mism=23, n=26/26 (EXACT LENGTH).  Cold decompile 2026-08-25.
 * Same D_800D1580 command word as func_1506EF5C (work them together): tests a per-index mask
 * word at o->unk2E4[(packed>>16)&0xFF] against (packed>>8)&0xFF, XORs the low bit of the
 * command into a flag, and if the flag survives adds (packed>>24) to o->unk138.
 * LEFT: register allocation only -- ours loads the command into $v0 and the object into $v1,
 * golden the reverse, and everything downstream shifts.  An explicit `hi` local per LAW C
 * changes nothing (still 23).
 */

typedef struct Obj1507488C {
    char pad0[0x138];
    /* 0x138 */ u8 unk138;
    char pad139[0x2E4 - 0x139];
    /* 0x2E4 */ s32 unk2E4[8];
} Obj1507488C;

void func_1507488C(void) {
    Obj1507488C *o;
    s32 packed;
    u8 flag;

    packed = D_800D1580;
    o = (Obj1507488C *)D_800D154C;
    flag = packed & 1;
    if ((o->unk2E4[(packed >> 16) & 0xFF] & ((packed >> 8) & 0xFF)) != 0) {
        flag = flag ^ 1;
    }
    if (flag != 0) {
        o->unk138 += packed >> 24;
    }
}
