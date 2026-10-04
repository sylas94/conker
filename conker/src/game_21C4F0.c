#include <ultra64.h>
#include "functions.h"
#include "variables.h"

void __osPiGetAccess(void);
void __osPiRelAccess(void);
s32 osPiRawReadIo(u32 devAddr, u32 *data);

/* osPiReadIo.  `register` is load-bearing and only bites at -O1: without it `status` spills to
 * the stack (frame 0x20, no $s0, `addiu $sp` left out of the jr delay slot) and the function
 * is one instruction short at every flag setting.  With it, at -O1, both functions here are
 * byte-perfect -- which also puts this TU in the same -O1 family as the game's other private
 * libultra copies (game_21C540, game_21CAF0, game_21CAC0). */
s32 func_151EF040(u32 devAddr, u32 *data) {
    register s32 status;

    __osPiGetAccess();
    status = osPiRawReadIo(devAddr, data);
    __osPiRelAccess();
    return status;
}

f32 func_151EF080(f32 arg0) {
    return sqrtf(arg0);
}
