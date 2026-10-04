/* tools/nearmiss/func_1507F454.c -- game_AC030, 27 instructions, leaf
 * STATUS: mism=11, n=27/27 (EXACT LENGTH).  Cold decompile 2026-08-25.
 * Steps an animation cursor: reads the sub-record at D_800D154C->unk31C + 0x58, bumps its
 * frame counter, and clears the pair when the D_80086BA0[idx] table byte reads 0.
 * The `+ 0x58` sub-struct POINTER is right: golden folds the first read to `lbu 0x5C(v1)`
 * off the parent and only then does `addiu v1,v1,88` for the rest -- exactly what a single
 * sub-pointer local produces.
 * LEFT: temp-register rotation only.  Golden runs t9,t7,t8,t0; ours runs t8,t9 and then
 * wraps into $a0, i.e. we are ONE temp ahead.  LAW C says drop a local, not add one --
 * adding a `tbl` local makes it worse (11 -> 18).
 */

typedef struct Sub1507F454 {
    char pad0[4];
    /* 0x04 */ u8 unk4;
    /* 0x05 */ u8 unk5;
} Sub1507F454;

typedef struct Rec1507F454 {
    char pad0[0x31C];
    /* 0x31C */ void *unk31C;
} Rec1507F454;

extern u8 *D_80086BA0[];

s32 func_1507F454(void) {
    Sub1507F454 *s;
    u8 idx;
    u8 n;

    s = (Sub1507F454 *)((u8 *)((Rec1507F454 *)D_800D154C)->unk31C + 0x58);
    idx = s->unk4;
    if (idx == 0) {
        return 1;
    }
    n = s->unk5 + 1;
    s->unk5 = n;
    if (D_80086BA0[idx][n] == 0) {
        s->unk4 = 0;
        s->unk5 = 0;
        return 1;
    }
    return 0;
}
