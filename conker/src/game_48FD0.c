#include <ultra64.h>
#include "functions.h"
#include "variables.h"

/* This build's libultra exports osMotorStart/osMotorStop/_MakeMotorData as real
   functions instead of the __osMotorAccess macro that os_motor.h defines. */
#undef osMotorStart
#undef osMotorStop
extern s32 osMotorStart(OSPfs *pfs);
extern s32 osMotorStop(OSPfs *pfs);
extern s32 _MakeMotorData(OSMesgQueue *mq, OSPfs *pfs, s32 channel);

extern u8 D_80084060[];
extern OSTimer D_800BE6E0;
extern f32 D_80096960;
extern u8 D_800BEAC2;
extern u8 D_800BEAC3;
extern u8 D_800E0A00;

s64 __ll_mul(u64 arg0, s32 arg1, s32 arg2);
u64 __ull_div(u64 arg0, u64 arg1);
void func_1501C0F0(u8 arg0, f32 arg1, f32 arg2);

void func_1501BB20(void) {
    if (D_80084064 != 0) {
        osSetTimer(&D_800BE6E0, __ull_div(__ll_mul(25ULL, *(s32 *)&D_8002BD10, D_8002BD14), 1000000ULL), 0, &D_8003B218, (OSMesg)6);
        D_80084064 = 0;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_48FD0/func_1501BBB8.s")

void func_1501C010(u8 arg0, u8 arg1) {
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f2;
    u32 temp_v0;

    temp_v0 = arg1;
    if (arg1 >= 9) {
        arg1 = 8;
        temp_v0 = 8;
    }
    if (temp_v0 == 8) {
        temp_f2 = 20.0f;
        temp_f12 = 0.0f;
    } else if (temp_v0 == 0) {
        temp_f2 = 0.0f;
        temp_f12 = 99.0f;
    } else {
        temp_f0 = ((f32)(u32)arg1 - 1.0f) * D_80096960 * 5.0f;
        temp_f2 = temp_f0 + 2.0f;
        temp_f12 = 7.0f - temp_f0;
    }
    func_1501C0F0(arg0, temp_f2, temp_f12);
}

void func_1501C0F0(u8 arg0, f32 arg1, f32 arg2) {
    u8 temp = D_80084060[arg0];

    if (temp < 4) {
        if (D_800BE944[temp] != 0) {
            D_800BE93C[temp] = 1;
            D_800BE950[temp] = 0.0f;
            D_800BE960[temp] = arg1;
            D_800BE970[temp] = arg2;
            D_800BE980[temp] = arg1 + arg2;
        }
    }
}

void func_1501C17C(u8 arg0) {
    u8 temp = D_80084060[arg0];
    if (temp < 4) {
        D_800BE93C[temp] = 0;
    }
}

void func_1501C1B0(void) {
    s32 i;
    s32 on;

    for (i = 0; i < 4; i++) {
        if (D_800BE938 != 0) {
            if (_MakeMotorData(&D_800BE900, (OSPfs *)&D_800BE760[i], i) == 0) {
                if (D_800BE944[i] == 0) {
                    D_800BE944[i] = 1;
                    D_800BE93C[i] = 0;
                    D_800BE940[i] = 0;
                    D_800BE948[i] = 0;
                    D_800BE950[i] = 0.0f;
                    D_800BE960[i] = 1.0f;
                    D_800BE970[i] = 1.0f;
                    D_800BE980[i] = 2.0f;
                    osMotorStop((OSPfs *)&D_800BE760[i]);
                }
            } else {
                D_800BE944[i] = 0;
            }
        }
        if (D_800BE944[i] != 0) {
            if ((D_800BEAC3 != 0) || (D_800E0A00 != 0)) {
                _MakeMotorData(&D_800BE900, (OSPfs *)&D_800BE760[i], i);
                osMotorStop((OSPfs *)&D_800BE760[i]);
                D_800BE948[i] = 0;
                D_800BE93C[i] = 0;
            }
            if ((D_800BEAC1 == 0) && (D_800BEAC0 == 0) && (D_800BEAC2 == 0) && (D_800BEAC3 == 0) && (D_800E0A00 == 0)) {
                switch (D_800BE93C[i]) {
                case 0:
                    if (D_800BE940[i] == 1) {
                        _MakeMotorData(&D_800BE900, (OSPfs *)&D_800BE760[i], i);
                        osMotorStop((OSPfs *)&D_800BE760[i]);
                        D_800BE948[i] = 0;
                    }
                    break;
                case 1:
                    D_800BE950[i] += D_800BE9A4;
                    while (D_800BE950[i] > D_800BE980[i]) {
                        D_800BE950[i] -= D_800BE980[i];
                    }
                    if (D_800BE960[i] <= D_800BE950[i]) {
                        on = 0;
                    } else {
                        on = 1;
                    }
                    if (on != 0) {
                        if (D_800BE948[i] == 0) {
                            osMotorStart((OSPfs *)&D_800BE760[i]);
                        }
                    } else {
                        if (D_800BE948[i] == 1) {
                            osMotorStop((OSPfs *)&D_800BE760[i]);
                        }
                    }
                    D_800BE948[i] = on;
                    break;
                }
            }
            D_800BE940[i] = D_800BE93C[i];
        }
    }
    D_800BE938 = 0;
    D_800BEAC3 = 0;
    D_800E0A00 = 0;
}

void func_1501C53C(void) {
    u8 i;
    for (i = 0; i < 4; i++) {
        func_1501C17C(i);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_48FD0/func_1501C57C.s")
