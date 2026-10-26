#include <ultra64.h>
#include "functions.h"
#include "variables.h"


/* was func_15172210 */
u8 *decal_alloc(s16 arg0, u16 arg1, u8 arg2, s32 arg3, s32 arg4, s32 arg5, u8 arg6, s32 arg7) {
    s32 var_a0;
    u8 *t;
    if (arg5 == 0) {
        var_a0 = 0xF;
    } else {
        var_a0 = 0x43;
    }
    t = node_alloc(var_a0, arg7, 0x60, 1, (u8) (s32) arg6, 1U);
    if (t == NULL) {
        return NULL;
    }
    *(s16 *)(t + 0x50) = arg0;
    *(s16 *)(t + 0x52) = 0;
    *(s16 *)(t + 0x54) = arg4;
    *(u16 *)(t + 0x56) = arg1;
    *(u8 *)(t + 0x58) = arg2;
    *(s8 *)(t + 0x59) = arg3;
    *(s16 *)(t + 0x16) = 0;
    *(s16 *)(t + 0x26) = 0;
    *(s16 *)(t + 0x36) = 0;
    *(s16 *)(t + 0x46) = 0;
    return t;
}

extern s32 D_8008CDEC; /* sprite texture descriptors (u8 * per id): u16 width / height at +6 / +8 */
s32 decal_place_on_floor(u8 *, f32, f32, f32, f32, s32, s32, s32);

// sprite_spawn_at: allocates a sprite (decal_alloc: kind `kind`, texture `tex`, flags ...) and places it at
// (x, y, z): normally through decal_place_on_floor (size `size`, `arg7`, `radius`; the sprite is freed again with
// node_destroy when that fails); with flags bit 1 as a flat quad of half side `radius` at height y, UVs from the
// texture's size (+6 / +8, + 0x100, << 5), 0x2000 on +0x18 / +0x1A / +0x2A / +0x48.
/* was func_151722BC */
void decal_spawn_at(f32 x, f32 y, f32 z, s16 kind, u16 arg4, u8 tex, f32 size, s32 arg7, s32 radius, s32 flags,
                   s32 argA, s32 argB, u8 argC, s32 argD) {
    u8 *v;
    u8 *t;
    f32 r;
    s16 h;

    v = decal_alloc(kind, arg4, tex, flags, argA, argB, argC, argD);
    if (v == NULL) {
        return;
    }
    if (!(flags & 2)) {
        if (decal_place_on_floor(v + 0x10, x, y, z, size, arg7, radius,
                          *(u16 *) (((u8 **) &D_8008CDEC)[v[0x58]] + 6)) == 0) {
            node_destroy((struct102 *) v);
        }
        return;
    }
    r = radius;
    h = (s32) y;
    *(s16 *) (v + 0x42) = h;
    *(s16 *) (v + 0x32) = h;
    *(s16 *) (v + 0x22) = h;
    *(s16 *) (v + 0x12) = h;
    *(s16 *) (v + 0x40) = (s32) (x - r);
    *(s16 *) (v + 0x10) = (s32) (x - r);
    *(s16 *) (v + 0x48) = 0x2000;
    *(s16 *) (v + 0x30) = (s32) (r + x);
    *(s16 *) (v + 0x20) = (s32) (r + x);
    *(s16 *) (v + 0x18) = *(s16 *) (v + 0x48);
    *(s16 *) (v + 0x24) = (s32) (z - r);
    *(s16 *) (v + 0x14) = (s32) (z - r);
    *(s16 *) (v + 0x44) = (s32) (r + z);
    *(s16 *) (v + 0x34) = (s32) (r + z);
    t = ((u8 **) &D_8008CDEC)[tex];
    *(s16 *) (v + 0x2A) = 0x2000;
    *(s16 *) (v + 0x38) = (*(u16 *) (t + 6) + 0x100) << 5;
    *(s16 *) (v + 0x28) = (*(u16 *) (t + 6) + 0x100) << 5;
    *(s16 *) (v + 0x1A) = *(s16 *) (v + 0x2A);
    *(s16 *) (v + 0x4A) = (*(u16 *) (t + 8) + 0x100) << 5;
    *(s16 *) (v + 0x3A) = (*(u16 *) (t + 8) + 0x100) << 5;
}

s32 decal_fit_to_triangle(s32, s32, f32, f32, f32, f32, s32, s32);
extern s32 D_8008CDEC;

