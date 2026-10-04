typedef struct {
    u8 unk0;
    u8 unk1;
    u8 pad2[0x3E];
    s32 unk40;
} Arg151407D0;

typedef struct {
    u8 pad0[0x44];
    s32 unk44;
    u8 pad48[0x11];
    s8 unk59;
} Sub151407D0;

extern s32 func_1513D524(s32, u8, u8, u8, u8, u8, s32, u8, s32);

s32 func_151407D0(s32 arg0, s32 arg1, Arg151407D0 *arg2, u8 arg3, u8 arg4, u8 arg5, u8 arg6, s8 arg7, u8 arg8, s32 arg9) {
    s32 ret;
    Sub151407D0 *sub;

    arg2->unk1 = 3;
    arg2->unk40 |= 0x40400000;
    ret = func_1513D524((s32)arg2, arg3, arg4, arg5, 1, arg6, arg1, arg8, arg9);
    if (ret != 0) {
        sub = (Sub151407D0 *)(ret + 0x110);
        memcpy(sub, arg0, arg1);
        sub->unk59 = arg7;
        sub->unk44 = 0;
    } else {
        extern s32 D_800DC9F0;

        return 0;
    }
    if (ret != 0) {
        D_800DC9F0++;
    }
    return ret;
}
