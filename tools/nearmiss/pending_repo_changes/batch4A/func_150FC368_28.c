void func_151C3B0C(s32, f32, f32, f32, f32, s32, s32, s32);

typedef struct {
    u8 pad0[0x84];
    u8 unk84;
} Sub31C_150FC368;

typedef struct {
    s32 unk0;
    u8 unk4;
    u8 pad5[0x36];
    u8 unk3B;
    u8 pad3C[0xEB];
    u8 unk127;
    u8 pad128[0x1F0];
    Sub318_150FC438 *unk318;
    Sub31C_150FC368 *unk31C;
} Obj_150FC368;

typedef struct {
    u8 pad0[0x1A0];
    Obj_150FC368 *unk1A0;
    u8 unk1A4;
} Arg0_150FC368;

void func_150FC368(Arg0_150FC368 *arg0) {
    Obj_150FC368 *obj = arg0->unk1A0;
    s32 mask;

    if (!(obj != NULL && obj->unk0 != 0 && obj->unk4 != 0xFF && obj->unk3B == arg0->unk1A4 &&
        obj->unk31C != NULL && obj->unk31C->unk84 == 0 && obj->unk127 != 0xFF && obj->unk318 != NULL)) {
        mask = 0xFF;
    } else {
        mask = ~(1 << obj->unk318->unk23D) & 0xFF;
    }
    func_151C3B0C((s32)arg0, 1.0f, 1.0f, 0.6f, 0.0f, 0xFF, 0xFF, mask);
}
