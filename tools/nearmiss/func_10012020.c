/* NEAR MISS -- init_11FA0 / func_10012020 (1344 B), parked 2026-08-16.
 *
 * STATUS
 *   Structurally EXACT.  Instruction sequence, jump table, control flow, delay slots and
 *   the .rodata literal pool all reproduce.  Best score with -R: 1800 (asm-differ, object
 *   mode).  The whole residual is ONE register-allocator decision that then renumbers every
 *   FP register and shifts every stack offset by 8:
 *
 *     golden:  div.s $f0,$f4,$f6 ; swc1 $f0,0x48(sp)      <- spilled to a stack temp,
 *              loop: lwc1 $f0,0x48(sp) ...                   reloaded every iteration
 *     ours:    div.s $f20,$f4,$f6                         <- kept in a CALLEE-SAVED FP reg,
 *              loop: mfc1 a1,$f20                            so the prologue grows an
 *                                                            `sdc1 $f20,0x20(sp)` and the
 *                                                            frame goes 0x70 -> 0x78.
 *
 *   This is the loop-invariant / spill-vs-callee-saved ranking tie.  BAIL SIGNATURE MET:
 *   five genuinely different honest spellings of the same code scored 3007 / 2252 / 1962 /
 *   1922 / 1800 and $f20 never released:
 *       1. `f32 sp48;` at function scope, division before the loop            -> 1962
 *       2. division written inline inside the loop body (LICM hoists it)      -> 1800
 *       3. `f32 sp48 = ...;` declared block-scoped inside the `if`            -> 1922
 *       4/5. earlier variants that also mis-scheduled the D_80041FD9 stores.
 *
 * WHAT WAS SOLVED ALONG THE WAY (keep these -- they are all confirmed against the golden)
 *
 *   a. The jump table is 1-based: `addiu t3,v0,-1 ; sltiu at,t3,5`, so the switch is
 *      case 1..5 with NO case 0, and the default arm carries the `D_8004277C == 4` test.
 *      Case bodies are emitted in source order 1,2,3,4,5 -- which is also ascending, so
 *      no reordering was needed.
 *
 *   b. THE DUPLICATE 0.08f POOL ENTRY.  The golden .rodata has D_8002C430 AND D_8002C438,
 *      both 0x3DA3D70A, i.e. two pool slots holding the same float.  Case 3 uses the value
 *      three times: twice before the `jal sinf` (CSE'd into the caller-saved $f14) and once
 *      after (a fresh load from the SECOND slot).  Writing `0.08f` three times makes IDO
 *      CSE all three into one slot and hold it in $f20 across the call -- wrong pool AND
 *      wrong register.  Writing the third occurrence as a different decimal that denotes the
 *      SAME float (0.079999998f) makes IDO's constant table mint a second node, which
 *      reproduces the golden pool byte-for-byte and puts $f14 back.
 *      CAVEAT, read before shipping this: the golden proves the original had two distinct
 *      constant-table nodes, but NOT which spelling produced them.  0.079999998f is one
 *      candidate; a folded expression (8.0f/100.0f) or a differently-typed constant are
 *      others.  Treat the spelling as unverified.
 *
 *   c. `D_80041FD9 = 0;` is the LAST statement of case 3 and of case 5 (not the first);
 *      putting it first mis-schedules the sb by ~0x10 bytes in both arms.
 *
 *   d. `if (D_8004277C == 4)` -- NOT the Yoda form mips_to_c emits.  `4 == D_8004277C`
 *      produces `bne t2,v1` where the golden has `bne v1,t2`.
 *
 *   e. D_8002BA10 / D_8002BA18 are 8-byte records copied wholesale into two locals
 *      (lw/lw/sw/sw against `addiu t6,sp,0x5c`), so they are STRUCTS, not f32[2]; the
 *      tail loop then walks them with f32 pointers.
 *
 *   f. include/variables.h inaccuracies hit here: D_80042780 and D_80042788 are declared as
 *      single f32 but are two-element records (the tail loop walks both), and D_8002BA10 /
 *      D_8002BA18 are absent entirely.
 *
 * REMAINING STACK-LAYOUT CLUE (not chased to the end)
 *   The golden frame is 0x70 with locals at 0x54 (8B), 0x5C (8B), 0x68 (4B) and a spill at
 *   0x48 -- note the 4-byte hole at 0x64 and the 8-byte hole at 0x4C.  Our locals pack
 *   tightly with no holes.  Those holes may mean the original declares locals we have not
 *   recovered, and recovering them may also be what changes the allocator's mind about $f20.
 *
 * conker.us.yaml was NOT modified for this TU: the migration line
 *     - [0x2C410, .rodata, init_11FA0]
 * is still un-applied, exactly as required while the function remains a #pragma GLOBAL_ASM.
 * Apply it only together with a matching C body.
 */

