/* PARK 2026-10-08 (wave 10B): mism 18 (19 without the barrier block). Frame, slots and every instruction are
 * right; the residue is register allocation / load order of stack args arg1/arg2 against the unk58
 * OR-chain temps and the unk60..65 constants. Refuted: 120 OR-tree forms, all 720 unk6x store orders,
 * unk58 positions, 4 callee prototypes, barrier blocks, block-scoped s, u32 vs s32 unk58. Next: permuter on the tail. */
/* Particle descriptor passed to func_15130280 (0x70 bytes). */
typedef struct {
    s32 unk0;
    s32 unk4;
    s16 unk8;
    s16 unkA;
    s32 unkC;
    s32 unk10;
    u8 unk14;
    u8 unk15;
    u8 unk16;
    u8 unk17;
    u8 unk18;
    u8 unk19;
    u8 unk1A;
    u8 unk1B;
    u8 unk1C;
    u8 unk1D;
    s16 unk1E;
    s16 unk20; /* 255 / lifetime */
    s16 unk22;
    f32 unk24;
    f32 unk28;
    f32 unk2C;
    struct17 pos;
    struct17 unk3C;
    struct17 vel;
    f32 unk54;
    u32 unk58;
    s32 unk5C;
    u8 unk60;
    u8 unk61;
    s8 unk62;
    s8 unk63;
    s8 unk64;
    u8 unk65;
    u8 unk66;
    u8 pad67;
    s16 unk68;
    u8 pad6A[2];
    f32 unk6C;
} ParticleDesc; /* 0x70 */
extern void *func_15130280(void *, u8, s32, s32, u8, s32);

void func_150B5E34(f32 *arg0, u8 arg1, s32 arg2) {
    ParticleDesc s;

    s.unk1D = 0x2B;
    s.unk8 = 0x4403;
    s.unk0 = 0x200005;
    s.unk4 = 0x20000;
    s.unkA = func_150ADA20() % 7U + 4;
    s.unkC = 0;
    s.unk10 = 0;
    s.unk14 = 0xFF;
    s.unk15 = 0xFF;
    s.unk16 = 0xFF;
    s.unk17 = 0xFF;
    s.unk18 = 0xFF;
    s.unk19 = 0xFF;
    s.unk1A = 0xFF;
    s.unk1B = 0xFF;
    s.unk1C = 0xFF;
    s.unk28 = s.unk2C = func_150ADA68() * 500.0f + 500.0f;
    s.pos = *(struct17 *)arg0;
    s.unk1E = 3;
    s.unk20 = 0x55;
    s.unk22 = 1;
    s.unk3C.unk0 = 0.0f;
    s.unk3C.unk4 = 0.0f;
    s.unk3C.unk8 = 0.0f;
    s.vel.unk0 = 0.0f;
    s.vel.unk4 = 0.0f;
    s.vel.unk8 = 0.0f;
    s.unk54 = 0.0f;
    s.unk24 = 1.0f;
    s.unk58 = 0xC200 | (((func_150ADA20() & 1) ? 0x40 : 0) | (1 | ((func_150ADA20() & 1) ? 0x80 : 0)));
    s.unk60 = 6;
    s.unk61 = 6;
    s.unk62 = -1;
    s.unk63 = -1;
    s.unk64 = -1;
    s.unk65 = 4;
    {
        extern void *func_15130280(void *, u8, s32, s32, u8, s32);

        func_15130280(&s, 1, 0, 0, arg1, arg2);
    }
}
