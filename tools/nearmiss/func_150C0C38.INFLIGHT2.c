/* func_150C0C38 (game_EDE60, 1376 bytes) -- IN-FLIGHT, NON-MATCHING, UNVERIFIED (attempt 2).
 *
 * Rescued at the end of wave 62. An agent was terminated by a session limit mid-edit and
 * had re-written this over an earlier revert, leaving the pragma removed and the C live.
 * Together with the other rescued TU it put 1272 wrong bytes into the linked image.
 *
 * NOT scored, NOT verified. Before reusing: inventory-check against the real TU (every
 * func_ definition AND every #pragma name must be present), re-score, then run the full
 * ROM gate. Kept only so the modelling work survives.
 */
#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern void *func_15167A68(s32, s32, s32, s32, s32, s32);

struct sub150C0AC0 {
    s32 unk0;
    s16 unk4;
    s16 unk6;
};

struct s150C0AC0_arg {
    s32 unk0;
    s32 unk4;
    s32 unk8;
    s32 unkC;
    s32 unk10;
    s16 unk14;
    s16 unk16;
    u8 unk18;
    u8 unk19;
    u8 unk1A;
    u8 unk1B;
};

struct s150C0AC0 {
    u8 pad0[0x10];
    s32 unk10;
    s32 unk14;
    struct s150C0AC0_arg unk18;
    f32 unk34;
    f32 unk38;
    f32 unk3C;
    struct sub150C0AC0 *unk40;
    s16 unk44;
    s16 unk46;
};


void func_150C09B0(s32 arg0, s32 arg1, s32 arg2) {
    func_15169850(arg1, (u8)arg2, arg0 + 0x20, arg0 + 0x24, arg0);
}

extern void func_150C0A48(struct102 *);

void func_150C09F0(struct102 *arg0) {
    func_150C0A48(arg0);
    func_15169804(arg0);
}

extern void func_15169824(struct102 *);

void func_150C0A1C(struct102 *arg0) {
    func_150C0A48(arg0);
    func_15169824(arg0);
}

struct sub150C0A48 {
    struct102 *unk0;
    s16        unk4;
};

struct s150C0A48 {
    u8 pad0[0x40];
    struct sub150C0A48 *unk40;
    s16 unk44;
};

void func_150C0A48(struct102 *arg0x) {
    struct s150C0A48 *arg0 = (struct s150C0A48 *)arg0x;
    s16 i;

    i = arg0->unk44;
    while (i != -1) {
        func_1516972C(arg0->unk40[i].unk0);
        i = arg0->unk40[i].unk4;
    }
}

struct s150C0AC0 *func_150C0AC0(struct s150C0AC0_arg *arg0, s32 arg1, s32 arg2) {
    struct s150C0AC0 *ret;
    s32 size;
    s16 i;
    s32 *ptr;

    size = (arg0->unk14 * 8) + 0x48;
    if ((arg0->unk18 & 2) == 0) {
        ptr = (s32 *)arg0->unk8;
        if (ptr == NULL) {
            return NULL;
        }
        if (*ptr == 0) {
            return NULL;
        }
    }

    ret = func_15167A68(0x25, arg2, size, 1, (u8)arg1, 1);
    if (ret == NULL) {
        return NULL;
    }

    memcpy(&ret->unk18, arg0, 0x1C);
    ret->unk40 = (struct sub150C0AC0 *)((u8 *)ret + 0x48);
    if (arg0->unk18 & 2) {
        ptr = (s32 *)ret->unk18.unk0;
        ret->unk34 = *(f32 *)((u8 *)ptr + 0);
        ret->unk38 = *(f32 *)((u8 *)ptr + 8);
    } else {
        ptr = (s32 *)ret->unk18.unk8;
        ret->unk34 = *(f32 *)((u8 *)ptr + 0x14);
        ret->unk38 = *(f32 *)((u8 *)ptr + 0x1C);
    }
    ret->unk3C = 0.0f;
    ret->unk44 = -1;
    ret->unk46 = 0;
    for (i = 0; i < arg0->unk14 - 1; i++) {
        ret->unk40[i].unk4 = i + 1;
    }
    ret->unk40[arg0->unk14 - 1].unk4 = -1;
    ret->unk10 = 1;
    ret->unk14 = 0;
    return ret;
}

struct Vec3f150C0C38 {
    f32 x;
    f32 y;
    f32 z;
};

