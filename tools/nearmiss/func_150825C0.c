#include <ultra64.h>
#define func_150ADA20 func_150ADA20_u8_proto
#define func_15083E90 func_15083E90_s32_proto
#include "functions.h"
#undef func_15083E90
#undef func_150ADA20
#include "variables.h"

extern s32 func_150ADA20(void);
extern struct127 *func_15083E90(u8);
extern struct172 D_80086CC4[];
extern void func_150302F0(struct127 *arg0, s32 arg1);
extern s32 D_80086CAC[];
extern void func_15036C70(struct127 *arg0);
/* Returns 0 from every early-exit path (`or v0,zero,zero` before the epilogue in
   golden) and tail-returns func_15082A44's result, so the symbol is s32-valued;
   func_1508295C below simply discards the value. */
extern s32 func_150825C0(s32 arg0, s32 arg1);
extern u8 D_800D2100;
extern u8 D_800D2101;
extern u8 D_800BE590;
extern u16 D_800BE598[];
extern s32 func_1503D660(s32 arg0, s32 arg1);
extern s32 func_1503D774(s32 arg0, s32 arg1);

typedef struct {
    u8 pad0[0x2];
    s16 unk2;
    u8 unk4;
    u8 unk5;
    u8 pad6[0xC];
    u8 unk12;
    u8 pad13[0x16];
    u8 unk29;
    u16 unk2A;
    u8 pad2C[0x7];
    s8 unk33;
    s32 unk34;
    u8 unk38;
    u8 unk39;
    u8 pad3A;
    u8 unk3B;
    u8 unk3C;
} GameAEB40Def;

typedef struct {
    u8 pad_0[0x2F];
    u8 field_0x2F;
} GameAEB40AnimationData;

typedef struct {
    u8 pad_0[0x300];
    s32 field_0x300;
    s32 field_0x304[4];
    s32 *field_0x314;
} GameAEB40ActorSlots;


#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_15081690.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_15081C20.s")

extern void func_1507DF10(struct127 *arg0, s32 arg1);

