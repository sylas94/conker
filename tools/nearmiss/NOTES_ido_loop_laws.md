# Four IDO laws found closing func_1508F060 + func_15017640  (2026-08-25)

Both functions are now byte-perfect and in the tree; the ROM gate is green
(4cbadd3c4e0729dec46af64ad018050eada4f47a).  `game_44A90.c` is retired (0 pragmas).
The parked `tools/nearmiss/func_15017640.c` is deleted -- it is solved.

These are general.  Apply them before inventing a new spelling.

--------------------------------------------------------------------- LAW A
**`addiu $vN, $zero, k` + `sll` + `addu` in front of a run of stores is the
signature of a LOOP, not of constant subscripts.**

IDO -O2 expands a constant-trip-count loop over a global array as

    peel   (n % 4) iterations with absolute %hi/%lo addressing
    then   ONE unrolled block of 4 through a COMPUTED base:
               addiu $vN, $zero, <peelcount>
               sll   $t,  $vN, <log2 stride>
               addu  $base, $t, <array>
           with the four bodies emitted in the order +1, +2, +3, +0.

func_1508F060 golden:

    lui/sb  D_800D246D              <- peeled i=0
    lui/sb  D_800D247D              <- peeled i=1
    addiu v0,zero,2 ; lui/addiu t7,D_800D2460 ; sll t6,v0,4 ; addu v1,t6,t7
    sb zero,0x1D(v1) 0x2D 0x3D 0xD  <- unrolled i=3,4,5,2

  and the whole function is just

      for (i = 0; i < 6; i++) { D_800D2460[i][13] = 0; }
      D_800D24C0 = 0;

The three "wasted" instructions that fold a compile-time constant offset are the
UNROLLER's address form; the constant folder never emits them.  Everything that
starts the loop at the peel index instead (`for (i = 2; i < 6; i++)`, explicit
subscripts, a pointer local, a ring do-while) folds to absolute stores and misses.
The old park had this exactly backwards -- it read the peeled iterations as separate
statements and searched for a way to make IDO *not* fold a constant.  Count the peel:
`n % 4` peeled + 4 unrolled tells you the original trip count.

--------------------------------------------------------------------- LAW B
**Golden materialising the SAME symbol address TWICE means the source does not
name that symbol twice.**  IDO CSEs identical address expressions, so two live
copies prove the two came from different expressions.

func_15017640 golden built `&D_800D2428` into both `$a0` (for the three element
stores) and `$v1` (as the loop end pointer).  Writing the bound as `D_800D2428`
CSEs onto `$a0`; writing it as `&D_800D2410[6]` -- the same address through the
OTHER array -- keeps both.  Worth 24 rows on its own (41 -> 11): the CSE had also
freed a slot, so our loop preheader emitted a `nop` where golden hoisted the
`lui $a0,%hi(D_800D24C8)` for a later call, and every row after that was shifted.

A lone `nop` in the middle of a function is almost always this: a hazard slot
golden filled with a hoisted instruction that we had already CSE'd away.

--------------------------------------------------------------------- LAW C
**Declared locals take $v0, $v1, ... BEFORE any compiler temp.**  So the first
register of the first address block tells you how many locals were live:

    first temp is $v1  ->  ONE local
    first temp is $a0  ->  TWO locals

func_15017640's golden address block starts at `$a0`, but the obvious source has
only `f32 *p`.  Adding the second local (`f32 *end`) shifted the entire temp
allocation one slot and took 11 -> 2.  Do not reach for a forcer when the temp
rotation is off by one -- count golden's first temp register and add the local
the count demands.  (`s32 i` for a fully-unrolled loop does NOT count: it never
gets a register.)

Related: statement ORDER inside the block sets the order temps are allocated in.
`D_800D2428[] = D_8009DCB4[]` before `D_800D2438[] = 0.0f` gives (a0, a1, a2) in
golden's order; swapping them rotates all three.

--------------------------------------------------------------------- LAW D
**`a = X, b = Y;` as ONE statement crosses the lui/addiu order.**

Golden emitted the two preheader pointers as

    lui   $v0, %hi(p_base)      <- p first
    lui   $v1, %hi(end_base)
    ...
    addiu $v1, $v1, %lo(...)    <- end first
    addiu $v0, $v0, %lo(...)

Two separate statements keep BOTH pairs in source order, so `end` first gives the
right addius and wrong luis (mism 2) and `p` first gives the right luis and wrong
addius (mism 2) -- the classic sign that no ordering of separate statements can
win.  One comma statement

    p = D_800D2410, end = &D_800D2410[6];

emits the luis in source order and the addius reversed.  That was the last 2 rows.
Nine spellings were measured; only the comma form is 0 (`for`-with-comma-init
cannot work here: `<` against an unknown bound adds a 2-instruction zero-trip
guard).  This is not a forcer -- both pointers are load-bearing and deleting
either breaks the loop.

--------------------------------------------------------------------- WHERE ELSE
LAW A is mechanical and should be swept for: any pragma function containing
`addiu $vN,$zero,k` immediately followed by `sll`/`addu` into a store base.

--------------------------------------------------------------------- LAW E
**A loop bound must be derived from the SAME symbol as the start, or IDO computes the
trip count at runtime and unrolls with a remainder.**

    while (p != D_800DD3FC)      <- a DIFFERENT end symbol
        -> subu (end-start) ; addiu at,zero,120 ; divu ; mfhi ; unroll by 2 + remainder
           112 words and a stack frame
    while (p != &D_800DD348[3])  <- same symbol, constant index
        -> a plain 40-word leaf loop

