#include <ultra64.h>
#include "functions.h"
#include "variables.h"


extern u16 D_800C4ED0[];
typedef struct {
    u8 unk0;
    u8 pad1[0xF];
} D_800C666FEntry;

typedef struct {
    u8 pad_0[0x4];
    u8 field_0x4;
    u8 pad_0x5[0x9B];
    u32 field_0xA0;
    u8 field_0xA4;
    u8 field_0xA5;
    u8 field_0xA6;
    u8 field_0xA7;
    u8 pad_0xA8[0x50];
    u32 field_0xF8;
    u8 pad_0xFC[0xD8];
    void *field_0x1D4;
    void *field_0x1D8;
    u8 pad_0x1DC[0x88];
    void *field_0x264;
} ActorInteractionFields;

extern D_800C666FEntry D_800C666F[];
extern void *allocate_memory(s32, s32, s32, s32);
extern void func_1502C608(s32);
extern void func_1502DF38(s32, s32);
extern void func_1502E4C4(s32);
extern void func_1502EAFC(struct127 *);
extern void func_1502EC34(void *, s32 *, s32 *, s32 *, s32 *);
extern void func_1502EEF4(s32);
extern void func_1502F264(s32);
extern void func_1502FBE8(struct127 *);
extern void func_150345E4(s32);
extern void func_1503A08C(struct127 *);
extern void func_1503A830(struct127 *);
extern void func_1503DF48(s32);
extern void func_150A4B04(struct127 *);
extern void func_1517AD00(s32, s32, s32);

extern Gfx D_80084160[];
extern Gfx D_80084190[];
extern Gfx *func_1502C408(Gfx *, s32);
extern Gfx *func_1502C974(Gfx *, s32, s32, s32, s32);
extern Gfx *func_15030E08(Gfx *, s32, s32);
extern Gfx *func_150368C4(Gfx *, s32, s32);
extern s32 func_1506196C(struct127 *, s32);

Gfx *func_1502BAD0(Gfx *gfx, s32 arg1, s16 arg2) {
    struct127 *obj;
    s32 i;
    s32 state;

    gSPDisplayList(gfx++, D_80084160);
    obj = D_800CC2D0;
    for (i = 0; i < 25; i++, obj++) {
        D_8003C8E0 = (i & 0xFFFFFF) | (1 << 24);
        state = obj->interaction_state;
        if (state == 0) {
            continue;
        }
        if (obj->unk5 == 3) {
            continue;
        }
        if (obj->unk5 == 5) {
            continue;
        }
        if (obj->unk5 == 2) {
            if (arg1 != 2) {
                continue;
            }
        } else if (obj->id == 0xFF) {
            continue;
        }
        if (arg1 == 6) {
            if (obj->unk5 != 7) {
                continue;
            }
        } else if (arg1 == 0) {
            if ((((u32)obj->unk184 >> 9) & 1) == 0) {
                continue;
            }
        } else if (arg1 == 1) {
            if (obj->unk5 == 7) {
                continue;
            }
            if (obj->unk5 == 1) {
                continue;
            }
            if ((obj->unk5 == 0) && (func_1506196C(obj, arg2) < 0xFF)) {
                continue;
            }
        } else if (arg1 == 2) {
            if (obj->unk5 != 2) {
                if (obj->unk5 == 7) {
                    continue;
                }
                if ((obj->unk5 != 0) && (obj->unk5 != 1)) {
                    continue;
                }
                if ((obj->unk5 == 0) && (func_1506196C(obj, arg2) == 0xFF)) {
                    continue;
                }
            }
        }
        if (obj->unk5 == 2) {
            gfx = func_1502C408(gfx, i);
        } else {
            gfx = func_1502C974(gfx, i, arg2, arg1, 0);
            if (i == 0) {
                gfx = func_150368C4(gfx, i, arg2);
            }
        }
    }
    D_8003C8E0 = 0xFFFFFF | (1 << 24);
    if (arg1 == 1) {
        gfx = func_15030E08(gfx, arg2, 0);
    } else if (arg1 == 2) {
        gfx = func_15030E08(gfx, arg2, 1);
    } else if (arg1 == 6) {
        gfx = func_15030E08(gfx, arg2, 2);
    }
    gSPDisplayList(gfx++, D_80084190);
    D_8003C8E0 = 0;
    return gfx;
}

