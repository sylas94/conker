/* 2026-10-06 OWNER RULING: a TU-aware permuter found mism 0 by making the visibility update read
 * arg0->flags directly, which leaves `flags = arg0->flags;` assigned but NEVER USED (deleting it -> 108).
 * The owner rejected that dead store as a forcer -- keep this function parked. The 0 version is saved at
 * tools/nearmiss/pending_repo_changes/DEADSTORE_func_151D2F90_game_1FFF60_0.c for reference only. */

/* UPDATE 2026-10-06: 42 -> 7 (fastscore, n=104/104, frame 0x18). Best honest body at the end of this file.
 * What closed it: the visibility test written as `if (obj->unk1D4 != 0 && (obj->unk74 & 0xF) != 0xF) set;
 * else clear;` (reproduces golden's two beql+sb and the dead sb); `u8 was` read from arg0->flags (not from
 * the flags local) then `was &= 2`; a `u8 now = arg0->flags & 2;` local with `if (was != now) { if (now) ...`.
 * RESIDUE (7 rows, all one fact): golden coalesces the shared lbu with `flags` ($v1) and copies into `was`
 * ($a1); ours coalesces it with `was`. Refuted: 96 type/order combos (was/flags u8/u16/s16/s32, one/two-step,
 * order) -- best 6 with s32 was but the entry still differs; no flags local puts the load in $v1 but fuses
 * was's two steps into one andi; moving `was &= 2` past the early-out = 32-55. */

/* tools/nearmiss/func_151D2F90.c -- game_1FFF60.
 *
 * FILE KIND: STANDALONE TU (a note; splice the body over the pragma in src/game_1FFF60.c).
 *
 * STATUS 2026-08-24: mism=42, frame -0x18 (golden's), n=104/104 -- EXACT LENGTH.
 * From no attempt at all to 42 with the right frame and length; the residue is register
 * rotation plus one branch-likely store.
 *
 * BUILT FROM THE MATCHED SIBLING, not from scratch. func_151D2C40 sits directly above it in
 * the same file and shares the shape: obj = arg0->unk10, the same three-clause early-out to
 * func_1516972C, and the same byte-offset cast idiom. The `& 0xFFFD` spelling (rather than
 * `& ~2`) is also already in this file, in func_151D2F00 -- IDO emits `andi ...,0xFFFD`
 * because the u8 promotes to int.
 *
 * TWO MEASURED FINDINGS, both worth more than the score:
 *
 * 1. `was` MUST BE READ SEPARATELY FROM arg0, not derived from a cached `flags` local.
 *        was = *(u8 *)((u8 *)arg0 + 0x18) & 2;     ->  42
 *        flags = ...; was = flags & 2;             ->  70
 *    Golden computes `was` BEFORE the early-out and spends it on two branch delay slots we
 *    otherwise leave as nop:
 *        lbu  $v1, 0x18($a0)      flags
 *        lw   $t7, 0x0($v0)
 *        or   $a1, $v1, $zero     a1 = flags
 *        andi $t6, $a1, 0x2
 *        beqz $t7, .L151D2FD4
 *        or   $a1, $t6, $zero     a1 = flags & 2   <- delay slot
 *    The double move through $a1 is the tell that `was` is assigned twice, not once.
 *
 * 2. ASSIGNMENT ORDER IS LOAD-BEARING AND ONE DIRECTION IS STRICTLY WRONG.
 *        assign flags then was  ->  42, n=104/104
 *        assign was then flags  -> 108, n=105/104   (an extra instruction appears)
 *    Declaration order does NOT matter here (42 either way), which is unusual for this
 *    codebase -- see memory/conker-private-libultra-copies.md for the frame-layout law where
 *    it does. Dropping the `flags` local entirely and re-reading at each use also gives 42,
 *    and is the simplest honest spelling, so prefer it.
 *
 * REMAINING RESIDUE. Golden keeps `flags` in the load register $v1 and routes `was` through
 * $a1; we put the load in $a2 and the copy in $a1 -- a one-register rotation. And at
 *        beql $t1, $zero, .L151D301C
 *        sb   $t5, 0x18($a0)          <- store in the branch-likely delay slot
 * we emit `beqz` + `nop`. That second half is the SAME delay-slot family as four other
 * functions -- see memory/conker-delayslot-duplication-family.md before spending time on it.
 *
 * GOLDEN CONTAINS DEAD CODE HERE, which is a useful sanity anchor: the `sb $t5, 0x18($a0)`
 * after `b .L151D301C` is unreachable, the orphan left when IDO converted the `||` chain into
 * two branch-likelies that each carry the same store in their delay slot. Do not try to
 * reproduce it deliberately; it falls out of the || spelling.
 */

/* ---- best body (7) ---- */
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
        arg0->flags = flags | 2;
    } else {
        arg0->flags = flags & 0xFFFD;
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
