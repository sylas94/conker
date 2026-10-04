/* tools/nearmiss/func_15188F84.c -- game_1B5CC0, 101 instructions, frame 0x30
 *
 * WHY THIS FUNCTION: it is one of the six named in the func_15113218 owner ruling as "the only
 * other code written against these tables, and the only realistic source of a naming for the
 * reserved block". func_15113218 is at SCORE 0 and is parked ONLY because 20 bytes of its
 * frame are locals it cannot name; the ruling is that the bar is evidence that NAMES them.
 * Five of those six siblings had never been attempted. This is the smallest (101 instrs).
 * The others: func_151135C4 (132, same TU as func_15113218), func_150F2A60 (139),
 * func_15112A80 (448), func_150F34F4 (959), func_150BDB70 (parked at 287, len_delta -12).
 *
 * THE STRUCT MODEL IS FREE. game_1B5CC0.c already declares `Node1518894C` and it already has
 * every field this function touches: unk1/unk2 (u8), unk8 (void *), unk10 (s32). Do not
 * re-derive it. `D_800BE9C0` (u8) and `D_800DBEF4` (struct131 *) are already in variables.h.
 *
 * ---------------------------------------------------------------- DECODE (from golden asm)
 * FRAME 0x30, NO STACK LOCALS. Saved: s0 0x14, s1 0x18, s2 0x1C, s3 0x20, s4 0x24, s5 0x28,
 * ra 0x2C. 0x00-0x0F is the outgoing-arg area for the bcopy call; 0x10-0x13 is pad.
 *
 * PROLOGUE:
 *      s2 = arg0                       a3 = &D_800DBEE8
 *      t1 = arg0->unk1  -> s3          t2 = D_800BE9C0  (u8 global)
 *      t3 = t2 * t1                    s5 = (t2 ^ 1) * t1
 *      t0 = 0xA0 (160)                 v1 = 0 (the search index)   a1 = 0
 *      blez D_800DBEE8[a1] -> skip the search loop entirely
 * NOTE `a1` is set to 0 and NEVER incremented, yet `sll $t6,$a1,1` is recomputed INSIDE the
 * loop -- so the source indexes D_800DBEE8 with something the compiler knows is 0, not with
 * the loop counter. Reproducing that (rather than hoisting D_800DBEE8[0]) is likely to matter.
 *
 * SEARCH LOOP (v1 = index, v0 = cursor stepping by 4, first member read with lhu):
 *      v0 = *(D_80089240)                     ; D_80089240 is a POINTER variable
 *      loop: if (arg0->unk10 == (s32)&D_800DBEF4[v0->unk0]) break;   ; *160, so struct131=160
 *            v1++; v0 += 4;
 *      while (v1 < D_800DBEE8[a1]);
 *
 * NOT FOUND (v1 == D_800DBEE8[0]):  arg0->unk2 = 0;  return;   (b .L151890F4, sb in the slot)
 *
 * FOUND:
 *      t5   = *(D_80089240)                       ; reloaded, not reused
 *      t8   = *(u16 *)(t5 + v1 * 4)               ; the found element's first member
 *      t5   = D_80089250[t2]                      ; array of pointers indexed by the u8 global
 *      t6   = *(void **)t5
 *      s4   = t6 + (t8 << 6)                      ; a 64-byte-element base
 *      s1   = t3  (= D_800BE9C0 * arg0->unk1)
 *      blez s3 -> skip the copy loop
 *
 * COPY LOOP (v1 = j from 0, s0 = j+1, s1 = k):
 *      if (arg0->unk1 == j + 1)  src = s4;
 *      else                      src = arg0->unk8 + ((j + s5 + 1) << 6);
 *      bcopy(src, arg0->unk8 + (s1 << 6), 0x40);
 *      j = j + 1;  s1++;
 *      while (j != arg0->unk1);
 * The `lw $v0,0x8($s2)` (arg0->unk8) is loaded on BOTH arms of the if and is the b-delay-slot
 * fill on the taken arm -- i.e. the source reads arg0->unk8 once per iteration, after the if.
 *
 * TAIL: arg0->unk1 is RELOADED (lbu 0x1) at the bottom of the loop body, so the compare below
 * re-reads it; on the skipped-loop path the prologue's t1 is still live.
 *      if (arg0->unk1 != arg0->unk2) { arg0->unk2 = arg0->unk2 + 1; }
 *
 * ---------------------------------------------------------------- STILL TO PIN
 *  - the element type behind D_80089240 (4-byte stride, first member u16) and D_80089250
 *    (array of pointers indexed by the D_800BE9C0 byte, each pointing at a struct whose first
 *    word is a pointer). Naming THOSE is the point of the exercise -- they are the tables
 *    func_15113218 is written against.
 *  - whether `a1` is a real variable that is provably 0 or an artefact of a hoisted index.
 *
 * ---------------------------------------------------------------- MEASURED 2026-08-25
 * The draft below is a FIRST CUT, measured once, NOT reduced:
 *      mism=161   frame=-48 (0x30, EXACT on the first try)   n=94/101 (SEVEN SHORT)
 * Frame exact with no stack locals confirms the register/local model above is right. The
 * seven missing instructions are all one fact, and it is the `a1` oddity flagged above:
 *
 *   GOLDEN MATERIALISES `&D_800DBEE8` INTO $a3 IN THE PROLOGUE (lui/addiu, idx2-3) AND KEEPS
 *   IT LIVE, recomputing `a3 + (a1 << 1)` and re-reading `lhu 0(t7)` on EVERY iteration of the
 *   search loop. Our `D_800DBEE8[0]` lets IDO hoist the whole thing to one load, so we lose
 *   the address materialisation, the per-iteration index, and the reload.
 *
 * ---------------------------------------------------------------- CONFIRMED, 161 -> 96
 * The index-variable diagnosis is RIGHT and is now applied in the C below:
 *      D_800DBEE8[0]       (literal)   mism=161   n=94/101   (SEVEN SHORT -- bound hoisted)
 *      D_800DBEE8[idx]   (s32 local) mism=96    n=102/101  (ONE OVER)   <-- parked
 *      ...idx as u8 / s16                identical, 96 -- the TYPE does not matter, only that
 *                                        it is a variable IDO will not fold
 *      u16 *tbl = D_800DBEE8; tbl[0]     101, n=100/101 -- keeps the address live but still
 *                                        hoists the bound; the SUBSCRIPT is what matters
 * A plain local initialised to 0 is enough; no opaque source is needed. That recovers the
 * prologue `lui/addiu a3,%hi/%lo(D_800DBEE8)`, the per-iteration `sll/addu`, and the reload.
 *
 * ---------------------------------------------------------------- THEN 96 -> 93, LENGTH EXACT
 * Second divergence, also confirmed: golden multiplies with $t1 (the freshly loaded
 * arg0->unk1) and only copies into $s3 AFTERWARDS, where we copied into a named `n` first and
 * multiplied with the copy. Measured, all frame -0x30:
 *      A  `n = arg0->unk1;` then `g * n`, `(g^1) * n`, loop `j < n` ...... 97   n=102/101
 *      B  keep `n`, but multiply with arg0->unk1 directly ................ 121  n=105/101
 *      D  same as B with `n` assigned after the products ................. 121  n=105/101
 *      C  NO `n` LOCAL AT ALL -- arg0->unk1 everywhere ................... 93   n=101/101
 * C reached exact length (101/101) at 93 -- but see below, DROPPING `n` WAS THE WRONG READ.
 *
 * ---------------------------------------------------------------- THEN 93 -> 78, AND WHY
 * Counting the prologue stores settled it: **GOLDEN SAVES SIX callee-saved registers**
 * (s0 0x14, s1 0x18, s2 0x1C, s3 0x20, s4 0x24, s5 0x28, + ra 0x2C). Variant C saves only
 * FIVE -- dropping `n` cost us `$s3 = arg0->unk1`, and C bought its exact length by spending
 * that slot elsewhere. So `n` is REAL; the earlier A variant was worse for a different reason.
 *
 * The discriminator is THE TAIL, not the products. Measured, all with `n = arg0->unk1` and the
 * products computed from `n`:
 *      tail `if (n != arg0->unk2)`            ..... 108  n=99/101   (two SHORT)
 *      tail `if (arg0->unk1 != arg0->unk2)`   .....  78  n=101/101  <-- PARKED
 *      `n` declared s32 instead of u8         ..... 117  n=103/101, frame 0x38 (WRONG)
 *      loop `j != n` instead of `j < n`       .....  78  (identical -- byte-neutral)
 * Golden RELOADS `lbu $t1,0x1($s2)` at the bottom of the copy loop for that final compare, so
 * the tail must re-read arg0->unk1 rather than reuse `n`. `n` MUST be u8: as s32 the frame
 * grows to 0x38.
 *
 * PROGRESSION: 161 (7 short) -> 96 (1 over) -> 93 (exact, but 5 saved regs) -> **78 (exact
 * length, exact frame, and the right SIX saved registers)**.
 *
 * ---------------------------------------------------------------- NEXT
 * 78 rows of pure register assignment. Work front-to-back; the first divergence cascades.
 * The mapping is now one consistent rotation, not a structural problem:
 *      golden:  s2=arg0   s3=n   s4=found base   s5=lim   s1=k   s0=j+1   (g stays in $t2)
 *      ours:    s3=arg0   s5=n   ...             ...      s1=?   ...      g SPILLED to $s2
 * The clearest single defect is that WE PUT `g` (D_800BE9C0) IN A SAVED REGISTER and golden
 * keeps it in $t2. Nothing between its read and its last use (`D_80089250[g]`) contains a
 * call, so a temp ought to suffice.
 *
 * BUT THE OBVIOUS FIX IS REFUTED -- reading the global directly does NOT demote it, it costs
 * an instruction (all frame -0x30):
 *      `u8 g` local used at all three sites ................... 78   n=101/101  <-- PARKED
 *      `g` for the products, D_800BE9C0 direct at the index ... 78   (identical)
 *      D_800BE9C0 direct at ALL three sites .................. 95   n=102/101
 *      `g` only at the index, direct in the products .......... 97   n=102/101
 * So the `g` local is load-bearing and its promotion to a saved register is NOT driven by how
 * many times the source names the global. Do not re-run that sweep. The next thing to try is
 * the OTHER end -- what forces arg0->unk1 out of $s3 -- e.g. declaration order of n/g/k/lim,
 * or giving the found-base `src` and `k` their live ranges in golden's order. This is now an
 * ordinary GRA-rotation residue; if it resists, the permuter is a reasonable next call here
 * because the length AND frame are both already exact (that is its good case).
 *
 * Treat the DECODE above as the reliable part; the C below is measured but NOT reduced.
 */

