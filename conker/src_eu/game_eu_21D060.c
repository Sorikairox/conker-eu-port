#include <ultra64.h>
#include "functions.h"
#include "variables.h"
#include "controller.h"


extern s32 D_8002C160;          /* __osContinitialized */
extern u64 D_8002C060;          /* osClockRate */
extern u8 D_80042DE0;           /* __osContLastCmd */
extern u8 D_80042DE1;           /* __osMaxControllers */
extern OSPifRam D_80042DA0;     /* __osContPifRam */
extern OSMesgQueue D_80042E08;  /* __osEepromTimerQ */
extern OSMesg D_80042E20;       /* __osEepromTimerMsg */
s32 os_si_raw_start_dma(s32, void *); /* __osSiRawStartDma */
void __osPackRequestData(u8);
void __osContGetInitData(u8 *, OSContStatus *);
void __osSiCreateAccessQueue(void);

/* was func_151EF850 */
s32 game_os_cont_init(OSMesgQueue *mq, u8 *bitpattern, OSContStatus *data) {
    OSMesg dummy;
    s32 ret = 0;
    OSTime t;
    OSTimer mytimer;
    OSMesgQueue timerMesgQueue;

    if (D_8002C160) {
        return 0;
    }
    D_8002C160 = TRUE;
    t = osGetTime();
    if (t < (500000ULL * D_8002C060) / 1000000ULL) {
        osCreateMesgQueue(&timerMesgQueue, &dummy, 1);
        osSetTimer(&mytimer, (500000ULL * D_8002C060) / 1000000ULL - t, 0, &timerMesgQueue, &dummy);
        osRecvMesg(&timerMesgQueue, &dummy, OS_MESG_BLOCK);
    }
    D_80042DE1 = 4;
    __osPackRequestData(0);
    ret = os_si_raw_start_dma(OS_WRITE, &D_80042DA0);
    osRecvMesg(mq, &dummy, OS_MESG_BLOCK);
    ret = os_si_raw_start_dma(OS_READ, &D_80042DA0);
    osRecvMesg(mq, &dummy, OS_MESG_BLOCK);
    __osContGetInitData(bitpattern, data);
    D_80042DE0 = 0;
    __osSiCreateAccessQueue();
    osCreateMesgQueue(&D_80042E08, &D_80042E20, 1);
    return ret;
}

extern u8 D_80042DE1;
extern OSPifRam D_80042DA0;
/* was func_151EFA48 */
void game_os_cont_get_init_data(u8 *pattern, OSContStatus *data) {
    u8 *ptr;
    __OSContRequesFormat requestformat;
    int i;
    u8 bits;

    bits = 0;
    ptr = (u8 *)D_80042DA0.ramarray;
    for (i = 0; i < D_80042DE1; i++, ptr += sizeof(requestformat), data++) {
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

extern OSPifRam __osContPifRam;
extern u8 _osContNumControllers;
/* was func_151EFB18 */
void game_os_pack_request_data(u8 cmd) {
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
