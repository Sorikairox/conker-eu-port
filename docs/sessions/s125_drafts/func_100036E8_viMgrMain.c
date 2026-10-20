// s125: viMgrMain (ultralib io/vimgr.c without the `first` block)
void func_100036E8(void *arg) {
    OSViContext_s86 *vc;
    OSDevMgr_s86 *dm;
    OSIoMesg *mb;
    u32 count;

    mb = NULL;
    vc = __osGetActiveQueue();
    if ((D_80038190 = vc->retraceCount) == 0) {
        D_80038190 = 1;
    }
    dm = (OSDevMgr_s86 *) arg;
    while (TRUE) {
        osRecvMesg(dm->evtQueue, (OSMesg *) &mb, OS_MESG_BLOCK);
        switch (mb->hdr.type) {
            case OS_MESG_TYPE_VRETRACE:
                __osViSwapContext();
                if (--D_80038190 == 0) {
                    vc = __osGetActiveQueue();
                    if (vc->msgq != NULL) {
                        osSendMesg(vc->msgq, vc->msg, OS_MESG_NOBLOCK);
                    }
                    D_80038190 = vc->retraceCount;
                }
                D_80042D4C++;
                count = D_80042D48;
                D_80042D48 = osGetCount();
                count = D_80042D48 - count;
                D_80042D40 = D_80042D40 + count;
                break;
            case OS_MESG_TYPE_COUNTER:
                __osTimerInterrupt();
                break;
        }
    }
}
