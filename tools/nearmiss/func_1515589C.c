/* func_1515589C  (game_182C30.c, 1120 B)  --  COLD DECOMPILE THIS WAVE
 * BOUNDED SCORE (--max-lines 280 == 1120/4, the symbol's own instruction count):
 *      9459 (build 1)  ->  400  in 10 builds.  Same 400 with -R and without.
 * NOT SHIPPED unless the header of this file says otherwise: restore the
 * #pragma in conker/src/game_182C30.c and prove
 *   `git status --short -- conker/src/game_182C30.c` prints NOTHING.
 *
 * =====================  WHAT IS LEFT: EXACTLY 2 INSTRUCTIONS  =================
 * Symbol size 1112 vs golden 1120.  EVERY instruction and EVERY REGISTER in the
 * whole 280-instruction function is identical except this one tail, at the end
 * of case 1's `arg0->field_0x14 != 0` arm:
 *
 *    golden                             mine
 *    3b4 lwc1 $f4,0x1c(t0)              3b4 lwc1 $f4,0x1c(t0)
 *    3b8 lw   t1,0x14(s0)               3b8 lw   t1,0x14(s0)
 *    3bc trunc.w.s $f8,$f4              3bc trunc.w.s $f8,$f4
 *    3c0 mfc1 t9,$f8                    3c0 mfc1 t9,$f8
 *    3c4 nop                            3c4 b    <.L15155CE8>
 *    3c8 sh   t9,0x12(t1)               3c8  sh  t9,0x12(t1)   <- in the slot
 *    3cc b    <.L15155CEC>
 *    3d0  lw  ra,0x34(sp)
 *
 * i.e. as1 filled the `b`'s delay slot from the PRECEDING instruction (`sh`) and
 * reused the mfc1 hazard slot for the branch; golden instead left the hazard nop
 * and filled the delay slot FROM THE TARGET (`lw ra`, retargeting +4).
 * RESIDUAL CLASS: as1 delay-slot-source choice, 1 site.
 * NOTE the SAME source shape in case 3 (lines 148-151 here) comes out EXACTLY
 * like golden (`b` + `sh` in the slot, no nop) -- golden itself uses the
 * steal-the-preceding form there.  So golden is INCONSISTENT between two
 * near-identical blocks, which means as1 saw different input for the two.
 * MEASURED DEAD for this: `return;` instead of `break;` at the end of that arm
 * (with the else flattened to a fall-through) -- byte-identical, still 400.
 *
 * ============================  THE FOUR LEVERS THAT PAID  ====================
 * (each one is a general law, worth banking)
 *
 * 1. **`x * 812` STRENGTH-REDUCES ONLY WHEN THE MULTIPLICAND IS A LOCAL.**
 *    `arg0->field_0x10 * 812` (a u8 MEMORY LOAD) emits `li t0,0x32c; multu; mflo`.
 *    `i * 812` with `s32 i = arg0->field_0x10;` emits golden's 9-instruction
 *    sll/subu/addu chain (4x-x, *4+x, *4-x, *4-x, *4).  The integer promotion is
 *    identical in C; IDO's reducer just refuses on a load operand.
 *    Cross-checked against the ALREADY-MATCHED func_151557FC in the same TU,
 *    which uses `(&D_800CC37D)[arg0 * 812]` on an s32 parameter and does emit
 *    the chain.  9459 -> 7170.
 *
 * 2. **TWO SPELLINGS OF THE SAME ADDRESS KEEP A POINTER LOCAL ALIVE.**  Golden
 *    computes `obj` ONCE before the switch (`addu t0,a3,t6`, spilled to its own
 *    home 0x48 across both calls) and then RE-COMPUTES the identical
 *    `a3 + 812*i` four more times for the `.unk31C` loads.  If both are written
 *    the same way IDO unifies them, deletes the entry computation and
 *    rematerialises `obj` in every arm (score 6370, frame 0x58, and `a3` stops
 *    being hoisted).  The fix is to spell them DIFFERENTLY:
 *        #define OBJEXPR (&D_800CC2D0[arg0->field_0x10])   <- the raw field
 *        #define U31C    (D_800CC2D0[i].unk31C)            <- the s32 local
 *    Both still emit the shift chain (the `obj` one via the CSE'd load in a2),
 *    but they are different ucode trees so neither is eliminated.
 *    6370 -> 1960 AND the frame snapped to golden's 0x50 in the same build.
 *    MEASURED: making them differ any OTHER way (byte-pointer cast on either
 *    side, `D_800CC2D0 + i`, `*(T**)((u8*)D_800CC2D0 + i*812 + 0x31C)`) is
 *    strictly worse -- all four spellings scored 8740 with frame 0x60.
 *
 * 3. **`id = (p != NULL) ? p->f : 0;` NOT `id = 0; if (p) id = p->f;`**
 *    The ternary is what produces golden's `move v0,zero / beqz / nop /
 *    b <next> / lbu` (the redundant `b` to the fall-through label is the
 *    signature of the ternary's empty join block); the if-form produced
 *    `beqzl` + a duplicated `andi`.  6370 -> 2405 on its own; combined with
 *    lever 2 -> 1460.
 *
 * 4. **SPLIT `t = a->f - GLOBAL;` INTO TWO STATEMENTS.**   1460 -> 400.
 *        t = arg0->field_0xE;
 *        t -= D_800BE9E4;
 *    One statement gives `lw <global> ; lh <field> ; subu v0,tX,tY`.
 *    Two statements give golden's `lh v0,0xe(s0) ; lw t7,0(v1) ; subu v0,v0,t7`
 *    -- the field load goes straight into the RESULT register and the operand
 *    order follows source order.  This one edit fixed BOTH case 1 and case 3.
 *
 * ============================  FRAME DECODE (quote)  =========================
 * framesize 0x50.  arg-build [0x00,0x28) (func_1515D5F8 takes 10 args, highest
 * slot sp+0x24), saved regs s0@0x30 ra@0x34, LOCALS = [0x38,0x50) = 0x18,
 * temp area = 0, TOP-DOWN in declaration order:
 *      i      0x4C
 *      obj    0x48   <- golden spills it HERE: `sw t0,0x48(sp)` around both
 *                       func_15048A40 calls.  A DECLARED POINTER SPILLS TO ITS
 *                       OWN HOME (confirms obj is the 2nd declared local).
 *      o2     0x44
 *      id     0x40
 *      t      0x3C
 *      extra  0x38   <- golden spills it HERE: `swc1 $f2,0x38(sp)`.
 * sum = 6*4 = 0x18 EXACT, and 0x30 + 0x8 + 0 + 0x18 = 0x50.
 * Both spill destinations are predicted by the declaration order above, which is
 * how the order was derived BEFORE any build confirmed it.
 *
 * ==========================  CALLEE / TYPE DECISIONS  ========================
 *  func_15048A40  -- functions.h says `void`; it returns f32.  FILE-LOCAL SHADOW
 *                    added at the top of the TU (same idiom as game_10B7D0.c,
 *                    game_142560.c, game_19A8B0.c, game_1AC2F0.c).
 *  func_1515F10C  -- golden calls it here with ONE argument (`or a0,a1,zero` and
 *                    NOTHING sets a1), but the already-matched func_15155EF8 in
 *                    the same TU calls it with TWO.  Resolved by replacing the
 *                    file's prototype with a K&R declaration `void func_1515F10C();`
 *                    so each call site passes what it writes.  func_15155EF8 was
 *                    re-verified BYTE-IDENTICAL afterwards (see below).
 *  func_1515D5F8  -- 10 x s32, copied from game_179F30.c:93.
 *  func_10010F30  -- functions.h (s32,u16,u8,s16,u8) works unchanged.
 *  struct127      -- x/y/z_position @0x14/18/1C, in_water @0xAD, unk31C @0x31C,
 *                    sizeof 0x32C; D_800CC2D0 is `struct127[26]` in variables.h.
 *  struct226      -- unkE/unk10/unk12 s16 @0xE/0x10/0x12; arg0->field_0x14 is
 *                    declared s32 in the TU's struct LL155FD4 and cast at use.
 *  Obj182C30      -- file-local shadow for D_800CC2D0[].unk31C's target; needed
 *                    .unk75 and .unk197, and structs.h's struct126 has 0x196/0x197
 *                    as padding.  NO SHARED HEADER WAS EDITED.
 *  struct LL155FD4 -- only change: `u8 pad_0x12[0x2]` split into
 *                    `u8 field_0x12; u8 pad_0x13;`.  Padding only, no layout change.
 *
 * ================  TU RE-VERIFICATION (mandatory, quoted) ===================
 * Per-symbol raw byte compare of build/src/game_182C30.c.o vs
 * expected/build/src/game_182C30.c.o (readelf st_value/st_size, .text bytes):
 *      func_15155780    IDENTICAL (124 B)
 *      func_151557FC    IDENTICAL (160 B)
 *      func_1515589C    SIZE 1112 vs golden 1120     <- the 2 instructions above
 *      func_15155CFC    IDENTICAL (508 B)
 *      func_15155EF8    IDENTICAL (68 B)     <- the K&R func_1515F10C decl is safe
 *      func_15155F3C    IDENTICAL (84 B)
 *      func_15155F90    IDENTICAL (68 B)
 *      func_15155FD4    IDENTICAL (84 B)
 *      func_15156028    IDENTICAL (360 B)
 * Sections: .rodata IDENTICAL, .data IDENTICAL, .text differs only by this fn.
 *
 * =========================  MEASURED VARIANT LOG  ===========================
 *   9459  build 1: &D_800CC2D0[u8 field] everywhere              (multu)
 *   9459  build 2: (u8*)D_800CC2D0 + u8field*812  (identical codegen; the
 *                  -g3 source-line column moved, which is how the build was
 *                  proven real rather than a no-op harness read)
 *   7170  build 3: + `s32 i` local                               (shift chain)
 *   6370  build 4: + case 3 written `if (t <= 0) {...} else {...}` (golden puts
 *                  the SMALL arm first: `bgtzl` to the big arm)
 *   8740  build 5: obj and .unk31C spelled differently via a byte-pointer cast
 *   -- sweep 1 (6 spellings, control fired 6370 vs 8740):
 *        baseA      6370  frame 0x58   (&D_800CC2D0[i]) / (D_800CC2D0[i].unk31C)
 *        CTRLmix    8740  frame 0x60
 *        bytecur    8740  frame 0x60
 *        ptradd     8740  frame 0x60
 *        u31craw    8740  frame 0x60
 *        objfld     6370  frame 0x58   (&D_800CC2D0[i].interaction_state)
 *   -- sweep 2 (structural):
 *        base       6370  frame 0x58
 *        noextra    8143  frame 0x60   (extra as an inline ternary -> WORSE;
 *                                       extra IS a declared local, 6th)
 *        objraw     1960  frame 0x50   <- WIN (lever 2)
 *        u31craw2  12575  frame 0x58   (the mirror image: much worse)
 *        noo2       6362  frame 0x58   (dropping the o2 local: no help)
 *        idtern     2405  frame 0x58   <- WIN (lever 3)
 *   1960  objraw
 *   1460  objraw + idtern
 *    400  + split subtraction (lever 4)
 *    400  + `return;` instead of `break;` in case 1's then-arm  (NO CHANGE)
 *
 * =====================  NEXT THINGS TO TRY, IN ORDER  =======================
 * 1. The residual is a single as1 delay-slot-source choice.  Because the
 *    instruction stream is byte-identical up to that point, as1 must be seeing
 *    a different INPUT there -- most likely an extra (later-deleted) label or
 *    basic-block boundary between the `sh` and the `b`.  Look for a C shape that
 *    makes IDO end that arm with a block boundary: a construct whose join block
 *    is empty.  Case 3's identical arm does NOT have it, so whatever it is, it
 *    is present in case 1 and absent in case 3 -- the ONLY structural asymmetry
 *    between them is that case 1's arm is at switch-body top level while case
 *    3's is nested inside `else` of the timer test.  Try wrapping case 1's body
 *    in the same `if (t <= 0) {...} else {...}` nesting shape as case 3
 *    (semantically: hoist the `arg0->field_0xE = t;` assignment into both arms).
 * 2. Feed it to the TU-aware permuter (permuter_tu.sh) with
 *    PERMUTER_TU_REQUIRE_FRAME / _REQUIRE_OFFSETS gates -- the base already has
 *    golden's exact frame AND every register, so the search space is tiny.
 */

