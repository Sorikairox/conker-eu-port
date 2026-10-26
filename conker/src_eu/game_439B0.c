#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* was func_15016500 */
void level_globals_reset(void) {
    g_hint_action = (u8)0;
    g_hint_box_open = (u8)0;
    g_hint_text_asset = 0;
    g_hint_intro_asset = 0;
    g_hint_text_buf = 0;
    g_hint_text_box = 0;
    bzero(g_hint_box_params, 48); // bzero
    g_hint_box_x = 0.0f;
    g_hint_box_y = 0.0f;
    g_hint_box_scale = 0.0f;
    g_hint_voice_pos = (u8)0;
    g_hint_voice_count = (u8)0;
    g_hint_voice_queue = 0;
}

// grim looking loop
s32 asset_lookup_rom(s32 *, s32, s32, u8, s32);
extern u8 g_text_bank_lang; /* was D_800BEECB */
/* was func_15016588 */
void level_build_flag_bitmask(void) {
    s32 idx;
    s32 i;
    bzero(D_eu_800BE9A0, 8);
    idx = -1;
    for (i = 0; i != 0x43; i++) {
        s32 bit;
        s32 sp40;
        if (!(i & 7)) {
            bit = 1;
            idx++;
        } else {
            bit *= 2;
        }
        asset_lookup_rom(&sp40, 3, 0x1A, g_text_bank_lang, i);
        if (sp40 != 0) {
            D_eu_800BE9A0[idx] |= bit;
        }
    }
}
