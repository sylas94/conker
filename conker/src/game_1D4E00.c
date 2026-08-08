#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern f32 D_800A8F68;
extern f32 D_800A8F6C;
extern f32 D_800A8F58;
extern f32 D_800A8F5C;
extern f32 D_800A8F60;
extern f32 D_800A8F64;
extern f32 D_800A8DE0;
extern void (*D_8008FA60[])(f32 *, void *, s32, u8, s32);

void func_1514373C(f32, f32, f32 *, f32 *);
s32 func_15046C80(f32 *, s32, f32, void *);
void *func_151A7950(void *, s32, u8, s32);
s32 func_151A8B20(void *, s16, s32, u8, s32);


#pragma GLOBAL_ASM("asm/nonmatchings/game_1D4E00/func_151A7950.s")

typedef struct {
    struct17 unk0;
    struct17 unkC;
} Point_151A7A90;

typedef struct {
    u8  pad0[0x10];
    s16 unk10;
    s16 unk12;
    f32 unk14;
    f32 unk18;
    u8  unk1C;
    u8  pad1D[3];
    f32 unk20;
    u8  pad24[8];
    s8  unk2C;
    s8  unk2D;
    u8  pad2E[2];
    f32 unk30;
    f32 unk34;
    f32 unk38;
    f32 unk3C;
    f32 unk40;
    f32 unk44;
    struct17 unk48;
    u8  pad54[4];
    f32 unk58;
    u8  pad5C[8];
    Point_151A7A90 *unk64;
    f32 unk68;
} Header_151A7A90;

extern s32 (*D_8008F940[])(void *);
extern s32 (*D_8008F948[])(void *);

void func_151A8340(void *, s16, s16, f32, s16);

