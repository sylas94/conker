/* tools/nearmiss/func_151E81EC.c -- game_20AE20, 10 instructions, leaf
 *
 * STATUS: mism=26, n=12/10 (TWO OVER).  Cold decompile 2026-08-25.
 *
 * WHAT IT IS: five zero stores.  Golden:
 *      lui at,%hi(D_800E0BA4) ; sw zero,%lo(D_800E0BA4)(at) ; sw zero,%lo(D_800E0BA0)(at)
 *      lui at,%hi(D_800E0BA8) ; sw zero,%lo(D_800E0BA8)(at) ; sw zero,%lo(D_800E0BAC)(at)
 *      lui at,%hi(D_8008FD84) ; sb zero,%lo(D_8008FD84)(at)
 *
 * ------------------------------------------------------------------ THE WHOLE PROBLEM
 * Golden REUSES $at across each PAIR but reloads it between them -- even though both %hi
 * values are the same 0x800e.  Measured: IDO never reuses $at across two DISTINCT symbols
 * (four separate `extern s32` gives four luis, n=12), so the pairs must be ONE symbol each,
 * i.e. two 8-byte objects at 0x800E0BA0 and 0x800E0BA8, stored +4,+0 and then +0,+4.
 *
 * But every aggregate spelling makes IDO build a BASE REGISTER ($v0/$v1 + addiu) instead of
 * the `$at` macro form, which also costs 12.  Refuted, all n=12:
 *      extern s32 D_800E0BA0[2] / [] ....... base pointer in v0,v1        (26/30)
 *      a 2-field struct .................... base pointer                (30)
 *      the same as tentative DEFINITIONS
 *        rather than extern .................. identical -- storage class is not the lever
 *      (&D_800E0BA0)[1] pointer-index ...... identical to the array form (30)
 *      u64 = 0 ............................. addiu t6,zero,0 + sw pairs  (68, n=16)
 *      D_800E0BA0 = D_800E0BA4 = 0 chains .. 14 instructions             (50)
 *
 * REOPEN WITH: the construct that makes IDO emit `sw $zero, sym+N($at)` -- the unexpanded
 * macro form WITH a non-zero addend.  Plain scalars give addend 0; every aggregate gives a
 * base register.  Until that is found this cannot close.
 */

extern s32 D_800E0BA0;
extern s32 D_800E0BA4;
extern s32 D_800E0BA8;
extern s32 D_800E0BAC;
extern u8 D_8008FD84;

void func_151E81EC(void) {
    D_800E0BA4 = 0;
    D_800E0BA0 = 0;
    D_800E0BA8 = 0;
    D_800E0BAC = 0;
    D_8008FD84 = 0;
}
