/* BLOCKED rodata: block 244CD0 shared (game_EEE70 + game_EF410). literal form (r2) = 0; extern form below = 3
   (D_800A0268 lwc1 scheduled after the -490.0f lui/mtc1 instead of before). */
extern f32 D_800A0268;
extern f32 D_800A026C;

void func_150C2424(u8 arg0) {
    func_1514C470(D_800A0268, -490.0f, -328.0f, D_800A0268, -490.0f, 328.0f,
                  (func_150ADA68() * 8.0f) + 8.0f, 1, 0, 0.0f, 0, arg0);
    func_1514C470(D_800A026C, -560.0f, -580.0f, 8117.0f, -560.0f, -580.0f,
                  (func_150ADA68() * 3.0f) + 4.0f, 3, 0, 0.0f, 0, arg0);
}

/* literal form, 0: */
void func_150C2424(u8 arg0) {
    func_1514C470(8500.0f, -490.0f, -328.0f, 8500.0f, -490.0f, 328.0f,
                  (func_150ADA68() * 8.0f) + 8.0f, 1, 0, 0.0f, 0, arg0);
    func_1514C470(8843.0f, -560.0f, -580.0f, 8117.0f, -560.0f, -580.0f,
                  (func_150ADA68() * 3.0f) + 4.0f, 3, 0, 0.0f, 0, arg0);
}
