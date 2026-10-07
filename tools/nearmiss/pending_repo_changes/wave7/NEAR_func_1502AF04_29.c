typedef struct {
    s32 unk0;
    s32 unk4;
} Reloc1502AF04;

s32 func_1502AF04(u8 *arg0, s32 arg1, s32 arg2, u32 arg3) {
    u8 *dst;
    u32 i;
    u32 size;

    arg2 *= 8;
    dst = (u8 *)((u32)(arg1 + 8) & ~0xF);
    size = (((u32)(arg0 + arg2) & 0xE) + arg3 * 8 + 0xF) & ~0xF;
    func_10004514((u32)(arg0 + arg2) & ~0xF, dst, size, 1);
    for (i = 0; i < arg3; i++) {
        ((Reloc1502AF04 *)((u32)dst + ((u32)(arg0 + arg2) & 0xF)))[i].unk0 += (s32)arg0;
    }
    return (u32)dst + ((u32)(arg0 + arg2) & 0xF);
}
