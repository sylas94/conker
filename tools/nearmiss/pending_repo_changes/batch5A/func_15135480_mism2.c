typedef struct {
    u8 pad0[0x18];
    u8 unk18;
    u8 pad19[3];
    s32 unk1C;
    u8 pad20[0x30];
    u8 unk50;
} Obj15135480;

typedef struct {
    s32 unk0;
    union {
        s32 w;
        u8 b;
    } unk4;
    u8 unk8;
    u8 unk9;
} Msg15135480;

struct arg1_1513555C;
void func_1513555C(struct102 *arg0, struct arg1_1513555C *arg1, u8 arg2);
void func_151355B8(struct102 *arg0, struct arg1_1513555C *arg1, u8 arg2);

void func_15135480(Obj15135480 *arg0, Msg15135480 *arg1, u8 arg2) {
    s32 id;
    s32 cur;

    if (arg2 == 0x2D) {
        id = arg1->unk0;
        cur = arg0->unk1C;
        if (id == cur) {
            arg0->unk1C = arg1->unk4.w;
            arg0->unk18 = arg1->unk9;
        } else if (arg1->unk4.w == cur) {
            arg0->unk1C = id;
            arg0->unk18 = arg1->unk8;
        }
    }
    switch (arg0->unk50) {
    case 1:
        func_151355B8((struct102 *)arg0, (struct arg1_1513555C *)arg1, arg2);
        break;
    case 2:
        func_1513555C((struct102 *)arg0, (struct arg1_1513555C *)arg1, arg2);
        break;
    default:
        if (arg2 == 0) {
            cur = arg0->unk1C;
            if (arg1->unk0 == cur || arg0->unk18 == arg1->unk4.b) {
                func_1516972C((struct102 *)arg0);
            }
        }
        break;
    }
}
