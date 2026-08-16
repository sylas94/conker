/* func_150B67E0  (game_E3C90, 992 bytes)  --  PARKED at 290 / 24600.
 *
 * EVERY INSTRUCTION IS CORRECT.  Frame (0x30), all branch targets, all constants, both
 * float-pool references and every schedule slot reproduce.  The entire residual is ONE
 * register choice and its rotation cascade:
 *
 *     golden : lui $t8,%hi(D_80088710) / lw $t8,%lo(..)($t8) / beq $t8,$at / andi $t9,$t8,0xFFF
 *     ours   : lui $v0,%hi(D_80088710) / lw $v0,%lo(..)($v0) / beq $v0,$at / andi $t8,$v0,0xFFF
 *
 * Golden spends a rotation temp ($t8) on that load; we get $v0 instead, so every temp from
 * there to the end of the function is one step behind ($t9->$t8, $t0->$t9, $t1->$t0,
 * $t4->$t3, $t2->$t1, $t3->$t2, $t5->$t4, $t6->$t5, $t7->$t6, $t9->$t8).  Sixteen rows,
 * all pure renames, no instruction added, removed or moved.
 *
 * SPELLINGS TRIED, ALL 290:
 *   - `if (D_80088710 != 0x3E7)` vs `if (0x3E7 != D_80088710)`  (operand-order lever)
 *   - reading the global into a named local first
 *   - hoisting the opening func_1509BE40 call into a named local (permuter's `new_var`)
 *   - `extern u32 D_80088710` instead of `extern s32`
 *   - a file-local UNPROTOTYPED `void func_1509BFB0();` shadowing the header's variadic
 *     declaration (needs the #define rename trick; compiles, changes nothing)
 * That is the documented BAIL SIGNATURE: several genuinely different honest spellings, no
 * movement.
 *
 * PERMUTER: set up and run (selftest PASS, base 290, TU-context confirmed irrelevant here).
 * Best find 145, and it gets there ONLY by writing
 *     func_1509BFB0(5, 0x4000, 4, 2, 0, (unsigned short)(D_80088710 & 0xFFF), 0, 0);
 * i.e. a cast that is semantically a no-op (the value is already masked to 12 bits) and
 * emits no instruction -- it only re-types the expression node and so nudges the rotation.
 * NOT TAKEN: that is exactly the banned no-op cast.  The cookbook's advice on a no-op-looking
 * cast is to go find the REAL type it is standing in for; func_1509BFB0 is variadic (this
 * function alone calls it with 3, 4, 5 and 8 arguments), so the argument undergoes default
 * promotion and there is no narrower declared parameter type to recover.
 *
 * THE TYPE-RECOVERY QUESTION IS NOW SETTLED, AND THE ANSWER IS "THERE IS NO NARROWER TYPE".
 * (2026-08-16.)  Read the callee, asm/nonmatchings/game_C8950/func_1509BFB0.s: it walks its
 * own va_list by hand --
 *       addiu $v1,$v1,3 ; and $v1,$v1,$a0(=-4) ; lw $t4,0($v1) ; sw $t4,...
 * -- i.e. EVERY variadic argument is 4-byte aligned and read with `lw`, a full 32-bit word,
 * and copied verbatim into the D_800D2F60 command buffer.  There is no `lhu`/`lbu` anywhere
 * in the vararg loop, and the only narrowing the callee does is on its own FIRST fixed
 * parameter (`andi $a3,0xFFF` / `andi ...,0xF000` on the id).  So the 6th argument's real
 * type is `int` after default promotion; `(unsigned short)` re-types the node and emits no
 * instruction, which is the definition of the banned forcer.  The proposed unlock DOES NOT
 * EXIST -- this is not a type-recovery problem after all.
 *
 * TWO FURTHER HONEST SPELLINGS TRIED (2026-08-16), BOTH 290:
 *   - moving `extern s32 D_80088710;` ahead of the two f32 externs (declaration order is
 *     load-bearing for IDO's temp rotation, so this was a real lever, not a cosmetic edit)
 *   - `extern u32 D_80088710;` with `track % 0x1000` in place of `& 0xFFF` (a genuinely
 *     different node kind -- MOD, not AND -- that still lowers to the same `andi`)
 * That makes EIGHT genuinely different honest spellings pinned at exactly 290.  Confirmed
 * BAIL: allocator tie, park it.
 *
 * DIAGNOSIS OF THE ONE ROW, for whoever picks this up.  Golden puts the D_80088710 load in
 * $t8 (a rotation temp); we put it in $v0.  $v0/$v1 are IDO's CSE/expression registers -- a
 * value that IDO treats as a common subexpression lands there instead of in the $t rotation,
 * and that is why our rotation is one step behind from that point on.  (The same mechanism,
 * running the other way, is visible in game_EE710/func_150C1260: there GOLDEN uses the CSE
 * register $v1 and we coalesce into $a0.)  To close this you must make IDO stop treating the
 * load as a CSE temp; reading it into a named local does NOT do that (measured).
 *
 * WHAT DID MOVE THE SCORE (keep): 590 -> 290 by putting the two `arg0->unk84` read-modify-
 * writes BEFORE `arg0->unk1B4 = 3` -- golden gives the 0x84 load the first rotation temp,
 * so that statement is first in the original despite the scheduler hoisting the `sh` above
 * the `or`.
 *
 * DECODE NOTES: 0x43E10000 = 450.0f, 0x43070000 = 135.0f; D_8009FCF0 and D_8009FCF4 are two
 * SEPARATE pool entries both holding 650.0f, so the source really does reference the constant
 * twice and IDO did not dedupe them; unk36C is already `u16 *` in structs.h; the tail
 * (`temp1`/`temp2` pair, the `|= 0x100` / `&= ~0x100` fork and the 0x200A gamepad probe) is
 * the same idiom as game_118670/func_150EB1C0 and game_EBD00/func_150BE850 (CLOSED).
 */

