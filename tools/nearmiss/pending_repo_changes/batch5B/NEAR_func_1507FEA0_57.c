typedef struct {
    u8 unk0;
    u8 pad1;
    u16 unk2;
    u8 unk4;
    u8 unk5;
    u8 pad6[6];
    u8 unkC;
    u8 unkD;
} MoveState1507FEA0;

typedef struct {
    u8 pad0[0x58];
    MoveState1507FEA0 unk58;
    s16 unk66;
} Ext1507FEA0;

void func_1507FF94(ActorUniqueIdFields *arg0);

void func_1507FEA0(struct127 *arg0) {
    Ext1507FEA0 *ext;
    MoveState1507FEA0 *state;

    ext = (Ext1507FEA0 *)arg0->unk31C;
    if (ext == NULL) {
        return;
    }
    if (arg0->unk127 == 0xFF) {
        return;
    }
    state = &ext->unk58;
    if (((u8 *)arg0)[0x13A] != 0) {
        ((u8 *)arg0)[0x13A]--;
    }
    if (state->unk0 == 1 && D_800C35EA != 1) {
        s32 dt = D_800BE9E4;
        s32 cur = state->unk2;
        s32 lim = 0xFFFF - dt;

        if (cur < lim) {
            state->unk2 = cur + dt;
        }
    } else {
        state->unk2 = 0;
        state->unk4 = 0;
        state->unk5 = 0;
        state->unkC = 0;
        state->unkD = 0;
    }
    ext = (Ext1507FEA0 *)arg0->unk31C;
    if (ext->unk66 != 0) {
        if (D_800BE9E4 < ext->unk66) {
            ext->unk66 -= D_800BE9E4;
        } else {
            func_1507FF94((ActorUniqueIdFields *)arg0);
            ((Ext1507FEA0 *)arg0->unk31C)->unk66 = 0;
        }
    }
    func_1507FC2C(arg0);
}
