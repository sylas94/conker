typedef struct {
    u8  pad0[0x6];
    u8  unk6;
} struct15033E84;
struct15033E84 *func_15033E84(struct127 *arg0);

void func_15052F9C(struct127 *arg0, f32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9) {
    struct127 *other;
    s32 kind;
    s32 hit;
    struct15033E84 *record;
    s32 angle;
    s32 state;

    hit = 0;
    kind = -1;
    if (arg0->id == 0x48) {
        record = func_15033E84(arg0);
        if (record != 0) {
            kind = record->unk6;
        }
    }
    other = &D_800CC2D0[arg0->unk124];
    if ((arg8 != 0) ||
        ((other->y_position < (arg0->y_position + (arg1 * arg0->y_scale))) && (other->y_velocity < 0.0f))) {
        arg0->unk13C = arg0->unk124 + 0x64;
        if (arg9 != 0) {
            D_800D1580 = arg9;
            func_1506E5FC();
        }
        other->unk1CC = other->y_position;
        other->unk76 = arg0->unk7A;
        other->unk31C->unk30 = 0;
        if (arg0->interaction_state == 0x20) {
            other->y_velocity = 0.0f;
            state = 2;
            arg0->y_velocity = 0.0f;
            if (arg0->id == 0x48) {
                if (kind == 0x7A) {
                    arg0->unk65 = arg0->unk124 + 1;
                    arg0->unk5C = arg2;
                    arg0->unk101 |= arg3;
                    func_1505E650(other, 5, 1.0f, 0.0f, 0.0f, 0.0f, 0);
                    func_15083568(other, 0x79, 1.0f, 0);
                    hit = 1;
                }
            } else {
                arg0->y_scale = 0.75f;
                other->y_position = arg0->y_position;
                state = 1;
                if (D_800BE9F0 == 6) {
                    state = 0x81;
                }
            }
            angle = arg0->unk7A;
            other->unk76 = angle;
            other->unk78 = angle;
            other->unk7A = angle;
            other->unk40 = ((s16) (angle + 0x4000)) * 0.005493164f;
            other->unk31C->unk4E = state;
            other->unk83 = 0;
            other->disable_run = 0;
        } else {
            other->unk65 = D_800C3E78 + 1;
            other->unk5C = arg2;
            other->unk101 |= arg3;
            other->disable_run = 0;
        }
        other->immune = arg6;
        other->unk239 = arg7;
        other->unk31C->unk27 = 0;
        arg0->unk232 = arg5;
        arg0->unk218 = 0;
        if (arg4 != 0) {
            func_1506160C(other, 1, 0, 0, 0);
            other->unk101 |= 0x40;
        }
    }
    if (hit != 0) {
        func_15060F28(arg0, 0);
    }
}


