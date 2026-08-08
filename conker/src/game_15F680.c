#include <ultra64.h>
#define func_15169260 func_15169260_s32
#include "functions.h"
#undef func_15169260
#include "variables.h"

void func_15132444(struct102 *arg0);
s32 func_1513264C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, u8 arg5, s32 arg6);
s32 func_151464B8(s16 *arg0);
extern u8 D_800C3E90;
extern s32 (*D_8008998C[])(s32);
extern s32 D_800A3880[];
extern s32 D_800DC640[];
s32 func_1502B6BC(s32 *arg0, s32 arg1, s32 *arg2, s32 arg3, s32 arg4, s32 arg5);
s32 func_1510CE60(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 *arg4);
void func_15168E54(s32 arg0, s32 arg1);
s32 func_15046C80(f32 *arg0, s32 arg1, f32 arg2, void *arg3);
s32 func_15044380(f32 arg0, f32 arg1, f32 arg2, void *arg3, s32 arg4, s32 arg5);

typedef struct {
    u8 bytes[0x10];
    u16 tail;
} Bytes18_15132DDC;

typedef struct {
    u8 pad_0[0x10];
    f32 field_0x10;
    u8 pad_14[0xC];
    f32 field_0x20;
    f32 field_0x24;
    f32 field_0x28;
    u8 pad_2C[0xC];
    f32 field_0x38;
    f32 field_0x3C;
    f32 field_0x40;
    f32 field_0x44;
    f32 field_0x48;
    f32 field_0x4C;
    f32 field_0x50;
    f32 field_0x54;
    f32 field_0x58;
    f32 field_0x5C;
    s32 field_0x60;
    u8 pad_64[0xF];
    u8 field_0x73;
    u8 field_0x74;
    u8 field_0x75;
    u8 pad_76[0x9A];
    f32 field_0x110;
    Bytes18_15132DDC field_0x114;
    u8 pad_126[0x6];
    u8 field_0x12C;
    u8 field_0x12D;
    u8 pad_12E[0x6];
    f32 field_0x134;
    f32 field_0x138;
    f32 field_0x13C;
    f32 field_0x140;
    f32 field_0x144;
    u8 field_0x148;
    u8 field_0x149;
    s8 field_0x14A;
} Func15132DDCArg0;

typedef struct {
    s32 field_0x0;
    u8 pad_4[0x10];
    f32 field_0x14;
    f32 field_0x18;
    f32 field_0x1C;
    u8 pad_20[0x8];
    f32 field_0x28;
    u8 pad_2C[0xB8];
    s16 field_0xE4;
    s16 field_0xE6;
    u8 pad_E8[0x10];
    s32 field_0xF8;
    u8 pad_FC[0x50];
    f32 field_0x14C;
    f32 field_0x150;
    u8 pad_154[0x2C];
    f32 field_0x180;
    u8 pad_184[0x4];
    s32 field_0x188;
    Bytes18_15132DDC field_0x18C;
    u8 pad_19E[0x192];
    f32 field_0x330[3];
    f32 field_0x33C[3];
} Func15132DDCLocals;

typedef s32 (*Func15132DDCCallback34)(Func15132DDCArg0 *, f32, f32, f32, f32, void *);
typedef s32 (*Func15132DDCCallback70)(Func15132DDCArg0 *, f32, f32, f32, f32);
typedef s32 (*Func15132DDCCallback74)(Func15132DDCArg0 *, void *, f32, f32, f32);

extern Func15132DDCCallback34 D_80089934[];
extern Func15132DDCCallback70 D_80089970[];
extern Func15132DDCCallback74 D_80089974[];
extern f32 D_800A386C;
extern f32 D_800A3870;

typedef struct {
    u8 pad_0[0x60];
    s32 field_0x60;
    u8 pad_1[0x4];
    u8 field_0x68;
} Func151323ACArg0;

typedef struct {
    u8 pad0[0x60];
    u32 flags;
    u8 pad64[0x8];
    s16 *unk6C;
    u8 pad70[0x8];
    u8 unk78;
} Obj15132A88;

typedef struct {
    u8 pad_0[0x18];
    s32 field_0x18;
    s32 field_0x1C;
    s32 field_0x20;
    f32 field_0x24;
    f32 field_0x28;
    f32 field_0x2C;
    f32 field_0x30;
    f32 field_0x34;
    f32 field_0x38;
    f32 field_0x3C;
    f32 field_0x40;
} MatrixTransformFields;

