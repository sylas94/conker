/* ===========================================================================
 * func_100049E0 -- init_49E0.c -- PARKED 2026-08-15 (rodata-migration wave)
 * ===========================================================================
 * MEASURED with the migration applied ([0x2C0A0, .rodata, init_49E0]):
 *     differ -o -R = 2674, 434 rows, 103 register-only, 4 mnemonic rows.
 * The 144 recorded in backlog.tsv for the PREVIOUS version of this file is not
 * reproducible: rebuilt as-was it measures 3064.  Score is the wrong ranking
 * metric here anyway (cookbook "register-colouring wall") -- this version is
 * STRUCTURALLY EXACT where the 3064 one was not.
 *
 * WHAT THIS VERSION FIXED, all verified by rebuild:
 *  1. FRAME 0x70 -> 0x68 (correct).  The lever was writing `msg` as an
 *     UNINITIALISED declaration plus a separate `msg = NULL;` STATEMENT placed
 *     between the D_8003B240 and D_8003A5C8 stores -- that is golden's store
 *     order (`sh`,`sw zero,0x64(sp)`,`sh`).  A declaration initialiser
 *     (`OSMesg msg = NULL;`) costs 8 bytes of compiler temp area.
 *     `switch ((s32)msg)` not `(u32)msg`; `u32 msg` is also 8 bytes worse.
 *  2. `sll t6,v0,0x0 ; bltz` after osAiGetStatus is
 *         (osAiGetStatus() & AI_STATUS_FIFO_FULL) == 0
 *     and nothing else.  Probed 8 spellings with the project's exact flags:
 *     `(s32)`, `(int)`, `< 0x80000000U`, `>= 0`, `0 <=`, `!(x < 0)`, and two
 *     assignment-in-condition forms ALL fold to a bare `bltz v0` with no move.
 *     Only the explicit sign-bit mask emits the temp move.  (AI_STATUS_FIFO_FULL
 *     is 0x80000000, so this is also the semantically right reading: use the
 *     short 20000 timeout unless the audio FIFO is full.)
 *  3. Three variables.h type errors, all proven by store width -- see the
 *     header comment below.  With them fixed the `sh`/`sh` stores are correct;
 *     the previous version emitted `sw`/`sb` there.
 *  4. `arg0 = arg0;` (present in the previous version, and a construct
 *     verify_match.sh bans) is NOT load-bearing: removing it leaves the object
 *     byte-identical, `sw a0,0x68(sp)` included.  Deleted.
 *
 * THE RESIDUAL, and why it is a BAIL and not a to-do:
 * IDO fills nine callee-saved registers.  Golden spends them on
 *     s0=client  s1=&D_8003B240  s2=&D_8002AC54  s3=&D_8003A581
 *     s4=&D_8003A582  s5=1  s6=&D_8003A583  s7=1  s8=&D_8002AC50
 * -- i.e. the constant 1 gets TWO registers and &D_8002AC6C gets none.  This
 * file gets the same nine minus one of the constants, plus &D_8002AC6C.  All
 * four mnemonic rows (`move a2,s7` vs `li a2,1` x2, and the two D_8002AC6C
 * lui/%lo clusters) descend from that single ranking decision.
 *
 * This was not guessed -- it was reproduced in a standalone probe with the
 * project's exact flags (scratchpad probe_k.c): a reduced loop+jump-table
 * switch over the same globals emits TWO `li sN,1` exactly like golden, and
 * adding the client-walk inner loop (which takes s0) drops it to ONE, exactly
 * like this file.  So the double-hoist is normal IDO output and the tie-break
 * is a depth-weighted reference count decided inside the compiler.  Use counts
 * were checked identical on both sides.  Four independent source spellings
 * (`1 == D_8003A584` vs `D_8003A584 == 1`, `u32 msg` vs `OSMesg msg`,
 * `(s32)` vs `(int)` vs the mask, and a diagnostic that deleted one
 * D_8002AC6C access) left the score EXACTLY unchanged at 2674/2753 -- the
 * cookbook's named BAIL signature for the loop-invariant ranking tie.
 *
 * TO RESUME: install this file at conker/src/init_49E0.c, apply
 *     - [0x2C0A0, .rodata, init_49E0]
 * in conker.us.yaml, `make -C conker extract VERSION=us`, then attack ONLY the
 * &D_8002AC6C hoist.  Everything else in the function is byte-exact.
 * =========================================================================== */

#include <ultra64.h>

#include "functions.h"

