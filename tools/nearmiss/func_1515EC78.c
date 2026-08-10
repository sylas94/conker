/* func_1515EC78 near-miss, SCORE 360 (3 instructions out of 191).
 * Everything matches byte-for-byte except the len==0.0f fallback block:
 *   target:  [shadow mtc1 zero,f14] lui at,0x42fe ; mtc1 at,f2 ; mov.s f12,f14
 *   ours:    [shadow mtc1 zero,f14] mtc1 zero,f12 ; mtc1 at,f2 ; nop
 *            + one extra "lui at,0x42fe" inside the divide branch, because the
 *              hoisted lui at 0x18fc gets owned by the else block instead of the
 *              divide block.
 * IDO constant-folds every spelling of the 0.0f copy (ny = nz, ny = nz = 0.0f,
 * plain 0.0f) into a fresh mtc1 zero, so the target's mov.s f12,f14 is not
 * reachable from C.  Stack layout / frame size / all other 188 instructions match.
 *
 * Named-local budget that reproduces the exact frame (0x80) and offsets:
 *   frame = roundup8(0x44 + namedSize); named block sits at 0x44 upward,
 *   first-declared local = highest address.  namedSize must be 56..60:
 *     p(4) v[3](12) nx,ny,nz,len(16) col[3](12) pos[3](12) i(4)
 *   -> v[3]@0x70, nx/ny/nz/len@0x6C..0x60, col@0x54, pos@0x48, i@0x44,
 *      compiler temps: mask spill@0x40, dy@0x3C, dz@0x38.
 */

struct Light1515EC78 {
    u8 pad0[5];
    u8 unk5[3];
    u8 pad8[6];
    s16 unkE;
    s16 unk10;
    s16 unk12;
    s16 unk14[4][3];
    u8 pad2C[3];
    u8 unk2F;
    u8 unk30;
};

struct LightOut1515EC78 {
    u8 unk0[3];
    u8 pad3;
    u8 unk4[3];
    u8 pad7;
    u8 unk8[3];
    u8 padB;
    u8 unkC;
    u8 padD[0x13];
    s16 unk20[3];
    s16 pad26;
    s16 unk28[3];
};

extern f32 D_800D9C10[][4][4];
void func_150A7960(f32 *, f32, f32, f32, f32 *, f32 *, f32 *);

void func_1515EC78(struct Light1515EC78 *arg0, s32 arg1, struct LightOut1515EC78 *arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6) {
    f32 *p;
    f32 v[3];
    f32 nx;
    f32 ny;
    f32 nz;
    f32 len;
    s32 col[3];
    s32 pos[3];
    s32 i;

    pos[0] = arg0->unkE;
    if (pos[0] != -0x8000) {
        pos[1] = arg0->unk10;
        pos[2] = arg0->unk12;
    } else {
        p = (f32 *)((arg0->unk12 & 0xFFFF) | (arg0->unk10 << 16));
        pos[0] = (s32)p[0];
        pos[1] = (s32)p[1];
        pos[2] = (s32)p[2];
    }

    if (arg6 & 2) {
        nx = (f32)(pos[0] - arg3);
        ny = (f32)(pos[1] - arg4);
        nz = (f32)(pos[2] - arg5);
        len = sqrtf((nx * nx) + (ny * ny) + (nz * nz));
        if (len != 0.0f) {
            len = 127.0f / len;
            nx = nx * len;
            ny = ny * len;
            nz = nz * len;
        } else {
            ny = nz = 0.0f;
            nx = 127.0f;
        }
        col[0] = (s32)nx;
        col[1] = (s32)ny;
        col[2] = (s32)nz;
    } else {
        col[0] = 0;
        col[1] = 0;
        col[2] = 127;
    }

    if (arg0->unk30 & (1 << arg1)) {
        pos[0] = arg0->unk14[arg1][0];
        pos[1] = arg0->unk14[arg1][1];
        pos[2] = arg0->unk14[arg1][2];
    } else {
        func_150A7960(D_800D9C10[arg1][0], (f32)pos[0], (f32)pos[1], (f32)pos[2], &v[0], &v[1], &v[2]);
        pos[0] = (s32)v[0];
        pos[1] = (s32)v[1];
        pos[2] = (s32)v[2];
        arg0->unk14[arg1][0] = pos[0];
        arg0->unk14[arg1][1] = pos[1];
        arg0->unk14[arg1][2] = pos[2];
        arg0->unk30 |= 1 << arg1;
    }

    for (i = 0; i < 3; i++) {
        arg2->unk0[i] = arg0->unk5[i];
        arg2->unk4[i] = arg0->unk5[i];
        arg2->unk8[i] = col[i];
        arg2->unk20[i] = pos[i];
        arg2->unk28[i] = pos[i];
    }
    arg2->unkC = arg0->unk2F;
}
