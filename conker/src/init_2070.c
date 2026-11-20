#include <ultra64.h>

#include "libc/stdarg.h"
#include "libc/string.h"
#include "functions.h"
#include "variables.h"

/* libultra _Pft (xstdio.h); chars are unsigned as in the original IDO build. */
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
} InitPft;

extern u8 D_8002AAF0[];
extern u8 D_8002AB14[];
void func_10002718(InitPft *px, va_list *pap, u8 code, u8 *ac);
void _Litob(InitPft *px, u8 code);

s32 func_100020D0(s32 (*pfn)(u8 *, u8 *, u32), u8 *arg, u8 *fmt, va_list args);

s32 func_10002070(s32 arg0, s32 arg1, s32 arg2) {
    return 1;
}

void func_10002088(s32 arg0, ...) {
    va_list args;

    va_start(args, arg0);
    D_80035500 = 0;
    func_100020D0((s32 (*)(u8 *, u8 *, u32))func_10002070, NULL, (u8 *)arg0, args);
}

#define ATOI(dst, src)                                  \
    for (dst = 0; *src >= '0' && *src <= '9'; ++src) {  \
        if (dst < 999)                                  \
            dst = dst * 10 + *src - '0';                \
    }
#define PUT(s, n)                                       \
    if (0 < (n)) {                                      \
        if ((arg = (u8 *)(*pfn)(arg, s, n)) != NULL)    \
            x.nchar += (n);                             \
        else                                            \
            return x.nchar;                             \
    }
#define PAD(s, n)                                       \
    if (0 < (n)) {                                      \
        int i, j = (n);                                 \
        for (; 0 < j; j -= i) {                         \
            i = 32 < (unsigned int)j ? 32 : j;          \
            PUT(s, i);                                  \
        }                                               \
    }

/* libultra _Printf (xprintf.c), the init segment's copy (twin of debugger func_16001BB4).
 * D_8002AAF0 = spaces, D_8002AB14 = zeroes (32 chars each, hence MAX_PAD 32).
 */
s32 func_100020D0(s32 (*pfn)(u8 *, u8 *, u32), u8 *arg, u8 *fmt, va_list args) {
    InitPft x;

    x.nchar = 0;
    while (1) {
        u8 *s;
        u8 c;
        u8 *t;
        static const u8 fchar[] = { ' ', '+', '-', '#', '0', '\0' };
        static const u32 fbit[] = { 1, 2, 4, 8, 16, 0 };
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
        for (x.flags = 0; (t = (u8 *)strchr((char *)fchar, *s)) != NULL; s++) {
            x.flags |= fbit[t - fchar];
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
        x.qual = strchr("hlL", *s) ? *s++ : '\0';
        if (x.qual == 'l' && *s == 'l') {
            x.qual = 'L';
            ++s;
        }
        func_10002718(&x, &args, *s, ac);
        x.width -= x.n0 + x.nz0 + x.n1 + x.nz1 + x.n2 + x.nz2;
        if (!(x.flags & 4)) {
            PAD(D_8002AAF0, x.width);
        }
        PUT(ac, x.n0);
        PAD(D_8002AB14, x.nz0);
        PUT(x.s, x.n1);
        PAD(D_8002AB14, x.nz1);
        PUT(x.s + x.n1, x.n2);
        PAD(D_8002AB14, x.nz2);
        if (x.flags & 4) {
            PAD(D_8002AAF0, x.width);
        }
        fmt = s + 1;
    }
    return 0;
}

/* libultra _Putfld (xprintf.c), the init segment's copy (twin of debugger func_160021FC). */
void func_10002718(InitPft *px, va_list *pap, u8 code, u8 *ac) {
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
        _Litob(px, code);
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
        _Litob(px, code);
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
        func_10001550(px, code);
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
        _Litob(px, 'x');
        break;

    case 's':
        px->s = va_arg(*pap, u8 *);
        strLen = strlen((char *)px->s);
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
