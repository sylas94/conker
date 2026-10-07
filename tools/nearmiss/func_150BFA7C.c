/* game_EC420 / func_150BFA7C -- NEAR-MISS 136 (fastscore mism, n=345/345, frame 0x60 exact), 2026-10-05.
 * Last pragma in game_EC420. Lift behaviour on a pair of 0xA0 D_800DBEF4 records (arg0[1] = partner).
 *
 * WHAT CLOSED 364 -> 136 (all honest):
 *  - top/bottom/range/type must stay out of registers. IDO rematerialises `top = base - 80` /
 *    `bottom = top - range` at their uses (and promotes range) when `base` is a copy of a value
 *    nothing redefines. Golden computes them once at entry, stores homes 0x5E/0x5A, spills temps
 *    0x30/0x2C. Fix: read unk7C into a scratch `temp`, `base = temp`, and REUSE `temp` for the rebase
 *    delta (`temp = bottom - top; arg0->unk7C += temp; ...`). (A permuter run found the mechanism
 *    via a fake `speed = arg0->unk7C; base = speed;`.)
 *  - declaration order sets the -g3 homes: top 5E, base 5C, bottom 5A, temp 54, range 50,
 *    speed 4C, timer 48, state 44, type 40, sp38 38.
 *  - `state = 1;` at the top of the rising branch (golden re-materialises t1=1 there) gives state t1
 *    and speed t2 like golden.
 * RESIDUE: golden keeps `base` as a real s16 variable (t0, spilled `sh t0,0x5C`); ours propagates it
 *  into a cvt(temp) CSE temp spilled `sw t0,0x34`. That shifts temp registers downstream (most of the
 *  136). Tried and refuted: base from memory (368), two defs of base (483+), temp reuse in the type==1
 *  branch (350), `base += unk80` in type==1 (350), block-scoped decls, line grouping, decl orders.
 * Diagnostic only (NOT shippable): `pr = &range` -> 324 from a 364 base, proving range residency is
 *  the trigger.
 */
/* One 0xA0-byte entry of the D_800DBEF4 table (struct131 in structs.h is a partial view); a lift
 * owns two consecutive entries, the second tracking its counterpart. */
typedef struct Lift150BFA7C {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ u8 pad4[0x4];
    /* 0x08 */ f32 unk8;
    /* 0x0C */ u8 padC[0x6];
    /* 0x12 */ s16 unk12;
    /* 0x14 */ u8 pad14[0x28];
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ u8 pad40[0xF];
    /* 0x4F */ u8 unk4F;
    /* 0x50 */ u8 pad50[0x1E];
    /* 0x6E */ u8 unk6E;
    /* 0x6F */ u8 pad6F[0x4];
    /* 0x73 */ u8 unk73;
    /* 0x74 */ u8 pad74[0x8];
    /* 0x7C */ s32 unk7C;
    /* 0x80 */ s32 unk80;
    /* 0x84 */ s32 unk84;
    /* 0x88 */ u8 pad88[0x18];
} Lift150BFA7C;

typedef struct {
    u8 unk0;
    u8 pad1;
    s16 unk2;
    u8 unk4;
    u8 unk5;
    s8 unk6;
    u8 pad7;
} Arg151D8868;

extern u8 D_800BE9EB;
extern void func_1518B6B0(f32, f32, f32, u8, s32);
extern void func_15164F0C(s32, u8, s32, s32, s32);
extern void func_151D8868(void *, s32, s32, s32);
extern s32 func_151EF610(void);
extern void func_1518CD20(Lift150BFA7C *, s32, s32);
extern void func_1508EE0C(s32, u16);