typedef struct {
    u8 pad_0[0x18];
    f32 field_0x18;
    f32 field_0x1C;
    s32 field_0x20;
    f32 field_0x24;
    f32 field_0x28;
    u8 pad_1[0xC];
    f32 field_0x38;
    f32 field_0x3C;
    f32 field_0x40;
} TransformDispatchFields;

typedef struct {
    u8 pad[4];
    f32 m[4][4];
} PaddedMtxF15133A94;

typedef struct {
    u8 pad_0[0x10];
    f32 field_0x10;
    f32 field_0x14;
    u8 pad_1[0x24];
    f32 field_0x3C;
    u8 pad_2[0x4];
    f32 field_0x44;
    f32 field_0x48;
    f32 field_0x4C;
    f32 field_0x50;
    f32 field_0x54;
    f32 field_0x58;
    f32 field_0x5C;
    s32 field_0x60;
} MotionFields15133;

typedef struct {
    s32 unk0;
    s32 unk4;
} Data15133E3C;

typedef struct {
    u8 pad_0[0x7C];
    s32 field_0x7C;
    u8 field_0x80;
} InteractionTargetFields;

typedef struct {
    s32 field_0x0;
    u8 field_0x4;
} InteractionKeyFields;

extern Data15133E3C D_800A3860;
void func_15169260(Data15133E3C *, s32, s32, u8);

typedef struct {
    u8 pad_0[0x38];
    struct17 field_0x38;
    u8 pad_44[0x1C];
    u32 field_0x60;
    s16 field_0x64;
    u8 pad_66[0xA];
    u8 field_0x70;
    u8 field_0x71;
    u8 field_0x72;
    u8 pad_73[0x3];
    u8 field_0x76;
    u8 field_0x77;
    u8 pad_78[0xA];
    s16 field_0x82;
    s16 field_0x84;
    u8 pad_86[0xC2];
    u8 field_0x148;
} Func151321D0Arg0;

typedef s32 (*Func151321D0Callback)(Func151321D0Arg0 *);

extern Func151321D0Callback D_800898B0[];
extern Func151321D0Callback D_80089914[];
extern Func151321D0Callback D_8008997C[];
extern Func151321D0Callback D_80089988[];
s32 func_1514672C(struct17 *arg0);

void func_151321D0(Func151321D0Arg0 *arg0) {
    s32 temp;
    u8 stopped;

    stopped = 0;
    arg0->field_0x60 &= 0xFFDFFFFF;
    if ((arg0->field_0x60 & 0x10) && (arg0->field_0x148 & 0x18)) {
        temp = D_80089988[arg0->field_0x77](arg0);
        if (temp == 0) {
            stopped = 1;
        }
    } else if (arg0->field_0x71 != 0) {
        temp = D_800898B0[arg0->field_0x71](arg0);
        if (temp == 0) {
            stopped = 1;
        }
    }

    if ((arg0->field_0x72 != 0) && !stopped) {
        temp = D_80089914[arg0->field_0x72](arg0);
        if (temp == 0) {
            stopped = 1;
        }
    }

    if ((arg0->field_0x60 & 0x80) && !stopped) {
        arg0->field_0x64 -= D_800BE9E4;
        if (arg0->field_0x64 < 0) {
            stopped = 1;
        }
    }

    if ((arg0->field_0x60 & 0x2000) && !stopped) {
        if (arg0->field_0x64 < arg0->field_0x82) {
            temp = arg0->field_0x64 * arg0->field_0x84;
            if (temp < arg0->field_0x70) {
                arg0->field_0x70 = temp;
            }
        }
    }

    if (!stopped && !(arg0->field_0x60 & 0x80000)) {
        stopped = func_1514672C(&arg0->field_0x38) == 0;
    }

    if (stopped) {
        if (arg0->field_0x76 != 0) {
            D_8008997C[arg0->field_0x76](arg0);
        }
        func_1516972C((struct102 *)arg0);
    }
}

extern void (*D_800899B0[])(s32);

void func_151323AC(Func151323ACArg0 *arg0) {
    s32 idx;

    idx = (arg0->field_0x60 & 0x100) ? arg0->field_0x68 : 0;
    D_800899B0[idx]((s32)arg0);
}

extern void (*D_800899D4[])(s32);

