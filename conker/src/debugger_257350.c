#include <ultra64.h>

#include "libc/stdarg.h"
#include "libc/stdlib.h"
#include "libc/string.h"
#include "functions.h"
#include "variables.h"


typedef struct {
    union {
        long long ll;
        double d;
    } v;
    u8 *s;
    s32 n0;
    s32 nz0;
    s32 n1;
    s32 nz1;
    s32 n2;
    s32 nz2;
    s32 prec;
    s32 width;
    u32 nchar;
    u32 flags;
    u8 qual;
} DebuggerPft;

extern u8 D_16003CB8[];
extern u8 D_16003CCC[];
extern s32 func_16001BB4(s32 (*arg0)(u8 *, u8 *, u32), u8 *arg1, u8 *arg2, va_list arg3);
extern u8 D_16003C70[];
extern u8 D_16003C94[];
extern u8 D_16004800[];
extern u8 D_16004804[];
extern u32 D_1600480C[];
void func_160021FC(DebuggerPft *px, va_list *pap, u8 code, u8 *ac);
void func_1600288C(void *arg0, unsigned char code);
void func_160033A8(DebuggerPft *px, u8 code);

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
    s32 var_v1;
    u8 *var_v0;

    var_v0 = arg0;
    var_v1 = 0;
    if (*arg0 != 0) {
        do {
            var_v1 += 1;
            var_v0 += 1;
        } while (*var_v0 != 0);
    }
    return var_v1;
}

s32 func_16001B34(u8 *arg0, u8 *arg1, ...) {
    va_list args;
    s32 temp_v0;

    va_start(args, arg1);
    temp_v0 = func_16001BB4(func_16001B8C, arg0, arg1, args);
    if (temp_v0 >= 0) {
        arg0[temp_v0] = 0;
    }
    return temp_v0;
}
// s32 func_16001BB4(void *arg0, s32 arg1, void *arg2, s32 arg3) ;
// NON-MATCHING: need to work out  func_16001BB4
// s32 func_16001B34(s8 arg0[], s32 arg1, s32 arg2, s32 arg3) {
//     s32 idx = func_16001BB4(&D_16001B8C, &arg1, arg2, &arg3);
//     if (idx >= 0) {
//         arg0[idx] = 0;
//     }
//     return idx;
// }

s32 func_16001B8C(u8 *arg0, u8 *arg1, u32 arg2) {
    return func_16001AD0(arg0, arg1, arg2) + arg2;
}

#define ATOI(dst, src)                         \
    for (dst = 0; *src >= '0' && *src <= '9'; ++src) {  \
        if (dst < 999)                                  \
            dst = dst * 10 + *src - '0';                \
    }
#define PUT(s, n)                              \
    if (0 < (n)) {                                      \
        if ((arg = (u8 *)(*pfn)(arg, s, n)) != NULL)    \
            x.nchar += (n);                             \
        else                                            \
            return x.nchar;                             \
    }
#define PAD(s, n)                                      \
    if (0 < (n)) {                                              \
        int i, j = (n);                                         \
        for (; 0 < j; j -= i) {                                 \
            i = 32 < (unsigned int)j ? 32 : j;                  \
            PUT(s, i);                                 \
        }                                                       \
    }

/* libultra _Printf (xprintf.c), private debugger copy. D_16003C70 = spaces, D_16003C94 = zeroes
 * (32 chars each, hence MAX_PAD 32), D_16004800 = "hlL", D_16004804 = fchar, D_1600480C = fbit. */
s32 func_16001BB4(s32 (*pfn)(u8 *, u8 *, u32), u8 *arg, u8 *fmt, va_list args) {
    DebuggerPft x;

    x.nchar = 0;
    while (1) {
        u8 *s;
        u8 c;
        u8 *t;
        u8 ac[32];

        s = fmt;
        while ((c = *s++) > 0) {
            if (c == '%') {
                s--;
                break;
            }
        }
        PUT(fmt, s - fmt);
        if (c == 0) {
            return x.nchar;
        }
        fmt = ++s;
        for (x.flags = 0; (t = (u8 *)strchr((char *)D_16004804, *s)) != NULL; s++) {
            x.flags |= D_1600480C[t - D_16004804];
        }
        if (*s == '*') {
            x.width = va_arg(args, int);
            if (x.width < 0) {
                x.width = -x.width;
                x.flags |= 4;
            }
            s++;
        } else {
            ATOI(x.width, s);
        }
        if (*s != '.') {
            x.prec = -1;
        } else if (*++s == '*') {
            x.prec = va_arg(args, int);
            ++s;
        } else {
            ATOI(x.prec, s);
        }
        x.qual = strchr((char *)D_16004800, *s) ? *s++ : '\0';
        if (x.qual == 'l' && *s == 'l') {
            x.qual = 'L';
            ++s;
        }
        func_160021FC(&x, &args, *s, ac);
        x.width -= x.n0 + x.nz0 + x.n1 + x.nz1 + x.n2 + x.nz2;
        if (!(x.flags & 4)) {
            PAD(D_16003C70, x.width);
        }
        PUT(ac, x.n0);
        PAD(D_16003C94, x.nz0);
        PUT(x.s, x.n1);
        PAD(D_16003C94, x.nz1);
        PUT(x.s + x.n1, x.n2);
        PAD(D_16003C94, x.nz2);
        if (x.flags & 4) {
            PAD(D_16003C70, x.width);
        }
        fmt = s + 1;
    }
    return 0;
}

