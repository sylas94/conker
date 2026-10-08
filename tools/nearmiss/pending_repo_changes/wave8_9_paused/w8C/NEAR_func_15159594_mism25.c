typedef struct {
    u8 pad0;
    u8 unk1;
    u8 pad2[0xA];
    u8 unkC;
    u8 padD[0x33];
    f32 unk40;
    s32 unk44;
    f32 unk48;
    f32 unk4C;
    u8 pad50[0x4];
    f32 unk54;
    u8 pad58[0x4];
    f32 unk5C;
    u8 pad60[0x20];
    f32 unk80;
    u8 unk84[0x19];
    u8 unk9D;
    u8 pad9E[0xA];
    f32 unkA8;
} Struct15159594;

extern s32 func_151596BC();
extern s32 func_1514672C(f32 *arg0);
extern s32 func_15046C00(f32 *arg0, s32 arg1, s32 arg2, f32 *arg3);
extern u8 func_151D8E20(void);
extern f32 D_800A63A4;

u8 func_15159594(Struct15159594 *arg0, f32 *arg1) {
    u8 ret;
    s32 snd;
    f32 sp34[3];

    ret = 1;
    if (func_151596BC(arg0, arg1) != 0) {
        if (0.0f < arg0->unk5C) {
            sp34[0] = arg0->unk40 + arg0->unk4C;
            sp34[1] = arg1[1];
            sp34[2] = arg0->unk48 + arg0->unk54;
            if (func_1514672C(sp34) == 0) {
                return 0;
            }
            if (func_15046C00(sp34, 0, arg0->unk44, &arg0->unk80) != 0) {
                sp34[1] = arg0->unk80;
                if (arg0->unk9D == 3) {
                    snd = func_151D8E20();
                    func_151DBCBC(snd, arg0->unkA8 * D_800A63A4, 0xFF, (s32)arg0->unk84, sp34, arg0->unkC, arg0->unk1);
                }
                ret = 0;
            }
        }
    } else {
        ret = 0;
    }
    return ret;
}
