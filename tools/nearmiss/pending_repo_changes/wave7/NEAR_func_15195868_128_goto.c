typedef struct {
    s8 type;
    u8 pad1[3];
    s32 val;
} Rec15195868;

s32 func_15195868(s32 arg0, s32 arg1, s32 arg2, s32 *arg3) {
    s32 i;
    s32 j;
    s8 type;

    i = -1;
    *arg3 = 0;
next:
    i++;
search:
    type = ((Rec15195868 *)arg0)[i].type;
    if (type != -3 && type != -0x21) {
        i++;
        goto search;
    }
    if (type == -0x21) {
        return -1;
    }
    if (((Rec15195868 *)arg0)[i].val != D_800B0E58[arg1] && arg1 != 0) {
        i++;
        goto search;
    }
    if (arg2-- > 0) {
        goto next;
    }
    while (type != -0xE) {
        type = ((Rec15195868 *)arg0)[++i].type;
    }
    j = i;
    do {
        (*arg3)++;
    } while (((Rec15195868 *)arg0)[++j].type == -0xB && ((Rec15195868 *)arg0)[++j].type == -0xE);
    return i;
}
