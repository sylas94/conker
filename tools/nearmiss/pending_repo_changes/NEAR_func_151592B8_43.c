typedef struct {
    u8 pad0[0x28];
    f32 unk28;
    u8 pad2C[0x84 - 0x2C];
    u16 unk84;
    u8 pad86[0xAD - 0x86];
    u8 unkAD;
} Obj151592B8;

typedef struct {
    u8 ids[2];
} Ids151592B8;

extern Ids151592B8 D_8008B040;

s32 func_151592B8(Struct15158BD0_src *arg0, u8 arg1) {
    s32 special = 0;
    s32 ret;

    if (arg1 == 0) {
        Ids151592B8 list = D_8008B040;
        s32 hit = 0;
        s32 i;

        for (i = 1; i >= 0; i--) {
            if (((Obj151592B8 *)arg0)->unk84 == list.ids[i]) {
                hit = 1;
            }
            if (hit) {
                break;
            }
        }
        special = hit;
    }
    if (special) {
        ret = 3;
    } else if (((Obj151592B8 *)arg0)->unkAD) {
        ret = 2;
    } else if (((Obj151592B8 *)arg0)->unk28 != 0.0f) {
        ret = 1;
    } else {
        ret = 4;
    }
    return ret;
}
