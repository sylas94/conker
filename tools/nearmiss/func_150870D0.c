extern s8 D_800D23A8;
extern s8 D_8008FD90;
extern s32 D_800D2394;
extern u8 *D_800872A0;
extern void *allocate_memory(s32, s32, s32, s32);
u8 func_150888A8(u8, u8, s32);
void func_15088824();

typedef struct {
    /* 0x00 */ s16 unk0;
    /* 0x02 */ s16 unk2;
    /* 0x04 */ s16 unk4;
    /* 0x06 */ s16 unk6;
    /* 0x08 */ u8 unk8;
    /* 0x09 */ u8 link[5];
    /* 0x0E */ u8 unkE;
    /* 0x0F */ u8 unkF;
} Waypoint;

typedef struct {
    char pad0[0x26];
    /* 0x26 */ u8 unk26;
    char pad27[0x2B - 0x27];
    /* 0x2B */ u8 unk2B;
    /* 0x2C */ u8 unk2C;
    /* 0x2D */ u8 unk2D;
    /* 0x2E */ u8 unk2E;
    char pad2F[1];
    /* 0x30 */ u8 unk30;
    /* 0x31 */ u8 unk31;
    char pad32[0x84 - 0x32];
} Struct150870D0;

void func_150870D0(s32 arg0, s32 arg1, s32 arg2) {
    Waypoint *node;
    Waypoint *nb;
    Struct150870D0 *p;
    s32 i;
    s32 count;
    u8 idx;
    u8 found;
    u8 fwd;
    u8 rev;
    u8 best;
    u8 hop[3];
    s32 n;
    s32 offset;

    D_800872A0 = 0;
    idx = func_15086D48(arg0);
    if (idx == 0xFF) {
        return;
    }

    node = (Waypoint *)(idx * sizeof(Waypoint) + (s32)D_800D2350);
    best = D_800D23A8 * 0xFF;
    found = 0xFF;
    for (i = 0; i < 5; i++) {
        n = node->link[i];
        if (n == 0xFF) {
            continue;
        }
        nb = (Waypoint *)(n * sizeof(Waypoint) + (s32)D_800D2350);
        if (nb->unkE != 0) {
            continue;
        }
        if (((D_800D23A8 == 0) && (nb->unkF >= best)) || ((D_800D23A8 != 0) && (best >= nb->unkF))) {
            best = nb->unkF;
            found = n;
        }
    }

    if (found != 0xFF) {
        fwd = func_150888A8(idx, found, 0);
        rev = func_150888A8(found, idx, 0);
    }

    if ((found == 0xFF) || (rev == 0xFF) || (fwd == 0xFF)) {
        return;
    }

    hop[2] = fwd;
    count = 0;
    hop[1] = found;
    do {
        hop[0] = hop[1];
        hop[1] = hop[2];
        hop[2] = func_150888A8(hop[0], hop[1], 0);
        count++;
    } while (idx != hop[0]);

    D_800D2399 = arg2;
    D_800D2398 = arg1;
    D_800D2394 = 0;
    arg1 += arg2;
    D_800872A0 = allocate_memory(arg1 * 0x84, 1, 0, 0);
    offset = 0;
    for (i = 0; i < arg1; i++) {
        p = (Struct150870D0 *)(offset + D_800872A0);
        func_15088824(p);
        p->unk2B = rev;
        p->unk2C = idx;
        p->unk2D = found;
        p->unk2E = fwd;
        if (i < D_800D2398) {
            p->unk31 = i;
        }
        p->unk30 = (i >= D_8008FD90);
        p->unk26 = count;
        offset += sizeof(Struct150870D0);
    }
    D_800D239A = 1;
}
