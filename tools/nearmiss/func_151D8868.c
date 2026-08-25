/* game_205C90 / func_151D8868  -- 444 bytes, frame 0x30, s0-s3 saved.
 *
 * BEST HONEST SCORE: fastscore mism=2, n=111/111.  Frame exact, EVERY register and EVERY
 * stack offset correct.  The only two differing words are one delay-slot pair:
 *      ours:   beqzl $t0, .L151D890C+4   /  lw $t1, 0x0($s2)
 *      gold:   beqz  $t0, .L151D890C     /  nop
 * (An earlier run that was killed by an API limit reported "mism=2, only a beql/nop pair" --
 *  that was THIS target, not the cross product.)
 *
 * Progression, all measured: 87 -> 24 -> 11 -> 4 -> 2.  Three structural unlocks:
 *   1. 87->24  the two in-loop tests SHARE one `return NULL` tail, so they are ONE `if`
 *              with `||`, not two separate `if`s:
 *                  if ((func_15181CC8(i) == 0) || (func_1517EF00(i) != 0)) return NULL;
 *              Two separate ifs duplicate the `b .L151D8A08 / or v0,zero,zero` tail
 *              (+2 instructions) and flip a bnez to a beqz.
 *   2. 24->11  the two loops use DIFFERENT variables.  Sharing one index pair across both
 *              loops forces loop 2's shift index into a saved register; golden has it in
 *              $v1, which only happens if its live range is confined to loop 2.  Loop 2
 *              keeps the file's own established idiom (matched func_151D8B24, same TU).
 *   3. 11->2   loop 1 has ONE named `u8` counter, not the two-s32 idiom.  `u8 i;` with a
 *              plain `i++` produces golden's three-instruction tail
 *                  addiu s1,s1,1 / andi s0,s1,0xFF / or s1,s0,zero
 *              (IDO keeps the untruncated value in i's register and the truncated one in a
 *              CSE temp) and it is the only form that gets the two `or ?,zero,zero` inits
 *              into golden's ORDER ($s1 then $s0) as well as into the right registers.
 *
 * THE 2 REMAINING ROWS ARE THE DOCUMENTED as1 BRANCH-LIKELY PEEPHOLE, NOT CODEGEN.
 * ugen emits "beqz $t0,L / nop" on both sides; the ASSEMBLER as1 then optionally rewrites
 * it to "beqzl $t0,L+4" by copying the instruction at L into the taken-only delay slot (the
 * copy at L stays, so the object size is unchanged -- exactly our 111/111).  as1 converted
 * for us and declined for golden.  See tools/ido_cookbook.md, sections "FOURTH RESIDUAL
 * CLASS: an ASSEMBLER peephole" and "The as1 peephole gate is NOT a function of the local
 * instruction pattern": a scan of all 464 golden objects found 8,451 conversions against
 * 950 honest declines (10.3%) with NO discriminator, and a hand-built probe whose local
 * window matched golden instruction-class for instruction-class CONVERTED where golden
 * DECLINED.  func_150D1C30 is a standing bail at 400 on exactly this class.
 * The one steerable lever the cookbook records (func_150FF840) is "what starts your
 * FALL-THROUGH block" -- but here the fall-through is "b .L151D8A08 / or v0,zero,zero", a
 * branch, on BOTH sides, so there is no fall-through filler to deny.
 *
 * RE-CONFIRMED AND NARROWED (bounded re-look; score re-measured in-TU at mism=2,
 * n=111/111, so the 2 is pure content -- this golden .s carries no trailing pad nops and
 * needs no length correction).  One hypothesis that the cookbook's corpus scan could not
 * have seen was tested and REFUTED: that the decision depends on TU CONTEXT, which
 * asm-processor changes (the original build assembled real C for the whole TU; ours
 * assembles placeholder bodies for the neighbouring #pragma GLOBAL_ASM functions).  Five
 * probes -- every other pragma deleted, a dummy function prepended (which also moves this
 * function's address in .text), a dummy appended, a second branchy guard function
 * prepended, and full isolation -- ALL still emit beqzl, with mism=2 and the same four
 * branch-likely instructions.  So the conversion is neither context- nor position-
 * dependent.
 *
 * WHAT THAT LEAVES, STATED PRECISELY.  as1 is deterministic, so if it saw the same input
 * on both sides it would decide the same way; our object is byte-identical to golden
 * apart from these two words.  Therefore the difference is UPSTREAM of the assembler --
 * it is in information ugen passes down (its block structure) that leaves no trace in the
 * instruction stream.  And a source edit can only reach that by changing something the
 * instruction stream does NOT show, which nothing in the 10 loop forms, 4 declaration
 * positions, 12 initialisation spellings or 120 declaration-order permutations already
 * swept does.  Any edit that DOES show up breaks an otherwise-exact match.
 * VERDICT: NOT REACHABLE FROM SOURCE.  Standing bail at 2, same class as func_150D1C30.
 * MEASURED INERT against this residual: 10 loop forms (while / for / for with split init /
 * for with the increment in the body / reversed comparison / "< n + 1" / explicit guarded
 * do-while / (s32) cast on the global / ++i / i += 1), hoisting "i = 0" above the guard
 * chain, and all 4 declaration positions of i.  Mechanism-backed park, not a plateau.
 *
 * OTHER THINGS MEASURED AND REJECTED -- DO NOT REPEAT:
 *   * two-s32-variable idiom for LOOP 1 (i++; j = (i = (u8) i);): floor 4, never lower.
 *     Swept 12 initialisation spellings (i=0;j=0 / j=0;i=0 / i=j=0 / j=i=0 / i=0;j=i /
 *     j=0;i=j / i=0;j=(u8)i / declaration initialisers both orders / for-init comma both
 *     orders / declaration order both ways) x 5 increment spellings x while/for.  The
 *     coupling is rigid: whichever variable is written first takes $s0, but golden wants
 *     the counter written FIRST and in $s1.  Only collapsing to one named u8 breaks it.
 *   * 120 declaration-order permutations of {temp_v0,i,j,k,m}: completely inert (all 11).
 *   * guard spellings for the D_800BEAC0..3 chain: "x != 0" chain and bare "x" chain are
 *     identical; splitting D_800BEAC3 into its own if costs +2 instructions (102);
 *     inverting to && with a trailing return NULL costs 78.
 *   * u32 i -> 181 (no truncation, 8 instructions short); casting every use of an s32
 *     counter ((u8) i or (i & 0xFF)) -> 64-70, +1 instruction.
 *
 * TYPES pinned from the matched near-twin func_1513418C (game_161520.c), which calls the
 * same allocator identically: func_15167A68(id, arg3, arg1 + off, 1, (u8) arg2, 1), then
 * "if (== NULL) return NULL;", then memcpy(dst_field, arg0, n).  Callers all declare
 * func_151D8868(void *, s32, s32, s32) (game_129EE0.c:61, game_200930.c:426, ...).
 *
 * The block below REPLACES the single remaining
 *   #pragma GLOBAL_ASM("asm/nonmatchings/game_205C90/func_151D8868.s")
 * in conker/src/game_205C90.c.  Nothing else in that TU changes.
 */
