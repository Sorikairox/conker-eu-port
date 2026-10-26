#include <ultra64.h>

#include "functions.h"
#include "variables.h"
// hoisted declarations of the NON_MATCHING bodies
void clamp_range_to_bounds(s32 *arg0, s32 *arg1, s32 arg2, s32 arg3);

void mtx_get_translation(Mtx *, s32, f32 *);

/* was func_151429E0 */
void fx_pick_random_color(u8 arg0, u8 *arg1, u8 *arg2, u8 *arg3) {
    u8 *temp_v1 = &g_fx_random_colours[(random_int() & 3) * 3 + arg0 * 12];

    *arg1 = temp_v1[0];
    *arg2 = temp_v1[1];
    *arg3 = temp_v1[2];
}
/* was func_15142A5C */
s32 obj_sub_counter_positive(struct127 *arg0) {
    u8 *temp_v0 = (u8 *)arg0->unk2D0;
    if (*(s16 *)(temp_v0 + 0x3C) > 0) {
        return 1;
    }
    return 0;
}
/* was func_15142A80 */
f32 lagrange_cubic_w0(f32 arg0) {
    return (1.0f - arg0) * (arg0 - 2.0f) * arg0 * 0.16666667f;
}
/* was func_15142AC0 */
f32 lagrange_cubic_w1(f32 arg0) {
    return (arg0 + 1.0f) * (arg0 - 1.0f) * (arg0 - 2.0f) * 0.5f;
}
/* was func_15142B04 */
f32 lagrange_cubic_w2(f32 arg0) {
    return (2.0f - arg0) * (arg0 + 1.0f) * arg0 * 0.5f;
}
/* was func_15142B44 */
f32 lagrange_cubic_w3(f32 arg0) {
    return (arg0 + 1.0f) * (arg0 - 1.0f) * arg0 * 0.16666667f;
}
/* was func_15142B7C */
Gfx *gfx_geometry_mode_cached(Gfx *gfx, s32 set, s32 clear) {
    if (~g_gfx_geom_clear_cached & clear) {
        gSPClearGeometryMode(gfx++, clear);
        g_gfx_geom_clear_cached |= clear;
    }
    if (~g_gfx_geom_set_cached & set) {
        gSPSetGeometryMode(gfx++, set);
        g_gfx_geom_set_cached |= set;
    }
    return gfx;
}
/* was func_15142C10 */
Gfx *gfx_env_color_cached(Gfx *gfx, s32 r, s32 g, s32 b, s32 a, u8 *arg5) {
    if ((r != g_gfx_env_r_cached) || (g != g_gfx_env_g_cached) || (b != g_gfx_env_b_cached) || (a != g_gfx_env_a_cached)) {
        if (*arg5 == 1) {
            gDPPipeSync(gfx++);
            *arg5 = 0;
        }
        gDPSetEnvColor(gfx++, r, g, b, a);
        g_gfx_env_r_cached = r;
        g_gfx_env_g_cached = g;
        g_gfx_env_b_cached = b;
        g_gfx_env_a_cached = a;
    }
    return gfx;
}
/* was func_15142CF0 */
Gfx *gfx_prim_color_cached(Gfx *gfx, s32 m, s32 l, s32 r, s32 g, s32 b, s32 a, u8 *arg7) {
    if ((m != g_gfx_prim_m_cached) || (l != g_gfx_prim_l_cached) || (r != g_gfx_prim_r_cached) || (g != g_gfx_prim_g_cached) || (b != g_gfx_prim_b_cached) || (a != g_gfx_prim_a_cached)) {
        if (*arg7 == 1) {
            gDPPipeSync(gfx++);
            *arg7 = 0;
        }
        gDPSetPrimColor(gfx++, m, l, r, g, b, a);
        g_gfx_prim_m_cached = m;
        g_gfx_prim_l_cached = l;
        g_gfx_prim_r_cached = r;
        g_gfx_prim_g_cached = g;
        g_gfx_prim_b_cached = b;
        g_gfx_prim_a_cached = a;
    }
    return gfx;
}
s32 sprite_load_texture_at(s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32);
s32 fx_material_tex_addr(s32, s32, s32, u8);
extern s32 g_gfx_tex_parm_a_cached; /* was D_800DD638 */
extern s32 g_gfx_tex_parm_b_cached; /* was D_800DD63C */
extern s32 g_gfx_tex_parm_c_cached; /* was D_800DD640 */
extern s32 g_gfx_tex_parm_d_cached; /* was D_800DD644 */

/* was func_15142E24 */
s32 gfx_load_texture_cached(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, s32 arg6, u8 arg7, s32 arg8, u8 *arg9, s32 argA) {
    s32 temp_v0;
    s32 temp_v0_2;

    temp_v0 = fx_material_tex_addr(arg1, arg6, arg2 >> 0x10, arg7);
    if ((temp_v0 != g_tex_cache_last_addr) || (arg3 != g_gfx_tex_parm_a_cached) || (arg4 != g_gfx_tex_parm_b_cached) || (arg5 != g_gfx_tex_parm_c_cached) || (arg8 != g_gfx_tex_parm_d_cached)) {
        if (*arg9 == 1) {
            *arg9 = 0;
        }
        if ((g_level_id == 0x18) || (g_level_id == 0x13) || (g_level_id == 6) || (g_level_id == 0x3B) || (g_level_id == 2) || (g_mp_mode_active != 0)) {
            argA = 3;
        }
        temp_v0_2 = sprite_load_texture_at(arg0, arg1, arg2 >> 8, arg8, 0, 0, 0, arg3, arg4, arg5, argA);
        g_tex_cache_last_addr = temp_v0;
        g_gfx_tex_parm_a_cached = arg3;
        g_gfx_tex_parm_b_cached = arg4;
        g_gfx_tex_parm_c_cached = arg5;
        arg0 = temp_v0_2;
        g_gfx_tex_parm_d_cached = g_gfx_tex_parm_d_cached;
    }
    return arg0;
}
/* was func_15142FBC */
Gfx *gfx_other_mode_cached(Gfx *gfx, s32 arg1, s32 arg2, u8 *arg3) {
    if ((arg1 != g_gfx_othermode_hi_cached) || (arg2 != g_gfx_othermode_lo_cached)) {
        if (*arg3 == 1) {
            gDPPipeSync(gfx++);
            *arg3 = 0;
        }
        gDPSetOtherMode(gfx++, arg1 | 0xF, arg2);
        g_gfx_othermode_hi_cached = arg1;
        g_gfx_othermode_lo_cached = arg2;
    }
    return gfx;
}
/* was func_15143044 */
s16 fx_layer_to_prim_depth(u8 arg0, s32 arg1) {
    return 0x7FFF - arg0;
}
extern s32 g_fx_tex_addrs[]; /* was D_80091914 */
extern s32 g_fx_material_tex_3; /* was D_800918C4 */
extern s32 g_emitter_ribbon_texdef; /* was D_80091960 */
/* Texture address of a material: kind (arg3) selects the source table. */
/* was func_1514306C */
s32 fx_material_tex_addr(s32 arg0, s32 arg1, s32 arg2, u8 arg3) {
    s32 v;

    switch (arg3) {
    case 1:
        v = 0;
        break;
    case 2:
        v = g_fx_tex_addrs[arg1];
        break;
    case 3:
        v = g_fx_material_tex_3;
        break;
    case 4:
        v = g_emitter_ribbon_texdef;
        break;
    case 5:
        v = arg1;
        break;
    case 6:
        v = *(s32 *)arg0;
        if ((u32)v >= 0x10000000U) {
            v = ((s32 *)v)[arg2];
        }
        break;
    default:
        v = (*(s32 **)&g_sprite_textures[arg1])[arg2];
        break;
    }
    return v;
}
/* was func_15143134 */
void mtx_transform_point_or_origin(void *arg0, void *arg1, void *arg2) {
    g_mtx_xform_dbg_step = 1;
    if ((arg0 != NULL) && ((((struct17 *)arg0)->unk0 != 0.0f) || (((struct17 *)arg0)->unk4 != 0.0f) || (((struct17 *)arg0)->unk8 != 0.0f))) {
        g_mtx_xform_dbg_step = 2;
        g_mtx_xform_dbg_x = ((struct17 *)arg0)->unk0;
        g_mtx_xform_dbg_y = ((struct17 *)arg0)->unk4;
        g_mtx_xform_dbg_z = ((struct17 *)arg0)->unk8;
        if (g_mtx_fixed_point != 0) {
            f32 mf[4][4];

            g_mtx_xform_dbg_step = 3;
            g_mtx_xform_dbg_mtx = arg2;
            guMtxL2F(mf, arg2);
            mtxf_transform_point(mf, ((struct17 *)arg0)->unk0, ((struct17 *)arg0)->unk4, ((struct17 *)arg0)->unk8,
                          &((struct17 *)arg1)->unk0, &((struct17 *)arg1)->unk4, &((struct17 *)arg1)->unk8);
            g_mtx_xform_dbg_step = 4;
        } else {
            g_mtx_xform_dbg_step = 5;
            g_mtx_xform_dbg_mtx = arg2;
            mtxf_transform_point(arg2, ((struct17 *)arg0)->unk0, ((struct17 *)arg0)->unk4, ((struct17 *)arg0)->unk8,
                          &((struct17 *)arg1)->unk0, &((struct17 *)arg1)->unk4, &((struct17 *)arg1)->unk8);
            g_mtx_xform_dbg_step = 6;
        }
    } else {
        g_mtx_xform_dbg_step = 7;
        mtx_get_translation(arg2, 0, arg1);
        g_mtx_xform_dbg_step = 8;
    }
    g_mtx_xform_dbg_step = 0;
}

