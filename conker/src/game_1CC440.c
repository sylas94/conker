#include <ultra64.h>
#include "functions.h"
#include "variables.h"

void func_15143794(s32, s32, f32, f32 *);
s32 func_1510F8CC(s32);
void func_15152B38(void *, u8, s32);
s32 func_1513170C(s32 *, s32);
struct Obj151A2960;
extern void (*D_8008F8E0[])(struct Obj151A2960 *, s32);
extern f32 D_800A8D3C;
extern f32 D_800A8D40;
extern f32 D_800A8D44;
extern f32 D_800A8D30;
extern f32 D_800A8D34;
extern f32 D_800A8D38;


#pragma GLOBAL_ASM("asm/nonmatchings/game_1CC440/func_1519EF90.s")

struct Sub1519F108 {
    u8 pad0[0x58];
    s32 unk58;
    s32 unk5C;
    s32 unk60;
};

struct Obj1519F108 {
    u8 pad0[0x20];
    s32 unk20;
    u8 pad24[0x74];
    struct Sub1519F108 **unk98;
};

void func_151478F4(struct Obj1519F108 *);

void func_1519F108(struct Obj1519F108 *arg0) {
    struct Sub1519F108 **pp = arg0->unk98;
    s32 *ptr;
    if (*pp != 0) {
        ptr = (s32 *)((u8 *)*pp + 0x58);
        if (arg0->unk20 == 6) {
            ptr[0] = 0;
        }
        if (arg0->unk20 == 7) {
            ptr[2] = 0;
        }
    }
    func_151478F4(arg0);
}

void func_15147928(struct Obj1519F108 *);

