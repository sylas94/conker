extern u8 D_800DF700[0xB4];
extern s32 D_800DF7B4;

typedef struct { s32 w; } Word15187EC0;

typedef struct {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
    u8 unk4;
    u8 unk5;
    u8 unk6;
    u8 unk7;
    u8 unk8;
    u8 pad9[7];
    Word15187EC0 unk10;
    f32 unk14;
    u8 unk18[0xC];
} Ent15187EC0;

s32 func_15187EC0(Word15187EC0 arg0, f32 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7) {
    Ent15187EC0 *e;

    if (D_800DF7B4 < 5) {
        e = &((Ent15187EC0 *)D_800DF700)[D_800DF7B4];
        e->unk14 = arg1;
        e->unk0 = e->unk6 = arg2;
        e->unk1 = e->unk7 = arg3;
        e->unk2 = e->unk8 = arg4;
        e->unk10 = arg0;
        e->unk3 = arg5;
        e->unk4 = arg6;
        e->unk5 = arg7;
        bzero(e->unk18, 12);
        return D_800DF7B4++;
    }
    return -1;
}
