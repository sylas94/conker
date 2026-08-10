/* Best candidate for func_1515E544 (game_18A8F0.c) -- SCORE 655, NOT a match.
 * Everything matches instruction-for-instruction up to 0x13a0; the only real
 * residual is that the target materialises a SECOND register holding 0x30
 * (`li t5,0x30`) for the two tail dmem-offset multiplies while this C reuses
 * the one already live in t0, and the second light-number increment lands in a
 * different scheduling slot.  The missing instruction shifts every later insn
 * by 4 bytes, which is what inflates the score.
 * Paste in place of the #pragma GLOBAL_ASM line at game_18A8F0.c:144. */

/* Conker's lights are 0x30 bytes each, not the stock 0x10-byte Light struct,
 * so gSPLight's (n)*24+24 dmem offset becomes (n)*48+48 here. */
#define CONKER_LIGHT_SIZE   0x30
#define gSPConkerLight(pkt, l, n)                                       \
    gDma2p((pkt), G_MOVEMEM, (l), CONKER_LIGHT_SIZE, G_MV_LIGHT,        \
           (u32)(((n) * CONKER_LIGHT_SIZE) + CONKER_LIGHT_SIZE))

Gfx *func_1515E544(Gfx *gfx, s32 arg1, u8 arg2, u8 arg3, s32 arg4) {
    s32 count;
    s32 extra;
    s32 i;
    s32 lightNo;

    count = arg3 & 0x7F;
    if (count != arg3) {
        extra = 1;
    } else {
        extra = 0;
    }

    gMoveWd(gfx++, G_MW_NUMLIGHT, G_MWO_NUMLIGHT, count * CONKER_LIGHT_SIZE);

    for (i = 0; i < count - extra - 1; i++) {
        gSPConkerLight(gfx++, ((D_800BE9C0 * arg2) + i) * CONKER_LIGHT_SIZE + arg1, i + 1);
    }
    lightNo = i;
    if (extra != 0) {
        gSPConkerLight(gfx++, &D_800DCD40, i + 1);
    }
    lightNo += extra;
    gSPConkerLight(gfx++, ((D_800BE9C0 * arg2) + i) * CONKER_LIGHT_SIZE + arg1, ++lightNo);
    gSPConkerLight(gfx++, arg4, ++lightNo);
    return gfx;
}
