/* ============================================================================
 * func_150130B4 (game_40490) -- WORKING SOURCE, BEST *CONTENT* POSITION.
 * NOT A MATCH.  Wave 52.
 *
 *   mism 353 of 406,  shape_miss 15,  n = 405/406,  frame 0x190 (-400)
 *   TRUE residue:  golden-only { nop x1 }      ours-only { (none) }
 *
 * Read tools/nearmiss/func_150130B4.c for the OTHER banked position
 * (mism 227 / shape_miss 22 / n = 406/406) -- that one has the better RAW
 * score but its 406th instruction is a SPURIOUS ; golden's extra
 * instruction is a scheduler nop.  This file has no spurious instruction at
 * all: every word it emits is a word golden emits, 7 more rows carry golden's
 * exact shape, and the only content difference left in the whole function is
 * golden's unfillable mtc1->cvt.s.w hazard nop.  Rank the two by BOTH numbers.
 *
 * WHAT CHANGED vs the 227 file -- ONE LINE, the flag word:
 *     -   temp = (fade ? 0x1000000 : 0);
 *     -   temp |= 0x2006;
 *     -   temp |= (attr16 ? 0x10 : 0);
 *     +   temp = (attr16 ? 0x10 : 0) | ((fade ? 0x1000000 : 0) | 0x2006);
 *
 * WHY it works (this is recorded cookbook law -- see ido_cookbook.md
 * "THE OPERAND-CANONICALISATION ASYMMETRY GENERALISES FROM addu TO |"):
 * IDO canonicalises an OR chain that contains a small constant and SINKS the
 * constant to the end so it can use  last -- which is NOT golden's tree.
 * The escape is to leave no small constant at the TOP level of the expression:
 * with the 0x2006 parenthesised INSIDE the fade operand, nothing is sinkable,
 * the ori stays bound to the fade ternary, and IDO emits the attr16 ternary
 * FIRST and the fade ternary SECOND -- golden's emission order exactly:
 *     beqz attr / li v1,16 / move v1,zero / beqz fade / move v0,zero /
 *     lui v0,0x100 / ori Rx,v0,0x2006 / or Ry,Rx,v1
 * The  write-back that the 227 form paid for its second statement
 * is gone.  The  SPLIT IS DEAD -- do not bring it back.
 *
 * THE ONE QUESTION IS STILL OPEN: golden homes the flag word in **t1**
 * (case 19 reads  with no reload) and reserves t0=kind, t1=flag,
 * so its rotation pool is t2..t9.  Ours homes it in **v1** and rotates over
 * t1..t9.  Everything measured this wave says the home is chosen by the
 * REGISTER ALLOCATOR, not by the spelling.  See the exhausted-lever list in
 * the wave report; nothing reached a t-register.
 *
 * MEASURE WITH BOTH, AND READ n= FIRST:
 *     python3 tools/fastscore.py  game_40490 func_150130B4 <candidate TU>
 *     python3 tools/shapescore.py game_40490 func_150130B4 <candidate TU>
 * NOTE THE TRAP: mism is inflated here by ~340 purely because n=405 shifts
 * every row from golden index 67 onward.  mism 353 is NOT "126 worse than
 * 227"; it is "the same function, one instruction short, better shaped".
 *
 * Drop-in for
 *     #pragma GLOBAL_ASM("asm/nonmatchings/game_40490/func_150130B4.s")
 * in src/game_40490.c (typedefs where the pragma was, function after them).
 * ============================================================================ */

typedef struct {
    f32 unk00;
    f32 unk04;
    f32 unk08;
    f32 unk0C;
    f32 unk10;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    s32 unk24;
    s32 unk28;
    s32 unk2C;
    s32 unk30;
    s32 unk34;
    s32 unk38;
    s32 unk3C;
    s32 unk40;
    s32 unk44;
    f32 unk48;
    s16 unk4C;
    s16 unk4E;
    s16 unk50;
    s16 unk52;
    u8  unk54;
    u8  unk55;
    u8  unk56;
    u8  unk57;
    u8  unk58;
    s8  unk59;
    u8  pad5A[2];
} Struct150130B4Desc; // 0x5C

