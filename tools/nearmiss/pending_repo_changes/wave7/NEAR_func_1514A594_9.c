struct Foo1514A594 {
    char pad0[0x34];
    Struct1514A4ECVec unk34;
    Struct1514A4ECVec unk40;
    char pad4C[0x8];
    f32 unk54;
    char pad58[0xD8];
    f32 unk130;
    f32 unk134;
    f32 unk138;
    f32 unk13C;
    f32 unk140;
};

s32 func_1514A594(struct Foo1514A594 *arg0) {
    f32 dx;
    f32 dy;
    f32 dz;

    arg0->unk130 = arg0->unk130 * arg0->unk140;
    arg0->unk134 = arg0->unk134 + (arg0->unk13C * D_800BE9A4);
    arg0->unk138 = arg0->unk138 * arg0->unk140;
    dx = arg0->unk130 * D_800BE9A4;
    dy = arg0->unk134 * D_800BE9A4;
    dz = arg0->unk138 * D_800BE9A4;
    arg0->unk34.unk0 += dx;
    arg0->unk34.unk4 += dy;
    arg0->unk34.unk8 += dz;
    arg0->unk40.unk0 += dx;
    arg0->unk40.unk4 += dy;
    arg0->unk40.unk8 += dz;
    arg0->unk40.unk0 = arg0->unk34.unk0 + (arg0->unk40.unk0 - arg0->unk34.unk0) * arg0->unk54;
    arg0->unk40.unk4 = arg0->unk34.unk4 + (arg0->unk40.unk4 - arg0->unk34.unk4) * arg0->unk54;
    arg0->unk40.unk8 = arg0->unk34.unk8 + (arg0->unk40.unk8 - arg0->unk34.unk8) * arg0->unk54;
    return 1;
}
