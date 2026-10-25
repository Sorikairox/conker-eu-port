/* P281: readable C for func_100036E8 (libultra viMgrMain, compiled C, 110 insns). Verified with difftest up to the
   N-th osRecvMesg (DIFFTEST_STOPCALL): the loop never returns. */
// vi_manager_main: the VI manager thread. Waits on the event queue: a retrace message swaps the VI context, counts
// down the retrace interval (sending the client's message when it expires and reloading it), counts the interrupt
// and advances __osCurrentTime by the counter ticks since the last retrace; a counter message runs the timers.
void func_100036E8(void *arg) {
    OSDevMgr_s86 *dm = arg;
    OSViContext_s86 *vc;
    OSMesg mesg = NULL;
    u32 count;

    vc = __osGetActiveQueue();
    D_80038190 = vc->retraceCount;
    if (D_80038190 == 0) {
        D_80038190 = 1;
    }
    while (TRUE) {
        osRecvMesg(dm->evtQueue, &mesg, OS_MESG_BLOCK);
        switch (((OSIoMesg *) mesg)->hdr.type) {
            case OS_MESG_TYPE_VRETRACE:
                __osViSwapContext();
                D_80038190--;
                if (D_80038190 == 0) {
                    vc = __osGetActiveQueue();
                    if (vc->msgq != NULL) {
                        osSendMesg(vc->msgq, vc->msg, OS_MESG_NOBLOCK);
                    }
                    D_80038190 = vc->retraceCount;
                }
                D_80042D4C++;
                count = osGetCount();
                D_80042D40 += count - D_80042D48;
                D_80042D48 = count;
                break;
            case OS_MESG_TYPE_COUNTER:
                __osTimerInterrupt();
                break;
        }
    }
}
