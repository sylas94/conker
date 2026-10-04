/* tools/nearmiss/func_15180580.c -- game_1AC2F0, 991 instructions, frame 0x130
 *
 * STATUS (2026-10-03, bottom-up big wave): mism=966, n=990/991, frame EXACT (verified via .mdebug
 * homes), prologue/$s assignment/control flow/all 18 call sites match. Residue ~150 structural +
 * ~200 register rows, mostly scheduling + temp-counter knock-on. NOT a near-miss in the usual sense.
 * ALSO BLOCKED ON RODATA: 0.01f / -399.0f must be literals (extern f32 -> 968, frame 296); they are
 * D_800A728C/D_800A7290 in block 24BD10, shared with still-asm func_1517E4A8/1517F814/151814FC/
 * 15181EE0 -> needs the whole-block campaign (see scratchpad campaigns ranking).
 * Levers found (1528 -> 966): `s32 pos[2]` aggregate (golden keeps centre coords in memory and
 * reloads after each call); named `f32 temp` for the two x0.01 products; loop literal `1.f` vs
 * `1.0f` (pooling); every call assigns all four x0/y0/x1/y1 (s-reg numbering by first appearance);
 * statement order w,bottom,left,top,right; second clamp constant is 28.0f not 30.0f.
 * First divergence: top region -- golden loads 0.01f/1.0f at the start of the `D_800C35EA == 1`
 * block after a nop (scope boundary?) and copies the merge block's first insn (`mtc1 zero,$f8`)
 * into the `b .L151806BC` delay slot. NOTE (2026-10-03, func_150F34F4): a block-scoped DECLARATION
 * can produce exactly that copy-strategy slot -- try a block-scoped local at that boundary first.
 * Texture section: golden holds 0.0f args in f20 across both func_1517FB9C calls (unsolved).
 */
typedef struct {
    char pad0[0x4];
    f32 unk4;
    f32 unk8;
    f32 unkC;
    f32 unk10;
    char pad14[0x10];
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    f32 unk30;
    char pad34[0x14C];
} Struct15180580;

extern f32 *D_800DDE44;
extern f32 *D_800DDE48;
extern f32 *D_800DDE4C;
extern f32 D_800DDDE8[][2];
extern Gfx D_8008D018[];
extern s32 D_80090298[];
extern u8 D_800DDD78[];
extern s32 func_1510D0EC(s32, s32, s32, s32);
extern Gfx *func_1517F9F4(Gfx *, s32, s32, s32, s32, s32);
extern Gfx *func_1517FB9C(Gfx *, s32, s32, f32, f32, s32);

#define WGFX15180580(pkt, a, b)     \
{                                   \
    Gfx *_g = (Gfx *)(pkt);         \
    _g->words.w0 = (u32)(a);        \
    _g->words.w1 = (u32)(b);        \
}

