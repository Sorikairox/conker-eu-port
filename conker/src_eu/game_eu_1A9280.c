#include <ultra64.h>
#include "functions.h"
#include "variables.h"


s32 func_151EFDD0();
extern u8 D_80096091[];
s32 func_1517BA70(u8 *arg0, u8 *arg1, s32 *arg2, s32 arg3) {
    s32 d;
    s32 lim;
    s32 r;

    *arg2 = *arg2 * 3 / 2;
    lim = D_80096091[arg0[8] * 0xA] << 8;
    if (*arg2 >= lim) {
        *arg2 -= lim;
    }
    *(s16 *)(arg1 + 0) = *(s16 *)(arg0 + 0);
    *(s16 *)(arg1 + 2) = *(s16 *)(arg0 + 2);
    *(s16 *)(arg1 + 4) = *(s16 *)(arg0 + 4);
    d = 0x29 - *(s8 *)(arg0 + 0xD);
    if (d == 0) {
        *(s8 *)(arg0 + 0xD) = *(s8 *)(arg0 + 0xD) - func_151EFDD0() % 8 + 4;
    } else if (d < 0) {
        r = func_151EFDD0();
        *(s8 *)(arg0 + 0xD) = *(s8 *)(arg0 + 0xD) - (func_151EFDD0() % -d >> 1) - r % 8 + 4;
    } else {
        r = func_151EFDD0();
        *(s8 *)(arg0 + 0xD) += (func_151EFDD0() % d >> 1) + r % 8 - 4;
    }
    *(s16 *)(arg1 + 0) = *(s16 *)(arg0 + 0);
    *(s16 *)(arg1 + 2) = *(s16 *)(arg0 + 2);
    *(s16 *)(arg1 + 4) = *(s16 *)(arg0 + 4);
    return 0;
}

s32 func_1517BC58(s16 *arg0, s16 *arg1, s32 *arg2, u8 *arg3) {
    s32 t;
    if (*arg2 >= 0x600) {
        arg1[1] = (arg0[1] + (*arg2 >> 6)) - 0x18;
        arg1[0] = (arg0[0] + (*arg2 >> 8)) - 6;
        t = ((*arg3 << 7) / ((*arg2 >> 6) - 0x17)) >> 4;
        if (t < *arg3) {
            *arg3 = t;
        }
        *arg2 = 0x600;
    } else {
        arg1[0] = arg0[0];
        arg1[1] = arg0[1];
    }
    arg1[2] = arg0[2];
    return 0;
}

s32 func_1517BD18(s16 *arg0, s16 *arg1, s32 *arg2, s32 arg3) {
    if (*arg2 >= 0x300) {
        if (*arg2 >= 0x501) {
            *arg2 -= 0x200;
        } else {
            *arg2 = 0x300;
        }
    }
    arg1[0] = arg0[0];
    arg1[1] = arg0[1];
    arg1[2] = arg0[2];
    return 0;
}