/* was func_15172474 */
void decal_spawn_on_triangle(f32 arg0, f32 arg1, f32 arg2, s32 arg3, s16 arg4, u16 arg5, u8 arg6, s32 arg7, s32 arg8, s32 arg9, s32 argA, u8 argB, s32 argC) {
    u8 *temp_v0;
    u8 *sp2C;

    temp_v0 = decal_alloc(arg4, arg5, arg6, arg8, arg9, argA, (s32) argB, argC);
    if (temp_v0 != NULL) {
        sp2C = temp_v0;
        if (decal_fit_to_triangle((s32)((u8 *)temp_v0 + 0x10), arg3, arg0, arg1, arg2, 0.0f, arg7, *(u16 *)((u8 *)((s32 *)&D_8008CDEC)[*((u8 *)temp_v0 + 0x58)] + 6)) == 0) {
            node_destroy((struct102 *)sp2C);
        }
    }
}

/* was func_15172530 */
void decal_tick(struct102 *arg0) {
    s16 temp_v0;
    s32 temp_v0_2;

    temp_v0 = (*(s16 *)((u8 *)arg0 + 0x50));
    if (temp_v0 < -1) {
        (*(s16 *)((u8 *)arg0 + 0x50)) = (s16) (temp_v0 + 1);
        if ((*(s16 *)((u8 *)arg0 + 0x50)) == -1) {
            node_destroy(arg0);
        }
    } else {
        if (temp_v0 == 0) {
            (*(s16 *)((u8 *)arg0 + 0x50)) = -3;
            return;
        }
        if (temp_v0 != -1) {
            if (!((*(u8 *)((u8 *)arg0 + 0x59)) & 4)) {
                if (D_800BE9E4 < temp_v0) {
                    (*(s16 *)((u8 *)arg0 + 0x50)) = (s16) (temp_v0 - D_800BE9E4);
                } else {
                    (*(s16 *)((u8 *)arg0 + 0x50)) = 0;
                }
            }
            (*(s16 *)((u8 *)arg0 + 0x52)) = (s16) ((*(s16 *)((u8 *)arg0 + 0x54)) + (*(s16 *)((u8 *)arg0 + 0x52)));
            temp_v0_2 = (*(u8 *)((u8 *)((&D_8008CDEC)[(*(u8 *)((u8 *)arg0 + 0x58))]) + 4));
            if (((s16) (*(s16 *)((u8 *)arg0 + 0x52)) / 256) >= temp_v0_2) {
                if ((*(u8 *)((u8 *)arg0 + 0x59)) & 4) {
                    (*(s16 *)((u8 *)arg0 + 0x50)) = -3;
                    return;
                }
                (*(s16 *)((u8 *)arg0 + 0x52)) = (s16) ((temp_v0_2 << 8) - 0x100);
            }
        }
    }
}

extern s32 D_800D30BC;
extern u32 D_800DD5E4;
extern s32 D_800DD5E8;
extern s16 D_800DD5EC;

