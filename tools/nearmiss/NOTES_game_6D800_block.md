# game_6D800 / rodata block 23D420 — the cleanest remaining jtbl migration

Surfaced by `python3 tools/jtbl_blocks.py`. Second-cheapest migratable block, and structurally
the tidiest one in the whole list: **the block holds exactly two symbols, and they are both
jump tables, one owned by each function.** No float pool, no stray `D_` constants to re-emit in
order — which is what makes most of the other 14 blocks fiddly.

| function | words | bytes | frame | jump table | entries | callees |
|---|---|---|---|---|---|---|
| `func_150403C8` | 217 | 868 | 0x50 | `jtbl_80098960` | 77 | several |
| `func_15040A78` | 148 | 592 | 0xB8 | `jtbl_80098A94` | 7 | **none — leaf** |

## Start with `func_15040A78`

It is a **leaf function** (no `jal` at all) with a **7-entry** jump table. An unknown callee
prototype is the top cause of failure on this project, and this function has zero callees, so
that whole failure mode is absent. 148 words is also comfortably inside the size band that
measures best (5/9 in the 800–1200 B sweep; this is 592 B).

Globals it touches: `D_800844B0`, `D_800C6860`, `D_800C68A0`.

## Method reminders that are already paid for

* **Match with the jump table still EXTERNAL and flip the yaml LAST.** Once the table is local
  the `.text` relocation no longer names the external symbol and asm-differ can only ever show a
  residual — you lose the only fine-grained oracle. See `conker-jtbl-unlocked`.
* **The jtbl words are a direct readout of the source's `case` order** — IDO emits case bodies
  in source order, so decode the table to function-relative offsets and write the cases in the
  order the *bodies* appear in `.text`, not in numeric order. This is what made
  `func_1518BA90`'s 9-entry switch fall out first try (see `tools/nearmiss/func_1518BA90.c`).
* **Both functions must be live C before the yaml line moves.** Flipping it with either still a
  pragma breaks the link outright (`undefined reference to jtbl_...`), because nothing emits the
  table into the object while the function is still assembly.

The whole persistent change, once both match:

```
-      - [0x23D420, rodata]
+      - [0x23D420, .rodata, game_6D800]
```

then a **full** `make -C conker extract VERSION=us` (never `--modes ld`, which silently
truncates `undefined_syms_auto.txt`), then the full ROM gate. The ROM sha1 is the only valid
acceptance test for a migrated jtbl function — asm-differ can never score one to 0.

## Two frame lessons from the 24BED0 block, likely to recur here

1. **A stack struct's size is set by the frame, not by the offsets its stores span.** Both
   functions of block 24BED0 needed a struct 8 bytes larger than its written fields implied.
   IDO seats the topmost local at `frame_end - sizeof`, so check that arithmetic before chasing
   any instruction.
2. **Where two routes to the same frame score identically, the score cannot choose between
   them** — growing the struct vs. adding a local above it. A dead local is banned under the
   unnamed-frame-bytes ruling; resolve the ambiguity by finding another user of the type.
