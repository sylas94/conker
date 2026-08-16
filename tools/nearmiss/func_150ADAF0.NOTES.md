# func_150ADAF0 (game_DAFA0, 1936 B) — NOT ATTEMPTED, and it is BLOCKED for a reason that is not the jump tables

Reconnaissance only, 2026-08-16. `conker.us.yaml` was **not** touched for this TU; the planned
line `- [0x22D080, .rodata, game_DAFA0]` remains un-applied, which is correct while the function
is still `#pragma GLOBAL_ASM`.

## The hard blocker: an external branch INTO the middle of the function

`conker/src/game_DAFA0.c` line 57 holds the repo's one inline `GLOBAL_ASM(` block. It defines
`func_150AE280`, and its body is:

    glabel func_150AE280
        lui   $t2, %hi(D_800D3858)
        lw    $t2, %lo(D_800D3858)($t2)
        lui   $at, %hi(D_800D3858)
        sw    $zero, %lo(D_800D3858)($at)
        b     .L150AE0AC          <-- branches into func_150ADAF0's BODY
         or   $sp, $t2, $zero     <-- while swapping the stack pointer

`.L150AE0AC` is a *local* label at offset 0x5BC inside
`asm/nonmatchings/game_DAFA0/func_150ADAF0.s` (line 400, `lw $ra, 0x0($sp)`). It resolves today
only because asm-processor assembles the pragma'd function and the inline block into the same
unit. `func_150ADAF0` is therefore a function with a **second, external entry point in its
interior**, reached by a hand-written stack-switching trampoline (a longjmp-style unwind:
restore `$sp` from `D_800D3858`, then re-enter the epilogue).

C cannot express that. The moment `func_150ADAF0` becomes C, `.L150AE0AC` ceases to exist and
`func_150AE280` will not assemble. Any plan for this TU has to solve that first — e.g. by also
hand-writing `func_150ADAF0`'s epilogue, or by proving `.L150AE0AC` can be re-expressed as its
own `glabel`-ed asm stub that both paths call. **Do not start the C until that is settled.**

## The rodata scoping in the wave brief is incomplete

The brief describes the migration block 0x22D080.. as "four jump tables plus `D_80088628` +
`D_800886A4`". `D_80088628` and `D_800886A4` are **also jump tables**, and worse ones:

| symbol | entries | note |
|---|---|---|
| `jtbl_800885C0` | 5  | `.L150ADB90/98/BA4/BB0/BBC`, all resolved by splat |
| `jtbl_800885D4` | 7  | targets `.L150ADC74/C88/C9C`, and `.L150ADC2C` three times (the default) |
| `jtbl_800885F0` | 7  | same shape: `.L150ADD24/D38/D4C`, `.L150ADCD8` ×3, `.L150ADD04` |
| `jtbl_8008860C` | 7  | same shape: `.L150ADDD4/DE8/DFC`, `.L150ADD88` ×3, `.L150ADDB4` |
| `D_80088628`    | 31 | **raw `.word 0x150ADE24` …** — splat did NOT resolve these to labels, so there are no `glabel .L…` anchors for them in the `.s` |
| `D_800886A4`    | ≥6 | first three entries are `func_1509DD10 / func_1509DD20 / func_1509DD30` — addresses in a **different function** — then raw in-function addresses `0x150AE0F8 / 0x150AE108 / 0x150AE118` |

`D_800886A4` mixing cross-function addresses with in-function addresses cannot be a plain C
`switch` jump table (a switch's table can only hold labels of the enclosing function). Decide
what it actually is before assuming the migration line is enough.

Note also that jtbl_800885D4 / 5F0 / 860C are the same 7-entry shape with the default target
repeated at indices 3, 4 and 6 — i.e. three sibling switches over the same 0..6 selector, whose
default arm is folded into the table. That is the same 0-based-table-with-default-entries idiom
that `func_1501C730` (game_49BE0, closed this wave) needed an explicit `case 0:` for.

## Symbols that correctly stay external

`D_800885B0` (shared with func_150ADA20 / A68 / ACC) and `D_80087358` / `D_80088420` /
`D_8008845C` / `D_80088498` / `D_800884D4`, which live in earlier rodata blocks.
