#include <ultra64.h>
#define func_150ADA20 func_150ADA20_u8_decl_in_functions_h
#include "functions.h"
#undef func_150ADA20
u32 func_150ADA20(void);
#include "variables.h"

void func_151058B4();
extern void func_1000FD38(void *, void *, s32);
extern s32 func_151464B8(s16 *);

extern s32 *D_800DBF94;

typedef struct {
    s32 count;
    const u8 *list;
    struct127 *obj;
} Msg35;

void func_15104A80(struct131 *arg0) {
    struct127 *found;

    found = NULL;
    {
        s32 mask;
        s32 i;
        struct127 *obj;

        i = arg0 - D_800DBEF4;
        mask = D_800DBF94[i];
        if (mask != 0) {
            for (i = 0; i < 25 && found == NULL; i++) {
                obj = &D_800CC2D0[i];
                if (obj->interaction_state != 0 && (mask & (1U << i))) {
                    found = obj;
                }
            }
        }
    }
    if (((u8 *)arg0)[0x72] == 0xF9 || ((u8 *)arg0)[0x72] == 0xF8 || ((u8 *)arg0)[0x72] == 0xF7) {
        Msg35 msg;

        msg.obj = found;
        if (((u8 *)arg0)[0x72] == 0xF9) {
            const u8 list[9] = { 0, 1, 2, 3, 4, 5, 0xF, 0x10, 0x11 };

            msg.count = 9;
            msg.list = list;
        } else if (((u8 *)arg0)[0x72] == 0xF8) {
            const u8 list[9] = { 6, 7, 8, 0x18, 0x19, 0x1A, 0x12, 0x13, 0x14 };

            msg.count = 9;
            msg.list = list;
        } else if (((u8 *)arg0)[0x72] == 0xF7) {
            const u8 list[9] = { 9, 0xA, 0xB, 0xC, 0xD, 0xE, 0x15, 0x16, 0x17 };

            msg.count = 9;
            msg.list = list;
        }
        func_151494E0((s32)&msg, 0x35);
    } else if (((u8 *)arg0)[0x72] == 0xF6) {
        Msg35 msg2;

        msg2.obj = found;
        func_151494E0((s32)&msg2.obj, 0x38);
    }
}

typedef struct {
    void *target;
    f32 accum;
    s16 timer;
    f32 x;
    f32 y;
    f32 z;
    f32 radius;
    f32 yOffset;
    f32 floor;
    u8 pad24[0x20];
    s16 *unk44;
} Func15104C44Data;

typedef struct {
    s16 unk0;
    u8 unk2;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    f32 unk30;
    s8 unk34;
    s32 unk38;
    f32 unk3C;
    f32 unk40;
    s16 unk44;
    s16 unk46;
    u8 unk48;
    u8 unk49;
    u8 unk4A;
    u8 unk4B;
    u8 unk4C;
} Func15104C44Desc;

extern void func_15143874(s16, f32, f32 *, f32 *);
extern s32 func_15046C80(f32 *, s32, f32, f32 *);
extern void func_15105CE0(Func15104C44Desc *, s32, s32, s32);

