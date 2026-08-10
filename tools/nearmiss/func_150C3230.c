/* BEST SCORE 235 (of 209 instructions) -- was 250 before this pass.
 *
 * Verified with a freshly-rebuilt object each time (tools/iter_match.sh
 * game_EF410 func_150C3230, and diff.py -o func_150C3230 -s for an isolated
 * per-function diff).  Exactly THREE residual sites remain (9 diff lines):
 *
 *  A. 205 pts -- the 0x1F9/0x1FB selector: the target emits TWO extra words,
 *       1418: b 1428
 *       141c:  andi a1,v0,0xffff     (a delay-slot DUPLICATE of the merge at 1424)
 *     i.e. the end-of-then-block jump survives as its own basic block and its
 *     empty delay slot is filled by copying the merge instruction.  IDO chains
 *     that block away for us (bne points straight at the merge).
 *  B.  30 pts -- uniform +1 t-register rotation in the tail health block
 *     (target t4/t5/t6, ours t3/t4/t5).  The target's allocator consumes one
 *     extra t-pseudo between `sp3C.unk10 = arg0->unk65;` and the
 *     `lbu ...,0x1CA(v1)`; every t-register before that point matches exactly.
 *
 * NEW THIS PASS -- the reloc residual is SOLVED (was 10 pts):
 *   the golden .s names the interior symbol D_800CC028 (== D_800CC2D0 - 0x2A8
 *   == &D_800CC2D0[-1].unk84).  `D_800CC2D0[index-1].unk84.uh` compiles to the
 *   SAME linked bytes but a different .o reloc (imm -680 vs 0), so the object
 *   diff never reaches 0.  Spelling it through the interior symbol -- the
 *   idiom this repo already uses for THIS array in game_182C30.c,
 *   `(&D_800CC37D)[arg0 * 812]` -- makes the object bytes identical.
 *   Reverting to `D_800CC2D0[index - 1].unk84.uh` costs exactly +10.
 *
 * Shapes measured for the selector (all with the D_800CC028 spelling):
 *   this file (default-then-override inside the else)              235
 *   nested ternary  `c?2:(c2?3:1)`                                 240
 *       (right block structure + right delay slot, but the inner
 *        ternary's temp lands in a1 -> extra `move v0,a1`)
 *   plain if / else-if / else chain                                295
 *       (RIGHT instruction count and RIGHT block layout; the only
 *        diff is that `li v0,1` sits in the b's slot instead of the
 *        bne's, and the b's slot gets the andi dup -- a pure
 *        delay-slot-fill choice)
 *   `type = 1;` hoisted above the first test                       815
 *   switch/case (IDO dispatches with beq, not bnel/bne)           1175
 *   `arg0->unk222 = index;` moved after the if-chain               510
 *   explicit empty `else { }` on the inner if     -- no effect (IDO drops it)
 *   whole chain on one physical source line       -- no effect (not -g3 lines)
 *   named local for the lhu value                 -- +8 frame (0x68), 580
 *
 * Levers tried for the t-rotation, none moved it in the +1 direction:
 *   named local for `arg0->unk65` (goes to v0, shifts -1 the WRONG way, 255),
 *   byte-offset pointer spelling of `&D_800CC2D0[unk124-1]` (byte-identical),
 *   statement reordering.  A 4th scalar local is impossible: it moves sp3C
 *   from sp+0x3C to sp+0x40 and grows the frame 0x60 -> 0x68, so the original
 *   has EXACTLY three scalar locals.
 *
 * PERMUTER CANDIDATE: both residuals are register-allocation / delay-slot-fill
 * choices, not logic.  Semantics independently verified.
 */

typedef struct {
    struct127 *unk0;
    f32 unk4[3];
    s32 unk10;
    s32 unk14;
} Struct150C3230;

extern u8 D_800CC028;

void func_15059C84(struct127 *arg0);
void func_1505A770(struct127 *arg0);
void func_1507C324(struct127 *arg0, struct127 *arg1);
void func_1506AC8C(struct127 *arg0, s32 arg1, void *arg2);

void func_150C3230(struct127 *arg0) {
    s32 index;
    s32 type;
    struct127 *target;
    Struct150C3230 sp3C;

    arg0->unkF8 |= 0x4000000;
    if ((arg0->unk222 != 0) && (arg0->unk65 == 0)) {
        arg0->old_x_position = D_800CC2D0[arg0->unk124 - 1].x_position;
        arg0->old_y_position = D_800CC2D0[arg0->unk124 - 1].y_position;
        arg0->old_z_position = D_800CC2D0[arg0->unk124 - 1].z_position;
        arg0->unk222 = 0;
    }

    func_15059C84(arg0);
    func_1505A770(arg0);
    func_15058898(arg0, arg0->old_y_position);
    func_1505B5F8(arg0, arg0->unk180);

    if (arg0->unk28 == 0.0f) {
        arg0->xz_velocity *= 0.5f;
    }

    index = arg0->unk65;
    if (index != 0) {
        arg0->unk222 = index;
        if (*(u16 *)(&D_800CC028 + index * 812) == 0x1F9) {
            type = 2;
        } else {
            type = 1;
            if (*(u16 *)(&D_800CC028 + index * 812) == 0x1FB) {
                type = 3;
            }
        }
    } else {
        type = 0;
    }

    func_1505E650(arg0, type, 0.0f, 0.0f, 0.0f, 0.0f, 0);

    if (arg0->unk65 != 0) {
        func_1507C324(arg0, &D_800CC2D0[arg0->unk65 - 1]);
    }

    if (arg0->unk2E4 != 0) {
        if (arg0->unk65 != 0) {
            target = &D_800CC2D0[arg0->unk65 - 1];
            if (target->interaction_state == 5) {
                arg0->unk65 = 0;
                arg0->unk2E4 = 0;
            }
        } else {
            target = NULL;
        }

        if ((D_800BE616 == 0) && (D_800C35EA == 0) && (arg0->unk65 == 0)) {
            arg0->unk2E4 = 0;
        }

        if (D_800BE9E4 < arg0->unk2E4) {
            arg0->unk2E4 -= D_800BE9E4;
            if (D_800BE616 != 0) {
                func_1508B20C(arg0->x_position, arg0->y_position, arg0->z_position, 900.0f);
            }
        } else {
            sp3C.unk4[0] = arg0->x_position;
            sp3C.unk4[1] = arg0->y_position;
            sp3C.unk4[2] = arg0->z_position;
            sp3C.unk0 = &D_800CC2D0[arg0->unk124 - 1];
            sp3C.unk10 = arg0->unk65;
            if (target != NULL) {
                target->stunned = 0;
                target->immune = 0;
                if (target->health != 0) {
                    target->health = 1;
                }
            }
            func_1506AC8C(arg0, (D_800BE616 != 0) ? 0xB : 0xE, &sp3C);
            func_15060F28(arg0, 1);
        }
    }
}
