#include <ultra64.h>
#include "functions.h"
#include "variables.h"


/* 12-byte slot record. The first word is a bitfield: golden reads it whole (`lw` + `srl 31`)
   for the guard and updates the top byte in place (`lbu`/`sb`) for each field write, which is
   exactly what these bitfield assignments produce. */
typedef struct Rec150A0264 {
    u32 unk0_b0 : 1;
    u32 unk0_b1 : 1;
    u32 unk0_b2 : 4;
    u32 unk0_b6 : 2;
    u32 unk0_rest : 24;
    u32 unk4;
    u32 unk8;
} Rec150A0264;

typedef struct Src150A0264 {
    char pad0[4];
    s32 unk4;
    s32 unk8;
} Src150A0264;

extern Rec150A0264 D_800D3010[];

/* NEAR MISS, mism=65 n=46/43 (THREE OVER). The shape is certainly
       for (i = 0; i < 10; i++) { D_800D3010[i].unk0_b0 = 0; .unk4 = 0; .unk8 = 0; }
   -- golden PEELS records 0 and 1 and then runs a 4-records-per-iteration unrolled loop
   from &D_800D3010[2] to &D_800D3010[10], which is what IDO does to this loop; we get the
   same shape but three instructions long. Try a pointer walk instead of the index, and
   check whether the peel wants the two records written out explicitly.
#pragma GLOBAL_ASM removed only when it reaches 0. */
#pragma GLOBAL_ASM("asm/nonmatchings/game_CD5A0/func_150A00F0.s")

/* NEAR MISS, mism=54 n=51/50 (ONE OVER). Per-frame tick over the same 10-record table:
       extern u16 D_80088510[];   extern u16 D_8008851C[];
       Rec150A0264 *r, *end;
       end = &D_800D3010[10];
       for (r = D_800D3010; r != end; r++) {
           if ((r->unk0_b0 != 0) && (r->unk0_b1 == 1)) {
               r->unk8 = r->unk8 + D_800BE9E4;
               if (r->unk8 >= D_80088510[r->unk0_b2]) {
                   r->unk8 = r->unk8 - D_80088510[r->unk0_b2];
                   r->unk4 = r->unk4 + 1;
                   if (D_8008851C[r->unk0_b2] != 0) {
                       r->unk4 = r->unk4 % D_8008851C[r->unk0_b2];
                   }
               }
           }
       }
   LADDER: 79 -> 76 (unk4/unk8 typed UNSIGNED: golden is `sltu` and `divu`; as s32 we emitted
   `slt` plus `div` AND its three-instruction signed-overflow guard) -> 57 (the increment and
   the modulo are TWO statements with an explicit `!= 0` guard -- golden's `sw t5,0x4(v1)` sits
   in the `beq` delay slot, so unk4 += 1 happens on BOTH paths) -> 54 (hoist the end pointer;
   `r != &D_800D3010[10]` in the condition recomputes base+120 every iteration).
   REFUTED: an `idx` local for r->unk0_b2 (117, worse); a separate `extern D_800D3088[]` as the
   end marker (89 -- IDO then cannot prove the loop runs once and adds an entry test).
   REMAINING +1: we emit `lui base / addiu +120` for the end pointer where golden folds it to
   `%hi/%lo(D_800D3010+120)` (rendered as D_800D3088). Get that fold and this should close. */
#pragma GLOBAL_ASM("asm/nonmatchings/game_CD5A0/func_150A019C.s")

s32 func_150A0264(s32 arg0, Src150A0264 *arg1) {
    Rec150A0264 *r = &D_800D3010[arg0];

    if (r->unk0_b0 != 0) {
        return 0;
    }
    r->unk0_b0 = 1;
    r->unk0_b1 = 0;
    r->unk0_b2 = arg1->unk4;
    r->unk4 = 0;
    return 1;
}

s32 func_150A02D0(s32 arg0, s32 arg1, Src150A0264 *arg2) {
    switch (arg1) {
    case 0:
        D_800D3010[arg0].unk0_b1 = 1;
        return 1;
    case 1:
        D_800D3010[arg0].unk0_b1 = 0;
        return 1;
    case 2:
        D_800D3010[arg0].unk4 = arg2->unk8;
        return 1;
    }
    return 0;
}

typedef struct {
    s32 unk0;
    s32 unk4;
    s32 unk8;
} D3014Struct;

extern D3014Struct D_800D3014[];

s32 func_150A0374(s32 arg0, s32 arg1, s32 arg2) {
    if (arg1 == 3) {
        return D_800D3014[arg0].unk0;
    }
    return 0;
}