struct Prt150C0C38 {
    u8 pad0[0x40];
    struct Vec3f150C0C38 unk40;
};

struct Node150C0C38 {
    struct Prt150C0C38 *unk0;
    s16 unk4;
};

struct Src150C0C38 {
    s32 unk0;
    u8 pad4[0x10];
    f32 unk14;
    u8 pad18[4];
    f32 unk1C;
    u8 pad20[0x1B];
    u8 unk3B;
    f32 unk3C;
    u8 pad40[0x44];
    u16 unk84;
    u8 pad86[0xFA];
    f32 unk180;
};

struct Main150C0C38 {
    u8 pad0[1];
    u8 unk1;
    u8 pad2[0xA];
    u8 unkC;
    u8 padD[0xB];
    struct Vec3f150C0C38 *unk18;
    u8 pad1C[4];
    struct Src150C0C38 *unk20;
    u8 unk24;
    u8 pad25[3];
    f32 unk28;
    u8 pad2C[2];
    s16 unk2E;
    u8 unk30;
    u8 pad31[3];
    f32 unk34;
    f32 unk38;
    f32 unk3C;
    struct Node150C0C38 *unk40;
    s16 unk44;
    s16 unk46;
};

struct Spawn150C0C38 {
    s32 unk00;
    s32 unk04;
    u16 unk08;
    s16 unk0A;
    s32 unk0C;
    s32 unk10;
    u8 unk14;
    u8 unk15;
    u8 unk16;
    u8 unk17;
    u8 unk18;
    u8 unk19;
    u8 unk1A;
    u8 unk1B;
    u8 unk1C;
    u8 unk1D;
    s16 unk1E;
    s16 unk20;
    s16 unk22;
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    struct Vec3f150C0C38 unk30;
    f32 unk3C;
    f32 unk40;
    f32 unk44;
    f32 unk48;
    f32 unk4C;
    f32 unk50;
    f32 unk54;
    s32 unk58;
    u8 pad5C[4];
    u8 unk60;
    u8 unk61;
    s8 unk62;
    s8 unk63;
    s8 unk64;
    s8 unk65;
    u8 pad66[0xE];
};

struct Local150C0C38 {
    struct Vec3f150C0C38 unk0;
    u8 unkC;
    u8 unkD;
    u8 unkE;
    u8 unkF;
    struct Main150C0C38 *unk10;
};

extern void *func_15130280(void *, u8, s32, s32, u8, s32);
extern f32 D_800A01C0;

