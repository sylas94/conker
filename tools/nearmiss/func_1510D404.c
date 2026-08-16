extern u8 D_800DBDBA;
extern s32 D_800DBDBC;
extern s32 func_10004074(s16 *);
extern s32 func_10006240(void *, void *, u32);

void func_1510D404(void) {
    s32 max;
    s32 min;
    s32 i;
    s32 *entry;
    s32 data;
    s8 val;
    u8 delay;

    if (D_800D9F5C == -1) {
        return;
    }
    delay = D_800DBDBA;
    if ((delay == 0) && (D_800D9F60 != 0)) {
        return;
    }
    max = D_800D9F5C;
    if (delay != 0) {
        D_800DBDBA = delay - 1;
    }

    min = D_800D9F58;
    D_800D9F58 = 0xFFFF;
    D_800D9F5C = -1;
    if ((min < 0) || (max >= 0x1E53)) {
        D_8003C8E0 = 0xC000046;
        func_150AD770();
    }

    D_800DBDBC = -1;
    for (i = min; i <= max; i++) {
        val = (s8)D_800BC448[i];
        if (val != 0) {
            if (val < 4) {
                D_800BC448[i] = val - 1;
                if ((s8)D_800BC448[i] == 0) {
                    D_800DBDBC = i;
                    func_10004074((s16 *)D_800B0E58[i]);
                    D_800B0E58[i] = -1;
                } else {
                    if (i < D_800D9F58) {
                        D_800D9F58 = i;
                    }
                    if (D_800D9F5C < i) {
                        D_800D9F5C = i;
                    }
                }
            } else if (val & 0x40) {
                entry = (s32 *)D_800B0E58[i];
                data = entry[0];
                func_10006240((void *)(entry[1] + data), entry, D_8003809C);
                func_10004074((s16 *)data);
                D_800BC448[i] = (s8)D_800BC448[i] & ~0x40;
                if (i < D_800D9F58) {
                    D_800D9F58 = i;
                }
                if (D_800D9F5C < i) {
                    D_800D9F5C = i;
                }
            }
        }
    }
    D_800DBDBC = -2;
}
