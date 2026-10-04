# Cold wave over the never-attempted list (2026-08-25)

Worked the **1457 still-pragma'd functions that have no park file at all**, smallest first,
rather than re-grinding the parked backlog. Tooling added this wave, both reusable:

* `scratchpad/worklist.py` — every pragma'd function with no park, by instruction count.
* `scratchpad/simple.py` — the same list, ranked by SHAPE: no `jal`, no loop, no float, no
  branch scores 0 and matches fastest per unit effort. **This is the better picker.**
* `scratchpad/try.py <tu> <func> <body.c> [--rows N] [--opt "-O2"] [--drop REGEX]` — splices a
  candidate body over its pragma in the REAL TU and scores it. `--drop` removes a conflicting
  forward declaration.

**A caveat on both scripts: "no park file" does NOT mean "never attempted".** Several
functions carry their prior analysis as a COMMENT IN THE TU (func_151EF610 has a full
flag-contradiction diagnosis above its pragma) or in a NOTES_*.md. `simple.py` filters TU
comments; `worklist.py` does not. Check before starting.

## Shipped-shape result

Nothing reached 0 this wave. One is very close and two others are close enough to be worth a
second pass; the rest were triaged out as structurally impossible in the current build.

| func | tu | best | n | note |
|---|---|---|---|---|
| **func_1516F864** | game_19A8B0 | **22** | 34/34 exact, leaf | parked, full ladder in its park file |
| func_1517F75C | game_1AC2F0 | 17 | 22/22 exact, leaf | below |
| func_150E33CC | game_1104D0 | 21 | 17/18 | below |
| func_151D10E4 | game_1FA770 | 28 | 22/21 | below |

