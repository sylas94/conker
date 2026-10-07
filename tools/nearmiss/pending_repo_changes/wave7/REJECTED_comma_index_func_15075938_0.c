void func_15075938(void) {
    u8 changed;
    s32 temp_a0;
    s32 refIndex;
    s32 temp_v0;

    changed = 0;
    temp_a0 = D_800D154C->unk21E - D_800D154C->unk221;
    if (temp_a0 < 0) {
        temp_v0 = (*(u8 **)&D_800D2108)[D_800D154C->unk13F];
        temp_a0 = (temp_a0 + temp_v0) - 1;
    } else {
        temp_v0 = (*((u8 **) (&D_800D2108)))[0, D_800D154C->unk13F];
        if ((temp_v0 - 1) <= temp_a0) {
            temp_a0 = (temp_a0 - temp_v0) + 1;
        }
    }
    refIndex = (D_800D1891 == 0xFF) ? temp_v0 - 2 : D_800D1891;
    if (D_800D1892 == 0) {
        if (refIndex == temp_a0) {
            changed = 1;
        }
    } else if (D_800D1892 == 1) {
        if (refIndex != temp_a0) {
            changed = 1;
        }
    } else if (D_800D1892 == 2) {
        if (refIndex < temp_a0) {
            changed = 1;
        }
    } else {
        if (refIndex > temp_a0) {
            changed = 1;
        }
    }
    if (changed) {
        func_15075400(D_800D1890);
    }
}
