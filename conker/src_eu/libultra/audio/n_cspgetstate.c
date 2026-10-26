#include <n_libaudio.h>

// EU: built with -O2 (see Makefile), with two empty functions after it.

s32 n_alCSPGetState(N_ALCSPlayer *seqp) {
    return seqp->state;
}

void ptstart(void) {
}

/* was func_eu_10017D80 */
void audio_csp_stub_eu(void) {
}