typedef struct {
    u8  unk00;
    u8  unk01;
    s16 unk02;
    s16 unk04;
    u8  pad06[2];
    s32 unk08;
    s32 unk0C;
    u8  unk10;
    u8  unk11;
    u8  unk12;
    u8  unk13;
    f32 unk14;
    f32 unk18;
    f32 unk1C;
    f32 unk20;
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    f32 unk30;
    f32 unk34;
    f32 unk38;
    f32 unk3C;
    s32 unk40;
    u8  unk44;
    u8  unk45;
    u8  unk46;
    u8  unk47;
    s32 unk48;
    u8  pad4C[0xC];
} Struct150130B4Spawn; // 0x58

typedef struct {
    f32 unk00;
    f32 unk04;
    f32 unk08;
    f32 unk0C;
} Struct150130B4TrailPayload; // 0x10

typedef struct {
    f32 unk00;
    f32 unk04;
    struct131 *unk08;
    f32 unk0C;
    f32 unk10;
    f32 unk14;
} Struct150130B4TrackPayload; // 0x18

typedef struct {
    u8 unk0[6];
} Struct150130B4Ids;

extern Struct150130B4Ids D_80082E98;
extern struct131 *func_151149AC(u8);
extern void *func_151407D0(void *, s32, void *, s32, s32, s32, s32, s32, s32, s32);

