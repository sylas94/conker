#include <ultra64.h>

#include "functions.h"
#include "variables.h"

s32 func_1600160C();

typedef struct {
    s32 unk0;
} func_160006CC_sp3C;

extern u8 D_160037F0;
extern func_160006CC_sp3C D_16003B48;

void func_160006CC(struct118 *arg0);

void func_16000000(void) {
    func_160012B0(278, &D_160046AC);
}

s32 func_16000028(void) {
    if (D_16003890 & 0xC000) {
        D_16003AF4 = 1;
        return 3;
    }
    return 0;
}

void func_16000058(void) {
    s32 i;
    s32 phi_s2;

    func_16001338(255, 255, 255);
    func_160012B0(44, &D_160046D0); // "MAIN MENU"
    phi_s2 = 108;
    for(i = 0; i < 2; i++) {
        if (D_16003B1C == i) {
            func_16001338(255, 0, 0);     // red
        } else {
            func_16001338(255, 255, 255); // white
        }
        func_160012B0(phi_s2, D_16003B20[i]);
        phi_s2 += 32;
    }
    if (D_16003B1C == 2) {
        func_16001338(255, 0, 0);     // red
    } else {
        func_16001338(255, 255, 255); // white
    }
    if (D_16003AF0 != 0) {
        if ((D_1600389C->unk120 == 32) && (D_160038A4 == 0)) {
            func_160012B0(phi_s2, &D_160046DC);
        } else if (D_16003AF0 != 0) {
            func_160012B0(phi_s2, &D_160046E8);
        }
    } else {
        func_160012B0(phi_s2, &D_160046F4); // "RETRY CODE"
    }
    func_16001338(255, 255, 255);
    func_160012B0(611, &D_16004700); // "Version"
    func_16001044(619, 1, 163);
    func_160012B0(643, &D_16004708); // "Built"
    func_160012B0(651, &D_16004710); // "Dec 19 2000"
    func_160012B0(663, &D_1600471C); // "09:57:42"
}

s32 func_16000224(void) {
    s32 res = 0;

    if (D_16003890 & 0x40000) { // D_JPAD is 0x0400
        D_16003B1C -= 1;
        res = 1;
    }
    if (D_16003890 & 0x80000) { // U_JPAD is 0x0800
        D_16003B1C += 1;
        res = 1;
    }
    if (D_16003B1C >= 3) {
        D_16003B1C = 0;
    }
    if (D_16003B1C < 0) {
        D_16003B1C = 2;
    }
    if (D_16003890 & A_BUTTON) {
        switch(D_16003B1C) {
            case 0:
                res = 3;
                D_16003AF4 = 2;
                break;
            case 1:
                res = 3;
                D_16003AF4 = 3;
                break;
            case 2:
                res = 4;
                break;
        }
    }
    return res;
}

void func_16000304(void) {
}

void func_1600030C(void) {
}

void func_16000314(void) {
    switch(D_16003B28) {
        case 0:
            func_16000424(D_1600389C);
            func_160006CC(D_1600389C);
            break;
        case 1:
        case 2:
            func_16000590(D_1600389C);
            break;
    }
}

s32 func_16000384(void) {
    s32 res = 0;

    if (D_16003890 & (R_CBUTTONS | D_CBUTTONS)) {
        D_16003B28 += 1;
        if (D_16003B28 >= 3) {
            D_16003B28 = 0;
        }
        return 3;
    }
    if (D_16003890 & (L_CBUTTONS | U_CBUTTONS)) {
        D_16003B28 -= 1;
        if (D_16003B28 < 0) {
            D_16003B28 = 2;
        }
        return 3;
    }
    if (D_16003890 & B_BUTTON) {
        D_16003AF4 = 1;
        res = 3;
    }
    return res;
}

