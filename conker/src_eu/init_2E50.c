#include <ultra64.h>
#include "functions.h"
#include "variables.h"

// libultra io/devmgr.c, pre-2.0J __osDevMgrMain (no 64DD block), with a Rare addition:
// DMAREAD stops the thread g_os_pi_thread while g_pi_direct_read_active is set and flags g_pi_dma_busy while the read is in flight.
extern OSThread g_os_pi_thread; /* was D_80035C70 */
extern u8 g_pi_direct_read_active; /* was D_8003A8D2 */
extern u8 g_pi_dma_busy; /* was D_8003A8D3 */
extern u8 g_pi_restart_thread; /* was D_8003A8D5 */

/* was func_10002E50 */
void pi_dev_mgr_main(void *args) {
    OSIoMesg *mb;
    OSMesg em;
    OSMesg dummy;
    s32 ret;
    OSDevMgr *dm;

    dm = (OSDevMgr *)args;
    mb = NULL;
    ret = 0;
    while (TRUE) {
        osRecvMesg(dm->cmdQueue, (OSMesg)&mb, OS_MESG_BLOCK);
        switch (mb->hdr.type) {
            case OS_MESG_TYPE_DMAREAD:
                if (g_pi_direct_read_active) {
                    g_pi_restart_thread = 1;
                    osStopThread(&g_os_pi_thread);
                    g_pi_restart_thread = 0;
                }
                g_pi_dma_busy = 1;
                osRecvMesg(dm->acsQueue, &dummy, OS_MESG_BLOCK);
                ret = dm->dma(OS_READ, mb->devAddr, mb->dramAddr, mb->size);
                break;
            case OS_MESG_TYPE_DMAWRITE:
                osRecvMesg(dm->acsQueue, &dummy, OS_MESG_BLOCK);
                ret = dm->dma(OS_WRITE, mb->devAddr, mb->dramAddr, mb->size);
                break;
            case OS_MESG_TYPE_EDMAREAD:
                osRecvMesg(dm->acsQueue, &dummy, OS_MESG_BLOCK);
                ret = dm->edma(mb->piHandle, OS_READ, mb->devAddr, mb->dramAddr, mb->size);
                break;
            case OS_MESG_TYPE_EDMAWRITE:
                osRecvMesg(dm->acsQueue, &dummy, OS_MESG_BLOCK);
                ret = dm->edma(mb->piHandle, OS_WRITE, mb->devAddr, mb->dramAddr, mb->size);
                break;
            case OS_MESG_TYPE_LOOPBACK:
                osSendMesg(mb->hdr.retQueue, mb, OS_MESG_NOBLOCK);
                ret = -1;
                break;
            default:
                ret = -1;
                break;
        }
        if (ret == 0) {
            osRecvMesg(dm->evtQueue, &em, OS_MESG_BLOCK);
            osSendMesg(mb->hdr.retQueue, mb, OS_MESG_NOBLOCK);
            osSendMesg(dm->acsQueue, NULL, OS_MESG_NOBLOCK);
            if (mb->hdr.type == OS_MESG_TYPE_DMAREAD) {
                g_pi_dma_busy = 0;
            }
        }
    }
}
