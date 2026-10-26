#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#include "controller.h"

// EU addresses are in undefined_syms.eu.txt; this file is built -O1
extern s32 __osContinitialized;
extern OSPifRam __osContPifRam;
extern u8 _osLastSentSiCmd;      // __osContLastCmd
extern u8 _osContNumControllers; // __osMaxControllers
extern OSMesgQueue __osEepromTimerQ;
extern OSMesg __osEepromTimerMsg;
void __osSiCreateAccessQueue(void);
s32 os_si_raw_start_dma(s32, void *); // __osSiRawStartDma
void __osContGetInitData(u8 *pattern, OSContStatus *data);
void __osPackRequestData(u8 cmd);

#define USEC_TO_CYCLES(n) (((u64)(n) * osClockRate) / 1000000LL)

s32 osContInit(OSMesgQueue *mq, u8 *bitpattern, OSContStatus *data) {
    OSMesg dummy;
    s32 ret = 0;
    OSTime t;
    OSTimer mytimer;
    OSMesgQueue timerMesgQueue;

    if (__osContinitialized) {
        return 0;
    }
    __osContinitialized = 1;
    t = osGetTime();
    if (t < USEC_TO_CYCLES(500000)) {
        osCreateMesgQueue(&timerMesgQueue, &dummy, 1);
        osSetTimer(&mytimer, USEC_TO_CYCLES(500000) - t, 0, &timerMesgQueue, &dummy);
        osRecvMesg(&timerMesgQueue, &dummy, OS_MESG_BLOCK);
    }
    _osContNumControllers = MAXCONTROLLERS;
    __osPackRequestData(CONT_CMD_REQUEST_STATUS);
    ret = os_si_raw_start_dma(OS_WRITE, &__osContPifRam);
    osRecvMesg(mq, &dummy, OS_MESG_BLOCK);
    ret = os_si_raw_start_dma(OS_READ, &__osContPifRam);
    osRecvMesg(mq, &dummy, OS_MESG_BLOCK);
    __osContGetInitData(bitpattern, data);
    _osLastSentSiCmd = CONT_CMD_REQUEST_STATUS;
    __osSiCreateAccessQueue();
    osCreateMesgQueue(&__osEepromTimerQ, &__osEepromTimerMsg, 1);
    return ret;
}

void __osContGetInitData(u8 *pattern, OSContStatus *data) {
    u8 *ptr;
    __OSContRequesFormat requestformat;
    int i;
    u8 bits;

    bits = 0;
    ptr = (u8 *)__osContPifRam.ramarray;
    for (i = 0; i < _osContNumControllers; i++, ptr += sizeof(requestformat), data++) {
        requestformat = *(__OSContRequesFormat *)ptr;
        data->errno = CHNL_ERR(requestformat);
        if (data->errno == 0) {
            data->type = (requestformat.typel << 8) | requestformat.typeh;
            data->status = requestformat.status;
            bits |= 1 << i;
        }
    }
    *pattern = bits;
}

void __osPackRequestData(u8 cmd) {
    u8 *ptr;
    __OSContRequesFormat requestformat;
    int i;

    for (i = 0; i < 16; i++) {
        __osContPifRam.ramarray[i] = 0;
    }
    __osContPifRam.pifstatus = CONT_CMD_EXE;
    ptr = (u8 *)__osContPifRam.ramarray;
    requestformat.dummy = CONT_CMD_NOP;
    requestformat.txsize = CONT_CMD_REQUEST_STATUS_TX;
    requestformat.rxsize = CONT_CMD_REQUEST_STATUS_RX;
    requestformat.cmd = cmd;
    requestformat.typeh = CONT_CMD_NOP;
    requestformat.typel = CONT_CMD_NOP;
    requestformat.status = CONT_CMD_NOP;
    requestformat.dummy1 = CONT_CMD_NOP;
    for (i = 0; i < _osContNumControllers; i++) {
        *(__OSContRequesFormat *)ptr = requestformat;
        ptr += sizeof(requestformat);
    }
    *ptr = CONT_CMD_END;
}
