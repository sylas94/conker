struct Obj15116058 {
    u8 pad0[0x16];
    u16 unk16;
    u8 pad18[0x8];
    Vtx *unk20[2];
    u8 pad28[0x14];
    s32 unk3C;
};

void func_15116058(struct Obj15116058 *arg0) {
    s32 i;
    s16 du;
    s16 dv;

    du = (s16)(arg0->unk3C >> 16);
    dv = (s16)(arg0->unk3C & 0xFFFF);

    for (i = 0; i < arg0->unk16; i++) {
        arg0->unk20[D_800BE9C0][i].v.tc[0] = arg0->unk20[!D_800BE9C0][i].v.tc[0] + du;
        arg0->unk20[D_800BE9C0][i].v.tc[1] = arg0->unk20[!D_800BE9C0][i].v.tc[1] + dv;
    }
}
