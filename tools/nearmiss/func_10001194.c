/* ============================================================================
 * func_10001194  (conker/src/init_1050.c)  --  PARKED at mism=36, 2026-08-21.
 *
 *   python3 tools/fastscore.py init_1050 func_10001194 <this body spliced in>
 *   ->  mism=36   frame=-80   n=163/163
 *   OPT_FLAGS -O2 -g3 (tree default; confirmed correct, see flag sweep below)
 *
 * INSTRUCTION COUNT IS EXACT (163/163) and the FRAME IS EXACT (0x50), as are
 * all four spill slots (0x28 / 0x40 / 0x44 / 0x4C) and the whole control-flow
 * skeleton.  127 of 163 rows are byte-identical after relocation masking.
 * The 36 residual rows form FOUR clusters, and cluster A is the root cause --
 * B and D are its register-numbering wake.
 *
 * This TU has ONE pragma; closing this function takes init_1050 to zero.
 * Its two siblings (func_10001050, func_100010F8) are matched C -- do NOT
 * replace the file wholesale, splice over the pragma line only.
 *
 * ============================ WHAT MOVED THE SCORE ==========================
 * 545 -> 55 -> 38 -> 36.  Three independent levers, all worth banking:
 *
 * 1. THE LOOP MUST BE `i = 0;` BEFORE A GUARDING `if`, then `do/while`.
 *    A plain `for (i = 0; i < count; i++)` is unrolled x4 by IDO (n=203 vs 163,
 *    with an `andi t8,v0,0x3` remainder preamble); golden's loop is not
 *    unrolled.  This is the cookbook law at line 6040 and it held exactly:
 *        for (i = 0; i < count; i++)              545  n=203
 *        i = 0; while (i < count) { ...; i++; }   448  n=199
 *        i = 0; if (n) { for (; i < n; i++) ... } 127  n=167
 *        i = 0; if (n != 0) { do {...} while(i<n); } 55 n=163  <-- exact length
 *
 * 2. STATEMENT ORDER OF THE FOUR "mid" STATEMENTS.  The two D_800354F8/FC
 *    ALIGN16 stores must come BEFORE the `blocks = ... >> 12` computation.
 *    Golden interleaves the ALIGN16 `+0xF` work ahead of the `subu`/`srl`
 *    chain, which is a -g3 line-attribution effect, not a coincidence:
 *        blocks; count; F8; FC   -> 55
 *        F8; FC; blocks; count   -> 38   <-- used here
 *        blocks; F8; FC; count   -> 38
 *        F8; blocks; FC; count   -> 38
 *        F8; blocks; count; FC   -> 53
 *        blocks; F8; count; FC   -> 53
 *        FC; F8; blocks; count   -> 123 (n=167)
 *        F8; FC; count; blocks   -> 168 (n=155)
 *
 * 3. DECLARATION ORDER: `u32 count;` must precede `u32 blocks;`.  Worth 2 rows,
 *    and it is what puts the loop-count spill at 0x4C instead of 0x48.
 *    A search over 260 permutations of the 8 locals found nothing better.
 *
 * ========================== THE 36 REMAINING ROWS ===========================
 * (idx = instruction index; comparison masks relocated fields, so %hi/%lo
 *  symbol NAMES are not being compared -- the ROM gate stays the authority.)
 *
 * --- CLUSTER A (18 rows, idx42-59): THE ROOT CAUSE -------------------------
 * IDO must spend its ONE callee-saved register on a value living across the
 * two func_10003C6C calls.  There are exactly two candidates; golden picks the
 * other one:
 *     golden: $s0 = &D_8002AAE8, and the constant 0x1ECC0 is rematerialised
 *             (`lui a0,0x1 / ori a0,a0,0xECC0`) at BOTH call sites.
 *     ours:   $s0 = 0x1ECC0 (`lui s0 / ori s0` once, then `move a0,s0` twice),
 *             and the array address is rematerialised (`lui at`+`sw v0,N(at)`).
 *
 *   idx    OURS                    GOLDEN
 *   42    lui   s0,0x1        |  lui   $a0,(0x1ECC0 >> 16)
 *   43    ori   s0,s0,0xecc0  |  ori   $a0,$a0,(0x1ECC0 & 0xFFFF)
 *   44    move  a0,s0         |  addiu $a1,$zero,0xFF
 *   45    li    a1,255        |  addiu $a2,$zero,0x3
 *   46    li    a2,3          |  addiu $a3,$zero,0x1
 *   47    li    a3,1          |  jal   func_10003C6C
 *   48    jal   func_10003C6C |  sw    $zero,0x10($sp)
 *   49    sw    zero,16(sp)   |  lui   $s0,%hi(D_8002AAE8)
 *   50    lui   at,0x0        |  addiu $s0,$s0,%lo(D_8002AAE8)
 *   51    sw    v0,0(at)      |  lui   $a0,(0x1ECC0 >> 16)
 *   52    move  a0,s0         |  sw    $v0,0x0($s0)
 *   53    li    a1,255        |  ori   $a0,$a0,(0x1ECC0 & 0xFFFF)
 *   54    li    a2,3          |  addiu $a1,$zero,0xFF
 *   55    li    a3,1          |  addiu $a2,$zero,0x3
 *   56    jal   func_10003C6C |  addiu $a3,$zero,0x1
 *   57    sw    zero,16(sp)   |  jal   func_10003C6C
 *   58    lui   at,0x0        |  sw    $zero,0x10($sp)
 *   59    sw    v0,4(at)      |  sw    $v0,0x4($s0)
 *
 * BEST THEORY: this is a RANKING TIE, not a missing source construct.  Count
 * the instructions each candidate saves:
 *     address in a reg : 2 (lui+addiu) + 1 + 1 = 4   vs  direct: 2 + 2 = 4
 *     constant in a reg: 2 (lui+ori)   + 1 + 1 = 4   vs  remat : 2 + 2 = 4
 * BOTH ARE EXACTLY NET-ZERO.  IDO has no cost reason to prefer either, so the
 * choice falls out of internal value-numbering order, and in an assignment
 * `D_8002AAE8[0] = func_10003C6C(0x1ECC0, ...)` the RHS constant is numbered
 * before the LHS address.  This is the same "loop-invariant ranking tie" that
 * has blocked other functions in this project.  Consistent with that, EIGHT
 * honest spellings of this block all produce the identical wrong choice (see
 * DO-NOT-REPEAT).  If anything cracks it, it will be a general mechanism
 * (the permuter, or a law about IDO's CSE numbering order), not a spelling.
 *
 * --- CLUSTER B (5 rows, idx74-78): WAKE OF A -------------------------------
 * Pure temp-register rotation: identical instructions, identical stack slots,
 * registers shifted by one position in IDO's temp sequence.
 *   74    addu v1,t4,s0  |  addu $v0,$t4,$s0
 *   75    subu t0,t5,v1  |  subu $v1,$t5,$v0
 *   76    move a0,t0     |  or   $a0,$v1,$zero
 *   77    sw   t0,40(sp) |  sw   $v1,0x28($sp)     <- SAME slot 0x28
 *   78    sw   v1,68(sp) |  sw   $v0,0x44($sp)     <- SAME slot 0x44
 * Golden numbers v0 then v1; we number v1 then t0.  Fix cluster A and this
 * should follow for free -- do not chase it directly.
 *
 * --- CLUSTER D (6 rows, idx138-147): WAKE OF A -----------------------------
 * Same story inside the loop body; instructions and slots identical, temps
 * rotated (ours t9/t3/t4/t5, golden t4/t5/t6/t7).
 *   138   lw   t9,0(t1)  |  lw   $t4,0x0($t1)
 *   141   addu v0,t9,a0  |  addu $v0,$t4,$a0
 *   142   lw   t3,0(v0)  |  lw   $t5,0x0($v0)
 *   144   xor  t4,t3,a1  |  xor  $t6,$t5,$a1
 *   145   addu t5,t4,s0  |  addu $t7,$t6,$s0
 *   147   sw   t5,0(v0)  |  sw   $t7,0x0($v0)
 *
 * --- CLUSTER C (7 rows, idx113-123): INDEPENDENT, AND GENUINELY STUCK ------
 * The table-size argument.  Golden does NOT distribute the multiply and uses
 * the ori/xori mask expansion; we distribute and use an and-with-register.
 * Both are 5 instructions, which is why n stays exact.
 *   ours: sll a2,t7,2 / addiu a2,a2,23 / li at,-16 / and t8,a2,at / move a2,t8
 *   gold: addiu a2,t7,2 / sll t8,a2,2 / addiu a2,t8,0xF / ori t9,a2,0xF
 *                                                      / xori a2,t9,0xF
 * Two SEPARATE sub-problems, each individually solvable but not jointly:
 *   * the ori/xori IS reachable -- writing the mask literally as
 *     `((x | 0xF) ^ 0xF)` reproduces golden's `ori`/`xori` exactly.  But every
 *     such spelling still distributes, making the block 4 instructions instead
 *     of 5 and shifting everything after it (score 77-87).
 *   * the un-distributed `addiu a2,t7,2` was NOT reachable: IDO folds
 *     `(x + 2) * 4 + 0xF` into `x*4 + 23` in every spelling tried, including
 *     via an intermediate variable (IDO forward-propagates it).
 * A spelling that both keeps `+2` live AND uses the literal mask would close
 * this cluster; I could not find one.
 *
 * ==================== DO NOT REPEAT (all measured, -O2 -g3) =================
 * Framebuffer block (cluster A) -- ALL give the same wrong $s0 choice:
 *   D_8002AAE8[0]/[1] = call;                      36  <-- best, and natural
 *   both calls on ONE source line                  36  (no -g3 line effect)
 *   blank line between the two calls               36
 *   decimal 126144/255 instead of hex              36
 *   mixed hex/decimal between the two calls        36
 *   *(D_8002AAE8 + 0) / *(D_8002AAE8 + 1)          36
 *   s32 *fb = D_8002AAE8; fb[0]/fb[1]              46  frame 0x58 WRONG (+1 spill)
 *   fb = &D_8002AAE8[0]                            46  frame 0x58 WRONG
 *   fb assigned BETWEEN the two calls              46  frame 0x58 WRONG
 *   s32 tmp = call; D_8002AAE8[0] = tmp; ...       46  frame 0x58 WRONG
 *   for (i = 0; i < 2; i++) D_8002AAE8[i] = call; 198  n=159 (collapses)
 *   i=0; do { D_8002AAE8[i]=call; i++; } while(i<2); 198 n=159
 *   func_10003C6C((void *)0x1ECC0, ...)          CCFAIL "Constants must have
 *                                                 arithmetic type"
 * Table-size argument (cluster C):
 *   ALIGNU16((count + 1) * 4)                      36  <-- best
 *   ALIGNU16((blocks + 2) * 4)                     36
 *   ((count+1)*4 + 0xF) & 0xFFFFFFF0               36
 *   ALIGNU16((blocks + 2) * sizeof(s32))           36
 *   size = (count+1)*4;  then ALIGNU16(size)       36  (propagated, no effect)
 *   size = count+1;      then ALIGNU16(size*4)     36
 *   ALIGN16 (signed) instead of ALIGNU16           82  (loses the unsigned mask)
 *   ((((count + 1) * 4) + 0xF) | 0xF) ^ 0xF        77  (right ori/xori, 1 short)
 *   ((((blocks + 2) * 4) + 0xF) | 0xF) ^ 0xF       77
 *   size = blocks+2; ((size*4 + 0xF) | 0xF) ^ 0xF  77
 *   ALIGNU16((count + 1) << 2)                    126  n=167
 *   ALIGNU16((blocks + 2) << 2)                   126  n=167
 *   ALIGNU16(4 * (blocks + 2))                    138  n=167
 *   u32 nent = blocks+2, loop bound `nent - 1` 126-135  n=167.  IDO materialises
 *       nent and does NOT reassociate the bound back to blocks+1, so golden's
 *       bound really is a `count = blocks + 1` local.
 * Loop-count local:
 *   `count` local, bound `count`                   36  <-- best
 *   no local, bound written `blocks + 1`      82-137
 * romBase:
 *   s32 romBase = (s32)D_42450;  (local)           36  <-- best; this is what
 *       puts &D_42450 in $s0 for the loop, per cookbook line 640 (hoist the
 *       base above the loop or IDO keeps it on the stack)
 *   `(s32)D_42450` written out at each use        184  (spilled to stack)
 * OPT_FLAGS sweep on the best source (this TU has NO Makefile override, and
 * none is justified -- the tree default wins by a mile):
 *   -O2 -g3    36        <-- tree default, correct
 *   -O2       163  n=164
 *   -O1       291  n=176
 *   -g        402  n=187
 *   -O2 -g1 / -O2 -g2 / -O3 / -Wo,-loopunroll,0 : asm-processor rejects
 * NOTE: the Makefile's `$(LOOP_UNROLL)` on line 232 is a DANGLING HOOK -- the
 * variable is never assigned anywhere in the tree, so it expands to nothing and
 * fastscore's flag set is faithful.  The x4 unroll seen at first is real IDO
 * behaviour and had to be defeated in the source, not with a flag.
 *
 * ============================ SEMANTICS RECOVERED ===========================
 * Settled; do not re-derive:
 *   - D_8000030C is osResetType: 0 = cold boot -> clear from D_80043B40, else
 *     warm boot -> clear only from D_800E9D10.  Both clear up to 0x80400000.
 *   - $s0 carries `0x80400000 - (s32)&D_80043B40` across the bzero and into
 *     both osInval*Cache calls; it must be a LOCAL assigned in BOTH arms of the
 *     if/else.  IDO does no partial-redundancy elimination, so hoisting it to a
 *     single assignment before the `if` does NOT reproduce golden.
 *   - D_42450 / D_19EA88 / D_151FA130 are absolute link-time symbols from
 *     conker/undefined_syms_auto.txt (0x42450, 0x19EA88, 0x151FA130).  They have
 *     no declaration in variables.h, hence the file-local `extern u8 X[];`.
 *   - `blocks` = number of 4 KiB chunks in the game overlay,
 *     ((&D_151FA130 - &func_15000000) + 0xFFF) >> 12.  The offset table has
 *     `count + 1` == `blocks + 2` entries and is decrypted in place by
 *     xor 0x8039CCCA then rebased by + &D_42450.
 *   - ALIGN16 vs ALIGNU16 in macros.h are NOT interchangeable here: the signed
 *     form emits `and` against -0x10 held in a register (what golden uses for
 *     the two D_800354F8/FC stores), the unsigned form is what golden wants for
 *     the byte count.  Getting this backwards costs 46 rows.
 *   - The prologue's `sw $a0,0x50($sp)` is ordinary IDO -g3 argument homing for
 *     an otherwise-unused parameter: the MATCHED sibling func_100010F8 in this
 *     same TU has the identical `addiu sp,-0x20 / sw ra / sw a0,0x20(sp)`
 *     shape.  `arg0` is genuinely unread in the body.
 * ==========================================================================*/

