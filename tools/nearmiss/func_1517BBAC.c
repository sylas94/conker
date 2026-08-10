/* ---------------- func_1517BBAC ---------------- */

typedef struct {
    /* 0x00 */ s16 x;
    /* 0x02 */ s16 y;
    /* 0x04 */ s16 z;
    /* 0x06 */ u8  kind;
    /* 0x07 */ u8  swayIdx;
    /* 0x08 */ u8  unk8;
    /* 0x09 */ u8  unk9;
    /* 0x0A */ u8  beh;
    /* 0x0B */ u8  state;
    /* 0x0C */ s8  halfW;
    /* 0x0D */ s8  height;
} ScRec;

typedef struct {
    /* 0x00 */ s32 rom;
    /* 0x04 */ u32 size;
    /* 0x08 */ s32 buf;
    /* 0x0C */ u8  loaded;
} ScAsset;

typedef struct {
    /* 0x00 */ s16 ob[3];
    /* 0x06 */ u16 flag;
    /* 0x08 */ s16 tc[2];
    /* 0x0C */ u8  cn[4];
} ScVtx;

typedef struct {
    /* 0x00 */ u8  unk0;
    /* 0x01 */ u8  unk1;
    /* 0x02 */ u16 unk2;
    /* 0x04 */ u8  unk4[6];
} ScTex;

typedef s32 (*ScHookFn)(ScRec *, ScVtx *, s32 *, u8 *);

typedef struct {
    /* 0x00 */ ScHookFn fn;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
} ScHook;

extern ScRec  *D_800DDD18;
extern s32     D_8008CEB4;
extern u32     D_800DDC40[15];
extern s16     D_800DDB80[15][2];
extern u8      D_800DDBC0[16];
extern u8      D_800DDBD0[16];
extern u8      D_800DDBE0[16];
extern u8      D_800DDBF0[16];
extern u8      D_800DDC10[16];
extern u8      D_800DDC80[16];
extern s16     D_800DDC90[60];
extern ScHook  D_8008CEBC[];
extern s16     D_8008CF00[];
extern ScTex   D_80095CE0[];
extern u16     D_80095CE2[];
extern f32     D_800A7240;
extern f32     D_800A7244;
extern s16     D_800DD472;
extern s16     D_800DD474;
extern struct { s16 unk0; s16 unk2; s16 unk4; } D_800DD470;

extern void func_1517B89C(s32, s32);
extern s32  allocate_memory(s32, s32, s32, s32);
extern s32  func_150AD9A0(s32, s32, s32);
extern void func_15170500(s32, s32, s32, s32, s32, s32, s32);
extern void func_10004074(s32);
extern void func_10006240(s32, s32, s32);

#define SCVB     ((ScVtx *)D_800DDD10[D_800BE9C0])
#define SCAS     (((ScAsset *)&D_800DDA90)[type])
#define SCCH(k)  (((s32 *)&D_800DD478)[type * 26 + (k)])

