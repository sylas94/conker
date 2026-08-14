/* ===========================================================================
 * func_150380C0  --  game_64120.c  --  936 B, frame 0x80, 1 callee, 27 regions
 *
 * ###########################################################################
 * ## THIS FUNCTION IS **SCORE 0**.  IT IS FINISHED C.  IT CANNOT BE SHIPPED.##
 * ###########################################################################
 * Spelling the two constants as ordinary literals -- which is what they ARE --
 *     out[0..2] = -99999.0f;      thresh = 1600000000.0f;
 * gives, measured this wave through make + buildlock + the real asm-differ:
 *     func_150380C0  flags='-R'  score=0
 *     func_150380C0  flags=''    score=0
 * and the emitted .rodata of build/src/game_64120.c.o is
 *     0000 c7c34f80 4ebebc20 c7c34f80 00000000
 * i.e. D_8009863C, D_80098640, D_80098644 in golden's exact ROM order and with
 * golden's exact values.  There is nothing left to find in this function: the
 * control flow, the declaration list, all 11 parameter types, the
 * func_15037698 prototype and every register/stack/scheduling decision are
 * confirmed byte-exact against golden.
 *
 * IT CANNOT BE SHIPPED because those 12 bytes cannot be linked to 0x8009863C.
 * The full proof, and the death of the "just migrate the range" plan, is in
 * the RODATA MIGRATION section at the bottom of this comment.  Read it before
 * anyone spends another hour on this function or on the migration idea.
 *
 * BEST SHIPPABLE SCORE: 1220 (the code below, `extern f32', EXACT frame 0x80).
 * Re-measured this wave from this exact file: -R = 1220.  Unchanged.
 *
 * RESIDUAL CLASS: **rodata float literal** -- and the residual is PROVEN to be
 * EXACTLY FOUR INSTRUCTIONS, nothing else.  Probe (one variable changed, rest
 * of the file byte-identical to what is below):
 *
 *     out[0..2] = D_8009863C / D_80098644   (extern f32)      -> 1220
 *     out[0..2] = -99840.0f  (0xC7C30000, low16 == 0)         ->  410
 *     out[0..2] = -99999.0f  (the TRUE value, needs .rodata)  ->    0
 *
 * and at 410 the ENTIRE asm-differ output is these four lines and nothing else:
 *     14a8: lui  at,%hi(D_8009863C)        vs  lui  at,0xc7c3
 *     14ac: lwc1 $f0,%lo(D_8009863C)(at)   vs  mtc1 at,$f0
 *     17c8: lui  at,%hi(D_80098644)        vs  lui  at,0xc7c3
 *     17cc: lwc1 $f0,%lo(D_80098644)(at)   vs  mtc1 at,$f0
 * Every stack offset, every register (integer AND fp), every branch target,
 * every scheduling decision and the frame size 0x80 are IDENTICAL to golden.
 * The control-flow reconstruction, the declaration list, all 11 parameter types
 * and the func_15037698 prototype are therefore CONFIRMED CORRECT.
 *
 * asm/data/23CD10.rodata.s:282,288 give
 *     D_8009863C = .float -99999        D_80098644 = .float -99999
 * i.e. TWO separate rodata entries holding the SAME value -- the signature of
 * IDO emitting one constant-pool entry per source-level literal.  The original
 * wrote `-99999.0f' three times at each site.  0xC7C34F80 has low16 = 0x4F80
 * != 0 so it cannot inline as lui+mtc1, and this project /DISCARD/s live-C
 * .rodata, so the only expressible form is `extern f32 D_xxxx'.  That turns a
 * link-time CONSTANT into a memory OBJECT; IDO must then assume the store
 * `out[0] = ...' may alias it, so it reloads for each of the three stores and
 * CSEs the address into $v1:
 *     golden: lui at,%hi ; lwc1 f0,%lo(at) ; swc1 f0,0(s2) ; 4(s2) ; 8(s2)
 *     here  : lui v1,%hi ; addiu v1,v1,%lo ; lwc1 f4,0(v1) ; swc1 f4,0(s2)
 *             ; lwc1 f6,0(v1) ; swc1 f6,4(s2) ; lwc1 f8,0(v1) ; swc1 f8,8(s2)
 * The two extra fp webs per site also renumber the fp allocator downstream,
 * which is where most of the 1220 comes from.
 * => needs_rodata_migration = YES, and the migration is IMPOSSIBLE.  See below.
 *
 * ---------------------------------------------------------------------------
 * RODATA MIGRATION -- INVESTIGATED TO EXHAUSTION THIS WAVE, ANSWER IS **NO**
 * ---------------------------------------------------------------------------
 * The plan was `- [0x23D0FC, .rodata, game_64120]' covering exactly the twelve
 * bytes D_8009863C..D_80098647, with [before] and [after] left as asm blocks.
 * It fails on TWO independent, separately fatal grounds.  Both are measured,
 * not argued.
 *
 * (1) MIGRATION GRANULARITY IS 16 BYTES, NOT 4.  IDO emits `.rodata' with
 *     sh_addralign = 16 and pads sh_size up to a multiple of 16.  Every one of
 *     the 14 objects in this tree that has a .rodata says align 16 / size 0x10
 *     or 0x20 or 0x30 -- no exceptions.  Building this function with the real
 *     literals gives 12 bytes of content in a 0x10-byte section:
 *         .rodata PROGBITS 00000000 00fc90 000010 01  A  0  0 16
 *         0000 c7c34f80 4ebebc20 c7c34f80 00000000
 *     A migrated range must therefore start 16-byte-aligned AND be a multiple
 *     of 16 AND have its trailing bytes be zero in the ROM.  Ours has none of
 *     the three:
 *         0x8009863C mod 16 == 0xC   -> ld would insert 4 bytes of alignment
 *                                       padding and shift ALL later rodata;
 *         ROM 0x23D108 == 42652EE0   -> the 4 pad bytes would overwrite
 *                                       D_80098648 (func_15038468's 57.29578).
 *     The two migrations that DO exist in conker.us.yaml are not
 *     counter-examples, they are the rule: 0x247780 (game_138520) and 0x24F480
 *     (game_1ED0F0) are each a COMPLETE original-TU rodata block, 16 bytes,
 *     16-aligned, ending in the TU's own natural zero padding --
 *         00247780: 38c90fdb 00000000 00000000 00000000
 *         0024f480: 459c4000 3dcccccd 00000000 00000000
 *     You can only ever migrate a WHOLE TU rodata block.
 *
 * (2) THE WHOLE-BLOCK ESCAPE HATCH IS CLOSED BY THE SEGMENT LAYOUT.  Doing the
 *     whole block would normally be fine even with stubs, because splat's
 *     `migrate_rodata_to_functions' (default true) writes each still-stubbed
 *     function's rodata into its own asm/nonmatchings/<tu>/<func>.s, and
 *     tools/asm-processor reserves the space in source order with a
 *     `const char _asmpp_rodataN[N]' placeholder (asm_processor.py:844).  It
 *     does not fire here.  splat only pairs a `.rodata' subsegment with a `c'
 *     subsegment of the same name when they are SIBLINGS, and siblings are
 *     assigned per parent code segment (segtypes/common/code.py:259-270).
 *     conker.us.yaml puts every C text subsegment in segment `game'
 *     (vram 0x15000000, line 238) and every rodata subsegment in segment
 *     `game_data' (vram 0x80082B20, line 781).  They can never be siblings.
 *     MEASURED: I set `- [0x23CD10, .rodata, game_64120]' (the whole block)
 *     and ran a FULL `make -C conker extract'.  Result: conker.ld correctly
 *     switched to `build/src/game_64120.c.o(.rodata);', every
 *     asm/nonmatchings/game_64120/*.s was regenerated with .text ONLY (a grep
 *     for `.section .rodata' over the entire nonmatchings tree still returns
 *     zero files), and D_80098250 / D_8009862C / D_8009863C / jtbl_80098254
 *     were all still in undefined_syms_auto.txt.  i.e. the stubs' rodata is
 *     simply DROPPED.  Migrating the block therefore requires every one of its
 *     rodata owners to be live C first.
 *
 * THE OWNERSHIP MAP OF THE BLOCK (0x23CD10..0x23D1AF = 0x80098250..0x800986EF,
 * 0x4A0 bytes, 16-aligned at both ends, 27 symbols, all owned by this TU and
 * laid out in exact function order):
 *     func_15036C70  LIVE    D_80098250
 *     func_15036CE8  stub    jtbl_80098254(0x100) D_80098354/58/5C
 *     func_15036F34  stub    D_80098360 jtbl_80098364(0x2C4) D_80098628
 *     func_15037880  LIVE    D_8009862C
 *     func_150379DC  stub    D_80098630/34/38
 *     func_150380C0  <-- us  D_8009863C/40/44
 *     func_15038468  stub    D_80098648
 *     func_15038620  stub    D_8009864C/50/54/58/5C
 *     func_1503A830  stub    jtbl_80098660(0x7C) D_800986DC/E0/E4/E8
 *     func_1503B708  stub    D_800986EC
 * So the price of this function is: decompile func_15036CE8, 15036F34,
 * 150379DC, 15038468, 15038620, 1503A830, 1503B708 (three of them jump-table
 * functions), AND convert func_15036C70's D_80098250 and func_15037880's
 * D_8009862C from `extern f32' to literals in the same edit.  Nothing less
 * links.  That is a whole-TU campaign, not a one-line yaml change.
 *
 * (The yaml experiment was fully reverted: conker.ld, undefined_syms_auto.txt,
 * undefined_funcs_auto.txt, asm/data/23CD10.rodata.s and every file under
 * asm/nonmatchings/game_64120/ all compare IDENTICAL to their pre-experiment
 * snapshots after a second full re-split, and the code bin still links to
 * 842e3d348e3c8ae0039e2ab367ad492f9b5266d8.)
 *
 * RULED OUT, each measured:
 *   extern const f32 D_8009863C;                        -> 1220 (no change;
 *       IDO 5.3 does not use const-qualification for alias analysis)
 *   out[2] = out[1] = out[0] = D_8009863C;              ->  635, BUT the frame
 *       goes 0x80 -> 0x88: the chain's intermediate value costs two extra
 *       4-byte compiler temps and every stack offset above 0x50 shifts by 8.
 *       Lower score, structurally WORSE (35 wrong stack offsets instead of 6
 *       extra instructions), so it is deliberately NOT the parked form.
 *   a carrier local (`f32 v; v = D_8009863C; out[0]=v; out[1]=v; out[2]=v;')
 *       would give golden's exact 5-instruction sequence, but it adds a 12th
 *       home and the 410 probe PROVES golden has exactly 11 -- so golden has no
 *       carrier and one here would be a fake frame-shaping local.  Not used.
 *   declaring `self'/`other' as pointer locals                -> byte-identical
 *       object (IDO homes neither), so they are not distinguishable that way.
 *
 * ---------------------------------------------------------------------------
 * FRAME DECODE (read off golden first, then confirmed exact by the build)
 *   framesize 0x80
 *   0x00..0x2F  argbuild = roundup(4 * 10 args, 16) = 0x30   [func_15037698]
 *   0x30..0x3F  saved    s0 @0x30, s1 @0x34, s2 @0x38, ra @0x3C
 *   0x40..0x53  compiler temps (20 B): 0x44 = the i+1 spill, 0x50 = the CSE'd
 *               &D_800CC2D0[idx] spilled around the call
 *   0x54..0x7F  local home area (44 B) = 11 declared autos, TOP-DOWN:
 *       0x7C  s32 i         [$v1,  spilled 0x7C round the call]
 *       0x78  f32 dist      [$f14, spilled 0x78]
 *       0x74  f32 dx        [$f0   -- never spilled: DEAD HOLE in golden]
 *       0x70  f32 dz        [$f2   -- dead hole]
 *       0x6C  f32 dy        [$f12  -- dead hole]
 *       0x68  s32 best      [$ra used as a general register!, spilled 0x68]
 *       0x64  f32 thresh    [$f16, spilled 0x64]
 *       0x60  s32 selfId    [$t5,  spilled 0x60]
 *       0x5C  s32 idxPlus1  [stored once pre-loop, read in-loop]
 *       0x58  s32 flagA     [stored once pre-loop]
 *       0x54  s32 flagB     [stored once pre-loop]
 *   The three dead holes are what identified dx/dz/dy as three separate named
 *   locals; the in-place squares mul.s $f0,$f0,$f0 / $f2,$f2,$f2 /
 *   $f12,$f12,$f12 confirm three distinct webs and force the STATEMENT FORM
 *   `dx = a - b; dx = dx * dx;' (writing the square inline emits
 *   `mul.s $f4,$f0,$f0' instead).
 *   NEITHER `self' NOR `other' is a declared local: golden reaches the records
 *   as D_800CC2D0[idx] / D_800CC2D0[i] and IDO CSEs them into $t1 (caller-saved
 *   -> spilled to the TEMP slot 0x50) and $s0 (callee-saved, strength-reduced
 *   to `addiu s0,s0,0x32C' on the back edge).
 *
 * SCORE HISTORY
 *   1472  first draft (self/other as locals, decl order self,other,i,best,...)
 *    635  + frame decode decl order + in-place squares + chained triple store
 *   1220  + plain triple store  (frame becomes EXACT 0x80; parked form)
 *    410  + inlinable-literal probe -99840.0f (semantically wrong, evidence)
 *      0  + the TRUE literals -99999.0f / 1600000000.0f -- correct C, unlinkable
 *
 * BRANCH SENSES read off golden (IDO reverses: source `X == Y' -> `beq Y,X',
 * and the RIGHT operand's load is emitted first):
 *   `beql $t2(0xFF), $t7'      -> D_800CC2D0[i].unk127 == 0xFF
 *   `beq  $t5(selfId), $a0'    -> D_800CC2D0[i].id == selfId
 *   `bne  $v1(i), $t7(unk222)' -> i == D_800CC2D0[idx].unk222
 *   `beq  $ra(best), $at(-1)'  -> the D_800CC40B return is the FALLTHROUGH, so
 *                                 the source is `if (best != -1) return ...;'
 *   The `(A && B) || C' shape at the distance test is read straight off
 *   bc1f / bc1tl / bnel: A false -> go test C; B true -> body; else test C.
 *   The `bnel X,next ; b continue' pairs with a duplicated instruction in the
 *   likely delay slot are as1's delay-slot filler and reproduce by themselves
 *   from plain `if (...) { continue; }' statements.
 *
 * PROTOTYPES DERIVED FROM GOLDEN
 *   func_15037698(s32, s32, s32, f32, f32, f32, f32 *, f32, s32, s32)
 *     -- a3/arg5/arg6 are f32 (mtc1 $a3,$f14 and lwc1 0x78/0x7C($sp) in the
 *        callee), arg7 is f32 * (lw 0x80($sp), then swc1 through it), arg8 is
 *        f32 (lwc1 0x84($sp)), arg9 is the beqz flag, arg10 a word.
 *   func_150380C0's own 11 params are pinned by the incoming-arg homes at
 *   0x80..0xA8 and by which of them reach func_15037698.
 *
 * D_800CC40B: golden's return is `lbu %lo(D_800CC40B)(v0)' with v0 = %hi +
 *   best*0x32C, i.e. the byte at D_800CC2D0 + best*sizeof(struct127) + 0x13B.
 *   Written as the array D_800CC40B[best * 0x32C] so the R_MIPS_HI16/LO16
 *   relocs are against the same symbol golden's object uses (D_800CC40B is a
 *   real project symbol -- undefined_syms_auto.txt:7065).  Writing it as
 *   D_800CC2D0[best].pad139[2] relocates against D_800CC2D0+0x13B instead and
 *   shows as a two-instruction diff.
 *
 * TO SHIP THE DAY THE BLOCK IS MIGRATED: delete the three `extern f32
 * D_800986xx' lines and substitute  D_8009863C -> -99999.0f,
 * D_80098640 -> 1600000000.0f, D_80098644 -> -99999.0f.  That is the entire
 * edit and it was measured at score 0 both with and without -R.
 *
 * NO shared header was edited.  struct127 from include/structs.h is used for
 * every field except the three s16 at 0x1A4/0x1A8/0x1AA, which structs.h has as
 * `u16 pad1A4; s16 unk1A6; u32 pad1A8;' -- golden reads them with `lh', so a
 * file-local overlay struct is cast over the record for exactly those three.
 * =========================================================================== */

