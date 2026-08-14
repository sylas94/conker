/* func_1000A03C  --  conker/src/init_8F90.c   (222 asm lines, 0 fp, 3 callees)
 * PARKED AT 2570.  max_score 24600.  Residual: ALLOCATION + BASIC BLOCK.
 *
 * init_8F90 carries NO OPT_FLAGS override (conker/Makefile lines 118-135 list
 * init_17F10/17F80/19B50/1AAE0/1C060/1E480/1E4A0/1E530/1FB40/20000/214F0/22040/
 * 22460 and game_221290; 8F90 is not among them), so the global -O2 -g3 applies.
 *
 * Score history (`-o func_1000A03C -R --max-lines 4096`, expected/ seeded from a
 * clean pragma build of the TU -- it was NOT seeded before, see below):
 *    4600  build #1: 9 locals, list heads read through a cast-pointer macro
 *    3814  D_800406A0 retyped file-locally instead (see NEGATIVE-TURNED-POSITIVE)
 *    4182  + head/spare/entry/voice/bank locals, node and cur SEPARATE  (worse)
 *    2991  + node and cur MERGED into one variable  (golden uses $s0 for both)
 *    2580  + headNext/spareNext locals  -> frame finally 0x78, all three
 *          observable stack offsets (0x64/0x68/0x74) now match golden
 *    2580  - `status' local dropped: exactly neutral, so it is NOT in golden
 *    2570  + compare written `node->unk10 == mesg->dramAddr' (see below)
 *
 * ===================== WHAT THE MEASUREMENTS ESTABLISHED =====================
 *
 * 1. THE FRAME.  framesize 0x78; saved s0-s3+ra at 0x14-0x27; the locals home
 *    ends at 0x78.  Three locals are observable:
 *        i        spilled to 0x74 across osRecvMesg -> ordinal (0x78-0x74)/4 = 1
 *        received spilled to 0x68                   -> ordinal 4
 *        mesg     address-taken (&mesg to osRecvMesg), homed at 0x64 -> ordinal 5
 *    So the declaration list must open with i, <two more>, received, mesg.  j and
 *    k (the two reloc-loop indices) are the two; any other pair would do equally
 *    as far as the object can tell, but two indices is what the code needs.
 *    Measured frame law for THIS function: framesize = round8(48 + 4*nlocals),
 *    i.e. 16 locals -> 0x70, 17 or 18 -> 0x78.  The saved-register COUNT does not
 *    move it (16 locals gave 0x70 with both 4 and 5 saved registers).
 *
 * 2. THE INDICES ARE UNSIGNED.  The count at +0xE is loaded with `lh' (s16) and
 *    the loop test is `sltu' -- an s32 index would give `slt'.
 *
 * 3. IDO REVERSES COMPARISON OPERANDS, and getting it wrong costs three registers,
 *    not one.  Golden: `lw t6,0x64(sp); lw t8,0x10(s0); lw t7,8(t6); bnel t7,t8'.
 *    Written `mesg->dramAddr == node->unk10' this file emitted the same three
 *    loads into t7/t6/t8 and `bnel t6,t8'; written `node->unk10 == mesg->dramAddr'
 *    all four instructions match golden exactly.  rs is the SECOND source operand.
 *
 * 4. THE LIST HEAD MUST BE A NAMED VARIABLE.  Golden reads D_800406A0.unk4 ONCE
 *    and uses the register through both following stores.  Spelling the head
 *    inline four times makes IDO re-load it after every store (a store through
 *    `node' may alias the global), which cost ~15 rows.  NOTE the counter-example
 *    that made this confusing: func_10009BE4 (also in this TU, also golden) runs
 *    the identical remove-and-prepend idiom with a framesize of 0x18 -- ZERO
 *    declared locals -- and does NOT re-load its head; there the node pointer is
 *    an incoming PARAMETER rather than a local derived from the same global.
 *
 * 5. `headNext'/`spareNext' ARE REAL.  Golden loads head->unk0 BEFORE the two
 *    stores into node (`lw t5,0(v1); sw v1,4(s0); sw t5,0(s0)').  as1 cannot hoist
 *    a load with base v1 above a store with base s0, so the load is a separate
 *    source statement.
 *
 * ============================ WHAT IS STILL WRONG ============================
 *
 * A. `found = 1' -> golden `li a1,1'; this source gets `move a1,s3', sharing the
 *    hoisted constant with the `node->unk16 == 1' comparison.  Golden hoists TWO
 *    ones into the preheader (`li s3,1; li s2,1' -- s3 for the two `== 1' tests
 *    and for `busy = 1', s2 for `node->unk15 = 1') and still spends an immediate
 *    on `found = 1'.  So golden has THREE distinct constant-1 EXPRESSIONS, which
 *    means `found' most likely is not plain s32.  Untried: `u8 found;', `s8',
 *    `u16'.  Cheap, one build each.
 *
 * B. The prepend block's register triple.  golden  lw v1,4(s1) / lw t5,0(v1) /
 *    sw v1,4(s0) / move v0,v1 / sw t5,0(s0) / lw a0,0(v1);  this source uses only
 *    v0 and v1 and never emits the `move'.  The same `or $v0,$v1,$zero' copy is in
 *    func_10009BE4's golden, so it is inherent to whatever the source says, not to
 *    the surrounding function.  Appears TWICE (both phases), ~8 rows.
 *
 * C. Phase-2 loop tail.  Golden puts `node = next' in its own basic block that
 *    three branch-likelies duplicate into their delay slots, and closes with
 *    `bnel s2,zero' + a duplicated `lbu t7,0x16(s0)'.  This source emits a plain
 *    `bnez s2' with `move s0,s2' in the delay -- correct but two instructions
 *    shorter, which is why every branch target downstream reads as a diff.
 *
 * D. Everything else is t-register rotation downstream of A-C.
 *
 * ================ SUPERSEDES THE PRE-EXISTING PARKED VERSION =================
 * This file already existed at HEAD, holding an UNSCORED head start from aborted
 * wave 44 (`git show HEAD:tools/nearmiss/func_1000A03C.c`).  That version reached
 * the same overall reconstruction independently -- good cross-validation -- but
 * it was never built, it typed the lists through `struct54' plus `(s32)' casts on
 * the list heads (which is what produces the re-load storm in point 4 above), and
 * it padded the frame with six BANNED dead locals `probe1..probe6'.  The six
 * probes are exactly the six real locals derived here, so its author had reached
 * the same frame arithmetic; this version pays for them with variables the code
 * actually uses.
 *
 * Two shapes from that version that are still UNTRIED here and cost one build
 * each:  `node->unk0 = link->unk0;' BEFORE `node->unk4 = link;' (as1 may swap the
 * two same-base stores, which would reproduce golden's load-before-store without
 * the headNext local -- but that drops to 15 locals and needs two others), and
 * `if (1 == node->unk16)' with the constant first.
 *
 * ===================== HOUSEKEEPING DONE FOR THIS TU =========================
 * expected/build/src/init_8F90.c.o and expected/build/src/game_AEB40.c.o did NOT
 * exist; both were seeded from a clean pragma build.  Without them `diff.py -o'
 * cannot score at all.
 *
 * The two file-local shadows below were VERIFIED not to disturb the TU: with them
 * in place func_10009FFC, func_10009B2C, func_10009B4C, func_10009B90,
 * func_100093CC and func_10009980 all still score 0 (func_10009FFC needs
 * `--max-lines 18' -- at 60 its window runs into func_1000A03C and reads 45).
 */

