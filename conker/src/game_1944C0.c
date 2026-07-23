#include <ultra64.h>

#include "functions.h"
#include "variables.h"

extern void (*D_8008CA20[])(struct102 *);
extern void (*D_8008C9C8[])(struct102 *);
extern void (*D_8008CB64)(void);
extern void (*D_8008CB70)(void);

extern s16 D_800DD1C0;
extern s16 D_800DD1C2;
extern s16 D_800DD1C4;
extern s16 D_800DD1C6;

typedef struct {
    u8 pad0[0x10];
    Mtx mtx[2];
    f32 unk90;
    f32 unk94;
    f32 unk98;
    f32 unk9C;
    f32 unkA0;
    f32 unkA4;
    u8 padA8[0x18];
    f32 unkC0;
    f32 unkC4;
    f32 unkC8;
    u8 padCC[0x4];
    Gfx *display_list;
    u8 padD4[0x11];
    u8 prim_alpha;
    u8 tile_ult;
    u8 padE7[0x5];
    u8 render_mode;
    u8 combine_mode;
} Struct15168C4C;

Gfx *func_15142FBC(Gfx *gfx, s32 arg1, s32 arg2, u8 *arg3);

#define WGFX15168C4C(pkt, a, b)     \
{                                   \
    Gfx *_g = (Gfx *)(pkt);         \
    _g->words.w0 = (u32)(a);        \
    _g->words.w1 = (u32)(b);        \
}

#define WGSPMATRIX15168C4C(pkt, mtx)        WGFX15168C4C(pkt, 0xDA380003, mtx)
#define WGSPDISPLAYLIST15168C4C(pkt, dl)    WGFX15168C4C(pkt, 0xDE000000, dl)

struct Some15171F04 {
    u8 pad0[4];
    u8 unk4;
    u8 pad5;
    u16 unk6;
    u16 unk8;
};

typedef struct {
    char pad_0[0x98];
    s16 field_0x98;
    s16 field_0x9A;
    char pad_0x9C[0xC];
    u16 field_0xA8;
    char pad_0xAA[0x6];
    u8 field_0xB0;
    char pad_0xB1[0x1];
    s8 field_0xB2;
} GameAnimObject;

typedef struct {
    char pad_0[0x1];
    u8 field_0x1;
    char pad_0x2[0xA];
    u8 field_0xC;
    char pad_0xD[0x3];
    u8 field_0x10;
    char pad_0x11[0x12];
    u8 field_0x23;
    char pad_0x24[0x4];
    char pad_0x28[0x20];
    u8 field_0x48;
} GameObjectHeader;

extern struct Some15171F04 *D_8008CA4C[];

void func_15169070(s32, s32, s32, u8);

#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_15167010.s")
// PERMUTER CANDIDATE (best 405): target uses OSR limit `addiu s2,s0,0x1484` (base-relative)
// + phantom saved reg s1; can't trigger the `<`-preserving strength-reduction form from C.
// Closest form:
// void func_15167010(void) {
//     void (*func)(void);
//     struct115 *p;
//     for (p = D_8008B4A8; p < D_8008B4A8 + 101; p++) {
//         func = (void (*)(void))p->unk18;
//         if (func != NULL) { func(); }
//     }
// }

void func_1516706C(void) {
    void (**funcp)(void);
    void (**end)(void);
    void (*func)(void);

    funcp = &D_8008CB64; end = &D_8008CB70;
    do {
        func = *funcp;
        if (func != NULL) {
            func();
        }
        funcp++;
    } while (funcp != end);
}
extern u8 D_800DCE50[];

