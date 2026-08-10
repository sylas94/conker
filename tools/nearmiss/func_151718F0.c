typedef unsigned char u8;
typedef signed short s16;
typedef unsigned int u32;
typedef int s32;
typedef float f32;

struct Table151718F0 {
    u8 unk0[3];
};

extern struct Table151718F0 D_8008CC20;
extern f32 func_15048A40(u8);
extern f32 func_150489B0(u8);
extern u8 func_150ADA20(void);
extern void func_1516D4E8();

void func_151718F0(f32 arg0, f32 arg1, f32 arg2, f32 arg3, s32 arg4, f32 arg5, s32 arg6, s32 arg7, u8 arg8, s32 arg9) {
    s32 i;
    s32 angle;
    u8 ang;
    f32 sinv;
    f32 cosv;
    f32 zpos;
    f32 zvel;
    s32 vz;
    u8 vzhi;
    u8 vzlo;
    f32 speed;
    s32 scale;
    s32 life;
    s16 ypos;
    f32 xpos;
    f32 xvel;
    s32 vx;
    u8 vxhi;
    u8 vxlo;
    struct Table151718F0 col;

    col = D_8008CC20;
    if (arg7 != 0) {
        angle = 0;
        for (i = 0; i < arg7; i++) {
            ang = angle >> 8;
            sinv = func_15048A40(ang);
            cosv = func_150489B0(ang);
            zpos = (arg3 * cosv) + arg2;
            zvel = 200.0f * cosv;
            vz = (s32)zvel;
            vzhi = vz >> 8;
            vzlo = vz;
            speed = ((func_150ADA20() & 0xFFFFU) * (1.0f / 65536.0f)) + 100.0f;
            scale = ((func_150ADA20() & 0xFFFFU) * arg5) + arg4;
            life = (func_150ADA20() & 0xF) + 0xA;
            ypos = arg1;
            xpos = (arg3 * sinv) + arg0;
            xvel = 200.0f * sinv;
            vx = (s32)xvel;
            vxhi = vx >> 8;
            vxlo = vx;
            func_1516D4E8((s16)(s32)xpos, ypos, (s16)(s32)zpos, 0xD,
                0, (&col)[arg6].unk0[0], (&col)[arg6].unk0[1], (&col)[arg6].unk0[2],
                0, 0, 0, 0,
                2, vxhi, vxlo, vzhi,
                vzlo, 0, 0, 5,
                0, 0, 0, (s16)scale,
                (s16)scale, life, (s32)speed, 0,
                0, arg8, arg9);
            angle += 0xFFFF / arg7;
        }
    }
}