void func_15081E0C(struct127 *arg0, u16 arg1, u8 arg2) {
    if (D_800BE616 == 0) {
        if (arg0->health != 0) {
            arg0->health = 7;
        }
        if ((arg2 == 0) || (arg1 != 0xA)) {
            func_1507DF10(arg0, arg1);
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_15081E78.s")

/* --- func_150825C0 -------------------------------------------------- */

/* structs.h's struct258 describes the same table but is only 0x10 bytes and has
   no members below 0x4; golden indexes D_800D20FC with a 0x30 (48) byte stride
   (`sll t4,s2,2; subu t4,t4,s2; sll s2,t4,4`) and reads u8 fields at +1/+2, so
   this file uses a local 0x30-byte view instead of retyping the shared header. */
typedef struct {
    u8  unk0;
    u8  unk1;
    u8  unk2;
    u8  unk3;
    s16 unk4;
    s16 unk6;
    s16 unk8;
    s16 unkA;
    u8  padC[0x24];
} GameAEB40Spawn;

extern u8 *D_800D210C;
extern f32 D_8009CC30;
extern f32 D_8009CC34;
extern f32 D_8009CC38;
extern f32 D_8009CC3C;
extern f32 D_800D9C10[][4][4];
extern s32 func_150A6360(void *arg0, f32 arg1[4][4], f32 arg2, f32 arg3, f32 arg4,
                         f32 arg5, f32 arg6, f32 arg7);
extern s32 func_15082A44(GameAEB40Spawn *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

s32 func_150825C0(s32 arg0, s32 arg1) {
    f32 rad;
    s32 i;
    u16 t;
    u8 ok;
    u8 flags;
    s32 j;

    if (D_800D210C[arg0] != 0) {
        return 0;
    }
    if (((GameAEB40Spawn *)D_800D20FC)[arg0].unk2 == 1) {
        return 0;
    }
    if (((GameAEB40Spawn *)D_800D20FC)[arg0].unk6 == 0x7FFF) {
        return 0;
    }
    t = (*(u16 **)&D_800D2110)[arg0];
    if (t != 0) {
        if (t <= D_800BE9A0) {
            (*(u16 **)&D_800D2110)[arg0] = 0;
        } else {
            (*(u16 **)&D_800D2110)[arg0] = t - D_800BE9A0;
        }
        return 0;
    }
    flags = ((GameAEB40Spawn *)D_800D20FC)[arg0].unk1;
    if (arg0 >= 5) {
        if ((flags & 6) != 0) {
            if ((flags & 6) == 2) {
                rad = D_8009CC30;
            } else if ((flags & 6) == 4) {
                rad = D_8009CC34;
            } else {
                rad = D_8009CC38;
            }
            ok = 1;
            for (j = 0; j < D_8008FD8C; j++) {
                if (D_800CC2D0[j].interaction_state == 0) {
                    continue;
                }
                if (D_800CC2D0[j].unk127 == 0xFF) {
                    continue;
                }
                if ((1 << D_800CC2D0[j].unk127) &
                    *(u16 *)((u8 *)&D_800D2138 + 0x208)) {
                    if (((D_800CC2D0[j].x_position -
                          ((GameAEB40Spawn *)D_800D20FC)[arg0].unk6) *
                         (D_800CC2D0[j].x_position -
                          ((GameAEB40Spawn *)D_800D20FC)[arg0].unk6)) +
                        ((D_800CC2D0[j].z_position -
                          ((GameAEB40Spawn *)D_800D20FC)[arg0].unkA) *
                         (D_800CC2D0[j].z_position -
                          ((GameAEB40Spawn *)D_800D20FC)[arg0].unkA)) <= rad) {
                        ok = 0;
                        break;
                    }
                }
            }
            if (ok != 0) {
                return 0;
            }
        }
    }
    if (flags & 8) {
        ok = 1;
        for (i = 0; i <= D_80082FA0; i++) {
            if (func_150A6360((void *)((i * 0x180) + D_800BE628), D_800D9C10[i],
                              ((GameAEB40Spawn *)D_800D20FC)[arg0].unk6,
                              ((GameAEB40Spawn *)D_800D20FC)[arg0].unk8 + 150,
                              ((GameAEB40Spawn *)D_800D20FC)[arg0].unkA,
                              150.0f, 150.0f, D_8009CC3C) != 0) {
                ok = 0;
            }
        }
        if (ok == 0) {
            return 0;
        }
    }
    return func_15082A44(&((GameAEB40Spawn *)D_800D20FC)[arg0], arg0, 0, 0, 0);
}

void func_1508295C(s32 arg0, s32 arg1, s32 arg2) {
    s32 start;
    s32 end;
    s32 i;

    if (arg2 != 0) {
        start = 0;
        end = D_800D2101;
    } else {
        start = D_800D2101;
        end = D_800D2100;
    }

    i = start;
    if (start < end) {
        do {
            func_150825C0(i, arg1);
            i++;
        } while (i != end);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_150829D8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_15082A44.s")

void func_150832AC(struct127 *arg0) {
    GameAEB40AnimationData *temp_v1;
    u8 temp_a0;
    GameAEB40ActorSlots *temp_s0;
    s32 i;
    s32 temp_s3;

    temp_v1 = (GameAEB40AnimationData *)arg0->unk144;
    if (temp_v1 != 0) {
        temp_a0 = temp_v1->field_0x2F;
        temp_s0 = (GameAEB40ActorSlots *)arg0;
        if (temp_a0 == 0) {
            if (arg0->unk127 == 0) {
                temp_s3 = 5;
            } else {
                temp_s3 = 3;
            }
        } else {
            temp_s3 = temp_a0;
        }
        for (i = 0; i <= D_80082FA0; i++) {
            temp_s0->field_0x304[i] = (s32)func_1515D480(temp_s3);
        }
        if ((&temp_s0->field_0x300)[i] != 0) {
            arg0->unk301[0] = temp_s3;
        }
        temp_s0->field_0x314 = func_1515D440();
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_15083384.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_15083568.s")

void func_150836CC(struct127 *arg0, s32 arg1) {
    struct172 *temp_s2;
    s32 i;
    u8 *temp_v1;

    func_150302F0(arg0, arg1);
    arg1--;
    temp_s2 = &D_80086CC4[arg1];
    i = 0;
    temp_v1 = (u8 *)*(s32 *)temp_s2;
    if (i < temp_s2->unk4) {
        u8 *temp_s0;
        struct127 *temp_v0;

        temp_s0 = temp_v1;
        do {
            if (temp_s0[3] == 0) {
                temp_v0 = func_1505F0AC(temp_s0[0]);
                if (temp_v0 != 0) {
                    if (temp_v0->unk65 == ((arg0 - D_800CC2D0) + 1)) {
                        func_15060F28(temp_v0, 0);
                    }
                }
            }
            i++;
            temp_s0 += 0x10;
        } while (i < temp_s2->unk4);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_150837D4.s")

extern s32 allocate_memory(s32, s32, s32, s32);

s32 func_150838EC(struct127 *arg0, s32 arg1, s32 arg2, f32 arg3) {
    s32 idx;

    idx = arg0->id;
    if (D_800D1588[idx] == 0) {
        return 0;
    }
    if (((u16 *)D_800C5A90)[idx] == 0) {
        return 0;
    }
    *(s32 *)((s32)arg0 + 0x2D0) = allocate_memory(0x3E0, 1, 2, 0);
    if (*(s32 *)((s32)arg0 + 0x2D0) == 0) {
        return 1;
    }
    bzero(*(s32 *)((s32)arg0 + 0x2D0), 0x40);
    func_1505E650(arg0, arg1, arg3, 0.0f, 0.0f, 0.0f, arg2);
    return 0;
}

void func_150839B8(struct127 *arg0, s32 arg1, void *arg2) {
    GameAEB40Def *temp_v0;
    u16 temp_v1;

    if (arg1 != 0xFF) {
        temp_v0 = (GameAEB40Def *)D_800D1C90[arg1];
        if (arg2 != 0) {
            temp_v1 = *(u16 *)((u8 *)arg2 + 0x2C);
            if (temp_v1 == 0) {
                *(u16 *)((u8 *)arg0 + 0x10) = temp_v0->unk2A;
            } else {
                if (temp_v1 == 1) {
                    *(u16 *)((u8 *)arg0 + 0x10) = 0;
                } else {
                    *(u16 *)((u8 *)arg0 + 0x10) = temp_v1;
                }
            }
            if (D_800BE9F0 == 0x1D) {
                *(u16 *)((u8 *)arg0 + 0x10) = 0x3E8;
            }
        } else {
            *(u16 *)((u8 *)arg0 + 0x10) = 0;
        }
        *((u8 *)arg0 + 0x13B) = temp_v0->unk39;
        arg0->unk2CB = temp_v0->unk33;
        arg0->unk2CC = temp_v0->unk34;
        arg0->unk5 = temp_v0->unk12;
        *((u8 *)arg0 + 0x68) = temp_v0->unk3B;
        *((u8 *)arg0 + 0x69) = temp_v0->unk3C;
        *(s16 *)((u8 *)arg0 + 0x160) = temp_v0->unk2;
        if (temp_v0->unk4 != 0) {
            *(s32 *)((u8 *)arg0 + 0x2C4) = D_80086CAC[temp_v0->unk5];
            *((u8 *)arg0 + 0x2C8) = temp_v0->unk4;
        }
        arg0->unk2C9 = *((u8 *)arg0 + 0x2C8) + temp_v0->unk38;
        if (temp_v0->unk29 != 0) {
            func_15036C70(arg0);
        }
    }
}

extern struct127 *func_1505ED34(void);

struct127 *func_15083AC8(struct127 *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, s32 arg7, f32 arg8) {
    struct127 *obj;
    GameAEB40ActorSlots *slots;
    s32 paused;
    s32 blocked;
    s32 i;

    func_1503D774(arg2, 0);
    func_1503D660(arg2, 0);
    obj = func_1505ED34();
    obj->unique_id = 0xFF - (obj - D_800CC2D0);
    obj->unkAB = arg3;
    obj->interaction_state = arg4;
    func_150615DC(obj);
    obj->unk232 = 1;
    obj->health = 1;
    obj->immune = 0xFF;
    obj->unk65 = (arg0 - D_800CC2D0) + 1;
    obj->unk5C = arg1;
    obj->unk123 = 1;
    obj->id = arg2;
    obj->pad66 = arg0->pad66;
    obj->pad66 &= ~0x10;
    obj->pad66 |= 0;
    *((u8 *)obj + 0x1DD) = *((u8 *)arg0 + 0x1DD);
    *((u8 *)obj + 0x1DE) = *((u8 *)arg0 + 0x1DE);
    *((u8 *)obj + 0x1DF) = *((u8 *)arg0 + 0x1DE);
    *((u8 *)obj + 0x1E0) = *((u8 *)arg0 + 0x1E0);
    *((u8 *)obj + 0x1E1) = *((u8 *)arg0 + 0x1E1);
    *((u8 *)obj + 0x1E2) = *((u8 *)arg0 + 0x1E2);
    if (arg6 == 0) {
        obj->xz_scale = 1.0f;
        obj->y_scale = 1.0f;
        obj->unk154 = 1.0f;
        obj->unk158 = 1.0f;
    } else {
        obj->xz_scale = arg0->xz_scale;
        obj->y_scale = arg0->y_scale;
        obj->unk154 = arg0->unk154;
        obj->unk158 = arg0->unk158;
    }
    obj->unk101 = arg6;
    obj->padAC = arg5;
    func_1503D774(arg2, 0);
    if (arg5 & 1) {
        obj->unkF8 |= 0x4000;
        *(f32 *)((u8 *)obj + 0x270) = (f32)(u32)*(u16 *)((u8 *)D_800D1C90[arg2] + 0xE) * obj->xz_scale;
    }
    paused = 0;
    if (arg5 & 2) {
        paused = 1;
    }
    slots = (GameAEB40ActorSlots *)obj;
    for (i = 0; i <= D_80082FA0; i++) {
        slots->field_0x304[i] = (s32)func_1515D480(1);
    }
    if ((&slots->field_0x300)[i] != 0) {
        obj->unk301[0] = 1;
    }
    slots->field_0x314 = func_1515D440();
    if (D_800C35EA == 1) {
        blocked = 1;
    } else {
        blocked = 0;
    }
    if (blocked) {
        D_800C3638 = 0;
    }
    func_150839B8(obj, arg2, NULL);
    func_150837D4(obj - D_800CC2D0, arg2, 1);
    func_150838EC(obj, arg7, paused, arg8);
    if (blocked) {
        D_800C3638 = 1;
    }
    return obj;
}

extern u8 D_800D2100;

struct struct258b {
    u8 pad0[0x28];
    u8 unk28;
    u8 pad29[0x7];
};

s32 func_15083DA0(void) {
    s32 id;
    s32 i;

    id = 1;
    i = 0;
    while (i < (s32)D_800D2100) {
        if (id == ((struct struct258b *)D_800D20FC)[i].unk28) {
            id++;
            i = 0;
        }
        i++;
    }
    if (id >= 0x100) {
        id = 0xFF;
    }
    return id;
}

s32 func_15083E0C(u8 id) {
    s32 i;
    s32 offset;
    struct struct258b *base;
    struct struct258b *ptr;

    if (id == 0) {
        return -1;
    }

    i = 0;
    if ((s32)D_800D2100 > 0) {
        base = (struct struct258b *)D_800D20FC;
        offset = 0;
        ptr = base;
        do {
            i++;
            if (ptr->unk28 == id) {
                return ((s32)((u8 *)offset + (s32)base) - (s32)base) / 0x30;
            }
            offset += sizeof(struct struct258b);
            ptr++;
        } while (i < (s32)D_800D2100);
    }
    return -1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_15083E90.s")

s32 func_15083FB0(u8 arg0) {
    struct127 *temp;

    temp = func_15083E90(arg0);
    if (temp != 0) {
        return temp - D_800CC2D0;
    }
    return -1;
}

extern struct127 *func_1505EEF4(void);

s32 func_15084000(void) {
    struct127 *temp = func_1505EEF4();

    if (temp != 0) {
        return temp - D_800CC2D0;
    }
    return -1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_15084044.s")

extern void func_150843AC(void *arg0, s32 arg1);

void func_1508434C(u8 *arg0) {
    s32 count;
    s32 i;

    count = arg0[0x2C9];
    if (count == 0) {
        count = 1;
    }
    for (i = 0; i < count; i++) {
        func_150843AC(arg0, i);
    }
}

void func_100043B4(s32 *arg0, u32 arg1);
extern s32 D_800D19A0;
extern s32 D_800D1F80[187];
extern void func_150843AC(void *arg0, s32 arg1);
void func_150843AC(void *arg0, s32 arg1)
{
  unsigned char limit;
  s32 *p;
  s32 i;
  u8 idx;
  if (((*((s32 *) ((((u8 *) arg0) + (arg1 * 8)) + 0x28C))) == 0) && ((*((s32 *) ((((u8 *) arg0) + (arg1 * 8)) + 0x290))) == 0))
  {
    return;
  }
  limit = 8;
  idx = ((u8 *) (*((s32 *) (((u8 *) arg0) + 0x2C4))))[arg1];
  for (p = (s32 *) (((s8 *) arg0) + (arg1 << 3)), i = 0; i != limit; p++, i += 4)
  {
    s32 cur = *((s32 *) (((u8 *) p) + 0x28C));
    if (cur != 0)
    {
      if (cur != (&D_800D19A0)[idx])
      {
        func_100043B4((s32 *) cur, 3);
      }
      else
      {
        ((u8 *) D_800D1F80)[idx] -= 1;
      }
      *((s32 *) (((u8 *) p) + 0x28C)) = 0;
    }
  }

}


void func_15084488(u8 *arg0, s32 arg1, s32 arg2) {
    s32 count;
    s32 i;
    GameAEB40Def *temp_v0;
    u8 *ptr;
    u8 *list;
    s32 idx;

    idx = arg0[4];
    if (idx != 0xFF) {
        func_1503D774(idx, arg2);
        temp_v0 = (GameAEB40Def *)D_800D1C90[idx];
        list = arg0 + 4;
        count = temp_v0->unk4;
        if (count == 0) {
            count = 1;
        } else {
            list = (u8 *)D_80086CAC[temp_v0->unk5];
        }
        i = 0;
        ptr = list;
        count += temp_v0->unk38;
        if (count > 0) {
            do {
                func_1503D774(*ptr, arg2);
                func_1503D660(*ptr, arg2);
                i++;
                ptr++;
            } while (i != count);
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_15084558.s")

typedef struct {
    u8 pad[0x1C9];
    u8 unk1C9;
    u8 pad2[0x2C4 - 0x1CA];
    u8 *unk2C4;
    u8 unk2C8;
} GameAEB40Struct;

u8 func_150849A0(GameAEB40Struct *a0) {
    s32 v1 = a0->unk1C9;
    if (v1 != 0) {
        return a0->unk2C4[v1 - 1];
    }
    return a0->unk2C4[0];
}

u8 func_150849CC(GameAEB40Struct *a0, s32 *a1) {
    s32 v1;
    s32 v0;
    v0 = a0->unk1C9;
    if (v0 != 0) {
        v1 = v0 - 1;
    } else {
        v0 = a0->unk2C8;
        if (v0 != 0) {
            v1 = v0 - 1;
        } else {
            v1 = 0;
        }
    }
    if (a1 != 0) {
        *a1 = v1;
    }
    return a0->unk2C4[v1];
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_AEB40/func_15084A18.s")

void func_15084C30(struct127 *arg0) {
    struct197 *sp1C;
    f32 temp_f0;

    if (arg0->id == 0x94) {
        sp1C = arg0->unk2D0;
        temp_f0 = (f32)((u32)func_150ADA20() % (u32)(s32)sp1C->unk18);
        sp1C->unk8 = temp_f0;
    }
}


s32 func_15084CB0(s32 arg0) {
    s32 ret;
    s32 i;

    ret = 0;
    i = 0;
    if ((s32)D_800BE590 > 0) {
        do {
            if (arg0 == D_800BE598[i]) {
                ret = i;
                break;
            }
            i++;
        } while (i < (s32)D_800BE590);
    }
    return ret;
}
