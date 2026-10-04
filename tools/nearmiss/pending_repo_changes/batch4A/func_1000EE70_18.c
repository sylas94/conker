typedef struct {
    u8 pad0[2];
    s16 unk2;
    s16 unk4;
    s16 unk6;
    u8 pad8[0x10];
    struct127 *unk18;
    s32 unk1C;
    u8 pad20[4];
    u16 unk24;
} struct_init_EB00_EE70;


s32 func_1000EE70(struct_init_EB00_EE70 *arg0, s32 arg1, s32 *arg2, s32 arg3, s32 arg4, s32 *arg5) {
    struct127 *obj = arg0->unk18;

    if (obj != NULL && *arg2 != 0) {
        s32 id = arg0->unk1C & 0xFF;

        if ((obj->interaction_state != 0) && (obj->unique_id == id)) {
            *arg5 = (((u32)obj->unk184 >> 3) & 0x30) << 1;
            arg0->unk2 = (s16)obj->x_position;
            arg0->unk4 = (s16)obj->y_position;
            arg0->unk6 = (s16)obj->z_position;
            return 0;
        }
        if (func_1000F44C(arg0->unk24) == 0) {
            return 0;
        }
    }
    return 1;
}
