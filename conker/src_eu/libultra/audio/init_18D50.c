#include "n_libaudio.h"


/* was func_10018D50 */
void n_csp_stop(N_ALCSPlayer *seqp)
{
    N_ALEvent evt;

    evt.type            = AL_SEQP_STOP_EVT;

    n_alEvtqPostEvent(&seqp->evtq, &evt, 0, 2);
}
