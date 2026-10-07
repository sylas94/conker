typedef struct {
    s32 unk0;
    s32 unk4;
} Entry62D10;

extern Entry62D10 **D_800C4488[];

void func_15062D10(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    Entry62D10 *base;
    Entry62D10 *entry;
    s32 packed;
    s32 modX;
    s32 modY;
    s32 newX;
    s32 newY;
    s32 tmp;

    if ((&D_800D19A0)[arg0] == 0) {
        return;
    }
    base = D_800C4488[arg0][arg4];
    entry = &base[arg1];
    packed = entry->unk4;
    modX = ((packed >> 12) & 0xFFF) + 2;
    modY = (packed & 0xFFF) + 2;
    packed = entry->unk0;
    if (arg5 != 0) {
        newX = arg2 & 0xFFF;
    } else {
        tmp = ((packed >> 12) & 0xFFF) + arg2;
        newX = tmp;
        if (modX < tmp) {
            newX = tmp - modX;
        } else if (tmp < 0) {
            newX = tmp + modX;
        }
    }
    if (arg5 != 0) {
        newY = arg3 & 0xFFF;
    } else {
        tmp = (packed & 0xFFF) + arg3;
        newY = tmp;
        if (modY < tmp) {
            newY = tmp - modY;
        } else if (tmp < 0) {
            newY = tmp + modY;
        }
    }
    packed = (packed & 0xFF000000) | (newY & 0xFFF) | ((newX & 0xFFF) << 12);
    entry->unk0 = packed;
}
