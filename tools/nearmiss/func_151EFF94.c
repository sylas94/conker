/* VERIFIED byte-perfect for BOTH func_151EFF70 and func_151EFF94
 * ONLY when this TU is compiled with plain -O2 (i.e. WITHOUT -g3).
 * Requires this Makefile override next to the other per-file OPT_FLAGS lines:
 *     $(BUILD_DIR)/$(SRC_DIR)/game_21D420.c.o: OPT_FLAGS := -O2
 * Under the default -O2 -g3 it scores 219 (three pure instruction-schedule sites).
 */
#include <ultra64.h>

#include "libc/stdarg.h"
#include "libc/string.h"
#include "functions.h"
#include "variables.h"

extern s32 func_100020D0(u8 *(*arg0)(u8 *, u8 *, u32), u8 *arg1, u8 *arg2, va_list arg3);

u8 *func_151EFF70(u8 *arg0, u8 *arg1, u32 arg2) {
    return (u8 *)memcpy(arg0, arg1, arg2) + arg2;
}

s32 func_151EFF94(u8 *arg0, u8 *arg1, ...) {
    va_list args;
    s32 temp_v0;

    va_start(args, arg1);
    temp_v0 = func_100020D0(func_151EFF70, arg0, arg1, args);
    if (temp_v0 >= 0) {
        arg0[temp_v0] = 0;
    }
    return temp_v0;
}
