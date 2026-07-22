#include <ultra64.h>

#include "functions.h"
#include "variables.h"

s32 func_1600160C(s32 arg0);


void func_16000000(void) {
    func_160012B0(278, &D_160046AC);
}

s32 func_16000028(void) {
    if (D_16003890 & 0xC000) {
        D_16003AF4 = 1;
        return 3;
    }
    return 0;
}

void func_16000058(void) {
    s32 i;
    s32 phi_s2;

    func_16001338(255, 255, 255);
    func_160012B0(44, &D_160046D0); // "MAIN MENU"
    phi_s2 = 108;
    for(i = 0; i < 2; i++) {
        if (D_16003B1C == i) {
            func_16001338(255, 0, 0);     // red
        } else {
            func_16001338(255, 255, 255); // white
        }
        func_160012B0(phi_s2, D_16003B20[i]);
        phi_s2 += 32;
    }
    if (D_16003B1C == 2) {
        func_16001338(255, 0, 0);     // red
    } else {
        func_16001338(255, 255, 255); // white
    }
    if (D_16003AF0 != 0) {
        if ((D_1600389C->unk120 == 32) && (D_160038A4 == 0)) {
            func_160012B0(phi_s2, &D_160046DC);
        } else if (D_16003AF0 != 0) {
            func_160012B0(phi_s2, &D_160046E8);
        }
    } else {
        func_160012B0(phi_s2, &D_160046F4); // "RETRY CODE"
    }
    func_16001338(255, 255, 255);
    func_160012B0(611, &D_16004700); // "Version"
    func_16001044(619, 1, 163);
    func_160012B0(643, &D_16004708); // "Built"
    func_160012B0(651, &D_16004710); // "Dec 19 2000"
    func_160012B0(663, &D_1600471C); // "09:57:42"
}

s32 func_16000224(void) {
    s32 res = 0;

    if (D_16003890 & 0x40000) { // D_JPAD is 0x0400
        D_16003B1C -= 1;
        res = 1;
    }
    if (D_16003890 & 0x80000) { // U_JPAD is 0x0800
        D_16003B1C += 1;
        res = 1;
    }
    if (D_16003B1C >= 3) {
        D_16003B1C = 0;
    }
    if (D_16003B1C < 0) {
        D_16003B1C = 2;
    }
    if (D_16003890 & A_BUTTON) {
        switch(D_16003B1C) {
            case 0:
                res = 3;
                D_16003AF4 = 2;
                break;
            case 1:
                res = 3;
                D_16003AF4 = 3;
                break;
            case 2:
                res = 4;
                break;
        }
    }
    return res;
}

void func_16000304(void) {
}

void func_1600030C(void) {
}

void func_16000314(void) {
    switch(D_16003B28) {
        case 0:
            func_16000424(D_1600389C);
            func_160006CC(D_1600389C);
            break;
        case 1:
        case 2:
            func_16000590(D_1600389C);
            break;
    }
}

s32 func_16000384(void) {
    s32 res = 0;

    if (D_16003890 & (R_CBUTTONS | D_CBUTTONS)) {
        D_16003B28 += 1;
        if (D_16003B28 >= 3) {
            D_16003B28 = 0;
        }
        return 3;
    }
    if (D_16003890 & (L_CBUTTONS | U_CBUTTONS)) {
        D_16003B28 -= 1;
        if (D_16003B28 < 0) {
            D_16003B28 = 2;
        }
        return 3;
    }
    if (D_16003890 & B_BUTTON) {
        D_16003AF4 = 1;
        res = 3;
    }
    return res;
}

