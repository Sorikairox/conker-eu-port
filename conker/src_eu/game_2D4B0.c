#include <ultra64.h>

#include "functions.h"
#include "variables.h"

/* was func_15000000 */
void game_init_message_queues(void) {
    OSMesgQueue *msgQueue;
    s32 i;

    for (i = 0; i < 3; i++)
    {
        msgQueue = &D_80041E58[i];
        osCreateMesgQueue(msgQueue, &D_80041EA0[i], 8);
        music_player_set_msg_queue(i, msgQueue);
    }

    music_stub_noop3(0, 6, 1); // stub function
    music_system_reset();
}

/* was func_15000090 */
void level_music_stop_all(void) {
    music_release_stopped_slots();
}

#ifdef NON_MATCHING
void music_release_stopped_slots(void);
void music_song_set_volume(s32 arg0, s32 arg1);
void music_song_set_fade(s32 arg0, s32 arg1, s32 arg2);
s32 music_song_set_chans_level(s32 arg0, s32 arg1, s32 arg2, s32 arg3);
void audio_set_bus_mix_type(s32 arg0, u32 arg1);
void music_set_all_paused(s32 arg0);
s32 music_get_playing_songs(s32 *arg0);
void music_stop_song(s32 arg0, s32 arg1);
void music_play_song(s32 arg0, s32 arg1, s32 arg2);
extern s8 D_800422A0;

// Level music block, level header (D_800B0DF0) +0x2C..+0x39.
typedef struct {
    s16 songA;  // +0x0: first song (< 0: none, 0: silence)
    u16 volA;   // +0x2: music_song_set_volume
    u16 fadeA;  // +0x4: music_song_set_chans_level
    s16 songB;  // +0x6: second song
    u16 volB;   // +0x8
    u16 fadeB;  // +0xA
    u8  mode;   // +0xC: 0..4, how songs already playing are handled
    u8  unkD;   // +0xD: audio_set_bus_mix_type(1, ...)
} LevelMusic;

