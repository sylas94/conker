# Solo smallest-first session, 2026-10-13 (no agents)

Matched + ROM-gated: func_150DE32C, func_150E75A0, func_150C8600, func_150D765C, func_150DFBD0, func_151C43E0, func_1506B3B8,
func_151B4EA4, func_151B50F4 (game_1E2180 now at 0 pragmas; rodata block 24EE90 migrated with exact-bit literals).

Levers that closed them:
- Local initialised tables (`u8 ids[8] = {...}`, `s32 *tables[2] = {D_x, D_y}`) are copied from a .data image; when the
  image block has only this owner, write the real initialiser and migrate the block as `[0xADDR, .data, <tu>]` (4 done).
- gSPSegment loops: a named `seg = i + N;` right before the macro; a dead `i = 0` in golden means the loop var is i and
  the segment is derived, not a second loop variable.
- One-register temp rotation: add the named local the $v0/$v1 law demands (`u8 idx = D_...`).
- Permuter fakes are HINTS: `new_var = 0` used as a table index -> the honest `table[sel]` while sel is 0; moving an alias
  decl into a block -> an approved sub-struct pointer declared in that block.
- Literal vs extern: a scale constant loaded BEFORE the a1/a2 mtc1 param moves = a .rodata literal (an extern load can't
  pass the stack-home stores). Shared-block functions then need a whole-block campaign (24EE90 done, 24E840 staged).
- -g3 line boundaries are scheduling barriers: two statements on ONE line schedule together (seen on func_151C6D70).
  Not used for a match (treated as a forcer).

