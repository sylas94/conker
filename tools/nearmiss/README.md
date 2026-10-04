# Abandoned reconstructions

> **Exception — `func_151C196C.c` is NOT abandoned and NOT unverified.** It is a confirmed
> score-0 match (whole TU, both with and without `-R`) that is *blocked on another function*.
> Its `5000.0f` literal makes IDO emit a private 16-byte `.rodata` pool, and the golden block
> at `0x24F480` is `459C4000 3DCCCCCD 00000000 00000000` — `D_800AA9C0` (5000.0f, this
> function) followed by `D_800AA9C4` (0.1f), which belongs to **`func_151C1D5C`**, the next
> function in the same TU and still a `#pragma`. Migrating the block today would lay a
> 16-byte section carrying only 5000.0f over the golden 16 bytes and zero the 0.1f, breaking
> the ROM; *not* migrating it means the object will not link. Ship both together: once
> `func_151C1D5C` is live C carrying its own 0.1f, IDO emits pool constants in first-use order
> and reproduces the golden block exactly, at which point
> `- [0x24F480, .rodata, game_1ED0F0]` becomes correct.
> `func_151C1D5C` is 604 B / 151 instructions / 1 callee / 9 float ops and not hand-written,
> so closing it unlocks **1,612 bytes**.

72 functions, **72,680 bytes**, that are still `#pragma GLOBAL_ASM` stubs but
already have a C reconstruction someone wrote and then dropped when the score plateaued.
Recovered from a session scratchpad (a temporary directory) so they stop being one wipe away
from gone.

One file per function, named `<func>.c`. `backlog.tsv` carries the size, owning TU, and the
original snapshot filename.

## The scores ARE known now — read `ranked.tsv` first

`backlog.tsv` is sorted by SIZE, which ranks how much work a function was to write, not how
close it is to matching. Nothing recorded scores, so the parks that were nearly finished were
invisible and effort went to functions scoring in the hundreds. Regenerate the real ranking
with:

    python3 tools/nearmiss/_triage.py --out tools/nearmiss/ranked.tsv

First full run (2026-08-23), 207 parks: **86 score, 99 do not even splice, 22 are already
decompiled.** Seventeen score 25 or below. Three score 0 and **none of them ships as-is**:

| func | why it does not ship |
|---|---|
| `func_15113218` | its 0 is a **known fake** — the frame is padded with five dead `probe` locals, which the project bans. Its own park says so. |
| `func_1518BA90` | real, but needs `jtbl_800A7410`; blocked on the rodata block migration until `func_1518BD60` also reaches 0. |
| `func_100052A0` | real (mism=0, n=180/180) but **will not link**: the match needs a function-scope `static u64`, a real `.bss` allocation with a local symbol, and `conker.ld` discards it. |

A scorer reporting 0 is necessary, never sufficient. Two of those three prove it.

## Repairing stale parks — and why the scores need reading carefully

99 parks would not splice at all. `_autofix.py` splices, compiles, deletes exactly the
duplicate the TU has since gained, and retries, leaving the parks themselves untouched:

    python3 tools/nearmiss/_autofix.py --out tools/nearmiss/repaired.tsv

Result: measurable parks **86 → 102**. Sixteen newly unlocked — but **only 11 of those are
trustworthy**. Five deleted a *deliberate shadow* and are flagged `SEMANTIC RISK`.

A park that works around a wrong `variables.h` declaration brackets its own with
`#define` / `#undef`. That looks exactly like a duplicate, and deleting it produces a
**better score for a different program**. The worked example is `func_15010880`:
`variables.h` says `struct178 D_800D3098[73]`, the symbol really holds a pointer, and the park
re-declares it `extern struct178 *D_800D3098;` on purpose. Without the shadow,
`&D_800D3098[72]` silently becomes an address computation instead of a pointer load — golden's
`lw $v0, %lo(D_800D3098)($v0)` is precisely the instruction that vanishes. The park's honest
score is 210; the broken version reads **16 with an exact instruction count**.

