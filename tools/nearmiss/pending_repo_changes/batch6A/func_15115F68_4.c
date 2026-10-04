/* near-miss 4: two adjacent sll/sra pairs scheduled in the other order (t7<->t6, t1<->t9).
   576 decl/assign orders + 162 type/test combos all stay at 4. */
struct Obj15115F68 {
    f32 unk0;
    u8 pad4[0x38];
    s32 unk3C;
    u8 pad40[0x3C];
    f32 unk7C;
    f32 unk80;
};

void func_15115F68(struct Obj15115F68 *arg0) {
    s8 div = (s8)arg0->unk3C;
    s8 speed = (s8)(arg0->unk3C >> 16);
    s8 max = (s8)(arg0->unk3C >> 8);
    s8 min = (s8)(arg0->unk3C >> 24);

    if (div != 0) {
        arg0->unk0 += arg0->unk7C / div + speed;
    } else {
        arg0->unk0 += speed * D_800BE9E4;
    }
    if (max < arg0->unk0) {
        arg0->unk0 = max;
    } else if (arg0->unk0 < min) {
        arg0->unk0 = min;
    }
    arg0->unk7C = arg0->unk80 = 0.0f;
}