### func_1517F75C (game_1AC2F0) — 17, exact length
A countdown sweep over `D_800DDE10[]` (declared `s16[]` in the TU, indexed as `u16*`):
for each entry up to `D_80082FA0`, subtract the frame delta `D_800BE9E4`, clamping at 0.
```c
if (D_80082FA0 >= 0) {
    p = (u16 *)D_800DDE10;  end = &((u16 *)D_800DDE10)[D_80082FA0];  dt = D_800BE9E4;
    do { if (dt < *p) { *p = *p - dt; } else { *p = 0; } p++; } while (p <= end);
}
```
The loop bound is `p <= end` (golden's `sltu`/`beql` pair), i.e. INCLUSIVE, and the compare
is `slt at, dt, *p` so the subtract arm is `dt < *p`. Residual is register naming only.
REFUTED: hoisting `p = (u16 *)D_800DDE10` above the `if` (32, and it goes one instruction
long); reading `D_800BE9E4` inline in the loop instead of via `dt` (32).

### func_150E33CC (game_1104D0) — 21, one short
```c
s32 func_150E33CC(s32 arg0, s32 arg1, s32 *arg2, s32 arg3) {
    if (*arg2 != 0) { func_1000E7A0(2, *arg2); return 0; }
    return 1;
}
```
Four parameters (a0/a1/a3 are spilled to their home slots by -g3, which is how we know they
exist); only `arg2` is read. Its TU declares `extern void func_150E33CC(void);` and passes it
as a CALLBACK (`(s32)func_150E33CC` to func_1000FA64), so that declaration has to be dropped
or fixed to install this. Golden materialises `a0 = 2` BEFORE the branch and moves the loaded
value with `or $a1, $v0, $zero` in the jal delay slot; we load straight into `a1` and are one
instruction short as a result. Loading into a named local and passing it is the thing to try.

### func_151D10E4 (game_1FA770) — 28, one over
```c
s32 func_151D10E4(void *arg0, s32 arg1, s32 arg2) {   /* the TU's own prototype */
    s32 temp = *(s32 *)((u8 *)arg0 + 0x1D4);
    if (temp == 0) { return 0; }
    func_15143134(&D_800AAF9C[arg2 & 0xFF], arg1, temp);
    return 1;
}
```
`D_800AAF9C` is an array of **12-byte** records (`(x*4 - x) * 2`... actually `((x<<2)-x)<<2`).
`arg2` is masked to a byte, so it is really `u8` even though the TU's prototype says s32.
Golden computes the `andi` and the whole index BEFORE the `bnez`, we compute it after.

## Triaged out — do not re-open without a build change

* `func_150A7770`, `func_151F892C`, `func_151F8960`, `func_150AD960` — the `.s` files are
  marked **`/* Handwritten function */`** and contain `add`/`sub`/`neg` (trap-on-overflow
  forms IDO never emits) or `lwl`/`lwr`. Not C.
* `func_150AC9B0` — 4 instructions, a bare `j func_150AC2D8` tail-call thunk. A C call emits
  `jal`+`jr`; not expressible.
* `func_150A81A0` (game_D5650) — copies 0x40 bytes with **`ld`/`sd`**, which are MIPS III.
  The tree builds `-mips2`, and a `u64` copy compiles to lw/sw pairs (measured: 272, n=38/12).
  Same blocker as [[conker-handwritten-math-cluster]]; needs the -mips3 question answered.
* `func_150829D8` (game_AEB40) — dispatches through `jtbl_8009CC40`; blocked on the rodata
  block migration, see [[conker-jtbl-unlocked]].

## Second batch — float-shaped candidates

| func | tu | best | n | note |
|---|---|---|---|---|
| **func_15034420** | game_61490 | **6** | 32/32 exact, leaf | own park file; PRIME permuter candidate |
| func_1510B958 | game_138520 | 21 | 30/30 exact, leaf | below |

### func_1510B958 (game_138520) — 21, exact length
Writes the two camera FOV-ish scalars at `D_800D35E0[0..1]` from camera record `arg0`
(`D_800BE628`, stride 0x180 — the TU already uses that stride at lines 59/60/70/93):
```c
Cam *p = &((Cam *)D_800BE628)[arg0];
D_800D35E0[0] = (((p->unk74 / p->unk6C) - 1.0f) * -1.0f) + p->unk64;
D_800D35E0[1] = (((p->unk78 / p->unk70) - 1.0f) * -1.0f) + p->unk68;
```
The `1.0f` and `-1.0f` are materialised ONCE each into $f0/$f2 and reused across both
statements, so they are literals in the source (not a `-(x - 1.0f)` rewrite, which would fold).
Residual is register naming plus one scheduling slot: golden emits the second `mtc1` before
the `lui` for D_800BE628, we emit the pointer load first.

## Method note for the next pass

The fastest picker is `simple.py` (shape-ranked), NOT `worklist.py` (size-ranked): of the
size-ranked candidates, most of the smallest are handwritten stubs, tail-call thunks, or
MIPS III `ld/sd` copies. Of the SHAPE-ranked ones, the straight-line and float-only functions
landed at 6, 17, 21, 22 on a first or second cut, which is near-miss territory immediately.

Three of the four best results this wave (6, 17, 22) are **exact length AND exact frame with a
pure register residue** — the documented good case for decomp-permuter. That is the obvious
next move for this batch, and it has not been run on any of them.

### func_1515B994 (game_188440) — 19, exact length (31/31), leaf
A semi-implicit Euler step on one axis, `D_800BE9A4` being the delta:
```c
s32 func_1515B994(Ph *arg0) {          /* returns 1 unconditionally */
    f32 vel = arg0->unk78;             /* velocity */
    f32 acc = arg0->unk74;             /* acceleration */
    arg0->unk14 = arg0->unk14 + ((vel * D_800BE9A4) + ((0.5f * acc) * D_800BE9A4));
    arg0->unk78 = vel + (acc * D_800BE9A4);
    arg0->unk1C = arg0->unk7C + ((arg0->unk80 * (arg0->unk78 + vel)) * 0.5f);
    return 1;
}
```
`D_800BE9A4` is loaded ONCE for the first statement and RELOADED for the second (the store to
unk14 may alias it), and `arg0->unk78` is RE-READ after its own store for the third — both
fall out of writing it in this order, and both are in golden.
Residual is pure FP register naming: golden puts the 0.5f constant in $f16, vel in $f2,
acc in $f14, unk14 in $f18; we get f14 / f0 / f2 / f16. Same family as the parked
func_15121C80 (@5), which is also an f0/f2 rotation — solving one probably solves both.

## Third batch

| func | tu | best | n | note |
|---|---|---|---|---|
| **func_150A0264** | game_CD5A0 | **9** | 27/27 exact, leaf | own park file; likely BITFIELDS, see park |
| func_1515B994 | game_188440 | 19 | 31/31 exact, leaf | above |

Triaged out: `func_1502DB20` (game_58F80) dispatches through `jtbl_80096DF8` — jtbl-blocked.
`func_150A6500` (game_D3040) — its `.s` contains TWO function bodies back to back (a second
prologue/epilogue after the first `jr`), so the split is suspect; check the yaml boundary
before decompiling it.

## Wave scoreboard

Seven functions opened cold, all previously never attempted, none previously parked:

    func_150A0264   9   27/27 exact   leaf
    func_15034420   6   32/32 exact   leaf
    func_1517F75C  17   22/22 exact   leaf
    func_1515B994  19   31/31 exact   leaf
    func_1510B958  21   30/30 exact   leaf
    func_150E33CC  21   17/18
    func_1516F864  22   34/34 exact   leaf
    func_151D10E4  28   22/21

**SIX of the eight have EXACT instruction count AND exact frame**, with residues that are
purely register naming. That is a very different backlog from the parked one (whose residues
are structural or GRA ties that survived thousands of permuter iterations) — these are the
shape decomp-permuter is documented to crack quickly.

A permuter run on func_15034420 is set up and selftest-PASSED at
`/tmp/conker_permuter_tu/func_15034420` (harness score 35 == fastscore 6; the selftest's
TU-context control confirms a plain single-function permuter would optimise the wrong bytes).
Recreate with:
    python3 scratchpad/permsetup.py            # writes /tmp/cand_61490.c
    ./permuter_tu.sh setup game_61490 func_15034420 /tmp/cand_61490.c
    ./permuter_tu.sh selftest /tmp/conker_permuter_tu/func_15034420
    ./permuter_tu.sh run      /tmp/conker_permuter_tu/func_15034420 -j 8 --best-only --stop-on-zero
First run produced no improvement over base in its initial window.

**The common residue across this whole wave is the IDO temp rotation** (t0/t2/t4 where golden
has t1/t3/t9, f0/f2 where golden has f2/f14). Solving that ONE law would move six functions at
once, which makes it a far better target than any individual function here.

## *** THE BITFIELD LAW -- TWO MATCHES, AND IT IS A FAMILY ***

`func_150A0264` sat at **9** with exact length and exact frame under byte punning
(`u8 *b = (u8 *)r; *b = *b | 0x80; ...`). Respelling the record as **BITFIELDS** took it
straight to **0**:

```c
typedef struct Rec150A0264 {
    u32 unk0_b0 : 1;      /* 0x80 */
    u32 unk0_b1 : 1;      /* 0x40 */
    u32 unk0_b2 : 4;      /* 0x3C */
    u32 unk0_b6 : 2;      /* 0x03 */
    u32 unk0_rest : 24;
    s32 unk4;
    s32 unk8;
} Rec150A0264;
```
Both the plain `u32` bitfield spelling and a `union { u32 word; struct { u8 f0:1; ... } b; }`
score 0; the plain one is installed. Byte punning reproduces the INSTRUCTIONS but not the
register rotation -- that residual "temp rotation" was never a rotation problem at all, it was
the wrong source construct. **Check bitfields before blaming the allocator.**

**THE TELL, in golden asm:** a read/modify/write chain on one address where the mask is
partial (not 0xFF/0xFFFF) -- `lbu` then `ori 0x80` / `andi 0xBF` / `andi 0xC3` + `andi 0x3C`,
each `sb`'d back and feeding the next. A guard that reads the SAME storage as a 32-bit word
(`lw` + `srl 31`) alongside byte-sized updates is the union/bitfield combination.
`scratchpad/bitfields.py` scans for exactly this shape; it found only 5 never-attempted
candidates repo-wide, 3 of them in this one TU.

### Second match, same TU: func_150A02D0 -> 0
The if-chain spelling scored 57 (n=39/41) because golden hoists ALL THREE tests to the top.
That is a **`switch`**, not an if-chain -- three cases is too few for a jump table so IDO
emits a `beq` chain, and only `switch` puts the comparisons before the bodies:
```c
switch (arg1) {
case 0: D_800D3010[arg0].unk0_b1 = 1; return 1;
case 1: D_800D3010[arg0].unk0_b1 = 0; return 1;
case 2: D_800D3010[arg0].unk4 = arg2->unk8; return 1;
}
return 0;
```
57 -> **0**. Both are installed in `conker/src/game_CD5A0.c`.

### Third sibling still open: func_150A00F0 — 65, n=46/43 (three over)
Same table, an init sweep: `for (i = 0; i < 10; i++) { .unk0_b0 = 0; .unk4 = 0; .unk8 = 0; }`.
Golden PEELS records 0 and 1 then runs a 4-records-per-iteration unrolled loop from
`&D_800D3010[2]` to `&D_800D3010[10]`. Measured: index loop s32 65, u32 65 (identical),
store order 4/0/8 → 73, and **pointer walks are badly wrong** — `p < &D_800D3010[10]` gives
n=14/43 and a do/while pointer form n=13/43, i.e. IDO does not unroll the pointer form at all.
Keep the index loop; the residual is in how the peel is spelled.

## Permuter verdict on func_15034420: REJECTED (forcer)
It improved its own metric 35 → 25, and the whole gain decomposes to typing a local
`long long` for a 16-bit shift result. The honest half (hoisting `v >> 4` into a local) is
worth ZERO. Full decomposition in that function's park file. Third time on this repo the
permuter's best output has been its only dishonest one.

## Fourth batch — the rest of game_CD5A0, plus a fourth bitfield candidate

| func | tu | best | n | note |
|---|---|---|---|---|
| func_150A019C | game_CD5A0 | 54 | 51/50 | diagnosis kept in the TU comment above its pragma |
| func_151A4ECC | game_1D0840 | 10 | 44/44 | own park file; frame 8 too big |

### func_150A019C — two REAL TYPE ERRORS found by reading the opcodes
79 → 76 → 57 → 54. Worth generalising:
* golden uses **`sltu`** and **`divu`**; as `s32` we emitted `slt` and `div` — and `div` drags
  in IDO's three-instruction SIGNED-OVERFLOW guard (`addiu at,-1` / `bne` / `lui at,0x8000` /
  `bne`) on top of the zero-check. **Three spurious instructions bought by one wrong sign.**
  Typing `unk4`/`unk8` as `u32` removed all of it. Re-verified: both shipped matches in that
  TU stay at 0 with the unsigned fields, and the full ROM gate is green.
