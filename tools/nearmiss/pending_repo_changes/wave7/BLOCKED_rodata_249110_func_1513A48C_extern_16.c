typedef struct {
    s32 unk00;
    s32 unk04;
    struct17 unk08;
    s16 unk14;
    s16 unk16;
    s16 unk18;
    s16 unk1A;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
    s16 unk2C;
    s16 unk2E;
    f32 unk30;
    f32 unk34;
    f32 unk38;
} Arg15152190;

extern void func_15152190(Arg15152190 *, s32 *, f32 *, s32, f32, s32, u8, s32);
extern s32 D_800A4260[];
extern f32 D_800A4264[];
extern f32 D_800A4950;
extern f32 D_800A4954;
extern f32 D_800A4958;
extern f32 D_800A495C;

void func_1513A48C(struct17 *arg0, u8 arg1, s32 arg2) {
    Arg15152190 b;
    f32 sp28 = D_800A4950;

    b.unk00 = 8;
    b.unk04 = 4;
    b.unk08 = *arg0;
    b.unk14 = 0;
    b.unk16 = 0xFF;
    b.unk18 = -0x37;
    b.unk1A = 0x20;
    b.unk1C = 10.0f;
    b.unk20 = 9.0f;
    b.unk24 = D_800A4954;
    b.unk28 = D_800A4958;
    b.unk2C = 0x28;
    b.unk2E = 0x14;
    b.unk30 = sp28;
    b.unk34 = sp28;
    b.unk38 = D_800A495C;
    func_15152190(&b, D_800A4260, D_800A4264, 1, 0.0f, 1, arg1, arg2);
}
