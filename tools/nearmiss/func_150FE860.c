/* game_12BD10 / func_150FE860 -- NEAR MISS, mism=7, n=218/218, frame 0x110 (correct)
 *
 * Score this file straight: python3 tools/fastscore.py game_12BD10 func_150FE860 tools/nearmiss/func_150FE860.c
 *
 * REMAINING 7 ROWS
 *   idx18/20  beqz delay slot holds `lui at,%hi(D_800A2034)`; golden holds
 *             `lwc1 f12,0xF8(sp)`.  Pure swap of two hoisted instructions.
 *   idx26     `addu a2,t7,v0` vs golden `addu a2,v0,t7` (operand order of
 *             temp + D_80088BA0*0x40).  Swapping the C operands does NOT change it.
 *   idx107/109/116/123
 *             rand0/rand1 land at 0x8C/0x90; golden has them at 0x88/0x8C.
 *             ROOT CAUSE + THE OPEN QUESTION, see below.
 *
 * THE OPEN QUESTION (this is the whole blocker)
 *   Golden's local area is exactly 136 bytes (0x88..0x10F, frame 0x110, base 0x88
 *   is fixed by the arg area + 8B temp + s0/ra at 0x78/0x7C).  Fixed slots:
 *     0x104/0xF8/0xEC/0xE0/0xD4/0xC8  six struct17          (72)
 *     0xC0..0xC7                      2 unidentified words   (8)
 *     0xBC spBC, 0xB0 spB0[3], 0xA4 spA4[3]                 (28)
 *     0x90..0xA3                      5 unidentified words  (20)
 *     0x8C rand1, 0x88 rand0                                 (8)
 *   rand0 at 0x88 is the BOTTOM slot => golden has NO block-scope local, because
 *   IDO allocates block-scope slots BELOW every function-scope one (measured).
 *   But two schedule flips in this function are ONLY reproduced by a block-scope
 *   declaration inside the inner `if` of the else branch:
 *     * idx63/64  golden `bc1tl .L150FE980` + duplicated `lwc1 f18,0x100(sp)`;
 *                 without it we emit `bc1t` + `nop`.
 *     * idx83/84  golden `nop; b; lui at,0x4208`(delay-slot duplicate of the
 *                 join block's first insn); without it we emit `b; nop`.
 *   Both are the same IDO transform: branch-likely with the successor block's
 *   first instruction duplicated into the delay slot.  Find the fn-scope-only
 *   construct that triggers it and this function closes.
 *
 * DO NOT REPEAT (all measured, all worse or neutral)
 *   - block decl in the *else* block (depth 1)         -> no flip      (153)
 *   - block decl in the inner *else* arm               -> no flip      (182)
 *   - block var copied into inv / dz / spBC (coalesce) -> still costs a slot
 *   - 10th function-scope scalar (pressure alone)      -> no flip      (182)
 *   - `inv = sqrtf(..); dz = z*(1.0f/inv)`             -> 154
 *   - `dx = (0.0f - x) * inv`                          -> emits mtc1+sub.s, +1 insn
 *   - `dx = x * -inv`                                  -> neg.s on inv, not on x
 *   - sqrt arg as `z*z + x*x`                          -> add.s operands swap
 *   - moving `spBC = 0;` after/below the inner if      -> sw lands at idx90 (wrong)
 *   - `D_800A2034 < fabsf(x)` instead of `fabsf(x) > D_800A2034` -> identical
 *   - swapping the C operands of `temp + D_80088BA0*0x40` -> identical asm
 *   - `mtx` block-local in the THEN block IS REQUIRED (fixes idx55-57 b/nop) and
 *     is FREE (coalesces into spBC's slot) -- keep it.
 *
 * CALIBRATION TWINS (same call shape, already matched): conker/src/game_12B250.c
 *   func_150FDDA0, game_12B7D0.c func_150FE320, game_12C1E0.c func_150FED30.
 *   `((u8 *)&arg1)[3]` for the u8 arg, `s32 unused;` for register-resident slots.
 */
#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern f32 D_800A2030;
extern f32 D_800A2034;
extern f32 D_800A2038;
extern s32 D_800A2000;
extern s32 D_800A200C;
extern s32 D_800A2018;
extern s32 D_800A2024;
extern u8 D_80088BA0;
extern s32 func_15145EA4(s32 *arg0, s32 *arg1, s32 arg2, s32 arg3);
void func_15145740(struct127 *arg0, struct17 *arg1, struct17 *arg2, struct17 *arg3, f32 arg4);
void func_151D5148(struct127 *arg0);
s32 func_151C229C(struct17 *arg0, struct17 *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, f32 arg10, s32 arg11, struct127 *arg12, s32 arg13, s32 arg14, s32 arg15, s32 arg16, s32 arg17, s32 arg18, s32 arg19, s32 arg20, f32 arg21, s32 arg22, s32 arg23, s32 arg24, s32 arg25, s32 arg26);
void func_151D3F14(struct17 *arg0, u8 arg1, s32 arg2);
void func_151D4408(struct17 *, struct17 *, void *, struct127 *, f32, s32, s32);
void func_150FEC28(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, u8 arg5, s32 arg6);