void func_151323F8(Func151323ACArg0 *arg0) {
    s32 idx;

    idx = (arg0->field_0x60 & 0x100) ? arg0->field_0x68 : 0;
    D_800899D4[idx]((s32)arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_15F680/func_15132444.s")

void func_15132570(struct102 *arg0) {
    func_15132444(arg0);
    func_15169804(arg0);
}

void func_1513259C(struct102 *arg0) {
    func_15132444(arg0);
    func_15169824(arg0);
}

void func_151325C8(void *arg0) {
    s32 i;
    s32 *p;

    for (i = 0, p = (s32 *)arg0; i <= D_80082FA0; i++, p++) {
        if (p[0x55] != 0) {
            func_100043B4((s32 *)p[0x55], 4);
        }
    }

    p = (s32 *)((s32 *)arg0)[0x59];
    if (((s32 *)arg0)[0x59] != 0) {
        func_100043B4(p, 4);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_15F680/func_1513264C.s")

s32 func_15132A4C(s32 arg0, s32 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5) {
    return func_1513264C(arg0, arg1, arg2, 0, arg3, arg4, arg5);
}

void func_15132A88(Obj15132A88 *arg0) {
    s16 *temp;
    s32 ret;
    s32 flags;

    arg0->flags &= 0xFFDFFFFF;
    if (arg0->flags & 0x20000) {
        return;
    }

    if (arg0->flags & 0x400) {
        temp = arg0->unk6C;
        if (temp != NULL) {
            if (func_151464B8(temp) != 0) {
                return;
            }
        }
    }

    flags = arg0->flags;
    if (flags & 0x80000) {
        arg0->flags = flags | 0x200000;
        return;
    }

    ret = D_8008998C[arg0->unk78]((s32)arg0 + 0x90 + (D_800BE9C0 << 6));
    if (ret == -1) {
        func_1516972C((struct102 *)arg0);
        return;
    }

    if (ret == 0) {
        arg0->flags &= 0xFFFBFFFF;
    } else {
        arg0->flags |= 0x240000;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_15F680/func_15132B80.s")

s32 func_15132DDC(Func15132DDCArg0 *arg0) {
    Func15132DDCLocals sp38;
    register f32 temp_f0;

    if (arg0->field_0x60 & 7) {
        memcpy(sp38.field_0x33C, &arg0->field_0x38, 0xC);
    }

    if (arg0->field_0x60 & 8) {
        arg0->field_0x48 += arg0->field_0x5C * D_800BE9A4;
    }

    if (arg0->field_0x60 & 0x20) {
        arg0->field_0x38 += arg0->field_0x44 * D_800BE9A4;
        arg0->field_0x3C += arg0->field_0x48 * D_800BE9A4;
        arg0->field_0x40 += arg0->field_0x4C * D_800BE9A4;
    }

    if (arg0->field_0x60 & 0x40) {
        arg0->field_0x20 += arg0->field_0x50 * D_800BE9A4;
        arg0->field_0x24 += arg0->field_0x54 * D_800BE9A4;
        arg0->field_0x28 += arg0->field_0x58 * D_800BE9A4;
    }

    if (arg0->field_0x60 & 7) {
        sp38.field_0x330[0] = arg0->field_0x38;
        sp38.field_0x330[1] = sp38.field_0x33C[1];
        sp38.field_0x330[2] = arg0->field_0x40;

        if (func_15046C80(sp38.field_0x330, 0, arg0->field_0x3C - arg0->field_0x10, &arg0->field_0x110) != 0) {
            if ((arg0->field_0x12D == 1) || ((arg0->field_0x12D == 2) && (arg0->field_0x12C & 1))) {
                arg0->field_0x148 |= 1;
                if (arg0->field_0x60 & 0x10) {
                    temp_f0 = sqrtf((arg0->field_0x44 * arg0->field_0x44) +
                                    (arg0->field_0x48 * arg0->field_0x48) +
                                    (arg0->field_0x4C * arg0->field_0x4C));
                    if (temp_f0 > 1.0f) {
                        arg0->field_0x148 |= 8;
                        arg0->field_0x140 = temp_f0;
                        arg0->field_0x144 = 1.0f / temp_f0;
                    }
                }

                if (arg0->field_0x73 != 0) {
                    if (D_80089934[arg0->field_0x73](arg0, sp38.field_0x33C[0], sp38.field_0x33C[1],
                                                     sp38.field_0x33C[2], arg0->field_0x110,
                                                     &arg0->field_0x114) == 0) {
                        return 0;
                    }
                }

                if (arg0->field_0x60 & 0x10) {
                    memcpy(&arg0->field_0x134, &arg0->field_0x38, 0xC);
                }
            }

            if (arg0->field_0x12D == 3) {
                arg0->field_0x148 |= 2;
                if (arg0->field_0x74 != 0) {
                    if (D_80089970[arg0->field_0x74](arg0, sp38.field_0x33C[0], sp38.field_0x33C[1],
                                                     sp38.field_0x33C[2], arg0->field_0x110) == 0) {
                        return 0;
                    }
                }
            }
        }

        if (arg0->field_0x60 & 4) {
            sp38.field_0x0 = 4;
            sp38.field_0x14 = arg0->field_0x38;
            sp38.field_0x18 = arg0->field_0x3C;
            sp38.field_0x1C = arg0->field_0x40;
            sp38.field_0x188 = 0;
            sp38.field_0x18C = arg0->field_0x114;
            sp38.field_0x28 = 1.0f;
            sp38.field_0x14C = 1.0f;
            sp38.field_0xE4 = (s16)(s32)arg0->field_0x10;
            sp38.field_0x150 = 1.0f;
            sp38.field_0xE6 = (s16)(s32)arg0->field_0x10;
            if (arg0->field_0x12C & 2) {
                sp38.field_0x180 = arg0->field_0x110;
            } else {
                sp38.field_0x180 = D_800A386C;
            }
            sp38.field_0xF8 = 0;

            if (func_15044380(sp38.field_0x33C[0], sp38.field_0x33C[1], sp38.field_0x33C[2], &sp38, 0, 0) != 0) {
                arg0->field_0x148 |= 4;
                if (arg0->field_0x60 & 0x10) {
                    temp_f0 = sqrtf((arg0->field_0x44 * arg0->field_0x44) +
                                    (arg0->field_0x48 * arg0->field_0x48) +
                                    (arg0->field_0x4C * arg0->field_0x4C));
                    if (temp_f0 > 1.0f) {
                        arg0->field_0x148 |= 0x10;
                        arg0->field_0x140 = temp_f0;
                        arg0->field_0x144 = 1.0f / temp_f0;
                        arg0->field_0x14A = (s8)(s32)(func_150484A0(sp38.field_0x14 - arg0->field_0x38,
                                                                     sp38.field_0x1C - arg0->field_0x40) *
                                                       D_800A3870);
                    }
                }

                if (arg0->field_0x75 != 0) {
                    if (D_80089974[arg0->field_0x75](arg0, &sp38, sp38.field_0x33C[0],
                                                     sp38.field_0x33C[1], sp38.field_0x33C[2]) == 0) {
                        return 0;
                    }
                }

                if (arg0->field_0x60 & 0x10) {
                    memcpy(&arg0->field_0x134, &arg0->field_0x38, 0xC);
                }
            }
        }
    }

    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_15F680/func_151332DC.s")

s32 func_151424F4(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, f32 arg10, f32 arg11);

s32 func_15133510(s32 arg0, MatrixTransformFields *arg1) {
    func_151424F4(arg0,
                  arg1->field_0x18,
                  arg1->field_0x1C,
                  arg1->field_0x20,
                  arg1->field_0x24,
                  arg1->field_0x28,
                  arg1->field_0x2C,
                  arg1->field_0x30,
                  arg1->field_0x34,
                  arg1->field_0x38,
                  arg1->field_0x3C,
                  arg1->field_0x40);
    return 1;
}

extern void (*D_800899F8[])(void *, void *, u8);
void func_151B9660(void *arg0);
typedef struct 
{
  u8 pad_0[0x60];
  s32 field_0x60;
  u8 pad_64[2];
  u16 field_0x66;
  u8 field_0x68;
  u8 pad_69[0x13];
  s32 field_0x7C;
  u8 field_0x80;
} Func15133588Arg0;
typedef struct 
{
  s32 field_0x0;
  s32 field_0x4;
  u8 field_0x8;
  u8 field_0x9;
} Func15133588Arg1;
void func_15133588(Func15133588Arg0 *arg0, Func15133588Arg1 *arg1, u8 arg2)
{
  s32 temp_v0;
  s32 temp_v0_2;
  s32 temp_v1;
  u8 var_v0;
  void (*callback)(void *, void *, u8);
  temp_v0 = arg2;
  if ((temp_v0 == 0x1B) && (arg0->field_0x66 == 0x22))
  {
    func_151B9660(arg0);
  }
  if (temp_v0 == 0x2D)
  {
    temp_v0_2 = arg1->field_0x0;
    ;
    if (temp_v0_2 == arg0->field_0x7C)
    {
      arg0->field_0x7C = arg1->field_0x4;
      arg0->field_0x80 = arg1->field_0x9;
    }
    else
      if (arg0->field_0x7C != arg1->field_0x4)
    {
    }
    else
    {
      arg0->field_0x7C = temp_v0_2;
      arg0->field_0x80 = arg1->field_0x8;
      second_update_done:
      ;

      ;
      ;
    }
  }
  else
    if (temp_v0 == 0)
  {
    temp_v0_2 = arg1->field_0x0;
    if ((temp_v0_2 == arg0->field_0x7C) || (arg0->field_0x80 == (*((u8 *) (&arg1->field_0x4)))))
    {
      arg0->field_0x7C = 0;
      arg0->field_0x80 = 0;
    }
  }
  var_v0 = (arg0->field_0x60 & 0x100) ? (arg0->field_0x68) : (0);
  callback = D_800899F8[var_v0];
  if (0 != callback)
  {
    callback(arg0, arg1, arg2);
  }
}


s32 func_151336A8(s32 arg0, s32 **arg1, s32 arg2) {
    s32 sp2C;
    s32 sp28;

    *arg1 = (s32 *)func_1502B6BC(&sp2C, 0, &sp28, 2, 9, D_800A3880[arg0]);
    if (*arg1 == 0) {
        return 0;
    }
    func_1510CE60(**arg1, 0, 1, 0x3E, &D_800DC640[arg0]);
    func_15168E54(**arg1, (s32)*arg1);
    return 1;
}

s32 func_15142838(s32 arg0, f32 arg1, f32 arg2, s32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 arg7, f32 arg8);

s32 func_15133760(s32 arg0, TransformDispatchFields *arg1) {
    func_15142838(arg0,
                  arg1->field_0x18,
                  arg1->field_0x1C,
                  arg1->field_0x20,
                  arg1->field_0x24,
                  arg1->field_0x28,
                  arg1->field_0x38,
                  arg1->field_0x3C,
                  arg1->field_0x40);
    return 1;
}

s32 func_151337C0(f32 *arg0) {
    arg0[14] += arg0[17] * D_800BE9A4;
    arg0[15] += (arg0[18] * D_800BE9A4) + (((arg0[23] * D_800BE9A4) * D_800BE9A4) * 0.5f);
    arg0[16] += arg0[19] * D_800BE9A4;
    arg0[18] += arg0[23] * D_800BE9A4;
    arg0[8] += arg0[20] * D_800BE9A4;
    arg0[9] += arg0[21] * D_800BE9A4;
    arg0[10] += arg0[22] * D_800BE9A4;
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_15F680/func_15133894.s")

s32 func_151339D4(MotionFields15133 *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4) {
    f32 temp;

    arg0->field_0x3C = arg0->field_0x10 + arg4;
    temp = arg0->field_0x14;
    arg0->field_0x44 = arg0->field_0x44 * temp;
    arg0->field_0x48 = arg0->field_0x48 * -temp;
    arg0->field_0x4C = arg0->field_0x4C * temp;
    arg0->field_0x50 = arg0->field_0x50 * temp;
    arg0->field_0x54 = arg0->field_0x54 * temp;
    arg0->field_0x58 = arg0->field_0x58 * temp;
    return 1;
}

s32 func_15133A50(MotionFields15133 *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4) {
    arg0->field_0x3C = arg0->field_0x10 + arg4;
    arg0->field_0x44 = 0.0f;
    arg0->field_0x48 = 0.0f;
    arg0->field_0x4C = 0.0f;
    arg0->field_0x50 = 0.0f;
    arg0->field_0x54 = 0.0f;
    arg0->field_0x58 = 0.0f;
    return 1;
}

s32 func_15133A94(Mtx *arg0, u8 *arg1) {
    struct127 *obj;
    struct255 *mtx;
    PaddedMtxF15133A94 sp18;
    u8 *src;

    obj = *(struct127 **)(arg1 + 0x7C);
    if ((obj == NULL) || (obj->interaction_state == 0) || (obj->id == 0xFF) ||
        (arg1[0x80] != *(u8 *)((u8 *)obj + 0x3B))) {
        return -1;
    }
    mtx = obj->unk1D4;
    if (mtx == NULL) {
        return 0;
    }
    if ((obj->unk74 & 0xF) == 0xF) {
        return 0;
    }
    if (D_800C3E90) {
        src = (u8 *)mtx;
        src += arg1[0x170] << 6;
        memcpy(arg0, src, 0x40);
        return 1;
    }
    src = (u8 *)mtx;
    src += arg1[0x170] << 6;
    memcpy(sp18.m, src, 0x40);
    sp18.m[0][3] = 0.0f;
    sp18.m[1][3] = 0.0f;
    sp18.m[2][3] = 0.0f;
    sp18.m[3][3] = 1.0f;
    guMtxF2L(sp18.m, arg0);
    return 1;
}

s32 func_15133B98(MotionFields15133 *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4, s32 arg5) {
    f32 temp;

    temp = arg0->field_0x14;
    arg0->field_0x3C = arg0->field_0x10 + arg4;
    arg0->field_0x44 = arg0->field_0x44 * temp;
    arg0->field_0x48 = arg0->field_0x48 * -temp;
    arg0->field_0x4C = arg0->field_0x4C * temp;
    arg0->field_0x50 = arg0->field_0x50 * temp;
    arg0->field_0x54 = arg0->field_0x54 * temp;
    arg0->field_0x58 = arg0->field_0x58 * temp;
    if (fabsf(arg0->field_0x48) < 4.0f) {
        arg0->field_0x60 &= -0x6A;
        arg0->field_0x44 = 0.0f;
        arg0->field_0x48 = 0.0f;
        arg0->field_0x4C = 0.0f;
        arg0->field_0x50 = 0.0f;
        arg0->field_0x54 = 0.0f;
        arg0->field_0x58 = 0.0f;
        arg0->field_0x5C = 0.0f;
    }
    return 1;
}

s32 func_15133C58(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4, s32 arg5) {
    func_15133B98(arg0, arg1, arg2, arg3, arg4, arg5);
    if (func_150ADA20() & 1) {
        func_10010F88(((u32)func_150ADA20() % 9) + 0x2DE, 0x2EE0, 0, 0, 0,
                      (s32)*(f32 *)&arg1, (s32)*(f32 *)&arg2, (s32)*(f32 *)&arg3,
                      0x1F4, 0x3E8);
    }
    return 1;
}

s32 func_15133D20(s32 arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4, s32 arg5) {
    func_15133B98(arg0, arg1, arg2, arg3, arg4, arg5);
    if (func_150ADA20() & 1) {
        func_10010F88(((u32)func_150ADA20() % 10) + 0x1B8, 0x5DC0, 0, 0, 0,
                      (s32)*(f32 *)&arg1, (s32)*(f32 *)&arg2, (s32)*(f32 *)&arg3,
                      0x1F4, 0x3E8);
    }
    return 1;
}

void func_15133DE8(InteractionTargetFields *arg0, InteractionKeyFields *arg1, u8 arg2) {
    s32 temp;

    if (arg2 == 0) {
        temp = arg1->field_0x0;
        if ((temp == arg0->field_0x7C) ||
            (arg0->field_0x80 == arg1->field_0x4)) {
            func_1516972C((struct102 *)arg0);
        }
    }
}

void func_15133E3C(s32 arg0, u8 arg1) {
    Data15133E3C sp18;

    sp18 = D_800A3860;
    func_15169260(&sp18, 2, arg0, arg1);
}

s32 func_15133EEC(s32 arg0, u16 arg1, u8 arg2, s32 arg3);

void func_15133E84(s32 arg0, void *arg1, s32 arg2) {
    func_15133EEC(arg0, *(u16 *)((u8 *)arg1 + 0x170), *(u8 *)((u8 *)arg1 + 0x172), *(s32 *)((u8 *)arg1 + 0x174));
}

void func_15133EB8(s32 arg0, void *arg1, s32 arg2) {
    func_15133EEC(arg0, *(u16 *)((u8 *)arg1 + 0x174), *(u8 *)((u8 *)arg1 + 0x176), *(s32 *)((u8 *)arg1 + 0x178));
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_15F680/func_15133EEC.s")

typedef struct {
    u8 unk0[4];
    u16 unk4;
    u8 unk6;
    u8 unk7;
    s32 unk8;
} Elem15133FD8B;

typedef u8 Entry15133FD8[8];

s32 func_15133FD8(s32 arg0, void *arg1, s32 arg2) {
    u8 i;
    Entry15133FD8 *base;
    Elem15133FD8B *e;

    base = (Entry15133FD8 *)((u8 *)arg1 + 0x170);
    for (i = 0; i < (*base)[0]; i++) {
        e = (Elem15133FD8B *)base[i];
        arg0 = func_15133EEC(arg0, e->unk4, e->unk6, e->unk8);
    }
    return arg0;
}
