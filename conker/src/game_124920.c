#include <ultra64.h>
#define func_150ADA20 func_150ADA20_u8_decl_in_functions_h
#define func_10010F88 func_10010F88_void_decl_in_functions_h
#include "functions.h"
#undef func_150ADA20
#undef func_10010F88
s32 func_150ADA20(void);
#include "variables.h"

extern f32 sinf(f32);
extern s32 func_15145128(struct17 *, struct17 *, f32 *, f32 *);
extern s32 func_15146078(struct17 *, struct17 *, struct17 *);

typedef struct {
    f32 unk00;
    f32 unk04;
    f32 unk08;
    f32 unk0C;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    struct17 unk28;
    struct17 unk34;
    struct17 unk40;
    f32 unk4C;
    s32 unk50;
    s16 unk54;
    s16 unk56;
    u8 unk58;
    u8 pad59[3];
    s32 unk5C;
    u8 unk60;
    u8 unk61;
    u8 unk62;
    u8 unk63;
    u8 unk64;
    u8 unk65;
    u8 unk66;
    u8 unk67;
    u8 unk68;
    u8 pad69;
    u8 unk6A;
    u8 pad6B;
    s32 unk6C;
    u8 unk70;
    u8 pad71;
    s16 unk72;
    s16 unk74;
    u8 pad76[2];
    s32 unk78;
} Func150F802CSpawn;

typedef struct {
    u8 unk0;
    u8 unk1;
    s16 unk2;
    s16 unk4;
    s32 unk8;
    s32 unkC;
    u8 unk10;
    u8 unk11;
    u8 unk12;
    u8 unk13;
    f32 unk14;
    f32 unk18;
    struct17 unk1C;
    struct17 unk28;
    f32 unk34;
    f32 unk38;
    f32 unk3C;
    s32 unk40;
    u8 unk44;
    u8 unk45;
    u8 unk46;
    u8 unk47;
    s32 unk48;
    u8 unk4C;
    u8 pad4D[3];
    s32 unk50;
} Func150F81BCSpawn;

typedef struct {
    struct17 unk0;
    struct17 unkC;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
} Func150F81BCExtra;

struct Func150F7E20Sub {
    u8 pad0[0x18];
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
};

struct Func150F7E20Obj {
    u8 pad0[0x2C];
    f32 unk2C;
    f32 unk30;
    u8 pad34[0x28];
    u8 unk5C;
};


typedef struct {
    u8 pad0[4];
    f32 unk4;
    u8 pad8[0x30];
    struct17 unk38;
    u8 pad44[0x20];
    s32 unk64;
    f32 unk68;
    f32 unk6C;
    u8 unk70;
    u8 pad71[3];
    struct17 unk74;
    struct17 unk80;
    f32 unk8C;
    f32 unk90;
    f32 unk94;
    struct17 unk98;
    struct17 unkA4;
    s8 unkB0;
    u8 padB1[3];
} Func150F7470Big;

typedef struct {
    u8 pad0[0x3B];
    u8 unk3B;
} Func150F7470Obj;

extern s32 func_151C4B0C(s32, Func150F7470Big *, struct17 *, struct17 *, f32 *, f32, u8, s32, struct17 *, u8 *, s32,
                         f32, Func150F7470Obj *, s32, u8, u8, s32, u8);
extern void func_15145974(struct17 *, f32 *, f32 *);
s32 func_1513264C(void *arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, u8 arg5, s32 arg6);
s32 func_10010F88(s32 arg0, u16 arg1, s16 arg2, u8 arg3, s32 arg4, s16 arg5, s16 arg6, s16 arg7, s16 arg8, s16 arg9);

