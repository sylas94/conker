typedef struct Obj131A {
    u8  pad0[0x40];
    s32 unk40;
    s32 *unk44;
    u8  pad48[0x7];
    u8  unk4F;
    u8  pad50[0x8];
    u16 unk58;
    u8  pad5A[0x46];
} Obj131A;

typedef struct Act127A {
    u8  pad0[0xF8];
    s32 unkF8;
    u8  padFC[0x80];
    f32 unk17C;
    u8  pad180[0x1E];
    s16 unk19E;
    u16 unk1A0;
    u8  pad1A2[0xD2];
    u8  unk274;
} Act127A;

extern u8   D_80089120[];
extern f32  D_800DBE54;
extern f32  D_800DBE58;
extern u16  D_800DBE60;
extern f32  D_800DBE68;
extern f32  D_800DBE6C;
extern f32  D_800DBE70;
extern s32 *D_800DBF94;
extern s32  D_800D37E0;
extern s32  D_800D3830;
extern f32  D_800A2D60;
extern f32  D_800A2D64;
extern f32  D_800A2D78;
extern f32  D_800A2D7C;
extern f32  D_800A2D80;
extern f32  D_800A2D84;
extern f32  D_800A2D88;
extern f32  D_800A2D8C;
extern f32  D_800A2D90;
extern f32  D_800A2D94;

extern s32  func_1510E670(s32);
extern void func_1510F800();
extern s32  func_150A6568(s32, s32, s32 *, s32, s32, s32, s32, s32);
extern void func_150A44F0(s32, s32 *, s32);
extern s32  func_150A43E0(s32, s32, s32, s32 *);
extern s32  func_150A4FA0(s32, s32);

#define RECS ((unkfunc_1510F8D8 *)&D_800D3300)

