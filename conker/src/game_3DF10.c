/* game_3DF10.c -- func_15010A60.
 *
 * The five float constants are this function's OWN anonymous literal pool, not
 * globals: golden hoists them into callee-saved $f20..$f30, and IDO only hoists
 * LITERALS -- an `extern f32` is a memory object it reloads inside a
 * call-containing loop (measured: extern 330 / frame -0x1A0, literals 0 / -0x1D0;
 * `extern const f32` is identical to extern at 330).
 *
 * The pool is therefore migrated to this TU in conker.us.yaml:
 *     [0x23AF60, .rodata, game_3DF10]
 */
#include <ultra64.h>
#include "functions.h"
#include "variables.h"

// fat struct to decipher

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
} Vec3f3DF10;

typedef struct {
    /* 0x00 */ f32 unk00;
    /* 0x04 */ f32 unk04;
    /* 0x08 */ f32 unk08;
    /* 0x0C */ f32 unk0C;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ Vec3f3DF10 unk28;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ f32 unk40;
    /* 0x44 */ f32 unk44;
    /* 0x48 */ f32 unk48;
    /* 0x4C */ f32 unk4C;
    /* 0x50 */ s32 unk50;
    /* 0x54 */ s16 unk54;
    /* 0x56 */ s16 unk56;
    /* 0x58 */ u8 unk58;
    u8 pad59[3];
    /* 0x5C */ s32 unk5C;
    /* 0x60 */ u8 unk60;
    /* 0x61 */ u8 unk61;
    /* 0x62 */ u8 unk62;
    /* 0x63 */ u8 unk63;
    /* 0x64 */ u8 unk64;
    /* 0x65 */ u8 unk65;
    /* 0x66 */ u8 unk66;
    /* 0x67 */ u8 unk67;
    /* 0x68 */ u8 unk68;
    u8 pad69;
    /* 0x6A */ u8 unk6A;
    u8 pad6B;
    /* 0x6C */ s32 unk6C;
    /* 0x70 */ u8 unk70;
    u8 pad71;
    /* 0x72 */ s16 unk72;
    /* 0x74 */ s16 unk74;
    u8 pad76[2];
} Struct3DF10Part; /* size 0x78 */

typedef struct {
    /* 0x00 */ f32 unk00;
    /* 0x04 */ f32 unk04;
    /* 0x08 */ f32 unk08;
    /* 0x0C */ f32 unk0C;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ Vec3f3DF10 unk18;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
} Struct3DF10Tail; /* size 0x2C */

typedef struct {
    u8 pad0[0x50];
    s32 unk50;
} Obj3DF10;

extern void func_150E8854(void);
extern void func_1510F800(s32);
extern void *func_15132A4C(void *, s32, s32, s32, u8, s32);
extern Obj3DF10 *func_1513B5E0(void *, s32, s32, s32, s32);
extern struct225 *func_151602C0(Header *, Header2 *, s32, s32, s32, s32, u8, u8, s32, u8, s32);
extern u32 osGetCount(void);

extern Vec3f3DF10 D_80096450[];
extern u8 D_80096498[];

