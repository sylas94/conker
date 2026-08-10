#include <ultra64.h>
#include "functions.h"
#include "variables.h"

typedef struct {
    u8 pad_0x0[0x10];
    u8 field_0x10;
    u8 field_0x11;
    s8 field_0x12;
    s8 field_0x13;
    f32 field_0x14;
    f32 field_0x18;
    f32 field_0x1C;
    f32 field_0x20;
} CompactOscillatorMotionState;

typedef struct {
    u8 pad_0x0[0x2C];
    f32 field_0x2C;
    f32 field_0x30;
    u8 pad_0x34[0xDC];
    CompactOscillatorMotionState field_0x110;
} CompactOscillatorObject;

void func_151B1918(struct260 *arg0);
void func_15149368(struct260 *arg0);


#pragma GLOBAL_ASM("asm/nonmatchings/game_1DD500/func_151B0050.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1DD500/func_151B01B8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1DD500/func_151B03B8.s")

extern u8 D_800A3FE6[];
s32 func_15134070(struct102 *);

typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
} TrailNode;

typedef struct {
    /* 0x00 */ struct102 *owner;
    /* 0x04 */ u8 ownerId;
    /* 0x08 */ s32 count;
    /* 0x0C */ TrailNode nodes[11];
    /* 0x90 */ f32 unk90;
    /* 0x94 */ u8 isSmall;
} TrailPayload;

typedef struct {
    /* 0x00 */ struct102 *owner;
    /* 0x04 */ u8 ownerId;
} ActorEvent;

