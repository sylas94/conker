/* =====================================================================================
 * game_6C960 / func_1503F62C   (396 B, 99 instructions)   PARKED 2026-08-16
 *
 * BEST SCORE: 116   (n = 97/99, frame 0x40 EXACT, sp3C at 0x3C EXACT)
 *
 * THE RESIDUAL, exactly
 *   The instruction STREAM is otherwise identical to golden -- I diffed it row by row.  The
 *   whole 116 is one register-allocator decision and its knock-on renaming:
 *
 *       golden uses TWO callee-saved registers:   s0 = arg0 (copied in the prologue),
 *                                                 s1 = arg6, and s0 is later re-used for the
 *                                                 CSEd `*arg6` temp in the error path.
 *       live C uses ONE:                          s0 = arg6; arg0 is HOMED to its caller slot
 *                                                 (`sw a0,0x40(sp)` / `lw a0,0x40(sp)`), and
 *                                                 the `*arg6` temp lands in a0 instead.
 *
 *   That accounts for the 2 missing instructions exactly (`sw s1,0x28` + `lw s1,0x28`, since
 *   goldens `or s0,a0,zero` + `lw a0,0x40(sp)` cancel out against our `sw a0,0x40(sp)`), and
 *   every remaining row is the s0<->s1 rename plus a0<->v1/v0 in the three free calls:
 *       golden  .L750:  bnel a0,zero,.L768 / lw a0,0x3EC(s0)   jal free / nop
 *       live C          bnezl v1,...       / lw v0,0x3EC(a0)   jal free / move a0,v1
 *   Golden puts the FIELD value straight in $a0 (it is the call argument) because $a0 is free;
 *   in live C $a0 is holding the object, so a `move` is needed.  Same source, different colour.
 *
 * IT IS A RANKING TIE, and the arithmetic says so
 *   The two allocations cost the SAME: golden spends 2 instructions saving/restoring $s1 to
 *   avoid the 2-instruction spill of arg0.  Net zero.  There is nothing for a spelling to
 *   push against.
 *
 * SPELLINGS MEASURED -- ALL EXACTLY 116 (dead flat, 20 builds)
 *   arg0 typed s32 / void* / Game6C960Object*;  func_1502FE10 params all-s32 / all-void* /
 *   pointer-typed;  its return typed s32 / void;  `(*arg6)->x` vs `arg6[0]->x`;  error-first
 *   vs success-first if-structure;  free() taking s32 ptr or void ptr;  a copy local
 *   `temp = arg0`;
 *   the allocation result via a local (`obj = allocate_memory(); *arg6 = obj;`);  a local
 *   `obj` reassigned from `*arg6` three times;  `s32 sp3C[2]` instead of a scalar;  and 1, 2
 *   extra declared locals (3 or more grows the frame to 0x48 and scores 117).
 *
 * TWO NEGATIVES THAT KILL THE OBVIOUS THEORIES -- do not re-derive these
 *   (a) REFERENCE COUNT IS NOT THE LEVER.  Giving arg0 a second use (`->field_0x3F6 = arg0`
 *       instead of `= 0`) scores 90 with n=98/99 and arg0 is STILL homed.  A standalone probe
 *       (two calls, then 1/2/3/4 uses of the parameter, plus `register`, plus a copy local)
 *       never once produced `move s0,a0`.  So goldens promotion is not bought with uses.
 *   (b) THE CORPUS HAS NO PRECEDENT.  Mining all 464 objects in conker/expected/build/src for
 *       matched (non-pragma) functions with `or s0,a0,zero` in the first 6 instructions AND at
 *       most one subsequent s0 reference returns exactly TWO functions -- func_15195FF0 and
 *       func_150174C0 -- and BOTH are call-free loop bodies (the parameter is loop-invariant).
 *       There is no matched function anywhere in the tree where a parameter used ONCE, across
 *       calls, as a call argument, is promoted to a callee-saved register.  Either goldens s0
 *       web is bigger than the listing shows, or the promotion is driven by something outside
 *       the source.  Deciding which is the next real step; guessing spellings is not.
 *
 * ONE THING THAT DID MOVE IT, and why it is NOT the answer
 *   Reassigning the PARAMETER as scratch in the error path (`arg0 = (s32)*arg6;` and then
 *   reading the fields through it) merges arg0s web with the object temp and scores 46 with
 *   n = 99/99 -- goldens exact instruction COUNT and the `or sN,a0,zero` prologue.  But it is
 *   wrong: a written-to parameter is homed in the callers slot, so the frame sheds 8 bytes
 *   (0x40 -> 0x38) and every stack offset moves.  It is also a forcer (the reassignment exists
 *   only to change codegen).  Recorded because it PROVES the shape of goldens s0 web -- one
 *   web spanning both the incoming arg0 and the error-path object -- without being shippable.
 *
 * A NOTE ON THE SEMANTICS (this is faithful, not a transcription slip)
 *   The error path frees the pointers that are ZERO, not the ones that are non-zero:
 *   `bnel a0,zero,.L768` skips the free when the pointer is non-null.  That is an inverted
 *   check in the original game.  Both branch polarities were re-read against the listing.
 *
 * NEXT STEP FOR WHOEVER PICKS THIS UP
 *   Do NOT sweep spellings again -- the plateau is measured and flat.  Find the mechanism:
 *   build a minimal standalone probe that reproduces goldens prologue (`sw s0` / `or s0,a0` /
 *   `sw ra` / `sw s1` / `sw a1..a3` to caller slots) and bisect what turns homing into
 *   promotion.  A single positive there closes this function in one build.
 * ===================================================================================== */

