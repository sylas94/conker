#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern void *allocate_memory();
extern void func_10004074();
extern void func_15188A58();
extern s32 func_1502DB20();

typedef struct Node1518894C {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
    u8 unk4;
    char pad5[1];
    s16 unk6;
    void *unk8;
    struct Node1518894C *unkC;
    s32 unk10;
} Node1518894C;

extern Node1518894C *D_800DF7CC;

typedef struct Struct15188810Arg {
    char pad0[4];
    u8 unk4;
} Struct15188810Arg;

typedef struct Node15188810 {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
    u8 unk4;
    char pad5[1];
    s16 unk6;
    void *unk8;
    struct Node15188810 *unkC;
    Struct15188810Arg *unk10;
    s32 unk14;
} Node15188810;

void func_15188810(Struct15188810Arg *arg0, s32 arg1, s32 arg2) {
    Node15188810 *node;
    s32 size[5];
    void *mem;

    node = (Node15188810 *)D_800DF7C8[0];
    while (node != 0) {
        if (arg0 == node->unk10) {
            if (node->unk6 < arg1) {
                node->unk6 = arg1;
            }
            node->unk4 = arg2;
            return;
        }
        node = node->unkC;
    }

    node = allocate_memory(0x18, 1, 0, 0);
    if (node != 0) {
        s32 count;

        count = func_1502DB20(arg0->unk4);
        if (count == 0) {
            func_10004074(node);
            return;
        }

        size[0] = (count * 3) << 7;
        mem = allocate_memory(size[0], 1, 1, 1);
        if (mem == 0) {
            func_10004074(node);
            return;
        }

        node->unk0 = 0;
        node->unk1 = 3;
        node->unk2 = 0;
        node->unk3 = 0x14;
        node->unk4 = arg2;
        node->unk6 = arg1;
        node->unk8 = mem;
        node->unk10 = arg0;
        node->unk14 = 0;
        bzero(mem, size[0]);
        func_15188A58(node, D_800DF7C8);
    }
}

void func_1518894C(s32 arg0, s32 arg1, s32 arg2) {
    Node1518894C *node;
    void *mem;

    node = D_800DF7CC;
    while (node != 0) {
        if (arg0 == node->unk10) {
            if (node->unk6 < arg1) {
                node->unk6 = arg1;
            }
            node->unk4 = arg2;
            return;
        }
        node = node->unkC;
    }

    node = allocate_memory(0x14, 1, 0, 0);
    if (node != 0) {
        mem = allocate_memory(0x180, 1, 1, 0);
        if (mem == 0) {
            func_10004074(node);
            return;
        }

        node->unk0 = 1;
        node->unk1 = 3;
        node->unk2 = 0;
        node->unk3 = 0x14;
        node->unk4 = arg2;
        node->unk6 = arg1;
        node->unk8 = mem;
        node->unk10 = arg0;
        bzero(mem, 0x180);
        func_15188A58(node, &D_800DF7CC);
    }
}

typedef struct Node15188A58 {
    char pad0[12];
    struct Node15188A58 *unkC;
} Node15188A58;

void func_15188A58(Node15188A58 *arg0, Node15188A58 **arg1) {
    Node15188A58 *node;

    arg0->unkC = 0;
    if (*arg1 != 0) {
        node = *arg1;
        while (node->unkC != 0) {
            node = node->unkC;
        }
        node->unkC = arg0;
    } else {
        *arg1 = arg0;
    }
}

typedef struct Node15188A9C {
    char pad0[6];
    s16 unk6;
    char pad8[4];
    struct Node15188A9C *unkC;
    s32 unk10;
} Node15188A9C;

void func_15188A9C(s32 arg0) {
    Node15188A9C *node;

    node = (Node15188A9C *)D_800DF7C8[0];
    while (node != 0) {
        if (arg0 == node->unk10) {
            node->unk6 = 0;
        }
        node = node->unkC;
    }
}

typedef struct Node15188AD0 {
    char pad0[8];
    s32 *unk8;
    struct Node15188AD0 *unkC;
    s32 unk10;
} Node15188AD0;

extern void func_10004074(Node15188AD0 *arg0);

void func_15188AD0(s32 arg0) {
    Node15188AD0 *node;
    Node15188AD0 *prev;
    Node15188AD0 *next;

    prev = 0;
    node = (Node15188AD0 *)D_800DF7C8[0];
    while (node != 0) {
        next = node->unkC;
        if (arg0 == node->unk10) {
            if (prev == 0) {
                D_800DF7C8[0] = (s32)next;
            } else {
                prev->unkC = next;
            }
            func_100043B4(node->unk8, 2);
            func_10004074(node);
        } else {
            prev = node;
        }
        node = next;
    }
}

