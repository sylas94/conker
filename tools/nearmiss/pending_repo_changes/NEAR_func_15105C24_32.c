typedef struct Node15105C24 {
    u8 pad0[8];
    struct Node15105C24 *next;
    u8 padC[7];
    u8 unk13;
    u8 pad14[0x14];
    s32 unk28;
} Node15105C24;

extern Node15105C24 *D_800DCE50[][104];

Node15105C24 *func_15105C24(s32 arg0) {
    u8 i;
    u8 j;
    Node15105C24 *node;

    for (i = 0; i < 2; i++) {
        for (j = 0; j < 2; j++) {
            for (node = D_800DCE50[j][(&D_800A5770)[i]]; node != NULL; node = node->next) {
                if (node->unk13 == 0x2E && node->unk28 == arg0) {
                    return node;
                }
            }
        }
    }
    return NULL;
}
