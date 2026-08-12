# func_151CA6A0 — 1068 B, game_1F4650.c — parked at **asm-differ 172** (was 517, was 4333)

`tools/nearmiss/func_151CA6A0.c` is the WHOLE TU with this function live (pragma removed).
Drop it over `conker/src/game_1F4650.c` to resume. The repo copy of the TU is UNTOUCHED
(pragma still in place) — verified with `git status --short -- conker/src/game_1F4650.c`
(prints nothing).

## WAVE 2026-08-12 — 517 → 172, and the register allocation now matches golden EXACTLY

**172 / 267 instructions / frame 248 / 1068 bytes.** Everything from the prologue to
instruction 195 is byte-identical to golden, *including every register name*, and everything
from instruction 218 to the epilogue is byte-identical. The entire residual is **16 rows in
one basic block** — the fifth (3.0f) descriptor block — and it is a pure SCHEDULING
permutation: the instruction multiset, the register assignment and every stack offset are
already golden's.

### The two edits, and what they mean

Both are the same discovery: **the four quadrant blocks are written with one uniform idiom.**
The function builds the same 0x58-byte descriptor four times, once per corner, poking a 2-bit
alignment field in `spA0.unk14` with a different code each time. The parked file used to spell
those four blocks three different ways. Golden spells them **one** way:

```c
spA0.unk14 &= ~0x6;  spA0.unk14 |= 0x6;   spA0.unk0 =  25.0f;  spA0.unk4 =  25.0f;
spA0.unk14 &= ~0x6;  spA0.unk14 |= 0x4;   spA0.unk0 = -25.0f;  spA0.unk4 =  25.0f;
spA0.unk14 &= ~0x6;  spA0.unk14 |= 0x0;   spA0.unk0 = -25.0f;  spA0.unk4 = -25.0f;
spA0.unk14 &= ~0x6;  spA0.unk14 |= 0x2;   spA0.unk0 =  25.0f;  spA0.unk4 = -25.0f;
```

| step | edit | score | rows |
|---|---|---|---|
| base (last wave) | blocks 1,2 split; block 3 `&= ~0x6` only; block 4 combined | 517 | 39 `r` + 2 `<` + 2 `>` |
| **1** | block 3 gains `spA0.unk14 \|= 0x0;` | **477** | block 3 becomes byte-identical |
| **2** | block 4 split from `= (x & ~6) \| 2` into `&= ~6; \|= 2;` | **172** | **every register in the function now matches** |

Step 1 emits **no instruction** (267 before and after) but consumes one IDO temp-register web,
which is exactly the "forcers are temp-register rotation counters" law seen from the useful
side. Step 2 emits no extra instruction either. Together they moved the whole t-register
rotation onto golden's and collapsed all 39 register rows plus the two block-3/4 blocks.

### HONESTY FLAG on `spA0.unk14 |= 0x0;` — read this before shipping

A statement that emits zero instructions and only shifts register allocation is, in isolation,
exactly the banned "no-op mask chain". The argument *for* it here is that it is not an isolated
invention: it is the `k = 0` member of a four-way family whose other three members (`k` = 6, 4,
2) are each independently forced by the binary, in four copy-pasted blocks that are otherwise
identical token for token. Copy-paste-and-edit-the-constant is the obvious origin of four such
blocks, and editing `0x6` to `0x0` rather than deleting the line is what produces it.
**That is an argument, not proof.** It is recorded here rather than decided, because the
function is at 172 and the question is not yet live. If a later wave reaches 0, the call has
to be made explicitly.

Measured, so nobody re-explores it: `|= 0x0` is **inert everywhere except block 3**. Inserting
it before block 1's `&= ~0x6` (n8), or at any of the six positions inside block 5 (n0–n5), or
after block 5's `unk14`/`unk30`/`unk34` (n6, n7), is **byte-identical** to the base. It is
load-bearing only in the one place where golden's registers demand it.

## The residual at 172 — 16 rows, one block, pure scheduling

Instructions 193–217, the block that rebuilds the descriptor for the twelve-particle ring.
Same 25 instructions, same registers, different order:

```
       GOLD                              MINE
 193   lui at,0x4040                     lui at,0x4040          <- identical
 194   mtc1 at,$f0                       mtc1 at,$f0
 195   mtc1 zero,$f2                     mtc1 zero,$f2
 196   li v1,1                           lw t8,248(sp)
 197   lw t8,248(sp)                     li t1,153
 198   li t1,153                         sb t1,176(sp)
 199   swc1 $f2,160(sp)                  swc1 $f0,172(sp)
 200   swc1 $f2,164(sp)                  swc1 $f0,168(sp)
 201   swc1 $f0,172(sp)                  swc1 $f2,160(sp)
 202   swc1 $f0,168(sp)                  swc1 $f2,164(sp)
 203   sb   t1,176(sp)                   lbu t6,573(t8)
 ...
 211   sllv t2,t0,t9                     li v1,1
```

Two facts:
* golden emits the five opening stores in **exact source order** (160, 164, 172, 168, 176);
  mine emits the three *constant groups* in **reverse** order (`sb`, then the 3.0f pair, then
  the 0.0f pair) while preserving source order *within* each group;
* golden hoists `li v1,1` (the comparison constant of `if (D_80082FA0 == 1)`) to the head of
  the block; mine emits it at its use, 15 instructions later.