typedef struct Node15188B74 {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
    char pad4[2];
    s16 unk6;
    char pad8[4];
    struct Node15188B74 *unkC;
} Node15188B74;

extern void (*D_8008D580[])(Node15188B74 *);
extern void (*D_8008D588[])(Node15188B74 *);

void func_15188B74(s32 idx) {
    Node15188B74 *node;
    Node15188B74 *prev;
    Node15188B74 *next;
    s32 *head;
    void (**funcs0)(Node15188B74 *);
    void (**funcs1)(Node15188B74 *);
    s32 countdown;
    s32 fade;
    s32 maxFade;

    head = &D_800DF7C8[idx];
    node = (Node15188B74 *)*head;
    funcs1 = D_8008D588;
    prev = 0;
    if (node != 0) {
        funcs0 = D_8008D580;
        maxFade = 0xFF;
        do {
            countdown = node->unk6;
            next = node->unkC;
            if (countdown != 0) {
                node->unk6 = countdown - D_800BE9E4;
                countdown = node->unk6;
            }
            if (countdown < 0) {
                node->unk6 = 0;
            }
            funcs0[node->unk0](node);

            fade = node->unk3;
            if (node->unk6 != 0) {
                if (fade != maxFade) {
                    fade += D_800BE9E4 << 4;
                    if (fade >= 0x100) {
                        fade = maxFade;
                    }
                    node->unk3 = fade;
                }
                prev = node;
            } else if (fade != 0) {
                fade -= D_800BE9E4 << 3;
                if (fade < 0) {
                    fade = 0;
                }
                if (fade == 0) {
                    if (prev == 0) {
                        *head = (s32)next;
                    } else {
                        prev->unkC = next;
                    }
                    funcs1[node->unk0](node);
                    func_10004074((Node15188AD0 *)node);
                } else {
                    node->unk3 = fade;
                    prev = node;
                }
            }
            node = next;
        } while (node != 0);
    }
}

typedef struct Node15188D00 {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
    char pad4[4];
    s32 unk8;
    struct Node15188D00 *unkC;
    s32 unk10;
    s32 unk14;
} Node15188D00;

extern Mtx D_80089470;
extern Gfx *(*D_8008D590[])(Gfx *, Node15188D00 *, s16);

#define WGFX15188D00(pkt, a, b)     \
{                                   \
    Gfx *_g = (Gfx *)(pkt);         \
    _g->words.w0 = (u32)(a);        \
    _g->words.w1 = (u32)(b);        \
}

Gfx *func_15188D00(Gfx *gfx, s32 idx, s16 arg2) {
    Node15188D00 *node;
    Gfx *(**callbacks)(Gfx *, Node15188D00 *, s16);
    s16 tmp;

    tmp = arg2;
    node = (Node15188D00 *)D_800DF7C8[idx];
    if (node == 0) {
        return gfx;
    }

    WGFX15188D00(gfx++, 0xDA380003, &D_80089470);
    WGFX15188D00(gfx++, 0xD9FFFFFF, 0x00200004);
    WGFX15188D00(gfx++, 0xD9EEFFFF, 0x00000000);
    WGFX15188D00(gfx++, 0xE7000000, 0x00000000);
    WGFX15188D00(gfx++, 0xE2001E01, 0x00000000);
    WGFX15188D00(gfx++, 0xEC000000, 0x000000FF);
    callbacks = D_8008D590;
    while (node != 0) {
        gfx = callbacks[node->unk0](gfx, node, tmp);
        node = node->unkC;
    }
    return gfx;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1B5CC0/func_15188E48.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1B5CC0/func_15188F84.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1B5CC0/func_15189118.s")

void func_151895A4(s32 *arg0) {
    func_100043B4((s32 *)arg0[2], 2);
}

void func_151895CC(s32 *arg0) {
    func_100043B4((s32 *)arg0[2], 2);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1B5CC0/func_151895F4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1B5CC0/func_151897A4.s")

typedef struct Node151898C0 {
    char pad0[12];
    struct Node151898C0 *unkC;
    s32 unk10;
    s32 unk14;
} Node151898C0;

void func_151898C0(s32 arg0, s32 arg1) {
    Node151898C0 *node;

    node = (Node151898C0 *)D_800DF7C8[0];
    while (node != 0) {
        if (arg0 == node->unk10) {
            node->unk14 = arg1;
            return;
        }
        node = node->unkC;
    }
}
