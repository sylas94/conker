/* tools/nearmiss/func_150ECC70.c -- game_1199D0, 344 instructions, frame 0x38
 *
 * STATUS (2026-10-03, cold wave): mism=229, n=340/344, frame EXACT. Byte-identical through
 * word 146; the rest is the SAME stream shifted 2 words. The ONLY real defect is one
 * unconditional-branch delay-slot choice made inside as1:
 *   golden: lui at,0x435C / mtc1 f16 / nop / swc1 f16,0x190(s0) / b .L150ECF38 / lui at,0x40C0
 *           (copies the merge block's first insn into the slot, branches to merge+4)
 *   ours:   lui / mtc1 / b merge / swc1   (store sunk into the slot, hazard nop dropped)
 * Same family as func_1516C934 / func_1515589C ("unsteerable unconditional-branch delay slot",
 * ido_cookbook.md ~267/~2671). FLAGS DO NOT HELP (measured): -O2 -g3 229, -O2 229, -O1 710, -g 848.
 * No rodata blocker (all float constants inline lui+mtc1).
 * REFUTED (13 spellings): nested/else-if/goto forms of the `sp28 == 0` return, same-line joins,
 * cast-pointer store, inverted outer polarity (363), array+loop like sibling func_150E1860
 * (513/1120), combined unk84 expression (275). Ternary clamps score 30 at n=344 but are
 * structurally FURTHER (clamp codegen changes, slot still sunk) -- do not ship that.
 * Function: 3-channel colour fade (sibling func_150E1860 in game_10ED10 is the 4-entry loop form).
 * File-local decls needed: see top of the body below. Arg type = existing struct108.
 */
s32 func_1509BE40();
void func_150495B0(f32 *arg0, f32 arg1, f32 *arg2, f32 arg3, f32 arg4, f32 arg5);
extern f32 D_80088AD0;
extern f32 D_80088AD4;
extern f32 D_80088AD8;
extern f32 D_80088ADC;
extern f32 D_80088AE0;
extern f32 D_80088AE4;
extern f32 D_80088AE8;
extern f32 D_80088AEC;
extern f32 D_80088AF0;

void func_150ECC70(struct108 *arg0) {
    s32 a3;
    s32 v1;
    s32 sp2C;
    s32 sp28;

    if (func_1509BE40(1, 0x403B, 6, 0x2000) != 0) {
        func_1509BFB0(0, 0x4031, 1);
        func_1509BFB0(0, 0x4032, 1);
        func_1509BFB0(0, 0x4033, 1);
        arg0->unk84 |= 0x80021200;
        if (func_1509BE40(1, 0x4038, 6, 0x2000) != 0) {
            D_80088ADC = 128.0f;
            D_80088AE0 = 255.0f;
            D_80088AE4 = 255.0f;
        } else if (func_1509BE40(1, 0x4039, 6, 0x2000) != 0) {
            D_80088ADC = 255.0f;
            D_80088AE0 = 128.0f;
            D_80088AE4 = 255.0f;
        } else if (func_1509BE40(1, 0x403A, 6, 0x2000) != 0) {
            D_80088ADC = 255.0f;
            D_80088AE0 = 255.0f;
            D_80088AE4 = 128.0f;
        } else {
            D_80088ADC = 255.0f;
            D_80088AE0 = 255.0f;
            D_80088AE4 = 255.0f;
        }
        sp28 = func_1509BE40(0, 0x2007, 0xB7) | 0x2000;
        if (func_1509BE40(1, 0x4010, 6, 0x2000) == 0) {
            arg0->unk134 = 0;
            arg0->unk190 = 0.0f;
            return;
        }
        if (sp28 == 0) {
            return;
        }
        arg0->unk134 = 1;
        sp2C = func_1509BE40(1, sp28, 0x9C, 0x2000);
        func_1509BFB0(1, 0x9000, 0x17, sp2C);
        a3 = func_1509BE40(1, sp28, 0x9A, 0x2000);
        v1 = a3 >> 1;
        if (a3 < 900) {
            a3 = 900;
        } else if (a3 > 0x4A6) {
            a3 = 0x4A6;
        }
        if (v1 < 180) {
            v1 = 180;
        } else if (v1 > 0xE7) {
            v1 = 0xE7;
        }
        func_1509BFB0(2, 0x9000, 8, a3, v1);
        arg0->unk190 = 220.0f;
    } else {
        D_80088ADC = 255.0f;
        D_80088AE0 = 255.0f;
        D_80088AE4 = 255.0f;
        func_1509BFB0(0, 0x4031, 0);
        func_1509BFB0(0, 0x4032, 0);
        func_1509BFB0(0, 0x4033, 0);
        arg0->unk84 &= ~0x80021200;
        arg0->unk84 |= 8;
    }
    func_150495B0(&D_80088AD0, D_80088ADC, &D_80088AE8, 4.0f, 6.0f, arg0->unk7B4);
    func_150495B0(&D_80088AD4, D_80088AE0, &D_80088AEC, 4.0f, 6.0f, arg0->unk7B4);
    func_150495B0(&D_80088AD8, D_80088AE4, &D_80088AF0, 4.0f, 6.0f, arg0->unk7B4);
    func_1509BFB0(1, 0x30F3, 0x12, (u8)D_80088AD0);
    func_1509BFB0(1, 0x30F4, 0x12, (u8)D_80088AD4);
    func_1509BFB0(1, 0x30F5, 0x12, (u8)D_80088AD8);
}
