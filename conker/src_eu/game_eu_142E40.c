#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
void func_1511F8A4(u8 *arg0);
u8 *func_151149AC(u8);
#endif


void func_15115630(s32 arg0) {
}

void func_1511563C(u8 *arg0) {
    f32 temp_f0;

    (*(f32 *)((u8 *)arg0 + 0x68)) = (f32) ((f32) (((s32) (*(s32 *)((u8 *)arg0 + 0x3C)) >> 0x10) * D_800BE9E4) * 0.00390625f);
    (*(f32 *)((u8 *)arg0 + 8)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x68)) + (*(f32 *)((u8 *)arg0 + 8)));
    temp_f0 = (*(f32 *)((u8 *)arg0 + 8));
    if (temp_f0 < 0.0f) {
        (*(f32 *)((u8 *)arg0 + 8)) = (f32) (temp_f0 + 360.0f);
        return;
    }
    if (temp_f0 >= 360.0f) {
        (*(f32 *)((u8 *)arg0 + 8)) = (f32) (temp_f0 - 360.0f);
    }
}

void func_151156DC(u8 *arg0) {
    f32 temp_f0;

    (*(f32 *)((u8 *)arg0 + 0x64)) = (f32) ((f32) (((s32) (*(s32 *)((u8 *)arg0 + 0x3C)) >> 0x10) * D_800BE9E4) * 0.00390625f);
    (*(f32 *)((u8 *)arg0 + 4)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x64)) + (*(f32 *)((u8 *)arg0 + 4)));
    temp_f0 = (*(f32 *)((u8 *)arg0 + 4));
    if (temp_f0 < 0.0f) {
        (*(f32 *)((u8 *)arg0 + 4)) = (f32) (temp_f0 + 360.0f);
        return;
    }
    if (temp_f0 >= 360.0f) {
        (*(f32 *)((u8 *)arg0 + 4)) = (f32) (temp_f0 - 360.0f);
    }
}

void func_1511577C(u8 *arg0) {
    f32 temp_f0;

    (*(f32 *)((u8 *)arg0 + 0x60)) = (f32) ((f32) (((s32) (*(s32 *)((u8 *)arg0 + 0x3C)) >> 0x10) * D_800BE9E4) * 0.00390625f);
    (*(f32 *)arg0) = (f32) ((*(f32 *)((u8 *)arg0 + 0x60)) + (*(f32 *)arg0));
    temp_f0 = (*(f32 *)arg0);
    if (temp_f0 < 0.0f) {
        (*(f32 *)arg0) = (f32) (temp_f0 + 360.0f);
        return;
    }
    if (temp_f0 >= 360.0f) {
        (*(f32 *)arg0) = (f32) (temp_f0 - 360.0f);
    }
}

void func_1511581C(s32 arg0) {
}

