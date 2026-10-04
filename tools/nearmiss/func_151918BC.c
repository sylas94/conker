/* tools/nearmiss/func_151918BC.c -- game_1BA1D0, 49 instructions, frame 0x30 (s0 + ra saved)
 *
 * STATUS: mism=36, n=50/49 (ONE OVER), FRAME EXACT (-0x30).  Updated 2026-08-26.
 *
 * >>> ITS TWIN func_151A4ECC (game_1D0840) IS NOW SHIPPED BYTE-PERFECT.  What closed it:
 * >>>   LAW G (u8 truthiness): for a `u8` local, `if (x != 0)` makes IDO materialise a
 * >>>   widened copy (`or $vN,$aM,$zero`) and REMATERIALISE the constant after the call
 * >>>   instead of spilling it; `if (x)` / `if (!x)` uses the byte directly and spills
 * >>>   sb/lbu.  See tools/nearmiss/NOTES_ido_loop_laws.md.
 * >>>   Compare operand order: the RIGHT operand is loaded FIRST.
 * Both are applied below (44 -> 39 truthiness, 39 -> 36 compare order) and both are
 * confirmed correct here -- the frame, the u8 sb/lbu spill and the whole prologue match.
 *
 * WHAT IT IS: see the body.  `func_15190770(void *, s32, s32, s32)` is DEFINED in this same
 * TU at line 989 -- read the TU for callee prototypes before inventing them.
 *
 * ---------------------------------------------------------------- SCORE LADDER (measured)
 *   46  sub-struct EMBEDDED in the object (`arg0->unk28.unk4` for the guard byte)
 *   44  flat object fields, `arg0->unk2C != t->unk3B`, `flag == 0` / `flag != 0`
 *   39  ...with `if (!flag)` / `if (flag)`                                    [LAW G]
 *   36  ...with the compare written `t->unk3B != arg0->unk2C` (RIGHT OPERAND LOADED FIRST)
 *   36  every variant of where `f` is materialised: assigned at function top, assigned
 *       inside `if (!flag)`, block-scoped `Frm *f = ...` initialiser, `register Frm *f`,
 *       declared first among the locals, embedded-struct object so no cast is needed,
 *       and fully inline `((Frm151918BC *)&arg0->unk28)->...` at every use (41).
 *       NONE of them removes the duplicate.
 *
 * ---------------------------------------------------------------- WHAT IS LEFT (ONE CAUSE)
 * We emit `addiu $a0, $s0, 40` TWICE -- once before the `beq` (hoisted with the else
 * block's `addiu $t5,$zero,300`) and again as the first instruction of the THEN block.
 * Golden emits it ONCE, before the branch, and both arms share it.  That duplicate is the
 * +1 length; every remaining mismatch after row 26 is the resulting one-row shift, so
 * KILLING THE DUPLICATE CLOSES THE FUNCTION.  It is a rematerialisation, not a schedule:
 * IDO re-derives `base + const` per basic block.  Find what gives the address a single
 * shared value number across the if/else and this is done.
 */
typedef struct Tgt151918BC {
    s32 unk0;
    char pad4[0x37];
    u8 unk3B;
    char pad3C[0x198];
    s32 unk1D4;
} Tgt151918BC;

typedef struct Frm151918BC {
    Tgt151918BC *unk0;
    u8 unk4;
    u8 unk5;
    s16 unk6;
    u8 unk8;
} Frm151918BC;

typedef struct Obj151918BC {
    u8 pad0;
    u8 unk1;
    char pad2[0xA];
    u8 unkC;
    u8 unkD;
    s16 unkE;
    char pad10[0x18];
    Tgt151918BC *unk28;
    u8 unk2C;
} Obj151918BC;

void func_151918BC(Obj151918BC *arg0) {
    Tgt151918BC *t;
    Frm151918BC *f;
    u8 flag;

    flag = 0;
    t = arg0->unk28;
    if (t->unk0 == 0) {
        flag = 1;
    } else if (t->unk3B != arg0->unk2C) {
        flag = 1;
    }
    if (!flag) {
        if (t->unk1D4 != 0) {
            f = (Frm151918BC *)&arg0->unk28;
            flag = 1;
            if ((arg0->unkD & 1) != 0) {
                f->unk8 = f->unk8 | 1;
                f->unk6 = arg0->unkE;
            } else {
                f->unk6 = 0x12C;
            }
            func_15190770(f, 0, arg0->unkC, arg0->unk1);
        }
    }
    if (flag) {
        func_1516972C(arg0);
    }
}
