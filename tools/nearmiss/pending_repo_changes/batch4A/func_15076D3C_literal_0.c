void func_15076D3C(void) {
    f32 scale = 0.01f;

    {
        s16 xz = D_800D1890 | (D_800D1891 << 8);
        s16 y = D_800D1892 | (D_800D1893 << 8);

        D_800D154C->xz_scale = xz * scale;
        D_800D154C->y_scale = y * scale;
    }
    D_800D154C->unk154 = D_800D154C->xz_scale;
    D_800D154C->unk158 = D_800D154C->y_scale;
    func_15062BDC(D_800D154C, D_800D154C->xz_scale, D_800D154C->y_scale);
}
