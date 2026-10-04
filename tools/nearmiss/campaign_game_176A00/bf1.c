typedef struct {
    char pad0[0x38];
    struct17 unk38;
    f32 unk44;
    f32 unk48;
} Struct1514BF9CSub;

typedef struct {
    char pad0[0x34];
    struct17 unk34;
    char pad40[0xD0];
    Struct1514BF9CSub unk110;
} Struct1514BF9CObj;

void func_1514BF9C(Struct1514BF9CObj *arg0) {
    Struct1514BF9CSub *sub;
    struct17 old;
    s32 i;
    f32 ax;
    f32 ay;
    f32 az;

    old = arg0->unk110.unk38;
    for (i = D_800BE9E4; i != 0; i--) {
        sub = &arg0->unk110;
        sub->unk38.unk0 *= sub->unk48;
        sub->unk38.unk4 *= sub->unk48;
        sub->unk38.unk8 *= sub->unk48;
    }
    sub = &arg0->unk110;
    sub->unk38.unk4 += sub->unk44 * D_800BE9A4;
    ax = (sub->unk38.unk0 - old.unk0) * D_800BE9A8;
    ay = (sub->unk38.unk4 - old.unk4) * D_800BE9A8;
    az = (sub->unk38.unk8 - old.unk8) * D_800BE9A8;
    arg0->unk34.unk0 += (old.unk0 + 0.5f * ax * D_800BE9A4) * D_800BE9A4;
    arg0->unk34.unk4 += (old.unk4 + 0.5f * ay * D_800BE9A4) * D_800BE9A4;
    arg0->unk34.unk8 += (old.unk8 + 0.5f * az * D_800BE9A4) * D_800BE9A4;
}
