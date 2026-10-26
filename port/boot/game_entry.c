/* PC version of the game entrypoint game_thread_main (game/entrypoint.c is still GLOBAL_ASM), plus
 * the memory-model self-test (docs/port/MEMORY.md "Endianness test"). Compiled as a game TU, i.e.
 * through the vbe IR pass, so it has the N64's big-endian memory semantics.
 *
 * Translated from asm/nonmatchings/game/entrypoint/game_thread_main.s (EU symbols). The main loop's
 * switch is the asm jump table jtbl_80095DE0 read *from the ROM data* (game_data, loaded by
 * port_mem_load): its words are code labels inside game_thread_main, which the loader leaves as N64
 * addresses, so this file maps them back to the cases. */
#include <ultra64.h>
#include "../ultra/pc_mem.h"

void port_glog(const char *fmt, ...);
#define port_log port_glog /* format strings live in vbe game memory */
const char *port_gstr(const char *gamestr);

/* data (EU addresses; all live in the n64_rdram mirror) */
extern s32 g_segment_table, g_level_start_session_mode, g_level_start_player_mask, g_level_load_id, g_view_count_minus1; /* was D_800BE9F4; was D_800BEE08; was D_800BEE20; was D_800BEE24; was D_800D3048 */
extern OSMesgQueue g_game_main_queue; /* was D_800BEE30 */
extern OSMesg g_game_main_msgs[16]; /* was D_800BEE48 */
extern s16 g_gfx_done_msgs[]; /* was D_800BEE88 */
extern u8 g_gfx_vi_mode_pending, g_text_bank_lang, g_game_frame_state, g_render_level_world, g_game_mode; /* was D_800E0B94; was D_800BEA37; was D_800BEECB; was D_800BEA35; was D_800BEECA */
extern s16 g_gfx_tasks_pending; /* was D_800BEEC8 */

/* callees: prototypes must match the wasm signature of the definition (C body or stub) */
void game_bss_clear(void);
void sched_init(OSMesgQueue *);
void texture_build_size_table(void);
void audio_system_init(void);
void game_init_message_queues(void);
void level_build_flag_bitmask(void);
void game_clear_e9d00_flag(void);
void controller_init_si_queue(void);
void controller_init_all(void);
void settings_reset_defaults(void);
void glyph_set_load_rom(s32);
void view_zoom_state_reset(void);
void text_queue_reset(void);
void save_block_realloc_random(void);
void menu_init(void);
void level_lights_clear(void);
s32 random_seed(s32);
void level_start_game(s32, s32, s32);
void level_load(void);
void sched_send_retrace_msg(void);
void game_main_loop(void);

int port_entry_iterations;
void port_wait_frame(void); /* main-loop passes (for the log) */

/* P318: the game main loop game_thread_main is game C now (game/entrypoint.c, P281/P317); this PC translation of the asm is kept for A/B runs only (-DP318_ENTRY_PC_OLD) */
#ifdef P318_ENTRY_PC_OLD
void game_thread_main(void) {
    const u32 *jtbl = port_n64_to_wasm(0x80095DE0); /* jtbl_80095DE0_game, 5 entries */
    u32 target;

    port_log("[entry] game_thread_main (PC version) jtbl %08X %08X %08X %08X %08X\n", jtbl[0], jtbl[1],
             jtbl[2], jtbl[3], jtbl[4]);
    game_bss_clear();
    g_segment_table = 0;
    osCreateMesgQueue(&g_game_main_queue, g_game_main_msgs, 16);
    g_gfx_done_msgs[0] = 2;     /* sh 0x0(g_gfx_done_msgs) */
    g_gfx_done_msgs[0x10] = 2;  /* sh 0x20(g_gfx_done_msgs) */
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
    port_log("[entry] init sequence done, entering main loop (state %d)\n", g_game_frame_state);
    { /* session P9: texture_build_size_table (C) DMAs the texture bank at &D_1A3B40; texture 0xED0 inflates to 768 */
        extern s16 g_texture_expanded_sizes[];
        if (g_texture_expanded_sizes[0xED0] == 768 && g_texture_expanded_sizes[0] > 0) port_log("[romsym] size table PASS (tex 0xED0 = 768, tex 0 = %d)\n", g_texture_expanded_sizes[0]);
        else port_log("[romsym] size table FAIL (tex 0xED0 = %d, want 768)\n", g_texture_expanded_sizes[0xED0]);
    }
    for (;;) {
        u32 idx = (u32)g_game_frame_state - 1;
        target = idx < 5 ? jtbl[idx] : 0x1500797C;
        if (port_entry_iterations++ < 3)
            port_log("[entry] loop state %d -> case %08X\n", g_game_frame_state, target);
        switch (target) {
            case 0x1500793C:
                menu_init();
                /* fallthrough */
            case 0x15007944:
                level_lights_clear();
                if (g_game_mode == 2) random_seed(0x81280783);
                /* lh 0x2(...): the low halves of three s32 globals (mixed-width access) */
                level_start_game(((s16 *)&g_level_start_session_mode)[1], ((s16 *)&g_level_start_player_mask)[1], ((s16 *)&g_level_load_id)[1]);
                /* fallthrough */
            case 0x15007970:
                level_load();
                g_game_frame_state = 0;
                /* fallthrough */
            case 0x1500797C:
                break;
            default:
                port_log("[entry] jump-table word %08X is not a case label\n", target);
                return;
        }
        sched_send_retrace_msg();
        g_view_count_minus1 = 0;
        game_main_loop();
        port_wait_frame(); /* PC: the frame wait happens inside asm stubs today; pace one pass per frame */
    }
}
#endif /* P318_ENTRY_PC_OLD */
#ifndef P318_ENTRY_PC_OLD
/* P318: the game C main loop (game/entrypoint.c) ends each pass with game_main_loop. The PC version above paced one
 * pass per frame with port_wait_frame(); keep that pacing (same frame timing, so det=2 routes stay comparable) by
 * wrapping the pass's last call (port/Makefile -Wl,--wrap=game_main_loop; the main loop is its only caller). */
