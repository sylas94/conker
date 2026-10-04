/* tools/nearmiss/func_150403C8.c -- game_6D800, jtbl block 23D420 (SCOUT ONLY, no C yet)
 *
 * STATUS: SCOUT. Shape measured, body not yet decoded, nothing compiled or scored. Recorded
 * so the next pass starts from the shape rather than from a cold read of 217 instructions.
 *
 * WHY IT MATTERS: it is the SECOND of the two functions owning rodata block 23D420. The
 * migration
 *      - [0x23D420, rodata]  ->  - [0x23D420, .rodata, game_6D800]
 * needs BOTH live C, and the other one (func_15040A78, an F3DEX2 display-list walker) is
 * already at 191 with its whole structure reproducing -- see tools/nearmiss/func_15040A78.c.
 * So this function is the sole remaining blocker on that block.
 *
 * MEASURED SHAPE
 *      217 instructions / 868 bytes      frame 0x50 (small -- most state is in registers)
 *      jump table jtbl_80098960, 77 entries, but only 12 DISTINCT targets
 *      NO indirect calls (no jalr) -- unlike func_15040A78, which dispatches through
 *          D_800844B0[]. This one branches instead.
 *      globals: D_8003C8E0  D_800848B0  D_800BE9C0  D_800C6860  D_800C68A0  D_800C68A1
 *      callees: func_10007DA0 func_15040754 func_1504082C func_150408CC func_15040CC8
 *               func_150AD770
 *
 * *** IT IS RECURSIVE -- IT CALLS ITSELF. ***
 * `func_150403C8` appears in its own callee list. Together with the shared segment table
 * D_800C6860 (the same global func_15040A78 fills with -1 and indexes by segment number),
 * that makes this the RECURSIVE display-list walker of the pair: where func_15040A78 keeps
 * an explicit `stack[21]` of return addresses and loops, this one recurses on G_DL. Expect
 * the recursion to be the thing that shapes the frame, and do not try to model it as a loop.
 *
 * THE JUMP TABLE IS THE MAP. 77 entries over 12 targets means a wide opcode range with heavy
 * fall-through to a few shared bodies -- the histogram is:
 *      29 -> .L15040648        (the default/skip body)
 *      21 -> .L150405A0
 *      11 -> .L150405EC
 *       7 -> .L15040640
 *       2 -> .L150405F4
 *       1 each -> .L150405FC .L150405E4 .L150405D4 .L150405C4 .L150405AC .L15040598
 *                 .L15040488
 * Decode the table to function-relative offsets FIRST and write the `case` labels grouped by
 * target, in the order the BODIES appear in .text -- IDO emits case bodies in source order,
 * so the body order is a direct readout of the original `switch`. That is what made
 * func_1518BA90's 9-entry switch fall out on the first try.
 *
 * METHOD REMINDERS (already paid for elsewhere, do not rediscover)
 *  * Match with the jump table still EXTERNAL and flip the yaml LAST -- once the table is
 *    local the .text relocation stops naming the external symbol and asm-differ can only ever
 *    show a residual.
 *  * A stack object's size is set by the FRAME, not by the offsets its stores span; IDO seats
 *    the topmost local at frame_end - sizeof. Both 24BED0 functions needed a struct 8 bytes
 *    larger than their stores implied.
 *  * Do not resize an array to make a frame total come out -- see the stack[25] trap recorded
 *    in tools/nearmiss/func_15040A78.c.
 *  * The ROM sha1 is the only valid acceptance test for a migrated jtbl function.
 */

