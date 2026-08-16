/* ===========================================================================
 * func_15146970 -- game_173D40.c -- PARKED 2026-08-15 (rodata-migration wave)
 * ===========================================================================
 * This file is the WHOLE TU as it stood when parked, because the migration of
 * block 0x24A190 needs the whole TU: that block is
 *     D_800A56D0 (a local-array initialiser image) + jtbl_800A56E4, both from
 *     func_15146970, followed by the TU's 19 POOLED FLOAT LITERALS, which
 *     eight ALREADY-MATCHING neighbours currently reach as `extern f32`.
 * Migrating the block therefore means those eight functions must stop using
 * `D_800A57xx` and spell the constants inline.  That part is DONE and VERIFIED.
 *
 * MEASURED with [0x24A190, .rodata, game_173D40] applied:
 *     differ -o -R = 210, 883 rows, ZERO register-only rows.
 *     All eight neighbours still build; the .rodata comes out in golden's order
 *     (array image, then jump table, then the 19 floats in source order).
 *
 * THE 19 FLOATS ARE SOLVED.  Do not re-derive them.  IDO converts decimal
 * literals ROUND-TO-NEAREST, so the shortest round-tripping decimal for each
 * golden word reproduces it bit-for-bit; this was checked by compiling the
 * whole list with the project's exact flags and comparing .data against the
 * golden .rodata -- all 19 words identical.  The mapping actually used:
 *     3CCCCCCC 0.024999999f   3CA30553 0.0199f       40FF3B65 7.9760003f
 *     BECE5605 -0.40300003f   3E916873 0.284f        3F741BDA 0.95355f
 *     3BFC0FC1 0.0076923077f  3F360B61 0.7111111f    3C40C0C1 0.011764706f
 *     3C23D70A 0.01f          3F828F5C 1.02f         3F70A3D8 0.94000006f
 * Note 0.025f, 7.976f, 0.94f and -0.403f are all WRONG by one ulp -- the ROM's
 * constants are genuinely those odd values, not the round numbers.
 *
 * THE RESIDUAL is ONE DISPLACED INSTRUCTION, and it is a known plateau.
 * Golden and this file contain exactly the same instructions; golden puts the
 * default `li v0,-1` in the switch bounds-check DELAY SLOT and lets the
 * dispatch `sll` follow it,
 *     sltiu at,a0,9 / beqz at,<epilogue> / li v0,-1 / sll t6,a0,0x2
 * where IDO here fills that slot from the fall-through instead and leaves the
 * `li v0,-1` as a one-instruction block at the tail:
 *     sltiu at,a0,9 / beqz at,<tail> / sll t6,a0,0x2 ... tail: li v0,-1
 * Same instruction count, same registers, 4-byte displacement -- asm-differ's
 * "displaced scores worse than missing" case.
 *
 * NINE honest spellings were probed standalone with the project's exact flags
 * (scratchpad probe_s.c) and every one filled the slot from the fall-through:
 *   trailing `return -1;`; `default: return -1;` last; `default:` FIRST (worse,
 *   685 -- it moves the body into the middle); `default: ;` + trailing return;
 *   `s32 ret = -1; ... return ret;` (IDO sinks the li to the tail, 215);
 *   `ret = -1;` as a separate statement; `ret` shared with case 6's failure
 *   path; NO trailing return at all (loses the instruction entirely);
 *   `switch ((u32)arg0)`; an explicit `if ((u32)arg0 < 9)` guard (emits TWO
 *   sltiu); and every case body on one line vs many (the -g3 reflow lever --
 *   measured no-op here, and the probe's one-line macro form behaves the same).
 *   All-break + single-exit is much worse (1025): `ret` then has to survive the
 *   func_150A2AEC call and gets a stack home golden does not have.
 * This is the cookbook's "unsteerable delay-slot strategy" family.  BAIL.
 *
 * Everything else is confirmed: the switch's SOURCE case order is
 * 8,7,5,2,0,1,4,3,6 (bodies in source order, per the -g3 switch law); case 6's
 * five-word list is a BLOCK-SCOPED local array initialiser (function-scope
 * would copy it at entry, golden copies it inside the case); and the index is
 * `(arg1 - (s32)D_800CC2D0) / (s32)sizeof(struct127)` with a real `div`.
 *
 * TO RESUME: install this file at conker/src/game_173D40.c, apply
 *     - [0x24A190, .rodata, game_173D40]
 * in conker.us.yaml, `make -C conker extract VERSION=us`.  Only the delay slot
 * is left.
 * =========================================================================== */

