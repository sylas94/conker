/* PARKED near-miss: func_10008CE8 in TU init_8180  (the TU's ONLY remaining pragma)
 *
 * SCORE      fastscore mism=5   frame=-64 (0x40, CORRECT)   n=126/126 (CORRECT)
 *            Scored IN-FILE: this body spliced over the #pragma GLOBAL_ASM line in the
 *            real conker/src/init_8180.c, per the wave brief. Isolated scoring lies here.
 *            Reproduce:  splice the body below over the pragma, then
 *                        python3 tools/fastscore.py init_8180 func_10008CE8
 *
 * REMAINING DIFF ROWS -- all five are the SAME single fact:
 *   idx16    ours=afae0030  gold=afae0034     sw t6, 0x30(sp)  vs  0x34(sp)
 *   idx55    ours=afa90028  gold=afa9002c     sw t1, 0x28(sp)  vs  0x2C(sp)
 *   idx61    ours=8fab0030  gold=8fab0034     lw t3, 0x30(sp)  vs  0x34(sp)
 *   idx99    ours=8fab0028  gold=8fab002c     lw t3, 0x28(sp)  vs  0x2C(sp)
 *   idx102   ours=8faf0030  gold=8faf0034     lw t7, 0x30(sp)  vs  0x34(sp)
 * Every other one of the 126 words is byte-identical (relocations masked), including the
 * frame size, the two branch-likely loops, all register names, and both %hi/%lo pairs.
 *
 * WHAT THE BLOCKER IS
 *   Two compiler CSE temps live on the stack:
 *       t_A = &D_8003CA3C[idx]        (address CSE: lhu at the compare, sh at the update)
 *       t_B = idx * 4                 (scaled-index CSE, used twice to index D_8003CA48)
 *   plus one named local (the sequence-data offset, `sp3C`).
 *   Golden's local area is 0x28..0x3F and holds the three values at 0x2C / 0x34 / 0x3C.
 *   Ours holds them at 0x28 / 0x30 / 0x3C.
 *   i.e. IDO gives each item an 8-byte slot; GOLDEN anchors the 4-byte value at slot+4,
 *   OURS anchors the CSE temps at slot+0 (our named local IS at slot+4, matching).
 *   It is a uniform +4 anchoring of the temp slots, nothing semantic.
 *
 *   MEASURED LAW (probe, same TU, -O2 -g3):
 *       0 extra named locals  -> frame 0x40, temps at 0x28/0x30   (slot+0)   <-- ours
 *       1 extra named local   -> frame 0x48, temps at 0x2C/0x34   (slot+4)   <-- golden's
 *       2 extra named locals  -> frame 0x48, temps at 0x28/0x30   (slot+0)
 *   So the +4 anchoring IS reachable, but only by paying an extra 8-byte named-local slot,
 *   which then shifts the incoming-arg reads (0x40/0x43/0x44 -> 0x48/0x4B/0x4C) and sp3C,
 *   costing 13 rows instead of 5. Every attempt to get +4 anchoring at frame 0x40 failed.
 *   Equivalent framing: golden behaves as if the saved-register area were 5 words
 *   (0x18..0x2C, only 4 used) instead of 4 (0x18..0x28).
 *
 * DO NOT REPEAT -- every spelling measured, with its in-file mism:
 *   5   BEST (this file): u8 idx / s32 arg1; locals `s32 sp3C; void *temp; u32 i;`
 *       tail with &D_8003CA58[idx] inlined (no `seq` local).
 *   5   same, arg1 declared u32                       (identical output)
 *   5   same, temp declared u8 * or s32               (identical output)
 *   5   same, sp3C declared u32                       (identical output)
 *   5   `if (D_8003CA48[idx] == 0)` / `if (!D_8003CA48[idx])` instead of `== NULL`
 *   5   `sp3C = (s32)(D_8003CD40->seqArray[arg1].offset);` extra parens
 *   5   decl orders sp3C|i|temp and sp3C|temp|i  (12 of 24 type x order combos, all 5)
 *   7   `s32 sp3C` moved to the outer if's block scope        (slots 0x28/0x30/0x34)
 *   7   sp3C AND temp both at block scope                     (slots 0x28/0x30/0x38)
 *   7   decl order i|temp|sp3C                                (sp3C slot moves to 0x34)
 *   8   `s32 i` instead of `u32 i`   (3 extra rows: sltu -> slt)
 *   9   for-loops instead of while-loops
 *   9   `s32 idx` parameter          (lbu 0x43 becomes lw 0x40, 4 extra rows)
 *  13   ADD an `ALCSeq *seq` local for &D_8003CA58[idx]  -> temps land at 0x2C/0x34
 *       (CORRECT!) but frame becomes 0x48 and 13 other rows break. Closest structural
 *       relative of golden -- if anyone finds how to buy the +4 anchoring for free,
 *       THIS is the variant to combine it with.
 *  13   `u16 *p = &D_8003CA3C[idx];` used for both the compare and the store (frame 0x48)
 *  13   no `temp` local at all (call func_10004074(D_8003CA48[idx]) directly):
 *       the freed pointer then lands in a0 instead of v0, killing `or a0,v0,zero`
 *       and 7 more register rows. The `temp` local is LOAD-BEARING (delete it -> 13).
 *  13   an EXTRA local of ANY size to buy the +4 anchoring: u8 / s16 / u8[4], declared
 *       first, last or in the middle -- IDO charges a full 8-byte slot for every one of
 *       them, so the frame always goes 0x40 -> 0x48. There is no cheap 4-byte local.
 *       (u8 pad first: slots 0x2C/0x34/0x40 -- temps CORRECT, frame and sp3C wrong.)
 *  18   u8 pad[8]
 *  19   `temp` assigned BEFORE the null test instead of inside it
 *  75   sp3C inlined into the func_10004514 argument (n=125: IDO then evaluates
 *       seqArray[arg1].offset AFTER allocate_memory; golden evaluates it before and
 *       spills it in the jal delay slot)
 *  86   one variable reused for both the freed pointer and the offset (n=127)
 *
 * NOT TRIED / NEXT IDEAS
 *   - decomp-permuter on this body (the residue is exactly a stack-slot ranking tie).
 *   - find a MATCHED -O2 -g3 function elsewhere in the tree whose CSE temps sit at
 *     slot+4 and read its source: that is the one datum that would settle the law.
 *   - OPT_FLAGS is NOT available as a lever here: init_8180.c is full of already-matched
 *     -O2 -g3 code, so the TU flags are pinned.
 *
 * SEMANTICS ARE BELIEVED CORRECT AND THE SOURCE IS HONEST: no volatile, no pointer-to-
 * parameter, no shadowing static, no dead frame-shaping local (the one local that looked
 * decorative, `temp`, passed the load-bearing test above: deleting it makes the score
 * WORSE, 5 -> 13).
 */
