/* game_14F130 / func_15121C80 -- NEAR MISS, mism=5, n=276/276, frame 0x50 (both correct)
 *
 * Score: python3 tools/fastscore.py game_14F130 func_15121C80 tools/nearmiss/func_15121C80.c
 *
 * THE ONLY REMAINING DIFFERENCE is a single FP register pair swapped, f0 <-> f2:
 *     idx167  ours lwc1 f0,%lo(D_800A3448)   golden lwc1 f2      <- `mark`
 *     idx168  ours lwc1 f2,0x18C(v1)         golden lwc1 f0      <- the 0x18C value
 *     idx169  ours c.eq.s f0,f2              golden c.eq.s f2,f0
 *     idx173  ours swc1 f2,0x37C(s0)         golden swc1 f0
 *     idx195  ours swc1 f0,0x18C(t0)         golden swc1 f2
 *   Operand ROLES are identical (`mark != value` both ways); only the physical
 *   registers differ.  In golden `mark` shares f2 with `accel`; in ours it shares
 *   f0 with `rate`.  This is FP temp-register rotation, the float analogue of the
 *   GPR t6..t3 rotation -- something earlier in the function must consume one more
 *   or one fewer FP temp than our source does.  Every instruction up to idx166 is
 *   already byte-identical, so the difference is invisible in the emitted code.
 *
 * DO NOT REPEAT (all measured)
 *   - all 6 permutations of the declaration order of rate/accel/mark: FLAT at 5.
 *     Declaration order does NOT drive the FP assignment here.
 *   - `mark` declared first (13) or last (8) -- worse, because it moves sp4C off 0x4C.
 *   - `*(f32*)(..0x18C) != mark` instead of `mark != ..`: still 5 (same rows).
 *   - caching the 0x18C value in a second local `cur`: 18, and the frame grows to
 *     0x58 -- there is no room, the local area is exactly 32 bytes:
 *       0x4C sp4C | 0x48/0x44/0x40 three f32 | 0x3C flag | 0x30 struct17 sp30.
 *   - `mark = D_800A3448` hoisted to the top of the function: 160.
 *   - caching arg0->unk3D4 in a local across the block: 98 (golden re-reads it for
 *     the final 0x18C store -- keep `arg0->unk3D4` spelled out in all four places).
 *   - caching arg0->unk3D0 in a local: no change (IDO coalesces it away).
 *
 * WHAT WAS LOAD-BEARING (do not undo)
 *   - the D_800A3448 compare arms are INVERTED relative to the obvious reading:
 *     the `!=` arm must come FIRST (it is the fall-through).  Writing `==` first
 *     costs ~25 rows.
 *   - the 12-byte copy must be STRUCT ASSIGNMENT (`*(struct17*)&arg0->unk2F8 = sp30;`),
 *     which IDO block-copies with lw/sw.  Member-wise float assignment emits
 *     lwc1/swc1 and costs ~20 rows.
 *   - `mark` MUST exist: without it IDO materialises &D_800A3448 and loads it twice,
 *     adding an instruction (n=277) and shifting every branch offset after idx94.
 *   - the sp4C expression must be written product-first:
 *       ((f32)u16field * 0.0054931640625f) + f32field
 *     the other order delays the 0x40 load past the bgez block (22 rows).
 *   - func_15048758 takes `f32 *` and is called as func_15048758(&sp4C) -- a0 is set
 *     back at .L15121E04 and kept alive across the whole block.
 *
 * CALIBRATION TWINS: conker/src/game_14F580.c func_15122170 and game_14F8F0.c
 *   func_15122980 -- same struct108 player type and the same
 *   func_1512A390 / func_15123A54 / func_1512E140 tail.
 */
#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern f32 D_800A3440;
extern f32 D_800A3444;
extern f32 D_800A3448;
extern f32 D_800A344C;
extern f32 D_800A3450;
extern f32 D_800A3454;
extern u8 D_800BEA0C;
void func_150495B0(f32 *arg0, f32 arg1, f32 *arg2, f32 arg3, f32 arg4, f32 arg5);
void func_15049688(f32 *arg0, f32 arg1, f32 *arg2, f32 arg3, f32 arg4, f32 arg5);
void func_15123A54(struct108 *arg0);
void func_1512E140(struct108 *arg0);
void func_1512A390(struct108 *arg0);

