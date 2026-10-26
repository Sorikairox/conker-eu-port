#include <n_libaudio.h>


/* was func_10017AF0 */
void n_csp_set_msg_queue(N_ALCSPlayer *seqp, s32 arg1) {
    seqp->unk84 = arg1;
}

/* was func_10017B04 */
void n_csp_set_chan_notify(N_ALCSPlayer *seqp, s32 chan, u8 arg2) {
    seqp->chanState[chan].unk17 = arg2;
}

/* was func_10017B30 */
void n_csp_reset_chan_levels(N_ALCSPlayer *seqp) {
    s32 chan;

    seqp->chanMask = 0xFFFF;
    for (chan = 0; chan < seqp->maxChannels; chan++)
    {
        seqp->chanState[chan].unkE = 0xFF;
        seqp->chanState[chan].unkD = 0xFF;
    }
}

/* was func_10017BB8 */
void n_csp_mute_chan(N_ALCSPlayer *seqp, s32 arg1) {
    n_csp_send_midi(seqp, 0, arg1 | 0xB0, 252, 0);
}