/* Four of this file's globals are declared with the wrong type in variables.h, and
 * func_100049E0 is the function that proves it.  They are shadowed file-locally rather
 * than corrected in the shared header, because that header is a dependency of every
 * GLOBAL_ASM object in the tree and one of the four (D_8003B234) is deliberately used
 * with the WRONG type by init_50A0.c, which already matches.
 *
 *   D_8003B234  variables.h: OSPfs *      -- actually the head of the scheduler's client
 *               list.  func_100049E0 walks it as {next, msgQ, flags} and tests bit 0 of
 *               the 0x8 field (`lw t8,8(s0); andi t9,t8,1`).  OSPfs happens to have
 *               scalars at 0x0/0x4/0x8 too, which is why the wrong type survived.
 *               PR/sched.h's stock OSScClient is only {next, msgQ}: Conker's has a
 *               third word.
 *   D_8003B240  variables.h: OSMesg       -- actually an OSScMsg.  Both are written with
 *   D_8003A5C8  variables.h: u8           -- a HALFWORD store (`sh`) of 1 and 4, i.e. the
 *               `short type` field of PR/sched.h's OSScMsg, and 1 and 4 are exactly
 *               OS_SC_RETRACE_MSG and OS_SC_PRE_NMI_MSG.  Only their ADDRESS is ever
 *               handed to osSendMesg, which is how an OSMesg/u8 spelling survived.
 *   D_8003A588  variables.h: u8           -- actually the OSTimer that osSetTimer arms.
 */
#define D_8003B234 D_8003B234_ospfs_decl_in_variables_h
#define D_8003B240 D_8003B240_osmesg_decl_in_variables_h
#define D_8003A5C8 D_8003A5C8_u8_decl_in_variables_h
#define D_8003A588 D_8003A588_u8_decl_in_variables_h
#include "variables.h"
#undef D_8003B234
#undef D_8003B240
#undef D_8003A5C8
#undef D_8003A588

typedef struct ScClient {
    /* 0x00 */ struct ScClient *next;
    /* 0x04 */ OSMesgQueue     *msgQ;
    /* 0x08 */ u32              flags;
} ScClient;

extern ScClient *D_8003B234;
extern OSScMsg   D_8003B240;
extern OSScMsg   D_8003A5C8;
extern OSTimer   D_8003A588;

void func_10004F00(void);
void func_10004FE0(void);
void func_10004DB0(void);

/* The scheduler thread.  Blocks on the interrupt queue and dispatches one of seven
   message codes: 0 = vertical retrace (notify every client, age the frame counters and
   arm the watchdog timer), 1 = RDP done, 2 = RSP task done, 3 = watchdog timeout,
   6 = read the controllers.  Codes 4 and 5 are accepted by the bounds check but have no
   body, so they reach the top of the loop exactly as an out-of-range code does.  The
   loop never exits; the epilogue the compiler emits after it is unreachable. */
void func_100049E0(s32 arg0) {
    OSMesg    msg;
    OSTime    timeout;
    ScClient *client;

    /*ARGPROBE*/

    D_8003A581 = 0;
    D_8003A582 = 0;
    D_8003A584 = 1;
    D_8003A583 = 0;
    D_8003B240.type = OS_SC_RETRACE_MSG;
    msg = NULL;
    D_8003A5C8.type = OS_SC_PRE_NMI_MSG;

    while (1) {
        osRecvMesg(&D_8003B218, &msg, OS_MESG_BLOCK);

        switch ((s32)msg) {
            case 0:
                client = D_8003B234;
                while (client != NULL) {
                    if ((client->flags & 1) == 0) {
                        osSendMesg(client->msgQ, &D_8003B240, OS_MESG_NOBLOCK);
                    }
                    client = client->next;
                }
                if ((D_8003B238 != 0xFF) && (D_8003B238 < 0xFF)) {
                    D_8003B238 = D_8003B238 + 1;
                }
                if (D_8003B23A != 0) {
                    D_8003B23A = D_8003B23A - 1;
                }
                if ((D_8003A581 == 0) && (D_8002AC6C == 0) &&
                    (osRecvMesg(&D_8003B200, &D_8002AC54, OS_MESG_NOBLOCK) == 0)) {
                    timeout = 200000;
                    if ((D_8003A582 != 0) || ((osAiGetStatus() & AI_STATUS_FIFO_FULL) == 0)) {
                        timeout = 20000;
                    }
                    osSetTimer(&D_8003A588, timeout, 0, &D_8003B218, (OSMesg)3);
                    D_8002AC6C = 1;
                }
                if (D_8003A581 == 0) {
                    func_10004DB0();
                }
                break;
            case 2:
                if (D_8003A582 == 3) {
                    if (osSpTaskYielded(&D_8002AC50->list) == 1) {
                        osSpTaskLoad(&D_8002AC54->list);
                        osSpTaskStartGo(&D_8002AC54->list);
                        D_8003A581 = 1;
                        D_8003A582 = 4;
                    } else {
                        D_8003A582 = 1;
                        osSpTaskLoad(&D_8002AC54->list);
                        osSpTaskStartGo(&D_8002AC54->list);
                        D_8003A581 = 1;
                        D_8003A583 = 0;
                    }
                } else if (D_8003A581 != 0) {
                    osSendMesg(D_8002AC54->msgQ, D_8002AC54->msg, OS_MESG_BLOCK);
                    D_8003A581 = 0;
                    if (D_8003A582 == 4) {
                        osSpTaskLoad(&D_8002AC50->list);
                        osSpTaskStartGo(&D_8002AC50->list);
                        D_8003A580 = 1;
                        D_8003A582 = 1;
                    }
                } else {
                    D_8003A583 = 0;
                    if (D_8003A584 == 1) {
                        func_10004FE0();
                    }
                }
                break;
            case 1:
                D_8003A584 = 1;
                if (D_8003A583 == 0) {
                    func_10004FE0();
                }
                break;
            case 3:
                D_8002AC6C = 0;
                if (D_8003A583 != 0) {
                    osSpTaskYield();
                    D_8003A582 = 3;
                } else {
                    osSpTaskLoad(&D_8002AC54->list);
                    osSpTaskStartGo(&D_8002AC54->list);
                    D_8003A581 = 1;
                }
                break;
            case 6:
                if (D_8002AC5C == 0) {
                    osContStartReadData(&D_800BE900);
                }
                break;
        }
    }
}

