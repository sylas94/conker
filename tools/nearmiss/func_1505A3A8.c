/* func_1505A3A8 (game_83300.c, 548 B) -- MEASURED score 20, wave 2026-08-11.
 *
 * SUPERSEDES the old whole-TU snapshot that used to live in this file (measured 1295, NOT
 * the "1" the backlog claimed; the old filename hint "v1_1295.c" was the honest number).
 * That snapshot was also DESTRUCTIVE -- it predated the match of func_1506045C and installing
 * it wholesale reverted that function to a stub. This file is now just the function.
 *
 * INSTALL: replace `#pragma GLOBAL_ASM(".../func_1505A3A8.s")` with the body below AND change
 * the forward declaration at the top of game_83300.c from
 *     f32  func_1505A3A8(f32 arg0, void *arg1, f32 arg2, f32 arg3, u8 arg4);
 * to
 *     void func_1505A3A8(f32 arg0, struct127 *arg1, f32 arg2, f32 arg3, u8 arg4);
 * (`void` is right: golden sets no return value before `jr ra`, and no live C caller in the
 * tree uses one.)
 *
 * RESIDUAL: exactly TWO rows, both register-only. Golden emits
 *     mul.s $f20,$f20,$f0   /  lui at,0x40a0  /  mul.s $f14,$f14,$f0
 * and this emits the two mul.s in the opposite order. Everything else -- all 137
 * instructions, the frame, the branch-likely delay slots, the stack layout -- is byte-exact.
 * Row census from `diff.py -o func_1505A3A8 -R --max-lines 4096`:
 *     2 register-only, 0 inserted, 0 deleted, 0 replaced.
 *
 * WHY IT IS STUCK (measured, do not re-probe blind):
 *   IDO homes the two incoming f32 parameters that arrive in a2/a3 into $f20 (callee-saved,
 *   paid for with sdc1/ldc1) and $f14, and **the SECOND-assigned of the two gets $f20**.
 *   Golden needs a2 in $f20, so a2 must be scaled SECOND -- hence `arg3` first here. But
 *   golden's two mul.s come out in the a2-then-a3 order, i.e. golden assigns a2 second yet
 *   emits its multiply first. IDO here emits multiplies in statement order and will not
 *   reorder these two, so the two requirements are mutually exclusive under every spelling
 *   tried. Writing them a2-first flips the whole $f20/$f14 map and costs 145 (score 165).
 *   Ruled out, each built and scored on this base:
 *     both statements on one source line (either order) - 20 / 165 (no reorder happens)
 *     `arg2 = arg2 * X;` plain form in either slot        - 25 / 25
 *     `X * arg2` reversed operands                        - 30
 *     `*D_800D1550` instead of `D_800D1550[0]`, both and mixed - 20 / 20 (inert)
 *     a named `f32 scale` local hoisting the load         - 20 (a3 first) / 165 (a2 first)
 *   3047 frame-gated decomp-permuter iterations from this exact base: no improvement.
 *
 * WHAT GOT IT FROM 1295 TO 20 -- four independent levers, each measured both ways:
 *   1. SCALE arg3 BEFORE arg2 (1295 -> 1015). Fixes the entry `mtc1 a2,$f20 / mtc1 a3,$f14`
 *      pair and every $f20/$f14 row downstream. See the rule above.
 *   2. In the in_water block, MULTIPLY BEFORE THE 2.0f STORE (-> 885 combined). Golden
 *      hoists `lui %hi(D_800994C0)` above the beqzl and materialises 2.0f after it; that is
 *      the emission order of `arg3 *= D_800994C0; arg2 = 2.0f;`, not the reverse.
 *   3. READ THE FIELD, NOT A CACHED LOCAL, on the RHS and in the guards (-> 230). Golden
 *      does `swc1 $f8,0x3c(a1)` immediately followed by `lwc1 $f10,0x3c(a1)` -- it stores
 *      and RELOADS. `obj->f = obj->f - x;` produces that reload; `obj->f = local - x;` lets
 *      IDO forward the stored value and drops the load. Confirmed against 339 live-C sites
 *      of the same idiom in the matched corpus (e.g. game_10CD70.c func_150DFDD0:201).
 *   4. DELETE the `speed` local entirely, reading `arg1->xz_velocity` in both sign tests
 *      (-> 20). This was the honest half of a permuter output; the same output's `int
 *      new_var = 1;` constant-pinning half is a banned forcer and was discarded.
 *
 * No banned constructs: no dummy labels, no volatile, no self-assignment, no dead locals
 * (this version has no locals at all), no no-op masks.
 *
 * ========== WAVE 2026-08-11b: THE TWO AXES SWEPT EXHAUSTIVELY -- BOTH FLAT ==============
 * The "mutually exclusive" verdict above rested only on RESPELLINGS; statement ORDER and
 * pairwise LINE JOINS had never been swept.  Both are now swept EXHAUSTIVELY, plus two new
 * families.  98 builds, each hard-built (object + asm-processor intermediate removed first,
 * `make` hard-failed on error) and scored with AND without -R; the two always agreed exactly.
 *
 * THE RESIDUAL IS NOT A REGISTER-ALLOCATION CONFLICT.  IT IS A SCHEDULER TIE-BREAK.
 * The note above says a2 must be scaled SECOND to win $f20, so golden's a2-first emission is
 * unreachable.  That framing is wrong in a way that matters.  With the -g3 line numbers that
 * asm-differ prints in the CURRENT column, the real invariant is:
 *        the mul.s writing $f14 is ALWAYS emitted BEFORE the mul.s writing $f20.
 * It held in 16 of 16 instrumented spellings, INCLUDING every form that puts both multiplies
 * on ONE line number.  In the shipped base the register MAP IS ALREADY GOLDEN'S
 * (mtc1 a2,$f20 / mtc1 a3,$f14, byte-identical); the sole divergence is that IDO emits
 * arg3's multiply first where golden emits arg2's first.  So the open question is not "how
 * do I get a2 into $f20" -- that is solved and shipped -- but "how do I make IDO schedule
 * the $f20 multiply first".  No source-level lever found so far touches that tie-break.
 *
 * AXIS 1 -- EXHAUSTIVE ORDER SWEEP of the three independent opening statements
 * (3 = `arg3 *= D_800D1550[0];`, 2 = `arg2 *= ...;`, G = the whole D_800CC27C guard block).
 * All 3! = 6 orderings built and scored:
 *        32G     20    <- shipped base, unique best
 *        3G2    480
 *        23G    165    (reproduces the old "a2-first costs 145" figure exactly)
 *        2G3    625
 *        G32   1735
 *        G23   1735
 * Law: the guard block must come third and arg3 must be scaled before arg2.  Nothing ties.
 *
 * AXIS 2 -- EXHAUSTIVE SINGLE-JOIN SWEEP.  Joining any two adjacent lines is always valid C
 * here (the body carries no // comments and no preprocessor lines), so all 64 adjacent line
 * pairs of the 65-line body were joined one at a time and scored:
 *        ALL 64 SCORED EXACTLY 20.  DEAD FLAT, no exceptions.
 * A greedy climb therefore has no first step to take.  IDO's line grouping has NO effect
 * anywhere in this function -- a real per-function property, not a general law.
 *
 * SCALE-PAIR SPELLING BATTERY (14 builds, each instrumented for the mtc1/mul rows):
 *         20  arg3 *= S; arg2 *= S;                          <- base
 *         30  both plain (arg3 = arg3 * S; arg2 = arg2 * S;)
 *         25  mixed compound/plain, either way round
 *        175  both plain, a2 first
 *         20  comma operator, ONE statement:  arg3 *= S, arg2 *= S;
 *        165  comma operator reversed
 *         20  both statements on ONE physical line (a3 first)
 *        165  ... a2 first
 *         25  nested comma:  arg2 = (arg3 *= S, arg2 * S);
 *        170  nested comma the other way round
 *         30  reversed operands (S * arg3)
 *         20  first scale joined onto the function's signature line
 *         20  second scale joined onto the guard's line
 * In EVERY one of these the $f14 mul precedes the $f20 mul.  The same-line and comma forms
 * give both multiplies the SAME -g3 line number and STILL do not reorder them.
 *
 * LOCALS ARE THE WRONG FAMILY -- ruled out properly (8 builds).  The pre-2026-08 whole-TU
 * snapshot used `f32 aa/bb` locals; on the CURRENT base (levers 1-4 applied) they are
 * catastrophic, so that shape can be abandoned for good:
 *       2786 / 2426  two locals aa+bb: both declaration orders x both assignment orders
 *        270 / 2296  one local for the arg2 role (assigned first / second)
 *        200 / 2366  one local for the arg3 role (assigned first / second)
 *
 * `register` IS INERT (6 builds).  This was the most promising remaining idea: the 23-order
 * base ALREADY has golden's mul emission order, so flipping only its register map would have
 * closed the function.  `register f32 arg2` / `register f32 arg3` / both, applied to the
 * 32-base and to the 23-base:  20/20/20 and 165/165/165 -- identical to unqualified in all
 * six cases.  IDO 5.3 at -O2 ignores the storage class for this decision.
 *
 * VERDICT (stronger than the previous bail, and differently aimed).  Residual 2 rows, 100%
 * register-only, 0 structural.  Both assigned axes are now EXHAUSTIVELY swept and both are
 * FLAT (the 6-ordering table above; 64/64 joins at exactly 20).  The blocker is a single
 * list-scheduler tie-break between two independent, equal-priority mul.s that IDO always
 * resolves toward the $f14 destination.  Re-open ONLY with a lever that acts on scheduling
 * priority rather than on source order or spelling.  Spellings, orders, joins, locals and
 * storage classes are all now measured dead.
 */
