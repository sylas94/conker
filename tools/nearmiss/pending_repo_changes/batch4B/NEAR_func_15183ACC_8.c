extern void func_1510CE60(s32, s32, s32, s32, s32 *);

void func_15183ACC(s32 arg0) {
    Struct15183974 *e;
    Inner1502B6BC *ret;

    e = &((Struct15183974 *)D_800DDE80)[arg0];
    if (e->unk0 == 0) {
        ret = func_1502B6BC(0, 0, 0, 2, 9, arg0 + 0xAD);
        if (ret != 0) {
            e->unk0 = (s32)ret;
            e->unk4 = ret->unk0;
            e->unk8 = ret->unk8;
            e->unkC = ((s32 *)ret)[6];
            D_800DDF78[arg0] = ((s32 *)ret)[4];
            func_1510CE60(D_800DDF78[arg0], 0, 1, 0x3E, &e->unk10);
            D_800DDF68[arg0] = 1;
        }
    }
}
