extern f32 D_800986EC;
extern f32 D_800C3FD0[3];
extern void func_150380C0(f32 *, s32, s32, s32, f32, s32, s32, s32, s32, s32, s32);

void func_1503B708(f32 *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 argA) {
    arg0[0] = -99999.0f;
    arg0[1] = -99999.0f;
    arg0[2] = -99999.0f;
    D_800C3FD0[0] = -99999.0f;
    D_800C3FD0[1] = -99999.0f;
    D_800C3FD0[2] = -99999.0f;
    if (func_15037880(arg3, arg0) == 0) {
        func_150380C0(arg0, arg1, arg2, arg3, arg4, arg5, arg6, arg7, arg8, arg9, argA);
    }
}
