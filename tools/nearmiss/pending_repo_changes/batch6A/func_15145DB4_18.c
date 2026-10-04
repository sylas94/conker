struct s15145DB4 {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    s16 padC;
    s16 padE;
    s16 unk10;
    s16 unk12;
    s16 unk14;
};

void func_15145DB4(struct s15145DB4 *arg0, struct17 *arg1, struct17 *arg2, s32 arg3) {
    f32 m[4][4];
    struct17 *src;
    struct17 *dst;
    f32 *p0;
    f32 *p1;
    f32 *p2;

    func_150A8050(m, arg0->unk0, arg0->unk4, arg0->unk8);
    m[3][0] = arg0->unk10;
    m[3][1] = arg0->unk12;
    m[3][2] = arg0->unk14;
    dst = arg2;
    p0 = &dst->unk0;
    p1 = &dst->unk4;
    p2 = &dst->unk8;
    if (arg3 > 0) {
        src = arg1;
        do {
            func_150A7960(m[0], src->unk0, src->unk4, src->unk8, p0, p1, p2);
            arg3--;
            src++;
            p0 += 3;
            p1 += 3;
            p2 += 3;
        } while (arg3 > 0);
    }
}
