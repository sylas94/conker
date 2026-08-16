/* func_151BDD8C  --  game_1E73B0.c  (217 asm lines, 2 mul, 8 fp, 1 callee)
 *
 * BEST SCORE 1685.  Progression: 3267 -> 1992 -> 1840 -> 1795 -> 1769 -> 1685.
 * FRAME AND EVERY STACK OFFSET NOW MATCH GOLDEN EXACTLY (0xA8; 0x14 ra, 0x28 p
 * temp, 0x4C/0x5C ptr arrays, 0x70/0x88 vec arrays, 0xA0 actor home).
 * Only 13 instruction-level diffs remain (plus 126 register renames):
 *
 *   bash tools/buildlock.sh bash -c 'cd conker && make -s build/src/game_1E73B0.c.o VERSION=us \
 *       && python3 ../tools/asm-differ/diff.py -o func_151BDD8C -R --max-lines 4096'
 *
 * ============================ WHAT IS SETTLED ============================
 *
 * ACTOR INDEXING IS THE `div' POINTER-DIFFERENCE FORM (as the brief predicted
 * for this one):  `subu a2,t4,&D_800CC2D0 ; li at,0x32C ; div ; mflo a2'.
 * The pointer subtracted is `p->unk0' (the struct127* at arg0+0x28), NOT arg0.
 *
 * THE TWO `multu' ARE **NOT** ACTOR INDEXING.  Both are `multu a0,a3' with
 * a3 = 0xC hoisted as a loop invariant -- they are `i * sizeof(vertex)' for the
 * two stack `vertex[2]' arrays.  Verified: the products feed `t0 = sp+0x88' and
 * `t1 = sp+0x70', which are 24-byte (2 x 12) regions.
 *
 * NO RODATA RISK AT ALL.  All six fp constants are lui-able (low16 == 0):
 * 0x41000000=8.0, 0x40400000=3.0, 0x3F800000=1.0, 0x3FC00000=1.5,
 * 0x41A80000=21.0, 0x40C00000=6.0.  They inline via lui+mtc1 and match.
 *
 * `lw at,0(t7) ; sw at,0x34(a2)' x3 USING **$at** IS A STRUCT COPY, not six
 * scalar assignments -- $at is never a data register in ordinary C expressions.
 * So the destination has two 12-byte members at 0x34 and 0x40 and the source is
 * `vertex sp88[2] / sp70[2]'.  `objA->unk34 = sp88[i];' reproduces it exactly,
 * including the $at usage and the interleaved load/store order.
 *
 * THE COUNTERS ARE `u8'.  Every loop ends `andi t,i,0xff ; slti at,t,2 ;
 * bnez ; move i,t' -- mask on ASSIGNMENT, unmasked use = a u8 local.
 * THE ACTOR INDEX IS NOT: `slti at,a2,4' is unmasked and the two array uses are
 * `andi ...,0xff' at the USE site, i.e. an explicit `(u8)idx' cast twice.
 *
 * THE FIRST GUARD'S OPERAND ORDER: golden loads `p->unk4' FIRST then
 * `actor->unique_id'; because IDO reverses comparison operands the source must
 * read `actor->unique_id != p->unk4' (writing it the other way swapped the two
 * lbu's -- measured, 3267 -> the swap alone was worth ~1275 with the rest).
 *
 * `p' (= arg0 + 0x28) IS **NOT** A HOME-SLOT LOCAL: it spills to 0x28, i.e.
 * a COMPILER TEMP below the home area, whereas `actor' spills to 0x A0 inside
 * the home area.  By the spill-destination law that makes `p' an address CSE
 * and `actor' a declared pointer -- but declaring `p' anyway is what puts the
 * spill at 0x28, so it is kept.
 *
 * THE LOCAL COUNT IS PINNED AT 12 SCALARS + 80 BYTES OF ARRAYS:
 *   frame = 0x18 (arg build + ra) + 4*(scalars + 4 compiler temps) + 80.
 *   9 scalars -> 0x88.  Adding objA/objB/sa/sb -> 0x98.  Adding four more -> 0xA8.
 *   Removing `idx' -> 0xA0.  The set below (p, actor, idx, objA, objB, objA2,
 *   objB2, objA3, objB3, sa, sb, i, j -- j packs with i) reproduces 0xA8 and
 *   EVERY stack offset.  Per-loop obj locals are a GUESS that happens to give
 *   the right count; a different 12-scalar set may be the real one.
 *
 * ========================== THE THREE OPEN DIFFS ==========================
 *
 * (1) THE SUB-POINTER IS MATERIALISED IN GOLDEN AND FOLDED HERE (8 instrs).
 *     golden loop2:  addiu v0,a0,0x110 ; lbu t5,0x58(v0) ; and ; sb t6,0x58(v0)
 *     this build:                        lbu t5,0x168(v0) ; and ; sb t6,0x168(v0)
 *     Same for `objB + 0x170' in loop 3 (golden keeps the addiu even though only
 *     ONE offset, 0x4, is used through it), and loop 3's `objA + 0x110' is
 *     emitted TWICE here (once per side of the inner if) where golden emits it
 *     once before the test.
 *     MEASURED, ALL FOLD IDENTICALLY (all 1685, byte-for-byte the same output):
 *        inline  ((SubA *)((u8 *)obj + 0x110))->unk58 &= ~1
 *        via a declared typed local  sa = (SubA *)((u8 *)obj + 0x110); sa->unk58 &= ~1
 *        via a declared s32          sa = (s32)obj + 0x110; *(u8 *)(sa + 0x58) &= ~1
 *     So IDO folds `base + const' into the load displacement regardless of the
 *     spelling, and the ONLY case where it does NOT fold in THIS build is when
 *     the assignment and the uses are in DIFFERENT BASIC BLOCKS (loop 3's objA,
 *     which is used inside an if/else -- and that one does match golden).
 *     => golden's un-folded loop-2 and objB addiu's mean the value reaching the
 *     use is something IDO cannot prove is base+const.  NOT YET FOUND.
 *     Note loop 1 folds in BOTH (`objA->unk168 |= 1' -> lbu 0x168), so the
 *     source really is inconsistent between the loops; do not "fix" that.
 *
 * (2) THE FIRST `src[]' STORE IS SCHEDULED EARLY IN GOLDEN (4 instrs).
 *     golden: lui t8 ; addiu t8,%lo(D_800AA778) ; sw t8,0x5c(sp) ; then the
 *     other three lui's, three addiu's, and the remaining seven sw's.
 *     this build emits four lui, four addiu, then all eight sw contiguously.
 *     Pure scheduling; likely downstream of (1)/(3).
 *
 * (3) 126 REGISTER RENAMES.  The shape is systematic, not random:
 *        golden  v0=sub pointer   v1=mflo temp  a0=i        a1=&p[i]  a2=obj
 *                a3=-3/0xC/&D_800BE728         t2=-5        t3=p      t4=actor
 *        here    v0=obj           v1=sub        a0=&p[i]    a1=i      a2=const
 *                a3=-5                          t2=p        t3=actor
 *     i.e. golden hands v0 to the SUB pointer and a2 to the object, this build
 *     the reverse, and everything downstream shifts by one.  Since IDO's
 *     allocation order is v0,v1,a0-a3,t0-t5, golden's priority list puts the sub
 *     pointer above the object -- the variable SET/ORDER is still not exactly right.
 *
 * NEGATIVES WORTH NOT REPEATING (all measured):
 *   - `p->unk8[i]->x' written out at each use (no obj local): 3267, adds five
 *     redundant `lw v0,8/0x10(v1)' reloads.  The obj locals are required.
 *   - dropping `idx' and using `(u8)(actor - D_800CC2D0)' inline: frame 0xA0
 *     (wrong) even though the div/CSE is identical -- 1769.
 *   - one shared counter for all three loops: 1795; golden uses a0 for loops
 *     1 and 3 and a1 for loop 2, so there are at least two counters (1685).
 */

