# func_1516E8CC — 992 B, game_19A8B0.c — parked at 4 differing instruction rows / 248

`func_1516E8CC.c` is the WHOLE TU (`conker/src/game_19A8B0.c`) with the pragma removed
and the reconstruction live. Drop it in place to resume.

## What it is
A particle colour-ramp updater, one of the `D_8008CBA0[]` behaviour handlers
(`s32 (*)(struct Obj1516D4E8 *)`). It fades `unk1F` (alpha) up or down by `dt<<5` / `dt<<4`,
advances `unk14`/`unk16` by `dt*10`, builds a ramp index, then walks 8 keys of
`D_800A6E00[]` and lerps the RGB triple `D_800A6E0C[i-1] .. D_800A6E0C[i]` into
`unk1C/1D/1E`.

`func_1516ECAC`, immediately below it in the same TU, is an already-matched near-twin of the
first third and was the template for the fade block (including the
`((volatile Obj *)arg0)->field` reload idiom).

## Residual (isolated objdump, mine vs expected/)

```
row  36:  golden  move  a2,a1          mine  lbu  a2,0x24(a0)
row  47:  golden  addu  a2,a1,t3       mine  addu a2,a2,t3      (follows from row 36)
row 245:  golden  jr    ra             mine  (absent)
row 246:  golden  nop                  mine  (absent)
```
244 of 248 rows are byte-identical, registers included. Instruction count 246 vs 248.
asm-differ whole-object score 405 (`-o func_1516E8CC -R --max-lines 4096`); that number is
dominated by the 2-instruction shift cascading through the rest of the object, it is NOT
405 wrong instructions. `-s`/`-ss`/`-sss` all FALSE-ZERO here because golden has three
`jr ra` and the candidate has two — do not trust a stop-at-ret score on this function.

### Residual 1 — `move a2,a1` vs a fresh `lbu`
Golden's `idx` is seeded by a read of `arg0->unk24` that CSEs against the value already in
`a1`, so IDO emits a register copy. The candidate emits a real load because the two reloads
inside the fade branches are written `((volatile struct Obj1516D4E8 *)arg0)->unk24` and a
volatile read kills availability for the later plain read.
A non-volatile mechanism that still forces those two reloads would close this row. Ruled out:
* plain `arg0->unk24` (no volatile anywhere) — the reloads vanish entirely, and the
  `bnezl`+duplicated `sb` becomes `bnez`+`nop`: opcode-diff 12.
* `vp->unk24` (read through the second pointer local) — opcode-diff 13/14, extra `move`s.
* volatile *store* `((volatile Obj *)arg0)->unk1F = temp_v1` — reload appears but the
  `sb` leaves the branch-likely delay slot: opcode-diff 14.
* byte-pointer store `*((u8 *)arg0 + 0x1F) = temp_v1` — IDO still disambiguates: no reload.
* `idx = temp_v0;` (copy instead of re-read) — IDO copy-propagates it away, `idx` then
  reuses `v1` instead of `a2` and the whole loop allocation rotates: opcode-diff 5.
* `idx = temp_v0;` + testing `if (idx == 0)` instead of `temp_v0` — identical to the above.

Measured rule from this: **IDO disambiguates two accesses off the SAME pointer variable by
constant offset (store `0x1F`, load `0x24` → no reload), but NOT across two different
pointer variables.** That is the whole reason `vp` exists.

### Residual 2 — the trailing dead `jr ra; nop`
Golden ends `move v0,zero / jr ra / nop / jr ra / nop`. Corpus check: this doubled epilogue
does occur in live-C output (`init_1AAE0.c __n_resetPerfChanState`, a straight-line `void`
function), so it is reachable, but no source shape tried here produced it:
`break` + trailing `return 0` (current, best), `return 0` inside the loop + trailing
`return 0` (opcode-diff 7, and the body's exit degrades from `b` to an inline `jr ra`).

## Levers that DID move it (in order of size)
1. `for (i = vp->unk26; i < vp->unk26 + 8; i++)` — using the second pointer for the loop
   INIT as well as the bound. This single token change took the diff from 127 differing rows
   to 4: it produced golden's `move v1,a1` index/cursor split, the `move v0,a0` pointer copy,
   and aligned every remaining register. Reading the init through `arg0` and only the bound
   through `vp` was worth ~120 rows less.
2. A named pointer local `struct Obj1516D4E8 *vp = arg0;` (assigned first, so it takes `v0`).
   Without it IDO hoists `arg0->unk26 + 8` out of the loop entirely — golden reloads it every
   iteration, which is only possible if the load and the body's `sb`s go through different
   pointer variables. `volatile` on `vp` also works but costs a duplicate load at the entry
   guard (opcode-diff 7 vs 6).
3. Assignment order `temp_v1 = arg0->unk1F;` BEFORE `temp_v0 = arg0->unk24;` — swaps the two
   into golden's `v1`/`a1`. Rows 1-35 go from all-wrong to exact. (The load order in the asm
   is the other way round; that is scheduling, not source order.)
4. `idx += arg0->unk1F >> 5;` as a compound RMW, not `idx = temp_v0 + (...)`. Compound gives
   accumulator-first `addu a2,a1,t3`; the full assignment gives `addu dst,shift,temp_v0`.
   Both spellings of the full-assignment operand order produced the same wrong order, so the
   compound form is the only handle.
5. `if (temp_v0 == 0) {shift} else {+= 8}` — the branch sense follows the source exactly
   (`if (X == 0)` → `bnez` to the else body). The inverted spelling emits `beqz`.
6. Interpolation term order `cur*inv + prev*frac`, NOT `prev*frac + cur*inv`. IDO evaluates
   the operands of `+` right-to-left, so the term written SECOND is emitted first.
7. `break` in the loop body, not `return 0` (shared `b`-to-tail epilogue).

## Free / inert here
Declaration order of `idx` vs `temp` — exactly 0 change (a null site).
`idx = idx + 8` vs `idx += 8` — 0 change.
`temp` local for the `unk3F0`-style read — 0 change.

## Semantics worth keeping
`u8` table entries feeding a float expression compile through IDO's **unsigned**
int→float path (`mtc1; cvt.s.w; bgez; add.s 0x4F800000`) with no cast in the source —
that came out for free and matches golden, so do not "fix" it with an `(s32)` cast.