void __real_game_main_loop(void);
void __wrap_game_main_loop(void) {
    if (port_entry_iterations++ < 3) port_log("[entry] game C main loop pass %d (state %d)\n", port_entry_iterations, g_game_frame_state);
    __real_game_main_loop();
    port_wait_frame();
}
#endif

/* ---------------------------------------------------------------- memory-model self-test */

/* converted game functions (game_eu_CA630.c, game_eu_6EDC0.c) that read ROM-data fields */
s32 event_table_get_block(s32 i);  /* g_event_table[i].unk0  s32 (a pointer in the data: relocated); was D_800877D0 */
u16 event_table_get_u16_8(s32 i);  /* g_event_table[i].unk8  u16; was D_800877D0 */
s32 event_table_get_id_field(s32 i);  /* *(u16 *)(&g_event_table[i] + 0xA) & 0xFFF; was D_800877D0 */
s32 event_table_get_word4(s32 i);  /* g_event_table[i].unk4  s32; was D_800877D0 */
s32 dbgfont_char_index(u8 c);   /* index of c in the u8 table g_dbgfont_chars; was D_80084C60 */
#include "../stubs/memtest_expect.h"

static int fails;
static void check(const char *what, int i, u32 got, u32 want) {
    if (got != want) fails++;
    if (got != want || i < 2)
        port_log("[memtest] %-30s i=%-3d got %08X want %08X %s\n", port_gstr(what), i, got, want,
                 port_gstr(got == want ? "ok" : "FAIL"));
}

int port_memtest(void) {
    int k;
    static s32 word; /* mixed-width semantics on a word written by game code */
    word = 0x12345678;
    check("s32 read as s16[1] (lh +2)", 0, (u16)((s16 *)&word)[1], 0x5678);
    check("s32 read as u8[0] (lbu +0)", 0, ((u8 *)&word)[0], 0x12);
    ((u8 *)&word)[3] = 0x9A;
    check("u8[3] store then s32 read", 0, (u32)word, 0x1234569A);
    for (k = 0; k < MEMTEST_N; k++) {
        const MemtestRow *r = &memtest_rows[k];
        u32 p = (u32)event_table_get_block(r->i), n = port_wasm_to_n64((void *)p);
        check("event_table_get_block unk0 (ptr)", r->i, n ? n : p, r->unk0); /* relocated back to N64 */
        check("event_table_get_word4 unk4 s32", r->i, (u32)event_table_get_word4(r->i), r->unk4);
        check("event_table_get_u16_8 unk8 u16", r->i, event_table_get_u16_8(r->i), r->unk8);
        check("event_table_get_id_field (u16 +0xA)&0xFFF", r->i, (u32)event_table_get_id_field(r->i), r->unkA);
    }
    for (k = 0; k < MEMTEST_NC; k++)
        check("dbgfont_char_index u8 table", memtest_chars[k].c, (u32)dbgfont_char_index(memtest_chars[k].c), memtest_chars[k].idx);
    port_log("[memtest] %s (%d failures)\n", port_gstr(fails ? "FAIL" : "PASS"), fails);
    return fails;
}
