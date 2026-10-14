void func_151AF388(f32 *arg0, f32 arg1, f32 arg2, f32 arg3, u8 arg4) {
    f32 k;
    f32 vel[3];
    u8 flag;
    f32 c;
    u32 b;
    u32 a;
    f32 f;

    k = 0.13000001f;
    vel[0] = -arg1 * k;
    vel[1] = -arg2 * k;
    vel[2] = -arg3 * k;
    flag = (func_150ADA20() & 1) ? 1 : 0;
    f = func_150ADA68();
    a = func_150ADA20();
    b = func_150ADA20();
    c = func_150ADA68() * 202.0f + 142.0f;
    func_151D9014(arg0, vel, 0, f * 0.126f + -0.702f, (a & 0xF) + 10, b % 45 + 137,
                  c, flag, 1.7f, 1.7f, 0, 0, 1, 0, arg4, 1);
}
