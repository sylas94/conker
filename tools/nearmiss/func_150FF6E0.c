/* ===========================================================================
 * func_150FF6E0  --  game_12C1E0.c  --  92 asm lines  --  cold decompile
 * PARKED at 180 (bounded window, 88 words, with AND without -R).
 * draft1 2078 -> 1958 -> 180.  (The unbounded 4096-line window reads 280 -- it
 * bleeds into func_150FF840; always bound the window on this TU.)
 *
 * STATE: FRAME EXACT (0x88), every stack offset exact, every instruction
 * present and in golden's order EXCEPT one: golden has a redundant
 *      af4: b   afc
 *      af8:  move v0,zero      (delay slot)
 * where the live C elides the branch and emits `move v0,zero` bare.  The rest
 * of the residual is a UNIFORM +1 IDO TEMP-ROTATION OFFSET: from the loop
 * preheader onwards golden allocates t3,t4,t5 | t6,t7,t8,t9,t2,t3 | t5,t6,t7
 * where the live C allocates t2,t3,t4 | t5,t6,t7,t8,t9,t2 | t4,t5,t6.
 * Everything BEFORE the preheader (the four %hi/%lo src addresses t6..t9,
 * t0 = &dst, t1 = arg2) already matches, so exactly ONE extra temp allocation
 * happens in golden between `src[3] = &D_800A205C;` and the loop, and it
 * produces NO instruction (it is coalesced away).
 *
 * ---------------------------------------------------------------------------
 * FRAME DECODE (SETTLED -- reproduces 0x88 exactly)
 * ---------------------------------------------------------------------------
 * framesize 0x88.  arg-build [0x00,0x18) (func_1514654C takes 6 args).
 * saved regs s0 0x1C, s1 0x20, ra 0x24.  temps [0x28,0x33).
 * Home area, TOP-DOWN in declaration order, ENDING at 0x88:
 *   [0x84,0x88) decl#1  4     which   (s32)
 *   [0x5C,0x84) decl#2  0x28  src[10] (a3 of func_1514654C)
 *   [0x34,0x5C) decl#3  0x28  dst[10] (5th arg of func_1514654C)
 *   [0x33,0x34) decl#4  1     i       (u8 -- `andi ...,0xff` on the increment)
 * Declaration order is PINNED by the addresses: src MUST be 0x5C and dst
 * 0x34, which only happens with a 4-byte local declared FIRST.
 *
 * ---------------------------------------------------------------------------
 * THE ONE STRUCTURAL LEVER THAT PAID (1958 -> 280)
 * ---------------------------------------------------------------------------
 * Golden computes i*12 TWICE in the loop, once by shifts (sll/subu/sll) for
 * the D_800A2080 element and once by `multu` for arg0[i].  Writing the first
 * as a pointer local (`base = D_800A2080[rand&1]; ... &base[i]`) makes IDO CSE
 * the two multiplies, which costs an extra callee-saved register (s2), grows
 * the frame to 0x90 and scores 1958.  Writing it as a genuine 2-D array
 * subscript `&D_800A2080[which][i]` (with `s32 which` holding the index)
 * keeps them distinct, restores the frame to 0x88 and the whole instruction
 * stream to golden's.
 *
 * ---------------------------------------------------------------------------
 * MEASURED NEGATIVES (all against the 280 base unless stated)
 * ---------------------------------------------------------------------------
 *  2078  draft1: `struct17 *base` declared LAST (order i,src,dst,base).
 *                frame 0x98, 3 saved s-regs.
 *  1958  same but `struct17 *base` declared FIRST.  frame 0x90.
 *   180  CURRENT: `s32 which` + 2-D subscript &D_800A2080[which][i].
 *   180  `which = func_150ADA20();` with the `& 1` moved to the use site
 *        (&D_800A2080[which & 1][i]).  BYTE-IDENTICAL output -- the mask
 *        position is folded, so it is not the rotation lever.
 *   180  `if (...) {...; return 1;} else {return 0;}` instead of the trailing
 *        `return 0;`.  BYTE-IDENTICAL -- does NOT restore golden's `b afc`.
 *   735  early-return form `if (... == 0) { return 0; } ...; return 1;`
 *        (reorders the two blocks; golden puts the return-0 block LAST).
 *  1983  `which = func_150ADA20() & 1;` moved AFTER the four src[] stores.
 *        The rand MUST be the first statement.
 *
 * RESIDUAL CLASS: as1 PEEPHOLE (the un-elided `b` into a filled delay slot)
 * + ALLOCATION (a single-slot temp-rotation offset with no instruction of its
 * own).  Do NOT close this with a no-op mask -- the N-no-ops test applies and
 * a rotation forcer here would be a fake match.
 * =========================================================================== */

/* ---- parked source: this is the 280 build, verbatim ---- */

extern f32 D_800A205C;
extern f32 D_800A2068;
extern f32 D_800A2074;
extern struct17 D_800A2080[2][6];

s32 func_150FF6E0(struct17 *arg0, struct17 *arg1, struct17 *arg2, struct17 *arg3, struct17 *arg4, struct127 *arg5, struct126 *arg6) {
    s32 which;
    void *src[10];
    void *dst[10];
    u8 i;

    which = func_150ADA20() & 1;
    src[0] = &D_800A2050;
    src[1] = &D_800A2068;
    src[2] = &D_800A2074;
    src[3] = &D_800A205C;
    for (i = 0; i < 6; i++) {
        src[i + 4] = &D_800A2080[which][i];
        dst[i + 4] = &arg0[i];
    }
    dst[0] = arg1;
    dst[1] = arg2;
    dst[2] = arg3;
    dst[3] = arg4;
    if (func_1514654C(arg5, arg6, 0, src, dst, 0xA) != 0) {
        arg3->unk0 -= arg2->unk0;
        arg3->unk4 -= arg2->unk4;
        arg3->unk8 -= arg2->unk8;
        return 1;
    }
    return 0;
}