void func_15121C80(struct108 *arg0, f32 arg1) {
    f32 sp4C;
    f32 rate;
    f32 accel;
    f32 mark;
    s32 flag;
    struct17 sp30;

    flag = (arg0->unk5F0 & 0x10) != 0;
    if (flag) {
        flag = (*arg0->unk36C & 0x10) != 0;
    }

    if ((flag == 0) &&
        ((D_800BE616 != 0) || (arg0->unk23E == 9) || (arg0->unk23E == 0x3B)) &&
        (*(u8 *)((u8 *)arg0->unk3D4 + 0x1B3) != 0)) {
        if (D_800BE616 != 0) {
            *(f32 *)((u8 *)arg0 + 0x97C) = 5.0f;
            *(f32 *)((u8 *)arg0 + 0x980) = 8.0f;
            func_150495B0((f32 *)((u8 *)arg0 + 0x96C), 5.0f, (f32 *)((u8 *)arg0 + 0x98C), 1.0f, 2.0f, arg0->unk7B4);
            func_150495B0((f32 *)((u8 *)arg0 + 0x970), *(f32 *)((u8 *)arg0 + 0x980), (f32 *)((u8 *)arg0 + 0x990), 1.0f, 2.0f, arg0->unk7B4);
            func_15049688(&arg0->unk37C, *(f32 *)((u8 *)arg0->unk3D0 + 0x40) - 180.0f, (f32 *)&arg0->unk7C8,
                          *(f32 *)((u8 *)arg0 + 0x96C), *(f32 *)((u8 *)arg0 + 0x970), arg0->unk7B4);
        } else {
            func_15049688(&arg0->unk37C, *(f32 *)((u8 *)arg0->unk3D0 + 0x40) - 180.0f, (f32 *)&arg0->unk7C8,
                          5.0f, 8.0f, arg0->unk7B4);
        }
        arg0->unk39C = arg0->unk37C * D_800A3440;
    } else if (arg0->unk698 == 0) {
        sp4C = ((((f32)*(u16 *)((u8 *)arg0->unk3D0 + 0x7C) * 0.0054931640625f) +
                 *(f32 *)((u8 *)arg0->unk3D0 + 0x40)) - 180.0f) - arg1;

        if (flag != 0) {
            if (arg0->unk23E != 0x1C) {
                sp4C -= (f32)(*(s32 *)((u8 *)arg0->unk3D0 + 0x2E4) >> 0x10) * D_800A3444;
            }
        }

        if ((arg0->unk23E == 9) || (arg0->unk23E == 0x38) || (arg0->unk23E == 0x39) ||
            (arg0->unk23E == 0x37) || (arg0->unk23E == 0x3B) || (arg0->unk23E == 0x12)) {
            sp4C -= (f32)*(s16 *)((u8 *)arg0->unk3D4 + 0x12) * 0.0054931640625f;
        }

        func_15048758(&sp4C);

        if (arg0->unk23C != 0) {
            mark = D_800A3448;
            if (mark != *(f32 *)((u8 *)arg0->unk3D4 + 0x18C)) {
                arg0->unk37C = *(f32 *)((u8 *)arg0->unk3D4 + 0x18C);
                sp30 = *(struct17 *)((u8 *)arg0->unk3D4 + 0x160);
                *(struct17 *)&arg0->unk2F8 = sp30;
                *(struct17 *)&arg0->unk304 = sp30;
                *(f32 *)((u8 *)arg0->unk3D4 + 0x18C) = mark;
            } else {
                arg0->unk37C = sp4C;
            }
            *(f32 *)&arg0->unk7C8 = 0.0f;
        } else {
            if ((flag != 0) || (arg0->pad600[0] != 0)) {
                rate = 4.0f;
                accel = 6.0f;
            } else if (((arg0->unk23E == 9) && (D_800BE616 != 0)) || (arg0->unk23E == 0x38) ||
                       (arg0->unk23E == 0x39) || (arg0->unk23E == 0x37) ||
                       (arg0->unk23E == 0x3B) || (arg0->unk23E == 0x12)) {
                rate = 2.0f;
                accel = 6.0f;
            } else if (arg0->unk84 & 0x200000) {
                rate = 1.0f;
                accel = D_800A344C;
            } else {
                rate = 0.75f;
                accel = D_800A3450;
            }
            if (D_800BEA0C == 0) {
                func_15049688(&arg0->unk37C, sp4C, (f32 *)&arg0->unk7C8, rate, accel, arg0->unk7B4);
            }
        }
        arg0->unk39C = arg0->unk37C * D_800A3454;
    }

    func_1512A390(arg0);
    func_15123A54(arg0);
    func_1512E140(arg0);
}
