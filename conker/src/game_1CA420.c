#include <ultra64.h>
#include "functions.h"
#include "variables.h"


extern void func_15147D64(u8 *arg0, s32 arg1);
extern void func_1519E3BC(void *arg0, s16 arg1, u8 arg2, s32 arg3);
extern s32 func_1519D030(void *arg0, s32 arg1, s16 arg2, u8 arg3, u8 arg4, s32 arg5);
extern void func_1519E688(void);
extern s32 func_1514ED3C(s32 arg0, s32 arg1, s32 *arg2);
extern s32 func_1514EC1C(s32 arg0, s32 arg1, s16 arg2);
extern s32 D_800E0920;
extern s32 func_15147A80(void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
extern s32 func_1519E304(void *, void *, f32, f32, f32, f32);

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} Vec1519D030;

typedef struct {
    f32 unk0;
    f32 unk4;
    u8 unk8;
    u8 pad9[3];
    s32 unkC;
    u8 unk10;
    u8 pad11[3];
    Vec1519D030 unk14;
    s16 unk20;
    s16 unk22;
    s16 unk24;
    u8 pad26[2];
    f32 unk28;
    f32 unk2C;
    f32 unk30;
    f32 unk34;
    s16 unk38;
    s16 unk3A;
    u8 unk3C;
    u8 unk3D;
    u8 unk3E;
    u8 unk3F;
} D_800A8B80_Entry;

extern D_800A8B80_Entry D_800A8B80[];

typedef struct {
    Vec1519D030 unk0;
    s16 unkC;
    u16 unkE;
    s32 unk10;
    u8 unk14;
    u8 unk15;
    u8 pad16[2];
    s32 unk18;
} Header1519D030;

typedef struct {
    void *unk0;
    u8 unk4;
    u8 unk5;
    u8 unk6;
    u8 unk7;
    Vec1519D030 unk8;
    Vec1519D030 unk14;
    f32 unk20;
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    f32 unk30;
    f32 unk34;
    f32 unk38;
    f32 unk3C;
    u8 unk40;
    u8 pad41;
    s16 unk42;
    s16 unk44;
    s16 unk46;
    s16 unk48;
    s16 unk4A;
    u8 unk4C;
    u8 pad4D[3];
    f32 unk50;
    f32 unk54;
    f32 unk58;
    u8 unk5C;
    u8 unk5D;
    u8 unk5E;
    u8 unk5F;
} Payload1519D030;

typedef struct Obj1519E464 {
    s32 unk0;
    u8 pad4[0x37];
    u8 unk3B;
    u8 pad3C[0x48];
    u16 unk84;
    u8 pad86[0x14E];
    s32 unk1D4;
    u8 pad1D8[0x11C];
    s32 unk2F4;
} Obj1519E464;

typedef struct Sub1519E464 {
    Obj1519E464 *unk0;
    u8 unk4;
    u8 pad5[3];
    s32 unk8;
} Sub1519E464;

typedef struct Arg1519E464 {
    u8 unk0;
    u8 unk1;
    u8 pad2[0xA];
    u8 unkC;
    u8 unkD;
    s16 unkE;
    u8 pad10[0x18];
    Sub1519E464 unk28;
} Arg1519E464;

void func_1519CF70(u8 arg0) {
    u8 sp1C[4];

    sp1C[0] = arg0;
    func_15147D64(sp1C, 6);
}

struct s_1519CFA0 {
    char pad0[0x1E];
    u16 unk1E;
    char pad20[0x10];
    u8 unk30;
    char pad31[0x67];
    u8 *unk98;
};

void func_1519CFA0(struct s_1519CFA0 *arg0) {
    u8 *temp;

    arg0->unk30 = 0;
    temp = arg0->unk98;
    arg0->unk1E &= 0xFFFD;
    temp[6] |= 1;
    temp[6] |= 4;
}

extern void func_1514EDF0(struct260 *, s32);
extern void func_151478F4(struct s_1519CFA0 *);

void func_1519CFD0(struct s_1519CFA0 *arg0) {
    s32 *temp;

    temp = (s32 *)arg0->unk98;
    func_1514EDF0((struct260 *)arg0, *temp);
    func_151478F4(arg0);
}

extern void func_15147928(struct s_1519CFA0 *);

void func_1519D000(struct s_1519CFA0 *arg0) {
    s32 *temp;

    temp = (s32 *)arg0->unk98;
    func_1514EDF0((struct260 *)arg0, *temp);
    func_15147928(arg0);
}

