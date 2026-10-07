/* An effect that follows an actor and calls back into D_8008FC4C..58 by index. */
typedef struct {
    u8 pad0[0x10];
    struct127 *owner;    /* 0x10 */
    u8 ownerId;          /* 0x14: owner->unique_id when attached */
    u8 pad15;
    s16 timer;           /* 0x16 */
    u8 flags;            /* 0x18: bit 0 = timed, bit 1 = shown */
    s8 updateFn;         /* 0x19 */
    s8 showFn;           /* 0x1A */
    s8 hideFn;           /* 0x1B */
    s8 expireFn;         /* 0x1C */
} Effect151D2F90;

extern s32 (*D_8008FC4C[])(Effect151D2F90 *);
extern void (*D_8008FC50[])(Effect151D2F90 *);
extern void (*D_8008FC54[])(Effect151D2F90 *);
extern void (*D_8008FC58[])(Effect151D2F90 *);

void func_151D2F90(Effect151D2F90 *arg0) {
    struct127 *obj;
    u8 flags;
    u8 was;
    u8 now;

    obj = arg0->owner;
    flags = arg0->flags;
    was = arg0->flags;
    was &= 2;
    if (obj->interaction_state == 0 || obj->id == 0xFF || obj->unique_id != arg0->ownerId) {
        func_1516972C((struct102 *)arg0);
        return;
    }
    if (obj->unk1D4 != 0 && (obj->unk74 & 0xF) != 0xF) {
        arg0->flags = arg0->flags | 2;
    } else {
        arg0->flags = arg0->flags & 0xFFFD;
    }
    if (arg0->flags & 1) {
        arg0->timer -= D_800BE9E4;
        if (arg0->timer < 0) {
            if (arg0->expireFn != -1) {
                D_8008FC58[arg0->expireFn](arg0);
            }
            func_1516972C((struct102 *)arg0);
            return;
        }
    }
    now = arg0->flags & 2;
    if (was != now) {
        if (now) {
            D_8008FC50[arg0->showFn](arg0);
        } else {
            D_8008FC54[arg0->hideFn](arg0);
        }
    }
    if (arg0->updateFn != -1) {
        if (D_8008FC4C[arg0->updateFn](arg0) == 0) {
            func_1516972C((struct102 *)arg0);
        }
    }
}
