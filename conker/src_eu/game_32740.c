#include <ultra64.h>

#include "functions.h"
#include "variables.h"
// hoisted declarations of the NON_MATCHING bodies
void collision_find_floor(s32 arg0, s32 arg1, s32 arg2, s32 arg3, s32 arg4, s32 arg5, f32 arg6, f32 arg7, f32 arg8, f32 arg9, u16 argA, s32 argB, f32 argC, f32 argD);
void camera_calc_relative_yaw(struct108 *arg0);
void camera_queue_event(struct108 *arg0, s32 arg1, void *arg2);
extern f32 g_camera_initial_eye_k; /* was D_80095DA0 */
extern f32 g_camera_event_params[]; /* was D_800C3A20 */


s32 allocate_memory(s32, s32, s32, s32);
s32 asset_load(s32 *arg0, s32 arg1, ...);
void camera_controller_init(struct108 *arg0, s32 arg1, s16 arg2, s32 arg3);
void camera_viewport_tables_reset(void);
void camera_shake_tracks_load(void);
extern s32 g_camera_fixed_pos_records; /* was D_800DC450 */
extern s16 g_camera_pivot_count; /* was D_800898F0 */
extern s32 g_camera_event_queues; /* was D_800DC6E0 */
extern Mtx *g_view_mtx_bufs[];       /* per DL buffer: view matrices, 0x40 per player; was D_800DC6D0 */
extern s32 g_camera_grid_bufs[]; /* was D_800BE6D0 */
extern s32 g_camera_saved_slots; /* was D_800DC440 */

/* Level init: load the 0x18-byte records (g_camera_fixed_pos_records), allocate the per-player camera controllers (g_player_views,
 * 0x9A0 each) and view matrices, initialise each controller, then the camera tables. */
/* was func_15005290 */
void camera_level_init(s32 arg0, s32 arg1) {
    s32 size;
    s32 n;
    u32 i;

    g_camera_fixed_pos_records = asset_load(&size, 3, 0xC, arg0, 8);
    g_camera_pivot_count = (u32)size / 0x18;
    n = g_last_player_index + 1;
    g_player_views = (struct108 *)allocate_memory(n * 0x9A0, 1, 1, 0);
    g_camera_event_queues = allocate_memory(n * 0xB0, 1, 0, 0);
    g_view_mtx_bufs[0] = (Mtx *)allocate_memory(n << 6, 1, 1, 0);
    g_view_mtx_bufs[1] = (Mtx *)allocate_memory(n << 6, 1, 1, 0);
    i = 0;
    do {
        g_camera_grid_bufs[i] = allocate_memory(g_framebuffer_width * 2, 1, 2, 0);
        camera_controller_init((struct108 *)((u8 *)g_player_views + i * 0x9A0), i, (s16)arg0, arg1);
        g_camera_timers[i] = 0;
        i++;
    } while (i <= (u32)g_last_player_index);
    camera_viewport_tables_reset();
    camera_shake_tracks_load();
    g_camera_frame_count = 0;
    g_camera_saved_slots = allocate_memory(g_last_player_index * 0x9A0 + 0x9A0, 1, 2, 0);
}
// NON-MATCHING: first half ok, second half needs work
// void camera_level_init(s32 arg0, s32 arg1) {
//     s32 pad0;
//     s32 sp68;
//     s32 pad1;
//     s32 temp_s0;
//     s32 i;
//
//     D_800DC020 = asset_load(&sp68, 3, 12, arg0, 8);
//     D_80089550 = (sp68 / 24U);
//     temp_s0 = g_last_player_index + 1;
//     g_player_views = allocate_memory(temp_s0 * 0x9A0, 1, 1, 0);
//     g_sky_asset = allocate_memory(temp_s0 * 0xB0, 1, 0, 0);
//     g_coll_probe_z->unk0 = allocate_memory(temp_s0 << 6, 1, 1, 0);
//     g_coll_probe_z->unk4 = allocate_memory(temp_s0 << 6, 1, 1, 0);
//
//     i = 0;
//     do {
//         D_800BE2B0[i] = allocate_memory(g_framebuffer_width * 2, 1, 2, 0);
//         camera_controller_init(&g_player_views[i], i, arg0, arg1);
//         g_camera_timers[i] = 0;
//     } while (g_last_player_index >= i++) ;
//
//     func_1512ABF8();
//     func_1512D238();
//     g_camera_frame_count = 0;
//     D_800DC010 = allocate_memory((g_last_player_index * 0x9A0) + 0x9A0, 1, 2, 0);
// }

