#include <ultra64.h>
#include "functions.h"
#include "variables.h"


extern f32 g_area_emitter_rate_base; /* was D_800A1940 */
extern f32 g_area_emitter_rate_range; /* was D_800A1944 */
u8 player_mask_hides_all(s32);
s32 spawn_region_random_point(s32, f32 *, f32 *, f32 *, f32 *);

/* was func_150ECAA0 */
void fx_area_emitter_update(u8 *arg0) {
    struct260 *temp_v0;
    struct {
        f32 x;
        f32 y;
        f32 z;
        f32 w;
    } tmp;
    f32 sp68;
    f32 *v;

    if (player_mask_hides_all(*(s32 *)(arg0 + 0x30)) != 0) {
        return;
    }
    v = (f32 *)(arg0 + 0x28);
    v[3] += (g_area_emitter_rate_base + random_float() * g_area_emitter_rate_range) * v[1] * g_frame_step_f;
    if (v[3] > 1.0f) {
        tmp.w = 0.0f;
        do {
            spawn_region_random_point(*(s32 *)v, &tmp.x, &tmp.z, &sp68, &tmp.y);
            temp_v0 = effect_node_create((random_int() % 131U) + 80, -1, 0x5A, -1, 1, 0, 0x10, arg0[0xC], arg0[1]);
            if (temp_v0 != NULL) {
                memcpy((u8 *)temp_v0 + 0x28, &tmp, 0x10);
            }
            v[3] -= 1.0f;
        } while (v[3] > 1.0f);
    }
}

s32 particle_spawn_ex(s32 arg0, u8 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5);

