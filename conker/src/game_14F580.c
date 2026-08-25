#include <ultra64.h>
#include "functions.h"
#include "variables.h"


extern f32 D_800A3460;
extern f32 D_800A3470;
extern f32 D_800A3474;
extern f32 D_800A3478;
extern f32 D_800A347C;
void func_15122980(struct108 *arg0);

void func_151220D0(struct108 *arg0) {
    struct17 sp1C;
    f32 temp;

    if ((*arg0->unk36C & 4) == 0) {
        func_15048F90((struct17 *)&arg0->unk2F8, (struct17 *)&arg0->unk2BC, &sp1C);
        sp1C.unk0 += *(f32 *)&arg0->unk2C8 - arg0->unk2BC;
        sp1C.unk8 += *(f32 *)&arg0->unk2D0 - arg0->unk2C4;
        temp = func_15048FC8(&sp1C);
        arg0->unk37C = temp;
        arg0->unk39C = temp * D_800A3460;
    }
    func_15122980(arg0);
}

void func_15122170(struct108 *arg0) {
    f32 temp_f16;
    f32 temp_f2;
    f32 temp_f18;

    if ((*arg0->unk36C & 4) != 0) {
        func_15122980(arg0);
        return;
    }
    *(f32 *)arg0->pad5DC -= *(f32 *)arg0->pad5DC * D_800A3470;
    *(f32 *)&arg0->pad6B4[0x10] = 0.0f;
    func_15125330(arg0);
    if (*(struct17 **)&arg0->pad600[0x14] == NULL) {
        func_15122980(arg0);
        return;
    }
    temp_f2 = (*(struct17 **)&arg0->pad600[0x14])->unk0 - arg0->unk2BC;
    temp_f16 = (*(struct17 **)&arg0->pad600[0x14])->unk8 - arg0->unk2C4;
    temp_f18 = sqrtf((temp_f2 * temp_f2) + (temp_f16 * temp_f16));
    if (temp_f18 == 0.0f) {
        func_15122980(arg0);
        return;
    }
    temp_f2 = func_15048C30(-temp_f2 / temp_f18);
    if (temp_f16 > 0.0f) {
        temp_f2 = 270.0f - (temp_f2 * D_800A3474);
    } else {
        temp_f2 = (temp_f2 * D_800A3478) + 90.0f;
    }
    temp_f2 += -90.0f + *(f32 *)arg0->pad5DC;
    while (temp_f2 < 0.0f) {
        temp_f2 += 360.0f;
    }
    while (temp_f2 > 360.0f) {
        temp_f2 -= 360.0f;
    }
    if (arg0->unk698 == 0) {
        if (arg0->unk23C != 0) {
            *(f32 *)&arg0->pad61C[0x14] = 0.0f;
            arg0->unk37C = temp_f2;
        } else if (arg0->unk84 & 0x40000000) {
            func_15049688(&arg0->unk37C, temp_f2, (f32 *)&arg0->pad61C[0x14], 3.0f, 6.0f, arg0->unk7B4);
        } else if (arg0->unk84 & 0x4000000) {
            func_15049688(&arg0->unk37C, temp_f2, (f32 *)&arg0->pad61C[0x14], 3.0f, 6.0f, arg0->unk7B4);
        } else {
            func_15049688(&arg0->unk37C, temp_f2, (f32 *)&arg0->pad61C[0x14], 1.5f, 2.0f, arg0->unk7B4);
        }
        arg0->unk39C = arg0->unk37C * D_800A347C;
    }
    func_1512A390(arg0);
    func_15123A54(arg0);
    func_1512E140(arg0);
    if (arg0->unk84 & 0x40000000) {
        func_15123A54(arg0);
        arg0->unk190 = 30.0f;
        func_1512E140(arg0);
    }
}
