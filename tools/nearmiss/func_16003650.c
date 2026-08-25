/* ============================================================================
 * func_16003650  (debugger_258ED0.c)  --  PERMANENT BAIL, NOT A NEAR-MISS.
 * 2026-08-21.  40 words / 160 bytes.  Single-pragma TU.
 *
 * DO NOT PUT THIS BACK IN A WORK QUEUE.  This file exists only so the next wave
 * that picks func_16003650 off a size-ranked list stops in 30 seconds instead of
 * spending a wave on it.  There is NO C reconstruction below because no C source
 * compiled by IDO 5.3 can emit these bytes.  The claim is now MEASURED, not
 * asserted -- see PROOF.
 *
 * ================= WHAT THE FUNCTION IS =====================================
 * A debugger TLB dump.  It walks all 32 TLB entries and fans each one out into
 * four parallel 32-word arrays:
 *     mtc0 $t0,$0        write CP0 Index  = i
 *     tlbr               read that TLB entry into EntryLo0/1, EntryHi, PageMask
 *     mfc0 $t1,$2   -> D_160038AC[i]      (CP0 $2  EntryLo0)
 *     mfc0 $t2,$3   -> D_1600392C[i]      (CP0 $3  EntryLo1)
 *     mfc0 $t3,$10  -> D_160039AC[i]      (CP0 $10 EntryHi)
 *     mfc0 $t4,$5   -> D_16003A2C[i]      (CP0 $5  PageMask)
 * The four destinations are 0x80 apart (0x38AC + 0x80 = 0x392C + 0x80 = 0x39AC
 * + 0x80 = 0x3A2C), i.e. four adjacent u32[32] arrays -- consistent with the
 * loop and with 32 TLB entries.  Semantics are fully understood; that is not
 * the blocker.
 *
 * ================= WHY IT IS UNREACHABLE FROM C =============================
 * 6 of the 40 words are coprocessor-0 instructions that IDO 5.3 has no way to
 * emit from any C construct: 1x mtc0 (40880000), 1x tlbr (42000001), 4x mfc0
 * (40091000 / 400A1800 / 400B5000 / 400C2800).  A further 5 words are `addi`
 * (trapping add: 21080001, 20840004, 20A50004, 20E70004, 20C60004); IDO emits
 * `addiu` for every induction-variable and pointer increment it has ever been
 * observed to produce in this tree.  9 more words are CP0 hazard-delay nops
 * placed by hand around the mtc0/tlbr/mfc0 sequence.  spimdisasm independently
 * flags the whole routine `/* Handwritten function *(/` and tags each CP0 op
 * `handwritten instruction`.  It is the ONLY function in the entire nonmatchings
 * corpus that contains a CP0 instruction:
 *     grep -rl 'tlbr|mtc0|mfc0|tlbwi|tlbp' conker/asm/nonmatchings/  ->  1 file
 * (29 files carry the "Handwritten function" banner; this is the only CP0 one.)
 *
 * ================= PROOF: THE THREE ESCAPE HATCHES ARE MEASURED SHUT ========
 * All three run against the real ../ido/ido5.3_recomp/cc with the tree's CFLAGS.
 *
 *  1. asm("tlbr");        COMPILES, and that is the trap.  IDO 5.3 has no
 *     inline-asm construct at all, so it parses this as an ordinary CALL to an
 *     undefined external function named `asm` taking a string literal:
 *         8:  3c040000  lui  a0,0x0     R_MIPS_HI16 .rodata
 *         c:  0c000000  jal  0          R_MIPS_26   asm      <-- a real reloc
 *        10:  24840000  addiu a0,a0,0   R_MIPS_LO16 .rodata
 *     i.e. it emits a jal to a symbol `asm` plus a .rodata string.  Anyone who
 *     sees "it compiled" and stops has produced a link error, not a match.
 *  2. __asm__("tlbr");    Identical -- same `jal asm` + .rodata string.
 *  3. #pragma asm / #pragma endasm (the IRIX MIPSpro spelling) is NOT recognised
 *     by this front-end.  The pragma body is fed to the C parser verbatim:
 *         cfe: Error: line 5: Unknown character $ ignored
 *          \tmtc0\t$8, $0
 *         cfe: Error: line 5: Syntax Error
 *     Both at file scope and inside a function body.  No object is produced.
 *
 * ================= THE FLOOR, FOR THE RECORD ================================
 * The closest measurable C is the loop SCAFFOLDING with the four mfc0 reads
 * replaced by four extern u32 loads (dishonest by construction -- it is only a
 * yardstick, it is not a candidate):
 *
 *     extern u32 D_160038AC[32], D_1600392C[32], D_160039AC[32], D_16003A2C[32];
 *     extern u32 D_CP0_2, D_CP0_3, D_CP0_10, D_CP0_5;
 *     void func_16003650(void) {
 *         u32 *p0 = D_160038AC, *p1 = D_1600392C;
 *         u32 *p2 = D_160039AC, *p3 = D_16003A2C;
 *         s32 i = 0;
 *         do { *p0 = D_CP0_2; *p1 = D_CP0_3; *p2 = D_CP0_10; *p3 = D_CP0_5;
 *              i++; p0++; p1++; p2++; p3++; } while (i != 32);
 *     }
 *
 * DO NOT REPEAT -- measured with tools/fastscore.py (flag-overridden):
 *     -O2 -g3   mism=238  frame=leaf  n=60/40
 *     -O2       mism=238  frame=leaf  n=60/40
 *     -g        mism=200  frame=-24   n=56/40
 *     -O1       mism=160  frame=-24   n=52/40   <- best, and structurally capped
 * Even at the floor the length is wrong (52 vs 40) and 6 words are opcodes the
 * compiler cannot spell.  There is no gradient to follow here.
 *
 * ================= VERDICT ==================================================
 * BAIL.  The #pragma GLOBAL_ASM in conker/src/debugger_258ED0.c is permanent and
 * should be excluded from near-miss / single-pragma-TU rankings, exactly like
 * the other 28 "Handwritten function" bodies.  Reclassifying it out of
 * asm/nonmatchings/ would be a tooling change (splat yaml + progress accounting),
 * not a decompilation, and is out of scope here.
 * ========================================================================== */
