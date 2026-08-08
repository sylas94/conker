#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern void (*D_8008FC70[])(void *, s16, void *);
extern void *func_151D8868(void *arg0, s32 arg1, s32 arg2, s32 arg3);
extern f32 D_800AB1D4;
extern f32 D_800AB1D8;
extern f32 D_800AB1DC;
extern f32 D_800AB1E0;
extern f32 D_800AB1E4;
extern f32 D_800AB1E8;
extern f32 D_800AB1EC;
extern f32 D_800AB1F0;
extern f32 D_800AB1F4;
extern f32 D_800AB1F8;
extern f32 D_800AB21C;
extern f32 D_800AB220;
extern f32 D_800AB224;
extern f32 D_800AB228;
extern f32 D_800AB22C;
extern f32 D_800AB230;
extern f32 D_800AB234;
extern s32 allocate_memory(s32, s32, s32, s32);

void func_1503F404(void *, void *, void *, void *, void *, void *, void *, void *, void *, void *);
s32 func_15132A4C(void *, s32, s32, s32, u8, s32);
void func_15131828(void *, void *, void *, void *);
void func_15131958(void *, s32, void *);
void func_151541B8(void *, f32, s32, f32, f32, u8, s32);
struct conker151D5514;
void func_1514FCE8(struct conker151D5514 *a0, u8 a1, s32 a2);

typedef struct {
    char pad_0x00[0xC];
    s32 field_0x0C;
} ActorA8State;

#pragma GLOBAL_ASM("asm/nonmatchings/game_200930/func_151D3480.s")

struct Sub151D3D50 {
    s16 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
};

struct Vec151D3D50 {
    s32 unk0;
    s32 unk4;
    s32 unk8;
};

s32 func_151D3D50(void *arg0) {
    struct Sub151D3D50 *p = (struct Sub151D3D50 *)((u8 *)arg0 + 0x170);
    if (p->unk0 > 0) {
        p->unk4 = p->unk4 + p->unk8 * D_800BE9A4;
        p->unk4 = func_15144B68(p->unk4);
        *(f32 *)((u8 *)arg0 + 0x24) = *(f32 *)((u8 *)arg0 + 0x54) + sinf(p->unk4) * p->unkC;
        p->unk0 = p->unk0 - D_800BE9E4;
    } else {
        *(struct Vec151D3D50 *)((u8 *)arg0 + 0x20) = *(struct Vec151D3D50 *)((u8 *)arg0 + 0x50);
    }
    return 1;
}

void func_15143134(void *, s32, s32);

