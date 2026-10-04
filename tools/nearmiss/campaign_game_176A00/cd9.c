void func_1514C858(f32 arg0, f32 arg1, f32 arg2, f32 arg3, s16 arg4, s16 arg5, s16 arg6, s16 arg7,
                   u8 arg8, s32 arg9, f32 argA, s32 argB, u8 argC) {
    f32 temp_arg0 = arg0;
    f32 temp_arg1 = arg1;
    f32 ts;
    f32 tc;
    f32 rx;
    f32 rz;
    f32 x;
    f32 z;
    s16 range;
    s16 base;
    u8 angle;
    s16 i;
    f32 s;
    f32 c;

    ts = func_151423D8(arg4 - 0x40);
    tc = func_151423D8(arg4);
    if (arg6 < arg5) {
        range = arg5 - arg6 + 1;
        base = arg6;
    } else {
        range = arg6 - arg5 + 1;
        base = arg5;
    }
    i = 0;
    if (arg7 > 0) {
        rx = arg3 * ts;
        rz = arg3 * tc;
        do {
            angle = (u32)func_150ADA20() % range + base;
            s = func_151423D8(angle - 0x40);
            c = func_151423D8(angle);
            x = rx * c + temp_arg0;
            z = rz * c + arg2;
            if (D_8008AA00[arg8] != 0) {
                if (D_8008AA00[arg8](3, i, x, temp_arg1 - arg3 * s, z,
                             temp_arg0, temp_arg1, arg2, angle, arg4, arg3, arg9, argA, argB, argC) == 0) {
                    return;
                }
            }
            i++;
        } while (i < arg7);
    }
}
