# Solo smallest-first, 2026-10-14 (continuation of NOTES_solo_smallest_2026-10-13.md)

All matches left UNCOMMITTED; force-clean ROM gate exact (842e3d34 / 4cbadd3c) after installing them.

## Matched
- func_1507E3C0 (game_AB760), func_1501E1B4 + func_1501E400 (game_49D30), func_151AC408 (game_1D92F0),
  func_150F1A00 + func_150F20F0 (game_11C2B0), func_15088F30 (game_B3020) -- see the 10-13 notes / session.
- func_1511AF30 (game_142560): `arg0->base += (diff < 0.0f) ? -1 : 1;` -- a ternary, NOT `step = 1; if (..) step = -1;`
  (that gives bc1fl instead of golden's `bc1f; nop; b; li -1`). The wobble update reuses the named `diff` local
  (`diff = target - wobble; wobble += diff * k`) -- that puts the subtract in $f2. Rodata literals reached as `extern f32`
  (loads are not hoisted, the block is shared with still-asm siblings).
- func_1508B2A8 (game_B3020): recursive flood-fill. Keys: `node = id + (Node *)D_800D2350` (addu order);
  `dist = dz; dist = dx*dx + dist*dist` (reusing the dz local puts the sum in $f2, a fresh local gives $f12);
  link test `if (node->links[j] != 0xFF) { link = node->links[j]; if (!visited(link)) recurse(node->links[j]); }`
  -- the permuter hint (compare the field, not the local) turned into this honest nesting. Original-game BUG: visited
  bit is `1 << (id & 3)` with byte `id >> 3`.
- func_1511617C (game_142560): a named `f32 delta` local in both arms (`delta = -vel; vel += delta * k`) fixed FP
  rotation AND frame size; pass `arg0->y` (not the `oldY` copy) to the call so golden's reload of oldY appears.
- func_1503E260 (game_6B320): index loop `bones[i]` (IDO strength-reduces to the s1 walk pointer, bones itself stays
  a temp in v0) -- a hand-written `bones++` walk puts the pointer in s0. Then NO `p = &D_800C6660[arg0]` local: IDO
  CSEs the repeated `D_800C6660[arg0].f` into s7 anyway, and dropping the named local moved the call-spill slot
  0x38 -> 0x3C (the last 2 diffs). A pointer local you can delete for free can still move a spill slot.
- func_15035FE8 (game_61D10): golden's `blez count` guard + pointer-compare latch is an INDEX loop strength-reduced by
  IDO (`for (i..) { e = &D_800C3F08[i]; if (e->unkB != 0) continue; ...}`), same shape as sibling func_15035D6C.
- func_1000E934 (init_B1B0): row pointers stepping 0x40 = `[3][16]` 2-D tables (D_800418B0 cast, as game_AC030 does,
  since variables.h types it s32[]); the 4 bytes of frame short were a SEPARATE index `k` for the final 12-entry loop.
- func_151D75C4 (game_204660): `actor->unique_id != link->id` (right operand emitted first); `p = &arg0->unk28;`
  assigned BEFORE `link = &arg0->link;` (IDO rematerialises p per arm, spills it across the call).
- func_1502F264 (game_58F80): reuse one bone pointer for the NULL test and the `+= unk5C` advance
  (`f32 (*bone)[4][4]`); a separate mtx local leaves the 1D4 value in a1 instead of v1. Original copies unk76 twice.
- func_15083568 (game_AEB40): permuter hint `i < (&D_80086CC4[arg1])->unk4` -> honest form has NO set local at all
  (`D_80086CC4[arg1].unk0` / `.unk4` read directly). Needs header shadow (functions.h says void) and `arg1--` in
  place -- golden keeps arg1-1 in the param's own s-reg and passes `arg1 + 1`; every idx-local spelling is 80+.
  Same idiom as the already-shipped sibling func_150836CC. FLAG FOR REVIEW: parameter decrement.
- func_151B4A14 (game_1E0560): frame 0x10 short = FOUR more named locals (-g3 slots top-down: 2 between ret and
  model, 2 after the colour outs). Named mode1/mode2/full/alpha constants+copy fit. Last residue (alpha in t8 vs v0)
  was a TYPE: the colour outs are u32 (permuter hint `unsigned int a`), with func_1502EC34 taking u32 *.
- func_1505DDA8 (game_83300): s8 return, `u8 i` loop with early `continue` on `interaction_state == 0` (keeps the
  global bound in a register); func_1505DF10's definition takes a 6th arg (both callers pass 0).
- func_150F1B48 (game_11C2B0): `((Tilt *)&D_800CC298)->f` as a macro -- an explicit cast expression keeps the address
  in a register where a named pointer local is copy-propagated.
- func_15156028 (game_182C30): block-scoped `s32 a = arg1[0] - D_800CC2D0;` declarations-with-initialisers inside the
  arm fixed the scheduling.
- func_1515942C (game_185560): golden OR order is `m5 | m1 | m2 | m3 | m4`, not source order m1..m5.
  (gate 3: these four ROM-exact 2026-10-14.)

- func_15114F44 (game_13D350): display-list sanity check. The 12-byte records are `u32 (*list)[3]` indexed
  `list[i][k]` -- IDO strength-reduces it with the base copied through v0 (`lw v0; ...; or s0,v0` in the blez delay
  slot). A hand-written `p += 3` walk is 3 (blezl instead of blez).
- func_1511473C (game_13D350): early `return` on `arg0 == NULL || arg1 >= D_800DBEF0` (the nested-if form is 4);
  0x137 is a flag byte inside struct127's pad134, read as `((u8 *)arg0)[0x137]` like game_83300 does.
  (gate 4: both ROM-exact 2026-10-14.)
- func_151CCD1C (game_1F4650): spawn descriptor; copying sibling func_151CAB78's block-local Emitter/Extra typedefs
  closes it. Local order `sp88, sp2C, temp_v0` (-g3 slots).
- func_15064A14 (game_90840): first draft matched -- if/else-if chain on partner->id with a `big ? : ` ternary.
- func_1000E17C (init_B1B0): 12 -> 0 by dropping the `type` local and repeating the expression via a
  `VOICE_TYPE(v)` macro in BOTH the first and third loops (IDO CSEs it; a named local changes const register choice).
  Permuter hint: the inlined expression.
  (gate 5: all three ROM-exact 2026-10-14.)
- func_1518A094 (game_1B74A0): attach-to-bone update. Keys, in order of effect: (1) the 0x188 test is `at->target`
  (attach block at 0x170, target at +0x18); (2) the permuter hint moved `u8 ok` INTO the handler block -- that
  put `at` in a spilled temp (v1 + sw 0x3C) instead of an s-reg, as golden has; (3) `if (target ok) {..} else
  return 0;` + `if (handler(arg0, &ok)) { if (!ok) return 1; } else return 0;`; (4) frame/slots closed by an
  `f32 *out` local in the matrix block, reassigned per output triple (`out = &arg0->unk34; ..; out = &arg0->unk40`).
- func_15189FF0 (game_1B74A0): spawn + memcpy. Params are u8 and the callee prototype takes u8 (golden andi's a3 in
  a register, lbu's the stack ones); `if (obj) { u8 *attach = obj + 0x170; memcpy(attach, ..) } else return NULL;
  return obj;` -- the block-scoped destination local is what the permuter found (6 -> 0).
  game_1B74A0 COMPLETE (0 pragmas). (gate 6: ROM-exact 2026-10-14.)
- func_1516FBCC (game_19A8B0): particle fade/grow/colour-blend. First half (fade) matched first try with plain
  field reads (the post-store reload of fadingIn happens naturally). Tail: ONE reused local `v` for alpha, growth
  and blend, each spelled load-then-update (`v = growX; v *= dt; sizeX += v;`, `v = blend; v += dt;`), plus
  `v *= 2` AFTER `arg0->blend = v` (66 -> 8 -> 0). Original BUG: sizeX tested twice (`sizeX <= 0 || sizeX <= 0`).
- func_151B9F00 (game_1E73B0): spawn descriptor. Typed Spawn/Extra structs; decl order obj, desc, extra (-g3);
  arg1 is s32 with a u8 callee prototype (golden andi's a3 at entry); `obj + ((Obj *)obj)->unk50 + 0xF8` (addu
  order); and the struct127 index `idx` as a BLOCK-scoped local around its if -- that stops IDO hoisting the
  div above the descriptor stores (26 -> 0).
  (gate 7: both ROM-exact 2026-10-14.)
- func_15030E08 (game_5D2C0): node-list walker. The mask test SKIPS when the bit is set
  (`(obj->unk74 & m) == m` -> continue); the S15030F94 struct moved above it (gained unk4).
- func_15033838 (game_5D2C0): effect toggle. Golden's 0x20 frame has NO -g3 local slots -> drop the u16 `id`
  local (164 -> 1); the leftover 1 was my inverted `kind == 6`. game_5D2C0 now 8 pragmas.
  (gate 8: both ROM-exact 2026-10-14.)
- func_150EB484 (game_1188E0): header-shadow `D_800D3098` as a POINTER (`struct178 D_800D3098[73]` in
  variables.h is wrong); `id = D_80088AA0[i]` local in an s-reg; decls `i, id, obj` (frame 0x50 = 4 slots).
  Its own prototype in the TU becomes s32.
- func_15019CC8 (game_45B80; old park "best 2868", arg1 homed instead of s0): write the camera block as REAL
  struct indexing -- `&((Cam *)D_800BE628)[arg1].vp[D_800BE9C0]` / `.proj[D_800BE9C0]` (0x180-byte struct, Vp[2]
  at 0x40, Mtx[2] at 0x100). Flat `D_800BE628 + arg1 * 0x180 + ...` makes IDO CSE the product across the calls
  and spill it; array indexing recomputes it each time and keeps arg1 in s0 (129 -> 0 first try).
  (gate 9: func_150EB484 + func_15019CC8 ROM-exact 2026-10-14, re-run after a PC restart.)

## In progress: game_1188E0 whole-TU campaign (rodata block 245F50)
Block 245F50 (0x70 B) is referenced ONLY by game_1188E0's last three functions -> once all three match, migrate
with `[0x245F50, .rodata, game_1188E0]` + conker.ld swap; the vec3 tables D_800A1490/149C/14A8 and u8[4]
D_800A14D8 must be defined in the TU in order before the literal pool. fix_1188E0c.py = TU edits (pointer
shadow, u32 func_150ADA20 shadow, Gate struct fields 0..8, u8 prototype for func_150EBC80).
- func_150EBC80: 0 with literal `1.6409999f` (bits 3FD20C49; NOT 1.641f) and decls pos, step, i, spark.
  me/full_150EBC80.c. An extern can't match: golden hoists the VALUE into f26 (only a literal allows that).
- func_150EB8C4: 32. Same 0x7C spawn layout as Func150F892CSpawnA. Only the three `1.0f` stores (0x1C/20/24)
  schedule after the int stores; source order, chaining and in-loop placement don't move them. Permuter running.
- func_150EB614: 59. Door spring/damper; state = low 2 bits of 0x73 written by a two-statement macro (`&= ~3;
  |= s`, golden's two sb); `return` early for state 3 and else-branch for state 2 (block last);
  `dz*dz + (dx*dx + dy*dy)`; loads accel, damp, ang, vel. Residue: FP temp pool shifted ~3 regs (vel f16 vs f2).

## Parked
- func_150888A8 (game_B3020) -- 16 only with a redundant double read (`link = links[j]; if (links[j] != 0xFF && link != from)`),
  a forcer; honest nestings 33-59. Needs `s8` third param (prototype at the top of the TU must change to s8 too),
  `if (next->dir != want) {best..} else alt = link;` (beql target is the else arm), idx+base addu order.
- func_151E4EE8 (game_20AE20) -- 81: one extra `move v0,v1` (u8 alpha local gets IDO's unsigned float conversion, golden
  holds alpha and the clamped sum in the same reg). Permuter run started.
- func_1000B060 (init_A420) -- 18: locals `s16 angle, hi; f32 d; s32 raw` with `angle = raw; if (0<z) angle = +-0x80 - (s16)raw`,
  `angle = (s8)(angle + offset)`, `angle += angle`. Residue: temp numbering (golden adds into a fresh temp).
- func_15016850 (game_43D00) -- 75: golden strength-reduces the index away (LFTR: bound `count*0x30` recomputed in each
  path). Neither the index form nor an explicit byte-offset loop reproduces it. handle must be the 4th declared local (0x50).
- func_150E8930 (game_113D60) -- 6: takes NO params (golden never spills a0) although func_150E88C0 passes one -> forward
  decl must become `extern void func_150E8930();`. Needs a typed func_15169260 prototype via header shadow. Residue:
  D_800DCDC4 tests use $v1 not $v0. Permuter run started.
- func_15031070 (game_5D2C0) -- 49: golden keeps `unk1E` in v0 then `move a1,v0`; IDO forwards the load into a1 (same
  wall as the func_1514654C note in game_16EE20).
- func_1512DD50 (game_15B200) -- 90: spill/frame (0x50 vs 0x48) bound; local declaration order does not move the frame.
- func_1509DBBC (game_C9EC0) -- skipped: paths return an undefined v0, part of the parked C9EC0 campaign.
- func_1515452C (game_17CAF0) -- 52 (`f32 *dt = &D_800BE9A4` form; conversion shape exact) / 90 (`(&D_800BE9A4)[0]`).
  Golden materialises &D_800BE9A4 in v1 in the ENTRY block (before the sizeY `if`); IDO copy-propagates a dt local
  into `lui at` forms, and the array spelling places it after the if. Permuter only reached 340 with a `new_var` fake
  assigned before the if. Candidate in scratchpad me/full_1515452C.c.
- func_151B0050 (game_1DD500) -- 2. Needs header shadow (functions.h types func_150ADA20 as u8; it is s32 here) and
  `func_150ADA68() * 0` with an INT zero (`* 0.0f` is folded away, golden keeps the mul.s by mtc1 zero). With no extra
  local the four call-temp spill slots sit 4 bytes high; a named `s32 ret` (ret = 1; return ret;) fixes three of them.
  Permuter's 0 is a fake (`pos[ret = 2] = arg4;`). An `f32 speed` local gets the stack exactly right but rotates the FP
  pool. Candidate: scratchpad me/full_151B0050.c.
- func_151C7038 (game_1F3780) -- 92, but that is ONE instruction: golden hoists the `li v0,1` of `return 1` into the
  block before the clamp's first branch. Everything else is exact once the clamp is spelled
  `if (v > 255.0f) v = 255; else if (v < 0.0f) v = 0.0f;` (INT 255 in the assignment stops IDO CSEing it with the compare
  literal, as golden reloads 0x437F). ret locals, wrapping, return types do not move it. Candidate me/full_151C7038.c.
- func_15022024 (game_49D30) -- 13, FP register choice only. `f32 unset = D_80096A14` local is required (golden reads
  the sentinel once although the stores could alias it). Golden: zero f2 / sentinel f12 / field f0; ours rotated by one.
  zero local, chained stores, decl order, value local (111) don't fix it. Permuter run started.
- func_15044B78 (game_71820) -- 92 (shift-dominated). Rotated box test; stack slots all match with locals
  dims/s/c/dx/dy/dz/rx/rz/<one word at 0x24>/half/w/d. Residue: golden interleaves the dims field loads with the
  dx/dy loads (line-boundary scheduling); `dy = py - y; dy += half;` is the closest. Needs header shadow (functions.h
  types func_15048A40 void), the struct moved above the function, unk16 named. Permuter only broke semantics.
- func_1508907C (game_B3020) -- 89. Shape exact (peeled + 2x unrolled 5-link loop); golden keeps all four u8 params in
  a-regs (sw homes, andi to t, or back) and only uses s0 (for the constant 5); ours moves params to s0-s2. Permuter hint
  (read `node->links[i]` everywhere) is worse when spelled honestly.
- func_1500AC14 (game_36680) -- 57. Golden has 6 locals with `size` at 0x5C (i, id first). Golden strength-reduces the
  D_800DDB80 index and keeps D_800BE478 as `i*2`; ours does the opposite. w (tex->width) must be read once before the
  stores. Permuter run started. Candidate me/full_1500AC14.c.
- func_1509BE40 (game_C8950) -- 88. Varargs (needs `#include "libc/stdarg.h"`). Golden stores the second va_arg value
  back to 0x38(sp) (its own vararg slot) and reloads it for the handler call -- not a -g3 local slot; named-param
  spellings are 95.
- func_15114A1C (game_13D350) -- 112. Golden uses fp and an unused s3; permuter outputs only changed semantics.
- func_151CC524 (game_1F4650) -- 111. Same emitter template as func_151CCD1C, two spawns. Every conditional for
  `arg4 ? 0x40 : 0` (ternary / if-else) adds 8 bytes of frame golden lacks; OR order does not matter.
  Needs fix_cc524.py (TU prototype -> all u8). Candidate me/full_151CC524.c.
- func_1508EE0C (game_B3020) -- 81. 0x18-byte trigger records (count at 2, u16 cmds at 8); switch on cmd>>12 with
  case 2/3 (constants hoisted in s4/s5). Golden walks the first (search) loop with pointers (count via a1 walk, cmds
  via v0 += 2) and keeps the masked params in s1/s4; ours uses offsets. e-pointer local is worse (113).
  Candidate me/full_1508EE0C.c.
- func_151412BC (game_16DC80) -- 18, pure a1/a2/a3 rotation (golden j=a1, width=a2, probe=a3). Keys found: outer
  bucket loop is an INDEX loop `for (i = 0; i < 2; i++)` (no entry guard; end compare against D_800DD190 =
  D_800DCE50+0x340); probe sub-struct at node+0x110 (golden hoists that base); zero stores cell[3]..cell[0];
  index spelled `[col + row * W]` (permuter hint, 42 -> 18). Remaining permuter outputs are j/node copy fakes.
  Candidate me/full_151412BC.c.
- func_151A175C (game_1CC440) -- 45. Particle tick (fade/scale/24.8 fixed-point velocity). `p = &arg0->anim`
  local, `vel = p->velHi[k]; vel = (vel << 8) | p->velLo[k];` split (102 -> 45). Golden colours vx=a1, vy/vz=a3,
  x=v1, y=a2, z=a1; ours differs. Candidate me/full_151A175C.c.
- func_1502AB04 (game_57FA0) -- 92. ROM-cache shift: bcopy down + unrolled fill loop. The two data words are an
  8-byte STRUCT copy (lw/sw via $at); u32 index. Residue: golden keeps `count` in s2 across bcopy, ours homes it
  at 0x20(sp) and reloads (param types u32/u8/u16/s16 don't fix it). Needs fix_57fa0b.py (moves RomEntry above).
  Candidate me/full_1502AB04.c. Permuter's 0 is a param alias (`n = count;` used for the bcopy test and loop
  start) -- banned, but it proves the whole residue is count's register allocation.
- func_15147EB8 (game_175250) -- 24. Handler-chain update (start/update/end fn tables D_8008A3E0/3F8/42C). Keys:
  `s32 alpha` block-scoped (arg0 then spills to its home like golden), `path = arg0->path` local, x/y/z zeroed in
  order. Residue: golden computes `ret = !done` BEFORE the end-callback and spills it at 0x18; ours sinks it to
  the return, and the frame is 16 bytes short. Candidate me/full_15147EB8.c; permuter running.
- func_1516F864 (game_19A8B0) -- still 22; the 1516FBCC split-multiply lever (`vel *= dt`) is 25-30. Untouched.
- func_15143E94 (game_16EE20) -- 11. Two-web flag: first flag is s8 `alive`. Entry scheduling residue (golden
  `sb zero,0x37(sp)` before the D_80082FA0 load). Permuter: only `alive = ret = 0` (12) and ret-sinking that
  leaves ret uninitialised. Candidate me/full_15143E94.c.
- func_15147EB8 permuter: only fake was `(new_var = !done)` in the condition. Still 24.
- func_1506E46C (game_981E0) -- 48 (old park note said 4009). Keys: `switch (arg2)`, `id = *arg1 & 0x7FFF`
  (second read, so id stays a live web spilled at 0x18), decls entry, cmd, rand, pitch, chance, id (frame 0x30),
  `if ((cmd >> 24) >= rand) {...} else return 0;`. Residue: case-2 beql delay and the second id (cmd>>16) in v0
  not v1. Permuter: only an `&arg0` alias fake. Candidate me/full_1506E46C.c.
- func_15141A7C (game_16EE20) -- 28 (old 2673). Keys: D_8008A084/D_8008A0B4 called through casts, the call via a
  fn-typed view `((Handler *)D_8008A0B4)[i].fn(...)` and the test via the s32 view (golden reloads the fn pointer);
  the list walk in its own block `{ Node *node = arg0->unk2F4; if (iter(node, 0x1A, &node)) do {...} while (...); }`
  (fixes the preheader order, 39 -> 28). Permuter 0 = `Elem *elem = node->elem;` at loop top + test via
  `node->elem->handler` (a redundant re-read; banned) -- proves the residue is the handler reload in the loop.
  Candidate me/full_15141A7C_b.c.
- func_151ED29C (game_215960) -- 79. Leaf tile-setup DL builder (PipeSync, SetTile x2, SetTileSize). `fmt` must be a
  local (golden reads tex->fmt once and CSEs `F5|fmt<<21`; 181 -> 79). Residue: golden puts masks in v0 and the siz
  temp in a3, ours swaps them; decl order / loop shape / fmt position don't move it. Candidate me/full_151ED29C.c.
- func_150198FC (game_45B80) -- 79 (old 1470). `D_8002AAE8[1 - D_800BE9C0]` is the honest framebuffer index (golden
  sll then negu). Residues: +1 temp rotation from the viewport block on, and golden keeps D_80082F90's value in v1
  (stores `1` from v1, `v1+1` from t3) with lui/at per access where ours CSEs &D_80082F90.
- game_1188E0 campaign: func_150EB8C4 permuter only found the -g3 one-line forcer; func_150EB614 permuter only
  semantics-breaking outputs (run killed by a PC restart at ~9 min).
