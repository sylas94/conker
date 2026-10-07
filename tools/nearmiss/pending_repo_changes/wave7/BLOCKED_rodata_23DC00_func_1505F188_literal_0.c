void func_1505F188(struct127 *arg0) {
    s32 *p;
    f32 v;

    for (p = (s32 *)arg0; p < (s32 *)((u8 *)arg0 + 0x32C); p++) {
        *p = 0;
    }
    v = -10000.0f;
    ((u8 *)arg0)[0x2FD] = 2;
    *(s16 *)&arg0->unk38 = -0x2710;
    arg0->xz_scale = 1.0f;
    arg0->y_scale = 1.0f;
    arg0->unk118 = v;
    arg0->unk180 = v;
    arg0->gravity = 3.3f;
    ((u8 *)arg0)[0x1DC] = 0xFF;
    arg0->unk127 = 0xFF;
    arg0->unk84.uh = 0xFFFF;
    arg0->unk13F = 0xFF;
    *(u8 **)((u8 *)arg0 + 0x2C4) = &arg0->id;
    ((u8 *)arg0)[0x2C8] = 1;
    arg0->unk2C9 = 1;
    arg0->id = 0xFF;
    arg0->unk2CB = 0x32;
    arg0->unk48 = 1.0f;
    arg0->unk6E = ((u32)func_150ADA20() % 0x32) + 0x32;
    func_150615DC(arg0);
    ((u8 *)arg0)[0x1DD] = 0xFF;
    ((u8 *)arg0)[0x1DE] = 0xFF;
    ((u8 *)arg0)[0x1DF] = 0xFF;
    *(s16 *)((u8 *)arg0 + 0x18C) = 0;
    *(s16 *)((u8 *)arg0 + 0x18E) = 0;
    *(s16 *)((u8 *)arg0 + 0x190) = 0;
    *(s16 *)((u8 *)arg0 + 0x192) = 0;
    *(s16 *)((u8 *)arg0 + 0x194) = 0;
    *(s16 *)((u8 *)arg0 + 0x196) = 0xA;
    *(s16 *)((u8 *)arg0 + 0x198) = 0xA;
    *(s16 *)((u8 *)arg0 + 0x19A) = 0;
    *(s16 *)((u8 *)arg0 + 0x19C) = 0;
}