void func_1517BBAC(s32 px, s32 py, s32 pz, s32 range, f32 yaw, s32 cx, s32 cy, s32 cz)
{
    s32 i;
    s32 n;
    s32 lo;
    s32 hi;
    s32 mid;
    s32 dist;
    s32 sway;
    s32 dirSign;
    s32 axisFlag;
    s32 type;
    s16 xmax;
    s16 xmin;
    s16 zmax;
    s16 zmin;
    s32 d2;
    s32 j;
    s32 k;
    s32 lim;
    s32 sz;
    s32 r;
    s32 stride;
    s32 c;
    s32 m;
    s32 w;
    s32 h;
    s32 x;
    s32 y;
    s32 z;
    s32 cs;
    s32 sn;
    ScVtx *v;

    D_800DDD58 = 0;
    dirSign = 1;
    axisFlag = 1;
    xmin = px - range;
    xmax = px + range;
    zmin = pz - range;
    zmax = pz + range;
    hi = D_800DDD20 - 1;
    lo = 0;
    mid = 0;

    if ((yaw > 45.0f && yaw < 135.0f) || (yaw > 225.0f && yaw < D_800A7240)) {
        axisFlag = 0;
        if (yaw > 180.0f) {
            dirSign = -1;
        }
    } else if (yaw > 90.0f && yaw < 270.0f) {
        dirSign = -1;
    }

    if (axisFlag != D_8008CEB4) {
        D_8008CEB4 = axisFlag;
        func_1517B89C(0, hi);
    }

    while (lo <= hi) {
        mid = (lo + hi) / 2;
        if (axisFlag == 0) {
            if (dirSign == 1) {
                if (xmin < D_800DDD18[mid].x) {
                    hi = mid - 1;
                } else if (xmin > D_800DDD18[mid].x) {
                    lo = mid + 1;
                } else if (xmin == D_800DDD18[mid].x) {
                    break;
                }
            } else {
                if (xmax < D_800DDD18[mid].x) {
                    hi = mid - 1;
                } else if (xmax > D_800DDD18[mid].x) {
                    lo = mid + 1;
                } else if (xmax == D_800DDD18[mid].x) {
                    break;
                }
            }
        } else {
            if (dirSign == 1) {
                if (zmin < D_800DDD18[mid].z) {
                    hi = mid - 1;
                } else if (zmin > D_800DDD18[mid].z) {
                    lo = mid + 1;
                } else if (zmin == D_800DDD18[mid].z) {
                    break;
                }
            } else {
                if (zmax < D_800DDD18[mid].z) {
                    hi = mid - 1;
                } else if (zmax > D_800DDD18[mid].z) {
                    lo = mid + 1;
                } else if (zmax == D_800DDD18[mid].z) {
                    break;
                }
            }
        }
    }

    for (j = 0; j < 15; j++) {
        D_800DDC40[j] = 0x7FFF;
    }

    i = mid;
    if ((axisFlag == 0 && dirSign == 1 && i < D_800DDD20 && D_800DDD18[i].x < xmax) ||
        (axisFlag == 0 && dirSign == -1 && i >= 0 && xmin < D_800DDD18[i].x) ||
        (axisFlag != 0 && dirSign == 1 && i < D_800DDD20 && D_800DDD18[i].z < zmax) ||
        (axisFlag != 0 && dirSign == -1 && i >= 0 && zmin < D_800DDD18[i].z)) {
        n = (D_800DDD20 < (u32)D_800DDD0C) ? D_800DDD20 : (s32)D_800DDD0C;
        D_800DDD10[D_800BE9C0] = allocate_memory(n * 64, 4, 2, 0);
        if (D_800DDD10[D_800BE9C0] == 0) {
            return;
        }
    } else {
        D_800DDD10[D_800BE9C0] = 0;
        return;
    }

    for (n = 0;
         n < (u32)D_800DDD0C &&
             ((axisFlag == 0 && dirSign == 1 && i < D_800DDD20 && D_800DDD18[i].x < xmax) ||
              (axisFlag == 0 && dirSign == -1 && i >= 0 && xmin < D_800DDD18[i].x) ||
              (axisFlag != 0 && dirSign == 1 && i < D_800DDD20 && D_800DDD18[i].z < zmax) ||
              (axisFlag != 0 && dirSign == -1 && i >= 0 && zmin < D_800DDD18[i].z));
         i += dirSign) {
        dist = func_150AD9A0(D_800DDD18[i].x - px, D_800DDD18[i].y - py, D_800DDD18[i].z - pz);
        if (dist >= range) {
            continue;
        }
        type = D_800DDD18[i].kind & 0xF;
        if (dist < D_800DDC40[type]) {
            D_800DDC40[type] = dist;
        }
        d2 = func_150AD9A0(D_800DDD18[i].x - cx, D_800DDD18[i].y - cy, D_800DDD18[i].z - cz);
        if (d2 < 0x8D) {
            continue;
        }
        if (d2 < 0xF0) {
            dist = range - ((range - dist) * (d2 - 0x8C)) / 100;
        }

        if (SCCH(0) == 0) {
            if (SCAS.rom != 0) {
                sz = D_80095CE0[D_800DDBC0[type]].unk1 * D_80095CE0[D_800DDBC0[type]].unk2;
                SCAS.buf = func_10003C6C(SCAS.size, 1, 2, 1, 0);
                if (SCAS.buf != 0) {
                    SCCH(0) = func_10003C6C(sz, 4, 1, 0, 0);
                    if (SCCH(0) != 0) {
                        func_10004514(SCAS.rom, (void *)SCAS.buf, SCAS.size, 1);
                        SCAS.loaded = 1;
                        stride = D_80095CE2[D_800DDBC0[type] * 5];
                        for (j = 1; j < 26; j++) {
                            SCCH(j) = SCCH(j - 1) + stride;
                        }
                    } else {
                        func_10004074(SCAS.buf);
                    }
                }
            }
        } else if (SCAS.loaded == 0) {
            SCAS.loaded = 1;
            func_100043B4((s32 *)SCCH(0), 4);
        }

        v = &SCVB[n * 4];
        sway = D_800DDC90[D_800DDD18[i].swayIdx];
        if (sway < 0) {
            sway = 0;
        }

        if (D_800DD470.unk0 != 0 &&
            func_150AD9A0(D_800DDD18[i].x - D_800DD470.unk0, D_800DDD18[i].y - D_800DD472,
                          D_800DDD18[i].z - D_800DD474) < 0x50 &&
            D_800DDBC0[type] == 0 && D_800DDD18[i].state != 0x21) {
            D_800DDD18[i].state = 0x21;
            func_15170500(D_800DDD18[i].x, D_800DDD18[i].y + 0x44, D_800DDD18[i].z, 0, 0, 0xFF, 0);
        }

        if (D_800DDD18[i].state >= 0x21) {
            if (D_800DDD18[i].state >= 0x22) {
                D_800DDD18[i].state = D_800DDD18[i].state - 1;
            }
            v[3].flag = D_800DDD18[i].height;
        } else {
            if (dist < 0x30 && D_800DDBC0[type] == 0) {
                D_800DDD18[i].state = 0x22;
                func_15170500(D_800DDD18[i].x, D_800DDD18[i].y + 0x44, D_800DDD18[i].z, 0, 0, 0xFF, 0);
            }
            v[3].flag = D_800DDD18[i].height;
        }

        v[2].flag = D_800DDD18[i].halfW;
        dist = range - dist;
        dist = (s32)((u32)dist >> 1);
        if (dist >= 0x100) {
            dist = 0xFF;
        }
        v->cn[3] = dist;

        if (D_8008CEBC[D_8008CF00[D_800DDC80[type] * 16 + D_800DDD18[i].beh * 2]].fn != NULL) {
            if (D_8008CEBC[D_8008CF00[D_800DDC80[type] * 16 + D_800DDD18[i].beh * 2]].fn(
                    &D_800DDD18[i], v, &sway, &v->cn[3]) != 0) {
                continue;
            }
        } else {
            v->ob[0] = D_800DDD18[i].x;
            v->ob[1] = D_800DDD18[i].y;
            v->ob[2] = D_800DDD18[i].z;
        }

        c = D_800DDD18[i].kind | 0x9F;
        v[0].cn[0] = v[0].cn[1] = v[0].cn[2] = c;
        v[1].cn[0] = v[1].cn[1] = v[1].cn[2] = c;
        v[2].cn[0] = v[2].cn[1] = v[2].cn[2] = c;
        v[3].cn[0] = v[3].cn[1] = v[3].cn[2] = c;
        v[1].cn[3] = v[2].cn[3] = v[3].cn[3] = v[0].cn[3];

        if (D_800DDD18[i].state >= 0x21) {
            v->flag = D_800DDBE0[type] + type * 26;
        } else {
            v->flag = type * 26 + (sway >> 8);
        }
        v[1].flag = D_800DDBF0[type];

        SCVB[n * 4 + 1].tc[0] = SCVB[n * 4 + 2].tc[0] = D_800DDB80[type][0];
        SCVB[n * 4 + 2].tc[1] = SCVB[n * 4 + 3].tc[1] = D_800DDB80[type][1];
        n++;
    }

    D_800DDD58 = n;
    if (D_800BEAC0 == 0) {
        for (k = 0; k != 15; k++) {
            lim = (D_800DDBD0[k] << 8) - 1;
            if (lim < 0x101) {
                continue;
            }
            if ((1 << k) & D_800DDC04) {
                if ((1 << k) & D_800DDC08) {
                    r = func_151EF610() % 10;
                    if (r == 0) {
                        D_800DDC10[k] |= func_151EF610() % 16;
                    } else if (r == 1) {
                        D_800DDC10[k] &= func_151EF610() % 16;
                    } else {
                        r = D_800BE9E4 << 5;
                    }
                } else {
                    r = D_800BE9E4 << 6;
                }
                for (j = 0; j != 4; j++) {
                    if (D_800DDC10[k] & (1 << j)) {
                        D_800DDC90[k * 4 + j] -= r;
                        if (D_800DDC90[k * 4 + j] <= 0) {
                            D_800DDC90[k * 4 + j] = -D_800DDC90[k * 4 + j];
                            D_800DDC10[k] ^= (1 << j);
                        }
                    } else {
                        D_800DDC90[k * 4 + j] += r;
                        if (D_800DDC90[k * 4 + j] >= lim) {
                            D_800DDC90[k * 4 + j] = lim * 2 - D_800DDC90[k * 4 + j];
                            D_800DDC10[k] ^= (1 << j);
                        }
                    }
                }
            } else {
                r = D_800BE9E4 * 48;
                for (j = 0; j != 4; j++) {
                    D_800DDC90[k * 4 + j] += r;
                    if (D_800DDC90[k * 4 + j] >= lim) {
                        D_800DDC90[k * 4 + j] -= lim;
                    }
                }
            }
        }
    }

    m = func_151EF610() % (u32)D_800DDD0C;
    if (m < D_800DDD58) {
        if (SCVB[m * 4].flag % 26 == 0 && D_800DDBC0[SCVB[m * 4].flag / 26] == 0) {
            func_15170500(SCVB[m * 4].ob[0], SCVB[m * 4].ob[1] + 0x44, SCVB[m * 4].ob[2], 0, 1,
                          0xFF, 0);
        }
    }

    yaw = yaw * D_800A7244;
    cs = (s16)(cosf(yaw) * 128.0f);
    sn = (s16)(sinf(yaw) * 128.0f);
    for (m = 0; m < D_800DDD58; m++) {
        w = (s16)SCVB[m * 4 + 2].flag;
        x = SCVB[m * 4].ob[0];
        h = SCVB[m * 4 + 3].flag << 2;
        y = SCVB[m * 4].ob[1];
        z = SCVB[m * 4].ob[2];
        SCVB[m * 4].ob[0] = SCVB[m * 4 + 3].ob[0] = ((w * cs) >> 5) + x;
        SCVB[m * 4].ob[1] = SCVB[m * 4 + 1].ob[1] = y;
        SCVB[m * 4].ob[2] = SCVB[m * 4 + 3].ob[2] = z - ((w * sn) >> 5);
        SCVB[m * 4 + 1].ob[0] = SCVB[m * 4 + 2].ob[0] = x - ((w * cs) >> 5);
        SCVB[m * 4 + 2].ob[1] = SCVB[m * 4 + 3].ob[1] = h + y;
        SCVB[m * 4 + 1].ob[2] = SCVB[m * 4 + 2].ob[2] = ((w * sn) >> 5) + z;
        SCVB[m * 4].tc[0] = SCVB[m * 4].tc[1] = 0;
        SCVB[m * 4 + 1].tc[1] = SCVB[m * 4 + 3].tc[0] = 0;
    }
    D_800DD470.unk0 = 0;
}