void func_160021FC(DebuggerPft *px, va_list *pap, u8 code, u8 *ac) {
    s32 strLen;

    px->n0 = px->nz0 = px->n1 = px->nz1 = px->n2 = px->nz2 = 0;

    switch (code) {
    case 'c':
        ac[px->n0++] = va_arg(*pap, int);
        break;

    case 'd':
    case 'i':
        if (px->qual == 'l') {
            px->v.ll = va_arg(*pap, long);
        } else if (px->qual == 'L') {
            px->v.ll = va_arg(*pap, long long);
        } else {
            px->v.ll = va_arg(*pap, int);
        }

        if (px->qual == 'h') {
            px->v.ll = (short)px->v.ll;
        }

        if (px->v.ll < 0) {
            ac[px->n0++] = '-';
        } else if (px->flags & 2) {
            ac[px->n0++] = '+';
        } else if (px->flags & 1) {
            ac[px->n0++] = ' ';
        }

        px->s = &ac[px->n0];
        func_160033A8(px, code);
        break;

    case 'x':
    case 'X':
    case 'u':
    case 'o':
        if (px->qual == 'l') {
            px->v.ll = va_arg(*pap, long);
        } else if (px->qual == 'L') {
            px->v.ll = va_arg(*pap, long long);
        } else {
            px->v.ll = va_arg(*pap, int);
        }

        if (px->qual == 'h') {
            px->v.ll = (unsigned short)px->v.ll;
        } else if (px->qual == 0) {
            px->v.ll = (unsigned int)px->v.ll;
        }

        if (px->flags & 8) {
            ac[px->n0++] = '0';
            if (code == 'x' || code == 'X') {
                ac[px->n0++] = code;
            }
        }

        px->s = &ac[px->n0];
        func_160033A8(px, code);
        break;

    case 'e':
    case 'f':
    case 'g':
    case 'E':
    case 'G':
        px->v.d = (px->qual == 'L') ? va_arg(*pap, double) : va_arg(*pap, double);

        if ((*(u16 *)&px->v.d) & 0x8000) {
            ac[px->n0++] = '-';
        } else if (px->flags & 2) {
            ac[px->n0++] = '+';
        } else if (px->flags & 1) {
            ac[px->n0++] = ' ';
        }

        px->s = &ac[px->n0];
        func_1600288C(px, code);
        break;

    case 'n':
        if (px->qual == 'h') {
            *va_arg(*pap, unsigned short *) = px->nchar;
        } else if (px->qual == 'l') {
            *va_arg(*pap, unsigned long *) = px->nchar;
        } else if (px->qual == 'L') {
            *va_arg(*pap, unsigned long long *) = px->nchar;
        } else {
            *va_arg(*pap, unsigned int *) = px->nchar;
        }
        break;

    case 'p':
        px->v.ll = (long)va_arg(*pap, void *);
        px->s = &ac[px->n0];
        func_160033A8(px, 'x');
        break;

    case 's':
        px->s = va_arg(*pap, u8 *);
        strLen = func_16001B00(px->s);
        px->n1 = strLen;
        if (px->prec >= 0 && px->prec < px->n1) {
            px->n1 = px->prec;
        }
        break;

    case '%':
        ac[px->n0++] = '%';
        break;

    default:
        ac[px->n0++] = code;
        break;
    }
}
extern double D_16004828[];
s16 func_16002D2C(s16 *arg0, struct05 *arg1);
void func_16002DE4(DebuggerPft *px, u8 code, u8 *p, s16 nsig, s16 xexp);