void func_16000424(struct118 *arg0) {
    // TODO is this a RGB struct?
    u32 tmp0;
    u32 tmp1;
    s32 pad;

    func_16001338(255, 255, 255);
    func_160012B0(35, &D_16004728);     // "Pc"
    func_16001044(43, 0, arg0->unk11C);
    func_160012B0(67, &D_1600472C);     // "Cause"
    func_16001044(75, 0, arg0->unk120);
    func_16001338(128, 128, 255);
    tmp0 = arg0->unk120;
    tmp1 = (tmp0 >> 2) & 0xF;

    func_160012B0(107, D_16003848[tmp1]);
    if (tmp1 == 11) {
        func_16001044(111, 1, (tmp0 >> 28) & 3);
    }
    func_16001338(255, 255, 255);
    func_160012B0(131, &D_16004734);      // "Sr"
    func_16001044(139, 0, arg0->unk118);
    func_160012B0(163, &D_16004738);      // "Badvadr"
    func_16001044(171, 0, arg0->unk124);
    func_160012B0(195, &D_16004740);      // "Thread"
    func_16001044(203, 1, arg0->unk14);
    if (D_160038A4 != 0) {
        func_160012B0(52, &D_16004748);   // "Lockup_Now"
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/debugger/debugger/func_16000590.s")
// NON-MATCHING: score 1532, but PURELY register-allocation. Every instruction's opcode,
// operand order, immediate and memory offset matches the target - the only difference is that
// the target promotes the pointer parameter to saved register s5 (`move s5,a0`, then uses it as
// `0x12c(s5)` and `s5+idx*4`) and so uses 6 saved regs (s0-s5), while IDO homes the parameter
// to 0x30(sp) for my source and reloads it (5 saved regs, s0-s4). That single spill cascades a
// rename onto nearly every saved-register instruction, inflating the score. Tried every form of
// the two arg0 accesses - (u8*)+off / (s32*)[] inline / a `ctx` local / an `s32*` parameter / a
// file-local struct member / a `register` pointer local - none make IDO keep arg0 in a saved
// register across the (arg0-free) first loop; it always homes+reloads it. `i+col` inlined in the
// 2nd loop DOES strength-reduce to the target's `addu` induction base, so the logic below is
// byte-exact in operation. PERMUTER CANDIDATE (register-only).
//
// extern u8 D_160047A4[];
// extern u8 D_160047AC[];
// extern u8 *D_16003B30[];
//
// void func_16000590(s32 *arg0) {          // arg0 is the exception-context / register dump
//     u32 val;
//     s32 i, pos, col, idx;
//     s32 *rp;
//     col = 0;
//     val = arg0[0x4B];                     // arg0->0x12C
//     func_160012B0(3, D_160047A4);
//     func_16001044(0xA, 0, val);
//     val >>= 12;
//     pos = 0x2C;
//     for (i = 0; i < 6; i++) {
//         if (val & 1) { func_160012B0(pos, D_16003B30[i]); pos += 0x20; }
//         val >>= 1;
//     }
//     i = 0;
//     pos = 0xC3;
//     if (D_16003B28 == 1) { idx = 0x4C; } else { idx = 0x6C; col = 0x10; }
//     rp = &arg0[idx];
//     for (; i < 0x10; i++) {
//         func_160012B0(pos, D_160047AC);
//         func_16001044(pos + 2, 1, i + col);
//         func_16001044(pos + 5, 2, rp[1]);
//         rp += 2;
//         pos += 0x20;
//     }
// }

#pragma GLOBAL_ASM("asm/nonmatchings/debugger/debugger/func_160006CC.s")
// NON-MATCHING: best score 135, one instruction short. Everything (frame 0x40, the
// D_16003B48 struct copy through $at, the whole rotated do-while with bnezl, the loop body,
// the arg0[idx*4+4] value load, the epilogue) is byte-identical EXCEPT the peeled first read of
// the table: the original emits
//     lui t0,%hi(D_160037F0) / addiu t0,t0,%lo(D_160037F0) / lbu v0,0(t0)
// (materializes the address in a fresh caller-saved register), while IDO folds mine to
//     lui v0,%hi / lbu v0,%lo(D_160037F0)(v0)
// for EVERY source form tried (array/struct/pointer var/cast/index var/register/q-after-call/
// q=p/index-and-zero). A single-use constant global pointer always folds; the fresh materialize
// is an IDO allocation decision. The missing addiu makes the fn 4 bytes short, and the freed
// register cascades a t1<->t0 rename through the loop (hence 135, not ~15). A `for` loop DOES
// materialize but adds an entry-guard + duplicate read (854, worse). PERMUTER CANDIDATE
// (%lo-fold; permuter's `q=&global` reload mutations can force the materialize).
// D_160037F0 (3-byte {char,char,ctx-word-index} records) and D_16003B48 (the "\0\0 \0"
// template) are not in variables.h, so they are declared file-locally here.
//
// typedef struct {
//     u8 name[2];
//     u8 idx;
// } DbgRegName;
//
// typedef struct {
//     u8 b[4];
// } DbgTextBuf;
//
// extern DbgRegName D_160037F0[];
// extern DbgTextBuf D_16003B48;
//
// void func_160006CC(struct118 *arg0) {
//     DbgTextBuf buf;
//     s32 pos;
//     DbgRegName *p;
//     u8 c;
//     DbgRegName *q;
//
//     buf = D_16003B48;
//     pos = 0x123;
//     p = D_160037F0;
//     q = D_160037F0;
//     func_16001338(192, 192, 255);
//     c = q->name[0];
//     do {
//         buf.b[0] = c;
//         buf.b[1] = p->name[1];
//         func_160012B0(pos, buf.b);
//         pos += 3;
//         func_16001044(pos, 0, *(s32 *) ((s32) arg0 + (p->idx * 4) + 4));
//         pos += 0xD;
//         p++;
//         c = p->name[0];
//     } while (c != 0);
// }
#pragma GLOBAL_ASM("asm/nonmatchings/debugger/debugger/func_1600078C.s")
// NON-MATCHING: close but still some stuff to figure out
// void func_1600078C(void) {
//     s32 temp_s0;
//     u8 range_prefix;
//     u32 temp_s2;
//     s32 temp_s5;
//     s32 phi_s1;
//     u32 *phi_s2;
//     u32 phi_s5;
//     DbgRegName *q;
//
//     temp_s0 = D_1600389C->unkF4;
//     func_16001338(0, 255, 0); // green
//     func_160012B0(11, &D_160047B0);
//     temp_s2 = (D_16003B4C * 4) + temp_s0;
//     if (((temp_s2 & 3) == 0) && (temp_s2 >= 0x80000000U) && (temp_s2 < 0x80800001U)) {
//         if (D_16003B4C == 0) {
//             func_16001338(255, 0, 0); // red
//             phi_s5 = &D_8002D4B0;
//         } else {
//             temp_s5 = &D_8002D4B0 - 0x2B50; // 11088 ?
//             if ((temp_s2 >= temp_s5) && (temp_s2 < (temp_s5 + 0x400))) {
//                 func_16001338(128, 128, 255); // purple
//                 phi_s5 = temp_s5;
//             } else if ((temp_s2 >= (u32) &D_8002D8B0) && (temp_s2 < ((u32)&D_8002D8B0 + 0x4000))) {
//                 func_16001338(255, 128, 128); // light red
//                 phi_s5 = temp_s5;
//             } else {
//                 func_16001338(255, 255, 255);
//                 phi_s5 = temp_s5;
//             }
//         }
//         phi_s1 = 97; // "a"
//         phi_s2 = temp_s2;
//         for (i = 0; i < 22; i++) {
//             func_16001044(phi_s1, 0, phi_s2);
//             func_160012B0(phi_s1 + 8, &D_160047BC);
//             range_prefix = (*phi_s2 >> 24);
//             if (range_prefix == 0x80) {                   // 0x80000000
//                 func_16001338(128, 128, 255);
//             } else if (range_prefix == 0x15) {            // 0x15000000
//                 func_16001338(255, 0, 0);
//             } else if (range_prefix == 0x16) {            // 0x16000000
//                 func_16001338(128, 255, 128);
//             } else if (range_prefix == 0x10) {            // 0x10000000
//                 func_16001338(255, 0, 0);
//             } else {
//                 func_16001338(255, 255, 255);
//             }
//             func_16001044(phi_s1 + 0xC, 0, *phi_s2);
//             func_160012B0(phi_s1 + 0x16, &D_160047C0);
//             func_16001338(255, 255, 255);
//             func_16001044(phi_s1 + 0x16, 1, *phi_s2);
//             if (((u32) phi_s2 >= phi_s5) && ((u32) phi_s2 < (phi_s5 + 0x400))) {
//                 func_16001338(128, 128, 0xFF);
//             } else if (((u32) phi_s2 >= (u32) &D_8002D8B0) && ((u32) phi_s2 < ((u32)&D_8002D8B0 + 0x4000))) {
//                 func_16001338(255, 128, 128);
//             } else {
//                 func_16001338(255, 255, 255);
//             }
//             phi_s1 += 0x20;
//             phi_s2 += 4;
//         }
//     }
// }

s32 func_16000A5C(void) {
    s32 res = 0;

    if ((D_160036F3 >= 41) || (D_16003890 & U_CBUTTONS)) {
        D_16003B4C -= 1;
        if (D_16003B4C < 0) {
            D_16003B4C = 0;
        } else {
            res = 3;
        }
    } else if ((D_160036F3 < -40) || (D_16003890 & D_CBUTTONS)) {
        D_16003B4C += 1;
        if (D_16003B4C >= 201) {
            D_16003B4C = 200;
        }
        res = 3;
    }
    if ((D_16003890 & B_BUTTON)) {
        D_16003AF4 = 1;
        res = 3;
    }
    return res;
}

// called from func_10007DAC
#pragma GLOBAL_ASM("asm/nonmatchings/debugger/debugger/func_16000B14.s")
#pragma GLOBAL_ASM("asm/nonmatchings/debugger/debugger/func_16000F8C.s")
// NON-MATCHING: best score 77. Marking `bits`/`exp` `register` (below) makes IDO compute exp
// exactly once (matching the target's instruction count) - every instruction then matches
// EXCEPT the stack frame is 0x60 vs the target's 0x58: IDO reserves an unused 8-byte -g3 debug
// home for `bits` and `exp` even though both live only in registers (no stores to 0x58/0x5c
// ever emitted). buf@0x28 and the f32 scratch val@0x54 are already correct; the only knock-on
// is the temp-register picks (v0/t9 vs t9/t0). Removing the named locals (inlining exp) drops
// the dead homes but then IDO computes exp TWICE (val is address-taken, so not CSE'd) -> worse.
// Catch-22: exp must be a named local to be computed once, but a named local reserves the -g3
// home the target lacks. Not crackable from C by hand. PERMUTER CANDIDATE.
//
// void func_16000F8C(s32 arg0, f32 arg1) {
//     register s32 bits;
//     register u32 exp;
//     s32 val;
//     u8 buf[0x2C];
//     if ((arg0 >= (D_160038A0 << 5)) && (arg0 < 833)) {
//         *(f32 *) &val = arg1;
//         bits = val;
//         exp = ((u32) bits & 0x7F800000) >> 23;
//         if ((exp == 0 || exp >= 0xFF) && ((bits << 1) != 0)) {
//             func_160012B0(arg0, D_160047D0);
//         } else {
//             func_16001B34(buf, D_160047D4, D_160047DC, D_160047E0, arg1);
//             func_160012B0(arg0, buf);
//         }
//     }
// }
//
#if 0
// Earlier analysis / reconstructions:
// NON-MATCHING: every instruction matches except the stack frame is 0x60 instead of 0x58
// (IDO gives `bits` and `exp` an unused 8-byte home slot here, which the original does not
// have) and consequently the sp offsets 0x60 vs 0x58 and the temp register picks differ.
// The local offsets that matter are right: buf at sp+0x28, the f32 scratch at sp+0x54.
// void func_16000F8C(s32 arg0, f32 arg1) {
//     s32 bits;
//     u32 exp;
//     s32 val;
//     u8 buf[0x2C];
//
//     if ((arg0 >= (D_160038A0 << 5)) && (arg0 < 833)) {
//         *(f32 *) &val = arg1;
//         bits = val;
//         exp = ((u32) bits & 0x7F800000) >> 23;
//         if (((exp == 0) || (exp >= 0xFF)) && ((bits << 1) != 0)) {
//             func_160012B0(arg0, D_160047D0);
//         } else {
//             func_16001B34(buf, D_160047D4, D_160047DC, D_160047E0, arg1);
//             func_160012B0(arg0, buf);
//         }
//     }
// }

// NON-MATCHING: lots to figure out
// void func_16000F8C_old(s32 arg0, f32 arg1) {
//     struct165 tmp;
//     s32 temp_v1;
//     u32 temp_t9;
//
//     if ((arg0 >= (D_160038A0 << 5)) && (arg0 < 833)) {
//         tmp.unk18 = arg1;
//         temp_v1 = *(s32*)&tmp.unk18;
//         temp_t9 = (u32) (temp_v1 & 0x7F800000) >> 0x17;
//         if ((temp_t9 == 0) || (temp_t9 >= 0x255U)) {
//             if ((temp_v1 * 2) != 0) {
//                 func_160012B0(arg1, &D_160047D0); // arg0,
//                 return;
//             }
//         }
//         func_16001B34(&arg0, &tmp.unk0, &D_160047D4, &D_160047DC, &D_160047E0); // , (f64) arg1
//         func_160012B0(arg0, &tmp.unk0);
//     }
// }
#endif

#pragma GLOBAL_ASM("asm/nonmatchings/debugger/debugger/func_16001044.s")
// NOT ATTEMPTED (large + guaranteed near-miss). func_16001044(s32 pos, s32 mode, s32 val) draws a
// value at framebuffer position `pos` in one of three formats. Structure fully analysed:
//   - Top: struct-copies the 10-word powers-of-10 table D_16003B50[0..9] (1,10,...,1e9) into a
//     local s32 pow[10] at sp+0x78 (IDO emits a 3-word-unrolled bne copy loop + tail word).
//   - Bounds guard: if (pos < (D_160038A0 << 5) || pos >= 0x341) return;  fb = func_1600160C(pos).
//   - mode 0 (hex): s1 = fb + 0x70; for (i=0;i<8;i++){ nib = val & 0xF; c = (u8)((nib>=0xA?nib+7:nib)
//     + 0x30); func_160014F0(s1, c); val >>= 4 (sra); s1 -= 0x10; }
//   - mode 1 (decimal): if (val < 0) { func_160014F0(fb,'-'); val = -val; } then divide by pow[9..0]
//     high->low extracting digits (IDO's 64-bit signed `div` idiom with break 7 / break 6 guards),
//     suppressing leading zeros, drawing each digit via func_160014F0.
//   - mode 2 (float): the SAME exponent test + func_16001B34(buf,&D_160047E8,&D_160047F0,&D_160047F4,
//     (f64)*(f32*)&val) + func_160012B0(pos,buf) pattern as func_16000F8C, or func_160012B0(pos,
//     &D_160047E4) for inf/nan/denormal. This float path inherits func_16000F8C's UNFIXABLE -g3
//     debug-home frame issue, so the whole function cannot reach 0 by hand. PERMUTER CANDIDATE.

void func_160012B0(s32 arg0, u8 *arg1) {
    if (arg1 && (arg0 >= (D_160038A0 << 5)) && (arg0 < 833)) {
        s32 fb = func_1600160C(arg0);
        while (*arg1 != 0) {
            fb = func_160014F0(fb, *arg1 & 0xFF);
            *arg1++;
        }
    }
}
// convert rgb to rgba16
void func_16001338(u8 arg0, u8 arg1, u8 arg2) {
    D_1600388C = ((arg0 & 0xF8) << 8) | ((arg1 & 0xF8) << 3) | ((arg2 & 0xF8) >> 2) | 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/debugger/debugger/func_16001390.s")
// NON-MATCHING: best score 749, but STRUCTURALLY byte-exact - a filled-rectangle blit.
// The prologue (frame 0x20, all four s16 param homes, the x1->s0 promotion `move s0,t8`,
// every sign-extension), the func_1600160C(0) call with y0/x0/y1+1 spilled to the param homes
// and reloaded, BOTH loops (the inner LOOP_UNROLL'd `for (i=x1; i>0; i--) *fb++ = D_1600388C;`
// down-counter with the blez guard, the outer row-advance `fb += width - cols`), and the whole
// epilogue all match in opcode/immediate/offset. The ONLY diff is register allocation in the
// cols/rows/pointer setup block: the target reloads y1+1 straight into a3 (the row-induction
// register) so `subu a3,a3,a2` + in-place `sll t2,a3;sra a3,t2` keeps (s16)rows in a3 for BOTH
// the entry `blez a3` guard and the loop; IDO instead reloads y1+1 into a temp, computes rows in
// a0, then sign-extends it TWICE (once for the guard, once for the induction) + a `move a3,tN`.
// Same JUSTREG class as func_1000C934 (memory) - which register IDO reloads a spilled param into
// isn't controllable from C. Reordering cols/rows/pointer, for/while/do-while forms, and reusing
// x1 as cols were all explored (3561 -> 754 -> 749). PERMUTER CANDIDATE (register-only).
//
// void func_16001390(s16 x0, s16 y0, s16 x1, s16 y1) {
//     s16 rows;
//     u16 *fb;
//     s32 i;
//     if (x1 < x0) { return; }
//     if (y1 < y0) { return; }
//     if (x0 < 0) { return; }
//     if (y0 < 0) { return; }
//     x1++;
//     y1++;
//     fb = (u16 *)func_1600160C(0);
//     rows = y1 - y0;
//     x1 -= x0;
//     fb += x0 + y0 * D_160038A8;
//     for (; rows > 0; rows--) {
//         for (i = x1; i > 0; i--) {
//             *fb++ = D_1600388C;
//         }
//         fb += D_160038A8 - x1;
//     }
// }
#pragma GLOBAL_ASM("asm/nonmatchings/debugger/debugger/func_160014F0.s")
// NON-MATCHING: score 1220, but the LOGIC is byte-exact - every instruction in the whole body
// (the two-var clamp, the (idx-0x20)*8 glyph offset with subtract-first via `idx -= 0x20`, the
// LOOP_UNROLL'd 4x pixel expander with the u16 `pixel` temp, the per-row fb += width-8 advance,
// the a0+0x10 return) matches in opcode/immediate/offset. The ONLY diff is register allocation
// at the top: the target keeps the masked arg1 in a1 (`andi t6,a1; move a1,t6`) and so emits the
// -g3 dead param-home `sw a1,4(sp)` for the modified parameter, using a separate a2 for `idx`;
// IDO computes my `arg1 & 0xFF` straight into a2, merging arg1 and idx (arg1's live range ends
// at the clamp), which drops the home + move and cascades a rename onto every later instruction.
// No source form (in-place `&=` vs `=&`, separate idx, idx-=0x20, u16 pixel) makes IDO keep the
// modified arg1 in a1 to trigger the home. Glyph bitmap D_16003CE0 declared file-locally.
// PERMUTER CANDIDATE (register-only).
//
// extern u8 D_16003CE0[];
// s32 func_160014F0(s32 arg0, s32 arg1) {
//     u16 color, px, pixel;
//     u8 *gp;
//     u16 *fb;
//     s32 row, col, idx;
//     arg1 &= 0xFF;
//     color = D_1600388C;
//     fb = (u16 *)arg0;
//     idx = arg1;
//     if (arg1 < 0x20) idx = 0x20;
//     idx -= 0x20;
//     gp = &D_16003CE0[idx * 8];
//     for (row = 0; row < 8; row++) {
//         px = *gp;
//         for (col = 0; col < 8; col++) {
//             pixel = (px & 0x80) ? color : 1;
//             *fb++ = pixel;
//             px = (px << 1) & 0xFFFF;
//         }
//         fb += D_160038A8 - 8;
//         gp++;
//     }
//     return arg0 + 0x10;
// }

// splat into framebuffer
s32 func_1600160C(s32 arg0) {
    s32 row;
    s32 width;
    s32 tmp;
    s32 w2;

    tmp = arg0 & 0xFFE0;
    row = tmp;
    width = D_160038A8;
    if (width != 0x124) {
        row = (tmp >> 2) + tmp;
    }
    w2 = width * 2;
    row = (row >> 2) * w2;
    row += (arg0 & 0x1F) << 4;
    row += width * 4;
    row += 0x10;
    return D_8002AAE8[D_16003888] + row;
}

// contains delay slot
void func_16001678(void) {
    u32 *ptr;
    u32 *end;
    s32 height;
    s32 width;

    ptr = (u32 *) D_8002AAE8[D_16003888];
    width = D_160038A8;
    if (width == 0x124) {
        height = 0xD7;
    } else {
        height = 0x108;
    }
    end = ptr + ((width >> 1) * height);
    while (ptr < end) {
        ptr[0] = 0x00010001;
        ptr[1] = 0x00010001;
        ptr[2] = 0x00010001;
        ptr[3] = 0x00010001;
        ptr += 4;
    }
}

s32 func_160016F4(s32 arg0) {
    return arg0;
}
