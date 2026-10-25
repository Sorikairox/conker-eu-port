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
#ifdef NON_MATCHING
// lift_y_update: world-object mover (update table next to func_15115CDC): moves the object's y (+0x12, s16) between
// its rest height (+0x7C, taken from y on the first call) and the target in the params word +0x3C (low half), in
// `steps` (byte 1) equal steps, with a pause of byte 0 + 1 frames. Timer +0x80: > 0 = going up (counts down at
// the target), < 0 = waiting to return (counts up), 0 = at rest (starts again by itself when flag 4 of +0x4F is set)
// or going back down. +0x5C gets this frame's y change.
void func_15115B40(u8 *obj) {
    s32 params = *(s32 *) (obj + 0x3C);
    s32 steps = (params >> 16) & 0xFF;
    s32 pause = ((params >> 24) & 0xFF) + 1;
    s32 target = (s16) params;
    s32 old_y = *(s16 *) (obj + 0x12);
    s32 loop = 0;
    s32 moving = 0;
    s32 rest;
    s32 step;
    s32 timer;
    s32 y;

    if ((obj[0x4F] & 4) == 4) {
        loop = 1;
    }
    rest = *(s32 *) (obj + 0x7C);
    if (rest == 0) {
        *(s32 *) (obj + 0x7C) = old_y;
        rest = old_y;
    }
    step = (target - rest) / steps;
    timer = *(s32 *) (obj + 0x80);
    if (timer == 0) {
        if (rest == old_y) {
            if (loop) {
                *(s32 *) (obj + 0x80) = pause;
                timer = pause;
            }
        } else {
            y = (s16) (old_y - step);
            if (rest < target) {
                if (rest < y) {
                    moving = 1;
                }
            } else if (y < rest) {
                moving = 1;
            }
            if (moving) {
                *(s16 *) (obj + 0x12) = y;
                timer = *(s32 *) (obj + 0x80);
            } else {
                timer = -pause;
                *(s16 *) (obj + 0x12) = rest;
                *(s32 *) (obj + 0x80) = timer;
            }
        }
    }
    if (timer > 0) {
        y = (s16) (*(s16 *) (obj + 0x12) + step);
        if (*(s32 *) (obj + 0x7C) < target) {
            if (y < target) {
                moving = 1;
            }
        } else if (target < y) {
            moving = 1;
        }
        if (moving) {
            *(s16 *) (obj + 0x12) = y;
            *(s32 *) (obj + 0x80) = pause;
            timer = pause;
        } else {
            *(s16 *) (obj + 0x12) = target;
            *(s32 *) (obj + 0x80) = timer - 1;
            timer--;
        }
    }
    if (timer < 0) {
        *(s32 *) (obj + 0x80) = timer + 1;
    }
    *(s16 *) (obj + 0x5C) = *(s16 *) (obj + 0x12) - old_y;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_15115B40.s")
#endif

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
#ifdef NON_MATCHING
s32 func_15195FB0(u8 *, s32, s32, s32, s32, s32, s32);

// object_start_pending_anim: if the object has no animation handle yet (+0x7C), starts the one requested in +0x3C
// (bits 0-14 id, bits 15+ passed as is, bits 16-23 / 24-31 as the last two arguments) and clears the request.
void func_15116690(u8 *obj) {
    s32 req;

    if (*(s32 *)(obj + 0x7C) != 0) {
        return;
    }
    req = *(s32 *)(obj + 0x3C);
    *(s32 *)(obj + 0x7C) = func_15195FB0(obj, req & 0x7FFF, req >> 15, -1, 0, (req >> 24) & 0xFF, (req >> 16) & 0xFF);
    *(s32 *)(obj + 0x3C) = 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_15116690.s")
#endif

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
#ifdef NON_MATCHING
// object_bob_update: cosine bob around the base value +0x12 (s16): the offset +0x18 (f32) becomes
// cos(phase +0x7C * 360/65536) * amplitude (low half of +0x3C, s16), the phase advances by the speed (high half of
// +0x3C) * D_800BE9E4, and +0x5C (s16) = the change of the bobbed value (base + offset, truncated) this frame.
void func_15116854(u8 *obj) {
    s16 before;
    s32 cfg;
    f32 amplitude;
    u32 speed;
    f32 offset;

    before = (s32) ((f32) *(s16 *) (obj + 0x12) + *(f32 *) (obj + 0x18));
    cfg = *(s32 *) (obj + 0x3C);
    amplitude = (s16) cfg;
    speed = (cfg >> 16) & 0xFFFF;
    offset = cosf(*(s32 *) (obj + 0x7C) * 0.0054931640625f) * amplitude;
    *(f32 *) (obj + 0x18) = offset;
    *(s32 *) (obj + 0x7C) += speed * D_800BE9E4;
    *(s16 *) (obj + 0x5C) = (s32) (((f32) *(s16 *) (obj + 0x12) + offset) - before);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_15116854.s")
#endif

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

#ifdef NON_MATCHING
void func_15116F34(u8 *obj);
#endif
void func_15116F04(u8 *arg0) {
    if (arg0[0x73] & 2) {
        func_15116F34(arg0);
    }
}

#ifdef NON_MATCHING
// mover_step: moves the object's s16 position +0x10 towards its s32 target +0x7C (+0x3C: sound entry index >> 10,
// speed in the other bits; +0x5A gets the per-axis delta). At the target the deltas are cleared and the entry's
// stop sound plays if the move sound was on (+0x74); entries with a near-arrival sound go to func_1511712C;
// otherwise the move sound starts (unless +0x74) and each axis steps by (speed * D_800BE9E4) / 2, clamped.
typedef struct {
    /* 0x0 */ s16 move_sfx;
    /* 0x2 */ s16 unk2;
    /* 0x4 */ s16 stop_sfx;
    /* 0x6 */ s16 unk6;
    /* 0x8 */ s16 near_sfx;
    /* 0xA */ s16 near_lead;
} MoverSfx; // 0xC
extern MoverSfx D_80089600[];
s32 func_151152A4(u8 *obj, s32 sound, s32 vol, s16 r0, s16 r1, s32 flags);

void func_1511712C(u8 *obj);

void func_15116F34(u8 *obj) {
    s32 bits = *(s32 *)(obj + 0x3C);
    s32 kind = bits >> 10;
    s16 *pos = (s16 *)(obj + 0x10);
    s32 *target = (s32 *)(obj + 0x7C);
    s16 *delta = (s16 *)(obj + 0x5A);
    s32 step;
    s32 i;

    if (target[0] == pos[0] && target[1] == pos[1] && target[2] == pos[2]) {
        delta[2] = 0;
        delta[1] = delta[2];
        delta[0] = delta[2];
        if (*(u16 *)(obj + 0x74) != 0) {
            if (kind != 0 && D_80089600[kind].stop_sfx != 0) {
                func_151152A4(obj, D_80089600[kind].stop_sfx, 0x5DC0, 0x7D0, 0xFA0, 4);
            }
            *(u16 *)(obj + 0x74) = 0;
        }
        return;
    }
    if (kind != 0 && D_80089600[kind].near_sfx != 0) {
        func_1511712C(obj);
        return;
    }
    if (kind != 0 && *(u16 *)(obj + 0x74) == 0 && D_80089600[kind].move_sfx != 0) {
        func_151152A4(obj, D_80089600[kind].move_sfx, 0x5DC0, 0x7D0, 0xFA0, 0);
    }
    step = ((bits & 0xFFFF03FF) * D_800BE9E4) >> 1;
    for (i = 0; i < 3; i++) {
        delta[i] = pos[i];
        if (pos[i] != target[i]) {
            if (target[i] < pos[i]) {
                pos[i] -= step;
                if (pos[i] < target[i]) {
                    pos[i] = target[i];
                }
            } else {
                pos[i] += step;
                if (target[i] < pos[i]) {
                    pos[i] = target[i];
                }
            }
        }
        delta[i] = pos[i] - delta[i];
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_15116F34.s")
#endif

#ifdef NON_MATCHING
// mover_step_sfx: func_15116F34's path for movers whose sound entry has a near-arrival sound: starts the move sound
// (entry +0, unless +0x74 says it already plays), steps the s16 position +0x10 towards the s32 target +0x7C by
// ((+0x3C & 0xFFFF03FF) * D_800BE9E4) / 2 per axis (clamped; +0x5A gets the per-axis delta) and plays the entry's
// +8 sound once the largest remaining distance minus +0xA * speed / 2 drops to 0 (on the frame it crosses, or
// when the move sound started this frame).
void func_1511712C(u8 *obj) {
    s32 bits = *(s32 *)(obj + 0x3C);
    s32 kind = bits >> 10;
    s32 speed = bits & 0xFFFF03FF;
    s16 *pos = (s16 *)(obj + 0x10);
    s32 *target = (s32 *)(obj + 0x7C);
    s16 *delta = (s16 *)(obj + 0x5A);
    s32 started = FALSE;
    s32 farthest = 0;
    s32 step;
    s32 dist;
    s32 i;

    if (kind != 0 && *(u16 *)(obj + 0x74) == 0 && D_80089600[kind].move_sfx != 0) {
        func_151152A4(obj, D_80089600[kind].move_sfx, 0x5DC0, 0x7D0, 0xFA0, 0);
        started = TRUE;
    }
    step = (speed * D_800BE9E4) >> 1;
    for (i = 0; i < 3; i++) {
        delta[i] = pos[i];
        if (pos[i] != target[i]) {
            if (target[i] < pos[i]) {
                pos[i] -= step;
                dist = pos[i] - target[i];
            } else {
                pos[i] += step;
                dist = target[i] - pos[i];
            }
            if (dist < 0) {
                pos[i] = target[i];
            }
            if (farthest < dist) {
                farthest = dist;
            }
        }
        delta[i] = pos[i] - delta[i];
    }
    if (kind != 0 && D_80089600[kind].near_sfx != 0) {
        farthest -= (D_80089600[kind].near_lead * speed) >> 1;
        if (farthest <= 0 && (-step < farthest || started)) {
            func_151152A4(obj, D_80089600[kind].near_sfx, 0x5DC0, 0x7D0, 0xFA0, 0);
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_1511712C.s")
#endif

#ifdef NON_MATCHING
/* spin_angles_update: three angles in degrees at +0x00 (f32[3]) turn by their rates +0x60 (f32[3]) times the ticks
 * D_800BE9E4 and stay in [0, 360); each rate first moves toward its target +0x7C (f32[3]) by +0x3C / 256 (s32) without
 * overshooting. No direct caller (reached through a table); the asm's v0 is the loop bound 0xC, not a result. */
void func_151172FC(u8 *o) {
    f32 *angle = (f32 *) o;
    f32 *rate = (f32 *) (o + 0x60);
    f32 *target = (f32 *) (o + 0x7C);
    f32 step = *(s32 *) (o + 0x3C) * 0.00390625f;
    f32 ticks = D_800BE9E4;
    s32 i;

    for (i = 0; i < 3; i++) {
        if (rate[i] != target[i]) {
            if (target[i] < rate[i]) {
                rate[i] -= step;
                if (rate[i] < target[i]) {
                    rate[i] = target[i];
                }
            } else {
                rate[i] += step;
                if (target[i] < rate[i]) {
                    rate[i] = target[i];
                }
            }
        }
        angle[i] += rate[i] * ticks;
        if (angle[i] < 0.0f) {
            angle[i] += 360.0f;
        } else if (360.0f <= angle[i]) {
            angle[i] -= 360.0f;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_151172FC.s")
#endif

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_15117424.s")

#ifdef NON_MATCHING
// swing_angle_step: spring-damped swing of one angle (degrees) of a swinging object towards its rest angle (the signed
// low 10 bits of +0x3C); returns the new angle (callers func_15117A20 / 15117A48 / 15117A70 pick the axis). Speed
// +0x84, spring +0x80, damping +0x7C. At rest at the target nothing happens; a swing that starts from rest plays the
// move sound of the D_80089600 entry (+0x3C >> 10). The speed gains spring * |offset| towards the target
// (func_15048A70 = signed angle difference) and is damped; when both are below 0.01 the angle snaps to the target.
// The angle stays in [0, 360).
f32 func_15117858(f32 *arg0, f32 angle) {
    u8 *obj = (u8 *) arg0;
    f32 damp = *(f32 *) (obj + 0x7C);
    s32 params = *(s32 *) (obj + 0x3C);
    f32 spring = *(f32 *) (obj + 0x80);
    f32 speed = *(f32 *) (obj + 0x84);
    f32 rest = (f32) ((params << 22) >> 22);
    s32 kind;
    f32 diff;

    if (angle == rest && speed == 0.0f) {
        return angle;
    }
    kind = params >> 10;
    if (speed == 0.0f && kind != 0 && D_80089600[kind].move_sfx != 0) {
        func_151152A4(obj, D_80089600[kind].move_sfx, 0x5DC0, 0xC8, 0x9C4, 0);
    }
    angle += speed * (f32) D_800BE9E4;
    diff = func_15048A70(angle, rest);
    if (0.0f < diff) {
        speed += fabsf(diff) * spring;
    } else {
        speed -= fabsf(diff) * spring;
    }
    speed *= damp;
    if (fabsf(diff) < 0.01f && fabsf(speed) < 0.01f) {
        angle = rest;
        speed = 0.0f;
    } else if (angle < 0.0f) {
        angle += 360.0f;
    } else if (360.0f <= angle) {
        angle -= 360.0f;
    }
    *(f32 *) (obj + 0x84) = speed;
    return angle;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_15117858.s")
#endif

void func_15117A20(f32 *arg0) {
    arg0[2] = func_15117858(arg0, arg0[2]);
}

void func_15117A48(f32 *arg0) {
    arg0[1] = func_15117858(arg0, arg0[1]);
}

void func_15117A70(f32 *arg0) {
    arg0[0] = func_15117858(arg0, arg0[0]);
}

#ifdef NON_MATCHING
// pendulum_angle_step: like func_15117858 with a bounce instead of a spring: the swing speed (+0x84) grows by
// +0x80 * D_800BE9E4 towards the rest angle (signed low 10 bits of +0x3C); when the angle crosses the rest angle it
// lands on it and the speed reverses scaled by +0x7C (-bounce * speed). A swing that starts from rest plays the
// move sound of the D_80089600 entry (+0x3C >> 10). Near rest (|offset| < 2, |speed| < 1) it stops; the angle
// stays in [0, 360). Returns the new angle (callers func_15117CF0 / 15117D18 pick the axis).
f32 func_15117A98(f32 *arg0, f32 angle) {
    u8 *obj = (u8 *) arg0;
    f32 bounce = *(f32 *) (obj + 0x7C);
    f32 accel = *(f32 *) (obj + 0x80) * (f32) D_800BE9E4;
    s32 params = *(s32 *) (obj + 0x3C);
    f32 speed = *(f32 *) (obj + 0x84);
    f32 rest = (f32) ((params << 22) >> 22);
    s32 kind;
    f32 before;
    f32 diff;

    if (angle == rest && speed == 0.0f) {
        return angle;
    }
    kind = params >> 10;
    if (speed == 0.0f && kind != 0 && D_80089600[kind].move_sfx != 0) {
        func_151152A4(obj, D_80089600[kind].move_sfx, 0x5DC0, 0xC8, 0x9C4, 0);
    }
    before = func_15048A70(angle, rest);
    angle += speed * (f32) D_800BE9E4;
    diff = func_15048A70(angle, rest);
    if ((diff <= 0.0f && 0.0f < before) || (0.0f <= diff && before < 0.0f)) {
        diff = 0.0f;
        angle = rest;
        speed = -bounce * speed;
    } else if (0.0f < diff) {
        speed += accel;
    } else {
        speed -= accel;
    }
    if (fabsf(diff) < 2.0f && fabsf(speed) < 1.0f) {
        angle = rest;
        speed = 0.0f;
    } else if (angle < 0.0f) {
        angle += 360.0f;
    } else if (360.0f <= angle) {
        angle -= 360.0f;
    }
    *(f32 *) (obj + 0x84) = speed;
    return angle;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_15117A98.s")
#endif

void func_15117CF0(f32 *arg0) {
    arg0[0] = func_15117A98(arg0, arg0[0]);
}

void func_15117D18(f32 *arg0) {
    arg0[2] = func_15117A98(arg0, arg0[2]);
}

#ifdef NON_MATCHING
void func_15104A80(u8 *);

void func_15117D40(u8 *arg0) {
    s32 sp1C;
    void (*var_t0)(u8 *); // P256: only func_15104A80 (prop_owner_effects_clear), called with the object in a0
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
                var_t0(arg0); // P256: the asm jalr passes a0 = arg0 (a1-a3 = step, flag, 3 are not read)
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
#ifdef NON_MATCHING
// gate_swing_update: world mesh record (D_800DBEF4, 0xA0 bytes) handler at D_800893D8 for the per-level push gate / door
// (levels 1 / 0x29, 0xB, 0x17, 0x28, 0x2F, 0x35, 0x3C, 0x40, 0x41; other levels do nothing). The level case gives the
// open angle, the handle point (scaled by +0x2C..+0x34), the squared reach (scaled by +0x34 squared) and the creak
// sound; bit 3 of +0x73 marks gates that only close when told to (state 1). A player (D_800CC2D0, D_8008FD8C of them)
// near the handle and not busy (+0x31C byte +0x6B < 4) pushes it: state 2 (opening) waits 50 ticks (+0x7C bits 8..15)
// then swings +0x0 up to the open angle with speed +0x84 / acceleration +0x80, plays sound 0x14 and sets state 3
// (open). With bit 2 of +0x73 the gate is pushed from the other side and only drives the player's +0x6B state (3 -> 4).
// The player's +0x6C..+0x70 get the handle position. Without a player it swings shut (state 1 -> 0). +0x4F bit 5 is set
// while it is opening or waiting.
void func_15060A30(s32, void *);
void func_15118324(u8 *arg0, f32 arg1, f32 arg2, f32 arg3, u8 *arg4);

void func_151184BC(u8 *rec) {
    f32 pos[3];
    f32 open = 40.0f;
    f32 reach = 40000.0f;
    f32 x;
    f32 y;
    f32 z;
    f32 acc;
    f32 spd;
    f32 dx;
    f32 dy;
    f32 dz;
    s32 sound = 0x4B8;
    s32 state = rec[0x73] & 3;
    s32 back = rec[0x73] & 4;
    s32 closeOnly = rec[0x73] & 8;
    s32 timer;
    s32 started;
    s32 n;
    s32 i;
    u8 *player;
    u8 *p;
    u8 *q;

    switch (D_800BE9F0) {
        case 0x1:
        case 0x29:
            x = -13.0f;
            y = 76.0f;
            z = 354.0f;
            reach = 10000.0f;
            break;
        case 0xB:
            x = 70.0f;
            y = 120.0f;
            z = 329.0f;
            sound = 0x4BA;
            closeOnly = 8;
            break;
        case 0x17:
            x = 0.0f;
            y = 125.0f;
            z = 322.0f;
            break;
        case 0x28:
            open = 55.0f;
            x = 0.0f;
            y = 99.0f;
            z = 168.0f;
            closeOnly = 8;
            break;
        case 0x35:
            open = 20.0f;
            x = 0.0f;
            y = -328.0f;
            z = 549.0f;
            break;
        case 0x2F:
            open = 90.0f;
            reach = 5625.0f;
            x = 0.0f;
            y = 61.0f;
            z = 104.0f;
            closeOnly = 8;
            break;
        case 0x3C:
            open = 30.0f;
            reach = 10000.0f;
            x = 22.0f;
            y = 13.0f;
            z = 419.0f;
            closeOnly = 8;
            break;
        case 0x41:
            open = 45.0f;
            if (back == 4) {
                reach = -1.0f;
            }
            x = 0.0f;
            y = 25.0f;
            z = 336.0f;
            closeOnly = 8;
            break;
        case 0x40:
            open = 45.0f;
            x = 0.0f;
            y = 47.0f;
            z = 72.0f;
            closeOnly = 8;
            reach = 10000.0f;
            break;
        default:
            return;
    }
    x *= *(f32 *) (rec + 0x2C);
    y *= *(f32 *) (rec + 0x30);
    z *= *(f32 *) (rec + 0x34);
    reach *= *(f32 *) (rec + 0x34) * *(f32 *) (rec + 0x34);
    if (*(s32 *) (rec + 0x7C) == 0) {
        *(s32 *) (rec + 0x7C) = 2;
        if (state == 3) {
            *(f32 *) rec = open;
        }
    }
    acc = *(f32 *) (rec + 0x80);
    timer = (*(s32 *) (rec + 0x7C) >> 8) & 0xFF;
    started = *(s32 *) (rec + 0x7C) & 1;
    spd = *(f32 *) (rec + 0x84);
    func_15118324(rec, x, y, z, (u8 *) pos);

    player = NULL;
    if (state != 3 && state != 1) {
        n = D_8008FD8C;
        for (p = (u8 *) D_800CC2D0; p < (u8 *) D_800CC2D0 + n * 0x32C; p += 0x32C) {
            if (p[0x65] != 0 || p[0x104] != 0) {
                continue;
            }
            q = *(u8 **) (p + 0x31C);
            if (q[0x17] != 0 || q[0x27] != 0 || q[0x6B] >= 4) {
                continue;
            }
            if (*(f32 *) (p + 0x18) + 40.0f < pos[1]) {
                dy = (*(f32 *) (p + 0x18) + *(s16 *) (p + 0xE6)) - pos[1];
                dz = *(f32 *) (p + 0x1C) - pos[2];
                dx = *(f32 *) (p + 0x14) - pos[0];
                if (dz * dz + (dx * dx + dy * dy) < reach) {
                    player = p;
                    break;
                }
            }
        }
    }
    if (player == NULL && state == 2) {
        n = D_8008FD8C;
        p = (u8 *) D_800CC2D0;
        for (i = 0; i < n; i++, p += 0x32C) {
            if ((*(u8 **) (p + 0x31C))[0x6B] != 0) {
                player = p;
                break;
            }
        }
    }

    if (player != NULL || state == 2) {
        if (player != NULL && !started) {
            func_15060A30(0x16B, player);
        }
        if (!back) {
            if (!started) {
                timer = 50;
                started++;
                acc = 0.0f;
            }
            state = 2;
            if (player != NULL) {
                (*(u8 **) (player + 0x31C))[0x6B] = (timer != 0) ? 1 : 2;
            }
            if (timer != 0) {
                timer = (D_800BE9E4 < timer) ? timer - D_800BE9E4 : 0;
            } else {
                spd += acc;
                if (spd > 30.0f) {
                    spd = 30.0f;
                }
                acc += 0.03f;
                if (acc > 0.2f && *(u16 *) (rec + 0x74) == 0) {
                    func_151152A4(rec, sound, 0x7D00, 0x5DC, 0xDAC, 0);
                }
                *(f32 *) rec += spd;
                if (open <= *(f32 *) rec) {
                    *(f32 *) rec = open;
                    state = 3;
                    started = 0;
                    spd = 0.0f;
                    acc = 0.0f;
                    func_151152A4(rec, 0x14, 0x7D00, 0x5DC, 0xDAC, 4);
                    if (player != NULL) {
                        (*(u8 **) (player + 0x31C))[0x6B] = 0;
                    }
                }
            }
            if (player != NULL) {
                func_15118324(rec, x, y, z, (u8 *) pos);
                q = *(u8 **) (player + 0x31C);
                *(s16 *) (q + 0x6C) = (s32) pos[0];
                *(s16 *) (q + 0x6E) = (s32) pos[1];
                *(s16 *) (q + 0x70) = (s32) pos[2];
            }
        } else if (player != NULL && (q = *(u8 **) (player + 0x31C)) != NULL) {
            if (!started && q[0x6B] == 0) {
                timer = 50;
                started++;
            }
            if (timer != 0) {
                q[0x6B] = 3;
            } else if (q[0x6B] == 3) {
                q[0x6B] = 4;
                started = 0;
            }
            if (timer != 0) {
                timer = (D_800BE9E4 < timer) ? timer - D_800BE9E4 : 0;
            }
        }
        if (player != NULL && *(u8 **) (player + 0x31C) != NULL) {
            func_15118324(rec, x, y, z, (u8 *) pos);
            q = *(u8 **) (player + 0x31C);
            *(s16 *) (q + 0x6C) = (s32) pos[0];
            *(s16 *) (q + 0x6E) = (s32) pos[1];
            *(s16 *) (q + 0x70) = (s32) pos[2];
        }
    } else if ((!closeOnly || state == 1) && *(f32 *) rec > 0.0f) {
        if (!started) {
            acc = 0.1f;
            started++;
        }
        spd += 0.1f;
        state = 1;
        if (spd > 30.0f) {
            spd = 30.0f;
        }
        acc += 0.05f;
        *(f32 *) rec -= spd;
        if (*(f32 *) rec <= 0.0f) {
            *(f32 *) rec = 0.0f;
            started = 0;
            state = 0;
            acc = 0.0f;
            spd = 0.0f;
        }
    }

    rec[0x73] = (rec[0x73] & ~3) | state;
    *(s32 *) (rec + 0x7C) = (*(s32 *) (rec + 0x7C) & 0xFE) | (timer << 8) | started;
    *(f32 *) (rec + 0x80) = acc;
    *(f32 *) (rec + 0x84) = spd;
    rec[0x4F] &= ~0x60;
    if (state == 2 || (state == 0 && timer != 0)) {
        rec[0x4F] |= 0x20;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_151184BC.s")
#endif

#ifdef NON_MATCHING
void func_15118F2C(s32 arg0, s32 arg1);
#endif
void func_15118EEC(s32 arg0) {
    func_15118F2C(arg0, 0);
}

void func_15118F0C(s32 arg0) {
    func_15118F2C(arg0, 3);
}

#ifdef NON_MATCHING
// mover_swing_step: swings a world mesh record (D_800DBEF4, 0xA0 bytes) about its yaw +0x4 like a door. +0x3C: low 10 bits
// = signed open angle, bits 10..15 = D_80089600 sound row, top byte = light slot + 1 (0 = none). +0x73 bits 0..1 = state
// (0 closed, 1 closing, 2 opening, 3 open; bit 2 picks the other default constants, which hold the same values), +0x7C = acceleration (0 -> 0.3), +0x80 = top speed
// (0 -> 0.075), +0x84 = angular velocity. Starting from rest plays the row's open / close sound; arriving bounces back
// (velocity * -accel) until it is below 1, then snaps, sets state 3 / 0 and plays the open / close stop sound. The new
// yaw is stored unless the netplay owner check says otherwise; on level 2 it sets func_1000E75C's level from the open
// fraction, elsewhere a light slot is dimmed by it (func_151885BC / func_151741D0, plus func_15174200 for slot 0 on level 1).
// func_15118EEC / func_15118F0C pass arg1 (0 / 3) through to func_1511FF00. Reached through the D_800893D8 table.
void func_1511FF00(u8 *arg0, s32 arg1);
f32 func_15048A70(f32 arg0, f32 arg1);
s32 func_151152A4(u8 *obj, s32 sound, s32 vol, s16 r0, s16 r1, s32 flags);
s32 func_15022BB0(s32 arg0, s32 arg1);
void func_1000E75C(s32 arg0);
void func_151885BC(s32 arg0, f32 arg1);
void func_151741D0(s32 arg0, s32 arg1);
void func_15174200(s32 arg0, s32 arg1, s32 arg2);

void func_15118F2C(s32 arg0, s32 arg1) {
    u8 *rec = (u8 *) arg0;
    MoverSfx *row;
    s32 bits;
    s32 angle;
    s32 kind;
    s32 state;
    s32 sound = 0;
    s32 slot;
    s32 level;
    f32 open;
    f32 target;
    f32 yaw;
    f32 vel;
    f32 accel;
    f32 top;
    f32 diff;
    f32 frac;

    func_1511FF00(rec, arg1);
    bits = *(s32 *) (rec + 0x3C);
    angle = (bits << 22) >> 22;
    kind = (bits & 0xFC00) >> 10;
    row = &D_80089600[kind];
    open = angle;
    target = open;
    state = rec[0x73] & 3;
    yaw = *(f32 *) (rec + 4);
    vel = *(f32 *) (rec + 0x84);
    if (state == 0 || state == 1) {
        target = 0.0f;
    }
    if (state == 0 || state == 3) {
        vel = 0.0f;
        yaw = target;
    }
    if (yaw == target && vel == 0.0f) {
        *(f32 *) (rec + 0x84) = vel;
    } else {
        if (*(f32 *) (rec + 0x7C) == 0.0f) {
            *(f32 *) (rec + 0x7C) = 0.3f;
        }
        accel = *(f32 *) (rec + 0x7C);
        if (*(f32 *) (rec + 0x80) == 0.0f) {
            *(f32 *) (rec + 0x80) = 0.075f;
        }
        top = *(f32 *) (rec + 0x80);
        if (vel == 0.0f) {
            sound = (target == 0.0f) ? row->unk2 : row->move_sfx;
        }
        yaw += vel;
        diff = func_15048A70(yaw, target);
        if (fabsf(diff) < fabsf(vel)) {
            vel = -vel * accel;
            if (fabsf(vel) < 1.0f) {
                vel = 0.0f;
                if (target == 0.0f) {
                    sound = row->unk6;
                    state = 0;
                } else {
                    sound = row->stop_sfx;
                    state = 3;
                }
                yaw = target;
            } else {
                *(f32 *) (rec + 0x80) = top * 0.5f;
            }
        } else if (diff > 0.0f) {
            vel += top;
            if (vel > 5.0f) {
                vel = 5.0f;
            }
        } else {
            vel -= top;
            if (vel < -5.0f) {
                vel = -5.0f;
            }
        }
        if (fabsf(diff) > 30.0f && diff * vel < 0.0f) {
            vel = 0.0f;
        }
        if (yaw < -180.0f) {
            yaw += 360.0f;
        } else if (yaw >= 180.0f) {
            yaw -= 360.0f;
        }
        rec[0x73] = (rec[0x73] & ~3) | state;
        if (sound != 0) {
            func_151152A4(rec, sound, 0x5DC0, 0x9C4, 0x1194, 0);
        }
        *(f32 *) (rec + 0x84) = vel;
    }
    if (D_800BE9B4 == 0 && yaw == *(f32 *) (rec + 4)) {
        return;
    }
    if (D_800C35EA == 1 && func_15022BB0((rec - (u8 *) D_800DBEF4) / 0xA0, 0) != 0) {
        yaw = *(f32 *) (rec + 4);
    } else {
        *(f32 *) (rec + 4) = yaw;
    }
    slot = (u8) (*(s32 *) (rec + 0x3C) >> 24);
    if (D_800BE9F0 == 2) {
        func_1000E75C((s32) (255.0f - fabsf((yaw - open) * 255.0f / open)));
        return;
    }
    if (slot == 0) {
        return;
    }
    frac = 1.0f - fabsf((fabsf(yaw) - (f32) (angle < 0 ? -angle : angle)) / open);
    func_151885BC(slot - 1, frac);
    level = (s32) (frac * 255.0f);
    func_151741D0(level, slot - 1);
    if (D_800BE9F0 == 1 && slot - 1 == 0) {
        func_15174200(level, 0, 0xF8);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_15118F2C.s")
#endif

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_151194A4.s")

void func_1511992C(u8 *arg0, s32 *arg1) {
    if ((arg1[0] == 1) && (((u8 *)arg1)[0x65] == 0) && !(arg0[0x73] & 3) && !(arg0[0x73] & 4)) {
        arg0[0x73] &= ~3;
        arg0[0x73] |= 2;
    }
}

#ifdef NON_MATCHING
// mover_bob_y_update: (port-b P194 draft, verified and inserted P195). World mesh record (D_800DBEF4, 0xA0 bytes) handler: moves the record's y (+0x12) towards
// base + (phase * amplitude) / 256, where phase = the upper half of +0x3C (unsigned), amplitude = +0x80 and the base y
// is latched once into +0x84 (low half = the starting y, bit 31 marks it as set). It moves at most +0x7C (speed) per
// call; +0x7C == 0 does nothing. The "arrived" bits 0 / 1 of +0x73 are cleared while it moves and both set when y is
// already at the target.
void func_15119974(u8 *rec) {
    s16 *y = (s16 *) (rec + 0x12);
    s32 speed;
    s32 target;
    s32 diff;

    if (*(s32 *) (rec + 0x84) == 0) {
        *(s32 *) (rec + 0x84) = *y | 0x80000000;
    }
    speed = *(s32 *) (rec + 0x7C);
    if (speed == 0) {
        return;
    }
    rec[0x73] &= ~3;
    target = (s32) ((u16) (*(s32 *) (rec + 0x3C) >> 16) * *(s32 *) (rec + 0x80)) / 256 + (s16) *(s32 *) (rec + 0x84);
    if (target == *y) {
        rec[0x73] |= 3;
        return;
    }
    diff = *y - target;
    if (diff < 0) {
        if (-diff < speed) {
            *y = target;
        } else {
            *y += speed;
        }
    } else if (diff < speed) {
        *y = target;
    } else {
        *y -= speed;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_15119974.s")
#endif

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
#ifdef NON_MATCHING
f32 func_150484A0(f32, f32);
f32 func_150489B0(u8);
f32 func_15048A40(u8);

// mesh_cluster_spin: splits the vertices (obj + 0x28, 16-byte records, count +0x16) into clusters with
// func_15119A54 (seed = each unassigned vertex outside the radius, 100 or 400 for kinds 0x21 / 0x22; cluster tag at
// +6). Then, last cluster first, rotates each cluster whose centre angle a (func_150484A0(sum x, sum z) in 256ths)
// exceeds its tag by -a (sin func_15048A40 / cos func_150489B0) in the x/z plane and re-tags its vertices
// ((tag - 1) & 3) << 8 | a. Sets the done flag +0x84.
void func_15119C54(u8 *obj) {
    s16 *v = *(s16 **) (obj + 0x28);
    s32 radius = 100;
    s32 tag = 0;
    s32 i;
    s32 sx, sz, a;
    f32 s, c, x, z;

    if (*(u16 *) (obj + 0x54) == 0x21 || *(u16 *) (obj + 0x54) == 0x22) {
        radius = 400;
    }
    *(s32 *) (obj + 0x84) = 1;
    for (i = 0; i < *(u16 *) (obj + 0x16); i++, v += 8) {
        if (*(u16 *) &v[3] == 0 && radius < v[2] * v[2] + v[0] * v[0]) {
            tag++;
            v[3] = tag;
            func_15119A54(obj, (u8 *) v, radius, tag);
        }
    }
    for (; tag != 0; tag--) {
        sx = 0;
        sz = 0;
        v = *(s16 **) (obj + 0x28);
        for (i = 0; i < *(u16 *) (obj + 0x16); i++, v += 8) {
            if (*(u16 *) &v[3] == tag) {
                sx += v[0];
                sz += v[2];
            }
        }
        if (sx == 0 && sz == 0) {
            continue;
        }
        a = (s32) (func_150484A0((f32) sx, (f32) sz) * 40.743664f) & 0xFF;
        if (tag >= a) {
            continue;
        }
        s = func_15048A40(-a & 0xFF);
        c = func_150489B0(-a & 0xFF);
        v = *(s16 **) (obj + 0x28);
        for (i = 0; i < *(u16 *) (obj + 0x16); i++, v += 8) {
            if (*(u16 *) &v[3] == tag) {
                z = (f32) v[2];
                x = (f32) v[0];
                v[3] = (((tag - 1) & 3) << 8) | a;
                v[0] = (s32) (z * s + x * c);
                v[2] = (s32) (z * c - x * s);
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_15119C54.s")
#endif

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_15119EB8.s")

#ifdef NON_MATCHING
// pickup_spin_update: world mesh record (D_800DBEF4, 0xA0 bytes) handler for a spinning, bobbing pickup (P195). The phase
// +0x7C advances by 5 degrees * D_800BE9A4 (wrapping at 6 pi) and drives the tilt +0x0 / +0x8 (15 * sin / cos), the
// spin +0x4 (phase * 60 / pi) and the bob of y +0x12 around the base +0x80 (latched from y). While +0x84 (respawn
// timer, in ticks) is 0, the first live player (D_800CC2D0, D_8008FD8C of them; +0x3C >= 0) within 80 units on the
// ground plane and in its height band fades it in by distance; touching it with +0x1CA set gives the item
// (func_15060BA4): respawning pickups (+0x3C high half = respawn time / 50) start their timer and set +0x70 bit 2,
// others are marked taken (+0x6E) and saved through func_1508F26C(2, index); then sound 0x1CF and the effect
// func_151D6F64. +0x8A is the alpha, +0x4F the draw flags (0x21 idle, 0x31 fading, 0x20 taken).
s32 func_1507C7C0(struct127 *, s16 *, s16 *, s16 *);
s32 func_15060BA4(struct127 *arg0, s32 arg1);
void func_1508F26C(s32 arg0, s32 arg1);
u16 func_10010344(u16 sfx, struct127 *obj, s32 vol, s16 arg3, u16 arg4);
void func_151D6F64(s16 *arg0, struct127 *arg1);

void func_1511A540(u8 *rec) {
    u8 *p;
    f32 phase;
    f32 d2;
    f32 dx;
    f32 dz;
    f32 y;
    s16 height;
    s16 unk4C;
    s16 unk4A;
    s32 v;

    if (*(s32 *) (rec + 0x84) < 0x20) {
        if (*(s32 *) (rec + 0x80) == 0) {
            *(s32 *) (rec + 0x80) = *(s16 *) (rec + 0x12);
        }
        *(f32 *) (rec + 0) = sinf(*(f32 *) (rec + 0x7C)) * 15.0f;
        *(f32 *) (rec + 4) = *(f32 *) (rec + 0x7C) * 19.098593f;
        *(f32 *) (rec + 8) = cosf(*(f32 *) (rec + 0x7C)) * 15.0f;
        *(f32 *) (rec + 0x7C) += 0.08726647f * D_800BE9A4;
        phase = *(f32 *) (rec + 0x7C);
        if (18.849556f <= phase) {
            *(f32 *) (rec + 0x7C) = phase - 18.849556f;
            phase = *(f32 *) (rec + 0x7C);
        }
        *(s16 *) (rec + 0x12) = (s32) (cosf(phase + phase) * 10.0f) + *(s32 *) (rec + 0x80) + 10;
        if (*(s32 *) (rec + 0x84) != 0) {
            rec[0x4F] = 0x31;
            rec[0x8A] = (0x20 - *(s32 *) (rec + 0x84)) << 3;
        } else {
            for (p = (u8 *) D_800CC2D0; p < (u8 *) D_800CC2D0 + D_8008FD8C * 0x32C; p += 0x32C) {
                if (*(s32 *) p == 0 || p[0x127] == 0xFF || *(s32 *) (rec + 0x3C) < 0) {
                    continue;
                }
                dz = *(s16 *) (rec + 0x14) - *(f32 *) (p + 0x1C);
                dx = *(s16 *) (rec + 0x10) - *(f32 *) (p + 0x14);
                d2 = dz * dz + dx * dx;
                if (!(d2 < 6400.0f)) {
                    rec[0x8A] = 0xFF;
                    rec[0x4F] = 0x21;
                    continue;
                }
                func_1507C7C0((struct127 *) p, &height, &unk4C, &unk4A);
                rec[0x4F] = 0x31;
                y = *(s16 *) (rec + 0x12);
                if (*(f32 *) (p + 0x18) < y + 80.0f && y - 80.0f < *(f32 *) (p + 0x18) + height && p[0x1CA] != 0) {
                    if (func_15060BA4((struct127 *) p, 1) != 0) {
                        v = *(s32 *) (rec + 0x3C);
                        if (v != 0) {
                            *(s32 *) (rec + 0x84) = ((v >> 16) & 0xFFFF) * 50;
                            rec[0x70] |= 4;
                        } else {
                            rec[0x6E] = 1;
                            func_1508F26C(2, ((rec - (u8 *) D_800DBEF4) / 0xA0) & 0xFFFF);
                        }
                        rec[0x4F] = 0x20;
                        func_10010344(0x1CF, (struct127 *) p, 0x7D00, 0xC8, 0x9C4);
                        func_151D6F64((s16 *) rec, (struct127 *) p);
                    } else {
                        rec[0x4F] = 0x31;
                        rec[0x8A] = (u32) ((0.25f + d2 * 0.0001171875f) * 255.0f);
                    }
                    break;
                }
            }
        }
    }
    if (*(s32 *) (rec + 0x84) > 0) {
        *(s32 *) (rec + 0x84) -= D_800BE9E4;
        if (*(s32 *) (rec + 0x84) <= 0) {
            *(s32 *) (rec + 0x84) = 0;
            rec[0x8A] = 0xFF;
            rec[0x4F] = 0x21;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_1511A540.s")
#endif

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
#ifdef NON_MATCHING
// obj_texture_anim_step: steps the animated texture of a scenery object. The first D_800896C4 entry that applies
// (level filter -1 or the current level D_800BE9F0; id 0xFF = any, else the object's +0x54 type, with 0x8000 set for
// level-filtered entries) gives the frame table, frame count, ticks per frame and ping-pong flag. *slots holds the
// object's texture slot (looked up once from its +0x1C texture list by func_1511A998: index << 16 | slot) and
// *state the playing direction (high half) and the tick counter (low half). The frame texture is loaded
// (func_1510D66C, age 3 on levels 6 / 0x3B else 0x3E) and patched into the display list (func_1510DDF4).
typedef struct {
    /* 0x0 */ s32 *frames;
    /* 0x4 */ u8 count;
    /* 0x5 */ u8 id;
    /* 0x6 */ s8 level;
    /* 0x7 */ u8 ticks;
    /* 0x8 */ u8 pingpong;
} TexAnim; // 0xC
extern TexAnim D_800896C4[24];
s32 func_1511A998(s8 *arg0, s32 *arg1);
s32 func_1510D66C(s32 id, s32 *outSize, s32 age, s32 addRef);
void func_1510DDF4(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4);

void func_1511AA1C(u8 *obj, s32 *slots, s32 *state) {
    TexAnim *e;
    TexAnim *found = NULL;
    s32 id;
    s32 second;
    s32 dir;
    s32 tick;
    s32 tex;
    s32 size;
    s32 end;

    for (e = D_800896C4; e != D_800896C4 + 24; e++) {
        id = e->id;
        if (e->level != -1) {
            if (D_800BE9F0 != e->level) {
                continue;
            }
            if (id != 0xFF) {
                id |= 0x8000;
            }
        }
        if (id == 0xFF || id == *(u16 *)(obj + 0x54)) {
            found = e;
            break;
        }
    }
    if (found == NULL) {
        return;
    }
    if (*slots == 0) {
        *slots = func_1511A998(*(s8 **)(obj + 0x1C), &second);
        *slots |= second << 16;
    } else {
        second = (*slots >> 16) & 0xFFFF;
    }
    dir = (s16)(*state >> 16);
    if (dir == 0) {
        dir = 1;
    }
    tick = (*state & 0xFFFF) + dir;
    if (found->pingpong) {
        if (tick < 0) {
            dir = 1;
            tick = found->ticks;
        } else if (tick >= found->count * found->ticks) {
            dir = -1;
            tick = (found->count - 1) * found->ticks;
        }
    } else if (tick >= found->count * found->ticks) {
        tick -= found->count * found->ticks;
        dir = 1;
    }
    tex = func_1510D66C(found->frames[tick / found->ticks], &size,
                        (D_800BE9F0 == 6 || D_800BE9F0 == 0x3B) ? 3 : 0x3E, 0);
    end = 0;
    if (second != 0) {
        end = size + tex - 0x20;
    }
    func_1510DDF4((s32)obj, tex, end, 4, 5);
    *state = (dir << 16) | tick;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_1511AA1C.s")
#endif

void func_1511AC84(u8 *arg0) {
    if (*(s32 *)(arg0 + 0x3C) != 0) {
        func_15116690(arg0);
    }
    func_1511AA1C(arg0, arg0 + 0x80, arg0 + 0x84);
}

s32 func_15022BB0(s32, s32);
void func_15116854(u8 *);

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

#ifdef NON_MATCHING
f32 sinf(f32);
f32 cosf(f32);

/* D_800A3340: vertex count, then (vertex index, reference object 0 / 1) pairs */
static const u8 D_800A3340_pairs[17] = {
    8, 0, 0, 1, 1, 2, 0, 3, 1, 4, 0, 5, 1, 6, 1, 7, 0,
};

// part_vertices_follow_refs: rotates this part's 8 template vertices (obj + 0x28) around two reference objects
// (obj - 0xA0 and obj - 0x140) by each reference's yaw (+0x8, degrees) and writes them into the current vertex
// buffer (obj + 0x20 + D_800BE9C0 * 4), offset by the part position (+0x10/+0x12/+0x14). Runs while the redraw
// counter +0x7C is non-zero; a change of either reference yaw (cached at +0x80 / +0x84) restarts it at 2.
// Only for obj + 0x3C == 0: otherwise the asm reads uninitialised locals (the reference pointers and the table
// are set only in that branch) and draws nothing; the C does nothing in that case.
void func_1511BD5C(u8 *obj) {
    u8 *ref[2];
    const u8 *pair;
    s32 n;
    u8 *r;
    s16 *src;
    s32 dx, dy, sx, sy, sz;
    f32 ang, s, c, fx, fy;

    if (*(s32 *) (obj + 0x3C) != 0) {
        return;
    }
    n = D_800A3340_pairs[0];
    ref[0] = obj - 0xA0;
    ref[1] = obj - 0x140;
    pair = &D_800A3340_pairs[1];

    if (*(f32 *) (obj + 0x80) != *(f32 *) (ref[0] + 8) || *(f32 *) (obj + 0x84) != *(f32 *) (ref[1] + 8)) {
        *(f32 *) (obj + 0x80) = *(f32 *) (ref[0] + 8);
        *(s32 *) (obj + 0x7C) = 2;
        *(f32 *) (obj + 0x84) = *(f32 *) (ref[1] + 8);
    }
    if (*(s32 *) (obj + 0x7C) == 0) {
        return;
    }
    *(s32 *) (obj + 0x7C) -= 1;

    while (n-- != 0) {
        r = ref[pair[1]];
        dx = *(s16 *) (r + 0x10) - *(s16 *) (obj + 0x10);
        dy = *(s16 *) (r + 0x12) - *(s16 *) (obj + 0x12);
        ang = -*(f32 *) (r + 8) * 0.0174532924f;
        s = sinf(ang);
        c = cosf(ang);
        src = (s16 *) (*(u8 **) (obj + 0x28) + pair[0] * 16);
        fy = (f32) (src[1] - dy);
        fx = (f32) (src[0] - dx);
        sz = src[2] + *(s16 *) (obj + 0x14);
        sy = (s32) (fy * c - fx * s) + dy + *(s16 *) (obj + 0x12);
        sx = (s32) (fy * s + fx * c) + dx + *(s16 *) (obj + 0x10);
        *(s16 *) (*(u8 **) (obj + 0x20 + D_800BE9C0 * 4) + pair[0] * 16 + 0) = sx;
        *(s16 *) (*(u8 **) (obj + 0x20 + D_800BE9C0 * 4) + pair[0] * 16 + 2) = sy;
        *(s16 *) (*(u8 **) (obj + 0x20 + D_800BE9C0 * 4) + pair[0] * 16 + 4) = sz;
        pair += 2;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_1511BD5C.s")
#endif

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
void func_151714BC(u8 *, u8, s32); /* P274: 3 arguments, void (the asm caller also sets a3 = 1, unused) */
void func_151741D0(s32, s32);
/* D_800A3354 (rodata in func_1511BD5C's GLOBAL_ASM): the three hit sound ids, copied to the stack table */
static const u16 D_800A3354_ids[3] = { 0x2B6, 0x2BD, 0x2BE };
s32 func_1000EC24(s32, s32, s32, s32, s32, s32, s32); /* a function (init_EB00.c), not data */

void func_1511CBC0(u8 *arg0) {
    struct {
        u16 u50[3]; /* P274: was u8 * (indexing read bytes through an uninitialised pointer) */
        u8 pad56[0x2];
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
                    func_151714BC(sp48, 0xFF, 0);
                    func_10010F30(0x2BE, 0x7FFFU, 0x40U, 0, 0U);
                    break;
                case 0:
                    temp_t9 = func_150ADA20() % 3U;
                    sp.u50[0] = D_800A3354_ids[0];
                    sp.u50[1] = D_800A3354_ids[1];
                    sp.u50[2] = D_800A3354_ids[2];
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

#ifdef NON_MATCHING
f32 func_150489B0(u8);

// mesh_tex_wave_update: handler (table EU 8008912C) for a mesh object: on first use allocates its 12-byte state
// (+0x7C: cached texture coordinates, two texture-animation words) and caches each source vertex's texture
// coordinates; every frame offsets the current vertex buffer's coordinates by (amp_s * cos-like(phase),
// amp_t * sin-like(phase)) (func_150489B0 / func_15048A40 of (+0x80 >> 4) & 0xFF; amplitudes = the low 12 bits and
// the next 12 bits of +0x3C), advances the phase +0x80 by the top byte of +0x3C * D_800BE9E4, then runs the texture
// animation (func_1511AA1C).
void func_1511DD44(u8 *obj) {
    s32 *st = *(s32 **)(obj + 0x7C);
    s16 *uv;
    s16 *dst;
    s32 i;
    s32 off;
    s32 packed;
    s32 amp_s;
    s32 amp_t;
    u32 speed;
    u8 phase;
    f32 a;
    f32 b;
    s16 ds;
    s16 dt;

    if (st == NULL) {
        st = (s32 *)allocate_memory(0xC, 1, 0, 0);
        *(s32 **)(obj + 0x7C) = st;
        st[1] = 0;
        st[2] = 0;
        uv = allocate_memory(*(u16 *)(obj + 0x16) * 4, 1, 0, 0);
        st[0] = (s32)uv;
        dst = uv;
        for (i = 0, off = 0; i < *(u16 *)(obj + 0x16); i++, off += 0x10) {
            dst += 2;
            dst[-2] = *(s16 *)(*(u8 **)(obj + 0x28) + off + 8);
            dst[-1] = *(s16 *)(*(u8 **)(obj + 0x28) + off + 0xA);
        }
    } else {
        uv = (s16 *)st[0];
    }
    packed = *(s32 *)(obj + 0x3C);
    amp_s = packed & 0xFFF;
    amp_t = (packed >> 12) & 0xFFF;
    speed = (packed >> 24) & 0xFF;
    phase = (*(s32 *)(obj + 0x80) >> 4) & 0xFF;
    a = func_15048A40(phase);
    b = func_150489B0(phase);
    *(s32 *)(obj + 0x80) += speed * D_800BE9E4;
    if (*(u16 *)(obj + 0x16) > 0) {
        ds = (s32)((f32)amp_s * b);
        dt = (s32)((f32)amp_t * a);
        for (i = 0, off = 0; i < *(u16 *)(obj + 0x16); i++, off += 0x10) {
            *(s16 *)(*(u8 **)(obj + 0x20 + D_800BE9C0 * 4) + off + 8) = uv[i * 2] + ds;
            *(s16 *)(*(u8 **)(obj + 0x20 + D_800BE9C0 * 4) + off + 0xA) = uv[i * 2 + 1] + dt;
        }
    }
    func_1511AA1C(obj, st + 1, st + 2);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_1511DD44.s")
#endif

#ifdef NON_MATCHING
void func_15094EC8(u8 *, s32 *, s32, f32, s32, s32);

// mesh_tex_scroll_update: handler (table EU 80089318) for a mesh object: on first use caches each source vertex's
// texture coordinates minus 0x2000 (+0x7C, allocated) and writes the source positions plus the offset (+0x10..+0x14)
// into both vertex buffers (+0x24, +0x20); every frame advances the scroll (+0x80) by speed * 0.01 * D_800BE9E4
// (speed = low half of +0x3C) and rebuilds the current buffer's texture coordinates (func_15094EC8) with the two
// packed bytes of +0x3C (top byte signed).
void func_1511DF6C(u8 *obj) {
    s16 *uv = *(s16 **)(obj + 0x7C);
    s16 *dst;
    s32 i;
    s32 off;
    s32 packed;

    if (uv == NULL) {
        uv = allocate_memory(*(u16 *)(obj + 0x16) * 4, 1, 0, 0);
        *(s16 **)(obj + 0x7C) = uv;
        dst = uv;
        for (i = 0, off = 0; i < *(u16 *)(obj + 0x16); i++, off += 0x10) {
            dst += 2;
            dst[-2] = *(s16 *)(*(u8 **)(obj + 0x28) + off + 8) - 0x2000;
            dst[-1] = *(s16 *)(*(u8 **)(obj + 0x28) + off + 0xA) - 0x2000;
        }
        for (i = 0, off = 0; i < *(u16 *)(obj + 0x16); i++, off += 0x10) {
            *(s16 *)(*(u8 **)(obj + 0x20) + off + 0) = *(s16 *)(*(u8 **)(obj + 0x24) + off + 0) =
                *(s16 *)(*(u8 **)(obj + 0x28) + off + 0) + *(s16 *)(obj + 0x10);
            *(s16 *)(*(u8 **)(obj + 0x20) + off + 2) = *(s16 *)(*(u8 **)(obj + 0x24) + off + 2) =
                *(s16 *)(*(u8 **)(obj + 0x28) + off + 2) + *(s16 *)(obj + 0x12);
            *(s16 *)(*(u8 **)(obj + 0x20) + off + 4) = *(s16 *)(*(u8 **)(obj + 0x24) + off + 4) =
                *(s16 *)(*(u8 **)(obj + 0x28) + off + 4) + *(s16 *)(obj + 0x14);
        }
    }
    packed = *(s32 *)(obj + 0x3C);
    *(f32 *)(obj + 0x80) += (f32)((f32)(s16)packed * 0.01) * (f32)D_800BE9E4;
    func_15094EC8(*(u8 **)(obj + 0x20 + D_800BE9C0 * 4), (s32 *)uv, *(u16 *)(obj + 0x16), *(f32 *)(obj + 0x80),
                  packed >> 24, (packed >> 16) & 0xFF);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_1511DF6C.s")
#endif

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

#ifdef NON_MATCHING
s32 func_15031C4C(struct127 *, s32, s32);
u8 *func_1509B570(s32);
void func_151D6F20(s32, s32);
f32 cosf(f32);
typedef struct {
    u16 phase0;  /* 0x0: bob phase (x) */
    u16 phase1;  /* 0x2: bob phase (z) */
    u16 state;   /* 0x4: 0 growing, 1 wobbling, 2 shown, 3 shrinking (taken) */
    u16 wob;     /* 0x6: wobble phase */
    f32 amp;     /* 0x8: wobble amplitude */
    f32 scale;   /* 0xC: full scale (the placement's +0x2C) */
} Pickup1511E4F4;
#define PK_U8(p, o) (*(u8 *) ((u8 *) (p) + (o)))
#define PK_F32(p, o) (*(f32 *) ((u8 *) (p) + (o)))
#define PK_S16(p, o) (*(s16 *) ((u8 *) (p) + (o)))
#define PK_ANG (6.2831855f / 65536.0f)
/* pickup_update: world-object callback of type 0x28 (D_80089030[0x28][0], obj +0x38): a floating pickup. On the
 * first call it allocates its 0x10-byte state into obj +0x7C (the full scale from +0x2C; the scales +0x2C..+0x34
 * start at 0). Unless the object kind (+0x54) is 0x59 / 0x5A it spins (+4 += 1.52 per tick) and bobs (+0 / +0x18 from
 * two cosine phases). Kind 0x54 uses item 0x17 for func_15031C4C and is disabled on level 0x2D while object 0xBA's
 * +0x1FE4 is <= 0. While not taken (state < 3) the first player that is active (+0x0), alive (+0x1CA), not 0xFF
 * (+0x127), playing (+0x300), on the right team for the +0x84 filter (1 team 0, 2 not team 0, 3 even teams), that
 * does not already hold the item, and is within 100 * size (ctl +0x1AF / 64, * 1.4 with ctl +0x84) horizontally and
 * overlaps vertically (func_1507C7C0 height) takes it: +0x80 = the player's +0x3B, state 3, func_1511E320 and
 * func_151D6F20. Then the scale animation: grow by 0.26 * scale per tick, wobble (amplitude 0.3 falling by 0.02 *
 * scale) and shrink to 0 after being taken (then +0x6E = 1). */
void func_1511E4F4(u8 *obj) {
    Pickup1511E4F4 *s;
    struct127 *p;
    s32 off = 0;
    s32 item = -1;
    f32 dx, dz, size, r, y;
    s16 h, t1, t2;
    u8 *o;

    s = *(Pickup1511E4F4 **) (obj + 0x7C);
    if (s == NULL) {
        s = (Pickup1511E4F4 *) allocate_memory(0x10, 1, 0, 0);
        *(Pickup1511E4F4 **) (obj + 0x7C) = s;
        bzero(s, 0x10);
        s->scale = PK_F32(obj, 0x2C);
        PK_F32(obj, 0x34) = 0.0f;
        PK_F32(obj, 0x30) = 0.0f;
        PK_F32(obj, 0x2C) = 0.0f;
    }
    switch (*(u16 *) (obj + 0x54)) {
    case 0x59:
    case 0x5A:
        break;
    case 0x54:
        item = 0x17;
        if (D_800BE9F0 == 0x2D) {
            o = func_1509B570(0xBA);
            if (o != NULL && *(s32 *) (o + 0x1FE4) <= 0) {
                off = 1;
            }
        }
        /* fallthrough */
    default:
        PK_F32(obj, 4) += (f32) D_800BE9E4 * 1.52f;
        PK_F32(obj, 0) = 8.0f * cosf((f32) s->phase0 * PK_ANG);
        PK_F32(obj, 0x18) = 12.0f * cosf((f32) s->phase1 * PK_ANG);
        s->phase0 = (u16) (u32) ((f32) s->phase0 + (f32) D_800BE9E4 * 507.0f);
        s->phase1 = (u16) (u32) ((f32) s->phase1 + (f32) D_800BE9E4 * 419.0f);
        break;
    }
    if ((s32) s->state < 3 && !off) {
        for (p = D_800CC2D0; p < &D_800CC2D0[D_8008FD8C]; p++) {
            if (*(s32 *) p == 0 || PK_U8(p, 0x1CA) == 0 || PK_U8(p, 0x127) == 0xFF || PK_U8(p, 0x300) == 0) {
                continue;
            }
            if (*(s32 *) (obj + 0x84) == 1 && PK_U8(p, 0x128) != 0) {
                continue;
            }
            if (*(s32 *) (obj + 0x84) == 2 && PK_U8(p, 0x128) == 0) {
                continue;
            }
            if (*(s32 *) (obj + 0x84) == 3 && (PK_U8(p, 0x128) & 1)) {
                continue;
            }
            if (item != -1 && func_15031C4C(p, item, 0) != 0) {
                continue;
            }
            dx = (f32) PK_S16(obj, 0x10) - p->x_position;
            dz = (f32) PK_S16(obj, 0x14) - p->z_position;
            size = (f32) PK_U8(p->unk31C, 0x1AF) * 0.015625f;
            if (PK_U8(p->unk31C, 0x84) != 0) {
                size *= 1.4f;
            }
            r = 100.0f * size;
            if (dx * dx + dz * dz < r * r) {
                func_1507C7C0(p, &h, &t1, &t2);
                y = (f32) PK_S16(obj, 0x12);
                if (y < PK_F32(p, 0x17C) && PK_F32(p, 0x18) < y + r && y - r < PK_F32(p, 0x18) + (f32) h) {
                    *(s32 *) (obj + 0x80) = PK_U8(p, 0x3B);
                    s->state = 3;
                    func_1511E320(obj, p);
                    func_151D6F20((s32) p, (s32) obj);
                    break;
                }
            }
        }
    }
    if (s->state == 0) {
        PK_F32(obj, 0x34) += 0.26f * s->scale;
        if (s->scale <= PK_F32(obj, 0x34)) {
            PK_F32(obj, 0x34) = s->scale;
            s->wob = 0;
            s->state++;
            s->amp = 0.3f;
        }
        PK_F32(obj, 0x30) = PK_F32(obj, 0x34);
        PK_F32(obj, 0x2C) = PK_F32(obj, 0x34);
    } else if (s->state == 1) {
        s->amp -= 0.02f * s->scale;
        if (s->amp <= 0.0f) {
            s->state++;
            s->amp = 0.0f;
        }
        PK_F32(obj, 0x34) = cosf((f32) s->wob * PK_ANG) * s->amp + s->scale;
        PK_F32(obj, 0x30) = PK_F32(obj, 0x34);
        PK_F32(obj, 0x2C) = PK_F32(obj, 0x34);
        s->wob += D_800BE9E4 * 0x1613;
    } else if (s->state == 3) {
        PK_F32(obj, 0x34) -= 0.26f * s->scale;
        if (PK_F32(obj, 0x34) <= 0.0f) {
            s->state = 0;
            PK_U8(obj, 0x6E) = 1;
            PK_F32(obj, 0x34) = 0.0f;
        }
        PK_F32(obj, 0x30) = PK_F32(obj, 0x34);
        PK_F32(obj, 0x2C) = PK_F32(obj, 0x34);
    }
}
#undef PK_U8
#undef PK_F32
#undef PK_S16
#undef PK_ANG
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_1511E4F4.s")
#endif

#ifdef NON_MATCHING
// mover_slide_step: world mesh record (D_800DBEF4, 0xA0 bytes) handler at D_8008936C for sliding / bobbing scenery.
// +0x80 is the command (1 = open, 0 = close, anything else keeps going with a 90x step); starting an open / close from
// the other end plays the D_80089600 row (+0x3C low half) move / start sound. +0x3C high half picks the motion; +0x84
// latches the rest position on the first call (+0x7C, set to 1 at the end) and +0x73 bits 0..1 hold the state
// (0 closed, 1 closing, 2 opening, 3 open). Types 0 / 3: move y +0x8 / x +0x4 down to -110 / 260; 2, 8: x up by at most
// 70 (80 for type 2); 4, 6, 7: x down by at most 70 (80 / 82, type 6 at half speed); 10, 11: y bobs as sin(phase) * 10
// with a splash sound when the phase wraps after 4 pi; 12, 13: y = 180 - sin(phase) * 10 (10 / 12 add a fixed step first).
void func_1511ED08(u8 *rec) {
    f32 *x = (f32 *) (rec + 4);
    f32 *y = (f32 *) (rec + 8);
    f32 *rest = (f32 *) (rec + 0x84);
    s32 cmd = *(s32 *) (rec + 0x80);
    s32 state = rec[0x73] & 3;
    s32 sfx = -1;
    s32 type;
    s16 sound;
    f32 dir;
    f32 dt;
    f32 range;
    f32 speed;
    f32 lim;

    if (cmd == 1) {
        if (state == 0 || state == 1) {
            state = 2;
            sfx = 0;
        }
        dir = 1.0f;
    } else if (cmd == 0) {
        if (state == 3 || state == 2) {
            state = 1;
            sfx = 1;
        }
        dir = -1.0f;
    } else {
        dir = 90.0f;
    }
    if (sfx != -1) {
        sound = ((s16 *) &D_80089600[*(s32 *) (rec + 0x3C) & 0xFFFF])[sfx];
        if (sound > 0) {
            func_151152A4(rec, sound, 0x5DC0, 0xC8, 0x9C4, 0);
        }
    }
    dt = D_800BE9E4;
    type = *(s32 *) (rec + 0x3C) >> 16;
    range = 70.0f;
    speed = 6.0f;
    dir *= dt;
    if (type == 2 || type == 4) {
        range = 80.0f;
    } else if (type == 6) {
        speed = 3.0f;
        range = 82.0f;
    }
    switch (type) {
        case 0:
            if (*(s32 *) (rec + 0x7C) == 0) {
                *rest = *y;
            }
            *y -= dir * speed;
            if (*y > *rest) {
                *y = *rest;
                state = 0;
            }
            if (*y < -110.0f) {
                *y = -110.0f;
                state = 3;
            }
            break;
        case 3:
            if (*(s32 *) (rec + 0x7C) == 0) {
                *rest = *x;
            }
            *x -= dir * 3.0f;
            if (*x < 260.0f) {
                *x = 260.0f;
                state = 3;
            }
            if (*x > *rest) {
                *x = *rest;
                state = 0;
            }
            break;
        case 2:
        case 8:
            if (*(s32 *) (rec + 0x7C) == 0) {
                *rest = *x;
            }
            *x += dir * speed;
            lim = *rest + range;
            if (*x > lim) {
                *x = lim;
                state = 3;
            }
            if (*x < *rest) {
                *x = *rest;
                state = 0;
            }
            break;
        case 4:
        case 6:
        case 7:
            if (*(s32 *) (rec + 0x7C) == 0) {
                *rest = *x;
            }
            *x -= dir * speed;
            lim = *rest - range;
            if (*x > *rest) {
                *x = *rest;
                state = 0;
            }
            if (*x < lim) {
                *x = lim;
                state = 3;
            }
            break;
        case 10:
            *rest += 0.01f;
            dt = D_800BE9E4;
            /* fallthrough */
        case 11:
            *rest += 0.04f * dt;
            *y = sinf(*rest) * 10.0f;
            if (*rest > 12.566371f) {
                *rest -= 12.566371f * ((func_150ADA20() & 4) + 1);
                func_151152A4(rec, 0x503, 0x1F40, 0x96, 0x258, 0);
            }
            break;
        case 12:
            *rest += 0.01f;
            dt = D_800BE9E4;
            /* fallthrough */
        case 13:
            *rest += 0.04f * dt;
            *y = 180.0 - sinf(*rest) * 10.0f;
            break;
    }
    *(s32 *) (rec + 0x7C) = 1;
    rec[0x73] = (rec[0x73] & ~3) | state;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_142E40/func_1511ED08.s")
#endif

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