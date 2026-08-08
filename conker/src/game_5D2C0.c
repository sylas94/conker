#include <ultra64.h>
#define func_15083568 func_15083568_orig
#include "functions.h"
#undef func_15083568
#include "variables.h"

extern f32 D_80097B68;
extern f32 D_800970DC;
extern u8 D_800BEA0C;
extern s32 D_800902BC[];
void func_1000FD38(void *, void *, s32);
s32 func_15033BDC();

typedef struct Game5D2C0RenderState {
    u8 pad_0[0x2];
    u8 field_0x02;
    u8 pad_0x03[0x13];
    u8 field_0x16;
    u8 pad_0x17[0x29];
    f32 field_0x40;
} Game5D2C0RenderState;

Game5D2C0RenderState *func_15083568(struct127 *, s32, f32, s32);
extern void func_150A7A48(f32 arg0[4][4], f32 arg1[4][4], f32 arg2[4][4]);
extern void func_1503E5F8();
extern void *allocate_memory(s32 size, s32 arg1, s32 arg2, s32 arg3);
extern void func_10004074(void *arg0);
void func_15031C14(void *arg0);
void func_1503F7B8(void *arg0);
void func_1518CA04(s32 arg0);
s32 func_1502FE10(s32 arg0, void *arg1, void *arg2, void *arg3, void *arg4, void *arg5, void *arg6);
s32 func_1503F62C(s32 arg0, s32 arg1, void *arg2, void *arg3, void *arg4, void *arg5, void *arg6);

typedef struct Game5D2C0EffectState {
    u8 pad_0[0x1];
    u8 field_0x01;
    u8 field_0x02;
    u8 pad_0x03[0x1F];
    s16 field_0x22;
    u8 pad_0x24[0x14];
    s32 field_0x38;
    s32 field_0x3C;
} Game5D2C0EffectState;

typedef struct Game5D2C0EventState {
    u8 pad_0[0x5];
    u8 field_0x05;
} Game5D2C0EventState;

typedef struct Game5D2C0FlagState {
    u8 pad_0[0x3];
    u8 field_0x03;
} Game5D2C0FlagState;

typedef struct Game5D2C0ActorState {
    u8 pad_0[0x11A];
    u8 field_0x11A;
    u8 pad_0x11B[0x81];
    u16 field_0x19C;
} Game5D2C0ActorState;

typedef struct Game5D2C0PositionState {
    s32 field_0x00;
    u8 pad_0x04[0x10];
    f32 field_0x14;
    f32 field_0x18;
    f32 field_0x1C;
    u8 pad_0x20[0x64];
    u16 field_0x84;
    u8 pad_0x86[0x27];
    u8 field_0xAD;
    u8 pad_0xAE[0x6A];
    f32 field_0x118;
    u8 pad_0x11C[0x64];
    f32 field_0x180;
    u8 pad_0x184[0x198];
    Game5D2C0ActorState *field_0x31C;
} Game5D2C0PositionState;

typedef struct Game5D2C0AnimationState {
    u8 pad_0[0x4];
    u16 field_0x04;
    u8 pad_0x06[0x2];
    f32 field_0x08;
    u8 pad_0x0C[0xC];
    f32 field_0x18;
} Game5D2C0AnimationState;

typedef struct Game5D2C0AnimationOwner {
    u8 pad_0[0x48];
    struct197 *field_0x48;
} Game5D2C0AnimationOwner;

#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_1502FE10.s")

typedef struct Func1502FFD8Arg0 {
    u8 pad0[1];
    u8 unk1;
    u8 pad2[2];
    u8 unk4;
    u8 pad5[3];
    u8 unk8;
    u8 unk9;
    u8 padA[0xD];
    s8 unk17;
    u8 pad18[0xC];
    s32 unk24;
    void *unk28;
    void *unk2C;
    s32 unk30;
    u8 pad34[0x14];
    void *unk48;
} Func1502FFD8Arg0;

typedef struct Func15030158Arg0 {
    u8 unk0;
    u8 unk1;
    u8 pad2[6];
    u8 unk8;
    u8 unk9;
    u8 padA[0x1A];
    s32 unk24;
    void *unk28;
    void *unk2C;
    s32 unk30;
    void *unk34;
    u8 pad38[0xC];
    void *unk44;
    void *unk48;
    void *unk4C;
    void *unk50;
    struct Func15030158Arg0 *unk54;
    struct Func15030158Arg0 *unk58;
} Func15030158Arg0;

