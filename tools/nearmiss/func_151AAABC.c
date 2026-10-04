/* tools/nearmiss/func_151AAABC.c -- game_1D6E80, 37 instructions, frame -0x30
 *
 * STATUS: mism=45, n=35/37 (TWO SHORT), frame -0x28 vs -0x30.  Cold decompile 2026-10-02.
 * Rows 0-7 (prologue, the arg0->$a1 move, both field loads and `addiu $v1,$a1,0x58`) are
 * already byte-exact.
 *
 * WHAT IT IS: lazily create two sub-objects hanging off the +0x58 sub-struct, and if one
 * already exists, just set a flag byte inside it instead.
 *   `void *func_151AA48C(void *, s32)`   is DEFINED in this TU at line 393 (above us, so no
 *                                        forward declaration needed)
 *   `void *func_151AB2C4(struct_151AB2C4_arg *, s32)` is defined at line 583 (BELOW us, so a
 *                                        forward declaration IS needed or the compile fails
 *                                        with "redeclaration of func_151AB2C4"); the typedef
 *                                        struct_151AB2C4_arg is at line 40, so it is usable.
 * BOTH CALLS TAKE TWO ARGUMENTS and golden only ever sets $a0 -- `$a1` still holds arg0 from
 * the `or $a1,$a0,$zero` at the top, so the second argument IS arg0 itself.  That is why the
 * parameter gets copied into $a1 and doubles as the base for 0x6C/0x18/0x58.
 *
 * ---------------------------------------------------------------- SCORE LADDER (measured)
 *   57  n=34/37 -- flag writes spelled `*(u8 *)(p->unk14 + 0x84) = 1`
 *   45  n=35/37 -- >>> the flag writes go through an INTERMEDIATE POINTER LOCAL:
 *       `q = (Flag *)(p->unk14 + 0x80); q->unk4 = 1;`  and  `q = (Flag *)(p->unk1C + 0x58);
 *       q->unk4 = 1;`  Golden really does split the offset (`addiu $v0,$v0,128` then
 *       `sb $t7,4($v0)`, and `addiu $v0,$a0,88` then `sb $t8,4($v0)`), which only happens
 *       when the source names the +0x80 / +0x58 pointer.  Note the SAME `Flag` shape is
 *       applied at two different offsets.                                   <-- PARKED
 *
 * ---------------------------------------------------------------- WHAT IS LEFT
 * Two instructions and one 8-byte frame slot, which by [[conker-ido-local-decl-laws]] LAW I
 * means ONE MORE DECLARED LOCAL than the body below has.  The visible shape of the gap:
 * golden loads `lw $a0,0x1C($v1)` (p->unk1C) TWICE -- once in the `b` delay slot of the
 * then-arm and once on the fall-through -- and tests it with `beqz $a0`, i.e. that value is
 * materialised into the ARGUMENT register on both paths.  We load it once into $v0 and test
 * $v0.  Try giving p->unk1C its own local, and watch the `b 0x60` delay slot: golden fills
 * it with `lw $ra,0x14($sp)` (a shared epilogue load), we fill it with the flag store.
 */
typedef struct Flag151AAABC {
    char pad0[0x4];
    /* 0x4 */ u8 unk4;
} Flag151AAABC;

typedef struct Sub151AAABC {
    char pad0[0x14];
    /* 0x14 */ s32 unk14;
    char pad18[0x4];
    /* 0x1C */ s32 unk1C;
} Sub151AAABC;

typedef struct Obj151AAABC {
    char pad0[0x18];
    /* 0x18 */ s32 unk18;
    char pad1C[0x6C - 0x1C];
    /* 0x6C */ s32 unk6C;
} Obj151AAABC;

void *func_151AB2C4(struct_151AB2C4_arg *, s32);

void func_151AAABC(Obj151AAABC *arg0) {
    Sub151AAABC *p;
    Flag151AAABC *q;
    void *v;

    v = (void *)arg0->unk18;
    p = (Sub151AAABC *)((u8 *)arg0 + 0x58);
    if (arg0->unk6C != 0) {
        q = (Flag151AAABC *)(p->unk14 + 0x80);
        q->unk4 = 1;
    } else {
        p->unk14 = (s32)func_151AA48C(v, (s32)arg0);
    }
    if (p->unk1C != 0) {
        q = (Flag151AAABC *)(p->unk1C + 0x58);
        q->unk4 = 1;
    } else {
        p->unk1C = (s32)func_151AB2C4((struct_151AB2C4_arg *)v, (s32)arg0);
    }
}