void func_15010A60(void) {
    void *result;
    Struct3DF10Part part;
    s32 i;
    u8 desc[0x3C];
    Struct3DF10Tail tail;
    f32 sp[6];
    f32 rnd;
    Obj3DF10 *ent;
    Header header;
    Header2 header2;
    void *payload;
    struct225 *snd;
    Vec3f3DF10 pos;

    func_150E8854();

    desc[1] = 3;
    desc[2] = 6;
    *(s16 *)&desc[4] = 0x12C;
    *(s32 *)&desc[0x30] = 9;
    desc[0] = 0;
    *(s32 *)&desc[0x34] = 0x1AF;
    desc[0x38] = 0;

    part.unk50 = 0xD00;
    part.unk54 = 0x12C;
    part.unk56 = 0x56;
    part.unk58 = 0;
    part.unk60 = 0xFF;
    part.unk61 = 0x10;
    part.unk62 = 0;
    part.unk63 = 0;
    part.unk64 = 0;
    part.unk65 = 0;
    part.unk66 = 0;
    part.unk67 = 0;
    part.unk68 = 2;
    part.unk6A = 2;
    part.unk6C = 0;
    part.unk70 = 0;
    part.unk72 = 1;
    part.unk74 = 0xFF;

    part.unk00 = 1.0f;
    part.unk04 = 1.0f;
    part.unk0C = 1.0f;
    part.unk08 = 1.0f;
    part.unk10 = 0.0f;
    part.unk14 = 0.0f;
    part.unk18 = 0.0f;
    part.unk1C = 1.0f;
    part.unk20 = 1.0f;
    part.unk24 = 1.0f;
    part.unk34 = 0.0f;
    part.unk38 = 0.0f;
    part.unk3C = 0.0f;
    part.unk40 = 0.0f;
    part.unk44 = 0.0f;
    part.unk48 = 0.0f;
    part.unk4C = 0.0f;
    tail.unk24 = 0.0f;
    tail.unk28 = 0.0f;

    for (i = 0; i < 6; i++) {
        pos = D_80096450[i];
        part.unk28 = pos;
        tail.unk18 = pos;

        func_1510F800(0);
        part.unk5C = func_1510FD20((s32)part.unk28.x, (s32)part.unk28.z);

        rnd = (u32)(osGetCount() * func_150ADA20()) & 0xFFFF;
        rnd *= 1.525902189e-05f;
        sp[0] = (rnd + rnd) * 3.141592741f;
        tail.unk00 = sp[0];

        rnd = (u32)(osGetCount() * func_150ADA20()) & 0xFFFF;
        rnd *= 1.525902189e-05f;
        sp[1] = (rnd + rnd) * 3.141592741f;
        tail.unk04 = sp[1];

        rnd = (u32)(osGetCount() * func_150ADA20()) & 0xFFFF;
        rnd *= 1.525902189e-05f;
        sp[4] = rnd * 3.800000191f + 2.0f;
        tail.unk10 = sp[4];

        rnd = (u32)(osGetCount() * func_150ADA20()) & 0xFFFF;
        rnd *= 1.525902189e-05f;
        sp[5] = rnd * 3.800000191f + 2.0f;
        tail.unk14 = sp[5];

        rnd = (u32)(osGetCount() * func_150ADA20()) & 0xFFFF;
        rnd *= 1.525902189e-05f;
        sp[2] = rnd * 0.1100000069f + 0.05000000075f;
        tail.unk08 = sp[2];

        rnd = (u32)(osGetCount() * func_150ADA20()) & 0xFFFF;
        rnd *= 1.525902189e-05f;
        sp[3] = rnd * 0.1100000069f + 0.05000000075f;
        tail.unk0C = sp[3];

        result = func_15132A4C(&part, 3, 0xFF, 0x18, 0xFF, 1);
        if (result != NULL) {
            memcpy((u8 *)result + 0x170, sp, 0x18);
        }

        if (D_80096498[i] != 0) {
            ent = func_1513B5E0(desc, 0, 0x2C, 0xFF, 1);
            if (ent != NULL) {
                memcpy((u8 *)ent + ent->unk50 + 0xF8, &tail, 0x2C);
            }
            header2.unk0 = (s32)D_80096450[i].x;
            header2.unk4 = (s32)D_80096450[i].y;
            header2.unk8 = (s32)D_80096450[i].z;
            payload = result;
            header.unk0 = 2;
            header.unk1 = 0x16;
            header.unk2 = 0x12C;
            header.unk4 = 0;
            snd = func_151602C0(&header, &header2, 0xC, 0xFF, 0xFF, 0xFF, 0xFF, 0, 4, 0xFF, 1);
            if (snd != NULL) {
                memcpy((u8 *)snd + 0x18, &payload, 4);
            }
        }
    }
}
