/* PARKED near-miss: func_150DFEFC  (game_10CD70.c, 964 bytes, frame 0xB0)
 *
 * BEST SCORE 110 (asm-differ -o func_150DFEFC -R --max-lines 4096; identical without -R),
 * and that is ONE INSTRUCTION away from byte-perfect -- see RESIDUAL.
 * Bounded: readelf -sW expected/build/src/game_10CD70.c.o -> size=964, so the score is real.
 * Built size 960 (mine is one instruction SHORT). .rodata / .data already IDENTICAL.
 *
 * !!! THE 110 REQUIRES A ONE-LINE FIX IN include/functions.h THAT IS NOT APPLIED !!!
 *     line 1087:  u8   func_150ADA20(void);      <- present in the tree, WRONG
 *                 s32  func_150ADA20(void);      <- what this function needs
 *     func_150ADA20 is a #pragma GLOBAL_ASM stub (asm/nonmatchings/game_DAE50/func_150ADA20.s),
 *     so its u8 return is an unverified guess, and it is load-bearing:
 *         with u8  ... score 966        with s32 ... score 110
 *     The mechanism, isolated in a micro-benchmark (scratchpad t3.c, cases c1-c4): when the
 *     result of a u8-returning call has to survive a later call, IDO materialises the
 *     zero-extension into the save -- "andi s1,v0,0xff" -- where the golden asm has a bare
 *     "move s1,v0" followed by the source own "andi a1,s1,0xff" at the point of use.
 *     No cast at the call site suppresses it: (u32)f(), (s32)f() and plain f() all emit the
 *     andi (cases c1/c2/c3); only a word-returning declaration (case c4) reproduces golden.
 *     Assigning to s32 locals also works but costs 3 stack homes the frame does not have.
 *     BLAST RADIUS -- PARTIALLY MEASURED, and it looks small.  107 TUs / 613 call sites reference
 *     func_150ADA20.  With the s32 prototype in place I rebuilt six RNG-heavy TUs and compared
 *     .text against expected/:
 *         game/done/game_3C3D0   .text IDENTICAL
 *         game/done/game_122650  .text IDENTICAL
 *         game_1028F0            .text IDENTICAL
 *         game_108E90            .text IDENTICAL
 *         game_100810            .text IDENTICAL
 *         game_111670            BUILD FAILED  <- and it builds fine with the u8 header
 *     The one failure is not a codegen change, it is a duplicate declaration:
 *         cfe: Error: src/game_111670.c, line 66: redeclaration of 'func_150ADA20';
 *              previous declaration at line 1087 in file 'include/functions.h'
 *         cfe: Error: src/game_111670.c, line 66: Incompatible function return type
 *     i.e. game_111670.c carries its own local "u8 func_150ADA20(void);" that has to be deleted
 *     or retyped along with the header line.  So the change is two lines, and five of five
 *     compilable RNG-heavy TUs were byte-identical under it.  Still needs a full make +
 *     make replace + ROM sha1 before it ships -- but this is a SYSTEMIC unlock, not a
 *     one-function trick: every function in the tree that keeps an RNG result across a call is
 *     currently being compiled against a wrong prototype.
 *
 * WHAT IT IS.  Per-frame update for one smoke/spark emitter bolted to an actor.  Validates the
 * actor handle (obj->interaction_state != 0 and obj->unique_id == src->id), then runs three
 * independent countdowns off D_800BE9E4: timer0 spawns a func_151602C0 particle at the actor
 * truncated position, timer1 runs a 2..4 iteration loop emitting func_15107700 puffs with colour
 * AE/D2/FF/(rand%61+150), timer2 emits one func_15107B78.  Each timer is re-armed with its own
 * random interval.  Returns void; the failure path writes arg0->unkE = -1.
 *
 * FRAME DECODE -- this came out EXACTLY right on the first build (frame 0xB0 on draft 1) and it
 * pins the declaration list completely, because two of the six locals sit in alignment padding:
 *   saved regs 0x38..0x78 (f20,f22,f24 + s0-s7,fp,ra), arg build 0x00..0x2F, one compiler temp
 *   at 0x78 (the spilled &arg0->src), home area 0x88..0xB0:
 *     0xAC  src      (4, register-only -- its home is never touched)
 *     0xA8  obj      (4, homed: sw t6,0xa8(sp) once, lw a0,0xa8(sp) three times)
 *     0xA7  count    (1, register-only; lives in the 2 bytes of padding above header)
 *     0xA0  header   (Header, 6 -- sb 3 / sb -1 / sh / sb 0 at +0,+1,+2,+4)
 *     0x94  header2  (Header2, 12 -- the three trunc.w.s of the actor position)
 *     0x8C  colour   (u8[4] -- 0xAE,0xD2,0xFF,rand)
 *   count cannot go anywhere else: putting it in the 0x90..0x93 gap instead pushes colour
 *   to 0x90 and golden has it at 0x8C, so the order src,obj,header,header2,count,colour is the
 *   only one that fits.  Adding a 7th scalar moves the compiler temp from 0x78 to 0x7c -- that
 *   is the measurement that proved the list is exactly six long.
 *
 * MEASURED NEGATIVES (each re-scored through make + buildlock + real asm-differ):
 *   - the six locals above, u8 func_150ADA20 ............................ score 966
 *   - + s32 r for the first rand of each block (7 locals), u8 proto ...... score 580
 *   - + s32 r,r2,r3 for all three loop rands (9 locals), u8 proto ........ score 361, frame 0xB8
 *       (fixes every andi but overshoots the home area by 4 bytes)
 *   - dropping src and writing arg0->src.timerN instead .................. score 2290, 932 bytes
 *       (the golden "addiu v0,s4,0x28" + "lh 6(v0)" only appears with the pointer local;
 *        the direct form collapses to "lh 0x2e(s4)" and loses ~8 instructions)
 *   - u8- or s16-typed rand locals instead of s32 ....................... still emit the andi
 *
 * ONE MORE LEVER THAT PAID: IDO reverses comparison operands.  "beql t9(src->id), t0(obj->uid)"
 * means the source is (obj->unique_id != src->id), not (src->id != obj->unique_id); writing it
 * the other way round swaps the two lbu instructions.
 *
 * RESIDUAL -- the ENTIRE function is byte-identical except three instructions at 0x930:
 *     golden   930: lw   t6,0x78(sp)   93c: sh t0,8(t6)   940: move v0,t6
 *     mine     930: lw   v0,0x78(sp)   93c: sh t0,8(v0)   (no move)
 *   i.e. at the tail of the timer1 block golden reloads the spilled src into a scratch register
 *   for the store and then restores the variable own register with a move, while mine reloads
 *   straight into v0 and saves the instruction.  The identical construct at the tail of the
 *   timer0 block (0x7a0) reloads TWICE (lw t4 / sh / lw v0) and matches exactly in both, so this
 *   is the merge-point reload of a spilled local, decided by liveness on the not-taken side of
 *   the branch (timer0 and timer2 get "bgezl", timer1 gets a plain "bgez").
 *   Not reachable from any spelling tried; this is a permuter job.
 *
 * TU state: the #pragma GLOBAL_ASM for func_150DFEFC is LIVE in game_10CD70.c and
 * include/functions.h is UNMODIFIED; this file is the working C only.
 */