// PERMUTER CANDIDATE / JUSTREG (best 25): structure + strength-reduction byte-perfect.
// Only diff: the innermost do-while's loop-rotated call target `func = p->unk0` lands in
// v0 (named local) but the target uses temp t9 (software-pipelined reload); the trailing
// `D_800DD190--` then uses t0 vs t9 as a cascade. func must load BEFORE the store to fill
// the jalr delay slot (needs the named local), which pins it to v0. Inline call (t9) breaks
// the delay-slot fill (270). Not steerable from C. Best reconstruction:
// void func_151670C0(void) {
//     s32 s6; s32 s5; struct115 *p; struct102 *node; void (*func)(struct102 *);
//     for (s6 = 0; s6 != 2; s6++) {
//         p = D_8008B4A8;
//         for (s5 = 0; s5 != 0x65; s5++, p++) {
//             if (p->unk0 != NULL) {
//                 node = ((struct102 *(*)[104])D_800DCE50)[s6][s5];
//                 D_800DD190++;
//                 if (node != NULL) {
//                     do {
//                         func = p->unk0;
//                         ((struct102 **)D_800DD198)[D_800DD190] = (struct102 *)node->unk8;
//                         func(node);
//                         node = ((struct102 **)D_800DD198)[D_800DD190];
//                     } while (node != NULL);
//                 }
//                 D_800DD190--;
//             }
//         }
//     }
// }
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_151670C0.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_151671E8.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_15167310.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_151674F8.s")
void func_15168A4C(s32 *arg0, s32 arg1);

s32 func_15167A68(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    GameObjectHeader *temp;

    temp = (GameObjectHeader *)func_10003C6C(arg2, 1, arg3, 0, (u8)arg5);
    if (temp != 0) {
        temp->field_0x1 = arg1;
        func_15168A4C((s32 *)temp, arg0);
        temp->field_0xC = *((u8 *)&arg4 + 3);
    }
    return (s32)temp;
}

