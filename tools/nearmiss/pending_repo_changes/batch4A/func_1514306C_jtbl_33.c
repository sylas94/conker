extern s32 D_800915B0;
extern s32 D_80091514;
extern s32 D_80091564[];
typedef struct {
    s32 *unk0;
    u8 pad4[8];
} Tbl1514306C;
extern Tbl1514306C D_80090B60[];

s32 func_1514306C(s32 arg0, s32 arg1, s32 arg2, u8 arg3) {
    s32 ret;
    s32 x;

    switch (arg3) {
    case 1:
        ret = D_800915B0;
        break;
    case 2:
        ret = D_80091514;
        break;
    case 3:
        ret = 0;
        break;
    case 4:
        ret = D_80091564[arg1];
        break;
    case 5:
        ret = arg1;
        break;
    case 6:
        x = *(s32 *)arg0;
        if ((u32)x >= 0x10000000) {
            ret = ((s32 *)x)[arg2];
        } else {
            ret = x;
        }
        break;
    default:
        ret = D_80090B60[arg1].unk0[arg2];
        break;
    }
    return ret;
}
