/*
 * NEAR-MISS: game_FB060 / func_150CDBB0 (324 bytes, 81 instructions)
 * BEST: fastscore mism=70, n=79/81.  Two instructions short.
 *   Measure with: python3 tools/fastscore.py game_FB060 func_150CDBB0 <cand.c>
 *
 * ============================================================== BEST SOURCE
 *   extern f32 D_800A07B0;                       // 3000.0f, asm/data/245270.rodata.s
 *
 *   typedef struct {                             // same shape as game_1312F0.c
 *       f32 unk00; f32 unk04; f32 unk08; f32 unk0C;
 *       f32 unk10; f32 unk14; f32 unk18;
 *       u8  unk1C; u8 pad1D[0x7];
 *   } Struct1504715C;                            // 0x24
 *
 *   void func_1504715C(Struct1504715C *, struct127 *);
 *   s32  func_15046C80(struct17 *, s32, f32, void *);
 *   void func_1514C678(f32, f32, s32, f32, s32, s32, s32, s32, s32, f32, s32, s32);
 *
 *   void func_150CDBB0(struct127 *arg0, u8 arg1, s32 arg2) {
 *       struct17 sp6C;
 *       Struct1504715C sp48;
 *
 *       if (arg0 == NULL) {
 *           return;
 *       }
 *       func_1504715C(&sp48, arg0);
 *       sp6C.unk0 = arg0->x_position;
 *       sp6C.unk4 = arg0->y_position + 1000.0f;
 *       sp6C.unk8 = arg0->z_position;
 *       if (func_15046C80(&sp6C, 0, arg0->y_position - D_800A07B0, &sp48) != 0) {
 *           sp6C.unk4 = sp48.unk00;
 *           func_1514C678(sp6C.unk0, sp6C.unk4, *(s32 *)&sp6C.unk8, 251.0f, 0, 0xFF,
 *                         (func_150ADA20() & 0xF) + 0x23, 0x17, 0, 0.0f, 0, arg1);
 *           func_1514C678(sp6C.unk0, sp6C.unk4, *(s32 *)&sp6C.unk8, 290.0f, 0, 0xFF,
 *                         (func_150ADA20() % 0x15U) + 0x1E, 0x18, 0, 0.0f, 0, arg1);
 *       }
 *   }
 *
 * ESTABLISHED (byte-identical): frame 0x78, EVERY stack displacement, both
 * parameter homes (`sw a1,0x7c` / `sw a2,0x80`), s0=arg0, the whole float block
 * (1000.0f inline and D_800A07B0=3000.0f from rodata), both branch targets, the
 * `andi v0,0xf` and `divu/mfhi %0x15` random forms, and all 12 outgoing
 * arguments of both calls including the inlined 251.0f and 290.0f.
 *
 * ================================================== THE PROTOTYPE IS SETTLED
 * game_19E040.c (live C, matched) declares and calls
 *      extern void func_150CDBB0(void *, u8, s32);
 *      func_150CDBB0(arg0, arg1, 1);
 * so three scalar parameters, with a u8 second.  arg2 is genuinely unused; IDO
 * homes it anyway under -g3.
 *
 * ================================================== DELTA 1 (1 insert, 1 delete)
 *   golden  0x7c  swc1 $f8,0x70(sp)  /  0x80 jal func_150ADA20  /  0x84 nop
 *   ours          jal func_150ADA20  /  swc1 $f8,0x70(sp) sunk into the delay slot
 * IDO clearly CAN put a store in a jal delay slot -- it does exactly that twice
 * in this same function for `jal func_1514C678 / swc1 $f10,0x24(sp)`.  Note the
 * difference in the two cases: 0x24(sp) is the OUTGOING ARGUMENT area (compiler
 * owned), while 0x70(sp) is inside sp6C, whose address escaped to func_15046C80.
 * Working hypothesis: IDO's delay-slot filler will not move a store to an
 * ESCAPED stack object across a call, only argument setup.  Unexplained: ours
 * moves it anyway from the same source.
 *
 * ================================================== DELTA 2 (the real blocker)
 * golden reloads the u8 parameter from its home slot before EACH call
 *     0x8c  lbu t0,0x7f(sp)      ...      0xe8  lbu t5,0x7f(sp)
 * ours loads it ONCE into s0 (free after arg0's last use at 0x60) and reuses it,
 * so the second lbu disappears and every integer temp in the second call block
 * rotates by one.  Golden never promotes arg1 and never saves s1 -- arg1 stayed
 * memory-resident with a per-use reload.
 *
 * ========================================= WHAT THE PERMUTER PROVED, AND WHY
 * ========================================= ITS ANSWER CANNOT BE SHIPPED
 * 8293 iterations.  Its best candidate (315 -> 202, the biggest single move
 * anyone has made on this function) is:
 *       u8 *new_var2 = &arg1;    ...    <12th arg> = *new_var2;   /* twice */
 * i.e. TAKE THE ADDRESS OF THE PARAMETER.  That is exactly the mechanism -- an
 * escaping address kills the cross-call CSE and forces the per-use `lbu` -- and
 * it is the confirmation that delta 2 is an ALIASING question, not a register
 * ranking tie as the previous note assumed.
 * REJECTED: nothing in this function takes arg1's address, and a pointer local
 * that exists only to launder a parameter through memory is a forcer.  Its
 * second candidate (305) casts one call's third argument to `(long long)` to
 * break a different CSE -- same objection.
 *
 * ================================ HONEST CAUSES OF THAT ALIASING, ALL RULED OUT
 * Every one of these produces the IDENTICAL object (mism=70, `lbu s0,0x7f(sp)`):
 *   - K&R-style definition (`void func_150CDBB0(arg0, arg1, arg2) struct127 *arg0;
 *     u8 arg1; s32 arg2; { ... }`) -- period-appropriate, and it changes nothing.
 *   - 4-byte struct-by-value 2nd parameter (`{u8 pad0[3]; u8 unk3;}`) read as
 *     `arg1.unk3`: still promoted to s0.  So "struct params are memory-resident"
 *     is FALSE for IDO 5.3 here.
 *   - 8-byte struct-by-value 2nd parameter with the 3rd folded into it: same.
 *   - `(u8)arg1` at both call sites; `s32 arg1` with casts.
 *   - named `s32` locals for the two random values: frame grows 0x78 -> 0x80,
 *     which also PROVES golden has no named locals beyond sp6C/sp48 and that the
 *     8 unexplained bytes at 0x40..0x47 are the hidden temp of a call inside an
 *     argument list (see func_150C71C0's note for the -g3 local-slot law).
 *
 * BAIL SIGNATURE: cross-call CSE of a parameter's home slot that only an
 * address-escape reproduces, and no honest construct in this function escapes.
 * REOPEN WITH: any IDO 5.3 construct OTHER than `&param` that marks a parameter
 * home slot as aliased -- or evidence that delta 1 (the escaped-store delay-slot
 * rule) is the root cause and delta 2 is downstream of it.
 * Left as #pragma GLOBAL_ASM.  NOT FAKED.
 */
