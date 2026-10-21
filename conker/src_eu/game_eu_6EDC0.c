#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#ifdef NON_MATCHING // hoisted declarations of the NON_MATCHING bodies
Gfx *func_150417F8(Gfx *gdl, s32 x, s32 y, s32 idx);
s32 func_15041770(u8 arg0);
s32 func_15042F30(s32 arg0);
#endif


#ifdef NON_MATCHING
extern s32 D_80084CC0;

u8 *func_150415B0(u8 *arg0) {
    u8 *temp_a0;
    u8 *temp_a0_10;
    u8 *temp_a0_11;
    u8 *temp_a0_2;
    u8 *temp_a0_3;
    u8 *temp_a0_4;
    u8 *temp_a0_5;
    u8 *temp_a0_6;
    u8 *temp_a0_7;
    u8 *temp_a0_8;
    u8 *temp_a0_9;

    (*(s32 *)((u8 *)arg0 + 4)) = -1;
    (*(s32 *)((u8 *)arg0 + 0)) = 0xD7000002;
    temp_a0_2 = arg0 + 8;
    (*(s32 *)((u8 *)temp_a0_2 + 0)) = 0xE7000000;
    (*(s32 *)((u8 *)temp_a0_2 + 4)) = 0;
    temp_a0_3 = temp_a0_2 + 8;
    (*(s32 *)((u8 *)temp_a0_3 + 0)) = 0xFCFFFFFF;
    (*(s32 *)((u8 *)temp_a0_3 + 4)) = 0xFFFCF279;
    temp_a0_4 = temp_a0_3 + 8;
    (*(s32 *)((u8 *)temp_a0_4 + 0)) = 0xEF002C0F;
    (*(s32 *)((u8 *)temp_a0_4 + 4)) = 0x55204C;
    temp_a0_5 = temp_a0_4 + 8;
    (*(s32 *)((u8 *)temp_a0_5 + 0)) = 0xFD90003F;
    (*(s32 **)((u8 *)temp_a0_5 + 4)) = &D_80084CC0;
    temp_a0_6 = temp_a0_5 + 8;
    (*(s32 *)((u8 *)temp_a0_6 + 0)) = 0xFD900000;
    (*(s32 **)((u8 *)temp_a0_6 + 4)) = &D_80084CC0;
    temp_a0_7 = temp_a0_6 + 8;
    (*(s32 *)((u8 *)temp_a0_7 + 4)) = 0x07000000;
    (*(s32 *)((u8 *)temp_a0_7 + 0)) = 0xF5900000;
    temp_a0_8 = temp_a0_7 + 8;
    (*(s32 *)((u8 *)temp_a0_8 + 0)) = 0xE6000000;
    (*(s32 *)((u8 *)temp_a0_8 + 4)) = 0;
    temp_a0_9 = temp_a0_8 + 8;
    (*(s32 *)((u8 *)temp_a0_9 + 0)) = 0xF3000000;
    (*(s32 *)((u8 *)temp_a0_9 + 4)) = 0x077FF200;
    temp_a0_10 = temp_a0_9 + 8;
    (*(s32 *)((u8 *)temp_a0_10 + 0)) = 0xE7000000;
    (*(s32 *)((u8 *)temp_a0_10 + 4)) = 0;
    temp_a0_11 = temp_a0_10 + 8;
    (*(s32 *)((u8 *)temp_a0_11 + 0)) = 0xF5800800;
    (*(s32 *)((u8 *)temp_a0_11 + 4)) = 0;
    temp_a0 = temp_a0_11 + 8;
    (*(s32 *)((u8 *)temp_a0 + 0)) = 0xF2000000;
    (*(s32 *)((u8 *)temp_a0 + 4)) = 0xFC1FC;
    return temp_a0 + 8;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6EDC0/func_150415B0.s")
#endif
#ifdef NON_MATCHING
Gfx *func_150416EC(Gfx *arg0, s32 arg1, s32 arg2, u8 *arg3) {
    Gfx *temp_v0;
    Gfx *var_s2;
    s32 var_s1;
    u8 *var_s0;
    u8 temp_t6;
    u8 var_a0;

    var_s2 = arg0;
    temp_t6 = *arg3;
    var_s0 = arg3;
    var_s1 = arg1;
    var_a0 = temp_t6 & 0xFF;
    if (temp_t6 != 0) {
        do {
            temp_v0 = func_150417F8(var_s2, var_s1, arg2, func_15041770(var_a0));
            var_a0 = (*(u8 *)((u8 *)var_s0 + 1));
            var_s2 = temp_v0;
            var_s0 += 1;
            var_s1 += 8;
        } while (var_a0 != 0);
    }
    return var_s2;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6EDC0/func_150416EC.s")
#endif
extern u8 D_80084C60[];
s32 func_15041770(u8 arg0) {
    s32 i;
    for (i = 0; i < 0x50; i++) {
        if (arg0 == D_80084C60[i]) {
            return i;
        }
    }
    return i;
}

Gfx *func_150417F8(Gfx *gdl, s32 x, s32 y, s32 idx) {
    s32 col = idx % 8; // fakematch: locals keep the unfolded mod/sub/div
    s32 s = col * 8;
    s32 row = (idx - col) / 8;

    gSPTextureRectangle(gdl++, x << 2, y << 2, (x + 8) << 2, (y + 12) << 2, 0, s * 32, (row * 3) << 7, 0x400, 0x400);
    return gdl;
}

void func_150418D0(s32 arg0, s32 *arg1, s32 *arg2, f32 *arg3, s32 *arg4, f32 *arg5) {
    if ((arg0 >= 0xA8) && (arg0 < 0x100)) {
        *arg5 = 1.0f;
        switch (arg0) {
        case 0xA8:
        case 0xA9:
            *arg1 = 0x20;
            *arg2 = 0x12;
            *arg3 = 3.1f;
            *arg4 = 1;
            return;
        case 0xAA:
        case 0xAB:
        case 0xAC:
        case 0xAD:
            *arg1 = 0x20;
            *arg2 = 0x1B;
            *arg3 = 2.0f;
            *arg4 = 1;
            *arg5 = 0.603f;
            return;
        case 0xAE:
            *arg1 = 0x10;
            *arg2 = 0x11;
            *arg3 = -1.6f;
            *arg4 = 1;
            return;
        case 0xAF:
        case 0xB0:
            *arg1 = 0x2E;
            *arg2 = 0x10;
            *arg3 = 2.0f;
            *arg4 = 1;
            return;
        case 0xB6:
        case 0xB7:
        case 0xB8:
        case 0xB9:
            *arg1 = 0x10;
            *arg2 = 0xC;
            *arg3 = 2.0f;
            *arg4 = 0;
            return;
        case 0xBA:
            *arg4 = 0;
            *arg3 = 0.2f;
            *arg1 = 0x37;
            *arg2 = 0xC;
            return;
        case 0xB1:
            *arg1 = 0x26;
            *arg2 = 0x18;
            *arg3 = 2.0f;
            *arg4 = 1;
            *arg5 = 0.726f;
            return;
        default:
            *arg1 = 0xC;
            *arg2 = 0x10;
            *arg3 = 2.0f;
            *arg4 = 0;
            return;
        }
    } else {
        *arg3 = 0.0f;
        *arg1 = 0;
        *arg2 = 0;
    }
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6EDC0/func_15041A9C.s")

#ifdef NON_MATCHING
extern f32 D_80038400;
extern f32 D_80038404;
extern s32 D_80085D24;

void func_15042BC4(u8 *arg0, s32 *arg1, s32 *arg2, s32 *arg3) {
    struct {
        f32 u54;
        s32 u58;
        f32 u5C;
        s32 u60;
        s32 u64;
        s32 u68;
    } sp;
    s32 temp_a0;
    s32 temp_s3;
    s32 temp_v0;
    s32 temp_v0_2;
    s32 temp_v0_3;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 var_s0;
    s32 var_s5;
    s32 var_t0;
    u8 *var_s2;
    u8 var_a0;
    u8 var_v0;
    u8 *temp_v0_4;
    u8 *temp_v0_5;

    if (arg0 != NULL) {
        *arg1 = 0;
        *arg2 = 0;
        *arg3 = 0;
        var_s5 = 0;
        var_s0 = 0;
        if (*arg0 == 0) {
            *arg2 += 0xC;
        }
        var_s2 = arg0;
        if (*arg0 != 0) {
            var_a0 = *var_s2;
            var_v0 = var_a0;
            do {
                if (var_v0 == 0xBC) {
                    var_s2 += 2;
                } else {
                    temp_v0 = func_15042F30(var_a0);
                    temp_v1 = temp_v0 & 0xFF;
                    temp_s3 = temp_v0 & 0xFF;
                    var_t0 = 0;
                    if (temp_v1 == 0x60) {
                        *arg1 += 4;
                        if (var_s0 < 0xC) {
                            var_s0 = 0xC;
                        }
                    } else if ((temp_v1 < 0xA1) || (temp_v1 >= 0xA8)) {
                        if ((temp_v1 >= 0xA8) && (temp_v1 < 0x100)) {
                            sp.u68 = 0;
                            func_150418D0(temp_s3, &sp.u64, &sp.u60, &sp.u5C, &sp.u58, &sp.u54);
                            var_t0 = sp.u68;
                            *arg1 = (s32) ((f32) *arg1 + ((f32) sp.u64 * sp.u54));
                            temp_v0_2 = (s32) ((f32) (s32) ((f32) sp.u60 * sp.u54) - sp.u5C) + 1;
                            if (var_s0 < temp_v0_2) {
                                var_s0 = temp_v0_2;
                            }
                            if ((f32) *arg3 < sp.u5C) {
                                *arg3 = (s32) sp.u5C;
                            }
                        } else if (temp_v1 < 0xA1) {
                            if (*var_s2 == 0xA) {
                                temp_v0_3 = *arg1;
                                if (var_s5 < temp_v0_3) {
                                    var_s5 = temp_v0_3;
                                }
                                *arg1 = 0;
                                if (var_s0 < 0xC) {
                                    var_s0 = 0xC;
                                }
                                *arg2 += var_s0;
                                var_s0 = 0;
                            } else {
                                var_t0 = 1;
                            }
                        }
                    }
                    var_s2 += 1;
                    if (var_t0 != 0) {
                        temp_v1_2 = temp_s3 * 4;
                        temp_v0_4 = D_80085D24 + temp_v1_2;
                        *arg1 = (*arg1 + (*(u8 *)((u8 *)temp_v0_4 + 0)) + (*(u8 *)((u8 *)temp_v0_4 + 2))) - 1;
                        temp_v0_5 = D_80085D24 + temp_v1_2;
                        temp_a0 = (*(u8 *)((u8 *)temp_v0_5 + 3)) + (*(u8 *)((u8 *)temp_v0_5 + 1));
                        if (temp_a0 >= var_s0) {
                            var_s0 = temp_a0;
                        }
                    }
                }
                var_a0 = *var_s2;
                var_v0 = var_a0;
            } while (var_a0 != 0);
        }
        if (*arg1 < var_s5) {
            *arg1 = var_s5;
        }
        *arg2 += var_s0;
        *arg1 = (s32) ((f32) *arg1 * D_80038400);
        *arg2 = (s32) ((f32) *arg2 * D_80038404);
        *arg3 = (s32) ((f32) *arg3 * D_80038400);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6EDC0/func_15042BC4.s")
#endif
#ifdef NON_MATCHING
extern u8 D_80085CC0;
extern u8 D_80085CC1;
extern u8 D_80085CC2;
extern s32 D_80085CC3;

s32 func_15042F30(s32 arg0) {
    s32 *var_v0_2;
    s32 temp_t6;
    s32 var_a0;
    s32 var_v0;

    temp_t6 = arg0 & 0xFF;
    if ((temp_t6 >= 0x61) && (temp_t6 < 0x7B)) {
        var_v0 = (temp_t6 - 0x20) & 0xFF;
    } else {
        var_v0 = temp_t6 & 0xFF;
    }
    if (temp_t6 == 0x20) {
        return 0x60;
    }
    if (var_v0 == D_80085CC0) {
        return 0;
    }
    if (var_v0 == D_80085CC1) {
        return 1;
    }
    var_v0_2 = &D_80085CC3;
    var_a0 = 3;
    if (var_v0 == D_80085CC2) {
        return 2;
    }
loop_13:
    if (var_v0 == (*(u8 *)((u8 *)var_v0_2 + 0))) {
        return var_a0;
    }
    if (var_v0 == (*(u8 *)((u8 *)var_v0_2 + 1))) {
        return var_a0 + 1;
    }
    if (var_v0 == (*(u8 *)((u8 *)var_v0_2 + 2))) {
        return var_a0 + 2;
    }
    if (var_v0 == (*(u8 *)((u8 *)var_v0_2 + 3))) {
        return var_a0 + 3;
    }
    var_a0 += 4;
    var_v0_2 = (s32 *)((u8 *)var_v0_2 + (4));
    if (var_a0 == 0x5F) {
        return temp_t6;
    }
    goto loop_13;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_6EDC0/func_15042F30.s")
#endif