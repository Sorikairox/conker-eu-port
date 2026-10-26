#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* P98: g_mp3_log_callback callback (mp3main_decode_next_frame calls it with (0, line, length)); a1 / a2 reach ring_buffer_put_record untouched */
/* was func_10012560 */
void mp3_id3_text_enqueue(s32 arg0, u8 *arg1, s32 arg2) {
    ring_buffer_put_record(&g_mp3_text_queue, arg1, arg2);
}

/* was func_10012588 */
void mp3_voice_init(s32 arg0) {
    audio_fx_mixer_init(arg0);
    ring_buffer_init(&g_mp3_text_queue, &g_mp3_text_queue_buf, 64);
    mp3_stream_set_text_cb(mp3_id3_text_enqueue);
}

/* was func_100125CC */
void mp3_voice_stop(s32 arg0) {
    s32 res = mp3_stream_get_state();
    if ((arg0 != 30) || (g_level_loaded_id != 27)) {
        if (res == 1) {
            mp3_stream_set_volume(0, 11010);
            return;
        }
        if (res != 0) {
            mp3_stream_stop();
        }
    }
}

/* was func_1001263C */
void mp3_voice_play(s32 arg0, s32 arg1, s32 arg2) {
    s32 temp_v0;
    s32 sp18;

    sp18 = 0;
    temp_v0 = asset_lookup_rom(&sp18, 2, 22, arg0);
    g_mp3_voice_last_id = (s16) arg0;
    if ((temp_v0 != 0) && (sp18 != 0)) {
        mp3_stream_set_volume(arg1, 0);
        mp3_stream_set_pan(arg2, 1);
        if (arg0 != 0xD2) {
            mp3_stream_set_fx(10, 11000);
        } else {
            mp3_stream_set_fx(0, 0);
        }
        mp3_stream_start(temp_v0, sp18);
    }
}

// text_queue_read: takes the next record of the text queue g_mp3_text_queue into the buffer arg0 (at most arg1 bytes,
// ring_buffer_get_record) and returns its length (P182: the asm caller lipsync_poll_text_queue loops while it is non-zero; it was void).
/* was func_100126E8 */
s32 text_queue_read(s32 arg0, s32 arg1) {
    return ring_buffer_get_record(&g_mp3_text_queue, arg0, arg1);
}

/* was func_10012718 */
s32 mp3_voice_play_at_object(u16 arg0, struct127 *arg1, s32 arg2, s16 arg3, u16 arg4) {
    s32 sp3C;
    s32 sp38;
    s32 sp34;

    if (arg1->camera != 0) {
        mp3_voice_play(arg0, arg2, 64);
    } else {
        sound_source_mix(arg1->x_position, arg1->y_position, arg1->z_position, arg2, arg4, arg3, &sp3C, &sp38, &sp34);
        mp3_voice_play(arg0, sp38, sp3C);
    }
    return 1;
}

/* was func_100127D0 */
s32 mp3_voice_is_playing(void) {
    s32 tmp = mp3_stream_get_state();

    if (tmp == 1 || tmp == 2 || tmp == 5) {
        return 1;
    }
    return 0;
}
