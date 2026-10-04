void func_15007558(void) {
    u16 sum;
    s32 i;
    s32 ret;

    for (i = 0; i < 0x1C; i++) {
        D_800BE358[i + 2] = D_800E0BE0[i];
    }
    sum = 0xCC;
    for (i = 2; i < 0x1E; i++) {
        sum += D_800BE358[i] << (i & 3);
    }
    *(u16 *)D_800BE358 = sum;
    if (D_8002AC5C == 0) {
        ret = func_151DCEF0(&D_800BE900, 0, D_800BE358, 0x20);
    }
}
