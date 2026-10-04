struct s15145CD0 {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    s16 padC;
    s16 padE;
    s16 unk10;
    s16 unk12;
    s16 unk14;
};

void func_15145CD0(struct s15145CD0 *arg0, struct17 **arg1, struct17 **arg2, s32 arg3) {
    f32 m[4][4];
    struct17 *s;
    struct17 *d;

    func_150A8050(m, arg0->unk0, arg0->unk4, arg0->unk8);
    m[3][0] = arg0->unk10;
    m[3][1] = arg0->unk12;
    m[3][2] = arg0->unk14;
    while (arg3 > 0) {
        s = *arg1;
        d = *arg2;
        func_150A7960(m[0], s->unk0, s->unk4, s->unk8, &d->unk0, &d->unk4, &d->unk8);
        arg3--;
        arg1++;
        arg2++;
    }
}