/* ---- goes at the TOP of init_8F90.c, ahead of #include "variables.h" ---- */

typedef struct AudioBankNode AudioBankNode;

typedef struct {
    u8 pad0[0xA];
    u8 unkA;
} AudioBankVoice;

typedef struct {
    u8 pad0[0x8];
    AudioBankVoice *unk8;
} AudioBankEntry;

typedef struct {
    u8 pad0[0xE];
    s16 unkE;
    u32 unk10[1];
} AudioBank;

struct AudioBankNode {
    AudioBankNode *unk0;
    AudioBankNode *unk4;
    u32 unk8;
    s32 unkC;
    AudioBank *unk10;
    s8 unk14;
    u8 unk15;
    u8 unk16;
};

typedef struct {
    u8 unk0;
    u8 unk1;
    u8 unk2;
    u8 unk3;
    AudioBankNode *unk4;
    AudioBankNode *unk8;
    AudioBankNode *unkC;
    AudioBankNode *unk10;
    s32 unk14;
} AudioBankLists;

/* variables.h declares D_800416F0 as `OSMesgQueue *', but the object at that
   address IS the queue (func_10008F90 builds it with osCreateMesgQueue(&...)).
   D_800406A0 is struct147 there, whose .unk4/.unk8 are s32 and whose bank
   pointer (struct54.unk10) is s32.  Shadowed rather than corrected in the shared
   header, which 106 TUs include. */
