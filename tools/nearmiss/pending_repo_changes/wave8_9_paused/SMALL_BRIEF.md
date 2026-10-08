# Small-function batch brief (Conker decomp, IDO 5.3)

You get a batch list (func, TU, size, flags). Work it smallest-first. For EACH function:
1. Check prior work FIRST: `tools/nearmiss/<func>.c` (a park file: header explains the residue and
   what was refuted), `tools/nearmiss/NOTES_*.md` (grep the name), and comments next to the
   pragma in the TU. Don't repeat refuted spellings. Many parks predate this session's new levers.
2. Fast reject (report, don't grind): a bare `j` tail-call thunk; MIPS III (ld/sd/dsll...);
   lwl/lwr; trapping add/sub/neg; `/* Handwritten */`; no stack frame + register usage IDO never
   emits (e.g. $at/$k0 as GPRs, `or $t0,$sp,$zero`).
3. Time-box: ~10 honest attempts / one clear diagnosis per function, then move on.

## Levers proven THIS session (try these on old parks first)
- A block that DECLARES something (even a block-scope `extern` of a symbol the block uses) is a
  -g3 scheduling barrier; a bare `{}` is not. It fixes entry-block order, jal/branch delay-slot
  fills (incl. the "golden copies the merge block's first insn into the b delay slot" pattern once
  thought unsteerable), constant materialisation points, loop-tail order, store order.
- Where a struct/local is declared (which block) decides its -g3 home and store order.
- Callee prototype param width (s16 vs s32), pointer vs s32, a global's declared type (u32 vs s32,
  u8* vs s32), return-type shadows (`#define f f_hdr` / `#include "functions.h"` / `#undef` /
  real prototype -- see conker/src/game_121A20.c) decide narrowing / andi / temps.
- `D[i]` hoists a row address, `(u8 *)D + (i << 2)` rematerialises per use; aggregate local keeps
  values in memory; `x + x` vs `x*2`; `1.f`/`1`/`= 0` vs `1.0f`/`0.0f` decide FP pooling/regs;
  integer literal in a float expr keeps a real mul.s; `(s16)` on a delta fixes temp rotation;
  only loops whose counter isn't reused get unrolled; per-TU `OPT_FLAGS` (fastscore prints them).
- Literal vs `extern f32`: an extern load is aliasable memory and schedules differently. For a
  constant in a SHARED rodata block (`asm/data/*.rodata.s` used by other still-asm functions),
  the function must match WITH `extern` (the symbol stays in asm data). If it only matches with a
  literal, report "BLOCKED: rodata" with the block name -- that needs a whole-block campaign.
  Jump tables (`jtbl_`) likewise need the block to migrate -- report "BLOCKED: jtbl" unless the
  jtbl's block is referenced only by this function (then say so; coordinator decides).

## Environment / rules
- Repo (Windows) `C:\Users\ssyla\OneDrive\Desktop\conker\conker decomp`; WSL
  `/mnt/c/Users/ssyla/OneDrive/Desktop/conker/conker decomp` (SPACE -- single-quote).
  `wsl -d Ubuntu-22.04 -- bash -c "cd '<wsl repo>' && <cmd>"`, python with PYTHONUTF8=1; put loops
  in a .sh in your work dir. Heavy scanning inside WSL.
- Scoring: `python3 tools/fastscore.py <TU> <func> <copy.c>` (mism 0 = match);
  `tools/nearmiss/_dump.py`, `tools/structdiff.py`. Never two fastscores of one function at once.
  For nested TUs (libultra/...) fastscore may pick the wrong flags -- check conker/Makefile.
- NEVER edit the repo (src, headers, yaml, ld, Makefile). NO make, conker/build/, git, splat,
  permuter, NON_MATCHING/PERMUTER builds.
- Deliverable: for each TU in your batch, ONE whole-TU copy `<work dir>/<TU basename>.c` (LF)
  containing ONLY the functions you matched (unmatched stay `#pragma GLOBAL_ASM`), with every
  already-C function still byte-identical vs `conker/expected/build/src/<TU>.c.o` (masked .text).
  Snapshot after every match.

## Fake-match policy (owner-mandated)
Score 0 necessary, not sufficient. BANNED: `if (0) {}`, `x && x`, dummy labels / goto used only for
codegen, `*(volatile T*)&x`, unnamed pad / never-referenced locals to move the frame, `new_var`
pins, non-bug self-assignment, `p = &local` reload tricks. Owner-APPROVED: declaring blocks incl.
block-scope extern as barriers; named+used frame locals; a dead store of a call's return value;
honest temps; statement/store order. Original-game bugs reproduced WITH
`/* BUG (original game): ... */`. Flag anything else whose only effect is codegen.

