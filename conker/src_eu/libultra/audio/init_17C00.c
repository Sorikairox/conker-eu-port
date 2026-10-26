#include <n_libaudio.h>


/* was func_10017C00 */
void n_csp_unmute_chan(N_ALCSPlayer *seqp, s32 arg1) {
    seqp->chanMask |= 1 << arg1;
    n_csp_send_midi(seqp, 0, arg1 | 0xB0, 0xFC, 0xFF);
}

/* was func_10017C68 */
void n_csp_fade_chan(N_ALCSPlayer *seqp, s32 arg1, u8 arg2, u8 arg3) {
    n_csp_send_midi(seqp, 0, arg1 | 0xB0, 0xFD, arg3);
    n_csp_send_midi(seqp, 0, arg1 | 0xB0, 0xFF, arg2);
}

/* was func_10017CE0 */
void n_csp_set_chan_fx_enable(N_ALCSPlayer *seqp, s32 arg1, u8 arg2) {
    n_csp_send_midi(seqp, 0, arg1 | 0xB0, 0x41, arg2);
}

/* was func_10017D30 */
void n_csp_set_chan_level(N_ALCSPlayer *seqp, s32 arg1, u8 arg2) {
    n_csp_send_midi(seqp, 0, arg1 | 0xB0, 0xFC, arg2);
}
