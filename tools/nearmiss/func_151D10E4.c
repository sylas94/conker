/* tools/nearmiss/func_151D10E4.c -- game_1FA770, 21 instructions, frame -0x18
 * STATUS: mism=12, n=21/21 (EXACT LENGTH).  Cold decompile 2026-08-25.
 * Guards on arg0->unk1D4 and forwards to func_15143134(&D_800AAF9C[arg2], arg1, unk1D4).
 * D_800AAF9C is an array of 12-byte records (the `sll 2 / subu / sll 2` is *12).
 * The forward declaration in game_1FA770.c:506 was `s32 arg2`; corrected to `u8 arg2` here
 * (golden's `sw a2,0x20(sp)` + `andi a2,0xFF` is the u8-parameter tell).
 * LEFT: golden masks the parameter in its register (`andi a3,a2,255`) and computes the
 * record address FIRST; we spill it and reload with `lbu 0x23(sp)`, then load unk1D4 first.
 * Hoisting the record pointer into a local ahead of the guard does not change the score.
 */

typedef struct Obj151D10E4 {
    char pad0[0x1D4];
    /* 0x1D4 */ s32 unk1D4;
} Obj151D10E4;

typedef struct Rec151D10E4 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} Rec151D10E4;

extern Rec151D10E4 D_800AAF9C[];
extern void func_15143134(Rec151D10E4 *, s32, s32);

s32 func_151D10E4(void *arg0, s32 arg1, u8 arg2) {
    Rec151D10E4 *p;
    s32 v;

    p = &D_800AAF9C[arg2];
    v = ((Obj151D10E4 *)arg0)->unk1D4;
    if (v == 0) {
        return 0;
    }
    func_15143134(p, arg1, v);
    return 1;
}
