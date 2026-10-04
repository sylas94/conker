/* ============================================================================
 * func_151B8908  (game_1E58B0.c)  --  P A R K E D  at mism 22,  2026-08-21.
 *
 * FILE KIND: BODY-TO-SPLICE.  Everything below the banner is LIVE C.  To score
 * it, replace EXACTLY this one line in conker/src/game_1E58B0.c
 *     #pragma GLOBAL_ASM("asm/nonmatchings/game_1E58B0/func_151B8908.s")
 * with the whole of this file from the first `typedef` onward.  Do NOT replace
 * the TU wholesale: its sibling func_151B86F4 is CLOSED and live, and IDO's
 * codegen for this function is TU-context dependent (isolated it compiles to
 * 144 instructions, in-file to the golden 142 -- so an isolated score, and
 * therefore the decomp-permuter, is measuring the wrong function.  That is why
 * no permuter run is recorded here).
 *
 * MEASUREMENT (in-file, tools/fastscore.py, OPT_FLAGS -O2 -g3):
 *     mism = 22     n = 142/142     frame = -176 (0xB0)   == golden exactly
 * Everything except register NAMES is already golden: the length, the frame,
 * every stack offset, every immediate, every branch, every relocation site.
 *
 * ================= WHAT IS LEFT: A UNIFORM +1 TEMP ROTATION =================
 * All 22 rows are one fault.  From idx106 onward our t-register allocation is
 * golden's rotated back by exactly one slot; the pool order measured here is
 *     t4 -> t6 -> t7 -> t5 -> t9 -> t8 -> t0 -> t3 -> t2 -> t1 -> (t4)
 *
 *   idx  ours                       golden
 *   106  or    $t4,$v0,$v1          or    $t6,$v0,$v1
 *   107  ori   $t6,$t4,0xC000       ori   $t7,$t6,0xC000
 *   109  or    $t7,$t6,$at          or    $t5,$t7,$at
 *   110  lw    $t4,0xB0($sp)        lw    $t6,0xB0($sp)
 *   112  or    $t5,$t7,$at          or    $t9,$t5,$at
 *   113  addiu $t9,$zero,6          addiu $t8,$zero,6
 *   114  addiu $t8,$zero,5          addiu $t0,$zero,5
 *   115  addiu $t0,$zero,-1         addiu $t3,$zero,-1
 *   116  addiu $t3,$zero,-1         addiu $t2,$zero,-1
 *   117  addiu $t2,$zero,-1         addiu $t1,$zero,-1
 *   118  addiu $t1,$zero,0xFF       addiu $t4,$zero,0xFF
 *   119  sw    $t5,0x94($sp)        sw    $t9,0x94($sp)
 *   120-127  the 0x9C..0xA2 byte stores, same rotation
 *   128  lbu   $t6,0xC($t4)         lbu   $t7,0xC($t6)
 *   131  sw    $t6,0x10($sp)        sw    $t7,0x10($sp)
 *   132  lbu   $t7,1($t4)           lbu   $t5,1($t6)
 *   136  sw    $t7,0x14($sp)        sw    $t5,0x14($sp)
 *
 * The phase is IDENTICAL to golden up to and including idx105 (the second
 * `andi $t1,$v0,1`).  So GOLDEN MINTS EXACTLY ONE MORE VALUE NUMBER THAN WE DO,
 * AND IT DOES SO BETWEEN THE SECOND `andi` AND THE `or $t6,$v0,$v1` -- i.e.
 * inside the second `if` body, or at the leaves of the flag expression.  That
 * window is only four source tokens wide, which is what makes this hard.
 *
 * The position is PROVEN, not guessed.  A free value number placed just BEFORE
 * the second andi (any redundant mask on the RNG result) takes the whole
 * function to mism 2, with the only surviving rows being that andi's own
 * register and its branch:
 *     idx100  ours andi $t4,$v0,1   golden andi $t1,$v0,1
 *     idx101  the matching beqz
 * i.e. one slot too early.  A free value number one slot LATER is the entire
 * remaining fault.
 *
 * ================= DO-NOT-REPEAT: EVERY SPELLING MEASURED ===================
 * (all in-file, all n=142/142 unless noted; base = the source below = 22)
 *
 *   -- probes that PROVE the position (diagnostics, NOT shippable) --
 *   (func_150ADA20() & 0xFF) & 1   as the 2nd if's test .................. 2
 *   (func_150ADA20() & 1) & 0xFF   as the 2nd if's test .................. 2
 *   (u8)(func_150ADA20() & 1)      as the 2nd if's test .................. 2
 *   ((func_150ADA20() & 1) & 0xFFFF) ..................................... 2
 *   ((func_150ADA20() & 1) & 1) .......................................... 2
 *   same free mask on the FIRST if instead ............................... 4
 *   same free mask on BOTH ifs ........................................... 26
 *   free mask on the table index ......................................... 76
 *
 *   -- flag-word spellings (all inert) --
 *   temp_v0 | temp_v1 | 0xC000 | 0x40000 | 0x800000   (base) ............. 22
 *   (temp_v0 | temp_v1) | 0xC000 | 0x40000 | 0x800000 .................... 22
 *   ((temp_v0|temp_v1) | 0xC000 | 0x40000) | 0x800000 .................... 22
 *   temp_v1 | temp_v0 | ...  (operands swapped -- IDO canonicalises) ..... 22
 *   temp_v0 | (temp_v1 | 0xC000) | ... ................................... 22
 *   temp_v0 | temp_v1 | (0x4000 | 0x8000) | ... .......................... 22
 *   (s32)(temp_v0 | temp_v1) | ... ....................................... 22
 *   (temp_v0|temp_v0) | ... .............................................. 22
 *   temp_v1 |= temp_v0;  then  unk58 = temp_v1 | ... ..................... 22
 *   unk58 = a|b|0xC000|0x40000;  unk58 |= 0x800000; ...................... 33
 *   unk58 = a|b|0xC000;  unk58 |= 0x40000;  unk58 |= 0x800000; ... 75 (n=146)
 *   unk58 = a|b;  then three |= ................................... 74 (n=146)
 *   unk58 = 0xC000|0x40000|0x800000;  unk58 |= a;  unk58 |= b; ........... 34
 *   unk58 = a; unk58 = unk58 | b | consts; ............................... 22
 *
 *   -- identity ops at temp_v0's LEAF (all folded at parse; no value number) --
 *   & -1 / | 0 / + 0 / * 1 / / 1 / ^ 0 / >> 0 / << 0 / & 0xFFFFFFFF ...... 22
 *   the same on temp_v1's leaf ........................................... 22
 *
 *   -- if-statement shapes --
 *   `!= 0` on the 2nd / 1st / both tests ................................. 22
 *   ternary for the 2nd if ............................................... 22
 *   `% 2U` for the 2nd / 1st / both tests ................................ 22
 *   `& 1U` ............................................................... 22
 *   `1 << 7` instead of 0x80 ............................................. 22
 *   arms swapped with `== 0` ............................................. 25
 *   arms swapped with `!` ................................................ 25
 *   `temp_v0 = 0;` then a bare `if` (no else) ............................ 93
 *   same on the first flag ............................................... 43
 *   inline ternaries for both flags (temps, not named locals) ............ 26
 *   inline ternary for the 2nd flag only ................................. 24
 *   inline ternary for the 1st flag only ................................. 26
 *   `temp_v0 = temp_v0;` after the 2nd if ................................ 22
 *   `temp_v0 = 0x80 & 0xFF;` / `= (u8)0x80;` in the arm .................. 22
 *
 *   -- narrow types on the flag variables --
 *   temp_v0 as u8 / u16 / u32 / s16 ...................................... 22
 *   temp_v0 as s8 ........................................................ 23
 *   (u8)temp_v0 or (temp_v0 & 0xFF) in the OR (emits an andi) ............ 35
 *
 *   -- dead stores (IDO's DSE removes them AND mints nothing) --
 *   `sp3C.unk58 = 0;` before the OR / after the ifs ...................... 22
 *   `sp3C.unk60 = 0;` before the OR ...................................... 22
 *   `sp3C.unk1D = sp3C.unk1D;` before the OR ............................. 22
 *   `sp3C.unk58 = 0;` before the 2nd if .................................. 43
 *
 *   -- statement moves / assignment forms elsewhere --
 *   `sp3C.unk5C = 0;` moved before the flag word ......................... 24
 *   unk28/unk2C written as two statements instead of chained ............. 22
 *   unk3C/unk48 chained (`unk48 = unk3C = ...`) ................... 180 (n=150)
 *   dropping `sp3C.unk66 = 0xFF;` / `sp3C.unk60 = 6;` .................... 32
 *   `ret = func_15130280(...)` instead of a bare call .................... 22
 *   a pointer alias `p = arg0;` used for all three arg0 reads ............ 22
 *   a copy variable `temp_v2 = temp_v0;` before the OR ................... 22
 *
 * CONCLUSION ON THE BLOCKER: value numbers are minted only by real operations
 * and by redundant NARROWING masks.  Identity arithmetic, casts, copies and
 * dead stores are all folded before numbering, and every narrowing mask that
 * can be written in this window belongs to the *condition* subtree, which is
 * numbered BEFORE the surviving andi (IDO rewrites `(x&1)&0xFF` into a single
 * new mask web and lets the old one die, so the emitted andi gets the LATER
 * number -- that is why every condition probe lands at 2 and not 0).  There is
 * no construct left in the four-token window that mints without emitting.
 * A shippable fix therefore needs a source construct that is NOT reachable from
 * this shape -- most likely a different spelling of the two conditional bits
 * altogether.  Do not spend another wave on the flag expression itself.
 *
 * ================= THE OTHER QUESTION, AND WHY IT IS *NOT* A STOP ===========
 * Golden's local area is 144 bytes (0x20..0xAF) but only 140 are accounted for
 * by [descriptor 0x70][table 0x10][3 scalars].  The descriptor sits at 0x3C,
 * not 0x40, so FOUR BYTES LIVE ABOVE IT, i.e. a 4-byte local declared FIRST.
 * This is NOT the banned "declare N unreferenced bytes" case: three DIFFERENT
 * honest, fully-referenced readings reproduce the object bit for bit, and all
 * score the same 22:
 *     (a) `s32 rnd;` holding the RNG draw for the table index   <-- SHIPPED
 *     (b) `void *ret;` taking func_15130280's discarded result
 *         (precedent: game_1D0840.c func_151A4638 declares `struct260 *ret;`
 *          first, ahead of its spawn-descriptor struct)
 *     (c) padding the descriptor typedef to 0x74 (`u8 pad67[0xD]`)
 * (a) was shipped because the variable is READ, not merely assigned, and
 * because 0x70 is the descriptor size proven by func_15130280's own
 * `memcpy(obj + 0x10, arg0, 0x70)` and used by both matched siblings
 * (game_15D730.c Struct15131EE4Local, game_17CAF0.c Local15153634Spawn).
 * Reading (c) would contradict those two matched files, so it was rejected.
 * Whichever reading a future wave prefers, the object is identical -- this
 * question is CLOSED and is not the blocker.
 *
 * ================= WHAT IS ALREADY PROVEN CORRECT ===========================
 * - The descriptor is the same 0x70 spawn block as game_15D730.c's
 *   func_15131EE4 and game_17CAF0.c's func_15153634; only unk62/63/64 had to
 *   be re-typed s8 (golden materialises them with `addiu $t,$zero,-1`, which
 *   is the SIGNED spelling; a u8 field would emit `addiu $t,$zero,0xFF`).
 * - D_800AA4B8 is a 4-entry s32 table {0x60,0x61,0x62,0x63} (see
 *   conker/asm/data/24EF50.rodata.s); golden copies all 16 bytes to the stack
 *   with one struct assignment and then indexes the COPY, which is why it
 *   materialises the address once with lui+addiu instead of four %hi/%lo pairs.
 * - The flag word is 0x84C000 with two random bits; the three constants must be
 *   three SEPARATE `|` terms (golden emits ori 0xC000, then lui 0x40000 + or,
 *   then lui 0x800000 + or -- IDO does not fold constants across a `|` chain).
 * - unk28 and unk2C take the same value via a CHAINED assignment (golden stores
 *   0x68 before 0x64), matching game_1D0840.c func_151A4638 and
 *   game_17CAF0.c func_15153634.
 * ==========================================================================*/

