#include <ultra64.h>
#include "functions.h"
#include "variables.h"


extern u8 g_level_anim_frame; /* was D_800DD835 */
extern u8 g_level_anim_accum; /* was D_800DD836 */

/* was func_15174F10 */
void level_anim_frame_counter_tick(s32 arg0, s32 arg1) {
    g_level_anim_accum += g_frame_ticks;
    if (arg0 < g_level_anim_accum) {
        g_level_anim_frame++;
        if (g_level_anim_frame >= arg1) {
            g_level_anim_frame = 0;
        }
        g_level_anim_accum = 0;
    }
}

extern void (*g_level_update_fns[])(s32); /* was D_8008D0A4 */
extern u16 g_text_icon_clock; /* was D_800CC16E */
s32 texscroll_update(s32, s32);
s32 tex_scroll_update();
void ambient_slots_refresh(void);
s32 light_fx_update();

/* was func_15174F68 */
void level_update_frame(s32 arg0, s32 arg1) {
    level_frame_hook_nop();
    texscroll_update(g_level_part_dls[0], g_level_part_dls[1]);
    tex_scroll_update();
    if (g_level_header->padB[0] != 0) {
        g_level_update_fns[g_level_header->padB[0]](arg1);
    }
    if (g_mp_mode_active == 0) {
        ambient_slots_refresh();
        light_fx_update();
    }
    g_text_icon_clock += g_frame_ticks << 6;
}

extern Gfx *(*g_level_pre_layer_fns[])(Gfx *, s32); /* was D_8008D114 */

/* was func_15174AA4 */
Gfx *render_level_pre_layer(Gfx *gdl, s32 arg1, s32 arg2) {
    gDPPipeSync(gdl++);
    gSPMatrix(gdl++, g_identity_mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    if (*((u8 *)g_level_header + 0xC) != 0) {
        gdl = g_level_pre_layer_fns[*((u8 *)g_level_header + 0xC)](gdl, arg2);
    }
    gSPMatrix(gdl++, g_identity_mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    return gdl;
}

extern Gfx *(*g_level_post_layer_fns[])(Gfx *, s32); /* was D_8008D11C */

/* was func_15174B48 */
Gfx *render_level_post_layer(Gfx *gdl, s32 arg1, s32 arg2) {
    gDPPipeSync(gdl++);
    gSPMatrix(gdl++, g_identity_mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    if (*((u8 *)g_level_header + 0xD) != 0) {
        gdl = g_level_post_layer_fns[*((u8 *)g_level_header + 0xD)](gdl, arg2);
    }
    gSPMatrix(gdl++, g_identity_mtx, G_MTX_NOPUSH | G_MTX_LOAD | G_MTX_MODELVIEW);
    return gdl;
}
