#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* was func_150175E0 */
void render_set_detail_level(void) {
    if ((D_800BE616 == 0) && ((g_save_progress_bits->unk18 & 1) == 0)) {
        g_hud_health_shown_pieces = g_hud_health_max_pieces = 3;
    } else {
        g_hud_health_shown_pieces = g_hud_health_max_pieces = 6;
    }
}

extern s32 g_hud_health_pos_hidden; /* was D_8009E084 */
extern Mtx g_hud_persp_mtx; /* was D_800D27F0 */
extern s32 g_hud_health_pos; /* was D_800D2848 */
extern s32 g_hud_health_rot; /* was D_800D2858 */
extern s32 g_hud_health_show_timer; /* was D_800D2864 */
extern u16 g_hud_persp_norm; /* was D_800D2874 */
extern s32 g_hud_bubbles; /* was D_800D2880 */
extern s8 g_hud_bubble0_state; /* was D_800D288D */
extern s8 g_hud_bubble1_state; /* was D_800D289D */
extern s32 g_hud_bubble_spawn_timer; /* was D_800D28E0 */
extern s32 g_hud_air_meter_block; /* was D_800D28E8 */
extern s32 g_hud_health_piece_dl; /* was D_800D29A8 */

/* was func_15017640 */
void camera_view_state_init(void) {
    f32 *var_v0;
    u8 *temp_v0;

    g_hud_clock_enabled = 0;
    g_hud_health_piece_dl = 0;
    (*(f32 *)((u8 *)(&g_hud_health_rot) + 0)) = 0.0f;
    (*(f32 *)((u8 *)(&g_hud_health_rot) + 4)) = 0.0f;
    (*(f32 *)((u8 *)(&g_hud_health_rot) + 8)) = 0.0f;
    (*(f32 *)((u8 *)(&g_hud_health_pos) + 0)) = (f32) (*(s16 *)((u8 *)(&g_hud_health_pos_hidden) + 0));
    (*(f32 *)((u8 *)(&g_hud_health_pos) + 4)) = (f32) (*(s16 *)((u8 *)(&g_hud_health_pos_hidden) + 2));
    var_v0 = g_hud_health_piece_scales;
    (*(f32 *)((u8 *)(&g_hud_health_pos) + 8)) = (f32) (*(s16 *)((u8 *)(&g_hud_health_pos_hidden) + 4));
    g_hud_health_show_timer = 0;
    g_hud_health_drop_list = NULL;
    do {
        var_v0 = (f32 *)((u8 *)var_v0 + (4));
        (*(f32 *)((u8 *)var_v0 + -4)) = 1.0f;
    } while ((u32) var_v0 < (u32) &g_hud_health_pos);
    g_hud_bubble0_state = 0;
    g_hud_bubble1_state = 0;
    temp_v0 = ((s32 *)((u8 *)&g_hud_bubbles + (2 * 0x10)));
    (*(s8 *)((u8 *)temp_v0 + 0x1D)) = 0;
    (*(s8 *)((u8 *)temp_v0 + 0x2D)) = 0;
    (*(s8 *)((u8 *)temp_v0 + 0x3D)) = 0;
    (*(s8 *)((u8 *)temp_v0 + 0xD)) = 0;
    g_hud_bubble_spawn_timer = 0;
    bzero(&g_hud_air_meter_block, 0xC0);
    guPerspective(&g_hud_persp_mtx, &g_hud_persp_norm, 50.0f, 60.6f, 53.0f, 20000.0f, 1.0f);
}
// void camera_view_state_init(void) {
//     s32 i;
//     g_hud_clock_enabled = 0;
//     D_800D2588 = 0;
//
//     D_800D2438[0] = 0.0f;
//     D_800D2438[1] = 0.0f;
//     D_800D2438[2] = 0.0f;
//
//     D_800D2428[0] = D_8009DCB4[0];
//     D_800D2428[1] = D_8009DCB4[1];
//     D_800D2428[2] = D_8009DCB4[2];
//
//     D_800D2444 = 0;
//     g_hud_health_drop_list = 0;
//
//     for (i = 0; i < 6; i++) {
//         g_hud_health_piece_scales[i] = 1.0f;
//     }
//
//     D_800D246D = 0;
//     D_800D247D = 0;
//
//     D_800D2460[1][13] = 0;
//     D_800D2460[2][13] = 0;
//     D_800D2460[3][13] = 0;
//     D_800D2460[0][13] = 0;
//
//     D_800D24C0 = 0;
//     bzero(&D_800D24C8, 0xC0);
//     guPerspective(&D_800D23D0, &D_800D2454, 50.0f, 60.599998474121094f, 53.0f, D_800968B0, 1.0f);
// }
