# func_150A3FC4 (game_D0F20.c) — HARD BAIL: hand-written assembly

**Do not assign this function again. It is not C and cannot be decompiled.**
No score was taken and none is meaningful.

## Evidence (all quoted from `conker/asm/nonmatchings/game_D0F20/func_150A3FC4.s`)

1. **splat already tagged it.** Line 1 of the `.s` is literally
   `/* Handwritten function */`.

2. **No prologue or epilogue at all.** The function never touches `$sp`, yet it
   clobbers the callee-saved `$s5,$s6,$s7,$fp`. It "saves" them into *floating
   point registers* and restores them at the end:

   ```
   /* D1498 150A3FE8 44950800 */  mtc1  $s5, $f1
   /* D14A4 150A3FF4 44961000 */  mtc1  $s6, $f2
   ...
   /* D1860 150A43B0 44150800 */  mfc1  $s5, $f1
   /* D1868 150A43B8 44161000 */  mfc1  $s6, $f2
   ```
   No C compiler emits `mtc1`/`mfc1` as integer register spill slots.

3. **It branches backwards INTO THE PREVIOUS FUNCTION.**
   ```
   /* D14FC 150A404C 1100FFDB */  beqz  $t0, .L150A3FBC
   ```
   `func_150A3FC4` starts at 0x150A3FC4, so `.L150A3FBC` is *eight bytes before
   its own entry point* — it is the trailing `jr $ra` of `func_150A3A70`
   (which ends at 0x150A3FC0). Cross-function branch: unreachable from C.

4. **Other code jumps into its middle.** It carries interior `glabel`s
   (`func_150A40A8` at 0x150A40A8, `func_150A411C` at 0x150A411C) and jumps to
   them itself (`j func_150A40A8`, `j func_150A411C`).

5. **Trapping `sub`, not `subu`.** splat annotates each one
   `/* handwritten instruction */`. IDO always emits `subu` for C arithmetic.

6. **64-bit `ldl`/`ldr` in a `-mips2 -o32` build**:
   `ldl $t0, 0x0($a3)` / `ldr $t0, 0x7($a3)`.

7. **Registers live-in beyond the ABI.** `$s5,$s6,$s7,$fp` are *read* before
   any definition, i.e. they are extra arguments passed in callee-saved
   registers. It also reads a 5th argument at `lw $v0, 0x10($sp)` while having
   allocated no frame.

## Systemic finding — the screen that was missing

`func_150A3FC4` was handed out as "screened: no jump table, no splat interior
symbol run, no pooled float constant, mid-band, never attempted". All of that
was true and all of it was irrelevant: **nothing in the screen tested whether
the function is compiler output at all.**

The filter is one line and it is exact, because splat has already done the
classification for us:

```sh
grep -l 'Handwritten function' conker/asm/nonmatchings/<tu>/<func>.s
```

Repo-wide as of this run:

```
$ grep -rl 'Handwritten function' conker/asm/nonmatchings/ | wc -l
29
```

**All 29 still carry a live `#pragma GLOBAL_ASM`** (verified by matching each
one back to its `src/<tu>.c`), so all 29 are still in the candidate pool and
any of them can be drawn again. Three of them are in `game_D0F20` alone:
`func_150A3A70`, `func_150A3FC4`, `func_150A44F0`.

This extends the known "handwritten math cluster" (previously recorded as
game_D4E10 / D5500 / DAC30 / DAE50 in the 0x150A region) — **game_D0F20 is
another member of that cluster.**

Recommended: add the `Handwritten function` grep to the picker's pre-filter and
mark all 29 as permanently ineligible, rather than spending an agent-wave
rediscovering it one function at a time.
