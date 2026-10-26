#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#include "controller.h"

extern OSPifRam __osContPifRam;
extern u8 _osLastSentSiCmd;      // __osContLastCmd
extern u8 _osContNumControllers; // __osMaxControllers
void __osSiGetAccess(void);
void __osSiRelAccess(void);
s32 os_si_raw_start_dma(s32, void *); // __osSiRawStartDma
static void contreaddata_text_017C(void);


u32 __osSpGetStatus(void);
void __osSpSetStatus(u32);

OSYieldResult osSpTaskYielded(OSTask *tp) {
    s32 status;
    OSYieldResult result;

    status = __osSpGetStatus();
    if (status & SP_STATUS_YIELDED) {
        result = OS_TASK_YIELDED;
    } else {
        result = 0;
    }
    if (status & SP_STATUS_YIELD) {
        tp->t.flags |= result;
        tp->t.flags &= ~OS_TASK_DP_WAIT;
    }
    return result;
}

void osSpTaskYield(void) {
    __osSpSetStatus(SP_SET_YIELD);
}

s32 osContStartReadData(OSMesgQueue *mq) {
    s32 ret = 0;
    s32 i;

    __osSiGetAccess();
    if (_osLastSentSiCmd != CONT_CMD_READ_BUTTON) {
        contreaddata_text_017C();
        ret = os_si_raw_start_dma(OS_WRITE, &__osContPifRam);
        osRecvMesg(mq, NULL, OS_MESG_BLOCK);
    }
    for (i = 0; i < 16; i++) {
        __osContPifRam.ramarray[i] = 0xFF;
    }
    __osContPifRam.pifstatus = 0;
    ret = os_si_raw_start_dma(OS_READ, &__osContPifRam);
    _osLastSentSiCmd = CONT_CMD_READ_BUTTON;
    __osSiRelAccess();
    return ret;
}

void osContGetReadData(OSContPad *data) {
    u8 *ptr = (u8 *)__osContPifRam.ramarray;
    __OSContReadFormat readformat;
    int i;

    for (i = 0; i < _osContNumControllers; i++, ptr += sizeof(__OSContReadFormat), data++) {
        readformat = *(__OSContReadFormat *)ptr;
        data->errno = CHNL_ERR(readformat);
        if (data->errno == 0) {
            data->button = readformat.button;
            data->stick_x = readformat.stick_x;
            data->stick_y = readformat.stick_y;
        }
    }
}

// __osPackReadData
static void contreaddata_text_017C(void) {
    u8 *ptr = (u8 *)__osContPifRam.ramarray;
    __OSContReadFormat readformat;
    int i;

    for (i = 0; i < 16; i++) {
        __osContPifRam.ramarray[i] = 0;
    }
    __osContPifRam.pifstatus = CONT_CMD_EXE;
    readformat.dummy = CONT_CMD_NOP;
    readformat.txsize = CONT_CMD_READ_BUTTON_TX;
    readformat.rxsize = CONT_CMD_READ_BUTTON_RX;
    readformat.cmd = CONT_CMD_READ_BUTTON;
    readformat.button = 0xFFFF;
    readformat.stick_x = -1;
    readformat.stick_y = -1;
    for (i = 0; i < _osContNumControllers; i++) {
        *(__OSContReadFormat *)ptr = readformat;
        ptr += sizeof(__OSContReadFormat);
    }
    *ptr = CONT_CMD_END;
}