s32 func_1502FFD8(Func1502FFD8Arg0 *arg0, u8 *arg1) {
    s32 sp3C;
    s32 flags;
    s32 sp34;

    if (arg0->unk24 == 0) {
        if (arg0->unk17 == -1) {
            if (func_1502FE10(arg0->unk1, &arg0->unk24, (u8 *)arg0 + 0x14, &sp3C, &arg0->unk30, 0, 0) != 0) {
                return 1;
            }
        } else {
            if (func_1503F62C(arg0->unk1, arg0->unk17, &arg0->unk24, (u8 *)arg0 + 0x14, &sp3C, &arg0->unk30, &arg0->unk48) != 0) {
                return 1;
            }
        }

        flags = arg1[0x66] & 0xC;
        sp34 = arg0->unk24 - sp3C;
        if (((arg0->unk4 & 0x10) == 0) && (flags == 8) && (arg0->unk30 != 0)) {
            arg0->unk28 = allocate_memory(sp34, 1, 2, 2);
            if (arg0->unk28 == 0) {
                return 1;
            }

            arg0->unk2C = allocate_memory(sp34, 1, 2, 2);
            if (arg0->unk2C == 0) {
                func_10004074(arg0->unk28);
                arg0->unk28 = 0;
                return 1;
            }

            bcopy((void *)sp3C, arg0->unk28, sp34);
            bcopy((void *)sp3C, arg0->unk2C, sp34);
            arg0->unk8 = 1;
        } else {
            arg0->unk28 = (void *)sp3C;
            arg0->unk2C = (void *)sp3C;
        }
        arg0->unk9 = 1;
    }
    return 0;
}

void func_15030158(Func15030158Arg0 *arg0, s32 arg1) {
    void *temp_a0;
    s32 *head;

    if (arg1 == 0) {
        func_15031C14(arg0);
    }
    if (arg0->unk9 != 0) {
        if (arg0->unk8 != 0) {
            if (arg1 != 0) {
                func_10004074(arg0->unk28);
                func_10004074(arg0->unk2C);
            } else {
                func_100043B4(arg0->unk28, 4);
                func_100043B4(arg0->unk2C, 4);
            }
        }
        temp_a0 = arg0->unk48;
        if (temp_a0 != 0) {
            func_1503F7B8(temp_a0);
        }
        func_1518CA04(arg0->unk1);
    }
    temp_a0 = arg0->unk34;
    if (temp_a0 != 0) {
        if (arg1 != 0) {
            func_10004074(temp_a0);
        } else {
            func_100043B4(temp_a0, 4);
        }
    }
    if (arg0->unk44 != 0) {
        void *temp_v0;

        temp_v0 = arg0->unk44;
        func_10004074(temp_v0);
    }
    temp_a0 = arg0->unk4C;
    if (temp_a0 != 0) {
        if (arg1 != 0) {
            func_10004074(temp_a0);
        } else {
            func_100043B4(temp_a0, 4);
        }
    }
    temp_a0 = arg0->unk50;
    if (temp_a0 != 0) {
        if (arg1 != 0) {
            func_10004074(temp_a0);
        } else {
            func_100043B4(temp_a0, 4);
        }
    }

    head = (s32 *)(s32)&D_800C3EE0;
    if ((s32)arg0 == *head) {
        *head = (s32)arg0->unk54;
    }
    if (arg0->unk58 != 0) {
        arg0->unk58->unk54 = arg0->unk54;
    }
    if (arg0->unk54 != 0) {
        arg0->unk54->unk58 = arg0->unk58;
    }
    func_10004074(arg0);
}

s32 func_15030310(void *arg0, s32 arg1, s32 arg2);

