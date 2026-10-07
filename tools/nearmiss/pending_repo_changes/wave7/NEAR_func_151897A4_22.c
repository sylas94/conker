typedef struct Obj151897A4 {
    char pad0[0x8A];
    u8 unk8A;
} Obj151897A4;

typedef struct Node151897A4 {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
    u8 unk4;
    char pad5[1];
    s16 unk6;
    Mtx *unk8;
    struct Node151897A4 *unkC;
    Obj151897A4 *unk10;
} Node151897A4;

Gfx *func_151137D4(Gfx *, Obj151897A4 *, Mtx *, s32, s32, s32);

Gfx *func_151897A4(Gfx *gfx, Node151897A4 *node, s16 arg2) {
    s32 i;
    s32 count;
    s32 base;
    s32 step;
    s32 alpha;
    Mtx *mtx;
    s32 frame;
    s32 n;
    s32 saved;

    if (node->unk2 == 0) {
        return gfx;
    }
    count = node->unk2;
    frame = D_800BE9C0;
    step = node->unk3;
    n = node->unk1;
    base = frame * n;
    saved = node->unk10->unk8A;
    for (i = 0; i < count; i++) {
        alpha = ((i + 3) * step * 32) >> 8;
        node->unk10->unk8A = alpha;
        mtx = &node->unk8[base + i];
        gfx = func_151137D4(gfx, node->unk10, mtx, arg2, 0, 0);
    }
    node->unk10->unk8A = saved;
    return gfx;
}
