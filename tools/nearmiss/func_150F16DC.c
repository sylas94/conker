/* ===========================================================================
 * NEAR MISS -- func_150F16DC  (game_11C2B0.c, 804 bytes golden)
 *
 * BEST SCORE 1529 (asm-differ -o func_150F16DC -R --max-lines 4096; identical
 * without -R).  NOTE: this project's asm-differ restrict_to_function() only
 * truncates at the function START, so the printed score covers func_150F16DC
 * PLUS every function after it in game_11C2B0.c.o.  The control (pragma in
 * place) scores 0 and the objcopy compare says .text/.rodata/.data IDENTICAL,
 * so the whole residual belongs to this function.
 *
 * Our size 816 vs golden 804 = exactly 3 instructions too many.
 *
 * RESIDUAL (the only structural defect left):
 *   golden computes `arg1 * 12` ONCE at the second use site and shares it
 *   between the func_15102B38 arg2 (&D_800A168C[..]) and arg3
 *   (&D_800A174C[..]) address computations:
 *        sll t9,v0,2 / subu t9,t9,v0 / sll v0,t9,2   <- v0 = arg1*12
 *        ...
 *        addu t0,t6,v0   (174C)      addu a2,t1,v0   (168C)
 *   ours rematerialises it, emitting the 3-instruction sll/subu/sll chain
 *   twice (once at 2b34 for a2, again at 2b6c..2b8c for a3).  IDO schedules
 *   our a2 immediately after the arg1*12 (because it reloads the CSE'd
 *   2-index partial address early) while golden defers a2 to last.  This is
 *   a scheduler/rematerialisation tie, not a spelling problem.
 *
 * Everything else already matches instruction-for-instruction INCLUDING
 * registers from 28dc to 2b24 (the whole prologue, both guard chains, the
 * D_800A1810 mask test, the func_15145EA4 call, the Header/Header2 fill and
 * the func_151602C0 call).  Remaining cosmetic rows: the `addiu v0,sp,0x80`
 * vs `lui` hoist over the `arg0->id == 0x23` branch, and our two spill slots
 * landing at 0x44/0x48 instead of golden's 0x48/0x4C.
 *
 * REGISTER / FRAME MAP (golden vs ours, after the fixes below): identical.
 *   0x84..0x8F f32 sp84[3]   0x83 u8 flag   0x80 2-byte mask struct
 *   0x7C,0x78  f32* cursors  0x70 Header    0x64 Header2
 *   0x5C..0x63 f32 sp5C[2]   0x50..0x5B s32 sp50[3]
 *
 * SPELLINGS RULED OUT, WITH SCORES (all measured, stale-object guard on):
 *   4646  original w19 head-start (s32 sp7C/sp78 with (s32) casts, Vec3i*
 *         prototype for func_15102B38, `Pair sp80` declared before `u8 sp83`)
 *         -- frame 0x98 (8 bytes too big), 808 bytes.
 *   4702  same but `u8 sp83` declared before `Pair sp80` (fixes the 0x83/0x80
 *         ordering but not the frame; still 808).
 *   5585  sp7C/sp78 retyped `f32 *` and the (s32) casts dropped: FIXES THE
 *         FRAME to 0x90 exactly, but 792 bytes (3 SHORT) because IDO then
 *         CSEs the FULL &D_800A168C[sp83][arg2][arg1] and reloads it.
 *   4301  arg2 spelled `(D_800A168C[sp83][arg2] + arg1)` (pointer arithmetic)
 *         -- 812 bytes, kills the 2-index CSE entirely.
 *   1725  ** KEY UNLOCK ** switch func_15102B38 to the project-standard
 *         prototype already used by the matched siblings game_12B250.c /
 *         game_12BD10.c / game_1F2730.c:
 *           void func_15102B38(s32,u8,s32,s32,f32*,s32,s32,f32,s32,s32,s32,
 *                              s32,u8,s32);
 *         The (s32) cast on arg2/arg3 makes the top address node a DIFFERENT
 *         TYPE from the f32* first use, so IDO CSEs only the shared 2-index
 *         node &D_800A168C[sp83][arg2] -- exactly golden's shape.  816 bytes.
 *   1529  ** KEY UNLOCK 2 ** the two func_150ADA20() results must live in an
 *         AGGREGATE, not two scalars.  Golden stores BOTH (0x50 read back for
 *         `% 6`, 0x58 written and never read) with 0x54 reserved between them.
 *         A plain `s32 sp58` scalar is register-promoted and its dead store is
 *         eliminated (we emitted `nop` in the jal delay slot); `s32 sp50[3]`
 *         with sp50[0] and sp50[2] assigned reproduces golden's 0x50/0x54/0x58
 *         layout byte-for-byte.  Verified: `sw v0,0x50(sp)` and
 *         `sw v0,0x58(sp)` now both present at golden's offsets.
 *         (`s32 sp54[2]` + `s32 sp50` scores the same 1529.)
 *   6606  folding flag+mask into one 4-byte `Sel150F16DC sp80` struct and
 *         reading the flag as `sp80.unk3` -- 856 bytes, much worse (every
 *         index read becomes a memory load).
 *
 * NOT TRIED / NEXT LEVER: force IDO to schedule the arg2 address computation
 * last.  Candidates: give arg3's expression a type that shares the arg1*12
 * node with arg2's; or change the order in which the two spill slots are
 * allocated (golden 0x48=&D_800A180C[..], 0x4C=2-index partial, ours 0x44/0x48
 * -- ours reserves 8 unused bytes at 0x48..0x4F, so a locals-layout nudge may
 * move the reload site).
 *
 * NO rodata migration needed: every float constant here is an `extern f32`
 * global in a multi-glabel block (D_800A1898..D_800A18B4 live in
 * asm/data/*.rodata.s alongside many other symbols), and .rodata compares
 * IDENTICAL in every build above.
 * ===========================================================================
 *
 * ---------------------------------------------------------------------------
 * WAVE 2026-08-12 -- 1529 RE-VERIFIED AND THE RESIDUAL RE-DERIVED FROM SCRATCH
 * ---------------------------------------------------------------------------
 * The score above is real: an independent private whole-TU scorer (repo
 * pipeline -> private build/ + expected/ pair -> the real asm-differ) prints
 *     SCORE 1529 INSNS 204 FRAME 144 BYTES 816
 * for this file, and SCORE 0 / INSNS 201 / FRAME 144 / BYTES 804 for the repo
 * copy with the #pragma still in.  permuter_tu.sh selftest check (b) proves the
 * private pipeline's object is BYTE-IDENTICAL to `make build/src/game_11C2B0.c.o`.
 * So: golden 201 instructions, ours 204 -- exactly 3 too many -- frame correct.
 *
 * THE PARKED "NEXT LEVER" ABOVE WAS BASED ON A STALE RESIDUAL.  Compared with
 * addresses stripped, this candidate is identical to golden INCLUDING REGISTERS
 * from 28dc all the way to 29e4.  There are exactly three defects left:
 *
 *  (1) THE 3 EXTRA INSTRUCTIONS -- `arg1 * 12` is computed TWICE in the final
 *      block.  Golden computes it once into $v0 at the top of the block and
 *      shares it between BOTH address arguments:
 *          2b34 sll t9,v0,2 / subu t9,t9,v0 / sll v0,t9,2      <- once
 *          2b7c lw t1,0x4c(sp)                                  <- 168C partial
 *          2b8c addu t0,t6,v0   (a3 = ...174C + arg1*12)
 *          2b98 addu a2,t1,v0   (a2 = partial + arg1*12)
 *      Ours emits the sll/subu/sll chain a second time for a3, because it forms
 *      a2 EARLY (it reloads the 168C partial in the first three instructions of
 *      the block) and the arg1*12 register is then dead and gets reused.
 *      This is a CSE decision, not a spelling: see the flat sweeps below.
 *
 *  (2) The two compiler spill slots land at 0x40/0x44; golden uses 0x48/0x4C.
 *      MEASURED RULE (probes p1/p2/p3, which strip one or both call-crossing
 *      values out of the last call): spill temps are handed out DESCENDING from
 *      a boundary, and in our build that boundary is 0x48 -- with only ONE
 *      call-crossing value the single temp lands at 0x44, never at 0x4C, and
 *      with none the frame drops to 0x88 with 0x40..0x47 unused.  Golden's
 *      boundary is 0x50 (the locals base).  Both frames are 0x90 and every
 *      DECLARED local offset (0x50..0x8F) already matches golden exactly, so
 *      this is an allocation-ORDER difference in IDO's temp list, not a missing
 *      local.  Confirmed: adding locals does not fix it (see d1/d3/d4 below).
 *
 *  (3) Cosmetic: golden hoists `addiu v0,sp,0x80` above the `arg0->id == 0x23`
 *      branch where we hoist `lui t2,%hi(D_800A1810)`.
 *
 * NEW NEGATIVES, ALL MEASURED WITH THE SCORER ABOVE (score / insns / frame):
 *   a2 and a3 spelled `&X[..][..][..]` vs `X[..][..][..]` vs `&X[..][..][..][0]`
 *     -- all 9 combinations BYTE-IDENTICAL to base (1529/204/144).
 *   a2 or a3 as `(D_800A168C[sp83][arg2] + arg1)`      4422/203/152 and 5993/207/152
 *   prototype arg2 as `f32 *` or `f32 (*)[3]` (no cast) 2904/200/144  <- 1 SHORT:
 *     IDO then CSEs the FULL 3-index address and the FIRST block stops matching
 *     golden (the spilled value becomes the full address, not the 2-index
 *     partial).  The (s32) cast on arg2 is therefore load-bearing and correct.
 *   prototype arg3 as `f32 *` / `f32 (*)[3]`            4422/203/152
 *   both as `f32 *` / `f32 (*)[3]` / `Vec3 *`           5808/198/152 (3 SHORT)
 *   D_800A174C dimensioned [2][4][6] with `[arg1 * 3]`  4729/206/152
 *   BOTH arrays [2][4][6] with `[arg1 * 3]`             5072/201/152 <- right
 *     instruction count, wrong frame and an extra spill; rejected.
 *   extern-declaration ORDER of D_800A1810/168C/174C/180C, all 3 shuffles  1529 (identical)
 *   `% 5` / `% 0x33` / `% 6` signed instead of unsigned  1729 / 1729 / 1724 (all worse
 *     -- `divu` confirms the unsigned spelling is right); all three at once 2124
 *   `((u32) sp50[0] % 6U)`                              1529 (identical)
 *   sp5C[0]/sp5C[1] order swapped                       1597
 *   sp50[0]/sp50[2] order swapped                       1545
 *   the two sp50 stores before the two sp5C stores      1779
 *   `s32 sp50[3]` replaced by a 3-field Vec3i struct    1729  <- the ARRAY is right
 *   `sp7C = &D_800A168C[..][..][..][0];`                1529 (identical)
 *   `sp78 = &sp84[0];`                                  1529 (identical)
 *   `(u8) D_800A180C[sp83][arg1]` at the call           1529 (identical)
 *   `(s32) &sp84[0]` for the 9th argument               1529 (identical)
 *   `if (!arg0)` / `if (arg0 == 0)`                     1529 (identical)
 *   shift term cast / operands swapped in `+ (…<< 6)`   1529 (identical)
 *   two extra pointer locals (`f32 (*)[3]` + `u8 *`) holding the reused
 *     addresses                                          5410/203/160 -- REFUSED,
 *     grows the frame to 0xA0; golden's 0x90 cannot hold two more locals, which
 *     DISPROVES the "golden spills declared locals" reading of 0x48/0x4C.
 *   `s32 sp50[4]` / `s32 sp50[5]`                       1862/204/152 (frame grows 8,
 *     temps move up 4) -- you cannot buy golden's 0x48/0x4C with extra locals.
 *
 * PERMUTER: setup + selftest PASS (all five checks; (b) byte-identical codegen,
 * (b2) pycparser round-trip neutral, (e) isolation DIFFERS so the TU harness is
 * load-bearing).  Base permuter metric 1519 (asm-differ 1529; constant +10
 * offset).  ~3,400 iterations at -j4 with PERMUTER_TU_REQUIRE_FRAME=144 produced
 * SEVEN "wins" (1320,1323,1344,1489,1493,1507,1517).  **ALL SEVEN REJECTED** --
 * every one is a single `perm_temp_for_expr` insertion, i.e. a `new_var` that
 * caches `arg2`, `sp83` or the function pointer `func_150ADA20` and changes
 * nothing else.  Reproduced by hand as `u8 diag = arg2;` declared last: 1490,
 * 204 instructions, frame 144, spill temps STILL at 0x40/0x44 -- so it does not
 * even touch defect (2); it is pure register noise over a banned construct.
 *
 * WHERE TO GO NEXT.  Defect (1) is the whole 3-instruction gap and it is a CSE
 * decision inside ONE basic block, so the productive question is what makes IDO
 * defer the 0x4C reload (and hence the a2 `addu`) to the end of the block.
 * Everything reachable by respelling the two address arguments, the prototype,
 * the array dimensions and the declaration order has now been enumerated and is
 * flat; what has NOT been tried is changing the FIRST use (`sp7C = ...`) so that
 * the CSE'd 2-index partial is created by a different statement shape while the
 * first block's bytes are preserved.
 * =========================================================================== */

