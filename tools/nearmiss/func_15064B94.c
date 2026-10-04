/* tools/nearmiss/func_15064B94.c -- game_90840, 946 instructions, frame 0x38
 *
 * STATUS (2026-10-03): .text BYTE-IDENTICAL -- mism 0, n=946/946, structdiff zero rows, all
 * 37 raw-word diffs vs expected/ are R_MIPS_LO16 .rodata addends. NOT SHIPPABLE YET: BLOCKED ON
 * RODATA. The 38 float constants must be written as LITERALS (extern f32 D_800997E8.. spelling
 * scores 52: IDO treats an extern load as aliasable memory and won't hoist it above the
 * arg0->unkAA byte stores). Literals land in this TU's live-C .rodata, which is /DISCARD/ed.
 * Our .rodata = exactly D_800997E8..D_8009987C (0x98 B) in order. The block
 * asm/data/23E160.rodata.s also holds D_800997E0/E4 (func_150642AC, asm) before it and
 * jtbl_80099880 (func_15065A5C, asm, 19 KB) after it, so it ships only with a whole-TU rodata
 * migration (yaml `[0x23E160, .rodata, game_90840]`) once every rodata-owning sibling in the
 * TU is C -- or via a mid-block split if IDO's section alignment allows placing it at 0x...E8.
 * Splice the body below over the pragma at that point and ROM-gate.
 * Function: player animation selector (returns anim id, calls func_1505E650 with speed/blend).
 */
typedef struct {
    u8  pad0[0x8];
    s16 unk8;
    u8  padA[0x4];
    u16 unkE;
    u8  pad10[0x7];
    u8  unk17;
    u8  pad18[0x2];
    u8  unk1A;
    u8  pad1B[0x8];
    s8  unk23;
    u8  pad24[0xE];
    u16 unk32;
    u8  pad34[0x8];
    u8  unk3C;
    u8  pad3D[0x9];
    s16 unk46;
    u8  pad48[0x6];
    u8  unk4E;
    u8  pad4F;
    s8  unk50;
    u8  pad51[0x27];
    u8  unk78;
    u8  pad79[0x139];
    u8  unk1B2;
} func_15064B94_s;

extern u8 D_800B85A4[];

