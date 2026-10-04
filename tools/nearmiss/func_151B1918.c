/* tools/nearmiss/func_151B1918.c -- game_1DD500, 35 instructions, frame -0x30 (s0-s4 + ra)
 *
 * STATUS: mism=12, n=35/35 (EXACT LENGTH), FRAME EXACT, all five callee-saved registers
 * saved and restored exactly as golden.  Cold decompile 2026-10-02.
 *
 * WHAT IT IS: teardown of the 12-entry, 12-byte-record table embedded at +0x28 (it ends
 * exactly at the f32 at +0xB8).  Entries 1..11 get their first word released through
 * func_1516972C and all three words zeroed; entry 0 only gets its third word cleared.
 * The TU declares `void func_151B1918(struct260 *arg0);` at line 25, so the parameter type
 * is fixed -- and struct260 in structs.h is only 0x24 long, so the body must cast.  Use a
 * `#define O ((Obj151B1918 *)arg0)` MACRO, not a local:
 *
 *     >>> THE BIG LEVER WAS NOT THE LOOP, IT WAS THE CAST.  Writing
 *     >>>     Obj151B1918 *o = (Obj151B1918 *)arg0;
 *     >>> costs a SIXTH callee-saved register (IDO parks `o` in $s4 and keeps it live
 *     >>> across the whole loop) and scores 63, n=38/35.  Replacing that local with a
 *     >>> macro that re-spells the cast at each use scores 12, n=35/35.  Same lesson as
 *     >>> [[conker-ido-local-decl-laws]]: a named local IDO cannot coalesce is a register.
 *
 * ---------------------------------------------------------------- SCORE LADDER (measured)
 *   70  `o` local, plain `for (i = 1; i < 12; i++)` over `o->unk28[i]`, no `r` pointer
 *   64  `o` local + `r = &o->unk28[i]`, i from 1
 *   63  `o` local + `r = &o->unk28[i + 1]`, i from 0   (frame becomes exact here)
 *   12  >>> macro cast instead of the `o` local, `r = &O->unk28[i + 1]`, i from 0 < 11,
 *       test spelled `O->unk28[i + 1].unk0` and the call argument spelled `r->unk0`
 *       (golden really does load that word twice, from two different IVs)   <-- PARKED
 *   12  identical with an extra `arr = O->unk28;` base local (IDO coalesces it away)
 *   62  recast as `s32 *p` walking by 3 with `p[3]/p[4]/p[5]` + a `q = &p[3]` (n=32/35)
 *   98  the same without `q` (n=28/35)
 *
 * ---------------------------------------------------------------- WHAT IS LEFT (ONE CAUSE)
 * WHERE THE INDUCTION VARIABLE IS BASED:
 *      golden: addiu $s2,$a0,40   (= &O->unk28[0])   then  lw $t6,12($s2)
 *              addiu $s0,$s2,12   (s0 DERIVED FROM s2)
 *      ours:   move  $s2,$a0                          then  lw $t6,52($s2)
 *              addiu $s0,$a0,52   (s0 derived from arg0 instead)
 * Same addresses, different split: IDO folds our `0x28 + 12*(i+1)` into the load offset and
 * bases the IV at arg0; golden bases it at the array and keeps +12 as the offset.  An
 * explicit `arr = O->unk28` base local does NOT survive (rematerialised).  The remaining
 * rows are that plus the knock-on schedule: golden's `beql` delay slot holds the first
 * `sw $zero,0($s1)` and the three stores precede the three `addiu` increments, while ours
 * puts `addiu $s3,$s3,12` in the delay slot and sinks the stores below the increments.
 * Fixing the IV base should bring the schedule with it.
 */
#define O ((Obj151B1918 *)arg0)

void func_151B1918(struct260 *arg0) {
    Rec151B1918 *r;
    s32 i;

    O->unk28[0].unk8 = 0;
    O->unkB8 = 0.0f;
    for (i = 0; i < 11; i++) {
        r = &O->unk28[i + 1];
        if (O->unk28[i + 1].unk0 != NULL) {
            func_1516972C((struct102 *)r->unk0);
        }
        r->unk0 = NULL;
        r->unk4 = 0;
        r->unk8 = 0;
    }
}