void func_151A7A90(Header_151A7A90 *arg0) {
    Header_151A7A90 *hdr;
    u8 flag;
    struct17 scale;
    struct17 up;
    struct17 dir;
    s32 idx1;
    s32 idx2;

    hdr = arg0;
    flag = 0;
    if (arg0->unk1C & 1) {
        arg0->unk10 -= D_800BE9E4;
        if (arg0->unk10 < 0) {
            flag = 1;
        }
    }
    idx1 = arg0->unk2C;
    if (idx1 != -1) {
        if (!flag) {
            flag = (D_8008F940[idx1](arg0) == 0);
        }
    }
    idx2 = arg0->unk2D;
    if (idx2 != -1) {
        if (!flag) {
            flag = (D_8008F948[idx2](arg0) == 0);
        }
    }

    if (!flag) {
        arg0->unk68 -= D_800BE9A4;
        if (arg0->unk68 < 0.0f) {
            func_151A8340(arg0, 0, arg0->unk12 - 1, arg0->unk20, 100);
            arg0->unk68 = func_150ADA68() * arg0->unk18 + arg0->unk14;
        }
        if (arg0->unk1C & 2) {
            Point_151A7A90 *pt;

            dir.unk0 = arg0->unk3C - arg0->unk30;
            dir.unk4 = arg0->unk40 - arg0->unk34;
            dir.unk8 = arg0->unk44 - arg0->unk38;
            up = arg0->unk48;
            func_151450B4(&dir, &up, &scale);
            {
                s32 i;

                scale.unk0 *= arg0->unk58;
                scale.unk4 *= arg0->unk58;
                scale.unk8 *= arg0->unk58;

                pt = arg0->unk64;
                for (i = 0; i < hdr->unk12; i++) {
                    pt->unkC.unk0 = arg0->unk30 + pt->unk0.unk0 * scale.unk0 +
                                    pt->unk0.unk4 * up.unk0 + pt->unk0.unk8 * dir.unk0;
                    pt->unkC.unk4 = arg0->unk34 + pt->unk0.unk0 * scale.unk4 +
                                    pt->unk0.unk4 * up.unk4 + pt->unk0.unk8 * dir.unk4;
                    pt->unkC.unk8 = arg0->unk38 + pt->unk0.unk0 * scale.unk8 +
                                    pt->unk0.unk4 * up.unk8 + pt->unk0.unk8 * dir.unk8;
                    pt++;
                }
            }
        }
    }

    if (flag) {
        func_1516972C((struct102 *)arg0);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1D4E00/func_151A7D6C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1D4E00/func_151A8340.s")

extern void func_151D5E30(void *);

void func_151A8560(void *arg0) {
    func_151D5E30((void *)((u8 *)arg0 + 0x6C));
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1D4E00/func_151A8584.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1D4E00/func_151A85D4.s")

typedef struct {
    u8 bytes[4];
} Unaligned4_151A8624;

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
} Vec3f_151A8624;

typedef struct {
    void *unk0;
    u8 unk4;
    u8 pad5[3];
    Header2 unk8;
    u8 unk14;
    u8 pad15[3];
    Header2 unk18;
    u8 unk24;
    u8 unk25;
    u8 pad26[2];
} Payload_151A8624;

typedef struct {
    s16 unk0;
    s16 unk2;
    f32 unk4;
    f32 unk8;
    u8 unkC;
    u8 padD[3];
    f32 unk10;
    Unaligned4_151A8624 unk14;
    f32 unk18;
    u8 unk1C;
    s8 unk1D;
    u8 pad1E[2];
    f32 unk20;
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    f32 unk30;
    f32 unk34;
    f32 unk38;
    f32 unk3C;
    f32 unk40;
    f32 unk44;
    f32 unk48;
    u8 unk4C;
    u8 pad4D[3];
} Header_151A8624;

void *func_151A8624(u8 *arg0, Header2 *arg1, u8 arg2, s16 arg3,
                    f32 arg4, f32 arg5, Unaligned4_151A8624 *arg6,
                    f32 arg7, Vec3f_151A8624 *arg8, u8 arg9, u8 argA,
                    s8 argB, s32 argC, u8 argD, s32 argE) {
    void *temp_v0;
    Header_151A8624 header;
    Payload_151A8624 payload;
    u8 flag;

    if (arg0 == NULL) {
        return NULL;
    }
    if (arg9 >= 2) {
        arg9 = 0;
    }

    payload.unk8 = *arg1;
    payload.unk14 = arg2;
    payload.unk25 = 0;
    payload.unk0 = arg0;
    payload.unk4 = arg0[0x3B];
    payload.unk24 = argA;
    temp_v0 = &header;

    if (arg8 != NULL) {
        *(Vec3f_151A8624 *)&payload.unk18 = *arg8;
    } else {
        ((Vec3f_151A8624 *)&payload.unk18)->unk0 = 0.0f;
        ((Vec3f_151A8624 *)&payload.unk18)->unk4 = 0.0f;
        ((Vec3f_151A8624 *)&payload.unk18)->unk8 = 0.0f;
    }

    if (arg3 == -1) {
        header.unk0 = 0x12C;
    } else {
        header.unk0 = arg3;
    }
    header.unk2 = 9;
    header.unk4 = arg4;
    header.unk8 = arg5;
    if (arg3 == -1) {
        flag = 0;
    } else {
        flag = 1;
    }
    header.unkC = flag;
    header.unk10 = D_800A8DE0;
    header.unk14 = *arg6;
    header.unk18 = arg7;
    if ((arg9 != 0) && (arg9 == 1)) {
        header.unk1C = 1;
    } else {
        header.unk1C = 1;
    }
    header.unk20 = 0.0f;
    header.unk24 = 0.0f;
    header.unk28 = 0.0f;
    header.unk2C = 0.0f;
    header.unk30 = 0.0f;
    header.unk34 = 0.0f;
    header.unk38 = 0.0f;
    header.unk3C = 0.0f;
    header.unk40 = 0.0f;
    header.unk44 = 0.0f;
    header.unk1D = argB;
    header.unk4C = 2;
    header.unk48 = 1.0f;

    temp_v0 = func_151A7950(temp_v0, argC + 0x28, argD, argE);
    if (temp_v0 != NULL) {
        memcpy(*(void **)((u8 *)temp_v0 + 0x60), &payload, sizeof(payload));
    }
    return temp_v0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1D4E00/func_151A87F8.s")

extern void (*D_8008F964[])(u8 *, s32, u8);

void func_151A8A20(u8 *arg0, s32 arg1, u8 arg2) {
    s32 idx;

    idx = arg0[0x5C];
    if (idx >= 3) {
        idx = 0;
    }
    if (D_8008F964[idx] != NULL) {
        D_8008F964[idx](arg0, arg1, arg2);
    }
}

typedef struct {
    s32 unk0;
    u8  unk4;
} SubA_151A8A78;

typedef struct {
    s32 unk0;
    union {
        s32 w4;
        u8  b4;
    } u4;
    u8  unk8;
    u8  unk9;
} ArgB_151A8A78;

void func_151A8A78(void *arg0, s32 arg1, u8 arg2) {
    SubA_151A8A78 *temp_v0 = *(SubA_151A8A78 **)((u8 *)arg0 + 0x60);
    ArgB_151A8A78 *b = (ArgB_151A8A78 *)arg1;
    s32 b0;

    if (arg2 == 0) {
        b0 = b->unk0;
        if ((b0 == temp_v0->unk0) || (temp_v0->unk4 == b->u4.b4)) {
            func_1516972C((struct102 *)arg0);
        }
    } else if (arg2 == 0x2D) {
        if (temp_v0->unk0 == b->unk0) {
            temp_v0->unk0 = b->u4.w4;
            temp_v0->unk4 = b->unk9;
        } else if (temp_v0->unk0 == b->u4.w4) {
            temp_v0->unk0 = b->unk0;
            temp_v0->unk4 = b->unk8;
        }
    }
}

extern f32 D_800A8F50;
extern f32 D_800A8F54;

extern void func_1510F800(s32);

typedef struct {
    u8  unk0;
    u8  pad1[3];
    struct134 *unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    u8  unk24;
    u8  unk25;
    u8  unk26;
    u8  pad27;
    f32 unk28;
    f32 unk2C;
    f32 unk30;
    f32 unk34;
    f32 unk38;
    f32 unk3C;
    f32 unk40;
    s32 unk44;
    u8  unk48;
    u8  unk49;
    u8  pad4A[2];
    s32 unk4C;
    s32 unk50;
    f32 unk54;
} Header_151A8B20;

s32 func_151A8B20(void *arg0, s16 arg1, s32 arg2, u8 arg3, s32 arg4) {
    s32 effect;
    Header_151A8B20 header;
    Header_151A8B20 *ptr;

    memcpy(&header, arg0, 0x28);

    header.unk28 = 0.0f;
    header.unk2C = D_800A8F50;
    header.unk44 = 0;
    header.unk48 = 0;
    header.unk49 = 0;
    header.unk4C = 0;

    effect = (s32)func_15149130((arg1 == -1) ? 0x12C : arg1, -1, 0x25, -1, (arg1 == -1) ? 0 : 1, 0x22, (struct37 *)(arg2 + 0x58), arg3, arg4);
    if (effect != 0) {
        ptr = (Header_151A8B20 *)(effect + 0x28);
        memcpy(ptr, &header, 0x58);

        if (ptr->unk0 & 4) {
            f32 posZ;
            f32 posX;

            if ((ptr->unk0 & 2) && (ptr->unk4 != NULL)) {
                posX = (f32)ptr->unk4->unk0;
                posZ = (f32)ptr->unk4->unk4;
            } else {
                posX = ptr->unk10;
                posZ = ptr->unk18;
            }
            func_1510F800(0);
            ptr->unk50 = func_1510FD20((s32)posX, (s32)posZ);
        } else {
            ptr->unk50 = 0;
        }

        if ((ptr->unk0 & 2) && (ptr->unk4 != NULL)) {
            ptr->unk54 = func_15144598(ptr->unk4);
        } else {
            ptr->unk54 = (ptr->unk20 * ptr->unk20) * D_800A8F54;
        }
    }
    return effect;
}

typedef struct {
    u8  unk0;
    u8  pad1[3];
    void *unk4;
    f32 unk8;
    f32 unkC;
    u8  pad10[0x15];
    s8  unk25;
    s8  unk26;
    u8  pad27;
    f32 unk28;
    f32 unk2C;
    u8  pad30[0x20];
    s32 unk50;
    f32 unk54;
} Header_151A8CEC;

extern s32 (*D_8008F980[])(void *);
extern void (*D_8008F970[])(void *, f32 *, f32, u8);

s32 func_151464B8(s32);
void func_151A8F1C(void *, f32 *, f32 *, f32 *);
void func_151A8F6C(void *, f32 *, f32 *, f32 *);

void func_151A8CEC(u8 *arg0) {
    Header_151A8CEC *ptr;
    void (*cb)(void *, f32 *, f32 *, f32 *);
    f32 pos[3];
    f32 radius;
    f32 angle;
    u8 flag;

    ptr = (Header_151A8CEC *)(arg0 + 0x28);

    if (*(s8 *)(arg0 + 0x4D) != -1) {
        if (D_8008F980[ptr->unk25](arg0) == 0) {
            *(s16 *)(arg0 + 0xE) = -1;
            return;
        }
    }

    if ((ptr->unk0 & 4) && (ptr->unk50 != 0)) {
        if (func_151464B8(ptr->unk50) != 0) {
            return;
        }
    }
    if (!(ptr->unk0 & 1)) {
        return;
    }

    ptr->unk28 += (ptr->unk8 + func_150ADA68() * ptr->unkC) * D_800BE9A4 * ptr->unk54;

    if (ptr->unk28 > 1.0f) {
        if ((ptr->unk0 & 2) && (ptr->unk4 != NULL)) {
            cb = func_151A8F1C;
        } else {
            cb = func_151A8F6C;
        }
        do {
            cb(arg0, pos, &angle, &radius);
            if (ptr->unk0 & 8) {
                pos[1] = radius;
                flag = 1;
            } else if (func_15046C80(pos, 0, radius, &ptr->unk2C) != 0) {
                pos[1] = ptr->unk2C;
            } else {
                pos[1] = radius;
                flag = 1;
            }
            if (ptr->unk26 != -1) {
                D_8008F970[ptr->unk26](arg0, pos, angle, flag);
            }
            ptr->unk28 -= 1.0f;
        } while (ptr->unk28 > 1.0f);
    }
}

extern void func_151432BC(void *, f32 *, f32 *, f32 *, f32 *);

void func_151A8F1C(void *arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    func_151432BC(*(void **)((u8 *)arg0 + 0x2C), arg1, arg1 + 2, arg2, arg3);
    arg1[1] = arg2[0];
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1D4E00/func_151A8F6C.s")

void func_151A931C(u8 *, s32, u8);

void func_151A9024(u8 *arg0, s32 arg1, u8 arg2) {
    if (arg0[0x4C] == 1) {
        func_151A931C(arg0, arg1, arg2);
    }
}

extern void (*D_8008F984[])(void);
s32 func_151A9060(u8 *arg0)
{
  s32 new_var;
  s32 idx;
  arg0[0x16] |= 0x4;
  new_var = *((s32 *) (arg0 + 0x18));
  idx = new_var & 0xFFFFFFFFu;
  new_var = idx < 0;
  if (new_var || (idx >= 8))
  {
    return 1;
  }
  if (D_8008F984[idx])
  {
    D_8008F984[idx]();
  }
  return 1;
}


void func_151A90C0(s32 arg0, s32 arg1) {
    struct {
        s8 unk0;
        u8 pad1[3];
        s32 unk4;
        f32 unk8;
        f32 unkC;
        f32 unk10;
        f32 unk14;
        f32 unk18;
        f32 unk1C;
        f32 unk20;
        s8 unk24;
        s8 unk25;
        s8 unk26;
    } sp30;
    s32 sp28;
    f32 temp_f0;
    s32 temp_v0;

    sp30.unk0 = 2;
    sp30.unk4 = arg0;
    temp_f0 = (f32)(arg1 & 1);
    if (temp_f0) {
        sp30.unk8 = D_800A8F58;
    } else {
        sp30.unk8 = D_800A8F5C;
    }

    if (temp_f0) {
        sp30.unkC = D_800A8F60;
    } else {
        sp30.unkC = D_800A8F64;
    }

    temp_f0 = 0.0f;
    sp30.unk10 = temp_f0;
    sp30.unk14 = temp_f0;
    sp30.unk18 = temp_f0;
    sp30.unk1C = temp_f0;
    sp30.unk20 = temp_f0;
    sp30.unk24 = 1;
    sp30.unk25 = -1;
    sp30.unk26 = 0;
    ((s8 *)&sp28)[-4] = (s8)arg1;

    temp_v0 = func_151A8B20(&sp30, -1, 1, 0xFF, 0);
    if (temp_v0 != 0) {
        memcpy((void *)(temp_v0 + 0x80), ((s8 *)&sp28) - 4, 1);
    }
}

struct S6_151A91AC { s16 unk0; s16 unk2; s16 unk4; };
extern struct S6_151A91AC D_8008F9A4;

struct Loc_151A91AC {
    s32 unk0;
    s16 unk4;
    u8  unk6;
    u8  unk7;
    s32 unk8;
    s32 unkC;
    u8  unk10;
    u8  unk11;
    u8  unk12;
    u8  unk13;
    u8  unk14;
    u8  unk15;
    u8  unk16;
    u8  unk17;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    s32 unk24;
    s32 unk28;
};

void func_151A91AC(u8 *arg0, f32 *arg1, s32 arg2, s32 arg3) {
    struct Loc_151A91AC sp64;
    f32 fval;
    struct S6_151A91AC sp58;
    u32 idx;
    s32 r3;
    s32 r2;

    sp58 = D_8008F9A4;
    fval = func_150ADA68() * 50.0f + 50.0f;
    idx = (u32)func_150ADA20() % 3U;

    sp64.unk6 = (u8)((s16 *)&sp58)[idx];
    sp64.unk7 = 0;
    sp64.unk16 = 0;
    sp64.unk17 = 7;
    sp64.unk8 = 0;
    sp64.unkC = 0;
    sp64.unk0 = 0x1701;
    sp64.unk4 = 0x3C;
    sp64.unk10 = 0xA0;
    sp64.unk11 = 0xFF;
    sp64.unk12 = 0;
    sp64.unk13 = 0;
    sp64.unk14 = 0;
    sp64.unk15 = 0xFF;
    sp64.unk18 = 0x3B0002;

    r2 = func_150ADA20();
    r3 = func_150ADA20();
    func_1513C650((s32)&sp64, 1, 0, (s32)(arg0 + 0x58), arg1[0], arg1[1], arg1[2],
                  fval, fval, r2 & 0xFF,
                  (r3 & 1) + (func_150ADA20() & 1), 3, 0xFF, 0,
                  arg0[0xC], arg0[1]);
}

void func_151A931C(u8 *arg0, s32 arg1, u8 arg2) {
    u8 *ptr;

    if (arg2 == 0x17) {
        ptr = arg0 + 0x28;
        if (*(u8 *)arg1 != arg0[0x80]) {
            goto ret;
        }
        *ptr |= 1;
    ret:
        return;
    } else if (arg2 == 0x18) {
        ptr = arg0 + 0x28;
        if (*(u8 *)arg1 == arg0[0x80]) {
            *ptr &= ~1;
        }
    }
}

typedef struct {
    f32 unk0;
    f32 unk4;
    u8  unk8;
    u8  unk9;
    u8  unkA;
    u8  unkB;
    u8  unkC;
    u8  padD[3];
    void *unk10;
} Def_151A9390;

typedef struct {
    f32 x;
    f32 y;
    f32 z;
} Vec3f_151A9390;

typedef struct {
    s16 unk0;
    s16 unk2;
    s16 unk4;
} Pos_151A9390;

typedef struct {
    u8  unk0;
    u8  pad1[3];
    void *unk4;
    f32 unk8;
    f32 unkC;
    Vec3f_151A9390 unk10;
    f32 unk1C;
    f32 unk20;
    s8  unk24;
    s8  unk25;
    s8  unk26;
    u8  pad27;
} Header_151A9390;

extern Def_151A9390 D_8008F9AC[];

void *func_1516284C(Header *, s32 *, s32, s32, s32, u8, u8, s32, u8, u8, s32);

void func_151A9390(u8 arg0, u8 arg1, Pos_151A9390 *arg2, Vec3f_151A9390 *arg3,
                   f32 arg4, f32 arg5, s16 arg6, u8 arg7, s32 arg8) {
    Header_151A9390 hdr;
    s32 effect;

    if (arg1 >= 9) {
        return;
    }

    hdr.unk0 = 1 | ((arg2 != NULL) ? 2 : 0) | ((arg0 & 1) ? 4 : 0) | ((arg0 & 2) ? 8 : 0);
    hdr.unk4 = arg2;
    hdr.unk8 = D_8008F9AC[arg1].unk0;
    hdr.unkC = D_8008F9AC[arg1].unk4;
    if (arg3 != NULL) {
        hdr.unk10 = *arg3;
    } else {
        hdr.unk10.x = 0.0f;
        hdr.unk10.y = 0.0f;
        hdr.unk10.z = 0.0f;
    }
    hdr.unk1C = arg4;
    hdr.unk20 = arg5;
    hdr.unk24 = 2;
    hdr.unk25 = -1;
    hdr.unk26 = 1;

    effect = func_151A8B20(&hdr, arg6, 0x2C, arg7, arg8);
    if (effect != 0) {
        u8 *ptr;

        ptr = (u8 *)(effect + 0x80);
        memcpy(ptr, D_8008F9AC[arg1].unk10, 0x2C);
        if (arg0 & 8) {
            ptr[0x28] |= 1;
        }
        if (arg0 & 0x10) {
            ptr[0x28] |= 2;
        }
    }

    if (arg0 & 4) {
        Header spawn;
        s32 pos[3];

        spawn.unk0 = ((arg6 == -1) ? 0 : 1) | 2;
        spawn.unk1 = 2;
        spawn.unk2 = (arg6 == -1) ? 0x12C : arg6;
        spawn.unk4 = D_8008F9AC[arg1].unkB;

        if (arg3 != NULL) {
            pos[0] = (s32)arg3->x;
            pos[1] = (s32)arg3->y;
            pos[2] = (s32)arg3->z;
        } else {
            pos[0] = arg2->unk0;
            pos[1] = arg2->unk2;
            pos[2] = arg2->unk4;
        }

        func_1516284C(&spawn, pos, D_8008F9AC[arg1].unk8, D_8008F9AC[arg1].unk9,
                      D_8008F9AC[arg1].unkA, 0xFF, 0, 0, D_8008F9AC[arg1].unkC,
                      0xFF, 1);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1D4E00/func_151A9634.s")

typedef struct {
    f32 unk0;
    u8 pad4[0x14];
    s32 unk18;
    u8 unk1C;
    u8 unk1D;
    u8 pad1E[2];
    s32 unk20;
} Struct151A9834;

typedef struct {
    f32 x;
    f32 y;
    f32 z;
} Vec3f151A9834;

void func_151A9834(f32 *arg0, f32 arg1, f32 arg2, Struct151A9834 *arg3,
                   s32 arg4, u8 arg5, s32 arg6, u8 arg7, s32 arg8) {
    Struct151A9834 sp8C;
    Vec3f151A9834 sp80;
    Vec3f151A9834 sp74;
    f32 temp_f22;
    f32 temp_f20;
    f32 temp_f0;

    if (arg3 == 0) {
        arg3 = &sp8C;
        sp8C.unk0 = D_800A8F68;
        sp8C.unk18 = 0;
        sp8C.unk1C = 7;
        sp8C.unk1D = 0;
        sp8C.unk20 = 0;
    }

    sp80.y = arg0[1];
    if (arg4 > 0) {
        temp_f22 = D_800A8F6C;
        do {
            temp_f20 = func_150ADA68();
            temp_f0 = func_150ADA68();
            func_1514373C((temp_f20 + temp_f20) * temp_f22, temp_f0 * arg2,
                          &sp80.x, &sp80.z);
            sp80.x += arg0[0];
            sp80.z += arg0[2];

            if (func_15046C80(&sp80.x, 0, arg1, arg3) != 0) {
                sp74.x = sp80.x;
                sp74.y = arg3->unk0;
                sp74.z = sp80.z;
                D_8008FA60[arg5](&sp74.x, arg3, arg6, arg7, arg8);
            }
            arg4--;
        } while (arg4 > 0);
    }
}
