#include <ultra64.h>
#include "functions.h"
#include "variables.h"


/* Near-miss at 160/6300; see tools/nearmiss/func_150C7670.c */
typedef struct { u8 pad00[0x14]; u8 *unk14; } Mid150C7670;
typedef struct {
    u8 pad00[0x70];
    u8 unk70;
    u8 pad71[0xFF];
    Mid150C7670 *unk170;
} Obj150C7670;

s32 func_150C7670(Obj150C7670 *arg0) {
    f32 temp;

    temp = arg0->unk170->unk14[0x2F];
    {
        extern f32 D_800A04C0;

        arg0->unk70 = temp * D_800A04C0;
    }
    return 1;
}


extern u8 D_80089470[];

s32 func_150C773C(void *arg0, s32 arg1) {
    memcpy(arg0, D_80089470, 0x40);
    return 1;
}
