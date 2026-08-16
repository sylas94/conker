void func_150585F0(struct127 *arg0) {
    f32 temp_f14;
    u16 phi_a2;

    temp_f14 = arg0->unk109 * D_80099478;
    func_1505A3A8(0.0f, arg0, 1.0f, temp_f14, 0);
    if (arg0->unk1CC < D_8009947C) {
        arg0->unk1CC = arg0->y_position;
    }
    if ((arg0->in_water != 0) && (arg0->in_water < 0xA)) {
        arg0->gravity = 0.0f;
        if (arg0->y_velocity < 60.0f) {
            arg0->y_velocity *= D_80099480;
        }
        if (((arg0->unk118 - 60.0f) + 40.0f) < arg0->y_position) {
            arg0->unk81 = 0;
            arg0->unk83 = 0;
            arg0->in_water = 0;
            arg0->unkB8 = 0.0f;
            arg0->gravity = 4.0f;
        }
    }
    if ((D_800BE616 == 0) || (1 != arg0->interaction_state)) {
        arg0->unk21C = 0;
    }
    if (arg0->stunned != 0xFF) {
        if (arg0->stunned != 0xFE) {
            if ((arg0->health != 0) || (1 != arg0->interaction_state)) {
                arg0->stunned -= 1;
            }
        }
        arg0->unk10C -= D_800CC264;
        if ((arg0->unk28 < D_80099484) && ((arg0->unkF4 & 0x100) != 0)) {
            arg0->unk10C = 0;
        }
        if (arg0->unk10C <= 0) {
            if (arg0->unk31C != 0) {
                arg0->unk31C->matrix_physics = 0;
            }
            arg0->unk10C = 0;
            func_1505E874(D_800C3E78, arg0);
        }
        if (arg0->stunned == 0) {
            arg0->xz_velocity = 0.0f;
            arg0->unk81 = 0;
            arg0->unk76 = arg0->unk78 = arg0->unk7A;
            if (arg0->in_water != 0) {
                arg0->y_velocity = 0.0f;
                if (1 == arg0->interaction_state) {
                    func_1506B078();
                }
            } else if (1 == arg0->interaction_state) {
                arg0->gravity = 4.0f;
                arg0->unkF8 &= 0xFFFF7FFF;
            }
            if (arg0->unk238 != 0) {
                arg0->unk23A = arg0->unk238;
            }
        } else if ((arg0->unk10B & 2) == 0) {
            phi_a2 = arg0->unk76;
            if ((arg0->unk10B & 4) != 0) {
                phi_a2 ^= 0x8000;
            }
            arg0->unk80 = 0xA;
            func_150599C8(arg0, 0xC, phi_a2);
        }
    }
}

// NON-MATCHING: 80% there
