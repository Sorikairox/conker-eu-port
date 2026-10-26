#include <ultra64.h>

#include "functions.h"
#include "variables.h"


// game entrypoint
/* P281: readable C for game_thread_main (game entry point, compiled C, 128 insns; replaces the commented US draft
   below). Verified with difftest up to the N-th frame (DIFFTEST_STOPCALL on game_main_loop): the loop never returns. */
extern s32 g_segment_table; /* was D_800D3048 */
extern OSMesgQueue g_game_main_queue;   /* main message queue; was D_800BEE30 */
extern OSMesg g_game_main_msgs[16]; /* was D_800BEE48 */
extern s16 g_gfx_done_msgs[];         /* two s16 fields at 0x00 and 0x20; was D_800BEE88 */
extern u8 g_gfx_vi_mode_pending; /* was D_800BEA37 */
extern u8 g_game_frame_state;            /* frame state: 1-5 run the frame steps, 0 / 4 idle; was D_800BEA35 */
extern u8 g_render_level_world; /* was D_800BEECA */
extern u8 g_text_bank_lang; /* was D_800BEECB */
extern s16 g_gfx_tasks_pending; /* was D_800BEEC8 */
extern s32 g_level_start_session_mode; /* was D_800BEE24 */
extern s32 g_level_start_player_mask; /* was D_800BEE20 */
extern s32 g_view_count_minus1; /* was D_800BEE08 */
void texture_build_size_table(void);
void audio_system_init(void);
void level_build_flag_bitmask(void);
void game_clear_e9d00_flag(void);
void controller_init_all(void);
void settings_reset_defaults(void);
void glyph_set_load_rom(s16 idx);
void menu_init(void);
void level_lights_clear(void);
void random_seed(s32 arg0);
void level_load(void);
void game_main_loop(void);
void view_zoom_state_reset(void);
void save_block_realloc_random(void);
// game_main: the game thread's entry. Initialises the subsystems and the message queue, then loops forever: frame
// states 1 / 5 run menu_init, then (from 2) the frame update, the 0x81280783 hook in mode 2 and level_start_game
// with the low halves of g_level_start_session_mode / g_level_start_player_mask / g_level_load_id, then (from 3) level_load and the state goes back
// to 0; every pass ends with sched_send_retrace_msg, g_view_count_minus1 = 0 and game_main_loop.
/* was func_15007830 */
void game_thread_main(void) {
    game_bss_clear();
    g_segment_table = 0;
    osCreateMesgQueue(&g_game_main_queue, g_game_main_msgs, 16);
    g_gfx_done_msgs[0] = 2;
    g_gfx_done_msgs[0x10] = 2;
    g_gfx_vi_mode_pending = 0;
    sched_init(&g_game_main_queue);
    texture_build_size_table();
    g_text_bank_lang = 0;
    audio_system_init();
    game_init_message_queues();
    level_build_flag_bitmask();
    game_clear_e9d00_flag();
    g_gfx_tasks_pending = 0;
    controller_init_si_queue();
    controller_init_all();
    settings_reset_defaults();
    glyph_set_load_rom(0);
    view_zoom_state_reset();
    text_queue_reset();
    g_game_frame_state = 5;
    g_level_start_session_mode = 0;
    g_level_start_player_mask = 1;
    g_render_level_world = 1;
    save_block_realloc_random();
    while (TRUE) {
        switch (g_game_frame_state) {
            case 1:
            case 5:
                menu_init();
                /* fallthrough */
            case 2:
                level_lights_clear();
                if (g_game_mode == 2) {
                    random_seed(0x81280783);
                }
                /* g_level_load_id is declared `u16 *` in variables.h; the code reads the low half of the word */
                level_start_game((s16) g_level_start_session_mode, (s16) g_level_start_player_mask, ((s16 *) &g_level_load_id)[1]);
                /* fallthrough */
            case 3:
                level_load();
                g_game_frame_state = 0;
                break;
        }
        sched_send_retrace_msg();
        g_view_count_minus1 = 0;
        game_main_loop();
    }
}
// NON-MATCHING: need to better understand jump tables
// void game_thread_main(void) {
//     game_bss_clear();
//     D_800D2C28 = 0;
//     osCreateMesgQueue(&g_frame_dt_history_2, &D_800BEA28, 16);
//     g_view_widths_3->unk0 = 2;
//     g_view_widths_3->unk20 = 2;
//     D_800BE617 = 0;
//     sched_init(&g_frame_dt_history_2);
//     texture_build_size_table();
//     D_800BEAAB = 0;
//     audio_system_init();
//     game_init_message_queues();
//     level_build_flag_bitmask();
//     func_151EEFF0();
//     D_800BEAA8 = 0;
//     controller_init_si_queue();
//     controller_init_all();
//     func_151DD970();
//     func_15015920(0);
//     view_zoom_state_reset();
//     text_queue_reset();
//     D_800BEA04[0] = 0;
//     g_frame_phase_accum[0] = 1;
//     D_800BE615 = 5;
//     D_800BEAAA = 1;
//     save_block_realloc_random();
//     do {
//         switch(D_800BE615) {
//             case 0:
//             case 4:
//                 func_151E50C8();
//             case 1:
//                 level_lights_clear();
//                 if (2 == g_game_mode) {
//                     random_seed(0x81280783);
//                 }
//                 level_start_game(D_800BEA04[1], g_frame_phase_accum[1], g_level_load_id[1]);
//             case 2:
//                 level_load();
//                 D_800BE615 = 0U;
//             case 3:
//                 sched_send_retrace_msg();
//                 D_800BE9E8 = 0;
//                 game_main_loop();
//         }
//     } while (1);
// }