/* _Ldtob (libultra xldtob.c). Unlike the SDK, this copy builds its 0.0/1.0 constants as
 * float locals converted to double at runtime (golden: mtc1/cvt.d.s, with 0.0 kept in a
 * double stack slot) -- IDO folds every literal spelling. The -g3 frame also holds one
 * extra pointer local, here the typed copy of arg0. */
void func_1600288C(void *arg0, unsigned char code) {
    unsigned char buff[32];
    unsigned char *p;
    double ldval;
    double zero;
    float fz = 0.0f;
    float fo = 1.0f;
    DebuggerPft *px = arg0;
    short err;
    short nsig;
    short xexp;

    p = buff;
    ldval = px->v.d;
    zero = fz;

    if (px->prec < 0) {
        px->prec = 6;
    } else if (px->prec == 0 && (code == 'g' || code == 'G')) {
        px->prec = 1;
    }

    err = func_16002D2C(&xexp, (struct05 *)px);
    if (err > 0) {
        func_16001AD0(px->s, err == 2 ? "NaN" : "Inf", px->n1 = 3);
        return;
    } else if (err == 0) {
        nsig = 0;
        xexp = 0;
    } else {
        {
            int i;
            int n;

            if (ldval < zero) {
                ldval = -ldval;
            }

            if ((xexp = xexp * 30103 / 100000 - 4) < 0) {
                n = (3 - xexp) & ~3, xexp = -n;

                for (i = 0; n > 0; n >>= 1, i++) {
                    if (n & 1) {
                        ldval *= D_16004828[i];
                    }
                }
            } else if (xexp > 0) {
                double factor = fo;

                xexp &= ~3;

                for (n = xexp, i = 0; n > 0; n >>= 1, i++) {
                    if (n & 1) {
                        factor *= D_16004828[i];
                    }
                }

                ldval /= factor;
            }
        }
        {
            int gen = px->prec + ((code == 'f') ? 10 + xexp : 6);

            if (gen > 0x13) {
                gen = 0x13;
            }

            for (*p++ = '0'; gen > 0 && zero < ldval; p += 8) {
                int j;
                long lo = ldval;

                if ((gen -= 8) > 0) {
                    ldval = (ldval - lo) * 1e8;
                }

                for (p += 8, j = 8; lo > 0 && --j >= 0;) {
                    ldiv_t qr;
                    qr = ldiv(lo, 10);
                    *--p = qr.rem + '0', lo = qr.quot;
                }

                while (--j >= 0) {
                    *--p = '0';
                }
            }

            gen = p - &buff[1];

            for (p = &buff[1], xexp += 7; *p == '0'; p++) {
                --gen, --xexp;
            }

            nsig = px->prec + ((code == 'f') ? xexp + 1 : ((code == 'e' || code == 'E') ? 1 : 0));

            if (gen < nsig) {
                nsig = gen;
            }

            if (nsig > 0) {
                const unsigned char drop = nsig < gen && '5' <= p[nsig] ? '9' : '0';
                int n;

                for (n = nsig; p[--n] == drop;) {
                    --nsig;
                }

                if (drop == '9') {
                    ++p[n];
                }

                if (n < 0) {
                    --p, ++nsig, ++xexp;
                }
            }
        }
    }

    func_16002DE4(px, code, p, nsig, xexp);
}

s16 func_16002D2C(s16 *arg0, struct05 *arg1) {
    s16 temp_v1 = (arg1->unk0 & 0x7FF0) >> 4;

    if (temp_v1 == 0x7FF) {
        s32 ret;
        *arg0 = 0;
        if ((arg1->unk0 & 0xF) || (arg1->unk2) || (arg1->unk4) || (arg1->unk6)) {
            ret = 2;
        }
        else {
            ret = 1;
        }
        return ret;
    }

    if (temp_v1 > 0) {
        arg1->unk0 = (arg1->unk0 & 0x800F) | 0x3FF0;
        *arg0 = temp_v1 - 0x3FE;
        return -1;
    }

    if (temp_v1 < 0) {
      return 2;
    }

    *arg0 = 0;
    return 0;
}

#define FLAGS_HASH 8
#define FLAGS_ZERO 16
#define FLAGS_MINUS 4