struct260 *func_151B09BC(struct102 *arg0, struct102 *arg1, s16 arg2, u8 arg3, s32 arg4) {
    struct260 *result;
    TrailPayload payload;
    ActorEvent evt;
    s32 kind;
    s16 life;
    u8 timed;
    s32 i;

    if (arg0 == NULL) {
        return NULL;
    }

    kind = 4;
    if (arg1 != NULL) {
        kind = arg1->unk4;
        if (kind == 0x53 || kind == 0xA5) {
            kind = 4;
        } else {
            kind = func_15134070(arg1);
        }
    }

    if (kind == 0x63) {
        return NULL;
    }

    if (D_800A3FE6[kind << 4] == 2) {
        return NULL;
    }

    if (D_800A3FE6[kind << 4] == 1) {
        payload.isSmall = 1;
    } else {
        payload.isSmall = 0;
    }

    evt.owner = arg0;
    evt.ownerId = *(u8 *)((u8 *)arg0 + 0x3B);
    func_151494E0((s32)&evt, 0x13);

    timed = 0;
    if (arg2 == -1) {
        life = 0x12C;
    } else {
        life = arg2;
        timed = 1;
    }

    payload.owner = arg0;
    payload.ownerId = *(u8 *)((u8 *)arg0 + 0x3B);
    payload.count = 0;
    payload.unk90 = 0.0f;
    payload.nodes[0].unk0 = 0;
    payload.nodes[0].unk4 = 0;
    payload.nodes[0].unk8 = 0;
    payload.nodes[1].unk0 = 0;
    payload.nodes[1].unk4 = 0;
    payload.nodes[1].unk8 = 0;
    payload.nodes[2].unk0 = 0;
    payload.nodes[2].unk4 = 0;
    payload.nodes[2].unk8 = 0;
    for (i = 3; i < 11; i++) {
        payload.nodes[i].unk0 = 0;
        payload.nodes[i].unk4 = 0;
        payload.nodes[i].unk8 = 0;
    }

    result = func_151491F4(life, -1, 0x13, timed, 0xF, 0x98, arg3, arg4);
    if (result != NULL) {
        memcpy((u8 *)result + 0x28, &payload, 0x98);
    }
    return result;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1DD500/func_151B0B88.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1DD500/func_151B118C.s")

s32 func_151B1478(struct260 *arg0) {
    s32 v1;
    if (*(s16 *)((u8 *)arg0 + 0x1C) < 0x20) {
        v1 = *(s16 *)((u8 *)arg0 + 0x1C) << 3;
        if (v1 < *(u8 *)((u8 *)arg0 + 0x5C)) {
            *(u8 *)((u8 *)arg0 + 0x5C) = v1;
        }
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1DD500/func_151B14AC.s")

s32 func_151B1828(CompactOscillatorObject *arg0) {
    CompactOscillatorObject *p = arg0;
    CompactOscillatorMotionState *f = &arg0->field_0x110;
    f32 r1;
    f32 r2;
    f->field_0x10 = f->field_0x10 + f->field_0x12 * D_800BE9E4;
    f->field_0x11 = f->field_0x11 + f->field_0x13 * D_800BE9E4;
    r1 = func_151423D8((u8)(f->field_0x10 - 0x40));
    r2 = func_151423D8((u8)(f->field_0x11 - 0x40));
    p->field_0x2C += (f->field_0x14 + f->field_0x1C * r1 - p->field_0x2C) * 0.5f;
    p->field_0x30 += (f->field_0x18 + f->field_0x20 * r2 - p->field_0x30) * 0.5f;
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1DD500/func_151B1918.s")

typedef struct {
    s32 unk0;
    u8  unk4;
} SubA151B19A4;

typedef struct {
    s32 unk0;
    union {
        s32 w4;
        u8  b4;
    } u4;
    u8  unk8;
    u8  unk9;
} ArgB151B19A4;

void func_151B19A4(struct260 *arg0, s32 arg1, u8 arg2) {
    SubA151B19A4 *temp_v0 = (SubA151B19A4 *)((u8 *)arg0 + 0x28);
    ArgB151B19A4 *b = (ArgB151B19A4 *)arg1;
    s32 v1 = temp_v0->unk0;

    if (arg2 == 0 || arg2 == 0x13) {
        if ((v1 == b->unk0) || (b->u4.b4 == temp_v0->unk4)) {
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

void func_151B1A58(struct260 *arg0) {
    func_151B1918(arg0);
    func_1514933C(arg0);
}

void func_151B1A84(struct260 *arg0) {
    func_151B1918(arg0);
    func_15149368(arg0);
}

void func_151B1AB0(void *arg0) {
    struct260 *temp_v0;
    struct {
        void *unk0;
        u8 unk4;
        f32 unk8;
    } sp28;

    if (*(s32 *)&arg0 != 0) {
        sp28.unk0 = arg0;
        sp28.unk4 = *(u8 *)((s32)arg0 + 0x3B);
        sp28.unk8 = 0.0f;

        temp_v0 = func_151491F4(0x3C, -1, 0x15, 1, 0x11, 0xC, 0xFF, 1);
        if (temp_v0 != NULL) {
            memcpy((void *)((s32)temp_v0 + 0x28), &sp28, 0xC);
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1DD500/func_151B1B34.s")

void func_151B1FAC(struct260 *arg0, s32 arg1, u8 arg2) {
    SubA151B19A4 *temp_v0 = (SubA151B19A4 *)((u8 *)arg0 + 0x28);
    ArgB151B19A4 *b = (ArgB151B19A4 *)arg1;
    s32 b0;

    if (arg2 == 0x2D) {
        if (temp_v0->unk0 == b->unk0) {
            temp_v0->unk0 = b->u4.w4;
            temp_v0->unk4 = b->unk9;
        } else {
            if (temp_v0->unk0 == b->u4.w4) {
                temp_v0->unk0 = b->unk0;
                ((volatile SubA151B19A4 *)temp_v0)->unk4 = b->unk8;
            }
trailing_label_151B1FAC:
            ;
        }
    } else if (arg2 == 0) {
        b0 = b->unk0;
        if ((b0 == temp_v0->unk0) || (b->u4.b4 == temp_v0->unk4)) {
            func_1516972C((struct102 *)arg0);
        }
    }
}
