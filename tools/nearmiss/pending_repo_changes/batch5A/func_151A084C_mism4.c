struct Obj151A084C {
    s32 unk0;
    u8 pad4[0x37];
    u8 unk3B;
    u8 pad3C[0x198];
    s32 unk1D4;
};

struct Par151A084C {
    u8 pad0[0x18];
    struct Obj151A084C *unk18;
    u8 unk1C;
    u8 pad1D[0x3B];
    struct Sub1519F3B8 unk58;
};

struct Ref151A084C {
    struct Par151A084C *unk0;
    u8 unk4;
};

struct Arg151A084C {
    u8 pad0[0xD];
    u8 unkD;
    s16 unkE;
    u8 pad10[0x18];
    struct Ref151A084C unk28;
};

void func_151A084C(struct Arg151A084C *arg0) {
    struct Sub1519F3B8 *q;
    struct Obj151A084C *obj;
    u8 done;
    struct Ref151A084C *s;

    s = &arg0->unk28;
    done = 0;
    obj = arg0->unk28.unk0->unk18;
    q = &arg0->unk28.unk0->unk58;
    if (obj->unk0 == 0) {
        done = 1;
    }
    if (obj->unk3B != s->unk0->unk1C) {
        done = 1;
    }
    if (!done) {
        if (obj->unk1D4 != 0) {
            s32 *ret;

            done = 1;
            ret = func_1519F1C8(s->unk0, s->unk4);
            if (s->unk4 == 6) {
                q->unk0 = ret;
            } else {
                q->unk8 = ret;
            }
        }
    }
    if (done) {
        func_151A0928(arg0);
        arg0->unkE = -1;
        arg0->unkD |= 1;
    }
}
