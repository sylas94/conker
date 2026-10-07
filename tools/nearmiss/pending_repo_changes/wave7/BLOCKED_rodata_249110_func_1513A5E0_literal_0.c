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
extern s32 D_800A4268[];
extern f32 D_800A4270[];
extern f32 D_800A4960;
extern f32 D_800A4964;
extern f32 D_800A4968;
extern f32 D_800A496C;

void func_1513A5E0(struct17 *arg0, u8 arg1, s32 arg2) {
    Arg15152190 b;
    f32 sp28 = 0.0201f;

    b.unk00 = 7;
    b.unk04 = 7;
    b.unk08 = *arg0;
    b.unk14 = 0;
    b.unk16 = 0xFF;
    b.unk18 = -0x32;
    b.unk1A = 0x1B;
    b.unk1C = 4.0f;
    b.unk20 = 4.0f;
    b.unk24 = -0.43f;
    b.unk28 = 0.272f;
    b.unk2C = 0x19;
    b.unk2E = 0x28;
    b.unk30 = sp28;
    b.unk34 = sp28;
    b.unk38 = 20.187f;
    func_15152190(&b, D_800A4268, D_800A4270, 2, 0.0f, 1, arg1, arg2);
}