extern u8 D_800BEAC2;
extern u8 D_800BEAC3;
extern s32 func_15181CC8(s32);
extern s32 func_1517EF00(s32);
extern void *func_15167A68(s32, s32, s32, s32, s32, s32);

typedef struct {
    u8 pad0[0xE];
    u8 unkE[4];
    u8 unk12;
    u8 unk13;
    u8 pad14[2];
    u8 unk16;
} Struct151D8868;

void *func_151D8868(void *arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 i;
    Struct151D8868 *temp_v0;
    s32 k;
    s32 m;

    if (D_800E0B94 != 0) {
        return NULL;
    }
    if (func_151D87E0(((u8 *)arg0)[5]) == 0) {
        return NULL;
    }
    if ((D_800BEAC0 != 0) || (D_800BEAC1 != 0) || (D_800BEAC2 != 0) || (D_800BEAC3 != 0)) {
        return NULL;
    }

    i = 0;
    while (i <= D_80082FA0) {
        if (((u8 *)arg0)[5] & (1 << i)) {
            if ((func_15181CC8(i) == 0) || (func_1517EF00(i) != 0)) {
                return NULL;
            }
        }
        i++;
    }

    temp_v0 = func_15167A68(0x3F, arg3, arg1 + 0x18, 1, (u8) arg2, 1);
    if (temp_v0 == NULL) {
        return NULL;
    }
    memcpy(&temp_v0->unkE, arg0, 8);
    k = 0;
    m = 0;
    do {
        if (temp_v0->unk13 & (1 << m)) {
            func_1501C010((u8) k, ((u8 *)arg0)[4]);
        }
        k++;
        m = (k = (u8) k);
    } while (m < 4);
    temp_v0->unk16 = ((u8 *)arg0)[4];
    return temp_v0;
}
