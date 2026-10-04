typedef struct {
    u8 pad0[0xE];
    u16 unkE;
    s16 unk10;
} Info15035714;

typedef struct {
    u8 pad0[0x30];
    s32 unk30;
    u8 pad34[4];
    f32 unk38;
} Arg15035714;

extern f32 D_80097D70;
extern f32 D_800D9C10[][4][4];
extern s32 func_150A6360(s32, void *, s32, f32, f32, f32, f32, f32);

s32 func_15035714(s32 mode, struct127 *obj, Arg15035714 *arg2, f32 arg3) {
    f32 y;
    f32 hh;
    f32 sy;
    f32 sx;
    s32 id;
    s32 base = D_800BE628;
    Info15035714 *info;

    id = obj->id;
    info = (Info15035714 *)D_800D1C90[id];
    sx = (u32)info->unkE * obj->xz_scale;
    sy = (u32)info->unkE * obj->y_scale;
    hh = info->unk10 * obj->y_scale;
    if (mode == 1 || mode == 0) {
        y = arg3 - ((obj->y_position + hh) - arg3);
    } else {
        y = obj->y_position + hh;
    }
    if (func_150A6360(base, D_800D9C10, arg2->unk30, y, arg2->unk38, sx, sy, D_80097D70) == 0) {
        return 1;
    }
    return 0;
}
