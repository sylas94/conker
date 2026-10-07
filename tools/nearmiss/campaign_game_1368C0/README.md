# game_1368C0 campaign (2026-10-03) -- SHIPPED except func_15109848

Shipped (uncommitted at time of writing): func_151094FC, func_15109FB8, func_1510A40C in C; the TU
emits blocks 246F70+246FE0 as ONE .rodata (yaml `[0x246F70, .rodata, game_1368C0]`, the
`[0x246FE0, rodata]` line removed). func_15109848 stays GLOBAL_ASM; its 7 pool floats are supplied
as named `const f32 D_800A2634[1]`..`D_800A264C[1]` stand-ins in golden position (they're the first
pool after the aggregates, so order holds). When 9848 matches, delete those stand-ins and use literals.

func_15109848 (hit effect; func_15130374 0x70 descriptor + func_15152B38 0x74 record):
mism 94, n=246/246, frame 0x110 exact; structdiff 0 opcode / 0 immediate rows, ONE instruction
placed differently (`lw t0, arg0` one slot early around `fx.unk58 = A | (B|5) | 0xC200`), rest a
consistent temp renaming (92 rows). Refuted: 120 operator orders/groupings, 320 ternary/type combos,
242 statement moves, 60 store reorders, callee proto width, u32 field, 76 declaring-block placements.
Full all-C TU with the 94 version: game_1368C0.allC_9848_at_94.c

2026-10-06: TU-aware permuter, 30 min / ~13.7K iterations from the 94 version (REQUIRE_FRAME=272). Its
best (permuter 685 -> 205) is `fx.unk58 = (short)(<flag ORs>) | 0xC200;` -- but that is 154 by fastscore
(n=248/246): the permuter's weights bought register-row wins with 2 extra instructions, a dead end.
Its other output split the store into `fx.unk58 = 0xC200; fx.unk58 = ... | fx.unk58;` (forcer).
Honest variants of the hint also lose: `s16 flags` / `u16 flags` local = 188-195 and frame 0x118.
