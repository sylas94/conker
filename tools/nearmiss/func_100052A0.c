/* init_50A0 / func_100052A0  (720 B)  -- MATCHES (mism=0), BLOCKED ON .bss PLACEMENT
 *
 * *** THE HEADER BELOW IS SUPERSEDED AND ITS DIAGNOSIS IS WRONG. MEASURED 2026-08-23: ***
 *      mism=0   frame=-80   n=180/180
 * both as a standalone file and spliced over the pragma. The "five missing nops" story below
 * describes a state this file is no longer in -- the C in it reproduces all 180 words,
 * trailing inter-function pad included. Do not spend another pass on the nops.
 *
 * *** THE REAL BLOCKER IS THE LINKER, NOT THE CODEGEN. ***
 * Installing it into conker/src/init_50A0.c compiles clean and then FAILS TO LINK, 19 times:
 *      `.bss' referenced in section `.text' of build/src/init_50A0.c.o:
 *             defined in discarded section `.bss' of build/src/init_50A0.c.o
 * Finding #1 below -- that D_8003BC20 must be a FUNCTION-SCOPE static u64 -- is what makes it
 * match, and it is also what breaks the link. A function-scope static is a real .bss
 * allocation with a LOCAL symbol, and conker.ld sends every unlisted section to /DISCARD/.
 * The file-scope tentative definition `u64 D_8003B260;` in the same TU links fine only
 * because a tentative definition becomes a COMMON symbol, which the linker allocates
 * separately and never puts in the object's .bss.
 *
 * So this is the .bss analogue of the jtbl/rodata blocker, and it is NOT a one-line fix:
 * conker.ld has NO bss output section at all, and conker.us.yaml carries three competing
 * commented-out guesses about where bss even starts (around line 233):
 *      # - {start: 0x2D4B0, type: bss,  vram: 0x8002D4B0}
 *      # - {start: 0x2D4B0, type: .bss, vram: 0x8003B260, name: init_50A0}
 *      # - {start: 0x2D4B0, type: bss,  vram: 0x8003B270}
 * Getting the vram wrong does not fail loudly -- it relocates %hi/%lo in .text and changes
 * ROM bytes. Whoever takes this on must gate on the ROM sha1, not on the link succeeding.
 *
 * DO NOT "fix" this by making the static an extern or a file-scope tentative definition:
 * finding #1 measured both at 262, because IDO then promotes the address into $s7.
 *
 * SUPERSEDED HEADER FOLLOWS ------------------------------------------------------------
 * init_50A0 / func_100052A0  (720 B)  -- NEAR MISS, BLOCKED ON A TOOLCHAIN ARTIFACT
 *
 *   raw fastscore : mism=80   frame=-80  n=173/180
 *   n= gap        : golden 180 words, ours 173 -> 7 words short
 *                   2 of those 7 are inter-function pad (golden's last two
 *                   words are 00000000, aligning osMotorStop to 0x10005570)
 *   pad-corrected : 60  = 5 real missing words (x10) + 10 mismatch rows
 *
 * THE ONLY DEFECT: golden has FIVE 0x00000000 nops at 0x1000552C..0x1000553C,
 * between the self-branch at .L10005524 and the (unreachable) epilogue.  Our
 * object goes straight from the self-loop into the epilogue, so the epilogue's
 * 10 instructions land 5 words early -> the 10 rows.  Every single reachable
 * instruction, in every block, is byte-identical: fastscore's row list contains
 * NOTHING but the shifted epilogue.
 *
 * The nops are an epilogue-alignment artifact, not C:
 *   - golden epilogue sits at func+0x2A0 -- 32-byte aligned.
 *   - the same artifact exists in the sibling init_49E0/func_100049E0.s:
 *     unconditional branch + 4 nops + epilogue at func+0x3A0 -- also 32-byte
 *     aligned.  That function is likewise unclosed.
 *   - IDO 5.3 as shipped in ido/ido5.3_recomp emits no such padding, and it is
 *     the only compiler in the tree.
 *
 * DO NOT REPEAT (all measured, all flat at mism=80):
 *   - tail spelling: while(1){}, for(;;){}, while(1){;}, do{}while(1);,
 *     a goto self-loop, a trailing return;, five trailing empty statements.
 *   - dead code after the loop (a trailing osWritebackDCacheAll(); call, a dead
 *     store to D_8002AAE0, an i++ inside the loop): IDO deletes unreachable code
 *     outright and never leaves nops behind, so NO source construct placed after
 *     the infinite loop can produce them.
 *   - flag sweep: -O2/-g2, -g1, -g0, no -g, -O1/-g3, -g, -mips3 all score WORSE
 *     (215 / 215 / 93 / 93 / 227 / 215 / 358).  -O3 -g3 ties at 80.  -O2 -g3 is
 *     correct and the Makefile has no OPT_FLAGS override for init_50A0.
 *
 * TWO REAL FINDINGS THAT GOT IT HERE (keep both):
 *  1. D_8003BC20 must be a FUNCTION-SCOPE static u64.  Taken as the extern u64
 *     from variables.h -- or as a file-scope tentative definition -- IDO
 *     promotes its address into $s7, an 8th saved register golden does not
 *     have, which shifts the whole prologue and costs 262.  Function-scope
 *     static: 262 -> 80, and golden's two-lui-per-64-bit-load shape falls out
 *     for free.
 *  2. osMotorStop must be #undef'd: os_motor.h defines it as the
 *     __osMotorAccess(x, MOTOR_STOP) macro, but this build exports it as a real
 *     one-argument function.  Same workaround as game_48FD0.c / game_33660.c.
 *
 * Pass this file straight to fastscore; it needs no hand edits:
 *   python3 tools/fastscore.py init_50A0 func_100052A0 tools/nearmiss/func_100052A0.c
 */
#include <PR/sched.h>

#include "functions.h"
#include "variables.h"

#undef osMotorStop
extern s32 osMotorStop(OSPfs *pfs);
extern s32 _MakeMotorData(OSMesgQueue *mq, OSPfs *pfs, s32 channel);

u64 D_8003B260; // bss

void func_100052A0(s32 arg0) {
    static u64 D_8003BC20;
    OSMesg mesg;
    s32 i;

    mesg = NULL;
    if (D_8002BD18 == 0) {
        osRecvMesg(&D_8003B9D0, &mesg, 1);
    }
    D_8002AC5C = 1;
    osStopThread((OSThread *)&D_80035910);
    osStopThread(&D_80031AE0);
    func_100093CC();
    D_8003BC20 = osGetTime();
    __osViInit();
    D_8002AAE0 = 1;
    osSetThreadPri(NULL, 11);

    if (D_8002AAE4 != 0) {
        if (D_80084064 == 0) {
            osRecvMesg(&D_800BE900, &D_800BE990, 1);
        }
        for (i = 0; i < 4; i++) {
            if (D_800BE944[i] != 0) {
                _MakeMotorData(&D_800BE900, (OSPfs *)&D_800BE760[i], i);
                osMotorStop((OSPfs *)&D_800BE760[i]);
                D_800BE948[i] = 0;
            }
        }
    }

    while (osGetTime() < D_8003BC20 + 2272727) {
    }

    while (osGetTime() < D_8003BC20 + 7500000) {
    }

    osWritebackDCacheAll();

    while (1) {
    }
}