extern vertex D_800AA778;
extern vertex D_800AA784;
extern vertex D_800AA790;
extern vertex D_800AA79C;
extern void func_15145EA4(vertex **arg0, vertex **arg1, void *arg2, s32 arg3);

typedef struct {
    u8 pad0[0x48];
    /* 0x48 */ f32 unk48;
    /* 0x4C */ f32 unk4C;
    u8 pad50[0x8];
    /* 0x58 */ u8 unk58;
} SubA151BDD8C;

typedef struct {
    u8 pad0[0x4];
    /* 0x04 */ f32 unk4;
} SubB151BDD8C;

typedef struct {
    u8 pad0[0x34];
    /* 0x34 */ vertex unk34;
    /* 0x40 */ vertex unk40;
    u8 pad4C[0x168 - 0x4C];
    /* 0x168 */ u8 unk168;
} ObjA151BDD8C;

typedef struct {
    u8 pad0[0x34];
    /* 0x34 */ vertex unk34;
    /* 0x40 */ vertex unk40;
    u8 pad4C[0xC];
    /* 0x58 */ s32 unk58;
} ObjB151BDD8C;

typedef struct {
    /* 0x00 */ struct127 *unk0;
    /* 0x04 */ u8 unk4;
    u8 pad5[0x3];
    /* 0x08 */ ObjA151BDD8C *unk8[2];
    /* 0x10 */ ObjB151BDD8C *unk10[2];
} Sub151BDD8C;

