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
