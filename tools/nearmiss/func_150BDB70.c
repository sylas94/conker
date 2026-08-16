/* func_150BDB70  (game_EB020, 800 bytes)  --  PARKED at 3335 / 19900.
 *
 * WHAT IS RIGHT: every instruction is present and in the right order; the frame (0x60),
 * every local slot (sp5C/sp58/sp54/sp50 for the four mode constants, sp38 for the record
 * spill), every field offset, every constant, both float pools, and both call sequences
 * reproduce.  What is left is ONE codegen decision plus its register-colouring cascade.
 *
 * THE BLOCKER -- IDO strength-reduces the scan loop and golden does not.
 *   golden : "slti at, v0, 0x19" at FIVE sites plus a rotated inner skip-loop
 *            (.L150BDD94 tests the bit, .L150BDDB0 is a second copy of the same test used
 *            for subsequent skips).  Loop-invariant registers: v1=mask, a1=0xFF,
 *            a2=&D_800CC2D0, a3=0x32C  -- FOUR.
 *   ours   : IDO proves the trip count and rewrites "i < 0x19" into "i != 0x19", hoisting
 *            0x19 into a1 ("bnel t0,a1,..").  That single-instruction bottom test removes
 *            the reason to rotate the skip path, so the inner loop never appears and we come
 *            out 12 instructions short.  FIVE loop-invariant registers, so the whole
 *            colouring below rotates and drags ~40 rows of pure register renames with it.
 *
 * SPELLINGS TRIED (score):
 *   for + "continue" on the bit test ................. 3405
 *   for + body nested inside "if (bit != 0)" ......... 3405   (IDO normalises the two)
 *   for with "i <= 0x18" instead of "i < 0x19" ....... 3405   (same comparison node)
 *   while + explicit "i++; continue;" at each skip ... 5720   (worse: 7 increment sites)
 *   first mask test inlined instead of via "mask" .... 3335   (kept; -70)
 * Score does not move across genuinely different honest spellings => allocator/strength-
 * reduction ranking tie, i.e. the documented BAIL SIGNATURE.  Not faked.
 *
 * WHAT WOULD UNBLOCK IT: something in the original source that stops IDO proving the trip
 * count.  Every construct that does so honestly (a variable bound, a non-unit step, a
 * second reaching definition of i) changes other instructions, so it needs a real find,
 * not a spelling shuffle.  Compare game_EEB10/func_150C16C0, where the mirror-image effect
 * (a constant divisor that KEEPS its div-by-zero trap because IDO hoists it into a
 * callee-saved register rather than folding it) turned out to be reproducible for free.
 *
 * HEADER INACCURACIES FOUND (worked around file-locally, headers untouched):
 *   - structs.h "struct126" has no members at 0x24 / 0x16C / 0x170 / 0x197; they land inside
 *     pad129[0x6C] and pad196[0x2].  Rec150BDB70 below is the accurate view.
 *   - struct127 0x66 is "pad66" and 0x2FC is "pad2FC[0x3]"; both are real fields
 *     (0x66 is a bitfield whose bit 5 this function clears/sets, 0x2FC a camera-id bitmask).
 *
 * DECODE NOTES worth keeping:
 *   - "arg0->unk2E4 -= arg0->unk2E4 >> 3" is an ARITHMETIC shift with no rounding fixup, so
 *     unk2E4 is signed and the source really is "x -= x >> 3", not "x -= x / 8".
 *   - 0x43B40000 in the wrap is 360.0f (not 10.0f -- 0x41200000 appears twice right after it
 *     and is easy to misattribute):
 *         if (180.0f < t) t -= 360.0f;   unk2E4 = t * 10.0f;
 *   - the record index is biased by 100: the +0xFFFEC2D0 addend is exactly -100 * 0x32C.
 *   - func_15052F9C/func_1505327C take their f32 args in GPRs (o32: arg0 is a pointer, so
 *     no later float argument is eligible for $f12/$f14).
 */

