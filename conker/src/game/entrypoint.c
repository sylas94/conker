#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* Notes on this function's codegen (jump table jtbl_80095A30 lives in this TU's
 * .rodata; see the `- [0x23A4F0, .rodata, game/entrypoint]` entry in
 * conker.us.yaml):
 *
 * 1) The two `sh 2` stores at D_800BEA68+0x0 / +0x20 must go through a SIGNED
 *    s16 lvalue. With the u16 fields that structs.h's struct195 declares, IDO
 *    materialises the constant twice (`li v1,2` for the stores plus a separate
 *    `li s1,2` hoisted for the loop compare) and every callee-saved register
 *    shifts by one. With s16 the two 2's are one value and it lands in s7.
 *    variables.h's `struct195 *D_800BEA68` is also wrong: the asm takes the
 *    symbol's ADDRESS, so it is an object, not a pointer. Both header bugs are
 *    worked around with a file-local cast.
 *
 * 2) `while (1) { ... }` -- NOT `do { ... } while (1);`. They generate identical
 *    instructions, but only the `while` form makes IDO 32-byte-align the dead
 *    (unreachable) epilogue, which is what produces the three trailing `nop`s.
 *
 * 3) D_800BE9F4 is a 32-bit slot read as s16 by func_15007A70(s16,s16,s16);
 *    IDO narrows the load to `lh <sym>+2`.
 */

// game entrypoint
void func_15007830(void) {
    func_15007A20();
    D_800D2C28 = 0;
    osCreateMesgQueue(&D_800BEA10, &D_800BEA28, 16);
    ((s16 *)&D_800BEA68)[0] = 2;
    ((s16 *)&D_800BEA68)[0x10] = 2;
    D_800BE617 = 0;
    func_100050A0(&D_800BEA10);
    func_15003570();
    D_800BEAAB = 0;
    func_10008180();
    func_15000000();
    func_15016588();
    func_151EEFF0();
    D_800BEAA8 = 0;
    func_150061B0();
    func_15006234();
    func_151DD970();
    func_15015920(0);
    func_15008A60();
    func_15042D50();
    D_800BE615 = 5;
    D_800BEA04[0] = 0;
    D_800BEA00[0] = 1;
    D_800BEAAA = 1;
    func_1509C120();
    while (1) {
        switch (D_800BE615) {
            case 1:
            case 5:
                func_151E50C8();
            case 2:
                func_15017498();
                if (2 == D_800E0B94) {
                    func_150ADACC(0x81280783);
                }
                func_15007A70(D_800BEA04[0], D_800BEA00[0], (s16)D_800BE9F4);
            case 3:
                func_15007B3C();
                D_800BE615 = 0;
            case 4:
                break;
        }
        func_100051E8();
        D_800BE9E8 = 0;
        func_150186D0();
    }
}
