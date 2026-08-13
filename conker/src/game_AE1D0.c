#include <ultra64.h>
#include "functions.h"
#include "variables.h"

typedef struct {
    u16 field_0x0;
    u16 field_0x2;
    u16 field_0x4;
    u16 field_0x6;
    u16 field_0x8;
    u16 field_0xa;
    u16 field_0xc;
    u16 field_0xe;
} Struct1508108C;

extern u16 D_8009BD30;
extern u16 D_8009BD34;
extern u16 D_8009BD38;
extern Struct1508108C D_8009BD3C[];


#pragma GLOBAL_ASM("asm/nonmatchings/game_AE1D0/func_15080D20.s")

s32 func_1508108C(Struct1508108C *arg0) {
    s32 temp_v0;
    s32 var_v1;
    s32 var_a1;

    if ((temp_v0 = ((u8 *)arg0)[4]) == D_8009BD30) {
        return 0;
    }
    if (temp_v0 == D_8009BD34) {
        return 1;
    }
    arg0 = D_8009BD3C;
    var_v1 = 3;
    if (temp_v0 == D_8009BD38) {
        return 2;
    }
    var_a1 = 0x17;

loop:
    if (temp_v0 == arg0->field_0x0) {
        return var_v1;
    }
    if (temp_v0 == arg0->field_0x4) {
        return var_v1 + 1;
    }
    if (temp_v0 == arg0->field_0x8) {
        return var_v1 + 2;
    }
    if (temp_v0 == arg0->field_0xc) {
        return var_v1 + 3;
    }
    var_v1 += 4;
    arg0++;
    if (var_v1 != var_a1) {
        goto loop;
    }

    return -1;
}

/* One hit sphere bound to a bone of a model. */
typedef struct {
    /* 0x0 */ u8  bone;
    /* 0x1 */ u8  part;
    /* 0x2 */ u16 radius;
    /* 0x4 */ s16 x;
    /* 0x6 */ s16 y;
    /* 0x8 */ s16 z;
} HitSphere; /* size 0xA */

/* struct124 (include/structs.h) has the wrong types at 0xE/0x10: the game reads a u16 at
 * 0xE (golden `lhu $t2,0xE($t1)` + the bgez/0x4F800000 unsigned-to-float fixup) and an s16
 * at 0x10 (golden `lh $t6,0x10($t5)`), not an s16 and an s32.  Corrected file-locally. */
typedef struct {
    /* 0x00 */ u8  pad0[0xE];
    /* 0x0E */ u16 body_radius;
    /* 0x10 */ s16 body_height;
} ModelBounds;

/* D_8009BD30 is an array of 4-byte records; the byte at +2 of record N selects
 * which hit-sphere table the model uses. */
extern u8 D_8009BD32[];
extern HitSphere *D_80086C60[];
extern u8 D_8009CBCC[];

s32 func_151452C4(struct17 *arg0, struct17 *arg1, struct17 *arg2, f32 arg3, struct17 *arg4, struct17 *arg5, f32 *arg6, f32 *arg7);

/* Ray vs. per-bone hit-sphere test for one actor.  Broad phase: build the whole-object
 * bounding sphere from D_800D1C90[obj->id] and ray-test it; if that hits, walk the model's
 * hit-sphere table, skipping bones masked off in obj->unk9C, transform each sphere's local
 * offset by its bone matrix and keep the nearest / highest-priority hit.
 *
 * ORIGINAL-GAME BUG, reproduced deliberately: the tail does `*outDist = tNear;` after the
 * loop, overwriting the tracked best distance with the LAST call's near-t rather than the
 * best one.  Golden does exactly this (0x15081460..0x15081484); it is not to be "fixed".
 */
s32 func_1508114C(struct127 *obj, struct17 *rayOrigin, struct17 *rayDir, struct17 *outNear, struct17 *outFar, struct17 *outCentre, f32 *outDist, s32 *outIndex, s32 *outBone, s32 *outPart, s16 *outOffset) {
    s32 idx;
    HitSphere *spheres;
    s32 count;
    s32 type;
    s32 bestIndex;
    f32 tNear;
    f32 tFar;
    s32 i;
    struct17 centre;
    struct17 bestCentre;
    struct17 near;
    struct17 far;
    struct17 local;
    struct17 bestNear;
    struct17 bestFar;
    s32 bestPart;
    HitSphere *p;
    u8 *mtx;
    f32 radius;

    if (obj->unk1D4 == NULL) {
        return -1;
    }
    idx = func_1508108C((Struct1508108C *)obj);
    if (idx == -1) {
        return -1;
    }
    type = D_8009BD32[idx * 4];
    spheres = D_80086C60[type];
    count = D_8009CBCC[type];
    *outDist = -1.0f;
    centre.unk0 = obj->x_position;
    centre.unk4 = (((ModelBounds *)D_800D1C90[obj->id])->body_height * obj->y_scale) + obj->y_position;
    centre.unk8 = obj->z_position;
    radius = ((ModelBounds *)D_800D1C90[obj->id])->body_radius * obj->y_scale;
    if (func_151452C4(rayOrigin, rayDir, &centre, radius, &near, &far, &tNear, &tFar) == 0) {
        return 0;
    }
    bestPart = -1;
    i = 0;
    if (count > 0) {
        p = spheres;
        do {
            if (((1 << p->bone) & obj->unk9C) != 0) {
                goto next;
            }
            mtx = (u8 *)obj->unk1D4;
            local.unk0 = p->x;
            local.unk4 = p->y;
            local.unk8 = p->z;
            func_15143134(&local, &centre, (s32)mtx + (p->bone << 6));
            if (func_151452C4(rayOrigin, rayDir, &centre, p->radius * obj->xz_scale, &near, &far, &tNear, &tFar) != 0) {
                if ((*outDist == -1.0f) || ((tNear < *outDist) && (p->part >= bestPart))) {
                    *outDist = tNear;
                    bestNear = near;
                    bestFar = far;
                    bestCentre = centre;
                    bestIndex = i;
                    bestPart = p->part;
                }
            }
        next:
            i++;
            p++;
        } while (i != count);
    }
    if (*outDist == -1.0f) {
        return 0;
    }
    *outDist = tNear;
    *outIndex = bestIndex;
    *outPart = spheres[bestIndex].part;
    *outBone = spheres[bestIndex].bone;
    outOffset[0] = spheres[bestIndex].x;
    outOffset[1] = spheres[bestIndex].y;
    outOffset[2] = spheres[bestIndex].z;
    *outNear = bestNear;
    *outFar = bestFar;
    if (outCentre != NULL) {
        *outCentre = bestCentre;
    }
    return 1;
}


#pragma GLOBAL_ASM("asm/nonmatchings/game_AE1D0/func_15081574.s")
