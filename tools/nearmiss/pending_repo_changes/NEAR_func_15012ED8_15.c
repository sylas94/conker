extern u8 D_800BE530[];
extern s16 D_800BE550[];
extern u8 D_800BE564;

void func_15012ED8(Gfx *arg0) {
    s32 i;
    s32 cmd;

    i = 0;
    cmd = (s8)(arg0[i].words.w0 >> 24);
    while (cmd != -0x21) {
        if (cmd == -5) {
            D_800BE550[D_800BE564] = i;
            D_800BE530[D_800BE564 * 3 + 0] = arg0[i].words.w1 >> 24;
            D_800BE530[D_800BE564 * 3 + 1] = arg0[i].words.w1 >> 16;
            D_800BE530[D_800BE564 * 3 + 2] = arg0[i].words.w1 >> 8;
            D_800BE564++;
        }
        i++;
        cmd = (s8)(arg0[i].words.w0 >> 24);
    }
}
