#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern u8 D_800DF7D0[];
extern s16 *D_800DF9B8[];
extern s32 *D_800E0148[];
void func_1510D630(s16 *arg0);
s32 *func_1502B6BC(s32, s32, s32, s32, s32, s32);
s32 func_1510CE60(s32, s32, s32, s32, s16 **);
void func_15168E54(s32, s32 *);

// NEAR-MISS 16 -> MATCH (wave 61). The parked candidate carried a `u8 c` local that the
// original never had. Frame-layout law measured here (game_1B9DB0, -O2 -g3):
//
//     temp_area_top = (frame - 4) - roundup4(sum of named-local sizes)
//     frame         = round8(0x28 + roundup4(locals) + 4 * n_temps)
//
// so golden's first spill at 0x38 with frame 0x40 proves the function has EXACTLY ONE
// named local (4 bytes), and its second spill at 0x2c (three slots lower, not two) proves
// four compiler temps, one more than any two-local spelling can produce. `s32 *ret` is that
// one local; the `move v1,v0` pair that looked like a named `c` is IDO's own temporary,
// created by the post-increment `D_800DF7D0[arg0]++` -- which yields the old value as a
// separate live range while the CSE of the load feeds the addiu. Writing the increment as
// `= D_800DF7D0[arg0] + 1` collapses the two live ranges and costs 847.
s32 func_1518C900(s32 arg0) {
    s32 *ret;

    if (D_800DF7D0[arg0] == 0) {
        ret = func_1502B6BC(0, 0, 0, 2, 9, arg0);
        if (ret == 0) {
            return 0;
        }
        func_1510CE60(*ret, 0, 1, 0x3E, &D_800DF9B8[arg0]);
        func_15168E54(*ret, ret);
        D_800E0148[arg0] = ret;
    } else {
        ret = D_800E0148[arg0];
    }
    if (D_800DF7D0[arg0] != 0xFF) {
        D_800DF7D0[arg0]++;
    }
    return *ret;
}

void func_1518CA04(s32 arg0) {
    if (arg0 != 0x1E4) {
        if (D_800DF7D0[arg0] != 0) {
            if (--D_800DF7D0[arg0] == 0) {
                func_1510D630(D_800DF9B8[arg0]);
                func_100043B4(D_800E0148[arg0], 4);
            }
        }
    }
}
