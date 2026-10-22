#include <ultra64.h>
#include "functions.h"
#include "variables.h"

s32 func_15115244();


#ifdef NON_MATCHING
Gfx *func_15110AC4(Gfx *gdl, s32 arg1, s32 arg2, s32 arg3, s32 arg4, u8 r, u8 g, u8 b);
u8 *func_15110C28(u8 *);
s32 func_15110E44(f32 arg0, f32 arg1, f32 arg2, f32 arg3);
extern u8 D_800D9F89, D_800D9F8A, D_800D9F8B, D_800D9F8C, D_800D9F8D, D_800D9F8E, D_800D9F8F, D_800D9F90;
extern u8 D_800D9F91, D_800D9F92, D_800D9F93, D_800D9F99, D_800D9F9A, D_800D9F9B, D_800D9F9C, D_800D9F9D;
extern u8 D_800D9F9E, D_800D9F9F, D_800D9FA0, D_800D9FA1, D_800D9FA2, D_800D9FA3;
extern u8 D_800BEA55;
extern s32 D_800BE624;
extern s16 D_80083336;
/* camera/overlay draw callbacks, indexed by D_800B0DF0->unk8 */
extern Gfx *(*D_80089578[])(Gfx *, f32, f32, f32, f32, f32, f32, s32);