s32 camera_pop_mode(struct108 *arg0, s32 arg1);
void camera_apply_zoom_level(struct108 *arg0);
void camera_calc_view_dir(struct108 *arg0);
void camera_update_mode_index(struct108 *arg0);
void camera_level_hook_dispatch(struct108 *arg0, s32 arg1);
void camera_event_queue_clear(struct108 *arg0);
void camera_pivot_slot_reset(struct108 *arg0, s32 arg1);
void camera_shake_reset(struct108 *arg0);
void camera_update_underwater_mode(struct108 *arg0);
void obj_place_at_start(void *arg0, s32 arg1, s32 arg2);
extern s32 g_camera_restore_skip; /* was D_800898C0 */
extern s32 g_camera_saved_tgt_197[]; /* was D_800898C4 */
extern s32 g_camera_saved_tgt_198[]; /* was D_800898D4 */

#define CAM_W(o) (*(s32 *)(p + (o)))
#define CAM_H(o) (*(s16 *)(p + (o)))
#define CAM_F(o) (*(f32 *)(p + (o)))

/* Initialise one per-player camera controller (0x9A0 bytes, g_player_views[player]): clear it, reset the 21 camera
 * slots (camera_pop_mode, 999 timers), link it with the player's object record g_objects[player] (0x32C each,
 * record +0x318 = controller, controller +0x3D0 = record, +0x3D4 = record +0x31C), mode arg2 (camera_pivot_slot_reset /
 * camera_level_hook_dispatch), then the default distances / limits. */