s32 func_1519D030(void *arg0, s32 arg1, s16 arg2, u8 arg3, u8 arg4, s32 arg5) {
    Header1519D030 header;
    Payload1519D030 payload;
    s32 temp_v0;
    D_800A8B80_Entry *entry;
    s32 flag;

    entry = &D_800A8B80[arg1];

    if (arg0 == NULL) {
        return 0;
    }

    payload.unk20 = 0.0f;
    payload.unk50 = ((struct127 *)arg0)->x_position;
    payload.unk54 = ((struct127 *)arg0)->y_position;
    payload.unk58 = ((struct127 *)arg0)->z_position;
    payload.unk0 = arg0;
    payload.unk4 = ((struct127 *)arg0)->unique_id;
    payload.unk6 = 2;
    payload.unk7 = 0;
    payload.unk4C = arg1;
    header.unkC = arg2;
    payload.unk2C = 0.0f;

    flag = (arg3 != 0) ? 1 : 0;
    header.unkE = flag | 2;

    payload.unk24 = entry->unk0;
    payload.unk28 = entry->unk4;
    payload.unk40 = entry->unk8;
    header.unk15 = entry->unkC;
    payload.unk5 = entry->unk10;
    payload.unk8 = entry->unk14;
    payload.unk42 = entry->unk20;
    payload.unk44 = entry->unk22;
    payload.unk46 = entry->unk24;
    payload.unk38 = entry->unk28;
    payload.unk34 = entry->unk2C;
    payload.unk30 = entry->unk30;
    payload.unk3C = entry->unk34;
    payload.unk48 = entry->unk38;
    payload.unk4A = entry->unk3A;
    payload.unk5C = entry->unk3C;
    payload.unk5D = entry->unk3D;
    payload.unk5E = entry->unk3E;
    payload.unk5F = entry->unk3F;

    if (func_1519E304(&payload, &header.unk0, 0.0f, 0.0f, 0.0f, 1.0f) != 0) {
        payload.unk14 = header.unk0;
        header.unkE |= 4;
    }

    header.unk10 = 4;
    temp_v0 = func_15147A80(&header, 0x60, 0x24, 3, 3, 3, 0, 0, 0, arg4, arg5);
    if (temp_v0 != 0) {
        memcpy((void *)*(s32 *)((u8 *)temp_v0 + 0x98), &payload, 0x60);
    }
    return temp_v0;
}

extern f32 D_800BE9A4;
extern s32 D_800BE9E4;
typedef struct 
{
  f32 unk0;
  f32 unk4;
  f32 unk8;
  f32 unkC;
  f32 unk10;
  f32 unk14;
  f32 unk18;
  s16 unk1C;
  s16 unk1E;
  u8 unk20;
  u8 pad21[3];
} Trail1519D240;
typedef struct 
{
  f32 unk0;
  f32 unk4;
  f32 unk8;
  f32 unkC;
  f32 unk10;
  f32 unk14;
  f32 unk18;
  s16 unk1C;
  s16 unk1E;
  u8 unk20;
  u8 pad21[3];
} Trail1519D240Alt;
typedef struct 
{
  u8 pad0[0x25];
  u8 unk25;
  u8 pad26[6];
  s8 unk2C;
  s8 unk2D;
  s8 unk2E;
  u8 pad2F[0x25];
  f32 unk54;
  f32 unk58;
  f32 unk5C;
  u8 pad60[0x34];
  Trail1519D240 *unk94;
  Payload1519D030 *unk98;
} Arg1519D240;
s32 func_1519D240(Arg1519D240 *arg0)
{
  Payload1519D030 *payload;
  Trail1519D240 *entries;
  s32 index;
  s32 offset;
  register s32 mask;
  s16 temp;
  Trail1519D240 *entry;
  Trail1519D240Alt *same_entry;
  payload = arg0->unk98;
  entries = arg0->unk94;
  if ((arg0->unk2C < 2) && (payload->unk6 & 1))
  {
    return 0;
  }
  index = arg0->unk2E;
  mask = -3;
  if (index != arg0->unk2D)
  {
    do
    {
      index -= 1;
      if (index < 0)
      {
        index = arg0->unk25 - 1;
      }
      offset = index * (sizeof(Trail1519D240));
      entry = &entries[index];
      entry->unk20 = 0xFF;
      same_entry = (Trail1519D240Alt *) (((u8 *) entries) + offset);
      temp = entry->unk1E;
      entry->unkC *= payload->unk30;
      entry->unk10 += payload->unk24 * D_800BE9A4;
      entry->unk14 *= payload->unk30;
      entry->unk0 += same_entry->unkC * D_800BE9A4;
      entry->unk4 += same_entry->unk10 * D_800BE9A4;
      entry->unk8 += same_entry->unk14 * D_800BE9A4;
      if (temp > 0)
      {
        entry->unk1E = temp - D_800BE9E4;
      }
      else
      {
        entry->unk1C -= D_800BE9E4 * payload->unk46;
      }
      entry->unk18 += D_800BE9A4 * payload->unk34;
      if (entry->unk1C < 0)
      {
        payload->unk6 &= mask;
        if (index != arg0->unk2D)
        {
          do
          {
            arg0->unk2D++;
            if (arg0->unk2D == arg0->unk25)
            {
              arg0->unk2D = 0;
            }
            arg0->unk2C--;
          }
          while (index != arg0->unk2D);
        }
        entries[arg0->unk2D].unk1C = 0;
      }
    }
    while (index != arg0->unk2D);
  }
  if (arg0->unk2C > 0)
  {
    entry = entries;
    mask = arg0->unk2D;
    entry += mask;
    *((Vec1519D030 *) (&arg0->unk54)) = *((Vec1519D030 *) (&entry->unk0));
  }
  else
  {
    arg0->unk54 = 0.0f;
    arg0->unk58 = 0.0f;
    arg0->unk5C = 0.0f;
  }
  return 1;
}