/* ---- BEST MEASURED VERSION (400).  Paste over the pragma in game_182C30.c ----
 *
 * At the TOP of the TU (replacing the plain `#include "functions.h"`):
 *     #include <ultra64.h>
 *     #define func_15048A40 func_15048A40_void_decl_in_functions_h
 *     #include "functions.h"
 *     #undef func_15048A40
 *     extern f32 func_15048A40(u8 arg0);
 *     #include "variables.h"
 *
 * In `struct LL155FD4`, replace `u8 pad_0x12[0x2];` with:
 *     u8 field_0x12;
 *     u8 pad_0x13;
 *
 * After the struct, add:
 *     typedef struct {
 *         u8 pad0[0x75];
 *         u8 unk75;
 *         u8 pad76[0x121];
 *         u8 unk197;
 *     } Obj182C30;
 *
 *     #define OBJEXPR (&D_800CC2D0[arg0->field_0x10])
 *     #define U31C (D_800CC2D0[i].unk31C)
 *
 * DELETE the line `void func_1515F10C(struct226 *arg0, struct225 *arg1);` that
 * sits below the pragma and put these two immediately ABOVE func_1515589C:
 *     void func_1515F10C();
 *     s32 func_1515D5F8(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
 */

void func_1515589C(struct LL155FD4 *arg0) {
    s32 i;
    struct127 *obj;
    Obj182C30 *o2;
    s32 id;
    s32 t;
    f32 extra;

    i = arg0->field_0x10;
    obj = OBJEXPR;
    switch (arg0->field_0x11) {
    case 0:
        o2 = (Obj182C30 *)U31C;
        id = (o2 != NULL) ? o2->unk75 : 0;
        if ((!(id & 0x80)) && (id != 0x2A) && (id != 0x2B) && (!((id == 0x42) && (D_800D2E68 & 4))) &&
            (id != 0x2C) && (o2->unk197 == 0) && (id != 0) && (id != 0x1F) && (obj->in_water == 0)) {
            arg0->field_0x11 = 1;
            arg0->field_0xE = 0x78;
            func_10010F30(0x1EB, 0x7FFF, 0x40, 0, 0);
            return;
        }
        if (arg0->field_0x14 != 0) {
            func_1515F10C(arg0->field_0x14);
            arg0->field_0x14 = 0;
        }
        break;
    case 1:
        t = arg0->field_0xE;
        t -= D_800BE9E4;
        if ((t <= 0) || (((Obj182C30 *)U31C)->unk75 == 0)) {
            arg0->field_0x11 = 2;
            t = 0;
        }
        arg0->field_0xE = t;
        arg0->field_0x12 += D_800BE9E4 * 2;
        if (arg0->field_0x14 != 0) {
            if (((Obj182C30 *)U31C)->unk75 == 5) {
                extra = 85.0f;
            } else {
                extra = 0.0f;
            }
            ((struct226 *)arg0->field_0x14)->unkE = (s16)(s32)obj->x_position;
            ((struct226 *)arg0->field_0x14)->unk10 =
                (s16)(s32)((func_15048A40(arg0->field_0x12) * 15.0f) +
                           (obj->y_position + 160.0f + arg0->field_0x98 + extra));
            ((struct226 *)arg0->field_0x14)->unk12 = (s16)(s32)obj->z_position;
        } else {
            arg0->field_0x14 = func_1515D5F8(0, 0, 0, 2, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0);
        }
        break;
    case 2:
        if (((Obj182C30 *)U31C)->unk75 == 0) {
            arg0->field_0x11 = 0;
        }
        if (arg0->field_0x14 != 0) {
            func_1515F10C(arg0->field_0x14);
            arg0->field_0x14 = 0;
        }
        break;
    case 3:
        t = arg0->field_0xE;
        t -= D_800BE9E4;
        if (t <= 0) {
            arg0->field_0x11 = 2;
            arg0->field_0xE = 0;
        } else {
            arg0->field_0xE = t;
            arg0->field_0x12 += D_800BE9E4 * 2;
            if (arg0->field_0x14 != 0) {
                ((struct226 *)arg0->field_0x14)->unkE = (s16)(s32)obj->x_position;
                ((struct226 *)arg0->field_0x14)->unk10 =
                    (s16)(s32)((func_15048A40(arg0->field_0x12) * 15.0f) + (obj->y_position + 160.0f));
                ((struct226 *)arg0->field_0x14)->unk12 = (s16)(s32)obj->z_position;
            } else {
                arg0->field_0x14 = func_1515D5F8(0, 0, 0, 2, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0);
            }
        }
        break;
    }
}