void func_1519F168(struct Obj1519F108 *arg0) {
    struct Sub1519F108 **pp = arg0->unk98;
    s32 *ptr;
    if (*pp != 0) {
        ptr = (s32 *)((u8 *)*pp + 0x58);
        if (arg0->unk20 == 6) {
            ptr[0] = 0;
        }
        if (arg0->unk20 == 7) {
            ptr[2] = 0;
        }
    }
    func_15147928(arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1CC440/func_1519F1C8.s")

s32 *func_1519F1C8(void *arg0, s32 arg1);

struct Sub1519F3B8 {
    s32 *unk0;
    s32 unk4;
    s32 *unk8;
    s32 unkC;
};

struct Obj1519F3B8 {
    u8 pad0[0x58];
    struct Sub1519F3B8 unk58;
};

void func_1519F3B8(struct Obj1519F3B8 *arg0) {
    struct Sub1519F3B8 *p = &arg0->unk58;
    p->unk0 = func_1519F1C8(arg0, 6);
    p->unk4 = 0;
    p->unk8 = func_1519F1C8(arg0, 7);
    p->unkC = 0;
}

struct Obj1519F400 {
    u8 pad0[0x58];
    s32 unk58;
    s32 unk5C;
    s32 unk60;
    s32 unk64;
};

void func_1519F48C();
void func_151A0928();

void func_1519F400(struct Obj1519F400 *arg0) {
    s32 *p;
    p = (s32 *)((u8 *)arg0 + 0x58);
    if (p[0] != 0) {
        func_1519F48C(p[0]);
    }
    if (p[2] != 0) {
        func_1519F48C(p[2]);
    }
    if (p[1] != 0) {
        func_151A0928(p[1]);
        func_1516972C((struct102 *)p[1]);
    }
    if (p[3] != 0) {
        func_151A0928(p[3]);
        func_1516972C((struct102 *)p[3]);
    }
}

struct Sub1519F48C {
    u8 pad0[0x58];
    s32 unk58;
    s32 unk5C;
    s32 unk60;
};

struct Ref1519F48C {
    struct Sub1519F48C *unk0;
    u8 unk4;
};

struct Obj1519F48C {
    u8 pad0[0x1E];
    u16 unk1E;
    s32 unk20;
    u8 pad24[0xC];
    u8 unk30;
    u8 pad31[0x67];
    struct Ref1519F48C *unk98;
};

void func_1519F48C(struct Obj1519F48C *arg0) {
    struct Ref1519F48C *p = arg0->unk98;
    s32 *ptr;

    if (p->unk0 != 0) {
        ptr = (s32 *)((u8 *)p->unk0 + 0x58);
        if (arg0->unk20 == 6) {
            ptr[0] = 0;
        }
        if (arg0->unk20 == 7) {
            ptr[2] = 0;
        }
        p->unk0 = 0;
    }
    arg0->unk30 = 0;
    arg0->unk1E &= ~2;
    p->unk4 |= 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1CC440/func_1519F4F0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1CC440/func_1519F7F0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1CC440/func_1519FE6C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1CC440/func_151A084C.s")

struct Obj151A0928 {
    u8 pad0[0x28];
    s32 *unk28;
    u8 unk2C;
};

void func_151A0928(struct Obj151A0928 *arg0) {
    s32 *ptr = (s32 *)((u8 *)arg0->unk28 + 0x58);
    if (arg0->unk2C == 6) {
        ptr[1] = 0;
    } else {
        ptr[3] = 0;
    }
}

struct Sub151A0950 {
    u8 pad0[0x18];
    s32 unk18;
    u8 unk1C;
};

struct Obj151A0950 {
    u8 pad0[0x98];
    struct Sub151A0950 **unk98;
};

struct Arg151A0950 {
    s32 unk0;
    u8 unk4;
};

void func_151A0950(struct Obj151A0950 *arg0, struct Arg151A0950 *arg1, u8 arg2) {
    struct Sub151A0950 *v0;
    struct Sub151A0950 **pp = arg0->unk98;
    s32 temp;
    if (arg2 == 10) {
        v0 = *pp;
        if (v0 != 0) {
            temp = v0->unk18;
            if (arg1->unk0 == temp || arg1->unk4 == v0->unk1C) {
                func_1519F48C((struct Obj1519F48C *)arg0);
            }
        }
    }
}

struct Sub151A09B4 {
    u8 pad0[0x3B];
    u8 unk3B;
};

struct Mid151A09B4 {
    u8 pad0[0x18];
    struct Sub151A09B4 *unk18;
};

struct Obj151A09B4 {
    u8 pad0[0x28];
    struct Mid151A09B4 *unk28;
};

struct Arg151A09B4 {
    struct Sub151A09B4 *unk0;
    u8 unk4;
};

void func_151A09B4(struct Obj151A09B4 *arg0, struct Arg151A09B4 *arg1, u8 arg2) {
    struct Sub151A09B4 *v0 = arg0->unk28->unk18;
    if (arg2 == 0) {
        if (v0 == arg1->unk0 || arg1->unk4 == v0->unk3B) {
            func_151A0928((struct Obj151A0928 *)arg0);
            func_1516972C((struct102 *)arg0);
        }
    }
}

struct Obj151A0A10 {
    u8 pad0[0x14];
    f32 unk14;
    u8 pad18[0x1C - 0x18];
    f32 unk1C;
    u8 pad20[0x180 - 0x20];
    f32 unk180;
    s32 unk184;
};

struct Payload151A0A10 {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    u8 unkC;
    u8 padD[0x10 - 0xD];
    f32 unk10;
};

void func_151A0A10(struct Obj151A0A10 *arg0, s32 arg1, u8 arg2, s32 arg3) {
    struct260 *temp_v0;
    struct Payload151A0A10 sp38;

    if (arg0 != NULL) {
        sp38.unk0 = arg0->unk14;
        sp38.unk8 = arg0->unk1C;
        if (D_800C35EA != 1) {
            sp38.unk4 = arg0->unk180;
            sp38.unk10 = 0.0f;
            switch (func_1510F8CC(arg0->unk184)) {
            case 10:
                sp38.unkC = 0;
                break;
            case 15:
            case 17:
                sp38.unkC = 1;
                break;
            default:
                sp38.unkC = 0;
                break;
            }
            temp_v0 = func_151491F4((s16)arg1, -1, 1, 1, 0, 0x14, (u8)arg2, arg3);
            if (temp_v0 != NULL) {
                memcpy((u8 *)temp_v0 + 0x28, &sp38, 0x14);
            }
        }
    }
}

extern f32 D_800A8D10;
extern f32 D_800BE9A4;
extern f32 func_150ADA68(void);
void func_1514C678(f32, f32, s32, f32, s32, s32, s32, s32, s32, f32, s32, s32);

struct Sub151A0AF8 {
    f32 unk0;
    f32 unk4;
    s32 unk8;
    u8 unkC;
    u8 padD[0x10 - 0xD];
    f32 unk10;
};

struct Obj151A0AF8 {
    u8 pad0[0xC];
    u8 unkC;
    u8 padD[0x28 - 0xD];
    struct Sub151A0AF8 unk28;
};

void func_151A0AF8(struct Obj151A0AF8 *arg0) {
    struct Sub151A0AF8 *p;
    arg0->unk28.unk10 += D_800A8D10 * D_800BE9A4;
    if (1.0f < arg0->unk28.unk10) {
        p = &arg0->unk28;
        do {
            func_1514C678(p->unk0, p->unk4, p->unk8,
                          func_150ADA68() * 25.0f + 15.0f,
                          0, 0xFF, 5, 4, p->unkC, 0.0f, 0, arg0->unkC);
            p->unk10 -= 1.0f;
        } while (1.0f < p->unk10);
    }
}


#pragma GLOBAL_ASM("asm/nonmatchings/game_1CC440/func_151A0C0C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1CC440/func_151A0E40.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1CC440/func_151A0F28.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1CC440/func_151A1010.s")

void func_151A11CC(f32 arg0, f32 arg1, s32 arg2, s32 arg3) {
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1CC440/func_151A11E4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1CC440/func_151A175C.s")

struct Src151A18DC {
    u8 unk0;
    u8 unk1;
    u8 pad2[0xA];
    u8 unkC;
    u8 padD[0x1B];
    s32 unk28;
    s32 unk2C;
    s32 unk30;
    f32 unk34;
    f32 unk38;
    s16 unk3C;
    s16 unk3E;
    s16 unk40;
    s16 unk42;
    s16 unk44;
};

struct Blk151A18DC {
    s32 a;
    s32 b;
    s32 c;
};

struct Dst151A18DC {
    struct Blk151A18DC unk0;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    s16 unk18;
    s16 unk1A;
    s16 unk1C;
    s16 unk1E;
    s32 pad20;
};

void func_151A18DC(struct Src151A18DC *arg0) {
    struct Dst151A18DC sp34;
    struct260 *temp_v0;

    sp34.unk0 = *(struct Blk151A18DC *)&arg0->unk28;
    sp34.unkC = arg0->unk34;
    sp34.unk10 = 0.0f;
    sp34.unk14 = arg0->unk38;
    sp34.unk18 = arg0->unk3E;
    sp34.unk1A = arg0->unk40;
    sp34.unk1C = arg0->unk42;
    sp34.unk1E = arg0->unk44;

    temp_v0 = func_151491F4(arg0->unk3C, -1, 3, 1, 0, 0x20, arg0->unkC, arg0->unk1);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &sp34, 0x20);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1CC440/func_151A1998.s")

struct Sub151A1E34 {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    s16 unkE;
    s16 unk10;
    s16 unk12;
};

struct Obj151A1E34 {
    u8 pad0[0x34];
    s16 unk34;
    s16 unk36;
    s16 unk38;
    u8 pad3A[0x3F - 0x3A];
    u8 unk3F;
    u8 pad40[0x50 - 0x40];
    struct Sub151A1E34 unk50;
};

void func_151A1E34(struct Obj151A1E34 *arg0) {
    s16 temp_v1;
    struct Sub151A1E34 *temp_v0;

    temp_v0 = &arg0->unk50;
    temp_v1 = arg0->unk38;
    if (arg0->unk50.unk4 < temp_v1) {
        arg0->unk3F = (u32)(temp_v0->unk2 - temp_v1) * (u32)temp_v0->unk0;
    }
    if (temp_v0->unkA < temp_v1) {
        arg0->unk34 = arg0->unk36 = (u32)(temp_v0->unk8 - temp_v1) * (u32)temp_v0->unk6;
    }
    if (temp_v1 < temp_v0->unkC) {
        arg0->unk3F = (u32)temp_v1 * (u32)temp_v0->unkE;
    }
    if (temp_v1 < temp_v0->unk10) {
        arg0->unk34 = arg0->unk36 = (u32)temp_v1 * (u32)temp_v0->unk12;
    }
}

struct Src151A1EE8 {
    u8 unk0;
    u8 unk1;
    u8 pad2[0xA];
    u8 unkC;
    u8 padD[0x1B];
    s32 unk28;
    s32 unk2C;
    s32 unk30;
    f32 unk34;
    f32 unk38;
    s16 unk3C;
    s16 unk3E;
    s16 unk40;
    s16 unk42;
    s16 unk44;
    s16 unk46;
    s16 unk48;
};

struct Blk3151A1EE8 {
    s32 a;
    s32 b;
    s32 c;
};

struct Dst151A1EE8 {
    struct Blk3151A1EE8 unk0;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    union {
        struct {
            s16 unk18;
            s16 unk1A;
            s16 unk1C;
            s16 unk1E;
        } s;
        f64 _align;
    } u18;
    s16 unk20;
    s16 unk22;
};

void func_151A1EE8(struct Src151A1EE8 *arg0) {
    struct Dst151A1EE8 sp38;
    struct260 *temp_v0;

    sp38.unk0 = *(struct Blk3151A1EE8 *)&arg0->unk28;
    sp38.unkC = arg0->unk34;
    sp38.unk10 = 0.0f;
    sp38.unk14 = arg0->unk38;
    sp38.u18.s.unk18 = arg0->unk3E;
    sp38.u18.s.unk1A = arg0->unk40;
    sp38.u18.s.unk1C = arg0->unk42;
    sp38.u18.s.unk1E = arg0->unk44;
    sp38.unk20 = arg0->unk46;
    sp38.unk22 = arg0->unk48;

    temp_v0 = func_151491F4(arg0->unk3C, -1, 4, 1, 0, 0x24, arg0->unkC, arg0->unk1);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &sp38, 0x24);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1CC440/func_151A1FB4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1CC440/func_151A24A8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1CC440/func_151A25E0.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1CC440/func_151A26EC.s")

struct Sub151A2960 {
    s16 unk0;
    s16 unk2;
    s16 unk4;
    s8 unk6;
};

struct Obj151A2960 {
    u8 pad0[0x1A];
    s16 unk1A;
    u8 pad1C[0x2C - 0x1C];
    u8 unk2C;
    u8 pad2D[0xB0 - 0x2D];
    struct Sub151A2960 unkB0;
};

void func_151A2960(struct Obj151A2960 *arg0, s32 arg1) {
    struct Sub151A2960 *temp_v0;

    temp_v0 = &arg0->unkB0;
    if (arg0->unk1A < temp_v0->unk0) {
        arg0->unk2C = arg0->unk1A * temp_v0->unk2;
    }
    if (D_800BE616 == 0) {
        if (-1 != temp_v0->unk4) {
            if ((-1 != temp_v0->unk6) && (temp_v0->unk4 >= arg0->unk1A)) {
                D_8008F8E0[temp_v0->unk6](arg0, temp_v0->unk4);
                temp_v0->unk4 = -1;
            }
        }
    }
    func_1513170C((s32 *)arg0, arg1);
}

void func_151A2C24(s32, s32, s32, s32, f32, f32, f32, s32, f32, f32, f32, f32, s16, s16, s16, s16, s16, s16, s8, u8, s32, s32);

void func_151A2A14(s32 a0, s16 a1, s16 a2, f32 a3, f32 p4, f32 p5, s32 p6, f32 p7, f32 p8, f32 p9, f32 p10, s16 p11, s16 p12, s16 p13, s16 p14, s16 p15, s16 p16, s8 p17, u8 p18, s32 p19) {
    func_151A2C24(a0, 0, a1, a2, a3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, p18, p19, 1);
}

void func_151A2AD4(s32 a0, s32 a1, f32 a2, f32 a3, s32 p4, f32 p5, f32 p6, f32 p7, f32 p8, s16 p9, s16 p10, s16 p11, s16 p12, s16 p13, s16 p14, s8 p15, u8 p16, s32 p17) {
    func_151A2C24(a0, a1, 0, 0, 0.0f, a2, a3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16, p17, 0);
}

void func_151A2B84(f32 *in, s32 a1, s32 a2, s32 a3, f32 t, f32 *out) {
    f32 s = 1.0f - t;
    out[0] = in[0] * s;
    out[1] = in[1] * s;
    out[2] = in[2] * s;
}

void func_151A2BD0(f32 *in, s32 a1, s32 a2, f32 a3, f32 t, f32 *out) {
    func_15143794((s16) a1, (s16) a2, (1.0f - t) * a3, out);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1CC440/func_151A2C24.s")

void func_151A2F0C(void *arg0) {
    struct Vec151A2F0C {
        f32 a;
        f32 b;
        f32 c;
    };
    struct Obj151A2F0C {
        u8 pad0[0x1];
        u8 unk1;
        u8 pad2[0xC - 0x2];
        u8 unkC;
        u8 padD[0x38 - 0xD];
        f32 unk38;
        f32 unk3C;
        struct Vec151A2F0C unk40;
        f32 unk4C;
        f32 unk50;
        f32 unk54;
        u8 pad58[0x68 - 0x58];
        s32 unk68;
    };
    struct Arg151A2F0C {
        s32 unk00;
        s32 unk04;
        struct Vec151A2F0C unk08;
        f32 unk14;
        f32 unk18;
        f32 unk1C;
        f32 unk20;
        f32 unk24;
        f32 unk28;
        s16 unk2C;
        s16 unk2E;
        s16 unk30;
        s16 unk32;
        s32 unk34;
        s32 unk38;
        s16 unk3C;
        s16 unk3E;
        s16 unk40;
        u8 unk42;
        u8 unk43;
        u8 unk44;
        u8 unk45;
        u8 unk46;
        u8 unk47;
        u8 unk48;
        u8 unk49;
        u8 unk4A;
        u8 unk4B;
        u8 unk4C;
        u8 unk4D;
        u8 unk4E;
        u8 unk4F;
        u8 unk50;
        u8 unk51;
        u8 unk52;
        u8 unk53;
        u8 unk54;
        u8 unk55;
        u8 unk56;
        u8 unk57;
        u8 unk58;
        u8 pad59[3];
        s32 unk5C;
        s32 unk60;
        s16 unk64;
        s16 unk66;
        s16 unk68;
        u8 unk6A;
        u8 pad6B;
        f32 unk6C;
        s8 unk70;
        s8 unk71;
        s8 unk72;
        s8 unk73;
    };
    struct Arg151A2F0C sp1C;
    struct Obj151A2F0C *obj;

    obj = arg0;
    sp1C.unk00 = 8;
    sp1C.unk04 = 6;
    sp1C.unk08 = obj->unk40;
    if (obj->unk68 & 0x1000) {
        sp1C.unk08.a += obj->unk4C;
        sp1C.unk08.b += obj->unk50;
        sp1C.unk08.c += obj->unk54;
    }
    sp1C.unk14 = ((obj->unk38 + obj->unk3C) * 0.5f) * D_800A8D30;
    sp1C.unk18 = ((obj->unk38 + obj->unk3C) * 0.5f) * D_800A8D34;
    sp1C.unk1C = D_800A8D38;
    sp1C.unk20 = 0.0f;
    sp1C.unk24 = 8.0f;
    sp1C.unk28 = 10.0f;
    sp1C.unk2C = 0;
    sp1C.unk2E = 0xFF;
    sp1C.unk30 = -0x40;
    sp1C.unk32 = 0x56;
    sp1C.unk34 = 3;
    sp1C.unk38 = 1;
    sp1C.unk3C = 0x11;
    sp1C.unk3E = 0x12;
    sp1C.unk40 = 1;
    sp1C.unk42 = 4;
    sp1C.unk43 = 2;
    sp1C.unk44 = 3;
    sp1C.unk45 = 0xFF;
    sp1C.unk46 = 0xC8;
    sp1C.unk47 = 0xC8;
    sp1C.unk48 = 0xFF;
    sp1C.unk49 = 0;
    sp1C.unk4A = 0x37;
    sp1C.unk4B = 0x37;
    sp1C.unk4C = 0;
    sp1C.unk4D = 0xFF;
    sp1C.unk4E = 0xFF;
    sp1C.unk4F = 0xFF;
    sp1C.unk50 = 0xFF;
    sp1C.unk51 = 0;
    sp1C.unk52 = 0;
    sp1C.unk53 = 0;
    sp1C.unk54 = 0;
    sp1C.unk55 = 0xFF;
    sp1C.unk56 = 0;
    sp1C.unk57 = 1;
    sp1C.unk58 = 0x24;
    sp1C.unk5C = 0x200005;
    sp1C.unk60 = 0x60600;
    sp1C.unk64 = 7;
    sp1C.unk66 = 0x24;
    sp1C.unk68 = 1;
    sp1C.unk6A = 0;
    sp1C.unk6C = 1.0f;
    sp1C.unk70 = -1;
    sp1C.unk71 = 0;
    sp1C.unk72 = -1;
    sp1C.unk73 = -1;

    func_15152B38(&sp1C, obj->unkC, obj->unk1);
}

typedef struct {
    /* 0x0 */ f32 a;
    /* 0x4 */ f32 b;
    /* 0x8 */ f32 c;
} Struct3W151A3150;

typedef struct Obj151A3150 {
    u8 pad0[0x1];
    u8 unk1;
    u8 pad2[0xC - 0x2];
    u8 unkC;
    u8 padD[0x38 - 0xD];
    f32 unk38;
    f32 unk3C;
    Struct3W151A3150 unk40;
    f32 unk4C;
    f32 unk50;
    f32 unk54;
    u8 pad58[0x68 - 0x58];
    s32 unk68;
} Obj151A3150;

typedef struct {
    /* 0x00 */ s32 unk00;
    /* 0x04 */ s32 unk04;
    /* 0x08 */ Struct3W151A3150 unk08;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ s16 unk2C;
    /* 0x2E */ s16 unk2E;
    /* 0x30 */ s16 unk30;
    /* 0x32 */ s16 unk32;
    /* 0x34 */ s32 unk34;
    /* 0x38 */ s32 unk38;
    /* 0x3C */ s16 unk3C;
    /* 0x3E */ s16 unk3E;
    /* 0x40 */ s16 unk40;
    /* 0x42 */ u8 unk42;
    /* 0x43 */ u8 unk43;
    /* 0x44 */ u8 unk44;
    /* 0x45 */ u8 unk45;
    /* 0x46 */ u8 unk46;
    /* 0x47 */ u8 unk47;
    /* 0x48 */ u8 unk48;
    /* 0x49 */ u8 unk49;
    /* 0x4A */ u8 unk4A;
    /* 0x4B */ u8 unk4B;
    /* 0x4C */ u8 unk4C;
    /* 0x4D */ u8 unk4D;
    /* 0x4E */ u8 unk4E;
    /* 0x4F */ u8 unk4F;
    /* 0x50 */ u8 unk50;
    /* 0x51 */ u8 unk51;
    /* 0x52 */ u8 unk52;
    /* 0x53 */ u8 unk53;
    /* 0x54 */ u8 unk54;
    /* 0x55 */ u8 unk55;
    /* 0x56 */ u8 unk56;
    /* 0x57 */ u8 unk57;
    /* 0x58 */ u8 unk58;
    /* 0x59 */ u8 pad59[3];
    /* 0x5C */ s32 unk5C;
    /* 0x60 */ s32 unk60;
    /* 0x64 */ s16 unk64;
    /* 0x66 */ s16 unk66;
    /* 0x68 */ s16 unk68;
    /* 0x6A */ u8 unk6A;
    /* 0x6B */ u8 pad6B;
    /* 0x6C */ f32 unk6C;
    /* 0x70 */ s8 unk70;
    /* 0x71 */ s8 unk71;
    /* 0x72 */ s8 unk72;
    /* 0x73 */ s8 unk73;
} Struct151A3150;

void func_151A3150(Obj151A3150 *arg0) {
    Struct151A3150 sp1C;

    sp1C.unk00 = 0xA;
    sp1C.unk04 = 0xF;
    sp1C.unk08 = arg0->unk40;
    if (arg0->unk68 & 0x1000) {
        sp1C.unk08.a += arg0->unk4C;
        sp1C.unk08.b += arg0->unk50;
        sp1C.unk08.c += arg0->unk54;
    }
    sp1C.unk14 = ((arg0->unk38 + arg0->unk3C) * 0.5f) * D_800A8D3C;
    sp1C.unk18 = ((arg0->unk38 + arg0->unk3C) * 0.5f) * D_800A8D40;
    sp1C.unk1C = D_800A8D44;
    sp1C.unk20 = 0.0f;
    sp1C.unk24 = 8.0f;
    sp1C.unk28 = 8.0f;
    sp1C.unk2C = 0;
    sp1C.unk2E = 0xFF;
    sp1C.unk30 = -0x40;
    sp1C.unk32 = 0x56;
    sp1C.unk34 = 3;
    sp1C.unk38 = 2;
    sp1C.unk3C = 0xF;
    sp1C.unk3E = 0x1E;
    sp1C.unk40 = 1;
    sp1C.unk42 = 4;
    sp1C.unk43 = 2;
    sp1C.unk44 = 3;
    sp1C.unk45 = 0xFF;
    sp1C.unk46 = 0xC8;
    sp1C.unk47 = 0xC8;
    sp1C.unk48 = 0xFF;
    sp1C.unk49 = 0;
    sp1C.unk4A = 0x37;
    sp1C.unk4B = 0x37;
    sp1C.unk4C = 0;
    sp1C.unk4D = 0xFF;
    sp1C.unk4E = 0xFF;
    sp1C.unk4F = 0xFF;
    sp1C.unk50 = 0xFF;
    sp1C.unk51 = 0;
    sp1C.unk52 = 0;
    sp1C.unk53 = 0;
    sp1C.unk54 = 0;
    sp1C.unk55 = 0xFF;
    sp1C.unk56 = 0;
    sp1C.unk57 = 1;
    sp1C.unk58 = 0x24;
    sp1C.unk5C = 0x200005;
    sp1C.unk60 = 0x60600;
    sp1C.unk64 = 0xF;
    sp1C.unk66 = 0x11;
    sp1C.unk68 = 1;
    sp1C.unk6A = 0;
    sp1C.unk6C = 1.0f;
    sp1C.unk70 = -1;
    sp1C.unk71 = 0;
    sp1C.unk72 = -1;
    sp1C.unk73 = -1;

    func_15152B38(&sp1C, arg0->unkC, arg0->unk1);
}
