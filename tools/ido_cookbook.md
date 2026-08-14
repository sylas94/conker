# IDO 5.3 -O2 Matching Cookbook — Core

The tight, high-frequency subset of IDO 5.3 (`-O2 -g3`) matching idioms — the
general codegen rules that help on a LARGE fraction of functions. Read this
before iterating.

## Language / syntax (compile errors)
- C89 ONLY: declare ALL locals at the TOP of their block. A mid-block declaration is a
  cfe "Syntax Error".
- Missing global/callee: add a LOCAL `extern <type> D_xxxx;` or a callee prototype at the
  TOP of your own .c file. NEVER edit shared headers.
- A prototype's param type must agree across ALL in-file decls/defs of a function (`s32`
  vs `u8` mismatch is "Incompatible type"). Match narrowing at the use/cast site, or
  update every local/in-file decl together — never a shared header.

## Constants (read them exactly)
- Read float/double constants EXACTLY from the `lui` immediate, never guess:
  0x3F000000=0.5, 0x3F400000=0.75, 0x3F800000=1.0, 0x40000000=2.0, 0x40400000=3.0,
  0x40800000=4.0, 0xBF800000=-1.0. One wrong constant = a tiny non-zero score on an
  otherwise-perfect diff; check immediates FIRST.
- A single-precision `f32` literal must be written to FULL precision (e.g.
  `0.352000028f`, not `0.352f`) to match the low-halfword `ori` (`lui %hi; ori %lo`).
  Recover the decimal from the full 32-bit pattern (lui<<16 | ori).
- Single vs double from the LITERAL TYPE: bare `3.64` promotes to DOUBLE
  (`cvt.d.w`/`mul.d`); `3.64f` keeps it single (`mul.s`).
- Float / int-literal arithmetic forms: `x/2` keeps `div.s` by 2.0 but `x/2.0f`
  strength-reduces to `mul.s` by 0.5; `x + x` doubles via `add.s fN,fN` while `2.0f * x`
  emits a materialized-2.0 `mul.s`. Pick the literal form to match div-vs-mul / add-vs-mul.
- An all-ones / `-1` immediate keys off the field's width+signedness: `(u16)-1` →
  `ori 0xFFFF`, plain `-1` → `li reg,-1`; a `-1` stored to a `u8`/`u16` masks to
  `li 0xff`/`0xffff` where `s8`/`s16` gives `li -1`.

## Return values
- A value still live in v0 (int) / f0 (float) at `jr ra` usually means the function
  RETURNS it — add an explicit `return <that value>;` to pin the register.
- Declare the function `void` (not `s32`) when a callee's result should flow straight out:
  `s32` makes IDO PRESERVE the result with a spurious `move v1,v0`. A `u8`/`u16` return
  type adds an `andi v0,reg,0xFF/0xFFFF` mask before `jr ra`.
- Branch-sense from `slt`+`beqz`: `slt at,a0,X; beqz at,->body` runs the body when
  `a0 < X` — write `a0 < X`, not the inverted `>=`/`!=` (which flips `beqz`↔`bnez`).
- Choose the 0/1-return SHAPE by the asm's branch form: a bare `return a < b;` (or
  `return a >= b;`) collapses to `slt;xori`/`bc1f`-fallthrough; an eager-prime form
  (`if (cond) return 1; return 0;`) primes a constant then branches to a separate
  epilogue. Match whichever the asm shows (eager-prime vs fallthrough, likely vs plain).

## Loops & branches
- Backward branch at bottom of body => `do { } while (cond);`, not for/while.
- `bnel`/`beql` are branch-LIKELY: their delay-slot instruction runs ONLY when taken.
  A plain `beqz`/`bnez` delay-slot instruction ALWAYS runs (both paths) — a store in a
  plain branch's delay slot is UNCONDITIONAL; pull it OUT of the conditional. Decide
  conditional-vs-not by the likely-bit, not by proximity to the `if`.
- `while (i--)` (implicit `!= 0`) blocks IDO's -O2 loop-unrolling that `for`/`while(i!=0)`
  trigger, and tests the raw value (`move/beqz`, not `sltu`). Use it for countdown loops.
- Constant-bound `for (i = 0; i < N; i++)` (literal `N`) UNROLLS by 4 with no trip guard;
  ANY pointer-bound form (`p != end`, `&arr[N]`, `p < end`) either injects a `divu` guard
  or fails to unroll. Use the literal-count index loop when the asm shows a clean unroll.
- A two-constant ternary's operand order sets which `li` is FIRST: `(cond)?A:B` lays out
  `li B` then `li A`; the inverted condition swaps them.