/* P139 */
/*
 * spawn_region_random_point: random point inside the spawn region `rgn` (s16 centre x / y / z +0 / +2 / +4, s16
 * radius +6, s16 height +8, s16 half depth +0xA, f32 angle in degrees +0x10, shape = +0x15 & 3). Writes x, z and
 * the vertical span top / bottom:
 *   0 disc: random byte direction, random distance < radius; top = y + height, bottom = y;
 *   1 the same disc with bottom = y - height;
 *   2 box rotated by the angle (degrees * 256 / 360 as a byte; IDO f32 -> u32 conversion): random offsets
 *     in -radius..radius and -depth..depth; top = y + height, bottom = y;
 *   3 the centre line: x, z, top = y + height, bottom = y - height.
 * (angle_byte_cos = byte-angle sine; x += d * sin(a), z -= d * sin(a - 0x40).) Returns 0 (callers declare s32 or
 * void and ignore it; the asm leaves no defined value).
 */
/* was func_151432BC */
s32 spawn_region_random_point(u8 *rgn, f32 *x, f32 *z, f32 *top, f32 *bottom) {
    s16 *r = (s16 *) rgn;
    f32 c, s;
    f32 d;
    f32 u, v;
    f32 deg;
    u32 a;
    u8 ang;

    switch (rgn[0x15] & 3) {
        case 0:
            ang = random_int();
            c = angle_byte_cos((ang - 0x40) & 0xFF);
            s = angle_byte_cos(ang);
            d = random_float() * (f32) r[3];
            *x = (f32) r[0] + d * s;
            *z = (f32) r[2] - d * c;
            *top = (f32) (r[1] + r[4]);
            *bottom = (f32) r[1];
            break;
        case 1:
            ang = random_int();
            c = angle_byte_cos((ang - 0x40) & 0xFF);
            s = angle_byte_cos(ang);
            d = random_float() * (f32) r[3];
            *x = (f32) r[0] + d * s;
            *z = (f32) r[2] - d * c;
            *top = (f32) (r[1] + r[4]);
            *bottom = (f32) (r[1] - r[4]);
            break;
        case 2:
            deg = *(f32 *) (rgn + 0x10) * 0.7111111f;
            /* f32 -> u32 as IDO converts it (negative / NaN / too large -> 0xFFFFFFFF); only the low byte is used */
            if (deg >= 2147483648.0f) {
                a = (deg - 2147483648.0f < 2147483648.0f) ? ((u32) (s32) (deg - 2147483648.0f) | 0x80000000)
                                                           : 0xFFFFFFFF;
            } else if (deg > -1.0f) {
                a = (u32) (s32) deg;
            } else {
                a = 0xFFFFFFFF;
            }
            ang = a;
            c = angle_byte_cos((a - 0x40) & 0xFF);
            s = angle_byte_cos(ang);
            u = random_float() * ((f32) r[3] + (f32) r[3]) + (f32) -r[3];
            v = random_float() * ((f32) r[5] + (f32) r[5]) + (f32) -r[5];
            *x = (f32) r[0] + (u * s + v * c);
            *z = (f32) r[2] + (v * s - u * c);
            *top = (f32) (r[1] + r[4]);
            *bottom = (f32) r[1];
            break;
        default:
            *x = (f32) r[0];
            *z = (f32) r[2];
            *top = (f32) (r[1] + r[4]);
            *bottom = (f32) (r[1] - r[4]);
            break;
    }
    return 0;
}

// void spawn_region_random_point(struct208 *arg0, f32 *arg1, f32 *arg2, f32 *arg3, f32 *arg4) {
//     struct209 tmp;
//     f32 temp_f2;
//     f32 temp_f6;
//     f32 temp_ret;
//     s32 temp_t6;
//     u8 temp_a0;
//
//     temp_t6 = (arg0->unk15) & 3;
//     if (temp_t6 == 0) {
//         tmp.unk1B = random_int();
//         tmp.unk14 = angle_byte_cos((tmp.unk1B - 64) & 0xFF);
//         tmp.unk10 = angle_byte_cos(tmp.unk1B);
//         temp_ret = random_float();
//         temp_f2 = temp_ret * arg0->unk6;
//         *arg1 = (arg0->unk0 + (temp_f2 * tmp.unk10));
//         *arg2 = (arg0->unk4 - (temp_f2 * tmp.unk14));
//         *arg3 = (arg0->unk2 + arg0->unk8);
//         *arg4 = arg0->unk2;
//     } else if (temp_t6 != 1) {
//         if (temp_t6 == 2) {
//             tmp.unk2F = (u32) (arg0->unk10 * D_800A5644); // 0.7111111283302307
//             tmp.unk28 = angle_byte_cos((tmp.unk2F - 64));
//             tmp.unk24 = angle_byte_cos(tmp.unk2F);
//             tmp.unk20 = (random_float() * (2.0f * (f32) arg0->unk6)) + (f32) -(s32) arg0->unk6;
//             temp_f2 = (random_float() * (2.0f * (f32) arg0->unkA)) + (f32) -(s32) arg0->unkA;
//             temp_f6 = temp_f2 * tmp.unk24;
//             *arg1 = (arg0->unk0 + ((tmp.unk20 * tmp.unk24) + (temp_f2 * tmp.unk28)));
//             *arg2 = (arg0->unk4 + (temp_f6 - (tmp.unk20 * tmp.unk28)));
//             *arg3 = (arg0->unk2 + arg0->unk8);
//             *arg4 = arg0->unk2;
//         } else {
//             *arg1 = arg0->unk0;
//             *arg2 = arg0->unk4;
//             *arg3 = (arg0->unk2 + arg0->unk8);
//             *arg4 = (arg0->unk2 - arg0->unk8);
//         }
//     } else {
//         tmp.unkB = random_int();
//         tmp.unk4 = angle_byte_cos((tmp.unkB - 64));
//         tmp.unk0 = angle_byte_cos(tmp.unkB);
//         temp_ret = random_float();
//         temp_f2 = temp_ret * (f32) arg0->unk6;
//         *arg1 = (arg0->unk0 + (temp_f2 * tmp.unk0));
//         *arg2 = (arg0->unk4 - (temp_f2 * tmp.unk4));
//         *arg3 = (arg0->unk2 + arg0->unk8);
//         *arg4 = (arg0->unk2 - arg0->unk8);
//     }
// }


