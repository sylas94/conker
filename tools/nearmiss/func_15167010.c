/* tools/nearmiss/func_15167010.c -- game_1944C0, 23 instructions, frame -0x28
 *
 * STATUS: mism=24, n=22/23 (ONE SHORT).  Cold decompile 2026-08-25.
 * Walks 101 struct115 records (0x34 each, D_8008B4A8 .. +0x1484) and calls record->unk18()
 * when it is non-NULL.  struct115 is already in structs.h; its unk18 is declared
 * void(*)(struct102*) but golden sets up NO argument before `jalr $v0`, hence the local
 * void(*)(void) view here.
 *
 * LAW E is already applied: `p < &D_8008B4A8[101]` gives golden's `addiu $s2,$s0,0x1484`
 * (end derived from the start register) rather than a second materialisation.
 *
 * ------------------------------------------------------------------ WHAT IS LEFT
 * Golden's frame is -0x28 and saves s0, s1, s2; ours is -0x20 and saves s0, s1.
 * **Golden saves $s1 and never uses it** -- so the original had THREE callee-saved locals and
 * one was optimised away but kept its slot (LAW C: count golden's saved registers, not just
 * its first temp).  Find the third local and the frame plus the missing word come together.
 * A do-while spelling scores identically (24), so the loop shape is not the lever.
 */

typedef struct Rec15167010 {
    char pad0[0x18];
    void (*unk18)(void);
    char pad1C[0x34 - 0x1C];
} Rec15167010;

void func_15167010(void) {
    Rec15167010 *p;

    for (p = (Rec15167010 *)D_8008B4A8; p < (Rec15167010 *)&D_8008B4A8[101]; p++) {
        if (p->unk18 != NULL) {
            p->unk18();
        }
    }
}