#include <ultra64.h>
#include "functions.h"
#include "variables.h"


typedef struct {
    f32 unk0;
    f32 unk4;
    s32 unk8;
} Struct15147040;

typedef struct {
    s32 pad0;
    struct17 vec;
} Struct15146E84Vec;

typedef struct {
    s32 values[8];
    s32 pad20;
} Struct15146E84Buffer;

typedef struct {
    s32 unk0;
    s32 unk4;
    Struct15147040 unk8;
    f32 unk14;
    f32 unk18;
    s16 unk1C;
    s16 unk1E;
    s16 unk20;
    s16 unk22;
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    f32 unk30;
    f32 unk34;
    f32 unk38;
    s8 unk3C;
    u8 pad3D;
    s16 unk3E;
    s16 unk40;
} Struct15146A98;

typedef struct {
    char pad_0[0x40];
    f32 field_0x40;
    char pad_1[0x190];
    s32 field_0x1D4;
} ActorFields;

extern s32 func_15142314(s32, s32, Struct15147040 *);
extern void func_1504715C(s32, s32);
extern s32 func_15046C80(f32 *, s32, f32, s32);
extern void func_15141F78(u8, struct157 *, f32, u8, struct157 *, u8);
extern void func_15142180(u8, Struct15147040 *, s32, f32, f32);
extern u8 func_151D8E20(void);
extern void func_151DAB58(u8, f32, u8, struct17 *, s32, u8, u8);
extern u8 (*D_8008FD04)(void);
extern u8 (*D_8008FD1C)(void);
extern u8 (*D_8008FD30)(void);
extern void func_15150F90(void *, s32, s32, s32);
void func_15143794(s32, s32, f32, f32 *);
struct260 *func_15130374(void *, u8, s32, u8, s32);

s32 func_15146890(Struct15147040 *arg0, ActorFields *arg1, s32 arg2, u8 arg3) {
    f32 sp2C[3];
    s32 temp_a1;

    if ((arg3 != 1) && (arg3 != 2)) {
        return 0;
    }

    if (arg3 == 1) {
        temp_a1 = 0x13;
    } else {
        temp_a1 = 0x17;
    }

    func_15142314(arg1->field_0x1D4, temp_a1, arg0);
    if (arg2 == 0) {
        return 1;
    }

    sp2C[0] = arg0->unk0;
    sp2C[1] = arg0->unk4 + 10.0f;
    sp2C[2] = *(f32 *)&arg0->unk8;
    func_1504715C(arg2, (s32)arg1);
    return func_15046C80(sp2C, 0, arg0->unk4 - 50.0f, arg2);
}

extern s32 func_151420F8(s32);
extern s32 func_150A2AEC(s32, s32, s32 *, s32);

/* Map an actor's damage/effect kind (arg0) onto the particle-effect id used for it,
   for the actor `arg1`.  Most kinds are a fixed id; kind 1 depends on the current
   world (D_800BE9F0) and, in world 4, on whether func_151420F8 accepts the actor;
   kind 6 first has to register a five-entry effect list against the actor's index in
   D_800CC2D0, and reports -1 if that fails.  Anything from 9 up is unmapped. */
s32 func_15146970(s32 arg0, s32 arg1) {
    switch (arg0) {
    case 8: return 0x10;
    case 7: return 0xF;
    case 5: return 5;
    case 2: return 2;
    case 0: return 0;
    case 1:
        if (D_800BE9F0 == 4) {
            if (func_151420F8(arg1) != 0) {
                return 6;
            }
            return 3;
        }
        return 1;
    case 4: return 4;
    case 3: return 3;
    case 6:
        {
            s32 list[5] = { 0x401D, 0x401E, 0x401F, 0x4020, 0x4021 };

            if (func_150A2AEC((arg1 - (s32)D_800CC2D0) / (s32)sizeof(struct127), 5, list,
                              arg1) == -1) {
                return -1;
            }
            return 6;
        }
    }
    return -1;
}