* the increment and the modulo are **two statements** with an explicit `!= 0` guard, because
  golden's `sw $t5,0x4($v1)` sits in the `beq` DELAY SLOT — so `unk4 += 1` happens on both
  paths and only the `%` is conditional.
* `r != &D_800D3010[10]` in the loop condition RECOMPUTES base+120 every iteration; hoist the
  end pointer. (An `extern D_800D3088[]` end marker is worse, 89 — IDO then cannot prove the
  loop runs once and adds an entry test.)

### func_151A4ECC — the TU already had the types
31 → 10 purely by reaching the embedded `struct frame151A3504` through a POINTER LOCAL
instead of offsets from arg0 ([[conker-pointer-chase-form]]). Its callee is DEFINED in the
same TU with a full prototype, and the object embeds the callee's frame struct at +0x28 --
read the TU before inventing types. Remaining defect is 8 frame bytes; see the park.

## Running total for the wave

**2 byte-perfect matches** (func_150A0264, func_150A02D0 — both in game_CD5A0, full clean ROM
gate, code bin 842e3d34 / ROM 4cbadd3c), and 9 functions opened cold and parked with ladders:

    func_151A4ECC  10   44/44 exact
    func_15034420   6   32/32 exact   leaf
    func_1517F75C  17   22/22 exact   leaf
    func_1515B994  19   31/31 exact   leaf
    func_1510B958  21   30/30 exact   leaf
    func_150E33CC  21   17/18
    func_1516F864  22   34/34 exact   leaf
    func_151D10E4  28   22/21
    func_150A019C  54   51/50
    func_150A00F0  65   46/43