## Report
Table: func | result (MATCH / near-miss mism+n / BLOCKED rodata|jtbl / REJECT reason) | one line.
Paths to the per-TU copies. For each match: any judgement call. For near-misses: the residue and
next lever (short) -- the coordinator updates park files.

## Added after batches 1-2
- Golden storing arg0 once and reloading it from its home slot (with `addiu vN,vN,OFF` before a
  store) = a named sub-struct pointer `s = &arg0->subOFF` with every access through it.
- A pointer-to-array cast `(*(u8 (*)[N])&D)[i]` (or the true array decl) lets IDO strength-reduce.
- NOT accepted: a block-scoped alias of a PARAMETER (`{ T *o = arg0; ... }`) used only to steer
  codegen -- that's a new_var pin. Report such near-misses instead.

## Added after batches 3-6 (all closed real functions; full log in tools/nearmiss/NOTES_smallest_first_2026-10-03.md)
- Index loop over a GLOBAL array (`for (i...) D[i]...`) gives separate address materialisation and
  folds the end bound into `%lo(sym+N)`; a local pointer walk does not.
- Storing through the global array (not a cached local pointer) lets IDO hoist stack-arg loads.
- A barrier block around the FINAL call fixes an unfilled jal delay slot; per-case block-scope
  extern fixes per-case slot fills.
- List walks: `var = next; continue;` in the non-taking branch, `next` declared in the loop body.
- `ptr++` as a BODY statement (not the for-increment) fixes "split-symbol" peel residues.
- Constant-hoist family: declare the per-entry pointer INSIDE the conditional block.
- Header shadows: callee declared with narrower params (`u8`/`u16`), `u32` vs `s32`, or a `void`
  return (see conker/src/game_121A20.c for the shadow pattern) -- often the whole residue.
- A field read as u16 for a test and as s16 for an argument is real (golden has lhu AND lh).
- `x |= 0;` on a byte field is a REAL lbu/sb in golden when you see it -- not a forcer.
- Float locals live across a call: function-scope -> callee-saved $f20; block-scope -> own slot.
- Actor pointers: an `#define`-style macro expression per use, not a cached local, when golden
  rematerialises the address each time.
- REJECTED by coordinator (do not submit): overwriting a PARAMETER as a working variable
  (`for (i = arg0 = X; ...)`), block-scoped alias of a parameter, unnamed pad locals.
- A masked .text compare is NOT a ROM verdict: one 0-score function broke the ROM sha1 when
  linked (a relocation/data difference). Prefer exact symbol spelling for every %hi/%lo/jal
  target; avoid `*(u8 *)&GLOBAL` style punning unless golden really reads a byte of a wider global.

## Added 2026-10-06 (each closed a real function this week)
- ASSIGNMENT POSITION decides a constant local's register (not declaration order): if a counter/flag
  lands in the wrong register, move its `x = K;` among the entry statements (e.g. right after the
  competing def) -- IDO hoists the constant itself.
- SWITCH SCOPE: a case body that is a declaring block still OPEN at its final `return` makes IDO fill
  the jtbl range-check delay slot from the fall-through (`sll`) instead of the default target
  (`li v0,K`). Close the block before the last statement: `{ T x[] = ...; if (f(x)) return -1; } return 6;`.
- Initialised local array: `const T a[] = {...}` puts the image in .rodata, non-const in .data -- match
  golden's section. Initialiser copies emit destination-first; a struct copy emits source-first.
- Memory residency: golden storing/reloading a "point" through the stack = an ARRAY (`f32 p[3]`); a
  struct17 local gets its fields scalarised into FP registers.
- RIGHT operand is emitted first (also for `!=` in branches and for `a*b + c*d` products).
- Rematerialisation: IDO recomputes `y = x - K` at each use (and promotes its operands) when x is a copy
  of something never redefined; golden computing once at entry + spilling means x's source is redefined
  later (often a reused scratch temp).
- REJECTED by owner: a dead read of a field/global into an otherwise-unused local (permuter loves these).
- For -g / libultra TUs fastscore may score at -O2 -g3 by mistake: check the "# TU: OPT_FLAGS" line it prints
  against conker/Makefile (libultra/audio/* is -g) and force flags if needed (Scorer(...).opt = ['-g']).
- SDK code (libultra, n_audio): write the verbatim SDK shape first with u8 chars and SDK decl order.
