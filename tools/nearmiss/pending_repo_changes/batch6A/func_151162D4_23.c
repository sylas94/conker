/* near-miss 23: only residue = shared lw 0x3C lands in v0 (ours) vs t9 (golden); amp-before-speed order right.
   Needs TU's later 'extern void func_151162D4(void *);' changed to the struct type + cast at call. */
struct Obj151162D4 {
    u8 pad0[0x12];
    s16 unk12;
    u8 pad14[0x4];
    f32 unk18;
    u8 pad1C[0x20];
    s32 unk3C;
    u8 pad40[0x1C];
    s16 unk5C;
    u8 pad5E[0x1E];
    s32 unk7C;
};

void func_151162D4(struct Obj151162D4 *arg0) {
    f32 amp;
    u32 speed;
    s16 initial;

    initial = (s16)(s32)((f32)arg0->unk12 + arg0->unk18);
    amp = (s16)arg0->unk3C;
    speed = (arg0->unk3C >> 16) & 0xFFFF;
    arg0->unk18 = cosf((f32)arg0->unk7C * 0.0054931640625f) * amp;
    arg0->unk7C += speed * D_800BE9E4;
    arg0->unk5C = (s32)(((f32)arg0->unk12 + arg0->unk18) - (f32)initial);
}
