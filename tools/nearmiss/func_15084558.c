/* func_15084558  --  game_AEB40.c  (309 asm lines, 0 mul, 0 fp, 3 callees)
 *
 * BEST SCORE 3240 (base with the pragma restored: n/a -- cold decompile).
 * Progression: 3800 (first build) -> 4203 -> 3240.
 *
 *   bash tools/buildlock.sh bash -c 'cd conker && make -s build/src/game_AEB40.c.o VERSION=us \
 *       && python3 ../tools/asm-differ/diff.py -o func_15084558 -R --max-lines 4096'
 *
 * ============================ WHAT IS SETTLED ============================
 *
 * ACTOR INDEXING IS *BOTH* FORMS, in the same function -- read them separately:
 *   - `subu s7,s0,t9 ; li at,0x32C ; div ; mflo s7'  is the POINTER DIFFERENCE
 *     `arg0 - D_800CC2D0'.  It must be written INLINE inside the j-loop
 *     (`if (j == arg0 - D_800CC2D0) continue;'): golden computes it AFTER the
 *     `blez' loop guard, i.e. IDO hoisted it from inside into the outer-loop
 *     preheader.  A local assigned before the loop puts it BEFORE the blez.
 *   - `sll/subu/addu ladder (4x-x, *4+x, *4-x, *4-x, *4) = 812x' is the LOCAL
 *     index `D_800CC2D0[j]'.  Confirmed 812 by hand.
 *
 * ONE LOOP GUARD, NOT TWO.  `if (count > 0) { for (i = 0; i != count; i++) }'
 * emits BOTH a `blez' and a `beqz' (measured, 4203).  Golden has one `blez',
 * so the source is a bare `for (i = 0; i < count; i++)'.
 *
 * DECLARATION ORDER IS PINNED BY `count'.  Golden spills count to 0x7C of a
 * 0x90 frame => (0x90-0x7C)/4 = 5 => count is the FIFTH declared local.  With
 * count third the spill landed at 0x84 (measured).  The order below
 * (id, list, i, j, count, ...) reproduces 0x7C AND the 0x44 temp for `id*4'.
 *
 * THE 3-CALLEE PROTOTYPES: func_1508434C(u8*) and func_100043B4(s32*,u32) are
 * already live in this TU; func_10004074 has NO prototype in functions.h
 * (line 876 is commented out) and takes the s32 element value, so it needs the
 * file-local `extern void func_10004074(s32);' above.
 *
 * ========================= THE TWO OPEN QUESTIONS =========================
 *
 * (1) THE DEAD COUNTING LOOP.  Golden's outer-loop body opens with a 4x-UNROLLED
 *     EMPTY loop `t5 = 0..i' that also walks a POINTER `v0 = list; v0++' and
 *     then throws BOTH away (t5 := 0 immediately after; v0 is never read).  It
 *     also leaves a dead `addu s0,s6,s5' (= list + i) in the entry delay slot.
 *     Reading: IDO substituted the induction variable's FINAL VALUE (list + i)
 *     and never re-ran DCE over the now-dead walk.
 *     MEASURED:
 *       `ptr = list; for (j=0;j<i;j++) ptr++;'  + later uses spelled `list[i]'
 *            -> loop kept, POINTER DELETED (score 3800/3240): 4 instrs missing
 *               (`addu s0,s6,s5', `move v0,s6', `addu v0,s6,t5', and the two
 *               `bne'->`bnel' rotations).
 *       same loop, later uses spelled `*ptr'
 *            -> pointer KEPT but in a SAVED register (s5), which pushes `i' to
 *               s6 and SPILLS `list' -- 10 saved-reg candidates for 9 registers
 *               (score 4203).  Golden has exactly 9 and `ptr' is NOT one.
 *       `for (ptr = list; ptr < &list[i]; ptr++) {}'  -> 12518, wrecks the loop.
 *       `oid = *ptr; ptr++;' as the body (dead load) -> load DCE'd, pointer
 *            still deleted (3240, current).
 *     STILL UNKNOWN: the spelling that keeps a DEAD pointer walk.
 *
 * (2) THE s8 LOOP-INVARIANT.  Golden hoists &D_800CC2D0 into s8 and computes
 *     the 187-loop's end sentinel (&D_800D1874) locally inside the flagB block.
 *     This build does the opposite (s8 = &D_800D1588+0x2ec, &D_800CC2D0
 *     recomputed with lui/addiu inside the j-loop).  Both have exactly 9
 *     saved-register candidates for 9 registers, so this is purely a RANKING
 *     inversion.  By the "first use in source position" law &D_800CC2D0 (used
 *     at the top of the j-loop) should win, and it does not.
 *     MEASURED: `other = D_800CC2D0 + j;' instead of `&D_800CC2D0[j]' makes it
 *     WORSE (12518; base moves to s7 and 0x32C lands in s8 as `li s8,0x32c').
 *
 * ================== A THIRD DIFF THAT IS *NOT* CLOSEABLE ==================
 *
 * SPLAT'S INTERIOR AUTO-SYMBOLS MAKE THE OBJECT UN-MATCHABLE BY CONSTRUCTION.
 * The 187-element clear loop `for (k=0;k<187;k++) if (D_800D1588[k]==x) ...'
 * is unrolled by IDO with a 3-iteration FRONT PEEL (187 & 3 == 3) and 46x4
 * iterations from index 3 (0x1594) to index 187 (0x1874) -- the arithmetic
 * checks exactly: 0x1874-0x1588 = 0x2EC = 187*4.
 * But conker/undefined_syms_auto.txt lines 7109-7111 define
 *     D_800D158C = 0x800D158C;  D_800D1590 = 0x800D1590;  D_800D1594 = 0x800D1594;
 * because the STILL-ASM version of this function references those addresses.
 * expected/build/src/game_AEB40.c.o therefore carries
 *     R_MIPS_HI16 D_800D158C / D_800D1594 / D_800D1874   (addend 0)
 * while ANY C spelling of `D_800D1588[k]' carries
 *     R_MIPS_HI16 D_800D1588                             (addend 4/8/0xC/0x2EC)
 * and, because o32 relocations are REL, the addend lives IN THE INSTRUCTION:
 *     mine     3190: 2442000c  addiu v0,v0,12       31a0: ac200004  sw zero,4(at)
 *     expected 31a8: 24420000  addiu v0,v0,%lo(D_800D1594)
 * The LINKED bytes are identical (the linker adds the addend), so the ROM stays
 * byte-perfect, but `cmp' on .text can never be clean and the score can never
 * reach 0.  6 instructions of the residue are this artifact.
 * The only way to get addend-0 relocations is to name the three interior
 * symbols and hand-write the peel, which is a manual unroll = a FAKE, refused.
 * => this function is verifiable ONLY by the ROM gate, not by score 0.
 *
 * REMAINING NON-REGISTER DIFFS at 3240 (25 of 490 lines; the rest are register
 * renames downstream of (1) and (2)):
 *   2f58/2f6c  s8 invariant                                    -- open (2)
 *   2f8c/2f94/2fa8 + two bne/bnel  dead pointer walk           -- open (1)
 *   2fd4/2fd8  the lui/addiu for &D_800CC2D0 inside the j-loop -- follows (2)
 *   3024       `move t4,v1' -- golden reads other->unk2C9 into TWO registers
 *              (one feeds `blez'+`andi 1', one is the k-loop bound).  Writing
 *              `for (k = 0; k < other->unk2C9; k++)' instead of the `n' local
 *              made it worse (re-read per iteration).  1 instruction.
 *   3158/316c/3174, 3220/3234/323c, 329c/32a4  argument-setup SCHEDULING:
 *              golden emits `li a1,3' early and `move s0,a3' in the branch
 *              delay slot (loads into a temp, copies to the saved register);
 *              this build coalesces the load straight into s0.
 *   318c..31c4 the splat symbol artifact above -- NOT CLOSEABLE.
 */

