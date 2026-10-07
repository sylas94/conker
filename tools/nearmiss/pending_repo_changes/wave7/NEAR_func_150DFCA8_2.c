typedef struct {
    u8 pad_0x0[0x4];
    f32 field_0x4;
    u8 pad_0x8[0x5C];
    f32 field_0x64;
    u8 pad_0x68[0x14];
    f32 field_0x7C;
} Game10CD70Bob;

extern f32 D_800A0FA0;
extern f32 D_800A0FA4;
extern f32 D_800A0FA8;
extern f32 D_800A0FAC;

void func_150DFCA8(Game10CD70Bob *arg0) {
    f32 step;
    f32 target;

    step = arg0->field_0x64 * D_800BE9E4;
    arg0->field_0x4 += step;
    if (arg0->field_0x4 < 11.0f) {
        target = D_800A0FA0;
        arg0->field_0x7C = target;
    } else if (arg0->field_0x4 > 55.0f) {
        target = -D_800A0FA4;
        arg0->field_0x7C = target;
    } else {
        target = arg0->field_0x7C;
    }
    if (arg0->field_0x64 < target) {
        arg0->field_0x64 += D_800A0FA8;
        if (arg0->field_0x64 > target) {
            arg0->field_0x64 = target;
        }
    } else if (arg0->field_0x64 > target) {
        arg0->field_0x64 -= D_800A0FAC;
        if (arg0->field_0x64 < target) {
            arg0->field_0x64 = target;
        }
    }
}