Gfx *func_15180580(Gfx *gfx, s32 arg1) {
    f32 scale;
    f32 temp;

    s32 i;
    s16 x0;
    s16 y0;
    s16 x1;
    s16 y1;

    if (D_800DDE40 != 0) {
        if (D_800C35EA == 1) {
            scale = *D_800DDE44 * 0.01f;
            if (1.0f < scale) {
                scale = 1.0f;
            } else if (scale < 0.0f) {
                scale = 0.0f;
            }
            temp = *D_800DDE48 * 0.01f;
            D_800DDDE8[arg1][0] = ((Struct15180580 *)D_800BE628)->unk4 * temp;
            temp = -(*D_800DDE4C * 0.01f);
            D_800DDDE8[arg1][1] = ((Struct15180580 *)D_800BE628)->unk8 * temp;
        } else {
            scale = 1.0f;
        }
    } else {
        scale = (&D_800DDDC8)[arg1];
    }

    if (scale == 0.0f) {
        return gfx;
    }

    gSPDisplayList(gfx++, D_8008D018);
    gDPPipeSync(gfx++);
    gDPSetFillColor(gfx++, 0x10001);
    gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, 255);
    WGFX15180580(gfx++, 0xFCFFFFFF, 0xFFFDF6FB);
    WGFX15180580(gfx++, 0xEF000CFF, 0x0F0A4004);
    WGFX15180580(gfx++, 0xD9E0FFFE, 0);
    WGFX15180580(gfx++, 0xD9FFFFFF, 0x200004);

    if (scale < 1.0f) {
        s16 left;
        s16 top;
        s16 w;
        s16 bottom;
        s16 right;

        w = -399.0f * scale + 400.0f;
        bottom = ((Struct15180580 *)D_800BE628)[arg1].unk28;
        left = ((Struct15180580 *)D_800BE628)[arg1].unk2C;
        top = ((Struct15180580 *)D_800BE628)[arg1].unk24;
        right = ((Struct15180580 *)D_800BE628)[arg1].unk30;
        y0 = top;
        y1 = (((Struct15180580 *)D_800BE628)[arg1].unk10 + D_800DDDE8[arg1][1]) - w;
        x0 = left;
        x1 = right;
        gfx = func_1517F9F4(gfx, x0, y0, x1, y1, arg1);

        y0 = (((Struct15180580 *)D_800BE628)[arg1].unk10 + D_800DDDE8[arg1][1]) + w;
        y1 = bottom;
        x0 = left;
        x1 = right;
        gfx = func_1517F9F4(gfx, x0, y0, x1, y1, arg1);

        y0 = (((Struct15180580 *)D_800BE628)[arg1].unk10 + D_800DDDE8[arg1][1]) - w;
        y1 = (((Struct15180580 *)D_800BE628)[arg1].unk10 + D_800DDDE8[arg1][1]) + w;
        x0 = left;
        x1 = (((Struct15180580 *)D_800BE628)[arg1].unkC + D_800DDDE8[arg1][0]) - w;
        gfx = func_1517F9F4(gfx, x0, y0, x1, y1, arg1);

        y0 = (((Struct15180580 *)D_800BE628)[arg1].unk10 + D_800DDDE8[arg1][1]) - w;
        y1 = (((Struct15180580 *)D_800BE628)[arg1].unk10 + D_800DDDE8[arg1][1]) + w;
        x0 = (((Struct15180580 *)D_800BE628)[arg1].unkC + D_800DDDE8[arg1][0]) + w;
        x1 = right;
        gfx = func_1517F9F4(gfx, x0, y0, x1, y1, arg1);

        if ((&D_800DDE1C)[arg1] != 0) {
            gDPPipeSync(gfx++);
            WGFX15180580(gfx++, 0xEF002C0F, 0x0F0A4004);
            WGFX15180580(gfx++, 0xFCFFFFFF, 0xFFFDF6FB);
            gDPSetPrimColor(gfx++, 0, 0, 0, 0, 0, 255);

            for (i = 0; i < 2; i++) {
                y0 = ((Struct15180580 *)D_800BE628)[arg1].unk10 - 1.f;
                y1 = ((Struct15180580 *)D_800BE628)[arg1].unk10 + 1.f;
                gfx = func_1517F9F4(gfx, left - i, y0 - i, right + i, y1 + i, arg1);
                x0 = ((Struct15180580 *)D_800BE628)[arg1].unkC - 1.f;
                x1 = ((Struct15180580 *)D_800BE628)[arg1].unkC + 1.f;
                gfx = func_1517F9F4(gfx, x0 - i, top - i, x1 + i, bottom + i, arg1);
                if ((&D_800DDE1C)[arg1] == 1) {
                    s32 pos[2];

                    pos[0] =((Struct15180580 *)D_800BE628)[arg1].unkC + D_800DDDE8[arg1][0];
                    pos[1] = ((Struct15180580 *)D_800BE628)[arg1].unk10 + D_800DDDE8[arg1][1];

                    x0 = pos[0] - 60; x1 = pos[0] - 30; y0 = pos[1] - 60; y1 = pos[1] - 58;
                    gfx = func_1517F9F4(gfx, x0 - i, y0 - i, x1 + i, y1 + i, arg1);
                    y0 = pos[1] - 60; y1 = pos[1] - 30; x0 = pos[0] - 60; x1 = pos[0] - 58;
                    gfx = func_1517F9F4(gfx, x0 - i, y0 - i, x1 + i, y1 + i, arg1);
                    y0 = pos[1] - 30; y1 = pos[1] - 60; x0 = pos[0] + 58; x1 = pos[0] + 60;
                    gfx = func_1517F9F4(gfx, x0 - i, y0 - i, x1 + i, y1 + i, arg1);
                    y0 = pos[1] - 58; y1 = pos[1] - 60; x0 = pos[0] + 30; x1 = pos[0] + 60;
                    gfx = func_1517F9F4(gfx, x0 - i, y0 - i, x1 + i, y1 + i, arg1);
                    y0 = pos[1] + 60; y1 = pos[1] + 30; x0 = pos[0] + 60; x1 = pos[0] + 58;
                    gfx = func_1517F9F4(gfx, x0 - i, y0 - i, x1 + i, y1 + i, arg1);
                    y0 = pos[1] + 60; y1 = pos[1] + 58; x0 = pos[0] + 60; x1 = pos[0] + 30;
                    gfx = func_1517F9F4(gfx, x0 - i, y0 - i, x1 + i, y1 + i, arg1);
                    y0 = pos[1] + 60; y1 = pos[1] + 30; x0 = pos[0] - 60; x1 = pos[0] - 58;
                    gfx = func_1517F9F4(gfx, x0 - i, y0 - i, x1 + i, y1 + i, arg1);
                    y0 = pos[1] + 60; y1 = pos[1] + 58; x0 = pos[0] - 60; x1 = pos[0] - 30;
                    gfx = func_1517F9F4(gfx, x0 - i, y0 - i, x1 + i, y1 + i, arg1);
                }
                if (i == 0) {
                    gDPPipeSync(gfx++);
                    WGFX15180580(gfx++, 0xEF002C0F, 0x00504244);
                    gDPSetFillColor(gfx++, 0);
                    gDPSetPrimColor(gfx++, 0, 0, 255, 255, 255, 0);
                }
            }
        }

        gDPPipeSync(gfx++);
        WGFX15180580(gfx++, 0xFCFFFFFF, 0xFFFFF3F9);
        WGFX15180580(gfx++, 0xD7000002, 0xFFFFFFFF);
        WGFX15180580(gfx++, 0xFD900000, func_1510D0EC(D_80090298[1], 0, 3, 0));
        WGFX15180580(gfx++, 0xF5900000, 0x07000000);
        WGFX15180580(gfx++, 0xF3000000, 0x077FF000);
        WGFX15180580(gfx++, 0xF5881000, 0x00098260);
        WGFX15180580(gfx++, 0xF2002002, 0x000FE0FE);
        WGFX15180580(gfx++, 0xEF002CFF, 0x005011C4);

        gfx = func_1517FB9C(gfx, w, 0x40, 0.0f, 0.0f, arg1);
        if ((&D_800DDE1C)[arg1] != 0) {
            gDPPipeSync(gfx++);
            WGFX15180580(gfx++, 0xFD700000, func_1510D0EC(D_80090298[2], 0, 3, 0));
            WGFX15180580(gfx++, 0xF5700000, 0x07000000);
            WGFX15180580(gfx++, 0xF3000000, 0x077FF000);
            WGFX15180580(gfx++, 0xF5681000, 0x00098260);
            gfx = func_1517FB9C(gfx, w / 2, 0x40, 0.0f, 0.0f, arg1);
            if ((&D_800DDE1C)[arg1] == 2) {
                WGFX15180580(gfx++, 0xFCFFFFFF, 0xFFFCF279);
                WGFX15180580(gfx++, 0xFD100000, func_1510D0EC(D_80090298[D_800DDD78[arg1] + 3], 0, 3, 0));
                WGFX15180580(gfx++, 0xF5100000, 0x07000000);
                WGFX15180580(gfx++, 0xF3000000, 0x073FF000);
                WGFX15180580(gfx++, 0xF5101000, 0x00094250);

                gfx = func_1517FB9C(gfx, w / 4, 0x20, 32.0f, 28.0f, arg1);
                gfx = func_1517FB9C(gfx, w / 4, 0x20, 28.0f, 32.0f, arg1);
                if (D_800DDD78[arg1] < 2) {
                    D_800DDD78[arg1]++;
                } else {
                    D_800DDD78[arg1] = 0;
                }
            }
        }
    } else {
        gDPFillRectangle(gfx++,
            ((Struct15180580 *)D_800BE628)[arg1].unk2C,
            ((Struct15180580 *)D_800BE628)[arg1].unk24,
            ((Struct15180580 *)D_800BE628)[arg1].unk30,
            ((Struct15180580 *)D_800BE628)[arg1].unk28);
    }
    WGFX15180580(gfx++, 0xD9FFFFFF, 1);
    return gfx;
}
