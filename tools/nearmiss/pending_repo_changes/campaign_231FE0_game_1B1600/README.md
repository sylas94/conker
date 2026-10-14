# Campaign: rodata block 0x231FE0 (game_1B1600)

Block 0x231FE0..0x232040 (0x60 bytes) = `D_8008D520` (Gfx[3]: gSPMatrix(D_80089470), E7 pipesync, DF enddl),
`D_8008D538` (Vtx[4] quad), and the literal `0.017453292f` (PI/180) at `D_8008D578` + 4 bytes pad.
`D_8008D520` is referenced from data table 22FF90 (by symbol, so a C definition still links).

Owners: func_15187D6C (Euler rotation matrix) and func_15187A98 (12-petal display list, refs D_8008D538).

- func_15187D6C.c -- fastscore 0 with the literal (`x *= 0.017453292f`); with `extern f32 D_8008D578` it is 8
  (golden hoists the literal's lui above the a1..a3 mtc1 moves -- literal tell). Decl order sx,cx,sz,sy,cy,cz
  gives golden's slots (cx/sy live in f20/f22 but still own slots 0x40/0x38). Params are scaled in place
  (`x *= k`): golden stores them to the param homes, so this is the original's own shape.
- func_15187A98.c -- 19. Residue: (1) frame 0xF8 vs 0x100 -- every slot is 8 lower, so golden has an 8-byte
  memory local declared before `base` that no instruction touches (scalars here get no slot; only arrays do);
  (2) a cyclic temp rotation in the gDPSetPrimColor..gSPVertex macros (golden _g=v1/dur=a1, ours a0/v1).
  `s32 dur` + `s32 alpha` named locals got it from 27 to 19.

To ship: both at 0, then define D_8008D520/D_8008D538 const in the TU (before func_15187A98), add
`[0x231FE0, .rodata, game_1B1600]` to conker.us.yaml and swap the conker.ld line for 231FE0.rodata.s.o(.rodata)
-> build/src/game_1B1600.c.o(.rodata); check the TU .rodata is exactly 0x60.
