#include <ultra64.h>
#define func_15178E14 func_15178E14_header_mismatch
#define func_15048A40 func_15048A40_header_mismatch
#define func_150ADA20 func_150ADA20_header_mismatch
#include "functions.h"
#undef func_15178E14
#undef func_15048A40
#undef func_150ADA20
#include "variables.h"

typedef struct Func15178750Inner {
    u8 pad0[0x36];
    u8 unk36;
} Func15178750Inner;

typedef struct Func15178750Arg1 {
    u8 pad0[0x14];
    Func15178750Inner *unk14;
} Func15178750Arg1;

extern s32 func_15168118();

extern f32 func_15048A40(u8);
extern f32 func_150489B0(u8);
extern u32 func_150ADA20(void);
extern void *func_15167A68(s32, s32, s32, s32, s32, s32);
extern s32 D_8008CA64;

/* The 0x38-byte init block bcopy()ed into a fresh sprite object at +0x10. */
typedef struct ParticleInit {
    /* 0x00 */ s32 animPtr;
    /* 0x04 */ void *owner;
    /* 0x08 */ s32 unk08;
    /* 0x0C */ s16 animFrame;
    /* 0x0E */ s16 animSpeed;
    /* 0x10 */ s16 x;
    /* 0x12 */ s16 y;
    /* 0x14 */ s16 z;
    /* 0x16 */ s16 velX;
    /* 0x18 */ s16 velZ;
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ u8 xFrac;
    /* 0x1D */ u8 zFrac;
    /* 0x1E */ u8 yFrac;
    /* 0x1F */ s8 updateFuncIdx;
    /* 0x20 */ s16 velY;
    /* 0x22 */ s16 accelY;
    /* 0x24 */ s16 width;
    /* 0x26 */ s16 height;
    /* 0x28 */ s16 lifetime;
    /* 0x2A */ s8 alphaFade;
    /* 0x2B */ u8 expireFuncIdx;
    /* 0x2C */ u8 primR;
    /* 0x2D */ u8 primG;
    /* 0x2E */ u8 primB;
    /* 0x2F */ u8 alpha;
    /* 0x30 */ u8 envR;
    /* 0x31 */ u8 envG;
    /* 0x32 */ u8 envB;
    /* 0x34 */ s16 flags;
} ParticleInit;

typedef struct Emitter15177F90 {
    char pad0[0x10];
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 unk20;
    char pad24[0xA];
    /* 0x2E */ s16 unk2E;
    /* 0x30 */ s16 unk30;
    /* 0x32 */ s16 unk32;
    /* 0x34 */ u8 unk34;
    /* 0x35 */ u8 unk35;
    char pad36[0x1];
    /* 0x37 */ u8 unk37;
} Emitter15177F90;

typedef struct Sprite15177F90 {
    char pad0[0x10];
    /* 0x10 */ ParticleInit init;
    /* 0x48 */ s8 unk48;
} Sprite15177F90;

