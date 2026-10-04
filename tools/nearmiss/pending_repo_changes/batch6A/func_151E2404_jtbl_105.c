extern s8 D_800E0BE0[0x1C];
extern u8 *D_80082BBC;

void func_151E2404(void) {
    s8 *src = D_800E0BE0;
    s8 idx = D_800AB690[D_8008FDD4->pad42 * 10];
    s8 *dst = (s8 *)(D_80082BBC + idx * 10);

    dst[0] = 0;
    dst[1] = src[2];
    dst[2] = src[3];
    dst[3] = src[0x10];
    dst[4] = src[0x11];
    switch (idx) {
        case 0:
            dst[5] = src[4];
            break;
        case 1:
        case 2:
            dst[5] = src[0xD];
            dst[6] = src[0xE];
            break;
        case 5:
        case 7:
            dst[5] = src[0x12];
            break;
        case 8:
        case 9:
            dst[5] = src[7];
            dst[6] = src[0x13];
            break;
    }
    dst[8] = src[0x16];
    dst[9] = src[6];
    func_150076A0();
}
