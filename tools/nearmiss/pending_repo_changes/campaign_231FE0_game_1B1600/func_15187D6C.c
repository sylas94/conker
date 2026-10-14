extern f32 D_8008D578;
extern f32 sinf(f32);
extern f32 cosf(f32);
void func_151EFE00(f32 (*)[4]);

void func_15187D6C(f32 m[4][4], f32 x, f32 y, f32 z) {
    f32 sx;
    f32 cx;
    f32 sz;
    f32 sy;
    f32 cy;
    f32 cz;

    x *= 0.017453292f;
    y *= 0.017453292f;
    z *= 0.017453292f;
    sx = sinf(x);
    cx = cosf(x);
    sy = sinf(y);
    cy = cosf(y);
    sz = sinf(z);
    cz = cosf(z);
    func_151EFE00(m);
    m[0][0] = (cy * cz) - (sx * sy * sz);
    m[0][1] = (cy * sz) + (sx * sy * cz);
    m[0][2] = -sy * cx;
    m[1][0] = -cx * sz;
    m[1][1] = cx * cz;
    m[1][2] = sx;
    m[2][0] = (sy * cz) + (sx * cy * sz);
    m[2][1] = (sy * sz) - (sx * cy * cz);
    m[2][2] = cx * cy;
}