#define D_800416F0 D_800416F0_ptr_decl_in_variables_h
#define D_800406A0 D_800406A0_struct147_decl_in_variables_h
#include "variables.h"
#undef D_800416F0
#undef D_800406A0
extern OSMesgQueue D_800416F0;
extern AudioBankLists D_800406A0;

/* ---- goes where the pragma is ---- */

extern u32 D_8002AE50;
extern s32 D_8003E384;
extern void func_10004074(void *arg0);
extern void func_1000A348(void);

void func_1000A03C(void) {
    s32 i;
    u32 j;
    u32 k;
    s32 received;
    OSIoMesg *mesg;
    AudioBankNode *node;
    AudioBankNode *head;
    AudioBank *bank;
    s32 found;
    AudioBankNode *next;
    AudioBankNode *spare;
    AudioBank *used;
    AudioBankEntry *entry;
    AudioBankVoice *voice;
    AudioBankNode *headNext;
    AudioBankNode *spareNext;
    s32 busy;

    received = 0;
    mesg = NULL;
    for (i = 0; i < D_8002AE50; i++) {
        if (osRecvMesg(&D_800416F0, (OSMesg *)&mesg, OS_MESG_NOBLOCK) != -1) {
            received++;
            found = 0;
            node = D_800406A0.unkC;
            while ((node != NULL) && (found == 0)) {
                if (node->unk10 == (AudioBank *)mesg->dramAddr) {
                    found = 1;
                    if (node == D_800406A0.unkC) {
                        D_800406A0.unkC = node->unk0;
                    }
                    if (node->unk0 != NULL) {
                        node->unk0->unk4 = node->unk4;
                    }
                    if (node->unk4 != NULL) {
                        node->unk4->unk0 = node->unk0;
                    }
                    node->unk0 = NULL;
                    node->unk4 = NULL;
                    head = D_800406A0.unk4;
                    if (head != NULL) {
                        headNext = head->unk0;
                        node->unk4 = head;
                        node->unk0 = headNext;
                        if (head->unk0 != NULL) {
                            head->unk0->unk4 = node;
                        }
                        head->unk0 = node;
                    } else {
                        D_800406A0.unk4 = node;
                        node->unk0 = NULL;
                        node->unk4 = NULL;
                    }
                    if (node->unk16 == 1) {
                        bank = node->unk10;
                        for (j = 0; j < bank->unkE; j++) {
                            bank->unk10[j] = bank->unk10[j] + (u32)node->unk10;
                        }
                    }
                    node->unk15 = 1;
                    node->unk14++;
                } else {
                    node = node->unk0;
                }
            }
        }
    }
    D_8002AE50 = D_8002AE50 - received;
    node = D_800406A0.unk10;
    while (node != NULL) {
        busy = 0;
        next = node->unk0;
        if (node->unk16 == 1) {
            used = node->unk10;
            for (k = 0; k < used->unkE; k++) {
                entry = (AudioBankEntry *)used->unk10[k];
                voice = entry->unk8;
                if (voice->unkA != 0) {
                    voice->unkA = 0;
                    busy = 1;
                }
            }
        }
        if (busy == 0) {
            node->unk14 = 0;
            node->unk15 = 0;
            func_10004074(node->unk10);
            node->unkC = 0;
            if (node == D_800406A0.unk10) {
                D_800406A0.unk10 = next;
            }
            if (node->unk0 != NULL) {
                node->unk0->unk4 = node->unk4;
            }
            if (node->unk4 != NULL) {
                node->unk4->unk0 = node->unk0;
            }
            spare = D_800406A0.unk8;
            if (spare != NULL) {
                spareNext = spare->unk0;
                node->unk4 = spare;
                node->unk0 = spareNext;
                if (spare->unk0 != NULL) {
                    spare->unk0->unk4 = node;
                }
                spare->unk0 = node;
            } else {
                D_800406A0.unk8 = node;
                node->unk0 = NULL;
                node->unk4 = NULL;
            }
        }
        node = next;
    }
    if (D_8003E384 != 0) {
        func_1000A348();
        D_8003E384 = 0;
    }
}
