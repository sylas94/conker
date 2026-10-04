u8 func_151F27E0(u16 addr) {
    u8 temp = 0;
    u8 temp2;
    int i;

    for (i = 0; i < 16; i++) {
        if (temp & 0x10) {
            temp2 = 0x15;
        } else {
            temp2 = 0;
        }
        temp <<= 1;
        temp |= (u8)((addr & 0x400) ? 1 : 0);
        addr <<= 1;
        temp ^= temp2;
    }
    return temp & 0x1f;
}