/* ---------------------------------------------------------------- MEASURED 2026-08-23
 * STATUS: 179, n=217/217, frame -0x58 vs golden -0x50 (8 bytes OVER).
 *
 * *** THE ENTRY TEST IS ONE MERGED BLOCK, NOT TWO. 180 -> 179. ***
 * Golden does not branch straight to `done`. It falls through the `*p == -0x21` test into the
 * arg1 guard, where `beqz $t8` reaches `done` because arg1 is already known to be 0:
 *      if ((arg1 != 0) || (*(s8 *)p == -0x21)) {
 *          if (arg1 == 0) goto done;
 *          if ((u32)arg0 >= arg1) return;
 *      }
 * Behaviourally identical to the two-test form, one byte closer. TAKEN.
 *
 * *** THE FRAME SURPLUS IS DIAGNOSED, AND THE OBVIOUS FIX IS REFUTED TWICE. ***
 * Golden keeps w1 -> the sum -> target ALL in $s0 across the G_DL case, and keeps `ret` at
 * 0x40($sp). We do the opposite: we spill w1 to 0x40 AND target to 0x48 around the calls, and
 * hold `ret` in $s6. Two memory temps instead of one is exactly the 8-byte surplus, and it is
 * also why we emit `nop` in two delay slots where golden reloads `ret` -- golden can use
 * `beql`/`bnel` there precisely because a memory-resident `ret` gives it something to put in
 * the slot.
 *
 * That reads like "w1 and target are one variable in the source". THEY ARE NOT:
 *      w1/target merged .............................. 210, frame -0x40, n=215/217
 *      merged, named `target` instead ................ 210
 *      merged + case -0x25 given its OWN local ....... 210   <- the obvious objection, tested
 *      merged + merged entry test .................... 210
 * The merge does not shorten a live range, it DELETES the locals region altogether. $s0 being
 * reused for all three values is IDO coalescing adjacent live ranges, which it does without
 * being asked. Do not re-derive this; it has now been measured four ways.
 *
 * ALSO BYTE-NEUTRAL (all 179, frame unmoved): `ret` as u32; `ret` at every declaration
 * position; inverting `if (ret != 0)` into an empty-then/else; case -0x25 with its own local.
 *
 * SUPERSEDED ------------------------------------------------------- MEASURED 2026-08-22
 * mism=180, n=217/217 -- EXACT INSTRUCTION COUNT on the first candidate that compiled.
 * frame -0x40 vs golden -0x50: 16 bytes short. Structure (loop condition, the switch, the
 * recursion, the two flush tails) is therefore correct; the rest is frame + allocation.
 *
 * *** A REAL HEADER BUG WAS FIXED TO GET HERE, AND IT IS BYTE-NEUTRAL ***
 * `func_150408CC` was declared AND defined `void`, but golden's caller stores its $v0
 * (`sw $v0, 0x40($sp)` right after the jal). It is a one-line tail call to func_1504072C,
 * which returns s32 -- and game_6D800.c:44 already uses `return func_1504072C(...)` in a
 * matched sibling, so the void was simply a decompilation shortcut that happened to match.
 * Changed BOTH functions.h and the definition to s32 + `return`, then PROVED byte-neutrality
 * by disassembling func_150408CC out of the real TU object before and after: identical, all
 * 9 instructions. Without this the caller cannot capture the value at all.
 *   -> the check is scratchpad/jt1/neutral.py; re-run it if the definition is ever touched.
 *   -> NOTE the first run of that check reported "NOT NEUTRAL". It was a FALSE NEGATIVE: only
 *      the definition had been changed, so it clashed with the still-void header declaration
 *      and failed to compile. A compile failure is not a neutrality verdict. Change the
 *      declaration and the definition together.
 *
 * REMAINING: 16 bytes of frame. Golden's locals run 0x40..0x4F; ours is just the 4-byte
 * `ret` at 0x40. Find the real stack-resident locals -- do NOT pad, and do not resize
 * anything to make the total come out (see the stack[25] trap in func_15040A78.c).
 *
 * FRAME ATTEMPTS THAT DID NOTHING (all stayed at -0x40, n=217/217):
 *      named `s8 op` local, switched on ......... 187  <- taken, honest, but frame unmoved
 *      named `s32 seg` for the segment index .... 189
 *      both together ........................... 187
 *      `arg1 ?` instead of `arg1 != 0 ?` ....... 189
 * DECLARING MORE LOCALS DOES NOT MOVE THIS FRAME. All four spellings left it at 0x40.
 *
 * *** THE FRAME IS NOW DIAGNOSED EXACTLY -- read this before touching it again. ***
 * The prologues are IDENTICAL: ra 0x3C, fp 0x38, s7..s0 at 0x34..0x18 in BOTH. So the
 * outgoing-argument area is the same in both and the whole 16-byte gap is the LOCALS region
 * that sits above the saved registers:
 *      golden: locals 0x40..0x4F (16 bytes), of which only `ret` at 0x40 is used
 *      ours:   NO locals region at all -- ra at 0x3C is the top, frame closes at 0x40
 * i.e. GOLDEN KEEPS `ret` MEMORY-RESIDENT (`sw $v0,0x40($sp)` ... `lw $t0,0x40($sp)`) WHILE
 * WE KEEP IT IN A REGISTER. That is the entire difference. An earlier guess that golden
 * reserved a six-word outgoing area is REFUTED by the identical prologues -- do not chase it.
 *
 * So the task is not "find a missing local", it is "make `ret` spill". IDO spills a local to
 * memory when it is live across calls and every callee-saved register is already committed.
 * Golden commits nine: s0=target, s1=p, s2=&D_800BE9C0, s3=1, s4=flush, s5=&D_8003C8E0,
 * s6=0xC00005B, s7=&D_800C68A1, fp=&D_800C68A0. Get all nine of those live simultaneously
 * and `ret` has nowhere to go but the stack. Do NOT declare padding to buy the 16 bytes.
 *
 * *** ALL 77 CASES MUST BE WRITTEN OUT, INCLUDING THE 29 EMPTY ONES. ***
 * The first version listed only the cases that DO something and scored 187 -- but it emitted
 * `addiu $t9,$v0,0x25 / sltiu $at,0x11`, a SEVENTEEN-entry table, against golden's
 * `addiu $t0,$t9,0x2D / sltiu $at,0x4D`. The table width is set by the lowest and highest case
 * LABEL, so every case in the range has to exist even when its body is empty. Writing all 77
 * took 187 -> 180 and, just as importantly, moved the frame -0x40 -> -0x58 (golden -0x50):
 * the extra cases supplied the register pressure that was missing, and `ret` now spills.
 * The frame is now 8 bytes OVER rather than 16 under -- a different problem, and a better one.
 *
 * The 77 entries decode to twelve groups (index = case value + 0x2D). Body order in .text is
 * the SOURCE case order, which is what the switch below follows:
 *      -0x22            G_DL (the big one, with the recursion)
 *      -0x19            D_800C68A0 = 0
 *      21 cases         D_800C68A0 = 1   (-0x1C -0x1B -0xA 0x6 0x7 0x10..0x1F)
 *      0x5              ret = func_1504082C(p); D_800C68A0 = 1
 *      0x1              ret = func_15040754(p)
 *      -0x3             D_800848B0 = p[1]
 *      -0x1 / 11 cases / 2 cases    flush = 1   -- THREE separate groups, same body, emitted
 *                                   separately by IDO, so they must stay three `case` groups
 *      -0x25            G_MOVEWORD segment write
 *      0x9..0xF + default           D_8003C8E0 = 0xC00005B; func_150AD770()
 *      29 cases         empty -- `break;` only, listed LAST (their target is the common tail)
 *
 * NOTE the case VALUES in the 187 version were partly wrong even though it scored well:
 * func_1504082C is case 0x5 (not -0x1B) and func_15040754 is case 0x1 (not -0x1A). An exact
 * instruction count does not mean the case values are right -- decode the table, do not guess.
 *
 * ---------------------------------------------------------------- PERMUTER RUN 2026-08-22
 * MAX_FRAME=88, selftest PASS, 4 outputs. NOTHING ADOPTED -- all are worse than the parked
 * 180 in-file:
 *      output-5345 -> 189 (n=216/217)     output-6700 -> 201 (n=216/217)
 *      output-5470 -> 205, frame -0x50    <- GOLDEN'S EXACT FRAME, but via `volatile`
 *
 * *** THE volatile CANDIDATE IS A FORCER AND IS REJECTED -- BUT IT CONFIRMS THE DIAGNOSIS. ***
 * It is the only variant that reached golden's 0x50 frame, and it did so by forcing a value
 * to be MEMORY-RESIDENT. That is an independent confirmation, from a search that knew nothing
 * of the theory, that the frame difference is exactly "golden keeps `ret` in memory, we keep
 * it in a register". So the remaining work is to find an HONEST reason for `ret` to live on
 * the stack -- enough simultaneous live values that the allocator has no register left --
 * not to declare it volatile. Do not ship the volatile form; it buys the frame and still
 * scores 205, worse than the honest 180.
 *
 * FIRST RUN OF THIS SEARCH PRODUCED ZERO CANDIDATES: MAX_FRAME was set to golden's 80 while
 * the base frame is 88, so the gate rejected the base itself and every descendant. Set
 * MAX_FRAME to the BASE frame, not the target frame.
 */