/* was func_151436B4 */
void vec3_from_angles_rad(f32 arg0, f32 arg1, f32 arg2, struct17 *arg3) {
    f32 sp24;
    f32 sp20;
    f32 sp1C;
    f32 temp_f0;
    f32 temp_f2;

    sp24 = cosf(arg0);
    sp20 = sinf(arg0);
    sp1C = cosf(arg1);
    temp_f0 = sinf(arg1);
    temp_f2 = arg2 * sp1C;
    arg3->unk0 = temp_f2 * sp20;
    arg3->unk4 = -arg2 * temp_f0;
    arg3->unk8 = temp_f2 * sp24;
}
/* was func_1514373C */
void vec2_from_angle_rad(f32 arg0, f32 arg1, f32 *arg2, f32 *arg3) {
    f32 c = cosf(arg0);
    f32 s = sinf(arg0);
    *arg2 = arg1 * s;
    *arg3 = arg1 * c;
}
/* was func_15143794 */
void vec3_from_angles_byte(s16 arg0, s16 arg1, f32 arg2, struct17 *arg3) {
    f32 sp24;
    f32 sp20;
    f32 sp1C;
    f32 temp_f0;
    f32 temp_f2;

    sp24 = angle_byte_cos(arg0);
    sp20 = angle_byte_cos(arg0 - 0x40);
    sp1C = angle_byte_cos(arg1);
    temp_f0 = angle_byte_cos(arg1 - 0x40);
    temp_f2 = arg2 * sp1C;
    arg3->unk0 = temp_f2 * sp20;
    arg3->unk4 = -arg2 * temp_f0;
    arg3->unk8 = temp_f2 * sp24;
}
/* was func_15143834 */
void vec3_from_angles_byte_w(s16 arg0, s16 arg1, f32 arg2, struct17 *arg3) {
    vec3_from_angles_byte(arg0, arg1, arg2, arg3);
}
/* was func_15143874 */
void vec2_from_angle_byte(s16 arg0, f32 arg1, f32 *arg2, f32 *arg3) {
    f32 sp1C = angle_byte_cos(arg0);
    f32 s = angle_byte_cos(arg0 - 0x40);
    *arg2 = arg1 * s;
    *arg3 = arg1 * sp1C;
}
/* was func_151438D8 */
u8 *map_marker_find(s32 arg0, s32 arg1, u16 arg2, u8 *arg3) {
    u8 *sp58;
    s32 sp34;
    s32 sp30;
    s32 sp2C;
    s32 sp28;
    s32 sp24;
    s32 sp20;
    s32 var_a0;
    s32 var_a1;
    s32 var_v0;
    u8 *temp_v1;
    u8 *temp_v1_2;
    u8 *var_t0;

    if (arg3 == NULL) {
        return NULL;
    }
    sp58 = NULL;
    clamp_range_to_bounds(&arg0, &arg1, 0, g_level_zone_count);
    var_a1 = arg0;
    var_t0 = NULL;
    if (var_a1 < arg1) {
        sp30 = arg2 & 0x80;
        sp34 = arg2 & 0x40;
        sp28 = arg2 & 0x200;
        sp2C = arg2 & 0x100;
        sp20 = arg2 & 0x1000;
        sp24 = arg2 & 0x400;
        do {
            var_v0 = 0;
            var_a0 = 0;
            if (arg2 & 1) {
                temp_v1 = g_level_zones + (var_a1 * 0x34);
                if (((*(s16 *)((u8 *)arg3 + 0)) == (*(s16 *)((u8 *)temp_v1 + 0))) && ((*(s16 *)((u8 *)arg3 + 2)) == (*(s16 *)((u8 *)temp_v1 + 2))) && ((*(s16 *)((u8 *)arg3 + 4)) == (*(s16 *)((u8 *)temp_v1 + 4)))) {
                    var_v0 = 1;
                    var_a0 = 1;
                }
            } else {
                var_v0 = 1;
            }
            if (arg2 & 2) {
                temp_v1_2 = g_level_zones + (var_a1 * 0x34);
                if (((*(s16 *)((u8 *)arg3 + 6)) == (*(s16 *)((u8 *)temp_v1_2 + 6))) && ((*(s16 *)((u8 *)arg3 + 8)) == (*(s16 *)((u8 *)temp_v1_2 + 8))) && ((*(s16 *)((u8 *)arg3 + 0xA)) == (*(s16 *)((u8 *)temp_v1_2 + 0xA)))) {
                    var_v0 = (var_v0 | 2) & 0xFFFF;
                    var_a0 = (var_a0 | 2) & 0xFFFF;
                }
            } else {
                var_v0 = (var_v0 | 2) & 0xFFFF;
            }
            if (arg2 & 4) {
                if ((*(f32 *)((u8 *)arg3 + 0xC)) == (*(f32 *)((u8 *)((g_level_zones + (var_a1 * 0x34))) + 0xC))) {
                    var_v0 = (var_v0 | 4) & 0xFFFF;
                    var_a0 = (var_a0 | 4) & 0xFFFF;
                }
            } else {
                var_v0 = (var_v0 | 4) & 0xFFFF;
            }
            if (arg2 & 8) {
                if ((*(f32 *)((u8 *)arg3 + 0x10)) == (*(f32 *)((u8 *)((g_level_zones + (var_a1 * 0x34))) + 0x10))) {
                    var_v0 = (var_v0 | 8) & 0xFFFF;
                    var_a0 = (var_a0 | 8) & 0xFFFF;
                }
            } else {
                var_v0 = (var_v0 | 8) & 0xFFFF;
            }
            if (arg2 & 0x10) {
                if ((*(u8 *)((u8 *)arg3 + 0x14)) == (*(u8 *)((u8 *)((g_level_zones + (var_a1 * 0x34))) + 0x14))) {
                    var_v0 = (var_v0 | 0x10) & 0xFFFF;
                    var_a0 = (var_a0 | 0x10) & 0xFFFF;
                }
            } else {
                var_v0 = (var_v0 | 0x10) & 0xFFFF;
            }
            if (arg2 & 0x20) {
                if ((*(u8 *)((u8 *)arg3 + 0x15)) == ((s32) (*(u8 *)((u8 *)((g_level_zones + (var_a1 * 0x34))) + 0x15)) >> 2)) {
                    var_v0 = (var_v0 | 0x20) & 0xFFFF;
                    var_a0 = (var_a0 | 0x20) & 0xFFFF;
                }
            } else {
                var_v0 = (var_v0 | 0x20) & 0xFFFF;
            }
            if (sp34 != 0) {
                if ((*(u8 *)((u8 *)arg3 + 0x16)) == (*(u8 *)((u8 *)((g_level_zones + (var_a1 * 0x34))) + 0x16))) {
                    var_v0 = (var_v0 | 0x40) & 0xFFFF;
                    var_a0 = (var_a0 | 0x40) & 0xFFFF;
                }
            } else {
                var_v0 = (var_v0 | 0x40) & 0xFFFF;
            }
            if (sp30 != 0) {
                if ((*(u8 *)((u8 *)arg3 + 0x17)) == (*(u8 *)((u8 *)((g_level_zones + (var_a1 * 0x34))) + 0x17))) {
                    var_v0 = (var_v0 | 0x80) & 0xFFFF;
                    var_a0 = (var_a0 | 0x80) & 0xFFFF;
                }
            } else {
                var_v0 = (var_v0 | 0x80) & 0xFFFF;
            }
            if (sp2C != 0) {
                if ((*(s32 *)((u8 *)arg3 + 0x18)) == (*(s32 *)((u8 *)((g_level_zones + (var_a1 * 0x34))) + 0x18))) {
                    var_v0 = (var_v0 | 0x100) & 0xFFFF;
                    var_a0 = (var_a0 | 0x100) & 0xFFFF;
                }
            } else {
                var_v0 = (var_v0 | 0x100) & 0xFFFF;
            }
            if (sp28 != 0) {
                if ((*(s32 *)((u8 *)arg3 + 0x1C)) == (*(s32 *)((u8 *)((g_level_zones + (var_a1 * 0x34))) + 0x1C))) {
                    var_v0 = (var_v0 | 0x200) & 0xFFFF;
                    var_a0 = (var_a0 | 0x200) & 0xFFFF;
                }
            } else {
                var_v0 = (var_v0 | 0x200) & 0xFFFF;
            }
            if (sp24 != 0) {
                if ((*(s32 *)((u8 *)arg3 + 0x20)) == (*(s32 *)((u8 *)((g_level_zones + (var_a1 * 0x34))) + 0x20))) {
                    var_v0 = (var_v0 | 0x400) & 0xFFFF;
                    var_a0 = (var_a0 | 0x400) & 0xFFFF;
                }
            } else {
                var_v0 = (var_v0 | 0x400) & 0xFFFF;
            }
            if (sp20 != 0) {
                if (var_v0 == 0x7FF) {
                    var_t0 = (var_a1 * 0x34) + g_level_zones;
                }
            } else if (var_a0 != 0) {
                var_t0 = (var_a1 * 0x34) + g_level_zones;
            }
            var_a1 += 1;
        } while (var_a1 != arg1);
    }
    return var_t0;
}
/* was func_15143D18 */
void clamp_range_to_bounds(s32 *arg0, s32 *arg1, s32 arg2, s32 arg3) {
    if (arg3 < arg2) {
        arg2 ^= arg3 ^= arg2 ^= arg3;
    }
    if (*arg1 < *arg0) {
        *arg0 ^= *arg1 ^= *arg0 ^= *arg1;
    }
    if (*arg0 < arg2) {
        *arg0 = arg2;
    }
    if (arg3 < *arg1) {
        *arg1 = arg3;
    }
}
/* was func_15143DA8 */
s32 clamp_int_report(s32 *arg0, s32 arg1, s32 arg2) {
    if (arg2 < arg1) {
        arg1 ^= arg2 ^= arg1 ^= arg2;
    }
    if (*arg0 < arg1) {
        *arg0 = arg1;
        return 1;
    }
    if (arg2 < *arg0) {
        *arg0 = arg2;
        return 2;
    }
    return 0;
}

/* was func_15143E08 */
s32 obj_get_yaw_byte(struct127 *arg0) {
    return (((s32) arg0->unk7A >> 8) + 64) & 0xFF;
}

