/* game_1B9DB0 / func_1518C900 -- CLOSED, wave 61 (was parked at 16).
 * Live in conker/src/game_1B9DB0.c. verify_match.sh: ALL CHECKS PASSED.
 * relcheck.py: PASS, 65/65 instructions incl. every relocated field. ROM gate byte-identical.
 *
 * THE FIX. The parked candidate carried a `u8 c` local that the original never had, and the
 * increment was written `D_800DF7D0[arg0] = D_800DF7D0[arg0] + 1`. The match is ONE named
 * local (`s32 *ret`) and a POST-INCREMENT:
 *
 *     s32 func_1518C900(s32 arg0) {
 *         s32 *ret;
 *         if (D_800DF7D0[arg0] == 0) {
 *             ret = func_1502B6BC(0, 0, 0, 2, 9, arg0);
 *             if (ret == 0) return 0;
 *             func_1510CE60(*ret, 0, 1, 0x3E, &D_800DF9B8[arg0]);
 *             func_15168E54(*ret, ret);
 *             D_800E0148[arg0] = ret;
 *         } else {
 *             ret = D_800E0148[arg0];
 *         }
 *         if (D_800DF7D0[arg0] != 0xFF) D_800DF7D0[arg0]++;
 *         return *ret;
 *     }
 *
 * `D_800DF7D0[arg0]++` yields the old value as its own live range (golden's `move v1,v0`
 * pair, which had been misread as a named `c`) while the CSE of the load feeds the `addiu`.
 * Same function with `= x + 1` instead: 847.
 *
 * ================= THE FRAME-LAYOUT LAW (measured here, reusable) =================
 * For a -O2 -g3 TU, with L = roundup4(sum of named-local sizes) and T = number of compiler
 * temp slots:
 *
 *     temp_area_top = (frame - 4) - L          temps descend from there, 4 bytes each
 *     frame         = round8(base + L + 4*T)   base = first byte above the saved-reg area
 *
 * Calibration run on this function (base 0x28: outgoing args 0x00-0x17, an invariant 8-byte
 * gap 0x18-0x1f, $s0 at 0x20, $ra at 0x24):
 *
 *     locals                      L     frame   temp#1   temp#3   score
 *     s32*ret, u8 c               8     0x40    0x34     0x2c       16
 *     s32*ret, u8*p, u8 c        12     0x40    0x30     0x28       40
 *     s32*ret, u8 c, s32 unused  12     0x40    0x30     0x28       40   <- UNUSED locals count
 *     s32*ret, u8 c, inner s32   12     0x40    0x30     0x28      205   <- BLOCK scope counts
 *     s32*ret alone               4     0x38    0x30     0x28     1407
 *     GOLDEN                      4     0x40    0x38     0x2c        0   <- L=4 AND T=4
 *
 * READING RULES THIS ESTABLISHES:
 *  * A spill slot at (frame-4)-L pins the TOTAL SIZE of the named locals, not their count.
 *    Golden's 0x38 with frame 0x40 says L=4 exactly -- so a 4-byte pointer local leaves room
 *    for NOTHING else, and any second scalar is a misreading.
 *  * Scalars are NOT byte-packed: `u8 c` costs a full word once another local follows it.
 *  * Unused locals, and locals declared in an inner block, both consume a slot -- so you
 *    cannot hide a variable from the frame by scoping it.
 *  * `register` is completely inert (16 for every placement tried).
 *  * `static` moves the local off the stack but rewrites every access through %hi/%lo
 *    (1407/1405/2721) -- useful only as a DIAGNOSTIC for L, never as a spelling.
 *  * The frame ALONE cannot separate L from T: golden's 0x40 is round8(0x28+4+16) and the
 *    two-local 0x40 is round8(0x28+8+12). Read L off the FIRST spill offset, then T off the
 *    gap to the LAST spill (which is always the bottom temp).
 */