typedef struct {
    u8 pad0[0xE];
    /* 0x0E */ s16 unkE;
} Obj151BDD8C;

void func_151BDD8C(Obj151BDD8C *arg0) {
    Sub151BDD8C *p;
    struct127 *actor;
    vertex sp88[2];
    vertex sp70[2];
    s32 idx;
    vertex *src[4];
    vertex *dst[4];
    ObjA151BDD8C *objA;
    ObjB151BDD8C *objB;
    ObjA151BDD8C *objA2;
    ObjB151BDD8C *objB2;
    ObjA151BDD8C *objA3;
    ObjB151BDD8C *objB3;
    SubA151BDD8C *sa;
    SubB151BDD8C *sb;
    u8 i;
    u8 j;

    p = (Sub151BDD8C *)((u8 *)arg0 + 0x28);
    actor = p->unk0;
    if ((actor->interaction_state == 0) || (actor->unique_id != p->unk4)) {
        arg0->unkE = -1;
        return;
    }
    j = 0;
    if ((actor->unk1D4 != NULL) && ((actor->unk74 & 0xF) != 0xF)) {
        src[0] = &D_800AA778;
        src[1] = &D_800AA784;
        src[2] = &D_800AA790;
        src[3] = &D_800AA79C;
        dst[0] = &sp88[0];
        dst[1] = &sp88[1];
        dst[2] = &sp70[0];
        dst[3] = &sp70[1];
        func_15145EA4(src, dst, (u8 *)actor->unk1D4 + 0x40, 4);
        for (i = 0; i < 2; i++) {
            objA = p->unk8[i];
            if (objA != NULL) {
                objA->unk168 |= 1;
                objA->unk34 = sp88[i];
                objA->unk40 = sp70[i];
            }
            objB = p->unk10[i];
            if (objB != NULL) {
                objB->unk58 |= 2;
                objB->unk58 &= ~4;
                objB->unk34 = sp88[i];
                objB->unk40 = sp70[i];
            }
        }
    } else {
        for (j = 0; j < 2; j++) {
            objA2 = p->unk8[j];
            if (objA2 != NULL) {
                sa = (SubA151BDD8C *)((u8 *)objA2 + 0x110);
                sa->unk58 &= ~1;
            }
            objB2 = p->unk10[j];
            if (objB2 != NULL) {
                objB2->unk58 &= ~2;
            }
        }
    }
    idx = actor - D_800CC2D0;
    if (idx < 4) {
        for (i = 0; i < 2; i++) {
            objA3 = p->unk8[i];
            if (objA3 != NULL) {
                sa = (SubA151BDD8C *)((u8 *)objA3 + 0x110);
                if (*(u16 *)((u16 **)D_800BE728[0])[(u8)idx] & 0x8000) {
                    sa->unk48 = 6.0f;
                    sa->unk4C = 21.0f;
                } else {
                    sa->unk48 = 3.0f;
                    sa->unk4C = 8.0f;
                }
            }
            objB3 = p->unk10[i];
            if (objB3 != NULL) {
                sb = (SubB151BDD8C *)((u8 *)objB3 + 0x170);
                if (*(u16 *)((u16 **)D_800BE728[0])[(u8)idx] & 0x8000) {
                    sb->unk4 = 1.5f;
                } else {
                    sb->unk4 = 1.0f;
                }
            }
        }
    }
}
