#include <ultra64.h>

#include "functions.h"
#include "variables.h"


// game entrypoint
#ifdef NON_MATCHING
/* P281: readable C for func_15007830 (game entry point, compiled C, 128 insns; replaces the commented US draft
   below). Verified with difftest up to the N-th frame (DIFFTEST_STOPCALL on game_main_loop): the loop never returns. */
extern s32 D_800D3048;
extern OSMesgQueue D_800BEE30;   /* main message queue */
extern OSMesg D_800BEE48[16];
extern s16 D_800BEE88[];         /* two s16 fields at 0x00 and 0x20 */
extern u8 D_800BEA37;
extern u8 D_800BEA35;            /* frame state: 1-5 run the frame steps, 0 / 4 idle */
extern u8 D_800BEECA;
extern u8 D_800BEECB;
extern s16 D_800BEEC8;
extern s32 D_800BEE24;
extern s32 D_800BEE20;
extern s32 D_800BEE08;
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
void func_15008A60(void);
void save_block_realloc_random(void);
// game_main: the game thread's entry. Initialises the subsystems and the message queue, then loops forever: frame
// states 1 / 5 run menu_init, then (from 2) the frame update, the 0x81280783 hook in mode 2 and level_start_game
// with the low halves of D_800BEE24 / D_800BEE20 / D_800BE9F4, then (from 3) level_load and the state goes back
// to 0; every pass ends with sched_send_retrace_msg, D_800BEE08 = 0 and game_main_loop.
void func_15007830(void) {
    func_15007A20();
    D_800D3048 = 0;
    osCreateMesgQueue(&D_800BEE30, D_800BEE48, 16);
    D_800BEE88[0] = 2;
    D_800BEE88[0x10] = 2;
    D_800BEA37 = 0;
    sched_init(&D_800BEE30);
    texture_build_size_table();
    D_800BEECB = 0;
    audio_system_init();
    game_init_message_queues();
    level_build_flag_bitmask();
    game_clear_e9d00_flag();
    D_800BEEC8 = 0;
    controller_init_si_queue();
    controller_init_all();
    settings_reset_defaults();
    glyph_set_load_rom(0);
    func_15008A60();
    text_queue_reset();
    D_800BEA35 = 5;
    D_800BEE24 = 0;
    D_800BEE20 = 1;
    D_800BEECA = 1;
    save_block_realloc_random();
    while (TRUE) {
        switch (D_800BEA35) {
            case 1:
            case 5:
                menu_init();
                /* fallthrough */
            case 2:
                level_lights_clear();
                if (D_800E0B94 == 2) {
                    random_seed(0x81280783);
                }
                /* D_800BE9F4 is declared `u16 *` in variables.h; the code reads the low half of the word */
                level_start_game((s16) D_800BEE24, (s16) D_800BEE20, ((s16 *) &D_800BE9F4)[1]);
                /* fallthrough */
            case 3:
                level_load();
                D_800BEA35 = 0;
                break;
        }
        sched_send_retrace_msg();
        D_800BEE08 = 0;
        game_main_loop();
    }
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game/entrypoint/func_15007830.s")
#endif
// NON-MATCHING: need to better understand jump tables
// void func_15007830(void) {
//     func_15007A20();
//     D_800D2C28 = 0;
//     osCreateMesgQueue(&D_800BEA10, &D_800BEA28, 16);
//     D_800BEA68->unk0 = 2;
//     D_800BEA68->unk20 = 2;
//     D_800BE617 = 0;
//     sched_init(&D_800BEA10);
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
//     func_15008A60();
//     text_queue_reset();
//     D_800BEA04[0] = 0;
//     D_800BEA00[0] = 1;
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
//                 if (2 == D_800E0B94) {
//                     random_seed(0x81280783);
//                 }
//                 level_start_game(D_800BEA04[1], D_800BEA00[1], D_800BE9F4[1]);
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
