#include <ultra64.h>

#include "functions.h"
#include "variables.h"


// wtf?
typedef struct { s32 w[9]; } Va36;
extern void func_150AAD98(Va36);

void func_15049260(Va36 arg0) {
    func_150AAD98(arg0);
}

/* asm-differ reports score 10, but the LINKED bytes are identical -- every instruction,
 * register and scheduling slot matches. The residual is purely a RELOCATION-SYMBOL NAMING
 * artifact: the extracted .s spells the last store as %hi/%lo(D_800CC238 + 0x4) because
 * spimdisasm never emitted a D_800CC23C label there, while C naturally writes
 * %hi/%lo(D_800CC23C). Both encode to 3C01800D / E428C23C once the linker resolves them.
 * asm-differ compares OBJECTS, so it scores the symbol name; the force-clean full-ROM sha1
 * gate is the authority and confirms this is byte-perfect (same class as func_15063C60). */
extern f32 D_80099080;   /* 0.001f, asm/data/game_76710.rodata.s */

void func_150492CC(f32 arg0, f32 arg1, f32 arg2) {
    D_800CC220 = arg0;
    D_800CC224 = arg1;
    D_800CC228 = arg2;
    D_800CC22C = arg0 / 2;
    D_800CC230 = arg1 / 2;
    D_800CC234 = arg2 / 2;

    if (arg0 == 0.0f) {
        arg0 = D_80099080;
    }

    D_800CC238 = arg1 / arg0;
    D_800CC23C = arg2 / arg0;
}

// too many temp vars
#pragma GLOBAL_ASM("asm/nonmatchings/game_76710/func_15049350.s")
