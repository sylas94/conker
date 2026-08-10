/* func_15060778 (game_83300.c) -- best 2878.
 * Instruction-for-instruction identical to the target EXCEPT one register-allocation
 * decision: the target keeps the (u16)id value in caller-saved a0 and spills it to
 * sp+0x44 around each call; IDO here promotes it to a callee-saved reg (s0/s1, frame
 * 0x50 vs 0x58) and copies it with `andi a0,sN,0xffff` at each use.
 * Tried and rejected: u16/s32/u32 id, explicit (u16) casts at 0/1/all call sites,
 * 48 declaration-order permutations, split id/cur variables (memory-homed instead),
 * field expressions instead of the variable (reloads after the call), `register`,
 * tail duplication.  PERMUTER CANDIDATE.
 * Notes that ARE settled and correct:
 *   - `== arg0 & 0x7FFF` is a real C precedence bug in the original (gives
 *     xor/sltiu/andi 0x7FFF); parenthesising it would NOT match.
 *   - `if (mode == 2) { break; }` (early break) is what produces the
 *     `bne a0,v0 -> case-3 body` layout; an `if (mode != 2) {...}` wrapper gives beq.
 *   - s32 id + implicit u16 param conversions is what makes the raw id die before
 *     the call (target reuses v1 for arg0 right after func_1001147C).
 */
s32 func_10010E78(u16 arg0, s32 arg1, u16 arg2, s16 arg3, u8 arg4, s32 arg5,
                  s16 arg6, s16 arg7, s16 arg8, s16 arg9, s16 argA);

void func_15060778(s32 arg0, struct127 *arg1, u16 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    s32 id;
    u16 *dest;
    s32 flags;
    s32 mode;
    u16 handle;

    id = 0;
    dest = NULL;
    if (arg6 & 8) {
        flags = 0;
    } else {
        flags = ((u32)arg1->unk184 >> 3) & 0x30;
    }

    mode = arg6 & 3;
    switch (mode) {
    case 1:
        dest = &arg1->unk8C;
        id = arg1->unk8C;
        break;
    case 2:
    case 3:
        dest = &arg1->unk8E;
        id = arg1->unk8E;
        if (mode == 2) {
            break;
        }
        if (func_1001147C(id) == arg0 & 0x7FFF) {
            if (arg6 & 4) {
                func_1000F91C(id, arg2 + (flags * 50), (arg1->unk13F * 10) + arg3, flags, 0,
                              arg1->x_position, arg1->y_position, arg1->z_position, arg4, arg5);
            } else {
                func_1000F85C(id, 0x10, arg3);
                func_1000F85C(id, 8, arg2 + (flags * 50));
            }
            return;
        }
        arg0 |= 0x8000;
        break;
    }

    if (arg6 & 4) {
        handle = func_10010E78(id, arg0, arg2 + (flags * 50), arg3, flags, 0,
                               arg1->x_position, arg1->y_position, arg1->z_position, arg4, arg5);
    } else {
        handle = func_10010BE8((u16)id, arg0, arg2 + (flags * 50), 0x40, arg3, flags, 1);
    }
    if (dest != NULL) {
        *dest = handle;
    }
}
