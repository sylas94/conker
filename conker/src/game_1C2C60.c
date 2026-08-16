#include <ultra64.h>
#define func_151422C0 func_151422C0_header
#include "functions.h"
#undef func_151422C0
#include "variables.h"

void func_1519CDB0(s32, f32, s32);
extern void *allocate_memory(s32, s32, s32, s32);

s32 func_15195DD4(s32, s32, s32, s32, s32, s32, s32);
s32 func_151422C0();
struct225 *func_151602C0(Header *, Header2 *, s32, s32, s32, s32, u8, u8, s32, u8, s32);

extern char D_800A8A40[];
extern char D_800A8A48[];
extern f32 D_800A8AA8;
extern f32 D_800A8AF8;

extern s32 D_800E08E0;
extern s32 D_800E08E4;
extern s32 D_800E08E8;
extern s32 D_800E08EC;
extern s32 D_800E08F0;

typedef struct Struct151957B0 {
    struct Struct151957B0 *prev;
    struct Struct151957B0 *next;
} Struct151957B0;

void *func_151957B0(s32 size, void *head, void *tail) {
    Struct151957B0 *node;
    Struct151957B0 *prev;

    node = allocate_memory(size, 1, 0, 0);
    if (node != 0) {
        node->next = 0;
        prev = *(Struct151957B0 **)tail;
        if (prev != 0) {
            node->prev = prev;
            (*(Struct151957B0 **)tail)->next = node;
            *(Struct151957B0 **)tail = node;
        } else {
            node->prev = 0;
            *(Struct151957B0 **)tail = node;
            *(Struct151957B0 **)head = node;
        }
    }
    return node;
}

void trailing_151957B0(void) {
}

