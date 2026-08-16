#include <ultra64.h>
#include "functions.h"
#include "variables.h"

/* An 8-byte record table terminated by a record whose unk0 offset is zero.
 * func_1502B7F0 loads it and stores the base through the pointer we hand it, so
 * undefined_syms_auto.txt only knows the address of the pointer itself. */
typedef struct {
    s32 unk0;
    s32 unk4;
} Struct43880;

extern Struct43880 *D_800D18B0;

void func_150163D0(s32 arg0) {
    s32 count;
    s32 i;

    if (func_1502B7F0((s32 *)&D_800D18B0, 3, 12, arg0, 9) > 0) {
        count = 1;
        i = 0;
        while (D_800D18B0[i].unk0 != 0) {
            count++;
            i++;
        }
        for (i = 0; i < count - 1; i++) {
            D_800D18B0[i].unk0 += (s32)D_800D18B0;
        }
    } else {
        D_800D18B0 = NULL;
    }
}