void func_15167AD8(s32 arg0, s32 arg1, s32 arg2) {
    GameObjectHeader *temp;

    temp = (GameObjectHeader *)func_15167A68(3, arg2, 0x28, 0, (u8)arg1, 1);
    if (temp != 0) {
        bcopy(arg0, &temp->field_0x10, 0x18);
        temp->field_0x23 = 0xFF;
    }
}
void func_15167B44(struct102 *arg0) {
    s32 temp_v0;
    s32 temp_v1;
    s32 temp_a1;
    s32 temp_a2;

    temp_v0 = *(u8 *)((u8 *)arg0 + 0x24);
    if (temp_v0 != 0) {
        D_8008CA20[temp_v0](arg0);
    }

    temp_v1 = *(s8 *)((u8 *)arg0 + 0x22);
    if (temp_v1 > 0) {
        temp_v0 = *(u8 *)((u8 *)arg0 + 0x23);
        if (temp_v1 < temp_v0) {
            *(u8 *)((u8 *)arg0 + 0x23) = temp_v0 - temp_v1;
        } else {
            *(s16 *)((u8 *)arg0 + 0x14) = *(u8 *)(*(s32 *)((u8 *)arg0 + 0x10) + 4) << 8;
        }
    } else if (temp_v1 < 0) {
        temp_a1 = -temp_v1;
        temp_a2 = *(s16 *)((u8 *)arg0 + 0x14);
        if ((temp_a2 / 0x100) >= (*(u8 *)(*(s32 *)((u8 *)arg0 + 0x10) + 4) - 1)) {
            temp_v0 = *(u8 *)((u8 *)arg0 + 0x23);
            if (temp_a1 < temp_v0) {
                *(u8 *)((u8 *)arg0 + 0x23) = temp_v0 - temp_a1;
                *(s16 *)((u8 *)arg0 + 0x14) = temp_a2 - *(s16 *)((u8 *)arg0 + 0x16);
            }
        }
    }

    *(s16 *)((u8 *)arg0 + 0x14) += *(s16 *)((u8 *)arg0 + 0x16);
    if ((*(s16 *)((u8 *)arg0 + 0x14) / 0x100) >= *(u8 *)(*(s32 *)((u8 *)arg0 + 0x10) + 4)) {
        func_1516972C(arg0);
    }
}
// PERMUTER CANDIDATE / near-miss (best ~1090): full reconstruction below; stack frame (0x70)
// and locals sp50@0x50, sp5C@0x5C match. Blocker: the `mode` value (3/9) is MEMORY-resident at
// 0x48 in the target (spilled, double beq+bne, sw/lw 0x48(sp)); a clean `s32 mode` stays in a
// register (single branch). Forcing memory via the func_15168C4C idiom `*(s32*)((u8*)&mode - 4)`
// gets memory-residence but lands the anchor at 0x6C (slot 0x68, CSE'd base) not 0x4C/0x48 absolute;
// register renames cascade from the misaligned mode block. Needs the permuter (or exact anchor
// placement). ObjC58: unk10=s32** (arg1 of E24 + arg6=(*unk10)[unk14>>8]); unk14 s16; unk18/1A/1C/
// 1E/20 s16; unk22 s8; unk23 u8. sp5C is {s16 x,y,z,unk6,unk8; u8 unkA; u8 unkD} copied from those.
// Gfx *func_15167C58(Gfx *arg0, ObjC58 *arg1, s32 arg2) {
//     s32 mode; StructC58a sp5C; StructC58b sp50; Gfx *gfx; s32 **p = arg1->unk10;
//     sp50.unk0 = 1;
//     gfx = func_15142E24(arg0, (s32)p, arg1->unk14 << 8, 2, 0x100, 0x100,
//                         (*p)[arg1->unk14 >> 8], 5, (s32)&sp5C, (u8 *)&sp50, 3);
//     sp5C.unk0 = arg1->unk18; sp5C.unk2 = arg1->unk1A; sp5C.unk4 = arg1->unk1C;
//     sp5C.unk6 = arg1->unk1E; sp5C.unk8 = arg1->unk20; sp5C.unkA = arg1->unk23; sp5C.unkD = 0;
//     if (0xFF != arg1->unk22) { *(s32*)((u8*)&mode - 4) = 3; } else { *(s32*)((u8*)&mode - 4) = 9; }
//     gfx = func_15142FBC(gfx, 0x2C00,
//         (D_800A4AC8[*(s32*)((u8*)&mode-4)].unk4 | D_800A4AC8[*(s32*)((u8*)&mode-4)].unk0) | 4, (u8*)&sp50);
//     return (Gfx *)func_15095760(gfx, &sp5C);
// }
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_15167C58.s")
s32 func_15167D84(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    GameObjectHeader *temp;

    temp = (GameObjectHeader *)func_15167A68((arg1 == 0) ? 5 : 0x42, arg5, arg2 + 0x50, 0, *((u8 *)&arg4 + 3), 1);
    if (temp == 0) {
        return (s32)temp;
    }
    bcopy(arg0, &temp->field_0x10, 0x38);
    temp->field_0x48 = *((s8 *)&arg3 + 3);
    return (s32)temp;
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_15167E0C.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_15168118.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_1516865C.s")
// PERMUTER CANDIDATE (best 3095): leaf func; logic decoded fully (strided 8x0x10 init loop +
// two conditional value-swaps keyed on obj->0x98 flags 0x80/0x100 + field mirroring). Target
// homes a1/a2/a3 to caller arg slots (0xc/0x10/0x14) in a leaf while keeping them register-
// resident, an IDO arg-home idiom not reproducible from C; register allocation also diverges.
// Best reconstruction:
// void func_1516865C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4) {
//     u8 *obj = (u8 *)arg0; s32 v0_val, v1_val, t1_val, t2_val, flags, i; s16 tmp; u8 *q; u8 t0b;
//     arg1 &= 0xFF; arg2 &= 0xFF; arg3 &= 0xFF;
//     v0_val = 0x2000; t1_val = 0x2000;
//     v1_val = ((s32)((D_8008CA4C[obj[0xA0]]->unk8 + 0x100) << 21)) >> 16;
//     t2_val = ((s32)((D_8008CA4C[obj[0xA0]]->unk6 + 0x100) << 21)) >> 16;
//     t0b = (u8)arg4; q = obj; i = 0;
//     do { i++; q += 0x40;
//         *(s16*)(q-0x2A)=0; q[-0x24]=arg1; q[-0x23]=arg2; q[-0x22]=arg3; q[-0x21]=t0b;
//         *(s16*)(q-0x1A)=0; q[-0x14]=arg1; q[-0x13]=arg2; q[-0x12]=arg3; q[-0x11]=t0b;
//         *(s16*)(q-0x0A)=0; q[-0x04]=arg1; q[-0x03]=arg2; q[-0x02]=arg3; q[-0x01]=t0b;
//         *(s16*)(q-0x3A)=0; q[-0x34]=arg1; q[-0x33]=arg2; q[-0x32]=arg3; q[-0x31]=t0b;
//     } while (i != 2);
//     flags = *(u16*)(obj+0x98);
//     if (flags & 0x80)  { v0_val = ((s32)((D_8008CA4C[obj[0xA0]]->unk8 + 0x100) << 21)) >> 16; v1_val = 0x2000; }
//     if (flags & 0x100) { t1_val = ((s32)((D_8008CA4C[obj[0xA0]]->unk6 + 0x100) << 21)) >> 16; t2_val = 0x2000; }
//     *(s16*)(obj+0x68)=t1_val; tmp=*(s16*)(obj+0x68);
//     *(s16*)(obj+0x7A)=v0_val; *(s16*)(obj+0x78)=t2_val;
//     *(s16*)(obj+0x28)=tmp; *(s16*)(obj+0x58)=tmp; *(s16*)(obj+0x18)=tmp;
//     tmp=*(s16*)(obj+0x7A); *(s16*)(obj+0x5A)=v1_val; *(s16*)(obj+0x88)=0;
//     *(s16*)(obj+0x3A)=tmp; *(s16*)(obj+0x6A)=tmp; *(s16*)(obj+0x2A)=tmp;
//     tmp=*(s16*)(obj+0x78); *(s16*)(obj+0x9C)=0; *(s16*)(obj+0x9E)=0;
//     *(s16*)(obj+0x38)=tmp; *(s16*)(obj+0x48)=tmp; *(s16*)(obj+0x8)=tmp;
//     tmp=*(s16*)(obj+0x5A); *(s16*)(obj+0x1A)=tmp; *(s16*)(obj+0x4A)=tmp; *(s16*)(obj+0xA)=tmp;
// }
s32 func_15168800(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp;

    temp = func_15167A68(0xE, arg2, 0xB8, 1, *((u8 *)&arg1 + 3), 1);
    if (temp == 0) {
        return 0;
    }
    bcopy(arg0, (void *)(temp + 0x10), 0xA8);
    return temp;
}
void func_15168870(GameAnimObject *arg0) {
    s32 temp_v0;
    s32 temp_v1;
    u8 temp_a1;
    s16 temp_a2;
    void (*func)(struct102 *);

    temp_a2 = arg0->field_0x9A;
    if (temp_a2 != 0) {
        temp_a1 = D_8008CA4C[arg0->field_0xB0]->unk4;
        temp_v1 = temp_a1;
        temp_v1 <<= 8;
        arg0->field_0x98 += temp_a2 * D_800BE9E4;
        temp_v0 = arg0->field_0x98;
        temp_v1 -= 1;
        if (temp_v1 < temp_v0) {
            if (arg0->field_0xA8 & 0x40) {
                arg0->field_0x98 = temp_v1 - (temp_v0 % temp_v1);
                arg0->field_0x9A = -temp_a2;
            } else if (arg0->field_0xA8 & 4) {
                arg0->field_0x98 = -1;
            } else {
                do {
                    arg0->field_0x98 = temp_v0 - temp_v1;
                    temp_v0 = arg0->field_0x98;
                } while (temp_v1 < temp_v0);
            }
        } else if (temp_v0 < 0) {
            if (arg0->field_0xA8 & 0x40) {
                arg0->field_0x98 = -temp_v0 % temp_v1;
                arg0->field_0x9A = -temp_a2;
            } else if (arg0->field_0xA8 & 4) {
                arg0->field_0x98 = -1;
            } else {
                do {
                    arg0->field_0x98 = temp_v0 + temp_v1;
                    temp_v0 = arg0->field_0x98;
                } while (temp_v0 < 0);
            }
        }
    }

    temp_v0 = arg0->field_0xB2;
    if (temp_v0 != -1) {
        func = D_8008C9C8[temp_v0];
        if (func != NULL) {
            func((struct102 *)arg0);
        }
    }

    if (arg0->field_0x98 == -1) {
        func_1516972C((struct102 *)arg0);
    }
}
void func_15168A2C(s32 arg0) {
    func_15168B10(arg0, 0);
}
extern u8 D_800DCE50[];

void func_15168A4C(s32 *arg0, s32 arg1) {
    s32 idx;
    s32 t;
    s32 *temp;

    idx = ((u8 *)arg0)[1];
    temp = (s32 *)(&D_800DCE50[(idx * 0x1A0) + (arg1 * 4)]);
    t = *temp & 0xFFFFFFFFFFFFFFFFu;
    arg0[2] = t;
    if (t != 0) {
        ((s32 *)t)[1] = (s32)arg0;
    }
    ((u8 *)arg0)[0] = (u8)arg1;
    arg0[1] = 0;
    *temp = (s32)arg0;
}
void func_15168A9C(struct12 *arg0) {
    s32 temp_v0 = *((u8 *)arg0 + 1);
    s32 temp_v1 = *(u8 *)arg0;
    u8 *temp_t9 = D_800DCE50;
    struct12 **temp_a1 = (struct12 **)&temp_t9[(temp_v0 * 0x1A0) + (temp_v1 * 4)];
    struct12 *temp_v0_2;

    if (arg0 == *temp_a1) {
        *temp_a1 = *(struct12 **)((s32)arg0 + 8);
    }
    temp_v0_2 = *(struct12 **)((s32)arg0 + 8);
    if (temp_v0_2 != NULL) {
        *(struct12 **)((s32)temp_v0_2 + 4) = *(struct12 **)((s32)arg0 + 4);
    }
    temp_v0_2 = *(struct12 **)((s32)arg0 + 4);
    if (temp_v0_2 != NULL) {
        *(struct12 **)((s32)temp_v0_2 + 8) = *(struct12 **)((s32)arg0 + 8);
    }
}
// void *func_15168A9C(struct12 *arg0) {
//     void *temp_a1;
//     void *temp_v0;
//     void *temp_v0_2;
//
//     temp_a1 = (arg0->unk1 * 0x1A0) + (arg0->unk0 * 4) + 0x800DCE50;
//     if (arg0 == *temp_a1) {
//         *temp_a1 = (void *) arg0->unk8;
//     }
//     temp_v0_2 = arg0->unk8;
//     if (temp_v0_2 != 0) {
//         temp_v0_2->unk4 = (void *) arg0->unk4;
//     }
//     temp_v0 = arg0->unk4;
//     if (temp_v0 != 0) {
//         temp_v0->unk8 = (void *) arg0->unk8;
//     }
//     return temp_v0;
// }


void func_15168B10(s32 arg0, s32 arg1) {
    func_15168A9C(arg0);
    func_15168A4C(arg0, arg1);
}

// PERMUTER CANDIDATE / JUSTREG (best 1057): structure fully matches (both 0x14 stores kept via
// RMW forwarding). Remainder is a v0<->t6 register rotation on `lo`/`masked` + constant-hoist
// scheduling (li 0x1E vs lui order) that no C form pinned. Best reconstruction:
// permuter NO ZERO, best 305 (improved from 1057)
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_15168B44.s")
// void func_15168B44(struct102 *arg0) {
//     s32 lo = *(s32 *)((u8 *)arg0 + 0x14) & 0xFFFF;
//     s32 hi;
//     s32 max;
//     if (lo != 0) {
//         *(s32 *)((u8 *)arg0 + 0x14) &= 0xFFFF0000;
//         *(s16 *)((u8 *)arg0 + 0x38) = 0x1E;
//         *(s32 *)((u8 *)arg0 + 0x14) |= (u16)(lo - 1);
//     } else {
//         max = *(u8 *)((u8 *)arg0 + 0x3F);
//         hi = (*(s32 *)((u8 *)arg0 + 0x14) >> 16) & 0xFFFF;
//         if (hi < max) {
//             *(u8 *)((u8 *)arg0 + 0x3F) = max - hi;
//             *(s16 *)((u8 *)arg0 + 0x38) = 0x1E;
//         } else {
//             *(s16 *)((u8 *)arg0 + 0x38) = 0;
//         }
//     }
// }
void func_15168BAC(struct102 *arg0) {
    u8 temp_v0;

    temp_v0 = *(u8 *)((u8 *)arg0 + 0xE4);
    if (temp_v0 != 0) {
        D_8008CA20[temp_v0](arg0);
    }
}
s32 func_15167A68(s32, s32, s32, s32, s32, s32);

void func_15168BE4(s32 *arg0, s32 arg1, s32 arg2) {
    s32 temp;

    if (arg0[0x10] != 0) {
        temp = func_15167A68(0x10, arg2, 0xF0, 1, (u8)arg1, 1);
        if (temp != 0) {
            bcopy(arg0, (void *)(temp + 0x90), 0x60);
        }
    }
}
Gfx *func_15168C4C(Gfx *gfx, Struct15168C4C *obj, s32 arg2) {
    s32 mode1;
    u8 update;
    s16 *zero_ptr;
    s16 *copy_ptr;

    func_15043D90((Mtx *)((u8 *)obj + (D_800BE9C0 << 6) + 0x10), obj->unk9C, obj->unkA0, obj->unkA4,
        obj->unkC0, obj->unkC4, obj->unkC8, obj->unk90, obj->unk94, obj->unk98);

    zero_ptr = &D_800DD1C4;
    copy_ptr = &D_800DD1C2;

    gDPPipeSync(gfx++);
    gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, obj->prim_alpha);
    D_800DD1C6 = obj->prim_alpha;
    *zero_ptr = 0;
    *copy_ptr = *zero_ptr;
    D_800DD1C0 = *copy_ptr;
    gDPSetEnvColor(gfx++, 0, 0, 0, 0);
    gDPSetTileSize(gfx++, 0, 2, obj->tile_ult, 0x7E, 0xFE);

    switch (obj->render_mode) {
    case 1:
        *(s32 *)((u8 *)&mode1 - 4) = 0x552230;
        break;
    case 2:
        *(s32 *)((u8 *)&mode1 - 4) = 0x504A50;
        break;
    }

    *(u8 *)((u8 *)&update - 4) = 0;
    gfx = func_15142FBC(gfx, 0x8ACA0, *(s32 *)((u8 *)&mode1 - 4), (u8 *)((u8 *)&update - 4));

    if (obj->combine_mode == 1) {
        gDPSetCombine(gfx++, 0x123824, 0xFF73FFFF);
    }

    WGSPMATRIX15168C4C(gfx++, (u8 *)obj + (D_800BE9C0 << 6) + 0x10);
    WGSPDISPLAYLIST15168C4C(gfx++, obj->display_list);

    return gfx;
}
void func_15168E34(s32 *arg0, s32 arg1) {
    s32 val = *arg0;
    if ((val & 0x0F000000) == 0) {
        *arg0 = val + arg1;
    }
}
typedef struct { s8 unk0; s8 unk1; s8 unk2; u8 unk3; u32 unk4; } Struct15168F08;