typedef struct Elem89240 {
    u16 unk0;
    char pad2[2];
} Elem89240;

typedef struct Tbl89250 {
    void *unk0;
} Tbl89250;

extern u16       D_800DBEE8[];
extern Elem89240 *D_80089240;
extern Tbl89250  *D_80089250[];

void func_15188F84(Node1518894C *arg0) {
    Elem89240 *p;
    u8 *src;
    s32 idx;
    s32 i;
    s32 j;
    s32 k;
    s32 lim;
    u8 n;
    u8 g;

    g = D_800BE9C0;
    n = arg0->unk1;
    lim = (g ^ 1) * n;
    k = g * n;
    idx = 0;
    i = 0;
    if (D_800DBEE8[idx] > 0) {
        p = D_80089240;
        do {
            if (arg0->unk10 == (s32)&D_800DBEF4[p->unk0]) {
                break;
            }
            i++;
            p++;
        } while (i < D_800DBEE8[idx]);
    }
    if (i == D_800DBEE8[idx]) {
        arg0->unk2 = 0;
        return;
    }
    src = (u8 *)D_80089250[g]->unk0 + (D_80089240[i].unk0 << 6);
    for (j = 0; j < n; j++) {
        if (n == (j + 1)) {
            bcopy(src, (u8 *)arg0->unk8 + (k << 6), 0x40);
        } else {
            bcopy((u8 *)arg0->unk8 + ((j + lim + 1) << 6),
                  (u8 *)arg0->unk8 + (k << 6), 0x40);
        }
        k++;
    }
    if (arg0->unk1 != arg0->unk2) {
        arg0->unk2 = arg0->unk2 + 1;
    }
}