s32 func_15040754(struct148 *arg0);
void func_15040CC8(u8 *arg0);
void func_10007DA0(void);

void func_150403C8(void *arg0, u32 arg1, s32 arg2) {
    u8 *p;
    s32 ret;
    s32 flush;
    u32 target;
    u32 w0;
    u32 w1;
    s32 idx;
    s32 cnt;
    s8 op;

    ret = 0;
    p = (u8 *)arg0;
    if ((arg1 != 0) || (*(s8 *)p == -0x21)) {
        if (arg1 == 0) {
            goto done;
        }
        if ((u32)arg0 >= arg1) {
            return;
        }
    }

    do {
        flush = 0;
        op = *(s8 *)p;
        switch (op) {
        case -0x22:
            w1 = *(u32 *)(p + 4);
            ret = func_150408CC((struct148 *)p);
            target = ((w1 & 0xFFFFFF) + D_800C6860[(w1 >> 24) & 0xF]) | 0x80000000;
            cnt = D_800C68A1 + 1;
            D_800C68A1 = cnt;
            if ((cnt & 0xFF) == 0x14) {
                func_15040CC8(p);
                D_8003C8E0 = 0xC00005B;
                func_150AD770();
            }
            if ((target >= 0x80000001U) && (target < 0xA0000000U) && ((target & 7) == 0)) {
                func_150403C8((void *)target, 0, (s32)p);
            } else {
                func_15040CC8(p);
                D_8003C8E0 = 0xC00005B;
                func_150AD770();
                D_800BE9C0 = 1 - D_800BE9C0;
                func_10007DA0();
                D_800BE9C0 = 1 - D_800BE9C0;
            }
            if ((s32)(s8)D_800C68A1 > 0) {
                D_800C68A1 = D_800C68A1 - 1;
            } else {
                D_8003C8E0 = 0xC00005B;
                func_150AD770();
                D_800BE9C0 = 1 - D_800BE9C0;
                func_10007DA0();
                D_800BE9C0 = 1 - D_800BE9C0;
            }
            break;
        case -0x19:
            D_800C68A0 = 0;
            break;
        case -0x1C: case -0x1B: case -0xA: case 0x6: case 0x7: case 0x10: case 0x11: case 0x12:
        case 0x13: case 0x14: case 0x15: case 0x16: case 0x17: case 0x18: case 0x19: case 0x1A:
        case 0x1B: case 0x1C: case 0x1D: case 0x1E: case 0x1F:
            D_800C68A0 = 1;
            break;
        case 0x5:
            ret = func_1504082C((u32 *)p);
            D_800C68A0 = 1;
            break;
        case 0x1:
            ret = func_15040754((struct148 *)p);
            break;
        case -0x3:
            D_800848B0 = *(u32 *)(p + 4);
            break;
        case -0x1:
            flush = 1;
            break;
        case -0x1E: case -0x1D: case -0x14: case -0x13: case -0x12: case -0x9: case -0x8:
        case -0x7: case -0x5: case -0x4: case -0x2:
            flush = 1;
            break;
        case -0x16: case -0x15:
            flush = 1;
            break;
        case -0x25:
            w0 = *(u32 *)p;
            w1 = *(u32 *)(p + 4);
            if (((w0 >> 16) & 0xFF) == 6) {
                idx = (s32)(w0 & 0xFFFF) / 4;
                D_800C6860[idx] = w1;
            }
            break;
        case 0x9: case 0xA: case 0xB: case 0xC: case 0xD: case 0xE: case 0xF:
        default:
            D_8003C8E0 = 0xC00005B;
            func_150AD770();
            break;
        case -0x2D: case -0x2C: case -0x2B: case -0x2A: case -0x29: case -0x28: case -0x27:
        case -0x26: case -0x24: case -0x23: case -0x21: case -0x20: case -0x1F: case -0x1A:
        case -0x18: case -0x17: case -0x11: case -0x10: case -0xF: case -0xE: case -0xD:
        case -0xC: case -0xB: case -0x6: case 0x0: case 0x2: case 0x3: case 0x4: case 0x8:
            break;
        }

        if ((flush != 0) && (D_800C68A0 != 0)) {
            func_15040CC8(p);
            D_800C68A0 = 0;
            D_8003C8E0 = 0xC00005B;
            func_150AD770();
            D_800BE9C0 = 1 - D_800BE9C0;
            func_10007DA0();
            D_800BE9C0 = 1 - D_800BE9C0;
        }
        if (ret != 0) {
            func_15040CC8(p);
            ret = 0;
            D_8003C8E0 = 0xC00005B;
            func_150AD770();
            D_800BE9C0 = 1 - D_800BE9C0;
            func_10007DA0();
            D_800BE9C0 = 1 - D_800BE9C0;
        }
        p += 8;
    } while (arg1 != 0 ? ((u32)p < arg1) : (*(s8 *)p != -0x21));

done:
    ;
}
