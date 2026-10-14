# Campaign: rodata block 0x24F9A0 (game_1FA770)

Block `asm/data/24F9A0.rodata.s` (D_800AAEE0..D_800AB0AC) is referenced only by game_1FA770 functions:
func_151CD4C0, func_151CD674, func_151CD7BC, func_151CDB94, func_151CDE20, func_151CE6D0, func_151CEC54,
func_151CF120, func_151CFA4C, func_151D014C, func_151D09A8, func_151D10E4, func_151D15D0
(plus the already-C users of D_800AB008/D_800AB020/D_800AB024, which would switch to literals).

Ready at score 0 (literal floats, exact bits): func_151CD674 (this dir).
Its constants: D_800AAFC0 = -0.25500003f, D_800AAFC4 = -0.12750001f (golden hoists them out of the loop,
so externs cannot match). Ship = all owners in C, then `[0x24F9A0, .rodata, game_1FA770]` + conker.ld swap.
