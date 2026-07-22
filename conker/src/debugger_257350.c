#include <ultra64.h>
#include <libc/stdarg.h>

#include "functions.h"
#include "variables.h"

s32 func_16001B8C(u8 *arg0, u8 *arg1, u32 arg2);
s32 func_16001BB4(s32 (*arg0)(u8 *, u8 *, u32), u8 *arg1, u8 *arg2, va_list arg3);

typedef struct {
    /* 0x00 */ long long val;
    /* 0x08 */ u8 *buf;
    /* 0x0C */ s32 f0C;
    /* 0x10 */ s32 f10;
    /* 0x14 */ s32 len;
    /* 0x18 */ s32 f18;
    /* 0x1C */ s32 f1C;
    /* 0x20 */ s32 f20;
    /* 0x24 */ s32 prec;
    /* 0x28 */ s32 f28;
    /* 0x2C */ s32 f2C;
    /* 0x30 */ s32 flags;
} Pft;

typedef struct {
    long long quot;
    long long rem;
} lldiv_t257350;

extern lldiv_t257350 lldiv(long long, long long);
extern u8 D_16003CB8[];
extern u8 D_16003CCC[];


// whats wrong with bcopy?
u8* func_16001AD0(u8 *arg0, u8 *arg1, u32 arg2) {
    u8 *tmp0 = arg0;
    u8 *tmp1 = arg1;

    while (arg2 > 0) {
        *tmp0++ = *tmp1++;
        arg2 -= 1;
    }

    return arg0;
}

s32 func_16001B00(u8 *arg0) {
    u8 *p = arg0;
    s32 len = 0;

    while (*p != 0) {
        len++;
        p++;
    }

    return len;
}

s32 func_16001B34(u8 *arg0, u8 *arg1, ...) {
    va_list ap;
    s32 ret;

    va_start(ap, arg1);
    ret = func_16001BB4(func_16001B8C, arg0, arg1, ap);
    if (ret >= 0) {
        arg0[ret] = 0;
    }
    va_end(ap);
    return ret;
}

s32 func_16001B8C(u8 *arg0, u8 *arg1, u32 arg2) {
    return func_16001AD0(arg0, arg1, arg2) + arg2;
}

#pragma GLOBAL_ASM("asm/nonmatchings/debugger_257350/func_16001BB4.s")
// uses jump table
#pragma GLOBAL_ASM("asm/nonmatchings/debugger_257350/func_160021FC.s")
// contains delay slot
#pragma GLOBAL_ASM("asm/nonmatchings/debugger_257350/func_1600288C.s")

s16 func_16002D2C(s16 *pex, u16 *ps) {
    s16 xchar = (ps[0] & 0x7FF0) >> 4;

    if (xchar == 0x7FF) {
        *pex = 0;
        return ((ps[0] & 0xF) != 0 || ps[1] != 0 || ps[2] != 0 || ps[3] != 0) ? 2 : 1;
    } else if (0 < xchar) {
        ps[0] = (ps[0] & 0x800F) | 0x3FF0;
        *pex = xchar - 0x3FE;
        return -1;
    } else if (xchar < 0) {
        return 2;
    } else {
        *pex = 0;
        return 0;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/debugger_257350/func_16002DE4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/debugger_257350/func_160033A8.s")
// NON-MATCHING: best 4874. This integer->string converter is ALGORITHMICALLY EXACT:
// every target instruction is reproduced in opcode/immediate/offset order (frame size 0x90
// matches). The entire remaining score is a pure saved-register rotation among three values:
// target uses {s0=i, s1=p, s2=&buf[0]}, this C yields {s0=&buf[0], s1=i, s2=p} (digits=s3 in
// both). IDO's coloring ranks the buffer-base temp above the loop counter here; declaration
// reorders and an explicit buffer pointer did not steer the priority (4765->4874->5115).
// PERMUTER CANDIDATE (saved-register assignment only).
//
// void func_160033A8(Pft *p, u8 c) {
//     int i;
//     u8 *digits;
//     int base;
//     unsigned long long a;
//     long long b;
//     u8 buf[24];
//
//     if (c == 'X') {
//         digits = D_16003CCC;
//     } else {
//         digits = D_16003CB8;
//     }
//
//     i = 24;
//     if (c == 'o') {
//         base = 8;
//     } else if (c == 'x' || c == 'X') {
//         base = 16;
//     } else {
//         base = 10;
//     }
//
//     a = p->val;
//     b = p->val;
//     if (c == 'd' || c == 'i') {
//         if (b < 0) {
//             a = -a;
//         }
//     }
//
//     if (a != 0 || p->prec != 0) {
//         i = 23;
//         buf[23] = digits[a % base];
//     }
//     p->val = a / base;
//
//     if ((long long)p->val > 0 && i > 0) {
//         b = p->val;
//         do {
//             lldiv_t257350 r = lldiv(b, base);
//             p->val = r.quot;
//             buf[--i] = digits[r.rem];
//             b = p->val;
//         } while (b > 0 && i > 0);
//     }
//
//     p->len = 24 - i;
//     func_16001AD0(p->buf, &buf[i], p->len);
//
//     if (p->len < p->prec) {
//         p->f10 = p->prec - p->len;
//     }
//     if (p->prec < 0) {
//         if ((p->flags & 0x14) == 0x10) {
//             i = p->f28 - p->f0C - p->f10 - p->len;
//             if (i > 0) {
//                 p->f10 = p->f10 + i;
//             }
//         }
//     }
// }