void func_150C0C38(struct Main150C0C38 *arg0) {
    struct Local150C0C38 loc;
    struct Spawn150C0C38 spawn;
    struct Main150C0C38 *self2;
    s32 doIt;
    s16 i;
    s16 idx;
    u8 rnd;
    s32 bitA;
    s32 bitB;
    f32 mag;
    f32 sinA;
    f32 sinB;

    loc.unk10 = arg0;
    loc.unkF = 0;
    if ((arg0->unk30 & 2) == 0) {
        if (arg0->unk20->unk0 == 0) {
            loc.unkF = 1;
        }
        if (arg0->unk20->unk3B != arg0->unk24) {
            loc.unkF = 1;
        }
        loc.unk0.x = arg0->unk20->unk14;
        loc.unk0.y = arg0->unk20->unk180;
        loc.unk0.z = arg0->unk20->unk1C;
    } else {
        memcpy(&loc.unk0, arg0->unk18, 0xC);
        loc.unk0.y -= 65.0f;
    }

    if (loc.unkF == 0) {
        doIt = 1;
        i = arg0->unk44;
        while (i != -1) {
            arg0->unk40[i].unk0->unk40 = loc.unk0;
            i = arg0->unk40[i].unk4;
        }
        if (arg0->unk30 & 4) {
            if ((arg0->unk20->unk84 != 0x1D) && (arg0->unk20->unk84 != 0x1E)) {
                doIt = 0;
            }
        }
        if (arg0->unk20->unk3C < 3.0f) {
            doIt = 0;
        }
        if (((loc.unk0.x != arg0->unk34) || (loc.unk0.z != arg0->unk38)) && doIt) {
            arg0->unk3C += arg0->unk28 * D_800BE9A4;
            if (arg0->unk3C > 1.0f) {
                spawn.unk1D = 0x6C;
                spawn.unk08 = 0x5103;
                spawn.unk00 = 0x200005;
                spawn.unk04 = 0x1F0600;
                spawn.unk0C = 0;
                spawn.unk10 = 0;
                spawn.unk17 = 0xFF;
                spawn.unk1C = 0xFF;
                spawn.unk48 = 0.0f;
                spawn.unk4C = 0.0f;
                spawn.unk50 = 0.0f;
                spawn.unk54 = 0.0f;
                spawn.unk1E = 0x1E;
                spawn.unk20 = 8;
                spawn.unk58 = 0x80DE01;
                spawn.unk60 = 8;
                spawn.unk61 = 6;
                spawn.unk62 = -1;
                spawn.unk63 = 0;
                spawn.unk64 = -1;
                spawn.unk65 = 0;
                self2 = arg0;
                while ((arg0->unk3C > 1.0f) && (loc.unk10->unk46 != -1)) {
                    idx = arg0->unk46;
                    rnd = func_150ADA20();
                    sinA = func_151423D8((u8)(rnd - 0x40));
                    sinB = func_151423D8((u8)rnd);
                    mag = (func_150ADA68() * 33.0f) + 40.0f;
                    spawn.unk18 = 0x52;
                    spawn.unk19 = 0x6B;
                    spawn.unk1A = 0x97;
                    spawn.unk14 = 0x87;
                    spawn.unk15 = 0x6B;
                    spawn.unk16 = 0x97;
                    spawn.unk1B = (func_150ADA20() % 0x79U) + 0x50;
                    spawn.unk28 = spawn.unk2C = (func_150ADA68() * 17.0f) + 67.0f;
                    spawn.unk30 = loc.unk0;
                    spawn.unk3C = mag * sinA;
                    spawn.unk40 = 0.0f;
                    spawn.unk44 = mag * sinB;
                    spawn.unk58 &= ~0xC0;
                    bitA = (func_150ADA20() & 1) ? 0x80 : 0;
                    bitB = (func_150ADA20() & 1) ? 0x40 : 0;
                    spawn.unk58 |= bitB | bitA;
                    spawn.unk0A = spawn.unk22 = (func_150ADA20() % 0x16U) + 0x46;
                    spawn.unk24 = D_800A01C0;
                    arg0->unk40[idx].unk0 = func_15130280(&spawn, 1, 0, 4, arg0->unkC, arg0->unk1);
                    if (arg0->unk40[idx].unk0 != NULL) {
                        memcpy((u8 *)arg0->unk40[idx].unk0 + 0xA8, &self2, 4);
                        arg0->unk46 = arg0->unk40[idx].unk4;
                        arg0->unk40[idx].unk4 = arg0->unk44;
                        arg0->unk44 = idx;
                    }
                    arg0->unk3C -= 1.0f;
                }
                while (arg0->unk3C > 1.0f) {
                    arg0->unk3C -= 1.0f;
                }
            }
        }
        arg0->unk34 = loc.unk0.x;
        arg0->unk38 = loc.unk0.z;
    }
    if (arg0->unk30 & 1) {
        arg0->unk2E -= D_800BE9E4;
        if (arg0->unk2E < 0) {
            loc.unkF = 1;
        }
    }
    if (loc.unkF != 0) {
        func_1516972C((struct102 *)arg0);
    }
}

struct s150C1198 {
    u8 pad0[0xA8];
    struct s150C1198List *unkA8;
};

struct s150C1198List {
    u8 pad0[0x40];
    struct sub150C0A48 *unk40;
    s16 unk44;
    s16 unk46;
};

void func_150C1198(struct s150C1198 *arg0) {
    struct s150C1198List *temp;
    s32 found;
    s16 prev;
    s16 idx;

    temp = arg0->unkA8;
    found = 0;
    prev = -1;
    idx = temp->unk44;
    while ((idx != -1) && (found == 0)) {
        if ((struct102 *)arg0 == temp->unk40[idx].unk0) {
            found = 1;
        } else {
            prev = idx;
            idx = temp->unk40[idx].unk4;
        }
    }

    if (found) {
        if (idx == temp->unk44) {
            temp->unk44 = temp->unk40[idx].unk4;
        } else {
            temp->unk40[prev].unk4 = temp->unk40[idx].unk4;
        }
        temp->unk40[idx].unk4 = temp->unk46;
        temp->unk46 = idx;
    }
}