#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern f32 D_8009FCF0;
extern f32 D_8009FCF4;
extern s32 D_80088710;

s32 func_1509BE40();
void func_1509BFB0(s32 num, s32, s32, ...);
void func_151254F4(struct108 *arg0, s32 arg1);
void func_15124B18(struct108 *arg0);

void func_150B67E0(struct108 *arg0) {
    s32 temp0;
    s32 i;
    s32 temp1;
    s32 temp2;

    temp0 = func_1509BE40(0, 0x503C, 0x1A);
    if (temp0 == 0) {
        if (func_15123934(arg0, arg0->unk2C, 0, 0, 0) != 0) {
            arg0->unk84 |= 0x20000;
            arg0->unk84 &= ~4;
            arg0->unk1B4 = 3;
            func_15124B18(arg0);
            arg0->unk23C = 1;
        }
        arg0->unk374 = D_8009FCF0;
        arg0->unk348 = 450.0f;
        arg0->unk34C = 450.0f;
    } else {
        func_1509BFB0(0, 0x4000, 0);
        if (arg0->unk2C == 1) {
            if (func_151239CC(arg0, 0) != 0) {
                arg0->unk1B4 = 2;
                func_15124B18(arg0);
            }
        }
        if (func_1509BE40(1, 0x4024, 6, 0x2000) != 0) {
            D_80088710 = 0x9003;
        } else if (func_1509BE40(1, 0x4025, 6, 0x2000) != 0) {
            D_80088710 = 0x9009;
        } else if (func_1509BE40(1, 0x4026, 6, 0x2000) != 0) {
            D_80088710 = 0x900A;
        } else if (func_1509BE40(1, 0x4027, 6, 0x2000) != 0) {
            D_80088710 = 0x900B;
        }
        if (D_80088710 != 0x3E7) {
            func_1509BFB0(5, 0x4000, 4, 2, 0, D_80088710 & 0xFFF, 0, 0);
        }
        for (i = 0; i < 3; i++) {
            if ((func_1509BE40(1, i + 0x400C, 6, 0x2000) != 0) ||
                (func_1509BE40(1, 0x4014, 6, 0x2000) != 0)) {
                func_1509BFB0(1, 0x2000, 0x3B, 2);
            }
        }
        if (func_1509BE40(1, 0x4000, 6, 0x2000) != 0) {
            func_1509BFB0(2, 0x9000, 6, 1, 0x80000);
            func_1509BFB0(1, 0x9000, 0x10, 0x55);
        } else {
            func_1509BFB0(2, 0x9000, 6, 0, 0x80000);
            func_1509BFB0(1, 0x9000, 0x10, 0);
        }
    }
    temp1 = func_1509BE40(0, func_1509BE40(0, 0x200A, 0xB7) | 0x2000, 0xBC);
    temp2 = func_1509BE40(0, 0x2000, 0xBB);
    if ((temp1 != 0) && (temp2 != -1)) {
        arg0->unk5F0 |= 0x100;
    } else {
        arg0->unk5F0 &= ~0x100;
    }
    if ((temp1 != 0) && (temp2 != -1)) {
        if (func_15123934(arg0, arg0->unk2C, 0, 0, 3) != 0) {
            arg0->unk84 |= 0x100002;
            arg0->unk674 = 0.0f;
            func_151254F4(arg0, arg0->unk3D0->unk65 - 1);
            arg0->unk134 = 0;
        }
        arg0->unk348 = (arg0->unk34C = 450.0f);
        arg0->unk374 = D_8009FCF4;
        if ((*arg0->unk36C & 4) != 0) {
            arg0->unk190 = 0.0f;
        } else {
            arg0->unk190 = 135.0f;
        }
    } else {
        if (func_151239CC(arg0, 3) != 0) {
            func_151254F4(arg0, arg0->unk23D);
            arg0->unk674 = 0.0f;
            arg0->unk190 = 0.0f;
        }
    }
}
