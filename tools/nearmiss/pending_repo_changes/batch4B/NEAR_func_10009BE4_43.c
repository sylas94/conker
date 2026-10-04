void func_10009BE4(struct54 *arg0) {
    struct54 *p;
    struct54 *q;

    if ((s32)arg0 & 1) {
        D_8003C8E0 = 0x0F000004;
        func_150AD770();
        return;
    }
    p = (struct54 *)arg0->unkC;
    p->unk0 = (struct54 *)arg0->unk8;
    if (arg0 == (struct54 *)D_800406A0.unk4) {
        D_800406A4 = arg0->unk0;
    }
    p = arg0->unk0;
    if (p != NULL) {
        p->unk4 = arg0->unk4;
    }
    p = arg0->unk4;
    if (p != NULL) {
        p->unk0 = arg0->unk0;
    }
    q = D_800406A0.unk10;
    if (q != NULL) {
        struct54 *r;

        arg0->unk4 = q;
        arg0->unk0 = q->unk0;
        r = q->unk0;
        if (r != NULL) {
            r->unk4 = arg0;
        }
        q->unk0 = arg0;
    } else {
        D_800406B0 = arg0;
        arg0->unk0 = NULL;
        arg0->unk4 = NULL;
    }
}
