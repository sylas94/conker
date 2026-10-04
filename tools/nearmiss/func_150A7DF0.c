/* ============================================================================
 * BAILED -- HAND-WRITTEN ASSEMBLY.  func_150A7DF0 (TU game_D52A0, 152 words)
 *
 * VERDICT  Not C-matchable with IDO 5.3.  This is hand-written asm, like its
 *          neighbours in the 0x150A math cluster.  Best measured C score:
 *          fastscore mism=2791  frame=-80  n=416/152   (-O2 -g3, tree default).
 *          The C below is a CORRECT semantic reconstruction (it computes exactly
 *          what the golden computes); it is kept only so the next person does
 *          not have to re-derive the maths.  It is NOT a near-miss.
 *
 * WHAT THE FUNCTION IS
 *          void func_150A7DF0(Mtx *m, f32 degX, f32 degY, f32 degZ)
 *          Euler XYZ rotation -> N64 fixed-point Mtx (s16 int part at 0x00..0x1F,
 *          u16 frac part at 0x20..0x3F).  D_8009F6B0 = 0.01745329238 = PI/180.
 *          Row values, all scaled by 65536.0f then split hi16/lo16:
 *            m00 = cy*cz                      m01 = cy*sz          m02 = -sy
 *            m10 = sx*sy*cz - cx*sz           m11 = sx*sy*sz + cx*cz
 *            m12 = sx*cy
 *            m20 = cx*sy*cz + sx*sz           m21 = cx*sy*sz - sx*cz
 *            m22 = cx*cy
 *          plus zeroed 4th row/column and int[3][3] = 1.
 *          Note golden stores `sh $zero, 0x18($a0)` TWICE (0x150A7ED4 and
 *          0x150A7F4C) -- a redundant dead store no C compiler would emit.
 *
 * EVIDENCE THAT IT IS HAND-WRITTEN  (all measured this wave)
 *
 *  1. MID-BODY STACK PUSH/POP.  Golden brackets EVERY call with
 *       addiu $sp,$sp,-8 ... jal cosf/sinf ... addiu $sp,$sp,8
 *     and keeps $a0 in a separately pushed 8-byte slot (`addiu $sp,-8; sw $a0,0($sp)`
 *     at the top, `lw $a0,0($sp); addiu $sp,8` at the bottom) -- 7 pushes / 7 pops.
 *     Across the ENTIRE game this is unique: of the 24 nonmatching .s files that
 *     contain `27BDFFF8` at all, 23 have exactly one (their prologue).  This one
 *     has seven.  Swept all 42 occurrences of `27bdfff8` in the 464 objects under
 *     conker/expected/build/src: 33 are at function offset 0; 7 are this function
 *     itself; 1 is inside the still-pragma'd func_150ADAF0; and the single
 *     remaining one (_getVol, init_20000.c, a fully matched pragma-free TU) is
 *     still a PROLOGUE -- IDO merely scheduled four sll/sra ahead of the frame
 *     adjust.  There is no precedent anywhere for a mid-body push/pop bracketing
 *     a call: IDO always pre-allocates the outgoing-argument area in the prologue.
 *
 *  2. swc1 CALLEE-SAVES.  Golden saves $f20,$f22,$f24,$f26,$f28,$f30 with six
 *     32-bit `swc1`.  Under the tree's `-mips2 -o32`, IDO emits `sdc1` -- measured:
 *     the probe below produced `sdc1 $f24/$f22/$f20` at -O2 -g3, -O2, -O1 and -g,
 *     and at `-mips1 -o32` as well.
 *
 *  3. REGISTER ALLOCATION NO IDO PASS PRODUCES.  Golden uses ALL SIX callee-saved
 *     FP registers and NOT ONE saved GPR: it moves the three float args straight
 *     into $f24/$f26/$f28 with `mtc1 $a1,$f24` etc. and never homes $a1-$a3.
 *     IDO on the same body used only $f20/$f22/$f24, homed $a1/$a2/$a3 to the
 *     stack (`sw $a2,0x58($sp)`), reloaded them around every call, and parked
 *     $a0 in $s0 -- the obvious compiler choice golden declines to make.
 *
 *  4. `addiu $t0,$zero,0x1` is materialised at 0x150A7F40, ~60 instructions
 *     before its single use in the `jr $ra` delay slot at 0x150A8044.
 *
 *  5. Two trailing `nop`s, and the duplicate dead `sh $zero,0x18($a0)` (above).
 *
 *  6. Position: game_D52A0 (0xD52A0-0xD5500) sits BETWEEN game_D4E10 and
 *     game_D5500, both already established as hand-written sin/cos/matrix asm
 *     (see the handwritten-math-cluster notes).  func_150AD960 in the same
 *     cluster uses trapping add/sub; func_150A7B80/7C10/7D00/150A6860 are
 *     64-bit-op blocked.
 *
 * FLAG SWEEP (all with the C below; no combination approaches golden)
 *     -O2 -g3  -mips2 -o32   mism=2791  n=416/152   <- tree default
 *     -O2      -mips2 -o32   mism=2830  n=420/152
 *     -O1      -mips2 -o32   mism=3950  n=532/152
 *     -g       -mips2 -o32   mism=4349  n=572/152
 *     -O2 -g3  -mips1 -o32   mism=2829  n=420/152
 *     -O2      -mips1 -o32   mism=2829  n=420/152
 *     -O1      -mips1 -o32   mism=4069  n=544/152
 *     -O2 -g3  -mips3 -o32   mism=431   n=180/152   <- emits trunc.l.s/dmfc1/
 *                            dsrl32 (64-bit); golden is 32-bit throughout, and a
 *                            -mips3 object will not link into the 32-bit ROM.
 *     -O1 -g3 / -O3          rejected by asm-processor
 *
 * RODATA NOTE (for whoever revisits): D_8009F6B0 at ROM 0x244170 is a 16-byte
 * blob = one float + 12 bytes of padding, i.e. this TU's own literal pool.  A
 * future C match would want conker.us.yaml [0x244170, .rodata, game_D52A0] plus
 * a follow-on [0x244180, rodata].  Not done -- there is nothing to attach it to.
 * ========================================================================= */

