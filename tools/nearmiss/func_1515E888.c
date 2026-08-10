struct Light1515E888 {
    char pad0[5];
    u8 unk5;
    u8 unk6;
    u8 unk7;
    char pad8[6];
    s16 unkE;
    s16 unk10;
    s16 unk12;
    char pad14[0x1B];
    u8 unk2F;
};

extern u8 D_800D9E21;
extern struct Light1515E888 *D_800D9E28[];

void func_1515E278(s32, s32, s32, s32, u8 *, s32, s32);

void func_1515E888(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, u8 *arg5, s32 arg6, s32 arg7) {
    f32 pos[3];
    f32 colour[3];
    struct Light1515E888 **list;
    struct Light1515E888 *light;
    s32 count;
    s32 i;
    s32 temp;
    f32 dx;
    f32 dy;
    f32 dz;
    f32 dist;
    f32 scale;
    f32 intensity;

    func_1515E278(arg1, arg2, arg3, arg4, arg5, arg6, arg7);
    colour[0] = (f32)(u32)arg5[0];
    colour[1] = (f32)(u32)arg5[1];
    colour[2] = (f32)(u32)arg5[2];
    count = (D_800D9E21 & 0x7F) - 1;
    i = 0;
    if (count > 0) {
        list = D_800D9E28;
        while (1) {
            light = *list;
            if (light != NULL) {
                pos[0] = (f32)light->unkE;
                pos[1] = (f32)light->unk10;
                pos[2] = (f32)light->unk12;
                scale = (f32)(u32)light->unk2F * 2048.0f;
                dz = pos[2] - (f32)arg3;
                dx = pos[0] - (f32)arg1;
                dy = pos[1] - (f32)arg2;
                dist = (dz * dz) + ((dx * dx) + (dy * dy));
                intensity = scale / dist;
                if (intensity > 1.0f) {
                    intensity = 1.0f;
                }
                colour[0] += intensity * (f32)(u32)light->unk5;
                colour[1] += intensity * (f32)(u32)light->unk6;
                colour[2] += intensity * (f32)(u32)light->unk7;
            }
            i++;
            list++;
            if (i == count) {
                break;
            }
        }
    }
    temp = (s32)colour[0];
    if (temp > 255) {
        temp = 255;
    }
    arg5[0] = temp;
    temp = (s32)colour[1];
    if (temp > 255) {
        temp = 255;
    }
    arg5[1] = temp;
    temp = (s32)colour[2];
    if (temp > 255) {
        temp = 255;
    }
    arg5[2] = temp;
}
