/* tools/nearmiss/func_150585F0.c -- game_83300
 *
 * STATUS: mism=2, n=170/170, frame -0x28 EXACT. Two rows, and they are ONE register:
 *      idx17   ours  mul.s $f0,$f6,$f10      gold  mul.s $f14,$f6,$f10
 *      idx19   ours  mfc1  $a3,$f0           gold  mfc1  $a3,$f14
 * 168 of 170 instructions are identical. This is an FP ARGUMENT-STAGING tie, not a source
 * defect: $f12 already carries the 0.0f first argument (`mtc1 $zero,$f12`, row 2, matches),
 * so $f14 is the next free float-argument register. `1.0f` never consumes it because IDO
 * materialises that constant straight into $a2 as the integer immediate 0x3F800000.
 *
 * WHAT IS SETTLED (all measured against a 2-scoring control in the same sweep):
 *   the named local is RIGHT -- inlining the product into the call costs 34 more rows (36),
 *      because it reorders every argument evaluation
 *   `u16 phi_a2` is RIGHT and must stay sub-word -- s32 or u32 both score 32
 *   byte-neutral: `(u32)` cast on the multiplicand; `(f32)` cast at the call site;
 *      declaration order of the two locals
 *   worse: two-step assign (`temp = f; temp *= g;`) -> 25
 *
 * IT IS NOT TEMP ROTATION. Declaring an extra unused f32 before or after the real locals
 * leaves the score at 2 either way, so the FP register here is not being chosen by a
 * declaration-order rotation counter. (Those two probes are NOT shippable source; they were
 * run only to identify the mechanism, and they ruled it out.)
 *
 * *** THE PERMUTER RAN AND FOUND NOTHING. 3823 ITERATIONS, ZERO OUTPUTS. ***
 * This was its ideal case and it still failed, which is worth recording because "run the
 * permuter" is the obvious next suggestion and it has now been tried properly:
 *   - selftest PASS on all five controls, including (e): the same C compiled in ISOLATION
 *     produces different bytes than in-TU, so the TU-aware harness was load-bearing.
 *   - BOTH gates were safe and both were armed -- PERMUTER_TU_REQUIRE_FRAME=40 and
 *     PERMUTER_TU_REQUIRE_OFFSETS=1 -- because the base already matched golden's frame AND
 *     its full stack-offset multiset (8 displacements). The search was therefore confined to
 *     register allocation, which is all that is wrong.
 *   - 3823 iterations, best score ever seen = the base. The permuter saves only improvements,
 *     so it emitted no outputs at all.
 * CONCLUSION: the randomizer does not generate a transformation that flips an FP register
 * assignment. Do not spend another run on this residue class -- func_15040A78 (25 min, gated
 * to golden's frame) likewise produced nothing better than its base. Both are FP/GPR
 * allocation ties with everything else already exact.
 *
 * SUPERSEDED SUGGESTION: this is the exact class decomp-permuter exists for -- a 2-row pure register tie with
 * correct length and frame. Set MAX_FRAME to the BASE frame (0x28), not the target.
 */

void func_150585F0(struct127 *arg0) {
    f32 temp_f14;
    u16 phi_a2;

    temp_f14 = arg0->unk109 * D_80099478;
    func_1505A3A8(0.0f, arg0, 1.0f, temp_f14, 0);
    if (arg0->unk1CC < D_8009947C) {
        arg0->unk1CC = arg0->y_position;
    }
    if ((arg0->in_water != 0) && (arg0->in_water < 0xA)) {
        arg0->gravity = 0.0f;
        if (arg0->y_velocity < 60.0f) {
            arg0->y_velocity *= D_80099480;
        }
        if (((arg0->unk118 - 60.0f) + 40.0f) < arg0->y_position) {
            arg0->unk81 = 0;
            arg0->unk83 = 0;
            arg0->in_water = 0;
            arg0->unkB8 = 0.0f;
            arg0->gravity = 4.0f;
        }
    }
    if ((D_800BE616 == 0) || (1 != arg0->interaction_state)) {
        arg0->unk21C = 0;
    }
    if (arg0->stunned != 0xFF) {
        if (arg0->stunned != 0xFE) {
            if ((arg0->health != 0) || (1 != arg0->interaction_state)) {
                arg0->stunned -= 1;
            }
        }
        arg0->unk10C -= D_800CC264;
        if ((arg0->unk28 < D_80099484) && ((arg0->unkF4 & 0x100) != 0)) {
            arg0->unk10C = 0;
        }
        if (arg0->unk10C <= 0) {
            if (arg0->unk31C != 0) {
                arg0->unk31C->matrix_physics = 0;
            }
            arg0->unk10C = 0;
            func_1505E874(D_800C3E78, arg0);
        }
        if (arg0->stunned == 0) {
            arg0->xz_velocity = 0.0f;
            arg0->unk81 = 0;
            arg0->unk76 = arg0->unk78 = arg0->unk7A;
            if (arg0->in_water != 0) {
                arg0->y_velocity = 0.0f;
                if (1 == arg0->interaction_state) {
                    func_1506B078();
                }
            } else if (1 == arg0->interaction_state) {
                arg0->gravity = 4.0f;
                arg0->unkF8 &= 0xFFFF7FFF;
            }
            if (arg0->unk238 != 0) {
                arg0->unk23A = arg0->unk238;
            }
        } else if ((arg0->unk10B & 2) == 0) {
            phi_a2 = arg0->unk76;
            if ((arg0->unk10B & 4) != 0) {
                phi_a2 ^= 0x8000;
            }
            arg0->unk80 = 0xA;
            func_150599C8(arg0, 0xC, phi_a2);
        }
    }
}

// NON-MATCHING: 80% there
