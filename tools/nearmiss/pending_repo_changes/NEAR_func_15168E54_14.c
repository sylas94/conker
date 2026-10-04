void func_15168E54(Struct15168F08 *arg0, s32 arg1) {
    s32 i;
    Struct15168F08 *p;
    s32 tag;

    i = 0;
    p = arg0;
    if (arg0->unk0 == -0x21) {
        return;
    }
    tag = arg0->unk0;
    do {
        if ((tag == 1) || ((tag == -0x24) && (p->unk3 == 0xE))) {
            func_15168E34((s32 *)&p->unk4, arg1);
        }
        i++;
        p = &arg0[i];
        tag = p->unk0;
    } while (tag != -0x21);
}
