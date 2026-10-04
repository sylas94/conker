void func_15007360(void) {
    u16 sum;
    s32 i;
    s32 ret;

    sum = 0xCC;
    for (i = 2; i < 0x68; i++) {
        sum += D_800BE2F0[i] << (i & 3);
    }
    *(u16 *)D_800BE2F0 = sum;
    if (D_8002AC5C == 0) {
        ret = func_151DCEF0(&D_800BE900, 0x44, &D_800BE2F0, 0x70);
    }
}
