#include "n_libaudio.h"


// this was the very first function to be successfully translated to C

// n_alSeqpPlay or n_alCSPPlay?
/* was func_10017AA0 */
void n_csp_play(N_ALCSPlayer *seqp)
{
    N_ALEvent evt;
    evt.type            = AL_SEQP_PLAY_EVT;

    n_alEvtqPostEvent(&seqp->evtq, &evt, 0, 2);
}
