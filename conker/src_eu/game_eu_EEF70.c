#include <ultra64.h>
#include "functions.h"
#include "variables.h"


#ifdef NON_MATCHING
s32 spawn_ring_emit(f32, f32, f32, f32, s32, s32, s32, s32, s32, f32, s32, s32);

/* was func_150C1260 */
void foot_ring_debris_effect(u8 *arg0, s32 arg1) {
    struct {
        f32 uA8;
        f32 uAC;
        f32 uB0;
        f32 uB4;
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
        f32 uEC;
        f32 uF0;
        f32 uF4;
        s32 uF8;
        s16 uFC;
        s16 uFE;
        s8 u100;
        u8 pad101[0x3];
        s32 u104;
        s8 u108;
        s8 u109;
        s8 u10A;
        s8 u10B;
        s8 u10C;
        s8 u10D;
        s8 u10E;
        s8 u10F;
        s8 u110;
        u8 pad111[0x1];
        s8 u112;
        u8 pad113[0x1];
        u8 * u114;
        u8 u118;
        u8 pad119[0x1];
        s16 u11A;
        s16 u11C;
        u8 pad11E[0x6];
        f32 u124;
        s32 u128;
        f32 u12C;
        u8 pad130[0x4];
        f32 u134;
    } sp;
    f32 sp80;
    f32 temp_f0;
    f32 temp_f20;
    f32 temp_f22;
    f32 temp_f24;
    f32 temp_f2;
    s32 temp_s0;
    s32 temp_t6;
    s32 temp_v1;
    s32 temp_v1_2;
    s32 var_s1;
    u8 *temp_v0;

    temp_t6 = arg1 & 0xFF;
    sp.u124 = ((*(f32 *)((u8 *)arg0 + 0x14C)) + (*(f32 *)((u8 *)arg0 + 0x150))) * 0.5f;
    if (arg0 != NULL) {
        temp_v1 = (*(s32 *)((u8 *)arg0 + 0x1D4));
        if (temp_v1 != 0) {
            switch (temp_t6) {                      /* irregular */
            case 0:
                sp.u128 = 0xD;
                break;
            case 1:
                sp.u128 = 0x11;
                break;
            }
            mtx_get_translation(temp_v1, sp.u128, &sp.u12C);
            temp_f0 = sp.u124 * 80.0f;
            sp80 = temp_f0;
            spawn_ring_emit(sp.u12C, (*(f32 *)((u8 *)arg0 + 0x180)), sp.u134, temp_f0, 0, 0x10, 0x10, 0, 0, temp_f0 * 4.0f, 0, 0xFF);
            water_ring_spawn(-1, (s32) sp.u12C, (s32) ((f32) (s32) (*(f32 *)((u8 *)arg0 + 0x180)) + 2.0f), (s32) sp.u134, 0xB, 0x13, 0, 0xFF, 0);
            sp.uFE = 5;
            sp.uF8 = 0x29E8;
            sp.u100 = 0;
            sp.u104 = 0;
            sp.u108 = 0xFF;
            sp.u109 = 1;
            sp.u10A = 0;
            sp.u10B = 0;
            sp.u10C = 0;
            sp.u10D = 0;
            sp.u10E = 0;
            sp.u10F = 0;
            sp.u110 = 0;
            sp.u112 = 1;
            sp.u114 = arg0;
            sp.uC4 = 1.0f;
            sp.uC8 = 1.0f;
            sp.uCC = 1.0f;
            sp.uAC = 0.4f;
            sp.uF0 = 0.0f;
            sp.uF4 = -0.9f;
            sp.u11A = 0x10;
            sp.u11C = 0xF;
            sp.u118 = (*(u8 *)((u8 *)arg0 + 0x3B));
            temp_v1_2 = (random_int() & 7) + 5;
            var_s1 = temp_v1_2 - 1;
            if (temp_v1_2 != 0) {
                do {
                    temp_s0 = random_int() & 0xFF;
                    temp_f20 = ((random_float() * 0.9f) + 0.1f) * 18.0f * sp.u124;
                    temp_f22 = angle_byte_cos((temp_s0 - 0x40) & 0xFF);
                    temp_f24 = angle_byte_cos(temp_s0 & 0xFF);
                    sp.uFC = (random_int() & 0x1F) + 0xF;
                    sp.uD0 = (sp80 * temp_f22) + sp.u12C;
                    sp.uE0 = temp_f20;
                    sp.uD4 = (*(f32 *)((u8 *)arg0 + 0x180)) + 2.0f;
                    sp.uD8 = (sp80 * temp_f24) + sp.u134;
                    sp.uDC = temp_f20 * temp_f22;
                    sp.uE4 = temp_f20 * temp_f24;
                    temp_f2 = ((random_float() * 0.9f) + 0.1f) * sp.u124 * 2.23f;
                    sp.uB0 = temp_f2;
                    sp.uB4 = temp_f2;
                    sp.uA8 = temp_f2;
                    sp.uB8 = random_float() * 360.0f;
                    sp.uBC = random_float() * 360.0f;
                    sp.uC0 = random_float() * 360.0f;
                    sp.uE8 = 25.0f - (random_float() * 50.0f);
                    sp.uEC = 25.0f - (random_float() * 50.0f);
                    temp_v0 = mdl_particle_spawn(&sp.uA8, 3, 0xFF, 4, 0xFF, 0);
                    if (temp_v0 != NULL) {
                        (*(f32 *)((u8 *)temp_v0 + 0x170)) = (f32) (*(f32 *)((u8 *)arg0 + 0x180));
                    }
                    var_s1 -= 1;
                } while (var_s1 != 0);
            }
        }
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_eu_EEF70/foot_ring_debris_effect.s")
#endif