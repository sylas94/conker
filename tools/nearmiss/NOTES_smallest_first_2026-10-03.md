# Smallest-first wave (2026-10-03) -- results and residues

Shipped (uncommitted at time of writing): func_15144B68, func_1519ED24 (declaring-block barrier
closed both old "unsteerable" parks), func_1503D5F0, func_15084D00 (plain natural loops),
func_1517F75C, func_1502EE8C, func_1507F454.

REJECT (not C): func_150A6354, func_150AD900, func_150AD930, func_150AA644, func_150A6500,
func_150AD780, func_150A7A00, func_150A7A14, func_150AD8B0 (hand-written 0x150A cluster / odd regs),
func_150AC9B0 (bare `j` thunk). Likely hand-written: func_150A7CB0, guMtxIdentF, func_150A7DA0.
BLOCKED jtbl (shared block): func_150829D8 (2416F0), func_1502DB20 (23B8A0).

Near-miss residues (score / next lever):
- func_10001420 19, func_15167010 12 (was 24): golden uses IDO loop-test replacement with a runtime
  `end = base + N` bound; ours keeps a counter -- same unknown in both.
- func_1513A594 22: golden keeps a dead `lw 0x1D4` + `beqz` to next insn; ~20 empty-body spellings fail.
- func_151A8584 / func_151A85D4 28: golden never homes a0 in prologue (spills only in call delay
  slots); TU must stay -g3 (at -O2 14/15 siblings break).
- func_1506EF5C 17, func_1507488C 22, func_15168B44 35 (n=27/26, likely one more hidden local).
- func_151E81EC 6 (was 26): golden `sw zero` x2 for an f64 = 0 pair; need a construct lowering to
  two sw $zero.
- func_151EF610 6 (-O2) / func_15125628 16: golden never CSEs the address of a global it reads then
  writes -- one compiler-level fact for the family.
- func_150E33CC 9 / func_151D10E4 12: golden keeps loaded value in v0 and copies to the arg reg in
  the jal delay slot; ours coalesces.
- func_150FB188 10 (was 11; block-scope extern around the call fixed the jal slot): f0/f2 swap left.
- func_1515F0AC 32 / func_1515F040: entry-block lui-at placement before c.le.s.
- func_15116110 7 (was 37): callee proto `u16` 2nd param is the lever; temp numbering left.
- func_150EA490 19 (was 43): `f32 r` + `u32 *p = &arg0->unk80`; golden keeps arg0 only in its home
  slot and reloads after the call. Twin func_151AAA4C likely same shape.

## Batch 2A
Shipped: func_151AAA4C, func_1514672C, func_1515B994, func_150413FC, func_1509CDDC, func_15159230,
func_151C1570, func_1515CF9C, func_151AAABC. REJECTED by coordinator: func_151B70B4 matched only via a
block-scoped alias of the parameter (`{ Obj *o = arg0; ... }`) -- a new_var pin; left asm.
Jtbl-blocked but codegen mism 0 (bodies in scratchpad only): func_15194320/15194394/15194794 --
block 24CCD0 is owned solely by game_1C1150 (10 asm funcs) -> a whole-TU campaign candidate.
func_15015F40 jtbl in shared block 23B040. REJECT: func_150AA9A0 (hand-written).
Near-misses: func_151B1918 5 (was 12; declaring block for `Rec *r`; IV base residue),
func_15034420 6, func_1503F964 14, func_1516F864 22, func_150A2E4C 26 (original-game bug z = y - v[2]).
LEVER: golden "stores arg0 once and reloads it from the home slot" = a named sub-struct pointer
`s = &arg0->subOFF` with all accesses through it (closed 151AAA4C, 151C1570) -- try on
func_151A8584/func_151A85D4.

## Batch 2B
Shipped: func_151A4900, func_151CE634, func_15086BD0 (+ real empty `static void func_15086C68(void) {}`
after it), func_150885EC, func_151745F0, func_1515D5F8.
REJECTED by coordinator: func_151BD21C (parameter-alias block, same as 151B70B4); without it, 3.
MATCH but needs a repo change (copies in tools/nearmiss/pending_repo_changes/):
- osAiSetNextBuffer: verbatim SDK + function-scope `static u8 hdwrBugFlag = 0;` = 0 at default flags.
  Needs init_data split: `[0x2AB40, .data, libultra/io/aisetnextbuf]` then `[0x2AB50, data]`
  -- requires a full splat regen of the 290D0 data blob (do it when no agent reads asm/).
