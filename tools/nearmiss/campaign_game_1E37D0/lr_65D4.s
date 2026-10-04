.late_rodata
glabel D_800AA474
    .float 0.003721999936
glabel D_800AA478
    .float 4.409547806

.text
glabel func_151B65D4
    /* 1E3A84 151B65D4 27BDFF48 */  addiu      $sp, $sp, -0xB8
    /* 1E3A88 151B65D8 AFBF0044 */  sw         $ra, 0x44($sp)
    /* 1E3A8C 151B65DC F7BE0038 */  sdc1       $f30, 0x38($sp)
    /* 1E3A90 151B65E0 F7BC0030 */  sdc1       $f28, 0x30($sp)
    /* 1E3A94 151B65E4 F7BA0028 */  sdc1       $f26, 0x28($sp)
    /* 1E3A98 151B65E8 F7B80020 */  sdc1       $f24, 0x20($sp)
    /* 1E3A9C 151B65EC F7B60018 */  sdc1       $f22, 0x18($sp)
    /* 1E3AA0 151B65F0 F7B40010 */  sdc1       $f20, 0x10($sp)
    /* 1E3AA4 151B65F4 00802825 */  or         $a1, $a0, $zero
    /* 1E3AA8 151B65F8 8CA60098 */  lw         $a2, 0x98($a1)
    /* 1E3AAC 151B65FC 8CA90094 */  lw         $t1, 0x94($a1)
    /* 1E3AB0 151B6600 8CC20000 */  lw         $v0, 0x0($a2)
    /* 1E3AB4 151B6604 8C4E0000 */  lw         $t6, 0x0($v0)
    /* 1E3AB8 151B6608 51C0000E */  beql       $t6, $zero, .L151B6644
    /* 1E3ABC 151B660C 94B9001E */   lhu       $t9, 0x1E($a1)
    /* 1E3AC0 151B6610 90CF0004 */  lbu        $t7, 0x4($a2)
    /* 1E3AC4 151B6614 9058003B */  lbu        $t8, 0x3B($v0)
    /* 1E3AC8 151B6618 3C014170 */  lui        $at, (0x41700000 >> 16)
    /* 1E3ACC 151B661C 55F80009 */  bnel       $t7, $t8, .L151B6644
    /* 1E3AD0 151B6620 94B9001E */   lhu       $t9, 0x1E($a1)
    /* 1E3AD4 151B6624 C444003C */  lwc1       $f4, 0x3C($v0)
    /* 1E3AD8 151B6628 44813000 */  mtc1       $at, $f6
    /* 1E3ADC 151B662C 00000000 */  nop
    /* 1E3AE0 151B6630 4606203C */  c.lt.s     $f4, $f6
    /* 1E3AE4 151B6634 00000000 */  nop
    /* 1E3AE8 151B6638 45020008 */  bc1fl      .L151B665C
    /* 1E3AEC 151B663C C4480014 */   lwc1      $f8, 0x14($v0)
    /* 1E3AF0 151B6640 94B9001E */  lhu        $t9, 0x1E($a1)
  .L151B6644:
    /* 1E3AF4 151B6644 A0A00030 */  sb         $zero, 0x30($a1)
    /* 1E3AF8 151B6648 24020001 */  addiu      $v0, $zero, 0x1
    /* 1E3AFC 151B664C 372B0008 */  ori        $t3, $t9, 0x8
    /* 1E3B00 151B6650 100000AC */  b          .L151B6904
    /* 1E3B04 151B6654 A4AB001E */   sh        $t3, 0x1E($a1)
    /* 1E3B08 151B6658 C4480014 */  lwc1       $f8, 0x14($v0)
  .L151B665C:
    /* 1E3B0C 151B665C 27A400A0 */  addiu      $a0, $sp, 0xA0
    /* 1E3B10 151B6660 E4A80010 */  swc1       $f8, 0x10($a1)
    /* 1E3B14 151B6664 C44A0018 */  lwc1       $f10, 0x18($v0)
    /* 1E3B18 151B6668 C4A60010 */  lwc1       $f6, 0x10($a1)
    /* 1E3B1C 151B666C E4AA0014 */  swc1       $f10, 0x14($a1)
    /* 1E3B20 151B6670 C444001C */  lwc1       $f4, 0x1C($v0)
    /* 1E3B24 151B6674 E4A40018 */  swc1       $f4, 0x18($a1)
    /* 1E3B28 151B6678 C4C80008 */  lwc1       $f8, 0x8($a2)
    /* 1E3B2C 151B667C 46083281 */  sub.s      $f10, $f6, $f8
    /* 1E3B30 151B6680 E7AA00A0 */  swc1       $f10, 0xA0($sp)
    /* 1E3B34 151B6684 C4C6000C */  lwc1       $f6, 0xC($a2)
    /* 1E3B38 151B6688 C4A40014 */  lwc1       $f4, 0x14($a1)
    /* 1E3B3C 151B668C 46062201 */  sub.s      $f8, $f4, $f6
    /* 1E3B40 151B6690 E7A800A4 */  swc1       $f8, 0xA4($sp)
    /* 1E3B44 151B6694 C4C40010 */  lwc1       $f4, 0x10($a2)
    /* 1E3B48 151B6698 C4AA0018 */  lwc1       $f10, 0x18($a1)
    /* 1E3B4C 151B669C AFA900B0 */  sw         $t1, 0xB0($sp)
    /* 1E3B50 151B66A0 AFA600B4 */  sw         $a2, 0xB4($sp)
    /* 1E3B54 151B66A4 46045181 */  sub.s      $f6, $f10, $f4
    /* 1E3B58 151B66A8 AFA500B8 */  sw         $a1, 0xB8($sp)
    /* 1E3B5C 151B66AC 0D450F99 */  jal        func_15143E64
    /* 1E3B60 151B66B0 E7A600A8 */   swc1      $f6, 0xA8($sp)
    /* 1E3B64 151B66B4 3C013F80 */  lui        $at, (0x3F800000 >> 16)
    /* 1E3B68 151B66B8 4481B000 */  mtc1       $at, $f22
    /* 1E3B6C 151B66BC 3C01800B */  lui        $at, %hi(D_800AA474)
    /* 1E3B70 151B66C0 C428A474 */  lwc1       $f8, %lo(D_800AA474)($at)
    /* 1E3B74 151B66C4 3C02800C */  lui        $v0, %hi(D_800BE9A4)
    /* 1E3B78 151B66C8 2442E9A4 */  addiu      $v0, $v0, %lo(D_800BE9A4)
    /* 1E3B7C 151B66CC 46080282 */  mul.s      $f10, $f0, $f8
    /* 1E3B80 151B66D0 C4440000 */  lwc1       $f4, 0x0($v0)
    /* 1E3B84 151B66D4 8FA600B4 */  lw         $a2, 0xB4($sp)
    /* 1E3B88 151B66D8 8FA500B8 */  lw         $a1, 0xB8($sp)
    /* 1E3B8C 151B66DC 8FA900B0 */  lw         $t1, 0xB0($sp)
    /* 1E3B90 151B66E0 C4C80014 */  lwc1       $f8, 0x14($a2)
    /* 1E3B94 151B66E4 3C01800B */  lui        $at, %hi(D_800AA478)
    /* 1E3B98 151B66E8 46045182 */  mul.s      $f6, $f10, $f4
    /* 1E3B9C 151B66EC C4C4001C */  lwc1       $f4, 0x1C($a2)
    /* 1E3BA0 151B66F0 27A40084 */  addiu      $a0, $sp, 0x84
    /* 1E3BA4 151B66F4 46064280 */  add.s      $f10, $f8, $f6
    /* 1E3BA8 151B66F8 E4CA0014 */  swc1       $f10, 0x14($a2)
    /* 1E3BAC 151B66FC C428A478 */  lwc1       $f8, %lo(D_800AA478)($at)
    /* 1E3BB0 151B6700 C4C20014 */  lwc1       $f2, 0x14($a2)
    /* 1E3BB4 151B6704 46080182 */  mul.s      $f6, $f0, $f8
    /* 1E3BB8 151B6708 4602B03C */  c.lt.s     $f22, $f2
    /* 1E3BBC 151B670C 46062280 */  add.s      $f10, $f4, $f6
    /* 1E3BC0 151B6710 E4CA001C */  swc1       $f10, 0x1C($a2)
    /* 1E3BC4 151B6714 4500007A */  bc1f       .L151B6900
    /* 1E3BC8 151B6718 E7A20058 */   swc1      $f2, 0x58($sp)
    /* 1E3BCC 151B671C C7A80058 */  lwc1       $f8, 0x58($sp)
    /* 1E3BD0 151B6720 24CA0008 */  addiu      $t2, $a2, 0x8
    /* 1E3BD4 151B6724 8D410000 */  lw         $at, 0x0($t2)
    /* 1E3BD8 151B6728 4608B083 */  div.s      $f2, $f22, $f8
    /* 1E3BDC 151B672C C4C40018 */  lwc1       $f4, 0x18($a2)
    /* 1E3BE0 151B6730 AC810000 */  sw         $at, 0x0($a0)
    /* 1E3BE4 151B6734 8D4D0004 */  lw         $t5, 0x4($t2)
    /* 1E3BE8 151B6738 C4460000 */  lwc1       $f6, 0x0($v0)
    /* 1E3BEC 151B673C 2408009B */  addiu      $t0, $zero, 0x9B
    /* 1E3BF0 151B6740 AC8D0004 */  sw         $t5, 0x4($a0)
    /* 1E3BF4 151B6744 46062480 */  add.s      $f18, $f4, $f6
    /* 1E3BF8 151B6748 8D410008 */  lw         $at, 0x8($t2)
    /* 1E3BFC 151B674C 2407001C */  addiu      $a3, $zero, 0x1C
    /* 1E3C00 151B6750 AC810008 */  sw         $at, 0x8($a0)
    /* 1E3C04 151B6754 C7AA00A0 */  lwc1       $f10, 0xA0($sp)
    /* 1E3C08 151B6758 C7A800A4 */  lwc1       $f8, 0xA4($sp)
    /* 1E3C0C 151B675C C4CC0020 */  lwc1       $f12, 0x20($a2)
    /* 1E3C10 151B6760 C4C6001C */  lwc1       $f6, 0x1C($a2)
    /* 1E3C14 151B6764 C7A400A8 */  lwc1       $f4, 0xA8($sp)
    /* 1E3C18 151B6768 3C014700 */  lui        $at, (0x47000000 >> 16)
    /* 1E3C1C 151B676C C4D40024 */  lwc1       $f20, 0x24($a2)
    /* 1E3C20 151B6770 46006406 */  mov.s      $f16, $f12
    /* 1E3C24 151B6774 460C3381 */  sub.s      $f14, $f6, $f12
    /* 1E3C28 151B6778 46029602 */  mul.s      $f24, $f18, $f2
    /* 1E3C2C 151B677C 00000000 */  nop
    /* 1E3C30 151B6780 46025682 */  mul.s      $f26, $f10, $f2
    /* 1E3C34 151B6784 00000000 */  nop
    /* 1E3C38 151B6788 46024702 */  mul.s      $f28, $f8, $f2
    /* 1E3C3C 151B678C 4600C607 */  neg.s      $f24, $f24
    /* 1E3C40 151B6790 46022782 */  mul.s      $f30, $f4, $f2
    /* 1E3C44 151B6794 00000000 */  nop
    /* 1E3C48 151B6798 46027282 */  mul.s      $f10, $f14, $f2
    /* 1E3C4C 151B679C 44817000 */  mtc1       $at, $f14
    /* 1E3C50 151B67A0 3C014680 */  lui        $at, (0x46800000 >> 16)
    /* 1E3C54 151B67A4 46020202 */  mul.s      $f8, $f0, $f2
    /* 1E3C58 151B67A8 44816000 */  mtc1       $at, $f12
    /* 1E3C5C 151B67AC E7AA0050 */  swc1       $f10, 0x50($sp)
    /* 1E3C60 151B67B0 E7A80048 */  swc1       $f8, 0x48($sp)
    /* 1E3C64 151B67B4 80AE002E */  lb         $t6, 0x2E($a1)
  .L151B67B8:
    /* 1E3C68 151B67B8 8C810000 */  lw         $at, 0x0($a0)
    /* 1E3C6C 151B67BC 4610603C */  c.lt.s     $f12, $f16
    /* 1E3C70 151B67C0 01C70019 */  multu      $t6, $a3
    /* 1E3C74 151B67C4 00007812 */  mflo       $t7
    /* 1E3C78 151B67C8 01E91021 */  addu       $v0, $t7, $t1
    /* 1E3C7C 151B67CC AC410000 */  sw         $at, 0x0($v0)
    /* 1E3C80 151B67D0 8C8B0004 */  lw         $t3, 0x4($a0)
    /* 1E3C84 151B67D4 AC4B0004 */  sw         $t3, 0x4($v0)
    /* 1E3C88 151B67D8 8C810008 */  lw         $at, 0x8($a0)
    /* 1E3C8C 151B67DC A0480010 */  sb         $t0, 0x10($v0)
    /* 1E3C90 151B67E0 E4500014 */  swc1       $f16, 0x14($v0)
    /* 1E3C94 151B67E4 AC410008 */  sw         $at, 0x8($v0)
    /* 1E3C98 151B67E8 3C014150 */  lui        $at, (0x41500000 >> 16)
    /* 1E3C9C 151B67EC 44812000 */  mtc1       $at, $f4
    /* 1E3CA0 151B67F0 00000000 */  nop
    /* 1E3CA4 151B67F4 46122181 */  sub.s      $f6, $f4, $f18
    /* 1E3CA8 151B67F8 46189480 */  add.s      $f18, $f18, $f24
    /* 1E3CAC 151B67FC 45000009 */  bc1f       .L151B6824
    /* 1E3CB0 151B6800 E446000C */   swc1      $f6, 0xC($v0)
    /* 1E3CB4 151B6804 C4420014 */  lwc1       $f2, 0x14($v0)
    /* 1E3CB8 151B6808 460E1281 */  sub.s      $f10, $f2, $f14
  .L151B680C:
    /* 1E3CBC 151B680C E44A0014 */  swc1       $f10, 0x14($v0)
    /* 1E3CC0 151B6810 C4420014 */  lwc1       $f2, 0x14($v0)
    /* 1E3CC4 151B6814 4602603C */  c.lt.s     $f12, $f2
    /* 1E3CC8 151B6818 00000000 */  nop
    /* 1E3CCC 151B681C 4503FFFB */  bc1tl      .L151B680C
    /* 1E3CD0 151B6820 460E1281 */   sub.s     $f10, $f2, $f14
  .L151B6824:
    /* 1E3CD4 151B6824 E4540018 */  swc1       $f20, 0x18($v0)
    /* 1E3CD8 151B6828 80AC002E */  lb         $t4, 0x2E($a1)
    /* 1E3CDC 151B682C 90AE0025 */  lbu        $t6, 0x25($a1)
    /* 1E3CE0 151B6830 258D0001 */  addiu      $t5, $t4, 0x1
    /* 1E3CE4 151B6834 A0AD002E */  sb         $t5, 0x2E($a1)
    /* 1E3CE8 151B6838 80A3002E */  lb         $v1, 0x2E($a1)
    /* 1E3CEC 151B683C 55C30004 */  bnel       $t6, $v1, .L151B6850
    /* 1E3CF0 151B6840 80AF002C */   lb        $t7, 0x2C($a1)
    /* 1E3CF4 151B6844 A0A0002E */  sb         $zero, 0x2E($a1)
    /* 1E3CF8 151B6848 80A3002E */  lb         $v1, 0x2E($a1)
    /* 1E3CFC 151B684C 80AF002C */  lb         $t7, 0x2C($a1)
  .L151B6850:
    /* 1E3D00 151B6850 80A2002D */  lb         $v0, 0x2D($a1)
    /* 1E3D04 151B6854 25F90001 */  addiu      $t9, $t7, 0x1
    /* 1E3D08 151B6858 1443000B */  bne        $v0, $v1, .L151B6888
    /* 1E3D0C 151B685C A0B9002C */   sb        $t9, 0x2C($a1)
    /* 1E3D10 151B6860 24580001 */  addiu      $t8, $v0, 0x1
    /* 1E3D14 151B6864 A0B8002D */  sb         $t8, 0x2D($a1)
    /* 1E3D18 151B6868 80AC002D */  lb         $t4, 0x2D($a1)
    /* 1E3D1C 151B686C 90AB0025 */  lbu        $t3, 0x25($a1)
    /* 1E3D20 151B6870 556C0003 */  bnel       $t3, $t4, .L151B6880
    /* 1E3D24 151B6874 80AD002C */   lb        $t5, 0x2C($a1)
    /* 1E3D28 151B6878 A0A0002D */  sb         $zero, 0x2D($a1)
    /* 1E3D2C 151B687C 80AD002C */  lb         $t5, 0x2C($a1)
  .L151B6880:
    /* 1E3D30 151B6880 25AEFFFF */  addiu      $t6, $t5, -0x1
    /* 1E3D34 151B6884 A0AE002C */  sb         $t6, 0x2C($a1)
  .L151B6888:
    /* 1E3D38 151B6888 C7A80084 */  lwc1       $f8, 0x84($sp)
    /* 1E3D3C 151B688C C7A60088 */  lwc1       $f6, 0x88($sp)
    /* 1E3D40 151B6890 461A4100 */  add.s      $f4, $f8, $f26
    /* 1E3D44 151B6894 C7A8008C */  lwc1       $f8, 0x8C($sp)
    /* 1E3D48 151B6898 461C3280 */  add.s      $f10, $f6, $f28
    /* 1E3D4C 151B689C E7A40084 */  swc1       $f4, 0x84($sp)
    /* 1E3D50 151B68A0 C7A60050 */  lwc1       $f6, 0x50($sp)
    /* 1E3D54 151B68A4 461E4100 */  add.s      $f4, $f8, $f30
    /* 1E3D58 151B68A8 E7AA0088 */  swc1       $f10, 0x88($sp)
    /* 1E3D5C 151B68AC C7AA0048 */  lwc1       $f10, 0x48($sp)
    /* 1E3D60 151B68B0 46068400 */  add.s      $f16, $f16, $f6
    /* 1E3D64 151B68B4 E7A4008C */  swc1       $f4, 0x8C($sp)
    /* 1E3D68 151B68B8 C4C80014 */  lwc1       $f8, 0x14($a2)
    /* 1E3D6C 151B68BC 460AA500 */  add.s      $f20, $f20, $f10
    /* 1E3D70 151B68C0 46164101 */  sub.s      $f4, $f8, $f22
    /* 1E3D74 151B68C4 E4C40014 */  swc1       $f4, 0x14($a2)
    /* 1E3D78 151B68C8 C4C60014 */  lwc1       $f6, 0x14($a2)
    /* 1E3D7C 151B68CC 4606B03C */  c.lt.s     $f22, $f6
    /* 1E3D80 151B68D0 00000000 */  nop
    /* 1E3D84 151B68D4 4503FFB8 */  bc1tl      .L151B67B8
    /* 1E3D88 151B68D8 80AE002E */   lb        $t6, 0x2E($a1)
    /* 1E3D8C 151B68DC 8C810000 */  lw         $at, 0x0($a0)
    /* 1E3D90 151B68E0 AD410000 */  sw         $at, 0x0($t2)
    /* 1E3D94 151B68E4 8C990004 */  lw         $t9, 0x4($a0)
    /* 1E3D98 151B68E8 AD590004 */  sw         $t9, 0x4($t2)
    /* 1E3D9C 151B68EC 8C810008 */  lw         $at, 0x8($a0)
    /* 1E3DA0 151B68F0 AD410008 */  sw         $at, 0x8($t2)
    /* 1E3DA4 151B68F4 E4D00020 */  swc1       $f16, 0x20($a2)
    /* 1E3DA8 151B68F8 E4D40024 */  swc1       $f20, 0x24($a2)
    /* 1E3DAC 151B68FC E4D20018 */  swc1       $f18, 0x18($a2)
  .L151B6900:
    /* 1E3DB0 151B6900 24020001 */  addiu      $v0, $zero, 0x1
  .L151B6904:
    /* 1E3DB4 151B6904 8FBF0044 */  lw         $ra, 0x44($sp)
    /* 1E3DB8 151B6908 D7B40010 */  ldc1       $f20, 0x10($sp)
    /* 1E3DBC 151B690C D7B60018 */  ldc1       $f22, 0x18($sp)
    /* 1E3DC0 151B6910 D7B80020 */  ldc1       $f24, 0x20($sp)
    /* 1E3DC4 151B6914 D7BA0028 */  ldc1       $f26, 0x28($sp)
    /* 1E3DC8 151B6918 D7BC0030 */  ldc1       $f28, 0x30($sp)
    /* 1E3DCC 151B691C D7BE0038 */  ldc1       $f30, 0x38($sp)
    /* 1E3DD0 151B6920 03E00008 */  jr         $ra
    /* 1E3DD4 151B6924 27BD00B8 */   addiu     $sp, $sp, 0xB8
