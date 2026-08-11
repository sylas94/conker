typedef struct {
    /* 0x00 */ s32 unk0;
    /* 0x04 */ s32 unk4;
    /* 0x08 */ s32 unk8;
    /* 0x0C */ u32 unkC;
    /* 0x10 */ s32 unk10;
    /* 0x14 */ s32 unk14;
    /* 0x18 */ OSTask_t list;
    /* 0x58 */ OSMesgQueue *msgQ;
    /* 0x5C */ void *msg;
} SchedTask1501C880; /* 0x60 */

typedef struct {
    u8 unk0[0x20];
} SchedMsg1501C880;

extern u8 D_800BE9C0;
extern s32 D_800BE9C8[];
extern SchedTask1501C880 *D_800BEAD4;
extern SchedTask1501C880 D_800BEAD8[];
extern u8 D_800BEBA0;
extern u64 *D_800BEB9C;
extern u64 *D_800BEAD0;
extern u64 D_800BEBB0[];
extern u64 D_800C1060[];
extern u64 D_800CBE10[];
extern u64 D_8003A5E8[];
extern s32 D_100291A0;
extern void func_1501A39C(void);
extern void func_1501CC3C(void);

#define WGFX1501C880(a, b)              \
{                                       \
    Gfx *_g = (Gfx *)D_800BE9D0;        \
    D_800BE9D0 += 8;                    \
    _g->words.w0 = (u32)(a);            \
    _g->words.w1 = (u32)(b);            \
}

void func_1501C880(s32 arg0, s32 arg1) {
    s32 limit;
    s32 count;

    arg0 = arg0;
    limit = (D_800BE9C8[1] - D_800BE9C8[0]) >> 3;
    D_800BEAD4 = &D_800BEAD8[D_800BE9C0];
    D_800BEAD4->unk0 = 0;
    count = (D_800BE9D0 - D_800BE9C8[D_800BE9C0]) >> 3;
    if ((count < 0) || (count > limit)) {
        func_1501A39C();
        D_800BE9D0 = D_800BE9D8[D_800BE9C0];
        WGFX1501C880(0xE9000000, 0);
        WGFX1501C880(0xDF000000, 0);
        count = (D_800BE9D0 - D_800BE9C8[D_800BE9C0]) >> 3;
    }

    if ((count < 0) || (count > (limit - 400))) {
        D_800BE9D0 = D_800BE9C8[D_800BE9C0] + ((limit - 400) << 3);
        WGFX1501C880(0xE9000000, 0);
        WGFX1501C880(0xDF000000, 0);
    }

    D_800BEAD4->list.data_ptr = (u64 *)D_800BE9C8[D_800BE9C0];
    D_800BEAD4->list.data_size = (D_800BE9D0 - D_800BE9C8[D_800BE9C0]) >> 3 << 3;
    func_1501CC3C();

    D_800BEAD4->list.type = 1;
    D_800BEAD4->list.flags = 4;
    D_800BEAD4->list.ucode_boot = (u64 *)&D_100290D0;
    D_800BEAD4->list.ucode_boot_size = (s32)&D_100291A0 - (s32)&D_100290D0;
    if (D_800BEBA0 != 0) {
        D_800BEAD4->list.ucode = D_800C1060;
        D_800BEAD4->list.ucode_data = D_800BEB9C;
    } else {
        D_800BEAD4->list.ucode = D_800BEBB0;
        D_800BEAD4->list.ucode_data = D_800BEAD0;
    }
    D_800BEAD4->list.ucode_data_size = 0x800;
    D_800BEAD4->list.dram_stack = D_800CBE10;
    D_800BEAD4->list.dram_stack_size = 0x400;
    D_800BEAD4->list.output_buff = (u64 *)D_80038090;
    D_800BEAD4->list.output_buff_size = (u64 *)D_80038094;
    D_800BEAD4->list.yield_data_ptr = D_8003A5E8;
    D_800BEAD4->list.yield_data_size = 0xC00;
    D_800BEAD4->unkC = 0x23;
    if (arg1 != 0) {
        D_800BEAD4->unkC |= 0x40;
    }
    if (D_800BE617 != 0) {
        D_800BEAD4->unkC |= (D_80082FA0 + 1) << 16;
        D_800BE617 = 0;
    }
    D_800BEAD4->msgQ = &D_800BEA10;
    D_800BEAD4->msg = &((SchedMsg1501C880 *)&D_800BEA68)[D_800BE9C0];
    D_800BEAD4->unk10 = D_8002AAE8[D_800BE9C0];
    osWritebackDCacheAll();
    osSendMesg(&D_8003B1E8, D_800BEAD4, 1);
    if (arg1 != 0) {
        D_800BE9C0 ^= 1;
    }
    *(s16 *)&D_800BEAA8 = *(s16 *)&D_800BEAA8 + 1;
}