typedef struct {
    s32 unk00;
    s32 unk04;
    s16 unk08;
    s16 unk0A;
    s32 unk0C;
    s32 unk10;
    u8 unk14;
    u8 unk15;
    u8 unk16;
    u8 unk17;
    u8 unk18;
    u8 unk19;
    u8 unk1A;
    u8 unk1B;
    u8 unk1C;
    u8 unk1D;
    s16 unk1E;
    s16 unk20;
    s16 unk22;
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    struct17 unk30;
    struct17 unk3C;
    struct17 unk48;
    f32 unk54;
    s32 unk58;
    s32 unk5C;
    u8 unk60;
    u8 unk61;
    s8 unk62;
    s8 unk63;
    s8 unk64;
    u8 unk65;
    u8 unk66;
    u8 pad67[9];
} Struct151B8908;

typedef struct {
    s32 unk0[4];
} Tbl151B8908;

typedef struct {
    u8 pad0[1];
    u8 unk1;
    u8 pad2[0xA];
    u8 unkC;
    u8 pad0D[0x2B];
    struct17 unk38;
} Arg151B8908;

extern Tbl151B8908 D_800AA4B8;
extern void *func_15130280(void *, u8, s32, s32, u8, s32);

void func_151B8908(Arg151B8908 *arg0) {
    s32 rnd;
    Struct151B8908 sp3C;
    Tbl151B8908 sp2C;
    s32 temp_v0;
    s32 temp_v1;

    sp2C = D_800AA4B8;
    rnd = func_150ADA20();
    sp3C.unk1D = sp2C.unk0[rnd & 3];
    sp3C.unk08 = 0x1303;
    sp3C.unk00 = 0x200005;
    sp3C.unk04 = 0;
    sp3C.unk0A = 0x12C;
    sp3C.unk0C = 0;
    sp3C.unk10 = 0;
    sp3C.unk14 = 0xFF;
    sp3C.unk15 = 0xFF;
    sp3C.unk16 = 0xFF;
    sp3C.unk17 = 0xFF;
    sp3C.unk18 = 0xFF;
    sp3C.unk19 = 0xFF;
    sp3C.unk1A = 0xFF;
    sp3C.unk1B = 0xFF;
    sp3C.unk1C = 0xFF;
    sp3C.unk28 = sp3C.unk2C = (func_150ADA68() * 500.0f) + 900.0f;
    sp3C.unk30 = arg0->unk38;
    sp3C.unk3C = *(struct17 *)&D_800A5480;
    sp3C.unk48 = *(struct17 *)&D_800A5480;
    sp3C.unk1E = 1;
    sp3C.unk20 = 0xFF;
    sp3C.unk22 = 1;
    sp3C.unk54 = 0.0f;
    sp3C.unk24 = 1.0f;

    if (func_150ADA20() & 1) {
        temp_v1 = 0x40;
    } else {
        temp_v1 = 0;
    }
    if (func_150ADA20() & 1) {
        temp_v0 = 0x80;
    } else {
        temp_v0 = 0;
    }
    sp3C.unk58 = temp_v0 | temp_v1 | 0xC000 | 0x40000 | 0x800000;
    sp3C.unk60 = 6;
    sp3C.unk61 = 5;
    sp3C.unk62 = -1;
    sp3C.unk63 = -1;
    sp3C.unk64 = -1;
    sp3C.unk65 = 0;
    sp3C.unk5C = 0;
    sp3C.unk66 = 0xFF;

    func_15130280(&sp3C, 1, 0, 0, arg0->unkC, arg0->unk1);
}
