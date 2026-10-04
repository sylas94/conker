/* tools/nearmiss/func_15116110.c -- game_142560, 27 instructions, frame -0x28
 * STATUS: mism=37, n=25/27 (TWO SHORT).  Cold decompile 2026-08-25.
 * Lazily creates arg0->unk7C from the packed word arg0->unk3C, then clears unk3C.
 * The 7-arg call is func_15195FB0(arg0, v & 0x7FFF, v >> 15, -1, 0, (v>>24)&0xFF,
 * (v>>16)&0xFF) -- arg order confirmed against a0..a3 and sp+0x10/0x14/0x18.
 * LEFT: exactly the two missing words are a pair of register COPIES golden makes around the
 * 15-bit mask -- `or a1,v0,zero` before `andi t7,a1,0x7FFF` and `or a1,t7,zero` after.  Do
 * NOT add them by hand (that is a forcer).  The 0x7FFF mask next to `sra 15` says unk3C is a
 * packed field layout; find the declaration that makes IDO produce the copies naturally.
 */

typedef struct Obj15116110 {
    char pad0[0x3C];
    /* 0x3C */ s32 unk3C;
    char pad40[0x7C - 0x40];
    /* 0x7C */ s32 unk7C;
} Obj15116110;

extern s32 func_15195FB0(void *, s32, s32, s32, s32, s32, s32);

void func_15116110(void *a) {
    Obj15116110 *arg0;
    s32 v;

    arg0 = (Obj15116110 *)a;

    if (arg0->unk7C == 0) {
        v = arg0->unk3C;
        arg0->unk7C = func_15195FB0(a, v & 0x7FFF, v >> 15, -1, 0,
                                    (v >> 24) & 0xFF, (v >> 16) & 0xFF);
        arg0->unk3C = 0;
    }
}
