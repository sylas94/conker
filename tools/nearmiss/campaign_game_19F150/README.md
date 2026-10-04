# game_19F150 / block 24BA90 campaign (2026-10-03) -- PARKED, nothing shipped

Block needs BOTH owners in C (jump table of 720C4 precedes 725FC's pool, so the named-stand-in
fallback can't hold order). func_151720C4 (sprite DL builder, jtbl) = MATCHED (f20c4_MATCH.txt).
func_151725FC (sloped quad) = mism 142, frame/n exact; residue ~10 insns in the first block
(golden loads+squares v[0][1] into f2 before the `b == 0` branch; ours squares after) which
also adds a duplicate 1e8 pool entry. ~600 variants refuted. NOTE best.c's 725FC carries an
UNUSED `f32 y` frame pad -- banned, must not ship as-is.
Also: already-C func_15172B20 moves a cosf spill (0x3C->0x38) when switched to literals.
Bonus func_15171D4C mism 67 (needs Obj15171CA0 as pad0[0x10]; Vtx vtx[4]; -- mk3.py).
IDO laws found: only loops whose counter is not reused get unrolled; reading v[0][2]
instead of a scalar reproduces a mov.s copy + late store.
