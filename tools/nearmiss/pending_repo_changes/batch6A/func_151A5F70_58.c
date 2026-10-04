/* near-miss 58: loop + call body structurally exact; residue = param roles swapped: golden keeps arg1 (list) in s0
   and arg0 only in its home slot (reloaded as t7/t0); ours keeps arg0 in s0 and homes arg1. */
struct Inner151A5F70 {
    u8 pad0[0x14];
    u8 unk14;
};

struct Sub151A5F70 {
    struct Inner151A5F70 *unk0;
    u8 unk4;
    u8 pad5[3];
    s32 unk8;
    u8 unkC;
    u8 padD[3];
    s32 unk10;
};

struct Obj151A5F70 {
    u8 pad0;
    u8 unk1;
    u8 pad2[0xA];
    u8 unkC;
    u8 padD[0x1B];
    struct Sub151A5F70 unk28;
};

struct List151A5F70 {
    s32 unk0;
    u8 *unk4;
    s32 unk8;
};

void func_151A6068(struct Inner151A5F70 *, s32, u8, u8, u8, u8);

void func_151A5F70(struct Obj151A5F70 *arg0, struct List151A5F70 *arg1, u8 arg2) {
    s32 i;
    s32 found;
    u8 *p;
    struct Sub151A5F70 *s;

    if (arg2 == 0x35) {
        i = 0;
        found = 0;
        p = arg1->unk4;
        while (i < arg1->unk0 && !found) {
            if (*p == arg0->unk28.unk4) {
                found = 1;
            } else {
                i++;
                p++;
            }
        }
        if (found) {
            s = &arg0->unk28;
            if (s->unk0->unk14 == 1) {
                func_151A6068(s->unk0, s->unk8, s->unkC & 1, s->unkC & 2, arg0->unkC, arg0->unk1);
                s->unk0->unk14 = 0;
                s->unk10 = arg1->unk8;
            }
        }
    }
}