void func_15104C44(struct131 *arg0) {
    Func15104C44Data *data;

    data = (Func15104C44Data *)((u8 *)arg0 + 0x28);
    if (data->timer >= 0) {
        data->timer -= D_800BE9E4;
        if (data->timer < 0) {
            func_1000FD38(func_1000EF40, data->target, 0);
        }
        if (func_151464B8(data->unk44) == 0) {
            data->accum += (0.1970000118f + func_150ADA68() * 0.3f) * D_800BE9A4;
            if (data->accum > 1.0f) {
                Func15104C44Desc desc;
                f32 pos[3];
                f32 offZ1;
                f32 offX1;
                f32 offZ2;
                f32 offX2;

                pos[1] = data->y + data->yOffset;
                desc.unk2 = 1;
                desc.unk34 = -1;
                desc.unk44 = 3;
                desc.unk46 = 4;
                desc.unk4C = 0;
                desc.unk40 = 45.0f;
                desc.unk3C = 25.0f;
                desc.unk4 = data->x;
                desc.unk8 = data->y + data->yOffset;
                desc.unkC = data->z;
                desc.unk14 = data->y + data->yOffset - 180.0f;
                desc.unk48 = 0x61;
                desc.unk49 = 0xF2;
                desc.unk4A = 0xFF;
                do {
                    func_15143874(func_150ADA20() & 0xFF, (func_150ADA68() * 0.5f + 0.5f) * data->radius, &pos[0], &pos[2]);
                    pos[0] += data->x;
                    pos[2] += data->z;
                    if (func_15046C80(pos, 0, data->y, &data->floor) != 0) {
                        func_15143874(func_150ADA20() & 0xFF, func_150ADA68() * 220.0f, &offX1, &offZ1);
                        func_15143874(func_150ADA20() & 0xFF, func_150ADA68() * 220.0f, &offX2, &offZ2);
                        desc.unk10 = data->x + offX1;
                        desc.unk18 = data->z + offZ1;
                        desc.unk28 = pos[0];
                        desc.unk2C = data->floor;
                        desc.unk30 = pos[2];
                        desc.unk1C = offX2 + pos[0];
                        desc.unk20 = desc.unk2C + 180.0f;
                        desc.unk24 = offZ2 + pos[2];
                        desc.unk0 = func_150ADA20() % 13U + 8;
                        desc.unk4B = func_150ADA20() % 156U + 100;
                        desc.unk38 = func_150ADA20() % 3U + 5;
                        func_15105CE0(&desc, 0, ((u8 *)arg0)[0xC], ((u8 *)arg0)[1]);
                    }
                    data->accum -= 1.0f;
                } while (data->accum > 1.0f);
            }
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_131F30/func_15104FF8.s")

typedef struct {
    f32 x;
    f32 y;
    f32 z;
} Func151050B0Vec;

typedef struct {
    u8 pad0[0x14];
    u8 unk14;
} Func151050B0Target;

typedef struct {
    Func151050B0Target *target;
    s16 timer;
    f32 accum;
    Func151050B0Vec pts[4];
    Func151050B0Vec dirs[4];
    s16 *unk6C;
} Func151050B0Data;

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    s16 unk14;
    s16 unk16;
    s16 unk18;
    s16 unk1A;
    s16 unk1C;
    s32 unk20;
    s32 unk24;
    u8 unk28;
    u8 unk29;
    u8 unk2A;
    u8 unk2B;
    u8 unk2C;
} Func151050B0Desc;

extern void func_15106F98(Func151050B0Vec *, Func151050B0Vec *, s32, Func151050B0Desc *, f32, s32, s32, s32);

void func_151050B0(struct131 *arg0) {
    Func151050B0Data *data;
    Func151050B0Desc desc;
    Func151050B0Vec from;
    Func151050B0Vec to;
    u8 a;
    u8 b;
    f32 t;

    data = (Func151050B0Data *)((u8 *)arg0 + 0x28);
    if (data->timer < 0) {
        data->target->unk14 = 1;
        return;
    }
    data->target->unk14 = 0;
    data->timer -= D_800BE9E4;
    if (data->timer < 0) {
        func_151494E0(0, 0x39);
        func_151494E0(0, 0x4B);
    }
    if (func_151464B8(data->unk6C) == 0) {
        data->accum += (0.04000000283f + func_150ADA68() * 0.07f) * D_800BE9A4;
        if (data->accum > 1.0f) {
            desc.unk0 = 10.0f;
            desc.unk4 = 15.0f;
            desc.unk8 = 20.0f;
            desc.unkC = 44.0f;
            desc.unk10 = 37.0f;
            desc.unk14 = 100;
            desc.unk16 = 0;
            desc.unk18 = 10;
            desc.unk1A = 1;
            desc.unk1C = 10;
            desc.unk20 = 4;
            desc.unk24 = 2;
            desc.unk28 = 0x7E;
            desc.unk29 = 0xF9;
            desc.unk2A = 0xFF;
            desc.unk2B = 0x37;
            desc.unk2C = 0xC8;
            do {
                a = func_150ADA68() * 3.0f;
                b = func_150ADA68() * 2 + 1 + a;
                if (b >= 4) {
                    b -= 4;
                }
                t = func_150ADA68();
                from.x = data->pts[a].x + data->dirs[a].x * t;
                from.y = data->pts[a].y + data->dirs[a].y * t;
                from.z = data->pts[a].z + data->dirs[a].z * t;
                t = func_150ADA68();
                to.x = data->pts[b].x + data->dirs[b].x * t;
                to.y = data->pts[b].y + data->dirs[b].y * t;
                to.z = data->pts[b].z + data->dirs[b].z * t;
                func_15106F98(&from, &to, 3, &desc, 0.3250000179f, 2, ((u8 *)arg0)[0xC], ((u8 *)arg0)[1]);
                data->accum -= 1.0f;
            } while (data->accum > 1.0f);
        }
    }
}

void func_1510550C(struct102 *arg0, s32 arg1, u8 arg2) {
    if (arg2 == 0x4B) {
        func_1516972C(arg0);
    }
}

void func_15105548(struct207 *arg0, s32 *arg1, u8 arg2) {
    struct206 *temp_v0 = &arg0->unk28;
    if ((arg2 == 0x38) && (temp_v0->unk0->unk14 == 1)) {
        temp_v0->unk70 = *arg1;
        temp_v0->unk4 = 300;
    }
}

typedef struct {
    f32 x;
    f32 y;
    f32 z;
} Func1510558CVec;

typedef struct {
    s16 unk0[9];
} Func1510558CBlob;

typedef struct {
    u8 pad0[0x30];
    Func1510558CVec pos;
    u8 pad3C[0x24];
    f32 dirX;
    f32 dirY;
    f32 dirZ;
    Func1510558CBlob blob;
    u8 pad7E[0xA];
    s32 flags;
} Func1510558CData;

typedef struct {
    s32 unk0;
    s32 unk4;
    Func1510558CVec pos;
    Func1510558CVec vel;
    Func1510558CBlob blob;
    f32 unk34;
    f32 unk38;
    f32 unk3C;
    f32 unk40;
    f32 unk44;
    s16 unk48;
    s16 unk4A;
    f32 unk4C;
    f32 unk50;
    f32 unk54;
} Func1510558CDesc;

extern s32 func_15102920(f32, u8, void *, void *, s32, s32, s32, s32, s32, s32);
extern void func_151C329C(void *, s32, s32);
extern void func_15151D6C(Func1510558CDesc *, const s32 *, const f32 *, s32, s32, s32);

void func_1510558C(struct131 *arg0) {
    Func1510558CData *data;
    s32 flags;

    data = (Func1510558CData *)((u8 *)arg0 + 0x110);
    flags = func_15102920(func_150ADA68() * 25.0f + 15.0f, func_150ADA20() % 56U + 200, &data->blob, &data->pos,
                  func_150ADA20() % 81U + 50, 1, 1, data->flags, ((u8 *)arg0)[0xC], ((u8 *)arg0)[1]);
    flags = data->flags;
    if ((flags & 0x1F) == 9) {
        if (func_150ADA68() < 0.4f) {
            func_151C329C(&data->pos, ((u8 *)arg0)[0xC], ((u8 *)arg0)[1]);
        }
    } else {
        if (func_150ADA68() < 0.1f) {
            func_151C329C(&data->pos, ((u8 *)arg0)[0xC], ((u8 *)arg0)[1]);
        }
        if (func_150ADA68() < 0.4f) {
            Func1510558CDesc desc;
            const s32 count[1] = { 0x85 };
            const f32 rate[1] = { 0.1f };

            desc.unk0 = 1;
            desc.unk4 = 3;
            desc.pos = data->pos;
            desc.vel.x = -data->dirX;
            desc.vel.y = -data->dirY;
            desc.vel.z = -data->dirZ;
            desc.blob = data->blob;
            desc.unk34 = 614.0f;
            desc.unk38 = 0.009000000544f;
            desc.unk3C = 0.01000000071f;
            desc.unk40 = -0.9040000439f;
            desc.unk44 = 0.395f;
            desc.unk48 = 15;
            desc.unk4A = 15;
            desc.unk4C = 0.06000000238f;
            desc.unk50 = 0.142f;
            desc.unk54 = 25.777f;
            func_15151D6C(&desc, count, rate, 1, ((u8 *)arg0)[0xC], ((u8 *)arg0)[1]);
        }
    }
}

void func_15105848(struct207 *arg0, s32 arg1, u8 arg2) {
    struct206 *temp_v0;

    if (arg2 == 0x38) {
        temp_v0 = &arg0->unk28;
        func_151058B4(arg0);
        temp_v0->unkC |= 1;
    } else {
        temp_v0 = &arg0->unk28;
        if (arg2 == 0x39) {
            temp_v0->unkC &= 0xFFFE;
        }
    }
}

typedef struct {
    s16 x;
    s16 y;
    s16 z;
} Func151058B4Target;

typedef struct {
    Func151058B4Target *target;
    f32 rate;
    s16 *unk8;
} Func151058B4Data;

typedef struct {
    f32 x;
    f32 y;
    f32 z;
    s16 unkC;
    s16 unkE;
    s32 unk10;
    s8 unk14;
    u8 unk15;
} Func151058B4Spawn;

typedef struct {
    f32 unk0;
    f32 vel[3];
    f32 unk10;
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
    u8 unk1E;
    u8 unk1F;
    u8 unk20;
    u8 unk21;
    s32 unk24;
    s32 unk28;
    s16 unk2C;
    s16 unk2E;
    s16 unk30;
    u8 unk32;
    f32 unk34;
    s8 unk38;
    u8 unk39;
} Func151058B4Particle;

extern void func_151432BC(Func151058B4Target *, f32 *, f32 *, f32 *, f32 *);
extern void func_15143794(s16, s16, f32, f32 *);
extern void func_1515C2F0(Func151058B4Spawn *, s32, Func151058B4Particle *, s32, s32, s32);

void func_151058B4(struct131 *arg0) {
    Func151058B4Data *data;
    f32 count;
    u32 angle;
    Func151058B4Spawn spawn;
    Func151058B4Particle part;
    f32 sp8C;
    f32 sp88;

    if (func_151464B8(((Func151058B4Data *)((u8 *)arg0 + 0x28))->unk8) == 0) {
        data = (Func151058B4Data *)((u8 *)arg0 + 0x28);
        count = (func_150ADA68() * 0.0013f + 0.001899999916f) * data->rate;
        if (count > 1.0f) {
            spawn.unkE = 0x15;
            spawn.unk10 = 0xA;
            spawn.unk14 = -1;
            part.unk14 = 4;
            part.unk15 = 2;
            part.unk16 = 3;
            part.unk17 = 0x61;
            part.unk18 = 0xF2;
            part.unk19 = 0xFF;
            part.unk1B = 0xFF;
            part.unk1C = 0xFF;
            part.unk1D = 0xFF;
            part.unk1E = 0xFF;
            part.unk1F = 0xFF;
            part.unk20 = 3;
            part.unk21 = 0x24;
            part.unk24 = 0x200005;
            part.unk28 = 0x60600;
            part.unk2C = 0x14;
            part.unk2E = 0xC;
            part.unk30 = 1;
            part.unk32 = 0;
            part.unk34 = 1.0f;
            part.unk38 = -1;
            part.unk39 = 0;
            spawn.y = data->target->y;
            do {
                part.unk1A = func_150ADA20() % 101U + 155;
                spawn.unk15 = (func_150ADA20() & 3) + 3;
                func_151432BC(data->target, &spawn.x, &spawn.z, &sp8C, &sp88);
                spawn.unkC = func_150ADA20() % 31U + 30;
                part.unk0 = func_150ADA68() * 10.13f + 7.399999619f;
                angle = func_150ADA20();
                func_15143794(angle & 0xFF, func_150ADA20() % 22U - 54, func_150ADA68() * 20.0f + 30.0f, part.vel);
                part.unk10 = func_150ADA68() * 1.486000061f + -3.048f;
                func_1515C2F0(&spawn, 0, &part, 0, ((u8 *)arg0)[0xC], ((u8 *)arg0)[1]);
                count -= 1.0f;
            } while (count > 1.0f);
        }
    }
}

void func_15105BC8(struct204 *arg0) {
    if ((arg0->unk34 & 1) != 0) {
        func_1508B20C(arg0->unk28->unk0, arg0->unk28->unk2, arg0->unk28->unk4, 500.0f);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_131F30/func_15105C24.s")
