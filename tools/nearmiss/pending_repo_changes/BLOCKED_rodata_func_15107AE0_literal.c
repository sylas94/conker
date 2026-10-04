void func_15107AE0(struct Vec15107A20 *arg0, struct Vec15107A20 *arg1, struct Vec15107A20 *arg2, struct Vec15107A20 *arg3) {
    f32 dx = arg1->x - arg0->x;
    f32 dy = arg1->y - arg0->y;
    f32 dz = arg1->z - arg0->z;

    arg2->x = arg0->x + dx * 0.333f;
    arg2->y = arg0->y + dy * 0.333f;
    arg2->z = arg0->z + dz * 0.333f;
    arg3->x = arg0->x + dx * 0.6667f;
    arg3->y = arg0->y + dy * 0.6667f;
    arg3->z = arg0->z + dz * 0.6667f;
}
