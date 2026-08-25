/* PARKED: func_15010A60  (TU game_3DF10 -- a SINGLE-function TU, so this file is a STANDALONE TU:
 *     python3 tools/fastscore.py game_3DF10 func_15010A60 tools/nearmiss/func_15010A60.c
 *
 * SCORE 0.  n = 340/340 words.  frame -0x1D0 == golden.  THE SOURCE IS FINISHED.
 * It is NOT committable as it stands, and the reason is section placement, not C:
 *
 *   ===================================================================================
 *   BLOCKER -- ONE conker.us.yaml LINE.  REPORT/APPLY BY THE LEAD, NOT BY THIS AGENT.
 *
 *     conker/conker.us.yaml, in the rodata segment list (currently around line 999):
 *          - [0x23AF10, rodata]
 *     +    - [0x23AF60, .rodata, game_3DF10]   # anonymous float literal pool of func_15010A60
 *          - [0x23AF80, rodata]
 *
 *   This is the SAME pattern already applied four lines above it, at
 *     - [0x23A600, .rodata, game_360A0]   # anonymous float literal pool of func_15008BF0
 *   ===================================================================================
 *
 * WHY THE MIGRATION IS REQUIRED -- mechanism, proved by probe, not assumed
 *   Golden hoists five float constants into the callee-saved FP registers f20..f30 (six sdc1 in
 *   the prologue) because they are LOOP-INVARIANT.  A probe built with the project's exact flags
 *   settles what IDO will and will not hoist out of a loop that contains calls:
 *       extern f32 G1, G2;   out[i] = G1 * G2;   ->  lui/addiu the ADDRESSES into $s2/$s3, then
 *                                                    lwc1 the VALUES INSIDE the loop, no sdc1
 *       float literals       out[i] = 0.05f*...  ->  lwc1 into $f20/$f22 BEFORE the loop, sdc1 in
 *                                                    the prologue  == golden's shape
 *   So golden's constants are C float LITERALS, not extern globals.  Written as extern f32 the
 *   function bottoms out at 330 with frame -0x1A0 (five sdc1 missing); written as literals it is
 *   0 with frame -0x1D0.  There is no third spelling: extern const f32 was measured and is
 *   identical to extern f32 (330).
 *
 * WHY THIS BLOCK IS ACTUALLY MIGRATABLE (unlike the game_20A290 counter-example)
 *   game_20A290.c records the general rule: a rodata block is migratable only if it is ENTIRELY
 *   anonymous pool entries, and a split fails if the cut is not 16-byte aligned.  Both conditions
 *   are satisfied here, which is why this one is worth applying:
 *     * The cut is at 0x23AF60 -> vram 0x800964A0, which IS 16-byte aligned, so IDO's 2**4
 *       .rodata alignment introduces no padding and nothing downstream shifts.
 *     * Everything below the cut in 0x23AF10 (the named, addressed objects D_80096450,
 *       D_80096498, D_8009649E) STAYS in asm/data/23AF10.rodata.s and is untouched.
 *     * The emitted section is byte-identical to golden.  Measured with objdump -s on the object
 *       this file produces:
 *         .rodata size 0x20, algn 2**4
 *         0000 3d4ccccd 3de147af 40733334 40490fdb
 *         0010 37800080 00000000 00000000 00000000
 *       versus asm/data/23AF10.rodata.s at 0x23AF60..0x23AF7F:
 *         D_800964A0 3D4CCCCD  D_800964A4 3DE147AF  D_800964A8 40733334
 *         D_800964AC 40490FDB  D_800964B0 37800080  + 3 zero words
 *       Identical, and it ends exactly on the next yaml boundary 0x23AF80.
 *   AFTER the yaml line is added, drop asm/data/23AF10.rodata.s's tail accordingly (splat
 *   regenerates it), move this file to conker/src/game_3DF10.c, and run the normal gate:
 *     tools/buildlock.sh tools/verify_match.sh game_3DF10 func_15010A60
 *     python3 tools/relcheck.py conker/build/src/game_3DF10.c.o func_15010A60
 *
 * WHAT THE FUNCTION DOES
 *   Level-init: walks a 6-entry table of hard-coded world positions (D_80096450, 3 floats each)
 *   and for each one spawns a particle emitter (func_15132A4C) with a 6-float parameter payload,
 *   then -- only where the parallel flag table D_80096498[i] is set -- also spawns a second
 *   emitter (func_1513B5E0) with an 0x2C payload and a looping sound (func_151602C0) whose 4-byte
 *   payload is a back-pointer to the first emitter.
 *
 * THE FOUR NON-OBVIOUS THINGS, in the order they were worth points
 *   1. float literals, not externs (330 -> 116; see above).
 *   2. LOCAL LAYOUT.  At -O2 -g3 every named local costs 4 bytes even when register-only; locals
 *      are laid out from the TOP of the frame DOWNWARD in declaration order, on top of a fixed
 *      16-byte scratch area at the bottom of the local region, and the frame is rounded to 8.
 *      Golden's map, which the declaration list in this file reproduces exactly:
 *        0x90 scratch(16) | 0xA0 pos(12) | 0xAC snd | 0xB0 payload | 0xB4 header2(12)
 *        0xC0 header(6+2) | 0xC8 ent | 0xCC rnd | 0xD0 sp[6] | 0xE8 tail(0x2C)
 *        0x114 desc(0x3C) | 0x150 i | 0x154 part(0x78) | 0x1CC result
 *      The five word-sized locals are INTERLEAVED between the aggregates -- collecting them at
 *      either end costs 4-8 bytes of frame and ~60 rows.
 *   3. "result" and "payload" are TWO variables (116 -> 60 -> 0).  Golden keeps the func_15132A4C
 *      return in callee-saved $s0 across the whole iteration and only stores it to the addressed
 *      local (0xB0, whose address goes to memcpy) INSIDE the D_80096498[i] arm.  Using one
 *      variable emits sw $v0,0xB0(sp) 42 instructions too early and shifts everything after it.
 *   4. The paired writes are  sp[k] = <expr>;  tail.unkNN = sp[k];  -- two statements, buffer
 *      first.  Chained  sp[k] = tail.unkNN = <expr>  = 60;  tail.unkNN = sp[k] = <expr>  costs an
 *      extra compiler temp and pushes the frame to -0x1D8 = 117.
 *
 * STRUCT PROVENANCE
 *   Struct3DF10Part is Struct1518B6B0 from the MATCHED conker/src/game_1B8B60.c (the func_15132A4C
 *   argument, size 0x78), with unk28/2C/30 folded into a Vec3 so the 12-byte struct assignment
 *   emits golden's lw/sw triples.  Header (0x6) and Header2 (0xC) are from include/structs.h.
 *   The func_1513B5E0 descriptor is a u8[0x3C] with field pokes, exactly as the MATCHED
 *   conker/src/game_168A90.c func_1513BAE8 writes the same descriptor.
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