#include <ultra64.h>

/* --- context that already exists in conker/src/init_8180.c ---
extern N_ALCSPlayer *D_8003C900[];
extern u16           D_8003C910[];
extern u16           D_8003CA3C[];
extern void         *D_8003CA48[];
extern ALCSeq        D_8003CA58[];
extern ALSeqFile    *D_8003CD40;
s32  allocate_memory(s32 size, s32 arg1, s32 arg2, s32 arg3);
void func_10004074(void *ptr);
s32  func_10004514(s32 devAddr, void *dramAddr, u32 size, s32 arg3);  (functions.h)
   ------------------------------------------------------------- */

s32 func_10008CE8(u8 idx, s32 arg1) {
    s32 sp3C;
    void *temp;
    u32 i;

    i = 0;
    func_10018C60(D_8003C900[idx]);
    while ((n_alCSPGetState(D_8003C900[idx]) != 0) && (i < 2000000)) {
        i++;
    }
    if (i >= 2000000) {
        func_10018C60(D_8003C900[idx]);
        while ((n_alCSPGetState(D_8003C900[idx]) != 0) && (i < 4000000)) {
            i++;
        }
    }
    if (arg1 != D_8003CA3C[idx]) {
        if (D_8003CA48[idx] != NULL) {
            temp = D_8003CA48[idx];
            func_10004074(temp);
            D_8003CA48[idx] = NULL;
        }
        sp3C = (s32)D_8003CD40->seqArray[arg1].offset;
        D_8003CA48[idx] = (void *)allocate_memory(D_8003C910[arg1], 0xFF, 2, 2);
        if (D_8003CA48[idx] == NULL) {
            return -1;
        }
        func_10004514(sp3C, D_8003CA48[idx], ALIGN16(D_8003C910[arg1]), 1);
        D_8003CA3C[idx] = arg1;
    }
    n_alCSeqNew(&D_8003CA58[idx], D_8003CA48[idx]);
    func_10018CB0(D_8003C900[idx], &D_8003CA58[idx]);
    func_10017B30(D_8003C900[idx]);
    return 0;
}
