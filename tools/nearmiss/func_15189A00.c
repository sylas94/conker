// func_15189A00  (game_1B6DB0, 1212 bytes) -- NEAR MISS, best score 2010.
// Parked model lives commented-out in conker/src/game_1B6DB0.c above the pragma.
//
// ============================================================================
// WHAT THE FUNCTION IS
// ============================================================================
// A particle-emitter tick for the spawner object created by func_15189900 (same TU).
// It is a near-clone of two ALREADY-MATCHED functions:
//     conker/src/game_17CAF0.c : func_15151A38, func_15152F70   (same emit loop)
//     conker/src/game_175250.c : func_15148F1C                  (same 3 param structs)
// Read those first; they carry the exact struct models for the func_15147DA0 call:
//     pos   { f32 x,y,z; s16 unkC; s16 unkE; s32 unk10; u8 pad14; u8 unk15; }  0x18
//     spawn { f32 unk0,4,8,C,10,14; u8 unk18,19,1A,1B; s16 unk1C; s16 unk1E; } 0x20
//     style { s32 unk0..unk18; u8 unk1C; u8 unk1D; }                           0x20
// func_15147DA0's own body (matched, game_175250.c:41) confirms it returns the object
// whose ->unk98 the memcpy tail writes through.
//
// The spawner object is Struct15189900Obj from this TU with the 0x50-byte parameter
// block at +0x10 expanded:
//   +0x01 u8 (arg14)          +0x0C u8 (arg13)
//   +0x10/12 s16 yaw base/half-range      +0x14/16 s16 pitch base/range
//   +0x18/1C/20 f32 pos base              +0x24/28/2C f32 pos jitter
//   +0x30/34 f32 speed base/range         +0x38/3C f32 rate base/range
//   +0x40/44 f32 spawn.unk0 base/range    +0x48/4A s16 spawn.unk1B base/range
//   +0x4C/50 f32 spawn.unk10 base/range   +0x54/56 s16 pos.unkC base/range
//   +0x58/5C s32 pos.unk15 base/range     +0x60 s16 retrigger timer (-= D_800BE9E4, +50)
//   +0x64 f32 emit accumulator            +0x68 f32 low-Y copied to part->unk98[0x48]
//   +0x6C s32 handle (func_151464B8)      +0x70 u8 flags (&1 -> arg4 = 0xA else 0)
//
// ============================================================================
// FRAME MODEL (this part is SOLVED and reproduced exactly -- do not re-derive it)
// ============================================================================
// frame 0x148 =  args 0..0x40 | 8 bytes compiler temp | f20-f28 0x48..0x70
//                | s0,s1,s2,ra 0x70..0x80 | NAMED LOCALS 0x80..0x148 (0xC8)
// Named locals are laid out first-declared-highest, packed by natural size/alignment,
// with ~0x28 bytes of unnamed compiler temps below them.  The four anchors pinned by
// golden's own stack offsets are:
//     style @ 0xC8 (0x20)   lowY @ 0xE8 (f32)   spawn @ 0xEC (0x20)   pos @ 0x10C (0x18)
// which forces EXACTLY 36 bytes of scalars declared before `pos` and EXACTLY 32 bytes
// declared after `style`.  That is why the declaration list is interleaved -- the same
// pattern the matched siblings func_15152F70 / func_15148F1C use.
// Calibration used: `mips-linux-gnu-objdump -d conker/expected/build/src/game_17CAF0.c.o`
// on func_15152F70 (frame 0x108 = 0x40 args + 0x28 fp + 4 pad + 0x24 gp + 0x78 locals).
//
// ============================================================================
// MEASURED SPELLINGS
// ============================================================================
//  2595  first honest spelling: no `handle`/`distSq`, structs first, `- obj->unk12`
//          -> frame came out 0x140 (8 bytes of named locals short) and every stack
//             offset was +4; that alone was ~500 of the score.
//  2045  + `s32 handle` and `f32 distSq` above `pos`, `ang1/ang2` moved above `pos`
//          -> frame 0x148, EVERY stack offset exact.  Residual = register rotation.
//  2010  + `ang1` rewritten `obj->unk10 - (rand%(u32)(r*2+1) + -r)` (see below), and
//          `cam` split into `ent`+`cam`
//          -> ang1's negu/subu/subu triple now matches golden's shape exactly, BUT
//             splitting the pointer local COST the dead `addiu v0,v0,0x2F8` row.
//        (untested at park time: cam-only + the ang1 fix, which should be ~1975)
//
//  WARNING: the model parked in game_1B6DB0.c is the 2010 model with `struct108 *ent`
//  swapped for a `u8 idx` local (frame-neutral: idx@0x12B, ang1@0x128, ang2@0x126, pos
//  still @0x10C).  That swap was queued behind the build lock and never landed before the
//  tree had to be restored, so the parked spelling itself is UNMEASURED.  To reproduce
//  2010 exactly, replace `u8 idx;` with `struct108 *ent;` and use
//      ent = &D_800DBFF0[D_800BE630[i]];
//      cam = (struct17 *)&ent->unk2F8;
//  To reproduce 2045, drop `ent`/`idx` entirely, add `s32 handle;` as the FIRST local and
//  hoist `handle = obj->unk6C;` out of the guard, and revert ang1 to the `- obj->unk12`
//  form.
//
// THE ang1 RESULT IS THE MAIN TRANSFERABLE FINDING:
//   golden:  negu t9,v1 ; subu t8,t4,t7 ; subu s1,t8,t9        i.e. (a-b) - (-c)
//   `obj->unk10 - ((rand % (u32)((obj->unk12*2)+1)) - obj->unk12)`
//        -> IDO reassociates a-(b-c) into (a-b)+c  ==> subu/addu   WRONG
//   `obj->unk10 - ((rand % (u32)((obj->unk12*2)+1)) + -obj->unk12)`
//        -> IDO reassociates a-(b+(-c)) into (a-b)-(-c) ==> negu/subu/subu   RIGHT
//   So an explicit unary minus on the range is required; the two forms are numerically
//   identical, which is why only the diff distinguishes them.
//
// THE DEAD `addiu` IS A -g3 ARTEFACT:
//   golden's loop loads 0x2F8/0x2FC/0x300 off the struct108 base and THEN computes
//   base+0x2F8 into a register that is never read.  That is IDO materialising a named
//   pointer local whose uses were folded into the load displacements.  It appears iff
//   there is exactly ONE named pointer local in the loop:
//       cam = (struct17 *)&D_800DBFF0[D_800BE630[i]].unk2F8;   -> addiu present
//       ent = &D_800DBFF0[idx]; cam = (struct17 *)&ent->unk2F8; -> addiu GONE
//
// ============================================================================
// THE BLOCKER (two symptoms, probably one cause)
// ============================================================================
// (1) +1 INTEGER TEMP-REGISTER ROTATION, uniform from the emit loop onward.
//     Golden's preheader runs t2,t3,t4,t5,t6,t7,t8,t9,t1,(t3,t4,t5,t6,t7);
//     ours runs   t3,t4,t5,t6,t7,t8,t9,t1,t2,(t4,...).  Pool is t1..t9 (9 wide).
//     Root cause is upstream, in the camera-proximity search loop:
//        golden coalesces THREE live-range pairs and spends 3 t-registers:
//            v0 = D_80082FA0        then &D_800DBFF0[idx]
//            v1 = obj->unk60 reload then the D_800BE630 walk pointer
//            a0 = loop index `i`    then the D_800BE630[] byte
//            a1 = found, a2 = D_800DBFF0, a3 = end ptr, t0 = 0x9A0, t1 = base, t2 = mflo
//        ours coalesces only two and spends 4:
//            v0 = obj->unk60 reload then &D_800DBFF0[idx]
//            a3 = D_80082FA0        then 0x9A0
//            a0 = found, a1 = D_800DBFF0, a2 = end, v1 = ptr,
//            t0 = i, t1 = base, t2 = byte, t3 = mflo      <-- one t too many
//     i.e. golden reuses the DEAD loop-index register for the loop-carried array byte;
//     we allocate a fresh one.  Everything after inherits the +1.
//     Spellings tried on the loop, all leaving the rotation at +1:
//        `for (i = 0; (i <= D_80082FA0) && (found == 0); i++)`   (matches golden's
//            two-test exit order and its `bltz` pre-test exactly -- this part is right)
//        index expression inlined vs. hoisted into a named `u8 idx` local
//        `cam` alone vs. `ent`+`cam`
//     NOT yet tried: making the walk explicitly pointer-based; swapping the declaration
//     order of `i`/`found`; giving `found` a non-s32 type; a named local for the
//     obj->unk60 reload (which is the pair golden coalesces with the walk pointer, and
//     is the most promising remaining lead).
//
// (2) THREE UNFILLED DELAY SLOTS = the entire 16-byte .text shortfall.
//     Golden leaves `nop` after the jal that follows each of
//         pos.unk8   = obj->unk20 + (rnd * obj->unk2C);        [swc1 0x114]
//         spawn.unk0 = (func_150ADA68()*obj->unk44)+obj->unk40; [swc1 0x0EC]
//         spawn.unkC = horiz * sin1;                            [swc1 0x0F8]
//     but DOES fill the slot after
//         spawn.unk10 = (func_150ADA68()*obj->unk50)+obj->unk4C;[swc1 0x0FC]
//     with that store.  We fill all four.  The 2nd and 4th cases are byte-for-byte the
//     same instruction shape (lwc1,lwc1,mul.s,add.s,store into the same struct, followed
//     by the same callee func_150ADA20) and differ only in FP register numbers, so no
//     source spelling separates them -- this is an IDO scheduler state difference, most
//     likely downstream of (1).  Fix (1) first; do not chase (2) on its own.
//
// (3) minor, one row: golden does `lw v0,0x98(v0) ; addiu a0,v0,0x48` for the memcpy
//     destination, we do `lw a0,0x98(v0) ; addiu a0,a0,0x48`.  Golden is materialising
//     an intermediate into the (now dead) return-value register, i.e. it very likely has
//     a second named local `dst = part->unk98;`.  Budget note: adding `dst` below
//     `style` costs 4 bytes, so `horiz` must be dropped at the same time (write
//     `(speed*sin2)` twice -- CSE keeps the `mul.s f2,f20,f26`, exactly as the matched
//     func_15152F70 sibling does).  UNTESTED -- this is the cheapest next experiment.
//
// ============================================================================
// NEXT EXPERIMENTS, IN ORDER
// ============================================================================
//  1. Restore cam-only (drop `ent`) + keep the `+ -obj->unk12` ang1 form.  Expected to
//     recover the dead addiu row and land near 1975.  This is the correct base.
//  2. Swap `horiz` for a named `u8 *dst` below `style` (fixes (3), budget-neutral).
//  3. Attack the rotation: give the obj->unk60 reload a named local so its live range
//     can coalesce with the walk pointer, and/or rewrite the search as a pointer walk.
//     Watch ONLY the t-register column in the preheader -- when it starts at t2 the rest
//     of the function should collapse.
//
// NOTE: no shared header was edited and none needed shadowing; every symbol this needs
// (D_800BE630, D_800A73A0, D_800A73A4) is already in undefined_syms_auto.txt and just
// needs a file-local `extern`.  functions.h's `u8 func_150ADA20(void)` and
// `f32 func_151423D8(u8)` are both correct for this call site.
