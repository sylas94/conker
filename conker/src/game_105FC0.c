#include <ultra64.h>
#define func_10010F88 func_10010F88_void
#include "functions.h"
#undef func_10010F88
#include "variables.h"

typedef struct {
    struct17 unk0;
    s16 unkC;
    s16 unkE;
    s32 unk10;
    u8 unk14;
    u8 unk15;
    u8 pad16[2];
    s32 unk18;
} Header150D8B88;

typedef struct {
    void *unk0;
    u8 unk4;
    u8 pad5[3];
    struct17 unk8;
    struct17 unk14;
    struct17 unk20;
    f32 unk2C;
    s16 unk30;
    u8 pad32[2];
    f32 unk34;
    f32 unk38;
    f32 unk3C;
    f32 unk40;
    f32 unk44;
    f32 unk48;
    u8 unk4C;
    u8 unk4D;
    u8 pad4E[2];
    u8 pad50[4];
} Payload150D8B88;

typedef struct {
    char pad_0x00[0xC];
    s32 field_0x0C;
} ActorA8State;

extern f32 D_800A0B48;
extern f32 D_800A0B4C;
extern f32 D_800A0B50;
extern s32 func_151EF610(void);
extern void func_1000D96C(s32, s32, s32);
extern s32 func_10010F88(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
extern s32 func_15147A80(void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
extern void func_15131828(void *, void *, void *, void *);
extern void func_15131958(void *, s32, void *);


void func_150D8B10(f32 *a0, f32 *a1) {
    a1[0] = a0[5];
    a1[1] = a0[6] + 20.0f;
    a1[2] = a0[7];
}

extern u8 D_800BE616;
extern f32 D_800A0B40;
extern f32 D_800A0B44;
void func_15145740(void *, void *, void *, void *, f32);

void func_150D8B3C(void *arg0, void *arg1) {
    f32 sp34[3];
    f32 sp28[3];

    func_15145740(arg0, sp34, sp28, arg1, D_800BE616 ? D_800A0B40 : D_800A0B44);
}

void func_150D8B88(f32 *arg0) {
    Header150D8B88 header;
    Payload150D8B88 payload;
    struct17 vec;
    s32 *temp_v0;
    s32 temp_a0;

    if (*(s32 *)((u8 *)arg0 + 0x31C) != 0) {
        if (D_800BE9F0 == 0xA) {
            func_1000D96C(0xA, 0x37, 0);
        }

        func_150D8B10(arg0, (f32 *)&header.unk0);
        payload.unk4D = 0;
        payload.unk4C = 1;
        payload.unk0 = arg0;
        payload.unk4 = ((u8 *)arg0)[0x3B];
        vec = header.unk0;
        payload.unk8 = vec;
        payload.unk14 = vec;
        func_150D8B3C(arg0, &payload.unk20);

        payload.unk3C = D_800A0B48;
        temp_a0 = func_151EF610() % 2;
        payload.unk30 = func_10010F88(temp_a0 + 0x1B6, 0x7FFF, 0, 0, 0, 0, 0, 0, 0x1F4, 0x1388);
        payload.unk34 = 0.0f;
        payload.unk2C = 0.0f;
        payload.unk40 = 0.0f;
        payload.unk44 = 0.0f;
        payload.unk48 = 0.0f;
        payload.unk38 = -16384.0f;

        if (*(s32 *)((u8 *)arg0 + 0x31C) != 0) {
            if (*(u8 *)(*(s32 *)((u8 *)arg0 + 0x31C) + 0x84) != 0) {
                payload.unk4C &= ~1;
            }
        }

        header.unk15 = 0x32;
        header.unkC = 0x12C;
        header.unkE = 0x36;
        header.unk10 = 2;
        header.unk14 = 5;
        header.unk18 = 0;

        temp_v0 = (s32 *)func_15147A80(&header, 0x50, 0x24, 0xE, 1, 0x11, 3, 0xFF, 0, 0xFF, 1);
        if (temp_v0 != 0) {
            memcpy((void *)temp_v0[0x98 / 4], &payload, 0x50);
        }
    }
}

void func_150D8D84(struct17 *arg0, struct17 *arg1, f32 arg2) {
    struct17 sp4;

    sp4 = *arg1;
    arg1->unk4 += D_800A0B4C * arg2;
    arg0->unk0 += sp4.unk0 * arg2;
    arg0->unk4 += (sp4.unk4 * arg2) + ((D_800A0B50 * arg2) * arg2);
    arg0->unk8 += sp4.unk8 * arg2;
}

typedef struct {
    char pad0[0x1C];
    u16 unk1C;
    u16 unk1E;
    char pad20[0x10];
    u8 unk30;
} ConkerStruct150D8E1C;

void func_150D8E1C(ConkerStruct150D8E1C *arg0) {
    arg0->unk30 = 0;
    arg0->unk1E &= ~0x2;
    arg0->unk1E |= 0x8;
    arg0->unk1E |= 1;
    arg0->unk1C = 0x28;
}

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} Func150D8E4CVec;

typedef struct {
    Func150D8E4CVec unk0;
    struct17 unkC;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
} Func150D8E4CEntry;

typedef struct {
    struct127 *unk0;
    u8 pad4[0x49];
    s8 unk4D;
} Func150D8E4CPayload;

typedef struct {
    u8 pad0[0x1E];
    u16 unk1E;
    u8 pad20[5];
    u8 unk25;
    u8 pad26[6];
    s8 unk2C;
    s8 unk2D;
    s8 unk2E;
    u8 pad2F[0x25];
    f32 unk54;
    f32 unk58;
    f32 unk5C;
    u8 pad60[0x34];
    Func150D8E4CEntry *unk94;
    Func150D8E4CPayload *unk98;
} Func150D8E4CObj;

s32 func_150D8E4C(Func150D8E4CObj *arg0)
{
    Func150D8E4CPayload *payload;
    Func150D8E4CEntry *base;
    Func150D8E4CEntry *entry;
    struct127 *actor;
    struct126 *stats;
    s32 i;
    s32 stride;

    payload = arg0->unk98;
    base = arg0->unk94;
    if ((arg0->unk2C < 2) && (arg0->unk1E & 8)) {
        return 0;
    }

    i = arg0->unk2E;
    if (i != arg0->unk2D) {
        do {
            i -= 1;
            if (i < 0) {
                i = arg0->unk25 - 1;
            }
            entry = &base[i];
            func_150D8D84((struct17 *)entry, &entry->unkC, D_800BE9A4);
        } while (i != arg0->unk2D);
    }

    stride = sizeof(Func150D8E4CEntry);
stride_set:
    if (arg0->unk2C > 0) {
        *((Func150D8E4CVec *)&arg0->unk54) =
            ((Func150D8E4CEntry *)((u8 *)base + (arg0->unk2D * stride)))->unk0;
    } else {
        arg0->unk54 = 0.0f;
        arg0->unk58 = 0.0f;
        arg0->unk5C = 0.0f;
    }

    payload->unk4D += D_800BE9E4;
    if (payload->unk4D >= 0x3D) {
        actor = payload->unk0;
        if (actor != NULL) {
            stats = actor->unk31C;
            if (stats != NULL) {
                stats->unk1AA++;
            }
        }
        payload->unk4D = 0;
    }

    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_105FC0/func_150D8FAC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_105FC0/func_150D942C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_105FC0/func_150D9C7C.s")

void func_150DA484(void *arg0) {
    u16 *temp = (u16 *)*(u32 *)((u8 *)arg0 + 0x98);
    if (temp[0x18] != 0) {
        func_100111C8(temp[0x18]);
    }
}

void func_150DA484(void *);
void func_151478F4(void *);

void func_150DA4B4(void *arg0) {
    func_150DA484(arg0);
    func_151478F4(arg0);
}

void func_15147928(void *);

void func_150DA4E0(void *arg0) {
    func_150DA484(arg0);
    func_15147928(arg0);
}

typedef struct {
    s32 unk0;
    u8 unk4;
    char pad5[0x3C - 0x5];
    f32 unk3C;
} SubA_150DA50C;

typedef struct {
    s32 unk0;
    union {
        u8 b4;
        s32 w4;
    } u4;
    union {
        f32 f8;
        struct {
            u8 b8;
            u8 b9;
        } s;
    } u8;
} ArgB_150DA50C;

void func_150DA50C(void *arg0, s32 arg1, u8 arg2) {
    SubA_150DA50C *temp_v1 = *(SubA_150DA50C **)((u8 *)arg0 + 0x98);
    ArgB_150DA50C *b = (ArgB_150DA50C *)arg1;
    s32 temp;

    if (arg2 == 0x44) {
        if ((b->unk0 == temp_v1->unk0) || (b->u4.b4 == temp_v1->unk4)) {
            temp_v1->unk3C = b->u8.f8;
        }
trailing_label_150DA50C:
        ;
    } else if (arg2 == 0) {
        temp = b->unk0;
        if ((temp == temp_v1->unk0) || (temp_v1->unk4 == b->u4.b4)) {
            func_1516972C(arg0);
        }
    } else if (arg2 == 0x2D) {
        if (temp_v1->unk0 == b->unk0) {
            temp_v1->unk0 = b->u4.w4;
            temp_v1->unk4 = b->u8.s.b9;
        } else if (temp_v1->unk0 == b->u4.w4) {
            temp_v1->unk0 = b->unk0;
            temp_v1->unk4 = b->u8.s.b8;
        }
    }
}

struct s_150DA5EC {
    s32 unk0;
    u8 unk4;
    f32 unk8;
};

extern void func_15147D64(struct s_150DA5EC *, s32);

void func_150DA5EC(u8 *arg0, f32 arg1) {
    struct s_150DA5EC sp1C;

    sp1C.unk0 = (s32) arg0;
    sp1C.unk4 = arg0[0x3B];
    sp1C.unk8 = arg1;
    func_15147D64(&sp1C, 0x44);
}

s32 func_150DA628(u8 *arg0, s32 arg1) {
    ActorA8State *temp_a2;

    temp_a2 = (ActorA8State *)(arg0 + 0xA8);
    func_15131828(arg0, arg0 + 0xAC, temp_a2, arg0 + 0xAA);
    func_15131958(arg0 + 0x58, temp_a2->field_0x0C, temp_a2);
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_105FC0/func_150DA67C.s")
