#include <ultra64.h>

#include "functions.h"
#include "variables.h"


#pragma GLOBAL_ASM("asm/nonmatchings/init_1420/func_10001420.s")
// JUSTREG (verified 2026-06-18): the body below is structurally byte-perfect
// vs the target — every instruction/immediate/branch matches — but IDO -O2
// allocates v0/v1 where the target uses a1/a0. Imported into decomp-permuter.
// void func_10001420(void) {
//     s32 *p = (s32 *)&D_80043B40;
//     do {
//         *p++ = 0;
//     } while ((u32)p < (u32)&D_80043B40 + 0xFE0);
// }

void func_10001444(void) {
    u32 saveMask = __osDisableInt();
    func_100061F8(2, 31);
    func_10001420();
    func_10005BE0();
    osInvalICache(&D_1002AAD0, 0x80400000 - (u32)&D_1002AAD0);
    __osRestoreInt(saveMask);
}

void func_100014A0(void) {
    osStopThread(&D_80031AE0);
}

void func_100014C4(s32 arg0) {
    u32 saveMask = __osDisableInt();
    func_100061F8(2, 31);

    if (0) {};

    if (D_8003BE74) {
        func_10004074(D_8003BE74 | 0x80000000);
    }
    if (D_8003BE70) {
        func_10004074(D_8003BE70 | 0x80000000);
    }
    func_10005B04(arg0);
    func_10001420();
    func_10005BE0();
    __osRestoreInt(saveMask);
}

// this is a loopy mutha. contains delay slot so insert nop after .L1000183C
typedef struct {
    long quot;
    long rem;
} ldiv_t;
ldiv_t ldiv(long num, long denom);

typedef struct {
    union { long long ll; double ld; } v;
    unsigned char *s;
    int n0;
    int nz0;
    int n1;
    int nz1;
    int n2;
    int nz2;
    int prec;
    int width;
    unsigned int nchar;
    unsigned int flags;
    char qual;
} _Pft;

void *memcpy(void *, const void *, unsigned int);
extern double D_8002BF20[];
extern char D_8002BF68[];
extern char D_8002BF6C[];
extern double D_8002BF78;
s16 func_100019F0(s16 *arg0, struct05 *arg1);
void func_10001AA8(_Pft *px, unsigned char code, unsigned char *p, short nsig, short xexp);

/* _Ldtob (libultra xldtob.c). Unlike the SDK, this copy builds its 0.0/1.0 constants as
 * float locals converted to double at runtime (golden: mtc1/cvt.d.s, with 0.0 kept in a
 * double stack slot) -- IDO folds every literal spelling. The -g3 frame also holds one
 * extra pointer local, here the typed copy of arg0. */
void func_10001550(void *arg0, unsigned char code) {
    unsigned char buff[32];
    unsigned char *p;
    double ldval;
    double zero;
    float fz = 0.0f;
    float fo = 1.0f;
    _Pft *px = arg0;
    short err;
    short nsig;
    short xexp;

    p = buff;
    ldval = px->v.ld;
    zero = fz;

    if (px->prec < 0) {
        px->prec = 6;
    } else if (px->prec == 0 && (code == 'g' || code == 'G')) {
        px->prec = 1;
    }

    err = func_100019F0(&xexp, (struct05 *)px);
    if (err > 0) {
        memcpy(px->s, err == 2 ? D_8002BF68 : D_8002BF6C, px->n1 = 3);
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
                        ldval *= D_8002BF20[i];
                    }
                }
            } else if (xexp > 0) {
                double factor = fo;

                xexp &= ~3;

                for (n = xexp, i = 0; n > 0; n >>= 1, i++) {
                    if (n & 1) {
                        factor *= D_8002BF20[i];
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
                    ldval = (ldval - lo) * D_8002BF78;
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

    func_10001AA8(px, code, p, nsig, xexp);
}


s16 func_100019F0(s16 *arg0, struct05 *arg1) {
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
        *arg0 = temp_v1 - 0x3FE; // 1022
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

void func_10001AA8(_Pft *px, unsigned char code, unsigned char *p, short nsig, short xexp) {
    if (nsig <= 0) {
        p = D_8002BF70;
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
            memcpy(&px->s[px->n1], p, px->n2 = nsig);
            px->nz2 = px->prec - nsig;
        } else if (nsig < xexp) {
            memcpy(&px->s[px->n1], p, nsig);
            px->n1 += nsig;
            px->nz1 = xexp - nsig;
            if (0 < px->prec || px->flags & FLAGS_HASH) {
                px->s[px->n1] = '.', ++px->n2;
            }
            px->nz2 = px->prec;
        } else {
            memcpy(&px->s[px->n1], p, xexp);
            px->n1 += xexp;
            nsig -= xexp;
            if (0 < px->prec || px->flags & FLAGS_HASH) {
                px->s[px->n1++] = '.';
            }
            if (px->prec < nsig) {
                nsig = px->prec;
            }
            memcpy(&px->s[px->n1], p + xexp, nsig);
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
            memcpy(&px->s[px->n1], p, nsig);
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
