typedef struct {
    s16 *unk0;
    u8 pad4[4];
    s16 *unk8;
    u32 unkC;
} Rec1509D08C;

typedef struct {
    Rec1509D08C *rec;
    u8 pad4[4];
} Slot1509D08C;

s32 func_1509D08C(s32 arg0, s32 arg1, s32 *arg2, s32 *arg3) {
    Slot1509D08C *tbl = (Slot1509D08C *)D_800D2FB0;
    Slot1509D08C *slot = &tbl[arg1];
    Rec1509D08C *rec;
    u32 i;
    s16 v;

    if (tbl == NULL) {
        if (arg2 != NULL) {
            *arg2 = 0xBF;
        }
        if (arg3 != NULL) {
            *arg3 = 0;
        }
        return 0;
    }
    if (slot[1].rec == NULL) {
        if (arg2 != NULL) {
            *arg2 = 0xBF;
        }
        if (arg3 != NULL) {
            *arg3 = 0;
        }
        return 0;
    }
    if (arg2 != NULL) {
        *arg2 = slot[1].rec->unk8[0];
    }
    if (arg3 != NULL) {
        *arg3 = slot[1].rec->unk0[0];
    }
    rec = slot[1].rec;
    for (i = 0; i < rec->unkC; i++) {
        v = rec->unk8[i];
        if (!(((u8 *)D_800D2E4C)[v >> 3] & (1 << (v & 7)))) {
            return 0;
        }
    }
    return 1;
}