void func_150F7470(struct17 *arg0, struct17 *arg1, s32 arg2, struct17 *arg3, u8 arg4, s32 arg5, f32 arg6, f32 arg7,
                   f32 arg8, Func150F7470Obj *arg9, u8 arg10, u8 arg11, u8 arg12, u8 arg13, s32 arg14, s8 arg15,
                   s32 arg16, u8 arg17, u8 arg18, s32 arg19) {
    Func150F7470Big big;
    Func150F802CSpawn spawn;
    s32 ret;
    struct17 dirB;
    u8 hasB;
    struct17 dirA;
    u8 hasA;

    hasB = 0;
    hasA = arg4;
    if (arg4) {
        dirA = *arg3;
    }
    big.unk70 = (arg11 ? 1 : 0) | (arg12 ? 2 : 0) | (arg13 ? 4 : 0);
    big.unkB0 = arg15;
    if (arg2 != 0 && arg3 != NULL) {
        if (!hasA) {
            if (!func_15145128(arg3, &dirA, NULL, NULL)) {
                return;
            }
            hasA = 1;
        }
    } else if (arg1 != NULL) {
        if (!func_15145128(arg1, &dirB, NULL, NULL)) {
            return;
        }
        hasB = 1;
    }
    if (!func_151C4B0C(arg5, &big, arg0, hasB ? &dirB : NULL, &big.unk68, arg7, arg10, arg2, hasA ? &dirA : NULL,
                       &big.unk70, 1, arg8, arg9, arg15, arg12, arg13, 0, arg17)) {
        return;
    }
    if (!func_15146078(&big.unk38, &big.unk74, &big.unk80)) {
        return;
    }
    big.unk64 = arg14;
    big.unk90 = 0.0f;
    big.unk8C = 0.0f;
    big.unk94 = 70.0f * arg7;
    big.unk98 = *arg0;
    big.unk6C = arg6;
    big.unkA4.unk0 = big.unk38.unk0 * 70.0f;
    big.unkA4.unk4 = big.unk38.unk4 * 70.0f;
    big.unkA4.unk8 = big.unk38.unk8 * 70.0f;
    big.unk70 |= (big.unk4 > 150.0f) ? 1 : 0;
    spawn.unk00 = 1.0f;
    spawn.unk04 = 1.0f;
    spawn.unk0C = 0.02000000142f;
    spawn.unk08 = 0.02000000142f;
    func_15145974(&big.unk38, &spawn.unk14, &spawn.unk10);
    spawn.unk1C = 1.0f;
    spawn.unk20 = 1.0f;
    spawn.unk24 = 1.0f;
    spawn.unk18 = 0.0f;
    spawn.unk28 = *arg0;
    spawn.unk34.unk0 = big.unk38.unk0 * arg6;
    spawn.unk34.unk4 = big.unk38.unk4 * arg6;
    spawn.unk34.unk8 = big.unk38.unk8 * arg6;
    spawn.unk40 = *(struct17 *)&D_800A5480;
    spawn.unk4C = 0.0f;
    spawn.unk50 = 0x120;
    spawn.unk54 = 0x12C;
    spawn.unk56 = 0x2F;
    spawn.unk58 = 0;
    spawn.unk5C = 0;
    spawn.unk60 = 0xFF;
    spawn.unk61 = 0x13;
    spawn.unk62 = 0;
    spawn.unk63 = 0;
    spawn.unk64 = 0;
    spawn.unk65 = 0;
    spawn.unk66 = 0;
    spawn.unk67 = 0;
    spawn.unk68 = 0;
    spawn.unk6A = 0;
    spawn.unk6C = (s32)arg9;
    spawn.unk70 = arg9->unk3B;
    spawn.unk72 = 1;
    spawn.unk74 = 0xFF;
    if (arg16 != 0) {
        spawn.unk78 = func_10010F88(arg16, 0x4650, -500, 0, -1, spawn.unk28.unk0, spawn.unk28.unk4, spawn.unk28.unk8,
                                    1000, 2000);
    } else {
        spawn.unk78 = 0;
    }
    ret = func_1513264C(&spawn, 0, 0, 0, 0xB4, arg18, arg19);
    if (ret != 0) {
        memcpy((void *)(ret + 0x170), &big, sizeof(big));
    }
}

typedef struct {
    s32 unk00;
    f32 unk04;
    struct17 unk08;
    struct17 unk14;
    struct17 unk20;
    struct17 unk2C;
    struct17 unk38;
    u8 unk44[0x12];
    s16 unk56;
    u8 unk58;
    u8 unk59;
    u8 unk5A;
    u8 pad5B;
    s32 unk5C;
    s32 unk60;
    u8 pad64[0xC];
} Func150F78B4Ray;

