/* ObjRec with the words at 0x18 and 0x1C also visible as their bytes (the record is
   read both ways by func_150A24C0). */
typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ u8  pad8[0xC];
    /* 0x14 */ u8  unk14;
    /* 0x15 */ u8  unk15;
    /* 0x16 */ u8  pad16;
    /* 0x17 */ u8  unk17;
    /* 0x18 */ union {
        s32 word;
        struct {
            s16 hi;
            u8  b2;
            u8  b3;
        } f;
    } unk18;
    /* 0x1C */ union {
        u32 word;
        struct {
            u8 b0;
            u8 b1;
            u8 b2;
            u8 b3;
        } f;
    } unk1C;
    /* 0x20 */ u32 unk20;
} ObjRecU;

s32 func_15183290(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, u32);

void func_150A24C0(ObjRecU *arg0, s32 arg1) {
    s32 count;
    s32 ret;

    if (arg1 == 0xFF) {
        return;
    }
    count = arg0->unk1C.word & 0xFF;
    if (count == 0 || arg0->unk17 == 9) {
        ret = func_15183290(arg0->unk0, arg0->unk2 + (arg0->unk1C.f.b1 << 4), arg0->unk4, arg0->unk18.word & 0xFF,
                            arg0->unk17, arg0->unk6, arg1, arg0->unk18.f.hi, arg0->unk18.f.b2, arg0->unk1C.f.b0,
                            arg0->unk20);
        if (ret != -1 && arg0->unk17 != 9) {
            arg0->unk1C.word = (ret << 8) | 0xF0 | (arg0->unk1C.word & 0xFFFF0000);
        }
    } else {
        if (count < 2) {
            count = 2;
        }
        arg0->unk1C.word = (arg0->unk1C.word & ~0xFF) | count;
    }
}
