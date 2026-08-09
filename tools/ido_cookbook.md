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

## Diagnosing a FALSE non-zero score
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