void func_15146A98(s32 arg0, s32 arg1, s32 arg2) {
    Struct15147040 sp5C;
    Struct15146A98 sp18;

    if (((ActorFields *)arg0)->field_0x1D4 != 0) {
        func_15146890(&sp5C, (ActorFields *)arg0, 0, (u8)arg1);
        sp18.unk0 = 5;
        sp18.unk4 = 0x16;
        sp18.unk8 = sp5C;
        sp18.unk14 = 0.024999999f;
        sp18.unk18 = 0.0199f;
        sp18.unk1C = 0;
        sp18.unk1E = 0xFF;
        sp18.unk20 = -0x14;
        sp18.unk22 = 0xE;
        sp18.unk24 = 6.0f;
        sp18.unk28 = 3.0f;
        sp18.unk2C = 7.9760003f;
        sp18.unk30 = -0.40300003f;
        sp18.unk34 = 0.284f;
        sp18.unk38 = 0.95355f;
        sp18.unk3C = 3;
        sp18.unk3E = 0x19;
        sp18.unk40 = 0x19;
        func_15150F90(&sp18, 0, 0xFF, 1);
    }
}

void func_15146BF8(ActorFields *, s32, s32, s32);

void func_15146BB8(s32 arg0, s32 arg1, s32 arg2) {
    func_15146BF8((ActorFields *)arg0, arg1, arg2, 0);
}

void func_15146BD8(s32 arg0, s32 arg1, s32 arg2) {
    func_15146BF8((ActorFields *)arg0, arg1, arg2, 1);
}

void func_15146BF8(ActorFields *arg0, s32 arg1, s32 arg2, s32 arg3) {
    Struct15147040 sp4C;
    s32 sp2C[8];
    s32 temp_a3;
    s32 temp_v0;

    temp_a3 = (u8)arg1;
    if (arg0->field_0x1D4 != 0) {
        if (func_15146890(&sp4C, (ActorFields *)*(s32 *)&arg0, (s32)&sp2C[-1], temp_a3) != 0) {
            temp_v0 = ((u8)arg3 != 0) ? 0xC : 0xB;
            func_15141F78((u8)temp_v0, (struct157 *)&sp2C[-1], (f32)arg2 * 0.0076923077f,
                          (u8)(u32)(arg0->field_0x40 * 0.7111111f),
                          (struct157 *)&sp4C, temp_a3);
            if (arg2 >= 0x73) {
                func_15142180(2, &sp4C, sp2C[5], 1.0f, 1.0f);
            }
        }
    }
}

void func_15146D60(ActorFields *arg0, s32 arg1, s32 arg2) {
    Struct15147040 sp4C;
    s32 sp2C[8];
    s32 temp_a3;

    temp_a3 = (u8)arg1;
    if (arg0->field_0x1D4 != 0) {
        if (func_15146890(&sp4C, (ActorFields *)*(s32 *)&arg0, (s32)&sp2C[-1], temp_a3) != 0) {
            func_15141F78(0xA, (struct157 *)&sp2C[-1], (f32)arg2 * 0.011764706f,
                          (u8)(u32)(arg0->field_0x40 * 0.7111111f),
                          (struct157 *)&sp4C, temp_a3);
        }
    }
}

