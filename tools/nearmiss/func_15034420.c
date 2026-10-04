/* tools/nearmiss/func_15034420.c -- game_61490, 32 instructions, LEAF (no frame)
 *
 * STATUS: mism=6, n=32/32 (EXACT LENGTH), leaf. SIX register names, nothing else.
 * *** PRIME decomp-permuter CANDIDATE *** -- exact length AND exact frame with a pure
 * register tie is the case [[conker-permuter-setup]] says it cracks in under a minute.
 * Cold decompile, opened 2026-08-25 from the never-attempted list.
 *
 * WHAT IT IS: builds a 4-entry s16 header at arg0 and returns the cursor past it.
 * `D_800CC5B4` is read at a **0x32C stride** -- that is the ACTOR RECORD stride from
 * [[conker-actor-control-system]] (array D_800CC2D0, 0x32C), so D_800CC5B4 is the field at
 * +0x2E4 of actor record `arg1`, not a standalone array. Golden spells the stride as the
 * shift chain ((((a*4-a)*4+a)*4-a)*4-a)*4 = 812; a plain struct index reproduces it exactly.
 *
 *      v         = (s16)(s32)((f32)actor[arg1].field_0x2E4 * D_80097D18);
 *      arg0[0]   = 0;
 *      arg0[2]   = 0x18;          // 24
 *      arg0[1]   = v >> 4;
 *      arg0[3]   = v - (v >> 4);
 *      return arg0 + 4;
 * The (s16) narrowing is golden's `sll t9,v1,16 / sra t0,t9,16` pair and is required.
 *
 * ---------------------------------------------------------------- THE RESIDUAL
 *      idx15/18   ours `addiu t1,zero,24` + `sh t1,0x4(a0)`   gold uses **t6**
 *      idx26-29   ours `sra a2` / `subu t2,t0,a2`             gold uses **t1** and **t5**
 * Golden REUSES $t6 -- the now-dead index temp -- for the 0x18 constant, which leaves t1/t5
 * for the shift pair. We take a fresh t1 for the constant and are pushed onto $a2 (an
 * ARGUMENT register) and t2. Everything else, including the whole float chain and the
 * sll/sra narrowing at idx19-25, is byte-identical.
 *
 * DO NOT REPEAT (all measured, all n=32/32 unless noted):
 *   6   base (this file)
 *   6   `s16 h = v >> 4;` named, `arg0[3] = v - h`            (identical)
 *   6   `v` declared s32 instead of s16                       (identical)
 *   6   the `arg0 + 4` return value hoisted into a local      (identical)
 *  13   `arg0[0] = 0;` moved above the float computation
 *  42   a third parameter (s32 or void *)   n=33/32 -- adds an arg spill; the function
 *  48   a fourth parameter                  n=34/32    really does take exactly TWO
 * The a2-as-temp allocation is NOT caused by a missing parameter, which was the obvious
 * hypothesis (golden never touches a2/a3, and a 2-arg function leaves both free).
 *
 * ---------------------------------------------------------- PERMUTER RUN, 2026-08-25: REJECTED
 * Set up with permuter_tu.sh (selftest PASS, incl. the TU-context control -- a plain
 * single-function permuter would optimise the wrong bytes here). It improved its own metric
 * 35 -> 25 and emitted output-25-1. **The entire gain is a FORCER and was rejected.**
 * Its candidate makes two changes; decomposed and scored separately in-file:
 *      hoist `v >> 4` into a local, computed before the 0x18 store ... 6  (NO GAIN)
 *      ...as `s16` or `s32`                                        ... 6  (NO GAIN)
 *      type that local `long long`                                 ... 5  (the whole gain)
 * A 64-bit type for a 16-bit shift result is not something any source writes; it exists only
 * to perturb codegen, which is the banned class ([[conker-fake-match-policy]]). Taking it
 * would buy ONE row. Do not reintroduce it, and note this is the third time the permuter's
 * best output on this repo has been its only dishonest one ([[conker-permuter-setup]]).
 */

typedef struct Rec32C15034420 {
    s32 unk0;
    char pad4[0x328];
} Rec32C15034420;

extern Rec32C15034420 D_800CC5B4[];
extern f32 D_80097D18;

s16 *func_15034420(s16 *arg0, s32 arg1) {
    s16 v;

    v = (s16)(s32)((f32)D_800CC5B4[arg1].unk0 * D_80097D18);
    arg0[0] = 0;
    arg0[2] = 0x18;
    arg0[1] = v >> 4;
    arg0[3] = v - (v >> 4);
    return arg0 + 4;
}
