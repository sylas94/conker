struct Obj1511F4D0 {
    u8 pad0[0x10];
    s16 unk10;
    s16 unk12;
    u8 pad14[0x1C];
    f32 unk30;
    u8 pad34[0x8];
    s32 unk3C;
    u8 pad40[0x33];
    u8 unk73;
    u8 pad74[0x8];
    s32 unk7C;
    u8 pad80[0x4];
    s32 unk84;
    u8 pad88[0x2A];
    s16 unkB2;
    u8 padB4[0x9C];
    s16 unk150;
    u8 pad152[0x9E];
    s16 unk1F0;
};

void func_1511F4D0(struct Obj1511F4D0 *arg0) {
    s32 state;
    s32 amount;
    s32 open;
    s32 spread;
    s32 nextOpen;
    s32 nextSpread;
    s32 delta;
    s32 base[2];

    state = arg0->unk73 & 3;
    if ((arg0->unk73 & 4) == 4) {
        if (state == 2) {
            state = 0;
        } else if (state == 1) {
            state = 3;
        }
    }

    amount = (s32)((f32)arg0->unk3C * arg0->unk30);
    open = arg0->unk84 & 0xFFFF;
    spread = (arg0->unk84 >> 16) & 0xFFFF;

    if (arg0->unk7C == 0) {
        arg0->unk7C = (arg0->unk10 & 0xFFFF) | (arg0->unk12 << 16);
        if (state == 3) {
            open = 13;
            spread = 13;
        } else {
            spread = 0;
            open = 0;
        }
    }

    base[0] = (s16)arg0->unk7C;
    base[1] = (s16)((arg0->unk7C >> 16) & 0xFFFF);

    if (state == 2) {
        nextOpen = open + D_800BE9E4;
        if (nextOpen < 13) {
            open = nextOpen;
        } else {
            open = 13;
        }
        if (open >= 9) {
            nextSpread = spread + D_800BE9E4;
            if (nextSpread < 13) {
                spread = nextSpread;
            } else {
                spread = 13;
                state = 3;
            }
        }
    } else if (state == 1) {
        nextSpread = spread - D_800BE9E4;
        if (nextSpread > 0) {
            spread = nextSpread;
        } else {
            spread = 0;
        }
        if (spread < 4) {
            nextOpen = open - D_800BE9E4;
            if (nextOpen > 0) {
                open = nextOpen;
            } else {
                open = 0;
                state = 0;
            }
        }
    }

    arg0->unk12 = base[1] + ((open * amount) / 13);
    arg0->unkB2 = base[1] - (((amount + 1) * open) / 13);
    delta = (spread * amount) / 13;
    arg0->unk150 = base[0] - delta;
    arg0->unk1F0 = base[0] + delta;
    arg0->unk84 = (open & 0xFFFF) | ((spread & 0xFFFF) << 16);
    arg0->unk73 &= ~3;
    arg0->unk73 |= state;
}