void func_150BFA7C(Lift150BFA7C *arg0) {
    s16 top;
    s16 base;
    s16 bottom;
    s32 temp;
    s32 range;
    s32 speed;
    s32 timer;
    s32 state;
    s32 type;
    Arg151D8868 sp38;

    type = (arg0->unk3C >> 16) & 0xFFFF;
    speed = 0x10;
    state = arg0->unk73 & 3;
    range = 0;
    if (type == 0) {
        range = 0x82;
    } else if (type == 2) {
        range = 0x622;
        speed = 0x30;
    }
    temp = arg0->unk7C;
    if (temp == 0) {
        temp = arg0->unk12 | 0x80000000;
        arg0->unk7C = temp;
    }
    base = temp;
    top = base - 0x50;
    bottom = top - range;
    if (type == 1) {
        if (base - arg0->unk12 != arg0->unk80) {
            arg0->unk12 = base + arg0->unk80;
        }
        return;
    }
    if ((arg0->unk4F & 4) && (D_800CC2D0[0].unk31C->unk57 == 1)) {
        func_1518B6B0(D_800CC2D0[0].x_position, D_800CC2D0[0].y_position, D_800CC2D0[0].z_position, 0xFF, 0);
        if (state == 0) {
            func_15164F0C(3, D_800BE9EB, 0, 0xFF, 0);
            sp38.unk0 = 1;
            sp38.unk2 = 0x3C;
            sp38.unk5 = 1;
            sp38.unk4 = 8;
            sp38.unk6 = -1;
            func_151D8868(&sp38, 0, 0xFF, 0);
        }
    }
    if (state == 3) {
        if (arg0->unk12 != top) {
            arg0->unk12 = top;
        }
        if (!(arg0->unk4F & 4) && !(arg0->unk73 & 4)) {
            state = 1;
        }
    } else if (state == 0) {
        if (arg0->unk12 != base) {
            arg0->unk12 = base;
        }
    } else if (state == 2) {
        timer = arg0->unk80 + D_800BE9E4;
        arg0->unk80 = timer;
        if (timer < 0) {
            arg0->unk0 = ((func_151EF610() % 5) - 2.0f) * 0.125f;
            arg0->unk8 = ((func_151EF610() % 5) - 2.0f) * 0.125f;
        } else {
            if (timer < 40) {
                arg0->unk0 = ((func_151EF610() % 5) - 2.0f) / 12.0f;
                arg0->unk8 = ((func_151EF610() % 5) - 2.0f) / 12.0f;
            } else {
                arg0->unk8 = 0.0f;
                arg0->unk0 = 0.0f;
            }
            if (arg0->unk12 < top) {
                if (type == 0) {
                    speed = ((arg0->unk12 - bottom + 16) * speed) / range;
                    if (arg0->unk84 == 0) {
                        func_1518CD20(arg0, 0xFF, 0);
                        arg0->unk84 = 1;
                    }
                }
                arg0->unk12 -= speed;
                arg0[1].unk80 = arg0->unk12 - top;
            } else {
                arg0->unk12 -= speed;
                arg0->unk84 = 0;
            }
            if (arg0->unk12 <= bottom || speed == 0) {
                arg0->unk12 = bottom;
                temp = bottom - top;
                arg0->unk7C += temp;
                arg0[1].unk7C += temp;
                arg0->unk7C |= 0x80000000;
                arg0->unk80 = 0;
                arg0[1].unk7C |= 0x80000000;
                arg0[1].unk80 = 0;
                if (type == 4 && state != 3) {
                    func_1518CD20(arg0, 0xFF, 0);
                }
                arg0->unk8 = arg0->unk0 = 0.0f;
                state = 3;
                if (type == 2) {
                    arg0->unk6E = 1;
                    arg0[1].unk6E = 1;
                    func_1508EE0C(2, arg0 - (Lift150BFA7C *)D_800DBEF4);
                    func_1508EE0C(2, (arg0 + 1) - (Lift150BFA7C *)D_800DBEF4);
                }
            }
        }
    } else if (state == 1) {
        arg0->unk12 += 3;
        state = 1;
        if (arg0->unk12 >= base) {
            arg0->unk12 = base;
            state = 0;
        }
    }
    arg0->unk73 &= ~3;
    arg0->unk73 |= state;
}
