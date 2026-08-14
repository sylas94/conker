/* ===========================================================================
 * func_15007B3C  --  game_34F20.c  --  MEASURED 2026-08-14
 * ===========================================================================
 * backlog.tsv IS WRONG FOR THIS ROW.  It says `bytes=96, measured_2026_08_11=1`.
 * The golden function is **1704 bytes** (mips-linux-gnu-readelf -sW on
 * expected/build/src/game_34F20.c.o) and this file, installed with the pragma
 * removed and all five neighbours live, measures:
 *
 *     differ_R = 2927,  differ (no -R) = 3227
 *     FNDIFF func_15007B3C  words=308  relocs=349  size=1696/1704
 *     (106 differing rows; golden is 426 instructions, this file 424)
 *
 * Calibration for those numbers: with the #pragma restored the same harness
 * prints `differ_R=0 differ=0 words=0 relocs=0 size=1704/1704`, so the 2927 is
 * real and not a stale object.  Treat every `measured_2026_08_11` value in
 * backlog.tsv as unverified until re-measured -- this one is off by 3 orders of
 * magnitude in the score and 18x in the size.
 *
 * WHAT IS ACTUALLY WRONG (it is much closer than 2927 suggests -- the score is
 * inflated because a whole-function register rotation scores every row):
 *
 *  1. HARD BLOCKER -- THE JUMP TABLE.  game_34F20 has NO `.rodata` line in
 *     conker.us.yaml (`grep -n game_34F20 conker/conker.us.yaml` gives only
 *     `- [0x34F20, c, game_34F20]`).  Golden reads
 *         lui at,%hi(jtbl_80095A50) / lw t8,%lo(jtbl_80095A50)(at)
 *     and live C emits
 *         lui at,%hi(.rodata)       / lw t8,%lo(.rodata)(at)
 *     i.e. a private live-C table that conker.ld discards.  This function
 *     CANNOT close until game_34F20's rodata block is migrated (see
 *     conker-jtbl-unlocked: one `[0xADDR, .rodata, game_34F20]` yaml line).
 *     The switch SHAPE is already right: golden's `addiu t8,v0,-0x13` /
 *     `sltiu at,t8,0x2d` is exactly cases 19..63 as written below.
 *
 *  2. A GLOBAL v0<->v1 WEB SWAP.  Golden gives the switch scrutinee v0
 *     (`lw v0,%lo(D_800BE9F4)(v0)`, `addiu t8,v0,-0x13`, four `bne v0,at`) and
 *     this file gives it v1; the same swap reappears in the D_80082FA0 loop,
 *     where golden's `i` is v0 / cursor v1 with homes 0x34 / 0x18 and this file
 *     has them the other way round.  One temp web too many or too few.
 *
 *  3. TWO INSTRUCTIONS, AND THE ONLY REAL STRUCTURAL DEFECT.  Golden CSEs the
 *     addresses of D_800D2456 and D_800D2457:
 *         lui v0,%hi(D_800D2456) / addiu v0,v0,%lo(D_800D2456)
 *         sb  t6,0(v0)           / sb    t6,%lo(D_800D2457)(at)
 *     this file emits an independent lui+%lo for each. They are adjacent bytes;
 *     golden is reading them as two fields of ONE object. Find that object
 *     (a 2-byte struct / a u8[2]) and this cluster and the 2-instruction
 *     shortfall both go away.  Do this BEFORE touching registers.
 *
 * TU-PHASE EXPERIMENT RUN ON THIS FUNCTION (negative -- see session report):
 * each of the five live neighbours (func_15007A70 declared BEFORE it;
 * func_150081E4/15008230/15008248/150082CC declared AFTER it) was replaced in
 * turn by a #pragma GLOBAL_ASM stub, with blank-line padding so the -g3 line
 * numbers were held fixed, and three pure line-shift controls (1/3/10 blank
 * lines inserted ahead of this function) were run as well.  All nine builds
 * produced this function BYTE-IDENTICAL (.text+reloc sha1 a8bd8ff6a1632607,
 * size 1696).  Neighbouring code in the same TU does not move this function's
 * codegen, and neither do absolute source line numbers.
 * =========================================================================== */

