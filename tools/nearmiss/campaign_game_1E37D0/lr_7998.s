.late_rodata
glabel D_800AA484
    .float 1198

.text
glabel func_151B7998
    /* 1E4E48 151B7998 27BDFFB8 */  addiu      $sp, $sp, -0x48
    /* 1E4E4C 151B799C F7BE0030 */  sdc1       $f30, 0x30($sp)
    /* 1E4E50 151B79A0 F7BC0028 */  sdc1       $f28, 0x28($sp)
    /* 1E4E54 151B79A4 F7BA0020 */  sdc1       $f26, 0x20($sp)
    /* 1E4E58 151B79A8 F7B80018 */  sdc1       $f24, 0x18($sp)
    /* 1E4E5C 151B79AC F7B60010 */  sdc1       $f22, 0x10($sp)
    /* 1E4E60 151B79B0 F7B40008 */  sdc1       $f20, 0x8($sp)
    /* 1E4E64 151B79B4 8083002C */  lb         $v1, 0x2C($a0)
    /* 1E4E68 151B79B8 8C820094 */  lw         $v0, 0x94($a0)
    /* 1E4E6C 151B79BC 28610002 */  slti       $at, $v1, 0x2
    /* 1E4E70 151B79C0 5420005E */  bnel       $at, $zero, .L151B7B3C
    /* 1E4E74 151B79C4 28610002 */   slti      $at, $v1, 0x2
    /* 1E4E78 151B79C8 8085002E */  lb         $a1, 0x2E($a0)
    /* 1E4E7C 151B79CC 4480C000 */  mtc1       $zero, $f24
    /* 1E4E80 151B79D0 3C013F80 */  lui        $at, (0x3F800000 >> 16)
    /* 1E4E84 151B79D4 24A5FFFF */  addiu      $a1, $a1, -0x1
    /* 1E4E88 151B79D8 04A10003 */  bgez       $a1, .L151B79E8
    /* 1E4E8C 151B79DC 24080014 */   addiu     $t0, $zero, 0x14
    /* 1E4E90 151B79E0 90850025 */  lbu        $a1, 0x25($a0)
    /* 1E4E94 151B79E4 24A5FFFF */  addiu      $a1, $a1, -0x1
  .L151B79E8:
    /* 1E4E98 151B79E8 8086002D */  lb         $a2, 0x2D($a0)
    /* 1E4E9C 151B79EC 50A60046 */  beql       $a1, $a2, .L151B7B08
    /* 1E4EA0 151B79F0 4480E000 */   mtc1      $zero, $f28
    /* 1E4EA4 151B79F4 4481F000 */  mtc1       $at, $f30
    /* 1E4EA8 151B79F8 3C01800B */  lui        $at, %hi(D_800AA484)
    /* 1E4EAC 151B79FC 4480E000 */  mtc1       $zero, $f28
    /* 1E4EB0 151B7A00 C43AA484 */  lwc1       $f26, %lo(D_800AA484)($at)
    /* 1E4EB4 151B7A04 00A01825 */  or         $v1, $a1, $zero
  .L151B7A08:
    /* 1E4EB8 151B7A08 24A5FFFF */  addiu      $a1, $a1, -0x1
    /* 1E4EBC 151B7A0C 04A10003 */  bgez       $a1, .L151B7A1C
    /* 1E4EC0 151B7A10 00000000 */   nop
    /* 1E4EC4 151B7A14 90850025 */  lbu        $a1, 0x25($a0)
    /* 1E4EC8 151B7A18 24A5FFFF */  addiu      $a1, $a1, -0x1
  .L151B7A1C:
    /* 1E4ECC 151B7A1C 00680019 */  multu      $v1, $t0
    /* 1E4ED0 151B7A20 00007012 */  mflo       $t6
    /* 1E4ED4 151B7A24 01C23821 */  addu       $a3, $t6, $v0
    /* 1E4ED8 151B7A28 C4F0000C */  lwc1       $f16, 0xC($a3)
    /* 1E4EDC 151B7A2C 4610C600 */  add.s      $f24, $f24, $f16
    /* 1E4EE0 151B7A30 4618D03C */  c.lt.s     $f26, $f24
    /* 1E4EE4 151B7A34 00000000 */  nop
    /* 1E4EE8 151B7A38 4500002F */  bc1f       .L151B7AF8
    /* 1E4EEC 151B7A3C 00000000 */   nop
    /* 1E4EF0 151B7A40 4610E032 */  c.eq.s     $f28, $f16
    /* 1E4EF4 151B7A44 00000000 */  nop
    /* 1E4EF8 151B7A48 4501001D */  bc1t       .L151B7AC0
    /* 1E4EFC 151B7A4C 00000000 */   nop
    /* 1E4F00 151B7A50 461AC101 */  sub.s      $f4, $f24, $f26
    /* 1E4F04 151B7A54 00A80019 */  multu      $a1, $t0
    /* 1E4F08 151B7A58 C4E60000 */  lwc1       $f6, 0x0($a3)
    /* 1E4F0C 151B7A5C C4E80004 */  lwc1       $f8, 0x4($a3)
    /* 1E4F10 151B7A60 46102383 */  div.s      $f14, $f4, $f16
    /* 1E4F14 151B7A64 C4EA0008 */  lwc1       $f10, 0x8($a3)
    /* 1E4F18 151B7A68 00007812 */  mflo       $t7
    /* 1E4F1C 151B7A6C 01E21821 */  addu       $v1, $t7, $v0
    /* 1E4F20 151B7A70 C4600000 */  lwc1       $f0, 0x0($v1)
    /* 1E4F24 151B7A74 C4620004 */  lwc1       $f2, 0x4($v1)
    /* 1E4F28 151B7A78 C46C0008 */  lwc1       $f12, 0x8($v1)
    /* 1E4F2C 151B7A7C 46060481 */  sub.s      $f18, $f0, $f6
    /* 1E4F30 151B7A80 46081501 */  sub.s      $f20, $f2, $f8
    /* 1E4F34 151B7A84 460E9102 */  mul.s      $f4, $f18, $f14
    /* 1E4F38 151B7A88 460A6581 */  sub.s      $f22, $f12, $f10
    /* 1E4F3C 151B7A8C 460EA202 */  mul.s      $f8, $f20, $f14
    /* 1E4F40 151B7A90 46040181 */  sub.s      $f6, $f0, $f4
    /* 1E4F44 151B7A94 460EB102 */  mul.s      $f4, $f22, $f14
    /* 1E4F48 151B7A98 46081281 */  sub.s      $f10, $f2, $f8
    /* 1E4F4C 151B7A9C E4660000 */  swc1       $f6, 0x0($v1)
    /* 1E4F50 151B7AA0 E46A0004 */  swc1       $f10, 0x4($v1)
    /* 1E4F54 151B7AA4 46046181 */  sub.s      $f6, $f12, $f4
    /* 1E4F58 151B7AA8 460EF281 */  sub.s      $f10, $f30, $f14
    /* 1E4F5C 151B7AAC E4660008 */  swc1       $f6, 0x8($v1)
    /* 1E4F60 151B7AB0 C4E8000C */  lwc1       $f8, 0xC($a3)
    /* 1E4F64 151B7AB4 460A4102 */  mul.s      $f4, $f8, $f10
    /* 1E4F68 151B7AB8 E4E4000C */  swc1       $f4, 0xC($a3)
    /* 1E4F6C 151B7ABC 8086002D */  lb         $a2, 0x2D($a0)
  .L151B7AC0:
    /* 1E4F70 151B7AC0 10A6000D */  beq        $a1, $a2, .L151B7AF8
    /* 1E4F74 151B7AC4 4600D606 */   mov.s     $f24, $f26
  .L151B7AC8:
    /* 1E4F78 151B7AC8 24D80001 */  addiu      $t8, $a2, 0x1
    /* 1E4F7C 151B7ACC A098002D */  sb         $t8, 0x2D($a0)
    /* 1E4F80 151B7AD0 8086002D */  lb         $a2, 0x2D($a0)
    /* 1E4F84 151B7AD4 90990025 */  lbu        $t9, 0x25($a0)
    /* 1E4F88 151B7AD8 57260004 */  bnel       $t9, $a2, .L151B7AEC
    /* 1E4F8C 151B7ADC 8089002C */   lb        $t1, 0x2C($a0)
    /* 1E4F90 151B7AE0 A080002D */  sb         $zero, 0x2D($a0)
    /* 1E4F94 151B7AE4 8086002D */  lb         $a2, 0x2D($a0)
    /* 1E4F98 151B7AE8 8089002C */  lb         $t1, 0x2C($a0)
  .L151B7AEC:
    /* 1E4F9C 151B7AEC 252AFFFF */  addiu      $t2, $t1, -0x1
    /* 1E4FA0 151B7AF0 14A6FFF5 */  bne        $a1, $a2, .L151B7AC8
    /* 1E4FA4 151B7AF4 A08A002C */   sb        $t2, 0x2C($a0)
  .L151B7AF8:
    /* 1E4FA8 151B7AF8 54A6FFC3 */  bnel       $a1, $a2, .L151B7A08
    /* 1E4FAC 151B7AFC 00A01825 */   or        $v1, $a1, $zero
    /* 1E4FB0 151B7B00 8083002C */  lb         $v1, 0x2C($a0)
    /* 1E4FB4 151B7B04 4480E000 */  mtc1       $zero, $f28
  .L151B7B08:
    /* 1E4FB8 151B7B08 3C013F80 */  lui        $at, (0x3F800000 >> 16)
    /* 1E4FBC 151B7B0C 4481F000 */  mtc1       $at, $f30
    /* 1E4FC0 151B7B10 461CC032 */  c.eq.s     $f24, $f28
    /* 1E4FC4 151B7B14 00000000 */  nop
    /* 1E4FC8 151B7B18 45030004 */  bc1tl      .L151B7B2C
    /* 1E4FCC 151B7B1C 44800000 */   mtc1      $zero, $f0
    /* 1E4FD0 151B7B20 10000003 */  b          .L151B7B30
    /* 1E4FD4 151B7B24 4618F003 */   div.s     $f0, $f30, $f24
    /* 1E4FD8 151B7B28 44800000 */  mtc1       $zero, $f0
  .L151B7B2C:
    /* 1E4FDC 151B7B2C 00000000 */  nop
  .L151B7B30:
    /* 1E4FE0 151B7B30 E7A0003C */  swc1       $f0, 0x3C($sp)
    /* 1E4FE4 151B7B34 E7B80040 */  swc1       $f24, 0x40($sp)
    /* 1E4FE8 151B7B38 28610002 */  slti       $at, $v1, 0x2
  .L151B7B3C:
    /* 1E4FEC 151B7B3C 24080014 */  addiu      $t0, $zero, 0x14
    /* 1E4FF0 151B7B40 C7A0003C */  lwc1       $f0, 0x3C($sp)
    /* 1E4FF4 151B7B44 14200033 */  bnez       $at, .L151B7C14
    /* 1E4FF8 151B7B48 C7B80040 */   lwc1      $f24, 0x40($sp)
    /* 1E4FFC 151B7B4C 3C01437F */  lui        $at, (0x437F0000 >> 16)
    /* 1E5000 151B7B50 44813000 */  mtc1       $at, $f6
    /* 1E5004 151B7B54 8083002E */  lb         $v1, 0x2E($a0)
    /* 1E5008 151B7B58 4600C086 */  mov.s      $f2, $f24
    /* 1E500C 151B7B5C 46003302 */  mul.s      $f12, $f6, $f0
    /* 1E5010 151B7B60 00000000 */  nop
    /* 1E5014 151B7B64 2463FFFF */  addiu      $v1, $v1, -0x1
  .L151B7B68:
    /* 1E5018 151B7B68 460C1202 */  mul.s      $f8, $f2, $f12
    /* 1E501C 151B7B6C 04610003 */  bgez       $v1, .L151B7B7C
    /* 1E5020 151B7B70 240D0001 */   addiu     $t5, $zero, 0x1
    /* 1E5024 151B7B74 90830025 */  lbu        $v1, 0x25($a0)
    /* 1E5028 151B7B78 2463FFFF */  addiu      $v1, $v1, -0x1
  .L151B7B7C:
    /* 1E502C 151B7B7C 444CF800 */  cfc1       $t4, $31
    /* 1E5030 151B7B80 00680019 */  multu      $v1, $t0
    /* 1E5034 151B7B84 44CDF800 */  ctc1       $t5, $31
    /* 1E5038 151B7B88 3C014F00 */  lui        $at, (0x4F000000 >> 16)
    /* 1E503C 151B7B8C 460042A4 */  cvt.w.s    $f10, $f8
    /* 1E5040 151B7B90 444DF800 */  cfc1       $t5, $31
    /* 1E5044 151B7B94 00005812 */  mflo       $t3
    /* 1E5048 151B7B98 31AD0078 */  andi       $t5, $t5, 0x78
    /* 1E504C 151B7B9C 11A00012 */  beqz       $t5, .L151B7BE8
    /* 1E5050 151B7BA0 01622821 */   addu      $a1, $t3, $v0
    /* 1E5054 151B7BA4 44815000 */  mtc1       $at, $f10
    /* 1E5058 151B7BA8 240D0001 */  addiu      $t5, $zero, 0x1
    /* 1E505C 151B7BAC 460A4281 */  sub.s      $f10, $f8, $f10
    /* 1E5060 151B7BB0 44CDF800 */  ctc1       $t5, $31
    /* 1E5064 151B7BB4 00000000 */  nop
    /* 1E5068 151B7BB8 460052A4 */  cvt.w.s    $f10, $f10
    /* 1E506C 151B7BBC 444DF800 */  cfc1       $t5, $31
    /* 1E5070 151B7BC0 00000000 */  nop
    /* 1E5074 151B7BC4 31AD0078 */  andi       $t5, $t5, 0x78
    /* 1E5078 151B7BC8 15A00005 */  bnez       $t5, .L151B7BE0
    /* 1E507C 151B7BCC 00000000 */   nop
    /* 1E5080 151B7BD0 440D5000 */  mfc1       $t5, $f10
    /* 1E5084 151B7BD4 3C018000 */  lui        $at, (0x80000000 >> 16)
    /* 1E5088 151B7BD8 10000007 */  b          .L151B7BF8
    /* 1E508C 151B7BDC 01A16825 */   or        $t5, $t5, $at
  .L151B7BE0:
    /* 1E5090 151B7BE0 10000005 */  b          .L151B7BF8
    /* 1E5094 151B7BE4 240DFFFF */   addiu     $t5, $zero, -0x1
  .L151B7BE8:
    /* 1E5098 151B7BE8 440D5000 */  mfc1       $t5, $f10
    /* 1E509C 151B7BEC 00000000 */  nop
    /* 1E50A0 151B7BF0 05A0FFFB */  bltz       $t5, .L151B7BE0
    /* 1E50A4 151B7BF4 00000000 */   nop
  .L151B7BF8:
    /* 1E50A8 151B7BF8 44CCF800 */  ctc1       $t4, $31
    /* 1E50AC 151B7BFC C4A4000C */  lwc1       $f4, 0xC($a1)
    /* 1E50B0 151B7C00 A0AD0010 */  sb         $t5, 0x10($a1)
    /* 1E50B4 151B7C04 46041081 */  sub.s      $f2, $f2, $f4
    /* 1E50B8 151B7C08 808E002D */  lb         $t6, 0x2D($a0)
    /* 1E50BC 151B7C0C 546EFFD6 */  bnel       $v1, $t6, .L151B7B68
    /* 1E50C0 151B7C10 2463FFFF */   addiu     $v1, $v1, -0x1
  .L151B7C14:
    /* 1E50C4 151B7C14 24020001 */  addiu      $v0, $zero, 0x1
    /* 1E50C8 151B7C18 D7B40008 */  ldc1       $f20, 0x8($sp)
    /* 1E50CC 151B7C1C D7B60010 */  ldc1       $f22, 0x10($sp)
    /* 1E50D0 151B7C20 D7B80018 */  ldc1       $f24, 0x18($sp)
    /* 1E50D4 151B7C24 D7BA0020 */  ldc1       $f26, 0x20($sp)
    /* 1E50D8 151B7C28 D7BC0028 */  ldc1       $f28, 0x28($sp)
    /* 1E50DC 151B7C2C D7BE0030 */  ldc1       $f30, 0x30($sp)
    /* 1E50E0 151B7C30 03E00008 */  jr         $ra
    /* 1E50E4 151B7C34 27BD0048 */   addiu     $sp, $sp, 0x48
