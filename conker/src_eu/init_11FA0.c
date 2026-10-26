#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* was func_10011FA0 */
void audio_mixer_request_mode(s32 *arg0) {
    g_audio_mixer_req_mode = arg0;
}

/* was func_10011FB0 */
void audio_mixer_set_override_mode(s32 arg0) {
    s32 tmp = g_audio_mixer_override_mode;
    if (tmp == 3) {
        g_sound_default_fx_mode = 1;
    }
    g_audio_mixer_override_mode = arg0;
}

/* was func_10011FDC */
void audio_mixer_set_base_mode(s32 arg0) {
    g_audio_mixer_base_mode = arg0;
}

/* was func_10011FEC */
void audio_mixer_reset_modes(void) {
    g_audio_mixer_req_mode = g_audio_mixer_override_mode = g_audio_mixer_base_mode = g_audio_mixer_fade_mode = 0;
}

// s129: music mixer per frame (mode from g_audio_mixer_req_mode/74/78: 1..5 set the master volume (music_player_set_master_gain, 3 buses)
// and voice 0/1 frequency + volume targets (music_player_set_voice_param params 9/8)); written from asm. Every declared local
// gets a stack slot at -O2, so the declaration order (mode, master, i, vol, freq, scale) fixes the frame.
extern s32 g_audio_mixer_default_freq; /* was D_8002BD68 */
f32 sinf(f32);

typedef struct {
    f32 v[2];
} F2_11FA0;

extern f32 g_audio_mixer_voice_freq[2]; /* was D_80042B20 */ // current frequency per voice
extern f32 g_audio_mixer_voice_vol[2]; /* was D_80042B28 */ // current volume per voice
extern f32 g_audio_mixer_master; /* was D_80042B30 */
extern f32 g_audio_mixer_master_scale; /* was D_80042B34 */
extern f32 g_audio_mixer_time; /* was D_80042B38 */

/* was func_10012020 */
void audio_mixer_update_frame(void) {
    s32 mode;
    f32 master;
    s32 i;
    F2_11FA0 vol;
    F2_11FA0 freq;
    f32 scale;

    master = 0.0f;
    vol = *(F2_11FA0 *)&g_audio_mixer_default_vol;
    freq = *(F2_11FA0 *)&g_audio_mixer_default_freq;
    mode = g_audio_mixer_req_mode;
    if ((*(s32 *)((u8 *)g_player_views + 0x5F0) & 1) && !(((u8 *)g_level_header)[0x2A] & 1)) {
        mode = 1;
    }
    if (g_audio_mixer_override_mode != 0) {
        mode = g_audio_mixer_override_mode;
    } else if (g_audio_mixer_base_mode != 0) {
        mode = g_audio_mixer_base_mode;
    }
    if (mode == 6) {
        mode = 0;
    }
    switch (mode) {
        case 1:
            g_audio_mixer_fade_mode = 0;
            master = (13.0f - g_audio_mixer_master) + g_audio_mixer_master;
            vol.v[0] = 127.0f;
            freq.v[0] = g_audio_mixer_voice_freq[0] + ((519.0f + sinf(g_audio_mixer_time * 0.05235988f) * 200.0f) - g_audio_mixer_voice_freq[0]);
            break;
        case 2:
            g_audio_mixer_fade_mode = 0;
            master = 70.0f;
            vol.v[0] = 127.0f;
            freq.v[0] = sinf(g_audio_mixer_time * 0.34906584f) * 200.0f + 450.0f;
            break;
        case 3:
            g_audio_mixer_fade_mode = 0;
            master = (52.0f - g_audio_mixer_master) * 0.08f + g_audio_mixer_master;
            vol.v[0] = g_audio_mixer_voice_vol[0] + (127.0f - g_audio_mixer_voice_vol[0]) * 0.08f;
            freq.v[0] = g_audio_mixer_voice_freq[0] + ((436.0f + sinf(g_audio_mixer_time * 0.12217305f) * 282.0f) - g_audio_mixer_voice_freq[0]) * 0.08f;
            g_sound_default_fx_mode = 0;
            break;
        case 4:
            g_audio_mixer_fade_mode = 4;
            vol.v[1] = 127.0f;
            if (g_level_first_frame) {
                freq.v[1] = 400.0f;
            } else {
                freq.v[1] = g_audio_mixer_voice_freq[1] + (400.0f - g_audio_mixer_voice_freq[1]);
            }
            g_sound_default_fx_mode = 0;
            break;
        case 5:
            vol.v[1] = 127.0f;
            freq.v[1] = 520.0f;
            g_sound_default_fx_mode = 0;
            break;
        default:
            if (g_audio_mixer_fade_mode == 4) {
                freq.v[1] = g_audio_mixer_voice_freq[1] + (11000.0f - g_audio_mixer_voice_freq[1]) * 0.05f;
                if (freq.v[1] < 9000.0f) {
                    g_audio_mixer_fade_mode = 4;
                } else {
                    g_audio_mixer_fade_mode = 0;
                    g_sound_default_fx_mode = 1;
                }
            }
            break;
    }
    g_audio_mixer_time += g_frame_step_f;
    if (master != g_audio_mixer_master || g_audio_mixer_master_scale != 1.0f) {
        scale = master / 127.0f;
        for (i = 0; i < 3; i++) {
            music_player_set_master_gain(i, scale, 1.0f);
        }
        g_audio_mixer_master = master;
        g_audio_mixer_master_scale = 1.0f;
    }
    for (i = 0; i < 2; i++) {
        if (freq.v[i] != g_audio_mixer_voice_freq[i]) {
            music_player_set_voice_param(i, i, 9, 0, freq.v[i]);
            g_audio_mixer_voice_freq[i] = freq.v[i];
        }
        if (vol.v[i] != g_audio_mixer_voice_vol[i]) {
            music_player_set_voice_param(i, i, 8, 0, vol.v[i]);
            g_audio_mixer_voice_vol[i] = vol.v[i];
        }
    }
    g_audio_mixer_req_mode = 0;
}