/* The 12-byte record at +0x28 that func_150E02C0 also hands to func_15149514 as
 * (arg0 + 0x28, arg0 + 0x2C): an actor handle plus three independent countdowns. */
typedef struct {
    /* 0x00 */ struct127 *obj;
    /* 0x04 */ u8  id;
    /* 0x05 */ u8  pad5;
    /* 0x06 */ s16 timer0;
    /* 0x08 */ s16 timer1;
    /* 0x0A */ s16 timer2;
} SmokeSource; /* size 0xC */

typedef struct {
    /* 0x00 */ u8  pad0;
    /* 0x01 */ u8  unk1;
    /* 0x02 */ u8  pad2[0xA];
    /* 0x0C */ u8  unkC;
    /* 0x0D */ u8  padD;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ u8  pad10[0x18];
    /* 0x28 */ SmokeSource src;
} SmokeEmitter;

/* func_151602C0 signature copied from its LIVE C definition in game_18D770.c.
 * func_15107B78 from its LIVE C definition in game_133190.c.
 * func_15107700 recovered from its own golden prologue (sll/sra 16 on a1..a3; lh at 0x13e and
 * 0x142 => s16 stack params; lwl/lwr through the word at 0x144 => u8 *), and it matches the
 * tail of func_15107C1C signature in game_133190.c exactly. */
extern struct225 *func_151602C0(Header *, Header2 *, s32, s32, s32, s32, u8, u8, s32, u8, s32);
extern void func_15107700(struct127 *, s16, s16, s16, s32, f32, f32, s16, s16, u8 *, u8, s32);
extern void func_15107B78(struct127 *, s32, s32, s32, s32);

void func_150DFEFC(SmokeEmitter *arg0) {
    SmokeSource *src;
    struct127 *obj;
    Header header;
    Header2 header2;
    s8 count;
    u8 colour[4];

    obj = arg0->src.obj;
    src = &arg0->src;
    if ((obj->interaction_state == 0) || (obj->unique_id != src->id)) {
        arg0->unkE = -1;
        return;
    }
    src->timer0 -= D_800BE9E4;
    if (src->timer0 < 0) {
        header2.unk0 = (s32)obj->x_position;
        header2.unk4 = (s32)obj->y_position;
        header2.unk8 = (s32)obj->z_position;
        header.unk0 = 3;
        header.unk1 = -1;
        header.unk2 = (func_150ADA20() % 0xBU) + 5;
        header.unk4 = 0;
        func_151602C0(&header, &header2, (func_150ADA20() % 0x79U) + 0x32, 0xFF, 0xFF, 0xFF, 0xFF, 0, 0, arg0->unkC, arg0->unk1);
        src->timer0 = (func_150ADA20() % 0x51U) + 0x45;
    }
    src->timer1 -= D_800BE9E4;
    if (src->timer1 < 0) {
        count = (func_150ADA20() % 3U) + 2;
        do {
            colour[0] = 0xAE;
            colour[1] = 0xD2;
            colour[2] = 0xFF;
            colour[3] = (func_150ADA20() % 0x3DU) + 0x96;
            func_15107700(obj, (s16)(func_150ADA20() & 0xFF), (s16)((func_150ADA20() % 0x81U) - 0x3F), (s16)((func_150ADA20() % 0x15U) + 0xA), 4, 40.0f, (func_150ADA68() * 20.0f) + 25.0f, 0, 2, colour, arg0->unkC, arg0->unk1);
            count--;
        } while (count > 0);
        src->timer1 = (func_150ADA20() % 0x8DU) + 0x19;
    }
    src->timer2 -= D_800BE9E4;
    if (src->timer2 < 0) {
        func_15107B78(obj, (s16)(func_150ADA20() & 0xFF), (s16)((func_150ADA20() & 0x7F) - 0x40), arg0->unkC, arg0->unk1);
        src->timer2 = (func_150ADA20() % 0x1AU) + 0xF;
    }
}
