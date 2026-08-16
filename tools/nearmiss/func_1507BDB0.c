/* MATCHED -- this is a copy of the shipped conker/src/game_A9260.c.
 * func_1507BDB0: score 0 with and without -R; .text/.rodata/.data of
 * build/src/game_A9260.c.o are byte-identical to expected/.  Kept here only as
 * a record of the levers that closed it:
 *   1. frame decode 0x38 = argbuild16 + (s0,s1,ra) padded to 0x20, then FIVE
 *      locals top-down: f32 t @0x34, s32 flags @0x30, u8 ended @0x2F,
 *      f32 ret @0x28, s32 old @0x24.  sum(sizeof)=20, 0x20+20=0x34 -> 0x38.
 *      The f32 at 0x34 is NOT the parameter: arg1 is mutated in the first
 *      third of the function and a *new* local `t` is born at the
 *      min(unk10*dt, unk18)+unk8 step, so the two webs are disjoint and both
 *      live in $f12 with no mov.s.  (Using arg1 throughout -> frame 0x30, 855;
 *      using a local from the top -> mov.s $f2,$f12, 2915.)
 *   2. branch sense: `if (D_800C35EA == 0) {...} else { arg1 = D_800BE9A4; }`
 *      (bnez to the else) not `if (!= 0) {...} else if`.
 *   3. `flags |= arg2->unkF4 & 0xE;` not a re-spelled full expression -- the
 *      re-read of arg0->unk4 was 2 extra instructions.
 *   4. INDEPENDENT-STATEMENT ORDER inside `if (arg2 != NULL)`: putting
 *      `flags |= arg2->unkF4 & 0xE;` BEFORE `arg2->unk1FC &= ~4;` (which is
 *      before `D_800C3E78 = arg2 - D_800CC2D0;`) took 805 -> 60 -> 20.
 *      The lw 0xF4 has to be scheduled above both sb's, and the web that is
 *      created first gets the lower temp register.
 *   5. the last 20 points: `arg2->unk76 += arg2->unk1FD << 8;
 *      arg2->unk7A = arg2->unk76; arg2->unk78 = arg2->unk76;`  The chained
 *      form `unk78 = unk7A = unk76 = unk76 + (unk1FD << 8)` emits the same
 *      three sh in the same order but puts the value in $t8; the += form puts
 *      it in $v0 like golden.  Introducing a named `s32 ang` local instead
 *      fixed $v0 but rotated every later temp register by one (195).
 * ===================================================================== */
#include <ultra64.h>
#include "functions.h"
#include "variables.h"

/* struct197 in structs.h stops at 0x1C; func_1507BDB0 reads 0x20, 0x28, 0x3A and
 * 0x3C off the same object (struct127::unk2D0), so a file-local widened view is
 * used here rather than retyping the shared header. */
typedef struct AnimPlay {
    /* 0x00 */ void (*unk0)(void);
    /* 0x04 */ u16 unk4;
    /* 0x06 */ u8  pad6[0x2];
    /* 0x08 */ f32 unk8;
    /* 0x0C */ u8  padC[0x4];
    /* 0x10 */ f32 unk10;
    /* 0x14 */ u8  pad14[0x4];
    /* 0x18 */ f32 unk18;
    /* 0x1C */ u8  pad1C[0x4];
    /* 0x20 */ f32 unk20;
    /* 0x24 */ u8  pad24[0x4];
    /* 0x28 */ s32 unk28;
    /* 0x2C */ u8  pad2C[0xE];
    /* 0x3A */ s16 unk3A;
    /* 0x3C */ s16 unk3C;
} AnimPlay;

extern u8 D_800BEA0C;
extern u8 D_800C365E;

f32 func_1506AD30(struct127 *arg0, f32 arg1, s32 arg2);

