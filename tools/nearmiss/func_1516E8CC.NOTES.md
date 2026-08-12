# func_1516E8CC — 992 B, game_19A8B0.c — **CLOSED 2026-08-11** (score 0, ROM byte-perfect)

`func_1516E8CC.c` is the WHOLE TU as shipped live in `conker/src/game_19A8B0.c`.
Kept here only as the record of how the last four rows fell.

## Verification actually run

* `python3 ../tools/asm-differ/diff.py -o func_1516E8CC -R --max-lines 4096` → `CURRENT (0)`
* same without `-R` → `CURRENT (0)`
* whole-TU compare: `.text IDENTICAL (14224 bytes)`, `.rodata IDENTICAL`, `.data IDENTICAL`
* `#pragma GLOBAL_ASM(".../func_1516E8CC.s")` gone, definition live at line 321
* **full ROM**: `make VERSION=us` → `build/conker.us.bin` sha1
  `842e3d348e3c8ae0039e2ab367ad492f9b5266d8` = `conker.us.sha1`. An A/B (HEAD version of
  the TU vs mine) produced the *same* ROM bytes both ways, so the change is ROM-neutral
  and the match is confirmed end to end.
* the function no longer contains a single `volatile` — the two casts the parked version
  borrowed from `func_1516ECAC` were **removed**, not added to.

## The two residuals and what actually closed them

### 1. `move a2,a1` vs a fresh `lbu a2,0x24(a0)` — **delete the temp, not add one**

Golden reloads `arg0->unk24` at the end of each fade branch and then CSEs the later
`idx = arg0->unk24` against that reload (`move a2,a1`). The parked version forced the
reloads with `((volatile Obj *)arg0)->unk24`, and a volatile read is never a CSE source,
so the later read became a real load.

Two independent facts closed it:

* **A store through a DIFFERENT pointer variable kills load availability; a store through
  the same one does not.** `vp->unk1F = temp_v1;` (with `vp = arg0;`) makes IDO re-issue
  the `arg0->unk24` load, exactly like the volatile did — but non-volatile, so the value
  stays available afterwards. Crucially the *register* is still `a0`: IDO's alias analysis
  keeps `vp` and `arg0` distinct while copy-propagation happily emits `sb v1,0x1f(a0)`.
  (Same split already visible in the loop: source says `vp->unk26` for init and bound,
  golden emits `lbu a1,0x26(a0)` for one and `lbu t3,0x26(v0)` for the other.)
* **Do not name the value.** With `vp->unk1F` in place, keeping `s32 temp_v0` for the
  first test rotated the whole allocation a1↔a2 (`move a1,a2` / `addu a1,a2,t3`,
  22 rows, score 125). Deleting `temp_v0` and writing the four reads as plain
  `arg0->unk24` — letting IDO do the CSE and the rematerialisation itself — is what put
  the value in `a1` and produced `move a2,a1`. Measured ladder:

  | variant | score | rows |
  |---|---|---|
  | parked baseline (volatile reads) | 405 | 4 |
  | + `} else {` wrapping the tail | 405 | 4 (inert — a null site) |
  | `vp->unk1F` store, explicit `temp_v0` reload statements | 1385 | reload hoisted above the store |
  | `vp->unk1F` store, `temp_v0` for the first test only | 125 | 22 (a1↔a2 rotation) |
  | **`vp->unk1F` store, no `temp_v0` at all** | **0** | **0** |

  Writing the reload as its own statement (`temp_v0 = arg0->unk24;` after the store) also
  loses: the scheduler hoists that load into the branch-likely delay slot and evicts
  golden's duplicated `sb`. An *implicit* reload (a plain read at the join) is not
  schedulable that way.

### 2. The trailing dead `jr ra; nop` — it is a SEPARATE EMPTY FUNCTION

Not an epilogue. Proven three ways:

* the only two live-C functions in the tree that "end" with `jr ra; nop; jr ra; nop`
  (`init_1AAE0 __n_resetPerfChanState`, `init_1E480 n_alSynDelete`) are both in `-g`
  TUs — that shape is not reachable at `-O2 -g3`, so the corpus note in the previous
  revision of this file was misleading;
* of the 14 splat-cut functions in the ROM that end that way, `game_2DF70/func_15001A08`
  has splat's own `glabel D_15001B08` sitting on those 8 bytes, and
  `game_981E0/func_15072F10` ends `lw ra / lw s0 / addiu sp,0x50 / jr ra / nop` and *then*
  a bare `jr ra; nop` with no frame teardown — which cannot be that function's epilogue;
* the tree already reconstructs exactly this: `game_981E0.c func_1507304C`,
  `game_1A5440.c static void func_15178750_pad(void) {}`.

So the fix is one empty leaf function placed between `func_1516E8CC` and `func_1516ECAC`:

```c
static void func_1516ECA4_pad(void) {
}
```

Consequence worth knowing: our object then reports `func_1516E8CC` with `.size` 984 while
`expected/` reports 992 (splat folded the orphan 8 bytes into the preceding symbol).
asm-differ still scores 0 because it diffs the whole object, but a *bounded per-function*
isolator would show two "missing" rows forever. The whole-TU `.text` compare is the
certification here.

## Levers from the old file that stayed load-bearing

`for (i = vp->unk26; i < vp->unk26 + 8; i++)`; `temp_v1 = arg0->unk1F;` written before the
`unk24` read; the compound `idx += arg0->unk1F >> 5;`; `if (temp_v0 == 0) {shift} else
{+= 8}` branch sense; interpolation term order `cur*inv + prev*frac`; `break` not `return`.
`u8` table entries feeding a float expression keep IDO's unsigned int→float path — no cast.
