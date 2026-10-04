void func_1500707C(s32 arg0) {
    s32 i;
    u8 *buf = D_800BE358;
    s8 *p;
    s32 ret;

    for (i = 0; i < 8; i++) {
        buf[i] = 0xFF;
    }
    osWritebackDCacheAll();
    p = &D_800BE3D8;
    if (D_8002AC5C == 0) {
        for (i = 0; i < 4; i++) {
            if (arg0 == *p) {
                s32 idx = (i << 4) + 4;
                s32 idx2 = idx + 1;
                ret = func_151DD4E0(&D_800BE900, idx, buf);
                func_151DD4E0(&D_800BE900, idx2, buf);
            }
            p++;
        }
    }
}
