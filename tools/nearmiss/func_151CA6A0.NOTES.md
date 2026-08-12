# func_151CA6A0 (game_1F4650.c, 1068 B) — near-miss, 2026-08-11

`tools/nearmiss/func_151CA6A0.c` is the WHOLE TU with the function live (pragma removed).
Drop it over `conker/src/game_1F4650.c` to reproduce.

## Result

* isolated compare: **mine = 269 instructions, gold = 267**. asm-differ `-R` and no-`-R` both
  give **4333** — but that number is NOT the function: because my body is 2 instructions (8 B)
  longer, every function after it in the TU shifts and asm-differ (which cannot bound a
  GLOBAL_ASM-sourced golden symbol — no `.size`) diffs to the end of `.text`. The real
  residual is the 2 instructions below plus the t-register rotation they cause.
* the structure is otherwise exact: all 5 `func_1515548C` call sites, all 5 `memcpy`s, the
  0x58-byte descriptor, the two `D_80082FA0 == 1` selects and the 12-iteration loop are
  instruction-for-instruction right.

## The whole residual, exactly

```
GOLD                       MINE
sw   s0,0x24(sp)           sw   a1,0xfc(sp)
mtc1 at,$f0                andi t6,a1,0xff
andi s0,a1,0xff            mtc1 at,$f0
sw   ra,0x2c(sp)           move a1,t6            <-- EXTRA
sw   s1,0x28(sp)           ...
sw   a0,0xf8(sp)           sw   s0,0x24(sp)
sw   a1,0xfc(sp)           ...
                           move s0,a1            <-- EXTRA (just before the 1st beqz)
```

Golden normalises the `u8` parameter **straight into the callee-saved `$s0`**; IDO normalises
it in place (`andi tX,a1,0xff` / `move a1,tX`), keeps it in `$a1` for the first
`if (arg1 != 0)` test (which happens before any call), and then copies to `$s0` for the three
later tests. +2 instructions, and the resulting temp-register rotation is what produces every
other row in the diff (t6↔t7, t8↔t9 … and a handful of adjacent-slot moves near `.L151CA9A0`).

## Spellings ruled out

| spelling | insns | note |
|---|---|---|
| `u8 arg1`, four `if (arg1 != 0) { t=4; } else { t=0; }` | 269 | baseline; this is the form matched sibling `func_151CAB78` uses |
| `s32 arg1`, four `if ((arg1 & 0xFF) != 0)` | 266 | **loses golden's `sw a1,0xfc(sp)` home store entirely** → proves the param really is `u8` (cookbook: a param is homed only if re-signed) |
| `register u8 arg1` | 269 | byte-identical to baseline |
| `temp_type = (arg1 != 0) ? 4 : 0;` ×4 | 269 | byte-identical to baseline |

Confirmed correct along the way: `spA0.unk14` must be **`u16`**, not `s16` — golden reloads it
with `lhu`, and `s16` gives `lh`. (Fixed; no longer in the residual.)

## Corpus evidence for the idiom, and why it does not reach here

Scanned all 841 `expected/build/src/*.c.o`: 78 functions open with `andi sN,aM,0xff` in their
first 8 instructions, 32 of them from live C. Two were read in full
(`game_1F4650.c func_151C9DE8`, `game_1ED0F0.c func_151BFDA0`): in BOTH, the `u8` parameter's
**first use is inside a call at the top of the function**, so the value can never live in the
argument register and IDO writes the mask straight to callee-saved. `func_151CAB78` — same TU,
same shape, matched — has the opposite: its `u8` param is tested once *before* its only call,
and it gets exactly my `andi t6,a1,0xff / move a1,t6`.

func_151CA6A0 is the awkward middle case: golden tests the param before the first call AND
needs it after three more, and golden's coalescer merged the whole chain into `$s0` while IDO
here splits the live range at the first use. No source-level lever found for that split.

## Reusable facts about game_1F4650.c (for func_151CB110 / func_151CAD28 / func_151C82D0)

* `func_1515548C(descriptor*, u8 kind, 0, 0, size, u8, s32)` returns a node or NULL; the
  caller then `memcpy((u8*)ret + 0x70, &payload, size)`. `+0x70` is the payload slot for
  every user of this API in the tree (`game_FC5F0`, `game_113D60`, `game_1F4650`).
* The 0x58-byte descriptor is `struct_150CF680` in `src/game_FC5F0.c` (fully field-named
  there) — reuse it rather than re-deriving. NOTE: field `unk14` is **u16**, not the `s16`
  that game_FC5F0.c/game_1F4650.c currently declare; it is read back with `lhu`.
  `unk14 = (1 << (obj->[0x23D] + 0xB)) | 0x50` is the layer/priority mask and the low bits
  1..2 are a 2-value alignment field poked with `x = (x & ~6) | k`.
* Payload local is **0x5C** bytes (not 0x58) in both `func_151CAB78` and `func_151CA6A0`,
  and sits immediately below the descriptor on the stack. Extra fields used only by
  func_151CA6A0: `+0x18` f32 radius (-62 or -50), `+0x1C` f32, `+0x20` f32 (1/62 = D_800AAE90
  or 1/50 = D_800AAE94), `+0x24` f32 angle (stepped by D_800AAE98 = pi/6, 12 times = a full
  circle), `+0x28` f32 = D_800AAE8C (99999).
* `D_800AAE88..D_800AAE98` are REAL GLOBALS (`asm/data/24F740.rodata.s`, a block that also
  holds jump-table words) — declare `extern f32`, no rodata migration needed.
* IDO local layout confirmed on this TU: locals are allocated **descending in declaration
  order** (first declared gets the highest address).
