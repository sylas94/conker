s32 func_1505DADC(struct127 *, u16 *, s32, s32, s32);

u16 func_150641D8(struct127 *arg0, u16 arg1, u16 arg2, u16 arg3) {
    u16 ret;
    s32 cur;
    u16 sp26;

    sp26 = 0;
    ret = arg1;
    if (func_150ADA20() & 1) {
        ret = arg2;
    }
    cur = arg0->unk84.uh;
    if ((arg1 == cur) || (arg2 == cur)) {
        ret = arg3;
        if (arg0->unk107 < 0x28) {
            return 999;
        }
    }
    if (arg3 == cur) {
        ret = 999;
    }
    if (func_1505DADC(arg0, &sp26, 0, 0xFE, 0x40) != 0xFF) {
        arg0->unk76 = sp26;
    }
    arg0->unk83 = 0xFF;
    return ret;
}
