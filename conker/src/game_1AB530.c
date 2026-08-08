#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern void *allocate_memory(s32 arg0, s32 arg1, s32 arg2, s32 arg3);

typedef struct Node_1517E134 {
    char pad0[0xC];
    f32 unkC;
    f32 unk10;
    char pad14[0x10];
    struct Node_1517E134 *next;
    s16 unk28;
    char pad2A[4];
    s8 unk2E;
    s8 unk2F;
    s8 unk30;
} Node_1517E134;

Node_1517E134 *func_1517E080(s32 arg0, s32 arg1) {
    Node_1517E134 *cur;
    Node_1517E134 **slot;

    cur = (Node_1517E134 *)D_800DDD64;
    if (cur != NULL) {
        if (cur->next != NULL) {
            do {
                cur = cur->next;
            } while (cur->next != NULL);
        }
        slot = &cur->next;
    } else {
        slot = (Node_1517E134 **)&D_800DDD64;
    }

    cur = allocate_memory(0x34, 1, 0, 1);
    if (cur == NULL) {
        return NULL;
    }
    *slot = cur;
    cur->next = NULL;
    cur->unk28 = 0;
    cur->unk2E = 0;
    cur->unk10 = 0.0f;
    cur->unkC = 0.0f;
    cur->unk2F = arg0;
    cur->unk30 = arg1;
    return cur;
}

typedef struct Node_1517E1AC {
    char pad0[0xC];
    f32 unkC;
    f32 unk10;
    char pad14[0x10];
    struct Node_1517E1AC *next;
    char pad28[0x2];
    u16 unk2A;
} Node_1517E1AC;

extern void func_10004074(void);

void func_1517E134(Node_1517E134 *arg0) {
    Node_1517E134 *cur;
    Node_1517E134 *prev;

    cur = (Node_1517E134 *)D_800DDD64;
    if (arg0 == cur) {
        D_800DDD64 = (s32)arg0->next;
    } else {
        prev = cur;
        if (cur != NULL) {
            cur = cur->next;
            while (arg0 != cur) {
                prev = cur;
                if (cur == NULL) {
                    break;
                }
                cur = cur->next;
            }
        }
        if (prev != NULL) {
            prev->next = arg0->next;
        } else {
            return;
        }
    }
    func_10004074();
}

void func_1517E1AC(void) {
    Node_1517E1AC *cur;
    s32 *width;
    s32 *height;
    s32 *framebuffer;
    s32 screenWidth;
    s32 ix;
    s32 iy;
    f32 x;
    f32 y;
    f32 zero;

    cur = (Node_1517E1AC *)D_800DDD64;
    framebuffer = (s32 *)((s32)&D_800BE9C4);
    if (cur != NULL) {
        width = (s32 *)((s32)&D_800BE620);
        height = (s32 *)((s32)&D_800BE624);
        zero = 0.0f;
        do {
            x = cur->unkC;
            if (zero <= x) {
                screenWidth = *width;
                if (x < (f32)screenWidth) {
                    y = cur->unk10;
                    if ((zero <= y) && (y < (f32)*height)) {
                        iy = (s32)y;
                        ix = (s32)x;
                        cur->unk2A = *(((u16 *)*framebuffer) + ix + (iy * screenWidth));
                    }
                }
            }
            cur = cur->next;
        } while (cur != NULL);
    }
}

typedef struct {
    u8 unk0[2];
} Pair_1517E28C;

extern Pair_1517E28C D_8008D004;
extern Pair_1517E28C D_8008D008;
extern Pair_1517E28C D_8008D00C;
extern u8 D_800DDD60;

typedef struct Node_1517E28C {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    char pad14[0x10];
    struct Node_1517E28C *next;
    char pad28[0x2];
    u16 unk2A;
    u16 unk2C;
    u8  unk2E;
    u8  unk2F;
    u8  unk30;
} Node_1517E28C;

extern s32 func_1517EAAC(f32 x, f32 y, f32 z, f32 *outX, f32 *outY);
extern s32 func_1517EC1C(Node_1517E28C *node, s32 *outDist);
extern Gfx *func_1517E4A8(Gfx *gfx, Node_1517E28C *node, s32 arg2, s32 arg3, s32 arg4, s32 arg5, u8 *arg6);

Gfx *func_1517E28C(Gfx *gfx, s32 arg1) {
    s32 alpha;
    s32 cull;
    s32 dist;
    Node_1517E28C *node;
    f32 *pos;
    Pair_1517E28C param0 = D_8008D004;
    Pair_1517E28C param1 = D_8008D008;
    Pair_1517E28C param2 = D_8008D00C;
    u8 *flag;

    node = (Node_1517E28C *)D_800DDD64;
    D_800DDD60 = 0;
    if (node != NULL) {
        do {
            if (node->unk30 != 0) {
                cull = 0;
                if (node->unk2E & 1) {
                    if (D_800DCDD0 == 0) {
                        cull = 1;
                    } else {
                        pos = (f32 *)D_8008CFFC[D_800B0DF0->unk10];
                        if (func_1517EAAC(pos[0], pos[1], pos[2], &node->unkC, &node->unk10) != 1) {
                            cull = 1;
                        }
                        alpha = (node->unk2A != 0xFFFC) ? -1 : 0xFF;
                    }
                } else {
                    if (func_1517EC1C(node, &dist) != 1) {
                        cull = 1;
                    }
                    alpha = ((s32)(node->unk2C - dist) < 0x1E) ? 0x100 : -1;
                }
                flag = (node->unk2E & 2) ? &D_800DD2D0 : NULL;
                if (!cull) {
                    gfx = func_1517E4A8(gfx, node, param0.unk0[node->unk2F], param1.unk0[node->unk2F],
                                        param2.unk0[node->unk2F], alpha, flag);
                } else if (flag != NULL) {
                    *flag = 0;
                }
            }
            node = node->next;
        } while (node != NULL);
    }
    return gfx;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1AB530/func_1517E4A8.s")

#define WGFX1517EA4C(pkt, a, b)     \
{                                   \
    Gfx *_g = (Gfx *)(pkt);         \
    _g->words.w0 = (u32)(a);        \
    _g->words.w1 = (u32)(b);        \
}

Gfx *func_1517EA4C(Gfx *arg0) {
    WGFX1517EA4C(arg0++, 0xE7000000, 0);
    WGFX1517EA4C(arg0++, 0xFCFFB3FF, 0xFF65FEFF);
    WGFX1517EA4C(arg0++, 0xEF002C0F, 0x00504344);
    return arg0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1AB530/func_1517EAAC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1AB530/func_1517EC1C.s")
