extern f32 D_80096900;
extern f32 D_80096904;

void func_1501B22C(s32 arg0) {
    struct259 *s;
    f32 a;
    f32 c;
    f32 sn;
    f32 b;

    s = &((struct259 *)D_800BE628)[arg0];
    a = s->unk74 * 0.5f;
    b = s->unk78 * 0.5f;
    {
        f32 ang = -a * D_80096900;

        c = cosf(ang);
        sn = sinf(ang);
    }
    s->unk9C = sn;
    s->unk90 = sn;
    s->unk94 = -c;
    s->unk88 = -s->unk94;
    s->unk98 = 0.0f;
    s->unk8C = 0.0f;
    {
        f32 ang = b * D_80096904;

        c = cosf(ang);
        sn = sinf(ang);
    }
    s->unkA0 = 0.0f;
    s->unkA8 = -sn;
    s->unkB4 = -sn;
    s->unkAC = 0.0f;
    s->unkA4 = -c;
    s->unkB0 = -s->unkA4;
}
