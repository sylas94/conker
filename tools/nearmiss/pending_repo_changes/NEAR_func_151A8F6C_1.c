typedef struct {
    u8 pad0[0x10];
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
} Emitter151A8F6C;

extern void func_15143874(s16, f32, f32 *, f32 *);

void func_151A8F6C(void *arg0, f32 *arg1, f32 *arg2, f32 *arg3) {
    Emitter151A8F6C *ptr;
    f32 f;
    s32 r;

    r = func_150ADA20();
    ptr = (Emitter151A8F6C *)((u8 *)arg0 + 0x28);
    f = func_150ADA68();
    func_15143874(r & 0xFF, f * ptr->unk20, arg1, arg1 + 2);
    arg1[0] += ptr->unk10;
    arg1[2] += ptr->unk18;
    arg1[1] = ptr->unk14;
    *arg2 = ptr->unk14;
    *arg3 = ptr->unk1C;
}
