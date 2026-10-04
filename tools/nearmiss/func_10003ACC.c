/* tools/nearmiss/func_10003ACC.c -- init_39C0, clear both framebuffers to an RGBA16 colour.
 *
 * FILE KIND: STANDALONE TU (a note; splice over the pragma in src/init_39C0.c).
 * STATUS 2026-08-24: mism=220 at the tree default, leaf, n=81/65 -- 16 instructions TOO MANY.
 * First attempt; the semantics are settled, the residue is one optimiser decision.
 *
 * THE BODY (best of three spellings, "walk then walk"):
 *   void func_10003ACC(s32 r, s32 g, s32 b) {
 *       s32 i; u16 *p; s32 n;
 *       n = (D_800BE620 * D_800BE624 * 2) >> 1;
 *       p = (u16 *) D_8002AAE8[0];
 *       if (p != 0) {
 *           for (i = 0; i < n; i++) { *p++ = COL; }
 *           p = (u16 *) D_8002AAE8[1];
 *           for (i = 0; i < n; i++) { *p++ = COL; }
 *       }
 *   }
 *   COL = ((r << 8) & 0xF800) | ((g << 3) & 0x7C0) | ((b >> 2) & 0x3E) | 1
 *
 * SETTLED FROM GOLDEN, not guessed:
 *   * n is `(w*h*2) >> 1`, NOT `w*h`. Golden emits `sll $t8,$v0,1` then `sra $t0,$t8,1` --
 *     the source really does form the byte size (the same expression the matched sibling
 *     func_100039C0 passes to allocate_memory) and shift it back. Note `>> 1`, not `/ 2`:
 *     a signed divide would emit the srl-31 / addu / sra bias sequence, which golden lacks.
 *   * The colour is RECOMPUTED in both blocks, not CSE'd -- golden builds the same
 *     sll/andi/or chain twice, once per loop.
 *   * The NULL check covers both loops: `beqz $v1, <epilogue>` on D_8002AAE8[0] exits the
 *     whole function, so the second loop is inside the same `if`.
 *   * D_8002AAE8 is already `extern s32 D_8002AAE8[2]` in include/variables.h -- cast at the
 *     use rather than redeclaring it, or the TU will not compile.
 *   * The TU NEEDS A PROTOTYPE: func_100039C0 calls func_10003ACC before its definition, so
 *     without one the implicit `int` declaration collides with the real signature. The
 *     original source must have had it.
 *
 * *** THE BLOCKER: IDO UNROLLS BOTH LOOPS, GOLDEN UNROLLS ONLY THE SECOND. ***
 * Golden's first loop is a plain 5-instruction pointer walk:
 *      .L10003B30: addiu $t2,$t2,1 ; slt $at,$t2,$a3 ; addiu $v1,$v1,2 ; bnez $at ; sh $v0,-0x2($v1)
 * while its second is unrolled x4 with an `n & 3` remainder loop in front (the
 * `andi $a1,$t0,0x3` / `beqz` prologue). Ours unrolls both, which is the whole +16.
 * Spellings tried: walk/walk 220 (n=81), walk/indexed 260 (n=85), indexed/indexed 383 (n=97)
 * -- so the second loop wants the POINTER-WALK spelling too, and the open question is only
 * what stops IDO unrolling the FIRST one.
 *
 * *** A LENGTH TRAP -- READ BEFORE CHASING THE SCORE. ***
 * Spelling loop 1 as a pointer-compare while:
 *      { u16 *e = p + n; while (p < e) { *p++ = COL; } }
 * scores 64 with n=65/65 -- the EXACT golden length, better than any counted form. It is
 * WRONG anyway. Golden's loop 1 is unambiguously a COUNTED loop:
 *      blez  $t0, .L10003B48        guard on the count, not on a pointer
 *      or    $a3, $t0, $zero
 *   .L10003B30:
 *      addiu $t2,$t2,1 ; slt $at,$t2,$a3 ; addiu $v1,$v1,2 ; bnez $at ; sh $v0,-0x2($v1)
 * and golden zeroes the counter (`or $t2,$zero,$zero`) up at instruction 7, before the NULL
 * check. The pointer-compare form emits `sltu $at,$v1,$a0` instead and has no counter at all.
 * It reaches the right length by coincidence. This is the same class of trap as the "second
 * parameter" note in func_150C7670.c: n matching is necessary, not sufficient.
 * Full sweep of loop-1 spellings (loop 2 held as a for-walk): for-walk 220 n=81,
 * while-walk 220 n=81, countdown 105 n=69, do-while 209 n=49, pointer-compare 64 n=65.
 *
 * So the real question stands unchanged: BOTH loops are `for (i = 0; i < n; i++) *p++ = COL;`
 * and only the SECOND unrolls. Ours unrolls both.
 *
 * NEXT: this is a good candidate for the corpus method that cracked the eeprom pair --
 * tools/nearmiss/_findb.py style. Look for MATCHED functions containing two similar loops
 * where only one is unrolled, and read what differs between them in the C. Do not reach for
 * `volatile` to suppress the unroll; that changes the semantics and is a forcer.
 */
