#include <ultra64.h>
#include "functions.h"
#include "variables.h"

typedef struct {
    s32 unk0;
    s32 unk4;
    u8 unk8;
    u8 unk9;
    u16 unkA;
} Elem15024130;

typedef struct {
    u16 unk0;
    u8 unk2;
    u8 pad3[5];
} Elem1502A8A0;

extern Elem15024130 *D_800C3D50;
extern u8 D_800C35E8[];
extern Elem1502A8A0 *D_800C35F0[];

extern struct131 *func_151149AC(s32);
extern s32 func_1502460C(s32, s32, s32, s32, s32, struct127 *, struct131 *, f32 *, s32);
extern s32 func_150265CC(s32, s32, s32, s32, s32, struct127 *, struct131 *, f32 *, s32);
extern s32 func_15029BB8(s32, s32, s32, s32, s32, struct127 *, struct131 *, f32 *, s32, s32);
extern void func_1502A8A0(s32, s32, s32, s32, s32);


void func_150238D0(void) {
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_50D80/func_150238D8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_50D80/func_15023BB0.s")

typedef struct {
    s8 unk0;
    u8 unk1;
    s16 unk2;
    s8 unk4;
    s8 unk5;
    s16 unk6;
} Elem15023DE0;

extern Elem15023DE0 *D_800C3688[][30];
extern u16 *D_800C35D8[];
extern s32 D_800C35B0[];
extern s32 D_800C3640[];

void func_15023DE0(Elem15023DE0 **arg0, Elem15023DE0 **arg1, s32 *arg2, s32 *arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, s32 arg8, s32 arg9, s32 arg10, s32 arg11) {
    Elem15023DE0 *p;
    s32 time;
    s32 curTime;

    if (arg0 != NULL) {
        *arg0 = NULL;
    }
    *arg1 = NULL;
    if (arg2 != NULL) {
        *arg2 = 0;
    }
    *arg3 = D_800C3640[arg11];

    if (D_800C3688[arg11][arg4] == NULL) {
        return;
    }

    p = D_800C3688[arg11][arg4] + 4;
    time = D_800C3688[arg11][arg4]->unk2;
    while ((u32) (p - D_800C3688[arg11][arg4]) < D_800C35D8[arg11][arg4]) {
        if ((p->unk1 == 0) && (p->unk0 == 0)) {
            time = p->unk2;
        } else {
            if (time <= arg10) {
                if ((arg5 == p->unk0) && ((arg6 == 0) || ((arg6 == 1) && (arg7 == p->unk2))) && ((arg8 == 0) || ((arg8 == 1) && (arg9 == p->unk4)))) {
                    if (arg0 != NULL) {
                        *arg0 = p;
                    }
                    if (arg2 != NULL) {
                        *arg2 = time;
                    }
                }
            }
            if (time > arg10) {
                if ((arg5 == p->unk0) && ((arg6 == 0) || ((arg6 == 1) && (arg7 == p->unk2))) && ((arg8 == 0) || ((arg8 == 1) && (arg9 == p->unk4)))) {
                    *arg1 = p;
                    *arg3 = time;
                    return;
                }
            }
            while (p->unk1 == 0) {
                if (p->unk0 == 0) {
                    time = p->unk2;
                    break;
                }
                p++;
                if ((u32) (p - D_800C3688[arg11][arg4]) >= D_800C35D8[arg11][arg4]) {
                    break;
                }
                curTime = D_800C35B0[arg11];
                if (time <= curTime) {
                    if ((arg5 == p->unk0) && ((arg6 == 0) || ((arg6 == 1) && (arg7 == p->unk2))) && ((arg8 == 0) || ((arg8 == 1) && (arg9 == p->unk4)))) {
                        if (arg0 != NULL) {
                            *arg0 = p;
                        }
                        if (arg2 != NULL) {
                            *arg2 = time;
                        }
                        continue;
                    }
                }
                if (time > curTime) {
                    if ((arg5 == p->unk0) && ((arg6 == 0) || ((arg6 == 1) && (arg7 == p->unk2))) && ((arg8 == 0) || ((arg8 == 1) && (arg9 == p->unk4)))) {
                        *arg1 = p;
                        *arg3 = time;
                        return;
                    }
                }
            }
            time += p->unk1;
        }
        p++;
    }
}

void func_15024130(s32 arg0, s32 arg1) {
    s32 i;
    s32 off;
    Elem15024130 *e;

    i = 0;
    if (arg0 > 0) {
        off = 0; do {
            e = (Elem15024130 *)((u8 *)D_800C3D50 + off);
            func_1502A8A0(e->unk0, e->unk8, e->unkA, e->unk4, arg1);
            i++;
            off += 0xC;
        } while (i != arg0);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_50D80/func_150241B4.s")

extern s32 D_800C35B8[];
extern u8 D_800C35C0[];
extern u8 D_800C363A[];
extern u8 D_800C3C8C;
extern u16 D_800C3C9A;

extern void func_150241B4(Elem15024130 *, s32 *, Elem15023DE0 *, s32, s32, s32, s32);

void func_150242F8(s32 arg0, s32 arg1) {
    s32 i;
    s32 time;
    Elem15023DE0 *p;
    s32 queued;

    if (D_800C3C8C == 2) {
        return;
    }
    if ((&D_800C35EA)[arg1] != 1) {
        return;
    }
    if (D_800C3C9A == 0) {
        return;
    }

    D_800C3638 = 0;
    queued = 0;
    for (i = 0; i < D_800C363A[arg1]; i++) {
        if (D_800C3688[arg1][i] == NULL) {
            continue;
        }
        if (D_800C35B8[arg1] == D_800C35B0[arg1]) {
            continue;
        }
        p = D_800C3688[arg1][i] + 4;
        time = D_800C3688[arg1][i]->unk2;
        while ((u32) (p - D_800C3688[arg1][i]) < D_800C35D8[arg1][i]) {
            if ((p->unk1 == 0) && (p->unk0 == 0)) {
                time = p->unk2;
            } else {
                if (time <= D_800C35B0[arg1]) {
                    if (time > D_800C35B8[arg1]) {
                        for (;;) {
                            if ((u32) (p - D_800C3688[arg1][i]) >= D_800C35D8[arg1][i]) {
                                break;
                            }
                            if (((arg0 == 0) && (p->unk0 != 0x11)) || ((arg0 == 1) && (p->unk0 == 0x11))) {
                                func_150241B4(D_800C3D50, &queued, p, i, p - D_800C3688[arg1][i], time, arg1);
                            }
                            if ((p->unk1 != 0) || ((p->unk1 == 0) && (p->unk0 == 0))) {
                                break;
                            }
                            p++;
                        }
                    }
                }
                if (time > D_800C35B0[arg1]) {
                    break;
                }
                while (p->unk1 == 0) {
                    if (p->unk0 == 0) {
                        time = p->unk2;
                        break;
                    }
                    p++;
                    if ((u32) (p - D_800C3688[arg1][i]) >= D_800C35D8[arg1][i]) {
                        break;
                    }
                }
                time += p->unk1;
            }
            p++;
        }
    }
    func_15024130(queued, arg1);
    D_800C3638 = 1;
    if (arg0 == 0) {
        D_800C35C0[arg1] = 1;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_50D80/func_1502460C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_50D80/func_150265CC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_50D80/func_15029BB8.s")

void func_1502A8A0(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
    struct127 *obj;
    struct131 *actor;
    f32 *pos;
    Elem1502A8A0 *elem;
    s32 flags;

    obj = NULL;
    actor = NULL;
    pos = NULL;
    flags = D_800C35E8[arg4];
    elem = &D_800C35F0[arg4][arg1];
    if (elem->unk0 == 2) {
        obj = func_15083E90(elem->unk2);
        if (obj == NULL) {
            return;
        }
        pos = &obj->x_position;
    } else if (elem->unk0 == 3) {
        actor = func_151149AC(elem->unk2);
        if (actor == NULL) {
            return;
        }
    }
    if (pos == NULL) {
        pos = &(&D_800C3958)[arg4][arg1].unk0;
    }
    if (D_800C3C88 != 2) {
        if (func_1502460C(arg0, arg1, arg2, arg3, arg4, obj, actor, pos, flags)) {
            return;
        }
        if (func_150265CC(arg0, arg1, arg2, arg3, arg4, obj, actor, pos, flags)) {
            return;
        }
        if (func_15029BB8(arg0, arg1, arg2, arg3, arg4, obj, actor, pos, flags, 0)) {
            return;
        }
    } else {
        if (func_1502460C(arg0, arg1, arg2, arg3, arg4, obj, actor, pos, flags)) {
            return;
        }
        func_15029BB8(arg0, arg1, arg2, arg3, arg4, obj, actor, pos, flags, 1);
    }
}
