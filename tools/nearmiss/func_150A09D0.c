#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern f32 D_8009F5A0;
extern f32 D_8009F5A4;

struct Func150A0D14Arg {
    u8 pad0[0xC];
    f32 unkC;
    f32 unk10;
    u8 pad14[0x10];
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    f32 unk30;
};

/* Partial view of struct108 (the camera record) covering the target fields. */
struct Func150A09D0Camera {
    u8  pad0[0x938];
    f32 unk938;
    f32 unk93C;
    f32 unk940;
    f32 unk944;
    u8  unk948;
    u8  unk949;
    u8  pad94A[0x56];
};

/* struct178 with the fields past 0x6 named (structs.h has them as a blob). */
struct Func150A09D0Entry {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ u8  pad8[0xC];
    /* 0x14 */ u8  unk14;
    /* 0x15 */ u8  unk15;
    /* 0x16 */ u8  pad16;
    /* 0x17 */ u8  unk17;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ u32 unk1C;
    /* 0x20 */ u32 unk20;
    /* 0x24 */ u8  pad24[0x10];
};

void func_1000FC18(u16 arg0, s16 arg1, s16 arg2, s16 arg3, s32 arg4);
s32 func_150A1DA0(u8 *arg0, struct178 *arg1, s32 arg2);
void func_150A23E4(struct178 *arg0);

void func_150A09D0(s32 arg0) {
    u32 count;
    s32 i;

    arg0 = arg0;
    for (i = 0; i < (u32)D_800D3094; i++) {
        switch ((s32)(*(struct Func150A09D0Entry **)&D_800D3098)[i].unk15 >> 2) {
        case 2:
            if ((*(struct Func150A09D0Entry **)&D_800D3098)[i].unk20 == 1) {
                (*(struct Func150A09D0Entry **)&D_800D3098)[i].unk20 ^= 3;
            } else if ((*(struct Func150A09D0Entry **)&D_800D3098)[i].unk20 == 2) {
                func_1000FC18((*(struct Func150A09D0Entry **)&D_800D3098)[i].unk1C >> 16,
                              (*(struct Func150A09D0Entry **)&D_800D3098)[i].unk0,
                              (*(struct Func150A09D0Entry **)&D_800D3098)[i].unk2,
                              (*(struct Func150A09D0Entry **)&D_800D3098)[i].unk4,
                              (*(struct Func150A09D0Entry **)&D_800D3098)[i].unk18);
                (*(struct Func150A09D0Entry **)&D_800D3098)[i].unk20 = 0;
            }
            if (D_800C35EA == 1) {
                if (func_150A1DA0((u8 *)D_800CC2D0, &(*(struct178 **)&D_800D3098)[i], 0) == 0) {
                    func_150A23E4(&(*(struct178 **)&D_800D3098)[i]);
                }
            }
            break;
        case 7:
            if (((*(struct Func150A09D0Entry **)&D_800D3098)[i].unk15 & 3) == 3) {
                (*(struct Func150A09D0Entry **)&D_800D3098)[i].unk20 = 0;
            } else {
                if ((*(struct Func150A09D0Entry **)&D_800D3098)[i].unk20 == 1) {
                    (*(struct Func150A09D0Entry **)&D_800D3098)[i].unk20 = 2;
                } else if ((*(struct Func150A09D0Entry **)&D_800D3098)[i].unk20 == 2) {
                    if (func_1000E46C((*(struct Func150A09D0Entry **)&D_800D3098)[i].unk17, 0,
                                      (*(struct Func150A09D0Entry **)&D_800D3098)[i].unk18, 0)) {
                        if (func_1000E46C((*(struct Func150A09D0Entry **)&D_800D3098)[i].unk17, 100,
                                          (*(struct Func150A09D0Entry **)&D_800D3098)[i].unk1C, 0)) {
                            (*(struct Func150A09D0Entry **)&D_800D3098)[i].unk20 = 0;
                        }
                    }
                }
            }
            break;
        case 4:
            if ((*(struct Func150A09D0Entry **)&D_800D3098)[i].unk17 != 9) {
                count = (*(struct Func150A09D0Entry **)&D_800D3098)[i].unk1C & 0xFF;
                if (count != 0) {
                    if ((*(struct Func150A09D0Entry **)&D_800D3098)[i].unk14 == 0) {
                        count--;
                    } else {
                        count = 0;
                    }
                    (*(struct Func150A09D0Entry **)&D_800D3098)[i].unk1C = ((*(struct Func150A09D0Entry **)&D_800D3098)[i].unk1C & ~0xFF) | count;
                    if (count == 0) {
                        count = (*(struct Func150A09D0Entry **)&D_800D3098)[i].unk1C;
                        D_800DDF5C[(count >> 8) & 0xFF] = 0;
                        (*(struct Func150A09D0Entry **)&D_800D3098)[i].unk1C &= 0xFFFF0000;
                    }
                }
            }
            /* fallthrough */
        case 0:
            if ((*(struct Func150A09D0Entry **)&D_800D3098)[i].unk17 == 0xC) {
                if ((*(struct Func150A09D0Entry **)&D_800D3098)[i].unk14 == 0) {
                    s32 j;

                    for (j = 0; j <= D_80082FA0; j++) {
                        struct Func150A09D0Camera *cam;

                        cam = (struct Func150A09D0Camera *)(D_800DBFF0 + j);
                        cam->unk93C = (f32)(*(struct Func150A09D0Entry **)&D_800D3098)[i].unk0;
                        cam->unk940 = (f32)(*(struct Func150A09D0Entry **)&D_800D3098)[i].unk2;
                        cam->unk944 = (f32)(*(struct Func150A09D0Entry **)&D_800D3098)[i].unk4;
                        cam->unk938 = (f32)(*(struct Func150A09D0Entry **)&D_800D3098)[i].unk6;
                        cam->unk949 = (*(struct Func150A09D0Entry **)&D_800D3098)[i].unk18;
                        cam->unk948 = 1;
                    }
                }
            }
            break;
        }
    }
}

