extern u8 D_160047E0[];
extern void func_16001B34(char *, const char *, ...);

void func_16000F8C(s32 arg0, f32 arg1) {
    f32 f;
    char buf[44];

    if ((arg0 >= (D_160038A0 << 5)) && (arg0 < 833)) {
        f = arg1;
        if ((((*(u32 *)&f & 0x7F800000) >> 23) == 0 || ((*(u32 *)&f & 0x7F800000) >> 23) >= 0xFF) &&
            (*(u32 *)&f << 1) != 0) {
            func_160012B0(arg0, D_160047D0);
            return;
        }
        func_16001B34(buf, D_160047D4, D_160047DC, D_160047E0, arg1);
        func_160012B0(arg0, buf);
    }
}