Nothing warns you: it compiles, it scores, and it scores far better. So `_autofix.py` reports
every identifier it removed, and marks a `#define`/`#undef` bracket with `!`. Removing sibling
*function definitions* the TU already has is the safe case — that is what the 11 clean ones did.
Best clean new score is 28, so this unlocked measurement, not matches.

## Tools

| tool | what it does |
|---|---|
| `_triage.py` | scores every park, writes `ranked.tsv` |
| `_splice.py` | park → full TU, ready for any scorer. **Splices by default**; only an explicit `STANDALONE TU` marker suppresses it |
| `_dump.py` | side-by-side ours vs golden, X-marking differing words |
| `_sweep.py` | scores a JSON list of `[label, full_tu_source]` variants |
| `_whyfail.py` | groups non-splicing parks by their real compiler error |
| `_autofix.py` | repairs the splice of stale parks and reports what they actually score |
| `../structdiff.py` | splits a residue into structural rows vs a register permutation |

Build variants by editing the text `_splice.py` returns. Hand-cutting a park from its
function definition drops the typedefs it declares above — then even the control fails to
compile, which reads as "every variant is broken" rather than "the harness is wrong".

Always put an unmodified control in the same sweep. Several conclusions in these parks were
measured against a baseline that had since moved, and a refutation measured against the wrong
baseline is not a refutation.

## Read this before using one

**These are UNVERIFIED.** Specifically:

* **The scores are unknown.** `filename_hint` is parsed out of the original filename and is a
  guess, not a measurement. Some are real scores, some were TU load addresses. Run
  `tools/rescore_backlog.sh` to replace them with measured numbers -- that is the step that
  turns this directory from a pile into a work queue.
* **They may not compile.** They were written against headers that have drifted since.
* **They may contain fake-match constructs.** Some pre-date the no-fake policy. Audit every
  one against the banned list in `tools/ido_cookbook.md` -- `new_var`, `dummy_label`,
  volatile-to-pin, `if (0) {}`, self-assignment, `x && x`, no-op mask chains, empty
  do-while, `&local`-to-force-a-reload -- **before** shipping anything derived from them.
  A score of 0 is necessary, not sufficient.
* **A definition here does not mean the function is close.** It means somebody started.
* **DESTRUCTIVE: many of these are whole-TU snapshots taken from an OLDER tree, and copying
  one over `conker/src/<tu>.c` can DELETE functions that have been matched since.** Real case:
  `func_1502BAD0.c` predates the match of its sibling `func_1502C974`, so installing it
  wholesale silently reverts that function to a stub. Apply only the hunk for your target,
  forward-declaring anything it needs, and before you build, diff the function lists:

      git show HEAD:conker/src/<tu>.c | grep -oE '^[A-Za-z_].*\bfunc_[0-9A-Fa-f]{8}\s*\(' \
        | grep -oE 'func_[0-9A-Fa-f]{8}' | sort -u > /tmp/before
      grep -oE '^[A-Za-z_].*\bfunc_[0-9A-Fa-f]{8}\s*\(' conker/src/<tu>.c \
        | grep -oE 'func_[0-9A-Fa-f]{8}' | sort -u > /tmp/after
      comm -23 /tmp/before /tmp/after     # anything printed is a function you just destroyed

  Always re-score EVERY sibling in the TU afterwards, not just your target.
* **A score of 0 does not prove it links.** In an unlinked object `lui $at, %hi(X)` encodes as
  `3C010000` whatever `X` is, so asm-differ cannot see a wrong `.rodata` reference — and `-R`
  hides the reference rows outright. A reconstruction that inlines a float literal will emit a
  private pool that `conker.ld` discards, scoring 0 and failing to link. Score with AND without
  `-R`, and let the ROM gate be the arbiter. See `func_1510C8A8` (commit f8e68f6) for the fix
  pattern: migrate the pool with a one-line `conker.us.yaml` edit rather than rewriting the C.

## Why they are worth keeping

Structure is the expensive half of a match and registers are the cheap half (see the
register-colouring section of `tools/ido_cookbook.md`). Each of these files is structural work
already paid for. Re-scored and sorted, the low end of this list is the cheapest remaining
byte source in the project.

Generated by `tools/backlog.py`.
