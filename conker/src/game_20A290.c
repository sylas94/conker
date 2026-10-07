#include <ultra64.h>
#include "functions.h"
#include "variables.h"

/* func_151DCDE0 -- needs `- [0x250010, .rodata, game_20A290]` in conker.us.yaml (+ splat --modes ld).
 * The old park said this block could never migrate because "IDO never puts initialised data in
 * .rodata". That holds for a const SCALAR (lands in .data), but a const ARRAY goes to .rodata:
 * with D_800AB550/D_800AB554 as one-element const arrays this object's .rodata is exactly golden's
 * 0x20-byte block 0x250010 -- 00000010 3F800000 3E4CCCCD BF316873 3E9BA5E4 41CDB646 + 8 zero pad.
 * `f32 sp28 = 0.2f` is a local with an initialiser (pool order: 0.2 precedes -0.693), and the real
 * source text is `0.30400002f` (golden holds 3E9BA5E4, `0.304f` gives ...E3).
 */
struct Vec151DCDE0 {
    s32 unk00;
    s32 unk04;
    s32 unk08;
};

struct Src151DCDE0 {
    struct Vec151DCDE0 unk00;
};

struct Conker151DCDE0 {
    s32 unk00;
    s32 unk04;
    struct Vec151DCDE0 unk08;
    s16 unk14;
    s16 unk16;
    s16 unk18;
    s16 unk1A;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
    s16 unk2C;
    s16 unk2E;
    f32 unk30;
    f32 unk34;
    f32 unk38;
};

void func_15152190(struct Conker151DCDE0 *, const s32 *, const f32 *, s32, f32, s32, s32, s32);

const s32 D_800AB550[1] = { 0x10 };
const f32 D_800AB554[1] = { 1.0f };

void func_151DCDE0(struct Src151DCDE0 *arg0, u8 arg1, s32 arg2) {
    struct Conker151DCDE0 sp2C;
    f32 sp28 = 0.2f;

    sp2C.unk00 = 0xC;
    sp2C.unk04 = 5;
    sp2C.unk08 = arg0->unk00;
    sp2C.unk14 = 0;
    sp2C.unk16 = 0xFF;
    sp2C.unk18 = -0x40;
    sp2C.unk1A = 0x31;
    sp2C.unk1C = 3.0f;
    sp2C.unk20 = 9.0f;
    sp2C.unk24 = -0.693f;
    sp2C.unk28 = 0.30400002f;
    sp2C.unk2C = 0x19;
    sp2C.unk2E = 0x14;
    sp2C.unk30 = sp28;
    sp2C.unk34 = sp28;
    sp2C.unk38 = 25.714f;
    func_15152190(&sp2C, D_800AB550, D_800AB554, 1, 26.0f, 0, arg1, arg2);
}
