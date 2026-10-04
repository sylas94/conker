typedef struct {
    f32 x;
    f32 y;
    f32 z;
} Vec3_151D5334;

typedef struct {
    Vec3_151D5334 pos;
    f32 unkC;
    f32 unk10;
    f32 unk14;
} Arg_151D5334;

void func_15164F0C(u8, u8, Arg_151D5334 *, u8, s32);

void func_151D5334(Vec3_151D5334 *arg0, f32 arg1, f32 arg2, f32 arg3, u8 arg4, u8 arg5, s32 arg6) {
    s32 i;
    Arg_151D5334 sp3C;

    sp3C.pos = *arg0;
    sp3C.unkC = arg1;
    sp3C.unk10 = arg2;
    sp3C.unk14 = arg3;
    for (i = 0; i < D_80082FA0 + 1; i++) {
        func_15164F0C(arg4, i, &sp3C, arg5, arg6);
    }
}
