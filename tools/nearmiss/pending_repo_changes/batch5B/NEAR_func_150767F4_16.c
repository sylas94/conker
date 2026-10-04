void func_150767F4(void) {
    s32 tmp0 = func_1505A630(D_800CC2D0[D_800D154C->unk222].x_position - D_800D154C->x_position, D_800D154C->z_position - D_800CC2D0[D_800D154C->unk222].z_position, 0) >> 8;

    if ((((tmp0 - (D_800CC34A[D_800D154C->unk222 * 0x196] >> 8)) + D_800D1891) & 0xFF) < (D_800D1891 * 2)) {
        func_15075400(D_800D1890);
    }
}