void func_16000424(struct118 *arg0) {
    // TODO is this a RGB struct?
    u32 tmp0;
    u32 tmp1;
    s32 pad;

    func_16001338(255, 255, 255);
    func_160012B0(35, &D_16004728);     // "Pc"
    func_16001044(43, 0, arg0->unk11C);
    func_160012B0(67, &D_1600472C);     // "Cause"
    func_16001044(75, 0, arg0->unk120);
    func_16001338(128, 128, 255);
    tmp0 = arg0->unk120;
    tmp1 = (tmp0 >> 2) & 0xF;

    func_160012B0(107, D_16003848[tmp1]);
    if (tmp1 == 11) {
        func_16001044(111, 1, (tmp0 >> 28) & 3);
    }
    func_16001338(255, 255, 255);
    func_160012B0(131, &D_16004734);      // "Sr"
    func_16001044(139, 0, arg0->unk118);
    func_160012B0(163, &D_16004738);      // "Badvadr"
    func_16001044(171, 0, arg0->unk124);
    func_160012B0(195, &D_16004740);      // "Thread"
    func_16001044(203, 1, arg0->unk14);
    if (D_160038A4 != 0) {
        func_160012B0(52, &D_16004748);   // "Lockup_Now"
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/debugger/debugger/func_16000590.s")

void func_160006CC(struct118 *arg0) {
    func_160006CC_sp3C sp3C;
    u8 *var_s3;
    u8 *var_s1;
    s32 temp_s0;
    u8 var_v0;
    u8 temp_v0;

    var_s3 = (u8 *)&sp3C;
    temp_s0 = 0x123;
    sp3C = D_16003B48;
    var_s1 = &D_160037F0;
    func_16001338(0xC0, 0xC0, 0xFF);
    var_v0 = *(volatile u8 *)&D_160037F0;

    do {
        var_s3[0] = var_v0;
        var_s3[1] = var_s1[1];
        func_160012B0(temp_s0, var_s3);
        temp_s0 += 3;
        temp_v0 = var_s1[2];
        func_16001044(temp_s0, 0, ((s32 *)arg0)[temp_v0 + 1]);
        var_v0 = var_s1[3];
        temp_s0 += 0xD;
        var_s1 += 3;
    } while (var_v0 != 0);
}
void func_160012B0(s32 arg0, u8 *arg1);
void func_16001338(u8 arg0, u8 arg1, u8 arg2);
extern s32 D_8002D4B0;
extern s32 *D_8002D8B0;
extern s32 D_16003B4C;
extern struct118 *D_1600389C;
extern u8 D_160047B0[];
extern u8 D_160047BC[];
extern u8 D_160047C0[];
void func_1600078C(void)
{
  s32 temp_s0;
  s32 temp_s0_2;
  s32 y;
  s32 i;
  u32 *addr;
  u32 word;
  u32 dataStart;
  u32 prefix;
  temp_s0 = ((s32 *) D_1600389C)[0x3D];
  func_16001338(0, 255, 0);
  func_160012B0(0xB, D_160047B0);
  addr = (u32 *) (temp_s0 + (D_16003B4C * 4));
  if ((((((((u32) addr) & 3) & 0xFFFFu) & 0xFFFFu) == 0) && (((u32) addr) >= 0x80000000U)) && (((u32) addr) < 0x80800001U))
  {
    dataStart = (u32) (&D_8002D4B0);
    if (D_16003B4C == 0)
    {
      func_16001338(255, 0, 0);
    }
    else
      if ((((u32) addr) >= dataStart) && (((u32) addr) < (dataStart + 0x400)))
    {
      func_16001338(128, 128, 255);
    }
    else
      if ((((u32) addr) >= ((u32) (&D_8002D8B0))) && (((u32) addr) < (((u32) (&D_8002D8B0)) + 0x4000)))
    {
      func_16001338(255, 128, 128);
    }
    else
    {
      func_16001338(255, 255, 255);
    }
    y = 0x61;
    i = 0;
    do
    {
      func_16001044(y, 0, addr);
      func_160012B0(y + 8, D_160047BC);
      word = *addr;
      prefix = (word >> 24) & 0xFF;
      if (prefix == 0x80)
      {
        func_16001338(128, 128, 255);
      }
      else
        if (prefix == 0x15)
      {
        func_16001338(255, 0, 0);
      }
      else
        if (prefix == 0x16)
      {
        func_16001338(128, 255, 128);
      }
      else
        if (prefix == 0x10)
      {
        func_16001338(255, 0, 0);
      }
      else
      {
        func_16001338(255, 255, 255);
      }
      func_16001044(y + 0xC, 0, word);
      temp_s0_2 = y + 0x16;
      func_160012B0(temp_s0_2, D_160047C0);
      func_16001338(255, 255, 255);
      func_16001044(temp_s0_2, 1, word);
      if ((((u32) addr) >= dataStart) && (((u32) addr) < (dataStart + 0x400)))
      {
        func_16001338(128, 128, 255);
      }
      else
        if ((((u32) addr) >= ((u32) (&D_8002D8B0))) && (((u32) addr) < (((u32) (&D_8002D8B0)) + 0x4000)))
      {
        func_16001338(255, 128, 128);
      }
      else
      {
        func_16001338(255, 255, 255);
      }
      i += 1;
      y += 0x20;
      addr += 1;
    }
    while (i != 0x16);
  }
}

void func_160012B0(s32 arg0, u8 *arg1);
void func_16001338(u8 arg0, u8 arg1, u8 arg2);

// NON-MATCHING: close but still some stuff to figure out
// void func_1600078C(void) {
//     s32 temp_s0;
//     u8 range_prefix;
//     u32 temp_s2;
//     s32 temp_s5;
//     s32 phi_s1;
//     u32 *phi_s2;
//     u32 phi_s5;
//     s32 i;
//
//     temp_s0 = D_1600389C->unkF4;
//     func_16001338(0, 255, 0); // green
//     func_160012B0(11, &D_160047B0);
//     temp_s2 = (D_16003B4C * 4) + temp_s0;
//     if (((temp_s2 & 3) == 0) && (temp_s2 >= 0x80000000U) && (temp_s2 < 0x80800001U)) {
//         if (D_16003B4C == 0) {
//             func_16001338(255, 0, 0); // red
//             phi_s5 = &D_8002D4B0;
//         } else {
//             temp_s5 = &D_8002D4B0 - 0x2B50; // 11088 ?
//             if ((temp_s2 >= temp_s5) && (temp_s2 < (temp_s5 + 0x400))) {
//                 func_16001338(128, 128, 255); // purple
//                 phi_s5 = temp_s5;
//             } else if ((temp_s2 >= (u32) &D_8002D8B0) && (temp_s2 < ((u32)&D_8002D8B0 + 0x4000))) {
//                 func_16001338(255, 128, 128); // light red
//                 phi_s5 = temp_s5;
//             } else {
//                 func_16001338(255, 255, 255);
//                 phi_s5 = temp_s5;
//             }
//         }
//         phi_s1 = 97; // "a"
//         phi_s2 = temp_s2;
//         for (i = 0; i < 22; i++) {
//             func_16001044(phi_s1, 0, phi_s2);
//             func_160012B0(phi_s1 + 8, &D_160047BC);
//             range_prefix = (*phi_s2 >> 24);
//             if (range_prefix == 0x80) {                   // 0x80000000
//                 func_16001338(128, 128, 255);
//             } else if (range_prefix == 0x15) {            // 0x15000000
//                 func_16001338(255, 0, 0);
//             } else if (range_prefix == 0x16) {            // 0x16000000
//                 func_16001338(128, 255, 128);
//             } else if (range_prefix == 0x10) {            // 0x10000000
//                 func_16001338(255, 0, 0);
//             } else {
//                 func_16001338(255, 255, 255);
//             }
//             func_16001044(phi_s1 + 0xC, 0, *phi_s2);
//             func_160012B0(phi_s1 + 0x16, &D_160047C0);
//             func_16001338(255, 255, 255);
//             func_16001044(phi_s1 + 0x16, 1, *phi_s2);
//             if (((u32) phi_s2 >= phi_s5) && ((u32) phi_s2 < (phi_s5 + 0x400))) {
//                 func_16001338(128, 128, 0xFF);
//             } else if (((u32) phi_s2 >= (u32) &D_8002D8B0) && ((u32) phi_s2 < ((u32)&D_8002D8B0 + 0x4000))) {
//                 func_16001338(255, 128, 128);
//             } else {
//                 func_16001338(255, 255, 255);
//             }
//             phi_s1 += 0x20;
//             phi_s2 += 4;
//         }
//     }
// }

s32 func_16000A5C(void) {
    s32 res = 0;

    if ((D_160036F3 >= 41) || (D_16003890 & U_CBUTTONS)) {
        D_16003B4C -= 1;
        if (D_16003B4C < 0) {
            D_16003B4C = 0;
        } else {
            res = 3;
        }
    } else if ((D_160036F3 < -40) || (D_16003890 & D_CBUTTONS)) {
        D_16003B4C += 1;
        if (D_16003B4C >= 201) {
            D_16003B4C = 200;
        }
        res = 3;
    }
    if ((D_16003890 & B_BUTTON)) {
        D_16003AF4 = 1;
        res = 3;
    }
    return res;
}

// called from func_10007DAC
#pragma GLOBAL_ASM("asm/nonmatchings/debugger/debugger/func_16000B14.s")
#pragma GLOBAL_ASM("asm/nonmatchings/debugger/debugger/func_16000F8C.s")
// NON-MATCHING: lots to figure out
// void func_16000F8C(s32 arg0, f32 arg1) {
//     struct165 tmp;
//     s32 temp_v1;
//     u32 temp_t9;
//
//     if ((arg0 >= (D_160038A0 << 5)) && (arg0 < 833)) {
//         tmp.unk18 = arg1;
//         temp_v1 = *(s32*)&tmp.unk18;
//         temp_t9 = (u32) (temp_v1 & 0x7F800000) >> 0x17;
//         if ((temp_t9 == 0) || (temp_t9 >= 0x255U)) {
//             if ((temp_v1 * 2) != 0) {
//                 func_160012B0(arg1, &D_160047D0); // arg0,
//                 return;
//             }
//         }
//         func_16001B34(&arg0, &tmp.unk0, &D_160047D4, &D_160047DC, &D_160047E0); // , (f64) arg1
//         func_160012B0(arg0, &tmp.unk0);
//     }
// }

#pragma GLOBAL_ASM("asm/nonmatchings/debugger/debugger/func_16001044.s")

void func_160012B0(s32 arg0, u8 *arg1) {
    if (arg1 && (arg0 >= (D_160038A0 << 5)) && (arg0 < 833)) {
        s32 fb = func_1600160C();
        while (*arg1 != 0) {
            fb = func_160014F0(fb, *arg1 & 0xFF);
            *arg1++;
        }
    }
}
// convert rgb to rgba16
void func_16001338(u8 arg0, u8 arg1, u8 arg2) {
    D_1600388C = ((arg0 & 0xF8) << 8) | ((arg1 & 0xF8) << 3) | ((arg2 & 0xF8) >> 2) | 1;
}

extern u16 D_1600388C;
extern s32 D_160038A8;
void func_16001390(s16 arg0, s16 arg1, register s16 arg2, s16 arg3)
{
  s32 count;
  u16 *ptr;
  if (arg2 < arg0)
  {
    return;
  }
  if (arg3 < arg1)
  {
    return;
  }
  if (arg0 < 0)
  {
    return;
  }
  if (arg1 < 0)
  {
    return;
  }
  arg2++;
  arg3++;
  ptr = (u16 *) func_1600160C(0);
  ptr += arg0 + (arg1 * D_160038A8);
  arg2 -= arg0;
  arg3 -= arg1;
  if (arg3 > 0)
  {
    do
    {
      count = arg2;
      if (arg2 > 0)
      {
        do
        {
          *(ptr++) = D_1600388C;
          count--;
        }
        while (count != 0);
      }
      arg3--;
      ptr += D_160038A8 - arg2;
    }
    while (arg3 > 0);
  }
}

#pragma GLOBAL_ASM("asm/nonmatchings/debugger/debugger/func_160014F0.s")

// splat into framebuffer
s32 func_1600160C(s32 arg0) {
    s32 row;
    s32 width;
    s32 tmp;
    s32 w2;

    tmp = arg0 & 0xFFE0;
    row = tmp;
    width = D_160038A8;
    if (width != 0x124) {
        row = (tmp >> 2) + tmp;
    }
    w2 = width * 2;
    row = (row >> 2) * w2;
    row += (arg0 & 0x1F) << 4;
    row += width * 4;
    row += 0x10;
    return D_8002AAE8[D_16003888] + row;
}

// contains delay slot
void func_16001678(void) {
    u32 *ptr;
    u32 *end;
    s32 height;
    s32 width;

    ptr = (u32 *) D_8002AAE8[D_16003888];
    height = D_160038A8;
    if (height == 0x124) {
        width = 0xD7;
    } else {
        width = 0x108;
    }

    end = ptr + ((height >> 1) * width);
    while (ptr < end) {
        ptr += 4;
        ptr[-4] = 0x10001;
        ptr[-3] = 0x10001;
        ptr[-2] = 0x10001;
        ptr[-1] = 0x10001;
    }
}

s32 func_160016F4(s32 arg0) {
    return arg0;
}
