#include <ultra64.h>
#include "functions.h"
#include "variables.h"


s32 particle_spawn_ex(s32 arg0, u8 arg1, s32 arg2, s32 arg3, u8 arg4, s32 arg5);
void vec2_from_angle_rad(f32, f32, f32 *, f32 *);
s32 memcpy(s32, f32 *, s32);

/* was func_eu_15108850 */
void area_sparkle_emitter_update(u8 *arg0) {
    struct {
        f32 u80;
        f32 u84;
        f32 u88;
        f32 u8C;
        f32 u90;
        s32 u94;
        s32 u98;
        s16 u9C;
        s16 u9E;
        s32 uA0;
        s32 uA4;
        s8 uA8;
        s8 uA9;
        s8 uAA;
        s8 uAB;
        s8 uAC;
        s8 uAD;
        s8 uAE;
        s8 uAF;
        s8 uB0;
        s8 uB1;
        s16 uB2;
        s16 uB4;
        s16 uB6;
        f32 uB8;
        f32 uBC;
        f32 uC0;
        f32 uC4;
        f32 uC8;
        f32 uCC;
        f32 uD0;
        f32 uD4;
        f32 uD8;
        f32 uDC;
        f32 uE0;
        f32 uE4;
        f32 uE8;
        s32 uEC;
        s32 uF0;
        s8 uF4;
        s8 uF5;
        s8 uF6;
        s8 uF7;
        s8 uF8;
        s8 uF9;
    } sp;
    f32 temp_f12;
    f32 temp_f2;
    f32 temp_f2_2;
    s32 temp_v0_2;
    s32 var_v0;
    u8 *temp_s0;
    u8 *temp_v0;

    temp_s0 = arg0 + 0x28;
    (*(f32 *)((u8 *)temp_s0 + 0)) = (f32) ((*(f32 *)((u8 *)temp_s0 + 0)) + ((0.030000001f + (random_float() * 0.010000001f)) * g_frame_step_f));
    if ((*(f32 *)((u8 *)temp_s0 + 0)) > 1.0f) {
        if ((*(u8 *)((u8 *)temp_s0 + 8)) & 1) {
            sp.uB1 = 0x74;
            sp.u9C = 0x5310;
            sp.u94 = 0x200005;
            sp.u98 = 0x9F0600;
            sp.uA8 = 0xFF;
            sp.uA9 = 0xFF;
            sp.uAA = 0xFF;
            sp.uAB = 0xFF;
            sp.uB2 = 1;
            sp.uA0 = 0;
            sp.uA4 = 0;
            sp.uB0 = 0xFF;
            sp.uD0 = 0.0f;
            sp.uD4 = 0.0f;
            sp.uD8 = 0.0f;
            sp.uDC = 0.0f;
            sp.uE0 = 0.0f;
            sp.uE4 = 0.0f;
            sp.uE8 = 0.0f;
            sp.uB4 = 0xFF;
            sp.uB6 = 1;
            sp.uB8 = 1.0f;
            sp.uF4 = 6;
            sp.uF5 = 6;
            sp.uF6 = 0x18;
            sp.uF7 = -1;
            sp.uF8 = -1;
            sp.uF9 = 0;
            sp.uF0 = 0;
            sp.u9E = 0x12C;
            sp.uAC = 0xFF;
            sp.uAD = 0xFF;
            sp.uAE = 0xFF;
            sp.u90 = 0.0f;
            do {
                temp_f2 = (random_float() * 20.0f) + 30.0f;
                temp_f12 = temp_f2 * 0.15f;
                sp.u80 = temp_f2;
                sp.u84 = temp_f2;
                sp.u88 = temp_f12;
                sp.u8C = temp_f12 * 0.5f;
                temp_f2_2 = (random_float() * 500.0f) + 600.0f;
                sp.uBC = temp_f2_2;
                sp.uC0 = temp_f2_2 * 0.5f;
                vec2_from_angle_rad(2.0f * (random_float() * 3.1415927f), (f32) (*(s16 *)((u8 *)((*(u8 **)((u8 *)temp_s0 + 4))) + 6)), &sp.uC4, &sp.uCC);
                sp.uC4 += (f32) (*(s16 *)((u8 *)((*(u8 **)((u8 *)temp_s0 + 4))) + 0));
                sp.uCC += (f32) (*(s16 *)((u8 *)((*(u8 **)((u8 *)temp_s0 + 4))) + 4));
                temp_v0 = (*(u8 **)((u8 *)temp_s0 + 4));
                sp.uC8 = (random_float() * (f32) (*(s16 *)((u8 *)temp_v0 + 8))) + (f32) (*(s16 *)((u8 *)temp_v0 + 2));
                var_v0 = 0;
                if (random_int() & 1) {
                    var_v0 = 0x40;
                }
                sp.uEC = var_v0 | 0xC000;
                sp.uAF = (random_int() & 0x7F) + 0x80;
                temp_v0_2 = particle_spawn_ex(&sp.u94, 2, 0, 0x14, (s32) (*(u8 *)((u8 *)arg0 + 0xC)), (s32) (*(u8 *)((u8 *)arg0 + 1)));
                if (temp_v0_2 != 0) {
                    memcpy(temp_v0_2 + 0xA8, &sp.u80, 0x14);
                }
                (*(f32 *)((u8 *)temp_s0 + 0)) = (f32) ((*(f32 *)((u8 *)temp_s0 + 0)) - 1.0f);
            } while ((*(f32 *)((u8 *)temp_s0 + 0)) > 1.0f);
            return;
        }
        do {
            (*(f32 *)((u8 *)temp_s0 + 0)) = (f32) ((*(f32 *)((u8 *)temp_s0 + 0)) - 1.0f);
        } while ((*(f32 *)((u8 *)temp_s0 + 0)) > 1.0f);
    }
}
extern f32 g_area_sparkle_edge_k; /* was D_800A2830 */
extern f32 g_area_sparkle_chance; /* was D_800A2834 */
/* was func_15108BD8 */
s32 area_sparkle_update(u8 *arg0, s32 arg1) {
    u8 *var_v0;
    f32 temp_f2;
    f32 temp_f0_3;
    f32 temp_f0_2;
    f32 temp_f0;
    u8 *sp18;

    temp_f0 = (*(f32 *)((u8 *)arg0 + 0xA8));
    var_v0 = arg0 + 0xA8;
    temp_f2 = (*(f32 *)((u8 *)arg0 + 0xAC)) - temp_f0;
    if ((temp_f0 < (*(f32 *)((u8 *)arg0 + 0xB4))) || (temp_f2 < (*(f32 *)((u8 *)var_v0 + 0xC)))) {
        (*(s32 *)((u8 *)arg0 + 0x1C)) = 0;
        var_v0 = arg0 + 0xA8;
    } else {
        temp_f0_2 = (*(f32 *)((u8 *)var_v0 + 8));
        if (((*(f32 *)((u8 *)var_v0 + 0)) < temp_f0_2) || (temp_f2 < temp_f0_2)) {
            (*(s32 *)((u8 *)arg0 + 0x1C)) = 0x10000;
        } else {
            (*(s32 *)((u8 *)arg0 + 0x1C)) = 0x20000;
        }
    }
    temp_f0_3 = (*(f32 *)((u8 *)var_v0 + 0x10));
    if (temp_f0_3 != 0.0f) {
        if ((temp_f0_3 < g_area_sparkle_edge_k) || ((11.0f - temp_f0_3) < g_area_sparkle_edge_k)) {
            (*(s32 *)((u8 *)arg0 + 0x1C)) = 0;
            (*(s8 *)((u8 *)arg0 + 0x74)) = -1;
        } else {
            (*(s8 *)((u8 *)arg0 + 0x74)) = 3;
        }
        (*(f32 *)((u8 *)var_v0 + 0x10)) = (f32) ((*(f32 *)((u8 *)var_v0 + 0x10)) - g_frame_step_f);
        if ((*(f32 *)((u8 *)var_v0 + 0x10)) < 0.0f) {
            (*(f32 *)((u8 *)var_v0 + 0x10)) = 0.0f;
            (*(s8 *)((u8 *)arg0 + 0x74)) = -1;
        }
        goto block_19;
    }
    (*(f32 *)((u8 *)var_v0 + 0)) = (f32) ((*(f32 *)((u8 *)var_v0 + 0)) - g_frame_step_f);
    if ((*(f32 *)((u8 *)var_v0 + 0)) < 0.0f) {
        return 0;
    }
    if ((*(s32 *)((u8 *)arg0 + 0x1C)) == 0x20000) {
        sp18 = var_v0;
        if (random_float() < g_area_sparkle_chance) {
            (*(f32 *)((u8 *)sp18 + 0x10)) = 11.0f;
        }
    }
block_19:
    return 1;
}
/* was func_15108D7C */
void area_sparkle_emitter_handle_event(u8 *arg0, s32 arg1, u8 arg2) {
    struct212 *temp_v0 = (struct212 *)(arg0 + 0x28);

    if (arg2 == 0x2B) {
        temp_v0->unk8 |= 1;
    } else if (arg2 == 0x2C) {
        temp_v0->unk8 &= ~1;
    }
}