Measured on func_151745F0: 760 -> 38 and the frame disappears.  `D_800DD348 + 3` and a
complete `D_800DD348[3]` declaration are identical; ANY distinct end symbol (declared as an
array, as a single object, or as `u8[]` with a cast) re-triggers the unroll.  Hoisting the
bound into an `end` LOCAL also re-triggers it (720) -- the expression has to stay inline in
the loop condition.

Cross-checked on func_150B6C90 (game_E4070): 220 -> 16 with the same one-line change.

NOTE LAW E pulls AGAINST LAW B.  LAW B says a symbol materialised twice in golden is not
named twice in the source; LAW E says the bound must come off the start symbol.  When golden
materialises start and end as two independent lui/addiu pairs AND does not unroll, the two
laws want opposite spellings -- that tension is unresolved (func_151745F0, 38).

--------------------------------------------------------------------- LAW F
**Repeated early returns in a guard chain are ONE `||`.**

Four separate `if (...) return 0;` statements each grow their own epilogue; golden branches
every failure to a single shared `return 0`.  On func_1514672C that is 84 (n=36/30) versus
3 (n=30/30) -- the length only becomes exact with the `||` chain.

--------------------------------------------------------------------- SHIPPED ON THESE LAWS
func_1508F060, func_15017640 (retired game_44A90), func_1507EEB8, func_1510B958,
func_151A6B68.  ROM gate green throughout: 4cbadd3c4e0729dec46af64ad018050eada4f47a.

func_1510B958 also needed a NEW SYMBOL: golden stores to D_800D35E0 and D_800D35E0+4 through
two separate `lui $at` macros, i.e. TWO SCALARS, not a 2-element array (the array spelling
builds a base register and scores 21).  D_800D35E4 did not exist, so it was added to
conker/undefined_syms.us.txt -- remember that a score-0 spelling can still fail to LINK.

================================================================================
WAVE 2026-08-26 -- FOUR MORE LAWS, ALL PAID FOR WITH SHIPPED FUNCTIONS
================================================================================

LAW G -- u8 TRUTHINESS.  For a `u8` local, writing `if (x != 0)` makes IDO
materialise a WIDENED COPY (`or $vN,$aM,$zero`) and REMATERIALISE the constant
after a call instead of spilling it; writing `if (x)` / `if (!x)` keeps the byte
value and spills it properly as `sb` / `lbu`.
    Symptom you are chasing: golden has `sb $vN,0xNN($sp)` + `lbu $vN,0xNN($sp)`
    around a jal, you write `u8` and IDO emits NO spill at all (and a wrong,
    smaller frame), so you conclude "u8 is not the type".  It is the type.  The
    `!= 0` is the bug.  `s8` DOES spill but reloads with `lb`, which is the
    one-instruction trap that makes you think you are 1 mismatch away.
    SHIPPED: func_151A4ECC (game_1D0840) 28 -> 0.
    Also worth 44 -> 39 on its twin func_151918BC.

LAW H -- THE RIGHT OPERAND IS EMITTED FIRST.  For a binary compare or bitwise op,
IDO loads the RIGHT-hand operand into the lower temp register / emits it first.
If golden loads X before Y, write `Y op X`.
    SHIPPED: func_1501D2C4 (game_49D30) 2 -> 0 -- `D_800C3A60[arg0] & (1ULL << arg1)`
    gives `and $t2,$v0,$t0` with $v0 = the SHIFT (the right operand).
    Also 10 -> 8 on func_151A4ECC and 39 -> 36 on func_151918BC.

LAW I -- -g3 GIVES EVERY DECLARED LOCAL A STACK SLOT, TOP-DOWN, IN DECLARATION
ORDER -- even locals that end up entirely in registers.  So the stack offset of
an ADDRESS-TAKEN local tells you exactly where it sits in the declaration list:
an offset one word below the top means one local was declared before it.
    SHIPPED: func_150CFDB8 (game_FC5F0) 3 -> 0.  `&sp2C` wanted sp+0x2C, we were
    emitting sp+0x34; moving `unsigned char *sp2C;` to be the LAST of the three
    declarations moved it down the two words and closed the function.
    Corollary: adding a local grows the frame by 8 even if it never touches memory.

LAW J -- A LOOP TEMP DECLARED INSIDE THE LOOP BLOCK ALLOCATES DIFFERENTLY from
the same variable declared at function top.
    SHIPPED: func_150CFDB8, 25 -> 3, purely by moving `s32 v;` inside the `while`
    body as `s32 v = func_150CFD84(...)`.

FP COROLLARY TO LAW C -- DO NOT NAME CSE'd FLOAT LOADS.  The FP local pool runs
$f0,$f2,$f12,$f14,$f16,...; every f32 local you declare consumes one slot and
ROTATES everything after it.  If golden's long-lived floats start at $f12 and
yours start at $f0, you have declared two locals too many, not too few.
    SHIPPED: func_15049C40 (game_770F0) 23 -> 0.  The dot-product/negate function
    reads arg1[0..3] twice each (once for the product, once for the negation); the
    "obvious" spelling names them x,y,z,w and scores 23.  DELETING all four locals
    and keeping only `f32 d` for the dot product -- letting IDO CSE the loads into
    its own temp pool -- is byte-perfect.
