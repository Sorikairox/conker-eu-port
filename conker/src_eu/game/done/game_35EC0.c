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

    D_800DDE08 = 0;

    // unrolled loop?
    D_800DDE40 = 0;
    D_800DDDAC = 0;
    D_800DDE28 = 0;
    D_800DDDB0 = 0;
    D_800DDE1C = 0;
    D_800DDE20 = 0;
    D_800DDDC8 = 0.0f;
    D_800DDDD8 = 0.0f;

    D_800DDE3C = 0;
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
    D_800DDE18 = 0;
    g_level_entry_zoom_mode = 0;
}
