/* func_15040FCC near-miss, best honest score 2465 (asm-differ, object level).
 * Instruction sequence matches the target 1:1 (same unrolling, same
 * multu/mflo/addu/addiu/sll/sh order, s0=8, s1=14, t5=0xF800, t2=0xE1);
 * residual is a register-allocation permutation only:
 *   target: v0=column(arg0+i) v1=i a1=buf1 a2=buf2 a3=zbuf t0=j t1=D_800BE9C0 temp, arg0 stays in a0
 *   ours:   v0=buf1 v1=D_800BE9C0 temp a1=buf2 a2=zbuf a3=i t0=column
 * IDO fills its allocation pool [v0,v1,a1,a2,a3] in source first-assignment
 * order; no natural ordering reproduces the target's (column,i,buf1,buf2,zbuf).
 * Good decomp-permuter candidate.
 */
void func_15040FCC(s32 arg0) {
    u16 *buf1;
    u16 *buf2;
    u16 *zbuf;
    s32 i;
    s32 j;
    s32 idx;

    buf1 = (u16 *)D_8002AAE8[D_800BE9C0 == 0];
    buf2 = (u16 *)D_8002AAE8[D_800BE9C0];
    zbuf = (u16 *)D_800BE9C4;

    for (i = 0; i != 8; i++) {
        idx = (arg0 + i) + D_800BE620 * 225 + 200;
        buf1[idx] = 0xF800;
        buf2[idx] = 0xF800;
        zbuf[idx] = 0;
    }
    for (j = 1; j < 7; j++) {
        for (i = 0; i != 14; i += 7) {
            idx = (arg0 + i) + D_800BE620 * (j + 225) + 200;
            buf1[idx] = 0xF800;
            buf2[idx] = 0xF800;
            zbuf[idx] = 0;
        }
    }
    for (j = 1; j < 7; j++) {
        for (i = 1; i < 7; i++) {
            idx = (arg0 + i) + D_800BE620 * (j + 225) + 200;
            buf1[idx] = 0;
            buf2[idx] = 0;
            zbuf[idx] = 0;
        }
    }
    for (i = 0; i != 8; i++) {
        idx = (arg0 + i) + D_800BE620 * (j + 225) + 200;
        buf1[idx] = 0xF800;
        buf2[idx] = 0xF800;
        zbuf[idx] = 0;
    }
}
