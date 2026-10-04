# game_176A00 campaign (2026-10-03) -- block 24A240 SHIPPED (uncommitted at time of writing)

Shipped in C: func_1514AB5C, func_1514B034, func_1514B364, func_1514B8E4 (block owners) +
func_1514BF9C, func_1514C678. yaml `[0x24A240, .rodata, game_176A00]`. 4 pragmas left:
- func_1514C858 -- mism 2: identical except one spilled float's stack slot (ours 0xA0, golden 0xA4).
  Same shape as matched func_1514C678. Draft: cd9.c (whole TU).
- func_1514A594 -- golden keeps one float local in memory; plain local 79, `f32 t[1]` fixes frame but 23
  and isn't natural. Drafts q1.c/q2.c.
- func_1514BE20 -- mism ~36, frame solved, call-arg setup scheduling left. Drafts bf1.c/bg1.c.
- func_1514A6A0 -- 303 insns sqrt/matrix, not attempted.