Gfx *func_15110420(Gfx *gdl, s32 arg1) {
    u8 *view;
    struct108 *player;
    f32 yaw;
    f32 pitch;
    f32 roll;
    f32 x;
    f32 y;
    f32 z;
    s32 handle;

    D_800D9F88[0] = 0;
    D_800D9F89 = 0;
    D_800D9F8A = 0;
    D_800D9F98[0] = 0;
    D_800D9F99 = 0;
    D_800D9F9A = 0;
    D_800D9F8B = 0;
    D_800D9F8C = 0;
    D_800D9F8D = 0;
    D_800D9F9B = 0;
    D_800D9F9C = 0;
    D_800D9F9D = 0;
    D_800D9F8E = 0;
    D_800D9F8F = 0;
    D_800D9F90 = 0;
    D_800D9F9E = 0;
    D_800D9F9F = 0;
    D_800D9FA0 = 0;
    D_800D9F91 = 0;
    D_800D9F92 = 0;
    D_800D9F93 = 0;
    D_800D9FA1 = 0;
    D_800D9FA2 = 0;
    D_800D9FA3 = 0;

    gdl->words.w0 = 0xD9FFF9FF;
    gdl->words.w1 = 0;
    gdl = (Gfx *)func_15110C28((u8 *)(gdl + 1));
    gDPPipeSync(gdl++);
    if (D_800BEA55 != 0) {
        gdl = func_15110AC4(gdl, 0, 0, D_800BE620, D_800BE624, 0, 0, 0);
    }
    if ((D_800C35EA == 1) && (D_800C3681 != 0)) {
        return gdl;
    }

    view = D_800DD210 + D_80082FA4 * 0x18;
    player = &D_800DBFF0[D_80082FA4];
    /* wrap the three angles (degrees): yaw and roll into [-180, 180), pitch into [0, 360) */
    yaw = 360.0f - (*(f32 *)(view + 0xC) + player->unk388);
    while (yaw < -180.0f) {
        yaw += 360.0f;
    }
    while (yaw >= 180.0f) {
        yaw -= 360.0f;
    }
    pitch = 360.0f - (*(f32 *)(view + 0x10) + player->unk380);
    while (pitch < 0.0f) {
        pitch += 360.0f;
    }
    while (pitch >= 360.0f) {
        pitch -= 360.0f;
    }
    roll = *(f32 *)(view + 0x14) + *(f32 *)&player->pad5EC;
    while (roll < -180.0f) {
        roll += 360.0f;
    }
    while (roll >= 180.0f) {
        roll -= 360.0f;
    }
    x = player->unk2F8;
    y = player->unk2FC;
    z = player->unk300;

    if (D_800C3682 != 0) {
        u8 *cam = (u8 *)D_800BE628 + D_80082FA4 * 0x180;
        return func_15110AC4(gdl, (s32)*(f32 *)(cam + 0x2C), (s32)*(f32 *)(cam + 0x24),
                             (s32)(*(f32 *)(cam + 0x30) - 1.0f), (s32)*(f32 *)(cam + 0x28), 0x16, 0x1C, 0x1B);
    }

    handle = func_15110E44(x, y, z, yaw);
    if (handle != 0) {
        gdl = D_80089578[D_800B0DF0->unk8](gdl, x, y, z, yaw, pitch, roll, handle);
    }
    gdl = (Gfx *)func_1501A490((s32)gdl, D_80083336, 0, 0, 0, 0);
    gdl->words.w1 = 0x400;
    gdl->words.w0 = 0xD9FFFFFF;
    return gdl + 1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/func_15110420.s")
#endif
void func_150A7A48(f32 (*)[4], f32 (*)[4], f32 (*)[4]);
void func_1511084C(f32 (*arg0)[4], f32 arg1, f32 arg2, f32 arg3) {
    f32 sp28[4][4];
    func_150A8050(arg0, 0.0f, arg2, 0.0f);
    func_150A8050(sp28, arg1, 0.0f, 0.0f);
    func_150A7A48(arg0, sp28, arg0);
    func_150A8050(sp28, 0.0f, 0.0f, arg3);
    func_150A7A48(arg0, sp28, arg0);
}

void func_150A7A48(f32 (*)[4], f32 (*)[4], f32 (*)[4]);
void func_1511084C(f32 (*)[4], f32, f32, f32);
void func_151108E0(s32 arg0, f32 (*arg1)[4], f32 arg2, f32 arg3, f32 arg4) {
    func_1511084C(arg1, arg2, arg3, arg4);
    func_150A7A48(arg1, (f32 (*)[4])((u8 *)D_800BE628 + arg0 * 0x180 + 0xBC), arg1);
}

#ifdef NON_MATCHING
Gfx *func_1501A6CC(Gfx *gdl, s32 ulx, s32 uly, s32 lrx, s32 lry);
extern u8 D_800DC2D8[];

/* Default camera callback (D_80089578[0], called by func_15110420): clear the current player's viewport
 * (D_800BE628[D_80082FA4] +0x24..0x30) to the level colour D_800DC2D8 via func_15110AC4; in split screen, from
 * player 0 only, draw the black divider bars (horizontal across the middle; vertical too with 3-4 players). The
 * position / angle arguments are unused. */
Gfx *func_15110948(Gfx *gdl, f32 x, f32 y, f32 z, f32 yaw, f32 pitch, f32 roll, s32 handle) {
    u8 *cam = (u8 *)D_800BE628 + D_80082FA4 * 0x180;
    s32 h;

    gdl = func_15110AC4(gdl, (s32)*(f32 *)(cam + 0x2C), (s32)*(f32 *)(cam + 0x24), (s32)(*(f32 *)(cam + 0x30) - 1.0f),
                        (s32)*(f32 *)(cam + 0x28), D_800DC2D8[0], D_800DC2D8[1], D_800DC2D8[2]);
    if (D_80082FA0 == 0 || D_80082FA4 != 0) {
        return gdl;
    }
    gdl->words.w0 = 0xE7000000;
    gdl->words.w1 = 0;
    gdl = (Gfx *)func_1501A490((s32)(gdl + 1), 0xFF, 0, 0, 0, 0);
    gdl->words.w0 = 0xF7000000;
    gdl->words.w1 = 0x10001;
    h = D_800BE624 >> 1;
    gdl = func_1501A6CC(gdl + 1, 0, h - 6, D_800BE620, h + 6);
    if (D_80082FA0 != 1) {
        h = D_800BE620 >> 1;
        gdl = func_1501A6CC(gdl, h - 1, 0, h + 1, D_800BE624);
    }
    return gdl;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/func_15110948.s")
#endif
Gfx *func_15110AC4(Gfx *gdl, s32 arg1, s32 arg2, s32 arg3, s32 arg4, u8 r, u8 g, u8 b) {
    gDPPipeSync(gdl++);
    gDPSetOtherMode(gdl++, 0x302C0F, 4);
    gdl = func_1501A680(gdl);
    gDPSetFillColor(gdl++, (GPACK_RGBA5551(r, g, b, 1) << 16) | GPACK_RGBA5551(r, g, b, 1));
    return func_1501A6CC(gdl, arg1, arg2, arg3, arg4);
}

extern u8 D_800DC2D8[];
Gfx *func_15110B80(Gfx *arg0, s32 arg1, s32 arg2, s32 arg3) {
    if ((D_800BE9F0 == 0x1B) || (D_800BE9F0 == 0x1E) || ((D_800BE9F0 == 0x31) && (*(u8 *)((u8 *)D_800DBFF0->unk3D4 + 0x78) == 3))) {
        arg0 = func_15110AC4(arg0, 2, 0, D_800BE620 - 2, D_800BE624, D_800DC2D8[0], D_800DC2D8[1], D_800DC2D8[2]);
    }
    return arg0;
}

#ifdef NON_MATCHING
extern u8 D_800BEEE2;

u8 *func_15110C28(u8 *arg0) {
    s32 temp_t5;
    s32 temp_t7;
    u8 *temp_a0;
    u8 *temp_a0_2;
    u8 *temp_a0_3;
    u8 *temp_a0_4;
    u8 *temp_v0;
    u8 *temp_v0_2;
    u8 *temp_v0_3;
    u8 *var_a0;

    var_a0 = arg0;
    if (D_80082FA4 == 0) {
        temp_a0 = var_a0 + 8;
        (*(s32 *)((u8 *)var_a0 + 0)) = 0xE7000000;
        (*(s32 *)((u8 *)var_a0 + 4)) = 0;
        (*(s32 *)((u8 *)temp_a0 + 4)) = 4;
        (*(s32 *)((u8 *)temp_a0 + 0)) = 0xEF302C0F;
        temp_a0_2 = temp_a0 + 8;
        (*(s32 *)((u8 *)temp_a0_2 + 0)) = 0xFCFFFFFF;
        (*(s32 *)((u8 *)temp_a0_2 + 4)) = 0xFFFE793C;
        temp_a0_3 = temp_a0_2 + 8;
        (*(s32 *)((u8 *)temp_a0_3 + 0)) = (s32) (((D_800BE620 - 1) & 0xFFF) | 0xFF100000);
        temp_a0_4 = temp_a0_3 + 8;
        (*(s32 *)((u8 *)temp_a0_3 + 4)) = (s32) D_800BEDE4;
        (*(s32 *)((u8 *)temp_a0_4 + 0)) = 0xF7000000;
        (*(s32 *)((u8 *)temp_a0_4 + 4)) = 0xFFFCFFFC;
        temp_v0 = func_1501A490((s32) (temp_a0_4 + 8), 0xFF, 0, 0, 0, 0);
        (*(s32 *)((u8 *)temp_v0 + 4)) = 0x8000;
        (*(s32 *)((u8 *)temp_v0 + 0)) = (s32) ((((D_800BE620 - 2) & 0x3FF) << 0xE) | 0xF6000000 | ((D_800BE624 & 0x3FF) * 4));
        (*(s32 *)((u8 *)temp_v0 + 8)) = 0xE7000000;
        (*(s32 *)((u8 *)temp_v0 + 0xC)) = 0;
        temp_v0_2 = func_1501A680(temp_v0 + 0x10);
        var_a0 = temp_v0_2;
        if (D_80082FA0 != 0) {
            (*(s32 *)((u8 *)temp_v0_2 + 0)) = 0xE7000000;
            (*(s32 *)((u8 *)temp_v0_2 + 4)) = 0;
            temp_v0_3 = func_1501A490((s32) (var_a0 + 8), 0xFF, 0, 0, 0, 0);
            (*(s32 *)((u8 *)temp_v0_3 + 0)) = 0xF7000000;
            (*(s32 *)((u8 *)temp_v0_3 + 4)) = 0x10001;
            temp_t5 = (s32) D_800BE624 >> 1;
            var_a0 = func_1501A6CC(temp_v0_3 + 8, 0, temp_t5 - 6, D_800BE620, temp_t5 + 6);
            if (D_80082FA0 != 1) {
                temp_t7 = (s32) D_800BE620 >> 1;
                var_a0 = func_1501A6CC(var_a0, temp_t7 - 1, 0, temp_t7 + 1, D_800BE624);
            }
            if (D_800BEEE2 != 0) {
                var_a0 = func_1501A6CC(var_a0, 0, 0, D_800BE620, D_800BE624);
            }
        }
    }
    return var_a0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/func_15110C28.s")
#endif
#ifdef NON_MATCHING
s32 func_15110E44(f32 arg0, f32 arg1, f32 arg2, f32 arg3) {
    struct {
        s32 u1C;
    } sp;
    s32 sp18;
    s32 var_a2;
    s32 var_v1;

    switch (D_800BE9F0) {
    case 0x6:
    case 0x3B:
        var_v1 = (s32) (((arg1 * 40.0f) / 1800.0f) + 200.0f);
        break;
    case 0x14:
        var_v1 = (s32) (((arg1 * 22.0f) / 1800.0f) + 113.0f);
        break;
    case 0xC:
        var_v1 = (s32) (((arg1 * 90.0f) / 1800.0f) + 150.0f);
        break;
    case 0x0:
        if ((arg1 < 1600.0f) && (arg3 > 26.0f)) {
            var_v1 = 0;
        } else {
            var_v1 = (s32) (((arg1 * 51.0f) / 1800.0f) + 134.0f);
        }
        break;
    case 0x7:
        if (arg2 < -1100.0f) {
        default:
block_46:
            var_v1 = 0x140;
        } else if (arg3 > 20.0f) {
            var_v1 = 0;
        } else {
            var_v1 = (s32) (((arg1 * 54.0f) / 1800.0f) + 167.0f);
        }
        break;
    case 0x41:
        var_v1 = 0x89;
        break;
    case 0x3C:
        if ((arg2 < -1650.0f) || ((arg0 > 3495.0f) && (arg0 < 4578.0f) && (arg2 < 2960.0f))) {
            goto block_46;
        }
        var_v1 = 0;
        break;
    case 0xB:
        sp18 = 0;
        if (func_150A29C8(0, 0x18) == 1) {
            var_a2 = sp18;
            if (func_150A29C8(0, 0x2E) == 0) {
                var_v1 = sp.u1C;
                if (arg3 > 0.0f) {
                    var_v1 = 0;
                } else {
                    var_a2 = 1;
                }
            } else {
                var_v1 = 0;
            }
        } else {
            var_a2 = 1;
            var_v1 = sp.u1C;
        }
        if (var_a2 != 0) {
            if (arg1 < 1218.0f) {
                var_v1 = 0x1E;
            } else {
                var_v1 = 0x140;
                if (arg1 < 2000.0f) {
                    var_v1 = 0xA0;
                }
            }
        }
        break;
    case 0x13:
        if ((D_800C35EA == 1) && ((D_800C3A08 == 2) || (D_800C3A08 == 1))) {
            goto block_46;
        }
        if (arg1 < 1900.0f) {
            var_v1 = 0x10E;
        } else {
            goto block_46;
        }
        break;
    case 0x1C:
        var_v1 = (s32) (((arg1 * 34.0f) / 1800.0f) + 130.0f);
        break;
    case 0xE:
        var_v1 = 0xA5;
        break;
    case 0x39:
        var_v1 = 0x54;
        break;
    case 0x2D:
        var_v1 = (s32) (((arg1 * 53.0f) / 1800.0f) + 139.0f);
        break;
    case 0x30:
        var_v1 = (s32) (((arg1 * 53.0f) / 1800.0f) + 139.0f);
        break;
    }
    return var_v1;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/func_15110E44.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/func_1511127C.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/func_15111CAC.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/func_15111DD8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/func_15112074.s")

#ifdef NON_MATCHING
extern s16 D_800895D4;
extern f32 D_800DC2F0;

void func_15112AA0(u8 *arg0) {
    f32 sp58;
    f32 sp4C;
    f32 sp40;
    u8 *sp3C;
    f32 sp30;
    f32 sp2C;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f0_4;
    f32 temp_f0_5;
    f32 temp_f0_6;
    f32 temp_f0_7;
    f32 temp_f0_8;
    f32 temp_f12;
    f32 temp_f12_2;
    f32 temp_f12_3;
    f32 temp_f14;
    f32 temp_f14_2;
    f32 temp_f14_3;
    f32 temp_f16;
    f32 temp_f18;
    f32 temp_f20;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f6;
    f32 var_f12;
    f32 var_f16;
    f32 var_f16_2;
    f32 var_f16_3;
    f32 var_f20;
    f32 var_f20_2;
    f32 var_f2;
    f32 var_f2_2;
    f32 var_f2_3;
    s16 var_a1;
    u16 temp_v1;
    u8 *temp_t0;

    temp_t0 = (*(u8 **)((u8 *)arg0 + 0x3C));
    temp_f12 = D_800CC2D0->x_position - (f32) (*(s16 *)((u8 *)arg0 + 0x10));
    temp_f2 = temp_f12 * temp_f12;
    temp_f18 = (D_800CC2D0->y_position + 65.0f) - (f32) (*(s16 *)((u8 *)arg0 + 0x12));
    temp_f14 = D_800CC2D0->z_position - (f32) (*(s16 *)((u8 *)arg0 + 0x14));
    temp_f16 = temp_f14 * temp_f14;
    temp_f6 = temp_f2 + (temp_f18 * temp_f18) + temp_f16;
    D_800DC2F0 = temp_f6;
    temp_f0 = (*(f32 *)((u8 *)temp_t0 + 0x2C));
    if ((temp_f0 * temp_f0) < temp_f6) {
        var_f16 = (*(f32 *)((u8 *)temp_t0 + 0x28));
        var_f20 = (*(f32 *)((u8 *)temp_t0 + 0x24));
        if (var_f16 < 0.0f) {
            var_f16 += 360.0f;
        }
        sp40 = (*(f32 *)((u8 *)temp_t0 + 4));
    } else {
        sp3C = temp_t0;
        sp30 = temp_f2;
        sp2C = temp_f16;
        sp58 = temp_f18;
        temp_f20 = func_150484A0(temp_f12, temp_f14);
        var_f20_2 = temp_f20 * 57.295776f;
        temp_f2_2 = func_150484A0(sp58, sqrtf(temp_f2 + temp_f16)) * 57.295776f;
        var_f16_2 = temp_f2_2;
        if (temp_f2_2 < 0.0f) {
            var_f16_2 = temp_f2_2 + 360.0f;
        } else if (temp_f2_2 >= 360.0f) {
            var_f16_2 = temp_f2_2 - 360.0f;
        }
        if (var_f20_2 < 0.0f) {
            var_f20_2 += 360.0f;
        } else if (var_f20_2 >= 360.0f) {
            var_f20_2 -= 360.0f;
        }
        sp4C = var_f16_2;
        sp3C = temp_t0;
        temp_f0_2 = func_15048A70((*(f32 *)((u8 *)temp_t0 + 0x24)), var_f20_2);
        var_f16_3 = var_f16_2;
        if (var_f16_3 > 180.0f) {
            var_f16_3 -= 360.0f;
        }
        temp_f12_2 = (*(f32 *)((u8 *)temp_t0 + 0xC));
        temp_f14_2 = (*(f32 *)((u8 *)temp_t0 + 0x14));
        if (((temp_f12_2 + temp_f14_2) < temp_f0_2) || (var_f2 = (*(f32 *)((u8 *)temp_t0 + 0x10)), (temp_f0_2 < (var_f2 - temp_f14_2)))) {
            var_f20 = (*(f32 *)((u8 *)temp_t0 + 0x24));
            var_f16 = (*(f32 *)((u8 *)temp_t0 + 0x28));
            sp40 = (*(f32 *)((u8 *)temp_t0 + 4));
        } else {
            sp40 = (*(f32 *)((u8 *)temp_t0 + 0));
            if (temp_f0_2 < var_f2) {

            } else if (temp_f12_2 < temp_f0_2) {
                var_f2 = temp_f12_2;
            } else {
                var_f2 = temp_f0_2;
            }
            var_f20 = (*(f32 *)((u8 *)temp_t0 + 0x24)) + var_f2;
            if (var_f20 < 0.0f) {
                var_f20 += 360.0f;
            } else if (var_f20 >= 360.0f) {
                var_f20 -= 360.0f;
            }
            temp_f0_3 = (*(f32 *)((u8 *)temp_t0 + 0x18));
            temp_f12_3 = (*(f32 *)((u8 *)temp_t0 + 0x20));
            if (((temp_f0_3 + temp_f12_3) < var_f16_3) || (var_f2_2 = (*(f32 *)((u8 *)temp_t0 + 0x1C)), (var_f16_3 < (var_f2_2 - temp_f12_3)))) {
                var_f16 = 0.0f;
            } else {
                if (var_f16_3 < var_f2_2) {

                } else if (temp_f0_3 < var_f16_3) {
                    var_f2_2 = temp_f0_3;
                } else {
                    var_f2_2 = var_f16_3;
                }
                var_f16 = var_f2_2;
            }
        }
        if (var_f16 < 0.0f) {
            var_f16 += 360.0f;
        }
    }
    sp4C = var_f16;
    sp3C = temp_t0;
    temp_f0_4 = func_15048A70((*(f32 *)((u8 *)arg0 + 4)), var_f20);
    var_f12 = temp_f0_4;
    temp_f0_5 = fabsf(temp_f0_4);
    temp_f14_3 = (*(f32 *)((u8 *)temp_t0 + 8));
    if (temp_f14_3 < temp_f0_5) {
        if (var_f12 < 0.0f) {
            var_f2_3 = -1.0f;
        } else {
            var_f2_3 = 1.0f;
        }
        var_f12 = var_f2_3 * temp_f14_3;
    }
    (*(f32 *)((u8 *)arg0 + 4)) = (f32) ((*(f32 *)((u8 *)arg0 + 4)) + (var_f12 * sp40));
    if ((D_800895D4 == 0) && (temp_f0_5 > 4.0f)) {
        D_800895D4 = -1;
    }
    temp_f0_6 = (*(f32 *)((u8 *)arg0 + 4));
    if (temp_f0_6 < 0.0f) {
        (*(f32 *)((u8 *)arg0 + 4)) = (f32) (temp_f0_6 + 360.0f);
    } else if (temp_f0_6 >= 360.0f) {
        (*(f32 *)((u8 *)arg0 + 4)) = (f32) (temp_f0_6 - 360.0f);
    }
    sp3C = temp_t0;
    temp_f0_7 = func_15048A70((*(f32 *)((u8 *)arg0 + 0)), 360.0f - var_f16);
    var_a1 = D_800895D4;
    (*(f32 *)((u8 *)arg0 + 0)) = (f32) ((*(f32 *)((u8 *)arg0 + 0)) + (temp_f0_7 * sp40));
    if ((var_a1 == 0) && (fabsf(temp_f0_7) > 4.0f)) {
        var_a1 = -1;
    }
    temp_f0_8 = (*(f32 *)((u8 *)arg0 + 0));
    if (temp_f0_8 < 0.0f) {
        (*(f32 *)((u8 *)arg0 + 0)) = (f32) (temp_f0_8 + 360.0f);
    } else if (temp_f0_8 >= 360.0f) {
        (*(f32 *)((u8 *)arg0 + 0)) = (f32) (temp_f0_8 - 360.0f);
    }
    if ((var_a1 == -1) && (temp_v1 = (*(u16 *)((u8 *)temp_t0 + 0x32)), (temp_v1 != 0))) {
        D_800895D4 = (s16) temp_v1;
        if ((s32) (32000.0f - (D_800DC2F0 * 0.1f)) > 0) {
            func_10010F30((s32) (*(u16 *)((u8 *)temp_t0 + 0x30)), 0x7D00U, 0x40U, 0, 0U);
        }
    } else {
        D_800895D4 = var_a1;
        if (var_a1 > 0) {
            D_800895D4 = var_a1 - 1;
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/func_15112AA0.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/func_15113000.s")

#ifdef NON_MATCHING
void func_15113700(void) {
    s32 var_v0;
    s32 var_v1;
    u8 *temp_a0;
    u8 *temp_a0_2;
    u8 temp_a1;

    var_v0 = 0;
    var_v1 = 0;
    if (D_800DC320 > 0) {
        do {
            temp_a0 = &D_800DBEF4->pad[var_v1];
            (*(u8 *)((u8 *)temp_a0 + 0x6F)) = (u8) ((*(u8 *)((u8 *)temp_a0 + 0x6F)) & ~0x40);
            temp_a0_2 = &D_800DBEF4->pad[var_v1];
            temp_a1 = (*(u8 *)((u8 *)temp_a0_2 + 0x6F));
            if (((temp_a1 & 0xF) || (((*(u8 *)((u8 *)temp_a0_2 + 0x70)) & 4) == 4)) && ((*(s32 *)((u8 *)temp_a0_2 + 0x38)) != 0)) {
                (*(u8 *)((u8 *)temp_a0_2 + 0x6F)) = (u8) (temp_a1 | 0x40);
            }
            var_v0 += 1;
            var_v1 += 0xA0;
        } while (var_v0 < D_800DC320);
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/func_15113700.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/func_15113798.s")

#ifdef NON_MATCHING
s32 func_15173948(s32 arg0, s32 arg1);
u8 *func_1515EAB4(u8 *arg0, s32 arg1, u8 arg2, s32 arg3, s32 arg4);
s32 func_15113D54(s32, u8 *, s32, s16, s32, s32);
extern s32 D_800895E0[];
extern s32 D_800895F0[];
extern u8 D_800D9FF0[];
extern s32 D_800DA230[];
extern u8 D_800DA240;
extern u8 D_800DA241;
extern u16 D_800DC318[];

/* Draws the sky/world mesh list of player arg2: geometry-mode setup, the player's light block
 * (func_1515EAB4), then one func_15113D54 per entry of the player's u16-pair list
 * (entry index into the 0xA0-byte D_800DBEF4 records, extra value), then a fixed matrix pop
 * and the geometry-mode reset. arg1 != 0 passes flag 0x10 to every entry. */
Gfx *func_15113B44(Gfx *arg0, s32 arg1, s16 arg2) {
    s32 flags;
    s32 i;
    u8 *gdl;
    u16 *entry;
    u16 idx;

    if (arg1 == 0) {
        flags = 0;
    } else {
        flags = 0x10;
    }
    gdl = (u8 *) func_15173948((s32) arg0, 0);
    *(s32 *) (gdl + 0x0) = 0xD9A3FFFF;
    *(s32 *) (gdl + 0x4) = 0;
    *(s32 *) (gdl + 0xC) = 0x20000;
    *(s32 *) (gdl + 0x8) = 0xD9FFFFFF;
    gdl = func_1515EAB4(gdl + 0x10, D_800DA230[arg2], D_800DA240, D_800DA241,
                        (s32) (D_800D9FF0 + arg2 * 16 + D_800BE9C0 * 8));
    for (i = 0; i < D_800DC318[arg2]; i++) {
        entry = (u16 *) (*(u8 **) D_800895E0[arg2] + i * 4);
        idx = entry[0];
        gdl = (u8 *) func_15113D54((s32) gdl, (u8 *) D_800DBEF4 + idx * 0xA0,
                                   (idx << 6) + *(s32 *) D_800895F0[D_800BE9C0], arg2, entry[1], flags);
    }
    *(s32 *) (gdl + 0x0) = 0xDA380003;
    *(u8 **) (gdl + 0x4) = D_80089810;
    *(s32 *) (gdl + 0x8) = 0xD9AFFDFF;
    *(s32 *) (gdl + 0xC) = 0;
    *(s32 *) (gdl + 0x14) = 0x20000;
    *(s32 *) (gdl + 0x10) = 0xD9FFFFFF;
    return (Gfx *) (gdl + 0x18);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/func_15113B44.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/func_15113D54.s")

extern u8 D_800C3A7C;
s32 func_15022BB0(s32, s32);
void *func_1510DEF0(s32, struct131 *, s32, s32, s32);

void func_15114208(void) {
    s32 i;
    s32 j;
    s32 found;
    s32 ok;
    struct131 *e;

    for (i = 0; i < D_800DC320; i++) {
        e = &D_800DBEF4[i];
        found = 0;
        for (j = 0; j < D_80082FA0; j++) {
            do {
            } while (0); // fakematch: changes the s-register allocation
            if (func_150859AC(j, 0) && ((u8 *)e)[0x8B + j] == 0) {
                found = 1;
                break;
            }
        }
        if ((e->pad70[0] & 8) || ((u8 *)e)[0x4C] == 0 || (((u8 *)e)[0x4F] & 0x10) == 0x10 || found ||
            (D_800C3A7C == 0 && D_800C35EA == 1 && !func_15022BB0(i, 0)) || !(((u8 *)e)[0x4F] & 1)) {
            ok = 0;
        } else {
            ok = 1;
        }
        if (ok) {
            if (*(void **)((u8 *)e + 0x94) == NULL) {
                *(void **)((u8 *)e + 0x94) = func_1510DEF0(1, e, 0, 1, 0);
            }
        } else if (*(struct102 **)((u8 *)e + 0x94) != NULL) {
            func_1516972C(*(struct102 **)((u8 *)e + 0x94));
            *(struct102 **)((u8 *)e + 0x94) = NULL;
        }
    }
}

#ifdef NON_MATCHING
/* the D_800DBEF4 record fields func_151143D4 uses (0xA0 bytes) */
typedef struct {
    u8  pad0[0x38];
    void (*update)(void *);   /* 0x38 */
    u8  pad3C[0x5A - 0x3C];
    s16 pos[3];               /* 0x5A */
    u8  pad60[0x6E - 0x60];
    u8  busy;                 /* 0x6E */
    u8  flags;                /* 0x6F: 0x40 = needs update */
    u8  pad70[0x80 - 0x70];
    s32 extra;                /* 0x80 */
    u8  pad84[0xA0 - 0x84];
} Rec151143D4;

/* a D_800D23C0 group (0x18 bytes): ids[] are (type << 12 | record index); type 2 = D_800DBEF4 record */
typedef struct {
    u8  pad0[2];
    u16 count;                /* 0x2 */
    u8  pad4[4];
    u16 ids[8];               /* 0x8 */
} Group151143D4;

extern s32 D_800DC3C8;

/* Runs the update callback of every pending record (flags & 0x40, not busy): first the first
 * D_800DC320 - D_800DC3C8 records, then the type-2 groups. In a group, the first record's position (0x5A..0x5E)
 * and 0x80 value are copied to each following member before its update. arg0 is not used. */
void func_151143D4(s32 arg0) {
    Rec151143D4 *rec;
    Group151143D4 *grp;
    s16 x, y, z;
    s32 extra;
    s32 n, i, j;
    u16 id;

    x = y = z = 0;
    extra = 0;
    n = D_800DC320 - D_800DC3C8;
    for (i = 0; i < n; i++) {
        rec = (Rec151143D4 *) D_800DBEF4 + i;
        if ((rec->flags & 0x40) == 0x40 && rec->busy == 0) {
            rec->update(rec);
        }
    }
    for (i = 0; i < (s32) D_80087380; i++) {
        grp = (Group151143D4 *) D_800D23C0 + i;
        if ((grp->ids[0] >> 12) != 2) {
            continue;
        }
        for (j = 0; j < grp->count; j++) {
            id = ((Group151143D4 *) D_800D23C0)[i].ids[j];
            if ((id >> 12) != 2) {
                continue;
            }
            rec = (Rec151143D4 *) D_800DBEF4 + (id & 0xFFF);
            if ((rec->flags & 0x40) == 0x40 && rec->busy == 0) {
                if (j != 0) {
                    rec->pos[0] = x;
                    rec->pos[1] = y;
                    rec->pos[2] = z;
                    rec->extra = extra;
                }
                rec->update(rec);
                grp = (Group151143D4 *) D_800D23C0 + i;   /* the callback may move the groups */
            }
            if (j == 0) {
                x = rec->pos[0];
                y = rec->pos[1];
                z = rec->pos[2];
                extra = rec->extra;
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/func_151143D4.s")
#endif

extern s32 *D_800DC3C4;

s32 func_151145D0(struct131 *arg0, s32 arg1) {
    if (*((u8 *)arg0 + 0x4F) & 0x80) {
        if (arg1 == -1) {
            return 1;
        }
        if (D_800DC3C4[arg0 - D_800DBEF4] & (1 << arg1)) {
            return 1;
        }
    }
    return 0;
}

s32 func_15114644(u8 *arg0) {
    s32 i;
    s32 v;
    s32 m; // fakematch: mask temp fixes the and operand order
    i = 0;
    if (arg0[0x4F] & 0x80) {
        v = D_800DC3C4[(arg0 - (u8 *)D_800DBEF4) / 160];
loop:
        m = 1 << i;
        if ((v & m) != 0) return i;
        m = 1 << (i + 1);
        if ((v & m) != 0) return i + 1;
        m = 1 << (i + 2);
        if ((v & m) != 0) return i + 2;
        m = 1 << (i + 3);
        if ((v & m) != 0) return i + 3;
        i += 4;
        if (i != 0x20) goto loop;
    }
    return 0;
}

#ifdef NON_MATCHING
void func_15114CBC(struct127 *, s32);
extern s32 *D_800DC3C4;
typedef void (*fn15114708)(u8 *, struct127 *, u8 *, void *);

void func_15114708(void) {
    s32 i;
    s32 j;
    s32 *mask;
    u8 *e;
    u8 *base;
    fn15114708 fn;
    struct127 *obj;
    u8 f;

    for (i = 0; i < D_800DC320; i++) {
        if (D_800DC3C4[i] == 0) {
            continue;
        }
        for (j = 0; j < 0x19 && D_800DC3C4[i] != 0; j++) {
            mask = &D_800DC3C4[i];
            if (!(*mask & (1 << j))) {
                continue;
            }
            *mask ^= 1 << j;
            base = (u8 *)D_800DBEF4;
            e = base + i * 0xA0;
            fn = *(fn15114708 *)(e + 0x78);
            obj = (struct127 *)((u8 *)D_800CC2D0 + j * 0x32C);
            if (fn != NULL && (e[0x92] != 0 || ((u8 *)obj)[0x127] != 0xFF)) {
                (*fn)(e, obj, base, (void *)fn);
                e = (u8 *)D_800DBEF4 + i * 0xA0;
            }
            f = e[0x4F];
            if ((f & 4) == 4 && !(f & 8)) {
                func_15114CBC(obj, i);
            }
        }
        e = (u8 *)D_800DBEF4 + i * 0xA0;
        e[0x4F] &= 0x73;
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/func_15114708.s")
#endif
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/func_151148C8.s")

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/func_15114CBC.s")

void func_150A7A48(f32 (*)[4], f32 (*)[4], f32 (*)[4]);
void func_15114E28(f32 (*arg0)[4], u8 *arg1) {
    f32 sp18[4][4];
    func_150A8050(arg0, 0.0f, *(f32 *)(arg1 + 4), 0.0f);
    func_150A8050(sp18, *(f32 *)arg1, 0.0f, *(f32 *)(arg1 + 8));
    func_150A7A48(sp18, arg0, arg0);
}

void func_15114E8C(f32 (*arg0)[4], u8 *arg1) {
    f32 sp20[4][4];

    func_15114E28(arg0, arg1);
    (*(f32 *)((u8 *)arg0 + 0x30)) = *(s16 *)(arg1 + 0x10);
    (*(f32 *)((u8 *)arg0 + 0x34)) = *(f32 *)(arg1 + 0x18) + *(s16 *)(arg1 + 0x12);
    (*(f32 *)((u8 *)arg0 + 0x38)) = *(s16 *)(arg1 + 0x14);
    func_150A7CB0(sp20, *(s32 *)(arg1 + 0x2C), *(s32 *)(arg1 + 0x30), *(s32 *)(arg1 + 0x34));
    func_150A7A48(sp20, arg0, arg0);
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/func_151149AC.s")

#ifdef NON_MATCHING
/* Per-frame release of the per-entry blocks D_800DC328[i] (P15, hand C from the asm). Entries are the
 * 0xA0-byte D_800DBEF4 records. A disabled entry (flag 0x70 & 1) drops its block pointer unless it is
 * kept (0x6F & 0x80). Otherwise a live block is freed at once, or, for kept / type-3 entries (0x4E),
 * after its D_800DC32C[i] frame countdown reaches 0. */
void func_10004074(s32);
void func_15114F9C(void) {
    s32 i;

    for (i = 0; i < D_800DC320; i++) {
        u8 *e = (u8 *)D_800DBEF4 + i * 0xA0;

        if ((e[0x70] & 1) == 1) {
            if (!(e[0x6F] & 0x80)) {
                D_800DC328[i] = 0;
            }
        } else if (D_800DC328[i] != 0) {
            if (e[0x4E] != 3 && !(e[0x6F] & 0x80)) {
                func_10004074(D_800DC328[i]);
                D_800DC328[i] = 0;
            } else if (D_800DC32C[i] != 0) {
                D_800DC32C[i]--;
            } else {
                func_10004074(D_800DC328[i]);
                D_800DC328[i] = 0;
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/func_15114F9C.s")
#endif
extern s32 D_800DC3C8;

void func_15115114(u32 arg0) {
    struct131 *p;
    u32 j;

    j = arg0 * 0xA0; // fakematch: j doubles as the row offset
    if (arg0 < D_800DC320) {
        p = (struct131 *)((u8 *)D_800DBEF4 + j);
        if (*(struct102 **)((u8 *)p + 0x94) != NULL) {
            func_1516972C(*(struct102 **)((u8 *)p + 0x94));
            *(struct102 **)((u8 *)D_800DBEF4 + arg0 * 0xA0 + 0x94) = NULL;
            p = (struct131 *)((u8 *)D_800DBEF4 + arg0 * 0xA0);
        }
        p->pad70[0] |= 8;
        D_800DBEF4[arg0].pad5A[0x14] = 1;
    }
    arg0 = D_800DC320 - 1;
    j = D_800DC320 - D_800DC3C8;
    if (D_800DC320 != 0) {
        p = (struct131 *)((u8 *)D_800DBEF4 + arg0 * 0xA0);
        if (p->pad70[0] & 8) {
            do {
                if (arg0 >= j && D_800DC3C8 != 0) {
                    D_800DC3C8--;
                } else {
                    j--;
                }
                D_800DC320--;
                arg0--;
                p--;
            } while (D_800DC320 != 0 && (p->pad70[0] & 8));
        }
    }
}

s32 func_15115244(u8 *arg0, s32 arg1, s32 *arg2, s32 arg3) {
    u8 *temp_v1;

    temp_v1 = (*(u8 **)((u8 *)arg0 + 0x18));
    if ((temp_v1 != NULL) && ((*arg2 != 0) || ((*(s32 *)((u8 *)arg0 + 0x1C)) == 0))) {
        (*(s32 *)((u8 *)arg0 + 0x1C)) = 1;
        (*(s16 *)((u8 *)arg0 + 2)) = (s16) (*(s16 *)((u8 *)temp_v1 + 0x10));
        (*(s16 *)((u8 *)arg0 + 4)) = (s16) (*(s16 *)((u8 *)temp_v1 + 0x12));
        (*(s16 *)((u8 *)arg0 + 6)) = (s16) (*(s16 *)((u8 *)temp_v1 + 0x14));
        return 0;
    }
    return 1;
}

#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_13DC30/func_151152A4.s")

void func_15115484(s32 arg0, s32 arg1, s32 arg2) {
    func_1001001C(func_15115244, arg0, 0, arg1, arg2);
}

s32 func_150ADC50();
extern s32 D_800DC3CC;
extern s32 D_800DC3D0;
extern s32 D_800DC3D4;

void func_151154C4(s32 arg0, s32 arg1, s32 arg2)
{
    s32 i;
    s32 j;
    if (D_800BE9F0 == 0x12 || D_800BE9F0 == 0x36 || D_800BE9F0 == 0x13) {
        for (i = 0; i < 2; i++) {
            u32 *base = (u32 *)D_800DC208[i];
            for (j = 0; j < D_800DBE18[i]; j++) {
                if ((base[j * 3 + 0] & 0xF0000000) != 0x80000000 || (base[j * 3 + 1] & 0xF0000000) != 0x80000000 || (base[j * 3 + 2] & 0xF0000000) != 0x80000000 || (base[j * 3 + 0] & 3) || (base[j * 3 + 1] & 3) || (base[j * 3 + 2] & 3)) {
                    D_8003C8E0 = 0x0C00005A;
                    func_150ADC50();
                }
            }
        }
        D_800DC3CC = arg0;
        D_800DC3D0 = arg1;
        D_800DC3D4 = arg2;
    }
}