**This block's emitted order is completely insensitive to the source.** Everything below was
swept this wave against the 172 base and every single variant is byte-identical:

| sweep | size | result |
|---|---|---|
| block 5, brace-aware: **every unit to every position** (14 units incl. both `if/else`s) + **all 120 permutations of the five opening stores** | 273 | **122 tie at 172**, none changes the emitted store order |
| adjacent line **joins**, runs of 2/3/4/5, at every position in block 5 | 16 | flat at 172 |
| literal spellings `0.f`, `3.f`, `0` (int), chained `a = b = k`, copy `unk8 = unkC`, `0x99`→`153` | 9 | flat at 172 (`0.f` and `0` *cost* an instruction: 268) |
| `if (D_80082FA0 != 1)` with the arms swapped | 1 | 382 |
| `\|= 0x0` inserted at 9 further positions | 9 | flat at 172 |
| declaration order of `temp_v0`/`temp_type`/`i` (all 6), `int`/`u32`/`register` `i`, `register temp_type`, `register`/`u8 *` `temp_v0` | 12 | flat at 172 |
| loop forms: `while`, `do/while`, `i < 12` | 3 | flat at 172 |
| `if (temp_v0)`, `memcpy` cast form | 2 | flat at 172 |
| block-3 mask spellings `= x & ~6`, `&= 0xFFF9`, chained store, stores-before-mask | 4 | flat |
| `0x50 \| (1 << …)` | 1 | flat |
| `spA0.unk10 = 0x99` moved after `unk34` | 1 | 672 |
| `sp44.unk28` / the `if` block hoisted above the spA0 stores | 1 | 1363 |
| `spA0.unk14` split from `\| 0x50` | 1 | 1332 |
| `s16 i` | 1 | 797 / **269 instructions** |

## The frame, re-read under the declaration-list law

Frame 248, and it is fully explained — **no unexplained words in this function.**

```
locals area ends at framesize:  spA0  160..247 (0x58 = 88)   <- declared first
                                sp44   68..159 (0x5C = 92)
                                temp_v0@64  temp_type@60  i@56
base (outgoing args + saved regs + compiler temps) = 52
framesize = roundup8(52 + sum(sizeof(local))) = roundup8(52 + 192) = roundup8(244) = 248
```

Calibrated directly: adding 1 unused scalar keeps 248 (the round-up absorbs it), adding 2 gives
256, 4 gives 264, 8 gives 280, 16 gives 312 — all exactly `roundup8(52 + L)`. **Unreferenced
locals are NOT dropped by IDO**; they occupy their home like any other. So the declaration list
is right, and there is no room for a cached `D_80082FA0` or any other extra local.

## Still true from the previous revision (do not re-explore)

* `if (arg1)` not `if (arg1 != 0)` — the u8-parameter law, threshold at TWO explicit `!= 0`
  comparisons; worth 1737 and it fixes the instruction count (269 → 267).
* `spA0.unk44 = *(u8*)(arg0+0x23D);` must be **above** the `unk14` mask pair (1944 points).
* the loop-counter init `i = 0;` lifted out of the `for` and placed **immediately ahead of**
  `sp44.unk24 = 0.0f;` (65 points; golden's `move s0,zero` precedes `swc1 $f2,0x68(sp)`).
* `func_1515548C(descriptor*, u8 kind, 0, 0, size, u8, s32)`; caller does
  `memcpy((u8*)ret + 0x70, &payload, size)`. Keep `temp_type` `s32` (call site does
  `andi a1,v0,0xff`).
* `spA0.unk14` is **u16** (golden reloads with `lhu`), not the `s16` the sibling files declare.
* `D_800AAE88..98` are real globals in `asm/data/24F740.rodata.s` — **no rodata migration.**
* **The sibling `func_151CAB78` contains byte-identical text.** Anchor every edit between
  `void func_151CA6A0(` and `void func_151CAACC(`. Every generator used this wave does.

## REFUSED this wave

Nothing needed refusing: no variant beat 172, so no trade between score and plausibility came
up. The previous wave's refusals stand — the permuter's `if ((short) arg1)` (562 at 269
instructions), `(unsigned short)` on a pointer NULL test (semantically wrong), and the
gratuitous `(long long)` shift-count cast (467, but the same two displaced instructions and
pure register noise). Note that the `(long long)` cast's 467 has now been beaten *and
explained* by step 1 above: it was doing the same register rotation, badly.

## Next move for whoever picks this up

The block-5 schedule is not reachable from statement order, line joins, literal spelling or
declaration order — 300+ variants, all byte-identical. What is left is a structural question
about that block: golden's scheduler had a different *pre-scheduling* order for three
independent things (the 0.0f store pair, the 3.0f store pair, and `sb 0x99`), and something
must make IDO generate them in a different sequence. Untried ideas, in the order I would try
them: whether `spA0.unk0/unk4` and `unk8/unkC` are array members (`f32 pos[2]; f32 size[2];`)
rather than four scalars — array subscripting produces different ucode for the same stores;
whether `sp44` is built by a helper the four call sites share; and the permuter seeded here
(the base is now excellent: correct count, frame, offsets and registers) with a hard gate on
`INSNS == 267` **and** on the residual staying inside block 5.