/* was func_15143E24 */
s16 obj_get_local_yaw_byte(struct127 *arg0) {
    if (arg0->unk31C != NULL) {
        return (arg0->unk7A - arg0->unk31C->unk12) >> 8;
    }
    return arg0->unk7A >> 8;
}
/* was func_15143E64 */
f32 vec3_length(struct17 *arg0) {
    return sqrtf((arg0->unk0 * arg0->unk0) + (arg0->unk4 * arg0->unk4) + (arg0->unk8 * arg0->unk8));
}
extern s32 g_view_count_minus1; /* was D_800BEE08 */
/* was func_15143E94 */
u8 fx_try_camera_shake(s32 arg0, s32 arg1)
{
  u8 ret;
  s8 i;
  u8 found;
  s8 n;
  s32 found2;
  structEU_151D8E18 sp28;
  ret = 0;
  if (((!found2) && (!found2)) && (!found2)) // fakematch: dummy test of the uninitialised found2 (permuter)
  {
  }
  n = g_last_player_index + 1;
  i = 0;
  found = 0;
  while ((!found) && (i < n))
  {
    if (g_objects[i].health != 0)
    {
      found = 1;
    }
    else
    {
      i++;
    }
  }

  if (found)
  {
    i = 0;
    found2 = 0;
    while ((!found2) && (i < n))
    {
      if (trigger_test_player(i, arg1) == 0)
      {
        found2 = 1;
      }
      else
      {
        i++;
      }
    }

    if (found2)
    {
      camera_shake_start(&g_player_views[g_view_count_minus1], arg0, 1);
      sp28.unk0 = 1;
      sp28.unk2 = (random_int() & 0xF) + 20;
      sp28.unk4 = (random_int() & 3) + 4;
      sp28.unk6 = -1;
      sp28.unk5 = 1;
      rumble_request(&sp28, 0, 0xFF, 0);
      ret = 1;
    }
  }
  return ret;
}
/* was func_1514401C */
s32 sprite_anim_advance(s32 arg0, s32 *arg1, s32 *arg2, s32 arg3) {
    s32 temp_t0;
    s32 temp_t5;
    s32 temp_t5_2;
    s32 temp_t5_3;
    s32 temp_t7;
    s32 var_t1;
    s32 var_v1;

    temp_t7 = arg3 & 0xFF;
    var_v1 = 0;
    temp_t0 = (*g_sprite_anim_table[arg0 & 0xFF] << 0x10) - 1;
    temp_t5 = *arg2 + (*arg1 * g_frame_ticks);
    *arg2 = temp_t5;
    var_t1 = temp_t5;
    if (temp_t0 < temp_t5) {
        if (temp_t7 & 1) {
            var_v1 = 1;
        } else if (temp_t7 & 2) {
            *arg1 = 0;
            *arg2 = temp_t0;
        } else if (temp_t7 & 4) {
            *arg2 = temp_t0 - (var_t1 % temp_t0);
            *arg1 = -*arg1;
        } else {
            do {
                temp_t5_2 = var_t1 - temp_t0;
                *arg2 = temp_t5_2;
                var_t1 = temp_t5_2;
            } while (temp_t0 < temp_t5_2);
        }
    } else if ((var_t1 < 0) && !(temp_t7 & 8)) {
        if (temp_t7 & 0x10) {
            *arg1 = 0;
            *arg2 = 0;
        } else if (temp_t7 & 4) {
            *arg2 = (s32) -var_t1 % temp_t0;
            *arg1 = -*arg1;
        } else {
            do {
                temp_t5_3 = var_t1 + temp_t0;
                *arg2 = temp_t5_3;
                var_t1 = temp_t5_3;
            } while (temp_t5_3 < 0);
        }
    }
    return var_v1;
}
// NON-MATCHING: regalloc only (flags copy in v0, limit in t0)
// s32 sprite_anim_advance(u8 arg0, s32 *arg1, s32 *arg2, u8 arg3) {
//     s32 max;
//     s32 pos;
//     s32 ret;
//
//     ret = 0;
//     max = (g_sprite_anim_table[arg0][0] << 16) - 1;
//     *arg2 += *arg1 * g_frame_ticks;
//     pos = *arg2;
//     if (max < pos) {
//         if (arg3 & 1) {
//             ret = 1;
//         } else if (arg3 & 2) {
//             *arg1 = 0;
//             *arg2 = max;
//         } else if (arg3 & 4) {
//             *arg2 = max - (pos % max);
//             *arg1 = -*arg1;
//         } else {
//             do {
//                 pos = *arg2 = pos - max;
//             } while (max < pos);
//         }
//     } else if ((pos < 0) && !(arg3 & 8)) {
//         if (arg3 & 0x10) {
//             *arg1 = 0;
//             *arg2 = 0;
//         } else if (arg3 & 4) {
//             *arg2 = -pos % max;
//             *arg1 = -*arg1;
//         } else {
//             do {
//                 pos = *arg2 = pos + max;
//             } while (pos < 0);
//         }
//     }
//     return ret;
// }
/* was func_151441A4 */
void fx_calc_color_mode_a(s16 *arg0, s16 *arg1, s16 *arg2, s16 *arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9, u8 argA, u8 argB, u8 argC, u8 argD) {
    s16 temp_v0;
    s16 temp_v0_2;

    switch (argD) {
    case 2:
        *arg0 = (s16) arg8;
        *arg1 = (s16) arg9;
        *arg2 = (s16) argA;
        *arg3 = (s16) argB;
        return;
    case 0:
        *arg3 = 0;
        temp_v0 = *arg3;
        *arg2 = temp_v0;
        *arg1 = temp_v0;
        *arg0 = temp_v0;
        return;
    case 1:
        *arg2 = 0;
        temp_v0_2 = *arg2;
        *arg1 = temp_v0_2;
        *arg0 = temp_v0_2;
        *arg3 = (s16) argB;
        return;
    case 3:
        *arg0 = (s16) ((s32) (arg4 * argC) >> 8);
        *arg1 = (s16) ((s32) (arg5 * argC) >> 8);
        *arg2 = (s16) ((s32) (arg6 * argC) >> 8);
        *arg3 = 0;
        return;
    case 4:
        *arg0 = (s16) ((s32) (arg4 * argC) >> 8);
        *arg1 = (s16) ((s32) (arg5 * argC) >> 8);
        *arg2 = (s16) ((s32) (arg6 * argC) >> 8);
        *arg3 = 0;
        return;
    default:
        *arg0 = (s16) ((s32) (arg4 * argC) >> 8);
        *arg1 = (s16) ((s32) (arg5 * argC) >> 8);
        *arg2 = (s16) ((s32) (arg6 * argC) >> 8);
        *arg3 = 0;
        return;
    }
}
/* was func_151442FC */
void fx_calc_color_mode_b(s16 *arg0, s16 *arg1, s16 *arg2, s16 *arg3, u8 arg4, u8 arg5, u8 arg6, u8 arg7, u8 arg8, u8 arg9, u8 argA, u8 argB, u8 argC, u8 argD) {
    s16 temp_v0;
    s16 temp_v0_2;
    s16 temp_v0_3;

    switch (argD) {
    case 2:
    case 3:
        *arg0 = (s16) arg4;
        *arg1 = (s16) arg5;
        *arg2 = (s16) arg6;
        *arg3 = (s16) arg7;
        return;
    case 13:
        *arg0 = (s16) arg4;
        *arg1 = (s16) arg5;
        *arg2 = (s16) arg6;
        *arg3 = 0;
        return;
    case 0:
        *arg3 = 0;
        temp_v0 = *arg3;
        *arg2 = temp_v0;
        *arg1 = temp_v0;
        *arg0 = temp_v0;
        return;
    case 1:
        *arg2 = (s16) argC;
        *arg1 = (s16) argC;
        *arg0 = (s16) argC;
        *arg3 = 0;
        return;
    case 7:
    case 12:
        *arg2 = 0;
        temp_v0_2 = *arg2;
        *arg1 = temp_v0_2;
        *arg0 = temp_v0_2;
        *arg3 = (s16) argB;
        return;
    case 8:
        *arg2 = 0;
        temp_v0_3 = *arg2;
        *arg1 = temp_v0_3;
        *arg0 = temp_v0_3;
        *arg3 = (s16) arg7;
        return;
    case 4:
        *arg2 = (s16) argC;
        *arg1 = (s16) argC;
        *arg0 = (s16) argC;
        *arg3 = (s16) ((s32) (arg7 * argB) >> 8);
        return;
    case 5:
        *arg2 = (s16) argC;
        *arg1 = (s16) argC;
        *arg0 = (s16) argC;
        *arg3 = (s16) ((s32) (arg7 * argB) >> 8);
        return;
    case 6:
        *arg0 = (s16) arg4;
        *arg1 = (s16) arg5;
        *arg2 = (s16) arg6;
        *arg3 = (s16) argB;
        return;
    case 10:
        *arg0 = (s16) arg8;
        *arg1 = (s16) arg9;
        *arg2 = (s16) argA;
        *arg3 = (s16) argB;
        return;
    case 11:
        *arg0 = (s16) arg8;
        *arg1 = (s16) arg9;
        *arg2 = (s16) argA;
        *arg3 = (s16) arg7;
        return;
    case 9:
        *arg2 = (s16) argC;
        *arg1 = (s16) argC;
        *arg0 = (s16) argC;
        *arg3 = (s16) argB;
        return;
    default:
        *arg2 = (s16) argC;
        *arg1 = (s16) argC;
        *arg0 = (s16) argC;
        *arg3 = (s16) ((s32) (arg7 * argB) >> 8);
        return;
    }
}
/* was func_151444DC */
s32 wrap_int_range(s32 arg0, s32 arg1, s32 arg2) {
    s32 range;

    if (arg1 < arg0) {
        range = (arg1 - arg2) + 1;
        do {
            arg0 -= range;
        } while (arg1 < arg0);
    }
    if (arg0 < arg2) {
        range = (arg1 - arg2) + 1;
        do {
            arg0 += range;
        } while (arg0 < arg2);
    }
    return arg0;
}
/* was func_15144528 */
f32 wrap_float_range(f32 arg0, f32 arg1, f32 arg2) {
    while (arg1 < arg0) {
        arg0 -= arg1 - arg2;
    }
    while (arg0 < arg2) {
        arg0 += arg1 - arg2;
    }
    return arg0;
}
/* was func_15144598 */
f32 spawn_region_area(struct_eu_15144598 *arg0) {
    f32 var_f2;

    switch (arg0->unk15 & 3) {
    case 2:
        var_f2 = (arg0->unk6 * arg0->unkA) * 4.0f;
        break;
    case 0:
    case 1:
        var_f2 = (arg0->unk6 * arg0->unk6) * 3.1415927f;
        break;
    default:
        var_f2 = 1.0f;
        break;
    }
    return var_f2;
}
/* was func_1514462C */
f32 spawn_region_volume(struct_eu_15144598 *arg0) {
    f32 var_f2;

    switch (arg0->unk15 & 3) {
    case 2:
        var_f2 = arg0->unk6 * arg0->unk8 * arg0->unkA;
        break;
    case 0:
        var_f2 = (arg0->unk6 * arg0->unk6) * 3.1415927f * arg0->unk8;
        break;
    case 1:
        var_f2 = (f32)arg0->unk6 * 1.0471976f * (f32)arg0->unk6 * (f32)arg0->unk6;
        break;
    default:
        var_f2 = 1.0f;
        break;
    }
    return var_f2;
}
/* was func_1514470C */
void spawn_region_random_point_3d(u8 *arg0, u8 *arg1) {
    f32 sp94;
    f32 sp90;
    f32 sp8C;
    f32 sp88;
    f32 sp84;
    f32 sp80;
    f32 sp7C;
    f32 sp74;
    f32 sp70;
    f32 sp6C;
    f32 sp64;
    f32 sp5C;
    f32 sp58;
    f32 sp54;
    f32 sp48;
    u8 sp47;
    struct17 sp38;
    f32 sp2C;
    f32 sp28;
    f32 temp_f12;
    f32 temp_f12_2;
    f32 temp_f14;
    f32 temp_f16;
    f32 temp_f16_2;
    f32 temp_f18;
    f32 temp_f2;
    f32 temp_f2_2;
    f32 temp_f2_3;
    f32 temp_f8;
    f32 var_f6;
    s32 temp_t9;
    u8 temp_v0;

    temp_f2 = (f32) (*(s16 *)((u8 *)arg0 + 6));
    sp90 = (f32) (*(s16 *)((u8 *)arg0 + 8));
    sp88 = (*(f32 *)((u8 *)arg0 + 0x24));
    sp84 = (*(f32 *)((u8 *)arg0 + 0x28));
    temp_f18 = (f32) (*(s16 *)((u8 *)arg0 + 0xA));
    sp80 = (*(f32 *)((u8 *)arg0 + 0x2C));
    sp7C = (*(f32 *)((u8 *)arg0 + 0x30));
    temp_t9 = (*(u8 *)((u8 *)arg0 + 0x15)) & 3;
    switch (temp_t9) {                              /* irregular */
    default:
        (*(f32 *)((u8 *)arg1 + 0)) = (f32) (*(s16 *)((u8 *)arg0 + 0));
        (*(f32 *)((u8 *)arg1 + 4)) = (f32) (*(s16 *)((u8 *)arg0 + 2));
        var_f6 = (f32) (*(s16 *)((u8 *)arg0 + 4));
block_7:
        (*(f32 *)((u8 *)arg1 + 8)) = var_f6;
        return;
    case 2:
        sp8C = temp_f2;
        sp94 = temp_f18;
        temp_f14 = (random_float() * (2.0f * temp_f2)) - temp_f2;
        sp70 = temp_f14;
        temp_f16 = random_float() * sp90;
        sp74 = temp_f16;
        temp_f8 = random_float() * (2.0f * temp_f18);
        sp64 = temp_f14;
        temp_f2_2 = temp_f8 - temp_f18;
        temp_f12 = (temp_f16 * sp88) + (temp_f2_2 * sp84);
        sp6C = temp_f12;
        (*(f32 *)((u8 *)arg1 + 0)) = (f32) ((f32) (*(s16 *)((u8 *)arg0 + 0)) + ((temp_f14 * sp7C) + (temp_f12 * sp80)));
        (*(f32 *)((u8 *)arg1 + 4)) = (f32) ((f32) (*(s16 *)((u8 *)arg0 + 2)) + ((temp_f16 * sp84) - (temp_f2_2 * sp88)));
        (*(f32 *)((u8 *)arg1 + 8)) = (f32) ((f32) (*(s16 *)((u8 *)arg0 + 4)) + ((sp6C * sp7C) - (sp64 * sp80)));
        return;
    case 0:
        sp8C = temp_f2;
        sp48 = random_float() * temp_f2;
        temp_v0 = random_int();
        sp47 = temp_v0;
        sp58 = angle_byte_cos((temp_v0 - 0x40) & 0xFF) * sp48;
        temp_f16_2 = random_float() * sp90;
        sp5C = temp_f16_2;
        temp_f2_3 = angle_byte_cos(temp_v0) * sp48;
        temp_f12_2 = (temp_f16_2 * sp88) + (temp_f2_3 * sp84);
        sp54 = temp_f12_2;
        (*(f32 *)((u8 *)arg1 + 0)) = (f32) ((f32) (*(s16 *)((u8 *)arg0 + 0)) + ((sp58 * sp7C) + (temp_f12_2 * sp80)));
        (*(f32 *)((u8 *)arg1 + 4)) = (f32) ((f32) (*(s16 *)((u8 *)arg0 + 2)) + ((temp_f16_2 * sp84) - (temp_f2_3 * sp88)));
        (*(f32 *)((u8 *)arg1 + 8)) = (f32) ((f32) (*(s16 *)((u8 *)arg0 + 4)) + ((sp54 * sp7C) - (sp58 * sp80)));
        return;
    case 1:
        sp8C = temp_f2;
        sp28 = random_float();
        sp2C = random_float();
        vec3_from_angles_rad(sp28 * 6.2831855f, sp2C * 6.2831855f, random_float() * temp_f2, &sp38);
        (*(f32 *)((u8 *)arg1 + 0)) = (f32) ((f32) (*(s16 *)((u8 *)arg0 + 0)) + (*(f32 *)&(sp38)));
        (*(f32 *)((u8 *)arg1 + 4)) = (f32) ((f32) (*(s16 *)((u8 *)arg0 + 2)) + sp38.unk4);
        var_f6 = (f32) (*(s16 *)((u8 *)arg0 + 4)) + sp38.unk8;
        goto block_7;
    }
}
/* was func_15144A74 */
f32 vec3_dot(struct17 *arg0, struct17 *arg1) {
    return (arg0->unk0 * arg1->unk0) + (arg0->unk4 * arg1->unk4) + (arg0->unk8 * arg1->unk8);
}
/* was func_15144AA8 */
f32 camera_get_yaw_deg(s32 arg0) {
    f32 var_f2 = g_player_views[arg0].unk380;

    while (var_f2 > 360.0f) {
        var_f2 -= 360.0f;
    }
    while (var_f2 < 0.0f) {
        var_f2 += 360.0f;
    }
    return var_f2;
}
/* was func_15144B34 */
f32 *camera_get_pos(s32 arg0) {
    return &g_player_views[arg0].unk2F8;
}
/* was func_15144B68 */
f32 wrap_angle_rad(f32 arg0) {
    f32 var_f2;

    var_f2 = arg0;
    if (arg0 > 6.2831855f) {
        do {
            var_f2 -= 6.2831855f;
        } while (var_f2 > 6.2831855f);
    }
    if (var_f2 < 0.0f) {
        do {
            var_f2 += 6.2831855f;
        } while (var_f2 < 0.0f);
    }
    return var_f2;
}
/* was func_15144BC8 */
f32 wrap_angle_deg(f32 arg0) {
    f32 var_f2 = arg0;

    while (var_f2 > 360.0f) {
        var_f2 -= 360.0f;
    }
    while (var_f2 < 0.0f) {
        var_f2 += 360.0f;
    }
    return var_f2;
}

