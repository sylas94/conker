/* func_1500AD84  --  game_36680.c  --  97 instructions, leaf, framesize 0, 0 callees, 0 fp
 *
 * STATUS: NEAR MISS.  Best honest score 975.  Best score of any kind 675 (uses an
 *         invented local copy of arg2 -- see V7 -- which I do NOT consider shippable).
 *         Pragma restored in conker/src/game_36680.c; tree left clean.
 *
 * The "// GOTO hell" comment that sat above the pragma is WRONG and cost this function
 * several passes.  There is no goto structure: it is one if/else on (arg1 != 0xFF) whose
 * else-arm is laid out last, followed by a common tail.  Control flow, block order,
 * access widths and every address CSE below are EXACT against golden.
 *
 * ================= FRAME DECODE =================
 * No `addiu sp` at all: framesize 0, no saved regs, no home area.  So NOTHING is spilled
 * and the frame gives zero evidence about the declaration list.  Every local is inferred
 * from CSE behaviour instead (see below).
 * Params: a0,a1,a2 (a2 is moved to a3 by golden's first instruction -- that move is the
 * entire residual).  Signature is pinned by the live caller at game_36680.c:899
 *   func_1500AD84(i, pair[0], pair[1])   with `u16 *pair`
 * and by the in-file prototype `extern void func_1500AD84(s32, s32, s32);`.
 *
 * ================= MEASUREMENT LOG (all bounded --max-lines 97) =================
 * V1  u8 *rec, no locals, rec[0]/rec[1] read directly            1380
 *       -> golden loads rec[1] ONCE; IDO reloaded it across the store to D_800DDBD0[arg0]
 * V2  V1 + `s32 level = rec[1]`                                   975   (-405)
 *       -> reload gone.  This is the honest best.
 * V3  V2 + `s32 flags = rec[0]`                                   975   (no change;
 *       only moved the flags value a3 -> v1.  rec[0] CSEs fine WITHOUT a local.)
 * V4  V3, declarations permuted twice (rec-last, then attr-first) 975   (BYTE-IDENTICAL
 *       output both times: declaration order is a proven NO-OP for this function)
 * V5  V3 with `u16 arg2` parameter                                905   (-70)
 *       -> the two `lw ..,8(sp)` reloads collapse to one `lhu ..,0xa(sp)`
 * V6  V5 + `u16 attr; attr = arg2;`                               815   (-90)
 *       -> reload gone but adds `andi t6,a2,0xffff` for the u16->u16 conversion
 * V7  V6 with s32 param and `s32 attr`                            675   (-140)
 *       -> home store gone.  BUT IDO coalesces `attr = arg2` into a2, so the copy
 *          disappears and the function is ONE INSTRUCTION SHORT of golden.
 * V8  V7 minus the `flags` local                                  675   (identical)
 * V9  Elem80095CE0 struct retype, no level/attr locals            1380
 *       -> a struct type does NOT buy CSE across an intervening store.  Combined with
 *          V1 this proves `level` is a REAL SOURCE LOCAL, not an IDO CSE.
 *
 * SAFE-RETYPE FINDING (reusable): retyping `extern u8 D_80095CE0[]` to a 10-byte record
 * array and rewriting the one use inside the ALREADY-MATCHED func_1500AF08 from
 *   D_80095CE0[D_800DDBC0[arg1] * 10] & 4   ->   D_80095CE0[D_800DDBC0[arg1]].unk0 & 4
 * left func_1500AF08 at score 0.  The retype is safe if anyone wants it later.
 *
 * ================= RESIDUAL: ALLOCATION =================
 * Golden's register assignment is
 *      a3 = arg2 (or a source local holding it)   a2 = rec[0]   v1 = rec
 *      t9 = level                                 v0 = &D_800DDBD0[arg0]
 * Mine is shifted one slot: the compiler temps take a2/a3 and the 3rd PARAMETER is left
 * in memory (homed at entry with `sw a2,8(sp)`, reloaded at each use).  IDO allocates
 * parameters before temps, so golden must have had arg2 in the allocation set and mine
 * does not -- with byte-identical usage (2 reads, same basic block, same nesting).
 * I could not find the lever.  Ruled out by measurement: declaration order (V4),
 * local count (V1 vs V2 vs V3 all home arg2), parameter type (V5), record type (V9).
 * Next thing to try is the permuter -- this is exactly a one-register scheduling nit.
 *
 * ================= PARKED SOURCE (V2, the honest best, score 975) =================
 * Needs these externs ahead of it in game_36680.c (D_800DDBD0 is already at line 7):
 *   extern u8 D_80095CC4[];  extern u8 D_80095CE0[];   extern u8 D_800DDBC0[];
 *   extern u8 D_800DDBE0[];  extern u8 D_800DDBF0[];   extern u8 D_800DDC20[][2];
 *   extern u8 D_800DDC80[];  extern u16 D_800BE478[];  extern s16 D_800BE438[][2];
 * (D_800DDC00/04/08 come from variables.h as s32.)
 */

void func_1500AD84(s32 arg0, s32 arg1, s32 arg2) {
    s32 level;
    u8 *rec;

    if (arg1 != 0xFF) {
        rec = &D_80095CE0[arg1 * 10];
        level = rec[1];
        D_800DDBD0[arg0] = level;
        if (rec[0] & 0x10) {
            D_800DDBD0[arg0] = level - 1;
            D_800DDBE0[arg0] = level - 1;
        } else {
            D_800DDBE0[arg0] = 0;
        }
        if (rec[0] & 0x80) {
            D_800DDBF0[arg0] = 2;
        } else {
            D_800DDBF0[arg0] = 1;
        }
        D_800BE438[arg0][0] = *(s16 *)(rec + 4);
        D_800BE438[arg0][1] = *(s16 *)(rec + 6);
        D_800DDBC0[arg0] = arg1;
        D_800DDC80[arg0] = arg2 & 0xFF7F;
        if (arg2 & 0x80) {
            D_800DDC00 |= 1 << arg0;
        }
        if (rec[0] & 1) {
            D_800DDC04 |= 1 << arg0;
        }
        if (rec[0] & 8) {
            D_800DDC08 |= 1 << arg0;
        }
    } else {
        D_800DDBD0[arg0] = 0;
    }
    D_800BE478[arg0] = 0;
    D_800DDC20[arg0][0] = D_80095CC4[arg0];
    D_800DDC20[arg0][1] = D_80095CC4[arg0];
}