void func_15146E84(ActorFields *arg0, s32 arg1, s32 arg2) {
    Struct15147040 sp7C;
    Struct15146E84Buffer sp58;
    u8 temp_color;
    Struct15146E84Vec sp44;
    s32 temp_rand;
    f32 temp_f0;

    if (arg0->field_0x1D4 != 0) {
        if (func_15146890(&sp7C, (ActorFields *)*(s32 *)&arg0, (s32)sp58.values, (u8)arg1) != 0) {
            temp_color = func_151D8E20();
            if (arg2 >= 0x47) {
                func_15142180(temp_color, &sp7C, sp58.values[6], 1.0f, 1.0f);
            }

            sp44.vec.unk0 = sp7C.unk0;
            sp44.vec.unk4 = *(f32 *)&sp58.values[0];
            sp44.vec.unk8 = *(f32 *)&sp7C.unk8;

            if (func_150ADA20() & 1) {
                temp_f0 = func_150ADA68();
                temp_rand = func_150ADA20();
                func_151D9B8C(temp_color, (temp_f0 * 10.0f) + 10.0f,
                              (u8)((temp_rand % 0x65U) + 0x64), (s32)&sp58.values[1], &sp44.vec,
                              (func_150ADA20() % 0x29U) + 0x50, 1, 1, 0, 0xFF, 1);
            } else {
                temp_f0 = func_150ADA68();
                func_151DAB58(temp_color, (temp_f0 * 8.0f) + 5.0f,
                              (u8)((func_150ADA20() % 0x65U) + 0x64), &sp44.vec, 1, 0xFF, 1);
            }
        }
    }
}

extern s32 func_15146890(Struct15147040 *, ActorFields *, s32, u8);
extern void func_1514C678(f32, f32, s32, f32, s32, s32, s32, s32, s32, f32, s32, s32);

void func_15147040(ActorFields *arg0, s32 arg1, s32 arg2) {
    Struct15147040 sp44;
    s16 temp;

    if (arg0->field_0x1D4 != 0) {
        func_15146890(&sp44, (ActorFields *)*(s32 *)&arg0, 0, (u8)arg1);
        temp = (func_150ADA20() % 11U) + 5;
        func_1514C678(sp44.unk0, sp44.unk4, sp44.unk8,
                      func_150ADA68() * 11.0f,
                      0, 0xFF, temp, 0x16, 0, 0.0f, 0, 0xFF);
    }
}

s32 func_151470FC(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, s32 arg5, s32 arg6, s32 arg7, s16 arg8, s32 arg9, s32 argA, s32 argB, s32 argC, s32 argD, u8 argE) {
    struct260 *ret;
    struct {
        f32 sp28;
        u8 pad2C[4];
        struct {
            s32 unk00;
            s32 unk04;
            s16 unk08;
            s16 unk0A;
            s32 unk0C;
            s32 unk10;
            u8 unk14;
            u8 unk15;
            u8 unk16;
            u8 unk17;
            u8 unk18;
            u8 unk19;
            u8 unk1A;
            u8 unk1B;
            u8 unk1C;
            u8 unk1D;
            s16 unk1E;
            s16 unk20;
            s16 unk22;
            f32 unk24;
            f32 unk28;
            f32 unk2C;
            f32 unk30;
            f32 unk34;
            f32 unk38;
            u8 pad3C[0xC];
            f32 unk48;
            f32 unk4C;
            f32 unk50;
            f32 unk54;
            s32 unk58;
            u8 pad5C[4];
            u8 unk60;
            u8 unk61;
            u8 unk62;
            s8 unk63;
        } sp30;
        u8 pad94[8];
    } stack;

    stack.sp30.unk1D = 0x29;
    stack.sp30.unk08 = 0xE03;
    stack.sp30.unk00 = 0x200005;
    stack.sp30.unk04 = 0;
    stack.sp30.unk0A = (func_150ADA20() & 0xF) + 0x14;
    stack.sp30.unk0C = 0;
    stack.sp30.unk10 = 0;
    stack.sp30.unk18 = 0xB0;
    stack.sp30.unk19 = 0xA0;
    stack.sp30.unk1A = 0x2A;
    stack.sp30.unk14 = 0x40;
    stack.sp30.unk15 = 0xB;
    stack.sp30.unk16 = 0x6A;
    stack.sp30.unk17 = 0xFF;
    stack.sp30.unk1B = (func_150ADA20() % 0x65U) + 0x64;
    stack.sp30.unk1C = 0xFF;
    stack.sp30.unk60 = 3;
    stack.sp30.unk61 = 3;

    stack.sp30.unk28 = stack.sp30.unk2C = (func_150ADA68() * 95.0f) + 101.0f;
    stack.sp30.unk30 = arg2;
    stack.sp30.unk34 = arg3;
    stack.sp30.unk38 = arg4;
    ((s32 *)&stack.sp28)[-2] = func_150ADA20();
    func_15143794(arg8, (s16)((((s32 *)&stack.sp28)[-2] % 0xBU) - 0xB),
                  ((func_150ADA68() * 396.0f) + 202.0f) * 0.01f, &stack.sp30.unk48);
    stack.sp30.unk54 = 0.0f;
    stack.sp30.unk58 = 0xE05;

    if (func_150ADA20() & 1) {
        stack.sp30.unk58 |= 0x40;
    }

    if (func_150ADA20() & 1) {
        stack.sp30.unk58 |= 0x80;
    }

    stack.sp30.unk62 = 0xA;
    stack.sp30.unk24 = 1.02f;
    stack.sp28 = 0.94000006f;
    stack.sp30.unk63 = -1;
    stack.sp30.unk1E = 0x14;
    stack.sp30.unk20 = 0xC;
    stack.sp30.unk22 = 0x1B;

    ret = func_15130374(&stack.sp30, 1, 4, argE, 1);
    if (ret != 0) {
        memcpy((u8 *)ret + 0xA8, &stack.sp28, 4);
    }
    return 1;
}