/* was func_15144C2C */
s32 wrap_byte_angle(s16 arg0) {
    s16 tmp1 = arg0;

    while (tmp1 >= 256)
    {
        tmp1 -= 255;
    }
    while (tmp1 < 0)
    {
        tmp1 += 255;
    }

    return tmp1;
}

/* was func_15144C8C */
f32 angle_diff_rad(f32 arg0, f32 arg1) {
    f32 tmp;

    arg0 = wrap_angle_rad(arg0);
    tmp = fabsf(arg0 - wrap_angle_rad(arg1));
    if (3.1415927f < tmp) {
        tmp = 6.2831855f - tmp;
    }
    return tmp;
}

/* P136 */
void mtxf_transform_point_w(u8 *, f32, f32, f32, f32 *, f32 *, f32 *, f32 *);
extern u8 g_cam_view_proj_mtx[]; /* per view: 4x4 f32 projection matrix (0x40 bytes); was D_800DA130 */
extern f32 g_cam_near_plane; /* was D_800D9F40 */

/*
 * world_to_screen: projects the world point pos (3 f32) with view `view`'s matrix (g_cam_view_proj_mtx + view * 0x40,
 * mtxf_transform_point_w) into scr[0..1], *oz and *ow (each out pointer may be NULL: a local is used). Fails (0) when
 * w >= 6000, w <= g_cam_near_plane or w == 0; else *oinv = 1 / w and scr becomes the viewport position: x = inv * x *
 * (half width +0x0C + 5) + centre x +0x34, y = centre y +0x38 - inv * y * (half height +0x10 + 5) of
 * g_player_cams + view * 0x180. Returns 1.
 */
/* was func_15144CEC */
s32 world_to_screen(f32 *pos, f32 *scr, f32 *oz, f32 *ow, f32 *oinv, u8 view) {
    f32 z, w, inv;
    u8 *vp;

    if (oz == NULL) {
        oz = &z;
    }
    if (ow == NULL) {
        ow = &w;
    }
    if (oinv == NULL) {
        oinv = &inv;
    }
    mtxf_transform_point_w(g_cam_view_proj_mtx + (view << 6), pos[0], pos[1], pos[2], &scr[0], &scr[1], oz, ow);
    if (*ow >= 6000.0f || *ow <= g_cam_near_plane) {
        return 0;
    }
    if (*ow == 0.0f) {
        return 0;
    }
    *oinv = 1.0f / *ow;
    vp = (u8 *) g_player_cams + view * 0x180;
    scr[0] = *oinv * (scr[0] * (*(f32 *) (vp + 0x0C) + 5.0f)) + *(f32 *) (vp + 0x34);
    vp = (u8 *) g_player_cams + view * 0x180;
    scr[1] = *(f32 *) (vp + 0x38) - *oinv * (scr[1] * (*(f32 *) (vp + 0x10) + 5.0f));
    return 1;
}
/* was func_15144E80 */
s32 tri_calc_normal(u8 *arg0, struct17 *arg1, u8 *arg2, struct17 *arg3) {
    struct {
        f32 u18;
        f32 u1C;
        f32 u20;
        f32 u24;
        f32 u28;
        f32 u2C;
        struct17 u30;
        f32 u3C;
        f32 u40;
        f32 u44;
        f32 u48;
        f32 u4C;
        f32 u50;
        f32 u54;
        f32 u58;
        f32 u5C;
    } sp;
    f32 temp_f10;
    struct17 *var_a3;

    var_a3 = arg3;
    if (var_a3 == NULL) {
        var_a3 = &sp.u30;
    }
    sp.u3C = (f32) (*(s16 *)((u8 *)arg0 + 0));
    sp.u40 = (f32) (*(s16 *)((u8 *)arg0 + 2));
    sp.u44 = (f32) (*(s16 *)((u8 *)arg0 + 4));
    temp_f10 = (f32) (*(s16 *)((u8 *)arg0 + 6));
    sp.u48 = temp_f10;
    sp.u4C = (f32) (*(s16 *)((u8 *)arg0 + 8));
    sp.u50 = (f32) (*(s16 *)((u8 *)arg0 + 0xA));
    sp.u54 = (f32) (*(s16 *)((u8 *)arg0 + 0xC));
    sp.u58 = (f32) (*(s16 *)((u8 *)arg0 + 0xE));
    sp.u5C = (f32) (*(s16 *)((u8 *)arg0 + 0x10));
    if ((sp.u3C == temp_f10) && (sp.u40 == sp.u4C) && (sp.u44 == sp.u50)) {
        return 0;
    }
    if ((sp.u3C == sp.u54) && (sp.u40 == sp.u58) && (sp.u44 == sp.u5C)) {
        return 0;
    }
    if ((sp.u48 == sp.u54) && (sp.u4C == sp.u58) && (sp.u50 == sp.u5C)) {
        return 0;
    }
    sp.u24 = sp.u3C - sp.u48;
    sp.u18 = sp.u54 - sp.u48;
    sp.u2C = sp.u44 - sp.u50;
    sp.u28 = sp.u40 - sp.u4C;
    sp.u1C = sp.u58 - sp.u4C;
    arg3 = var_a3;
    sp.u20 = sp.u5C - sp.u50;
    vec3_cross((struct17 *) &sp.u24, (struct17 *) &sp.u18, var_a3);
    vec3_cross((struct17 *) &sp.u24, arg3, arg1);
    (*(f32 *)((u8 *)arg2 + 0)) = (f32) (*(f32 *)((u8 *)(&sp.u24) + 0));
    (*(s32 *)((u8 *)arg2 + 4)) = (s32) (*(s32 *)((u8 *)(&sp.u24) + 4));
    (*(s32 *)((u8 *)arg2 + 8)) = (s32) (*(s32 *)((u8 *)(&sp.u24) + 8));
    return 1;
}
/* was func_151450B4 */
void vec3_cross(struct17 *arg0, struct17 *arg1, struct17 *arg2) {
    arg2->unk0 = arg0->unk4 * arg1->unk8 - arg0->unk8 * arg1->unk4;
    arg2->unk4 = arg0->unk8 * arg1->unk0 - arg0->unk0 * arg1->unk8;
    arg2->unk8 = arg0->unk0 * arg1->unk4 - arg0->unk4 * arg1->unk0;
}

