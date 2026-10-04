import sys
s=open('base2.c').read()
s=s.replace("""struct Obj15171CA0 {
    char pad0[0x16];
    s16 unk16;
    char pad18[0x26 - 0x18];
    s16 unk26;
    char pad28[0x36 - 0x28];
    s16 unk36;
    char pad38[0x46 - 0x38];
    s16 unk46;
    char pad48[0x50 - 0x48];
""","""struct Obj15171CA0 {
    char pad0[0x10];
    Vtx vtx[4];
""")
s=s.replace("""    ret->unk16 = 0;
    ret->unk26 = 0;
    ret->unk36 = 0;
    ret->unk46 = 0;""","""    ret->vtx[0].v.flag = 0;
    ret->vtx[1].v.flag = 0;
    ret->vtx[2].v.flag = 0;
    ret->vtx[3].v.flag = 0;""")
# move the Some15171F04 struct + D_8008CA4C decl above 1D4C
blk=s[s.index("struct Some15171F04 {"):s.index("s32 func_151725FC(")]
s=s.replace(blk,"")
s=s.replace('#pragma GLOBAL_ASM("asm/nonmatchings/game_19F150/func_15171D4C.s")\n', blk+open(sys.argv[1]).read())
open(sys.argv[2],'w',newline='\n').write(s)
