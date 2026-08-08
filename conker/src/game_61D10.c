#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/game_61D10/func_15034860.s")

extern s16 D_800C3EF0;
extern f32 D_80097D60;

struct Entry15034EB4 {
    u8 pad[0x34];
    f32 unk34;
    u8 pad2[0x8];
};

struct Obj15034EB4 {
    u8 pad[0x14C];
    f32 unk14C;
    u8 pad2[0x84];
    struct Entry15034EB4 *unk1D4;
};

void func_15034EB4(struct Obj15034EB4 *obj, s32 idx, s32 idx2) {
    f32 amt;
    struct Entry15034EB4 *e;
    struct Entry15034EB4 *e2;
    struct Entry15034EB4 *base;

    if (D_800C3EF0 != 0) {
        base = obj->unk1D4;
        amt = ((f32)D_800C3EF0 * D_80097D60) * obj->unk14C;
        e = &base[idx];
        e->unk34 -= amt;
        if (idx2 != -1) {
            e2 = &base[idx2];
            e2->unk34 -= amt;
        }
    }
}

extern u8 D_800C3F00;

void func_15034F20(void) {
    D_800C3F00 = 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_61D10/func_15034F30.s")

struct Entry150356C8 {
    u32 unk0;
    u8 unk4;
    u8 pad5[4];
    u8 unk9;
    u8 unkA;
    u8 unkB;
};

extern struct Entry150356C8 D_800C3F08[];

struct Entry150356C8 *func_150356C8(void) {
    if (D_800C3F00 == 15) {
        return NULL;
    }
    D_800C3F00++;
    return &D_800C3F08[D_800C3F00 - 1];
}


#pragma GLOBAL_ASM("asm/nonmatchings/game_61D10/func_15035714.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_61D10/func_15035808.s")

extern u8 D_80082FC0[];
extern u8 D_80083140[];

struct Obj15035D6C {
    u8 unk0;
    u8 pad1[2];
    u8 unk3;
    u8 pad4[2];
    u8 unk6;
    u8 pad7[0xC];
    u8 unk13;
    u8 unk14;
    u8 pad15[0xF];
    Gfx **unk24;
};

Gfx *func_15035D6C(Gfx *gfx, struct Obj15035D6C *obj, s32 red, s32 green, s32 blue) {
    struct Entry150356C8 *entry;
    s32 alpha;
    s32 i;
    s32 j;

    if (D_800C3F00 == 0) {
        return gfx;
    }

    gSPSetGeometryMode(gfx++, G_CULL_FRONT);

    for (i = 0; i < D_800C3F00; i++) {
        entry = &D_800C3F08[i];
        if (entry->unkB != 1) {
            continue;
        }
        if (entry->unk9 != obj->unk0) {
            continue;
        }
        if (entry->unkA != obj->unk6) {
            continue;
        }

        alpha = (entry->unk4 * obj->unk3) >> 8;

        gDPPipeSync(gfx++);
        gSPSegment(gfx++, 3, entry->unk0);
        gDPSetEnvColor(gfx++, red, green, blue, alpha);

        if (alpha < 255) {
            gSPSegment(gfx++, 8, D_80082FC0);
        } else {
            gSPSegment(gfx++, 8, D_80083140);
        }

        for (j = 0; j < obj->unk14; j++) {
            if (!(obj->unk13 & (1 << j))) {
                gSPDisplayList(gfx++, obj->unk24[j]);
            }
        }
    }

    gSPClearGeometryMode(gfx++, G_CULL_FRONT);

    return gfx;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_61D10/func_15035FE8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_61D10/func_15036148.s")