/* was func_15145128 */
s32 vec3_normalize_len(struct17 *arg0, struct17 *arg1, f32 *arg2, f32 *arg3) {
    f32 lenSq;
    f32 sp0;

    if (arg3 == NULL) {
        arg3 = &sp0;
    }
    lenSq = (arg0->unk0 * arg0->unk0) + (arg0->unk4 * arg0->unk4) + (arg0->unk8 * arg0->unk8);
    if (lenSq == 0.0f) {
        return 0;
    }
    if (arg2 != NULL) {
        *arg2 = sqrtf(lenSq);
        *arg3 = 1.0f / *arg2;
    } else {
        *arg3 = 1.0f / sqrtf(lenSq);
    }
    arg1->unk0 = *arg3 * arg0->unk0;
    arg1->unk4 = *arg3 * arg0->unk4;
    arg1->unk8 = *arg3 * arg0->unk8;
    return 1;
}
/* was func_151451F0 */
s32 segment_sphere_hit(struct17 *arg0, struct17 *arg1, struct17 *arg2, f32 arg3, f32 arg4, s32 arg5, s32 arg6, f32 *arg7, f32 *arg8) {
    if (ray_sphere_intersect(arg0, arg1, arg2, arg3, arg5, arg6, arg7, arg8)) {
        if ((*arg7 < 0.0f) && (*arg8 < 0.0f)) {
            return 0;
        }
        if ((*arg7 >= 0.0f) && (*arg8 < 0.0f)) {
            return 1;
        }
        if (*arg7 < arg4) {
            return 1;
        }
        return 0;
    }
    return 0;
}
typedef struct { f32 x, y, z; } V3;

/* was func_151452C4 */
s32 ray_sphere_intersect(struct17 *arg0, struct17 *arg1, struct17 *arg2, f32 arg3, s32 arg4, s32 arg5, f32 *arg6, f32 *arg7) {
    f32 dx, dy, dz;
    V3 dir;
    V3 org;
    f32 b, dd, d, t, t0, t1;

    dx = arg2->unk0 - arg0->unk0;
    dy = arg2->unk4 - arg0->unk4;
    dz = arg2->unk8 - arg0->unk8;
    dir = *(V3 *)arg1;
    org = *(V3 *)arg0;
    b = dx * dir.x + dy * dir.y + dz * dir.z;
    dd = dx * dx + dy * dy + dz * dz;
    d = dd - b * b;
    if ((arg3 * arg3) < d) {
        return 0;
    }
    t = sqrtf((arg3 * arg3) - d);
    if (b < t) {
        t = -t;
    }
    t0 = b - t;
    t1 = b + t;
    ((V3 *)arg4)->x = t0 * dir.x + org.x;
    ((V3 *)arg4)->y = t0 * dir.y + org.y;
    ((V3 *)arg4)->z = t0 * dir.z + org.z;
    *arg6 = t0;
    ((V3 *)arg5)->x = t1 * dir.x + org.x;
    ((V3 *)arg5)->y = t1 * dir.y + org.y;
    ((V3 *)arg5)->z = t1 * dir.z + org.z;
    *arg7 = t1;
    {
        V3 diff;

        diff.x = ((V3 *)arg4)->x - arg0->unk0;
        diff.y = ((V3 *)arg4)->y - arg0->unk4;
        diff.z = ((V3 *)arg4)->z - arg0->unk8;
        if (vec3_dot((struct17 *)&diff, arg1) < 0.0f) {
            return 0;
        }
    }
    return 1;
}

/* was func_151454BC */
s32 camera_within_dist(u8 arg0, f32 arg1, struct17 *arg2) {
    f32 tmp1;
    f32 tmp2;
    f32 tmp3;
    struct17 *temp_v0;

    temp_v0 = camera_get_pos(arg0);
    tmp1 = arg2->unk0 - temp_v0->unk0;
    tmp2 = arg2->unk4 - temp_v0->unk4;
    tmp3 = arg2->unk8 - temp_v0->unk8;

    if ((arg1 * arg1) < ((tmp1 * tmp1) + (tmp2 * tmp2) + (tmp3 * tmp3))) {
        return 0;
    }
    return 1;
}

/* was func_15145548 */
void segment_closest_point(struct17 *arg0, struct17 *arg1, struct17 *arg2, struct17 *arg3, f32 *arg4) {
    f32 sp24;

    if (arg4 == NULL) {
        arg4 = &sp24;
    }
    if (line_closest_point(arg0, arg1, arg2, arg3, arg4)) {
        if (*arg4 < 0.0f) {
            *arg3 = *arg0;
        } else if (*arg4 > 1.0f) {
            arg3->unk0 = arg0->unk0 + arg1->unk0;
            arg3->unk4 = arg0->unk4 + arg1->unk4;
            arg3->unk8 = arg0->unk8 + arg1->unk8;
        }
    } else {
        *arg3 = *arg0;
    }
}

/* was func_1514563C */
s32 line_closest_point(struct17 *arg0, struct17 *arg1, struct17 *arg2, struct17 *arg3, f32 *arg4) {
    struct {
        f32 u10;
        u8 pad14[0xC];
    } sp;
    f32 sp0;
    f32 temp_f0;
    f32 temp_f12;
    f32 temp_f14;
    f32 temp_f2;
    f32 temp_f6;

    if (arg4 == NULL) {
        arg4 = &sp.u10;
    }
    temp_f2 = arg1->unk0;
    temp_f12 = arg1->unk4;
    temp_f14 = arg1->unk8;
    temp_f0 = (temp_f2 * temp_f2) + (temp_f12 * temp_f12) + (temp_f14 * temp_f14);
    if (temp_f0 == 0.0f) {
        return 0;
    }
    temp_f6 = (((temp_f2 * arg2->unk0) + (temp_f12 * arg2->unk4) + (temp_f14 * arg2->unk8)) - ((temp_f2 * arg0->unk0) + (temp_f12 * arg0->unk4) + (temp_f14 * arg0->unk8))) / temp_f0;
    sp0 = temp_f6;
    *arg4 = temp_f6;
    arg3->unk0 = (temp_f6 * arg1->unk0) + arg0->unk0;
    arg3->unk4 = (*arg4 * arg1->unk4) + arg0->unk4;
    arg3->unk8 = (*arg4 * arg1->unk8) + arg0->unk8;
    return 1;
}
// NON-MATCHING: t is also stored to an unused stack slot at sp+0 (frame 0x20); closest draft:
// s32 line_closest_point(struct17 *arg0, struct17 *arg1, struct17 *arg2, struct17 *arg3, f32 *arg4) {
//     f32 sp10;
//     f32 lenSq;
//     f32 dotO;
//     f32 dotP;
//     f32 t;
//
//     if (arg4 == NULL) {
//         arg4 = &sp10;
//     }
//     lenSq = (arg1->unk0 * arg1->unk0) + (arg1->unk4 * arg1->unk4) + (arg1->unk8 * arg1->unk8);
//     if (lenSq == 0.0f) {
//         return 0;
//     }
//     dotO = (arg1->unk0 * arg0->unk0) + (arg1->unk4 * arg0->unk4) + (arg1->unk8 * arg0->unk8);
//     dotP = (arg1->unk0 * arg2->unk0) + (arg1->unk4 * arg2->unk4) + (arg1->unk8 * arg2->unk8);
//     *arg4 = t = (dotP - dotO) / lenSq;
//     arg3->unk0 = (t * arg1->unk0) + arg0->unk0;
//     arg3->unk4 = (*arg4 * arg1->unk4) + arg0->unk4;
//     arg3->unk8 = (*arg4 * arg1->unk8) + arg0->unk8;
//     return 1;
// }

/* was func_15145740 */
void obj_get_aim_vectors(struct127 *arg0, s32 arg1, s32 arg2, s32 arg3, f32 arg4) {
    s16 sp3E;
    f32 sp38;
    f32 sp34;
    f32 sp30;
    f32 sp24;
    f32 sp20;
    f32 temp_f12;
    f32 temp_f12_2;
    f32 temp_f2;
    f32 temp_f6;
    s16 var_t0;
    s16 var_v1;
    struct126 *temp_v0;
    struct126 *temp_v0_2;
    u8 temp_v1;

    temp_v1 = arg0->id;
    if ((temp_v1 == 0x96) && (temp_v0 = arg0->unk31C, (temp_v0->matrix_physics != 0))) {
        var_t0 = arg0->unk7A + temp_v0->unk80;
    } else {
        temp_v0_2 = arg0->unk31C;
        if (temp_v0_2 != NULL) {
            var_t0 = arg0->unk7A - temp_v0_2->unk12;
        } else {
            var_t0 = (s16) arg0->unk7A;
        }
    }
    if ((temp_v1 == 0x96) && (arg0->unk31C->matrix_physics != 0)) {
        var_v1 = arg0->unk31C->unk82 + 0x400;
    } else {
        var_v1 = arg0->unk1D1 * 0xC8;
    }
    temp_f2 = (f32) var_v1 * 0.005493164f;
    sp38 = temp_f2;
    sp3E = var_t0;
    sp20 = temp_f2 * 0.017453292f;
    vec_from_yaw_pitch(var_t0 & 0xFFFF, 2000.0f, temp_f2, (f32 *) arg1, arg1 + 8, arg1 + 4);
    if (arg2 != 0) {
        sp3E = var_t0;
        (*(f32 *)((u8 *)arg2 + 4)) = (f32) (cosf(sp20) * 1000.0f);
        temp_f6 = sinf(sp20) * 1000.0f;
        sp30 = temp_f6;
        temp_f12 = (f32) var_t0 * 0.0000958738f;
        sp24 = temp_f12;
        (*(f32 *)((u8 *)arg2 + 0)) = (f32) (cosf(temp_f12) * sp30);
        (*(f32 *)((u8 *)arg2 + 8)) = (f32) (sinf(temp_f12) * -temp_f6);
        if (arg3 != 0) {
            temp_f12_2 = sp20 + arg4;
            sp34 = temp_f12_2;
            (*(f32 *)((u8 *)arg3 + 4)) = (f32) (cosf(temp_f12_2) * 1000.0f);
            sp30 = sinf(temp_f12_2) * 1000.0f;
            (*(f32 *)((u8 *)arg3 + 0)) = (f32) (cosf(sp24) * sp30);
            (*(f32 *)((u8 *)arg3 + 8)) = (f32) (sinf(sp24) * -sp30);
        }
    }
}
// NON-MATCHING: 90% there
// void obj_get_aim_vectors(struct127 *arg0, struct17 *arg1, struct17 *arg2, struct17 *arg3, f32 arg4) {
//     struct194 tmp;
//     f32 temp_f6;
//     s16 phi_v1;
//     s16 phi_t0;
//
//     if ((arg0->unk4 == 0x96) && ((arg0->unk31C->unk7D != 0))) {
//         phi_t0 = arg0->unk7A + arg0->unk31C->unk80;
//     } else {
//         if (arg0->unk31C != 0) {
//             phi_t0 = arg0->unk7A - arg0->unk31C->unk12;
//         } else {
//             phi_t0 = arg0->unk7A;
//         }
//     }
//     if ((arg0->unk4 == 0x96) && (arg0->unk31C->unk7D != 0)) {
//         phi_v1 = arg0->unk31C->unk82 + 1024;
//     } else {
//         phi_v1 = arg0->unk1D1 * 200;
//     }
//     tmp.unk14 = phi_t0;
//     tmp.unk10 = phi_v1 * 0.005493164f;
//     tmp.unk0 = tmp.unk10 * D_800A56B4;
//     vec_from_yaw_pitch(phi_t0, 2000.0f, tmp.unk10, &arg1->unk0, &arg1->unk8, &arg1->unk4);
//     if (arg2 != 0) {
//         arg2->unk4 = cosf(tmp.unk0) * 1000.0f;
//         temp_f6 = sinf(tmp.unk0) * 1000.0f;
//         tmp.unk8 = temp_f6;
//         tmp.unk4 = phi_t0 * D_800A56B8;
//         arg2->unk0 = cosf(tmp.unk4) * tmp.unk8;
//         arg2->unk8 = sinf(tmp.unk4) * -temp_f6;
//         if (arg3 != 0) {
//             tmp.unkC = tmp.unk0 + arg4;
//             arg3->unk4 = cosf(tmp.unkC) * 1000.0f;
//             tmp.unk8 = sinf(tmp.unkC) * 1000.0f;
//             arg3->unk0 = cosf(tmp.unk4) * tmp.unk8;
//             arg3->unk8 = sinf(tmp.unk4) * -tmp.unk8;
//         }
//     }
// }

