#include <ultra64.h>
#include "functions.h"
#include "variables.h"

s32 func_1509BE40();

void func_150F6B00(struct108 *arg0) {
    struct174 dir;
    struct17 toTarget;
    struct17 offset;
    f32 blend;
    f32 invDist;
    f32 dot;
    f32 pitch;
    f32 pan;

    if ((func_1509BE40(1, 0x4003, 6, 0x2000) != 0) && (arg0->unk3D0->health != 0)) {
        arg0->unk84 |= 0xC0001000;
        func_15048F90((struct17 *)&D_800A1B80, (struct17 *)&arg0->unk2A4, &toTarget);
        func_15048F90((struct17 *)&D_800A1B80, (struct17 *)&D_800A1B8C, &offset);
        invDist = 1.0f / func_150AD930(&offset.unk0);
        func_1504917C(&offset, (struct17 *)&dir);
        dot = func_150AD900(&dir.unk0, &toTarget.unk0) * invDist * 0.75f;
        blend = (dot < 0.0f) ? 0.0f : ((dot > 1.0f) ? 1.0f : dot);

        pitch = -20.0f;
        if (func_1509BE40(4, 0x2000, 0xAC, 0x4040, 0x4041, 0x4042, 0x4043) != 0) {
            pan = (0 * blend) + -900.0f;
            arg0->unk374 = 220.0f;
        } else if (func_1509BE40(4, 0x2000, 0xAC, 0x4047, 0x4046, 0x4045, 0x4044) != 0) {
            pan = (0 * blend) + 900.0f;
            arg0->unk374 = 220.0f;
        } else {
            arg0->unk374 = 294.0f;
            pan = 0 * blend;
        }

        func_1509BFB0(3, 0x4003, 3, (s32)pan, (s32)pitch, (s32)((D_800A1B98 * blend) + D_800A1B9C));
        func_15049688(&arg0->unk37C, func_15048FC8((struct17 *)&D_800D9A50) - 180.0f, (f32 *)&arg0->unk7C8, 8.0f, 10.0f, arg0->unk7B4);
        arg0->unk39C = arg0->unk37C * D_800A1BA0;
    } else {
        arg0->unk84 &= 0x3FFFEFFF;
    }
}
