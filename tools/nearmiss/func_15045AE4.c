struct conker15045AE4_ent {
    s32 unk0;
    s16 **unk4;
    s32 unk8;
    s32 unkC;
};

struct conker15045AE4_obj {
    u8 pad0[0x40];
    s32 unk40;
    s32 *unk44;
    u8 pad48[0x10];
    u16 unk58;
    u8 pad5A[0x46];
};

struct conker15045AE4_dst {
    f32 unk0;
    s16 unk4[3][3];
    u8 pad16[2];
    s32 unk18;
    u8 unk1C;
    u8 unk1D;
    u8 pad1E[2];
    s32 unk20;
};

extern f32 D_80098D54;
extern s32 D_800D37E0;
extern void func_150A44F0(s32, s32 *, s32);
extern s32 func_150A43E0(s32, s32, s32, s32 *);

s32 func_15045AE4(struct conker15045714 *arg0, f32 arg1, s32 *arg2, struct conker15045AE4_dst *arg3) {
    s32 best;
    struct conker15045AE4_ent *ents;
    struct conker15045AE4_ent *ent;
    struct conker15045AE4_obj *obj;
    s16 **verts;
    s16 *vtx;
    s32 offset;
    s32 count;
    s32 i;
    s32 j;
    s32 idx;
    f32 height;

    best = -1;
    arg3->unk0 = D_80098D54;
    func_150A44F0(*arg2, &D_800D37E0, 0);
    count = func_150A43E0((s32)arg0->field_0x00, (s32)arg0->field_0x08, *arg2, &D_800D37E0);

    ents = (struct conker15045AE4_ent *)&D_800D3300;
    for (i = 0; i < count; i++) {
        height = (f32)ents[i].unk0 * 0.00390625f;
        if (height <= arg0->field_0x04) {
            if (arg3->unk0 < height) {
                best = i;
                arg3->unk0 = height;
            }
        }
    }

    if (best != -1) {
        ent = &ents[best];
        verts = ent->unk4;
        offset = ent->unk8;
        for (j = 0; j != 3; j++) {
            vtx = (s16 *)((u8 *)verts[j] + offset);
            arg3->unk4[j][0] = vtx[0];
            arg3->unk4[j][1] = vtx[1];
            arg3->unk4[j][2] = vtx[2];
        }

        obj = (struct conker15045AE4_obj *)&D_800DBEF4[ent->unkC];
        arg3->unk20 = (s32)obj;
        if (obj->unk44 != 0) {
            idx = (((s32)verts - D_800DBE3C) / 12) - obj->unk58;
            arg3->unk18 = obj->unk44[idx];
        } else {
            arg3->unk18 = obj->unk40;
        }
        arg3->unk1C |= 6;
        if ((D_800DBEF4[ent->unkC].unk6F & 0x80) == 0x80) {
            arg3->unk1C |= 1;
        }
        arg3->unk1D = 2;

        if (arg1 <= arg3->unk0) {
            arg3->unk1C |= 2;
            return 1;
        }
        return 0;
    }

    arg3->unk1C &= ~2;