void func_1502BD84(struct127 *arg0, s32 arg1) {
    arg0->unk1D4 = NULL;
    if (arg0->unk5 == 5) {
        func_1502DF38(arg1, 1);
        return;
    }
    if (arg0->id == 0xFF) {
        return;
    }
    if (arg0->unk5 == 3) {
        return;
    }
    if (arg0->unk5 == 2) {
        func_1502C608(arg1);
        return;
    }
    if (arg0->unk1C9 != 0) {
        func_1502FBE8(arg0);
    }
    func_1502E4C4(arg1);
    func_1502DF38(arg1, 0);
    func_1503A08C(arg0);
    if (arg0->unk1D4 == NULL) {
        arg0->unk1FC = 2;
    } else {
        func_150345E4(arg1);
        func_1503A830(arg0);
    }
    if (D_800C666F[arg1].unk0 != 0) {
        func_1503DF48(arg1);
    }
    if (arg0->interaction_state != 0) {
        func_1502EEF4(arg1);
        func_1502F264(arg1);
        if (*(u8 *)((u8 *)arg0 + 0xA4) != 0) {
            func_1502EAFC(arg0);
        }
        if ((arg0->unkF8 & 0x4000) != 0) {
            func_150A4B04(arg0);
        }
        if (*(s32 *)((u8 *)arg0 + 0x260) != 0) {
            func_1517AD00(*(u8 *)((u8 *)arg0 + 0x134), *(u8 *)((u8 *)arg0 + 0x135), arg1);
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502BEE4.s")

void func_1516972C(struct102 *arg0);
extern s32 D_80082FA0;
extern u8 D_800C3638;
extern struct127 D_800CC2D0[26];
extern s32 D_800D121C;
extern s32 func_150229E4(struct127 *);
extern s32 func_1506196C(struct127 *, s32);
extern struct102 *func_1510D970(s32, struct127 *, s32, s32, s32);
extern u8 D_800C3656;
void func_1502C1A4(void)
{
  struct127 *obj;
  s32 found;
  s32 i;
  s32 arg2;
  s32 arg4;
  s32 id;
  s32 state;
  struct102 *temp;
 obj = D_800CC2D0; do { state = obj->interaction_state; if (state != 0) { id = obj->id; found = 0; if ((((((((obj->unk5 != 3) && (id != 0xFF)) && (obj->unk123 == 0)) && ((obj->pad66 & 0x10) != 0x10)) && ((*((u16 *) (((u8 *) obj) + 0x160))) != 0)) && (obj->unk65 == 0)) && (((D_800C3638 == 0) || (D_800C3656 != 0)) || (func_150229E4(obj) != 0))) && ((obj->unk88 == 0) || (obj->unkCC >= (-0x96)))) { i = 0; if (D_80082FA0 >= 0) { do {
            if (func_1506196C(obj, i) != 0)
            {
              found = 1;
            }
            i++;
          }
          while (D_80082FA0 >= i);
        }
      }
      if (found != 0)
      {
        if ((*((struct102 **) (((u8 *) obj) + 0x2D4))) == 0)
        {
          arg2 = 0;
          if (obj->id == 0x4D)
          {
            arg2 = 2;
            arg4 = 1;
          }
          else
          {
            arg4 = 0;
          }
          *((struct102 **) (((u8 *) obj) + 0x2D4)) = func_1510D970(0, obj, arg2, 0, arg4);
          alloc_done:
          ;

          ;
          ;
        }
      }
      else
      {
        temp = *((struct102 **) (((u8 *) obj) + 0x2D4));
        if (temp != 0)
        {
          func_1516972C(temp);
          *((struct102 **) (((u8 *) obj) + 0x2D4)) = 0;
        }
      }
    }
    obj++;
  }
  while (obj != ((struct127 *) (&D_800D121C)));
}


extern s32 D_800C3E88;
extern s32 D_800C3E8C;
extern u16 D_800C3E7A;

void func_1502C380(void) {
    D_800C3E8C = D_800C3E88 = (&D_800C3E80)[D_800BE9C0];
    D_800C3E7A = 0;
}

extern u8 D_800CC406[];

s32 func_1502C3BC(s32 arg0) {
    s32 temp = D_800CC406[arg0 * 0x32C];

    if (temp >= 0x46) {
        temp = 0xB;
    }
    return temp;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502C408.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502C608.s")

extern f32 D_80096DE0;
extern f32 D_80096DE4;
extern s32 func_150849A0(struct127 *);
extern void func_150837D4(s32, s32, s32);

void func_1502C6E8(s32 arg0, s16 arg1, s32 arg2) {
    struct108 *cam;
    struct127 *obj;
    s32 mode;
    s32 lod;
    s32 maxLod;
    s32 model;
    f32 dists[4];
    f32 diff;
    f32 distSq;

    cam = &D_800DBFF0[arg1];
    obj = &D_800CC2D0[arg0];
    if (obj->unk1C9 != 0) {
        return;
    }
    if (obj->unk5 == 7) {
        return;
    }
    dists[0] = 500.0f;
    dists[1] = D_80096DE0;
    dists[2] = D_80096DE4;
    dists[3] = 2000.0f;
    maxLod = ((u8 *)obj)[0x2C8] - 1;
    if (maxLod == -1) {
        return;
    }
    mode = func_150849A0(obj);
    diff = cam->unk2F8 - obj->x_position;
    distSq = diff * diff;
    diff = cam->unk2FC - obj->y_position;
    diff = diff * diff;
    distSq += diff;
    diff = cam->unk300 - obj->z_position;
    diff = diff * diff;
    distSq += diff;
    if (distSq < (dists[0] * dists[0])) {
        lod = 0;
    } else if (distSq < (dists[1] * dists[1])) {
        lod = 1;
    } else if (distSq < (dists[2] * dists[2])) {
        lod = 2;
    } else if (distSq < (dists[3] * dists[3])) {
        lod = 3;
    } else {
        lod = 4;
    }
    if ((lod >= 2) && (obj->xz_velocity < 3.0f)) {
        lod--;
    }
    if (mode) {
        if (mode == 0x5A) {
            if (lod == 0) {
                lod = 1;
            }
        }
    } else if (D_800BE616 != 0) {
        lod = 1;
    }
    if (D_800C35EA == 1) {
        lod = 0;
    }
    if (maxLod < lod) {
        lod = maxLod;
        if (lod < 0) {
            lod = 0;
        }
    }
    if (lod == -1) {
        return;
    }
    if (lod == ((u8 *)obj)[0x1C8]) {
        return;
    }
    model = (*(u8 **)((u8 *)obj + 0x2C4))[lod];
    func_150837D4(arg0, model, 0);
    ((u8 *)obj)[0x1C8] = lod;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502C974.s")

void func_1502CC34(void *arg0, s32 arg1, s32 arg2, void *arg3, s32 *arg4, s32 *arg5, s32 *arg6, s32 *arg7, s32 *arg8, s32 *arg9, s32 *argA, s32 *argB, s32 *argC, s32 *argD) {
    u8 *temp_v0;
    u8 *temp_v1;

    temp_v0 = D_800D9B68[arg1];
    *arg4 = temp_v0[0];
    temp_v1 = D_800D9B78[arg1];
    *arg5 = temp_v0[1];
    *arg6 = temp_v0[2];
    *arg7 = temp_v1[0];
    *arg8 = temp_v1[1];
    *arg9 = temp_v1[2];
    *argA = 0;
    *argB = 0;
    *argC = 0;
    *argD = *(s32 *)((u8 *)arg3 + 0xC);
    if (((u8 *)arg0)[0xA4] != 0) {
        func_1502EC34(arg0, argA, argB, argC, argD);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502CCFC.s")

void func_1502D54C(s32 arg0, s32 *arg1) {
    u8 *temp_v0;

    temp_v0 = (u8 *)&D_800CC2D0[arg0];
    if ((temp_v0[0x66] & 0xC) == 4) {
        arg1[0] = (temp_v0[0x1E0] + temp_v0[0x1DD]) / 2;
        arg1[1] = (temp_v0[0x1E1] + temp_v0[0x1DE]) / 2;
        arg1[2] = (temp_v0[0x1E2] + temp_v0[0x1DF]) / 2;
        arg1[0] = 0xFF - arg1[0];
        arg1[1] = 0xFF - arg1[1];
        arg1[2] = 0xFF - arg1[2];
        return;
    }
    arg1[2] = 0xFF;
    arg1[1] = 0xFF;
    arg1[0] = 0xFF;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502D630.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502D824.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502DB20.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502DB84.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502DF38.s")

extern u8 D_800C3E90;
extern void func_150A9984(s32, s32);

void func_1502E474(void) {
    if (D_800C3E7A != 0) {
        func_150A9984((&D_800C3E80)[D_800BE9C0], D_800C3E7A);
    }
    D_800C3E90 = 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502E4C4.s")

void func_1502E9FC(s32 arg0, s32 arg1) {
}

void func_1502EA0C(ActorInteractionFields *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5) {
    arg0->field_0xA4 = 4;
    arg0->field_0xA5 = 0;
    arg0->field_0xA6 = arg5;
    arg0->field_0xA0 = (arg4 << 24) | (arg1 << 16) | (arg2 << 8) | arg3;
    arg0->field_0xA7 = 0xFF;
}

typedef struct {
    u8 pad0[0xA4];
    /* 0xA4 */ u8 unkA4;
} S1502EA50;

void func_1502EA50(S1502EA50 *arg0) {
    arg0->unkA4 = 0x5;
}

void func_1502EA60(u8 *arg0, s32 arg1) {
    arg0[0xA4] = 2;
    arg0[0xA5] = 0xFF;
    arg0[0xA6] = arg1;
}

void func_1502EA7C(u8 *arg0, s32 arg1) {
    arg0[0xA4] = 3;
    arg0[0xA5] = 0xFF;
    arg0[0xA6] = arg1;
}

void func_1502EA98(ActorInteractionFields *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    if (arg0->field_0xA4 != 6 && arg0->field_0xA4 != 7) {
        if (arg5 != 0) {
            arg0->field_0xA5 = 0xFF;
        } else {
            arg0->field_0xA5 = 0;
        }
        arg0->field_0xA0 = (arg4 << 24) | (arg1 << 16) | (arg2 << 8) | arg3;
        arg0->field_0xA6 = arg6;
    }
    arg0->field_0xA4 = 6;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502EAFC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502EC34.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502EE8C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502EEF4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502F01C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502F264.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502F3C8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502F490.s")

void func_1502F948(ActorInteractionFields *arg0) {
    s32 idx;
    void *temp;

    if ((arg0->field_0xF8 & 0x4000) && (arg0->field_0x264 != 0) && (arg0->field_0x1D4 != 0)) {
        idx = arg0->field_0x4;
        if (arg0->field_0x1D8 == 0) {
            temp = allocate_memory(D_800C4ED0[idx] << 6, 1, 1, 2);
            arg0->field_0x1D8 = temp;
            if (temp == 0) {
                return;
            }
        }
        bcopy(arg0->field_0x1D4, arg0->field_0x1D8, D_800C4ED0[idx] << 6);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502F9FC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502FBE8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_58F80/func_1502FD70.s")