/* --- local prototypes (missing from functions.h) --- */
void func_1500E738(void);
void func_1500C2A0(void);
s32  func_1507E114(s32 *);
void func_150091D0(void);
void func_15187F90(void);
void func_10003ACC(s32, s32, s32);
void func_1501C53C(void);
void func_15015E80(void);
void func_150162B0(void);
void func_15017930(s32);
void func_1501A220(s32, s32);
void func_15012F90(void);
void func_15008A60(void);
void func_15044370(void);
void func_15016670(void);
void func_15017868(void);
void func_151732E0(s32);
void func_1502AAF0(void);
void func_1502AAF8(s32);
void func_150031EC(s32);
void func_150039E0(s32, s32);
void func_15004574(void);
void func_1511F980(void);
void func_15003668(s32);
void func_15017578(s32);
void func_150045C4(s32);
void func_150000B0(void);
void func_1501BB20(void);
void func_15008870(s32);
void func_15008930(s32);
void func_15016690(s32);
void func_150169A0(s32);
void func_15005290(s32, s32);
void func_150006E0(s32);
void func_1510B070(s32);
void func_1500E70C(s32);
void func_150163D0(s32);
void func_150092DC(void);
void func_15000AD0(s32);
void func_151E81EC(void);
void func_1500E470(s32);
void func_15085B70(s32);
void func_1501B640(s32);
void func_15080200(void);
void func_15015910(void);
void func_1500C1E0(void);
void func_15004D50(void);
s32  func_1509C2A4(void);
void func_1509BBA0(s32);
void func_15013000(void);
void func_1507DFE4(s32, s32);
void func_151E562C(void);
s32  func_151E5FAC(void);
void func_15181E18(void);
void func_15017640(void);
void func_1501CC3C(void);
void func_150A11C4(struct127 *);
void func_151BF340(s32, s32);
void func_1509C3A0(void);
void func_151D8DE8(void);

/* --- local externs (missing from variables.h) --- */
extern u8  D_800E0A00;
extern s32 D_800DC9F0;
extern s32 D_800E0920;
extern s32 D_8003E384;
extern u8  D_800E0BD1;
extern u8  D_800BE619;
extern u8  D_800BE61A;
extern u8  D_800BEA0C;
extern s32 D_800BE3E4;
extern u8  D_800E0B99;