s32 func_150130B4(struct134 *arg0) {
    static const s32 sKindTable[5] = {3, 21, 104, 105, 126};
    static const s32 sSubKindTable[5] = {0x3400, 0x3400, 0x2200, 0x3400, 0x3400};
    static const s32 sSlotTable[8] = {2, 3, 4, 5, 6, 7, 8, 9};
    Struct150130B4Desc desc;
    Struct150130B4Spawn spawn;
    s32 kind;
    s32 temp;
    u8 fade;
    f32 mtx[4][4];

    arg0->unk16 |= 4;
    kind = arg0->unk1C;
    fade = (u32)arg0->unk20 >> 24;

    spawn.unk1C = (f32)arg0->unk0;
    spawn.unk20 = (f32)(s16)arg0->unk2;
    spawn.unk24 = (f32)arg0->unk4;
    func_150A8050(mtx, *(f32 *)&arg0->unkC, *(f32 *)&arg0->unk10, 0.0f);
    func_150A7960(mtx[0], 0.0f, 0.0f, -500.0f, &spawn.unk28, &spawn.unk2C, &spawn.unk30);
    spawn.unk28 += spawn.unk1C;
    spawn.unk2C += spawn.unk20;
    spawn.unk30 += spawn.unk24;

    desc.unk04 = (f32)(s16)arg0->unk6;
    desc.unk00 = desc.unk04;
    desc.unk0C = (f32)(s16)arg0->unk8;
    desc.unk08 = desc.unk0C;
    desc.unk18 = (f32)(((u32)arg0->unk20 >> 8) & 0xFF) * 0.003921568859f;
    desc.unk1C = (f32)((u32)arg0->unk20 & 0xFF) * 0.003921568859f;

    temp = (u8)((u32)arg0->unk18 >> 24);
    spawn.unk04 = 0x12C;
    spawn.unk08 = 0;
    spawn.unk02 = sSubKindTable[temp] + 3;
    spawn.unk0C = 0;
    spawn.unk00 = sKindTable[temp];
    spawn.unk10 = arg0->unk18;
    spawn.unk11 = (u32)arg0->unk18 >> 8;
    spawn.unk12 = (u32)arg0->unk18 >> 16;
    spawn.unk13 = 0xFF;
    spawn.unk14 = 0.0f;
    spawn.unk18 = 0.0f;
    spawn.unk34 = 1.0f;
    spawn.unk38 = 1.0f;
    spawn.unk3C = 1.0f;
    spawn.unk45 = 0xFF;
    spawn.unk44 = 0xFF;
    spawn.unk46 = 0;
    spawn.unk47 = 6;
    spawn.unk01 = 3;
    desc.unk54 = 0;
    desc.unk55 = 0;
    desc.unk56 = 0;
    desc.unk57 = 0;
    desc.unk48 = 1.0f;
    desc.unk10 = 0.41f;
    desc.unk14 = 0.2f;
    desc.unk20 = 0.000001f;

    if (fade) {
        func_1510F800(0);
        spawn.unk48 = func_1510FD20((s32)spawn.unk1C, (s32)spawn.unk24);
    } else {
        spawn.unk48 = 0;
        fade = 0;
    }
    desc.unk58 = 0;

    temp = ((((u32)arg0->unk20 >> 16) & 0xFF) != 0 ? 0x10 : 0) | ((fade ? 0x1000000 : 0) | 0x2006);
    temp |= 0x40000;
    temp |= 0x80000;
    temp |= 0x10000;
    temp |= 0x400000;
    spawn.unk40 = temp;

    switch (kind) {
    case 8:
        {
            Struct150130B4TrailPayload trail;
            void *obj;

            trail.unk00 = 0.975f;
            trail.unk04 = 0.325f;
            trail.unk08 = 0.0f;
            trail.unk0C = 0.0596f;
            obj = func_151407D0(&desc, 0x70, &spawn, 0, 0x29, 0, 0, -1, 0xFF, 1);
            if (obj != NULL) {
                memcpy((u8 *)obj + 0x170, &trail, 0x10);
            }
        }
        return 1;

    case 1:
    case 2:
    case 3:
    case 4:
        {
            s32 slot = sSlotTable[kind - 1];

            desc.unk58 = slot;
            func_151407D0(&desc, 0x60, &spawn, 0, 0, 0, 0, -1, 0xFF, 1);
        }
        return 1;

    case 9:
    case 10:
    case 11:
    case 12:
        {
            s32 slot = sSlotTable[kind - 5];

            desc.unk58 = slot;
            func_151407D0(&desc, 0x60, &spawn, 0, 0, 0, 0, -1, 0xFF, 1);
        }
        return 1;

    case 5:
    case 6:
    case 7:
        {
            const s32 sounds[3] = {12, 13, 14};

            desc.unk58 = sounds[kind - 5];
            func_151407D0(&desc, 0x60, &spawn, 0, 0, 0, 0, -1, 0xFF, 1);
        }
        return 1;

    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
    case 18:
        {
            void *obj;
            Struct150130B4TrackPayload track;
            Struct150130B4Ids ids;

            ids = D_80082E98;
            track.unk08 = func_151149AC(ids.unk0[kind - 13]);
            if (track.unk08 == NULL) {
                return 1;
            }
            track.unk00 = -80.0f;
            track.unk04 = fabsf(-0.0125f);
            track.unk0C = (f32)track.unk08->unk10;
            track.unk10 = (f32)track.unk08->unk12;
            desc.unk58 = 0;
            track.unk14 = (f32)track.unk08->unk14;
            obj = func_151407D0(&desc, 0x78, &spawn, 0x25, 0, 0, 0, -1, 0xFF, 1);
            if (obj != NULL) {
                memcpy((u8 *)obj + 0x170, &track, 0x18);
            }
        }
        return 1;

    case 19:
        desc.unk58 = 0x11;
        spawn.unk40 = temp & ~2;
        func_151407D0(&desc, 0x60, &spawn, 0, 0, 0, 0, -1, 0xFF, 1);
        return 1;

    default:
        func_151407D0(&desc, 0x60, &spawn, 0, 0, 0, 0, -1, 0xFF, 1);
        break;
    }
    return 1;
}
