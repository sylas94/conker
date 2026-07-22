#include <n_libaudio.h>

extern s32  D_800E0E00;
extern s32  D_800E0E04;
extern s32  D_800E0E10;
extern s16  D_800E0E14;
extern s16  D_800E0E16;
extern u8   D_800E0E18;
extern u8   D_800E0E2C;
extern s32  D_800E0E20;
extern s32  D_800E0E24;
extern s32  D_800E0E28;
extern s32  *D_800E0E30; // 0x8000
extern s32  D_800E0D80; // libaudio struct?
extern s16  D_800E0DB0;
extern s16  D_800E0DB2;
extern s32  D_800E0DD8;
extern s32  D_800E0DE0;
extern s32  D_800E0DE4;
extern s32  D_800E0DFC;
extern s32  D_800E0E08;

// structs.h/n_libaudio.h note: N_ALSynth in the header places `dma` at 0x2C,
// but the real struct has it at 0x24. Headers are shared, so access it locally.
#define N_SYN_DMA(s) (*(ALDMANew *)((u8 *)(s) + 0x24))


// Best non-matching attempt for func_151F27E0 (CRC-5, poly 0x15).
// Everything matches except one detail: the target reuses the register holding
// the result of `v |= bit` for the following `v ^= x` (andi t8,t4,0xff) instead of
// reloading v from the stack, which means those two operations are one expression
// in the original. Fusing them (`v = (v |= bit) ^ x;`) reproduces that exactly, but
// then `arg0 <<= 1` (temps t5/t6 in the target, between the `or` and the `lbu x`)
// lands after the expression instead of inside it; forcing it inside with a comma
// operator makes IDO spill the `|=` result to a1 and truncate it eagerly. Best score
// 5989 (~6 instructions), differing only in the placement of the arg0 shift.
//
// u8 func_151F27E0(u16 arg0) {
//     u8 v;
//     u8 x;
//     s32 i;
//
//     v = 0;
//     for (i = 0; i < 0x10; i++) {
//         if (v & 0x10) {
//             x = 0x15;
//         } else {
//             x = 0;
//         }
//         v = v << 1;
//         v = (v |= (u8) ((arg0 & 0x400) ? 1 : 0)) ^ x;
//         arg0 = arg0 << 1;
//     }
//     return v & 0x1F;
// }
// NON-MATCHING at -g: reconstruction is algorithmically exact (LFSR, poly 0x15) and scores
// ~2045 (mostly object-bleed; the isolated func is ~2 instrs off). The only diff is a -g
// delay-slot scheduling detail: the target folds the `v <<= 1` store into the (arg0 & 0x400)
// branch's delay slot, but a standalone `v = v << 1;` statement stores it early + pads a nop.
// Not cleanly controllable from C. Algorithm:
//   u8 v = 0; for (i=0;i<0x10;i++) { x = (v & 0x10) ? 0x15 : 0; v <<= 1;
//     v = (v |= (arg0 & 0x400) ? 1 : 0) ^ x; arg0 <<= 1; } return v & 0x1F;
#pragma GLOBAL_ASM("asm/nonmatchings/libultra/audio/game_21FC90/func_151F27E0.s")

// __osContDataCrc: CRC-8 (poly 0x85) over 32 bytes + 1 flush pass. Algorithm is
// byte-exact; best score 2341 (see below). NON-MATCHING for the same reason as the
// sibling func_151F27E0: at -g IDO defers the `v <<= 1` store and the `v ^= x` store
// into following branch delay slots (and reuses the shift-result register in the
// i==0x20 arm) in a way not controllable from C. PERMUTER CANDIDATE.
//
// u8 func_151F2890(u8 *arg0) {
//     u8 v; u8 x; s32 i; s32 j;
//     v = 0;
//     for (i = 0; i < 0x21; i++) {
//         for (j = 7; j >= 0; j--) {
//             x = (v & 0x80) ? 0x85 : 0;
//             v = v << 1;
//             if (i == 0x20) { v = v & 0xFF; }
//             else { v |= (arg0[0] & (1 << j)) ? 1 : 0; }
//             v = v ^ x;
//         }
//         arg0++;
//     }
//     return v;
// }
#pragma GLOBAL_ASM("asm/nonmatchings/libultra/audio/game_21FC90/func_151F2890.s")

