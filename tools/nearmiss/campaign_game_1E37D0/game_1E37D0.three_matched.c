#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern void func_150A7960(f32 *, f32, f32, f32, f32 *, f32 *, f32 *);
extern s32 func_15147A80(void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
} Vec151B6320;

typedef struct {
    Vec151B6320 unk0;
    s16 unkC;
    s16 unkE;
    s32 unk10;
    u8 unk14;
    u8 unk15;
    u8 pad16[2];
    s32 unk18;
} Header151B6320;

typedef struct {
    f32 *unk0;
    u8 unk4;
    u8 pad5[3];
    Vec151B6320 unk8;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    s32 unk28;
    s32 unk2C;
} Payload151B6320;

typedef struct {
    s32 unk0;
    u8 pad4[0x14 - 0x4];
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
    u8 pad2C[0x38 - 0x2C];
    f32 unk38;
    f32 unk3C;
    f32 unk40;
} struct151B76CCObj;

typedef struct {
    u8 pad0[4];
    struct151B76CCObj **unk4;
} struct151B76CCList;

typedef struct {
    u8 pad0[0x98];
    struct151B76CCList *unk98;
} struct151B76CCArg0;

void func_151B6320(f32 *arg0, u8 arg1, s32 arg2) {
    Header151B6320 header;
    Payload151B6320 payload;
    s32 *temp_v0;

    header.unk15 = 0xA;
    header.unk0.unk0 = arg0[5];
    header.unk0.unk4 = arg0[6];
    header.unk0.unk8 = arg0[7];
    header.unkC = 0x12C;
    header.unkE = 6;
    payload.unk0 = arg0;
    payload.unk4 = *(u8 *)((u8 *)arg0 + 0x3B);
    payload.unk8 = header.unk0;
    payload.unk14 = 0.0f;
    payload.unk18 = 0.0f;
    payload.unk20 = -16384.0f;
    payload.unk1C = -16384.0f;
    payload.unk24 = 0.0f;
    header.unk10 = 0xD;

    temp_v0 = (s32 *)func_15147A80(&header, 0x30, 0x1C, 0xB, 0xB, 0xB, 0, 0, 0, arg1, arg2);
    if (temp_v0 != NULL) {
        memcpy((void *)temp_v0[0x98 / 4], &payload, 0x2C);
    }
}

typedef struct {
    Vec151B6320 unk0;
    f32 unkC;
    u8 unk10;
    u8 pad11[3];
    f32 unk14;
    f32 unk18;
} Trail151B6420;

typedef struct {
    u8 pad0[0x1E];
    u16 unk1E;
    u8 pad20[0x25 - 0x20];
    u8 unk25;
    u8 pad26[0x2C - 0x26];
    s8 unk2C;
    s8 unk2D;
    s8 unk2E;
    u8 pad2F[0x54 - 0x2F];
    Vec151B6320 unk54;
    u8 pad60[0x94 - 0x60];
    Trail151B6420 *unk94;
} Obj151B6420;