/* was func_150054C4 */
void camera_controller_init(struct108 *arg0, s32 arg1, s16 arg2, s32 arg3) {
    u8 *p = (u8 *)arg0;
    u8 *rec;
    u16 i;

    bzero(p, 0x9A0);
    p[0x23D] = arg1;
    p[0x23C] = 1;
    for (i = 0; i < 0x15; i++) {
        camera_pop_mode(arg0, i);
        CAM_H(0x1B6 + i * 2) = 999;
    }
    CAM_F(0x5D4) = ((f32)g_framebuffer_height * 60.0f) / 216.0f;
    rec = (u8 *)g_objects + p[0x23D] * 0x32C;
    CAM_W(0x2C) = 1;
    CAM_W(0xDC) = 0;
    *(u8 **)(p + 0x3D0) = rec;
    CAM_F(0x24C) = 1.0f;
    CAM_F(0x250) = 1.0f;
    CAM_H(0x3CC) = p[0x23D];
    CAM_F(0x5D8) = ((f32)g_framebuffer_height * 40.0f) / 216.0f;
    *(u8 **)(rec + 0x318) = p;
    CAM_W(0x134) = 1;
    CAM_W(0x84) = 0xE;
    CAM_W(0x240) = 0;
    CAM_H(0x1E0) = 0xD;
    CAM_H(0x1B4) = 3;
    CAM_F(0x5CC) = 1.0f;
    CAM_F(0x3A8) = 0.0f;
    camera_apply_zoom_level(arg0);
    CAM_H(0x272) = -1;
    CAM_H(0x5FA) = 1;
    p[0x3E8] = 1;
    CAM_F(0x67C) = (f32)*(u16 *)((u8 *)g_level_header + 2);
    CAM_F(0x2B0) = CAM_F(0x2A4);
    CAM_F(0x2B4) = CAM_F(0x2A8);
    CAM_F(0x2B8) = CAM_F(0x2AC);
    CAM_W(0x5F0) |= 0x80000000;
    CAM_F(0x384) = 999.0f; /* D_80095D90 */
    camera_calc_view_dir(arg0);
    camera_update_mode_index(arg0);
    CAM_H(0x5FC) = 10;
    CAM_F(0x26C) = 1.0f;
    camera_event_queue_clear(arg0);
    CAM_W(0x238) = -1;
    CAM_H(0x3CC) = p[0x23D];
    CAM_H(0x368) = p[0x23D];
    rec = (u8 *)g_objects + p[0x23D] * 0x32C;
    *(u8 **)(p + 0x3D0) = rec;
    CAM_W(0x3D4) = *(s32 *)(rec + 0x31C);
    camera_pivot_slot_reset(arg0, arg2);
    CAM_W(0x7CC) = 2;
    CAM_F(0x3F4) = -1.0f;
    CAM_F(0x3F8) = -1.0f;
    CAM_F(0x7BC) = 999.0f; /* D_80095D94 */
    CAM_F(0x3E0) = CAM_F(0x3A0);
    *(f32 *)(*(u8 **)(p + 0x3D4) + 0x18C) = 999.0f;
    camera_shake_reset(arg0);
    camera_update_underwater_mode(arg0);
    CAM_F(0x674) = 1.0f;
    obj_place_at_start(*(void **)(p + 0x3D0), arg3, 0);
    camera_level_hook_dispatch(arg0, arg2);
    CAM_W(0x2E0) = CAM_W(0x2BC);
    CAM_W(0x2E4) = CAM_W(0x2C0);
    CAM_W(0x2E8) = CAM_W(0x2C4);
    CAM_W(0x2EC) = CAM_W(0x2F8);
    CAM_W(0x2F0) = CAM_W(0x2FC);
    CAM_W(0x2F4) = CAM_W(0x300);
    CAM_F(0x364) = -10000.0f; /* D_80095D98 */
    CAM_F(0x7E8) = 50.0f;
    CAM_F(0x86C) = 999.0f; /* D_80095D9C */
    CAM_W(0x8BC) = g_camera_grid_bufs[p[0x23D]];
    g_camera_restore_skip = 0;
    g_cutscene_restart_transition = 0;
    g_camera_saved_tgt_197[p[0x23D]] = 0;
    g_camera_saved_tgt_198[p[0x23D]] = 0;
    CAM_H(0x5FE) = 0x32;
    p[0x23C] = 1;
}
#undef CAM_W
#undef CAM_H
#undef CAM_F
// NON-MATCHING: not a terrible start.
// void camera_controller_init(struct108 *arg0, s32 arg1, s16 arg2, s32 arg3) {
//     f32 temp_f2;
//     f32 temp_f4;
//     s32 temp_s2;
//     u16 temp_t9;
//     u8 temp_v0;
//     struct127 *temp_a2;
//     u16 phi_s0;
//     f32 phi_f4;
//
//     bzero(arg0, 0x9A0); // bzero
//
//     arg0->unk23C = 1;
//     arg0->unk23D = arg1;
//
//     for (phi_s0 = 0; phi_s0 < 0x15; phi_s0++)
//     {
//         camera_pop_mode(arg0, phi_s0);
//         arg0->unk1B6[phi_s0] = 999;
//     }
//     temp_v0 = arg0->unk23D;
//     temp_a2 = &g_objects[temp_v0]; // * 0x32C);
//     arg0->unk5D4 = (f32) (((f32) g_framebuffer_height * 60.0f) / 216.0f);
//     arg0->unk2C = 1;
//     arg0->unkDC = 0;
//     arg0->unk3D0 = temp_a2;
//     arg0->unk24C = 1.0f;
//     arg0->unk250 = 1.0f;
//     arg0->unk3CC = (s16) temp_v0;
//     arg0->unk5D8 = (f32) (((f32) g_framebuffer_height * 40.0f) / 216.0f);
//     temp_a2->camera = arg0;
//     arg0->unk134 = 1;
//     arg0->unk84 = 0xE;
//     arg0->unk240 = 0;
//     arg0->unk1E0 = (u16)0xD;
//     arg0->unk1B4 = (u16)3;
//     arg0->unk5CC = 1.0f;
//     arg0->unk3A8 = 0.0f;
//     camera_apply_zoom_level(arg0);
//     arg0->unk272 = (u16)-1;
//     arg0->unk5FA = (s16) 1;
//     arg0->unk3E8 = (u8)1;
//     temp_t9 = g_level_header->unk2;
//     temp_f4 = (f32) temp_t9;
//     phi_f4 = temp_f4;
//     if ((s32) temp_t9 < 0) {
//         phi_f4 = temp_f4 + 4294967296.0f;
//     }
//     arg0->unk67C = phi_f4;
//     arg0->unk2B0 = (f32) arg0->unk2A4;
//     arg0->unk2B4 = (f32) arg0->unk2A8;
//     arg0->unk2B8 = (f32) arg0->unk2AC;
//     arg0->unk5F0 = (s32) (arg0->unk5F0 | 0x80000000);
//     arg0->unk384 = (f32) D_800959E0;
//     camera_calc_view_dir(arg0);
//     camera_update_mode_index(arg0);
//     arg0->unk5FC = (u16)0xA;
//     arg0->unk26C = 1.0f;
//     func_1512D66C(arg0);
//     temp_v0 = arg0->unk23D;
//     arg0->unk238 = -1;
//     arg0->unk3CC = (s16) temp_v0;
//     arg0->unk368 = (s16) temp_v0;
//     temp_a2 = &g_objects[temp_v0]; // * 0x32C);
//     arg0->unk3D0 = temp_a2;
//     arg0->unk3D4 = temp_a2->unk31C;
//     func_151298C0(arg0, arg2, temp_a2);
//     temp_f2 = D_800959E4;
//     arg0->unk7CC = 2;
//     arg0->unk3F4 = -1.0f;
//     arg0->unk3F8 = -1.0f;
//     arg0->unk7BC = temp_f2;
//     arg0->unk3E0 = (f32) arg0->unk3A0;
//     arg0->unk3D4->unk18C = temp_f2;
//     func_1512D6F0(arg0);
//     camera_update_underwater_mode(arg0);
//     arg0->unk674 = 1.0f;
//     func_15085430(arg0->unk3D0, arg3, 0);
//     camera_level_hook_dispatch(arg0, arg2);
//     arg0->unk2E0 = arg0->unk2BC;
//     arg0->unk364 = D_800959E8;
//     arg0->unk2E8 = arg0->unk2C4;
//     arg0->unk2E4 = arg0->unk2C0;
//     arg0->unk2F0 = arg0->unk2FC;
//     arg0->unk2EC = arg0->unk2F8;
//     arg0->unk2F4 = arg0->unk300;
//     arg0->unk7E8 = 50.0f;
//     arg0->unk86C = D_800959EC;
//     arg0->unk8BC = D_800BE2B0[arg0->unk23D]; // * 4) + 0x800C0000)->unk-1D50;
//     D_80089520 = 0;
//     g_cutscene_restart_transition = (u8)0;
//     D_80089524[arg0->unk23D] = 0;
//     D_80089534[arg0->unk23D] = 0;
//     arg0->unk5FE = (u16)0x3C;
//     arg0->unk23C = (u8)1;
// }

