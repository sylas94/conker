extern s32 D_80090324[];
extern s32 func_1510D0EC(s32, s32 *, s32, s32);

Gfx *func_150DFBD0(Gfx *gdl) {
    s32 i;
    s32 sp48[3];
    s32 data;

    for (i = 0; i < 3; i++) {
        data = func_1510D0EC(func_150DF8C0(i) ? D_80090324[D_800DD405 + 9] : D_80090324[8], sp48, 3, 0);
        gSPSegment(gdl++, i + 2, data);
    }
    return gdl;
}
