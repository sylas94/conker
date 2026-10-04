typedef struct Tgt151918BC {
    s32 unk0;
    char pad4[0x37];
    u8 unk3B;
    char pad3C[0x198];
    s32 unk1D4;
} Tgt151918BC;

typedef struct Frm151918BC {
    Tgt151918BC *unk0;
    u8 unk4;
    u8 unk5;
    s16 unk6;
    u8 unk8;
} Frm151918BC;

typedef struct Obj151918BC {
    u8 pad0;
    u8 unk1;
    char pad2[0xA];
    u8 unkC;
    u8 unkD;
    s16 unkE;
    char pad10[0x18];
    Tgt151918BC *unk28;
    u8 unk2C;
} Obj151918BC;

void func_151918BC(Obj151918BC *arg0) {
    Tgt151918BC *t;
    Frm151918BC *f;
    u8 flag;

    flag = 0;
    t = arg0->unk28;
    if (t->unk0 == 0) {
        flag = 1;
    } else if (t->unk3B != arg0->unk2C) {
        flag = 1;
    }
    if (!flag) {
        if (t->unk1D4 != 0) {
            f = (Frm151918BC *)&arg0->unk28;
            flag = 1;
            if ((arg0->unkD & 1) != 0) {
                f->unk6 = arg0->unkE;
                f->unk8 = f->unk8 | 1;
            } else {
                f->unk6 = 0x12C;
            }
            func_15190770(f, 0, arg0->unkC, arg0->unk1);
        }
    }
    if (flag) {
        func_1516972C(arg0);
    }
}
