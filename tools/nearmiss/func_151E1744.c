extern s8 D_800AB691[];
extern s8 D_800AB710[];
struct ColRGB {
    u8 r;
    u8 g;
    u8 b;
};
extern struct ColRGB D_800AB62C[];
extern char D_800AB864[];
extern char D_800AB868[];
extern char D_800AB86C[];
extern char D_800AB870[];
extern char D_800AB874[];
extern char D_800AB878[];
extern char D_800AB87C[];
extern char D_800AB880[];
extern char D_800AB884[];
extern char D_800AB88C[];
extern char D_800AB890[];
extern char D_800AB894[];
extern char D_800AB898[];
extern s8 D_800E0BB0;
extern s8 D_800E0BC8[];
extern s8 D_8008FE40;
extern s8 D_8008FE44[];
extern s8 D_8008FDA0;
extern s8 D_8008FDC4;
extern s32 D_8008FF34;
void func_15042E3C(char *, s32);
s32 func_151E24F0(s32 *);
void func_151E4314(void);

void func_151E1744(void) {
    s32 alpha;
    s32 i;
    s32 sel;
    s8 *row;
    s32 spA8[4];
    s32 res;
    s8 spA0[4];
    s8 min;
    s8 max;
    s8 init;
    s8 u7;
    s8 lim;
    s8 cap;
    s16 x;
    s16 y;
    s16 step;
    s16 sp8C[4];
    s16 sp84[4];
    s8 sp80[4];
    s8 sp7C[4];
    s8 sp78[4];
    s32 sound;
    s32 val;
    s16 n;

    sound = 0;
    *(s32 *)sp80 = D_8008FF34;

    if (D_800E0A96 != -1) {
        D_8008FDD4->unk20 &= ~0x20;
        alpha = D_800E0A95 - (D_800BE9E4 << 5);
        if (alpha <= 0) {
            D_800E0A95 = 0;
            D_8008FDD4->unk3F = D_800E0A96;
            D_800E0A96 = -1;
            return;
        }
        D_800E0A95 = alpha;
    } else {
        alpha = D_800E0A95 + (D_800BE9E4 << 5);
        if (alpha >= 0x100) {
            alpha = 0xFF;
        }
        D_800E0A95 = alpha;
    }

    func_1504332C(0xFF, 0xFF, 0xFF, alpha);

    row = &D_800AB710[D_800AB691[D_8008FDD4->pad42 * 10] * 12];
    D_800E0BB0 = row[0];
    u7 = row[7];
    D_800E0BC8[0] = row[8];
    D_800E0BC8[1] = row[9];
    D_800E0BC8[2] = row[10];
    D_800E0BC8[3] = row[11];
    if (D_8008FE40 < 3) {
        min = row[1];
        max = row[2];
        init = row[3];
    } else {
        min = row[4];
        max = row[5];
        init = row[6];
    }

    for (i = 0; i < 4; i++) {
        sp7C[i] = init;
        if (u7 != 0 && i >= 1) {
            sp7C[i] = u7;
        }
    }

    for (i = 0; i < D_800E0BB0; i++) {
        spA0[i] = 0;
        sp84[i] = 0x6E;
    }

    for (i = 0; i < D_8008FE40; i++) {
        spA0[D_800E0C00[i]]++;
    }

    for (i = D_8008FE40; i < 16; i++) {
        D_8008FE44[i] = -1;
    }

    for (i = 0; i < D_8008FE40; i++) {
        if (D_8008FE44[i] >= 0) {
            sel = D_800E0C00[i];
            if (D_8008FDD4->unk22[D_8008FE44[i]] & 0xF) {
                sound = 0x4FF;
            }
            if (D_8008FDD4->unk22[D_8008FE44[i]] & 8) {
                D_800E0C00[i]++;
            }
            if (D_8008FDD4->unk22[D_8008FE44[i]] & 4) {
                D_800E0C00[i]--;
            }
            if (D_8008FDD4->unk22[D_8008FE44[i]] & 2) {
                D_8008FDA0++;
            }
            if (D_8008FDD4->unk22[D_8008FE44[i]] & 1) {
                D_8008FDA0--;
            }
            if (D_8008FDA0 < 0) {
                D_8008FDA0 = 0;
                sound = 0;
            }
            D_800E0C00[i] &= D_800E0BB0 - 1;
            if (spA0[D_800E0C00[i]] >= sp7C[D_800E0C00[i]]) {
                D_800E0C00[i] = sel;
            }
            spA0[D_800E0C00[i]]++;
            spA0[sel]--;
        }
    }

    D_800E0BB1 = 1;
    for (i = 0; i < D_800E0BB0; i++) {
        if (D_800E0BB1 < spA0[i]) {
            D_800E0BB1 = spA0[i];
        }
    }
    D_800E0BB1 += D_8008FDA0;
    while (D_800E0BB1 * D_800E0BB0 < min) {
        D_800E0BB1++;
        D_8008FDA0++;
    }
    while (D_800E0BB1 * D_800E0BB0 > max) {
        D_800E0BB1--;
        D_8008FDA0--;
        if (D_8008FDA0 < 0) {
            D_8008FDA0 = 0;
        }
    }

    if (u7 != 0 && D_800E0BB1 == 1) {
        u7 = 1;
    }
    for (i = 0; i < 4; i++) {
        val = D_800E0BB1;
        if ((i == 1) && (u7 != 0)) {
            val = u7;
        }
        sp78[i] = val;
    }

    if (D_800E0BB0 == 2) {
        if (D_8008FDD4->unk20 & 0x40) {
            D_8008FDC4++;
        } else if (D_8008FDD4->unk20 & 0x80) {
            D_8008FDC4--;
        }
        if (D_8008FE40 >= 3) {
            D_8008FDC4 = 0;
        }
        lim = D_800E0BB1;
        if (D_8008FDC4 < -lim) {
            D_8008FDC4 = -lim;
        } else if (lim < D_8008FDC4) {
            D_8008FDC4 = lim;
        } else if (D_8008FDD4->unk20 & 0xC0) {
            sound = 0x4FF;
        }
        sp78[0] += D_8008FDC4;
        sp78[1] -= D_8008FDC4;
        for (i = 0; i < 2; i++) {
            cap = 8;
            if ((i == 1) && (u7 != 0)) {
                cap = u7;
            }
            if (sp78[i] <= 0) {
                sp78[i] = 1;
            }
            if (sp78[i] > cap) {
                sp78[i] = cap;
            }
        }
    }

    step = 296 / D_800E0BB0;
    x = step >> 1;
    n = D_8008FE40;
    for (i = 0; i < D_800E0BB0; i++) {
        sp8C[i] = x;
        x += step;
        while (sp78[i] > spA0[i]) {
            D_8008FE44[n] = -2;
            D_800E0C00[n] = i;
            spA0[i]++;
            n++;
        }
    }

    if (alpha == 0xFF) {
        if (D_8008FDD4->unk20 & 0x10) {
            D_800E0B94 = 7;
            D_800E0A88 = func_151E4314;
            D_8008FD74 = 8;
            sound = 0x500;
        } else if (D_8008FDD4->unk20 & 0x20) {
            D_800E0A96 = 4;
        }
    }

    D_8008FDD4->unk20 &= ~0x20;
    func_1504332C(0xFF, 0xFF, 0, alpha);
    func_150432FC(0x94, ((D_800E0BB0 == 4) << 5) + 0x78);
    func_15042E3C(D_800AB864, 0x1A);

    for (i = 0; i < D_800E0BB0; i++) {
        x = sp8C[i];
        func_1504332C(D_800AB62C[D_800E0BC8[i]].r, D_800AB62C[D_800E0BC8[i]].g,
                      D_800AB62C[D_800E0BC8[i]].b, alpha);
        func_150432FC(x, 0x50);
        if (D_800E0BC8[i] == 4) {
            func_15042E3C(D_800AB868, 9);
        } else if (D_800E0BC8[i] == 5) {
            func_15042E3C(D_800AB86C, 8);
        } else if (D_800E0BC8[i] == 7) {
            func_15042E3C(D_800AB870, 0xA);
        } else if (D_800E0BC8[i] == 8) {
            func_15042E3C(D_800AB874, 0xB);
        } else if (D_800E0BC8[i] == 9) {
            func_15042E3C(D_800AB878, 0x34);
        } else {
            func_15042E3C(D_800AB87C, D_800E0BC8[i] + ((D_800E0BC8[i] < 4) ? 0x59 : 0x4C));
        }
    }

    res = func_151E24F0(spA8);
    func_1504332C(0xFF, 0xFF, 0xFF, alpha);
    for (i = 0; i < n; i++) {
        sel = D_800E0C00[i];
        if (n == D_800E0BB0) {
            sp80[sel] = 0;
        }
        x = sp80[sel] + sp8C[sel];
        y = sp84[sel];
        sp80[sel] = -sp80[sel];
        if (sp80[sel] < 0) {
            sp84[sel] += 0x18;
        }
        func_150432FC(x, y);
        if (D_8008FE44[i] >= 0) {
            func_15042E3C(D_800AB880, D_8008FE44[i] + 1);
            if (res != 0) {
                func_15042E3C(D_800AB884, spA8[i] + 1);
            }
        } else {
            func_15042E3C(D_800AB88C, 5);
        }
    }

    if (sound != 0) {
        func_10010F30(sound, (sound == 0x4FF) ? 0x4650 : 0x7D00, 0x40, 0, 0);
    }

    if (D_800E0BB0 == 2) {
        func_15042D94(0x94, 0xB4, 0x81, D_800AB890, 0x3A);
        func_15042D94(0x7B, 0xB4, 0x81, D_800AB894, 0x3B);
        func_15042D94(0xAD, 0xB4, 0x81, D_800AB898, 0x3C);
    }
}