s32 func_150302F0(void *arg0, s32 arg1) {
    return func_15030310(arg0, arg1, 0xFF);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_15030310.s")

struct S150303E4 {
    u8 unk0;
    u8 pad1[0x53];
    struct S150303E4 *unk54;
};

s32 func_150303E4(struct127 *arg0) {
    struct S150303E4 *var;
    struct S150303E4 *next;
    s32 ret;

    if (arg0->unique_id == 0) {
        return 0;
    }

    var = (struct S150303E4 *)D_800C3EE0;
    ret = 0;
    if (var != 0) {
        do {
            next = var->unk54;
            if (var->unk0 == arg0->unique_id) {
                ret = 1;
                func_15030158(var, 0);
            }
            var = next;
        } while (next != 0);
    }
    return ret;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_15030468.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_15030AF4.s")

extern void *allocate_memory(s32 size, s32 arg1, s32 arg2, s32 arg3);
void func_15030D54(void *arg0, f32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6)
{
  f32 *temp;
  temp = allocate_memory(0x18, 1, 0, 2);
  *((f32 **) (((u8 *) arg0) + 0x44)) = temp;
  if (temp)
  {
    temp[((0, (*((s32 *) (((u8 *) arg0) + 0x34))) == 0)) * 0] = arg1;
    *((f32 *) ((*((s32 *) (((u8 *) arg0) + 0x44))) + 0x4)) = arg2;
    *((f32 *) ((*((s32 *) (((u8 *) arg0) + 0x44))) + 0x8)) = arg3;
    *((f32 *) ((*((s32 *) (((u8 *) arg0) + 0x44))) + 0xC)) = arg4;
    *((f32 *) ((*((s32 *) (((u8 *) arg0) + 0x44))) + 0x10)) = arg5;
    temp = ((u8 *) arg0) + 0x44;
    *((f32 *) ((*((s32 *) temp)) + 0x14)) = arg6;
    if (0, (*((s32 *) (((u8 *) arg0) + 0x34))) == 0)
    {
      *((void **) (((u8 *) arg0) + 0x34)) = allocate_memory(0x80, 1, 2, 2);
    }
  }
}


#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_15030E08.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_15030F94.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_15031070.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_150311C4.s")

void func_1503192C(struct127 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    struct126 *temp;
    temp = func_1503195C(arg0, arg1, arg3);
    if (temp != 0) {
        *((u8 *)temp + 3) = arg2;
    }
}

struct S1503195C {
    u8 unk0;
    u8 pad1[5];
    u8 unk6;
    u8 pad7[0x4D];
    struct S1503195C *unk54;
};

struct126 *func_1503195C(struct127 *arg0, s32 arg1, s32 arg2) {
    s32 key;
    struct S1503195C *var;
    struct S1503195C *next;

    key = arg0->unique_id;
    if (key == 0) {
        return 0;
    }

    var = (struct S1503195C *)D_800C3EE0;
    if (var != 0) {
        do {
            next = var->unk54;
            if ((key == var->unk0) && (arg1 == var->unk6)) {
                if (arg2 != 0) {
                    arg2 -= 1;
                    var = next;
                } else {
                    arg2 -= 1;
                    return (struct126 *)var;
                }
            } else {
                var = next;
            }
        } while (var != 0);
    }
    return 0;
}

struct S150319CC {
    u8 unk0;
    u8 pad1[5];
    u8 unk6;
    u8 pad7[0x4D];
    struct S150319CC *unk54;
};
struct S150319CC *func_150319CC(s32 arg0, u8 *arg1) {
    struct S150319CC *var;
    struct S150319CC *next;
    u8 key;

    if (arg1 != 0) {
        var = (struct S150319CC *)D_800C3EE0;
        if (var != 0) {
            key = arg1[0x3B];
            do {
                next = var->unk54;
                if ((var->unk0 == key) && (var->unk6 == arg0)) {
                    return var;
                }
                var = next;
            } while (next != 0);
        }
    }
    var = (struct S150319CC *)D_800C3EE0;
    if (var != 0) {
        do {
            next = var->unk54;
            if (var->unk6 == arg0) {
                return var;
            }
            var = next;
        } while (next != 0);
    }
    return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_15031A50.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_15031C14.s")

s32 func_15031E2C(void *arg0, s32 arg1) {
    s32 idx;

    idx = *(s32 *)((u8 *)arg0 + 0x38);

    if (idx >= 3) {
        idx = 5 - idx;
    }
    *(s16 *)((u8 *)arg0 + 0x18) = D_800902BC[idx];
    *(s32 *)((u8 *)arg0 + 0x38) = *(s32 *)((u8 *)arg0 + 0x38) + 1;
    if (*(s32 *)((u8 *)arg0 + 0x38) >= 6) {
        *(s32 *)((u8 *)arg0 + 0x38) = 0;
    }
    return 0;
}

s32 func_15031E7C(u8 *arg0, struct127 *arg1) {
    struct197 *anim;
    Gfx *gfx;
    s32 count;
    s32 i;
    f32 scale;

    anim = arg1->unk2D0;
    if (anim == 0) {
        return 0;
    }

    gfx = **(Gfx ***)(arg0 + 0x24);
    if (gfx == 0) {
        return 0;
    }

    if (arg1->unk84.uh == 0x55) {
        scale = 1.0f;
    } else if (arg1->unk84.uh == 0x56) {
        scale = 0.0f;
    } else {
        if ((0.0f <= anim->unk8) && (anim->unk8 <= 120.0f)) {
            scale = anim->unk8 * D_800970DC;
            scale = 1.0f - scale;
        } else {
            scale = 0.0f;
        }
    }

    i = 0;
    count = 4;
    do {
        count--;
        if (*(s8 *)((i << 3) + (u8 *)gfx) != -0xE) {
            do {
            } while (*(s8 *)((u8 *)gfx + (++i << 3)) != -0xE);
        }
        if (count != 0) {
            i++;
        }
    } while (count != 0);

    gfx[i].words.w0 = (G_SETTILESIZE << 24) | (2 << 12) | ((s32)((25.0f * scale) + 2.0f) & 0xFFF);
    return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_15031FC8.s")

void func_1503F5B8(s32 arg0, s32 arg1, s32 arg2, f32 arg3, f32 arg4, s32 arg5);

s32 func_150331B8(Game5D2C0AnimationOwner *arg0, struct127 *arg1) {
    struct197 *ptr;
    struct197 *temp;

    ptr = arg1->unk2D0;
    temp = arg0->field_0x48;
    if (temp == 0) {
        return 0;
    }
    if ((arg1->unk2E4 & 0xFF) != 0xFF) {
        func_1503F5B8((s32)temp, 0, arg1->unk2E4 & 0xFF, 1.0f, 0.0f, 1);
    }
    if (ptr != 0) {
        arg0->field_0x48->unk8 = ptr->unk8;
        temp = arg0->field_0x48;
        if (temp->unk18 <= temp->unk8) {
            temp->unk8 = temp->unk18 - 1.0f;
        }
    }
    return 0;
}


s32 func_1503327C(Game5D2C0AnimationOwner *arg0, s32 arg1) {
    Game5D2C0AnimationState *ptr;

    ptr = (Game5D2C0AnimationState *)arg0->field_0x48;
    if (ptr == 0) {
        return 0;
    }
    if ((ptr->field_0x04 & 0x8000) != 0x8000) {
        func_1503F5B8((s32)ptr, 0, 0, 1.0f, 0.0f, 1);
        ptr = (Game5D2C0AnimationState *)arg0->field_0x48;
    }
    if (ptr->field_0x18 - 1.0f <= ptr->field_0x08) {
        return 1;
    }
    return 0;
}

s32 func_15033328(Game5D2C0EffectState *arg0, Game5D2C0PositionState *arg1) {
    s32 delta;

    if (D_800C35EA == 1) {
        return 0;
    }
    if (arg1->field_0xAD == 0) {
        if (arg1->field_0x118 < arg1->field_0x180) {
            delta = D_800BE9E4;
            arg1 = (Game5D2C0PositionState *)arg0->field_0x38;
            if (delta < (s32)arg1) {
                arg0->field_0x38 = (s32)arg1 - delta;
                return 0;
            } else {
                return 1;
            }
        }
    }
    arg0->field_0x38 = 0x1E;
    return 0;
}

s32 func_150333A8(Game5D2C0FlagState *arg0, Game5D2C0PositionState *arg1) {
    Game5D2C0ActorState *temp;

    if (D_800C35EA == 1) {
        return 0;
    }
    if (arg1->field_0xAD != 0) {
        temp = arg1->field_0x31C;
        if (temp != 0) {
            temp->field_0x11A = 0;
        }
        return 1;
    }
    if ((arg1->field_0x118 != D_80097B68) && (arg1->field_0x18 < arg1->field_0x118 + 300.0f)) {
        arg0->field_0x03 = 0;
    } else {
        arg0->field_0x03 = 0xFF;
    }
    return 0;
}

s32 func_15033440(Game5D2C0EffectState *arg0, Game5D2C0EventState *arg1) {
    s32 state;

    state = arg0->field_0x01;
    if (state == 0x27) {
        goto add_delta;
    }
    if (state == 0x29) {
        goto clear;
    }
    if (state != 0x35) {
        goto done;
    }

add_delta:
    if (arg1->field_0x05 != 5) {
        goto done;
    }
    arg0->field_0x02 = 0;
    arg0->field_0x22 += D_800BE9E4 * 0xAAA;
    goto done;

clear:
    if (arg1->field_0x05 != 5) {
        goto done;
    }
    arg0->field_0x02 = 0;

done:
    return 0;
}

s32 func_150334B8(arg0, arg1)
u8 *arg0;
s16 arg1;
{
    Gfx *gfx;
    s32 count;
    s32 i;
    s32 w0;
    s32 w1;
    s32 width;
    s32 s;
    s32 t;
    s32 height;
    s32 offset;

    gfx = 0;
    count = 0;
    offset = 0;
    if (arg0[1] == 0x37) {
        gfx = **(Gfx ***)(arg0 + 0x24);
        count = 4;
        offset = -0x64;
    }
    if (gfx != 0) {
        i = 0;
        if (count != 0) {
            do {
                count--;
                if (*(s8 *)((i << 3) + (u8 *)gfx) != -0xE) {
                    do {
                    } while (*(s8 *)((u8 *)gfx + (++i << 3)) != -0xE);
                }
                if (count != 0) {
                    i++;
                }
            } while (count != 0);
        }

        w0 = gfx[i].words.w0;
        w1 = gfx[i].words.w1;
        width = ((w1 >> 12) & 0xFFF) + 2;
        s = ((w0 >> 12) & 0xFFF) + offset;
        t = w0 & 0xFFF;
        if (s >= width) {
            s -= width;
        }
        if (s < 0) {
            s += width;
        }
        height = (w1 & 0xFFF) + 2;
        if (t >= height) {
            t -= height;
        }
        if (t < 0) {
            t += height;
        }
        gfx[i].words.w0 = (G_SETTILESIZE << 24) | ((s & 0xFFF) << 12) | (t & 0xFFF);
    }
    return 0;
}

void *func_150335C8(struct127 *arg0, struct127 *arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    Game5D2C0RenderState *temp_v0;
    f32 sp124[4][4];
    f32 spE4[4][4];
    f32 spA4[4][4];
    f32 sp64[4][4];
    f32 sp60;
    f32 sp5C;
    f32 sp58;
    f32 sp54;
    f32 sp50;
    f32 sp4C;
    f32 sp48;
    f32 sp44;
    f32 sp40;
    f32 scale;

    if (arg1->unk1D4 == 0) {
        return 0;
    }

    temp_v0 = func_15083568(arg1, arg2, 1.0f, 0);
    if (temp_v0 != 0) {
        temp_v0->field_0x02 = arg3;
        temp_v0->field_0x40 = arg0->xz_scale;

        if (arg4 != 0) {
            temp_v0->field_0x16 = temp_v0->field_0x16 & ~4;
        } else {
            temp_v0->field_0x16 = temp_v0->field_0x16 | 4;
        }

        guMtxL2F(sp124, (Mtx *)((u8 *)arg1->unk1D4 + (arg3 << 6)));
        func_15048B10((s32)sp124, (s32)spE4);

        scale = arg0->xz_scale;
        func_150A9B0C(spA4, arg0->unkB8, arg0->unk40, arg0->unkC4, scale, arg0->y_scale, scale);

        spA4[3][0] = arg0->x_position;
        spA4[3][1] = arg0->y_position;
        spA4[3][2] = arg0->z_position;
        spA4[0][3] = 0.0f;
        spA4[1][3] = 0.0f;
        spA4[2][3] = 0.0f;
        spA4[3][3] = 1.0f;

        func_150A7A48(spA4, spE4, sp64);
        func_1503E5F8(sp64, &sp60, &sp5C, &sp58, &sp48, &sp44, &sp40, &sp54, &sp50, &sp4C);

        if (arg5 != 0) {
            sp58 = 0.0f;
            sp5C = 0.0f;
            sp60 = 0.0f;
        }

        func_15030D54(temp_v0, sp60, sp5C, sp58, sp48, sp44, sp40);
        return temp_v0;
    }

    return 0;
}

s32 func_1503378C(u8 *arg0, s16 *arg1) {
    u16 temp = (u16)arg1[0x42];
    if (arg0[1] == 0x11) {
        if ((temp == 0x3E) || (temp == 0x3D) || (temp == 0x41) || (temp == 0xD9) || (temp == 0x138) || (temp == 0x139)) {
            return 0;
        }
    }
    return 1;
}

extern s32 D_800902FC[];

s32 func_150337E4(void *arg0, s32 arg1) {
    s32 *p = (s32 *)arg0;
    p[0xE] += D_800BE9E4;
    if (p[0xE] >= 0x10) {
        p[0xE] = 0;
        p[0xF] ^= 1;
    }
    *(s16 *)((u8 *)arg0 + 0x18) = D_800902FC[p[0xF]];
    return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_5D2C0/func_15033838.s")

s32 func_150339C8(Game5D2C0EffectState *arg0, Game5D2C0PositionState *arg1) {
    func_150334B8(arg0, arg1);
    if (D_800C35EA != 1) {
        if (D_800BEA0C != 0) {
            if (arg0->field_0x3C != 0) {
                func_1000FD38(func_15033BDC, arg0, (s32)arg1);
            }
            arg0->field_0x3C = 0;
        } else if (arg0->field_0x3C == 0) {
            arg0->field_0x3C = func_1000FA64(0x448,
                (s16)(s32)arg1->field_0x14,
                (s16)(s32)arg1->field_0x18,
                (s16)(s32)arg1->field_0x1C,
                0x7D00, 0x3E8, 0x1F4, (s32)func_15033BDC, arg0, (s32)arg1, 0, 0) | 0x80000000;
        }
    }
    return 0;
}

s32 func_15033BDC();

s32 func_15033AD8(Game5D2C0EffectState *arg0, Game5D2C0PositionState *arg1) {
    if (D_800BE616 != 0) {
        func_1508B20C(arg1->field_0x14, arg1->field_0x18, arg1->field_0x1C, 900.0f);
    }
    if (arg0->field_0x38 == 0) {
        if (arg0->field_0x3C < 0x1E) {
            arg0->field_0x3C += D_800BE9E4;
        } else {
            arg0->field_0x3C = func_1000FA64(0x513,
                (s16)(s32)arg1->field_0x14,
                (s16)(s32)arg1->field_0x18,
                (s16)(s32)arg1->field_0x1C,
                0x7D00, 0x3E8, 0x1F4, (s32)func_15033BDC, arg0, (s32)arg1, 0, 0);
            arg0->field_0x38 = 0x513;
        }
    }
    return 0;
}

typedef struct Game5D2C0SoundInstance {
    u16 field_0x00;
    s16 field_0x02;
    s16 field_0x04;
    s16 field_0x06;
    u8 pad_0x08[0x10];
    Game5D2C0EffectState *field_0x18;
    Game5D2C0PositionState *field_0x1C;
    u8 pad_0x20[0x4];
    u16 field_0x24;
} Game5D2C0SoundInstance;

void func_10010FFC(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, void *arg5);

s32 func_15033BDC(Game5D2C0SoundInstance *arg0, s32 arg1, s32 *arg2, s32 arg3, s32 arg4, s32 arg5, s16 *arg6) {
    Game5D2C0EffectState *effect;
    Game5D2C0PositionState *pos;
    Game5D2C0ActorState *actor;

    effect = arg0->field_0x18;
    pos = arg0->field_0x1C;
    if ((effect != 0) && (pos != 0) && (pos->field_0x00 != 0)) {
        arg0->field_0x02 = pos->field_0x14;
        arg0->field_0x04 = pos->field_0x18;
        arg0->field_0x06 = pos->field_0x1C;

        if (*arg2 != 0) {
            if (effect->field_0x01 == 0x37) {
                s32 currentId = effect->field_0x38;
                s32 sfxId = -1;

                if (pos->field_0x84 != (currentId & 0xFFFF)) {
                    if (pos->field_0x84 == 0x15F) {
                        sfxId = (func_150ADA20() & 3) + 0x444;
                    }
                }
                if (sfxId != -1) {
                    func_10010FFC(0, sfxId, 0x5DC0, 0, 0, pos);
                }
                effect->field_0x38 = pos->field_0x84;
            } else {
                actor = pos->field_0x31C;
                if (actor != 0) {
                    if (actor->field_0x19C < 0x78) {
                        if (effect->field_0x38 == 0x513) {
                            effect->field_0x38 = 0x3A1;
                            effect->field_0x3C = func_1000FA64(0x3A1,
                                (s16)(s32)pos->field_0x14,
                                (s16)(s32)pos->field_0x18,
                                (s16)(s32)pos->field_0x1C,
                                0x7D00, 0x3E8, 0x1F4, (s32)func_15033BDC, effect, (s32)pos, 0, 0);
                            return 1;
                        }
                    }
                }
            }
            return 0;
        }

        if (effect->field_0x01 == 0x37) {
            if (arg0->field_0x24 != 0) {
                func_100111C8(arg0->field_0x24);
                arg0->field_0x24 = 0;
            }
            *arg6 = 0;
            return 0;
        }
    }
    return 1;
}

s32 func_15033E00(s32 arg0, u8 *arg1) {
    if (arg1[5] == 3) {
        return 1;
    }
    return 0;
}

s32 func_15033E28(u8 *arg0, u8 **arg1) {
    u8 *var;
    u8 *cur;
    u8 *next;
    s32 count;

    var = (u8 *)D_800C3EE0;
    count = 0;
    if (var == 0) {
        return 0;
    }
    cur = var;
    if (cur != 0) {
        do {
            next = *(u8 **)(cur + 0x54);
            if (arg0[0x3B] == cur[0]) {
                arg1[count] = cur;
                count += 1;
            }
            cur = next;
        } while (next != 0);
    }
    return count;
}

struct S15033E84 {
    u8 unk0;
    u8 pad[0x53];
    struct S15033E84 *unk54;
};
struct S15033E84 *func_15033E84(u8 *arg0) {
    struct S15033E84 *var;
    struct S15033E84 *next;
    u8 key;

    var = (struct S15033E84 *)D_800C3EE0;
    if (var != 0) {
        key = arg0[0x3B];
        do {
            next = var->unk54;
            if (var->unk0 == key) {
                return var;
            }
            var = next;
        } while (next != 0);
    }
    return 0;
}

void func_15033EC4(s32 arg0, s32 arg1) {
    struct S15033E84 *var;
    struct S15033E84 *next;
    s32 b;
    s32 key;

    b = arg0;
    var = (struct S15033E84 *)D_800C3EE0;
    if (var != 0) {
        do {
            next = var->unk54;
            key = var->unk0;
            if (b == key) {
                var->unk0 = arg1;
            } else if (arg1 == key) {
                var->unk0 = b;
            }
            var = next;
        } while (next != 0);
    }
}

s32 func_15033F0C(s32 arg0, u8 *arg1) {
    u8 *temp;

    if (D_800C35EA == 1) {
        return 0;
    }
    temp = *(u8 **)(arg1 + 0x31C);
    if (temp != 0) {
        if (temp[0x78] != 9) {
            if (temp[0x11A] != 3) {
                temp[0x11A] = 0;
                return 1;
            }
        }
    }
    return 0;
}

s32 func_15033F70(s32 arg0, u8 *arg1) {
    u8 *temp;

    if (D_800C35EA == 1) {
        return 0;
    }
    temp = *(u8 **)(arg1 + 0x31C);
    if (temp != 0) {
        if ((temp[0x78] != 0xC) && (temp[0x78] != 0x16)) {
            if (temp[0x11A] != 3) {
                temp[0x11A] = 0;
                return 1;
            }
        }
    }
    return 0;
}
