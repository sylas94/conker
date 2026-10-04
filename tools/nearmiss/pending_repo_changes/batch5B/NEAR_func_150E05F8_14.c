extern f32 D_800A0FD0;
extern f32 D_800A0FD4;

typedef struct {
    u8 pad0[0x10];
    s16 unk10;
    s16 unk12;
    s16 unk14;
    u8 pad16[0x8A - 0x16];
    u8 unk8A;
} Obj150E05F8;

void func_150E05F8(Obj150E05F8 *arg0) {
    f32 dx;
    f32 dy;
    f32 dz;
    f32 dist;
    s32 alpha;

    dz = D_800DBFF0->unk300 - arg0->unk14;
    dx = D_800DBFF0->unk2F8 - arg0->unk10;
    dy = D_800DBFF0->unk2FC - arg0->unk12;
    dist = sqrtf(dz * dz + (dx * dx + dy * dy));
    if (dist <= D_800A0FD0) {
        alpha = 0xFF;
    } else if (D_800A0FD4 <= dist) {
        alpha = 0;
    } else {
        alpha = 255.0f - (dist - D_800A0FD0) * (1.0f / (D_800A0FD4 - D_800A0FD0)) * 255;
    }
    arg0->unk8A = alpha;
}