void func_15007B3C(void) {
    s32 i;
    s32 sp30;
    s32 sp2C;
    s32 count;
    s32 level;
    s32 snd;
    struct127 *obj;

    if (D_800BE9B4 == 0) {
        D_800BE9B4 = 1;
    }

    func_10004308();
    func_15002FB4((s32) D_800BE9F4);

    level = (s32) D_800BE9F4;

    switch (level) {
        case 26:
        case 36:
        case 43:
        case 45:
        case 48:
        case 51:
        case 52:
        case 63:
            snd = 0x103;
            if (level == 36) {
                snd = 0xF3;
            }
            if (level == 51) {
                snd -= 8;
            }
            if (level == 63) {
                snd -= 8;
            }
            if (level == 52) {
                snd += 8;
            }
            break;
        case 19:
            snd = 0xEB;
            if ((((u8 *) D_800D2E4C)[0x11] & 4) == 0) {
                snd = ((s8 *) D_800B0DF0)[0x11] + 0xEB;
            }
            break;
        default:
            snd = ((s8 *) D_800B0DF0)[0x11] + 0xEB;
            break;
    }

    func_100014C4(snd);
    D_800E0A00 = 0;
    func_1500E738();
    func_1500C2A0();
    D_800DC9F0 = 0;
    D_800E0920 = 0;
    func_15008840();
    D_8003E384 = 1;
    sp30 = D_800DD2C0;
    sp2C = func_1507E114(&sp30);

    if (D_800E0B94 == 2) {
        sp30 = D_800E0BD1;
    }

    D_800BE9F8 = D_800BE9F0;
    D_800BE9F0 = (s32) D_800BE9F4;
    func_150091D0();
    func_15187F90();
    D_800BE619 = 0;
    D_800BE61A = 0;
    D_800BEA0C = 0;
    func_150081E4();

    if (D_800BE9ED != 0) {
        func_10003ACC(0xFF, 0xFF, 0xFF);
        D_800BE9ED = 0;
    } else {
        func_10003ACC(0, 0, 0);
    }

    if (D_800BE616 == 0) {
        if ((D_800D2E4C->unk18 & 1) == 0) {
            D_800D2456 = 3;
            D_800D2457 = 3;
            func_15085710(0, 5, 3);
        }
    }

    func_15002F40(D_800BE9F0);
    func_1501C53C();
    func_15015E80();
    func_150162B0();
    func_15017930(D_800BE9F0);
    func_15016500();
    func_1501A220(D_800BE9E8, 1);
    func_15012F90();
    func_15008A60();
    func_15000AC0();
    func_15012780();
    func_1500BE68();
    func_15044370();
    func_15016670();
    func_15004F00();
    func_15004E80();
    func_15017868();
    func_151732E0(D_800BE9F0);
    func_1502AAF0();
    func_1502AAF8(D_800BE9F0);
    func_150031EC(D_800BE9F0);
    func_150039E0(D_800BE9F0, 1);
    func_15004574();
    func_1511F980();
    func_15003668(D_800BE9F0);
    func_150038A0();
    func_150039B0(D_800BE9F0);
    func_15017578(D_800BE9F0);
    func_150045C4(D_800BE9F0);
    func_15008248(D_800BE9F0);
    func_150000B0();
    func_1000F248(D_800BE9F0);
    func_100125CC(D_800BE9F0);
    func_10011FEC();
    func_1501BB20();
    func_15008870(1);
    func_15008930(1);
    func_15016690(D_800BE9F0);
    func_150169A0(D_800BE9F0);
    func_15005290(D_800BE9F0, sp30);
    func_15016370();
    func_150006E0(D_800BE9F0);
    func_1510B070(0);

    for (i = 0; i <= D_80082FA0; i++) {
        func_15125690(&D_800DBFF0[i], 1);
    }

    func_1500E70C(D_800BE9F0);
    func_150163D0(D_800BE9F0);
    func_150092DC();
    func_15000AD0(D_800BE9F0);

    if (D_800BE9F0 == 0x1D) {
        func_151E81EC();
    }

    func_1500E470(D_800BE9F0);
    func_15009150(D_800BE9F0);
    func_15085B70(D_800BE9F0);
    func_15008DD0();
    func_1501B640(0);
    func_15080200();
    D_800BE9E4 = 2;
    func_15015910();
    func_15004F10();
    func_1501748C(D_800D2340);
    func_1500C1E0();
    func_15004E00();
    func_15004D50();
    func_150082CC();

    if (D_800BE616 == 0) {
        func_15085710(0, 9, D_800BE3E4);
    }

    if (func_1509C2A4() != 0) {
        D_800BE3E0 = sp30;
    }

    D_800D2E43 = 1;
    func_1509BBA0(4);
    func_1509BBA0(1);
    func_15013000();

    if (sp2C != 0) {
        func_1507DFE4(sp30, sp2C - 1);
    }

    func_151E562C();

    if ((D_800E0B99 != 0) || (D_800DDE38 == 2)) {
        if ((D_800C35EA != 1) && (D_800DDE38 != 1)) {
            count = func_151E5FAC();
            for (i = 0; i < count; i++) {
                func_15181E18();
            }
        }
        D_800E0B99 = 0;
    }

    func_15017640();
    func_1501CC3C();

    for (obj = D_800CC2D0; obj != &D_800CC2D0[25]; obj++) {
        if ((obj->interaction_state != 0) && (obj->unk127 != 0xFF)) {
            func_150A11C4(obj);
        }
    }

    if ((D_800D18A8 != 0) && (D_800BE9F0 != 0x22)) {
        D_800D18A8 = 0;
        func_151BF340(0xFF, 1);
    }

    func_1509C3A0();
    D_800BE9F4 = (u16 *) D_800BE9F0;
    func_151D8DE8();
}