void func_150FE860(struct127 *arg0, s32 arg1, s32 arg2) {
    struct17 sp104;
    struct17 spF8;
    struct17 spEC;
    struct17 spE0;
    struct17 spD4;
    struct17 spC8;
    f32 dx;
    f32 dz;
    s32 spBC;
    s32 spB0[3];
    s32 spA4[3];
    s32 temp;
    s32 temp_v0;
    s32 padA;
    s32 padB;
    f32 rand1;
    f32 rand0;

    func_151D5148(arg0);
    func_15145740(arg0, &spF8, &spEC, &spE0, D_800A2030);

    temp = (s32) arg0->unk1D4;
    if (temp != 0) {
        s32 mtx;

        mtx = temp + D_80088BA0 * 0x40;
        spB0[0] = (s32)&D_800A2000;
        spB0[1] = (s32)&D_800A2018;
        spB0[2] = (s32)&D_800A2024;
        spA4[0] = (s32)&sp104;
        spA4[1] = (s32)&spD4;
        spA4[2] = (s32)&spC8;
        spBC = mtx;
        func_15145EA4(spB0, spA4, spBC, 3);
        spC8.unk0 -= spD4.unk0;
        spC8.unk4 -= spD4.unk4;
        spC8.unk8 -= spD4.unk8;
    } else {
        spBC = 0;
        if ((fabsf(spF8.unk0) > D_800A2034) || (fabsf(spF8.unk8) > D_800A2034)) {
            f32 inv;

            inv = 1.0f / sqrtf((spF8.unk0 * spF8.unk0) + (spF8.unk8 * spF8.unk8));
            dz = spF8.unk8 * inv;
            dx = -spF8.unk0 * inv;
        } else {
            dz = 1.0f;
            dx = 0.0f;
        }
        sp104.unk0 = arg0->x_position + (34.0f * dx);
        sp104.unk4 = arg0->y_position + 49.0f;
        sp104.unk8 = arg0->z_position + (34.0f * dz);
    }

    rand0 = func_150ADA68();
    rand1 = func_150ADA68();
    temp_v0 = func_150ADA20();
    func_151C229C(&sp104, &spF8, 0, 0, 0, 0, 300.0f, D_800A2038,
                  (rand0 * 10.0f) + 25.0f, (rand1 * 200.0f) + 400.0f, 50.0f,
                  (temp_v0 % 0x9CU) + 0x64, arg0, 1, 1, 0, 0, 1, 1, 0, 0x35,
                  0.0f, 0xFF, -1, 0, ((u8 *)&arg1)[3], arg2);

    if (arg0->unk1D4 != 0) {
        if ((arg0->unk74 & 0xF) != 0xF) {
            func_151D3F14(&sp104, ((u8 *)&arg1)[3], arg2);
            func_151D4408(&spD4, &spC8, (void *)spBC, arg0, 1.0f, ((u8 *)&arg1)[3], arg2);
            if (func_150ADA20() & 1) {
                func_150FEC28((s32)arg0, D_80088BA0, (s32)&D_800A2000, (s32)&D_800A200C, (s32)&sp104, ((u8 *)&arg1)[3], arg2);
            }
        }
    }
}

extern s32 func_15145EA4
(s32 *arg0, s32 *arg1, s32 arg2, s32 arg3);
extern u8 D_80088BA0;
extern s32 D_800A2000;

typedef struct {
    char pad_0[0x1D4];
    s32 field_0x1D4;
} ActorFields;

void func_150FEBC8(ActorFields *arg0, s32 arg1, s32 arg2) {
    s32 sp20[2];
    s32 sp1C;
    s32 a2;

    a2 = arg0->field_0x1D4 + D_80088BA0 * 0x40;
    sp20[0] = (s32)&D_800A2000;
    sp1C = arg2;
    func_15145EA4(sp20, &sp1C, a2, 1);
}

extern void func_15102B38(s32, u8, s32, s32, f32 *, s32, s32, f32, s32, s32, s32, s32, u8, s32);
extern f32 D_800A203C, D_800A2040, D_800A2044, D_800A2048, D_800A204C;

void func_150FEC28(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, u8 arg5, s32 arg6) {
    f32 sp50[2];
    union { volatile s32 w; f64 d; } sp48;
    s32 sp44;

    sp50[1] = func_150ADA68() * D_800A203C + D_800A2040;
    sp50[0] = func_150ADA68() * D_800A2044 + D_800A2048;
    sp44 = func_150ADA20();
    sp48.w = func_150ADA20();
    func_15102B38(arg0, (u8)arg1, arg2, arg3, sp50, (sp44 & 3) + 6, 0xFF,
                  func_150ADA68() * 270.0f + D_800A204C, arg4, 0xFF, 0, -1,
                  arg5, arg6);
}
