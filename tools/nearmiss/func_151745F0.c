/* tools/nearmiss/func_151745F0.c -- game_1A11B0, 40 instructions, leaf
 *
 * STATUS: mism=38, n=40/40 (EXACT LENGTH, leaf).  Was 760/n=112 before LAW E.
 *
 * Table-slot allocator: scans 3 records of 0x3C at D_800DD348 for one with unkC == 0, fills
 * it, and copies a 0x24-byte block in with a STRUCT ASSIGNMENT (IDO expands that as a
 * 3-iteration loop using $at as the scratch -- the `lw $at` is the tell for an inline struct
 * copy, not for register pressure).
 *
 * LAW E is decisive here: `while (p != D_800DD3FC)` (a distinct end symbol) makes IDO compute
 * (end-start)/60 with subu+divu and unroll by 2 -- 112 words and a stack frame.  Any of
 * `&D_800DD348[3]`, `D_800DD348 + 3`, or a complete `D_800DD348[3]` declaration gives the
 * plain 40-word leaf.  Hoisting the bound into an `end` LOCAL re-triggers the unroll (720),
 * so the bound must stay an inline expression in the condition.
 *
 * ------------------------------------------------------------------ WHAT IS LEFT
 * Ours materialises the base ONCE and derives both pointers from it
 *      lui v1 / addiu v1 ; or v0,v1,zero ; addiu t4,v1,180
 * golden materialises TWO independent lui/addiu pairs (start in $v1, end in $v0).  Same
 * instruction count, different registers, and everything downstream shifts.  That is LAW B
 * (a symbol materialised twice is not named twice in the source) pulling AGAINST LAW E
 * (the bound must derive from the start symbol) -- the two laws want opposite spellings here,
 * and that tension is the open question.
 */

typedef struct Blk151745F0 {
    s32 unk0[9];
} Blk151745F0;

typedef struct Rec151745F0 {
    /* 0x00 */ f32 unk0;
    /* 0x04 */ f32 unk4;
    /* 0x08 */ f32 unk8;
    /* 0x0C */ u8 unkC;
    /* 0x0D */ char padD[3];
    /* 0x10 */ Blk151745F0 unk10;
    /* 0x34 */ s8 unk34;
    /* 0x35 */ char pad35[3];
    /* 0x38 */ s32 unk38;
} Rec151745F0;

extern Rec151745F0 D_800DD348[];
extern Rec151745F0 D_800DD3FC[];

s32 func_151745F0(f32 arg0, f32 arg1, f32 arg2, Blk151745F0 *arg3, s8 arg4, s32 arg5) {
    Rec151745F0 *p;

    p = D_800DD348;
    do {
        if (p->unkC == 0) {
            p->unk0 = arg0;
            p->unk4 = arg1;
            p->unkC = 3;
            p->unk8 = arg2;
            p->unk34 = arg4;
            p->unk38 = arg5;
            if (arg3 != NULL) {
                p->unk10 = *arg3;
            }
            return 0;
        }
        p++;
    } while (p != &D_800DD348[3]);
    return 1;
}
