#include <ultra64.h>
#include "functions.h"
#include "variables.h"


void mp3_stream_stop(void);
void mp3_stream_set_volume(s32, s32);
extern s32 D_800D3C60;

/* was func_1509EB20 */
s32 event_action_stream(s32 arg0, s32 arg1, u8 *arg2) {
    s32 var_a1;

    switch (arg1) {                                 /* irregular */
    case 0:
        var_a1 = 0x7FFF;
        if (D_800D3C60 >= 3) {
            var_a1 = (*(s32 *)((u8 *)arg2 + 8));
        }
        mp3_voice_play(arg0, var_a1, 0x40);
        return 1;
    case 1:
        if (D_800D3C60 == 4) {
    s32 pad;
            mp3_stream_set_volume((*(s32 *)((u8 *)arg2 + 8)), (*(s32 *)((u8 *)arg2 + 0xC)));
            return 1;
        }
        mp3_stream_set_volume((*(s32 *)((u8 *)arg2 + 8)), 0);
        return 1;
    case 2:
        mp3_stream_stop();
        return 1;
    default:
        return 0;
    }
}
/* was func_1509EBD0 */
s32 event_query_stream(s32 arg0, s32 arg1, s32 arg2) {
    s32 ret = 0;

    if (arg1 == 3) {
        return mp3_stream_get_state() == 1;
    }
    return ret;
}

void music_play_song(s32, s32, s32);
void music_stop_song(s32, s32);
extern s32 D_800D3C60;

/* was func_1509EC10 */
s32 event_action_music(s32 arg0, u32 arg1, u8 *arg2) {
    s32 temp_a0;
    s32 var_a1;

    switch (arg1) {
    case 0:
        music_play_song(arg0 & 0xFFF, (*(s32 *)((u8 *)arg2 + 8)), (*(s32 *)((u8 *)arg2 + 0xC)));
        return 1;
    case 2:
        music_song_set_fade(arg0 & 0xFFF, (*(s32 *)((u8 *)arg2 + 8)), 0);
        return 1;
    case 5:
        music_song_set_fade(arg0 & 0xFFF, (*(s32 *)((u8 *)arg2 + 8)), 1);
        return 1;
    case 1:
        music_stop_song(arg0 & 0xFFF, (*(s32 *)((u8 *)arg2 + 8)));
        return 1;
    case 3:
        if (D_800D3C60 == 5) {
            return music_song_set_chans_level(arg0 & 0xFFF, (*(s32 *)((u8 *)arg2 + 8)), (*(s32 *)((u8 *)arg2 + 0xC)), (*(s32 *)((u8 *)arg2 + 0x10)));
        }
        return music_song_set_chans_level(arg0 & 0xFFF, (*(s32 *)((u8 *)arg2 + 8)), (*(s32 *)((u8 *)arg2 + 0xC)), 0x3C);
    case 4:
        temp_a0 = arg0 & 0xFFF;
        if (D_800D3C60 == 5) {
            return music_song_set_marker(arg0 & 0xFFF, (*(s32 *)((u8 *)arg2 + 8)), (*(s32 *)((u8 *)arg2 + 0xC)), (*(s32 *)((u8 *)arg2 + 0x10)) & 0xFFF);
        }
        return music_song_set_marker(temp_a0, (*(s32 *)((u8 *)arg2 + 8)), (*(s32 *)((u8 *)arg2 + 0xC)), temp_a0);
    case 6:
        var_a1 = 1;
        if (D_800D3C60 == 3) {
            var_a1 = (*(s32 *)((u8 *)arg2 + 8));
        }
        music_song_set_paused(arg0 & 0xFFF, var_a1);
        return 1;
    default:
        return 0;
    }
}
/* was func_1509ED80 */
s32 event_query_music(s32 arg0, s32 arg1, s32 arg2) {
    switch (arg1) {
    case 7:
        return music_song_is_playing(arg0);
    case 8:
        return music_song_get_player_flags(arg0);
    }
    return 0;
}