typedef struct {
    u8 pad0;
    u8 unk1;
    u8 pad2[0xA];
    u8 unkC;
    u8 padD[0x2B];
    f32 unk38;
    f32 unk3C;
    f32 unk40;
    f32 unk44;
    f32 unk48;
    f32 unk4C;
    u8 pad50[0x2C];
    s32 unk7C;
    u8 pad80[8];
    s32 unk88;
    u8 pad8C[0xE4];
    Func150F7470Big unk170;
} Func150F78B4Obj;

void func_15081690(s32, f32, f32, f32, f32, f32, f32, Func150F78B4Ray *, f32, s32, s32, s32, s32, s32, s32);
void func_151D4DAC(s32, s32, struct17 *, struct17 *, Func150F78B4Ray *, s32, struct17 *, u8, s32);
void func_150F7F8C(void *arg0, u8 arg1, s32 arg2);

s8 func_150F78B4(Func150F78B4Obj *arg0) {
    Func150F7470Big *big;
    s32 obj;
    s8 result;
    f32 step;
    f32 scale;
    Func150F78B4Ray ray;
    f32 count;
    void *ret;

    result = 1;
    big = &arg0->unk170;
    obj = arg0->unk7C;
    step = (big->unk68 < D_800BE9A4) ? big->unk68 : D_800BE9A4;
    if (arg0->unk88 != 0) {
        func_1000F9D4(arg0->unk88, arg0->unk38, arg0->unk3C, arg0->unk40);
    }
    scale = big->unk6C * step;
    if (big->unk70 & 2) {
        func_15081690(obj, arg0->unk38, arg0->unk3C, arg0->unk40, big->unk38.unk0, big->unk38.unk4, big->unk38.unk8,
                      &ray, scale, 1, 0, !(big->unk70 & 4), big->unkB0, 0, 0);
        if (ray.unk59 >= 2) {
            func_151D4DAC(ray.unk00, obj, &ray.unk08, &ray.unk20, &ray, 0x1A, &big->unk38, arg0->unkC, arg0->unk1);
            if (big->unk70 & 1) {
                func_150F7F8C(&ray.unk08, arg0->unkC, arg0->unk1);
            }
            result = 0;
        }
    }
    arg0->unk38 += arg0->unk44 * step;
    arg0->unk3C += arg0->unk48 * step;
    arg0->unk40 += arg0->unk4C * step;
    if (result == 1) {
        big->unk68 -= D_800BE9A4;
        if (big->unk68 <= 0.0f) {
            result = 0;
            if (big->unk70 & 1) {
                func_150F7F8C(&arg0->unk38, arg0->unkC, arg0->unk1);
            }
        }
    }
    {
        Func150F81BCSpawn spawn;

        big->unk8C += scale;
        big->unk90 += step;
        count = big->unk8C * 0.01428571437f;
        if (count > 1.0f) {
            Func150F81BCExtra extra;

            extra.unk0 = big->unk74;
            extra.unkC = big->unk80;
            extra.unk24 = 8.318000793f;
            extra.unk28 = 8.318000793f;
            spawn.unk0 = 0x7A;
            spawn.unk1 = 0;
            spawn.unk2 = 0x4404;
            spawn.unk4 = 0xA;
            spawn.unk8 = 0;
            spawn.unkC = 0;
            spawn.unk10 = 0xFF;
            spawn.unk11 = 0xFF;
            spawn.unk12 = 0xFF;
            spawn.unk13 = 0xFF;
            spawn.unk14 = 0.0f;
            spawn.unk18 = 0.0f;
            extra.unk20 = 0.4670000076f;
            spawn.unk28 = *(struct17 *)&D_800A5480;
            spawn.unk34 = 1.0f;
            spawn.unk38 = 1.0f;
            spawn.unk3C = 1.0f;
            spawn.unk40 = 0xCC0008;
            spawn.unk45 = 0xFF;
            spawn.unk46 = 0;
            spawn.unk47 = 6;
            spawn.unk48 = 0;
            spawn.unk4C = 0xFF;
            spawn.unk50 = 0;
            do {
                extern s32 D_800A4AA0;

                extra.unk1C = 4.712388992f;
                extra.unk18 = 27.0f - big->unk90;
                spawn.unk1C = big->unk98;
                spawn.unk44 = extra.unk18 * 6.481481552f;
                ret = func_1513D2F0(&spawn, (s32)&D_800A4AA0, 0x24, 0, 0, 0x21, 0, 0, 0, 0x2C, arg0->unkC, arg0->unk1);
                if (ret != NULL) {
                    memcpy((u8 *)ret + 0x110, &extra, sizeof(extra));
                }
                big->unk8C -= 70.0f;
                big->unk90 -= big->unk94;
                big->unk98.unk0 += big->unkA4.unk0;
                big->unk98.unk4 += big->unkA4.unk4;
                big->unk98.unk8 += big->unkA4.unk8;
                count -= 1.0f;
            } while (count > 1.0f);
        }
    }
    return result;
}