void func_1510E950(s32 p0, s32 p1, s32 p2, s32 p3, s32 p4, s32 p5, s32 p6, f32 x, f32 y, f32 z, f32 topY, u16 excl, s32 actorArg, f32 yMin, f32 yMax, s32 noFallback) {
    s32 pass;
    s32 bestIdx;
    s32 count;
    s32 firstPass;
    s32 i;
    s32 flag;
    s32 bestPass;
    s32 found;
    s32 total;
    s32 prop;
    f32 bestY;
    s32 xi;
    s32 triPtr;
    s32 zi;
    s32 vertBase;
    s32 numPasses;
    s32 base;
    s32 triIdx;
    s32 *vp;
    s16 *dst;
    s32 objIdPlus1;
    s32 dummy;
    s16 *q;
    unkfunc_1510F8D8 *rec;
    Obj131A *obj;
    s32 *bp;
    f32 none;
    f32 h;
    s32 bkIdx;
    s32 bkPass;
    s32 bkFound;
    s32 notFound;
    f32 thresh;
    f32 radius;
    s32 count1;
    s32 count2;
    s32 sub;
    f32 bestAbove;
    f32 best;
    f32 tenk;
    s32 *vp2;
    s16 *dst2;
    s16 *q2;
    s32 objIdx;

    if (p0 != 0) {
        *(s32 *)p0 = 0;
    }
    total = 0;
    triPtr = 0;
    prop = 0;
    flag = 0;
    if (actorArg != 0) {
        radius = D_800DBE64;
    } else {
        radius = 50.0f;
    }
    none = D_800A2D60;
    D_800DBE68 = x;
    D_800DBE6C = y;
    D_800DBE70 = z;
    bkFound = 0;
    *(f32 *)p3 = none;
    if (p5 == 0) {
        dummy = 0;
        p5 = (s32)&dummy;
    }
    bestAbove = D_800A2D64;
    D_800DBE54 = none;
    objIdPlus1 = 0;
    D_800DBE60 = 0;
    if (actorArg != 0) {
        ((Act127A *)actorArg)->unk19E = 0;
    }
    numPasses = 4;
    firstPass = 1;
    notFound = 1;
    if (p4 != 0) {
        *(f32 *)p4 = none;
    }

    for (pass = 0; pass != numPasses; pass++) {
        if (D_80089120[pass] != 1) {
            continue;
        }
        if ((pass == 3) && (actorArg != 0) && (((Act127A *)actorArg)->unkF8 & 0x200)) {
            continue;
        }
        xi = (s32)x;
        zi = (s32)z;
        found = 0;
        func_1510F800(pass);
        if (pass == 2) {
            count1 = func_150A6568((s16)xi, (s16)zi, &count2, excl, xi, zi, (s32)yMin, (s32)yMax);
            func_150A44F0(count1, &D_800D37E0, 0);
            if (p4 != 0) {
                func_150A44F0(count2, &D_800D3830, 0);
                sub = 0;
                count = func_150A43E0(xi, zi, count2, &D_800D3830);
                none = D_800A2D78;
                if (count != 0) {
                    best = none;
                    for (i = 0; i < count; i++) {
                        h = (f32)RECS[i].unk0 / 256.0f;
                        if (best < h) {
                            if (h < bestAbove) {
                                sub = i;
                                best = h;
                            }
                        }
                    }
                    *(f32 *)p4 = best;
                }
                if ((*(f32 *)p4 != none) && (p2 != 0)) {
                    vp = (s32 *)RECS[sub].unk4;
                    base = RECS[sub].unk8;
                    dst = (s16 *)p2;
                    for (i = 0; i < 3; i++) {
                        q = (s16 *)(*vp + base);
                        vp++;
                        dst[0] = q[0];
                        dst[1] = q[1];
                        dst[2] = q[2];
                        dst += 3;
                    }
                }
            }
            count = func_150A43E0(xi, zi, count1, &D_800D37E0);
            none = D_800A2D7C;
        } else if (pass == 3) {
            count = func_150A4FA0(xi, zi);
            none = D_800A2D80;
        } else {
            count = func_150A3A70(xi, zi);
            none = D_800A2D84;
        }
        total += count;
        if (firstPass != 0) {
            bestY = none;
            bestIdx = -1;
            bestPass = pass;
            firstPass = 0;
        }
        for (i = 0; i < count; i++) {
            h = (f32)RECS[i].unk0 * 0.00390625f;
            if ((noFallback == 0) && (notFound != 0) && (*(f32 *)p3 == none)) {
                if ((*(f32 *)p3 == none) || (h < *(f32 *)p3)) {
                    if (func_1510E670(i) != 0) {
                        bkFound = 1;
                        bkIdx = i;
                        bkPass = pass;
                    }
                    none = D_800A2D88;
                }
            }
            if (D_800DBE54 < h) {
                D_800DBE54 = h;
            }
            if (y < topY) {
                if (h < topY + radius) {
                    if (bestY < h) {
                        flag = 1;
                    }
                }
            } else if (h < y + radius) {
                if (h < topY) {
                    if (bestY < h) {
                        flag = 1;
                    }
                } else if (bestY < topY) {
                    flag = 1;
                } else if (h < bestY) {
                    flag = 1;
                }
            }
            if (flag != 0) {
                flag = 0;
                if (func_1510E670(i) != 0) {
                    bestPass = pass;
                    found = 1;
                    bestY = h;
                    bestIdx = i;
                }
                none = D_800A2D8C;
            }
        }
        if ((found != 0) || (bkFound != 0)) {
            if ((found == 0) && (bkFound != 0)) {
                bestIdx = bkIdx;
                bestPass = bkPass;
            }
            bkFound = 0;
            if (p6 != 0) {
                *(s16 *)p6 = bestPass;
            }
            if (bestIdx != -1) {
                rec = &RECS[bestIdx];
                notFound = 0;
                h = (f32)rec->unk0 * 0.00390625f;
                *(f32 *)p3 = h;
                if (h < none) {
                    *(f32 *)p3 = none;
                }
                triPtr = rec->unk4;
                base = rec->unk8;
                if (pass != 3) {
                    if ((actorArg != 0) && (base == 0)) {
                        ((Act127A *)actorArg)->unk19E = (triPtr - D_800DBE3C) / 12;
                    }
                } else {
                    if (actorArg != 0) {
                        ((Act127A *)actorArg)->unk19E = (triPtr - D_800C6070[D_800CC2D4[rec->unkC * 812]]) / 12;
                    }
                }
                if ((base == 0) && (p0 != 0)) {
                    *(s32 *)p0 = rec->unk4;
                }
                vertBase = base;
            } else {
                *(f32 *)p3 = none;
                vertBase = 0;
                if (p0 != 0) {
                    *(s32 *)p0 = D_800DBE3C;
                }
                triPtr = D_800DBE3C;
            }
            triIdx = (triPtr - D_800DBE3C) / 12;
            if ((pass == 0) && (p5 != 0)) {
                if (D_800DBE5C != 0) {
                    *(s32 *)p5 = ((s32 *)D_800DBE5C)[triIdx];
                } else {
                    *(s32 *)p5 = 0;
                }
            } else if ((pass == 2) && (p5 != 0)) {
                D_800DBE60 = RECS[bestIdx].unkC + 1;
                obj = &((Obj131A *)D_800DBEF4)[D_800DBE60];
                if (obj[-1].unk44 != 0) {
                    *(s32 *)p5 = obj[-1].unk44[triIdx - obj[-1].unk58];
                } else {
                    *(s32 *)p5 = obj[-1].unk40;
                }
            } else if (p5 != 0) {
                *(s32 *)p5 = 0;
            }
            if (pass == 3) {
                objIdPlus1 = RECS[bestIdx].unkC + 1;
            }
        }
        if (count >= 2) {
            if (*(f32 *)p3 < y) {
                thresh = y;
            } else {
                thresh = *(f32 *)p3;
            }
            for (i = 0; i < count; i++) {
                h = (f32)RECS[i].unk0 * 0.00390625f;
                if (thresh < h) {
                    if (h < bestAbove) {
                        if (func_1510E670(i) == 0) {
                            bestAbove = h;
                            triIdx = (RECS[i].unk4 - D_800DBE3C) / 12;
                            if (pass == 0) {
                                if (D_800DBE5C != 0) {
                                    prop = ((s32 *)D_800DBE5C)[triIdx];
                                } else {
                                    prop = 0;
                                }
                            } else if (pass == 2) {
                                objIdx = RECS[i].unkC + 1;
                                obj = &((Obj131A *)D_800DBEF4)[objIdx];
                                if (obj[-1].unk44 != 0) {
                                    prop = obj[-1].unk44[triIdx - obj[-1].unk58];
                                } else {
                                    prop = obj[-1].unk40;
                                }
                            } else {
                                prop = 0;
                            }
                        }
                        none = D_800A2D90;
                    }
                }
            }
        }
    }
    if (p4 != 0) {
        tenk = D_800A2D94;
        if ((bestAbove != tenk) && ((prop & 0x1F) == 8)) {
            *(f32 *)p4 = tenk;
        }
        if ((*(f32 *)p4 == none) && ((*(s32 *)p5 & 0x1F) == 8)) {
            *(f32 *)p4 = *(f32 *)p3;
        }
    }
    if ((triPtr != 0) && (p1 != 0)) {
        vp2 = (s32 *)triPtr;
        dst2 = (s16 *)p1;
        for (i = 0; i < 3; i++) {
            q2 = (s16 *)(*vp2 + vertBase);
            vp2++;
            dst2[0] = q2[0];
            dst2[1] = q2[1];
            dst2[2] = q2[2];
            dst2 += 3;
        }
        if (p0 != 0) {
            *(s32 *)p0 = 0;
        }
    }
    if (actorArg != 0) {
        ((Act127A *)actorArg)->unk1A0 = D_800DBE60;
        if ((D_800DBE60 != 0) && (y - *(f32 *)p3 < 10.0f)) {
            obj = &((Obj131A *)D_800DBEF4)[D_800DBE60];
            obj[-1].unk4F |= 0x84;
            bp = &D_800DBF94[D_800DBE60];
            bp[-1] |= 1 << ((actorArg - (s32)D_800CC2D0) / 812);
        }
        if ((objIdPlus1 != 0) && (y - *(f32 *)p3 < 10.0f)) {
            ((Act127A *)actorArg)->unk274 = objIdPlus1;
        } else {
            ((Act127A *)actorArg)->unk274 = 0;
        }
    }
    if (total == 0) {
        *(f32 *)p3 = none;
        if (p5 != 0) {
            *(s32 *)p5 = 0;
        }
    }
    if (actorArg != 0) {
        ((Act127A *)actorArg)->unk17C = bestAbove;
    }
    D_800DBE58 = bestAbove;
}