#include <ultra64.h>
#include "functions.h"
#include "variables.h"

/* structs.h models struct127::unk31C as `struct126 *`, but struct126 has no members at
 * 0x24/0x16C/0x170/0x197 (they fall inside pad129[0x6C] / pad196[0x2]).  Per project policy
 * the shared header is left alone and an accurate view is made file-local. */
typedef struct {
    u8  pad0[0x24];
    s16 unk24;
    u8  pad26[0x16C - 0x26];
    f32 unk16C;
    f32 unk170;
    u8  pad174[0x197 - 0x174];
    u8  unk197;
    u8  pad198[0x19B - 0x198];
    u8  unk19B;
    u8  pad19C[0x19E - 0x19C];
    u16 unk19E;
} Rec150BDB70;

extern f32 D_8009FFF0;
extern void func_15052590(struct127 *arg0);
extern void func_15052F9C(struct127 *arg0, f32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9);
extern void func_1505327C(struct127 *arg0, f32 arg1, f32 arg2, s32 arg3, s32 arg4);

void func_150BDB70(struct127 *arg0) {
    s32 sp5C;
    s32 sp58;
    s32 sp54;
    s32 sp50;
    s32 mask;
    s32 i;
    struct127 *rec;
    s32 ang;
    f32 temp;

    if (arg0->id == 0x23) {
        sp5C = 0xA;
        sp58 = 0xB;
        sp54 = 0xC;
        sp50 = 1;
    } else {
        sp5C = 1;
        sp58 = 2;
        sp54 = 3;
        sp50 = 3;
    }

    arg0->unk2E8 = 0;
    arg0->pad2FC[0] = 0;
    arg0->unk2E4 -= arg0->unk2E4 >> 3;
    if (D_800BE616 != 0) {
        arg0->pad66 &= ~0x20;
    }
    if (arg0->unk13C != 0) {
        rec = &D_800CC2D0[arg0->unk13C - 100];
        if (rec->camera != NULL) {
            arg0->pad2FC[0] = 1 << rec->camera->unk23D;
        }
        if (rec->unk31C != NULL) {
            if (((Rec150BDB70 *)rec->unk31C)->unk197 != 0) {
                ang = ((Rec150BDB70 *)rec->unk31C)->unk16C * D_8009FFF0;
                arg0->unk7A = ang;
                arg0->unk76 = ang;
                temp = ((Rec150BDB70 *)rec->unk31C)->unk170;
                if (180.0f < temp) {
                    temp -= 360.0f;
                }
                arg0->unk2E8 = 1;
                arg0->pad66 |= 0x20;
                arg0->unk2E4 = temp * 10.0f;
            }
        }
    }
    func_15052590(arg0);

    if (arg0->unk232 == sp58) {
        func_15052F9C(arg0, 100.0f, sp50, 4, 0, sp54, 0, 0, 0, 0);
        return;
    }
    if (arg0->unk232 != sp5C) {
        return;
    }
    if ((~D_800D18A0 & D_800CC268) == 0) {
        return;
    }
    if (func_15072208(arg0, 0) != NULL) {
        return;
    }
    mask = ~D_800D18A0 & D_800CC268;
    for (i = 0; i < 0x19; i++) {
        if (((1 << i) & mask) != 0) {
            rec = &D_800CC2D0[i];
            if (rec->unk127 == 0xFF) {
                continue;
            }
            if (rec->unk65 != 0) {
                continue;
            }
            if (((Rec150BDB70 *)rec->unk31C)->unk19B != 0) {
                continue;
            }
            if (((Rec150BDB70 *)rec->unk31C)->unk197 != 0) {
                continue;
            }
            if (rec->unk13C != 0) {
                continue;
            }
            arg0->unk124 = i;
            func_1505327C(arg0, 44.0f, 3.2f, sp58, sp50);
            ((Rec150BDB70 *)rec->unk31C)->unk24 = 0x258;
            ((Rec150BDB70 *)rec->unk31C)->unk19E = 0;
            return;
        }
    }
}
