u8 func_151F2890(u8 *data) {
    u8 temp = 0;
    u8 temp2;
    int i;
    int j;

    for (i = 0; i <= 32; i++, data++) {
        for (j = 7; j >= 0; j--) {
            if (temp & 0x80) {
                temp2 = 0x85;
            } else {
                temp2 = 0;
            }
            temp <<= 1;
            if (i == 32) {
                temp &= -1;
            } else {
                temp |= ((*data & (1 << j)) ? 1 : 0);
            }
            temp ^= temp2;
        }
    }
    return temp;
}