/* --- file-local declarations the draft needs (variables.h is inaccurate, see (f)) --- */
typedef struct {
    /* 0x0 */ f32 unk0;
    /* 0x4 */ f32 unk4;
} Pair11FA0;

extern Pair11FA0 D_8002BA10;
extern Pair11FA0 D_8002BA18;
extern f32 D_80042784;
extern f32 sinf(f32);

void func_10012020(void) {
    f32 sp68;
    Pair11FA0 sp5C;
    Pair11FA0 sp54;
    f32 sp48;
    f32 *p54;
    f32 *p80;
    f32 *p5C;
    f32 *p88;
    s32 i;
    s32 mode;

    sp68 = 0.0f;
    sp5C = D_8002BA10;
    sp54 = D_8002BA18;
    mode = D_80042770;
    if ((D_800DBFF0->unk5F0 & 1) != 0) {
        if ((D_800B0DF0->pad2A[0] & 1) == 0) {
            mode = 1;
        }
    }
    if (D_80042774 != 0) {
        mode = D_80042774;
    } else if (D_80042778 != 0) {
        mode = D_80042778;
    }
    if (mode == 6) {
        mode = 0;
    }
    switch (mode) {
    case 1:
        D_8004277C = 0;
        sp68 = (13.0f - D_80042790) + D_80042790;
        sp5C.unk0 = 127.0f;
        sp54.unk0 = ((519.0f + (sinf(D_80042798 * 0.05235988f) * 200.0f)) - D_80042780) + D_80042780;
        break;
    case 2:
        D_8004277C = 0;
        sp68 = 70.0f;
        sp5C.unk0 = 127.0f;
        sp54.unk0 = (sinf(D_80042798 * 0.34906584f) * 200.0f) + 450.0f;
        break;
    case 3:
        D_8004277C = 0;
        sp68 = ((52.0f - D_80042790) * 0.08f) + D_80042790;
        sp5C.unk0 = ((127.0f - D_80042788) * 0.08f) + D_80042788;
        /* see (b): the third factor must be a DISTINCT constant-table node */
        sp54.unk0 = (((436.0f + (sinf(D_80042798 * 0.12217305f) * 282.0f)) - D_80042780) * 0.079999998f) + D_80042780;
        D_80041FD9 = 0;
        break;
    case 4:
        D_8004277C = 4;
        sp5C.unk4 = 127.0f;
        if (D_800BE9B4 != 0) {
            sp54.unk4 = 400.0f;
        } else {
            sp54.unk4 = (400.0f - D_80042784) + D_80042784;
        }
        D_80041FD9 = 0;
        break;
    case 5:
        sp5C.unk4 = 127.0f;
        sp54.unk4 = 520.0f;
        D_80041FD9 = 0;
        break;
    default:
        if (D_8004277C == 4) {
            sp54.unk4 = ((11000.0f - D_80042784) * 0.05f) + D_80042784;
            if (sp54.unk4 < 9000.0f) {
                D_8004277C = 4;
            } else {
                D_8004277C = 0;
                D_80041FD9 = 1;
            }
        }
        break;
    }

    D_80042798 = D_80042798 + D_800BE9A4;
    if (sp68 != D_80042790 || 1.0f != D_80042794) {
        sp48 = sp68 / 127.0f;   /* THE BLOCKER: golden spills this to 0x48(sp), we take $f20 */
        for (i = 0; i != 3; i++) {
            func_10008BC0(i, sp48, 1.0f);
        }
        D_80042790 = sp68;
        D_80042794 = 1.0f;
    }

    p80 = &D_80042780;
    p88 = &D_80042788;
    i = 0;
    p54 = &sp54.unk0;
    p5C = &sp5C.unk0;
    do {
        if (*p54 != *p80) {
            func_10008B60(i, i, 9, 0, (s32)*p54);
            *p80 = *p54;
        }
        if (*p5C != *p88) {
            func_10008B60(i, i, 8, 0, (s32)*p5C);
            *p88 = *p5C;
        }
        i++;
        p54++;
        p80++;
        p5C++;
        p88++;
    } while (i != 2);
    D_80042770 = 0;
}
