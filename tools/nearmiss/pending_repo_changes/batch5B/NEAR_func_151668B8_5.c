typedef struct {
    s32 unk0;
    s32 unk4;
} RenderModePair151668B8;

extern s16 D_800DCE40;
extern s32 D_800DD220;
extern s32 D_800DD224;
extern s32 D_800DD228;
extern s32 D_800DD230;
extern u8 D_800903F4[];
extern s32 D_800D2C9C;
extern RenderModePair151668B8 D_800A4AC8[];
extern Gfx *func_15094F70(Gfx *, s32, s32, s32, s32, s32, s32, s32, s32);
extern Gfx *func_15142FBC(Gfx *gfx, s32 arg1, s32 arg2, u8 *arg3);

Gfx *func_151668B8(Gfx *gfx, s32 arg1, s32 arg2, s32 arg3) {
    u8 update;

    D_800DD228 = (s32)D_800903F4;
    D_800DD220 = D_800DCE40;
    D_800DCE40 += 0x80;
    update = 1;
    if (D_800DCE40 >= 0x500) {
        D_800DCE40 = 0;
    }
    D_800DD224 = 1;
    gfx = func_15094F70(gfx, D_800DD228, D_800DD220, (s32)&D_800DD230, 0, 0, 0, D_800DD224, 3);
    return func_15142FBC(gfx, D_800D2C9C | 0x80000 | 0x2CA0, D_800A4AC8[3].unk4 | D_800A4AC8[3].unk0, &update);
}