#include <ultra64.h>
#include "functions.h"
#include "variables.h"

typedef struct {
    u8 pad0[0x94];
    s32 unk94;
    u8 pad98[0x13C];
    s32 unk1D4;
} struct_150EEE00_arg0;

extern u8 D_800A1638[];
extern u8 D_800A163C[];
extern f32 D_800A15F0[][3];
extern s32 (*D_8008FD00)(s32, u8);
extern f32 D_800A1830;
extern f32 D_800A1834;
extern f32 D_800A1870;
extern f32 D_800A1874;
extern u8 D_800A1674;
extern u8 D_800A1680;
extern f32 sinf(f32);

typedef struct {
    u8 pad0[0x14];
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    u8 pad20[0x1B];
    u8 unk3B;
} Struct150F0E48Src;

typedef struct {
    Struct150F0E48Src *unk0;
    u8 unk4;
    u8 pad5[3];
    f32 unk8;
    f32 unkC;
    f32 unk10;
} Struct150F0E48Sub;

typedef struct {
    u8 pad0[0x2B];
    u8 unk2B;
    u8 pad2C[0xC];
    f32 unk38;
    f32 unk3C;
    f32 unk40;
    f32 unk44;
    f32 unk48;
    u8 pad4C[0x5C];
    Struct150F0E48Src *unkA8;
    u8 unkAC;
} Struct150F0E48Obj;