extern void func_10004074(s32 arg0);

void func_15084558(struct127 *arg0) {
    u8 id;
    u8 *list;
    s32 i;
    s32 j;
    s32 count;
    s32 k;
    s32 n;
    s32 flagA;
    s32 flagB;
    s32 flagC;
    struct127 *other;
    u8 *olist;
    u8 *ptr;
    u8 oid;
    s32 tmpA;
    struct124 *tmpB;

    id = arg0->id;
    if (id == 0xFF) {
        return;
    }
    if ((&D_800D19A0)[id] == 0) {
        return;
    }
    count = arg0->unk2C9;
    list = *(u8 **)((u8 *)arg0 + 0x2C4);
    func_1508434C((u8 *)arg0);
    for (i = 0; i < count; i++) {
        flagA = 1;
        flagB = 1;
        flagC = 1;
        ptr = list;
        for (j = 0; j < i; j++) {
            oid = *ptr;
            ptr++;
        }
        for (j = 0; j < 25; j++) {
            if (j == arg0 - D_800CC2D0) {
                continue;
            }
            other = &D_800CC2D0[j];
            if (other->interaction_state == 0) {
                continue;
            }
            if (other->id == 0xFF) {
                continue;
            }
            if (other->unk5 == 2) {
                continue;
            }
            n = other->unk2C9;
            olist = *(u8 **)((u8 *)other + 0x2C4);
            for (k = 0; k < n; k++) {
                oid = olist[k];
                if (oid == list[i]) {
                    flagA = 0;
                }
                if ((D_800D1588[oid] == D_800D1588[list[i]]) && (D_800D1588[oid] != 0)) {
                    flagB = 0;
                }
                if ((D_800D1C90[oid] == D_800D1C90[list[i]]) && (D_800D1C90[oid] != 0)) {
                    flagC = 0;
                }
            }
        }
        if (flagB != 0) {
            tmpA = D_800D1588[list[i]];
            if (tmpA != 0) {
                func_100043B4((s32 *)(tmpA - 0x10), 3);
                for (k = 0; k < 187; k++) {
                    if (tmpA == D_800D1588[k]) {
                        D_800D1588[k] = 0;
                    }
                }
            }
        }
        if (flagC != 0) {
            tmpB = D_800D1C90[list[i]];
            if (tmpB != 0) {
                func_100043B4((s32 *)((u8 *)tmpB - 0x10), 3);
                D_800D1C90[list[i]] = NULL;
            }
        }
        if (flagA != 0) {
            if ((&D_800D19A0)[list[i]] != 0) {
                if (D_800C5C08[id] != 0) {
                    func_10004074(D_800C5C08[id]);
                    D_800C5C08[id] = 0;
                    func_10004074(D_800C6070[id]);
                    D_800C6070[id] = 0;
                }
                if (D_800C6360[id] != 0) {
                    func_10004074(D_800C6360[id]);
                    D_800C6360[id] = 0;
                }
            }
        }
    }
}