void func_15147318(ActorFields *arg0, s32 arg1, s32 arg2) {
    Struct15147040 sp4C;
    s32 sp2C[8];
    s32 temp_a3;

    temp_a3 = (u8)arg1;
    if (arg0->field_0x1D4 != 0) {
        if (func_15146890(&sp4C, (ActorFields *)*(s32 *)&arg0, (s32)&sp2C[-1], temp_a3) != 0) {
            if (arg2 >= 0x73) {
                func_15142180(0, &sp4C, sp2C[5], 1.0f, 1.0f);
            }
            func_15141F78((u8)D_8008FD04(), (struct157 *)&sp2C[-1], (f32)arg2 * 0.0076923077f,
                          (u8)(u32)(arg0->field_0x40 * 0.7111111f),
                          (struct157 *)&sp4C, temp_a3);
        }
    }
}

void func_15147478(ActorFields *arg0, s32 arg1, s32 arg2) {
    Struct15147040 sp4C;
    s32 sp2C[8];
    s32 temp_a3;

    temp_a3 = (u8)arg1;
    if (arg0->field_0x1D4 != 0) {
        if (func_15146890(&sp4C, (ActorFields *)*(s32 *)&arg0, (s32)&sp2C[-1], temp_a3) != 0) {
            func_15141F78((u8)D_8008FD1C(), (struct157 *)&sp2C[-1], (f32)arg2 * 0.0076923077f,
                          (u8)(u32)(arg0->field_0x40 * 0.7111111f),
                          (struct157 *)&sp4C, temp_a3);
            if (arg2 >= 0x73) {
                func_15142180(6, &sp4C, sp2C[5], 1.0f, 1.0f);
            }
        }
    }
}

void func_151475D8(ActorFields *arg0, s32 arg1, s32 arg2) {
    Struct15147040 sp4C;
    s32 sp2C[8];
    s32 temp_a3;

    temp_a3 = (u8)arg1;
    if (arg0->field_0x1D4 != 0) {
        if (func_15146890(&sp4C, (ActorFields *)*(s32 *)&arg0, (s32)&sp2C[-1], temp_a3) != 0) {
            func_15141F78((u8)D_8008FD30(), (struct157 *)&sp2C[-1], (f32)arg2 * 0.0076923077f,
                          (u8)(u32)(arg0->field_0x40 * 0.7111111f),
                          (struct157 *)&sp4C, temp_a3);
            if (arg2 >= 0x73) {
                func_15142180(0xB, &sp4C, sp2C[5], 1.0f, 1.0f);
            }
        }
    }
}
