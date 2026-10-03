#include <ultra64.h>

#include "functions.h"
#include "variables.h"


void func_150175E0(void) {
    if ((D_800BE616 == 0) && ((D_800D2E4C->unk18 & 1) == 0)) {
        D_800D2457 = D_800D2456 = 3;
    } else {
        D_800D2457 = D_800D2456 = 6;
    }
}

void func_15017640(void) {
    f32 *p;
    f32 *end;
    s32 i;

    D_800D2458 = 0;
    D_800D2588 = 0;

    D_800D2428[0] = D_8009DCB4[0];
    D_800D2428[1] = D_8009DCB4[1];
    D_800D2428[2] = D_8009DCB4[2];

    D_800D2438[0] = 0.0f;
    D_800D2438[1] = 0.0f;
    D_800D2438[2] = 0.0f;

    D_800D2444 = 0;
    D_800D245C = NULL;

    p = D_800D2410, end = &D_800D2410[6];
    do {
        *p = 1.0f;
        p++;
    } while (p < end);

    for (i = 0; i < 6; i++) {
        D_800D2460[i][13] = 0;
    }

    D_800D24C0 = 0;
    bzero(&D_800D24C8, 0xC0);
    guPerspective((Mtx *)&D_800D23D0, (u16 *)&D_800D2454, 50.0f, 60.6f, 53.0f, D_800968B0, 1.0f);
}
