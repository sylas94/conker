/* tools/nearmiss/func_1516F864.c -- game_19A8B0, 34 instructions, LEAF (no frame)
 *
 * STATUS: mism=22, n=34/34 (EXACT LENGTH), leaf (frame exact). Every opcode is in golden's
 * order; what remains is ONLY the IDO temp-register rotation. Cold decompile, opened
 * 2026-08-25 from the never-attempted list.
 *
 * WHAT IT IS: a 24-bit fixed-point integrator run twice (X and Y). Each axis keeps a
 * position as s16 whole + u8 fraction, and a velocity as s8 whole + u8 fraction:
 *      pos = (unkE << 8) + unk2A          vel = (unk26 << 8) + unk27      -- axis 1
 *      pos = (unk12 << 8) + unk2B         vel = (unk28 << 8) + unk29      -- axis 2
 *      pos += vel * D_800BE9E4;   unkE = pos >> 8;   unk2A = (u8)pos;
 * D_800BE9E4 is the per-frame delta (see [[conker-actor-control-system]]); golden reloads it
 * for the SECOND axis (`lw $t8, 0x0($a2)`), so the source reads the global twice -- a `dt`
 * local scores 52 at n=32/34 (TWO SHORT) and is wrong.
 *
 * TYPES ARE PINNED BY THE LOADS: unk26/unk28 are `lb` => SIGNED (the TU's struct
 * Obj1516D4E8 declares them u8, which is why the draft carries `(s8)` casts; a file-local
 * shadow struct declaring them s8 and dropping the casts measures IDENTICALLY at 22, so the
 * cast is byte-neutral -- fix the struct or keep the cast, it does not matter for bytes).
 * unkE/unk12 are `lh` (s16, already right); unk27/29/2A/2B are `lbu` (u8).
 *
 * SIGNATURE: the TU declares `extern void func_1516F864(s32);` and all four call sites pass
 * `(s32)arg0`, so the parked C keeps the s32 parameter and casts inside. Do NOT drop that
 * extern to change the signature: the calls at lines 502/656/707/788 come BEFORE the
 * definition, so removing it makes them implicit and the definition then conflicts.
 *
 * ---------------------------------------------------------------- SCORE LADDER (measured)
 *   31  one `acc` reused for both axes, `vel` reused, pointer local
 *   31  same with the cast inlined at every access instead of a pointer local (identical)
 *   32  fully inlined, no locals at all
 *   29  TWO separate accumulators (acc1/acc2) -- this alone fixes `a2 = &D_800BE9E4`
 *   26  ...plus the STATEMENT-SPLIT shape: assign the field to the local, THEN update it in
 *       place (`vel = o->unk26; vel = (vel << 8) + o->unk27;`). Golden reuses one register
 *       for the load result AND the assembled value (`lb v1` / `sll t8,v1,8` / `addu v1`),
 *       which a single-expression spelling never produces.
 *   22  ...plus loading the POSITION FIELD FIRST (`acc1 = o->unkE;` before the velocity
 *       statements). THIS IS WHAT FIXES THE v0/v1 PAIR.   <-- PARKED
 *
 * DO NOT REPEAT (all measured, all n=34/34 unless noted):
 *   - declaration order of vel/acc1/acc2: ALL SIX permutations x (pointer local | inlined
 *     cast) = 12 builds, every one exactly 26 from the pre-M base. Order is irrelevant here.
 *   - `(s16)` cast on the position load: 26.  `<<=` / `+=` compound forms: 26.
 *   - a `dt = D_800BE9E4` local: 52, n=32/34 -- it CSEs the two reads into one and loses two
 *     instructions. Golden reads the global once per axis.
 *
 * ---------------------------------------------------------------- WHAT IS LEFT
 * Pure temp rotation, and it is NOT a uniform shift -- the two axes swap register sets:
 *      ours:   axis1 uses t6,t7   axis2 uses t8,t9   then t3,t4
 *      golden: axis1 uses t8,t9   axis2 uses t7,t6   then t7,t6
 * Golden CYCLES TIGHTER, reusing t6/t7 for both later groups where we keep taking fresh
 * temps. Per [[ido-matching-tricks]] the rotation counter moves with the number of
 * temp-consuming operations emitted earlier, so the handle is something that consumes two
 * more temps before the first axis -- but it must be a real source difference, not a dummy
 * (see [[conker-fake-match-policy]]). The obvious candidates (the s8 cast, the dt local, the
 * compound-assign forms) are all refuted above.
 */

void func_1516F864(s32 arg0) {
    struct Obj1516D4E8 *o = (struct Obj1516D4E8 *)arg0;
    s32 vel;
    s32 acc1;
    s32 acc2;

    acc1 = o->unkE;
    vel = (s8)o->unk26;
    vel = (vel << 8) + o->unk27;
    acc1 = (acc1 << 8) + o->unk2A;
    acc1 = acc1 + (vel * D_800BE9E4);
    o->unkE = acc1 >> 8;
    o->unk2A = acc1;

    acc2 = o->unk12;
    vel = (s8)o->unk28;
    vel = (vel << 8) + o->unk29;
    acc2 = (acc2 << 8) + o->unk2B;
    acc2 = acc2 + (vel * D_800BE9E4);
    o->unk12 = acc2 >> 8;
    o->unk2B = acc2;
}
