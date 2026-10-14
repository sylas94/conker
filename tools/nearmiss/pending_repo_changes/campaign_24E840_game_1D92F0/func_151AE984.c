extern f32 D_800A9D90;
extern f32 D_800A9D94;

void func_151AE984(f32 *arg0, f32 arg1, f32 arg2, f32 arg3, u8 arg4, u8 arg5) {
    f32 k;
    f32 vel[3];
    f32 c;
    u32 b;
    u32 a;
    f32 f;

    k = 0.103f;
    vel[0] = -arg1 * k;
    vel[1] = -arg2 * k;
    vel[2] = -arg3 * k;
    f = func_150ADA68();
    a = func_150ADA20();
    b = func_150ADA20();
    c = func_150ADA68() * 219.0f + 77.0f;
    func_151D9014(arg0, vel, 0, f * D_800A9D90 + D_800A9D94, a % 31 + 60, b % 101 + 155,
                  c, arg4, 1.0f, 1.0f, 0, 0, 1, 0, arg5, 1);
}

====

void func_151AE984(f32 *arg0, f32 arg1, f32 arg2, f32 arg3, u8 arg4, u8 arg5) {
    f32 k;
    f32 vel[3];
    f32 c;
    u32 b;
    u32 a;
    f32 f;

    k = 0.103f;
    vel[0] = -arg1 * k;
    vel[1] = -arg2 * k;
    vel[2] = -arg3 * k;
    f = func_150ADA68();
    a = func_150ADA20();
    b = func_150ADA20();
    c = func_150ADA68() * 219.0f + 77.0f;
    func_151D9014(arg0, vel, 0, f * 0.602f + -1.045f, a % 31 + 60, b % 101 + 155,
                  c, arg4, 1.0f, 1.0f, 0, 0, 1, 0, arg5, 1);
}
