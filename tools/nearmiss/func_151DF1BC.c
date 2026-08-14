/* NEAR-MISS PARK: func_151DF1BC  (conker/src/game_20AE20.c, TU game_20AE20)
 * golden: 238 instructions, 0x3B8 bytes, frame 0x30
 * score command:
 *   bash tools/buildlock.sh bash -c 'cd conker && make -s build/src/game_20AE20.c.o VERSION=us \
 *     && python3 ../tools/asm-differ/diff.py -o func_151DF1BC -R --max-lines 238 --format json'
 *   (--max-lines 238 == the symbol's own instruction count; the default 4096 reads 16KB past it)
 *
 * BEST SCORE SO FAR: 3662 (declaration order x, actor, mode, alpha) / 3866 (order below).
 *
 * THE CONTROL FLOW AND EVERY CONSTANT ARE ALREADY EXACT. Verified line-for-line against
 * golden: the D_800E0A96 == -1 split, the fade +/- (D_800BE9E4 << 5) clamps, the
 * D_8008FEF8 toggle + the two func_1001263C variants, the actor block (unk232 /
 * D_800D154C / D_800C3E78 pointer-difference-by-812 / func_1507BB28 / unk21C / 0x201),
 * the (D_800E0A94 * alpha) >> 8 clamp, all three D_8008FDD4->unk20 masks
 * (0xFFCF / 0xC / 0x10 / 0x20 / 0xFFDF), c.eq.s against 0.0f, the unk1FF ternary-ish
 * if/else, and the D_800E9D00 bit tests which really do compile to sll 9 / sll 8 + bgez
 * from `& 0x400000` / `& 0x800000`.
 *
 * THE ONE REMAINING DEFECT -- A REGISTER-VS-MEMORY INVERSION:
 *   golden keeps `alpha` in t0 (a register variable, explicitly spilled to 0x28(sp)
 *   around every call: 14 accesses) and keeps `actor` PURELY IN MEMORY at 0x20(sp)
 *   (1 store + 7 reloads, two of which fill branch-likely delay slots).
 *   Mine does exactly the opposite: `actor` is the register variable (t0, spilled to its
 *   home) and `alpha` lives in memory.  Symptoms, in order of appearance:
 *      golden 1868: sw   v0,0x20(sp)      mine: move t0,v0
 *      golden 189c: move t0,zero          mine: sw   zero,0x2?(sp)
 *      golden 1ae8: lw   t8,0x20(sp)      (beql delay slot)  mine: nop
 *      golden 1b98: andi a3,t0,0xff       mine: lbu  a3,0x2b(sp)
 *   Everything else in the diff is register-renaming fallout from this one choice.
 *
 * FRAME (SOLVED): framesize 0x30 needs FOUR declared locals. Golden's homes are
 *   0x2C = first-declared, NEVER SPILLED (fully enregistered, live range crosses no call)
 *   0x28 = alpha, 0x24 = mode, 0x20 = actor.
 * Declaring only three (actor, mode, alpha) put the homes at 0x24/0x28/0x2C -- shifted up
 * by 4 -- and cost ~1000 points. The fourth local is modelled here as `x`, the
 * (D_800E0A94 * alpha) >> 8 intermediate, which is the only value in the function whose
 * live range crosses no call. With it the slot offsets match golden exactly.
 *
 * MEASURED (control variant fired: changing 0x200200 -> 0x200300 moved 4837 -> 4842):
 *   4837  three locals (actor, mode, alpha), alpha inline in the >= 0xFE clamp
 *   4845  three locals (alpha, mode, actor)
 *   4813  three locals (mode, alpha, actor)
 *   4817  three locals (alpha, actor, mode)
 *   4833  three locals (mode, actor, alpha)
 *   4789  three locals (actor, alpha, mode)
 *   3866  FOUR locals (x, alpha, mode, actor) + `x = ...>>8; if (x>=0xFE) alpha=0xFF;
 *         else alpha = x;`   <-- homes now 0x2C/0x28/0x24/0x20, matching golden
 *   3850  four locals (alpha, mode, actor, x)
 *   3851  four locals, `x = ...; alpha = x; if (x >= 0xFE) alpha = 0xFF;`
 *   3662  four locals (x, actor, mode, alpha)  -- best, but its homes are
 *         actor@0x28/mode@0x24/alpha@0x20, i.e. it wins on register naming while getting
 *         the SLOTS wrong; the 3866 ordering is the one that is structurally right.
 *
 * REFERENCE-COUNT ANALYSIS (done, and it says the two sources are equivalent):
 *   golden's alpha has exactly 6 defs + 6 uses; mine has exactly 6 + 6.
 *   golden's actor has 1 def + 12 uses; mine has 1 def + 12 uses.
 *   So IDO is NOT deciding on reference counts -- the two source forms are
 *   reference-identical and it still picks differently. The contest is localised to the
 *   region AFTER `D_800E0A95 = alpha;`: there alpha has 2 uses and actor has 4, and
 *   golden still keeps ALPHA resident in t0 through the actor block, spilling it at each
 *   of the three calls (1a4c/1a74, 1af0/1af4, 1b08/1b14) while reloading actor per use.
 *
 * FURTHER NEGATIVES (same harness; the control -- 0x200200 -> 0x200300 -- fired at
 * 4837 -> 4842, and every ordering variant below produced a distinct number, so the
 * harness is not stuck):
 *   3866  BASE: four locals (x, alpha, mode, actor)  <-- the shipped park state
 *   3866  V1  `if (alpha < 1)` instead of `<= 0`                        (no-op)
 *   3866  V2  `alpha = 0;` moved after the D_8008FEF8 toggle            (no-op)
 *   3866  V6  `if (actor)` instead of `if (actor != NULL)`              (no-op)
 *   3866  V7  block 2 rewritten as `if (... != 1) {...} else if (...)`  (no-op)
 *   3866  Z1  actor retyped `s32` with a (struct127 *) cast on every use (no-op)
 *   3866  Z3  `x = D_800E0A94 * alpha; x = x >> 8;`                     (no-op)
 *   3866  T5  `func_1504332C(0xFF, 0, 0, alpha & 0xFF)`                 (no-op)
 *   3850  V10 declaration order (actor, x, alpha, mode)
 *   3855  Y3  five locals (flags, x, alpha, mode, actor)
 *   4251  V8  clamp written `if (x < 0xFE) alpha = x; else alpha = 0xFF;`
 *   4646  Z5  `s16 x`
 *   4707  K5  Law-4 split of BOTH fade computations
 *   4793  K1  second `struct127 *p` used in the later unk1FF block, x dropped
 *   4793  K3  second `struct127 *p` used in the block-1 tail, x dropped
 *   4793  Y1  4th local = a cache of D_800E9D00 for the two bit tests
 *   4832  Z4  `u8 mode`
 *   4913  K4  Law-4 split of the `+` fade computation only
 *   4938  Z2  `alpha = D_800E0A94 * alpha; x = alpha >> 8;`
 *   5208  Y2  4th local = a cache of D_8008FDD4->unk20
 *   5844  T1  `D_800C3E78 = D_800D154C - D_800CC2D0;`
 *   6014  T2  T1 + `func_1507BB28(0, D_800D154C->unk232)`
 *   6134  T3  `func_1507BB28(0, D_800D154C->unk232)` alone
 *   6384  T4  the whole actor block rewritten through D_800D154C
 *   6583  V9  `D_800E0A95 = alpha;` duplicated into both branches
 *
 * DECOMP-PERMUTER (imported to ~/pdf1bc/nonmatchings/func_151DF1BC, compiler_type=ido,
 * 15 min, -j4, ~1140 candidates). Its best three all CONFIRM the diagnosis and all are
 * UNSHIPPABLE:
 *   best (its metric 1540): adds `struct127 *new_var; new_var = actor;` to split actor's
 *     references AND an empty `if (alpha) { }` to add one alpha reference. The empty if
 *     is a banned construct, and it is precisely the "give alpha one more use" lever --
 *     i.e. the permuter agrees the deficit is one alpha reference in the tail region.
 *   1560 / 1620: same `new_var` split, but they read `new_var` on a path where it was
 *     never assigned (undefined behaviour), plus a Law-4 split of the `+` fade. Measured
 *     honestly (K4/K5) that split is worth -1000, so those candidates win only via the UB.
 * No permuter candidate reached 0, and none was free of banned constructs.
 *
 * NEXT STEP: the missing lever is a legitimate source construct that adds exactly one
 * `alpha` reference (or removes one `actor` reference) in the region after
 * `D_800E0A95 = alpha;` WITHOUT emitting an instruction. Everything tried so far either
 * emits an extra instruction or is a no-op. Worth checking whether golden's caller
 * (func_151DE8F0) or a sibling in this TU reveals that the function actually takes a
 * parameter that shadows one of these slots.
 */

