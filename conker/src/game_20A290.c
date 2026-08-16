#include <ultra64.h>
#include "functions.h"
#include "variables.h"

/* func_151DCDE0 -- SOURCE-COMPLETE (the C below scores 0) but PERMANENTLY BLOCKED by section
 * placement, not by any remaining source question. Do not re-attempt the migration.
 *
 * THE BLOCKER, measured 2026-08-16. The pool at 0x250010 is
 *
 *      800AB550  .word  0x00000010     <- NAMED, ADDRESSED object (passed as &)
 *      800AB554  .float 1.0            <- NAMED, ADDRESSED object (passed as &)
 *      800AB558  .float 0.2
 *      800AB55C  .float -0.693
 *      800AB560  .float 0.30400002
 *      800AB564  .float 25.714
 *
 * Migrating it to this TU requires the C to emit all six IN ORDER. It cannot:
 * **IDO 5.3 NEVER PUTS INITIALISED DATA IN .rodata.** A standalone probe built with the project's
 * exact flags produced only .text and .data -- no .rodata section at all -- with
 * `const s32 x = 0x10;` landing in .data, and `static const` eliminated outright. The ONLY .rodata
 * IDO emits is the anonymous literal / jump-table pool. Confirmed on this very TU: with the two
 * objects defined as `const`, the object came out .rodata=16 (the four floats only) and .data=16
 * holding `00000010 3f800000`.
 *
 * Splitting the block to migrate only the four literals fails too: the cut would be at 0x250018,
 * and IDO gives .rodata 2**4 alignment, so the linker pads to 0x250020 and shifts everything.
 * Every migration that has shipped began on a 16-byte boundary.
 *
 * GENERAL RULE THIS ESTABLISHES: a rodata block is migratable only if it consists ENTIRELY of
 * anonymous pool entries (float literals, jump tables). One named addressed object anywhere in it
 * -- especially at its head -- puts the block out of reach of C.
 *
 * THE SOURCE IS OTHERWISE FINISHED. It scores 0, and its emitted pool is byte-identical to
 * golden's four literals:
 *
 *   void func_151DCDE0(struct Src151DCDE0 *arg0, u8 arg1, s32 arg2) {
 *       struct Conker151DCDE0 sp2C;
 *       f32 sp28 = 0.2f;
 *       sp2C.unk00 = 0xC;    sp2C.unk04 = 5;      sp2C.unk08 = arg0->unk00;
 *       sp2C.unk14 = 0;      sp2C.unk16 = 0xFF;   sp2C.unk18 = -0x40;   sp2C.unk1A = 0x31;
 *       sp2C.unk1C = 3.0f;   sp2C.unk20 = 9.0f;   sp2C.unk24 = -0.693f;
 *       sp2C.unk28 = 0.30400002f;
 *       sp2C.unk2C = 0x19;   sp2C.unk2E = 0x14;
 *       sp2C.unk30 = sp28;   sp2C.unk34 = sp28;   sp2C.unk38 = 25.714f;
 *       func_15152190(&sp2C, &D_800AB550, &D_800AB554, 1, 26.0f, 0, arg1, arg2);
 *   }
 *
 *   struct Vec151DCDE0    { s32 unk00; s32 unk04; s32 unk08; };
 *   struct Src151DCDE0    { struct Vec151DCDE0 unk00; };
 *   struct Conker151DCDE0 { s32 unk00; s32 unk04; struct Vec151DCDE0 unk08;
 *                           s16 unk14, unk16, unk18, unk1A;
 *                           f32 unk1C, unk20, unk24, unk28;
 *                           s16 unk2C, unk2E;
 *                           f32 unk30, unk34, unk38; };
 *   extern s32 D_800AB550;  extern f32 D_800AB554;
 *   void func_15152190(struct Conker151DCDE0 *, s32 *, f32 *, s32, f32, s32, s32, s32);
 *
 * Layout came from the two matched callers of func_15152190:
 *   src/game_1CBE20.c func_1519EA78      src/game_130B40.c func_151036B4
 *
 * `f32 sp28 = 0.2f` is a LOCAL WITH AN INITIALISER, proven by pool ordering: IDO emits anonymous
 * literals in order of first appearance, and 0.2f precedes -0.693f even though the field it fills
 * is assigned later. Declaring it BEFORE the struct scores 442 (scalars and aggregates share one
 * stack pool, so the struct slides and `addiu a0,sp,0x2c` breaks). As `extern f32` it scores 240,
 * because an extern's ADDRESS becomes a hoistable node instead of its value.
 *
 * ONE ULP MATTERED: `0.304f` compiles to 3E9BA5E3 but golden holds 3E9BA5E4 -- the real source
 * text is `0.30400002f`. asm-differ CANNOT see this, since .text carries only the %hi/%lo
 * reference: the score was 0 either way. When a pool is migrated its BYTES are a SEPARATE
 * acceptance test from the score.
 */
#pragma GLOBAL_ASM("asm/nonmatchings/game_20A290/func_151DCDE0.s")
