/* PARKED BASELINE: score 20 (build #1). Residual = ALLOCATION, 4 instructions:
   golden  2350: lw t6,0(a2) / 2354: mflo t8   (addu t0,t8,t6  == offset + base)
   mine    2350: lw t8,0(a2) / 2354: mflo t6   (addu t0,t8,t6  == base + offset)
   same at 2370/2374 (t7/t9). Everything else byte-identical incl. frame 0x60.
*/
/* File-local shadow of struct178: the shared header types 0x06..0x33 as one u8 blob,
   which cannot express the s16/f32/u8/s32 members this search compares. */
typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ s16 unk8;
    /* 0x0A */ s16 unkA;
    /* 0x0C */ f32 unkC;
    /* 0x10 */ f32 unk10;
    /* 0x14 */ u8  unk14;
    /* 0x15 */ u8  unk15;
    /* 0x16 */ u8  unk16;
    /* 0x17 */ u8  unk17;
    /* 0x18 */ s32 unk18;
    /* 0x1C */ s32 unk1C;
    /* 0x20 */ s32 unk20;
    /* 0x24 */ u8  unk24[0x10];
} ObjRec; /* size 0x34 */

#define OBJTBL ((ObjRec *) *(s32 *) &D_800D3098)

void func_15143D18(s32 *, s32 *, s32, s32);

ObjRec *func_151438D8(s32 arg0, s32 arg1, u16 arg2, ObjRec *arg3) {
    s32 i;
    ObjRec *result;
    u16 checked;
    u16 matched;

    result = NULL;
    if (arg3 == NULL) {
        return NULL;
    }
    func_15143D18(&arg0, &arg1, 0, D_800D3094);
    for (i = arg0; i < arg1; i++) {
        checked = 0;
        matched = 0;
        if (arg2 & 0x1) {
            if ((arg3->unk0 == OBJTBL[i].unk0) && (arg3->unk2 == OBJTBL[i].unk2) && (arg3->unk4 == OBJTBL[i].unk4)) {
                checked |= 0x1;
                matched |= 0x1;
            }
        } else {
            checked |= 0x1;
        }
        if (arg2 & 0x2) {
            if ((arg3->unk6 == OBJTBL[i].unk6) && (arg3->unk8 == OBJTBL[i].unk8) && (arg3->unkA == OBJTBL[i].unkA)) {
                checked |= 0x2;
                matched |= 0x2;
            }
        } else {
            checked |= 0x2;
        }
        if (arg2 & 0x4) {
            if (arg3->unkC == OBJTBL[i].unkC) {
                checked |= 0x4;
                matched |= 0x4;
            }
        } else {
            checked |= 0x4;
        }
        if (arg2 & 0x8) {
            if (arg3->unk10 == OBJTBL[i].unk10) {
                checked |= 0x8;
                matched |= 0x8;
            }
        } else {
            checked |= 0x8;
        }
        if (arg2 & 0x10) {
            if (arg3->unk14 == OBJTBL[i].unk14) {
                checked |= 0x10;
                matched |= 0x10;
            }
        } else {
            checked |= 0x10;
        }
        if (arg2 & 0x20) {
            if (arg3->unk15 == (OBJTBL[i].unk15 >> 2)) {
                checked |= 0x20;
                matched |= 0x20;
            }
        } else {
            checked |= 0x20;
        }
        if (arg2 & 0x40) {
            if (arg3->unk16 == OBJTBL[i].unk16) {
                checked |= 0x40;
                matched |= 0x40;
            }
        } else {
            checked |= 0x40;
        }
        if (arg2 & 0x80) {
            if (arg3->unk17 == OBJTBL[i].unk17) {
                checked |= 0x80;
                matched |= 0x80;
            }
        } else {
            checked |= 0x80;
        }
        if (arg2 & 0x100) {
            if (arg3->unk18 == OBJTBL[i].unk18) {
                checked |= 0x100;
                matched |= 0x100;
            }
        } else {
            checked |= 0x100;
        }
        if (arg2 & 0x200) {
            if (arg3->unk1C == OBJTBL[i].unk1C) {
                checked |= 0x200;
                matched |= 0x200;
            }
        } else {
            checked |= 0x200;
        }
        if (arg2 & 0x400) {
            if (arg3->unk20 == OBJTBL[i].unk20) {
                checked |= 0x400;
                matched |= 0x400;
            }
        } else {
            checked |= 0x400;
        }
        if (arg2 & 0x1000) {
            if (checked == 0x7FF) {
                result = &OBJTBL[i];
            }
        } else {
            if (matched != 0) {
                result = &OBJTBL[i];
