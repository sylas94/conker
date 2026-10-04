/* tools/nearmiss/func_151A85D4.c -- game_1D4E00, 20 instructions, frame -0x18
 *
 * TWIN of tools/nearmiss/func_151A8584.c -- byte-for-byte the same function with
 * D_8008F958 for D_8008F94C and func_15169824 for func_15169804.  READ THAT PARK; the
 * whole diagnosis (the -O2-vs--O2--g3 finding and the spill-placement residue) is there.
 * SOLVE ONE, SHIP BOTH.
 */

typedef struct Obj151A85D4 {
    char pad0[0x5C];
    /* 0x5C */ u8 unk5C;
} Obj151A85D4;

extern void (*D_8008F958[])(Obj151A85D4 *);

void func_151A85D4(Obj151A85D4 *arg0) {
    void (*fn)(Obj151A85D4 *);

    fn = D_8008F958[arg0->unk5C];
    if (fn != NULL) {
        fn(arg0);
    }
    func_151A8560(arg0);
    func_15169824((struct102 *)arg0);
}