void func_15177F90(u8 arg0, s32 arg1, u8 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, u8 arg8, s32 arg9, s32 arg10) {
    ParticleInit init;
    Emitter15177F90 *emitter;
    Sprite15177F90 *sprite;
    s32 count;
    s32 i;
    s32 angle;
    f32 sn;
    f32 cs;
    f32 dist;
    s32 x;
    s32 z;
    s32 y;
    s32 yOff;

    emitter = func_15167A68(0x3A, 0, 0x38, 0, arg8, 1);
    if (emitter == NULL) {
        return;
    }

    if (arg10 == 0) {
        arg10 = 0x118;
    } else {
        arg10 = 0x8C;
    }

    if (arg1 != 0) {
        emitter->unk10 = arg1;
        emitter->unk14 = 0x80000000;
    } else {
        emitter->unk10 = (arg3 << 16) | (arg4 & 0xFFFF);
        emitter->unk14 = arg5 << 16;
    }
    emitter->unk18 = arg3;
    emitter->unk1C = arg4;
    emitter->unk20 = arg5;
    emitter->unk30 = 0;
    emitter->unk32 = 0x320;
    emitter->unk35 = arg0;
    emitter->unk34 = arg2;
    emitter->unk2E = 0;
    emitter->unk37 = arg9;

    init.owner = emitter;
    init.velX = 0;
    init.velZ = 0;
    init.unk1A = 0;
    init.updateFuncIdx = 6;
    init.velY = 0;
    init.accelY = 0;
    init.width = arg10;
    init.height = arg10;
    init.alphaFade = 0;
    init.primR = 0xFF;
    init.primG = 0xFF;
    init.primB = 0xFF;
    init.alpha = 0xFF;
    init.flags = 0;
    init.animPtr = D_8008CA64;
    init.lifetime = arg7;

    count = arg0;
    for (i = 0; i < count; i++) {
        angle = func_150ADA20() & 0xFF;
        sn = func_15048A40((u8)angle);
        cs = func_150489B0((u8)angle);
        dist = (f32)(func_150ADA20() & 0xFFFF) * 50.0f * (1.0f / 65536.0f);
        x = (s32)((f32)arg3 + dist * sn);
        z = (s32)((f32)arg5 + dist * cs);
        yOff = func_150ADA20() & 0xFF;
        y = yOff + arg4 - 0x4E;

        init.expireFuncIdx = (func_150ADA20() & 7) + 7;
        init.animFrame = 0;
        init.animSpeed = 0;
        init.x = x;
        init.y = y;
        init.z = z;

        sprite = func_15167A68(0x3B, 0, 0x4C, 0, arg8, 1);
        if (sprite == NULL) {
            return;
        }
        bcopy(&init, &sprite->init, 0x38);
        sprite->unk48 = -1;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1A5440/func_15178268.s")

s32 func_15178750(s32 arg0, Func15178750Arg1 *arg1, s16 arg2) {
    Func15178750Inner *temp;

    temp = arg1->unk14;
    if (temp->unk36 & (1 << arg2)) {
        return func_15168118();
    }
    return arg0;
}

static void func_15178750_pad(void) {
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1A5440/func_151787AC.s")

typedef struct Node15178B98 {
    char pad0[0x8];
    struct Node15178B98 *unk8;
    char padC[0x4];
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    char pad24[0xC];
    s16 unk30;
    char pad32[0x2];
    u8 unk34;
} Node15178B98;

extern Node15178B98 *D_800DCF38;

Node15178B98 *func_15178B98(u8 arg0) {
    Node15178B98 *node;

    for (node = D_800DCF38; node != NULL; node = node->unk8) {
        if (node->unk34 == arg0) {
            return node;
        }
    }
    return NULL;
}

Node15178B98 *func_15178BE4(u8 arg0, s32 arg1, s16 arg2) {
    Node15178B98 *node;

    node = func_15178B98(arg0);
    if (node != NULL) {
        node->unk10 = arg1;
        node->unk14 = 0x80000000;
        node->unk30 = arg2;
    }
}

Node15178B98 *func_15178C34(u8 arg0, s32 arg1, s32 arg2, s32 arg3, s16 arg4) {
    Node15178B98 *node;

    node = func_15178B98(arg0);
    if (node != NULL) {
        node->unk10 = (arg1 << 16) | (arg2 & 0xFFFF);
        node->unk14 = arg3 << 16;
        node->unk30 = arg4;
    }
}

extern f32 sqrtf(f32);

s32 func_15178C9C(u8 arg0, s32 arg1) {
    Node15178B98 *node;
    s32 dx;
    s32 dy;
    s32 dz;
    s32 sum;

    node = func_15178B98(arg0);
    if (node != NULL) {
        dx = (s32)(D_800CC2D0[arg1].x_position - (f32)node->unk18);
        dy = (s32)(D_800CC2D0[arg1].y_position - (f32)node->unk1C);
        dz = (s32)(D_800CC2D0[arg1].z_position - (f32)node->unk20);
        dx = dx * dx;
        dy = dy * dy;
        dz = dz * dz;
        sum = dx + dy + dz;
        return (s32)sqrtf((f32)sum);
    }
    return 1;
}

typedef struct Node15178DA4 {
    char pad0[0x8];
    struct Node15178DA4 *unk8;
    char padC[0x8];
    struct Node15178DA4 *unk14;
    char pad18[0x16];
    u16 unk2E;
} Node15178DA4;

extern Node15178DA4 *D_800DCF3C;

void func_15178DA4(Node15178DA4 *arg0) {
    Node15178DA4 *next;
    Node15178DA4 *node;

    node = D_800DCF3C;
    func_100111C8(arg0->unk2E);
    if (node != NULL) {
        do {
            next = node->unk8;
            if (arg0 == node->unk14) {
                func_1516972C((struct102 *)node);
            }
            node = next;
        } while (next != NULL);
    }
    func_15169824((struct102 *)arg0);
}

void func_15178E14(u8 arg0) {
    func_15178DA4(func_15178B98(arg0));
}