s32 func_150F7E20(struct Func150F7E20Obj *arg0) {
    f32 temp;
    struct Func150F7E20Sub *sub;

    sub = (struct Func150F7E20Sub *)((u8 *)arg0 + 0x110);
    arg0->unk5C = sub->unk18 * 6.481481552f;
    temp = (sinf(sub->unk1C) * sub->unk28) + sub->unk24;
    arg0->unk30 = temp;
    arg0->unk2C = temp;
    sub->unk1C = func_15144B68(sub->unk1C + (sub->unk20 * D_800BE9A4));
    sub->unk18 -= D_800BE9A4;
    if (sub->unk18 < 0.0f) {
        return 0;
    }
    return 1;
}

void func_150F7F58(struct210 *arg0, s16 arg1) {
    func_15140410(arg0, &arg0->unk110, &arg0->unk11C, arg1);
}

extern f32 func_150ADA68(void);
void func_151541B8(void *, f32, u32, f32, f32, u8, s32);
void func_151D3F14(void *, u8, s32);


void func_150F7F8C(void *arg0, u8 arg1, s32 arg2) {
    f32 temp1;
    f32 temp0;

    temp0 = func_150ADA68();
    temp1 = func_150ADA68();
    func_151541B8(arg0, temp0 * 3.0f + 9.0f, 0x3F030C35, temp1 * 70.0f + 70.0f, 0.0f, arg1, arg2);
    func_151D3F14(arg0, arg1, arg2);
}


typedef struct {
    f32 *unk0;
    struct17 unk4;
    f32 unk10;
} Func150F802CExtra;

void func_150F802C(f32 *arg0, s16 arg1, u8 arg2, s32 arg3) {
    Func150F802CExtra extra;
    Func150F802CSpawn spawn;
    s32 ret;

    extra.unk0 = arg0;
    extra.unk4.unk0 = arg0[0];
    extra.unk4.unk4 = arg0[1];
    extra.unk4.unk8 = arg0[2];
    extra.unk10 = 0.0f;
    spawn.unk00 = 1.0f;
    spawn.unk04 = 1.0f;
    spawn.unk08 = 0.02000000142f;
    spawn.unk0C = 0.02000000142f;
    spawn.unk10 = arg0[3];
    spawn.unk14 = arg0[4];
    spawn.unk18 = arg0[5];
    spawn.unk1C = 1.0f;
    spawn.unk20 = 1.0f;
    spawn.unk24 = 1.0f;
    spawn.unk28.unk0 = arg0[0];
    spawn.unk28.unk4 = arg0[1];
    spawn.unk28.unk8 = arg0[2];
    spawn.unk34.unk0 = 0.0f;
    spawn.unk34.unk4 = 0.0f;
    spawn.unk34.unk8 = 0.0f;
    spawn.unk40 = *(struct17 *)&D_800A5480;
    spawn.unk4C = 0.0f;
    spawn.unk50 = 0x980;
    spawn.unk54 = arg1;
    spawn.unk56 = 0x2F;
    spawn.unk58 = 0;
    spawn.unk5C = 0;
    spawn.unk60 = 0xFF;
    spawn.unk61 = 0x14;
    spawn.unk62 = 0;
    spawn.unk63 = 0;
    spawn.unk64 = 0;
    spawn.unk65 = 0;
    spawn.unk66 = 0;
    spawn.unk67 = 0;
    spawn.unk68 = 0;
    spawn.unk6A = 0;
    spawn.unk6C = 0;
    spawn.unk70 = 0;
    spawn.unk72 = 1;
    spawn.unk74 = 0xFF;
    spawn.unk78 = 0;
    ret = func_1513264C(&spawn, 3, 0xFF, 0, 0xB4, arg2, arg3);
    if (ret != 0) {
        memcpy((void *)(ret + 0x170), &extra, sizeof(extra));
    }
}


