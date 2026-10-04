# game_1E37D0 / rodata block 24EF20 campaign (2026-10-03) -- PARKED, nothing shipped

Block 24EF20 (0x30 B, yaml `[0x24EF20, rodata]`) is owned by five functions. Migrating it
(`[0x24EF20, .rodata, game_1E37D0]`) requires ALL its constants to come from C in golden order.

| func | state |
|---|---|
| func_151B6420 | C, mism 0 (literal must be `0.4940000176f`) |
| func_151B7144 | C, mism 0 |
| func_151B7328 | C, mism 0 (local `const s32 tbl[4]` initializer IS D_800AA460) |
| func_151B65D4 | near-miss n=210/213: golden spills reloaded `st->unk14` to 0x58, ours keeps it in a reg |
| func_151B7998 | near-miss n=168/168, ~84 rows FP colouring order |
| func_151B70B4 | (no rodata) near-miss n=35/36, unfilled `jr` delay slot |

Files: `game_1E37D0.three_matched.c` (3 C, rest pragma -- NOT shippable alone, its literals need
the block migrated); `game_1E37D0.allC_nearmiss.c` (all five in C; emits the exact block bytes,
so the literal spellings are already right); `game_1E37D0.late_rodata_option.c` + `lr_*.s`
(ships the 3 today by giving the two asm stubs a leading `.late_rodata` -- needs tracked asm
outside asm/, no precedent in the tree; owner decision). The named `const f32 X[1]` fallback is
NOT viable here (changes 6420/7328 codegen). Close 65D4 + 7998 and the whole thing ships.
