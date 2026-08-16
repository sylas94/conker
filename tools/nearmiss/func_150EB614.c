/* Best non-matching attempt for func_150EB614 (SCORE 1883).
 * Structurally identical to the target; the ONLY real divergence is one extra
 * instruction: IDO makes `damping` memory-class (homes it at its definition,
 * `swc1 $f6,0x2c(sp)`) where the target keeps it in $f18 and spills it just
 * before the jal. Every later diff is register-renaming cascade from that.
 * Strong decomp-permuter candidate.
 */

extern f32 D_800A14DC;
extern f32 D_800A14E0;
extern f32 D_800A14E4;

typedef struct {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ u8  pad4[0xC];
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ s16 unk14;
    /* 0x16 */ u8  pad16[0x26];
    /* 0x3C */ s32 unk3C;
    /* 0x40 */ u8  pad40[0xF];
    /* 0x4F */ u8  unk4F;
    /* 0x50 */ u8  pad50[0x23];
    /* 0x73 */ u8  unk73;
    /* 0x74 */ u8  pad74[0x8];
    /* 0x7C */ f32 unk7C;
    /* 0x80 */ f32 unk80;
    /* 0x84 */ f32 unk84;
} struct_EB614;

void func_15117770(struct_EB614 *arg0);

void func_150EB614(struct_EB614 *arg0) {
    f32 speed;
    f32 dz;
    f32 target;
    f32 dx;
    f32 damping;
    f32 accel;
    f32 dy;
    f32 angle;
    f32 temp;
    f32 delta;

    if ((arg0->unk73 & 3) == 3) {
        return;
    }

    if ((arg0->unk73 & 3) != 2) {
        if (arg0->unk4F & 4) {
            if (D_800CC2D0[0].unk31C->unk57 != 0) {
                arg0->unk73 &= 0xFFFC;
                arg0->unk73 |= 2;
                arg0->unk3C = 0;
                arg0->unk7C = 0.5f;
                arg0->unk80 = D_800A14DC;
                arg0->unk84 = 0.0f;
            }
            dz = (f32) arg0->unk14 - D_800CC2D0[0].z_position;
            dx = (f32) arg0->unk10 - D_800CC2D0[0].x_position;
            dy = (f32) arg0->unk12 - D_800CC2D0[0].y_position;
            temp = sqrtf((dz * dz) + ((dx * dx) + (dy * dy)));
            if (temp > 740.0f) {
                temp = 740.0f;
            }
            target = (temp * D_800A14E0) + -40.0f;
        } else {
            target = -40.0f;
        }

        angle = arg0->unk0;
        damping = arg0->unk7C;
        accel = arg0->unk80;
        speed = arg0->unk84;

        if (angle != target || speed != 0.0f) {
            angle += speed * (f32) D_800BE9E4;
            delta = func_15048A70(angle, target);
            if (0.0f < delta) {
                speed += fabsf(delta) * accel;
            } else {
                speed -= fabsf(delta) * accel;
            }
            speed *= damping;

            if (fabsf(delta) < D_800A14E4 && fabsf(speed) < D_800A14E4) {
                speed = 0.0f;
                angle = target;
            } else if (angle < 0.0f) {
                angle += 360.0f;
            } else if (angle >= 360.0f) {
                angle -= 360.0f;
            }
            arg0->unk84 = speed;
        }
        arg0->unk0 = angle;
    } else {
        temp = arg0->unk0;
        func_15117770(arg0);
        if (temp == arg0->unk0) {
            arg0->unk73 &= 0xFFFC;
            arg0->unk73 |= 3;
            arg0->unk0 = 0.0f;
        }
    }
}