void func_1507BDB0(AnimPlay *arg0, f32 arg1, struct127 *arg2, s32 arg3) {
    f32 t;
    s32 flags;
    u8 ended;
    f32 ret;
    s32 old;

    if (arg0->unk28 == 0) {
        return;
    }

    if (arg2 != NULL) {
        if (D_800C35EA == 0) {
            if (D_800BE9A4 < 2.0f) {
                arg1 = D_800BE9A4 * arg1;
            } else {
                arg1 = arg1 + arg1;
            }
        } else {
            arg1 = D_800BE9A4;
        }
    }
    if (D_800BEA0C != 0) {
        arg1 = 0.0f;
    }

    if (arg0->unk18 < (arg0->unk10 * arg1)) {
        t = arg0->unk18 + arg0->unk8;
    } else {
        t = (arg0->unk10 * arg1) + arg0->unk8;
    }

    flags = arg0->unk4 & 0x8000;
    if (arg2 != NULL) {
        flags |= arg2->unkF4 & 0xE;
        arg2->unk1FC &= ~4;
        D_800C3E78 = arg2 - D_800CC2D0;
        D_800D154C = arg2;
    }

    ended = 0;
    if (arg2 != NULL) {
        if (((&D_800C35EA)[arg3] != 1) || ((&D_800C365E)[arg3] != 0)) {
            ret = func_1506AD30(D_800D154C, t, 0);
            if (ret != 0.0f) {
                t = ret;
            }
        }
    }

    if (arg0->unk10 >= 0.0f) {
        if (((arg0->unk18 - 1.0f) <= t) && (arg0->unk8 < (arg0->unk18 - 1.0f)) && (arg0->unk0 != NULL)) {
            old = arg0->unk28;
            if ((arg2 != NULL) && (arg2->unkF4 & 8)) {
                arg2->unk10C = 0;
                arg2->pad1C4 = 0;
                arg0->unk10 = 0.0f;
            }
            if (D_800C35EA == 0) {
                arg0->unk0();
            }
            if (old != arg0->unk28) {
                t = arg0->unk8;
                ended = 1;
            }
        }

        if ((arg2 != NULL) && (arg2->unk1FD != 0) && ((arg0->unk18 - 1.0f) <= t)) {
            arg2->unk76 += arg2->unk1FD << 8;
            arg2->unk7A = arg2->unk76;
            arg2->unk78 = arg2->unk76;
            arg0->unk8 = arg0->unk20;
            if (arg2->unkF4 & 4) {
                arg2->unk21C = 0;
            }
        } else if ((flags == 0) && (arg0->unk18 <= t)) {
            arg0->unk8 = (t - arg0->unk18) + arg0->unk20;
            ended = 1;
            if (arg2 != NULL) {
                arg2->unk1FC |= 4;
            }
        } else if ((flags != 0) && ((arg0->unk18 - 1.0f) <= t)) {
            if (((arg2 != NULL) && (arg2->unkF4 & 0xA)) || (arg0->unk4 & 0x8000)) {
                arg0->unk8 = arg0->unk18 - 1.0f;
            } else if (arg0->unk8 < (arg0->unk18 - 1.0f)) {
                arg0->unk8 = arg0->unk18 - 1.0f;
                if ((arg2 != NULL) && (arg2->unkF4 & 4)) {
                    arg2->unk21C = 0;
                }
            } else {
                arg0->unk8 = arg0->unk20;
                if (arg2 != NULL) {
                    arg2->unk138 = 0;
                    arg2->unk1FC |= 2;
                }
            }
            if ((arg2 != NULL) && (arg2->unkF4 & 8)) {
                arg2->unk10C = 0;
                arg2->pad1C4 = 0;
                arg0->unk10 = 0.0f;
            }
            if (arg0->unk8 < 0.0f) {
                arg0->unk8 = 0.0f;
            }
        } else {
            arg0->unk8 = t;
        }
    } else if (t < arg0->unk20) {
        arg0->unk8 = (t - arg0->unk20) + arg0->unk18;
    } else {
        arg0->unk8 = t;
    }

    if (arg0->unk3C > 0) {
        arg0->unk3C -= arg0->unk3A * D_800BE9E4;
    }
    if (arg2 != NULL) {
        if (ended != 0) {
            func_1506AD30(D_800D154C, arg0->unk8, 0);
        }
        *(f32 *)&arg2->padB4 = arg0->unk8;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_A9260/func_1507C22C.s")

void func_1507C324(void *arg0, void *arg1) {
    s32 *p0 = *(s32 **)((u8 *)arg0 + 0x2D0);
    s32 *p1 = *(s32 **)((u8 *)arg1 + 0x2D0);
    f32 temp;

    if (p0 != 0 && p1 != 0) {
        *(f32 *)((u8 *)p0 + 0x8) = *(f32 *)((u8 *)p1 + 0x8);
        temp = *(f32 *)((u8 *)p0 + 0x18) - 1.0f;
        if (temp <= *(f32 *)((u8 *)p0 + 0x8)) {
            *(f32 *)((u8 *)p0 + 0x8) = temp;
        }
    }
}

void func_1507C3E0(struct127 *arg0, s16 *arg1, s16 *arg2, s16 *arg3);

void func_1507C370(void) {
    s32 i;
    struct127 *obj = D_800CC2D0;

    for (i = 0; i < D_8008FD8C; i++, obj++) {
        struct126 *p = obj->unk31C;
        if (p != NULL) {
            func_1507C3E0(obj, (s16 *)((u8 *)p + 0x114), (s16 *)((u8 *)p + 0x116), (s16 *)((u8 *)p + 0x118));
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_A9260/func_1507C3E0.s")
