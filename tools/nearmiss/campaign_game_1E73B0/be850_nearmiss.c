typedef struct {
    /* 0x00 */ u8 unk00;
    /* 0x01 */ s8 unk01;
    /* 0x02 */ u8 unk02;
    /* 0x03 */ s8 unk03;
    /* 0x04 */ s8 unk04;
    /* 0x05 */ u8 pad05;
    /* 0x06 */ s16 unk06;
    /* 0x08 */ s32 unk08;
    /* 0x0C */ s32 unk0C;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ s32 unk24;
    /* 0x28 */ s32 unk28;
    /* 0x2C */ u8 unk2C;
    /* 0x2D */ u8 unk2D;
    /* 0x2E */ u8 pad2E[2];
    /* 0x30 */ u8 unk30;
    /* 0x31 */ u8 unk31;
    /* 0x32 */ u8 unk32;
    /* 0x33 */ u8 unk33;
    /* 0x34 */ u8 unk34;
    /* 0x35 */ u8 unk35;
    /* 0x36 */ u8 unk36;
    /* 0x37 */ u8 unk37;
    /* 0x38 */ u8 unk38;
    /* 0x39 */ u8 pad39[3];
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ u8 unk40;
    /* 0x41 */ u8 unk41;
    /* 0x42 */ u8 pad42[2];
    /* 0x44 */ struct17 unk44;
    /* 0x50 */ s32 unk50;
    /* 0x54 */ s16 unk54;
    /* 0x56 */ s16 unk56;
} S151BE850;

typedef struct {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ struct17 unk4;
    /* 0x10 */ u8 unk10;
    /* 0x11 */ u8 pad11[3];
} S151BE850Payload;

extern void func_1510F800(s32);
extern s32 func_1510FD20(s32, s32);
extern void func_151436B4(f32, f32, f32, f32 *);
extern void *func_15157010(void *, s32, f32, s32, s32, s32, u8, s32);
void *func_151BEEE0(f32 arg0, struct17 *arg1, s32 arg2, u8 arg3, u8 arg4, u8 arg5, s32 arg6, u8 arg7, s32 arg8);

void *func_151BE850(struct17 *arg0, f32 arg1, u8 arg2, u8 arg3, u8 arg4) {
    void *ret;
    s32 res;

    func_1510F800(0);
    res = func_1510FD20(arg0->unk0, arg0->unk8);
    if (arg4 >= 3) {
        return NULL;
    }
    if ((D_800D2E4C->unk19 & 4) || arg4 == 2) {
        S151BE850 sp68;
        S151BE850Payload sp54;
        const u8 tbl[3] = { 3, 1, 2 };

        sp54.unk0 = arg1;
        sp68.unk3C = 0;
        sp68.unk40 = 0;
        sp68.unk41 = 0;
        sp68.unk44 = *arg0;
        sp54.unk10 = arg2;
        {
        struct17 vec;

        func_151436B4(arg1 * 0.01745329238f, 0.0f, 39.0f, &vec.unk0);
        sp54.unk4.unk0 = vec.unk0 + arg0->unk0;
        sp54.unk4.unk4 = vec.unk4 + arg0->unk4 - 40.0f;
        sp54.unk4.unk8 = vec.unk8 + arg0->unk8;
        }
        sp68.unk38 = tbl[arg4];
        sp68.unk00 = (arg3 ? 0x10 : 0) | 0xE;
        sp68.unk01 = 1;
        if (D_800BE9F0 == 7) { sp68.unk02 = 6; } else { sp68.unk02 = 2; }
        sp68.unk03 = 0;
        sp68.unk04 = -1;
        sp68.unk0C = 8;
        sp68.unk06 = 0x12C;
        sp68.unk08 = 0xA2;
        sp68.unk10 = 0;
        sp68.unk14 = 0x620405;
        sp68.unk18 = 0x40200;
        sp68.unk2D = 8;
        sp68.unk1C = 0x14;
        sp68.unk20 = 0x37;
        sp68.unk2C = 0;
        sp68.unk24 = 0x80;
        sp68.unk28 = 0x20;
        sp68.unk30 = 0xFF;
        sp68.unk31 = 0xFF;
        sp68.unk32 = 0xFF;
        sp68.unk33 = 0xFF;
        sp68.unk34 = 0xFF;
        sp68.unk35 = 0xFF;
        sp68.unk36 = 0xFF;
        sp68.unk37 = 0xFF;
        sp68.unk50 = res;
        ret = func_15157010(&sp68, 0, 1.0f, 3, 0xFF, 0x18, 0xFF, 1);
        if (ret != NULL) {
            memcpy((u8 *)ret + 0x120, &sp54, 0x18);
        }
    } else {
        ret = func_151BEEE0(arg1, arg0, 3, 0xFF, arg4, arg3, res, 0xFF, 1);
    }
    return ret;
}
