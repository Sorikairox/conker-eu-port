#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* was func_15008A10 */
void obj_holder_refs_init(void) {
    D_80088720 = obj_find_by_setup_id(1);
    g_holder_target_pos.x = 0.0f;
    g_holder_target_pos.y = 0.0f;
    g_holder_target_pos.z = 0.0f;
    D_80088730 = obj_find_by_setup_id(1);
}

/* was func_15008A60 */
void view_zoom_state_reset(void) {
    if (0) {}

    g_screen_pulse_timer = 0;

    // unrolled loop?
    D_800DDE40 = 0;
    g_screen_fade_dir = 0;
    g_screen_fade_duration = 0;
    g_screen_fade_timer = 0;
    g_hud_lens_mode = 0;
    g_hud_lens_scripted = 0;
    g_hud_lens_zoom = 0.0f;
    g_hud_lens_zoom_rate = 0.0f;

    g_hud_lens_state = 0;
    g_screen_fade_dir_p1 = 0;
    g_screen_fade_duration_p1 = 0;
    g_screen_fade_timer_p1 = 0;
    g_hud_lens_mode_p1 = 0;
    g_hud_lens_scripted_p1 = 0;
    g_hud_lens_zoom_p1 = 0.0f;
    g_hud_lens_zoom_rate_p1 = 0.0f;

    g_hud_lens_state_p1 = 0;
    g_screen_fade_dir_p2 = 0;
    g_screen_fade_duration_p2 = 0;
    g_screen_fade_timer_p2 = 0;
    g_hud_lens_mode_p2 = 0;
    g_hud_lens_scripted_p2 = 0;
    g_hud_lens_zoom_p2 = 0.0f;
    g_hud_lens_zoom_rate_p2 = 0.0f;

    g_hud_lens_state_p2 = 0;
    g_screen_fade_dir_p3 = 0;
    g_screen_fade_duration_p3 = 0;
    g_screen_fade_timer_p3 = 0;
    g_hud_lens_mode_p3 = 0;
    g_hud_lens_scripted_p3 = 0;
    g_hud_lens_zoom_p3 = 0.0f;
    g_hud_lens_zoom_rate_p3 = 0.0f;

    g_hud_lens_state_p3 = 0;
    g_letterbox_track = 0;
    g_level_entry_zoom_mode = 0;
}