typedef struct {
    u8 pad0;
    u8 unk1;
    u8 pad2[0xA];
    u8 unkC;
    u8 padD[0x13];
    f32 unk20;
    f32 unk24;
    f32 unk28;
    u8 pad2C[0xC];
    f32 unk38;
    f32 unk3C;
    f32 unk40;
    u8 pad44[0x12C];
    Func150F802CExtra unk170;
} Func150F81BCObj;

s32 func_150F81BC(Func150F81BCObj *arg0) {
    Func150F802CExtra *ext;

    ext = &arg0->unk170;
    arg0->unk38 = ext->unk0[0];
    arg0->unk3C = ext->unk0[1];
    arg0->unk40 = ext->unk0[2];
    arg0->unk20 = ext->unk0[3];
    arg0->unk24 = ext->unk0[4];
    arg0->unk28 = ext->unk0[5];
    {
        struct17 diff;
        f32 dist;
        f32 unused;
        struct17 dir;
        f32 count;

        diff.unk0 = arg0->unk38 - ext->unk4.unk0;
        diff.unk4 = arg0->unk3C - ext->unk4.unk4;
        diff.unk8 = arg0->unk40 - ext->unk4.unk8;
        ext->unk10 += D_800BE9A4;
        if (func_15145128(&diff, &dir, &dist, &unused) != 0) {
            struct17 step;
            void *ret;
            Func150F81BCSpawn spawn;
            Func150F81BCExtra extra;

            step.unk0 = dir.unk0 * 20.0f;
            step.unk4 = dir.unk4 * 20.0f;
            step.unk8 = dir.unk8 * 20.0f;
            count = dist * 0.05000000075f;
            if (count > 1.0f) {
                f32 rate;

                rate = ext->unk10 / count;
                func_15146078(&diff, &extra.unk0, &extra.unkC);
                extra.unk20 = 0.4630000293f;
                extra.unk24 = 8.241000175f;
                extra.unk28 = 3.888999939f;
                spawn.unk0 = 0x7A;
                spawn.unk1 = 0;
                spawn.unk2 = 0x4404;
                spawn.unk4 = 0xA;
                spawn.unk8 = 0;
                spawn.unkC = 0;
                spawn.unk10 = 0xFF;
                spawn.unk11 = 0xFF;
                spawn.unk12 = 0xFF;
                spawn.unk13 = 0xFF;
                spawn.unk18 = 0.0f;
                spawn.unk14 = 0.0f;
                spawn.unk28 = *(struct17 *)&D_800A5480;
                spawn.unk34 = 1.0f;
                spawn.unk38 = 1.0f;
                spawn.unk3C = 1.0f;
                spawn.unk40 = 0xCC0008;
                spawn.unk45 = 0xFF;
                spawn.unk46 = 0;
                spawn.unk47 = 6;
                spawn.unk48 = 0;
                spawn.unk4C = 0xFF;
                spawn.unk50 = 0;
                do {
                    extern s32 D_800A4AA0;

                    extra.unk1C = 4.712388992f;
                    extra.unk18 = 27.0f - ext->unk10;
                    spawn.unk1C = ext->unk4;
                    spawn.unk44 = extra.unk18 * 6.481481552f;
                    ret = func_1513D2F0(&spawn, (s32)&D_800A4AA0, 0x24, 0, 0, 0x21, 0, 0, 0, 0x2C, arg0->unkC, arg0->unk1);
                    if (ret != NULL) {
                        memcpy((u8 *)ret + 0x110, &extra, sizeof(extra));
                    }
                    ext->unk4.unk0 += step.unk0;
                    ext->unk4.unk4 += step.unk4;
                    ext->unk4.unk8 += step.unk8;
                    count -= 1.0f;
                    ext->unk10 -= rate;
                } while (count > 1.0f);
            }
        }
    }
    return 1;
}
