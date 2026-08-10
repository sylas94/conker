/* func_15148BA4 near-miss: SCORE 100, instruction-for-instruction identical,
 * residual is 18 register-only ('r') diffs, coupled:
 *   entries=t2/const0x14=t1 (target) vs entries=t1/const0x14=t2 (mine)
 *   post-loop entry ptr v1 vs v0; CSE'd arg0->unk2D  v0 vs a1
 * decomp-permuter candidate.
 *
 * Requires in game_175250.c (added to the two existing local typedefs):
 *   struct Struct15148AF4_data  += { u8 pad19[10]; u8 unk23; u8 unk24; } after unk18
 *   struct Struct15148AF4_arg0  : pad2F[0x65] -> pad2F[0x31]; f32 unk60; u8 unk64;
 *                                 u8 pad65[0x18]; u8 unk7D; u8 pad7E[0x16];
 *   struct Struct15148BA4_vec { f32 unk0; f32 unk4; f32 unk8; };
 *   extern s32 (*D_8008A430[])(struct Struct15148AF4_arg0 *, f32, f32, f32, f32, void *);
 *   extern s32 (*D_8008A450[])(struct Struct15148AF4_arg0 *, f32, f32, f32, f32, void *);
 *   s32 func_15046C80(f32 *, s32, f32, void *);
 *
 * Local DECLARATION ORDER below is load-bearing: it puts pos@sp+0x34, old@sp+0x40
 * and data's spill slot @sp+0x50, matching the target frame exactly.
 */
s32 func_15148BA4(struct Struct15148AF4_arg0 *arg0) {
    s32 idx;
    struct Struct15148AF4_data *data;
    struct Struct15148AF4_entry *entry;
    struct Struct15148BA4_vec old;
    struct Struct15148BA4_vec pos;
    struct Struct15148AF4_entry *entries;

    data = arg0->unk98;
    entries = arg0->unk94;
    idx = arg0->unk2E;
    if (data->unk18 & 7) {
        old = *(struct Struct15148BA4_vec *)((u8 *)entries + (arg0->unk2D * 0x14));
    }
    do {
        idx -= 1;
        if (idx < 0) {
            idx = arg0->unk25 - 1;
        }
        entry = (struct Struct15148AF4_entry *)((u8 *)entries + (idx * 0x14));
        entry->unkC = entry->unkC - (data->unk10 * D_800BE9A4);
        entry->unk0 = entry->unk0 + (data->unk4 * D_800BE9A4);
        entry->unk4 = entry->unk4 + (entry->unkC * D_800BE9A4);
        entry->unk8 = entry->unk8 + (data->unkC * D_800BE9A4);
    } while (idx != arg0->unk2D);

    if (data->unk18 & 0x17) {
        if (entries[arg0->unk2D].unk4 < old.unk4) {
            pos.unk0 = entries[arg0->unk2D].unk0;
            pos.unk4 = old.unk4;
            pos.unk8 = entries[arg0->unk2D].unk8;
            if (func_15046C80(&pos.unk0, 0, entries[arg0->unk2D].unk4, &arg0->unk60) != 0) {
                if (arg0->unk7D == 3) {
                    if (data->unk24 != 0) {
                        if (D_8008A450[data->unk24](arg0, old.unk0, old.unk4, old.unk8, arg0->unk60,
                                                    &arg0->unk64) == 0) {
                            return 0;
                        }
                    }
                } else {
                    if (data->unk23 != 0) {
                        if (D_8008A430[data->unk23](arg0, old.unk0, old.unk4, old.unk8, arg0->unk60,
                                                    &arg0->unk64) == 0) {
                            return 0;
                        }
                    }
                }
            }
        }
    }
    return 1;
}
