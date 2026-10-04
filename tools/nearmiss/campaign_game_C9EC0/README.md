# game_C9EC0 / block 243B90 campaign (2026-10-03) -- PARKED, nothing shipped

func_1509D780 and func_1509D8FC: MATCHED (best.c). func_1509D180 (script dispatcher, jtbl): mism 166,
frame/homes/n exact (d180_candidate_full.c emits the exact .rodata layout). Residue = three as1
delay-slot/scheduling choices: case 34 beqz slot (golden lwc1 f4,0x90; ours beqzl+lw v0), case 5
tail (golden `sw; b; lw v0`, ours `b; sw`), case 24 `move a0,v0` order. Try the block-scoped
declaration lever (fixed similar slots in func_150F34F4 / func_150F887C) on those three cases first.
Fallback impossible: D180's jtbl holds its own .L labels. Block can't migrate until D180 = 0.
Notes: `0xE000 | 4` (not 0xE004) chosen for temp numbering; D8FC case 31 falls through to 30 (golden).