void func_1519582C(void) {
    D_800E08E0 = D_800E08E4 = 0;
    D_800E08E8 = D_800E08EC = 0;
    D_800E08F0 = -2;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1C2C60/func_15195868.s")

extern void *func_151957B0(s32, void *, void *);
extern s32 D_800E08E0;
extern s32 D_800E08E4;
extern s32 D_800E08E8;
extern s32 D_800E08EC;

typedef struct Struct15195984 {
    struct Struct15195984 *prev;
    struct Struct15195984 *next;
    s16 unk8;
    s16 unkA;
    s16 unkC;
    s16 unkE;
    s16 unk10;
    u8 unk12;
    u8 unk13;
    u8 unk14;
    char pad15[0x18 - 0x15];
    s32 unk18;
    s16 unk1C[5];
    s16 unk26[5];
} Struct15195984;

void *func_15195984(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    Struct15195984 *v0;
    s32 i;
    s32 hi;
    s32 lo;

    v0 = func_151957B0(0x3C, &D_800E08E8, &D_800E08EC);
    if (v0 != 0) {
        v0->unk18 = 0;
        for (i = 0; i < 5; i++) {
            v0->unk1C[i] = -1;
        }
        for (i = 0; i < 5; i++) {
            v0->unk26[i] = -1;
        }
        v0->unk8 = arg0;
        hi = ((arg1 >> 12) & 0xFFF) + 2;
        lo = (arg1 & 0xFFF) + 2;
        if (arg3 != 0) {
            hi <<= 1;
            lo <<= 1;
        }
        v0->unkE = (arg2 >> 12) & 0xFFF;
        v0->unk10 = arg2 & 0xFFF;
        v0->unkA = hi;
        v0->unkC = lo;
        v0->unkE = (u16)v0->unkE << 3;
        v0->unk10 = (u16)v0->unk10 << 3;
        v0->unk14 = 1;
    }
    return v0;
}

s16 func_15195A84(s16 arg0, s32 arg1, s32 arg2, s32 arg3) {
    return arg0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1C2C60/func_15195AA8.s")

typedef struct Struct15195D00 {
    char pad0[0x8];
    s32 unk8;
    u16 unkC;
    u8 unkE;
    u8 unkF;
    struct Struct15195D00 *unk10;
} Struct15195D00;

void func_15195D00(Struct15195984 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    Struct15195D00 *temp_v1;
    Struct15195D00 *temp_v0;
    s32 temp_arg3;

    temp_v0 = (Struct15195D00 *) arg0->unk18;
    if (temp_v0 != 0) {
        temp_v1 = temp_v0;
        do {
            if ((arg1 == temp_v1->unk8) && (arg2 == temp_v1->unkC)) {
                return;
            }
            temp_v0 = temp_v1->unk10;
            if (temp_v0 != 0) {
                temp_v1 = temp_v0;
                temp_v0 = temp_v0->unk10;
            }
        } while (temp_v0 != 0);
        temp_v0 = func_151957B0(0x14, &D_800E08E0, &D_800E08E4);
        temp_v1->unk10 = temp_v0;
    } else {
        temp_v0 = func_151957B0(0x14, &D_800E08E0, &D_800E08E4);
        arg0->unk18 = (s32) temp_v0;
    }
    temp_v0->unk8 = arg1;
    temp_v0->unkC = arg2;
    temp_arg3 = arg3;
    temp_v0->unkE = temp_arg3;
    temp_v0->unk10 = 0;
}

extern s32 func_15195868(s32, s32, s32, s32 *);

typedef struct {
    s32 pos;
    s32 size;
} Struct15195DD4Cmd;

s32 func_15195DD4(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    s32 idx;
    s32 key;
    s32 size;
    s32 depth;
    s32 pos;
    s32 i = arg3;
    Struct15195984 *node;

    if (arg0 == 0) {
        return 0;
    }
    if (D_800BEAC0 != 0) {
        return 0;
    }
    if (arg3 == -1) {
        i = 0;
    }
    do {
        idx = func_15195868(arg0, arg1, i, &depth);
        if (idx == -1) {
            arg3 = 0;
        } else {
            if (arg1 == 0) {
                arg1 = D_800E08F0;
            }
            if (arg4 != 0) {
                key = -1;
            } else {
                key = arg1;
            }
            node = (Struct15195984 *) D_800E08E8;
            while ((node != 0) && (key != node->unk8)) {
                node = node->next;
            }
            size = ((Struct15195DD4Cmd *) arg0 + idx)->size;
            pos = ((Struct15195DD4Cmd *) arg0 + idx)->pos;
            if (node == 0) {
                node = func_15195984(arg1, size, pos, arg2);
                if (node != 0) {
                    arg4 = 0;
                    node->unk12 = arg5;
                    node->unk13 = arg6;
                } else {
                    return 0;
                }
            } else {
                idx = func_15195A84(idx, (s32) node, size, arg2);
                arg4 = 0;
            }
            if (node->unk14 < depth) {
                node->unk14 = depth;
            }
            func_15195D00(node, arg0, idx, depth);
            i++;
        }
    } while (arg3 == -1);
    if (arg1 == D_800E08F0) {
        D_800E08F0--;
    }
    return (s32) node;
}

typedef struct {
    char pad_0x0[0x1C];
    s32 field_0x1C;
} ResourceEntry;

s32 func_15195FB0(ResourceEntry *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    return func_15195DD4(arg0->field_0x1C, arg1, arg2, arg3, arg4, arg5, arg6);
}

typedef struct {
    /* 0x0 */ u32 w0;
    /* 0x4 */ u32 w1;
} Cmd15195FF0;

typedef struct Sub15195FF0 {
    /* 0x00 */ char pad00[0x8];
    /* 0x08 */ Cmd15195FF0 *unk08;
    /* 0x0C */ u16 unk0C;
    /* 0x0E */ u8 unk0E;
    /* 0x0F */ u8 unk0F;
    /* 0x10 */ struct Sub15195FF0 *unk10;
} Sub15195FF0;

typedef struct Struct15195FF0 {
    /* 0x00 */ struct Struct15195FF0 *prev;
    /* 0x04 */ struct Struct15195FF0 *next;
    /* 0x08 */ s16 unk08;
    /* 0x0A */ s16 unk0A;
    /* 0x0C */ s16 unk0C;
    /* 0x0E */ u16 unk0E;
    /* 0x10 */ u16 unk10;
    /* 0x12 */ s8 unk12;
    /* 0x13 */ s8 unk13;
    /* 0x14 */ u8 unk14;
    /* 0x15 */ char pad15[0x3];
    /* 0x18 */ Sub15195FF0 *unk18;
    /* 0x1C */ s16 unk1C[5];
    /* 0x26 */ s16 unk26[5];
    /* 0x30 */ u8 unk30[5];
    /* 0x35 */ u8 unk35[5];
} Struct15195FF0;

void func_15195FF0(Cmd15195FF0 *arg0, Cmd15195FF0 *arg1) {
    Struct15195FF0 *node;
    u32 sp5C[8];
    Sub15195FF0 *sub;
    s32 uls;
    s32 ult;
    s32 w;
    s32 h;
    s32 x;
    s32 y;
    s32 i;
    s32 k;
    s32 idx;

    node = (Struct15195FF0 *)D_800E08E8;
    while (node != NULL) {
        w = node->unk0A;
        h = node->unk0C;
        x = node->unk0E;
        y = node->unk10;
        uls = x / 8 + 2;
        ult = y / 8 + 2;
        if (uls >= w) {
            uls = uls - w;
        }
        if (ult >= h) {
            ult = ult - h;
        }
        for (i = 0; i < 8 && i < node->unk14; i++) {
            sp5C[i] = 0xF2000000 | ((uls & 0xFFF) << 12) | (ult & 0xFFF);
            uls /= 2;
            ult /= 2;
        }
        w *= 8;
        h *= 8;
        if (D_800BEAC0 == 0) {
            x += node->unk12 * D_800BE9E4;
            y += node->unk13 * D_800BE9E4;
        }
        if (x < 0) {
            x += w;
        } else if (x >= w) {
            x -= w;
        }
        if (y < 0) {
            y += h;
        } else if (y >= h) {
            y -= h;
        }
        node->unk0E = x;
        node->unk10 = y;
        for (k = 0; k < 5 && node->unk1C[k] != -1; k++) {
            idx = node->unk1C[k];
            for (i = 0; i < node->unk30[k]; i++) {
                arg0[idx].w0 = sp5C[i];
                idx += 2;
            }
        }
        for (k = 0; k < 5 && node->unk26[k] != -1; k++) {
            idx = node->unk26[k];
            for (i = 0; i < node->unk35[k]; i++) {
                arg1[idx].w0 = sp5C[i];
                idx += 2;
            }
        }
        sub = node->unk18;
        while (sub != NULL) {
            idx = sub->unk0C;
            for (i = 0; i < sub->unk0E; i++, idx += 2) {
                sub->unk08[idx].w0 = sp5C[i];
            }
            if (sub->unk10 != NULL) {
                sub = sub->unk10;
            } else {
                sub = NULL;
            }
        }
        node = node->next;
    }
}

void func_15196318(u8 *arg0, s32 arg1, s32 arg2) {
    if (arg0 != 0) {
        arg0[0x12] = arg1;
        arg0[0x13] = arg2;
    }
}

extern void (*D_8008F898[])(void *);
extern void (*D_8008F88C[])(void *);
void func_151478F4(void *);
void func_15147928(void *);

void func_15196330(void *arg0) {
    s8 *temp;

    temp = *(s8 **)((u8 *)arg0 + 0x98);
    if (temp[0x65] != -1) {
        D_8008F898[temp[0x65]](arg0);
    }
    if (temp[0x62] != -1) {
        D_8008F88C[temp[0x62]](arg0);
    }
    func_151478F4(arg0);
}

void func_151963B4(void *arg0) {
    s8 *temp;

    temp = *(s8 **)((u8 *)arg0 + 0x98);
    if (temp[0x65] != -1) {
        D_8008F898[temp[0x65]](arg0);
    }
    if (temp[0x62] != -1) {
        D_8008F88C[temp[0x62]](arg0);
    }
    func_15147928(arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1C2C60/func_15196438.s")

typedef struct {
    /* 0x00 */ f32 x;
    /* 0x04 */ f32 y;
    /* 0x08 */ f32 z;
} Vec15196748;

typedef struct {
    /* 0x00 */ Vec15196748 pos;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ s8 unk1E;
    /* 0x1F */ u8 unk1F;
    /* 0x20 */ u8 unk20;
    /* 0x21 */ u8 unk21;
    /* 0x22 */ u8 pad22[0x2];
} Particle15196748;

typedef struct {
    /* 0x00 */ u8 pad0[0x6];
    /* 0x06 */ u8 unk6;
    /* 0x07 */ u8 pad7[0x40 - 0x7];
    /* 0x40 */ f32 unk40;
    /* 0x44 */ u8 pad44[0x52 - 0x44];
    /* 0x52 */ u8 unk52;
    /* 0x53 */ u8 pad53[0x58 - 0x53];
    /* 0x58 */ f32 unk58;
    /* 0x5C */ u8 pad5C[0x61 - 0x5C];
    /* 0x61 */ s8 unk61;
    /* 0x62 */ u8 pad62[0x64 - 0x62];
    /* 0x64 */ s8 unk64;
    /* 0x65 */ u8 pad65[0x68 - 0x65];
    /* 0x68 */ s8 unk68;
    /* 0x69 */ u8 pad69[0x6A - 0x69];
    /* 0x6A */ u8 unk6A;
    /* 0x6B */ u8 pad6B[0x8C - 0x6B];
    /* 0x8C */ u8 unk8C;
    /* 0x8D */ u8 unk8D;
    /* 0x8E */ u8 unk8E;
    /* 0x8F */ u8 unk8F;
} Desc15196748;

typedef struct {
    /* 0x00 */ u8 pad0[0x25];
    /* 0x25 */ u8 unk25;
    /* 0x26 */ u8 pad26[0x2C - 0x26];
    /* 0x2C */ s8 unk2C;
    /* 0x2D */ s8 unk2D;
    /* 0x2E */ s8 unk2E;
    /* 0x2F */ u8 pad2F[0x54 - 0x2F];
    /* 0x54 */ Vec15196748 unk54;
    /* 0x60 */ u8 pad60[0x94 - 0x60];
    /* 0x94 */ Particle15196748 *unk94;
    /* 0x98 */ Desc15196748 *unk98;
} Emitter15196748;

extern void (*D_8008F894[])(void *);
extern void (*D_8008F89C[])(void *);
extern s32 (*D_8008F880[])(void *);
void func_15198110(void *, s32);

s32 func_15196748(Emitter15196748 *arg0) {
    Desc15196748 *desc;
    Particle15196748 *arr;
    s32 i;
    s16 n;
    u8 scale;
    s8 life;
    u8 flags;
    u8 descFlags;

    desc = arg0->unk98;
    arr = arg0->unk94;
    if (arg0->unk2C < 2 && (desc->unk6 & 1)) {
        return 0;
    }
    i = arg0->unk2E;
    while (i != arg0->unk2D) {
        i--;
        if (i < 0) {
            i = arg0->unk25 - 1;
        }
        arr[i].unk10 += desc->unk40 * D_800BE9A4;
        arr[i].pos.x += arr[i].unkC * D_800BE9A4;
        arr[i].pos.y += arr[i].unk10 * D_800BE9A4;
        arr[i].pos.z += arr[i].unk14 * D_800BE9A4;
        arr[i].unk1F = 255;
        life = arr[i].unk1E;
        if (life > 0) {
            arr[i].unk1E = life - D_800BE9E4;
        } else {
            arr[i].unk1C -= desc->unk52 * D_800BE9E4;
        }
        if (arr[i].unk1C < desc->unk6A) {
            if (arr[i].unk21 == 0) {
                func_15198110(arg0, i);
            }
        }
        arr[i].unk18 += desc->unk58 * D_800BE9A4;
        if (arr[i].unk1C < 0) {
            desc->unk6 &= ~2;
            while (i != arg0->unk2D) {
                arg0->unk2D = arg0->unk2D + 1;
                if (arg0->unk2D == arg0->unk25) {
                    arg0->unk2D = 0;
                }
                arg0->unk2C = arg0->unk2C - 1;
            }
            arr[arg0->unk2D].unk1C = 0;
        }
    }
    i = arg0->unk2D;
    descFlags = desc->unk6;
    flags = descFlags;
    if (flags & 2) {
        flags = 0;
        n = desc->unk8C;
        do {
            arr[i].unk1F = flags; i++; flags += desc->unk8D; if (i == arg0->unk25) { i = 0; } n--;
        } while (n != 0 && i != arg0->unk2E);
        flags = desc->unk6;
    }
    if (flags & 4) {
        scale = 0;
        n = desc->unk8E;
        i = arg0->unk2E - 1;
        if (i < 0) {
            i = arg0->unk25 - 1;
        }
        do {
            arr[i].unk1F = (arr[i].unk1F * scale) >> 8; i--; scale += desc->unk8F; if (i < 0) { i = arg0->unk25 - 1; } n--;
        } while (n != 0 && i != arg0->unk2E);
    }
    if (desc->unk64 != -1) {
        D_8008F894[desc->unk64](arg0);
    }
    if (desc->unk68 != -1) {
        D_8008F89C[desc->unk68](arg0);
    }
    if (desc->unk61 != -1) {
        if (D_8008F880[desc->unk61](arg0) == 0) {
            return 0;
        }
    }
    if (arg0->unk2C > 0) {
        arg0->unk54 = arr[arg0->unk2D].pos;
    } else {
        arg0->unk54.x = 0.0f;
        arg0->unk54.y = 0.0f;
        arg0->unk54.z = 0.0f;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1C2C60/func_15196B4C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1C2C60/func_15197148.s")

extern f32 D_800A8AA4;

f32 func_151979F8(s32 arg0) {
    return D_800A8AA4;
}

f32 func_15197A0C(s32 arg0) {
    return (f32)func_151422C0(0xA, (s32) D_800A8A40, 1, 0x1F4, (s32) D_800A8A48, 0x8CC) * D_800A8AA8;
}

extern f32 D_800A8AAC;

f32 func_15197A68(s32 arg0) {
    return D_800A8AAC;
}

struct ConkerStruct15197A7C {
    s32 unk0;
    u8 unk4;
};

extern void func_15147D64(struct ConkerStruct15197A7C *, s32);

void func_15197A7C(u8 *arg0) {
    struct ConkerStruct15197A7C sp18;

    if (arg0 != 0) {
        sp18.unk0 = (s32) arg0;
        sp18.unk4 = arg0[0x3B];
        func_15147D64(&sp18, 8);
    }
}

s32 func_15197AB4(f32 *arg0)
{
  int dummy;
  arg0[0x50] = arg0[0x57] * arg0[0x50];
  arg0[0x51] += arg0[0x56] * D_800BE9A4;
  dummy = (arg0 != 0);
  arg0[0x52] = arg0[0x57] * arg0[0x52];
  arg0[0x53] = arg0[0x58] * arg0[0x53];
  arg0[0x54] += arg0[0x56] * D_800BE9A4;
  arg0[0x55] = arg0[0x58] * arg0[0x55];
  arg0[0xD] += arg0[0x50] * D_800BE9A4;
  arg0[0xE] += arg0[0x51] * D_800BE9A4;
  arg0[0xF] += arg0[0x52] * D_800BE9A4;
  arg0[0x10] += arg0[0x53] * D_800BE9A4;
  arg0[0x11] += arg0[0x54] * D_800BE9A4;
  arg0[0x12] += arg0[0x55] * D_800BE9A4;
  return 1;
}

typedef struct {
    char pad0[0x1C];
    s16 unk1C;
    char pad1E[0x2C - 0x1E];
    f32 unk2C;
    f32 unk30;
    char pad34[0x5C - 0x34];
    u8 unk5C;
    char pad5D[0x164 - 0x5D];
    f32 unk164;
    s16 unk168;
    s16 unk16A;
} Struct15197BBC;

s32 func_15197BBC(Struct15197BBC *arg0) {
    s16 temp;

    temp = arg0->unk1C;
    arg0->unk30 = arg0->unk30 - (arg0->unk30 * arg0->unk164);
    arg0->unk2C = arg0->unk2C - (arg0->unk2C * arg0->unk164);
    if (temp < arg0->unk168) {
        arg0->unk5C = temp * arg0->unk16A;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1C2C60/func_15197C10.s")

typedef struct {
    s32 unk0;
    u8 unk4;
} SubA_15198054;

typedef struct {
    s32 unk0;
    union {
        u8 b4;
        s32 w4;
    } u4;
    u8 unk8;
    u8 unk9;
} ArgB_15198054;

void func_151993B4();

void func_15198054(void *arg0, s32 arg1, u8 arg2) {
    SubA_15198054 *temp_v1 = *(SubA_15198054 **)((u8 *)arg0 + 0x98);
    ArgB_15198054 *b = (ArgB_15198054 *)arg1;

    if (arg2 == 0 || arg2 == 2 || arg2 == 8) {
        if ((b->unk0 == temp_v1->unk0) || (b->u4.b4 == temp_v1->unk4)) {
            func_151993B4(arg0);
        }
    } else if (arg2 == 0x2D) {
        if (temp_v1->unk0 == b->unk0) {
            temp_v1->unk0 = b->u4.w4;
            temp_v1->unk4 = b->unk9;
        } else if (temp_v1->unk0 == b->u4.w4) {
            temp_v1->unk0 = b->unk0;
            temp_v1->unk4 = b->unk8;
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1C2C60/func_15198110.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1C2C60/func_15198570.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1C2C60/func_151987CC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1C2C60/func_1519897C.s")

void func_15198C60(void) {
    func_10010F30(0x1AA, 0x7FFF, 0x40, 0, 0);
}

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    char padC[0x24 - 0xC];
} Struct15198C90Vec;

typedef struct {
    char pad_0x0[0x66];
    u16 field_0x66;
} Struct15198C90Sound;

typedef struct {
    char pad_0x0[0x2C];
    s8 field_0x2C;
    s8 field_0x2D;
    char pad_0x2E[0x94 - 0x2E];
    Struct15198C90Vec *field_0x94;
    Struct15198C90Sound *field_0x98;
} Struct15198C90;

void func_15198C90(Struct15198C90 *arg0) {
    Struct15198C90Vec *temp_v1;
    Struct15198C90Sound *temp_v2;
    u16 temp_a0;
    s32 temp_t6;
    s32 temp_t7;

    temp_v2 = arg0->field_0x98;
    temp_v1 = arg0->field_0x94;

    if (arg0->field_0x2C != 0) {
        temp_a0 = temp_v2->field_0x66;
        if (temp_a0 != 0) {
            temp_t6 = 0x1388;
            temp_t7 = 0x1F4;
            func_1000F91C(temp_a0, 0x7FFF, 0, 0, 0,
                          ((Struct15198C90Vec *)((u8 *)temp_v1 + (arg0->field_0x2D * 0x24)))->unk0,
                          ((Struct15198C90Vec *)((u8 *)temp_v1 + (arg0->field_0x2D * 0x24)))->unk4,
                          ((Struct15198C90Vec *)((u8 *)temp_v1 + (arg0->field_0x2D * 0x24)))->unk8,
                          temp_t7, temp_t6);
        }
    }
}

void func_15198D40(Struct15198C90 *arg0) {
    Struct15198C90Sound *temp;
    u16 val;

    temp = arg0->field_0x98;
    if (arg0->field_0x2C != 0) {
        val = temp->field_0x66;
        if (val != 0) {
            func_100111C8(val);
        }
    }
}

void func_15198D7C(s32 arg0) {
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1C2C60/func_15198D88.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1C2C60/func_151990AC.s")

struct ConkerStruct151993B4 {
    char pad0[0x1E];
    u16 unk1E;
    char pad20[0x10];
    u8 unk30;
    char pad31[0x67];
    u8 *unk98;
};

void func_151993B4(struct ConkerStruct151993B4 *arg0) {
    u8 *p;
    p = arg0->unk98;
    arg0->unk30 = 0;
    arg0->unk1E &= 0xFFFD;
    p[6] |= 1;
    p[6] |= 4;
}

extern u8 D_800A8A9C[];

void func_151993E4(u8 *arg0) {
    u8 *q;
    u8 *p;
    s32 i;
    s32 found;

    q = *(u8 **)(arg0 + 0x98);
    p = *(u8 **)q;
    i = 0;
    found = 0;
    do {
        if (p[0x3B] == D_800A8A9C[i]) {
            found = 1;
        } else {
            i++;
        }
    } while (!found && i < 6);

    if (found) {
        ((u8 *)D_800E0900[i])[0x14] = 0;
    }
}

void func_1519944C(u8 *arg0) {
    u8 *q;
    u8 *p;
    s32 i;
    s32 found;

    q = *(u8 **)(arg0 + 0x98);
    p = *(u8 **)q;
    i = 0;
    found = 0;
    do {
        if (p[0x3B] == D_800A8A9C[i]) {
            found = 1;
        } else {
            i++;
        }
    } while (!found && i < 6);

    if (found) {
        ((u8 *)D_800E0900[i])[0x14] = 1;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1C2C60/func_151994B8.s")

void func_15199834(u8 *arg0) {
    struct ConkerStruct15197A7C sp18;

    if (arg0 != 0) {
        sp18.unk0 = (s32) arg0;
        sp18.unk4 = arg0[0x3B];
        func_15147D64(&sp18, 0x26);
    }
}

void func_1516972C();

void func_1519986C(void *arg0, s32 arg1, u8 arg2) {
    SubA_15198054 *temp_v1 = *(SubA_15198054 **)((u8 *)arg0 + 0x98);
    ArgB_15198054 *b = (ArgB_15198054 *)arg1;

    if (arg2 == 0 || arg2 == 2 || arg2 == 0x26) {
        if ((b->unk0 == temp_v1->unk0) || (b->u4.b4 == temp_v1->unk4)) {
            func_1516972C(arg0);
        }
    } else if (arg2 == 0x2D) {
        if (temp_v1->unk0 == b->unk0) {
            temp_v1->unk0 = b->u4.w4;
            temp_v1->unk4 = b->unk9;
        } else if (temp_v1->unk0 == b->u4.w4) {
            temp_v1->unk0 = b->unk0;
            temp_v1->unk4 = b->unk8;
        }
    }
}

void func_15199980(void *);
void func_151478F4(void *);

void func_15199928(void *arg0) {
    func_15199980(arg0);
    func_151478F4(arg0);
}

void func_15147928(void *);

void func_15199954(void *arg0) {
    func_15199980(arg0);
    func_15147928(arg0);
}

extern void (*D_8008F8C0[])(void *);
extern void (*D_8008F8B4[])(void *);

void func_15199980(void *arg0) {
    s8 *temp;
    struct102 *p;

    temp = *(s8 **)((u8 *)arg0 + 0x98);
    if (temp[0x39] != -1) {
        D_8008F8C0[temp[0x39]](arg0);
    }
    if (temp[0x36] != -1) {
        D_8008F8B4[temp[0x36]](arg0);
    }
    p = *(struct102 **)(temp + 0x148);
    if (p != 0) {
        func_1516972C(p);
    }
}

extern s32 (*D_8008F8C4[])(void *);
extern void (*D_8008F8BC[])(void *);

void func_1519BE1C(struct17 *arg0, struct17 *arg1, f32 arg2, f32 arg3);

typedef struct {
    struct17 unk0;
    struct17 unkC;
    f32 unk18;
    char pad1C[0x28 - 0x1C];
} Struct15199A10Point;

typedef struct {
    char pad0[0xE];
    s16 unkE;
    s16 unk10;
    s16 unk12;
} Struct15199A10Out;

typedef struct {
    char pad0[0x14];
    Struct15199A10Out *unk14;
} Struct15199A10Node;

typedef struct {
    char pad0[0x20];
    f32 unk20;
    char pad24[0x30 - 0x24];
    f32 unk30;
    char pad34[0x38 - 0x34];
    s8 unk38;
    char pad39[0x48 - 0x39];
    s8 unk48;
    char pad49[0x148 - 0x49];
    Struct15199A10Node *unk148;
    char pad14C[0x150 - 0x14C];
    u8 unk150;
} Struct15199A10Data;

typedef struct {
    char pad0[0x1E];
    u16 unk1E;
    char pad20[0x25 - 0x20];
    u8 unk25;
    char pad26[0x2C - 0x26];
    s8 unk2C;
    s8 unk2D;
    s8 unk2E;
    char pad2F[0x54 - 0x2F];
    struct17 unk54;
    char pad60[0x94 - 0x60];
    Struct15199A10Point *unk94;
    Struct15199A10Data *unk98;
} Struct15199A10;

s32 func_15199A10(Struct15199A10 *arg0) {
    Struct15199A10Data *data;
    Struct15199A10Point *pts;
    s32 i;

    data = arg0->unk98;
    pts = arg0->unk94;
    data->unk150 &= ~0x10;
    if (arg0->unk2C < 2) {
        if (arg0->unk1E & 8) {
            return 0;
        }
    }
    if (data->unk48 != -1) {
        if (D_8008F8C4[data->unk48](arg0) == 0) {
            return 0;
        }
    }
    i = arg0->unk2E;
    while (i != arg0->unk2D) {
        Struct15199A10Point *pt;

        i--;
        if (i < 0) {
            i = arg0->unk25 - 1;
        }
        pt = &pts[i];
        func_1519BE1C(&pt->unk0, &pt->unkC, data->unk20, D_800BE9A4);
        pt->unk18 += data->unk30 * D_800BE9A4;
    }
    {
        Struct15199A10Point *head;

        if (data->unk148 != 0 && arg0->unk2C >= 2) {
            Struct15199A10Node *node = data->unk148;
            Struct15199A10Out *out = node->unk14;

            head = &pts[arg0->unk2D];
            out->unkE = head->unk0.unk0;
            out->unk10 = head->unk0.unk4;
            out->unk12 = head->unk0.unk8;
        }
    }
    if (data->unk38 != -1) {
        D_8008F8BC[data->unk38](arg0);
    }
    data->unk150 &= ~0x1;
    if (arg0->unk2C > 0) {
        arg0->unk54 = pts[arg0->unk2D].unk0;
    } else {
        arg0->unk54.unk0 = 0.0f;
        arg0->unk54.unk4 = 0.0f;
        arg0->unk54.unk8 = 0.0f;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1C2C60/func_15199C34.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1C2C60/func_1519A9A4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1C2C60/func_1519B4B8.s")

void func_1519BE1C(struct17 *arg0, struct17 *arg1, f32 arg2, f32 arg3) {
    struct17 sp4;

    sp4 = *arg1;
    arg1->unk4 += arg2 * arg3;
    arg0->unk0 += sp4.unk0 * arg3;
    arg0->unk4 += (sp4.unk4 * arg3) + (0.5f * arg2 * arg3 * arg3);
    arg0->unk8 += sp4.unk8 * arg3;
}

void func_1519BEB8(u8 *arg0) {
    u8 *q;
    u8 *p;
    s32 i;
    s32 found;

    q = *(u8 **)(arg0 + 0x98);
    p = *(u8 **)q;
    i = 0;
    found = 0;
    do {
        if (p[0x3B] == D_800A8A9C[i]) {
            found = 1;
        } else {
            i++;
        }
    } while (!found && i < 6);

    if (found) {
        ((u8 *)D_800E0900[i])[0x14] = 0;
    }
}

void func_1519BF20(u8 *arg0) {
    u8 *q;
    u8 *p;
    s32 i;
    s32 found;

    q = *(u8 **)(arg0 + 0x98);
    p = *(u8 **)q;
    i = 0;
    found = 0;
    do {
        if (p[0x3B] == D_800A8A9C[i]) {
            found = 1;
        } else {
            i++;
        }
    } while (!found && i < 6);

    if (found) {
        ((u8 *)D_800E0900[i])[0x14] = 1;
    }
}

void func_1519BF8C(void) {
    func_10010F30(0x1AA, 0x7FFF, 0x40, 0, 0);
}

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    char padC[0x28 - 0xC];
} Struct1519BFBCVec;

typedef struct {
    char pad_0x0[0x130];
    u16 field_0x130;
} Struct1519BFBCSound;

typedef struct {
    char pad0[0x2C];
    s8 unk2C;
    s8 unk2D;
    char pad2E[0x94 - 0x2E];
    Struct1519BFBCVec *unk94;
    Struct1519BFBCSound *field_0x98;
} Struct1519BFBC;

void func_1519BFBC(Struct1519BFBC *arg0) {
    Struct1519BFBCVec *temp_v1;
    Struct1519BFBCSound *temp_v2;
    u16 temp_a0;
    s32 temp_t6;
    s32 temp_t7;

    temp_v2 = arg0->field_0x98;
    temp_v1 = arg0->unk94;

    if (arg0->unk2C != 0) {
        temp_a0 = temp_v2->field_0x130;
        if (temp_a0 != 0) {
            temp_t6 = 0x1388;
            temp_t7 = 0x1F4;
            func_1000F91C(temp_a0, 0x7FFF, 0, 0, 0,
                          ((Struct1519BFBCVec *)((u8 *)temp_v1 + (arg0->unk2D * 0x28)))->unk0,
                          ((Struct1519BFBCVec *)((u8 *)temp_v1 + (arg0->unk2D * 0x28)))->unk4,
                          ((Struct1519BFBCVec *)((u8 *)temp_v1 + (arg0->unk2D * 0x28)))->unk8,
                          temp_t7, temp_t6);
        }
    }
}

void func_1519C06C(Struct1519BFBC *arg0) {
    Struct1519BFBCSound *temp = arg0->field_0x98;
    u16 val = temp->field_0x130;
    if (val != 0) {
        func_100111C8(val);
    }
}

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
} Struct1519C09CData;

struct225 *func_1519C09C(s32 arg0, f32 *arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, u8 arg6, s32 arg7) {
    struct225 *temp_v0;
    Header header;
    Header2 header2;
    s32 sp5C;
    Struct1519C09CData data;

    data.unk0 = 35.0f;
    data.unk4 = 5.0f;
    sp5C = arg0;
    header.unk0 = 2;
    header.unk1 = 2;
    header.unk2 = 0x12C;
    header.unk4 = 0x22;
    data.unk8 = 110.0f;
    data.unkC = 1.0f;
    data.unk10 = 0.0f;
    data.unk14 = 7.0f;
    data.unk18 = D_800A8AF8;
    data.unk1C = 127.0f;
    header2.unk0 = arg1[0];
    header2.unk4 = arg1[1];
    header2.unk8 = arg1[2];

    temp_v0 = func_151602C0(&header, &header2, arg2, arg3, arg4, arg5, 0xFF, 0, 0x24, arg6, arg7);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x18, &data, sizeof(data));
        memcpy((u8 *)temp_v0 + 0x38, &sp5C, sizeof(sp5C));
    }
    return temp_v0;
}

void func_1519C258(s32);
void func_151617C4(s32);

void func_1519C200(s32 arg0) {
    func_1519C258(arg0);
    func_151617C4(arg0);
}

void func_151617E4(s32);

void func_1519C22C(s32 arg0) {
    func_1519C258(arg0);
    func_151617E4(arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1C2C60/func_1519C258.s")

typedef struct {
    f32 x;
    f32 y;
    f32 z;
} Vec3f26C;

typedef struct {
    /* 0x00 */ Vec3f26C vel;
    /* 0x0C */ Vec3f26C avel;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
} Struct1519C26CSub;

typedef struct {
    char pad0[0x34];
    /* 0x34 */ Vec3f26C pos;
    /* 0x40 */ Vec3f26C rot;
} Struct1519C26C;

s32 func_1519C26C(Struct1519C26C *arg0) {
    f32 dtSq;
    Vec3f26C vel;
    Vec3f26C avel;
    Vec3f26C acc;
    Vec3f26C aacc;
    Struct1519C26CSub *p = (Struct1519C26CSub *)((char *)arg0 + 0x110);

    dtSq = D_800BE9A4 * D_800BE9A4;
    vel = p->vel;
    avel = p->avel;
    p->vel.y += p->unk18 * D_800BE9A4;
    p->avel.y += p->unk18 * D_800BE9A4;
    {
        s32 i;

        for (i = D_800BE9E4; i > 0; i--) {
            p->vel.x *= p->unk1C;
            p->vel.y *= p->unk1C;
            p->vel.z *= p->unk1C;
            p->avel.x *= p->unk20;
            p->avel.y *= p->unk20;
            p->avel.z *= p->unk20;
        }
    }
    acc.x = (p->vel.x - vel.x) * D_800BE9A8;
    acc.y = (p->vel.y - vel.y) * D_800BE9A8;
    acc.z = (p->vel.z - vel.z) * D_800BE9A8;
    aacc.x = (p->avel.x - avel.x) * D_800BE9A8;
    aacc.y = (p->avel.y - avel.y) * D_800BE9A8;
    aacc.z = (p->avel.z - avel.z) * D_800BE9A8;
    arg0->pos.x += vel.x * D_800BE9A4 + 0.5f * acc.x * dtSq;
    arg0->pos.y += vel.y * D_800BE9A4 + 0.5f * acc.y * dtSq;
    arg0->pos.z += vel.z * D_800BE9A4 + 0.5f * acc.z * dtSq;
    arg0->rot.x += avel.x * D_800BE9A4 + 0.5f * aacc.x * dtSq;
    arg0->rot.y += avel.y * D_800BE9A4 + 0.5f * aacc.y * dtSq;
    arg0->rot.z += avel.z * D_800BE9A4 + 0.5f * aacc.z * dtSq;
    return 1;
}

typedef struct {
    char pad0[0x24];
    f32 unk24;
    s16 unk28;
    s16 unk2A;
} C4E4Sub;

typedef struct {
    char pad0[0x1C];
    s16 unk1C;
    char pad1E[0x2C - 0x1E];
    f32 unk2C;
    f32 unk30;
    char pad34[0x5C - 0x34];
    u8 unk5C;
} C4E4Struct;

s32 func_1519C4E4(C4E4Struct *arg0) {
    s32 i;
    C4E4Sub *p = (C4E4Sub *)((char *)arg0 + 0x110);

    for (i = D_800BE9E4; i > 0; i--) {
        arg0->unk2C = arg0->unk2C - arg0->unk2C * p->unk24;
        arg0->unk30 = arg0->unk30 - arg0->unk30 * p->unk24;
    }
    if (arg0->unk1C < p->unk28) {
        s32 a1 = arg0->unk1C * p->unk2A;
        if (a1 < arg0->unk5C) {
            arg0->unk5C = a1;
        }
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1C2C60/func_1519C56C.s")

struct ConkerStruct1519C910_inner {
    char pad0[0x84];
    u16 unk84;
};

struct ConkerStruct1519C910 {
    struct ConkerStruct1519C910_inner *unk0;
    char pad4[0x154];
    s32 unk158;
    s32 unk15C;
};

struct ConkerStruct1519C910Outer {
    char pad0[0x98];
    struct ConkerStruct1519C910 *unk98;
};

s32 func_1519C910(struct ConkerStruct1519C910Outer *arg0) {
    struct ConkerStruct1519C910 *p = arg0->unk98;
    struct ConkerStruct1519C910_inner *q = p->unk0;
    u16 v = q->unk84;

    if (v != p->unk158) {
        if (v != p->unk15C) {
            return 0;
        }
    }
    return 1;
}

s32 func_1519C948(s32 arg0) {
    func_1519CDB0(arg0, 0.25f, 0x1C);
    return 0;
}

s32 func_1519C970(s32 arg0) {
    func_1519CDB0(arg0, 0.5f, 0x1D);
    return 0;
}

s32 func_1519C998(s32 arg0) {
    func_1519CDB0(arg0, 0.2f, 0x1D);
    return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1C2C60/func_1519C9C4.s")

struct Sub1519CD64 {
    s32 unk0;
    u8 unk4;
    u8 pad5[0x36];
    u8 unk3B;
};

struct Obj1519CD64 {
    u8 padD[0xD];
    u8 unkD;
    s16 unkE;
    u8 pad10[0x18];
    struct Sub1519CD64 *unk28;
    u8 unk2C;
};

void func_1519CD64(struct Obj1519CD64 *a0) {
    struct Sub1519CD64 *v0 = a0->unk28;

    if (v0->unk0 != 0 && v0->unk4 != 0xFF && v0->unk3B == a0->unk2C) {
        return;
    }
    a0->unkE = -1;
    a0->unkD |= 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1C2C60/func_1519CDB0.s")
