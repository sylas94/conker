extern u8 D_16003CE0[];

int func_160014F0(arg0, c)
    s32 arg0;
    u8 c;
{
    u16 *p = (u16 *)arg0;
    s32 color = D_1600388C;
    s32 ch;
    u8 *glyph;
    s32 row;
    s32 col;
    u16 bits;
    u16 pixel;

    ch = c;
    if (c < 0x20) {
        ch = 0x20;
    }
    glyph = &D_16003CE0[(ch - 0x20) << 3];
    for (row = 0; row < 8; row++) {
        col = 0;
        bits = *glyph;
        for (; col < 8; col++) {
            if (bits & 0x80) {
                pixel = color;
            } else {
                pixel = 1;
            }
            *p++ = pixel;
            bits <<= 1;
        }
        glyph++;
        p += D_160038A8 - 8;
    }
    return arg0 + 0x10;
}