// Level start: request the level's songs. Songs already playing that the level wants are kept (volume and
// fade set again); the rest are stopped, oldest-slot songs reused for the new ones.
/* was func_150000B0 */
void level_start_music(void) {
    LevelMusic m;
    s32 playing[3];
    s32 restart;
    s32 count;
    s32 needed;
    s32 excess;
    s32 slot;
    s32 i;
    s32 j;
    s32 *p;

    needed = 0;
    restart = FALSE;
    D_800422A0 = 0;
    if (D_800B0DF0 != NULL) {
        m = *(LevelMusic *) ((u8 *) D_800B0DF0 + 0x2C);
    } else {
        m.mode = 1;
        m.volA = 0;
        m.volB = 0;
        m.unkD = 2;
        m.songA = 0;
        m.songB = 0;
    }
    D_80041F04 = 0;
    D_80041F08 = 0;
    D_80041F0C = 0;

    if (m.songA == 1 && (D_800D2E4C->unk4 & 0x80)) {
        m.fadeA = 0x10;
        m.songA = 0x46;
    }

    switch (m.mode) {
    case 0:
    case 4:
        music_release_stopped_slots();
        break;
    case 2:
        restart = TRUE;
        music_release_stopped_slots();
        break;
    case 3:
        restart = TRUE;
        /* fallthrough */
    case 1:
        if (D_800BE9B4 == 2) {
            music_release_stopped_slots();
        } else if (D_800BE9F8 != 0x22) {
            restart = FALSE;
            m.songA = -1;
            m.songB = -1;
        }
        break;
    }

    count = music_get_playing_songs(playing);
    for (i = count; i < 3; i++) {
        playing[i] = -1;
    }

    // Mode 4: when song B is already playing (and song A is not), it becomes the first song.
    if (m.mode == 4 && m.songB >= 0) {
        for (i = 0; i < 3; i++) {
            if (m.songB == playing[i]) {
                if (m.songA >= 0) {
                    for (j = 0; j < 3; j++) {
                        if (m.songA == playing[j]) {
                            m.songB = 0;
                        }
                    }
                }
                if (m.songB >= 0) {
                    m.songA = m.songB;
                    m.fadeA = m.fadeB;
                    m.volA = m.volB;
                }
            }
        }
        if (m.songB >= 0) {
            m.songB = 0;
        }
    }

    music_set_all_paused(0);

    if (!restart) {
        // Keep the wanted songs that are already playing.
        for (i = 0; i < 3; i++) {
            if (playing[i] == -1) {
                continue;
            }
            if (m.songA == playing[i]) {
                music_song_set_chans_level(m.songA, 0, m.fadeA, 0);
                music_song_set_chans_level(m.songA, 100, m.fadeA ^ 0xFFFF, 0);
                music_song_set_volume(m.songA, m.volA);
                music_song_set_fade(m.songA, 0x7FFF, 0);
                playing[i] = -1;
                m.songA = -1;
                count--;
            } else if (m.songB == playing[i]) {
                music_song_set_chans_level(m.songB, 0, m.fadeB, 0);
                music_song_set_chans_level(m.songB, 100, m.fadeB ^ 0xFFFF, 0);
                music_song_set_volume(m.songB, m.volB);
                music_song_set_fade(m.songB, 0x7FFF, 0);
                playing[i] = -1;
                m.songB = -1;
                count--;
            }
        }
    }

    // Stop the songs that are not needed, newest slot first.
    if (m.songA >= 0) {
        needed = 1;
    }
    if (m.songB >= 0) {
        needed++;
    }
    if (count != 0 && needed < count) {
        excess = count - needed;
        if (excess != 0) {
            for (p = &playing[2]; p >= playing && excess != 0; p--) {
                if (*p != -1) {
                    music_stop_song(*p, 4);
                    *p = -1;
                    excess--;
                }
            }
        }
    }

    // Start song A in place of the last song still playing (or fresh).
    if (m.songA >= 0) {
        slot = -1;
        for (i = 0; i < 3; i++) {
            if (playing[i] != -1) {
                slot = i;
            }
        }
        if (slot == -1) {
            if (m.songA > 0) {
                music_play_song(m.songA, 0, 0);
            }
        } else {
            if (m.songA > 0) {
                music_play_song(m.songA, playing[slot], 5);
            } else {
                music_stop_song(playing[slot], 4);
            }
            playing[slot] = -1;
        }
        if (m.songA > 0) {
            music_song_set_chans_level(m.songA, 0, m.fadeA, 0);
            music_song_set_volume(m.songA, m.volA);
        }
    }

    if (m.songB >= 0) {
        slot = -1;
        for (i = 0; i < 3; i++) {
            if (playing[i] != -1) {
                slot = i;
            }
        }
        if (slot == -1) {
            if (m.songB > 0) {
                music_play_song(m.songB, 0, 0);
            }
        } else {
            if (m.songB > 0) {
                music_play_song(m.songB, playing[slot], 5);
            } else {
                music_stop_song(playing[slot], 4);
            }
            playing[slot] = -1;
        }
        if (m.songB > 0) {
            music_song_set_chans_level(m.songB, 0, m.fadeB, 0);
            music_song_set_volume(m.songB, m.volB);
        }
    }

    audio_set_bus_mix_type(1, m.unkD);
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_2D4B0/level_start_music.s")
#endif

#ifdef NON_MATCHING
extern f32 D_800D9F3C;            /* screen height (D_800B0DF0->unk0) */
extern f32 D_800D9F40;            /* screen width (D_800B0DF0->unk2) */
extern f32 D_800D3A90;
extern u8 D_800D9FA4[3];
extern u8 D_800D9FA8[3];
extern u8 D_800D9FAB;
extern u8 D_800D9FAC;
extern u8 D_800DA240;
extern s32 D_800DA230[];
extern u8 D_800D9FF0[][2][8];
extern f32 D_800D9EE0[][3];       /* per player, 0xC each: first float = -1 (no request) */
extern u8 D_800D9F10;
extern f32 D_800D9F18[][2];       /* per player projection request: first float = -1 (none) */
extern u8 D_800D9F38;             /* projection request count / pending flag */
void level_init_color_tables(s32 arg0);
s32 light_alloc_light_buf(s32 arg0);

/* Per-level setup of the screen / projection-request state: screen size floats, level_init_color_tables, clear the
 * D_800D9F88 / D_800D9F98 4x3 tables and the small flags, then per player (0..D_80082FA0): D_800DA230 handle,
 * D_800D9FF0 colour slots = 0xFF, D_800D9EE0 / D_800D9F18 requests = -1, and the request counters to 0.
 * arg0 (the level, D_800BE9F0) is passed through to level_init_color_tables in a0. The asm returns a stale v0 (callers ignore it). */
/* was func_150006E0 */
s32 level_setup_screen_projection(s32 arg0) {
    s32 i, j;

    D_800D9F40 = (f32)D_800B0DF0->unk2;
    D_800D9F3C = (f32)D_800B0DF0->unk0;
    D_800D3A90 = 100.0f - D_800D9F3C;
    level_init_color_tables(arg0);
    for (i = 0; i < 4; i++) {
        for (j = 0; j < 3; j++) {
            D_800D9F88[i * 3 + j] = 0;
            D_800D9F98[i * 3 + j] = 0;
        }
    }
    for (i = 0; i < 3; i++) {
        D_800D9FA4[i] = 0;
        D_800D9FA8[i] = 0;
    }
    D_800D9FAB = 0xFF;
    D_800D9FAC = 0xFF;
    D_800DA240 = 0xB;
    for (i = 0; i <= D_80082FA0; i++) {
        D_800DA230[i] = light_alloc_light_buf(D_800DA240);
    }
    for (i = 0; i <= D_80082FA0; i++) {
        for (j = 0; j < 2; j++) {
            D_800D9FF0[i][j][4] = 0xFF;
            D_800D9FF0[i][j][0] = 0xFF;
            D_800D9FF0[i][j][5] = 0xFF;
            D_800D9FF0[i][j][1] = 0xFF;
            D_800D9FF0[i][j][6] = 0xFF;
            D_800D9FF0[i][j][2] = 0xFF;
        }
    }
    for (i = 0; i <= D_80082FA0; i++) {
        D_800D9EE0[i][0] = -1.0f;
    }
    D_800D9F10 = 0;
    for (i = 0; i <= D_80082FA0; i++) {
        D_800D9F18[i][0] = -1.0f;
    }
    D_800D9F38 = 0;
    return 0;
}
#else
#pragma GLOBAL_ASM("asm/nonmatchings/game_2D4B0/level_setup_screen_projection.s")
#endif
// NON-MATCHING: almost only reg remaining
// void level_setup_screen_projection(void) {
//     s32 i;
//     s32 j;
//
//     D_800D9B20 = D_800B0DF0->unk2;
//     D_800D9B1C = D_800B0DF0->unk0;
//     D_800D3670 = 100.0f - D_800D9B1C;
//
//     level_init_color_tables();
//
//     // downhill from here!
//     for (i = 0; i < 4; i++) {
//         for (j = 0; j < 3; j++) {
//             D_800D9B68[i][j] = 0;
//             D_800D9B78[i][j] = 0;
//         }
//     }
//
//     for (i = 0; i < 3; i++) {
//         D_800D9B84[i] = 0;
//         D_800D9B88[i] = 0;
//     }
//
//     D_800D9B8B = 0xFF;
//     D_800D9B8C = 0xFF;
//     D_800D9E20 = 0xBU;
//
//     for (i = 0; i <= D_80082FA0; i++) {
//         D_800D9E10[i] = func_1515D480(D_800D9E20);
//     }
//
//     for (i = 0; i <= D_80082FA0; i++) {
//         for (j = 0; j < 2; j++) {
//             D_800D9BD0[i][j][4] = 0xff;
//             D_800D9BD0[i][j][0] = 0xff;
//             D_800D9BD0[i][j][5] = 0xff;
//             D_800D9BD0[i][j][1] = 0xff;
//             D_800D9BD0[i][j][6] = 0xff;
//             D_800D9BD0[i][j][2] = 0xff;
//         }
//     }
//
//     for (i = 0; i <= D_80082FA0; i++) {
//         D_800D9AC0[i].unk0 = -1.0f;
//     }
//
//     D_800D9AF0 = 0;
//     for (i = 0; i <= D_80082FA0; i++) {
//         D_800D9AF8[i].unk0 = -1.0f;
//     }
//     D_800D9B18 = 0;
// }
