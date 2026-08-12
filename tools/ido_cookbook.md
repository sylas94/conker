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
