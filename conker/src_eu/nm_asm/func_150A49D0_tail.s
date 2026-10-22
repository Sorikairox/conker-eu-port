/* P28: tail of func_150A49D0.s kept as asm under NON_MATCHING: func_150A3F50 code (its beqz to .L150A4F74) */
glabel func_150A49D0_tail
  .L150A4F74:
    /* D2784 150A4F74 44900000 */  mtc1       $s0, $f0
    /* D2788 150A4F78 44910800 */  mtc1       $s1, $f1
    /* D278C 150A4F7C 44921000 */  mtc1       $s2, $f2
    /* D2790 150A4F80 44931800 */  mtc1       $s3, $f3
    /* D2794 150A4F84 44942000 */  mtc1       $s4, $f4
    /* D2798 150A4F88 44952800 */  mtc1       $s5, $f5
    /* D279C 150A4F8C 44963000 */  mtc1       $s6, $f6
    /* D27A0 150A4F90 44973800 */  mtc1       $s7, $f7
    /* D27A4 150A4F94 449E4000 */  mtc1       $fp, $f8
    /* D27A8 150A4F98 449C4800 */  mtc1       $gp, $f9
    /* D27AC 150A4F9C 449F7800 */  mtc1       $ra, $f15
    /* D27B0 150A4FA0 3C1F150A */  lui        $ra, %hi(D_150A4FD4)
    /* D27B4 150A4FA4 27FF4FD4 */  addiu      $ra, $ra, %lo(D_150A4FD4)
    /* D27B8 150A4FA8 3C0A800D */  lui        $t2, %hi(D_800D3720)
    /* D27BC 150A4FAC 254A3720 */  addiu      $t2, $t2, %lo(D_800D3720)
    /* D27C0 150A4FB0 00001025 */  or         $v0, $zero, $zero
    /* D27C4 150A4FB4 3C0C800E */  lui        $t4, %hi(D_800DC270)
    /* D27C8 150A4FB8 8D8CC270 */  lw         $t4, %lo(D_800DC270)($t4)
    /* D27CC 150A4FBC 3C0B800E */  lui        $t3, %hi(D_800DC26C)
    /* D27D0 150A4FC0 8D6BC26C */  lw         $t3, %lo(D_800DC26C)($t3)
    /* D27D4 150A4FC4 3C09800E */  lui        $t1, %hi(D_800DBE4C)
    /* D27D8 150A4FC8 8D29C27C */  lw         $t1, %lo(D_800DBE4C)($t1)
    /* D27DC 150A4FCC 0000C025 */  or         $t8, $zero, $zero
    /* D27E0 150A4FD0 00004025 */  or         $t0, $zero, $zero
  glabel D_150A4FD4
    /* D27E4 150A4FD4 1309FD19 */  beq        $t8, $t1, func_150A443C
    /* D27E8 150A4FD8 03008025 */   or        $s0, $t8, $zero
    /* D27EC 150A4FDC 09429023 */  j          func_150A408C
    /* D27F0 150A4FE0 00000000 */   nop
