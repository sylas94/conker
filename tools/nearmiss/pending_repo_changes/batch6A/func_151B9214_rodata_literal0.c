/* BLOCKED rodata: D_800AA564 in block 24EFA0, every symbol of which is referenced only by game_1E6260
   (sole owner -> block migration candidate). Literal 0.0234f form (below) = 0; extern = 27 (reload after store);
   extern via a rate local = 20 (adds a frame slot). */
struct Sub151B9214 {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
};

struct Obj151B9214 {
    u8 pad0[0x170];
    struct Sub151B9214 unk170;
};

extern f32 D_800AA564;

s32 func_151B9214(struct Obj151B9214 *arg0) {
    struct Sub151B9214 *s;

    arg0->unk170.unk8 += arg0->unk170.unkC * D_800BE9A4;
    s = &arg0->unk170;
    s->unk8 = func_15144B68(arg0->unk170.unk8);
    s->unk0 = sinf(s->unk8) * s->unk4;
    if (0.0f < s->unk18) {
        s->unk18 -= D_800BE9A4;
        s->unkC += s->unk20 * D_800BE9A4;
        s->unk4 += s->unk1C * D_800BE9A4;
    } else {
        s->unkC += (s->unk14 - s->unkC) * 0.0234f;
        s->unk4 += (s->unk10 - s->unk4) * 0.0234f;
    }
    return 1;
}