// PERMUTER CANDIDATE / JUSTREG (best 717): mirrors matched sibling func_15168F08 but calls
// func_15168E34; the call forces saved-reg promotion and a delay-slot reschedule (target puts
// a0=&p->unk4 in the first beq slot + distributes i++ into the bnel slots) that drives a whole-
// function saved-register rotation (base s1 vs s4). Not steerable from C. Best reconstruction:
// permuter NO ZERO, best 360 (improved from 717)
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_15168E54.s")
// void func_15168E54(Struct15168F08 *arg0, s32 arg1) {
//     s32 i; Struct15168F08 *p; s8 tag;
//     i = 0; p = arg0;
//     if (arg0->unk0 == -0x21) { return; }
//     p = &arg0[i]; tag = p->unk0;
//     do {
//         i++;
//         if ((p->unk0 == 1) || ((p->unk0 == -0x24) && (p->unk3 == 0xE))) {
//             func_15168E34((s32 *)&p->unk4, arg1);
//         }
//         p = &arg0[i];
//         do { tag = p->unk0; } while (0);
//     } while (p->unk0 != -0x21);
// }

void func_15168F08(Struct15168F08 *arg0, s32 arg1) {
    s32 i;
    Struct15168F08 *p;
    s8 tag;

    i = 0;
    p = arg0;
    if (arg0->unk0 == -0x21) {
        return;
    }
    p = &arg0[i];
    tag = p->unk0;
    do {
        i++;
        if ((p->unk0 == 1) || ((p->unk0 == -0x24) && (p->unk3 == 0xE))) {
            p->unk4 = p->unk4 & 0xFFFFFF;
            p->unk4 += arg1;
        }
        p = &arg0[i];
        do {
            tag = p->unk0;
        } while (0);
    } while (p->unk0 != -0x21);
}
void func_15168F84(s32 arg0, s32 *arg1, s32 *arg2) {
    if (arg0 == 0) {
        *arg1 = 0x1;
        *arg2 = 0x41;
    } else if (arg0 == 1) {
        *arg1 = 0x42;
        *arg2 = 0x4F;
    } else if (arg0 == 2) {
        *arg1 = 0x50;
        *arg2 = 0x58;
    } else if (arg0 == 3) {
        *arg1 = 0x59;
        *arg2 = 0x5C;
    } else if (arg0 == 5) {
        *arg1 = 0x61;
        *arg2 = 0x63;
    } else if (arg0 == 6) {
        *arg1 = 0x64;
        *arg2 = 0x65;
    } else {
        *arg1 = 0x5D;
        *arg2 = 0x60;
    }
}
void func_15169040(s32 arg0, u8 arg1) {
    func_15169070(0, 0x68, arg0, arg1);
}
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_15169070.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_15169260.s")
#pragma GLOBAL_ASM("asm/nonmatchings/game_1944C0/func_1516944C.s")
void func_151695F0(struct127 *arg0, u8 arg1) {
    struct {
        s32 unk0;
        u8 unk4;
    } sp18;

    sp18.unk0 = (s32)arg0;
    sp18.unk4 = arg0->unique_id;
    func_15169040((s32)&sp18, arg1);
}
void func_1516962C(s32 arg0, struct127 *arg1, u8 arg2) {
    struct {
        s32 unk0;
        u8 unk4;
    } sp18;
    sp18.unk0 = (s32)arg1;
    sp18.unk4 = arg1->unique_id;
    func_1516944C(arg0, (s32)&sp18, arg2);
}
s32 func_15169668(s32 arg0, s32 arg1, s32 arg2, s32 arg3) {
    D_800D2DAB = 1;
    return arg0;
}
void func_1516968C(struct102 *arg0, u8 *arg1, u8 arg2) {
    if (arg2 == 0xF || arg2 == 0x10) {
        if (arg1[0] == ((u8 *)arg0)[0xC]) {
            func_1516972C(arg0);
        }
    }
}