void func_16002DE4(DebuggerPft *px, u8 code, u8 *p, s16 nsig, s16 xexp) {
    if (nsig <= 0) {
        p = "0";
        nsig = 1;
    }

    if (code == 'f' || ((code == 'g' || code == 'G') && (-4 <= xexp) && (xexp < px->prec))) {
        xexp++;
        if (code != 'f') {
            if (!(px->flags & FLAGS_HASH) && nsig < px->prec) {
                px->prec = nsig;
            }
            if ((px->prec -= xexp) < 0) {
                px->prec = 0;
            }
        }
        if (xexp <= 0) {
            px->s[px->n1++] = '0';
            if (0 < px->prec || px->flags & FLAGS_HASH) {
                px->s[px->n1++] = '.';
            }
            if (px->prec < -xexp) {
                xexp = -px->prec;
            }
            px->nz1 = -xexp;
            px->prec += xexp;
            if (px->prec < nsig) {
                nsig = px->prec;
            }
            func_16001AD0(&px->s[px->n1], p, px->n2 = nsig);
            px->nz2 = px->prec - nsig;
        } else if (nsig < xexp) {
            func_16001AD0(&px->s[px->n1], p, nsig);
            px->n1 += nsig;
            px->nz1 = xexp - nsig;
            if (0 < px->prec || px->flags & FLAGS_HASH) {
                px->s[px->n1] = '.', ++px->n2;
            }
            px->nz2 = px->prec;
        } else {
            func_16001AD0(&px->s[px->n1], p, xexp);
            px->n1 += xexp;
            nsig -= xexp;
            if (0 < px->prec || px->flags & FLAGS_HASH) {
                px->s[px->n1++] = '.';
            }
            if (px->prec < nsig) {
                nsig = px->prec;
            }
            func_16001AD0(&px->s[px->n1], p + xexp, nsig);
            px->n1 += nsig;
            px->nz1 = px->prec - nsig;
        }
    } else {
        if (code == 'g' || code == 'G') {
            if (nsig < px->prec) {
                px->prec = nsig;
            }
            if (--px->prec < 0) {
                px->prec = 0;
            }
            code = code == 'g' ? 'e' : 'E';
        }
        px->s[px->n1++] = *p++;
        if (0 < px->prec || px->flags & FLAGS_HASH) {
            px->s[px->n1++] = '.';
        }
        if (0 < px->prec) {
            if (px->prec < --nsig) {
                nsig = px->prec;
            }
            func_16001AD0(&px->s[px->n1], p, nsig);
            px->n1 += nsig;
            px->nz1 = px->prec - nsig;
        }
        p = &px->s[px->n1];
        *p++ = code;
        if (0 <= xexp) {
            *p++ = '+';
        } else {
            *p++ = '-';
            xexp = -xexp;
        }
        if (100 <= xexp) {
            if (1000 <= xexp) {
                *p++ = xexp / 1000 + '0', xexp %= 1000;
            }
            *p++ = xexp / 100 + '0', xexp %= 100;
        }
        *p++ = xexp / 10 + '0', xexp %= 10;
        *p++ = xexp + '0';
        px->n2 = p - &px->s[px->n1];
    }
    if ((px->flags & (FLAGS_ZERO | FLAGS_MINUS)) == FLAGS_ZERO) {
        int n = px->n0 + px->n1 + px->nz1 + px->n2 + px->nz2;

        if (n < px->width) {
            px->nz0 = px->width - n;
        }
    }
}

void func_160033A8(DebuggerPft *px, u8 code) {
    char buff[0x18];
    u8 *digs;
    s32 base;
    s32 i;
    unsigned long long ullval;

    digs = (code == 'X') ? D_16003CCC : D_16003CB8;

    base = (code == 'o') ? 8 : ((code != 'x' && code != 'X') ? 10 : 16);
    i = 0x18;
    ullval = px->v.ll;

    if ((code == 'd' || code == 'i') && px->v.ll < 0) {
        ullval = -ullval;
    }

    if (ullval != 0 || px->prec != 0) {
        buff[--i] = digs[ullval % base];
    }

    px->v.ll = ullval / base;

    while (px->v.ll > 0 && i > 0) {
        lldiv_t qr;

        qr = lldiv(px->v.ll, base);
        px->v.ll = qr.quot;
        buff[--i] = digs[qr.rem];
    }

    px->n1 = 0x18 - i;

    func_16001AD0(px->s, buff + i, px->n1);

    if (px->n1 < px->prec) {
        px->nz0 = px->prec - px->n1;
    }

    if (px->prec < 0 && (px->flags & 0x14) == 0x10) {
        if ((i = px->width - px->n0 - px->nz0 - px->n1) > 0) {
            px->nz0 += i;
        }
    }
}
