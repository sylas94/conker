# Fake-match debt audit (2026-08-14)

Scoped while waiting on a wave. **Nothing here is acted on** — every item below is
byte-perfect and inside a ROM that gates to the correct sha1. This is an inventory so
the debt is visible and decidable, not a change proposal.

The project rule is: *score 0 is necessary, not sufficient*. Banned for new work are
`new_var` / `dummy_label` / volatile-to-pin / `if (0)` / self-assignment / `x && x` /
no-op mask chains / empty `do {} while` / `&local` to force a reload / dead locals that
exist only to move the frame. The items below predate the current pipeline.

## 1. Seven places the authors flagged their own work

    game/done/game_1765E0.c:10   // fakematch? an alternative is to mark sp24 as volatile
    game_18D770.c:641            struct233 **tmp = &D_800C3958; // fakematch?
    game_3D9A0.c:30              // FAKEMATCH but works...
    game_83300.c:660             // FIXME: fakematch to force regalloc
    game_D5160.c:40              //     // fakematch to "help"...
    init_B1B0.c:308              // fakematch
    init_EB00.c:281              // fakematch

These are the highest-value items in the audit: the author already believed the construct
was wrong, so each is a recorded open question about what the original source said.

## 2. `volatile` — 61 occurrences across 33 game/init files

libultra has 2 more, on hardware registers, which are **legitimate** and out of scope.

Concentrations: `game_19A8B0.c` 9, `game_142560.c` 5, `game_1D0840.c` 4,
`game_E5E90.c` / `game_1FA770.c` / `game_156160.c` 3 each.

Three distinct shapes, which want different treatment:

**(a) Cast-to-pin — the classic forcer.** Defeats CSE or forces a reload:

    game_142560.c:588   arg4[0] = *(volatile f32 *)&arg4[0] + arg0->unk10;
    game_1D0840.c:359   *(volatile f32 *)&arg0->unk38 = arg0->unk38 + temp_f0;
    game_156160.c:24    entries[*(volatile u8 *)((u8 *)arg0 + 0x23D)].unk2 = 0;
    game_133190.c:320   D_80088C38[*(volatile u8 *)((s32)arg0 + 0x68)](arg0, arg1, arg2);

Note the wave-40 result is directly relevant here: a forced re-read is often honestly
spelled as a **second read of the same field**, because IDO's CSE turns the second read
into the register copy. `hp2 = hp;` scored 650 where `hp2 = arg0->health;` reached 0.
Several of these may dissolve the same way.

**(b) `volatile` in a declaration** — a storage-class forcer, and it grows the frame
under `-g3`:

    game_142560.c:244   volatile f32 sp2C;
    game_19A8B0.c:156   volatile s32 arg28, ...
    game_1AC2F0.c:342   ... volatile s16 arg4, ...
    game_1D6E80.c:633   volatile u16 field_0x5E;      <- inside a TYPE definition

**(c) Probably genuine** — leave alone unless proven otherwise:

    game_12BD10.c:33    union { volatile s32 w; f64 d; } sp48;   <- float/int punning idiom
    debugger/debugger.c:191  *(volatile u8 *)&D_160037F0          <- debug/hardware address

## 3. `do { } while (0)` wrappers

Including empty ones (`game_1D43B0.c:52`, and one unreachable between switch cases in
`game_16EE20.c`). `game_1D0840.c:683` stacks several banned constructs on one line — a
`mask = 0xFFu` no-op mask, a `do{}while(0)` wrapper and a volatile store.

## 4. One unnamed frame-shaping local (already documented in place)

`game_204660.c:195` — `s32 pad_dummy[2]`. Six of the original seven were removed in
commit `7270e0c` as a pure refactor; this one is the only site where the dummy is declared
*last*, below every aggregate, so no struct can absorb it. Deleting it breaks the match; a
4-byte version is byte-identical, so the true shortfall is 4 bytes not 8. Left with a
firing-control measurement recorded in a comment.

## How to handle this, if it is ever worked

Same method that worked for the dummy locals:

1. Find the **honest spelling** — the struct size, the second field read, the statement
   split that makes the forcer unnecessary.
2. **Accept only a byte-identical result.** The whole TU's `.text`/`.rodata`/`.data` must
   be unchanged; take a baseline compare *before* editing so a pass cannot be a
   pre-existing one.
3. Where no honest spelling exists, **document it in place** and move on.
4. **Never delete a working match to satisfy a lint.** These are byte-perfect; removing one
   without a replacement would trade a correct ROM for a tidy file.

Two traps apply directly to this work: 3 of 464 live `.c` files are **CRLF**
(`game_1E37D0.c`, `game_204660.c` among them), which silently no-ops a `\n`-matching
patcher; and `asm-differ -o` is **not bounded by symbol size**, so scores must be bounded
to the symbol when several functions in a TU are in flight.
