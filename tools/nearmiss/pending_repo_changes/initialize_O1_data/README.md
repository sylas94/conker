# __osInitialize_common -- MATCHED (fastscore 0, whole TU masked .text identical), needs build changes

Found by wave 10B on 2026-10-08. `initialize.c` here replaces conker/src/libultra/os/initialize.c. It is the
verbatim SDK shape. It needs all three of these together:
1. Makefile: `$(BUILD_DIR)/$(SRC_DIR)/libultra/os/initialize.c.o: OPT_FLAGS := -O1`
2. The TU owns 0x20 bytes of .data at 0x2BD10 (D_8002BD10 u64 osClockRate = 62500000, D_8002BD18,
   D_8002BD1C = 0x3FFF01, D_8002BD20). Defining osClockRate in the TU is what makes IDO emit golden's
   single-`lui` 64-bit stores. 0x2BD10 is INSIDE the big `[0x290D0, data]` blob of init_data, so this
   needs `[0x2BD10, .data, libultra/os/initialize]` + `[0x2BD30, data]` and a splat re-run to split
   290D0.data.s (generated asm/data). That re-run is the risky part, so it was not done.
3. Add `D_8002BD14 = 0x8002BD14;` (asm 20A3A0, 21C540, 48FD0 still address it). variables.h wrongly
   declares D_8002BD10 as s64 (it is u64: golden uses __ull_div). This copy doesn't include variables.h.
