/* tools/nearmiss/func_15040A78.c -- game_6D800, jtbl block 23D420
 *
 * STATUS: 128, n=148/148, frame -0xB8 and array base 0x64 -- BOTH NOW EXACTLY GOLDEN'S.
 *
 * *** THE FRAME LAW CLOSED THE LAST 8 BYTES: GOLDEN DECLARES TWO MORE LOCALS. ***
 * The func_15113218 park measured a law that applies directly here: under -O2 -g3 IDO gives
 * EVERY declared automatic a stack home whether or not it is ever spilled, so the frame reads
 * out the declared-local total. Ours: locals region 0x28..0xB0 = 0x88. Golden: 0x28..0xB8 =
 * 0x90. Eight bytes = two more 4-byte locals. Adding two took 131 -> 128 and moved the frame
 * to -0xB8.
 *
 * *** AND THIS TIME THE LAYOUT IS RIGHT, WHICH IS THE WHOLE DIFFERENCE FROM THE TRAP. ***
 * The stack[23]/[25] traps also reached frame 0xB8 -- with the array based at 0x5C against
 * golden's 0x64. Checked explicitly here: we now emit `addiu $t1, $sp, 0x64`, against golden's
 * `addiu $t2, $sp, 0x64`. Same base, only the register differs. ALWAYS check the base, not the
 * total.
 *
 * WHAT IS ESTABLISHED IS THE COUNT, NOT THE IDENTITY. Two extra locals is right; which two is
 * not yet distinguished. Giving case 0xDB its own word pair (below) is honest -- a distinct
 * variable per case is ordinary decompiled C and both are genuinely used -- but a variant with
 * one real and one UNUSED spare scores 128 as well, as do both alternative declaration
 * positions. So the frame is indifferent to which two locals they are; only the emitted code
 * can settle it, and 128 rows of register allocation still stand between here and that.
 * DO NOT ship the unused-spare form: an unused local is frame padding and is banned.
 *
 * *** THE "EXTRA LOCALS ARE THE HOISTED CONSTANTS" THEORY IS REFUTED. ***
 * It was attractive because it explained two symptoms with one cause: golden materialises
 * 0xFFFFFF (lui+ori) and 0x80000000 (lui) in the loop PREHEADER and re-materialises them after
 * the handler call, filling delay slots where we emit `nop` (structdiff: ours[30]=nop vs
 * gold[31]=lui $t4,0x8000) -- and two named locals holding them would also supply the missing
 * 8 bytes of frame. Measured, against a 131 control in the same sweep:
 *      mask + phys as locals, set before the loop ....... 128, frame -0xB8
 *      same, declared before the array .................. 128
 *      same, assigned at the top of the loop body ....... 128
 *      mask only (one extra local) ...................... 131, frame -0xB0
 * Identical to the w2/w3 form. Naming the constants does NOT make IDO hoist them, so the
 * hoisting and the frame are INDEPENDENT problems and only the frame is solved.
 *
 * NET: 128 is a plateau that ANY two extra locals reach. The frame law fixes the frame and
 * nothing else; the remaining 128 rows are register allocation plus the preheader scheduling.
 *
 * SUPERSEDED: 131, n=148/148 (exact length), frame -0xB0 vs golden -0xB8.
 *
 * *** `op` IS AN int, NOT A u8.  172 -> 131 AND THE LENGTH BECAME EXACT. ***
 * The opcode byte is read with `lbu` either way, but the VARIABLE's width decides where it
 * lives: golden keeps it in $s1, a CALLEE-SAVED register, across the handler call, whereas a
 * u8 local gets a memory home in IDO and ours spilled it to 0x33($sp) and reloaded it. That
 * cost a saved register (golden saves s0/s1/s2/ra, we only had s0/s1/ra) plus the store and
 * reload around the call. Measured: u8 -> 172 at frame -0xA8 with n=145; s32/u32/s16 all ->
 * 131 at frame -0xB0 with n=148/148. Only the u8-vs-wider boundary matters; declaration
 * position for `op` is byte-neutral (all 10 positions score 131).
 *
 * REFUTED AT THE SAME TIME: golden spills `active` with `sb`/`lbu` at 0x62($sp), which reads
 * like a u8 local. It is not -- s32/u8/s8/u32 for `active` ALL score identically. A byte-wide
 * spill is not by itself evidence of a byte-wide variable.
 *
 * *** REFUTED AT THE NEW BASELINE (all measured with a 131 control in the same sweep) ***
 * The park's earlier "REFUTED" list was measured against the u8-op baseline of 191/172. That
 * baseline was wrong, so those refutations did not carry and were all re-run. Result: they
 * still hold, and several more with them. Every one of these scores exactly 131:
 *     inverting the segment test so `depth--` is the else
 *     swapping the addend order, or the `| 0x80000000` operand order
 *     inlining `(w1 >> 24) & 0xF` instead of keeping `seg` as a local
 *     every width for `active` (u8/s8/u32/s16 -- see below)
 *     stack[22]
 * Worse: handler hoisted into a `void (*h)(s32)` local -> 145. case 1 unguarded -> 194.
 *
 * *** `op = *p` IS **NOT** UNCONDITIONAL.  MEASURED: 131 -> 175, n=148 -> 144. ***
 * Reading the opcode outside `if (active != 0)` looked strongly supported: golden puts
 * `lbu $s1, 0x0($s0)` in the DELAY SLOT of the active test, we emit a `nop` there, and we
 * additionally carry `lw $s1, 0x38($sp)` before the loop plus `sw $s1, 0x38($sp)` in the
 * epilogue -- a memory home IDO hands out to a variable read before it is written. All three
 * pointed the same way and all three were wrong. IDO will SPECULATE a safe load into a delay
 * slot it would otherwise fill with a nop, so a delay-slot load says nothing about whether
 * the source read is conditional. Do not re-derive this argument; measure instead.
 *
 * *** THE stack[23] TRAP -- SAME SHAPE AS THE OLD stack[25] TRAP. ***
 * stack[23] and stack[24] BOTH reach golden's exact frame (-0xB8) and BOTH score 128. The
 * tie is the tell: a real size cannot be indifferent to one more entry. 23 words seats the
 * base at 0xB8-0x5C = 0x5C, against golden's `addiu $t2, $sp, 0x64`. The array is 21 words
 * (0xB8 - 0x64 = 0x54); the missing 8 bytes are TEMPS below it, as before.
 *
 * SUPERSEDED STATUS: 172, n=145/148, frame -0xA8. Structure is RIGHT: every case body
 * reproduces, including the one that looked hardest (see THE EMPTY LOOP below). Residual is
 * 16 bytes of frame + 5 instructions + local scheduling around case 0xDE.
 *
 * FILE KIND: BODY SPLICE into conker/src/game_6D800.c over
 *   #pragma GLOBAL_ASM("asm/nonmatchings/game_6D800/func_15040A78.s")
 * then: python3 tools/fastscore.py game_6D800 func_15040A78 <spliced.c>
 *
 * WHAT IT IS: an F3DEX2 DISPLAY-LIST WALKER. That identification is what makes the whole
 * function readable, so start from it:
 *   - D_800C6860[16] is the SEGMENT TABLE. The prologue fills all 16 entries with -1
 *     ("unset") and then sets entry 0 to 0, which is the standard segment-0 = physical rule.
 *   - D_800844B0[] is a PER-OPCODE HANDLER TABLE, already declared in variables.h:376 as
 *     `extern void (*D_800844B0[])(s32 arg0);` -- call it with the (s32)-cast pointer.
 *   - the switch is on the opcode byte *p, and the jump table covers 0xDA..0xDF
 *     (`op - 0xDA`, range-checked against 6). Opcodes 0 and 1 are handled by compares
 *     BEFORE the table (`slti $at, $s1, 2`) -- IDO split one sparse switch into a compare
 *     cluster plus a table, so do NOT write two switches.
 *
 * DECODED CASE BODIES (jtbl order is the SOURCE case order; text order is the body order):
 *   0xDF  G_ENDDL   : p = stack[--depth];
 *   0xDE  G_DL      : stack[depth++] = p + 8; w1 = p[1];
 *                     seg = (w1 >> 24) & 0xF;
 *                     if (D_800C6860[seg] == -1) depth--;          // segment unset: skip
 *                     else p = ((w1 & 0xFFFFFF) + D_800C6860[seg]) | 0x80000000;
 *   0xDB  G_MOVEWORD: if (((w0 >> 16) & 0xFF) == 6)                // 6 = G_MW_SEGMENT
 *                         D_800C6860[(s32)(w0 & 0xFFFF) >> 2] = w1;
 *                     p += 8;
 *   1     G_VTX     : see THE EMPTY LOOP; p += 8;
 *   0xDA, 0xDC, default: p += 8;
 *
 * *** THE EMPTY LOOP -- IT IS REAL, DO NOT "FIX" IT ***
 * Case 1 counts `n = (w0 >> 12) & 0xFF` and then runs a loop with NO BODY. Golden really
 * does emit ~15 instructions of empty loop: a `n & 3` prologue that increments by 1, then a
 * main loop incrementing by 4 -- IDO's 4x unroll of `for (i = 0; i < n; i++) {}`. It looks
 * like a decompilation error and it is not. Written as a plain empty `for`, it reproduced
 * INSTRUCTION-FOR-INSTRUCTION on the first try (verified in the side-by-side). IDO did not
 * delete it because the induction variable survives.
 *
 * THE LOOP CONDITION is a disjunction, and the order matters:
 *      } while ((p <= arg2) || (depth > 0));
 * golden: `sltu $at,$s2,$s0 ; beql $at,$zero,<top>` then `bgtzl $a3,<top>` -- two separate
 * likely-branches back to the top, which is exactly what `||` emits here.
 *
 * ARGUMENTS: (start, mark, end). `mark` is homed at 0xBC and compared against p each
 * iteration to turn the handler calls ON; `end` turns them OFF again. So the walker executes
 * the whole list but only DISPATCHES between mark and end.
 *
 *
 * ---------------------------------------------------------------- PERMUTER RUN 2026-08-22
 * 18,699 iterations, MAX_FRAME=184, selftest PASS. 13 outputs. PARKED SCORE UNCHANGED at 191
 * -- nothing was adopted, and the reasons are worth keeping.
 *
 * *** THE PERMUTER'S RANKING IS INVERTED IN-FILE. CONFIRMED TWICE NOW. ***
 * Re-scored with fastscore inside the real TU (its own scores are the left column):
 *      3447 (its BEST) -> 166      4388 -> 141 (its 6th)     5811 -> 163
 *      3657 -> 184                 4944 -> 147               7220 -> 170
 *      4166 -> 183                 5371 -> 162               7430 -> 191 (= base)
 *      4194 -> 182                 4262 -> 152
 * Its top-ranked output is mid-table in reality; its SIXTH is the best. The same inversion
 * happened on func_1518BD60. TREAT THE output-<n> ORDER AS NOISE and re-score every output.
 *
 * *** ITS BEST CANDIDATE (141) IS BUILT ENTIRELY ON TWO FORCERS -- REJECTED. ***
 *   (1) `op = 0; for (i = op; ...); D_800C6860[op] = op;`  -- the OPCODE variable reused as a
 *       zero holder, before it has been assigned an opcode. Semantically meaningless.
 *   (2) `new_var = &(*((u32 *)(p + 4))); w1 = *new_var;` -- address-of-a-dereference, the
 *       textbook pointer-laundering forcer.
 * A regex screen over all 13 outputs for known forcer shapes (&(*x), a variable reused as a
 * constant, split shifts, volatile) flagged 4388 AND ONLY 4388 -- so the single best-scoring
 * candidate was also the only dishonest one. That is not a coincidence worth ignoring: on
 * this residue the permuter buys points mainly by laundering registers.
 *
 * NOT ADOPTED, PENDING REVIEW: output-4944 scores 147 and is clean of every forcer pattern
 * screened for. Its change is honest in KIND -- it drops the `p` cursor local and walks with
 * the `arg0` parameter directly, which is ordinary C and plausibly the original spelling.
 * It was NOT taken because the diff leaves `p` referenced after its initialiser is removed,
 * and a candidate whose correctness has not been established must not be parked as a
 * near-miss.
 *
 * *** THE HAND RE-DERIVATION WAS DONE, AND IT REFUTES THE 147. ***
 * Rewritten honestly -- `p` deleted outright and the walk done on the `arg0` parameter --
 * it scores 189 at frame -0xA0, against the parked 191 at -0xA8 and golden -0xB8. So the
 * honest form of that change is worth 2 points and moves the frame FURTHER from golden. The
 * permuter's 147 therefore did not come from the substitution that was visible in the diff;
 * it came from whatever else that candidate did, very possibly the same unverified `p` use
 * that stopped it being adopted. NOTHING FROM THIS RUN WAS ADOPTED and 191 stands.
 *
 * The lesson to carry: a permuter score is only a claim about a candidate, never about the
 * IDEA inside it. Re-derive the idea by hand before believing the number transfers.
 *
 * *** EVERY TABLE ENTRY WITH ITS OWN EMITTED BODY NEEDS ITS OWN `case` BLOCK. ***
 * 191 -> 172 (n=143 -> 145/148) purely by adding `case 0xDD:` with its own `p += 8; break;`.
 * The 7-entry table maps 0xDA/0xDC/0xDD to THREE SEPARATE bodies (.L15040C88/.L15040C90/
 * .L15040C98) even though all three are identical, so IDO emitted three blocks; letting 0xDD
 * fall into `default` collapsed two of them. Measured:
 *      case 0xDD as its own block ...................... 172   <- parked
 *      0xDA/0xDC/0xDD grouped into one block ........... 210   (n=141/148, WORSE)
 *      no explicit 0xDD (falls through to default) ..... 191
 * Position within the switch made NO difference (172 either way) -- only separateness did.
 * Same lesson as func_150403C8, where writing out all 77 cases was worth 187 -> 180 AND moved
 * the frame. Decode the table; give every distinct target its own block.
 *
 * ---------------------------------------------------------------- PERMUTER RUN 2026-08-23
 * Base 128 (frame -0xB8, base 0x64, n=148/148 -- all golden's), gated with
 * PERMUTER_TU_REQUIRE_FRAME=184. selftest PASS on all five controls, including (e): the same
 * C compiled in ISOLATION produces different bytes than in-TU, so the TU-aware harness is
 * load-bearing here. 25 minutes, ~4 new outputs.
 *
 * *** NOTHING BEATS 128. The best candidate re-scores 141. ***
 * Re-scored in-file with tools/nearmiss/_permrescore.py (its own score in brackets):
 *      4388 -> 141 [FORCER]   4362 -> 142   4944 -> 147   4262 -> 152   3832 -> 153
 *      3487 -> 155   5371 -> 162   5811 -> 163   3447 -> 166   7220 -> 170   4166 -> 183
 *      4194 -> 182   3657 -> 184   7430 -> 191   3572 -> 199
 * THE INVERSION HELD FOR A THIRD TIME: its best-named output (3447) is mid-table at 166, and
 * the best in-file (4388) is ALSO THE ONLY ONE FLAGGED FOR A FORCER (`&(*p)` laundering).
 * Same pattern as func_1518BD60 and the 2026-08-22 run. Score every output; screen every one.
 *
 * *** TRAP: `rm -rf permuter_tu/<func>` CLEANS NOTHING. ***
 * setup reports "contains a space; using /tmp/conker_permuter_tu" because the repo path has a
 * space in it -- IDO cc cannot write to such a path. So the working directory is
 * /tmp/conker_permuter_tu/<func>, and a clean of conker/permuter_tu/<func> silently leaves the
 * PREVIOUS run's outputs in place. Eleven of the outputs above are from 2026-08-22 and
 * re-score to exactly the numbers that run recorded; only 3487/3572/3832/4362 are new. Delete
 * the /tmp path, and read setup's own output for where it actually put things.
 *
 * *** TRAP: an output's source.c is a WHOLE pycparser file, not the region. ***
 * compile.sh takes everything after the line containing PERMUTER_SPLICE_MARKER. Splicing the
 * whole file onto tu_head.c duplicates the prelude, nothing compiles, and the forcer screen
 * fires on 100% of candidates because the prelude declares vu8/vu16/vu32. A screen that flags
 * every candidate is reporting a harness bug, not a fleet of dishonest candidates.
 *
 * REMAINING WORK
 * 1. FRAME: golden 0xB8, ours 0xA8 -- 16 bytes short.
 *
 *    *** A TRAP, MEASURED: `stack[25]` REACHES FRAME 0xB8 AND IS WRONG. ***
 *    Sizing the array to 25 words gives frame=-0xB8 (exact) and drops 191 -> 189, so it
 *    reads like progress. It is not: 25 words is 0x64 bytes, so the array lands at
 *    0xB8-0x64 = 0x54, whereas golden's base is 0x64 (`addiu $t2, $sp, 0x64`). Right total,
 *    wrong layout -- the 2 points came from somewhere else entirely. stack[26] scores the
 *    same, which is the tell: a real size would not be indifferent to +1 entry.
 *
 *    The array IS 21 words: 0xB8 - 0x64 = 0x54, and it is the topmost local. The missing 16
 *    bytes are compiler TEMPS BELOW it -- golden's temp region is 0x28..0x63 (0x3C) against
 *    our 0x28..0x53 (0x2C). Golden spills the active-flag to 0x62 and the depth to 0x48
 *    across the handler call. Get more values genuinely live across that call; do not pad,
 *    and do not resize the array to make the total come out.
 *
 *    ALSO REFUTED (all 191, n=143/148): inverting the segment test so `depth--` is the else;
 *    hoisting the handler into a `void (*h)(s32)` local; stack[20] and stack[22].
 * 2. The stream is 2 instructions out of phase around case 0xDE's "segment unset" branch --
 *    golden ends that branch with `b ; addiu $a3,$a3,-1` in the delay slot. Front-to-back:
 *    fix this before anything later, it is the first divergence.
 * 3. BOTH functions of this block must be live C before the yaml line moves; the other is
 *    func_150403C8 (217 words, 77-entry table). See NOTES_game_6D800_block.md.
 */

