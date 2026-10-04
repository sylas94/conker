# game_DADB0 is HANDWRITTEN -- do not decompile (2026-08-25)

Two pragmas, no matched code, both tiny vector helpers:

    func_150AD900(f32 *a, f32 *b)  -> a[0]*b[0] + a[1]*b[1] + a[2]*b[2]   (dot product)
    func_150AD930(f32 *v)          -> sqrtf(v[0]^2 + v[1]^2 + v[2]^2)     (magnitude)

The MEANING is certain; the codegen is not IDO's.  Evidence:

1. **FP registers run f0,f2,f4,f6,f8,f10 strictly sequentially** and never touch $f12/$f14.
   Those are free scratch in a function with no float parameters, and our IDO reaches for
   them every time.  Fifteen spellings measured -- locals for each component, six locals in
   golden's exact assignment order, `+=` accumulator, self-assigning squares, a struct
   parameter, an index loop -- and the allocation never starts at $f0.  Best 9 (magnitude,
   n=12/12) and 11 (dot, n=12/12 at plain -O2).
2. **The schedule is hand-interleaved**: `load, load, mul, load, mul, nop, mul, add, add`.
   IDO hoists all three loads first in every spelling.
3. Both functions put a COMPUTATION in the `jr $ra` delay slot (`add.s $f0` / `sqrt.s $f0`).
   That does force plain `-O2`, and -O2 does fix the LENGTH (13 -> 12 on the dot product) --
   but not the register allocation, so the flag is not the answer here.
4. It sits at 0xDADB0, wedged between game_DAC30 and game_DAE50, both already known
   hand-written (see the handwritten-math-cluster note).  The TU is 160 bytes.

Bail rather than force: a spelling that reproduces a hand-scheduled sequence would be a
fake match by construction.  If the whole 0x150A math cluster is ever migrated to .s files,
these two go with it.

## Side finding: the filled-`jr $ra`-delay-slot sweep is NOT a TU-level -g3 tell
Sweeping every pragma for a filled `jr $ra` slot returns ~39 TUs, but most of those TUs
already contain dozens of MATCHED functions built at -O2 -g3, so the tell is wrong at TU
granularity: `addiu $sp,$sp,N` fills that slot at -g3 too.  Excluding the plain sp-restore
narrows it to ~29 TUs and only a handful of functions each -- and of those, only game_DADB0
(2 of 2 pragmas, no matched code) is a clean whole-TU candidate.  The scan lives at
scratchpad/g3sweep.py.  Treat a filled slot as a PER-FUNCTION hint, never a TU verdict.
