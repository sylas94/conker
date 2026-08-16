/* ============================================================================
 * func_150825C0  (game_AEB40.c)  --  C L O S E D,  2026-08-13 WAVE 3.
 * 1560 -> 95 -> 30 -> 0.  The matching C is LIVE in conker/src/game_AEB40.c;
 * the #pragma GLOBAL_ASM is gone.  Verified: score 0 with -R and without -R,
 * size 924 == golden 924, and objcopy of .text/.rodata/.data against
 * expected/build/src/game_AEB40.c.o is IDENTICAL (13936 / 0 / 0 bytes) -- that
 * compare covers every other function in the TU, so nothing previously live
 * was lost.  No rodata migration was needed (this TU has no .rodata at all).
 *
 * ================= THE LEVER THAT CLOSED IT, AND HOW IT WAS FOUND ===========
 * Wave 2 ended at 30 with the ENTIRE integer body byte-identical and four FP
 * rows left:
 *     golden  mul.s $f0,$f0,$f0 / mul.s $f2,$f2,$f2 / add.s $f6,$f0,$f2
 *                                                   / c.le.s $f6,$f12
 *     ours    mul.s $f6,$f0,$f0 / mul.s $f4,$f2,$f2 / add.s $f8,$f6,$f4
 *                                                   / c.le.s $f8,$f12
 * Same opcodes, same sources, same slots; golden squares IN PLACE and we take
 * fresh registers.  Wave 2 had proved this was a pure FP-temp count difference
 * (our block allocates 11 fp temps, golden 9) and had concluded, from a single
 * experiment, that "golden has exactly ONE named f32 variable" and therefore
 * that no declaration could produce the in-place form.
 *
 * BOTH HALVES OF THAT CONCLUSION WERE WRONG, and the way to find out was not to
 * search source spellings but to ASK THE ALREADY-MATCHED CODE.  Disassemble
 * every expected/build/src/*.c.o, keep the functions that have no
 * #pragma GLOBAL_ASM anywhere in src/ (i.e. the ones whose C is live and
 * verified), and grep them for `mul.s $fN,$fN,$fN'.  Two of the hits sit in the
 * SAME FILE and give the contrast directly:
 *
 *   game_83300  func_1505A6F8   -- IN PLACE
 *       f32 x, z;
 *       x = arg0->x_position - arg1->x_position;   x *= x;
 *       z = arg0->z_position - arg1->z_position;   z *= z;
 *       return sqrtf(x + z);
 *     -> sub.s $f2,.. / sub.s $f12,.. / mul.s $f2,$f2,$f2 / nop
 *        / mul.s $f12,$f12,$f12 / add.s $f0,$f2,$f12
 *        i.e. golden func_150825C0's cluster instruction for instruction,
 *        NOP INCLUDED.
 *
 *   game_83300  func_1505693C   -- NOT in place
 *       temp_f0 = temp_f0 * temp_f0;                    -> mul.s $f0,$f0,$f0
 *       if ((temp_f2 * temp_f2) + (temp_f12 * temp_f12) < temp_f0)
 *                                                       -> mul.s $f6,$f2,$f2
 *                                                          mul.s $f8,$f12,$f12
 *
 * THE LAW: a square written INLINE inside a larger expression allocates a fresh
 * fp temp for the product; a SELF-ASSIGNMENT to a named f32 local (`d = d * d;'
 * or `d *= d;') reuses the operand's register.  It is the statement form, not
 * the operand's spelling, that decides -- writing the subtraction twice
 * (`(a-b)*(a-b)') does not help, because uopt's CSE temp for `a-b' is not the
 * kind ugen will overwrite.
 *
 * AND THE FRAME OBJECTION WAS ALSO WRONG.  Wave 2 believed sum(sizeof(local))
 * is pinned at 16 by the home area 0x40..0x4f, so no new local could be added.
 * A local declared LAST lands in the compiler-temp slack below the home area
 * and the frame does not move:
 *     rad,i,t,ok,flags,j + `f32 dx; f32 dz;' LAST ..... 0, frame 0x50, 924 B
 *     the two loop counters merged onto `i',
 *       then `f32 dx; f32 dz;' LAST ................... 0, frame 0x50, 924 B
 *       (byte-identical output -- the two declaration lists are
 *        indistinguishable from the binary; the shipped source keeps `j')
 *     `f32 dx; f32 dz;' declared FIRST .............. 66, frame 0x58
 * Declaration ORDER is what matters, not the count.  This is the same fact that
 * took func_150D1C30 from 445 to 400 in the same wave.
 *
 * THE SHIPPED FORM (live in conker/src/game_AEB40.c):
 *     dx = D_800CC2D0[j].x_position - spawn.unk6;   dx = dx * dx;
 *     dz = D_800CC2D0[j].z_position - spawn.unkA;   dz = dz * dz;
 *     if (dx + dz <= rad) { ok = 0; break; }
 * Note the term order is X FIRST here.  Wave 2 measured "x-term written first"
 * at 550 -- that was for the INLINE-EXPRESSION shape, where the canonicalisation
 * runs the other way.  Do not carry that number across to this shape.
 *
 * LOAD-BEARING TEST (both locals deleted, distance test reverted to the single
 * inline expression, everything else untouched): 30.  So dx and dz are
 * semantic, not frame shaping -- they carry the squared component distances and
 * are read by the comparison.
 *
 * ALSO STILL TRUE, all of it in the shipped source:
 *   - `arg1' (dead on entry: the timer block returns on every path) is the
 *     function's only spare int-width storage and is homed in the CALLER's arg
 *     slot, so carrying D_800BE9A0 in it costs no frame bytes.  That was the
 *     wave-2 lever, 230 -> 30.
 *   - `t' is a u16 reused for both the timer halfword and `flags & 6'; the
 *     ASSIGNMENT STATEMENT form of `t = flags & 6' is what produces golden's
 *     two register copies.
 *   - operand order: z-term-vs-x-term in the `&' and the final
 *     `(arg0 * 0x30) + (s32)D_800D20FC' so the last addu is `addu a0,s2,t4'.
 * ============================================================================ */