- func_151DD970 (game_20AE20), func_150B6C90 (game_E4070): match when the array is DEFINED in the TU
  (`s8 D_800E0BE0[28];` / `s32 *D_800D9898[10];`) -> needs a .bss segment per TU (see
  conker-bss-unlocked memory: one yaml SEGMENT). Law: a defined (not extern) global array lets IDO
  emit adjacent peeled stores sharing one `lui $at`.
- guMtxXFMF (game_21D5F0): SDK source matches at -O3 (IDO -O3 emits functions in REVERSE source order);
  asm-processor rejects -O3 -- TU has no GLOBAL_ASM left after this, so it could build without
  asm-processor. Needs Makefile surgery.
BLOCKED rodata (literal = 0, extern worse): func_15107AE0 (246ED0, extern 12), func_151254F4
(game_14FF90 block, extern 4).
REJECT: func_150A50C0, func_150A7960, func_150AC344 (hand-written).
Near-misses: func_1502FD70 5, func_1503DDD0 11, func_1511A410 13 (was 44), func_1517B7F8 18.

## Batch 3A
Shipped: func_151D3E6C, func_1509E640 (per-case block-scope extern), func_1510D8C0 (was parked 39 --
constant-hoist family: declare the per-entry pointer INSIDE the conditional block; try on the other
members), func_151AE590, func_150228E4, func_1503DD1C (callee declared `u32` param; real def s32).
Pending repo change: func_151F27E0 = libultra __osContAddressCrc, mism 0 at -O1 but TU game_21FC90
builds at -g (copies in pending_repo_changes/); neighbour func_151F2890 likely __osContDataCrc.
BLOCKED rodata: func_150344A0 (23C630), func_151B4B78 (24EE40). BLOCKED jtbl: func_1503453C (shared),
func_15141C0C (block 249CC0 owned solely by game_16EE20 -> campaign candidate).
REJECT: func_150AA5A8, func_150AA778.
Near-misses: func_1510F820 **1** (c.eq.s operand order only; p_best_1510F820.c in scratchpad),
func_15189FF0 6 (callee u8 params lever), func_150049A4 12 (BUG: s8 tag vs 0xDE never matches),
func_15077404 29, func_151B48DC 30, func_151DD8C0 34, func_150A00F0 65 ($at+addend fold).

## Batch 3B
Shipped: func_150AEDF8, func_15101090 (field read as u16 for the test, s16 for the arg -- golden
really has lhu AND lh), func_1519E304, func_15097910 (callee shadow `struct127 *func_15083E90(u8)`),
func_151A77C0, func_151CC1D4, func_151D324C (closes the delay-slot-duplication park; siblings
151DD140/151DD4E0/151D3130 may close the same way: block-scope extern of the callee in its branch +
`(b0 = arg1->unk0) == ...` with b0 declared in the case block), func_1509CBD4, func_150C5370.
BLOCKED: func_1508E6D0 jtbl (block 2424E0 owned solely by game_B3020 -> campaign candidate),
func_1503B708 rodata (23CD10), func_15007778 bss (+4 rows).
Near-misses (snippets in pending_repo_changes/NEAR_*): func_151A8F6C 1 (slot 0x24 vs 0x28),
func_16000F8C 5, func_15168E54 14, func_15012ED8 15, func_15104FF8 27, func_15116058 32,
func_15105C24 32, func_151592B8 43.

## Batch 4A
Shipped: func_1503D984, func_15034728, func_1512B53C, func_150497E0, func_1510B458, func_1509DDFC
(was 225), func_150A019C (was 54 -- index loop folds the end bound into %lo(sym+120)),
func_150A2D84, func_150C7670 (game_F4B20 now zero pragmas), func_1000EDA0 (was 65; header shadow).
BLOCKED: func_15076D3C rodata (23EBE0; extern 4), func_151B6254 rodata (block 24EF10 owned ONLY by
game_1E34C0; all-literal = 0 -> migrate that block), func_1514306C jtbl (249F40 shared, 33),
func_150B6BC0 jtbl (codegen 0; jtbl_8009FD00 sole-user but block 2447B0 holds D_8009FCF0/4 for
game_E3C90 -> split as `[0x2447C0, .rodata, game_E4070]`).
Near-misses: func_1502F3C8 6 (s-reg permutation), func_1503D368 13, func_1000EE70 18 (was 1650),
func_15187EC0 24, func_150FC368 28, func_151918BC 36. Bodies: pending_repo_changes/batch4A/.
Levers: index loop over a global array (separate address materialisation + folded end bound);
barrier block around the final call fixes an unfilled jal slot; storing through the global array
(not a local pointer) lets IDO hoist stack-arg loads.