void func_150A0D14(struct Func150A0D14Arg *arg0) {
    f32 angle;

    angle = arg0->unkC * D_8009F5A0;
    arg0->unk24 = func_150AD78C(angle);
    arg0->unk28 = func_150AD780(angle);
    angle = arg0->unk10 * D_8009F5A4;
    arg0->unk2C = func_150AD78C(angle);
    arg0->unk30 = func_150AD780(angle);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_CDE80/func_150A0D8C.s")

s32 func_150A1040(s32 arg0) {
    return arg0 + 0x400;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_CDE80/func_150A104C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_CDE80/func_150A11C4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_CDE80/func_150A1DA0.s")

void func_150A23E4(struct178 *arg0) {
    s32 var_t0;
    s32 var_v1;
    u8 temp_t1;
    s32 temp_t3;
    s32 temp_t4;
    u32 temp_v0;

    if (*(s32 *)&arg0->unk6[0x1A] == 0) {
        var_v1 = 0;
        var_t0 = 8;
        if ((arg0->unk6[0xF] & 3) == 0) {
            var_v1 = 0x8000;
        }
        temp_t1 = arg0->unk6[0x11];
        temp_t3 = temp_t1 & 0x7F;
        if ((s32)temp_t1 >> 7) {
            var_t0 = 0x108;
        }
        temp_t4 = temp_t3 * 327;
        temp_v0 = *(u32 *)&arg0->unk6[0x16];
        func_1000FA64(temp_v0 >> 16, arg0->unk0, arg0->pad2, arg0->unk4, temp_t4,
            *(s32 *)&arg0->unk6[0x12] | var_v1, temp_v0 & 0xFFFF, 0, 0, 0, var_t0, 0);
        *(s32 *)&arg0->unk6[0x1A] = 1;
trailing_label:
        ;
        return;
    }
    *(s32 *)&arg0->unk6[0x1A] = 1;
    return;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_CDE80/func_150A24C0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_CDE80/func_150A25D4.s")

s32 func_150A1DA0(u8 *arg0, struct178 *arg1, s32 arg2);
void func_15172E7C(u8 *arg0, s32 arg1, s32 arg2);

void func_150A278C(u8 *arg0) {
    struct178 *base;
    s32 i;

    if (arg0[0x65] != 0) {
        return;
    }
    for (i = 0; i < (u32)D_800D3094; i++) {
        struct178 *p;
        base = (struct178 *)*(s32 *)&D_800D3098;
        if (8 == (s32)base[i].unk6[0xF] >> 2) {
            if (func_150A1DA0(arg0, &base[i], 0) == 0) {
                p = (struct178 *)*(s32 *)&D_800D3098 + i;
                func_15172E7C(arg0, p->unk6[0x11], *(s32 *)&p->unk6[0x12]);
            }
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_CDE80/func_150A2864.s")

void func_150A2940(s32 arg0, s32 arg1, s32 arg2) {
    typedef u8 entry[0x34];

    arg0 &= 0xFFF;
    if ((u32)arg0 < (u32)D_800D3094) {
        if (arg1 != -1) {
            *(s32 *)&(*(entry **)&D_800D3098)[arg0][0x18] = arg1;
        }
        if (arg2 != -1) {
            (*(entry **)&D_800D3098)[arg0][0x17] = arg2;
        }
        *(s32 *)&(*(entry **)&D_800D3098)[arg0][0x1C] = 0;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_CDE80/func_150A29C8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_CDE80/func_150A2AEC.s")

extern u64 D_800D30F0[][3];

s32 func_150A2CA4(u32 arg0) {
    s32 i;

    arg0 &= 0xFFF;
    if ((u32)D_800D3094 < arg0) {
        return -1;
    }
    for (i = 0; i != 0x10; i++) {
        if (*(u16 *)((u8 *)&D_800D2138 + 0x208) & (1 << i)) {
            if ((D_800D30F0[i][arg0 >> 6] >> (arg0 & 0x3F)) & 1) {
                return i;
            }
        }
    }
    return -1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_CDE80/func_150A2D84.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_CDE80/func_150A2E4C.s")

s32 func_150A2E4C(struct178 *arg0, f32 x, f32 y, f32 z);

s32 func_150A2EE4(s32 a0, s32 a1) {
    struct178 *base;
    s32 ret;

    a1 &= 0xFFF;
    if ((u32)D_800D3094 < (u32)a1) {
        return 1;
    }
    base = (struct178 *)*(s32 *)&D_800D3098;
    ret = 0;
    if ((base[a1].unk6[0xF] & 3) == 3) {
        return func_150A2E4C(base + a1, D_800CC2D0[a0].x_position, D_800CC2D0[a0].y_position, D_800CC2D0[a0].z_position);
    }
    return ret;
}

s32 func_150A2FA4(s32 a0, s32 a1) {
    struct178 *base;
    struct108 *p;
    s32 ret;

    p = &D_800DBFF0[a0];
    a1 &= 0xFFF;
    if ((u32)D_800D3094 < (u32)a1) {
        return 1;
    }
    ret = 0;
    if (((base = (struct178 *)*(s32 *)&D_800D3098)[a1].unk6[0xF] & 3) == 3) {
        return func_150A2E4C(base + a1, p->unk2F8, p->unk2FC, p->unk300);
    }
    return ret;
}

s32 func_150A3058(s32 arg0, s16 arg1, s16 arg2, s16 arg3) {
    u8 pad[4];
    u8 sp48[0x32C];
    struct178 *base;
    s32 i;

    *(f32 *)&sp48[0x14] = (f32)arg1;
    *(f32 *)&sp48[0x2C] = (f32)arg1;
    *(f32 *)&sp48[0x18] = (f32)arg2;
    *(f32 *)&sp48[0x180] = (f32)arg2;
    *(f32 *)&sp48[0x30] = (f32)arg2;
    *(f32 *)&sp48[0x1C] = (f32)arg3;
    *(f32 *)&sp48[0x34] = (f32)arg3;

    for (i = 0; i < (u32)D_800D3094; i++) {
        base = (struct178 *)*(s32 *)&D_800D3098;
        if (base[i].unk6[0xE] == 0) {
            if (3 == ((s32)base[i].unk6[0xF] >> 2)) {
                if (base[i].unk6[0x11] == arg0) {
                    if (func_150A1DA0(sp48, &base[i], 0) == 0) {
                        return 1;
                    }
                }
            }
        }
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_CDE80/func_150A3194.s")

s32 func_150A32B4(struct178 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    u8 sp24[0x32C];
    u8 pad[8];

    *(f32 *)&sp24[0x14] = (f32)arg1;
    *(f32 *)&sp24[0x2C] = (f32)arg1;
    *(f32 *)&sp24[0x18] = (f32)arg2;
    *(f32 *)&sp24[0x180] = (f32)arg2;
    *(f32 *)&sp24[0x30] = (f32)arg2;
    *(f32 *)&sp24[0x1C] = (f32)arg3;
    *(f32 *)&sp24[0x34] = (f32)arg3;
    if (func_150A1DA0(sp24, arg0, 0) == 0) {
        return 1;
    }
    return 0;
}

void func_150A3330(s32 arg0, s32 *arg1, s32 *arg2, s32 *arg3, s32 *arg4) {
    typedef u8 entry[0x34];

    *arg1 = (*(entry **)&D_800D3098)[arg0][0x17];
    *arg2 = *(s32 *)&(*(entry **)&D_800D3098)[arg0][0x18];
    *arg3 = *(s32 *)&(*(entry **)&D_800D3098)[arg0][0x1C];
    *arg4 = *(s32 *)&(*(entry **)&D_800D3098)[arg0][0x20];
}

void func_150A3398(s32 arg0, u16 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    typedef u8 entry[0x34];

    if (arg1 & 1) {
        (*(entry **)&D_800D3098)[arg0][0x17] = arg2;
    }
    if (arg1 & 2) {
        *(s32 *)&(*(entry **)&D_800D3098)[arg0][0x18] = arg3;
    }
    if (arg1 & 4) {
        *(s32 *)&(*(entry **)&D_800D3098)[arg0][0x1C] = arg4;
    }
    if (arg1 & 8) {
        *(s32 *)&(*(entry **)&D_800D3098)[arg0][0x20] = arg5;
    }
}

void func_150A3444(s32 a0, s16 a1, s16 a2, s16 a3) {
    ((struct178 *)*(s32 *)&D_800D3098)[a0].unk0 = a1;
    *(s16 *)&((struct178 *)*(s32 *)&D_800D3098)[a0].pad2 = a2;
    ((struct178 *)*(s32 *)&D_800D3098)[a0].unk4 = a3;
}

s32 func_150A3504(void);

s32 func_150A34B0(u8 *arg0) {
    s32 ret;

    if (arg0[0x14] == 1) {
        return 0;
    }

    ret = 0;
    if (!(arg0[0x15] & 3)) {
        return func_150A3504();
    }
    return ret;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_CDE80/func_150A3504.s")
