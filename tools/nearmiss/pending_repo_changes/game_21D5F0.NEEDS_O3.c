#include <ultra64.h>
#include "functions.h"
#include "variables.h"


// This TU is SDK libultra gu built at -O3 (Rare's private libultra copy region).
// IDO -O3 emits the functions of a file in REVERSE source order, so guMtxXFMF (first in ROM)
// is written last.  At -O3 the third float arg gets its own `mtc1 $a3,$f16`, which -O2 can
// never produce.  Whole .text is byte-identical to the expected object at -O3.
// Needs: OPT_FLAGS := -O3 for this object, and asm_processor.py only accepts -O0/-O1/-O2/-g,
// so the asm-processor step must be given -O2 (or skipped: no GLOBAL_ASM left) while cc gets -O3.

void guMtxCatF(float m[4][4], float n[4][4], float r[4][4]) {
    int i;
    int j;
    int k;
    float temp[4][4];

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            temp[i][j] = 0.0f;
            for (k = 0; k < 4; k++) {
                temp[i][j] += m[i][k] * n[k][j];
            }
        }
    }

    for (i = 0; i < 4; i++) {
        for (j = 0; j < 4; j++) {
            r[i][j] = temp[i][j];
        }
    }
}

void guMtxXFMF(float mf[4][4], float x, float y, float z, float *ox, float *oy, float *oz) {
    *ox = mf[0][0] * x + mf[1][0] * y + mf[2][0] * z + mf[3][0];
    *oy = mf[0][1] * x + mf[1][1] * y + mf[2][1] * z + mf[3][1];
    *oz = mf[0][2] * x + mf[1][2] * y + mf[2][2] * z + mf[3][2];
}
