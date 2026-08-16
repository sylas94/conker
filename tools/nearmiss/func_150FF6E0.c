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
 *
 * ---------------------------------------------------------------------------
 * WAVE 2 (2026-08-14).  BASE RE-CONFIRMED 180 / 348 B (golden 352), bounded 88.
 * ---------------------------------------------------------------------------
 * THE ROTATION IS NOW PINNED TO ONE SLOT.  Listing every temp web in the order
 * the allocator hands out registers (it is NOT program order and it is NOT
 * source order -- the four %hi addresses come first in BOTH builds):
 *   golden  t6,t7,t8,t9 (the four src[] %hi) | t0=&dst | t1=arg2 |
 *           **t2 = A WEB THAT EMITS NOTHING** | t3=which | t4=which*72 |
 *           t5=&D_800A2080 | loop t6,t7,t8,t9,(t0/t1 live->skipped),t2,t3 |
 *           tail t5,t6,t7
 *   live    t6,t7,t8,t9                      | t0=&dst | t1=arg2 |
 *           t2=which | t3=which*72 | t4=&D_800A2080 |
 *           loop t5,t6,t7,t8,t9,(skip t0/t1),t2 | tail t4,t5,t6
 * So the allocator is a round-robin over t0..t9 that skips live registers, and
 * golden burns EXACTLY ONE extra slot between `t1 = arg2` and `t3 = which`.
 * Everything downstream is that one slot, uniformly.  The four %hi webs are
 * unaffected, which is why the offset does not look uniform in the raw diff.
 *
 * MEASURED THIS WAVE (bounded 88, vs the 180 base):
 *  1405  `i = 0; while (i < 6) { ...; i++; }` instead of the `for`.  348 B.
 *        The while form loses the rotated (bottom-test) loop shape entirely.
 *        HARD NEGATIVE -- the `for` is required.
 *   328  adding a DEDICATED `s32 ret;` declared LAST and returning it from an
 *        if/else.  THE FRAME GOES 0x88 -> 0x90 and every home offset moves
 *        (src 0x5c->0x64 etc.).  There is NO usable slack in the temp area:
 *        the local list is EXACTLY which / src[10] / dst[10] / i and any
 *        further auto is fatal.  This kills every "extra variable" theory.
 *   185  reusing `which` as the return value:
 *          `if (...) { ...; which = 1; } else { which = 0; } return which;`
 *        352 B -- THE SIZE FINALLY MATCHES GOLDEN -- but REFUSED: it does not
 *        produce golden's shape.  golden is `li v0,1` ... `b afc`/`move v0,zero`
 *        (return value straight into v0, redundant branch kept); this variant is
 *        `li v1,1` ... `move v1,zero` / `move v0,v1` -- the return web does NOT
 *        coalesce into v0 because `which`'s earlier index range conflicts, so it
 *        buys the right byte count with a `move v0,v1` that golden does not have.
 *        Classic "better size, less like golden".  DO NOT SHIP THIS.
 *        It does prove golden's `return 1;`/`return 0;` are DIRECT returns.
 *   180  `which = func_150ADA20() % 2U;` (the TU's own RNG idiom, cf. `% 3U` in
 *        func_150FF840 and `% 0x9CU` in func_150FED30).  IDENTICAL OUTPUT.
 *   180  `which = func_150ADA20(); which &= 1;` as two statements.  IDENTICAL.
 *   180  building the whole TU WITHOUT the func_150ADA20 s32 shadow (i.e. with
 *        functions.h's u8 declaration, so the u8->s32 widening mask is present).
 *        IDENTICAL OUTPUT -- the "extra folded mask consumes a rotation slot"
 *        theory is DEAD for this function.  (For reference the same build takes
 *        func_150FF840 from 5 to 99, so the shadow is still required TU-wide.)
 *   180  `struct17 *src[10]; struct17 *dst[10];` (with `(struct17 *)` casts on
 *        the four f32 externs) instead of `void *`.  IDENTICAL OUTPUT -- the
 *        element type of the pointer table is not the missing web.
 *
 * STILL OPEN, AND THIS IS THE WHOLE PROBLEM: what source form mints one extra
 * temp web between the src[] stores and the loop preheader while emitting no
 * instruction?  It cannot be a new auto (the frame 0x88 is exact and pins the
 * local list to which/src/dst/i), it cannot be a mask (`&1` at the use site is
 * byte-identical), and it must not be a no-op forcer.
 *
 * RULED OUT BY THE GOLDEN INSTRUCTIONS THEMSELVES (do not re-test):
 *   `dst[0..3] = ...` before the loop -- golden's four `sw` for dst[0..3] are
 *        scheduled AFTER the loop, so they are after it in source too.
 *   swapping the two loop-body statements -- golden stores src[i+4] (a68)
 *        before dst[i+4] (a7c).
 *   `i != 6` -- golden uses `slti at,a0,6`, a signed `<`.
 *   func_1514654C returning u8 -- golden branches on v0 with no `andi`.
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