void func_151D3E04(s32 *arg0, f32 *arg1, void *arg2, u8 arg3, f32 arg4) {
    if (arg0[0x1D4 / 4] != 0) {
        func_15143134(arg2, (s32)arg1, arg0[0x1D4 / 4] + (arg3 << 6));
    } else {
        arg1[0] = *(f32 *)((u8 *)arg0 + 0x14);
        arg1[1] = *(f32 *)((u8 *)arg0 + 0x18) + arg4;
        arg1[2] = *(f32 *)((u8 *)arg0 + 0x1C);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_200930/func_151D3E6C.s")

void func_151D3F14(f32 *arg0, u8 arg1, s32 arg2) {
    Header header;
    Header2 header2;

    header.unk0 = 3;
    header.unk1 = -1;
    header.unk2 = (func_150ADA20() % 3U) + 4;
    header.unk4 = 0;

    header2.unk0 = (s32) arg0[0];
    header2.unk4 = (s32) arg0[1];
    header2.unk8 = (s32) arg0[2];

    func_151602C0(&header, &header2, (func_150ADA20() % 13U) + 0x14, 0xFF, 0xE8, 0xAB, 0xFF, 0, 0, arg1, arg2);
}

void func_151D3FF4(f32 *arg0, u8 arg1, s32 arg2) {
    Header header;
    Header2 header2;

    header.unk0 = 3;
    header.unk1 = -1;
    header.unk2 = (func_150ADA20() % 0xBU) + 0x14;
    header.unk4 = 0;

    header2.unk0 = (s32) arg0[0];
    header2.unk4 = (s32) arg0[1];
    header2.unk8 = (s32) arg0[2];

    func_151602C0(&header, &header2, (func_150ADA20() % 0x18U) + 0x22, 0xFF, 0xA1, 0xA2, 0xFF, 0, 0, arg1, arg2);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_200930/func_151D40D4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_200930/func_151D42E8.s")

struct S151D4408Temps {
    f32 unk00;
    f32 unk04;
    f32 unk08;
    f32 unk0C;
    f32 unk10;
    f32 unk14;
    s32 pad18;
};

struct S151D4408 {
    f32 unk00;
    f32 unk04;
    f32 unk08;
    f32 unk0C;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    struct17 unk28;
    struct17 unk34;
    f32 unk40;
    f32 unk44;
    f32 unk48;
    f32 unk4C;
    s32 unk50;
    s16 unk54;
    s16 unk56;
    u8 unk58;
    u8 pad59[3];
    s32 unk5C;
    u8 unk60;
    u8 unk61;
    u8 unk62;
    u8 unk63;
    u8 unk64;
    u8 unk65;
    u8 unk66;
    u8 unk67;
    u8 unk68;
    u8 pad69;
    u8 unk6A;
    u8 pad6B;
    struct127 *unk6C;
    u8 unk70;
    u8 pad71;
    s16 unk72;
    s16 unk74;
    s32 pad78;
};

void func_151D4408(struct17 *arg0, struct17 *arg1, void *arg2, struct127 *arg3, f32 arg4, u8 arg5, s32 arg6) {
    struct S151D4408 sp54;
    struct S151D4408Temps sp38;
    f32 r;

    func_1503F404(arg2, &sp38.unk0C, &sp38.unk10, &sp38.unk14, &sp54.unk10, &sp54.unk14, &sp54.unk18, &sp38.unk00, &sp38.unk04, &sp38.unk08);
    sp54.unk10 += 180.0f;
block_151D4408:
    r = func_150ADA68();

    sp54.unk00 = 1.0f;
    sp54.unk04 = 1.0f;
    sp54.unk0C = D_800AB1D4 * arg4;
    sp54.unk08 = sp54.unk0C;
    sp54.unk1C = 1.0f;
    sp54.unk20 = 1.0f;
    sp54.unk24 = 1.0f;
    sp54.unk28 = *arg0;

    r = (r * 105.0f + 199.0f) * D_800AB1D8;
    sp54.unk34.unk0 = arg1->unk0 * r;
    sp54.unk34.unk4 = arg1->unk4 * r;
    sp54.unk34.unk8 = arg1->unk8 * r;

    sp54.unk40 = (func_150ADA68() * D_800AB1DC + D_800AB1E0) * D_800AB1E4;
    sp54.unk44 = 0.0f;
    sp54.unk48 = (func_150ADA68() * D_800AB1E8 + D_800AB1EC) * D_800AB1F0;
    sp54.unk4C = (func_150ADA68() * 320.0f + D_800AB1F4) * D_800AB1F8;
    sp54.unk50 = 0x29E8;
    sp54.unk54 = (func_150ADA20() & 7) + 0x1C;
    sp54.unk56 = 0x25;
    sp54.unk58 = 0;
    sp54.unk5C = 0;
    sp54.unk60 = 0xFF;
    sp54.unk61 = 8;
    sp54.unk62 = 0;
    sp54.unk63 = 0;
    sp54.unk64 = 0;
    sp54.unk65 = 0;
    sp54.unk66 = 0;
    sp54.unk67 = 0;
    sp54.unk68 = 2;
    sp54.unk6A = 1;
    sp54.unk6C = arg3;
    sp54.unk70 = arg3->unique_id;
    sp54.unk72 = 6;
    sp54.unk74 = 0x2A;
    func_15132A4C(&sp54, 3, 0xFF, 0, arg5, arg6);
}

struct S151D4668 {
    void *unk0;
    u8 unk4;
};

void func_151D4668(void *arg0) {
    struct S151D4668 sp18;
    sp18.unk0 = arg0;
    sp18.unk4 = *((u8 *)arg0 + 0x3B);
    func_151494E0((s32)&sp18, 0x3C);
}

struct S151D469C {
    void *unk0;
    u8 unk4;
    u8 pad5;
    s16 unk6;
    u8 unk8;
    u8 pad9[3];
    f32 unkC;
    u8 unk10;
    u8 pad11[3];
    u8 unk14[0xC];
};

void func_151D469C(void *arg0, s32 a1, s32 a2, s32 a3, s32 a4) {
    struct S151D469C sp38;
    struct260 *temp_v0;

    sp38.unk0 = arg0;
    sp38.unk4 = *((u8 *)arg0 + 0x3B);
    sp38.unk8 = *((u8 *)&a1 + 3);
    sp38.unkC = 0.0f;
    sp38.unk6 = -1;
    sp38.unk10 = 0;

    if (sp38.unk8 == 6) {
        sp38.unk6 = 0x82;
    }

    if (*(s32 *)((u8 *)arg0 + 0x1D4) != 0) {
        if ((*((u8 *)arg0 + 0x74) & 0xF) != 0xF) {
            D_8008FC70[*((u8 *)((s16 *)&a1 + 1) + 1)](arg0, sp38.unk6, &sp38.unk14);
            sp38.unk10 |= 1;
        }
    }

    temp_v0 = func_15149130((s16)a2, -1, 0x41, -1, 1, 0x35, (struct37 *)0x20, *((u8 *)&a3 + 3), a4);
    if (temp_v0 != NULL) {
        memcpy((void *)((s32)temp_v0 + 0x28), &sp38, 0x20);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_200930/func_151D4794.s")

void func_151D4C38(void *arg0, struct S151D469C *arg1, u8 arg2) {
    struct S151D469C *p;

    p = (struct S151D469C *)((u8 *)arg0 + 0x28);
    if (arg2 == 0x3C) {
        if ((arg1->unk0 == p->unk0) || (arg1->unk4 == p->unk4)) {
            func_1516972C((struct102 *)arg0);
        }
    } else if (arg2 == 4) {
        if ((arg1->unk0 == p->unk0) || (arg1->unk4 == p->unk4)) {
            p->unk10 = p->unk10 & ~1;
        }
block_151D4C38:
        ;
    } else {
        func_15149514((s32)arg1, arg2, (s32)p, (s32)&p->unk4, (s32)arg0);
    }
}

s32 func_151D4D04(u8 *arg0, s32 arg1) {
    ActorA8State *temp_a2;

    temp_a2 = (ActorA8State *)(arg0 + 0xA8);
    func_15131828(arg0, arg0 + 0xAC, temp_a2, arg0 + 0xAA);
    func_15131958(arg0 + 0x58, temp_a2->field_0x0C, temp_a2);
    return 1;
}

void func_151D469C(void *arg0, s32 a1, s32 a2, s32 a3, s32 a4);

void func_151D4D58(void *arg0) {
    func_151D469C(arg0, 0, 0x50, 0xFF, 1);
    func_151D469C(arg0, 1, 0x50, 0xFF, 1);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_200930/func_151D4DAC.s")

void func_151D5148(void *arg0) {
    s16 *p = *(s16 **)((u8 *)arg0 + 0x31C);
    if (p[0x24 / 2] > 0) {
        p[0x24 / 2]--;
        p = *(s16 **)((u8 *)arg0 + 0x31C);
    }
    p[0x1AA / 2]++;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_200930/func_151D5174.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_200930/func_151D5334.s")

struct S151D5404_30 {
    u8 unk0;
    u8 pad1;
    s16 unk2;
    u8 unk4;
    u8 unk5;
    u8 unk6;
    u8 pad7;
};

struct S151D5404_38 {
    struct17 unk0;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    u8 unk18;
    u8 pad19[7];
};

void func_151D5404(struct17 *arg0, f32 arg1, f32 arg2, f32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7) {
    struct S151D5404_38 sp38;
    struct S151D5404_30 sp30;
    void *temp_v0;
    s32 i;

    sp38.unk0 = *arg0;
    sp38.unkC = arg1;
    sp38.unk10 = arg2;
    sp38.unk14 = arg3;
    sp30.unk0 = 1;
    sp30.unk2 = (func_150ADA20() % (u32)((s16)arg5 + 1)) + (s16)arg4;
    sp30.unk4 = 0;
    sp30.unk6 = 0;

    for (i = 0; i < D_80082FA0 + 1; i++) {
        sp30.unk5 = 1 << i;
        sp38.unk18 = i;
        temp_v0 = func_151D8868(&sp30, 0x1C, 0xFF, 0);
        if (temp_v0 != NULL) {
            memcpy((u8 *)temp_v0 + 0x18, &sp38, 0x1C);
        }
    }
}

struct vec151D5514 {
    s32 unk00;
    s32 unk04;
    s32 unk08;
};

struct conker151D5514 {
    s16 unk00;
    s16 unk02;
    s16 unk04;
    s16 unk06;
    s32 unk08;
    s32 unk0C;
    struct vec151D5514 unk10;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    f32 unk30;
    s32 unk34;
    s32 unk38;
    f32 unk3C;
    f32 unk40;
    f32 unk44;
    f32 unk48;
    s16 unk4C;
    s16 unk4E;
    s16 unk50;
    s16 unk52;
    s16 unk54;
    s16 unk56;
    s8 unk58;
};

void func_151D5514(struct vec151D5514 *arg0, u8 arg1, s32 arg2) {
    struct conker151D5514 sp1C;

    sp1C.unk00 = 0;
    sp1C.unk02 = 0xFF;
    sp1C.unk04 = -0x40;
    sp1C.unk06 = 0x4A;
    sp1C.unk08 = 9;
    sp1C.unk0C = 3;
    sp1C.unk10 = *arg0;
    sp1C.unk1C = D_800AB21C;
    sp1C.unk20 = 214.0f;
    sp1C.unk24 = 203.0f;
    sp1C.unk28 = D_800AB220;
    sp1C.unk2C = D_800AB224;
    sp1C.unk30 = D_800AB228;
    sp1C.unk34 = 7;
    sp1C.unk38 = 3;
    sp1C.unk3C = 45.0f;
    sp1C.unk40 = D_800AB22C;
    sp1C.unk44 = D_800AB230;
    sp1C.unk48 = D_800AB234;
    sp1C.unk4C = 0xF;
    sp1C.unk4E = 0xF;
    sp1C.unk50 = 0x64;
    sp1C.unk52 = 0x64;
    sp1C.unk54 = 0xC;
    sp1C.unk56 = 0x14;
    sp1C.unk58 = 0;
    func_1514FCE8(&sp1C, arg1, arg2);
}

void func_151D5648(void *arg0, u8 arg1, s32 arg2) {
    union { f32 f; f64 _a; } temp_f0;
    u32 temp_a;

    func_151D5514(arg0, arg1, arg2);
    func_151D3FF4(arg0, arg1, arg2);
    temp_f0.f = func_150ADA68();
    temp_a = func_150ADA20();
    func_151541B8(arg0, temp_f0.f * 4.0f + 12.0f, 0x3FD20C49,
                  (f32)(u32)((temp_a % 0x38U) + 0xC8), 0.0f, arg1, arg2);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_200930/func_151D5714.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_200930/func_151D57F8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_200930/func_151D5A18.s")

extern s32 (*D_80086C90[])(struct127 *, struct127 *, s32);
s32 func_151452C4(struct17 *arg0, struct17 *arg1, struct17 *arg2, f32 arg3, struct17 *arg4, struct17 *arg5, f32 *arg6, f32 *arg7);

s32 func_151D5B6C(struct17 *arg0, struct17 *arg1, struct127 *arg2, s8 arg3, s32 arg4) {
    struct127 *obj;
    s32 i;
    s32 mask;
    struct17 point;
    struct17 hit0;
    struct17 hit1;
    f32 t0;
    f32 t1;
    f32 radius;

    mask = -1;
    for (i = 0; i < 25; i = (u8)(i + 1)) {
        obj = &D_800CC2D0[i];
        if (obj->interaction_state == 0) {
            continue;
        }
        if (obj->unk5 == 3) {
            continue;
        }
        if ((D_800BE9F0 != 0x23) && (obj->id == 0xFF)) {
            continue;
        }
        if (obj == arg2) {
            continue;
        }
        if ((obj->unkF8 & 0x40) == 0) {
            continue;
        }
        if ((arg3 != -1) && (D_80086C90[arg3](obj, arg2, arg4) == 0)) {
            continue;
        }
        if (obj->unkD2 < obj->unkD4) {
            radius = obj->unkD4;
        } else {
            radius = obj->unkD2;
        }
        point.unk0 = obj->x_position;
        point.unk4 = obj->y_position + obj->unkD6;
        point.unk8 = obj->z_position;
        if (func_151452C4(arg0, arg1, &point, radius + radius, &hit0, &hit1, &t0, &t1) != 0) {
            mask &= ~(1 << i);
        }
    }
    return mask;
}

void func_151D5D60(s32 arg0, s16 arg1, s32 arg2, s32 *arg3, s8 *arg4) {
    s8 sp27;
    s32 base;
    s32 *slot;

    if (arg4 == NULL) {
        arg4 = &sp27;
    }
    *arg4 = 0;

    slot = (s32 *)(*(s32 *)&arg0 + (arg1 * 4));
    base = *slot;
    if (base != 0) {
        goto block_6;
    }
    base = allocate_memory(arg2 * 2, 1, 2, 1);
    *slot = base;
    if (base == 0) {
        *arg3 = 0;
        return;
    }
    *arg4 = 1;
    base = *slot;

block_6:
    *arg3 = ((D_800BE9C0 != 0) ? 0 : arg2) + base;
}

void func_151D5E30(s32 *arg0) {
    s32 i;

    i = 0;
    do {
        if (arg0[i] != 0) {
            func_100043B4((s32 *)arg0[i], 3);
        }
        i = (u8)(i + 1);
    } while (i < 4);
}
