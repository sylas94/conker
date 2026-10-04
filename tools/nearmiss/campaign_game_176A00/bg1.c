struct Foo1514BE20 {
    char pad0[0x34];
    struct17 unk34;
    struct17 unk40;
    char pad4C[0x110];
    f32 unk15C;
};

extern s32 func_15145128(struct17 *, struct17 *, f32 *, f32 *);

void func_1514BE20(struct Foo1514BE20 *arg0) {
    struct17 target;
    struct17 cur;
    struct17 *p;
    struct17 dir;

    p = &dir;
    target.unk0 = arg0->unk34.unk0;
    target.unk4 = arg0->unk34.unk4 + 100.0f;
    target.unk8 = arg0->unk34.unk8;
    cur.unk0 = arg0->unk40.unk0 + (target.unk0 - arg0->unk40.unk0) * arg0->unk15C;
    cur.unk4 = arg0->unk40.unk4 + (target.unk4 - arg0->unk40.unk4) * arg0->unk15C;
    cur.unk8 = arg0->unk40.unk8 + (target.unk8 - arg0->unk40.unk8) * arg0->unk15C;
    {
        f32 sp34;
        f32 sp30;

        dir.unk0 = cur.unk0 - arg0->unk34.unk0;
        dir.unk4 = cur.unk4 - arg0->unk34.unk4;
        dir.unk8 = cur.unk8 - arg0->unk34.unk8;
        if (func_15145128(p, p, &sp34, &sp30)) {
            arg0->unk40.unk0 = arg0->unk34.unk0 + dir.unk0 * 100.0f;
            arg0->unk40.unk4 = arg0->unk34.unk4 + dir.unk4 * 100.0f;
            arg0->unk40.unk8 = arg0->unk34.unk8 + dir.unk8 * 100.0f;
        } else {
            arg0->unk40 = arg0->unk34;
        }
    }
}
