#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern f32 D_800A5760;
extern void *func_15167A68(s32, s32, s32, s32, s32, s32);
extern s32 *func_1515D480(s32);
extern s32 *func_1515D440(void);
extern s32 (*D_8008A200[])(void *, s8);
extern s32 (*D_8008A23C[])(void *, s8);
extern s32 (*D_8008A284[])(void *, s8);

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
} Struct15147A80Copy;

typedef struct {
    u8 pad0[0x94];
    u8 *unk94;
    u8 *unk98;
    u8 pad9C[4];
    u8 unkA0[1];
} Struct15147A80Obj;

void func_15147740(void *arg0) {
    s32 mode;
    s8 failed;

    failed = 0;
    if (*(u16 *)((u8 *)arg0 + 0x1E) & 1) {
        *(s16 *)((u8 *)arg0 + 0x1C) -= D_800BE9E4;
        if (*(s16 *)((u8 *)arg0 + 0x1C) < 0) {
            failed = 1;
        }
    }

    if (*(u8 *)((u8 *)arg0 + 0x2F) >= 0xF) {
        func_1516972C((struct102 *)arg0);
        return;
    }
    if (*(u8 *)((u8 *)arg0 + 0x2F) != 0) {
        if (failed == 0) {
            if (D_8008A200[*(u8 *)((u8 *)arg0 + 0x2F)](arg0, failed) == 0) {
                failed = 1;
            }
        }
    }

    if (*(u8 *)((u8 *)arg0 + 0x30) >= 0x12) {
        func_1516972C((struct102 *)arg0);
        return;
    }
    if (*(u8 *)((u8 *)arg0 + 0x30) != 0) {
        if (failed == 0) {
            if (D_8008A23C[*(u8 *)((u8 *)arg0 + 0x30)](arg0, failed) == 0) {
                failed = 1;
            }
        }
    }

    if (*(u16 *)((u8 *)arg0 + 0x1E) & 0x10) {
        mode = *(s8 *)((u8 *)arg0 + 0x24);
        if ((mode < -1) || (mode >= 8)) {
            func_1516972C((struct102 *)arg0);
            return;
        }
        if (mode != -1) {
            if (failed == 0) {
                if (D_8008A284[mode](arg0, failed) == 0) {
                    failed = 1;
                }
            }
        }
    }

    if (failed) {
        func_1516972C((struct102 *)arg0);
    }
}

extern void func_151D5E30(void *);

void func_151478D0(void *arg0) {
    func_151D5E30((void *)((u8 *)arg0 + 0x84));
}

extern void func_1514795C(void *);

void func_151478F4(void *arg0) {
    func_151478D0(arg0);
    func_1514795C(arg0);
    func_15169804((struct102 *)arg0);
}

void func_15147928(void *arg0) {
    func_151478D0(arg0);
    func_1514795C(arg0);
    func_15169824((struct102 *)arg0);
}

void func_1514795C(void *arg0) {
    s32 i;
    s32 *p;

    for (i = 0, p = (s32 *)arg0; i <= D_80082FA0; i++, p++) {
        if (p[0xF] != 0) {
            func_100043B4((s32 *)p[0xF], 4);
        }
    }

    p = (s32 *)((s32 *)arg0)[0x13];
    if (((s32 *)arg0)[0x13] != 0) {
        func_100043B4(p, 4);
    }
}

extern void (*D_8008A2F0[])(void *);

void func_151479E0(void *arg0) {
    s32 idx = *(s32 *)((u8 *)arg0 + 0x20);
    if (idx < 0) {
        idx = 0;
    } else if (idx >= 0x14) {
        idx = 0;
    }
    D_8008A2F0[idx](arg0);
}

extern void (*D_8008A340[])(void *);

void func_15147A30(void *arg0) {
    s32 idx = *(s32 *)((u8 *)arg0 + 0x20);
    if (idx < 0) {
        idx = 0;
    } else if (idx >= 0x14) {
        idx = 0;
    }
    D_8008A340[idx](arg0);
}