#if 0   /* semantic reconstruction only -- does NOT match, do not ship */

#include <ultra64.h>
#include "functions.h"
#include "variables.h"

extern f32 D_8009F6B0;      /* 0.01745329238f == PI/180 */
extern f32 sinf(f32);
extern f32 cosf(f32);

typedef struct {
    /* 0x00 */ s16 i[16];
    /* 0x20 */ u16 f[16];
} FixMtx;

void func_150A7DF0(FixMtx *mtx, f32 rx, f32 ry, f32 rz) {
    f32 sx, cx, sy, cy, sz, cz;
    f32 m00, m01, m02, m10, m11, m12, m20, m21, m22;
    u32 e;

    rx *= D_8009F6B0;
    cx = cosf(rx);
    sx = sinf(rx);
    ry *= D_8009F6B0;
    cy = cosf(ry);
    sy = sinf(ry);
    rz *= D_8009F6B0;
    cz = cosf(rz);
    sz = sinf(rz);

    m00 = cy * cz;
    m01 = cy * sz;
    m02 = -sy;
    m10 = sx * sy * cz - cx * sz;
    m11 = sx * sy * sz + cx * cz;
    m12 = sx * cy;
    m20 = cx * sy * cz + sx * sz;
    m21 = cx * sy * sz - sx * cz;
    m22 = cx * cy;

    mtx->i[3] = 0;
    mtx->i[7] = 0;
    mtx->i[11] = 0;
    mtx->i[12] = 0;
    mtx->i[13] = 0;
    mtx->i[14] = 0;
    mtx->f[3] = 0;
    mtx->f[7] = 0;
    mtx->f[11] = 0;
    mtx->f[12] = 0;
    mtx->f[13] = 0;
    mtx->f[14] = 0;
    mtx->f[15] = 0;

    e = m00 * 65536.0f; mtx->f[0]  = e; mtx->i[0]  = e >> 16;
    e = m01 * 65536.0f; mtx->f[1]  = e; mtx->i[1]  = e >> 16;
    e = m02 * 65536.0f; mtx->f[2]  = e; mtx->i[2]  = e >> 16;
    e = m10 * 65536.0f; mtx->f[4]  = e; mtx->i[4]  = e >> 16;
    e = m11 * 65536.0f; mtx->f[5]  = e; mtx->i[5]  = e >> 16;
    e = m12 * 65536.0f; mtx->f[6]  = e; mtx->i[6]  = e >> 16;
    e = m20 * 65536.0f; mtx->f[8]  = e; mtx->i[8]  = e >> 16;
    e = m21 * 65536.0f; mtx->f[9]  = e; mtx->i[9]  = e >> 16;
    e = m22 * 65536.0f; mtx->f[10] = e; mtx->i[10] = e >> 16;

    mtx->i[12] = 0;     /* golden really does store 0x18 twice */
    mtx->i[15] = 1;
}

#endif
