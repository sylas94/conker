extern void func_1505D024(struct127 *, s32, s32, s32);
extern f32 D_8009A0D8;

void func_15073A50(void) {
    struct127 *obj;
    struct127 *e;
    s32 idx;
    s32 val;

    obj = D_800D154C;
    idx = obj->unk124;
    e = &D_800CC2D0[idx];
    if (e->unk65 != 0) {
        val = D_800D1580;
        obj->unk13C = 0;
        e->immune = 0;
        func_1505D024(e, D_800D1580 & 0xFF00FF, 0, D_800C3E78);
        e->unk1CC = D_8009A0D8;
        if ((val << 1) < 0) {
            e->unk1CC = D_800D154C->y_position;
        }
        e->immune = 0x14;
        e->unk76 = D_800D154C->unk7A + val;
    }
}
