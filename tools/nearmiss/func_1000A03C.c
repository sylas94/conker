/*
 * func_1000A03C  --  init_8F90.c  (222 asm lines, 3 callees, 0 fp)
 * PARKED FROM AN ABORTED WAVE (wave 44 died on a session limit mid-run).
 * The agent had removed the pragma and left this live; it was NEVER SCORED,
 * so treat it as an UNVERIFIED head start, not a near-miss. Re-derive the
 * baseline score before trusting any of it.
 * Screened clean: still stubbed, not hand-written, no jtbl, no splat floor,
 * no pooled float, ZERO float ops.
 * CHECK OPT_FLAGS: init_8F90 is not a game_ TU; conker/Makefile line 81 sets the
 * global -O2 -g3 and lines 118-135 list per-TU overrides.
 */

void func_1000A03C(void) {
    u32 i;
    struct54 *node;
    s32 found;
    u32 count;
    OSIoMesg *msg;
    struct54 *link;
    struct54 *next;
    AudioBankFile *bank;
    u32 j;
    s32 busy;
    s32 probe1; s32 probe2; s32 probe3; s32 probe4; s32 probe5; s32 probe6;

    count = 0;
    msg = NULL;
    for (i = 0; i < D_8002AE50; i++) {
        if (osRecvMesg((OSMesgQueue *)&D_800416F0, (OSMesg *)&msg, 0) != -1) {
            count++;
            found = 0;
            node = D_800406A0.unkC;
            while ((node != NULL) && (found == 0)) {
                if (msg->dramAddr == (void *)node->unk10) {
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
                    if (D_800406A0.unk4 != 0) {
                        link = (struct54 *)D_800406A0.unk4;
                        node->unk0 = link->unk0;
                        node->unk4 = link;
                        if (link->unk0 != NULL) {
                            link->unk0->unk4 = node;
                        }
                        link->unk0 = node;
                    } else {
                        D_800406A0.unk4 = (s32)node;
                        node->unk0 = NULL;
                        node->unk4 = NULL;
                    }
                    if (1 == node->unk16) {
                        bank = (AudioBankFile *)node->unk10;
                        for (j = 0; j < bank->unkE; j++) {
                            bank->unk10[j] += node->unk10;
                        }
                    }
                    node->unk15 = 1;
                    node->unk14 += 1;
                } else {
                    node = node->unk0;
                }
            }
        }
    }
    D_8002AE50 -= count;
    node = D_800406A0.unk10;
    while (node != NULL) {
        busy = 0;
        next = node->unk0;
        if (1 == node->unk16) {
            bank = (AudioBankFile *)node->unk10;
            for (j = 0; j < bank->unkE; j++) {
                if (((AudioBankSound *)bank->unk10[j])->unk8->unkA != 0) {
                    ((AudioBankSound *)bank->unk10[j])->unk8->unkA = 0;
                    busy = 1;
                }
            }
        }
        if (busy == 0) {
            node->unk14 = 0;
            node->unk15 = 0;
            func_10004074((void *)node->unk10);
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
            if (D_800406A0.unk8 != 0) {
                link = (struct54 *)D_800406A0.unk8;
                node->unk0 = link->unk0;
                node->unk4 = link;
                if (link->unk0 != NULL) {
                    link->unk0->unk4 = node;
                }
                link->unk0 = node;
            } else {
                D_800406A0.unk8 = (s32)node;
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