typedef struct {
    u8 pad_0[0x68];
    u8 field_0x68;
    u8 field_0x69;
    u8 pad_1[0x1A];
    u16 field_0x84;
    u8 pad_2[0x25E];
    s32 field_0x2E4;
} ActorStateFields;

void *func_150EEF80(struct_150EEE00_arg0 *, u8, u8, s32);
void func_15143134(void *, void *, s32);
void func_15143874(s32, f32, f32 *, f32 *);
void func_151C329C(void *, s32, s32);
void *func_151407D0(void *, s32, void *, s32, s32, s32, s32, s32, s32, s32);
struct225 *func_151602C0(Header *, Header2 *, s32, s32, s32, s32, s32, s32, s32, u8, s32);
s32 func_15160A58(s32, s32, void *, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
void func_150F0A24(f32 *);

void func_150EEE00(struct_150EEE00_arg0 *arg0, u8 arg1) {
    f32 sp54[3];
    Header sp4C;
    Header2 sp40;
    s32 temp_v1;

    if (D_800A163C[arg1] & arg0->unk94) {
        return;
    }

    func_150EEF80(arg0, arg1, 0xFF, 1);
    temp_v1 = arg0->unk1D4;
    if (temp_v1 != 0) {
        func_15143134(D_800A15F0[arg1], sp54, temp_v1 + (D_800A1638[arg1] << 6));
        sp4C.unk0 = 3;
        sp4C.unk1 = -1;
        sp4C.unk2 = (func_150ADA20() % 3U) + 4;
        sp4C.unk4 = 0;
        sp40.unk0 = (s32) sp54[0];
        sp40.unk4 = (s32) sp54[1];
        sp40.unk8 = (s32) sp54[2];
        func_151602C0(&sp4C, &sp40, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0, 0xFF, 1);
        func_150F0A24(sp54);
    }
}

void func_150EEF40(struct210 *arg0, u8 arg1) {
    s8 sp18[6];

    *(struct210 **)&sp18[0] = arg0;
    sp18[4] = *(u8 *)((s32)arg0 + 0x3B);
    sp18[5] = arg1;
    func_151403A8(&sp18, 0x43);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_11C2B0/func_150EEF80.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_11C2B0/func_150EF38C.s")

s32 func_150EF784(u8 *arg0, s32 arg1, s32 arg2) {
    if (arg0[4] == 0x28) {
        return 1;
    }
    return 0;
}

void func_150EF7B0(u8 *arg0) {
    s32 i;
    s32 v;
    s32 *p = (s32 *)(arg0 + 0x110);

    for (i = 0; i != 8; i += 4) {
        v = *(s32 *)((u8 *)p + i + 0x1C);
        if (v != 0) {
            func_1516972C((struct102 *)v);
        }
    }
    v = p[9];
    if (v != 0) {
        func_1516972C((struct102 *)v);
    }
    v = p[10];
    if (v != 0) {
        func_1516972C((struct102 *)v);
    }
    v = p[11];
    if (v != 0) {
        func_1516972C((struct102 *)v);
    }
    func_1513CA6C(arg0);
}

void func_150EF860(u8 *arg0) {
    s32 i;
    s32 v;
    s32 *p = (s32 *)(arg0 + 0x110);

    for (i = 0; i != 8; i += 4) {
        v = *(s32 *)((u8 *)p + i + 0x1C);
        if (v != 0) {
            func_1516979C((struct102 *)v);
        }
    }
    v = p[9];
    if (v != 0) {
        func_1516979C((struct102 *)v);
    }
    v = p[10];
    if (v != 0) {
        func_1516979C((struct102 *)v);
    }
    v = p[11];
    if (v != 0) {
        func_1516979C((struct102 *)v);
    }
    func_1513CAA0((struct210 *)arg0);
}

typedef struct {
    s32 unk0;
    union {
        s32 w4;
        struct {
            u8 b4;
            u8 b5;
            u8 b6;
            u8 b7;
        } b;
    } u4;
    u8 unk8;
    u8 unk9;
} ArgB_150EF910;

typedef struct {
    s32 unk0;
    u8 unk4;
    u8 pad5[3];
    s32 unk8;
    u8 unkC;
    u8 unkD;
} SubA_150EF910;

void func_150EF910(void *arg0, s32 arg1, u8 arg2) {
    ArgB_150EF910 *b = (ArgB_150EF910 *)arg1;
    SubA_150EF910 *a = (SubA_150EF910 *)((u8 *)arg0 + 0x110);
    s32 bu0;
    s32 bu0b;
    s32 au0;
    u8 au4;
    u8 bu4;

    if (arg2 == 0) {
        au0 = a->unk0;
        bu0 = b->unk0;
        au4 = a->unk4;
        bu4 = b->u4.b.b4;
        if ((au0 == bu0) || (au4 == bu4)) {
            func_1516972C((struct102 *)arg0);
        }
    } else if (arg2 == 0x2D) {
        if (a->unk0 == b->unk0) {
            a->unk0 = b->u4.w4;
            a->unk4 = b->unk9;
        } else if (a->unk0 == b->u4.w4) {
            a->unk0 = b->unk0;
            a->unk4 = b->unk8;
        }
        if (a->unk8 == b->unk0) {
            a->unk8 = b->u4.w4;
            a->unkC = b->unk9;
        } else {
            if (a->unk8 == b->u4.w4) {
                a->unk8 = b->unk0;
                a->unkC = b->unk8;
            }
        block2_end: ;
        }
    } else if (arg2 == 0x43) {
        if ((a->unk0 == b->unk0) || (a->unk4 == b->u4.b.b4)) {
            if (a->unkD == b->u4.b.b5) {
                func_1516972C((struct102 *)arg0);
            }
        }
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_11C2B0/func_150EFA4C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_11C2B0/func_150EFB80.s")

typedef struct {
    s32 unk00;
    u8 unk04;
    u8 unk05;
    u8 pad06[2];
    s32 unk08;
} Payload_150EFEC8;

typedef struct {
    u8 pad_0[0x3B];
    u8 field_0x3B;
} ActorIdByteFields;

typedef struct {
    f32 unk00;
    f32 unk04;
    f32 unk08;
    f32 unk0C;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    s32 unk24;
    s32 unk28;
    s32 unk2C;
    s32 unk30;
    s32 unk34;
    s32 unk38;
    s32 unk3C;
    s32 unk40;
    s32 unk44;
    f32 unk48;
    s16 unk4C;
    s16 unk4E;
    s16 unk50;
    s16 unk52;
    u8 unk54;
    u8 unk55;
    u8 unk56;
    u8 unk57;
    u8 unk58;
    s8 unk59;
    u8 pad5A[2];
} Struct98_150EFEC8;

typedef struct {
    u8 unk00;
    u8 unk01;
    s16 unk02;
    s16 unk04;
    u8 pad06[2];
    s32 unk08;
    s32 unk0C;
    u8 unk10;
    u8 unk11;
    u8 unk12;
    u8 unk13;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    f32 unk30;
    f32 unk34;
    f32 unk38;
    f32 unk3C;
    s32 unk40;
    u8 unk44;
    u8 unk45;
    u8 unk46;
    u8 unk47;
    s32 unk48;
    u8 pad4C[0xC];
} Struct40_150EFEC8;

typedef struct {
    u8 pad_0[0x170];
    Payload_150EFEC8 field_0x170;
} CreatedObjectPayloadFields;

s32 func_150EFEC8(ActorIdByteFields *arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4, s32 arg5, u8 arg6, s32 arg7) {
    CreatedObjectPayloadFields *temp_v0;
    Struct98_150EFEC8 sp98;
    Struct40_150EFEC8 sp40;
    Payload_150EFEC8 sp34;

    sp34.unk00 = (s32)arg0;
    sp34.unk04 = arg0->field_0x3B;
    sp34.unk05 = arg1;
    sp34.unk08 = arg5;

    sp40.unk00 = D_8008FD00((s32)arg0, arg1);
    sp40.unk01 = 3;
    sp40.unk02 = 0x2203;
    sp40.unk04 = 0x12C;
    sp40.unk08 = 0;
    sp40.unk0C = 0;
    sp40.unk10 = arg2;
    sp40.unk11 = arg3;
    sp40.unk12 = arg4;
    sp40.unk13 = 0xFF;
    sp40.unk18 = 100.0f;
    sp40.unk14 = 100.0f;
    sp40.unk1C = 0.0f;
    sp40.unk20 = 0.0f;
    sp40.unk24 = 0.0f;
    sp40.unk28 = 0.0f;
    sp40.unk2C = 0.0f;
    sp40.unk30 = 0.0f;
    sp40.unk34 = 1.0f;
    sp40.unk38 = 1.0f;
    sp40.unk3C = 1.0f;
    sp40.unk40 = 0xCD2002;
    sp40.unk44 = 0xFF;
    sp40.unk45 = 0xFF;
    sp40.unk46 = 0;
    sp40.unk47 = 6;
    sp40.unk48 = 0;

    sp98.unk04 = 160.0f;
    sp98.unk00 = 160.0f;
    sp98.unk0C = 80.0f;
    sp98.unk08 = 80.0f;
    sp98.unk10 = 0.5f;
    sp98.unk14 = 0.5f;
    sp98.unk18 = 1.0f;
    sp98.unk1C = D_800A1830;
    sp98.unk20 = D_800A1834;
    sp98.unk24 = -1;
    sp98.unk34 = -1;
    sp98.unk28 = -1;
    sp98.unk38 = -1;
    sp98.unk2C = -1;
    sp98.unk3C = -1;
    sp98.unk30 = -1;
    sp98.unk40 = -1;
    sp98.unk44 = 0;
    sp98.unk48 = 1.0f;
    sp98.unk4C = 0;
    sp98.unk4E = 0;
    sp98.unk50 = 0;
    sp98.unk52 = 0;
    sp98.unk54 = 0xFF;
    sp98.unk55 = 0xFF;
    sp98.unk56 = 0xFF;
    sp98.unk57 = 0xFF;
    sp98.unk58 = 0xA;
    sp98.unk59 = -1;

    temp_v0 = func_151407D0(&sp98, 0x6C, &sp40, 0x1E, 0, 0, 0, -1, arg6, arg7);
    if (temp_v0 != 0) {
        memcpy(&temp_v0->field_0x170, &sp34, 0xC);
    }
    return (s32)temp_v0;
}

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} Vec3w_150F00EC;

typedef struct {
    u8 pad0[0x18];
    u8 unk18;
    u8 pad19[0x17];
    f32 unk30;
    f32 unk34;
    f32 unk38;
} Sub110_150F00EC;

typedef struct {
    u8 pad0[0x34];
    Vec3w_150F00EC unk34;
    u8 pad40[0xD0];
} Sub178_150F00EC;

typedef struct {
    u8 pad0[0x34];
    Vec3w_150F00EC unk34;
    f32 unk40;
    f32 unk44;
    f32 unk48;
    u8 pad4C[0xC];
    s32 unk58;
    u8 pad5C[0x11C];
    Sub178_150F00EC *unk178;
} Arg150F00EC;

s32 func_150F00EC(Arg150F00EC *arg0) {
    Sub178_150F00EC *temp_v0;
    Sub110_150F00EC *temp_v1;

    temp_v0 = arg0->unk178;
    temp_v1 = (Sub110_150F00EC *)(temp_v0 + 1);
    if (*(u8 *)((u8 *)temp_v0 + 0x128) & 1) {
        arg0->unk34 = temp_v0->unk34;
        arg0->unk40 = *(f32 *)&temp_v0->unk34.unk0 + (temp_v1->unk30 * 500.0f);
        arg0->unk44 = *(f32 *)&temp_v0->unk34.unk4 + (temp_v1->unk34 * 500.0f);
        arg0->unk48 = *(f32 *)&temp_v0->unk34.unk8 + (temp_v1->unk38 * 500.0f);
        arg0->unk58 |= 6;
    } else {
        arg0->unk58 &= ~4;
        arg0->unk58 &= ~2;
    }
    return 1;
}

struct225 *func_150F0198(u8 arg0, u8 arg1, u8 arg2, u8 arg3, s32 arg4, u8 arg5, s32 arg6) {
    struct225 *temp_v0;
    Header header;
    Header2 header2;
    s32 payload;

    payload = arg4;
    header.unk0 = 2;
    header.unk1 = -1;
    header.unk2 = 0x12C;
    header.unk4 = 0x21;
    header2.unk0 = 0;
    header2.unk4 = 0;
    header2.unk8 = 0;

    temp_v0 = func_151602C0(&header, &header2, arg0, arg1, arg2, arg3, 0xFF, 0, 4, arg5, arg6);
    if (temp_v0 != NULL) {
        memcpy(&temp_v0->unk18, &payload, 4);
    }
    return temp_v0;
}

typedef struct {
    u8 pad_0[0x12C];
    s32 field_0x12C[1];
} SlotTableFields;

typedef struct {
    u8 pad_0[0x8];
    SlotTableFields *field_0x8;
    u8 field_0xC;
} SlotTableLinkFields;

typedef struct {
    u8 pad_0[0x60];
    SlotTableLinkFields *field_0x60;
} SlotTableOwnerFields;

void func_150F02A0(SlotTableOwnerFields *arg0);

void func_150F0260(SlotTableOwnerFields *arg0) {
    func_150F02A0(arg0);
}

void func_150F0280(SlotTableOwnerFields *arg0) {
    func_150F02A0(arg0);
}

void func_150F02A0(SlotTableOwnerFields *arg0) {
    SlotTableLinkFields *temp = arg0->field_0x60;
    SlotTableFields *base = temp->field_0x8;
    base->field_0x12C[temp->field_0xC] = 0;
}

void func_150F0318(struct260 *arg0);

void func_150F02C0(struct260 *arg0) {
    func_150F0318(arg0);
    func_1514933C(arg0);
}

void func_150F02EC(struct260 *arg0) {
    func_150F0318(arg0);
    func_15149368(arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_11C2B0/func_150F0318.s")

void func_150F0380(struct210 *arg0);

void func_150F0328(struct210 *arg0) {
    func_150F0380(arg0);
    func_151411A4(arg0);
}

void func_151411C4(struct210 *arg0);

void func_150F0354(struct210 *arg0) {
    func_150F0380(arg0);
    func_151411C4(arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_11C2B0/func_150F0380.s")

void func_150F03E8(struct210 *arg0);
void func_151617C4(struct210 *arg0);

void func_150F0390(struct210 *arg0) {
    func_150F03E8(arg0);
    func_151617C4(arg0);
}

void func_151617E4(struct210 *arg0);

void func_150F03BC(struct210 *arg0) {
    func_150F03E8(arg0);
    func_151617E4(arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_11C2B0/func_150F03E8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_11C2B0/func_150F03F8.s")

typedef struct {
    s32 unk0;
    u8  unk4;
} SubA_F07E4;

typedef struct {
    s32 unk0;
    union {
        s32 w4;
        u8  b4;
    } u4;
    u8  unk8;
    u8  unk9;
} ArgB_F07E4;

void func_150F07E4(struct260 *arg0, s32 arg1, u8 arg2) {
    SubA_F07E4 *temp_v0 = *(SubA_F07E4 **)((u8 *)arg0 + 0x60);
    ArgB_F07E4 *b = (ArgB_F07E4 *)arg1;
    s32 b0;

    if (arg2 == 0) {
        b0 = b->unk0;
        if ((b0 == temp_v0->unk0) || (b->u4.b4 == temp_v0->unk4)) {
            func_1516972C((struct102 *)arg0);
        }
    } else if (arg2 == 0x2D) {
        if (temp_v0->unk0 == b->unk0) {
            temp_v0->unk0 = b->u4.w4;
            temp_v0->unk4 = b->unk9;
        } else if (temp_v0->unk0 == b->u4.w4) {
            temp_v0->unk0 = b->unk0;
            temp_v0->unk4 = b->unk8;
        }
    }
}

typedef struct {
    s32 unk0;
    u8  unk4;
} SubA_F088C;

typedef struct {
    s32 unk0;
    union {
        s32 w4;
        u8  b4;
    } u4;
    u8  unk8;
    u8  unk9;
} ArgB_F088C;

void func_150F088C(struct260 *arg0, s32 arg1, u8 arg2) {
    SubA_F088C *temp_v0 = (SubA_F088C *)((u8 *)arg0 + 0x170);
    ArgB_F088C *b = (ArgB_F088C *)arg1;
    s32 b0;

    if (arg2 == 0) {
        b0 = b->unk0;
        if ((b0 == temp_v0->unk0) || (b->u4.b4 == temp_v0->unk4)) {
            func_1516972C((struct102 *)arg0);
        }
    } else if (arg2 == 0x2D) {
        if (temp_v0->unk0 == b->unk0) {
            temp_v0->unk0 = b->u4.w4;
            temp_v0->unk4 = b->unk9;
        } else if (temp_v0->unk0 == b->u4.w4) {
            temp_v0->unk0 = b->unk0;
            temp_v0->unk4 = b->unk8;
        }
    }
}

void func_150F0938(s32 arg0) {
    func_15160A58(arg0, 0x25, &D_800A1674, 2, 0x12C, 4, 0, 0xFF, 0, 0xFF, 0, -1, 0, 0, 0xFF, 1);
    func_15160A58(arg0, 2, &D_800A1680, 2, 0x12C, 0xD, 0xFF, 0xFF, 0xFF, 0xFF, 0, -1, 0, 0, 0xFF, 1);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_11C2B0/func_150F0A24.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_11C2B0/func_150F0BEC.s")

s32 func_150F0E48(Struct150F0E48Obj *arg0, s32 arg1) {
    Struct150F0E48Sub *sub;
    Struct150F0E48Src *src;

    sub = (Struct150F0E48Sub *)((u8 *)arg0 + 0xA8);
    src = sub->unk0;
    if (src->unk3B != sub->unk4) {
        return 0;
    }

    arg0->unk40 = src->unk14;
    arg0->unk44 = src->unk18;
    arg0->unk48 = src->unk1C;
    sub->unk8 += D_800A1870 * D_800BE9A4;
    sub->unkC += D_800A1874 * D_800BE9A4;
    sub->unk10 += 0.25f * D_800BE9A4;
    sub->unk8 = func_15144B68(sub->unk8);
    sub->unkC = func_15144B68(sub->unkC);
    sub->unk10 = func_15144B68(sub->unk10);
    arg0->unk38 = (sinf(sub->unk8) * 243.0f) + 780.0f;
    arg0->unk3C = (sinf(sub->unkC) * 243.0f) + 780.0f;
    arg0->unk2B = (sinf(sub->unk10) * 50.0f) + 200.0f;
    return 1;
}

typedef struct {
    s32 unk0;
    u8  unk4;
} SubA150F1020;

typedef struct {
    s32 unk0;
    union {
        s32 w4;
        u8  b4;
    } u4;
    u8  unk8;
    u8  unk9;
} ArgB150F1020;

void func_150F1020(struct260 *arg0, s32 arg1, u8 arg2) {
    SubA150F1020 *temp_v0 = (SubA150F1020 *)((u8 *)arg0 + 0xA8);
    ArgB150F1020 *b = (ArgB150F1020 *)arg1;
    s32 b0;

    if (arg2 == 0x2D) {
        if (temp_v0->unk0 == b->unk0) {
            temp_v0->unk0 = b->u4.w4;
            temp_v0->unk4 = b->unk9;
        } else {
            if (temp_v0->unk0 == b->u4.w4) {
                temp_v0->unk0 = b->unk0;
                temp_v0->unk4 = b->unk8;
            }
        block_150F1020: ;
        }
    } else if (arg2 == 0 || arg2 == 0x43) {
        b0 = b->unk0;
        if ((b0 == temp_v0->unk0) || (b->u4.b4 == temp_v0->unk4)) {
            func_1516972C((struct102 *)arg0);
        }
    }
}

void func_150F10D4(struct210 *arg0) {
    s8 sp40[0x18];
    struct260 *temp_v0;

    *(struct210 **)&sp40[0] = arg0;
    sp40[4] = *(u8 *)((s32)arg0 + 0x3B);
    *(f32 *)&sp40[8] = 0.0f;
    *(f32 *)&sp40[0xC] = *(f32 *)((s32)arg0 + 0x14);
    *(f32 *)&sp40[0x10] = *(f32 *)((s32)arg0 + 0x18);
    *(f32 *)&sp40[0x14] = *(f32 *)((s32)arg0 + 0x1C);

    temp_v0 = func_15149130(0x12C, -1, 0x4C, -1, 0, 0x3A, (struct37 *)0x18, 0xFF, 1);
    if (temp_v0 != NULL) {
        memcpy((void *)((s32)temp_v0 + 0x28), &sp40, 0x18);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_11C2B0/func_150F1170.s")

void func_150F15F8(s32 arg0, s32 arg1, u8 arg2) {
    s32 *p = &arg0;
    s32 q;
    s32 b0;

    if (arg2 == 0x43) {
        b0 = *(s32 *)arg1;
        q = *p + 0x28;
        if ((b0 == *(s32 *)q) || (*(u8 *)(q + 4) == *(u8 *)(*(s32 *)&arg1 + 4))) {
            func_1516972C((struct102 *)*p);
        }
    } else {
        q = *p + 0x28;
        func_15149514(arg1, arg2, q, q + 4, *p);
    }
}

struct func150F1684_sub {
    s32 unk0;
    u8 unk4;
};

void func_150F1684(struct func150F1684_sub *arg0, struct func150F1684_sub *arg1, u8 arg2) {
    struct func150F1684_sub *temp = (struct func150F1684_sub *)((s32)arg0 + 0x18);
    s32 word;

    if (arg2 == 0x43) {
        word = arg1->unk0;
        if ((temp->unk0 == word) || (arg1->unk4 == temp->unk4)) {
            func_1516972C((struct102 *)arg0);
        }
    }
}

typedef struct {
    u8 unk0[2];
} Pair150F16DC;

typedef struct {
    Pair150F16DC unk0;
    u8 pad2;
    u8 unk3;
} Sel150F16DC;

typedef struct {
    s32 unk0;
    s32 unk4;
} Vec2i150F16DC;

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} Vec3i150F16DC;

extern Pair150F16DC D_800A1810;
extern f32 D_800A168C[2][4][2][3];
extern f32 D_800A174C[2][4][2][3];
extern u8 D_800A180C[2][2];
extern f32 D_800A1898;
extern f32 D_800A189C;
extern f32 D_800A18A0;
extern f32 D_800A18A4;
extern f32 D_800A18A8;
extern f32 D_800A18AC;
extern f32 D_800A18B0;
extern f32 D_800A18B4;

extern s32 func_15145EA4(f32 **arg0, f32 **arg1, s32 arg2, s32 arg3);
extern void func_15102B38(s32, u8, s32, s32, f32 *, s32, s32, f32, s32, s32, s32, s32, u8, s32);

void func_150F16DC(struct127 *arg0, u8 arg1, u8 arg2, u8 arg3, s32 arg4) {
    f32 sp84[3];
    u8 sp83;
    Pair150F16DC sp80;
    f32 *sp7C;
    f32 *sp78;
    Header sp70;
    Header2 sp64;
    f32 sp5C[2];
    s32 sp50[3];

    if (arg0 == NULL) {
        return;
    }
    if (arg2 >= 4) {
        return;
    }
    if (arg1 >= 2) {
        return;
    }

    if (arg0->id == 0x23) {
        sp83 = 1;
    } else {
        sp80 = D_800A1810;
        if (sp80.unk0[arg1] & arg0->unk94) {
            return;
        }
        sp83 = 0;
    }

    if (arg0->unk1D4 == 0) {
        return;
    }

    sp7C = D_800A168C[sp83][arg2][arg1];
    sp78 = sp84;
    func_15145EA4(&sp7C, &sp78, (s32) arg0->unk1D4 + (D_800A180C[sp83][arg1] << 6), 1);

    sp70.unk0 = 3;
    sp70.unk1 = -1;
    sp70.unk2 = (func_150ADA20() % 5U) + 4;
    sp70.unk4 = 0;
    sp64.unk0 = (s32) sp84[0];
    sp64.unk4 = (s32) sp84[1];
    sp64.unk8 = (s32) sp84[2];
    func_151602C0(&sp70, &sp64, (func_150ADA20() % 0x33U) + 0x50, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0, arg3, arg4);

    sp5C[1] = ((func_150ADA68() * D_800A1898) + D_800A189C) * D_800A18A0;
    sp5C[0] = ((func_150ADA68() * D_800A18A4) + D_800A18A8) * D_800A18AC;
    sp50[0] = func_150ADA20();
    sp50[2] = func_150ADA20();
    func_15102B38((s32) arg0, D_800A180C[sp83][arg1], (s32) &D_800A168C[sp83][arg2][arg1],
                  (s32) &D_800A174C[sp83][arg2][arg1], sp5C,
                  (sp50[0] % 6U) + 8, 0xFF, (func_150ADA68() * D_800A18B0) + D_800A18B4,
                  (s32) sp84, 0xFF, 0, -1, arg3, arg4);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_11C2B0/func_150F1A00.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_11C2B0/func_150F1B48.s")

void func_150F1CB0(ActorStateFields *arg0) {
    if (arg0->field_0x84 == 0x14) {
        arg0->field_0x68 = 0x1B;
    } else {
        arg0->field_0x68 = 0xC;
    }
    arg0->field_0x69 = 0x13;
    if ((arg0->field_0x2E4 & 0x3) == 0x3) {
        arg0->field_0x69 = 0x14;
    }
    if ((arg0->field_0x2E4 & 0xC) == 0xC) {
        arg0->field_0x69 = 0x17;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_11C2B0/func_150F1D10.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_11C2B0/func_150F20F0.s")

void func_150F2230(struct127 *arg0, s32 arg1, s32 arg2) {
    struct { f32 x; f32 y; f32 z; } sp2C;
    struct { f32 x; f32 y; f32 z; } sp20;

    if ((arg0->unk1D4 != NULL) && ((arg0->unk74 & 0xF) != 0xF)) {
        sp2C.x = 0.0f;
        sp2C.y = 0.0f;
        sp2C.z = 0.0f;
        func_15143874((s16)(func_150ADA20() & 0xFF), 100.0f, &sp2C.x, &sp2C.z);
        func_15143134(&sp2C.x, &sp20.x, (s32)arg0->unk1D4 + 0x4C0);
        func_151C329C(&sp20.x, (u8)arg1, arg2);
    }
}
