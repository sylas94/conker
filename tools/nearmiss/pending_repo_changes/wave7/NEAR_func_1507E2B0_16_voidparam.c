typedef struct {
    u8 pad0[0x120];
    u8 unk120;
} Struct1507E2B0Sub;

typedef struct {
    u8 pad0[0x4];
    u8 unk4;
    u8 pad5[0x65];
    u8 unk6A;
    u8 unk6B;
    u8 unk6C;
    u8 pad6D;
    u8 unk6E;
    u8 pad6F[0xB8];
    u8 unk127;
    u8 pad128[0x1F4];
    Struct1507E2B0Sub *unk31C;
} Struct1507E2B0;

void func_1507E2B0(void *arg) {
    Struct1507E2B0 *arg0 = arg;
    u8 t;
    s32 dt;


    if (arg0->unk4 == 0x2B) {
        return;
    }
    if (D_800C35EA == 1) {
        return;
    }
    if (arg0->unk127 != 0xFF && arg0->unk31C->unk120 != 0) {
        arg0->unk6A = 1;
        arg0->unk6B = 1;
        return;
    }
    if (arg0->unk6A >= 3) {
        arg0->unk6A = 0;
    }
    if (arg0->unk6B >= 3) {
        arg0->unk6B = 0;
    }
    t = arg0->unk6E;
    dt = D_800BE9E4;
    if (t >= dt) {
        arg0->unk6E = t - dt;
        return;
    }
    arg0->unk6E = 0;
    if (arg0->unk6C == 1) {
        return;
    }
    arg0->unk6A ^= 1;
    arg0->unk6B ^= 1;
    if (arg0->unk6A == 0) {
        arg0->unk6E = (u32)func_150ADA20() % 140 + 10;
    } else {
        arg0->unk6E = 1;
    }
}