s32 func_1517BD68(s16 *arg0, s16 *arg1, s32 *arg2, s32 arg3) {
    s32 v;
    s32 d;

    v = *arg2;
    if (v >= 0xD00) {
        return 1;
    }
    d = v - 0x600;
    if (v >= 0x100) {
        d = 0x190000 - d * d;
        arg1[1] = arg0[1] + d / 7680;
        v = *arg2;
        if (v >= 0x200) {
            if (v >= 0xA01) {
                *arg2 = v - 0x800;
            } else {
                *arg2 = 0x200;
            }
        }
    } else {
        arg1[1] = arg0[1];
    }
    arg1[0] = arg0[0];
    arg1[2] = arg0[2];
    return 0;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A9280/func_1517BE0C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A9280/func_1517C11C.s")

#ifdef NON_MATCHING // the definition is void (asm: v0 is not a result); one signature for wasm
void func_10004074(s32);
#else
s32 func_10004074(s32);
#endif
s32 func_10006530(s32, s32, u32);

void func_1517D534(void)
{
  int pad;
  s32 *var_s0;
  s32 temp_a0;
  s32 temp_a1;
  s32 var_s1;
 do { var_s0 = &D_800DDA90; var_s1 = 0; do { temp_a0 = *((s32 *) (((u8 *) var_s0) + 8)); if (temp_a0 != 0) { temp_a1 = (&D_800DD478)[var_s1 * 0x1A]; if (temp_a1 != 0) { func_10006530(temp_a0, temp_a1, D_8003809C); func_10004074(*((s32 *) (((u8 *) var_s0) + 8))); } *((s32 *) (((u8 *) var_s0) + 8)) = 0; } var_s1 += 1; var_s0 += 4; } while (var_s1 != 0xF); } while (0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A9280/func_1517D5E4.s")

extern u8 D_800DE158[];

void func_1517DAE8(s16 arg0, s16 arg1, s16 arg2, f32 arg3, s32 arg4, s32 arg5, u8 arg6) {
    u8 *p;
    s32 i = D_8008CEB0;

    if (i < 3) {
        p = D_800DE158 + i * 16;
        *(s16 *)(p + 0) = arg0;
        *(s16 *)(p + 2) = arg1;
        *(s16 *)(p + 4) = arg2;
        *(f32 *)(p + 0xC) = arg3;
        *(s16 *)(p + 8) = arg4;
        *(s16 *)(p + 0xA) = arg5;
        p[6] = arg6;
        D_8008CEB0 = i + 1;
    }
}


void func_1517DB6C(s16 arg0, s16 arg1, s16 arg2, s32 arg3, s32 arg4, s32 arg5) {
    func_1517DAE8(arg0, arg1, arg2, D_800DBFF0[arg3].unk380, arg4, arg5, (s32) D_800DDD1C >> 3);
}

typedef struct { s16 x, y, z; u8 idx; u8 pad7; u16 a; u16 b; f32 s; } EntDC00;
extern s32 D_800DE188;
s32 func_1517D5E4(s32, s16, s16, s16, f32, s32, s32, s32, s32, s32);

s32 func_1517DC00(s32 arg0, u16 *arg1) {
    s32 saved;

    saved = D_800DE188;
    D_800DDD1C += 5;
    
    if (D_800DDD1C >= 200) {
        D_800DDD1C -= 200;
    }
    while (D_8008CEB0 != 0) {
        D_8008CEB0--;
        if (arg1 != 0) {
            arg0 = func_1517D5E4(arg0, ((EntDC00 *)D_800DE158)[D_8008CEB0].x, ((EntDC00 *)D_800DE158)[D_8008CEB0].y, ((EntDC00 *)D_800DE158)[D_8008CEB0].z, ((EntDC00 *)D_800DE158)[D_8008CEB0].s, ((EntDC00 *)D_800DE158)[D_8008CEB0].a, ((EntDC00 *)D_800DE158)[D_8008CEB0].b, 16, 32, (s32)(arg1 + ((EntDC00 *)D_800DE158)[D_8008CEB0].idx * 640));
        }
    }
    D_800DE188 = saved;
    return arg0;
}

#ifdef NON_MATCHING
s32 func_1510D338(s32, s32, s32, s32);
extern s32 D_8008D340;
extern u16 *D_800DE154;

void func_1517D7B0(s32 *arg0, s32 arg1) {
    u32 sp48;
    u32 sp44;
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_a1;
    s32 temp_a1_2;
    s32 temp_ra;
    s32 temp_s3;
    s32 temp_t1;
    s32 temp_t1_2;
    s32 temp_t4;
    s32 temp_t6;
    s32 temp_t7_2;
    s32 temp_t7_3;
    s32 temp_t8;
    s32 temp_t8_2;
    s32 temp_t8_3;
    s32 temp_t9;
    s32 temp_v0;
    s32 temp_v0_10;
    s32 temp_v0_11;
    s32 temp_v0_12;
    s32 temp_v0_13;
    s32 temp_v0_14;
    s32 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v0_5;
    s32 temp_v0_6;
    s32 temp_v0_7;
    s32 temp_v0_8;
    s32 temp_v0_9;
    s32 var_a3;
    s32 var_s1;
    s32 var_t3;
    s32 var_t4;
    s32 var_v0;
    s32 var_v0_2;
    u16 temp_a2_2;
    u16 temp_a3;
    u16 var_s2;
    u32 temp_t7;
    u32 temp_v0_2;
    u32 var_s5;
    u32 var_s5_2;
    u32 var_t5;
    u32 var_v1;
    u8 *temp_a2;
    u8 *temp_a3_2;

    var_s2 = 0xFFFF;
    if (D_800DDD10[D_800BE9C0] != 0) {
        *arg0 = func_1517DC00(*arg0, D_800DE154);
        if ((D_800DDD20 != 0) && (D_800DE188 != 0)) {
            temp_v0 = *arg0;
            *arg0 = temp_v0 + 8;
            (*(s32 **)((u8 *)temp_v0 + 4)) = &D_8008D340;
            (*(s32 *)((u8 *)temp_v0 + 0)) = 0xDE000000;
            sp44 = 0;
            var_v1 = 0;
            *arg0 = func_1510D338(*arg0, 0xFF, 0xFF, 0);
            sp48 = 0;
            if (D_800DE188 != 0) {
                do {
                    var_t3 = 0;
                    var_s5 = 0;
                    temp_v0_2 = D_800DE188 - sp48;
                    var_t5 = temp_v0_2 * 4;
                    if (temp_v0_2 >= 5U) {
                        var_t5 = 0x10;
                    }
                    if (var_t5 != 0) {
                        var_v0 = 0;
                        do {
                            if (arg1 != (*(u16 *)((u8 *)((D_800DDD10[D_800BE9C0] + (sp48 << 6) + var_v0)) + 0x16))) {
                                var_t3 |= 1 << var_s5;
                            }
                            var_s5 += 4;
                            var_v0 += 0x40;
                        } while (var_s5 < var_t5);
                    }
                    if (var_t3 != 0x1111) {
                        temp_v0_3 = *arg0;
                        *arg0 = temp_v0_3 + 8;
                        (*(s32 *)((u8 *)temp_v0_3 + 0)) = (s32) (((var_t5 & 0xFF) << 0xC) | 0x01000000 | ((var_t5 & 0x7F) * 2));
                        temp_t8 = sp48 * 4;
                        (*(s32 **)((u8 *)temp_v0_3 + 4)) = (s32 *) (D_800DDD10[D_800BE9C0] + (temp_t8 * 0x10));
                        var_s5_2 = 0;
                        if (var_t5 != 0) {
                            do {
                                var_s5_2 += 4;
                                if ((var_v1 < var_t5) && ((var_v0_2 = var_v1 * 0x10, temp_a0 = D_800DDD10[D_800BE9C0] + (temp_t8 * 0x10), (var_s2 != (*(u16 *)((u8 *)((temp_a0 + var_v0_2)) + 6)))) || ((1 << var_v1) & var_t3))) {
loop_16:
                                    var_v1 += 4;
                                    var_v0_2 += 0x40;
                                    if (var_v1 < var_t5) {
                                        if ((var_s2 != (*(u16 *)((u8 *)((temp_a0 + var_v0_2)) + 6))) || ((1 << var_v1) & var_t3)) {
                                            goto loop_16;
                                        }
                                    }
                                }
                                if ((var_v1 >= var_t5) && (var_t3 != 0x1111)) {
                                    var_v1 = 0;
                                    if (var_t3 & 1) {
                                        do {
                                            var_v1 += 4;
                                        } while ((1 << var_v1) & var_t3);
                                    }
                                    temp_a2 = D_800DDD10[D_800BE9C0] + (temp_t8 * 0x10) + (var_v1 * 0x10);
                                    temp_a3 = (*(u16 *)((u8 *)temp_a2 + 6));
                                    if ((var_s2 != temp_a3) && (var_v1 < var_t5)) {
                                        var_s2 = temp_a3;
                                        temp_t8_2 = (s32) ((*(s16 *)((u8 *)temp_a2 + 0x28)) + 1) >> 5;
                                        temp_t7_2 = (s32) ((*(s16 *)((u8 *)temp_a2 + 0x2A)) + 1) >> 5;
                                        temp_v0_4 = *arg0;
                                        *arg0 = temp_v0_4 + 8;
                                        (*(s32 *)((u8 *)temp_v0_4 + 0)) = 0xFD100000;
                                        (*(s32 **)((u8 *)temp_v0_4 + 4)) = (s32 *) (&D_800DD478)[var_s2];
                                        temp_a1 = *arg0;
                                        *arg0 = temp_a1 + 8;
                                        (*(s32 **)((u8 *)temp_a1 + 4)) = (s32 *)0x07080200;
                                        (*(s32 *)((u8 *)temp_a1 + 0)) = 0xF5100000;
                                        temp_t1 = *arg0;
                                        *arg0 = temp_t1 + 8;
                                        (*(s32 **)((u8 *)temp_t1 + 4)) = NULL;
                                        (*(s32 *)((u8 *)temp_t1 + 0)) = 0xE6000000;
                                        temp_t6 = (s32) (((s16) temp_t7_2 * 5) + 3) >> 2;
                                        temp_s3 = *arg0;
                                        *arg0 = temp_s3 + 8;
                                        temp_ra = (s16) temp_t8_2 * 2;
                                        var_t4 = 0x7FF;
                                        (*(s32 *)((u8 *)temp_s3 + 0)) = 0xF3000000;
                                        temp_a0_2 = ((s16) temp_t8_2 * temp_t6) - 1;
                                        if (temp_a0_2 < 0x7FF) {
                                            var_t4 = temp_a0_2;
                                        }
                                        temp_v0_5 = temp_ra / 8;
                                        var_s1 = temp_v0_5;
                                        if (temp_v0_5 <= 0) {
                                            var_s1 = 1;
                                        }
                                        if (temp_v0_5 <= 0) {
                                            var_a3 = 1;
                                        } else {
                                            var_a3 = temp_v0_5;
                                        }
                                        (*(s32 **)((u8 *)temp_s3 + 4)) = (s32 *) ((((s32) (var_s1 + 0x7FF) / var_a3) & 0xFFF) | 0x07000000 | ((var_t4 & 0xFFF) << 0xC));
                                        temp_v0_6 = *arg0;
                                        *arg0 = temp_v0_6 + 8;
                                        (*(s32 **)((u8 *)temp_v0_6 + 4)) = NULL;
                                        (*(s32 *)((u8 *)temp_v0_6 + 0)) = 0xE7000000;
                                        temp_v0_7 = *arg0;
                                        *arg0 = temp_v0_7 + 8;
                                        (*(s32 **)((u8 *)temp_v0_7 + 4)) = (s32 *)0x80200;
                                        (*(s32 *)((u8 *)temp_v0_7 + 0)) = (s32) (((((s32) (temp_ra + 7) >> 3) & 0x1FF) << 9) | 0xF5100000);
                                        temp_v0_8 = *arg0;
                                        *arg0 = temp_v0_8 + 8;
                                        (*(s32 *)((u8 *)temp_v0_8 + 0)) = 0xF2000000;
                                        temp_t1_2 = ((((s16) temp_t8_2 - 1) * 4) & 0xFFF) << 0xC;
                                        (*(s32 **)((u8 *)temp_v0_8 + 4)) = (s32 *) (temp_t1_2 | (((temp_t6 - 1) * 4) & 0xFFF));
                                        temp_v0_9 = *arg0;
                                        *arg0 = temp_v0_9 + 8;
                                        (*(s32 *)((u8 *)temp_v0_9 + 0)) = (s32) (((((s32) (((s16) temp_t8_2 >> 1) + 7) >> 3) & 0x1FF) << 9) | 0xF5800000 | (((s32) ((s16) temp_t8_2 * (s16) temp_t7_2) >> 2) & 0x1FF));
                                        (*(s32 **)((u8 *)temp_v0_9 + 4)) = (s32 *)0x01080200;
                                        temp_v0_10 = *arg0;
                                        *arg0 = temp_v0_10 + 8;
                                        (*(s32 *)((u8 *)temp_v0_10 + 0)) = 0xF2000000;
                                        (*(s32 **)((u8 *)temp_v0_10 + 4)) = (s32 *) (temp_t1_2 | 0x01000000 | ((((s16) temp_t7_2 - 1) * 4) & 0xFFF));
                                    }
                                }
                                if (var_v1 < var_t5) {
                                    temp_t4 = 1 << var_v1;
                                    if (!(temp_t4 & var_t3)) {
                                        temp_t8_3 = (temp_t8 + var_v1) * 0x10;
                                        temp_a1_2 = var_v1 * 2;
                                        (*(s16 *)((u8 *)((D_800DDD10[D_800BE9C0] + temp_t8_3)) + 0x36)) = 0;
                                        var_t3 |= temp_t4;
                                        temp_a3_2 = D_800DDD10[D_800BE9C0] + temp_t8_3;
                                        temp_a2_2 = (*(u16 *)((u8 *)temp_a3_2 + 0x36));
                                        (*(u16 *)((u8 *)temp_a3_2 + 0x26)) = temp_a2_2;
                                        (*(u16 *)((u8 *)((D_800DDD10[D_800BE9C0] + temp_t8_3)) + 0x16)) = temp_a2_2;
                                        temp_t7_3 = (temp_a1_2 & 0xFF) << 0x10;
                                        (*(u16 *)((u8 *)((D_800DDD10[D_800BE9C0] + temp_t8_3)) + 6)) = temp_a2_2;
                                        temp_v0_11 = *arg0;
                                        temp_t9 = (temp_a1_2 + 4) & 0xFF;
                                        *arg0 = temp_v0_11 + 8;
                                        (*(s32 *)((u8 *)temp_v0_11 + 0)) = (s32) (temp_t7_3 | (temp_t9 << 8) | ((temp_a1_2 + 2) & 0xFF) | 0x05000000);
                                        (*(s32 **)((u8 *)temp_v0_11 + 4)) = NULL;
                                        temp_v0_12 = *arg0;
                                        *arg0 = temp_v0_12 + 8;
                                        (*(s32 **)((u8 *)temp_v0_12 + 4)) = NULL;
                                        (*(s32 *)((u8 *)temp_v0_12 + 0)) = (s32) (temp_t7_3 | (((temp_a1_2 + 6) & 0xFF) << 8) | temp_t9 | 0x05000000);
                                    }
                                }
                            } while (var_s5_2 < var_t5);
                        }
                    }
                    temp_t7 = sp48 + 4;
                    sp48 = temp_t7;
                } while (temp_t7 < (u32) D_800DE188);
            }
            temp_v0_13 = *arg0;
            *arg0 = temp_v0_13 + 8;
            (*(s32 **)((u8 *)temp_v0_13 + 4)) = (s32 *)0x200000;
            (*(s32 *)((u8 *)temp_v0_13 + 0)) = 0xD9FFFFFF;
            temp_v0_14 = *arg0;
            *arg0 = temp_v0_14 + 8;
            (*(s32 **)((u8 *)temp_v0_14 + 4)) = NULL;
            (*(s32 *)((u8 *)temp_v0_14 + 0)) = 0xE7000000;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A9280/func_1517D7B0.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_1A9280/func_1517E3CC.s")

void func_1517E5CC(s32 arg0, s32 arg1, s32 arg2) {
    D_800DD8A0[0] = arg0;
    D_800DD8A0[1] = arg1;
    D_800DD8A0[2] = arg2;
}