void func_151F2960(s32 arg0, s32 arg1) {
    if (D_800E0DFC == 0) {
        return;
    }
    D_800E0E04 = 4;
    if (D_800E0E2C == 0) {
      D_800E0E2C = 1;
        D_800E0E30 = allocate_memory(0x8000, 0xFF, 2, 1);
        if (D_800E0E30 == 0) {
            D_800E0E2C = 0;
            return;
        }
        D_800E0E20 = func_1502B5C8(0, 2, 0x17, 4);
        if (D_800E0E20 != 0) {
            func_100043B4(D_800E0E20, 0xFF);
        }
        D_800E0E24 = func_1502B5C8(0, 2, 0x17, 5);
        if (D_800E0E24 != 0) {
            func_100043B4(D_800E0E24, 0xFF);
        }
        D_800E0E28 = func_1502B5C8(0, 2, 0x17, 6);
        if (D_800E0E28 != 0) {
            func_100043B4(D_800E0E28, 0xFF);
        }
        if ((D_800E0E20 == 0) || (D_800E0E24 == 0) || (D_800E0E28 == 0)) {
            if (D_800E0E20 != 0) {
                func_10004074(D_800E0E20);
            }
            if (D_800E0E24 != 0) {
                func_10004074(D_800E0E24);
            }
            if (D_800E0E28 != 0) {
                func_10004074(D_800E0E28);
            }
            func_10004074(D_800E0E30);
            D_800E0E30 = 0;
            D_800E0E2C = 0;
            return;
        }
        func_151F3DE0();
    }
    D_800E0D80 = arg0;
    D_800E0DE0 = arg1;
    D_800E0DE4 = 0;
    D_800E0E10 = 0;
    D_800E0E18 = 5;
    D_800E0E04 = 5;
}

void func_151F2BA8(void) {
    u32 mask = osSetIntMask(1);
    D_800E0E04 = 3;
    osSetIntMask(mask);
}

void func_151F2BE8(void) {
    u32 mask = osSetIntMask(1);
    if (D_800E0E04 == 5) {
        D_800E0E04 = 6;
    } else {
        D_800E0E04 = 2;
    }
    osSetIntMask(mask);
}

void func_151F2C4C(void) {
    u32 mask = osSetIntMask(1);
    if (D_800E0E04 == 2) {
        D_800E0E18 = 5;
        D_800E0E04 = 7;
    } else if (D_800E0E04 == 6) {
        D_800E0E18 = 5;
        D_800E0E04 = 5;
    }
    osSetIntMask(mask);
}

s32 func_151F2CDC(void) {
    s32 ret = 0;
    u32 mask = osSetIntMask(1);

    if ((D_800E0E04 == 1) || (D_800E0E04 == 5) || (D_800E0E04 == 6) || (D_800E0E04 == 7) || (D_800E0E04 == 2)) {
        ret = D_800E0E04;
    }
    osSetIntMask(mask);
    return ret;
}

void func_151F2D6C(s32 arg0, s32 arg1) {
    u32 mask = osSetIntMask(1);
    if (arg0 < 0) {
        D_800E0E08 = 0;
    } else if (arg0 >= 0x8000) {
        D_800E0E08 = 0x7FFF;
    } else {
        D_800E0E08 = arg0;
    }
    D_800E0E10 = arg1;
    osSetIntMask(mask);
}

void func_151F2DFC(s32 arg0, s32 arg1) {
    if (arg0 >= 0x80) {
        arg0 = (u16)0x7F;
    } else {
        if (arg0 < 0) {
            arg0 = (u16)0;
        }
    }
    D_800E0E16 = arg0;
    if (arg1 != 0) {
        D_800E0E14 = (s16) D_800E0E16;
    }
}

