void func_15074A94(void) {
    f32 t; f32 d;
    d = func_1505A72C(D_800CC2D0, D_800D154C);
    if (D_800D154C->unk148 < D_8009A0E8) {
        D_800D154C->unk148 = D_800D154C->unk154;
    }
    if (d < 200.0f) { t = D_8009A0EC; } else { if (D_8009A0F0 < d) { t = D_800D154C->unk148; } else { f32 tmp = D_8009A0F4; t = D_800D154C->unk148; t = t - tmp; t = t * ((d - 200.0f) / D_8009A0F8); t = t + tmp; } }
    D_800D154C->unk154 = D_800D154C->unk158 = t;
    D_800D154C->unk15C = D_8009A0FC;
}
