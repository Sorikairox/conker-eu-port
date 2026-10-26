#include <ultra64.h>

#include "functions.h"
#include "variables.h"


/* was func_1001E4A0 */
s32 n_synth_aux_fx_new(s16 arg0, s32 arg1, s32 arg2) {
    n_alFxNew(&g_audio_synth->unk48[arg0].unk20, arg1, arg0, arg2);
    return g_audio_synth->unk48[arg0].unk20;
}
