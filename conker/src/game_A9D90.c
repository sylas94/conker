#include <ultra64.h>

#include "functions.h"
#include "variables.h"

extern s32 func_15084D70(s32, s32, s32, s16*, f32*, u8*, u8*, s32*, s32*, s32, s32*);
extern void func_15022190(s16, s16, s16, f32);
extern void func_1501D348(s32, s32, s32, s32, s32);
extern void func_1501C730(s32, s32, s32, s32, s32);
extern void func_1507D1D8(struct127 *);
extern void func_1509C3A0(void);


void func_1507C8E0(struct127 *arg0, s32 arg1) {
    arg0->unk31C->unk120 = (u8)2;
    arg0->unk31C->unk124 = arg1;
}

// "goto" hell
#pragma GLOBAL_ASM("asm/nonmatchings/game_A9D90/func_1507C8FC.s")

void func_1507CD0C(struct127 *arg0) {
    s32 temp_lo = ((s32)arg0 - (s32)&D_800CC2D0) / (s32)sizeof(struct127);

    arg0->unk31C->unk120 = 3;

    if (temp_lo <= D_80082FA0) {
        func_15181D70(temp_lo);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_A9D90/func_1507CD64.s")
void func_1509BFB0(s32 num, s32, s32, ...);
extern struct127 D_800CC40F[];

void func_1507D158(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    s32 temp = *(u8*)&D_800CC40F[arg0];
    func_1509BFB0(3, temp | 0x2000, arg1, arg2, arg3, arg4);
}

extern s16 D_800BE9F2;

extern void func_15082A44(void *, s32, s32, s32, s32);
extern void func_150054C4(struct108 *, s32, s16, s32);
extern void func_15181DC8(s32);
extern void func_1517EE40(s32, s32, s32, s32, s32, s32);
extern void func_15085430(struct127 *, s32, s32);
extern void func_15088D58(struct127 *);

// struct258 in structs.h stops short of the real 0x30-byte spawn slot.
typedef struct {
    u8  pad0[0x4];
    u8  unk4;
    u8  pad5[0x2B];
} struct258b;

// struct126 in structs.h stops at 0x1AA and pads over 0x11B.
typedef struct {
    u8  pad0[0x75];
    u8  unk75;
    u8  pad76[0xA5];
    u8  unk11B;
    u8  pad11C[0x4];
    u8  unk120;
    u8  pad121;
    u8  unk122;
    u8  pad123;
    s16 unk124;
    u8  pad126[0x84];
    s16 unk1AA;
    u8  pad1AC[0x3];
    s8  unk1AF;
    s8  unk1B0;
    u8  unk1B1;
} struct126b;

void func_1507D1D8(struct127 *arg0) {
    s32 index;
    s32 sp40;
    s8  sp3F;
    s8  sp3E;
    s8  sp3D;
    s8  sp3C;
    s32 sp38;
    s32 temp;

    sp40 = ((struct126b *)arg0->unk31C)->unk1AA;
    sp3E = ((struct126b *)arg0->unk31C)->unk1B0;
    sp3D = *(s8 *)((s32)arg0 + 0x328);
    sp3C = ((struct126b *)arg0->unk31C)->unk1AF;
    if (D_800BE616 != 0) {
        sp3F = ((struct126b *)arg0->unk31C)->unk11B;
    } else {
        sp3F = -1;
    }

    if (D_800BE9F0 == 0x2B) {
        index = ((s32)arg0 - (s32)&D_800CC2D0) / (s32)sizeof(struct127);
        temp = func_150859AC(index, 1);
        if ((temp >= 0x11) && (temp < 0x21)) {
            sp38 = (func_150ADA20() & 0xF) + 0x11;
            func_15085710(index, 0, sp38);
            if (sp38 < 0x1D) {
                ((struct258b *)((s32)D_800D20FC + (index * 0x30)))->unk4 = 0x9C;
            } else {
                ((struct258b *)((s32)D_800D20FC + (index * 0x30)))->unk4 = 0x9D;
            }
        }
    }

    index = ((s32)arg0 - (s32)&D_800CC2D0) / (s32)sizeof(struct127);
    func_15060F28(arg0, 0);
    D_800D18A8 = 1;
    func_15082A44((struct258b *)((index * 0x30) + (s32)D_800D20FC), index, 0, 0, 0);
    ((struct126b *)arg0->unk31C)->unk1B0 = sp3E;
    ((struct126b *)arg0->unk31C)->unk1AF = sp3C;
    *(s8 *)((s32)arg0 + 0x328) = sp3D;

    if (index <= D_80082FA0) {
        func_150054C4(&D_800DBFF0[index], index, D_800BE9F2, sp3F);
        func_15181DC8(index);
        func_1517EE40(0, 0, 0, 0, 1, index);
        func_1517EE40(0, 0, 0, 0x1E, 0, index);
    } else {
        func_15085430(arg0, sp3F, 0);
    }

    D_800D18A8 = 0;
    ((struct126b *)arg0->unk31C)->unk120 = 0;
    ((struct126b *)arg0->unk31C)->unk122 = 0;
    ((struct126b *)arg0->unk31C)->unk124 = 0;
    ((struct126b *)arg0->unk31C)->unk1AA = sp40;
    arg0->health = D_8008726C;
    arg0->unk22C |= 0x100;
    ((struct126b *)arg0->unk31C)->unk75 = 0;
    arg0->unk20F = 0xFF;
    *(u8 *)((s32)arg0 + 0x210) = 0xFF;
    arg0->unk211 = 0xFF;
    arg0->unk232 = 1;
    arg0->unk218 = NULL;
    ((struct126b *)arg0->unk31C)->unk11B = sp3F;

    if (D_800BE616 != 0) {
        ((struct126b *)arg0->unk31C)->unk1B1 = arg0->immune = 0x96;
        if (D_800BE9F0 == 0x33) {
            func_1507D158(index, 0x78, 0, 0, 0);
            func_15088D58(arg0);
        }
    }
}

void func_1507D4F8(s32 arg0) {
    struct127 *obj;
    struct126 *state;

    obj = &D_800CC2D0[arg0];
    if ((D_8008FDBC & 1) == 0) {
        func_15085710(arg0, 4, 1);
    }

    if (func_150859AC(arg0, 3) != 0) {
        func_15085710(arg0, 5, D_8008726C);
        obj->unkB2 = 0;

        if (D_800BE616 != 0) {
            if (*(s8 *)&D_800E0C20 == 0) {
                func_1507D1D8(obj);
                return;
            }

            obj->unk31C->unk120 = 0xA;
            return;
        }

        D_800D18A8 = 1;
        if (((D_800D2E4C->unk19 & 4) == 0) && (D_8008FDA8 >= 0)) {
            func_1501C730(1, 0x22, 0, 0, 0);
            return;
        }

        func_1501C730(2, *(s8 *)&D_800BE3DF, D_800BE3E0, 0, 0);
        return;
    }

    if (D_800BE616 == 0) {
        D_800D2E43 = 1;
        func_1509C3A0();
        D_800D18A8 = 1;
        func_15085710(arg0, 5, D_8008726C);
        func_15085710(arg0, 2, D_80087260);
        func_1501C730(1, 0x18, 0, 0, 0);
    } else {
        D_800D18A0 = D_800D18A0 | (1 << arg0);
    }

    state = obj->unk31C;
    if (state->unk84 == 0) {
        *(s8 *)&D_8008FD94 -= 1;
        state = obj->unk31C;
    }
    state->unk120 = 0xA;
    D_800BE618--;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_A9D90/func_1507D754.s")

void func_1507DB44(s32 arg0, s32 arg1) {
    func_1503DE70(arg0, arg1, -1);
}

void func_1507DB64(void) {
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_A9D90/func_1507DB6C.s")

void func_1507DE4C(struct127 *arg0) {

    if (arg0->interaction_state == 1) {
        func_150836CC(arg0, 0x44);
        func_150836CC(arg0, 0x23);
        arg0->unk9C |= 0xF000;
        func_150836CC(arg0, 0x44);
        func_150836CC(arg0, 0x23);
        return;
    }

    switch(arg0->id) {
        case 0x9F:
        case 0xa0:
            arg0->unk9C |= 0xF000;
            break;
        case 0x5A:
        case 0x74:
        case 0x7A:
            arg0->unk9C |= 0xFF8;
            break;
    }
}


#pragma GLOBAL_ASM("asm/nonmatchings/game_A9D90/func_1507DF10.s")
void func_1507DFE4(s32 arg0, s32 arg1) {
    s32 temp;
    s16 sp5C[3];
    f32 sp50[3];
    u8 sp4F;
    u8 sp4E;
    s32 sp48;
    s32 sp44;
    f32 temp_f0;
    s32 sp3C;
    s32 sp38;

    if (D_800C35EA != 1) {
        func_15084D70(0, arg0, 1, sp5C, sp50, &sp4F, &sp4E, &sp44, &sp48, 1, &sp38);
        temp_f0 = ((f32)(sp4E - 0x40) * 1.40625f) + 180.0f;
        if (sp38 == 0) {
            sp3C = 1;
        } else if (sp38 == 1) {
            sp3C = 3;
        } else {
            return;
        }
        func_15022190(sp5C[0], sp5C[1], sp5C[2], temp_f0);
        temp = D_800BE9F0;
        D_800BE9F0 = 0x25;
        D_800C3671 = 1;
        func_1501D348(0x25, sp3C, 0, 0, 0);
        D_800C3670 = 1;
        D_800BE9F0 = temp;
    }
}
extern s32 func_15084D70(s32, s32, s32, s16*, f32*, u8*, u8*, s32*, s32*, s32, s32*);


s32 func_1507E114(s32 arg0) {
    s32 sp5C;
    s16 sp54[3];
    f32 sp48[3];
    s32 sp44;
    u8 sp43;
    u8 sp42;
    s32 sp3C;
    s32 temp;

    if (D_800D18A8 == 0) {
        return 0;
    }
    temp = (s32)D_800BE9F4;
    if (temp == 0x22 || temp == 0x18) {
        return 0;
    }
    *(s32*)&D_800BE9F4 = (s8)D_800BE3DF;
    func_15084D70(0, (u8)D_800BE3E0, 1, sp54, sp48, &sp43, &sp42, &sp44, &sp3C, 1, &sp5C);
    return sp5C + 1;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_A9D90/func_1507E1D0.s")