## Batch 4B
Shipped: func_151D3130 (next declared in while body; park obsolete), func_15030310, func_15030F94
(`var = next; continue;` in the non-taking branch of a list walk, next declared in the loop body),
func_10009BE4 (header shadow; struct54*), func_1000A348, func_1515548C, func_1505EEF4 + twins
func_1505EFD0/func_1505F0AC (`ptr++` as a BODY statement, not the for-increment -- fixes
"split-symbol" peel parks; func_15060D54 does not close this way).
Pending: func_151F2890 = __osContDataCrc, 0 at -O1 (TU game_21FC90 is -g; same as func_151F27E0).
BLOCKED jtbl: func_1507DF10 (23EBE0 shared), func_1513DF9C (249560 shared).
REJECT: func_150A613C, func_150A5AB8, func_150AA4D0.
Near-misses (pending_repo_changes/batch4B/): func_1508DA1C 5, func_151407D0 7 (needs callee shadow;
base_16DC80_shadow.c), func_150DFBD0 7, func_15183ACC 8 (frame only), func_150641D8 17,
func_150495B0 47, func_151D5334 56.

## Batch 5A
Shipped: func_150A2864, func_1510B51C, func_1518BBF4 + func_150E35DC (D_800DD190++/-- node-stack
walkers: block-scope extern barrier on the decrement), func_151E530C, func_1501E73C, func_1502C608
(actor-pointer macro, not a local), func_1503D510, func_1510F720, func_151193F4 (`unk73 |= 0;` is a
REAL lbu/sb in golden), func_150C851C, func_15072208.
BLOCKED jtbl: func_15141CC0 (block 249CC0, game_16EE20-owned; codegen 0).
Near-misses (pending_repo_changes/batch5A/): func_15135480 2 (bnel operand order),
func_151A084C 4 (slots), func_15073A50 4 (frame 0x30 vs 0x28; was 664), func_1500727C 6 (was 1165),
func_1000C934 18, func_15007360 22, func_15145CD0 46.
Stale flags: "rodata" on func_1510B51C / func_151E530C was wrong (inline constants).

## Batch 5B
Shipped: func_1507E1D0, func_151D5714 (header shadow u8 args), func_150626EC, func_1516D400,
func_1507BB28 (original-game `while (1) {}` hang kept), func_15108D24, func_15133EEC (TU prototype
`Gfx *(Gfx *, u16, u8, s32)`), func_15166118, func_151AE2BC, func_1501A39C, func_151717FC.
REJECTED by coordinator: func_15004BF0 -- matched only by overwriting its parameter as a working
variable (`for (i = arg0 = D_800DBF00; ...)`); with a `start` local it's 16. Copy kept as
REJECTED_param_reuse_func_15004BF0_game_30E90.c.
Near-misses (pending_repo_changes/batch5B/): func_151668B8 5, func_15035714 10, func_150E05F8 14,
func_150767F4 16, func_1509D08C 26, func_1501B22C 45, func_10010630 54, func_1507FEA0 57.
Lever: float locals live across a call -> function-scope gets callee-saved $f20, block-scope spills
to its own slot.

## Batch 6A
Shipped: func_1511F3E8, func_1511C548 (barrier block around 2nd call), func_1000DF68 (header shadow
void; `s32 rate` in the arg2>=2 block), func_1507C22C.
BLOCKED rodata, block owned by ONE TU (migration candidates, literal = 0): func_151A0E40 +
func_151A0F28 (24D7E0, game_1CC440; also widen func_151A11CC to its real 28-param signature, param 3
f32 -- best/game_1CC440_literal_full.c), func_151B9214 (24EFA0, game_1E6260).
BLOCKED rodata shared: func_150C2424 (244CD0, extern 3). BLOCKED jtbl: func_15134070 (codegen 0;
block 248E10 owned solely by game_161520), func_151E2404 (250030 shared).
Near-misses (pending_repo_changes/batch6A/): func_15115F68 4, func_150498A4 8, func_15074A94 13,
func_15003570 16, func_15145DB4 18 (was 962), func_15007558 22 (was 610; dead `sw v0` family with
func_15007360), func_151162D4 23, func_151A5F70 58, func_1500707C 61, func_1508ECC0 70.
CORRECTION: func_1507C22C (game_A9260) scored 0 and passed the whole-TU masked .text check but
BROKE THE ROM sha1 when linked -- reverted, stays asm. Copy: batch6A/ROMFAIL_func_1507C22C_game_A9260.c.
Suspect the `*(u8 *)&D_800C3654` read or a relocation/data difference the masked compare can't see.
The masked .text check is NOT sufficient; only the full ROM build is.
