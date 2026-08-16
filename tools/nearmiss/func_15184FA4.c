/* func_15184FA4  (game_1B1600.c)  -- PARKED at score 15 (base: 100% asm = pragma)
 *
 * Cold decompile, wave "actor-array consumers".  305 asm instructions, 0 mul, 0 fp.
 * Progress:  build #1 = 150  ->  removed the `obj` local (frame 0xE0 -> 0xD8) = 31
 *            -> reversed the colours[] store order = 15.
 * Residual: THREE instructions, all register-name only ('r' marks), at the
 *           gSPViewport display-list slot:
 *                golden:  move a3,s0 / sw t6,0(a3) / sw t7,4(a3)
 *                mine:    move a2,s0 / sw t6,0(a2) / sw t7,4(a2)
 *           Everything else in the function is byte-identical.
 *
 * The `Gfx *_g` block-locals inside the gbi.h macros are allocated round-robin
 * over {v0,v1,a0,a1,a2,a3}.  Golden's sequence is v0,v1,a0,a1,[a3],v0,v1 (a2
 * skipped); mine is v0,v1,a0,a1,[a2],v0,v1 (a3 skipped).  Both then wrap to v0,
 * so it is NOT a persistent counter offset -- exactly one of the two argument
 * registers a2/a3 is treated as busy at that allocation and the choice differs.
 * a2 is provably DEAD there in golden (next a2 access is the write at 151851FC),
 * so plain liveness does not explain it.
 *
 * MEASURED NEGATIVES (all vs the base below; every sweep carried a CONTROL that FIRED,
 * so the "identical score" readings are evidence, not a broken harness):
 *   - `struct127 *obj = &D_800CC2D0[arg1];` as a declared local: 31 (frame 0xE0,
 *     4 bytes too many of home area; golden's locals are exactly count + colours[3]
 *     = 16 bytes, so the record pointer is a CSE, not a declared local).
 *   - colours[0]=0; colours[1]=0; colours[2]=0;  : 31 (stores come out
 *     0xC8,0xCC,0xD0; golden is 0xD0,0xCC,0xC8 -> source order is reversed).
 *
 *   SWEEP 1  (control: gDPSetOtherMode mode1 0x0F0A4000 -> ...4001 moved 15 -> 20)
 *     (s32) cast on the gSPPerspNormalize value ................... 15  (a2)
 *     `extern Vp D_8008D3E8[];` + array decay instead of &......... 15  (a2)
 *     raw gDma2p(...G_MOVEMEM...) instead of gSPViewport .......... 15  (a2)
 *     raw gMoveWd(...G_MW_PERSPNORM...) instead of gSPPerspNorm ... 15  (a2)
 *     arg2 typed u32 instead of s32 ............................... 15  (a2)
 *   SWEEP 2  (control: `count < 2` -> `count < 3` moved 15 -> 20)
 *     count as a ternary instead of if/else ....................... 15  (a2)
 *     colours as a 3-field struct instead of an array ............. 15  (a2)
 *     pass &colours[0] instead of colours ......................... 15  (a2)
 *     `count <= 1` instead of `count < 2` ......................... 15  (a2)
 *     FRAME-NEUTRAL PROBE: colours[2] + a declared struct127 *obj . 120 (a2)
 *   The probe deliberately wrecked the code (120) and the viewport register STILL
 *   came out a2, so the pick is insensitive to the local set, to the count
 *   computation and to every spelling of the two statements involved.  Whatever
 *   selects a3 in golden is structural (most likely the function SIGNATURE or an
 *   argument-register reservation) and is NOT reachable from this source shape.
 *
 * PERMUTER: tools/decomp-permuter via conker/permuter_tu.sh is set up for this
 * function but its MANDATORY selftest FAILS check (b2): the pycparser round-trip
 * changes codegen (roundtrip disasm sha1 0e5c6d69... vs harness/makefile
 * e59981ab...), so its scores would be measured on a different source.  Checks
 * (a) reassembly, (b) harness==makefile bytes, (c) positive and (d) negative
 * control all PASS.  NOTE for whoever retries: IDO's `cc` CANNOT WRITE AN OUTPUT
 * PATH CONTAINING A SPACE, so the default dir `conker/permuter_tu/<func>` (under
 * ".../conker decomp/...") always fails with a bare FileNotFoundError on the .o.
 * Create the dir somewhere space-free instead:
 *     ./permuter_tu.sh setup game_1B1600 func_15184FA4 <cand.c> ~/permtu/func_15184FA4
 *
 * Decoding notes that are settled (do not re-derive):
 *   0xFF48003F -> gDPSetColorImage(G_IM_FMT_CI, G_IM_SIZ_8b, 64, D_800DF088)
 *   0xDB0E.... -> gSPPerspNormalize(D_800DF0D0[arg2])   (G_MW_PERSPNORM = 0x0E)
 *   0xDC080008 -> gSPViewport(&D_8008D3E8)              (gDma2p, sizeof(Vp)=16)
 *   0xDA380007 -> gSPMatrix(..., G_MTX_PROJECTION|G_MTX_LOAD|G_MTX_NOPUSH)
 *   0xDA380003 -> gSPMatrix(&D_89470, G_MTX_MODELVIEW|G_MTX_LOAD|G_MTX_NOPUSH)
 *   D_89470 is undefined_syms_auto.txt  D_89470 = 0x89470  (lui/addiu = reloc,
 *   a plain integer constant would have come out as lui/ori).
 *   The FD/F5/E6/F3/E7/F5/F2 run is exactly gDPLoadTextureBlock's expansion:
 *     I / 8b / 64x64 / masks=maskt=6 / dxt 0x100 == CALC_DXT(64,1).
 *   Frame 0xD8 = arg-build 0x20 + saved(s0,s1,ra) 0x24..0x2F + temps + locals
 *   (count @ 0xD4, colours[3] @ 0xC8..0xD3, ending at framesize).
 */

