typedef struct AnimCmd {
    /* 0x0 */ f32 time;
    /* 0x4 */ u8  pad4[3];
    /* 0x7 */ u8  cmd;
    /* 0x8 */ s32 arg;
} AnimCmd;

typedef struct AnimPlayer {
    /* 0x00 */ u8  pad0[8];
    /* 0x08 */ f32 unk8;
    /* 0x0C */ u8  padC[0x1C];
    /* 0x28 */ s32 unk28;
} AnimPlayer;

typedef struct AnimObj {
    /* 0x000 */ u8  pad0[5];
    /* 0x005 */ u8  unk5;
    /* 0x006 */ u8  pad6[0xAE];
    /* 0x0B4 */ f32 unkB4;
    /* 0x0B8 */ u8  padB8[0x80];
    /* 0x138 */ u8  unk138;
    /* 0x139 */ u8  pad139[0x8B];
    /* 0x1C4 */ AnimCmd *unk1C4;
    /* 0x1C8 */ u8  pad1C8[0x108];
    /* 0x2D0 */ AnimPlayer *unk2D0;
} AnimObj;

extern u8 D_800C365E;
extern u8 D_80099A30[];
extern void (*D_800863FC[])(void);

f32 func_1506AD30(AnimObj *obj, f32 time, u8 filter) {
    s32 anim;
    u8 cmd;
    s32 i;

    if (obj->unk5 == 4) {
        return 0.0f;
    }
    D_800D1878 = 0.0f;
    if (time < obj->unkB4) {
        obj->unk138 = 0;
    }
    D_800D1880 = 1;
    while (obj->unk1C4 && obj->unk1C4[obj->unk138].time <= time && D_800D1880) {
        if (obj->unk1C4[obj->unk138].time < 900.0f) {
            D_800D1580 = obj->unk1C4[obj->unk138].arg;
            D_800D1874 = *(f32 *)&D_800D1580;
            anim = obj->unk2D0->unk28;
            if (D_800C35EA == 0 || D_800C365E != 0) {
                cmd = obj->unk1C4[obj->unk138].cmd;
                if (filter) {
                    i = 0;
                    while (filter) {
                        if (D_80099A30[i] == 0) {
                            cmd = 0;
                        }
                        if (cmd == D_80099A30[i]) {
                            break;
                        }
                        i++;
                    }
                }
                if (cmd) {
                    D_800863FC[cmd]();
                }
            }
            if (anim != obj->unk2D0->unk28) {
                time = obj->unk2D0->unk8;
            } else {
                obj->unk138++;
            }
        }
    }
    return D_800D1878;
}
