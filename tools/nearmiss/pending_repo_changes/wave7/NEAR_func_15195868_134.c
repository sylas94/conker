typedef struct {
    s8 type;
    u8 pad1[3];
    s32 val;
} Rec15195868;

s32 func_15195868(s32 arg0, s32 arg1, s32 arg2, s32 *arg3) {
    Rec15195868 *rec = (Rec15195868 *)arg0;
    s32 i;
    s32 j;
    s8 type;

    i = -1;
    *arg3 = 0;
    for (;;) {
        do {
            i++;
            type = rec[i].type;
        } while (type != -3 && type != -0x21);
        if (type == -0x21) {
            return -1;
        }
        if (rec[i].val == D_800B0E58[arg1] || arg1 == 0) {
            if (arg2-- <= 0) {
                break;
            }
        }
    }
    while (type != -0xE) {
        type = rec[++i].type;
    }
    j = i;
    do {
        (*arg3)++;
    } while (rec[++j].type == -0xB && rec[++j].type == -0xE);
    return i;
}