#ifdef NON_MATCHING
void func_15115828(u8 *arg0) {
    s16 temp_v1;
    s32 temp_a1;
    s32 var_v0;

    var_v0 = (*(s32 *)((u8 *)arg0 + 0x7C));
    if (var_v0 == 0) {
        var_v0 = (s32) (*(s16 *)((u8 *)arg0 + 0x12));
        (*(s32 *)((u8 *)arg0 + 0x7C)) = var_v0;
    }
    temp_v1 = (*(s16 *)((u8 *)arg0 + 0x12));
    if ((*(u8 *)((u8 *)arg0 + 0x4F)) & 4) {
        temp_a1 = (*(s32 *)((u8 *)arg0 + 0x3C));
        if ((var_v0 - temp_v1) < (s16) temp_a1) {
            (*(s16 *)((u8 *)arg0 + 0x12)) = (s16) (temp_v1 - ((s16) (temp_a1 >> 0x10) * D_800BE9E4));
        }
    } else {
        (*(s16 *)((u8 *)arg0 + 0x12)) = (s16) (s32) ((f32) temp_v1 + ((f32) (var_v0 - temp_v1) * 0.05f * (f32) D_800BE9E4));
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_15115828.s")
#endif
#ifdef NON_MATCHING
void func_151158E8(u8 *arg0) {
    f32 sp34;
    f32 sp1C;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f2;
    f32 temp_f2_2;
    s32 temp_a1;
    s32 temp_a2;
    s32 temp_a3;
    s32 temp_t1;
    s32 temp_t4;
    s32 temp_t8;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 var_v0;
    s32 var_v1;
    s32 var_v1_2;
    u8 temp_t2;
    u8 temp_t9;

    temp_v0 = (*(s32 *)((u8 *)arg0 + 0x3C));
    temp_a3 = temp_v0 >> 8;
    temp_t8 = (*(u8 *)((u8 *)arg0 + 0x4F)) & 4;
    var_v1 = temp_t8;
    temp_a2 = temp_v0 >> 0x18;
    if (temp_t8 != 0) {
        var_v1 = (*(u8 *)((u8 *)arg0 + 0x4F)) & 4;
        (*(s32 *)((u8 *)arg0 + 0x80)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x80)) + D_800BE9E4);
    }
    var_v0 = (*(s32 *)((u8 *)arg0 + 0x80));
    temp_a1 = temp_a2 + (s8) temp_a3;
    if (temp_a2 >= var_v0) {
        if ((var_v1 == 0) && (var_v0 != 0)) {
            (*(s32 *)((u8 *)arg0 + 0x80)) = temp_a2;
        }
    } else if (temp_a1 >= var_v0) {
        if (var_v1 == 0) {
            (*(s32 *)((u8 *)arg0 + 0x80)) = temp_a1;
        }
    } else {
        if (var_v1 == 0) {
            temp_t4 = var_v0 + D_800BE9E4;
            (*(s32 *)((u8 *)arg0 + 0x80)) = temp_t4;
            var_v0 = temp_t4;
        }
        temp_f0 = (f32) ((var_v0 - temp_a2) - (s8) temp_a3);
        if ((*(s32 *)((u8 *)arg0 + 0x84)) == 0) {
            temp_f2 = temp_f0 * 0.628f;
            sp34 = temp_f0;
            sp1C = temp_f2;
            (*(f32 *)((u8 *)arg0 + 0)) = (f32) (-3.0f * sinf(temp_f2 * 2.0f));
            (*(f32 *)((u8 *)arg0 + 8)) = (f32) (2.0f * sinf(temp_f2 * 3.0f));
            if (sp34 > 10.0f) {
                var_v1_2 = (*(s32 *)((u8 *)arg0 + 0x7C));
                if (var_v1_2 == 0) {
                    var_v1_2 = (s32) (*(s16 *)((u8 *)arg0 + 0x12));
                    (*(s32 *)((u8 *)arg0 + 0x7C)) = var_v1_2;
                }
                temp_v0_2 = (*(s32 *)((u8 *)arg0 + 0x3C));
                (*(s16 *)((u8 *)arg0 + 0x12)) = (s16) ((*(s16 *)((u8 *)arg0 + 0x12)) - ((s8) (temp_v0_2 >> 0x10) * D_800BE9E4));
                if (((temp_v0_2 & 0xFF) * 0x10) < (var_v1_2 - (*(s16 *)((u8 *)arg0 + 0x12)))) {
                    (*(s32 *)((u8 *)arg0 + 0x84)) = 1;
                    temp_t2 = (*(u8 *)((u8 *)arg0 + 0x4F)) & 0xFF9E;
                    (*(u8 *)((u8 *)arg0 + 0x4F)) = temp_t2;
                    (*(u8 *)((u8 *)arg0 + 0x4F)) = (u8) (temp_t2 | 0x20);
                }
            }
        } else {
            temp_f0_2 = D_800CC2D0->x_position - (f32) (*(s16 *)((u8 *)arg0 + 0x10));
            temp_f2_2 = D_800CC2D0->z_position - (f32) (*(s16 *)((u8 *)arg0 + 0x14));
            if (((temp_f0_2 * temp_f0_2) + (temp_f2_2 * temp_f2_2)) > 250000.0f) {
                temp_t1 = (*(s32 *)((u8 *)arg0 + 0x7C));
                (*(s32 *)((u8 *)arg0 + 0x7C)) = 0;
                temp_t9 = (*(u8 *)((u8 *)arg0 + 0x4F)) & 0xFF9E;
                (*(u8 *)((u8 *)arg0 + 0x4F)) = temp_t9;
                (*(u8 *)((u8 *)arg0 + 0x4F)) = (u8) (temp_t9 | 1);
                (*(s32 *)((u8 *)arg0 + 0x84)) = 0;
                (*(s32 *)((u8 *)arg0 + 0x80)) = 0;
                (*(s16 *)((u8 *)arg0 + 0x12)) = (s16) temp_t1;
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_151158E8.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_15115B40.s")

#ifdef NON_MATCHING
void func_15115CDC(u8 *arg0) {
    u8 sp97;
    s16 sp94;
    s16 sp8A;
    s16 sp88;
    s32 sp84;
    s32 sp80;
    s32 sp7C;
    s16 sp7A;
    s16 sp78;
    s16 sp76;
    s16 sp72;
    s32 sp68;
    u16 sp62;
    f32 sp5C;
    f32 sp58;
    f32 sp54;
    f32 sp50;
    s32 sp4C;
    f32 sp48;
    f32 sp44;
    f32 temp_f0;
    f32 temp_f0_2;
    s16 temp_t0;
    s16 temp_t1;
    s16 temp_t2;
    s16 temp_t9_2;
    s32 temp_t4;
    s32 temp_t7;
    s32 temp_t9;
    s32 temp_v0;
    s32 temp_v1;
    s32 var_a3;
    s32 var_s1;
    s32 var_t3;
    s32 var_v1;
    s8 var_t5;
    u16 temp_a0;

    temp_v0 = (*(s32 *)((u8 *)arg0 + 0x3C));
    var_a3 = 0;
    sp97 = (u8) (temp_v0 >> 0x10);
    sp94 = (s8) temp_v0 << 6;
    temp_v1 = (*(s32 *)((u8 *)arg0 + 0x84));
    sp62 = (u16) temp_v1;
    temp_t0 = (*(s16 *)((u8 *)arg0 + 0x10));
    sp84 = (s32) temp_t0;
    temp_t1 = (*(s16 *)((u8 *)arg0 + 0x12));
    sp80 = (s32) temp_t1;
    temp_t2 = (*(s16 *)((u8 *)arg0 + 0x14));
    sp7C = (s32) temp_t2;
    var_s1 = (temp_v1 >> 0x10) & 0xFFFF;
    if (((*(u8 *)((u8 *)arg0 + 0x4F)) & 4) == 4) {
        var_a3 = 1;
    }
    var_v1 = (*(s32 *)((u8 *)arg0 + 0x7C));
    if (var_v1 == 0) {
        var_v1 = (temp_t0 << 0x10) | (temp_t1 & 0xFFFF);
        (*(s32 *)((u8 *)arg0 + 0x7C)) = var_v1;
        (*(s32 *)((u8 *)arg0 + 0x80)) = (s32) (temp_t2 & 0xFFFF);
    }
    temp_t9 = (*(s32 *)((u8 *)arg0 + 0x80));
    temp_t4 = var_v1 >> 0x10;
    var_t5 = (s8) (temp_t9 >> 0x10);
    var_t3 = (temp_t9 >> 0x18) & 0xFF;
    sp8A = var_v1 + (s16) ((s8) (temp_v0 >> 0x18) << 6);
    sp88 = temp_t9 + (s16) ((s8) (temp_v0 >> 8) << 6);
    sp76 = (s16) temp_t9;
    if (var_t5 == 0) {
        if (((s16) temp_t4 == temp_t0) && ((s16) var_v1 == temp_t1) && (sp76 == temp_t2)) {
            if (var_a3 != 0) {
                var_t5 = 0x64;
            }
        } else {
            var_t3 -= (u32) (255.0f / (f32) sp97) & 0xFF;
            if (var_t3 <= 0) {
                var_t3 = 0;
                var_t5 = -0x64;
                if (var_s1 != 0) {
                    sp78 = (s16) var_v1;
                    sp68 = 0;
                    sp7A = (s16) temp_t4;
                    sp72 = -0x64;
                    func_100111C8(var_s1 & 0xFFFF);
                    var_s1 = 0;
                    func_10010F88(0x83, 0x5000U, 0, 0U, 0, (s16) (s32) (*(s16 *)((u8 *)arg0 + 0x10)), (s16) (s32) (*(s16 *)((u8 *)arg0 + 0x12)), (s16) (s32) (*(s16 *)((u8 *)arg0 + 0x14)), 0xC8, 0x3E8);
                    var_t3 = sp68;
                    var_t5 = -0x64;
                }
            } else if ((sp62 != 0) && (var_s1 == 0)) {
                sp78 = (s16) var_v1;
                sp68 = var_t3;
                sp7A = (s16) temp_t4;
                sp72 = (s16) var_t5;
                var_s1 = func_10010E78(var_s1 & 0xFFFF, (s32) sp62, 0x7FFFU, 0, 0U, 0, (s16) (s32) temp_t0, (s16) (s32) temp_t1, (s16) (s32) temp_t2, 0xC8, 0x3E8) & 0xFFFF;
            }
            temp_f0 = (f32) var_t3 * 0.003921569f;
            (*(s16 *)((u8 *)arg0 + 0x10)) = (s16) (s32) ((f32) (s16) temp_t4 + ((f32) ((s16) ((s16) temp_t4 + sp94) - (s16) temp_t4) * temp_f0));
            (*(s16 *)((u8 *)arg0 + 0x12)) = (s16) (s32) ((f32) (s16) var_v1 + ((f32) (sp8A - (s16) var_v1) * temp_f0));
            (*(s16 *)((u8 *)arg0 + 0x14)) = (s16) (s32) ((f32) sp76 + ((f32) (sp88 - sp76) * temp_f0));
        }
    }
    sp4C = (s32) sp62;
    if (var_t5 > 0) {
        sp5C = (f32) (s16) temp_t4;
        sp58 = (f32) (s16) var_v1;
        sp54 = (f32) (sp8A - (s16) var_v1);
        temp_t9_2 = var_t5 - 1;
        var_t5 = (s8) temp_t9_2;
        sp50 = (f32) sp76;
        sp48 = (f32) (sp88 - sp76);
        sp44 = (f32) ((s16) ((s16) temp_t4 + sp94) - (s16) temp_t4);
        if (var_t3 < 0xFF) {
            var_t5 = 0x64;
            var_t3 += (u32) (255.0f / (f32) sp97) & 0xFF;
            if ((sp62 != 0) && (var_s1 == 0)) {
                sp72 = 0x64;
                sp68 = var_t3;
                var_t5 = 0x64;
                var_s1 = func_10010E78(var_s1 & 0xFFFF, sp4C, 0x7FFFU, 0, 0U, 0, (s16) (s32) (*(s16 *)((u8 *)arg0 + 0x10)), (s16) (s32) (*(s16 *)((u8 *)arg0 + 0x12)), (s16) (s32) (*(s16 *)((u8 *)arg0 + 0x14)), 0xC8, 0x3E8) & 0xFFFF;
            }
            if (var_t3 >= 0x100) {
                var_t3 = 0xFF;
            }
        } else {
            var_t3 = 0xFF;
            if (var_s1 != 0) {
                temp_a0 = var_s1 & 0xFFFF;
                var_s1 = 0;
                sp68 = 0xFF;
                sp72 = temp_t9_2;
                func_100111C8(temp_a0);
                func_10010F88(0x83, 0x5000U, 0, 0U, 0, (s16) (s32) (*(s16 *)((u8 *)arg0 + 0x10)), (s16) (s32) (*(s16 *)((u8 *)arg0 + 0x12)), (s16) (s32) (*(s16 *)((u8 *)arg0 + 0x14)), 0xC8, 0x3E8);
                var_t3 = 0xFF;
                var_t5 = (s8) sp72;
            }
        }
        temp_f0_2 = (f32) var_t3 * 0.003921569f;
        (*(s16 *)((u8 *)arg0 + 0x10)) = (s16) (s32) (sp5C + (sp44 * temp_f0_2));
        (*(s16 *)((u8 *)arg0 + 0x12)) = (s16) (s32) (sp58 + (sp54 * temp_f0_2));
        (*(s16 *)((u8 *)arg0 + 0x14)) = (s16) (s32) (sp50 + (sp48 * temp_f0_2));
    }
    if (var_t5 < 0) {
        var_t5 = (s8) (s16) (var_t5 + 1);
    }
    temp_t7 = (*(s32 *)((u8 *)arg0 + 0x80)) & 0xFFFF;
    (*(s32 *)((u8 *)arg0 + 0x80)) = temp_t7;
    (*(s32 *)((u8 *)arg0 + 0x80)) = (s32) (temp_t7 | ((var_t5 & 0xFF) << 0x10) | (var_t3 << 0x18));
    (*(s16 *)((u8 *)arg0 + 0x5A)) = (s16) ((*(s16 *)((u8 *)arg0 + 0x10)) - sp84);
    (*(s16 *)((u8 *)arg0 + 0x5C)) = (s16) ((*(s16 *)((u8 *)arg0 + 0x12)) - sp80);
    (*(s16 *)((u8 *)arg0 + 0x5E)) = (s16) ((*(s16 *)((u8 *)arg0 + 0x14)) - sp7C);
    (*(s32 *)((u8 *)arg0 + 0x84)) = (s32) ((var_s1 << 0x10) | sp4C);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_15115CDC.s")
#endif
void func_1511638C(u8 *arg0, u8 *arg1) {
    f32 sp1C;
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f14;

    sp1C = func_150AD780((*(f32 *)((u8 *)arg0 + 4)) * 0.017453292f);
    temp_f0 = func_150AD78C((*(f32 *)((u8 *)arg0 + 4)) * 0.017453292f);
    temp_f12 = (*(f32 *)((u8 *)arg1 + 0x14)) - (f32) (*(s16 *)((u8 *)arg0 + 0x10));
    temp_f14 = (*(f32 *)((u8 *)arg1 + 0x1C)) - (f32) (*(s16 *)((u8 *)arg0 + 0x14));
    if (((*(u8 *)((u8 *)arg0 + 0x4F)) & 4) == 4) {
        (*(f32 *)((u8 *)arg0 + 0x7C)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x7C)) + ((temp_f0 * temp_f12) + (sp1C * temp_f14)));
        (*(f32 *)((u8 *)arg0 + 0x80)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x80)) - ((temp_f0 * temp_f14) + (sp1C * temp_f12)));
    }
}

#ifdef NON_MATCHING
void func_1511645C(u8 *arg0, u8 *arg1) {
    f32 sp1C;
    f32 sp18;
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f14;
    f32 temp_f2;

    temp_f12 = (*(f32 *)((u8 *)arg0 + 0x7C));
    temp_f14 = (*(f32 *)((u8 *)arg0 + 0x80));
    sp1C = temp_f12;
    sp18 = temp_f14;
    func_1511638C(arg0, arg1);
    if ((*(u16 *)((u8 *)arg1 + 0x84)) == 0x4B) {
        temp_f0 = (*(f32 *)((u8 *)arg0 + 0x7C));
        temp_f2 = (*(f32 *)((u8 *)arg0 + 0x80));
        (*(f32 *)((u8 *)arg0 + 0x7C)) = (f32) (temp_f0 + ((temp_f0 - temp_f12) * 4.0f));
        (*(f32 *)((u8 *)arg0 + 0x80)) = (f32) (temp_f2 + ((temp_f2 - temp_f14) * 4.0f));
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_1511645C.s")
#endif
#ifdef NON_MATCHING
void func_151164E8(u8 *arg0) {
    f32 temp_f0;
    f32 var_f2;
    s32 temp_a1;
    s32 temp_v1;

    temp_v1 = (*(s32 *)((u8 *)arg0 + 0x3C));
    temp_a1 = temp_v1 >> 0x10;
    if ((s8) temp_v1 != 0) {
        (*(f32 *)((u8 *)arg0 + 0)) = (f32) ((*(f32 *)((u8 *)arg0 + 0)) + (((*(f32 *)((u8 *)arg0 + 0x7C)) / (f32) (s8) temp_v1) + (f32) (s8) temp_a1));
    } else {
        (*(f32 *)((u8 *)arg0 + 0)) = (f32) ((*(f32 *)((u8 *)arg0 + 0)) + (f32) ((s8) temp_a1 * D_800BE9E4));
    }
    temp_f0 = (*(f32 *)((u8 *)arg0 + 0));
    var_f2 = (f32) (s8) (temp_v1 >> 8);
    if (var_f2 < temp_f0) {
        goto block_6;
    }
    var_f2 = (f32) (s8) (temp_v1 >> 0x18);
    if (temp_f0 < var_f2) {
block_6:
        (*(f32 *)((u8 *)arg0 + 0)) = var_f2;
    }
    (*(f32 *)((u8 *)arg0 + 0x80)) = 0.0f;
    (*(f32 *)((u8 *)arg0 + 0x7C)) = 0.0f;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_151164E8.s")
#endif
#ifdef NON_MATCHING
void func_151165D8(u8 *arg0) {
    s32 temp_t4;
    s32 var_a2;
    s32 var_t0;

    temp_t4 = (*(s32 *)((u8 *)arg0 + 0x3C));
    var_a2 = 0;
    if ((s32) (*(u16 *)((u8 *)arg0 + 0x16)) > 0) {
        var_t0 = 0;
        do {
            var_a2 += 1;
            (*(s16 *)((u8 *)(((*(s32 *)((u8 *)((arg0 + (D_800BE9C0 * 4))) + 0x20)) + var_t0)) + 8)) = (s16) ((*(s16 *)((u8 *)(((*(s32 *)((u8 *)((arg0 + ((D_800BE9C0 == 0) * 4))) + 0x20)) + var_t0)) + 8)) + (s16) (temp_t4 >> 0x10));
            (*(s16 *)((u8 *)(((*(s32 *)((u8 *)((arg0 + (D_800BE9C0 * 4))) + 0x20)) + var_t0)) + 0xA)) = (s16) ((*(s16 *)((u8 *)(((*(s32 *)((u8 *)((arg0 + ((D_800BE9C0 == 0) * 4))) + 0x20)) + var_t0)) + 0xA)) + (s16) temp_t4);
            var_t0 += 0x10;
        } while (var_a2 < (s32) (*(u16 *)((u8 *)arg0 + 0x16)));
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_151165D8.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_15116690.s")

#ifdef NON_MATCHING
f32 func_1510FBC8(f32, f32, f32);
extern u16 D_800CC774;

void func_151166FC(u8 *arg0) {
    s16 sp1E;
    f32 temp_f0;
    s16 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 var_v1;

    temp_v0 = (*(s16 *)((u8 *)arg0 + 0x12));
    sp1E = temp_v0;
    temp_f0 = func_1510FBC8((f32) (*(s16 *)((u8 *)arg0 + 0x10)), (f32) temp_v0, (f32) (*(s16 *)((u8 *)arg0 + 0x14)));
    (*(f32 *)((u8 *)arg0 + 0x7C)) = temp_f0;
    if (fabsf(temp_f0 - (f32) (*(s16 *)((u8 *)arg0 + 0x12))) > 200.0f) {
        (*(s32 *)((u8 *)arg0 + 0x3C)) = 0;
    }
    if (!((*(u8 *)((u8 *)arg0 + 0x4F)) & 4)) {
        temp_v0_2 = (*(s32 *)((u8 *)arg0 + 0x3C));
        (*(s32 *)((u8 *)arg0 + 0x3C)) = (s32) ((f32) temp_v0_2 + ((f32) -temp_v0_2 * 0.2f));
    } else {
        var_v1 = -0x14;
        if (D_800CC774 == 0x4B) {
            var_v1 = -0x28;
        }
        temp_v0_3 = (*(s32 *)((u8 *)arg0 + 0x3C));
        (*(s32 *)((u8 *)arg0 + 0x3C)) = (s32) ((f32) temp_v0_3 + ((f32) (var_v1 - temp_v0_3) * 0.3f));
    }
    (*(s16 *)((u8 *)arg0 + 0x12)) = (s16) (s32) ((*(f32 *)((u8 *)arg0 + 0x7C)) + (f32) (*(s32 *)((u8 *)arg0 + 0x3C)));
    (*(s16 *)((u8 *)arg0 + 0x5C)) = (s16) ((*(s16 *)((u8 *)arg0 + 0x12)) - sp1E);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_151166FC.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_15116854.s")

#ifdef NON_MATCHING
void func_15116940(u8 *arg0) {
    f32 sp2C;
    s32 sp28;
    s32 sp24;
    f32 sp20;
    s16 sp1E;
    f32 sp18;
    f32 temp_f2;
    f32 var_f10;
    s32 temp_t2;
    s32 temp_v0;

    temp_v0 = (*(s32 *)((u8 *)arg0 + 0x3C));
    temp_t2 = (temp_v0 >> 8) & 0xFF;
    sp28 = (temp_v0 >> 0x10) & 0xFF;
    sp2C = (f32) (temp_v0 & 0xFF);
    sp24 = (temp_v0 >> 0x18) & 0xFF;
    var_f10 = (f32) temp_t2;
    if (temp_t2 < 0) {
        var_f10 += 4294967296.0f;
    }
    sp20 = var_f10 * 1.40625f;
    sp1E = (*(s16 *)((u8 *)arg0 + 0x12));
    sp18 = (*(f32 *)((u8 *)arg0 + 0));
    (*(f32 *)((u8 *)arg0 + 0x18)) = (f32) (cosf((f32) (*(s32 *)((u8 *)arg0 + 0x7C)) * 0.0000958738f) * sp2C);
    temp_f2 = cosf((f32) (*(s32 *)((u8 *)arg0 + 0x80)) * 0.0000958738f) * sp20;
    (*(f32 *)((u8 *)arg0 + 0)) = temp_f2;
    (*(s32 *)((u8 *)arg0 + 0x7C)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x7C)) + (sp28 * D_800BE9E4));
    (*(s32 *)((u8 *)arg0 + 0x80)) = (s32) ((*(s32 *)((u8 *)arg0 + 0x80)) + (sp24 * D_800BE9E4));
    (*(s16 *)((u8 *)arg0 + 0x5C)) = (s16) ((*(s16 *)((u8 *)arg0 + 0x12)) - sp1E);
    (*(f32 *)((u8 *)arg0 + 0x60)) = (f32) (temp_f2 - sp18);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_15116940.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_15116A8C.s")

#ifdef NON_MATCHING
s32 func_15116E08(s32 arg0, s32 arg1, s32 arg2, u8 *arg3) {
    struct {
        f32 u1C;
        u8 pad20[0x4];
        f32 u24;
    } sp;

    sp.u1C = (f32) ((s32) (*(f32 *)((u8 *)arg3 + 0x14)) - arg0);
    sp.u24 = (f32) ((s32) (*(f32 *)((u8 *)arg3 + 0x1C)) - arg1);
    return (s32) ((*(f32 *)((u8 *)arg3 + 0x3C)) * func_15048A40(((0x40 - ((s32) (*(u16 *)((u8 *)arg3 + 0x76)) >> 8)) - func_150490A8(&sp.u1C, arg1, arg0)) & 0xFF));
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_15116E08.s")
#endif
void func_15116EA4(s32 arg0) {
}

typedef struct {
    u8 pad0[0x4F];
    u8 unk4F;
    u8 pad50[0x23];
    u8 unk73;
} struct_15116EB0;

typedef struct {
    u8 pad0[0x57];
    u8 unk57;
} struct_15116EB0_2;

typedef struct {
    u8 pad0[0x31C];
    struct_15116EB0_2 *unk31C;
} struct_15116EB0_1;

void func_15116EB0(struct_15116EB0 *arg0, struct_15116EB0_1 *arg1) {
    if (arg0->unk4F & 4) {
        if (!(arg0->unk73 & 3) && !(arg0->unk73 & 4)) {
            if (arg1->unk31C->unk57 == 1) {
                arg0->unk73 &= ~3;
                arg0->unk73 |= 2;
            }
        }
    }
}

void func_15116F04(u8 *arg0) {
    if (arg0[0x73] & 2) {
        func_15116F34(arg0);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_15116F34.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_1511712C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_151172FC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_15117424.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_15117858.s")

void func_15117A20(f32 *arg0) {
    arg0[2] = func_15117858(arg0, arg0[2]);
}

void func_15117A48(f32 *arg0) {
    arg0[1] = func_15117858(arg0, arg0[1]);
}

void func_15117A70(f32 *arg0) {
    arg0[0] = func_15117858(arg0, arg0[0]);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_15117A98.s")

void func_15117CF0(f32 *arg0) {
    arg0[0] = func_15117A98(arg0, arg0[0]);
}

void func_15117D18(f32 *arg0) {
    arg0[2] = func_15117A98(arg0, arg0[2]);
}

#ifdef NON_MATCHING
s32 func_15104A80(s32, s32, s32);

void func_15117D40(u8 *arg0) {
    s32 sp1C;
    s32 (*var_t0)(s32, s32, s32);
    s16 temp_v0_2;
    s16 temp_v0_3;
    s32 var_a1;
    s32 var_a2;
    s32 var_a3;
    s32 var_t1;
    s32 var_v0;
    u16 temp_v1;
    u8 temp_t9;
    u8 temp_v0;

    temp_v0 = (*(u8 *)((u8 *)arg0 + 0x73));
    temp_v1 = (*(u16 *)((u8 *)arg0 + 0x54));
    var_a1 = 0x28;
    var_t1 = 3;
    var_a2 = 0;
    var_t0 = NULL;
    var_a3 = temp_v0 & 3;
    if ((temp_v1 == 0x800B) && (D_800BE9F0 == 0xC)) {
        var_a1 = 0x22;
    } else if (D_800BE9F0 == 0x31) {
        var_a1 = 0x14;
        var_a2 = 1;
    } else if (D_800BE9F0 == 0xA) {
        var_a1 = 0x14;
        var_a2 = 1;
    } else if (D_800BE9F0 == 0x34) {
        var_a1 = 0xA;
        var_a2 = 1;
        var_t1 = 6;
        var_t0 = func_15104A80;
    } else if (temp_v1 == 4) {
        var_a1 = 0xF;
    }
    var_v0 = (*(s32 *)((u8 *)arg0 + 0x7C));
    if (var_v0 == 0) {
        var_v0 = (*(s16 *)((u8 *)arg0 + 0x12)) | 0x80000000;
        (*(s32 *)((u8 *)arg0 + 0x7C)) = var_v0;
    }
    if (var_a3 == 3) {
        temp_v0_2 = (s16) var_v0 - var_a1;
        if (temp_v0_2 != (*(s16 *)((u8 *)arg0 + 0x12))) {
            (*(s16 *)((u8 *)arg0 + 0x12)) = temp_v0_2;
        }
        if ((var_a2 != 0) && !((*(u8 *)((u8 *)arg0 + 0x4F)) & 4) && !(temp_v0 & 4)) {
            var_a3 = 1;
        }
    } else if (var_a3 == 0) {
        if ((s16) ((s16) var_v0 - var_a1) != (*(s16 *)((u8 *)arg0 + 0x12))) {
            (*(s16 *)((u8 *)arg0 + 0x12)) = (s16) var_v0;
        }
    } else if (var_a3 == 2) {
        temp_v0_3 = (s16) var_v0 - var_a1;
        (*(s16 *)((u8 *)arg0 + 0x12)) = (s16) ((*(s16 *)((u8 *)arg0 + 0x12)) - var_t1);
        if (temp_v0_3 >= (*(s16 *)((u8 *)arg0 + 0x12))) {
            (*(s16 *)((u8 *)arg0 + 0x12)) = temp_v0_3;
            var_a3 = 3;
            if (var_t0 != NULL) {
                sp1C = 3;
                var_t0(var_a1, var_a2, 3);
                var_a3 = 3;
            }
        }
    } else if (var_a3 == 1) {
        (*(s16 *)((u8 *)arg0 + 0x12)) = (s16) ((*(s16 *)((u8 *)arg0 + 0x12)) + 3);
        if ((*(s16 *)((u8 *)arg0 + 0x12)) >= (s16) var_v0) {
            (*(s16 *)((u8 *)arg0 + 0x12)) = (s16) var_v0;
            var_a3 = 0;
        }
    }
    temp_t9 = (*(u8 *)((u8 *)arg0 + 0x73)) & 0xFFFC;
    (*(u8 *)((u8 *)arg0 + 0x73)) = temp_t9;
    (*(u8 *)((u8 *)arg0 + 0x73)) = (u8) (temp_t9 | var_a3);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_15117D40.s")
#endif
#ifdef NON_MATCHING
s32 func_150AD9A0(s32, s32, s32);

void func_15117F3C(u8 *arg0) {
    s16 sp56;
    s16 sp54;
    s16 sp52;
    s16 sp50;
    s32 sp48;
    s32 sp3C;
    s32 sp38;
    f32 sp34;
    f32 sp30;
    f32 sp2C;
    f32 sp28;
    f32 sp24;
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f2;
    s16 var_v1_2;
    s32 temp_a0;
    s32 temp_a0_2;
    s32 temp_t1;
    s32 temp_t3;
    s32 temp_t6;
    s32 temp_t7;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 var_t0;
    s32 var_v1;
    u8 temp_t9;

    temp_v0 = (*(s32 *)((u8 *)arg0 + 0x3C));
    var_v1 = (*(s32 *)((u8 *)arg0 + 0x80));
    temp_t7 = temp_v0 >> 0x10;
    temp_t6 = (*(u8 *)((u8 *)arg0 + 0x73)) & 3;
    temp_t1 = temp_v0 & 0xFFFF;
    if (var_v1 == 0) {
        var_v1 = (*(s16 *)((u8 *)arg0 + 0x14)) | 0x80000000;
        (*(s32 *)((u8 *)arg0 + 0x7C)) = (s32) (((*(s16 *)((u8 *)arg0 + 0x10)) & 0xFFFF) | ((*(s16 *)((u8 *)arg0 + 0x12)) << 0x10));
        (*(s32 *)((u8 *)arg0 + 0x80)) = var_v1;
    }
    temp_v0_2 = (*(s32 *)((u8 *)arg0 + 0x7C));
    temp_t3 = temp_v0_2 >> 0x10;
    if (temp_t6 == 0) {
        (*(s16 *)((u8 *)arg0 + 0x10)) = (s16) temp_v0_2;
        (*(s16 *)((u8 *)arg0 + 0x12)) = (s16) temp_t3;
        (*(s16 *)((u8 *)arg0 + 0x14)) = (s16) var_v1;
        return;
    }
    sp52 = (s16) var_v1;
    sp54 = (s16) temp_t3;
    sp56 = (s16) temp_v0_2;
    sp38 = temp_t1;
    sp3C = temp_t6;
    sp50 = (s16) temp_t7;
    temp_v0_3 = func_150AD9A0((s16) temp_v0_2 - (*(s16 *)((u8 *)arg0 + 0x10)), (s16) temp_t3 - (*(s16 *)((u8 *)arg0 + 0x12)), (s16) var_v1 - (*(s16 *)((u8 *)arg0 + 0x14)));
    var_t0 = temp_t6;
    if (var_t0 == 3) {
        if ((s16) temp_t7 < 0) {
            sp48 = (s32) -(s16) temp_t7;
        } else {
            sp48 = (s32) (s16) temp_t7;
        }
        if ((temp_t1 != 0) && !((*(u8 *)((u8 *)arg0 + 0x4F)) & 4) && !((*(u8 *)((u8 *)arg0 + 0x73)) & 4)) {
            temp_a0 = (*(s32 *)((u8 *)arg0 + 0x84));
            if (D_800BE9E4 < temp_a0) {
                (*(s32 *)((u8 *)arg0 + 0x84)) = (s32) (temp_a0 - D_800BE9E4);
            } else {
                var_t0 = 1;
            }
        } else {
            (*(s32 *)((u8 *)arg0 + 0x84)) = temp_t1;
        }
    } else {
        temp_a0_2 = temp_v0_3 + 6;
        if (var_t0 == 2) {
            sp48 = temp_a0_2;
            if ((s16) temp_t7 < 0) {
                var_v1_2 = -(s16) temp_t7;
            } else {
                var_v1_2 = (s16) temp_t7;
            }
            if (temp_a0_2 >= var_v1_2) {
                var_t0 = 3;
                if ((s16) temp_t7 < 0) {
                    sp48 = (s32) -(s16) temp_t7;
                } else {
                    sp48 = (s32) (s16) temp_t7;
                }
                (*(s32 *)((u8 *)arg0 + 0x84)) = temp_t1;
            }
        } else if (var_t0 == 1) {
            if (temp_v0_3 < 3) {
                sp48 = 0;
                var_t0 = 0;
            } else {
                sp48 = temp_v0_3 - 3;
            }
        }
    }
    if (temp_v0_3 != sp48) {
        sp3C = var_t0;
        sp50 = (s16) temp_t7;
        sp34 = cosf((*(f32 *)((u8 *)arg0 + 0)) * 0.017453292f);
        sp30 = sinf((*(f32 *)((u8 *)arg0 + 0)) * 0.017453292f);
        sp2C = cosf((*(f32 *)((u8 *)arg0 + 4)) * 0.017453292f);
        sp28 = sinf((*(f32 *)((u8 *)arg0 + 4)) * 0.017453292f);
        sp24 = cosf((*(f32 *)((u8 *)arg0 + 8)) * 0.017453292f);
        temp_f0 = sinf((*(f32 *)((u8 *)arg0 + 8)) * 0.017453292f);
        if ((s16) temp_t7 < 0) {
            sp48 = -sp48;
        }
        temp_f12 = sp34 * sp28;
        temp_f2 = (f32) sp48;
        (*(s16 *)((u8 *)arg0 + 0x10)) = (s16) (s32) ((f32) sp56 + (temp_f2 * ((temp_f12 * sp24) + (sp30 * temp_f0))));
        (*(s16 *)((u8 *)arg0 + 0x12)) = (s16) (s32) ((f32) sp54 + (temp_f2 * ((temp_f12 * temp_f0) - (sp30 * sp24))));
        (*(s16 *)((u8 *)arg0 + 0x14)) = (s16) (s32) ((f32) sp52 + (temp_f2 * sp34 * sp2C));
    }
    temp_t9 = (*(u8 *)((u8 *)arg0 + 0x73)) & 0xFFFC;
    (*(u8 *)((u8 *)arg0 + 0x73)) = temp_t9;
    (*(u8 *)((u8 *)arg0 + 0x73)) = (u8) (temp_t9 | var_t0);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_15117F3C.s")
#endif
void func_151182BC(u8 *arg0, u8 *arg1) {
    s32 lo = *(s32 *)(arg0 + 0x3C) & 0xFFFF;
    s32 f;
    if (*(s32 *)arg1 == 1 && (arg0[0x4F] & 4)) {
        f = arg0[0x73];
        if (!(f & 3) && !(f & 4) && (lo == 0 || (*(u8 **)(arg1 + 0x31C))[0x57] == 1)) {
            arg0[0x73] = f & 0xFFFC;
            arg0[0x73] |= 2;
        }
    }
}

#ifdef NON_MATCHING
void func_15118324(u8 *arg0, f32 arg1, f32 arg2, f32 arg3, u8 *arg4) {
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f10;
    f32 temp_f12;
    f32 temp_f20;
    f32 temp_f20_2;
    f32 temp_f22;
    f32 temp_f22_2;
    f32 temp_f2;
    f32 var_f14;
    u8 *temp_v0;
    u8 *var_s0;

    var_f14 = arg2;
    var_s0 = arg0;
    if (((*(u16 *)((u8 *)var_s0 + 0x54)) == 0x8006) && (D_800BE9F0 == 0x35)) {
        temp_v0 = func_151149AC(0xFDU);
        var_s0 = temp_v0;
        func_1511F8A4(temp_v0);
        var_f14 = -555.0f;
        arg1 = 0.0f;
        arg3 = 0.0f;
    }
    arg2 = var_f14;
    temp_f20 = (*(f32 *)((u8 *)var_s0 + 0)) * 0.017453292f;
    temp_f22 = sinf(temp_f20);
    temp_f0 = cosf(temp_f20);
    temp_f10 = arg2 * temp_f0;
    (*(f32 *)((u8 *)arg4 + 0)) = arg1;
    (*(f32 *)((u8 *)arg4 + 4)) = (f32) (temp_f10 - (arg3 * temp_f22));
    (*(f32 *)((u8 *)arg4 + 8)) = (f32) ((arg2 * temp_f22) + (arg3 * temp_f0));
    temp_f20_2 = (*(f32 *)((u8 *)var_s0 + 4)) * 0.017453292f;
    temp_f22_2 = sinf(temp_f20_2);
    temp_f0_2 = cosf(temp_f20_2);
    temp_f12 = (*(f32 *)((u8 *)arg4 + 8));
    temp_f2 = (*(f32 *)((u8 *)arg4 + 0));
    (*(f32 *)((u8 *)arg4 + 0)) = (f32) ((temp_f12 * temp_f22_2) + (temp_f2 * temp_f0_2));
    (*(f32 *)((u8 *)arg4 + 8)) = (f32) ((temp_f12 * temp_f0_2) + (-temp_f2 * temp_f22_2));
    (*(f32 *)((u8 *)arg4 + 0)) = (f32) ((*(f32 *)((u8 *)arg4 + 0)) + (f32) (*(s16 *)((u8 *)var_s0 + 0x10)));
    (*(f32 *)((u8 *)arg4 + 4)) = (f32) ((*(f32 *)((u8 *)arg4 + 4)) + (f32) (*(s16 *)((u8 *)var_s0 + 0x12)));
    (*(f32 *)((u8 *)arg4 + 8)) = (f32) ((*(f32 *)((u8 *)arg4 + 8)) + (f32) (*(s16 *)((u8 *)var_s0 + 0x14)));
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_15118324.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_151184BC.s")

void func_15118EEC(s32 arg0) {
    func_15118F2C(arg0, 0);
}

void func_15118F0C(s32 arg0) {
    func_15118F2C(arg0, 3);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_15118F2C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_151194A4.s")

void func_1511992C(u8 *arg0, s32 *arg1) {
    if ((arg1[0] == 1) && (((u8 *)arg1)[0x65] == 0) && !(arg0[0x73] & 3) && !(arg0[0x73] & 4)) {
        arg0[0x73] &= ~3;
        arg0[0x73] |= 2;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_15119974.s")

#ifdef NON_MATCHING
void func_15119A54(u8 *arg0, u8 *arg1, s32 arg2, u16 arg3) {
    s8 *sp4C;
    u32 sp44;
    s16 temp_v0;
    s16 temp_v1_2;
    s32 var_s1_2;
    s32 var_v0_2;
    s8 *var_t0;
    s8 var_v0;
    u32 temp_v1;
    u32 var_s0;
    u32 var_s0_2;
    u32 var_s1;
    u32 var_s5;
    u8 *temp_a1;
    u8 *temp_a1_2;

    var_t0 = (*(s8 **)((u8 *)arg0 + 0x1C));
    var_v0 = *var_t0;
    var_s5 = sp44;
    if (var_v0 != -0x21) {
        do {
            switch (var_v0) {                       /* irregular */
            case 1:
                var_s5 = (u32) ((*(u32 *)((u8 *)var_t0 + 4)) & 0xFFFFFF) >> 4;
                break;
            case 5:
                sp4C = var_t0;
                temp_v1 = (*(u32 *)((u8 *)var_t0 + 4));
                var_v0_2 = 0;
                var_s1 = 0;
                var_s0 = temp_v1;
                do {
                    temp_a1 = (*(s32 *)((u8 *)arg0 + 0x28)) + ((((u32) (var_s0 & 0xFF) / 10U) + var_s5) * 0x10);
                    var_s1 += 1;
                    if (((*(s16 *)((u8 *)temp_a1 + 0)) == (*(s16 *)((u8 *)arg1 + 0))) && ((*(s16 *)((u8 *)temp_a1 + 2)) == (*(s16 *)((u8 *)arg1 + 2))) && ((*(s16 *)((u8 *)temp_a1 + 4)) == (*(s16 *)((u8 *)arg1 + 4)))) {
                        var_v0_2 = 1;
                        (*(u16 *)((u8 *)temp_a1 + 6)) = arg3;
                    } else {
                        var_s0 = var_s0 >> 8;
                    }
                } while (var_s1 < 3U);
                var_s0_2 = temp_v1;
                if (var_v0_2 != 0) {
                    var_s1_2 = 0;
                    do {
                        temp_a1_2 = (*(s32 *)((u8 *)arg0 + 0x28)) + ((((u32) (var_s0_2 & 0xFF) / 10U) + var_s5) * 0x10);
                        if ((*(u16 *)((u8 *)temp_a1_2 + 6)) == 0) {
                            temp_v1_2 = (*(s16 *)((u8 *)temp_a1_2 + 4));
                            temp_v0 = (*(s16 *)((u8 *)temp_a1_2 + 0));
                            if (arg2 < ((temp_v1_2 * temp_v1_2) + (temp_v0 * temp_v0))) {
                                (*(u16 *)((u8 *)temp_a1_2 + 6)) = arg3;
                                func_15119A54(arg0, temp_a1_2, arg2, arg3);
                            }
                        }
                        var_s1_2 += 1;
                        var_s0_2 = var_s0_2 >> 8;
                    } while (var_s1_2 != 3);
                }
                var_t0 = sp4C;
                break;
            }
            var_v0 = (*(s8 *)((u8 *)var_t0 + 8));
            var_t0 += 8;
        } while (var_v0 != -0x21);
        sp44 = var_s5;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_15119A54.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_15119C54.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_15119EB8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_1511A540.s")

#ifdef NON_MATCHING
s32 func_1511A998(s8 *arg0, s32 *arg1) {
    struct {
        s32 uC;
        s32 u10;
        u8 pad14[0x4];
    } sp;
    s32 var_v0;
    s32 var_v1;
    s8 var_a1;

    sp.uC = 0;
    sp.u10 = 0;
    var_v0 = 0;
    var_v1 = 0;
    if (*arg0 != -0x21) {
        var_a1 = *((0 * 8) + arg0);
loop_2:
        if (var_a1 == -3) {
            (&sp.uC)[var_v0] = var_v1;
            var_v0 += 1;
        }
        var_v1 += 1;
        var_a1 = *((var_v1 * 8) + arg0);
        if ((var_a1 != -0x21) && (var_v0 < 2)) {
            goto loop_2;
        }
    }
    *arg1 = sp.u10;
    return sp.uC;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_1511A998.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_1511AA1C.s")

void func_1511AC84(u8 *arg0) {
    if (*(s32 *)(arg0 + 0x3C) != 0) {
        func_15116690(arg0);
    }
    func_1511AA1C(arg0, arg0 + 0x80, arg0 + 0x84);
}

s32 func_15022BB0(s32, s32);
s32 func_15116854(u8 *);

void func_1511ACC0(u8 *arg0) {
    if ((D_800C35EA == 1) && (func_15022BB0((arg0 - (u8 *)D_800DBEF4) / 160, 0) != 0)) {
        *(s32 *)(arg0 + 0x7C) = 0;
        *(f32 *)(arg0 + 0x18) = 0.0f;
    }
    func_15116854(arg0);
    func_1511AA1C(arg0, arg0 + 0x80, arg0 + 0x84);
}

void func_1511AD48(u8 *arg0) {
    s32 var_a1;
    s32 var_v1;
    u8 *temp_v0;
    temp_v0 = (*(u8 **)((u8 *)arg0 + 0x80));
    (*(s8 *)((u8 *)temp_v0 + 0x1E)) = 1;
    (*(f32 *)((u8 *)temp_v0 + 0x10)) = 0.0f;
    (*(s8 *)((u8 *)temp_v0 + 0x1C)) = 0;
    (*(s8 *)((u8 *)temp_v0 + 0x1D)) = 7;
    (*(f32 *)((u8 *)temp_v0 + 0x14)) = 260.0f;
    (*(f32 *)((u8 *)temp_v0 + 0x18)) = 100.0f;
    var_v1 = 0;
    var_a1 = 0;
    if ((s32) (*(u16 *)((u8 *)arg0 + 0x16)) > 0) {
        do {
            var_v1 += 1;
            *(f32 *)((*(s32 *)((u8 *)temp_v0 + 4)) + var_a1) = 0.0f;
            var_a1 += 4;
        } while (var_v1 < (s32) (*(u16 *)((u8 *)arg0 + 0x16)));
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_1511ADC0.s")

#ifdef NON_MATCHING
extern f32 D_800A3558;
extern f32 D_800A355C;
extern f32 D_800A3564;
void func_1511B4B8(u8 *arg0) {
    u32 temp_hi;
    s32 var_v0;
    f32 temp_f2;
    f32 temp_f14;
    f32 temp_f12;
    f32 temp_f0_2;
    f32 temp_f0;
    f32 sp1C;

    temp_f0 = (f32) (*(s32 *)((u8 *)arg0 + 0x3C));
    temp_f14 = (*(f32 *)((u8 *)arg0 + 0x7C));
    temp_f12 = 75.0f * temp_f0 * D_800A3558;
    if (temp_f12 != temp_f14) {
        temp_f2 = temp_f12 - temp_f14;
        if (fabsf(temp_f2) < 1.0f) {
            (*(f32 *)((u8 *)arg0 + 0x7C)) = temp_f12;
        } else {
            var_v0 = 1;
            if (temp_f2 < 0.0f) {
                var_v0 = -1;
            }
            (*(f32 *)((u8 *)arg0 + 0x7C)) = (f32) (temp_f14 + (f32) var_v0);
        }
        (*(f32 *)((u8 *)arg0 + 0x80)) = 0.0f;
    } else {
        sp1C = temp_f0;
        temp_hi = func_150ADA20() % 1000U;
        if ((s32) temp_hi < 0x1F4) {
            (*(f32 *)((u8 *)arg0 + 0x84)) = (f32) ((f32) temp_hi * 5.0f * sp1C * D_800A355C * D_800A3558);
        }
        temp_f0_2 = (*(f32 *)((u8 *)arg0 + 0x80));
        (*(f32 *)((u8 *)arg0 + 0x80)) = (f32) (temp_f0_2 + (((*(f32 *)((u8 *)arg0 + 0x84)) - temp_f0_2) * D_800A3564));
    }
    (*(f32 *)((u8 *)arg0 + 0)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x7C)) + (*(f32 *)((u8 *)arg0 + 0x80)));
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_1511B4B8.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_1511B604.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_1511BAA4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_1511BD5C.s")

#ifdef NON_MATCHING
void func_15188580(s32, f32 *);

void func_1511BFAC(u8 *arg0) {
    struct {
        f32 u1C;
    } sp;
    u32 temp_t7;

    sp.u1C = 0.0f;
    func_15188580((*(s32 *)((u8 *)arg0 + 0x3C)), &sp.u1C);
    temp_t7 = (u32) (sp.u1C * 255.0f);
    (*(s8 *)((u8 *)arg0 + 0x8A)) = (s8) temp_t7;
    if (!(temp_t7 & 0xFF)) {
        (*(s8 *)((u8 *)arg0 + 0x8A)) = 1;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_1511BFAC.s")
#endif
#ifdef NON_MATCHING
extern f32 D_800A35A0;
extern f32 D_800A35A4;
extern f32 D_800A35A8;
s16 *allocate_memory(s32, s32, s32, s32);

s32 func_1511C08C(u8 *arg0, s32 arg1, s32 arg2, f32 arg3, f32 arg4) {
    f32 temp_f4;
    f32 var_f14;
    f32 var_f16;
    s16 *temp_a0;
    s16 *temp_a1;
    s16 *temp_v0;
    s16 *var_a2;
    s16 *var_v0;
    s16 temp_t6_2;
    s32 var_a3;
    s32 var_a3_2;
    s32 var_v1;
    s32 var_v1_2;
    u8 *temp_a0_2;
    u8 *temp_a0_3;
    u8 *temp_a1_2;
    u8 *temp_a1_3;
    u8 *temp_t0;
    u8 *temp_t2;
    u8 *temp_t4;
    u8 *temp_t6;
    u8 *temp_t8;

    if ((*(s16 **)((u8 *)arg0 + 0x7C)) == NULL) {
        temp_v0 = allocate_memory((*(u16 *)((u8 *)arg0 + 0x16)) * 4, 1, 0, 0);
        (*(s16 **)((u8 *)arg0 + 0x7C)) = temp_v0;
        var_a3 = 0;
        var_v1 = 0;
        if ((s32) (*(u16 *)((u8 *)arg0 + 0x16)) > 0) {
            var_a2 = temp_v0;
            do {
                var_a3 += 1;
                var_a2 = (s16 *)((u8 *)var_a2 + (4));
                (*(s16 *)((u8 *)var_a2 + -4)) = (s16) (*(s16 *)((u8 *)(((*(s32 *)((u8 *)arg0 + 0x28)) + var_v1)) + 8));
                (*(s16 *)((u8 *)var_a2 + -2)) = (s16) (*(s16 *)((u8 *)(((*(s32 *)((u8 *)arg0 + 0x28)) + var_v1)) + 0xA));
                temp_t8 = (*(s32 *)((u8 *)arg0 + 0x28)) + var_v1;
                temp_t6 = (*(s32 *)((u8 *)arg0 + 0x20)) + var_v1;
                (*(s32 *)((u8 *)temp_t6 + 0)) = (s32) (*(s32 *)((u8 *)temp_t8 + 0));
                (*(s32 *)((u8 *)temp_t6 + 4)) = (s32) (*(s32 *)((u8 *)temp_t8 + 4));
                (*(s32 *)((u8 *)temp_t6 + 8)) = (s32) (*(s32 *)((u8 *)temp_t8 + 8));
                (*(s32 *)((u8 *)temp_t6 + 0xC)) = (s32) (*(s32 *)((u8 *)temp_t8 + 0xC));
                temp_t4 = (*(s32 *)((u8 *)arg0 + 0x28)) + var_v1;
                temp_t2 = (*(s32 *)((u8 *)arg0 + 0x24)) + var_v1;
                (*(s32 *)((u8 *)temp_t2 + 0)) = (s32) (*(s32 *)((u8 *)temp_t4 + 0));
                (*(s32 *)((u8 *)temp_t2 + 4)) = (s32) (*(s32 *)((u8 *)temp_t4 + 4));
                (*(s32 *)((u8 *)temp_t2 + 8)) = (s32) (*(s32 *)((u8 *)temp_t4 + 8));
                (*(s32 *)((u8 *)temp_t2 + 0xC)) = (s32) (*(s32 *)((u8 *)temp_t4 + 0xC));
                temp_a0 = (*(s32 *)((u8 *)arg0 + 0x20)) + var_v1;
                *temp_a0 += (*(s16 *)((u8 *)arg0 + 0x10));
                temp_a0_2 = (*(s32 *)((u8 *)arg0 + 0x20)) + var_v1;
                (*(s16 *)((u8 *)temp_a0_2 + 2)) = (s16) ((*(s16 *)((u8 *)temp_a0_2 + 2)) + (*(s16 *)((u8 *)arg0 + 0x12)));
                temp_a0_3 = (*(s32 *)((u8 *)arg0 + 0x20)) + var_v1;
                (*(s16 *)((u8 *)temp_a0_3 + 4)) = (s16) ((*(s16 *)((u8 *)temp_a0_3 + 4)) + (*(s16 *)((u8 *)arg0 + 0x14)));
                temp_a1 = (*(s32 *)((u8 *)arg0 + 0x24)) + var_v1;
                *temp_a1 += (*(s16 *)((u8 *)arg0 + 0x10));
                temp_a1_2 = (*(s32 *)((u8 *)arg0 + 0x24)) + var_v1;
                (*(s16 *)((u8 *)temp_a1_2 + 2)) = (s16) ((*(s16 *)((u8 *)temp_a1_2 + 2)) + (*(s16 *)((u8 *)arg0 + 0x12)));
                temp_a1_3 = (*(s32 *)((u8 *)arg0 + 0x24)) + var_v1;
                temp_t6_2 = (*(s16 *)((u8 *)temp_a1_3 + 4));
                var_v1 += 0x10;
                (*(s16 *)((u8 *)temp_a1_3 + 4)) = (s16) (temp_t6_2 + (*(s16 *)((u8 *)arg0 + 0x14)));
            } while (var_a3 < (s32) (*(u16 *)((u8 *)arg0 + 0x16)));
        }
    }
    var_a3_2 = 0;
    var_f14 = 1.0f;
    var_f16 = 1.0f;
    if (arg3 != 1.0f) {
        var_f14 = 1.0f / arg3;
    }
    var_v1_2 = 0;
    if (arg4 != 1.0f) {
        var_f16 = 1.0f / arg4;
    }
    var_v0 = (*(s16 **)((u8 *)arg0 + 0x7C));
    if ((s32) (*(u16 *)((u8 *)arg0 + 0x16)) > 0) {
        do {
            var_a3_2 += 1;
            temp_f4 = (f32) *var_v0;
            var_v0 = (s16 *)((u8 *)var_v0 + (4));
            (*(s16 *)((u8 *)(((*(s32 *)((u8 *)((arg0 + (D_800BE9C0 * 4))) + 0x20)) + var_v1_2)) + 8)) = (s16) (s32) (((temp_f4 + ((-((*(f32 *)&(arg1)) - ((f32) (*(s16 *)((u8 *)arg0 + 0x10)) + D_800A35A0)) * D_800A35A8) - 1024.0f)) * var_f14) + 1024.0f);
            temp_t0 = (*(s32 *)((u8 *)((arg0 + (D_800BE9C0 * 4))) + 0x20)) + var_v1_2;
            var_v1_2 += 0x10;
            (*(s16 *)((u8 *)temp_t0 + 0xA)) = (s16) (s32) ((((f32) (*(s16 *)((u8 *)var_v0 + -2)) + ((((*(f32 *)&(arg2)) - ((f32) (*(s16 *)((u8 *)arg0 + 0x14)) + D_800A35A4)) * D_800A35A8) - 1024.0f)) * var_f16) + 1024.0f);
        } while (var_a3_2 < (s32) (*(u16 *)((u8 *)arg0 + 0x16)));
    }
    return (s32) var_v0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_1511C08C.s")
#endif
s32 func_1511C08C(u8 *, s32, s32, f32, f32);
void func_1511C37C(u8 *arg0)
{
  u8 *v;
  u8 *s;
  s = *(u8 **)(arg0 + 0x80);
  if (s != NULL) {
    v = s;
  } else {
    v = (u8 *)func_15083E90(arg0[0x3F]);
  }
  if (v != NULL) {
    func_1511C08C(arg0, *(s32 *)(v + 0x14), *(s32 *)(v + 0x1C), 1.0f, 1.0f);
  }
}

void func_1511C3E4(u8 *arg0) {
    *(f32 *)(arg0 + 4) = func_150484A0(*(s16 *)(arg0 + 0x10) - *(f32 *)((u8 *)D_800DBFF0 + 0x2F8),
                                       *(s16 *)(arg0 + 0x14) - *(f32 *)((u8 *)D_800DBFF0 + 0x300)) * 57.295776f;
}

#ifdef NON_MATCHING
void func_15060A30(s32, void *);
void func_150DE450(u8 *);

void func_1511C444(u8 *arg0) {
    f32 sp7C;
    f32 sp78;
    f32 sp74;
    s16 sp72;
    s32 sp5C;
    s32 sp48;
    f32 sp44;
    s32 sp40;
    s32 sp3C;
    f32 sp38;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f12;
    f32 temp_f16;
    f32 temp_f2;
    f32 temp_f4;
    f32 temp_f4_2;
    s16 temp_v0_5;
    s16 var_a3;
    s32 temp_t4;
    s32 temp_t9;
    s32 temp_v0_2;
    s32 var_a0;
    s32 var_t0;
    s32 var_t1;
    s32 var_t2;
    s32 var_v0;
    s32 var_v0_2;
    struct108 *var_a1;
    struct126 *temp_v0_4;
    struct127 *temp_v0_3;
    struct127 *var_s1;
    struct127 *var_v1;
    u8 temp_t6;
    u8 temp_v0;

    func_1511C3E4(arg0);
    temp_v0 = (*(u8 *)((u8 *)arg0 + 0x73));
    var_t1 = (*(s32 *)((u8 *)arg0 + 0x80));
    var_t2 = temp_v0 & 3;
    temp_t4 = temp_v0 & 4;
    sp38 = (*(f32 *)((u8 *)arg0 + 0x84));
    if (D_800BE9F0 == 0xA) {
        temp_f0 = (*(f32 *)((u8 *)arg0 + 0x34)) * 100.0f;
        sp44 = temp_f0 * temp_f0;
        if ((*(s32 *)((u8 *)arg0 + 0x7C)) == 0) {
            if ((*(s16 *)((u8 *)arg0 + 0x12)) == 0) {
                (*(s16 *)((u8 *)arg0 + 0x12)) = 1;
            }
            (*(s32 *)((u8 *)arg0 + 0x7C)) = (s32) ((*(s16 *)((u8 *)arg0 + 0x12)) & 0xFFFF);
            if (var_t2 == 3) {
                (*(s16 *)((u8 *)arg0 + 0x12)) = (*(s16 *)((u8 *)arg0 + 0x12));
            }
        }
        temp_v0_2 = (*(s32 *)((u8 *)arg0 + 0x7C));
        var_a3 = (s16) temp_v0_2;
        var_s1 = NULL;
        sp74 = (f32) (*(s16 *)((u8 *)arg0 + 0x10));
        var_t0 = temp_v0_2 >> 0x10;
        sp78 = (f32) (*(s16 *)((u8 *)arg0 + 0x12)) + -729.0f;
        sp7C = (f32) (*(s16 *)((u8 *)arg0 + 0x14));
        if ((var_t2 != 3) && (var_t2 != 1)) {
            var_a0 = 0;
            if (D_8008FD8C > 0) {
                var_a1 = D_800DBFF0;
loop_10:
                var_a0 += 0x9A0;
                if ((s32) var_a1->unk3D4->unk6B >= 4) {
                    var_v0 = D_8008FD8C * 0x4D;
                    goto block_16;
                }
                temp_v0_3 = var_a1->unk3D0;
                temp_f16 = temp_v0_3->y_position;
                if (((temp_f16 + 40.0f) < sp78) && (temp_f0_2 = (temp_f16 + (f32) temp_v0_3->unkE6) - sp78, temp_f2 = temp_v0_3->z_position - sp7C, temp_f12 = temp_v0_3->x_position - sp74, (((temp_f2 * temp_f2) + ((temp_f12 * temp_f12) + (temp_f0_2 * temp_f0_2))) < sp44))) {
                    var_s1 = temp_v0_3;
                } else {
                    var_v0 = D_8008FD8C * 0x4D;
block_16:
                    var_a1 += 0x9A0;
                    if (var_a0 < (var_v0 << 5)) {
                        goto loop_10;
                    }
                }
            }
        }
        if ((var_s1 == NULL) && ((var_t2 == 2) || (var_t2 == 1))) {
            var_v1 = D_800CC2D0;
            var_v0_2 = 0;
            if (D_8008FD8C > 0) {
loop_21:
                var_v0_2 += 1;
                if (var_v1->unk31C->unk6B != 0) {
                    var_s1 = var_v1;
                } else {
                    var_v1 += 0x32C;
                    if (var_v0_2 < D_8008FD8C) {
                        goto loop_21;
                    }
                }
            }
        }
        if ((var_s1 != NULL) || (var_t2 == 2)) {
            if ((var_s1 != NULL) && (var_t1 == 0)) {
                sp72 = var_a3;
                sp48 = var_t0;
                sp3C = var_t1;
                sp5C = var_t2;
                sp40 = temp_t4;
                func_15060A30(0x16B, var_s1);
            }
            if (temp_t4 == 0) {
                var_t2 = 2;
                if (var_t1 == 0) {
                    var_t0 = 0x32;
                    var_t1 += 1;
                    if (func_150DE450 != NULL) {
                        sp72 = var_a3;
                        sp48 = 0x32;
                        sp3C = var_t1;
                        sp5C = 2;
                        func_150DE450(arg0);
                        var_t0 = 0x32;
                        var_t2 = 2;
                    }
                }
                if (var_s1 != NULL) {
                    if (var_t0 != 0) {
                        var_s1->unk31C->unk6B = 1;
                    } else {
                        var_s1->unk31C->unk6B = 2;
                    }
                }
                if (var_t0 != 0) {
                    if (D_800BE9E4 < var_t0) {
                        var_t0 -= D_800BE9E4;
                    } else {
                        sp5C = 2;
                        sp3C = var_t1;
                        sp48 = 0;
                        func_10010F88(0x1A4, 0x7FFFU, 0, 0U, 0, (s16) (s32) (*(s16 *)((u8 *)arg0 + 0x10)), (s16) (s32) (*(s16 *)((u8 *)arg0 + 0x12)), (s16) (s32) (*(s16 *)((u8 *)arg0 + 0x14)), 0x5DC, 0xDAC);
                        var_t0 = sp48;
                        goto block_45;
                    }
                } else {
                    temp_f4 = sp38 + 1.0f;
                    sp38 = temp_f4;
                    (*(s16 *)((u8 *)arg0 + 0x12)) = (s16) (s32) ((f32) (*(s16 *)((u8 *)arg0 + 0x12)) - temp_f4);
                    temp_f0_3 = (f32) var_a3 - 300.0f;
                    if ((f32) (*(s16 *)((u8 *)arg0 + 0x12)) <= temp_f0_3) {
                        (*(s16 *)((u8 *)arg0 + 0x12)) = (s16) (s32) temp_f0_3;
                        sp38 = 0.0f;
                        if (var_s1 != NULL) {
                            var_s1->unk31C->unk6B = 0;
                        }
                        sp5C = 3;
                        sp3C = 0;
                        sp48 = var_t0;
                        func_10010F88(0x1A5, 0x7FFFU, 0, 0U, 0, (s16) (s32) (*(s16 *)((u8 *)arg0 + 0x10)), (s16) (s32) (*(s16 *)((u8 *)arg0 + 0x12)), (s16) (s32) (*(s16 *)((u8 *)arg0 + 0x14)), 0x5DC, 0xDAC);
                        var_t1 = 0;
block_45:
                        var_t2 = sp5C;
                    }
                }
                if (var_s1 != NULL) {
                    (*(s16 *)((u8 *)(var_s1->unk31C) + 0x6C)) = (s16) (s32) sp74;
                    (*(s16 *)((u8 *)(var_s1->unk31C) + 0x6E)) = (s16) (s32) sp78;
                    (*(s16 *)((u8 *)(var_s1->unk31C) + 0x70)) = (s16) (s32) sp7C;
                }
            } else if (var_s1 != NULL) {
                if ((var_t1 == 0) && (var_s1->unk31C->unk6B == 0)) {
                    var_t0 = 0x32;
                    var_t1 += 1;
                }
                temp_v0_4 = var_s1->unk31C;
                if (var_t0 != 0) {
                    temp_v0_4->unk6B = 3;
                } else if (temp_v0_4->unk6B == 3) {
                    temp_v0_4->unk6B = 4;
                    var_t1 = 0;
                }
                if (var_t0 != 0) {
                    if (D_800BE9E4 < var_t0) {
                        var_t0 -= D_800BE9E4;
                    } else {
                        var_t0 = 0;
                    }
                }
            }
            if (var_s1 != NULL) {
                (*(s16 *)((u8 *)(var_s1->unk31C) + 0x6C)) = (s16) (s32) sp74;
                (*(s16 *)((u8 *)(var_s1->unk31C) + 0x6E)) = (s16) (s32) sp78;
                (*(s16 *)((u8 *)(var_s1->unk31C) + 0x70)) = (s16) (s32) sp7C;
            }
        } else if (!(temp_v0 & 8) || (var_t2 == 1)) {
            temp_v0_5 = (*(s16 *)((u8 *)arg0 + 0x12));
            if (temp_v0_5 < var_a3) {
                if (var_t1 == 0) {
                    var_t1 += 1;
                }
                var_t2 = 1;
                temp_f4_2 = sp38 + 1.3f;
                sp38 = temp_f4_2;
                (*(s16 *)((u8 *)arg0 + 0x12)) = (s16) (s32) ((f32) temp_v0_5 + temp_f4_2);
                if ((*(s16 *)((u8 *)arg0 + 0x12)) >= var_a3) {
                    (*(s16 *)((u8 *)arg0 + 0x12)) = var_a3;
                    var_t1 = 0;
                    var_t2 = 0;
                    sp38 = 0.0f;
                }
            }
            if (var_s1 != NULL) {
                var_s1->unk31C->unk6B = 0;
            }
        }
        (*(s32 *)((u8 *)arg0 + 0x80)) = var_t1;
        temp_t6 = (*(u8 *)((u8 *)arg0 + 0x73)) & 0xFFFC;
        (*(u8 *)((u8 *)arg0 + 0x73)) = temp_t6;
        (*(u8 *)((u8 *)arg0 + 0x73)) = (u8) (temp_t6 | var_t2);
        temp_t9 = (*(s32 *)((u8 *)arg0 + 0x7C)) & 0xFFFF;
        (*(s32 *)((u8 *)arg0 + 0x7C)) = temp_t9;
        (*(s32 *)((u8 *)arg0 + 0x7C)) = (s32) (temp_t9 | (var_t0 << 0x10));
        (*(f32 *)((u8 *)arg0 + 0x84)) = sp38;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_1511C444.s")
#endif
void func_1511CAC8(void) {
}

void func_1511CAD0(u8 *arg0) {
    f32 temp_f8;
    f32 sp20;

    sp20 = sinf((*(f32 *)((u8 *)arg0 + 0x80)));
    temp_f8 = sinf((*(f32 *)((u8 *)arg0 + 0x84))) * 16.0f;
    (*(f32 *)((u8 *)arg0 + 0)) = (f32) (sp20 * 16.0f);
    (*(f32 *)((u8 *)arg0 + 8)) = temp_f8;
    (*(f32 *)((u8 *)arg0 + 0x80)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x80)) + (0.073f * D_800BE9A4));
    (*(f32 *)((u8 *)arg0 + 0x84)) = (f32) ((*(f32 *)((u8 *)arg0 + 0x84)) + (0.065f * D_800BE9A4));
    (*(f32 *)((u8 *)arg0 + 0x80)) = func_15144B68((*(f32 *)((u8 *)arg0 + 0x80)));
    {
        s32 blk_t; // fakematch: block boundary keeps the 0x84 store before the compare load
        (*(f32 *)((u8 *)arg0 + 0x84)) = func_15144B68((*(f32 *)((u8 *)arg0 + 0x84)));
    }
    if (((*(f32 *)((u8 *)arg0 + 8)) == 0.0f) && ((*(f32 *)((u8 *)arg0 + 0x84)) == 0.0f)) {
        (*(f32 *)((u8 *)arg0 + 0)) = 7.5f;
        (*(f32 *)((u8 *)arg0 + 8)) = 8.0f;
    }
}

#ifdef NON_MATCHING
s32 func_150B2C20(s32, s32);
s32 func_151714BC(u8 *, s32, s32, s32);
void func_151741D0(s32, s32);
extern s32 D_800A3354;
s32 func_1000EC24(s32, s32, s32, s32, s32, s32, s32); /* a function (init_EB00.c), not data */

void func_1511CBC0(u8 *arg0) {
    struct {
        u8 * u50;
        u8 pad54[0x4];
        u16 u58;
        u16 u5A;
        u8 * u5C;
        u8 pad60[0x4];
        s32 u64;
    } sp;
    u8 *sp48;
    s32 *sp44;
    s32 temp_a1;
    s32 temp_a1_2;
    s32 temp_t6_2;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v1;
    u16 temp_t1;
    u32 temp_hi;
    u32 temp_t5;
    u32 temp_t9;
    u8 temp_t6_3;
    u8 *temp_t6;
    u8 *temp_v0;

    sp.u64 = (*(u8 *)((u8 *)arg0 + 0x73)) & 3;
    if (D_800BE9F0 == 4) {
        sp.u5C = arg0 + 0x140;
    } else {
        sp.u5C = NULL;
    }
    if (sp.u64 == 1) {
        sp.u64 = 0;
        (*(s8 *)((u8 *)arg0 + 0x8A)) = 0;
        (*(s8 *)((u8 *)arg0 + 0x10E)) = 0;
        if (sp.u5C != NULL) {
            (*(s8 *)((u8 *)sp.u5C + 0x6E)) = 0;
        }
        temp_a1 = (*(s32 *)((u8 *)arg0 + 0x3C));
        if (temp_a1 != 0xFF) {
            func_151741D0(0, temp_a1);
        }
    }
    if (D_800BE9B4 != 0) {
        temp_v0 = arg0 + 0xA0;
        if (sp.u64 == 3) {
            (*(s8 *)((u8 *)arg0 + 0x8A)) = 0xFF;
            (*(s8 *)((u8 *)temp_v0 + 0x6E)) = 1;
            if (sp.u5C != NULL) {
                (*(s8 *)((u8 *)sp.u5C + 0x6E)) = 1;
            }
        } else {
            (*(s8 *)((u8 *)arg0 + 0x8A)) = 0;
            (*(s8 *)((u8 *)temp_v0 + 0x6E)) = 0;
            if (sp.u5C != NULL) {
                (*(s8 *)((u8 *)sp.u5C + 0x6E)) = 0;
            }
        }
    }
    if (sp.u64 == 2) {
        temp_v0_2 = (*(s32 *)((u8 *)arg0 + 0x7C));
        temp_t6 = arg0 + 0xA0;
        if (temp_v0_2 < 0) {
            (*(s32 *)((u8 *)arg0 + 0x7C)) = (s32) (temp_v0_2 + D_800BE9E4);
        } else {
            sp48 = temp_t6;
            if ((*(s32 *)((u8 *)arg0 + 0x80)) == 0) {
                temp_v1 = (*(s32 *)((u8 *)temp_t6 + 0x3C));
                temp_v0_3 = temp_v1 & 0xFF;
                switch (temp_v0_3) {                /* irregular */
                case 2:
                    break;
                case 1:
                    func_151714BC(sp48, 0xFF, 0, 1);
                    func_10010F30(0x2BE, 0x7FFFU, 0x40U, 0, 0U);
                    break;
                case 0:
                    temp_t9 = func_150ADA20() % 3U;
                    (*(s32 *)((u8 *)(&sp.u50[0]) + 0)) = (s32) (*(s32 *)((u8 *)(&D_800A3354) + 0));
                    (*(u16 *)((u8 *)(&sp.u50[0]) + 4)) = (u16) (*(u16 *)((u8 *)(&D_800A3354) + 4));
                    sp.u5A = (u16) temp_t9;
                    temp_t1 = (&sp.u50[0])[((u32) ((func_150ADA20() & 1) + sp.u5A + 1) % 3U) & 0xFFFF];
                    sp.u5A = (&sp.u50[0])[sp.u5A];
                    sp.u58 = temp_t1;
                    func_10010F30(0x2B7, 0x7FFFU, 0x40U, 0, 0U);
                    func_10010F30((s32) sp.u5A, 0x7FFFU, 0xAU, 0, 0U);
                    func_10010F30((s32) sp.u58, 0x7FFFU, 0x36U, 0, 0U);
                    sp.u5A = (u16) (func_150ADA20() % 5U);
                    temp_t5 = (u32) ((func_150ADA20() & 3) + sp.u5A + 1) % 5U;
                    sp44 = (s32 *)&func_1000EC24;
                    sp.u58 = (u16) temp_t5;
                    func_1000FA64((sp.u5A + 0x2B1) & 0xFFFF, (*(s16 *)((u8 *)arg0 + 0x10)), (*(s16 *)((u8 *)arg0 + 0x12)), (*(s16 *)((u8 *)arg0 + 0x14)), 0x4000, 0x2711U, 0x2710, (s32) &func_1000EC24, (u8 *)0x1001E, 0, 0x200, 0);
                    func_1000FA64((sp.u58 + 0x2B1) & 0xFFFF, (*(s16 *)((u8 *)arg0 + 0x10)), (*(s16 *)((u8 *)arg0 + 0x12)), (*(s16 *)((u8 *)arg0 + 0x14)), 0x4000, 0x2711U, 0x2710, (s32) sp44, (u8 *)0x1001E, 0, 0, 0);
                    sp.u5A = (u16) (func_150ADA20() % 5U);
                    temp_hi = (u32) ((func_150ADA20() & 3) + sp.u5A + 1) % 5U;
                    sp.u58 = (u16) temp_hi;
                    func_1000FA64((sp.u5A + 0x2B1) & 0xFFFF, (*(s16 *)((u8 *)arg0 + 0x10)), (*(s16 *)((u8 *)arg0 + 0x12)), (*(s16 *)((u8 *)arg0 + 0x14)), 0x4000, 0x2711U, 0x2710, (s32) sp44, (u8 *)0x32, 0, 0x300, 0);
                    func_1000FA64((temp_hi + 0x2B1) & 0xFFFF, (*(s16 *)((u8 *)arg0 + 0x10)), (*(s16 *)((u8 *)arg0 + 0x12)), (*(s16 *)((u8 *)arg0 + 0x14)), 0x4000, 0x2711U, 0x2710, (s32) sp44, (u8 *)0x32, 0, 0x100, 0);
                    break;
                case 3:
                    func_150B2C20((temp_v1 >> 8) & 0xFF, 0xFF);
                    break;
                }
            }
            (*(s8 *)((u8 *)arg0 + 0x8A)) = 0xFF;
            (*(s8 *)((u8 *)sp48 + 0x6E)) = 1;
            if (sp.u5C != NULL) {
                (*(s8 *)((u8 *)sp.u5C + 0x6E)) = 1;
            }
            temp_t6_2 = (*(s32 *)((u8 *)arg0 + 0x80)) + (D_800BE9E4 * 0x1E);
            (*(s32 *)((u8 *)arg0 + 0x80)) = temp_t6_2;
            if (temp_t6_2 >= 0xFF) {
                (*(s32 *)((u8 *)arg0 + 0x80)) = 0xFF;
                sp.u64 = 3;
            }
            temp_a1_2 = (*(s32 *)((u8 *)arg0 + 0x3C));
            if (temp_a1_2 != 0xFF) {
                func_151741D0((*(s32 *)((u8 *)arg0 + 0x80)), temp_a1_2);
            }
            if (sp.u64 == 3) {
                (*(s32 *)((u8 *)arg0 + 0x7C)) = 0;
                (*(s32 *)((u8 *)arg0 + 0x80)) = 0;
            }
        }
    }
    temp_t6_3 = (*(u8 *)((u8 *)arg0 + 0x73)) & 0xFFFC;
    (*(u8 *)((u8 *)arg0 + 0x73)) = temp_t6_3;
    (*(u8 *)((u8 *)arg0 + 0x73)) = (u8) (temp_t6_3 | sp.u64);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_1511CBC0.s")
#endif
void func_1511D0B4(s32 arg0, f32 *arg1) {
    *arg1 = 22000.0f;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_1511D0CC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_1511D91C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_1511DD44.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_1511DF6C.s")

struct B73 { u8 hi : 6; u8 lo : 2; };
void func_1511E14C(u8 *arg0)
{
  s32 var_v0;
  u8 *var_v1;
  u8 *temp_v0;
  f32 temp_f12;
  f32 temp_f2;
  temp_v0 = *((u8 **) (((u8 *) arg0) + 0x7C));
  if (temp_v0 == 0)
  {
    var_v1 = allocate_memory(0x10, 1, 0, 0);
    *((u8 **) (((u8 *) arg0) + 0x7C)) = var_v1;
    *((f32 *) (((u8 *) var_v1) + 0)) = 0.0f;
    *((f32 *) (((u8 *) var_v1) + 4)) = 0.0f;
    *((f32 *) (((u8 *) var_v1) + 8)) = 0.0f;
    *((f32 *) (((u8 *) var_v1) + 0xC)) = 0.025f;
  }
  else
  {
    var_v1 = temp_v0;
  }
  var_v0 = ((struct B73 *) (arg0 + 0x73))->lo;
  if (var_v0 == 0)
  {
    *((f32 *) (((u8 *) arg0) + 8)) = 0.0f;
  }
  else
    if (var_v0 == 3)
  {
    *((f32 *) (((u8 *) arg0) + 8)) = 90.0f;
    *((f32 *) (((u8 *) arg0) + 8)) = (f32) ((cosf((*((f32 *) (((u8 *) var_v1) + 0))) * 0.017453292f) * 0.5f) + (*((f32 *) (((u8 *) arg0) + 8))));
    *((f32 *) (((u8 *) var_v1) + 0)) = (f32) ((*((f32 *) (((u8 *) var_v1) + 0))) + (3.0f * ((f32) D_800BE9E4)));
  }
  else
    if (var_v0 == 2)
  {
    if ((*((f32 *) (((u8 *) arg0) + 8))) == 0.0f)
    {
      *((f32 *) (((u8 *) var_v1) + 4)) = 0.0f;
      *((f32 *) (((u8 *) var_v1) + 8)) = 0.0f;
    }
    *((f32 *) (((u8 *) var_v1) + 8)) = (f32) ((*((f32 *) (((u8 *) var_v1) + 0xC))) + (*((f32 *) (((u8 *) var_v1) + 8))));
    *((f32 *) (((u8 *) var_v1) + 4)) = (f32) ((*((f32 *) (((u8 *) var_v1) + 8))) + (*((f32 *) (((u8 *) var_v1) + 4))));
    *((f32 *) (((u8 *) arg0) + 8)) = (f32) ((*((f32 *) (((u8 *) var_v1) + 4))) + (*((f32 *) (((u8 *) arg0) + 8))));
    if ((*((f32 *) (((u8 *) arg0) + 8))) >= 90.0f)
    {
      var_v0 = 3;
      *((f32 *) (((u8 *) arg0) + 8)) = 90.0f;
    }
  }
  else
  {
    temp_f2 = *((f32 *) (((u8 *) arg0) + 8));
    temp_f12 = (f32) D_800BE9E4;
    if (temp_f12 < temp_f2)
    {
      *((f32 *) (((u8 *) arg0) + 8)) = (f32) (temp_f2 - temp_f12);
    }
    else
    {
      *((f32 *) (((u8 *) arg0) + 8)) = 0.0f;
      var_v0 = 0;
    }
  }
  *((u8 *) (arg0 + 0x73)) &= 0xFFFC;
  *((u8 *) (arg0 + 0x73)) |= var_v0;
}

s32 func_10010558(s32, struct127 *, s32, s32, s32, s32);

void func_1511E320(u8 *arg0, struct127 *arg1) {
    s32 snd;
    s32 vol;
    s32 isA;
    s32 isB;
    u8 id;

    vol = 0x6590;
    snd = 0;
    isA = arg1->id == 0x3B;
    isB = arg1->id == 0x80;
    switch (*(u16 *)(arg0 + 0x54)) {
    case 0x39:
    case 0x5C:
    case 0x5D:
    case 0x5E:
        if (isA) {
            func_10010630(0x542, arg1, 0x6590, 0x64, 0x3E8);
        } else if (isB) {
            func_10010630(0x567, arg1, 0x6590, 0x64, 0x3E8);
        }
        snd = 0x2B0;
        break;
    case 0x3A:
        if (isA) {
            snd = (func_150ADA20() & 1) + 0x53E;
        } else if (isB) {
            snd = 0x567;
        } else {
            snd = 0x60A;
        }
        break;
    case 0x3B:
    case 0x51:
        snd = 0x181;
        break;
    case 0x3C:
    case 0x6A:
        snd = 0xB1;
        break;
    case 0x3D:
    case 0x6B:
        snd = 0x442;
        break;
    case 0x3E:
        snd = 0x444;
        break;
    case 0x46:
        snd = 0x2F0;
        break;
    case 0x47:
        snd = 0x4A3;
        break;
    case 0x50:
    case 0x55:
        snd = (func_150ADA20() & 1) + 0xB;
        break;
    case 0x52:
    case 0x58:
        snd = 0x510;
        break;
    case 0x53:
        snd = 0x2AF;
        if (isB) {
            func_10010558(0x567, arg1, 0x7D00, 0x64, 0x3E8, 0x19);
        }
        break;
    case 0x56:
        if (isB) {
            func_10010630(0x567, arg1, 0x6590, 0x64, 0x3E8);
        }
        snd = 0x5AE;
        break;
    case 0x57:
    case 0x6D:
    case 0x6E:
        snd = 0x51;
        vol = 0x2328;
        break;
    case 0x64:
    case 0x65:
        snd = 0x629;
        vol = 0x7FFF;
        break;
    }
    if (snd != 0) {
        func_10010630(snd, arg1, vol, 0x64, 0x3E8);
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_1511E4F4.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_1511ED08.s")

#ifdef NON_MATCHING
void func_1511F1D8(u8 *arg0) {
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f12_2;
    f32 var_f2;

    if ((*(s32 *)((u8 *)arg0 + 0x7C)) == 0) {
        (*(f32 *)((u8 *)arg0 + 0x84)) = (f32) (*(s16 *)((u8 *)arg0 + 0x12));
    }
    temp_f0 = (f32) (*(s16 *)((u8 *)arg0 + 0x12));
    var_f2 = (f32) D_800BE9E4 * 4.0f;
    if ((*(s32 *)((u8 *)arg0 + 0x3C)) != 0) {
        var_f2 *= 0.25f;
    }
    if ((*(s32 *)((u8 *)arg0 + 0x80)) != 0) {
        temp_f12 = (*(f32 *)((u8 *)arg0 + 0x84)) + 500.0f;
        (*(s16 *)((u8 *)arg0 + 0x12)) = (s16) (s32) (temp_f0 + (var_f2 * 5.0f));
        if (temp_f12 < (f32) (*(s16 *)((u8 *)arg0 + 0x12))) {
            (*(s8 *)((u8 *)arg0 + 0x6E)) = 1;
            (*(s16 *)((u8 *)arg0 + 0x12)) = (s16) (s32) temp_f12;
        }
    } else {
        temp_f12_2 = (*(f32 *)((u8 *)arg0 + 0x84));
        (*(s16 *)((u8 *)arg0 + 0x12)) = (s16) (s32) (temp_f0 - var_f2);
        if ((f32) (*(s16 *)((u8 *)arg0 + 0x12)) < temp_f12_2) {
            (*(s16 *)((u8 *)arg0 + 0x12)) = (s16) (s32) temp_f12_2;
        }
    }
    (*(s32 *)((u8 *)arg0 + 0x7C)) = 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_1511F1D8.s")
#endif
void func_1511F30C(u8 *arg0) {
    s32 dir;
    f32 step;
    f32 lim;

    if (*(s32 *)(arg0 + 0x7C) == 0) {
        *(f32 *)(arg0 + 0x84) = (f32) *(s16 *)(arg0 + 0x14);
    }
    step = (f32) D_800BE9E4 * 4.0f;
    dir = 1 - (*(u8 *)(arg0 + 0x72) & 1);
    if (*(s32 *)(arg0 + 0x80) != 0) {
        if (dir & 1) {
            lim = *(f32 *)(arg0 + 0x84);
            *(s16 *)(arg0 + 0x14) = (s32) ((f32) *(s16 *)(arg0 + 0x14) + step);
            if (lim < (f32) *(s16 *)(arg0 + 0x14)) {
                *(s16 *)(arg0 + 0x14) = (s32) lim;
            }
        } else {
            lim = *(f32 *)(arg0 + 0x84);
            *(s16 *)(arg0 + 0x14) = (s32) ((f32) *(s16 *)(arg0 + 0x14) - step);
            if ((f32) *(s16 *)(arg0 + 0x14) < lim) {
                *(s16 *)(arg0 + 0x14) = (s32) lim;
            }
        }
    } else if (dir & 1) {
        *(s16 *)(arg0 + 0x14) = (s32) ((f32) *(s16 *)(arg0 + 0x14) - step);
        lim = *(f32 *)(arg0 + 0x84) - 350.0f;
        if ((f32) *(s16 *)(arg0 + 0x14) < lim) {
            *(s16 *)(arg0 + 0x14) = (s32) lim;
        }
    } else {
        *(s16 *)(arg0 + 0x14) = (s32) ((f32) *(s16 *)(arg0 + 0x14) + step);
        lim = *(f32 *)(arg0 + 0x84) + 350.0f;
        if (lim < (f32) *(s16 *)(arg0 + 0x14)) {
            *(s16 *)(arg0 + 0x14) = (s32) lim;
        }
    }
    *(s32 *)(arg0 + 0x7C) = 1;
}

#ifdef NON_MATCHING
s32 func_1508712C(s32, f32 *, s32 *, f32 *);
s32 func_150871B8(s32);

void func_1511F4C8(u8 *arg0) {
    struct {
        f32 u40;
        s32 u44;
        f32 u48;
        struct127 * u4C;
    } sp;
    f32 sp3C;
    struct108 *sp34;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f12;
    f32 temp_f12_2;
    f32 temp_f2;
    s16 temp_v0_3;
    s32 temp_v0_4;
    s32 temp_v0_5;
    struct108 *temp_a0;
    struct108 *var_a0;
    struct127 *temp_v1;
    u8 *temp_v0;
    u8 *temp_v0_2;
    u8 *var_s0;

    temp_v0 = (*(u8 **)((u8 *)arg0 + 0x7C));
    var_s0 = temp_v0;
    if (temp_v0 == NULL) {
        temp_v0_2 = allocate_memory(0x24, 1, 0, 0);
        (*(u8 **)((u8 *)arg0 + 0x7C)) = temp_v0_2;
        var_s0 = temp_v0_2;
        bzero(temp_v0_2, 0x24);
    }
    temp_v0_3 = (*(s16 *)((u8 *)var_s0 + 0x1C));
    if (temp_v0_3 > 0) {
        (*(s16 *)((u8 *)var_s0 + 0x1C)) = (s16) (temp_v0_3 - D_800BE9E4);
        if ((*(s16 *)((u8 *)var_s0 + 0x1C)) <= 0) {
            temp_a0 = &D_800DBFF0[(*(s32 *)((u8 *)arg0 + 0x84))];
            sp34 = temp_a0;
            func_151239CC(temp_a0, 0xA);
        }
    }
    temp_v0_4 = (*(s32 *)((u8 *)arg0 + 0x80));
    var_a0 = sp34;
    if (temp_v0_4 == 1) {
        temp_v1 = &D_800CC2D0[(*(s32 *)((u8 *)arg0 + 0x84))];
        (*(s16 *)((u8 *)arg0 + 0x10)) = (s16) (s32) temp_v1->x_position;
        (*(s16 *)((u8 *)arg0 + 0x12)) = (s16) ((s32) temp_v1->y_position + 0x64);
        (*(s16 *)((u8 *)arg0 + 0x14)) = (s16) (s32) temp_v1->z_position;
        sp.u4C = temp_v1;
        func_1508712C(func_150871B8(0x28), &sp.u48, &sp.u44, &sp.u40);
        (*(f32 *)((u8 *)var_s0 + 0x14)) = (f32) ((sp.u48 - sp.u4C->x_position) * 0.5f);
        temp_f2 = (*(f32 *)((u8 *)var_s0 + 0x14));
        (*(f32 *)((u8 *)var_s0 + 0x18)) = (f32) ((sp.u40 - sp.u4C->z_position) * 0.5f);
        temp_f12 = (*(f32 *)((u8 *)var_s0 + 0x18));
        (*(f32 *)((u8 *)var_s0 + 0)) = (f32) (sp.u4C->x_position + temp_f2);
        (*(f32 *)((u8 *)var_s0 + 4)) = (f32) (sp.u4C->y_position + 100.0f);
        (*(f32 *)((u8 *)var_s0 + 0x10)) = -90.0f;
        temp_f0 = sqrtf((temp_f2 * temp_f2) + (temp_f12 * temp_f12));
        (*(f32 *)((u8 *)var_s0 + 8)) = (f32) (sp.u4C->z_position + temp_f12);
        (*(f32 *)((u8 *)var_s0 + 0xC)) = temp_f0;
        (*(s32 *)((u8 *)arg0 + 0x80)) = 2;
        return;
    }
    if (temp_v0_4 == 2) {
        temp_v0_5 = (*(s32 *)((u8 *)arg0 + 0x84));
        if (D_80082FA0 >= temp_v0_5) {
            var_a0 = &D_800DBFF0[temp_v0_5];
            if (var_a0->unk2C != 0x400000) {
                sp34 = var_a0;
                func_15123934(var_a0, 0x400000, 0, var_a0->unk134, 0xA);
            }
            var_a0->unk2BC = (f32) (*(s16 *)((u8 *)arg0 + 0x10));
            var_a0->unk2C0 = (f32) (*(s16 *)((u8 *)arg0 + 0x12));
            var_a0->unk2A4 = var_a0->unk2BC;
            var_a0->unk2F8 = 0.0f;
            var_a0->unk300 = 0.0f;
            var_a0->unk2A8 = var_a0->unk2C0;
            var_a0->unk2C4 = (f32) (*(s16 *)((u8 *)arg0 + 0x14));
            var_a0->unk2AC = (*(s32 *)&(var_a0->unk2C4));
            var_a0->unk2FC = 300.0f;
            (*(s16 *)((u8 *)var_s0 + 0x1C)) = 0x3C;
        }
        sp34 = var_a0;
        temp_f12_2 = ((*(f32 *)((u8 *)var_s0 + 0x10)) * 3.1415927f) / 180.0f;
        sp3C = temp_f12_2;
        (*(s16 *)((u8 *)arg0 + 0x12)) = (s16) (s32) ((cosf(temp_f12_2) * (*(f32 *)((u8 *)var_s0 + 0xC))) + (*(f32 *)((u8 *)var_s0 + 4)));
        temp_f0_2 = sinf(temp_f12_2);
        (*(s16 *)((u8 *)arg0 + 0x10)) = (s16) (s32) ((*(f32 *)((u8 *)var_s0 + 0)) + ((*(f32 *)((u8 *)var_s0 + 0x14)) * temp_f0_2));
        (*(s16 *)((u8 *)arg0 + 0x14)) = (s16) (s32) ((*(f32 *)((u8 *)var_s0 + 8)) + ((*(f32 *)((u8 *)var_s0 + 0x18)) * temp_f0_2));
        (*(f32 *)((u8 *)var_s0 + 0x10)) = (f32) ((*(f32 *)((u8 *)var_s0 + 0x10)) + (f32) D_800BE9E4);
        if ((*(f32 *)((u8 *)var_s0 + 0x10)) > 90.0f) {
            (*(f32 *)((u8 *)var_s0 + 0x10)) = 90.0f;
            (*(s32 *)((u8 *)arg0 + 0x80)) = 0;
            (*(s8 *)((u8 *)arg0 + 0x6E)) = 1;
            if (D_80082FA0 >= (*(s32 *)((u8 *)arg0 + 0x84))) {
                func_151239CC(var_a0, 0xA);
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_1511F4C8.s")
#endif
void func_15114E8C(f32 (*)[4], u8 *);
u8 *func_151149AC(u8);
void func_1511F8A4(u8 *arg0) {
    s32 pad[2]; // fakematch: frame pad
    f32 sp48[4][4];
    f32 sp44;
    f32 sp40;
    f32 sp3C;
    u8 *temp_v0;
    u16 t = *(u16 *)(arg0 + 0x3E);
    if ((*(u16 *)(arg0 + 0x54) == 0x8005) && (D_800BE9F0 == 0x35)) {
        temp_v0 = func_151149AC(t);
        if (temp_v0 != 0) {
            func_15114E8C(sp48, temp_v0);
            func_150A7E40(sp48, -3.0f, 223.0f, 549.0f, &sp44, &sp40, &sp3C);
            *(s16 *)(arg0 + 0x10) = (s32)sp44;
            *(s16 *)(arg0 + 0x12) = (s32)sp40;
            *(s16 *)(arg0 + 0x14) = (s32)sp3C;
        }
    }
}

#ifdef NON_MATCHING
void func_1511F970(u8 *arg0) {
    s32 temp_t2;
    s32 temp_t4;
    s32 temp_v1;
    s32 temp_v1_2;

    if ((*(s32 *)((u8 *)arg0 + 0x7C)) == 0) {
        (*(s32 *)((u8 *)arg0 + 0x7C)) = 1;
        (*(s32 *)((u8 *)arg0 + 0x80)) = (s32) ((((s32) (*(s32 *)((u8 *)arg0 + 0x3C)) >> 0x10) & 0xFFFF) * 0x32);
    }
    temp_v1 = (*(s32 *)((u8 *)arg0 + 0x80));
    temp_t2 = ((*(s32 *)((u8 *)arg0 + 0x3C)) & 0xFFFF) * 0x32;
    if (temp_v1 != 0) {
        if (D_800BE9E4 < temp_v1) {
            (*(s32 *)((u8 *)arg0 + 0x80)) = (s32) (temp_v1 - D_800BE9E4);
            return;
        }
        (*(s32 *)((u8 *)arg0 + 0x80)) = 0;
        (*(s32 *)((u8 *)arg0 + 0x84)) = temp_t2;
        return;
    }
    temp_v1_2 = (*(s32 *)((u8 *)arg0 + 0x84));
    temp_t4 = temp_v1_2 - D_800BE9E4;
    if (D_800BE9E4 < temp_v1_2) {
        (*(s32 *)((u8 *)arg0 + 0x84)) = temp_t4;
        (*(s8 *)((u8 *)arg0 + 0x8A)) = (s8) ((s32) (temp_t4 * 0xFF) / temp_t2);
        return;
    }
    (*(s8 *)((u8 *)arg0 + 0x6E)) = 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_1511F970.s")
#endif
#ifdef NON_MATCHING
void func_1511FA68(u8 *arg0) {
    s32 sp8;
    s32 sp4;
    s32 temp_a2;
    s32 temp_a2_2;
    s32 temp_a2_3;
    s32 temp_a2_4;
    s32 temp_a2_5;
    s32 temp_f16;
    s32 temp_lo;
    s32 temp_t4;
    s32 var_a1;
    s32 var_a3;
    s32 var_t0;
    s32 var_v0;
    u8 temp_t4_2;
    u8 temp_v1;

    temp_v1 = (*(u8 *)((u8 *)arg0 + 0x73));
    var_v0 = temp_v1 & 3;
    if ((temp_v1 & 4) == 4) {
        if (var_v0 == 2) {
            var_v0 = 0;
        } else if (var_v0 == 1) {
            var_v0 = 3;
        }
    }
    temp_a2 = (*(s32 *)((u8 *)arg0 + 0x84));
    var_t0 = (*(s32 *)((u8 *)arg0 + 0x7C));
    var_a3 = (temp_a2 >> 0x10) & 0xFFFF;
    var_a1 = temp_a2 & 0xFFFF;
    temp_f16 = (s32) ((f32) (*(s32 *)((u8 *)arg0 + 0x3C)) * (*(f32 *)((u8 *)arg0 + 0x30)));
    if (var_t0 == 0) {
        temp_t4 = ((*(s16 *)((u8 *)arg0 + 0x10)) & 0xFFFF) | ((*(s16 *)((u8 *)arg0 + 0x12)) << 0x10);
        (*(s32 *)((u8 *)arg0 + 0x7C)) = temp_t4;
        if (var_v0 == 3) {
            var_a1 = 0xA;
            var_a3 = 0xA;
            var_t0 = temp_t4;
        } else {
            var_a3 = 0;
            var_a1 = 0;
            var_t0 = (*(s32 *)((u8 *)arg0 + 0x7C));
        }
    }
    sp4 = (s32) (s16) var_t0;
    sp8 = (s32) (s16) (((s32) (*(s32 *)((u8 *)arg0 + 0x7C)) >> 0x10) & 0xFFFF);
    if (var_v0 == 2) {
        temp_a2_2 = var_a1 + D_800BE9E4;
        var_a1 = 0xA;
        if (temp_a2_2 < 0xA) {
            var_a1 = temp_a2_2;
        }
        if (var_a1 >= 7) {
            temp_a2_3 = var_a3 + D_800BE9E4;
            var_a3 = 0xA;
            if (temp_a2_3 < 0xA) {
                var_a3 = temp_a2_3;
            } else {
                var_v0 = 3;
            }
        }
    } else if (var_v0 == 1) {
        temp_a2_4 = var_a3 - D_800BE9E4;
        var_a3 = 0;
        if (temp_a2_4 > 0) {
            var_a3 = temp_a2_4;
        }
        if (var_a3 < 3) {
            temp_a2_5 = var_a1 - D_800BE9E4;
            var_a1 = 0;
            if (temp_a2_5 > 0) {
                var_a1 = temp_a2_5;
            } else {
                var_v0 = 0;
            }
        }
    }
    (*(s16 *)((u8 *)arg0 + 0x12)) = (s16) (sp8 + ((s32) (var_a1 * temp_f16) / 10));
    (*(s16 *)((u8 *)arg0 + 0xB2)) = (s16) (sp8 - ((s32) ((temp_f16 + 1) * var_a1) / 10));
    temp_lo = (s32) (var_a3 * temp_f16) / 10;
    (*(s16 *)((u8 *)arg0 + 0x150)) = (s16) (sp4 - temp_lo);
    temp_t4_2 = (*(u8 *)((u8 *)arg0 + 0x73)) & ~3;
    (*(u8 *)((u8 *)arg0 + 0x73)) = temp_t4_2;
    (*(s16 *)((u8 *)arg0 + 0x1F0)) = (s16) (sp4 + temp_lo);
    (*(s32 *)((u8 *)arg0 + 0x84)) = (s32) ((var_a1 & 0xFFFF) | ((var_a3 & 0xFFFF) << 0x10));
    (*(u8 *)((u8 *)arg0 + 0x73)) = (u8) ((temp_t4_2 & 0xFF) | var_v0);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_1511FA68.s")
#endif
void func_1511FD00(s32 *arg0, s32 arg1) {
    if (arg0[0x80 / 4] == 0) {
        arg0[0x80 / 4] = 1;
    }
}

void func_1511FD20(u8 *arg0) {
    s32 pad[2]; // fakematch: frame size (unused locals)
    s32 lim;
    s32 pad2; // fakematch: frame slot
    s16 old;
    u32 st;

    old = *(f32 *)(arg0 + 0x18) + *(s16 *)(arg0 + 0x12);
    lim = *(s32 *)(arg0 + 0x3C);
    lim = lim * 50 / 60;
    if (D_800BE9B4 != 0) {
        *(s32 *)(arg0 + 0x7C) = func_150ADA20() & 0xFFFF;
    }
    *(f32 *)(arg0 + 0x18) = cosf(*(s32 *)(arg0 + 0x7C) * 0.005493164f) * 25.0f;
    st = *(s32 *)(arg0 + 0x80);
    *(s32 *)(arg0 + 0x7C) += D_800BE9E4 * 10;
    if (st == 1) {
        *(s32 *)(arg0 + 0x84) += D_800BE9E4;
        if (lim < *(s32 *)(arg0 + 0x84)) {
            *(s32 *)(arg0 + 0x80) = 2;
        }
    } else if (st == 2) {
        *(s16 *)(arg0 + 0x12) -= D_800BE9E4;
        if (*(s16 *)(arg0 + 0x12) < -10000) {
            *(s8 *)(arg0 + 0x6E) = 1;
        }
    }
    *(s16 *)(arg0 + 0x5C) = (*(f32 *)(arg0 + 0x18) + *(s16 *)(arg0 + 0x12)) - old;
}

void func_1511FEA8(u8 *arg0) {
    u8 *temp_v0 = func_151149AC(arg0[0x3F]);

    if (temp_v0 != NULL) {
        *(s16 *)(arg0 + 0x10) = *(s16 *)(temp_v0 + 0x10);
        *(s16 *)(arg0 + 0x12) = *(s16 *)(temp_v0 + 0x12);
        *(s16 *)(arg0 + 0x14) = *(s16 *)(temp_v0 + 0x14);
    }
}

void func_1511FEF0(void) {
    D_800DC3F0 = 0;
}

#ifdef NON_MATCHING
extern s32 D_800DC3F8;

void func_1511FF00(u8 *arg0, s32 arg1) {
    s32 *var_a1;
    s32 temp_t4;
    s32 temp_t7;
    s32 temp_v1;
    s32 var_a1_2;
    s32 var_a3;
    s32 var_t1;
    s32 var_v0;
    u8 temp_t0;
    u8 temp_t3;
    u8 temp_t7_2;
    u8 *temp_a1;
    u8 *temp_a3;
    u8 *temp_t0_2;
    u8 *temp_t0_3;

    temp_t0 = (*(u8 *)((u8 *)arg0 + 0x73));
    temp_t7 = (s32) (*(s32 *)((u8 *)arg0 + 0x3C)) >> 0x10;
    var_a3 = 0;
    var_t1 = 0;
    var_v0 = temp_t0 & 3;
    temp_v1 = temp_t0 & 4;
    if (D_800DC3F0 > 0) {
        var_a1 = &D_800DC3F8;
loop_2:
        if ((s32)arg0 != (s32)(*var_a1)) {
            var_t1 += 1;
            var_a1 = (s32 *)((u8 *)var_a1 + (8));
            if (var_t1 < D_800DC3F0) {
                goto loop_2;
            }
        }
    }
    if (var_t1 == D_800DC3F0) {
        if (var_t1 < 4) {
            temp_a1 = ((s32 *)((u8 *)&D_800DC3F8 + (var_t1 * 8)));
            (*(u8 **)((u8 *)temp_a1 + 0)) = arg0;
            (*(s32 *)((u8 *)temp_a1 + 4)) = (s32) (s8) temp_t7;
            D_800DC3F0 += 1;
            var_a3 = 1;
            goto block_7;
        }
    } else {
block_7:
        if ((s8) temp_t7 >= 0) {
            if (var_a3 != 0) {
                if ((s8) temp_t7 == (*(u8 *)((u8 *)D_800CCA0C + 0x11B))) {
                    if (arg1 == 0) {
                        if ((var_v0 != 0) && (var_v0 != 1)) {
                            var_v0 = 1;
                        }
                        (*(f32 *)((u8 *)arg0 + 4)) = (f32) ((s32) ((*(s32 *)((u8 *)arg0 + 0x3C)) << 0x16) >> 0x16);
                    } else if (arg1 == 1) {
                        var_v0 = 3;
                    } else if (arg1 == 2) {
                        var_v0 = 2;
                    } else if (arg1 == 3) {
                        if ((var_v0 != 0) && (var_v0 != 1)) {
                            if (temp_v1 != 0) {
                                var_v0 = 1;
                            }
                        } else if (temp_v1 == 0) {
                            var_v0 = 3;
                        }
                        (*(f32 *)((u8 *)arg0 + 4)) = (f32) ((s32) ((*(s32 *)((u8 *)arg0 + 0x3C)) << 0x16) >> 0x16);
                    }
                } else if ((arg1 == 0) || (arg1 == 2) || (arg1 == 3)) {
                    if ((arg1 != 3) || (temp_v1 != 0)) {
                        var_v0 = 0;
                    } else {
                        var_v0 = 3;
                    }
                }
            } else if ((var_v0 == 1) || (var_v0 == 2)) {
                var_a1_2 = 0;
                if (D_800DC3F0 > 0) {
                    do {
                        if (var_a1_2 != var_t1) {
                            temp_a3 = ((s32 *)((u8 *)&D_800DC3F8 + (var_a1_2 * 8)));
                            if (((s8) temp_t7 == (*(s32 *)((u8 *)temp_a3 + 4))) && ((temp_v1 != 0) || !((*(u8 *)((u8 *)((*(u8 **)((u8 *)temp_a3 + 0))) + 0x73)) & 4)) && ((temp_t0_2 = (*(u8 **)((u8 *)temp_a3 + 0)), temp_t3 = (*(u8 *)((u8 *)temp_t0_2 + 0x73)), temp_t4 = temp_t3 & 3, (temp_t4 != 3)) || (var_v0 != 2)) && ((temp_t4 != 0) || (var_v0 != 1))) {
                                (*(u8 *)((u8 *)temp_t0_2 + 0x73)) = (u8) (temp_t3 & 0xFFFC);
                                temp_t0_3 = (*(u8 **)((u8 *)temp_a3 + 0));
                                (*(u8 *)((u8 *)temp_t0_3 + 0x73)) = (u8) ((*(u8 *)((u8 *)temp_t0_3 + 0x73)) | var_v0);
                            }
                        }
                        var_a1_2 += 1;
                    } while (var_a1_2 < D_800DC3F0);
                }
            }
        }
        temp_t7_2 = (*(u8 *)((u8 *)arg0 + 0x73)) & 0xFFFC;
        (*(u8 *)((u8 *)arg0 + 0x73)) = temp_t7_2;
        (*(u8 *)((u8 *)arg0 + 0x73)) = (u8) (temp_t7_2 | var_v0);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_1511FF00.s")
#endif