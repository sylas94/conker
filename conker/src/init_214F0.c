#include <ultra64.h>

#include "functions.h"
#include "variables.h"

// struct21 *func_100214F0(struct42 *arg0, void *arg1, s32 arg2, void *struct21);
#pragma GLOBAL_ASM("asm/nonmatchings/init_214F0/func_100214F0.s")
s32 func_10021C40(Obj_214F0 *arg0, s32 arg1, void *arg2)
{
    switch (arg1) {
    case 5:
        arg0->unk28 = arg2;
        arg0->unk44 = arg0->unk28->unk0;
        arg0->unk38 = 0;
        arg0->unk28->unk4 = arg0->unk28->unk4 / 9 * 9;
        if (((u32)arg0->unk28->unk10 & 0xFF000003) != 0x80000000) {
            arg0->unk24 = 0;
            arg0->unk1C = arg0->unk20 = arg0->unk24;
            break;
        } else {
            arg0->unk2C = arg0->unk28->unk10->unk0 * 2 * arg0->unk28->unk10->unk4 * 8;
        }
        if (arg0->unk28->unkC != 0) {
            arg0->unk1C = arg0->unk28->unkC->unk0;
            arg0->unk20 = arg0->unk28->unkC->unk4;
            arg0->unk24 = arg0->unk28->unkC->unk8;
            bcopy(arg0->unk28->unkC->data, arg0->unk18, 0x20);
        } else {
            arg0->unk24 = 0;
            arg0->unk1C = arg0->unk20 = arg0->unk24;
        }
        break;
    case 4:
        arg0->unk3C = 0;
        arg0->unk40 = 1;
        arg0->unk38 = 0;
        if (arg0->unk28 != 0) {
            arg0->unk44 = arg0->unk28->unk0;
            arg0->unk24 = 0;
        }
        break;
    default:
        break;
    }
    return 0;
}
// ? func_10021C40(void *arg0, s32 arg1, s32 arg2) {
//     s32 temp_s0;
//     s32 temp_s0_2;
//     void *temp_t3;
//     void *temp_t3_2;
//
//     if (arg1 != 4) {
//         if (arg1 != 5) {
//
//         } else {
//             arg0->unk28 = arg2;
//             arg0->unk44 = (s32) *arg0->unk28;
//             arg0->unk38 = 0;
//             temp_t3 = arg0->unk28;
//             temp_t3->unk4 = (s32) (((s32) temp_t3->unk4 / 9) * 9);
//             if ((arg0->unk28->unk10 & 0xFF000003) != 0x80000000) {
//                 arg0->unk24 = 0;
//                 temp_s0 = arg0->unk24;
//                 arg0->unk20 = temp_s0;
//                 arg0->unk1C = temp_s0;
//             } else {
//                 temp_t3_2 = arg0->unk28->unk10;
//                 arg0->unk2C = (s32) (temp_t3_2->unk0 * 2 * temp_t3_2->unk4 * 8);
//                 if (arg0->unk28->unkC != 0) {
//                     arg0->unk1C = (s32) *arg0->unk28->unkC;
//                     arg0->unk20 = (s32) arg0->unk28->unkC->unk4;
//                     arg0->unk24 = (s32) arg0->unk28->unkC->unk8;
//                     bcopy(arg0->unk28->unkC + 0xC, arg0->unk18, 0x20);
//                 } else {
//                     arg0->unk24 = 0;
//                     temp_s0_2 = arg0->unk24;
//                     arg0->unk20 = temp_s0_2;
//                     arg0->unk1C = temp_s0_2;
//                 }
//             }
//         }
//     } else {
//         arg0->unk3C = 0;
//         arg0->unk40 = 1;
//         arg0->unk38 = 0;
//         if (arg0->unk28 != 0) {
//             arg0->unk44 = (s32) *arg0->unk28;
//             arg0->unk24 = 0;
//         }
//     }
//     return 0;
// }

void *func_10021E4C(Cmd214 *gfx, struct42 *obj, s32 a2, s32 count, s16 arg4, s16 arg5, s32 flags)
{
    s32 align;
    s32 res;

    if (count > 0) {
        res = ((s32 (*)(s32, s32, s32))obj->unk30)(obj->unk44, count, obj->unk34);
        if (res == 0) {
            obj->unk80 = 1;
            obj->unk62 = 0;
            obj->unk40 = 0;
            return gfx;
        }
        align = res & 7;
        count = count + align;
        {
            Cmd214 *_a = gfx++;
            _a->w0 = ((((count - (count & 7)) + 8) & 0xFFF) << 12) | 0x04000000 | (arg5 & 0xFFF);
            _a->w1 = res - align;
        }
    } else {
        align = 0;
    }
    if (flags & 2) {
        Cmd214 *_a = gfx++;
        _a->w0 = 0x0F000000;
        _a->w1 = obj->unk18 & 0x1FFFFFFF;
    }
    {
        Cmd214 *_a = gfx++;
        _a->w0 = (obj->unk14 & 0x1FFFFFFF & 0x00FFFFFF) | 0x01000000;
        _a->w1 = ((flags & 0xF) << 28) | (((a2 << 1) & 0xFFF) << 16) | ((align & 0xF) << 12) | (arg4 & 0xFFF);
    }
    obj->unk40 = 0;
    return gfx;
}
