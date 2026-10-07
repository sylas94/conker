extern u8 D_800C3C8C;
extern void func_1501E400(s32);

void func_1501E2F8(s32 arg0) {
    s32 i;

    i = arg0;
    for (;;) {
        if ((&D_800C35EA)[i] != 1) {
            return;
        }
        if (D_800C35B0[i] < D_800C3640[i]) {
            return;
        }
        if (D_800C3C8C != 0) {
            break;
        }
        func_1501E81C(0, i);
        if ((&D_800C35EA)[i] != 1) {
            return;
        }
        func_1501E400(0);
        i = 0;
        func_150242F8(1, 0);
        func_1501EC38(0);
        func_150242F8(0, 0);
        func_15020EC4(0);
    }
    D_800C3C8C = 2;
}
