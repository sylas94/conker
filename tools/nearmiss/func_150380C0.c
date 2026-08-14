/* ===========================================================================
 * func_150380C0  --  game_64120.c  --  936 B, frame 0x80, 1 callee, 27 regions
 *
 * BEST HONEST SCORE: 1220 (this file, EXACT frame) / 635 (chained-store variant,
 * frame 0x88 -- rejected, see below).  Cold start this wave.
 *
 * RESIDUAL CLASS: **rodata float literal** -- and the residual is PROVEN to be
 * EXACTLY FOUR INSTRUCTIONS, nothing else.  Probe (one variable changed, rest
 * of the file byte-identical to what is below):
 *
 *     out[0..2] = D_8009863C / D_80098644   (extern f32)      -> 1220
 *     out[0..2] = -99840.0f  (0xC7C30000, low16 == 0)         ->  410
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
 * => needs_rodata_migration = YES.  Migrating the 0x8009862C..0x80098644 float
 *    run into game_64120's own .rodata (conker.us.yaml `[0xADDR, .rodata,
 *    game_64120]' + splat --modes ld) closes this function at 0.  It cannot be
 *    done piecemeal while func_15036CE8 / 15036F34 / 15037698 / 150379DC /
 *    15038468 / 15038620 in the same TU are still #pragma GLOBAL_ASM and own
 *    literals interleaved in that same block (D_8009862C is already consumed by
 *    the live func_15037880).
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
 *    410  + inlinable-literal probe (semantically wrong, evidence only)
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
