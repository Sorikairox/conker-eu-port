#include <libaudio.h>
#include "n_libaudio.h"
#include "n_seqp.h"


/* was func_10018C60 */
void n_csp_end_track(N_ALSeqPlayer *seqp) {
    N_ALEvent evt;

    evt.type = AL_TRACK_END;
    n_alEvtqPostEvent(&seqp->evtq, &evt, 0, 2);
}
