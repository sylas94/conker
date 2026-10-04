extern void *allocate_memory(s32, s32, s32, s32);
extern void func_10004074(void *);
extern u8 D_1A37E0[];

void func_15003570(void) {
    u8 *buf;
    s32 addr;
    s32 adj;
    s32 i;
    u8 *p;
    u32 val;

    buf = allocate_memory(0x10, 1, 2, 0);
    addr = (s32)D_1A37E0;
    for (i = 0; i < 7762; i++) {
        if (addr & 1) {
            addr -= 1;
            adj = 1;
        } else {
            adj = 0;
        }
        func_10004514(addr, buf, 0x10, 1);
        p = adj + buf;
        val = (p[0] << 24) + (p[1] << 16) + (p[2] << 8) + p[3];
        ((u16 *)D_800B87A0)[i] = val;
        addr += ((u16 *)D_80091D20)[i] + adj;
    }
    func_10004074(buf);
}