extern u8 D_42450[];
extern u8 D_19EA88[];
extern u8 D_151FA130[];
extern void *allocate_memory(s32, s32, s32, s32);
extern void func_10006240(void *, s32 *, u32);
extern void func_10004074(void *);
extern void func_10003BD0(void);
extern void func_10005BE0(void);
extern void func_15007830(void);

void func_10001194(s32 arg0) {
    u32 count;
    u32 blocks;
    s32 romAddr;
    void *ram;
    u32 size;
    u32 i;
    s32 bssSize;
    s32 romBase;
    func_10005218();
    if (D_8000030C == 0) {
        bssSize = 0x80400000 - (s32)&D_80043B40;
        bzero(&D_80043B40, bssSize);
    } else {
        bzero(&D_800E9D10, 0x80400000 - (s32)&D_800E9D10);
        bssSize = 0x80400000 - (s32)&D_80043B40;
    }
    osInvalICache(&D_80043B40, bssSize);
    osInvalDCache(&D_80043B40, bssSize);
    func_10003920();
    func_10003930();
    func_10003BD0();
    func_1000709C();
    D_8002AAE8[0] = func_10003C6C(0x1ECC0, 0xFF, 3, 1, 0);
    D_8002AAE8[1] = func_10003C6C(0x1ECC0, 0xFF, 3, 1, 0);
    osCreateViManager(OS_PRIORITY_VIMGR);
    romBase = (s32)D_42450;
    func_10004514(romBase, &D_80082B20, 0x10, 1);
    romAddr = D_80082B20 + romBase;
    size = (s32)D_19EA88 - romAddr;
    ram = allocate_memory(size, 1, 2, 0);
    func_10004514(romAddr, ram, size, 1);
    func_10006240(ram, &D_80082B20, D_8003809C);
    func_10004074(ram);
    D_800354F8 = ALIGN16(&D_80033330);
    D_800354FC = (s32 *)ALIGN16(&D_80032B30);
    blocks = ((u32)((s32)D_151FA130 - (s32)func_15000000) + 0xFFF) >> 12;
    count = blocks + 1;
    func_10004514(romBase + 4, D_800354FC, ALIGNU16((count + 1) * 4), 1);
    i = 0;
    if (count != 0) {
        do {
            D_800354FC[i] = (D_800354FC[i] ^ 0x8039CCCA) + romBase;
            i++;
        } while (i < count);
    }
    D_8003BE74 = 0;
    func_10005B04(0xEB);
    func_10001420();
    func_10005BE0();
    func_15007830();
}
