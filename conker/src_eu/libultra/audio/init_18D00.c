#include "n_libaudio.h"


/* was func_10018D00 */
void n_csp_set_vol(N_ALCSPlayer *seqp, s16 vol)
{
    N_ALEvent evt;

    evt.type            = AL_SEQP_VOL_EVT;
    evt.msg.spvol.vol   = vol;

    n_alEvtqPostEvent(&seqp->evtq, &evt, 0, 2);
}
