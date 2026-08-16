/* func_1512DEA4 near-miss, best score 1575 (game_15B200.c).
 *
 * Everything matches byte-for-byte through the prologue, the sqrtf distance
 * block (incl. the 0x28(sp) home/reload of the third difference), the three
 * look-at stores, the frame size (0x68) and every sp-relative slot
 * (velX 0x54 / velY 0x58 / velZ 0x5C).
 *
 * ONLY residual: IDO globally allocates velY into $f2 across the switch,
 * whereas the target homes it to 0x58(sp) (`swc1 f10,0x58(sp)` at 1f0) and
 * reloads it at 2cc.  That single decision cascades into:
 *   - `lbu v0,0x870(s1)` scheduled early (1a8) instead of last (1f4)
 *   - plain `beqz` + store-in-delay-slot instead of `beqzl` + case-0 load
 *   - every FP register number in the four switch bodies and the post-switch
 *     accumulate block being rotated by one.
 * Permuter candidate.
 *
 * NOTE: the four `s32 padNN` locals exist purely to size the -g3 local area
 * to 16 words (frame 0x68).  With N named locals IDO produced
 * round_up_even(N + 7) words; 9 named => 16 words and the lone spill temp
 * lands at 0x28 exactly as the target.  They are the codebase's padNN idiom
 * but four of them is a smell -- if the real source shape is found, they go.
 */

#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern f32 D_800A3710;
extern f32 D_800A3714;
void func_150495B0(f32 *arg0, f32 arg1, f32 *arg2, f32 arg3, f32 arg4, f32 arg5);

typedef struct Func1512DEA4Camera {
    /* 0x00 */ u8  unk0;
    /* 0x01 */ u8  pad1[0x3];
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ f32 unk14;
    /* 0x18 */ f32 unk18;
    /* 0x1C */ f32 unk1C;
    /* 0x20 */ f32 unk20;
    /* 0x24 */ f32 unk24;
    /* 0x28 */ f32 unk28;
    /* 0x2C */ f32 unk2C;
    /* 0x30 */ f32 unk30;
    /* 0x34 */ f32 unk34;
    /* 0x38 */ f32 unk38;
    /* 0x3C */ f32 unk3C;
    /* 0x40 */ f32 unk40;
} Func1512DEA4Camera;

typedef struct Func1512DEA4Object {
    /* 0x000 */ u8  pad0[0x23C];
    /* 0x23C */ u8  unk23C;
    /* 0x23D */ u8  pad23D[0x2BC - 0x23D];
    /* 0x2BC */ f32 unk2BC;
    /* 0x2C0 */ f32 unk2C0;
    /* 0x2C4 */ f32 unk2C4;
    /* 0x2C8 */ u8  pad2C8[0x2F8 - 0x2C8];
    /* 0x2F8 */ f32 unk2F8;
    /* 0x2FC */ f32 unk2FC;
    /* 0x300 */ f32 unk300;
    /* 0x304 */ u8  pad304[0x3C0 - 0x304];
    /* 0x3C0 */ f32 unk3C0;
    /* 0x3C4 */ f32 unk3C4;
    /* 0x3C8 */ f32 unk3C8;
    /* 0x3CC */ u8  pad3CC[0x7B4 - 0x3CC];
    /* 0x7B4 */ f32 unk7B4;
    /* 0x7B8 */ u8  pad7B8[0x870 - 0x7B8];
    /* 0x870 */ Func1512DEA4Camera unk870;
    /* 0x8B4 */ u8  pad8B4[0x9A0 - 0x8B4];
} Func1512DEA4Object;

void func_1512DEA4(Func1512DEA4Object *arg0) {
    Func1512DEA4Camera *cam;
    f32 dist;
    f32 velZ;
    f32 velY;
    f32 velX;
    s32 pad50;
    s32 pad4C;
    s32 pad48;
    s32 pad44;

    dist = sqrtf(((arg0->unk870.unk4 - arg0->unk2BC) * (arg0->unk870.unk4 - arg0->unk2BC)) +
                 ((arg0->unk870.unk8 - arg0->unk2C0) * (arg0->unk870.unk8 - arg0->unk2C0)) +
                 ((arg0->unk870.unkC - arg0->unk2C4) * (arg0->unk870.unkC - arg0->unk2C4)));

    arg0->unk870.unk38 = arg0->unk870.unk4 + (arg0->unk870.unk10 * dist);
    arg0->unk870.unk3C = arg0->unk870.unk8 + (arg0->unk870.unk14 * dist);
    arg0->unk870.unk40 = arg0->unk870.unkC + (arg0->unk870.unk18 * dist);

    cam = &arg0->unk870;
    velY = arg0->unk870.unk24;

    switch (arg0->unk870.unk0) {
    case 0:
        velX = cam->unk20 * cam->unk18;
        velZ = cam->unk20 * -cam->unk10;
        break;
    case 1:
        velX = cam->unk20 * -cam->unk18;
        velZ = cam->unk20 * cam->unk10;
        break;
    case 2:
        velX = cam->unk20 * cam->unk10;
        velZ = cam->unk20 * cam->unk18;
        break;
    case 3:
        velX = cam->unk20 * -cam->unk10;
        velZ = cam->unk20 * -cam->unk18;
        break;
    }

    cam->unk38 += velX;
    cam->unk3C += velY;
    cam->unk40 += velZ;

    if (arg0->unk23C != 0) {
        arg0->unk2F8 = cam->unk38;
        arg0->unk2FC = cam->unk3C;
        arg0->unk300 = cam->unk40;
        cam->unk28 = 40.0f;
        cam->unk2C = 40.0f;
    } else {
        func_150495B0(&cam->unk28, 10.0f, &cam->unk30, 0.600000024f, D_800A3710, arg0->unk7B4);
        func_150495B0(&cam->unk2C, 10.0f, &cam->unk34, 0.600000024f, D_800A3714, arg0->unk7B4);
        func_150495B0(&arg0->unk2F8, cam->unk38, &arg0->unk3C0, cam->unk28, cam->unk2C, arg0->unk7B4);
        func_150495B0(&arg0->unk2FC, cam->unk3C, &arg0->unk3C4, cam->unk28, cam->unk2C, arg0->unk7B4);
        func_150495B0(&arg0->unk300, cam->unk40, &arg0->unk3C8, cam->unk28, cam->unk2C, arg0->unk7B4);
    }
}