/* was func_150ECC30 */
void fx_point_particle_emitter_update(u8 *arg0) {
    struct {
        s8 u8C;
        s8 u8D;
        s8 u8E;
        s8 u8F;
        f32 u90;
        f32 u94;
        f32 u98;
        s32 u9C;
        s32 uA0;
        s16 uA4;
        s16 uA6;
        s32 uA8;
        s32 uAC;
        s8 uB0;
        s8 uB1;
        s8 uB2;
        s8 uB3;
        s8 uB4;
        s8 uB5;
        s8 uB6;
        s8 uB7;
        s8 uB8;
        s8 uB9;
        s16 uBA;
        s16 uBC;
        s16 uBE;
        f32 uC0;
        f32 uC4;
        f32 uC8;
        s32 uCC;
        u8 padD0[0x8];
        f32 uD8;
        f32 uDC;
        f32 uE0;
        f32 uE4;
        f32 uE8;
        f32 uEC;
        f32 uF0;
        s32 uF4;
        u8 padF8[0x4];
        s8 uFC;
        s8 uFD;
        s8 uFE;
        s8 uFF;
        s8 u100;
        s8 u101;
    } sp;
    f32 temp_f10;
    f32 temp_f6;
    s32 temp_v0;
    s32 var_s0;
    s32 var_v0;
    u8 *temp_s1;

    temp_s1 = arg0 + 0x28;
    (*(f32 *)((u8 *)temp_s1 + 0xC)) = (f32) ((*(f32 *)((u8 *)temp_s1 + 0xC)) + ((1352.0f + (random_float() * 1698.0f)) * 0.0001f * g_frame_step_f));
    if ((*(f32 *)((u8 *)temp_s1 + 0xC)) > 1.0f) {
        sp.uB9 = 0x6C;
        sp.uA4 = 0x5103;
        sp.u9C = 0x200005;
        sp.uBA = 0x46;
        sp.uBC = 3;
        sp.uF4 = 0x80DE07;
        sp.uFC = 8;
        sp.uFD = 6;
        sp.u8C = 0;
        sp.u8D = 0;
        sp.uA0 = 0;
        sp.uA8 = 0;
        sp.uAC = 0;
        sp.uFE = 0x16;
        sp.uFF = -1;
        sp.u100 = -1;
        sp.u101 = 0;
        sp.uBE = 0x46;
        sp.uB0 = 0x47;
        sp.uB1 = 0xC2;
        sp.uB2 = 0;
        sp.uB3 = 0xFF;
        sp.uB4 = 0xC0;
        sp.uB5 = 0x49;
        sp.uB6 = 0;
        sp.uB8 = 0xFF;
        sp.u98 = 0.97047f;
        sp.uC0 = 1.021029f;
        (*(s32 *)((u8 *)(&sp.uCC) + 0)) = (s32) (*(s32 *)((u8 *)temp_s1 + 0));
        (*(s32 *)((u8 *)(&sp.uCC) + 4)) = (s32) (*(s32 *)((u8 *)temp_s1 + 4));
        (*(s32 *)((u8 *)(&sp.uCC) + 8)) = (s32) (*(s32 *)((u8 *)temp_s1 + 8));
        sp.uD8 = 0.0f;
        sp.uDC = 0.0f;
        sp.uE0 = 0.0f;
        sp.uE4 = 0.0f;
        sp.uE8 = 0.0f;
        sp.uEC = 0.0f;
        do {
            sp.u8E = (random_int() % 5U) + 4;
            sp.u8F = (random_int() % 5U) + 4;
            sp.u90 = random_float() * 11.0f;
            sp.u94 = random_float() * 11.0f;
            temp_f10 = random_float() * 0.172f;
            sp.uF4 &= ~0xC0;
            sp.uF0 = temp_f10 + 0.098000005f;
            var_s0 = 0;
            if (random_int() & 1) {
                var_s0 = 0x80;
            }
            if (random_int() & 1) {
                var_v0 = 0x40;
            } else {
                var_v0 = 0;
            }
            sp.uF4 |= var_v0 | var_s0;
            sp.uB7 = (random_int() % 101U) + 0x64;
            sp.uA6 = (random_int() % 51U) + 0x50;
            temp_f6 = (random_float() * 80.0f) + 92.0f;
            sp.uC8 = temp_f6;
            sp.uC4 = temp_f6;
            temp_v0 = particle_spawn_ex(&sp.u9C, 0, 0, 0x10, (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
            if (temp_v0 != 0) {
                memcpy(temp_v0 + 0xA8, &sp.u8C, 0x10);
            }
            (*(f32 *)((u8 *)temp_s1 + 0xC)) = (f32) ((*(f32 *)((u8 *)temp_s1 + 0xC)) - 1.0f);
        } while ((*(f32 *)((u8 *)temp_s1 + 0xC)) > 1.0f);
    }
}
/* was func_150ECFE8 */
void obj_tint_fx_spawn(u8 *arg0, u8 arg1, u8 arg2, u8 arg3, u8 arg4, u8 arg5, s16 arg6, u8 arg7, s32 arg8) {
    struct {
        u8 *unk0;
        u8 unk4;
        u8 unk5;
        u8 unk6;
        u8 unk7;
        u8 unk8;
        u8 unk9;
        u8 padA[2];
    } tmp;
    struct260 *temp_v0;

    tmp.unk0 = arg0;
    tmp.unk4 = arg0[0x3B];
    tmp.unk5 = arg1;
    tmp.unk6 = arg2;
    tmp.unk7 = arg3;
    tmp.unk8 = arg4;
    tmp.unk9 = arg5;
    temp_v0 = effect_node_create((arg6 == -1) ? 300 : arg6, -1, 0x5D, -1, (arg6 == -1) ? 0 : 1, 0x45, 0xC, arg7, arg8);
    if (temp_v0 != NULL) {
        memcpy((u8 *)temp_v0 + 0x28, &tmp, 0xC);
    }
}

/* was func_150ED0CC */
void obj_tint_fx_on_message(u8 *arg0, s32 arg1, u8 arg2) {
    node_handle_link_message(arg1, arg2, arg0 + 0x28, arg0 + 0x2C, arg0);
}

void obj_tint_set_flash(u8 *, s32, s32, s32, s32, s32, s32);

/* was func_150ED10C */
void obj_tint_fx_update(u8 *arg0) {
    u8 *sp28;
    u8 *temp_t6;
    u8 *temp_v0;

    temp_t6 = (*(u8 **)((u8 *)arg0 + 0x28));
    temp_v0 = arg0 + 0x28;
    sp28 = temp_t6;
    if (((*(s32 *)temp_t6) == 0) || ((*(u8 *)((u8 *)temp_v0 + 4)) != (*(u8 *)((u8 *)temp_t6 + 0x3B)))) {
        (*(s16 *)((u8 *)arg0 + 0xE)) = -1;
        return;
    }
    obj_tint_set_flash(sp28, (*(u8 *)((u8 *)temp_v0 + 5)), (*(u8 *)((u8 *)temp_v0 + 6)), (*(u8 *)((u8 *)temp_v0 + 7)), (s32) (*(u8 *)((u8 *)temp_v0 + 8)), 0, (s32) (*(u8 *)((u8 *)temp_v0 + 9)));
}

void obj_tint_fx_spawn(u8 *, u8, u8, u8, u8, u8, s16, u8, s32);
s32 object_explode_air_burst(struct127 *, u8, s32);

/* was func_150ED180 */
void obj_hit_green_tint(s32 arg0, u8 arg1, s32 arg2) {
    object_explode_air_burst(arg0, arg1, arg2);
    obj_tint_fx_spawn((u8 *)arg0, 0, 0xFF, 0, 0xFF, 4, -1, arg1, arg2);
}

s32 event_dispatch(s32, s32, ...);
void math_spring_approach(f32 *, f32, f32 *, f32, f32, f32);
extern f32 g_map_tint_r; /* current tint r, g, b; was D_80088E70 */
extern f32 g_map_tint_g; /* was D_80088E74 */
extern f32 g_map_tint_b; /* was D_80088E78 */
extern f32 g_map_tint_target_r; /* target tint r, g, b; was D_80088E7C */
extern f32 g_map_tint_target_g; /* was D_80088E80 */
extern f32 g_map_tint_target_b; /* was D_80088E84 */
extern f32 g_map_tint_vel_r; /* approach speeds; was D_80088E88 */
extern f32 g_map_tint_vel_g; /* was D_80088E8C */
extern f32 g_map_tint_vel_b; /* was D_80088E90 */

/* IDO's f32 -> u32 conversion: <= -1, >= 2^32 and NaN give 0xFFFFFFFF (undefined in C, wasm traps) */
#define TINT_F2U(f) ((!((f) > -1.0f) || (f) >= 4294967296.0f) ? 0xFFFFFFFFU : (u32) (f))

// object_update_option_tint: reads the option flags (0x403B tint on, 0x4038..0x403A which channel drops to 128,
// 0x4010 with the 0x2007 settings block) into the object's flags (+0x84), mode (+0x134) and value (+0x190), sends
// the 0x9000 parameters, then moves the global tint toward its target and sends it as 3 bytes (0x30F3..0x30F5).
/* was func_150ED1F0 */
void camera_update_map_tint(u8 *obj) {
    s32 block;
    s32 v;
    s32 hi;
    s32 lo;

    if (event_dispatch(1, 0x403B, 6, 0x2000) == 0) {
        g_map_tint_target_r = 255.0f;
        g_map_tint_target_g = 255.0f;
        g_map_tint_target_b = 255.0f;
        event_dispatch_alt(0, 0x4031, 0);
        event_dispatch_alt(0, 0x4032, 0);
        event_dispatch_alt(0, 0x4033, 0);
        *(u32 *) (obj + 0x84) &= 0x7FFDEDFF;
        *(u32 *) (obj + 0x84) |= 8;
    } else {
        event_dispatch_alt(0, 0x4031, 1);
        event_dispatch_alt(0, 0x4032, 1);
        event_dispatch_alt(0, 0x4033, 1);
        *(u32 *) (obj + 0x84) |= 0x80021200;
        if (event_dispatch(1, 0x4038, 6, 0x2000) != 0) {
            g_map_tint_target_r = 128.0f;
            g_map_tint_target_g = 255.0f;
            g_map_tint_target_b = 255.0f;
        } else if (event_dispatch(1, 0x4039, 6, 0x2000) != 0) {
            g_map_tint_target_r = 255.0f;
            g_map_tint_target_g = 128.0f;
            g_map_tint_target_b = 255.0f;
        } else if (event_dispatch(1, 0x403A, 6, 0x2000) != 0) {
            g_map_tint_target_r = 255.0f;
            g_map_tint_target_g = 255.0f;
            g_map_tint_target_b = 128.0f;
        } else {
            g_map_tint_target_r = 255.0f;
            g_map_tint_target_g = 255.0f;
            g_map_tint_target_b = 255.0f;
        }
        block = event_dispatch(0, 0x2007, 0xB7) | 0x2000;
        if (event_dispatch(1, 0x4010, 6, 0x2000) == 0) {
            *(s32 *) (obj + 0x134) = 0;
            *(f32 *) (obj + 0x190) = 0.0f;
            return;
        }
        if (block == 0) { /* never true (bit 0x2000 is set), kept from the asm */
            return;
        }
        *(s32 *) (obj + 0x134) = 1;
        event_dispatch_alt(1, 0x9000, 0x17, event_dispatch(1, block, 0x9C, 0x2000));
        v = event_dispatch(1, block, 0x9A, 0x2000);
        hi = v;
        lo = v >> 1;
        if (v < 0x384) {
            hi = 0x384;
        } else if (v >= 0x4A7) {
            hi = 0x4A6;
        }
        if (lo < 0xB4) {
            lo = 0xB4;
        } else if (lo >= 0xE8) {
            lo = 0xE7;
        }
        event_dispatch_alt(2, 0x9000, 8, hi, lo);
        *(f32 *) (obj + 0x190) = 220.0f;
    }
    math_spring_approach(&g_map_tint_r, g_map_tint_target_r, &g_map_tint_vel_r, 4.0f, 6.0f, *(f32 *) (obj + 0x7B4));
    math_spring_approach(&g_map_tint_g, g_map_tint_target_g, &g_map_tint_vel_g, 4.0f, 6.0f, *(f32 *) (obj + 0x7B4));
    math_spring_approach(&g_map_tint_b, g_map_tint_target_b, &g_map_tint_vel_b, 4.0f, 6.0f, *(f32 *) (obj + 0x7B4));
    event_dispatch_alt(1, 0x30F3, 0x12, (u8) TINT_F2U(g_map_tint_r));
    event_dispatch_alt(1, 0x30F4, 0x12, (u8) TINT_F2U(g_map_tint_g));
    event_dispatch_alt(1, 0x30F5, 0x12, (u8) TINT_F2U(g_map_tint_b));
}
