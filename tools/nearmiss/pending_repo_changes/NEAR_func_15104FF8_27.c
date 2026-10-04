typedef struct {
    s16 x;
    s16 y;
    s16 z;
    u8 pad6[0xE];
    u8 unk14;
} Func15104FF8Target;

typedef struct {
    Func15104FF8Target *target;
    f32 accum;
    s16 timer;
} Func15104FF8Data;

void func_15104FF8(struct131 *arg0, s32 arg1, u8 arg2) {
    Func15104FF8Data *data = (Func15104FF8Data *)((u8 *)arg0 + 0x28);

    if (arg2 == 0x38 && data->target->unk14 == 1) {
        data->timer = 300;
        func_1000FD38(func_1000EF40, data->target, 0);
        func_1000FA64(0x236, ((Func15104FF8Target *)arg0->unk28)->x, ((Func15104FF8Target *)arg0->unk28)->y,
                      ((Func15104FF8Target *)arg0->unk28)->z, 0x4000, 1500, 1000, (s32)func_1000EF40,
                      (void *)arg0->unk28, 0, 8, 0);
    }
}