game_CD5A0 went from 5 pragmas to 3.

## Fifth batch — the "flag + guard chain" family

`func_151A4ECC` (game_1D0840, **10**) and `func_151918BC` (game_1BA1D0, **44**, FRAME EXACT)
are the SAME function shape: identical guard chain against the same target struct
(`unk0` / `unk3B` / `unk1D4` — the Tgt1518BD60 layout from func_1518BD60's park), the same
set-a-flag/act-at-the-end skeleton, and the same sub-struct embedded at +0x28 that gets passed
to a helper. Both have their own park file. **Work them together.**

Two transferable findings from the pair:

* **`u8` vs `s32` for a flag spilled across a call is NOT a free choice, and the right answer
  is opposite in the two functions.** In func_151918BC `u8` is correct and gives the exact
  frame (golden `sb $v0,0x27($sp)` / `lbu`). In func_151A4ECC `u8` makes IDO stop spilling
  entirely and REMATERIALISE `addiu v1,1` after the call, losing 2 instructions and 8 frame
  bytes. The discriminator is whether a callee-saved register is already live: func_151918BC
  keeps arg0 in `$s0`; func_151A4ECC has no saved regs and re-spills arg0 to its own incoming
  home slot instead.
* **Comparison operand order is worth 2 rows** — `t->unk3B != arg0->unk2C` (target first)
  scores 44 where `arg0->unk2C != t->unk3B` scores 46, because golden loads the object byte
  first and IDO evaluates the written-first side last.

## Wave total

**2 byte-perfect matches** (func_150A0264, func_150A02D0; full clean ROM gate,
code bin 842e3d34 / ROM 4cbadd3c) and **11 functions opened cold**, every one previously
never attempted and none previously parked:

    func_15034420    6   32/32 exact   leaf
    func_151A4ECC   10   44/44 exact
    func_1517F75C   17   22/22 exact   leaf
    func_1515B994   19   31/31 exact   leaf
    func_1510B958   21   30/30 exact   leaf
    func_150E33CC   21   17/18
    func_1516F864   22   34/34 exact   leaf
    func_151D10E4   28   22/21
    func_151918BC   44   50/49         frame exact
    func_150A019C   54   51/50
    func_150A00F0   65   46/43
