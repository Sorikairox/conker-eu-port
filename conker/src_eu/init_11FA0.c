#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* was func_10011FA0 */
void audio_mixer_request_mode(s32 *arg0) {
    D_80042770 = arg0;
}

/* was func_10011FB0 */
void audio_mixer_set_override_mode(s32 arg0) {
    s32 tmp = D_80042774;
    if (tmp == 3) {
        D_80041FD9 = 1;
    }
    D_80042774 = arg0;
}

/* was func_10011FDC */
void audio_mixer_set_base_mode(s32 arg0) {
    D_80042778 = arg0;
}

/* was func_10011FEC */
void audio_mixer_reset_modes(void) {
    D_80042770 = D_80042774 = D_80042778 = D_8004277C = 0;
}

// s129: music mixer per frame (mode from D_80042770/74/78: 1..5 set the master volume (music_player_set_master_gain, 3 buses)
// and voice 0/1 frequency + volume targets (music_player_set_voice_param params 9/8)); written from asm. Every declared local
// gets a stack slot at -O2, so the declaration order (mode, master, i, vol, freq, scale) fixes the frame.
extern s32 D_8002BD68;
f32 sinf(f32);

typedef struct {
    f32 v[2];
} F2_11FA0;

extern f32 D_80042B20[2]; // current frequency per voice
extern f32 D_80042B28[2]; // current volume per voice
extern f32 D_80042B30;
extern f32 D_80042B34;
extern f32 D_80042B38;

/* was func_10012020 */
void audio_mixer_update_frame(void) {
    s32 mode;
    f32 master;
    s32 i;
    F2_11FA0 vol;
    F2_11FA0 freq;
    f32 scale;

    master = 0.0f;
    vol = *(F2_11FA0 *)&D_8002BD60;
    freq = *(F2_11FA0 *)&D_8002BD68;
    mode = D_80042770;
    if ((*(s32 *)((u8 *)D_800DBFF0 + 0x5F0) & 1) && !(((u8 *)D_800B0DF0)[0x2A] & 1)) {
        mode = 1;
    }
    if (D_80042774 != 0) {
        mode = D_80042774;
    } else if (D_80042778 != 0) {
        mode = D_80042778;
    }
    if (mode == 6) {
        mode = 0;
    }
    switch (mode) {
        case 1:
            D_8004277C = 0;
            master = (13.0f - D_80042B30) + D_80042B30;
            vol.v[0] = 127.0f;
            freq.v[0] = D_80042B20[0] + ((519.0f + sinf(D_80042B38 * 0.05235988f) * 200.0f) - D_80042B20[0]);
            break;
        case 2:
            D_8004277C = 0;
            master = 70.0f;
            vol.v[0] = 127.0f;
            freq.v[0] = sinf(D_80042B38 * 0.34906584f) * 200.0f + 450.0f;
            break;
        case 3:
            D_8004277C = 0;
            master = (52.0f - D_80042B30) * 0.08f + D_80042B30;
            vol.v[0] = D_80042B28[0] + (127.0f - D_80042B28[0]) * 0.08f;
            freq.v[0] = D_80042B20[0] + ((436.0f + sinf(D_80042B38 * 0.12217305f) * 282.0f) - D_80042B20[0]) * 0.08f;
            D_80041FD9 = 0;
            break;
        case 4:
            D_8004277C = 4;
            vol.v[1] = 127.0f;
            if (D_800BE9B4) {
                freq.v[1] = 400.0f;
            } else {
                freq.v[1] = D_80042B20[1] + (400.0f - D_80042B20[1]);
            }
            D_80041FD9 = 0;
            break;
        case 5:
            vol.v[1] = 127.0f;
            freq.v[1] = 520.0f;
            D_80041FD9 = 0;
            break;
        default:
            if (D_8004277C == 4) {
                freq.v[1] = D_80042B20[1] + (11000.0f - D_80042B20[1]) * 0.05f;
                if (freq.v[1] < 9000.0f) {
                    D_8004277C = 4;
                } else {
                    D_8004277C = 0;
                    D_80041FD9 = 1;
                }
            }
            break;
    }
    D_80042B38 += D_800BE9A4;
    if (master != D_80042B30 || D_80042B34 != 1.0f) {
        scale = master / 127.0f;
        for (i = 0; i < 3; i++) {
            music_player_set_master_gain(i, scale, 1.0f);
        }
        D_80042B30 = master;
        D_80042B34 = 1.0f;
    }
    for (i = 0; i < 2; i++) {
        if (freq.v[i] != D_80042B20[i]) {
            music_player_set_voice_param(i, i, 9, 0, freq.v[i]);
            D_80042B20[i] = freq.v[i];
        }
        if (vol.v[i] != D_80042B28[i]) {
            music_player_set_voice_param(i, i, 8, 0, vol.v[i]);
            D_80042B28[i] = vol.v[i];
        }
    }
    D_80042770 = 0;
}