void func_151F2E4C(s32 arg0, s32 arg1) {
    D_800E0DB2 = arg0;
    D_800E0DB0 = arg1;
    if (D_800E0DD8 == 0) {
        D_800E0DD8 = 2;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/libultra/audio/game_21FC90/func_151F2E88.s")

extern s16 _getVol(s16, s32, s16, u16);
extern s16 D_8002BC10[];
extern s16 D_8002BD0E[];
extern u8  D_800428C1;
extern u8  D_800428C2;

typedef struct {
    /* 0x00 */ char pad0[0xC];
    /* 0x0C */ s16 unkC;
    /* 0x0E */ s16 unkE;
    /* 0x10 */ s16 unk10;
    /* 0x12 */ s16 unk12;
    /* 0x14 */ char pad14[4];
    /* 0x18 */ u16 unk18;
    /* 0x1A */ s16 unk1A;
    /* 0x1C */ s16 unk1C;
    /* 0x1E */ u16 unk1E;
    /* 0x20 */ s16 unk20;
    /* 0x22 */ s16 unk22;
    /* 0x24 */ s16 unk24;
    /* 0x26 */ char pad26[2];
    /* 0x28 */ s32 unk28;
    /* 0x2C */ s32 unk2C;
    /* 0x30 */ char pad30[0x58];
    /* 0x88 */ s32 unk88;
    /* 0x8C */ char pad8C[4];
    /* 0x90 */ u32 unk90;
    /* 0x94 */ s16 unk94;
} Voice39E4;

void func_151F39E4(Voice39E4 *arg0) {
    if ((arg0->unkE != arg0->unk88) || (arg0->unkC != arg0->unk94)) {
        if (arg0->unk28 >= arg0->unk2C) {
            arg0->unk1C = (D_8002BC10[arg0->unkC] * arg0->unkE) >> 15;
            arg0->unk22 = (D_8002BD0E[-arg0->unkC] * arg0->unkE) >> 15;
            arg0->unk28 = arg0->unk2C;
            arg0->unk10 = arg0->unk1C;
            arg0->unk12 = arg0->unk22;
        } else {
            arg0->unk10 = _getVol(arg0->unk10, arg0->unk28, arg0->unk1A, arg0->unk18);
            arg0->unk12 = _getVol(arg0->unk12, arg0->unk28, arg0->unk20, arg0->unk1E);
        }
        if (arg0->unk10 == 0) {
            arg0->unk10 = 1;
        }
        if (arg0->unk12 == 0) {
            arg0->unk12 = 1;
        }
        arg0->unkE = arg0->unk88;
        if ((arg0->unkE == 0) && (arg0->unk90 != 0)) {
            func_151F2BA8();
        }
        if (arg0->unkC != arg0->unk94) {
            if (D_800428C2 != 0) {
                arg0->unkC = (arg0->unk94 >> 1) + 0x20;
            } else if (D_800428C1 != 0) {
                arg0->unkC = 0x40;
            } else {
                arg0->unkC = arg0->unk94;
            }
        }
        arg0->unk28 = 0;
        arg0->unk2C = ((arg0->unk90 + 0xB7) / 0xB8) * 0xB8;
        arg0->unk24 = 1;
    }
}

void func_151F3C1C(s32 arg0) {
    D_800E0E00 = arg0;
}

void func_151F3C34(s32 arg0) {
    D_800E0DFC = arg0;
}

s32 func_151F3C4C(s32 arg0, void *arg1, s32 arg2, s32 arg3) {
    s32 addr;
    ALDMAproc dmaproc;

    if (arg3 != -1) {
        D_800E0DE4 = arg3;
    }
    if (D_800E0DE4 + arg2 > D_800E0DE0) {
        arg2 = D_800E0DE0 - D_800E0DE4;
    }
    dmaproc = N_SYN_DMA(n_syn)(&addr);
    addr = dmaproc(D_800E0D80 + D_800E0DE4, arg2, 0);
    if (addr == 0) {
        return 0;
    }
    addr += 0x80000000;
    osInvalDCache((void *)addr, arg2);
    bcopy((void *)addr, arg1, arg2);
    D_800E0DE4 += arg2;
    return arg2;
}

void func_151F3D78(void) {
    void *state;
    ALDMAproc dmaproc;

    dmaproc = N_SYN_DMA(n_syn)(&state);
    dmaproc(D_800E0D80 + D_800E0DE4, 0x810, 0);
}