#pragma GLOBAL_ASM("asm/nonmatchings/game_1CA420/func_1519D454.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_1CA420/func_1519D9F4.s")

typedef struct {
    s32 unk0;
    u8 unk4;
    u8 pad5[0x47];
    u8 unk4C;
} SubA_1519E1F4;

typedef struct {
    union {
        s32 w0;
        u8 b0;
    } u0;
    union {
        s32 w4;
        u8 b4;
    } u4;
    u8 unk8;
    u8 unk9;
} ArgB_1519E1F4;

void func_1519E1F4(struct s_1519CFA0 *arg0, s32 arg1, u8 arg2) {
    SubA_1519E1F4 *temp_v0 = (SubA_1519E1F4 *)arg0->unk98;
    ArgB_1519E1F4 *b = (ArgB_1519E1F4 *)arg1;

    if (arg2 == 0) {
        if ((b->u0.w0 == temp_v0->unk0) || (b->u4.b4 == temp_v0->unk4)) {
            func_1519CFA0(arg0);
        }
    } else if (arg2 == 6) {
        if (temp_v0->unk4C == b->u0.b0) {
            func_1519CFA0(arg0);
        }
    } else if (arg2 == 7) {
        if ((b->u0.w0 == temp_v0->unk0) || (b->u4.b4 == temp_v0->unk4)) {
            func_1519CFA0(arg0);
        }
    } else if (arg2 == 0x2D) {
        if (temp_v0->unk0 == b->u0.w0) {
            temp_v0->unk0 = b->u4.w4;
            temp_v0->unk4 = b->unk9;
        } else if (temp_v0->unk0 == b->u4.w4) {
            temp_v0->unk0 = b->u0.w0;
            temp_v0->unk4 = b->unk8;
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1CA420/func_1519E304.s")

void func_1519E3BC(void *arg0, s16 arg1, u8 arg2, s32 arg3) {
    func_1519E688();
    func_1519D030(arg0, 3, 0x12C, 0, arg2, arg3);
    func_1519D030(arg0, 4, 0x12C, 0, arg2, arg3);
    func_151491F4(arg1, 6, -1, 1, 3, 0, arg2, arg3);
}

void func_1519E464(Arg1519E464 *arg0) {
    Sub1519E464 *sub;
    u8 invalid;
    s32 temp_v0;

    invalid = 0;
    sub = &arg0->unk28;
    if (arg0->unk28.unk0->unk0 == 0) {
        invalid = 1;
    }
    if (sub->unk0->unk3B == sub->unk4) {
    } else {
        invalid = 1;
    }
    if (invalid == 0) {
        if (sub->unk0->unk1D4 != 0) {
            invalid = 1;
            temp_v0 = func_1519D030(sub->unk0, sub->unk8, arg0->unkE, arg0->unkD & 1, arg0->unkC, arg0->unk1);
            if (temp_v0 != 0) {
                if (func_1514ED3C(sub->unk0->unk2F4, (s32)arg0, 0) != 0) {
                    func_1514EC1C(temp_v0, (s32)sub->unk0, 0x10);
                }
            }
        }
    }
    if (invalid != 0) {
        arg0->unkE = -1;
        arg0->unkD |= 1;
    }
}

typedef struct {
    s32 unk0;
    u8  unk4;
} SubA_1519E570;

typedef struct {
    s32 unk0;
    union {
        s32 w4;
        u8  b4;
    } u4;
    u8  unk8;
    u8  unk9;
} ArgB_1519E570;

void func_1519E570(struct260 *arg0, s32 arg1, u8 arg2) {
    SubA_1519E570 *temp_v0 = (SubA_1519E570 *)((u8 *)arg0 + 0x28);
    ArgB_1519E570 *b = (ArgB_1519E570 *)arg1;

    if (arg2 == 0) {
        if ((b->unk0 == temp_v0->unk0) || (b->u4.b4 == temp_v0->unk4)) {
            func_1516972C((struct102 *)arg0);
        }
    } else if (arg2 == 0x2D) {
        if (temp_v0->unk0 == b->unk0) {
            temp_v0->unk0 = b->u4.w4;
            temp_v0->unk4 = b->unk9;
        } else if (temp_v0->unk0 == b->u4.w4) {
            temp_v0->unk0 = b->unk0;
            temp_v0->unk4 = b->unk8;
        }
    }
}

void func_1519E61C(struct102 *arg0, s32 arg1, u8 arg2) {
    if (arg2 == 0 || arg2 == 9) {
        func_1516972C(arg0);
    }
}

extern void func_1519CF70(u8);

void func_1519E65C(s32 arg0) {
    func_1519CF70(3);
    func_1519CF70(4);
}

void func_1519E688(void) {
    func_1519CF70(3);
    func_1519CF70(4);
    func_15147D64(0, 9);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_1CA420/func_1519E6BC.s")

void func_1519E754(Arg1519E464 *arg0) {
    Sub1519E464 *sub;
    u8 invalid;

    invalid = 0;
    sub = &arg0->unk28;
    if (arg0->unk28.unk0->unk0 == 0) {
        invalid = 1;
    }
    if (sub->unk0->unk3B != sub->unk4) {
        invalid = 1;
    }
    if (invalid == 0) {
        sub->unk8 += D_800BE9E4;
        if (sub->unk0->unk84 != 0x7C) {
            invalid = 1;
            if (sub->unk8 >= 0xC9) {
                func_1519E3BC(sub->unk0, 0x12C, arg0->unkC, arg0->unk1);
            }
        }
    }
    if (invalid != 0) {
        D_800E0920 = 0;
        arg0->unkE = -1;
        arg0->unkD |= 1;
    }
}

void func_1519E818(struct260 *arg0, s32 arg1, u8 arg2) {
    SubA_1519E570 *temp_v0 = (SubA_1519E570 *)((u8 *)arg0 + 0x28);
    ArgB_1519E570 *b = (ArgB_1519E570 *)arg1;

    if (arg2 == 0) {
        if ((b->unk0 == temp_v0->unk0) || (b->u4.b4 == temp_v0->unk4)) {
            func_1516972C((struct102 *)arg0);
            D_800E0920 = 0;
    skip:
            ;
        }
    } else if (arg2 == 0x2D) {
        if (temp_v0->unk0 == b->unk0) {
            temp_v0->unk0 = b->u4.w4;
            temp_v0->unk4 = b->unk9;
        } else if (temp_v0->unk0 == b->u4.w4) {
            temp_v0->unk0 = b->unk0;
            temp_v0->unk4 = b->unk8;
        }
    }
}

extern void func_1514EDF0(struct260 *, s32);

void func_1519E8CC(struct260 *arg0) {
    func_1514EDF0(arg0, *(s32 *)((u8 *)arg0 + 0x28));
    func_1514933C(arg0);
}

void func_1519E8F8(struct260 *arg0) {
    func_1514EDF0(arg0, *(s32 *)((u8 *)arg0 + 0x28));
    func_15149368(arg0);
}

void func_1519E924(struct260 *arg0) {
    D_800E0920 = 0;
    func_1514933C(arg0);
}

void func_1519E948(struct260 *arg0) {
    D_800E0920 = 0;
    func_15149368(arg0);
}
