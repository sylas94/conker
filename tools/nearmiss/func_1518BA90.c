/* tools/nearmiss/func_1518BA90.c -- game_1B8F40, jtbl block 24BED0
 *
 * STATUS: scores 0 at n=89/89 with frame EXACT (-0x48).  NOT YET SHIPPABLE, and not
 * because of this function -- see BLOCKED below.
 *
 * FILE KIND: BODY SPLICE.  Substitute this body for the pragma in conker/src/game_1B8F40.c:
 *   #pragma GLOBAL_ASM("asm/nonmatchings/game_1B8F40/func_1518BA90.s")
 * then:  python3 tools/fastscore.py game_1B8F40 func_1518BA90 <spliced.c>
 *
 * *** BLOCKED ON func_1518BD60, NOT ON ITSELF ***
 * This function owns rodata block 24BED0 jointly with func_1518BD60 (which uses
 * D_800A7440 = 0.654f).  A jtbl migration only links if the TU re-emits the WHOLE block in
 * order, so the yaml line
 *      - [0x24BED0, rodata]   ->   - [0x24BED0, .rodata, game_1B8F40]
 * CANNOT be flipped until func_1518BD60 (856 B, 214 words) is also live C.  Flipping it
 * early breaks the link outright with "undefined reference to jtbl_800A7410".
 * Ship both functions and the yaml line as ONE change.
 *
 * THREE THINGS THAT WERE MEASURED, IN THE ORDER THEY MATTERED (94 -> 0)
 *
 * 1. THE STACK PACKET IS 0x20 BYTES, NOT THE 0x1C THAT ITS STORES SPAN.  This alone is
 *    worth 8 bytes of frame.  IDO seats the object at frame_end - sizeof, so 0x48-0x20 =
 *    0x28 = golden's base; a 0x1C struct seats at 0x24 and the frame closes at 0x40.
 *    Stores cover 0x00..0x1A only; 0x1B..0x1F are tail this function never writes.
 *    *** THIS IS AN INFERENCE FROM THE FRAME, NOT A DECODED FIELD. ***  func_1518BA90 is
 *    the ONLY caller of func_1518BCD0 and func_1518BD60 does not build this packet, so
 *    there is no second user to corroborate the tail against.  What IS certain: the object
 *    occupies 0x20 stack bytes in the retail binary.  What is invented: the names unk1B /
 *    unk1C.  Flagged to the owner rather than shipped silently.
 *
 * 2. arg1 IS A u8 PARAMETER COPIED INTO A u32 LOCAL.  Golden materialises it at the TOP
 *    (`andi $t6,$a1,0xFF ; or $a1,$t6,$zero`) and keeps it in a register for the whole
 *    function.  Every other spelling homes it and reloads `lbu $a1,0x4F($sp)` before the
 *    call, which is 1 instruction short and 85 rows wrong.  The LOCAL'S TYPE IS LOAD-BEARING
 *    and only u32 works -- this is the full measured matrix (all at the correct frame):
 *        u8 param + u32 local ....  2   <- then the flip below takes it to 0
 *        u8 param + no local .....  95  (n=88/89, reloads via lbu)
 *        u8 param + u8  local ....  95
 *        u8 param + s32 local ....  95
 *        s32/u32 param + u8 local . 95
 *        s32/u32 param + s32 local  113 (n=86/89)
 *
 * 3. THE COMPARISON OPERAND ORDER IS THE LAST 2 ROWS.  Golden loads arg0->unk3B FIRST:
 *        gold:  lbu $t8,0x3B($a3) ; lbu $t9,0x28($v1)
 *    so the source spells the NODE side on the LEFT: `node->unk28 == arg0->unk3B`.
 *    Writing it the intuitive way round emits the two lbu's swapped.  Note this axis was
 *    WORTH NOTHING at the wrong frame -- both orders scored 94 -- so it is only findable
 *    after the structural fixes.  Sweep structure first, operand order last.
 *
 * THE JUMP TABLE.  jtbl_800A7410 has 9 entries and IDO emits case bodies in SOURCE order,
 * so the table is a direct readout of how the cases were written.  Text order is
 * BB34, BB3C, BB90, BBC8, which maps to: case 0 / case 8 / cases 1-5 / cases 6,7+default.
 * The switch value is `arg0->unk4 + 1` (lbu, then addiu 1, then sltiu 9).
 *
 * DO NOT RE-DERIVE: the loop is the repo's standard D_800DCE50 walk (stride 0x1A0, 2
 * entries, terminated against &D_800DD190).  The matched func_15155FD4 in game_182C30.c
 * uses the identical shape with list offset 0x140; this one's list is at 0x7C.
 *
 * ACCEPTANCE.  fastscore masks relocated fields, so a migrated jtbl function can NEVER be
 * scored to 0 by asm-differ either -- the ROM sha1 is the only valid acceptance test for
 * this class.  Do not accept on the strength of the 0 above.
 */

extern u8 D_800DCE50[];
extern s8 D_800DD190;

s32 func_1518BCD0(s32 arg0, s32 arg1, s32 arg2);

typedef struct Node1518BA90 {
    u8 pad0[0x4];
    u8 unk4;
    u8 pad5[0x3];
    struct Node1518BA90 *unk8;
    u8 padC[0x18];
    struct Node1518BA90 *unk24;
    u8 unk28;
    u8 pad29[0x12];
    u8 unk3B;
} Node1518BA90;

typedef struct {
    f32 unk0;
    f32 unk4;
    f32 unk8;
    f32 unkC;
    s16 unk10;
    s16 unk12;
    Node1518BA90 *unk14;
    u8 unk18;
    u8 unk19;
    u8 unk1A;
    u8 unk1B;
    s32 unk1C;
} Packet1518BA90;

s32 func_1518BA90(Node1518BA90 *arg0, u8 arg1, s32 arg2) {
    Packet1518BA90 sp28;
    Node1518BA90 *node;
    s32 i;
    u32 loc;

    if (arg0 == NULL) {
        return 0;
    }
    loc = arg1;

    i = 0;
    do {
        node = *(Node1518BA90 **)&D_800DCE50[i + 0x7C];
        i += 0x1A0;
        while (node != NULL) {
            if ((arg0 == node->unk24) || (node->unk28 == arg0->unk3B)) {
                return (s32)node;
            }
            node = node->unk8;
        }
    } while ((u8 *)&D_800DD190 != &D_800DCE50[i]);

    switch (arg0->unk4 + 1) {
    case 0:
        return 0;
    case 8:
        sp28.unk12 = 0x37;
        sp28.unk10 = 4;
        sp28.unk19 = 5;
        sp28.unk1A = 0x13;
        sp28.unk0 = 2.76f;
        sp28.unk4 = 5.96f;
        sp28.unk8 = 3.21f;
        sp28.unkC = 5.0f;
        break;
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
        sp28.unk12 = 0;
        sp28.unk10 = 5;
        sp28.unk19 = 5;
        sp28.unk1A = 0x13;
        sp28.unk0 = 10.0f;
        sp28.unk4 = 10.0f;
        sp28.unk8 = 10.0f;
        sp28.unkC = 10.0f;
        break;
    default:
        return 0;
    }

    sp28.unk14 = arg0;
    sp28.unk18 = arg0->unk3B;
    return func_1518BCD0((s32)&sp28, loc, arg2);
}