void *func_15147A80(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, void *arg8, s32 arg9, s32 argA) {
    void *temp_v0;
    u8 id;
    s32 size;
    s32 i;

    size = *(u8 *)((u8 *)arg0 + 0x15) * arg2;
    if (*(u16 *)((u8 *)arg0 + 0xE) & 0x40) {
        id = 0x4D;
    } else {
        id = 0x22;
    }

    temp_v0 = func_15167A68(id, argA, arg1 + size + 0xA0, 1, (u8)arg9, 1);
    if (temp_v0 == NULL) {
        return NULL;
    }

    *(s32 *)((u8 *)temp_v0 + 0x98) = (s32)((u8 *)temp_v0 + 0xA0);
    *(s32 *)((u8 *)temp_v0 + 0x94) = *(s32 *)((u8 *)temp_v0 + 0x98) + arg1;
    memcpy((u8 *)temp_v0 + 0x10, arg0, 0x1C);
    *(u8 *)((u8 *)temp_v0 + 0x2C) = 0;
    *(u8 *)((u8 *)temp_v0 + 0x2D) = 0;
    *(u8 *)((u8 *)temp_v0 + 0x2E) = 0;
    *(u8 *)((u8 *)temp_v0 + 0x2F) = arg3;
    *(u8 *)((u8 *)temp_v0 + 0x30) = arg4;
    *(u8 *)((u8 *)temp_v0 + 0x31) = arg5;

    if (arg8 != NULL) {
        *(Struct15147A80Copy *)((u8 *)temp_v0 + 0x60) = *(Struct15147A80Copy *)arg8;
    } else {
        *(u8 *)((u8 *)temp_v0 + 0x7C) = 0;
    }

    *(s32 *)((u8 *)temp_v0 + 0x34) = arg6;
    *(s32 *)((u8 *)temp_v0 + 0x50) = arg7;
    *(u8 *)((u8 *)temp_v0 + 0x38) = 0;

    for (i = 0; i < 4; i++) {
        *(s32 *)((u8 *)temp_v0 + 0x3C + (i * 4)) = 0;
    }
    *(s32 *)((u8 *)temp_v0 + 0x4C) = 0;

    if (arg6 != 0) {
        for (i = 0; i <= D_80082FA0; i++) {
            *(s32 **)((u8 *)temp_v0 + 0x3C + (i * 4)) = func_1515D480(arg6);
        }
        *(s32 **)((u8 *)temp_v0 + 0x4C) = func_1515D440();
    }

    *(f32 *)((u8 *)temp_v0 + 0x54) = 0.0f;
    *(f32 *)((u8 *)temp_v0 + 0x58) = 0.0f;
    *(f32 *)((u8 *)temp_v0 + 0x5C) = 0.0f;
    bzero((u8 *)temp_v0 + 0x84, 0x10);
    return temp_v0;
}

extern void *func_151462C8(void *, void *, u8, void *, s32, s16, void *, s32, void *);
extern void *(*D_8008A2A4[])(void *, void *, s16);

void *func_15147C4C(void *arg0, void *arg1, s16 arg2) {
    s32 v0;
    u8 v1;

    if (*(u16 *)((u8 *)arg1 + 0x1E) & 0x20) {
        v0 = *(s32 *)((u8 *)arg1 + 0x28);
    } else {
        v0 = 0;
    }
    arg0 = func_151462C8(arg0, (u8 *)arg1 + 0x34, 0, 0, 0, arg2, (u8 *)arg1 + 0x54, 2, (void *)v0);
    v1 = *(u8 *)((u8 *)arg1 + 0x31);
    if (v1 >= 0x13) {
        func_1516972C((struct102 *)arg1);
        return arg0;
    }
    if (v1 != 0) {
        return D_8008A2A4[v1](arg1, arg0, arg2);
    }
    return arg0;
}

extern void (*D_8008A390[])(void *, s32, u8);

void func_15147D1C(void *arg0, s32 arg1, u8 arg2) {
    void (*fn)(void *, s32, u8) = D_8008A390[*(s32 *)((u8 *)arg0 + 0x20)];
    if (fn != NULL) {
        fn(arg0, arg1, arg2);
    }
}

void func_15147D64(s32 arg0, u8 arg1) {
    func_15169260(&D_800A5760, 2, arg0, arg1);
}