void func_15040A78(u8 *arg0, u8 *arg1, u8 *arg2) {
    u8 *stack[21];
    u8 *p;
    s32 depth;
    s32 active;
    u32 w0;
    u32 w1;
    s32 seg;
    s32 n;
    s32 i;
    u32 w2;
    u32 w3;
    s32 op;

    for (i = 0; i < 16; i++) {
        D_800C6860[i] = -1;
    }
    D_800C6860[0] = 0;

    depth = 0;
    active = 0;
    p = arg0;
    if (arg2 < arg0) {
        return;
    }

    do {
        if (p == arg1) {
            active = 1;
        }
        if (active != 0) {
            op = *p;
            D_800844B0[op]((s32)p);
        }
        if (p == arg2) {
            active = 0;
        }
        switch (op) {
        case 0xDF:
            depth--;
            p = stack[depth];
            break;
        case 0xDE:
            stack[depth] = p + 8;
            w1 = *(u32 *)(p + 4);
            depth++;
            p = p + 8;
            seg = (w1 >> 24) & 0xF;
            if (D_800C6860[seg] == -1) {
                depth--;
            } else {
                p = (u8 *)(((w1 & 0xFFFFFF) + D_800C6860[seg]) | 0x80000000);
            }
            break;
        case 0xDB:
            w2 = *(u32 *)p;
            w3 = *(u32 *)(p + 4);
            if (((w2 >> 16) & 0xFF) == 6) {
                D_800C6860[(s32)(w2 & 0xFFFF) >> 2] = w3;
            }
            p += 8;
            break;
        case 1:
            if (active != 0) {
                n = (*(u32 *)p >> 12) & 0xFF;
                for (i = 0; i < n; i++) {
                }
            }
            p += 8;
            break;
        case 0xDA:
            p += 8;
            break;
        case 0xDC:
            p += 8;
            break;
        case 0xDD:
            p += 8;
            break;
        default:
            p += 8;
            break;
        }
    } while ((p <= arg2) || (depth > 0));
}