/* was func_15172634 */
u8 *decal_draw(u8 *arg0, u8 *arg1, s32 arg2) {
    struct {
        s32 u8C;
        s32 u90;
        u32 u94;
        s32 u98;
        u8 pad9C[0x18];
        s32 uB4;
        s32 uB8;
    } sp;
    s32 sp88;
    s32 sp84;
    s32 sp80;
    s16 temp_a2;
    s16 temp_t5;
    s16 temp_t6;
    s16 temp_t8;
    s16 temp_v1_2;
    s16 var_a0_2;
    s32 temp_t4;
    s32 var_a0;
    s32 var_t0_2;
    s32 var_t2;
    s32 var_v1;
    s32 var_v1_2;
    u16 temp_v0_4;
    u32 temp_v0;
    u32 var_t0;
    u8 temp_v1;
    u8 *temp_s0;
    u8 *temp_s0_2;
    u8 *temp_s0_3;
    u8 *temp_v0_2;
    u8 *temp_v0_3;
    u8 *var_s0;
    u8 *var_s0_2;

    var_s0 = arg0;
    sp.u8C = 1;
    if ((*(s16 *)((u8 *)arg1 + 0x50)) >= 2) {
        temp_t4 = (&D_8008CDEC)[(*(u8 *)((u8 *)arg1 + 0x58))];
        sp88 = temp_t4;
        temp_v0 = *(s32 *)temp_t4;
        temp_a2 = (*(s16 *)((u8 *)arg1 + 0x52));
        var_t0 = temp_v0;
        var_v1 = temp_a2 >> 8;
        if (temp_v0 >= 0x10000000U) {
            var_t0 = *(s32 *)(temp_v0 + (var_v1 * 4));
            var_v1 = 0;
        }
        if ((var_t0 != D_800DD5E4) || (var_v1 != D_800DD5E8)) {
            sp.u90 = var_v1;
            sp.u94 = var_t0;
            temp_v0_2 = sprite_load_texture(var_s0, sp88, temp_a2, &sp.u98, 0, 0, 0, 2, 3);
            D_800DD5E4 = sp.u94;
            var_s0 = temp_v0_2;
            D_800DD5E8 = sp.u90;
        }
        var_t0_2 = D_800DD5EC & 0xF;
        if (!((*(u8 *)((u8 *)arg1 + 0x59)) & 1)) {
            var_v1_2 = 1;
        } else {
            var_v1_2 = 2;
        }
        if ((*(u8 *)((u8 *)sp88 + 0xA)) == 5) {
            var_v1_2 += 2;
        }
        if (var_t0_2 != var_v1_2) {
            var_t0_2 = var_v1_2;
            if (sp.u8C != 0) {
                (*(s32 *)((u8 *)var_s0 + 0)) = 0xE7000000;
                (*(s32 *)((u8 *)var_s0 + 4)) = 0;
                var_s0 += 8;
            }
            sp.u8C = 0;
            switch (var_v1_2) {                     /* switch 1; irregular */
            case 1:                                 /* switch 1 */
                sp84 = 0;
                sp80 = 0x504DD8;
                break;
            case 2:                                 /* switch 1 */
                sp84 = 0;
                sp80 = 0x504B50;
                break;
            case 3:                                 /* switch 1 */
                sp84 = 0x100000;
                sp80 = 0x0C184DD8;
                break;
            case 4:                                 /* switch 1 */
                sp84 = 0x100000;
                sp80 = 0x0C184B50;
                break;
            }
            (*(s32 *)((u8 *)var_s0 + 0)) = 0xE2001E01;
            (*(s32 *)((u8 *)var_s0 + 4)) = 0;
            temp_s0 = var_s0 + 8;
            (*(s32 *)((u8 *)temp_s0 + 0)) = 0xD9EEFFFF;
            (*(s32 *)((u8 *)temp_s0 + 4)) = 0;
            var_s0 = temp_s0 + 8;
        }
        sp.uB8 = var_t0_2;
        sp.uB4 = D_800DD5EC & 0xF0;
        temp_v0_3 = gfx_other_mode_cached(var_s0, sp84 | 0x80000 | D_800D30BC | 0x2CB0, sp80, &sp.u8C);
        var_t2 = sp.uB4;
        var_s0_2 = temp_v0_3;
        var_a0 = 0x40;
        if (!((*(u8 *)((u8 *)arg1 + 0x59)) & 8)) {
            temp_v1 = (*(u8 *)((u8 *)sp88 + 0xA));
            if (temp_v1 == 0) {
                if ((*(u16 *)((u8 *)arg1 + 0x56)) != 0) {
                    var_a0 = 0x10;
                } else {
                    var_a0 = 0x20;
                }
            } else if (temp_v1 == 5) {
                if ((*(u16 *)((u8 *)arg1 + 0x56)) != 0) {
                    var_a0 = 0x60;
                } else {
                    var_a0 = 0x50;
                }
            } else {
                var_a0 = 0x30;
            }
        }
        if (var_t2 != var_a0) {
            var_t2 = var_a0;
            if (sp.u8C != 0) {
                (*(s32 *)((u8 *)temp_v0_3 + 0)) = 0xE7000000;
                var_s0_2 = temp_v0_3 + 8;
                (*(s32 *)((u8 *)temp_v0_3 + 4)) = 0;
            }
            switch (var_a0) {
            case 0x10:
                (*(s32 *)((u8 *)var_s0_2 + 0)) = 0xFC30B261;
                (*(s32 *)((u8 *)var_s0_2 + 4)) = 0xFF67FFFF;
                var_s0_2 += 8;
                break;
            case 0x20:
                (*(s32 *)((u8 *)var_s0_2 + 0)) = 0xFCFFB3FF;
                (*(s32 *)((u8 *)var_s0_2 + 4)) = 0xFF64FE7F;
                var_s0_2 += 8;
                break;
            case 0x30:
                (*(s32 *)((u8 *)var_s0_2 + 0)) = 0xFCFF97FF;
                (*(s32 *)((u8 *)var_s0_2 + 4)) = 0xFF2DFEFF;
                var_s0_2 += 8;
                break;
            case 0x40:
                (*(s32 *)((u8 *)var_s0_2 + 0)) = 0xFCFFFFFF;
                (*(s32 *)((u8 *)var_s0_2 + 4)) = 0xFFFCF279;
                var_s0_2 += 8;
                break;
            case 0x50:
                (*(s32 *)((u8 *)var_s0_2 + 0)) = 0xFCFFB5FF;
                (*(s32 *)((u8 *)var_s0_2 + 4)) = 0xFFFCFE38;
                var_s0_2 += 8;
                break;
            case 0x60:
                (*(s32 *)((u8 *)var_s0_2 + 4)) = -0x1C8;
                (*(s32 *)((u8 *)var_s0_2 + 0)) = 0xFC30B5FF;
                var_s0_2 += 8;
                break;
            }
        }
        D_800DD5EC = sp.uB8 | var_t2;
        temp_v0_4 = (*(u16 *)((u8 *)arg1 + 0x56));
        temp_v1_2 = (*(s16 *)((u8 *)arg1 + 0x50));
        temp_t5 = ((s32) temp_v0_4 >> 8) & 0xF8;
        temp_t6 = ((s32) temp_v0_4 >> 3) & 0xF8;
        temp_t8 = (temp_v0_4 * 4) & 0xF8;
        if (temp_v1_2 >= 0x1A) {
            var_a0_2 = 0xFF;
        } else {
            var_a0_2 = temp_v1_2 * 0xA;
        }
        if ((temp_t5 != D_800DD5F0) || (temp_t6 != D_800DD5F2) || (temp_t8 != D_800DD5F4) || (var_a0_2 != D_800DD5F6)) {
            D_800DD5F0 = temp_t5;
            D_800DD5F2 = temp_t6;
            D_800DD5F4 = temp_t8;
            D_800DD5F6 = var_a0_2;
            if (sp.u8C != 0) {
                (*(s32 *)((u8 *)var_s0_2 + 0)) = 0xE7000000;
                (*(s32 *)((u8 *)var_s0_2 + 4)) = 0;
                var_s0_2 += 8;
            }
            (*(s32 *)((u8 *)var_s0_2 + 0)) = 0xFA000100;
            (*(s32 *)((u8 *)var_s0_2 + 4)) = (s32) ((temp_t5 << 0x18) | ((temp_t6 & 0xFF) << 0x10) | ((temp_t8 & 0xFF) << 8) | (var_a0_2 & 0xFF));
            var_s0_2 += 8;
        }
        (*(u8 **)((u8 *)var_s0_2 + 4)) = (u8 *) (arg1 + 0x10);
        (*(s32 *)((u8 *)var_s0_2 + 0)) = 0x01004008;
        temp_s0_2 = var_s0_2 + 8;
        (*(s32 *)((u8 *)temp_s0_2 + 0)) = 0x05000204;
        (*(s32 *)((u8 *)temp_s0_2 + 4)) = 0;
        temp_s0_3 = temp_s0_2 + 8;
        (*(s32 *)((u8 *)temp_s0_3 + 0)) = 0x05000406;
        (*(s32 *)((u8 *)temp_s0_3 + 4)) = 0;
        var_s0 = temp_s0_3 + 8;
    }
    return var_s0;
}
extern f32 D_800A7524;
extern f32 D_800A7530;
s32 floor_triangle_slope(s32, s32, f32 *, f32 *);
extern s32 D_800A73B0;
extern s32 D_800A73C0;
extern s32 D_800A73D0;

