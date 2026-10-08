#include <ultra64.h>
#include "functions.h"
#include "variables.h"

typedef struct {
    s32 unk0;
    s32 unk4;
} Vec2_15102B38;

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} Vec3_15102B38;

typedef struct {
    u8 unk0;
    u8 unk1;
    s16 unk2;
    s16 unk4;
    u8 pad6[2];
    s32 unk8;
    s32 unkC;
    u8 unk10;
    u8 unk11;
    u8 unk12;
    u8 unk13;
    Vec2_15102B38 unk14;
    Vec3_15102B38 unk1C;
    Vec3_15102B38 unk28;
    f32 unk34;
    f32 unk38;
    f32 unk3C;
    s32 unk40;
    u8 unk44;
    u8 unk45;
    u8 unk46;
    u8 unk47;
    s32 unk48;
    u8 unk4C;
    u8 pad4D[3];
    s32 unk50;
    s16 unk54;
    s16 unk56;
} Struct15102B38;

typedef struct {
    void *unk0;
    u8 unk4;
    u8 pad5[3];
    s32 unk8;
    s16 unkC;
    u8 padE[2];
    s32 unk10;
    u8 unk14;
    u8 pad15[3];
    Vec3_15102B38 unk18;
    Vec3_15102B38 unk24;
} Payload15102B38;

typedef struct {
    Payload15102B38 payload;
    Struct15102B38 header;
    s32 temp_v0;
} Locals15102B38;

extern void func_15103254(s16 arg0, u8 arg1, f32 arg2, s32 arg3, u8 arg4, u8 arg5, s32 arg6);


#pragma GLOBAL_ASM("asm/nonmatchings/game_12FDD0/func_15102920.s")

s32 func_15102B38(struct127 *arg0, u8 arg1, Vec3_15102B38 *arg2, Vec3_15102B38 *arg3, Vec2_15102B38 *arg4, s16 arg5, u8 arg6, f32 arg7, s32 arg8, u8 arg9, s32 argA, s16 argB, u8 argC, s32 argD) {
    Locals15102B38 sp;
    s32 flag;

    if (arg0 == NULL) {
        return 0;
    }

    sp.payload.unk14 = 0;
    sp.payload.unk18 = *(Vec3_15102B38 *)&D_800A5480;
    sp.payload.unk24 = *(Vec3_15102B38 *)&D_800A5480;
    sp.payload.unk10 = arg1;
    sp.payload.unk0 = arg0;
    sp.payload.unkC = argB;
    sp.payload.unk4 = arg0->unique_id;
    sp.payload.unk8 = arg1 << 6;
    sp.header.unk0 = 0x5F;
    sp.header.unk1 = 5;
    sp.header.unk2 = 0x2203;
    sp.header.unk8 = 0;
    sp.header.unkC = 0;
    sp.header.unk4 = arg5;
    sp.header.unk10 = 0xFF;
    sp.header.unk11 = 0xFF;
    sp.header.unk12 = 0xFF;
    sp.header.unk13 = 0xFF;
    sp.header.unk14 = *arg4;
    sp.header.unk1C = *arg2;
    sp.header.unk28 = *arg3;
    sp.header.unk40 = 0x40CC0009;
    sp.header.unk44 = arg6;
    sp.header.unk45 = 0xFF;
    sp.header.unk46 = 0;
    sp.header.unk47 = 7;
    sp.header.unk34 = 0.0f;
    sp.header.unk38 = 0.0f;
    sp.header.unk3C = 0.0f;
    sp.header.unk4C = arg9;

    if (func_150ADA20() & 1) {
        flag = 2;
    } else {
        flag = 0;
    }

    sp.temp_v0 = (s32)func_1513D2F0(&sp.header, &D_800A4AA0, 0x29, 0, 0, 0x16, flag + 1, 0, 0, argA + 0x30, argC, argD);
    if (sp.temp_v0 != 0) {
        memcpy((void *)(sp.temp_v0 + 0x110), &sp.payload, 0x30);
    }

    func_15103254(arg5, arg6, arg7, arg8, arg9, argC, argD);
    return sp.temp_v0;
}

void func_15102D50(s32 arg0, s32 arg1, u8 arg2) {
    func_15169850(arg1, arg2, arg0 + 0x110, arg0 + 0x114, arg0);
}

typedef struct {
    u8 pad0[0x34];
    Vec3_15102B38 unk34;
    Vec3_15102B38 unk40;
    u8 pad4C[0xC4];
    Payload15102B38 unk110;
} Obj15102D90;

extern s32 func_1514654C(struct127 *, struct126 *, s32, void *, void *, s32);
extern s32 func_15145EA4(s32 *arg0, s32 *arg1, s32 arg2, s32 arg3);

s32 func_15102D90(Obj15102D90 *arg0) {
    struct127 *actor;
    Payload15102B38 *p;
    s32 src[2];
    s32 dst[2];

    p = &arg0->unk110;
    p->unk14 &= ~1;
    actor = p->unk0;
    if (actor->unique_id != p->unk4 || actor->interaction_state == 0) {
        return 0;
    }
    if (actor->unk1D4 == NULL || (actor->unk74 & 0xF) == 0xF) {
        return 1;
    }
    src[0] = (s32)&arg0->unk34;
    src[1] = (s32)&arg0->unk40;
    dst[0] = (s32)&p->unk18;
    dst[1] = (s32)&p->unk24;
    if (p->unkC != -1) {
        struct126 *temp;

        temp = func_1503195C(actor, p->unkC, 0);
        if (temp == NULL) {
            return 0;
        }
        if (func_1514654C(actor, temp, p->unk10, src, dst, 2) == 0) {
            return 0;
        }
    } else {
        func_15145EA4(src, dst, (s32)actor->unk1D4 + p->unk8, 2);
    }
    p->unk14 |= 1;
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_12FDD0/func_15102EB8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_12FDD0/func_15103254.s")
