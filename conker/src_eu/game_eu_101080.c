#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
void func_150D513C(u8 *arg0);
#endif


#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_101080/func_150D3870.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_101080/func_150D3F78.s")

#ifdef NON_MATCHING
f32 func_15143E64(s32);
s32 func_1515C668(s32, s32 *, u8 *);

s32 func_150D44E4(u8 *arg0) {
    struct {
        s32 u7C;
        f32 u80;
        f32 u84;
        s32 u88;
        s32 * u8C;
    } sp;
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f14;
    f32 temp_f16;
    f32 temp_f2;
    f32 var_f0;
    f32 var_f12;
    f32 var_f24;
    f32 var_f26;
    f32 var_f2;
    s32 *temp_t6;
    s32 temp_a1;
    s32 var_a0;
    s32 var_t0;
    s8 var_v0;
    u8 *temp_v0;
    u8 *temp_v1;
    u8 *temp_v1_2;

    temp_t6 = (*(s32 **)((u8 *)arg0 + 0x98));
    sp.u8C = temp_t6;
    var_t0 = (*(s32 *)((u8 *)arg0 + 0x94));
    if (D_800C35EA != 1) {
        sp.u88 = var_t0;
        var_t0 = sp.u88;
        if (func_1515C668(*temp_t6, &sp.u7C, arg0) != 0) {
            var_f2 = func_15143E64(sp.u7C);
        } else {
            var_f2 = 0.0f;
        }
    } else if (D_800DBFF0->unk5F0 & 4) {
        var_f2 = 0.0f;
    } else {
        var_f2 = 128.0f;
    }
    if (var_f2 < 10.0f) {
        var_f26 = 0.0f;
    } else if (var_f2 > 70.0f) {
        var_f26 = 600.0f;
    } else {
        var_f26 = (var_f2 - 10.0f) * 0.016666668f * 600.0f;
    }
    if ((*(s8 *)((u8 *)arg0 + 0x2C)) >= 2) {
        var_f24 = 0.0f;
        var_a0 = (*(s8 *)((u8 *)arg0 + 0x2E)) - 1;
        if (var_a0 < 0) {
            var_a0 = (*(u8 *)((u8 *)arg0 + 0x25)) - 1;
        }
        if (var_a0 != (*(s8 *)((u8 *)arg0 + 0x2D))) {
            do {
                temp_a1 = var_a0;
                var_a0 -= 1;
                if (var_a0 < 0) {
                    var_a0 = (*(u8 *)((u8 *)arg0 + 0x25)) - 1;
                }
                temp_v1 = (temp_a1 * 0x14) + var_t0;
                temp_f16 = (*(f32 *)((u8 *)temp_v1 + 0xC));
                var_f24 += temp_f16;
                if (var_f26 < var_f24) {
                    if (temp_f16 != 0.0f) {
                        temp_f14 = (var_f24 - var_f26) / temp_f16;
                        temp_v0 = (var_a0 * 0x14) + var_t0;
                        temp_f0 = (*(f32 *)((u8 *)temp_v0 + 0));
                        temp_f2 = (*(f32 *)((u8 *)temp_v0 + 4));
                        temp_f12 = (*(f32 *)((u8 *)temp_v0 + 8));
                        (*(f32 *)((u8 *)temp_v0 + 0)) = (f32) (temp_f0 - ((temp_f0 - (*(f32 *)((u8 *)temp_v1 + 0))) * temp_f14));
                        (*(f32 *)((u8 *)temp_v0 + 4)) = (f32) (temp_f2 - ((temp_f2 - (*(f32 *)((u8 *)temp_v1 + 4))) * temp_f14));
                        (*(f32 *)((u8 *)temp_v0 + 8)) = (f32) (temp_f12 - ((temp_f12 - (*(f32 *)((u8 *)temp_v1 + 8))) * temp_f14));
                        (*(f32 *)((u8 *)temp_v1 + 0xC)) = (f32) ((*(f32 *)((u8 *)temp_v1 + 0xC)) * (1.0f - temp_f14));
                    }
                    var_f24 = var_f26;
                    if (var_a0 != (*(s8 *)((u8 *)arg0 + 0x2D))) {
                        do {
                            (*(s8 *)((u8 *)arg0 + 0x2D)) = (s8) ((*(s8 *)((u8 *)arg0 + 0x2D)) + 1);
                            if ((*(u8 *)((u8 *)arg0 + 0x25)) == (*(s8 *)((u8 *)arg0 + 0x2D))) {
                                (*(s8 *)((u8 *)arg0 + 0x2D)) = 0;
                            }
                            (*(s8 *)((u8 *)arg0 + 0x2C)) = (s8) ((*(s8 *)((u8 *)arg0 + 0x2C)) - 1);
                        } while (var_a0 != (*(s8 *)((u8 *)arg0 + 0x2D)));
                    }
                }
            } while (var_a0 != (*(s8 *)((u8 *)arg0 + 0x2D)));
        }
        if (var_f24 != 0.0f) {
            var_f12 = 1.0f / var_f24;
        } else {
            var_f12 = 0.0f;
        }
        sp.u80 = var_f12;
        sp.u84 = var_f24;
    }
    if ((*(s8 *)((u8 *)arg0 + 0x2C)) >= 2) {
        var_v0 = (*(s8 *)((u8 *)arg0 + 0x2E));
        var_f0 = sp.u84;
        do {
            var_v0 -= 1;
            if (var_v0 < 0) {
                var_v0 = (*(u8 *)((u8 *)arg0 + 0x25)) - 1;
            }
            temp_v1_2 = (var_v0 * 0x14) + var_t0;
            (*(f32 *)((u8 *)temp_v1_2 + 0x10)) = (f32) (var_f0 * ((*(f32 *)((u8 *)sp.u8C + 0x14)) * sp.u80));
            var_f0 -= (*(f32 *)((u8 *)temp_v1_2 + 0xC));
        } while (var_v0 != (*(s8 *)((u8 *)arg0 + 0x2D)));
    }
    return 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_101080/func_150D44E4.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_101080/func_150D4810.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_101080/func_150D4ED0.s")

#ifdef NON_MATCHING
s32 func_1514654C(struct127 *, s32, s32, s32 **, u8 **, s32);
extern s32 D_800A0DA0;
extern s32 D_800A0DAC;

s32 func_150D4FF0(u8 *arg0, u8 *arg1, struct127 *arg2, s32 arg3) {
    s32 *sp34;
    s32 *sp30;
    u8 *sp2C;
    u8 *sp28;

    if (arg2->unk1D4 != NULL) {
        sp30 = &D_800A0DA0;
        sp34 = &D_800A0DAC;
        sp28 = arg0;
        sp2C = arg1;
        if (func_1514654C(arg2, arg3, 0, &sp30, &sp28, 2) != 0) {
            return 1;
        }
        return 0;
    }
    (*(f32 *)((u8 *)arg0 + 0)) = (f32) arg2->x_position;
    (*(f32 *)((u8 *)arg0 + 4)) = (f32) (arg2->y_position + 100.0f);
    (*(f32 *)((u8 *)arg0 + 8)) = (f32) arg2->z_position;
    (*(f32 *)((u8 *)arg1 + 0)) = (f32) arg2->x_position;
    (*(f32 *)((u8 *)arg1 + 4)) = (f32) (arg2->y_position + 100.0f + 500.0f);
    (*(f32 *)((u8 *)arg1 + 8)) = (f32) arg2->z_position;
    return 2;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_101080/func_150D4FF0.s")
#endif
void func_150D50E4(s32 arg0) {
    func_150D513C(arg0);
    func_15147E64(arg0);
}

void func_150D5110(s32 arg0) {
    func_150D513C(arg0);
    func_15147E98(arg0);
}

#ifdef NON_MATCHING
void func_1000FD38(s32, s32, s32);
extern s32 func_150D5634;

void func_150D513C(u8 *arg0) {
    s32 *sp20;
    struct102 *temp_a0;
    struct102 *temp_a0_2;
    u8 *temp_s0;

    temp_s0 = (*(u8 **)((u8 *)arg0 + 0x98));
    if (D_8008FD8C < 5) {
        func_1000FD38(&func_150D5634, temp_s0, 0x5B3);
    }
    sp20 = &func_150D5634;
    func_1000FD38(&func_150D5634, temp_s0, 0x5B4);
    func_1000FD38(&func_150D5634, temp_s0, 0x5BC);
    temp_a0 = (*(struct102 **)((u8 *)temp_s0 + 0xC));
    if (temp_a0 != NULL) {
        func_1516972C(temp_a0);
    }
    temp_a0_2 = (*(struct102 **)((u8 *)temp_s0 + 0x10));
    if (temp_a0_2 != NULL) {
        func_1516972C(temp_a0_2);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_101080/func_150D513C.s")
#endif
extern f32 D_800A0DE4;
extern u8 D_800A0D90[];
s32 func_150D51D4(u8 *arg0)
{
  u8 *temp_v1;
  *(s16 *)(arg0 + 0x170) -= D_800BE9E4;
  temp_v1 = arg0 + 0x110;
  if (*(s16 *)(arg0 + 0x170) < 0) {
    arg0[0x18] = *(s32 *)&D_800A0D90[(func_150ADA20() & 3) * 4];
    *(s16 *)(arg0 + 0x170) = (func_150ADA20() & 7) + 3;
  }
  *(f32 *)(temp_v1 + 0x48) += (*(f32 *)(arg0 + 0x174) - *(f32 *)(temp_v1 + 0x48)) * D_800A0DE4;
  return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_101080/func_150D5268.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_101080/func_150D5634.s")