extern s32 D_800DF088;
extern u16 D_800DF0D0[];
extern Mtx D_800DF2F8[][2];
extern Vp D_8008D3E8;
extern Gfx D_8008D448;
extern Mtx D_89470;
extern s16 D_80082FA6;
extern s32 func_1502CCFC(s32, s32, s32, void *, s32, s32 *, s32, s32);
extern s32 func_1506196C(struct127 *, s32);
Gfx *func_1501A680(Gfx *arg0);
Gfx *func_1510B7B4(Gfx *arg0, s32 arg1);

Gfx *func_15184FA4(Gfx *gfx, s32 arg1, s32 arg2, s32 arg3) {
    s32 count;
    s32 colours[3];

    if (D_800CC2D0[arg1].unk127 == 0xFF) {
        count = D_800CC2D0[arg1].pad1C8 + 1;
    } else {
        count = D_800CC2D0[arg1].pad1C8;
    }

    gDPPipeSync(gfx++);
    gDPSetColorImage(gfx++, G_IM_FMT_CI, G_IM_SIZ_8b, 64, D_800DF088);
    gSPDisplayList(gfx++, &D_8008D448);
    gSPPerspNormalize(gfx++, D_800DF0D0[arg2]);
    gSPViewport(gfx++, &D_8008D3E8);
    gSPMatrix(gfx++, &D_800DF2F8[arg2][D_800BE9C0], G_MTX_PROJECTION | G_MTX_LOAD | G_MTX_NOPUSH);
    gSPMatrix(gfx++, &D_89470, G_MTX_MODELVIEW | G_MTX_LOAD | G_MTX_NOPUSH);

    colours[2] = 0;
    colours[1] = 0;
    colours[0] = 0;
    gfx = (Gfx *)func_1502CCFC((s32)gfx, arg1, arg3, D_800CC2D0[arg1].unk1D4,
                               func_1506196C(&D_800CC2D0[arg1], arg3), colours, 3, 1);

    gSPTexture(gfx++, 0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON);
    gDPPipeSync(gfx++);
    if (count < 2) {
        gDPSetCombine(gfx++, 0xFFFFFF, 0xFFFCF87C);
        gDPSetPrimColor(gfx++, 0, 0, 0xFF, 0xFF, 0xFF, 0xFF);
        gDPSetOtherMode(gfx++, 0x003C3F, 0x0F0A4000);
        gDPLoadTextureBlock(gfx++, D_800DF088, G_IM_FMT_I, G_IM_SIZ_8b, 64, 64, 0,
                            G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR, 6, 6,
                            G_TX_NOLOD, G_TX_NOLOD);
        gSPTextureRectangle(gfx++, 0, 0, 0xFC, 0xFC, G_TX_RENDERTILE, 0x10, 0x10, 0x400, 0x400);
        if (count == 0) {
            gDPPipeSync(gfx++);
            gDPLoadTextureBlock(gfx++, D_800DF088, G_IM_FMT_I, G_IM_SIZ_8b, 64, 64, 0,
                                G_TX_WRAP | G_TX_NOMIRROR, G_TX_WRAP | G_TX_NOMIRROR, 6, 6,
                                G_TX_NOLOD, G_TX_NOLOD);
            gSPTextureRectangle(gfx++, 0, 0, 0xFC, 0xFC, G_TX_RENDERTILE, 0x10, 0x10, 0x400, 0x400);
        }
        gDPPipeSync(gfx++);
    }
    gSPSetGeometryMode(gfx++, G_ZBUFFER | G_SHADING_SMOOTH);
    gfx = (Gfx *)func_1501A490((s32)func_1501A680(gfx), D_80082FA6, 0, 0, 0, 0);
    gfx = func_1510B7B4(gfx, arg3);
    D_800CC2D0[arg1].unk123 = 1;
    return gfx;
}
