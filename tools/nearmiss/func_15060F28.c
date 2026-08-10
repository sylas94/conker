extern s32  func_1514D310(struct127 *arg0);
extern void func_151695F0(struct127 *arg0, u8 arg1);
extern void func_15084558(struct127 *arg0);
extern void func_1504AF10(struct127 *arg0, s32 arg1, s32 arg2);
extern void func_1503E260(s32 arg0);
extern void func_150626EC(struct127 *arg0, s32 arg1);
extern void func_15060D54(struct127 *arg0);
extern s32  func_150303E4(struct127 *arg0);
extern void func_15188AD0(s32 arg0);
extern void func_10004074(void *arg0);
extern u8  *D_800D210C;

void func_15060F28(struct127 *arg0, s32 arg1) {
    struct129 *anim;
    s32 i;

    func_1514D310(arg0);
    func_151695F0(arg0, 0);
    if ((arg0->unk5 != 2) && (arg0->unk5 != 3)) {
        func_15084558(arg0);
        func_150626EC(arg0, arg1);
    }
    if (arg1 == 1) {
        func_1504AF10(arg0, 1, 0);
        func_1503E260(arg0 - D_800CC2D0);
    }
    if (arg0->unk13F != 0xFF) {
        if (arg1 != 2) {
            anim = arg0->unk144;
            if (anim != NULL) {
                if (anim->unk0 & 0x20) {
                    anim->unk2 = 1;
                    D_800D210C[arg0->unk13F] = 0;
                } else if (anim->unk0 & 1) {
                    D_800D210C[arg0->unk13F] = 0;
                } else {
                    anim->unk2 = 1;
                    D_800D210C[arg0->unk13F] &= 0x80;
                }
            } else {
                D_800D210C[arg0->unk13F] &= 0x80;
            }
        } else {
            D_800D210C[arg0->unk13F] = 0;
        }
    }
    if (*(void **)((u8 *)arg0 + 0x260) != NULL) {
        func_10004074(*(void **)((u8 *)arg0 + 0x260));
    }
    if (*(void **)((u8 *)arg0 + 0x264) != NULL) {
        func_10004074(*(void **)((u8 *)arg0 + 0x264));
    }
    if (*(void **)((u8 *)arg0 + 0x268) != NULL) {
        func_10004074(*(void **)((u8 *)arg0 + 0x268));
    }
    if (*(void **)((u8 *)arg0 + 0x26C) != NULL) {
        func_10004074(*(void **)((u8 *)arg0 + 0x26C));
    }
    if (*(void **)((u8 *)arg0 + 0x1D8) != NULL) {
        func_10004074(*(void **)((u8 *)arg0 + 0x1D8));
    }
    if (*(struct102 **)((u8 *)arg0 + 0x2D4) != NULL) {
        func_1516972C(*(struct102 **)((u8 *)arg0 + 0x2D4));
    }
    if (*(s32 **)((u8 *)arg0 + 0x304) != NULL) {
        for (i = 0; i <= D_80082FA0; i = (u8)(i + 1)) {
            func_100043B4(*(s32 **)((u8 *)arg0 + (i * 4) + 0x304), 4);
        }
    }
    if (*(s32 **)((u8 *)arg0 + 0x314) != NULL) {
        func_100043B4(*(s32 **)((u8 *)arg0 + 0x314), 4);
    }
    if (arg0->unk2D0 != NULL) {
        func_10004074(arg0->unk2D0);
    }
    if (*(void **)((u8 *)arg0 + 0x324) != NULL) {
        func_10004074(*(void **)((u8 *)arg0 + 0x324));
    }
    if ((arg0->unk31C != NULL) && (*(void **)((u8 *)arg0->unk31C + 0x11C) != NULL)) {
        func_10004074(*(void **)((u8 *)arg0->unk31C + 0x11C));
    }
    func_10010AA8(arg0);
    func_150303E4(arg0);
    func_15060D54(arg0);
    func_15188AD0((s32)arg0);
    if (arg0->unk31C != NULL) {
        func_10004074(arg0->unk31C);
    }
    func_1505F188(arg0);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_83300/func_150611E8.s")

// TODO: is this really struct127?
void func_150615DC(struct127 *arg0) {
    arg0->unk7 = 0xFF;
