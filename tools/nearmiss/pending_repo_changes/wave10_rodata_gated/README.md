# Wave 10A (2026-10-08): matches that need a rodata change before they can ship

- game_1CBE20.RODATA_SPLIT.c -- func_1519EB8C mism 0 with literals; takes game_1CBE20 to 0 pragmas.
  Needs block 24D640 SPLIT: keep `[0x24D640, rodata]`, add `[0x24D780, .rodata, game_1CBE20]`, and
  re-run splat so 24D640.rodata.s is regenerated shorter (a hand ld edit alone is not enough).
  Literal spellings matter: -1.32400012f, 26.18200111f.
- game_F3270 / game_F3BA0 .RODATA_MIGRATION.c -- 5F94+60D8 / 68C4+6A08 mism 0 with literals.
  Blocks 244ED0 / 244F10 can only migrate once 6460 / 6D90 also match (near-miss 53, file here),
  because the blocks can't be split at 0x244EFC. Check 0.60497f == 0x3F1ADF50 before use.
- NEAR_func_1500F40C_mism4_RODATA.c -- 4 off; sole owner of 23AD10 -> migrate on match.
- NEAR_func_1513B5E0_mism69.c -- buf induction variable live-range split (game_168A90's last fn).
