/* CLOSED -- game_3F1F0 / func_15011D60  (448 B).  fastscore mism=0, n=112/112, frame=-216.
 * verify_match.sh: ALL CHECKS PASSED (.text IDENTICAL, .text section size 0x1E0 both sides,
 * both TU symbols score 0 with and without -R).  relcheck.py: PASS -- 112/112 instructions,
 * 102 unrelocated words byte-equal to the ROM, all 10 relocated fields compose to the ROM's
 * bytes, 0 unpaired HI16.  This source is LIVE in conker/src/game_3F1F0.c.
 *
 * WHAT CLOSED IT: THE BLOCK-SCOPE LAW.  The parked candidate was 14 rows off (the old header
 * said 44; that was the pre-fix fastscore, and its "phantom 30 trailing-pad" story was wrong --
 * the length was always exact at 112/112).  All 14 rows were one permutation of the post-loop
 * basic block: golden emitted  mtc1 | sh 0xC8 | li t7,3 | swc1 x4 | lbu 0x90 | ...  while we
 * emitted  mtc1 | lbu 0x90 | li t7,3 | li t8,0x15 | lui | sh 0xC8 | ... | swc1 x4.  Same DAG,
 * same registers, same count.
 *
 * The whole fix is ONE PAIR OF BRACES.  Putting the for loop AND the five trailing zero stores
 * inside a block that carries a block-scope declaration flips IDO's list scheduler:
 *   - the four `swc1 $f0` stop sinking to the bottom of the block (they are dead ends, so a
 *     height-ranked scheduler puts them last -- which is what we were getting), and
 *   - `lbu 0x90(sp)` stops being hoisted above them.
 * That is the same mechanism as the recorded law: a block-scope declaration mints an allocator
 * web, and the web changes scheduling, not just colouring.  No new variable is invented here --
 * only the SCOPE of the existing loop counter `i` changes, so the variable set is byte-for-byte
 * the same as the parked candidate's.
 *
 * MEASURED BOUNDARY OF THE LAW (all with the fixed fastscore, in-TU):
 *   block must contain the loop AND all five zero stores  -> 0
 *   block contains the loop only                          -> 9
 *   block contains loop + `tmp.unk3C = 0` but not the floats -> 8
 *   block contains only the five zero stores (no loop)     -> 2   (li t7,3 / sh 0xC8 swap)
 *   `tmp.unk3C = 0` before the block instead of inside     -> 6..23
 *   block also swallows the three obj stores               -> 15
 *   no block at all (parked candidate)                     -> 14
 * The DECLARATION ITSELF is a ranking tie: `u8 i` (below), a loop temp `s32 v`/`u8 k` used in
 * the body, or an `f32 z = 0.0f` used for the four zeros all score 0, as does putting
 * `tmp.unk3C = 0` last inside the block instead of first.  An UNUSED declaration in the block
 * also scores 0 -- that spelling is rejected on the standing rule that an unused local has no
 * live range and is provably unnameable.  `u8 i` is chosen because it invents nothing.
 * Frame stays 0xD8 either way: the scalar area rounds 6 -> 8 bytes with `i` and 5 -> 8 without.
 *
 * STILL TRUE FROM THE PARK (do not re-derive): the search-key local is 0x40 bytes and
 * found/newObj must be ONE variable (a second pointer makes 4 scalars and frame 0xE0);
 * `tmp.unk4 = arg0->unk1C; if (tmp.unk4 >= 4)` is load-bearing because IDO forwards the u8
 * store into the compare (`lw t8` + `andi t9,t8,0xFF` with `sb t8` in the bnez delay slot) --
 * a named s32 temp costs ~30 rows; `% 0x79U` gives the divu/mfhi; ">= 4" gives the bnez.
 * IDO glues aggregate locals to the TOP of the frame in REVERSE declaration order.
 * The `(struct37 *)0x4C` cast is the repo-wide idiom for func_15149130's 7th parameter
 * (game_1028F0, game_10E240, game_113D60, game_11C2B0 ... all cast an integer the same way).
 *
 * PERMUTER: not needed and not used.  The previous session's ~7000-iteration run never moved
 * this function, and its best asm-differ output re-scored 44 in-TU -- a reminder that
 * asm-differ's number is misleading here.  fastscore was the authority throughout.
 */
#include <ultra64.h>

#include "functions.h"
#include "variables.h"

extern u8 D_800A1C00[][8];
extern s32 func_151149AC(u8);

typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ u8  unk14;
    /* 0x15 */ u8  unk15;
    /* 0x16 */ u8  unk16;
    /* 0x17 */ u8  unk17;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ u8  unk24[0x1C];
} ObjRec; /* size 0x40 */

typedef struct {
    /* 0x00 */ void *unk0;
    /* 0x04 */ u8  unk4;
    /* 0x05 */ u8  unk5;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ u8  unk8;
    /* 0x09 */ u8  pad9[3];
    /* 0x0C */ s32 unkC[8];
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ s16 unk3C;
    /* 0x3E */ s16 pad3E;
    /* 0x40 */ f32 unk40;
    /* 0x44 */ f32 unk44;
    /* 0x48 */ f32 unk48;
} Struct11D60; /* size 0x4C */

typedef struct {
    /* 0x00 */ u8  pad0[0x1C];
    /* 0x1C */ s32 unk1C;
} Arg11D60;

extern ObjRec *func_151438D8(s32, s32, u16, ObjRec *);

void func_15011D40(void) {
    func_15103800();
}

s32 func_15011D60(Arg11D60 *arg0) {
    Struct11D60 tmp;
    ObjRec obj;
    ObjRec *found;
    u8 flag;


    bzero(&tmp, 0x4C);
    tmp.unk8 = 0;
    tmp.unk6 = (func_150ADA20() % 0x79U) + 0x12C;
    tmp.unk0 = arg0;

    tmp.unk4 = arg0->unk1C;
    if (tmp.unk4 >= 4) {
        flag = 1;
    } else {
        flag = 0;
    }
    tmp.unk5 = flag;
    {
        u8 i;
        for (i = 0; i < 8; i++) {
            tmp.unkC[i] = func_151149AC(D_800A1C00[i][tmp.unk4]);
        }
        tmp.unk3C = 0;
        tmp.unk2C = 0.0f;
        tmp.unk30 = 0.0f;
        tmp.unk34 = 0.0f;
        tmp.unk38 = 0.0f;
    }
    obj.unk15 = 3;
    obj.unk17 = 0x15;
    obj.unk18 = tmp.unk4;
    found = func_151438D8(0, D_800D3094, 0x11A0, &obj);
    if (found != NULL) {
        tmp.unk40 = found->unk0;
        tmp.unk44 = found->unk4;
        tmp.unk48 = found->unk6;
    } else {
        tmp.unk48 = 10.0f;
    }
    found = (ObjRec *)func_15149130(0x12C, -1, -1, -1, 0, 0x38, (struct37 *)0x4C, 0xFF, 1);
    if (found != NULL) {
        memcpy((u8 *)found + 0x28, &tmp, 0x4C);
    }
    return 1;
}