void func_151696DC(struct102 *arg0) {
    s8 i;

    for (i = 0; i < D_800DD190; i++) {
        if ((s32)arg0 == ((s32 *)D_800DD198)[i]) {
            ((s32 *)D_800DD198)[i] = arg0->unk8;
        }
    }
}

void func_1516972C(struct102 *arg0) {
    void (*func)(struct102 *arg0);
    func_151696DC(arg0);

    if (arg0->unk0 >= 2) {
        func = D_8008B4D0[arg0->unk0].unk0;
        if (func != NULL) {
            func(arg0);
            return;
        }
        func_15169804(arg0);
    }
}

void func_1516979C(struct102 *arg0) {
    void (*func)(struct102 *arg0);

    func_151696DC(arg0);
    func = D_8008B4D4[arg0->unk0].unk0;
    if (func != NULL) {
        func(arg0);
        return;
    }
    func_15169824(arg0);
}

void func_15169804(struct102 *arg0) {
    func_15168B10(arg0, 1);
}

void func_15169824(struct102 *arg0) {
    func_15168A9C(arg0);
    func_10004074(arg0);
}

void func_15169850(s32 arg0, u8 arg1, s32 arg2, s32 arg3, s32 arg4) {
    if (arg1 == 0) {
        if (*(s32 *)arg0 == *(s32 *)arg2 || *(u8 *)(arg0 + 4) == *(u8 *)arg3) {
            func_1516972C((struct102 *)arg4);
        }
    } else if (arg1 == 0x2D) {
        s32 v = *(s32 *)arg0;
        if (v == *(s32 *)arg2) {
            *(s32 *)arg2 = *(s32 *)(arg0 + 4);
            *(u8 *)arg3 = *(u8 *)(arg0 + 9);
        } else if (*(s32 *)(arg0 + 4) == *(s32 *)arg2) {
            *(s32 *)arg2 = v;
            *(u8 *)arg3 = *(u8 *)(arg0 + 8);
        }
    }
}