extern u8 D_800E0A94;
extern u8 D_800E0A97;
extern u8 D_8008FE34;
extern f32 D_8008FDE8;
extern s8 D_8008FEF8;
extern char D_800AB800[];
extern s8 D_800E0BE9;
void func_151E7E9C(void);
void func_1000DE1C(s32, s32);
struct216 *func_1507BB28(s32, s32);

void func_151DF1BC(void) {
    s32 x;
    s32 alpha;
    s32 mode;
    struct127 *actor;

    actor = func_15083E90(9);
    if (D_800E0A96 != -1) {
        alpha = D_800E0A95 - (D_800BE9E4 << 5);
        if (alpha <= 0) {
            alpha = 0;
            D_8008FEF8 = (D_8008FEF8 == 0);
            if (D_8008FEF8 == 0) {
                mode = 0xE;
                func_1001263C((func_150ADA20() & 1) + 0xC8, 0x7D00, 0x40);
            } else {
                mode = 0xF;
                func_1001263C((func_150ADA20() % 3U) + 0xBE, 0x7D00, 0x40);
            }
            if (actor != NULL) {
                actor->unk232 = mode;
                D_800D154C = actor;
                D_800C3E78 = actor - D_800CC2D0;
                actor->unk218 = func_1507BB28(0, actor->unk232);
                actor->unk21C = 0;
                actor->pad201[0] = 0x14;
            }
            D_800E0A96 = -1;
        }
        D_8008FDD4->unk20 &= ~0x30;
    } else {
        alpha = D_800E0A95 + (D_800BE9E4 << 5);
        if (alpha >= 0x100) {
            alpha = 0xFF;
        }
    }

    D_800E0A95 = alpha;
    x = (D_800E0A94 * alpha) >> 8;
    if (x >= 0xFE) {
        alpha = 0xFF;
    } else {
        alpha = x;
    }

    if (D_8008FEF8 == 0) {
        func_151E3344(0x200200, 0, 1, alpha & 0xFF, 1);
        if ((D_8008FE34 == 9) && (D_8008FDD4->unk20 & 0xC)) {
            func_151E7E9C();
            func_1000DE1C(D_800E0A97, 0);
            D_800E0A97 = func_1000EA94(D_800E0BE9);
        }
        if (D_8008FDD4->unk20 & 0x10) {
            if (D_8008FE34 == 0x15) {
                if (D_8008FDE8 == 0.0f) {
                    D_800E0A96 = 1;
                    D_8008FDD4->unk20 &= ~0x30;
                }
            }
        }
        if (D_8008FDD4->unk20 & 0x20) {
            func_15007668();
        }
    }

    if (actor != NULL) {
        if (func_151F2CDC() == 1) {
            if (actor->unk1FF == 0) {
                actor->unk1FF = 1;
            }
        } else {
            actor->unk1FF = 0;
        }
    }

    if (D_8008FEF8 != 0) {
        if (D_8008FDD4->unk20 & 0x20) {
            D_800E0A96 = 1;
        }
        D_8008FDD4->unk20 &= ~0x20;
        if (D_8008FEF8 != 0) {
            func_1504332C(0xFF, 0, 0, alpha);
            func_15042D94(0x94, 0x14, 0x81, D_800AB800, 0x10);
        }
        D_800BE9EC = 0;
        if (D_800E9D00 & 0x400000) {
            D_800BE9EC = 1;
        }
        if (D_800E9D00 & 0x800000) {
            D_800BE9EC = 2;
        }
    }
}