/* was func_15145974 */
void vec3_to_yaw_pitch_deg(struct17 *arg0, f32 *arg1, f32 *arg2) {
    *arg1 = math_atan2f(arg0->unk0, arg0->unk8) * 57.295776f;
    if (arg2 != NULL) {
        *arg2 = (math_atan2f(sqrtf(arg0->unk0 * arg0->unk0 + arg0->unk8 * arg0->unk8), arg0->unk4) * 57.295776f) - 90.0f;
    }
}

/* was func_15145A0C */
f32 curve_table_lookup(f32 arg0, f32 arg1, f32 arg2) {
    return g_curve_table[(s32)(arg0 * arg2 * 100.0f)] * arg1;
}


/* was func_15145A50 */
void obj_set_destroyed(struct127 *arg0) {
    arg0->unk5 = 3;
    if (g_level_id != 51) {
        if ((g_mp_mode_active != 0) || (arg0->interaction_state == 5) || (arg0->interaction_state == 1) || (arg0->interaction_state == 21)) {
            arg0->interaction_state = 5;
            if (arg0->unk31C != NULL) {
                arg0->unk31C->unk78 = 0;
            }
        } else {
            obj_set_dead_fading(arg0);
        }
    }
}

void obj_get_fx_point_a(u8 *, f32 *, f32 *, f32 *);

/* was func_15145AD8 */
s32 ray_obj_ellipsoid_hit(u8 *arg0, u8 *arg1, u8 *arg2, s32 arg3, s32 arg4, f32 *arg5, f32 *arg6, s32 *arg7) {
    struct {
        f32 u38;
        f32 u3C;
        f32 u40;
        f32 u44;
        f32 u48;
        f32 u4C;
        f32 u50;
        f32 u54;
        f32 u58;
        f32 u5C;
        f32 u60;
        f32 u64;
        f32 u68;
        f32 u6C;
        f32 u70;
        f32 u74;
        f32 u78;
        s32 u7C;
    } sp;
    s32 *var_s0;
    f32 *var_a3;
    f32 temp_f0;

    if (arg5 != NULL) {
        arg5 = &sp.u78;
    }
    var_a3 = arg6;
    var_s0 = arg7;
    if (var_a3 != NULL) {
        var_a3 = &sp.u74;
    }
    if (var_s0 != NULL) {
        var_s0 = &sp.u7C;
    }
    arg6 = var_a3;
    obj_get_fx_point_a(arg2, var_s0, arg5, var_a3);
    if (*arg6 == 0.0f) {
        return 0;
    }
    if (*arg5 == 0.0f) {
        return 0;
    }
    temp_f0 = (*(f32 *)((u8 *)arg2 + 0xDC));
    sp.u3C = (*(f32 *)((u8 *)arg2 + 0xE0));
    sp.u68 = (*(f32 *)((u8 *)arg0 + 0));
    sp.u6C = (*(f32 *)((u8 *)arg0 + 4)) * temp_f0;
    sp.u70 = (*(f32 *)((u8 *)arg0 + 8));
    sp.u5C = (*(f32 *)((u8 *)arg1 + 0));
    sp.u60 = (*(f32 *)((u8 *)arg1 + 4)) * temp_f0;
    sp.u64 = (*(f32 *)((u8 *)arg1 + 8));
    sp.u40 = temp_f0;
    if (vec3_normalize_len((struct17 *) &sp.u5C, (struct17 *) &sp.u5C, &sp.u4C, &sp.u38) == 0) {
        return 0;
    }
    sp.u50 = (*(f32 *)((u8 *)var_s0 + 0));
    sp.u54 = (*(f32 *)((u8 *)var_s0 + 4)) * sp.u40;
    sp.u58 = (*(f32 *)((u8 *)var_s0 + 8));
    if (segment_sphere_hit((struct17 *) &sp.u68, (struct17 *) &sp.u5C, (struct17 *) &sp.u50, *arg5, sp.u4C, arg3, arg4, &sp.u48, &sp.u44) == 0) {
        return 0;
    }
    (*(f32 *)((u8 *)arg3 + 4)) = (f32) ((*(f32 *)((u8 *)arg3 + 4)) * sp.u3C);
    (*(f32 *)((u8 *)arg4 + 4)) = (f32) ((*(f32 *)((u8 *)arg4 + 4)) * sp.u3C);
    return 1;
}
/* was func_15145C90 */
u8 prop_is_flagged(s32 arg0) {
    if (arg0 < 0) {
        return 1;
    } else {
        return (g_world_objs[arg0].unk6F & 0x80) == 0x80;
    }
}

/* was func_15145CD0 */
void xform_points_ptrs(struct_eu_xform *arg0, struct17 **arg1, struct17 **arg2, s32 arg3) {
    f32 mf[4][4];
    s32 i;

    mtxf_rotate_xyz_deg(mf, arg0->unk0, arg0->unk4, arg0->unk8);
    mf[3][0] = arg0->unk10;
    mf[3][1] = arg0->unk12;
    mf[3][2] = arg0->unk14;
    for (i = 0; arg3 > 0; arg3--, i++) {
        mtxf_transform_point(mf, arg1[i]->unk0, arg1[i]->unk4, arg1[i]->unk8, &arg2[i]->unk0, &arg2[i]->unk4, &arg2[i]->unk8);
    }
}
/* was func_15145DB4 */
void xform_points_array(struct_eu_xform *arg0, struct17 *arg1, struct17 *arg2, s32 arg3) {
    f32 mf[4][4];
    s32 i;

    mtxf_rotate_xyz_deg(mf, arg0->unk0, arg0->unk4, arg0->unk8);
    mf[3][0] = arg0->unk10;
    mf[3][1] = arg0->unk12;
    mf[3][2] = arg0->unk14;
    for (i = 0; arg3 > 0; arg3--, i++) {
        mtxf_transform_point(mf, arg1[i].unk0, arg1[i].unk4, arg1[i].unk8, &arg2[i].unk0, &arg2[i].unk4, &arg2[i].unk8);
    }
}

