void func_1500727C(void) {
    u16 sum;
    s32 i;

    func_151DD3A0(&D_800BE900, 0x44, &D_800BE2F0, 0x70);
    sum = 0xCC;
    for (i = 2; i < 0x68; i++) {
        sum += D_800BE2F0[i] << (i & 3);
    }
    if (sum != *(u16 *)D_800BE2F0) {
        func_15007168();
    }
}
