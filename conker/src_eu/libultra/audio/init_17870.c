#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* was func_10017870 */
void audio_set_output_mode(u8 arg0) {
    s32 i;

    g_audio_surround = (u8)0;
    g_audio_mono = (u8)0;
    g_audio_headphones = (u8)0;

    switch (arg0) {

        case 1:
            g_audio_mono = (u8)1;
            break;
        case 3:
            g_audio_headphones = (u8)1;
            break;
        case 4:
            g_audio_surround = (u8)1;
            break;
    }

    for(i = 0; i < 2; i++) {
        audio_set_bus_mix_type(i, 0);
    }
}

/* was func_10017944 */
void audio_set_bus_mix_type(s32 arg0, u32 arg1) {
    if (arg1 == 0) {
        arg1 = g_audio_bus_mix_type[arg0];
    }

    g_audio_bus_one_side[arg0] = 0;
    g_audio_bus_invert[arg0] = 0;

    switch (arg1)
    {
        case 2:
            if (g_audio_surround != 0) {
                g_audio_bus_invert[arg0] = 1;
            }
            break;
        case 3:
            if (g_audio_surround != 0) {
                g_audio_bus_one_side[arg0] = 1;
            }
            break;
        case 4:
            if (g_audio_mono == 0) {
                g_audio_bus_one_side[arg0] = 1;
            }
            break;
        case 5:
            if (g_audio_mono == 0) {
                g_audio_bus_one_side[arg0] = 1;
                g_audio_bus_invert[arg0] = 1;
            }
            break;
    }

    g_audio_bus_mix_type[arg0] = arg1;
}
