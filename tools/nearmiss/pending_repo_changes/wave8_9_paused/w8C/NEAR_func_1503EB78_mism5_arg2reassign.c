extern f32 D_80098920;
extern f32 D_80098924;

struct func_1503EB78_part {
    u8 pad0[0x48];
    f32 vel[3];
    f32 rot[3];
    f32 unk60;
};

void func_1503EB78(void *arg0, f32 arg1, f32 arg2, s32 arg3) {
    s32 i;
    f32 scale[3];
    s16 mask;
    s16 base;

    if (arg3 != 0) {
        mask = 0x80;
        base = 0x7F;
    } else {
        mask = 0xFF;
        base = 0;
    }
    scale[2] = scale[0] = arg1 * D_80098920;
    arg2 *= D_80098920;
    scale[1] = arg2;
    for (i = 0; i < 3; i++) {
        ((struct func_1503EB78_part *)arg0)->vel[i] *= ((func_150ADA20() & mask) + base) * scale[i] + 2.0f;
    }
    for (i = 0; i < 3; i++) {
        ((struct func_1503EB78_part *)arg0)->rot[i] = ((s32)(func_150ADA20() & 0xFF) - 0x80) * 0.03125f;
    }
    ((struct func_1503EB78_part *)arg0)->unk60 = D_80098924;
}
