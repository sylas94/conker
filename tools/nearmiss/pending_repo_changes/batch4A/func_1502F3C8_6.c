void func_1502F490(struct127 *arg0, f32 *x, f32 *y, f32 *z, s32 arg4);

void func_1502F3C8(void) {
    s32 i;
    u8 parent;

    for (i = 0; i < 25; i++) {
        if (D_800CC2D0[i].interaction_state != 0) {
            parent = D_800CC2D0[i].unk274;
            if (parent != 0) {
                D_800CC2D0[i].y_position = D_800CC2D0[i].unk180;
                func_1502F490(&D_800CC2D0[parent - 1], &D_800CC2D0[i].x_position, &D_800CC2D0[i].y_position,
                              &D_800CC2D0[i].z_position, *(u16 *)((u8 *)&D_800CC2D0[i] + 0x19E));
                if (D_800CC2D0[i].y_position < D_800CC2D0[i].unk180) {
                    D_800CC2D0[i].y_position = D_800CC2D0[i].unk180;
                } else {
                    D_800CC2D0[i].unk180 = D_800CC2D0[i].y_position;
                }
            }
        }
    }
}
