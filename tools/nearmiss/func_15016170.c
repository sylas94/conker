/*
 * PARKED NEAR-MISS -- func_15016170  (game_43620.c, 320 B, 77 real words + 3 pad,
 * frame 0x28).  Only pragma left in game_43620.c; closing it retires the TU.
 *
 * BEST: fastscore mism=62, n=77/80 (the 3 are 16-byte function-alignment nops
 * that golden carries and we do not, worth a flat +30; the REAL residual is
 * 32 rows).  Instructions 0..35 are byte-identical.
 *   Measure with: python3 tools/fastscore.py game_43620 func_15016170 <cand.c>
 *
 * ============================================================== BEST SOURCE
 *   extern void func_151F3C34(void *);
 *
 *   void func_15016170(s32 arg0) {
 *       s32 idx;
 *       s16 tmp;
 *
 *       bzero(&D_800E0D80, 160);
 *       D_800E0D80.unk8  = (s32)alHeapDBAlloc(0, 0, (ALHeap *)arg0, 1, 80);
 *       D_800E0D80.unk74 = (s32)alHeapDBAlloc(0, 0, (ALHeap *)arg0, 1, 1088);
 *       D_800E0D80.unk5C = (s32)alHeapDBAlloc(0, 0, (ALHeap *)arg0, 1, 8);
 *       D_800E0D80.unkC  = 64;
 *       D_800E0D80.unk96 = 64;
 *       D_800E0D80.unkE  = 0x7FFF;
 *       D_800E0D80.unk84 = 0;
 *       D_800E0D80.unk88 = 0x7FFF;
 *       D_800E0D80.unk9A = 0;
 *       D_800E0D80.unk32 = 0;
 *       D_800E0D80.unk30 = 0;
 *       D_800E0D80.unk94 = D_800E0D80.unk96;
 *       idx = D_800E0D80.unkC;
 *       tmp = D_800E0D80.unkE;
 *       D_800E0D80.unk10 = (D_8002BC10[idx]  * tmp) >> 15;
 *       D_800E0D80.unk12 = (D_8002BD0E[-idx] * tmp) >> 15;
 *       D_800E0D80.unk24 = 1;
 *       D_800E0D80.unk14 = 0x7FFC;
 *       D_800E0D80.unk16 = 0;
 *       func_151F3C34(func_151F3C4C);
 *   }
 *
 * ============================== TWO RESIDUALS THAT CANCEL IN THE LENGTH COUNT
 * This is why n is 77 on BOTH sides even though the streams differ by two
 * separate one-instruction facts.  Do not read the equal length as "only
 * register names differ".
 *
 * RESIDUAL 1 -- the 0x7FFF twins (golden has one MORE instruction here).
 *   golden:  addiu t1,zero,0x7FFF ; addiu t9,zero,0x7FFF
 *            sh t1,0xE(s0)        ; sw t9,0x88(s0)
 *   ours:    one register feeds both the sh and the sw.
 *   That is -1 instruction AND -1 temp consumed, which rotates t0..t9 by one for
 *   the rest of the function and accounts for most of the 32 rows.
 *
 * RESIDUAL 2 -- -(idx*2) vs (-idx)*2 (ours has one MORE instruction here).
 *   golden CSEs the scaled index and negates the SCALED value:
 *       sll t2,v1,1  (shared with the D_8002BC10[idx] access)
 *       ... negu t6,t2 ; lui t7,%hi(D_8002BD0E) ; addu t7,t7,t6 ; lh t7,%lo(..)(t7)
 *   `D_8002BD0E[-idx]` instead builds (-idx)*2:  negu t4,v1 ; sll t5,t4,1.
 *
 * ==================================== HYPOTHESIS KILLED THIS WAVE (was tempting)
 * "IDO's constant CSE is TYPE-KEYED, which is why 0x40 is shared between two
 * `sh` stores but 0x7FFF is not shared between an `sh` and a `sw`."
 * FALSE.  include/structs.h struct186 already declares unkE as s16 and unk88 as
 * s32 -- the two stores ALREADY have different types in our source and IDO CSEs
 * them anyway.  Do not spend another wave on constant typing.
 *
 * RULED OUT (all byte-identical to the base at 62 unless noted):
 *   - `32767` instead of `0x7FFF` for unk88
 *   - an extra named `s16 vol;` local holding 0x7FFF for the unkE store.  Note
 *     this does NOT grow the frame: idx(4)+tmp(2)+vol(2) still fits the 8 local
 *     bytes at 0x18..0x1F, so the -g3 local-slot lever (see func_150C71C0's
 *     note) is EXHAUSTED here -- the frame already accounts for every byte.
 *   - `*(s16 *)((s32)D_8002BD0E - idx * 2)` byte-offset form for residual 2 (84,
 *     worse: it materialises the pointer with lui+addiu+subu instead of the
 *     %hi/%lo+negu form)
 *   - and everything in the earlier note: (s16)0x7FFF, 0x7FFFU, statement
 *     reordering, no temps at all, D_8002BD0E[0 - idx], D_8002BC10[127 - idx]
 *     (D_8002BD0E is exactly D_8002BC10+254), -(idx*1), idx as s16, and
 *     `*(D_8002BD0E - idx)` / `*(D_8002BC10 + idx)` (54 but wrong pointer form).
 *
 * SOLVED, KEEP THESE:
 *   - func_151F3C34 takes ONE argument.  a1 (=unkE) and a2 (=64) at the call
 *     site are leftover live values, not arguments; the mips_to_c draft's 3-arg
 *     call is wrong.  game_21FC90.c defines it as `void func_151F3C34(s32)`; a
 *     file-local prototype is needed because functions.h does not declare it.
 *   - struct186 in structs.h already has every field; no header work required.
 *   - `multu` + `sra 15` is just IDO's 32-bit multiply; the fields are signed.
 *
 * ============================================ PERMUTER (2245 iterations, -j 8)
 * selftest PASS, base 585 on the permuter's scale.  Best reached: 410.  Neither
 * of its two leading candidates is adoptable, but ONE of them contains a real,
 * separable hypothesis:
 *   - 420: `int new_var = (D_8002BD0E[-idx] * tmp) >> 15; D_800E0D80.unk12 = new_var;`
 *     -- a banned unnecessary temporary, and it does not close anything.
 *   - 410: `struct186 *new_var = &D_800E0D80; bzero(new_var, 160);` (a forcer --
 *     a pointer local that exists only to launder the global) PLUS a genuine
 *     idea: RE-READ `D_800E0D80.unkC` in the second index instead of reusing the
 *     cached `idx`.
 * That second idea, tested ALONE and honestly, is a real if small gain:
 *     D_800E0D80.unk12 = (D_8002BD0E[-D_800E0D80.unkC] * tmp) >> 15;   -> 59 (from 62)
 *     both indices re-read from the field                              -> 62
 * So golden re-reads unkC for the NEGATED index only.  That is the first thing
 * to move this function in several waves; build on it rather than on `idx`.
 *
 * REOPEN WITH: the 59 variant as the new base, re-seeded into the permuter.  The
 * func_150163D0 lesson from this wave is that the permuter is a LOCAL search --
 * it went 2039 iterations to 355 from the wrong basin and then hit 0 in 1604
 * from the right one, so re-seeding from 59 is worth more than more CPU on 62.
 * Left as #pragma GLOBAL_ASM.  NOT FAKED.
 */