- An EMPTY if-body with a populated else (`if (cond) {} else x = 0;`) reproduces a branch
  that skips an else-only body — use it (don't invert) when the asm branches that way.

## Type & access width (loads, stores, casts)
- Intrinsics: `fabsf`→`abs.s`; `(s32)`-on-float→`trunc.w.s`; `sqrtf`→`sqrt.s`.
- A cast controls BOTH load width AND evaluation order: `*(u8*)(p+0xC)` forces `lbu`
  (vs `lh` for an `s16` field) and can force the other operand evaluated first.
- Force `lbu` vs `lb` on an `s8`-declared field via `*(u8*)&p->field` (plain `p->field`
  emits `lb`); a `(s16)` cast on a `u16` field forces signed `lh` + a signed branch.
- Narrow-int truncations need the explicit cast pair: `(s16)(s32)f` →
  `trunc.w.s; sll 16; sra 16`; `(s16)(x << n)` → fused `sll (16+n); sra 16` where a plain
  `x << n` is one `sll`. A bare cast omits the narrowing.
- Bit packing `x * 65537` => `(x << 16) + x` (shift-operand first); `s16`-type it when the
  asm sign-extends before the multiply.
- Param width tradeoff: declare a param `s32` + mask INLINE at the use (`arg & 0xFF`) when
  the asm has NO entry-narrow `andi`; a `u8`/`u16` param forces an entry `andi` + home.
  Conversely, don't re-mask an already-narrow param when scaling/indexing it.

## Globals & indexing
- `D_xxxx[idx]` is needed for `lui %hi; addu at,idx; lwc1 %lo(D_xxxx)(at)`. Pointer/byte
  arithmetic materializes a base pointer + `0(reg)` load instead.
- Index-add operand order: `base[idx]` emits `addu index,base`; byte arithmetic
  `(Struct*)((u8*)base + idx*size)` emits `addu base,index`. Pick the form whose order
  matches the asm.
- A header-DECLARED aggregate the asm derefs as a POINTER → `(*(T**)&D_xxxx)[i]`; a
  header-DECLARED SCALAR the asm INDEXES → `(&D_xxxx)[i]`. Neither edits the header.
- IDO -O2 constant-folds `D_xxxx + off` into ONE `%lo(D_xxxx+off)`. Inverse: a `%lo` at a
  small offset may be its OWN distinct symbol — declare a SEPARATE `extern` and index it.

## Register allocation & evaluation order (the usual "so close" diffs)
- Multiply/commutative operand order matters: `a*b` vs `b*a` changes the FPU DEST register
  AND the LOAD ORDER of the two operands. Swap the term's operands when a chain's loads/
  dest come out wrong. (See BAIL for the canonicalized cases that DON'T flip.)
- Source-ASSIGNMENT order (not asm LOAD order) colors v0/v1: IDO colors by the order
  LOCALS are first assigned. To put a value in v0, assign/read its local FIRST — even if
  the asm loads it second. Declaration order of locals also fixes stack-slot assignment.
- To pin a deref vs an address into specific regs, declare the POINTER local FIRST
  (`s32 *p = (s32*)(arg+off);`) THEN read `*p`. Binding a field-loaded pointer to a NAMED
  local lands it in v0 where an inline `*(s32*)arg->f` lands a t-register.
- Plain truthiness (`if(x)`/`if(!x)`) reuses a value already live in a register; the
  explicit `x != 0`/`== 0` form can inject a spurious `move v1,v0`. Prefer bare
  truthiness when the asm reuses the register with no extra move.
- The OPERAND ORDER of an equality test steers `bnel`/`beql` register order (`a==b` vs
  `b==a`). (Plain `beq`/`bne` is canonicalized — see BAIL.)
- A compound RMW (`x += A*K`, `x &= ~m;`) emits accumulator-FIRST order and loads the
  lvalue EARLY, steering the schedule; a plain `x = x + A*K` reverses it. Reassigning a
  result back INTO a local that held one of its operands REUSES that operand's register.
- Modify a param in place (`arg0 += 1;`) to reuse the incoming aN register as the result;
  a fresh expr/local uses a temp.
- A conditionally-assigned value spills (`if (cond) x = ...;` homes `x`); a ternary
  `x = cond ? A : B;` keeps it in a register with a `move` default.
- Hoist a `p = &arg->sub` pointer ONCE above an if/switch chain to keep the sub-object
  base in a value reg (`addiu vN,base,off` per branch); per-branch access folds it into
  `off(base)` loads. Only stays distinct if you read/write THROUGH `*p`.

## CSE & store/load duplication
- Defeat DCE of intermediate RMW stores to the SAME address (`*p |= 0x80; *p &= 0xBF;`
  before a final overwrite): cast the lvalue `(volatile u8*)` to keep every `sb`.
- Distinct bit-op statements on DIFFERENT bits of the same field (`f &= ~0x2; f |= 0x8;`)
  are NOT dead — each keeps its own load-modify-store. Write each as its own statement
  when the asm shows one cycle per bit.
- Defeat DCE of all-but-last stores to a PLAIN global by having the NEXT statement READ
  the global back (`arr[i] = D_glob;` after `D_glob = ...`) so each `sw` stays "observed".
- Force a field RELOAD / defeat CSE across a call (or for a duplicate load) by reading the
  two uses through DIFFERENT types/casts, or via a `volatile`-cast pointer
  (`*(T *volatile *)((u8*)arg + off)`). Same-typed reads CSE into one load.
- A pointer written THROUGH (or a global pointer variable) RELOADS before the next access
  (can't prove no-alias). Store straight through `p->field`/`D_glob_ptr->field`; don't
  cache the pointer once when the asm re-loads it.

## Stack frame, homing & params
- Param homing: a param is NEVER homed if only forwarded/used as-is; it IS homed
  (`sw aN,off`) if reassigned or re-signed. Forward ALL args through to callees to
  suppress a spurious dead-param home; verify against a matched sibling's objdump.
- In-place forwarder: pass the callee's first param THROUGH UNCHANGED (`f(arg0, ...)`) →
  NO `move a0`, slot stays `nop`. A literal `0` emits `move a0,zero`.
- A 5th (stack) argument FORCES a frame + the sp+0x10 slot, regardless of type; ≤4 args
  stays frameless. Count callee args from sp+0x10/0x14/0x18 to fix a wrong frame.
- Reverse-engineer stack-local TYPES/SIZES and frame from the CALLEE's store widths
  (`sh`→`s16[]`, `swc1`→`f32[]`, `sb`/`sw`→`u8`/`s32`). Size a stack buffer to the EXACT
  bytes written: an oversized array pads to the next 8-aligned size and shifts the offset.
- SOURCE POSITION of the definition controls object emission order: define the body at its
  ORIGINAL position (leave a forward decl where an old prototype sat). Suspect this when a
  byte-correct body scores in the thousands.
- When a near-identical SIBLING already matches, mirror its exact C structure (call order,
  arg casts, last-arg literals) — often a 1-try match.

## A FAILED BUILD still scores 0 — always delete the object first
`asm-differ` scores whatever object is on disk. If your edit does not compile, `make` fails but
the PREVIOUS object is still there, and the differ happily reports the score it had before.
Caught live: a macro whose parameters were named `(w0, w1)` got substituted into `_g->words.w0`,
producing `cfe: Error: line 121: Syntax Error` — and the score still read 0 from the stale object.

Before believing any score:

    rm -f build/src/<tu>.c.o build/src/<tu>.c      # object AND asm-processor intermediate
    make -s build/src/<tu>.c.o VERSION=us || exit  # hard-fail, do not continue
    test -f build/src/<tu>.c.o || exit             # and an object was actually produced

Related trap: IDO's `cc -c -o "<path with a space>"` **exits 0 while writing no object at all**,
and the repo path contains a space. Any tooling that compiles outside `make` must use a
space-free output path (see `conker/permuter_tu.sh`).

### The strongest single check: compare the whole TU's .text
Per-function scoring can miss collateral damage. This proves the match AND that nothing else in
the file moved, in one step:

    mips-linux-gnu-objcopy -O binary --only-section=.text build/src/<tu>.c.o    /tmp/mine.bin
    mips-linux-gnu-objcopy -O binary --only-section=.text expected/build/src/<tu>.c.o /tmp/gold.bin
    cmp -s /tmp/mine.bin /tmp/gold.bin && echo IDENTICAL

## Diagnosing a FALSE non-zero score
- **A score for a function over 4096 bytes is measured on a PREFIX unless you pass
  `--max-lines`.** `diff.py --max-lines` defaults to 1024 and caps the diff at
  `max_lines * 4` = 4096 **bytes**; past that it emits a `...` row, and
  `score_diff_lines()` then rewinds to the end of the last 50-instruction matching streak
  and stops counting. func_1517BBAC (5144 B) read **791** by default and **40536** truncation-
  free, and a whole wave planned around that 791 as a hard plateau. Worse, the ranking
  INVERTS: a candidate reading 123 was truly 40381 while one reading 594 was truly 38831.
  **Always score with `--max-lines 4096`** (`tools/iter_match.sh` now does; a bare
  `diff.py -o <func> -R` does NOT). No effect at or below 4096 B — verified identical, and
  still 0 for functions that genuinely match. Only 12 remaining stubs exceed the limit, but
  they hold 5.4% of the remaining bytes and are exactly what a byte-first strategy selects for.
- A switch that matches byte-for-byte but scores non-zero may be ONLY compiler-jtbl
  rodata refs (anonymous LOCAL `.rodata` vs a NAMED jtbl symbol). Re-run with
  `-R`/`--no-show-rodata-refs`; a clean 0 confirms matched.
- A large whole-object / short-function score is often the Levenshtein of ADJACENT
  GLOBAL_ASM stubs bleeding into context. Verify in ISOLATION: `diff.py -o func -s`
  (stop-at-ret) shows 0, or raw-objdump the function's own symbol-size byte range.
- Score MAGNITUDE tracks FUNCTION SIZE, not wrongness: on a big function ONE early
  residue (a wrong reg/reloc/extra instr) shifts every later instruction and inflates
  the score into the hundreds/thousands. Diagnose the FIRST diverging instruction and fix
  THAT — do NOT chase the magnitude or assume a high score means "far". A 1200-score func
  is often one fix from 0; a 40-score func can be genuinely unsteerable.

## When to BAIL — compact checklist (one signal per line)
After ~4-6 iterations, if the ONLY residual is one of these, STOP, record best score,
REVERT to the stub, flag as a decomp-permuter candidate. Judge the func in ISOLATION
(objdump its bytes) — a single nop/JUSTREG can 4-byte-shift later functions and inflate
the per-object score far above the true delta.
- Single-register JUSTREG ('r' markers, all else identical) or a lone delay-slot
  placement diff — IDO won't be steered there from C.
- Canonicalized operand order: plain `beq`/`bne`, `mul.s` mem-first, `multu`/`mult`
  fresh-load-rs — not flippable from C (only LIKELY `bnel`/`beql` is steerable).
- IDO never uses `$at` as a general compiler temp from C (except the struct value-copy
  width trick).
- Coupled/cyclic JUSTREG (fixing one reg diff forces another) or a CSE mismatch (target
  re-loads where IDO collapses your two identical accesses).
- Native 64-bit ops under -mips2/-o32 (`ld`/`sd`/`dsll32`/`dsrl`/`dsra32`, `sd $zero`) —
  IDO lowers `long long` shifts to helper CALLS and word-splits 64-bit copies.
- Jump-table externalized: expected `.c.o` references an EXTERNAL jtbl symbol; C emits a
  LOCAL `.rodata` table and fails to link. Leave as a GLOBAL_ASM stub.
- Same-symbol read+write via SPLIT `lui %hi`/`%lo` (separate lui for load vs store): -O2
  CSEs both into one pointer; no C form splits them. (Distinct: an unsteerable
  split-base-vs-fold of `D_xxxx + off`.)
- Hand-written asm: surplus float args in non-ABI FPU regs ($f6-$f11), `ra` in a t-reg +
  `jr $t9` no-frame tail-call, or lazily-scheduled int→float arg conversions with no
  frame. Leave as GLOBAL_ASM.
- -g3 schedule/home artifacts: trailing dead doubled epilogue, callee-saved promotion of a
  cross-call pass-through, an opportunistic param-home filling an empty jal delay slot, a
  loop-rotation/strength-reduction reload, or a TU-temp-counter-driven spill-slot offset.
- Reloc-spelling on IDENTICAL bytes: the only residual is `%lo(sym)` vs `%lo(sym+off)` (or
  hi/lo paired to a different symbol) while the encoded BYTES match — a relocation-display
  artifact, not a codegen miss. Not steerable from C; confirm bytes in isolation and BAIL.
- Stack-aggregate off-by-one-WORD: a struct/array stack local whose frame offset is exactly
  one word (4/8 bytes) off, cascading every sp-relative access. Driven by IDO's spill-slot
  packing, not your declaration order — adding/removing a local just moves the cascade. BAIL.

NOTE — `register`/`volatile` as a LAST resort: a `register` hint or `volatile` local can
steer a stubborn value, but under -g3 it GROWS the frame (forces a home/spill slot) and
often trades one diff for a frame-size diff. Try every non-storage lever first; reach for
these only when nothing else moves the diff, and revert if the frame size shifts.
STALL RULE: if BEST has not improved for ~3 iterations AFTER you've diagnosed the FIRST
diverging instruction and tried its indicated fix, treat the diff as a plateau — record
best, REVERT to the stub, flag permuter. Do not keep grinding a stalled diff for magnitude.

For a stubborn diff, a specific instruction pattern, or a BAIL judgment not covered here,
grep ~/conker/tools/ido_reference.md (the full idiom set, organized by section).

## Locals, stack homes and the temp counter (wave 2026-08-08, game_77AD0/func_15052F9C)

Four levers found while taking one function 2179 -> 165. All are about *where IDO puts
things*, not about what the code computes, so they apply to any -O2 -g3 near-miss whose
diff is register/offset noise rather than wrong instructions.

- **Declaration order pins stack homes.** IDO assigns local homes DESCENDING from the top
  of the locals area, in DECLARATION order. So the spill offsets in the golden asm read
  back the original declaration order exactly: a locals area of 0x30..0x47 with spills at
  0x44/0x40/0x3C/0x38/0x34/0x30 means six locals declared in that order. Recovering it
  took 2179 -> 910 in a single edit. Do this FIRST on any function with spills — it is
  free information sitting in the asm.
- **A local spilled with `sw`/`lw` must be word-typed.** Declaring `s8 state` emitted
  `sb 0x35($sp)` + `li -0x7f` where golden had `sw 0x30($sp)` + `li 0x81`. Match the
  spill WIDTH in the asm to the C type.
- **The t-register counter is a statement-order oracle.** IDO walks t0..t9 round-robin in
  SOURCE-STATEMENT order; one missing or extra temp shifts every downstream t-number. So
  a uniform t-rotation in the diff means your statement count is off by one temp, NOT that
  your logic is wrong — do not rewrite the logic chasing it.
- **Burning exactly one temp without emitting an instruction.** When the block needs one
  MORE temp than the natural form consumes, write the store first and read the field back:
      other->unk76 = arg0->unk7A;  angle = other->unk76;   /* 430 -> 165 */
  instead of `angle = arg0->unk7A; other->unk76 = angle;`. Store-to-load forwarding means
  no extra instruction is emitted, but the temp counter advances. This is a legitimate
  period-authentic shape, not a forcer — the original programmer plausibly wrote either.
- **Source LINES matter, blank lines do not.** Two statements on the SAME source line can
  be reordered by the scheduler; on separate lines they are emitted in source order.
  Blank lines, brace placement and comments have zero effect — stop trying them.

### Unsteerable: the unconditional-branch delay-slot strategy
IDO fills a `b`'s delay slot two different ways and both occur in the same function:
  (a) SINK  — move the block's own last instruction down into the slot;
  (b) COPY  — duplicate the SUCCESSOR block's first instruction into the slot and retarget
      the branch past it (`b .Lmerge+4`).
Golden used (b); ~45 scored builds could not find a source form that selects it. Ruled out:
statement order of the trailing stores, storing through a loaded pointer, source
formatting, hoisting the store into the merge block, comma-operator and chained-assignment
forms. If your ONLY residual is a 4-byte shift from delay-slot strategy, treat it as a
plateau and BAIL per the STALL RULE — it is not reachable from honest C.

## Float-literal spelling, and flag artefacts (wave 2026-08-09, libultra/gu)

Two levers found while removing undefined behaviour from cosf.c. Both are general.

- **Break a float-constant CSE by changing its SPELLING, not the code.** IDO pools
  *identical* float literals within a function into one value with one long live range,
  which ties up a register across the whole block. Writing two occurrences differently --
  `if (0.0f < x)` and `if (0.f <= t)` -- splits them into two short-lived pool temps and
  shifts the FP allocation, with no instruction added or removed. cosf.c depends on this;
  normalising the spelling there silently breaks the match (measured: diff=92). Consider
  this before reaching for a chained-mask or dummy-local forcer.
- **A working copy is an honest substitute for an uninitialised read.** An uninitialised
  read makes a variable live-in at function entry, so it becomes one web spanning the
  block and gets a long-lived register instead of a short pool temp. A real `y = x;` copy
  placed before the value is consumed reproduces that legitimately. This is what let
  cosf.c stop reading two uninitialised locals (real UB) while keeping the match.

**Not every "forcer" is a forcer -- check the FLAGS first.** guNormalize.c carried a
trailing `dummy_label:` that turned out to compensate for a compiler flag, not codegen:
the plain unmodified SDK source is byte-identical at `-O2 -g0`, while at the tree default
`-O2 -g3` IDO schedules `addiu sp,sp,24` into the `jr ra` delay slot, which the shipped
code does not do. **libultra was shipped built without debug info.** The honest fix is a
one-line per-file `OPT_FLAGS` override in conker/Makefile (the mechanism already exists --
init_3920.c.o uses a bare `-O2`), not C surgery.

DIAGNOSTIC, cheap, do it first on any stubborn libultra/SDK-derived site: compile the clean
canonical source outside the build system across the `-g0/-g1/-g2/-g3` x `-O1/-O2` grid and
diff against `expected/`. If a flag combination matches, stop -- it is a flag artefact.

**IDO's redundant-load CSE is keyed on the C TYPE of the access, not just the address.**
A null test and a following deref of the same word get CSE'd into one load; writing the
test as a same-address, different-type read -- `*(s32 *)&obj->ptrField != 0` -- keeps both
loads. This replaces `volatile` on a struct field, which is much worse because it changes
the type for every user of the typedef and claims the memory is externally modified.

**Structurally closed, do not re-probe:** all 46 unreferenced-label sites
(`dummy_label_*`, `trailing_label_*`, `block_*`, bare `done:`/`skip:`) were probed --
0 deletable, 0 reshapable. An unreferenced label is an instruction-free basic-block
boundary and has no honest C equivalent. Same for the 18 chained no-op mask sites: they
are temp-counter forcers (removing N masks rotates the temp pool by -N mod 10) and only
one, game_F2820.c:103, had a reshape (operand re-association).

## Mine the matched corpus for the golden byte pattern (2026-08-09, func_15007168)

The strongest technique found so far, and it replaces guessing entirely. When you cannot
work out what source shape produces a stubborn instruction sequence, **stop guessing and
go find the sequence in code that already matches.** 611 built objects in `build/src/`
are, by definition, proof of what IDO emits for known-good C.

    for o in build/src/**/*.c.o; do mips-linux-gnu-objdump -d "$o"; done > /tmp/corpus.dis
    # then grep the corpus for the golden opcode pattern, and read the C that produced it

Worked example. `func_15007168` died two bytes short for ~100 attempts: golden emits
`lui $v1 ; lui $v0` (DESCENDING register order) and every hand-written variant produced
ascending. Searching the corpus for `lui rA ; lui rB ; addiu rB ; addiu rA` found 128
descending sites; one was `func_15008DD0` in game/done/game_36280.c, whose entire body is

    s32 i;  for (i = 0; i < 2; i++) { D_800DD460[i] = 0; }

So a descending lui pair is the signature of a **strength-reduced index loop**, not of two
pointer locals: the loop optimiser creates the limit's web first (colouring it `v0`) but
emits the derived cursor's address first (so `lui v1` leads). Rewriting the clear loop from
a two-pointer do-while to `for (i = 0; i < 0x68; i++) D_800BE2F0[i] = 0;` reproduced all
four instructions on the first try, and the function went to zero differing bytes.

GENERALISABLE RULE: two address materialisations whose `lui` order is DESCENDING by
register number => write an index loop over an array, not a pointer walk.

BEWARE OVER-GENERALISING A SWEEP. A 72-cell sweep (declaration order x assignment order x
same-line/multi-line x three do-while shapes) found `lui $v0` first in ALL 72 cases, and the
earlier attempt concluded IDO does this unconditionally. It does -- *for the pointer-local
family*. Golden itself was the counterexample sitting in plain sight. If an exhaustive sweep
says something is impossible but the golden code does it, your sweep is exploring one family
and the answer is in another.

RELATED, cheap, do it first: **verify every callee prototype against its real definition
before any codegen surgery.** func_15007B3C went 522 -> 470 from a single fix -- a callee
declared `(void)` that is really `(s32)`. Passing the loop counter put it in `$a0` with no
move and flipped the whole loop's register assignment to match golden.

## Temp creation order, and the negative test that kills whole families of guesses

Derived closing func_151EA15C (3232 B). It took the last 13 divergent rows to zero in a
single build, after ~100 builds of shape-guessing had failed.

**The rule.** IDO hands out stack homes for COMPILER-MANAGED values (CSE temps, hoisted
subexpressions) in DESCENDING address order, in order of temp CREATION. Creation numbering
follows C STATEMENT order, and RIGHT-TO-LEFT within a statement. Measured across the matched
corpus: 73% of >=5-argument call sites materialise the stack argument before `a0`, and for
`a->x = b->y;` the RHS address temp is numbered before the LHS.

So: **map golden's compiler-managed slots in descending address order and you have read off
the original creation order.** Do this before writing expressions, not after.

**The negative test — this is the valuable half.** If a temp is numbered AFTER the temp
belonging to the LAST statement of the block, it cannot have been created by the front end
walking the statement where it appears. It must be synthesised by a later pass (copy
propagation / CSE). Therefore **no reordering of statements or arguments can ever produce
it**, and your C must not name that expression directly.

Worked example. Golden numbered the `xbase + 0x3C` temp after line 375's temp — the last
statement of the loop body — while the expression appears at line 357. That single
observation killed the entire "shuffle the statements / shuffle the arguments" family before
a build was spent on it, and pointed straight at the fix: an earlier `x = xbase;` made `x`
and `xbase` provably equal, so writing

    func_15042D94(x + 0x3C, ...)      /* not xbase + 0x3C */

makes the front end create an `x + 0x3C` node; `xbase + 0x3C` then only comes into existence
when copy propagation substitutes `x` and CSE folds it — a later-pass temp, hence the last
number. One token, 13 rows.

Corpus exemplars confirming the home-ordering rule independently of decomp style:
`game_B3020.c func_1508BF14` (four `base + constant` locals taking strictly descending homes
in statement order), `libultra/audio/n_synallocvoice.c`, and `game_1FA770.c func_151D1138`
(RHS-before-LHS numbering).

### A non-zero score can be a genuine byte match
func_151EA15C shipped at **score 10**. The residual was 2 rows where golden reads
`%hi/%lo(D_8008FE48)` and the C emits `%hi(D_8008FE44)` + `%lo(D_8008FE44+0x4)`.
`D_8008FE48` is a splat AUTO-GENERATED symbol (`undefined_syms_auto.txt`) invented for that
interior address — exactly what a strength-reduced pointer walk emits. Both pairs resolve at
link time to `3C108009 / 2610FE48`, and the `%hi` is 0x8009 either way since both offsets
have bit 15 set. asm-differ is comparing an unlinked `.o` relocation against splat's
symbolised disassembly.

When your only residual is relocation SPELLING against an auto-generated symbol: hand-resolve
the HI16/LO16 pair, confirm the bytes, and let the ROM gate be the arbiter. Do NOT invent an
`extern` array bound to silence it — that is a fake, and the score is not the deliverable.

### L2 caveat, measured
Declaration order pins stack homes **only for locals whose homes are actually referenced**.
Permuting 11 unreferenced locals in func_151EA15C changed the score by exactly zero — only
the COUNT mattered (it sets L, hence the frame). Do not burn builds permuting locals that
are never spilled.

**Corrected 2026-08-10 — the stronger version of this claim was wrong.** An earlier revision
of this section read "on big functions the s-register assignment is allocator-internal, not
source-ordered; stop permuting declarations." That is false, and it was arrived at exactly the
way bad rules always are: two single permutations came back at zero, and the zero was
generalised.

What actually holds. Permuting locals at a **null site** — locals never spilled, or not
contested for a register — is free: swapping `mid`↔`d2` in func_1517BBAC and `j`↔`y1` in
func_15093B58 both scored **exactly 0** change. Permuting a local whose allocation *is*
contested is worth hundreds: on func_15093B58's `bigMap` base, moving `bigMap` from last to
first cost **+658**, moving it after `half` cost **+722**, and moving `j` after `y1` — the
very swap that had been free on the other base — cost **+400**.

Both measurements are real; they differ because the *base* differs. So:

> A null result from one permutation licenses nothing. Declaration order is inert for
> uncontested locals and load-bearing for contested ones, and which is which changes as soon
> as the surrounding source changes. Re-probe on the base you actually intend to ship.

The cheap discriminator: if the local has a stack home that golden references, or is live
across a call, its position is load-bearing. If it never spills, don't spend builds on it.

## The register-colouring wall, and why score misranks variants (wave 2026-08-10)

Two 3000–5000 B functions were driven to structural correctness and both stalled the same way:
`func_1517BBAC` 40705 → **791**, `func_15093B58` 6200 → **3575**. Neither residual was a
misunderstanding of the code. Both were *graph colouring* — golden and IDO filled the same nine
callee-saved registers with different sets, and every downstream row cascaded from that.

**The lesson that costs the most if you miss it: asm-differ's score MISRANKS variants near the
end.** In func_15093B58 the winning structural insight — caching parameter 5 in a local instead
of re-loading it twice — collapsed golden's two `lbu` loads into one, removed both speculative
hoists, and dropped the structural diff to 7 inserts / 7 deletes / 9 reorders. It scored
**4350, worse than the 3575 it replaced**, because an exact structure with a 4-register
permutation on top costs ~323 register rows while a wrong structure with lucky registers does not.

> Track **inserts / deletes / reorders** separately from register-only rows. Instruction
> structure converges to zero; a register permutation over an exact structure is one lever away.
> A lower score over the wrong structure is not close to anything.

`diff.py -o <func> -R` categorises rows; count them. func_1517BBAC's 791 was 464 register-only
out of 1105 rows — i.e. 42% of the "score" was one bad colouring, not 464 mistakes.

**What actually moves a colouring:** removing a loop-invariant hoist that is eating a
callee-saved register (func_1517BBAC lost two registers to `&D_800BE9C0` and to a hoisted
literal `26`, where golden spent them on the loop counter and a different address); or adding
a cached-pointer local so a value stops being rematerialised. Declaration order and
assignment-statement position are **measured no-ops** for this. If no source-level lever
exists, that is what the permuter is for — bail and hand it the seed.

### Sub-laws banked from the same two functions

**Loop bound opacity decides unrolling.** A compile-time-known bound makes IDO peel 3 and
unroll ×4. If golden's loop is *not* unrolled and has *no* entry test, the bound is opaque —
write a `do { } while (p < &SYMBOL);` against the splat symbol for the end address, not a
counted `for`. (`extern u32 D_800DDC7C;` used as a fill-loop bound is honest and load-bearing.)

**A 2-D array is not its flattening.** `s32 (*)[26]` subscripted `[type][k]` and
`((s32*)&base)[type*26 + k]` generate different code. The 2-D form was worth 160 points and
collapsed the compiler-temp area from 12 words to 10. Same family as the struct-vs-array trap.

**`x * 3` has exactly one spelling.** Seven forms probed with the project's exact flags
(`x*3`, `3*x`, `u8 arr[][3]`, `&arr[i*3]`, pointer arithmetic, s16/s8/unsigned index): every
multiply and every array-scale form emits the CSD reduction `sll t,x,2; subu t,t,x`. Only a
literal addition chain written as a **reassigning statement** — `idx = idx + idx + idx;` —
emits golden's `addu t8,s0,s0 / addu s0,t8,s0`. Inlined into the subscripts instead, it cost
−2400 in register churn.

**Ternary ≠ if/else, and it reaches the float registers.**
`bh = (D_8008FE1C == 1.0f) ? 4 : 6;` was worth **1810 points** over the `bh = 6; if (...) bh = 4;`
form. It produces golden's `li 6 … bc1f JOIN / b JOIN + li 4` layout *and* simultaneously flipped
two unrelated float locals into golden's `$f24`/`$f26`. Swapping their declaration order had
done nothing — the ternary was the lever.

**`==` operand slot.** `if (D_8008FE1C == 1.0f)` emits `c.eq.s $f4,$f0` — IDO puts the **right**
operand of `==` in the `fs` slot. `1.0f == D_8008FE1C` gives the reversed encoding.

**Constant folding into `%lo`.** `func(…, (s32)(D_CF2 + 1), …)` folds to `%lo(D_CF2+0x1)`;
`(s32)D_CF2 + 1` emits a separate `addiu`.

**Read the arithmetic order, not the store order.** Independent `sh` stores are scheduled, so
their order is not source order — but the `addu`/`subu` that feed them *are* in source order.
Golden computed both maxima before both minima, so the source reads
`xmax = px + range; xmin = px - range;`, not the store-order reading. Worth 190 points.

**IDO deletes a dead increment.** An explicit `v++` after `v`'s last use produced an identical
instruction count. A trailing `addiu $sN,$sN,0x10` in golden is therefore never a plain dead
increment — look for a real remaining use.

## The loop-invariant ranking tie (2026-08-10) — a named BAIL signal

Six functions were driven to their recorded near-miss scores and every one of them ended in
the same shape: **9-11 rows, 100% register-only, zero structural rows.** This is now a
recognised terminal state, not a sign you are close in a useful way.

The mechanism. IDO hoists loop-invariant values into callee-saved registers and assigns them
to slots in a fixed order, ranking candidates by a depth-weighted reference count. When two
candidates tie, or rank within one of each other, which one gets `$s6` versus `$s7` is decided
inside the compiler with **no source-level handle at all**. Worked examples:

* `func_1502BAD0` @45 — four hoisted constants; golden takes them (0xFF, 1, 7, 2), we get
  (0xFF, 7, 1, 2). Only the 1 and 7 swap, and that cascades into 7 branch-operand rows. Use
  counts were verified IDENTICAL on both sides (1 → 4 uses, 7 → 3, 2 → 6, 0xFF → 2).
* `func_1506AD30` @45 — the 0xC stride scores 21, the `&D_800D1580` base scores 20; they land
  in each other's registers. Ten forms across two sessions moved nothing.
* `func_150585F0` @10 — **two rows**, one scratch float register for a call argument bound to
  `$a3`. 21 source forms all produced `$f0` where golden has `$f14`.
* `func_150A09D0` @20 — two `addu`s in `jal` delay slots emitted (base, induction) where golden
  has (induction, base). 11 pointer spellings all canonicalised the same way; the other 8
  `addu`s in the same function already match.

> **BAIL RULE.** If the residual is 100% register-only with zero inserts/deletes/reorders, and
> two or more independent source spellings leave the score EXACTLY unchanged, stop. The
> allocation is internal. Record the register map and move on — this is not a permuter job
> either unless the permuter has a structural handle to pull.

The cheap diagnostic: dump the golden and candidate register assignments side by side. If use
counts match and only the register NAMES differ, there is nothing in the source to change.

### What DID close one: the address-taken-local store barrier
`func_15121490` @115 was the one function of the six that reached 0, and the lever generalises.

Golden kept `arg0->unk31C` in a **cross-block CSE temp** (`$v1`) for the reads before a call,
then copied it into the saved register for the stores after (`move s0,v1`). Three edits, only
in combination, reproduce that:

1. spell the guard as `state = arg0->unk31C->unk78;` — **not** `stats->unk78` — so IDO creates
   the CSE temp in the pre-branch block at all;
2. make `stats = arg0->unk31C;` the **first** statement of the merge block, so it CSEs against
   that temp and emits `move s0,v1` rather than a fresh load;
3. leave the later read as `stats->unk114`.

The load-bearing rule underneath, worth remembering on its own:

> **A store into an address-taken local aggregate kills IDO's available-expression set.**
> Everything live across it gets reloaded.

`stats = ...` had to precede the first store to `endPoint` for exactly this reason — placing it
after cost 770. Spelling the later read as `arg0->unk31C->unk114` after that store also reloads
(814/920), and hoisting it into a fresh float local fixes the read but costs +8 of frame
(1315/3349). When a value you expect to be CSE'd is being reloaded, look for a store to an
address-taken local between the two uses before you touch anything else.

### When the permuter cannot be used at all
`conker/permuter_tu.sh selftest` must pass before its output means anything. Two TUs failed it
in different ways, both fatal:
* **game_83300** — check (b2), the pycparser round trip, produced a disassembly whose sha1 is
  `da39a3ee...0709`, i.e. **the empty string**: the function vanishes entirely from the
  round-tripped source, so the permuter would be optimising nothing.
* **game_1B1600** — (b2) fails AND the (d) negative control fails (a deliberately perturbed
  source scored 630, identical to the baseline 630). A negative control that passes for free
  means the harness is not measuring the function.

Both TUs are dense in block-scoped `{ Gfx *_g = ...; }` gbi macro expansions, which pycparser
regenerates in a form IDO compiles differently. On such TUs, hand-match or bail.

### L0 correction: flag-sweeping a TU whose .text is injected asm is meaningless
The all-pragma flag sweep only works while the TU still contains genuine compiled C. For a TU
that is *entirely* GLOBAL_ASM, every flag setting produces the same injected bytes and the
sweep "passes" for all of them. The correct form of the test there: put your C in, and check
that **other, already-matched C functions in the same TU still score 0** against
`expected/build/src/<tu>.c.o`. That is what proved game_BC510.c is tree-default `-O2 -g3`.

## Register-tie levers that actually moved the score (wave 2026-08-11, game_13D350/18D770/1C2C60)

Four independent findings from one wave, all measured both ways (applied, reverted, re-applied).
They belong together because each one is a *handle* on an allocation the score says is untouchable.

### 1. Float-literal spelling controls whether IDO POOLS a constant across statements
`func_15114348` initialises an identity triad with `1.0f`/`0.0f`, then immediately calls
`guRotateF(mtx, angle, 1, 0, 0)` needing the same numbers. Spelled `1.0f, 0.0f, 0.0f` IDO shares
the initialiser's constants, keeps them live in FP registers and passes them with
`mfc1 a2,$f2`/`mfc1 a3,$f20` — **diff 345**, with the whole FP allocation rotated on eight rows.
Spelled `1.f, 0.f, 0.f` the pools split, `1.0f` dies after its last store, and IDO materialises
the arguments as golden does (`lui a2,0x3f80` for the integer-register argument, a fresh
`mtc1 zero,$f0` feeding both `mfc1 a3` and the stack slot) — **diff 0**.
Try this BEFORE any structural surgery when the residual is an FP-temp rotation plus a couple of
constant-materialisation rows. It costs one edit.

### 2. `&arr[i]` and `arr + i` are NOT interchangeable with `arr[i].field`
Both `&arr[i]` and `arr + i` emit `addu dst,index,base`. Only direct subscripting emits
`addu dst,base,index`. Corollary measured on a global: `#define OBJ ((T*)&D_800DBEF4[arg0])` gave
`addu v0,base,s1` at four of seven sites and `addu tN,s1,base` at the other three *from the same
macro*; rewriting as `((T*)((u8*)D_800DBEF4 + arg0*0xA0))` made all seven base-first and took the
score **30 → 0**. If a residual is nothing but swapped `addu` operands on `global[idx].field`,
re-spell the address arithmetic — do not reach for the permuter.
(This refines the existing "Globals & indexing" bullet: the pointer-local forms side with the
*index-first* order, not with the subscript form they look like.)

### 3. Naming an interpolation fraction aligns the whole FP file
`func_15162B28` went **503 → 200** the moment `rise`/`fall` became named locals instead of inline
sub-expressions — every single `$f` register then matched. This is the float analogue of the
statement-split trick: a named local gives the value its own live range instead of letting it
rotate through the FP temp pool.

### 4. Stack homes are per USED local, in declaration order, lowest address first
At `-O2 -g3` every named local gets a debug slot even when it lives entirely in a register. Among
locals that are actually *referenced*, slots are handed out in **declaration order from the lowest
address of the local area up**; never-referenced locals are appended after them (4-dummy probe:
frame 0x28 → 0x38, used pointer stayed lowest regardless of where it was declared).
So when a diff is all `s` marks plus a frame-size delta: count USED locals and reorder them.
**Size matters, not just count** — in `func_15196748` golden needed 17–18 bytes of locals; 16 put
the spilled temp at 0x24 instead of 0x20 and 20 pushed the frame to 0x40. The fix was adding a
genuinely-used `s8` (+1 byte, no codegen change); an `s16` or `s32` perturbed allocation instead.

### NEGATIVE result — the frame does not respond to the declaration list
`func_150611E8` is the counter-example that bounds finding 4. Its golden creates 8 homed values,
mine 12, and the count did **not** move when a local was deleted (`node`, twice), when two were
deleted, or when locals moved between block scope and the top-level list — all left the frame at
0x48. Only *adding* a fourth pointer local moved it (0x50). So frame size tracks
**compiler-managed temp creation**, and there is no "declare N fewer locals" dial. Attack it from
the CSE side (which repeated subexpressions get a temp), not the declaration list.

### `beqzl`/`bnel`/`bc1fl` with the target's first instruction duplicated in the delay slot
(i.e. branching to target+4) is IDO's fallback when the delay slot cannot be filled from the
current block. Two residuals this wave were exactly one such duplication, and in both the
duplication was **forced by the register allocation** — the register the target instruction
defines was still live on the taken path. Never chase it directly; fix the allocation and the
instruction appears for free. A diff that is one duplicated instruction is a register problem
wearing a scheduling costume.

### The unroll factor is set by the loop body AS WRITTEN, before LICM
In `func_150611E8`, writing the array base expression twice in the body unrolls the loop **x2**
(`andi v0,count,0x1`); assigning it to a pointer variable once at the top of the body unrolls
**x4** (`andi v0,count,0x3`) and reproduces golden's whole two-preamble structure — worth ~3000
diff points, and invisible unless you compare the `andi` mask against golden. Assigning the base
*inside* the loop rather than hoisting it above is also what makes IDO re-derive it in both
unrolled preambles and keep the argument on the stack instead of promoting it to a callee-saved
register.

## Source LINE placement is a scheduling lever under `-g3` (wave 2026-08-11, func_15196748)

**Two sources with byte-identical token streams, differing only in newlines, compile to
different `.text`.** This is not a curiosity — it is what closed `func_15196748` (505 → 0).

Proof, measured: take the function's source, join a `do { ... }` body's statements onto one
line, change nothing else. Token-normalised (`tr -s ' \t\n' ' '`) the two files are `cmp`-identical.
The objects are not:

```
- 11b8: 26310001 addiu s1,s1,1        <- separate lines
- 11bc: 00047400 sll   t6,a0,0x10
+ 11b8: 00047400 sll   t6,a0,0x10     <- one line
+ 11bc: 26310001 addiu s1,s1,1
```

asm-differ scored the two 180 and 120. At `-O2 -g3` IDO attributes instructions to source lines
and will not freely reorder across a line boundary; putting statements on the SAME line lets the
scheduler swap them. So:

> When a residual is a small number of **adjacent swapped instructions** inside one statement
> group, and no register is wrong, do not look for a semantic lever — **reflow the source**.
> One line per statement vs. several statements per line is a real, free knob.

`func_15196748`'s last three rows were exactly this: two loops each needed its body on one line
(each worth 60), and the `arr[i].unk1F = 255;` store needed to move one statement later. That
last one is an ordinary statement reorder, but note it only paid off *combined* with the reflow —
individually the reflows scored 120/120 and the reorder 120; together, 0.

**Corollary for the permuter:** its outputs are pycparser-regenerated, so they are reflowed
wholesale. An "improvement" whose diff looks like pure reformatting is therefore REAL, not noise
— check it with a token-normalised `cmp` and then score it, rather than dismissing it. Conversely,
when you hand-copy a permuter win into tidy house style you can lose it; re-score after tidying.

### Harness trap: `permuter_tu.sh selftest` check (b2) could fail for a TU that is fine
`selftest` used to pipe the round-trip compile into `head -5`. `compile.sh` runs `set -e`, so on a
TU that emits more than five `cfe:` warnings — game_18D770 emits ~50 — `head` closed the pipe, the
compiler took SIGPIPE, and compile.sh died *before writing the object*. The empty object
disassembled to the sha1 of the empty string, `da39a3ee...0709`, and (b2) reported "round trip
changes codegen". **game_18D770 was disqualified this way and is in fact a perfectly good permuter
target** (all five checks pass now; the round-trip sha1 equals the makefile sha1 exactly).
Fixed in `conker/permuter_tu.sh` by redirecting to a log. If you see the empty-string sha1
`da39a3ee5e6b4b0d3255bfef95601890afd80709` anywhere, it means *no object was produced* — it is
never evidence about the source. **The `game_83300` (b2) failure recorded above was diagnosed with
the buggy harness and should be re-tested before that TU is treated as unusable.**

### Two cheap sources of ground truth
- **A commented-out sibling constructor is gold.** `func_1516295C`'s `//` block in game_18D770.c
  handed over the exact field semantics of its payload struct for free. Grep the TU for
  `// s32 func_` before reverse-engineering field meanings by hand.
- **Float → u8/u16/u32 assignment** expands inline to the ~25-instruction `cfc1/ctc1 $31` +
  `0x4F000000` bias + `0x80000000` OR sequence with the `andi 0x78` exception test. Seeing it
  means the destination is UNSIGNED; a signed destination gets a bare `cvt.w.s`+`mfc1`. Four in a
  row is normal, not a red flag.

## Redundant-load forwarding, and reading the field itself (2026-08-11, func_1505A3A8: 1295 -> 20)

**IDO's store-then-reload is defeated by CACHING, not caused by it.** When golden shows
`swc1 X,off(r)` immediately followed by `lwc1 Y,off(r)` — storing a field and reloading the same
address — the source reads the FIELD on both sides:
```c
obj->f = obj->f - x;        /* swc1 then lwc1: IDO stores and RELOADS */
obj->f = cached - x;        /* IDO forwards the stored value; the reload VANISHES */
```
This is the normal idiom, not a quirk: **339 sites** across the matched corpus show that
`swc1`/`lwc1` pair, and reading one of them (game_10CD70.c:201) confirms the plain re-read form.
Corollary that finished the function: DELETING the cached local outright and reading the field in
every subsequent test was worth a further 210 points (230 -> 20). When golden reloads a field you
just stored, stop reaching for `volatile` or type-punning casts — write the field expression on
both sides.

## Which f32 parameter wins the callee-saved $f20: the SECOND-ASSIGNED one

For a function taking two f32 params in a2/a3, IDO homes them into `$f20` (paying `sdc1`/`ldc1`)
and `$f14`, and **the second-assigned of the two gets `$f20`**. Swapping the order of the two
statements that first write them swaps the registers and every downstream row (measured 1295 ->
1015 from that swap alone; reversing it costs +145 on the final base). Cheap first probe whenever
a float-heavy diff is a uniform `$f20`/`$f14` or callee-saved-FP permutation.

## Pointer cursor vs INDEX cursor — strength reduction, not constant folding (func_150428D4: -904)

A brief handed to an agent claimed golden's `or v1,zero,zero` + `addu s2,s3,v1` was IDO failing to
constant-fold a zero index, and that every honest `p = &str[i]` spelling folds it. **That framing
is wrong and it is what kept the function stuck.** The `addu` is the induction-variable
initialiser IDO's STRENGTH REDUCTION emits when the source walks an array with an INTEGER INDEX.
uopt runs constant propagation first and strength reduction after, so `i = 0` survives as a real
`move v1,zero` and the base pointer stays live into the preheader.
Rewriting the cursor from `u8 *p` to `s32 i` (`str[i]`, `i += 2`, `i++`) produced the `addu`
immediately along with `move s3,a0` / `addiu s2,s2,2` — **3857 -> 3278 in one edit**.
RULE: when golden has `addu <ptr>,<base>,<reg>` feeding a pointer that is then incremented by a
constant, and your C uses a pointer cursor, try an index cursor. It also explains golden's
register economy — the base dies right after the `addu`, so IDO recycles its callee-saved register
for the next variable, which is how golden used 7 callee-saved where the pointer form needs 9.
Second lever on the same function, worth 325: `while ((c = str[i]) != 0)` instead of
`c = str[i]; do { ... } while (c != 0);` is what makes IDO choose the branch-LIKELY guard and fill
its delay slot from the target block.

## MEASUREMENT TRAP: correct frame size, wrong stack offsets

One level below the known frame-growth trap. An extra local can keep the frame size EXACTLY
correct and still shift every stack-local offset: caching a global in a `u8 (*)[4]` local scored
108 BETTER (2845) but moved the callee's out-params from sp+0x64/0x60/0x5c to sp+0x60/0x5c/0x58,
with the frame still 0x80. `PERMUTER_TU_REQUIRE_FRAME` is blind to this because it only gates the
frame. A source whose stack offsets are wrong can never reach zero, so this is a plateau to
REFUSE, exactly like buying register wins by growing the frame. The harness wants an offset gate,
not just a frame gate.

## PERMUTER RE-SEED TRAP: pycparser re-splits joined lines

decomp-permuter regenerates candidates through pycparser, which reflows the source. So if a
line-reflow win got you from A to B, re-running `permuter_tu.sh setup` from the B source hands the
permuter the *pre-win* base again — the join is undone in the round trip. Use `chain` from the
output directory instead. That cost one wasted 900-iteration run.

## TU permuter status — corrected (2026-08-11)

* **game_83300 is USABLE.** Its recorded (b2) failure was entirely the `head -5`/SIGPIPE harness
  bug (commit ad4f136). With the fix all five checks pass and the round-trip disassembly sha1
  equals the makefile sha1 exactly (confirmed independently on two different functions in the TU).
  Strike the old entry. The unlock was immediately load-bearing: permuter output is what produced
  the insight that took func_1505A3A8 from 230 to 20.
* **game_1B1600 genuinely fails (b2)** — but NOT for the recorded reason. A real, non-empty object
  is produced; it differs from the makefile object by exactly two adjacent instruction swaps.
  Mechanism: pycparser reflows the TU's one-line `{ Gfx *_g = ...; w0=...; w1=...; }` gbi macro
  blocks onto seven lines, and the source-line scheduling law above then lets IDO swap
  `ori`/`addiu` and two `sw`s. This is our own line-placement finding firing against the harness.
  Hand-match only.
* **game_EB340 and game_6E770 both PASS** all five checks. For both, check (e) reports that
  isolated compilation DIFFERS from the in-TU build — the TU-aware harness is load-bearing there
  and a stock single-function permuter would have optimised the wrong bytes.

### selftest (d) has a latent FALSE-ALARM bug
The negative control looks for `0x44`, and failing that flips the first standalone `1` to `2`. On
a gbi-macro-dense TU the first standalone `1` is the `- 1` inside `((0x01 << (8)) - 1)`, turning a
`& 0xFF` into `& 0xFE` — a semantic NO-OP whenever the masked constant is even. Proved by direct
experiment on game_1B1600: perturbed and unperturbed objects are byte-identical (cf7e5711… both
ways) because `0xda` is even. So a (d) failure on such a TU is NOT evidence the harness fails to
measure the function. Fix: perturb a constant known to be live, or verify the perturbed object
actually differs before declaring failure.

## `u8 x = f();` is NOT `s32 x = f() & 0xFF;` — the mask can be REMATERIALISED (2026-08-11)

When golden masks the same source register **twice** —
`andi v1,v0,0xff ; li at,0x60 ; andi s3,v0,0xff ; bne v1,at,… ; [delay]` — that second `andi`
is not a scheduling accident and no amount of statement shuffling will produce it from
`s32 glyph = f(c) & 0xFF;`. That spelling makes ONE masked value and copies it (`move s3,v1`).
Declaring the variable **`u8`** and dropping the explicit mask (`u8 glyph = f(c);`) makes the
mask *be* the assignment, so when the variable also needs a callee-saved home across a later
call IDO **rematerialises the `andi`** instead of emitting a copy — golden's exact instruction.

Found by corpus mining, not by guessing: across 841 objects there are 66 sites with two
`andi rX,rY,0xff` off one source register, and only two send the second to a callee-saved
register. One of them, `game_131F30.c func_151050B0` @0x940, is the pattern exactly
(`andi v1,v0,0xff` … `andi s1,v0,0xff`), and its C is a **u8 variable assigned an int
expression and then live across a `jal`**.

> Whenever the diff shows `move sN,vM` where golden has `andi sN,v0,0xff` (or any other cheap
> recomputation), the variable's declared type is the lever — narrow the type, delete the
> explicit mask.

### Corollary: a DISPLACED instruction scores worse than a MISSING one
Adopting `u8 glyph` in func_150428D4 took the score **2953 → 3003** while making the object
strictly closer: the s32 form has no `andi s3,v0,0xff` at all, the u8 form has it and merely
sits in the `bne` delay slot instead of before the branch. asm-differ charged 50 points for the
displacement and gave the missing instruction a free pass. Count `ins`/`del`/`chg`/register-only
rows separately (they went 8/8/5/93 → 8/8/6/92) and check whether the golden instruction
*exists* in your output before believing a regression.

## Grep the tree for a symbol's REAL type before inventing one

`func_150428D4` carried a hand-invented `extern u8 (*D_80085994)[4];` with `[glyph][0..3]`
subscripts. The real declaration was already sitting in an **already-matched** TU
(`src/game_42DC0.c`): `typedef struct { u8 width; u8 height; u8 unk2; u8 unk3; } Glyph15015A38;`
and `extern Glyph15015A38 *D_80085994[];` — an array of pointers, one table per font. Adopting
it is byte-identical (score-neutral both ways) and it *names the arithmetic*: the near-miss's
mystery expression is `advance = width + unk2 - 1`, `lineheight = height + unk3`.
Cost: one `grep -rn D_xxxxxxxx src/ include/`. Do it before writing any access expression.

### NEGATIVE, measured: a global's ADDRESS hoist is not reachable from the access spelling
IDO LICM-hoisting `lui %hi(sym); addiu %lo(sym)` into a loop preheader (eating a callee-saved
register) where golden rematerialises `lui %hi; lw %lo(sym)` per use is a **cost-model** decision.
Six independent spellings of the same accesses — 2-D pointer-to-array subscript, flat `(u8*)`
cast with `[i*4+k]`, struct-pointer cast, the real array-of-pointers `D[0][i].field`,
`(*D)[i].field`, and `(D[0]+i)->field` — produced byte-identical output every time. Corpus:
879 sites rematerialise a global pointer and 180 hoist its address into a callee-saved register,
so **both behaviours are normal matched-C output**. Do not spend builds on the spelling; and
note you cannot buy it back by caching the pointer in a local either — any new local shifts
every stack-local offset (see the MEASUREMENT TRAP section).

## Merging two locals that golden shares a register for usually BACKFIRES

Tempting inference: golden puts `old` and `cb` in the same `$v1`, therefore they are one
variable in the source. Measured on `func_15162B28`: merging them does give the merged variable
a single register for both roles (which the two-local form never does), but the combined web is
now **long-lived**, so IDO hands it an `$a`-register and `$v1` — which the short-lived `cb` web
had correctly — goes unused. Score 10 → 55/80 across eight merge spellings.

> `$v1` (after `$v0`) goes to the SHORTEST-lived web; long-lived webs get `$a`/`$s` registers.
> If golden colours a long-lived value `$v1` and recycles it, that is graph-colouring *reuse*,
> not evidence of one variable — and merging the variables destroys the short web that earned
> the register.

### Corpus-level BAIL evidence — the strongest form there is
func_150585F0 sits at 10 on two rows: a computed a3-bound float that golden stages in `$f14` while
IDO puts it in `$f0`. Six independent spellings score EXACTLY 10, seven more are worse, and 3046
frame-gated permuter iterations produced no output at all. Then the decisive check: across
**630,452 lines of disassembly from 611 built objects, ZERO live-C functions stage a COMPUTED
a3-bound float in `$f14`** (all 7 live-C `$f14`->a3 sites are incoming-parameter forwarding), while
golden does it at 3 sites. That upgrades the claim from "we haven't found the spelling" to "no
matched C in this tree has ever produced this pattern". When a residual is a single unusual
register binding, grep the corpus for it before spending another run.

## PERMUTER OUTPUT CAN BE SEMANTICALLY WRONG, NOT MERELY FAKE (2026-08-11, func_15060778)

The most important safety finding to date about the permuter workflow. `weight_overrides` zeroes
the passes that emit banned CONSTRUCTS — it does **not** stop the randomizer's variable-reuse and
statement-motion passes from breaking SEMANTICS. Across ~1,420 gated iterations on one function,
every output that beat its base was unusable, and **three of four were semantically incorrect**,
not merely stylistically banned:

* `id = arg2;` reuses a still-LIVE variable, silently changing a callee's third argument.
* `(new_var = arg2)` assigned only on a path that always returns, then READ in the tail —
  uninitialised.
* `flags = 0;` moved out of an `if` branch into the `else` (where it is immediately overwritten),
  leaving `flags` uninitialised on the original path.
* `u8 *new_var = &arg->unk13F;` for a SINGLE use — a pure register forcer (the merely-banned one).

**Read every permuter output for CORRECTNESS, not just for banned tokens. Scoring better is not
evidence of equivalence.** A scan for `new_var`/`dummy_label` would have passed three of these.

### Keep the honest half — it can beat the permuter's own packaged result
Output-1955 shipped a real lever wrapped in a banned pointer split; the lever alone scored **1948**
against the packaged output's **1960**. Same pattern took another function from 230 to 20. When an
output mixes one honest change with one forcer, extract and generalise the honest half.

## Gates gate the ANSWER, not the search

`PERMUTER_TU_REQUIRE_FRAME` / `REQUIRE_OFFSETS` are only usable when the base already satisfies
them. Where the frame or the offsets ARE the residual, an exact gate rejects the base and the
permuter cannot start at all: on func_15060778 the golden 0x58 frame happens exactly when the last
blocker is solved, so gating on 88 was unusable. Use `PERMUTER_TU_MAX_FRAME=<base frame>` there —
which is what `frame` already recommends — to forbid buying wins by growing the frame without
demanding the answer up front.

## Break a conversion CSE by re-spelling ONE call site

When a value is passed as argument 0 to several calls and IDO promotes it to a callee-saved
register where golden spills it, the cause is IDO pooling all the conversions into one long-lived
web. Give ONE call site a different-typed spelling of the same conversion — here `0xFFFF & id`
instead of `(u16)id`, at the single callee whose parameter is `s32` where the others take `u16`.
Golden's `sw a0,0x44(sp)` / `lw a0,0x44(sp)` spill pair appeared for the first time and only `$s0`
was saved, exactly as golden does: **2878 -> 2103** on one token.
Related trap re-measured: declaring the variable `u16` is NOT the shortcut it looks like — 6366
with 97 register-only rows, because IDO re-emits the narrowing `andi` at every call site even for
an already-`u16` variable, and the extra instruction rotates the whole t-register pool.

## Corpus bail #2 — the narrowed-value-spilled-across-a-call pattern

func_15060778's residual is golden holding a narrowed value in an argument register across a call
and spilling it to a compiler-temp slot rather than promoting it to callee-saved. Across 569,790
lines from 611 objects / **5,479 live-C functions, only 42 spill an argument register to a temp
slot across a call at all, and in ZERO of them was the spilled value produced by a narrowing
mask** — golden does it twice in this one function. Same class as the computed-`$f14` finding:
"no matched C in this tree has ever produced this", not "we haven't found the spelling".
Instructive near-miss kept: a separate `u16 sid` carrier per switch arm scores 2652 and gets the
allocation almost exactly right (3 register-only rows, `flags` lands in golden's `$t0`) but fails
because IDO MEMORY-HOMES a `u16` local (`sh`/`lhu`) where golden spills a 32-bit compiler temp
(`sw`/`lw`).

## Is your score bounded? CHECK THE SYMBOL SIZE — do not assume either way

Two agents independently concluded that asm-differ "cannot bound a GLOBAL_ASM-sourced golden
symbol because asm-processor emits no `.size`", and therefore that their scores were inflated by
downstream shift. **Both were wrong about their own functions**, and the mistake cut in the
dangerous direction: it invites you to dismiss a real score as noise and substitute a hand-rolled
comparator.

Measured across every expected object:

    FUNC symbols total: 10185   with size=0: 4773

So it is neither "always broken" nor "always fine" — **47% of FUNC symbols carry no size, and the
rest do.** A GLOBAL_ASM stub is *not* automatically one of the unsized ones: all four wave-16
targets are stubbed and all four carry an exactly-correct size (944, 1068, 992, 992).

One command decides it, per function:
```sh
mips-linux-gnu-readelf -sW expected/build/src/<tu>.c.o | awk '$8=="<func>"{print $3}'
```
* nonzero, and equal to the byte count you expect → asm-differ bounds the function; the score is a
  real per-function number, even if your body length differs from golden.
* `0` → unbounded: diff.py runs to the end of `.text`, so a length difference contaminates the
  score with every following function. Only then is an objdump isolator warranted.

Corollary: when a length-differing candidate's score looks absurdly large, check the size before
theorising. And if you do write an isolator, keep asm-differ as a cross-check rather than
replacing it — a private comparator that disagrees with the tool everyone else uses is a fine way
to generate numbers nobody can reproduce.

### The stop-at-return scoring modes have a separate, real failure
`-s` / `-ss` / `-sss` stop at a `jr ra`. When golden has three `jr ra` and the candidate two (a
missing duplicated epilogue), a stop-at-return score compares unequal spans and can read FALSE
ZERO. That trap is genuine and is independent of the `.size` question — do not use the `-s` family
to certify a function whose return count differs from golden.

## Concurrent agents can overwrite each other's MEASUREMENT scripts

An agent reported its scratchpad `score.sh` being silently replaced between tool calls — twice,
once with an objdump comparator it never wrote — while a second agent ran concurrently. The likely
cause is a scratchpad path collision, not anything exotic, but the consequence is the same and it
is severe: **an agent whose measurement script is swapped underneath it reports fabricated
scores.**
Mitigations, both cheap, now standard in the wave brief:
1. Namespace scratchpad files under a per-agent directory with a unique token, never a bare name
   like `score.sh`.
2. Print the script's `sha1sum` and full body in the SAME shell invocation that executes it, so
   every number is produced by code that was visible at the moment it ran.

## Statement ORDER of independent loads is a register lever — a different axis from spelling

The single most useful correction this week. Two parked NOTES files concluded "no source handle
left; loop-invariant ranking tie" after trying many respellings — but **neither had reordered
independent statements**. Respelling a statement and moving a statement are different axes, and
only the first had been searched.

On func_1512B730, hoisting one integer load above two float loads was worth **190 points**
(355 -> 165) and cut wrong-register rows from 51 to 13. An exhaustive sweep of all **720**
orderings of the six opening loads gives the law in closed form: the only thing that matters is
that k0's load issues FIRST; all 10 orderings with k0 first score 160 and nothing scores lower.

RULE: when the residual is "the register webs are swapped and no spelling moves them", sweep the
ORDER of the independent loads before declaring a tie. It is a small, finite, cheap search.

## Line joins pay at the ADJACENT-PAIR granularity, not the block

IDO attaches a line number to every instruction and its list scheduler groups by them, so joining
two adjacent statements onto ONE line merges two scheduling groups. Worth 10 points each, twice,
on func_150B06B0 (580 -> 560). Why it stayed hidden through two prior waves is the instructive
part:

* one wave tested joining the WHOLE tail block — much worse (34 -> 51 rows)
* the next tested SPLITTING every statement — all 24 variants exactly inert

Both are the wrong granularity. Run a greedy climb over single adjacent PAIRS (join every
remaining pair, keep the best, repeat). ~20 builds. It is not universal — the same climb on
func_1512B730 left all 25 candidates byte-identical — but it is cheap enough to always try.

## Reading a permuter run by its log tail will mislead you

The 350 -> 160 find on func_1512B730 scrolled past about 1,000 iterations before the run ended;
the tail showed only "score = 350" and looked like a flat plateau. **The win was already on disk.**
Always list the output-* directories rather than trusting the tail.

Related, and it cost a result: permuter_tu.sh chain does an rm -rf of output-*. Copy any output
you care about BEFORE chaining.

And the permuter **cannot inherit a line join** — it regenerates C from a pycparser AST which
re-splits joined lines, so it can rediscover a join but never carry one through setup or chain.
Re-apply joins by hand afterwards; a greedy hand climb finds them far more cheaply than the
randomizer does.

## A one-instruction-short candidate makes its whole TU look regressed

A per-symbol whole-TU check flagged six functions as regressed. Five were pure address shift — the
candidate was 4 bytes short, so everything after it moved and the objdump TEXT differed while the
instruction stream was byte-identical. The sixth was the last function in the TU and differed only
in trailing 16-byte alignment padding (two pad nops vs one; .text 8448 bytes either way). Both
effects are the same shortfall and both vanish when the function matches.

Compare instruction streams with ADDRESSES STRIPPED, or build with the pragma in place as the
control, before believing a candidate broke its siblings.

## Do not park the lowest score if it was bought with implausible source

Two scores below the parked one were deliberately refused this wave: a 558 and a 574/575 family on
func_150B06B0 that got there by writing struct fields OUT OF NUMERIC ORDER to buy one-point
stack-offset alignment noise, while leaving all nine 60-point reordering penalties intact. Parked
instead was the 560 form — two line joins and a chained assignment, none of which changes a token
and all of which a human plausibly writes.

Score 0 is necessary, not sufficient; a lower score bought with implausible source is not progress
toward the real blocker, it is camouflage over it.

### func_150B06B0 — a publishable BAIL (2026-08-11)
Identical 236-instruction multiset with golden; every opcode, register, immediate and stack offset
correct. Pure list-scheduler priority tie on destination-vs-source address materialisation in a
struct copy. Exhausted: ~9,000 permuter iterations under exact frame (320) and stack-offset (103
displacements) gates; all 23 adjacent transpositions; all 120 pairwise swaps; the complete 462-move
relocation neighbourhood; a 570-variant move+swap re-run; all 22 pairwise line joins; all 24 line
splits (inert); 23 rotations of the copy (1480-4881, so the copy must be first). **Ten** copy
spellings are byte-identical. The one construct that would evaluate the destination in its own
right — a memcpy/bcopy CALL, idiomatic since the same TU calls memcpy — is dead: IDO emits a real
call (2000). Field-by-field is 3750 because golden's copy goes through $at, the assembler's
struct-assignment expansion, which field assignments cannot produce.

Revisit only with a new idea about operand ordering, not with more search.

## IDO allocates registers by WEB REFERENCE COUNT — a predictive law, and a bail criterion

The mechanism behind a whole family of "two registers are swapped and nothing moves them"
residuals. IDO ranks webs by reference count and hands out $v0, $v1, $a1, $a2 in that order.
Worked example (func_15162B28, settled at 10):

    p    many refs           -> $v0
    cb   5 defs + 2 uses = 7 -> $v1
    cur  5                   -> $a1
    old  1 def + 1 use  = 2  -> $a2      golden wants this one in $v1

`old` is the LEAST-referenced web in the function, so it can never outrank `cb` for $v1 in any
source that still emits golden's five `lb` sites and its single guard. That is not "we haven't
found the spelling" — it is arithmetic.

USE IT BOTH WAYS. Before hunting a register swap, count each web's defs+uses and check whether the
ranking you need is even reachable. If the register you want is held by a web with strictly more
references than yours, the only lever is changing the REFERENCE COUNTS (adding or removing uses),
not the spelling — and if golden's instruction count is already exact, you cannot change them.
This also explains why MERGING two locals backfires (measured 10 -> 55/80/293/1248): merging makes
one long-lived web out of two, and long-lived webs lose $v1 to short ones.

## The line-join lever is PER-FUNCTION, and "always-valid" means enumerate, don't climb

Joining two adjacent statements onto one line is always valid C in a body with no `//` comments
and no preprocessor lines — so the single-join neighbourhood is small and completely enumerable.
Do that instead of a greedy climb. Two exhaustive sweeps:

    func_1505A3A8   all 64 adjacent pairs joined, one at a time -> ALL exactly 20
    func_15162B28   all 51 adjacent pairs joined, one at a time -> ALL exactly 10

Dead flat. A greedy climb has no first step to take, because every first step is a plateau. This
does not refute the lever (it was worth 10 points twice on func_150B06B0) — it establishes that
line-number grouping is a per-function property. Enumerating costs ~50 builds and settles it.

## Distinguish a REGISTER tie from a SCHEDULER tie before theorising about either

func_1505A3A8's parked diagnosis claimed "mutually exclusive requirements": golden needs one
parameter scaled second to win the callee-saved $f20, yet emits its multiply first. That was
WRONG, and the correction matters more than the function.

**The register map is already golden's** — `mtc1 a2,$f20` / `mtc1 a3,$f14` are byte-identical. So
there is no allocation conflict at all; it is a single list-scheduler tie-break over two
independent multiplies. Measured invariant across 16/16 instrumented spellings: **the `mul.s`
writing $f14 is always emitted before the one writing $f20**, including in every form that gives
both multiplies the SAME `-g3` line number (same-line and comma forms).

Diagnostic that settles it in one look: asm-differ prints the `-g3` source line in the CURRENT
column. If your two rows carry DIFFERENT registers, it is allocation; if they carry the same
registers in a different ORDER, it is scheduling. Reordering the source flips the whole map on an
allocation problem and changes nothing on a scheduling one — on this function, swapping the two
scale statements flipped $f20/$f14 across the map while leaving the emission order identical.

### Two more per-function laws found by exhaustive sweep
* func_1505A3A8: of the 3! = 6 orderings of its independent opening statements, the parked order
  is the UNIQUE best (20); the others are 165, 480, 625, 1735, 1735. The order axis is live here
  but already optimal.
* func_15162B28: in every branch, `p->unk24 = N;` must come LAST (moving it costs 225–2320). The
  opening seed block is the only genuinely flat site, a real 3-way tie at 10.
* `register` is inert on both functions across 14 combined spellings — and it is in-corpus, since
  game_18D770 already contains a `register` declaration in a matched function. Stop reaching for it.

## A struct passed by pointer is bounded by what its CONSUMER copies, not by what you see written

The technique that turned a suspected forcer into a checked fact, and it is reusable whenever a
stack struct's tail extent is in doubt (which is whenever the frame needs N more bytes than your
fields account for).

Do NOT reason "the extent is unknown, so padding is fair". Follow the pointer:

1. Find every callee the struct pointer is passed to.
2. Walk through THIN FORWARDERS — they prove nothing. Here `func_151303BC` just calls
   `func_15130374`, which just calls `func_15130280`, none of them dereferencing the pointer.
3. Read the real consumer. `func_15130280` is live matched C and does
   `memcpy((s32)temp_v0 + 0x10, arg0, 0x70);` — it copies **0x70 bytes** out of the struct.

That single line bounds the type from below: the struct provably extends to at least 0x70,
regardless of how few fields the caller writes. A tail declaration is then a FACT, not padding.

The inverse case is the one to be suspicious of: if the consumer never touches past your last
modelled field, extra tail bytes have no support and the frame's missing bytes belong to some
other local.

### Corollary: model-vs-frame disagreement can be an ORIGINAL-GAME OVERREAD
Here the consumer copies 0x70 while the verified frame proves the local is 0x6C — so the original
game reads 4 bytes past its own params local every call. That is original-game behaviour and must
NOT be "fixed": declaring the struct 0x70 changes the frame and breaks the match. Record it and
move on.

### An unverified model in the tree is not evidence — check whether its user is still stubbed
`src/game_117490.c` models this same callee's parameter struct as `struct_EA11C_params`, ending at
0x63 with no tail — **12 bytes short** of what the consumer demonstrably reads. It looks
authoritative and is not: its only user, `func_150EA5CC`, is still a `#pragma GLOBAL_ASM` stub, so
nothing about that struct has ever been byte-verified.
Before citing an in-tree type as precedent, check that the function using it is LIVE C, not a
stub. A matched function's types are evidence; a stubbed function's types are a guess someone
wrote down. (This cuts both ways — it is also why "grep the tree for the real type" must be
followed by "and check it compiles into a matched object".)

# ==================================================================================
# IDO STACK-FRAME LAYOUT — SOLVED (2026-08-12). Read this before any cold decompile.
# ==================================================================================

Calibrated on an already-matched function, then confirmed by 13 predictive probes on a second.
This supersedes the earlier, partly-wrong stack-home notes further up this file (see the
CORRECTION below).

    EVERY DECLARED AUTO GETS A STACK HOME, whether or not it ends up living in a register.
    The home area is EXACTLY sum(sizeof(local)) bytes, it ENDS AT framesize, and locals are
    laid out TOP-DOWN in DECLARATION ORDER (first-declared = highest address).
    Below the home area sits the compiler-TEMP area; below that, the saved registers.

        framesize = (arg-build + saved regs) + temp_area + sum(sizeof(local))

Calibration, matched sibling func_151B6320: frame 144, locals occupy 64..143, and the declaration
list (top_dummy / header / pad_dummy / payload / temp_v0) sums to exactly 80 bytes. Observed
offsets place payload at 68..111, header at 116..139, top_dummy at 140, pad_dummy at 112,
temp_v0 at 64 — exactly declaration order, top-down, ZERO SLACK.

## Three consequences that matter far beyond one function

**1. `sw t1,X(sp)` / `sw a2,X+4(sp)` pairs around a call are usually NOT spill slots.**
They are the HOMES of the first two declared locals. Reading them as spills is precisely what made
an earlier revision of one near-miss model the frame as three separate regions and conclude —
wrongly — that declaration order could never buy the missing bytes.

**2. A golden `.s` with "dead holes" in its frame is telling you the ORIGINAL DECLARATION LIST,
exactly.** You can read the original author's declaration order and each local's byte size straight
off the offsets. For func_151B65D4 the frame decodes to:

    180 payload | 176 trail | 172 [1 word] | 160 delta | 144 [4 words] | 132 pos | 88..131 [11 words]
    = 96 bytes of declared locals

That is a *reading*, not a search. **Do this FIRST on every cold target** — it converts "guess the
locals and iterate" into "decode the locals, then write them down."

**3. It explains the `top_dummy` / `pad_dummy` locals in already-matched functions.** They are
frame-shaping declarations standing in for locals nobody has named yet. Which is exactly why they
must be treated as an OPEN QUESTION, not a finished match — see the discipline note below.

## The third-slot law (how to tell a home from a temp)

Sweeping a local to every position in the declaration list (8 orderings) showed the third slot is
*always* exactly that local's declared home, while the other two slots always take compiler temps:

    position in list:  1st  2nd  6th  7th  9th  10th 11th
    resulting home:     88  128  108  104   96    92  124

Exact match every time. So if a slot moves when you reorder declarations, it is a HOME; if it
stays put, it is a compiler TEMP and no declaration change will move it.

## CORRECTION to the earlier stack-home entries in this file

Two earlier notes are now known to be imprecise and should be read through this section:
* "stack homes are per USED local" — **wrong**. Every *declared* auto gets a home, used or not.
  The earlier probe concluded otherwise because unreferenced locals were being appended after the
  used ones, which looks like "used first" but is really just declaration order with the dummies
  declared last.
* "first-declared = highest address" for aggregates — **right, and it generalises to all locals**,
  not just aggregates.
The negative result recorded earlier (a frame that did NOT respond to adding or removing declared
locals) is still true and is not a contradiction: that function's missing bytes were in the
compiler-TEMP area, which the declaration list cannot reach. The two areas are separate, and the
first job is deciding which one your missing bytes are in.

## DISCIPLINE: an unnamed frame-shaping local is an OPEN QUESTION, not a match

When the frame proves N bytes of declared locals and every value you can name accounts for fewer,
the shortfall is real and it means the original had locals you have not identified. Declaring
`unknown0` / `unknown1` to reach the right frame is a legitimate *working state* — and it is NOT
shippable. It is the banned dead-local forcer wearing better names.
The parked func_151B65D4 does exactly this and is marked **MUST NOT BE COMMITTED AS A MATCH** until
those two 4-byte locals are either named or the score reaches 0 without them. Keep that discipline:
a byte-perfect score obtained with `unknownN` locals is a fake match, because the claim it encodes
("there are two more locals here") is unevidenced even when the bytes agree.
Route to resolving it: follow-the-pointer (does a consumer copy more out of an aggregate than you
have modelled?) before inventing a scalar.

## Home vs temp is ROLE-based, not declaration-order-based (refines the frame law)

The frame law says every declared auto gets a home in declaration order. This wave pinned down
which *values* end up in homes versus compiler temps, and it is not what declaration order alone
would predict.

Measured across 8 declaration orders on func_151B65D4: `stepAngle` ALWAYS takes its own declared
home, wherever that home happens to be (move it to 128 and the slot moves to 128). `count` and
`stepRadius` ALWAYS take compiler temps, no matter where they are declared. Golden wants `count`
in the home at 88 and the other two in temps at 80/72 — and **declaring `count` last does not do
it** (1406).

So IDO's home-vs-temp choice is driven by the value's ROLE (how and where it is used), not by
where you declare it. Declaration order controls WHERE a home sits; it does not control WHICH
values get one. When your residual is "the right slots exist but the wrong values are in them",
the declaration list is not the lever.

## A no-op edit that changes codegen is a RED FLAG, not a lever — even when it is uniform

func_151CA6A0 went 477 -> 172 on `spA0.unk14 |= 0x0;`, a statement that emits **no instruction**
and yet re-aligned the whole register allocation. That is a banned no-op mask by the letter of the
fake-match policy.

The defence offered was structural and is worth recording because it is the strongest form this
argument takes: the function pokes an alignment field in four blocks as `(x & ~6) | k` for
k = 6, 4, 0, 2, and three of those four are independently forced by the binary — so the k=0 member
"should" be spelled uniformly with its siblings. That is a real argument. It is still **not proof**,
because `| 0` is exactly the term a forcer would take, and the uniform-family claim is inferred
from three siblings rather than demonstrated for the fourth.

Handling: the function is PARKED at 172, the reliance is written into its NOTES, and nothing ships
until either an honest spelling of the k=0 case reproduces the codegen or the function reaches 0
without it. **Do not let "it is uniform with its siblings" become a licence to ship a no-op.** If
the uniform family is real, the k=0 block should be expressible as the same `(x & ~6) | k` shape
its siblings use — that is the thing to try, not `|= 0x0`.

## A private parallel-safe scorer (and why it must be cross-checked, not substituted)

Useful pattern when a wave needs hundreds of builds: a project dir that SYMLINKS
`conker/{include,asm,expected,diff_settings.py,src/libultra/*}` but owns its own `src/` and
`build/`, compiles with the repo's exact pipeline (`asm_processor.py -O2 -g3` | `ido cc -c -32
<CFLAGS> -O2 -g3 -mips2 -o32` | `asm_processor --post-process`), and runs the REAL asm-differ with
`-o <func> -R --max-lines 4096 -f build/src/<tu>.c.o`. It never touches `conker/build`, so it needs
no buildlock and several can run in parallel — this wave ran a 6-way sweep and 400 permutations
that way.

The discipline that makes it safe, and it is not optional: **calibrate against the real repo build
before trusting a single number, and cross-check every result that matters back through
`make` + buildlock.** This wave did both — controls with the pragma IN scored 0/0 on both TUs, the
parked baselines reproduced exactly (1398 and 517), and the final 172 was re-measured under the
repo's own `make`. A private scorer that is never reconciled with the shared tool is how a pipeline
starts producing numbers nobody else can reproduce; that failure mode has already been seen here
once.

## THE N-NO-OPS TEST: how to tell an evidenced construct from a forcer

The cleanest fake-match test found so far, and it settled a question that had blocked a function
for two waves.

A function reached 172 (from 517) on `spA0.unk14 |= 0x0;` — a statement emitting no instruction
that nonetheless re-aligned the whole register allocation. The structural defence was that the
function pokes an alignment field in four blocks as `(x & ~6) | k` for k = 6, 4, 0, 2, so the k=0
member "should" be spelled uniformly with its siblings.

**Both halves of that were refuted by measurement:**

1. The uniform shape `(x & ~6) | 0` scores **517 — byte-identical to simply dropping the term.**
   IDO folds `| 0` *inside an expression*; it consumes no register web. So the uniform spelling
   does not produce the codegen, and the "uniformity" argument buys nothing.
2. The 172 is reachable ONLY from a STANDALONE no-op statement — and **four different ones reach it
   equally**: `|= 0x0`, `+= 0`, `|= (0 << 1)`, `|= (x & 0x0)`.

That second point is the general test. **If N mutually-exclusive no-ops all produce the identical
score, the binary is evidencing "one extra folded temp web exists here" — not any particular source
construct.** No spelling among them is preferred by the evidence, so none of them is evidenced at
all. Ship none.

Making the four blocks genuinely uniform was measured too, and is strictly worse: 587 and 1413,
with two variants LOSING two instructions (265 vs golden's 267). The family argument was wrong in
both directions.

### Corollary: a gain contingent on a forcer is not a separate gain
The same function had a second edit recorded as "clean and valuable independently" — splitting
`= (x & ~6) | 2` into `&= ~6; |= 2;`. Measured without the forcer present, it is worth **zero**
(517 either way). Its 345 points existed only in the presence of the banned statement.
**When you remove a forcer, re-measure everything you attributed to other edits.** Contingent gains
evaporate, and a parked log that records them as independent will mislead the next wave.

## A written-to register parameter is homed in the CALLER's arg slot

Corrects a wrong claim in a parked log, measured twice. Reassigning a parameter (`arg2 = ...`)
instead of declaring a local for the same value is NOT "byte-identical with identical frame" — it
sheds exactly 4 bytes of frame (0x110 -> 0x108) and 326 points. A register parameter that is
written to is homed in the caller's argument slot (golden's `sw a3,276(sp)`), not in the callee's
local area, so it costs no local-area bytes.
Use it deliberately: when your frame is 4 bytes over and you have a scalar that shadows a
parameter, assigning through the parameter is the honest way to lose those bytes.

## Refuse a better score that breaks golden's store sequence

Recorded because the refusal was correct and the temptation was real: moving one field assignment
scored 1312 against a parked 1345 — 33 points better — but changed the emitted byte-store order
from golden's `1e 20 61` to `1e 61 20`. A score bought by making the emitted sequence demonstrably
LESS like golden is not progress. Dump the store order and diff it against golden before accepting
any reordering win.

## Environment: /tmp is wiped between tool invocations

In this WSL setup the distro shuts down between invocations and systemd clears `/tmp`, so a scorer
or snapshot written there vanishes before the next call. Keep working state under `$HOME` (or the
scratchpad) — within a single invocation `/tmp` is fine, across invocations it is not.

## When a SHARED HEADER is wrong: shadow it file-locally, never edit it

`include/functions.h` declares `func_150ADA20` as returning `u8`. Golden feeds its result straight
into `divu` with NO zero-extension, which a u8-returning declaration cannot produce — so the real
return type is a word and the header is simply wrong.

**Do not fix the header.** That symbol is referenced by **106 TUs**, including already-matched ones
under `src/game/done/`, and this was tested rather than assumed: correcting it to `s32` and
rebuilding every referencing TU causes **BUILD FAILURES in 13 of them**. A shared-header retype is
one of the few edits that can silently invalidate committed, byte-verified work.

The file-local fix, which is now the project idiom for a wrong prototype:
```c
/* functions.h declares this as u8; golden's divu with no zero-extension proves it is a word. */
#define func_150ADA20 func_150ADA20_u8_decl_in_functions_h
#include "functions.h"
#undef func_150ADA20
s32 func_150ADA20(void);
```
This renames the header's declaration out of the way across the include, then supplies the correct
one. Measured on func_150DFEFC: u8 header prototype **946**, file-local s32 prototype **110**, and
removing it after the match sends the score **0 -> 836**. Confirm the TU has no OTHER caller of the
symbol (this one had none), so the override cannot affect anything else in the file.
Always record the binary evidence for the retype in a comment above it — the justification is the
thing that makes this honest rather than a convenient hack.

## `addu` operand order: `<variable> + <temp>` canonicalises the TEMP first

Sharpens the earlier index-order entries. For `variable + temp`, IDO puts the TEMP first **no
matter how the source is written** — `mtx + (p->bone << 6)` and `(p->bone << 6) + mtx` BOTH emit
`addu a2,t7,v0`. For `temp + temp`, it keeps source order.
So when golden has `addu a2,v0,t7` (base first) and you cannot get it by swapping the operands,
**make the variable into a temp**: an explicit cast node does it. `(s32)mtx` with `mtx` declared
`u8 *` restored golden's order and was worth 10 points on func_1508114C (70 -> 60).

## An address-taken local is an ALIAS BARRIER the scheduler will not cross

If a local's address is passed to a callee, IDO must assume stores to it may alias, so it will not
hoist a load above those stores. On func_1508114C, golden's `lw v0,0x1d4(s2)` sits at the top of
the loop body, 20 instructions before its use — reachable only if the source reads the field into a
local BEFORE the `local.unkN` stores that precede the call. Left inline, the load is pinned next to
the `jal`, the `mtc1`->`cvt.s.w` delay becomes unfillable, and IDO emits a `nop` — and that single
nop was the entire 1068-vs-1064 size difference. Worth **890 points** (960 -> 70).
Generalisation: when golden loads something suspiciously early and you cannot move it, look for an
address-taken local between your load and golden's position, and hoist the read above the stores.

## IDO chooses a BASIC BLOCK for a spilled reload — a third residual class

Beyond allocation ties and intra-block scheduling there is a third kind: which block a spilled
variable's reload lands in. func_1508114C's final residual is exactly one instruction, and golden
puts the reload of a pointer in the compiler-generated LOOP PREHEADER (the block after the count
guard, beside the hoisted `addiu fp,sp,0x84`), while the candidate emits it as a plain statement
before the guard.
The only source-level control found is the LOOP SHAPE: `if (count > 0) { p = spheres; do {...}
while (i != count); }` fixes the placement exactly — but re-ranks three saved registers (a 3-cycle
rotation costing 20 rows, 60 -> 105). So the two requirements trade against each other, which is
the signature of a genuine tie rather than a missing spelling. The permuter found nothing better
across ~500 gated iterations.

## Check permuter output directories for UNSCORED wins before deleting

The last instruction of one match came from a permuter output left behind by a wave that was killed
mid-run: `permuter_tu/<func>/output-0-1/` with `score.txt` reading **0**, never applied. Nobody had
looked. Before deleting or re-running a permuter directory, list its `output-*` and read each
`score.txt` — and note `chain` does `rm -rf output-*`, so copy first.
(These directories are now gitignored: 1.6M of regenerable state that was one `git add .` away from
the repo.)

## Which SIDE OF A GUARD a statement is written on picks the basic block for a spilled reload

The control for the third residual class (a reload landing in the wrong basic block), and it
closed a function that was one instruction from done.

Golden put the reload of a pointer in the compiler-generated LOOP PREHEADER — the block after the
count guard, beside the hoisted `addiu fp,sp,0x84`. The candidate emitted it as a plain statement
before the guard. The loop shape that fixes placement was known to re-rank three saved registers,
costing 20 rows, so placement and ranking appeared to trade against each other.

They do not. **Split the two initialisations across the guard:**

    i = 0 BEFORE the guard, p = spheres INSIDE it   ->  0   <-- unique
    i and p BOTH inside the if                      ->  65
    i and p BOTH before the if                      ->  60  (the plain `for` shape)
    p before the if, i inside                       ->  60

Only one of four arrangements lands on zero. The mechanism: `i` must be live across the guard so
its home is fixed before the preheader exists, while `p`'s reload has to be *generated inside* the
preheader — and **the preheader only exists for statements written between the guard and the
loop.** So when golden has an instruction in a preheader you cannot reach, do not reshape the whole
loop; move that one statement to the other side of the guard and leave the rest where it is.
The continuation edge is load-bearing here too: rewriting the bone-mask test as a goto-free
positive nest scores 95.

## THE PERMUTER'S SCORE IS NOT asm-differ's SCORE

A measurement trap that would have shipped three regressions. A permuter run on a parked base
produced three `output-*` dirs whose internal scores looked like improvements; re-scored on the
real asm-differ they were all WORSE:

    permuter 1140  ->  asm-differ 1482
    permuter 1326  ->  asm-differ 1428
    permuter 1437  ->  a whitespace-only reformat of the base

**Never accept a permuter output on its own number.** Re-score every candidate with
`diff.py -o <func> -R --max-lines 4096` before believing it beat anything, and diff the output
against the base first — a "win" that is pure reformatting is the permuter round-tripping your
source, not improving it.

## Reading golden's `$at` chain to prove a preheader ordering is unreachable

Technique worth reusing when the residual is a reordering inside one block. Every `lui` that
materialises a constant or a `%hi` writes `$at`, so the `lui`s are **totally ordered** and the
chain can be read straight off both listings:

    GOLDEN  1.0f, %hi(A18), 10.0f, 199.0f, 233.0f, %hi(A1C), %hi(A20)
    MINE    1.0f, %hi(A18), %hi(A20), %hi(A1C), 10.0f, 199.0f, 233.0f

Golden's last five land in `f30,f28,f26,f24,f22` — one descending hoist group covering every
callee-saved FP register — so golden's two global loads sit where only a hoist can sit. Two
measurements then close both halves:

* a pre-loop SOURCE statement can never be emitted after the hoist group (moving one to be the
  last pre-loop statement moved its own `lui` past the globals but still left it before the
  hoists);
* the two global loads CANNOT be hoists, because **IDO never hoists a global load out of a
  call-containing loop** — golden proves it against itself by reloading two other globals with
  `lui`+`lwc1` every iteration.

Jointly contradictory under any model where preheader order follows source statement order, so no
statement ordering, cast spelling or declaration type can reach it. That is an honest bail with a
mechanism, not a plateau.

## VALIDATE the frame decode against golden's own spill/reload pairs

The frame law tells you the declaration list is readable off the offsets. Golden will often *prove*
two of those offsets for you, which turns the decode from a reading into a checked reading.

Any value live across a call must be spilled and reloaded, so golden brackets its `jal` with the
pairs. On func_150825C0 (frame 0x50, home area 0x40..0x4f = 16 B):

    sw  v1,0x48(sp)  ...  jal func_150A6360  ...  lw  v1,0x48(sp)
    sb  t1,0x45(sp)  ...  jal func_150A6360  ...  lbu t1,0x45(sp)

That pins two homes outright — and the *widths* pin the types: `sb`/`lbu` at 0x45 means a `u8`
there. The decode then follows by arithmetic: with `i` at 0x48 and `ok` at 0x45, exactly two bytes
sit between them, so there is exactly one `u16` in the gap. That is how `t` was typed, and the
resulting list (0x4c f32 rad, 0x48 s32 i, 0x46 u16 t, 0x45 u8 ok, 0x44 u8 flags, 0x40 s32 j) was
correct first time.
**Look for the spill/reload pairs around every call before guessing any local's type.**

## LICM of a register-passed `lda` of a local — not a CSE, and not reachable by spelling

A distinct hoist to recognise. Golden rematerialises `addiu a0,sp,0xa8` (the address of a local
matrix) at each call site; the candidate hoists it into a callee-saved register once and uses
`move a0,s5`, which costs a saved-register slot and rotates every downstream register.

The natural theory — "it is CSE'ing the two references to `&mtx` across the call" — is WRONG, and
the diagnostic is cheap: pass a *different* pointer at one site so `&mtx` has only ONE reference.
It still hoists into `$s5` with `move a0,s5`. So this is loop-invariant motion of the address
computation itself, not common-subexpression elimination of two uses.

Consequence: the address SPELLING is not a handle. Eight independent forms — `mtx`, `&mtx[0][0]`,
`mtx[0]`, an `f32 *` parameter, `f32[4][4]`, `void *`, a flat `f32[16]` with casts, and a
cast-through-address — all score EXACTLY 1446. When you see this shape, stop respelling the
address and look for what else is competing for the callee-saved slot.
Related trade measured on the same function: an early-exit `if (part == NULL) continue;` kills the
`&mtx` hoist and hits golden's exact byte count (828), but the loop bound `6` immediately takes the
freed slot instead. Something must remove BOTH hoists at once; removing either alone just moves the
problem.

# ================================================================================
# THE BAIL SIGNAL IS ONLY VALID IF THE VARIANTS SPAN DIFFERENT AXES
# ================================================================================

**This has now been falsified TWICE, on two different functions, and both times the bail was
wrong.** Read this before writing "N independent spellings score identically, therefore tie".

The rule as previously stated — "two independent spellings leaving the score EXACTLY unchanged
means an allocation tie with no source handle" — is unsound as written. N variants that all score
the same are evidence only about the axis they vary. If all N are points on ONE axis, they say
nothing about any other axis.

* **func_1512B730** was parked as an immovable "loop-invariant ranking tie" on five spellings. All
  five respelled INDIVIDUAL STATEMENTS; none reordered INDEPENDENT ones. Sweeping statement ORDER
  took it **355 -> 165** and an exhaustive 720-ordering sweep then gave the law in closed form.
* **func_150825C0** was bailed at 95 on four respellings. All four varied the SPELLING of the timer
  block; none varied its SHAPE. Binding the scratch AFTER the guard instead of before it
  reproduced golden's integer register allocation **EXACTLY** — 13 mismatched integer registers
  down to zero.

So before recording a bail, list the axes you actually varied and name the ones you did not. The
axes known to be independent here:

  1. SPELLING of an expression (casts, operand order, literal form)
  2. ORDER of independent statements
  3. SHAPE — where a binding sits relative to a guard, a loop, or a call
  4. TYPE/WIDTH of a local or parameter
  5. SCOPE — block-local vs function-top declaration
  6. LINE placement (which statements share a source line)
  7. REFERENCE COUNT of a web (adding or removing a use)

A bail is only defensible when several of these are exhausted, or when a mechanism rules the
target out (a web reference-count that cannot be reached, a corpus scan showing no matched C
produces the pattern, or two jointly contradictory requirements).

## Corollary, seen three times now: BETTER STRUCTURE CAN SCORE WORSE

On func_150825C0 the variant with **zero** integer register mismatches scores **230**, while the
variant with thirteen scores **95**. The 230 is strictly closer to golden — its whole integer body
matches — and asm-differ charges more for the one remaining row's shape than for thirteen renames.
Track `ins/del/chg/register-only` counts separately and read the actual diff rows; never let the
scalar score alone pick which candidate to park. The parked file here holds the *structurally*
better body even though its number is worse, which is the right call.

## A binding that spans both arms of an `if` costs a callee-saved register

The mechanism that moved func_150D1C30 from 1538 to 1425 at golden's exact byte count.

If both arms of an outer `if` bind the same local, that is ONE web spanning the whole construct, so
IDO gives it a callee-saved register held across the entire function — which pushes an argument out
of `$s0` into `$s1` and re-colours everything downstream. Reading the array expression *directly*
in the else arm confines the local to the if arm and lets golden's caller-saved `$v0`/`$v1` pair
appear. That removed seven prologue rows and about twenty else-arm rows in one edit.
Generalisation: when golden uses caller-saved registers where you use callee-saved ones, look for a
local your source binds in more places than golden's does. The fix is to stop binding it, not to
respell it.

## Which constants IDO must keep in a register (and which it need not)

Useful when a loop-invariant hoist is evicting the value you want hoisted. A constant needs a
register only if the consuming instruction has no immediate form:
* `multu` and `sb` have no immediate form -> their operands MUST be in registers.
* `bne reg,imm` is an assembler MACRO through `$at` -> the bound of a `!=` loop test need NOT be,
  and golden may rematerialise it in the latch instead of hoisting it.
So a loop bound appearing in a callee-saved register is not inevitable — it is competing for the
slot, and whether it wins depends on what else is live. On func_150D1C30 the plain `if` form does
not hoist the bound at all (the matrix address takes the slot), while the early-exit form hoists it
at rank one.

## An otherwise-unused PARAMETER is FREE int-width storage

The lever that took func_150825C0 from 230 to 30 and made its entire integer body byte-identical
to golden. It applies whenever you need an int-width carrier but the frame decode proves no local
fits.

IDO homes **every integer register parameter at entry** — `sw a0,0x50(sp)` / `sw a1,0x54(sp)` —
whether or not the function ever reads it. Those homes sit in the incoming-argument area, NOT in
the local area, so a parameter is 4 bytes of int-width storage that costs **nothing** against
`sum(sizeof(locals))`.

So when the frame says "16 bytes of locals exactly, no room" and the codegen says "this value must
be carried at int width", the answer is not a new local (which moves the frame) and not a `u16`
local (which truncates). It is an unused parameter. Golden's own `sw a1,0x54(sp)` is the evidence
that the slot exists and is free.

Ladder on that function, each rung measured:

    u16 scratch bound inside the guard ......... 230
    the parameter carries the halfword ......... 360 / 375
    the parameter carries the halfword,
      read by both tests ....................... 65
    the parameter carries D_800BE9A0 ........... 30   <-- the whole integer body matches

Note the last step: which VALUE the int-width carrier holds matters as much as having one. Try the
carrier on each candidate value, not just the obvious one.

## Read a suggested mechanism against the listing BEFORE spending builds on it

A brief proposed that a `move a1,v1` was argument setup, since `$a1` is an argument register. That
was falsifiable from the golden `.s` alone in about a minute — the block contains **no call at
all**; it returns 0 down both arms. Several builds would have been wasted testing it.
But the *axis* the hypothesis named (type/width) was correct and did contain the answer. So: check
a proposed mechanism against the disassembly first, discard the specific claim if it does not
survive, and **keep the axis**. A wrong mechanism on the right axis is still a useful pointer.

## Proving golden has exactly ONE variable web of a given class

Sharp technique for deciding whether a residual can come from a named local at all.

func_150825C0's remaining 4 rows are FP: golden reuses a dying operand register in place
(`mul.s $f0,$f0,$f0`) where we take fresh destinations. To test whether golden's source has a
second `f32` local, introduce one — paid for by merging two disjoint loop counters so the frame
does not move. Result: **50**, worse, and the diff shows why — the new local takes `$f12` and
pushes the existing one to `$f14`.

That is proof golden has exactly ONE named FP variable, so the in-place multiply cannot come from a
named local; it is the allocator reusing a dead temp. When a "just add a local" idea is available
and cheap, use it as a *probe* rather than a fix: where the new local lands tells you how many
webs of that class golden really has.

## A register swap can manufacture fake opcode differences

On func_150D1C30 two rows differ by opcode — golden `beqz v0,2b8 / nop` against ours
`beqzl v1,2bc / lw v0,0x24(s1)` — worth 200 points each and looking like a separate delay-slot
problem. They are not. They are a *consequence* of having the loaded pointer and the cursor copy in
swapped registers: with our assignment the scheduler can fill the slot, with golden's it cannot.
Fix the register swap and both opcode rows go away for free.
Before treating an opcode difference as its own problem, check whether the registers feeding it are
already wrong — if they are, it is downstream and costs nothing to chase directly.

## The in-place FP square is a STATEMENT FORM, not a spelling

Closed func_150825C0 from 30. Golden's `mul.s $f0,$f0,$f0` — the product reusing its operand's
register — comes from squaring a NAMED f32 local in its own statement:

    d = a - b;
    d = d * d;      /* -> mul.s $fN,$fN,$fN  */

The same square written INLINE inside a larger expression takes a fresh destination:

    if ((a-b)*(a-b) + (c-d)*(c-d) < r)   /* -> mul.s $f6,$f2,$f2 etc. */

Both forms are ordinary C and neither is a forcer; the difference is only whether the value has its
own statement. So when a residual is "same opcodes, same sources, same slots, only the DESTINATION
registers differ", the question is not how to respell the expression — it is whether the value
should be a named local with its own assignment.

### How it was found: mine the MATCHED corpus for the instruction pattern
Not by guessing at the compiler, and not by the idea the brief suggested (writing the subtraction
twice so CSE builds the temp — that was wrong). Disassemble every `expected/build/src/*.c.o`, keep
the functions that have no `#pragma GLOBAL_ASM` anywhere in `src/`, and grep for the pattern:
**57 in-place squares exist game-wide.** Two sit in one file and settle it between them:

* `game_83300 func_1505A6F8` (matched, live C) — `x = p->x - q->x; x *= x;` … reproduces golden's
  cluster instruction for instruction, nop included.
* `game_83300 func_1505693C` (matched, live C) — the contrast: an inline square in a comparison,
  taking fresh registers.

When a residual is a codegen shape you cannot reach, find a MATCHED function that already emits
that exact shape and read its C. Matched code is ground truth; the compiler manual is not available
and guessing is expensive.

## FOURTH RESIDUAL CLASS: an ASSEMBLER peephole, decided by basic-block boundaries

The three known classes are allocation, intra-block scheduling, and which block a reload lands in.
func_150D1C30 exposed a fourth, and it is not the compiler at all — it is `as1`.

`as1` rewrites `beqz X,L / nop` into `beqzl X,L+4`, by duplicating the fall-through block's last
instruction into the nullified delay slot and moving the join label past it. It does this at five
of the six unrolled guards in golden. **Guard 2 is spared** — and only because, in golden, its join
label is the first instruction of the 4×-unrolled main body, so the fall-through block ends at
`sb s4,0x9(t9)`, which is unsafe to duplicate (`$t9` is undefined on the taken path) and `as1`
gives up. Our compile has no block boundary at that address, sees a harmless load as the block's
last instruction, and fills the slot.

So the two remaining rows are worth 400 points and are **not a codegen problem at all** — they are
the assembler behaving correctly on a control-flow graph whose block boundaries differ from
golden's. The fix is to restore the boundary, which is a source-level control-flow question.
Recognise the shape: an isolated `beqz`/`nop` pair in golden where you emit `beqzl` plus a
duplicated instruction, with every register already correct, means look at where golden's basic
blocks begin — not at the branch.

## BOUNDARY CONDITION on "an unused parameter is free int-width storage"

The law is real but narrower than it first looked, and the difference is worth stating because it
cost a wave to establish.

A parameter's home sits in the CALLER's frame — `sw a1,0xB8(sp)` where framesize is 0xB8 — so it is
outside `sum(sizeof(locals))` entirely. That is exactly why it is free storage, and it is also why
it **cannot make the local area BIGGER**.

* Use it when you need an int-width carrier and the frame says no local fits. It adds storage
  without moving the frame. (func_150825C0: 230 → 30.)
* It does NOT help when the frame proves you need MORE declared-local bytes than you can account
  for. func_151B65D4's frame demands 96 bytes of locals while every named value totals 88; a
  parameter contributes nothing to that sum, so it cannot supply the missing 8. Six builds
  spending or removing those two words all scored worse (865, 873, 2900, 3003, 3108).

Diagnostic: work out whether your shortfall is in the LOCAL AREA (frame arithmetic) or in
INT-WIDTH CARRIERS (codegen wants a word). The parameter lever answers only the second.

## The `as1` branch-likely peephole: mechanism, and two refuted theories

Following on from the fourth residual class. Read off the object rather than guessed:

**Mechanism.** `as1` rewrites `beqz X,L / nop` by COPYING the instruction sitting AT `L` into the
branch-likely (taken-only) delay slot and moving the label to `L+4`. The copy at `L` remains for
the fall-through path, so both paths execute it exactly once and **no instruction is added** — which
is why a converted and unconverted object are the same size, differing only in a `beqz`→`beqzl` row
and a `nop`→duplicate row.

**REFUTED: "a label with more than one predecessor is a block boundary as1 respects."** Disproved
inside the same function — golden's epilogue join has THREE predecessors and `as1` still moved the
label and duplicated `lw ra,0x74(sp)` into both delay slots. Hunting for a second reference to a
join is a dead end.

**REFUTED: "express the peel/main-body seam in C."** Writing an unrolled loop as an explicit 2+4
pair of loops scores 8214 at 864 bytes — 36 bytes larger — because it destroys the unroller's own
peel. The seam is the unroller's property; expressing it changes it.

**The transform is SELECTIVE, so refusal is the common case.** Across every golden `.s`: 5,121
conditional branches carry a `nop` delay slot, and **708 of those target a plain `lw`** — trivially
duplicable, yet left unconverted. So the gate is not "is the target duplicable". Mining those 708
sites against matched C is the one remaining route with real information in it.

**Sharper statement of one open case**, for whoever picks it up: undo every conversion, and the
lone unconverted guard is the ONLY one in its function with a spare, non-defining instruction
(`li s4,1`) between the join label and the branch. Every other guard has only the load, which
*defines* the register being tested. Any explanation must account for that shape.

**You cannot inspect `as1`'s input.** `cc -S` and `cc -K` both kill the recompiled `ugen` with
SIGSEGV, and the intermediates are not kept. The assembler's behaviour has to be inferred from
matched objects.

## The as1 peephole gate is NOT a function of the local instruction pattern — closed by counterexample

func_150D1C30 is a DOCUMENTED BAIL at 400, and it is closed constructively rather than by fatigue.

The route was to mine the sites where `as1` declined to convert `beqz X,L / nop` into a
branch-likely with the target duplicated. Mined across all 464 golden objects:

    FILL 14,692   CONV 8,451   DECL 2,503

**Two thirds of the declines are not evidence at all** — they are `as1`'s own macro expansions,
which it never revisits: 797 div/divu `break` guards, 541 `lui` `%hi` halves, 137 `multu`, plus
`mflo`/`mfhi`. The honest population is **950 declines against 8,308 conversions, a 10.3% decline
rate**, and only ~250 of those sit in TUs built at the real `-O2 -g3` (init_1AAE0, init_20000,
init_1C060 and game_221290 carry `-g`/`-O1` overrides).

**No candidate discriminator is a gate.** Each is a weak correlation: candidate mnemonic spans
3.3%–17.0%, block length 5.9%–15.6%, forward vs backward 23.7% vs 12.7%, label predecessor count
flat. The "sharpest clue" from the previous wave — that the declining guard is the only one with a
spare *non-defining* instruction between the join label and the branch — comes out **backwards**:
that bucket has the LOWEST decline rate in the corpus (3.5%), not the highest.

**And then the counterexample, which is what actually closes it.** A hand-built probe compiled with
the real IDO and the repo's flags produces a guard whose window is the same instruction-class for
instruction-class as golden's — a label moved onto a spare `li` by the preceding guard's own
conversion, then `beqz RD,L / nop / lw RT,0x14(RD) / sb RC,0x9(RT) / L: lw RD,off(RB)`. The same
`as1` with the same flags **CONVERTS the probe and DECLINES golden**.

So the decision is not a function of the local instruction pattern. And since our object is
byte-identical to golden apart from those two words, **no local edit can reach it**. That is a
mechanism-backed bail, not a plateau.

### Method note worth keeping
When a corpus scan is meant to find a gate, first separate the tool's OWN artefacts from real
decisions — here two thirds of the population was macro expansion and would have produced a
confident wrong answer. Then, before trusting a correlation, build the 2×2 and check the predicted
cell really is extreme; a clue that is true of one function can be the *opposite* of the corpus
trend.

## A NON-INLINABLE FLOAT LITERAL IS A SYSTEMIC BLOCKER, AND IT IS DIAGNOSABLE IN ONE PROBE

Two cold targets in one wave hit the same wall, and the diagnosis is identical for both — so this
is a class, not a coincidence.

**Mechanism.** Live-C `.rodata` is `/DISCARD/`ed project-wide, so a float constant whose low 16 bits
are nonzero (it cannot be built with `lui`+`mtc1`) must be spelled `extern f32 D_XXXXXXXX`. That
turns a **link-time constant into a memory OBJECT**, and IDO treats the two completely differently:

* a literal's `%hi`/`%lo` pair is a link-time constant it never considers for loop-invariant motion;
* an extern variable's ADDRESS is an ordinary loop invariant, so with callee-saved registers free
  IDO hoists it — `lui s6,%hi / addiu s6,s6,%lo` in the preheader plus `lwc1 $f10,0(s6)` in the
  loop, where golden has `lui at,%hi / lwc1 $f10,%lo(at)` INSIDE the loop.
* it also defeats alias analysis: because the object might alias a store, IDO reloads it per use
  instead of keeping one copy.

Either way the extra web renumbers every temp register downstream and shifts the saved-register
block, so a **one-instruction cause produces a four-figure score**.

**The one-probe diagnosis.** Substitute a nearby literal that IS inlinable (low16 == 0) — it is
semantically wrong and for evidence only — and re-score:

* func_150380C0: parked form 1220 → probe **410**, and the entire asm-differ output is FOUR LINES
  (`lui at,%hi(D_8009863C)` vs `lui at,0xc7c3`, and `lwc1 %lo(...)` vs `mtc1 at,$f0`, twice). Every
  stack offset, every integer AND fp register, every branch target, all scheduling and the 0x80
  framesize are IDENTICAL to golden.
* func_150E7C9C: 1466 → **604**, with the `$s6` hoist gone and every prologue/epilogue offset and
  branch target matching.

That probe is worth running early: it separates "my reconstruction is wrong" from "only the
literal blocks me", and in both cases here it **proved the control flow, the declaration list, all
parameter types and the callee prototypes were already correct**.

**The fix is the yaml migration**, not a source change. Do NOT try to work around it:
* `extern const f32` is inert — IDO 5.3 does not use `const` for alias analysis (measured, 1466 and
  1220 unchanged).
* Swapping operand order is inert.
* A carrier local gives golden's instruction sequence but adds a stack home the frame decode proves
  golden does not have — that is a fake frame-shaping local, so refuse it.

**Two rodata entries holding the same value are a tell.** `D_8009863C` and `D_80098644` are both
`.float -99999` — IDO emits one constant-pool entry per source-level literal, so duplicates in a
block mean literals, not shared globals.

# ================================================================================
# RODATA MIGRATION: THE GRANULARITY IS A WHOLE TU BLOCK. NARROW SPLITS ARE IMPOSSIBLE.
# ================================================================================

A wave was planned around migrating 12 bytes and 4 bytes out of shared rodata blocks, on the
reasoning that only the target function's own constants needed to move. That plan was WRONG, and
the reason is worth knowing before anyone re-plans it.

## Law 1 - a migrated range must be 16-aligned, a multiple of 16, and zero-padded in the ROM

IDO emits .rodata with sh_addralign 16 and pads sh_size to a multiple of 16 - measured on 14 of 14
objects in this tree that have any rodata. ld honours that alignment. So a 12-byte range starting
at a vram address congruent to 0xC mod 16 gets padding inserted BEFORE it and four bytes of zero
padding written AFTER it, on top of the next function's constants.

Both migrations that already exist in conker.us.yaml are complete original-TU blocks ending in that
TU's own natural zero padding - that is the rule, not a coincidence:

    0x247780: 38c90fdb 00000000 00000000 00000000   [0x247780, .rodata, game_138520]
    0x24F480: 459c4000 3dcccccd 00000000 00000000   [0x24F480, .rodata, game_1ED0F0]

PRE-FLIGHT TEST for any proposed migration: confirm range_start % 16 == 0, and dump the ROM at
range_end to confirm zeros up to the next 16-byte boundary. Both candidates in that wave failed it -
one sat at 0xC mod 16 with a real constant (42652EE0) four bytes past its end, the other had three
live constants immediately after it.

## Law 2 - the obvious workaround is permanently off in this repo

Letting still-stubbed functions carry their own rodata in their nonmatchings .s is supported in
principle: splat has migrate_rodata_to_functions, and asm-processor emits const char _asmpp_rodataN
placeholders for exactly this. It can NEVER fire here. splat pairs a .rodata subsegment with a c
subsegment only when they are SIBLINGS, and siblings are computed per parent code segment
(splat/segtypes/common/code.py lines 259-270). Conker's yaml puts all C text in segment "game"
(vram 0x15000000) and all rodata in segment "game_data" (vram 0x80082B20), so nothing is ever a
sibling.

Proved by experiment rather than by reading: setting a whole-block migration produced a correct
conker.ld line and intact symbol files - and DROPPED every stubbed function's rodata (a grep for
".section .rodata" under asm/nonmatchings returned 0 files). Turning it on would mean merging the
two top-level segments, i.e. rewriting the linker script.

## Consequence: rodata-blocked functions unlock in TU-LEVEL CLUSTERS, not individually

To migrate a block you must first decompile EVERY function that owns a constant in it, and in the
same commit convert every already-live consumer in that TU from extern f32 to a literal.
For game_64120's block that is a cluster of seven: func_15036F34, func_150379DC, func_150380C0,
func_15038468, func_15038620, func_1503A830, func_1503B708.

So when the inlinable-literal probe says "the C is right and only the literal blocks me", the next
question is not "how do I migrate this symbol" but "how big is the cluster that shares its block,
and is that cluster worth a campaign?"

### A finished function that cannot ship
func_150380C0 with its true literals scores 0 - byte-exact against golden both with and without -R -
and the object's own .rodata comes out as c7c34f80 4ebebc20 c7c34f80, golden's exact values in
golden's exact order. The C is DONE. It is unshippable only because those twelve bytes cannot be
linked to 0x8009863C. Park such a function with the literals in place and the reason recorded; it
costs one yaml line the day its cluster closes.

### Two corrections to a parked file, both from measuring rather than assuming
* func_150E7C9C's note claimed "frame 0xA8 reproduced EXACTLY". Wrong: 0xA8 only arises from the s6
  save that the extern hoist itself forces. The true frame is 0xA0.
* Its probe figure of 604 was measured with the WRONG constant (0.4375f). With the true literal
  0.4315068424f the residual is 399, and at 399 there is not one inserted, deleted or reordered
  instruction - only the frame size, one addiu offset, and a t-register rotation.
ALWAYS PROBE WITH THE TRUE VALUE; a convenient nearby constant measures a different function.

# ================================================================================
# SIBLING-PROJECT INTELLIGENCE: WHAT TRANSFERS, WHAT DOES NOT, AND FOUR NEW LEVERS
# ================================================================================

Checked the other N64 decomps for transferable lore. The result is worth recording because most
of it does NOT transfer, and the one source that does is not a Rare game.

## The landscape, measured rather than assumed

* **Perfect Dark** (Rare, 2000) - "fully decompiled" and yet **97.4%**. The project states the gap
  is "a small handful of functions ... not yet byte-matching even though they are functionally the
  same." CALIBRATION: a residue of functionally-correct-but-not-byte-matching functions is the
  NORMAL end state of a mature decomp, not evidence that this project is doing something wrong.
* **Banjo-Kazooie** (Rare, 1998, Conker's engine grandparent) - IDO, but `OPT_FLAGS := -O2` with
  **NO -g3** (read from its Makefile). Engine and struct lore transfers; NONE of our distinctive
  levers do. Stack homing, source-line-placement scheduling and the frame-layout law are all -g3
  artefacts. They are ours alone, which is why this cookbook has no upstream.
* **Banjo-Tooie** (WIP, Mr-Wiseguy) - the DIRECT engine sibling of Conker, same era and lineage.
  Thin on matching lore, but the best external candidate for STRUCT LAYOUTS AND PROTOTYPES - i.e.
  the `unknownN` blocker class (func_151B65D4), which is an RE problem, not a codegen problem.
* **Paper Mario** - GCC 2.8.1, NOT IDO. A dead lead; do not spend time on it.

## The real source: OoT's "-O2 decompilation (for IDO 5.3)" guide

Same compiler, different game. It INDEPENDENTLY CONFIRMS laws derived from scratch in this file,
which is the strongest validation any of them have had:

* naive codegen creates pseudo-registers WITH RESERVED STACK SPACE, then the optimizer promotes
  them to registers while PRESERVING the reservations  == our stack-home law
* rodata literals are "really const" and are HOISTED TO FUNCTION START IN SAVED REGISTERS
  == the exact extern-hoist mechanism behind our whole rodata blocker class
* `&a[i]` vs `a + i` selects different loop-counter strategies  == our pointer-vs-index law
* moving statements between basic blocks affects regalloc  == our which-side-of-a-guard lever
* constants in locals are REMATERIALISED after calls rather than spilled  == our mask law
* "IDO does not use SSA form" - each variable generally stays in ONE register, so reusing a
  variable produces surprises. This is the MECHANISM behind our measured "merging two locals
  backfires" result (10 -> 55/80/293/1248).

### RECONCILIATION, not a correction, to the web-reference-count law
The guide gives the allocation order as **v0, v1, a0-a3, t0-t5, then stack**. This file says
`$v0, $v1, $a1, $a2`. NOT a contradiction: ours was derived on functions WITH PARAMETERS, where
`a0` (and often `a3`) is already occupied by an incoming argument. Ours is the special case.
BUT IT MEANS OUR LIST STOPS TOO EARLY. Extend the ranking through `a3` and `t0-t5` before
declaring a register unreachable - a bail that assumed the list ended at `$a2` may be wrong for
any function with more live webs than four.

## FOUR LEVERS WE DID NOT HAVE (verify each before trusting it)

1. **`void f(void)` uses 4 MORE bytes of stack than `void f()`.** A pure frame-size knob with no
   semantic change. This tree currently has 288 `(void)` prototypes and exactly 1 empty-paren.
2. **Calling a function that returns a value consumes stack EVEN IF THE RESULT IS IGNORED.**
   A second frame knob.
3. **`for (i = 0, other = 4; i < 4; i++)`** - multi-init in the loop header as a regalloc lever.
4. Three cheap axes: comma vs semicolon statement separation; ternary vs if/else (occasional
   regalloc difference only); and DUPLICATING an expression to let CSE fold it back, forcing a
   reorder (the inverse of our break-a-CSE-by-re-spelling-one-call-site law).

**WHY 1 AND 2 MATTER MORE THAN THEY LOOK.** The BAIL checklist in this file contains
"Stack-aggregate off-by-one-WORD ... BAIL" - a frame off by exactly one word, declared
unreachable BECAUSE WE HAD NO FRAME LEVER. There are now two, and both move the frame by exactly
4 bytes. Every bail in that class is re-openable.
CAVEAT, and it is the project's own standard: the OoT guide marks its own -g/-O2 stack claim
"TODO: verify". VERIFY BOTH IN THIS TREE BEFORE USING THEM, and if either turns out load-bearing
in a shipped match, it faces the delete-and-objsame test like any other construct. A prototype
spelling is a declaration change, not a no-op mask, so it is defensible in principle - but
"defensible in principle" is not the standard here; measurement is.

# ================================================================================
# WAVE 33 - TWO CLEAN CLASSIFICATIONS, ZERO CLOSED
# ================================================================================

Four cold targets, chosen to avoid the rodata class. The avoidance WORKED: both probes came back
negative (func_1000CEAC has zero float ops at all; func_15160E30's only constants are 255.0f and
IDO's 2^31 float->unsigned bias, both low16==0 and inlinable). The rodata screen is now a reliable
pre-filter and should stay in every brief.

## func_15160E30 @430 - a PURE SCHEDULER residual, and a positional proof

Frame EXACT at 0x100. The differ shows **zero 'r' (register), zero 's' (stack-offset) and zero 'i'
(immediate) rows** - ten rows out of ~230 instructions, all pure ordering, instruction counts equal
in every block. Five source variants scored IDENTICALLY at 430 (struct pointers vs s32[2]+casts,
operand order of the multiply, declaration-order swap of two locals), which by the N-no-ops test
says those axes are all dead.

THE FINDING WORTH KEEPING: the function has four `return 1` tail blocks compiled from IDENTICAL
source. **Two of them match golden exactly; two do not.** Same source, same registers, different
schedule. That is direct evidence that the residual is POSITIONAL - a scheduler tie-break decided
by where the block sits, not by anything written in it. It is the cleanest permuter target this
project has produced, and it is exactly the class the -g3 source-line lever acts on.

## func_1000CEAC @2710 - one missing web explains both the frame AND the register map

Control flow reproduced essentially instruction-for-instruction across all 20 regions (rotated
osRecvMesg while-loop, 16-bit mask loop, 4-way dispatch, unrolled-by-2 tail loop all line up).
The callee-saved map differs by ONE web:

    golden   s3=&D_800418B0  s4=&D_800BE9E4  s5=2      s6=ptr8  s7=1
    ours                                     s5=ptr8   s6=1     s7=&D_800BE9E4

and every t-register in the four dispatch arms renames in lockstep - that is where the bulk of
2710 lives. Frame 0xa0 vs golden 0x98: **exactly one surplus compiler temp slot**, with both sides
carrying 5 live spills. One cause, two symptoms.

THE STEP THAT PAID MOST: deleting a `timers` local took 6320 -> 3360, and the ENTIRE tail loop then
matched including golden's spills around both calls. A local you added "because the value is used
twice" can cost four figures.

**THIS IS THE FIRST TARGET FOR THE NEW FRAME LEVERS.** The frame is 8 bytes heavy = two 4-byte
knobs, and the function calls several routines whose return values it ignores. Lever 2 above
predicts exactly this shape.

# ================================================================================
# NEGATIVE, MEASURED: BOTH IMPORTED "FRAME LEVERS" ARE FALSE AT -O2 -g3. RETIRED.
# ================================================================================

Two claims were imported from OoT's "-O2 decompilation (for IDO 5.3)" guide and written up here
as promising, on the grounds that this project had NO frame lever at all and the bail checklist
contains a whole class ("stack-aggregate off-by-one-WORD") that was declared unreachable purely
for want of one. Both are now MEASURED FALSE at our flags. Do not spend a wave on them.

    L1   `void f(void)` uses 4 more bytes of stack than `void f()`      -> FALSE
    L1b  same, applied to the DEFINED function's own declaration        -> FALSE
    L2   calling a function that RETURNS a value costs stack even when
         the result is ignored                                          -> FALSE

## The measurement (scratchpad/framelever2.sh, run outside conker/src so the ROM is untouched)

Real IDO 5.3 via `../ido/ido5.3_recomp/cc`, the Makefile's exact CFLAGS, `-mips2 -o32`, `-O2 -g3`.
Framesize read from the prologue `addiu sp,sp,-N`.

THE DESIGN POINT THAT MAKES THE NEGATIVE TRUSTWORTHY: a single test function proves nothing here,
because IDO rounds the frame to 8 bytes and that padding can absorb a 4-byte delta. So the number
of live-across-a-call locals was SWEPT 0..8, which walks the frame through 24/32/40/48/56/64. A
real +4 must push at least one of those across a boundary and surface as +8. It never did.

    N locals      0    1    2    3    4    5    6    7    8
    (void)       24   32   32   40   48   56   56   64   64
    ()           24   32   32   40   48   56   56   64   64
    delta         0    0    0    0    0    0    0    0    0

L1b (probe(void) vs probe(), N = 0,2,4,6): leaf/32/40/48 on both sides, delta 0 throughout.
L2 (ignored int return vs void callee vs captured, N = 0..6): 24/32/32/48/48/56/56 on ALL THREE
columns. An ignored return costs exactly what a void callee costs.
An earlier noisy run also measured plain `-O2` with the same result, so this is not a -g3 artefact.

## What this means, and the correction it forces

* The "stack-aggregate off-by-one-WORD" BAIL CLASS DOES NOT RE-OPEN. It was written up here as
  re-openable on the strength of these levers. That was premature; it stands as a bail.
* This project still has NO cheap frame lever. The frame responds to the DECLARATION LIST (the
  stack-home law) and to assigning through a parameter instead of a shadow local - and, per the
  strongest measured result in this file, to DELETING an unnecessary local (6320 -> 3360 on
  func_1000CEAC). That remains the whole toolkit.
* GENERAL LESSON ABOUT IMPORTED LORE. The OoT guide is credible - it independently confirms six
  laws derived from scratch here - and it still shipped two claims that do not hold at our flags.
  Its own text marks the stack claim "TODO: verify". CONFIRMED-ELSEWHERE IS NOT CONFIRMED-HERE:
  measure every imported law in this tree before ranking a wave around it. Cost of measuring: one
  script and two minutes. Cost of not measuring: a wave.

## What SURVIVES from the same source (unaffected by this negative)

The allocation-order correction still stands and is still worth using: the full order is
**v0, v1, a0-a3, t0-t5, then stack**, where this file previously recorded only v0, v1, a1, a2.
Those agree - ours was derived on functions WITH parameters, where a0 (and often a3) is already
occupied - but our truncated list can make a register look unreachable when it is merely further
down the table. Re-check any bail that concluded "unreachable" while counting only four slots.

# ================================================================================
# THE TU-PHASE HYPOTHESIS IS DEAD. MEASURED AT THE BYTE LEVEL, THREE WAYS.
# ================================================================================

The idea: IDO's temp/register rotation counter is TRANSLATION-UNIT scoped, so a function's
tie-break phase depends on the real code compiled before it, and in a TU that is mostly
`#pragma GLOBAL_ASM` stubs that phase is wrong BY CONSTRUCTION. It predicted that several of the
twelve bails at score <= 20 would compile to 0 with no source change once neighbours were
decompiled, and it was the main argument for whole-TU campaigns over size-ranked targets.

IT IS FALSE. Not "no score change" - NO BYTE CHANGE.

1. game_34F20. Each of the five live neighbours replaced in turn by a GLOBAL_ASM stub -
   func_15007A70 (declared BEFORE the target) and four declared AFTER. The target came out
   byte-identical every time (.text+reloc sha1 a8bd8ff6a1632607).
2. game_18D770, on a genuine tie-class function. func_15160E30 (frame exact, stack-offset multiset
   exact, zero register rows, purely positional residual) survived five neighbour stubs including
   the function immediately preceding it - byte-identical (sha1 866339abee517824).
3. MAXIMUM PERTURBATION. func_15160E30 compiled with ALL 111 other function bodies in the TU
   demoted to prototypes - 4 FUNC symbols instead of 115 - is byte-identical to the full-TU build:
   words=0, relocs=0.

THE HARNESS WAS PROVEN, which is what makes this a result and not a broken null: every stub variant
changed exactly its own function's bytes and no other function's, and all nine whole-object sha1s
differ, so the builds were distinct and not stale. The one plausible confound - the -g3 line table -
was held fixed by padding each stub to preserve line count, then tested separately as a control.

**THE CORRECT STATEMENT: the TU HEAD matters (types, file-local prototypes, macros); other function
BODIES do not.** There is no TU-scoped counter for function bodies to advance.

CONSEQUENCE. Whole-TU campaigns can NO LONGER be justified by "the neighbours fix the phase". They
remain justified by shared types, shared file-local prototypes, and rodata-block granularity
(migration is per-TU) - which are real and separate reasons. Size-ranked target picking is NOT
disqualified by this experiment.

# ================================================================================
# MEASUREMENT TRAP: `-o <func>` IS **NOT** BOUNDED BY THE SYMBOL SIZE
# ================================================================================

This file previously said boundedness is per-function and told you to check the symbol size. That
advice is INCOMPLETE and the second half is wrong for our invocation. Read from diff.py:

    max_function_size_bytes = args.max_lines * 4          # line 572
    ...
    if end is not None:  end_addr = eval_int(end)
    else:                end_addr = start_addr + config.max_function_size_bytes   # 1499, 1591

`st_size` IS parsed out of the symtab (1461/1468) and is NOT used to set the window. So with our
standard `--max-lines 4096` the disassembly window is **16,384 bytes from the symbol start** - far
past the end of every function in this project (the ones in play measure 548-1704 bytes).

WHY IT USUALLY DOES NOT BITE: the bytes after your function are normally the injected asm of
still-stubbed neighbours, identical on both sides, so they contribute nothing and the window LOOKS
bounded. Symbol sizes are present for these functions (func_1000CEAC 1100, func_15160E30 1032,
func_15007B3C 1704, func_15162B28 976, func_1505A3A8 548) - having a size does not mean it is used.
(4,773 of 10,185 FUNC symbols in expected/ have size 0, which is a separate issue.)

WHEN IT DOES BITE, AND IT ALMOST FAKED A MAJOR RESULT: **perturb any LATER function in the same TU
and the earlier function's score moves, purely because the differ is comparing those later bytes.**
Anyone testing "does a neighbour affect my function" BY SCORE would have measured a large effect
and confirmed the TU-phase hypothesis. The experiment above only survives because it compared the
function's OWN byte range (sha1 of its .text+relocs), not the score.
RULE: for any question of the form "does X elsewhere in the TU affect this function", compare
BYTES over the symbol's own range. Never use the score.

# ================================================================================
# THE -g3 SOURCE-LINE-PLACEMENT LEVER DID NOT REPRODUCE - QUALIFY IT
# ================================================================================

The levers list credits "source LINE placement is a scheduling lever under -g3" with closing
func_15196748 from a bailed score of 1. On func_15160E30 it produced NOTHING: six variants on the
four `return 1` tail blocks - blank line before the last two, before all four, before the 3rd only,
before the 4th only, merging the last two onto the store above, merging all four - every one
byte-identical. The merges genuinely move those instructions to a different line in the -g3 line
table (asm-differ's source column proves it) and codegen does not move. Controls in game_34F20
agree: inserting 1, 3 or 10 blank lines ahead of a function left it byte-identical.

**So the lever is NOT "absolute line number" and NOT "blank lines".** Whatever closed func_15196748
was something narrower - most likely which STATEMENTS SHARE A LINE at an adjacent-pair granularity
(this file already records "line joins pay at the ADJACENT-PAIR granularity, not the block"), not
where a line sits. Do not budget a wave on blank-line placement again without re-reading that entry.

# ================================================================================
# permuter_tu.sh SELFTEST CHECK (e) IS AN ARTIFACT - ITS CONCLUSION IS WRONG
# ================================================================================

Check (e) reports "isolation DIFFERS from the in-TU build. A plain single-function permuter would
optimise the wrong bytes; this harness is load-bearing." That is a FALSE ALARM: objdump_fn.sh
includes objdump's ADDRESS COLUMN, and a function necessarily sits at a different offset in a
4-symbol object than in a 115-symbol one, so the sha1 differs while the instruction bytes are
identical (measured: words=0). The header comment's "on-record case of a source that compiled to
golden bytes in isolation and scored 560 inside its real 40-function TU" is either the same address
artifact or a TU-HEAD difference (types/prototypes/macros), which the isolation test preserved.
permuter_tu.sh remains worth using for its exact flags and per-function scoring; only check (e)'s
CONCLUSION is wrong.

# ================================================================================
# FRAME LAW, SHARPENED: A SPILLED LOCAL IS SPILLED TO ITS OWN HOME
# ================================================================================

Worth 569 points on func_1000CEAC and it is the operational half of the stack-home law that had
been missed. Because a spilled local goes to ITS OWN HOME, any spill offset in golden READS OFF
that local's declaration POSITION:

    declaration ordinal = (framesize - spill_offset) / 4

Golden spills ptrC to 0x80 with framesize 0x98 => ptrC is the SIXTH declared local. And the frame
size then reads off the local COUNT. Golden 0x98 vs ours 0xa0 => golden has SEVEN locals where we
had NINE. That is not "one surplus compiler temp" (the earlier park's reading, and it survived
three hours of wrong work) - it is TWO SURPLUS AUTOS, and no amount of statement-shuffling moves it.

**WHEN THE FRAME IS 4N BYTES WRONG, COUNT LOCALS. DO NOT CHASE TEMPS.** And read every spill offset
in golden as a declaration ordinal BEFORE writing the declaration list.
COROLLARY THAT COSTS TIME IF MISSED: the frame rounds to 8, so removing ONE local can leave the
frame unchanged and look like a dead lever. **Probe by removing locals in PAIRS.**
The 11-ablation falsification of the "surplus temp" theory (every single-statement deletion inside
case 1 and case 2, all frame -160) is the model for killing a frame theory cheaply.

## Corollary: a deduced declaration list is FALSIFIABLE, and it falsified the obvious source
Seven locals with ptrC sixth, plus "mask and i are simultaneously live so they cannot be one
variable" and "ptr8 must be a local (golden holds it in s6 across osRecvMesg)", left exactly one
arrangement: NO `p` local (index the array directly - which golden's four reloads already showed),
and **`chan` and the loop counter `i` are THE SAME VARIABLE**. Corroborated independently by golden
reusing a2 for both the chan copy and i=0; with a separate chan we emitted a3 there, and the merge
snapped it to a2.

# ================================================================================
# AFTER ANY STRUCTURAL WIN, THE WHOLE NEGATIVE LIST IS STALE
# ================================================================================

A clean case, and it should be doctrine. On func_1000CEAC's old base, writing `default:` last scored
2624 vs 2710 - an apparent 86-point WIN, and the previous park listed it as the #2 thing to try.
After the p->unk8/p->unkC read order was fixed, the SAME change scores 2410 vs 2141 - a 269-point
LOSS. **Negatives measured on a defective base are not negatives.** Re-measure the ruled-out list
after every structural improvement, and record which base each negative was measured against.

# ================================================================================
# A PERMUTER "WIN" REFUSED ON BINARY EVIDENCE - THE RIGHT KIND OF REFUSAL
# ================================================================================

Over 5,287 gated iterations the permuter's single best output on func_1000CEAC was exactly
`u16 mask` -> `u32 mask`, worth 2141 -> 1795 on the real differ with the frame still exact. It is
semantically identical (mask is `lhu`-loaded so it is already 0..0xffff, and `>>= 1` never widens
it) and contains NO banned construct - a grep for the usual tells passes it.
IT IS STILL WRONG. Golden contains TWO redundant u16 truncations that only a u16-typed variable can
produce: `andi v0,v1,0xffff` immediately after an `lhu`, and `andi t3,v0,0xffff` after the `srl`.
A u32 spelling deletes them. So the lower score buys itself by making the output LESS like golden -
the exact rule this file already states. **A 346-point improvement that removes two instructions
golden has is a regression, not a win.**

# ================================================================================
# NEW LAW: A REPEATED MASK CONSTANT MOVES INTO A REGISTER AT ITS THIRD USE
# ================================================================================

This closed func_1512317C outright (565 -> 0) and it is corroborated three ways.

THE OBSERVATION. Golden emits `and $t6, $t5, $a1` with `addiu $a1, $zero, -0x11` set up earlier,
where the obvious spelling gives `andi t6, t5, 0xffef`. Writing `~0x10` in ONE mask block and
`0xFFEF` in the other scores 565; writing `~0x10` in BOTH scores **0**.

TWO SEPARATE THINGS ARE GOING ON, and both matter:
 1. **THE THIRD USE SWITCHES TO A REGISTER.** Corpus evidence from func_15125DB4, a matched sibling
    in the same TU, showing the ladder in one function:
        andi  $t9, $t8, 0xFFEF
        andi  $t1, $t0, 0xFFEF
        addiu $a0, $zero, -0x11      <- third use materialises the constant into a register
    and the identical ladder appears for 0xFFF0 (andi, andi, addiu -0x10) and 0xFFE0.
 2. **THE SPELLINGS MUST AGREE.** IDO counts uses of the CONSTANT EXPRESSION. Spelling one site
    `0xFFEF` and another `~0x10` gives it two different constants, each below the threshold, so
    neither is promoted. Pick one spelling for a given mask and use it everywhere in the function.

THE COUNTER-EXAMPLE THAT BOUNDS THE LAW, and it is why this is a law rather than a superstition:
matched func_150EEC84 (game_11A680.c) contains `*(u16 *)((u8 *)D_800BE748 + (idx * 6)) &= ~0x10;`
and compiles to a bare `andi t4,t3,0xffef`. So `~0x10` does NOT always produce a register - a SINGLE
use stays immediate. The trigger is the third use, not the spelling.

USE IT AS A DIAGNOSTIC: if golden materialises a mask into a register and you emit `andi`, count
your uses of that exact constant expression - you probably have two where golden has three, or you
have split one constant across two spellings.

# ================================================================================
# THE RODATA PRE-FILTER PROBE, AS THIS FILE STATED IT, IS WRONG. IT GIVES FALSE NEGATIVES.
# ================================================================================

The probe was written as: substitute a low16-zero literal, and "if the score COLLAPSES and the
residual becomes a handful of lui/lwc1 rows, the C is right and the function is rodata-blocked."
**That misses an entire failure mode.** On func_150EFB80 the substitution made the score WORSE
(935 -> 1140), because a lui-able literal inlines as lui+mtc1 and DELETES the `lwc1` that golden
actually has. Read by score, that function looks not-rodata-blocked. It is rodata-blocked.

**CORRECTED PROBE: substitute the literal and read the SHAPE, not the score.** Specifically, check
whether the FRAME SIZE, the $f-REGISTER SAVE LIST, and the LOOP-INVARIANT REGISTER ASSIGNMENTS snap
to golden. On func_150FFD84 that was decisive in a single build: frame 0x108 -> 0x118 with the two
`sdc1 $f26/$f28` saves reappearing.

## TWO distinct failure modes of `extern f32` - this file only described the first

**(1) ADDRESS HOIST.** An `extern f32` is an addressable object, so its ADDRESS becomes a
loop-invariant candidate and competes for the last callee-saved register, EVICTING the real
candidate. On func_150EFB80 golden puts the divisor constant 0x65 in `$s8` (`li s8,0x65`, then
`divu zero,v0,s8`); the extern spelling puts `&D_800A1828` there and falls back to `li at,0x65`.
Cost: ~8 rows plus an address shift = 935.

**(2) LOAD HOIST DENIED - NEW, and it corrupts the frame.** Golden hoists the VALUE of a rodata
float out of a loop into an `$f` register. A loop-invariant LOAD can only leave a call-containing
loop if the compiler knows the memory cannot be written - i.e. only for a true constant. Spelled
`extern f32`, the load is correctly pinned INSIDE the loop, which also removes the `sdc1` saves of
the registers that would have held it and **SHRINKS THE FRAME** (0x118 -> 0x108 on func_150FFD84).
=> **ON A RODATA-BLOCKED FUNCTION THE FRAME CAN BE WRONG FOR A REASON THAT HAS NOTHING TO DO WITH
THE DECLARATION LIST.** Check the $f-register save count against golden BEFORE hunting phantom
locals. This is the first known way to mis-apply the frame law and waste hours.

# ================================================================================
# LOOP-INVARIANT CANDIDATES ARE RANKED BY SOURCE POSITION OF FIRST USE
# ================================================================================

Falsifiable and falsified in the right direction: reordering two statements moved `li s8,0x65` to
golden's exact address. IDO ranks loop-invariant candidates by the SOURCE POSITION OF THEIR FIRST
USE and hands out whatever callee-saved registers remain. Useful whenever a near-miss differs only
in WHICH value occupies the last s-register - the lever is statement order, not spelling.
(Related but distinct from the web-reference-count law, which ranks by defs+uses.)

# ================================================================================
# MINE THE MATCHED CORPUS **FIRST**, AHEAD OF THE FRAME DECODE
# ================================================================================

This out-earned every other lever in wave 36 and the ordering advice is now explicit. Both of one
agent's targets had their spawn structs ALREADY DEFINED in matched code (game_17CAF0.c), and a
matched sibling (func_15152B38) shared the same two locals - which calibrated both struct sizes
exactly and confirmed the declaration-order reading BEFORE a line of C was written. Result:
func_150EFB80 scored 945 on its FIRST build with the frame already exact.

**STANDARD FIRST STEP ON ANY COLD START: grep the matched corpus for another caller of the same
callee, and for the struct types it passes.** Matched code is ground truth and it is free. Only
then decode the frame.

# ================================================================================
# WAVE 36 RESULT AND THE CONCRETE UNBLOCK ORDER
# ================================================================================

CLOSED: func_1512317C, 908 B, game_14FF90.c - a per-frame camera mode gate. Verified independently:
score 0 with and without -R, all 55 siblings in the TU still 0, .text IDENTICAL (23,808 bytes),
.rodata/.data/.bss identical, symbol size 908 on both sides, tree-wide pragma count 1745 -> 1744.

PARKED: func_151B7328 @676 - frame is 8 bytes heavy in the COMPILER-TEMP pool, not the aggregates
(proved by a deliberately-wrong shrink: cutting the struct by 8 gave framesize 0x100 with the
header at 0xE4 exactly, so 0xB0 of aggregate is right). A 9-build bisect localises the surplus to
two statements that cost FOUR pool webs in our spelling and TWO in golden's.

**THE ACTIONABLE ONE.** func_150EFB80 @935 and func_150FFD84 @6378 are BOTH rodata-blocked, and
neither is register-allocation-hard - both are within a handful of instructions of matching. The
rodata migration is not a niche jump-table unlock; it is what closes this whole family.
game_12C1E0's block 246BF0 needs only **FOUR** more functions decompiled - func_150FF2D4,
func_150FF474, func_150FF6E0, func_150FF840 - versus SIXTEEN still stubbed in game_11C2B0. That is
a bounded campaign, and it should close func_150FFD84, whose loop body is already byte-exact under
the probe. Prefer it to game_64120's seven-function cluster.

# ================================================================================
# RODATA MIGRATION, THIRD AND HARDEST LAW: A TU OWNS **ONE CONTIGUOUS RUN**
# ================================================================================

The wave-37 campaign was planned on the belief that game_12C1E0's five remaining functions all
owned constants in ONE block (0x246BF0), so closing four would permit a one-line migration and
unlock the fifth. **That premise was wrong, and the reason generalises to every future campaign.**

An object file has ONE `.rodata` section placed at ONE address. So a TU can only be given a SINGLE
CONTIGUOUS RUN of the ROM's rodata. Measured for game_12C1E0:

    func_150FF474's constants   ROM 0x246BE4 .. 0x246BF0   (tail of block 0x246B10)
    ...0x40 bytes of NAMED objects referenced from OTHER TUs sit between...
    func_150FFD84's constants   ROM 0x246C54 .. 0x246C5C   (inside block 0x246BF0)

To own both, game_12C1E0 would have to own the foreign objects in between - which belong to other
translation units. **There is no yaml spelling for that.** The migration is not merely blocked
pending more decompilation; it is UNAVAILABLE, permanently, for this pair.

So the pre-flight test for any proposed campaign now has THREE parts, and the new one is first:
 0. **CONTIGUITY** - collect every rodata symbol the TU's functions reference, sort by ROM address,
    and confirm NOTHING between the lowest and highest is referenced from another TU. If a foreign
    object sits in the middle, stop: no amount of decompilation will fix it.
 1. 16-ALIGNED start, MULTIPLE OF 16 length (IDO emits .rodata with sh_addralign 16 and pads
    sh_size to a multiple of 16 - measured 14/14).
 2. zero padding in the ROM from range_end to the next 16-byte boundary.

## AND MIGRATION IS NOT ALWAYS A WIN - IT CAN COST
Discovered on func_150FF840, which is at score 5 with `extern` spelling: converting to true literals
took it **5 -> 1170**. Golden emits a SEPARATE `lui %hi` per constant; a TU-local pool shares one
`lui %hi(.rodata)` across them. So a function whose golden code loads several constants
independently is HURT by owning its pool. Check the golden `lui` pattern before assuming a
migration helps: separate `lui %hi` per constant => leave it external.

# ================================================================================
# THE UNBOUNDED-WINDOW TRAP IS REAL, AND IT IS ENORMOUS - MEASURED BOTH WAYS
# ================================================================================

Last wave established that `-o <func>` disassembles `max_lines * 4` bytes from the symbol start
rather than stopping at the function. Wave 37 was the first to work SEVERAL functions inside ONE TU,
which is exactly the condition that makes it bite, and the magnitude is not marginal:

    func              bounded (own symbol range)      --max-lines 4096 window
    func_150FF2D4                  325                        12778
    func_150FF474                 4660                        12553
    func_150FF6E0                  180                         7988
    func_150FF840                    5                         7708
    func_150FFD84                 6378                         6378

A function at **5** reads as **7708** if you score it the default way while its neighbours are also
being edited. Anyone driving a multi-function TU by the raw number is chasing noise.
**RULE: when more than one function in a TU is in flight, bound the window to the symbol's own
instruction count (or byte-compare the symbol's range) for every reported score.**

# ================================================================================
# functions.h DECLARES THE RNG WRONG, AND IT IS WORTH THOUSANDS
# ================================================================================

`func_150ADA20` is declared returning **u8** in conker/include/functions.h. It really returns
**s32**. The binary evidence is decisive: golden spills the raw result as a WORD and performs a
32-bit `divu`, whereas the u8 declaration narrows it to `sb`/`lbu`, i.e. it computes the modulo on
the low byte only - a different function.
Fixing it with the FILE-LOCAL SHADOW took func_150FF840 from **3950 -> 325**.

    #define func_150ADA20 func_150ADA20_u8_decl_in_functions_h
    #include "functions.h"
    #undef func_150ADA20
    s32 func_150ADA20(void);

**VERIFIED SAFE THE ONLY WAY THAT COUNTS:** after the retype, all 11 already-matched functions in
that TU still byte-compare IDENTICAL against expected/. Do that check before trusting any retype.
This is the second file-local shadow to pay four figures. The RNG is called all over the tree, so
expect this one specifically to recur - and prefer the shadow to editing the shared header, which
was tested and breaks 13 TUs.

## The same wave's second retype: pointer parameters declared as s32
Several callees (func_150FFCC8, func_150FFB6C, func_151D5A18, func_151D3E6C, and arg8 of
func_15102B38) take real POINTERS but are declared `s32`. With the wrong declaration IDO CSEs the
seven `addiu a?,sp,0x11c` address computations into one spilled temp; with real pointer types it
recomputes them as golden does. Worth **325 -> 5**.
GENERAL FORM: *if golden recomputes an address at each call site and you emit one spilled temp,
suspect a parameter declared as an integer where it is really a pointer.*

# ================================================================================
# A 2-D SUBSCRIPT AND A POINTER CURSOR ARE NOT INTERCHANGEABLE (1958 -> 180)
# ================================================================================

On func_150FF6E0, spelling the element as a genuine two-dimensional subscript
`&D_800A2080[which][i]` with an `s32` index local scores 180; hoisting a `struct17 *base` pointer
local scores 1958. The pointer form makes IDO **CSE the two `i*12` multiplies**, where golden
computes one by shifts and the other by `multu`. That extra shared web costs a third callee-saved
register and grows the frame 0x88 -> 0x90.
This is the same family as the existing index-vs-pointer-cursor entry, but the mechanism is worth
stating separately: the pointer form creates a CSE opportunity the subscript form does not.

# ================================================================================
# WAVE 37 RESULT
# ================================================================================

CLOSED: func_15152F70, 808 B, game_17CAF0.c - a randomised particle-burst spawner. Verified
independently: score 0 with and without -R, all 49 siblings in the TU still 0, .text IDENTICAL
(24,896 bytes), .rodata/.data/.bss identical, symbol size 808 both sides, pragmas 1744 -> 1743.

THE CAMPAIGN DID NOT CLOSE BUT IT LEFT THREE FUNCTIONS VERY CLOSE, all with EXACT frames:
  func_150FF840 @5    - one instruction. Golden fills the second `if`'s branch delay with a
                        speculated body load; live C picks the third `if`'s condition load out of
                        the branch target, forcing `beqzl` and duplicating an `lbu`.
  func_150FF6E0 @180  - one redundant `b` with `move v0,zero` in its delay slot that live C elides,
                        plus a UNIFORM +1 temp-rotation offset from the loop preheader onward.
                        Exactly one extra temp allocation happens in golden and it emits NO
                        instruction.
  func_150FF2D4 @325  - two rows: a `lw` one slot early, and golden duplicating `lui at,0x4208`
                        (34.0f) into a delay slot where live C shares one lui at the merge.
  func_150FF474 @4660 and func_150FFD84 @6378 are HARD BLOCKED by the unavailable migration above.

Naming a reciprocal (`inv = 1.0f/sqrtf(...)`) instead of inlining it twice fixed both `mul.s`
operand orders on func_150FF2D4 (525 -> 505) - another instance of the statement-form law.

# ================================================================================
# HARNESS TRAP: CRLF SILENTLY MAKES EVERY VARIANT SCORE IDENTICALLY
# ================================================================================

**This can FAKE the N-no-ops test, which is one of the load-bearing rules in this file.**

conker/src/game_1E37D0.c has CRLF line endings (3 of 464 live .c files do). A Python variant
harness matching `'\n'` patterns then matches NOTHING, `str.replace` returns the string unchanged,
the "variant" is byte-identical to the base, and every build reports the base score. One agent got
EIGHT consecutive identical readings this way, including two that were supposed to DELETE WHOLE
STATEMENTS.

Read against the N-no-ops rule ("if N mutually-exclusive no-ops all score identically, the binary
evidences one extra folded temp web"), that is a false positive generator: a broken harness produces
exactly the signature the rule treats as evidence.

**MANDATORY WHENEVER A VARIANT SWEEP RETURNS UNIFORM SCORES:**
 1. `.replace('\r\n', '\n')` on read, or operate on bytes.
 2. ASSERT the pattern was found before writing the variant (fail loudly, never silently no-op).
 3. Include a CONTROL VARIANT THAT MUST CHANGE THE SCORE, and check it fired.
**Treat "every variant scored identically" as a harness bug until the control fires.** Only after
the control fires may uniform scores be read as evidence about the compiler.

# ================================================================================
# as1 WILL NOT MOVE THE SECOND HALF OF A lui/%lo MACRO PAIR INTO A DELAY SLOT
# ================================================================================

The exact mechanism behind func_150FF840's residual of **5** - one instruction in 816 bytes.

Golden fills a plain `beqz t2,d78` from the FALL-THROUGH path with a movable
`lwc1 $f16,0x11c(sp)`. Our fall-through begins instead with `lwc1 $f0,%lo(D_800A217C)(at)` - the
second half of a `lui`/`%lo` MACRO PAIR, which as1 will not separate from its `lui`. Denied that
filler, as1 falls back to filling from the BRANCH TARGET, which forces an annulled `beqzl` and
DUPLICATES `lbu t3,0x133(sp)` (annulled copy plus real copy). That duplicate is the entire 4-byte
excess. There is no register-allocation error anywhere in the 203-word body.

UPSTREAM CAUSE, and this is the steerable part: golden issues the three scale constants as a BLOCK
at the head of the if-body and hoists BOTH operands of statement 1 above the branch; ours hoists one
operand and loads the constants lazily. So the lever is what is available at the top of the
fall-through, not the branch itself.

GENERAL FORM: **if golden has a plain branch where you emit `beqzl` + a duplicated instruction, look
at what starts your fall-through block. A `%lo` half, or anything else as1 cannot move, denies the
delay slot and forces the likely-branch form.**

# ================================================================================
# THE -g3 SOURCE-LINE LEVER IS FULLY DEAD - SECOND INDEPENDENT CONFIRMATION
# ================================================================================

Already qualified once (blank lines and absolute line number do nothing). Wave 38 killed the last
surviving reading: three ADJACENT-PAIR LINE JOINS - the one form still believed live - were
byte-identical on func_150F64DC. Combined with the earlier six variants on func_15160E30 and the
blank-line controls in game_34F20, the lever is retired in all its forms.
**Do not budget a wave on source-line placement.** Whatever closed func_15196748 is still
unexplained, and the honest position is that we do not know what it was.
(Note the CRLF trap above before trusting ANY uniform-score result, including this one - these
particular measurements were on an LF file, which is why they stand.)

# ================================================================================
# THE (s16) CAST ASYMMETRY: STACK ARGUMENTS TRUNCATE FOR FREE
# ================================================================================

An `(s16)` cast on a STACK-passed argument costs ZERO instructions; the same cast on a
REGISTER-passed argument costs `sll 16` / `sra 16`. Golden shows both halves in ONE call: `a3` gets
the sll/sra pair while the arguments at sp+0x10 and sp+0x14 get nothing, because the callee re-reads
the stack short with `lh` at offset+2.

**CONSEQUENCE, and it is a trap in the prototype-verification step: a golden stack argument with no
visible truncation does NOT disprove an s16 prototype.** Do not "correct" a prototype to s32 on that
evidence - check the CALLEE's load width instead.

# ================================================================================
# SPILL DESTINATION DISTINGUISHES A DECLARED POINTER FROM AN ADDRESS CSE
# ================================================================================

A refinement of the frame law that reads real information out of golden:
 * a POINTER LOCAL live across many calls spills to **its own declaration home**
 * a pointer that is merely an ADDRESS CSE (`&arg0->field`) spills to a **compiler TEMP slot**
Measured on both func_150F64DC (obj -> 0xC0, src -> 0x84) and its matched sibling func_150DFEFC
(obj -> 0xA8, src -> 0x78). So the spill OFFSET tells you which candidate pointers were really
DECLARED and which the compiler invented - decide the declaration list from that before guessing.

# ================================================================================
# TRAILING STRUCT PADDING, NOT A DUMMY LOCAL - AND WE HAVE SEVEN IN SHIPPED CODE
# ================================================================================

The matched func_151B6320 (game_1E37D0.c) ships TWO unnamed frame-shaping locals:
    s32 top_dummy;  Header151B6320 header;  s32 pad_dummy;  Payload151B6320 payload;
The arithmetic says they are not locals at all: 4 + 0x1C + 4 + 0x2C equals header 0x1C + payload
0x30 with SIX bytes of trailing pad in the header rather than two. So `Header151B6320` has 6 bytes
of trailing padding and `Payload151B6320` is 0x30, not 0x2C - and with the structs spelled correctly
both dummies disappear.

**THIS PROJECT'S OWN RULE SAYS AN UNNAMED FRAME-SHAPING LOCAL IS AN OPEN QUESTION, NOT A MATCH**, and
a survey found SEVEN of them live in shipped, ROM-gated code across SIX TUs:
    game_1CA420.c:171  game_1D0840.c:137  game_1E37D0.c:63,65
    game_1FA770.c:192  game_204660.c:185 (s32 pad_dummy[2])  game_E1280.c:48
The bytes are correct, so this is debt rather than a fake match - but each one encodes a WRONG
STRUCT SIZE that will cost every future function touching the same type. Fix the struct, re-verify
byte-identical, re-gate.

# ================================================================================
# WAVE 38: ZERO CLOSED, TWO STRONG BAILS, TWO REAL ADVANCES
# ================================================================================

func_150FF840 @5    - as1 peephole, mechanism fully explained above. Bailed per the peephole rule
                      after five honest variants left it at 5 or worse.
func_150FF2D4 @325  - one instruction short. Golden's instruction ORDER is the WORSE one by critical
                      path (it puts `lw a2` immediately before its use), so it is NOT reachable by
                      reordering the source; plus golden TAIL-DUPLICATES a `lui` (34.0f) into a
                      delay slot, splitting an li.s macro across a merge. The C is positively
                      CONFIRMED correct by a load asymmetry: golden loads arg5->unk0 once but
                      arg5->unk8 twice, which is exactly the no-local-copies form - a
                      `f32 dz = arg5->unk8;` local would be WRONG.
func_150FF6E0 @180  - allocation is a ROUND-ROBIN over t0..t9 that SKIPS LIVE REGISTERS, and golden
                      burns one extra slot on a web that emits no instruction. Two whole families of
                      explanation are now dead: no extra auto can exist (a dedicated `s32 ret;`
                      moves the frame 0x88 -> 0x90 and every home offset), and no extra folded MASK
                      exists (building with the u8 RNG declaration is byte-identical at 180).
func_151B7328 668 -> 279  - after a declaration-order win EVERY aggregate sits at golden's exact
                      offset; one surplus 8-byte compiler-temp slot remains.
func_150F64DC 0 -> 120 on a COLD start - two reordering penalties (60 each), frame exact, every
                      register identical, every instruction present.

A REFUSAL WORTH RECORDING: on func_150FF6E0 a variant scored 185 and hit golden's EXACT SIZE (352 B)
by reusing `which` as the return value. It was REFUSED - it buys the byte count with a `move v0,v1`
that golden does not contain. Matching the size is not matching the code.

STEP ZERO PAID AGAIN, AND HARDER: func_150DFEFC (game_10CD70.c) is a matched sibling of the cold
target with the same emitter shape, the same early-outs, the same timer idiom, the same 11-argument
call and the same `s8 count; do{}while(count>0)` loop. Reusing its declaration list VERBATIM gave a
byte-exact frame on BUILD #1, at score 140 out of a possible ~22,000. Cost: fifteen minutes of
grepping. Mine the corpus before writing anything.

# ================================================================================
# THE ACTOR-ARRAY UNLOCK: STRENGTH REDUCTION FIRES ON A LOCAL, NOT ON A MEMORY LOAD
# ================================================================================

**This is the widest-reaching law found this session. 268 still-stubbed functions reference
D_800CC2D0**, the actor array, whose stride is 812 == 0x32C. Every one of them multiplies an index
by 812 somewhere, and every one of them can be got wrong in exactly the way below.

    arg0->field_0x10 * 812        (u8 load)   -> li t0,0x32c ; multu ; mflo
    s32 i = arg0->field_0x10;  i * 812        -> IDO's 9-instruction sll/subu/addu chain
                                                 (4x-x, *4+x, *4-x, *4-x, *4  ==  812x)

C integer promotion makes those two expressions IDENTICAL in meaning. IDO's strength reducer simply
refuses to fire when the multiplicand is a MEMORY LOAD, and fires when it is a LOCAL. Cross-checked
against the already-matched func_151557FC in the same TU, which multiplies an s32 parameter and does
emit the chain.
**SO: if golden shows the sll/subu/addu ladder, hoist the index into a local. If golden shows
`multu`, feed the field load directly.** Reading which form golden used tells you whether the
original source had an index variable.

## Its companion: TWO SPELLINGS OF THE SAME ADDRESS KEEP A POINTER LOCAL ALIVE ACROSS A SWITCH
Golden computed `obj` once before a switch (spilling it to its OWN home) and then RE-COMPUTED the
identical `base + 812*i` four more times for the `.unk31C` member loads. Written the same way in C,
IDO unifies all five, DELETES the entry computation and rematerialises the pointer in every arm.
The fix is to spell the two uses DIFFERENTLY:
    pointer:      &D_800CC2D0[arg0->field_0x10]     (raw field index)
    member loads:  D_800CC2D0[i].unk31C             (local index)
Worth **6370 -> 1960**, and the frame snapped from 0x58 to golden's 0x50 in the same build.
**IMPORTANT NEGATIVE:** making them differ in any OTHER way is strictly worse - a byte-pointer cast
on either side, `D_800CC2D0 + i`, and `*(T**)((u8*)base + i*812 + 0x31C)` all scored 8740 with frame
0x60. This REFINES the earlier "2-D subscript vs pointer cursor" entry: **the distinguishing axis is
raw-field-vs-local INDEX, not the addressing syntax.**

# ================================================================================
# HOW TO READ A TERNARY OFF GOLDEN: THE REDUNDANT BRANCH TO THE NEXT LABEL
# ================================================================================

    id = (p != NULL) ? p->f : 0;   ->  move v0,zero / beqz / nop / b <next label> / lbu
    id = 0; if (p != NULL) id = p->f;   ->  beqzl + a duplicated successor instruction

**A `b` whose target is the immediately-following label is the SIGNATURE OF A TERNARY** - it is the
ternary's empty join block. When you see one in golden, write a ternary; when you see `beqzl` plus a
duplicate, you wrote a ternary where golden had an if. Worth 6370 -> 2405 on its own.

# ================================================================================
# SPLITTING `t = a->field - GLOBAL;` INTO TWO STATEMENTS IS A REAL LEVER
# ================================================================================

    one statement:   lw <global> ; lh <field> ; subu v0,tX,tY
    two statements:  lh v0,0xe(s0) ; lw t7,0(v1) ; subu v0,v0,t7
Split into `t = a->field; t -= GLOBAL;` the field load goes **straight into the result register** and
the operand order follows source order. One edit applied at two sites took a function 1460 -> 400.
GENERALISATION: when golden's binary op writes its result into the register that already held one
operand, that operand was loaded by a SEPARATE STATEMENT.

# ================================================================================
# SEVEN UNNAMED FRAME-SHAPING LOCALS: SIX REMOVED, ONE HONESTLY UNEXPLAINED
# ================================================================================

ROOT CAUSE - one type, five wrong copies. func_15147A80 is itself decompiled (game_174BF0.c:169)
and does `memcpy((u8 *)temp_v0 + 0x10, arg0, 0x1C)` - it reads **0x1C** bytes from the header. Five
callers declared that header as 0x18 and made up the 4-byte difference with a dummy local.
Corroborated twice independently: game_105FC0.c already spells the same type correctly (with
`u8 pad16[2]; s32 unk18;` and no dummy), and func_151D7830 already declares `s32 unk18` and writes
it. NOTE the callee's `arg2` is NOT the header size - it varies (0x18/0x1C/0x24/0x60), so it is a
stride; that was checked rather than assumed.

**PLACEMENT LAW: the dummy sits IMMEDIATELY ABOVE the struct it belongs to.** First-declared ==
highest address, so a local declared just before an aggregate is that aggregate's TRAILING PADDING.
All five fixed sites match that shape.

**THE ONE LEFT IN PLACE, and why leaving it is the right answer.** game_204660.c's `s32 pad_dummy[2]`
is the only site where the dummy is declared LAST - i.e. BELOW every aggregate - so no struct exists
for it to belong to. Ruled out with evidence: both aggregates are proven exactly 0x1C (by
func_15147A80's own memcpy and by their member offsets); leading padding is impossible because
golden pins both bases with `addiu a0,sp,0x4C` / `addiu a1,sp,0x68`; trailing padding is impossible
by the placement law. It is compiler-TEMP space at sp+[0x44,0x4C), dead in our object. Measured with
a FIRING CONTROL: deleting it gives frame 0x80 and breaks the match, while a 4-byte `s32 pad_dummy`
gives frame 0x88 with .text BYTE-IDENTICAL - so the true shortfall is 4 bytes, not 8. Left as-is and
documented in a code comment.
ACCEPTANCE TEST APPLIED THROUGHOUT: all six TUs byte-identical before and after (.text/.rodata/.data),
verified independently on a clean rebuild, and a baseline compare was run BEFORE any edit so the
post-patch pass could not be a pre-existing one.

## CRLF is worse than recorded: TWO of those six TUs are CRLF
game_1E37D0.c AND game_204660.c. The safe pattern that worked: a bytes-mode patcher that detects the
file's EOL, converts LF-authored patterns to it, asserts each pattern occurs EXACTLY ONCE, and
post-asserts that no dummy survived. Resulting diff: 7 changed lines, zero line-ending churn.

# ================================================================================
# AUDIT FINDING: BANNED CONSTRUCTS ARE LIVE IN SHIPPED CODE
# ================================================================================

Surveying for the dummies turned up more. In live C, EXCLUDING libultra:
  * **61 `volatile` occurrences in game/init code** (libultra has only 2, and those are legitimate
    hardware-register access). Game-code examples are the classic pin form:
    `*(volatile f32 *)&arg0->unk38 = arg0->unk38 + temp_f0;`
  * **`do { } while (0)` wrappers**, including EMPTY ones (game_1D43B0.c:52, and one sitting
    unreachable between switch cases in game_16EE20.c).
This project's rules ban `volatile`-to-pin and empty `do {} while` for NEW work; these predate the
current pipeline and are byte-perfect and ROM-gated, so they are DEBT, not fake matches shipped
knowingly. They still matter: each is an unresolved question about what the original source said.
**Handle them the way the dummies were handled** - find the honest spelling, accept ONLY a
byte-identical result, and where no honest spelling exists, document it in place rather than
silently reverting a shipped match. Do not delete a working match to satisfy a lint.

# ================================================================================
# WAVE 39 NEAR-MISS STATE
# ================================================================================

func_1515589C  COLD -> 400 in 10 builds (first build 9459). Every one of ~278 instructions and every
    register matches except a 2-instruction tail: golden fills a delay slot from the TARGET, ours
    from the PRECEDING instruction, absorbing an mfc1 hazard nop. Golden itself uses the
    steal-the-preceding form at a byte-identical case-3 arm, so the two arms saw different input;
    the only structural asymmetry is that case 1's arm is at switch-body top level while case 3's is
    nested inside an `else`.
func_150F64DC  still 120 (two reordering penalties). Count spelling is now exhausted, including
    `% 2U`. Two corrections to earlier notes: conker/Makefile:146-149 documents IDO ITSELF
    scheduling at -g3, so this is a ugen ucode-shape lever rather than an as1 hazard; and the
    supposed ground-truth sibling func_150DFEFC does NOT actually contain the adjacency in question.
func_151B7328  still 279. Part 1 did NOT hand over the answer (this function defines its own header
    type, already 0x1C). DECISIVE NEGATIVE: a build-up ladder of nine probe functions with identical
    locals and the same 11-arg call - each adding one construct, then all combined - ALL produced
    frame 0x80 with TEMP == 0. With three waves of removal probes that never got below 0x108, the
    STATEMENT LEVEL IS NOW RULED OUT IN BOTH DIRECTIONS. The 8-byte reserve is a register-pressure
    artefact of the whole 233-instruction body, not any construct. Next step is pressure reduction
    or the permuter, not construct enumeration.
    Also measured: the known-wrong u8 RNG declaration is NOT a lever here (byte-identical at 279).

# ================================================================================
# expected/ IS NOT THE AUTHORITY. THE ROM GATE IS. AND expected/ HAS DRIFTED.
# ================================================================================

Wave 40 produced a scare that every future wave will hit, so the adjudication procedure is
recorded here.

**THE SYMPTOM.** After closing func_151E9D18, `-o func_151E9D18` scored **10**, not 0, and the
whole-object `.text` compare said DIFFERS.

**THE ADJUDICATION, in this order:**
 1. **Compare EVERY symbol separately, not the whole section.** The per-symbol compare showed
    `1 symbol differs out of 40`, and it was **func_151EA15C** - a DIFFERENT function, already
    matched and live C. func_151E9D18 itself was byte-identical.
 2. The score of 10 was therefore the UNBOUNDED-WINDOW TRAP biting the verification step: the
    16,384-byte window from func_151E9D18's start swept into func_151EA15C's drifted byte.
 3. **Run the ROM gate.** Inner sha1 `842e3d34...` PASSED with the change live. The ROM is the
    ground truth; if the linked image is byte-perfect then every function in it is byte-perfect.

**CONCLUSION: the `expected/` object was the stale party, not our source.** The differing byte is a
relocation addend (`addiu s0,s0,4` vs `addiu s0,s0,0`) inside a function this wave never touched.

**CORROBORATION FROM THE FILESYSTEM, worth checking whenever this recurs:** `expected/` is a static
golden snapshot, not regenerated as work proceeds - **462 of 464 objects are dated 2026-08-09**, and
`game_215960.c.o` is one of only **TWO** dated 08-10. An object with an anomalous date is the
signature of the known drift bug (stub_expand.py copying without deleting), not of normal work.

**RULE.** `expected/` is a fast convenience reference and it can be WRONG. When a whole-object
compare disagrees with a clean ROM gate, believe the gate. Never revert a match on the strength of
an `expected/` diff alone: first compare per-symbol to find WHICH function differs, and if it is not
the one you edited, check the object's date and gate the ROM.

# ================================================================================
# THE ACTOR-ARRAY LAW HAS A SECOND HALF: `div` BY 0x32C IS A POINTER DIFFERENCE
# ================================================================================

Wave 40 was planned around the prediction that these targets would show `base + 812*i`. **Both
targets went the OTHER WAY and the prediction was wrong.** They RECOVER AN INDEX FROM A POINTER:

    subu a3, ptr, &D_800CC2D0 ; addiu at, zero, 0x32C ; div zero, a3, at ; mflo a3

In C that is simply `ptr - D_800CC2D0` on a `struct127 *`. **A `div` by 0x32C is the signature of a
POINTER DIFFERENCE and needs no index local at all** - `D_800C3E78 = actor - D_800CC2D0;` (the
game_49D30.c idiom) reproduces it verbatim. Note also that a lone `multu` near actor code may be
unrelated to the array entirely: func_151DF1BC's was `D_800E0A94 * alpha`, an alpha blend.

So the full reading of golden is a three-way decision, not a two-way one:
    sll/subu/addu ladder  -> index was a LOCAL, multiplied
    li 0x32C ; multu      -> index was a RAW FIELD LOAD, multiplied
    div by 0x32C          -> there is no index; the source subtracted two POINTERS

## AMENDMENT: the ladder also fires on a u8 field load
The first statement of Law 1 ("reduction refuses on a memory load") is too strong. A caller
(func_15186794) does `lbu t8,0x124(a0)` and then emits the identical 9-instruction ladder. The
reliable half of the law is the READING DIRECTION - decide from golden which of the three forms to
write - not a claim about what IDO will refuse.

# ================================================================================
# TWO CACHES OF ONE FIELD ARE HONEST SOURCE, AND YOU CANNOT FAKE THEM WITH A COPY
# ================================================================================

func_151D4DAC's golden has one `lbu v0,0x1ca` plus `move v1,v0`, with v1 feeding a `>= 3` test and
v0 feeding a `- 1`. Measured:

    one local                       30   (five register-only lines)
    hp2 = hp;      (the copy)      650
    hp2 = arg0->health;  (2nd read)  0

**IDO's CSE turns the SECOND READ of the same field into the register copy.** So a redundant-looking
pair of caches of one field is the HONEST reading of the machine code, not a register-shuffling
trick - and the two locals must be initialised INDEPENDENTLY FROM THE FIELD, never from each other.
This is the constructive converse of the fake-match rules: writing literally what the asm does
(`hp2 = hp;`) is the WRONG answer; writing what the source must have said is the right one.

# ================================================================================
# A NARROWING CAST GETS FOLDED INTO A CALL ARGUMENT - HOIST IT TO ITS OWN STATEMENT
# ================================================================================

Writing `f(a, b, ((u16)(g(...) * K) - 0x4000) | 1, idx)` made IDO DROP the inner `andi 0xffff`
(because the outer parameter is already u16) AND evaluate the argument list in a different order,
costing an extra `mov.s $f2,$f0`. Hoisting the cast into its own statement - `u16 angle;
angle = g(...) * K;` - restored BOTH `andi`s and golden's evaluation order, and the entire tail
became byte-identical in one build (35 -> 30).
**GENERALISATION: when golden materialises a narrowing cast as its own `andi` rather than folding it
into the call, the cast was a separate ASSIGNMENT in the source.**

# ================================================================================
# FRAME LAW AMENDMENT: ONLY SPILLED LOCALS OCCUPY HOMES, BUT THE COUNT STILL SIZES THE AREA
# ================================================================================

Measured on two functions in the same wave, and it resolves an apparent contradiction with the
existing entry:
 * func_151D4DAC has FOUR declared locals, a 0x28 frame and a SINGLE spill slot at 0x24 - four
   homes would have collided with `ra` at 0x1C.
 * func_151DF1BC has THREE spilled locals and needed a FOURTH DECLARED local to push its homes from
   0x24/0x28/0x2C down to golden's 0x20/0x24/0x28 (worth ~1000 points).
So: **only spilled locals actually occupy home slots, but the home AREA is still sized by the
DECLARED count.** That is why adding a local that never spills can still move every other home.

# ================================================================================
# WAVE 40 RESULT
# ================================================================================

CLOSED:
  func_151E9D18  1092 B  game_215960.c  - HUD two-team score readout: builds the icon display list
      (SETTIMG/SETTILE/LOADBLOCK/SETTILESIZE for a 32b RGBA tile), accumulates two team totals from
      one of three sources depending on the mode flags, caches the pair, draws both icons and prints
      both numbers.
  func_151D4DAC   924 B  game_200930.c  - actor damage/impact dispatcher: fires the impact effect for
      a whitelist of 47 actor ids, decrements or zeroes health, swaps the event code, and reports the
      event with the source actor's array index (or -1).
Verified independently: score 0 (func_151D4DAC, .text IDENTICAL 10768 B, 0 of 55 symbols differ),
per-symbol compare clean for func_151E9D18 with the sole difference in an untouched neighbour, zero
banned constructs in either TU, pragmas 1743 -> 1741, ROM gate passed.

PARKED:
  func_15184FA4 @15 - THREE instructions, register-name only, at the gSPViewport slot. The `Gfx *_g`
      block-locals inside the gbi.h macros are handed out round-robin over {v0,v1,a0,a1,a2,a3};
      golden's first block skips a2 and ours skips a3, and both then wrap to v0 - so it is NOT a
      persistent counter offset. a2 is provably DEAD at that point in golden, so liveness does not
      explain it either. Eleven source variants across two sweeps, EACH WITH A CONTROL THAT FIRED
      (15 -> 20 both times), all returned 15 with the viewport register still a2. Its permuter
      selftest fails check (b2) - round trip changes codegen - so permuter scores would be measured
      on a different source and are not trusted. Structural selector, not reachable from this source.
  func_151DF1BC @3866 - control flow, every constant, every mask and every callee argument list are
      already EXACT across all 238 instructions. The whole residual is a register-vs-memory inversion
      between two locals living across calls: golden keeps `alpha` resident in t0 and `actor` purely
      in memory at 0x20(sp); ours does the opposite.

# ================================================================================
# MEASUREMENT TRAP #6: SPLAT INTERIOR SYMBOLS GIVE A FUNCTION A NONZERO SCORE FLOOR
# ================================================================================

**A function can be CORRECT and still never reach score 0 at object level.** This is new, it is
mechanical, and it is screenable in advance.

## The mechanism, verified from the binary
func_15084558 clears a 187-element array: `for (k=0;k<187;k++) if (D_800D1588[k]==x) D_800D1588[k]=0;`
IDO unrolls it with a 3-iteration FRONT PEEL (187 & 3 == 3) then 46 iterations of 4. The peel
references indices 0..3 as four separate addresses - and because the STILL-ASM version of the
function referenced those addresses, **splat minted them as separate symbols**:

    undefined_syms_auto.txt:7108-7111
      D_800D1588 = 0x800D1588;   D_800D158C = 0x800D158C;
      D_800D1590 = 0x800D1590;   D_800D1594 = 0x800D1594;
    golden .s references: D_800D1588 x6, D_800D158C x4, D_800D1590 x4, D_800D1594 x2

`expected/build/src/game_AEB40.c.o` is built FROM THAT PRAGMA, so it carries **addend-0**
relocations against the invented names. Any C spelling of `D_800D1588[k]` emits R_MIPS_HI16/LO16
against the BASE with addend 4/8/0xC. **o32 relocations are REL, so the addend lives IN THE
INSTRUCTION FIELD** - confirmed by objdump:

    mine      addiu v0,v0,12                      R_MIPS_LO16 D_800D1588
    expected  addiu v0,v0,%lo(D_800D1594)         R_MIPS_LO16 D_800D1594   (addend 0)

The LINKED bytes are IDENTICAL - the linker adds the addend either way - so the ROM stays
byte-perfect. But `cmp` on `.text` can never be clean and the score has a floor of ~6 instructions.
**Such a function is verifiable ONLY by the ROM gate.**
The only way to force addend-0 relocations is to name the three interior symbols and hand-write the
peel - i.e. a manual unroll. That is a fake and was correctly refused.

## THE PRE-FILTER, run it before picking any target with an array loop
tools/splat_interior2.sh: flag any function whose golden .s references a RUN of >= 3 CONSECUTIVE
4-byte-spaced symbols (the unrolled-peel signature; the confirmed case had a run of 4).
**542 stubbed functions carry it**, run lengths 3 to 67:
    run 3: 141   run 4: 111   run 5: 63   run 6: 54   run 7: 40   run 8: 36   ... run 67: 2
CAVEAT, so nobody over-reads this: a run is a RISK INDICATOR, not a verdict. It only bites if your C
would index a base array where golden names the interior slots. Short runs may be genuinely distinct
adjacent scalars. Long runs (>10) are near-certainly arrays.
**AND DO NOT USE THIS AS A LICENCE.** func_15084558 is parked at 3240 with 25 non-register diffs, of
which only ~6 are the artifact. The floor is ~6 instructions, so the artifact explains a residual of
6 - it does not excuse 3240. A function is not "done but unscoreable" until everything except the
floor is gone.

# ================================================================================
# THE ACTOR-INDEX LAW NEEDS A FOURTH CLAUSE: BOTH FORMS CAN APPEAR IN ONE FUNCTION
# ================================================================================

func_15084558 contains the `div` POINTER-DIFFERENCE form AND the sll/subu/addu 812 LADDER, ten
instructions apart: `arg0 - D_800CC2D0` for the self-index test, and `D_800CC2D0[j]` for the scan.
So the brief's rule "if the div is there, declare NO index local" is right about the div and wrong
as a whole-function rule - **you still need the loop index local for the ladder.** Decide per SITE,
not per function.

**NEW, and it cost real points: the div expression must be written INLINE INSIDE THE INNER LOOP.**
    if (j == arg0 - D_800CC2D0) continue;      <- correct
    idx = arg0 - D_800CC2D0;  ... loop ...     <- wrong
Golden computes the difference AFTER the loop's `blez` guard - i.e. IDO hoisted it from inside the
loop into the preheader. Assigning it to a local before the loop puts it BEFORE the `blez` and costs
the match. This is the same family as the which-side-of-a-guard lever: **let IDO do the hoisting;
writing the hoist yourself puts the code in the wrong basic block.**

# ================================================================================
# `lw $at,0(reg)` / `sw $at,off(reg)` PAIRS ARE A STRUCT COPY, NOT SCALAR ASSIGNMENTS
# ================================================================================

**`$at` is never a data register in ordinary C expressions** - IDO reserves it for the assembler and
for compiler-generated BLOCK MOVES. So a run of `lw $at` / `sw $at` pairs is a struct assignment.
In func_151BDD8C six such pairs decode as
    objA->unk34 = sp88[i];   objA->unk40 = sp70[i];
where both sides are 12-byte structs. Writing them as six FIELD assignments would have required the
members to be s32 (lw/sw) while the array is fp - an obvious contradiction, and the giveaway that
the struct-copy reading is the right one.
Add this to the reading rules: **see `$at` as a data register => look for an aggregate assignment.**

# ================================================================================
# WAVE 41: ZERO CLOSED, ONE TRAP FOUND, TWO FUNCTIONS ADVANCED
# ================================================================================

func_151BDD8C  3267 -> 1685. **Frame and every stack offset now match** (0xA8; ra 0x14, p-spill
    0x28, ptr arrays 0x4C/0x5C, vec arrays 0x70/0x88, actor home 0xA0). Residual: 8 instructions
    where golden MATERIALISES a sub-pointer (`addiu v0,a0,0x110`) that IDO folds into the load
    displacement here - proved NOT a spelling issue, since inline cast, declared typed pointer and
    declared s32 all produce BYTE-IDENTICAL output at 1685; the only case that does not fold is when
    the assignment and its uses sit in different basic blocks, which is exactly the case that already
    matches. Plus 4 instructions of scheduling and a systematic one-slot register shift, so the
    12-scalar local set is still not exactly right.
func_15084558  3800 -> 3240, and it is the trap case above. Everything from the prologue through the
    outer-loop preheader is byte-identical INCLUDING both stack slots, the saved-register roles and
    the 812 ladder. Of 25 non-register diffs, ~6 are the splat artifact (unfixable), 4 are a dead
    4x-unrolled counting loop that also walks a pointer, and 4 are a loop-invariant RANKING inversion
    with 9 candidates for 9 saved registers on both sides.

# ================================================================================
# PICKER BUG THAT COST A WHOLE WAVE: A `.s` FILE DOES **NOT** MEAN "STILL STUBBED"
# ================================================================================

Wave 42 fed both agents four functions that were **already decompiled**, and they spent the wave
verifying finished work. The agents caught it and said so plainly; the fault was entirely in the
target picker.

**`asm/nonmatchings/<tu>/<func>.s` FILES ARE RETAINED AFTER A FUNCTION IS DECOMPILED.** Removing the
`#pragma GLOBAL_ASM` does not delete the `.s`. A picker that walks `asm/nonmatchings/` therefore sees
every function that has EVER been stubbed, including all 3,900+ already-matched ones.

**THE AUTHORITATIVE TEST FOR "STILL STUBBED" IS A LIVE `#pragma GLOBAL_ASM` LINE IN
`conker/src/<tu>.c`** - build the candidate set from `src/`, never from the asm directory:

    stubbed = {}
    for c in glob.glob("src/**/*.c", recursive=True):
        for m in re.finditer(r'#pragma\s+GLOBAL_ASM\("([^"]+)"\)', open(c).read()):
            stubbed[os.path.basename(m.group(1))[:-2]] = os.path.basename(c)[:-2]

Cross-check the count against the tree-wide pragma total (`grep -rc GLOBAL_ASM conker/src/`) before
trusting any target list. If the picker's count and the grep count disagree, the picker is wrong.
The same mistake is available in any tool that enumerates work from `asm/` - check them all.

# ================================================================================
# TRAP #6 CONFIRMED INDEPENDENTLY, AND IT HAS A NAME: THE RELOCATION-NAMING FLOOR
# ================================================================================

A second, cleaner case turned up by accident, and it is the strongest possible demonstration
because the function is **already shipped and ROM-verified**.

`func_151E24F0` (game_20AE20.c, live C since commit 65645c7, inside a ROM that gates byte-perfect)
scores **10**. Exactly ONE byte differs across the entire 43,840-byte `.text` of its object:

    built     4c04: 3c0b0000  lui   t3,0x0        R_MIPS_HI16 D_8008FE44
              4c08: 256b0004  addiu t3,t3,4       R_MIPS_LO16 D_8008FE44   (addend 4, in-field)
    expected  4c04: 3c0b0000  lui   t3,0x0        R_MIPS_HI16 D_8008FE48
              4c08: 256b0000  addiu t3,t3,0       R_MIPS_LO16 D_8008FE48   (addend 0)

**The `lui` words are IDENTICAL (0x3c0b0000); only the relocation's SYMBOL NAME differs, and
asm-differ scores that too.** Both resolve to 0x8008FE48, and the linked word is 0x256bfe48 - exactly
the golden encoding in the .s comment.

The construct is IDO's strength-reduced loop-end pointer for `for (i = 0; i < 4; i++) v = D_8008FE44[i];`
(the `sltu` proves an unsigned pointer compare). **`D_8008FE48` is not a real variable:**
asm/data/234900.rodata.s holds ONE contiguous initialised run spanning 0x8008FE44-0x8008FE54 which
splat chopped into labels at FE44 (1 byte), FE45 (3), FE48 (12) and FE54 - and the function itself
indexes `D_8008FE44[j]` for j up to 16, proving a single array.

Reaching 0 would require declaring a fictitious `extern s8 D_8008FE48[]` and writing `p < D_8008FE48`
- inventing an array boundary the source never had. **Correctly REFUSED** under "refuse a better
score that makes the output less like golden": the output is already exactly golden.

## Consequences, and one of them affects the verification protocol
* **A SHIPPED, CORRECT FUNCTION CAN SCORE NONZERO.** Score != 0 is not evidence of a defect for
  code that is already live. Check whether the residual is entirely relocation-naming before
  treating it as a regression.
* **THE "ALL SIBLINGS STILL 0" CHECK WILL FLAG THESE AS FALSE POSITIVES.** When a sibling scores
  nonzero, diff it: if every differing row is a `%hi`/`%lo` pair whose instruction WORDS match and
  only the reloc symbol name differs, it is the floor, not a regression.
* Add it as a residual class in its own right: **RELOCATION-NAMING FLOOR**, distinct from
  ALLOCATION / SCHEDULING / BASIC BLOCK / as1 PEEPHOLE. Such a function is verifiable only by the
  ROM gate - which is, as ever, the authority.

# ================================================================================
# WAVE 42: ZERO NEW FUNCTIONS, TWO USEFUL CONFIRMATIONS
# ================================================================================

Nothing was closed and nothing in the repository was modified. The three functions reported as
"closed" (func_15015A38, func_15023DE0, func_1500AF08) were all already live C from commits 65645c7
and b401477; the agents verified rather than re-derived them, and said so explicitly.

What the wave is actually worth:
 1. the picker bug above, now fixed - it would have silently poisoned every future wave;
 2. the relocation-naming floor, proved from the binary on a shipped function;
 3. an incidental confirmation that the screened-clean pool is real: with zero callees and zero
    float, three of the four targets had genuinely nothing left to get wrong, which is why they were
    already finished.

## Reconciling the stubbed-function count (do this whenever a tool disagrees with grep)
`grep -rc GLOBAL_ASM conker/src/ --include=*.c` gives 1741, but only **1737** are live
`#pragma GLOBAL_ASM("...s")` lines. The other four are: one `#pragma GLOBAL_ASM_DISABLED`
(game_18D770.c:176, func_151606A8 - deliberately NOT stubbed), two comments that merely mention
the macro, and one commented-out pragma (init_B1B0.c:687).
**PLUS a mechanism the pragma scan cannot see:** game_DAFA0.c:57 uses asm-processor's INLINE
`GLOBAL_ASM(` block form, with the assembly written directly in the C file and no `.s` reference at
all (func_150AE280). There is exactly ONE of these in the tree.
So the true count of still-stubbed functions is **1738**. Any tool that enumerates remaining work
must handle both forms, and its total should be reconciled against the grep before use.

# ================================================================================
# SCREEN FOR HAND-WRITTEN ASSEMBLY FIRST -- SPLAT ALREADY TAGS IT, AND 29 ARE LIVE
# ================================================================================

Half a wave went into a function that is **not compiler output at all**. splat says so on line 1
of the .s (`/* Handwritten function */`) and the picker never looked.

    $ grep -rl 'Handwritten function' conker/asm/nonmatchings/ | wc -l   -> 29 (all still stubbed)

Concentrated where the cookbook already warned the hand-written math lives: game_D4450 (6),
game_225D20 (5), game_D86A0 (4), game_D0F20 (3), game_D3040 (2), plus singles in game_DAE10/
DAE50/DAFA0/DF260/D5650.

## The seven signatures, from func_150A3FC4
Any ONE of these is decisive; this function had all seven.
 1. `/* Handwritten function */` on line 1, and `/* handwritten instruction */` per-instruction.
 2. **No prologue or epilogue** - never touches `$sp` - yet it clobbers callee-saved
    `$s5/$s6/$s7/$fp`.
 3. It "saves" those integer registers **into FLOATING-POINT registers**:
    `mtc1 $s5,$f1` ... later `mfc1 $s5,$f1`. No C compiler emits that.
 4. It **branches backwards INTO THE PREVIOUS FUNCTION**: `beqz $t0,.L150A3FBC`, where
    0x150A3FBC is eight bytes *before* its own entry at 0x150A3FC4 - it is the trailing `jr $ra`
    of func_150A3A70.
 5. **Interior glabels** (func_150A40A8, func_150A411C) that other code jumps into.
 6. Trapping `sub` rather than `subu`.
 7. 64-bit `ldl`/`ldr` in a `-mips2 -o32` build; and callee-saved registers READ BEFORE ANY
    DEFINITION (extra arguments passed in `$s5/$s6/$s7/$fp`), plus a 5th argument read at
    `lw $v0,0x10($sp)` with no frame allocated.

**THE LESSON ABOUT SCREENING, not just about this function:** every screen the picker applied
(no jtbl, no interior-symbol run, no pooled float, mid-band, unattempted) was TRUE and ALL of them
were IRRELEVANT, because none tested whether the thing was C. A clean screen result is not evidence
of tractability if the screens do not cover the failure mode. Ask what a screen set does NOT test.

# ================================================================================
# AN AGENT REFUSED ITS OWN BEST SCORE, AND THAT IS THE RIGHT CALL
# ================================================================================

func_15167E0C reached **685** (from 885), with structure byte-exact: same instruction count, same
addresses, same branch forms, frame 0x20, ~160 of 195 instructions identical *including register
names*. It was flagged NOT SHIPPABLE by the agent that produced it:

> the 685 uses one packed variable for the Y and X axes and a second for Z, a split with no
> semantic justification chosen purely for its register effect - not shippable as-is even at 0.
> The honest single-variable shape scores 860.

That is exactly the standard: **a variable split chosen for its register effect rather than its
meaning is a forcer, even when it is not on the banned-construct list.** Score 0 would not have
made it shippable.

The residual is a genuine allocation wall, and it is well-characterised: golden spends TWO pool
registers on the packed 24.8 value and ZERO on the sum; the honest C spends one on each. Golden's
packed-Y and packed-X live ranges OVERLAP (packed-X is built before packed-Y is consumed), which is
what forces the second pool register and evicts the sum. Writing that overlap into the source DOES
flip the register class correctly - verified by dumping the diff - but IDO then picks a1/a2 instead
of v0/v1, which displaces another local out of a3 and re-registers the whole function. **The
pool-assignment ORDER is not steerable from C.**

# ================================================================================
# PICKER: A SCREEN I TRIED AND REJECTED, RECORDED SO NOBODY RE-ADDS IT
# ================================================================================

func_15167E0C was NOT unattempted: its TU already carried a parked 885 reconstruction **in a comment
block inside the .c file**, not in tools/nearmiss/. The obvious screen - "skip if the function name
occurs more than once in src/<tu>.c" - was implemented, measured, and **REVERTED**: it discarded
**424 of ~550** candidates, because the second occurrence is almost always a forward declaration or
a same-file caller. Catching a handful of notes is not worth losing three quarters of the pool.
The agent brief now tells agents to grep their own TU for an existing note instead.
Current screen tally: parked 113, handwritten 29, size 1304, jtbl 15, splat floor 125 -> **149
candidates surviving**.

# ================================================================================
# WAVE 43 RESULT
# ================================================================================

CLOSED: func_15125DB4, 900 B, game_14FF90.c - the per-frame player control-mask gate. It seeds the
paired 16-bit enable masks from the animation state, then progressively clears mask bits through a
long chain of state and flag tests, and finally decrements a timer and clamps it at zero.
Verified independently: score 0 with and without -R, **all 56 siblings in the TU still 0**, .text
IDENTICAL (23,808 bytes), .rodata/.data/.bss identical, symbol size 900 both sides, zero banned
constructs, grep GLOBAL_ASM 1741 -> 1740, and the full clean ROM gate passed on both sha1s.

Notable: this is the function whose golden supplied the corpus evidence for the mask third-use law
(`andi 0xFFEF / andi 0xFFEF / addiu -0x11`). Knowing in advance that it masks with the same constant
at least three times - and that all sites must be spelled identically - was handed to the agent in
the brief and is the kind of pre-loaded fact that makes a cold start cheap.

# ================================================================================
# A WRONG-HEADER WORKAROUND WAS COSTING MATCHES, AND IT IS A SYSTEMIC UNLOCK
# ================================================================================

func_151438D8 was parked at 20 with the note *"residual = ALLOCATION, 4 instructions"*.
**It was not allocation.** It was the spelling used to reach a mis-declared global, and the fix
took it **20 -> 0**.

variables.h declares `extern struct178 D_800D3098[73]`, but the symbol actually holds a **POINTER**.
Twelve live TUs work around that with the cast-through-address idiom `*(s32 *) &D_800D3098`. The
parked reconstruction copied the idiom. Replacing it with the sanctioned file-local shadow closed
the function:

    #define D_800D3098 D_800D3098_array_decl_in_variables_h
    #include "variables.h"
    #undef D_800D3098
    extern ObjRec *D_800D3098;

**THE RULE, and it explains why only 2 of 13 sites diverged:**
`((T *) *(s32 *) &SYM)` makes IDO evaluate **base-then-offset**; a plain `extern T *SYM` evaluates
**offset-then-base** wherever the address is produced as a VALUE (`&TBL[i]` assigned to something).
At load-BASE sites the two are identical, which is why eleven sites matched either way and only the
two `result = &OBJTBL[i];` sites differed:

    golden  lw t6,0(a2) / mflo t8 / addu t0,t8,t6
    cast    lw t8,0(a2) / mflo t6 / addu t0,t8,t6      <- same `addu` WORD, operands swapped

Both spellings were built in the same tree to prove it (20 vs 0).

## The corollary is the important half: A PARKED RESIDUAL CLASSIFICATION CAN BE WRONG
The earlier note read the swapped `lw`/`mflo` destinations as register allocation *because the
`addu` instruction word was byte-identical in both builds*. That reasoning is seductive and wrong.
**When two operands land in the same two registers but SWAPPED, suspect the SOURCE OPERAND ORDER of
the expression, not the allocator.** A misclassification does not merely fail to close a function —
it pins it in the backlog under a label that discourages anyone from re-opening it.

## FIVE PARKED NEAR-MISSES USE THE SAME IDIOM AND SHOULD BE RE-CHECKED WITH THE SHADOW FIRST
    func_15162B28   parked @1      <- in the "<=20 unreachable allocation tie" cluster
    func_150A09D0   parked @20     <- same cluster
    func_150144B8   parked @207
    func_150FA1B8   parked @1695
    func_15010880   parked (score not recorded)
The idiom reaches five distinct symbols across twelve live TUs: D_8002BD10, D_800A66B4,
D_800BE9F4, D_800D3098, D_800DC2B0.
**This matters most for the <=20 cluster**, which this file already describes as a terminal
"the allocation is internal, there is nothing in the source to change" state. Two of its members
reach a global through this idiom, so at least those two deserve one build with the shadow before
that verdict stands.

# ================================================================================
# IDO HOMES A LOCAL ONLY IF IT SURVIVES uopt -- SINGLE-DEF SINGLE-USE IS DEMOTED
# ================================================================================

A refinement of the frame law with a real cost attached. In func_1508BC20, `step = 0xAA / n;` read
once per loop iteration is FORWARD-SUBSTITUTED away: the div block SINKS into the loop preheader and
the quotient lands in a compiler TEMP (0x48) instead of `step`'s own home (0x6C, declaration ordinal
7). Rewriting the same value as a MULTI-DEF variable —

    n = count >> 1;  if (n < 2) n = 2;  n = 0xAA / n;

— makes IDO keep it: the store lands in home ordinal 7, the div stops sinking, and the loop guard
becomes `blezl s3,<epilogue>` with `lw ra` annulled in the delay slot. **Three separate divergences
fixed by one change.**
THE CATCH, measured: IDO then ENREGISTERS it in `$a0` (caller-saved), adding `mflo a0` after the trap
checks plus a redundant load/move/spill per iteration, where golden never enregisters it at all. No
honest spelling got both, so 785 (single-def, right allocation, wrong block order) beat 1113
(multi-def, right block order, wrong allocation). **A frame home that refuses to appear may mean the
variable is being optimised out of existence, not that the declaration list is wrong.**

# ================================================================================
# `return <var>` VS `break` DECIDES WHETHER A SPILLED RESULT IS CONSTANT-PROPAGATED
# ================================================================================

Worth **685 -> 70** on func_15084044, from one keyword. The allocation-failure path sets a result
and leaves the loop. Written as `return ret;` at that point, IDO folds it to `li v0,1` and jumps to
a private tail. Golden instead stores `sw t3,0x48(sp)` in a branch delay slot and falls into the
common `lw v0,0x48(sp)` tail — i.e. **the source `break`s out of the loop** so several values reach
a single return and the constant cannot be propagated.
GENERAL FORM: if golden spills a result and falls into ONE shared return, the source has one exit
and `break`s to it. If golden folds a constant into `li v0,K` with its own tail, the source returned
early at that point.

# ================================================================================
# IDO REVERSES COMPARISON OPERANDS -- BUT NOT UNIFORMLY (rs IS THE SECOND OPERAND)
# ================================================================================

Golden: `lw t6,0x64(sp); lw t8,0x10(s0); lw t7,8(t6); bnel t7,t8`.
Written `mesg->dramAddr == node->unk10` the three loads land in the same registers but the branch is
`bnel t6,t8`; written `node->unk10 == mesg->dramAddr` **all four instructions match**. So `rs` is the
SECOND source operand.
**CAVEAT, measured in the same wave:** the identical rewrite on func_15084044 changed nothing
(70 -> 70). The normalisation reverses a compare of TWO FIELD READS but not one where an operand is
already a live register. Do not treat it as unconditional.

# ================================================================================
# TWO AGENT CLAIMS I CHECKED AND ONE WAS FALSE
# ================================================================================

* **FALSE:** "expected/build/src/ held only THREE objects for the whole repo." Verified directly:
  **464** objects present, all of the wave's TUs among them, with the usual 462-at-2026-08-09 /
  2-at-08-10 split. The agent was almost certainly looking at its own private scorer directory
  (a symlinked tree with its own build/), not conker/expected/. **Not a real trap — do not act on
  it.** A private scorer needs its expected/ seeded; the repo's does not.
* **TRUE and already known:** `-o <func>` is not bounded by the symbol. One agent's first reading of
  685 was taken over a 16 KB window running through four later functions.
* **TRUE:** a stale object silently scores. One agent's first verification of the closed function
  read 20 against a STALE object; a forced rebuild gave 0. Always `rm` the object first.

# ================================================================================
# WAVE 44 RESULT
# ================================================================================

CLOSED: func_151438D8, 1088 B, game_16EE20.c — a masked linear search over the 0x34-stride global
object table. It takes an index range BY ADDRESS (the callee clamps both ends in place), a u16
field-selector mask and a key record; for each of eleven selectable field groups it accumulates a
"checked" and a "matched" mask, with selector bit 0x1000 switching the accept test from any-match to
all-match, and returns the LAST accepted record or NULL.
Verified independently: score 0 with and without -R, **all 75 siblings in the TU still 0**, .text
IDENTICAL (20,256 bytes), .rodata/.data/.bss identical, symbol size 1088 both sides, and **this
wave's diff adds ZERO banned constructs** (the TU's pre-existing self-assignment at line 496 and
`do{}while(0)` at line 1298 are already inventoried in tools/FAKEMATCH_AUDIT.md).
A relocation-TABLE-POSITION difference was checked and dismissed: identical relocation SET at
identical offsets, ordered differently because the golden object got them from an appended
GLOBAL_ASM block rather than inline C. Table position does not affect linking.

PARKED: func_1508BC20 @785 (basic-block + allocation, both families documented with scores),
func_15084044 @70 (one CSE register substitution: golden holds it in $a3, ours in $v0),
func_1000A03C @2570 (frame now exactly 0x78 with all three observable offsets matching).

# ================================================================================
# THE MIS-DECLARED-GLOBAL UNLOCK: CONFIRMED, SCOPED, AND ONE OF ITS TARGETS CLOSED
# ================================================================================

Wave 45 tested last wave's hypothesis on four parked near-misses. **Scorecard: one closed, two
clean negatives, one brief that was factually wrong.** The law survives, but with a precise limit.

## CONFIRMED: func_150A09D0, 20 -> 0 in ONE build, from the spelling alone
This was a member of the "<= 20 unreachable allocation tie" cluster that this file calls a terminal
state. Its recorded residual was two `addu`s in `jal` delay slots emitted as (base, induction) where
golden has (induction, base) — and eleven pointer spellings had all canonicalised the same way.
**It really was not allocation.** The two divergent sites are exactly the two that pass
`&D_800D3098[i]` as a VALUE; the eleven load-BASE sites in the same function were identical under
either spelling. That is why it sat at 20 for so long: 11 of 13 sites agreed.

## THE LIMIT, measured: THE LAW NEEDS A RUNTIME INDEX
On func_15010880 the shadow moved nothing (210 -> 210, a clean negative recorded as instructed).
The reason is exact: its value sites use CONSTANT indices —
    0xEA0 = 72 * 0x34   ->  &D_800D3098[72]
    0xED4 = 73 * 0x34   ->  &D_800D3098[73]
and a constant index folds to a single `addiu rD,base,K`, so base-then-offset and offset-then-base
are **BIT-IDENTICAL**. Four spelling variants all scored 210.
**RULE: the operand-order law only bites where the index is a RUNTIME value.** With a constant
index, do not bother.
(Incidental proof the declaration really is wrong: index **73** is one PAST the declared
`struct178 D_800D3098[73]`.)

## THE CHEAPEST TEST, and it needs no build: LOOK FOR AN IN-FUNCTION CONTROL
func_150A09D0 touches TWO pointer globals. `D_800DBFF0` is CORRECTLY declared in variables.h as
`extern struct108 *D_800DBFF0;`, and its address-as-value site was ALREADY emitting golden's operand
order (`addu v0,a0,t3`) back at score 20. `D_800D3098` is mis-declared as an array, and its value
sites emitted the reverse. **Same construct, two declarations, opposite operand order, inside one
function.** So when a near-miss shows swapped `addu` operands, find a correctly-declared pointer
global elsewhere in the SAME function and compare — that tells you which spelling is right before
you build anything.

## THE SHADOW IS SAFE TU-WIDE, PROVED BY BYTES NOT ARGUMENT
game_CDE80.c has ELEVEN other `D_800D3098` users that keep the `*(s32 *)&D_800D3098` cast idiom.
The shadow does not disturb them, because `&SYM` is the symbol address under either declared type
and the cast overrides the type anyway — confirmed by the whole-.text byte compare, with all 19
siblings still scoring 0. The pattern is now live in two TUs (game_16EE20.c, game_CDE80.c) and
should be the DEFAULT fix for a mis-declared global, not a last resort.

# ================================================================================
# NEW LAW: READING THE SAME f32 GLOBAL TWICE IN ONE FUNCTION COSTS 8 FRAME BYTES
# ================================================================================

This is the whole of func_150144B8's residual of 207 — a function with **ZERO instruction
differences**, where the entire score is one 8-byte frame delta making all 22 sp-relative offsets
read 8 too high (`addiu sp,sp,-0xc8` vs golden's `-0xc0`; no 'r' rows, no inserts, no deletes).

IDO CSEs two `lwc1 %lo(G)(at)` of the same global into one live value and gives that CSE a **HOMED
compiler temp**. Measured on the standalone compiler:
    two reads of D_80096688                              -> frame 200
    either read removed, or the second pointed elsewhere -> frame 192
**It is the READ, not the arithmetic** — two bare assignments `tmp.unk1C = G; tmp.unk20 = G;` still
cost the 8. **It does not accumulate**: three or four such reads still cost exactly 8.
**THE CONTRAST MATTERS:** an IMMEDIATE CSE is FREE — the same function uses 0.015625f twice from one
`lui at,0x3c80; mtc1` with no frame cost.
CONSEQUENCE for the frame law: an 8-byte surplus between the saved registers and the home area is
NOT always a mis-counted local. Check for a repeated f32 GLOBAL read first; that space is a homed
CSE temp, and the locals may already be perfect (they were here — the home layout reproduced golden
exactly, just shifted by 8).

# ================================================================================
# MY OWN BRIEF WAS FACTUALLY WRONG ON func_15162B28, AND THE AGENT CAUGHT IT
# ================================================================================

I told the agent that function's parked notes list D_800886F0/F4/F8 and to check each against
variables.h. **Those symbols are not referenced by that function at all.** It touches exactly two
globals — D_8008B364 and D_800BE9A4 — and the three I named appear in func_15164644, a DIFFERENT
function in the same TU. My grep had pulled symbols from the whole parked file, including notes
about other functions, rather than from the function's own references.
The agent audited every `%hi()` in the golden .s, refuted the premise from the binary, and said so.
**Lesson for briefing: extract a function's symbols from ITS OWN golden .s, never from a parked
file that may discuss neighbours.**
Its verdict is unchanged and now better evidenced: exactly TWO rows, the same row twice, 100%
register-only — golden coalesces the local into `$v1` (the register it later recycles) where ours
gets `$a2`. The register-colouring wall stands.

# ================================================================================
# func_15010880: A PURE SCHEDULING RESIDUAL, EXHAUSTIVELY BOUNDED
# ================================================================================

Instruction MULTISET is identical — same 84 instructions, same registers, same immediates, same
relocations, verified by objdump rather than by the differ. Twelve instructions in one straight-line
window are permuted: golden runs a store chain to completion then loads the global; ours hoists the
load above the store. Both are legal schedules of the same DAG covering an lw->addiu interlock.
Axes exhausted with nothing ever below 210: **12/12 statement orders, 8/8 declaration orders, 7/7
OPT_FLAGS settings, 13 global spelling/type variants, 12 line join/split variants, 3 alias-analysis
probes, and a 3,906-iteration permuter run** (histogram bottomed out at the base).

**A USEFUL BY-PRODUCT — THE SHIPPED FLAGS ARE OPTIMAL, MEASURED:**
    -O2 -g3  (shipped)  210   <- best
    -O2                 330
    -O1 -g3            1204
    -O2 -g             3899   (-g1/-g2 identical)
    -O3 -g3            6864
Anyone tempted to explain a residual by "maybe this TU used different flags" now has a number.

# ================================================================================
# WAVE 45 RESULT
# ================================================================================

CLOSED: func_150A09D0, 836 B, game_CDE80.c — a per-frame sweep of the game object table dispatching
on the object kind field, handling a queued-sound retrigger with a proximity test, a two-stage state
machine, a countdown that frees the slot it names, and a broadcast of the object's position into
every active camera record.
Verified independently: score 0 with and without -R, **all 19 siblings in the TU still 0**, .text
IDENTICAL (12,448 bytes), .rodata/.data/.bss identical, symbol size 836 both sides, zero banned
constructs, grep GLOBAL_ASM 1739 -> 1738.

PARKED: func_15010880 @210 (pure scheduling, exhaustively bounded above), func_15162B28 @10
(register-colouring wall, verdict restored with better evidence), func_150144B8 @207 (zero
instruction differences; the whole score is the 8-byte f32-CSE frame temp above).

# ================================================================================
# THE f32-CSE LAW WAS RIGHT ABOUT THE MECHANISM AND WRONG ABOUT THE FIX:
# SPLAT'S D_ NAMES FOR ANONYMOUS LITERAL POOLS ARE NOT GLOBALS AT ALL
# ================================================================================

Wave 46 was launched to cash in the f32-CSE law on func_150144B8 @207 (a function with ZERO
instruction differences). The law reproduced exactly. **The fix it implied was wrong, and the
reason is systemic enough to change how this project reads .rodata.**

`D_80096688` is NOT a global variable. It is **splat's minted name for an anonymous IDO literal
slot**. Golden's source contains no symbol there at all — it multiplies by the FLOAT LITERAL
`0.01745329238f` (pi/180), and IDO minted that constant into the TU's literal pool.

    named extern, read twice   -> frame 200      <- what we were building
    float literal, read twice  -> frame 192      == GOLDEN, byte-identical instruction stream

**HOW TO RECOGNISE AN ANONYMOUS POOL WITHOUT BUILDING ANYTHING — DUPLICATE VALUES.**
A named shared global appears ONCE. An anonymous per-function literal pool repeats itself,
because each function mints its own copy:

    D_80096688  .float 0.01745329238      <- pi/180
    D_80096690  .float 0.01745329238      <- pi/180 AGAIN, different address
    D_80096694  .float 0.01745329238      <- and AGAIN
    D_8009664C  .float -10000
    D_8009667C  .float -10000             <- -10000 twice
    D_800966B4  .float -10000             <- three times
    D_80096698 / D_8009669C / D_800966A8  .float 1.525902189e-05   <- x3

Three copies of pi/180 at three addresses is not a program with three constants. It is one
constant minted three times by three functions. **When you see a repeated value in a D_ run,
stop treating those names as variables.**

## THE CONSEQUENCE FOR THE `extern f32` ESCAPE, WHICH THIS FILE PREVIOUSLY CALLED FREE
It is free **only when the constant is read ONCE**. Read once, `extern f32 G` and a literal emit
the same `lui at,%hi / lwc1 %lo` pair with the same relocation, so the escape is invisible.
Read TWICE, IDO homes the named-extern CSE (+8 frame bytes) but pools the literal CSE for free.
That is the whole of func_150144B8's 207. The escape has a documented cost now, not a blanket
licence.

## WHY IT STILL CANNOT BE SHIPPED: THE POOL MUST BE MINTED, AND MINTING IS ALL-OR-NOTHING
To get the literal to land at 0x80096688 the whole game_40490 pool must come from C, and IDO
mints literals in the order the functions using them appear. Verified this wave:

  * The region **is contiguous and exclusively owned** — grep over src/ and asm/nonmatchings/
    finds ZERO foreign references to D_800966xx. It therefore does NOT hit the contiguity law
    that permanently killed game_12C1E0.
  * The region is **jtbl -> float pool -> jtbl**: func_150130B4's jump table sits immediately
    below 0x80096630, and jtbl_800966C0 immediately above 0x800966B4 (after two zero-float
    alignment slots). Since the jtbl unlock and the rodata migration are THE SAME conker.us.yaml
    line, one edit addresses both.
  * **THE TRUE COST, and it is larger than the pool's stubbed functions:** ELEVEN functions use
    this pool, not five. Five are stubbed (func_150130B4 which also needs its jtbl, func_15013778,
    func_150144B8, func_1501474C, func_15014B60). **The other six are already byte-perfect live C**
    reaching the pool through sixteen `extern f32` declarations (game_40490.c lines 9-23 and 661).
    A migration must rewrite those six to literals as well, because the names cease to exist once
    the section is emitted from C.

**So the campaign risks SIX matching functions to gain FIVE.** That is a legitimate trade only if
the six can be held at 0 under the literal spelling, which is a measurable precondition, not a
hope. Run it as a staged spike with that as the kill switch — never as an open-ended rewrite.
Until then **207 is a hard floor on func_150144B8; do not respell the multiply again.**

# ================================================================================
# NEW VARIANT OF THE RELOCATION-NAMING FLOOR: LOOP BOUNDS SPELLED AS THE *NEXT* SYMBOL
# ================================================================================

On func_1501BBB8, golden bounds three of four loops with `%hi/%lo(D_800BE760)`, `(D_800BE930)`,
`(D_800BE708)` at **addend 0**, where the natural `for (i = 0; i < 4; i++)` produces
`%hi/%lo(D_800BE748)+24`, `(D_800BE918)+24`, `(D_800BE700)+8`.
The LINKED words are identical — base+24 IS the next symbol's address, and these are absolute
linker-script constants from undefined_syms_auto.txt. Only the OBJECT relocation differs.

This is a HARDER variant than the known floor: there the instruction words matched and only the
reloc symbol NAME differed; **here the words differ too and only the linked result agrees.**
Root cause: in the original these were file-statics whose relocs were section-relative with the
+24 folded into the addend; splat resolved each final address to whatever symbol sits there.

TWO RULES FALL OUT:
  (a) An array-walk loop whose end lands exactly on another D_ symbol must be bounded by
      `(T *)D_<next>`, not by a count.
  (b) It must be a **do/while**. Written as a `for` with an address bound, IDO emits an entry
      guard golden does not have — measured 11555 (`for`) vs 10190 (`do/while`), same bound.

# ================================================================================
# IDO 5.3 AT -O2 -g3 HAS NO ACTIVE LOOP UNROLLER: A 2x-UNROLLED LOOP IS *SOURCE*
# ================================================================================

func_1501BBB8's middle loop steps `i` by 2 and handles players i and i+1 per iteration. That is
how the original was written; it is not a compiler artifact. Proved two ways:
  * The other three loops in the same function are also 4-trip and are NOT unrolled — an active
    unroller would have taken those first.
  * Through the Makefile's dangling `LOOP_UNROLL` hook (referenced line 221, never defined):
    `-Wo,-loopunroll,2`, `,200` and bare all left the function at exactly 248 instructions, while
    `-Wo,-nounroll` produced "uopt: Warning: unrecognized option" — so `-loopunroll` IS recognised
    and simply has no effect here.
  * Opt sweep: -O2 -> 247, -O1 -> 460, -g -> 487, none unrolled. (-O3 is unreachable:
    asm_processor.py rejects it.)
**If golden's loop is unrolled, unroll the SOURCE.**

# ================================================================================
# NEW READING-GOLDEN RULE: `slti at,X,K` + `bnez at` MEANS THE *ELSE* HOLDS THE ZERO
# ================================================================================

`slti at,X,K` followed by `bnez at` where the taken side stores ZERO means the source is
`if (X >= K) { compute } else { 0 }` — NOT `if (X < K) { 0 } else { compute }`.
Flipping four dead-zone tests on that reading alone (with the loop-bound fix) moved func_1501BBB8
from 8920 to 6520 in ONE build.
RELATED, also confirmed: a ternary whose true-value is a constant that golden materialises far
earlier is not a ternary in source — it is `n = 4; if (cond != K) n = other;`. The ternary emits
an extra `b`/`li` pair where golden has a bare `beq ... join`.

# ================================================================================
# DECLARATION ORDER CAN BE COMPLETELY INERT -- MEASURED OVER ALL 720 ORDERINGS
# ================================================================================

This file has repeatedly listed declaration order as the top untried lever. On func_15084044 it is
worth NOTHING: **all 5! x 3! = 720 orderings scored exactly 13** at frame -96 (466 s, affordable
only because of the new scorer). Roughly 25 further structural/type/statement-order variants also
scored 13. The residual is ONE virtual register — golden uses all six caller-saved pseudos and
gives the CSE `$a3`; ours recycles the dead `obj`'s `$v0`.
Also resolved from the raw encodings: the accompanying `bne` operand flip is **not a second
defect** — both builds put the higher-numbered register in `rs`, so the flip follows from the
colour. One defect, not two.

# ================================================================================
# NEW TOOL: tools/fastscore.py -- 0.7 s PER VARIANT, ~85x FASTER
# ================================================================================

asm_processor + IDO cc into a PRIVATE directory, then a relocation-masked word compare against the
golden .s. Cross-validated to reproduce asm-differ's row count exactly on func_15084044 (13 = 13).
It never touches conker/build/, so it needs no buildlock and **cannot read a stale object**.
This is what made the 720-case sweep affordable at all.

**IT IS A SEARCH METRIC, NOT A VERDICT — the tool's own docstring says so.** Relocation symbols are
masked out, so `mism == 0` still has to be confirmed on the real `make` + asm-differ loop before
anything is called a match. Two cautions measured while building it:
  * Grepping the disassembly for a fixed base register is a TRAP — one variant looked like a win
    but had merely re-coloured `base` s4->s5.
  * A raw word compare WITHOUT relocation masking reports ~125 false mismatches on an otherwise
    perfect build.

TOOLING GAP worth closing: asm-differ refuses `end` together with `-o` ("end address not supported
together with -o"), and clamping `--max-lines` to the symbol's instruction count silently triggers
the truncation walk-back (trap 1). There is currently **no supported way to get a symbol-bounded
score**; both agents hand-rolled readelf+objdump+difflib beside every score.

# ================================================================================
# OPEN QUESTION, HANDED OVER WITH THIRTEEN NEGATIVES ENUMERATED
# ================================================================================

What C makes IDO emit a **symbolic store** (`lui at,%hi(SYM)` + `s* rt,%lo(SYM)(at)`) to a global
while a base register holding `&SYM` is live and is being used for the LOADS in the same statement?
Golden emits 4 instructions per site for `D_800BE740 |= K`; every spelling we can produce emits 3.
Ruled out, each built with the project's exact flags: `|=`; `x = x | K`; `A[0] |= K`; read hoisted
into an int local; `G = *(u8*)&G | K`; `*(u8*)&G = G | K`; struct member at offset 0; s32-typed
global; OR of a variable; `= 0` moved after the blocks; three `u8 *f = &G` pointer-local variants;
and `extern volatile u8`. **So it is not the |= spelling, not the width, not volatile, not a cast,
not statement position — it is how the original TU declared that byte.**
It is a 4-instruction-per-site systematic that cascades into a wrong register class (s0) and a
wrong frame size downstream, so it is worth real effort.

# ================================================================================
# WAVE 46 RESULT
# ================================================================================

CLOSED: NOTHING. Four functions parked, every negative recorded with its score, both TUs reverted
to pristine with their pragmas live and their stale objects deleted.
  func_150144B8 @207   cause SOLVED (literal, not global); blocked on the game_40490 pool migration
  func_15084044 @70    hand-search space provably exhausted (720 orderings + ~25 variants); permuter
  func_150D5124 @105   100% register naming, t6<->t7 exchanged on 20 of 199 rows; permuter
  func_1501BBB8 @6520  cold, whole CFG + frame + all four loops reproduced; blocked on the
                       symbolic-store construct above
A screen failure worth noting: func_150D5124 was briefed as "never attempted" but carried a parked
attempt as a comment block at game_100810.c:111-179 claiming best 105. The agent rebuilt it from
scratch and reproduced exactly 105, so the baseline is confirmed rather than inherited — but
**pick_clean.sh should screen for parked comment blocks inside live TUs, not just pragmas.**
