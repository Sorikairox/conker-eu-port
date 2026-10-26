#include <ultra64.h>
#include "functions.h"
#include "variables.h"


/* P93: 28 arguments as the asm passes them (a0 = 0, a1..a3 = the first three floats in integer registers) */
s32 beam_effect_spawn(s32, f32, f32, f32, f32, f32, f32, f32, f32, f32, f32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, s32, f32, f32, f32, f32, f32, f32);
void impact_scatter_ahead(s32);
int game_gu_random(void);
extern s32 g_storm_active; /* was D_80088DA4 */
extern s32 g_storm_center; /* was D_800D9E24 */
extern s32 g_storm_spread; /* was D_800D9E28 */
extern s32 g_storm_intensity_max; /* was D_800D9E2C */
extern s32 g_storm_phase_timer; /* was D_800D9E30 */
extern s32 g_storm_intensity; /* was D_800D9E34 */

/* was func_150E6060 */
void weather_lightning_storm_update(void) {
    f32 temp_f12;
    f32 temp_f14;
    f32 temp_f20;
    f32 temp_f22;
    f32 temp_f22_2;
    f32 temp_f24;
    f32 temp_f2;
    f32 temp_f30;
    f32 var_f20;
    f32 var_f24;
    f32 var_f26;
    f32 var_f28;
    s32 temp_lo;
    s32 temp_s1;
    s32 temp_s2;
    s32 temp_t5;
    s32 temp_t6;
    s32 var_a0;
    s32 var_s3;
    s32 var_s4;
    s32 var_v1;

    if (g_storm_active == 1) {
        var_v1 = g_storm_phase_timer + g_frame_ticks;
        g_storm_phase_timer = var_v1;
        if (var_v1 >= 0x83) {
            var_v1 = -(game_gu_random() % 30);
            g_storm_phase_timer = var_v1;
        }
        if (var_v1 >= 0x1F) {
            var_a0 = g_storm_intensity;
            if (var_a0 < g_storm_intensity_max) {
                temp_t5 = var_a0 + (g_frame_ticks * 2);
                g_storm_intensity = temp_t5;
                var_a0 = temp_t5;
            }
        } else {
            temp_t6 = g_storm_intensity - g_frame_ticks;
            if (g_frame_ticks < g_storm_intensity) {
                g_storm_intensity = temp_t6;
                var_a0 = temp_t6;
            } else {
                g_storm_active = 0;
                g_storm_intensity = 0;
                var_a0 = 0;
            }
        }
        temp_lo = (s32) (var_a0 + 0xA) / 10;
        var_s3 = var_a0 + 1;
        impact_scatter_ahead(var_a0);
        var_s4 = 0;
        if (temp_lo > 0) {
            do {
                if ((var_s3 >= 0xA) || ((game_gu_random() % 11) == var_s3)) {
                    temp_s1 = (((game_gu_random() % (s32) g_storm_spread) * 2) - g_storm_spread) + g_storm_center;
                    temp_s2 = (((game_gu_random() % (s32) g_storm_spread) * 2) - g_storm_spread) + g_storm_center;
                    var_f26 = (f32) (game_gu_random() % 200);
                    var_f24 = (f32) temp_s2;
                    var_f20 = (f32) temp_s1;
                    var_f28 = ((f32) (game_gu_random() % 200) + var_f26) - 100.0f;
                    if (((var_f24 - 5.0f) < var_f20) && (var_f20 < (var_f24 + 5.0f))) {
                        var_f28 += 150.0f;
                        var_f26 += 150.0f;
                    }
                    if ((game_gu_random() % 2) != 0) {
                        var_f20 = (f32) (s32) (var_f20 + 180.0f);
                    } else {
                        var_f24 = (f32) (s32) (var_f24 + 180.0f);
                    }
                    temp_f22 = var_f20 * 0.017453292f;
                    temp_f20 = sinf(temp_f22) * 3000.0f;
                    temp_f22_2 = cosf(temp_f22) * 3000.0f;
                    temp_f30 = var_f24 * 0.017453292f;
                    temp_f24 = sinf(temp_f30) * 3000.0f;
                    temp_f2 = g_player_views->unk2F8;
                    temp_f12 = g_player_views->unk2FC;
                    temp_f14 = g_player_views->unk300;
                    beam_effect_spawn(0, temp_f20 + temp_f2, var_f28 + temp_f12, temp_f22_2 + temp_f14, temp_f24 + temp_f2, var_f26 + temp_f12, (cosf(temp_f30) * 3000.0f) + temp_f14, 160.0f, 10.0f, 4.0f, 360.0f, 0xF, 0x43, 0, 0, 0, 0, 0, 0, -1, 0, 0, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f);
                }
                var_s4 += 1;
                var_s3 -= 0xA;
            } while (var_s4 != temp_lo);
        }
    }
}