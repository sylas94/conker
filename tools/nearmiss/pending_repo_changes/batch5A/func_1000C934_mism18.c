s32 func_1000C934(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 sp3C;
    s32 sp38;
    s32 temp_t7;

    sp3C = 0;
    temp_t7 = D_800DBFF0->unk5F0 & 1;
    if (temp_t7 != 0) {
        sp38 = 0x7FFF;
    } else {
        sp38 = 12000;
    }
    if ((D_800BE9F0 == 0x37) && (temp_t7 == 0)) {
        func_100114D0(2200, 1066, -1600, sp38, 3000, 1500, 0, &sp3C, 0);
        sp3C = sp38 - (sp3C & 0xFF00);
    }
    if ((sp3C != arg0) & 0xFFFF) {
        func_1000E40C(84, sp3C);
    }
    return sp3C | 0x80000000;
}