void func_10004DB0(void) {
    if (D_8003A582 == 0) {
        if (osRecvMesg(&D_8003B1E8, &D_8002AC50, 0) == 0) {
            if ((osViGetCurrentFramebuffer() != D_8002AC50->framebuffer) &&
                (osViGetNextFramebuffer() != D_8002AC50->framebuffer) &&
                ((D_8003B23A == 0) || (D_8003B238 >= D_8003B239))) {
                if ((D_8003B238 != 0xFF) &&
                    ((D_8003B238 >= D_8003B239) || (D_8003B23A == 0))) {
                    D_8003B239 = D_8003B238;
                }
                func_10004F00();
                return;
            }
            D_8003A582 = 2;
        }
    } else if (D_8003A582 == 2) {
        if ((D_8003B23A == 0) || (D_8003B238 >= D_8003B239)) {
            func_10004F00();
        }
    } else if (D_8003A582 == 6) {
        func_10004FE0();
    }
}
// NON-MATCHING: branching is not right
// void func_10004DB0(void) {
//     if (D_8003A582 == 0) {
//         if (osRecvMesg(&D_8003B1E8, &D_8002AC50, 0) == 0) {
//             if ((osViGetCurrentFramebuffer() == D_8002AC50->framebuffer) ||
//                 (osViGetNextFramebuffer() == D_8002AC50->framebuffer) ||
//                 ((D_8003B23A != 0) && (D_8003B238 < D_8003B239))) {
//                 D_8003A582 = 2;
//             } else {
//                 if (D_8003B238 != 255) {
//                     if ((D_8003B238 >= D_8003B239) || (D_8003B23A == 0)) {
//                         D_8003B239 = D_8003B238;
//                     }
//                 }
//                 func_10004F00();
//             }
//         }
//     } else if (D_8003A582 == 2) {
//         if ((D_8003B23A == 0) || ( D_8003B238 >= D_8003B239)) {
//             func_10004F00();
//         }
//     } else if (D_8003A582 == 6) {
//         func_10004FE0();
//     }
// }

void func_10004F00(void) {
    if (D_8002AC5C == 0) {
        osSpTaskLoad(&D_8002AC50->list);
        osSpTaskStartGo(&D_8002AC50->list);
        D_8003A580 = 0;
        D_8002AC58 = D_8002AC50;
        D_8003A583 = 1;
        D_8003A584 = 0;
        if ((D_8003B238 == 255) ||
            ((D_8003B238 >= 11) && ((D_8003B238 >= 21) || (D_800C35EA != 1)))) {
            D_8003B238 = 2;
        }
        D_800BE9E4 = D_8003B238;
        D_8003B238 = 0 ;
        D_8003A582 = 1;
        osSendMesg(D_8003B230, &D_8003B240, 0);
    }
}

void func_10004FE0(void) {
    if (D_8003B238 <= 0) {
        D_8003A582 = 6;
    } else {
        func_10005020();
    }
}

void func_10005020(void) {
    void *fb;

    D_8003A582 = 0;
    fb = D_8002AC50->framebuffer;
    if ((D_8002AC50->flags & OS_SC_SWAPBUFFER) && (D_8002AC5C == 0)) {
        func_1515FDA0(fb);
        osViSwapBuffer(fb);
    }
    osSendMesg(D_8002AC50->msgQ, D_8002AC50->msg, 1);
}