/* P41: initial camera eye. Controller arg0 (g_player_views[player]) gets eye = arg2 (0x2F8, copied to 0x27C and 0x304),
 * at = the record arg1's position (0x2A4, copied to 0x2BC / 0x2B0 / 0x2E0), the horizontal distance 0x374, the
 * eye height state (collision_find_floor → 0x354..0x360, 0x348 / 0x34C), then the camera setup callees. Outside level
 * 0x21 and unless g_cutscene_slot_state == 1, camera events 5 / 8 (with g_camera_event_params[3] = yaw 0x37C) / 6. */
/* was func_15005818 */
void camera_set_initial_eye(struct108 *arg0, u8 *arg1, f32 *arg2) {
    u8 *p = (u8 *)arg0;
    f32 dx;
    f32 dz;
    f32 h;

    p[0x23C] = 1;
    *(f32 *)(p + 0x2F8) = arg2[0];
    *(f32 *)(p + 0x2FC) = arg2[1];
    *(f32 *)(p + 0x300) = arg2[2];
    *(s32 *)(p + 0x27C) = *(s32 *)(p + 0x2F8);
    *(s32 *)(p + 0x280) = *(s32 *)(p + 0x2FC);
    *(s32 *)(p + 0x284) = *(s32 *)(p + 0x300);
    *(s32 *)(p + 0x304) = *(s32 *)(p + 0x2F8);
    *(s32 *)(p + 0x308) = *(s32 *)(p + 0x2FC);
    *(s32 *)(p + 0x30C) = *(s32 *)(p + 0x300);
    collision_find_floor((s32)(p + 0x644), (s32)(p + 0x648), (s32)(p + 0x354), (s32)(p + 0x360), (s32)(p + 0x640), 0,
                  *(f32 *)(p + 0x2F8), *(f32 *)(p + 0x2FC), *(f32 *)(p + 0x300), *(f32 *)(p + 0x2FC), 0, 0, g_camera_initial_eye_k, *(f32 *)(p + 0x2FC));
    *(f32 *)(p + 0x358) = *(f32 *)(p + 0x354);
    *(f32 *)(p + 0x35C) = *(f32 *)(p + 0x354);
    *(f32 *)(p + 0x2A4) = *(f32 *)(arg1 + 0x14);
    *(f32 *)(p + 0x2A8) = *(f32 *)(arg1 + 0x18);
    *(f32 *)(p + 0x2AC) = *(f32 *)(arg1 + 0x1C);
    *(s32 *)(p + 0x2BC) = *(s32 *)(p + 0x2A4);
    *(s32 *)(p + 0x2C0) = *(s32 *)(p + 0x2A8);
    *(s32 *)(p + 0x2C4) = *(s32 *)(p + 0x2AC);
    dx = *(f32 *)(p + 0x2A4) - *(f32 *)(p + 0x2F8);
    dz = *(f32 *)(p + 0x2AC) - *(f32 *)(p + 0x300);
    *(s32 *)(p + 0x2B0) = *(s32 *)(p + 0x2A4);
    *(s32 *)(p + 0x2B4) = *(s32 *)(p + 0x2A8);
    *(s32 *)(p + 0x2B8) = *(s32 *)(p + 0x2AC);
    h = *(f32 *)(p + 0x2FC) - *(f32 *)(p + 0x354);
    *(f32 *)(p + 0x34C) = h;
    *(f32 *)(p + 0x348) = h;
    *(f32 *)(p + 0x374) = sqrtf(dx * dx + dz * dz);
    *(s32 *)(p + 0x2E0) = *(s32 *)(p + 0x2BC);
    *(s32 *)(p + 0x2E4) = *(s32 *)(p + 0x2C0);
    *(s32 *)(p + 0x2E8) = *(s32 *)(p + 0x2C4);
    *(s32 *)(p + 0x2EC) = *(s32 *)(p + 0x2F8);
    *(s32 *)(p + 0x2F0) = *(s32 *)(p + 0x2FC);
    *(s32 *)(p + 0x2F4) = *(s32 *)(p + 0x300);
    camera_apply_zoom_level(arg0);
    camera_calc_yaw(arg0);
    camera_calc_pitch(arg0);
    camera_calc_relative_yaw(arg0);
    *(s32 *)(p + 0x5F0) |= 4;
    if (g_level_id != 0x21 && g_cutscene_slot_state != 1) {
        camera_queue_event(arg0, 5, NULL);
        g_camera_event_params[3] = *(f32 *)(p + 0x37C);
        camera_queue_event(arg0, 8, g_camera_event_params);
        camera_queue_event(arg0, 6, NULL);
    }
}
// void camera_set_initial_eye(struct108 *arg0, void *arg1, void *arg2) {
//     void *sp48;
//     f32 temp_f0;
//     f32 temp_f12;
//     f32 temp_f14;
//     f32 temp_f2;
//     f32 temp_f2_2;
//     void *temp_a1;
//     void *temp_v0;
//     void *temp_v1;
//
//     arg0->unk23C = (u8)1;
//     temp_v1 = arg0->unk2F8;
//     arg0->unk2F8 = (f32) arg2->unk0;
//     arg0->unk2FC = (f32) arg2->unk4;
//     arg0->unk300 = (f32) arg2->unk8;
//     arg0->unk27C = (s32) temp_v1->unk0;
//     arg0->unk280 = (s32) temp_v1->unk4;
//     arg0->unk284 = (s32) temp_v1->unk8;
//     arg0->unk304 = (s32) temp_v1->unk0;
//     arg0->unk308 = (s32) temp_v1->unk4;
//     arg0->unk30C = (s32) temp_v1->unk8;
//     temp_f0 = arg0->unk2FC;
//     sp48 = temp_v1;
//     func_1510E7A4(arg0->unk644, arg0->unk648, arg0->unk354, arg0->unk360, arg0->unk640, 0, arg0->unk2F8, temp_f0, arg0->unk300, temp_f0, 0, 0, D_800959F0, temp_f0);
//     temp_f2 = arg0->unk354;
//     arg0->unk358 = temp_f2;
//     arg0->unk35C = temp_f2;
//     temp_v0 = arg0->unk2A4;
//     temp_a1 = arg0->unk2BC;
//     arg0->unk2A4 = (f32) arg1->unk14;
//     arg0->unk2A8 = (f32) arg1->unk18;
//     arg0->unk2AC = (f32) arg1->unk1C;
//     temp_a1->unk0 = (s32) temp_v0->unk0;
//     temp_a1->unk4 = (s32) temp_v0->unk4;
//     temp_a1->unk8 = (s32) temp_v0->unk8;
//     temp_f12 = arg0->unk2A4 - arg0->unk2F8;
//     temp_f14 = arg0->unk2AC - arg0->unk300;
//     arg0->unk2B0 = (s32) temp_v0->unk0;
//     arg0->unk2B4 = (s32) temp_v0->unk4;
//     temp_f2_2 = arg0->unk2FC - arg0->unk354;
//     arg0->unk2B8 = (s32) temp_v0->unk8;
//     arg0->unk34C = temp_f2_2;
//     arg0->unk348 = temp_f2_2;
//     arg0->unk374 = sqrtf((temp_f12 * temp_f12) + (temp_f14 * temp_f14));
//     arg0->unk2E0 = (s32) temp_a1->unk0;
//     arg0->unk2E4 = (s32) temp_a1->unk4;
//     arg0->unk2E8 = (s32) temp_a1->unk8;
//     arg0->unk2EC = (s32) temp_v1->unk0;
//     arg0->unk2F0 = (s32) temp_v1->unk4;
//     arg0->unk2F4 = (s32) temp_v1->unk8;
//     camera_apply_zoom_level(temp_f12, temp_f14, arg0, temp_a1);
//     camera_calc_yaw(arg0);
//     camera_calc_pitch(arg0);
//     camera_calc_relative_yaw(arg0);
//     arg0->unk5F0 = (s32) (arg0->unk5F0 | 4);
//     if ((g_level_id != 0x21) && (g_cutscene_slot_state != 1)) {
//         func_1512D560(arg0, 5, 0);
//         D_800C3600->unkC = (f32) arg0->unk37C;
//         func_1512D560(arg0, 8, D_800C3600);
//         func_1512D560(arg0, 6, 0);
//     }
// }