typedef struct {
    /* 0x000 */ u8  pad0[0x1A4];
    /* 0x1A4 */ s16 unk1A4;
    /* 0x1A6 */ s16 unk1A6;
    /* 0x1A8 */ s16 unk1A8;
    /* 0x1AA */ s16 unk1AA;
} Struct150380C0Rot;

extern f32 D_8009863C;   /* rodata literal -99999.0f -- see header */
extern f32 D_80098640;   /* rodata literal 1600000000.0f (== 40000^2) */
extern f32 D_80098644;   /* rodata literal -99999.0f -- see header */
extern u8 D_800CC40B[];
extern s32 func_15037698(s32 arg0, s32 arg1, s32 arg2, f32 arg3, f32 arg4, f32 arg5,
                         f32 *arg6, f32 arg7, s32 arg8, s32 arg9);

s32 func_150380C0(f32 *out, s32 arg1, s32 arg2, s32 idx, f32 arg4, s32 arg5, f32 *arg6,
                  s32 arg7, s32 arg8, s32 arg9, s32 arg10) {
    s32 i;
    f32 dist;
    f32 dx;
    f32 dz;
    f32 dy;
    s32 best;
    f32 thresh;
    s32 selfId;
    s32 idxPlus1;
    s32 flagA;
    s32 flagB;

    best = -1;
    flagA = 1;
    flagB = -1;
    if ((&D_800C35EA)[0] == 1 || (&D_800C35EA)[1] == 1) {
        out[0] = D_8009863C;
        out[1] = D_8009863C;
        out[2] = D_8009863C;
        return 0;
    }

    idxPlus1 = idx + 1;
    selfId = D_800CC2D0[idx].id;
    if (selfId == 5 || selfId == 0xAD || selfId == 0xAE || selfId == 0xAF) {
        flagA = 0;
    }
    if (selfId == 0x2D) {
        flagB = 0x2C;
    }

    if (arg9 == 0) {
        thresh = (f32)(D_800CC2D0[idx].unk23D * 8);
        thresh = thresh * thresh;
    } else {
        thresh = D_80098640;
    }

    for (i = 0; i < 25; i++) {
        if (D_800CC2D0[i].interaction_state == 0) {
            continue;
        }
        if (D_800CC2D0[i].id == 0xFF) {
            continue;
        }
        if (i == idx) {
            continue;
        }
        if (D_800CC2D0[i].unk65 == idxPlus1) {
            continue;
        }
        if (D_800CC2D0[idx].unk65 == i + 1) {
            continue;
        }
        if (flagA == 0 && D_800CC2D0[i].id == selfId) {
            continue;
        }
        if (D_800CC2D0[i].id == flagB) {
            continue;
        }
        if (arg8 != 0 || (D_800CC2D0[idx].unk2F8 & 7) == 4) {
            if (D_800CC2D0[i].unk127 == 0xFF) {
                continue;
            }
        }
        if ((D_800CC2D0[idx].unk2F8 & 7) == 5) {
            if (D_800CC2D0[i].unk127 != 0xFF) {
                continue;
            }
        }
        dx = D_800CC2D0[idx].x_position - D_800CC2D0[i].x_position;
        dx = dx * dx;
        dz = D_800CC2D0[idx].z_position - D_800CC2D0[i].z_position;
        dz = dz * dz;
        dy = D_800CC2D0[idx].y_position - D_800CC2D0[i].y_position;
        dy = dy * dy;
        dist = (dx + dz) + dy;
        if (i == D_800CC2D0[idx].unk222 &&
            (D_800CC2D0[idx].unk223 == 1 || D_800CC2D0[idx].unk223 == 0xC)) {
            dist = 0.0f;
        }
        if ((dist < thresh && dist < *arg6) || D_800CC2D0[i].id == arg5) {
            if (func_15037698(idx, arg1, arg2,
                              (f32)((Struct150380C0Rot *)&D_800CC2D0[i])->unk1A4,
                              (f32)((Struct150380C0Rot *)&D_800CC2D0[i])->unk1AA,
                              (f32)((Struct150380C0Rot *)&D_800CC2D0[i])->unk1A8,
                              out, arg4, arg7, arg10) != 0) {
                *arg6 = dist;
                best = i;
                if (D_800CC2D0[i].id == arg5) {
                    break;
                }
            }
        }
    }

    if (best != -1) {
        return D_800CC40B[best * 0x32C] + 1;
    }
    out[0] = D_80098644;
    out[1] = D_80098644;
    out[2] = D_80098644;
    return 0;
}
