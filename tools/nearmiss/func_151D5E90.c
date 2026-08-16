/* func_151D5E90 near-miss, honest score 1500 (no forcers).
 * Full command semantics recovered; residual = frame size 0x50 vs 0x98
 * (target has ~26 word-sized function-scope locals; only 8 are justifiable)
 * plus a register-allocation cascade (x -> t1 vs a2, y2 -> a2 vs a3,
 * width -> s1 vs s2, sliceW -> s2 vs s0) and the two global loads being
 * scheduled after the 5 setup commands instead of at the top of the block.
 *
 * With 18 extra (unused, therefore BANNED) locals inserted so the frame
 * becomes 0x98 with height at 0x8C, sliceH at 0x84 and y2 at 0x34 -- the
 * exact spill offsets the target uses -- the score drops to 1066.
 * Good decomp-permuter candidate.
 */
Gfx *func_151D5E90(Gfx *gfx, void *timg, s32 arg2, s32 arg3) {
    u32 width;
    u32 height;
    u32 sliceW;
    u32 sliceH;
    u32 x;
    u32 y;
    u32 y2;
    u32 x2;

    gDPPipeSync(gfx++);
    gDPSetCombineMode(gfx++, G_CC_DECALRGBA, G_CC_DECALRGBA);
    gDPSetOtherMode(gfx++, 0x000CFF, 0x0F0A4000);
    gSPLoadGeometryMode(gfx++, 0);
    gSPTexture(gfx++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);

    width = D_800BE620;
    height = D_800BE624;
    sliceH = 16;
    for (y = 0; y < height; y = y2) {
        y2 = y + sliceH;
        if (y2 > height) {
            sliceH = height - y;
            y2 = y + sliceH;
        }
        x = 0;
        sliceW = 128;
        while (x < width) {
            x2 = x + sliceW;
            if (x2 > width) {
                sliceW = width - x;
                x2 = x + sliceW;
            }
            gDPLoadTextureTile(gfx++, timg, G_IM_FMT_RGBA, G_IM_SIZ_16b, width, 0,
                               x, y, x2 - 1, y2 - 1, 0,
                               G_TX_NOMIRROR, G_TX_NOMIRROR, G_TX_NOMASK, G_TX_NOMASK,
                               G_TX_NOLOD, G_TX_NOLOD);
            gSPTextureRectangle(gfx++, x << 2, y << 2, x2 << 2, y2 << 2,
                                G_TX_RENDERTILE, x << 5, y << 5, 1 << 10, 1 << 10);
            gDPPipeSync(gfx++);
            x = x2;
        }
    }
    gDPSetOtherMode(gfx++, 0x080C3F, 0x0F0A4000);
    return gfx;
}