/* was func_15145EA4 */
void mtx_transform_points(f32 **arg0, f32 **arg1, Mtx *arg2, s32 arg3) {
    f32 **p;
    f32 mtx[4][4];
    f32 **q;
    f32 *v;
    f32 *o;

    if (g_mtx_fixed_point != 0) {
        guMtxL2F(mtx, arg2);
        if (arg3 > 0) {
            p = arg0;
            q = arg1;
            do {
                v = *p;
                if (!arg3) {} // fakematch: extends arg3's live range (count in s1, not s2)
                if ((v != NULL) && ((v[0] != 0.0f) || (v[1] != 0.0f) || (v[2] != 0.0f))) {
                    o = *q;
                    mtxf_transform_point(mtx, v[0], v[1], v[2], o, o + 1, o + 2);
                } else {
                    mtx_get_translation(arg2, 0, *q);
                }
                arg3--;
                p++;
                q++;
            } while (arg3 > 0);
        }
    } else {
        if (arg3 > 0) {
            p = arg0;
            q = arg1;
            do {
                v = *p;
                if ((v != NULL) && ((v[0] != 0.0f) || (v[1] != 0.0f) || (v[2] != 0.0f))) {
                    o = *q;
                    mtxf_transform_point((f32 (*)[4]) arg2, v[0], v[1], v[2], o, o + 1, o + 2);
                } else {
                    mtx_get_translation(arg2, 0, *q);
                }
                arg3--;
                p++;
                q++;
            } while (arg3 > 0);
        }
    }
}
/* P142 */
// plane_axes_from_normal: builds two unit axes spanning the plane with normal n (a: in-plane axis, b = a x n,
// then a = b x n). Returns 0 for a zero normal, else 1. An axis-aligned normal (two zero components) gets fixed
// unit axes; otherwise a = (1, ..) with a[j] chosen so that the in-plane condition holds, then both are normalised.
/* was func_15146078 */
s32 vec3_make_basis(f32 *n, f32 *a, f32 *b) {
    f32 len;
    f32 scale;
    s32 zeros;
    s32 nonzero;
    s32 zero;
    s32 i;
    s32 j;

    if (n[0] == 0.0f && n[1] == 0.0f && n[2] == 0.0f) {
        return 0;
    }
    // count the zero components; remember the last zero and the last nonzero index
    zeros = 0;
    nonzero = 0;
    zero = 0;
    if (n[0] == 0.0f) {
        zeros++;
        zero = 0;
    } else {
        nonzero = 0;
    }
    if (n[1] == 0.0f) {
        zeros++;
        zero = 1;
    } else {
        nonzero = 1;
    }
    if (n[2] == 0.0f) {
        zeros++;
        zero = 2;
    } else {
        nonzero = 2;
    }
    if (zeros == 2) {
        // normal along one axis: take the other two unit axes
        switch (nonzero) {
            case 0:
                a[0] = 0.0f;
                a[2] = 0.0f;
                a[1] = 1.0f;
                b[0] = 0.0f;
                b[1] = 0.0f;
                b[2] = 1.0f;
                break;
            case 1:
                a[1] = 0.0f;
                a[2] = 0.0f;
                a[0] = 1.0f;
                b[0] = 0.0f;
                b[1] = 0.0f;
                b[2] = 1.0f;
                break;
            case 2:
                a[1] = 0.0f;
                a[2] = 0.0f;
                a[0] = 1.0f;
                b[0] = 0.0f;
                b[2] = 0.0f;
                b[1] = 1.0f;
                break;
        }
        return 1;
    }
    i = 1;
    j = 2;
    if (zeros == 1 && zero == 2) {
        i = 2;
        j = 1;
    }
    a[0] = 1.0f;
    a[i] = 1.0f;
    a[j] = -n[0] - n[i] / n[j];
    vec3_cross((struct17 *) a, (struct17 *) n, (struct17 *) b);
    vec3_cross((struct17 *) b, (struct17 *) n, (struct17 *) a);
    vec3_normalize_len((struct17 *) a, (struct17 *) a, &len, &scale);
    vec3_normalize_len((struct17 *) b, (struct17 *) b, &len, &scale);
    return 1;
}
u8 *light_write_light_cmds(u8 *, s32, u8, u8, u8 *);
u8 *light_apply_object_lights(u8 *, s16, s32, s32, s32, s32, s32, s32, u8 *, u8 *, s32, s32, s32, s32);
extern s32 g_player_light_bufs[]; /* was D_800DA230 */
extern u8 g_light_buf_size; /* was D_800DA240 */
extern u8 g_light_count; /* was D_800DA241 */
extern u8 g_player_ambient_lights[]; /* was D_800D9FF0 */
/* Lights of a model part (arg1: +0x00 count, +0x04 out list, +0x08 per-player light buffers, +0x18 lookat,
 * +0x1C mask). kind (arg2) 1: the object's own light set (arg3 +0x301 / +0x302 / +0x304 / +0x314) when it is
 * alive and in room arg4, else (2) the level's default lights; other kinds: the nearest point lights at arg6. */
/* was func_151462C8 */
u8 *model_part_emit_lights(u8 *gfx, u8 *arg1, u8 arg2, u8 *arg3, u8 arg4, s16 arg5, f32 *arg6, u8 arg7, s32 arg8) {
    s32 buf = *(s32 *)(arg1 + 8 + arg5 * 4);
    s32 lookat;
    s32 kind;
    s32 flags;

    if (buf == 0) {
        return gfx;
    }
    lookat = *(s32 *)(arg1 + 0x18);
    if (lookat == 0) {
        return gfx;
    }
    kind = arg2;
    if (arg2 == 1) {
        if (arg3 == NULL) {
            kind = 0;
        } else if ((*(s32 *)arg3 != 0) && (arg4 == arg3[0x3B]) && (arg3[4] != 0xFF) && (arg3[0x302] != 0)) {
            kind = 1;
        } else {
            kind = 2;
        }
    }
    if (kind == 1) {
        return light_write_light_cmds(gfx, *(s32 *)(arg3 + 0x304 + arg5 * 4), arg3[0x301], arg3[0x302], *(u8 **)(arg3 + 0x314));
    }
    if (kind == 2) {
        return light_write_light_cmds(gfx, g_player_light_bufs[arg5], g_light_buf_size, g_light_count, g_player_ambient_lights + arg5 * 16 + g_dl_buf_index * 8);
    }
    flags = ((arg7 & 2) ? 0x10 : 0) | 8 | ((arg7 & 1) ? 2 : 0);
    return light_apply_object_lights(gfx, arg5, (s32)arg6[0], (s32)arg6[1], (s32)arg6[2], arg8, buf, *(s32 *)arg1, (u8 *)lookat,
                         arg1 + 4, *(s32 *)(arg1 + 0x1C), 0, flags, 0);
}
/* was func_151464B8 */
u8 player_mask_hides_all(s16 *arg0) {
    s32 i;
    s16 mask;

    for (i = 0, mask = 0; i <= g_last_player_index; i++) {
        mask |= 1 << i;
    }
    return !(arg0[1] & mask);
}

/* was func_15146508 */
void obj_broadcast_replace(struct127 *arg0, struct127 *arg1) {
    struct193 tmp;

    tmp.unk0 = arg0;
    tmp.unk4 = arg1;
    tmp.unk8 = arg0->unique_id;
    tmp.unk9 = arg1->unique_id;
    node_broadcast_all(&tmp, 45, arg0, arg1);
}

/* P136 */
u8 *attachment_find_by_slot(u8 *, u16, s32);
s32 attachment_get_matrices(u8 *, u8 *, Mtx **, s32 *);

/*
 * model_node_points_to_world: transforms n local points (in[i] -> out[i], 3 f32 each) by the matrix of node `node`
 * of a model instance obj (obj +0x1D4 = its matrix array, required). The matrix comes from, in order: the node's
 * attached instance (+0x48: its frame matrix array +0x3E8[g_dl_buf_index] + idx * 0x40, 0 when that instance is not
 * ready (+0x3F6)); a sub-model (+0x1E id, attachment_find_by_slot / attachment_get_matrices, entry +0x20 when that model is
 * skinned (+0x48)); the node's own frame matrices (+0x34 + g_dl_buf_index * 0x40); else mtx_transform_points with obj's
 * matrix + node byte +2 * 0x40. Mtx (s15.16) -> float with guMtxL2F, points with mtxf_transform_point.
 * Returns 1, or 0 when something is missing.
 */
/* was func_1514654C */
s32 model_node_points_to_world(u8 *obj, u8 *node, s32 idx, f32 **in, f32 **out, s32 n) {
    f32 mf[4][4];
    Mtx *mtx;
    s32 unused;
    u8 *sub;
    u8 *att;
    s32 i;

    if (obj == NULL || node == NULL || *(s32 *) (obj + 0x1D4) == 0) {
        return 0;
    }
    att = *(u8 **) (node + 0x48);
    if (att != NULL) {
        if (att[0x3F6] == 0) {
            return 0;
        }
        mtx = (Mtx *) (((u8 **) (att + 0x3E8))[g_dl_buf_index] + (idx << 6));
    } else if (*(u16 *) (node + 0x1E) != 0) {
        sub = attachment_find_by_slot(obj, *(u16 *) (node + 0x1E), 0);
        if (sub == NULL) {
            return 0;
        }
        if (attachment_get_matrices(sub, obj, &mtx, &unused) == 0) {
            return 0;
        }
        if (*(s32 *) (sub + 0x48) != 0) {
            mtx = (Mtx *) ((u8 *) mtx + (*(u16 *) (node + 0x20) << 6));
        }
    } else if (*(u8 **) (node + 0x34) != NULL) {
        mtx = (Mtx *) (*(u8 **) (node + 0x34) + (g_dl_buf_index << 6));
    } else {
        mtx_transform_points(in, out, (Mtx *) (*(u8 **) (obj + 0x1D4) + (node[2] << 6)), n);
        return 1;
    }
    if (mtx == NULL) {
        return 0;
    }
    guMtxL2F(mf, mtx);
    for (i = 0; i < n; i++) {
        mtxf_transform_point(mf, in[i][0], in[i][1], in[i][2], &out[i][0], &out[i][1], &out[i][2]);
    }
    return 1;
}

/* was func_1514672C */
s32 pos_in_world_bounds(u8 *arg0) {
    f32 temp_f0;

    if ((fabsf((*(f32 *)((u8 *)arg0 + 0))) > 19500.0f) || (fabsf((*(f32 *)((u8 *)arg0 + 8))) > 19500.0f) || (temp_f0 = (*(f32 *)((u8 *)arg0 + 4)), (temp_f0 > 19500.0f)) || (temp_f0 < -9500.0f)) {
        return 0;
    }
    return 1;
}
// NON-MATCHING: JUSTREG: first 3 statements are out of order
// s32 pos_in_world_bounds(struct17 *arg0) {
//     if ((D_800A56C4 < fabsf(arg0->unk0)) || (D_800A56C4 < fabsf(arg0->unk8)) || (D_800A56C4 < arg0->unk4) || (arg0->unk4 < D_800A56C8)) {
//         return 0;
//     } else {
//         return 1;
//     }
// }

/* was func_151467A4 */
void fx_random_flicker_update(f32 *arg0, f32 arg1, f32 *arg2, f32 arg3, f32 arg4, f32 arg5, f32 arg6, f32 *arg7) {
    *arg0 = *arg0 - g_frame_step_f;
    if (*arg0 < 0.0f) {
        *arg0 = random_float() * arg1;
        if ((random_int() & 3) != 0) {
            *arg2 = (random_float() * (arg4 - arg3)) + arg3;
        } else {
            *arg2 = (random_float() * (arg5 - arg4)) + arg4;
        }
    }
    *arg7 = ((*arg2 - *arg7) * arg6) + *arg7;
}