/* was func_15172B6C */
s32 decal_fit_to_triangle(s32 arg0, s32 arg1, f32 arg2, f32 arg3, f32 arg4, f32 arg5, s32 arg6, s32 arg7) {
    struct {
        f32 u64;
        f32 u68;
        u8 pad6C[0x8];
        f32 u74;
        f32 u78;
        f32 u7C;
        f32 u80;
        f32 u84;
        f32 u88;
    } sp;
    f32 sp58;
    s32 sp48;
    f32 sp40;
    s32 *var_a1;
    s32 *var_v0_2;
    f32 *var_v0;
    f32 temp_f0;
    f32 temp_f0_2;
    f32 temp_f0_3;
    f32 temp_f12;
    f32 temp_f12_2;
    f32 temp_f14;
    f32 temp_f18;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f4;
    f32 temp_f6;
    f32 temp_f6_2;
    f32 temp_f8;
    f32 var_f12;
    f32 var_f12_2;
    f32 var_f14;
    f32 var_f18;
    f32 var_f2;
    s16 temp_f10;
    s32 temp_t6;
    s32 var_a0;
    s32 var_a0_2;
    s32 var_v1;
    s32 var_v1_2;
    s32 var_v1_3;

    temp_t6 = arg6 / 16;
    var_v1 = temp_t6;
    if (temp_t6 == 0) {
        var_v1 = 1;
    }
    sp48 = var_v1;
    if (floor_triangle_slope(arg1, 0, &sp.u64, &sp.u68) == 0) {
        return 0;
    }
    temp_f18 = (f32) -sp48;
    sp.u74 = 0.0f;
    temp_f12 = -temp_f18 - temp_f18;
    temp_f4 = (temp_f18 * sp.u68) + (sp.u64 * 0.0f);
    sp.u78 = temp_f4;
    var_f2 = (2.0f * temp_f12) + (2.0f * sp.u68 * (-temp_f4 - temp_f4));
    if (var_f2 == 0.0f) {
        var_f2 = D_800A7524;
    }
    sp.u80 = temp_f18;
    temp_f14 = sp.u64 * sp.u80;
    sp.u84 = (temp_f12 * (2.0f * temp_f14)) / var_f2;
    if (sp.u68 == 0.0f) {
        var_f18 = 0.0f;
    } else {
        var_f18 = (sp.u84 - temp_f14) / sp.u68;
    }
    sp.u7C = temp_f18;
    var_f12 = (temp_f18 * temp_f18) + (0.0f + (sp.u78 * sp.u78));
    if (var_f12 > 1e8f) {
        var_f12 = 1e8f;
    }
    temp_f2 = (f32) (sp48 * sp48);
    if (var_f12 < temp_f2) {
        var_f12 = temp_f2;
    }
    temp_f0 = sqrtf(var_f12);
    sp.u88 = var_f18;
    var_f14 = (var_f18 * var_f18) + ((sp.u80 * sp.u80) + (sp.u84 * sp.u84));
    if (var_f14 > 1e8f) {
        var_f14 = 1e8f;
    }
    if (var_f14 < temp_f2) {
        var_f14 = temp_f2;
    }
    temp_f0_2 = sqrtf(var_f14);
    var_v0 = &sp.u74;
    var_a0 = 0;
    var_v1_2 = arg0;
    temp_f2_2 = (f32) arg6;
    do {
        temp_f8 = (*(f32 *)((u8 *)var_v0 + 0xC));
        var_a0 += 2;
        temp_f6 = (*(f32 *)((u8 *)var_v0 + 0)) * temp_f2_2;
        var_v0 = (f32 *)((u8 *)var_v0 + (4));
        var_v1_2 += 2;
        (*(f32 *)((u8 *)var_v0 + -4)) = (f32) (temp_f6 / temp_f0);
        (*(f32 *)((u8 *)var_v0 + 8)) = (f32) ((temp_f8 * temp_f2_2) / temp_f0_2);
        (*(s16 *)((u8 *)var_v1_2 + -2)) = (s16) (s32) (*(f32 *)((u8 *)var_v0 + -4));
        (*(s16 *)((u8 *)var_v1_2 + 0xE)) = (s16) (s32) (*(f32 *)((u8 *)var_v0 + 8));
        (*(s16 *)((u8 *)var_v1_2 + 0x1E)) = (s16) (s32) -(*(f32 *)((u8 *)var_v0 + -4));
        (*(s16 *)((u8 *)var_v1_2 + 0x2E)) = (s16) (s32) -(*(f32 *)((u8 *)var_v0 + 8));
    } while (var_a0 < 6);
    temp_f12_2 = (arg5 - 225.0f) * D_800A7530;
    sp40 = temp_f12_2;
    sp58 = cosf(temp_f12_2);
    temp_f0_3 = sinf(temp_f12_2);
    var_a0_2 = 0;
    if ((u8) arg7 == 0x10) {
        var_f12_2 = 256.0f;
        var_a1 = &D_800A73D0;
    } else if ((u8) arg7 == 0x20) {
        var_f12_2 = 512.0f;
        var_a1 = &D_800A73C0;
    } else {
        var_f12_2 = 1024.0f;
        var_a1 = &D_800A73B0;
    }
    var_v1_3 = arg0;
    var_v0_2 = var_a1;
    do {
        var_a0_2 += 0x10;
        var_v1_3 += 0x10;
        temp_f6_2 = (f32) (*(s16 *)((u8 *)var_v0_2 + 0));
        temp_f10 = (*(s16 *)((u8 *)var_v0_2 + 2));
        var_v0_2 = (s32 *)((u8 *)var_v0_2 + (4));
        (*(s16 *)((u8 *)var_v1_3 + -8)) = (s16) (s32) ((((temp_f6_2 - var_f12_2) * sp58) - (((f32) temp_f10 - var_f12_2) * temp_f0_3)) + var_f12_2 + 8192.0f);
        (*(s16 *)((u8 *)var_v1_3 + -6)) = (s16) (s32) ((((f32) (*(s16 *)((u8 *)var_v0_2 + -2)) - var_f12_2) * sp58) + (((f32) (*(s16 *)((u8 *)var_v0_2 + -4)) - var_f12_2) * temp_f0_3) + var_f12_2 + 8192.0f);
    } while (var_a0_2 < 0x40);
    (*(s16 *)((u8 *)arg0 + 0)) = (s16) (s32) ((f32) (*(s16 *)((u8 *)arg0 + 0)) + arg2);
    (*(s16 *)((u8 *)arg0 + 2)) = (s16) (s32) ((f32) (*(s16 *)((u8 *)arg0 + 2)) + arg3);
    (*(s16 *)((u8 *)arg0 + 4)) = (s16) (s32) ((f32) (*(s16 *)((u8 *)arg0 + 4)) + arg4);
    (*(s16 *)((u8 *)arg0 + 0x10)) = (s16) (s32) ((f32) (*(s16 *)((u8 *)arg0 + 0x10)) + arg2);
    (*(s16 *)((u8 *)arg0 + 0x12)) = (s16) (s32) ((f32) (*(s16 *)((u8 *)arg0 + 0x12)) + arg3);
    (*(s16 *)((u8 *)arg0 + 0x14)) = (s16) (s32) ((f32) (*(s16 *)((u8 *)arg0 + 0x14)) + arg4);
    (*(s16 *)((u8 *)arg0 + 0x20)) = (s16) (s32) ((f32) (*(s16 *)((u8 *)arg0 + 0x20)) + arg2);
    (*(s16 *)((u8 *)arg0 + 0x22)) = (s16) (s32) ((f32) (*(s16 *)((u8 *)arg0 + 0x22)) + arg3);
    (*(s16 *)((u8 *)arg0 + 0x24)) = (s16) (s32) ((f32) (*(s16 *)((u8 *)arg0 + 0x24)) + arg4);
    (*(s16 *)((u8 *)arg0 + 0x30)) = (s16) (s32) ((f32) (*(s16 *)((u8 *)arg0 + 0x30)) + arg2);
    (*(s16 *)((u8 *)arg0 + 0x32)) = (s16) (s32) ((f32) (*(s16 *)((u8 *)arg0 + 0x32)) + arg3);
    (*(s16 *)((u8 *)arg0 + 0x34)) = (s16) (s32) ((f32) (*(s16 *)((u8 *)arg0 + 0x34)) + arg4);
    return 1;
}
void collision_find_floor_default_range(s32, s32, s32, s32, s32, s32, f32, f32, f32, f32, u16, s32);
s32 decal_fit_to_triangle(s32, s32, f32, f32, f32, f32, s32, s32);
// sprite_place_on_floor: moves (x, z) by `dist` along the angle `angle` - 90 degrees (x += dist sin, z += dist cos of
// angle - 90), looks up the floor under the new point (collision_find_floor_default_range: floor object and height) and places the
// sprite there (decal_fit_to_triangle with the floor, x, the floor height, z, angle, arg6 and the low byte of arg7).
// Returns decal_fit_to_triangle's result, 0 when there is no floor or the floor height is the "none" value -10000.
/* was func_15173090 */
s32 decal_place_on_floor(u8 *spr, f32 x, f32 y, f32 z, f32 angle, s32 dist, s32 arg6, s32 arg7) {
    s32 floor;
    f32 floorY;
    s32 tri;
    f32 a;
    f32 c;
    f32 s;

    a = (angle - 90.0f) * 0.017453292f;
    c = cosf(a);
    s = sinf(a);
    x += (f32) dist * s;
    z += (f32) dist * c;
    collision_find_floor_default_range((s32) &floor, 0, (s32) &floorY, 0, (s32) &tri, 0, x, y, z, y, 0, 0);
    if (floor == 0) {
        return 0;
    }
    if (floorY == -10000.0f) {
        return 0;
    }
    return decal_fit_to_triangle((s32) spr, floor, x, floorY, z, angle, arg6, (u8) arg7);
}
