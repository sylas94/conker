typedef struct {
    u8 unk00;
    u8 unk01;
    u8 unk02;
    u8 unk03;
    u8 unk04;
    u8 pad05;
    s16 unk06;
    s32 unk08;
    s32 unk0C;
    s32 unk10;
    s32 unk14;
    s32 unk18;
    s32 unk1C;
    s32 unk20;
    s32 unk24;
    s32 unk28;
    u8 unk2C;
    u8 unk2D;
    u8 pad2E[2];
    u8 unk30;
    u8 unk31;
    u8 unk32;
    u8 unk33;
    u8 unk34;
    u8 unk35;
    u8 unk36;
    u8 unk37;
    u8 unk38;
    u8 pad39[3];
    s32 unk3C;
    u8 unk40;
    u8 unk41;
    u8 pad42[2];
    struct17 unk44;
    u8 pad50[4];
    s16 unk54;
    s16 unk56;
} Struct150FAE18Emitter; /* 0x58 */

typedef struct {
    f32 unk00;
    f32 unk04;
    f32 unk08;
    f32 unk0C;
    u8 unk10;
    u8 pad11;
    s16 unk12;
    s16 unk14;
    s16 unk16;
    s16 unk18;
    u8 unk1A;
    u8 unk1B;
    u8 unk1C;
    u8 unk1D;
    u8 unk1E;
    u8 unk1F;
    u8 unk20;
    u8 unk21;
    u8 unk22;
    u8 unk23;
    s32 unk24;
    s32 unk28;
    s32 unk2C;
    s32 unk30;
    s32 unk34;
    s32 unk38;
    s32 unk3C;
    u8 unk40;
    u8 unk41;
    u8 pad42[2];
    u8 unk44;
    u8 pad45[3];
    f32 unk48;
    f32 unk4C;
    f32 unk50;
    f32 unk54;
} Struct150FAE18Sprite; /* 0x58 */

typedef struct {
    Struct150FAE18Emitter params;
    s16 tag;
    u8 pad5A[2];
} Struct150FAE18EmitterBlock; /* 0x5C */

typedef union {
    s32 words[4];
    s16 sprite[8];
} Struct150FAE18SpriteIds;

extern f32 D_800A5480;
extern Struct150FAE18SpriteIds D_800A1D20;
extern void *func_15157010(Struct150FAE18Emitter *, s32, f32, s32, s32, s32, u8, s32);
extern void *func_1515548C(Struct150FAE18Sprite *, s32, s32, s32, s32, u8, s32);

void func_150FAE18(s16 arg0, u8 arg1, s32 arg2) {
    Struct150FAE18EmitterBlock block;
    void *obj;
    Struct150FAE18Sprite sprite;
    u8 i;
    Struct150FAE18SpriteIds ids;

    block.tag = arg0;
    block.params.unk38 = 0;
    block.params.unk00 = 0x61;
    block.params.unk01 = 3;
    block.params.unk02 = 4;
    block.params.unk03 = 2;
    block.params.unk04 = 0;
    block.params.unk06 = arg0;
    block.params.unk08 = 0xA5;
    block.params.unk0C = 0x17;
    block.params.unk10 = 0;
    block.params.unk14 = 0x200405;
    block.params.unk18 = 0x60200;
    block.params.unk2C = 0;
    block.params.unk2D = 8;
    block.params.unk1C = 1;
    block.params.unk20 = 0x38;
    block.params.unk24 = 0x80;
    block.params.unk28 = 0x20;
    block.params.unk30 = 0xFF;
    block.params.unk31 = 0xFF;
    block.params.unk32 = 0xFF;
    block.params.unk33 = 0xFF;
    block.params.unk34 = 0xFF;
    block.params.unk35 = 0xFF;
    block.params.unk36 = 0xFF;
    block.params.unk37 = 0xFF;
    block.params.unk3C = 0;
    block.params.unk40 = 0;
    block.params.unk41 = 1;
    block.params.unk44 = *(struct17 *)&D_800A5480;
    block.params.unk54 = 0xA;
    block.params.unk56 = 0x19;

    obj = func_15157010(&block.params, 0, 1.0f, 0, 0, 2, arg1, arg2);
    if (obj != NULL) {
        memcpy((u8 *)obj + 0x120, &block.tag, 2);
    }

    ids = D_800A1D20;
    sprite.unk12 = arg0;
    sprite.unk08 = 16.0f;
    sprite.unk0C = 16.0f;
    sprite.unk14 = 0x29;
    sprite.unk16 = 0xA;
    sprite.unk18 = 0x19;
    sprite.unk1A = 0;
    sprite.unk1B = 0xFF;
    sprite.unk1C = 0xFF;
    sprite.unk1D = 0xFF;
    sprite.unk1E = 0xFF;
    sprite.unk1F = 0xFF;
    sprite.unk20 = 0xFF;
    sprite.unk21 = 0xFF;
    sprite.unk22 = 0xFF;
    sprite.unk23 = 0xFF;
    sprite.unk24 = 0;
    sprite.unk28 = 0x200405;
    sprite.unk2C = 0x60200;
    sprite.unk40 = 0;
    sprite.unk41 = 7;
    sprite.unk30 = 0x19;
    sprite.unk34 = 0x22;
    sprite.unk38 = 0x80;
    sprite.unk3C = 0x20;
    sprite.unk44 = 0;
    sprite.unk48 = 1.f;
    sprite.unk4C = 1.f;
    sprite.unk50 = 0.0f;
    sprite.unk54 = 0.0f;
    sprite.unk04 = 62.0f;

    for (i = 0; i < 8; i++) {
        sprite.unk00 = i * 24.75f + -65.0f;
        sprite.unk10 = ids.sprite[i];
        obj = func_1515548C(&sprite, 0xE, 0, 0, 2, arg1, arg2);
        if (obj != NULL) {
            memcpy((u8 *)obj + 0x70, &block.tag, 2);
        }
    }
}
