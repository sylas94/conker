void func_10003ACC(s32 r, s32 g, s32 b) {
    s32 i;
    u16 *p;
    s32 size;
    s32 n;

    size = D_800BE620 * D_800BE624 * 2;
    p = (u16 *)D_8002AAE8[0];
    i = 0;
    n = size >> 1;
    if (p != 0) {
        for (; i < n; i++, p++) {
            *p = ((r << 8) & 0xF800) | ((g << 3) & 0x7C0) | ((b >> 2) & 0x3E) | 1;
        }
        p = (u16 *)D_8002AAE8[1];
        for (i = 0; i < n; i++) {
            p[i] = ((r << 8) & 0xF800) | ((g << 3) & 0x7C0) | ((b >> 2) & 0x3E) | 1;
        }
    }
}
