typedef struct Waypoint151CE51C {
    f32 unk0;
    f32 unk4;
    u8 pad8[0x14];
} Waypoint151CE51C;

typedef struct Lift151CE51C {
    u8 pad0[0x1E];
    u16 unk1E;
    u8 pad20[0x5];
    u8 unk25;
    u8 pad26[0x6];
    s8 unk2C;
    s8 unk2D;
    s8 unk2E;
    u8 pad2F[0x65];
    Waypoint151CE51C *unk94;
} Lift151CE51C;

typedef struct Arg151CE51C {
    u8 pad0[0x18];
    s32 unk18;
} Arg151CE51C;

struct Obj151CE634 *func_151CE634(s32);
void func_1515C1A0(struct127 *, f32 *, f32 *, f32 *);
s32 func_1505D024(struct127 *, s32, u16, s32);

void func_151CE51C(struct127 *arg0, Arg151CE51C *arg1) {
    f32 pos[3];
    f32 radius;
    f32 height;
    Lift151CE51C *lift;
    s32 idx;

    lift = (Lift151CE51C *)func_151CE634(arg1->unk18);
    if (lift == NULL) {
        return;
    }
    func_1515C1A0(arg0, pos, &radius, &height);
    if (lift->unk1E & 8) {
        if (lift->unk2C > 0) {
            idx = lift->unk2E - 1;
            if (idx < 0) {
                idx = lift->unk25 - 1;
            }
            if (pos[1] - height <= lift->unk94[idx].unk4) {
                func_1505D024(arg0, 0x60019, 0, -1);
            }
        }
    } else {
        if (lift->unk2C > 0) {
            if (lift->unk94[lift->unk2D].unk4 <= pos[1] + height) {
                func_1505D024(arg0, 0x60019, 0, -1);
            }
        }
    }
}