s32 func_151B6420(Obj151B6420 *arg0) {
    Trail151B6420 *trail = arg0->unk94;
    s32 i;
    s32 n;
    f32 base;
    f32 diff;

    if ((arg0->unk2C < 2) && (arg0->unk1E & 8)) {
        return 0;
    }
    i = arg0->unk2E;
    while (i != arg0->unk2D) {
        i--;
        if (i < 0) {
            i = arg0->unk25 - 1;
        }
        (trail + i)->unkC -= D_800BE9A4;
        if ((trail + i)->unkC < 0.0f) {
            while (i != arg0->unk2D) {
                arg0->unk2D++;
                if (arg0->unk2D == arg0->unk25) {
                    arg0->unk2D = 0;
                }
                arg0->unk2C--;
            }
        }
    }
    if (arg0->unk2C > 0) {
        base = trail[arg0->unk2D].unk18;
        i = arg0->unk2D;
        do {
            diff = (trail + i)->unk18 - base;
            n = diff * 0.4940000176f;
            if (n > 155) {
                (trail + i)->unk10 = 155;
            } else {
                (trail + i)->unk10 = n;
            }
            i++;
            if (i >= arg0->unk25) {
                i = 0;
            }
        } while (i != arg0->unk2E);
    }
    if (arg0->unk2C > 0) {
        arg0->unk54 = trail[arg0->unk2D].unk0;
    } else {
        arg0->unk54.unk0 = 0.0f;
        arg0->unk54.unk4 = 0.0f;
        arg0->unk54.unk8 = 0.0f;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1E37D0/func_151B65D4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1E37D0/func_151B6928.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1E37D0/func_151B70B4.s")

typedef struct {
    s32 unk0;
    s32 unk4;
    s16 unk8;
    s16 unkA;
    s32 unkC;
    s32 unk10;
    u8 unk14;
    u8 unk15;
    u8 unk16;
    u8 unk17;
    u8 unk18;
    u8 unk19;
    u8 unk1A;
    u8 unk1B;
    u8 unk1C;
    u8 unk1D;
    s16 unk1E;
    s16 unk20;
    s16 unk22;
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    Vec151B6320 unk30;
    Vec151B6320 unk3C;
    Vec151B6320 unk48;
    f32 unk54;
    s32 unk58;
    s32 unk5C;
    u8 unk60;
    u8 unk61;
    s8 unk62;
    s8 unk63;
    s8 unk64;
    u8 unk65;
    u8 unk66;
    u8 pad67[9];
} Spawn151B7144;

extern void *func_15130280(void *, u8, s32, s32, u8, s32);

void func_151B7144(f32 *arg0, u8 arg1, s32 arg2) {
    Spawn151B7144 sp28;
    s32 temp_v0;
    s32 temp_v1;

    sp28.unk1D = 0x29;
    sp28.unk8 = 0xE03;
    sp28.unk0 = 0x200005;
    sp28.unk4 = 0;
    sp28.unkC = 0;
    sp28.unk10 = 0;
    sp28.unk1E = 0x12;
    sp28.unk20 = 0xE;
    if (func_150ADA20() & 1) {
        temp_v1 = 0x40;
    } else {
        temp_v1 = 0;
    }
    if (func_150ADA20() & 1) {
        temp_v0 = 0x80;
    } else {
        temp_v0 = 0;
    }
    sp28.unk58 = temp_v0 | 1 | temp_v1 | 0x8000 | 0x4000 | 0x800 | 0x400 | 0x200 | 0x10000;
    sp28.unk60 = 3;
    sp28.unk61 = 3;
    sp28.unk62 = -1;
    sp28.unk63 = -1;
    sp28.unk64 = -1;
    sp28.unk65 = 0;
    sp28.unk22 = 0x28;
    sp28.unk14 = 0xDD;
    sp28.unk15 = 0xD3;
    sp28.unk16 = 0xCD;
    sp28.unk17 = 0xFF;
    sp28.unk18 = 0x57;
    sp28.unk19 = 0x55;
    sp28.unk1A = 0x5A;
    sp28.unk1C = 0xFF;
    sp28.unk54 = 0.0f;
    sp28.unk24 = 1.05674696f;
    sp28.unk30.unk0 = arg0[5];
    sp28.unk30.unk4 = arg0[6];
    sp28.unk30.unk8 = arg0[7];
    sp28.unk3C.unk0 = 0.0f;
    sp28.unk3C.unk4 = 0.0f;
    sp28.unk3C.unk8 = 0.0f;
    sp28.unk1B = (func_150ADA20() % 0x38U) + 0xC8;
    sp28.unkA = (func_150ADA20() % 10U) + 0x1E;
    sp28.unk28 = sp28.unk2C = (func_150ADA68() * 50.0f) + 89.0f;
    sp28.unk48.unk0 = 0.0f;
    sp28.unk48.unk4 = 0.0f;
    sp28.unk48.unk8 = 0.0f;
    func_15130280(&sp28, 1, 0, 0, arg1, arg2);
}

typedef struct {
    s32 unk0;
    s32 unk4;
    u8 unk8;
    u8 pad9[3];
    s32 unkC;
} Payload151B7328;

typedef struct {
    Vec151B6320 unk0;
    s16 unkC;
    s16 unkE;
    s32 unk10;
    u8 unk14;
    u8 unk15;
    u8 pad16[2];
} Header151B7328;

extern s32 (*D_8008FB90[])(void *, void *);

void *func_151B7328(void *arg0, u8 arg1, s32 arg2, u8 arg3, s32 arg4) {
    void *ret;
    Header151B7328 header;
    Payload151B7328 payload;
    s32 *sub;
    Spawn151B7144 spawn;

    payload.unk0 = 0;
    payload.unk4 = 0;
    payload.unk8 = arg1;
    header.unk15 = 0x14;
    header.unk0 = *(Vec151B6320 *)&D_800A5480;
    header.unkC = 0x12C;
    header.unkE = 0x14;
    header.unk10 = 0x10;
    header.unk14 = 2;
    ret = (void *)func_15147A80(&header, arg2 + 0x10, 0x14, 0, 0xE, 0xE, 0, 0, 0, arg3, arg4);
    if (ret != NULL) {
        sub = *(s32 **)((u8 *)ret + 0x98);
        memcpy(sub, &payload, 0xC);
        sub[1] = (s32)(sub + 4);
        memcpy((void *)sub[1], arg0, arg2);
        if (D_8008FB90[arg1](ret, (u8 *)ret + 0x10) == 0) {
            func_1516972C(ret);
            return NULL;
        } else {
            const s32 tbl[4] = { 0x60, 0x61, 0x62, 0x63 };
            s32 temp_v0;
            s32 temp_v1;

            spawn.unk1D = tbl[func_150ADA20() & 3];
            spawn.unk8 = 0x1303;
            spawn.unk0 = 0x200005;
            spawn.unk4 = 0;
            spawn.unkA = 0x12C;
            spawn.unkC = 0;
            spawn.unk10 = 0;
            spawn.unk14 = 0xFF;
            spawn.unk15 = 0xFF;
            spawn.unk16 = 0xFF;
            spawn.unk17 = 0xFF;
            spawn.unk18 = 0xFF;
            spawn.unk19 = 0xFF;
            spawn.unk1A = 0xFF;
            spawn.unk1B = 0xFF;
            spawn.unk1C = 0xFF;
            spawn.unk28 = spawn.unk2C = (func_150ADA68() * 800.0f) + 1700.0f;
            spawn.unk30 = header.unk0;
            spawn.unk3C = *(Vec151B6320 *)&D_800A5480;
            spawn.unk48 = *(Vec151B6320 *)&D_800A5480;
            spawn.unk1E = 1;
            spawn.unk20 = 0xFF;
            spawn.unk22 = 1;
            spawn.unk54 = 0.0f;
            spawn.unk24 = 1.0f;
            if (func_150ADA20() & 1) {
                temp_v1 = 0x40;
            } else {
                temp_v1 = 0;
            }
            if (func_150ADA20() & 1) {
                temp_v0 = 0x80;
            } else {
                temp_v0 = 0;
            }
            spawn.unk58 = temp_v0 | temp_v1 | 0x4000 | 0x8000 | 0x40000;
            spawn.unk60 = 6;
            spawn.unk61 = 5;
            spawn.unk62 = -1;
            spawn.unk63 = -1;
            spawn.unk64 = -1;
            spawn.unk65 = 0;
            spawn.unk5C = 0;
            spawn.unk66 = 0xFF;
            *sub = (s32)func_15130280(&spawn, 1, 0, 0, arg3, arg4);
        }
    }
    return ret;
}

s32 func_151B7678(struct151B76CCArg0 *arg0, f32 *arg1) {
    struct151B76CCList *list;
    struct151B76CCObj **entry;
    struct151B76CCObj *obj;

    list = arg0->unk98;
    entry = list->unk4;
    obj = *entry;
    if ((obj->unk0 == 0) || (*((u8 *) entry + 4) != *((u8 *) obj + 0x3B))) {
        return 0;
    }

    arg1[0] = obj->unk14;
    arg1[1] = obj->unk18;
    arg1[2] = obj->unk1C;
    return 1;
}

s32 func_151B76CC(struct151B76CCArg0 *arg0, f32 *arg1) {
    struct151B76CCList *list;
    struct151B76CCObj **objPtr;
    struct151B76CCObj *obj;
    f32 mtx[4][4];

    list = arg0->unk98;
    objPtr = list->unk4;
    obj = *objPtr;
    func_150A8050(mtx, obj->unk20, obj->unk24, obj->unk28);
    mtx[3][0] = obj->unk38;
    mtx[3][1] = obj->unk3C;
    mtx[3][2] = obj->unk40;
    mtx[0][0] *= obj->unk18;
    mtx[0][1] *= obj->unk18;
    mtx[0][2] *= obj->unk18;
    mtx[1][0] *= obj->unk1C;
    mtx[1][1] *= obj->unk1C;
    mtx[1][2] *= obj->unk1C;
    mtx[2][0] *= obj->unk18;
    mtx[2][1] *= obj->unk18;
    mtx[2][2] *= obj->unk18;
    func_150A7960(mtx[0], 0.0f, 0.0f, -250.0f, arg1, arg1 + 1, arg1 + 2);
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1E37D0/func_151B77F4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1E37D0/func_151B7998.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1E37D0/func_151B7C38.s")

extern void (*D_8008FB98[])(void *, s32, u8);

void func_151B82CC(void *arg0, s32 arg1, u8 arg2) {
    void *v0 = *(void **)((u8 *)arg0 + 0x98);
    void (*f)(void *, s32, u8) = D_8008FB98[*(u8 *)((u8 *)v0 + 0x8)];
    if (f != 0) {
        f(arg0, arg1, arg2);
    }
}

struct S151B8318 {
    s32 unk0;
    u8 unk4;
};

struct T151B8318 {
    s32 unk0;
    struct S151B8318 *unk4;
};

void func_151B8318(struct102 *arg0, struct S151B8318 *arg1, u8 arg2) {
    int id;
    struct T151B8318 *v0 = *(struct T151B8318 **)((u8 *)arg0 + 0x98);
    struct S151B8318 *v1 = v0->unk4;

    if (arg2 == 0) {
        if ((v1->unk0 == (id = arg1->unk0)) || (arg1->unk4 == v1->unk4)) {
            func_1516972C(arg0);
        }
    }
}

void func_151B8370(void *arg0) {
    s32 v0 = *(s32 *)((u8 *)arg0 + 0x98);
    struct102 *v = *(struct102 **)v0;
    if (v != 0) {
        func_1516972C(v);
    }
}

extern void func_151B8370(void *);
extern void func_151478F4(void *);

void func_151B83A0(void *arg0) {
    func_151B8370(arg0);
    func_151478F4(arg0);
}

extern void func_15147928(void *);

void func_151B83CC(void *arg0) {
    func_151B8370(arg0);
    func_15147928(arg0);
}
