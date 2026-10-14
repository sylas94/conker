# Campaign: rodata block 24E840 (game_1D92F0) -- 2 of 3 owners ready

Block 0x24E840 (D_800A9D80..D_800A9DE0, 25 floats) is referenced only by game_1D92F0:
- func_151AE984 -- MATCH with literals (file here). Needs prototype line `void func_151AE984(f32 *, f32, f32, f32, u8, u8);`.
- func_151AF388 -- MATCH with literals (file here). Needs prototype `void func_151AF388(f32 *, f32, f32, f32, u8);`.
- func_151AECA0 -- NOT DONE (372 insns, 21 calls, uses 9 of the floats). The blocker.
- already-C functions read D_800A9D80/84/88/98/9C/A0/A4 as externs -> switch to literals.

The literal is what makes the K load schedule above the param moves (an extern load can't pass the stack-home stores).
Use exact-bit spellings or the .rodata image differs: 0.10300001f, 0.60200006f, -1.0450001f, 0.13000001f, 1.7f, 0.126f,
-0.702f (full table: python decode of asm/data/24E840.rodata.s, shortest round-trip repr).
Then: yaml `[0x24E840, .rodata, game_1D92F0]` + conker.ld swap; check TU .rodata == block bytes.
Same recipe already shipped for block 24EE90 (game_1E2180, 2026-10-13).
