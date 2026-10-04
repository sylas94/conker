void func_1503D438(s32 *arg0, s32 arg1);

typedef struct {
    s8 op;
    u8 b1;
    u8 b2;
    u8 b3;
    s32 w1;
} Cmd1503D368;


void func_1503D368(Cmd1503D368 *dl, s32 arg1) {
    s32 i;
    Cmd1503D368 *cmd;
    s32 op;

    if (dl != NULL) {
        i = 0;
        cmd = dl;
        if (-0x21 != dl->op) {
            op = cmd->op;
            do {
            switch (op) {
            case 1:
                func_1503D438(&cmd->w1, arg1);
                break;
            case -0x24:
                if (cmd->b3 == 14) {
                    func_1503D438(&cmd->w1, arg1);
                }
                break;
            }
                i++;
                cmd = &dl[i];
                op = cmd->op;
            } while (-0x21 != op);
        }
    }
}