void func_1505A3A8(f32 arg0, struct127 *arg1, f32 arg2, f32 arg3, u8 arg4) {
    arg3 *= D_800D1550[0];
    arg2 *= D_800D1550[0];
    if (D_800CC27C != 0) {
        if (arg1->unk28 < 5.0f) {
            if (arg1->interaction_state != 30) {
                arg2 = 0.0f;
            }
        }
    }
    if (arg1->interaction_state == 1) {
        if (arg1->in_water != 0) {
            arg3 *= D_800994C0;
            arg2 = 2.0f;
        }
        if (arg1->unkA8 != 0) {
            arg3 *= 0.25f;
        }
        if (arg1->unk81 != 0) {
            if (arg1->unk81 & 0x40) {
                if (arg1->unk81 & 0x20) {
                    arg3 = 0.0f;
                } else {
                    arg3 = D_800994C4;
                }
            } else {
                arg3 *= D_800994C8;
                if (arg4 >= 0x2E) {
                    arg2 *= 0.5f;
                }
                if (arg4 >= 0x5B) {
                    arg0 *= 0.5f;
                }
            }
        }
        if (arg1->unkAE != 0) {
            arg3 *= D_800994CC;
        }
    }
    if (arg0 < 0.0f) {
        if (0.0f < arg1->xz_velocity) {
            arg3 += arg2;
        } else {
            arg3 = arg2;
        }
    } else {
        if (arg1->xz_velocity < 0.0f) {
            arg2 += arg3;
        }
    }
    if (arg0 < arg1->xz_velocity) {
        arg1->xz_velocity = arg1->xz_velocity - arg3;
        if (arg1->xz_velocity < arg0) {
            arg1->xz_velocity = arg0;
        }
    } else {
        if ((arg0 - 1.0f) < arg1->xz_velocity) {
            arg2 *= D_800994D0;
        }
        arg1->xz_velocity = arg1->xz_velocity + arg2;
        if (arg0 < arg1->xz_velocity) {
            arg1->xz_velocity = arg0;
        }
    }
}