## Parks
## func_151D42E8 (game_200930) -- mism 2
Ternary `angle = arg1 ? ((u16)(u32)(func_150484A0(arg1[0], arg1[2]) * D_800AB1D0) - 0x4000) | 1 : 0;` gives golden's redundant b.
Residue: golden reloads arg0 (`lw a0,0x28(sp)`) before mul.s; ours after `lui at,0x4F00`. Refuted: if/else, operand order,
block-scope extern in branch/around call, f32/u32 temps, struct17 params, s32 angle. Permuter 15 min: no gain.
## func_1504ADD0 (game_77AD0) -- mism 38 (fastscore)
Golden hoists 0x28, bound 25 and &sp48 into s-regs, re-li's 0x77; ours hoists 0x77. switch / pointer loops / decl orders refuted.
## func_151E50C8 (game_20AE20) -- mism 23
23-byte s8 copy D_8008FE54 -> D_800E0BE0. Golden peel: 3 loads first (reverse) then 3 stores via one lui; body in natural
0,1,2,3 order. Best: countdown pointer walk `for (i = 23; i != 0; i--) *dst++ = *src++;` (23). Index loop 88, struct copy 168.
## func_1503EB78 (game_6B320) -- mism 16 honest / 5 needs `arg2 *= D_80098920` (BANNED param reuse)
Golden computes the product in arg2's own register (mul.s f14,f14,f2) -- the param-reuse signature.
## func_1507E7E4 (game_AB760) -- mism 5
Needs u8/u8/u16 params (remove the later `extern void func_1507E7E4(void *, s32...)`), extra local `s32 cur = arg0[0x6F]`
(frame slot), residue = beq operand order on cur compares + t8/t9 on the u16 compare. Permuter 15 min: nothing.
## func_150229E4 (game_49D30) -- mism 21
`s32 owner; u8 id;` register rotation (owner a1, id a2, count a3 in golden). Permuter only found fakes (id = 4 reuse).
## func_15167C58 (game_1944C0) -- mism 48
Decl order p, sp5C, sp50, gfx, mode gives golden's frame (sp50 0x50, sp5C 0x5C, mode 0x48). mode must be a two-if /
else-if (memory-resident). Residue: temp regs numbered one lower than golden throughout. Permuter: only `(x != 0xFF) != 0` fake.
## func_150AEB9C (game_DBA60) -- mism 85 (anti-tamper checksum + spawn loop)
Golden keeps list index in s3, entries via D_800886E4 reloaded each iter, no s-reg address hoists. Ours hoists.
## func_151AE984 (game_1D92F0) -- mism 7
Needs prototype line 11 arg4 u8; locals `f32 k; f32 vel[3]; f32 c; u32 b; u32 a; f32 f;` with k = D_800A9D8C first and
c = 4th rand. Residue: golden loads D_800A9D8C before the a1/a2 mtc1s (prologue scheduling).
## func_150234A4 (game_49D30) -- BANNED construct required
Golden spills the key into arg0's home slot (0x28): original code is `arg0++` (param overwrite, owner-banned). Index loop
version: 39, structure otherwise exact.
## func_15114B94 (game_13D350) -- mism 38
Free-slot + trailing-trim. Needs 2 declared locals (frame 0x28). Best: locals count, keep (u32) with `count - 1` index.
Residue: register allocation (arg0 in a2, entry in a1, unk94 loaded straight into a0).
## func_1506D584 (game_981E0) -- mism 24 (old park note was wrong: it's float->u32 conversion, not soft trunc)
`u16 val = cmd; if (val != 0xFFFF) val = val / divisor;` + prototype func_1507E7E4(struct127 *, u8, u8, u16, s32) + locals id/state.
Residue: golden loads cmd inside the branch but hoists its lui above the lbu test; cmd-inside versions score 61.
## func_1514BE20 (game_176A00) -- mism 43
Lerp toward pos+100y by unk15C, normalise (func_15145128), prev = pos + dir*100 else prev = pos. Locals top, mid, f32 t, dir,
len, len2 give golden's relative layout but all slots are 8 lower (frame 0x58 vs 0x60): two unknown 4-byte locals declared last.
Must remove the later `extern void func_1514BE20(void *);` in the TU.
## func_151C6D70 (game_1F3780) -- mism 4 (2 with a same-line layout, NOT shipped)
`(b % 1U) + 0xFF` keeps golden's store of the 2nd rand() (a RAND_RANGE(0xFF,0xFF) shape). Locals scale[2], size, b, a.
Residue: size in $f2 vs golden $f18 + one lui order. NEW OBSERVATION: at -g3 putting `size = ...; func(...)` on ONE source
line changes scheduling (fixes the lui order) -- line boundaries act as scheduling barriers. Treated as a forcer.
## func_151C43E0 (game_1EF500) -- mism 10
Ray query like game_124920 func_150F78B4. Needs two named locals declared after `ray` (pos, solid) for golden's 0xE0 frame.
Residue: result/flags registers swapped (t0 vs v1). Assignment position, type, named flags all refuted.
## func_150183D0 (game_45880) -- handwritten (j to glabels, addiu zero-init, full s-reg save) -- skip
## func_150EFA4C (game_11C2B0) -- mism 42
Needs `(s32)actor->unk1D4` (struct127 types it as a pointer -> scaled add), locals link/owner/sub/actor/u8 idx.
Residue: temp numbering + li v0,1 placement; single-return form is worse (60). Permuter only found an uninitialised-var fake.
## func_15188E48 (game_1B5CC0) -- mism 62
Matrix-history shift with bcopy. `for (j = 0; j < count; j++) { i = j + 1; if (count == i) {...} }` gives the frame + loop
shape; locals src/total help a little. Residue: count/cur/prev register assignment.
## func_15063254 (game_83300) -- old park; frame needs 2 unknown slots (0x4C, 0x28); structure exact
## func_16000590 (debugger) -- mism ~96: golden keeps arg0 in s5 across calls, ours reloads its home
## func_150C5568 (game_F2820) -- mism 35: kill u8 + struct17 d/v; one unknown 4-byte memory local declared first
## campaign 24E840 (game_1D92F0) -- func_151AE984 + func_151AF388 MATCH with literals; blocked on func_151AECA0 (372 insns).
   Staged in tools/nearmiss/pending_repo_changes/campaign_24E840_game_1D92F0/.