#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern s32 *allocate_memory(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

/* The live TUs typedef, with the two byte fields this function writes named.  Offsets and the
 * total size (0x3F8, which is exactly the allocation size) are unchanged. */
typedef struct {
    u8 pad_0[0x45];
    u8 field_0x45;
    u8 pad_46[0x1CF];
    u8 field_0x215;
    u8 pad_216[0x1CA];
    s32 field_0x3E0[2];
    s32 field_0x3E8[2];
    s32 field_0x3F0;
    u8 field_0x3F4;
    u8 field_0x3F5;
    u8 field_0x3F6;
} Game6C960Object;

void func_10004074(s32 *arg0);
void func_1503F5B8(Game6C960Object *arg0, s32 arg1, s32 arg2, f32 arg3, f32 arg4, s32 arg5);
s32 func_1502FE10(s32 arg0, void *arg1, void *arg2, void *arg3, void *arg4, void *arg5, void *arg6);

s32 func_1503F62C(s32 arg0, s32 arg1, void *arg2, void *arg3, void *arg4, void *arg5, Game6C960Object **arg6) {
    s32 sp3C;

    *arg6 = (Game6C960Object *) allocate_memory(0x3F8, 1, 2, 2);
    if (*arg6 == 0) {
        return 1;
    }
    bzero(*arg6, 0x40);
    (*arg6)->field_0x215 = 1;
    (*arg6)->field_0x45 = 1;
    func_1502FE10(arg0, arg2, arg3, arg4, arg5, &(*arg6)->field_0x3F0, &sp3C);
    (*arg6)->field_0x3F4 = sp3C;
    (*arg6)->field_0x3F5 = arg1;
    (*arg6)->field_0x3F6 = 0;
    (*arg6)->field_0x3E8[0] = (s32) allocate_memory(sp3C * 0x40, 1, 2, 2);
    (*arg6)->field_0x3E8[1] = (s32) allocate_memory(sp3C * 0x40, 1, 2, 2);
    if (((*arg6)->field_0x3E8[0] == 0) || ((*arg6)->field_0x3E8[1] == 0)) {
        if ((*arg6)->field_0x3E8[0] == 0) {
            func_10004074((s32 *) (*arg6)->field_0x3E8[0]);
        }
        if ((*arg6)->field_0x3E8[1] == 0) {
            func_10004074((s32 *) (*arg6)->field_0x3E8[1]);
        }
        func_10004074((s32 *) *arg6);
        return 1;
    }
    func_1503F5B8(*arg6, 1, 0, 1.0f, 0.0f, 0);
    return 0;
}
