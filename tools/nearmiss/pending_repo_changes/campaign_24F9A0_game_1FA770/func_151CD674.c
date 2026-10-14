/* score 0 with literals; ships only when rodata block 0x24F9A0 migrates (all 13 owners in C) */
typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    u8 pad10[0xC];
} Pt151CD674;

typedef struct {
    u8 pad0[0x44];
    f32 unk44;
} Info151CD674;

typedef struct {
    f32 x, y, z;
} Vec151CD674;

typedef struct {
    u8 pad0[0x10];
    Vec151CD674 unk10;
    u8 pad1C[2];
    u16 unk1E;
    u8 pad20[5];
    u8 unk25;
    u8 pad26[6];
    s8 unk2C;
    s8 unk2D;
    s8 unk2E;
    u8 pad2F[0x25];
    Vec151CD674 unk54;
    u8 pad60[0x34];
    Pt151CD674 *unk94;
    Info151CD674 *unk98;
} Obj151CD674;

extern f32 D_800AAFC0;
extern f32 D_800AAFC4;

s32 func_151CD674(Obj151CD674 *arg0) {
    Info151CD674 *info = arg0->unk98;
    Pt151CD674 *pts = arg0->unk94;
    s32 i;
    Pt151CD674 *p;

    if ((arg0->unk2C < 2) && (arg0->unk1E & 8)) {
        return 0;
    }
    i = arg0->unk2E;
    if (i != arg0->unk2D) {
        do {
            i--;
            if (i < 0) {
                i = arg0->unk25 - 1;
            }
            p = &pts[i];
            p->unk4 += (p->unkC * D_800BE9A4) + (-0.12750001f * (D_800BE9A4 * D_800BE9A4));
            p->unkC += -0.25500003f * D_800BE9A4;
            if (p->unk4 < info->unk44) {
                while (i != arg0->unk2D) {
                    arg0->unk2D++;
                    if (arg0->unk2D == arg0->unk25) {
                        arg0->unk2D = 0;
                    }
                    arg0->unk2C--;
                }
                pts[arg0->unk2D].unk4 = info->unk44;
            }
        } while (i != arg0->unk2D);
    }
    arg0->unk54 = arg0->unk10;
    return 1;

}
