/* game_20A290 / func_151DCDE0 -- SOURCE-COMPLETE (scores 0), BLOCKED ON RODATA MIGRATION.
 * Wave 61. Was parked at 240; the residual is gone, the C is written, and the only thing
 * standing between this and a match is one line of conker.us.yaml owned by the other lane.
 *
 * HAND-OFF, one line:
 *     conker.us.yaml:1497    - [0x250010, rodata]
 *                     ->     - [0x250010, .rodata, game_20A290]
 * then re-run splat --modes ld. Today build/conker.ld places only
 * `build/src/game_20A290.c.o(.text)`; every other section of that object falls into
 * `/DISCARD/ : { *(*); }`, so a C-emitted literal pool is thrown away and its relocations
 * resolve to nothing. That is the ONLY reason the pragma is still in the tree.
 *
 * The full source is in the block comment at the top of conker/src/game_20A290.c.
 *
 * WHAT WAS WRONG. The 0.2f shared by unk30 and unk34 was modelled as `extern f32
 * D_800AB558`. It is a FLOAT LITERAL, and the pool's own ordering proves it:
 *
 *     800AB550  .word  0x00000010     addressed object, passed as &
 *     800AB554  .float 1.0            addressed object, passed as &
 *     800AB558  .float 0.2            <- filled unk30/unk34, the THIRD fp field assigned
 *     800AB55C  .float -0.693         <- filled unk24, the FIRST fp field assigned
 *     800AB560  .float 0.304
 *     800AB564  .float 25.714
 *
 * IDO emits anonymous float literals in order of FIRST APPEARANCE IN THE SOURCE. 0.2f sits
 * ahead of -0.693f even though its field is assigned later, which is only possible if 0.2f
 * appears earlier in the text than any other literal -- i.e. in the initialiser of the local
 * declared at the top:  `f32 sp28 = 0.2f;`.
 *
 * THAT ALSO EXPLAINS THE 240. IDO schedules a literal-pool load as a constant and hoists it
 * into the PROLOGUE, between `addiu sp` and `sw ra`; an `extern` load is an ordinary memory
 * reference and stays in the body. The 4-instruction placement that no extern spelling could
 * reach was never a scheduler tie -- it was the compiler telling us the value's provenance.
 *
 * MEASURED (asm-differ -o, no -R):
 *      0   literals + `f32 sp28 = 0.2f`  -- and the emitted pool comes out in the ROM's
 *          exact order at .rodata +0/+4/+8/+0xc
 *    240   same shape, values as `extern f32`
 *    240   ditto as `extern const f32` with a const-qualified callee prototype (const inert)
 *    240   `sp2C.unk34 = sp2C.unk30 = sp28;`
 *    442   local declared BEFORE the struct -- scalars and aggregates share ONE pool, so the
 *          struct slides to sp+0x28 and `addiu a0,sp,0x2c` breaks
 *    880   no local, both fields read the symbol directly
 *   1052   local left unused, both fields read the symbol directly
 *
 * WHEN MIGRATING: D_800AB550 (0x10) and D_800AB554 (1.0f) are ADDRESSED, so they must come
 * back as two named objects declared ahead of the function, in that order, so the pool still
 * begins with them and the four literals follow.
 *
 * GENERAL LESSON. A rodata pool is EVIDENCE, not just data. Its ordering is the compiler's
 * record of the order the constants were first written in the source, so a pool entry that
 * sits earlier than its use tells you a local initialiser exists -- and a constant that
 * golden schedules earlier than you can reach is a hint that you have modelled a literal as
 * an extern. Worth checking on every fp near-miss whose residual is "golden loads it sooner".
 */
