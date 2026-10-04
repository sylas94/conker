/* near-miss 70: logic exact (3 nested scans). Residue: golden uses POINTER IVs (row t0 += 0x18, entry t3 += 2) off a
   preheader-loaded base and keeps only arg2 in s0; ours uses offset IVs and keeps all 3 u16 args in s0-s2.
   A 'tbl' local gives pointer IVs (u3, 73) but loads the base before the count guard. */
typedef struct {
    u16 unk0;
    u16 unk2;
    s32 unk4;
    u16 unk8[8];
} Struct1508ECC0;

s32 func_1508ECC0(u16 arg0, u16 arg1, u16 arg2) {
    u32 i;
    u32 j;
    u32 k;
    Struct1508ECC0 *e;

    for (i = 0; i < D_80087380; i++) {
        for (j = 0; j < ((Struct1508ECC0 *)D_800D23C0)[i].unk2; j++) {
            e = &((Struct1508ECC0 *)D_800D23C0)[i];
            if (e->unk8[j] == (u16)((arg0 << 12) + arg1)) {
                for (k = 0; k < e->unk2; k++) {
                    if (arg2 == (e->unk8[k] >> 12) && k != j) {
                        return e->unk8[k] & 0xFFF;
                    }
                }
                return -1;
            }
        }
    }
    return -1;
}
