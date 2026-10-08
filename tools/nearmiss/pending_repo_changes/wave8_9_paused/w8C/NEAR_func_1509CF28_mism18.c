typedef struct {
    u32 unk0;
    u32 unk4;
} Reloc1509CF28;

typedef struct {
    Reloc1509CF28 *unk0;
    s32 unk4;
} Seg1509CF28;

extern s32 D_800D2FB0;
extern Seg1509CF28 *func_1502B6BC(s32, s32, u32 *, s32, s32, s32, s32);

s32 func_1509CF28(s32 arg0, s32 *arg1) {
    Seg1509CF28 *seg;
    Reloc1509CF28 *q;
    u32 i;
    u32 count;
    Reloc1509CF28 *p;
    u32 flags;
    s32 done;

    count = 0;
    D_800D2FB0 = (s32)func_1502B6BC(0, 0, &count, 3, 8, 0, arg0);
    seg = (Seg1509CF28 *)D_800D2FB0;
    if (seg == NULL) {
        *arg1 = 0;
        return 0;
    }
    seg[0].unk4 = count - 1;
    *arg1 = count - 1;
    for (i = 1; i < count; i++) {
        done = 0;
        p = ((Seg1509CF28 *)D_800D2FB0)[i].unk0;
        do {
            p->unk0 += (u32)((Seg1509CF28 *)D_800D2FB0)[i].unk0;
            flags = p->unk4;
            if (flags & 0x80000000) {
                done = 1;
            }
            p->unk4 = flags & 0x0FFFFFFF;
            p++;
        } while (!done);
        q = seg[i].unk0;
        q[1].unk4 = (q[1].unk4 & 0x0FFFFFFF) >> 1;
    }
    return 1;
}