s32 func_15064B94(struct127 *arg0, f32 arg1, f32 arg2, s32 arg3, f32 arg4) {
    s32 anim;
    f32 sp30;
    f32 speed;
    func_15064B94_s *S;

    anim = 0;
    sp30 = 4.0f;
    speed = 1.0f;
    S = (func_15064B94_s *)arg0->unk31C;
    if (S->unk46 > 0) {
        anim = 0x4C;
        speed = arg1 / 24.0f;
    } else if (S->unk4E == 2) {
        anim = 5;
        if (S->unk50 > 0) {
            anim = 0x54;
        }
        sp30 = 2.0f;
    } else if (arg0->unk13C >= 100) {
        if (arg0->xz_velocity < 1.0f) {
            anim = func_1504C078();
        } else {
            switch (D_800B85A4[D_800D154C->unk13C * 0x32C]) {
            case 0x8C:
                arg0->unkAA = 0x5A;
                speed = arg1 / 6.0f + 0.4f;
                anim = 0x1A6;
                if (14.0f < arg0->xz_velocity) {
                    anim = 0x1A7;
                    speed = arg1 / 26.0f + 0.5f;
                }
                break;
            case 0x57:
                arg0->unkAA = 0x5A;
                speed = arg1 / 6.0f + 0.4f;
                anim = 0x116;
                if (14.0f < arg0->xz_velocity) {
                    anim = 0x117;
                    speed = arg1 / 26.0f + 0.5f;
                }
                break;
            case 0xA8:
            case 0xA9:
                if (14.0f < arg0->xz_velocity) {
                    anim = 0x1B1;
                    speed = arg1 / 22.0f + 0.4f;
                } else {
                    anim = 0x1B0;
                    speed = arg1 * 0.0625f + 0.6f;
                }
                break;
            case 0x13:
                anim = 0x14C;
                speed = arg1 / 6.0f;
                break;
            case 0x89:
                anim = 0x1FB;
                speed = arg1 / 6.0f;
                break;
            default:
                if (14.0f < arg0->xz_velocity) {
                    anim = 0x2E4;
                    speed = arg1 * 0.0625f + 0.5f;
                } else {
                    anim = 0xD7;
                    speed = arg1 / 6.0f + 0.4f;
                }
                break;
            }
        }
    } else if ((arg3 != 0) && (S->unk78 == 0)) {
        anim = arg3;
        speed = arg1 / 15.0f + 0.6f;
    } else if ((2.6f < arg0->unk44) && (S->unk32 & 1)) {
        arg0->unkAA = 0x28;
        sp30 = 5.0f;
        speed = arg0->unk44 / 15.0f + 0.5f;
        anim = func_1504C0B8();
    } else if (S->unk78 == 0x16) {
        if (1.0f <= arg0->unk44) {
            anim = (S->unk1B2 != 0) ? 0x2C6 : 0xE8;
            arg0->unkAA = 0x1E;
            speed = arg1 * 0.0625f + 0.6f;
        } else {
            anim = func_1504C078();
        }
    } else if (S->unk78 == 9) {
        if (1.0f <= arg0->unk44) {
            if (D_800BE616 == 0) {
                arg0->unkAA = 0x37;
            }
            anim = 0x7E;
            if (D_800BE616 == 0) {
                speed = arg1 * 0.0625f + 0.6f;
            } else if (20.0f <= arg0->unk44) {
                anim = 0x22C;
                speed = arg1 / 22.0f + 0.4f;
            }
        } else {
            anim = func_1504C078();
        }
    } else if (S->unk78 == 0x38) {
        if (1.0f <= arg0->unk44) {
            anim = 0x1E1;
            if (20.0f <= arg0->unk44) {
                anim = 0x1E2;
                speed = arg1 / 22.0f + 0.4f;
            }
        } else {
            anim = func_1504C078();
        }
    } else if (S->unk78 == 0x39) {
        if (arg0->unk84.uh != 0x1EB) {
            if (1.0f <= arg0->unk44) {
                anim = 0x1EC;
                if (20.0f <= arg0->unk44) {
                    anim = 0x1ED;
                    speed = arg1 / 22.0f + 0.4f;
                }
            } else {
                anim = func_1504C078();
            }
        } else {
            anim = 999;
        }
    } else if (S->unk78 == 0x37) {
        if (arg0->unk84.uh != 0x1F4) {
            if (1.0f <= arg0->unk44) {
                anim = 0x1F5;
                if (20.0f <= arg0->unk44) {
                    anim = 0x1F6;
                    speed = arg1 / 22.0f + 0.4f;
                }
            } else {
                anim = func_1504C078();
            }
        } else {
            anim = 999;
        }
    } else if (S->unk78 == 0x3B) {
        if ((arg0->unk84.uh != 0x222) && (arg0->unk84.uh != 0x236)) {
            if ((1.0f <= arg0->unk44) || (S->unk23 > 0)) {
                arg0->unkAA = 0x37;
                anim = 0x223;
                if (20.0f <= arg0->unk44) {
                    anim = 0x224;
                    speed = arg1 / 22.0f + 0.4f;
                }
            } else {
                anim = func_1504C078();
            }
        } else {
            anim = 999;
        }
    } else if ((S->unk78 == 0x12) || (S->unk78 == 0x18) || (S->unk78 == 0x41)) {
        if (1.0f <= arg0->unk44) {
            arg0->unkAA = 0x50;
            speed = arg1 * 0.0625f + 0.6f;
            anim = 0xEC;
            if (20.0f <= arg0->unk44) {
                anim = 0xF8;
                speed = arg1 / 22.0f + 0.4f;
            }
        } else {
            anim = func_1504C078();
        }
    } else if (S->unk78 == 0x24) {
        if (1.0f <= arg0->unk44) {
            arg0->unkAA = 0x50;
            speed = arg1 * 0.0625f + 0.6f;
            anim = 0x158;
            if (20.0f <= arg0->unk44) {
                anim = 0x159;
                speed = arg1 / 22.0f + 0.4f;
            }
        } else {
            anim = func_1504C078();
        }
    } else if (S->unk78 == 0x22) {
        if (1.0f <= arg0->unk44) {
            arg0->unkAA = 0x50;
            speed = arg1 * 0.0625f + 0.6f;
            anim = 0x15B;
            if (20.0f <= arg0->unk44) {
                anim = 0x15C;
                speed = arg1 / 22.0f + 0.4f;
            }
        } else {
            anim = func_1504C078();
        }
    } else if (S->unk78 == 0x21) {
        if (1.0f <= arg0->unk44) {
            arg0->unkAA = 0x6E;
            speed = arg1 * 0.0625f + 0.6f;
            anim = 0x123;
            if (15.0f <= arg0->unk44) {
                anim = 0x124;
                speed = arg1 / 27.0f;
            }
        } else {
            anim = func_1504C078();
        }
    } else if (S->unk78 == 0x26) {
        if (1.0f <= arg0->unk44) {
            arg0->unkAA = 0x50;
            speed = arg1 * 0.0625f + 0.6f;
            anim = 0x178;
            if (20.0f <= arg0->unk44) {
                anim = 0x179;
                speed = arg1 / 22.0f + 0.4f;
            }
        } else {
            anim = func_1504C078();
        }
    } else if (S->unk78 == 0x3A) {
        if (1.0f <= arg0->unk44) {
            arg0->unkAA = 0x50;
            speed = arg1 * 0.0625f + 0.6f;
            anim = 0x1FB;
        } else {
            anim = func_1504C078();
        }
    } else if (S->unk78 == 0x25) {
        if (1.0f <= arg0->unk44) {
            arg0->unkAA = 0x50;
            speed = arg1 * 0.0625f + 0.6f;
            anim = 0xD7;
            if (20.0f <= arg0->unk44) {
                speed = arg1 / 22.0f + 0.4f;
            }
        } else {
            anim = func_1504C078();
        }
    } else if ((S->unk78 == 0x2D) || (S->unk78 == 0x2E)) {
        if (1.0f <= arg0->unk44) {
            speed = arg1 * 0.0625f + 0.6f;
            anim = 0x1B0;
            if (20.0f <= arg0->unk44) {
                anim = 0x1B1;
                speed = arg1 / 22.0f + 0.4f;
            }
        } else {
            anim = func_1504C078();
        }
    } else if (S->unk78 == 0x23) {
        if (1.0f <= arg0->unk44) {
            arg0->unkAA = 0x50;
            speed = arg1 * 0.0625f + 0.6f;
            anim = 0x161;
            if (20.0f <= arg0->unk44) {
                anim = 0x162;
                speed = arg1 / 22.0f + 0.4f;
            }
        } else {
            anim = func_1504C078();
        }
    } else if (S->unk78 == 0x15) {
        if (1.0f <= arg0->unk44) {
            arg0->unkAA = 0x50;
            speed = arg1 * 0.0625f + 0.6f;
            anim = 0xED;
            if (20.0f <= arg0->unk44) {
                speed = arg1 / 22.0f + 0.4f;
            }
        } else {
            anim = func_1504C078();
        }
    } else if ((S->unk78 == 0x19) || (S->unk78 == 0x40)) {
        if (1.0f <= arg0->xz_velocity) {
            sp30 = 8.0f;
            speed = arg1 * 0.125f + 0.3f;
            anim = 0x112;
            if (18.0f <= arg0->xz_velocity) {
                anim = 0x111;
                speed = arg1 / 20.0f + 0.3f;
            }
        } else {
            anim = func_1504C078();
        }
    } else if ((S->unk1A != 0) && (1.0f < arg2)) {
        arg0->unkAA = 0x28;
        anim = 0x6D;
        speed = arg1 / 6.5f + 0.3f;
        sp30 = 8.0f;
    } else if (S->unk8 > 0) {
        if (arg2 < 1.0f) {
            anim = func_1504C078();
        } else {
            speed = arg1 / 6.0f + 0.3f;
            anim = S->unkE;
            sp30 = 16.0f;
        }
    } else if (S->unk17 != 0) {
        sp30 = 5.0f;
        if (*(u16 *)D_800CC284 & 0x2000) {
            if (arg0->unk84.uh != 0x283) {
                arg0->xz_velocity *= 0.2f;
                D_800D1580 = 0xFF010604;
                func_1506E5FC();
            }
            arg0->disable_run = 3;
            arg0->disable_jump = 3;
            anim = 0x283;
        } else {
            if (arg0->unk84.uh == 0x283) {
                D_800D1580 = 0xFF010604;
                func_1506E5FC();
            }
            if ((1.0f <= arg0->unk44) && (arg0->disable_run == 0)) {
                arg0->unkAA = 0x2D;
                speed = arg0->xz_velocity / 9.0f;
                anim = 0x4E;
            } else {
                anim = func_1504C078();
            }
        }
    } else if (S->unk32 & 2) {
        if (1.0f <= arg0->unk44) {
            S->unk3C = 0x1C;
            arg0->unkAA = 0xF;
            anim = 100;
            speed = arg4 / 5.0f + 0.3f;
            sp30 = 8.0f;
            if (func_150ADA20() % 1000U >= 988) {
                anim = (func_150ADA20() & 1) + 0x65;
                speed = 0.65f;
                arg0->disable_run = 0xFF;
                arg0->unk83 = 0xFF;
            }
        }
    }

    if ((anim != 0) && (anim != 999)) {
        func_1505E650(arg0, anim, speed, sp30, 0.0f, 0.0f, 0);
    }
    return anim;
}
